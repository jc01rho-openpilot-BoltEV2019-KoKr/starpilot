import pyray as rl
from openpilot.selfdrive.ui.lib.starpilot_status import TRAFFIC_COLOR

def draw_pause_symbol(cx: float, cy: float):
  # Draw two vertical bars || in the center
  rl.draw_rectangle(int(cx - 8), int(cy - 16), 5, 32, rl.WHITE)
  rl.draw_rectangle(int(cx + 3), int(cy - 16), 5, 32, rl.WHITE)

def render_lateral_paused(rect: rl.Rectangle):
  # Draw background & red border
  rl.draw_rectangle_rounded(rect, 0.3, 10, rl.Color(0, 0, 0, 166))
  rl.draw_rectangle_rounded_lines_ex(rect, 0.3, 10, 4, TRAFFIC_COLOR)

  cx = rect.x + rect.width / 2.0
  cy = rect.y + rect.height / 2.0

  # Draw turn/curved arrow icon (translucent)
  rl.draw_ring(rl.Vector2(int(cx), int(cy)), 20, 24, 45, 315, 0, rl.Color(255, 255, 255, 100))
  # Arrowhead
  rl.draw_triangle(
    rl.Vector2(int(cx + 12), int(cy - 20)),
    rl.Vector2(int(cx + 25), int(cy - 12)),
    rl.Vector2(int(cx + 20), int(cy - 25)),
    rl.Color(255, 255, 255, 100)
  )

  # Draw pause overlay
  draw_pause_symbol(cx, cy)

def render_longitudinal_paused(rect: rl.Rectangle):
  # Draw background & red border
  rl.draw_rectangle_rounded(rect, 0.3, 10, rl.Color(0, 0, 0, 166))
  rl.draw_rectangle_rounded_lines_ex(rect, 0.3, 10, 4, TRAFFIC_COLOR)

  cx = rect.x + rect.width / 2.0
  cy = rect.y + rect.height / 2.0

  # Draw speedometer arc (translucent)
  rl.draw_ring(rl.Vector2(int(cx), int(cy + 8)), 20, 24, -45, 225, 0, rl.Color(255, 255, 255, 100))
  # Needle
  rl.draw_line_ex(
    rl.Vector2(int(cx), int(cy + 8)),
    rl.Vector2(int(cx + 14), int(cy - 6)),
    3,
    rl.Color(255, 255, 255, 100)
  )

  # Draw pause overlay
  draw_pause_symbol(cx, cy)
