import { api, showSnackbar } from "../api.js"
import { usePolling } from "../composables.js"
import { GalaxyConfirm } from "../components/GalaxyModal.js"
import { GalaxySection } from "../components/GalaxySection.js"
import { GalaxyEmbed } from "../components/GalaxyEmbed.js"

function shortCommit(commit) {
  return String(commit || "").slice(0, 10) || "—"
}

export const SystemTools = {
  name: "SystemTools",
  components: { GalaxySection, GalaxyEmbed },
  data() {
    return {
      branches: [],
      currentBranch: "",
      branchLoading: true,
      fastStatus: null,
      checkedForUpdates: false,
      busy: "",
    }
  },
  created() { this.poll = usePolling(() => this.loadFastStatus(), { interval: 3000 }); this.poll.start() },
  mounted() { this.loadBranches() },
  beforeUnmount() { this.poll?.destroy() },
  computed: {
    updateAvailable() { return !!this.fastStatus?.updateAvailable && !this.fastStatus?.running },
  },
  methods: {
    shortCommit,
    async loadBranches() {
      try {
        const data = await api.getUpdateBranches()
        this.branches = Array.isArray(data?.branches) ? data.branches : []
        this.currentBranch = data?.currentBranch || ""
        this.isOnroad = !!data?.isOnroad
      } catch (e) {
        showSnackbar("Failed to load update info.", "error")
      } finally {
        this.branchLoading = false
      }
    },
    async loadFastStatus() {
      try { this.fastStatus = await api.getUpdateFastStatus() } catch (e) { this.fastStatus = null }
    },
    async backupToggles() {
      try {
        const blob = await api.backupToggles()
        const url = URL.createObjectURL(blob)
        const a = document.createElement("a")
        a.href = url
        a.download = "toggle-backup.json"
        a.click()
        setTimeout(() => URL.revokeObjectURL(url), 1000)
        showSnackbar("Toggle backup downloaded.")
      } catch (e) {
        showSnackbar(e?.message || "Backup failed.", "error")
      }
    },
    onRestoreFile(e) {
      const file = e.target.files[0]
      e.target.value = ""
      if (!file) return
      if (file.size > 5_000_000) { showSnackbar("That toggle backup file is too large.", "error"); return }
      file.text().then((text) => {
        let data
        try { data = JSON.parse(text) } catch { showSnackbar("That file is not a valid toggle backup.", "error"); return }
        if (!data || typeof data !== "object" || Array.isArray(data)) { showSnackbar("That file is not a valid toggle backup.", "error"); return }
        api.restoreToggles(data).then((res) => {
          showSnackbar(res?.message || "Toggles restored!")
        }).catch((err) => showSnackbar(err?.message || "Failed to restore toggles.", "error"))
      })
    },
    async resetDefault() {
      if (!(await GalaxyConfirm({ title: "Reset toggles to default?", message: "This resets all toggles to their default values and reboots.", confirmLabel: "Reset", danger: true }))) return
      try {
        await api.resetTogglesDefault()
        showSnackbar("Resetting toggles to default... rebooting.")
      } catch (e) {
        showSnackbar("Reset failed.", "error")
      }
    },
    onBranchSelect(e) {
      const branch = e.target.value
      e.target.value = this.currentBranch || ""
      this.switchBranch(branch)
    },
    async switchBranch(branch) {
      if (!branch || branch === this.currentBranch) return
      if (!(await GalaxyConfirm({ title: "Switch branch?", message: `Switch to ${branch} and update?`, confirmLabel: "Switch" }))) return
      try {
        await api.setUpdateBranch(branch)
        showSnackbar(`Switching to ${branch}...`)
      } catch (e) {
        showSnackbar(e?.message || "Switch failed.", "error")
      }
    },
    async checkUpdates() {
      if (this.busy) return
      this.busy = "check"
      try {
        await this.loadFastStatus()
        this.checkedForUpdates = true
        const st = this.fastStatus
        if (st?.running) showSnackbar("An update is already running.")
        else if (st?.updateAvailable) showSnackbar(st?.message || "Update available.")
        else showSnackbar(st?.message || "No update available — you're up to date.")
      } catch (e) {
        showSnackbar("Failed to check for updates.", "error")
      } finally {
        this.busy = ""
      }
    },
    async applyFastUpdate() {
      if (this.busy || this.isOnroad) return
      if (this.fastStatus?.running) { showSnackbar("Fast update is already running."); return }
      if (!this.checkedForUpdates || !this.updateAvailable) {
        showSnackbar("No update available. Run \"Check for Updates\" first.", "error")
        return
      }
      const st = this.fastStatus
      const confirmed = await GalaxyConfirm({
        title: "Update available",
        message: `Fast update to the latest commit on ${st?.branch || "this branch"}.\n\nYour device will reboot when the update is done.`,
        confirmLabel: "Update & Reboot",
        danger: true,
      })
      if (!confirmed) return
      await this.runUpdate("fast")
    },
    async runUpdate(action) {
      if (this.busy) return
      this.busy = action
      try {
        if (action === "rollback") {
          const st = this.fastStatus
          if (st && !st.rollbackAvailable) {
            showSnackbar("No previous installed version is available to roll back to.", "error")
            return
          }
        }
        if (action !== "fast") {
          const actionLabels = { recover: "Recover the interrupted update?", rollback: "Roll back to the previous installed version?" }
          if (!(await GalaxyConfirm({ title: actionLabels[action] || "Continue?", message: "Your device will reboot when the operation is done.", confirmLabel: "Continue", danger: true }))) return
        }
        const fn = action === "fast" ? api.updateFast : action === "recover" ? api.updateRecover : api.updateRollback
        const payload = await fn()
        showSnackbar(payload?.message || "Update started.")
        await this.loadFastStatus()
      } catch (e) {
        showSnackbar(e?.message || "Update failed.", "error")
      } finally {
        this.busy = ""
      }
    },
    async factoryReset() {
      if (!(await GalaxyConfirm({ title: "Factory reset?", message: "This wipes params, backups, themes, models, maps, and route data, then reboots. This cannot be undone.", confirmLabel: "Factory Reset", danger: true }))) return
      try {
        await api.factoryReset()
        showSnackbar("Factory resetting...")
      } catch (e) {
        showSnackbar(e?.message || "Factory reset failed.", "error")
      }
    },
    async saveMe() {
      if (!(await GalaxyConfirm({ title: "SAVE ME", message: "This will factory reset the device by wiping params, backups, themes, models, maps, and route data. The device will reboot when the wipe is complete. This cannot be undone.", confirmLabel: "Factory Reset", danger: true }))) return
      try {
        await api.factoryReset()
        showSnackbar("SAVE ME initiated — factory resetting...")
      } catch (e) {
        showSnackbar(e?.message || "Factory reset failed.", "error")
      }
    },
    async deleteAllDrivingRoutes() {
      if (!(await GalaxyConfirm({ title: "Delete All Driving Routes", message: "This permanently deletes all local routes from standard, high-resolution, and alternate footage storage. It does not reset settings or reboot the device.", confirmLabel: "Delete Routes", danger: true }))) return
      try {
        const payload = await api.deleteAllRoutes(true)
        showSnackbar(payload?.message || "All local driving routes deleted.")
      } catch (e) {
        showSnackbar(e?.message || "Failed to delete driving routes.", "error")
      }
    },
  },
  template: `
    <div>
      <h2 style="margin-top:0;">System Tools</h2>

      <GalaxySection title="Backup & Restore" icon="bi-arrow-repeat">
        <div style="padding: var(--sp-3); display:flex; gap:8px; flex-wrap:wrap;">
          <button type="button" class="gx-btn" @click="backupToggles"><i class="bi bi-download"></i> Backup Toggles</button>
          <button type="button" class="gx-btn gx-btn--tonal" @click="$refs.restoreInput.click()"><i class="bi bi-upload"></i> Restore Toggles</button>
          <button type="button" class="gx-btn gx-btn--tonal" @click="resetDefault">Reset to Default</button>
          <button type="button" class="gx-btn" style="background:var(--error);color:var(--on-error);" @click="saveMe">SAVE ME</button>
          <button type="button" class="gx-btn" style="background:var(--error);color:var(--on-error);" @click="deleteAllDrivingRoutes">Delete All Driving Routes</button>
          <input ref="restoreInput" type="file" accept=".json" style="display:none;" @change="onRestoreFile" />
        </div>
        <GalaxyEmbed src="/manage_toggles" title="Backup & Restore" style="min-height:60vh; margin: var(--sp-3);" />
      </GalaxySection>

      <GalaxySection title="Software & Updates" icon="bi-arrow-up-circle">
        <div style="padding: var(--sp-3);">
          <div v-if="branchLoading" class="gx-loading">Loading update info...</div>
          <template v-else>
            <p v-if="isOnroad" style="color:var(--text-muted);">Updates and branch switching are only available while offroad.</p>

            <div v-if="fastStatus" class="gx-card" style="margin-bottom:12px;">
              <div class="gx-section__header">
                <i class="bi bi-arrow-repeat"></i>
                <span class="gx-section__title">Update Status</span>
                <span v-if="fastStatus.running" class="gx-chip" style="background:var(--primary);color:var(--on-primary);">{{ fastStatus.progressPercent }}%</span>
                <span v-else-if="fastStatus.updateAvailable" class="gx-chip" style="background:var(--warning);color:var(--black);">Update available</span>
                <span v-else class="gx-chip">Up to date</span>
              </div>
              <div style="padding: var(--sp-3); display:grid; gap:6px;">
                <div class="gx-row" style="border-top:none; min-height:0; padding:4px 0;"><span class="gx-row__label">Branch</span><span class="gx-row__value">{{ fastStatus.branch || currentBranch || '—' }}</span></div>
                <div v-if="fastStatus.running" class="gx-row" style="border-top:none; min-height:0; padding:4px 0;"><span class="gx-row__label">Stage</span><span class="gx-row__value">{{ fastStatus.stage }} · {{ fastStatus.progressLabel }}</span></div>
                <div class="gx-row" style="border-top:none; min-height:0; padding:4px 0;"><span class="gx-row__label">Local</span><span class="gx-row__value" style="font-family:monospace;">{{ shortCommit(fastStatus.localCommit) }}</span></div>
                <div class="gx-row" style="border-top:none; min-height:0; padding:4px 0;"><span class="gx-row__label">Remote</span><span class="gx-row__value" style="font-family:monospace;">{{ shortCommit(fastStatus.remoteCommit) }}</span></div>
                <div v-if="fastStatus.message" class="gx-row__desc">{{ fastStatus.message }}</div>
                <div v-if="fastStatus.warning && (fastStatus.running || fastStatus.updateAvailable)" class="gx-row__desc" style="color:var(--warning);">{{ fastStatus.warning }}</div>
                <div v-if="fastStatus.agnosUpdate?.available && fastStatus.agnosUpdate?.warnings?.length" style="margin-top:4px;">
                  <div v-for="w in fastStatus.agnosUpdate.warnings" :key="w" class="gx-row__desc" style="color:var(--warning);">⚠ {{ w }}</div>
                </div>
              </div>
            </div>

            <h4 style="margin:12px 0 8px;">Switch branch</h4>
            <div class="gx-row" style="border-top:none; padding:4px 0;">
              <select class="gx-field gx-field--full" :disabled="!!isOnroad" @change="onBranchSelect">
                <option v-if="!branches.length" value="">No branches available</option>
                <option v-for="b in branches" :key="b" :value="b" :selected="b === currentBranch">{{ b === currentBranch ? b + ' (current)' : b }}</option>
              </select>
            </div>
            <div style="display:flex; gap:8px; margin-top:12px; flex-wrap:wrap;">
              <button type="button" class="gx-btn gx-btn--tonal" :disabled="!!busy || isOnroad || !!fastStatus?.running" @click="checkUpdates">
                <i v-if="busy === 'check'" class="bi bi-arrow-repeat gx-spin"></i>
                <i v-else class="bi bi-search"></i> {{ busy === 'check' ? 'Checking...' : 'Check for Updates' }}
              </button>
              <button type="button" class="gx-btn" :disabled="!updateAvailable || !!busy || isOnroad" @click="applyFastUpdate">
                <i class="bi bi-arrow-up-circle"></i> {{ busy === 'fast' ? 'Updating...' : 'Update Now' }}
              </button>
              <button type="button" class="gx-btn gx-btn--tonal" :disabled="!!busy || isOnroad" @click="runUpdate('recover')">Recover</button>
              <button type="button" class="gx-btn gx-btn--tonal" :disabled="!!busy || isOnroad" @click="runUpdate('rollback')">Rollback</button>
            </div>
            <p v-if="checkedForUpdates && !updateAvailable && !fastStatus?.running" style="color:var(--text-muted); margin:8px 0 0;">
              The device is up to date. Update becomes available only after a check finds a newer commit.
            </p>
          </template>
        </div>
      </GalaxySection>

      <GalaxySection title="Danger Zone" icon="bi-exclamation-triangle">
        <div style="padding: var(--sp-3);">
          <p style="color: var(--text-muted);">Last resort only. This wipes params, backups, themes, models, maps, and route data, then reboots the device.</p>
          <button type="button" class="gx-btn" style="background:var(--error);color:var(--on-error);" @click="factoryReset">Factory Reset Device</button>
        </div>
      </GalaxySection>
    </div>
  `,
}
