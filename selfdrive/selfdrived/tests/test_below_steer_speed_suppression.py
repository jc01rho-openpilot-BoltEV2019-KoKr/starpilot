"""Regression / source-contract test for belowSteerSpeed suppression in selfdrived.

The "Steer Unavailable Under <X> km/h" alert is emitted as EventName.belowSteerSpeed.
Car brands may already emit this event from their own `CarState` emitters, but
selfdrived intentionally:

  1. strips brand-emitted belowSteerSpeed events before publication at line ~411, and
  2. no longer injects its own belowSteerSpeed warning at line ~423.

This test encodes both invariants as a source-contract: if either contract breaks
the test will fail. On unmodified selfdrived.py, the injection test is expected
to fail (RED) until the active `self.events.add(EventName.belowSteerSpeed)` line
in the show_alert block is commented out.
"""
from __future__ import annotations

import re
from pathlib import Path

SOURCE_PATH = Path(__file__).resolve().parent.parent / "selfdrived.py"
METHOD_START = re.compile(r"def update_events\(self[^:]*:\s*\n")


def _get_update_events_source() -> str:
  text = SOURCE_PATH.read_text()
  start_match = METHOD_START.search(text)
  if start_match is None:
    raise AssertionError("update_events method not found in selfdrived.py")
  start = start_match.start()
  rest = text[start:]
  lines = rest.split("\n")
  method_lines = [lines[0]]
  for line in lines[1:]:
    if re.match(r"^  def ", line):
      break
    method_lines.append(line)
  return "\n".join(method_lines)


class TestBelowSteerSpeedSuppression:
  """Source-contract: brand strip is kept, selfdrived injection is disabled."""

  def test_strips_brand_originated_below_steer_speed(self):
    """selfdrived must keep the brand-strip filter active.

    Line ~411 removes any car-originated belowSteerSpeed event from `car_events`
    before publication. Commenting that line out would re-enable brand-specific
    alerts; this assertion guards against that regression.
    """
    block = _get_update_events_source()
    assert "EventName.belowSteerSpeed" in block, \
      "belowSteerSpeed must still appear in update_events"

    strip_pattern = re.compile(
      r"^[^#\n]*e\.name\.raw\s*!=\s*EventName\.belowSteerSpeed",
      re.MULTILINE,
    )
    assert strip_pattern.search(block) is not None, (
      "Brand-originated belowSteerSpeed strip is missing or commented out"
    )

  def test_does_not_inject_below_steer_speed_warning(self):
    """selfdrived must NOT inject its own belowSteerSpeed warning.

    The active `self.events.add(EventName.belowSteerSpeed)` inside the show_alert
    block is what surfaces "Steer Unavailable Under <X> km/h" for every brand,
    because brand emitters are already stripped above. Commenting that line out
    suppresses the warning at the source. This assertion fails until that line
    is commented out.
    """
    block = _get_update_events_source()
    active_adds = re.findall(
      r"^[ \t]*self\.events\.add\(EventName\.belowSteerSpeed\)",
      block,
      re.MULTILINE,
    )
    assert active_adds == [], (
      f"Expected zero active belowSteerSpeed injections, found {len(active_adds)}"
    )
