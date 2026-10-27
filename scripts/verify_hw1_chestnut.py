#!/usr/bin/env python3
"""Regression guard: sunnypilot features + Tesla HW1 + Chestnut eGPU must all survive.

Run from the repo root after ANY sync/merge from commaai/openpilot:

    python3 scripts/verify_hw1_chestnut.py

Exits non-zero if an integration point was stripped. This exists because
release-chestnut is NOT a superset of this fork: naively checking out
comma's modeld/ over ours removes livedelay, RoadEdgeLaneChange and
modelDataV2SP. Stdlib only, so it runs anywhere.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
failures: list[str] = []
skipped: list[str] = []
checks = 0


def _read(rel: str) -> str | None:
    p = ROOT / rel
    if not p.is_file():
        return None
    return p.read_text(encoding="utf-8", errors="replace")


def need_file(rel: str, why: str) -> None:
    global checks
    checks += 1
    if not (ROOT / rel).exists():
        failures.append(f"[missing file] {rel}  ({why})")


def need_text(rel: str, needle: str, why: str) -> None:
    global checks
    checks += 1
    body = _read(rel)
    if body is None:
        failures.append(f"[missing file] {rel}  ({why})")
    elif needle not in body:
        failures.append(f"[stripped] {rel!r} no longer contains {needle!r}  ({why})")


def need_text_if_present(rel: str, needle: str, why: str) -> None:
    """For CI-generated artifacts: enforced on prebuilt branches, skipped on source
    branches where the file legitimately does not exist yet."""
    global checks
    if not (ROOT / rel).exists():
        skipped.append(f"{rel} (CI-generated, absent on source branch)")
        return
    checks += 1
    body = _read(rel)
    if body is None or needle not in body:
        failures.append(f"[stripped] {rel!r} no longer contains {needle!r}  ({why})")



# --- A. sunnypilot hooks inside modeld.py (exactly what release-chestnut drops) ---
MODELD = "openpilot/selfdrive/modeld/modeld.py"
for needle, why in [
    ("from openpilot.sunnypilot.livedelay.helpers import get_lat_delay", "live lateral delay"),
    ("from openpilot.sunnypilot.modeld_v2.modeld_base import ModelStateBase", "sunnypilot model base"),
    ("from openpilot.sunnypilot.selfdrive.controls.lib.relc import RoadEdgeLaneChangeController", "road-edge lane change"),
    ("class ModelState(ModelStateBase)", "ModelState must inherit sunnypilot base"),
    ("RoadEdgeLaneChangeController()", "RELC must be instantiated"),
    ("model.lat_delay = get_lat_delay(", "lat delay must be applied"),
    ("modelDataV2SP", "sunnypilot model msg must be published"),
]:
    need_text(MODELD, needle, why)

# --- B. sunnypilot packages ---
for rel, why in [
    ("openpilot/sunnypilot/livedelay/helpers.py", "livedelay"),
    ("openpilot/sunnypilot/modeld_v2/modeld_base.py", "modeld_v2 base"),
    ("openpilot/sunnypilot/selfdrive/controls/lib/relc.py", "RELC"),
    ("openpilot/sunnypilot/models/fetcher.py", "runtime model fetcher"),
]:
    need_file(rel, why)

# --- C. cereal wiring for the sunnypilot message ---
need_text("openpilot/cereal/custom.capnp", "struct ModelDataV2SP", "SP model schema")
need_text("openpilot/cereal/log.capnp", "modelDataV2SP", "SP model union member")
need_text("openpilot/cereal/services.py", "modelDataV2SP", "SP model service")

# --- D. Chestnut eGPU stack ---
need_file("openpilot/system/hardware/chestnut/flash.py", "chestnut flasher")
need_file("openpilot/system/hardware/chestnut/firmware_wrapped.bin", "chestnut firmware")
need_text("openpilot/cereal/log.capnp", "struct ChestnutState", "eGPU telemetry schema")
need_text("openpilot/selfdrive/modeld/helpers.py", "def chestnut_present", "eGPU detection (upstream renamed usbgpu -> chestnut)")
need_text("openpilot/selfdrive/modeld/helpers.py", "def chestnut_compiled", "big-model gate (upstream renamed usbgpu -> chestnut)")
need_text("openpilot/selfdrive/modeld/modeld.py", "chestnutGpuState", "eGPU telemetry published")
need_text("openpilot/sunnypilot/models/fetcher.py", "MODEL_URL_CHESTNUT", "eGPU model bundle URL (upstream renamed usbgpu -> chestnut)")
need_text("openpilot/selfdrive/modeld/helpers.py", "_patch_amdgpu_firmware_fetch", "amdgpu microcode local-firmware fetch (device fix from chestnut-ap1)")
need_text("openpilot/common/hardware/usb.py", "0x3801", "current chestnut USB firmware ID (device fix e08806f1a)")
# Chestnut weights are fetched at runtime by sunnypilot, NOT vendored like comma does.
checks += 1
if list((ROOT / "openpilot/selfdrive/modeld/models").glob("big_driving_tinygrad.pkl.chunk*")):
    failures.append(
        "[conflict] vendored big_driving_tinygrad.pkl chunks found; sunnypilot fetches the "
        "USB-GPU model at runtime via fetcher.py - vendoring ~2.1GB fights the model manager"
    )

# --- E. Tesla HW1 ---
TV = "opendbc_repo/opendbc/car/tesla/values.py"
for needle, why in [
    ("TESLA_MODEL_S_HW1", "Model S HW1 platform"),
    ("TESLA_MODEL_X_HW1", "Model X HW1 platform"),
    ("FLAG_HW1", "HW1 feature flag"),
    ("LEGACY_CARS", "legacy safety grouping"),
]:
    need_text(TV, needle, why)
need_file("opendbc_repo/opendbc/car/tesla/teslacan_legacy.py", "HW1 CAN builder")
need_file("opendbc_repo/opendbc/car/tesla/carcontroller.py", "Tesla actuation")
need_file("opendbc_repo/opendbc/car/tesla/radar_interface.py", "HW1 radar")
need_file("opendbc_repo/opendbc/safety/modes/tesla_legacy.h", "HW1 safety hooks (safety lives opendbc-side; panda ignition moved to opendbc)")
need_file("opendbc_repo/opendbc/dbc/tesla_can.dbc", "HW1 CAN DBC")

print(f"verify_hw1_chestnut: {checks} checks, {len(failures)} failure(s), {len(skipped)} skipped\n")
for sk in skipped:
    print("  SKIP " + sk)
if skipped:
    print()
if failures:
    for f in failures:
        print("  FAIL " + f)
    print("\nRESULT: REGRESSION - a sunnypilot / HW1 / Chestnut integration point was lost.")
    sys.exit(1)
print("RESULT: OK - sunnypilot features, Tesla HW1 and Chestnut eGPU support all intact.")
