import os

from openpilot.common.basedir import BASEDIR
from opendbc.car.car_helpers import interfaces
from opendbc.car.docs import get_all_car_docs
from opendbc.car.docs_definitions import SupportType
from opendbc.car.mock.values import CAR as MOCK
from openpilot.selfdrive.debug.dump_car_docs import dump_car_docs
from openpilot.selfdrive.debug.print_docs_diff import print_car_docs_diff
from openpilot.selfdrive.car.docs import (
  CARS_MD_TEMPLATE,
  generate_starpilot_cars_md,
  get_starpilot_community_car_docs,
  get_starpilot_supported_car_docs,
)


class TestCarDocs:
  @classmethod
  def setup_class(cls):
    cls.all_cars = get_all_car_docs()

  def test_generator(self):
    generate_starpilot_cars_md(self.all_cars, CARS_MD_TEMPLATE)

  def test_starpilot_community_cars_are_registered(self):
    community_cars = get_starpilot_community_car_docs(self.all_cars)

    assert community_cars
    assert all(car.support_type == SupportType.COMMUNITY for car in community_cars)
    assert all(car.car_fingerprint != MOCK.MOCK for car in community_cars)
    assert all(car.car_fingerprint in interfaces for car in community_cars)

  def test_every_starpilot_supported_car_is_rendered(self):
    rendered_docs = generate_starpilot_cars_md(self.all_cars, CARS_MD_TEMPLATE)
    supported_cars = get_starpilot_supported_car_docs(self.all_cars)

    assert supported_cars
    for car in supported_cars:
      expected_row = f"|{car.model} {car.years}".rstrip()
      assert expected_row in rendered_docs, f"Missing supported car from CARS.md: {car.name}"

    assert "|Subaru|Ascent 2023-25|" in rendered_docs

  def test_docs_diff(self):
    dump_path = os.path.join(BASEDIR, "selfdrive", "car", "tests", "cars_dump")
    dump_car_docs(dump_path)
    print_car_docs_diff(dump_path)
    os.remove(dump_path)
