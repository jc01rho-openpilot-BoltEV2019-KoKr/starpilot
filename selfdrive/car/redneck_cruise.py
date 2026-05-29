from cereal import car
from opendbc.car import apply_hysteresis
from openpilot.common.constants import CV
from openpilot.common.realtime import DT_CTRL

ButtonType = car.CarState.ButtonEvent.Type

SEND_BUTTON_NONE = 0
SEND_BUTTON_INCREASE = 1
SEND_BUTTON_DECREASE = 2

HYST_GAP = 0.0
INACTIVE_TIMER = 0.4

CRUISE_BUTTON_TIMERS = {
  int(ButtonType.decelCruise): 0,
  int(ButtonType.accelCruise): 0,
  int(ButtonType.setCruise): 0,
  int(ButtonType.resumeCruise): 0,
  int(ButtonType.cancel): 0,
  int(ButtonType.mainCruise): 0,
}


def get_minimum_set_speed(is_metric: bool) -> int:
  return 30 if is_metric else 20


def update_manual_button_timers(CS: car.CarState, button_timers: dict[int, int]) -> None:
  for button_type in button_timers:
    if button_timers[button_type] > 0:
      button_timers[button_type] += 1

  for event in CS.buttonEvents:
    button_type = event.type.raw if hasattr(event.type, "raw") else int(event.type)
    if button_type in button_timers:
      button_timers[button_type] = 1 if event.pressed else 0


class RedneckCruise:
  def __init__(self, CP, FPCP):
    self.CP = CP
    self.FPCP = FPCP

    self.v_target = 0
    self.v_target_ms_last = 0.0
    self.v_cruise_cluster = 0
    self.v_cruise_min = 0
    self.state = "inactive"
    self.pre_active_timer = 0
    self.is_ready = False
    self.is_ready_prev = False
    self.cruise_button_timers = dict(CRUISE_BUTTON_TIMERS)

  @staticmethod
  def _send_button_for_state(state: str) -> int:
    if state == "increasing":
      return SEND_BUTTON_INCREASE
    if state == "decreasing":
      return SEND_BUTTON_DECREASE
    return SEND_BUTTON_NONE

  def _reset(self) -> None:
    self.state = "inactive"
    self.pre_active_timer = 0
    self.is_ready = False
    self.is_ready_prev = False

  def _update_calculations(self, CS: car.CarState, v_target_ms: float, is_metric: bool) -> None:
    speed_conv = CV.MS_TO_KPH if is_metric else CV.MS_TO_MPH
    ms_conv = CV.KPH_TO_MS if is_metric else CV.MPH_TO_MS

    self.v_target_ms_last = apply_hysteresis(v_target_ms, self.v_target_ms_last, HYST_GAP * ms_conv)
    self.v_target = round(self.v_target_ms_last * speed_conv)
    self.v_cruise_min = get_minimum_set_speed(is_metric)
    self.v_cruise_cluster = round(CS.cruiseState.speedCluster * speed_conv)

  def _update_readiness(self, CS: car.CarState, CC: car.CarControl) -> None:
    update_manual_button_timers(CS, self.cruise_button_timers)
    button_pressed = any(timer > 0 for timer in self.cruise_button_timers.values())
    self.is_ready = CC.enabled and not CC.cruiseControl.override and not CC.cruiseControl.cancel and not CC.cruiseControl.resume and not button_pressed

  def _update_state_machine(self) -> int:
    self.pre_active_timer = max(0, self.pre_active_timer - 1)

    if self.state != "inactive":
      if not self.is_ready:
        self.state = "inactive"
      elif self.state == "preActive":
        if self.pre_active_timer <= 0:
          if self.v_target == self.v_cruise_cluster:
            self.state = "holding"
          elif self.v_target > self.v_cruise_cluster:
            self.state = "increasing"
          elif self.v_target < self.v_cruise_cluster and self.v_cruise_cluster > self.v_cruise_min:
            self.state = "decreasing"
      elif self.state == "holding":
        if self.v_target != self.v_cruise_cluster:
          self.state = "preActive"
      elif self.state == "increasing":
        if self.v_target <= self.v_cruise_cluster:
          self.state = "holding"
      elif self.state == "decreasing":
        if self.v_target >= self.v_cruise_cluster or self.v_cruise_cluster <= self.v_cruise_min:
          self.state = "holding"
    elif self.is_ready and not self.is_ready_prev:
      self.pre_active_timer = int(INACTIVE_TIMER / DT_CTRL)
      self.state = "preActive"

    return self._send_button_for_state(self.state)

  def run(self, CS: car.CarState, CC: car.CarControl, v_target_ms: float, is_metric: bool) -> tuple[int, int]:
    if self.FPCP.pcmCruiseSpeed or not self.FPCP.redneckCruiseAvailable:
      self._reset()
      return SEND_BUTTON_NONE, 0

    self._update_calculations(CS, v_target_ms, is_metric)
    self._update_readiness(CS, CC)
    send_button = self._update_state_machine()

    self.is_ready_prev = self.is_ready
    return send_button, self.v_target
