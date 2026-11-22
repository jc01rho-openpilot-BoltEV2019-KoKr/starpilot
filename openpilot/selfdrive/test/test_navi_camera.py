import importlib
import json
import socket
import sys
import threading
import time
import types
from types import SimpleNamespace

import pytest

from openpilot.selfdrive.navi_camera import (
  INT16_MAX,
  RearCameraMotion,
  camera_distance,
  traffic_signal_display,
  traffic_signal_fields,
)

RSL_MODULE = "openpilot.selfdrive.road_speed_limiter"


class TestCameraDistance:
  def test_legacy_camera_counts_down_and_clamps_at_zero(self):
    assert camera_distance(1, 300, None, 50) == (250, False)
    assert camera_distance(1, 300, None, 400) == (0, False)
    assert camera_distance(1, 0, None, 10) == (0, False)

  def test_legacy_camera_clamps_to_int16(self):
    assert camera_distance(1, 100000, None, 0) == (INT16_MAX, False)

  def test_rear_camera_before_pass(self):
    assert camera_distance(86, 100, 200, 30) == (70, False)

  def test_rear_camera_counts_down_hold_zone_after_pass(self):
    assert camera_distance(86, 100, 200, 150) == (150, True)

  def test_rear_camera_expires_after_hold_zone(self):
    assert camera_distance(86, 100, 200, 350) == (0, False)

  def test_rear_camera_rejects_invalid_samples(self):
    assert camera_distance(86, 100, 0, 10) == (0, False)
    assert camera_distance(86, float("nan"), 200, 10) == (0, False)
    assert camera_distance(86, "x", 200, 10) == (0, False)

  def test_rear_camera_without_hold_uses_legacy_contract(self):
    assert camera_distance(86, 100, None, 30) == (70, False)


class TestRearCameraMotion:
  def test_heartbeats_integrate_travel_and_new_sample_resets(self):
    motion = RearCameraMotion()
    assert motion.update(86, 100, 200, "a", 10.0, 10.0, 0.0, 10.0) == (100, False)
    assert motion.update(86, 100, 200, "a", 10.0, 15.0, 0.0, 10.0) == (50, False)
    assert motion.update(86, 100, 200, "a", 10.0, 25.0, 0.0, 10.0) == (150, True)
    assert motion.update(86, 100, 200, "b", 25.0, 25.0, 1.0, 10.0) == (90, False)

  def test_legacy_camera_uses_packet_age(self):
    motion = RearCameraMotion()
    assert motion.update(1, 300, None, None, 10.0, 12.0, 0.0, 10.0) == (280, False)

  def test_invalid_rear_sample_clears_tracking(self):
    motion = RearCameraMotion()
    assert motion.update(86, 100, 200, "a", 10.0, 10.0, -1.0, 10.0) == (0, False)
    assert motion.key is None


class TestTrafficSignal:
  def test_missing_payload_defaults_to_off(self):
    fields = traffic_signal_fields(None)
    assert not any(fields[k] for k in ("isGreenLightOn", "isLeftLightOn", "isRedLightOn"))
    assert all(fields[k] == 0 for k in ("greenLightRemainTime", "leftLightRemainTime", "redLightRemainTime", "distance"))

  def test_payload_is_coerced_to_schema_ranges(self):
    fields = traffic_signal_fields({"isRedLightOn": 1, "redLightRemainTime": 99999, "distance": "x", "leftLightRemainTime": 12.7})
    assert fields["isRedLightOn"] is True
    assert fields["redLightRemainTime"] == INT16_MAX
    assert fields["distance"] == 0
    assert fields["leftLightRemainTime"] == 12

  def test_display_hides_when_nothing_reported(self):
    ts = SimpleNamespace(**traffic_signal_fields({}))
    assert traffic_signal_display(ts) is None

  def test_display_lists_lights_in_order(self):
    ts = SimpleNamespace(**traffic_signal_fields({"isRedLightOn": True, "redLightRemainTime": 12, "greenLightRemainTime": 3}))
    assert traffic_signal_display(ts) == [("red", True, 12), ("left", False, 0), ("green", False, 3)]


class TestNaviDataSchema:
  def test_new_fields_round_trip(self):
    pytest.importorskip("capnp")
    from openpilot.cereal import log

    fields = log.NaviData.schema.fields
    assert fields["ts"].proto.ordinal.explicit == 14
    assert fields["camRearPassed"].proto.ordinal.explicit == 15

    event = log.Event.new_message()
    navi = event.init("naviData")
    navi.camLimitSpeedLeftDist = 150
    navi.camRearPassed = True
    navi.ts = traffic_signal_fields({"isLeftLightOn": True, "leftLightRemainTime": 7, "distance": 120})

    with log.Event.from_bytes(event.to_bytes()) as decoded:
      assert decoded.which() == "naviData"
      assert decoded.naviData.camRearPassed
      assert decoded.naviData.camLimitSpeedLeftDist == 150
      assert decoded.naviData.ts.isLeftLightOn
      assert decoded.naviData.ts.leftLightRemainTime == 7
      assert decoded.naviData.ts.distance == 120


@pytest.fixture
def road_speed_limiter(monkeypatch, request):
  pytest.importorskip("numpy")
  stubs = {
    "openpilot.cereal.messaging": {},
    "openpilot.common.realtime": {"DT_CTRL": 0.01},
    "openpilot.common.swaglog": {"cloudlog": SimpleNamespace(info=lambda *a, **k: None, error=lambda *a, **k: None)},
  }
  for name, attrs in stubs.items():
    try:
      importlib.import_module(name)
    except ImportError:
      module = types.ModuleType(name)
      module.__dict__.update(attrs)
      monkeypatch.setitem(sys.modules, name, module)
  sys.modules.pop(RSL_MODULE, None)
  request.addfinalizer(lambda: sys.modules.pop(RSL_MODULE, None))
  return importlib.import_module(RSL_MODULE)


def _limiter(module, **navi):
  limiter = module.SpeedLimiter.__new__(module.SpeedLimiter)
  limiter.slowing_down = False
  limiter.started_dist = 0
  limiter.last_limit_speed_left_dist = 0
  limiter.rear_passed = False
  limiter.logMonoTime = time.monotonic_ns()
  limiter.recv = lambda: None
  defaults = {"isHighway": False, "camType": 1, "camLimitSpeedLeftDist": 0, "camLimitSpeed": 0, "camRearPassed": False,
                  "sectionLimitSpeed": 0, "sectionLeftDist": 0, "sectionAvgSpeed": 0, "sectionAdjustSpeed": False}
  limiter.naviData = SimpleNamespace(**{**defaults, **navi})
  return limiter


def _server(module):
  server = module.NaviServer.__new__(module.NaviServer)
  server.json_road_limit = None
  server.json_traffic_signal = None
  server.active = 0
  server.last_updated = 0.0
  server.last_updated_active = 0.0
  server.lock = threading.Lock()
  server.remote_addr = None
  server.remote_gps_addr = None
  server.seen_receive_ports = set()
  return server


class TestNaviServerPorts:
  def test_listens_on_legacy_and_current_ports(self, road_speed_limiter):
    assert road_speed_limiter.Port.RECEIVE_PORTS == (2843, 3843)

  def test_udp_recv_accepts_packets_on_every_socket(self, road_speed_limiter):
    server = _server(road_speed_limiter)
    socks = []
    try:
      for _ in range(2):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(("127.0.0.1", 0))
        sock.setblocking(False)
        socks.append(sock)
      with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sender:
        for limit, sock in zip((50, 80), socks, strict=True):
          sender.sendto(json.dumps({"active": 1, "road_limit": {"road_limit_speed": limit}}).encode(), sock.getsockname())
          assert server.udp_recv(socks)
          assert server.get_limit_val("road_limit_speed") == limit
      assert server.seen_receive_ports == {sock.getsockname()[1] for sock in socks}
      assert server.active == 1
    finally:
      for sock in socks:
        sock.close()


class TestSpeedLimiter:
  def test_rear_camera_hold_keeps_limit_then_releases(self, road_speed_limiter):
    limiter = _limiter(road_speed_limiter, camType=86, camLimitSpeedLeftDist=150, camLimitSpeed=60, camRearPassed=True)
    cs = SimpleNamespace(vEgo=20.0)

    apply_speed, limit, left_dist, first_started, _ = limiter.get_max_speed(cs, 100.0)
    assert (apply_speed, limit, left_dist, first_started) == (60.0, 60, 150, True)

    limiter.naviData.camRearPassed = False
    limiter.naviData.camLimitSpeedLeftDist = 0
    assert limiter.get_max_speed(cs, 100.0)[0] == 0
    assert not limiter.slowing_down

  @pytest.mark.parametrize("cam_type, expected", [(86, 90.0), (1, 60.0)])
  def test_section_zone_smooth_approach_only_for_listed_cameras(self, road_speed_limiter, cam_type, expected):
    limiter = _limiter(road_speed_limiter, camType=cam_type, camLimitSpeedLeftDist=300, camLimitSpeed=60, sectionLeftDist=500)
    cs = SimpleNamespace(vEgo=25.0)
    assert limiter.get_max_speed(cs, 100.0)[0] == pytest.approx(expected)

  def test_stale_data_clears_rear_state(self, road_speed_limiter):
    limiter = _limiter(road_speed_limiter, camType=86, camLimitSpeedLeftDist=150, camLimitSpeed=60, camRearPassed=True)
    limiter.get_max_speed(SimpleNamespace(vEgo=20.0), 100.0)
    limiter.logMonoTime = time.monotonic_ns() - int(5e9)
    assert limiter.get_max_speed(SimpleNamespace(vEgo=20.0), 100.0)[0] == 0
    assert not limiter.rear_passed and not limiter.slowing_down


def _sm(**navi):
  defaults = {"active": 1, "isHighway": False, "camType": 1, "camLimitSpeed": 0, "camLimitSpeedLeftDist": 0,
                  "sectionLimitSpeed": 0, "sectionLeftDist": 0, "camRearPassed": False}
  return {"naviData": SimpleNamespace(**{**defaults, **navi})}


class TestNdaCameraWarning:
  @pytest.fixture
  def events(self):
    return pytest.importorskip("openpilot.selfdrive.selfdrived.events")

  def test_context_prefers_valid_camera_then_section(self, events):
    assert events.get_nda_camera_warning_context(_sm(camLimitSpeed=60, camLimitSpeedLeftDist=300,
                                                     sectionLimitSpeed=80, sectionLeftDist=900)) == (60.0, 300.0)
    assert events.get_nda_camera_warning_context(_sm(sectionLimitSpeed=80, sectionLeftDist=900)) == (80.0, 900.0)

  def test_context_ignores_inactive_out_of_range_and_distance_only_data(self, events):
    assert events.get_nda_camera_warning_context(_sm(active=0, camLimitSpeed=60, camLimitSpeedLeftDist=300)) == (0.0, 0.0)
    assert events.get_nda_camera_warning_context(_sm(camLimitSpeed=110, camLimitSpeedLeftDist=300)) == (0.0, 0.0)
    assert events.get_nda_camera_warning_context(_sm(camLimitSpeedLeftDist=300)) == (0.0, 0.0)

  def test_policy_escalates_to_critical_near_limit(self, events):
    AlertStatus = events.AlertStatus
    assert events.get_nda_camera_warning_policy(30.0, 60.0)[3] == AlertStatus.userPrompt
    ratio, interval, duration, status = events.get_nda_camera_warning_policy(90.0, 60.0)
    assert status == AlertStatus.critical
    assert ratio == pytest.approx(1.5)
    assert interval == pytest.approx(0.8)
    assert duration == pytest.approx(0.32)

  def test_critical_alert_plays_speed_down(self, events):
    sm = _sm(camLimitSpeed=60, camLimitSpeedLeftDist=150, camRearPassed=True)
    alert = events.nda_camera_warning_alert(None, SimpleNamespace(vEgo=25.0), sm, True, 0, None)
    assert alert.audible_alert == events.AudibleAlert.speedDown
    assert alert.alert_text_1.startswith("60 kph") and alert.alert_text_1.endswith("hold 150 m")

  def test_event_is_registered_as_warning(self, events):
    assert events.ET.WARNING in events.EVENTS[events.EventName.ndaCameraWarn]


def test_speed_down_sound_is_bundled():
  soundd = pytest.importorskip("openpilot.selfdrive.ui.soundd")
  from pathlib import Path
  from openpilot.starpilot.audio.sound_pack import read_wav

  file_name, loops, _ = soundd.sound_list[soundd.AudibleAlert.speedDown]
  assert loops == 3
  assert soundd.ALERT_VOLUME_KEYS[soundd.AudibleAlert.speedDown] == "PromptVolume"
  assert len(read_wav(Path(soundd.__file__).resolve().parents[1] / "assets/sounds" / file_name)) > 0
