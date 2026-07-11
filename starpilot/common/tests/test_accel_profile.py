from openpilot.starpilot.common.accel_profile import (
  ACCELERATION_PROFILES,
  A_CRUISE_MAX_VALS_ECO_TRUCK,
  A_CRUISE_MAX_VALS_STANDARD_TRUCK,
  A_CRUISE_MAX_VALS_SPORT_PLUS_TRUCK,
  A_CRUISE_MAX_VALS_SPORT_TRUCK,
  get_accel_profile_curve_values,
  interpolate_accel_profile,
)


def test_truck_curves_match_expected_values():
  assert get_accel_profile_curve_values(ACCELERATION_PROFILES["ECO"], ev_tuning=False, truck_tuning=True) == A_CRUISE_MAX_VALS_ECO_TRUCK
  values = get_accel_profile_curve_values(ACCELERATION_PROFILES["STANDARD"], ev_tuning=False, truck_tuning=True)
  assert values == A_CRUISE_MAX_VALS_STANDARD_TRUCK
  assert get_accel_profile_curve_values(ACCELERATION_PROFILES["SPORT"], ev_tuning=False, truck_tuning=True) == A_CRUISE_MAX_VALS_SPORT_TRUCK
  assert get_accel_profile_curve_values(ACCELERATION_PROFILES["SPORT_PLUS"], ev_tuning=False, truck_tuning=True) == A_CRUISE_MAX_VALS_SPORT_PLUS_TRUCK


def test_standard_truck_curve_keeps_mid_high_speed_authority():
  values = get_accel_profile_curve_values(ACCELERATION_PROFILES["STANDARD"], ev_tuning=False, truck_tuning=True)

  assert interpolate_accel_profile(20.0, values) >= 1.18
  assert interpolate_accel_profile(25.0, values) >= 0.98
  assert interpolate_accel_profile(30.0, values) >= 0.90


def test_truck_profiles_remain_ordered():
  eco = get_accel_profile_curve_values(ACCELERATION_PROFILES["ECO"], ev_tuning=False, truck_tuning=True)
  standard = get_accel_profile_curve_values(ACCELERATION_PROFILES["STANDARD"], ev_tuning=False, truck_tuning=True)
  sport = get_accel_profile_curve_values(ACCELERATION_PROFILES["SPORT"], ev_tuning=False, truck_tuning=True)
  sport_plus = get_accel_profile_curve_values(ACCELERATION_PROFILES["SPORT_PLUS"], ev_tuning=False, truck_tuning=True)

  for e, s, sp, spp in zip(eco, standard, sport, sport_plus, strict=True):
    assert e < s < sp < spp
