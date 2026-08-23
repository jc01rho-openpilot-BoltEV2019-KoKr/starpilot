import pyray as rl

from openpilot.system.ui.lib.application import FontWeight, gui_app
from openpilot.system.ui.lib.text_measure import draw_text_with_shadow, measure_text_cached


PULSE_COLOR = rl.Color(52, 190, 112, 255)
GLIDE_COLOR = rl.Color(65, 155, 235, 255)
BANNER_BACKGROUND = rl.Color(0, 0, 0, 210)


def render_pulse_glide(rect: rl.Rectangle, coasting: bool) -> None:
  """Render the developer-only P&G phase badge beside the standard HUD badges."""
  border = GLIDE_COLOR if coasting else PULSE_COLOR
  label = "GLIDE" if coasting else "PULSE"
  font = gui_app.font(FontWeight.BOLD)
  font_size = 27
  text_size = measure_text_cached(font, label, font_size)

  rl.draw_rectangle_rounded(rect, 0.3, 10, rl.Color(0, 0, 0, 166))
  rl.draw_rectangle_rounded_lines_ex(rect, 0.3, 10, 4, border)
  draw_text_with_shadow(
    font,
    label,
    rl.Vector2(rect.x + (rect.width - text_size.x) / 2, rect.y + (rect.height - text_size.y) / 2),
    font_size,
    rl.WHITE,
  )


def render_pulse_glide_banner(content_rect: rl.Rectangle, coasting: bool) -> None:
  """Render a non-alert on-road status banner while developer P&G is armed."""
  border = GLIDE_COLOR if coasting else PULSE_COLOR
  state_label = "GLIDING" if coasting else "PULSE"
  title_font = gui_app.font(FontWeight.MEDIUM)
  state_font = gui_app.font(FontWeight.BOLD)
  title_size = measure_text_cached(title_font, "PULSE & GLIDE", 22)
  state_size = measure_text_cached(state_font, state_label, 34)

  banner_w = max(340.0, title_size.x + 48.0, state_size.x + 96.0)
  banner_h = 86.0
  banner_rect = rl.Rectangle(
    content_rect.x + (content_rect.width - banner_w) / 2.0,
    content_rect.y + 28.0,
    banner_w,
    banner_h,
  )

  rl.draw_rectangle_rounded(banner_rect, 0.25, 12, BANNER_BACKGROUND)
  rl.draw_rectangle_rounded_lines_ex(banner_rect, 0.25, 12, 4, border)

  title_pos = rl.Vector2(
    banner_rect.x + (banner_rect.width - title_size.x) / 2.0,
    banner_rect.y + 10.0,
  )
  state_pos = rl.Vector2(
    banner_rect.x + (banner_rect.width - state_size.x) / 2.0,
    banner_rect.y + 38.0,
  )
  draw_text_with_shadow(title_font, "PULSE & GLIDE", title_pos, 22, rl.WHITE)
  draw_text_with_shadow(state_font, state_label, state_pos, 34, rl.WHITE)
