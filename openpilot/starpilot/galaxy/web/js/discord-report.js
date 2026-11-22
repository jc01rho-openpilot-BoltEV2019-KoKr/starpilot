import { requestJson } from "./startup.js"
import { GxNotice } from "./notice.js"

const ENDPOINT = "./api/settings/discord-report"

export const DiscordReportSettings = {
  components: { GxNotice },
  props: { unauthorized: Function },
  emits: ["changed"],
  data: () => ({ status: null, webhook: "", busy: false, error: "", saved: "" }),
  mounted() { this.load() },
  methods: {
    async load() {
      try { this.status = await requestJson(ENDPOINT) } catch (error) { this.failed(error) }
    },
    failed(error) {
      if (error.status === 401) this.unauthorized?.()
      else this.error = error.message || "Discord battery report settings are unavailable"
    },
    async send(body, message) {
      if (this.busy) return
      this.busy = true
      this.error = ""
      this.saved = ""
      try {
        this.status = await requestJson(ENDPOINT, { request: { method: "POST",
          headers: { "Content-Type": "application/json" }, body: JSON.stringify(body) } })
        this.webhook = ""
        this.saved = message
        this.$emit("changed")
      } catch (error) { this.failed(error) }
      finally { this.busy = false }
    },
    save() { this.send({ action: "save", webhook: this.webhook.trim() }, "Webhook saved. Drive-end battery reports are on.") },
    remove() {
      if (window.confirm("Remove the Discord webhook and stop battery reports?")) this.send({ action: "remove" }, "Webhook removed.")
    },
  },
  template: `<section v-if="status?.owner" class="gx-card gx-settings__section">
    <div class="gx-section__header"><i class="bi bi-battery-half" aria-hidden="true"></i><span class="gx-section__title">Discord battery report</span></div>
    <p class="gx-page-description">After each drive, sends the Panda 12 V supply voltage (latest, minimum, maximum) to a private Discord webhook. The saved URL is never shown again.</p>
    <form @submit.prevent="save">
      <fieldset :disabled="busy" style="border:0; margin:0; padding:0; min-width:0">
        <div class="gx-row"><span class="gx-row__info"><span class="gx-row__label">Webhook</span></span><span>{{ status.configured ? "Configured" : "Not configured" }}</span></div>
        <div class="gx-row gx-row--stack"><label class="gx-field-group">Discord webhook URL
          <input class="gx-field" type="password" v-model="webhook" placeholder="https://discord.com/api/webhooks/..." maxlength="512" required autocomplete="new-password" spellcheck="false"></label></div>
        <div class="gx-panel gx-actions">
          <button class="gx-btn" type="submit"><i class="bi bi-check-lg" aria-hidden="true"></i> Save</button>
          <button class="gx-btn" type="button" :disabled="!status.configured" @click="remove"><i class="bi bi-trash" aria-hidden="true"></i> Remove</button>
        </div>
      </fieldset>
    </form>
    <GxNotice v-if="saved" tone="info">{{ saved }}</GxNotice>
    <GxNotice v-if="error" tone="danger">{{ error }}</GxNotice>
  </section>`,
}
