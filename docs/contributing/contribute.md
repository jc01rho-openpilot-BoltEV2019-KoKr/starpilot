# Contribute to StarPilot

Contributions are welcome. StarPilot is driver-assistance software, so changes should be focused, testable, and safe for vehicles outside the change's intended scope.

## Pull requests

Open all pull requests against the **`Dom` branch**. `Dom` is StarPilot's testing and integration branch; do not target the release branch directly.

A pull request should:

* have one clear purpose and contain only changes needed for that purpose;
* explain what changed, why it changed, and how it was tested;
* link the relevant issue or feedback item when one exists;
* avoid unrelated cleanup, refactors, dependency changes, and formatting churn; and
* pass the existing tests and checks.

Keep commits reviewable and update documentation when behavior or configuration changes. If a change needs a large refactor, separate that work from the behavior change when practical.

### Vehicle-specific changes

Do your best to ensure a vehicle-specific change affects only the intended vehicle, platform, or brand. Prefer the narrowest appropriate condition instead of changing shared behavior for every vehicle.

Tests should prove both sides of that boundary:

* the affected vehicle receives the new or corrected behavior; and
* an unaffected vehicle, platform, brand, or configuration retains the existing behavior.

Include the vehicle and hardware used for on-road or bench testing in the pull request. Hardware testing is valuable, but it does not replace an automated regression test when the behavior can be tested in code.

## Development environment

StarPilot keeps host-native development tools separate from device-target builds. Run the setup and development commands from the repository root.

Install the Python dependencies before starting:

```bash
tools/install_python_dependencies.sh
```

On Ubuntu, `tools/ubuntu_setup.sh` installs both the system and Python dependencies. The development tools also require `uv`.

Use `./dev` for host-native tools. It creates and reuses an isolated environment under `.host_runtime/`, keeping host build artifacts out of the working tree:

```bash
./dev replay
./dev cabana
./dev plotjuggler
./dev shell
```

For desktop UI work, use `./c3` or `./c4`. These commands use the same isolated host environment.

Use `./build` when you need comma-compatible device artifacts. This is the expected validation for changes that affect compiled device code or runtime behavior:

```bash
./build
```

Device builds require Docker Desktop or Podman with Linux/aarch64 support and a configured comma sysroot. See the [laptop device-build guide](../how-to/laptop-device-build.md) for setup instructions and the [complete StarPilot development workflow](https://github.com/firestar5683/StarPilot/blob/Dom/tools/STARPILOT_DEVELOPMENT.md) for all host commands and troubleshooting.

## Code formatting

Match the style of the code around your change and do not reformat unrelated files. Python formatting and lint rules are defined in `pyproject.toml`; the project uses two-space indentation and Ruff.

Run Ruff on changed Python files while developing:

```bash
ruff check path/to/changed_file.py
ruff format --check path/to/changed_file.py
```

Before submitting, run the repository lint checks from the project root:

```bash
./scripts/lint/lint.sh
```

## Testing standards

Every behavior change or bug fix should include focused automated tests when practical. Recent StarPilot tests favor small regression cases that construct the relevant state, exercise one behavior, and assert the exact result.

At minimum:

1. Add or update a test that would fail without the change.
2. Cover important boundaries, modes, and disabled states related to the change.
3. For vehicle-specific behavior, add a negative case showing the change does not bleed into an unaffected vehicle or configuration.
4. Run the directly affected test module and the existing tests for the affected subsystem.
5. Ensure the pull request passes all existing CI checks before it is ready to merge.

Run a focused test module with pytest:

```bash
pytest path/to/test_file.py
```

Run the full test suite when your development environment supports it:

```bash
pytest
```

If a test requires special hardware or cannot run in your environment, say so in the pull request and document the closest validation you completed.
