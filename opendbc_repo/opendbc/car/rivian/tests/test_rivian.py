from types import SimpleNamespace

from opendbc.car import Bus, lateral as lateral_helpers, structs
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.docs_definitions import CarHarness
from opendbc.car.rivian import carcontroller as rivian_carcontroller
from opendbc.car.rivian import ext_controller
from opendbc.car.rivian.carcontroller import CarController, get_longitudinal_accel
from opendbc.car.rivian.carstate import get_cruise_available
from opendbc.car.rivian.carstate_ext import RivianLongitudinalState
from opendbc.car.rivian.ext_controller import ExternalController
from opendbc.car.rivian.faults import get_steering_faults
from opendbc.car.rivian.fingerprints import FW_VERSIONS
from opendbc.car.rivian.interface import CarInterface
from opendbc.car.rivian.toi_controller import (TOI_ACK_FRAMES, TOI_MAX_ANGLE_FRAMES,
                                               TOI_RECOVERY_TIMEOUT_FRAMES, ToiController, ToiState)
from opendbc.car.rivian.values import (CAR, FW_QUERY_CONFIG, MAX_ALLOWED_LATERAL_ACCEL, CarControllerParams, WMI,
                                       ModelLine, ModelYear, RivianFlags, RivianSafetyFlags)


class TestRivian:
  @staticmethod
  def _car_params(bus_one_messages=(), alpha_long=False, gen2=False):
    fingerprint = {bus: {} for bus in range(8)}
    if not gen2:
      fingerprint[0][0x321] = 8
    fingerprint[1] = {address: 8 for address in bus_one_messages}
    return CarInterface.get_params(CAR.RIVIAN_R1_GEN1, fingerprint, [], alpha_long, False, False, SimpleNamespace())

  def test_standard_harness_uses_torque_control(self):
    params = self._car_params()

    assert not params.dashcamOnly
    assert params.steerControlType == structs.CarParams.SteerControlType.torque
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert not params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert not params.openpilotLongitudinalControl

  def test_longitudinal_harness_uses_torque_and_openpilot_long(self):
    params = self._car_params((0x131A,), alpha_long=True)

    assert not params.dashcamOnly
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert params.openpilotLongitudinalControl
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL

  def test_extreme_harness_enables_angle_control(self):
    params = self._car_params((0x1310,))

    assert not params.dashcamOnly
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL

  def test_extreme_and_longitudinal_harnesses_enable_both_paths(self):
    params = self._car_params((0x1310, 0x131A), alpha_long=True)

    assert not params.dashcamOnly
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL
    assert params.openpilotLongitudinalControl

  def test_gen2_is_detected_without_enabling_harness_capabilities(self):
    params = self._car_params(gen2=True)

    assert params.flags & RivianFlags.GEN2
    assert not params.flags & RivianFlags.ANGLE_HARNESS
    assert not params.flags & RivianFlags.LONGITUDINAL_HARNESS

  def test_gen2_detection_preserves_explicit_harness_capabilities(self):
    params = self._car_params((0x1310, 0x131A), alpha_long=True, gen2=True)

    assert params.flags & RivianFlags.GEN2
    assert params.flags & RivianFlags.ANGLE_HARNESS
    assert params.flags & RivianFlags.LONGITUDINAL_HARNESS
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.ANGLE_CONTROL
    assert params.safetyConfigs[0].safetyParam & RivianSafetyFlags.LONG_CONTROL

  def test_gen2_docs_use_rivian_b_harness(self):
    gen2_docs = [doc for doc in CAR.RIVIAN_R1_GEN1.config.car_docs if "2025" in doc.name]

    assert len(gen2_docs) == 2
    assert all(CarHarness.rivian_b in doc.car_parts.parts for doc in gen2_docs)

  def test_standard_harness_uses_acm_state_for_stock_acc_availability(self):
    params = self._car_params()

    assert get_cruise_available(params.flags, 0)  # standby
    assert get_cruise_available(params.flags, 1)  # ACC active before VDM responds
    assert not get_cruise_available(params.flags, 2)  # Highway Assist
    assert not get_cruise_available(params.flags, 3)  # unavailable
    assert not get_cruise_available(params.flags, 4)  # faulted

  def test_longitudinal_harness_does_not_depend_on_stock_acm_state(self):
    params = self._car_params((0x131A,), alpha_long=True)

    assert all(get_cruise_available(params.flags, feature_status) for feature_status in range(5))

  def test_gas_pedal_zeroes_stale_longitudinal_acceleration(self):
    assert get_longitudinal_accel(0.07, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(-2.44, gas_pressed=True) == 0.0
    assert get_longitudinal_accel(0.07, gas_pressed=False) == 0.07

  def test_longitudinal_drag_feedforward_is_active_only_while_controlling(self):
    assert get_longitudinal_accel(0.0, gas_pressed=False, long_active=False, v_ego=8.0) == 0.0
    assert get_longitudinal_accel(0.0, gas_pressed=False, long_active=True, v_ego=8.0) == 0.17
    assert get_longitudinal_accel(0.0, gas_pressed=True, long_active=True, v_ego=8.0) == 0.0

  def test_live_params_update_rx_dev_command_model(self):
    updates = []
    controller = CarController.__new__(CarController)
    controller.ext_controller = SimpleNamespace(
      roll=0.0,
      angle_offset_deg=0.0,
      VM=SimpleNamespace(update_params=lambda stiffness, ratio: updates.append((stiffness, ratio))),
    )

    controller.update_live_params(0.05, 1.25, 0.8, 16.0)

    assert controller.ext_controller.roll == 0.05
    assert controller.ext_controller.angle_offset_deg == 1.25
    assert updates == [(0.8, 16.0)]

  def test_rivian_angle_limit_does_not_change_shared_angle_car_behavior(self, monkeypatch):
    limits = SimpleNamespace(ANGLE_LIMITS=SimpleNamespace(MAX_ANGLE_RATE=5.0, STEER_ANGLE_MAX=500.0))
    vehicle_model = SimpleNamespace()

    monkeypatch.setattr(ext_controller, "get_max_angle_vm", lambda *args: 10.0)
    monkeypatch.setattr(ext_controller, "get_max_angle_delta_vm", lambda *args: 1.0)
    monkeypatch.setattr(lateral_helpers, "get_max_angle_vm", lambda *args: 10.0)
    monkeypatch.setattr(lateral_helpers, "get_max_angle_delta_vm", lambda *args: 1.0)

    rivian_angle = ext_controller.apply_rivian_steer_angle_limits_vm(
      20.0, 15.0, 10.0, 0.0, True, limits, vehicle_model,
    )
    shared_angle = lateral_helpers.apply_steer_angle_limits_vm(
      20.0, 15.0, 10.0, 0.0, True, limits, vehicle_model,
    )

    assert rivian_angle == 14.0
    assert shared_angle == 10.0

  def test_angle_saturation_is_debounced_and_clears_outside_angle_mode(self):
    controller = ExternalController(self._car_params((0x1310,)))
    car_state = SimpleNamespace(out=SimpleNamespace(
      vEgoRaw=15.0,
      aEgo=0.0,
      steeringAngleDeg=0.0,
    ))

    for _ in range(ext_controller.ANGLE_SAT_FRAMES - 1):
      controller._update_angle(car_state, True, desired_angle=200.0, desired_lat_accel=2.0)
      assert not controller.angle_saturated

    controller._update_angle(car_state, True, desired_angle=200.0, desired_lat_accel=2.0)
    assert controller.angle_saturated

    controller.torque_active = True
    controller._update_angle(car_state, True, desired_angle=200.0, desired_lat_accel=2.0)
    assert not controller.angle_saturated

  def test_angle_saturation_ignores_parking_speed_turns(self):
    controller = ExternalController(self._car_params((0x1310,)))
    car_state = SimpleNamespace(out=SimpleNamespace(
      vEgoRaw=2.0,
      aEgo=0.0,
      steeringAngleDeg=0.0,
    ))

    for _ in range(ext_controller.ANGLE_SAT_FRAMES + 5):
      controller._update_angle(car_state, True, desired_angle=400.0, desired_lat_accel=0.8)

    assert not controller.angle_saturated

  def test_angle_command_envelope_is_below_product_lateral_accel_limit(self):
    assert 0.0 < CarControllerParams.ANGLE_LIMITS.MAX_LATERAL_ACCEL <= MAX_ALLOWED_LATERAL_ACCEL

  def test_angle_saturation_param_is_seeded_and_edge_written(self):
    writes = []
    controller = CarController.__new__(CarController)
    controller.ext_controller = SimpleNamespace(angle_saturated=False)
    controller.angle_saturation_last = None
    controller.angle_saturation_params = SimpleNamespace(
      put_bool=lambda key, value: writes.append((key, value)),
    )

    controller._publish_angle_saturation()
    controller._publish_angle_saturation()
    controller.ext_controller.angle_saturated = True
    controller._publish_angle_saturation()

    assert writes == [
      ("RivianAngleSaturated", False),
      ("RivianAngleSaturated", True),
    ]

  def test_toi_recovery_failure_param_is_edge_written(self):
    writes = []
    controller = CarController.__new__(CarController)
    controller.angle_harness = False
    controller.toi_controller = SimpleNamespace(recovery_failed=False)
    controller.toi_recovery_failed_last = None
    controller.toi_recovery_params = SimpleNamespace(
      put_bool=lambda key, value: writes.append((key, value)),
    )

    controller._publish_toi_recovery_failed()
    controller._publish_toi_recovery_failed()
    controller.toi_controller.recovery_failed = True
    controller._publish_toi_recovery_failed()

    assert writes == [
      ("RivianToiRecoveryFailed", False),
      ("RivianToiRecoveryFailed", True),
    ]

  @staticmethod
  def _controller_actuators(monkeypatch, *, angle_harness, torque_active, requested_torque, applied_torque,
                            angle_control=True, toi_recovering=False, gen2=False, frame=1):
    monkeypatch.setattr(rivian_carcontroller, "create_lka_steering", lambda *args: None)
    monkeypatch.setattr(rivian_carcontroller, "create_angle_steering", lambda *args: None)
    monkeypatch.setattr(rivian_carcontroller, "create_acm_status", lambda *args: None)
    monkeypatch.setattr(rivian_carcontroller, "apply_driver_steer_torque_limits", lambda *args: applied_torque)
    controller = CarController.__new__(CarController)
    flags = RivianFlags.GEN2 if gen2 else RivianFlags(0)
    controller.CP = SimpleNamespace(flags=flags, openpilotLongitudinalControl=False)
    controller.packer = None
    controller.frame = frame
    controller.apply_torque_last = 0
    controller.cancel_frames = 0
    controller.toi_controller = SimpleNamespace(
      update=lambda *args: (True, True),
      recovering=toi_recovering,
      recovery_failed=False,
    )
    controller.angle_harness = angle_harness
    controller.ext_controller = None
    if angle_harness:
      controller.ext_controller = SimpleNamespace(
        update=lambda *args: None,
        force_torque=False,
        torque_cmd=applied_torque,
        toi_act_cmd=True,
        apply_angle_last=12.0,
        angle_active=not torque_active,
        torque_active=torque_active,
        torque_prearm=False,
        toi_controller=SimpleNamespace(recovering=toi_recovering, recovery_failed=False),
      )

    output = SimpleNamespace()
    actuators = SimpleNamespace(torque=requested_torque, accel=0.0, as_builder=lambda: output)
    car_control = SimpleNamespace(
      actuators=actuators,
      latActive=True,
      longActive=False,
      enabled=True,
      cruiseControl=SimpleNamespace(cancel=False),
    )
    car_state = SimpleNamespace(
      out=SimpleNamespace(
        gearShifter=structs.CarState.GearShifter.drive,
        vEgo=10.0,
        vEgoRaw=10.0,
        gasPressed=False,
        steeringTorque=0.0,
        steeringAngleDeg=0.0,
      ),
      acm_lka_hba_cmd={},
      sccm_wheel_touch={},
      vdm_adas_status=(),
    )

    result = controller.update(car_control, car_state, 0, SimpleNamespace(rivian_angle_control=angle_control))[0]
    result.force_torque = controller.ext_controller.force_torque if angle_harness else None
    return result

  def test_angle_toggle_selects_controller_live(self, monkeypatch):
    angle_output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=False,
      requested_torque=0.0,
      applied_torque=0,
      angle_control=True,
    )
    torque_output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=False,
      requested_torque=0.0,
      applied_torque=0,
      angle_control=False,
    )

    assert not angle_output.force_torque
    assert torque_output.force_torque

  def test_angle_channel_reports_actual_zero_torque(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=False,
      requested_torque=0.42,
      applied_torque=0,
    )

    assert output.torque == 0.0
    assert output.torqueOutputCan == 0
    assert output.lateralControlMode == structs.CarControl.Actuators.LateralControlMode.angle

  def test_torque_fallback_reports_applied_can_torque(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=True,
      requested_torque=0.42,
      applied_torque=100,
    )
    steer_max = round(float(rivian_carcontroller.np.interp(
      10.0,
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[0],
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[1],
    )))

    assert output.torque == 100 / steer_max
    assert output.torqueOutputCan == 100
    assert output.lateralControlMode == structs.CarControl.Actuators.LateralControlMode.torque

  def test_torque_harness_reporting_is_unchanged(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=False,
      torque_active=False,
      requested_torque=0.42,
      applied_torque=80,
    )
    steer_max = round(float(rivian_carcontroller.np.interp(
      10.0,
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[0],
      rivian_carcontroller.CarControllerParams.STEER_MAX_LOOKUP[1],
    )))

    assert output.torque == 80 / steer_max
    assert output.torqueOutputCan == 80
    assert output.lateralControlMode == structs.CarControl.Actuators.LateralControlMode.torque

  def test_torque_recovery_is_reported_explicitly(self, monkeypatch):
    output = self._controller_actuators(
      monkeypatch,
      angle_harness=True,
      torque_active=True,
      requested_torque=0.42,
      applied_torque=0,
      toi_recovering=True,
    )

    assert output.lateralControlMode == structs.CarControl.Actuators.LateralControlMode.torqueRecovering

  def test_gen2_does_not_transmit_missing_wheel_touch_message(self, monkeypatch):
    monkeypatch.setattr(
      rivian_carcontroller,
      "create_wheel_touch",
      lambda *args: (_ for _ in ()).throw(AssertionError("Gen 2 has no SCCM wheel-touch message")),
    )

    self._controller_actuators(
      monkeypatch,
      angle_harness=False,
      torque_active=False,
      requested_torque=0.0,
      applied_torque=0,
      gen2=True,
      frame=0,
    )

  def test_gen1_continues_transmitting_wheel_touch_message(self, monkeypatch):
    calls = []
    monkeypatch.setattr(rivian_carcontroller, "create_wheel_touch", lambda *args: calls.append(args))

    self._controller_actuators(
      monkeypatch,
      angle_harness=False,
      torque_active=False,
      requested_torque=0.0,
      applied_torque=0,
      frame=0,
    )

    assert len(calls) == 1

  def test_software_cruise_speed_request_is_clamped_to_rivian_bounds(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))

    assert state.set_cruise_speed(45 * CV.MPH_TO_MS) == 45 * CV.MPH_TO_MS
    assert state.set_cruise_speed(10 * CV.MPH_TO_MS) == 20 * CV.MPH_TO_MS
    assert state.set_cruise_speed(100 * CV.MPH_TO_MS) == 85 * CV.MPH_TO_MS

  @staticmethod
  def _longitudinal_parsers(scroll=0, scroll_click=0):
    return {
      Bus.alt: SimpleNamespace(vl={
        "WheelButtons_Fwd": {
          "RightButton_Scroll": scroll,
          "RightButton_ScrollClick": scroll_click,
          "RightButton_RightClick": 0,
          "RightButton_LeftClick": 0,
        },
        "BSM_BlindSpotIndicator_Fwd": {
          "BSM_BlindSpotIndicator_Left": 0,
          "BSM_BlindSpotIndicator_Right": 0,
        },
      }),
      Bus.adas: SimpleNamespace(vl={"Cluster": {"Cluster_Unit": 1}}),
      Bus.pt: SimpleNamespace(vl={"VDM_AdasSts": {"VDM_UserAdasRequest": 0}}),
    }

  @staticmethod
  def _longitudinal_ret():
    return SimpleNamespace(
      buttonEvents=[],
      cruiseState=SimpleNamespace(enabled=True, speed=0.0),
      vEgoCluster=10.0,
      leftBlindspot=False,
      rightBlindspot=False,
    )

  def test_scroll_rotation_emits_one_personality_event_per_detent(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))
    ret = self._longitudinal_ret()

    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=0)) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=1))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]
    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=1)) == []
    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=255)) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll=2))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]

  def test_scroll_click_emits_held_distance_button_edges(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=True))
    ret = self._longitudinal_ret()

    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers()) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll_click=2))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, True)]
    assert state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll_click=2)) == []
    events = state.update_longitudinal_upgrade(ret, self._longitudinal_parsers(scroll_click=0))
    assert [(event.type, event.pressed) for event in events] == [(structs.CarState.ButtonEvent.Type.gapAdjustCruise, False)]

  def test_scroll_controls_are_ignored_without_openpilot_longitudinal(self):
    state = RivianLongitudinalState(SimpleNamespace(openpilotLongitudinalControl=False))
    events = state.update_longitudinal_upgrade(
      self._longitudinal_ret(),
      self._longitudinal_parsers(scroll=1, scroll_click=2),
    )
    assert events == []

  def test_angle_harness_ignores_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, True, False, 1, 0)

    assert not permanent
    assert not temporary
    assert not disengage

  def test_angle_harness_reports_active_eac_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, False, False, 2, 12)

    assert not permanent
    assert temporary
    assert disengage

  def test_torque_harness_reports_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(False, True, False, 1, 0)

    assert not permanent
    assert temporary
    assert not disengage

  def test_angle_harness_reports_persistent_toi_fault(self):
    permanent, temporary, disengage = get_steering_faults(True, True, True, 1, 0)

    assert not permanent
    assert temporary
    assert not disengage

  def test_custom_fuzzy_fingerprinting(self, subtests):
    for platform in CAR:
      with subtests.test(platform=platform.name):
        for wmi in WMI:
          for line in ModelLine:
            for year in ModelYear:
              for bad in (True, False):
                vin = ["0"] * 17
                vin[:3] = wmi
                vin[3] = line.value
                vin[9] = year.value
                if bad:
                  vin[3] = "Z"
                vin = "".join(vin)

                matches = FW_QUERY_CONFIG.match_fw_to_car_fuzzy({}, vin, FW_VERSIONS)
                should_match = year != ModelYear.T_2026 and not bad
                assert (matches == {platform}) == should_match, "Bad match"

  def test_toi_engagement_waits_for_epas_acknowledgement(self):
    controller = ToiController()

    assert controller.update(True, False, False, False, False) == (True, False)
    assert controller.state == ToiState.REARMING

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False) == (True, False)

    assert controller.state == ToiState.TORQUE
    assert controller.update(True, False, False, True, False) == (True, True)

  def test_toi_delayed_acknowledgement_does_not_report_recovery_failure(self):
    controller = ToiController()

    for _ in range(31):
      assert controller.update(True, False, False, False, False) == (True, False)

    assert controller.state == ToiState.REARMING
    assert not controller.recovery_failed

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False) == (True, False)

    assert controller.state == ToiState.TORQUE
    assert not controller.recovery_failed

  def test_toi_prearm_allows_torque_before_epas_acknowledgement(self):
    controller = ToiController()

    assert controller.update(True, False, False, False, False, prearming=True) == (True, True)
    assert controller.state == ToiState.PREARMING
    assert not controller.recovering

    assert controller.update(True, False, False, False, False) == (True, True)
    assert controller.state == ToiState.ACTIVATING

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False) == (True, True)

    assert controller.state == ToiState.TORQUE
    assert not controller.recovery_failed

  def test_toi_prearm_resumes_after_high_angle_release(self):
    controller = ToiController()

    for _ in range(TOI_MAX_ANGLE_FRAMES):
      assert controller.update(True, True, False, False, False, prearming=True) == (True, True)

    assert controller.update(True, True, False, False, False, prearming=True) == (False, False)
    assert controller.state == ToiState.RELEASING

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, True, False, False, False, prearming=True) == (False, False)

    assert controller.state == ToiState.PREARMING
    assert controller.update(True, True, False, False, False, prearming=True) == (True, True)

  def test_toi_prearmed_activation_timeout_releases_request(self):
    controller = ToiController()

    assert controller.update(True, False, False, False, False, prearming=True) == (True, True)
    for _ in range(TOI_RECOVERY_TIMEOUT_FRAMES - 1):
      assert controller.update(True, False, False, False, False) == (True, True)

    assert controller.update(True, False, False, False, False) == (False, False)
    assert controller.state == ToiState.RELEASING
    assert controller.recovery_failed

  def test_high_angle_toi_release_waits_for_feedback_before_rearming(self):
    controller = ToiController()
    controller.state = ToiState.TORQUE

    for _ in range(TOI_MAX_ANGLE_FRAMES):
      assert controller.update(True, True, False, True, False) == (True, True)

    assert controller.update(True, True, False, True, False) == (False, False)
    assert controller.state == ToiState.RELEASING

    # Unlike the old two-frame blip, the request stays low for as long as the
    # EPAS continues reporting that torque overlay is active.
    for _ in range(5):
      assert controller.update(True, True, False, True, False) == (False, False)

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, True, False, False, False) == (False, False)

    assert controller.state == ToiState.REARMING
    assert controller.update(True, True, False, False, False) == (True, False)

  def test_driver_override_recovery_waits_for_lower_angle_before_rearming(self):
    controller = ToiController()
    controller.state = ToiState.RELEASING

    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, True, False, False, False, high_angle_rearm=False,
                               hold_high_angle_release=True) == (False, False)

    assert controller.state == ToiState.HIGH_ANGLE_LOCKOUT
    for _ in range(TOI_RECOVERY_TIMEOUT_FRAMES + 1):
      assert controller.update(True, True, False, False, False, high_angle_rearm=False,
                               hold_high_angle_release=True) == (False, False)
    assert not controller.recovery_failed

    # The high-angle threshold has hysteresis: dropping below the 90 degree
    # release point is not sufficient; rearming waits until 80 degrees.
    assert controller.update(True, False, False, False, False, high_angle_rearm=False,
                             hold_high_angle_release=True) == (False, False)
    assert controller.state == ToiState.HIGH_ANGLE_LOCKOUT
    assert controller.update(True, False, False, False, False, high_angle_rearm=True,
                             hold_high_angle_release=True) == (False, False)
    assert controller.state == ToiState.REARMING
    assert controller.update(True, False, False, False, False, high_angle_rearm=True,
                             hold_high_angle_release=True) == (True, False)
    for _ in range(TOI_ACK_FRAMES):
      assert controller.update(True, False, False, True, False, high_angle_rearm=True,
                               hold_high_angle_release=True) == (True, False)

    assert controller.state == ToiState.TORQUE
    assert controller.update(True, False, False, True, False, high_angle_rearm=True,
                             hold_high_angle_release=True) == (True, True)

  def test_toi_fault_forces_release_at_any_angle(self):
    controller = ToiController()
    controller.state = ToiState.TORQUE

    assert controller.update(True, False, True, False, False) == (False, False)
    assert controller.state == ToiState.RELEASING

  def test_toi_recovery_timeout_is_reported_and_request_stays_released(self):
    controller = ToiController()
    controller.state = ToiState.RELEASING

    for _ in range(TOI_RECOVERY_TIMEOUT_FRAMES):
      assert controller.update(True, False, True, False, False) == (False, False)

    assert controller.recovery_failed
    assert controller.state == ToiState.RELEASING

  def test_toi_release_resets_external_torque_limiter(self):
    controller = ExternalController.__new__(ExternalController)
    controller.torque_active = True
    controller.torque_prearm = False
    controller.driver_override_recovery = False
    controller.apply_torque_last = 100
    controller.torque_cmd = 100
    controller.toi_controller = SimpleNamespace(
      update=lambda *args, **kwargs: (False, False),
      recovering=True,
      recovery_failed=False,
    )

    car_state = SimpleNamespace(
      out=SimpleNamespace(vEgoRaw=10.0, steeringTorque=0.0, steeringAngleDeg=100.0),
      toi_fault=True,
      toi_active=False,
      toi_unavailable=False,
    )
    controller._update_torque(car_state, SimpleNamespace(torque=1.0))

    assert controller.apply_torque_last == 0
    assert controller.torque_cmd == 0
    assert not controller.toi_act_cmd

  @staticmethod
  def _handoff_controller(torque_active=False, lat_active_last=True):
    controller = ExternalController.__new__(ExternalController)
    controller.hands_on = False
    controller.torque_active = torque_active
    controller.torque_active_frames = ext_controller.MIN_TORQUE_FRAMES
    controller.driver_override_recovery = False
    controller.galaxy_torque_recovery = False
    controller.hands_off_frames = ext_controller.DRIVER_HANDS_OFF_EXIT_FRAMES
    controller.lat_active_last = lat_active_last
    controller.eac_dead_frames = 0
    controller.eac_rearm_release_frames = 0
    controller.eac_rearm_attempted = False
    controller.force_torque = False
    controller.torque_prearm = False
    controller.prearm_frames = 0
    controller.prearm_torque_peak = 0
    controller.prearm_stall_frames = 0
    controller.prearm_abort_lockout = 0
    controller.apply_torque_last = 0
    controller.rate_budget = SimpleNamespace(bounds=lambda *_: (-1000.0, 1000.0))
    return controller

  @staticmethod
  def _handoff_actuators(torque=0.0):
    return SimpleNamespace(torque=torque)

  @staticmethod
  def _handoff_car_state(*, speed=10.0, angle=0.0, rate=0.0, torque=0.0, pressed=False,
                         eac_status=1, eac_error_code=0, temporary_fault=False, permanent_fault=False):
    return SimpleNamespace(
      out=SimpleNamespace(
        vEgoRaw=speed,
        steeringAngleDeg=angle,
        steeringRateDeg=rate,
        steeringTorque=torque,
        steeringPressed=pressed,
        steerFaultTemporary=temporary_fault,
        steerFaultPermanent=permanent_fault,
      ),
      eac_status=eac_status,
      eac_error_code=eac_error_code,
    )

  def test_rx_dev_status_available_hands_off_hands_back_without_extra_delay(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state()

    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())

    assert not controller.torque_active

  def test_non_driver_recovery_does_not_inherit_25_degree_limit(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(speed=2.0, angle=50.0)

    controller._update_torque_active(car_state, True, 50.0, self._handoff_actuators())

    assert not controller.torque_active

  def test_galaxy_torque_to_angle_waits_until_wheel_is_under_25_degrees(self):
    controller = self._handoff_controller(torque_active=True)
    controller.galaxy_torque_recovery = True
    controller.hands_off_frames = 0
    car_state = self._handoff_car_state(speed=2.0, angle=ext_controller.HANDOFF_MAX_ANGLE_DEG)

    controller._update_torque_active(
      car_state,
      True,
      ext_controller.HANDOFF_MAX_ANGLE_DEG,
      self._handoff_actuators(),
    )

    assert controller.torque_active

    car_state.out.steeringAngleDeg = ext_controller.HANDOFF_MAX_ANGLE_DEG - 1.0
    controller._update_torque_active(
      car_state,
      True,
      ext_controller.HANDOFF_MAX_ANGLE_DEG - 1.0,
      self._handoff_actuators(),
    )

    assert not controller.torque_active
    assert not controller.galaxy_torque_recovery

  def test_route_opposing_reaction_torque_does_not_force_fallback_without_hands_on(self):
    controller = self._handoff_controller()
    # Route-derived signature from the first incident. rx-dev-src requires its
    # filtered hands-on signal in addition to steeringPressed.
    car_state = self._handoff_car_state(speed=6.85, angle=130.5, torque=-1.64, pressed=True)

    controller._update_torque_active(car_state, True, 135.7, self._handoff_actuators())

    assert not controller.torque_active

  def test_confirmed_driver_override_enters_torque_fallback(self):
    controller = self._handoff_controller()
    controller.hands_on = True
    car_state = self._handoff_car_state(torque=2.35, pressed=True)

    controller._update_torque_active(car_state, True, 15.0, self._handoff_actuators())

    assert controller.torque_active
    assert controller.driver_override_recovery

  def test_driver_override_requires_one_second_hands_off_before_angle_handback(self):
    controller = self._handoff_controller(torque_active=True)
    controller.driver_override_recovery = True
    controller.hands_off_frames = ext_controller.DRIVER_HANDS_OFF_EXIT_FRAMES - 1
    car_state = self._handoff_car_state(angle=0.0)

    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())

    assert controller.torque_active

    controller.hands_off_frames += 1
    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())

    assert not controller.torque_active
    assert not controller.driver_override_recovery

  def test_driver_override_does_not_hand_back_to_angle_mid_turn(self):
    controller = self._handoff_controller(torque_active=True)
    controller.driver_override_recovery = True
    car_state = self._handoff_car_state(angle=ext_controller.HANDOFF_MAX_ANGLE_DEG)

    controller._update_torque_active(
      car_state,
      True,
      ext_controller.HANDOFF_MAX_ANGLE_DEG,
      self._handoff_actuators(),
    )

    assert controller.torque_active

  def test_inertial_torsion_peak_is_rejected_while_column_is_swinging(self):
    controller = ExternalController.__new__(ExternalController)
    controller.torsion_cnt = 0
    controller.torsion_sign = 0
    controller.rate_hist = ext_controller.deque(
      [0.0] * ext_controller.TORSION_RATE_WINDOW,
      maxlen=ext_controller.TORSION_RATE_WINDOW,
    )

    for _ in range(20):
      assert not controller._update_torsion(8.0, 100.0, 4.0, 9)

    assert controller.torsion_cnt == 0

  def test_driver_torsion_is_detected_when_column_is_settled(self):
    controller = ExternalController.__new__(ExternalController)
    controller.torsion_cnt = 0
    controller.torsion_sign = 0
    controller.rate_hist = ext_controller.deque(
      [0.0] * ext_controller.TORSION_RATE_WINDOW,
      maxlen=ext_controller.TORSION_RATE_WINDOW,
    )

    detected = False
    for _ in range(10):
      detected = controller._update_torsion(4.1, 0.0, 4.0, 9)

    assert detected

  def test_strong_driver_override_bypasses_inertial_torsion_rejection(self):
    controller = ExternalController(self._car_params((0x1310,), gen2=True))
    car_state = SimpleNamespace(
      out=SimpleNamespace(
        steeringTorque=ext_controller.DRIVER_OVERRIDE_TORQUE + 0.1,
        steeringRateDeg=200.0,
        steeringPressed=True,
      ),
      sccm_wheel_touch=None,
      hands_on_level=0,
    )

    for _ in range(ext_controller.DRIVER_OVERRIDE_FRAMES - 1):
      controller._update_hands_on(car_state)
      assert not controller.hands_on

    controller._update_hands_on(car_state)

    assert controller.hands_on

  def test_light_torsion_presence_delays_driver_hands_off_timer(self):
    controller = ExternalController.__new__(ExternalController)
    controller.torsion_lpf = ext_controller.FirstOrderFilter(0.0, ext_controller.PRESENCE_LPF_RC, 0.01)
    controller.presence_cnt = 0
    controller.presence_sign = 0
    controller.presence_hold = 0

    presence = False
    for _ in range(ext_controller.PRESENCE_MIN_FRAMES + 20):
      presence = controller._update_torsion_presence(2.0)

    assert presence
    assert controller.presence_hold == ext_controller.PRESENCE_HOLD_FRAMES

  def test_gen2_hands_on_detection_does_not_require_sccm_message(self):
    controller = ExternalController(self._car_params((0x1310,), gen2=True))
    car_state = SimpleNamespace(
      out=SimpleNamespace(steeringTorque=0.0, steeringRateDeg=0.0),
      sccm_wheel_touch=None,
      hands_on_level=0,
    )

    controller._update_hands_on(car_state)

    assert not controller.hands_on

  def test_fresh_low_speed_engagement_starts_in_angle_when_epas_available(self):
    controller = self._handoff_controller(lat_active_last=False)
    car_state = self._handoff_car_state(speed=0.0)

    controller._update_torque_active(car_state, True, -25.4, self._handoff_actuators())

    assert not controller.torque_active

  def test_fresh_engagement_starts_in_torque_when_epas_not_available(self):
    controller = self._handoff_controller(lat_active_last=False)
    car_state = self._handoff_car_state(eac_status=0)

    controller._update_torque_active(car_state, True, -25.4, self._handoff_actuators())

    assert controller.torque_active

  def test_live_force_torque_prearms_before_releasing_angle(self):
    controller = self._handoff_controller()
    controller.force_torque = True
    car_state = self._handoff_car_state(eac_status=2)
    actuators = self._handoff_actuators(torque=0.5)

    controller._update_torque_active(car_state, True, 0.0, actuators)

    assert controller.torque_prearm
    assert not controller.torque_active

    steer_max = round(float(ext_controller.np.interp(
      car_state.out.vEgoRaw,
      ext_controller.CCP.STEER_MAX_LOOKUP[0],
      ext_controller.CCP.STEER_MAX_LOOKUP[1],
    )))
    controller.apply_torque_last = round(0.5 * steer_max)
    controller._update_torque_active(car_state, True, 0.0, actuators)

    assert controller.torque_active
    assert not controller.torque_prearm
    assert controller.galaxy_torque_recovery
    assert controller.prearm_last_outcome == "reached"

  def test_live_force_torque_prearm_ramps_with_eac_active(self):
    controller = self._handoff_controller()
    controller.force_torque = True
    controller.torque_cmd = 0
    controller.toi_act_cmd = False
    controller.toi_controller = ToiController()
    car_state = self._handoff_car_state(speed=33.8, eac_status=2)
    car_state.toi_fault = False
    car_state.toi_active = False
    car_state.toi_unavailable = False
    actuators = self._handoff_actuators(torque=0.103)

    for _ in range(10):
      controller._update_torque_active(car_state, True, 0.0, actuators)
      controller._update_torque(car_state, actuators)
      assert controller.toi_act_cmd
      assert controller.torque_cmd != 0
      assert not controller.toi_controller.recovery_failed
      if controller.torque_active:
        break

    assert controller.torque_active
    assert not controller.torque_prearm
    assert controller.prearm_last_outcome == "reached"
    assert controller.toi_controller.state == ToiState.ACTIVATING

    car_state.toi_active = True
    for _ in range(TOI_ACK_FRAMES):
      controller._update_torque(car_state, actuators)

    assert controller.toi_controller.state == ToiState.TORQUE
    assert controller.torque_cmd != 0

  def test_cancel_live_force_during_prearm_keeps_angle_active(self):
    controller = self._handoff_controller()
    controller.force_torque = True
    car_state = self._handoff_car_state(eac_status=2)
    actuators = self._handoff_actuators(torque=0.5)
    controller._update_torque_active(car_state, True, 0.0, actuators)
    assert controller.torque_prearm

    controller.force_torque = False
    controller._update_torque_active(car_state, True, 0.0, actuators)

    assert not controller.torque_prearm
    assert not controller.torque_active
    assert not controller.galaxy_torque_recovery

  def test_inhibited_no_error_rearms_once_after_continuous_release(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES - 1):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
      assert controller.torque_active

    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())

    assert not controller.torque_active
    assert controller.eac_rearm_attempted
    assert controller.eac_dead_frames == 1

  def test_inhibited_rearm_release_window_resets_on_driver_input(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES - 1):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())

    car_state.out.steeringPressed = True
    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert controller.eac_rearm_release_frames == 0
    assert controller.torque_active

    car_state.out.steeringPressed = False
    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert controller.eac_rearm_release_frames == 1
    assert controller.torque_active

  def test_failed_inhibited_rearm_falls_back_without_repeated_probes(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert not controller.torque_active

    for _ in range(ext_controller.EAC_RECOVER_FRAMES - 1):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
      assert not controller.torque_active
    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert controller.torque_active

    for _ in range(ext_controller.MIN_TORQUE_FRAMES + ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert controller.torque_active
    assert controller.eac_rearm_attempted

  def test_successful_inhibited_rearm_stays_in_angle(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert not controller.torque_active

    car_state.eac_status = 2
    controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())

    assert not controller.torque_active
    assert not controller.eac_rearm_attempted
    assert controller.eac_dead_frames == 0

  def test_inhibited_rearm_rejects_errors_and_faults(self):
    for state in (
      self._handoff_car_state(eac_status=0, eac_error_code=1),
      self._handoff_car_state(eac_status=3),
      self._handoff_car_state(eac_status=0, temporary_fault=True),
      self._handoff_car_state(eac_status=0, permanent_fault=True),
    ):
      controller = self._handoff_controller(torque_active=True)
      for _ in range(ext_controller.MIN_TORQUE_FRAMES + ext_controller.EAC_REARM_RELEASE_FRAMES):
        controller._update_torque_active(state, True, 0.0, self._handoff_actuators())
      assert controller.torque_active
      assert not controller.eac_rearm_attempted

  def test_inhibited_rearm_requires_settled_wheel_near_command(self):
    unsafe_states = (
      (self._handoff_car_state(eac_status=0, angle=100.0), 0.0),
      (self._handoff_car_state(eac_status=0, rate=ext_controller.UNWIND_HANDOFF_RATE), 0.0),
      (self._handoff_car_state(eac_status=0, angle=20.0), 0.0),
    )
    for state, desired_angle in unsafe_states:
      controller = self._handoff_controller(torque_active=True)
      for _ in range(ext_controller.MIN_TORQUE_FRAMES + ext_controller.EAC_REARM_RELEASE_FRAMES):
        controller._update_torque_active(state, True, desired_angle, self._handoff_actuators())
      assert controller.torque_active
      assert not controller.eac_rearm_attempted

  def test_inhibited_rearm_budget_resets_after_disengagement(self):
    controller = self._handoff_controller(torque_active=True)
    car_state = self._handoff_car_state(eac_status=0)

    for _ in range(ext_controller.EAC_REARM_RELEASE_FRAMES):
      controller._update_torque_active(car_state, True, 0.0, self._handoff_actuators())
    assert controller.eac_rearm_attempted

    controller._update_torque_active(car_state, False, 0.0, self._handoff_actuators())

    assert not controller.torque_active
    assert not controller.eac_rearm_attempted
