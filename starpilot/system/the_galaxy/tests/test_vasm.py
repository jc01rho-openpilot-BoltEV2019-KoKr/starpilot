import importlib.util
import sys
import threading

from pathlib import Path
from types import ModuleType, SimpleNamespace

import pytest


TEST_DIR = Path(__file__).resolve().parent
MODULE_DIR = TEST_DIR.parent

smbus2_module = ModuleType("smbus2")
setattr(smbus2_module, "SMBus", object)
sys.modules.setdefault("smbus2", smbus2_module)

from openpilot.starpilot.system.the_galaxy.tests.test_dashboard_stats import _install_server_import_stubs  # noqa: E402


_install_server_import_stubs()
msgq_module = ModuleType("msgq")
visionipc_module = ModuleType("msgq.visionipc")
setattr(visionipc_module, "VisionIpcClient", lambda *args, **kwargs: None)
setattr(visionipc_module, "VisionStreamType", SimpleNamespace(VISION_STREAM_DRIVER=0))
setattr(msgq_module, "visionipc", visionipc_module)
sys.modules["msgq"] = msgq_module
sys.modules["msgq.visionipc"] = visionipc_module
pil_module = ModuleType("PIL")
setattr(pil_module, "Image", SimpleNamespace(fromarray=lambda value: value))
sys.modules.setdefault("PIL", pil_module)

spec = importlib.util.spec_from_file_location("vasm_server", MODULE_DIR / "the_galaxy.py")
assert spec is not None and spec.loader is not None
the_galaxy = importlib.util.module_from_spec(spec)
spec.loader.exec_module(the_galaxy)

_decode_json_object = the_galaxy._decode_json_object
_normalize_vasm_config = the_galaxy._normalize_vasm_config


class FakeParams:
  def __init__(self, is_onroad):
    self.is_onroad = is_onroad

  def get_bool(self, key):
    return self.is_onroad if key == "IsOnroad" else False


def _snapshot_client(monkeypatch, is_onroad, capture):
  monkeypatch.setattr(the_galaxy, "params", FakeParams(is_onroad))
  assert the_galaxy._import_galaxy_web_symbols()
  app = the_galaxy.Flask("vasm_snapshot_test")
  the_galaxy.setup(app)

  view = app.view_functions["v_asm_snapshot"]
  closure = dict(zip(view.__code__.co_freevars, view.__closure__, strict=True))
  closure["_get_live_driver_jpeg"].cell_contents = capture
  return app


def test_normalize_vasm_config_accepts_bounded_polygons():
  config = _normalize_vasm_config({
    "width": 1920,
    "height": 1080,
    "poly_left": [[1.2, 2.7], [100, 3], [90, 200]],
    "poly_right": [],
  })

  assert config == {
    "width": 1920,
    "height": 1080,
    "poly_left": [[1, 3], [100, 3], [90, 200]],
    "poly_right": [],
  }


@pytest.mark.parametrize("config", (
  {},
  {"width": 1920, "height": 1080, "poly_left": [], "poly_right": []},
  {"width": 1920, "height": 1080, "poly_left": [[-1, 1], [2, 2], [3, 3]], "poly_right": []},
  {"width": 1920, "height": 1080, "poly_left": [[1, 1], [2, 2]], "poly_right": []},
))
def test_normalize_vasm_config_rejects_unsafe_config(config):
  with pytest.raises(ValueError):
    _normalize_vasm_config(config)


@pytest.mark.parametrize("raw", (
  '{"width":1928,"height":1208,"poly_left":[],"poly_right":[]}',
  b'{"width":1928,"height":1208,"poly_left":[],"poly_right":[]}',
))
def test_decode_vasm_config_from_legacy_params_payload(raw):
  assert _decode_json_object(raw) == {
    "width": 1928,
    "height": 1208,
    "poly_left": [],
    "poly_right": [],
  }


@pytest.mark.parametrize("raw", (None, "", "invalid", [], 1))
def test_decode_vasm_config_rejects_non_objects(raw):
  assert _decode_json_object(raw) == {}


def test_snapshot_rejects_capture_when_onroad(monkeypatch):
  capture_called = False

  def capture():
    nonlocal capture_called
    capture_called = True
    return b"jpeg"

  app = _snapshot_client(monkeypatch, True, capture)

  response = app.test_client().get("/api/v_asm/snapshot")

  assert response.status_code == 409
  assert not capture_called


def test_snapshot_returns_jpeg_when_offroad(monkeypatch):
  jpeg = b"\xff\xd8\xff\xe0test-jpeg"
  app = _snapshot_client(monkeypatch, False, lambda: jpeg)

  response = app.test_client().get("/api/v_asm/snapshot")

  assert response.status_code == 200
  assert response.content_type == "image/jpeg"
  assert response.data == jpeg


def test_snapshot_returns_service_unavailable_when_capture_fails(monkeypatch):
  app = _snapshot_client(monkeypatch, False, lambda: None)

  response = app.test_client().get("/api/v_asm/snapshot")

  assert response.status_code == 503


def test_snapshot_rejects_overlapping_capture(monkeypatch):
  first_capture_started = threading.Event()
  release_first_capture = threading.Event()
  capture_lock = threading.Lock()
  capture_calls = 0

  def capture():
    nonlocal capture_calls
    with capture_lock:
      capture_calls += 1
      call_number = capture_calls
    if call_number == 1:
      first_capture_started.set()
      assert release_first_capture.wait(timeout=2.0)
    return b"jpeg"

  app = _snapshot_client(monkeypatch, False, capture)
  responses = {}

  def request_snapshot(name):
    responses[name] = app.test_client().get("/api/v_asm/snapshot")

  first_request = threading.Thread(target=request_snapshot, args=("first",))
  second_request = threading.Thread(target=request_snapshot, args=("second",))
  first_request.start()
  assert first_capture_started.wait(timeout=2.0)
  second_request.start()
  second_request.join(timeout=2.0)
  release_first_capture.set()
  first_request.join(timeout=2.0)

  assert not first_request.is_alive()
  assert not second_request.is_alive()
  assert responses["first"].status_code == 200
  assert responses["second"].status_code == 429
  assert capture_calls == 1
