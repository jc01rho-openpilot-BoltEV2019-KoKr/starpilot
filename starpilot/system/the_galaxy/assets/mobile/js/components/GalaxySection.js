export const GalaxySection = {
  name: "GalaxySection",
  props: {
    title: { type: String, required: true },
    icon: { type: String, default: "bi-toggles" },
    count: { type: [Number, String], default: "" },
    defaultOpen: { type: Boolean, default: true },
  },
  data() { return { open: this.defaultOpen } },
  template: `
    <section class="gx-card">
      <div class="gx-section__header" role="button" @click="open = !open">
        <i class="bi" :class="icon"></i>
        <span class="gx-section__title">{{ title }}</span>
        <span v-if="count !== ''" class="gx-section__count">{{ count }}</span>
        <i class="bi bi-chevron-down gx-chevron" :class="{ open }"></i>
      </div>
      <transition name="gx-collapse">
        <div v-show="open" class="gx-section__body">
          <slot />
        </div>
      </transition>
    </section>
  `,
}
