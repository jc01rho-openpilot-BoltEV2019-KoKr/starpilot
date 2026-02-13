# CONTROLS KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Lateral and longitudinal control algorithms: PID, MPC, actuator limits, safety checks.

## STRUCTURE

```
selfdrive/controls/
├── lib/                # Control utilities
│   ├── longitudinal_mpc.py  # Model predictive control
│   ├── latcontrol_pid.py   # Lateral PID
│   ├── latcontrol_indi.py  # Lateral INDI
│   └── vehicle_model.py    # Vehicle dynamics model
├── __init__.py         # Control exports
└── test/               # Control tests
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Lateral PID | `lib/latcontrol_pid.py` | Basic steering control |
| Lateral INDI | `lib/latcontrol_indi.py` | Advanced lateral (frogpilot) |
| Longitudinal MPC | `lib/longitudinal_mpc.py` | Distance control, stop/go |
| Vehicle model | `lib/vehicle_model.py` | Dynamics, tire model |
| Actuator limits | `car.values.py` (in car/) | `steerMax`, `gasMax`, `brakeMax` |
| Safety checks | `__init__.py` | `calcActuators()` clamping |

## CONVENTIONS

**Lateral control:**
```python
def update(self, active, v_ego, angle_steers, steer_override):
    # Returns: steerActuator (float, -1 to 1)
    # Uses: pathPlan (from modeld), carState
    pass
```

**Longitudinal control:**
```python
def update(self, active, v_ego, v_target, a_target, lead_veh):
    # Returns: gas, brake (float, 0 to 1)
    # Uses: lead_data, longControlState
    pass
```

**Actuator clamping:**
```python
gas = clip(gas, 0, gasMax)
brake = clip(brake, 0, brakeMax)
steer = clip(steer, -steerMax, steerMax)
```

**Safety:**
- `latActive` only if `steeringPressed < 1.0`
- `longActive` only if `gasPressed < 0.1`
- Emergency: `controlsState.longControlState = LongCtrlState.stop`

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Bypass actuator limits | Safety violation |
| Ignore `steeringPressed` | Override detection failure |
| Skip `calcActuators()` clamping | Unsafe outputs |
| Hardcode gains | Use `car.CarParams` dynamic gains |
| Modify `pathPlan` | Use modeld output, don't override |

## COMMANDS

```bash
# Control tests
pytest selfdrive/controls/test/ -v

# Simulation
python tools/sim/sim.py --controls
```

## NOTES

**Control modes:**
- LatControl: PID (default), INDI (frogpilot)
- LongControl: PID, MPC (stop/go)

**Gains:**
- Lateral: `steerKp`, `steerKi`, `steerKd` (in car params)
- Longitudinal: `kpP`, `kpI`, `kd` (in longitudinal_mpc.py)

**FrogPilot extras:**
- `frogpilot/controls/latcontrol.py` (INDI)
- `frogpilot/controls/longcontrol.py` (aggressive personalities)
- `frogpilot/controls/stopdetector.py` (stop sign detection)
