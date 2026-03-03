#!/usr/bin/env python3
import datetime
import os
import signal
import sys
import traceback

from cereal import log
import cereal.messaging as messaging
import openpilot.system.sentry as sentry
from openpilot.common.params import Params, ParamKeyType
from openpilot.common.text_window import TextWindow
from openpilot.system.hardware import HARDWARE, PC
from openpilot.system.manager.helpers import unblock_stdout, write_onroad_params, save_bootlog
from openpilot.system.manager.process import ensure_running
from openpilot.system.manager.process_config import managed_processes
from openpilot.system.athena.registration import register, UNREGISTERED_DONGLE_ID
from openpilot.common.swaglog import cloudlog, add_file_handler
from openpilot.system.version import get_build_metadata, terms_version, training_version

from openpilot.frogpilot.common.frogpilot_functions import convert_params, frogpilot_boot_functions, setup_frogpilot, uninstall_frogpilot
from openpilot.frogpilot.common.frogpilot_variables import EXCLUDED_KEYS, frogpilot_default_params, get_frogpilot_toggles, params_cache, params_memory


def manager_init() -> None:
  save_bootlog()

  build_metadata = get_build_metadata()

  params = Params()
  params.clear_all(ParamKeyType.CLEAR_ON_MANAGER_START)
  params.clear_all(ParamKeyType.CLEAR_ON_ONROAD_TRANSITION)
  params.clear_all(ParamKeyType.CLEAR_ON_OFFROAD_TRANSITION)
  if build_metadata.release_channel:
    params.clear_all(ParamKeyType.DEVELOPMENT_ONLY)

  # FrogPilot variables
  setup_frogpilot(build_metadata)
  convert_params(params_cache)

  default_params: list[tuple[str, str | bytes]] = [
    ("CompletedTrainingVersion", "0"),
    ("DisengageOnAccelerator", "0"),
    ("GsmMetered", "1"),
    ("HasAcceptedTerms", "0"),
    ("LanguageSetting", "main_en"),
    ("OpenpilotEnabledToggle", "1"),
    ("LongitudinalPersonality", str(log.LongitudinalPersonality.standard)),

    #NDA neokii
    ("AutoNaviSpeedCtrlStart", "25"),
    ("AutoNaviSpeedCtrlEnd", "15"),
  ]
  if not PC:
    default_params.append(("LastUpdateTime", datetime.datetime.utcnow().isoformat().encode('utf8')))

  if params.get_bool("RecordFrontLock"):
    params.put_bool("RecordFront", True)

  # set unset params
  reset_toggles = params.get_bool("DoToggleReset")
  reset_toggles_stock = params.get_bool("DoToggleResetStock")
  for k, v, stock in [(k, v, v) for k, v in default_params] + [(k, v, stock) for k, v, _, stock in frogpilot_default_params]:
    if (reset_toggles or reset_toggles_stock) and k in EXCLUDED_KEYS:
      continue

    if params.get(k) is None or reset_toggles or reset_toggles_stock:
      if params_cache.get(k) is None or reset_toggles or reset_toggles_stock:
        params.put(k, v if not reset_toggles_stock else stock)
        params_cache.remove(k)
      else:
        params.put(k, params_cache.get(k))
    else:
      params_cache.put(k, params.get(k))
  params.remove("DoToggleReset")
  params.remove("DoToggleResetStock")

  frogpilot_boot_functions(build_metadata, params_cache)

  # Create folders needed for msgq
  try:
    os.mkdir("/dev/shm")
  except FileExistsError:
    pass
  except PermissionError:
    print("WARNING: failed to make /dev/shm")

  # set version params
  params.put("Version", build_metadata.openpilot.version)
  params.put("TermsVersion", terms_version)
  params.put("TrainingVersion", training_version)
  params.put("GitCommit", build_metadata.openpilot.git_commit)
  params.put("GitCommitDate", build_metadata.openpilot.git_commit_date)
  params.put("GitBranch", build_metadata.channel)
  params.put("GitRemote", build_metadata.openpilot.git_origin)
  params.put_bool("IsTestedBranch", build_metadata.tested_channel)
  params.put_bool("IsReleaseBranch", build_metadata.release_channel)

  # Legacy Bolt fingerprint migration after branch consolidation
  bolt_source_branch_file = "/data/media/0/starpilot_source_branch"
  bolt_fingerprint_migration_flag_file = "/data/media/0/frogpilot_bolt_fingerprint_migrated.flag"
  if not os.path.exists(bolt_fingerprint_migration_flag_file):
    source_branch = ""
    try:
      if os.path.exists(bolt_source_branch_file):
        with open(bolt_source_branch_file, encoding="utf-8") as f:
          source_branch = f.read().strip()
    except OSError:
      cloudlog.exception("failed reading StarPilot source branch file")

    migration_branch = source_branch or build_metadata.channel
    replacements = {}
    if migration_branch in {"TorqueTune", "TorquePedal"}:
      replacements = {
        "CHEVROLET_BOLT_EUV": "CHEVROLET_BOLT_ACC_2022_2023",
        "CHEVROLET_BOLT_CC": "CHEVROLET_BOLT_CC_2022_2023",
      }
    elif migration_branch in {"TotallyTune", "StarPilot-2017", "StarPilot 2017"}:
      replacements = {
        "CHEVROLET_BOLT_CC": "CHEVROLET_BOLT_CC_2017",
      }
    elif migration_branch in {"StarPilot"}:
      replacements = {
        "CHEVROLET_BOLT_CC": "CHEVROLET_BOLT_CC_2019_2021",
      }

    migrated_values = []
    if replacements:
      for param_key in ("CarModel", "CarModelName"):
        current_value = params.get(param_key, encoding='utf-8')
        normalized_value = current_value[4:] if current_value is not None and current_value.startswith("CAR.") else current_value
        if normalized_value in replacements:
          new_value = replacements[normalized_value]
          params.put(param_key, new_value)
          params_cache.put(param_key, new_value)
          migrated_values.append(f"{param_key}: {current_value} -> {new_value}")

    if migrated_values:
      cloudlog.info(f"migrated legacy bolt fingerprint values from branch '{migration_branch}' (source='{source_branch}'): {', '.join(migrated_values)}")

    # Keep Bolt display label aligned with live fingerprint selection
    bolt_models = {
      "CHEVROLET_BOLT_EUV",
      "CHEVROLET_BOLT_CC",
      "CHEVROLET_BOLT_ACC_2022_2023",
      "CHEVROLET_BOLT_ACC_2022_2023_PEDAL",
      "CHEVROLET_BOLT_CC_2022_2023",
      "CHEVROLET_BOLT_CC_2019_2021",
      "CHEVROLET_BOLT_CC_2017",
    }
    if (params.get("CarModel", encoding='utf-8') or "") in bolt_models:
      params.remove("CarModelName")
      params_cache.remove("CarModelName")

    with open(bolt_fingerprint_migration_flag_file, "w") as f:
      f.write(migration_branch or "unknown")

  # One-time migration to align FrogPilot defaults after install
  frogpilot_migration_flag_file = "/data/media/0/frogpilot_migrated.flag"
  if not os.path.exists(frogpilot_migration_flag_file):
    params.put_bool("NNFF", False)
    params.put_bool("NNFFLite", False)
    params.put_bool("AdvancedLateralTune", True)
    params.put_bool("ForceAutoTuneOff", True)
    params.put_bool("ForceAutoTune", False)

    params.put_bool("CECurves", False)
    params.put_bool("CENavigation", False)
    params.put_bool("ShowCEMStatus", True)
    params.put_bool("CESlowerLead", True)
    params.put_bool("CEStoppedLead", True)
    params.put_int("CEModelStopTime", 8)

    params.put_bool("ReverseCruise", True)
    params.put_bool("HumanFollowing", False)
    params.put_bool("HumanAcceleration", False)

    params.put_int("TuningLevel", 3)
    params.put_bool("TuningLevelConfirmed", True)

    params.put_bool("DeveloperUI", True)
    params.put_bool("DeveloperWidgets", True)
    params.put_bool("DeveloperSidebar", False)
    params.put_bool("LeadInfo", True)
    params.put_bool("BorderMetrics", True)
    params.put_bool("ShowSteering", True)
    params.put_bool("BlindSpotMetrics", True)

    with open(frogpilot_migration_flag_file, "w") as f:
      f.write("migrated")

  # One-time migration for HumanAcceleration and HumanFollowing to off
  migration_flag_file = "/data/media/0/frogpilot_human_toggles_migrated.flag"
  if not os.path.exists(migration_flag_file):
    if params.get_bool("HumanAcceleration"):
      params.put_bool("HumanAcceleration", False)
    if params.get_bool("HumanFollowing"):
      params.put_bool("HumanFollowing", False)
    with open(migration_flag_file, "w") as f:
      f.write("migrated")

  # One-time migration for NNFFLite to off
  nnfflite_migration_flag_file = "/data/media/0/frogpilot_nnfflite_migrated.flag"
  if not os.path.exists(nnfflite_migration_flag_file):
    if params.get_bool("NNFFLite"):
      params.put_bool("NNFFLite", False)
    with open(nnfflite_migration_flag_file, "w") as f:
      f.write("migrated")

  # One-time migration for CEM settings
  cem_migration_flag_file = "/data/media/0/frogpilot_cem_migrated.flag"
  if not os.path.exists(cem_migration_flag_file):
    # Enable slower and stopped leads by default
    if not params.get_bool("CESlowerLead"):
      params.put_bool("CESlowerLead", True)
    if not params.get_bool("CEStoppedLead"):
      params.put_bool("CEStoppedLead", True)
    # Disable navigation and curves by default
    if params.get_bool("CENavigation"):
      params.put_bool("CENavigation", False)
    if params.get_bool("CECurves"):
      params.put_bool("CECurves", False)
    with open(cem_migration_flag_file, "w") as f:
      f.write("migrated")

  # One-time migration for NNFF to off
  nnff_migration_flag_file = "/data/media/0/frogpilot_nnff_migrated.flag"
  if not os.path.exists(nnff_migration_flag_file):
    if params.get_bool("NNFF"):
      params.put_bool("NNFF", False)
    with open(nnff_migration_flag_file, "w") as f:
      f.write("migrated")

  # One-time migration for lateral tuning/auto-tune preferences
  lateral_tuning_migration_flag_file = "/data/media/0/frogpilot_lateral_tuning_migrated.flag"
  if not os.path.exists(lateral_tuning_migration_flag_file):
    if not params.get_bool("AdvancedLateralTune"):
      params.put_bool("AdvancedLateralTune", True)
    if params.get_bool("ForceAutoTune"):
      params.put_bool("ForceAutoTune", False)
    if not params.get_bool("ForceAutoTuneOff"):
      params.put_bool("ForceAutoTuneOff", True)
    with open(lateral_tuning_migration_flag_file, "w") as f:
      f.write("migrated")

  # set dongle id
  reg_res = register(show_spinner=True)
  if reg_res:
    dongle_id = reg_res
  else:
    serial = params.get("HardwareSerial")
    raise Exception(f"Registration failed for device {serial}")
  os.environ['DONGLE_ID'] = dongle_id  # Needed for swaglog
  os.environ['GIT_ORIGIN'] = build_metadata.openpilot.git_normalized_origin # Needed for swaglog
  os.environ['GIT_BRANCH'] = build_metadata.channel # Needed for swaglog
  os.environ['GIT_COMMIT'] = build_metadata.openpilot.git_commit # Needed for swaglog

  if not build_metadata.openpilot.is_dirty:
    os.environ['CLEAN'] = '1'

  # init logging
  sentry.init(sentry.SentryProject.SELFDRIVE)
  cloudlog.bind_global(dongle_id=dongle_id,
                       version=build_metadata.openpilot.version,
                       origin=build_metadata.openpilot.git_normalized_origin,
                       branch=build_metadata.channel,
                       commit=build_metadata.openpilot.git_commit,
                       dirty=build_metadata.openpilot.is_dirty,
                       device=HARDWARE.get_device_type())

  # preimport all processes
  for p in managed_processes.values():
    p.prepare()


def manager_cleanup() -> None:
  # send signals to kill all procs
  for p in managed_processes.values():
    p.stop(block=False)

  # ensure all are killed
  for p in managed_processes.values():
    p.stop(block=True)

  cloudlog.info("everything is dead")


def manager_thread() -> None:
  cloudlog.bind(daemon="manager")
  cloudlog.info("manager start")
  cloudlog.info({"environ": os.environ})

  params = Params()

  ignore: list[str] = []
  if params.get("DongleId", encoding='utf8') in (None, UNREGISTERED_DONGLE_ID):
    ignore += ["manage_athenad", "uploader"]
  if os.getenv("NOBOARD") is not None:
    ignore.append("pandad")
  ignore += [x for x in os.getenv("BLOCK", "").split(",") if len(x) > 0]

  sm = messaging.SubMaster(['deviceState', 'carParams', 'frogpilotPlan'], poll='deviceState')
  pm = messaging.PubMaster(['managerState'])

  write_onroad_params(False, params)
  ensure_running(managed_processes.values(), False, params=params, CP=sm['carParams'], not_run=ignore, classic_model=False, tinygrad_model=False, frogpilot_toggles=get_frogpilot_toggles())

  started_prev = False

  # FrogPilot variables
  frogpilot_toggles = get_frogpilot_toggles()

  classic_model = frogpilot_toggles.classic_model
  tinygrad_model = frogpilot_toggles.tinygrad_model

  while True:
    sm.update(1000)

    started = sm['deviceState'].started

    if started and not started_prev:
      if not frogpilot_toggles.force_onroad:
        params.clear_all(ParamKeyType.CLEAR_ON_ONROAD_TRANSITION)

      # FrogPilot variables
      frogpilot_toggles = get_frogpilot_toggles()

      classic_model = frogpilot_toggles.classic_model
      tinygrad_model = frogpilot_toggles.tinygrad_model

    elif not started and started_prev:
      params.clear_all(ParamKeyType.CLEAR_ON_OFFROAD_TRANSITION)
      params_memory.clear_all(ParamKeyType.CLEAR_ON_OFFROAD_TRANSITION)

    # update onroad params, which drives pandad's safety setter thread
    if started != started_prev:
      write_onroad_params(started, params)

    started_prev = started

    ensure_running(managed_processes.values(), started, params=params, CP=sm['carParams'], not_run=ignore, classic_model=classic_model, tinygrad_model=tinygrad_model, frogpilot_toggles=frogpilot_toggles)

    running = ' '.join("{}{}\u001b[0m".format("\u001b[32m" if p.proc.is_alive() else "\u001b[31m", p.name)
                       for p in managed_processes.values() if p.proc)

    if os.path.isfile("/tmp/print_processes"):
      print(running)

    cloudlog.debug(running)

    # send managerState
    msg = messaging.new_message('managerState', valid=True)
    msg.managerState.processes = [p.get_process_state_msg() for p in managed_processes.values()]
    pm.send('managerState', msg)

    # Exit main loop when uninstall/shutdown/reboot is needed
    shutdown = False
    for param in ("DoUninstall", "DoShutdown", "DoReboot"):
      if params.get_bool(param):
        shutdown = True
        params.put("LastManagerExitReason", f"{param} {datetime.datetime.now()}")
        cloudlog.warning(f"Shutting down manager - {param} set")

    if shutdown:
      break

    # Update FrogPilot variables
    if sm['frogpilotPlan'].togglesUpdated:
      frogpilot_toggles = get_frogpilot_toggles()

def main() -> None:
  manager_init()
  if os.getenv("PREPAREONLY") is not None:
    return

  # SystemExit on sigterm
  signal.signal(signal.SIGTERM, lambda signum, frame: sys.exit(1))

  try:
    manager_thread()
  except Exception:
    traceback.print_exc()
    sentry.capture_exception()
  finally:
    manager_cleanup()

  params = Params()
  if params.get_bool("DoUninstall"):
    cloudlog.warning("uninstalling")
    uninstall_frogpilot()
  elif params.get_bool("DoReboot"):
    cloudlog.warning("reboot")
    HARDWARE.reboot()
  elif params.get_bool("DoShutdown"):
    cloudlog.warning("shutdown")
    HARDWARE.shutdown()


if __name__ == "__main__":
  unblock_stdout()

  try:
    main()
  except KeyboardInterrupt:
    print("got CTRL-C, exiting")
  except Exception:
    add_file_handler(cloudlog)
    cloudlog.exception("Manager failed to start")

    try:
      managed_processes['ui'].stop()
    except Exception:
      pass

    # Show last 3 lines of traceback
    error = traceback.format_exc(-3)
    error = "Manager failed to start\n\n" + error
    with TextWindow(error) as t:
      t.wait_for_exit()

    raise

  # manual exit because we are forked
  sys.exit(0)
