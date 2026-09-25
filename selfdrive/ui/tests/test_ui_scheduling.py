
import gc
import importlib
import os
import sys
import types

import pytest

UI_MODULE = "openpilot.selfdrive.ui.ui"
CAMERAD_AND_MODELD_CORES = {6, 7}
POWER_SAVE_ONLINE_CORES = {0, 1, 2, 3}


class _StopMain(Exception):
  pass


def _load_ui_with_stubbed_raylib_stack(monkeypatch, calls):
  app = types.SimpleNamespace(
    big_ui=lambda: True,
    init_window=lambda _name: (calls.append("init_window"), (_ for _ in ()).throw(_StopMain()))[1],
    set_progress_hook=lambda _hook: None,
  )
  stall_monitor = types.SimpleNamespace(progress=lambda _phase: None, start=lambda: None, stop=lambda: None)

  stubs = {
    "openpilot.system.ui.lib.application": types.SimpleNamespace(gui_app=app),
    "openpilot.selfdrive.ui.stall_monitor": types.SimpleNamespace(UIStallMonitor=lambda _name: stall_monitor),
    "openpilot.selfdrive.ui.ui_state": types.SimpleNamespace(ui_state=types.SimpleNamespace()),
    "openpilot.common.watchdog": types.SimpleNamespace(kick_watchdog=lambda: None),
    "openpilot.common.realtime": types.SimpleNamespace(set_core_affinity=lambda _cores: None),
  }
  for name, module in stubs.items():
    monkeypatch.setitem(sys.modules, name, module)
  monkeypatch.delitem(sys.modules, UI_MODULE, raising=False)
  ui = importlib.import_module(UI_MODULE)

  monkeypatch.setattr(ui, "TICI", True)
  monkeypatch.setattr(ui, "set_core_affinity", lambda cores: calls.append(("affinity", tuple(cores))))
  monkeypatch.setattr(ui.os, "sched_setscheduler", lambda pid, policy, param: calls.append(("scheduler", pid, policy, param.sched_priority)))
  return ui


@pytest.fixture
def gc_restored():
  was_enabled = gc.isenabled()
  gc.enable()
  yield
  if was_enabled:
    gc.enable()
  else:
    gc.disable()


def test_ui_runs_as_normal_task_off_control_cores(monkeypatch, gc_restored):
  calls = []
  ui = _load_ui_with_stubbed_raylib_stack(monkeypatch, calls)

  ui.configure_ui_scheduling()

  assert ("scheduler", 0, os.SCHED_OTHER, 0) in calls
  affinity = [call for call in calls if call[0] == "affinity"]
  assert affinity == [("affinity", (0, 1, 2, 3, 4, 5))]
  assert not CAMERAD_AND_MODELD_CORES & set(affinity[0][1])
  assert POWER_SAVE_ONLINE_CORES <= set(affinity[0][1]), "mask must stay non-empty in power save"
  assert not gc.isenabled(), "scheduling move must keep GC disabled"


def test_main_applies_scheduling_before_opening_the_window(monkeypatch, gc_restored):
  calls = []
  ui = _load_ui_with_stubbed_raylib_stack(monkeypatch, calls)

  with pytest.raises(_StopMain):
    ui.main()

  scheduler_index = next(i for i, call in enumerate(calls) if isinstance(call, tuple) and call[0] == "scheduler")
  assert scheduler_index < calls.index("init_window")
  assert not any(isinstance(call, tuple) and call[0] == "scheduler" and call[2] != os.SCHED_OTHER for call in calls)
