"""Pure NDA (road-limit v2) helpers shared by road_speed_limiter, the UI and tests.

Ported from neokii/npilot selfdrive/controls/neokii/navi_controller.py (d11d78cb, 2026-10-05).
Kept free of cereal and numpy so the logic can be tested without device builds.
"""
import math

# Rear-facing enforcement cameras: v2 senders report a signed distance plus a hold distance
# that stays enforced after the vehicle passes the camera pole.
REAR_CAMERA_TYPES = frozenset({75, 76, 86, 87, 88, 89})
# Camera types that keep the smooth approach curve even inside a section-enforcement zone.
SECTION_SMOOTH_CAMERA_TYPES = frozenset({2, 86, 88})

INT16_MIN = -32768
INT16_MAX = 32767

_TRAFFIC_SIGNAL_BOOLS = ("isGreenLightOn", "isLeftLightOn", "isRedLightOn")
_TRAFFIC_SIGNAL_INTS = ("greenLightRemainTime", "leftLightRemainTime", "redLightRemainTime", "distance")


def camera_distance(cam_type, distance, hold_distance, travel, source_age=0., v_ego=0.):
  """Normalize a v2 signed camera distance for positive-distance consumers.

  Returns (distance_m, rear_passed). After a rear camera is passed the distance counts down the
  remaining hold zone; legacy senders (no hold distance) keep the positive-distance contract.
  """
  if cam_type in REAR_CAMERA_TYPES and hold_distance is not None:
    try:
      distance, hold_distance, source_age = float(distance), float(hold_distance), float(source_age)
      if not all(math.isfinite(v) for v in (distance, hold_distance, source_age, travel, v_ego)) or \
         hold_distance <= 0 or source_age < 0:
        return 0, False
      current = distance - (max(travel, 0.) + source_age * max(v_ego, 0.))
      if current < -hold_distance:
        return 0, False
      passed = current <= 0.
      remaining = hold_distance + current if passed else current
      return min(max(math.ceil(remaining), 1), INT16_MAX), passed
    except (TypeError, ValueError, OverflowError):
      return 0, False
  try:
    distance = float(distance)
    return min(int(max(distance - travel, 0)), INT16_MAX) if distance > 0 else 0, False
  except (TypeError, ValueError, OverflowError):
    return 0, False


class RearCameraMotion:
  """Tracks travel for one publisher-owned rear-camera sample; heartbeats never restart it."""
  def __init__(self):
    self.key = None
    self.last_time = 0.
    self.last_speed = 0.
    self.travel = 0.

  def update(self, cam_type, distance, hold, source_id, received_at, now, age, speed):
    if cam_type not in REAR_CAMERA_TYPES or hold is None:
      self.key = None
      return camera_distance(cam_type, distance, hold, max(now - received_at, 0.) * max(speed, 0.))
    try:
      distance, hold, age, speed = float(distance), float(hold), float(age), float(speed)
      if not all(math.isfinite(v) for v in (distance, hold, age, speed, received_at, now)) or hold <= 0 or age < 0:
        raise ValueError('Invalid rear sample')
      speed = max(speed, 0.)
      # Missing IDs retain the packet-age behavior of earlier v2 senders.
      key = (source_id if source_id is not None else received_at, cam_type, distance, hold)
      if key != self.key:
        self.travel = (max(now - received_at, 0.) + age) * speed
        self.key = key
      else:
        self.travel += max(now - self.last_time, 0.) * (self.last_speed + speed) / 2.
      self.last_time, self.last_speed = now, speed
      return camera_distance(cam_type, distance, hold, self.travel)
    except (TypeError, ValueError, OverflowError):
      self.key = None
      return 0, False


def _clamp_int16(value):
  try:
    value = float(value)
  except (TypeError, ValueError):
    return 0
  if not math.isfinite(value):
    return 0
  return int(min(max(value, INT16_MIN), INT16_MAX))


def traffic_signal_fields(traffic_signal):
  ts = traffic_signal if isinstance(traffic_signal, dict) else {}
  fields = {key: bool(ts.get(key, False)) for key in _TRAFFIC_SIGNAL_BOOLS}
  fields.update({key: _clamp_int16(ts.get(key, 0)) for key in _TRAFFIC_SIGNAL_INTS})
  return fields


def traffic_signal_display(ts):
  """Return [(light, on, remaining_s)] for red, left and green, or None when nothing is reported."""
  lights = [
    ("red", bool(ts.isRedLightOn), int(ts.redLightRemainTime)),
    ("left", bool(ts.isLeftLightOn), int(ts.leftLightRemainTime)),
    ("green", bool(ts.isGreenLightOn), int(ts.greenLightRemainTime)),
  ]
  if not any(on or remaining > 0 for _, on, remaining in lights):
    return None
  return lights
