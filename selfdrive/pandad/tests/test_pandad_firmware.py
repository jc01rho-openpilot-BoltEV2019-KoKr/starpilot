import importlib.util
from pathlib import Path

import pytest


PANDAD_PATH = Path(__file__).resolve().parents[1] / "pandad.py"
SPEC = importlib.util.spec_from_file_location("pandad_under_test", PANDAD_PATH)
assert SPEC is not None and SPEC.loader is not None
PANDAD = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(PANDAD)


class FakeParams:
  def __init__(self, car_make, ignore_ignition_line):
    self.car_make = car_make
    self.ignore_ignition_line = ignore_ignition_line

  def get(self, key, encoding=None):
    assert key == "CarMake"
    return self.car_make

  def get_bool(self, key):
    assert key == "IgnoreIgnitionLine"
    return self.ignore_ignition_line


@pytest.mark.parametrize(("car_make", "enabled", "expected"), [
  ("gm", True, True),
  ("GM", True, True),
  ("tesla", True, False),
  ("tesla", False, False),
  (None, True, False),
])
def test_ignore_ignition_line_is_gm_only(car_make, enabled, expected):
  assert PANDAD.get_ignore_ignition_line(FakeParams(car_make, enabled)) == expected
