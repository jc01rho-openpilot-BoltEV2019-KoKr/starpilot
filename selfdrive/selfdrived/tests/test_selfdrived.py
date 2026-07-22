from cereal import car

from openpilot.selfdrive.selfdrived.selfdrived import commanded_torque_at_max_for_saturation


def test_immediate_max_output_saturation_is_torque_controller_only():
  CP = car.CarParams.new_message()
  CP.steerControlType = car.CarParams.SteerControlType.torque
  CP.lateralTuning.init("torque")

  assert commanded_torque_at_max_for_saturation(CP, 1.0)
  assert not commanded_torque_at_max_for_saturation(CP, 0.99)

  CP.lateralTuning.init("pid")
  assert not commanded_torque_at_max_for_saturation(CP, 1.0)

  CP.lateralTuning.init("torque")
  CP.steerControlType = car.CarParams.SteerControlType.angle
  assert not commanded_torque_at_max_for_saturation(CP, 1.0)
