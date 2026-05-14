# TrueNAS SCALE GitHub Build Runner

This setup runs a single GitHub self-hosted runner as a TrueNAS SCALE custom app and routes the `Compile StarPilot` workflow onto that runner.

The app container:

- registers one repository-scoped GitHub Actions runner
- stays visible in the TrueNAS Apps UI
- mounts the host Docker socket so `./build` can launch the existing larch64 build container flow
- persists runner state and build caches in one dataset mounted at `/runner`

## What this workflow does

`.github/workflows/compile_starpilot.yaml` now:

- lets an admin choose a `target_ref` branch from the Actions UI
- checks out that branch on the NAS runner
- runs `./build`
- prunes the tree with `scripts/ci_package_prebuilt_tree.sh`
- commits the result as `build`
- pushes that commit back to the selected branch without force-pushing

Use a branch intended for built output. The prune step removes developer-facing files and is not meant for normal day-to-day development branches.

## 1. Publish the runner image

You need a registry image for TrueNAS to deploy. The repo includes `.github/workflows/publish_truenas_runner.yaml` for this.

1. Open **Actions** on GitHub.
2. Run **Publish TrueNAS Runner Image**.
3. Leave `image_tag` as `latest` unless you want a versioned tag.
4. After it finishes, the image is available at:

```text
ghcr.io/<repo-owner>/starpilot-truenas-runner:latest
```

If you prefer to build it locally, run:

```bash
docker build -f tools/truenas_github_runner/Dockerfile -t ghcr.io/<repo-owner>/starpilot-truenas-runner:latest .
docker push ghcr.io/<repo-owner>/starpilot-truenas-runner:latest
```

## 2. Create a runner token

Generate a repository-scoped self-hosted runner token in GitHub:

1. Open the repository.
2. Go to **Settings > Actions > Runners**.
3. Click **New self-hosted runner**.
4. Choose **Linux** and **x64**.
5. Copy the one-time registration token from the generated setup commands.

That token expires quickly. Paste it into TrueNAS during deployment and restart the app if you need to re-register.

## 3. Deploy on TrueNAS SCALE

TrueNAS custom apps support Docker Compose YAML through **Apps > Discover Apps > Custom App > Install via YAML**.

Create a dataset for persistent runner state first, for example:

```text
/mnt/<pool>/apps/starpilot-runner
```

Then paste this compose YAML into TrueNAS after replacing the placeholders:

```yaml
services:
  starpilot-runner:
    image: ghcr.io/<repo-owner>/starpilot-truenas-runner:latest
    container_name: starpilot-runner
    restart: unless-stopped
    environment:
      GITHUB_REPOSITORY_URL: https://github.com/<repo-owner>/<repo-name>
      RUNNER_NAME: starpilot-truenas-runner
      RUNNER_LABELS: self-hosted,truenas,starpilot-build
      RUNNER_WORKDIR: /runner/_work
      RUNNER_TOKEN: <paste-one-time-runner-token>
      DOCKER_GID: ""
      REMOVE_RUNNER_ON_EXIT: "0"
    volumes:
      - /mnt/<pool>/apps/starpilot-runner:/runner
      - /var/run/docker.sock:/var/run/docker.sock
```

If the container starts but cannot talk to Docker, inspect the Docker socket group on TrueNAS and set `DOCKER_GID` to that numeric group id.

## 4. Verify runner registration

Confirm all of the following:

- the app shows as `Running` in TrueNAS
- the container passes its healthcheck
- GitHub shows the runner as online with labels `self-hosted`, `truenas`, and `starpilot-build`

## 5. Run a build

1. Open **Actions > Compile StarPilot**.
2. Click **Run workflow**.
3. Enter the branch name in `target_ref`.
4. Optionally set `jobs` to the parallelism you want for `./build`.
5. Start the run.

On success, the workflow pushes a new commit named `build` back to that branch.

## Operational notes

- `RUNNER_TOKEN` is only required on first registration or when you want to replace a stale runner with the same name.
- Runner state is persisted in `/runner`, so normal restarts do not need a new token.
- `REMOVE_RUNNER_ON_EXIT=1` enables best-effort deregistration on shutdown, but that only works when the provided token is still valid.
- The build cache, GitHub workspace, and `.comma_sysroot` data all persist under the runner dataset as long as the workflow runs in the same mounted work area.
