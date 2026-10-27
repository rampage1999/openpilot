import sys
import time
from pathlib import Path

from openpilot.common.hardware import AGNOS
from openpilot.common.hardware.usb import CHESTNUT_USB_PRODUCT, USB_DEVICES_PATH, is_chestnut_usb_id

MODELS_DIR = Path(__file__).resolve().parent / 'models'


def modeld_pkl_path(chestnut: bool):
  prefix = 'big_' if chestnut else ''
  return MODELS_DIR / f'{prefix}driving_tinygrad.pkl'

def _patch_amdgpu_firmware_fetch():
  # Device fix (chestnut-ap1 2ea0c0d06): tinygrad's fetch_fw only reads /lib/firmware
  # on python 3.14+ (needs compression.zstd), but AGNOS ships the amdgpu microcode the
  # USB GPU's userspace driver needs - prefer local firmware (zst or uncompressed,
  # sha256-verified) over the network so the eGPU initializes even offline.
  import hashlib
  import pathlib
  try:
    from tinygrad import helpers
  except Exception:
    return
  if getattr(helpers, "_amdgpu_local_fw_patched", False):
    return
  orig = helpers.fetch_fw

  def fetch_fw(path, name, sha256):
    for fp, zst in ((pathlib.Path(f"/lib/firmware/{path}/{name}.zst"), True),
                    (pathlib.Path(f"/lib/firmware/{path}/{name}"), False)):
      if not fp.is_file():
        continue
      try:
        if zst:
          import zstandard
          blob = zstandard.ZstdDecompressor().stream_reader(fp.read_bytes()).read()
        else:
          blob = fp.read_bytes()
      except Exception:
        continue
      if hashlib.sha256(blob).hexdigest() == sha256:
        return blob
    return orig(path, name, sha256)

  helpers.fetch_fw = fetch_fw
  helpers._amdgpu_local_fw_patched = True

def load_oob(path, chestnut=False):
  if chestnut:
    _patch_amdgpu_firmware_fetch()
  from tinygrad import Context
  device = 'USB+AMD:LLVM' if chestnut else 'QCOM' if AGNOS else 'METAL' if sys.platform == 'darwin' else 'CPU:LLVM'
  with Context(DEV=device):
    from tinygrad_repo.examples.openpilot.helpers import load_pickle
    return load_pickle(path, out_of_band=True)

def chestnut_present() -> bool:
  for d in USB_DEVICES_PATH.glob("*"):
    try:
      usb_id = (int((d / "idVendor").read_text(), 16), int((d / "idProduct").read_text(), 16))
      product = (d / "product").read_text().strip()
      if is_chestnut_usb_id(*usb_id) and product == CHESTNUT_USB_PRODUCT:
        return True
    except Exception:
      pass
  return False

def wait_for_chestnut(timeout: float = 10.) -> None:
  # the cable is detected before chestnut enumerates
  st = time.monotonic()
  while not chestnut_present():
    if time.monotonic() - st > timeout:
      raise TimeoutError("chestnut did not enumerate")
    time.sleep(0.1)

def chestnut_compiled() -> bool:
  path = modeld_pkl_path(chestnut=True)
  return path.is_file() and all(
    (MODELS_DIR / f'big_driving_warp_{size}_tinygrad.pkl').is_file() for size in ('1344x760', '1928x1208'))
