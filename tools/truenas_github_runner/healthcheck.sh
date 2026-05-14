#!/usr/bin/env bash

set -euo pipefail

RUNNER_HOME="${RUNNER_HOME:-/runner}"

test -f /opt/actions-runner/.runner
test -f "${RUNNER_HOME}/.state/configured"
pgrep -f "Runner.Listener" >/dev/null
