from abc import ABC, abstractmethod
from dataclasses import dataclass
from enum import Enum
import math
import numpy as np
import pyray as rl
from openpilot.common.constants import CV
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.selfdrive.ui.onroad.starpilot.starpilot_border import _csc_state, _intensity, _glow_color


# --- Named constants ---

X_MIN = 3.0
X_MAX = 60.0
PATH_Y_FAR_SCALE = 1800.0
PERSPECTIVE_GAIN = 0.35
PERSPECTIVE_MAX_OFFSET = 26.0
PERSPECTIVE_EXPONENT = 1.8

ROAD_HEIGHT = 80.0
ROAD_SEGMENTS = 16
ROAD_W_BOTTOM = 22.0
ROAD_W_TOP = 14.0
ROAD_THICKNESS = 4.0
ROAD_HALF_SIZE = 40.0
ROAD_EDGE_INSET = 2.0
FILL_ALPHA = 35

MIN_SPEED_FOR_TIME = 0.3
MAX_TIME_DISPLAY = 99.0
TIME_FACTOR = 2.0

STOP_SNAP_THRESHOLD = 0.5
STOP_LERP_RATE = 0.25
STOP_DISTANCE_MAX = 60.0

CHEVRON_COUNT = 4
CHEVRON_SPACING = 0.3
CHEVRON_STEP = 0.05

CEM_STATUS_CURVE = 3
CEM_STATUS_LEAD = 4
CEM_STATUS_STOP_LIGHT = 8

LEAD_STOPPED_SPEED_THRESHOLD = 1.0

COLOR_FORCE_STOP = rl.Color(255, 30, 60, 255)
COLOR_LEAD_STOPPED = rl.Color(255, 60, 60, 255)
COLOR_LEAD_SLOWER = rl.Color(255, 191, 0, 255)
COLOR_SHADOW = rl.Color(0, 0, 0, 100)
COLOR_STOP_SIGN = rl.Color(196, 30, 58, 255)
COLOR_STOP_SIGN_OUTLINE = rl.Color(255, 255, 255, 255)
COLOR_STOP_LINE_GLOW = rl.Color(255, 30, 60, 255)
COLOR_STOP_LINE_CORE = rl.Color(255, 200, 200, 255)

# Set to True to force test-cycle mode (flip back to False before pushing)
TEST_CYCLE = True


# --- Conversion helpers ---

def _speed_conversion() -> float:
  return CV.MS_TO_KPH if ui_state.is_metric else CV.MS_TO_MPH

def _speed_unit() -> str:
  return "km/h" if ui_state.is_metric else "mph"

def _to_display_speed(val: float) -> tuple[int, str]:
  return int(round(val * _speed_conversion())), _speed_unit()

def _get_val(msg: str, attr: str, default=None):
  return getattr(ui_state.sm[msg], attr, default) if _sm_valid(msg) else default


# --- Shared helpers ---

def _sm_valid(key: str) -> bool:
  return key in ui_state.sm.valid and ui_state.sm.valid[key]

def _time_to_stop(distance: float, v_ego: float) -> str:
  if v_ego > MIN_SPEED_FOR_TIME:
    t = max(0.0, min(MAX_TIME_DISPLAY, TIME_FACTOR * distance / v_ego))
    return f"{t:.1f}"
  return "0.0"

def _calc_reduction(v_cruise: float, target: float) -> int:
  if v_cruise > 0.1 and target > 0.1 and target < v_cruise:
    return int(round((v_cruise - target) * _speed_conversion()))
  return 0

def _with_alpha(color: rl.Color, a: int) -> rl.Color:
  return rl.Color(color.r, color.g, color.b, max(0, min(255, a)))

def _pulse(freq: float) -> float:
  return 0.5 + 0.5 * math.sin(rl.get_time() * freq)

def _road_xy(distance: float, icx: float, bottom: float, data: 'AetherGaugeData') -> tuple[float, float, float]:
  t = max(0.0, min(1.0, _get_t_from_x(distance)))
  offset = _get_perspective_offset(t, data)
  return t, icx + offset, bottom - t * ROAD_HEIGHT

def _get_t_from_x(x: float) -> float:
  x_clamped = max(X_MIN, min(X_MAX, x))
  return (1.0 - X_MIN / x_clamped) / (1.0 - X_MIN / X_MAX)

def _get_perspective_offset(t: float, data: 'AetherGaugeData | None') -> float:
  curvature = 0.0
  if data:
    if data.indicator_type == IndicatorType.ROAD_CURVE:
      curvature = data.indicator_value
    elif _sm_valid("starpilotPlan"):
      curvature = ui_state.sm["starpilotPlan"].roadCurvature

  path_y_far = PATH_Y_FAR_SCALE * curvature
  max_offset_top = math.tanh(path_y_far * PERSPECTIVE_GAIN) * PERSPECTIVE_MAX_OFFSET
  return max_offset_top * (t ** PERSPECTIVE_EXPONENT)


# --- Data model ---

class IndicatorType(Enum):
  NONE = "none"
  ROAD_CURVE = "road_curve"
  FORCE_STOP = "force_stop"
  STOP_LIGHT = "stop_light"
  LEAD = "lead"


@dataclass
class AetherGaugeData:
  text: str
  unit: str = ""
  color: rl.Color = rl.WHITE
  indicator_type: IndicatorType = IndicatorType.NONE
  indicator_value: float = 0.0
  indicator_extra: str = ""
  reduction_text: str = ""
  is_numeric: bool = False


# --- Source base class ---

class AetherGaugeSource(ABC):
  @abstractmethod
  def is_active(self) -> bool: ...

  @abstractmethod
  def get_gauge_data(self) -> AetherGaugeData: ...


# --- Shared curve speed gauge builder ---

def _build_curve_gauge_data(curvature: float, target_speed: float, v_cruise: float) -> AetherGaugeData:
  v_ego = _get_val("carState", "vEgo", 0.0)
  display_speed, unit = _to_display_speed(min(v_ego, target_speed) if target_speed > 0.1 else v_ego)
  reduction = _calc_reduction(v_cruise, target_speed)
  intensity = _intensity(curvature)

  return AetherGaugeData(
    text=str(display_speed),
    unit=unit,
    color=_glow_color(intensity),
    indicator_type=IndicatorType.ROAD_CURVE,
    indicator_value=curvature,
    reduction_text=f"-{reduction}" if reduction > 0 else "",
    is_numeric=True,
  )


# --- Force stop source ---

class ForceStopSource(AetherGaugeSource):
  def is_active(self) -> bool:
    return _get_val("starpilotPlan", "forcingStop", False)

  def get_gauge_data(self) -> AetherGaugeData:
    v_ego = _get_val("carState", "vEgo", 0.0)
    forcing_stop_distance = _get_val("starpilotPlan", "forcingStopLength", 0.0)

    return AetherGaugeData(
      text=_time_to_stop(forcing_stop_distance, v_ego),
      unit="s",
      color=COLOR_FORCE_STOP,
      indicator_type=IndicatorType.FORCE_STOP,
      indicator_value=forcing_stop_distance,
      is_numeric=True,
    )


# --- Curve speed source (CSC active) ---

class CurveSpeedSource(AetherGaugeSource):
  def is_active(self) -> bool:
    state = _csc_state()
    return state is not None and state['active']

  def get_gauge_data(self) -> AetherGaugeData:
    state = _csc_state()
    if state is None:
      return AetherGaugeData(text="")

    csc_speed = _get_val("starpilotPlan", "cscSpeed", 0.0)
    v_cruise = _get_val("starpilotPlan", "vCruise", 0.0)
    return _build_curve_gauge_data(state['curvature'], csc_speed, v_cruise)


# --- CEM: Stop light / stop sign ---

class CEMStopLightSource(AetherGaugeSource):
  def is_active(self) -> bool:
    return ui_state.conditional_status == CEM_STATUS_STOP_LIGHT and _sm_valid("starpilotPlan")

  def get_gauge_data(self) -> AetherGaugeData:
    stopping_distance = 0.0
    if _sm_valid("modelV2"):
      model = ui_state.sm["modelV2"]
      if len(model.position.x) > 0:
        stopping_distance = model.position.x[min(32, len(model.position.x) - 1)]

    if stopping_distance == 0.0:
      stopping_distance = _get_val("starpilotPlan", "forcingStopLength", 0.0)

    v_ego = _get_val("carState", "vEgo", 0.0)

    return AetherGaugeData(
      text=_time_to_stop(stopping_distance, v_ego),
      unit="s",
      color=COLOR_FORCE_STOP,
      indicator_type=IndicatorType.STOP_LIGHT,
      indicator_value=stopping_distance,
      indicator_extra="red",
      is_numeric=True,
    )


# --- CEM: Curvature (non-CSC) ---

class CEMCurvatureSource(AetherGaugeSource):
  def is_active(self) -> bool:
    return ui_state.conditional_status == CEM_STATUS_CURVE and _sm_valid("starpilotPlan")

  def get_gauge_data(self) -> AetherGaugeData:
    csc_speed = _get_val("starpilotPlan", "cscSpeed", 0.0)
    v_ego = _get_val("carState", "vEgo", 0.0)
    v_cruise = _get_val("starpilotPlan", "vCruise", v_ego)
    target_speed = csc_speed if csc_speed > 0.1 else v_cruise
    road_curvature = _get_val("starpilotPlan", "roadCurvature", 0.0)
    return _build_curve_gauge_data(road_curvature, target_speed, v_cruise)


# --- CEM: Lead vehicle (graphic only, no numeric) ---

class CEMLeadSource(AetherGaugeSource):
  def is_active(self) -> bool:
    return (ui_state.conditional_status == CEM_STATUS_LEAD
            and _sm_valid("radarState")
            and ui_state.sm["radarState"].leadOne.status)

  def get_gauge_data(self) -> AetherGaugeData:
    lead = ui_state.sm["radarState"].leadOne
    lead_speed = lead.vLead
    lead_dist = lead.dRel

    is_stopped = lead_speed < LEAD_STOPPED_SPEED_THRESHOLD
    return AetherGaugeData(
      text="STOPPED" if is_stopped else "SLOW",
      color=COLOR_LEAD_STOPPED if is_stopped else COLOR_LEAD_SLOWER,
      indicator_type=IndicatorType.LEAD,
      indicator_value=lead_dist,
      indicator_extra="stopped" if is_stopped else "slower",
    )


# --- Test cycle source (debug only) ---

@dataclass
class _TestCycleState:
  indicator_type: IndicatorType
  text: str
  color: rl.Color
  base_indicator_value: float
  indicator_extra: str
  reduction_text: str


class TestCycleSource(AetherGaugeSource):
  def __init__(self):
    self._states = [
      _TestCycleState(IndicatorType.ROAD_CURVE, "45", rl.Color(0, 255, 100, 255), 0.005, "", "-20"),
      _TestCycleState(IndicatorType.STOP_LIGHT, "", COLOR_FORCE_STOP, 35.0, "red", ""),
      _TestCycleState(IndicatorType.LEAD, "", COLOR_LEAD_SLOWER, 25.0, "slower", ""),
      _TestCycleState(IndicatorType.LEAD, "", COLOR_LEAD_SLOWER, 15.0, "stopped", ""),
      _TestCycleState(IndicatorType.FORCE_STOP, "", COLOR_FORCE_STOP, 12.0, "", ""),
    ]
    self._cycle_sec = 6.0

  def is_active(self) -> bool:
    return rl.get_time() > 3.0

  def get_gauge_data(self) -> AetherGaugeData:
    now = rl.get_time()
    elapsed = (now - 3.0) % self._cycle_sec
    cycle_idx = int((now - 3.0) / self._cycle_sec) % len(self._states)
    state = self._states[cycle_idx]
    anim_t = elapsed / max(0.001, self._cycle_sec - 0.5)

    if state.indicator_type in (IndicatorType.STOP_LIGHT, IndicatorType.FORCE_STOP):
      ind_val = max(5.0, 60.0 - anim_t * 55.0)
      text = f"{max(0.0, (self._cycle_sec - 0.5) - elapsed):.1f}"
      return AetherGaugeData(text=text, unit="s", color=state.color,
        indicator_type=state.indicator_type, indicator_value=ind_val,
        indicator_extra=state.indicator_extra, reduction_text=state.reduction_text, is_numeric=True)

    if state.indicator_type == IndicatorType.LEAD:
      ind_val = max(3.0, 60.0 - anim_t * 57.0)
      is_stopped = state.indicator_extra == "stopped"
      text = "STOPPED" if is_stopped else "SLOW"
      color = COLOR_LEAD_STOPPED if is_stopped else COLOR_LEAD_SLOWER
      return AetherGaugeData(text=text, color=color,
        indicator_type=state.indicator_type, indicator_value=ind_val,
        indicator_extra=state.indicator_extra, reduction_text=state.reduction_text)

    return AetherGaugeData(text=state.text, unit=_speed_unit(), color=state.color,
      indicator_type=state.indicator_type, indicator_value=state.base_indicator_value,
      indicator_extra=state.indicator_extra, reduction_text=state.reduction_text, is_numeric=True)


# --- Main widget ---

class AetherGauge:
  def __init__(self):
    self._sources: list[AetherGaugeSource] = [
      ForceStopSource(),
      CEMStopLightSource(),
      CurveSpeedSource(),
      CEMCurvatureSource(),
      CEMLeadSource(),
    ]
    if TEST_CYCLE:
      self._sources.insert(0, TestCycleSource())
    self._stop_smooth_s = 0.0

  def get_active_data(self) -> AetherGaugeData | None:
    for source in self._sources:
      if source.is_active():
        return source.get_gauge_data()
    return None

  def render(self, rect: rl.Rectangle, font_bold: rl.Font, font_medium: rl.Font, current_speed: float):
    data = self.get_active_data()
    if not data:
      return

    cx = rect.x + rect.width / 2
    cy_speed = rect.y + 180

    speed_text = str(round(current_speed))
    speed_text_size = measure_text_cached(font_bold, speed_text, 176)
    icon_cx = cx - speed_text_size.x / 2 - 70.0

    if data.indicator_type in (IndicatorType.ROAD_CURVE, IndicatorType.FORCE_STOP, IndicatorType.LEAD, IndicatorType.STOP_LIGHT):
      self._render_unified_road(rect, icon_cx, cy_speed - 39.5, data, font_bold, font_medium)

  def _render_unified_road(self, rect: rl.Rectangle, icx: float, icy: float, data: AetherGaugeData, font_bold: rl.Font, font_medium: rl.Font):
    bottom = icy + ROAD_HALF_SIZE

    smoothed_s = 0.0
    if data.indicator_type == IndicatorType.FORCE_STOP:
      raw_s = max(0.0, min(1.0, (STOP_DISTANCE_MAX - data.indicator_value) / STOP_DISTANCE_MAX))
      if abs(raw_s - self._stop_smooth_s) > STOP_SNAP_THRESHOLD:
        self._stop_smooth_s = raw_s
      else:
        self._stop_smooth_s += (raw_s - self._stop_smooth_s) * STOP_LERP_RATE
      smoothed_s = self._stop_smooth_s
      distance_to_use = STOP_DISTANCE_MAX - smoothed_s * STOP_DISTANCE_MAX
    else:
      distance_to_use = data.indicator_value

    points_left = []
    points_right = []

    for i in range(ROAD_SEGMENTS + 1):
      t = i / ROAD_SEGMENTS
      offset = _get_perspective_offset(t, data)
      cx_t = icx + offset
      y_t = bottom - t * ROAD_HEIGHT
      w_t = ROAD_W_BOTTOM - t * (ROAD_W_BOTTOM - ROAD_W_TOP)

      points_left.append(rl.Vector2(cx_t - w_t, y_t))
      points_right.append(rl.Vector2(cx_t + w_t, y_t))

    fill_color = _with_alpha(data.color, FILL_ALPHA)
    for i in range(ROAD_SEGMENTS):
      rl.draw_triangle(points_left[i], points_right[i], points_left[i+1], fill_color)
      rl.draw_triangle(points_right[i], points_right[i+1], points_left[i+1], fill_color)
      rl.draw_line_ex(points_left[i], points_left[i+1], ROAD_THICKNESS, COLOR_SHADOW)
      rl.draw_line_ex(points_right[i], points_right[i+1], ROAD_THICKNESS, COLOR_SHADOW)
      rl.draw_line_ex(points_left[i], points_left[i+1], ROAD_THICKNESS, data.color)
      rl.draw_line_ex(points_right[i], points_right[i+1], ROAD_THICKNESS, data.color)

    if data.indicator_type in (IndicatorType.STOP_LIGHT, IndicatorType.FORCE_STOP):
      self._draw_stop_line(icx, bottom, distance_to_use, data)

    if data.indicator_type == IndicatorType.LEAD:
      self._draw_lead_car(icx, bottom, data)

    if data.indicator_type in (IndicatorType.ROAD_CURVE, IndicatorType.FORCE_STOP, IndicatorType.STOP_LIGHT):
      self._draw_standard_chevrons(icx, bottom, distance_to_use, data)

    if data.indicator_type == IndicatorType.STOP_LIGHT:
      self._draw_traffic_light(icx, icy, distance_to_use, data)

    if data.indicator_type == IndicatorType.FORCE_STOP:
      self._draw_approaching_stop_sign(icx, icy, bottom, distance_to_use, data, font_bold)

    self._draw_mini_cradle(icx, bottom, data, font_bold, font_medium)

  def _draw_stop_line(self, icx: float, bottom: float, distance: float, data: AetherGaugeData):
    t, cx_line, cy_line = _road_xy(distance, icx, bottom, data)
    w_line = ROAD_W_BOTTOM - t * (ROAD_W_BOTTOM - ROAD_W_TOP)

    p_left = rl.Vector2(cx_line - w_line + ROAD_EDGE_INSET, cy_line)
    p_right = rl.Vector2(cx_line + w_line - ROAD_EDGE_INSET, cy_line)

    fade = 1.0 - t * 0.5
    glow_a = int(150 * fade)

    rl.draw_line_ex(p_left, p_right, max(3.0, 7.0 * fade), _with_alpha(COLOR_STOP_LINE_GLOW, glow_a))
    rl.draw_line_ex(p_left, p_right, max(1.5, 3.5 * fade), COLOR_STOP_LINE_CORE)

  def _draw_lead_car(self, icx: float, bottom: float, data: AetherGaugeData):
    t_lead, cx_lead, cy_lead = _road_xy(data.indicator_value, icx, bottom, data)
    t_lead = max(0.15, min(0.85, t_lead))

    scale = 0.45 + (1.0 - t_lead) * 0.55
    W_car = 30.0 * scale
    H_car = 18.0 * scale

    is_stopped = data.indicator_extra == "stopped"
    is_slower = data.indicator_extra == "slower"

    if is_stopped:
      border_color = COLOR_LEAD_STOPPED
    elif is_slower:
      border_color = _with_alpha(data.color, int(160 + 95 * _pulse(3.0)))
    else:
      border_color = data.color

    self._draw_lead_car_body(cx_lead, cy_lead, W_car, H_car, border_color)
    self._draw_lead_tail_lights(cx_lead, cy_lead, W_car, H_car, is_stopped, is_slower, border_color)
    self._draw_lead_wheels(cx_lead, cy_lead, W_car, H_car)
    self._draw_lead_following_chevrons(icx, bottom, t_lead, data)

  def _draw_lead_car_body(self, cx: float, cy: float, w: float, h: float, border_color: rl.Color):
    rect_cabin = rl.Rectangle(cx - w * 0.3, cy - h, w * 0.6, h * 0.45)
    rl.draw_rectangle_rounded(rect_cabin, 0.5, 4, rl.Color(15, 15, 15, 240))
    rl.draw_rectangle_rounded_lines_ex(rect_cabin, 0.5, 4, 1.5, border_color)

    rect_body = rl.Rectangle(cx - w / 2, cy - h * 0.65, w, h * 0.55)
    rl.draw_rectangle_rounded(rect_body, 0.3, 4, rl.Color(20, 20, 20, 240))
    rl.draw_rectangle_rounded_lines_ex(rect_body, 0.3, 4, 1.5, border_color)

  def _draw_lead_tail_lights(self, cx: float, cy: float, w: float, h: float,
                              is_stopped: bool, is_slower: bool, border_color: rl.Color):
    tl_w = w * 0.15
    tl_h = h * 0.12
    tl_x_left = int(cx - w * 0.45)
    tl_x_right = int(cx + w * 0.3)
    tl_y = int(cy - h * 0.55)
    glow_x = int(cx - w * 0.38)
    glow_xr = int(cx + w * 0.38)
    glow_y = int(cy - h * 0.5)

    if is_stopped:
      pulse = _pulse(8.0)
      r_glow = int(w * 0.08 * (1.0 + 0.4 * pulse))
      c_glow = rl.Color(255, 30, 60, int(150 + 105 * pulse))
      rl.draw_circle(glow_x, glow_y, r_glow, c_glow)
      rl.draw_circle(glow_xr, glow_y, r_glow, c_glow)
      c_tl = rl.Color(255, 220, 220, 255)
    elif is_slower:
      pulse = _pulse(3.0)
      r_glow = int(w * 0.06 * (1.0 + 0.2 * pulse))
      c_glow = rl.Color(255, 140, 30, int(100 + 80 * pulse))
      rl.draw_circle(glow_x, glow_y, r_glow, c_glow)
      rl.draw_circle(glow_xr, glow_y, r_glow, c_glow)
      c_tl = rl.Color(255, 160, 60, int(180 + 75 * pulse))
    else:
      c_tl = COLOR_FORCE_STOP

    rl.draw_rectangle(tl_x_left, tl_y, int(tl_w), int(tl_h), c_tl)
    rl.draw_rectangle(tl_x_right, tl_y, int(tl_w), int(tl_h), c_tl)

  def _draw_lead_wheels(self, cx: float, cy: float, w: float, h: float):
    wheel_y = int(cy - h * 0.1)
    wheel_w = int(w * 0.12)
    wheel_h = int(h * 0.1)
    wheel_color = rl.Color(10, 10, 10, 255)
    rl.draw_rectangle(int(cx - w * 0.4), wheel_y, wheel_w, wheel_h, wheel_color)
    rl.draw_rectangle(int(cx + w * 0.28), wheel_y, wheel_w, wheel_h, wheel_color)

  def _draw_lead_following_chevrons(self, icx: float, bottom: float, t_lead: float, data: AetherGaugeData):
    progress = (rl.get_time() * 1.5) % 1.0
    for i in range(2):
      t = t_lead * (1.0 - ((i + progress) / 2) % 1.0)

      offset_t = _get_perspective_offset(t, data)
      cx_t = icx + offset_t
      cy_t = bottom - t * ROAD_HEIGHT

      chevron_w = 12.0 - t * 5.0
      chevron_thick = max(1.5, 3.5 - t * 1.5)
      lx = cx_t - chevron_w
      rx = cx_t + chevron_w

      alpha = max(0, min(255, int(data.color.a * (1.0 - t / t_lead) * math.sin(t / t_lead * math.pi))))
      c_color = _with_alpha(data.color, alpha)

      rl.draw_line_ex(rl.Vector2(lx, cy_t + chevron_w * 0.5), rl.Vector2(cx_t, cy_t), chevron_thick, c_color)
      rl.draw_line_ex(rl.Vector2(rx, cy_t + chevron_w * 0.5), rl.Vector2(cx_t, cy_t), chevron_thick, c_color)

  def _draw_standard_chevrons(self, icx: float, bottom: float, distance: float, data: AetherGaugeData):
    is_stop = data.indicator_type in (IndicatorType.FORCE_STOP, IndicatorType.STOP_LIGHT)
    progress = (rl.get_time() * 1.2) % 1.0
    t_stop = max(0.05, min(1.0, distance / STOP_DISTANCE_MAX)) if is_stop else 1.0
    max_t = t_stop if is_stop else 1.0

    for i in range(CHEVRON_COUNT):
      t = max_t - (i + progress) * CHEVRON_SPACING
      if t < 0.0 or t > max_t:
        continue

      t_next = min(max_t, t + CHEVRON_STEP)
      cx_t = icx + _get_perspective_offset(t, data)
      cx_next = icx + _get_perspective_offset(t_next, data)

      cy_t = bottom - t * ROAD_HEIGHT
      cy_next = bottom - t_next * ROAD_HEIGHT

      dx = cx_next - cx_t
      dy = cy_next - cy_t
      len_v = math.hypot(dx, dy)
      dir_up_x, dir_up_y = (dx / len_v, dy / len_v) if len_v > 0.001 else (0.0, -1.0)

      dir_right_x = -dir_up_y
      dir_right_y = dir_up_x

      chevron_w = max(2.0, 14.0 - t * 6.0)
      chevron_h = chevron_w * 0.6
      chevron_thick = max(2.0, 4.0 - t * 2.0)

      lx = cx_t - dir_right_x * chevron_w - dir_up_x * chevron_h
      ly = cy_t - dir_right_y * chevron_w - dir_up_y * chevron_h
      rx = cx_t + dir_right_x * chevron_w - dir_up_x * chevron_h
      ry = cy_t + dir_right_y * chevron_w - dir_up_y * chevron_h

      alpha_factor = math.sin((t / max_t) * math.pi) if max_t > 0.01 else 0.0
      alpha = max(0, min(255, int(data.color.a * alpha_factor)))
      chev_color = _with_alpha(data.color, alpha)
      chev_shadow = rl.Color(0, 0, 0, int(alpha * 0.5))

      rl.draw_line_ex(rl.Vector2(lx, ly + 1.5), rl.Vector2(cx_t, cy_t + 1.5), chevron_thick, chev_shadow)
      rl.draw_line_ex(rl.Vector2(rx, ry + 1.5), rl.Vector2(cx_t, cy_t + 1.5), chevron_thick, chev_shadow)
      rl.draw_line_ex(rl.Vector2(lx, ly), rl.Vector2(cx_t, cy_t), chevron_thick, chev_color)
      rl.draw_line_ex(rl.Vector2(rx, ry), rl.Vector2(cx_t, cy_t), chevron_thick, chev_color)

  def _draw_traffic_light(self, icx: float, icy: float, distance: float, data: AetherGaugeData):
    t_light, cx_light, cy_road = _road_xy(distance, icx, icy + ROAD_HALF_SIZE, data)
    s_light = 1.0 - t_light

    scale_light = 0.6 + (s_light ** 2.0) * 1.4
    cy_light = cy_road - 35.0 * s_light
    width = 11.0 * scale_light
    height = 27.0 * scale_light

    rl.draw_rectangle_rounded(rl.Rectangle(cx_light - width/2, cy_light - height/2 + 1.5, width, height), 0.2, 4, rl.Color(0, 0, 0, 120))
    rect_housing = rl.Rectangle(cx_light - width/2, cy_light - height/2, width, height)
    rl.draw_rectangle_rounded(rect_housing, 0.2, 4, rl.Color(22, 22, 22, 255))
    rl.draw_rectangle_rounded_lines_ex(rect_housing, 0.2, 4, 1.0, rl.Color(80, 80, 80, 255))

    r_bulb = 2.2 * scale_light
    y_red = cy_light - 7.5 * scale_light
    y_yellow = cy_light
    y_green = cy_light + 7.5 * scale_light

    active_light = data.indicator_extra if data.indicator_extra in ("red", "yellow", "green") else "red"

    if active_light == "red":
      glow_pulse = _pulse(5.0)
      rl.draw_circle_v(rl.Vector2(cx_light, y_red), r_bulb + 3.0 * glow_pulse, rl.Color(255, 30, 60, 45))
      rl.draw_circle_v(rl.Vector2(cx_light, y_red), r_bulb + 6.0 * glow_pulse, rl.Color(255, 30, 60, 15))

    c_red = rl.Color(255, 30, 60, 255) if active_light == "red" else rl.Color(50, 10, 15, 255)
    c_yellow = rl.Color(255, 200, 0, 255) if active_light == "yellow" else rl.Color(50, 40, 0, 255)
    c_green = rl.Color(0, 255, 100, 255) if active_light == "green" else rl.Color(0, 40, 15, 255)

    rl.draw_circle_v(rl.Vector2(cx_light, y_red), r_bulb, c_red)
    rl.draw_circle_v(rl.Vector2(cx_light, y_yellow), r_bulb, c_yellow)
    rl.draw_circle_v(rl.Vector2(cx_light, y_green), r_bulb, c_green)

  def _draw_approaching_stop_sign(self, cx: float, icy: float, bottom: float,
                                  smoothed_distance: float, data: AetherGaugeData, font_bold: rl.Font):
    t_stop_gauge = _get_t_from_x(smoothed_distance)
    smoothed_s = max(0.0, min(1.0, 1.0 - (smoothed_distance / STOP_DISTANCE_MAX)))

    offset_stop = _get_perspective_offset(t_stop_gauge, data) if data else 0.0
    cx_stop = cx + offset_stop

    cy_road = bottom - t_stop_gauge * ROAD_HEIGHT
    y_sign = cy_road - 25.0 * smoothed_s

    r_min = 6.0
    r_max = 20.0
    r_sign = r_min + (smoothed_s ** 2.0) * (r_max - r_min)

    shadow_alpha = int(min(120, r_sign * 12))
    rl.draw_poly(rl.Vector2(cx_stop, y_sign + 2.0), 8, r_sign, 22.5, rl.Color(0, 0, 0, shadow_alpha))
    rl.draw_poly(rl.Vector2(cx_stop, y_sign), 8, r_sign, 22.5, COLOR_STOP_SIGN)

    outline_t = max(0.8, min(1.5, r_sign * 0.07))
    outline_a = int(max(0, min(200, (r_sign - 5.0) * 20)))
    if outline_a > 20:
      for i in range(8):
        a1 = math.radians(22.5 + i * 45.0)
        a2 = math.radians(22.5 + ((i + 1) % 8) * 45.0)
        p1 = rl.Vector2(cx_stop + r_sign * math.cos(a1), y_sign + r_sign * math.sin(a1))
        p2 = rl.Vector2(cx_stop + r_sign * math.cos(a2), y_sign + r_sign * math.sin(a2))
        rl.draw_line_ex(p1, p2, outline_t, _with_alpha(COLOR_STOP_SIGN_OUTLINE, outline_a))

    stop_font_size = max(4, int(r_sign * 0.7))
    stop_txt_size = measure_text_cached(font_bold, "STOP", stop_font_size)
    stop_pos = rl.Vector2(cx_stop - stop_txt_size.x / 2, y_sign - stop_txt_size.y / 2)
    rl.draw_text_ex(font_bold, "STOP", stop_pos, stop_font_size, 0, rl.WHITE)

  def _draw_mini_cradle(self, cx: float, bottom: float, data: AetherGaugeData, font_bold: rl.Font, font_medium: rl.Font):
    if not data.text:
      return

    if data.is_numeric:
      val_size = measure_text_cached(font_bold, data.text, 48)
      val_pos = rl.Vector2(int(cx - val_size.x / 2), int(bottom + 12))
      self._draw_text_with_shadow(font_bold, data.text, val_pos, 48, data.color)

      unit_y = bottom + 12 + val_size.y * 0.8
      if data.unit:
        unit_size = measure_text_cached(font_medium, data.unit, 20)
        unit_pos = rl.Vector2(int(cx - unit_size.x / 2), int(unit_y))
        self._draw_text_with_shadow(font_medium, data.unit, unit_pos, 20, rl.Color(255, 255, 255, 200))
        unit_y = unit_pos.y

      if data.reduction_text:
        red_size = measure_text_cached(font_medium, data.reduction_text, 20)
        red_pos = rl.Vector2(int(cx - red_size.x / 2), int(unit_y + 18))
        rl.draw_text_ex(font_medium, data.reduction_text, red_pos, 20, 0, rl.Color(255, 255, 255, 160))
    else:
      val_size = measure_text_cached(font_bold, data.text, 24)
      val_pos = rl.Vector2(int(cx - val_size.x / 2), int(bottom + 16))
      self._draw_text_with_shadow(font_bold, data.text, val_pos, 24, data.color)

  def _draw_text_with_shadow(self, font: rl.Font, text: str, pos: rl.Vector2, size: int, color: rl.Color):
    for dx, dy in ((-1, -1), (1, -1), (-1, 1), (1, 1)):
      rl.draw_text_ex(font, text, rl.Vector2(pos.x + dx, pos.y + dy), size, 0, rl.BLACK)
      rl.draw_text_ex(font, text, pos, size, 0, color)
