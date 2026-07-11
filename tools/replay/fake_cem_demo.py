#!/usr/bin/env python3

import argparse
import signal
import time
from itertools import cycle

from openpilot.common.params import Params
from openpilot.starpilot.common.experimental_state import CEStatus, CE_STATUS_PARAM


SCENARIOS = [
  ("curve", CEStatus["CURVATURE"]),
  ("lead", CEStatus["LEAD"]),
  ("stop light", CEStatus["STOP_LIGHT"]),
  ("speed", CEStatus["SPEED"]),
]

running = True


def _handle_signal(_signum, _frame) -> None:
  global running
  running = False


def main() -> None:
  parser = argparse.ArgumentParser(description="Publish fake CEM statuses for desktop onroad replay.")
  parser.add_argument("--hold-seconds", type=float, default=2.0, help="How long each CEM status stays active.")
  parser.add_argument("--publish-interval", type=float, default=0.25, help="Seconds between CEStatus writes.")
  args = parser.parse_args()

  signal.signal(signal.SIGINT, _handle_signal)
  signal.signal(signal.SIGTERM, _handle_signal)

  params_memory = Params(memory=True)
  scenario_cycle = cycle(SCENARIOS)
  label, status = next(scenario_cycle)
  next_switch = time.monotonic() + args.hold_seconds
  print(f"showing CEM: {label}", flush=True)

  try:
    while running:
      now = time.monotonic()
      if now >= next_switch:
        label, status = next(scenario_cycle)
        next_switch = now + args.hold_seconds
        print(f"showing CEM: {label}", flush=True)

      params_memory.put_int(CE_STATUS_PARAM, status)
      time.sleep(args.publish_interval)
  finally:
    params_memory.put_int(CE_STATUS_PARAM, CEStatus["OFF"])


if __name__ == "__main__":
  main()
