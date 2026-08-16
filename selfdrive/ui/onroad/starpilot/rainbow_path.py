from __future__ import annotations

import colorsys

import pyray as rl
from openpilot.system.ui.lib.shader_polygon import Gradient


HUE_RANGE = 120.0
SCROLL_DEG_PER_SEC_PER_MPS = 5.0
ALPHA_BOTTOM = 0.5
ALPHA_TOP = 0.1
NUM_STOPS = 12


def _hsla_to_color(h: float, s: float, l: float, a: float) -> rl.Color:
  rgb = colorsys.hls_to_rgb(h, l, s)
  return rl.Color(int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255), int(a * 255))


class RainbowPath:
  """Rainbow path renderer for the StarPilot onroad UI."""

  def __init__(self) -> None:
    self._hue_offset: float = 0.0
    self._last_time: float = 0.0

  def update(self, speed_ms: float) -> None:
    """Accumulate hue offset from vehicle speed. Call once per frame."""
    now = rl.get_time()
    dt = now - self._last_time if self._last_time > 0.0 else 0.0
    self._last_time = now
    if speed_ms > 0.0 and dt > 0.0:
      self._hue_offset = (self._hue_offset + speed_ms * SCROLL_DEG_PER_SEC_PER_MPS * dt) % 360.0

  def get_gradient(self, gradient_bottom: float, gradient_top: float) -> Gradient:
    """Build a Gradient compatible with draw_polygon().

    Args:
      gradient_bottom: Normalized y-position (0-1) of the path bottom.
      gradient_top: Normalized y-position (0-1) of the path top.
    """
    stops = [i / (NUM_STOPS - 1) for i in range(NUM_STOPS)]
    colors = []

    for stop in stops:
      path_hue = (stop * HUE_RANGE + self._hue_offset) % 360.0
      alpha = ALPHA_BOTTOM + (ALPHA_TOP - ALPHA_BOTTOM) * stop
      colors.append(_hsla_to_color(path_hue / 360.0, 1.0, 0.5, alpha))

    return Gradient(
      start=(0.0, gradient_bottom),
      end=(0.0, gradient_top),
      colors=colors,
      stops=stops,
    )
