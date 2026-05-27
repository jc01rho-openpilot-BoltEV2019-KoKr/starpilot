import math
from dataclasses import dataclass

from opendbc.can import CANParser
from opendbc.car import Bus, structs
from opendbc.car.interfaces import RadarInterfaceBase
from opendbc.car.hyundai.values import CAR, DBC, HYUNDAI_MANDO_FRONT_RADAR_DBC, HYUNDAI_MRR30_RADAR_DBC, \
                                       HYUNDAI_MRR35_RADAR_DBC
from openpilot.common.swaglog import cloudlog

RADAR_START_ADDR = 0x500
RADAR_MSG_COUNT = 32
MRR30_RADAR_START_ADDR = 0x210
MRR30_RADAR_MSG_COUNT = 16
MRR35_RADAR_START_ADDR = 0x3A5
MRR35_RADAR_MSG_COUNT = 32


@dataclass(frozen=True)
class RadarTrackConfig:
  start_addr: int
  msg_count: int
  radar_type: str
  bus: int = 1
  frequency: int = 50


RADAR_TRACK_CONFIGS = {
  HYUNDAI_MANDO_FRONT_RADAR_DBC: RadarTrackConfig(RADAR_START_ADDR, RADAR_MSG_COUNT, "mando"),
  HYUNDAI_MRR30_RADAR_DBC: RadarTrackConfig(MRR30_RADAR_START_ADDR, MRR30_RADAR_MSG_COUNT, "mrr30"),
  HYUNDAI_MRR35_RADAR_DBC: RadarTrackConfig(MRR35_RADAR_START_ADDR, MRR35_RADAR_MSG_COUNT, "mrr35", bus=0, frequency=20),
}

# POC for parsing corner radars: https://github.com/commaai/openpilot/pull/24221/


def get_radar_track_config(car_fingerprint) -> RadarTrackConfig | None:
  radar_dbc = DBC[car_fingerprint].get(Bus.radar)
  return RADAR_TRACK_CONFIGS.get(radar_dbc)


def get_radar_can_parser(CP, radar_config):
  if radar_config is None:
    return None

  messages = [(f"RADAR_TRACK_{addr:x}", radar_config.frequency) for addr in range(radar_config.start_addr, radar_config.start_addr + radar_config.msg_count)]
  return CANParser(DBC[CP.carFingerprint][Bus.radar], messages, radar_config.bus)


class RadarInterface(RadarInterfaceBase):
  def __init__(self, CP):
    super().__init__(CP)
    self.radar_config = get_radar_track_config(CP.carFingerprint)
    self.updated_messages = set()
    self.trigger_msg = (self.radar_config.start_addr + self.radar_config.msg_count - 1) if self.radar_config is not None else RADAR_START_ADDR
    self.track_id = 0

    self.radar_off_can = CP.radarUnavailable
    # Probe whether radar tracks still exist on the Ioniq 6 while OP long is active,
    # without changing planner behavior yet.
    self.ioniq_6_radar_probe = CP.carFingerprint == CAR.HYUNDAI_IONIQ_6 and CP.openpilotLongitudinalControl and self.radar_off_can
    self.ioniq_6_radar_probe_logged = False
    self.ioniq_6_radar_probe_updates = 0
    self.rcp = get_radar_can_parser(CP, self.radar_config)

  def update(self, can_strings):
    if self.ioniq_6_radar_probe and self.rcp is not None and not self.ioniq_6_radar_probe_logged:
      vls = self.rcp.update(can_strings)
      self.updated_messages.update(vls)
      self.ioniq_6_radar_probe_updates += 1

      if self.trigger_msg in self.updated_messages:
        rr = self._update(self.updated_messages)
        cloudlog.warning(f"Ioniq 6 radar probe: saw {len(rr.points)} radar tracks with radarUnavailable forced on")
        self.updated_messages.clear()
        self.ioniq_6_radar_probe_logged = True
      elif self.ioniq_6_radar_probe_updates >= 500:
        cloudlog.warning("Ioniq 6 radar probe: no radar track frames observed after startup")
        self.ioniq_6_radar_probe_logged = True
        self.updated_messages.clear()

    if self.radar_off_can or (self.rcp is None):
      return super().update(None)

    vls = self.rcp.update(can_strings)
    self.updated_messages.update(vls)

    if self.trigger_msg not in self.updated_messages:
      return None

    rr = self._update(self.updated_messages)
    self.updated_messages.clear()

    return rr

  def _update(self, updated_messages):
    ret = structs.RadarData()
    if self.rcp is None:
      return ret

    if not self.rcp.can_valid:
      ret.errors.canError = True

    if self.radar_config is None:
      return ret

    for addr in range(self.radar_config.start_addr, self.radar_config.start_addr + self.radar_config.msg_count):
      msg = self.rcp.vl[f"RADAR_TRACK_{addr:x}"]

      if self.radar_config.radar_type == "mrr30":
        for i in ("1", "2"):
          track_key = addr * 2 + int(i) - 1
          if track_key not in self.pts:
            self.pts[track_key] = structs.RadarData.RadarPoint()
            self.pts[track_key].trackId = self.track_id
            self.track_id += 1

          valid = msg[f"{i}_STATE"] in (3, 4)
          if valid:
            pt = self.pts[track_key]
            pt.measured = True
            pt.dRel = msg[f"{i}_LONG_DIST"]
            pt.yRel = msg[f"{i}_LAT_DIST"]
            pt.vRel = msg[f"{i}_REL_SPEED"]
            pt.aRel = float("nan")
            pt.yvRel = float("nan")
          else:
            del self.pts[track_key]
        continue

      if addr not in self.pts:
        self.pts[addr] = structs.RadarData.RadarPoint()
        self.pts[addr].trackId = self.track_id
        self.track_id += 1

      if self.radar_config.radar_type == "mrr35":
        valid = msg["STATE"] in (3, 4)
        if valid:
          self.pts[addr].measured = True
          self.pts[addr].dRel = msg["LONG_DIST"]
          self.pts[addr].yRel = msg["LAT_DIST"]
          self.pts[addr].vRel = msg["REL_SPEED"]
          self.pts[addr].aRel = msg["REL_ACCEL"]
          self.pts[addr].yvRel = float("nan")
        else:
          del self.pts[addr]
        continue

      valid = msg['STATE'] in (3, 4)
      if valid:
        azimuth = math.radians(msg['AZIMUTH'])
        self.pts[addr].measured = True
        self.pts[addr].dRel = math.cos(azimuth) * msg['LONG_DIST']
        self.pts[addr].yRel = 0.5 * -math.sin(azimuth) * msg['LONG_DIST']
        self.pts[addr].vRel = msg['REL_SPEED']
        self.pts[addr].aRel = msg['REL_ACCEL']
        self.pts[addr].yvRel = float('nan')

      else:
        del self.pts[addr]

    ret.points = list(self.pts.values())
    return ret
