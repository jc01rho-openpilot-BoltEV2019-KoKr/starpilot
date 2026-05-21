import pyray as rl
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.lib.starpilot_status import CEM_OVERRIDE_COLOR, EXPERIMENTAL_COLOR
from openpilot.system.ui.lib.text_measure import measure_text_cached

def render_cem_status(rect: rl.Rectangle, font):
  if not ui_state.params.get_bool("ShowCEMStatus"):
    return

  experimental_mode = ui_state.sm["selfdriveState"].experimentalMode
  cond_status = ui_state.conditional_status

  # Map status to text label
  status_labels = {
    1: "CHILL",
    2: "EXP",
    3: "CURVE",
    4: "LEAD",
    5: "TURN",
    6: "SLOW",
    7: "FAST",
    8: "STOP",
  }

  label = "CHILL"
  border_color = rl.Color(0, 0, 0, 166)

  if cond_status == 1:
    label = "CHILL"
    border_color = CEM_OVERRIDE_COLOR  # Yellow
  elif experimental_mode:
    label = status_labels.get(cond_status, "EXP")
    border_color = EXPERIMENTAL_COLOR  # Orange
  else:
    label = "CHILL"
    border_color = rl.Color(80, 80, 80, 255)

  # Draw background
  rl.draw_rectangle_rounded(rect, 0.3, 10, rl.Color(0, 0, 0, 166))
  # Draw border
  rl.draw_rectangle_rounded_lines_ex(rect, 0.3, 10, 4, border_color)

  # Draw text label centered inside the badge
  font_size = 20
  text_sz = measure_text_cached(font, label, font_size)
  pos_x = rect.x + (rect.width - text_sz.x) / 2
  pos_y = rect.y + (rect.height - text_sz.y) / 2
  rl.draw_text_ex(font, label, rl.Vector2(int(pos_x), int(pos_y)), font_size, 0, rl.WHITE)
