#!/usr/bin/env python3
import json

COUNTRY_PREFIX = "nation."
STATE_PREFIX = "us_state."

# Legacy C3 map selection stored bare region codes instead of the prefixed
# Keys consumed by mapd and the settings UIs.
US_STATE_CODES = frozenset({
  "AK", "AL", "AR", "AS", "AZ", "CA", "CO", "CT", "DC", "DE", "FL", "GA",
  "GU", "HI", "IA", "ID", "IL", "IN", "KS", "KY", "LA", "MA", "MD", "ME",
  "MI", "MN", "MO", "MP", "MS", "MT", "NC", "ND", "NE", "NH", "NJ", "NM",
  "NV", "NY", "OH", "OK", "OR", "PA", "PR", "RI", "SC", "SD", "TN", "TX",
  "UT", "VA", "VI", "WA", "WI", "WV", "WY",
})

COUNTRY_CODES = frozenset({
  "AF", "AL", "AM", "AO", "AQ", "AR", "AT", "AU", "AZ", "BA", "BD", "BE",
  "BF", "BG", "BH", "BI", "BJ", "BN", "BO", "BR", "BS", "BT", "BW", "BY",
  "BZ", "CA", "CD", "CF", "CG", "CH", "CI", "CL", "CM", "CN", "CO", "CR",
  "CU", "CY", "CZ", "DE", "DJ", "DK", "DO", "DZ", "EC", "EE", "EG", "ER",
  "ES", "ET", "FJ", "FK", "FR", "GA", "GB", "GD", "GE", "GH", "GL", "GM",
  "GN", "GQ", "GR", "GT", "GU", "GW", "GY", "HK", "HN", "HR", "HT", "HU",
  "ID", "IE", "IL", "IN", "IQ", "IR", "IS", "IT", "JM", "JO", "JP", "KE",
  "KG", "KH", "KM", "KP", "KR", "KW", "KZ", "LA", "LB", "LK", "LR", "LS",
  "LT", "LU", "LV", "LY", "MA", "MC", "MD", "ME", "MG", "MK", "ML", "MM",
  "MN", "MO", "MR", "MS", "MT", "MV", "MW", "MX", "MY", "MZ", "NA", "NC",
  "NE", "NG", "NI", "NL", "NO", "NP", "NZ", "OM", "PA", "PE", "PG", "PH",
  "PK", "PL", "PS", "PT", "PY", "QA", "RO", "RS", "RU", "RW", "SA", "SB",
  "SC", "SD", "SE", "SG", "SI", "SK", "SL", "SN", "SO", "SR", "SS", "SV",
  "SY", "SZ", "TD", "TF", "TG", "TH", "TJ", "TL", "TM", "TN", "TR", "TT",
  "TW", "TZ", "UA", "UG", "US", "UY", "UZ", "VE", "VN", "VU", "YE", "ZA",
  "ZM", "ZW",
})

LEGACY_AMBIGUOUS_CODES = COUNTRY_CODES & US_STATE_CODES


def _normalize_json_selection(selected_raw: str) -> str | None:
  try:
    data = json.loads(selected_raw)
  except (json.JSONDecodeError, TypeError, ValueError):
    return None

  if not isinstance(data, dict):
    return None

  normalized = []
  for nation in data.get("nations", []):
    normalized.append(f"{COUNTRY_PREFIX}{nation}")
  for state in data.get("states", []):
    normalized.append(f"{STATE_PREFIX}{state}")

  return ",".join(sorted(dict.fromkeys(normalized)))


def normalize_map_token(token: str) -> str | None:
  token = token.strip()
  if not token:
    return None

  if token.startswith(COUNTRY_PREFIX) or token.startswith(STATE_PREFIX):
    return token

  if token in US_STATE_CODES and token not in COUNTRY_CODES:
    return f"{STATE_PREFIX}{token}"
  if token in COUNTRY_CODES and token not in US_STATE_CODES:
    return f"{COUNTRY_PREFIX}{token}"
  if token in LEGACY_AMBIGUOUS_CODES:
    # Old C3 selections are ambiguous for a handful of bare codes like CA/IN.
    # Prefer U.S. states here so the common state-download flow keeps working;
    # users who intended the country can reselect once in the fixed UI.
    return f"{STATE_PREFIX}{token}"

  return None


def normalize_maps_selected(selected_raw: str | bytes | None) -> str:
  if isinstance(selected_raw, bytes):
    selected_raw = selected_raw.decode("utf-8", errors="ignore")
  if not selected_raw:
    return ""

  json_normalized = _normalize_json_selection(selected_raw)
  if json_normalized is not None:
    return json_normalized

  normalized = []
  seen = set()
  for token in selected_raw.split(","):
    normalized_token = normalize_map_token(token)
    if normalized_token is not None and normalized_token not in seen:
      normalized.append(normalized_token)
      seen.add(normalized_token)

  normalized.sort()
  return ",".join(normalized)
