from types import SimpleNamespace

import pytest

from cereal import car
from openpilot.system.manager.process_config import allow_uploads, camera_run, managed_processes, sentry_mode


class FakeParams:
  def __init__(self, always_allow_uploads: bool = False):
    self.always_allow_uploads = always_allow_uploads

  def get_bool(self, key: str) -> bool:
    assert key == "AlwaysAllowUploads"
    return self.always_allow_uploads


@pytest.mark.parametrize(
  "started,no_uploads,no_onroad_uploads,always_allow_uploads,expected",
  [
    (True, False, False, False, True),
    (False, False, False, False, True),
    (True, True, False, False, False),
    (False, True, False, False, False),
    (True, True, True, False, False),
    (False, True, True, False, True),
    (True, True, False, True, True),
  ],
)
def test_allow_uploads(started, no_uploads, no_onroad_uploads, always_allow_uploads, expected):
  params = FakeParams(always_allow_uploads)
  toggles = SimpleNamespace(no_uploads=no_uploads, no_onroad_uploads=no_onroad_uploads)

  assert allow_uploads(started, params, car.CarParams.new_message(), toggles) is expected


def test_uploader_runs_at_background_priority():
  assert managed_processes["uploader"].nice == 19


class CameraParams:
  def __init__(self, capture: bool):
    self.capture = capture

  def get_bool(self, key: str) -> bool:
    assert key in {"IsDriverViewEnabled", "SentryModeCapture"}
    return self.capture if key == "SentryModeCapture" else False


@pytest.mark.parametrize(
  "started,capture,expected",
  [
    (False, True, True),
    (False, False, False),
    (True, False, True),
  ],
)
def test_camera_run_preserves_onroad_camera_and_offroad_sentry_capture(started, capture, expected):
  assert camera_run(started, CameraParams(capture), car.CarParams.new_message(), SimpleNamespace()) is expected


class SentryParams:
  def __init__(self, enabled: bool):
    self.enabled = enabled

  def get_bool(self, key: str) -> bool:
    assert key == "SentryModeEnabled"
    return self.enabled


@pytest.mark.parametrize("started,enabled,expected", [(True, True, False), (False, True, True), (False, False, False)])
def test_sentry_process_is_offroad_only(started, enabled, expected):
  assert sentry_mode(started, SentryParams(enabled), car.CarParams.new_message(), SimpleNamespace()) is expected
