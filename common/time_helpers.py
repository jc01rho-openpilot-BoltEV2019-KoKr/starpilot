import datetime
from pathlib import Path

MIN_DATE = datetime.datetime(year=2025, month=2, day=21)
MAX_DATE = datetime.datetime(year=2035, month=1, day=1)

def _utc_now_naive():
  return datetime.datetime.now(datetime.UTC).replace(tzinfo=None)

def min_date():
  # on systemd systems, the default time is the systemd build time
  systemd_path = Path("/lib/systemd/systemd")
  if systemd_path.exists():
    d = datetime.datetime.fromtimestamp(systemd_path.stat().st_mtime, datetime.UTC).replace(tzinfo=None)
    return max(MIN_DATE, d + datetime.timedelta(days=1))
  return MIN_DATE

def system_time_valid():
  return min_date() < _utc_now_naive() < MAX_DATE
