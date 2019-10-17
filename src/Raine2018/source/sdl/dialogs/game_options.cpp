#include "raine.h"
#include "profile.h" // fps
#include "games.h"
#include "savegame.h"
#include "../gui/menu.h"
#include "emumain.h"
#include <sys/types.h>
#include <dirent.h>
#include <zlib.h>
#include "files.h"
#include <time.h>
#include <sys/stat.h>
#include "dialogs/messagebox.h"
#include "ingame.h"
#include "sprite_viewer.h"
#include "translator.h"
#include "conf-sound.h"
#if HAS_NEO
#include "neocd/cache.h"
#endif
#include <math.h>

// #include <SDL/SDL_image.h>

#if 0
extern "C" {
  int get_saved_picture(gzFile fin,char **s); // defined in savegame.c
}
#endif

static int exit_options;

static int my_reset(int sel) {
  reset_game_hardware();
  exit_options = 1;
  return 1;
}

typedef struct {
  int num;
  char date[30];
  SDL_Surface *picture;
} saves_t;

static int allocated = 0, used = 0;
static saves_t *saves = NULL;

static int load_savegame(int sel) {
  SaveSlot = saves[sel].num;
  GameLoad();
  exit_options = 1;
  return 1;
}

static int saveit(int sel) {
  SaveSlot = saves[sel].num;
  GameSave();
  exit_options = 1;
  return 1;
}

static int sort_saves(const void *a, const void *b) {
  return ((saves_t *)a)->num - ((saves_t *)b)->num;
}

static menu_item_t *get_savegames(int for_saving) {
  char fdir[1024];
  snprintf(fdir,1024,"%ssavegame",dir_cfg.exe_path);
  DIR *dir = opendir(fdir);

  allocated = used = 0;

  /* The stupid incompatible windows hasn't got any glob function, so I must
   * use opendir here... Shhhhh ! */

  if (dir) {
    struct dirent *entry;
    int len = strlen(current_game->main_name);
    int n;
    // 1st look for height
    while ((entry = readdir(dir))) {
      if (!strnicmp(entry->d_name,current_game->main_name,len)) {
	char fpath[1024];
	int version = 0;
	sprintf(fpath,"%s%s%s",fdir,SLASH,entry->d_name);
	gzFile fin = gzopen(fpath,"rb");
	if (fin) {
	  version = mgetl(fin);
	}
	if (version == SAVE_FILE_TYPE_2 || version == SAVE_FILE_TYPE_1) {
	  struct stat buf;
	  char *s = entry->d_name+len+3;
	  if (allocated == used) {
	    allocated += 10;
	    saves = (saves_t*)realloc(saves,sizeof(saves_t)*allocated);
	  }
	  saves[used].num = atoi(s);
	  stat(fpath,&buf);
	  int ret = strftime(saves[used].date,sizeof(saves[used].date),"%x %X",localtime((const time_t*)&buf.st_mtime));
	  if (!ret) {
	    printf("couldn't store date\n");
	    exit(1);
	  }
#if 0
	  int taille = get_saved_picture(fin,&s);
	  if (s) {
	    SDL_RWops *rw = SDL_RWFromMem(s, taille);
	    saves[used].picture = IMG_Load_RW(rw,1);
	    if (saves[used].picture)
	      free(s);
	  } else
#endif
	    saves[used].picture = NULL;
	  used++;
	}
	gzclose(fin);
      }
    }
    closedir(dir);
    qsort(saves,used,sizeof(saves_t),&sort_saves);
    int size = sizeof(menu_item_t)*(used+(for_saving ? 2 : 1));
    menu_item_t *menu = (menu_item_t*)malloc(size);
    memset(menu,0,size);
    for (n=0; n<used; n++) {
      char buff[80];
      sprintf(buff,"%d - %s",saves[n].num,saves[n].date);
      menu[n].label = strdup(buff);
      menu[n].label = strdup(buff);
      menu[n].menu_func = (for_saving ? &saveit : &load_savegame);
#if 0
      static int dummy = 0;
      menu[n].values_list_size = 1;
      menu[n].value_int = &dummy;
      menu[n].values_list_label[0] = _("X");
#endif
    }
    if (for_saving) {
      // find free number for the save
      int free = 0, found = 0;
      char buff[80];
      if (allocated == used) {
	allocated += 10;
	saves = (saves_t*)realloc(saves,sizeof(saves_t)*allocated);
      }
      for (; !found; free++) {
	for (n=0; n<used; n++) {
	  if (saves[n].num == free)
	    break;
	}
	if (n == used)
	  break;
      }
      saves[used].num = free;
      sprintf(buff,_("%d - Free savegame slot"),free);
      menu[used].label = strdup(buff);
      menu[used].menu_func = &saveit;
    }
    return menu;
  }
  return NULL;
}

static void free_saves(menu_item_t *menu) {
  int n;
  if (saves) {
    for (n=0; n<used; n++) {
      if (saves[n].picture)
	SDL_FreeSurface(saves[n].picture);
      free((void*)menu[n].label);
    }
    free(saves);
    free(menu);
    saves = NULL;
  }
}

static int my_load(int sel) {
  exit_options = 0;
  menu_item_t *menu = get_savegames(0);
  if (!used) {
    MessageBox(_("Error"),_("No savegames loadable for this game"));
    return 0;
  }
  TMenu *load = new TMenu(_("Load game"),menu);
  load->execute();
  delete load;
  free_saves(menu);
  return exit_options;
}

static int my_save(int sel) {
  exit_options = 0;
  menu_item_t *menu = get_savegames(1);
  TMenu *load = new TMenu(_("Save game"),menu);
  load->execute();
  delete load;
  free_saves(menu);
  return exit_options;
}

static int graphical_layers(int sel) {
  int size = sizeof(menu_item_t)*(layer_info_count+1);
  menu_item_t *menu = (menu_item_t*)malloc(size);
  memset(menu,0,size);

  int n;
  for (n=0; n<layer_info_count; n++) {
    menu[n].label = layer_info_list[n].name;
    menu[n].value_int = &layer_info_list[n].enabled;
    menu[n].values_list_size = 2;
    menu[n].values_list[0] = 0;
    menu[n].values_list[1] = 1;
    menu[n].values_list_label[0] = _("Off");
    menu[n].values_list_label[1] = _("On");
  }
  TMenu *layers = new TMenu(_("Layers"),menu);
  layers->execute();
  delete layers;
  free(menu);
  return 0;
}

extern int cpu_fps; // emumain.c

static int ifps;

static int reset_fps(int sel) {
    fps = default_fps;
    return 0;
}

static menu_item_t game_options[] =
{
  { _("Reset game hardware"), &my_reset },
  { _("Load game"), &my_load },
  { _("Save game"), &my_save },
  { _("Graphical layers..."), &graphical_layers },
  { _("Sprite viewer"), &sprite_viewer },
#if HAS_NEO
  { _("Edit screen"), &do_screen },
  { _("Edit msg"), &do_msg },
#endif
  { _("CPU frame skip (1=no skip) "), NULL, &cpu_fps, 3, { 1, 16, 1 } },
  { _("FPS"), NULL, &ifps, ITEM_FLOATEDIT, { 10,0,180 }, { "", (char*)&fps, "1", "200" } },
  { _("Reset fps to driver's default value"), &reset_fps },
  { _("FPS counter"), NULL, (int*)&raine_cfg.show_fps_mode, 5, { 0, 1, 2, 3, 4 },
    { _("Off"), _("Immediate FPS"), _("Average FPS"), _("Profiler"), _("Rdtsc Cycles") } },
  { NULL }
};

class TGame_options : public TMenu {
  public:
    TGame_options(char *title, menu_item_t *menu) : TMenu(title,menu)
  {}
    int can_be_displayed(int n) {
      switch(n) {
	case 3: // graphical layers
	  return layer_info_count;
#if HAS_NEO
	case 5: // screens
	  if (is_current_game("ssrpg")) {
	      char name[30];
	      name[0] = 0;
	      UINT32 len,offset;
	      return find_spec("f_bg",name,&offset,&len);
	  }
	  return 0;
	case 6: // msg
	  return current_game && is_current_game("ssrpg");
#endif
      }
      return 1;
    }
};

int do_game_options(int sel) {
    if (fabs(default_fps) < 1e-4)
	default_fps = fps;
    TGame_options *menu = new TGame_options(_("Game options"),game_options);
    menu->execute();
    delete menu;
    return exit_options;
}

