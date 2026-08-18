from types import SimpleNamespace

from openpilot.system.ui.lib import application


def test_raylib_target_fps_limits_mici(monkeypatch):
  monkeypatch.setattr(application, "OFFSCREEN", False)
  monkeypatch.setattr(application, "DEVICE_TYPE", "mici")

  assert application._raylib_target_fps(60) == 60


def test_raylib_target_fps_limits_other_devices(monkeypatch):
  monkeypatch.setattr(application, "OFFSCREEN", False)
  monkeypatch.setattr(application, "DEVICE_TYPE", "tici")

  assert application._raylib_target_fps(60) == 60


def test_raylib_target_fps_disables_limit_for_offscreen(monkeypatch):
  monkeypatch.setattr(application, "OFFSCREEN", True)
  monkeypatch.setattr(application, "DEVICE_TYPE", "tici")

  assert application._raylib_target_fps(60) == 0


def test_burn_in_shift_transitions_between_positions(monkeypatch):
  app = object.__new__(application.GuiApplication)
  app._burn_in_start_time = 100.0

  monkeypatch.setattr(application, "BURN_IN_PREVENTION", True)
  monkeypatch.setattr(application, "BURN_IN_SHIFT_INTERVAL", 10.0)
  monkeypatch.setattr(application, "BURN_IN_SHIFT_PIXELS", 2)
  monkeypatch.setattr(application, "BURN_IN_SHIFT_TRANSITION_SECONDS", 2.0)

  assert app._burn_in_shift(108.0) == (0.0, 0.0)
  midpoint = app._burn_in_shift(109.0)
  assert midpoint == (-1.0, 0.0)
  assert app._burn_in_shift(110.0) == (-2.0, 0.0)


def test_font_supports_text_checks_all_glyphs():
  font = SimpleNamespace(
    texture=SimpleNamespace(id=101),
    glyphCount=2,
    glyphs=[SimpleNamespace(value=ord("A")), SimpleNamespace(value=ord("한"))],
  )

  assert application._font_supports_text(font, "A한")
  assert not application._font_supports_text(font, "A글")


def test_font_fallback_loads_missing_text_glyphs(monkeypatch):
  inter_font = SimpleNamespace(
    texture=SimpleNamespace(id=102),
    glyphCount=1,
    glyphs=[SimpleNamespace(value=ord("A"))],
  )
  unifont_font = SimpleNamespace(
    texture=SimpleNamespace(id=103),
    glyphCount=1,
    glyphs=[SimpleNamespace(value=ord("A"))],
  )
  dynamic_font = object()
  fake_app = SimpleNamespace(
    font=lambda _: unifont_font,
    font_for_text=lambda text: dynamic_font,
  )

  monkeypatch.setattr(application, "gui_app", fake_app)
  monkeypatch.setattr(application.multilang, "requires_unifont", lambda: False)

  assert application.font_fallback(inter_font, "한글") is dynamic_font
