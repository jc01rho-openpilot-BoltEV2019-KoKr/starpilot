#!/bin/sh
""":"
REPO_ROOT="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
PYTHON_BIN="$REPO_ROOT/.venv/bin/python"

if [ -x "$PYTHON_BIN" ]; then
  exec "$PYTHON_BIN" "$0" "$@"
fi

exec python3 "$0" "$@"
":"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from openpilot.tools.lib.logreader import LogReader, ReadMode


def main():
  if len(sys.argv) != 2:
    print("Usage: python auto_source.py <log_path>")
    sys.exit(1)

  log_path = sys.argv[1]
  lr = LogReader(log_path, default_mode=ReadMode.AUTO, sort_by_time=True)
  print("\n".join(lr.logreader_identifiers))


if __name__ == "__main__":
  main()
