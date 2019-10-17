#include "sdl/gui/menu.h"
#include "sdl/compat.h"
#include "sdl/gui/tfont.h"
#include "sdl/dialogs/colors.h"
#include "str_opaque.h"
#include "control.h"
#include "control_internal.h"

extern int do_dirs(int sel); // dirs.cpp
static int lang_int;
extern "C" void init_lang(); // raine.c

static int set_lang(int sel) {
    char *locale;
    switch(lang_int) {
    case 1: locale = "fr"; break;
    case 2: locale = "es"; break;
    case 3: locale = "pt"; break;
    default: locale = "C"; break;
    }
    strcpy(language,locale);
    init_lang();
    return 0;
}

static menu_item_t gui_menu[14] =
{
{  _("Language"), &set_lang, &lang_int, 4, {0, 1, 2, 3 }, { "English", "French","Spanish", "Portuguese"} },
};

extern int add_gui_options(menu_item_t *menu);
extern int add_fonts_gui_options(menu_item_t *menu);
TMenu *gui_options;

static menu_item_t color_menu[] =
{
{ _("Colors..."), &do_colors, },
{ _("No HUD messages"), NULL, &silent_hud, 2, {0, 1}, { _("No"), _("Yes") } },
{ _("Opaque HUD"), NULL, &opaque_hud, 2, { 0, 1 }, { _("No"), _("Yes") } },
{ _("Pause when focus lost"), NULL, &pause_on_focus, 2, { 0, 1 }, { _("No"), _("Yes") }}
};

int do_gui_options(int sel) {
  int nb = 1;
  if (strstr(language,"fr")) lang_int = 1;
  else if (strstr(language,"es")) lang_int = 2;
  else if (strstr(language,"pt")) lang_int = 3;
  else lang_int = 0;
  char old_lang[3];
  strcpy(old_lang,language);

  nb += add_fonts_gui_options(&gui_menu[nb]);
  nb += add_gui_options(&gui_menu[nb]);
  nb += add_menu_options(&gui_menu[nb]);
  gui_menu[nb++] = color_menu[0];
  gui_menu[nb++] = color_menu[1];
  gui_menu[nb++] = color_menu[2];
  gui_menu[nb].label = _("Directories...");
  gui_menu[nb].menu_func = &do_dirs;
  gui_options = new TMenu(_("Options"), gui_menu);
  gui_options->execute();
  delete gui_options;

  if (strcmp(language,old_lang)) {
      return 1; // redraw main menu if locale changes
  }
  return 0;
}

