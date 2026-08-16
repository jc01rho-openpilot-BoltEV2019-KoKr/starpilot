import pytest

from openpilot.starpilot.common import cpu_throttle


def test_offline_cpu_placeholders_do_not_hide_sustained_load(monkeypatch):
  monkeypatch.setattr(cpu_throttle, "_online_cpu_count", lambda: 4)

  usage = cpu_throttle._online_cpu_usage([80, 80, 80, 80, 0, 0, 0, 0])
  average = sum(usage) / len(usage)

  assert usage == [80.0, 80.0, 80.0, 80.0]
  assert cpu_throttle._compute_throttle_factor(average, 0) == pytest.approx(1.75)


def test_idle_reserved_cores_do_not_hide_affinity_core_saturation(monkeypatch):
  monkeypatch.setattr(cpu_throttle, "_online_cpu_count", lambda: 8)

  usage = cpu_throttle._online_cpu_usage([74, 82, 100, 85, 92, 98, 0, 47], cores=[2])

  assert usage == [100.0]
  assert cpu_throttle._compute_throttle_factor(sum(usage) / len(usage), 1) == 4.0


@pytest.mark.parametrize(("online_spec", "expected"), (
  ("0-3", 4),
  ("0-3,6-7", 6),
))
def test_online_cpu_count_parser(monkeypatch, tmp_path, online_spec, expected):
  online_path = tmp_path / "online"
  online_path.write_text(online_spec, encoding="utf-8")
  monkeypatch.setattr(cpu_throttle, "Path", lambda _: online_path)
  cpu_throttle._online_cpu_count.cache_clear()

  assert cpu_throttle._online_cpu_count() == expected
