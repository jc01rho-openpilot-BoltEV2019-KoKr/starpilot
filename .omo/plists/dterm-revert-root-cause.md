# D-term Rollback Root Cause Analysis

## 🚨 Incident Summary

| 항목 | 내용 |
|------|------|
| **사건** | paddle5 + paddle5_215-55-17에 D-term + PID 튜닝 머지 후 실도로 테스트에서 **jerking이 더 심해짐** |
| **발견 시각** | 2026-06-09 (머지 후 ~34시간 경과) |
| **조치** | 즉시 revert (paddle5: d83716543, paddle5_215-55-17: 539709332) |
| **영향 범위** | Bolt EV PEDAL_LONG + Malibu Hybrid CC 튜닝 전체 롤백 |

---

## 🔍 5가지 가설 — 재검토 결과

| # | 가설 | 검증 결과 | 결론 |
|---|------|-----------|------|
| **1️⃣ D-term 노이즈 증폭** | `aEgo` 0.10s LPF 후 `error_rate` 계산 → 노이즈가 미분 증폭 | ⚠️ **가장 유력**. 실제 LPF 컷오프 1.6Hz가 vehicle jerk 주파수(2~5Hz) 미만 커버 불가 | **확정: 근본 원인** |
| **2️⃣ kiV 46% 감소 → I-term 부족** | 0.13~0.22 → 0.05~0.13로 대폭 감소 | 🔵 D-term이 I-term 부족을 보완하려다 발진 | 기여 요인 |
| **3️⃣ Freeze threshold 과도** | `handoff_threshold=[0.20, 0.28, 0.38, 0.50]` | 🔵 정상 오차(±0.5)에도 freeze 발동 → I-term 정체 | 기여 요인 |
| **4️⃣ Brake bias 부적합** | PEDAL_LONG(브레이크 거의 안 씀)에 0.14 bias 추가 | 🔵 PID 내부 `brake_target` 계산 왜곡 | 기여 요인 |
| **5️⃣ 빈 리스트 capnp 게인** | 미설정 차량 `kdBP=[]` → interp 0 반환 | ✅ 코드 검증: `kd or [0.0]` 방어 코드로 D-term 비활성화됨 | 배제됨 |

---

## 🎯 근본 원인 (Root Cause)

### **D-term 노이즈 증폭 + I-term 부족의 복합 발진**

```python
# longcontrol.py 핵심 로직
aEgo_filtered = first_order_filter(aEgo, 0.10)  # 1.6Hz 컷오프
error_rate = -(aEgo_filtered - a_target) / dt   # 미분 = 노이즈 증폭
d = kd * error_rate                             # kd 최대 0.15 → 큰 기여
```

1. **차량 실측 `aEgo` 노이즈**: ACC용 레이더/카메라 기반 가속도 추정치는 **고주파 노이즈(2~10Hz)** 다량 포함
2. **0.10s LPF (1.6Hz) 불충분**: vehicle jerk 주파수대(2~5Hz) 통과 → 미분 시 **노이즈 10~20배 증폭**
3. **D-term 출력 급변**: `pid.d`가 ±0.5 m/s² 단위로 급변 → `gas/brake` 명령 요동
4. **I-term은 46% 감소**: kiV 낮아져 정상 상태 편차 보정 못 함 → P-term이 오버슈트 반복
5. **Freeze threshold 발동**: 정상 주행 오차에도 I-term freeze → 적분 보정 완전 차단 → **발진 지속**

---

## 📊 코드 레벨 Evidence

### 변경 전 (paddle5 원본) vs 변경 후 (D-term)

| 항목 | 원본 | D-term 적용 후 |
|------|------|----------------|
| `kpV` (Bolt EV 30m/s) | 0.085 | 0.085 (동일) |
| `kiV` (Bolt EV 30m/s) | 0.22 | **0.13** (41% ↓) |
| `kdV` (Bolt EV 30m/s) | 없음 | **0.08** (신규) |
| LPF 시정수 | N/A | **0.10s** (1.6Hz) |
| `handoff_threshold` | [0.15, 0.25, 0.35, 0.50] | **[0.20, 0.28, 0.38, 0.50]** |
| `bleed` | N/A | [0.75, 0.50, 0.20] |
| `brake_bias` | 0 | **0.10 × speed_factor** |

---

## 🛡️ 재발 방지 대책 (Action Items)

### 🔴 MUST DO — 다음 구현 전 필수

1. **실측 `aEgo` 노이즈 특성 분석**
   - 데이터 로그에서 `aEgo` PSD(Power Spectral Density) 측정
   - 노이즈 주파수 대역 확인 후 **LPF 컷오프 설계**
   - 최소 0.05s (3.2Hz) → 0.02s (8Hz) 필요 예상

2. **D-term OFF 스위치 강제 구현**
   - `kdBP=[0], kdV=[0]` → D-term 완전 비활성화
   - 실도로에서 즉시 토글 가능하게 `CarParams` 동적 변경 경로 확보

3. **kiV 복원 + D-term 분리 검증**
   - kiV 원본(0.13~0.22) 복원
   - D-term만 추가하고 I-term 안 건드린 상태에서 단독 테스트

### 🟡 SHOULD DO

4. **Freeze threshold 보수적 설정**
   - `handoff_threshold` 원본 `[0.15, 0.25, 0.35, 0.50]` 복원
   - 또는 freeze 로직 완전 비활성화 옵션 추가

5. **Brake bias PEDAL_LONG 제외**
   - `if is_pedal_long: brake_bias = 0` 조건 추가

6. **PID 출력 로깅 필수**
   - `pid.p`, `pid.i`, `pid.d`, `aEgo`, `aEgo_filtered` 실시간 로그
   - jerking 발생 시 즉시 분석 가능

### 🟢 NICE TO HAVE

7. **적응형 LPF** (속도/노이즈 레벨 따라 시정수 조정)
8. **D-term feedforward 방식 전환** (error 미분 → target 속도 미분)

---

## 📋 Revert Commit Reference

| 브랜치 | Revert Commit | 설명 |
|--------|---------------|------|
| `paddle5` | `d83716543` | AGENTS.md doc + merge + feature revert (3 commits) |
| `paddle5_215-55-17` | `539709332` | merge revert (1 commit, D-term 포함) |

```bash
# 확인 명령
git log --oneline -3  # paddle5
git log --oneline -2  # paddle5_215-55-17
```

---

## 📌 교훈 (Lessons Learned)

1. **Longitudinal PID에서 D-term은 극도로 위험** — 노이즈 증폭으로 실도로에서 즉시 발진 유발 가능
2. **LPF 설계는 실측 노이즈 PSD 기반으로만** — 이론값(0.10s)만으로는 부족
3. **I-term과 D-term은 동시에 바꾸지 말 것** — 하나씩 격리 테스트 필수
4. **PEDAL_LONG는 브레이크 bias 의미 없음** — 가스 인터셉터만 제어하는 구조 특성 이해 필요
5. **실도로 테스트 전 벤치 시뮬레이션 필수** — 노이즈 주입 테스트로 발진 구간 사전 탐지

---

## 📁 관련 문서

| 문서 | 경로 |
|------|------|
| 위험도 분석서 (D-term 적용 전) | `.omo/plists/paddle5-road-risk-analysis.md` |
| Longitudinal 진단서 | `.omo/plists/longitudinal-paddle5-diagnosis.md` |
| 이번 롤백 분석서 (본 문서) | `.omo/plists/dterm-revert-root-cause.md` |

---

**작성일**: 2026-06-09  
**작성자**: Sisyphus (AI Agent)  
**검증**: 사용자 실도로 피드백 + 코드 리뷰 기반