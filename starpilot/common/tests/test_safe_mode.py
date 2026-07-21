from openpilot.common.params import UnknownKeyName
from openpilot.starpilot.common.safe_mode import SAFE_MODE_MANAGED_KEYS, _apply_value


class RemovedParamStore:
  def get(self, key):
    raise UnknownKeyName(key)


def test_apply_value_ignores_removed_param():
  assert not _apply_value(RemovedParamStore(), "RemovedParam", "stale value")


def test_safe_mode_manages_lane_centering_keys():
  assert "LaneCentering" in SAFE_MODE_MANAGED_KEYS
  assert "LaneCenterOffset" in SAFE_MODE_MANAGED_KEYS
