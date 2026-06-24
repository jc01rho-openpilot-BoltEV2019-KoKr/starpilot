import json
from types import SimpleNamespace

from openpilot.starpilot import starpilot_process


class FakeParams:
  def __init__(self):
    self.writes = []

  def put(self, key, value):
    self.writes.append((key, value))


class FakeThreadManager:
  def run_with_lock(self, *args, **kwargs):
    return None


class FakeThemeManager:
  def update_active_theme(self, *args, **kwargs):
    return None


class FakeModelManager:
  def randomize_selected_model(self):
    return None


def test_transition_offroad_skips_invalid_gps_persist():
  params = FakeParams()
  planner = SimpleNamespace(gps_position={
    "latitude": 0.0,
    "longitude": 0.0,
    "bearing": 0.0,
    "speed": 0.0,
    "hasFix": False,
    "updatedAtMonotonic": 1.0,
    "updatedAtSec": 1.0,
  })
  toggles = SimpleNamespace(lock_doors_timer=0, random_themes=False)

  starpilot_process.transition_offroad(
    planner,
    FakeModelManager(),
    FakeThemeManager(),
    FakeThreadManager(),
    False,
    None,
    params,
    toggles,
  )

  assert params.writes == []


def test_transition_offroad_persists_valid_gps():
  params = FakeParams()
  gps_position = {
    "latitude": 41.0,
    "longitude": -87.0,
    "bearing": 90.0,
    "speed": 12.0,
    "hasFix": True,
    "updatedAtMonotonic": 1.0,
    "updatedAtSec": 2.0,
  }
  planner = SimpleNamespace(gps_position=gps_position)
  toggles = SimpleNamespace(lock_doors_timer=0, random_themes=False)

  starpilot_process.transition_offroad(
    planner,
    FakeModelManager(),
    FakeThemeManager(),
    FakeThreadManager(),
    False,
    None,
    params,
    toggles,
  )

  assert params.writes == [("LastGPSPosition", json.dumps(gps_position))]
