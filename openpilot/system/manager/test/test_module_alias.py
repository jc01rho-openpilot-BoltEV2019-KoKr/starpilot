import sys
import types

import pytest

from openpilot.system.manager.module_alias import import_process_module, legacy_alias


@pytest.fixture
def nested_module(monkeypatch):
  name = 'openpilot.selfdrive.test_legacy_alias_target'
  module = types.ModuleType(name)
  monkeypatch.setitem(sys.modules, name, module)
  monkeypatch.setattr('importlib.util.find_spec', lambda alias: object() if alias == name else None)
  return module


def test_legacy_name_resolves_to_nested_module(nested_module):
  assert import_process_module('selfdrive.test_legacy_alias_target') is nested_module


def test_road_speed_limiter_legacy_name_maps_to_nested_path():
  assert legacy_alias('selfdrive.road_speed_limiter') == 'openpilot.selfdrive.road_speed_limiter'


def test_current_name_imports_directly():
  assert import_process_module('openpilot.system.manager.module_alias').legacy_alias is legacy_alias


def test_unknown_module_still_raises():
  with pytest.raises(ModuleNotFoundError):
    import_process_module('selfdrive.does_not_exist_anywhere')


def test_missing_dependency_inside_module_is_not_masked(monkeypatch):
  def fail(name):
    raise ModuleNotFoundError("No module named 'numpy'", name='numpy')

  monkeypatch.setattr('importlib.import_module', fail)
  with pytest.raises(ModuleNotFoundError) as e:
    import_process_module('selfdrive.road_speed_limiter')
  assert e.value.name == 'numpy'
