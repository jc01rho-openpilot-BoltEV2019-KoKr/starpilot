"""Runner orchestration tests: no native libraries, route downloads, or vehicle IO."""
import importlib.util
import json
from pathlib import Path
import sys
from types import SimpleNamespace

import pytest


@pytest.fixture
def runner():
  spec = importlib.util.spec_from_file_location("fleet_safety_runner_test", Path(__file__).with_name("fleet_safety.py"))
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


def test_inventory_missing_route_remains_uncovered(runner, monkeypatch):
  monkeypatch.setitem(sys.modules, "opendbc.car.values", SimpleNamespace(PLATFORMS={"covered": None, "exempt": None, "missing": None}))
  monkeypatch.setitem(sys.modules, "opendbc.car.tests.routes", SimpleNamespace(
    routes=[SimpleNamespace(car_model="covered", route="route-a", segment=2)], non_tested_cars=["exempt"]))
  entries = {entry["platform"]: entry for entry in runner.inventory()}
  assert entries["covered"]["status"] == "pending"
  assert entries["covered"]["routes"] == [{"route": "route-a", "segment": 2}]
  assert entries["exempt"]["declared_without_route"]
  assert entries["exempt"]["status"] == "uncovered"
  assert entries["missing"]["status"] == "uncovered"


def configure_main(runner, monkeypatch, tmp_path, routes):
  monkeypatch.setattr(sys, "argv", ["fleet_safety", "--all", "--scenario", "recorded", "--out", str(tmp_path)])
  monkeypatch.setattr(runner, "inventory", lambda: [dict(platform="test-platform", routes=routes,
                                                        declared_without_route=False, status="pending" if routes else "uncovered")])
  monkeypatch.setattr(runner, "build_safety", lambda *args: tmp_path / "mock-safety")


def test_missing_route_fails_run(runner, monkeypatch, tmp_path):
  configure_main(runner, monkeypatch, tmp_path, [])
  (tmp_path / "results.json").write_text(json.dumps(dict(cases=[], counts={"pass": 1})))
  monkeypatch.setattr(runner.subprocess, "run", lambda *args, **kwargs: pytest.fail("No route may launch a worker"))
  assert runner.main() == 1
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {"uncovered": 1}


def test_failed_build_cannot_leave_stale_pass(runner, monkeypatch, tmp_path):
  configure_main(runner, monkeypatch, tmp_path, [])
  (tmp_path / "results.json").write_text(json.dumps(dict(cases=[], counts={"pass": 1})))

  def failed_build(*args):
    raise OSError("compiler unavailable")

  monkeypatch.setattr(runner, "build_safety", failed_build)
  assert runner.main() == 1
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {"error": 1}
  assert report["cases"][0]["reason"] == "Safety build failed"


@pytest.mark.parametrize("status,returncode,expected", [
  ("pass", 0, 0), ("failed", 1, 1), ("uncovered", 1, 1), ("error", 1, 1),
])
def test_worker_status_controls_overall_result(runner, monkeypatch, tmp_path, status, returncode, expected):
  configure_main(runner, monkeypatch, tmp_path, [dict(route="registered-route", segment=2)])

  def worker(command, **kwargs):
    path = Path(command[command.index("--worker") + 1])
    case = json.loads(path.read_text())
    path.with_suffix(".result.json").write_text(json.dumps(dict(status=status, execution_id=case["execution_id"])))
    return SimpleNamespace(returncode=returncode)

  monkeypatch.setattr(runner.subprocess, "run", worker)
  assert runner.main() == expected
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {status: 1}


def test_crashed_worker_cannot_reuse_previous_pass(runner, monkeypatch, tmp_path):
  configure_main(runner, monkeypatch, tmp_path, [dict(route="new-route", segment=2)])
  (tmp_path / "case_0000.result.json").write_text(json.dumps(dict(status="pass", route="old-route")))
  monkeypatch.setattr(runner.subprocess, "run", lambda *args, **kwargs: SimpleNamespace(returncode=1))
  assert runner.main() == 1
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {"error": 1}


def test_worker_nonzero_exit_cannot_report_pass(runner, monkeypatch, tmp_path):
  configure_main(runner, monkeypatch, tmp_path, [dict(route="registered-route", segment=2)])

  def worker(command, **kwargs):
    path = Path(command[command.index("--worker") + 1])
    case = json.loads(path.read_text())
    path.with_suffix(".result.json").write_text(json.dumps(dict(status="pass", execution_id=case["execution_id"])))
    return SimpleNamespace(returncode=1)

  monkeypatch.setattr(runner.subprocess, "run", worker)
  assert runner.main() == 1


def test_wrong_execution_identity_cannot_report_pass(runner, monkeypatch, tmp_path):
  configure_main(runner, monkeypatch, tmp_path, [dict(route="registered-route", segment=2)])

  def worker(command, **kwargs):
    path = Path(command[command.index("--worker") + 1])
    path.with_suffix(".result.json").write_text(json.dumps(dict(status="pass", execution_id="other-run")))
    return SimpleNamespace(returncode=0)

  monkeypatch.setattr(runner.subprocess, "run", worker)
  assert runner.main() == 1
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {"error": 1}


def test_checked_in_baseline_loads_cleanly(runner):
  baseline_path = Path(__file__).with_name("fleet_safety_baseline.json")
  cases = runner.load_baseline(baseline_path)
  assert len(cases) >= 600


def test_invalid_baseline_fails_before_build_and_clears_stale_pass(runner, monkeypatch, tmp_path):
  bad_baseline = tmp_path / "missing_baseline.json"
  monkeypatch.setattr(sys, "argv", ["fleet_safety", "--all", "--out", str(tmp_path), "--baseline", str(bad_baseline)])
  monkeypatch.setattr(runner, "inventory", lambda: [dict(platform="p", routes=[], declared_without_route=True, status="uncovered")])
  monkeypatch.setattr(runner, "build_safety", lambda *args: pytest.fail("build_safety must not run when baseline fails to load"))
  (tmp_path / "results.json").write_text(json.dumps(dict(cases=[], counts={"pass": 1})))
  assert runner.main() == 1
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {"error": 1}
  assert report["cases"][0]["reason"] == "Baseline load failed"


def test_baseline_passes_matching_known_non_pass_and_preserves_raw_counts(runner, monkeypatch, tmp_path):
  baseline_path = tmp_path / "baseline.json"
  baseline_path.write_text(json.dumps({
    "schema_version": 1,
    "cases": {
      "no-route-car": {"status": "uncovered", "reason": "No registered route"},
      "err-car|abcd/2021-01-01||recorded": {"status": "error", "error_kind": "Fixture identity mismatch"},
      "fail-car|efgh/2022-02-02|2|recorded": {"status": "failed"},
      "pass-car|ijkl/2023-03-03||recorded": {"status": "pass"},
    },
  }))
  monkeypatch.setattr(sys, "argv", [
    "fleet_safety", "--all", "--scenario", "recorded", "--out", str(tmp_path), "--baseline", str(baseline_path),
  ])
  monkeypatch.setattr(runner, "inventory", lambda: [
    dict(platform="no-route-car", routes=[], declared_without_route=False, status="uncovered"),
    dict(platform="err-car", routes=[dict(route="abcd/2021-01-01", segment=None)], declared_without_route=False, status="pending"),
    dict(platform="fail-car", routes=[dict(route="efgh/2022-02-02", segment=2)], declared_without_route=False, status="pending"),
    dict(platform="pass-car", routes=[dict(route="ijkl/2023-03-03", segment=None)], declared_without_route=False, status="pending"),
    dict(platform="new-unlisted-no-route", routes=[], declared_without_route=True, status="uncovered"),
  ])
  monkeypatch.setattr(runner, "build_safety", lambda *args: tmp_path / "mock-safety")

  def worker(command, **kwargs):
    path = Path(command[command.index("--worker") + 1])
    case = json.loads(path.read_text())
    if case["platform"] == "err-car":
      res = dict(status="error", error="ValueError('Fixture identity mismatch: MOCK != err-car')")
    elif case["platform"] == "fail-car":
      res = dict(status="failed", route="efgh/2022-02-02/2", errors=[],
                 panda_results={"0": {"status": "failed", "unexpected_acceptances": 0, "hook_errors": 0}})
    else:
      res = dict(status="pass", route="ijkl/2023-03-03/2")
    res["execution_id"] = case["execution_id"]
    path.with_suffix(".result.json").write_text(json.dumps(res))
    return SimpleNamespace(returncode=0 if res["status"] == "pass" else 1)

  monkeypatch.setattr(runner.subprocess, "run", worker)
  assert runner.main() == 0
  report = json.loads((tmp_path / "results.json").read_text())
  assert report["counts"] == {"uncovered": 2, "error": 1, "failed": 1, "pass": 1}
  assert report["baseline"]["regression_count"] == 0
  assert report["baseline"]["new_uncovered"] == ["new-unlisted-no-route"]


@pytest.mark.parametrize("baseline_entry,current_item,should_regress", [
  ({"status": "pass"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "failed"}, True),
  ({"status": "pass"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "uncovered"}, True),
  ({"status": "pass"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "error", "error": "LogsUnavailable"}, True),
  ({"status": "uncovered"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "failed"}, True),
  ({"status": "uncovered"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "pass"}, False),
  ({"status": "failed"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "error", "error": "TypeError('boom')"}, True),
  ({"status": "failed"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "failed",
                          "panda_results": {"0": {"unexpected_acceptances": 1, "hook_errors": 0}}}, True),
  ({"status": "failed"}, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "failed",
                          "errors": ["Unconfigured outgoing bus 8"]}, True),
  ({"status": "error", "error_kind": "Fixture identity mismatch"},
   {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "error",
    "error": "RuntimeError('Safety configuration unavailable')"}, True),
  (None, {"platform": "p", "registered_route": "r/t", "segment": None, "scenario": "recorded", "status": "failed"}, True),
])
def test_evaluate_baseline_transitions(runner, baseline_entry, current_item, should_regress):
  baseline = {} if baseline_entry is None else {"p|r/t||recorded": baseline_entry}
  summary = runner.evaluate_baseline([current_item], baseline)
  assert (summary["regression_count"] > 0) is should_regress

