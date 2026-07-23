import json
import subprocess
from types import SimpleNamespace

import pytest

from openpilot.starpilot.system import low_voltage_discord as report


class FakeParams:
  def __init__(self, values=None):
    self.values = values or {}
    self.puts = []
    self.removes = []

  def get(self, key, encoding=None):
    value = self.values.get(key)
    if encoding is not None and isinstance(value, bytes):
      return value.decode(encoding)
    return value

  def get_bool(self, key):
    value = self.values.get(key, False)
    return value in (True, 1, "1", b"1")

  def get_float(self, key):
    return float(self.values.get(key, 0.0))

  def put(self, key, value):
    self.values[key] = value
    self.puts.append((key, value))

  def put_bool(self, key, value):
    self.put(key, bool(value))

  def remove(self, key):
    self.values.pop(key, None)
    self.removes.append(key)


def owner_params(**overrides):
  values = {
    "GithubUsername": "jc01rho",
    "GithubSshKeys": "ssh-ed25519 test",
    "LowVoltageDiscordReport": True,
    "LowVoltageDiscordWebhook": "https://discord.com/api/webhooks/123/token",
    "LowVoltageShutdown": 11.8,
  }
  values.update(overrides)
  return FakeParams(values)


def test_owner_gate_requires_exact_username_ssh_keys_toggle_and_webhook():
  assert report.reporting_enabled(owner_params())
  assert report.reporting_enabled(owner_params(GithubUsername=" JC01RHO "))
  assert not report.reporting_enabled(owner_params(GithubUsername="someone"))
  assert not report.reporting_enabled(owner_params(GithubSshKeys=""))
  assert not report.reporting_enabled(owner_params(LowVoltageDiscordReport=False))
  assert not report.reporting_enabled(owner_params(LowVoltageDiscordWebhook=""))


def test_validate_webhook_restricts_discord_https_urls():
  assert report.validate_webhook_url("https://discord.com/api/webhooks/123/token")
  assert report.validate_webhook_url("https://discordapp.com/api/webhooks/123/token")
  assert report.validate_webhook_url("https://ptb.discord.com/api/webhooks/123/token")
  assert report.validate_webhook_url("https://canary.discord.com/api/webhooks/123/token")
  assert not report.validate_webhook_url("http://discord.com/api/webhooks/123/token")
  assert not report.validate_webhook_url("https://example.com/api/webhooks/123/token")
  assert not report.validate_webhook_url("https://discord.com.example/api/webhooks/123/token")


def test_voltage_summary_ignores_invalid_samples_and_tracks_range():
  summary = report.DriveVoltageSummary()
  for value in (0, 5999, 12000, 13500, 18001, 11850):
    summary.update(value)
  assert summary.samples == 3
  assert summary.latest_mv == 11850
  assert summary.min_mv == 11850
  assert summary.max_mv == 13500


def test_extract_voltage_requires_live_valid_known_peripheral():
  state = SimpleNamespace(pandaType="tres", voltage=12345)
  assert report.extract_voltage_mv(state, alive=True, valid=True) == 12345
  assert report.extract_voltage_mv(state, alive=False, valid=True) is None
  assert report.extract_voltage_mv(state, alive=True, valid=False) is None
  assert report.extract_voltage_mv(SimpleNamespace(pandaType="unknown", voltage=12345), alive=True, valid=True) is None


def test_build_payload_contains_voltage_data_but_not_webhook():
  summary = report.DriveVoltageSummary(latest_mv=12100, min_mv=11750, max_mv=14200, samples=50)
  payload = report.build_discord_payload(summary, threshold_v=11.8, drive_id="route--1", car_fingerprint="CHEVROLET_BOLT")
  encoded = json.dumps(payload)
  assert payload["content"]
  assert "11.75 V" in payload["content"]
  assert "route--1" in payload["content"]
  assert "webhooks" not in encoded
  assert len(payload["content"]) <= 2000


def test_pending_report_uses_stable_drive_id_for_deduplication():
  summary = report.DriveVoltageSummary(latest_mv=12100, min_mv=11800, max_mv=14200, samples=10)
  first = report.make_pending_report(summary, threshold_v=11.8, drive_id="route--1")
  second = report.make_pending_report(summary, threshold_v=11.8, drive_id="route--1")
  assert first["id"] == second["id"]


def test_send_report_uses_curl_argv_stdin_and_never_returns_secret():
  params = owner_params()
  calls = []

  def fake_run(cmd, **kwargs):
    calls.append((cmd, kwargs))
    return subprocess.CompletedProcess(cmd, 0, "", "")

  payload = {"content": "battery report"}
  result = report.send_discord_payload(params, payload, run=fake_run)

  assert result.ok
  assert result.error == ""
  assert len(calls) == 1
  cmd, kwargs = calls[0]
  assert isinstance(cmd, list)
  assert cmd[0] == "curl"
  assert params.values["LowVoltageDiscordWebhook"] not in cmd
  assert params.values["LowVoltageDiscordWebhook"] in kwargs["input"]
  assert '\\"content\\":\\"battery report\\"' in kwargs["input"]
  assert kwargs["shell"] is False
  assert kwargs["timeout"] <= 20
  assert params.values["LowVoltageDiscordWebhook"] not in repr(result)


def test_send_report_sanitizes_failures_and_rechecks_owner():
  params = owner_params(GithubUsername="someone")
  called = False

  def fake_run(*args, **kwargs):
    nonlocal called
    called = True
    raise AssertionError("must not send")

  result = report.send_discord_payload(params, {"content": "x"}, run=fake_run)
  assert not result.ok
  assert result.error == "disabled"
  assert not called

  params = owner_params()
  secret = params.values["LowVoltageDiscordWebhook"]

  def failed_run(*args, **kwargs):
    raise subprocess.TimeoutExpired(args[0], 15, output=secret)

  result = report.send_discord_payload(params, {"content": "x"}, run=failed_run)
  assert not result.ok
  assert result.error == "timeout"
  assert secret not in repr(result)


def test_pending_report_is_deduplicated_after_success():
  params = owner_params(LowVoltageDiscordLastDrive="")
  summary = report.DriveVoltageSummary(latest_mv=12100, min_mv=11800, max_mv=14300, samples=10)
  pending = report.make_pending_report(summary, threshold_v=11.8, drive_id="drive-1", car_fingerprint="BOLT")
  params.put("LowVoltageDiscordPendingReport", pending)

  calls = []
  ok = lambda *args, **kwargs: calls.append(args) or subprocess.CompletedProcess(args[0], 0, "", "")
  assert report.deliver_pending_report(params, run=ok).ok
  assert params.values["LowVoltageDiscordLastDrive"] == pending["id"]
  assert "LowVoltageDiscordPendingReport" in params.removes
  assert report.deliver_pending_report(params, run=ok).error == "no_pending"
  assert len(calls) == 1


def test_invalid_pending_report_is_removed_without_sending():
  params = owner_params(LowVoltageDiscordPendingReport={"unexpected": True})
  result = report.deliver_pending_report(params, run=lambda *args, **kwargs: pytest.fail("must not send"))
  assert not result.ok
  assert result.error == "invalid_pending"
  assert "LowVoltageDiscordPendingReport" in params.removes


def test_drive_reporter_creates_one_pending_report_per_started_falling_edge():
  params = owner_params(CurrentRoute="route--segment")
  reporter = report.LowVoltageDriveReporter(params)
  reporter.update_started(False)
  reporter.sample(12500)
  assert reporter.update_started(False) is None

  reporter.update_started(True)
  reporter.sample(14200)
  reporter.sample(11900)
  pending = reporter.update_started(False, car_fingerprint="CHEVROLET_BOLT")

  assert pending is not None
  assert pending["drive_id"] == "route--segment"
  assert pending["summary"]["min_mv"] == 11900
  assert reporter.update_started(False) is None


def test_delayed_delivery_cancels_if_device_returns_onroad():
  params = owner_params(IsOnroad=True)
  sleeps = []
  result = report.deliver_after_offroad_delay(params, delay_s=5, sleep=lambda seconds: sleeps.append(seconds),
                                                run=lambda *args, **kwargs: pytest.fail("must not send"))
  assert sleeps == [5]
  assert result.error == "onroad"


def test_send_report_keeps_pending_when_transport_fails_then_retries():
  params = owner_params(CurrentRoute="route-retry")
  summary = report.DriveVoltageSummary(latest_mv=12100, min_mv=11800, max_mv=14000, samples=5)
  params.put("LowVoltageDiscordPendingReport", report.make_pending_report(summary, threshold_v=11.8, drive_id="route-retry"))

  failed = lambda *args, **kwargs: subprocess.CompletedProcess(args[0], 22, "", "failed")
  assert report.deliver_pending_report(params, run=failed).error == "http"
  assert "LowVoltageDiscordPendingReport" in params.values

  succeeded = lambda *args, **kwargs: subprocess.CompletedProcess(args[0], 0, "", "")
  assert report.deliver_pending_report(params, run=succeeded).ok
  assert "LowVoltageDiscordPendingReport" not in params.values


def test_remove_webhook_disables_and_clears_pending_secret():
  params = owner_params(LowVoltageDiscordPendingReport={"id": "pending"})
  report.remove_webhook(params)
  assert params.values["LowVoltageDiscordReport"] is False
  assert "LowVoltageDiscordWebhook" not in params.values
  assert "LowVoltageDiscordPendingReport" not in params.values


def test_failed_pending_report_is_not_overwritten_by_next_drive():
  params = owner_params()
  first_summary = report.DriveVoltageSummary(latest_mv=12000, min_mv=11700, max_mv=14000, samples=5)
  second_summary = report.DriveVoltageSummary(latest_mv=12200, min_mv=11900, max_mv=14100, samples=6)
  first = report.make_pending_report(first_summary, threshold_v=11.8, drive_id="drive-1")
  second = report.make_pending_report(second_summary, threshold_v=11.8, drive_id="drive-2")
  report.save_pending_report(params, first)
  report.save_pending_report(params, second)
  assert [item["id"] for item in params.values["LowVoltageDiscordPendingReport"]] == [first["id"], second["id"]]

  failed = lambda *args, **kwargs: subprocess.CompletedProcess(args[0], 22, "", "failed")
  assert report.deliver_pending_report(params, run=failed).error == "http"
  assert len(params.values["LowVoltageDiscordPendingReport"]) == 2

  succeeded = lambda *args, **kwargs: subprocess.CompletedProcess(args[0], 0, "", "")
  assert report.deliver_pending_report(params, run=succeeded).ok
  assert [item["id"] for item in params.values["LowVoltageDiscordPendingReport"]] == [second["id"]]
