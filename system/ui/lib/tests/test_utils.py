from types import SimpleNamespace

from openpilot.system.ui.lib import utils


def test_draw_circle_gradient_uses_and_caches_vector_api(monkeypatch):
  calls = []
  monkeypatch.setattr(utils.rl, "Vector2", lambda x, y: SimpleNamespace(x=x, y=y))
  monkeypatch.setattr(utils.rl, "draw_circle_gradient", lambda *args: calls.append(args))
  monkeypatch.setattr(utils, "_draw_circle_gradient_vector_api", None)

  utils.draw_circle_gradient_compat(10.5, 20.5, 30, "inner", "outer")
  utils.draw_circle_gradient_compat(11.5, 21.5, 31, "inner", "outer")

  assert [len(call) for call in calls] == [4, 4]
  assert calls[0][0].x == 10.5
  assert calls[0][0].y == 20.5


def test_draw_circle_gradient_falls_back_and_caches_legacy_api(monkeypatch):
  calls = []

  def draw_circle_gradient(*args):
    calls.append(args)
    if len(args) == 4:
      raise RuntimeError("function requires 5 arguments")

  monkeypatch.setattr(utils.rl, "Vector2", lambda x, y: SimpleNamespace(x=x, y=y))
  monkeypatch.setattr(utils.rl, "draw_circle_gradient", draw_circle_gradient)
  monkeypatch.setattr(utils, "_draw_circle_gradient_vector_api", None)

  utils.draw_circle_gradient_compat(10.5, 20.5, 30, "inner", "outer")
  utils.draw_circle_gradient_compat(11.5, 21.5, 31, "inner", "outer")

  assert [len(call) for call in calls] == [4, 5, 5]
  assert calls[1][:2] == (10, 20)
  assert calls[2][:2] == (11, 21)
