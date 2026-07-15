from __future__ import annotations

import importlib.util
import sys

from pathlib import Path


def load_local_module(name: str):
  path = Path(__file__).resolve().with_name(f"{name}.py")
  spec = importlib.util.spec_from_file_location(f"test_local_{name}", path)
  assert spec is not None and spec.loader is not None
  module = importlib.util.module_from_spec(spec)
  sys.modules[spec.name] = module
  spec.loader.exec_module(module)
  return module


route_eval = load_local_module("evaluate_route_ground_truth")
GroundTruthEvent = route_eval.GroundTruthEvent


def test_clustered_runtime_events_collapses_same_value_burst():
  events = [
    {"event": "publish", "time_s": "10.0", "speedLimitMph": "35"},
    {"event": "publish", "time_s": "10.5", "speedLimitMph": "35"},
    {"event": "publish", "time_s": "11.0", "speedLimitMph": "45"},
  ]
  clusters = route_eval.clustered_runtime_events(events, "publish", 2.0)
  assert [route_eval.runtime_value(event) for event in clusters] == [35, 45]


def test_score_route_separates_candidate_publish_and_wrong_value():
  truth = [GroundTruthEvent("route", 10.0, 35, "regulatory", 40, "")]
  events = [
    {"event": "candidate", "time_s": "10.2", "candidateSpeedLimitMph": "35"},
    {"event": "publish", "time_s": "10.4", "speedLimitMph": "45"},
  ]
  rows, totals = route_eval.score_route(truth, events, 1.0, 2.0, 0.5)
  assert totals["candidate_hit"] == 1
  assert totals["publish_hit"] == 0
  assert totals["wrong_publish"] == 1
  assert totals["unmatched_publish_bursts"] == 1
  assert rows[0]["wrong_publish_values"] == "45"
