import unittest
from types import SimpleNamespace

from cereal import car
from openpilot.common.constants import CV
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.car.redneck_cruise import (
  INACTIVE_TIMER,
  RedneckCruise,
  SEND_BUTTON_DECREASE,
  SEND_BUTTON_INCREASE,
  SEND_BUTTON_NONE,
)


ButtonType = car.CarState.ButtonEvent.Type


class TestRedneckCruise(unittest.TestCase):
  def setUp(self):
    self.CP = SimpleNamespace()
    self.FPCP = SimpleNamespace(pcmCruiseSpeed=False, redneckCruiseAvailable=True)
    self.redneck = RedneckCruise(self.CP, self.FPCP)

  def _new_state(self, speed_cluster_mph=20.0, button_events=None):
    return SimpleNamespace(
      cruiseState=SimpleNamespace(speedCluster=speed_cluster_mph * CV.MPH_TO_MS),
      buttonEvents=button_events or [],
    )

  @staticmethod
  def _new_control(override=False, cancel=False, resume=False):
    return SimpleNamespace(
      enabled=True,
      cruiseControl=SimpleNamespace(override=override, cancel=cancel, resume=resume),
    )

  @staticmethod
  def _button_event(button_type, pressed):
    return SimpleNamespace(type=button_type, pressed=pressed)

  def _run_until_active(self, target_mph, speed_cluster_mph=20.0, button_events=None, override=False, cancel=False, resume=False):
    frames = int(INACTIVE_TIMER / DT_CTRL) + 2
    send_button = SEND_BUTTON_NONE
    v_target = 0
    for _ in range(frames):
      send_button, v_target = self.redneck.run(
        self._new_state(speed_cluster_mph=speed_cluster_mph, button_events=button_events),
        self._new_control(override=override, cancel=cancel, resume=resume),
        target_mph * CV.MPH_TO_MS,
        is_metric=False,
      )
      button_events = None
    return send_button, v_target

  def test_increases_cluster_speed_toward_target(self):
    send_button, v_target = self._run_until_active(target_mph=25.0, speed_cluster_mph=20.0)
    self.assertEqual(SEND_BUTTON_INCREASE, send_button)
    self.assertEqual(25, v_target)

  def test_decreases_cluster_speed_toward_target(self):
    send_button, v_target = self._run_until_active(target_mph=20.0, speed_cluster_mph=25.0)
    self.assertEqual(SEND_BUTTON_DECREASE, send_button)
    self.assertEqual(20, v_target)

  def test_suppresses_output_during_manual_cruise_button_use(self):
    button_event = self._button_event(ButtonType.accelCruise, True)
    send_button, _ = self._run_until_active(target_mph=25.0, speed_cluster_mph=20.0, button_events=[button_event])
    self.assertEqual(SEND_BUTTON_NONE, send_button)

  def test_suppresses_output_for_capnp_style_button_events(self):
    button_event = SimpleNamespace(type=SimpleNamespace(raw=int(ButtonType.accelCruise)), pressed=True)
    send_button, _ = self._run_until_active(target_mph=25.0, speed_cluster_mph=20.0, button_events=[button_event])
    self.assertEqual(SEND_BUTTON_NONE, send_button)

  def test_suppresses_output_for_override_cancel_and_resume(self):
    for kwargs in ({"override": True}, {"cancel": True}, {"resume": True}):
      with self.subTest(**kwargs):
        send_button, _ = self._run_until_active(target_mph=25.0, speed_cluster_mph=20.0, **kwargs)
        self.assertEqual(SEND_BUTTON_NONE, send_button)

  def test_resets_when_pcm_cruise_speed_is_enabled(self):
    self.FPCP.pcmCruiseSpeed = True
    send_button, v_target = self._run_until_active(target_mph=25.0, speed_cluster_mph=20.0)
    self.assertEqual(SEND_BUTTON_NONE, send_button)
    self.assertEqual(0, v_target)


if __name__ == "__main__":
  unittest.main()
