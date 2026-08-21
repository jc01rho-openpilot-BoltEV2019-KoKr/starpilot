from openpilot.selfdrive.modeld import dmonitoringmodeld


class FakeParams:
  def __init__(self, active: bool):
    self.active = active

  def get_bool(self, key: str) -> bool:
    assert key == "UsbGpuActive"
    return self.active


def test_non_gpu_affinity_is_unchanged(monkeypatch):
  calls = []
  monkeypatch.setattr(dmonitoringmodeld, "set_core_affinity", calls.append)

  assert not dmonitoringmodeld.update_external_gpu_affinity(FakeParams(False), False)
  assert calls == []


def test_external_gpu_adds_idle_camera_core(monkeypatch):
  calls = []
  monkeypatch.setattr(dmonitoringmodeld, "set_core_affinity", calls.append)

  assert dmonitoringmodeld.update_external_gpu_affinity(FakeParams(True), False)
  assert calls == [dmonitoringmodeld.EXTERNAL_GPU_AFFINITY_CORES]

  calls.clear()
  assert dmonitoringmodeld.update_external_gpu_affinity(FakeParams(True), True)
  assert calls == []


def test_affinity_returns_to_upstream_default_after_gpu_fallback(monkeypatch):
  calls = []
  monkeypatch.setattr(dmonitoringmodeld, "set_core_affinity", calls.append)

  assert not dmonitoringmodeld.update_external_gpu_affinity(FakeParams(False), True)
  assert calls == [dmonitoringmodeld.DEFAULT_AFFINITY_CORES]
