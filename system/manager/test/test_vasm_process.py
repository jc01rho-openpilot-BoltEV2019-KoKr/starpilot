from types import SimpleNamespace

from openpilot.system.manager.process_config import run_v_asm


def test_vasm_process_defaults_off_and_runs_only_onroad():
  assert not run_v_asm(False, None, None, SimpleNamespace(v_asm_enabled=False))
  assert not run_v_asm(False, None, None, SimpleNamespace(v_asm_enabled=True))
  assert not run_v_asm(True, None, None, SimpleNamespace(v_asm_enabled=False))
  assert run_v_asm(True, None, None, SimpleNamespace(v_asm_enabled=True))
