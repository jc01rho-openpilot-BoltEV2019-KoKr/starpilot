from collections import deque

import numpy as np
import pytest

import starpilot.system.speed_limit_vision as slv
from starpilot.system.speed_limit_vision import DetectorProposal, HistoryEntry, ProposalTrack, SpeedLimitVisionDaemon


def daemon_with_history(current_speed, entries):
  daemon = SpeedLimitVisionDaemon.__new__(SpeedLimitVisionDaemon)
  daemon.published_speed_limit_mph = current_speed
  daemon.history = deque(HistoryEntry(speed, confidence, float(index)) for index, (speed, confidence) in enumerate(entries))
  return daemon


def test_speed_change_requires_two_matching_reads_below_single_read_threshold():
  daemon = daemon_with_history(40, [(55, 0.82)])
  assert daemon._confirm_detection() is None

  daemon.history.append(HistoryEntry(55, 0.76, 1.0))
  assert daemon._confirm_detection() == pytest.approx((55, 0.82))


def test_speed_change_rejects_weak_confirming_read():
  daemon = daemon_with_history(40, [(35, 0.78), (35, 0.48)])
  assert daemon._confirm_detection() is None


def test_speed_change_accepts_single_high_confidence_read():
  daemon = daemon_with_history(40, [(55, 0.84)])
  assert daemon._confirm_detection() == pytest.approx((55, 0.84))


def test_speed_change_accepts_single_strong_consensus_read():
  daemon = daemon_with_history(70, [])
  daemon.history.append(HistoryEntry(60, 0.74, 1.0, strong_consensus=True))
  assert daemon._confirm_detection() == pytest.approx((60, 0.74))


def test_low_speed_change_requires_two_reads_below_low_speed_threshold():
  daemon = daemon_with_history(40, [(25, 0.89)])
  assert daemon._confirm_detection() is None

  daemon.history.append(HistoryEntry(25, 0.96, 1.0))
  assert daemon._confirm_detection() == pytest.approx((25, 0.96))


def test_low_speed_change_accepts_single_high_confidence_read():
  daemon = daemon_with_history(40, [(25, 0.91)])
  assert daemon._confirm_detection() == pytest.approx((25, 0.91))


def test_low_speed_change_accepts_single_strong_consensus_read():
  daemon = daemon_with_history(40, [])
  daemon.history.append(HistoryEntry(25, 0.95, 1.0, strong_consensus=True))
  assert daemon._confirm_detection() == pytest.approx((25, 0.95))


def test_low_speed_change_rejects_low_confidence_sequence():
  daemon = daemon_with_history(40, [(25, 0.82), (25, 0.88), (25, 0.89)])
  assert daemon._confirm_detection() is None


def textured_track_frame(offset_x=0, offset_y=0):
  frame = np.zeros((120, 180, 3), dtype=np.uint8)
  x1, y1, x2, y2 = 90 + offset_x, 30 + offset_y, 130 + offset_x, 90 + offset_y
  frame[y1:y2, x1:x2] = 220
  cv2 = pytest.importorskip("cv2")
  cv2.rectangle(frame, (x1 + 3, y1 + 3), (x2 - 3, y2 - 3), (20, 20, 20), 2)
  cv2.putText(frame, "55", (x1 + 5, y1 + 42), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (10, 10, 10), 2)
  return frame, (x1, y1, x2, y2)


def test_flow_track_bbox_follows_translation():
  cv2 = pytest.importorskip("cv2")
  first, bbox = textured_track_frame()
  second, expected_bbox = textured_track_frame(4, 3)
  first_gray = cv2.cvtColor(first, cv2.COLOR_BGR2GRAY)
  second_gray = cv2.cvtColor(second, cv2.COLOR_BGR2GRAY)
  points = SpeedLimitVisionDaemon._track_feature_points(first_gray, bbox)

  tracked_bbox, tracked_points = SpeedLimitVisionDaemon._flow_track_bbox(first_gray, second_gray, bbox, points)

  assert tracked_bbox == pytest.approx(expected_bbox, abs=1)
  assert tracked_points is not None and len(tracked_points) >= 4


def test_temporal_track_boosts_two_consistent_model_reads():
  cv2 = pytest.importorskip("cv2")
  frame, bbox = textured_track_frame()
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  points = SpeedLimitVisionDaemon._track_feature_points(gray, bbox)
  daemon = SpeedLimitVisionDaemon.__new__(SpeedLimitVisionDaemon)
  daemon.proposal_track = ProposalTrack(DetectorProposal(0.20, 0, bbox), bbox, gray, points, 0.0, 0.0)
  daemon.track_inference_count = 0
  daemon.track_failure_count = 0
  daemon.last_classifier_forward_count = 0
  daemon.last_classifier_forward_duration_s = 0.0
  daemon._classify_speed_limit_from_model = lambda _crop: (55, 0.90)
  daemon._is_regulatory_speed_sign = lambda _crop: True

  first = daemon._classify_proposal_track(frame, 0.2)
  second = daemon._classify_proposal_track(frame, 0.4)

  assert first.speed_limit_mph == 55
  assert second.speed_limit_mph == 55
  assert first.confidence < slv.CHANGE_SINGLE_READ_MIN_CONFIDENCE
  assert second.confidence >= slv.CHANGE_SINGLE_READ_MIN_CONFIDENCE
  assert daemon.track_inference_count == 2


def detector_classifier_daemon(*, regulatory: bool, model_read, bbox=(700, 100, 780, 220), proposal_confidence=0.80):
  daemon = SpeedLimitVisionDaemon.__new__(SpeedLimitVisionDaemon)
  daemon._collect_detector_classifier_proposals = lambda _frame: [(proposal_confidence, 0, bbox)]
  daemon._is_regulatory_speed_sign = lambda _crop: regulatory
  daemon._classify_speed_limit_from_model = model_read if callable(model_read) else lambda _crop: model_read
  daemon._read_speed_limit_from_crop = lambda _crop: pytest.fail("detector/classifier runtime must not call OCR")
  return daemon


@pytest.fixture
def model_only_runtime(monkeypatch):
  monkeypatch.setattr(slv, "DETECTOR_CLASSIFIER_CROP_OCR_ENABLED", False)


def test_detector_classifier_runtime_reads_regulatory_sign_without_ocr(model_only_runtime):
  daemon = detector_classifier_daemon(regulatory=True, model_read=(55, 0.99))
  detection = daemon._detect_sign_from_detector_classifier(np.zeros((480, 960, 3), dtype=np.uint8))

  assert detection is not None
  assert detection.speed_limit_mph == 55


def test_detector_classifier_marks_two_strong_model_crops_as_consensus(model_only_runtime):
  reads = iter(((20, 0.96), (20, 0.97), None))
  daemon = detector_classifier_daemon(regulatory=True, model_read=lambda _crop: next(reads), proposal_confidence=0.80)
  detection = daemon._detect_sign_from_detector_classifier(np.zeros((480, 960, 3), dtype=np.uint8))

  assert detection is not None
  assert detection.speed_limit_mph == 20
  assert detection.strong_consensus


def test_detector_classifier_runtime_rejects_single_untrusted_non_regulatory_model_read_without_ocr(model_only_runtime):
  reads = iter(((55, 0.99), None, None, None))
  daemon = detector_classifier_daemon(regulatory=False, model_read=lambda _crop: next(reads))
  detection = daemon._detect_sign_from_detector_classifier(np.zeros((480, 960, 3), dtype=np.uint8))

  assert detection is None


def test_detector_classifier_runtime_accepts_repeated_model_only_consensus_without_ocr(model_only_runtime):
  daemon = detector_classifier_daemon(regulatory=False, model_read=(60, 0.99))
  detection = daemon._detect_sign_from_detector_classifier(np.zeros((480, 960, 3), dtype=np.uint8))

  assert detection is not None
  assert detection.speed_limit_mph == 60


def test_detector_classifier_runtime_rejects_tiny_model_only_consensus_without_ocr(model_only_runtime):
  daemon = detector_classifier_daemon(
    regulatory=True,
    model_read=(40, 0.99),
    bbox=(700, 100, 720, 125),
    proposal_confidence=0.14,
  )
  detection = daemon._detect_sign_from_detector_classifier(np.zeros((480, 960, 3), dtype=np.uint8))

  assert detection is None
