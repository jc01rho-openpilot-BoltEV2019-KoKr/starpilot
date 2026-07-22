import hashlib
from pathlib import Path
import tempfile
import unittest
from unittest import mock

import numpy as np
import zstandard
import tinygrad.helpers
from tinygrad.helpers import _decompress_zstd, fetch_fw, polyN, is_numpy_ndarray
from tinygrad.tensor import Tensor

class TestPolyN(unittest.TestCase):
  def test_tensor(self):
    np.testing.assert_allclose(polyN(Tensor([1.0, 2.0, 3.0, 4.0]), [1.0, -2.0, 1.0]).numpy(), [0.0, 1.0, 4.0, 9.0])

class TestIsNumpyNdarray(unittest.TestCase):
  def test_tensor_numpy(self):
    self.assertTrue(is_numpy_ndarray(Tensor([1, 2, 3]).numpy()))

class TestZstd(unittest.TestCase):
  def test_decompress(self):
    payload = b"local firmware payload"
    compressed = zstandard.ZstdCompressor().compress(payload)
    self.assertEqual(_decompress_zstd(compressed), payload)

  def test_fetch_fw_uses_local_zstd(self):
    payload = b"local firmware payload"
    with tempfile.TemporaryDirectory() as tmp:
      firmware = Path(tmp) / "firmware.bin.zst"
      firmware.write_bytes(zstandard.ZstdCompressor().compress(payload))
      with mock.patch.object(tinygrad.helpers.pathlib, "Path", return_value=firmware), \
           mock.patch.object(tinygrad.helpers, "fetch") as remote_fetch:
        self.assertEqual(fetch_fw("amdgpu", "firmware.bin", hashlib.sha256(payload).hexdigest()), payload)
        remote_fetch.assert_not_called()

if __name__ == '__main__':
  unittest.main()
