import io
from types import MethodType

import numpy as np

from openpilot.selfdrive.modeld import modeld
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


def test_external_gpu_probe_matches_upstream_retry_loop(monkeypatch):
  from openpilot.system.hardware.chestnut import flash

  calls = []
  results = iter((False, False, True))
  monkeypatch.setattr(flash, "link_up", lambda: calls.append("probe") or next(results))
  monkeypatch.setattr(model_compiler.time, "sleep", lambda seconds: calls.append(("sleep", seconds)))

  model_compiler.wait_for_external_gpu()

  assert calls == ["probe", ("sleep", 1), "probe", ("sleep", 1), "probe"]


def test_external_gpu_warmup_runs_a_complete_frame_and_resets(monkeypatch):
  class FakeTensor:
    @staticmethod
    def zeros(shape, **kwargs):
      calls.append(("tensor", shape, kwargs))
      return FakeTensor()

    def realize(self):
      return self

  calls = []
  state = modeld.ModelState.__new__(modeld.ModelState)
  state.frame_buf_size = 32
  state.vision_input_names = ["img", "big_img"]
  state._blob_cache = {}
  state._warp_dev = "QCOM"
  state.desire_key = "desire"
  state.prev_desired_curv_key = "prev_desired_curv"
  state.numpy_inputs = {
    "desire": np.zeros((1, 8), dtype=np.float32),
    "traffic_convention": np.zeros((1, 2), dtype=np.float32),
    "action_t": np.zeros((1, 2), dtype=np.float32),
    "prev_desired_curv": np.zeros((1, 5, 1), dtype=np.float32),
  }

  def fake_run(self, bufs, transforms, inputs, prepare_only):
    calls.append((
      "run",
      {key: value.shape for key, value in bufs.items()},
      {key: value.shape for key, value in transforms.items()},
      {key: value.shape for key, value in inputs.items()},
      prepare_only,
    ))
    return {}

  state.run = MethodType(fake_run, state)
  state._reset_state = MethodType(lambda self: calls.append(("reset",)), state)
  monkeypatch.setattr(modeld, "Tensor", FakeTensor)

  state.warmup()

  assert calls == [
    ("tensor", (32,), {"dtype": "uint8", "device": "QCOM"}),
    ("tensor", (32,), {"dtype": "uint8", "device": "QCOM"}),
    (
      "run",
      {"img": (32,), "big_img": (32,)},
      {"img": (3, 3), "big_img": (3, 3)},
      {"desire": (8,), "traffic_convention": (2,), "action_t": (2,)},
      False,
    ),
    ("reset",),
  ]
