from openpilot.common.params import UnknownKeyName
from openpilot.starpilot.common.safe_mode import _apply_value


class RemovedParamStore:
  def get(self, key):
    raise UnknownKeyName(key)


def test_apply_value_ignores_removed_param():
  assert not _apply_value(RemovedParamStore(), "RemovedParam", "stale value")
