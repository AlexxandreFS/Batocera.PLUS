// Desativa a verificação de navegador padrão.
user_pref("browser.shell.checkDefaultBrowser", false);

// Desativa as atualizaçõesautomáticas.
user_pref("app.update.auto", false);
user_pref("app.update.checkInstallTime", false);
user_pref("browser.search.update", false);

// Define a pasta de download padrão.
user_pref("browser.download.dir", "/userdata/downloads");
user_pref("browser.download.folderList", 2);

// Ativa a restauração de abas abertas na ultima execução do firefox.
user_pref("browser.startup.page", 3);

// Ativa a execução de conteúdo em flash offline.
user_pref("plugin.state.flash", 2);
user_pref("plugins.http_https_only", false);

// Habilita conteúdo DRM.
user_pref("media.eme.enabled", true);

// Habilita a rolagem da página com o botão do meio mouse.
user_pref("general.autoScroll", true);

// Ativa o tema personalizado.
user_pref("extensions.activeThemeID", "{5ab03bdd-3d91-4c73-801e-607ca27458d0}");
user_pref("browser.theme.toolbar-theme", 0);

// Customização dos itens na tela do navegador.
user_pref("browser.search.widget.inNavBar", true);
user_pref("browser.download.autohideButton", false);
user_pref("browser.uiCustomization.state", "{\"placements\":{\"widget-overflow-fixed-list\":[],\"nav-bar\":[\"back-button\",\"forward-button\",\"stop-reload-button\",\"home-button\",\"urlbar-container\",\"search-container\",\"downloads-button\",\"bookmarks-menu-button\",\"sidebar-button\",\"library-button\"],\"toolbar-menubar\":[\"menubar-items\"],\"TabsToolbar\":[\"tabbrowser-tabs\",\"new-tab-button\",\"customizableui-special-spring6\",\"zoom-controls\",\"fullscreen-button\",\"alltabs-button\"],\"PersonalToolbar\":[\"personal-bookmarks\"]},\"seen\":[\"developer-button\"],\"dirtyAreaCache\":[\"nav-bar\",\"toolbar-menubar\",\"TabsToolbar\",\"PersonalToolbar\",\"widget-overflow-fixed-list\"],\"currentVersion\":16,\"newElementCount\":36}");

// Remove a página incial da mozzila.
user_pref("browser.startup.homepage_override.mstone", "ignore");
user_pref("datareporting.policy.dataSubmissionPolicyNotifiedTime", "1568476951612");
user_pref("datareporting.policy.dataSubmissionPolicyAcceptedVersion", 2);
