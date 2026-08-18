import pytest

from openpilot.selfdrive.modeld.modeld import get_car_lateral_smooth_seconds, get_lateral_smooth_seconds


@pytest.mark.parametrize(("v_ego", "expected"), [
  (0.0, 0.4),
  (2.0, 0.4),
  (5.0, 0.2),
  (8.0, 0.0),
  (30.0, 0.0),
])
def test_lateral_smoothing_tapers_with_speed(v_ego, expected):
  assert get_lateral_smooth_seconds(v_ego, 0.4) == pytest.approx(expected)


@pytest.mark.parametrize("v_ego", [0.0, 5.0, 30.0])
def test_default_lateral_smoothing_is_disabled(v_ego):
  assert get_lateral_smooth_seconds(v_ego) == 0.0


@pytest.mark.parametrize("v_ego", [0.0, 5.0, 30.0])
def test_non_rivian_cars_keep_configured_starpilot_smoothing(v_ego):
  assert get_car_lateral_smooth_seconds("toyota", v_ego, 0.4) == 0.4


@pytest.mark.parametrize(("v_ego", "maximum", "expected"), [
  (0.0, 0.4, 0.4),
  (5.0, 0.4, 0.2),
  (30.0, 0.4, 0.0),
  (0.0, 0.0, 0.0),
])
def test_rivian_uses_configured_smoothing(v_ego, maximum, expected):
  assert get_car_lateral_smooth_seconds("rivian", v_ego, maximum) == pytest.approx(expected)
