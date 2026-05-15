#!/usr/bin/env bash

set -euo pipefail

RUNNER_HOME="${RUNNER_HOME:-/runner}"
RUNNER_WORKDIR="${RUNNER_WORKDIR:-${RUNNER_HOME}/_work}"
RUNNER_LABELS="${RUNNER_LABELS:-self-hosted,truenas,starpilot-build}"
RUNNER_NAME="${RUNNER_NAME:-$(hostname)}"
REMOVE_RUNNER_ON_EXIT="${REMOVE_RUNNER_ON_EXIT:-0}"
RUNNER_ALLOW_RUNASROOT=1

export RUNNER_ALLOW_RUNASROOT

log() {
  printf '[truenas-runner] %s\n' "$*"
}

fail() {
  printf '[truenas-runner] ERROR: %s\n' "$*" >&2
  exit 1
}

require_env() {
  local name="$1"
  [[ -n "${!name:-}" ]] || fail "Missing required environment variable: ${name}"
}

ensure_docker_access() {
  if [[ ! -S /var/run/docker.sock ]]; then
    fail "Docker socket /var/run/docker.sock is not mounted."
  fi

  if [[ -n "${DOCKER_GID:-}" ]]; then
    if ! getent group docker-host >/dev/null 2>&1; then
      groupadd --gid "${DOCKER_GID}" docker-host
    fi
    usermod -aG docker-host runner
  fi
}

prepare_dirs() {
  mkdir -p "${RUNNER_HOME}" "${RUNNER_WORKDIR}" "${RUNNER_HOME}/.state" "${RUNNER_HOME}/.config"

  chown -R runner:runner "${RUNNER_HOME}"
}

restore_runner_config() {
  local file=""
  for file in .runner .credentials .credentials_rsaparams; do
    if [[ -f "${RUNNER_HOME}/.config/${file}" ]]; then
      cp -f "${RUNNER_HOME}/.config/${file}" "/opt/actions-runner/${file}"
      chown runner:runner "/opt/actions-runner/${file}"
    else
      rm -f "/opt/actions-runner/${file}"
    fi
  done
}

persist_runner_config() {
  local file=""
  for file in .runner .credentials .credentials_rsaparams; do
    if [[ -f "/opt/actions-runner/${file}" ]]; then
      cp -f "/opt/actions-runner/${file}" "${RUNNER_HOME}/.config/${file}"
      chown runner:runner "${RUNNER_HOME}/.config/${file}"
    fi
  done
}

configure_runner() {
  require_env GITHUB_REPOSITORY_URL

  if [[ -f /opt/actions-runner/.runner ]]; then
    log "Existing runner configuration detected; skipping registration."
    return
  fi

  require_env RUNNER_TOKEN

  log "Registering GitHub runner ${RUNNER_NAME} for ${GITHUB_REPOSITORY_URL}"

  gosu runner /opt/actions-runner/config.sh \
    --url "${GITHUB_REPOSITORY_URL}" \
    --token "${RUNNER_TOKEN}" \
    --name "${RUNNER_NAME}" \
    --labels "${RUNNER_LABELS}" \
    --work "${RUNNER_WORKDIR}" \
    --unattended \
    --replace
}

cleanup() {
  local exit_code=$?

  if [[ -n "${runner_pid:-}" ]]; then
    kill "${runner_pid}" >/dev/null 2>&1 || true
    wait "${runner_pid}" || true
  fi

  if [[ "${REMOVE_RUNNER_ON_EXIT}" == "1" && -n "${RUNNER_TOKEN:-}" && -f /opt/actions-runner/.runner ]]; then
    log "Removing runner registration on exit."
    gosu runner /opt/actions-runner/config.sh remove --token "${RUNNER_TOKEN}" || true
  fi

  exit "${exit_code}"
}

trap cleanup EXIT INT TERM

ensure_docker_access
prepare_dirs
restore_runner_config
configure_runner
persist_runner_config

touch "${RUNNER_HOME}/.state/configured"
chown runner:runner "${RUNNER_HOME}/.state/configured"

log "Starting runner ${RUNNER_NAME}"
gosu runner /opt/actions-runner/run.sh &
runner_pid=$!
wait "${runner_pid}"
