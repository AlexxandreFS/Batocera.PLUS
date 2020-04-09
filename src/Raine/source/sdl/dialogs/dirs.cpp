#include "raine.h"
#include "../gui/menu.h"
#include "../compat.h"
#include "sdl/dialogs/messagebox.h"
#include "sdl/dialogs/fsel.h"

static menu_item_t *menu;

static int do_dir(int sel) {
  char res[256];
  dsel(menu[sel].values_list_label[0],NULL,res,(char*)menu[sel].label);
  strcpy(menu[sel].values_list_label[0], res);
  return 0;
}

static int do_m68kdis(int sel) {
  char *exts[] = { "m68kdis", NULL };
  fsel(dir_cfg.share_path,exts,dir_cfg.m68kdis,"Find m68kdis command");
  strcpy(menu[sel].values_list_label[0], dir_cfg.m68kdis);
  return 0;
}

static int do_dz80(int sel) {
  char *exts[] = { "dz80", NULL };
  fsel(dir_cfg.share_path,exts,dir_cfg.dz80,"Find dz80 command");
  strcpy(menu[sel].values_list_label[0], dir_cfg.dz80);
  return 0;
}

int do_dirs(int sel) {
  int nb = 5;
  int bidon = 1;
  int n;
  menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+2));
  memset(menu,0,sizeof(menu_item_t)*(nb+2));
  menu[0].label = _("Screenshot dir");
  menu[0].values_list_label[0] = dir_cfg.screen_dir;

  menu[1].label = _("Emudx dir");
  menu[1].values_list_label[0] = dir_cfg.emudx_dir;

  menu[2].label = _("Artwork dir");
  menu[2].values_list_label[0] = dir_cfg.artwork_dir;

  menu[3].label = _("m68kdis (console)");
  menu[3].values_list_label[0] = dir_cfg.m68kdis;

  menu[4].label = _("dz80 (console)");
  menu[4].values_list_label[0] = dir_cfg.dz80;
  for (n=0; n< nb; n++) {
    menu[n].value_int = &bidon;
    menu[n].values_list_size = 1;
    menu[n].values_list[0] = bidon;
    menu[n].menu_func = &do_dir;
  }
  menu[3].menu_func = &do_m68kdis;
  menu[4].menu_func = &do_dz80;

  TMenu *mbox = new TMenu(_("Directories"),menu);
  mbox->execute();
  delete mbox;
  free(menu);
  return 0;
}


