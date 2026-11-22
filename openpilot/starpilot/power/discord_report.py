"""Owner-only drive-end 12 V supply report sent to a private Discord webhook.

The usage_stats worker samples peripheralState while a drive runs, queues one
report when the drive ends and delivers it while parked. The webhook is a secret
(DONT_LOG param) and never leaves this module except as the request target.
"""
from __future__ import annotations

from dataclasses import asdict, dataclass
import datetime
import hashlib
from typing import Any
from urllib.parse import urlparse

import requests

from openpilot.starpilot.power.offroad_preferences import effective, read_saved

OWNER_GITHUB_USERNAME = "jc01rho"
REPORT_KEY = "LowVoltageDiscordReport"
WEBHOOK_KEY = "LowVoltageDiscordWebhook"
PENDING_KEY = "LowVoltageDiscordPendingReport"
LAST_DRIVE_KEY = "LowVoltageDiscordLastDrive"
MIN_VALID_VOLTAGE_MV = 6000
MAX_VALID_VOLTAGE_MV = 18000
MAX_DISCORD_CONTENT_LENGTH = 2000
MAX_PENDING_REPORTS = 20
ALLOWED_HOSTS = frozenset(("discord.com", "discordapp.com", "ptb.discord.com", "canary.discord.com"))


@dataclass
class DriveVoltageSummary:
  latest_mv: int | None = None
  min_mv: int | None = None
  max_mv: int | None = None
  samples: int = 0

  def update(self, voltage_mv: int | None) -> None:
    if voltage_mv is None or not MIN_VALID_VOLTAGE_MV <= voltage_mv <= MAX_VALID_VOLTAGE_MV:
      return
    self.latest_mv = voltage_mv
    self.min_mv = voltage_mv if self.min_mv is None else min(self.min_mv, voltage_mv)
    self.max_mv = voltage_mv if self.max_mv is None else max(self.max_mv, voltage_mv)
    self.samples += 1


def _text(params, key: str) -> str:
  value = params.get(key)
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="replace")
  return value if isinstance(value, str) else ""


def owner_is_allowed(params) -> bool:
  return (_text(params, "GithubUsername").strip().casefold() == OWNER_GITHUB_USERNAME and
          bool(_text(params, "GithubSshKeys").strip()))


def validate_webhook_url(url: object) -> bool:
  if not isinstance(url, str):
    return False
  try:
    parsed = urlparse(url.strip())
  except ValueError:
    return False
  return (parsed.scheme == "https" and parsed.hostname in ALLOWED_HOSTS and parsed.path.startswith("/api/webhooks/") and
          len(parsed.path.split("/")) >= 5)


def reporting_enabled(params) -> bool:
  return owner_is_allowed(params) and params.get_bool(REPORT_KEY) and validate_webhook_url(_text(params, WEBHOOK_KEY))


def extract_voltage_mv(peripheral_state) -> int | None:
  if peripheral_state is None or str(getattr(peripheral_state, "pandaType", "unknown")).casefold().endswith("unknown"):
    return None
  try:
    voltage_mv = int(getattr(peripheral_state, "voltage", 0))
  except (TypeError, ValueError):
    return None
  return voltage_mv if MIN_VALID_VOLTAGE_MV <= voltage_mv <= MAX_VALID_VOLTAGE_MV else None


def cutoff_volts(params) -> float:
  return effective(read_saved(params)).cutoff_tenths / 10


def _format_voltage(voltage_mv: int | None) -> str:
  return "unavailable" if voltage_mv is None else f"{voltage_mv / 1000:.2f} V"


def build_discord_payload(summary: DriveVoltageSummary, *, threshold_v: float, drive_id: str, car_fingerprint: str = "") -> dict:
  below_threshold = summary.min_mv is not None and summary.min_mv < threshold_v * 1000
  lines = [
    "🔋 **StarPilot drive-end 12 V report**",
    f"Drive: `{drive_id or 'unknown'}`",
    f"Vehicle: `{car_fingerprint or 'unknown'}`",
    f"Latest: **{_format_voltage(summary.latest_mv)}**",
    f"Minimum: **{_format_voltage(summary.min_mv)}**",
    f"Maximum: **{_format_voltage(summary.max_mv)}**",
    f"Samples: {summary.samples}",
    f"Low-voltage cutoff: {threshold_v:.1f} V",
    f"Below cutoff: {'YES' if below_threshold else 'no'}",
    "Source: Panda/comma peripheral supply voltage",
  ]
  return {"content": "\n".join(lines)[:MAX_DISCORD_CONTENT_LENGTH], "allowed_mentions": {"parse": []}}


def make_pending_report(summary: DriveVoltageSummary, *, threshold_v: float, drive_id: str, car_fingerprint: str = "") -> dict[str, Any]:
  timestamp = datetime.datetime.now(datetime.UTC).isoformat()
  identifier_source = drive_id or f"{timestamp}|{summary.samples}|{summary.latest_mv}"
  return {
    "id": hashlib.sha256(identifier_source.encode()).hexdigest()[:24],
    "drive_id": drive_id,
    "created_at": timestamp,
    "threshold_v": float(threshold_v),
    "car_fingerprint": car_fingerprint,
    "summary": asdict(summary),
  }


def pending_queue(params) -> list[dict[str, Any]]:
  pending = params.get(PENDING_KEY)
  if isinstance(pending, dict):
    return [pending]
  if isinstance(pending, list):
    return [item for item in pending if isinstance(item, dict)]
  return []


def _save_queue(params, queue: list[dict[str, Any]]) -> None:
  if queue:
    params.put(PENDING_KEY, queue[-MAX_PENDING_REPORTS:], block=True)
  else:
    params.remove(PENDING_KEY)


def save_pending_report(params, pending: dict[str, Any]) -> None:
  queue = pending_queue(params)
  if not any(item.get("id") == pending.get("id") for item in queue):
    queue.append(pending)
  _save_queue(params, queue)


def send_discord_payload(params, payload: dict, *, post=None) -> str:
  """Post one message; returns "" on success or a short reason that never contains the webhook."""
  if not reporting_enabled(params):
    return "disabled"
  post = requests.post if post is None else post
  try:
    response = post(_text(params, WEBHOOK_KEY).strip(), json=payload, timeout=(3, 10), allow_redirects=False)
  except requests.RequestException:
    return "transport"
  try:
    return "" if response.status_code in (200, 204) else f"http {response.status_code}"
  finally:
    response.close()


def deliver_pending_report(params, *, post=None) -> str:
  queue = pending_queue(params)
  if not queue:
    return "no_pending"
  pending = queue[0]
  if not {"id", "drive_id", "threshold_v", "summary"} <= set(pending) or not isinstance(pending.get("summary"), dict):
    _save_queue(params, queue[1:])
    return "invalid_pending"
  if _text(params, LAST_DRIVE_KEY) == str(pending["id"]):
    _save_queue(params, queue[1:])
    return "duplicate"
  try:
    payload = build_discord_payload(DriveVoltageSummary(**pending["summary"]), threshold_v=float(pending["threshold_v"]),
                                    drive_id=str(pending["drive_id"]), car_fingerprint=str(pending.get("car_fingerprint") or ""))
  except (TypeError, ValueError):
    _save_queue(params, queue[1:])
    return "invalid_pending"
  result = send_discord_payload(params, payload, post=post)
  if not result:
    params.put(LAST_DRIVE_KEY, str(pending["id"]), block=True)
    _save_queue(params, queue[1:])
  return result


class DriveVoltageReporter:
  OFFROAD_DELAY_S = 5.0
  RETRY_S = 120.0

  def __init__(self, params, *, post=None):
    self.params = params
    self.post = post
    self.started = False
    self.summary = DriveVoltageSummary()
    self.last_stamp = None
    self.next_delivery = 0.0

  def sample(self, stamp: int, peripheral_state) -> None:
    if self.started and stamp != self.last_stamp:
      self.last_stamp = stamp
      self.summary.update(extract_voltage_mv(peripheral_state))

  def update_started(self, started: bool, now: float, *, car_fingerprint: str = "") -> dict[str, Any] | None:
    pending = None
    if started and not self.started:
      self.summary = DriveVoltageSummary()
    elif not started and self.started:
      if self.summary.samples > 0 and reporting_enabled(self.params):
        pending = make_pending_report(self.summary, threshold_v=cutoff_volts(self.params),
                                      drive_id=_text(self.params, "CurrentRoute").strip(), car_fingerprint=car_fingerprint)
        save_pending_report(self.params, pending)
      self.next_delivery = now + self.OFFROAD_DELAY_S
    self.started = started
    return pending

  def deliver_if_due(self, now: float, allowed) -> str | None:
    """Parked only, at most once per RETRY_S, so a failed or offline send is retried without hammering Discord."""
    if self.started or now < self.next_delivery or not allowed():
      return None
    self.next_delivery = now + self.RETRY_S
    if not pending_queue(self.params):
      return None
    return deliver_pending_report(self.params, post=self.post)


def webhook_status(params) -> dict[str, bool]:
  owner = owner_is_allowed(params)
  return {
    "owner": owner,
    "configured": owner and validate_webhook_url(_text(params, WEBHOOK_KEY)),
    "enabled": owner and params.get_bool(REPORT_KEY),
  }


def configure_webhook(params, webhook: object) -> bool:
  if not owner_is_allowed(params) or not validate_webhook_url(webhook):
    return False
  assert isinstance(webhook, str)
  params.put(WEBHOOK_KEY, webhook.strip(), block=True)
  params.put_bool(REPORT_KEY, True, block=True)
  return True


def remove_webhook(params) -> None:
  params.put_bool(REPORT_KEY, False, block=True)
  params.remove(WEBHOOK_KEY)
  params.remove(PENDING_KEY)
