#!/usr/bin/env python3
import argparse
import pickle
import time

from tinygrad.device import Device
from tinygrad.engine.jit import TinyJit
from tinygrad.tensor import Tensor

from openpilot.selfdrive.modeld.compile_modeld import NV12Frame, _parse_size, warp_perspective_tinygrad
from openpilot.system.camerad.cameras.nv12_info import get_nv12_info


def make_warp_dm(nv12: NV12Frame, dm_w: int, dm_h: int):
  cam_w, cam_h, stride, _, _, _ = nv12
  stride_pad = stride - cam_w

  def warp_dm(input_frame, matrix_inverse):
    matrix_inverse = matrix_inverse.to(Device.DEFAULT).realize()
    return warp_perspective_tinygrad(
      input_frame[:cam_h * stride],
      matrix_inverse,
      (dm_w, dm_h),
      (cam_h, cam_w),
      stride_pad,
      border_fill_val=16,
    ).reshape(-1, dm_h * dm_w)

  return warp_dm


def compile_dm_warp(nv12: NV12Frame, dm_w: int, dm_h: int, pkl_path: str) -> None:
  print(f"Compiling DM warp for {nv12.width}x{nv12.height} -> {dm_w}x{dm_h}...")
  warp_dm_jit = TinyJit(make_warp_dm(nv12, dm_w, dm_h), prune=True)

  for index in range(10):
    frame = Tensor.randint(nv12.size, low=0, high=256, dtype="uint8").realize()
    matrix_inverse = Tensor(Tensor.randn(3, 3).mul(8).realize().numpy(), device="NPY")
    Device.default.synchronize()
    start = time.perf_counter()
    warp_dm_jit(frame, matrix_inverse).realize()
    queued = time.perf_counter()
    Device.default.synchronize()
    end = time.perf_counter()
    print(f"  [{index + 1}/10] enqueue {(queued - start) * 1e3:6.2f} ms -- total {(end - start) * 1e3:6.2f} ms")

  with open(pkl_path, "wb") as artifact_file:
    pickle.dump(warp_dm_jit, artifact_file)
  print(f"  saved {pkl_path}")


def main() -> int:
  parser = argparse.ArgumentParser()
  parser.add_argument("--camera-resolution", type=_parse_size, required=True, help="Camera resolution WxH")
  parser.add_argument("--warp-to", type=_parse_size, required=True, help="DM input resolution WxH")
  parser.add_argument("--output", required=True)
  args = parser.parse_args()

  cam_w, cam_h = args.camera_resolution
  nv12 = NV12Frame(cam_w, cam_h, *get_nv12_info(cam_w, cam_h))
  dm_w, dm_h = args.warp_to
  compile_dm_warp(nv12, dm_w, dm_h, args.output)
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
