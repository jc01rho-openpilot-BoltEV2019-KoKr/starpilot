from types import SimpleNamespace

import pytest

from opendbc.car import gen_empty_fingerprint
from opendbc.car.tesla.carcontroller import CarController, get_safety_CP
from opendbc.car.tesla.coop_steering import CooperativeSteeringController
from opendbc.car.tesla.interface import CarInterface
from opendbc.car.tesla.values import CAR, DBC, CarControllerParams, TeslaSafetyFlags
from opendbc.car.vehicle_model import VehicleModel


def make_car_state(torque=0.0, speed=15.0, angle=0.0):
  return SimpleNamespace(out=SimpleNamespace(
    steeringTorque=torque,
    steeringAngleDeg=angle,
    vEgo=speed,
    vEgoRaw=speed,
  ))


@pytest.fixture
def vehicle_model():
  return VehicleModel(get_safety_CP())


def test_disabled_preserves_angle_command(vehicle_model):
  controller = CooperativeSteeringController()
  angle, lat_active = controller.update(12.5, True, False, make_car_state(torque=2.0), vehicle_model)

  assert angle == 12.5
  assert lat_active


def test_light_driver_torque_adjusts_angle(vehicle_model):
  controller = CooperativeSteeringController()
  angle = 0.0

  for _ in range(10):
    angle, lat_active = controller.update(0.0, True, True, make_car_state(torque=1.5), vehicle_model)

  assert lat_active
  assert angle > 0.0
  assert angle <= CarControllerParams.ANGLE_LIMITS.STEER_ANGLE_MAX


def test_inactive_lateral_resets_override(vehicle_model):
  controller = CooperativeSteeringController()
  for _ in range(10):
    controller.update(0.0, True, True, make_car_state(torque=1.5), vehicle_model)

  angle, lat_active = controller.update(8.0, False, True, make_car_state(torque=1.5, angle=8.0), vehicle_model)
  assert angle == 8.0
  assert not lat_active

  angle, lat_active = controller.update(8.0, True, True, make_car_state(angle=8.0), vehicle_model)
  assert angle == 8.0
  assert lat_active


@pytest.mark.parametrize(("candidate", "enabled", "expected"), (
  (CAR.TESLA_MODEL_3, False, False),
  (CAR.TESLA_MODEL_3, True, True),
  (CAR.TESLA_MODEL_Y, True, False),
  (CAR.TESLA_MODEL_S_PREAP, True, False),
))
def test_safety_flag_is_model_3_only(candidate, enabled, expected):
  toggles = SimpleNamespace(tesla_cooperative_steering=enabled, trailer_load_kg=0.0)
  params = CarInterface.get_params(candidate, gen_empty_fingerprint(), [], False, False, False, toggles)

  has_flag = any(config.safetyParam & TeslaSafetyFlags.COOP_STEERING.value for config in params.safetyConfigs)
  assert has_flag is expected

  if candidate != CAR.TESLA_MODEL_S_PREAP:
    assert CarController(DBC[candidate], params).coop_enabled is expected
