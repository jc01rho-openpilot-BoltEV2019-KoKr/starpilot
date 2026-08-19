from types import SimpleNamespace

from cereal import car, custom, log
from opendbc.car.vehicle_model import VehicleModel
from opendbc.car.volkswagen.interface import CarInterface
from opendbc.car.volkswagen.values import CAR
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.controls.lib.drive_helpers import MAX_CURVATURE
from openpilot.selfdrive.controls.lib.latcontrol_curvature import LatControlCurvature


def build_controller():
  cp = CarInterface.get_non_essential_params(CAR.VOLKSWAGEN_ID4_MK1)
  ci = CarInterface(cp, custom.StarPilotCarParams.new_message())
  controller = LatControlCurvature(cp.as_reader(), ci, DT_CTRL)

  cs = car.CarState.new_message()
  cs.vEgo = 15.0
  cs.steeringAngleDeg = 0.0

  params = log.LiveParametersData.new_message()
  params.steerRatio = cp.steerRatio
  params.stiffnessFactor = 1.0
  params.roll = 0.0
  params.angleOffsetDeg = 0.0
  return controller, cs, VehicleModel(cp), params


def test_curvature_controller_output_and_reset():
  controller, cs, vm, params = build_controller()
  toggles = SimpleNamespace()
  assert controller.pid.i_dt == DT_CTRL

  _, output, state = controller.update(True, cs, vm, params, False, 0.01, False, 0.2, None, None, toggles)
  assert state.active
  assert 0.0 < output <= MAX_CURVATURE

  _, output, state = controller.update(False, cs, vm, params, False, 0.01, False, 0.2, None, None, toggles)
  assert not state.active
  assert output == 0.0


def test_curvature_controller_uses_feedforward_during_driver_override():
  controller, cs, vm, params = build_controller()
  cs.steeringPressed = True
  desired_curvature = -0.015

  _, output, state = controller.update(True, cs, vm, params, False, desired_curvature, False, 0.2,
                                       None, None, SimpleNamespace())
  assert state.active
  assert output == desired_curvature
