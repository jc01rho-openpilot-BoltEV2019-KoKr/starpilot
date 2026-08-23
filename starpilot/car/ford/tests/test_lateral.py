import sys
from types import SimpleNamespace

import pytest

from ..lateral import HANDOFF_PAUSE_FRAMES, FordLateralController, HumanTurnDetector


class FakeSubMaster(dict):
  def __init__(self, services):
    super().__init__({"liveDelay": SimpleNamespace(lateralDelay=0.12)})
    self.updated = dict.fromkeys(services, False)

  def update(self, timeout):
    pass


@pytest.fixture
def controller(monkeypatch):
  messaging = SimpleNamespace(SubMaster=FakeSubMaster)
  monkeypatch.setitem(sys.modules, "cereal.messaging", messaging)
  CP = SimpleNamespace(flags=0, carFingerprint="FORD_EDGE_MK2")
  controller = FordLateralController(CP)
  controller.sm = FakeSubMaster(["modelV2", "liveDelay"])
  return controller


def car_state(speed=15.0, curvature=0.0, steering_pressed=False, steering_angle=0.0):
  return SimpleNamespace(out=SimpleNamespace(
    vEgoRaw=speed,
    yawRate=-curvature * speed,
    steeringPressed=steering_pressed,
    steeringAngleDeg=steering_angle,
  ))


def test_human_turn_requires_sustained_input():
  detector = HumanTurnDetector()
  assert not detector.update(True, True, 0.0)
  for _ in range(29):
    assert not detector.update(True, True, 50.0)
  assert detector.update(True, True, 50.0)
  assert not detector.update(True, False, 50.0)


def test_curvature_strategy_uses_polynomial_signals(controller):
  result = controller.update_curvature(
    SimpleNamespace(latActive=True), car_state(), SimpleNamespace(curvature=0.001))
  assert result.active
  assert 0.0 < result.curvature <= 0.001
  assert result.ramp_type == 2


def test_curvature_lookahead_tracks_bounded_live_delay(controller):
  controller.sm["liveDelay"].lateralDelay = 0.38
  assert controller._curvature_lookahead() == pytest.approx(0.38)

  controller.sm["liveDelay"].lateralDelay = 0.1
  assert controller._curvature_lookahead() == pytest.approx(0.2)

  controller.sm["liveDelay"].lateralDelay = 0.6
  assert controller._curvature_lookahead() == pytest.approx(0.4)


def test_curvature_strategy_uses_learned_lookahead(controller, monkeypatch):
  controller.sm["liveDelay"].lateralDelay = 0.38
  lookaheads = []
  monkeypatch.setattr(controller, "_predicted_curvature",
                      lambda _v_ego, lookahead: lookaheads.append(lookahead) or 0.0)

  controller.update_curvature(SimpleNamespace(latActive=True), car_state(),
                              SimpleNamespace(curvature=0.001))

  assert lookaheads == [pytest.approx(0.38)]


def test_lane_change_accepts_capnp_enum_wrappers(controller):
  controller.model = SimpleNamespace(meta=SimpleNamespace(
    laneChangeState=SimpleNamespace(raw=2),
    laneChangeDirection=SimpleNamespace(raw=1),
  ))
  assert controller._lane_change() == (True, 1)


def test_angle_strategy_uses_path_angle_and_shadow(controller):
  result = controller.update_angle(
    SimpleNamespace(latActive=True), car_state(curvature=0.001), SimpleNamespace(curvature=0.001))
  assert result.active
  assert result.curvature == 0.0
  assert result.path_angle > 0.0
  assert result.shadow_curvature == pytest.approx(0.0005)


def test_manual_turn_releases_lateral(controller):
  controller.human_turn_enabled = True
  CC = SimpleNamespace(latActive=True)
  CS = car_state(steering_pressed=True, steering_angle=50.0)
  actuators = SimpleNamespace(curvature=0.001)
  for _ in range(61):
    result = controller.update_angle(CC, CS, actuators)
  assert not result.active
  assert result.path_angle == 0.0


def test_curvature_control_stays_active_during_driver_correction(controller):
  controller.human_turn_enabled = True
  CC = SimpleNamespace(latActive=True)
  actuators = SimpleNamespace(curvature=0.001)

  for _ in range(20):
    result = controller.update_curvature(
      CC, car_state(steering_pressed=True, steering_angle=10.0), actuators)
    assert result.active


def test_curvature_manual_turn_keeps_session_active_with_neutral_command(controller):
  controller.human_turn_enabled = True
  CC = SimpleNamespace(latActive=True)
  actuators = SimpleNamespace(curvature=0.001)

  controller.update_curvature(
    CC, car_state(steering_pressed=True, steering_angle=0.0), actuators)
  for _ in range(30):
    result = controller.update_curvature(
      CC, car_state(steering_pressed=True, steering_angle=50.0), actuators)

  assert result.active
  assert result.curvature == 0.0
  assert result.path_angle == 0.0


def test_angle_control_pulses_inactive_after_sustained_driver_correction(controller):
  controller.human_turn_enabled = True
  CC = SimpleNamespace(latActive=True)
  actuators = SimpleNamespace(curvature=0.001)

  for _ in range(10):
    assert controller.update_angle(
      CC, car_state(steering_pressed=True, steering_angle=10.0), actuators).active

  for _ in range(HANDOFF_PAUSE_FRAMES):
    assert not controller.update_angle(CC, car_state(), actuators).active

  assert controller.update_angle(CC, car_state(), actuators).active


def test_short_driver_correction_does_not_pause_angle_control(controller):
  controller.human_turn_enabled = True
  CC = SimpleNamespace(latActive=True)
  actuators = SimpleNamespace(curvature=0.001)

  for _ in range(9):
    assert controller.update_angle(
      CC, car_state(steering_pressed=True, steering_angle=10.0), actuators).active

  assert controller.update_angle(CC, car_state(), actuators).active


def test_angle_control_recovers_from_bounded_tracking_stall(controller):
  controller.human_turn_enabled = True
  controller.angle_blend = 0.0
  CC = SimpleNamespace(latActive=True)
  CS = car_state(speed=15.0, curvature=0.0)
  actuators = SimpleNamespace(curvature=0.01)

  for _ in range(10):
    assert controller.update_angle(CC, CS, actuators).active

  for _ in range(HANDOFF_PAUSE_FRAMES):
    assert not controller.update_angle(CC, CS, actuators).active
