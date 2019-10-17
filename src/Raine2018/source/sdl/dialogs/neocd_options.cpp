#include "../gui/menu.h"
#include "deftypes.h"
#include "neocd/neocd.h"
#include "neocd/cdrom.h"
#include "neocd/cdda.h"
#include "sdl/dialogs/fsel.h"
#include "raine.h"
#include "SDL_image.h"
#include "neocd/cache.h"
#include "games.h"
#include "games/neogeo.h"
#include "68000/starhelp.h"
#include "neo_softdips.h"
#include "neo_debug_dips.h"

static char *neo_names[] =
{
    "Europe MVS (Ver. 2)",
    "Europe MVS (Ver. 1)",
    "US MVS (Ver. 2?)",
    "US MVS (Ver. 1)",
    "Asia MVS (Ver. 3)",
    "Japan MVS (Ver. 3)",
    "Japan MVS (Ver. 2)",
    "Japan MVS (Ver. 1)",
    "NEO-MVH MV1C",
    "Japan MVS (J3)",
    "Custom Japanese Hotel",
    "Universe Bios (Hack, Ver. 3.1)",
    "Universe Bios (Hack, Ver. 3.0)",
    "Universe Bios (Hack, Ver. 2.3)",
    "Universe Bios (Hack, Ver. 2.2)",
    "Universe Bios (Hack, Ver. 2.1)",
    "Universe Bios (Hack, Ver. 2.0)",
    "Universe Bios (Hack, Ver. 1.3)",
    "Universe Bios (Hack, Ver. 1.2)",
    "Universe Bios (Hack, Ver. 1.1)",
    "Universe Bios (Hack, Ver. 1.0)",
    // hacks
    "Debug MVS (Hack?)",
    "Asia AES",
    "Japan AES",
    "Irrmaze bios",
};

static int select_bios(int sel);

static int choose_bios(int sel) {
    int size = sizeof(neo_names)/sizeof(char*)+1;
    menu_item_t *menu = (menu_item_t*)malloc(size*sizeof(menu_item_t));
    memset(menu,0,size*sizeof(menu_item_t));
    int n;
    size--;
    int nb_bios = 0;
    for (n=0; n<size; n++) {
	menu[n].label = neo_names[n];
	if (check_bios_presence(n)) {
	    nb_bios++;
	    menu[n].menu_func = &select_bios;
	}
    }
    if (nb_bios) {
	TMenu *load = new TMenu(_("Neo-Geo bios"),menu);
	load->set_sel(neogeo_bios);
	load->execute();
	delete load;
    } else
	MessageBox("Error","Can't find any neogeo bios in your roms.\nSetup your rom directories so that neogeo.zip is loadable","OK");
    free(menu);
    return 0;
}

static char label[100];

static int exit_to(int sel) {
  set_neocd_exit_to(exit_to_code);
  return 0;
}

static int do_update_block(int sel) {
  char fdir[1024];
  snprintf(fdir,1024,"%s",dir_cfg.screen_dir);
  char picture[256];
  *picture = 0;
  char *exts[] = { "block*png", NULL };
  fsel(fdir,exts,picture,"Update block");
  if (picture[strlen(picture)-1] != SLASH[0]) {
    char map[256];
    char *name = strrchr(picture,'/');
    SDL_Surface *img = IMG_Load(picture);
    if (img->format->BitsPerPixel != 8) {
      MessageBox(_("Error"),_("This picture isn't 8bpp"));
      SDL_FreeSurface(img);
      return 0;
    }
    int pitch = img->pitch;
    if (!name) return 0;
    snprintf(map,256,"%ssavedata" SLASH "%s",dir_cfg.exe_path,name);
    strcpy(&map[strlen(map)-3],"map");
    FILE *fmap = fopen(map,"rb");
    if (!fmap) {
      char error[256];
      sprintf(error,"no map %s",map);
      MessageBox(_("Error"),error);
      return 0;
    }
    char last_name[30];
    *last_name = 0;
    FILE *fspr = NULL;
    while (!feof(fmap)) {
      int x,y,tileno,flip;
      char spr[30];
      fscanf(fmap,"%d,%d,%x,%d,%s\n",&x,&y,&tileno,&flip,spr);
      if (!*last_name || strcmp(last_name,spr)) {
	strcpy(last_name,spr);
	char *path = get_override(spr);
	if (fspr) fclose(fspr);
	fspr = fopen(path,"rb+");
	if (!fspr) {
	  char error[128];
	  sprintf(error,"could not open %s",path);
	  MessageBox(_("Error"),path);
	  break;
	}
	printf("%s:\n",spr);
      }
      fseek(fspr,tileno*256,SEEK_SET);
      UINT8 *pixels = ((UINT8*)img->pixels)+y*pitch+x;
      for (y=0; y<16; y++) {
	fwrite(pixels,1,16,fspr);
	pixels += pitch;
      }
    }
    fclose(fmap);
    if (fspr) fclose(fspr);
    SDL_FreeSurface(img);
  }
  return 0;
}

static int select_neocd_bios(int sel) {
    char path[FILENAME_MAX];
    if (*neocd_bios_file) {
	strcpy(path,neocd_bios_file);
	char *s = path;
	char *old;
	do {
	    old = s;
	    s = strstr(s+1,SLASH);
	} while (s);
	if (old) *old = 0;
	else
	    strcpy(path,".");
    } else
	strcpy(path,".");

    char *exts[] = { "bin", "zip", NULL };
    fsel(path,exts,neocd_bios_file,"Find NeoCD bios");
    if (*neocd_bios_file && is_neocd()) {
	if (neocd_bios) {
	    free(neocd_bios);
	    neocd_bios = NULL;
	}
	setup_neocd_bios();
	if (current_game)
	    set_68000_io(0,0xc00000,0xc7ffff, NULL, neocd_bios); // reload !
    }
    select_bios(neogeo_bios);
    return 0;
}

static int dev_mode;

static menu_item_t neocd_menu[] =
{
    { _("Neo-Geo bios"), &choose_bios,},
    { _("NeoCD bios"), &select_neocd_bios, },
    { _("Soft dips"), &do_soft_dips, },
    { _("Debug dips"), &do_debug_dsw, },
    { _("Developper mode"), NULL, &dev_mode, 2, {0, 1}, {_("No"),_("Yes")} },
{ _("Exit to"), &exit_to, &exit_to_code, 4, {0, 2, 5, 6},
  {_("NeoGeo Logo"), _("CD Interface"), _("Test mode"), _("Config mode") } },
  { _("Loading animations speed"), NULL, &cdrom_speed, 8, { 0, 1, 2, 4, 8, 16, 32, 48 },
    { _("Off"), _("CD 1x (150 Kb/s)"), _("2x"), _("4x"), _("8x (default)"), _("16x"), _("32x"), _("48x") } },
  { _("Update neocd sprite block"), &do_update_block },
  { _("Allow speed hacks"), NULL, &allowed_speed_hacks, 2, { 0, 1 }, { _("No"), _("Yes") }},
  { _("Raster effects"), NULL, &disable_irq1, 2, { 0, 1 }, { _("Enabled"), _("Disabled") }},
  { _("Capture mode"), NULL, &capture_new_pictures, 2, { 0, 1 }, { _("Overwrite"), _("New pictures") }},
  { NULL },
};

static int select_bios(int sel) {
    neogeo_bios = sel;
    sprintf(label,_("Neo-Geo bios : %s"),neo_names[neogeo_bios]);
    static char label2[180];
    if (!*neocd_bios_file) {
	sprintf(label2,_("No NeoCD bios"));
    } else {
	char *s = neocd_bios_file;
	char *old;
	do {
	    old = s;
	    s = strstr(s+1,SLASH);
	} while (s);
	if (old == neocd_bios_file) s = old;
	else
	    s = old+1;
	sprintf(label2,_("NeoCD bios : %s"),s);
    }

    neocd_menu[0].label = (const char*)label;
    neocd_menu[1].label = (const char*)label2;
    set_neogeo_bios(sel);
    return 1;
}

class TNeo_options : public TMenu {
  public:
    TNeo_options(char *title, menu_item_t *menu) : TMenu(title,menu)
  {}
    int can_be_displayed(int n) {
      switch(n) {
      case 2:
      case 3:
      case 4: return current_game && current_game->load_game == &load_neocd;
      case 7: return (current_game != NULL); // update block
      }
      return 1;
    }
};

int do_neocd_options(int sel) {
    select_bios(neogeo_bios);
    if (current_game && current_game->load_game == &load_neocd)
	dev_mode = (is_neocd() ? RAM[0x10fe80 ^ 1] : RAM[0xfe80 ^1]);
    TMenu *menu = new TNeo_options(_("NeoCD/Neo-Geo options"), neocd_menu);
    menu->execute();
    delete menu;
    if (current_game && current_game->load_game == &load_neocd) {
	if (is_neocd())
	    RAM[0x10fe80 ^ 1] = dev_mode;
	else
	    RAM[0xfe80 ^1] = dev_mode;
    }
    return 0;
}
