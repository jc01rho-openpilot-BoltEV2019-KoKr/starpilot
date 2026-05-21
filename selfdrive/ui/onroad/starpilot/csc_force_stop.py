import pyray as rl
import math
from openpilot.common.constants import CV
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.text_measure import measure_text_cached

def render_csc_force_stop(content_rect: rl.Rectangle, font_bold):
  plan = ui_state.sm["starpilotPlan"] if ui_state.sm.valid.get("starpilotPlan", False) else None
  if not plan:
    return

  forcing_stop = getattr(plan, "forcingStop", False)
  csc_enabled = getattr(plan, "curveSpeedControlEnabled", False)
  cond_status = ui_state.conditional_status

  if not forcing_stop and not (cond_status == 3 and csc_enabled):
    return

  # Calculate layout coordinates matching C++
  # setSpeedRect calculations:
  ss_width = 200 if ui_state.is_metric else 172
  ss_x = content_rect.x + 60 + (172 - ss_width) // 2
  ss_y = content_rect.y + 45
  ss_height = 204

  csc_x = ss_x + ss_width + 30
  csc_y = ss_y
  w = 215
  h = 215

  csc_rect = rl.Rectangle(csc_x, csc_y, w, h)
  badge_rect = rl.Rectangle(csc_x, csc_y + h + 10, w, 100)

  distance_conversion = 1.0 if ui_state.is_metric else 3.28084
  speed_conversion = CV.MS_TO_KPH if ui_state.is_metric else CV.MS_TO_MPH
  dist_unit = "m" if ui_state.is_metric else "ft"
  speed_unit = "km/h" if ui_state.is_metric else "mph"

  car_state = ui_state.sm["carState"] if ui_state.sm.valid.get("carState", False) else None
  v_ego = car_state.vEgo if car_state else 0.0

  if forcing_stop:
    # ── FORCE STOP MODE ──
    forcing_stop_length = getattr(plan, "forcingStopLength", 0.0)
    stop_sign_confirmed = getattr(plan, "stopSignConfirmed", False)

    # Draw Octagon Stop sign in csc_rect
    cx = csc_x + w / 2
    cy = csc_y + h / 2
    radius = 65.0
    rl.draw_poly(rl.Vector2(int(cx), int(cy)), 8, radius, 22.5, rl.WHITE)
    rl.draw_poly(rl.Vector2(int(cx), int(cy)), 8, radius - 5, 22.5, rl.Color(196, 30, 58, 255))

    if stop_sign_confirmed:
      # Draw white checkmark
      rl.draw_line_ex(rl.Vector2(int(cx - 20), int(cy)), rl.Vector2(int(cx - 5), int(cy + 15)), 6, rl.WHITE)
      rl.draw_line_ex(rl.Vector2(int(cx - 5), int(cy + 15)), rl.Vector2(int(cx + 25), int(cy - 15)), 6, rl.WHITE)
    else:
      # Draw white exclamation mark
      rl.draw_rectangle(int(cx - 4), int(cy - 25), 8, 30, rl.WHITE)
      rl.draw_circle(int(cx), int(cy + 18), 5, rl.WHITE)

    # Draw red badge with stopping distance
    rl.draw_rectangle_rounded(badge_rect, 0.24, 16, rl.Color(196, 30, 58, 166))
    rl.draw_rectangle_rounded_lines_ex(badge_rect, 0.24, 16, 4, rl.Color(255, 150, 150, 255))

    dist_val = int(round(forcing_stop_length * distance_conversion))
    text = f"{dist_val} {dist_unit}"
    text_sz = measure_text_cached(font_bold, text, 40)
    rl.draw_text_ex(font_bold, text, rl.Vector2(int(csc_x + 20), int(badge_rect.y + (100 - text_sz.y) / 2)), 40, 0, rl.WHITE)

  else:
    # ── CURVE SPEED CONTROL MODE ──
    csc_speed = getattr(plan, "cscSpeed", 0.0)
    road_curvature = getattr(plan, "roadCurvature", 0.0)

    # Pulsing glowing border for CSC icon
    phase = (rl.get_time() % 2.0) / 2.0 * 2.0 * math.pi
    alpha_factor = 0.5 + 0.5 * math.sin(phase)
    glow_color = rl.Color(0, 140, 255, int(255 * (0.3 + 0.7 * alpha_factor)))
    glow_width = int(8 + 4 * alpha_factor)

    rl.draw_rectangle_rounded(csc_rect, 0.24, 16, rl.Color(0, 0, 0, 166))
    rl.draw_rectangle_rounded_lines_ex(csc_rect, 0.24, 16, glow_width, glow_color)

    # Draw curvy path line inside csc_rect
    cx = csc_x + w / 2
    cy = csc_y + h / 2
    path_color = rl.Color(0, 140, 255, 255)
    
    # Draw curve left or right
    if road_curvature < 0:
      # Left curve spline
      p1 = rl.Vector2(int(cx), int(cy + 60))
      p2 = rl.Vector2(int(cx), int(cy - 20))
      p3 = rl.Vector2(int(cx - 50), int(cy - 50))
      rl.draw_spline_bezier_quadratic([p1, p2, p3], 3, 8, path_color)
      # Left arrowhead
      rl.draw_triangle(
        rl.Vector2(int(cx - 55), int(cy - 60)),
        rl.Vector2(int(cx - 35), int(cy - 40)),
        rl.Vector2(int(cx - 45), int(cy - 35)),
        path_color
      )
    else:
      # Right curve spline
      p1 = rl.Vector2(int(cx), int(cy + 60))
      p2 = rl.Vector2(int(cx), int(cy - 20))
      p3 = rl.Vector2(int(cx + 50), int(cy - 50))
      rl.draw_spline_bezier_quadratic([p1, p2, p3], 3, 8, path_color)
      # Right arrowhead
      rl.draw_triangle(
        rl.Vector2(int(cx + 55), int(cy - 60)),
        rl.Vector2(int(cx + 45), int(cy - 35)),
        rl.Vector2(int(cx + 35), int(cy - 40)),
        path_color
      )

    # Draw blue badge with CSC speed target
    rl.draw_rectangle_rounded(badge_rect, 0.24, 16, rl.Color(0, 140, 255, 166))
    rl.draw_rectangle_rounded_lines_ex(badge_rect, 0.24, 16, 4, rl.Color(100, 200, 255, 255))

    csc_speed_val = int(round(min(v_ego, csc_speed) * speed_conversion))
    text = f"{csc_speed_val} {speed_unit}"
    text_sz = measure_text_cached(font_bold, text, 40)
    rl.draw_text_ex(font_bold, text, rl.Vector2(int(csc_x + 20), int(badge_rect.y + (100 - text_sz.y) / 2)), 40, 0, rl.WHITE)
