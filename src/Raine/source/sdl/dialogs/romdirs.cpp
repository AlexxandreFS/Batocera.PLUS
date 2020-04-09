#include "raine.h"
#include "../gui/menu.h"
#include "../compat.h"
#include "sdl/dialogs/messagebox.h"
#include "sdl/dialogs/fsel.h"
#include "romdir.h"

static int end;

static int do_dir(int sel) {
  sel--;
  int ret = MessageBox(dir_cfg.rom_dir[sel],_("Directory options"),_("Change dir|Remove dir"));
  if (ret == 1) {
    char res[256];
    dsel(dir_cfg.rom_dir[sel],NULL,res,"Rom dir");
    free(dir_cfg.rom_dir[sel]);
    dir_cfg.rom_dir[sel] = strdup(res);
  } else if (ret == 2) // remove
    remove_rom_dir(sel);
  end = 0;
  return 1;
}

static int add_dir(int sel) {
  char res[256];
  if (dir_cfg.rom_dir[0])
    strcpy(res,dir_cfg.rom_dir[0]);
  else
    res[0] = 0;
  dsel(res,NULL,res,"Rom dir");
  add_rom_dir(res);
  end = 0;
  return 1;
}

int do_romdir(int sel) {
  int nb;
  menu_item_t *menu;
  do {
    end = 1;
    for (nb=0; dir_cfg.rom_dir[nb]; nb++);
    menu = (menu_item_t*)malloc(sizeof(menu_item_t)*(nb+2));
    memset(menu,0,sizeof(menu_item_t)*(nb+2));
    for (int n=0; n<nb; n++) {
      menu[n+1].label = dir_cfg.rom_dir[n];
      menu[n+1].menu_func = &do_dir;
    }
    menu[0].label = _("Add rom dir...");
    menu[0].menu_func = &add_dir;

    TMenu *mbox = new TMenu(_("rom dirs"),menu);
    mbox->execute();
    delete mbox;
  } while (!end);
  free(menu);
  return 0;
}
