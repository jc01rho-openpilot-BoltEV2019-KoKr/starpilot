import importlib
import sys
import types
from unittest.mock import patch

import pytest


@pytest.fixture
def updater_module(monkeypatch):
  hardware = types.ModuleType("openpilot.system.hardware")
  hardware.HARDWARE = types.SimpleNamespace(get_device_type=lambda: "tici")
  monkeypatch.setitem(sys.modules, "openpilot.system.hardware", hardware)
  sys.modules.pop("openpilot.system.ui.updater", None)
  module = importlib.import_module("openpilot.system.ui.updater")
  yield module
  sys.modules.pop("openpilot.system.ui.updater", None)


def test_device_tree_tici_uses_big_ui(updater_module):
  with patch.object(updater_module, "_device_tree_device_type", return_value="tici"), \
       patch.object(updater_module, "_framebuffer_size", return_value=(536, 240)), \
       patch.object(updater_module, "_reported_device_type", return_value="mici"):
    assert updater_module._ui_device_type() == "tici"


def test_device_tree_tizi_uses_big_ui(updater_module):
  with patch.object(updater_module, "_device_tree_device_type", return_value="tizi"), \
       patch.object(updater_module, "_framebuffer_size", return_value=(536, 240)), \
       patch.object(updater_module, "_reported_device_type", return_value="mici"):
    assert updater_module._ui_device_type() == "tizi"


@pytest.mark.parametrize("device_tree_type", ["mici", "comma 4", "comma four"])
def test_non_tici_device_tree_uses_small_ui(updater_module, device_tree_type):
  with patch.object(updater_module, "_device_tree_device_type", return_value=device_tree_type), \
       patch.object(updater_module, "_framebuffer_size", return_value=(2160, 1080)), \
       patch.object(updater_module, "_reported_device_type", return_value="tici"):
    assert updater_module._ui_device_type() == "mici"


def test_small_framebuffer_uses_small_ui_without_device_tree(updater_module):
  with patch.object(updater_module, "_device_tree_device_type", return_value=None), \
       patch.object(updater_module, "_framebuffer_size", return_value=(536, 240)), \
       patch.object(updater_module, "_reported_device_type", return_value="tici"):
    assert updater_module._ui_device_type() == "mici"


def test_reported_tici_used_when_no_other_signal(updater_module):
  with patch.object(updater_module, "_device_tree_device_type", return_value=None), \
       patch.object(updater_module, "_framebuffer_size", return_value=None), \
       patch.object(updater_module, "_reported_device_type", return_value="tici"):
    assert updater_module._ui_device_type() == "tici"
