import sys
import types
from types import SimpleNamespace

from opendbc.car import structs

fake_interfaces = types.ModuleType("opendbc.car.interfaces")


class _FakeCarControllerBase:
  def __init__(self, dbc_names=None, CP=None):
    self.CP = CP


fake_interfaces.CarControllerBase = _FakeCarControllerBase
sys.modules.setdefault("opendbc.car.interfaces", fake_interfaces)

fake_params = types.ModuleType("openpilot.common.params")


class _FakeParams:
  pass


class _FakeUnknownKeyName(Exception):
  pass


fake_params.Params = _FakeParams
fake_params.UnknownKeyName = _FakeUnknownKeyName
sys.modules.setdefault("openpilot.common.params", fake_params)

fake_testing_grounds = types.ModuleType("openpilot.starpilot.common.testing_grounds")
fake_testing_grounds.testing_ground = SimpleNamespace(use_1=False)
sys.modules.setdefault("openpilot.starpilot.common.testing_grounds", fake_testing_grounds)

from opendbc.car.gm.carcontroller import (
  AUTO_HOLD_DRIVE_GEARS,
  CarController,
  estimate_auto_hold_brake,
  get_adas_keepalive_step,
  get_lka_steering_cmd_counter,
  get_volt_one_pedal_target_decel,
  get_testing_ground_1_brake_switch_bias,
  get_stock_cc_active_for_cancel,
  shape_truck_positive_accel,
  should_activate_auto_hold,
  should_activate_volt_one_pedal,
  should_send_adas_status,
  should_send_stock_long_cancel,
  should_spoof_dash_speed,
  should_spoof_ecm_cruise_status,
  supports_volt_auto_hold,
  supports_volt_one_pedal,
  use_interceptor_sng_launch,
)
from opendbc.car.gm.gmcan import get_friction_brake_mode
from opendbc.car.gm.values import AccState, CAR, GMFlags
from opendbc.car.structs import CarParams
from opendbc.car.common.conversions import Conversions as CV


def _cs(enabled, pcm_acc_status):
  return SimpleNamespace(
    out=SimpleNamespace(cruiseState=SimpleNamespace(enabled=enabled), accFaulted=False),
    pcm_acc_status=pcm_acc_status,
  )


def _sng_cs(v_ego, standstill, cruise_standstill):
  return SimpleNamespace(
    out=SimpleNamespace(
      vEgo=v_ego,
      standstill=standstill,
      cruiseState=SimpleNamespace(standstill=cruise_standstill),
    ),
  )


def _controller(car_fingerprint=CAR.CHEVROLET_BOLT_CC_2018_2021):
  controller = CarController.__new__(CarController)
  controller.CP = SimpleNamespace(carFingerprint=car_fingerprint)
  controller.planner_regen_hold = False
  controller.regen_paddle_pressed = False
  controller.regen_paddle_timer = 0
  controller.regen_press_counter = 0
  controller.regen_release_counter = 0
  controller.regen_min_on_frames = 0
  controller.regen_min_off_frames = 0
  controller.pedal_active_last = False
  controller.pedal_steady = 0.0
  controller.aego = 0.0
  controller.maneuver_paddle_mode = "auto"
  return controller


def test_gen1_bolt_pedal_cancel_uses_pcm_acc_status():
  CP = SimpleNamespace(carFingerprint=CAR.CHEVROLET_BOLT_CC_2018_2021)

  assert get_stock_cc_active_for_cancel(CP, _cs(False, AccState.ACTIVE))


def test_gen2_bolt_acc_pedal_cancel_uses_enabled_only():
  CP = SimpleNamespace(carFingerprint=CAR.CHEVROLET_BOLT_ACC_2022_2023_PEDAL)

  assert not get_stock_cc_active_for_cancel(CP, _cs(False, AccState.ACTIVE))


def test_stock_cancel_is_suppressed_when_acc_is_faulted():
  CP = SimpleNamespace(carFingerprint=CAR.CHEVROLET_VOLT_CAMERA)
  cs = _cs(True, AccState.FAULTED)
  cs.out.accFaulted = True

  assert get_stock_cc_active_for_cancel(CP, cs)
  assert not should_send_stock_long_cancel(11, cs)


def test_stock_cancel_requires_delay_and_no_acc_fault():
  cs = _cs(True, AccState.ACTIVE)

  assert not should_send_stock_long_cancel(10, cs)
  assert should_send_stock_long_cancel(11, cs)


def test_gen1_bolt_pedal_ecm_cruise_spoof_is_not_gated_by_dash_speed_toggle():
  CP = SimpleNamespace(
    carFingerprint=CAR.CHEVROLET_BOLT_CC_2018_2021,
    enableGasInterceptorDEPRECATED=True,
    flags=GMFlags.PEDAL_LONG.value,
    openpilotLongitudinalControl=True,
  )

  assert not should_spoof_dash_speed(CP, SimpleNamespace(disable_openpilot_long=True, gm_pedal_longitudinal=True))
  assert should_spoof_ecm_cruise_status(CP)


def test_gateway_keepalive_uses_gateway_cadence():
  cp = SimpleNamespace(networkLocation=CarParams.NetworkLocation.gateway, flags=0)

  assert get_adas_keepalive_step(cp, is_kaofui_car=True) == 100
  assert get_adas_keepalive_step(cp, is_kaofui_car=False) == 200


def test_removed_camera_keepalive_uses_camera_cadence():
  cp = SimpleNamespace(networkLocation=CarParams.NetworkLocation.fwdCamera, flags=GMFlags.NO_CAMERA.value)

  assert get_adas_keepalive_step(cp, is_kaofui_car=True) == 100


def test_live_camera_path_does_not_send_pt_keepalive():
  cp = SimpleNamespace(networkLocation=CarParams.NetworkLocation.fwdCamera, flags=0)

  assert get_adas_keepalive_step(cp, is_kaofui_car=True) is None


def test_ascm_int_cars_do_not_send_radar_status():
  common = {
    "networkLocation": CarParams.NetworkLocation.fwdCamera,
    "radarUnavailable": False,
  }

  assert not should_send_adas_status(SimpleNamespace(carFingerprint=CAR.BUICK_LACROSSE_ASCM, **common), is_kaofui_car=True)
  assert not should_send_adas_status(SimpleNamespace(carFingerprint=CAR.CHEVROLET_VOLT_ASCM, **common), is_kaofui_car=True)


def test_volt_auto_hold_requires_toggle_supported_non_cc_only_volt_and_stock_safety():
  stock_safety = [SimpleNamespace(safetyParam=0x8000)]
  no_safety = [SimpleNamespace(safetyParam=0)]

  assert not supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      openpilotLongitudinalControl=True,
      networkLocation=CarParams.NetworkLocation.fwdCamera,
      safetyConfigs=no_safety,
    ),
    True,
  )
  assert not supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CC,
      openpilotLongitudinalControl=True,
      networkLocation=CarParams.NetworkLocation.fwdCamera,
      safetyConfigs=no_safety,
    ),
    True,
  )
  assert supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      openpilotLongitudinalControl=True,
      networkLocation=CarParams.NetworkLocation.fwdCamera,
      safetyConfigs=stock_safety,
    ),
    True,
  )
  assert supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT,
      openpilotLongitudinalControl=False,
      networkLocation=CarParams.NetworkLocation.gateway,
      safetyConfigs=stock_safety,
    ),
    True,
  )
  assert supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_2019,
      openpilotLongitudinalControl=False,
      networkLocation=CarParams.NetworkLocation.fwdCamera,
      safetyConfigs=stock_safety,
    ),
    True,
  )
  assert not supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_2019,
      openpilotLongitudinalControl=False,
      networkLocation=CarParams.NetworkLocation.fwdCamera,
      safetyConfigs=no_safety,
    ),
    True,
  )
  assert not supports_volt_auto_hold(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      openpilotLongitudinalControl=True,
      networkLocation=CarParams.NetworkLocation.fwdCamera,
      safetyConfigs=no_safety,
    ),
    False,
  )


def test_auto_hold_brake_estimate_uses_driver_or_op_brake_and_clamps():
  assert estimate_auto_hold_brake(0.0, 20.0) == 80
  assert estimate_auto_hold_brake(20.0, 40.0) == 110
  assert estimate_auto_hold_brake(20.0, 160.0) == 160
  assert estimate_auto_hold_brake(100.0, 400.0) == 240


def test_volt_one_pedal_requires_toggle_supported_volt_stock_safety_and_ev_transmission():
  stock_safety = [SimpleNamespace(safetyParam=0x8000)]
  no_safety = [SimpleNamespace(safetyParam=0)]

  assert supports_volt_one_pedal(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      safetyConfigs=stock_safety,
      transmissionType=structs.CarParams.TransmissionType.direct,
    ),
    True,
  )
  assert not supports_volt_one_pedal(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      safetyConfigs=no_safety,
      transmissionType=structs.CarParams.TransmissionType.direct,
    ),
    True,
  )
  assert not supports_volt_one_pedal(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CC,
      safetyConfigs=stock_safety,
      transmissionType=structs.CarParams.TransmissionType.direct,
    ),
    True,
  )
  assert not supports_volt_one_pedal(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      safetyConfigs=stock_safety,
      transmissionType=structs.CarParams.TransmissionType.automatic,
    ),
    True,
  )
  assert not supports_volt_one_pedal(
    SimpleNamespace(
      carFingerprint=CAR.CHEVROLET_VOLT_CAMERA,
      safetyConfigs=stock_safety,
      transmissionType=structs.CarParams.TransmissionType.direct,
    ),
    False,
  )


def test_auto_hold_drive_gears_accept_capnp_dynamic_enum_membership():
  msg = structs.CarState.new_message()
  msg.gearShifter = structs.CarState.GearShifter.drive

  assert msg.gearShifter in AUTO_HOLD_DRIVE_GEARS


def test_auto_hold_activation_allows_direct_entry_from_stopped_brake_press():
  assert should_activate_auto_hold(
    True,
    False,
    False,
    True,
    False,
    True,
    False,
    False,
    0.01,
  )


def test_auto_hold_activation_stays_latched_after_brake_release():
  assert should_activate_auto_hold(
    True,
    False,
    True,
    False,
    False,
    True,
    False,
    False,
    0.0,
  )


def test_auto_hold_activation_blocks_when_long_is_active_or_motion_is_above_threshold():
  assert not should_activate_auto_hold(
    True,
    True,
    False,
    True,
    False,
    True,
    True,
    False,
    0.0,
  )
  assert not should_activate_auto_hold(
    True,
    True,
    False,
    False,
    False,
    False,
    False,
    False,
    0.03,
  )


def test_auto_hold_activation_allows_standstill_even_if_speed_filter_is_slightly_above_threshold():
  assert should_activate_auto_hold(
    True,
    True,
    False,
    False,
    False,
    True,
    False,
    False,
    0.05,
  )


def test_auto_hold_activation_releases_immediately_on_gas_press():
  assert not should_activate_auto_hold(
    True,
    True,
    True,
    False,
    True,
    True,
    False,
    False,
    0.0,
  )


def test_volt_one_pedal_activation_requires_main_l_mode_and_no_driver_input():
  assert should_activate_volt_one_pedal(
    True,
    True,
    False,
    False,
    False,
    False,
    True,
    structs.CarState.GearShifter.low,
    3.0,
  )
  assert not should_activate_volt_one_pedal(
    True,
    False,
    False,
    False,
    False,
    False,
    True,
    structs.CarState.GearShifter.low,
    3.0,
  )
  assert not should_activate_volt_one_pedal(
    True,
    True,
    True,
    False,
    False,
    False,
    True,
    structs.CarState.GearShifter.low,
    3.0,
  )
  assert not should_activate_volt_one_pedal(
    True,
    True,
    False,
    True,
    False,
    False,
    True,
    structs.CarState.GearShifter.low,
    3.0,
  )
  assert not should_activate_volt_one_pedal(
    True,
    True,
    False,
    False,
    False,
    True,
    True,
    structs.CarState.GearShifter.low,
    3.0,
  )
  assert not should_activate_volt_one_pedal(
    True,
    True,
    False,
    False,
    False,
    False,
    False,
    structs.CarState.GearShifter.drive,
    3.0,
  )


def test_volt_one_pedal_target_decel_stays_active_above_low_speed_band():
  assert get_volt_one_pedal_target_decel(0.5 * CV.MPH_TO_MS) == -1.0
  assert get_volt_one_pedal_target_decel(6.0 * CV.MPH_TO_MS) == -1.1
  assert get_volt_one_pedal_target_decel(20.0 * CV.MPH_TO_MS) == -1.1


def test_volt_one_pedal_regression_ignores_noisy_wheel_direction_bits():
  assert should_activate_volt_one_pedal(
    True,
    True,
    False,
    False,
    False,
    False,
    True,
    structs.CarState.GearShifter.low,
    3.0,
  )


def test_volt_one_pedal_requires_time_in_drive_before_arming():
  assert not should_activate_volt_one_pedal(
    True,
    True,
    False,
    False,
    False,
    False,
    True,
    structs.CarState.GearShifter.low,
    2.5,
  )


def test_friction_brake_mode_keeps_near_stop_disabled_for_regular_long_braking():
  CP = SimpleNamespace(carFingerprint=CAR.CHEVROLET_VOLT_ASCM)

  assert get_friction_brake_mode(120, False, True, False, CP) == 0xa


def test_friction_brake_mode_uses_near_stop_hold_mode_for_volt_auto_hold():
  CP = SimpleNamespace(carFingerprint=CAR.CHEVROLET_VOLT_ASCM)

  assert get_friction_brake_mode(120, False, True, False, CP, allow_near_stop_mode=True) == 0xb
  assert get_friction_brake_mode(120, False, True, True, CP, allow_near_stop_mode=True) == 0xd


def test_calc_pedal_command_small_accel_deadband_keeps_creep_target_stable():
  pos_controller = _controller()
  neg_controller = _controller()

  pos_pedal, pos_regen = pos_controller.calc_pedal_command(0.02, True, 0.3)
  neg_pedal, neg_regen = neg_controller.calc_pedal_command(-0.02, True, 0.3)

  assert not pos_regen
  assert not neg_regen
  assert pos_pedal == neg_pedal


def test_calc_pedal_command_creep_switch_does_not_snap_to_target():
  controller = _controller()
  controller.pedal_active_last = True
  controller.pedal_steady = 0.18
  controller.regen_press_counter = 20

  pedal_gas, press_regen = controller.calc_pedal_command(-1.0, True, 0.5)

  assert press_regen
  assert pedal_gas > 0.15


def test_calc_pedal_command_softens_small_positive_follow_ramp_at_road_speed():
  controller = _controller()
  controller.pedal_active_last = True
  controller.pedal_steady = 0.18

  pedal_gas, press_regen = controller.calc_pedal_command(0.2, True, 18.0)

  assert not press_regen
  assert pedal_gas - 0.18 < 0.026


def test_calc_pedal_command_keeps_strong_positive_requests_responsive():
  controller = _controller()
  controller.pedal_active_last = True
  controller.pedal_steady = 0.18

  pedal_gas, press_regen = controller.calc_pedal_command(1.4, True, 18.0)

  assert not press_regen
  assert pedal_gas - 0.18 > 0.04


def test_shape_truck_positive_accel_softens_small_highway_requests():
  shaped = shape_truck_positive_accel(0.12, 26.0, True)

  assert 0.09 < shaped < 0.10


def test_shape_truck_positive_accel_keeps_mid_follow_requests_available():
  shaped = shape_truck_positive_accel(0.45, 13.5, True)

  assert 0.43 < shaped < 0.45


def test_shape_truck_positive_accel_leaves_large_requests_alone():
  assert shape_truck_positive_accel(1.0, 26.0, True) == 1.0


def test_shape_truck_positive_accel_is_inactive_when_disabled_or_low_speed():
  assert shape_truck_positive_accel(0.12, 26.0, False) == 0.12
  assert shape_truck_positive_accel(0.12, 6.0, True) == 0.12


def test_use_interceptor_sng_launch_requires_actual_near_stop():
  CP = SimpleNamespace(vEgoStarting=0.25)

  assert use_interceptor_sng_launch(CP, _sng_cs(0.0, True, True))
  assert use_interceptor_sng_launch(CP, _sng_cs(0.2, False, True))
  assert not use_interceptor_sng_launch(CP, _sng_cs(1.2, False, True))
  assert not use_interceptor_sng_launch(CP, _sng_cs(0.0, True, False))


def test_use_interceptor_sng_launch_extends_for_maneuver_mode():
  CP = SimpleNamespace(vEgoStarting=0.25)

  assert use_interceptor_sng_launch(CP, _sng_cs(1.2, False, True), maneuver_mode=True)
  assert not use_interceptor_sng_launch(CP, _sng_cs(2.2, False, True), maneuver_mode=True)


def test_testing_ground_1_brake_switch_bias_is_softened_but_still_speed_scaled():
  assert get_testing_ground_1_brake_switch_bias(0.0) == 40
  assert get_testing_ground_1_brake_switch_bias(6.0) == 85
  assert get_testing_ground_1_brake_switch_bias(15.0) == 130
  assert get_testing_ground_1_brake_switch_bias(30.0) == 170


def test_lka_counter_uses_returned_loopback_counter():
  cs = SimpleNamespace(
    loopback_lka_steering_cmd_updated=True,
    loopback_lka_steering_cmd_counter=2,
    loopback_lka_steering_cmd_ts_nanos=1,
    pt_lka_steering_cmd_counter=0,
  )

  assert get_lka_steering_cmd_counter(0, cs) == 3


def test_lka_counter_keeps_advancing_without_loopback_updates():
  cs = SimpleNamespace(
    loopback_lka_steering_cmd_updated=False,
    loopback_lka_steering_cmd_counter=0,
    loopback_lka_steering_cmd_ts_nanos=1,
    pt_lka_steering_cmd_counter=0,
  )

  next_counter = 1
  sent = []
  for _ in range(6):
    idx = get_lka_steering_cmd_counter(next_counter, cs)
    sent.append(idx)
    next_counter = (idx + 1) % 4

  assert sent == [1, 2, 3, 0, 1, 2]


def test_lka_counter_only_seeds_from_pt_counter_once_without_loopback():
  cs = SimpleNamespace(
    loopback_lka_steering_cmd_updated=False,
    loopback_lka_steering_cmd_counter=0,
    loopback_lka_steering_cmd_ts_nanos=0,
    pt_lka_steering_cmd_counter=0,
  )

  next_counter = -1
  sent = []
  for _ in range(6):
    idx = get_lka_steering_cmd_counter(next_counter, cs)
    sent.append(idx)
    next_counter = (idx + 1) % 4

  assert sent == [1, 2, 3, 0, 1, 2]
