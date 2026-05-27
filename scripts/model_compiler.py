#!/usr/bin/env python3
import argparse
import codecs
import os
import pickle
import json
import re
import shutil
import subprocess
import sys

from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
  sys.path.insert(0, str(REPO_ROOT))

from openpilot.selfdrive.modeld.constants import ModelConstants
from openpilot.starpilot.common.model_versions import uses_combined_driving_artifacts

DEFAULT_INPUT_ROOT = Path("/data/openpilot/uncompiledmodels")
DEFAULT_OUTPUT_ROOT = Path("/data/openpilot/compiledmodels")
COMPILE_SCRIPT = REPO_ROOT / "tinygrad_repo/examples/openpilot/compile3.py"
COMBINED_COMPILE_SCRIPT = REPO_ROOT / "selfdrive/modeld/compile_modeld.py"
MODEL_VERSIONS_CACHE = Path("/data/models/.model_versions.json")
DM_MODEL_KEY = "dm"
DM_MODEL_NAME = "dmonitoring_model"
DM_TARGET_ALIASES = {DM_MODEL_KEY, "dmonitoring", DM_MODEL_NAME}
DM_INPUT_CANDIDATES = ("dmonitoring_model.onnx", "dmonitoring.onnx", "dm.onnx")

COMPONENT_ALIASES = {
  "driving_off_policy": ("driving_off_policy", "off_policy", "offpolicy"),
  "driving_on_policy": ("driving_on_policy", "on_policy", "onpolicy"),
  "driving_policy": ("driving_policy", "policy"),
  "driving_vision": ("driving_vision", "vision"),
}
MEDMODEL_INPUT_SIZE = (512, 256)
DEFAULT_CAMERA_RESOLUTIONS = (
  (1928, 1208),
  (1344, 760),
)


def build_compile_env(*, combined: bool = False) -> dict[str, str]:
  env = os.environ.copy()
  existing_pythonpath = env.get("PYTHONPATH", "")
  env["PYTHONPATH"] = f"{REPO_ROOT}:{existing_pythonpath}" if existing_pythonpath else str(REPO_ROOT)

  numeric_defaults = {
    "DEBUG": "0",
    "FLOAT16": "1",
    "IMAGE": "2",
    "JIT_BATCH_SIZE": "0",
    "NOLOCALS": "1",
  }
  for key, default in numeric_defaults.items():
    value = env.get(key)
    try:
      int(str(value), 0)
    except (TypeError, ValueError):
      env[key] = default

  return env


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(
    description="Compile staged ONNX driving models into tinygrad pkls without touching selfdrive/modeld/models.",
  )
  parser.add_argument("--model", help="Output model key, for example sc2.")
  parser.add_argument("--dm", action="store_true", help="Compile the driver monitoring model into dmonitoring_model_tinygrad.pkl.")
  parser.add_argument("--input-dir", type=Path, default=DEFAULT_INPUT_ROOT, help="Directory containing staged ONNX files. Flat root files like driving_policy.onnx are preferred.")
  parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT_ROOT, help="Directory for compiled tinygrad pkls and metadata.")
  parser.add_argument("--version", help="Model version. v16+ uses the combined driving_tinygrad artifact path. If omitted, split-policy staged models default to the combined build.")
  parser.add_argument("--list", action="store_true", help="List detected staged models and exit.")
  parser.add_argument("--force", action="store_true", help="Legacy no-op. Compiled outputs are always cleared before a build.")

  args, unknown = parser.parse_known_args()
  dynamic_model_flags = [arg[2:] for arg in unknown if arg.startswith("--")]
  invalid = [arg for arg in unknown if not arg.startswith("--")]
  if invalid:
    parser.error(f"Unexpected arguments: {' '.join(invalid)}")
  if len(dynamic_model_flags) > 1:
    parser.error("Pass only one dynamic model flag, for example ./models --sc2")
  if args.model and dynamic_model_flags and args.model != dynamic_model_flags[0]:
    parser.error("Use either --model sc2 or --sc2, not both with different values.")
  args.model = args.model or (dynamic_model_flags[0] if dynamic_model_flags else None)
  if args.model and args.model.strip().lower() in DM_TARGET_ALIASES:
    args.dm = True
    args.model = None
  if args.dm and args.model:
    parser.error("Use either --dm or a driving model key, not both.")
  return args


def detect_component(path: Path) -> str | None:
  stem = path.stem.lower()
  for component, aliases in COMPONENT_ALIASES.items():
    if any(alias in stem for alias in aliases):
      return component
  return None


def find_staged_dm(input_root: Path) -> Path | None:
  if not input_root.is_dir():
    return None

  for candidate in DM_INPUT_CANDIDATES:
    path = input_root / candidate
    if path.is_file():
      return path

  for child in sorted(input_root.iterdir()):
    if not child.is_dir():
      continue
    for candidate in DM_INPUT_CANDIDATES:
      path = child / candidate
      if path.is_file():
        return path

  return None


def find_staged_models(input_root: Path) -> dict[str, dict[str, Path]]:
  found: dict[str, dict[str, Path]] = {}
  if not input_root.is_dir():
    return found

  for child in sorted(input_root.iterdir()):
    if not child.is_dir():
      continue
    model_files = {}
    for onnx_file in sorted(child.glob("*.onnx")):
      component = detect_component(onnx_file)
      if component:
        model_files[component] = onnx_file
    if model_files:
      found[child.name] = model_files

  flat_root_files = {}
  for onnx_file in sorted(input_root.glob("*.onnx")):
    component = detect_component(onnx_file)
    if component is None:
      continue

    model_key = None
    lowered = onnx_file.stem.lower()
    for alias in COMPONENT_ALIASES[component]:
      if lowered == alias:
        model_key = None
        break
      suffix = f"_{alias}"
      if lowered.endswith(suffix):
        model_key = onnx_file.stem[:-len(suffix)]
        break

    if model_key in ("", "driving"):
      model_key = None

    if model_key:
      found.setdefault(model_key, {})[component] = onnx_file
    else:
      flat_root_files[component] = onnx_file

  if flat_root_files:
    found["_root"] = flat_root_files

  return found


def resolve_model_files(input_root: Path, model_key: str) -> dict[str, Path]:
  staged = find_staged_models(input_root)
  if model_key in staged:
    return staged[model_key]

  root_files = staged.get("_root")
  if root_files and len(staged) == 1:
    return root_files

  prefixed_files = {}
  for onnx_file in sorted(input_root.glob(f"{model_key}_*.onnx")):
    component = detect_component(onnx_file)
    if component:
      prefixed_files[component] = onnx_file
  return prefixed_files


def get_metadata_value_by_name(model, name: str):
  for prop in model.metadata_props:
    if prop.key == name:
      return prop.value
  return None


def write_metadata(onnx_path: Path, output_path: Path) -> None:
  import onnx

  model = onnx.load(str(onnx_path))
  output_slices = get_metadata_value_by_name(model, "output_slices")
  if output_slices is None:
    raise ValueError(f"output_slices not found in metadata for {onnx_path.name}")

  def get_name_and_shape(value_info) -> tuple[str, tuple[int, ...]]:
    shape = tuple(int(dim.dim_value) for dim in value_info.type.tensor_type.shape.dim)
    return value_info.name, shape

  metadata = {
    "model_checkpoint": get_metadata_value_by_name(model, "model_checkpoint"),
    "output_slices": pickle.loads(codecs.decode(output_slices.encode(), "base64")),
    "input_shapes": dict(get_name_and_shape(x) for x in model.graph.input),
    "output_shapes": dict(get_name_and_shape(x) for x in model.graph.output),
  }

  with open(output_path, "wb") as f:
    pickle.dump(metadata, f)


def compile_component(onnx_path: Path, output_path: Path) -> None:
  subprocess.run(
    [sys.executable, str(COMPILE_SCRIPT), str(onnx_path), str(output_path)],
    cwd=REPO_ROOT,
    env=build_compile_env(combined=False),
    check=True,
  )


def compile_combined_model(component_paths: dict[str, Path], output_path: Path) -> None:
  vision_path = component_paths["driving_vision"]
  off_policy_path = component_paths["driving_off_policy"]
  on_policy_path = component_paths.get("driving_on_policy") or component_paths.get("driving_policy")
  if on_policy_path is None:
    raise ValueError("Combined compile requires driving_on_policy.onnx (or driving_policy.onnx) alongside driving_off_policy.onnx")

  frame_skip = ModelConstants.MODEL_RUN_FREQ // ModelConstants.MODEL_CONTEXT_FREQ
  camera_resolutions = [f"{width}x{height}" for width, height in DEFAULT_CAMERA_RESOLUTIONS]
  subprocess.run(
    [
      sys.executable,
      str(COMBINED_COMPILE_SCRIPT),
      "--model-size",
      f"{MEDMODEL_INPUT_SIZE[0]}x{MEDMODEL_INPUT_SIZE[1]}",
      "--camera-resolutions",
      *camera_resolutions,
      "--vision-onnx",
      str(vision_path),
      "--off-policy-onnx",
      str(off_policy_path),
      "--on-policy-onnx",
      str(on_policy_path),
      "--output",
      str(output_path),
      "--frame-skip",
      str(frame_skip),
    ],
    cwd=REPO_ROOT,
    env=build_compile_env(combined=True),
    check=True,
  )


def infer_model_version(model_key: str, explicit_version: str | None) -> str:
  if explicit_version:
    return explicit_version.strip()

  if MODEL_VERSIONS_CACHE.is_file():
    try:
      version_map = json.loads(MODEL_VERSIONS_CACHE.read_text())
      version = version_map.get(model_key)
      if isinstance(version, str) and version.strip():
        return version.strip()
    except Exception:
      pass

  return ""


def should_use_combined_artifacts(model_version: str, model_files: dict[str, Path]) -> bool:
  if uses_combined_driving_artifacts(model_version):
    return True
  if model_version.strip():
    return False

  has_vision = "driving_vision" in model_files
  has_off_policy = "driving_off_policy" in model_files
  has_on_policy = "driving_on_policy" in model_files or "driving_policy" in model_files
  return has_vision and has_off_policy and has_on_policy


def resolve_split_component_inputs(model_files: dict[str, Path]) -> dict[str, Path]:
  resolved: dict[str, Path] = {}

  vision_path = model_files.get("driving_vision")
  if vision_path is not None:
    resolved["driving_vision"] = vision_path

  policy_path = model_files.get("driving_policy") or model_files.get("driving_on_policy")
  if policy_path is not None:
    resolved["driving_policy"] = policy_path

  off_policy_path = model_files.get("driving_off_policy")
  if off_policy_path is not None:
    resolved["driving_off_policy"] = off_policy_path

  return resolved


def clear_existing_outputs(output_dir: Path) -> list[Path]:
  removed = []
  for existing in sorted(output_dir.iterdir()):
    if existing.is_file() or existing.is_symlink():
      existing.unlink()
    elif existing.is_dir():
      shutil.rmtree(existing)
    removed.append(existing)
  return removed


def list_models(staged: dict[str, dict[str, Path]], input_root: Path) -> int:
  dm_path = find_staged_dm(input_root)
  if not staged and dm_path is None:
    print(f"No staged models found in {input_root}")
    return 0

  for model_key, files in sorted(staged.items()):
    print(model_key)
    for component, path in sorted(files.items()):
      print(f"  {component}: {path}")

  if dm_path is not None:
    print(DM_MODEL_KEY)
    print(f"  {DM_MODEL_NAME}: {dm_path}")
  return 0


def main() -> int:
  args = parse_args()
  staged = find_staged_models(args.input_dir)

  if args.list:
    return list_models(staged, args.input_dir)

  if args.dm:
    onnx_path = find_staged_dm(args.input_dir)
    if onnx_path is None:
      raise SystemExit(
        f"No staged ONNX file found for {DM_MODEL_NAME} in {args.input_dir}. "
        f"Use one of: {', '.join(str(args.input_dir / candidate) for candidate in DM_INPUT_CANDIDATES)}"
      )

    args.output_dir.mkdir(parents=True, exist_ok=True)
    print(f"Compiling {DM_MODEL_NAME} from {onnx_path} -> {args.output_dir}")

    removed = clear_existing_outputs(args.output_dir)
    if removed:
      print(f"  cleared {len(removed)} existing output entries")

    output_pkl = args.output_dir / f"{DM_MODEL_NAME}_tinygrad.pkl"
    output_metadata = args.output_dir / f"{DM_MODEL_NAME}_metadata.pkl"

    compile_component(onnx_path, output_pkl)
    write_metadata(onnx_path, output_metadata)
    print(f"  saved {output_pkl.name}")
    print(f"  saved {output_metadata.name}")
    print("Done.")
    return 0

  if not args.model:
    available = ", ".join(sorted(k for k in staged if k != "_root"))
    if find_staged_dm(args.input_dir) is not None:
      available = f"{available}, {DM_MODEL_KEY}" if available else DM_MODEL_KEY
    raise SystemExit(f"Choose a model key, for example ./models --sc2 or ./models --dm. Available staged models: {available or 'none'}")

  model_key = args.model.strip()
  files = resolve_model_files(args.input_dir, model_key)
  if not files:
    raise SystemExit(
      f"No staged ONNX files found for {model_key} in {args.input_dir}. "
      f"Use {args.input_dir}/driving_policy.onnx and {args.input_dir}/driving_vision.onnx, "
      f"or {args.input_dir}/driving_on_policy.onnx with {args.input_dir}/driving_off_policy.onnx, "
      f"or optionally {args.input_dir / model_key}/*.onnx"
    )

  model_version = infer_model_version(model_key, args.version)
  use_combined_artifacts = should_use_combined_artifacts(model_version, files)

  args.output_dir.mkdir(parents=True, exist_ok=True)
  mode_label = "combined" if use_combined_artifacts else "split"
  version_label = model_version or ("auto-combined" if use_combined_artifacts else "legacy-default")
  print(f"Compiling {model_key} ({version_label}, {mode_label}) from {args.input_dir} -> {args.output_dir}")

  removed = clear_existing_outputs(args.output_dir)
  if removed:
    print(f"  cleared {len(removed)} existing output entries")

  if use_combined_artifacts:
    required_components = {"driving_vision", "driving_off_policy"}
    if not (files.get("driving_on_policy") or files.get("driving_policy")):
      required_components.add("driving_on_policy")
    missing = sorted(component for component in required_components if component not in files)
    if missing:
      raise SystemExit(f"Missing required ONNX files for combined compile of {model_key}: {', '.join(missing)}")

    output_pkl = args.output_dir / f"{model_key}_driving_tinygrad.pkl"
    compile_combined_model(files, output_pkl)
    print(f"  saved {output_pkl.name}")
    print("Done.")
    return 0

  split_components = resolve_split_component_inputs(files)
  missing = sorted(component for component in ("driving_policy", "driving_vision") if component not in split_components)
  if missing:
    raise SystemExit(f"Missing required ONNX files for {model_key}: {', '.join(missing)}")

  for component, onnx_path in sorted(split_components.items()):
    output_pkl = args.output_dir / f"{model_key}_{component}_tinygrad.pkl"
    output_metadata = args.output_dir / f"{model_key}_{component}_metadata.pkl"

    print(f"  compiling {component}: {onnx_path.name}")
    compile_component(onnx_path, output_pkl)
    write_metadata(onnx_path, output_metadata)
    print(f"  saved {output_pkl.name}")
    print(f"  saved {output_metadata.name}")

  print("Done.")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
