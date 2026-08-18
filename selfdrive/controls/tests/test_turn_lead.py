from cereal import car

import pytest

from openpilot.selfdrive.controls.controlsd import get_control_lateral_smooth_seconds, turn_lead_allowed


LateralControlMode = car.CarControl.Actuators.LateralControlMode


def test_turn_lead_is_suppressed_only_during_applied_angle_control():
  assert not turn_lead_allowed("rivian", LateralControlMode.angle)
  assert turn_lead_allowed("rivian", LateralControlMode.torque)
  assert turn_lead_allowed("rivian", LateralControlMode.torqueRecovering)
  assert turn_lead_allowed("rivian", LateralControlMode.inactive)
  assert turn_lead_allowed("ford", LateralControlMode.angle)


@pytest.mark.parametrize("v_ego", [0.0, 5.0, 30.0])
def test_non_rivian_control_smoothing_matches_starpilot(v_ego):
  assert get_control_lateral_smooth_seconds("toyota", v_ego, 0.0) == 0.1


@pytest.mark.parametrize(("v_ego", "expected"), [
  (0.0, 0.4),
  (5.0, 0.2),
  (30.0, 0.0),
])
def test_rivian_control_smoothing_remains_speed_scheduled(v_ego, expected):
  assert get_control_lateral_smooth_seconds("rivian", v_ego, 0.4) == pytest.approx(expected)
