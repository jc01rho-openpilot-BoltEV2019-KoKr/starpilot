#include "catch2/catch.hpp"
#define private public
#include "common/params.h"
#include "common/util.h"

TEST_CASE("params_nonblocking_put") {
  char tmp_path[] = "/tmp/asyncWriter_XXXXXX";
  const std::string param_path = mkdtemp(tmp_path);
  auto param_names = {"CarParams", "IsMetric"};
  {
    Params params(param_path);
    for (const auto &name : param_names) {
      params.putNonBlocking(name, "1");
      // param is empty
      REQUIRE(params.get(name).empty());
    }

    // check if thread is running
    REQUIRE(params.future.valid());
    REQUIRE(params.future.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout);
  }
  // check results
  Params p(param_path);
  for (const auto &name : param_names) {
    REQUIRE(p.get(name) == "1");
  }
}

TEST_CASE("settings_tier_is_independent_from_tuning_level") {
  Params params;

  REQUIRE(params.getSettingsTier("AlwaysOnLateral") == SETTINGS_SIMPLE);
  REQUIRE(params.getTuningLevel("AlwaysOnLateral") == 0);
  REQUIRE(params.getSettingsTier("HumanLaneChanges") == SETTINGS_SIMPLE);
  REQUIRE(params.getTuningLevel("HumanLaneChanges") == 2);
  REQUIRE(params.getSettingsTier("AdvancedLateralTune") == SETTINGS_ADVANCED);
}
