import importlib.util
import json

from types import SimpleNamespace

from test_dashboard_stats import MODULE_DIR, _install_server_import_stubs


def _load_server_module():
  _install_server_import_stubs()
  spec = importlib.util.spec_from_file_location("agnos_update_server", MODULE_DIR / "the_galaxy.py")
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


def _manifest(system_hash):
  return json.dumps([
    {
      "name": "boot",
      "url": "https://example.com/boot.img.xz",
      "hash": "boot-hash",
      "hash_raw": "boot-raw",
      "size": 100,
    },
    {
      "name": "system",
      "url": f"https://example.com/{system_hash}.img.xz",
      "hash": system_hash,
      "hash_raw": system_hash,
      "size": 900,
    },
  ])


def test_agnos_status_detects_manifest_change_from_local_git_object(monkeypatch):
  server = _load_server_module()
  local_commit = "a" * 40
  remote_commit = "b" * 40
  local_manifest = _manifest("old-system")
  remote_manifest = _manifest("new-system")

  def fake_git_stdout(repo_path, args, timeout=15):
    assert repo_path == "/repo"
    if args == ["show", f"{local_commit}:{server._AGNOS_MANIFEST_PATH}"]:
      return local_manifest
    if args == ["show", f"{remote_commit}:{server._AGNOS_MANIFEST_PATH}"]:
      return remote_manifest
    raise AssertionError(args)

  monkeypatch.setattr(server, "_git_stdout", fake_git_stdout)
  monkeypatch.setattr(server, "_git_has_commit", lambda repo_path, commit: commit == remote_commit)

  status = server._build_agnos_update_status("/repo", "owner/repo", local_commit, remote_commit, "main")

  assert status["checked"] is True
  assert status["available"] is True
  assert status["changedPartitions"] == ["system"]
  assert status["estimatedDownloadMb"] == 900
  assert "physically access" in " ".join(status["warnings"])


def test_agnos_status_ignores_same_manifest_content(monkeypatch):
  server = _load_server_module()
  local_commit = "a" * 40
  remote_commit = "b" * 40
  manifest = _manifest("same-system")

  def fake_git_stdout(repo_path, args, timeout=15):
    if args in (
      ["show", f"{local_commit}:{server._AGNOS_MANIFEST_PATH}"],
      ["show", f"{remote_commit}:{server._AGNOS_MANIFEST_PATH}"],
    ):
      return manifest
    raise AssertionError(args)

  monkeypatch.setattr(server, "_git_stdout", fake_git_stdout)
  monkeypatch.setattr(server, "_git_has_commit", lambda repo_path, commit: commit == remote_commit)

  status = server._build_agnos_update_status("/repo", "owner/repo", local_commit, remote_commit, "main")

  assert status["checked"] is True
  assert status["available"] is False
  assert status["changedPartitions"] == []


def test_agnos_status_fetches_remote_manifest_from_github_when_commit_is_not_local(monkeypatch):
  server = _load_server_module()
  local_commit = "a" * 40
  remote_commit = "b" * 40
  local_manifest = _manifest("old-system")
  remote_manifest = _manifest("new-system")
  requested_urls = []

  def fake_git_stdout(repo_path, args, timeout=15):
    if args == ["show", f"{local_commit}:{server._AGNOS_MANIFEST_PATH}"]:
      return local_manifest
    raise AssertionError(args)

  def fake_get(url, timeout):
    requested_urls.append((url, timeout))
    return SimpleNamespace(text=remote_manifest, raise_for_status=lambda: None)

  monkeypatch.setattr(server, "_git_stdout", fake_git_stdout)
  monkeypatch.setattr(server, "_git_has_commit", lambda repo_path, commit: False)
  monkeypatch.setattr(server.requests, "get", fake_get)

  status = server._build_agnos_update_status(
    "/repo",
    "https://github.com/owner/repo.git",
    local_commit,
    remote_commit,
    "main",
  )

  assert status["checked"] is True
  assert status["available"] is True
  assert requested_urls == [(
    f"https://raw.githubusercontent.com/owner/repo/{remote_commit}/{server._AGNOS_MANIFEST_PATH}",
    server._AGNOS_REMOTE_MANIFEST_TIMEOUT_S,
  )]
