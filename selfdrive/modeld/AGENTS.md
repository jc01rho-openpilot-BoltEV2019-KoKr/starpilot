# MODEL INFERENCE KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

ML model inference for perception/prediction: lane detection, path planning, lead vehicle tracking.

## STRUCTURE

```
selfdrive/modeld/
├── models/             # Model outputs
│   ├── driving_model_frame.h  # C++ struct for outputs
│   └── commonmodel.h          # Common model types
├── runners/            # Inference backends
│   ├── thneed.py       # TICI hardware acceleration
│   ├── onnx.py         # CPU/GPU ONNX runtime
│   └── tinygrad.py     # Tinygrad runner (frogpilot)
├── __init__.py         # Model exports
├── dmonitoringmodel.py # Driver monitoring model
└── test/               # Model tests
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Model inputs | `models/commonmodel.h` | Input frame, width, height |
| Model outputs | `models/driving_model_frame.h` | `pathPlan`, `leadData`, `meta` |
| Thneed runner | `runners/thneed.py` | TICI NPU acceleration |
| ONNX runner | `runners/onnx.py` | Fallback for x86_64 |
| Model loading | `__init__.py` | `ModelManager` class |
| Driver monitoring | `dmonitoringmodel.py` | Face tracking |

## CONVENTIONS

**Model inputs:**
```python
# Input: RGB frame (1208x1920 on TICI)
frame = np.zeros((1208, 1920, 3), dtype=np.uint8)
# Or model-specific crop from camera frames
```

**Model outputs:**
```c
// From driving_model_frame.h
ModelData {
  PathPlan pathPlan;      // Desired path
  LeadDataV3 leadDataV3;  // Lead vehicle data
  Meta meta;              // Metadata (speed, state)
}
```

**Runner selection:**
```python
if on_tici:
    runner = ThneedRunner(model_path)
else:
    runner = ONNXRunner(model_path)
```

**Model versions:**
- `selfdrive/assets/models/supercombo.dlc`: latest
- Version in `constants.py`: `MODEL_VERSION`
- Mismatch = crash, check file hash

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Hardcode model path | Use `ModelManager.getModelPath()` |
| Skip version check | Model mismatch → crash |
| Bypass `ModelManager` | Direct loading breaks caching |
| Modify model outputs | Use as-is, don't post-process |
| Ignore TICI fallback | Must work on x86_64 for testing |

## COMMANDS

```bash
# Model tests
pytest selfdrive/modeld/test/test_modeld.py

# Model benchmarking
python selfdrive/modeld/test/benchmark.py

# Model conversion
python tools/model_conversion/convert.py
```

## NOTES

**Model runners:**
- **Thneed**: Qualcomm SNPE, TICI NPU acceleration (fastest)
- **ONNX**: CPU/GPU, portable, slower (~10-15 FPS)
- **Tinygrad**: FrogPilot alternative, supports various backends

**Model outputs:**
- `pathPlan`: Desired path (polyline)
- `leadData`: Lead vehicle position, speed, distance
- `meta`: Model metadata, confidence scores

**FrogPilot extras:**
- `frogpilot/classic_modeld/`: Legacy model support
- `frogpilot/tinygrad_modeld/`: Tinygrad inference
- `frogpilot/assets/nnff_models/`: Custom models
