"""Offer the NDA camera limit to the Speed Limit Controller as its dashboard source."""
from dataclasses import replace

from opendbc.car.dashboard_speed_limit import Observation, Status, Tracker
from openpilot.selfdrive.navi_camera import NDA_DATA_MAX_AGE_NS, nda_slc_limit
from openpilot.starpilot.speed_limits import selection as sel

SERVICE = 'naviData'
# Episodes are part of the observation identity; keep them apart from the OEM TSR episodes.
EPISODE_BASE = 1 << 31


class NaviDashboardSource:
  """Turn naviData frames into dashboard observations with the OEM TSR contract.

  The observation time is the frame's receipt time, it expires NDA_DATA_MAX_AGE_NS later, and the
  episode changes whenever the offered limit changes, so a stale or passed camera never lingers.
  """

  def __init__(self):
    self._tracker = Tracker()
    self._frame = 0

  def update(self, sm, v_ego_mps: float) -> None:
    frame = int(sm.recv_frame.get(SERVICE, 0))
    if frame == 0 or frame == self._frame:
      return
    self._frame = frame
    mono_ns = int(sm.logMonoTime[SERVICE])
    limit_kph = nda_slc_limit(sm[SERVICE], v_ego_mps) if sm.valid[SERVICE] else 0.0
    status, speed_mps = (Status.VALID, limit_kph / 3.6) if limit_kph > 0 else (Status.ABSENT, 0.0)
    self._tracker.update(mono_ns, status, speed_mps, valid_until_ns=mono_ns + NDA_DATA_MAX_AGE_NS)

  def merge(self, oem: Observation | None, now_ns: int) -> Observation | None:
    """Return the OEM observation, or the NDA one when it is live and lower than a live OEM sign."""
    navi = self._tracker.observation
    if navi.status is not Status.VALID or navi.valid_until_ns <= now_ns:
      return oem
    if oem is not None and oem.status is Status.VALID and oem.valid_until_ns > now_ns and oem.speed_mps <= navi.speed_mps:
      return oem
    return replace(navi, episode=navi.episode + EPISODE_BASE)


def slc_takes_dashboard(runtime) -> bool:
  """True when the SLC runtime controls speed and reads the dashboard source, so it owns the NDA limit."""
  settings = getattr(runtime, 'settings', None)
  if settings is None or not settings.enabled:
    return False
  policy = settings.selection
  return policy.mode is not sel.SelectionMode.ORDERED or sel.Source.DASHBOARD in policy.slots
