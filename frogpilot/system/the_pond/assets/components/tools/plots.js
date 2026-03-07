import { html, reactive } from "https://esm.sh/@arrow-js/core"

const state = reactive({
  loading: true,
  error: "",
  paused: false,
  showAdvancedTerms: false,
  live: null,
  samples: [],
})

let initialized = false
let pollHandle = null
let lastTimestamp = 0

const MAX_POINTS = 240
const POLL_INTERVAL_MS = 500
const SVG_WIDTH = 1000
const SVG_HEIGHT = 260
const ADVANCED_TERMS_KEY = "plotsShowAdvancedTerms"

function isPlotsRouteActive() {
  return window.location.pathname === "/plots"
}

function toNumber(value, fallback = 0) {
  const n = Number(value)
  return Number.isFinite(n) ? n : fallback
}

function formatValue(value, digits = 2) {
  return toNumber(value).toFixed(digits)
}

function formatAge(seconds) {
  const value = Math.max(0, toNumber(seconds))
  if (value < 1) return `${Math.round(value * 1000)} ms`
  return `${value.toFixed(1)} s`
}

function formatSourceLabel(kind, source) {
  const normalizedKind = String(kind || "").toLowerCase()
  const normalizedSource = String(source || "").toLowerCase()

  if (normalizedKind === "lateral") {
    if (normalizedSource === "torquestate") return "Steering controller output"
    if (normalizedSource === "curvature") return "Path model estimate"
  }

  if (normalizedKind === "longitudinal") {
    if (normalizedSource.includes("livelocationkalman")) return "Control output + calibrated acceleration"
    if (normalizedSource === "controlsstate") return "Planner target output"
  }

  if (normalizedKind === "lateralterms") {
    if (normalizedSource === "torquestate") return "Steering torque controller"
    if (normalizedSource === "pidstate") return "Steering angle PID controller"
  }

  if (normalizedKind === "longitudinalterms") {
    if (normalizedSource === "controlsstate") return "Longitudinal controller terms"
  }

  return "Live control signal"
}

function stopPolling() {
  if (!pollHandle) return
  clearTimeout(pollHandle)
  pollHandle = null
}

function pushSample(payload) {
  const timestamp = toNumber(payload.timestamp, 0)
  if (!timestamp || timestamp <= 0 || timestamp === lastTimestamp) return

  lastTimestamp = timestamp
  state.samples.push({
    timestamp,
    desiredLateralAccel: toNumber(payload.desiredLateralAccel),
    actualLateralAccel: toNumber(payload.actualLateralAccel),
    desiredLongitudinalAccel: toNumber(payload.desiredLongitudinalAccel),
    actualLongitudinalAccel: toNumber(payload.actualLongitudinalAccel),
    lateralP: toNumber(payload.lateralP),
    lateralI: toNumber(payload.lateralI),
    lateralD: toNumber(payload.lateralD),
    lateralF: toNumber(payload.lateralF),
    longitudinalUpAccelCmd: toNumber(payload.longitudinalUpAccelCmd),
    longitudinalUiAccelCmd: toNumber(payload.longitudinalUiAccelCmd),
    longitudinalUfAccelCmd: toNumber(payload.longitudinalUfAccelCmd),
  })

  if (state.samples.length > MAX_POINTS) {
    state.samples.splice(0, state.samples.length - MAX_POINTS)
  }
}

async function fetchLiveData() {
  const response = await fetch("/api/plots/live")
  const payload = await response.json()

  if (!response.ok) {
    throw new Error(payload.error || response.statusText || "Failed to load live plot data")
  }

  state.live = payload
  state.error = ""
  state.loading = false

  if (!payload.stale) {
    pushSample(payload)
  }
}

function ensurePolling() {
  if (pollHandle) return

  const poll = async () => {
    if (!isPlotsRouteActive()) {
      pollHandle = null
      return
    }

    if (!state.paused) {
      try {
        await fetchLiveData()
      } catch (error) {
        state.error = error?.message || String(error)
        state.loading = false
      }
    }

    pollHandle = setTimeout(poll, POLL_INTERVAL_MS)
  }

  pollHandle = setTimeout(poll, POLL_INTERVAL_MS)
}

function clearHistory() {
  state.samples = []
  lastTimestamp = 0
}

function togglePaused() {
  state.paused = !state.paused
  if (state.paused) {
    stopPolling()
    return
  }

  if (!isPlotsRouteActive()) return

  fetchLiveData().catch((error) => {
    state.error = error?.message || String(error)
  })
  ensurePolling()
}

function toggleAdvancedTerms() {
  state.showAdvancedTerms = !state.showAdvancedTerms
  try {
    localStorage.setItem(ADVANCED_TERMS_KEY, state.showAdvancedTerms ? "1" : "0")
  } catch (error) {
    console.warn("Failed to persist plots advanced terms preference", error)
  }
}

function yForValue(value, min, max) {
  const safeMin = toNumber(min, -1)
  const safeMax = toNumber(max, 1)
  const clamped = Math.max(safeMin, Math.min(safeMax, toNumber(value)))
  const span = Math.max(1e-6, safeMax - safeMin)
  return ((safeMax - clamped) / span) * SVG_HEIGHT
}

function computeRange(samples, desiredKey, actualKey) {
  let maxAbs = 0
  for (const sample of samples) {
    maxAbs = Math.max(
      maxAbs,
      Math.abs(toNumber(sample?.[desiredKey])),
      Math.abs(toNumber(sample?.[actualKey])),
    )
  }

  const halfSpan = Math.max(1.5, Math.ceil((maxAbs * 1.25) * 10) / 10)
  return { min: -halfSpan, max: halfSpan }
}

function buildPolyline(samples, key, min, max) {
  if (!samples.length) return ""

  const lastIndex = Math.max(1, samples.length - 1)
  return samples.map((sample, index) => {
    const x = (index / lastIndex) * SVG_WIDTH
    const y = yForValue(sample?.[key], min, max)
    return `${x.toFixed(2)},${y.toFixed(2)}`
  }).join(" ")
}

function computeRangeForKeys(samples, keys) {
  let maxAbs = 0
  for (const sample of samples) {
    for (const key of keys) {
      maxAbs = Math.max(maxAbs, Math.abs(toNumber(sample?.[key])))
    }
  }

  const halfSpan = Math.max(0.15, Math.ceil((maxAbs * 1.35) * 1000) / 1000)
  return { min: -halfSpan, max: halfSpan }
}

function latestSampleValue(key) {
  const latest = state.samples[state.samples.length - 1]
  if (latest) return latest[key]
  return toNumber(state.live?.[key])
}

function PlotCard(title, desiredKey, actualKey, sourceKind, sourceLabel, desiredLabel = "Target", actualLabel = "Measured") {
  const hasData = state.samples.length > 1
  const range = computeRange(state.samples, desiredKey, actualKey)
  const desiredPolyline = buildPolyline(state.samples, desiredKey, range.min, range.max)
  const actualPolyline = buildPolyline(state.samples, actualKey, range.min, range.max)
  const zeroY = yForValue(0, range.min, range.max)
  const topQuarterY = yForValue(range.max * 0.5, range.min, range.max)
  const bottomQuarterY = yForValue(range.min * 0.5, range.min, range.max)

  return html`
    <section class="plotCard plotChartCard">
      <div class="plotCardHeader">
        <h2>${title}</h2>
        <span class="plotSource">Source: ${formatSourceLabel(sourceKind, sourceLabel)}</span>
      </div>

      <div class="plotLegend">
        <span class="plotLegendItem"><i class="plotLegendLine desired"></i>${desiredLabel}: ${formatValue(latestSampleValue(desiredKey))}</span>
        <span class="plotLegendItem"><i class="plotLegendLine actual"></i>${actualLabel}: ${formatValue(latestSampleValue(actualKey))}</span>
      </div>

      <div class="plotSvgWrap">
        ${hasData ? html`
          <svg class="plotSvg" viewBox="0 0 ${SVG_WIDTH} ${SVG_HEIGHT}" preserveAspectRatio="none" role="img" aria-label="${title} live plot">
            <line class="plotGridLine" x1="0" y1="${topQuarterY}" x2="${SVG_WIDTH}" y2="${topQuarterY}"></line>
            <line class="plotZeroLine" x1="0" y1="${zeroY}" x2="${SVG_WIDTH}" y2="${zeroY}"></line>
            <line class="plotGridLine" x1="0" y1="${bottomQuarterY}" x2="${SVG_WIDTH}" y2="${bottomQuarterY}"></line>
            <polyline class="plotLine desired" points="${desiredPolyline}"></polyline>
            <polyline class="plotLine actual" points="${actualPolyline}"></polyline>
          </svg>
        ` : html`
          <div class="plotEmpty">Waiting for enough live samples...</div>
        `}
      </div>

      <div class="plotRangeRow">
        <span>${formatValue(range.max, 1)} m/s²</span>
        <span>0.0 m/s²</span>
        <span>${formatValue(range.min, 1)} m/s²</span>
      </div>
    </section>
  `
}

function LateralTermsPlotCard(sourceLabel) {
  const hasData = state.samples.length > 1
  const keys = ["lateralP", "lateralI", "lateralD", "lateralF"]
  const range = computeRangeForKeys(state.samples, keys)
  const zeroY = yForValue(0, range.min, range.max)
  const topQuarterY = yForValue(range.max * 0.5, range.min, range.max)
  const bottomQuarterY = yForValue(range.min * 0.5, range.min, range.max)

  return html`
    <section class="plotCard plotChartCard">
      <div class="plotCardHeader">
        <h2>Lateral Controller Terms</h2>
        <span class="plotSource">Source: ${formatSourceLabel("lateralTerms", sourceLabel)}</span>
      </div>

      <div class="plotLegend">
        <span class="plotLegendItem"><i class="plotLegendLine p"></i>P: ${formatValue(latestSampleValue("lateralP"), 3)}</span>
        <span class="plotLegendItem"><i class="plotLegendLine i"></i>I: ${formatValue(latestSampleValue("lateralI"), 3)}</span>
        <span class="plotLegendItem"><i class="plotLegendLine d"></i>D: ${formatValue(latestSampleValue("lateralD"), 3)}</span>
        <span class="plotLegendItem"><i class="plotLegendLine f"></i>F: ${formatValue(latestSampleValue("lateralF"), 3)}</span>
      </div>

      <div class="plotSvgWrap">
        ${hasData ? html`
          <svg class="plotSvg" viewBox="0 0 ${SVG_WIDTH} ${SVG_HEIGHT}" preserveAspectRatio="none" role="img" aria-label="Lateral controller terms live plot">
            <line class="plotGridLine" x1="0" y1="${topQuarterY}" x2="${SVG_WIDTH}" y2="${topQuarterY}"></line>
            <line class="plotZeroLine" x1="0" y1="${zeroY}" x2="${SVG_WIDTH}" y2="${zeroY}"></line>
            <line class="plotGridLine" x1="0" y1="${bottomQuarterY}" x2="${SVG_WIDTH}" y2="${bottomQuarterY}"></line>
            <polyline class="plotLine p" points="${buildPolyline(state.samples, "lateralP", range.min, range.max)}"></polyline>
            <polyline class="plotLine i" points="${buildPolyline(state.samples, "lateralI", range.min, range.max)}"></polyline>
            <polyline class="plotLine d" points="${buildPolyline(state.samples, "lateralD", range.min, range.max)}"></polyline>
            <polyline class="plotLine f" points="${buildPolyline(state.samples, "lateralF", range.min, range.max)}"></polyline>
          </svg>
        ` : html`
          <div class="plotEmpty">Waiting for enough live samples...</div>
        `}
      </div>

      <div class="plotRangeRow">
        <span>${formatValue(range.max, 3)}</span>
        <span>0.000</span>
        <span>${formatValue(range.min, 3)}</span>
      </div>
    </section>
  `
}

function LongitudinalTermsPlotCard(sourceLabel) {
  const hasData = state.samples.length > 1
  const keys = ["longitudinalUpAccelCmd", "longitudinalUiAccelCmd", "longitudinalUfAccelCmd"]
  const range = computeRangeForKeys(state.samples, keys)
  const zeroY = yForValue(0, range.min, range.max)
  const topQuarterY = yForValue(range.max * 0.5, range.min, range.max)
  const bottomQuarterY = yForValue(range.min * 0.5, range.min, range.max)

  return html`
    <section class="plotCard plotChartCard">
      <div class="plotCardHeader">
        <h2>Longitudinal Accel Cmd Terms</h2>
        <span class="plotSource">Source: ${formatSourceLabel("longitudinalTerms", sourceLabel)}</span>
      </div>

      <div class="plotLegend">
        <span class="plotLegendItem"><i class="plotLegendLine p"></i>Up: ${formatValue(latestSampleValue("longitudinalUpAccelCmd"), 3)}</span>
        <span class="plotLegendItem"><i class="plotLegendLine i"></i>Ui: ${formatValue(latestSampleValue("longitudinalUiAccelCmd"), 3)}</span>
        <span class="plotLegendItem"><i class="plotLegendLine f"></i>Uf: ${formatValue(latestSampleValue("longitudinalUfAccelCmd"), 3)}</span>
      </div>

      <div class="plotSvgWrap">
        ${hasData ? html`
          <svg class="plotSvg" viewBox="0 0 ${SVG_WIDTH} ${SVG_HEIGHT}" preserveAspectRatio="none" role="img" aria-label="Longitudinal accel cmd terms live plot">
            <line class="plotGridLine" x1="0" y1="${topQuarterY}" x2="${SVG_WIDTH}" y2="${topQuarterY}"></line>
            <line class="plotZeroLine" x1="0" y1="${zeroY}" x2="${SVG_WIDTH}" y2="${zeroY}"></line>
            <line class="plotGridLine" x1="0" y1="${bottomQuarterY}" x2="${SVG_WIDTH}" y2="${bottomQuarterY}"></line>
            <polyline class="plotLine p" points="${buildPolyline(state.samples, "longitudinalUpAccelCmd", range.min, range.max)}"></polyline>
            <polyline class="plotLine i" points="${buildPolyline(state.samples, "longitudinalUiAccelCmd", range.min, range.max)}"></polyline>
            <polyline class="plotLine f" points="${buildPolyline(state.samples, "longitudinalUfAccelCmd", range.min, range.max)}"></polyline>
          </svg>
        ` : html`
          <div class="plotEmpty">Waiting for enough live samples...</div>
        `}
      </div>

      <div class="plotRangeRow">
        <span>${formatValue(range.max, 3)}</span>
        <span>0.000</span>
        <span>${formatValue(range.min, 3)}</span>
      </div>
    </section>
  `
}

async function initialize() {
  try {
    state.showAdvancedTerms = localStorage.getItem(ADVANCED_TERMS_KEY) === "1"
  } catch (error) {
    state.showAdvancedTerms = false
  }

  try {
    await fetchLiveData()
  } catch (error) {
    state.error = error?.message || String(error)
    state.loading = false
  } finally {
    ensurePolling()
  }
}

export function LivePlots() {
  if (!initialized) {
    initialized = true
    initialize()
  }
  if (!state.paused) {
    ensurePolling()
  }

  return html`
    <div class="plotsPage">
      <h1>Plots</h1>

      <section class="plotCard plotStatusCard">
        <p class="plotDescription">
          Live comparison view for tuning diagnostics. If desired tracks actual closely, tuning is likely good. Large divergence often points to model mismatch or limits.
        </p>

        <div class="plotStatusGrid">
          <p><strong>Onroad:</strong> ${state.live?.isOnroad ? "Yes" : "No"}</p>
          <p><strong>Sample Age:</strong> ${formatAge(state.live?.sampleAgeSeconds)}</p>
          <p><strong>Vehicle Speed:</strong> ${formatValue(state.live?.speed)} m/s</p>
          <p><strong>Samples:</strong> ${state.samples.length}</p>
        </div>

        <div class="plotActions">
          <button class="plotButton" @click="${togglePaused}">
            ${state.paused ? "Resume Live" : "Pause Live"}
          </button>
          <button class="plotButton" @click="${clearHistory}">
            Clear History
          </button>
        </div>

        ${state.error ? html`<p class="plotError"><strong>Error:</strong> ${state.error}</p>` : ""}
        ${state.live?.lastError ? html`<p class="plotError"><strong>Source Error:</strong> ${state.live.lastError}</p>` : ""}
      </section>

      <div class="plotCharts">
        ${PlotCard(
          "Lateral Response (m/s²)",
          "desiredLateralAccel",
          "actualLateralAccel",
          "lateral",
          state.live?.lateralSource,
          "Target",
          "Measured",
        )}
        ${PlotCard(
          "Longitudinal Response (m/s²)",
          "desiredLongitudinalAccel",
          "actualLongitudinalAccel",
          "longitudinal",
          state.live?.longitudinalSource,
          "Target",
          "Measured",
        )}
      </div>

      <div class="plotAdvancedRow">
        <button class="plotButton" @click="${toggleAdvancedTerms}">
          ${state.showAdvancedTerms ? "Hide Advanced Controller Terms" : "Show Advanced Controller Terms"}
        </button>
      </div>

      ${state.showAdvancedTerms ? html`
        <div class="plotCharts">
          ${LateralTermsPlotCard(state.live?.lateralTermsSource)}
          ${LongitudinalTermsPlotCard(state.live?.longitudinalTermsSource)}
        </div>
      ` : ""}

      ${state.loading ? html`<p>Loading live data...</p>` : ""}
    </div>
  `
}
