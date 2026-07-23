import pyray as rl
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.selfdrive.ui.onroad.starpilot.widgets.base import LayoutWidget
from openpilot.selfdrive.ui.onroad.starpilot.aethergauge import AetherGauge

class AetherGaugeWidget(LayoutWidget):
  def __init__(self, hud_renderer):
    super().__init__("aethergauge", priority=3)
    self.hud_renderer = hud_renderer
    self._aethergauge = AetherGauge()
    self._font_bold = gui_app.font(FontWeight.BOLD)
    self._font_medium = gui_app.font(FontWeight.MEDIUM)
    self._alpha_filter = FirstOrderFilter(0.0, 0.3, 1 / gui_app.target_fps)

  @property
  def is_visible(self) -> bool:
    return self._aethergauge.has_active_source()

  def get_size(self) -> tuple[float, float]:
    # Width 180, height 250 covers the road visual and the mini text cradle
    return 180.0, 250.0

  def _render(self, rect: rl.Rectangle) -> None:
    target = 1.0 if self._aethergauge.has_active_source() else 0.0
    alpha = self._alpha_filter.update(target)
    if alpha < 0.02:
      return
    cx = rect.x + rect.width / 2
    # Set the road bottom to rect.y + 130, leaving 120px for the text cradle underneath
    bottom = rect.y + 130
    self._aethergauge.render(
      rect, self._font_bold, self._font_medium,
      current_speed=self.hud_renderer.speed,
      cx=cx,
      bottom=bottom,
      alpha=alpha,
    )
