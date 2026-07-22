import math
import pyray as rl
from cereal import log, custom
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.selfdrive.ui import UI_BORDER_SIZE
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.widgets import Widget

AlertSize = log.SelfdriveState.AlertSize

BTN_SIZE = 192
DMOJI_SIZE = 128
CONE_SIZE = round(52 / 60 * DMOJI_SIZE)

CONE_COLOR_GREEN = (0, 255, 64)
CONE_COLOR_ORANGE = (255, 115, 0)
AWARENESS_UNFULL_PERCENT = 95


class DriverStateRenderer(Widget):
  def __init__(self):
    super().__init__()
    self.position_x: float = 0.0
    self.position_y: float = 0.0
    self.x_shift: float = 0.0
    self.auto_position = True
    self.is_active = False
    self.is_rhd = False
    self.is_face_detected = False
    self._awareness_unfull = False

    self._fade_filter = FirstOrderFilter(0.0, 0.05, 1 / gui_app.target_fps)
    self._color_fade_filter = FirstOrderFilter(1.0, 0.05, 1 / gui_app.target_fps)
    self._pitch_filter = FirstOrderFilter(0.0, 0.05, 1 / gui_app.target_fps, initialized=False)
    self._yaw_filter = FirstOrderFilter(0.0, 0.05, 1 / gui_app.target_fps, initialized=False)
    self._rotation_filter = FirstOrderFilter(0.0, 0.1, 1 / gui_app.target_fps, initialized=False)

    self._dm_background = gui_app.texture("icons_mici/onroad/driver_monitoring/dm_background.png", DMOJI_SIZE, DMOJI_SIZE)
    self._dm_person = gui_app.texture("icons_mici/onroad/driver_monitoring/dm_person.png", CONE_SIZE, CONE_SIZE)
    self._dm_cone = gui_app.texture("icons_mici/onroad/driver_monitoring/dm_cone.png", CONE_SIZE, CONE_SIZE)

  def _render(self, rect):
    bg = self._dm_background
    rl.draw_texture_ex(bg,
                       rl.Vector2(self.position_x - bg.width / 2,
                                  self.position_y - bg.height / 2),
                       0.0, 1.0,
                       rl.Color(255, 255, 255, int(255 * self._fade_filter.x)))

    person = self._dm_person
    rl.draw_texture_ex(person,
                       rl.Vector2(self.position_x - person.width / 2,
                                  self.position_y - person.height / 2),
                       0.0, 1.0,
                       rl.Color(255, 255, 255, int(255 * 0.9 * self._fade_filter.x)))

    green_amount = self._color_fade_filter.update(0.0 if self._awareness_unfull else 1.0)
    if self.is_active:
      cone = self._dm_cone
      source_rect = rl.Rectangle(0, 0, cone.width, cone.height)
      dest_rect = rl.Rectangle(
        self.position_x,
        self.position_y,
        cone.width,
        cone.height,
      )
      r = int(round(CONE_COLOR_GREEN[0] * green_amount + CONE_COLOR_ORANGE[0] * (1 - green_amount)))
      g = int(round(CONE_COLOR_GREEN[1] * green_amount + CONE_COLOR_ORANGE[1] * (1 - green_amount)))
      b = int(round(CONE_COLOR_GREEN[2] * green_amount + CONE_COLOR_ORANGE[2] * (1 - green_amount)))
      rl.draw_texture_pro(
        cone,
        source_rect,
        dest_rect,
        rl.Vector2(dest_rect.width / 2, dest_rect.height / 2),
        self._rotation_filter.x - 90,
        rl.Color(r, g, b, int(255 * self._fade_filter.x)),
      )

  def _update_state(self):
    sm = ui_state.sm
    dm_state = sm["driverMonitoringState"]
    self.is_active = dm_state.activePolicy == log.DriverMonitoringState.MonitoringPolicy.vision
    self.is_rhd = dm_state.isRHD
    self.is_face_detected = dm_state.visionPolicyState.faceDetected
    self._awareness_unfull = self.is_active and dm_state.visionPolicyState.awarenessPercent < AWARENESS_UNFULL_PERCENT
    face_pitch = dm_state.visionPolicyState.pose.pitch + math.radians(6)
    face_yaw = -dm_state.visionPolicyState.pose.yaw

    pitch = self._pitch_filter.update(face_pitch)
    yaw = self._yaw_filter.update(face_yaw)

    rotation = math.degrees(math.atan2(pitch * 2, yaw))
    angle_diff = rotation - self._rotation_filter.x
    angle_diff = ((angle_diff + 180) % 360) - 180
    self._rotation_filter.update(self._rotation_filter.x + angle_diff)

    alert_ok = sm["selfdriveState"].alertSize == AlertSize.none
    if alert_ok:
      starpilot_ss = sm["starpilotSelfdriveState"]
      alert_ok = starpilot_ss.alertSize == custom.StarPilotSelfdriveState.AlertSize.none
    data_fresh = sm.recv_frame["driverStateV2"] > ui_state.started_frame
    not_hidden = not ui_state.starpilot_toggles.get("hide_dm_icon", False)
    should_draw = alert_ok and data_fresh and not_hidden

    if not should_draw:
      self._fade_filter.update(0.0)
    elif not self.is_active:
      self._fade_filter.update(0.35)
    else:
      self._fade_filter.update(1.0)

    self._pre_calculate_position()

  def _pre_calculate_position(self):
    if not self.auto_position:
      return
    width, height = self._rect.width, self._rect.height
    offset = UI_BORDER_SIZE + BTN_SIZE // 2 + 20
    self.position_x = self._rect.x + (width - offset if self.is_rhd else offset) + self.x_shift
    self.position_y = self._rect.y + height - offset
