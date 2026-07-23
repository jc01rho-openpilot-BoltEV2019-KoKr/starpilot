from __future__ import annotations

import time


VASM_STATE_TIMEOUT_SECONDS = 3.0


def get_fresh_vasm_state(params_memory, now: float | None = None) -> tuple[bool, bool]:
  """Return V-ASM state only while the vision daemon is updating it."""
  try:
    updated_at = float(params_memory.get("VASMLastUpdateMonoTime") or 0)
  except (TypeError, ValueError):
    return False, False

  current_time = time.monotonic() if now is None else now
  age = current_time - updated_at
  if updated_at <= 0 or age < 0 or age > VASM_STATE_TIMEOUT_SECONDS:
    return False, False

  active_values = ("1", b"1", True)
  return params_memory.get("VASMLeftActive") in active_values, params_memory.get("VASMRightActive") in active_values
