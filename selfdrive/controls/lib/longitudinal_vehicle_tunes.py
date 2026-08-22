import numpy as np


HONDA_HRV_3G_FAR_FOLLOW_BRAKE_SLEW_RATE = 3.0
HONDA_HRV_3G_FAR_FOLLOW_RELEASE_SLEW_RATE = 2.0
HONDA_HRV_3G_UNTRACKED_SLOW_LEAD_DECEL_SCALE = 1.35
HYUNDAI_ELANTRA_LEAD_FOLLOW_JERK_SCALE = 1.25
GM_SILVERADO_EARLY_FOLLOW_MIN_EGO_SPEED = 18.0
GM_SILVERADO_EARLY_FOLLOW_MAX_DISTANCE = 130.0
GM_SILVERADO_EARLY_FOLLOW_MIN_MODEL_PROB = 0.85
GM_SILVERADO_EARLY_FOLLOW_MAX_LATERAL_OFFSET = 1.2
GM_SILVERADO_FOLLOW_PREBRAKE_MIN_HEADWAY = 1.25
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_EGO_SPEED = 2.0
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LEAD_SPEED = 0.45
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LEAD_DELTA = 0.35
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LEAD_ACCEL = 0.35
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MIN_MODEL_PROB = 0.95
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LATERAL_OFFSET = 1.75
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MIN_BRAKE = 0.18
TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_BRAKE = 0.32
TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_EGO_SPEED = 12.0
TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_MODEL_PROB = 0.85
TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_LATERAL_OFFSET = 1.2
TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_DISTANCE = 45.0
TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_DISTANCE = 105.0
TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_CLOSING_SPEED = 4.0
TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_BRAKE = 0.8
TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_BRAKE = 2.0
TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_DECEL = 0.5
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MIN_SPEED = 5.0
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MIN_CLOSING_SPEED = 0.75
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MIN_DISTANCE = 70.0
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MAX_DISTANCE = 100.0
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_DISTANCE_TIME = 4.5
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_DISTANCE_OFFSET = 32.0
TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MAX_LATERAL_OFFSET = 1.75
TOYOTA_RAV4_TSS2_FAR_FOLLOW_BRAKE_SLEW_RATE = 2.5
TOYOTA_RAV4_TSS2_FAR_FOLLOW_RELEASE_SLEW_RATE = 1.75
TOYOTA_CAMRY_TSS2_FORCE_STOP_HANDOFF_M = 4.5
# The Camry's force-stop path otherwise consumes the model endpoint before the
# normal MPC stop-distance margin can be applied. Keep it within the forward
# offset range exposed by the Force Stop setting.
TOYOTA_CAMRY_TSS2_FORCE_STOP_DISTANCE_BIAS_M = 6.0
DEFAULT_FORCE_STOP_HANDOFF_M = 6.0


def is_toyota_rav4_tss2_post_departure_tune(CP):
  """Identify RAV4 TSS2 variants that need normal catch-up caps after departure."""
  return (
    getattr(CP, "brand", "") == "toyota" and
    str(getattr(CP, "carFingerprint", "")) in ("TOYOTA_RAV4_TSS2", "TOYOTA_RAV4_TSS2_2023")
  )


def get_toyota_rav4_tss2_early_lead_cap(CP, lead, v_ego, accel_min):
  """Start a mild RAV4 coast/brake response before a hard lead approach."""
  if (
    not is_toyota_rav4_tss2_post_departure_tune(CP) or
    lead is None or not bool(getattr(lead, "status", False)) or
    bool(getattr(lead, "radar", False)) or
    float(v_ego) < TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_EGO_SPEED or
    float(getattr(lead, "modelProb", 0.0)) < TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_MODEL_PROB or
    abs(float(getattr(lead, "yRel", 0.0))) > TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_LATERAL_OFFSET
  ):
    return None

  distance = float(getattr(lead, "dRel", float("inf")))
  lead_speed = max(float(getattr(lead, "vLead", 0.0)), 0.0)
  closing_speed = float(v_ego) - lead_speed
  lead_brake = max(0.0, -float(getattr(lead, "aLeadK", 0.0)))
  if (
    not TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_DISTANCE <= distance <= TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_DISTANCE or
    closing_speed < TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_CLOSING_SPEED or
    lead_brake < TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_BRAKE
  ):
    return None

  distance_factor = np.clip(
    (TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_DISTANCE - distance) /
    (TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_DISTANCE - TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_DISTANCE),
    0.0, 1.0,
  )
  closing_factor = np.clip((closing_speed - 4.0) / 6.0, 0.0, 1.0)
  brake_factor = np.clip(
    (lead_brake - TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_BRAKE) /
    (TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_BRAKE - TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_BRAKE),
    0.0, 1.0,
  )
  confidence_factor = np.clip(
    (float(getattr(lead, "modelProb", 0.0)) - TOYOTA_RAV4_TSS2_EARLY_LEAD_MIN_MODEL_PROB) / 0.13,
    0.0, 1.0,
  )
  decel = 0.10 + 0.20 * distance_factor + 0.10 * closing_factor + 0.10 * brake_factor
  decel *= 0.75 + 0.25 * confidence_factor
  return max(float(accel_min), -min(TOYOTA_RAV4_TSS2_EARLY_LEAD_MAX_DECEL, decel))


def is_toyota_rav4_tss2_radar_follow_lead(CP, lead, v_ego):
  """Keep a credible RAV4 radar lead active through model-horizon dropouts."""
  if (
    not is_toyota_rav4_tss2_post_departure_tune(CP) or
    lead is None or not bool(getattr(lead, "status", False)) or
    not bool(getattr(lead, "radar", False)) or
    float(v_ego) < TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MIN_SPEED or
    abs(float(getattr(lead, "yRel", 0.0))) > TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MAX_LATERAL_OFFSET
  ):
    return False

  lead_speed = max(float(getattr(lead, "vLead", 0.0)), 0.0)
  closing_speed = float(v_ego) - lead_speed
  distance_limit = float(np.clip(
    TOYOTA_RAV4_TSS2_RADAR_FOLLOW_DISTANCE_OFFSET +
    TOYOTA_RAV4_TSS2_RADAR_FOLLOW_DISTANCE_TIME * float(v_ego),
    TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MIN_DISTANCE,
    TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MAX_DISTANCE,
  ))
  return (
    float(getattr(lead, "dRel", float("inf"))) <= distance_limit and
    closing_speed >= TOYOTA_RAV4_TSS2_RADAR_FOLLOW_MIN_CLOSING_SPEED
  )


def allow_radar_standstill_gap_settle(CP):
  """Keep the generic stopped-lead gap nudge out of the early RAV4 TSS2 path."""
  return not (
    getattr(CP, "brand", "") == "toyota" and
    str(getattr(CP, "carFingerprint", "")) == "TOYOTA_RAV4_TSS2"
  )


def get_far_follow_output_slew_rates(CP):
  if CP.brand == "honda" and str(CP.carFingerprint) == "HONDA_HRV_3G":
    return (
      HONDA_HRV_3G_FAR_FOLLOW_BRAKE_SLEW_RATE,
      HONDA_HRV_3G_FAR_FOLLOW_RELEASE_SLEW_RATE,
    )
  if is_toyota_rav4_tss2_post_departure_tune(CP):
    return (
      TOYOTA_RAV4_TSS2_FAR_FOLLOW_BRAKE_SLEW_RATE,
      TOYOTA_RAV4_TSS2_FAR_FOLLOW_RELEASE_SLEW_RATE,
    )
  return 0.0, 0.0


def get_untracked_slow_lead_decel_scale(CP):
  if CP.brand == "honda" and str(CP.carFingerprint) == "HONDA_HRV_3G":
    return HONDA_HRV_3G_UNTRACKED_SLOW_LEAD_DECEL_SCALE
  return 1.0


def get_lead_follow_jerk_scale(CP):
  """Spread the lead-source transition for cars with a sharp vision-lead handoff."""
  if getattr(CP, "brand", "") == "hyundai" and str(getattr(CP, "carFingerprint", "")) == "HYUNDAI_ELANTRA_2021":
    return HYUNDAI_ELANTRA_LEAD_FOLLOW_JERK_SCALE
  return 1.0


def is_gm_silverado_early_follow_lead(CP, lead, v_ego):
  """Admit a credible centered vision lead before it becomes a close lead."""
  if (
    CP.brand != "gm" or str(CP.carFingerprint) not in ("CHEVROLET_SILVERADO", "CHEVROLET_SILVERADO_CC") or
    lead is None or not bool(getattr(lead, "status", False)) or bool(getattr(lead, "radar", False)) or
    float(v_ego) < GM_SILVERADO_EARLY_FOLLOW_MIN_EGO_SPEED or
    float(getattr(lead, "dRel", float("inf"))) > GM_SILVERADO_EARLY_FOLLOW_MAX_DISTANCE or
    float(getattr(lead, "modelProb", 0.0)) < GM_SILVERADO_EARLY_FOLLOW_MIN_MODEL_PROB or
    abs(float(getattr(lead, "yRel", 0.0))) > GM_SILVERADO_EARLY_FOLLOW_MAX_LATERAL_OFFSET
  ):
    return False
  return True


def get_follow_prebrake_min_headway(CP, t_follow):
  """Return the comfort pre-brake floor without changing lead safety distance."""
  if CP.brand == "gm" and str(CP.carFingerprint) in ("CHEVROLET_SILVERADO", "CHEVROLET_SILVERADO_CC"):
    return max(float(t_follow), GM_SILVERADO_FOLLOW_PREBRAKE_MIN_HEADWAY)
  return max(float(t_follow), 1.6)


def get_toyota_sienna_post_departure_restop_cap(CP, lead, v_ego, accel_min,
                                                stop_distance, now_t, departure_latch_until):
  """Re-arm a stop if a Sienna's lead twitches forward and stops again."""
  if (
    CP.brand != "toyota" or str(CP.carFingerprint) != "TOYOTA_SIENNA_4TH_GEN" or
    now_t >= departure_latch_until or lead is None or not lead.status or
    float(v_ego) > TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_EGO_SPEED
  ):
    return None

  lead_radar = bool(getattr(lead, "radar", False))
  lead_prob = float(getattr(lead, "modelProb", 1.0 if lead_radar else 0.0))
  if not lead_radar and lead_prob < TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MIN_MODEL_PROB:
    return None
  if abs(float(getattr(lead, "yRel", 0.0))) > TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LATERAL_OFFSET:
    return None

  lead_speed = max(float(getattr(lead, "vLead", 0.0)), 0.0)
  lead_delta = lead_speed - float(v_ego)
  lead_accel = float(getattr(lead, "aLeadK", 0.0))
  max_distance = max(float(stop_distance) + 3.0, 4.5)
  if (
    float(getattr(lead, "dRel", float("inf"))) > max_distance or
    lead_speed > TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LEAD_SPEED or
    lead_delta > TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LEAD_DELTA or
    lead_accel > TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_LEAD_ACCEL
  ):
    return None

  speed_factor = float(np.clip(float(v_ego) / TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_EGO_SPEED, 0.0, 1.0))
  closing_factor = float(np.clip((float(v_ego) - lead_speed) / 1.5, 0.0, 1.0))
  hold_brake = TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MIN_BRAKE + 0.08 * speed_factor + 0.06 * closing_factor
  brake_floor = -float(np.clip(
    hold_brake,
    TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MIN_BRAKE,
    TOYOTA_SIENNA_POST_DEPARTURE_RESTOP_MAX_BRAKE,
  ))
  return brake_floor if accel_min >= 0.0 else max(float(accel_min), brake_floor)


def get_force_stop_handoff_distance(car_fingerprint):
  """Return the distance at which force-stop control hands off to MPC."""
  if str(car_fingerprint) == "TOYOTA_CAMRY_TSS2":
    return TOYOTA_CAMRY_TSS2_FORCE_STOP_HANDOFF_M
  return DEFAULT_FORCE_STOP_HANDOFF_M


def get_force_stop_distance_bias(car_fingerprint):
  if str(car_fingerprint) == "TOYOTA_CAMRY_TSS2":
    return TOYOTA_CAMRY_TSS2_FORCE_STOP_DISTANCE_BIAS_M
  return 0.0
