from __future__ import annotations

import shutil
from pathlib import Path

from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.widgets import DialogResult
from openpilot.system.ui.widgets.option_dialog import MultiOptionDialog
from openpilot.system.ui.widgets.confirm_dialog import ConfirmDialog, alert_dialog
from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import StarPilotPanel
from openpilot.starpilot.common.maps_catalog import (
  COUNTRY_REGION_GROUPS,
  MAP_SCHEDULE_LABELS,
  MAP_SECTIONS,
  STATE_REGION_GROUPS,
  sanitize_selected_locations_csv,
  schedule_label,
  schedule_param_value,
)


class StarPilotMapRegionLayout(StarPilotPanel):
  def __init__(self, region_map: dict[str, str], prefix: str):
    super().__init__()
    self._prefix = prefix
    self.CATEGORIES = []

    for key, name in sorted(region_map.items(), key=lambda item: item[1]):
      self.CATEGORIES.append({
        "title": name,
        "type": "toggle",
        "get_state": lambda k=key: self._get_map_state(k),
        "set_state": lambda s, k=key: self._set_map_state(k, s),
        "color": "#68ACA3"
      })
    self._rebuild_grid()

  def _get_map_state(self, key):
    selected = set(sanitize_selected_locations_csv(self._params.get("MapsSelected", encoding="utf-8") or "").split(","))
    selected.discard("")
    return f"{self._prefix}{key}" in selected

  def _set_map_state(self, key, state):
    selected = set(sanitize_selected_locations_csv(self._params.get("MapsSelected", encoding="utf-8") or "").split(","))
    selected.discard("")

    prefixed_key = f"{self._prefix}{key}"
    if state:
      selected.add(prefixed_key)
    else:
      selected.discard(prefixed_key)

    self._params.put("MapsSelected", sanitize_selected_locations_csv(sorted(selected)))


class StarPilotMapCountriesLayout(StarPilotPanel):
  def __init__(self):
    super().__init__()
    self.CATEGORIES = [
      {"title": tr_noop(group["title"]), "panel": group["key"], "icon": "toggle_icons/icon_map.png", "color": "#68ACA3"}
      for group in COUNTRY_REGION_GROUPS
    ]
    self._rebuild_grid()


class StarPilotMapStatesLayout(StarPilotPanel):
  def __init__(self):
    super().__init__()
    self.CATEGORIES = [
      {"title": tr_noop(group["title"]), "panel": group["key"], "icon": "toggle_icons/icon_map.png", "color": "#68ACA3"}
      for group in STATE_REGION_GROUPS
    ]
    self._rebuild_grid()


class StarPilotMapsLayout(StarPilotPanel):
  def __init__(self):
    super().__init__()

    self._sub_panels = {
      "countries": StarPilotMapCountriesLayout(),
      "states": StarPilotMapStatesLayout(),
    }

    for section in MAP_SECTIONS:
      for group in section["groups"]:
        self._sub_panels[group["key"]] = StarPilotMapRegionLayout(group["regions"], section["prefix"])

    self.CATEGORIES = [
      {"title": tr_noop("Download Maps"), "type": "hub", "on_click": self._on_download, "icon": "toggle_icons/icon_map.png", "color": "#68ACA3"},
      {"title": tr_noop("Auto Update Schedule"), "type": "value", "get_value": lambda: schedule_label(self._params.get("PreferredSchedule")), "on_click": self._on_schedule, "icon": "toggle_icons/icon_calendar.png", "color": "#68ACA3"},
      {"title": tr_noop("Countries"), "panel": "countries", "icon": "toggle_icons/icon_map.png", "color": "#68ACA3"},
      {"title": tr_noop("U.S. States"), "panel": "states", "icon": "toggle_icons/icon_map.png", "color": "#68ACA3"},
      {"title": tr_noop("Storage Used"), "type": "value", "get_value": self._get_storage, "on_click": lambda: None, "icon": "toggle_icons/icon_system.png", "color": "#68ACA3"},
      {"title": tr_noop("Remove Maps"), "type": "hub", "on_click": self._on_remove, "icon": "toggle_icons/icon_map.png", "color": "#68ACA3"},
    ]

    for _, panel in self._sub_panels.items():
      if hasattr(panel, "set_navigate_callback"):
        panel.set_navigate_callback(self._navigate_to)
      if hasattr(panel, "set_back_callback"):
        panel.set_back_callback(self._go_back)

    self._rebuild_grid()

  def _get_storage(self) -> str:
    maps_path = Path("/data/media/0/osm/offline")
    if not maps_path.exists():
      return "0 MB"
    total_size = sum(f.stat().st_size for f in maps_path.rglob("*") if f.is_file())
    mb = total_size / (1024 * 1024)
    if mb > 1024:
      return f"{(mb / 1024):.2f} GB"
    return f"{mb:.2f} MB"

  def _on_schedule(self):
    options = list(MAP_SCHEDULE_LABELS.values())
    current = schedule_label(self._params.get("PreferredSchedule"))
    dialog = MultiOptionDialog(tr("Auto Update Schedule"), options, current)

    def on_select(res):
      if res == DialogResult.CONFIRM and dialog.selection:
        self._params.put("PreferredSchedule", schedule_param_value(dialog.selection))
        self._rebuild_grid()

    gui_app.push_widget(dialog, callback=on_select)

  def _on_download(self):
    current_selected = self._params.get("MapsSelected", encoding="utf-8") or ""
    selected_raw = sanitize_selected_locations_csv(current_selected)
    if selected_raw != current_selected:
      self._params.put("MapsSelected", selected_raw)
    selected = [k.strip() for k in selected_raw.split(",") if k.strip()]
    if not selected:
      gui_app.push_widget(alert_dialog(tr("Please select at least one region or state first!")))
      return

    def on_confirm(res):
      if res == DialogResult.CONFIRM:
        self._params_memory.put_bool("DownloadMaps", True)
        gui_app.push_widget(alert_dialog(tr("Map download started in background.")))

    gui_app.push_widget(ConfirmDialog(tr("Start downloading maps for selected regions?"), tr("Download"), on_close=on_confirm))

  def _on_remove(self):
    def on_confirm(res):
      if res == DialogResult.CONFIRM:
        maps_path = Path("/data/media/0/osm/offline")
        if maps_path.exists():
          shutil.rmtree(maps_path, ignore_errors=True)
        gui_app.push_widget(alert_dialog(tr("Maps removed.")))
        self._rebuild_grid()

    gui_app.push_widget(ConfirmDialog(tr("Delete all downloaded map data?"), tr("Remove"), on_close=on_confirm))
