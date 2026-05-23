from dataclasses import dataclass
import math
import pyray as rl
from openpilot.common.constants import CV
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.selfdrive.ui.onroad.starpilot.starpilot_border import _csc_state, _intensity, _glow_color

@dataclass
class AetherGaugeData:
  text: str
  unit: str = ""
  label: str = ""
  animation: str = "none" # e.g. "down_arrows"
  color: rl.Color = rl.WHITE
  indicator_type: str = "none" # e.g. "road_curve"
  indicator_value: float = 0.0 # value used by indicator (e.g. curvature)

class AetherGaugeSource:
  def is_active(self) -> bool:
    return False

  def get_gauge_data(self) -> AetherGaugeData:
    raise NotImplementedError

class CurveSpeedSource(AetherGaugeSource):
  def is_active(self) -> bool:
    state = _csc_state()
    return state is not None and state['active']

  def get_gauge_data(self) -> AetherGaugeData:
    state = _csc_state()
    if state is None:
      return AetherGaugeData(text="")
      
    plan = ui_state.sm["starpilotPlan"]
    car_state = ui_state.sm["carState"]
    
    speed_conversion = CV.MS_TO_KPH if ui_state.is_metric else CV.MS_TO_MPH
    speed_unit = "km/h" if ui_state.is_metric else "mph"
    
    csc_speed = getattr(plan, "cscSpeed", 0.0)
    v_ego = car_state.vEgo if car_state else 0.0
    
    csc_speed_val = int(round(min(v_ego, csc_speed) * speed_conversion))
    
    intensity = _intensity(state['curvature'])
    color = _glow_color(intensity)
    
    return AetherGaugeData(
      text=str(csc_speed_val),
      unit=speed_unit,
      label="CURVE",
      animation="down_arrows",
      color=color,
      indicator_type="road_curve",
      indicator_value=state['curvature']
    )

class AetherGauge:
  def __init__(self):
    self.sources: list[AetherGaugeSource] = [CurveSpeedSource()]

  def get_active_data(self) -> AetherGaugeData | None:
    for source in self.sources:
      if source.is_active():
        return source.get_gauge_data()
    return None

  def render(self, rect: rl.Rectangle, font_bold: rl.Font, font_medium: rl.Font, current_speed: float):
    data = self.get_active_data()
    if not data:
      return

    cx = rect.x + rect.width / 2
    # Vertical center of travel speed text is exactly at rect.y + 180 (matching hud_renderer.py)
    cy_speed = rect.y + 180

    speed_text = str(round(current_speed))
    speed_text_size = measure_text_cached(font_bold, speed_text, 176)

    # Position the curving road widget to the left of the speed text, center-aligned vertically
    icon_cx = cx - speed_text_size.x / 2 - 70.0

    if data.indicator_type == "road_curve":
      self._render_unified_road(icon_cx, cy_speed, data, font_bold, font_medium)

  def _render_unified_road(self, icx: float, icy: float, data: AetherGaugeData, font_bold: rl.Font, font_medium: rl.Font):
    # Dimensions of the road projection
    half_size = 40.0
    bottom = icy + half_size
    top = icy - half_size
    
    # Non-linear curvature offset
    abs_curv = abs(data.indicator_value)
    sign = math.copysign(1.0, data.indicator_value) if data.indicator_value != 0.0 else 1.0
    curve_offset = max(-half_size, min(half_size, sign * (abs_curv ** 0.5) * 300.0))
    
    # 3D perspective widths
    w_bottom = 28.0
    w_top = 14.0
    thickness = 4.0
    
    # Generate points along the road path
    num_segments = 16
    points_left = []
    points_right = []
    
    for i in range(num_segments + 1):
      t = i / num_segments
      # Center path quadratic bend
      offset = curve_offset * (t ** 2)
      cx_t = icx + offset
      y_t = bottom - t * 80.0
      
      # Perspective width interpolation
      w_t = w_bottom - t * (w_bottom - w_top)
      
      points_left.append(rl.Vector2(int(cx_t - w_t), int(y_t)))
      points_right.append(rl.Vector2(int(cx_t + w_t), int(y_t)))

    # A. Draw glowing road surface fill (glowing HUD look)
    fill_color = rl.Color(data.color.r, data.color.g, data.color.b, 35)
    for i in range(num_segments):
      rl.draw_triangle(points_left[i], points_right[i], points_left[i+1], fill_color)
      rl.draw_triangle(points_right[i], points_right[i+1], points_left[i+1], fill_color)

    # B. Draw left and right road boundaries
    shadow_color = rl.Color(0, 0, 0, 100)
    for i in range(num_segments):
      # Shadow lines
      rl.draw_line_ex(rl.Vector2(points_left[i].x, points_left[i].y + 2), rl.Vector2(points_left[i+1].x, points_left[i+1].y + 2), thickness, shadow_color)
      rl.draw_line_ex(rl.Vector2(points_right[i].x, points_right[i].y + 2), rl.Vector2(points_right[i+1].x, points_right[i+1].y + 2), thickness, shadow_color)
      
      # Main boundaries
      rl.draw_line_ex(points_left[i], points_left[i+1], thickness, data.color)
      rl.draw_line_ex(points_right[i], points_right[i+1], thickness, data.color)

    # C. Draw animating chevrons flowing down the road center path
    progress = (rl.get_time() * 1.2) % 1.0
    for i in range(3):
      # Chevron fraction t (flowing down from 1.0 to 0.0)
      t = 1.0 - ((i + progress) / 3.0)
      
      # Calculate local tangent vector for rotation
      t_next = min(1.0, t + 0.05)
      cx_t = icx + curve_offset * (t ** 2)
      cy_t = bottom - t * 80.0
      
      cx_next = icx + curve_offset * (t_next ** 2)
      cy_next = bottom - t_next * 80.0
      
      dx = cx_next - cx_t
      dy = cy_next - cy_t
      len_v = math.sqrt(dx**2 + dy**2)
      if len_v > 0.001:
        dir_up_x = dx / len_v
        dir_up_y = dy / len_v
      else:
        dir_up_x = 0.0
        dir_up_y = -1.0
        
      dir_right_x = -dir_up_y
      dir_right_y = dir_up_x
      
      # Perspective scaling of chevrons
      chevron_w = 14.0 - t * 6.0
      chevron_h = chevron_w * 0.6
      chevron_thick = max(2.0, 4.0 - t * 2.0)
      
      # Vertices
      lx = cx_t - dir_right_x * chevron_w + dir_up_x * chevron_h
      ly = cy_t - dir_right_y * chevron_w + dir_up_y * chevron_h
      rx = cx_t + dir_right_x * chevron_w + dir_up_x * chevron_h
      ry = cy_t + dir_right_y * chevron_w + dir_up_y * chevron_h
      
      # Alpha envelope fading in at horizon, bright in middle, fading out at bottom
      alpha_factor = math.sin(t * math.pi)
      alpha = int(data.color.a * alpha_factor)
      chev_color = rl.Color(data.color.r, data.color.g, data.color.b, alpha)
      chev_shadow = rl.Color(0, 0, 0, int(alpha * 0.5))
      
      # Draw chevron with shadow
      rl.draw_line_ex(rl.Vector2(int(lx), int(ly + 1.5)), rl.Vector2(int(cx_t), int(cy_t + 1.5)), chevron_thick, chev_shadow)
      rl.draw_line_ex(rl.Vector2(int(rx), int(ry + 1.5)), rl.Vector2(int(cx_t), int(cy_t + 1.5)), chevron_thick, chev_shadow)
      
      rl.draw_line_ex(rl.Vector2(int(lx), int(ly)), rl.Vector2(int(cx_t), int(cy_t)), chevron_thick, chev_color)
      rl.draw_line_ex(rl.Vector2(int(rx), int(ry)), rl.Vector2(int(cx_t), int(cy_t)), chevron_thick, chev_color)

    # D. Draw clean floating target speed directly below the road base
    self._draw_mini_cradle(icx, bottom + 25, data.text, data.unit, data.color, font_bold, font_medium)

  def _draw_mini_cradle(self, cx: float, cy: float, target_speed: str, unit: str, color: rl.Color, font_bold: rl.Font, font_medium: rl.Font):
    val_size = measure_text_cached(font_bold, target_speed, 48)
    unit_size = measure_text_cached(font_medium, unit, 24)
    
    gap = 6
    total_w = val_size.x + gap + unit_size.x
    start_x = cx - total_w / 2
    
    # Speed numbers
    val_pos = rl.Vector2(int(start_x), int(cy - val_size.y / 2))
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x - 1, val_pos.y - 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x + 1, val_pos.y - 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x - 1, val_pos.y + 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x + 1, val_pos.y + 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, val_pos, 48, 0, color)
    
    # Unit text
    unit_y = cy + (val_size.y - unit_size.y) / 2 - 2
    unit_pos = rl.Vector2(int(start_x + val_size.x + gap), int(unit_y))
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x - 1, unit_pos.y - 1), 24, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x + 1, unit_pos.y - 1), 24, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x - 1, unit_pos.y + 1), 24, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x + 1, unit_pos.y + 1), 24, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, unit_pos, 24, 0, rl.Color(255, 255, 255, 200))
