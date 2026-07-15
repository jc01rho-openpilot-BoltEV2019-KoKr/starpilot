import importlib.util

import pytest

from argparse import Namespace
from pathlib import Path


def load_local_module(name: str):
  path = Path(__file__).resolve().with_name(f"{name}.py")
  spec = importlib.util.spec_from_file_location(f"test_local_{name}", path)
  assert spec is not None and spec.loader is not None
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


import_queue = load_local_module("import_manual_review_queue")
build_review_classifier = load_local_module("build_review_classifier_dataset")
select_queue = load_local_module("select_manual_review_queue")
compare_queues = load_local_module("compare_manual_review_queues")
rescore_queue = load_local_module("rescore_manual_review_queue")
is_classifier_reject = import_queue.is_classifier_reject
split_for_key = import_queue.split_for_key
split_group_key = import_queue.split_group_key
select_rows = select_queue.select_rows


def review_row(key: str, route: str, speed: int, priority: float) -> dict[str, str]:
  return {
    "record_key": key,
    "route": route,
    "detector_class": "regulatory_speed_limit",
    "candidate_speed_limit_mph": str(speed),
    "review_priority": str(priority),
    "proposal_confidence": "0.8",
    "candidate_confidence": "0.99",
  }


def test_review_selection_balances_routes_and_speeds():
  rows = [
    *(review_row(f"a-{index}", "route-a", 30, 10 - index) for index in range(5)),
    *(review_row(f"b-{index}", "route-b", 65, 10 - index) for index in range(5)),
  ]
  args = Namespace(
    max_rows=4,
    max_per_route=2,
    max_per_speed=2,
    max_no_read=2,
    max_school=2,
    max_advisory=2,
  )

  selected = select_rows(rows, args)

  assert len(selected) == 4
  assert sum(row["route"] == "route-a" for row in selected) == 2
  assert sum(row["route"] == "route-b" for row in selected) == 2


def test_review_selection_prioritizes_model_disagreements():
  unchanged = review_row("unchanged", "route-a", 30, 5.0)
  changed = {**review_row("changed", "route-a", 30, 2.0), "comparison_change": "value_changed"}
  args = Namespace(max_rows=1, max_per_route=2, max_per_speed=2, max_no_read=2, max_school=2, max_advisory=2)

  assert select_rows([unchanged, changed], args)[0]["record_key"] == "changed"


def test_review_selection_deduplicates_adjacent_same_speed_frames():
  first = {**review_row("first", "route-a", 40, 5.0), "segment": "1", "frame_time_s": "10.0"}
  duplicate = {**review_row("duplicate", "route-a", 40, 4.0), "segment": "1", "frame_time_s": "11.0"}
  different_speed = {**review_row("different", "route-a", 45, 3.0), "segment": "1", "frame_time_s": "11.0"}
  args = Namespace(
    max_rows=3,
    max_per_route=3,
    max_per_speed=3,
    max_no_read=3,
    max_school=3,
    max_advisory=3,
    min_seconds_per_route_speed=3.0,
  )

  selected_keys = {row["record_key"] for row in select_rows([first, duplicate, different_speed], args)}
  assert selected_keys == {"first", "different"}


def test_lost_reads_remain_balanced_by_previous_speed():
  row = {
    **review_row("lost", "route-a", 0, 5.0),
    "candidate_speed_limit_mph": "",
    "before_speed_limit_mph": "55",
    "comparison_change": "lost_read",
  }

  assert select_queue.predicted_speed(row) == 55
  assert select_queue.bucket_name(row) == "speed_55"


def test_primary_speed_limits_override_general_limit():
  rows = [
    *(review_row(f"primary-{index}", f"route-p-{index}", 40, 10 - index) for index in range(3)),
    *(review_row(f"low-{index}", f"route-l-{index}", 15, 10 - index) for index in range(3)),
  ]
  args = Namespace(
    max_rows=6,
    max_per_route=1,
    max_per_speed=1,
    max_primary_speed=3,
    max_speed_20=2,
    max_no_read=1,
    max_school=1,
    max_advisory=1,
    min_seconds_per_route_speed=0.0,
  )

  selected = select_rows(rows, args)
  assert sum(select_queue.predicted_speed(row) == 40 for row in selected) == 3
  assert sum(select_queue.predicted_speed(row) == 15 for row in selected) == 1


def test_manual_import_splits_adjacent_frames_by_route():
  rows = [{"record_key": f"frame-{index}", "route": "dongle/route"} for index in range(8)]
  splits = {split_for_key(split_group_key(row), 5, 0) for row in rows}

  assert len(splits) == 1


def test_only_reviewed_proposal_crops_become_classifier_rejects(tmp_path):
  crop_path = tmp_path / "crop.jpg"
  crop_path.write_bytes(b"crop")
  row = {
    "review_status": "ignore",
    "review_sign_type": "not_speed_limit",
    "detector_class": "regulatory_speed_limit",
    "crop_path": str(crop_path),
  }

  assert is_classifier_reject(row)
  assert not is_classifier_reject({**row, "detector_class": "negative_empty"})
  assert not is_classifier_reject({**row, "review_status": "uncertain"})


def test_advisory_positive_is_a_runtime_negative(tmp_path):
  crop_path = tmp_path / "crop.jpg"
  frame_path = tmp_path / "frame.jpg"
  crop_path.write_bytes(b"crop")
  frame_path.write_bytes(b"frame")
  row = {
    "record_key": "advisory",
    "review_status": "corrected",
    "review_sign_type": "advisory",
    "review_speed_limit_mph": "40",
    "crop_path": str(crop_path),
    "frame_path": str(frame_path),
  }

  assert import_queue.is_advisory_positive(row)
  runtime_row = import_queue.runtime_row(row, "val", "advisory_negative")
  assert runtime_row["sample_type"] == "advisory_negative"
  assert runtime_row["speed_limit_mph"] == 40
  assert build_review_classifier.is_advisory(row)
  assert build_review_classifier.keep_advisory_reject({**row, "split": "val"}, 0.0)
  assert not build_review_classifier.keep_advisory_reject({**row, "split": "train"}, 0.0)


def test_queue_comparison_distinguishes_gained_lost_and_changed_reads():
  no_read = {"candidate_speed_limit_mph": "", "candidate_confidence": ""}
  speed_20 = {"candidate_speed_limit_mph": "20", "candidate_confidence": "0.99"}
  speed_30 = {"candidate_speed_limit_mph": "30", "candidate_confidence": "0.98"}

  assert compare_queues.classify_change(no_read, speed_20, 0.05) == "gained_read"
  assert compare_queues.classify_change(speed_20, no_read, 0.05) == "lost_read"
  assert compare_queues.classify_change(speed_20, speed_30, 0.05) == "value_changed"
  assert compare_queues.classify_change(speed_20, {**speed_20, "candidate_confidence": "0.97"}, 0.05) == ""


def test_rescore_row_preserves_before_values_and_marks_gained_read(tmp_path):
  crop_path = tmp_path / "crop.jpg"
  import cv2
  import numpy as np
  cv2.imwrite(str(crop_path), np.zeros((32, 32, 3), dtype=np.uint8))
  daemon = type("Daemon", (), {"_classify_speed_limit_from_model": lambda self, crop: (20, 0.99)})()
  row = {
    "record_key": "candidate",
    "crop_path": str(crop_path),
    "candidate_speed_limit_mph": "",
    "candidate_confidence": "",
  }

  rescored = rescore_queue.rescore_row(row, daemon, "model", 0.05)

  assert rescored["before_speed_limit_mph"] == ""
  assert rescored["candidate_speed_limit_mph"] == "20"
  assert rescored["comparison_change"] == "gained_read"


def test_corrected_bbox_regenerates_classifier_crop(tmp_path):
  import cv2
  import numpy as np

  frame_path = tmp_path / "frame.jpg"
  original_crop_path = tmp_path / "original_crop.jpg"
  frame = np.zeros((100, 200, 3), dtype=np.uint8)
  frame[20:80, 60:140] = 255
  cv2.imwrite(str(frame_path), frame)
  cv2.imwrite(str(original_crop_path), np.zeros((20, 20, 3), dtype=np.uint8))
  row = {
    "record_key": "corrected-box",
    "frame_path": str(frame_path),
    "crop_path": str(original_crop_path),
    "bbox": "0,0,20,20",
    "crop_bbox": "0,0,24,24",
    "review_bbox": "60,20,140,80",
  }

  crop_path, crop_bbox, corrected = import_queue.corrected_classifier_crop(row, tmp_path, overwrite=False)
  crop = cv2.imread(crop_path)

  assert corrected
  assert crop is not None and crop.shape[:2] == (72, 96)
  assert crop.mean() > 150
  assert crop_bbox == "52,14,148,86"


def test_corrected_bbox_requires_readable_source_frame(tmp_path):
  row = {
    "record_key": "missing-corrected-box-frame",
    "frame_path": str(tmp_path / "missing-frame.jpg"),
    "crop_path": str(tmp_path / "original-crop.jpg"),
    "bbox": "0,0,20,20",
    "crop_bbox": "0,0,24,24",
    "review_bbox": "60,20,140,80",
  }

  with pytest.raises(RuntimeError, match="unreadable frame"):
    import_queue.corrected_classifier_crop(row, tmp_path, overwrite=False)


def test_corrected_record_removes_inherited_classifier_sample(tmp_path):
  stale = tmp_path / "train" / "55" / "base_review_bad_record_key_hash.jpg"
  retained = tmp_path / "train" / "55" / "base_review_other_record_hash.jpg"
  stale.parent.mkdir(parents=True)
  stale.write_bytes(b"stale")
  retained.write_bytes(b"retained")

  removed = build_review_classifier.remove_inherited_records(tmp_path, ["bad:record/key"])

  assert removed == 1
  assert not stale.exists()
  assert retained.exists()


def test_reject_repeat_spec_preserves_record_key_punctuation():
  counts = build_review_classifier.parse_reject_repeat_counts(["route/sign=track:55=32"])

  assert counts == {"route/sign=track:55": 32}

  with pytest.raises(ValueError, match="at least 1"):
    build_review_classifier.parse_reject_repeat_counts(["bad-record=0"])


def test_conditional_reject_generates_runtime_crop_expansions(tmp_path):
  import cv2
  import numpy as np

  frame_path = tmp_path / "frame.jpg"
  crop_path = tmp_path / "crop.jpg"
  frame = np.zeros((100, 200, 3), dtype=np.uint8)
  cv2.imwrite(str(frame_path), frame)
  cv2.imwrite(str(crop_path), frame[20:80, 60:140])
  row = {
    "record_key": "conditional-sign",
    "frame_path": str(frame_path),
    "crop_path": str(crop_path),
    "bbox": "60,20,140,80",
    "review_bbox": "60,20,140,80",
    "review_ignore_reason": "conditional_restriction",
  }

  rows = import_queue.classifier_reject_variant_rows(row, "train", tmp_path, overwrite=False)

  assert len(rows) == 4
  assert rows[1]["crop_bbox"] == "60,20,140,80"
  assert rows[2]["crop_bbox"] == "52,16,148,87"
  assert rows[3]["crop_bbox"] == "60,20,154,90"
  assert all(Path(variant["crop_path"]).is_file() for variant in rows)
