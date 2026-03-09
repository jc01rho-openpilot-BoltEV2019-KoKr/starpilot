#!/usr/bin/env python3
import json
import time
import numpy as np
from dataclasses import dataclass
from collections import defaultdict
from typing import NamedTuple

from cereal import messaging, car
from openpilot.common.conversions import Conversions as CV
from openpilot.common.realtime import DT_MDL
from openpilot.common.params import Params
from openpilot.common.swaglog import cloudlog
from openpilot.selfdrive.controls.lib.drive_helpers import CONTROL_N
from openpilot.selfdrive.modeld.constants import ModelConstants
from openpilot.selfdrive.car.gm.values import GMFlags


@dataclass
class Action:
  accel_bp: list[float]  # m/s^2
  time_bp: list[float]   # seconds

  def __post_init__(self):
    assert len(self.accel_bp) == len(self.time_bp)


@dataclass
class Maneuver:
  description: str
  actions: list[Action]
  repeat: int = 0
  initial_speed: float = 0.  # m/s

  _active: bool = False
  _finished: bool = False
  _action_index: int = 0
  _action_frames: int = 0
  _ready_cnt: int = 0
  _repeated: int = 0

  def get_accel(self, v_ego: float, long_active: bool, standstill: bool, cruise_standstill: bool) -> float:
    ready = abs(v_ego - self.initial_speed) < 0.3 and long_active and not cruise_standstill
    if self.initial_speed < 0.01:
      ready = ready and standstill
    self._ready_cnt = (self._ready_cnt + 1) if ready else 0

    if self._ready_cnt > (3. / DT_MDL):
      self._active = True

    if not self._active:
      return min(max(self.initial_speed - v_ego, -2.), 2.)

    action = self.actions[self._action_index]
    action_accel = np.interp(self._action_frames * DT_MDL, action.time_bp, action.accel_bp)

    self._action_frames += 1

    # reached duration of action
    if self._action_frames > (action.time_bp[-1] / DT_MDL):
      # next action
      if self._action_index < len(self.actions) - 1:
        self._action_index += 1
        self._action_frames = 0
      # repeat maneuver
      elif self._repeated < self.repeat:
        self._repeated += 1
        self._action_index = 0
        self._action_frames = 0
        self._active = False
      # finish maneuver
      else:
        self._finished = True

    return float(action_accel)

  @property
  def finished(self):
    return self._finished

  @property
  def active(self):
    return self._active


BASE_MANEUVERS = [
  Maneuver(
    "come to stop",
    [Action([-0.5], [12])],
    repeat=2,
    initial_speed=5.,
  ),
  Maneuver(
    "start from stop",
    [Action([1.5], [6])],
    repeat=2,
    initial_speed=0.,
  ),
  Maneuver(
    "creep: alternate between +1m/s^2 and -1m/s^2",
    [
      Action([1], [3]), Action([-1], [3]),
      Action([1], [3]), Action([-1], [3]),
      Action([1], [3]), Action([-1], [3]),
    ],
    repeat=2,
    initial_speed=0.,
  ),
  Maneuver(
    "brake step response: -1m/s^2 from 20mph",
    [Action([-1], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
  Maneuver(
    "gas step response: +1m/s^2 from 20mph",
    [Action([1], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
  Maneuver(
    "gas step response: +4m/s^2 from 20mph",
    [Action([4], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
]

STANDARD_BRAKE_STEPS = [
  Maneuver(
    "brake step response: -4m/s^2 from 20mph",
    [Action([-4], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
]

PEDAL_LONG_BRAKE_STEPS = [
  Maneuver(
    "brake step response: -2.0m/s^2 from 20mph",
    [Action([-2.0], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
  Maneuver(
    "brake step response: -2.5m/s^2 from 20mph",
    [Action([-2.5], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
  Maneuver(
    "brake step response: -4m/s^2 from 20mph (informational, pedal-limited)",
    [Action([-4], [3])],
    repeat=2,
    initial_speed=20. * CV.MPH_TO_MS,
  ),
]


def clone_maneuver(m: Maneuver, label_suffix: str = "") -> Maneuver:
  actions = [Action(list(a.accel_bp), list(a.time_bp)) for a in m.actions]
  desc = f"{m.description} {label_suffix}".strip()
  return Maneuver(desc, actions, repeat=m.repeat, initial_speed=m.initial_speed)


def build_maneuvers(CP, label_suffix: str = "") -> list[Maneuver]:
  is_gm_pedal_long = (CP.carName == "gm" and CP.enableGasInterceptor and bool(CP.flags & GMFlags.PEDAL_LONG.value))
  maneuvers = [clone_maneuver(m, label_suffix) for m in BASE_MANEUVERS]
  brake_steps = PEDAL_LONG_BRAKE_STEPS if is_gm_pedal_long else STANDARD_BRAKE_STEPS

  # Keep brake step maneuvers grouped with other step responses.
  insert_idx = next((i for i, m in enumerate(maneuvers) if m.description.startswith("gas step response")), len(maneuvers))
  for step in reversed(brake_steps):
    maneuvers.insert(insert_idx, clone_maneuver(step, label_suffix))

  return maneuvers


class ManeuverPhase(NamedTuple):
  name: str
  paddle_mode: str
  maneuvers: list[Maneuver]


def build_maneuver_phases(CP) -> list[ManeuverPhase]:
  is_gm_pedal_long = (CP.carName == "gm" and CP.enableGasInterceptor and bool(CP.flags & GMFlags.PEDAL_LONG.value))
  if not is_gm_pedal_long:
    return [ManeuverPhase("standard", "auto", build_maneuvers(CP))]

  # For pedal-long GM, run paired A/B phases to isolate pedal-only vs pedal+paddle behavior.
  return [
    ManeuverPhase("pedal_only", "off", build_maneuvers(CP, "[pedal-only]")),
    ManeuverPhase("pedal_plus_paddle", "force", build_maneuvers(CP, "[pedal+paddle]")),
  ]


def get_phase_step_count(phase: ManeuverPhase) -> int:
  return sum(m.repeat + 1 for m in phase.maneuvers)


def get_total_step_count(phases: list[ManeuverPhase]) -> int:
  return sum(get_phase_step_count(phase) for phase in phases)


def write_status(params: Params, status: dict, history_line: str | None = None, **fields) -> None:
  if history_line:
    history = list(status.get("history", []))
    history.append(history_line)
    status["history"] = history[-120:]

  status.update(fields)
  status["updatedAtSec"] = time.time()
  params.put("LongitudinalManeuverStatus", json.dumps(status, separators=(",", ":")))


def main():
  params = Params()
  history = []
  raw_status = params.get("LongitudinalManeuverStatus", encoding="utf-8") or ""
  if raw_status:
    try:
      prior_status = json.loads(raw_status)
      if isinstance(prior_status, dict):
        raw_history = prior_status.get("history", [])
        if isinstance(raw_history, list):
          history = [str(line) for line in raw_history if str(line).strip()][-120:]
    except Exception:
      pass

  status = {
    "state": "starting",
    "phase": "",
    "paddleMode": "auto",
    "maneuver": "",
    "runIndex": 0,
    "runTotal": 0,
    "stepIndex": 0,
    "stepTotal": 0,
    "phaseStepIndex": 0,
    "phaseStepTotal": 0,
    "uiShow": True,
    "uiSize": "mid",
    "uiText1": "Long Maneuvers",
    "uiText2": "Waiting for CarParams...",
    "history": history,
  }
  write_status(params, status, history_line="Mode armed, waiting for CarParams.")

  cloudlog.info("maneuversd is waiting for CarParams")
  cp_bytes = params.get("CarParams", block=True)
  try:
    with car.CarParams.from_bytes(cp_bytes) as msg:
      CP = msg
  except Exception:
    # Fallback for branches that decode via Event wrapper only.
    CP = messaging.log_from_bytes(cp_bytes).carParams
  cloudlog.warning("LONG_MANEUVER_MODE|state=STARTED")
  params.put("LongitudinalManeuverPaddleMode", "auto")

  sm = messaging.SubMaster(['carState', 'carControl', 'controlsState', 'modelV2'], poll='modelV2')
  pm = messaging.PubMaster(['longitudinalPlan'])

  phases = build_maneuver_phases(CP)
  total_step_count = max(get_total_step_count(phases), 1)
  phase_idx = 0
  active_phase = phases[phase_idx]
  active_phase_step_total = get_phase_step_count(active_phase)
  params.put("LongitudinalManeuverPaddleMode", active_phase.paddle_mode)
  cloudlog.warning(f"LONG_MANEUVER_PHASE|name={active_phase.name}|paddleMode={active_phase.paddle_mode}")
  write_status(
    params,
    status,
    state="phase",
    phase=active_phase.name,
    paddleMode=active_phase.paddle_mode,
    stepTotal=total_step_count,
    phaseStepTotal=active_phase_step_total,
    uiText1="Long Maneuvers",
    uiText2=f"Phase {phase_idx + 1}/{len(phases)}: {active_phase.name} ({active_phase_step_total} steps)",
    history_line=f"Phase {phase_idx + 1}/{len(phases)} started: {active_phase.name} ({active_phase_step_total} steps).",
  )

  maneuvers = iter(active_phase.maneuvers)
  maneuver = None
  maneuver_run_count: defaultdict[str, int] = defaultdict(int)
  run_active = False
  active_description = ""
  active_run_index = 0
  active_run_total = 0
  finished_logged = False
  active_phase_name = active_phase.name
  active_paddle_mode = active_phase.paddle_mode
  step_index = 0
  phase_step_index = 0

  t_idx = ModelConstants.T_IDXS[:CONTROL_N]
  try:
    while True:
      sm.update()

      if maneuver is None:
        maneuver = next(maneuvers, None)
        run_active = False
        active_description = ""
        if maneuver is None:
          if phase_idx + 1 < len(phases):
            phase_idx += 1
            active_phase = phases[phase_idx]
            active_phase_name = active_phase.name
            active_paddle_mode = active_phase.paddle_mode
            active_phase_step_total = get_phase_step_count(active_phase)
            phase_step_index = 0
            params.put("LongitudinalManeuverPaddleMode", active_paddle_mode)
            cloudlog.warning(f"LONG_MANEUVER_PHASE|name={active_phase_name}|paddleMode={active_paddle_mode}")
            write_status(
              params,
              status,
              state="phase",
              phase=active_phase_name,
              paddleMode=active_paddle_mode,
              phaseStepIndex=phase_step_index,
              phaseStepTotal=active_phase_step_total,
              uiText1="Long Maneuvers",
              uiText2=f"Phase {phase_idx + 1}/{len(phases)}: {active_phase_name} ({active_phase_step_total} steps)",
              history_line=f"Phase {phase_idx + 1}/{len(phases)} started: {active_phase_name} ({active_phase_step_total} steps).",
            )
            maneuvers = iter(active_phase.maneuvers)
            maneuver = next(maneuvers, None)
          elif not finished_logged:
            cloudlog.warning("LONG_MANEUVER_MODE|state=FINISHED")
            write_status(
              params,
              status,
              state="finished",
              maneuver="",
              runIndex=0,
              runTotal=0,
              uiShow=True,
              uiSize="mid",
              uiText1="Long Maneuvers Complete",
              uiText2=f"Completed {step_index}/{total_step_count} steps. Returning to normal long control.",
              history_line=f"Complete: {step_index}/{total_step_count} steps finished.",
            )
            params.put_bool("LongitudinalManeuverMode", False)
            finished_logged = True
            break

      plan_send = messaging.new_message('longitudinalPlan')
      plan_send.valid = sm.all_checks()

      longitudinalPlan = plan_send.longitudinalPlan
      accel = 0
      v_ego = max(sm['carState'].vEgo, 0)

      if maneuver is not None:
        accel = maneuver.get_accel(v_ego, sm['carControl'].longActive, sm['carState'].standstill, sm['carState'].cruiseState.standstill)

        if maneuver.active and not run_active:
          maneuver_run_count[maneuver.description] += 1
          step_index += 1
          phase_step_index += 1
          run_active = True
          active_description = maneuver.description
          active_run_index = maneuver_run_count[maneuver.description]
          active_run_total = maneuver.repeat + 1
          cloudlog.warning(
            f"LONG_MANEUVER_START|desc={maneuver.description}|run={maneuver_run_count[maneuver.description]}|"
            f"accel={accel:.3f}|phase={active_phase_name}|paddleMode={active_paddle_mode}"
          )
          write_status(
            params,
            status,
            state="running",
            phase=active_phase_name,
            paddleMode=active_paddle_mode,
            maneuver=active_description,
            runIndex=active_run_index,
            runTotal=active_run_total,
            stepIndex=step_index,
            stepTotal=total_step_count,
            phaseStepIndex=phase_step_index,
            phaseStepTotal=active_phase_step_total,
            uiShow=True,
            uiSize="mid",
            uiText1="Long Maneuvers",
            uiText2=f"Step {step_index}/{total_step_count}: {active_description} ({active_run_index}/{active_run_total})",
            history_line=f"Step {step_index}/{total_step_count} started: {active_description} ({active_run_index}/{active_run_total}).",
          )
        elif run_active and not maneuver.active:
          cloudlog.warning(
            f"LONG_MANEUVER_END|desc={active_description}|run={maneuver_run_count[active_description]}|"
            f"phase={active_phase_name}|paddleMode={active_paddle_mode}"
          )
          write_status(
            params,
            status,
            state="running",
            phase=active_phase_name,
            paddleMode=active_paddle_mode,
            maneuver=active_description,
            runIndex=active_run_index,
            runTotal=active_run_total,
            stepIndex=step_index,
            stepTotal=total_step_count,
            phaseStepIndex=phase_step_index,
            phaseStepTotal=active_phase_step_total,
            uiShow=True,
            uiSize="small",
            uiText1="Long Maneuvers",
            uiText2=f"Step {step_index}/{total_step_count} complete",
            history_line=f"Step {step_index}/{total_step_count} complete: {active_description} ({active_run_index}/{active_run_total}).",
          )
          run_active = False
          active_description = ""

      longitudinalPlan.aTarget = accel
      longitudinalPlan.shouldStop = v_ego < CP.vEgoStopping and accel < 1e-2

      longitudinalPlan.allowBrake = True
      longitudinalPlan.allowThrottle = True
      longitudinalPlan.hasLead = True

      # Build a full horizon trajectory so both old and new long APIs can consume the test plan.
      speed_traj = [max(v_ego + accel * t, 0.0) for t in t_idx]
      speed_traj[0] = max(speed_traj[0], 0.2)  # keeps stock-ACC resume spamming path alive when needed
      longitudinalPlan.speeds = speed_traj
      longitudinalPlan.accels = [accel] * CONTROL_N
      longitudinalPlan.jerks = [0.0] * CONTROL_N

      pm.send('longitudinalPlan', plan_send)

      if maneuver is not None and maneuver.finished:
        if run_active:
          cloudlog.warning(
            f"LONG_MANEUVER_END|desc={active_description}|run={maneuver_run_count[active_description]}|"
            f"phase={active_phase_name}|paddleMode={active_paddle_mode}"
          )
          write_status(
            params,
            status,
            state="running",
            phase=active_phase_name,
            paddleMode=active_paddle_mode,
            maneuver=active_description,
            runIndex=active_run_index,
            runTotal=active_run_total,
            stepIndex=step_index,
            stepTotal=total_step_count,
            phaseStepIndex=phase_step_index,
            phaseStepTotal=active_phase_step_total,
            uiShow=True,
            uiSize="small",
            uiText1="Long Maneuvers",
            uiText2=f"Step {step_index}/{total_step_count} complete",
            history_line=f"Step {step_index}/{total_step_count} complete: {active_description} ({active_run_index}/{active_run_total}).",
          )
        cloudlog.warning(
          f"LONG_MANEUVER_FINISHED|desc={maneuver.description}|runs={maneuver_run_count[maneuver.description]}|"
          f"phase={active_phase_name}|paddleMode={active_paddle_mode}"
        )
        write_status(
          params,
          status,
          state="running",
          phase=active_phase_name,
          paddleMode=active_paddle_mode,
          maneuver="",
          runIndex=0,
          runTotal=0,
          uiShow=True,
          uiSize="small",
          uiText1="Long Maneuvers",
          uiText2=f"Maneuver complete: {maneuver.description}",
          history_line=f"Maneuver complete: {maneuver.description}.",
        )
        maneuver = None
        run_active = False
        active_description = ""
        active_run_index = 0
        active_run_total = 0
  finally:
    if not finished_logged:
      write_status(
        params,
        status,
        state="stopped",
        uiShow=True,
        uiSize="small",
        uiText1="Long Maneuvers Stopped",
        uiText2=f"Stopped at step {step_index}/{total_step_count}.",
        history_line=f"Stopped at step {step_index}/{total_step_count}.",
      )
    params.put("LongitudinalManeuverPaddleMode", "auto")
