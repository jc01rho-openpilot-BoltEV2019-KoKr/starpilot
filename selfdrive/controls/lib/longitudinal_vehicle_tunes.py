HONDA_HRV_3G_FAR_FOLLOW_BRAKE_SLEW_RATE = 3.0
HONDA_HRV_3G_FAR_FOLLOW_RELEASE_SLEW_RATE = 2.0


def get_far_follow_output_slew_rates(CP):
  if CP.brand == "honda" and str(CP.carFingerprint) == "HONDA_HRV_3G":
    return (
      HONDA_HRV_3G_FAR_FOLLOW_BRAKE_SLEW_RATE,
      HONDA_HRV_3G_FAR_FOLLOW_RELEASE_SLEW_RATE,
    )
  return 0.0, 0.0
