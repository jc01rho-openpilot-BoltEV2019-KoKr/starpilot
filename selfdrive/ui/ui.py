#!/usr/bin/env python3
import gc
import os
import time

from openpilot.system.hardware import TICI
from openpilot.common.realtime import set_core_affinity
from openpilot.common.watchdog import kick_watchdog
from openpilot.system.ui.lib.application import gui_app
from openpilot.selfdrive.ui.stall_monitor import UIStallMonitor
from openpilot.selfdrive.ui.ui_state import ui_state

BIG_UI = gui_app.big_ui()

# Every core except camerad's isolated core 6 and modeld's core 7. Cores 0-3 never go
# offline, so the mask stays valid while power save offlines the big cluster.
UI_CORES = (0, 1, 2, 3, 4, 5)


def configure_ui_scheduling() -> None:
  """Run the UI as an ordinary time-shared task instead of a real-time one.

  The UI used to be SCHED_FIFO 50 pinned to core 5 alone, where plannerd, radard and
  starpilot_process run at FIFO 51 (and every thread they spawn inherits it). A strict
  priority FIFO gives a lower task no CPU at all while a higher one is runnable, so a
  load burst at a control-state change (lane change, lateral engage) could stall the
  render loop past the manager's 10s watchdog. As a normal task the scheduler moves the
  UI to whichever allowed core has time, and it can never delay a control process.
  """
  gc.disable()
  if TICI:
    os.sched_setscheduler(0, os.SCHED_OTHER, os.sched_param(0))
  set_core_affinity(list(UI_CORES))


def _stall_context() -> dict[str, object]:
  active_widget = gui_app.get_active_widget()
  context = {
    "ui_mode": "big" if BIG_UI else "small",
    "started": ui_state.started,
    "ignition": ui_state.ignition,
    "engaged": ui_state.engaged,
    "render_frame": gui_app.frame,
    "ui_state_frame": ui_state.sm.frame,
    "target_fps": gui_app.target_fps,
    "active_widget": type(active_widget).__name__ if active_widget is not None else "none",
  }

  try:
    device_state = ui_state.sm["deviceState"]
    context.update({
      "device_state_valid": bool(ui_state.sm.valid["deviceState"]),
      "memory_usage_percent": int(device_state.memoryUsagePercent),
      "gpu_usage_percent": int(device_state.gpuUsagePercent),
      "max_cpu_usage_percent": max((int(value) for value in device_state.cpuUsagePercent), default=0),
      "max_cpu_temp_c": round(max((float(value) for value in device_state.cpuTempC), default=0.0), 1),
      "max_gpu_temp_c": round(max((float(value) for value in device_state.gpuTempC), default=0.0), 1),
      "thermal_status": str(device_state.thermalStatus),
    })
  except Exception:
    pass

  return context


def main():
  configure_ui_scheduling()

  stall_monitor = UIStallMonitor("raylib_ui")
  stall_monitor.progress("ui.before_init_window")
  stall_monitor.start()

  try:
    gui_app.init_window("UI")
    stall_monitor.progress("ui.after_init_window")
    gui_app.set_progress_hook(stall_monitor.progress)
    kick_watchdog()
    stall_monitor.progress("ui.before_layout_init")
    if BIG_UI:
      from openpilot.selfdrive.ui.layouts.main import MainLayout
      MainLayout()
    else:
      from openpilot.selfdrive.ui.mici.layouts.main import MiciMainLayout
      MiciMainLayout()
    stall_monitor.progress("ui.after_layout_init")
    stall_monitor.set_context(_stall_context())
    kick_watchdog()
    stall_monitor.progress("ui.loop_ready")
    context_update_time = 0.0

    for _should_render in gui_app.render():
      stall_monitor.progress("ui.loop_iteration")
      kick_watchdog()
      stall_monitor.progress("ui.after_watchdog")
      ui_state.update(progress_hook=stall_monitor.progress)
      stall_monitor.progress("ui.after_state_update")
      now = time.monotonic()
      if now - context_update_time >= 1.0:
        stall_monitor.set_context(_stall_context())
        context_update_time = now
      stall_monitor.progress("ui.loop_idle")
  finally:
    gui_app.set_progress_hook(None)
    stall_monitor.stop()


if __name__ == "__main__":
  main()
