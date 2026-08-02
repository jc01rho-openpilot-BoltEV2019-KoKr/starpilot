import sys
from types import ModuleType, SimpleNamespace

import numpy as np
import pytest


def _stub_ui_dependencies() -> None:
  """Keep this focused renderer test independent from a live raylib context."""
  application = ModuleType("openpilot.system.ui.lib.application")
  application.gui_app = SimpleNamespace(target_fps=20)
  application.GL_VERSION = ""
  application.FONT_SCALE = 1.0
  application.font_fallback = lambda font: font
  sys.modules[application.__name__] = application

  shader_polygon = ModuleType("openpilot.system.ui.lib.shader_polygon")
  shader_polygon.Gradient = lambda **kwargs: SimpleNamespace(**kwargs)
  shader_polygon.draw_polygon = lambda *args, **kwargs: None
  sys.modules[shader_polygon.__name__] = shader_polygon

  text_measure = ModuleType("openpilot.system.ui.lib.text_measure")
  text_measure.measure_text_cached = lambda *args, **kwargs: None
  sys.modules[text_measure.__name__] = text_measure

  widgets = ModuleType("openpilot.system.ui.widgets")
  widgets.Widget = object
  sys.modules[widgets.__name__] = widgets

  ui_state = ModuleType("openpilot.selfdrive.ui.ui_state")
  ui_state.ui_state = SimpleNamespace()
  ui_state.UIStatus = SimpleNamespace()
  sys.modules[ui_state.__name__] = ui_state


_stub_ui_dependencies()
import openpilot.selfdrive.ui.onroad.model_renderer as model_renderer


class _FakeSubMaster:
  def __init__(self, plan):
    self.recv_frame = {"starpilotPlan": 1}
    self._plan = plan

  def __getitem__(self, key):
    assert key == "starpilotPlan"
    return self._plan


@pytest.mark.parametrize(
  ("lane_width_left", "lane_width_right", "expected_side"),
  [
    (3.5, 0.0, 0),
    (0.0, 3.5, 1),
  ],
)
def test_adjacent_path_keeps_a_single_valid_side(monkeypatch, lane_width_left, lane_width_right, expected_side):
  fake_ui_state = SimpleNamespace(
    sm=_FakeSubMaster(SimpleNamespace(laneWidthLeft=lane_width_left, laneWidthRight=lane_width_right)),
    started_frame=0,
  )
  monkeypatch.setattr(model_renderer, "ui_state", fake_ui_state)

  renderer = object.__new__(model_renderer.ModelRenderer)
  left_outer = np.ones((2, 3), dtype=np.float32)
  left_inner = np.ones((2, 3), dtype=np.float32)
  right_inner = np.ones((2, 3), dtype=np.float32)
  right_outer = np.ones((2, 3), dtype=np.float32)
  renderer._lane_lines = [
    SimpleNamespace(raw_points=left_outer),
    SimpleNamespace(raw_points=left_inner),
    SimpleNamespace(raw_points=right_inner),
    SimpleNamespace(raw_points=right_outer),
  ]
  renderer._adjacent_path_vertices = [
    np.ones((4, 2), dtype=np.float32),
    np.ones((4, 2), dtype=np.float32),
  ]

  def fake_get_adjacent_path_polygon(line1, *_args):
    side = 0 if line1 is left_outer else 1
    return np.array([[side, 0], [side, 1], [side + 0.5, 1], [side + 0.5, 0]], dtype=np.float32)

  monkeypatch.setattr(renderer, "_get_adjacent_path_polygon", fake_get_adjacent_path_polygon)

  renderer._update_adjacent_paths(max_idx=1, max_distance=10.0)

  assert renderer._adjacent_path_vertices[expected_side].size >= 4
  assert renderer._adjacent_path_vertices[1 - expected_side].size == 0
