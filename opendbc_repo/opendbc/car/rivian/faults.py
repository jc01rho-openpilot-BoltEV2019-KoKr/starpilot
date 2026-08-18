TOI_FAULT_ALERT_FRAMES = 25


def get_steering_faults(angle_harness: bool, toi_fault: bool, toi_fault_persistent: bool,
                        eac_status: int, eac_error_code: int) -> tuple[bool, bool, bool]:
  if angle_harness:
    # The torque controller handles the short ToiFlt release/rearm handshake
    # internally. Escalate only if EPAS does not recover inside that window.
    temporary = toi_fault_persistent or (eac_status == 2 and eac_error_code != 0)
    return eac_status == 4, temporary, eac_status == 2 and eac_error_code == 12

  return False, toi_fault or eac_error_code != 0, False
