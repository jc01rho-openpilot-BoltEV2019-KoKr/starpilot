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
