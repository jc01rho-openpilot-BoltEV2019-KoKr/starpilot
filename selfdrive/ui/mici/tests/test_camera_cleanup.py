import gc
from types import SimpleNamespace
import weakref

import pytest

from openpilot.selfdrive.ui.mici.onroad import cameraview as mici_cameraview
from openpilot.selfdrive.ui.onroad import cameraview as big_cameraview


@pytest.mark.parametrize("module", (mici_cameraview, big_cameraview))
def test_road_transition_releases_camera_buffers(monkeypatch, module):
  class FakeClient:
    pass

  view = module.CameraView.__new__(module.CameraView)
  old_client = FakeClient()
  old_client_ref = weakref.ref(old_client)
  view._name = "camerad"
  view._stream_type = object()
  view.client = old_client
  view.frame = None
  view.available_streams = [object()]
  view._target_client = FakeClient()
  view._target_stream_type = object()
  view._switching = True
  view._texture_needs_update = False
  view.last_connection_attempt = 123.0
  view._closed = True
  cleared = []
  view._clear_textures = lambda: cleared.append(True)

  monkeypatch.setattr(module, "VisionIpcClient", lambda *_args, **_kwargs: FakeClient())
  del old_client

  view._offroad_transition()
  gc.collect()

  assert old_client_ref() is None
  assert cleared == [True]
  assert view.frame is None
  assert view.available_streams == []
  assert view._target_client is None
  assert view._target_stream_type is None
  assert view._switching is False
  assert view._texture_needs_update
  assert view.last_connection_attempt == 0.0


@pytest.mark.parametrize("module", (mici_cameraview, big_cameraview))
def test_transition_callback_does_not_retain_camera_view(monkeypatch, module):
  class FakeClient:
    pass

  callbacks = []
  monkeypatch.setattr(module, "TICI", False)
  monkeypatch.setattr(module, "VisionIpcClient", lambda *_args, **_kwargs: FakeClient())
  monkeypatch.setattr(module.rl, "load_shader_from_memory", lambda *_args: SimpleNamespace(id=1))
  monkeypatch.setattr(module.rl, "get_shader_location", lambda *_args: 0)
  monkeypatch.setattr(module.rl, "unload_shader", lambda *_args: None)
  monkeypatch.setattr(module.ui_state, "add_offroad_transition_callback", callbacks.append)
  monkeypatch.setattr(module.ui_state, "remove_offroad_transition_callback", callbacks.remove)

  view = module.CameraView("camerad", object())
  view_ref = weakref.ref(view)
  assert len(callbacks) == 1

  del view
  gc.collect()

  assert view_ref() is None
  assert callbacks == []


@pytest.mark.parametrize("module", (mici_cameraview, big_cameraview))
def test_stream_switch_releases_graphics_before_old_client(module):
  events = []

  class FakeClient:
    pass

  view = module.CameraView.__new__(module.CameraView)
  view.client = FakeClient()
  old_client_finalizer = weakref.finalize(view.client, events.append, "client")
  view._target_client = FakeClient()
  view._target_stream_type = object()
  view._stream_type = object()
  view._switching = True
  view._texture_needs_update = False
  view._closed = True
  view._clear_textures = lambda: events.append("graphics")
  view._initialize_textures = lambda: events.append("initialize")

  view._complete_switch()
  gc.collect()

  assert old_client_finalizer.alive is False
  assert events == ["graphics", "client", "initialize"]


@pytest.mark.parametrize("module", (mici_cameraview, big_cameraview))
def test_egl_cleanup_deletes_texture_before_images(monkeypatch, module):
  events = []
  view = module.CameraView.__new__(module.CameraView)
  view.texture_y = None
  view.texture_uv = None
  view.egl_texture = SimpleNamespace(id=7)
  view.egl_images = {0: object(), 1: object()}
  view._closed = True

  if module is mici_cameraview:
    view._use_egl = True
  else:
    monkeypatch.setattr(module, "TICI", True)

  monkeypatch.setattr(module.rl, "unload_texture", lambda _texture: events.append("texture"))
  monkeypatch.setattr(module, "destroy_egl_image", lambda _image: events.append("image"))

  view._clear_textures()

  assert events == ["texture", "image", "image"]
  assert view.egl_texture is None
  assert view.egl_images == {}
