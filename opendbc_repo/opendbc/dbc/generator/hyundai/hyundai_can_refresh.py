#!/usr/bin/env python3
from pathlib import Path


GENERIC_LFAHDA = "BO_ 1157 LFAHDA_MFC: 4 XXX"
REFRESH_LFAHDA = "BO_ 1157 LFAHDA_MFC: 8 XXX"


def main() -> None:
  dbc_dir = Path(__file__).resolve().parents[2]
  source = dbc_dir / "hyundai_kia_generic.dbc"
  target = dbc_dir / "hyundai_can_refresh_generated.dbc"

  dbc = source.read_text(encoding="utf-8")
  if dbc.count(GENERIC_LFAHDA) != 1:
    raise RuntimeError(f"expected exactly one {GENERIC_LFAHDA!r} definition")

  target.write_text(dbc.replace(GENERIC_LFAHDA, REFRESH_LFAHDA, 1), encoding="utf-8")


if __name__ == "__main__":
  main()
