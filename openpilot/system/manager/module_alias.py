"""Module name compatibility for installs that span the move of the top level packages into openpilot/."""

import importlib
import importlib.util

LEGACY_PACKAGES = ('cereal', 'common', 'selfdrive', 'starpilot', 'system', 'tools')


def legacy_alias(proc: str) -> str | None:
  top, sep, _ = proc.partition('.')
  if not sep or top not in LEGACY_PACKAGES:
    return None

  alias = f'openpilot.{proc}'
  try:
    found = importlib.util.find_spec(alias)
  except (ImportError, ValueError):
    return None
  return alias if found is not None else None


def import_process_module(proc: str):
  try:
    return importlib.import_module(proc)
  except ModuleNotFoundError as e:
    if e.name is not None and proc != e.name and not proc.startswith(f'{e.name}.'):
      raise
    alias = legacy_alias(proc)
    if alias is None:
      raise
    return importlib.import_module(alias)
