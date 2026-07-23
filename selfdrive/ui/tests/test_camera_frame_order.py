import pytest

from openpilot.selfdrive.ui.mici.onroad import cameraview as mici_cameraview
from openpilot.selfdrive.ui.onroad import cameraview as big_cameraview


class FakeFrame:
  def __init__(self, frame_id: int, idx: int):
    self.frame_id = frame_id
    self.idx = idx


def _camera_view(cameraview):
  view = cameraview.CameraView.__new__(cameraview.CameraView)
  view._name = "camerad"
  view.frame = None
  view._last_frame_id = -1
  view._regressive_frame_count = 0
  view._texture_needs_update = False
  view._closed = True
  return view


@pytest.mark.parametrize("cameraview", [big_cameraview, mici_cameraview])
def test_reused_egl_slot_cannot_move_camera_backwards(monkeypatch, cameraview):
  monkeypatch.setattr(cameraview.cloudlog, "warning", lambda *_args, **_kwargs: None)
  view = _camera_view(cameraview)

  displayed = FakeFrame(frame_id=10, idx=0)
  assert view._accept_frame(displayed, packet_frame_id=10)

  # camerad cycles back to this shared slot while it remains displayed.
  displayed.frame_id = 30
  view._observe_displayed_frame()

  delayed = FakeFrame(frame_id=20, idx=1)
  assert not view._accept_frame(delayed, packet_frame_id=20)
  assert view.frame is displayed
  assert view._last_frame_id == 30
  assert view._regressive_frame_count == 1


@pytest.mark.parametrize("cameraview", [big_cameraview, mici_cameraview])
def test_newer_camera_frame_is_accepted(cameraview):
  view = _camera_view(cameraview)
  view._last_frame_id = 30
  newer = FakeFrame(frame_id=31, idx=2)

  assert view._accept_frame(newer, packet_frame_id=31)
  assert view.frame is newer
  assert view._last_frame_id == 31
  assert view._texture_needs_update
