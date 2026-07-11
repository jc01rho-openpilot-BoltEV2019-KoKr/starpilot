#!/usr/bin/env python3

import argparse
import signal
import time

from cereal import car, log, messaging

AlertSize = log.SelfdriveState.AlertSize
AlertStatus = log.SelfdriveState.AlertStatus
AudibleAlert = log.SelfdriveState.AudibleAlert
VisualAlert = car.CarControl.HUDControl.VisualAlert


running = True


def _handle_signal(_signum, _frame) -> None:
  global running
  running = False


def build_msg(text1: str, text2: str, size: int, status: int,
              audible: int = AudibleAlert.none,
              visual: int = VisualAlert.none,
              alert_type: str = ""):
  m = messaging.new_message("selfdriveState")
  m.valid = True
  ss = m.selfdriveState
  ss.alertSize = size
  ss.alertStatus = status
  ss.alertText1 = text1
  ss.alertText2 = text2
  ss.alertType = alert_type
  ss.alertSound = audible
  ss.alertHudVisual = visual
  return m


def main() -> None:
  parser = argparse.ArgumentParser(description="Publish a fake critical full-screen selfdriveState alert for desktop onroad replay.")
  parser.add_argument("--delay", type=float, default=20.0, help="Seconds to wait after start before firing the alert (allows replay route + UI to come up, then ~10s for the user to open Settings).")
  parser.add_argument("--hold-interval", type=float, default=0.25, help="Seconds between selfdriveState publishes.")
  parser.add_argument("--hold", type=float, default=5.0, help="Seconds to keep the critical alert active before clearing it.")
  parser.add_argument("--text1", type=str, default="TAKE CONTROL IMMEDIATELY", help="Primary alert text.")
  parser.add_argument("--text2", type=str, default="Controls Mismatch", help="Secondary alert text.")
  parser.add_argument("--audible", action="store_true", default=True, help="Include warningImmediate audible alert.")
  parser.add_argument("--silent", dest="audible", action="store_false", help="Omit audible alert (override --audible).")
  args = parser.parse_args()

  signal.signal(signal.SIGINT, _handle_signal)
  signal.signal(signal.SIGTERM, _handle_signal)

  pm = messaging.PubMaster(["selfdriveState"])

  audible = AudibleAlert.warningImmediate if args.audible else AudibleAlert.none
  visual = VisualAlert.steerRequired

  none_msg = build_msg("", "", AlertSize.none, AlertStatus.normal)
  fire_msg = build_msg(args.text1, args.text2, AlertSize.full, AlertStatus.critical,
                        audible=audible, visual=visual,
                        alert_type="controlsMismatch/immediateDisable")

  print(f"fake_alert_demo: waiting {args.delay:.1f}s before firing critical alert...", flush=True)

  end = time.monotonic() + args.delay
  while running and time.monotonic() < end:
    pm.send("selfdriveState", none_msg)
    none_msg.clear_write_flag()
    time.sleep(args.hold_interval)

  if not running:
    return

  print(f"fake_alert_demo: firing critical red alert: '{args.text1}' / '{args.text2}' for {args.hold:.1f}s", flush=True)

  held = time.monotonic() + args.hold
  try:
    while running and time.monotonic() < held:
      pm.send("selfdriveState", fire_msg)
      fire_msg.clear_write_flag()
      time.sleep(args.hold_interval)
  finally:
    print("fake_alert_demo: clearing alert (sending AlertSize.none) so UI fades out...", flush=True)
    clear = build_msg("", "", AlertSize.none, AlertStatus.normal)
    for _ in range(3):
      pm.send("selfdriveState", clear)
      clear.clear_write_flag()
      time.sleep(args.hold_interval)


if __name__ == "__main__":
  main()
