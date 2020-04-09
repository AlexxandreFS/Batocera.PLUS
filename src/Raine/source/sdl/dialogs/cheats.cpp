#include "sdl/gui/menu.h"
#include "arpro.h"
#include "sdl/compat.h"
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "sdl/dialogs/cheats.h"
#ifdef HAS_CONSOLE
#include "sdl/console/scripts.h"
#endif

class TCheatDlg : public TMenu
{
  public:
    TCheatDlg(char *title, menu_item_t *menu) : TMenu(title,menu)
    {}
    void disp_menu(int n,int y,int w,int h) {
      TMenu::disp_menu(n,y,w,h);
      draw_bot_frame();
    }
    void draw_bot_frame() {
      int base = work_area.y+work_area.h;
      boxColor(sdl_screen,0,base,sdl_screen->w,sdl_screen->h,bg_frame);
      char cheat_info[256];
      if (sel < CheatCount) {
	snprintf(cheat_info,256,"Info: %s",CheatList[sel].info);
      } else {
	snprintf(cheat_info,256,"Script");
      }
      font->put_string(HMARGIN,base,cheat_info,fg_frame,bg_frame);
      if (!(sdl_screen->flags & SDL_DOUBLEBUF)) {
	SDL_Rect area;
	area.x = 0; area.y = base; area.w = sdl_screen->w; area.h = sdl_screen->h-base;
	do_update(&area);
      }
    }
    int get_max_bot_frame_dimensions(int &w, int &h) {
      unsigned int max = 0, maxnb = -1;
      for (int n=0; n<CheatCount; n++) {
	if (strlen(CheatList[n].info) > max) {
	  max = strlen(CheatList[n].info);
	  maxnb = n;
	}
      }
      char cheat_info[256];
#ifdef HAS_CONSOLE
      if (CheatCount < 0 && nb_scripts)
	sprintf(cheat_info,"Script");
      else
#endif
	sprintf(cheat_info,"Info: %s",(max > 0 ? CheatList[maxnb].info : ""));
      if (font) font->dimensions(cheat_info,&w,&h);
      return strlen(cheat_info);
    }
};

int adjust_cheat(int sel) {
  int val = CheatList[sel].edit_value;
  if (CheatList[sel].type & CHEAT_EDIT_BASE)
    val--;
  if (CheatList[sel].type & CHEAT_EDIT_BCD)
    val = ((val/10)<<4) + (val%10);
  CheatList[sel].edit_value = val;
  return 0;
}

int do_cheats(int sel) {
  int size = sizeof(menu_item_t)*(CheatCount+
#ifdef HAS_CONSOLE
	nb_scripts+1
#else
	1
#endif
);
  menu_item_t *menu = (menu_item_t*)malloc(size);
  memset(menu,0,size);
  if (!CheatCount
#ifdef HAS_CONSOLE
		  && !nb_scripts
#endif
     ) return 0;

  for (int n=0; n<CheatCount; n++) {
    menu[n].label = CheatList[n].name;
    if (CheatList[n].type & CHEAT_EDITABLE) {
      char text[10];
      int val;
      get_cheat_hex_value(n,text);
      sscanf(text,"%x",&val);
      CheatList[n].old_value = val;
      menu[n].value_int = (int*)&CheatList[n].edit_value;
      if (CheatList[n].type & CHEAT_EDIT_BCD)
	val = ((val >> 4)*10)+(val & 0xf);
      if (CheatList[n].type & CHEAT_EDIT_BASE)
	val++;
      CheatList[n].edit_value = val;
      menu[n].values_list_size = 3;
      menu[n].values_list[0] = CheatList[n].mask; // inf
      menu[n].values_list[1] = CheatList[n].data; // supp
      menu[n].values_list[2] = 1;
    } else {
      menu[n].value_int = (int*)&CheatList[n].active;
      menu[n].values_list_size = 2;
      menu[n].values_list[0] = 0;
      menu[n].values_list[1] = 1;
      menu[n].values_list_label[0] = _("Off");
      menu[n].values_list_label[1] = _("On");
    }
  }
#ifdef HAS_CONSOLE
  add_scripts(&menu[CheatCount]);
#endif
  TCheatDlg *cheats = new TCheatDlg(_("Cheats"),menu);
  cheats->execute();
  delete cheats;
  for (int n=0; n<CheatCount; n++) {
    if (CheatList[n].type & CHEAT_EDITABLE) {
      adjust_cheat(n);
      if (CheatList[n].edit_value != CheatList[n].old_value) {
	CheatList[n].active = 1;
      } else
        CheatList[n].active = 0;
    }
  }
  free(menu);
  return 0;
}

