export const LAYOUT_URL = "/assets/components/tools/device_settings_layout.json?v=settings-tier-1"

async function handle(res) {
  const data = await res.json().catch(() => ({}))
  if (!res.ok) {
    const err = new Error(data?.error || data?.message || res.statusText || "Request failed")
    err.data = data
    throw err
  }
  return data
}

export const api = {
  async postAction(endpoint) {
    const res = await fetch(endpoint, { method: "POST" })
    return handle(res)
  },

  async getOptions(endpoint) {
    const res = await fetch(endpoint)
    return handle(res)
  },

  async getLayout() {
    const res = await fetch(LAYOUT_URL, { cache: "no-store" })
    const data = await handle(res)
    return (data || [])
      .map((section) => ({ ...section, params: (section.params || []).filter((p) => p.key !== "Model") }))
      .filter((section) => (section.params || []).length > 0)
  },

  async getParams() {
    const res = await fetch("/api/params/all")
    return handle(res)
  },

  async getDefaults() {
    const res = await fetch("/api/params/defaults")
    return res.ok ? handle(res) : {}
  },

  async updateParam({ key, value, label }) {
    const body = { key, value }
    if (label) body.label = label
    const res = await fetch("/api/params", {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async getFlmWorkspace() {
    const res = await fetch("/api/flm/workspace", { cache: "no-store" })
    return res.ok ? handle(res) : null
  },

  async getFavoritesSlots() {
    const res = await fetch("/api/favorites/slots", { cache: "no-store" })
    return handle(res)
  },

  async saveFavoritesSlots(slots) {
    const res = await fetch("/api/favorites/slots", {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ slots }),
    })
    return handle(res)
  },

  async activateFavoriteAction(key) {
    const res = await fetch("/api/favorites/action", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ key }),
    })
    return handle(res)
  },

  async getDeviceStatus() {
    const res = await fetch("/api/device/status")
    return res.ok ? handle(res) : null
  },

  async getStats() {
    const res = await fetch("/api/stats")
    return res.ok ? handle(res) : null
  },

  
  async getRoutesStream({ onProgress, onRoutes, signal } = {}) {
    const res = await fetch("/api/routes", { signal })
    if (!res.ok || !res.body) throw new Error(`Route request failed (${res.status})`)
    const reader = res.body.getReader()
    const decoder = new TextDecoder()
    let buffer = ""
    while (true) {
      const { value, done } = await reader.read()
      if (done) break
      buffer += decoder.decode(value, { stream: true })
      const events = buffer.split(/\r?\n\r?\n/)
      buffer = events.pop() || ""
      for (const event of events) {
        const lines = event.split(/\r?\n/).filter((l) => l.startsWith("data:"))
        if (!lines.length) continue
        try {
          const payload = JSON.parse(lines.map((l) => l.slice(5).trimStart()).join("\n"))
          if (Number.isFinite(payload.progress)) onProgress?.(payload.progress)
          onRoutes?.(Array.isArray(payload.routes) ? payload.routes : [])
        } catch (e) {  }
      }
    }
  },

  async getRoute(name) {
    const res = await fetch(`/api/routes/${encodeURIComponent(name)}`)
    return handle(res)
  },

  async deleteRoute(name) {
    const res = await fetch(`/api/routes/${encodeURIComponent(name)}`, { method: "DELETE" })
    return handle(res)
  },

  async renameRoute(oldName, newName) {
    const res = await fetch("/api/routes/rename", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ old: oldName, new: newName }),
    })
    return handle(res)
  },

  async resetRouteName(name) {
    const res = await fetch("/api/routes/reset_name", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ name }),
    })
    return handle(res)
  },

  async setRoutePreserved(name, preserved) {
    const res = await fetch(`/api/routes/${encodeURIComponent(name)}/preserve`, { method: preserved ? "POST" : "DELETE" })
    return handle(res)
  },

  async deleteAllRoutes(includePreserved) {
    const res = await fetch(`/api/routes/delete_all?include_preserved=${includePreserved}`, { method: "DELETE" })
    return handle(res)
  },

  async getRouteLogs(name) {
    const res = await fetch(`/api/routes/${encodeURIComponent(name)}/logs`)
    return handle(res)
  },

  async getScreenRecordings() {
    const res = await fetch("/api/screen_recordings/list")
    return handle(res)
  },

  async deleteScreenRecording(filename) {
    const res = await fetch(`/api/screen_recordings/delete/${encodeURIComponent(filename)}`, { method: "DELETE" })
    return handle(res)
  },

  async deleteAllScreenRecordings() {
    const res = await fetch("/api/screen_recordings/delete_all", { method: "DELETE" })
    return handle(res)
  },

  async renameScreenRecording(oldName, newName) {
    const res = await fetch("/api/screen_recordings/rename", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ old: oldName, new: newName }),
    })
    return handle(res)
  },

  
  async getErrorLogs() {
    const res = await fetch("/api/error_logs", { headers: { Accept: "application/json" } })
    return handle(res)
  },

  async getErrorLog(filename) {
    const res = await fetch(`/api/error_logs/${encodeURIComponent(filename)}`)
    return res.text()
  },

  async deleteErrorLog(filename) {
    const res = await fetch(`/api/error_logs/${encodeURIComponent(filename)}`, { method: "DELETE" })
    return res.ok
  },

  async deleteAllErrorLogs() {
    const res = await fetch("/api/error_logs/delete_all", { method: "DELETE" })
    return res.ok
  },

  async getTmuxLogs() {
    const res = await fetch("/api/tmux_log/list")
    return handle(res)
  },

  async tmuxCapture() {
    const res = await fetch("/api/tmux_log/capture", { method: "POST" })
    return res.ok
  },

  async tmuxSnapshot() {
    const res = await fetch("/api/tmux_log/snapshot")
    return handle(res)
  },

  async deleteTmuxLog(filename) {
    const res = await fetch(`/api/tmux_log/delete/${encodeURIComponent(filename)}`, { method: "DELETE" })
    return res.ok
  },

  async deleteAllTmuxLogs() {
    const res = await fetch("/api/tmux_log/delete_all", { method: "DELETE" })
    return res.ok
  },

  async renameTmuxLog(oldName, newName) {
    const res = await fetch(`/api/tmux_log/rename/${encodeURIComponent(oldName)}/${encodeURIComponent(newName)}`, { method: "PUT" })
    return res.ok
  },

  async runTroubleshoot() {
    const res = await fetch("/api/troubleshoot", { method: "POST" })
    return handle(res)
  },

  async getTroubleshoot() {
    const res = await fetch("/api/troubleshoot")
    return res.ok ? handle(res) : null
  },

  async resetTroubleshoot() {
    const res = await fetch("/api/troubleshoot/reset", { method: "POST" })
    return res.ok
  },

  
  async getWheelControlsStatus() {
    const res = await fetch("/api/wheel-controls/status", { cache: "no-store" })
    return handle(res)
  },

  async wheelControlsOp(operation, body = {}) {
    const res = await fetch(`/api/wheel-controls/${operation}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async getBluetoothStatus() {
    const res = await fetch("/api/bluetooth/status")
    return handle(res)
  },

  async bluetoothOp(operation, body = {}) {
    const res = await fetch(`/api/bluetooth/${operation}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async carFeaturesCheck(tool = "") {
    const query = tool ? `?tool=${encodeURIComponent(tool)}` : ""
    const res = await fetch(`/api/car_features_check${query}`)
    return res.ok ? handle(res) : null
  },

  
  async lateralManeuvers(action) {
    const res = await fetch(`/api/lateral_maneuvers/${action}`, { method: "POST" })
    return handle(res)
  },

  async lateralManeuversStatus() {
    const res = await fetch("/api/lateral_maneuvers/status")
    return handle(res)
  },

  async longitudinalManeuvers(action) {
    const res = await fetch(`/api/longitudinal_maneuvers/${action}`, { method: "POST" })
    return handle(res)
  },

  async longitudinalManeuversStatus() {
    const res = await fetch("/api/longitudinal_maneuvers/status")
    return handle(res)
  },

  
  async getMapsStatus() {
    const res = await fetch("/api/maps/status")
    return handle(res)
  },

  async getMapsCatalog() {
    const res = await fetch("/api/maps/catalog")
    return handle(res)
  },

  async mapsOp(operation, body = {}) {
    const res = await fetch(`/api/maps/${operation}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async getNavigation() {
    const res = await fetch("/api/navigation")
    return handle(res)
  },

  async setNavigation(body) {
    const res = await fetch("/api/navigation", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async getNavigationKeys() {
    const res = await fetch("/api/navigation_key")
    return handle(res)
  },

  async setNavigationKey(body) {
    const res = await fetch("/api/navigation_key", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async navigationFavorite(body) {
    const res = await fetch("/api/navigation/favorite", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  
  async backupToggles() {
    const res = await fetch("/api/toggles/backup", { method: "POST" })
    if (!res.ok) {
      const data = await res.json().catch(() => ({}))
      throw new Error(data?.message || "Failed to create toggle backup.")
    }
    return res.blob()
  },

  async restoreToggles(data) {
    const res = await fetch("/api/toggles/restore", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(data),
    })
    return handle(res)
  },

  async resetTogglesDefault() {
    const res = await fetch("/api/toggles/reset_default", { method: "POST" })
    return handle(res)
  },

  async getUpdateBranches() {
    const res = await fetch("/api/update/branches")
    return handle(res)
  },

  async getUpdateBranch() {
    const res = await fetch("/api/update/branch")
    return handle(res)
  },

  async setUpdateBranch(branch) {
    const res = await fetch("/api/update/branch", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ branch }),
    })
    return handle(res)
  },

  async updateFast() {
    const res = await fetch("/api/update/fast", { method: "POST" })
    return handle(res)
  },

  async getUpdateFastStatus() {
    const res = await fetch("/api/update/fast/status")
    return handle(res)
  },

  async updateRecover() {
    const res = await fetch("/api/update/recover", { method: "POST" })
    return handle(res)
  },

  async updateRollback() {
    const res = await fetch("/api/update/rollback", { method: "POST" })
    return handle(res)
  },

  async factoryReset() {
    const res = await fetch("/api/update/factory_reset", { method: "POST" })
    return handle(res)
  },

  async getAgnosStatus() {
    const res = await fetch("/api/update/agnos_status")
    return res.ok ? handle(res) : null
  },

  
  async getVasmConfig() {
    const res = await fetch("/api/v_asm/config")
    return handle(res)
  },

  async setVasmConfig(body) {
    const res = await fetch("/api/v_asm/config", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async vasmSnapshot() {
    const res = await fetch("/api/v_asm/snapshot")
    return res.ok ? handle(res) : null
  },

  async getPipConfig() {
    const res = await fetch("/api/pip_preview/config")
    return handle(res)
  },

  async setPipConfig(body) {
    const res = await fetch("/api/pip_preview/config", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    })
    return handle(res)
  },

  async pipSnapshot() {
    const res = await fetch("/api/pip_preview/snapshot")
    return res.ok ? handle(res) : null
  },
}

export function showSnackbar(message, level = "info") {
  const wrapper = document.getElementById("snackbar_wrapper")
  if (!wrapper) return
  for (const el of Array.from(wrapper.children)) {
    el.classList.remove("show")
    el.remove()
  }
  const el = document.createElement("div")
  el.className = "snackbar show"
  el.style.background = level === "error" ? "var(--error)" : "var(--color-confirm, #8b6cc5)"
  el.style.borderRadius = "var(--border-radius-base, 5px)"
  el.style.color = "var(--text-color, #fff)"
  el.style.margin = "0 auto var(--margin-base, 1rem)"
  el.style.padding = "var(--padding-base, 1rem)"
  el.style.textAlign = "center"
  el.textContent = message
  wrapper.appendChild(el)
  setTimeout(() => {
    el.classList.remove("show")
    setTimeout(() => el.remove(), 500)
  }, 2400)
}
