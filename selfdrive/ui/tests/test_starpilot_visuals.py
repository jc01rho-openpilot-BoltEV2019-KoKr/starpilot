import importlib.util
import unittest
from pathlib import Path


MODULE_PATH = Path(__file__).resolve().parents[1] / "lib" / "starpilot_visuals.py"
SPEC = importlib.util.spec_from_file_location("starpilot_visuals_under_test", MODULE_PATH)
MODULE = importlib.util.module_from_spec(SPEC)
assert SPEC is not None and SPEC.loader is not None
SPEC.loader.exec_module(MODULE)
lead_indicator_enabled = MODULE.lead_indicator_enabled


class FakeParams:
  def __init__(self, values=None):
    self.values = values or {}

  def get_bool(self, key, block=False, default=False):
    value = self.values.get(key, default)
    if isinstance(value, bool):
      return value
    return str(value or "").strip() in ("1", "true", "True")


class TestStarPilotVisuals(unittest.TestCase):
  def test_lead_indicator_disabled_by_default(self):
    self.assertFalse(lead_indicator_enabled(FakeParams()))

  def test_lead_indicator_can_be_enabled(self):
    self.assertTrue(lead_indicator_enabled(FakeParams({"LeadIndicator": True})))

  def test_hide_lead_marker_suppresses_lead_indicator(self):
    self.assertFalse(lead_indicator_enabled(FakeParams({"LeadIndicator": True, "HideLeadMarker": True})))


if __name__ == "__main__":
  unittest.main()
