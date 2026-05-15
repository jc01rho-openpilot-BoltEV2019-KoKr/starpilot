FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
ARG RUNNER_VERSION=2.334.0

ENV RUNNER_HOME=/runner
ENV RUNNER_WORKDIR=/runner/_work

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    docker.io \
    git \
    gosu \
    jq \
    sudo \
    tar \
    unzip \
  && rm -rf /var/lib/apt/lists/*

RUN useradd --create-home --home-dir /home/runner --shell /bin/bash runner \
  && usermod -aG sudo runner \
  && echo "runner ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/runner

WORKDIR /opt/actions-runner

RUN curl -fsSL -o actions-runner.tar.gz \
      "https://github.com/actions/runner/releases/download/v${RUNNER_VERSION}/actions-runner-linux-x64-${RUNNER_VERSION}.tar.gz" \
  && tar -xzf actions-runner.tar.gz \
  && rm actions-runner.tar.gz \
  && ./bin/installdependencies.sh \
  && chown -R runner:runner /opt/actions-runner

COPY tools/truenas_github_runner/entrypoint.sh /usr/local/bin/truenas-runner-entrypoint
COPY tools/truenas_github_runner/healthcheck.sh /usr/local/bin/truenas-runner-healthcheck

RUN chmod 755 /usr/local/bin/truenas-runner-entrypoint /usr/local/bin/truenas-runner-healthcheck

HEALTHCHECK --interval=30s --timeout=10s --start-period=30s --retries=5 CMD ["/usr/local/bin/truenas-runner-healthcheck"]

ENTRYPOINT ["/usr/local/bin/truenas-runner-entrypoint"]
