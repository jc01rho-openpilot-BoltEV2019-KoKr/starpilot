import time

import pyray as rl

from openpilot.selfdrive.ui.lib.starpilot_status import get_border_color, get_mode_transition_banner_text
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.application import FontWeight
from openpilot.system.ui.widgets.label import UnifiedLabel


class ModeTransitionBanner:
  SHOW_TIME_SECONDS = 2.5

  def __init__(self, *, font_size: int = 34, width: int = 520, height: int = 72, top_margin: int = 22):
    self._last_mode: str | None = None
    self._visible_until = 0.0
    self._width = width
    self._height = height
    self._top_margin = top_margin
    self._label = UnifiedLabel(
      "",
      font_size,
      FontWeight.BOLD,
      text_color=rl.WHITE,
      alignment=rl.GuiTextAlignment.TEXT_ALIGN_CENTER,
      alignment_vertical=rl.GuiTextAlignmentVertical.TEXT_ALIGN_MIDDLE,
    )

  def update(self):
    current_mode = get_mode_transition_banner_text(ui_state) if ui_state.started else None

    if not ui_state.started:
      self._last_mode = None
      self._visible_until = 0.0
      return

    if not ui_state.params.get_bool("ShowModeStatusBanner", default=True):
      self._last_mode = current_mode
      self._visible_until = 0.0
      return

    if self._last_mode is None:
      self._last_mode = current_mode
      return

    if current_mode != self._last_mode:
      self._last_mode = current_mode
      if current_mode is not None:
        self._label.set_text(f"{current_mode} MODE")
        self._visible_until = time.monotonic() + self.SHOW_TIME_SECONDS

  def render(self, rect: rl.Rectangle):
    if (not ui_state.started or
        not ui_state.params.get_bool("ShowModeStatusBanner", default=True) or
        time.monotonic() > self._visible_until):
      return

    banner_width = min(rect.width - 120, self._width)
    banner_rect = rl.Rectangle(
      rect.x + (rect.width - banner_width) / 2,
      rect.y + self._top_margin,
      banner_width,
      self._height,
    )

    rl.draw_rectangle_rounded(banner_rect, 0.3, 12, rl.Color(0, 0, 0, 175))
    rl.draw_rectangle_rounded_lines_ex(banner_rect, 0.3, 12, 4, get_border_color(ui_state))
    self._label.render(banner_rect)
