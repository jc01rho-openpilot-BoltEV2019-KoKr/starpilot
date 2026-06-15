from __future__ import annotations


def parse_model_version(version: str | None) -> int | None:
  text = str(version or "").strip().lower()
  if not text.startswith("v"):
    return None

  raw_number = text[1:]
  if not raw_number.isdigit():
    return None
  return int(raw_number)


def is_tinygrad_model_version(version: str | None) -> bool:
  parsed = parse_model_version(version)
  return parsed is not None and parsed >= 8


def uses_split_off_policy_artifacts(version: str | None) -> bool:
  parsed = parse_model_version(version)
  return parsed is not None and 12 <= parsed < 16


def uses_combined_driving_artifacts(version: str | None) -> bool:
  parsed = parse_model_version(version)
  return parsed is not None and parsed >= 16
