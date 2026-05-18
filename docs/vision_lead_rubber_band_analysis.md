# Vision Lead Rubber-banding Analysis & Safety Evaluation

**Date**: 2026-05-19
**Branch**: paddle5
**Author**: AI-assisted analysis with multi-LLM council review

---

## Problem Statement

야간 vision-only (radar 없음) 주행 시 앞차를 따라가는 동안 속도 진동(rubber-banding) 발생.

### Typical Scenario
- **설정속도**: 90 km/h, **앞차속도**: 85 km/h
- **속도차**: 5 km/h (1.39 m/s) — `VISION_LEAD_APPROACH_MIN_CLOSING_SPEED = 2.0` 미만
- **Vision 거리 노이즈**: ±5~10m (야간)
- **진동 진폭**: 90→70→90 km/h (20 km/h)
- **t_follow**: 이미 2.20s (충분히 큰 값)

### Root Cause
1. Vision-only lead의 야간 거리 노이즈(±5~10m)가 MPC에 직접 전달됨
2. MPC가 노이즈를 실제 거리 변화로 오인 → 과도한 가감속 명령
3. `get_vision_lead_approach_cap()`이 트리거되지 않음 (closing_speed < 2.0 m/s)
4. 결과적으로 순수 MPC 비용 함수만이 제어 → 노이즈에 과민 반응

---

## 3 Proposed Modifications & Safety Evaluation

### Mod 1: `acceleration_jerk`/`danger_jerk` Uncertainty 스케일링

**변경 위치**: `selfdrive/controls/lib/longitudinal_mpc_lib/long_mpc.py`

```python
# Before
if 0.45 <= uncertainty < 0.60:
    scale = float(np.interp(uncertainty, [0.45, 0.60], [1.2, 1.5]))
    speed_jerk *= scale  # ← speed_jerk만

# After
if 0.45 <= uncertainty < 0.60:
    scale = float(np.interp(uncertainty, [0.45, 0.60], [1.2, 1.5]))
    speed_jerk *= scale
    acceleration_jerk *= scale  # NEW
    danger_jerk *= scale        # NEW
```

| 항목             | 평가                                                                                   |
| ---------------- | -------------------------------------------------------------------------------------- |
| **안전성 위험도**    | **Low/Minimal** — MPC 비용 함수의 jerk 페널티 증가. 급제동 시 panic bypass가 우회하여 안전 보장 |
| **Panic Bypass** | 간섭 없음 — slope-based bypass는 독립적으로 작동                                           |
| **효과**             | Small~Medium — uncertainty 0.45~0.60 범위 의존적. 이 범위 도달 빈도에 따라 효과 가변적. 정량적 검증 필요 |
| **엣지 케이스**      | 컷인/급정거 시에도 panic bypass가 filter_time_factor=0.0으로 설정 → 빠른 반응 유지               |

**Council 결과**: ✅ **Go** (가장 안전한 개선안)

---

### Mod 2: Approach Cap에 Filtered `lead_dist_f` 사용

**변경 위치**: `selfdrive/controls/lib/longitudinal_planner.py`

```python
# Before
gap_to_tight_follow = float(lead.dRel) - tight_follow_gap  # raw dRel

# After
gap_to_tight_follow = float(self.lead_dist_f) - tight_follow_gap  # filtered
```

| 항목             | 평가                                                                                   |
| ---------------- | -------------------------------------------------------------------------------------- |
| **안전성 위험도**    | **High** — 필터 지연(Lag)으로 앞차 거리 감소 인식 지연                                         |
| **충돌 위험**      | 앞차 급정거/컷인 시 제동 시점 늦춰짐 → 충돌 가능성 증가                                          |
| **효과**             | High — 고무줄 현상 크게 감소 (하지만 안전을 담보로 얻는 것)                                        |
| **안전 방어벽**    | `get_vision_lead_approach_cap`은 safety-critical limit 로직 → raw 데이터 유지 필수                   |

**Council 결과**: ❌ **No-Go** (안전과 직결된 로직에 필터링 적용 불가)

---

### Mod 3: EMA Alpha Uncertainty 연동

**변경 위치**: `selfdrive/controls/lib/longitudinal_planner.py`

```python
# Before
alpha = max(0.02, min(0.15, 0.05 + 0.002 * v_ego))

# After
alpha = max(0.02, min(0.15, 0.05 + 0.002 * v_ego))
alpha *= max(0.3, 1.0 - uncertainty * 0.5)  # uncertainty 높으면 alpha 30~70% 감소
```

| 항목             | 평가                                                                                   |
| ---------------- | -------------------------------------------------------------------------------------- |
| **안전성 위험도**    | **Critical** — 시스템 설계 철학과 정면 충돌                                                    |
| **현재 설계**      | uncertainty > 0.45 → 필터 약화 (빠른 반응), > 0.70 → 필터 완전 해제                              |
| **제안 설계**      | uncertainty 높음 → 필터 강화 (느린 반응) → 위험 상황에서 오히려 반응성 저하                           |
| **충돌 위험**      | 야간/악천후 등 불확실성이 높은 상황에서 앞차 급정거 시 거리 감소를 한참 뒤에 인식 → 심각한 추돌 위험       |
| **효과**             | High — 진동은 사라지지만 자율주행이 아닌 맹목적 크루즈 수준으로 전락                                  |

**Council 결과**: ❌ **No-Go** (자율주행 제어의 안티 패턴 — 절대 적용 불가)

---

## Final Recommendation

### ✅ 적용 권장: Mod 1만

```python
# longitudinal_mpc_lib/long_mpc.py:476-479
if 0.45 <= uncertainty < 0.60:
    scale = float(np.interp(uncertainty, [0.45, 0.60], [1.2, 1.5]))
    speed_jerk *= scale
    acceleration_jerk *= scale  # NEW
    danger_jerk *= scale        # NEW
```

### ⚠️ 적용 금지: Mod 2, Mod 3

이 두 수정은 safety-critical 로직에 필터링 지연을 도입하여 추돌 위험을 증가시킵니다.

---

## Alternative Approaches (Mod 1 효과가 부족할 경우)

### 1. Custom Personalities UI 설정 (코드 수정 없음)

차량 UI → Standard Personality에서 다음 값 설정:

| 설정                     | UI 입력값 | 실제 MPC 값 | 효과                  |
| ------------------------ | --------- | ----------- | --------------------- |
| Acceleration Smoothness  | 180       | 1.80        | 가속 변화 억제 ×1.8       |
| Braking Smoothness       | 180       | 1.80        | 감속 변화 억제 ×1.8       |
| Safety Gap Bias          | 150       | 1.50        | 안전 간격 증가 ×1.5       |
| Slowdown Response        | 150       | 1.50        | 감속 부드러움 ×1.5        |
| Speed-Up Response        | 150       | 1.50        | 가속 부드러움 ×1.5        |

### 2. Approach Cap 약화 (코드 수정)

```python
# longitudinal_planner.py:41
VISION_LEAD_APPROACH_MAX_DECEL = 0.30  # 0.55 → 0.30
VISION_LEAD_APPROACH_TRIGGER_TIME = 3.5  # 4.5 → 3.5
```

**안전성**: **High (No-Go)** — Approach Cap 약화는 안전성 저하가 명확함. MPC가 독립적으로 처리하더라도, `VISION_LEAD_APPROACH_MAX_DECEL`을 0.30으로 낮추면 실제 위험 상황(급정거, 컷인)에서 감속이 불충분해질 가능성이 높음. Council 평가: No-Go로 재분류 권장.

### 3. Lead Filter 강화 (코드 수정)

```python
# longitudinal_mpc_lib/long_mpc.py
LEAD_FILTER_TIME_HIGH = 2.5   # 1.8 → 2.5
```

**안전성**: Low — 기존 메커니즘 활용, panic bypass로 안전 보장

---

## Key Safety Principles

1. **Safety-critical limit 로직에는 raw 데이터 사용** — 필터링된 데이터로 접근 cap 계산 금지
2. **Uncertainty 높을수록 응답성 유지** — 필터 약화가 원칙, 필터 강화 금지
3. **Panic bypass는 절대 무력화하지 않음** — 모든 수정은 bypass와 독립적이어야 함
4. **Cost 함수 조정 > 데이터 조작** — MPC의 비용 함수를 통해 부드럽게 유도하는 것이 안전한 접근

---

## Council Review Details

| Councillor | Response | Status     |
| ---------- | -------- | ---------- |
| beta (gemini-pro) | Full analysis — Mod 1 Go, Mod 2 No-Go, Mod 3 No-Go | ✅ Complete |
| alpha (opus)      | —                                                | ⏱️ Timed out |
| gamma (lower-coding) | —                                             | ⏱️ Timed out |

**Consensus**: Mod 1만 Go, 나머지는 No-Go (1명 응답, 보수적 평가)

---

## Council Re-Evaluation (2nd Round)

**Date**: 2026-05-19
**Councillor**: beta (gemini-pro) — ✅ Complete | alpha (opus) — ⏱️ Timed out | gamma — ⏱️ Timed out

### Key Findings

1. **Mod 1 효과 재평가**: "Medium" → **"Small~Medium"** — uncertainty 0.45~0.60 범위 의존적. 이 범위를 벗어나면 효과 0.
2. **Alternative 2 재분류**: "Medium" → **"High/No-Go"** — Approach Cap 약화는 안전성 저하가 명확.
3. **Mod 1 단독 부족**: Mod 1만으로는 20 km/h 진동 억제가 불충분할 가능성 높음. **Alternative 3 (Lead Filter 강화) 병행 필수.**
4. **누락 분석 발견**:
   - `dist_factor`가 이미 `acceleration_jerk`/`danger_jerk`에 적용 중 → Mod 1과 중복/상호작용 분석 필요
   - `a_change_cost = acceleration_jerk` → Mod 1이 a_change_cost에도 간접 영향
   - MPC solver feasibility: jerk 비용 1.5배 증가 시 infeasible solution 가능성
   - 야간 uncertainty 분포에 대한 실증 데이터 부재

### Recommended Application Strategy

| Phase | Action | Code Change | Safety Risk |
|-------|--------|-------------|-------------|
| **Phase 1** | Custom Personalities UI 설정 (Smoothness 180, Safety Gap 150) | 없음 | Minimal |
| **Phase 2** | Mod 1 + Alternative 3 병행 (`LEAD_FILTER_TIME_HIGH = 2.2`) | 있음 | Low |
| **Phase 3** | 실차 로그 분석 → uncertainty 분포 확인 → threshold/scale 재조정 | 있음 | Low |

### Remaining Uncertainties

- uncertainty가 0.45~0.60 범위에 실제로 얼마나 자주 도달하는지 실차 데이터 부재
- Mod 1 단독으로 20 km/h 진동을 충분히 억제할 수 있는지 정량적 검증 필요
- 야간 vs 주간 uncertainty 분포 차이 미분석
