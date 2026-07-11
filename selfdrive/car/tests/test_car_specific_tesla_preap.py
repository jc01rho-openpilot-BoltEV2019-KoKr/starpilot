from unittest.mock import PropertyMock, patch  # noqa: TID251

from cereal import car, custom

from openpilot.selfdrive.selfdrived.events import Events
from openpilot.selfdrive.selfdrived.selfdrived import add_tesla_preap_starpilot_events


StarPilotEventName = custom.StarPilotOnroadEvent.EventName
NAP_CONF_PATH = "opendbc.car.tesla.preap.nap_conf.NAPConf.pedal_calibrated"


def _make_cp(*, fingerprint="TESLA_MODEL_S_PREAP", brand="tesla", pcm_cruise=False, op_long=True):
  cp = car.CarParams.new_message()
  cp.carFingerprint = fingerprint
  cp.brand = brand
  cp.pcmCruise = pcm_cruise
  cp.openpilotLongitudinalControl = op_long
  return cp


def _make_cs():
  cs = car.CarState.new_message()
  cs.cruiseState.available = True
  cs.gearShifter = "drive"
  return cs


def _run(cp, calibrated):
  with patch(NAP_CONF_PATH, new_callable=PropertyMock, return_value=calibrated):
    events = Events(starpilot=True)
    add_tesla_preap_starpilot_events(cp, _make_cs(), custom.StarPilotCarState.new_message(), events, False)
  return events.names


def test_fires_in_preap_pedal_mode_when_uncalibrated():
  cp = _make_cp(pcm_cruise=False, op_long=True)
  assert StarPilotEventName.pedalNotCalibrated in _run(cp, calibrated=False)


def test_silent_in_preap_pedal_mode_when_calibrated():
  cp = _make_cp(pcm_cruise=False, op_long=True)
  assert StarPilotEventName.pedalNotCalibrated not in _run(cp, calibrated=True)


def test_silent_in_preap_nopedal_mode_even_when_uncalibrated():
  cp = _make_cp(pcm_cruise=True, op_long=False)
  assert StarPilotEventName.pedalNotCalibrated not in _run(cp, calibrated=False)


def test_silent_on_non_preap_tesla():
  cp = _make_cp(fingerprint="TESLA_MODEL_S", pcm_cruise=False, op_long=True)
  assert StarPilotEventName.pedalNotCalibrated not in _run(cp, calibrated=False)


def test_silent_on_non_tesla_brand():
  cp = _make_cp(fingerprint="HONDA_CIVIC_2022", brand="honda", pcm_cruise=True, op_long=False)
  assert StarPilotEventName.pedalNotCalibrated not in _run(cp, calibrated=False)
