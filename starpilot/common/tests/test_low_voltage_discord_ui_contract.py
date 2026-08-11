from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[3]


def test_low_voltage_discord_param_contract_is_private():
  params_keys = (REPO_ROOT / "common/params_keys.h").read_text()
  assert '{"LowVoltageDiscordWebhook", {PERSISTENT | DONT_LOG, STRING' in params_keys
  assert '{"LowVoltageDiscordPendingReport", {PERSISTENT | DONT_LOG, JSON, "[]", "[]"' in params_keys


def test_python_and_qt_device_settings_are_owner_gated():
  python_ui = (REPO_ROOT / "selfdrive/ui/layouts/settings/starpilot/system_settings.py").read_text()
  qt_ui = (REPO_ROOT / "starpilot/ui/qt/offroad/device_settings.cc").read_text()
  assert 'owner_is_allowed(self._controller._params)' in python_ui
  assert 'Keyboard(min_text_size=1, password_mode=True' in python_ui
  assert 'lowVoltageDiscordOwner(params)' in qt_ui
  assert 'InputDialog::getText' in qt_ui and 'true, 1' in qt_ui


def test_galaxy_has_masked_dedicated_secret_api_and_control():
  server = (REPO_ROOT / "starpilot/system/the_galaxy/the_galaxy.py").read_text()
  layout = (REPO_ROOT / "starpilot/system/the_galaxy/assets/components/tools/device_settings_layout.json").read_text()
  javascript = (REPO_ROOT / "starpilot/system/the_galaxy/assets/components/tools/device_settings.js").read_text()
  snackbar = (REPO_ROOT / "starpilot/system/the_galaxy/assets/js/snackbar.js").read_text()
  assert '"LowVoltageDiscordWebhook",' in server and "GALAXY_PRIVATE_PARAM_KEYS" in server
  assert '@app.route("/api/low_voltage_discord"' in server
  assert '"ui_type": "discord_webhook"' in layout
  assert layout.count('"label": "Drive-End Battery Discord Report"') == 1
  assert 'type="password"' in javascript
  assert 'Configured' in javascript
  assert "async function readJsonResponse(response)" in javascript
  assert "Galaxy API unavailable. Restart the device." in javascript
  assert "snackbar.textContent = String(msg ?? \"\")" in snackbar


def test_starpilot_process_tracks_peripheral_voltage_and_offroad_transition():
  process = (REPO_ROOT / "starpilot/starpilot_process.py").read_text()
  assert '"peripheralState"' in process
  assert "LowVoltageDriveReporter(params)" in process
  assert "low_voltage_reporter.update_started(False" in process
  assert "deliver_after_offroad_delay" in process
