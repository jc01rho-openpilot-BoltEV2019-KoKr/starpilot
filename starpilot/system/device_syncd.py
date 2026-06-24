#!/usr/bin/env python3
import requests
import time

from pathlib import Path

from cereal import messaging

from openpilot.common.params import Params, ParamKeyFlag, ParamKeyType
from openpilot.common.realtime import Ratekeeper
from openpilot.common.time_helpers import system_time_valid

from openpilot.starpilot.common.starpilot_utilities import get_starpilot_api_info, is_url_pingable
from openpilot.starpilot.common.starpilot_variables import EXCLUDED_KEYS, STARPILOT_API, update_starpilot_toggles

GALAXY_PRESENCE_INTERVAL_ACTIVE = 60
GALAXY_PRESENCE_INTERVAL_IDLE = 240
GALAXY_PAIRED_PARAM = "GalaxyPaired"
GALAXY_UPLOAD_PENDING_PARAM = "GalaxyUploadPending"
LEGACY_GALAXY_PREFIX = "".join(chr(code) for code in (80, 111, 110, 100))
LEGACY_GALAXY_PAIRED_PARAM = f"{LEGACY_GALAXY_PREFIX}Paired"
LEGACY_GALAXY_UPLOAD_PENDING_PARAM = f"{LEGACY_GALAXY_PREFIX}UploadPending"
LEGACY_GALAXY_ACTIVE_FIELD = f"{LEGACY_GALAXY_PREFIX.lower()}_active"
REMOTE_SYNC_SCOPES = ("galaxy", LEGACY_GALAXY_PREFIX.lower())

REMOTE_TOGGLE_CHECK_INTERVAL_ACTIVE = 10
REMOTE_TOGGLE_CHECK_INTERVAL_IDLE = 60


def _legacy_bool(params, key):
  try:
    return Path(params.get_param_path(key)).read_text(encoding="utf-8").strip() == "1"
  except Exception:
    return False


def _clear_legacy_param(params, key):
  try:
    Path(params.get_param_path(key)).unlink()
  except FileNotFoundError:
    pass
  except Exception:
    pass


def _get_migrated_bool(params, key, legacy_key):
  if params.get_bool(key):
    return True
  if _legacy_bool(params, legacy_key):
    params.put_bool(key, True)
    return True
  return False


def _put_migrated_bool(params, key, legacy_key, value):
  params.put_bool(key, value)
  if not value:
    _clear_legacy_param(params, legacy_key)


def _remote_request(method, path, **kwargs):
  response = None
  for scope in REMOTE_SYNC_SCOPES:
    response = requests.request(method, f"{STARPILOT_API}/{scope}/{path}", **kwargs)
    if response.status_code != 404:
      return response
  return response


def check_toggles(started, params, sm=None, boot_run=False):
  if not _get_migrated_bool(params, GALAXY_PAIRED_PARAM, LEGACY_GALAXY_PAIRED_PARAM):
    return None

  if not is_url_pingable(STARPILOT_API):
    return None

  if not boot_run:
    if started and not sm["starpilotCarState"].isParked:
      return None
    if sm["deviceState"].screenBrightnessPercent == 0:
      return None

  try:
    api_token, _, device_type, dongle_id = get_starpilot_api_info()
    if not dongle_id or not api_token:
      return None

    response = _remote_request(
      "GET",
      "toggles/pending",
      params={"dongle_id": dongle_id, "api_token": api_token},
      headers={"Content-Type": "application/json", "User-Agent": "starpilot-api/1.0"},
      timeout=10,
    )
    response.raise_for_status()

    data = response.json()
    galaxy_active = data.get("galaxy_active") is True or data.get(LEGACY_GALAXY_ACTIVE_FIELD) is True

    if data.get("paired") is False:
      _put_migrated_bool(params, GALAXY_PAIRED_PARAM, LEGACY_GALAXY_PAIRED_PARAM, False)
      print("Device was unpaired remotely")
      return False

    toggles = data.get("toggles")
    if not toggles:
      return galaxy_active

    for key, value in toggles.items():
      if key in EXCLUDED_KEYS:
        continue
      try:
        params.check_key(key)
      except Exception:
        print(f"Skipping unknown param key: {key}")
        continue

      if value is None:
        continue

      try:
        casted_value = params.cpp2python(key, value.encode("utf-8") if isinstance(value, str) else value)
        if casted_value is not None:
          params.put(key, casted_value)
      except Exception as exception:
        print(f"Skipping remote toggle {key}: {exception}")
        continue

    update_starpilot_toggles()

    _remote_request(
      "POST",
      "toggles/ack",
      json={
        "api_token": api_token,
        "device": device_type,
        "starpilot_dongle_id": dongle_id,
      },
      headers={"Content-Type": "application/json", "User-Agent": "starpilot-api/1.0"},
      timeout=10,
    ).raise_for_status()

    print(f"Successfully applied {len(toggles)} remote toggles")
    return galaxy_active

  except Exception as e:
    print(f"Failed to check remote toggles: {e}")
    return None


def ping_galaxy_presence(interval, parked, started, state_changed):
  last_ping = getattr(ping_galaxy_presence, "_last_ping", 0.0)
  now = time.monotonic()
  if not state_changed and (now - last_ping) < interval:
    return

  try:
    api_token, build_metadata, device_type, dongle_id = get_starpilot_api_info()
    if not dongle_id or not api_token:
      return

    payload = {
      "api_token": api_token,
      "build_metadata": build_metadata,
      "device": device_type,
      "dongle_id": dongle_id,
      "starpilot_dongle_id": dongle_id,
      "is_onroad": bool(started),
      "is_parked": bool(parked),
    }

    response = _remote_request(
      "POST",
      "presence/device",
      json=payload,
      headers={"Content-Type": "application/json", "User-Agent": "starpilot-api/1.0"},
      timeout=10,
    )
    response.raise_for_status()
    ping_galaxy_presence._last_ping = now

  except Exception as e:
    print(f"Failed to update Galaxy presence: {e}")


def upload_toggles(params):
  if not is_url_pingable(STARPILOT_API):
    return False

  try:
    api_token, build_metadata, device_type, dongle_id = get_starpilot_api_info()
    if not dongle_id or not api_token:
      return False

    toggles = {}
    for key in params.all_keys():
      key_str = key.decode("utf-8") if isinstance(key, bytes) else str(key)
      if key_str in EXCLUDED_KEYS:
        continue
      if params.get_key_flag(key) & ParamKeyFlag.DONT_LOG:
        continue

      value = params.get(key)
      if value is None:
        continue

      key_type = params.get_type(key)
      if key_type == ParamKeyType.BYTES:
        value = value.decode("utf-8", "replace")
      elif key_type == ParamKeyType.TIME:
        value = value.isoformat()
      toggles[key_str] = value

    payload = {
      "api_token": api_token,
      "build_metadata": build_metadata,
      "device": device_type,
      "dongle_id": dongle_id,
      "starpilot_dongle_id": dongle_id,
      "toggles": toggles,
    }

    response = _remote_request(
      "POST",
      "toggles/sync",
      json=payload,
      headers={"Content-Type": "application/json", "User-Agent": "starpilot-api/1.0"},
      timeout=10,
    )
    response.raise_for_status()

    print("Successfully uploaded toggles to StarPilot.com")
    return True

  except Exception as e:
    print(f"Failed to upload toggles: {e}")
    return False


def galaxy_thread():
  rate_keeper = Ratekeeper(1, None)

  sm = messaging.SubMaster(["deviceState", "starpilotCarState"])

  params = Params(return_defaults=True)

  boot_sync_complete = False
  galaxy_active = False
  previous_parked = False
  previous_started = False

  next_toggle_check_at = 0.0

  while True:
    sm.update(0)

    parked = sm["starpilotCarState"].isParked
    started = sm["deviceState"].started
    long_maneuver_mode = params.get_bool("LongitudinalManeuverMode")
    lateral_maneuver_mode = params.get_bool("LateralManeuverMode")
    maneuver_mode_active = long_maneuver_mode or lateral_maneuver_mode
    state_changed = started != previous_started or parked != previous_parked

    if _get_migrated_bool(params, GALAXY_PAIRED_PARAM, LEGACY_GALAXY_PAIRED_PARAM) and not maneuver_mode_active:
      presence_interval = GALAXY_PRESENCE_INTERVAL_ACTIVE if started or galaxy_active else GALAXY_PRESENCE_INTERVAL_IDLE
      ping_galaxy_presence(presence_interval, parked, started, state_changed)

    if not boot_sync_complete and system_time_valid():
      boot_galaxy_active = check_toggles(False, params, boot_run=True)
      if boot_galaxy_active is not None:
        galaxy_active = boot_galaxy_active
      boot_sync_complete = True

    now = time.monotonic()
    if state_changed and parked:
      next_toggle_check_at = 0.0

    if maneuver_mode_active:
      next_toggle_check_at = max(next_toggle_check_at, now + REMOTE_TOGGLE_CHECK_INTERVAL_IDLE)
    elif boot_sync_complete and now >= next_toggle_check_at:
      latest_galaxy_active = check_toggles(started, params, sm)
      if latest_galaxy_active is not None:
        galaxy_active = latest_galaxy_active
      next_toggle_check_at = now + REMOTE_TOGGLE_CHECK_INTERVAL_ACTIVE if galaxy_active else REMOTE_TOGGLE_CHECK_INTERVAL_IDLE

    if _get_migrated_bool(params, GALAXY_UPLOAD_PENDING_PARAM, LEGACY_GALAXY_UPLOAD_PENDING_PARAM) and not maneuver_mode_active:
      if not _get_migrated_bool(params, GALAXY_PAIRED_PARAM, LEGACY_GALAXY_PAIRED_PARAM):
        _put_migrated_bool(params, GALAXY_UPLOAD_PENDING_PARAM, LEGACY_GALAXY_UPLOAD_PENDING_PARAM, False)
      elif upload_toggles(params):
        _put_migrated_bool(params, GALAXY_UPLOAD_PENDING_PARAM, LEGACY_GALAXY_UPLOAD_PENDING_PARAM, False)

    previous_parked = parked
    previous_started = started

    rate_keeper.keep_time()


def main():
  galaxy_thread()


if __name__ == "__main__":
  main()
