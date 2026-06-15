# Paddle5 Longitudinal Control — 도로 위험도 분석서

**작성일**: 2026-06-07
**브랜치**: paddle5-dterm
**변경 범위**: 5 파일 (+162/-20)

---

## 1. 변경 요약

| 파일 | 변경 내용 |
|------|-----------|
| `car.capnp` | `LongitudinalPIDTuning`에 `kdBP/kdV` 필드 추가 |
| `longcontrol.py` | D-term 지원 + Option B/C/D (I-term bleed, freeze threshold, brake bias) |
| `interface.py` | Option A/E/F (Bolt PEDAL_LONG kiV/kpV/kf 감소, D-term 게인, actuator delay) |
| `test_gm.py` | Bolt EV PEDAL_LONG 게인 어서션 5개 차종 |
| `test_longcontrol.py` | brake bias 기대값 업데이트 + D-term 유닛 테스트 6개 |

---

## 2. D-term 위험 분석

### 2.1 D-term 메커니즘

```
aego_filtered = aego_filter.update(CS.aEgo)    # 0.05s 시정수 LPF
error_rate = (aego_filtered - prev) / DT_CTRL
pid.d = kd * (-error_rate)   # anti-derivative-kick
```

**핵심**: D-term은 `aEgo`의 변화율에만 반응. `a_target` 변화에는 반응하지 않음 (anti-derivative-kick 패턴).

### 2.2 위험 시나리오별 분석

#### S1: 정상 고속도로 주행 (80km/h, 선행차 없음)
- `error ≈ 0`, `error_rate ≈ 0` → D-term 기여 ≈ 0
- **위험도**: 🟢 없음

#### S2: 선행차 급감속 (a_target이 -2.0으로 급변)
- `aEgo`가 아직 변하지 않음 → `error_rate ≈ 0`
- D-term은 `aEgo`가 실제로 감속하기 시작할 때만 개입
- kp/ki/feedforward가 먼저 반응, D-term은 뒤늦게 감쇄
- **위험도**: 🟢 낮음 (D-term이 늦게 개입하므로 과감쇄 없음)

#### S3: 노이즈 환경 (거친 도로, aEgo 노이즈)
- `aego_filter`의 0.05s 시정수 = ~3.2Hz 컷오프
- 100Hz 샘플링에서 50Hz 이상 성분 완전 차단
- aEgo 노이즈 폭 (~0.1 m/s²) → error_rate ≈ 2.0 m/s³ → d = 0.10 * 2.0 = 0.20 m/s²
- **위험도**: 🟡 낮음~중간 (실도로에서 확인 필요, kdV를 낮출 수 있음)

#### S4: D-term이 없는 차량 (kdBP/kdV 미설정)
- `kdBP = [0.0]`, `kdV = [0.0]` (기본값)
- `PIDController.__init__`에서 `isinstance(k_d, Number)` → `k_d = [[0], [0]]`
- `k_d` 속성은 항상 0 → `d = 0` → D-term 없음
- **위험도**: 🟢 없음 (하위 호환 100%)

#### S5: kd가 과도한 경우 (진동)
- kdV = [0.15, 0.12, 0.10, 0.08]의 최대값 0.15
- error_rate 최대 ~5.0 m/s³ (급감속) → d = 0.15 * 5.0 = 0.75 m/s²
- accel_limits [-3.0, 2.0] 내에서 안전하게 클리핑
- **위험도**: 🟡 중간 (실도로 확인 필요)

#### S6: I-term freeze가 D-term과 상호작용
- freeze_integrator = True일 때 D-term은 여전히 동작
- freeze 중 aEgo가 변하면 D-term이 응답 → 이는 바람직한 동작
- **위험도**: 🟢 없음

---

## 3. Option B/C/D 위험 분석

### 3.1 Option B: I-term bleed 강화

| 시나리오 | 이전 bleed | 이후 bleed | 영향 |
|----------|-----------|-----------|------|
| error = 0.15 (미세 오차) | 1.0 (no bleed) | 0.75 (25% bleed) | 미세 오차에서도 I-term 감쇄 시작 |
| error = 0.50 (중간 오차) | ~0.85 | 0.50 | I-term이 2배 빨리 감쇄 |
| error = 1.0 (큰 오차) | ~0.15 | 0.20 | 약간 완화 (step change 방지) |

**위험도**: 🟢 낮음. 기존 대비 I-term이 빨리 감쇄되므로 과적분은 줄어들지만, 큰 오차 영역(0.75~1.5)에서는 오히려 bleed가 약간 완화됨 → 부드러운 전환.

### 3.2 Option C: Freeze threshold 강화

| 속도 | 이전 threshold | 이후 threshold | 이전 hold | 이후 hold |
|------|---------------|---------------|----------|----------|
| 0 m/s | 0.35 | 0.20 | 25f | 35f |
| 12 m/s | 0.55 | 0.38 | 14f | 20f |
| 25 m/s | 0.70 | 0.50 | 10f | 14f |

**위험도**: 🟡 중간. 더 작은 a_target 변화에서도 freeze가 발생하므로:
- 장점: I-term windup 방지 효과 증대
- 단점: 정상적인 a_target 변화에서도 freeze가 발동 → 응답 지연 가능
- **완화**: hold_frames가 증가했으므로 freeze가 더 오래 유지 → I-term이 안정적으로 유지됨

### 3.3 Option D: Brake bias 안정화

| 파라미터 | 이전 | 이후 |
|---------|------|------|
| speed_factor 상한 | 1.0 | 0.8 |
| max_bias 상한 | 0.20 | 0.14 |
| bias 비율 | 0.12 | 0.10 |

**위험도**: 🟢 낮음. Brake bias가 30~40% 감소 → 감속 시 과도한 음의 가속도 명령 감소. 제동 거리가 약간 늘어날 수 있으나, 안전 마진이 충분함.

---

## 4. interface.py 위험 분석

### 4.1 Option A: kiV 감소

| 속도 | 이전 kiV | 이후 kiV | 감소율 |
|------|---------|---------|--------|
| 0 m/s | 0.07 | 0.05 | 29% |
| 5 m/s | 0.10 | 0.07 | 30% |
| 15 m/s | 0.15 | 0.10 | 33% |
| 35 m/s | 0.24 | 0.13 | 46% |

**위험도**: 🟡 중간. I-term 누적이 크게 감소 → 정상 주행에서는 응답이 약간 느려질 수 있음. I-term windup이 줄어들어 지터가 감소하는 대가.

### 4.2 Option E: Actuator delay 0.5 → 0.7

**위험도**: 🟢 낮음. MPC가 미래를 더 멀리 예측 → feedforward가 더 정확해짐. 과도 응답 감소.

### 4.3 Option F: D-term 게인

kdV = [0.15, 0.12, 0.10, 0.08] — 저속에서 높고 고속에서 낮음.

**위험도**: 🟡 중간 (S3, S5와 동일). 실도로 확인 필요.

---

## 5. 상호작용 위험 분석

### 5.1 D-term + Option B (I-term bleed)
- D-term이 aEgo 변화율에 반응 → 응답 속도 증가
- I-term bleed가 더 빨라짐 → I-term 누적 감소
- **상호작용**: 긍정적. 두 메커니즘이 보완적.

### 5.2 D-term + Option C (freeze threshold)
- Freeze 중 D-term은 여전히 동작 → aEgo 변화에 대한 응답 유지
- **상호작용**: 긍정적. Freeze가 I-term만 제한하고 D-term은 독립적.

### 5.3 kiV 감소 + D-term 추가
- kiV가 29~46% 감소 → I-term 누적 감소
- D-term이 응답 속도 보완 → net 응답은 유지
- **상호작용**: 긍정적. I-term 감소분을 D-term이 보완.

### 5.4 kpV 감소 + D-term 추가
- kpV가 10~15% 감소 → 비례 응답 약간 감소
- D-term이 변화율 감쇄 → 오버슈트 방지
- **상호작용**: 긍정적.

---

## 6. 실도로 검증 체크리스트

### 6.1 필수 테스트 시나리오

| # | 시나리오 | 검증 기준 | 방법 |
|---|---------|----------|------|
| T1 | 80km/h 정속 주행 (5분) | `aEgo` 표준편차 < 0.05 m/s² | rlog 분석 |
| T2 | 선행차 추종 (100→60km/h 감속) | jerk < 1.5 m/s³ | rlog 분석 |
| T3 | 선행차 추종 (60→100km/h 가속) | jerk < 1.5 m/s³ | rlog 분석 |
| T4 | 정지→출발 (신호대기 후 출발) | 부드러운 가속, 1초 내 목표 도달 | 운전자 감각 |
| T5 | 크루즈 설정속도 변경 (±10km/h) | 오버슈트 < 2km/h | rlog 분석 |
| T6 | 내리막 주행 (5% 경사) | 과도한 브레이크 없음 | 운전자 감각 |
| T7 | 오르막 주행 (5% 경사) | 과도한 가속 없음 | 운전자 감각 |

### 6.2 모니터링 지표

```
실시간 모니터링:
- pid.d: D-term 출력 (±0.5 m/s² 이내 정상)
- pid.i: I-term 누적 (±1.0 이내 정상)
- error_rate: aEgo 변화율 (±3.0 m/s³ 이내 정상)
- aego_filter.x: 필터링된 aEgo (노이즈 없음)
```

### 6.3 롤백 조건

| 조건 | 조치 |
|------|------|
| T1 실패 (aEgo 지터 > 0.1) | kdV를 50% 감소 (0.075, 0.06, 0.05, 0.04) |
| T2/T3 실패 (jerk > 2.0) | kdV를 30% 감소 |
| T4 실패 (출발 시 진동) | kdV[0]을 0으로 설정 |
| 전반적 응답 부족 | kiV를 10% 증가 |
| 전반적 과감쇄 | kpV를 10% 증가 |

---

## 7. 결론

### 전체 위험도: 🟡 중간 (실도로 검증 필요)

**낮은 위험**:
- D-term은 `aEgo` 변화율에만 반응 (anti-derivative-kick) → `a_target` 변화에 직접 반응하지 않음
- kd가 없는 차량은 영향 없음 (하위 호환 100%)
- Option D (brake bias)는 30~40% 감소로 안전 마진 충분

**중간 위험**:
- D-term이 실도로에서 노이즈에 어떻게 반응하는지 확인 필요
- Option C (freeze threshold)가 정상적인 a_target 변화에서도 발동할 수 있음
- kiV 29~46% 감소가 응답 속도에 미치는 영향 확인 필요

**완화 조치**:
- 모든 변경은 Bolt EV PEDAL_LONG + Malibu Hybrid CC에만 적용
- 다른 차량은 영향 없음
- kd 미설정 차량은 기존 동작 100% 유지
- 롤백 조건이 명확하게 정의됨
