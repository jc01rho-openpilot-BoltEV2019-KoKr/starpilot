# Low-Voltage Battery Discord Report Implementation Plan

> **For Hermes:** Use subagent-driven-development skill to implement this plan task-by-task.

**Goal:** Add an owner-only StarPilot device setting that, when the configured GitHub SSH-key username is `jc01rho`, sends a single low-voltage battery report to a Discord webhook after each genuine onroad-to-offroad transition.

**Architecture:** Use the already-running `starpilot_process` as the transition orchestrator because it observes `deviceState.started` continuously and already owns `transition_offroad()`. Sample the generic vehicle supply voltage from `peripheralState.voltage` during the drive and at the transition; do not make the first implementation dependent on GM-only `APM_Stats`, because `gm_global_a_powertrain_expansion.dbc` is not in the current GM runtime DBC map. Dispatch a bounded, asynchronous `curl` subprocess with a JSON payload, while keeping the webhook in a `DONT_LOG` Params key and persisting only non-secret delivery state for deduplication/retry.

**Tech Stack:** Python, cereal messaging (`deviceState`, `peripheralState`), StarPilot Params, existing `ThreadManager`, `curl`, pytest, StarPilot Python/Raylib settings UI and Qt settings UI.

---

## Feasibility findings and constraints

- `GithubUsername` is persistent and is populated when the user enters a GitHub username and StarPilot successfully fetches public SSH keys (`selfdrive/ui/widgets/ssh_key.py`, `selfdrive/ui/qt/widgets/ssh_keys.cc`). It can gate this owner-specific feature.
- This is not strong OAuth authentication: the value is user-entered and can be changed locally. Treat `GithubUsername == "jc01rho"` plus a non-empty `GithubSshKeys` value as an ownership/configuration gate, not as cryptographic identity proof.
- The canonical drive-end hook already exists at `starpilot/starpilot_process.py:294-300`: `deviceState.started` changes from true to false and calls `transition_offroad()` exactly once per observed transition.
- `starpilot_process` is `always_run` (`system/manager/process_config.py:234-237`), so it remains available offroad to perform delivery and retry.
- `peripheralState.voltage` is the vehicle low-voltage supply measurement in millivolts. `hardwared` already feeds it to `PowerMonitoring`, including the configured low-voltage shutdown threshold.
- GM DBC `gm_global_a_powertrain_expansion.dbc` defines `0x1D6 APM_Stats.APM_Low_Voltage_Sensed`, but that DBC is not currently in `GMPlatformConfig.dbc_dict`. Adding it to runtime parsing would require bus availability validation on the target Bolt and is intentionally deferred.
- Do not store, commit, print, or include the webhook URL in logs, exceptions, command output, tests, or the plan. Use `[REDACTED]` in examples.

## Recommended first-release semantics

- Feature name: `LowVoltageDiscordReport`.
- Visible and executable only when:
  - `GithubUsername`, stripped and case-folded, equals `jc01rho`;
  - `GithubSshKeys` is non-empty;
  - the toggle is enabled;
  - a valid Discord HTTPS webhook has been configured.
- Trigger only on `deviceState.started: true -> false`, not process boot while already offroad and not ordinary disengagement.
- Capture these non-sensitive fields:
  - route/session identifier if available;
  - UTC timestamp;
  - instantaneous voltage at transition;
  - minimum and maximum valid voltage observed during the drive;
  - voltage sample count;
  - configured `LowVoltageShutdown` threshold;
  - whether the final/minimum value is below that threshold;
  - device type and car fingerprint if already available without new identification work.
- A valid voltage sample is `peripheralState` alive/valid, known panda type, and a plausible millivolt range (recommended `6000 <= mV <= 18000`). Never report the default zero value as real data.
- Send one report per completed drive. If no valid sample exists, either skip delivery with a non-secret status reason or send `voltage unavailable`; default recommendation is skip and record the reason locally.
- Use a short delay after the transition (recommended 5 seconds) to allow the electrical system to settle, but retain the drive minimum and transition sample. Cancel the delayed attempt if ignition/onroad resumes before sending.
- Use `curl` with argv, not `shell=True`; write JSON to stdin so payload quoting is safe. Recommended bounds: `--fail-with-body --silent --show-error --connect-timeout 5 --max-time 15 --retry 2 --retry-delay 2`, HTTP POST, `Content-Type: application/json`.
- Never log `curl` argv because it contains the webhook URL. Log only sanitized success/failure classifications and HTTP-independent return codes.

---

### Task 1: Register owner-only configuration Params

**Objective:** Define the enable flag, secret webhook storage, and non-secret delivery state with correct logging protections.

**Files:**
- Modify: `common/params_keys.h`
- Test: existing Params validation tests discovered during implementation

**Step 1: Write the failing Params contract test**

Add assertions that:

- `LowVoltageDiscordReport` is a persistent BOOL with default false.
- `LowVoltageDiscordWebhook` is persistent, has no committed default URL, and includes `DONT_LOG`.
- `LowVoltageDiscordLastDrive` and `LowVoltageDiscordPendingReport` are either `DONT_LOG` or contain strictly non-secret metadata. Prefer a single JSON pending-state key marked `DONT_LOG` to eliminate accidental payload logging.

**Step 2: Run the focused test and verify failure**

Run the repository's Params-key test target located during implementation. Expected: failure because the keys do not exist.

**Step 3: Add minimal key definitions**

Recommended keys:

```text
LowVoltageDiscordReport          PERSISTENT | BOOL, default 0
LowVoltageDiscordWebhook         PERSISTENT | DONT_LOG | STRING
LowVoltageDiscordPendingReport   PERSISTENT | DONT_LOG | JSON, default {}
LowVoltageDiscordLastDrive       PERSISTENT | STRING
```

Do not place a webhook literal in source.

**Step 4: Run the focused test and verify pass**

Expected: all Params key/schema tests pass.

---

### Task 2: Add pure ownership, voltage, and payload helpers

**Objective:** Isolate all policy and formatting logic from process lifecycle code so it is deterministic and unit-testable.

**Files:**
- Create: `starpilot/system/low_voltage_discord.py`
- Create: `starpilot/system/tests/test_low_voltage_discord.py` or the repository-consistent adjacent test location

**Step 1: Write failing tests**

Cover:

1. Owner gate accepts `jc01rho`, including harmless whitespace/case normalization if desired.
2. Owner gate rejects empty, similar, or different usernames.
3. Gate requires non-empty `GithubSshKeys`; document that this proves only successful public-key lookup, not OAuth identity.
4. Voltage validator accepts plausible millivolt values and rejects zero, negative, unknown-panda, stale, and implausible values.
5. Drive accumulator computes min/max/latest/sample count without accepting invalid samples.
6. Payload contains only intended report fields and never contains webhook data.
7. Discord content obeys Discord's message-length limit.
8. Dedupe helper rejects a drive ID already marked delivered.
9. Secret redaction helper never returns the URL, even on malformed URLs or subprocess errors.

**Step 2: Run tests and confirm RED**

```bash
pytest -q starpilot/system/tests/test_low_voltage_discord.py
```

Expected: import/module failure.

**Step 3: Implement pure helpers**

Suggested components:

```python
OWNER_GITHUB_USERNAME = "jc01rho"
MIN_VALID_VOLTAGE_MV = 6000
MAX_VALID_VOLTAGE_MV = 18000

@dataclass
class DriveVoltageSummary:
  latest_mv: int | None = None
  min_mv: int | None = None
  max_mv: int | None = None
  samples: int = 0

  def update(self, voltage_mv: int | None) -> None: ...
  def to_report(self, threshold_v: float, drive_id: str, ...) -> dict: ...
```

Functions should include:

```python
def owner_is_allowed(params) -> bool: ...
def extract_valid_voltage_mv(peripheral_state, alive: bool, valid: bool) -> int | None: ...
def build_discord_payload(report: dict) -> dict: ...
def report_id(drive_id: str, transition_mono_ns: int) -> str: ...
```

Keep the module free of network side effects until the delivery task.

**Step 4: Run tests and confirm GREEN**

Expected: all helper tests pass.

---

### Task 3: Implement secure bounded `curl` delivery

**Objective:** Send the Discord POST without blocking the control loop or exposing the webhook.

**Files:**
- Modify: `starpilot/system/low_voltage_discord.py`
- Modify: `starpilot/system/tests/test_low_voltage_discord.py`

**Step 1: Write failing delivery tests**

Mock `subprocess.run` and verify:

- Command is an argv list and never uses `shell=True`.
- Webhook is passed only as the destination argument and is never copied into log/error text.
- JSON is passed through stdin (`input=json.dumps(payload)`), not interpolated into a shell command.
- Timeouts and finite retries are set.
- Return code zero marks the report delivered.
- Nonzero, timeout, or missing `curl` leaves a retryable pending record.
- A second call with the same report ID does not send twice.
- Runtime owner gate is checked immediately before each attempt, so removing/changing the GitHub username disables pending delivery.

**Step 2: Run tests and verify failure**

Expected: delivery function absent.

**Step 3: Add delivery implementation**

Use an API shaped like:

```python
def send_pending_report(params, report: dict, run=subprocess.run) -> DeliveryResult:
  ...
```

Security requirements:

- Fetch the webhook from Params only inside the worker immediately before sending.
- Require `https://discord.com/api/webhooks/` or `https://discordapp.com/api/webhooks/`; reject other schemes/hosts.
- Do not return or print the URL.
- Do not call shared `run_cmd`, because its failure/reporting behavior may include command details.
- Capture output but log only a sanitized status. Do not log Discord response bodies.
- Set pending state before network I/O and mark delivered atomically after success.

**Step 4: Run tests and verify pass**

Expected: all delivery and redaction tests pass.

---

### Task 4: Track voltage during a drive

**Objective:** Subscribe to the generic low-voltage source and maintain an in-memory drive summary.

**Files:**
- Modify: `starpilot/starpilot_process.py:241-324`
- Modify: `starpilot/common/tests/test_starpilot_process.py`

**Step 1: Write failing process tests**

Test the extracted state-transition helper rather than running the infinite process loop:

- Starting a drive resets the accumulator.
- Valid `peripheralState.voltage` samples update min/max/latest.
- Invalid or stale samples are ignored.
- `true -> false` finalizes exactly one report candidate.
- Initial boot in offroad state does not finalize a report.
- `false -> true -> false` creates one new report per drive.
- A quick offroad/onroad bounce does not send a stale prior report.

**Step 2: Add `peripheralState` subscription**

Extend the `SubMaster` list in `starpilot_process.py` to include `peripheralState`.

**Step 3: Add a small coordinator object**

Instantiate a `LowVoltageDiscordReporter` or equivalent near other process-owned managers. It should:

- reset on rising `started` edge;
- sample on each loop when onroad;
- finalize on falling edge;
- hold no webhook string in object repr/log output.

**Step 4: Verify focused tests**

```bash
pytest -q starpilot/common/tests/test_starpilot_process.py starpilot/system/tests/test_low_voltage_discord.py
```

Expected: pass.

---

### Task 5: Hook finalization into `transition_offroad()` asynchronously

**Objective:** Schedule one delivery attempt after genuine drive completion without blocking StarPilot's realtime loop.

**Files:**
- Modify: `starpilot/starpilot_process.py:178-192, 294-300`
- Modify: `starpilot/common/tests/test_starpilot_process.py`

**Step 1: Write failing integration tests**

Verify:

- Owner mismatch means no thread is scheduled.
- Missing webhook means no thread is scheduled.
- Disabled toggle means no thread is scheduled.
- Valid owner/config schedules exactly one named worker through `ThreadManager`.
- The worker waits for the configured settlement delay.
- Before sending, it rechecks `IsOnroad` or current `deviceState.started`; if the car restarted, it cancels.
- A delivery failure keeps pending state; success clears pending and records the report ID.

**Step 2: Integrate with the existing falling edge**

Call report finalization from the existing `not started and started_previously` branch, after the final sample is captured and before or within `transition_offroad()`.

Use `thread_manager.run_with_lock()` so network activity cannot block the model/planner loop. Give the worker a unique stable function name so duplicate scheduling is naturally suppressed.

**Step 3: Add boot/offroad retry**

Because a network may not be ready at the transition, check for a pending report periodically while offroad. Retry with bounded backoff, for example at 30 seconds, 2 minutes, and 10 minutes, then retain pending data until the next boot/offroad period. Always recheck owner, toggle, webhook validity, and that the device remains offroad.

Do not retry indefinitely in a tight loop.

**Step 4: Run focused tests**

Expected: all process and reporter tests pass.

---

### Task 6: Add owner-only device settings UI

**Objective:** Let the owner enable reporting and securely add/remove the webhook from StarPilot device settings, while hiding the feature for all other usernames.

**Files:**
- Modify: `selfdrive/ui/layouts/settings/starpilot/system_settings.py`
- Modify: corresponding Python UI tests (locate adjacent settings tests)
- Modify: `starpilot/ui/qt/offroad/device_settings.cc`
- Modify: `starpilot/ui/qt/offroad/device_settings.h` if key grouping is needed
- Modify: an existing reusable masked-secret/input control, or add a minimal dedicated control in the nearest UI module
- Test: add/extend StarPilot device-settings contract tests

**Step 1: Write failing UI contract tests**

Verify for both Python/Raylib and Qt:

- `LowVoltageDiscordReport` appears only when `GithubUsername == "jc01rho"` and `GithubSshKeys` exists.
- Toggle cannot be enabled without a configured valid webhook.
- UI displays only `Configured`/`Not configured`, never the URL.
- Add/replace input is masked if the framework supports it.
- Remove requires confirmation.
- Changing/removing GitHub SSH identity hides and disables runtime behavior but does not expose the stored secret.

**Step 2: Add UI rows under Device Management**

Recommended UX:

```text
Low-Voltage Discord Report        [toggle]
Discord Webhook                   [ADD / REMOVE]   Configured
```

Description must state:

- report is sent after a drive ends;
- voltage is the comma/Panda-observed 12 V supply;
- feature is owner-specific;
- the username check is a local configuration gate, not OAuth authentication.

**Step 3: Validate webhook input without network leakage**

Validate scheme and host locally. An optional `TEST` button may send a generic test message, but only after explicit user action and with the same sanitized delivery helper. Never display or log the URL.

**Step 4: Run UI tests**

Run the focused Python UI and Qt contract tests. Expected: pass.

---

### Task 7: Add GM APM voltage as an optional phase-two source

**Objective:** Determine whether the target Chevrolet Bolt exposes CAN `0x1D6 APM_Stats` on a bus available to openpilot, without compromising the generic implementation.

**Files:**
- No production change until route/CAN evidence confirms message presence
- Possible future modifications:
  - `opendbc_repo/opendbc/car/gm/values.py`
  - `opendbc_repo/opendbc/car/gm/carstate.py`
  - GM parser tests
  - an appropriate cereal/custom field if the value must be exported

**Step 1: Collect evidence on the target device**

For a representative route, verify:

- CAN ID `0x1D6` is received;
- which bus receives it;
- update frequency and checksum/counter behavior;
- decoded `APM_Low_Voltage_Sensed` agrees with `peripheralState.voltage` within a documented tolerance;
- message remains available at ignition shutdown long enough to capture a meaningful final sample.

**Step 2: Decide source priority**

Recommended priority after validation:

1. GM `APM_Low_Voltage_Sensed` if fresh and plausible;
2. `peripheralState.voltage` fallback;
3. unavailable.

Include the source name in the Discord report.

**Step 3: Avoid blindly changing the platform DBC map**

Do not simply add `gm_global_a_powertrain_expansion` as another `Bus.pt` DBC because the current dictionary maps one DBC per bus. Options include merging the message into the generated powertrain DBC, adding a dedicated parser, or exporting the signal from another StarPilot process. Select only after bus evidence is available.

---

### Task 8: End-to-end validation and safety review

**Objective:** Prove correct behavior without sending secrets or test spam.

**Files:**
- Test-only fixtures as needed
- No real webhook in repository files

**Step 1: Run static checks**

```bash
python3 -m py_compile starpilot/system/low_voltage_discord.py starpilot/starpilot_process.py

git diff --check
```

Expected: clean.

**Step 2: Run focused tests**

```bash
pytest -q \
  starpilot/system/tests/test_low_voltage_discord.py \
  starpilot/common/tests/test_starpilot_process.py \
  selfdrive/ui/tests/<device-settings-test>.py \
  starpilot/common/tests/<device-settings-contract-test>.py
```

Expected: pass.

**Step 3: Run broader tests**

```bash
pytest -q
```

If the full suite is not feasible on the host, record the exact blocker and run all impacted suites.

**Step 4: Secret scan**

Inspect the diff for:

```text
https://discord.com/api/webhooks/
webhook tokens
curl command logs
payloads containing the URL
```

Expected: no real URL/token and no logging path that exposes it.

**Step 5: Bench test with a local HTTP server**

Use a localhost fake endpoint only in a developer test configuration; verify:

- one POST on true→false;
- no POST on boot-offroad;
- no POST for non-owner;
- retry after simulated network failure;
- no duplicate after process restart with pending/delivered state;
- cancellation when onroad resumes during delay.

Production URL validation must continue to restrict actual configured values to Discord HTTPS hosts; local endpoint support should exist only via dependency injection in tests, not a runtime setting.

**Step 6: Controlled device rollout**

1. Configure username and SSH keys for `jc01rho`.
2. Add webhook through masked UI; confirm UI shows only `Configured`.
3. Enable the toggle.
4. Complete a short drive with known healthy 12 V voltage.
5. Switch ignition off and confirm exactly one Discord report.
6. Reboot while offroad and confirm no duplicate.
7. Perform a quick offroad→onroad transition within the delay and confirm cancellation.
8. Disconnect network at drive end, reconnect offroad, and confirm a single retry delivery.
9. Remove GitHub username and confirm no pending/new report is sent.

---

## Expected files to change

Likely minimum set:

```text
common/params_keys.h
starpilot/system/low_voltage_discord.py
starpilot/system/tests/test_low_voltage_discord.py
starpilot/starpilot_process.py
starpilot/common/tests/test_starpilot_process.py
selfdrive/ui/layouts/settings/starpilot/system_settings.py
selfdrive/ui/tests/<device-settings-test>.py
starpilot/ui/qt/offroad/device_settings.cc
starpilot/ui/qt/offroad/device_settings.h
starpilot/common/tests/<device-settings-contract-test>.py
```

Phase two, only after CAN evidence:

```text
opendbc_repo/opendbc/car/gm/values.py
opendbc_repo/opendbc/car/gm/carstate.py
corresponding GM tests/schema export
```

## Risks and mitigations

- **Username spoofability:** `GithubUsername` is local input, not OAuth. Mitigate by requiring successfully fetched SSH keys and treating the gate as owner-specific UI/config gating only. For strong identity, add a separate signed challenge or owner provisioned token in a future design.
- **Webhook leakage:** mark secret Params `DONT_LOG`; mask UI; never use shared command logging; never print response body or argv.
- **Duplicate messages:** persist a report ID/pending state before I/O and mark completion atomically; trigger only on a falling started edge.
- **Network unavailable after shutdown:** asynchronous offroad retry with bounded backoff and persistent pending state.
- **Stale/zero voltage:** require service alive/valid, known panda, plausible range, and at least one drive sample.
- **Voltage meaning:** `peripheralState.voltage` is the supply voltage seen by Panda/comma, not a lab-grade battery-terminal measurement and not battery SOC. Label it accordingly.
- **Ignition transient:** report minimum, transition, and optionally delayed settled sample rather than presenting one transient as definitive.
- **Control-loop blocking:** all delay and network work runs in `ThreadManager`, never in the realtime loop.
- **GM DBC availability:** do not claim APM DBC data is live until CAN route evidence confirms bus/message availability.

## Acceptance criteria

- No report can be emitted unless the runtime username gate, SSH-key presence, toggle, valid webhook, valid drive transition, and valid voltage conditions all pass.
- Exactly one report is delivered per completed drive despite retries, reboot, or process restart.
- The webhook is absent from source, git diff, logs, exceptions, telemetry, tests, and UI display.
- The transition path does not block `starpilot_process`.
- Non-GM vehicles remain safe because the first release uses generic `peripheralState.voltage`.
- Discord text clearly labels the reading as 12 V supply voltage observed by Panda/comma and includes its source.
- Focused and impacted UI/process tests pass, followed by the broadest feasible pytest run.
