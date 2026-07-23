import importlib.util
from pathlib import Path

import pytest


PANDAD_PATH = Path(__file__).resolve().parents[1] / "pandad.py"
SPEC = importlib.util.spec_from_file_location("pandad_under_test", PANDAD_PATH)
assert SPEC is not None and SPEC.loader is not None
PANDAD = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PANDAD)


class FakeParams:
  def __init__(self, ignore_ignition_line):
    self.ignore_ignition_line = ignore_ignition_line

  def get_bool(self, key):
    assert key == "IgnoreIgnitionLine"
    return self.ignore_ignition_line


@pytest.mark.parametrize(("enabled", "expected"), [
  (True, True),
  (False, False),
])
def test_ignore_ignition_line_follows_toggle(enabled, expected):
  assert PANDAD.get_ignore_ignition_line(FakeParams(enabled)) == expected
