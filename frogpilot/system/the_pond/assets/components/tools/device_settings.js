import { html, reactive } from "https://esm.sh/@arrow-js/core"

// ―――――――――――――――――――――――――――――――
// Module-level state (persists across re-renders)
// ―――――――――――――――――――――――――――――――
const state = reactive({
  layout: [],
  allKeys: [],
  values: {},
  loadingLayout: true,
  loadingValues: true,
  filter: "",
  collapsed: {},
  expanded: {},
  updatingKeys: {},
  fetched: false,
})

async function fetchLayoutAndParams() {
  state.loadingLayout = true
  state.loadingValues = true

  // 1. Fetch Layout Structure (Build-time Static JSON)
  try {
    const layoutRes = await fetch("/assets/components/tools/device_settings_layout.json")
    const layoutData = await layoutRes.json()
    state.layout = layoutData

    // Extract flatter key map
    const keys = []
    for (const section of layoutData) {
      for (const p of section.params) {
        keys.push(p.key)
      }
    }
    state.allKeys = keys
  } catch (e) {
    console.error("Failed to fetch UI layout:", e)
  }
  state.loadingLayout = false

  // 2. Fetch Live Values (Device State)
  try {
    const res = await fetch("/api/params/all")
    const data = await res.json()
    state.values = data
  } catch (e) {
    console.error("Failed to fetch param values:", e)
  }
  state.loadingValues = false
  requestAnimationFrame(syncInputs)
}

function syncInputs() {
  for (const key of state.allKeys) {
    const el = document.getElementById(`ds-${key}`)
    if (el) {
      if (el.type === "checkbox") {
        el.checked = !!state.values[key]
      } else if (el.tagName === "SELECT") {
        const endpoint = el.getAttribute("data-endpoint")
        if (endpoint && !el.dataset.hydrated) {
          el.dataset.hydrated = "1"
          fetch(endpoint).then(r => r.json()).then(options => {
            el.innerHTML = ""
            for (const opt of options) {
              const o = document.createElement("option")
              o.value = opt.value
              o.textContent = opt.label
              el.appendChild(o)
            }
            el.value = state.values[key] || ""
          }).catch(() => { el.innerHTML = '<option value="">Error loading</option>' })
        } else {
          el.value = state.values[key] || ""
        }
      } else {
        el.value = state.values[key]
        const displayEl = document.getElementById(`ds-display-${key}`)
        if (displayEl) {
          const precision = el.getAttribute("data-precision")
          const pInt = precision ? parseInt(precision, 10) : null
          displayEl.textContent = formatSliderValue(state.values[key], el.getAttribute("step"), pInt, key)
        }
      }
    }
  }
}

function formatSliderValue(val, stepStr, precisionInt, key) {
  if (val === null || val === undefined) return "--"
  const v = parseFloat(val)
  if (isNaN(v)) return val

  // Specific formatting for the Audio Volume sliders mappings to simulate C++ behavior
  const volumeKeys = [
    "DisengageVolume", "EngageVolume", "PromptVolume",
    "PromptDistractedVolume", "RefuseVolume",
    "WarningImmediateVolume", "WarningSoftVolume"
  ]
  if (key && volumeKeys.includes(key)) {
    if (v === 0) return "Muted"
    if (v === 101) return "Auto"
    return `${v}%`
  }

  if (precisionInt !== undefined && precisionInt !== null) {
    return Number(v.toFixed(precisionInt)).toString()
  }

  if (!stepStr || !stepStr.includes(".")) return Math.round(v).toString()
  const dec = stepStr.split(".")[1].length
  return Number(v.toFixed(dec)).toString()
}

async function updateParam(key, elType) {
  const current = state.values[key]

  // Extract new value from the DOM directly to avoid reactive race conditions
  const el = document.getElementById(`ds-${key}`)
  if (!el) return

  let formattedVal
  if (elType === "checkbox") {
    formattedVal = current ? false : true
  } else if (elType === "dropdown") {
    formattedVal = el.value
  } else {
    // Numeric slider - coerce to float
    formattedVal = parseFloat(el.value)
  }

  try {
    const res = await fetch("/api/params", {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ key, value: formattedVal }),
    })
    const data = await res.json()

    if (res.ok) {
      state.values = { ...state.values, [key]: formattedVal }
      showSnackbar(data.message || `${key} updated`)
    } else {
      revertInput(key, current, elType)
      showSnackbar(data.error || "Failed to update parameter")
    }
  } catch (e) {
    revertInput(key, current, elType)
    showSnackbar("Network error — is the device reachable?")
  }
}

function revertInput(key, current, elType) {
  const el = document.getElementById(`ds-${key}`)
  if (el) {
    if (elType === "checkbox") el.checked = !!current
    else if (elType === "dropdown") el.value = current || ""
    else {
      el.value = current
      const displayEl = document.getElementById(`ds-display-${key}`)
      if (displayEl) {
        const precision = el.getAttribute("data-precision")
        const pInt = precision ? parseInt(precision, 10) : null
        displayEl.textContent = formatSliderValue(current, el.getAttribute("step"), pInt, key)
      }
    }
  }
}

function handleSliderInput(e, key) {
  const displayEl = document.getElementById(`ds-display-${key}`)
  if (displayEl) {
    const el = e.target
    const precision = el.getAttribute("data-precision")
    const pInt = precision ? parseInt(precision, 10) : null
    displayEl.textContent = formatSliderValue(el.value, el.getAttribute("step"), pInt, key)
  }
}

function toggleSection(name) {
  state.collapsed = { ...state.collapsed, [name]: !state.collapsed[name] }
  setTimeout(syncInputs, 50)
}

function toggleManage(key) {
  state.expanded = { ...state.expanded, [key]: !state.expanded[key] }
  setTimeout(syncInputs, 50)
}

function matchesFilter(p) {
  if (!state.filter) return true
  const q = state.filter.toLowerCase()
  return p.label.toLowerCase().includes(q) || p.key.toLowerCase().includes(q)
}

// ―――――――――――――――――――――――――――――――
// Component
// ―――――――――――――――――――――――――――――――
export function DeviceSettings() {
  if (!state.fetched) {
    state.fetched = true
    fetchLayoutAndParams()
  }

  return html`
    <div class="ds-wrapper">
      <h2>Device Settings</h2>

      <input
        class="ds-search"
        type="text"
        placeholder="Search settings..."
        @input="${(e) => { state.filter = e.target.value }}"
      />

      ${() => {
      if (state.loadingLayout || state.loadingValues) {
        return html`<div class="ds-loading">Loading configuration...</div>`
      }

      const loadedKeys = state.allKeys.length

      // Sync DOM inputs after reactive render
      requestAnimationFrame(syncInputs)

      return html`
          <div class="ds-status-bar">
            <span>${loadedKeys} settings mapped dynamically</span>
          </div>

          ${state.layout.map(section => {
        const visibleParams = section.params.filter(p => matchesFilter(p))
        if (visibleParams.length === 0) return ""

        const isCollapsed = state.collapsed[section.name]

        return html`
              <div class="ds-section ${isCollapsed ? 'collapsed' : ''}">
                <div class="ds-section-header" @click="${() => toggleSection(section.name)}">
                  <i class="bi ${section.icon}"></i>
                  <span class="ds-section-title">${section.name} (${visibleParams.length})</span>
                  <i class="bi bi-chevron-down ds-section-chevron"></i>
                </div>
                <div class="ds-section-body">
                  ${() => visibleParams.map(p => {
          if (p.parent_key) {
            if (!state.values[p.parent_key]) return ""
            if (!state.expanded[p.parent_key]) return ""
          }

          const isNumeric = p.ui_type === "numeric" || p.data_type === "float" || p.data_type === "int"
          const isChild = p.parent_key ? "ds-child-modifier" : ""

          return html`
                        <div class="ds-row ${isNumeric ? 'ds-row-numeric' : ''} ${isChild}">
                        <div class="ds-row-info">
                          <div class="ds-row-text">
                            <span class="ds-row-label">${p.label}</span>
                            ${p.description ? html`<div class="ds-row-desc">${p.description}</div>` : ""}

                            ${() => p.is_parent_toggle && state.values[p.key] ? html`
                               <div class="ds-manage-btn" @click="${() => toggleManage(p.key)}">
                                   ${state.expanded[p.key] ? 'Close' : 'Manage'} <i class="bi bi-chevron-${state.expanded[p.key] ? 'up' : 'down'}"></i>
                               </div>
                            ` : ''}
                          </div>
                          ${isNumeric ? html`<span class="ds-row-value" id="ds-display-${p.key}">${state.values[p.key] !== undefined ? formatSliderValue(state.values[p.key], p.step !== undefined ? String(p.step) : undefined, p.precision, p.key) : '..'}</span>` : ""}
                        </div>

                        ${isNumeric ? html`
                          <div class="ds-slider-container">
                            <input
                              type="range"
                              class="ds-slider"
                              id="ds-${p.key}"
                              min="${p.min !== undefined ? p.min : (p.data_type === 'float' ? 0.0 : 0)}"
                              max="${p.max !== undefined ? p.max : (p.data_type === 'float' ? 100.0 : 100)}"
                              step="${p.step !== undefined ? p.step : (p.data_type === 'float' ? 0.01 : 1)}"
                              data-precision="${p.precision !== undefined ? p.precision : ''}"
                              value="${state.values[p.key] !== undefined ? state.values[p.key] : ''}"
                              @input="${(e) => handleSliderInput(e, p.key)}"
                              @change="${() => updateParam(p.key, 'numeric')}"
                            />
                          </div>
                        ` : p.ui_type === "dropdown" ? html`
                           <select class="ds-select" id="ds-${p.key}"
                             data-endpoint="${p.options_endpoint || ''}"
                             @change="${() => updateParam(p.key, 'dropdown')}">
                             <option value="">Loading…</option>
                           </select>
                        ` : html`
                          <input
                            type="checkbox"
                            class="ds-toggle"
                            id="ds-${p.key}"
                            .checked="${!!state.values[p.key]}"
                            @change="${() => updateParam(p.key, 'checkbox')}"
                          />
                        `}
                        </div>
                    `
        })}
                </div>
              </div>
            `
      })}

          ${() => {
          const totalVisible = state.layout.reduce((acc, s) =>
            acc + s.params.filter(p => matchesFilter(p)).length, 0)
          if (totalVisible === 0) {
            return html`<div class="ds-empty">No settings match your search.</div>`
          }
          return ""
        }}
        `
    }}
    </div>
  `
}
