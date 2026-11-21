import time

import pyray as rl

from openpilot.selfdrive.navi_camera import traffic_signal_display
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.text_measure import draw_text_with_shadow, measure_text_cached

NAVI_DATA_TIMEOUT_S = 2.0
LIGHT_RADIUS = 34
LIGHT_GAP = 22
ROW_CENTER_Y = 380
TEXT_SIZE = 40

ON_COLORS = {
  "red": rl.Color(230, 45, 45, 255),
  "left": rl.Color(45, 200, 95, 255),
  "green": rl.Color(45, 200, 95, 255),
}
OFF_COLOR = rl.Color(70, 70, 70, 200)
HOUSING_COLOR = rl.Color(0, 0, 0, 150)
ARROW_COLOR = rl.Color(20, 20, 20, 255)


def _draw_left_arrow(cx: float, cy: float, r: float) -> None:
  head = r * 0.55
  rl.draw_triangle(rl.Vector2(cx - head, cy), rl.Vector2(cx, cy + head), rl.Vector2(cx, cy - head), ARROW_COLOR)
  rl.draw_rectangle_rec(rl.Rectangle(cx - 1, cy - head * 0.3, head, head * 0.6), ARROW_COLOR)


def render_traffic_signal(content_rect: rl.Rectangle, font) -> None:
  sm = ui_state.sm
  if time.monotonic() - sm.recv_time["naviData"] > NAVI_DATA_TIMEOUT_S:
    return
  navi = sm["naviData"]
  if not navi.active:
    return
  lights = traffic_signal_display(navi.ts)
  if lights is None:
    return

  diameter = LIGHT_RADIUS * 2
  row_width = len(lights) * diameter + (len(lights) - 1) * LIGHT_GAP
  start_x = content_rect.x + content_rect.width / 2 - row_width / 2
  pad = 12
  housing = rl.Rectangle(start_x - pad, ROW_CENTER_Y - LIGHT_RADIUS - pad, row_width + pad * 2, diameter + pad * 2)
  rl.draw_rectangle_rounded(housing, 0.5, 10, HOUSING_COLOR)

  for i, (light, on, remaining) in enumerate(lights):
    cx = start_x + LIGHT_RADIUS + i * (diameter + LIGHT_GAP)
    rl.draw_circle(int(cx), int(ROW_CENTER_Y), LIGHT_RADIUS, ON_COLORS[light] if on else OFF_COLOR)
    if light == "left":
      _draw_left_arrow(cx, ROW_CENTER_Y, LIGHT_RADIUS)
    if remaining > 0:
      text = str(remaining)
      size = measure_text_cached(font, text, TEXT_SIZE)
      pos = rl.Vector2(round(cx - size.x / 2), round(ROW_CENTER_Y + LIGHT_RADIUS + pad + 6))
      draw_text_with_shadow(font, text, pos, TEXT_SIZE, rl.WHITE)
