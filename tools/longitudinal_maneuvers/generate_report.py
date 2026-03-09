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


def report(platform, route, _description, CP, ID, maneuvers):
  output_path = Path(__file__).resolve().parent / "longitudinal_reports"
  output_fn = output_path / f"{platform}_{route.replace('/', '_')}.html"
  output_path.mkdir(exist_ok=True)
  target_cross_times = defaultdict(list)

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
