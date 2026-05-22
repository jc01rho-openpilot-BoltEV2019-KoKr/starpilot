from __future__ import annotations
import math
from dataclasses import dataclass
from collections.abc import Callable
from enum import Enum
import pyray as rl
from openpilot.selfdrive.ui import UI_BORDER_SIZE
from openpilot.selfdrive.ui.lib.starpilot_status import get_screen_edge_color
from openpilot.selfdrive.ui.ui_state import ui_state


class BorderLayer(Enum):
  BEHIND = 0
  OVERLAY = 1


@dataclass
class BorderEffect:
  render_fn: Callable[[rl.Rectangle, float], None]
  layer: BorderLayer
  name: str = ""


_GLOW_LAYERS = 16
_GLOW_MAX_ALPHA = 255
_GLOW_MIN_ALPHA = 250
_GLOW_BASE_INTENSITY = 0.70
_GLOW_SPAN = 3.5
_BREATHING_PERIOD = 4.5
_GLOW_FADE_IN_DURATION = 0.6

_CURVATURE_MIN = 0.0005
_CURVATURE_MAX = 0.02

_GREEN = rl.Color(34, 197, 94, 255)
_AMBER = rl.Color(251, 191, 36, 255)
_ORANGE = rl.Color(234, 88, 12, 255)
_RED = rl.Color(201, 34, 49, 255)

_last_was_active = False
_activation_start = 0.0
_fade_out_start = 0.0
_last_state = None


def _csc_state():
  sm = ui_state.sm
  if sm.recv_frame["starpilotPlan"] < ui_state.started_frame:
    return None
  if sm.recv_frame["carState"] < ui_state.started_frame:
    return None
  if sm.recv_frame["controlsState"] < ui_state.started_frame:
    return None

  plan = sm["starpilotPlan"]
  if plan.speedLimitChanged or not ui_state.params.get_bool("ShowCSCStatus"):
    return None

  car_state = sm["carState"]
  v_cruise = car_state.vCruiseCluster
  if v_cruise == 0.0:
    v_cruise = sm["controlsState"].vCruiseDEPRECATED
  is_cruise_set = 0 < v_cruise < 255

  if not is_cruise_set:
    return None

  return {
    'training': plan.cscTraining,
    'active': plan.cscControllingSpeed,
    'curvature': plan.roadCurvature,
  }


def _intensity(curvature: float) -> float:
  if abs(curvature) < _CURVATURE_MIN:
    return _GLOW_BASE_INTENSITY
  curve = min(1.0, (abs(curvature) - _CURVATURE_MIN) / (_CURVATURE_MAX - _CURVATURE_MIN))
  return _GLOW_BASE_INTENSITY + (1.0 - _GLOW_BASE_INTENSITY) * curve


def _glow_period(intensity: float) -> float:
  t = max(0.0, min(1.0, (intensity - _GLOW_BASE_INTENSITY) / (1.0 - _GLOW_BASE_INTENSITY)))
  return _BREATHING_PERIOD / (1.0 + 2.0 * t)


def _lerp_color(a: rl.Color, b: rl.Color, t: float) -> rl.Color:
  t = max(0.0, min(1.0, t))
  return rl.Color(
    a.r + int((b.r - a.r) * t),
    a.g + int((b.g - a.g) * t),
    a.b + int((b.b - a.b) * t),
    255)


def _glow_color(intensity: float) -> rl.Color:
  t = max(0.0, min(1.0, (intensity - _GLOW_BASE_INTENSITY) / (1.0 - _GLOW_BASE_INTENSITY)))
  if t < 0.5:
    return _lerp_color(_GREEN, _AMBER, t / 0.5)
  elif t < 0.6:
    return _lerp_color(_AMBER, _ORANGE, (t - 0.5) / 0.1)
  else:
    return _lerp_color(_ORANGE, _RED, (t - 0.6) / 0.4)


def _render_csc_glow(border_rect: rl.Rectangle, border_width: float = UI_BORDER_SIZE):
  global _last_was_active, _activation_start, _fade_out_start, _last_state

  state = _csc_state()
  now = rl.get_time()
  border_color = get_screen_edge_color(ui_state)

  if state is None or not state['active']:
    if _last_was_active:
      _fade_out_start = now
      _last_was_active = False
    if _last_state is None:
      return
    fade_out = max(0.0, 1.0 - (now - _fade_out_start) / _GLOW_FADE_IN_DURATION)
    if fade_out <= 0:
      _last_state = None
      return
    intensity, period, color, t_norm = _last_state
    fade = fade_out
  else:
    if not _last_was_active:
      _activation_start = now
      _fade_out_start = 0.0
    _last_was_active = True

    intensity = _intensity(state['curvature'])
    period = _glow_period(intensity)
    color = _glow_color(intensity)
    t_norm = max(0.0, min(1.0, (intensity - _GLOW_BASE_INTENSITY) / (1.0 - _GLOW_BASE_INTENSITY)))
    _last_state = (intensity, period, color, t_norm)
    fade = min(1.0, (now - _activation_start) / _GLOW_FADE_IN_DURATION)

  elapsed = now - _activation_start
  phase = (elapsed % period) / period
  amplitude = 0.3 + 0.7 * t_norm
  breath = max(0.0, min(1.0, 0.5 + amplitude * math.sin(phase * 2 * math.pi)))
  base_alpha = max(_GLOW_MIN_ALPHA * fade, _GLOW_MAX_ALPHA * intensity * breath * fade)

  step = border_width * _GLOW_SPAN / (_GLOW_LAYERS - 1)
  base_inset = border_width * 0.5

  for i in range(_GLOW_LAYERS):
    inset = base_inset + i * step
    t = i / (_GLOW_LAYERS - 1)
    a = int(base_alpha * (1.0 - t) * (1.0 - t))
    if a < 3:
      continue

    glow_rect = rl.Rectangle(
      border_rect.x + inset,
      border_rect.y + inset,
      border_rect.width - 2 * inset,
      border_rect.height - 2 * inset,
    )
    if t < 0.4:
      layer_color = border_color
    else:
      blend_factor = (t - 0.4) / 0.6
      layer_color = _lerp_color(border_color, color, blend_factor)
    rl.draw_rectangle_rounded_lines_ex(glow_rect, 0.12, 10, int(border_width * 1.5), rl.Color(layer_color.r, layer_color.g, layer_color.b, a))


_effects: list[BorderEffect] = [
  BorderEffect(_render_csc_glow, BorderLayer.BEHIND, "csc_glow"),
]


def render_behind(border_rect: rl.Rectangle, border_width: float):
  for effect in _effects:
    if effect.layer == BorderLayer.BEHIND:
      effect.render_fn(border_rect, border_width)


def render_overlay(border_rect: rl.Rectangle, border_width: float):
  for effect in _effects:
    if effect.layer == BorderLayer.OVERLAY:
      effect.render_fn(border_rect, border_width)
