from __future__ import annotations
from dataclasses import replace
import subprocess
from pathlib import Path

import pyray as rl

from openpilot.common.basedir import BASEDIR
from openpilot.starpilot.common.starpilot_variables import ACTIVE_THEME_PATH
from openpilot.system.ui.lib.application import gui_app, FontWeight, MouseEvent, MousePos
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.lib.scroll_panel2 import GuiScrollPanel2
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.widgets.label import gui_label
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.lib.starpilot_state import starpilot_state
from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import _SettingsPage
from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import (
  AETHER_LIST_METRICS,
  COMPACT_PANEL_METRICS,
  AetherAdjustorRow,
  AetherListColors,
  AetherScrollbar,
  TileGrid,
  ToggleTile,
  panel_style_from_color,
  _point_hits,
  draw_action_pill,
  draw_list_group_shell,
  draw_list_scroll_fades,
  draw_section_header,
  draw_settings_panel_header,
  init_list_panel,
)

PANEL_STYLE = panel_style_from_color("#E63956")
SECTION_GAP = AETHER_LIST_METRICS.section_gap
SECTION_HEADER_HEIGHT = AETHER_LIST_METRICS.section_header_height
SECTION_HEADER_GAP = AETHER_LIST_METRICS.section_header_gap

GROUP_HEADER_HEIGHT = 20
GROUP_HEADER_GAP = 4
GROUP_HAIRLINE_COLOR = rl.Color(255, 255, 255, 10)
GROUP_HEADER_COLOR = rl.Color(255, 255, 255, 90)

SOUNDS_PANEL_METRICS = replace(
  COMPACT_PANEL_METRICS,
  outer_margin_y=14,
  panel_padding_top=16,
  panel_padding_bottom=14,
  header_height=88,
)


class SoundsManagerView(Widget):
  def __init__(self, controller: "StarPilotSoundsLayout"):
    super().__init__()
    self._controller = controller
    self._pressed_target: str | None = None
    self._adjustor_rows: dict[str, AetherAdjustorRow] = {}
    self._was_interacting: dict[str, bool] = {}
    self._active_adjustor_key: str | None = None
    self._can_click = True
    self._reset_rect = rl.Rectangle(0, 0, 0, 0)

    self._scroll_panel = GuiScrollPanel2(horizontal=False)
    self._scrollbar = AetherScrollbar()
    self._content_height = 0.0
    self._scroll_offset = 0.0
    self._scroll_rect = rl.Rectangle(0, 0, 0, 0)
    self._tile_grid_h = 0.0

    self._init_adjustors()
    self._init_toggles()
    self._forward_touch_valid()

  def _forward_touch_valid(self):
    for adjustor in self._adjustor_rows.values():
      adjustor.set_touch_valid_callback(
        lambda: self._scroll_panel.is_touch_valid() or adjustor.is_interacting
      )
    self._toggle_grid.set_touch_valid_callback(
      lambda: self._scroll_panel.is_touch_valid()
    )

  def _init_toggles(self):
    self._toggle_grid = TileGrid(columns=2, padding=12)
    for key in self._controller.CUSTOM_ALERTS_KEYS:
      info = self._controller.ALERT_INFO[key]
      tile = ToggleTile(
        title=tr(info["title"]),
        get_state=lambda k=key: self._controller._params.get_bool(k),
        set_state=lambda state, k=key: self._controller._params.put_bool(k, state),
        bg_color=PANEL_STYLE.accent,
        desc=tr(info.get("subtitle", "")),
        is_enabled=info.get("is_enabled"),
        disabled_label=tr(info.get("disabled_label", "")) if info.get("disabled_label") else "",
      )
      self._toggle_grid.add_tile(tile)
    self._child(self._toggle_grid)

  def _set_active_adjustor(self, key: str, active: bool):
    if active:
      if self._active_adjustor_key and self._active_adjustor_key != key:
        old = self._adjustor_rows.get(self._active_adjustor_key)
        if old:
          old.reset_interaction()
      self._active_adjustor_key = key
    elif self._active_adjustor_key == key:
      self._active_adjustor_key = None

  def _init_adjustors(self):
    for key in self._controller.VOLUME_KEYS:
      info = self._controller.VOLUME_INFO[key]

      def on_change(v, k=key, min_v=info["min"]):
        new_v = int(v)
        if new_v != 101 and new_v < min_v:
          new_v = min_v
        self._controller._params.put_int(k, new_v)

      adjustor = AetherAdjustorRow(
        tr(info["title"]),
        tr(info["subtitle"]),
        0.0, 101.0, 1.0,
        get_value=lambda k=key: float(self._controller._params.get_int(k, return_default=True, default=100)),
        on_change=on_change,
        on_commit=None,
        unit="%",
        labels={0.0: tr("Muted"), 101.0: tr("Auto")},
        presets=[0, 25, 50, 75, 101],
        is_active=lambda k=key: self._active_adjustor_key == k,
        set_active=lambda active, k=key: self._set_active_adjustor(k, active),
        style=PANEL_STYLE,
        color=PANEL_STYLE.accent,
      )
      self._adjustor_rows[key] = adjustor

    cd_key = self._controller.COOLDOWN_KEY
    cd_info = self._controller.COOLDOWN_INFO
    def on_cd_commit(v):
      self._controller._params.put_int(cd_key, int(v))

    cd_adjustor = AetherAdjustorRow(
      tr(cd_info["title"]),
      tr(cd_info["subtitle"]),
      0.0, float(cd_info["max"]), 1.0,
      get_value=lambda: float(self._controller._params.get_int(cd_key, return_default=True, default=0)),
      on_change=lambda _v: None,
      on_commit=on_cd_commit,
      unit=" " + tr("min"),
      labels={0.0: tr("Off"), 1.0: tr("1 min")},
      presets=[0, 1, 5, 10, 20, 30],
      is_active=lambda: self._active_adjustor_key == cd_key,
      set_active=lambda active: self._set_active_adjustor(cd_key, active),
      style=PANEL_STYLE,
      color=PANEL_STYLE.accent,
    )
    self._adjustor_rows[cd_key] = cd_adjustor

  def _handle_mouse_press(self, mouse_pos: MousePos):
    self._pressed_target = self._target_at(mouse_pos)
    self._can_click = True
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_press(mouse_pos)
    self._toggle_grid._handle_mouse_press(mouse_pos)

  def _handle_mouse_release(self, mouse_pos: MousePos):
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_release(mouse_pos)
    self._toggle_grid._handle_mouse_release(mouse_pos)

    target = self._target_at(mouse_pos) if self._scroll_panel.is_touch_valid() else None
    if self._pressed_target is not None and self._pressed_target == target and self._can_click:
      self._activate_target(target)
    self._pressed_target = None
    self._can_click = True

  def _handle_mouse_event(self, mouse_event: MouseEvent):
    if not self._scroll_panel.is_touch_valid():
      self._can_click = False
      return
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_event(mouse_event)
    self._toggle_grid._handle_mouse_event(mouse_event)

  def _target_at(self, mouse_pos: MousePos) -> str | None:
    if _point_hits(mouse_pos, self._reset_rect, self._scroll_rect, pad_x=6, pad_y=0):
      return "action:restore_defaults"
    return None

  def _activate_target(self, target: str):
    if target == "action:restore_defaults":
      self._controller._restore_defaults()

  def show_event(self):
    super().show_event()
    self._pressed_target = None
    self._can_click = True

  def hide_event(self):
    super().hide_event()
    self._pressed_target = None
    self._can_click = True

  def _render(self, rect: rl.Rectangle):
    self.set_rect(rect)

    frame, scroll_rect, content_width = init_list_panel(rect, PANEL_STYLE, metrics=SOUNDS_PANEL_METRICS)
    self._scroll_rect = scroll_rect

    self._draw_header(frame.header)

    self._content_height = self._measure_content_height(content_width)

    self._scroll_panel.set_enabled(self.is_visible)
    self._scroll_offset = self._scroll_panel.update(
      scroll_rect, max(self._content_height, scroll_rect.height)
    )

    rl.begin_scissor_mode(
      int(scroll_rect.x), int(scroll_rect.y),
      int(scroll_rect.width), int(scroll_rect.height)
    )
    self._draw_scroll_content(scroll_rect, content_width)
    rl.end_scissor_mode()

    if self._content_height > scroll_rect.height:
      self._scrollbar.render(scroll_rect, self._content_height, self._scroll_offset)
    draw_list_scroll_fades(scroll_rect, self._content_height, self._scroll_offset,
                           AetherListColors.PANEL_BG)

    for key in self._controller.VOLUME_KEYS:
      adjustor = self._adjustor_rows[key]
      is_interacting = adjustor.is_interacting
      if self._was_interacting.get(key, False) and not is_interacting:
        self._controller._test_sound(key)
      if adjustor._preset_applied:
        adjustor._preset_applied = False
        self._controller._test_sound(key)
      self._was_interacting[key] = is_interacting

  def _measure_content_height(self, content_width: float) -> float:
    col_width = (content_width - SECTION_GAP) / 2
    left_h = 0.0
    for key in self._controller.VOLUME_KEYS:
      left_h += self._adjustor_rows[key].measure_height(col_width)
    left_h += GROUP_HEADER_HEIGHT + GROUP_HEADER_GAP
    left_h += GROUP_HEADER_HEIGHT + GROUP_HEADER_GAP
    left_h += GROUP_HEADER_HEIGHT + GROUP_HEADER_GAP

    cd_h = self._adjustor_rows[self._controller.COOLDOWN_KEY].measure_height(col_width)
    group_h = GROUP_HEADER_HEIGHT + GROUP_HEADER_GAP
    self._tile_grid_h = left_h - cd_h - group_h

    right_h = cd_h + group_h + self._tile_grid_h

    section_overhead = SECTION_HEADER_HEIGHT + SECTION_HEADER_GAP
    return section_overhead + max(left_h, right_h) + 12.0

  def _draw_header(self, rect: rl.Rectangle):
    draw_settings_panel_header(rect, tr("Sounds & Alerts"), tr("Manage system volumes and custom alert toggles."), subtitle_size=24)

    btn_w = 120.0
    btn_h = 38.0
    btn_x = rect.x + rect.width - btn_w
    btn_y = rect.y + (rect.height - btn_h) / 2
    self._reset_rect = rl.Rectangle(btn_x, btn_y, btn_w, btn_h)

    hovered = _point_hits(gui_app.last_mouse_event.pos, self._reset_rect, self._scroll_rect, pad_x=6, pad_y=0)
    pressed = self._pressed_target == "action:restore_defaults"
    draw_action_pill(
      self._reset_rect, tr("Reset All"),
      rl.Color(255, 255, 255, 8 if not pressed else 14),
      rl.Color(255, 255, 255, 18 if not pressed else 28),
      AetherListColors.SUBTEXT if not hovered else AetherListColors.HEADER,
    )

  def _draw_scroll_content(self, rect: rl.Rectangle, content_width: float):
    y = rect.y + self._scroll_offset
    col_width = (content_width - SECTION_GAP) / 2

    draw_section_header(
      rl.Rectangle(rect.x, y, col_width, SECTION_HEADER_HEIGHT),
      tr("Volume"), style=PANEL_STYLE
    )
    draw_section_header(
      rl.Rectangle(rect.x + col_width + SECTION_GAP, y, col_width, SECTION_HEADER_HEIGHT),
      tr("Alerts"), style=PANEL_STYLE
    )
    y += SECTION_HEADER_HEIGHT + SECTION_HEADER_GAP

    col_left = rl.Rectangle(rect.x, y, col_width, self._content_height)
    col_right = rl.Rectangle(rect.x + col_width + SECTION_GAP, y, col_width, self._content_height)

    self._draw_volume_column(col_left)
    self._draw_utility_column(col_right)

  def _draw_group_header(self, x: float, y: float, width: float, label: str) -> float:
    gui_label(rl.Rectangle(x, y, width, GROUP_HEADER_HEIGHT), label, 14, GROUP_HEADER_COLOR, FontWeight.MEDIUM)
    y += GROUP_HEADER_HEIGHT
    rl.draw_line(int(x), int(y), int(x + width), int(y), GROUP_HAIRLINE_COLOR)
    return y + GROUP_HEADER_GAP

  def _draw_volume_column(self, rect: rl.Rectangle):
    safety_keys = ["WarningImmediateVolume", "WarningSoftVolume", "RefuseVolume", "PromptDistractedVolume"]
    system_keys = ["EngageVolume", "DisengageVolume"]
    info_keys = ["PromptVolume", "BelowSteerSpeedVolume"]

    groups = [
      (tr("SAFETY ALERTS"), safety_keys),
      (tr("SYSTEM STATE"), system_keys),
      (tr("INFORMATIONAL"), info_keys),
    ]

    total_h = sum(GROUP_HEADER_HEIGHT + GROUP_HEADER_GAP + sum(self._adjustor_rows[k].measure_height(rect.width) for k in keys) for _, keys in groups)
    draw_list_group_shell(
      rl.Rectangle(rect.x - 12, rect.y - 12, rect.width + 24, total_h + 24),
      style=PANEL_STYLE
    )

    current_y = rect.y
    for label, keys in groups:
      current_y = self._draw_group_header(rect.x, current_y, rect.width, label)
      for key in keys:
        adjustor = self._adjustor_rows[key]
        row_h = adjustor.measure_height(rect.width)
        row_rect = rl.Rectangle(rect.x, current_y, rect.width, row_h)
        adjustor.set_is_last(True)
        adjustor.set_parent_rect(self._scroll_rect)
        adjustor.render(row_rect)
        current_y += row_h

  def _draw_utility_column(self, rect: rl.Rectangle):
    current_y = rect.y

    cd_key = self._controller.COOLDOWN_KEY
    adjustor = self._adjustor_rows[cd_key]
    row_h = adjustor.measure_height(rect.width)
    adjustor.set_is_last(True)
    adjustor.set_parent_rect(self._scroll_rect)
    adjustor.render(rl.Rectangle(rect.x, current_y, rect.width, row_h))
    current_y += row_h

    current_y = self._draw_group_header(rect.x, current_y, rect.width, tr("CUSTOM ALERTS"))

    tile_grid_h = self._tile_grid_h

    tile_grid_rect = rl.Rectangle(rect.x - 12, current_y - 12, rect.width + 24, tile_grid_h + 24)
    draw_list_group_shell(tile_grid_rect, style=PANEL_STYLE)

    self._toggle_grid.set_parent_rect(self._scroll_rect)
    self._toggle_grid.render(rl.Rectangle(rect.x, current_y, rect.width, tile_grid_h))


class StarPilotSoundsLayout(_SettingsPage):
  COOLDOWN_KEY = "SwitchbackModeCooldown"
  VOLUME_KEYS = [
    "WarningImmediateVolume",
    "WarningSoftVolume",
    "RefuseVolume",
    "PromptDistractedVolume",
    "EngageVolume",
    "DisengageVolume",
    "PromptVolume",
    "BelowSteerSpeedVolume",
  ]
  CUSTOM_ALERTS_KEYS = [
    "GreenLightAlert",
    "LeadDepartingAlert",
    "LoudBlindspotAlert",
    "SpeedLimitChangedAlert",
  ]

  COOLDOWN_INFO = {
    "title": tr_noop("Switchback Mode Cooldown"),
    "subtitle": tr_noop("Time before switchback re-engages"),
    "min": 0,
    "max": 30,
  }
  VOLUME_INFO = {
    "WarningImmediateVolume": {"title": tr_noop("Immediate Warning"), "subtitle": tr_noop("Critical safety intervention"), "min": 25},
    "WarningSoftVolume": {"title": tr_noop("Soft Warning"), "subtitle": tr_noop("Approaching system limits"), "min": 25},
    "RefuseVolume": {"title": tr_noop("Engagement Refused"), "subtitle": tr_noop("Action refused by system"), "min": 0},
    "PromptDistractedVolume": {"title": tr_noop("Distracted Driver"), "subtitle": tr_noop("Driver attention required"), "min": 0},
    "EngageVolume": {"title": tr_noop("Engagement Chime"), "subtitle": tr_noop("System engaged confirmation"), "min": 0},
    "DisengageVolume": {"title": tr_noop("Disengagement Alert"), "subtitle": tr_noop("Handoff to manual control"), "min": 0},
    "PromptVolume": {"title": tr_noop("General Prompt"), "subtitle": tr_noop("System guidance prompt"), "min": 0},
    "BelowSteerSpeedVolume": {"title": tr_noop("Low Speed Alert"), "subtitle": tr_noop("Minimum speed for steering"), "min": 0},
  }

  _sound_player_process = None

  def __init__(self):
    super().__init__()
    self._init_sound_player()

    self.ALERT_INFO = {
      "GreenLightAlert": {
        "title": tr_noop("Green Light"),
        "subtitle": tr_noop("When lead car moves at green light"),
      },
      "LeadDepartingAlert": {
        "title": tr_noop("Lead Departure"),
        "subtitle": tr_noop("When lead vehicle pulls away"),
      },
      "LoudBlindspotAlert": {
        "title": tr_noop("Loud Blindspot"),
        "subtitle": tr_noop("Blind spot collision warning"),
        "is_enabled": lambda: starpilot_state.car_state.hasBSM,
        "disabled_label": tr_noop("Needs BSM")
      },
      "SpeedLimitChangedAlert": {
        "title": tr_noop("Speed Limit"),
        "subtitle": tr_noop("When posted speed limit changes"),
        "is_enabled": lambda: self._params.get_bool("ShowSpeedLimits") or (
          starpilot_state.car_state.hasOpenpilotLongitudinal and self._params.get_bool("SpeedLimitController")
        ),
        "disabled_label": tr_noop("Needs Speed Limits")
      },
    }

    self._manager_view = SoundsManagerView(self)

  def _restore_defaults(self):
    for key in self.VOLUME_KEYS:
      default = 25 if "Warning" in key else 100
      self._params.put_int(key, default)
    self._params.put_int(self.COOLDOWN_KEY, 0)
    for key in self.CUSTOM_ALERTS_KEYS:
      self._params.put_bool(key, False)

  @classmethod
  def _init_sound_player(cls):
    if cls._sound_player_process is not None and cls._sound_player_process.poll() is None: return
    program = """
import numpy as np
import sounddevice as sd
import sys
import wave
while True:
  try:
    line = sys.stdin.readline()
    if not line: break
    path, volume = line.strip().split('|')
    with wave.open(path, 'rb') as sound_file:
      audio = np.frombuffer(sound_file.readframes(sound_file.getnframes()), dtype=np.int16).astype(np.float32) / 32768.0
      sd.play(audio * float(volume), sound_file.getframerate())
    sd.wait()
  except Exception:
    sd._terminate()
    sd._initialize()
"""
    cls._sound_player_process = subprocess.Popen(["python3", "-u", "-c", program], stdin=subprocess.PIPE, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

  def _test_sound(self, key: str):
    base_name = key.replace("Volume", "")
    if ui_state.started:
      alert_name = "belowSteerSpeed" if base_name == "BelowSteerSpeed" else base_name[0].lower() + base_name[1:]
      self._params_memory.put("TestAlert", alert_name)
    else:
      self._play_sound_offroad(key)

  def _play_sound_offroad(self, key: str):
    base_name = key.replace("Volume", "")
    preview_base_name = "Prompt" if base_name == "BelowSteerSpeed" else base_name
    snake_case = "".join(["_" + c.lower() if c.isupper() else c for c in preview_base_name]).lstrip("_")
    stock_path = Path(BASEDIR) / "selfdrive" / "assets" / "sounds" / f"{snake_case}.wav"
    theme_path = ACTIVE_THEME_PATH / "sounds" / f"{snake_case}.wav"
    sound_path = theme_path if theme_path.exists() else stock_path
    if not sound_path.exists(): return
    volume = self._params.get_int(key, return_default=True, default=100) / 100.0
    if self._sound_player_process.poll() is not None:
      self._sound_player_process = None
      self._init_sound_player()
    try:
      self._sound_player_process.stdin.write(f"{sound_path}|{volume}\n".encode())
      self._sound_player_process.stdin.flush()
    except: pass
