from collections.abc import Callable
from pathlib import Path
from unittest.mock import MagicMock

import pytest

from openpilot.system.manager import build as build_module


def valid_pxd(model: str) -> str:
  return f'''cdef extern from "acados_solver_{model}.h":
    ctypedef struct nlp_solver_capsule "{model}_solver_capsule":
        pass
    nlp_solver_capsule * acados_create_capsule "{model}_acados_create_capsule"()
    int acados_free_capsule "{model}_acados_free_capsule"(nlp_solver_capsule *capsule)
'''


@pytest.mark.parametrize("contents", ["", "incomplete", valid_pxd("long")])
def test_present_invalid_pxd_is_stale(tmp_path: Path, contents: str) -> None:
  # Given
  pxd_path = tmp_path / "acados_solver.pxd"
  pxd_path.write_text(contents)

  # When / Then
  assert build_module.is_acados_pxd_stale(pxd_path, "lat")


def test_missing_pxd_is_not_stale(tmp_path: Path) -> None:
  # Given / When / Then
  assert not build_module.is_acados_pxd_stale(tmp_path / "acados_solver.pxd", "lat")


def test_matching_pxd_is_not_stale(tmp_path: Path) -> None:
  # Given
  pxd_path = tmp_path / "acados_solver.pxd"
  pxd_path.write_text(valid_pxd("lat"))

  # When / Then
  assert not build_module.is_acados_pxd_stale(pxd_path, "lat")


def test_find_stale_acados_dirs_returns_only_invalid_whitelisted_dir(tmp_path: Path) -> None:
  # Given
  lat_dir = tmp_path / build_module.ACADOS_GENERATED_DIRS[0][0]
  long_dir = tmp_path / build_module.ACADOS_GENERATED_DIRS[1][0]
  other_dir = tmp_path / "other/c_generated_code"
  for directory in (lat_dir, long_dir, other_dir):
    directory.mkdir(parents=True)
  (lat_dir / "acados_solver.pxd").write_text("")
  (long_dir / "acados_solver.pxd").write_text(valid_pxd("long"))
  (other_dir / "acados_solver.pxd").write_text("")

  # When / Then
  assert build_module.find_stale_acados_dirs(tmp_path) == [lat_dir]


def test_purge_acados_generated_dirs_refuses_non_whitelisted_path(tmp_path: Path) -> None:
  # Given
  allowed_dir = tmp_path / build_module.ACADOS_GENERATED_DIRS[0][0]
  rejected_dir = tmp_path / "other/c_generated_code"
  allowed_dir.mkdir(parents=True)
  rejected_dir.mkdir(parents=True)

  # When / Then
  with pytest.raises(ValueError):
    build_module.purge_acados_generated_dirs(tmp_path, [allowed_dir, rejected_dir])
  assert allowed_dir.exists()
  assert rejected_dir.exists()


def test_purge_acados_generated_dirs_removes_whitelisted_path(tmp_path: Path) -> None:
  # Given
  target_dir = tmp_path / build_module.ACADOS_GENERATED_DIRS[0][0]
  target_dir.mkdir(parents=True)

  # When
  build_module.purge_acados_generated_dirs(tmp_path, [target_dir])

  # Then
  assert not target_dir.exists()


@pytest.mark.parametrize("output", [
  b"Error compiling Cython file: acados_solver.pxd: 'nlp_solver_capsule' is not a type identifier",
  b"acados_ocp_solver_pyx.pyx: cimported module has no attribute 'acados_free_capsule'",
  b"Error compiling Cython file: 'acados_solver.pxd' not found",
])
def test_cython_pxd_errors_are_recognized(output: bytes) -> None:
  # Given / When / Then
  assert build_module.is_cython_pxd_error(output)


@pytest.mark.parametrize("output", [
  b"acados_ocp_solver_pyx.o Error -9",
  b"acados_solver_lat.c: error: use of undeclared identifier 'foo'",
])
def test_non_pxd_build_errors_are_not_recognized(output: bytes) -> None:
  # Given / When / Then
  assert not build_module.is_cython_pxd_error(output)


def recovery_runner(results: list[tuple[int, bytes]]) -> tuple[Callable[[], tuple[int, bytes]], list[int]]:
  calls: list[int] = []

  def run() -> tuple[int, bytes]:
    calls.append(1)
    return results[len(calls) - 1]

  return run, calls


@pytest.mark.parametrize("final_result", [(0, b""), (1, b"same cython failure")])
def test_cython_failure_purges_once_and_runs_at_most_twice(tmp_path: Path, monkeypatch: pytest.MonkeyPatch,
                                                           final_result: tuple[int, bytes]) -> None:
  # Given
  run, calls = recovery_runner([(1, b"Error compiling Cython file: acados_solver.pxd"), final_result])
  purged: list[list[Path]] = []
  monkeypatch.setattr(build_module, "purge_acados_generated_dirs", lambda _base, dirs: purged.append(dirs))

  # When
  result = build_module.run_with_acados_recovery(run, tmp_path)

  # Then
  assert result == final_result
  assert len(calls) == 2
  assert purged == [[tmp_path / relative for relative, _model in build_module.ACADOS_GENERATED_DIRS]]


def test_non_cython_failure_does_not_purge_or_retry(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
  # Given
  failure = (1, b"acados_ocp_solver_pyx.o Error -9")
  run, calls = recovery_runner([failure])
  purged: list[list[Path]] = []
  monkeypatch.setattr(build_module, "purge_acados_generated_dirs", lambda _base, dirs: purged.append(dirs))

  # When / Then
  assert build_module.run_with_acados_recovery(run, tmp_path) == failure
  assert len(calls) == 1
  assert purged == []


def test_build_preflight_purges_stale_dir_before_sequence(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> None:
  # Given
  stale_dir = tmp_path / build_module.ACADOS_GENERATED_DIRS[0][0]
  purged: list[list[Path]] = []
  monkeypatch.setattr(build_module, "BASEDIR", str(tmp_path))
  monkeypatch.setattr(build_module, "CACHE_DIR", tmp_path / "cache")
  monkeypatch.setattr(build_module, "find_stale_acados_dirs", lambda _base: [stale_dir])
  monkeypatch.setattr(build_module, "purge_acados_generated_dirs", lambda _base, dirs: purged.append(dirs))
  monkeypatch.setattr(build_module, "run_with_acados_recovery", lambda _run, _base: (0, b""))

  # When
  build_module.build(MagicMock())

  # Then
  assert purged == [[stale_dir]]
