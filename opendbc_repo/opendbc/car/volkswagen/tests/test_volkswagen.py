import random
import re

from opendbc.car.structs import CarParams
from opendbc.car.volkswagen.interface import CarInterface
from opendbc.car.volkswagen.values import CAR, FW_QUERY_CONFIG, WMI, VolkswagenFlags, VolkswagenSafetyFlags
from opendbc.car.volkswagen.fingerprints import FW_VERSIONS

Ecu = CarParams.Ecu

CHASSIS_CODE_PATTERN = re.compile('[A-Z0-9]{2}')
# TODO: determine the unknown groups
SPARE_PART_FW_PATTERN = re.compile(b'\xf1\x87(?P<gateway>[0-9][0-9A-Z]{2})(?P<unknown>[0-9][0-9A-Z][0-9])(?P<unknown2>[0-9A-Z]{2}[0-9])([A-Z0-9]| )')


class TestVolkswagenPlatformConfigs:
  MEB_CARS = {car for car in CAR if car.config.flags & VolkswagenFlags.MEB}

  @staticmethod
  def _get_meb_params(car, gateway=True, alpha_long=False):
    fingerprint = {bus: {} for bus in range(8)}
    if gateway:
      fingerprint[1][0x13D] = 32
    return CarInterface.get_params(car, fingerprint, [], alpha_long, False, False, None)

  def test_meb_platform_params(self):
    for car in self.MEB_CARS:
      cp = self._get_meb_params(car)
      assert cp.flags & VolkswagenFlags.MEB
      assert cp.transmissionType == CarParams.TransmissionType.direct
      assert cp.steerControlType == CarParams.SteerControlType.curvatureDEPRECATED
      assert cp.steerAtStandstill
      assert cp.safetyConfigs[-1].safetyModel == CarParams.SafetyModel.volkswagenMeb
      assert not cp.dashcamOnly
      assert not cp.radarUnavailable

      has_gen2_crc = bool(cp.safetyConfigs[-1].safetyParam & VolkswagenSafetyFlags.MEB_ALT_CRC)
      assert has_gen2_crc == bool(car.config.flags & VolkswagenFlags.MEB_GEN2)

  def test_meb_camera_harness_is_passive(self):
    cp = self._get_meb_params(CAR.VOLKSWAGEN_ID4_MK1, gateway=False, alpha_long=True)
    assert cp.dashcamOnly
    assert cp.radarUnavailable
    assert not cp.alphaLongitudinalAvailable
    assert not cp.openpilotLongitudinalControl
    assert not (cp.safetyConfigs[-1].safetyParam & VolkswagenSafetyFlags.LONG_CONTROL)

  def test_meb_docs_assume_required_gateway_harness(self):
    fingerprint = {bus: {} for bus in range(8)}
    cp = CarInterface.get_params(CAR.VOLKSWAGEN_ID4_MK1, fingerprint, [], True, False, True, None)

    assert cp.networkLocation == CarParams.NetworkLocation.gateway
    assert not cp.dashcamOnly
    assert cp.alphaLongitudinalAvailable

  def test_meb_gateway_longitudinal(self):
    cp = self._get_meb_params(CAR.VOLKSWAGEN_ID4_MK1, gateway=True, alpha_long=True)
    assert cp.alphaLongitudinalAvailable
    assert cp.openpilotLongitudinalControl
    assert not cp.pcmCruise
    assert cp.safetyConfigs[-1].safetyParam & VolkswagenSafetyFlags.LONG_CONTROL

  def test_taos_longitudinal_actuator_delay(self):
    taos_cp = CarInterface.get_non_essential_params(CAR.VOLKSWAGEN_TAOS_MK1)
    golf_cp = CarInterface.get_non_essential_params(CAR.VOLKSWAGEN_GOLF_MK7)

    assert abs(taos_cp.longitudinalActuatorDelay - 0.25) < 1e-6
    assert abs(golf_cp.longitudinalActuatorDelay - 0.15) < 1e-6

  def test_spare_part_fw_pattern(self, subtests):
    # Relied on for determining if a FW is likely VW
    for platform, ecus in FW_VERSIONS.items():
      with subtests.test(platform=platform.value):
        for fws in ecus.values():
          for fw in fws:
            assert SPARE_PART_FW_PATTERN.match(fw) is not None, f"Bad FW: {fw}"

  def test_chassis_codes(self, subtests):
    for platform in CAR:
      with subtests.test(platform=platform.value):
        assert len(platform.config.wmis) > 0, "WMIs not set"
        assert len(platform.config.chassis_codes) > 0, "Chassis codes not set"
        assert all(CHASSIS_CODE_PATTERN.match(cc) for cc in
                   platform.config.chassis_codes), "Bad chassis codes"

        # Shared MEB chassis codes are valid only when VIN model-year sets are disjoint.
        for comp in CAR:
          if platform == comp:
            continue
          shared_chassis = platform.config.chassis_codes & comp.config.chassis_codes
          if shared_chassis:
            both_meb = platform.config.flags & VolkswagenFlags.MEB and comp.config.flags & VolkswagenFlags.MEB
            disjoint_years = (getattr(platform.config, "model_years", set()) and getattr(comp.config, "model_years", set()) and
                              not platform.config.model_years & comp.config.model_years)
            assert both_meb and disjoint_years, f"Shared chassis codes: {comp}"

  def test_custom_fuzzy_fingerprinting(self, subtests):
    all_radar_fw = list({fw for ecus in FW_VERSIONS.values() for fw in ecus[Ecu.fwdRadar, 0x757, None]})

    for platform in CAR:
      with subtests.test(platform=platform.name):
        model_years = getattr(platform.config, "model_years", set()) or {"0"}
        for wmi in WMI:
          for chassis_code in platform.config.chassis_codes | {"00"}:
            for model_year in model_years:
              vin = ["0"] * 17
              vin[0:3] = wmi
              vin[6:8] = chassis_code
              vin[9] = model_year
              vin = "".join(vin)

              # Check a few FW cases - expected, unexpected
              for radar_fw in random.sample(all_radar_fw, 5) + [b'\xf1\x875Q0907572G \xf1\x890571', b'\xf1\x877H9907572AA\xf1\x890396']:
                should_match = ((wmi in platform.config.wmis and chassis_code in platform.config.chassis_codes) and
                                radar_fw in all_radar_fw)

                live_fws = {(0x757, None): [radar_fw]}
                matches = FW_QUERY_CONFIG.match_fw_to_car_fuzzy(live_fws, vin, FW_VERSIONS)

                expected_matches = {platform} if should_match else set()
                assert expected_matches == matches, "Bad match"
