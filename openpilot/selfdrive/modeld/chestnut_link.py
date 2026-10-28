"""Raw-USB probe of the chestnut ASM2464 bridge, used by modeld before tinygrad opens Device["AMD"].

sunnypilot's hardwared also publishes `chestnutState` (voltage / PCIe LTSSM) for the
offroad alerts. This probe does not publish that service: a second publisher would
raise MultiplePublishersError, and the message does not exist yet at the moment
modeld decides whether to attempt the big model.

It only reads the link, and sends PCIe power-on at most once, and only while the
link is down. Re-sending power-on on every poll (what flash.link_up() does) a few
seconds before tinygrad opens the GPU hangs the in-car weight upload.
"""
import struct
import time

import usb1

from openpilot.common.hardware.usb import CHESTNUT_PCIE_READY, CHESTNUT_USB_IDS
from openpilot.selfdrive.modeld.helpers import chestnut_ready

PROBE_TIMEOUT_S = 3.0
PROBE_INTERVAL_S = 0.2
STABLE_READS = 3
LTSSM_REG = 0xB450


class ChestnutUsb:
  """Pre-bootstrap ASM2464 reader. The Device["AMD"] path does not exist yet."""

  def __init__(self):
    self._context = None
    self._handle = None

  def close(self) -> None:
    for obj in (self._handle, self._context):
      if obj is not None:
        try:
          obj.close()
        except Exception:
          pass
    self._handle = self._context = None

  def _connect(self) -> None:
    self._context = usb1.USBContext()
    for vendor_id, product_id in CHESTNUT_USB_IDS:
      if (handle := self._context.openByVendorIDAndProductID(vendor_id, product_id, skip_on_error=True)) is not None:
        self._handle = handle
        return
    self.close()

  def _control_read(self, request: int, value: int, length: int) -> bytes:
    if self._handle is None:
      self._connect()
    if self._handle is None:
      raise usb1.USBErrorNoDevice
    try:
      return bytes(self._handle.controlRead(0xC0, request, value, 0, length, timeout=100))
    except usb1.USBError:
      self.close()
      raise

  def read_ina(self) -> tuple[int, int, bool]:
    return struct.unpack('<Hh?', self._control_read(0xC0, 0, 5))

  def read_ltssm(self) -> int:
    return self._control_read(0xE4, LTSSM_REG, 1)[0]

  def power_on_pcie(self) -> None:
    # tinygrad's CustomASM24Controller.set_pcie_power(True)
    if self._handle is None:
      self._connect()
    if self._handle is None:
      raise usb1.USBErrorNoDevice
    self._handle.controlWrite(0x40, 0xF3, 1, 0, b"", timeout=10000)


class _Reading:
  """Duck-types the fields chestnut_ready() reads off a chestnutState capnp reader."""

  def __init__(self, supplyVoltage: int, supplyCurrent: int, supplyFault: bool, pcieLtssm: int):
    self.supplyVoltage = supplyVoltage
    self.supplyCurrent = supplyCurrent
    self.supplyFault = supplyFault
    self.pcieLtssm = pcieLtssm


def wait_for_stable_chestnut(timeout: float = PROBE_TIMEOUT_S, interval: float = PROBE_INTERVAL_S,
                              stable_reads: int = STABLE_READS) -> bool:
  """Poll hardware until chestnut_ready() holds for `stable_reads` samples, or timeout.

  A read exception resets the streak instead of raising. PCIe power-on is sent at
  most once, and only when the link is down.
  """
  asm = ChestnutUsb()
  consecutive = 0
  powered_on = False
  deadline = time.monotonic() + timeout
  try:
    while time.monotonic() < deadline:
      try:
        ltssm = asm.read_ltssm()
        if ltssm != CHESTNUT_PCIE_READY and not powered_on:
          asm.power_on_pcie()
          powered_on = True
          ltssm = asm.read_ltssm()
        voltage, current, fault = asm.read_ina()
      except Exception:
        consecutive = 0
      else:
        reading = _Reading(voltage, current, fault, ltssm)
        consecutive = consecutive + 1 if chestnut_ready(reading) else 0
        if consecutive >= stable_reads:
          return True
      time.sleep(interval)
  finally:
    asm.close()
  return False
