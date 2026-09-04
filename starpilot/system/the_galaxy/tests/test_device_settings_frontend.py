from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[4]
DEVICE_SETTINGS_PATH = REPO_ROOT / "starpilot/system/the_galaxy/assets/components/tools/device_settings.js"
DEVICE_SETTINGS_CSS_PATH = REPO_ROOT / "starpilot/system/the_galaxy/assets/components/tools/device_settings.css"


def _device_settings():
  return DEVICE_SETTINGS_PATH.read_text(encoding="utf-8")


def test_device_settings_surfaces_hidden_advanced_settings_count():
  source = _device_settings()

  assert "countAdvancedHiddenByDeveloperMode" in source
  assert "isAdvancedHiddenByDeveloperMode" in source
  assert "hiddenAdvancedCount" in source


def test_developer_mode_notice_is_rendered_when_advanced_settings_hidden():
  source = _device_settings()

  assert "ds-dev-mode-notice" in source
  assert "advanced setting" in source
  assert "Enable Developer Mode" in source


def test_developer_mode_notice_navigates_to_developer_section():
  source = _device_settings()

  assert 'window.__theGalaxyNavigate("/device_settings/developer")' in source


def test_advanced_settings_hidden_count_shown_in_status_bar():
  source = _device_settings()

  assert "advanced hidden" in source


def test_device_settings_uses_the_params_api_and_layout_json():
  source = _device_settings()

  assert 'fetch("/api/params/all")' in source
  assert 'fetch("/api/params/defaults")' in source
  assert 'fetch("/assets/components/tools/device_settings_layout.json?v=settings-tier-1"' in source


def test_developer_mode_notice_has_styles():
  css = DEVICE_SETTINGS_CSS_PATH.read_text(encoding="utf-8")

  assert ".ds-dev-mode-notice" in css
  assert ".ds-dev-mode-notice-btn" in css
