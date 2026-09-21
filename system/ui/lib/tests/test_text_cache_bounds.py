import pyray as rl

from openpilot.system.ui.lib import text_measure, wrap_text


def test_measure_text_cache_is_bounded(monkeypatch):
  monkeypatch.setattr(text_measure, "font_fallback", lambda font, _text: font)
  monkeypatch.setattr(text_measure.rl, "measure_text_ex", lambda *_args: rl.Vector2(10, 20))
  monkeypatch.setattr(text_measure, "find_emoji", lambda _text: [])
  text_measure._cache.clear()

  for index in range(text_measure.MAX_CACHE_ENTRIES * 3):
    text_measure.measure_text_cached(rl.Font(), f"dynamic-{index}", 32)

  assert len(text_measure._cache) <= text_measure.MAX_CACHE_ENTRIES


def test_measure_text_cache_still_returns_cached_value(monkeypatch):
  calls = []

  def fake_measure(*_args):
    calls.append(1)
    return rl.Vector2(10, 20)

  monkeypatch.setattr(text_measure, "font_fallback", lambda font, _text: font)
  monkeypatch.setattr(text_measure.rl, "measure_text_ex", fake_measure)
  monkeypatch.setattr(text_measure, "find_emoji", lambda _text: [])
  text_measure._cache.clear()

  font = rl.Font()
  first = text_measure.measure_text_cached(font, "stable", 32)
  second = text_measure.measure_text_cached(font, "stable", 32)

  assert len(calls) == 1
  assert (first.x, first.y) == (second.x, second.y)


def test_wrap_text_cache_is_bounded(monkeypatch):
  monkeypatch.setattr(wrap_text, "font_fallback", lambda font, _text: font)
  monkeypatch.setattr(wrap_text, "measure_text_cached", lambda *_args, **_kwargs: rl.Vector2(1, 1))
  wrap_text._cache.clear()

  for index in range(wrap_text.MAX_CACHE_ENTRIES * 3):
    wrap_text.wrap_text(rl.Font(), f"dynamic text {index}", 32, 500)

  assert len(wrap_text._cache) <= wrap_text.MAX_CACHE_ENTRIES


def test_wrap_text_cache_still_returns_cached_value(monkeypatch):
  calls = []

  def fake_measure(*_args, **_kwargs):
    calls.append(1)
    return rl.Vector2(1, 1)

  monkeypatch.setattr(wrap_text, "font_fallback", lambda font, _text: font)
  monkeypatch.setattr(wrap_text, "measure_text_cached", fake_measure)
  wrap_text._cache.clear()

  font = rl.Font()
  first = wrap_text.wrap_text(font, "stable text", 32, 500)
  before = len(calls)
  second = wrap_text.wrap_text(font, "stable text", 32, 500)

  assert len(calls) == before
  assert first == second
