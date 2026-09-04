import { api, showSnackbar } from "../api.js"
import { GalaxyConfirm } from "../components/GalaxyModal.js"
import { GalaxySection } from "../components/GalaxySection.js"

function fmtDuration(seconds) {
  seconds = Number(seconds) || 0
  const h = Math.floor(seconds / 3600)
  const m = Math.floor((seconds % 3600) / 60)
  return h > 0 ? `${h}h ${m}m` : `${m}m`
}

function formatBytes(bytes) {
  if (!bytes) return "0 MB"
  const mb = bytes / 1e6
  return mb >= 1000 ? `${(mb / 1000).toFixed(2)} GB` : `${mb.toFixed(1)} MB`
}

function normalizeRoute(r) {
  const name = String(r?.name || "")
  const isCustomName = !!r?.isCustomName
  return {
    name,
    displayName: r?.displayName || name.split("--").pop() || name,
    displayDate: r?.displayDate || "",
    approxDurationSeconds: Number(r?.approxDurationSeconds || 0),
    segmentCount: Number(r?.segmentCount || r?.numSegments || 0),
    is_preserved: !!r?.is_preserved,
    isCustomName,
    png: r?.png || "",
  }
}

export const Recordings = {
  name: "Recordings",
  components: { GalaxySection },
  data() {
    return {
      loading: true,
      error: "",
      routes: [],
      progress: 0,
      searchQuery: "",
      sortOrder: "newest",
      showPreservedOnly: false,
      playerRoute: null,
      playerLoading: false,
      playerError: "",
      segments: [],
      current: 0,
      cameras: [],
      selectedCamera: "",
      logsRoute: null,
      logsData: null,
    }
  },
  computed: {
    stats() {
      return {
        count: this.routes.length,
        formattedDuration: fmtDuration(this.routes.reduce((n, r) => n + r.approxDurationSeconds, 0)),
        preservedCount: this.routes.filter((r) => r.is_preserved).length,
      }
    },
    visibleRoutes() {
      let list = this.routes.slice()
      if (this.showPreservedOnly) list = list.filter((r) => r.is_preserved)
      if (this.searchQuery.trim()) {
        const q = this.searchQuery.toLowerCase()
        list = list.filter((r) => [r.displayName, r.displayDate, r.name].some((v) => String(v || "").toLowerCase().includes(q)))
      }
      const sorters = {
        newest: (a, b) => (b.name > a.name ? 1 : -1),
        oldest: (a, b) => (a.name > b.name ? 1 : -1),
        longest: (a, b) => b.approxDurationSeconds - a.approxDurationSeconds,
        shortest: (a, b) => a.approxDurationSeconds - b.approxDurationSeconds,
      }
      return list.sort(sorters[this.sortOrder] || sorters.newest)
    },
  },
  methods: {
    fmtDuration,
    formatBytes,
    async loadRoutes() {
      this.loading = true
      this.error = ""
      this.routes = []
      this.progress = 0
      const seen = new Set()
      try {
        this.controller?.abort()
        this.controller = new AbortController()
        await api.getRoutesStream({
          signal: this.controller.signal,
          onProgress: (p) => { this.progress = p },
          onRoutes: (raw) => {
            for (const r of raw) {
              if (seen.has(r.name)) continue
              seen.add(r.name)
              this.routes.push(normalizeRoute(r))
            }
          },
        })
      } catch (e) {
        if (e?.name !== "AbortError") this.error = "Couldn't load routes. Try refreshing."
      } finally {
        this.loading = false
      }
    },
    async deleteRoute(route) {
      if (!(await GalaxyConfirm({ title: "Delete route?", message: `Delete “${route.displayName}”?`, confirmLabel: "Delete", danger: true }))) return
      try {
        await api.deleteRoute(route.name)
        this.routes = this.routes.filter((r) => r.name !== route.name)
        showSnackbar("Route deleted!")
      } catch (e) {
        showSnackbar("Delete failed.", "error")
      }
    },
    async togglePreserved(route) {
      try {
        await api.setRoutePreserved(route.name, !route.is_preserved)
        route.is_preserved = !route.is_preserved
      } catch (e) {
        showSnackbar("Failed to update preserved state.", "error")
      }
    },
    async renameRoute(route) {
      const newName = prompt("Rename route:", route.displayName)
      if (!newName || newName === route.displayName) return
      try {
        const payload = await api.renameRoute(route.name, newName)
        Object.assign(route, normalizeRoute({ ...route, name: payload.name || newName, isCustomName: true }))
        route.displayName = payload.name || newName
        showSnackbar("Route renamed!")
      } catch (e) {
        showSnackbar("Rename failed.", "error")
      }
    },
    async deleteAllRoutes(includePreserved) {
      const label = includePreserved ? "Delete all routes, including preserved?" : "Delete all non-preserved routes?"
      if (!(await GalaxyConfirm({ title: label, message: "This action cannot be undone.", confirmLabel: includePreserved ? "Delete Everything" : "Delete Non-Preserved", danger: true }))) return
      try {
        const payload = await api.deleteAllRoutes(includePreserved)
        this.routes = []
        showSnackbar(payload?.message || "Routes deleted!")
      } catch (e) {
        showSnackbar("Failed to delete routes.", "error")
      }
    },
    async openPlayer(route) {
      this.playerRoute = route
      this.playerLoading = true
      this.playerError = ""
      try {
        const data = await api.getRoute(route.name)
        const segments = Array.isArray(data.segment_urls) ? data.segment_urls.filter((u) => typeof u === "string") : []
        const cameras = ["forward", "wide", "driver"].filter((c) => data.available_cameras?.includes(c))
        if (!segments.length) throw new Error("No video segments for this route.")
        if (!cameras.length) throw new Error("No camera video for this route.")
        this.segments = segments
        this.current = 0
        this.cameras = cameras
        this.selectedCamera = cameras.includes("forward") ? "forward" : cameras[0]
        this.$nextTick(() => this.playSegment())
      } catch (e) {
        this.playerError = e?.message || "Could not load route."
      } finally {
        this.playerLoading = false
      }
    },
    cameraUrl(url, low) {
      if (this.selectedCamera === "forward") return low && !url.includes("?" ) ? `${url}?quality=low` : url
      const sep = url.includes("?") ? "&" : "?"
      return `${url}${sep}camera=${encodeURIComponent(this.selectedCamera)}${low ? "&quality=low" : ""}`
    },
    playSegment() {
      const video = this.$refs.player
      if (!video || !this.segments[this.current]) return
      video.src = this.cameraUrl(this.segments[this.current])
      video.load()
      video.play().catch(() => {})
    },
    downloadRoute() {
      if (!this.playerRoute) return
      const a = document.createElement("a")
      a.href = `/video/${this.playerRoute.name}/combined?camera=${encodeURIComponent(this.selectedCamera)}`
      a.download = `${this.playerRoute.displayName}-${this.selectedCamera}.mp4`
      a.click()
    },
    closePlayer() {
      if (this.$refs.player) { this.$refs.player.pause(); this.$refs.player.removeAttribute("src") }
      this.playerRoute = null
      this.playerLoading = false
      this.playerError = ""
      this.segments = []
      this.cameras = []
    },
    async openLogs(route) {
      try {
        this.logsData = await api.getRouteLogs(route.name)
        this.logsRoute = route
      } catch (e) {
        showSnackbar("Could not read logs.", "error")
      }
    },
  },
  async mounted() { await this.loadRoutes() },
  beforeUnmount() { this.controller?.abort() },
  template: `
    <div>
      <h2 style="margin-top:0;">Recordings</h2>

      <section class="gx-card">
        <div class="gx-section__header">
          <i class="bi bi-camera-reels"></i>
          <span class="gx-section__title">Dashcam Routes</span>
          <span class="gx-section__count">{{ stats.count }} drives · {{ stats.formattedDuration }}</span>
        </div>
        <div style="padding: var(--sp-3); display:flex; gap:8px; flex-wrap:wrap;">
          <input class="gx-field" style="flex:1; min-width:160px;" type="search" placeholder="Search routes..." v-model="searchQuery" />
          <select class="gx-field" v-model="sortOrder">
            <option value="newest">Newest first</option>
            <option value="oldest">Oldest first</option>
            <option value="longest">Longest duration</option>
            <option value="shortest">Shortest duration</option>
          </select>
          <button type="button" class="gx-chip" :style="!showPreservedOnly?'background:var(--primary);color:var(--on-primary);':''" @click="showPreservedOnly=false">All</button>
          <button type="button" class="gx-chip" :style="showPreservedOnly?'background:var(--primary);color:var(--on-primary);':''" @click="showPreservedOnly=true">Preserved</button>
        </div>
      </section>

      <div v-if="loading" class="gx-loading">Finding local routes... ({{ Math.round(progress) }}%)</div>
      <div v-if="error" class="gx-empty" style="color: var(--error);">{{ error }}</div>
      <section class="gx-card">
        <div v-if="!visibleRoutes.length && !loading" class="gx-empty">No routes found.</div>
        <article v-for="r in visibleRoutes" :key="r.name" class="gx-row" style="cursor:pointer;" @click="openPlayer(r)">
          <div class="gx-row__info">
            <span class="gx-row__label">{{ r.displayName }} <span v-if="r.is_preserved" class="gx-chip gx-chip--dev">Preserved</span></span>
            <span class="gx-row__desc">{{ fmtDuration(r.approxDurationSeconds) }} · {{ r.segmentCount }} segments</span>
          </div>
          <div style="display:flex; gap:6px;">
            <button type="button" class="gx-btn gx-btn--tonal" title="Preserve" @click.stop="togglePreserved(r)"><i class="bi" :class="r.is_preserved ? 'bi-heart-fill' : 'bi-heart'"></i></button>
            <button type="button" class="gx-btn gx-btn--tonal" title="Logs" @click.stop="openLogs(r)"><i class="bi bi-file-earmark-arrow-down"></i></button>
            <button type="button" class="gx-btn gx-btn--tonal" title="Rename" @click.stop="renameRoute(r)"><i class="bi bi-pencil"></i></button>
            <button type="button" class="gx-btn" style="background:var(--error);color:var(--on-error);" title="Delete" @click.stop="deleteRoute(r)"><i class="bi bi-trash"></i></button>
          </div>
        </article>
      </section>

      <section class="gx-card" v-if="routes.length">
        <div class="gx-section__header">
          <i class="bi bi-exclamation-triangle"></i>
          <span class="gx-section__title">Delete local routes</span>
        </div>
        <div style="display:flex; gap:8px; padding: var(--sp-3); flex-wrap:wrap;">
          <button type="button" class="gx-btn gx-btn--tonal" @click="deleteAllRoutes(false)">Delete Non-Preserved</button>
          <button type="button" class="gx-btn" style="background:var(--error);color:var(--on-error);" @click="deleteAllRoutes(true)">Delete All Including Preserved</button>
        </div>
      </section>

      <div v-if="logsRoute && logsData" class="gx-card" style="margin-top:12px;">
        <div class="gx-section__header">
          <i class="bi bi-file-earmark-arrow-down"></i>
          <span class="gx-section__title">{{ logsData.segments?.length || 0 }} segments · {{ formatBytes(logsData.totalBytes) }}</span>
          <a class="gx-btn gx-btn--tonal" :href="'/api/routes/' + logsRoute.name + '/logs/download'" download>Download all (.tar)</a>
        </div>
        <div v-for="seg in logsData.segments || []" :key="seg.segmentNum" class="gx-row">
          <div class="gx-row__info">
            <span class="gx-row__label">Segment {{ seg.segmentNum }}</span>
            <span class="gx-row__desc">{{ seg.filename }} · {{ formatBytes(seg.bytes) }}</span>
          </div>
          <a class="gx-btn gx-btn--tonal" :href="seg.url" download>Download</a>
        </div>
      </div>

      <transition name="gx-fade">
        <div v-if="playerRoute" class="gx-scrim" @click.self="closePlayer">
          <div class="gx-sheet" style="max-width:640px; width:100%;" role="dialog" aria-label="Route video player">
            <div class="gx-section__header" style="cursor:default;">
              <i class="bi bi-camera-video"></i>
              <span class="gx-section__title">{{ playerRoute.displayName }}</span>
              <button type="button" class="gx-icon-btn" aria-label="Close player" @click="closePlayer"><i class="bi bi-x-lg"></i></button>
            </div>
            <div style="padding: var(--sp-3);">
              <div v-if="playerError" class="gx-empty" style="color: var(--error);">{{ playerError }}</div>
              <div v-else-if="playerLoading" class="gx-loading"><i class="bi bi-hourglass-split"></i> Loading video...</div>
              <template v-else-if="segments.length">
                <video ref="player" class="gx-video" controls muted playsinline preload="metadata"></video>
                <div style="display:flex; gap:8px; padding: var(--sp-3) 0 0; flex-wrap:wrap; align-items:center;">
                  <button type="button" class="gx-btn gx-btn--tonal" :disabled="current<=0" @click="current--; playSegment()"><i class="bi bi-skip-start-fill"></i></button>
                  <select class="gx-field" :value="current" @change="current = Number($event.target.value); playSegment()">
                    <option v-for="(s,i) in segments" :key="i" :value="i">Segment {{ i + 1 }}</option>
                  </select>
                  <button type="button" class="gx-btn gx-btn--tonal" :disabled="current>=segments.length-1" @click="current++; playSegment()"><i class="bi bi-skip-end-fill"></i></button>
                  <button v-for="c in cameras" :key="c" type="button" class="gx-chip" :style="selectedCamera===c?'background:var(--primary);color:var(--on-primary);':''" @click="selectedCamera=c; playSegment()">{{ c }}</button>
                  <button type="button" class="gx-btn" @click="downloadRoute"><i class="bi bi-download"></i> Download</button>
                </div>
              </template>
            </div>
          </div>
        </div>
      </transition>
    </div>
  `,
}
