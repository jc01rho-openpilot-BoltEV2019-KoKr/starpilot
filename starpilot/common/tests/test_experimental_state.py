from openpilot.starpilot.common.experimental_state import (
  CC_STATUS_PARAM,
  CCStatus,
  CE_STATUS_PARAM,
  CEStatus,
  requested_experimental_mode,
  restore_persisted_cc_state,
)


class FakeParams:
  def __init__(self, bools=None, ints=None):
    self.bools = dict(bools or {})
    self.ints = dict(ints or {})

  def get_bool(self, key):
    return bool(self.bools.get(key, False))

  def put_bool(self, key, value):
    self.bools[key] = bool(value)

  def get_int(self, key, default=0):
    return int(self.ints.get(key, default))

  def put_int(self, key, value):
    self.ints[key] = int(value)


def test_requested_experimental_mode_defaults_to_experimental_in_ccm_auto():
  params = FakeParams(bools={"ConditionalChill": True})
  params_memory = FakeParams(ints={CC_STATUS_PARAM: CCStatus["OFF"]})

  assert requested_experimental_mode(params, params_memory) is True


def test_requested_experimental_mode_respects_ccm_manual_override():
  params = FakeParams(bools={"ConditionalChill": True})

  params_memory = FakeParams(ints={CC_STATUS_PARAM: CCStatus["USER_CHILL"]})
  assert requested_experimental_mode(params, params_memory) is False

  params_memory = FakeParams(ints={CC_STATUS_PARAM: CCStatus["USER_EXPERIMENTAL"]})
  assert requested_experimental_mode(params, params_memory) is True


def test_requested_experimental_mode_prefers_cem_if_both_conditional_modes_are_enabled():
  params = FakeParams(bools={"ConditionalExperimental": True, "ConditionalChill": True})

  params_memory = FakeParams(ints={
    CE_STATUS_PARAM: CEStatus["OFF"],
    CC_STATUS_PARAM: CCStatus["USER_EXPERIMENTAL"],
  })
  assert requested_experimental_mode(params, params_memory) is False

  params_memory = FakeParams(ints={
    CE_STATUS_PARAM: CEStatus["USER_OVERRIDDEN"],
    CC_STATUS_PARAM: CCStatus["USER_CHILL"],
  })
  assert requested_experimental_mode(params, params_memory) is True


def test_requested_experimental_mode_safe_mode_overrides_ccm():
  params = FakeParams(bools={"SafeMode": True, "ConditionalChill": True})
  params_memory = FakeParams(ints={CC_STATUS_PARAM: CCStatus["USER_EXPERIMENTAL"]})

  assert requested_experimental_mode(params, params_memory) is False


def test_restore_persisted_cc_state_rehydrates_manual_override():
  params = FakeParams(
    bools={"PersistChillState": True},
    ints={"PersistedCCStatus": CCStatus["USER_CHILL"]},
  )
  params_memory = FakeParams(ints={CC_STATUS_PARAM: CCStatus["OFF"]})

  restored_status = restore_persisted_cc_state(params, params_memory)

  assert restored_status == CCStatus["USER_CHILL"]
  assert params_memory.get_int(CC_STATUS_PARAM) == CCStatus["USER_CHILL"]
