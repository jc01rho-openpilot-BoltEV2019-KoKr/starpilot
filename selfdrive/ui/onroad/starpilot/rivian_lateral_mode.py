import pyray as rl

from cereal import car
from openpilot.selfdrive.ui.ui_state import ui_state

ANGLE_COLOR = rl.Color(0x3A, 0xDB, 0x6D, 255)
TORQUE_COLOR = rl.Color(0x4D, 0x9D, 0xFF, 255)
DRIVER_OVERRIDE_COLOR = rl.Color(255, 255, 255, 255)
LateralControlMode = car.CarControl.Actuators.LateralControlMode


class RivianLateralMode:
  """Display Rivian's active lateral channel and driver steering input."""

  def __init__(self):
    self.mode: str | None = None
    self.driver_override = False
    self._frame = -1

  def update(self) -> None:
    sm = ui_state.sm
    if sm.frame == self._frame:
      return
    self._frame = sm.frame

    CP = ui_state.CP
    rivian = CP is not None and CP.brand == "rivian"
    car_state_received = sm.recv_frame["carState"] >= ui_state.started_frame
    car_control_received = sm.recv_frame["carControl"] >= ui_state.started_frame
    if not rivian or not car_state_received or not car_control_received or not sm["carControl"].latActive:
      self.mode = None
      self.driver_override = False
      return

    self.driver_override = sm["carState"].steeringPressed
    lateral_mode = sm["carOutput"].actuatorsOutput.lateralControlMode
    if lateral_mode == LateralControlMode.angle:
      self.mode = "angle"
    elif lateral_mode in (LateralControlMode.torque, LateralControlMode.torqueRecovering):
      self.mode = "torque"
    else:
      self.mode = None

  @property
  def wheel_tint(self) -> "rl.Color | None":
    if self.driver_override:
      return DRIVER_OVERRIDE_COLOR
    if self.mode == "angle":
      return ANGLE_COLOR
    if self.mode == "torque":
      return TORQUE_COLOR
    return None


rivian_lateral_mode = RivianLateralMode()
