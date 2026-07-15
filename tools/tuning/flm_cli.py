#!/usr/bin/env python3
import argparse
import json

from openpilot.system.hardware.hw import Paths
from openpilot.starpilot.system.the_galaxy import flm_workspace


def main() -> None:
  parser = argparse.ArgumentParser(description="Run the Firestar Lateral Method analyzer against local routes.")
  parser.add_argument("routes", nargs="+", help="One or more local route ids.")
  parser.add_argument("--report-id", dest="report_id", default=None, help="Optional report id override.")
  args = parser.parse_args()

  footage_paths = [
    str(Paths.log_root(HD=True, raw=True)),
    str(Paths.log_root(konik=True, raw=True)),
    str(Paths.log_root(raw=True)),
  ]
  report = flm_workspace.analyze_routes(args.routes, footage_paths, report_id=args.report_id)
  print(json.dumps({
    "reportId": report["reportId"],
    "htmlPath": report["htmlPath"],
    "jsonPath": report["jsonPath"],
  }, indent=2))


if __name__ == "__main__":
  main()
