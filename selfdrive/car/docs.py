#!/usr/bin/env python3
import argparse
import os

from openpilot.common.basedir import BASEDIR
from opendbc.car.car_helpers import interfaces
from opendbc.car.docs import get_all_car_docs, generate_cars_md
from opendbc.car.docs_definitions import CarDocs, SupportType
from opendbc.car.mock.values import CAR as MOCK

CARS_MD_OUT = os.path.join(BASEDIR, "docs", "CARS.md")
CARS_MD_TEMPLATE = os.path.join(BASEDIR, "selfdrive", "car", "CARS_template.md")


def get_starpilot_community_car_docs(all_car_docs: list[CarDocs]) -> list[CarDocs]:
  return [car_docs for car_docs in all_car_docs
          if car_docs.support_type == SupportType.COMMUNITY and
          car_docs.car_fingerprint != MOCK.MOCK and
          car_docs.car_fingerprint in interfaces]


def get_starpilot_supported_car_docs(all_car_docs: list[CarDocs]) -> list[CarDocs]:
  upstream_car_docs = [car_docs for car_docs in all_car_docs if car_docs.support_type == SupportType.UPSTREAM]
  return upstream_car_docs + get_starpilot_community_car_docs(all_car_docs)


def generate_starpilot_cars_md(all_car_docs: list[CarDocs], template_fn: str) -> str:
  return generate_cars_md(
    all_car_docs,
    template_fn,
    starpilot_community_car_docs=get_starpilot_community_car_docs(all_car_docs),
  )


if __name__ == "__main__":
  parser = argparse.ArgumentParser(description="Auto generates supported cars documentation",
                                   formatter_class=argparse.ArgumentDefaultsHelpFormatter)

  parser.add_argument("--template", default=CARS_MD_TEMPLATE, help="Override default template filename")
  parser.add_argument("--out", default=CARS_MD_OUT, help="Override default generated filename")
  args = parser.parse_args()

  with open(args.out, 'w') as f:
    f.write(generate_starpilot_cars_md(get_all_car_docs(), args.template))
  print(f"Generated and written to {args.out}")
