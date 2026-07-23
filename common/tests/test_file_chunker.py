from pathlib import Path

from openpilot.common import file_chunker


def test_chunked_stream_round_trip(tmp_path, monkeypatch):
  monkeypatch.setattr(file_chunker, "CHUNK_SIZE", 7)
  path = tmp_path / "artifact.pkl"
  payload = b"a model artifact spanning several chunks"
  path.write_bytes(payload)

  targets = file_chunker.get_chunk_targets(path, len(payload))
  file_chunker.chunk_file(path, targets)

  assert file_chunker.file_chunked_exists(path)
  assert file_chunker.read_file_chunked(path) == payload
  with file_chunker.open_file_chunked(path) as stream:
    assert stream.read(9) + stream.read() == payload


def test_unchunked_stream_does_not_materialize_file(tmp_path, monkeypatch):
  path = tmp_path / "fat.onnx"
  payload = b"large model read through bounded buffers"
  path.write_bytes(payload)
  original_read_bytes = Path.read_bytes

  def reject_whole_file_read(candidate):
    if candidate == path:
      raise AssertionError("streaming must not call Path.read_bytes()")
    return original_read_bytes(candidate)

  monkeypatch.setattr(Path, "read_bytes", reject_whole_file_read)
  with file_chunker.open_file_chunked(path) as stream:
    assert stream.read() == payload
