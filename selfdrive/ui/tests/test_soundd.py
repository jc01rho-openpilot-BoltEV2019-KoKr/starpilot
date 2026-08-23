from cereal import log
from cereal import messaging
from cereal.messaging import SubMaster, PubMaster
from openpilot.selfdrive.ui.soundd import (
  SELFDRIVE_STATE_TIMEOUT,
  SOUNDD_SERVICES,
  check_selfdrive_timeout_alert,
  is_turn_steering_limit_alert,
  should_mute_turn_steering_limit_alert,
)

import time

AudibleAlert = log.SelfdriveState.AudibleAlert


class TestSoundd:
  def test_does_not_consume_car_state_reader(self):
    assert "carState" not in SOUNDD_SERVICES
    assert "starpilotSelfdriveState" in SOUNDD_SERVICES

  def test_turn_steering_limit_alert_detection(self):
    assert is_turn_steering_limit_alert("steerSaturated/warning")
    assert is_turn_steering_limit_alert("goatSteerSaturated/warning")
    assert is_turn_steering_limit_alert("thisIsFineSteerSaturated/warning")
    assert not is_turn_steering_limit_alert("laneChangeBlocked/warning")

  def test_turn_steering_limit_alert_is_muted_only_below_threshold(self):
    assert should_mute_turn_steering_limit_alert("steerSaturated/warning", 10.0, 25.0)
    assert not should_mute_turn_steering_limit_alert("steerSaturated/warning", 25.0, 25.0)
    assert not should_mute_turn_steering_limit_alert("steerSaturated/warning", 30.0, 25.0)
    assert not should_mute_turn_steering_limit_alert("steerSaturated/warning", 10.0, 0.0)
    assert not should_mute_turn_steering_limit_alert("laneChangeBlocked/warning", 10.0, 25.0)

  def test_check_selfdrive_timeout_alert(self):
    sm = SubMaster(['selfdriveState'])
    pm = PubMaster(['selfdriveState'])

    for _ in range(100):
      cs = messaging.new_message('selfdriveState')
      cs.selfdriveState.enabled = True

      pm.send("selfdriveState", cs)

      time.sleep(0.01)

      sm.update(0)

      assert not check_selfdrive_timeout_alert(sm)

    for _ in range(SELFDRIVE_STATE_TIMEOUT * 110):
      sm.update(0)
      time.sleep(0.01)

    assert check_selfdrive_timeout_alert(sm)

  # TODO: add test with micd for checking that soundd actually outputs sounds
