import { html, reactive } from "/assets/vendor/arrow-core.js"
import { galaxyPath, isGalaxyTunnel } from "/assets/js/utils.js"
import {
  enableSentryPush,
  sendSentryTestPush,
} from "/assets/components/sentry_notifications.js"

const state = reactive({
  loading: true,
  savingKey: "",
  params: {},
  status: {},
  event: {},
  testBusy: false,
  pushBusy: false,
})

let pollTimer = null

async function fetchParams() {
  try {
    const response = await fetch(galaxyPath("/api/params/all"), { cache: "no-store" })
    if (response.ok) state.params = await response.json()
  } catch (error) {
    console.error("Failed to fetch Sentry settings:", error)
  } finally {
    state.loading = false
  }
}

async function fetchStatus() {
  try {
    const response = await fetch(galaxyPath("/api/sentry/status"), { cache: "no-store" })
    if (!response.ok) return
    const payload = await response.json()
    state.status = payload.status || {}
    state.event = payload.lastEvent || {}
  } catch (error) {
    console.error("Failed to fetch Sentry status:", error)
  }
}

function startPolling() {
  if (pollTimer !== null) return
  fetchParams()
  fetchStatus()
  pollTimer = window.setInterval(fetchStatus, 5000)
}

async function saveParam(key, value) {
  state.savingKey = key
  try {
    const response = await fetch(galaxyPath("/api/params"), {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ key, value }),
    })
    const payload = await response.json()
    if (!response.ok) {
      showSnackbar(payload.error || `Failed to update ${key}.`)
      return
    }
    state.params = { ...state.params, ...(payload.updated || {}), [key]: value }
    showSnackbar(payload.message || "Sentry setting saved.")
  } catch (error) {
    showSnackbar("Network error — is the device reachable?")
  } finally {
    state.savingKey = ""
  }
}

async function sendTestEvent() {
  if (state.testBusy) return
  state.testBusy = true
  try {
    const response = await fetch(galaxyPath("/api/sentry/test"), { method: "POST" })
    const payload = await response.json()
    if (!response.ok) {
      showSnackbar(payload.error || "Sentry test failed.")
      return
    }
    showSnackbar("Test capture started. The images will appear here shortly.")
  } catch (error) {
    showSnackbar("Network error — is the device reachable?")
  } finally {
    state.testBusy = false
  }
}

async function enablePush() {
  if (state.pushBusy) return
  state.pushBusy = true
  try {
    const result = await enableSentryPush()
    showSnackbar(result.message)
  } catch (error) {
    showSnackbar(error.message || "Could not enable Chrome notifications.")
  } finally {
    state.pushBusy = false
  }
}

async function sendTestPush() {
  if (state.pushBusy) return
  state.pushBusy = true
  try {
    await sendSentryTestPush()
    showSnackbar("Test push sent. Check your Chrome notifications.")
  } catch (error) {
    showSnackbar(error.message || "Could not send the test push.")
  } finally {
    state.pushBusy = false
  }
}

function renderEvent() {
  const event = state.event || {}
  if (!event.eventId) return html`<p class="sentry-empty">No Sentry events recorded yet.</p>`

  return html`
    <div class="sentry-event-meta">
      <span class="sentry-event-kind">${String(event.kind || "event").toUpperCase()}</span>
      <span>${event.detectedAt || ""}</span>
    </div>
    <p class="sentry-event-message">${event.message || "Movement detected while parked."}</p>
    ${Array.isArray(event.imageUrls) && event.imageUrls.length > 0 ? html`
      <div class="sentry-image-grid">
        ${event.imageUrls.map((url, index) => html`
          <a href="${galaxyPath(url)}" target="_blank" rel="noopener">
            <img src="${galaxyPath(url)}" alt="Sentry capture ${index + 1}" loading="lazy" />
          </a>
        `)}
      </div>
    ` : html`<p class="sentry-empty">No camera images were available for this event.</p>`}
  `
}

export function SentryMode() {
  startPolling()
  const remote = isGalaxyTunnel()

  return html`
    <div class="sentry-page">
      <div class="sentry-page-header">
        <div>
          <h2>Sentry Mode</h2>
          <p>Monitor the parked vehicle and review movement captures directly in Galaxy.</p>
        </div>
        <span class="sentry-status-pill">${() => state.status.state || "unknown"}</span>
      </div>

      <section class="sentry-card">
        <h3>Configuration</h3>
        <p class="sentry-muted">Galaxy is the built-in notification and image viewer. Webhook and ntfy delivery are optional.</p>

        ${() => state.loading ? html`<div class="sentry-loading">Loading Sentry settings…</div>` : html`
          <label class="sentry-setting-row">
            <span>
              <strong>Enable Sentry Mode</strong>
              <small>Detect sustained movement while the vehicle is parked.</small>
            </span>
            <input
              type="checkbox"
              class="sentry-toggle"
              checked="${() => !!state.params.SentryModeEnabled}"
              disabled="${() => state.savingKey === "SentryModeEnabled"}"
              @change="${(event) => saveParam("SentryModeEnabled", !!event.currentTarget.checked)}" />
          </label>

          <label class="sentry-field">
            <span><strong>Webhook URL</strong><small>Optional Discord-compatible or custom webhook.</small></span>
            <input
              class="sentry-input"
              type="url"
              value="${() => state.params.SentryModeWebhook || ""}"
              placeholder="https://…"
              disabled="${() => state.savingKey === "SentryModeWebhook"}"
              @change="${(event) => saveParam("SentryModeWebhook", event.currentTarget.value.trim())}" />
          </label>

          <label class="sentry-field">
            <span><strong>ntfy URL</strong><small>Optional ntfy topic URL for phone notifications.</small></span>
            <input
              class="sentry-input"
              type="url"
              value="${() => state.params.SentryModeNtfyUrl || ""}"
              placeholder="https://ntfy.sh/…"
              disabled="${() => state.savingKey === "SentryModeNtfyUrl"}"
              @change="${(event) => saveParam("SentryModeNtfyUrl", event.currentTarget.value.trim())}" />
          </label>

          <div class="sentry-action-row">
            <button class="sentry-button" @click="${enablePush}" disabled="${() => state.pushBusy}">
              ${() => state.pushBusy ? "Enabling…" : "Enable Chrome notifications"}
            </button>
            <button class="sentry-button sentry-button-secondary" @click="${sendTestPush}" disabled="${() => state.pushBusy}">
              ${() => state.pushBusy ? "Sending…" : "Send test push"}
            </button>
          </div>
          <p class="sentry-muted">Enable notifications once, then use the test push to verify Galaxy can reach this browser even when the page is not active.</p>
        `}
      </section>

      <section class="sentry-card">
        <div class="sentry-card-heading">
          <div>
            <h3>Latest Event</h3>
            <p class="sentry-muted">Events refresh automatically every five seconds.</p>
          </div>
          ${remote ? "" : html`
            <button class="sentry-button sentry-button-secondary" @click="${sendTestEvent}" disabled="${() => state.testBusy}">
              ${() => state.testBusy ? "Capturing…" : "Send test capture"}
            </button>
          `}
        </div>
        ${() => renderEvent()}
      </section>
    </div>
  `
}
