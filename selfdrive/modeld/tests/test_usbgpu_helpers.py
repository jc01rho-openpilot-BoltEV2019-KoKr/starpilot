import io

import numpy as np

from openpilot.selfdrive.modeld.helpers import dump_oob, load_oob, tinygrad_dev_config
from scripts import model_compiler


def test_external_gpu_keeps_the_native_device_available():
  assert tinygrad_dev_config(True, tici=True) == "QCOM;USB+AMD:LLVM"
  assert tinygrad_dev_config(False, tici=True) == "QCOM"
  assert tinygrad_dev_config(True, tici=False) == "CPU:LLVM;USB+AMD:LLVM"


def test_out_of_band_artifact_round_trip():
  artifact = {"weights": np.arange(32, dtype=np.float32), "metadata": {"version": 1}}
  stream = io.BytesIO()
  dump_oob(artifact, stream)
  stream.seek(0)

  restored = load_oob(stream)
  assert restored["metadata"] == artifact["metadata"]
  np.testing.assert_array_equal(restored["weights"], artifact["weights"])


def test_external_gpu_probe_retries_until_pcie_is_ready(monkeypatch):
  calls = []
  probe_count = 0
  def probe():
    nonlocal probe_count
    probe_count += 1
    calls.append("probe")
    return (False, "LTSSM=0x00") if probe_count < 3 else (True, "LTSSM=0x78")
  monkeypatch.setattr(
    model_compiler,
    "_probe_external_gpu_link_once",
    probe,
  )
  monkeypatch.setattr(model_compiler.time, "sleep", lambda seconds: calls.append(("sleep", seconds)))

  model_compiler.wait_for_external_gpu({"PYTHONPATH": "/tmp/openpilot"})

  assert calls == ["probe", ("sleep", 1), "probe", ("sleep", 1), "probe"]


def test_external_gpu_probe_reports_failure(monkeypatch):
  monkeypatch.setattr(model_compiler, "_probe_external_gpu_link_once", lambda: (False, "link unavailable"))
  monkeypatch.setattr(model_compiler.time, "sleep", lambda _: None)

  assert model_compiler.wait_for_external_gpu({}) is False
