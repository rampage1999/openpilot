#!/usr/bin/env python3
"""On-device chestnut eGPU diagnostic. Run over SSH from the openpilot checkout:

  cd /data/openpilot
  python tools/chestnut_diag.py
  python tools/chestnut_diag.py --no-load

Prints USB detection, the driving-weight file (size, magic, sha256, recorded
device), the camera warp, and then loads the big model in this process with a
full traceback. Stop modeld first so this process is the only one opening the
ASM2464:

  tmux a
  # Ctrl-b then the modeld window is not required; from another SSH session:
  pkill -f openpilot.sunnypilot.modeld_v2 || true

modeld's own traceback, when the process dies, is in the manager tmux pane
(stderr) and in swaglog:

  grep -a -E "chestnut big model|modeld exception|big model" /data/log/swaglog /data/log/swaglog.* | tail -200
  ls -lt /data/community/crashes | head
  cat /tmp/chestnut_big_model_probe.log
"""

import argparse
import os
import sys
import traceback

# The repo root is the parent of tools/, which is how the device checkout is laid out.
_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
if _ROOT not in sys.path:
  sys.path.insert(0, _ROOT)


def _section(title: str) -> None:
  print(f"\n=== {title} ===", flush=True)


def _memory() -> None:
  _section("memory")
  for path in ("/proc/meminfo", "/proc/self/status"):
    try:
      lines = open(path).read().splitlines()
    except OSError as exc:
      print(f"{path}: {exc}")
      continue
    interesting = ("MemTotal", "MemAvailable", "MemFree", "VmRSS", "VmSize")
    for line in lines:
      if line.startswith(interesting):
        print(line)


def _usb() -> None:
  _section("usb")
  try:
    from openpilot.common.hardware.usb import USB_DEVICES_PATH, is_chestnut_usb_id
    from openpilot.selfdrive.modeld.helpers import chestnut_firmware_current, chestnut_present
  except Exception:
    traceback.print_exc()
    return
  print(f"sysfs {USB_DEVICES_PATH}")
  found = False
  if USB_DEVICES_PATH.is_dir():
    for device in sorted(USB_DEVICES_PATH.glob("*")):
      try:
        vendor = int((device / "idVendor").read_text(), 16)
        product = int((device / "idProduct").read_text(), 16)
      except (OSError, ValueError):
        continue
      name = ""
      try:
        name = (device / "product").read_text().strip()
      except OSError:
        pass
      speed = ""
      try:
        speed = (device / "speed").read_text().strip()
      except OSError:
        pass
      mark = "  CHESTNUT" if is_chestnut_usb_id(vendor, product) else ""
      print(f"  {vendor:04x}:{product:04x}  speed={speed} Mbps  product={name!r}{mark}")
      found = True
  if not found:
    print("  no usb devices under sysfs (normal on a laptop; on a comma this means the bus was not readable)")
  try:
    print(f"chestnut_present (VID/PID): {chestnut_present()}")
    print(f"chestnut_firmware_current (product string matches bundled firmware): {chestnut_firmware_current()}")
  except Exception:
    traceback.print_exc()


def _weights() -> None:
  _section("weights")
  from openpilot.sunnypilot.modeld_v2.chestnut_load import describe_artifact, warp_path_for

  pkl_path = None
  expected = None
  try:
    from openpilot.common.hardware.hw import Paths
    from openpilot.sunnypilot.modeld_v2.chestnut_load import bundle_sha256
    from openpilot.sunnypilot.modeld_v2.modeld import _find_driving_pkl
    from openpilot.sunnypilot.models.helpers import get_active_bundle
    print(f"model root: {Paths.model_root()}")
    root = Paths.model_root()
    if os.path.isdir(root):
      names = sorted(os.listdir(root))
      print(f"  {len(names)} entries")
      for name in names:
        full = os.path.join(root, name)
        try:
          size = os.path.getsize(full)
        except OSError:
          size = -1
        if name.endswith((".pkl", ".pkl.cache")) or "driving" in name:
          print(f"  {size:12d}  {name}")
    bundle = get_active_bundle(chestnut=True)
    if bundle is None:
      print("active chestnut bundle: none (ModelManager_ActiveBundleChestnut empty or rejected)")
    else:
      print(f"active chestnut bundle: {getattr(bundle, 'displayName', None) or getattr(bundle, 'internalName', None)} "
            f"ref={getattr(bundle, 'ref', None)} runner={getattr(bundle, 'runner', None)}")
      pkl_path = _find_driving_pkl(bundle)
      expected = bundle_sha256(bundle)
      print(f"  pkl: {pkl_path}")
      print(f"  expected sha256: {expected}")
  except Exception:
    print("could not read the active bundle (params/cereal not available here):")
    traceback.print_exc()

  env = os.environ.get("COMBINED_MODEL_PKL")
  if env:
    print(f"COMBINED_MODEL_PKL override: {env}")
    pkl_path = env

  if pkl_path:
    info = describe_artifact(pkl_path)
    _print_artifact("driving pkl", info)
    digest = info.get("sha256")
    if expected and digest:
      print(f"  sha256 match: {digest == expected}")
  else:
    print("no driving pkl path to describe")

  _section("warps")
  from openpilot.common.basedir import BASEDIR
  warp_dir = os.path.join(BASEDIR, "openpilot/sunnypilot/modeld_v2/models")
  print(warp_dir)
  if os.path.isdir(warp_dir):
    for name in sorted(os.listdir(warp_dir)):
      if "warp" not in name:
        continue
      info = describe_artifact(os.path.join(warp_dir, name))
      _print_artifact(name, info)
  for size in ((1928, 1208), (1344, 760)):
    path = warp_path_for(*size)
    print(f"warp {size[0]}x{size[1]} exists={os.path.isfile(path)} path={path}")


def _print_artifact(label: str, info: dict) -> None:
  print(f"{label}:")
  for key in ("path", "exists", "size", "magic", "plain", "devices", "sha256", "header_error", "error"):
    if key in info:
      print(f"  {key}: {info[key]!r}" if key == "magic" else f"  {key}: {info[key]}")


def _gpu_env() -> None:
  _section("gpu env")
  for key in ("GMMU", "DEV", "USB", "USB_GPU", "AMD", "AMD_AQL", "AMD_DISABLE_SDMA", "GRAPH_ONE_KERNEL", "COMBINED_MODEL_PKL"):
    print(f"  {key}={os.environ.get(key)!r}")
  print("  (modeld_v2 forces GMMU=0 and uses the device name baked into the pkl, which is AMD for chestnut weights.")
  print("   It does not read USB_GPU. The eGPU is selected by opening Device AMD, which tinygrad binds to the ASM2464.)")
  try:
    os.environ.setdefault("GMMU", "0")
    from openpilot.sunnypilot.modeld_v2.chestnut_load import prepare_chestnut_runtime
    prepare_chestnut_runtime()
    from tinygrad.device import Device
    print(f"  Device.DEFAULT={Device.DEFAULT!r}")
    amd = Device["AMD"]
    print(f"  Device['AMD']={amd!r} is_usb={getattr(amd, 'is_usb', None)}")
  except Exception:
    print("  opening Device['AMD'] failed:")
    traceback.print_exc()


def _load(cam_w: int, cam_h: int) -> int:
  _section(f"load big model {cam_w}x{cam_h}")
  print("This constructs the chestnut ModelState in this process and runs one warmup.")
  print("A crash here is the same failure modeld hits. The traceback below is the one to keep.")
  try:
    os.environ["GMMU"] = "0"
    from openpilot.sunnypilot.modeld_v2.chestnut_load import (
      preflight_big_model, warp_path_for, bundle_sha256, memory_line)
    from openpilot.sunnypilot.modeld_v2.modeld import _find_driving_pkl
    from openpilot.sunnypilot.models.helpers import get_active_bundle
    env = os.environ.get("COMBINED_MODEL_PKL")
    bundle = None if env and os.path.exists(env) else get_active_bundle(chestnut=True)
    pkl = env if env and os.path.exists(env) else _find_driving_pkl(bundle)
    expected = None if env and os.path.exists(env) else bundle_sha256(bundle)
    warp = warp_path_for(cam_w, cam_h)
    refusal = preflight_big_model(pkl, warp, expected)
    print(f"preflight: {refusal or 'ok'}")
    print(memory_line())
    if refusal:
      return 2
    from openpilot.sunnypilot.modeld_v2.chestnut_load import prepare_chestnut_runtime
    prepare_chestnut_runtime()
    from openpilot.sunnypilot.modeld_v2.modeld import ModelState
    model = ModelState(cam_w, cam_h, True)
    print(f"constructed DEV={model.DEV} generation={model.generation} {memory_line()}")
    model.warmup()
    print(f"warmup ok {memory_line()}")
    return 0
  except Exception:
    traceback.print_exc()
    return 1


def main() -> int:
  parser = argparse.ArgumentParser(description="Print chestnut GPU, weights, and try the big model")
  parser.add_argument("--no-load", action="store_true", help="stop after detection and file checks")
  parser.add_argument("--cam-w", type=int, default=1928)
  parser.add_argument("--cam-h", type=int, default=1208)
  args = parser.parse_args()
  print(f"python {sys.version}")
  print(f"cwd {os.getcwd()}")
  _memory()
  _usb()
  try:
    _weights()
  except Exception:
    traceback.print_exc()
  _gpu_env()
  if args.no_load:
    print("\nskipping the big-model load (--no-load)")
    return 0
  return _load(args.cam_w, args.cam_h)


if __name__ == "__main__":
  sys.exit(main())
