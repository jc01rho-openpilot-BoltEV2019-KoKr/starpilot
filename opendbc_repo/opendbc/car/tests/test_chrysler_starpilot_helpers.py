from types import SimpleNamespace

from opendbc.car.chrysler.carcontroller import (
  JEEP_BRAKE_HOLD_DEFAULT_DECEL,
  clip_jeep_brake_hold_decel,
  supports_jeep_brake_hold,
)
from opendbc.car.chrysler.values import CAR, ChryslerSafetyFlags, JEEPS


def test_jeep_group_is_grand_cherokee_only():
  assert JEEPS == {CAR.JEEP_GRAND_CHEROKEE, CAR.JEEP_GRAND_CHEROKEE_2019}


def test_jeep_brake_hold_support_requires_toggle_jeep_pcm_and_safety_flag():
  safety = [SimpleNamespace(safetyParam=ChryslerSafetyFlags.JEEP_BRAKE_HOLD.value)]
  no_safety = [SimpleNamespace(safetyParam=0)]

  assert supports_jeep_brake_hold(SimpleNamespace(
    carFingerprint=CAR.JEEP_GRAND_CHEROKEE,
    pcmCruise=True,
    safetyConfigs=safety,
  ), True)
  assert not supports_jeep_brake_hold(SimpleNamespace(
    carFingerprint=CAR.JEEP_GRAND_CHEROKEE,
    pcmCruise=True,
    safetyConfigs=no_safety,
  ), True)
  assert not supports_jeep_brake_hold(SimpleNamespace(
    carFingerprint=CAR.JEEP_GRAND_CHEROKEE,
    pcmCruise=False,
    safetyConfigs=safety,
  ), True)
  assert not supports_jeep_brake_hold(SimpleNamespace(
    carFingerprint=CAR.CHRYSLER_PACIFICA_2018,
    pcmCruise=True,
    safetyConfigs=safety,
  ), True)
  assert not supports_jeep_brake_hold(SimpleNamespace(
    carFingerprint=CAR.JEEP_GRAND_CHEROKEE,
    pcmCruise=True,
    safetyConfigs=safety,
  ), False)


def test_jeep_brake_hold_decel_is_bounded():
  assert clip_jeep_brake_hold_decel(JEEP_BRAKE_HOLD_DEFAULT_DECEL) == JEEP_BRAKE_HOLD_DEFAULT_DECEL
  assert clip_jeep_brake_hold_decel(-8.0) == -3.0
  assert clip_jeep_brake_hold_decel(0.5) == -0.5
