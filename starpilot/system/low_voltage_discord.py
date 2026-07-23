from __future__ import annotations

from dataclasses import asdict, dataclass
import datetime
import hashlib
import json
import subprocess
import time
from typing import Any, Callable
from urllib.parse import urlparse


OWNER_GITHUB_USERNAME = "jc01rho"
MIN_VALID_VOLTAGE_MV = 6000
MAX_VALID_VOLTAGE_MV = 18000
MAX_DISCORD_CONTENT_LENGTH = 2000


@dataclass
class DeliveryResult:
  ok: bool
  error: str = ""


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


class LowVoltageDriveReporter:
  def __init__(self, params):
    self.params = params
    self.started = False
    self.summary = DriveVoltageSummary()

  def sample(self, voltage_mv: int | None) -> None:
    if self.started:
      self.summary.update(voltage_mv)

  def update_started(self, started: bool, *, car_fingerprint: str = "") -> dict[str, Any] | None:
    pending = None
    if started and not self.started:
      self.summary = DriveVoltageSummary()
    elif not started and self.started and self.summary.samples > 0 and reporting_enabled(self.params):
      drive_id = _param_text(self.params, "CurrentRoute").strip() or datetime.datetime.now(datetime.timezone.utc).isoformat()
      pending = make_pending_report(self.summary, threshold_v=self.params.get_float("LowVoltageShutdown"),
                                    drive_id=drive_id, car_fingerprint=car_fingerprint)
      save_pending_report(self.params, pending)
    self.started = started
    return pending


def _param_text(params, key: str) -> str:
  value = params.get(key)
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="replace")
  return str(value or "")


def owner_is_allowed(params) -> bool:
  return _param_text(params, "GithubUsername").strip().casefold() == OWNER_GITHUB_USERNAME and bool(_param_text(params, "GithubSshKeys").strip())


def validate_webhook_url(url: str) -> bool:
  try:
    parsed = urlparse(str(url).strip())
  except Exception:
    return False
  allowed_hosts = {"discord.com", "discordapp.com", "ptb.discord.com", "canary.discord.com"}
  return parsed.scheme == "https" and parsed.hostname in allowed_hosts and parsed.path.startswith("/api/webhooks/") and len(parsed.path.split("/")) >= 5


def reporting_enabled(params) -> bool:
  return owner_is_allowed(params) and params.get_bool("LowVoltageDiscordReport") and validate_webhook_url(_param_text(params, "LowVoltageDiscordWebhook"))


def extract_voltage_mv(peripheral_state, *, alive: bool, valid: bool) -> int | None:
  if not alive or not valid or peripheral_state is None:
    return None
  panda_type = str(getattr(peripheral_state, "pandaType", "unknown")).casefold()
  if panda_type.endswith("unknown"):
    return None
  try:
    voltage_mv = int(getattr(peripheral_state, "voltage", 0))
  except (TypeError, ValueError):
    return None
  return voltage_mv if MIN_VALID_VOLTAGE_MV <= voltage_mv <= MAX_VALID_VOLTAGE_MV else None


def _format_voltage(voltage_mv: int | None) -> str:
  return "unavailable" if voltage_mv is None else f"{voltage_mv / 1000:.2f} V"


def build_discord_payload(summary: DriveVoltageSummary, *, threshold_v: float, drive_id: str, car_fingerprint: str = "") -> dict[str, str]:
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
  return {"content": "\n".join(lines)[:MAX_DISCORD_CONTENT_LENGTH]}


def make_pending_report(summary: DriveVoltageSummary, *, threshold_v: float, drive_id: str, car_fingerprint: str = "") -> dict[str, Any]:
  timestamp = datetime.datetime.now(datetime.timezone.utc).isoformat()
  identifier_source = drive_id or f"{timestamp}|{summary.samples}|{summary.latest_mv}"
  return {
    "id": hashlib.sha256(identifier_source.encode()).hexdigest()[:24],
    "drive_id": drive_id,
    "created_at": timestamp,
    "threshold_v": float(threshold_v),
    "car_fingerprint": car_fingerprint,
    "summary": asdict(summary),
  }


def _pending_queue_from_params(params) -> list[dict[str, Any]]:
  pending = params.get("LowVoltageDiscordPendingReport")
  if not pending:
    return []
  if isinstance(pending, bytes):
    pending = pending.decode("utf-8", errors="replace")
  if isinstance(pending, str):
    try:
      pending = json.loads(pending)
    except json.JSONDecodeError:
      return [{}]
  if isinstance(pending, dict):
    return [pending]
  if isinstance(pending, list):
    return [item for item in pending if isinstance(item, dict)]
  return [{}]


def send_discord_payload(params, payload: dict[str, str], *, run: Callable = subprocess.run) -> DeliveryResult:
  if not reporting_enabled(params):
    return DeliveryResult(False, "disabled")
  webhook = _param_text(params, "LowVoltageDiscordWebhook").strip()
  command = [
    "curl", "--fail-with-body", "--silent", "--show-error",
    "--connect-timeout", "5", "--max-time", "15", "--retry", "2", "--retry-delay", "2",
    "--config", "-",
  ]
  def curl_config_quote(value: str) -> str:
    return value.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\r", "\\r")

  body = json.dumps(payload, separators=(",", ":"))
  curl_config = "\n".join((
    f'url = "{curl_config_quote(webhook)}"',
    'header = "Content-Type: application/json"',
    f'data = "{curl_config_quote(body)}"',
  ))
  try:
    completed = run(command, input=curl_config, capture_output=True, text=True,
                    check=False, shell=False, timeout=20)
  except subprocess.TimeoutExpired:
    return DeliveryResult(False, "timeout")
  except (OSError, subprocess.SubprocessError):
    return DeliveryResult(False, "transport")
  return DeliveryResult(completed.returncode == 0, "" if completed.returncode == 0 else "http")


def deliver_pending_report(params, *, run: Callable = subprocess.run) -> DeliveryResult:
  queue = _pending_queue_from_params(params)
  if not queue:
    return DeliveryResult(False, "no_pending")
  pending = queue[0]
  required = {"id", "drive_id", "threshold_v", "summary"}
  if not required.issubset(pending) or not isinstance(pending.get("summary"), dict):
    _save_pending_queue(params, queue[1:])
    return DeliveryResult(False, "invalid_pending")
  if _param_text(params, "LowVoltageDiscordLastDrive") == str(pending["id"]):
    _save_pending_queue(params, queue[1:])
    return DeliveryResult(False, "duplicate")
  try:
    summary = DriveVoltageSummary(**pending["summary"])
    payload = build_discord_payload(summary, threshold_v=float(pending["threshold_v"]), drive_id=str(pending["drive_id"]),
                                    car_fingerprint=str(pending.get("car_fingerprint") or ""))
  except (TypeError, ValueError):
    _save_pending_queue(params, queue[1:])
    return DeliveryResult(False, "invalid_pending")

  result = send_discord_payload(params, payload, run=run)
  if result.ok:
    params.put("LowVoltageDiscordLastDrive", str(pending["id"]))
    _save_pending_queue(params, queue[1:])
  return result


def deliver_after_offroad_delay(params, *, delay_s: float = 5.0, sleep: Callable = time.sleep,
                                run: Callable = subprocess.run) -> DeliveryResult:
  sleep(delay_s)
  if params.get_bool("IsOnroad"):
    return DeliveryResult(False, "onroad")
  return deliver_pending_report(params, run=run)


def _save_pending_queue(params, queue: list[dict[str, Any]]) -> None:
  if queue:
    params.put("LowVoltageDiscordPendingReport", queue)
  else:
    params.remove("LowVoltageDiscordPendingReport")


def save_pending_report(params, pending: dict[str, Any]) -> None:
  queue = _pending_queue_from_params(params)
  if not any(item.get("id") == pending.get("id") for item in queue):
    queue.append(pending)
  _save_pending_queue(params, queue)


def webhook_status(params) -> dict[str, bool]:
  return {
    "owner": owner_is_allowed(params),
    "configured": validate_webhook_url(_param_text(params, "LowVoltageDiscordWebhook")),
    "enabled": params.get_bool("LowVoltageDiscordReport"),
  }


def configure_webhook(params, webhook: str) -> bool:
  webhook = str(webhook or "").strip()
  if not owner_is_allowed(params) or not validate_webhook_url(webhook):
    return False
  params.put("LowVoltageDiscordWebhook", webhook)
  return True


def remove_webhook(params) -> None:
  params.put_bool("LowVoltageDiscordReport", False)
  params.remove("LowVoltageDiscordWebhook")
  params.remove("LowVoltageDiscordPendingReport")
