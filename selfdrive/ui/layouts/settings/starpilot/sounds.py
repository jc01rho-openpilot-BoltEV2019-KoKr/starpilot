from __future__ import annotations
import subprocess
from pathlib import Path

import pyray as rl

from openpilot.common.basedir import BASEDIR
from openpilot.starpilot.common.starpilot_variables import ACTIVE_THEME_PATH
from openpilot.system.ui.lib.application import gui_app, MouseEvent, MousePos
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.widgets import Widget
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.lib.starpilot_state import starpilot_state
from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import StarPilotPanel
from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import (
  AETHER_LIST_METRICS,
  AetherAdjustorRow,
  AetherListColors,
  panel_style_from_color,
  _point_hits,
  draw_settings_panel_header,
  draw_toggle_pill,
  init_list_panel,
)

PANEL_STYLE = panel_style_from_color("#E63956")
SECTION_GAP = AETHER_LIST_METRICS.section_gap



class SoundsManagerView(Widget):
  def __init__(self, controller: "StarPilotSoundsLayout"):
    super().__init__()
    self._controller = controller
    self._pressed_target: str | None = None
    self._adjustor_rows: dict[str, AetherAdjustorRow] = {}
    self._was_interacting: dict[str, bool] = {}
    self._toggle_rects: dict[str, rl.Rectangle] = {}
    self._active_adjustor_key: str | None = None

    self._init_adjustors()

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
        "",
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
    def on_cd_commit(v):
      self._controller._params.put_int(cd_key, int(v))

    cd_adjustor = AetherAdjustorRow(
      tr(self._controller.COOLDOWN_INFO["title"]),
      "",
      0.0, float(self._controller.COOLDOWN_INFO["max"]), 1.0,
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
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_press(mouse_pos)

  def _handle_mouse_release(self, mouse_pos: MousePos):
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_release(mouse_pos)

    target = self._target_at(mouse_pos)
    if self._pressed_target is not None and self._pressed_target == target:
      self._activate_target(target)
    self._pressed_target = None

  def _handle_mouse_event(self, mouse_event: MouseEvent):
    for adjustor in self._adjustor_rows.values():
      adjustor._handle_mouse_event(mouse_event)

  def _target_at(self, mouse_pos: MousePos) -> str | None:
    for key, rect in self._toggle_rects.items():
      if _point_hits(mouse_pos, rect, pad_x=6, pad_y=6):
        return f"toggle:{key}"
    return None

  def _activate_target(self, target: str):
    if target.startswith("toggle:"):
      key = target.split(":", 1)[1]
      info = self._controller.ALERT_INFO.get(key)
      if info and info.get("is_enabled", lambda: True)():
        current = self._controller._params.get_bool(key)
        self._controller._params.put_bool(key, not current)

  def _render(self, rect: rl.Rectangle):
    self.set_rect(rect)
    self._toggle_rects.clear()

    frame, _scroll_rect, _content_width = init_list_panel(rect, PANEL_STYLE)

    self._draw_header(frame.header)

    metrics = AETHER_LIST_METRICS
    actual_header_height = 100
    content_y = frame.header.y + actual_header_height
    content_h = (frame.shell.y + frame.shell.height) - content_y - metrics.panel_padding_bottom

    col_width = (frame.scroll.width - SECTION_GAP) / 2
    col_left = rl.Rectangle(frame.scroll.x, content_y, col_width, content_h)
    col_right = rl.Rectangle(frame.scroll.x + col_width + SECTION_GAP, content_y, col_width, content_h)

    self._draw_volume_column(col_left)
    self._draw_utility_column(col_right)

    for key in self._controller.VOLUME_KEYS:
      adjustor = self._adjustor_rows[key]
      is_interacting = adjustor.is_interacting
      if self._was_interacting.get(key, False) and not is_interacting:
        self._controller._test_sound(key)
      if adjustor._preset_applied:
        adjustor._preset_applied = False
        self._controller._test_sound(key)
      self._was_interacting[key] = is_interacting

  def _draw_header(self, rect: rl.Rectangle):
    draw_settings_panel_header(rect, tr("Sounds & Alerts"), tr("Manage system volumes and custom alert toggles."), subtitle_size=24)

  def _draw_volume_column(self, rect: rl.Rectangle):
    current_y = rect.y
    for key in self._controller.VOLUME_KEYS:
      adjustor = self._adjustor_rows[key]
      row_h = adjustor.measure_height(rect.width)
      row_rect = rl.Rectangle(rect.x, current_y, rect.width, row_h)
      adjustor.set_is_last(True)
      adjustor.set_parent_rect(rect)
      adjustor.render(row_rect)
      current_y += row_h

  def _draw_utility_column(self, rect: rl.Rectangle):
    current_y = rect.y

    cd_key = self._controller.COOLDOWN_KEY
    adjustor = self._adjustor_rows[cd_key]
    row_h = adjustor.measure_height(rect.width)
    adjustor.set_is_last(True)
    adjustor.set_parent_rect(rect)
    adjustor.render(rl.Rectangle(rect.x, current_y, rect.width, row_h))
    current_y += row_h

    toggle_h = AETHER_LIST_METRICS.utility_row_height
    for i, key in enumerate(self._controller.CUSTOM_ALERTS_KEYS):
      row_rect = rl.Rectangle(rect.x, current_y, rect.width, toggle_h)
      self._draw_toggle_row(row_rect, key, self._controller.ALERT_INFO[key])
      current_y += toggle_h

  def _draw_toggle_row(self, rect: rl.Rectangle, key: str, info: dict):
    padded_rect = rl.Rectangle(rect.x, rect.y + 4, rect.width - 12, rect.height - 8)

    current_val = self._controller._params.get_bool(key)
    is_enabled = info.get("is_enabled", lambda: True)()

    mouse_pos = gui_app.last_mouse_event.pos
    hovered = _point_hits(mouse_pos, padded_rect, pad_x=6, pad_y=6)
    pressed = self._pressed_target == f"toggle:{key}"

    status_str = tr("ON") if current_val else tr("OFF")
    if not is_enabled: status_str = tr(info.get("disabled_label", "UNAVAILABLE"))

    draw_toggle_pill(padded_rect, current_val, is_enabled, tr(info["title"]), status_str, hovered, pressed, style=PANEL_STYLE)

    self._toggle_rects[key] = padded_rect


class StarPilotSoundsLayout(StarPilotPanel):
  COOLDOWN_KEY = "SwitchbackModeCooldown"
  VOLUME_KEYS = [
    "BelowSteerSpeedVolume",
    "DisengageVolume",
    "EngageVolume",
    "PromptVolume",
    "PromptDistractedVolume",
    "RefuseVolume",
    "WarningSoftVolume",
    "WarningImmediateVolume",
  ]
  CUSTOM_ALERTS_KEYS = [
    "GoatScream",
    "GoatScreamCriticalAlerts",
    "GreenLightAlert",
    "LeadDepartingAlert",
    "LoudBlindspotAlert",
    "SpeedLimitChangedAlert",
  ]

  COOLDOWN_INFO = {"title": tr_noop("Switchback Mode Cooldown"), "min": 0, "max": 30}
  VOLUME_INFO = {
    "BelowSteerSpeedVolume": {"title": tr_noop("Min Steer Speed Alert"), "min": 0},
    "DisengageVolume": {"title": tr_noop("Disengage Volume"), "min": 0},
    "EngageVolume": {"title": tr_noop("Engage Volume"), "min": 0},
    "PromptVolume": {"title": tr_noop("Prompt Volume"), "min": 0},
    "PromptDistractedVolume": {"title": tr_noop("Distracted Volume"), "min": 0},
    "RefuseVolume": {"title": tr_noop("Refuse Volume"), "min": 0},
    "WarningSoftVolume": {"title": tr_noop("Warning Soft"), "min": 25},
    "WarningImmediateVolume": {"title": tr_noop("Warning Immediate"), "min": 25},
  }

  _sound_player_process = None

  def __init__(self):
    super().__init__()
    self._init_sound_player()

    self.ALERT_INFO = {
      "GoatScream": {"title": tr_noop("Goat Scream")},
      "GoatScreamCriticalAlerts": {"title": tr_noop("Goat Critical")},
      "GreenLightAlert": {"title": tr_noop("Green Light")},
      "LeadDepartingAlert": {"title": tr_noop("Lead Departure")},
      "LoudBlindspotAlert": {
        "title": tr_noop("Loud Blindspot"),
        "is_enabled": lambda: starpilot_state.car_state.hasBSM,
        "disabled_label": tr_noop("Needs BSM")
      },
      "SpeedLimitChangedAlert": {
        "title": tr_noop("Speed Limit"),
        "is_enabled": lambda: self._params.get_bool("ShowSpeedLimits") or (
          starpilot_state.car_state.hasOpenpilotLongitudinal and self._params.get_bool("SpeedLimitController")
        ),
        "disabled_label": tr_noop("Needs Speed Limits")
      },
    }

    self._manager_view = SoundsManagerView(self)

  def _render(self, rect: rl.Rectangle):
    self._manager_view.render(rect)

  def show_event(self):
    super().show_event()

  def hide_event(self):
    super().hide_event()

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
