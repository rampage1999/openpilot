"""The big-model preflight must reject the files that make tinygrad abort."""

import hashlib
import json
import struct
import unittest

from openpilot.sunnypilot.modeld_v2.chestnut_load import PLAIN_MAGIC, preflight_big_model


def _plain(path, devices: list[str]) -> None:
  header = {
    "parts": [{
      "key": "run",
      "blob": [0, 0],
      "header": {
        "buffers": [{"device": device, "nbytes": 4} for device in devices],
        "inputs": [],
        "calls": [],
      },
    }],
    "extras": [0, 0],
  }
  payload = json.dumps(header).encode()
  blob = PLAIN_MAGIC + struct.pack("<Q", len(payload)) + payload
  blob += b"\0" * (-len(blob) % 256)
  path.write_bytes(blob + b"\0" * 32)


class TestChestnutPreflight(unittest.TestCase):
  def test_missing_pkl(self):
    reason = preflight_big_model(None, "/no/warp.pkl", min_model_bytes=1, min_warp_bytes=1)
    self.assertIn("no chestnut driving pkl", reason)

  def test_lfs_pointer_and_partial(self):
    import tempfile
    from pathlib import Path
    with tempfile.TemporaryDirectory() as directory:
      root = Path(directory)
      pointer = root / "partial.pkl"
      pointer.write_bytes(b"version https://git-lfs.github.com/spec/v1\noid sha256:abc\nsize 1\n")
      warp = root / "warp.pkl"
      _plain(warp, ["AMD"])
      reason = preflight_big_model(str(pointer), str(warp), min_model_bytes=1, min_warp_bytes=1)
      self.assertIn("Git LFS pointer", reason)

      small = root / "small.pkl"
      _plain(small, ["AMD"])
      reason = preflight_big_model(str(small), str(warp), min_model_bytes=10_000_000, min_warp_bytes=1)
      self.assertIn("partial download", reason)

  def test_qcom_artifact_is_refused(self):
    import tempfile
    from pathlib import Path
    with tempfile.TemporaryDirectory() as directory:
      root = Path(directory)
      pkl, warp = root / "qcom.pkl", root / "warp.pkl"
      _plain(pkl, ["QCOM"])
      _plain(warp, ["AMD"])
      reason = preflight_big_model(str(pkl), str(warp), min_model_bytes=1, min_warp_bytes=1)
      self.assertIn("QCOM", reason)
      self.assertIn("not the USB AMD", reason)

  def test_hash_mismatch_and_amd_ok(self):
    import tempfile
    from pathlib import Path
    with tempfile.TemporaryDirectory() as directory:
      root = Path(directory)
      pkl, warp = root / "amd.pkl", root / "warp.pkl"
      _plain(pkl, ["AMD", "NPY"])
      _plain(warp, ["AMD"])
      bad = preflight_big_model(str(pkl), str(warp), expected_sha256="0" * 64, min_model_bytes=1, min_warp_bytes=1)
      self.assertIn("sha256 mismatch", bad)
      digest = hashlib.sha256(pkl.read_bytes()).hexdigest()
      self.assertIsNone(preflight_big_model(str(pkl), str(warp), expected_sha256=digest, min_model_bytes=1, min_warp_bytes=1))

  def test_warp_must_be_plain_amd(self):
    import tempfile
    from pathlib import Path
    with tempfile.TemporaryDirectory() as directory:
      root = Path(directory)
      pkl, warp = root / "amd.pkl", root / "warp.pkl"
      _plain(pkl, ["AMD"])
      warp.write_bytes(b"not a model")
      reason = preflight_big_model(str(pkl), str(warp), min_model_bytes=1, min_warp_bytes=1)
      self.assertIn("camera warp", reason)
      _plain(warp, ["QCOM"])
      reason = preflight_big_model(str(pkl), str(warp), min_model_bytes=1, min_warp_bytes=1)
      self.assertIn("camera warp", reason)


if __name__ == "__main__":
  unittest.main()
