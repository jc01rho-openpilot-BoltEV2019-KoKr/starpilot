#!/usr/bin/env python3
import platform
import shutil
import signal
import subprocess
import tarfile
import time
import threading
import urllib.request
from http.server import HTTPServer, BaseHTTPRequestHandler
from pathlib import Path

from openpilot.common.params import Params

GALAXY_DIR = Path("/data/galaxy")
FRPC_VERSION = "0.67.0"
FRPC_LOG = GALAXY_DIR / "frpc.log"
AUTH_PORT = 8083

process = None
auth_server = None


class AuthHandler(BaseHTTPRequestHandler):
  """Serves only GET /glxyauth — returns the PIN hash file contents."""
  def do_GET(self):
    if self.path == "/glxyauth":
      auth_file = GALAXY_DIR / "glxyauth"
      if auth_file.exists():
        data = auth_file.read_bytes()
        self.send_response(200)
        self.send_header("Content-Type", "text/plain")
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)
        return
    self.send_response(404)
    self.end_headers()

  def log_message(self, format, *args):
    pass  # suppress request logs


def start_auth_server():
  global auth_server
  if auth_server is not None:
    return
  auth_server = HTTPServer(("127.0.0.1", AUTH_PORT), AuthHandler)
  thread = threading.Thread(target=auth_server.serve_forever, daemon=True)
  thread.start()
  print(f"Galaxy: Auth server listening on 127.0.0.1:{AUTH_PORT}")


def cleanup_frpc(*_):
  global process
  if process is not None and process.poll() is None:
    process.terminate()
    try:
      process.wait(timeout=5)
    except subprocess.TimeoutExpired:
      process.kill()
    process = None


def get_arch_url():
  arch = platform.machine()
  if arch in ("aarch64", "arm64"):
    return f"https://github.com/fatedier/frp/releases/download/v{FRPC_VERSION}/frp_{FRPC_VERSION}_linux_arm64.tar.gz", f"frp_{FRPC_VERSION}_linux_arm64"
  elif arch in ("x86_64", "amd64"):
    return f"https://github.com/fatedier/frp/releases/download/v{FRPC_VERSION}/frp_{FRPC_VERSION}_linux_amd64.tar.gz", f"frp_{FRPC_VERSION}_linux_amd64"
  return None, None


def setup_frpc():
  GALAXY_DIR.mkdir(parents=True, exist_ok=True)
  frpc_bin = GALAXY_DIR / "frpc"

  if not frpc_bin.exists():
    print("Galaxy: Downloading frpc...")
    url, folder_name = get_arch_url()
    if not url:
      print("Galaxy: Unsupported architecture")
      return False

    tar_path = GALAXY_DIR / "frp.tar.gz"
    try:
      urllib.request.urlretrieve(url, tar_path)
      with tarfile.open(tar_path, "r:gz") as tar:
        tar.extractall(path=GALAXY_DIR, filter='data')

      # Move binary
      extracted_bin = GALAXY_DIR / folder_name / "frpc"
      extracted_bin.rename(frpc_bin)
      frpc_bin.chmod(0o755)

      # Cleanup
      tar_path.unlink()
      shutil.rmtree(GALAXY_DIR / folder_name)
      print("Galaxy: frpc downloaded and installed.")
    except Exception as e:
      print(f"Galaxy: Failed to install frpc: {e}")
      return False

  return True


def main():
  global process
  params = Params()

  signal.signal(signal.SIGTERM, cleanup_frpc)
  signal.signal(signal.SIGINT, cleanup_frpc)

  # Wait for DongleId to be set (usually set on boot/pairing)
  dongle_id = params.get("DongleId", encoding='utf8')
  while not dongle_id:
    print("Galaxy: Waiting for DongleId...")
    time.sleep(5)
    dongle_id = params.get("DongleId", encoding='utf8')

  print(f"Galaxy: DongleId: {dongle_id}")
  print("Galaxy: Starting manager loop...")

  while True:
    glxyauth_file = GALAXY_DIR / "glxyauth"
    galaxy_password_hash = glxyauth_file.read_text().strip() if glxyauth_file.exists() else None
    is_paired = galaxy_password_hash and len(galaxy_password_hash) == 64

    if is_paired:
      if process is None or process.poll() is not None:
        if process is not None:
          print(f"Galaxy: frpc exited with code {process.returncode}. Restarting...")

        print("Galaxy: Password set. Preparing frpc tunnel...")
        if not setup_frpc():
          print("Galaxy: FRPC setup failed. Retrying later...")
          time.sleep(10)
          continue

        # Start the tiny auth HTTP server (serves /glxyauth on localhost)
        start_auth_server()

        frpc_toml = GALAXY_DIR / "frpc.toml"
        config = f"""\
serverAddr = "galaxy.firestar.link"
serverPort = 7000

[transport]
tls.enable = true
poolCount = 2

[[proxies]]
name = "{dongle_id}_pond"
type = "http"
localIP = "127.0.0.1"
localPort = 8082
customDomains = ["{dongle_id}.devices.local"]
transport.useCompression = true

[[proxies]]
name = "{dongle_id}_auth"
type = "http"
localIP = "127.0.0.1"
localPort = {AUTH_PORT}
customDomains = ["auth-{dongle_id}.devices.local"]
"""
        frpc_toml.write_text(config)

        print("Galaxy: Starting frpc tunnel...")
        log_file = open(FRPC_LOG, 'a')
        process = subprocess.Popen(
          [str(GALAXY_DIR / "frpc"), "-c", str(frpc_toml)],
          stdout=log_file,
          stderr=log_file
        )
    else:
      if process is not None and process.poll() is None:
        print("Galaxy: Password cleared. Stopping frpc tunnel...")
        cleanup_frpc()

    time.sleep(3)


if __name__ == "__main__":
  main()

