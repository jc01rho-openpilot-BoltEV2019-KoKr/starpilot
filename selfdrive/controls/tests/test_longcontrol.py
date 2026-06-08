from types import SimpleNamespace

from cereal import car
import pytest

import openpilot.selfdrive.controls.lib.longcontrol as longcontrol
from openpilot.selfdrive.controls.lib.longcontrol import LongControl, LongCtrlState, long_control_state_trans


def make_toggles(**overrides):
  defaults = {
    "custom_accel_profile": False,
    "human_acceleration": False,
    "startAccel": 1.5,
    "stopAccel": -0.5,
    "stoppingDecelRate": 0.8,
    "vEgoStarting": 0.5,
    "vEgoStopping": 0.5,
  }
  defaults.update(overrides)
  return SimpleNamespace(**defaults)


class TestLongControlStateTransition:

  def test_stay_stopped(self):
    CP = car.CarParams.new_message()
    toggles = make_toggles()
    active = True
    current_state = LongCtrlState.stopping
    next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=True, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
    assert next_state == LongCtrlState.stopping
    next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=False, brake_pressed=True, cruise_standstill=False, starpilot_toggles=toggles)
    assert next_state == LongCtrlState.stopping
    next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=False, brake_pressed=False, cruise_standstill=True, starpilot_toggles=toggles,
                             allow_stopping_release=False)
    assert next_state == LongCtrlState.stopping
    next_state = long_control_state_trans(CP, active, current_state, v_ego=1.0,
                             should_stop=False, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
    assert next_state == LongCtrlState.pid
    active = False
    next_state = long_control_state_trans(CP, active, current_state, v_ego=1.0,
                             should_stop=False, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
    assert next_state == LongCtrlState.off


def test_engage():
  CP = car.CarParams.new_message()
  toggles = make_toggles()
  active = True
  current_state = LongCtrlState.off
  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=True, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
  assert next_state == LongCtrlState.stopping
  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=False, brake_pressed=True, cruise_standstill=False, starpilot_toggles=toggles)
  assert next_state == LongCtrlState.stopping
  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=False, brake_pressed=False, cruise_standstill=True, starpilot_toggles=toggles)
  assert next_state == LongCtrlState.stopping
  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=False, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
  assert next_state == LongCtrlState.pid


def test_starting():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  toggles = make_toggles(vEgoStarting=0.5)
  active = True
  current_state = LongCtrlState.starting
  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.1,
                             should_stop=False, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
  assert next_state == LongCtrlState.starting
  next_state = long_control_state_trans(CP, active, current_state, v_ego=1.0,
                             should_stop=False, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles)
  assert next_state == LongCtrlState.pid


def test_stopping_release_hysteresis_blocks_immediate_launch():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  toggles = make_toggles(vEgoStarting=0.5)
  active = True
  current_state = LongCtrlState.stopping

  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.0,
                             should_stop=False, brake_pressed=False, cruise_standstill=False, starpilot_toggles=toggles,
                             allow_stopping_release=False)
  assert next_state == LongCtrlState.stopping


def test_stopping_release_allows_launch_while_cruise_standstill_latched():
  CP = car.CarParams.new_message()
  toggles = make_toggles(vEgoStarting=0.5)
  active = True
  current_state = LongCtrlState.stopping

  next_state = long_control_state_trans(CP, active, current_state, v_ego=0.0,
                             should_stop=False, brake_pressed=False, cruise_standstill=True, starpilot_toggles=toggles,
                             allow_stopping_release=True)
  assert next_state == LongCtrlState.pid


def test_starting_accel_unchanged_when_custom_profile_disabled():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  CS = car.CarState.new_message(vEgo=0.0, aEgo=0.0, brakePressed=False)
  CS.cruiseState.standstill = False

  output_accel = lc.update(
    active=True,
    CS=CS,
    a_target=0.1,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(startAccel=1.5),
  )

  assert lc.long_control_state == LongCtrlState.starting
  assert output_accel == 1.5


def test_starting_accel_obeys_a_target_cap_when_custom_profile_enabled():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  CS = car.CarState.new_message(vEgo=0.0, aEgo=0.0, brakePressed=False)
  CS.cruiseState.standstill = False

  output_accel = lc.update(
    active=True,
    CS=CS,
    a_target=0.1,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(startAccel=1.5, custom_accel_profile=True),
  )

  assert lc.long_control_state == LongCtrlState.starting
  assert output_accel == 0.1


def test_update_requires_sustained_positive_target_to_leave_stopping():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  lc.long_control_state = LongCtrlState.stopping
  CS = car.CarState.new_message(vEgo=0.0, aEgo=0.0, brakePressed=False)
  CS.cruiseState.standstill = False

  release_frames = int(round(longcontrol.STOPPING_RELEASE_HYSTERESIS / longcontrol.DT_CTRL))
  for _ in range(release_frames - 1):
    output_accel = lc.update(
      active=True,
      CS=CS,
      a_target=0.5,
      should_stop=False,
      accel_limits=(-3.0, 2.0),
      starpilot_toggles=make_toggles(startAccel=1.5),
    )
    assert lc.long_control_state == LongCtrlState.stopping
    assert output_accel <= 0.0

  lc.update(
    active=True,
    CS=CS,
    a_target=0.5,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(startAccel=1.5),
  )

  assert lc.long_control_state == LongCtrlState.starting


def test_update_releases_stopping_on_small_sustained_positive_target():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  lc.long_control_state = LongCtrlState.stopping
  CS = car.CarState.new_message(vEgo=0.0, aEgo=0.0, brakePressed=False)
  CS.cruiseState.standstill = False

  release_frames = int(round(longcontrol.STOPPING_RELEASE_HYSTERESIS / longcontrol.DT_CTRL))
  for _ in range(release_frames - 1):
    output_accel = lc.update(
      active=True,
      CS=CS,
      a_target=0.16,
      should_stop=False,
      accel_limits=(-3.0, 2.0),
      starpilot_toggles=make_toggles(startAccel=1.5),
    )
    assert lc.long_control_state == LongCtrlState.stopping
    assert output_accel <= 0.0

  lc.update(
    active=True,
    CS=CS,
    a_target=0.16,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(startAccel=1.5),
  )

  assert lc.long_control_state == LongCtrlState.starting


def test_update_releases_stopping_with_cruise_standstill_latched():
  CP = car.CarParams.new_message(vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  lc.long_control_state = LongCtrlState.stopping
  lc.last_output_accel = -2.003
  CS = car.CarState.new_message(vEgo=0.0, aEgo=0.0, brakePressed=False)
  CS.cruiseState.standstill = True

  release_frames = int(round(longcontrol.STOPPING_RELEASE_HYSTERESIS / longcontrol.DT_CTRL))
  for _ in range(release_frames - 1):
    output_accel = lc.update(
      active=True,
      CS=CS,
      a_target=0.5,
      should_stop=False,
      accel_limits=(-3.0, 2.0),
      starpilot_toggles=make_toggles(startAccel=1.5),
    )
    assert lc.long_control_state == LongCtrlState.stopping
    assert output_accel <= 0.0

  output_accel = lc.update(
    active=True,
    CS=CS,
    a_target=0.5,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(startAccel=1.5),
  )

  assert lc.long_control_state == LongCtrlState.pid
  assert output_accel > 0.0


def test_stopping_state_follows_stronger_moving_stop_target():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  lc.long_control_state = LongCtrlState.stopping
  lc.last_output_accel = -1.40
  CS = car.CarState.new_message(vEgo=4.0, aEgo=-1.2, brakePressed=False)
  CS.cruiseState.standstill = False

  output_accel = lc.update(
    active=True,
    CS=CS,
    a_target=-3.5,
    should_stop=True,
    accel_limits=(-3.5, 2.0),
    starpilot_toggles=make_toggles(stopAccel=-0.5, stoppingDecelRate=0.8, vEgoStopping=0.5),
  )

  assert lc.long_control_state == LongCtrlState.stopping
  assert output_accel < -1.43


def test_volt_testing_ground_handoff_freezes_integrator(monkeypatch):
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = True
  CP.carFingerprint = "CHEVROLET_VOLT_ASCM"
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  monkeypatch.setattr(longcontrol, "testing_ground", SimpleNamespace(use_2=True))

  lc = LongControl(CP)
  freeze = lc._get_pedal_long_freeze(a_target=0.7, error=0.7, v_ego=8.0, accel_limits=(-3.0, 2.0))

  assert freeze
  assert lc.integrator_hold_frames > 0


def test_non_interceptor_volt_testing_ground_handoff_freezes_integrator(monkeypatch):
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = False
  CP.carFingerprint = "CHEVROLET_VOLT_ASCM"
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  monkeypatch.setattr(longcontrol, "testing_ground", SimpleNamespace(use_2=True))

  lc = LongControl(CP)
  freeze = lc._get_pedal_long_freeze(a_target=0.7, error=0.7, v_ego=8.0, accel_limits=(-3.0, 2.0))

  assert freeze
  assert lc.integrator_hold_frames > 0


def test_negative_target_unwinds_positive_accel_command_after_sign_flip():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  lc.long_control_state = LongCtrlState.pid
  lc.last_output_accel = 1.2
  lc.pid.i = 1.2
  CS = car.CarState.new_message(vEgo=30.0, aEgo=0.9, brakePressed=False, gasPressed=False)
  CS.cruiseState.standstill = False

  output_accel = lc.update(
    active=True,
    CS=CS,
    a_target=-0.5,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(),
  )

  assert lc.long_control_state == LongCtrlState.pid
  assert output_accel <= 0.01


def test_negative_target_unwinds_positive_accel_command_at_low_speed():
  CP = car.CarParams.new_message(startingState=True, vEgoStarting=0.5)
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  lc.long_control_state = LongCtrlState.pid
  lc.last_output_accel = 0.9
  lc.pid.i = 0.9
  CS = car.CarState.new_message(vEgo=1.3, aEgo=0.35, brakePressed=False, gasPressed=False)
  CS.cruiseState.standstill = False

  output_accel = lc.update(
    active=True,
    CS=CS,
    a_target=-1.2,
    should_stop=False,
    accel_limits=(-3.0, 2.0),
    starpilot_toggles=make_toggles(),
  )

  assert lc.long_control_state == LongCtrlState.pid
  assert output_accel <= 0.01


def test_negative_target_creep_guard_keeps_mild_crawl_request():
  capped = LongControl._cap_positive_output_on_negative_target(
    output_accel=0.18,
    a_target=-0.2,
    error=-0.5,
    CS=car.CarState.new_message(vEgo=0.2, aEgo=0.0),
  )

  assert capped == pytest.approx(0.18)


def test_pedal_long_brake_bias_adds_small_negative_nudge_for_strong_decel_request():
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = True
  CP.flags = 1
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  CS = car.CarState.new_message(vEgo=20.0, aEgo=0.0, brakePressed=False)

  biased = lc._apply_pedal_long_brake_bias(-1.0, -3.0, CS)

  assert biased < -1.0
  assert biased == pytest.approx(-1.15, abs=0.03)


def test_pedal_long_brake_bias_does_not_touch_non_pedal_or_mild_decel():
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = False
  CP.flags = 0
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]

  lc = LongControl(CP)
  CS = car.CarState.new_message(vEgo=20.0, aEgo=0.0, brakePressed=False)

  assert lc._apply_pedal_long_brake_bias(-1.0, -3.0, CS) == -1.0
  assert lc._apply_pedal_long_brake_bias(-0.4, -0.6, CS) == -0.4


def test_d_term_zero_when_kd_not_configured():
  """D-term should return 0 when kdV is empty or not configured."""
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = True
  CP.flags = 1
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]
  # kdV not set or empty

  lc = LongControl(CP)
  CS = car.CarState.new_message(vEgo=20.0, aEgo=0.0, brakePressed=False)

  # Call private method directly
  d = lc._compute_d_term(0.5, 20.0)
  assert d == 0.0


def test_d_term_derivative_on_measurement_no_kick():
  """D-term should use Derivative on Measurement (DOM): -d(aEgo)/dt.
  Setpoint changes should NOT produce derivative kick."""
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = True
  CP.flags = 1
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]
  CP.longitudinalTuning.kdBP = [0.0, 5.0, 15.0, 35.0]
  CP.longitudinalTuning.kdV = [0.02, 0.02, 0.02, 0.02]

  lc = LongControl(CP)
  lc.d_term_active = True

  # Same aEgo, different a_target → should NOT affect D-term (DOM)
  d1 = lc._compute_d_term(1.0, 20.0)  # a_target=1.0
  d2 = lc._compute_d_term(-1.0, 20.0)  # a_target=-1.0 (step change)
  
  # D-term should be identical (within small float tolerance) since aEgo same
  assert abs(d1 - d2) < 0.01


def test_d_term_noise_rejection():
  """D-term should attenuate high-frequency noise on aEgo.
  5Hz sine noise (±0.5 m/s²) should produce D-term < 0.05 m/s²."""
  import numpy as np
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = True
  CP.flags = 1
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]
  CP.longitudinalTuning.kdBP = [0.0, 5.0, 15.0, 35.0]
  CP.longitudinalTuning.kdV = [0.02, 0.02, 0.02, 0.02]

  lc = LongControl(CP)
  lc.d_term_active = True

  DT_CTRL = 0.01
  max_d = 0.0
  
  # Inject 5Hz sine noise on aEgo (±0.5 m/s²)
  for i in range(1000):
    t = i * DT_CTRL
    aEgo_noisy = 0.5 * np.sin(2 * np.pi * 5 * t)
    d = lc._compute_d_term(aEgo_noisy, 20.0)
    max_d = max(max_d, abs(d))
  
  # With cascaded LPF (0.05s + 0.02s = 3.2Hz + 8Hz), 5Hz should be attenuated
  assert max_d < 0.05


def test_aego_filter_tracks_acceleration():
  """aEgo filter should track real acceleration changes (low frequency)."""
  import numpy as np
  CP = car.CarParams.new_message()
  CP.brand = "gm"
  CP.enableGasInterceptorDEPRECATED = True
  CP.flags = 1
  CP.longitudinalTuning.kpBP = [0.0]
  CP.longitudinalTuning.kpV = [0.1]
  CP.longitudinalTuning.kiBP = [0.0]
  CP.longitudinalTuning.kiV = [0.03]
  CP.longitudinalTuning.kdBP = [0.0, 5.0, 15.0, 35.0]
  CP.longitudinalTuning.kdV = [0.02, 0.02, 0.02, 0.02]

  lc = LongControl(CP)
  lc.d_term_active = True

  # Ramp acceleration: 0.0 -> 2.0 m/s² over 2 seconds
  DT_CTRL = 0.01
  aEgo = 0.0
  target_aEgo = 2.0
  rate = target_aEgo / 2.0  # 1.0 m/s³
  
  for i in range(200):
    aEgo += rate * DT_CTRL
    d = lc._compute_d_term(aEgo, 20.0)
    # D-term should be approximately -kd * rate = -0.02 * 1.0 = -0.02
    if i > 50:  # After filter settles
      assert abs(d - (-0.02)) < 0.01
