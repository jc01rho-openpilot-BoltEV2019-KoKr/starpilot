import { GalaxyEmbed } from "../components/GalaxyEmbed.js"

export const Tuning = {
  name: "Tuning",
  components: { GalaxyEmbed },
  template: `
    <div class="gx-view">
      <div class="gx-section__header" style="padding: var(--sp-3) var(--sp-4);">
        <i class="bi bi-sign-turn-right"></i>
        <span class="gx-section__title">Tuning & Maneuvers</span>
      </div>
      <GalaxyEmbed src="/tuning" title="Tuning" />
    </div>
  `,
}
