import { GalaxyEmbed } from "../components/GalaxyEmbed.js"

export const Home = {
  name: "Home",
  components: { GalaxyEmbed },
  template: `
    <div class="gx-view">
      <GalaxyEmbed src="/classic" title="Home" />
    </div>
  `,
}
