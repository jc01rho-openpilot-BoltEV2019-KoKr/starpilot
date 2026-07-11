import hashlib

from scripts.model_compiler import split_oversized_artifact
from openpilot.starpilot.assets import download_functions
from openpilot.starpilot.assets.model_manager import MANIFEST_CANDIDATES, ModelManager
from openpilot.starpilot.common.model_versions import UNIFIED_ARTIFACT_FORMAT


def test_v22_is_the_only_manifest_candidate():
  assert MANIFEST_CANDIDATES == ("v22",)


def test_behavior_version_does_not_control_artifact_layout():
  manager = object.__new__(ModelManager)
  assert manager._required_files("example", UNIFIED_ARTIFACT_FORMAT) == [
    "example_driving_tinygrad.pkl",
  ]
  assert manager._required_files("example", "") == [
    "example_driving_tinygrad.pkl",
  ]
  assert manager._required_files("example", "split") == []


def test_dropbox_urls_are_direct_downloads():
  url = "https://www.dropbox.com/scl/fi/id/model.pkl?rlkey=key&st=value&dl=0"
  normalized = download_functions.normalize_download_url(url)
  assert normalized.count("dl=1") == 1
  assert "dl=0" not in normalized
  assert "rlkey=key" in normalized


def test_download_verification_uses_manifest_size_and_sha(tmp_path, monkeypatch):
  artifact = tmp_path / "model.pkl"
  artifact.write_bytes(b"unified model")
  monkeypatch.setattr(download_functions, "get_remote_file_size", lambda *args, **kwargs: 0)

  assert download_functions.verify_download(
    artifact,
    "https://example.com/model.pkl",
    allow_unknown_size=True,
    expected_size=artifact.stat().st_size,
    expected_sha256="02f64c1311bd6392462fa9c7c929b002057f261fdcef2050554c08694e7d2120",
  )
  assert not download_functions.verify_download(
    artifact,
    "https://example.com/model.pkl",
    allow_unknown_size=True,
    expected_size=artifact.stat().st_size + 1,
  )


def test_lfs_pointer_is_not_accepted_as_model(tmp_path, monkeypatch):
  artifact = tmp_path / "model.pkl"
  artifact.write_text(
    "version https://git-lfs.github.com/spec/v1\n"
    f"oid sha256:{'0' * 64}\n"
    "size 123456789\n",
  )
  monkeypatch.setattr(download_functions, "get_remote_file_size", lambda *args, **kwargs: artifact.stat().st_size)
  assert not download_functions.verify_download(artifact, "https://example.com/model.pkl")


def test_multipart_download_is_atomic_and_checksum_verified(tmp_path, monkeypatch):
  payload = b"first part" + b"second part"
  expected_sha = hashlib.sha256(payload).hexdigest()
  part_payloads = {
    "https://example.com/model.pkl.p00": b"first part",
    "https://example.com/model.pkl.p01": b"second part",
  }

  class FakeResponse:
    def __init__(self, data):
      self.data = data
      self.text = data.decode()

    def __enter__(self):
      return self

    def __exit__(self, *args):
      pass

    def raise_for_status(self):
      pass

    def iter_content(self, chunk_size):
      del chunk_size
      yield self.data

  def fake_get(url, **kwargs):
    del kwargs
    if url.endswith(".sha256"):
      return FakeResponse(f"{expected_sha}  model.pkl\n".encode())
    return FakeResponse(part_payloads[url])

  def fake_size(url, **kwargs):
    del kwargs
    return len(part_payloads.get(url, b""))

  class FakeParams:
    def get_bool(self, key):
      del key
      return False

    def put(self, key, value):
      del key, value

  monkeypatch.setattr(download_functions.requests, "get", fake_get)
  monkeypatch.setattr(download_functions, "get_remote_file_size", fake_size)
  destination = tmp_path / "model.pkl"

  assert download_functions.download_multipart_file(
    "cancel", destination, "progress", "https://example.com/model.pkl", "download", FakeParams(),
  )
  assert destination.read_bytes() == payload


def test_multipart_checksum_failure_leaves_no_model(tmp_path, monkeypatch):
  class FakeResponse:
    text = f"{'0' * 64}  model.pkl"

    def __enter__(self):
      return self

    def __exit__(self, *args):
      pass

    def raise_for_status(self):
      pass

    def iter_content(self, chunk_size):
      del chunk_size
      yield b"corrupt"

  monkeypatch.setattr(download_functions.requests, "get", lambda *args, **kwargs: FakeResponse())
  monkeypatch.setattr(
    download_functions,
    "get_remote_file_size",
    lambda url, **kwargs: len(b"corrupt") if url.endswith(".p00") else 0,
  )

  class FakeParams:
    def get_bool(self, key):
      del key
      return False

    def put(self, key, value):
      del key, value

  destination = tmp_path / "model.pkl"
  assert not download_functions.download_multipart_file(
    "cancel", destination, "progress", "https://example.com/model.pkl", "download", FakeParams(),
  )
  assert not destination.exists()


def test_oversized_artifact_split_round_trip(tmp_path):
  artifact = tmp_path / "model.pkl"
  artifact.write_bytes(b"multipart artifact")

  outputs = split_oversized_artifact(artifact, chunk_size=10, force=True)
  part_paths = [path for path in outputs if path.suffix != ".sha256"]
  assert len(part_paths) == 2
  assert b"".join(path.read_bytes() for path in part_paths) == artifact.read_bytes()
