import io
import threading
import time

import numpy as np
import pytest

from openpilot.starpilot.system.bluetooth.audio import BluetoothAudioSink
from openpilot.starpilot.system.bluetooth.bluez import PairingAgent
from openpilot.starpilot.system.bluetooth.daemon import BluetoothController
from openpilot.starpilot.system.bluetooth.protocol import A2DP_SINK_UUID, HID_UUID, BluetoothDevice, BluetoothStatus, device_capabilities, show_pairing_device


class FakeParams:
  def __init__(self, **values):
    self.values = values

  def get_bool(self, key):
    return bool(self.values.get(key, False))

  def get(self, key, encoding=None, **_kwargs):
    value = self.values.get(key)
    return value.decode(encoding) if encoding and isinstance(value, bytes) else value

  def put_bool(self, key, value):
    self.values[key] = value

  def put(self, key, value):
    self.values[key] = value

  def remove(self, key):
    self.values.pop(key, None)


class FakeAgent:
  def __init__(self):
    self.responses = []

  def respond(self, prompt_id, accepted, value):
    self.responses.append((prompt_id, accepted, value))
    return prompt_id == "prompt"


class FakeBlueZ:
  def __init__(self):
    self.agent = FakeAgent()
    self.powered = False
    self.discovering = False
    self.closed = False
    self.actions = []
    self.device = {
      "address": "00:11:22:33:44:55",
      "name": "Speaker",
      "paired": True,
      "trusted": True,
      "connected": False,
      "audio": True,
      "controller": False,
    }

  def close(self):
    self.closed = True

  def set_powered(self, powered):
    self.powered = powered

  def status(self):
    return {"powered": self.powered, "discovering": self.discovering, "devices": [dict(self.device)], "prompt": None}

  def start_discovery(self):
    self.discovering = True

  def stop_discovery(self):
    self.discovering = False

  def device_for_address(self, _address):
    return dict(self.device)

  def pair(self, address):
    self.actions.append(("pair", address))

  def connect(self, address):
    self.actions.append(("connect", address))

  def disconnect(self, address):
    self.actions.append(("disconnect", address))

  def remove(self, address):
    self.actions.append(("remove", address))


class FakeRadio:
  available = True
  ready = True

  def __init__(self):
    self.starts = 0
    self.stops = 0

  def start(self):
    self.starts += 1

  def stop(self):
    self.stops += 1


class FakeProcess:
  def __init__(self):
    self.stdin = io.BytesIO()
    self.stopped = False

  def poll(self):
    return 0 if self.stopped else None

  def terminate(self):
    self.stopped = True

  def wait(self, timeout=None):
    return 0

  def kill(self):
    self.stopped = True


def test_protocol_round_trip_and_capabilities():
  audio, controller = device_capabilities([A2DP_SINK_UUID, HID_UUID])
  assert audio and controller
  status = BluetoothStatus.from_dict({
    "available": True,
    "enabled": True,
    "devices": [{"address": "00:11:22:33:44:55", "name": "Combo", "uuids": [A2DP_SINK_UUID, HID_UUID], "audio": True, "controller": True}],
  })
  assert status.devices == (BluetoothDevice("00:11:22:33:44:55", "Combo", uuids=(A2DP_SINK_UUID, HID_UUID), audio=True, controller=True),)


def test_pairing_list_filters_anonymous_and_irrelevant_advertisements():
  assert not show_pairing_device("00:11:22:33:44:55", "00:11:22:33:44:55", False, False, False, False, False, False)
  assert not show_pairing_device("00:11:22:33:44:55", "Nearby sensor", False, False, False, False, False, False)
  assert show_pairing_device("00:11:22:33:44:55", "Media Remote", False, False, False, False, False, True)
  assert show_pairing_device("00:11:22:33:44:55", "Known device", True, True, False, False, False, False)


def test_pairing_agent_accept_reject_and_timeout():
  agent = PairingAgent()
  result = []
  worker = threading.Thread(target=lambda: result.append(agent.request("confirmation", "/device", "123456", timeout=1.0)))
  worker.start()
  deadline = time.monotonic() + 1.0
  while agent.prompt is None and time.monotonic() < deadline:
    time.sleep(0.01)
  assert agent.prompt is not None
  assert agent.respond(agent.prompt["id"], True)
  worker.join(timeout=1.0)
  assert result == [(True, "")]
  assert agent.request("pin", "/device", timeout=0.01) == (False, "")


def test_disabled_status_does_not_start_radio_or_bluez():
  params = FakeParams(IsOffroad=True, BluetoothEnabled=False)
  radio = FakeRadio()
  created = []
  controller = BluetoothController(params, lambda: created.append(FakeBlueZ()) or created[-1], radio)
  status = controller.status()
  assert status["available"] and not status["enabled"] and not status["powered"]
  assert radio.starts == 0 and created == []


def test_power_pair_audio_and_offroad_enforcement():
  params = FakeParams(IsOffroad=True, BluetoothEnabled=False)
  radio = FakeRadio()
  clients = []
  controller = BluetoothController(params, lambda: clients.append(FakeBlueZ()) or clients[-1], radio)
  controller.handle({"command": "set_power", "enabled": True})
  assert params.get_bool("BluetoothEnabled") and radio.starts == 1 and clients[0].powered
  controller.handle({"command": "select_audio", "address": "00:11:22:33:44:55"})
  assert params.get("BluetoothAudioAddress") == "00:11:22:33:44:55"
  controller.handle({"command": "select_audio", "address": ""})
  assert params.get("BluetoothAudioAddress") is None
  assert clients[0].actions == []
  params.values["IsOffroad"] = False
  with pytest.raises(RuntimeError, match="offroad"):
    controller.handle({"command": "start_scan"})
  controller.handle({"command": "connect", "address": "00:11:22:33:44:55"})
  assert clients[0].actions[-1] == ("connect", "00:11:22:33:44:55")
  params.values["IsOffroad"] = True
  controller.handle({"command": "set_power", "enabled": False})
  assert not params.get_bool("BluetoothEnabled") and radio.stops == 1 and clients[0].closed


def test_audio_uses_soundd_engage_alert_and_cleans_up():
  params = FakeParams(IsOffroad=True, BluetoothEnabled=True)
  params_memory = FakeParams()
  client = FakeBlueZ()
  client.device["connected"] = True
  controller = BluetoothController(params, lambda: client, FakeRadio(), params_memory, sleep=lambda _delay: None)

  result = controller.handle({"command": "test_audio", "address": client.device["address"]})
  deadline = time.monotonic() + 1.0
  while params.get_bool("BluetoothAudioTestActive") and time.monotonic() < deadline:
    time.sleep(0.01)

  assert params.get("BluetoothAudioAddress") == client.device["address"]
  assert 2500 <= result["audio_test_delay_ms"] <= 3000
  assert params_memory.get("TestAlert") == "engage"
  assert not params.get_bool("BluetoothAudioTestActive")


def test_audio_requires_connected_device_and_offroad():
  params = FakeParams(IsOffroad=True, BluetoothEnabled=True)
  client = FakeBlueZ()
  controller = BluetoothController(params, lambda: client, FakeRadio(), FakeParams())

  with pytest.raises(RuntimeError, match="Connect"):
    controller.handle({"command": "test_audio", "address": client.device["address"]})
  params.values["IsOffroad"] = False
  with pytest.raises(RuntimeError, match="offroad"):
    controller.handle({"command": "test_audio", "address": client.device["address"]})


def test_scan_stops_after_timeout():
  params = FakeParams(IsOffroad=True, BluetoothEnabled=True)
  client = FakeBlueZ()
  controller = BluetoothController(params, lambda: client, FakeRadio())
  controller.handle({"command": "start_scan"})
  assert client.discovering and controller._scan_deadline > time.monotonic()

  controller._maintain_scan(controller.status(), controller._scan_deadline)
  assert not client.discovering and controller._scan_deadline == 0.0


def test_audio_queue_is_nonblocking_and_falls_back():
  params = FakeParams(BluetoothEnabled=True, BluetoothAudioAddress="00:11:22:33:44:55")
  process = FakeProcess()
  sink = BluetoothAudioSink(params, popen_factory=lambda *_args, **_kwargs: process, start_thread=False)
  sink._aplay = "/usr/bin/aplay"
  sink._thread = threading.Thread(target=sink._run, daemon=True)
  sink._thread.start()
  samples = np.array([-1.0, 0.0, 1.0], dtype=np.float32)
  deadline = time.monotonic() + 1.0
  while not sink._address and time.monotonic() < deadline:
    time.sleep(0.01)
  assert not sink.submit(samples)
  deadline = time.monotonic() + 1.0
  while not sink.healthy and time.monotonic() < deadline:
    time.sleep(0.01)
  assert sink.healthy
  assert len(process.stdin.getvalue()) == 12
  assert sink.submit(samples)
  process.stopped = True
  assert not sink.healthy
  sink.close()


def test_full_audio_queue_immediately_restores_local_output():
  params = FakeParams(BluetoothEnabled=True, BluetoothAudioAddress="00:11:22:33:44:55")
  process = FakeProcess()
  sink = BluetoothAudioSink(params, start_thread=False)
  sink._aplay = "/usr/bin/aplay"
  sink._address = "00:11:22:33:44:55"
  sink._process = process
  sink._healthy = True
  sink._last_write = time.monotonic()
  samples = np.zeros(3, dtype=np.float32)

  assert sink.submit(samples)
  assert sink.submit(samples)
  assert sink.submit(samples)
  assert not sink.submit(samples)
  assert not sink.healthy


def test_audio_address_decodes_device_params_bytes():
  params = FakeParams(BluetoothEnabled=True, BluetoothAudioAddress=b"00:11:22:33:44:55")
  sink = BluetoothAudioSink(params, start_thread=False)
  assert sink.desired_address() == "00:11:22:33:44:55"
