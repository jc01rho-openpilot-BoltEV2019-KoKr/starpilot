import pyray as rl
from openpilot.selfdrive.ui.ui_state import ui_state, UIStatus
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.selfdrive.ui.onroad.starpilot.widgets.base import LayoutWidget
from openpilot.selfdrive.ui.onroad.hud_renderer import (
  UI_CONFIG, FONT_SIZES, COLORS, CRUISE_DISABLED_CHAR
)

class SetSpeedWidget(LayoutWidget):
  def __init__(self, hud_renderer):
    super().__init__("set_speed", priority=1)
    self.hud_renderer = hud_renderer
    self._font_semi_bold = gui_app.font(FontWeight.SEMI_BOLD)
    self._font_bold = gui_app.font(FontWeight.BOLD)

  @property
  def is_visible(self) -> bool:
    return (
      self.hud_renderer.is_cruise_available
      and not ui_state.starpilot_toggles.get("hide_max_speed", False)
    )

  def get_size(self) -> tuple[float, float]:
    set_speed_width = (
      UI_CONFIG.set_speed_width_metric
      if ui_state.is_metric
      else UI_CONFIG.set_speed_width_imperial
    )
    return float(set_speed_width), float(UI_CONFIG.set_speed_height)

  def _render(self, rect: rl.Rectangle) -> None:
    rl.draw_rectangle_rounded(rect, 0.35, 10, COLORS.BLACK_TRANSLUCENT)
    rl.draw_rectangle_rounded_lines_ex(rect, 0.35, 10, 6, COLORS.BORDER_TRANSLUCENT)

    max_color = COLORS.GREY
    set_speed_color = COLORS.DARK_GREY
    if self.hud_renderer.is_cruise_set:
      set_speed_color = COLORS.WHITE
      if ui_state.status == UIStatus.ENGAGED:
        max_color = COLORS.ENGAGED
      elif ui_state.status == UIStatus.DISENGAGED:
        max_color = COLORS.DISENGAGED
      elif ui_state.status == UIStatus.OVERRIDE:
        max_color = COLORS.OVERRIDE

    max_text = tr("MAX")
    max_text_width = measure_text_cached(self._font_semi_bold, max_text, FONT_SIZES.max_speed).x
    rl.draw_text_ex(
      self._font_semi_bold,
      max_text,
      rl.Vector2(rect.x + (rect.width - max_text_width) / 2, rect.y + 27),
      FONT_SIZES.max_speed,
      0,
      max_color,
    )

    set_speed_text = (
      CRUISE_DISABLED_CHAR
      if not self.hud_renderer.is_cruise_set
      else str(round(self.hud_renderer.set_speed))
    )
    speed_text_width = measure_text_cached(self._font_bold, set_speed_text, FONT_SIZES.set_speed).x
    rl.draw_text_ex(
      self._font_bold,
      set_speed_text,
      rl.Vector2(rect.x + (rect.width - speed_text_width) / 2, rect.y + 77),
      FONT_SIZES.set_speed,
      0,
      set_speed_color,
    )
