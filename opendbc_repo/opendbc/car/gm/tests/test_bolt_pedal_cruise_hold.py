"""Bolt pedal cruise behavior ported from paddle5: cruise-trim pass-through and cruise-hold error filtering."""

import numpy as np
import pytest

from opendbc.car import DT_CTRL
from opendbc.car.gm.carcontroller import bolt_pedal_fraction
from opendbc.car.gm.conventional_pedal import GMConventionalPedalPolicy
from opendbc.car.gm.longitudinal import GMPedalLongitudinalPolicy

HIGHWAY = 80.0 / 3.6


@pytest.mark.parametrize("speed", [15.0, HIGHWAY, 35.0])
@pytest.mark.parametrize("accel", [-0.15, -0.04, 0.0, 0.04, 0.15])
def test_cruise_trim_is_continuous_at_road_speed(speed, accel):
  below = bolt_pedal_fraction(accel - 1e-6, speed, False, cruise_trim=True)
  above = bolt_pedal_fraction(accel + 1e-6, speed, False, cruise_trim=True)
  assert abs(above - below) < 1e-5


def test_cruise_trim_preserves_sign_and_monotonicity():
  requests = np.linspace(-0.15, 0.15, 301)
  outputs = [bolt_pedal_fraction(float(a), HIGHWAY, False, cruise_trim=True) for a in requests]
  assert all(cur > prev for prev, cur in zip(outputs[:-1], outputs[1:], strict=True))


def test_cruise_trim_passes_small_commands_proportionally():
  neutral = bolt_pedal_fraction(0.0, HIGHWAY, False, cruise_trim=True)
  half = bolt_pedal_fraction(0.02, HIGHWAY, False, cruise_trim=True)
  full = bolt_pedal_fraction(0.04, HIGHWAY, False, cruise_trim=True)
  assert (half - neutral) == pytest.approx((full - neutral) / 2, rel=0.05)


@pytest.mark.parametrize("speed", [0.3, 5.0, 8.0])
@pytest.mark.parametrize("accel", [-0.05, -0.0399, 0.0399, 0.05])
def test_cruise_trim_keeps_creep_deadband_at_low_speed(speed, accel):
  assert bolt_pedal_fraction(accel, speed, False, cruise_trim=True) == bolt_pedal_fraction(accel, speed, False)


@pytest.mark.parametrize("speed", [0.3, 8.0, HIGHWAY])
@pytest.mark.parametrize("accel", [-2.5, -0.15, 0.15, 1.4])
def test_cruise_trim_does_not_change_larger_requests(speed, accel):
  assert bolt_pedal_fraction(accel, speed, False, cruise_trim=True) == bolt_pedal_fraction(accel, speed, False)


def test_default_keeps_small_command_deadband():
  outputs = [bolt_pedal_fraction(a, HIGHWAY, False) for a in (-0.0399, 0.0, 0.0399)]
  assert outputs[0] == outputs[1] == outputs[2]


@pytest.mark.parametrize("speed", [8.0, 15.0])
@pytest.mark.parametrize("accel", [-0.04, -0.02, 0.02, 0.04])
def test_cruise_trim_blend_is_continuous_across_speed_boundaries(speed, accel):
  below = bolt_pedal_fraction(accel, speed - 1e-6, False, cruise_trim=True)
  above = bolt_pedal_fraction(accel, speed + 1e-6, False, cruise_trim=True)
  assert abs(above - below) < 1e-5


def _noisy_errors(policy, target, frames=300, amplitude=0.3):
  return [policy.error(target, target + amplitude * np.sin(2.0 * np.pi * 5.0 * frame * DT_CTRL)) for frame in range(frames)]


def test_cruise_hold_error_rejects_sensor_noise():
  filtered = _noisy_errors(GMPedalLongitudinalPolicy(False), 0.0)[100:]
  raw = [-0.3 * np.sin(2.0 * np.pi * 5.0 * frame * DT_CTRL) for frame in range(300)][100:]
  assert np.max(np.abs(filtered)) < 0.25 * np.max(np.abs(raw))


def test_cruise_hold_error_keeps_dc_residual_for_integrator():
  policy = GMPedalLongitudinalPolicy(False)
  errors = [policy.error(0.0, -0.05) for _ in range(300)]
  assert errors[-1] == pytest.approx(0.05, abs=1e-3)


@pytest.mark.parametrize("target", [0.6, -1.3, -2.5])
def test_dynamic_and_hard_braking_targets_use_raw_a_ego(target):
  policy = GMPedalLongitudinalPolicy(False)
  for _ in range(100):
    policy.error(target, 0.0)
  assert policy.error(target, 0.4) == pytest.approx(target - 0.4)


def test_lead_following_decel_stays_partially_filtered():
  policy = GMPedalLongitudinalPolicy(False)
  for _ in range(100):
    policy.error(-0.8, 0.0)
  error = policy.error(-0.8, 0.4)
  assert -0.8 - 0.4 < error < -0.8


def test_reset_reseeds_filter_from_next_sample():
  policy = GMPedalLongitudinalPolicy(False)
  for _ in range(100):
    policy.error(0.0, 1.0)
  policy.reset()
  assert policy.error(0.0, -0.2) == pytest.approx(0.2)


def test_conventional_pedal_profiles_keep_raw_error():
  policy = GMConventionalPedalPolicy(malibu=True)
  assert policy.error(0.0, 0.3) == pytest.approx(-0.3)
