from types import SimpleNamespace

import openpilot.selfdrive.ui.mici.onroad.model_renderer as model_renderer


class _FakeParams:
  def __init__(self, enabled: bool):
    self.enabled = enabled

  def get(self, key):
    assert key == "HideLeadMarker"
    return b"0" if self.enabled else b"1"

  def get_bool(self, key):
    assert key == "HideLeadMarker"
    return not self.enabled


def test_lead_indicator_renders_in_aol_without_longitudinal_control(monkeypatch):
  monkeypatch.setattr(model_renderer, "ui_state", SimpleNamespace(always_on_lateral_active=True))
  renderer = object.__new__(model_renderer.ModelRenderer)
  renderer._params = _FakeParams(enabled=True)
  renderer._longitudinal_control = False

  assert renderer._should_render_lead_indicator(SimpleNamespace())


def test_lead_indicator_still_honors_disabled_setting():
  renderer = object.__new__(model_renderer.ModelRenderer)
  renderer._params = _FakeParams(enabled=False)

  assert not renderer._should_render_lead_indicator(SimpleNamespace())
  assert not renderer._should_render_lead_indicator(None)
