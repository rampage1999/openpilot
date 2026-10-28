import os
from dataclasses import dataclass
from enum import StrEnum
from pathlib import Path

CHESTNUT_FW_VERSION = "8516b768"
CHESTNUT_USB_IDS = ((0xADD1, 0x0001), (0x3801, 0x0001))
CHESTNUT_ROM_USB_IDS = ((0x174C, 0x2464), (0x174C, 0x2463))
CHESTNUT_USB_PRODUCT = f"custom {CHESTNUT_FW_VERSION}-CLEAN"
USB_DEVICES_PATH = Path("/sys/bus/usb/devices")
TYPEC_CC_ORIENTATION_PATH = Path("/sys/class/power_supply/usb/typec_cc_orientation")
PRIMARY_USB_CONTROLLER = "a600000.ssusb"

# Shared readiness thresholds. status.py and the modeld probe both use these.
CHESTNUT_POWERED_VOLTAGE = 5000  # mV
CHESTNUT_PCIE_READY = 0x78       # ChestnutState.pcieLtssm "link up"
CHESTNUT_SLOW_USB_MBPS = 5000    # USB 3.0 5 Gbps; below this the link negotiated down


def is_chestnut_usb_id(vendor_id: int, product_id: int, include_bootloader: bool = False) -> bool:
  ids = CHESTNUT_USB_IDS + CHESTNUT_ROM_USB_IDS if include_bootloader else CHESTNUT_USB_IDS
  return (vendor_id, product_id) in ids


def decode_pcie_ltssm(value: int) -> str:
  """Human label for ChestnutState.pcieLtssm. Only 0x78 (link up) and 0x00 (down) are known."""
  if value == CHESTNUT_PCIE_READY:
    return f"Link Up (0x{value:02x})"
  if value == 0x00:
    return f"Down / Not Linked (0x{value:02x})"
  return f"Training / Unknown (0x{value:02x})"


class ChestnutHwState(StrEnum):
  ABSENT = "absent"
  BOOTLOADER = "bootloader"
  FIRMWARE_MISMATCH = "firmware_mismatch"
  UNCOMPILED = "uncompiled"
  NOT_READY_POWER = "not_ready_power"
  NOT_READY_PCIE = "not_ready_pcie"
  NOT_READY = "not_ready"
  DEGRADED_LINK = "degraded_link"
  READY = "ready"
  ACTIVE = "active"


CHESTNUT_STATE_LABELS: dict[ChestnutHwState, str] = {
  ChestnutHwState.ABSENT: "Not Detected",
  ChestnutHwState.BOOTLOADER: "Bootloader / Recovery Mode",
  ChestnutHwState.FIRMWARE_MISMATCH: "Firmware Mismatch",
  ChestnutHwState.UNCOMPILED: "Model Not Compiled",
  ChestnutHwState.NOT_READY_POWER: "Not Ready (Power)",
  ChestnutHwState.NOT_READY_PCIE: "Not Ready (PCIe)",
  ChestnutHwState.NOT_READY: "Not Ready",
  ChestnutHwState.DEGRADED_LINK: "Degraded USB Link",
  ChestnutHwState.READY: "Ready",
  ChestnutHwState.ACTIVE: "Active",
}

# A chestnut-sourced model can be selected in these states. DEGRADED_LINK is usable
# (the GPU is up) but the USB link negotiated below 5 Gbps.
CHESTNUT_USABLE_STATES = (ChestnutHwState.READY, ChestnutHwState.ACTIVE, ChestnutHwState.DEGRADED_LINK)


@dataclass
class ChestnutHardwareInfo:
  state: ChestnutHwState
  present: bool
  firmware_ok: bool
  pcie_link_up: bool | None
  powered: bool | None
  slow_usb: bool
  pcie_label: str


def get_chestnut_hardware_state(devices: list[dict], state, compiled: bool,
                                 active: bool = False) -> ChestnutHardwareInfo:
  """Lifecycle of the eGPU from unplugged through driving the big model.

  `state` is a cereal ChestnutState reader (pcieLtssm/supplyVoltage/supplyFault) or
  None. `devices` is get_usb_state()'s dicts. `compiled` is true when a big-model
  bundle or the vendored chestnut pkl is on disk.
  """
  bootloader_only = any(is_chestnut_usb_id(d["vendorId"], d["productId"], include_bootloader=True)
                        and not is_chestnut_usb_id(d["vendorId"], d["productId"]) for d in devices)
  app_devices = [d for d in devices if is_chestnut_usb_id(d["vendorId"], d["productId"])]

  if not app_devices and not bootloader_only:
    return ChestnutHardwareInfo(ChestnutHwState.ABSENT, False, False, None, None, False, "-")
  if bootloader_only and not app_devices:
    return ChestnutHardwareInfo(ChestnutHwState.BOOTLOADER, True, False, None, None, False, "-")

  device = next((d for d in app_devices if d["speedMbps"]), app_devices[0])
  firmware_ok = len(app_devices) == 1 and device["product"] == CHESTNUT_USB_PRODUCT
  slow_usb = len(app_devices) == 1 and device["speedMbps"] < CHESTNUT_SLOW_USB_MBPS

  if not firmware_ok:
    return ChestnutHardwareInfo(ChestnutHwState.FIRMWARE_MISMATCH, True, False, None, None, slow_usb, "-")
  if not compiled:
    return ChestnutHardwareInfo(ChestnutHwState.UNCOMPILED, True, True, None, None, slow_usb, "-")
  if state is None:
    return ChestnutHardwareInfo(ChestnutHwState.NOT_READY, True, True, None, None, slow_usb, "-")

  pcie_link_up = int(state.pcieLtssm) == CHESTNUT_PCIE_READY
  powered = state.supplyVoltage >= CHESTNUT_POWERED_VOLTAGE and not state.supplyFault
  pcie_label = decode_pcie_ltssm(int(state.pcieLtssm))

  if not powered and not pcie_link_up:
    hw_state = ChestnutHwState.NOT_READY
  elif not powered:
    hw_state = ChestnutHwState.NOT_READY_POWER
  elif not pcie_link_up:
    hw_state = ChestnutHwState.NOT_READY_PCIE
  elif slow_usb:
    hw_state = ChestnutHwState.DEGRADED_LINK
  else:
    hw_state = ChestnutHwState.ACTIVE if active else ChestnutHwState.READY

  return ChestnutHardwareInfo(hw_state, True, True, pcie_link_up, powered, slow_usb, pcie_label)


def get_usb_topology() -> set[str]:
  try:
    return set(os.listdir(USB_DEVICES_PATH))
  except OSError:
    return set()


def read(path: Path) -> str | None:
  try:
    return path.read_text().strip()
  except OSError:
    return None


def read_int(path: Path, base: int = 10) -> int:
  try:
    return int(path.read_text(), base)
  except (OSError, ValueError, TypeError):
    return 0


def cable_connected() -> bool:
  return read_int(TYPEC_CC_ORIENTATION_PATH) != 0


def usb_devices() -> list[Path]:
  try:
    devices = (d for d in USB_DEVICES_PATH.glob("*") if (d / "idVendor").exists())
    return sorted(devices, key=lambda p: p.name)
  except OSError:
    return []


def controller(device: Path) -> Path | None:
  try:
    return next((parent for parent in device.resolve().parents if parent.name.endswith(".ssusb")), None)
  except OSError:
    return None


def get_usb_state() -> list[dict]:
  devices = []
  typec_orientation = read_int(TYPEC_CC_ORIENTATION_PATH)
  for device in usb_devices():
    vendor_id = read_int(device / "idVendor", 16)
    product_id = read_int(device / "idProduct", 16)
    ctrl = controller(device)
    devices.append({
      "busnum": read_int(device / "busnum"),
      "devnum": read_int(device / "devnum"),
      "vendorId": vendor_id,
      "productId": product_id,
      "speedMbps": read_int(device / "speed"),
      "manufacturer": read(device / "manufacturer") or "",
      "product": read(device / "product") or "",
      "linkErrorCount": read_int(ctrl / "portli", 0) & 0xFFFF if ctrl is not None else 0,
      "usb3Lane": {1: "a", 2: "b"}.get(typec_orientation, "unknown") if ctrl is not None and ctrl.name == PRIMARY_USB_CONTROLLER else "unknown",
    })
  return devices


def set_usb_state(device_state, devices: list[dict]) -> None:
  entries = device_state.usbState.init('devices', len(devices))

  chestnut_present = False
  for entry, device in zip(entries, devices, strict=True):
    entry.busnum = device["busnum"]
    entry.devnum = device["devnum"]
    entry.vendorId = device["vendorId"]
    entry.productId = device["productId"]
    entry.speedMbps = device["speedMbps"]
    entry.manufacturer = device["manufacturer"]
    entry.product = device["product"]
    entry.linkErrorCount = device["linkErrorCount"]
    entry.usb3Lane = device.get("usb3Lane", "unknown")

    if is_chestnut_usb_id(entry.vendorId, entry.productId):
      chestnut_present = True

  device_state.chestnutPresent = chestnut_present
  device_state.usbState.connected = cable_connected()
