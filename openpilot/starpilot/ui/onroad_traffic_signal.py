"""NDA (road-limit v2) traffic signal overlay for the large onroad view. Display only."""

import time

import pyray as rl

from openpilot.selfdrive.navi_camera import traffic_signal_display
from openpilot.starpilot.ui.presentation import FontRole

NAVI_DATA_TIMEOUT_S = 2.0
LIGHT_RADIUS = 34
LIGHT_GAP = 22
ROW_OFFSET_Y = 350
TEXT_SIZE = 40
PAD = 12

ON_COLORS = {
  "red": rl.Color(230, 45, 45, 255),
  "left": rl.Color(45, 200, 95, 255),
  "green": rl.Color(45, 200, 95, 255),
}
OFF_COLOR = rl.Color(70, 70, 70, 200)
HOUSING_COLOR = rl.Color(0, 0, 0, 150)
ARROW_COLOR = rl.Color(20, 20, 20, 255)
SHADOW_COLOR = rl.Color(0, 0, 0, 170)


def fresh_lights(sm, now: float):
  if "naviData" not in sm.data or now - sm.recv_time["naviData"] > NAVI_DATA_TIMEOUT_S:
    return None
  navi = sm["naviData"]
  if not navi.active:
    return None
  return traffic_signal_display(navi.ts)


def _draw_left_arrow(cx: float, cy: float, r: float) -> None:
  head = r * 0.55
  rl.draw_triangle(rl.Vector2(cx - head, cy), rl.Vector2(cx, cy + head), rl.Vector2(cx, cy - head), ARROW_COLOR)
  rl.draw_rectangle_rec(rl.Rectangle(cx - 1, cy - head * 0.3, head, head * 0.6), ARROW_COLOR)


def render_traffic_signal(fonts, content: rl.Rectangle, sm) -> None:
  lights = fresh_lights(sm, time.monotonic())
  if lights is None:
    return

  diameter = LIGHT_RADIUS * 2
  row_width = len(lights) * diameter + (len(lights) - 1) * LIGHT_GAP
  start_x = content.x + content.width / 2 - row_width / 2
  center_y = content.y + ROW_OFFSET_Y
  housing = rl.Rectangle(start_x - PAD, center_y - LIGHT_RADIUS - PAD, row_width + PAD * 2, diameter + PAD * 2)
  rl.draw_rectangle_rounded(housing, 0.5, 10, HOUSING_COLOR)

  for i, (light, on, remaining) in enumerate(lights):
    cx = start_x + LIGHT_RADIUS + i * (diameter + LIGHT_GAP)
    rl.draw_circle(int(cx), int(center_y), LIGHT_RADIUS, ON_COLORS[light] if on else OFF_COLOR)
    if light == "left":
      _draw_left_arrow(cx, center_y, LIGHT_RADIUS)
    if remaining > 0:
      text = str(remaining)
      size = fonts.measure(text, FontRole.BOLD, TEXT_SIZE)
      x, y = round(cx - size.width / 2), round(center_y + LIGHT_RADIUS + PAD + 6)
      fonts.draw(text, FontRole.BOLD, TEXT_SIZE, x + 2, y + 2, SHADOW_COLOR)
      fonts.draw(text, FontRole.BOLD, TEXT_SIZE, x, y, rl.WHITE)
