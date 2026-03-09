import { html, reactive } from "https://esm.sh/@arrow-js/core";
import { Link } from "/assets/components/router.js";
import { upperFirst, hideSidebar } from "/assets/js/utils.js";

const MenuItems = {
  home: [
    { name: "Home", link: "/", icon: "bi-house-fill" },
  ],
  navigation: [
    { name: "Manage Keys", link: "/manage_navigation_keys", icon: "bi-key-fill" },
    { name: "Set Destination", link: "/set_navigation_destination", icon: "bi-globe-americas" },
  ],
  recordings: [
    { name: "Dashcam Routes", link: "/dashcam_routes", icon: "bi-camera-reels" },
    { name: "Screen Recordings", link: "/screen_recordings", icon: "bi-record-circle" },
  ],
  tools: [
    { name: "Toggles", link: "/device_settings", icon: "bi-toggle-on" },
    { name: "Download Speed Limits", link: "/download_speed_limits", icon: "bi-download" },
    { name: "Error Logs", link: "/manage_error_logs", icon: "bi-exclamation-triangle" },
    { name: "Galaxy", link: "/galaxy", icon: "bi-globe2" },
    { name: "Long Maneuvers", link: "/longitudinal_maneuvers", icon: "bi-signpost-split" },
    { name: "Model Manager", link: "/manage_models", icon: "bi-cpu" },
    { name: "Plots", link: "/plots", icon: "bi-graph-up-arrow" },
    { name: "Testing Ground", link: "/testing_ground", icon: "bi-bezier2" },
    { name: "Theme Maker", link: "/theme_maker", icon: "bi-palette-fill" },
    { name: "Tmux Log", link: "/manage_tmux", icon: "bi-terminal" },
    { name: "Backup and Restore", link: "/manage_toggles", icon: "bi-arrow-repeat" },
    { name: "Software", link: "/manage_updates", icon: "bi-arrow-up-circle" },
    { name: "Vehicle Features", link: "/vehicle_features", icon: "bi-car-front" },
  ],
};

const state = reactive({
  activeRoute: ""
});

export function Sidebar() {
  const currentPath = window.location.pathname;
  const matchesPath = (link) => {
    if (link === "/") return currentPath === "/";
    return currentPath === link || currentPath.startsWith(`${link}/`);
  };
  const activeItem = Object.values(MenuItems).flat().find(item => matchesPath(item.link));
  state.activeRoute = activeItem?.name ?? "";


  function navigate(link) {
    state.activeRoute = link.name;
    window.scrollTo(0, 0);
    hideSidebar();

    document.querySelectorAll('.sidebar li').forEach(el => {
      el.classList.remove('active');
    });

    const linkElement = document.querySelector(`.sidebar li a[href="${link.link}"]`);
    if (linkElement) {
      linkElement.parentElement.classList.add('active');
    }
  }

  return html`
    <div id="sidebarUnderlay" class="hidden"></div>
    <div id="sidebar" class="sidebar">
      <div>
        <div class="title">
          <img class="logo" src="/assets/images/main_logo.png" alt="Galaxy logo" />
          <div class="title_text sidebar_header">
            <p>Galaxy</p>
          </div>
        </div>
        <hr />
        ${() => Object.entries(MenuItems).map(([section, links]) => html`
          <div class="sidebar_widget">
            <ul class="menu_section">
              <li>
                <span class="section-title">${upperFirst(section)}</span>
                <ul id="${section}">
                  ${links.map(link => {
    const isActive = state.activeRoute === link.name;
    const classList = [isActive && "active"].filter(Boolean).join(" ");

    const content = html`
                      <div class="menu-item-link">
                        <i class="bi ${link.icon}"></i>
                        <span>${upperFirst(link.name)}</span>
                      </div>
                    `;

    return html`
                      <li class="${classList}">
                        ${Link(link.link, content, () => navigate(link))}
                      </li>
                    `;
  })}
                </ul>
              </li>
            </ul>
          </div>
        `)}
      </div>
    </div>`;
}

function setupMenuButton() {
  const button = document.getElementById("menu_button");
  const sidebar = document.getElementById("sidebar");
  const underlay = document.getElementById("sidebarUnderlay");

  button.addEventListener("click", () => {
    sidebar.classList.toggle("visible");
    underlay.classList.toggle("hidden");
  });

  underlay.addEventListener("click", hideSidebar);
}

document.addEventListener("DOMContentLoaded", setupMenuButton, false);
