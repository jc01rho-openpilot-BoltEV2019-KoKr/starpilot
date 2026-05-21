import pyray as rl
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.text_measure import measure_text_cached

def render_stopping_point(renderer, font):
  params = ui_state.params
  if not params.get_bool("ShowStoppingPoint"):
    return

  plan = ui_state.sm["starpilotPlan"] if ui_state.sm.valid.get("starpilotPlan", False) else None
  if not plan or not plan.redLight:
    return

  model = ui_state.sm["modelV2"] if ui_state.sm.valid.get("modelV2", False) else None
  if not model or not len(model.position.x):
    return

  stopping_distance = model.position.x[min(32, len(model.position.x) - 1)]

  # Get the end of the projected path on the screen
  projected = renderer._path.projected_points
  if projected.size < 4:
    return

  mid_idx = len(projected) // 2
  v_left = projected[mid_idx - 1]
  v_right = projected[mid_idx]
  cx = (v_left[0] + v_right[0]) / 2.0
  cy = (v_left[1] + v_right[1]) / 2.0

  # Draw programmatic stop sign (octagon)
  radius = 35.0
  # Draw white outer octagon
  rl.draw_poly(rl.Vector2(int(cx), int(cy - radius)), 8, radius, 22.5, rl.WHITE)
  # Draw red inner octagon
  rl.draw_poly(rl.Vector2(int(cx), int(cy - radius)), 8, radius - 4, 22.5, rl.Color(196, 30, 58, 255))

  # Draw "STOP" text centered in octagon
  font_size = 18
  lbl_sz = measure_text_cached(font, "STOP", font_size)
  rl.draw_text_ex(
    font, "STOP",
    rl.Vector2(int(cx - lbl_sz.x / 2), int(cy - radius - lbl_sz.y / 2)),
    font_size, 0, rl.WHITE
  )

  # Draw metrics if enabled
  if params.get_bool("ShowStoppingPointMetrics"):
    is_metric = ui_state.is_metric
    if is_metric:
      dist_text = f"{int(round(stopping_distance))} m"
    else:
      dist_text = f"{int(round(stopping_distance * 3.28084))} ft"

    text_sz = measure_text_cached(font, dist_text, 24)
    tx = cx - text_sz.x / 2
    ty = cy - radius * 2 - text_sz.y - 5

    # Draw black outline/shadow text
    rl.draw_text_ex(font, dist_text, rl.Vector2(int(tx - 1), int(ty - 1)), 24, 0, rl.BLACK)
    rl.draw_text_ex(font, dist_text, rl.Vector2(int(tx + 1), int(ty - 1)), 24, 0, rl.BLACK)
    rl.draw_text_ex(font, dist_text, rl.Vector2(int(tx - 1), int(ty + 1)), 24, 0, rl.BLACK)
    rl.draw_text_ex(font, dist_text, rl.Vector2(int(tx + 1), int(ty + 1)), 24, 0, rl.BLACK)
    # Draw white text
    rl.draw_text_ex(font, dist_text, rl.Vector2(int(tx), int(ty)), 24, 0, rl.WHITE)
