import pyray as rl
import math
from openpilot.selfdrive.ui.ui_state import ui_state

def render_weather_icon(rect: rl.Rectangle):
  # Get weather parameters from starpilotPlan
  plan = ui_state.sm["starpilotPlan"] if ui_state.sm.valid.get("starpilotPlan", False) else None
  if not plan or plan.weatherId == 0:
    return

  weather_id = plan.weatherId
  weather_daytime = plan.weatherDaytime

  # Background color based on day/night
  bg_color = rl.Color(135, 206, 235, 255) if weather_daytime else rl.Color(25, 25, 112, 255)

  # Draw background badge
  rl.draw_rectangle_rounded(rect, 0.2, 10, bg_color)
  rl.draw_rectangle_rounded_lines_ex(rect, 0.2, 10, 4, rl.Color(0, 0, 0, 255))

  # Define weather conditions
  is_rain = (200 <= weather_id <= 232) or (300 <= weather_id <= 321) or (500 <= weather_id <= 531)
  is_snow = (600 <= weather_id <= 622)
  is_fog = (701 <= weather_id <= 762)

  # Scissor to avoid overflowing the rounded rectangle
  rl.begin_scissor_mode(int(rect.x + 4), int(rect.y + 4), int(rect.width - 8), int(rect.height - 8))

  cx = rect.x + rect.width / 2.0
  cy = rect.y + rect.height / 2.0

  if is_rain:
    # 1. Draw Gray Clouds
    rl.draw_circle(int(cx - 15), int(cy - 15), 18, rl.Color(180, 180, 180, 255))
    rl.draw_circle(int(cx + 15), int(cy - 12), 16, rl.Color(160, 160, 160, 255))
    rl.draw_circle(int(cx), int(cy - 20), 20, rl.Color(200, 200, 200, 255))

    # 2. Draw falling rain drops (slanted lines)
    drops = [
      (cx - 20, cy + 5),
      (cx - 5, cy + 12),
      (cx + 10, cy + 3),
      (cx + 22, cy + 10),
      (cx - 10, cy + 22),
      (cx + 12, cy + 20)
    ]
    rain_color = rl.Color(0, 191, 255, 255)
    for dx, dy in drops:
      rl.draw_line_ex(rl.Vector2(int(dx), int(dy)), rl.Vector2(int(dx - 3), int(dy + 12)), 3, rain_color)

  elif is_snow:
    # 1. Draw Clouds
    rl.draw_circle(int(cx - 15), int(cy - 15), 18, rl.Color(180, 180, 180, 255))
    rl.draw_circle(int(cx + 15), int(cy - 12), 16, rl.Color(160, 160, 160, 255))
    rl.draw_circle(int(cx), int(cy - 20), 20, rl.Color(200, 200, 200, 255))

    # 2. Draw snowflakes (white asterisks)
    flakes = [
      (cx - 20, cy + 10),
      (cx - 5, cy + 20),
      (cx + 12, cy + 8),
      (cx + 20, cy + 22)
    ]
    for fx, fy in flakes:
      # Draw asterisk snowflake
      rl.draw_line_ex(rl.Vector2(int(fx - 5), int(fy)), rl.Vector2(int(fx + 5), int(fy)), 2, rl.WHITE)
      rl.draw_line_ex(rl.Vector2(int(fx), int(fy - 5)), rl.Vector2(int(fx), int(fy + 5)), 2, rl.WHITE)
      rl.draw_line_ex(rl.Vector2(int(fx - 4), int(fy - 4)), rl.Vector2(int(fx + 4), int(fy + 4)), 2, rl.WHITE)
      rl.draw_line_ex(rl.Vector2(int(fx - 4), int(fy + 4)), rl.Vector2(int(fx + 4), int(fy - 4)), 2, rl.WHITE)

  elif is_fog:
    # Draw gray horizontal bands representing fog
    fog_color = rl.Color(220, 220, 220, 180)
    rl.draw_rectangle_rounded(rl.Rectangle(cx - 40, cy - 25, 80, 8), 0.5, 4, fog_color)
    rl.draw_rectangle_rounded(rl.Rectangle(cx - 50, cy - 10, 100, 8), 0.5, 4, fog_color)
    rl.draw_rectangle_rounded(rl.Rectangle(cx - 35, cy + 5, 70, 8), 0.5, 4, fog_color)
    rl.draw_rectangle_rounded(rl.Rectangle(cx - 45, cy + 20, 90, 8), 0.5, 4, fog_color)

  else:
    # Clear / Sun or Moon
    if weather_daytime:
      # Sun
      rl.draw_circle(int(cx), int(cy), 22, rl.GOLD)
      # Rays
      ray_color = rl.ORANGE
      for i in range(8):
        angle = i * (math.pi / 4.0)
        x1 = cx + 26 * math.cos(angle)
        y1 = cy + 26 * math.sin(angle)
        x2 = cx + 38 * math.cos(angle)
        y2 = cy + 38 * math.sin(angle)
        rl.draw_line_ex(rl.Vector2(int(x1), int(y1)), rl.Vector2(int(x2), int(y2)), 4, ray_color)
    else:
      # Moon
      rl.draw_circle(int(cx + 5), int(cy - 5), 24, rl.Color(255, 255, 224, 255))
      # Subtracted shadow to make crescent
      rl.draw_circle(int(cx - 3), int(cy - 11), 24, bg_color)

      # Tiny stars
      rl.draw_circle(int(cx - 25), int(cy - 20), 2, rl.WHITE)
      rl.draw_circle(int(cx + 28), int(cy + 15), 3, rl.WHITE)
      rl.draw_circle(int(cx - 20), int(cy + 25), 1.5, rl.WHITE)

  rl.end_scissor_mode()
