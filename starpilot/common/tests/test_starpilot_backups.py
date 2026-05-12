from types import SimpleNamespace

from openpilot.starpilot.common import starpilot_backups as sb


class FakeParams:
  def __init__(self, minimum_backup_size=0):
    self.minimum_backup_size = minimum_backup_size

  def get_int(self, _key, return_default=False, default=0):
    return self.minimum_backup_size if self.minimum_backup_size is not None else default

  def put_int(self, _key, value):
    self.minimum_backup_size = value


def test_get_directory_size_skips_filtered_files(tmp_path):
  (tmp_path / ".git").mkdir()
  (tmp_path / ".git" / "ignored.pack").write_bytes(b"123456")
  (tmp_path / "keep.py").write_bytes(b"abcd")
  (tmp_path / "skip.pyc").write_bytes(b"zzzzzz")

  assert sb.get_directory_size(tmp_path) == 4


def test_backup_starpilot_skips_when_free_space_is_below_floor(tmp_path, monkeypatch):
  monkeypatch.setattr(sb, "STARPILOT_BACKUPS", tmp_path / "backups")
  monkeypatch.setattr(sb.shutil, "disk_usage", lambda _path: (10, 9, sb.MINIMUM_BACKUP_FREE_BYTES - 1))

  called = False

  def fake_create_backup(*args, **kwargs):
    nonlocal called
    called = True

  monkeypatch.setattr(sb, "create_backup", fake_create_backup)

  build_metadata = SimpleNamespace(channel="devel", openpilot=SimpleNamespace(git_commit="abcdef123456"))
  sb.backup_starpilot(build_metadata, FakeParams())

  assert called is False


def test_backup_starpilot_uses_estimated_size_on_first_backup(tmp_path, monkeypatch):
  monkeypatch.setattr(sb, "STARPILOT_BACKUPS", tmp_path / "backups")
  monkeypatch.setattr(sb, "BASEDIR", str(tmp_path / "source"))
  monkeypatch.setattr(sb, "get_directory_size", lambda _path: 100)
  monkeypatch.setattr(sb.shutil, "disk_usage", lambda _path: (1000, 650, 350))

  called = False

  def fake_create_backup(*args, **kwargs):
    nonlocal called
    called = True

  monkeypatch.setattr(sb, "create_backup", fake_create_backup)

  build_metadata = SimpleNamespace(channel="devel", openpilot=SimpleNamespace(git_commit="abcdef123456"))
  sb.backup_starpilot(build_metadata, FakeParams(minimum_backup_size=0))

  assert called is False


def test_backup_tar_filter_excludes_git_and_build_artifacts():
  assert sb.backup_tar_filter(sb.tarfile.TarInfo("backup/.git/objects/pack")) is None
  assert sb.backup_tar_filter(sb.tarfile.TarInfo("backup/selfdrive/module.pyc")) is None
  assert sb.backup_tar_filter(sb.tarfile.TarInfo("backup/selfdrive/module.py")) is not None


def test_create_backup_removes_partial_archive_on_oserror(tmp_path, monkeypatch):
  source = tmp_path / "source"
  source.mkdir()
  (source / "keep.txt").write_text("ok")

  destination = tmp_path / "backups" / "sample_auto"
  destination.parent.mkdir()

  class FailingTar:
    def __enter__(self):
      return self

    def __exit__(self, exc_type, exc, tb):
      return False

    def add(self, *args, **kwargs):
      raise OSError("disk full")

  monkeypatch.setattr(sb.tarfile, "open", lambda *args, **kwargs: FailingTar())

  params = FakeParams(minimum_backup_size=123)
  sb.create_backup(source, destination, "ok", "fail", params, compressed=True)

  assert not (destination.parent / "sample_auto_in_progress.tar.zst").exists()
  assert not (destination.parent / "sample_auto.tar.zst").exists()
  assert params.minimum_backup_size == 123


def test_create_backup_updates_minimum_backup_size_with_latest_archive_size(tmp_path):
  source = tmp_path / "source"
  source.mkdir()
  (source / "a.txt").write_text("small")

  destination = tmp_path / "backups" / "first_auto"
  destination.parent.mkdir()
  params = FakeParams()

  sb.create_backup(source, destination, "ok", "fail", params, compressed=True)
  first_size = (destination.parent / "first_auto.tar.zst").stat().st_size

  (source / "b.txt").write_text("larger payload" * 4096)
  second_destination = destination.parent / "second_auto"
  sb.create_backup(source, second_destination, "ok", "fail", params, compressed=True)
  second_size = (destination.parent / "second_auto.tar.zst").stat().st_size

  assert params.minimum_backup_size == second_size
  assert second_size >= first_size
