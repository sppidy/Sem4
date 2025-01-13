// Retrieve theme settings from localStorage or system preferences
const localStorageTheme = localStorage.getItem("theme");
const systemSettingDark = window.matchMedia("(prefers-color-scheme: dark)");

function calculateSettingAsThemeString() {
  if (localStorageTheme !== null) {
    return localStorageTheme;
  }
  return systemSettingDark.matches ? "dark" : "light";
}

// Set the initial theme
let currentThemeSetting = calculateSettingAsThemeString();
const button = document.querySelector("[data-theme-toggle]");
const htmlElement = document.documentElement; // <html> element
const lightIcon = document.querySelector("#light-icon");
const darkIcon = document.querySelector("#dark-icon");

// Update icons visibility and theme
function updateThemeUI() {
  const isDark = currentThemeSetting === "dark";

  // Update icon visibility
  if (lightIcon && darkIcon) {
    lightIcon.style.display = isDark ? "none" : "block";
    darkIcon.style.display = isDark ? "block" : "none";
  }

  // Update the theme attribute on <html> for CSS
  htmlElement.setAttribute("data-theme", currentThemeSetting);
}

// Apply the initial theme
updateThemeUI();

// Add event listener to toggle theme on button click
if (button) {
  button.addEventListener("click", () => {
    currentThemeSetting = currentThemeSetting === "dark" ? "light" : "dark";

    // Save the theme in localStorage
    localStorage.setItem("theme", currentThemeSetting);

    // Update UI
    updateThemeUI();
  });
}

// Listen for system theme changes
systemSettingDark.addEventListener("change", () => {
  if (localStorage.getItem("theme") === null) {
    currentThemeSetting = systemSettingDark.matches ? "dark" : "light";
    updateThemeUI();
  }
});
