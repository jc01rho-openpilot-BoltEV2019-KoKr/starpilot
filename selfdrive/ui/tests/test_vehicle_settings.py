import importlib
import sys
import types
import unittest

from openpilot.selfdrive.ui.tests.test_aethergrid import (
  _clear_modules,
  _install_aethergrid_stubs,
  _install_panel_stubs,
)


AETHERGRID_MODULE = "openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid"
PANEL_MODULE = "openpilot.selfdrive.ui.layouts.settings.starpilot.panel"
VEHICLE_MODULE = "openpilot.selfdrive.ui.layouts.settings.starpilot.vehicle"


def _module(name, **attributes):
  module = types.ModuleType(name)
  for attribute, value in attributes.items():
    setattr(module, attribute, value)
  return module


def _install_vehicle_stubs():
  _install_aethergrid_stubs()
  setattr(sys.modules["openpilot.system.ui.lib.multilang"], "tr_noop", lambda text: text)

  sys.modules["openpilot.system.hardware"] = _module(
    "openpilot.system.hardware",
    HARDWARE=types.SimpleNamespace(reboot=lambda: None),
  )
  sys.modules["openpilot.system.ui.widgets.confirm_dialog"] = _module(
    "openpilot.system.ui.widgets.confirm_dialog",
    ConfirmDialog=type("ConfirmDialog", (), {}),
    alert_dialog=lambda *_args, **_kwargs: None,
  )
  sys.modules["openpilot.selfdrive.ui.lib.starpilot_state"] = _module(
    "openpilot.selfdrive.ui.lib.starpilot_state",
    starpilot_state=types.SimpleNamespace(update=lambda **_kwargs: None),
  )
  sys.modules["openpilot.selfdrive.ui.lib.fingerprint_catalog"] = _module(
    "openpilot.selfdrive.ui.lib.fingerprint_catalog",
    FingerprintModelOption=type("FingerprintModelOption", (), {}),
    format_fingerprint_value=lambda value: str(value),
    get_fingerprint_catalog=lambda: [],
    shorten_model_label=lambda value: str(value),
  )
  sys.modules["openpilot.starpilot.common.starpilot_variables"] = _module(
    "openpilot.starpilot.common.starpilot_variables",
    migrate_cancel_button_controls=lambda *_args, **_kwargs: None,
  )


def _import_vehicle():
  _install_vehicle_stubs()
  _clear_modules(AETHERGRID_MODULE)
  aethergrid = importlib.import_module(AETHERGRID_MODULE)
  _install_panel_stubs(aethergrid)

  sys.modules[PANEL_MODULE] = _module(PANEL_MODULE, _SettingsPage=type("_SettingsPage", (), {}))

  _clear_modules(VEHICLE_MODULE)
  return importlib.import_module(VEHICLE_MODULE)


class TestVehicleSettingsFirstRender(unittest.TestCase):
  def test_single_column_first_render_has_row_height(self):
    vehicle = _import_vehicle()
    view = vehicle.VehicleSettingsManagerView(types.SimpleNamespace())
    width = view.TWO_COLUMN_BREAKPOINT - 1

    view._check_rebuild_grid = lambda: None
    view._build_identity_rows = lambda: [object()]
    view._build_steering_rows = lambda: []
    view._toggle_grid.tiles = []
    drawn_sections = []

    def capture_section(y, _x, _width, title, _rows, row_height):
      drawn_sections.append((title, row_height))
      return y + 100

    view._draw_section = capture_section

    self.assertFalse(view._uses_two_columns(width))
    view._measure_content_height(width)
    view._draw_scroll_content(vehicle.rl.Rectangle(0, 0, width, 760), width)

    self.assertEqual(drawn_sections, [
      ("Vehicle Identity", vehicle.ROW_HEIGHT),
      ("Steering Controls", vehicle.ROW_HEIGHT),
    ])


if __name__ == "__main__":
  unittest.main()
