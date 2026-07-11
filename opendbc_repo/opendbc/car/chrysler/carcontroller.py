from opendbc.can import CANPacker
from opendbc.car import Bus, DT_CTRL
from opendbc.car.lateral import apply_meas_steer_torque_limits
from opendbc.car.chrysler import chryslercan
from opendbc.car.chrysler.values import JEEPS, RAM_CARS, RAM_DT, CarControllerParams, ChryslerFlags, ChryslerSafetyFlags, ChryslerStarPilotFlags
from opendbc.car.interfaces import CarControllerBase

JEEP_BRAKE_HOLD_DEFAULT_DECEL = -2.0
JEEP_BRAKE_HOLD_MIN_DECEL = -0.5
JEEP_BRAKE_HOLD_MAX_DECEL = -3.0


def clip_jeep_brake_hold_decel(decel: float) -> float:
  return max(JEEP_BRAKE_HOLD_MAX_DECEL, min(JEEP_BRAKE_HOLD_MIN_DECEL, float(decel)))


def supports_jeep_brake_hold(CP, brake_hold_enabled: bool) -> bool:
  safety_cfg = getattr(CP, "safetyConfigs", ())
  safety_param = safety_cfg[0].safetyParam if safety_cfg else 0
  return (
    brake_hold_enabled and
    getattr(CP, "pcmCruise", False) and
    CP.carFingerprint in JEEPS and
    bool(safety_param & ChryslerSafetyFlags.JEEP_BRAKE_HOLD.value)
  )


class CarController(CarControllerBase):
  def __init__(self, dbc_names, CP):
    super().__init__(dbc_names, CP)
    self.apply_torque_last = 0

    self.hud_count = 0
    self.last_lkas_falling_edge = 0
    self.lkas_control_bit_prev = False
    self.last_button_frame = 0

    self.packer = CANPacker(dbc_names[Bus.pt])
    self.params = CarControllerParams(CP)
    self.jeep_brake_hold_decel = JEEP_BRAKE_HOLD_DEFAULT_DECEL
    self.last_das_3_counter = -1

  def update(self, CC, CS, now_nanos, starpilot_toggles):
    can_sends = []

    lkas_active = CC.latActive and self.lkas_control_bit_prev

    # cruise buttons
    if (self.frame - self.last_button_frame) * DT_CTRL > 0.05:
      das_bus = 2 if self.CP.carFingerprint in RAM_CARS else 0

      # ACC cancellation
      if CC.cruiseControl.cancel:
        self.last_button_frame = self.frame
        can_sends.append(chryslercan.create_cruise_buttons(self.packer, CS.button_counter + 1, das_bus, CS.button_message, cancel=True))

      # ACC resume from standstill
      elif CC.cruiseControl.resume:
        self.last_button_frame = self.frame
        can_sends.append(chryslercan.create_cruise_buttons(self.packer, CS.button_counter + 1, das_bus, CS.button_message, resume=True))

    # HUD alerts
    if self.frame % 25 == 0:
      if CS.lkas_car_model != -1:
        can_sends.append(chryslercan.create_lkas_hud(self.packer, self.CP, lkas_active, CC.hudControl.visualAlert,
                                                     self.hud_count, CS.lkas_car_model, CS.auto_high_beam))
        self.hud_count += 1

    # steering
    if self.frame % self.params.STEER_STEP == 0:

      # TODO: can we make this more sane? why is it different for all the cars?
      lkas_control_bit = self.lkas_control_bit_prev
      if self.FPCP is not None and self.FPCP.flags & ChryslerStarPilotFlags.NO_MIN_STEERING_SPEED:
        lkas_control_bit = CC.latActive
      elif self.CP.carFingerprint in RAM_DT:
        if self.CP.minEnableSpeed <= CS.out.vEgo <= self.CP.minEnableSpeed + 0.5:
          lkas_control_bit = True
        if (self.CP.minEnableSpeed >= 14.5) and (CS.out.gearShifter != 2):
          lkas_control_bit = False
      elif CS.out.vEgo > self.CP.minSteerSpeed:
        lkas_control_bit = True
      elif self.CP.flags & ChryslerFlags.HIGHER_MIN_STEERING_SPEED:
        if CS.out.vEgo < (self.CP.minSteerSpeed - 3.0):
          lkas_control_bit = False
      elif self.CP.carFingerprint in RAM_CARS:
        if CS.out.vEgo < (self.CP.minSteerSpeed - 0.5):
          lkas_control_bit = False

      # EPS faults if LKAS re-enables too quickly
      lkas_control_bit = lkas_control_bit and (self.frame - self.last_lkas_falling_edge > 200)

      if not lkas_control_bit and self.lkas_control_bit_prev:
        self.last_lkas_falling_edge = self.frame
      self.lkas_control_bit_prev = lkas_control_bit

      # steer torque
      new_torque = int(round(CC.actuators.torque * self.params.STEER_MAX))
      apply_torque = apply_meas_steer_torque_limits(new_torque, self.apply_torque_last, CS.out.steeringTorqueEps, self.params)
      if not lkas_active or not lkas_control_bit:
        apply_torque = 0
      self.apply_torque_last = apply_torque

      can_sends.append(chryslercan.create_lkas_command(self.packer, self.CP, int(apply_torque), lkas_control_bit))

    if supports_jeep_brake_hold(self.CP, getattr(starpilot_toggles, "jeep_brake_hold", False)):
      self.update_jeep_brake_hold(CC, CS, can_sends)
    elif getattr(CS, "brake_hold", False):
      CS.brake_hold = False

    self.frame += 1

    new_actuators = CC.actuators.as_builder()
    new_actuators.torque = self.apply_torque_last / self.params.STEER_MAX
    new_actuators.torqueOutputCan = self.apply_torque_last

    return new_actuators, can_sends

  def update_jeep_brake_hold(self, CC, CS, can_sends):
    if not getattr(CS, "das_3", None):
      CS.brake_hold = False
      return

    counter_changed = CS.das_3.get("COUNTER") != self.last_das_3_counter
    self.last_das_3_counter = CS.das_3.get("COUNTER")

    if not CS.brake_hold and CS.cruise_active_actual and CS.acc_decelerating and CS.out.standstill:
      CS.brake_hold = True
      self.jeep_brake_hold_decel = JEEP_BRAKE_HOLD_DEFAULT_DECEL

    driver_intervened = (
      CC.cruiseControl.cancel or
      CS.out.gasPressed or
      CS.out.brakePressed or
      not CS.forward_gear or
      not CS.out.standstill
    )
    if CS.brake_hold and driver_intervened:
      CS.brake_hold = False
      return

    if not CS.brake_hold:
      return

    if CS.cruise_active_actual:
      self.jeep_brake_hold_decel = clip_jeep_brake_hold_decel(
        min(self.jeep_brake_hold_decel, CS.das_3.get("ACC_DECEL", JEEP_BRAKE_HOLD_DEFAULT_DECEL))
      )
      return

    counter_offset = 2 if counter_changed else 3
    can_sends.append(chryslercan.create_das_3_command(self.packer, counter_offset, self.jeep_brake_hold_decel, CS.das_3))

    if self.frame % 10 == 0:
      can_sends.append(chryslercan.create_cruise_buttons(
        self.packer, CS.button_counter + 1, 0, CS.button_message, resume=True
      ))
