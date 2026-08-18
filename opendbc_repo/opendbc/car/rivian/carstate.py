import copy
from cereal import custom
from opendbc.can import CANParser
from opendbc.car import Bus, structs
from opendbc.car.interfaces import CarStateBase
from opendbc.car.rivian.carstate_ext import RivianLongitudinalState
from opendbc.car.rivian.faults import TOI_FAULT_ALERT_FRAMES, get_steering_faults
from opendbc.car.rivian.values import DBC, GEAR_MAP, RivianFlags
from opendbc.car.common.conversions import Conversions as CV

GearShifter = structs.CarState.GearShifter


def get_cruise_available(flags: int, acm_feature_status: int) -> bool:
  # VDM reports unavailable until after stock ACC activates, so it cannot gate
  # the PCM enable edge. The ACM reports standby before activation and ACC once active.
  return bool(flags & RivianFlags.LONGITUDINAL_HARNESS) or acm_feature_status in (0, 1)


class CarState(CarStateBase):
  def __init__(self, CP, FPCP):
    super().__init__(CP, FPCP)
    self.last_speed = 30
    self.longitudinal_state = RivianLongitudinalState(CP)

    self.acm_lka_hba_cmd: dict | None = None
    self.sccm_wheel_touch: dict | None = None
    self.vdm_adas_status: list[dict] = []
    self.hands_on_level = 0
    self.eac_status = 0
    self.eac_error_code = 0
    self.toi_fault = False
    self.toi_active = False
    self.toi_unavailable = False
    self.toi_fault_frames = 0

  def update(self, can_parsers, starpilot_toggles) -> structs.CarState:
    cp = can_parsers[Bus.pt]
    cp_cam = can_parsers[Bus.cam]
    cp_adas = can_parsers[Bus.adas]
    ret = structs.CarState()

    # Vehicle speed
    ret.vEgoRaw = cp.vl["ESP_Status"]["ESP_Vehicle_Speed"] * CV.KPH_TO_MS
    ret.vEgo, ret.aEgo = self.update_speed_kf(ret.vEgoRaw)
    ret.standstill = abs(ret.vEgoRaw) < 0.01
    conversion = CV.KPH_TO_MS if cp_adas.vl["Cluster"]["Cluster_Unit"] == 0 else CV.MPH_TO_MS
    ret.vEgoCluster = cp_adas.vl["Cluster"]["Cluster_VehicleSpeed"] * conversion

    # Gas pedal
    ret.gasPressed = cp.vl["VDM_PropStatus"]["VDM_AcceleratorPedalPosition"] > 0

    # Brake pedal
    ret.brake = cp.vl["ESPiB3"]["ESPiB3_pMC1"] / 250.0  # pressure in Bar
    ret.brakePressed = cp.vl["iBESP2"]["iBESP2_BrakePedalApplied"] == 1

    # Steering wheel
    ret.steeringAngleDeg = cp.vl["EPAS_AdasStatus"]["EPAS_InternalSas"]
    ret.steeringRateDeg = cp.vl["EPAS_AdasStatus"]["EPAS_SteeringAngleSpeed"]
    ret.steeringTorque = cp.vl["EPAS_SystemStatus"]["EPAS_TorsionBarTorque"]
    ret.steeringPressed = self.update_steering_pressed(abs(ret.steeringTorque) > 1.0, 5)

    self.eac_error_code = int(cp.vl["EPAS_AdasStatus"]["EPAS_EacErrorCode"])
    self.eac_status = int(cp.vl["EPAS_AdasStatus"]["EPAS_EacStatus"])
    self.hands_on_level = int(cp.vl["EPAS_SystemStatus"]["EPAS_HandsOnLevel"])
    self.toi_fault = cp.vl["EPAS_SystemStatus"]["H_CAN_EPSS_ToiFlt"] != 0
    self.toi_active = cp.vl["EPAS_SystemStatus"]["H_CAN_EPSS_ToiActive"] != 0
    self.toi_unavailable = cp.vl["EPAS_SystemStatus"]["H_CAN_EPS_ToiUnavailable"] != 0
    toi_fault = self.toi_fault or self.toi_unavailable
    self.toi_fault_frames = self.toi_fault_frames + 1 if toi_fault else 0
    toi_fault_persistent = self.toi_fault_frames >= TOI_FAULT_ALERT_FRAMES
    ret.steerFaultPermanent, ret.steerFaultTemporary, ret.steeringDisengage = get_steering_faults(
      bool(self.CP.flags & RivianFlags.ANGLE_HARNESS), toi_fault, toi_fault_persistent,
      self.eac_status, self.eac_error_code,
    )

    # Cruise state
    speed = min(int(cp_adas.vl["ACM_tsrCmd"]["ACM_tsrSpdDisClsMain"]), 85)
    self.last_speed = speed if speed != 0 else self.last_speed
    acm_feature_status = int(cp_cam.vl["ACM_Status"]["ACM_FeatureStatus"])
    ret.cruiseState.enabled = acm_feature_status == 1
    # TODO: find cruise set speed on CAN
    ret.cruiseState.speed = self.last_speed * CV.MPH_TO_MS  # detected speed limit
    if not self.CP.openpilotLongitudinalControl:
      ret.cruiseState.speed = -1
    ret.cruiseState.available = get_cruise_available(self.CP.flags, acm_feature_status)
    ret.cruiseState.standstill = cp.vl["VDM_AdasSts"]["VDM_AdasVehicleHoldStatus"] == 1

    # ACM_Status->ACM_FaultSupervisorState normally 1, appears to go to 3 when either:
    # 1. car in park/not in drive (normal)
    # 2. something (message from another ECU) ACM relies on is faulty
    #  * ACM_FaultStatus will stay 0 since ACM itself isn't faulted
    # TODO: ACM_FaultStatus hasn't been seen high yet, but log anyway
    ret.accFaulted = (cp_cam.vl["ACM_Status"]["ACM_FaultStatus"] == 1 or
                      # VDM_AdasFaultStatus=Brk_Intv is the default for some reason
                      # VDM_AdasFaultStatus=Cntr_Fault isn't fully understood, but we've seen it in the wild
                      # VDM_AdasFaultStatus=Imps_Cmd was seen when sending it rapidly changing ACC enable commands, or when ACC command drops out
                      cp.vl["VDM_AdasSts"]["VDM_AdasFaultStatus"] in (2, 3))  # 2=Cntr_Fault, 3=Imps_Cmd

    # Gear
    ret.gearShifter = GEAR_MAP.get(int(cp.vl["VDM_PropStatus"]["VDM_Prndl_Status"]), GearShifter.unknown)

    # Gen 2 does not publish these signals. Stock ACC handles their disengage
    # behavior at standstill, and the doors cannot be opened while driving.
    if not (self.CP.flags & RivianFlags.GEN2):
      ret.doorOpen = any(cp_adas.vl["IndicatorLights"][door] != 2 for door in ("RearDriverDoor", "FrontPassengerDoor", "DriverDoor", "RearPassengerDoor"))
      ret.seatbeltUnlatched = cp.vl["RCM_Status"]["RCM_Status_IND_WARN_BELT_DRIVER"] != 0

    # Blinkers
    ret.leftBlinker = cp_adas.vl["IndicatorLights"]["TurnLightLeft"] in (1, 2)
    ret.rightBlinker = cp_adas.vl["IndicatorLights"]["TurnLightRight"] in (1, 2)

    # AEB
    ret.stockAeb = cp_cam.vl["ACM_AebRequest"]["ACM_EnableRequest"] != 0

    # Messages needed by carcontroller
    self.acm_lka_hba_cmd = copy.copy(cp_cam.vl["ACM_lkaHbaCmd"])
    if not (self.CP.flags & RivianFlags.GEN2):
      self.sccm_wheel_touch = copy.copy(cp.vl["SCCM_WheelTouch"])
    # This message can lag and deliver two samples in one parser cycle. Forward
    # every sample so cancelling stock ACC remains reliable.
    adas_status_msgs = cp.vl_all["VDM_AdasSts"]
    self.vdm_adas_status = [dict(zip(adas_status_msgs, vals, strict=True))
                            for vals in zip(*adas_status_msgs.values(), strict=True)]
    if not self.vdm_adas_status:
      self.vdm_adas_status = [copy.copy(cp.vl["VDM_AdasSts"])]

    self.longitudinal_state.update(ret, can_parsers)

    fp_ret = custom.StarPilotCarState.new_message()

    return ret, fp_ret

  def set_cruise_speed(self, speed: float) -> float:
    return self.longitudinal_state.set_cruise_speed(speed)

  @staticmethod
  def get_can_parsers(CP):
    parsers = {
      Bus.pt: CANParser(DBC[CP.carFingerprint][Bus.pt], [], 0),
      Bus.adas: CANParser(DBC[CP.carFingerprint][Bus.pt], [], 1),
      Bus.cam: CANParser(DBC[CP.carFingerprint][Bus.pt], [], 2),
    }
    if CP.flags & RivianFlags.LONGITUDINAL_HARNESS:
      parsers[Bus.alt] = CANParser(DBC[CP.carFingerprint][Bus.alt], [], 1)
    return parsers
