import pyray as rl
from openpilot.selfdrive.ui.onroad.starpilot.widgets.base import LayoutWidget
from openpilot.selfdrive.ui.onroad.exp_button import ExpButton

class SteeringWheelWidget(LayoutWidget):
  def __init__(self, exp_button: ExpButton):
    super().__init__("steering_wheel", priority=1)
    self._button = exp_button
    self._child(self._button)

  @property
  def is_visible(self) -> bool:
    return bool(self._button.is_visible)

  def get_size(self) -> tuple[float, float]:
    return 192.0, 192.0

  def _render(self, rect: rl.Rectangle) -> None:
    self._button.render(rect)
