import sys
from types import ModuleType, SimpleNamespace
from unittest.mock import MagicMock
import pytest

# Stub native cereal / msgq / visionipc / jwt / usb1 / panda / transformations / acados before importing MICI module
def _stub(name, **attrs):
    m = MagicMock()
    for k, v in attrs.items():
        setattr(m, k, v)
    sys.modules[name] = m

_stub("jwt")
_stub("usb1")
_stub("panda")
_stub("opendbc.car.car_helpers", interfaces={})
_stub("openpilot.common.transformations.transformations")
_stub("openpilot.common.transformations.orientation", rot_from_euler=lambda *a: None, euler_from_rot=lambda *a: None)
_stub("openpilot.selfdrive.controls.lib.longitudinal_mpc_lib.c_generated_code.acados_ocp_solver_pyx")
_stub("openpilot.starpilot.common.accel_profile")
_stub("msgq")
_stub("msgq.visionipc", VisionStreamType=SimpleNamespace(VISION_STREAM_ROAD=0, VISION_STREAM_WIDE_ROAD=1, VISION_STREAM_DRIVER=2))
_stub("cereal")
_stub("cereal.messaging")
_stub("cereal.car")
_stub("cereal.log", LiveCalibrationData=SimpleNamespace(Status=SimpleNamespace(calibrated=0)), SelfdriveState=SimpleNamespace(OpenpilotState=0))
_stub("openpilot.selfdrive.ui.mici.onroad.cameraview", CameraView=object)

import pyray as rl
from openpilot.system.ui.lib.application import FontWeight, gui_app
from openpilot.common.params import ParamKeyType
from openpilot.starpilot.common.favorite_slots import (
  FAVORITE_ACTION_DECEL_COUNTER,
  FAVORITE_ACTION_DISTANCE_DECREASE,
  FAVORITE_SLOTS_PARAM,
)
from openpilot.selfdrive.ui.mici.onroad.augmented_road_view import FavoriteSlotsOverlay
from openpilot.selfdrive.ui.ui_state import ui_state


class FakeParams:
  def __init__(self):
    self.store = {}
    self.types = {
      FAVORITE_SLOTS_PARAM: ParamKeyType.JSON,
      "RedneckCruise": ParamKeyType.BOOL,
      "FeatureToggle": ParamKeyType.BOOL,
      "AccelerationProfile": ParamKeyType.INT,
    }

  def get(self, key):
    return self.store.get(key)

  def get_bool(self, key):
    return bool(self.store.get(key, False))

  def put(self, key, value):
    self.store[key] = value

  def put_bool(self, key, value):
    self.store[key] = bool(value)

  def put_bool_nonblocking(self, key, value):
    self.put_bool(key, value)

  def get_int(self, key, default=0):
    return int(self.store.get(key, default))

  def put_int(self, key, value):
    self.store[key] = int(value)

  def put_int_nonblocking(self, key, value):
    self.put_int(key, value)

  def put_nonblocking(self, key, value):
    self.put(key, value)

  def get_type(self, key):
    return self.types.get(key, ParamKeyType.STRING)


def _tap(overlay, rect, pos):
  overlay._handle_mouse_press(pos)
  overlay._handle_mouse_release(pos)


@pytest.fixture(autouse=True)
def setup_ui_state():
  params = FakeParams()
  memory = FakeParams()
  orig_params = getattr(ui_state, "ui_params", None)
  orig_memory = getattr(ui_state, "params_memory", None)
  ui_state.ui_params = params
  ui_state.params_memory = memory
  orig_font_fn = getattr(gui_app, "font", None)
  fake_font = rl.Font()
  gui_app.font = lambda *a, **kw: fake_font
  yield params, memory
  ui_state.ui_params = orig_params
  ui_state.params_memory = orig_memory
  if orig_font_fn is not None:
    gui_app.font = orig_font_fn


def test_mici_slot_partitioning(setup_ui_state):
  overlay = FavoriteSlotsOverlay()
  rect = rl.Rectangle(0, 0, 2160, 1080)
  slots = [(0, {}), (1, {}), (2, {})]
  boxes = overlay._slot_rects(rect, slots)

  assert len(boxes) == 3
  # Each slot width is 2160 / 3 = 720
  assert boxes[0][1].x == 0
  assert boxes[0][1].width == 720
  assert boxes[1][1].x == 720
  assert boxes[1][1].width == 720
  assert boxes[2][1].x == 1440
  assert boxes[2][1].width == 720


def test_mici_boolean_toggle_and_feedback(setup_ui_state):
  params, memory = setup_ui_state
  params.put("RedneckCruise", False)
  params.put(FAVORITE_SLOTS_PARAM, [
    {"enabled": True, "show_onroad": True, "key": "RedneckCruise", "label": "Redneck Cruise"},
  ])

  overlay = FavoriteSlotsOverlay()
  rect = rl.Rectangle(0, 0, 2160, 1080)
  overlay._visible_slots(force=True)
  overlay._button_rects = overlay._slot_rects(rect, overlay._visible_slots())

  # Tap Slot 0 (x=300, y=500)
  tap_pos = rl.Vector2(300, 500)
  _tap(overlay, rect, tap_pos)

  assert params.get_bool("RedneckCruise") is True
  assert memory.get_bool("StarPilotTogglesUpdated") is True
  assert overlay._feedback_slot == 0


def test_mici_action_trigger_and_feedback(setup_ui_state):
  params, memory = setup_ui_state
  params.put(FAVORITE_SLOTS_PARAM, [
    {"enabled": True, "show_onroad": True, "key": FAVORITE_ACTION_DISTANCE_DECREASE, "label": "Distance -"},
  ])

  overlay = FavoriteSlotsOverlay()
  rect = rl.Rectangle(0, 0, 2160, 1080)
  overlay._visible_slots(force=True)
  overlay._button_rects = overlay._slot_rects(rect, overlay._visible_slots())

  # Tap Slot 0
  tap_pos = rl.Vector2(300, 500)
  _tap(overlay, rect, tap_pos)

  assert memory.get_int(FAVORITE_ACTION_DECEL_COUNTER) == 1
  assert overlay._feedback_slot == 0


def test_mici_dropdown_enum_cycle_and_active_label(setup_ui_state):
  params, memory = setup_ui_state
  params.put_int("AccelerationProfile", 0)
  params.put(FAVORITE_SLOTS_PARAM, [
    {"enabled": True, "show_onroad": True, "key": "AccelerationProfile", "label": "Acceleration Profile"},
  ])

  overlay = FavoriteSlotsOverlay()
  rect = rl.Rectangle(0, 0, 2160, 1080)
  overlay._visible_slots(force=True)
  overlay._button_rects = overlay._slot_rects(rect, overlay._visible_slots())

  # Tap 1: Cycles from Standard (0) to Eco (1)
  tap_pos = rl.Vector2(300, 500)
  _tap(overlay, rect, tap_pos)
  assert params.get_int("AccelerationProfile") == 1
  assert memory.get_bool("StarPilotTogglesUpdated") is True

  # Tap 2: Cycles from Eco (1) to Sport (2)
  _tap(overlay, rect, tap_pos)
  assert params.get_int("AccelerationProfile") == 2

  # Tap 3: Cycles from Sport (2) to Sport+ (3)
  _tap(overlay, rect, tap_pos)
  assert params.get_int("AccelerationProfile") == 3

  # Tap 4: Wraps around from Sport+ (3) to Standard (0)
  _tap(overlay, rect, tap_pos)
  assert params.get_int("AccelerationProfile") == 0


def test_mici_tap_travel_cancellation(setup_ui_state):
  params, memory = setup_ui_state
  params.put("RedneckCruise", False)
  params.put(FAVORITE_SLOTS_PARAM, [
    {"enabled": True, "show_onroad": True, "key": "RedneckCruise", "label": "Redneck Cruise"},
  ])

  overlay = FavoriteSlotsOverlay()
  rect = rl.Rectangle(0, 0, 2160, 1080)
  overlay._visible_slots(force=True)
  overlay._button_rects = overlay._slot_rects(rect, overlay._visible_slots())

  # Press at (300, 500), drag to (350, 500) (dx=50px > MAX_TAP_TRAVEL 24px)
  press_pos = rl.Vector2(300, 500)
  drag_pos = rl.Vector2(350, 500)

  overlay._handle_mouse_press(press_pos)
  overlay._handle_mouse_event(SimpleNamespace(pos=drag_pos))
  overlay._handle_mouse_release(drag_pos)

  # Should NOT have toggled
  assert params.get_bool("RedneckCruise") is False
  assert overlay._feedback_slot is None
