import pyray as rl
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.text_measure import measure_text_cached

def render_compass(rect: rl.Rectangle, font):
  if not ui_state.params.get_bool("Compass"):
    return

  # Retrieve bearing
  bearing = 0.0
  gps = ui_state.sm["gpsLocationExternal"] if ui_state.sm.valid.get("gpsLocationExternal", False) else None
  if gps and gps.bearingDeg != 0:
    bearing = gps.bearingDeg
  else:
    try:
      last_gps = ui_state.params_memory.get("LastGPSPosition")
      if last_gps:
        import json
        data = json.loads(last_gps)
        bearing = data.get("bearing", 0.0)
    except Exception:
      pass

  # Draw background
  rl.draw_rectangle_rounded(rect, 0.2, 10, rl.Color(0, 0, 0, 166))
  rl.draw_rectangle_rounded_lines_ex(rect, 0.2, 10, 4, rl.Color(0, 0, 0, 255))

  # Clip ribbon to widget boundary
  rl.begin_scissor_mode(int(rect.x + 4), int(rect.y + 4), int(rect.width - 8), int(rect.height - 8))

  # Display range: +/- 45 degrees
  range_deg = 45
  pixels_per_degree = rect.width / (range_deg * 2.0)

  start_deg = int(bearing - range_deg)
  end_deg = int(bearing + range_deg) + 1

  labels = {0: "N", 45: "NE", 90: "E", 135: "SE", 180: "S", 225: "SW", 270: "W", 315: "NW"}

  for deg in range(start_deg, end_deg):
    norm_deg = (deg + 360) % 360
    offset_deg = deg - bearing
    x = rect.x + rect.width / 2.0 + offset_deg * pixels_per_degree

    if rect.x <= x <= rect.x + rect.width:
      if norm_deg % 45 == 0:
        notch_height = 25
        notch_width = 3
        lbl = labels.get(norm_deg, "")
        if lbl:
          lbl_sz = measure_text_cached(font, lbl, 22)
          rl.draw_text_ex(font, lbl, rl.Vector2(int(x - lbl_sz.x / 2), int(rect.y + 12)), 22, 0, rl.WHITE)
      elif norm_deg % 15 == 0:
        notch_height = 15
        notch_width = 2
      elif norm_deg % 5 == 0:
        notch_height = 8
        notch_width = 1
      else:
        continue

      y_start = rect.y + rect.height - notch_height - 10
      y_end = rect.y + rect.height - 10
      rl.draw_line_ex(rl.Vector2(int(x), int(y_start)), rl.Vector2(int(x), int(y_end)), notch_width, rl.WHITE)

  rl.end_scissor_mode()

  # Draw static triangular pointer pointing UP at bottom center
  triangle_size = 12
  tx = rect.x + rect.width / 2
  ty = rect.y + rect.height - 12
  v1 = rl.Vector2(int(tx), int(ty - triangle_size))
  v2 = rl.Vector2(int(tx - triangle_size / 1.5), int(ty))
  v3 = rl.Vector2(int(tx + triangle_size / 1.5), int(ty))
  rl.draw_triangle(v1, v2, v3, rl.WHITE)
