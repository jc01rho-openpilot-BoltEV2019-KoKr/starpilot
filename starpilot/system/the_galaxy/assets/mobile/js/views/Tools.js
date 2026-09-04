import { navigate, toolHref } from "../store.js"

const TOOLS = [
  { name: "Galaxy", link: "/galaxy", icon: "bi-globe2", desc: "Pairing & remote access" },
  { name: "Logs & Diagnostics", link: "/logs", icon: "bi-exclamation-triangle", desc: "Error logs, tmux, troubleshoot" },
  { name: "Model Manager", link: "/manage_models", icon: "bi-cpu", desc: "Install/swap models" },
  { name: "Navigation & Maps", link: "/navigation", icon: "bi-map", desc: "Offline maps & destinations" },
  { name: "PiP Side Camera", link: "/manage_pip_sidecam", icon: "bi-camera-video", desc: "Adjust PiP side-camera window" },
  { name: "Plots", link: "/plots", icon: "bi-graph-up-arrow", desc: "Live telemetry plots" },
  { name: "Sentry Mode", link: "/sentry", icon: "bi-shield-exclamation", desc: "Sentry alerts & security" },
  { name: "System Tools", link: "/system", icon: "bi-arrow-repeat", desc: "Backup, restore, updates" },
  { name: "Testing Ground", link: "/testing_ground", icon: "bi-bezier2", desc: "Experiments & testing" },
  { name: "Theme Maker", link: "/theme_maker", icon: "bi-palette-fill", desc: "Customize the look" },
  { name: "Tuning & Maneuvers", link: "/tuning", icon: "bi-sign-turn-right", desc: "Steering & speed behaviour" },
  { name: "V-ASM Spot Monitor", link: "/manage_v_asm", icon: "bi-bounding-box", desc: "Adjust spot-monitor window" },
  { name: "Vehicle Controls", link: "/vehicle", icon: "bi-car-front", desc: "Controllers, bluetooth, vehicle features" },
].sort((a, b) => a.name.localeCompare(b.name))

export const Tools = {
  name: "Tools",
  data() { return { TOOLS } },
  methods: {
    open(t) {
      navigate(toolHref(t.link))
    },
  },
  template: `
    <div>
      <h2 style="margin-top:0;">Tools</h2>
      <div class="gx-grid">
        <button v-for="t in TOOLS" :key="t.link" type="button" class="gx-tile" @click="open(t)">
          <i class="bi" :class="t.icon"></i>
          <span>{{ t.name }}</span>
          <small style="color: var(--text-muted);">{{ t.desc }}</small>
        </button>
      </div>
    </div>
  `,
}
