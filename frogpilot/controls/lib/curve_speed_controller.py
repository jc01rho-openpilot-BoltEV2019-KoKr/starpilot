#!/usr/bin/env python3
import json
import numpy as np

from openpilot.common.realtime import DT_MDL

from openpilot.frogpilot.common.frogpilot_variables import CRUISING_SPEED, DEFAULT_LATERAL_ACCELERATION, PLANNER_TIME, params

CALIBRATION_PROGRESS_THRESHOLD = 10 / DT_MDL
MAX_CURVATURE = 0.1
MIN_CURVATURE = 0.001
PERCENTILE = 90
ROUNDING_PRECISION = 5
STEP = 0.001

# Optimized curve speed parameters for smoother driving
CURVE_DECEL_DAMPENING = 0.75  # Reduce deceleration rate for gentler slowdown (0-1, lower = less aggressive)
MIN_CURVE_SPEED_REDUCTION = 0.85  # Minimum speed reduction factor (1.0 = no minimum limit)
GENTLE_CURVE_THRESHOLD = 0.015  # Curvature below this is considered gentle (reduced deceleration)
HIGHWAY_SPEED_THRESHOLD = 25  # m/s - above this, be more conservative with speed changes


class CurveSpeedController:
  def __init__(self, FrogPilotVCruise):
    self.frogpilot_planner = FrogPilotVCruise.frogpilot_planner

    self.enable_training = False
    self.target_set = False

    self.training_timer = 0

    self.curvature_data = json.loads(params.get("CurvatureData") or "{}")

    self.required_curvatures = [str(round(road_curvature, ROUNDING_PRECISION)) for road_curvature in np.arange(MIN_CURVATURE, MAX_CURVATURE + STEP, STEP)]

    self.update_lateral_acceleration()

    # Smoothing state for curve speed transitions
    self.previous_target = None
    self.curve_entry_speed = None

  def log_data(self, v_ego, sm):
    self.enable_training = v_ego > CRUISING_SPEED
    self.enable_training &= not self.frogpilot_planner.tracking_lead
    self.enable_training &= not sm["carControl"].longActive

    if self.enable_training:
      self.training_timer += DT_MDL

      if self.training_timer >= PLANNER_TIME and self.frogpilot_planner.driving_in_curve and not (sm["carState"].leftBlinker or sm["carState"].rightBlinker):
        lateral_acceleration = abs(self.frogpilot_planner.lateral_acceleration)
        road_curvature = abs(round(self.frogpilot_planner.road_curvature, ROUNDING_PRECISION))

        key = str(road_curvature)
        if key in self.curvature_data:
          data = self.curvature_data[key]

          average = data["average"]
          count = data["count"]

          self.curvature_data[key] = {
            "average": ((average * count) + lateral_acceleration) / (count + 1),
            "count": count + 1
          }
        else:
          self.curvature_data[key] = {
            "average": lateral_acceleration,
            "count": 1
          }

        self.update_lateral_acceleration()
      else:
        self.enable_training = False

    elif self.training_timer >= PLANNER_TIME:
      progress = 0.0
      for key in self.required_curvatures:
        if key in self.curvature_data:
          progress += min(self.curvature_data[key]["count"] / CALIBRATION_PROGRESS_THRESHOLD, 1.0)

      params.put_float_nonblocking("CalibrationProgress", (progress / len(self.required_curvatures)) * 100)
      params.put_nonblocking("CurvatureData", json.dumps(self.curvature_data))

      self.enable_training = False

      self.training_timer = 0

    else:
      self.enable_training = False

      self.training_timer = 0

  def update_lateral_acceleration(self):
    if self.curvature_data:
      all_samples = [data["average"] for data in self.curvature_data.values()]
      # Use slightly higher percentile for more confident lateral acceleration
      self.lateral_acceleration = float(np.percentile(all_samples, PERCENTILE))
    else:
      self.lateral_acceleration = DEFAULT_LATERAL_ACCELERATION

    params.put_float_nonblocking("CalibratedLateralAcceleration", self.lateral_acceleration)

  def update_target(self, v_ego):
    road_curvature = abs(self.frogpilot_planner.road_curvature)

    # Use calibrated lateral acceleration with a small boost for smoother driving
    lateral_acceleration = self.lateral_acceleration * 1.1  # 10% boost for less aggressive deceleration

    if self.target_set:
      # Calculate base curve speed from physics
      csc_speed = (lateral_acceleration / max(road_curvature, 0.0001))**0.5

      # Apply gentle curve handling - less deceleration for gentle curves
      if road_curvature < GENTLE_CURVE_THRESHOLD:
        # Gentle curve - reduce deceleration significantly
        dampening = CURVE_DECEL_DAMPENING * 0.5
      else:
        dampening = CURVE_DECEL_DAMPENING

      # Calculate deceleration rate with dampening
      time_to_curve = max(self.frogpilot_planner.time_to_curve, 0.5)
      raw_decel_rate = (v_ego - csc_speed) / time_to_curve
      decel_rate = raw_decel_rate * dampening

      # At highway speeds, be more conservative with speed changes
      if v_ego > HIGHWAY_SPEED_THRESHOLD:
        decel_rate *= 0.85

      # Apply minimum speed reduction limit
      min_speed = v_ego * MIN_CURVE_SPEED_REDUCTION
      csc_speed = max(csc_speed, min_speed)

      # Smooth the target transition
      self.target -= decel_rate * DT_MDL

      # Ensure target stays within reasonable bounds
      self.target = float(np.clip(self.target, CRUISING_SPEED, max(csc_speed, v_ego)))

      # Apply smoothing between previous and current target
      if self.previous_target is not None:
        # Exponential smoothing for smoother transitions
        alpha = 0.3
        self.target = alpha * self.target + (1 - alpha) * self.previous_target

      self.previous_target = self.target

    else:
      self.target_set = True
      self.target = v_ego
      self.curve_entry_speed = v_ego
      self.previous_target = v_ego

