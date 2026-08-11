import sys
from types import ModuleType, SimpleNamespace

if "smbus2" not in sys.modules:
  _smbus2 = ModuleType("smbus2")

  class SMBus:  # noqa: N801
    def __init__(self, *a, **k):
      pass

    def close(self):
      pass

  _smbus2.SMBus = SMBus
  sys.modules["smbus2"] = _smbus2

import numpy as np

from openpilot.selfdrive.controls.lib.drive_helpers import get_lateral_active


def test_get_lateral_active_requires_enabled_without_aol():
  assert not get_lateral_active(False, True, False, False, False, False, False, True)


def test_get_lateral_active_allows_aol_while_disabled():
  assert get_lateral_active(False, False, True, False, False, False, False, True)


# ---------------------------------------------------------------------------
# LaneCenteringController — deterministic RED tests.
#
# Locked contract: .slim/deepwork/lane-center-control.md
#   class LaneCenteringController in drive_helpers.py
#   update(model_curvature, model_v2, v_ego, enabled, offset, lat_active, model_valid) -> float
#
# Sign conventions (controlsd / latcontrol_torque):
#   laneLines[1] left  -> y negative     laneLines[2] right -> y positive
#   measured_curvature = -VM.calc_curvature(SA); get_steer_from_curvature(-desired)
#   => openpilot curvature positive -> steer right; negative -> steer left
#   offset positive -> desire right of geometric center
#
# Hard gates (model_curvature returned unchanged, filter state hard-reset):
#   enabled, lat_active, model_valid, laneChangeState == off, v_ego >= 5 m/s,
#   model_v2.position itself missing/malformed (no baseline to correct from at all).
#
# Laneline confidence (probability, std, width -- ramped smoothly, NOT a hard gate):
#   blends the *target* between the laneline center and the model's own predicted path.
#   With `offset == 0` this is numerically indistinguishable from the old hard-gate "noop"
#   behavior (see the tests below), which is why the original RED tests still hold unchanged.
#   The actual behavior change lives in the "laneline confidence blends, offset survives"
#   section further down: with a nonzero `offset` and no/unreliable lane lines, the controller
#   no longer drops the correction to zero -- it falls back to applying `offset` alone on top
#   of the model's own path, e.g. on a center-stripe-only road with a curbed shoulder and no
#   lane line to read on that side.
# ---------------------------------------------------------------------------

_V_EGO = 20.0
_XS = np.linspace(0.0, 50.0, 52)


def _lane(y_val):
  return SimpleNamespace(x=_XS.copy(), y=np.full_like(_XS, float(y_val)))


def _model_v2(left_y=-1.8, right_y=1.8, *, model_y=0.0, left_prob=0.9, right_prob=0.9,
              left_std=0.1, right_std=0.1, lane_change_state=0):
  """SimpleNamespace fixture mirroring the modelV2 lane-line shape."""
  return SimpleNamespace(
    laneLines=[_lane(0), _lane(left_y), _lane(right_y), _lane(0)],
    laneLineProbs=[0.0, left_prob, right_prob, 0.0],
    laneLineStds=[0.0, left_std, right_std, 0.0],
    position=_lane(model_y),
    meta=SimpleNamespace(laneChangeState=int(lane_change_state)),
  )


def _ctrl():
  from openpilot.selfdrive.controls.lib.drive_helpers import LaneCenteringController
  return LaneCenteringController()


def _converge(v2, offset=0.0, model_curv=0.0, steps=300):
  c = _ctrl()
  out = model_curv
  for _ in range(steps):
    out = c.update(model_curv, v2, _V_EGO, True, offset, True, True)
  return c, out


# ===== hard gates: gate failure returns model_curvature unchanged =====

def test_lc_disabled_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6), _V_EGO, False, 0.0, True, True) == 0.01


def test_lc_lateral_inactive_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6), _V_EGO, True, 0.0, False, True) == 0.01


def test_lc_invalid_model_is_noop():
  # Stale/invalid modelV2 must hard-reset; do not correct from cached lines.
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6), _V_EGO, True, 0.0, True, False) == 0.01


def test_lc_low_speed_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6), 3.0, True, 0.0, True, True) == 0.01


def test_lc_low_probability_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6, left_prob=0.3), _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_high_std_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6, right_std=0.5), _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_implausible_narrow_width_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=1.2), _V_EGO, True, 0.0, True, True) == 0.01  # width 2.2 < 2.6


def test_lc_implausible_wide_width_is_noop():
  assert _ctrl().update(0.01, _model_v2(left_y=-2.5, right_y=2.5), _V_EGO, True, 0.0, True, True) == 0.01  # width 5.0 > 4.8


def test_lc_lane_change_is_noop():
  for state in (1, 2, 3):
    assert _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6, lane_change_state=state),
                          _V_EGO, True, 0.0, True, True) == 0.01


# ===== malformed data: treated as no-confidence (smooth fade target=0, not hard reset) =====

def test_lc_nan_in_lane_line_is_noop():
  bad = _model_v2(left_y=-1.0, right_y=2.6)
  bad.laneLines[1].y[10] = np.nan
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_empty_lane_line_is_noop():
  bad = _model_v2()
  bad.laneLines[2] = SimpleNamespace(x=np.array([]), y=np.array([]))
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_empty_model_path_is_noop():
  bad = _model_v2(left_y=-1.5, right_y=2.1)
  bad.position = SimpleNamespace(x=np.array([]), y=np.array([]))
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_mismatched_lane_xy_lengths_are_noop():
  bad = _model_v2(left_y=-1.5, right_y=2.1)
  bad.laneLines[1].x = bad.laneLines[1].x[:-1]
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_non_monotonic_lane_x_is_noop():
  bad = _model_v2(left_y=-1.5, right_y=2.1)
  bad.laneLines[2].x[10] = bad.laneLines[2].x[9]
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_mismatched_model_path_xy_lengths_are_noop():
  bad = _model_v2(left_y=-1.5, right_y=2.1)
  bad.position.y = bad.position.y[:-1]
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


def test_lc_non_monotonic_model_path_x_is_noop():
  bad = _model_v2(left_y=-1.5, right_y=2.1)
  bad.position.x[10] = bad.position.x[9]
  assert _ctrl().update(0.01, bad, _V_EGO, True, 0.0, True, True) == 0.01


# ===== laneline confidence blends, offset survives (the behavior this PR adds) =====
#
# The tests above all pass offset=0.0, so a confidence-degraded target (which collapses to
# the model's own path) produces the same zero correction the old hard gate did -- that's why
# they still pass unmodified. These tests set offset != 0 to show the actual change: the
# correction no longer disappears when lane lines are missing/unreliable, because the target
# falls back to (model's own path + offset) instead of just (model's own path).

def test_lc_no_lanelines_offset_still_applies():
  # Both lines undetected entirely (e.g. a center-stripe-only road with a curbed shoulder and
  # no line to read there). Old behavior: hard-gated to zero, offset silently dropped. New
  # behavior: falls back to applying offset alone, same magnitude as if lines were confident
  # and already centered.
  v2 = _model_v2(left_y=-1.8, right_y=1.8, left_prob=0.0, right_prob=0.0)
  _, out = _converge(v2, offset=0.3)
  assert out > 1e-6


def test_lc_one_sided_laneline_offset_still_applies():
  # Only the right line is confidently detected -- e.g. no line on the curb side. A single
  # unreliable line is enough to drag the old hard gate's min(probL, probR) check below
  # threshold; offset must still apply.
  v2 = _model_v2(left_y=-1.8, right_y=1.8, left_prob=0.1, right_prob=0.9)
  _, out = _converge(v2, offset=0.3)
  assert out > 1e-6


def test_lc_no_lanelines_zero_offset_still_noop():
  # No lanelines AND no user offset: nothing to correct toward -- must not invent a pull from
  # a laneline center it shouldn't trust.
  v2 = _model_v2(left_y=-1.8, right_y=1.8, left_prob=0.0, right_prob=0.0)
  _, out = _converge(v2, offset=0.0)
  assert abs(out) < 1e-6


def test_lc_implausible_width_offset_still_applies():
  v2 = _model_v2(left_y=-4.0, right_y=4.0)  # width 8.0, well beyond _LC_MAX_WIDTH
  _, out = _converge(v2, offset=0.3)
  assert out > 1e-6


def test_lc_confidence_fade_matches_no_lanelines_offset_magnitude():
  # A fully-confident, already-centered lane line and a fully-unconfident one should converge
  # to the *same* correction when offset is identical -- both reduce to "target = model's own
  # path + offset". This is the blend's continuity property: confidence changes how much the
  # laneline center pulls the target, not whether offset applies.
  centered_confident = _model_v2(left_y=-1.8, right_y=1.8)  # center 0.0, matches model_y default
  no_lanelines = _model_v2(left_y=-1.8, right_y=1.8, left_prob=0.0, right_prob=0.0)
  _, out_confident = _converge(centered_confident, offset=0.3)
  _, out_no_lines = _converge(no_lanelines, offset=0.3)
  assert np.isclose(out_confident, out_no_lines, atol=1e-6)


def test_lc_high_confidence_still_pulls_toward_laneline_center():
  # Sanity check the blend didn't regress full-confidence centering: with zero offset and a
  # laneline center that disagrees with the model's own path, high confidence should still
  # pull toward the laneline center (this duplicates the intent of
  # test_lc_center_right_steers_right but stated in blend terms for contrast with the tests
  # above).
  v2 = _model_v2(left_y=-1.5, right_y=2.1)  # center +0.3 m right, high confidence
  _, out = _converge(v2, offset=0.0)
  assert out > 1e-6


# ===== correction signs (positive openpilot curvature = steer right) =====

def test_lc_symmetric_lane_no_correction():
  _, out = _converge(_model_v2(left_y=-1.8, right_y=1.8))
  assert abs(out) < 1e-6


def test_lc_curved_lane_matching_model_path_has_no_correction():
  _, out = _converge(_model_v2(left_y=-1.5, right_y=2.1, model_y=0.3))
  assert abs(out) < 1e-6


def test_lc_center_right_steers_right():
  # Car left of geometric center => center_y > 0 => positive curvature (right)
  _, out = _converge(_model_v2(left_y=-1.5, right_y=2.1))  # center +0.3 m right
  assert out > 1e-6


def test_lc_center_left_steers_left():
  # Car right of geometric center => center_y < 0 => negative curvature (left)
  _, out = _converge(_model_v2(left_y=-2.1, right_y=1.5))  # center -0.3 m left
  assert out < -1e-6


def test_lc_model_path_right_of_lane_center_steers_left():
  _, out = _converge(_model_v2(left_y=-1.8, right_y=1.8, model_y=0.3))
  assert out < -1e-6


def test_lc_negative_offset_steers_left():
  _, out = _converge(_model_v2(left_y=-1.8, right_y=1.8), offset=-0.3)
  assert out < -1e-6


def test_lc_positive_offset_steers_right():
  _, out = _converge(_model_v2(left_y=-1.8, right_y=1.8), offset=0.3)
  assert out > 1e-6


# ===== magnitude properties =====

def test_lc_correction_capped():
  # center 1.5 m right -> raw 2*1.5/20^2 = 0.0075, above the 0.004 raw cap.
  _, out = _converge(_model_v2(left_y=0.0, right_y=3.0), steps=500)
  assert np.isclose(out, 0.004 * 0.30, atol=1e-8)


def test_lc_offset_proportional():
  _, o1 = _converge(_model_v2(left_y=-1.8, right_y=1.8), offset=0.15)
  _, o2 = _converge(_model_v2(left_y=-1.8, right_y=1.8), offset=0.30)
  assert abs(o2) > abs(o1) > 1e-6


def test_lc_correction_additive_to_model_curvature():
  _, base = _converge(_model_v2(left_y=-1.5, right_y=2.1), model_curv=0.0)
  _, with_c = _converge(_model_v2(left_y=-1.5, right_y=2.1), model_curv=0.01)
  assert abs((with_c - 0.01) - base) < 1e-4


# ===== smooth stateful transitions =====

def test_lc_smooth_activation():
  c = _ctrl()
  v2 = _model_v2(left_y=-1.5, right_y=2.1)
  first = c.update(0.0, v2, _V_EGO, True, 0.0, True, True)
  steady = 0.0
  for _ in range(300):
    steady = c.update(0.0, v2, _V_EGO, True, 0.0, True, True)
  assert 0 < first < steady  # ramps up gradually, not instant


def test_lc_smooth_fallback():
  c = _ctrl()
  v2_good = _model_v2(left_y=-1.5, right_y=2.1)
  for _ in range(300):
    c.update(0.0, v2_good, _V_EGO, True, 0.0, True, True)
  # confidence drops -> correction fades, does not snap to zero
  v2_bad = _model_v2(left_y=-1.5, right_y=2.1, left_prob=0.2)
  fading = c.update(0.0, v2_bad, _V_EGO, True, 0.0, True, True)
  assert abs(fading) > 1e-6
  final = 0.0
  for _ in range(300):
    final = c.update(0.0, v2_bad, _V_EGO, True, 0.0, True, True)
  assert abs(final) < 1e-6  # fully fades back to model curvature


def test_lc_invalid_model_hard_resets_after_active():
  c = _ctrl()
  v2 = _model_v2(left_y=-1.5, right_y=2.1)
  for _ in range(300):
    c.update(0.0, v2, _V_EGO, True, 0.0, True, True)
  # invalid/stale model: hard reset (unlike low-confidence smooth fade)
  out = c.update(0.01, v2, _V_EGO, True, 0.0, True, False)
  assert out == 0.01


def test_lc_lane_change_hard_resets_after_active():
  # Warm correction must not leave a 0.4s residual when a lane change begins.
  # Cold-start laneChangeState==off checks are insufficient: residual only appears
  # after nonzero correction has already been filtered in.
  for state in (1, 2, 3):
    c = _ctrl()
    v2 = _model_v2(left_y=-1.5, right_y=2.1)
    for _ in range(300):
      c.update(0.0, v2, _V_EGO, True, 0.0, True, True)
    assert abs(c._correction) > 1e-6
    v2.meta.laneChangeState = state
    out = c.update(0.01, v2, _V_EGO, True, 0.0, True, True)
    assert out == 0.01
    assert c._correction == 0.0


def test_lc_non_finite_offset_hard_resets_cold():
  import math
  for bad_offset in (float("nan"), float("inf"), float("-inf"), math.nan):
    out = _ctrl().update(0.01, _model_v2(left_y=-1.0, right_y=2.6), _V_EGO, True, bad_offset, True, True)
    assert out == 0.01
    assert math.isfinite(out)


def test_lc_non_finite_offset_hard_resets_after_active():
  import math
  for bad_offset in (float("nan"), float("inf"), float("-inf")):
    c = _ctrl()
    v2 = _model_v2(left_y=-1.5, right_y=2.1)
    for _ in range(300):
      c.update(0.0, v2, _V_EGO, True, 0.0, True, True)
    assert abs(c._correction) > 1e-6
    out = c.update(0.01, v2, _V_EGO, True, bad_offset, True, True)
    assert out == 0.01
    assert c._correction == 0.0
    assert math.isfinite(out)


def test_lc_update_requires_explicit_model_valid():
  import inspect
  from openpilot.selfdrive.controls.lib.drive_helpers import LaneCenteringController
  sig = inspect.signature(LaneCenteringController.update)
  assert "model_valid" in sig.parameters
  assert sig.parameters["model_valid"].default is inspect.Parameter.empty
