"""Load the chestnut big model without taking the small-model modeld down.

The driving pkl is a plain SPTGPLN1 artifact compiled for the USB AMD device
(ASM2464). A comma pickle, a Git LFS pointer, a partial download, or a QCOM
artifact must be refused before tinygrad opens the GPU: those paths abort the
process instead of raising. The actual construct+warmup then runs in a child
process so an abort or an OOM during the upload kills the probe, not modeld.
"""

import hashlib
import json
import os
import struct
import traceback
from pathlib import Path

try:
  from openpilot.common.swaglog import cloudlog
except Exception:  # unit tests and a half-installed checkout still need the file checks
  import logging
  cloudlog = logging.getLogger("chestnut")

PLAIN_MAGIC = b"SPTGPLN1"
LFS_PREFIX = b"version https://git-lfs.github.com/spec/v1"
# Real chestnut driving artifacts are hundreds of MB. Anything smaller is a
# pointer, a truncated download, or the wrong file.
MIN_MODEL_BYTES = 8 << 20
MIN_WARP_BYTES = 64 << 10
PROBE_TIMEOUT_S = 180
PROBE_LOG = "/tmp/chestnut_big_model_probe.log"
# AMD is the eGPU. NPY/CPU/DISK show up as host-side buffers inside the artifact.
_CHESTNUT_DEVICE_PREFIXES = ("AMD", "NPY", "CPU", "DISK", "NULL")
BIG_MODEL_STABLE_FRAMES = 30


def memory_line() -> str:
  rss, avail = "unknown", "unknown"
  try:
    for line in Path("/proc/self/status").read_text().splitlines():
      if line.startswith("VmRSS:"):
        rss = line.split()[1] + " kB"
  except OSError:
    pass
  try:
    for line in Path("/proc/meminfo").read_text().splitlines():
      if line.startswith("MemAvailable:"):
        avail = line.split()[1] + " kB"
  except OSError:
    pass
  return f"rss={rss} mem_available={avail}"


def file_sha256(path: str) -> str:
  with open(path, "rb") as handle:
    return hashlib.file_digest(handle, "sha256").hexdigest()


def _read_header(path: str) -> tuple[bytes, dict | None, str | None]:
  """Return (magic, header or None, error or None). Does not touch the GPU."""
  try:
    size = os.path.getsize(path)
  except OSError as exc:
    return b"", None, f"{path} cannot be stat'd ({exc})"
  try:
    with open(path, "rb") as handle:
      magic = handle.read(len(PLAIN_MAGIC))
      if magic.startswith(LFS_PREFIX[:8]) or magic == LFS_PREFIX[:len(magic)]:
        # Distinguish a real Git LFS pointer from a short read of something else.
        handle.seek(0)
        prefix = handle.read(len(LFS_PREFIX))
        if prefix == LFS_PREFIX:
          return prefix, None, f"{path} is a Git LFS pointer ({size} bytes), not model weights"
      if magic != PLAIN_MAGIC:
        return magic, None, (
          f"{path} is not a plain tinygrad model (magic {magic[:16]!r}, {size} bytes). "
          "Chestnut weights must be an SPTGPLN1 artifact compiled for the USB AMD eGPU, "
          "not a comma pickle and not a QCOM driving_tinygrad.pkl."
        )
      (length,) = struct.unpack("<Q", handle.read(8))
      if length <= 0 or length > (64 << 20):
        return magic, None, f"{path} has an absurd header length {length}"
      header = json.loads(handle.read(length))
  except (OSError, struct.error, json.JSONDecodeError, UnicodeError) as exc:
    return b"", None, f"{path} could not be parsed ({exc})"
  return magic, header, None


def artifact_devices(header: dict) -> set[str]:
  found: set[str] = set()
  for entry in header.get("parts") or []:
    part = entry.get("header") or {}
    for buf in part.get("buffers") or []:
      if device := buf.get("device"):
        found.add(str(device))
    for spec in part.get("inputs") or []:
      if device := spec.get("device"):
        found.add(str(device))
  return found


def _device_ok(device: str) -> bool:
  prefix = device.split(":", 1)[0]
  return prefix in _CHESTNUT_DEVICE_PREFIXES


def describe_artifact(path: str) -> dict:
  """Facts a diagnostic can print. Never raises."""
  info: dict = {"path": path, "exists": False}
  try:
    info["exists"] = os.path.isfile(path)
    if not info["exists"]:
      return info
    info["size"] = os.path.getsize(path)
    magic, header, error = _read_header(path)
    info["magic"] = magic[:16]
    info["plain"] = magic == PLAIN_MAGIC and header is not None
    info["header_error"] = error
    if header is not None:
      info["devices"] = sorted(artifact_devices(header))
    info["sha256"] = file_sha256(path)
  except Exception as exc:
    info["error"] = str(exc)
  return info


def preflight_big_model(pkl_path: str | None, warp_path: str, expected_sha256: str | None = None,
                        min_model_bytes: int = MIN_MODEL_BYTES, min_warp_bytes: int = MIN_WARP_BYTES) -> str | None:
  """Return a human-readable refusal, or None when the files are safe to load."""
  if not pkl_path:
    return "no chestnut driving pkl. The model manager has not finished a hashed download into the chestnut slot."
  if not os.path.isfile(pkl_path):
    return f"chestnut driving pkl is not on disk: {pkl_path}"
  try:
    size = os.path.getsize(pkl_path)
  except OSError as exc:
    return f"chestnut driving pkl cannot be stat'd: {pkl_path} ({exc})"
  if size < min_model_bytes:
    return (
      f"chestnut driving pkl is only {size} bytes ({pkl_path}). "
      "That is a partial download or a Git LFS pointer, not the big model. "
      "The model manager deletes a file that fails its sha256; wait until the chestnut download reaches 100."
    )
  _, header, error = _read_header(pkl_path)
  if error:
    return error
  assert header is not None
  devices = artifact_devices(header)
  bad = sorted(device for device in devices if not _device_ok(device))
  if bad:
    return (
      f"chestnut driving pkl targets {bad}, not the USB AMD eGPU ({pkl_path}). "
      "A QCOM (onboard Adreno) artifact cannot be remapped onto the chestnut. "
      f"Recorded devices: {sorted(devices) or 'none'}."
    )
  if not devices:
    return f"chestnut driving pkl records no devices ({pkl_path})"
  if "AMD" not in {device.split(':', 1)[0] for device in devices}:
    return f"chestnut driving pkl has no AMD buffers ({sorted(devices)}); it will not run on the eGPU"

  expected = (expected_sha256 or "").strip().lower()
  if expected:
    digest = file_sha256(pkl_path)
    if digest != expected:
      return (
        f"chestnut driving pkl sha256 mismatch for {pkl_path}: on disk {digest}, bundle expects {expected}. "
        "The file is a partial or corrupt download and will not be loaded."
      )

  if not os.path.isfile(warp_path):
    return (
      f"camera warp for this frame size is missing: {warp_path}. "
      "The big model fuses this warp in front of the network. "
      "A comma 4 frame is 1928x1208 or 1344x760; both big_driving_warp pkls must be real SPTGPLN1 files, not LFS pointers."
    )
  try:
    warp_size = os.path.getsize(warp_path)
  except OSError as exc:
    return f"camera warp cannot be stat'd: {warp_path} ({exc})"
  if warp_size < min_warp_bytes:
    return f"camera warp is only {warp_size} bytes ({warp_path}), expected a compiled SPTGPLN1 warp"
  _, warp_header, warp_error = _read_header(warp_path)
  if warp_error:
    return f"camera warp: {warp_error}"
  assert warp_header is not None
  warp_devices = artifact_devices(warp_header)
  warp_bad = sorted(device for device in warp_devices if not _device_ok(device))
  if warp_bad or "AMD" not in {device.split(':', 1)[0] for device in warp_devices}:
    return f"camera warp targets {sorted(warp_devices) or warp_bad}, not AMD ({warp_path})"
  return None


def bundle_sha256(bundle) -> str | None:
  try:
    digest = bundle.models[0].artifact.downloadUri.sha256
  except (AttributeError, IndexError, TypeError):
    return None
  digest = (digest or "").strip().lower()
  return digest or None


def warp_path_for(cam_w: int, cam_h: int) -> str:
  from openpilot.common.basedir import BASEDIR
  return f"{BASEDIR}/openpilot/sunnypilot/modeld_v2/models/big_driving_warp_{cam_w}x{cam_h}_tinygrad.pkl"


def note_big_model_failure(params) -> None:
  """Remember the failure for this ignition so a restarted modeld stays on the small model.

  ChestnutLoading is left alone. hardwared stops touching the ASM2464 while that
  param is set, and the weight upload is still using the link. The driving loop
  clears it when the load thread exits.
  """
  for key, value in (("ChestnutActive", False), ("ChestnutBigFailed", True)):
    try:
      params.put_bool(key, value, block=True)
    except Exception:
      cloudlog.exception("chestnut big model: could not record param %s", key)


def big_model_already_failed(params) -> bool:
  try:
    return bool(params.get_bool("ChestnutBigFailed"))
  except Exception:
    return False


def _prefer_oom_kill() -> None:
  # The probe is disposable. Ask the kernel to reclaim it before modeld.
  try:
    Path("/proc/self/oom_score_adj").write_text("1000")
  except OSError:
    pass


def prepare_chestnut_runtime() -> None:
  """Local amdgpu firmware + zstd decompress. Stock modeld does this; modeld_v2 used to skip it.

  tinygrad only reads /lib/firmware amdgpu microcode on Python 3.14+. AGNOS ships that
  microcode as zstd, and the eGPU's userspace driver needs it before the first AMD buffer.
  Without the patch the big model opens the USB GPU, fails to fetch firmware, and aborts
  while the QCOM small model was already fine.
  """
  from openpilot.selfdrive.modeld.helpers import _patch_amdgpu_firmware_fetch
  _patch_amdgpu_firmware_fetch()
  from openpilot.sunnypilot.modeld_v2.helpers import patch_fetch_fw
  patch_fetch_fw()
  try:
    from tinygrad.runtime.ops_amd import AMDDevice
    AMDDevice.wait_timeout_ms = 3000
  except Exception:
    cloudlog.exception("chestnut big model: could not set the AMD command timeout")


def probe_big_model_process(cam_w: int, cam_h: int, log_path: str) -> None:
  """Child entry. Spawned so a GPU abort does not kill modeld. Writes a traceback and re-raises."""
  _prefer_oom_kill()
  try:
    os.environ["GMMU"] = "0"
    prepare_chestnut_runtime()
    from openpilot.sunnypilot.modeld_v2.modeld import ModelState
    model = ModelState(cam_w, cam_h, True)
    model.warmup()
    del model
  except Exception:
    try:
      Path(log_path).write_text(traceback.format_exc())
    except OSError:
      pass
    raise


def _read_probe_log(log_path: str) -> str:
  try:
    return Path(log_path).read_text(errors="replace")[:8000]
  except OSError:
    return ""


def load_big_model_guarded(cam_w: int, cam_h: int):
  """Warmed chestnut ModelState, or None. Does not raise. Leaves the small model untouched."""
  from openpilot.common.params import Params
  params = Params()
  if big_model_already_failed(params):
    cloudlog.error(
      "chestnut big model: not retrying after a failure this ignition (param ChestnutBigFailed). "
      "The small model stays up. Restart the car to try the eGPU model again. %s", memory_line())
    return None

  from openpilot.sunnypilot.modeld_v2.modeld import _find_driving_pkl
  from openpilot.sunnypilot.models.helpers import get_active_bundle
  env_pkl = os.environ.get("COMBINED_MODEL_PKL")
  bundle = None if env_pkl and os.path.exists(env_pkl) else get_active_bundle(chestnut=True)
  pkl_path = env_pkl if env_pkl and os.path.exists(env_pkl) else _find_driving_pkl(bundle)
  warp = warp_path_for(cam_w, cam_h)
  expected = None if env_pkl and os.path.exists(env_pkl) else bundle_sha256(bundle)
  refusal = preflight_big_model(pkl_path, warp, expected)
  if refusal:
    cloudlog.error("chestnut big model refused: %s | warp=%s %s", refusal, warp, memory_line())
    try:
      params.put_bool("ChestnutActive", False)
      params.put_bool("ChestnutLoading", False)
    except Exception:
      cloudlog.exception("chestnut big model: could not record the refusal")
    return None

  # Set before the child starts. If this process is killed mid-load, the next
  # modeld start sees the flag and publishes the small model instead of trying again.
  note_big_model_failure(params)
  cloudlog.warning(
    "chestnut big model: probing %s (%s bytes) in a child process before loading it into modeld. %s",
    pkl_path, os.path.getsize(pkl_path), memory_line())

  import multiprocessing
  try:
    Path(PROBE_LOG).unlink(missing_ok=True)
  except OSError:
    pass
  ctx = multiprocessing.get_context("spawn")
  proc = ctx.Process(target=probe_big_model_process, args=(cam_w, cam_h, PROBE_LOG), daemon=True)
  proc.start()
  proc.join(PROBE_TIMEOUT_S)
  if proc.is_alive():
    cloudlog.error("chestnut big model: probe still running after %ss; killing it and staying on the small model. %s",
                   PROBE_TIMEOUT_S, memory_line())
    proc.kill()
    proc.join(5)
    return None
  if proc.exitcode != 0:
    cloudlog.error(
      "chestnut big model: probe exited %s (signal %s if negative). Staying on the small model.\n%s",
      proc.exitcode, -proc.exitcode if proc.exitcode and proc.exitcode < 0 else 0, _read_probe_log(PROBE_LOG))
    return None

  cloudlog.warning("chestnut big model: probe ok, loading into modeld. %s", memory_line())
  try:
    prepare_chestnut_runtime()
    from openpilot.sunnypilot.modeld_v2.modeld import ModelState
    model = ModelState(cam_w, cam_h, True)
    model.warmup()
  except Exception:
    cloudlog.exception("chestnut big model: in-process load failed after a good probe. Staying on the small model. %s",
                       memory_line())
    return None
  cloudlog.warning("chestnut big model: loaded %s. It will be adopted on the next frame. %s", pkl_path, memory_line())
  return model
