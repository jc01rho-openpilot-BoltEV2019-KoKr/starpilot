#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "${ROOT_DIR}"

find . -name "matlab.*.md" -delete

find . -type d \( -iname "debug" -o -iname "test" -o -iname "tests" -o -name "__pycache__" \) -exec rm -rf {} +

find . -type f \( \
  -name "*.a" -o \
  -name "*.o" -o \
  -name "*.onnx" -o \
  -name "*.os" -o \
  -name "*.pyc" -o \
  -name "moc_*" \
\) -delete

find .github -mindepth 1 -maxdepth 1 ! -name "workflows" -exec rm -rf {} +
find .github/workflows -mindepth 1 ! \( \
  -type f \( \
    -name "compile_starpilot.yaml" -o \
    -name "publish_truenas_runner.yaml" -o \
    -name "review_pull_request.yaml" -o \
    -name "schedule_update.yaml" -o \
    -name "update_pr_branch.yaml" -o \
    -name "update_release_branch.yaml" -o \
    -name "update_tinygrad.yaml" \
  \) \
\) -exec rm -rf {} +

find panda/board -type f \
  ! -name "__init__.py" \
  ! -name "bootstub.panda.bin" \
  ! -name "bootstub.panda_h7.bin" \
  ! -name "panda.bin.signed" \
  ! -name "panda_h7.bin.signed" \
  -delete

find third_party/ -name "*Darwin*" -exec rm -rf {} +
find third_party/ -name "*x86*" -exec rm -rf {} +

rm -f .gitignore .gitmodules .gitattributes .lfsconfig .overlay_init

rm -rf .sconsign.dblite .vscode/ Jenkinsfile release/ scripts/ site_scons/ teleoprtc_repo/

find . -type d -empty ! -path "./.git*" -delete

touch prebuilt
