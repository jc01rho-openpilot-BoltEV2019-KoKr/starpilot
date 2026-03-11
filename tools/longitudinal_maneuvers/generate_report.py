#!/usr/bin/env python3
import argparse
import base64
import io
import os
import math
import json
import pprint
import webbrowser
from collections import defaultdict
from pathlib import Path
import matplotlib.pyplot as plt

from openpilot.tools.lib.logreader import LogReader
from openpilot.system.hardware.hw import Paths


def tabulate_html(rows, headers):
  builder = ["<table>", "<thead>", "<tr>"]
  for h in headers:
    builder.append(f"<th>{h}</th>")
  builder += ["</tr>", "</thead>", "<tbody>"]

  for row in rows:
    builder.append("<tr>")
    for cell in row:
      builder.append(f"<td>{cell}</td>")
    builder.append("</tr>")

  builder += ["</tbody>", "</table>"]
  return "\n".join(builder)


def parse_log_marker(text):
  raw = text
  try:
    payload = json.loads(text)
    if isinstance(payload, dict):
      raw = payload.get("msg", text)
  except json.JSONDecodeError:
    pass

  if not isinstance(raw, str) or not raw.startswith("LONG_MANEUVER_"):
    return None

  parts = raw.split("|")
  event = parts[0].replace("LONG_MANEUVER_", "")
  fields = {}
  for p in parts[1:]:
    if "=" in p:
      k, v = p.split("=", 1)
      fields[k] = v
  return event, fields


def extract_maneuver_intervals(msgs):
  intervals = []
  current = None

  for msg in msgs:
    which = msg.which()
    if which not in ("logMessage", "errorLogMessage"):
      continue

    text = msg.logMessage if which == "logMessage" else msg.errorLogMessage
    marker = parse_log_marker(text)
    if marker is None:
      continue

    event, fields = marker
    desc = fields.get("desc", "")
    run = int(fields.get("run", "0")) if fields.get("run", "0").isdigit() else 0

    if event == "START":
      current = {"desc": desc, "run": run, "start": msg.logMonoTime}
    elif event == "END" and current is not None:
      if not desc or desc == current["desc"]:
        intervals.append((current["desc"], current["run"], current["start"], msg.logMonoTime))
        current = None

  if current is not None:
    intervals.append((current["desc"], current["run"], current["start"], msgs[-1].logMonoTime))

  return intervals


def format_car_params(CP):
  return pprint.pformat({k: v for k, v in CP.to_dict().items() if not k.endswith('DEPRECATED')}, indent=2)


def is_informational_maneuver(description: str) -> bool:
  return "informational" in description.lower()


def split_phase_suffix(description: str) -> tuple[str, str]:
  desc = description.strip()
  if desc.endswith("]") and " [" in desc:
    idx = desc.rfind(" [")
    phase = desc[idx + 2:-1].strip().lower()
    if phase in {"pedal-only", "pedal+paddle"}:
      return desc[:idx], phase
  return desc, "standard"


def is_low_speed_stop_maneuver(description: str) -> bool:
  base_desc, _ = split_phase_suffix(description)
  return base_desc.lower().startswith("low-speed stop envelope:")


def is_paddle_blend_probe(description: str) -> bool:
  base_desc, _ = split_phase_suffix(description)
  return base_desc.lower().startswith("paddle blend probe:")


def is_terminal_stop_probe(description: str) -> bool:
  base_desc, _ = split_phase_suffix(description)
  return base_desc.lower().startswith("terminal stop probe:")


def interp_scalar(x: float, xp: list[float], fp: list[float]) -> float:
  if x <= xp[0]:
    return fp[0]
  for i in range(1, len(xp)):
    if x <= xp[i]:
      x0, x1 = xp[i - 1], xp[i]
      y0, y1 = fp[i - 1], fp[i]
      if x1 == x0:
        return y1
      return y0 + (y1 - y0) * ((x - x0) / (x1 - x0))
  return fp[-1]


def clamp(x: float, lo: float, hi: float) -> float:
  return max(lo, min(hi, x))


def first_true_time(times: list[float], values: list[bool]) -> float | None:
  for t, v in zip(times, values, strict=True):
    if v:
      return t
  return None


def sample_nearest(times: list[float], values: list[float], t_target: float) -> float:
  if not times:
    return 0.0
  idx = min(range(len(times)), key=lambda i: abs(times[i] - t_target))
  return values[idx]


def integrate_distance(times: list[float], speeds: list[float], start_t: float, end_t: float | None = None) -> float:
  if len(times) < 2:
    return 0.0

  total = 0.0
  end_val = times[-1] if end_t is None else end_t
  if end_val <= start_t:
    return 0.0

  for i in range(1, len(times)):
    t0, t1 = times[i - 1], times[i]
    v0, v1 = speeds[i - 1], speeds[i]
    if t1 <= start_t:
      continue
    if t0 >= end_val:
      break

    seg_start = max(t0, start_t)
    seg_end = min(t1, end_val)
    if seg_end <= seg_start:
      continue

    dt = max(t1 - t0, 1e-3)
    alpha_start = (seg_start - t0) / dt
    alpha_end = (seg_end - t0) / dt
    vs = v0 + (v1 - v0) * alpha_start
    ve = v0 + (v1 - v0) * alpha_end
    total += 0.5 * (vs + ve) * (seg_end - seg_start)

  return total


def extract_regen_paddle_state_from_can(msgs, t_ref_nanos: int) -> tuple[list[float], list[bool], str]:
  by_src: dict[int, list[tuple[float, bool]]] = defaultdict(list)
  for m in msgs:
    if m.which() != "can":
      continue
    t = (m.logMonoTime - t_ref_nanos) / 1e9
    for c in m.can:
      if int(c.address) != 189:
        continue
      dat = bytes(c.dat)
      if len(dat) == 0:
        continue
      # DBC: EBCMRegenPaddle.RegenPaddle is 4-bit signal at start bit 7 (motorola/big-endian), i.e. high nibble of byte 0.
      paddle_raw = (dat[0] >> 4) & 0xF
      by_src[int(c.src)].append((t, paddle_raw != 0))

  if by_src.get(128):
    samples = by_src[128]
    times = [s[0] for s in samples]
    states = [s[1] for s in samples]
    return times, states, "can src 128"

  if by_src:
    best_src = max(by_src.keys(), key=lambda s: len(by_src[s]))
    samples = by_src[best_src]
    times = [s[0] for s in samples]
    states = [s[1] for s in samples]
    return times, states, f"can src {best_src}"

  return [], [], "unavailable"


def report(platform, route, _description, CP, ID, maneuvers):
  output_path = Path(__file__).resolve().parent / "longitudinal_reports"
  output_fn = output_path / f"{platform}_{route.replace('/', '_')}.html"
  output_path.mkdir(exist_ok=True)
  target_cross_times = defaultdict(list)
  low_speed_stop_rows = []
  paddle_blend_rows = []

  builder = [
    "<style>summary { cursor: pointer; }\n td, th { padding: 8px; } </style>\n",
    "<h1>Longitudinal maneuver report</h1>\n",
    f"<h3>{platform}</h3>\n",
    f"<h3>{route}</h3>\n",
    f"<h3>{ID.gitCommit}, {ID.gitBranch}, {ID.gitRemote}</h3>\n",
  ]
  if _description is not None:
    builder.append(f"<h3>Description: {_description}</h3>\n")
  builder.append(f"<details><summary><h3 style='display: inline-block;'>CarParams</h3></summary><pre>{format_car_params(CP)}</pre></details>\n")
  builder.append('{ summary }')  # to be replaced below
  for description, runs in maneuvers:
    print(f'plotting maneuver: {description}, runs: {len(runs)}')
    builder.append("<div style='border-top: 1px solid #000; margin: 20px 0;'></div>\n")
    builder.append(f"<h2>{description}</h2>\n")
    for run, msgs in enumerate(runs):
      cc_pairs = [(m.logMonoTime, m.carControl) for m in msgs if m.which() == 'carControl']
      co_pairs = [(m.logMonoTime, m.carOutput) for m in msgs if m.which() == 'carOutput']
      cs_pairs = [(m.logMonoTime, m.carState) for m in msgs if m.which() == 'carState']
      lp_pairs = [(m.logMonoTime, m.livePose) for m in msgs if m.which() == 'livePose']
      plan_pairs = [(m.logMonoTime, m.longitudinalPlan) for m in msgs if m.which() == 'longitudinalPlan']
      if not (cc_pairs and co_pairs and cs_pairs and lp_pairs and plan_pairs):
        continue

      t_carControl, carControl = zip(*cc_pairs, strict=True)
      t_carOutput, carOutput = zip(*co_pairs, strict=True)
      t_carState, carState = zip(*cs_pairs, strict=True)
      t_livePose, livePose = zip(*lp_pairs, strict=True)
      t_longitudinalPlan, longitudinalPlan = zip(*plan_pairs, strict=True)

      # make time relative seconds
      t_carControl = [(t - t_carControl[0]) / 1e9 for t in t_carControl]
      t_carOutput = [(t - t_carOutput[0]) / 1e9 for t in t_carOutput]
      t_carState = [(t - t_carState[0]) / 1e9 for t in t_carState]
      t_livePose = [(t - t_livePose[0]) / 1e9 for t in t_livePose]
      t_longitudinalPlan = [(t - t_longitudinalPlan[0]) / 1e9 for t in t_longitudinalPlan]

      # maneuver validity
      longActive = [m.longActive for m in carControl]
      maneuver_valid = all(longActive) and (not any(cs.cruiseState.standstill for cs in carState) or CP.autoResumeSng)

      _open = 'open' if maneuver_valid else ''
      title = f'Run #{int(run)+1}' + (' <span style="color: red">(invalid maneuver!)</span>' if not maneuver_valid else '')

      builder.append(f"<details {_open}><summary><h3 style='display: inline-block;'>{title}</h3></summary>\n")

      info_only = is_informational_maneuver(description)

      # get first acceleration target and first intersection
      aTarget = longitudinalPlan[0].aTarget
      target_cross_time = None
      initial_speed = carState[0].vEgo
      builder.append(f'<h3 style="font-weight: normal">Initial aTarget: {round(aTarget, 2)} m/s^2')

      # Localizer is noisy, require two consecutive 20Hz frames above threshold
      prev_crossed = False
      for t, lp in zip(t_livePose, livePose, strict=True):
        crossed = (0 < aTarget < lp.accelerationDevice.x) or (0 > aTarget > lp.accelerationDevice.x)
        if crossed and prev_crossed:
          builder.append(f', <strong>crossed in {t:.3f}s</strong>')
          target_cross_time = t
          if maneuver_valid:
            target_cross_times[description].append(t)
          break
        prev_crossed = crossed
      else:
        builder.append(', <strong>not crossed</strong>')
      builder.append('</h3>')

      builder.append(
        f'<h3 style="font-weight: normal">Initial speed: <strong>{initial_speed:.2f} m/s '
        f'({initial_speed * 2.23694:.1f} mph)</strong></h3>'
      )

      if abs(aTarget) > 1e-3:
        if aTarget < 0:
          achieved = min((lp.accelerationDevice.x for lp in livePose), default=0.0)
          ratio = achieved / aTarget if aTarget != 0 else 0.0
          est_power_kw = (CP.mass * initial_speed * abs(aTarget)) / 1000.0
          ref = " vs 70 kW reference" if CP.carName == "gm" else ""
          builder.append(
            f'<h3 style="font-weight: normal">Estimated wheel regen demand: '
            f'<strong>{est_power_kw:.1f} kW</strong>{ref}</h3>'
          )
        else:
          achieved = max((lp.accelerationDevice.x for lp in livePose), default=0.0)
          ratio = achieved / aTarget if aTarget != 0 else 0.0

        builder.append(
          f'<h3 style="font-weight: normal">Peak achieved accel: <strong>{achieved:.2f} m/s^2</strong>, '
          f'Achieved/target ratio: <strong>{ratio:.2f}</strong></h3>'
        )

      if info_only:
        builder.append('<h3 style="font-weight: normal">Result type: <strong>informational</strong> (pedal/regen authority check)</h3>')

      cc_accels = [m.actuators.accel for m in carControl]
      co_accels = [m.actuatorsOutput.accel for m in carOutput]
      cs_accels = [m.aEgo for m in carState]
      cs_speeds = [m.vEgo for m in carState]
      plan_a_targets = [m.aTarget for m in longitudinalPlan]

      if is_low_speed_stop_maneuver(description) or is_terminal_stop_probe(description):
        should_stop_t = first_true_time(t_longitudinalPlan, [m.shouldStop for m in longitudinalPlan])
        stop_threshold = 0.20
        stop_t = first_true_time(t_carState, [v <= stop_threshold for v in cs_speeds])
        stop_time = stop_t if stop_t is not None else float("nan")
        target_decel = min(plan_a_targets)
        achieved_decel = min(cs_accels)
        ratio = (abs(achieved_decel) / max(abs(target_decel), 1e-3)) if target_decel < -1e-3 else 0.0
        min_speed = min(cs_speeds) if cs_speeds else float("nan")
        final_speed = cs_speeds[-1] if cs_speeds else float("nan")
        stop_reached = bool(cs_speeds) and (min_speed <= stop_threshold)

        rollout_m = float("nan")
        if should_stop_t is not None:
          rollout_end = stop_t if stop_t is not None else t_carState[-1]
          rollout_m = integrate_distance(t_carState, cs_speeds, should_stop_t, rollout_end)

        terminal_zone = [i for i, v in enumerate(cs_speeds) if 0.20 <= v <= 2.00]
        terminal_target = float("nan")
        terminal_achieved = float("nan")
        terminal_ratio = float("nan")
        if terminal_zone:
          terminal_achieved = min(cs_accels[i] for i in terminal_zone)
          terminal_targets = [sample_nearest(t_longitudinalPlan, plan_a_targets, t_carState[i]) for i in terminal_zone]
          terminal_target = min(terminal_targets) if terminal_targets else float("nan")
          if not math.isnan(terminal_target) and terminal_target < -1e-3:
            terminal_ratio = abs(terminal_achieved) / max(abs(terminal_target), 1e-3)

        linger_s = 0.0
        for i in range(1, len(t_carState)):
          if 0.20 <= cs_speeds[i - 1] <= 1.50 and 0.20 <= cs_speeds[i] <= 1.50:
            linger_s += (t_carState[i] - t_carState[i - 1])

        init_mph = initial_speed * 2.23694
        expected_ratio_floor = interp_scalar(init_mph, [6.0, 8.0, 12.0, 16.0, 20.0], [0.38, 0.45, 0.60, 0.72, 0.82])
        ratio_deficit = max(expected_ratio_floor - ratio, 0.0)
        terminal_ratio_goal = 0.95
        terminal_deficit = 0.0 if math.isnan(terminal_ratio) else max(terminal_ratio_goal - terminal_ratio, 0.0)
        _, phase_tag = split_phase_suffix(description)

        # In paddle mode, lower regen_gain_ratio => stronger commanded decel (since accel_term_scale uses 1/gain).
        # Delta is relative to goal tracking in the terminal zone.
        suggested_paddle_gain_delta_pct = 0.0
        if phase_tag == "pedal+paddle" and (not math.isnan(terminal_ratio)):
          suggested_paddle_gain_delta_pct = clamp(100.0 * ((terminal_ratio / max(terminal_ratio_goal, 1e-3)) - 1.0), -20.0, 10.0)

        suggested_accel_min_delta = 0.0
        if (not stop_reached) or ratio_deficit > 0.03 or terminal_deficit > 0.05:
          suggested_accel_min_delta = -clamp(0.05 + 0.40 * max(ratio_deficit, terminal_deficit), 0.05, 0.35)

        rollout_excess = 0.0 if math.isnan(rollout_m) else max(rollout_m - 2.0, 0.0)
        linger_excess = max(linger_s - 2.0, 0.0)
        suggested_stop_margin_m = clamp((0.60 * rollout_excess) + (0.40 * linger_excess), 0.0, 3.0)
        suggested_stop_margin_ft = suggested_stop_margin_m * 3.28084

        if not stop_reached:
          stop_grade = "NO_STOP"
        elif ratio >= expected_ratio_floor and (math.isnan(terminal_ratio) or terminal_ratio >= terminal_ratio_goal) and (math.isnan(rollout_m) or rollout_m <= 2.0) and linger_s <= 2.0:
          stop_grade = "OK"
        elif ratio >= 0.88 * expected_ratio_floor and min_speed <= 0.35 and (math.isnan(rollout_m) or rollout_m <= 3.5) and linger_s <= 3.5:
          stop_grade = "MARGINAL"
        else:
          stop_grade = "LIMITED"

        if not stop_reached:
          if phase_tag == "pedal+paddle" and abs(suggested_paddle_gain_delta_pct) >= 1.0:
            gain_text = f" and adjust low-speed `regen_gain_ratio` by {suggested_paddle_gain_delta_pct:+.0f}%"
          else:
            gain_text = ""
          tuning_hint = (
            f"No true stop: lower low-speed `accel_min` by {abs(suggested_accel_min_delta):.2f} m/s^2"
            f"{gain_text}."
          )
        elif ratio_deficit > 0.03 or terminal_deficit > 0.05:
          if phase_tag == "pedal+paddle" and abs(suggested_paddle_gain_delta_pct) >= 1.0:
            tuning_hint = (
              f"Terminal decel deficit: adjust low-speed `regen_gain_ratio` by {suggested_paddle_gain_delta_pct:+.0f}% "
              f"(negative = stronger paddle+pedal decel) and lower low-speed `accel_min` by {abs(suggested_accel_min_delta):.2f} m/s^2."
            )
          else:
            tuning_hint = (
              f"Terminal decel deficit: lower low-speed `accel_min` by {abs(suggested_accel_min_delta):.2f} m/s^2 "
              f"(pedal-only authority path)."
            )
        elif rollout_excess > 0.0 or linger_excess > 0.0:
          tuning_hint = (
            f"Late-stop rollout/linger: increase `IncreasedStoppingDistance` by ~{max(suggested_stop_margin_ft, 0.5):.1f} ft "
            f"(or add equivalent planner shouldStop margin)."
          )
        else:
          tuning_hint = "Low-speed stop authority is within target; focus next on paddle-transition smoothness."

        builder.append(
          f'<h3 style="font-weight: normal">Low-speed stop metrics: '
          f'expected ratio floor <strong>{expected_ratio_floor:.2f}</strong>, '
          f'achieved ratio <strong>{ratio:.2f}</strong>, '
          f'terminal ratio (0.2-2.0 m/s) <strong>{"n/a" if math.isnan(terminal_ratio) else f"{terminal_ratio:.2f}"}</strong>, '
          f'linger in 0.2-1.5 m/s <strong>{linger_s:.2f}s</strong>, '
          f'stop time <strong>{"n/a" if math.isnan(stop_time) else f"{stop_time:.2f}s"}</strong>, '
          f'rollout after shouldStop <strong>{"n/a" if math.isnan(rollout_m) else f"{rollout_m:.2f}m"}</strong>, '
          f'min speed <strong>{"n/a" if math.isnan(min_speed) else f"{min_speed:.2f} m/s"}</strong>, '
          f'suggested paddle gain delta <strong>{suggested_paddle_gain_delta_pct:+.0f}%</strong>, '
          f'suggested accel_min delta <strong>{suggested_accel_min_delta:.2f} m/s^2</strong>, '
          f'suggested stop margin <strong>{suggested_stop_margin_ft:.1f} ft</strong>, '
          f'grade <strong>{stop_grade}</strong></h3>'
        )
        builder.append(f'<h3 style="font-weight: normal">Tuning hint: <strong>{tuning_hint}</strong></h3>')

        low_speed_stop_rows.append([
          description,
          phase_tag,
          int(run) + 1,
          round(init_mph, 1),
          round(target_decel, 2),
          round(achieved_decel, 2),
          round(expected_ratio_floor, 2),
          round(ratio, 2),
          "n/a" if math.isnan(stop_time) else round(stop_time, 2),
          "n/a" if math.isnan(rollout_m) else round(rollout_m, 2),
          "n/a" if math.isnan(terminal_ratio) else round(terminal_ratio, 2),
          round(linger_s, 2),
          "n/a" if math.isnan(min_speed) else round(min_speed, 2),
          round(final_speed, 2),
          round(suggested_paddle_gain_delta_pct, 0),
          round(suggested_accel_min_delta, 2),
          round(suggested_stop_margin_ft, 1),
          stop_grade,
          tuning_hint,
        ])

      if is_paddle_blend_probe(description):
        regen_times, regen_states, regen_source = extract_regen_paddle_state_from_can(msgs, cs_pairs[0][0])
        if not regen_states:
          regen_times = list(t_carState)
          regen_states = [bool(getattr(m, "regenBraking", False)) for m in carState]
          regen_source = "carState.regenBraking"
        edge_times = [regen_times[i] for i in range(1, len(regen_states)) if regen_states[i] != regen_states[i - 1]]

        jerks = []
        jerk_times = []
        for i in range(1, len(livePose)):
          dt = max(t_livePose[i] - t_livePose[i - 1], 1e-3)
          da = livePose[i].accelerationDevice.x - livePose[i - 1].accelerationDevice.x
          jerks.append(da / dt)
          jerk_times.append(t_livePose[i])

        edge_jerk_peaks = []
        edge_cmd_steps = []
        edge_out_steps = []
        for edge_t in edge_times:
          local_jerks = [abs(j) for tj, j in zip(jerk_times, jerks, strict=True) if abs(tj - edge_t) <= 0.5]
          if local_jerks:
            edge_jerk_peaks.append(max(local_jerks))

          cc_pre = sample_nearest(t_carControl, cc_accels, edge_t - 0.25)
          cc_post = sample_nearest(t_carControl, cc_accels, edge_t + 0.25)
          edge_cmd_steps.append(abs(cc_post - cc_pre))

          co_pre = sample_nearest(t_carOutput, co_accels, edge_t - 0.25)
          co_post = sample_nearest(t_carOutput, co_accels, edge_t + 0.25)
          edge_out_steps.append(abs(co_post - co_pre))

        max_edge_jerk = max(edge_jerk_peaks) if edge_jerk_peaks else float("nan")
        max_cmd_step = max(edge_cmd_steps) if edge_cmd_steps else float("nan")
        max_out_step = max(edge_out_steps) if edge_out_steps else float("nan")
        suggested_blend_step_reduction = 0.0
        suggested_confirm_frames_add = 0
        if not math.isnan(max_cmd_step) and max_cmd_step > 0.45:
          suggested_blend_step_reduction = clamp((1.0 - (0.45 / max_cmd_step)) * 100.0, 0.0, 50.0)
        if not math.isnan(max_edge_jerk) and max_edge_jerk > 2.5:
          suggested_confirm_frames_add = int(clamp(math.ceil((max_edge_jerk - 2.5) / 0.8), 1, 3))

        if len(edge_times) == 0:
          blend_grade = "NO_EDGES"
        elif not math.isnan(max_edge_jerk) and max_edge_jerk <= 2.5 and (math.isnan(max_cmd_step) or max_cmd_step <= 0.45):
          blend_grade = "SMOOTH"
        elif not math.isnan(max_edge_jerk) and max_edge_jerk <= 3.5:
          blend_grade = "OK"
        else:
          blend_grade = "HARSH"

        if blend_grade == "NO_EDGES":
          blend_hint = "Probe did not toggle regen paddle; verify pedal+paddle phase was active."
        elif blend_grade == "HARSH":
          adjustments = []
          if suggested_blend_step_reduction > 0.0:
            adjustments.append(f"reduce blend step rates by ~{suggested_blend_step_reduction:.0f}%")
          if suggested_confirm_frames_add > 0:
            adjustments.append(f"increase press/release confirm frames by +{suggested_confirm_frames_add}")
          if not adjustments:
            adjustments.append("increase paddle min on/off hold by +1 frame")
          blend_hint = f"Harsh paddle transitions: {', '.join(adjustments)}."
        elif blend_grade == "OK":
          if suggested_confirm_frames_add > 0:
            blend_hint = f"Mostly stable; +{suggested_confirm_frames_add} confirm frame may remove remaining edge pulse."
          else:
            blend_hint = "Mostly stable; transition behavior is acceptable."
        else:
          blend_hint = "Transition behavior is already smooth."

        builder.append(
          f'<h3 style="font-weight: normal">Paddle blend metrics: '
          f'edge source <strong>{regen_source}</strong>, '
          f'edges <strong>{len(edge_times)}</strong>, '
          f'max |jerk| near edges <strong>{"n/a" if math.isnan(max_edge_jerk) else f"{max_edge_jerk:.2f} m/s^3"}</strong>, '
          f'max command step <strong>{"n/a" if math.isnan(max_cmd_step) else f"{max_cmd_step:.2f} m/s^2"}</strong>, '
          f'max output step <strong>{"n/a" if math.isnan(max_out_step) else f"{max_out_step:.2f} m/s^2"}</strong>, '
          f'suggested blend-step reduction <strong>{suggested_blend_step_reduction:.0f}%</strong>, '
          f'suggested confirm-frame add <strong>+{suggested_confirm_frames_add}</strong>, '
          f'grade <strong>{blend_grade}</strong></h3>'
        )
        builder.append(f'<h3 style="font-weight: normal">Tuning hint: <strong>{blend_hint}</strong></h3>')

        _, phase_tag = split_phase_suffix(description)
        paddle_blend_rows.append([
          description,
          phase_tag,
          int(run) + 1,
          regen_source,
          len(edge_times),
          "n/a" if math.isnan(max_edge_jerk) else round(max_edge_jerk, 2),
          "n/a" if math.isnan(max_cmd_step) else round(max_cmd_step, 2),
          "n/a" if math.isnan(max_out_step) else round(max_out_step, 2),
          round(suggested_blend_step_reduction, 0),
          suggested_confirm_frames_add,
          blend_grade,
          blend_hint,
        ])

      pitches = [math.degrees(m.orientationNED[1]) for m in carControl]
      builder.append(f'<h3 style="font-weight: normal">Average pitch: <strong>{sum(pitches) / len(pitches):0.2f} degrees</strong></h3>')

      plt.rcParams['font.size'] = 40
      fig = plt.figure(figsize=(30, 26))
      ax = fig.subplots(4, 1, sharex=True, gridspec_kw={'height_ratios': [5, 3, 1, 1]})

      ax[0].grid(linewidth=4)
      ax[0].plot(t_carControl, [m.actuators.accel for m in carControl], label='carControl.actuators.accel', linewidth=6)
      ax[0].plot(t_carOutput, [m.actuatorsOutput.accel for m in carOutput], label='carOutput.actuatorsOutput.accel', linewidth=6)
      ax[0].plot(t_longitudinalPlan, [m.aTarget for m in longitudinalPlan], label='longitudinalPlan.aTarget', linewidth=6)
      ax[0].plot(t_carState, [m.aEgo for m in carState], label='carState.aEgo', linewidth=6)
      ax[0].plot(t_livePose, [m.accelerationDevice.x for m in livePose], label='livePose.accelerationDevice.x', linewidth=6)
      # TODO localizer accel
      ax[0].set_ylabel('Acceleration (m/s^2)')
      #ax[0].set_ylim(-6.5, 6.5)
      ax[0].legend(prop={'size': 30})

      if target_cross_time is not None:
        ax[0].plot(target_cross_time, aTarget, marker='o', markersize=50, markeredgewidth=7, markeredgecolor='black', markerfacecolor='None')

      ax[1].grid(linewidth=4)
      ax[1].plot(t_carState, [m.vEgo for m in carState], 'g', label='vEgo', linewidth=6)
      ax[1].set_ylabel('Velocity (m/s)')
      ax[1].legend()

      ax[2].plot(t_carControl, longActive, label='longActive', linewidth=6)
      ax[3].plot(t_carState, [m.gasPressed for m in carState], label='gasPressed', linewidth=6)
      ax[3].plot(t_carState, [m.brakePressed for m in carState], label='brakePressed', linewidth=6)
      for i in (2, 3):
        ax[i].set_yticks([0, 1], minor=False)
        ax[i].set_ylim(-1, 2)
        ax[i].legend()

      ax[-1].set_xlabel("Time (s)")
      fig.tight_layout()

      buffer = io.BytesIO()
      fig.savefig(buffer, format='webp')
      plt.close(fig)
      buffer.seek(0)
      builder.append(f"<img src='data:image/webp;base64,{base64.b64encode(buffer.getvalue()).decode()}' style='width:100%; max-width:800px;'>\n")
      builder.append("</details>\n")

  summary = ["<h2>Summary</h2>\n"]
  cols = ['maneuver', 'type', 'crossed', 'runs', 'mean', 'min', 'max']
  table = []
  for description, runs in maneuvers:
    times = target_cross_times[description]
    row_type = 'informational' if is_informational_maneuver(description) else 'required'
    l = [description, row_type, len(times), len(runs)]
    if len(times):
      l.extend([round(sum(times) / len(times), 2), round(min(times), 2), round(max(times), 2)])
    table.append(l)
  summary.append(tabulate_html(table, cols) + '\n')

  if low_speed_stop_rows:
    summary.append("<h3>Low-Speed Stop Envelope</h3>\n")
    summary.append(
      tabulate_html(
        low_speed_stop_rows,
        [
          "maneuver",
          "phase",
          "run",
          "initial mph",
          "target decel",
          "achieved decel",
          "expected ratio floor",
          "achieved ratio",
          "time to stop (s)",
          "rollout after shouldStop (m)",
          "terminal ratio (0.2-2.0m/s)",
          "linger 0.2-1.5m/s (s)",
          "min speed (m/s)",
          "final speed (m/s)",
          "suggested paddle gain delta (%)",
          "suggested accel_min delta",
          "suggested stop margin (ft)",
          "grade",
          "tuning hint",
        ],
      ) + '\n'
    )

  if paddle_blend_rows:
    summary.append("<h3>Paddle Blend Transition Probe</h3>\n")
    summary.append(
      tabulate_html(
        paddle_blend_rows,
        [
          "maneuver",
          "phase",
          "run",
          "edge source",
          "regen edges",
          "max |jerk| near edges (m/s^3)",
          "max command step (m/s^2)",
          "max output step (m/s^2)",
          "suggested blend-step reduction (%)",
          "suggested confirm-frame add",
          "grade",
          "tuning hint",
        ],
      ) + '\n'
    )

  sum_idx = builder.index('{ summary }')
  builder[sum_idx:sum_idx + 1] = summary

  with open(output_fn, "w") as f:
    f.write(''.join(builder))

  print(f"\nOpening report: {output_fn}\n")
  webbrowser.open_new_tab(str(output_fn))


if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Generate longitudinal maneuver report from route')
  parser.add_argument('route', type=str, help='Route name (e.g. 00000000--5f742174be)')
  parser.add_argument('description', type=str, nargs='?')

  args = parser.parse_args()

  if '/' in args.route or '|' in args.route:
    lr = LogReader(args.route)
  else:
    segs = [seg for seg in os.listdir(Paths.log_root()) if args.route in seg]
    lr = LogReader([os.path.join(Paths.log_root(), seg, 'rlog.zst') for seg in segs])

  CP = lr.first('carParams')
  ID = lr.first('initData')
  platform = CP.carFingerprint
  print('processing report for', platform)

  maneuvers: list[tuple[str, list[list]]] = []
  msgs = list(lr)
  intervals = extract_maneuver_intervals(msgs)

  if intervals:
    grouped: dict[str, list[list]] = defaultdict(list)
    for desc, _, start, end in intervals:
      run_msgs = [m for m in msgs if start <= m.logMonoTime <= end]
      if run_msgs:
        grouped[desc].append(run_msgs)
    maneuvers = list(grouped.items())
  else:
    # Fallback for logs generated by the original alertDebug-based implementation.
    active_prev = False
    description_prev = None
    for msg in msgs:
      if msg.which() == 'alertDebug':
        active = 'Maneuver Active' in msg.alertDebug.alertText1
        if active and not active_prev:
          if msg.alertDebug.alertText2 == description_prev:
            maneuvers[-1][1].append([])
          else:
            maneuvers.append((msg.alertDebug.alertText2, [[]]))
          description_prev = maneuvers[-1][0]
        active_prev = active
      if active_prev:
        maneuvers[-1][1][-1].append(msg)

  report(platform, args.route, args.description, CP, ID, maneuvers)
