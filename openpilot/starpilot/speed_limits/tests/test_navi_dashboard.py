from types import SimpleNamespace

import pytest

from opendbc.car.dashboard_speed_limit import Observation, Status
from openpilot.selfdrive.navi_camera import NDA_DATA_MAX_AGE_NS
from openpilot.starpilot.speed_limits import selection as sel
from openpilot.starpilot.speed_limits.navi_dashboard import (
  EPISODE_BASE,
  SERVICE,
  NaviDashboardSource,
  dashboard_observation,
  slc_takes_dashboard,
)

T0 = 100_000_000_000
V_EGO = 20.0


class FakeSm:
  def __init__(self):
    self.recv_frame = {}
    self.logMonoTime = {}
    self.valid = {SERVICE: True}
    self._navi = None

  def receive(self, frame, mono_ns, **navi):
    defaults = {"active": 1, "isHighway": False, "camType": 1, "camLimitSpeed": 0, "camLimitSpeedLeftDist": 0,
                "sectionLimitSpeed": 0, "sectionLeftDist": 0}
    self._navi = SimpleNamespace(**{**defaults, **navi})
    self.recv_frame[SERVICE] = frame
    self.logMonoTime[SERVICE] = mono_ns

  def __getitem__(self, service):
    assert service == SERVICE
    return self._navi


def camera(sm, frame, mono_ns, limit=80, distance=400):
  sm.receive(frame, mono_ns, camLimitSpeed=limit, camLimitSpeedLeftDist=distance)


def live(source, sign, now_ns):
  observation = source.merge(sign, now_ns)
  assert observation is not None
  return observation


def oem(speed_mps, *, expiry=T0 + 10 * NDA_DATA_MAX_AGE_NS, episode=3):
  return Observation(Status.VALID, speed_mps, T0 - 1, expiry, episode)


def test_nothing_received_leaves_the_oem_observation_untouched():
  source, sm = NaviDashboardSource(), FakeSm()
  source.update(sm, V_EGO)
  assert source.merge(None, T0) is None
  sign = oem(20.0)
  assert source.merge(sign, T0) is sign


def test_camera_in_range_becomes_a_valid_observation_with_the_frame_timing():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0)
  source.update(sm, V_EGO)
  observation = live(source, None, T0 + 1)
  assert observation.status is Status.VALID
  assert observation.speed_mps == pytest.approx(80 / 3.6)
  assert (observation.observed_ns, observation.valid_until_ns) == (T0, T0 + NDA_DATA_MAX_AGE_NS)
  assert observation.episode >= EPISODE_BASE


def test_camera_outside_the_lookahead_is_not_offered():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0, distance=601)
  source.update(sm, V_EGO)
  assert source.merge(None, T0) is None


def test_an_observation_expires_with_its_frame():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0)
  source.update(sm, V_EGO)
  assert source.merge(None, T0 + NDA_DATA_MAX_AGE_NS - 1) is not None
  assert source.merge(None, T0 + NDA_DATA_MAX_AGE_NS) is None


def test_a_passed_camera_is_withdrawn_at_once():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0)
  source.update(sm, V_EGO)
  camera(sm, 2, T0 + 1, distance=0)
  source.update(sm, V_EGO)
  assert source.merge(None, T0 + 2) is None


def test_episode_changes_with_the_limit_and_holds_while_it_stays():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0, limit=80, distance=400)
  source.update(sm, V_EGO)
  first = live(source, None, T0)
  camera(sm, 2, T0 + 1, limit=80, distance=380)
  source.update(sm, V_EGO)
  assert live(source, None, T0 + 1).episode == first.episode
  camera(sm, 3, T0 + 2, limit=60, distance=100)
  source.update(sm, V_EGO)
  assert live(source, None, T0 + 2).episode > first.episode


def test_a_repeated_frame_is_not_read_twice():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0)
  source.update(sm, V_EGO)
  sm.receive(1, T0 + 5, camLimitSpeed=0)
  source.update(sm, V_EGO)
  assert source.merge(None, T0 + 6) is not None


def test_invalid_frames_offer_nothing():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0)
  sm.valid[SERVICE] = False
  source.update(sm, V_EGO)
  assert source.merge(None, T0) is None


def test_the_lower_of_a_live_oem_sign_and_the_camera_wins():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0, limit=80)
  source.update(sm, V_EGO)
  higher_sign, lower_sign = oem(100 / 3.6), oem(60 / 3.6)
  assert live(source, higher_sign, T0).speed_mps == pytest.approx(80 / 3.6)
  assert source.merge(lower_sign, T0) is lower_sign
  assert live(source, oem(80 / 3.6), T0).episode == 3


def test_an_expired_oem_sign_does_not_block_the_camera():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0, limit=80)
  source.update(sm, V_EGO)
  expired = oem(60 / 3.6, expiry=T0)
  assert live(source, expired, T0).speed_mps == pytest.approx(80 / 3.6)


def _card(source, sign=None):
  evidence = SimpleNamespace(observation=sign) if sign is not None else None
  return SimpleNamespace(CI=SimpleNamespace(CS=SimpleNamespace(dashboard_limit=evidence)), sm=None, navi_dashboard=source)


def test_card_without_a_navi_source_keeps_the_oem_observation():
  sign = oem(20.0)
  assert dashboard_observation(_card(None, sign), T0) is sign
  assert dashboard_observation(_card(None), T0) is None


def test_card_feeds_the_frame_and_merges_the_camera():
  source, sm = NaviDashboardSource(), FakeSm()
  camera(sm, 1, T0)
  card = _card(source)
  card.sm = sm
  assert dashboard_observation(card, T0) is None
  observation = dashboard_observation(card, T0 + 1, V_EGO)
  assert observation is not None and observation.speed_mps == pytest.approx(80 / 3.6)
  assert dashboard_observation(card, T0 + 2) is not None


def _runtime(**selection):
  enabled = selection.pop("enabled", True)
  policy = sel.SelectionPolicy(selection.pop("mode", sel.SelectionMode.ORDERED), selection.pop("slots"), False)
  return SimpleNamespace(settings=SimpleNamespace(enabled=enabled, selection=policy))


def test_slc_owns_the_camera_only_when_it_controls_speed_from_the_dashboard():
  ordered = (sel.Source.DASHBOARD, sel.Source.MAP)
  assert slc_takes_dashboard(_runtime(slots=ordered))
  assert slc_takes_dashboard(_runtime(slots=(sel.Source.VISION,), mode=sel.SelectionMode.HIGHEST))
  assert not slc_takes_dashboard(_runtime(slots=ordered, enabled=False))
  assert not slc_takes_dashboard(_runtime(slots=(sel.Source.VISION, sel.Source.MAP)))
  assert not slc_takes_dashboard(None)
