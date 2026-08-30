import json
import os
import socketserver
import threading
import time

from typing import Any

from openpilot.common.params import Params
from openpilot.common.swaglog import cloudlog
from openpilot.starpilot.system.bluetooth.bluez import BlueZClient
from openpilot.starpilot.system.bluetooth.protocol import BLUETOOTH_SOCKET_PATH
from openpilot.starpilot.system.bluetooth.radio import BluetoothRadio


OFFROAD_COMMANDS = {"set_power", "start_scan", "stop_scan", "pair", "forget", "test_audio", "pairing_response"}
SCAN_DURATION = 20.0
AUDIO_TEST_START_DELAY = 3.0
AUDIO_TEST_HOLD_TIME = 3.0


class BluetoothController:
  def __init__(self, params: Params | None = None, bluez_factory=BlueZClient, radio: BluetoothRadio | None = None,
               params_memory: Params | None = None, sleep=time.sleep):
    self.params = params or Params()
    self.params_memory = params_memory or Params(memory=True)
    self._bluez_factory = bluez_factory
    self._radio = radio or BluetoothRadio()
    self._lock = threading.RLock()
    self._bluez: BlueZClient | None = None
    self._pairing_address = ""
    self._pairing_error = ""
    self._last_reconnect = 0.0
    self._scan_deadline = 0.0
    self._audio_test_deadline = 0.0
    self._sleep = sleep
    self.params.remove("BluetoothAudioTestActive")
    self.params_memory.remove("TestAlert")

  def close(self) -> None:
    self.params.remove("BluetoothAudioTestActive")
    self.params_memory.remove("TestAlert")
    with self._lock:
      if self._bluez is not None:
        self._bluez.close()
        self._bluez = None
    if not self.params.get_bool("BluetoothEnabled"):
      try:
        self._radio.stop()
      except Exception:
        pass

  def _client(self) -> BlueZClient:
    with self._lock:
      if self._bluez is None:
        if not self.params.get_bool("BluetoothEnabled"):
          raise RuntimeError("Bluetooth is disabled")
        self._radio.start()
        self._bluez = self._bluez_factory()
        self._bluez.set_powered(True)
      return self._bluez

  def _reset_client(self) -> None:
    with self._lock:
      if self._bluez is not None:
        try:
          self._bluez.close()
        except Exception:
          pass
        self._bluez = None

  def _offroad(self) -> bool:
    return self.params.get_bool("IsOffroad")

  def status(self) -> dict[str, Any]:
    result = {
      "available": self._radio.available,
      "enabled": self.params.get_bool("BluetoothEnabled"),
      "powered": False,
      "discovering": False,
      "offroad": self._offroad(),
      "selected_audio": self.params.get("BluetoothAudioAddress", encoding="utf-8") or "",
      "devices": [],
      "prompt": None,
      "error": self._pairing_error,
      "pairing_address": self._pairing_address,
    }
    if not result["enabled"]:
      return result
    try:
      result.update(self._client().status())
      result["available"] = True
      prompt = result.get("prompt")
      if prompt is not None and self._pairing_address:
        prompt["address"] = self._pairing_address
        device = next((item for item in result["devices"] if item["address"].upper() == self._pairing_address.upper()), None)
        prompt["name"] = device["name"] if device else self._pairing_address
    except Exception as error:
      result["error"] = str(error)
      self._reset_client()
    return result

  def _require_offroad(self, command: str) -> None:
    if command in OFFROAD_COMMANDS and not self._offroad():
      raise RuntimeError("Bluetooth settings can only be changed offroad")

  def _pair_worker(self, address: str) -> None:
    try:
      self._client().pair(address)
      status = self._client().device_for_address(address)
      if status.get("audio") and not self.params.get("BluetoothAudioAddress", encoding="utf-8"):
        self.params.put("BluetoothAudioAddress", address)
      self._pairing_error = ""
    except Exception as error:
      self._pairing_error = str(error)
      cloudlog.exception("Bluetooth pairing failed")
    finally:
      self._pairing_address = ""

  def _test_audio_worker(self, address: str, deadline: float) -> None:
    try:
      self._sleep(max(0.0, deadline - time.monotonic()))
      if (not self._offroad() or not self.params.get_bool("BluetoothEnabled") or
          (self.params.get("BluetoothAudioAddress", encoding="utf-8") or "").upper() != address.upper()):
        return
      device = self._client().device_for_address(address)
      if not device.get("connected"):
        return
      self.params_memory.put("TestAlert", "engage")
      self._sleep(AUDIO_TEST_HOLD_TIME)
    except Exception:
      cloudlog.exception("Bluetooth audio test failed")
    finally:
      self._audio_test_deadline = 0.0
      self.params.remove("BluetoothAudioTestActive")

  def handle(self, request: dict[str, Any]) -> dict[str, Any]:
    command = str(request.get("command", ""))
    if command == "status":
      return {"status": self.status()}
    self._require_offroad(command)

    address = str(request.get("address", ""))
    if command == "set_power":
      enabled = bool(request.get("enabled", False))
      if enabled:
        try:
          self.params.put_bool("BluetoothEnabled", True)
          self._client()
        except Exception:
          self.params.put_bool("BluetoothEnabled", False)
          self._reset_client()
          try:
            self._radio.stop()
          except Exception:
            pass
          raise
      else:
        try:
          with self._lock:
            client = self._bluez
          if client is not None:
            client.set_powered(False)
        finally:
          self._reset_client()
          self._radio.stop()
          self.params.remove("BluetoothAudioAddress")
          self.params.put_bool("BluetoothEnabled", False)
          self._scan_deadline = 0.0
    elif command == "start_scan":
      if not self.params.get_bool("BluetoothEnabled"):
        raise RuntimeError("Enable Bluetooth before scanning")
      self._client().start_discovery()
      self._scan_deadline = time.monotonic() + SCAN_DURATION
    elif command == "stop_scan":
      self._client().stop_discovery()
      self._scan_deadline = 0.0
    elif command == "pair":
      if self._pairing_address:
        raise RuntimeError("Another Bluetooth device is already pairing")
      self._pairing_address = address
      self._pairing_error = ""
      threading.Thread(target=self._pair_worker, args=(address,), daemon=True).start()
    elif command == "connect":
      self._client().connect(address)
    elif command == "disconnect":
      self._client().disconnect(address)
    elif command == "forget":
      self._client().remove(address)
      if (self.params.get("BluetoothAudioAddress", encoding="utf-8") or "").upper() == address.upper():
        self.params.remove("BluetoothAudioAddress")
    elif command == "select_audio":
      if address:
        device = self._client().device_for_address(address)
        if not device.get("audio"):
          raise RuntimeError("Selected device does not support Bluetooth audio")
        self.params.put("BluetoothAudioAddress", address)
      else:
        self.params.remove("BluetoothAudioAddress")
    elif command == "test_audio":
      if self.params.get_bool("BluetoothAudioTestActive"):
        raise RuntimeError("Bluetooth audio test is already playing")
      device = self._client().device_for_address(address)
      if not device.get("audio"):
        raise RuntimeError("Selected device does not support Bluetooth audio")
      if not device.get("paired") or not device.get("connected"):
        raise RuntimeError("Connect the Bluetooth audio device before testing")
      self.params.put("BluetoothAudioAddress", address)
      self.params.put_bool("BluetoothAudioTestActive", True)
      deadline = time.monotonic() + AUDIO_TEST_START_DELAY
      self._audio_test_deadline = deadline
      threading.Thread(target=self._test_audio_worker, args=(address, deadline), daemon=True).start()
      return {"audio_test_delay_ms": max(0, round((deadline - time.monotonic()) * 1000))}
    elif command == "pairing_response":
      if not self._client().agent.respond(str(request.get("prompt_id", "")), bool(request.get("accepted", False)), str(request.get("value", ""))):
        raise RuntimeError("Pairing request is no longer active")
    else:
      raise RuntimeError(f"Unknown Bluetooth command: {command}")
    return {}

  def _maintain_scan(self, status: dict[str, Any], now: float) -> None:
    if not status["discovering"]:
      self._scan_deadline = 0.0
    elif not status["offroad"] or (self._scan_deadline and now >= self._scan_deadline):
      self._client().stop_discovery()
      self._scan_deadline = 0.0

  def maintain_connections(self) -> None:
    while True:
      time.sleep(2)
      if not self.params.get_bool("BluetoothEnabled"):
        continue
      try:
        status = self.status()
        if not status["available"] or not status["powered"]:
          continue
        now = time.monotonic()
        self._maintain_scan(status, now)
        if self._pairing_address or now - self._last_reconnect < 15:
          continue
        self._last_reconnect = now
        selected = str(status["selected_audio"])
        candidates = [device for device in status["devices"] if device["paired"] and device["trusted"] and not device["connected"]]
        candidates.sort(key=lambda device: device["address"].upper() != selected.upper())
        for device in candidates:
          if device["audio"] or device["controller"]:
            try:
              self._client().connect(device["address"])
            except Exception:
              cloudlog.warning(f"Bluetooth reconnect failed for {device['address']}")
      except Exception:
        cloudlog.exception("Bluetooth connection maintenance failed")


class BluetoothRequestHandler(socketserver.StreamRequestHandler):
  def handle(self) -> None:
    try:
      raw = self.rfile.readline(1024 * 1024)
      request = json.loads(raw)
      payload = self.server.controller.handle(request)
      response = {"ok": True, **payload}
    except Exception as error:
      response = {"ok": False, "error": str(error)}
    self.wfile.write(json.dumps(response, separators=(",", ":")).encode() + b"\n")


class BluetoothServer(socketserver.ThreadingUnixStreamServer):
  daemon_threads = True

  def __init__(self, socket_path: str, controller: BluetoothController):
    self.controller = controller
    super().__init__(socket_path, BluetoothRequestHandler)


def main() -> None:
  try:
    os.unlink(BLUETOOTH_SOCKET_PATH)
  except FileNotFoundError:
    pass
  controller = BluetoothController()
  threading.Thread(target=controller.maintain_connections, daemon=True).start()
  try:
    with BluetoothServer(BLUETOOTH_SOCKET_PATH, controller) as server:
      os.chmod(BLUETOOTH_SOCKET_PATH, 0o660)
      server.serve_forever()
  finally:
    controller.close()
    try:
      os.unlink(BLUETOOTH_SOCKET_PATH)
    except FileNotFoundError:
      pass


if __name__ == "__main__":
  main()
