from types import SimpleNamespace

from cereal import log
from openpilot.selfdrive.selfdrived.selfdrived import should_loud_blindspot_alert_without_lateral


LaneChangeState = log.LaneChangeState


def _car_state(left_blinker=False, right_blinker=False, left_blindspot=False, right_blindspot=False):
  return SimpleNamespace(
    leftBlinker=left_blinker,
    rightBlinker=right_blinker,
    leftBlindspot=left_blindspot,
    rightBlindspot=right_blindspot,
  )


def _sm(lane_change_state=LaneChangeState.off, lat_active=False, lateral_check=False, pause_lateral=False):
  return {
    "modelV2": SimpleNamespace(meta=SimpleNamespace(laneChangeState=lane_change_state)),
    "carControl": SimpleNamespace(latActive=lat_active),
    "starpilotPlan": SimpleNamespace(lateralCheck=lateral_check),
    "starpilotCarState": SimpleNamespace(pauseLateral=pause_lateral),
  }


def _toggles(enabled=True):
  return SimpleNamespace(
    loud_blindspot_alert=True,
    loud_blindspot_alert_when_disengaged=enabled,
  )


def test_loud_blindspot_alert_without_lateral_for_matching_signal():
  CS = _car_state(left_blinker=True, left_blindspot=True)

  assert should_loud_blindspot_alert_without_lateral(CS, _sm(lat_active=False), _toggles())
  assert should_loud_blindspot_alert_without_lateral(CS, _sm(lat_active=True, lateral_check=False), _toggles())
  assert should_loud_blindspot_alert_without_lateral(CS, _sm(lat_active=True, lateral_check=True, pause_lateral=True), _toggles())


def test_loud_blindspot_alert_without_lateral_ignores_active_lateral():
  CS = _car_state(right_blinker=True, right_blindspot=True)

  assert not should_loud_blindspot_alert_without_lateral(CS, _sm(lat_active=True, lateral_check=True), _toggles())


def test_loud_blindspot_alert_without_lateral_requires_matching_side_and_toggle():
  assert not should_loud_blindspot_alert_without_lateral(_car_state(left_blinker=True, right_blindspot=True), _sm(), _toggles())
  assert not should_loud_blindspot_alert_without_lateral(_car_state(left_blinker=True, right_blinker=True, left_blindspot=True), _sm(), _toggles())
  assert not should_loud_blindspot_alert_without_lateral(_car_state(left_blinker=True, left_blindspot=True), _sm(), _toggles(enabled=False))


def test_loud_blindspot_alert_without_lateral_skips_normal_lane_change_alert_path():
  CS = _car_state(left_blinker=True, left_blindspot=True)

  assert not should_loud_blindspot_alert_without_lateral(CS, _sm(lane_change_state=LaneChangeState.preLaneChange), _toggles())
