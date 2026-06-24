#!/usr/bin/env python3
import datetime
import shutil
import tarfile
import zstandard as zstd

from pathlib import Path

from openpilot.common.basedir import BASEDIR
from openpilot.common.params import Params
from openpilot.system.hardware.hw import Paths

from openpilot.starpilot.common.starpilot_utilities import delete_file
from openpilot.starpilot.common.starpilot_variables import EXCLUDED_KEYS, STARPILOT_BACKUPS, TOGGLE_BACKUPS


MINIMUM_BACKUP_FREE_BYTES = 2 * 1024 * 1024 * 1024
EXCLUDED_BACKUP_DIRS = frozenset({
  ".git",
  ".mypy_cache",
  ".pytest_cache",
  ".venv",
  "__pycache__",
})
EXCLUDED_BACKUP_SUFFIXES = frozenset({".a", ".o", ".pyc", ".pyo", ".so"})


def backup_tar_filter(tarinfo):
  path = Path(tarinfo.name)
  if any(part in EXCLUDED_BACKUP_DIRS for part in path.parts):
    return None

  if path.suffix in EXCLUDED_BACKUP_SUFFIXES:
    return None

  return tarinfo


def get_directory_size(path):
  total_size = 0
  for child in path.rglob("*"):
    if not child.is_file() or child.is_symlink():
      continue

    relative_path = Path(path.name) / child.relative_to(path)
    tarinfo = tarfile.TarInfo(str(relative_path))
    if backup_tar_filter(tarinfo) is None:
      continue

    try:
      total_size += child.stat().st_size
    except OSError:
      continue

  return total_size


def backup_starpilot(build_metadata, params):
  maximum_backups = 3
  cleanup_backups(STARPILOT_BACKUPS, maximum_backups)

  today = datetime.datetime.now().date()
  for backup in STARPILOT_BACKUPS.glob("*_auto.tar.zst"):
    if backup.name.endswith(f"_{build_metadata.channel}_auto.tar.zst"):
      if datetime.datetime.fromtimestamp(backup.stat().st_mtime).date() == today:
        if not backup.name.startswith(f"{build_metadata.openpilot.git_commit[:6]}_"):
          delete_file(backup, report=False)

  _, _, free = shutil.disk_usage(STARPILOT_BACKUPS)
  backup_source = Path(BASEDIR)
  minimum_backup_size = params.get_int("MinimumBackupSize", return_default=True, default=0)
  estimated_backup_size = minimum_backup_size or get_directory_size(backup_source)
  required_free = max(estimated_backup_size * maximum_backups, MINIMUM_BACKUP_FREE_BYTES)
  if free <= required_free:
    print("Insufficient free space for automatic StarPilot backup. Aborting...")
    return

  destination = STARPILOT_BACKUPS / f"{build_metadata.openpilot.git_commit}_{build_metadata.channel}_auto"
  create_backup(
    backup_source,
    destination,
    "Successfully backed up StarPilot!",
    "Failed to backup StarPilot...",
    params,
    estimated_backup_size,
    compressed=True,
  )


def backup_toggles(params, boot_run=False):
  params_backup = Params(f"{Paths.shm_path()}/params_backup", return_defaults=True)

  changes_found = False
  for key in params.all_keys():
    current_value = params.get(key)
    if current_value is None:
      continue

    if boot_run:
      params_backup.put(key, current_value)
      changes_found = True
    elif current_value != params_backup.get(key):
      params_backup.put(key, current_value)
      changes_found |= key.decode("utf-8") not in EXCLUDED_KEYS

  maximum_backups = 5
  cleanup_backups(TOGGLE_BACKUPS, maximum_backups)

  if not changes_found or boot_run:
    if not changes_found:
      print("Toggles are identical to the previous backup. Aborting...")
    return

  params.put_bool("GalaxyUploadPending", True)

  destination = TOGGLE_BACKUPS / f"{datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')}_auto"
  create_backup(Path(params_backup.get_param_path()), destination, "Successfully backed up toggles!", "Failed to backup toggles...", params)


def cleanup_backups(directory, limit):
  directory.mkdir(parents=True, exist_ok=True)

  for backup in directory.glob("*_in_progress*"):
    delete_file(backup, report=False)

  backups = sorted(directory.glob("*_auto*"), key=lambda f: f.stat().st_mtime, reverse=True)
  for oldest_backup in backups[limit:]:
    delete_file(oldest_backup, report=False)


def create_backup(backup, destination, success_message, fail_message, params, minimum_backup_size=0, compressed=False):
  final_destination = destination.parent / f"{destination.name}.tar.zst" if compressed else destination

  if final_destination.exists():
    print("Backup already exists. Aborting...")
    return

  if compressed:
    compressed_temp = destination.parent / f"{destination.name}_in_progress.tar.zst"

    backup_error = None

    with open(compressed_temp, "wb") as f_out:
      cctx = zstd.ZstdCompressor()
      with cctx.stream_writer(f_out) as compressor:
        with tarfile.open(fileobj=compressor, mode="w") as tar:
          try:
            tar.add(backup, arcname=destination.name, filter=backup_tar_filter)
          except OSError as error:
            backup_error = error

    if backup_error is not None:
      delete_file(compressed_temp, report=False)
      print(f"{fail_message} {backup_error}")
      return

    compressed_temp.rename(final_destination)

    compressed_backup_size = final_destination.stat().st_size
    params.put_int("MinimumBackupSize", compressed_backup_size)
  else:
    in_progress_destination = destination.parent / f"{destination.name}_in_progress"

    shutil.copytree(backup, in_progress_destination, symlinks=True)

    in_progress_destination.rename(destination)

  print(success_message)
