#!/usr/bin/env python3
import os
import shutil
import subprocess
from collections.abc import Callable
from pathlib import Path

# NOTE: Do NOT import anything here that needs be built (e.g. params)
from openpilot.common.basedir import BASEDIR
from openpilot.common.spinner import Spinner
from openpilot.common.text_window import TextWindow
from openpilot.common.swaglog import cloudlog, add_file_handler
from openpilot.system.hardware import HARDWARE, AGNOS
from openpilot.system.version import get_build_metadata

MAX_CACHE_SIZE = 4e9 if "CI" in os.environ else 2e9
CACHE_DIR = Path("/data/scons_cache" if AGNOS else "/tmp/scons_cache")

TOTAL_SCONS_NODES = 2705
MAX_BUILD_PROGRESS = 100

ACADOS_GENERATED_DIRS = (
  (Path("selfdrive/controls/lib/lateral_mpc_lib/c_generated_code"), "lat"),
  (Path("selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code"), "long"),
)


def get_mem_available_kb() -> int | None:
  try:
    with open("/proc/meminfo") as f:
      for line in f:
        if line.startswith("MemAvailable:"):
          return int(line.split()[1])
  except Exception:
    pass
  return None


def choose_agnos_build_attempts(nproc: int) -> list[int]:
  override = os.getenv("SP_BUILD_JOBS", "").strip()
  if override:
    attempts = [max(1, int(override))]
  else:
    attempts_env = os.getenv("SP_BUILD_ATTEMPTS", "").strip()
    if attempts_env:
      attempts = [max(1, int(part.strip())) for part in attempts_env.split(",") if part.strip()]
    else:
      max_jobs = max(1, int(os.getenv("SP_BUILD_MAX_JOBS", "7")))
      attempts = list(range(max_jobs, 0, -1))
  return list(dict.fromkeys(max(1, min(nproc, n)) for n in attempts))


def is_acados_pxd_stale(pxd_path: Path, model: str) -> bool:
  if not pxd_path.exists():
    return False
  try:
    contents = pxd_path.read_text()
  except OSError:
    return True
  required_tokens = (
    "nlp_solver_capsule",
    f'"{model}_acados_create_capsule"',
    f'"{model}_acados_free_capsule"',
  )
  return not all(token in contents for token in required_tokens)


def find_stale_acados_dirs(base_dir: Path) -> list[Path]:
  return [
    base_dir / relative_dir
    for relative_dir, model in ACADOS_GENERATED_DIRS
    if is_acados_pxd_stale(base_dir / relative_dir / "acados_solver.pxd", model)
  ]


def purge_acados_generated_dirs(base_dir: Path, directories: list[Path]) -> None:
  allowed_dirs = {(base_dir / relative_dir).resolve() for relative_dir, _model in ACADOS_GENERATED_DIRS}
  resolved_dirs = [directory.resolve() for directory in directories]
  if any(directory not in allowed_dirs for directory in resolved_dirs):
    raise ValueError("refusing to purge a non-acados generated directory")
  for directory in resolved_dirs:
    if directory.exists():
      shutil.rmtree(directory)


def is_cython_pxd_error(output: bytes) -> bool:
  if b"Error -9" in output:
    return False
  has_artifact = b"acados_solver.pxd" in output or b"acados_ocp_solver_pyx" in output
  has_signature = any(signature in output for signature in (
    b"Error compiling Cython file",
    b"is not a type identifier",
    b"cimported module has no attribute",
    b".pxd' not found",
    b'.pxd" not found',
  ))
  return has_artifact and has_signature


def run_with_acados_recovery(
  run_sequence: Callable[[], tuple[int, bytes]], base_dir: Path,
) -> tuple[int, bytes]:
  result = run_sequence()
  if result[0] == 0 or not is_cython_pxd_error(result[1]):
    return result

  cloudlog.error("acados Cython build failed; purging generated MPC code and retrying once\n" + result[1].decode("utf8", "replace"))
  print("Build recovery: acados Cython error detected, regenerating MPC code and retrying once")
  purge_acados_generated_dirs(base_dir, [base_dir / relative_dir for relative_dir, _model in ACADOS_GENERATED_DIRS])
  return run_sequence()


def build(spinner: Spinner, dirty: bool = False, minimal: bool = False) -> None:
  stale_acados_dirs = find_stale_acados_dirs(Path(BASEDIR))
  if stale_acados_dirs:
    cloudlog.warning(f"stale acados generated pxd detected: {stale_acados_dirs}")
    print("Build preflight: purging stale generated MPC code")
    purge_acados_generated_dirs(Path(BASEDIR), stale_acados_dirs)

  env = os.environ.copy()
  env['SCONS_PROGRESS'] = "1"
  nproc = os.cpu_count()
  if nproc is None:
    nproc = 2

  extra_args = ["--minimal"] if minimal else []

  if AGNOS:
    HARDWARE.set_power_save(False)
    os.sched_setaffinity(0, range(8))  # ensure we can use the isolcpus cores
    attempts = choose_agnos_build_attempts(nproc)
    mem_available_kb = get_mem_available_kb()
    attempts_s = ", ".join(f"-j{n}" for n in attempts)
    print(f"AGNOS build: attempts {attempts_s} (MemAvailable={mem_available_kb} kB)")
  else:
    attempts = [nproc, max(1, nproc // 2), 1]

  # Preserve order while de-duplicating.
  attempts = list(dict.fromkeys(max(1, int(n)) for n in attempts))

  # building with all cores can result in using too much memory,
  # so retry with less parallelism.
  compile_output: list[bytes] = []

  def run_scons(n: int, cache_args: list[str]) -> int:
    nonlocal compile_output, spinner, env
    scons: subprocess.Popen[bytes] = subprocess.Popen(["scons", f"-j{int(n)}", *cache_args, *extra_args], cwd=BASEDIR, env=env, stderr=subprocess.PIPE)
    assert scons.stderr is not None

    # Read progress from stderr and update spinner
    while scons.poll() is None:
      try:
        line = scons.stderr.readline()
        if line is None:
          continue
        line = line.rstrip()
        prefix = b'progress: '
        if line.startswith(prefix):
          i = int(line[len(prefix):])
          spinner.update_progress(MAX_BUILD_PROGRESS * min(1., i / TOTAL_SCONS_NODES), 100.)
        elif len(line):
          compile_output.append(line)
          print(line.decode('utf8', 'replace'))
      except Exception:
        pass

    if scons.returncode != 0 and scons.stderr is not None:
      compile_output += scons.stderr.read().split(b'\n')
    return scons.returncode

  def run_full_sequence() -> tuple[int, bytes]:
    last_rc = 1
    for n in attempts:
      compile_output.clear()
      last_rc = run_scons(n, ["--cache-populate"])
      if last_rc == 0:
        return 0, b"\n".join(compile_output)
      if AGNOS:
        blob = b"\n".join(compile_output)
        idx = attempts.index(n)
        if idx + 1 < len(attempts):
          nxt = attempts[idx + 1]
          if b"Error -9" in blob:
            cloudlog.warning(f"scons likely OOM-killed (Error -9), retrying with -j{nxt} after -j{n}")
            print(f"Build retry: detected Error -9 with -j{n}, retrying with -j{nxt}")
          else:
            cloudlog.warning(f"scons failed with -j{n}, retrying with -j{nxt}")
            print(f"Build retry: -j{n} failed, retrying with -j{nxt}")
          continue
        break

    if last_rc != 0:
      blob = b"\n".join(compile_output)
      if AGNOS and b"Error -9" in blob:
        cloudlog.warning("scons likely OOM-killed (Error -9), retrying with -j1 --cache-disable")
        print("Build retry: detected Error -9, retrying with -j1 --cache-disable")
        compile_output.clear()
        last_rc = run_scons(1, ["--cache-disable"])
    return last_rc, b"\n".join(compile_output)

  last_returncode, final_output = run_with_acados_recovery(run_full_sequence, Path(BASEDIR))

  if last_returncode != 0:
    # Build failed log errors
    error_s = final_output.decode('utf8', 'replace')
    add_file_handler(cloudlog)
    cloudlog.error("scons build failed\n" + error_s)

    # Show TextWindow
    spinner.close()
    if not os.getenv("CI"):
      with TextWindow("openpilot failed to build\n \n" + error_s) as t:
        t.wait_for_exit()
    exit(1)

  # enforce max cache size
  cache_files = [f for f in CACHE_DIR.rglob('*') if f.is_file()]
  cache_files.sort(key=lambda f: f.stat().st_mtime)
  cache_size = sum(f.stat().st_size for f in cache_files)
  for f in cache_files:
    if cache_size < MAX_CACHE_SIZE:
      break
    cache_size -= f.stat().st_size
    f.unlink()


if __name__ == "__main__":
  spinner = Spinner()
  spinner.update_progress(0, 100)
  build_metadata = get_build_metadata()
  build(spinner, build_metadata.openpilot.is_dirty, minimal = AGNOS)
