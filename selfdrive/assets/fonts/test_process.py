import json

from openpilot.selfdrive.assets.fonts import process


def test_korean_translation_glyphs_are_added_to_unifont(tmp_path, monkeypatch):
  languages_path = tmp_path / "languages.json"
  translations_path = tmp_path / "app_ko.po"
  languages_path.write_text(json.dumps({"한국어": "main_ko"}), encoding="utf-8")
  translations_path.write_text('msgstr "한글 테스트"', encoding="utf-8")

  monkeypatch.setattr(process, "LANGUAGES_FILE", languages_path)
  monkeypatch.setattr(process, "TRANSLATIONS_DIR", tmp_path)

  _, unifont_codepoints = process._char_sets()

  assert {ord(character) for character in "한글테스트"} <= set(unifont_codepoints)
