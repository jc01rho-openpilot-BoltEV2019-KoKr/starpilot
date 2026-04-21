import cereal.messaging as messaging

from openpilot.selfdrive.controls.lib.drive_helpers import CONTROL_N
from openpilot.selfdrive.test.process_replay.migration import migrate_longitudinalPlan


def test_migrate_longitudinal_plan_uses_legacy_helper_signature():
  long_plan = messaging.new_message('longitudinalPlan')
  long_plan.longitudinalPlan.speeds = [float(i) for i in range(CONTROL_N)]
  long_plan.longitudinalPlan.accels = [0.1] * CONTROL_N

  car_params = messaging.new_message('carParams')

  ops, add_ops, del_ops = migrate_longitudinalPlan([
    (0, long_plan.as_reader()),
    (1, car_params.as_reader()),
  ])

  assert len(ops) == 1
  assert add_ops == []
  assert del_ops == []

  _, migrated = ops[0]
  assert migrated.longitudinalPlan.aTarget != 0.0
