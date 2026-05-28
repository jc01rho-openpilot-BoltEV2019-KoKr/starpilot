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
  stop_sign_confirmed: bool = False
  indicator_extra: str = ""

class AetherGaugeSource:
  def is_active(self) -> bool:
    return False

  def get_gauge_data(self) -> AetherGaugeData:
    raise NotImplementedError

class ForceStopSource(AetherGaugeSource):
  def is_active(self) -> bool:
    if "starpilotPlan" not in ui_state.sm.valid or not ui_state.sm.valid["starpilotPlan"]:
      return False
    plan = ui_state.sm["starpilotPlan"]
    return getattr(plan, "forcingStop", False)

  def get_gauge_data(self) -> AetherGaugeData:
    plan = ui_state.sm["starpilotPlan"]
    
    distance_conversion = 1.0 if ui_state.is_metric else 3.28084
    dist_unit = "m" if ui_state.is_metric else "ft"
    
    forcing_stop_length = getattr(plan, "forcingStopLength", 0.0)
    dist_val = int(round(forcing_stop_length * distance_conversion))
    stop_sign_confirmed = getattr(plan, "stopSignConfirmed", False)
    
    color = rl.Color(255, 30, 60, 255) # Sleek high-contrast red
    
    return AetherGaugeData(
      text=str(dist_val),
      unit=dist_unit,
      label="STOP",
      animation="force_stop",
      color=color,
      indicator_type="force_stop",
      indicator_value=forcing_stop_length,
      stop_sign_confirmed=stop_sign_confirmed
    )

class CEStatus:
  USER_OVERRIDDEN = 2
  CURVATURE = 3
  LEAD = 4
  SIGNAL = 5
  SPEED = 6
  SPEED_LIMIT = 7
  STOP_LIGHT = 8

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

class CEMSource(AetherGaugeSource):
  # Configuration mapping for each conditional status code.
  # Format: (label, animation, indicator_type, static_color)
  CONFIGS = {
    CEStatus.USER_OVERRIDDEN: ("EXP", "down_arrows", "road_curve", rl.Color(255, 140, 0, 255)),
    CEStatus.CURVATURE:       ("CURVE", "down_arrows", "road_curve", None),
    CEStatus.LEAD:            ("LEAD", "lead", "lead", rl.Color(255, 191, 0, 255)),
    CEStatus.STOP_LIGHT:      ("STOP", "stop_light", "stop_light", rl.Color(255, 30, 60, 255)),
  }

  def __init__(self, status: int):
    self.status = status
    self.label, self.animation, self.indicator_type, self.static_color = self.CONFIGS[status]

  def is_active(self) -> bool:
    if ui_state.conditional_status != self.status:
      return False
    if self.status in (CEStatus.CURVATURE, CEStatus.STOP_LIGHT):
      return "starpilotPlan" in ui_state.sm.valid and ui_state.sm.valid["starpilotPlan"]
    if self.status == CEStatus.LEAD:
      if "radarState" not in ui_state.sm.valid or not ui_state.sm.valid["radarState"]:
        return False
      return ui_state.sm["radarState"].leadOne.status
    return True

  def get_gauge_data(self) -> AetherGaugeData:
    plan = ui_state.sm["starpilotPlan"] if "starpilotPlan" in ui_state.sm.valid and ui_state.sm.valid["starpilotPlan"] else None
    car_state = ui_state.sm["carState"] if "carState" in ui_state.sm.valid and ui_state.sm.valid["carState"] else None
    starpilot_car_state = ui_state.sm["starpilotCarState"] if "starpilotCarState" in ui_state.sm.valid and ui_state.sm.valid["starpilotCarState"] else None
    model = ui_state.sm["modelV2"] if "modelV2" in ui_state.sm.valid and ui_state.sm.valid["modelV2"] else None
    radar_state = ui_state.sm["radarState"] if "radarState" in ui_state.sm.valid and ui_state.sm.valid["radarState"] else None

    # Determine conversion and unit (STOP_LIGHT displays stopping distance; others display speeds)
    is_distance = (self.status == CEStatus.STOP_LIGHT)
    if is_distance:
      conversion = 1.0 if ui_state.is_metric else 3.28084
      unit = "m" if ui_state.is_metric else "ft"
    else:
      conversion = CV.MS_TO_KPH if ui_state.is_metric else CV.MS_TO_MPH
      unit = "km/h" if ui_state.is_metric else "mph"

    # Default output parameters
    val = 0
    indicator_value = 0.0
    stop_sign_confirmed = False
    indicator_extra = ""

    # Shared cruise speed calculation fallback
    v_cruise = getattr(plan, "vCruise", car_state.vEgo if car_state else 0.0) if plan else (car_state.vEgo if car_state else 0.0)

    if self.status == CEStatus.STOP_LIGHT:
      stopping_distance = 0.0
      if model and len(model.position.x) > 0:
        stopping_distance = model.position.x[min(32, len(model.position.x) - 1)]
      else:
        stopping_distance = getattr(plan, "forcingStopLength", 0.0) if plan else 0.0
      val = int(round(stopping_distance * conversion))
      indicator_value = stopping_distance
      stop_sign_confirmed = getattr(plan, "stopSignConfirmed", False) or (getattr(starpilot_car_state, "dashboardStopSign", 0) > 0 if starpilot_car_state else False)
      indicator_extra = "red"

    elif self.status == CEStatus.CURVATURE:
      csc_speed = getattr(plan, "cscSpeed", 0.0) if plan else 0.0
      target_speed = csc_speed if csc_speed > 0.1 else v_cruise
      val = int(round(target_speed * conversion))
      indicator_value = getattr(plan, "roadCurvature", 0.0) if plan else 0.0

    elif self.status == CEStatus.LEAD:
      lead = radar_state.leadOne if radar_state else None
      lead_speed = lead.vLead if (lead and lead.status) else 0.0
      val = int(round(lead_speed * conversion))
      indicator_value = lead.dRel if (lead and lead.status) else 0.0
      if lead and lead.status and lead_speed < 1.0:
        indicator_extra = "stopped"
      else:
        indicator_extra = "slower"




    elif self.status == CEStatus.USER_OVERRIDDEN:
      val = int(round(v_cruise * conversion))

    # Resolve color (CURVATURE dynamically computes its glow color)
    if self.status == CEStatus.CURVATURE:
      road_curvature = getattr(plan, "roadCurvature", 0.0) if plan else 0.0
      intensity = max(0.0, min(1.0, abs(road_curvature) * 200.0))
      color = _glow_color(intensity)
    else:
      color = self.static_color

    return AetherGaugeData(
      text=str(val),
      unit=unit,
      label=self.label,
      animation=self.animation,
      color=color,
      indicator_type=self.indicator_type,
      indicator_value=indicator_value,
      stop_sign_confirmed=stop_sign_confirmed,
      indicator_extra=indicator_extra
    )

class AetherGauge:
  def __init__(self):
    self.sources: list[AetherGaugeSource] = [
      ForceStopSource(),
      CEMSource(CEStatus.STOP_LIGHT),
      CurveSpeedSource(),
      CEMSource(CEStatus.CURVATURE),
      CEMSource(CEStatus.LEAD),
      CEMSource(CEStatus.USER_OVERRIDDEN),
    ]
    # Smoothed approach progress for stop sign (smooth motion between data updates)
    self._stop_smooth_s = 0.0

  def get_active_data(self) -> AetherGaugeData | None:
    for source in self.sources:
      if source.is_active():
        return source.get_gauge_data()
    return None

  def _get_x_from_t(self, t: float) -> float:
    x_min = 3.0
    x_max = 60.0
    denom = max(1e-6, 1.0 - t * (1.0 - x_min / x_max))
    return x_min / denom

  def _get_t_from_x(self, x: float) -> float:
    x_min = 3.0
    x_max = 60.0
    x_clamped = max(x_min, min(x_max, x))
    return (1.0 - x_min / x_clamped) / (1.0 - x_min / x_max)


  def _get_perspective_offset(self, t: float, data: AetherGaugeData) -> float:
    curvature = 0.0
    if data:
      if data.indicator_type == "road_curve":
        curvature = data.indicator_value
      elif "starpilotPlan" in ui_state.sm.valid and ui_state.sm.valid["starpilotPlan"]:
        curvature = ui_state.sm["starpilotPlan"].roadCurvature
    
    # Convert curvature C to Y-offset at 60 meters: Y = 0.5 * C * 60^2 = 1800 * C
    path_y_far = 1800.0 * curvature
    
    # Apply tanh compression to limit max offset while exaggerating small curves
    gain = 0.35
    max_offset = 26.0
    # Match sign convention so right curves curve right, left curves curve left
    max_offset_top = math.tanh(path_y_far * gain) * max_offset
    
    # Smooth quadratic-based curvature profile (t^1.8) distributed evenly across the height
    return max_offset_top * (t ** 1.8)

  def render(self, rect: rl.Rectangle, font_bold: rl.Font, font_medium: rl.Font, current_speed: float):
    data = self.get_active_data()
    
    # === TEST CYCLE OVERRIDE ===
    # Set to True to cycle all Aethergauge visual effects for testing.
    # Set to False to run off live data.
    TEST_CYCLE = True
    if TEST_CYCLE:
      now_time = rl.get_time()
      if now_time > 3.0:
        cycle_sec = 4.0
        states = [
          ("road_curve", "45", "CURVE", rl.Color(0, 255, 100, 255), 0.005, "", False),
          ("stop_light", "25", "STOP", rl.Color(255, 30, 60, 255), 35.0, "red", False),
          ("lead", "32", "LEAD", rl.Color(255, 191, 0, 255), 25.0, "slower", False),
          ("lead", "0", "LEAD", rl.Color(255, 191, 0, 255), 15.0, "stopped", False),
          ("force_stop", "12", "STOP", rl.Color(255, 30, 60, 255), 12.0, "", True),
        ]
        cycle_idx = int((now_time - 3.0) / cycle_sec) % len(states)
        s = states[cycle_idx]
        
        # Determine dynamic indicator_value (approaching distance/speed) for animations
        ind_val = s[4]
        elapsed = (now_time - 3.0) % cycle_sec
        if s[0] in ("stop_light", "force_stop"):
          ind_val = max(2.0, 60.0 - (elapsed / (cycle_sec - 0.5)) * 58.0)
        elif s[0] == "lead":
          ind_val = max(10.0, 80.0 - (elapsed / (cycle_sec - 0.5)) * 70.0)
          
        extra = s[5]

        data = AetherGaugeData(
          text=s[1] if s[0] not in ("stop_light", "force_stop") else str(int(round(ind_val * (1.0 if s[5] != "metric" else 3.28084)))),
          unit="mph" if s[5] != "metric" else "km/h",
          label=s[2],
          color=s[3],
          indicator_type=s[0],
          indicator_value=ind_val,
          indicator_extra=extra,
          stop_sign_confirmed=s[6]
        )

    if not data:
      return

    cx = rect.x + rect.width / 2
    # Vertical center of travel speed text is exactly at rect.y + 180 (matching hud_renderer.py)
    cy_speed = rect.y + 180

    speed_text = str(round(current_speed))
    speed_text_size = measure_text_cached(font_bold, speed_text, 176)

    # Position the curving road widget to the left of the speed text, center-aligned vertically
    icon_cx = cx - speed_text_size.x / 2 - 70.0

    if data.indicator_type in ("road_curve", "force_stop", "lead", "stop_light"):
      self._render_unified_road(icon_cx, cy_speed - 39.5, data, font_bold, font_medium)

  def _render_unified_road(self, icx: float, icy: float, data: AetherGaugeData, font_bold: rl.Font, font_medium: rl.Font):
    # Dimensions of the road projection
    half_size = 40.0
    bottom = icy + half_size
    top = icy - half_size
    
    # Model path lookup
    model = ui_state.sm["modelV2"] if ui_state.sm.valid.get("modelV2", False) else None
    
    # 3D perspective widths (milder narrowing for small 2D widget to keep lane boundaries parallel)
    w_bottom = 22.0
    w_top = 14.0
    thickness = 4.0
    
    # Generate points along the road path
    num_segments = 16
    points_left = []
    points_right = []
    
    for i in range(num_segments + 1):
      t = i / num_segments
      if data.indicator_type in ("road_curve", "lead", "stop_light", "force_stop") and model:
        offset = self._get_perspective_offset(t, data)
      else:
        offset = 0.0
      
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
    left_color = data.color
    right_color = data.color

    shadow_color = rl.Color(0, 0, 0, 100)
    for i in range(num_segments):
      # Shadow lines
      rl.draw_line_ex(rl.Vector2(points_left[i].x, points_left[i].y + 2), rl.Vector2(points_left[i+1].x, points_left[i+1].y + 2), thickness, shadow_color)
      rl.draw_line_ex(rl.Vector2(points_right[i].x, points_right[i].y + 2), rl.Vector2(points_right[i+1].x, points_right[i+1].y + 2), thickness, shadow_color)
      
      # Main boundaries
      rl.draw_line_ex(points_left[i], points_left[i+1], thickness, left_color)
      rl.draw_line_ex(points_right[i], points_right[i+1], thickness, right_color)

    if data.indicator_type in ("stop_light", "force_stop"):
      t_line = max(0.0, min(1.0, self._get_t_from_x(data.indicator_value)))
      w_line = w_bottom - t_line * (w_bottom - w_top)
      
      if model:
        offset_line = self._get_perspective_offset(t_line, data)
      else:
        offset_line = 0.0
        
      cx_line = icx + offset_line
      cy_line = bottom - t_line * 80.0
      
      p_left = rl.Vector2(int(cx_line - w_line + 2.0), int(cy_line))
      p_right = rl.Vector2(int(cx_line + w_line - 2.0), int(cy_line))
      
      line_color_glow = rl.Color(255, 30, 60, int(150 * (1.0 - t_line * 0.5)))
      line_color_core = rl.Color(255, 200, 200, 255)
      
      rl.draw_line_ex(p_left, p_right, max(3.0, 7.0 * (1.0 - t_line * 0.5)), line_color_glow)
      rl.draw_line_ex(p_left, p_right, max(1.5, 3.5 * (1.0 - t_line * 0.5)), line_color_core)

    # C. Draw animating overlays based on active indicator mode
    if data.indicator_type == "lead":
      lead_dist = data.indicator_value
      t_lead = max(0.15, min(0.85, self._get_t_from_x(lead_dist)))
      
      # Model curvature offset for lead car center
      if model:
        offset_lead = self._get_perspective_offset(t_lead, data)
      else:
        offset_lead = 0.0
        
      cx_lead = icx + offset_lead
      cy_lead = bottom - t_lead * 80.0
      
      # Scale size by depth (closer car is larger)
      scale = 0.45 + (1.0 - t_lead) * 0.55
      W_car = 30.0 * scale
      H_car = 18.0 * scale
      
      is_stopped = (data.indicator_extra == "stopped")
      is_slower = (data.indicator_extra == "slower")

      if is_stopped:
        border_color = rl.Color(255, 60, 60, 255)
      elif is_slower:
        # Gentle amber pulse on the outline to show active braking
        pulse = 0.5 + 0.5 * math.sin(rl.get_time() * 3.0)
        border_color = rl.Color(data.color.r, data.color.g, data.color.b, int(160 + 95 * pulse))
      else:
        border_color = data.color

      # Draw car cabin
      rect_cabin = rl.Rectangle(cx_lead - W_car * 0.3, cy_lead - H_car, W_car * 0.6, H_car * 0.45)
      rl.draw_rectangle_rounded(rect_cabin, 0.5, 4, rl.Color(15, 15, 15, 240))
      rl.draw_rectangle_rounded_lines_ex(rect_cabin, 0.5, 4, 1.5, border_color)
      
      # Draw car body
      rect_body = rl.Rectangle(cx_lead - W_car / 2, cy_lead - H_car * 0.65, W_car, H_car * 0.55)
      rl.draw_rectangle_rounded(rect_body, 0.3, 4, rl.Color(20, 20, 20, 240))
      rl.draw_rectangle_rounded_lines_ex(rect_body, 0.3, 4, 1.5, border_color)
      
      # Draw taillights with state-dependent intensity
      tl_w = W_car * 0.15
      tl_h = H_car * 0.12
      if is_stopped:
        pulse = 0.5 + 0.5 * math.sin(rl.get_time() * 8.0)  # Fast warning pulse
        # Outer glowing red halo
        rl.draw_circle(int(cx_lead - W_car * 0.38), int(cy_lead - H_car * 0.5), int(W_car * 0.08 * (1.0 + 0.4 * pulse)), rl.Color(255, 30, 60, int(150 + 105 * pulse)))
        rl.draw_circle(int(cx_lead + W_car * 0.38), int(cy_lead - H_car * 0.5), int(W_car * 0.08 * (1.0 + 0.4 * pulse)), rl.Color(255, 30, 60, int(150 + 105 * pulse)))
        # Inner bright core
        rl.draw_rectangle(int(cx_lead - W_car * 0.45), int(cy_lead - H_car * 0.55), int(tl_w), int(tl_h), rl.Color(255, 220, 220, 255))
        rl.draw_rectangle(int(cx_lead + W_car * 0.3), int(cy_lead - H_car * 0.55), int(tl_w), int(tl_h), rl.Color(255, 220, 220, 255))
      elif is_slower:
        pulse = 0.5 + 0.5 * math.sin(rl.get_time() * 3.0)  # Gentle brake throb
        # Warm amber glow halo
        rl.draw_circle(int(cx_lead - W_car * 0.38), int(cy_lead - H_car * 0.5), int(W_car * 0.06 * (1.0 + 0.2 * pulse)), rl.Color(255, 140, 30, int(100 + 80 * pulse)))
        rl.draw_circle(int(cx_lead + W_car * 0.38), int(cy_lead - H_car * 0.5), int(W_car * 0.06 * (1.0 + 0.2 * pulse)), rl.Color(255, 140, 30, int(100 + 80 * pulse)))
        # Amber taillight core
        rl.draw_rectangle(int(cx_lead - W_car * 0.45), int(cy_lead - H_car * 0.55), int(tl_w), int(tl_h), rl.Color(255, 160, 60, int(180 + 75 * pulse)))
        rl.draw_rectangle(int(cx_lead + W_car * 0.3), int(cy_lead - H_car * 0.55), int(tl_w), int(tl_h), rl.Color(255, 160, 60, int(180 + 75 * pulse)))
      else:
        rl.draw_rectangle(int(cx_lead - W_car * 0.45), int(cy_lead - H_car * 0.55), int(tl_w), int(tl_h), rl.Color(255, 30, 60, 255))
        rl.draw_rectangle(int(cx_lead + W_car * 0.3), int(cy_lead - H_car * 0.55), int(tl_w), int(tl_h), rl.Color(255, 30, 60, 255))
      
      # Draw wheels
      rl.draw_rectangle(int(cx_lead - W_car * 0.4), int(cy_lead - H_car * 0.1), int(W_car * 0.12), int(H_car * 0.1), rl.Color(10, 10, 10, 255))
      rl.draw_rectangle(int(cx_lead + W_car * 0.28), int(cy_lead - H_car * 0.1), int(W_car * 0.12), int(H_car * 0.1), rl.Color(10, 10, 10, 255))
      
      # Draw flow-limited chevrons behind the lead vehicle (flowing from car to driver)
      progress = (rl.get_time() * 1.5) % 1.0
      num_chevs = 2
      for i in range(num_chevs):
        t = t_lead * (1.0 - ((i + progress) / num_chevs) % 1.0)
        
        if model:
          offset_t = self._get_perspective_offset(t, data)
        else:
          offset_t = 0.0
          
        cx_t = icx + offset_t
        cy_t = bottom - t * 80.0
        
        chevron_w = 12.0 - t * 5.0
        chevron_thick = max(1.5, 3.5 - t * 1.5)
        lx = cx_t - chevron_w
        rx = cx_t + chevron_w
        
        alpha = int(data.color.a * (1.0 - t / t_lead) * math.sin(t / t_lead * math.pi))
        c_color = rl.Color(data.color.r, data.color.g, data.color.b, max(0, min(255, alpha)))
        
        rl.draw_line_ex(rl.Vector2(int(lx), int(cy_t + chevron_w * 0.5)), rl.Vector2(int(cx_t), int(cy_t)), chevron_thick, c_color)
        rl.draw_line_ex(rl.Vector2(int(rx), int(cy_t + chevron_w * 0.5)), rl.Vector2(int(cx_t), int(cy_t)), chevron_thick, c_color)

    else:
      # Standard chevrons for road_curve, force_stop, and stop_light
      is_stop = data.indicator_type in ("force_stop", "stop_light")
      if data.indicator_type == "force_stop":
        speed_factor = max(0.1, min(1.0, data.indicator_value / 30.0))
      elif data.indicator_type == "stop_light":
        speed_factor = max(0.1, min(1.0, data.indicator_value / 30.0))
      else:
        speed_factor = 1.0

      progress = (rl.get_time() * 1.2 * speed_factor) % 1.0
      t_stop = max(0.05, min(1.0, data.indicator_value / 60.0)) if is_stop else 1.0

      for i in range(3):
        if is_stop:
          # Flow UPWARD towards the stopping point
          t = ((i + progress) / 3.0) * t_stop
          if t > t_stop:
            continue
        else:
          # Chevron fraction t (flowing down from 1.0 to 0.0)
          t = 1.0 - ((i + progress) / 3.0)
        
        # Calculate local tangent vector for rotation using model path
        t_next = min(1.0, t + 0.05)
        if model:
          offset_t = self._get_perspective_offset(t, data)
          cx_t = icx + offset_t
          
          offset_next = self._get_perspective_offset(t_next, data)
          cx_next = icx + offset_next
        else:
          cx_t = icx
          cx_next = icx
        
        cy_t = bottom - t * 80.0
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
        
        # Vertices - if is_stop, chevron tip points upward (wings extend backward)
        dir_mult = -1.0 if is_stop else 1.0
        lx = cx_t - dir_right_x * chevron_w + dir_mult * dir_up_x * chevron_h
        ly = cy_t - dir_right_y * chevron_w + dir_mult * dir_up_y * chevron_h
        rx = cx_t + dir_right_x * chevron_w + dir_mult * dir_up_x * chevron_h
        ry = cy_t + dir_right_y * chevron_w + dir_mult * dir_up_y * chevron_h
        
        # Alpha envelope: fade out near limits
        if is_stop:
          alpha_factor = math.sin(t / t_stop * math.pi)
        else:
          alpha_factor = math.sin(t * math.pi)
        alpha = int(data.color.a * alpha_factor)
        chev_color = rl.Color(data.color.r, data.color.g, data.color.b, alpha)
        chev_shadow = rl.Color(0, 0, 0, int(alpha * 0.5))
        
        # Draw chevron with shadow
        rl.draw_line_ex(rl.Vector2(int(lx), int(ly + 1.5)), rl.Vector2(int(cx_t), int(cy_t + 1.5)), chevron_thick, chev_shadow)
        rl.draw_line_ex(rl.Vector2(int(rx), int(ry + 1.5)), rl.Vector2(int(cx_t), int(cy_t + 1.5)), chevron_thick, chev_shadow)
        
        rl.draw_line_ex(rl.Vector2(int(lx), int(ly)), rl.Vector2(int(cx_t), int(cy_t)), chevron_thick, chev_color)
        rl.draw_line_ex(rl.Vector2(int(rx), int(ry)), rl.Vector2(int(cx_t), int(cy_t)), chevron_thick, chev_color)

    # E. Draw overhead traffic light if stop_light
    if data.indicator_type == "stop_light":
      t_light = max(0.0, min(1.0, self._get_t_from_x(data.indicator_value)))
      s_light = 1.0 - t_light
      
      if model:
        offset_light = self._get_perspective_offset(t_light, data)
      else:
        offset_light = 0.0
        
      cx_light = icx + offset_light
      
      # 3D perspective translation matching the stop sign vertical translation
      y_sign_light = (icy - 30.0) + (s_light ** 1.5) * 50.0
      scale_light = 0.6 + (s_light ** 2.0) * 1.4
      
      cy_light = y_sign_light - 15.0 * scale_light
      width = 11.0 * scale_light
      height = 27.0 * scale_light
      
      # Shadow
      rl.draw_rectangle_rounded(rl.Rectangle(cx_light - width/2, cy_light - height/2 + 1.5, width, height), 0.2, 4, rl.Color(0, 0, 0, 120))
      # Housing
      rect_housing = rl.Rectangle(cx_light - width/2, cy_light - height/2, width, height)
      rl.draw_rectangle_rounded(rect_housing, 0.2, 4, rl.Color(22, 22, 22, 255))
      rl.draw_rectangle_rounded_lines_ex(rect_housing, 0.2, 4, 1.0, rl.Color(80, 80, 80, 255))
      
      r_bulb = 2.2 * scale_light
      y_red = cy_light - 7.5 * scale_light
      y_yellow = cy_light
      y_green = cy_light + 7.5 * scale_light
      
      active_light = data.indicator_extra if data.indicator_extra in ("red", "yellow", "green") else "red"
      
      # Pulse halo glow for active light
      if active_light == "red":
        glow_pulse = 0.5 + 0.5 * math.sin(rl.get_time() * 5.0)
        rl.draw_circle(int(cx_light), int(y_red), int(r_bulb + 3.0 * glow_pulse), rl.Color(255, 30, 60, 45))
        rl.draw_circle(int(cx_light), int(y_red), int(r_bulb + 6.0 * glow_pulse), rl.Color(255, 30, 60, 15))
        
      c_red = rl.Color(255, 30, 60, 255) if active_light == "red" else rl.Color(50, 10, 15, 255)
      c_yellow = rl.Color(255, 200, 0, 255) if active_light == "yellow" else rl.Color(50, 40, 0, 255)
      c_green = rl.Color(0, 255, 100, 255) if active_light == "green" else rl.Color(0, 40, 15, 255)
      
      rl.draw_circle(int(cx_light), int(y_red), int(r_bulb), c_red)
      rl.draw_circle(int(cx_light), int(y_yellow), int(r_bulb), c_yellow)
      rl.draw_circle(int(cx_light), int(y_green), int(r_bulb), c_green)

    # G. Draw approaching stop sign if force_stop
    if data.indicator_type == "force_stop":
      self._draw_approaching_stop_sign(icx, icy, bottom, data.indicator_value, data, font_bold)

    # D. Draw clean floating target speed directly below the road base
    self._draw_mini_cradle(icx, bottom, data.text, data.unit, data.color, font_bold, font_medium)

  def _draw_mini_cradle(self, cx: float, bottom: float, target_speed: str, unit: str, color: rl.Color, font_bold: rl.Font, font_medium: rl.Font):
    # Digits (centered at cx, top at bottom + 12)
    val_size = measure_text_cached(font_bold, target_speed, 48)
    val_pos = rl.Vector2(int(cx - val_size.x / 2), int(bottom + 12))
    
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x - 1, val_pos.y - 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x + 1, val_pos.y - 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x - 1, val_pos.y + 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, rl.Vector2(val_pos.x + 1, val_pos.y + 1), 48, 0, rl.BLACK)
    rl.draw_text_ex(font_bold, target_speed, val_pos, 48, 0, color)
    
    # Unit (centered at cx, top at bottom + 12 + val_size.y * 0.8)
    unit_size = measure_text_cached(font_medium, unit, 20)
    unit_pos = rl.Vector2(int(cx - unit_size.x / 2), int(bottom + 12 + val_size.y * 0.8))
    
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x - 1, unit_pos.y - 1), 20, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x + 1, unit_pos.y - 1), 20, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x - 1, unit_pos.y + 1), 20, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, rl.Vector2(unit_pos.x + 1, unit_pos.y + 1), 20, 0, rl.BLACK)
    rl.draw_text_ex(font_medium, unit, unit_pos, 20, 0, rl.Color(255, 255, 255, 200))

  def _draw_approaching_stop_sign(self, cx: float, icy: float, bottom: float, distance: float, data: AetherGaugeData, font_bold: rl.Font):
    # Normalized progress: d_max = 60.0 meters
    d_max = 60.0
    raw_s = max(0.0, min(1.0, (d_max - distance) / d_max))
    # EMA smoother: interpolates between data updates (20Hz) for fluid sub-pixel motion.
    # Large discontinuities (new stop sign) reset instantly.
    if abs(raw_s - self._stop_smooth_s) > 0.5:
      self._stop_smooth_s = raw_s
    self._stop_smooth_s += (raw_s - self._stop_smooth_s) * 0.25
    s = self._stop_smooth_s
    
    # 3D perspective depth coordinate, derived from smoothed s for consistency
    distance_smoothed = d_max - s * d_max
    t_stop_gauge = self._get_t_from_x(distance_smoothed)
    
    if data:
      offset_stop = self._get_perspective_offset(t_stop_gauge, data)
    else:
      offset_stop = 0.0
      
    cx_stop = cx + offset_stop
    
    # 3D perspective translation (stays within the road boundary)
    y_sign = (icy - 30.0) + (s ** 1.5) * 50.0
    
    # Dynamic scale based on distance
    r_min = 6.0
    r_max = 20.0
    r_sign = r_min + (s ** 2.0) * (r_max - r_min)
    
    # Shadow alpha scales with sign size (fainter at distance), position uses raw floats
    shadow_alpha = int(min(120, r_sign * 12))
    rl.draw_poly(rl.Vector2(cx_stop, y_sign + 2.0), 8, r_sign, 22.5, rl.Color(0, 0, 0, shadow_alpha))
    
    # Draw red octagon body (always visible at full opacity)
    red_color = rl.Color(196, 30, 58, 255)
    rl.draw_poly(rl.Vector2(cx_stop, y_sign), 8, r_sign, 22.5, red_color)
    
    # Proportional white outline — thickness and alpha both scale with sign size.
    # At distance (r=6): barely visible hint of an edge.
    # Up close (r=20): crisp outline at full alpha.
    outline_t = max(0.8, min(1.5, r_sign * 0.07))
    outline_a = int(max(0, min(200, (r_sign - 5.0) * 20)))
    if outline_a > 20:
      for i in range(8):
        a1 = math.radians(22.5 + i * 45.0)
        a2 = math.radians(22.5 + ((i + 1) % 8) * 45.0)
        p1 = rl.Vector2(cx_stop + r_sign * math.cos(a1), y_sign + r_sign * math.sin(a1))
        p2 = rl.Vector2(cx_stop + r_sign * math.cos(a2), y_sign + r_sign * math.sin(a2))
        rl.draw_line_ex(p1, p2, outline_t, rl.Color(255, 255, 255, outline_a))
    
    # Draw "STOP" text centered on the sign face (always visible, sized to fit within octagon)
    stop_font_size = max(4, int(r_sign * 0.7))
    stop_txt_size = measure_text_cached(font_bold, "STOP", stop_font_size)
    stop_pos = rl.Vector2(cx_stop - stop_txt_size.x / 2, y_sign - stop_txt_size.y / 2)
    rl.draw_text_ex(font_bold, "STOP", stop_pos, stop_font_size, 0, rl.WHITE)
