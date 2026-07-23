from openpilot.selfdrive.ui.layouts.settings import device
from openpilot.system.ui.widgets import DialogResult


class FakeParams:
  def __init__(self):
    self.writes = []

  def put_bool(self, key, value):
    self.writes.append((key, value))

  def put_bool_nonblocking(self, *_args, **_kwargs):
    raise AssertionError("reboot command must be written synchronously")


def _device_layout():
  layout = device.DeviceLayout.__new__(device.DeviceLayout)
  layout._params = FakeParams()
  return layout


def test_confirmed_user_reboot_is_written_synchronously():
  layout = _device_layout()

  layout._perform_reboot(DialogResult.CONFIRM)

  assert layout._params.writes == [("DoUserReboot", True)]


def test_confirmed_user_reboot_is_allowed_onroad(monkeypatch):
  layout = _device_layout()

  monkeypatch.setattr(device.ui_state, "started", True)
  monkeypatch.setattr(device.ui_state, "ignition", True)
  layout._perform_reboot(DialogResult.CONFIRM)

  assert layout._params.writes == [("DoUserReboot", True)]


def test_cancelled_user_reboot_is_ignored():
  layout = _device_layout()

  layout._perform_reboot(DialogResult.CANCEL)

  assert layout._params.writes == []
