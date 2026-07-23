#!/usr/bin/env python3
import io
import math
import os
import sys
from pathlib import Path

CHUNK_SIZE = 45 * 1024 * 1024  # 45MB, under GitHub's 50MB limit


def get_chunk_name(name, idx, num_chunks):
  return f"{name}.chunk{idx + 1:02d}of{num_chunks:02d}"


def get_manifest_path(name):
  return f"{name}.chunkmanifest"


def _chunk_paths(path, num_chunks):
  return [get_manifest_path(path)] + [get_chunk_name(path, i, num_chunks) for i in range(num_chunks)]


def get_chunk_paths(path, file_size):
  num_chunks = math.ceil(file_size / CHUNK_SIZE)
  return _chunk_paths(path, num_chunks)


get_chunk_targets = get_chunk_paths


def chunk_file(path, targets):
  manifest_path, *chunk_paths = targets
  with open(path, 'rb') as f:
    data = f.read()
  actual_num_chunks = max(1, math.ceil(len(data) / CHUNK_SIZE))
  assert len(chunk_paths) >= actual_num_chunks, f"Allowed {len(chunk_paths)} chunks but needs at least {actual_num_chunks}, for path {path}"
  for i, chunk_path in enumerate(chunk_paths):
    with open(chunk_path, 'wb') as f:
      f.write(data[i * CHUNK_SIZE:(i + 1) * CHUNK_SIZE])
  Path(manifest_path).write_text(str(len(chunk_paths)))
  os.remove(path)


def get_existing_chunks(path):
  if os.path.isfile(path):
    return [path]
  manifest_path = get_manifest_path(path)
  if os.path.isfile(manifest_path):
    num_chunks = int(Path(manifest_path).read_text().strip())
    return _chunk_paths(path, num_chunks)
  raise FileNotFoundError(path)


def file_chunked_exists(path) -> bool:
  return os.path.isfile(path) or os.path.isfile(get_manifest_path(path))


class ChunkStream(io.RawIOBase):
  def __init__(self, paths):
    self._paths = iter(paths)
    self._file = None

  def readable(self):
    return True

  def readinto(self, buffer):
    count = 0
    view = memoryview(buffer)
    while count < len(buffer):
      if self._file is None:
        path = next(self._paths, None)
        if path is None:
          break
        self._file = open(path, "rb")
      bytes_read = self._file.readinto(view[count:])
      if not bytes_read:
        self._file.close()
        self._file = None
        continue
      count += bytes_read
    return count

  def close(self):
    if self._file is not None:
      self._file.close()
      self._file = None
    super().close()


def open_file_chunked(path):
  chunks = get_existing_chunks(path)
  if chunks and chunks[0] == get_manifest_path(path):
    chunks = chunks[1:]
  return io.BufferedReader(ChunkStream(chunks))


def read_file_chunked(path):
  manifest_path = get_manifest_path(path)
  if os.path.isfile(manifest_path):
    num_chunks = int(Path(manifest_path).read_text().strip())
    return b''.join(Path(get_chunk_name(path, i, num_chunks)).read_bytes() for i in range(num_chunks))
  if os.path.isfile(path):
    return Path(path).read_bytes()
  raise FileNotFoundError(path)


if __name__ == "__main__":
  file_path = sys.argv[1]
  chunk_file(file_path, get_chunk_targets(file_path, os.path.getsize(file_path)))
