from types import SimpleNamespace

import pytest
import requests

from openpilot.common.params import Params
from openpilot.starpilot.power import discord_report as report
from openpilot.starpilot.power.offroad_preferences import KEY as POWER_KEY, PowerPolicy, to_value

WEBHOOK = "https://discord.com/api/webhooks/123/token-secret"


class Response:
  def __init__(self, status_code):
    self.status_code = status_code
    self.closed = False

  def close(self):
    self.closed = True


class Post:
  def __init__(self, status_code=204, error=None):
    self.status_code, self.error, self.calls = status_code, error, []

  def __call__(self, url, **kwargs):
    self.calls.append((url, kwargs))
    if self.error is not None:
      raise self.error
    return Response(self.status_code)


@pytest.fixture
def params(tmp_path):
  store = Params(str(tmp_path))
  store.put("GithubUsername", "jc01rho", block=True)
  store.put("GithubSshKeys", "ssh-ed25519 AAAA", block=True)
  return store


class Source(SimpleNamespace):
  def __getitem__(self, key):
    return self.data[key]

  def update(self, timeout):
    pass


def peripheral(voltage, panda="dos"):
  return SimpleNamespace(pandaType=panda, voltage=voltage)


def drive(reporter, voltages, *, start=0.0):
  reporter.update_started(True, start)
  for stamp, voltage in enumerate(voltages, 1):
    reporter.sample(stamp, peripheral(voltage))
    reporter.sample(stamp, peripheral(voltage))  # a repeated message is one sample
  return reporter.update_started(False, start + 10, car_fingerprint="CHEVROLET_BOLT_EUV")


def test_webhook_validation_and_owner_gate(params):
  assert report.validate_webhook_url(WEBHOOK)
  for bad in ("http://discord.com/api/webhooks/1/t", "https://evil.example/api/webhooks/1/t", "https://discord.com/other/1/t", None, 5):
    assert not report.validate_webhook_url(bad)
  assert report.configure_webhook(params, WEBHOOK)
  assert report.webhook_status(params) == {"owner": True, "configured": True, "enabled": True}
  params.put("GithubUsername", "someone", block=True)
  assert report.webhook_status(params) == {"owner": False, "configured": False, "enabled": False}
  assert not report.reporting_enabled(params)
  assert not report.configure_webhook(params, WEBHOOK)


def test_summary_ignores_unknown_panda_and_out_of_range_voltage():
  assert report.extract_voltage_mv(peripheral(12400, "unknown")) is None
  assert report.extract_voltage_mv(peripheral(500)) is None
  assert report.extract_voltage_mv(None) is None
  assert report.extract_voltage_mv(peripheral(12400)) == 12400


def test_drive_end_queues_report_with_effective_cutoff_and_delivers_once_parked(params):
  report.configure_webhook(params, WEBHOOK)
  params.put("CurrentRoute", "route-1", block=True)
  params.put(POWER_KEY, to_value(PowerPolicy(True, 6, 122)), block=True)
  post = Post()
  reporter = report.DriveVoltageReporter(params, post=post)
  pending = drive(reporter, (12600, 11900, 1000, 12100))
  assert pending is not None and pending["summary"] == {"latest_mv": 12100, "min_mv": 11900, "max_mv": 12600, "samples": 3}
  assert pending["threshold_v"] == 12.2 and pending["drive_id"] == "route-1"

  assert reporter.deliver_if_due(12.0, lambda: True) is None  # waits after the drive ends
  assert reporter.deliver_if_due(16.0, lambda: False) is None  # never sends while not parked
  assert post.calls == []
  assert reporter.deliver_if_due(16.0, lambda: True) == ""
  url, kwargs = post.calls[0]
  assert url == WEBHOOK and kwargs["timeout"] == (3, 10) and kwargs["allow_redirects"] is False
  content = kwargs["json"]["content"]
  assert "Minimum: **11.90 V**" in content and "Below cutoff: YES" in content and "CHEVROLET_BOLT_EUV" in content
  assert params.get(report.PENDING_KEY) is None and params.get(report.LAST_DRIVE_KEY) == pending["id"]


def test_failed_delivery_keeps_report_and_retries_after_two_minutes(params):
  report.configure_webhook(params, WEBHOOK)
  post = Post(error=requests.ConnectionError("offline"))
  reporter = report.DriveVoltageReporter(params, post=post)
  drive(reporter, (12300,))
  assert reporter.deliver_if_due(15.0, lambda: True) == "transport"
  assert len(report.pending_queue(params)) == 1
  assert reporter.deliver_if_due(15.0 + report.DriveVoltageReporter.RETRY_S - 1, lambda: True) is None
  post.error, post.status_code = None, 500
  assert reporter.deliver_if_due(15.0 + report.DriveVoltageReporter.RETRY_S, lambda: True) == "http 500"
  post.status_code = 200
  assert reporter.deliver_if_due(15.0 + 2 * report.DriveVoltageReporter.RETRY_S, lambda: True) == ""
  assert report.pending_queue(params) == []


def test_disabled_or_empty_drive_queues_nothing(params):
  reporter = report.DriveVoltageReporter(params, post=Post())
  assert drive(reporter, (12300,)) is None  # no webhook configured
  report.configure_webhook(params, WEBHOOK)
  assert drive(reporter, ()) is None  # no valid sample
  assert report.pending_queue(params) == []


def test_remove_clears_secret_and_queue(params):
  report.configure_webhook(params, WEBHOOK)
  report.save_pending_report(params, {"id": "x", "drive_id": "", "threshold_v": 11.8, "summary": {}})
  report.remove_webhook(params)
  assert params.get(report.WEBHOOK_KEY) is None and params.get(report.PENDING_KEY) is None
  assert not params.get_bool(report.REPORT_KEY)


def test_analytics_worker_samples_peripheral_state_and_reports_at_drive_end(params):
  from openpilot.starpilot.analytics.runtime import SERVICES, AnalyticsWorker
  report.configure_webhook(params, WEBHOOK)
  params.put_bool("IsOffroad", True, block=True)
  clock = [1.0]
  services = ("deviceState", "peripheralState")
  source = Source(data={"deviceState": SimpleNamespace(started=True), "peripheralState": peripheral(12200)},
                  valid=dict.fromkeys(services, True), alive=dict.fromkeys(services, True),
                  logMonoTime=dict.fromkeys(services, 1_000_000_000))
  for name in set(SERVICES) - set(services):
    source.valid[name] = source.alive[name] = False
    source.logMonoTime[name] = 0
  post = Post()
  worker = AnalyticsWorker(params, source, voltage_reporter=report.DriveVoltageReporter(params, post=post),
                           clock_valid=lambda: False, monotonic=lambda: clock[0])
  worker.poll_once()
  source.data["peripheralState"] = peripheral(11700)
  source.logMonoTime = dict.fromkeys(source.logMonoTime, 1_500_000_000)
  clock[0] = 1.5
  worker.poll_once()
  source.data["deviceState"].started = False
  clock[0] = 1.6
  worker.poll_once()
  assert report.pending_queue(params)[0]["summary"]["min_mv"] == 11700
  source.logMonoTime["deviceState"] = 7_000_000_000
  clock[0] = 7.0
  worker.poll_once()
  assert len(post.calls) == 1 and report.pending_queue(params) == []
