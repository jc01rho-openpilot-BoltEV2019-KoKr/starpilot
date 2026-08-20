FROM ghcr.io/commaai/openpilot-base-aarch64:latest

ARG CAPNP_VERSION=1.0.2

ENV PYTHONUNBUFFERED=1
ENV UV_LINK_MODE=copy
WORKDIR /work

# Keep this image minimal; dependency resolution is done by uv inside the workspace.
# rsync/ssh-client are needed for optional sysroot sync from a comma device.
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    rsync \
    openssh-client \
    e2fsprogs \
    android-sdk-libsparse-utils \
    qemu-user-static \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    cmake \
    python3-pip \
    xz-utils \
    git \
  && rm -rf /var/lib/apt/lists/*

RUN set -eux; \
    tmpdir="$(mktemp -d)"; \
    curl -fsSL "https://github.com/capnproto/capnproto/archive/refs/tags/v${CAPNP_VERSION}.tar.gz" | tar -xz -C "${tmpdir}"; \
    cmake -S "${tmpdir}/capnproto-${CAPNP_VERSION}/c++" -B "${tmpdir}/build" \
      -DBUILD_TESTING=OFF \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/usr/local; \
    cmake --build "${tmpdir}/build" -j"$(nproc)"; \
    cmake --install "${tmpdir}/build"; \
    ldconfig; \
    capnp --version; \
    rm -rf "${tmpdir}"

RUN /usr/bin/python3 -m pip install --no-cache-dir --break-system-packages uv

# Fix for "dubious ownership" git errors when mounting folders on Linux hosts.
RUN git config --global --add safe.directory /work
