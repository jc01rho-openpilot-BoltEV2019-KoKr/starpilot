import json
import os
import socket
import time

from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any

from openpilot.common.params import Params


BLUETOOTH_SOCKET_PATH = "/tmp/starpilot-bluetooth.sock"
BLUETOOTH_RADIO_HELPER = "/usr/comma/bluetooth-radio"
A2DP_SINK_UUID = "0000110b-0000-1000-8000-00805f9b34fb"
HID_UUID = "00001124-0000-1000-8000-00805f9b34fb"
HOG_UUID = "00001812-0000-1000-8000-00805f9b34fb"
COMMAND_TIMEOUTS = {
  "set_power": 55.0,
  "start_scan": 20.0,
  "stop_scan": 20.0,
  "connect": 35.0,
  "disconnect": 20.0,
  "forget": 20.0,
  "test_audio": 10.0,
}


@dataclass(frozen=True)
class BluetoothDevice:
  address: str
  name: str
  paired: bool = False
  trusted: bool = False
  connected: bool = False
  blocked: bool = False
  rssi: int | None = None
  uuids: tuple[str, ...] = ()
  audio: bool = False
  controller: bool = False

  @classmethod
  def from_dict(cls, value: dict[str, Any]) -> "BluetoothDevice":
    return cls(
      address=str(value.get("address", "")),
      name=str(value.get("name", value.get("address", "Unknown device"))),
      paired=bool(value.get("paired", False)),
      trusted=bool(value.get("trusted", False)),
      connected=bool(value.get("connected", False)),
      blocked=bool(value.get("blocked", False)),
      rssi=int(value["rssi"]) if value.get("rssi") is not None else None,
      uuids=tuple(str(uuid).lower() for uuid in value.get("uuids", ())),
      audio=bool(value.get("audio", False)),
      controller=bool(value.get("controller", False)),
    )


@dataclass(frozen=True)
class BluetoothStatus:
  available: bool = False
  enabled: bool = False
  powered: bool = False
  discovering: bool = False
  offroad: bool = False
  selected_audio: str = ""
  pairing_address: str = ""
  devices: tuple[BluetoothDevice, ...] = ()
  prompt: dict[str, Any] | None = None
  error: str = ""

  @classmethod
  def from_dict(cls, value: dict[str, Any]) -> "BluetoothStatus":
    return cls(
      available=bool(value.get("available", False)),
      enabled=bool(value.get("enabled", False)),
      powered=bool(value.get("powered", False)),
      discovering=bool(value.get("discovering", False)),
      offroad=bool(value.get("offroad", False)),
      selected_audio=str(value.get("selected_audio", "")),
      pairing_address=str(value.get("pairing_address", "")),
      devices=tuple(BluetoothDevice.from_dict(device) for device in value.get("devices", ())),
      prompt=value.get("prompt"),
      error=str(value.get("error", "")),
    )


def device_capabilities(uuids: list[str] | tuple[str, ...], bluetooth_class: int = 0, icon: str = "") -> tuple[bool, bool]:
  normalized = {str(uuid).lower() for uuid in uuids}
  major_class = (int(bluetooth_class) >> 8) & 0x1F
  audio = A2DP_SINK_UUID in normalized or major_class == 0x04 or icon in {"audio-card", "audio-headphones", "audio-headset"}
  controller = HID_UUID in normalized or HOG_UUID in normalized or major_class == 0x05 or icon in {"input-gaming", "input-mouse", "input-keyboard"}
  return audio, controller


def show_pairing_device(address: str, name: str, paired: bool, trusted: bool, connected: bool, blocked: bool,
                        audio: bool, controller: bool) -> bool:
  known = paired or trusted or connected
  named = bool(name) and name not in {address, "Unknown device"}
  return known or (named and not blocked and (audio or controller))


class BluetoothClient:
  def __init__(self, socket_path: str = BLUETOOTH_SOCKET_PATH, timeout: float = 5.0):
    self.socket_path = socket_path
    self.timeout = timeout

  def call(self, command: str, **payload: Any) -> dict[str, Any]:
    request = json.dumps({"command": command, **payload}, separators=(",", ":")).encode() + b"\n"
    with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as sock:
      sock.settimeout(max(self.timeout, COMMAND_TIMEOUTS.get(command, 0.0)))
      sock.connect(self.socket_path)
      sock.sendall(request)
      response = bytearray()
      while not response.endswith(b"\n"):
        chunk = sock.recv(65536)
        if not chunk:
          break
        response.extend(chunk)

    if not response:
      raise RuntimeError("Bluetooth service returned no response")
    result = json.loads(response)
    if not result.get("ok", False):
      raise RuntimeError(str(result.get("error", "Bluetooth operation failed")))
    return result

  def status(self) -> BluetoothStatus:
    if os.getenv("SP_ALLOW_DESKTOP_FAKE_BLUETOOTH", "0") == "1" and not os.path.exists(self.socket_path):
      return BluetoothStatus(
        available=True,
        enabled=True,
        powered=True,
        discovering=False,
        offroad=True,
        devices=(
          BluetoothDevice("00:11:22:33:44:55", "Bluetooth Speaker", paired=True, connected=True, audio=True),
          BluetoothDevice("AA:BB:CC:DD:EE:FF", "Game Controller", controller=True, rssi=-48),
        ),
      )
    if not os.path.exists(self.socket_path):
      params = Params()
      return BluetoothStatus(
        available=Path(BLUETOOTH_RADIO_HELPER).is_file(),
        enabled=params.get_bool("BluetoothEnabled"),
        offroad=params.get_bool("IsOffroad"),
        selected_audio=params.get("BluetoothAudioAddress", encoding="utf-8") or "",
      )
    return BluetoothStatus.from_dict(self.call("status").get("status", {}))

  @staticmethod
  def serialize_status(status: BluetoothStatus) -> dict[str, Any]:
    return asdict(status)

  def set_power(self, enabled: bool) -> None:
    params = Params()
    bootstrap = enabled and not os.path.exists(self.socket_path)
    if bootstrap:
      params.put_bool("BluetoothEnabled", True)
      deadline = time.monotonic() + max(self.timeout, 10.0)
      while not os.path.exists(self.socket_path):
        if time.monotonic() >= deadline:
          params.put_bool("BluetoothEnabled", False)
          raise RuntimeError("Bluetooth service did not start")
        time.sleep(0.05)
    try:
      self.call("set_power", enabled=enabled)
    except Exception:
      if bootstrap:
        params.put_bool("BluetoothEnabled", False)
      raise

  def start_scan(self) -> None:
    self.call("start_scan")

  def stop_scan(self) -> None:
    self.call("stop_scan")

  def pair(self, address: str) -> None:
    self.call("pair", address=address)

  def connect(self, address: str) -> None:
    self.call("connect", address=address)

  def disconnect(self, address: str) -> None:
    self.call("disconnect", address=address)

  def forget(self, address: str) -> None:
    self.call("forget", address=address)

  def select_audio(self, address: str) -> None:
    self.call("select_audio", address=address)

  def test_audio(self, address: str) -> float:
    result = self.call("test_audio", address=address)
    return max(0.0, float(result.get("audio_test_delay_ms", 0)) / 1000.0)

  def respond(self, prompt_id: str, accepted: bool, value: str = "") -> None:
    self.call("pairing_response", prompt_id=prompt_id, accepted=accepted, value=value)
