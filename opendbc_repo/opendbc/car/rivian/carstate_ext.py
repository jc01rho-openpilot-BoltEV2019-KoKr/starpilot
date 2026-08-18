"""Rivian Extreme-harness state support."""

import math

from opendbc.car import Bus, structs
from opendbc.car.common.conversions import Conversions as CV
from opendbc.car.rivian.values import RivianFlags

ButtonType = structs.CarState.ButtonEvent.Type

MAX_SET_SPEED = 85 * CV.MPH_TO_MS
MIN_SET_SPEED = 20 * CV.MPH_TO_MS


class RivianLongitudinalState:
  """State provided by the Extreme harness park-assist CAN bridge."""

  def __init__(self, CP):
    self.CP = CP
    self.set_speed = 10
    self.increase_button = False
    self.decrease_button = False
    self.distance_button = 0
    self.scroll_click_pressed = False
    self.increase_counter = 0
    self.decrease_counter = 0
    self.stalk_down_counter = 0

  def set_cruise_speed(self, speed: float) -> float:
    if self.CP.openpilotLongitudinalControl:
      self.set_speed = max(MIN_SET_SPEED, min(float(speed), MAX_SET_SPEED))
    return self.set_speed

  def update_longitudinal_upgrade(self, ret: structs.CarState, can_parsers) -> list:
    cp_park = can_parsers[Bus.alt]
    cp_adas = can_parsers[Bus.adas]
    cp = can_parsers[Bus.pt]
    button_events = []

    prev_increase_button = self.increase_button
    prev_decrease_button = self.decrease_button
    prev_scroll_click_pressed = self.scroll_click_pressed

    if self.CP.openpilotLongitudinalControl:
      right_scroll = int(cp_park.vl["WheelButtons_Fwd"]["RightButton_Scroll"])
      if right_scroll != 255:
        if self.distance_button != right_scroll:
          # Rivian's rotary value changes once per detent. A release-only gap
          # event preserves the existing three-profile personality cycling.
          button_events.append(structs.CarState.ButtonEvent(pressed=False, type=ButtonType.gapAdjustCruise))
        self.distance_button = right_scroll

      # Scroll-click is a separate two-bit signal from rotary movement. Treat
      # it as a held distance button so the existing short/long/very-long
      # mappings apply, including Traffic Mode on a very-long hold.
      self.scroll_click_pressed = cp_park.vl["WheelButtons_Fwd"]["RightButton_ScrollClick"] == 2
      if self.scroll_click_pressed != prev_scroll_click_pressed:
        button_events.append(structs.CarState.ButtonEvent(pressed=self.scroll_click_pressed, type=ButtonType.gapAdjustCruise))

      self.increase_button = cp_park.vl["WheelButtons_Fwd"]["RightButton_RightClick"] == 2
      self.decrease_button = cp_park.vl["WheelButtons_Fwd"]["RightButton_LeftClick"] == 2
      self.increase_counter = self.increase_counter + 1 if self.increase_button else 0
      self.decrease_counter = self.decrease_counter + 1 if self.decrease_button else 0

      metric = cp_adas.vl["Cluster"]["Cluster_Unit"] == 0
      conversion = CV.KPH_TO_MS if metric else CV.MPH_TO_MS
      long_press_step = 10.0 if metric else 5.0
      set_speed_display = self.set_speed * (CV.MS_TO_KPH if metric else CV.MS_TO_MPH)

      if self.increase_button:
        if self.increase_counter % 66 == 0:
          self.set_speed = math.ceil((set_speed_display + 1) / long_press_step) * long_press_step * conversion
        elif not prev_increase_button:
          self.set_speed += conversion

      if self.decrease_button:
        if self.decrease_counter % 66 == 0:
          self.set_speed = math.floor((set_speed_display - 1) / long_press_step) * long_press_step * conversion
        elif not prev_decrease_button:
          self.set_speed -= conversion

      if not ret.cruiseState.enabled:
        self.set_speed = ret.vEgoCluster

      stalk_down = int(cp.vl["VDM_AdasSts"]["VDM_UserAdasRequest"]) in (3, 4)
      self.stalk_down_counter = self.stalk_down_counter + 1 if stalk_down else 0
      if self.stalk_down_counter == 50:
        self.set_speed = max(self.set_speed, ret.vEgoCluster)

      self.set_speed = max(MIN_SET_SPEED, min(self.set_speed, MAX_SET_SPEED))
      ret.cruiseState.speed = self.set_speed

    ret.leftBlindspot = cp_park.vl["BSM_BlindSpotIndicator_Fwd"]["BSM_BlindSpotIndicator_Left"] != 0
    ret.rightBlindspot = cp_park.vl["BSM_BlindSpotIndicator_Fwd"]["BSM_BlindSpotIndicator_Right"] != 0

    return button_events

  def update(self, ret: structs.CarState, can_parsers) -> None:
    button_events = []

    if self.CP.flags & RivianFlags.LONGITUDINAL_HARNESS:
      button_events.extend(self.update_longitudinal_upgrade(ret, can_parsers))

    ret.buttonEvents = button_events
