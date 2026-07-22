import pyray as rl
from cereal import log, custom
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.onroad.starpilot.widgets.base import LayoutWidget
from openpilot.selfdrive.ui.onroad.driver_state import DriverStateRenderer

AlertSize = log.SelfdriveState.AlertSize


class DriverMonitorWidget(LayoutWidget):
  def __init__(self, renderer: DriverStateRenderer):
    super().__init__("driver_monitor", priority=2)
    self._renderer = renderer
    self._child(self._renderer)
    self._renderer.auto_position = False

  @property
  def is_visible(self) -> bool:
    sm = ui_state.sm
    alert_ok = sm["selfdriveState"].alertSize == AlertSize.none
    if alert_ok:
      starpilot_ss = sm["starpilotSelfdriveState"] if sm.valid.get("starpilotSelfdriveState", False) else None
      if starpilot_ss:
        alert_ok = starpilot_ss.alertSize == custom.StarPilotSelfdriveState.AlertSize.none
    data_fresh = sm.recv_frame["driverStateV2"] > ui_state.started_frame
    not_hidden = not ui_state.starpilot_toggles.get("hide_dm_icon", False)
    return bool(alert_ok and data_fresh and not_hidden)

  def get_size(self) -> tuple[float, float]:
    return 192.0, 192.0

  def _render(self, rect: rl.Rectangle) -> None:
    self._renderer.position_x = rect.x + rect.width / 2
    self._renderer.position_y = rect.y + rect.height / 2
    self._renderer.render(rect)
