/* WARNING : don't use this on a double buffered screen !
I tried to make it work in double buffer mode at first, before realizing it
creates really too many problems, and it's much easier to simply disable double
buffer before calling the gui */

/* Very basic menu system, inspired from neocdpsp interface
 * In fact it has become the core of the new gui system for raine.
 *
 * The idea behind this one is to have something as easy to program as
 * possible (1st goal), usable with any peripheral (2nd), and also nice if
 * possible (3rd !) ;-)
 *
 * To achieve this easy programmation, I took some ideas from the guis on psp:
 * a basic "menu" on screen, you can move to any option, pressing a button
 * execute it, and moving right or left changes values in a list of values
 * if there is one. It's nice, easy to use, and easy to program. All this stuff
 * is handled by a very basic struct :
 *
 * typedef struct {
 *                const char *label;
 *                int (*menu_func)(int);
 *                int     *value_int;
 *                int     values_list_size;
 *                int values_list[16];
 *                char* values_list_label[16];
 * } menu_item_t;
 *
 * A menu is just a list of these structs, ended by an entry with label=NULL
 * To have something static, just pass a label and menu_func=value_int=NULL
 * To have a simple command, just pass a function in menu_func.
 * And to have list of values where to choose from, just pass an int and
 * some lists. Something to notice about these lists : contrary to what
 * allegro did, here you don't have to worry about list indexes. For example
 * if you want to choose the audio frequency you would put :
 * { "Audio frequency", NULL, &audio_sample_rate, 3, {11025,22050,44100}, NULL}
 * If you pass a menu_func != NULL with a value_int != NULL, then menu_func
 * is called everytime you change the value of value_int in the list.
 *
 * The end result is something which looks a little like the mame's menu system
 * but with quite some difference :
 * 1) it's nicer : transparency effects, true type support, bitmap handling,
 * flashing background for the selected option...
 * 2) it can be controlled with any device (mouse, keyboard, joystick...).
 * 3) it pauses the game when you call the gui ! ;-)
 *
 * Another advantage is that you don't have to care about coordinates or fonts
 * sizes. It's configured to adapt to anything you pass.
 *
 * The original psp implementation was in pure C. This one is in C++ to add
 * a few features more easily, like bitmap handling, and make the whole thing
 * even easier to use. This file contains the gory details, you shouldn't
 * have to look into it just to use the gui !
 *
 * The objects hierarchy :
 *
 * TMenu is the default container class. It displays menu_item entries one
 * under the other, with a frame (a status bar at the bottom + a title bar at
 * the top).
 *
 * TDialog is the same thing without frame. The goal of TDialog is to be able
 * to display a dialog on top of a menu (or another dialog) which is already on
 * scren.
 *
 * TMenuMultiCol displays a multi column dialog based on a double indexed array
 * of strings (char *cols[][]). It might have been possible to do it using
 * value_list_label from the menu_item_t struct, but at the time I wrote this
 * it looked like the easiest solution. Since it works well, I won't try to
 * rewrite it any time soon.
 *
 * TBitmap_menu is the way I found to have a bitmap in a dialog (as a header
 * here). This is the dialog which showed the most the need for some
 * extensions.
 *
 * Extensions : a pc being more complex than a psp, I had quickly a need for
 * extensions, that is widgets more complex than simple strings in dialogs.
 * But at the same time, I wanted to keep the simplicity of menu_item_t. This
 * is why I created the widget classes (see widget.cpp/widget.h for details) to
 * handle the widgets, as an array in TMenu (child).
 *
 * In menu_item_t an extension is identified by values_list_size < 0 in
 * menu_item_t (which should never happen normally with strings).
 * Depending on the value of this field, different types of widgets are created
 * to fill the child array and handle the menu_item entry.
 * The list of extensions is given and commented in menuitem.h
 */

#include "raine.h"
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "video/palette.h"
#include "version.h"
#include "games.h"
#include "menu.h"
#include "tfont.h"
#include "widget.h"
#include "tslider.h"
#include "tedit.h"
#include "sdl/SDL_gfx/SDL_framerate.h"
#include "sdl/SDL_gfx/SDL_rotozoom.h"
#include <SDL_image.h>
#include "blit.h"
#include "sdl/display_sdl.h"
#include "sdl/blit_sdl.h"
#include "display.h" // ScreenChange
#include "sdl/dialogs/gui_options.h"
#include "tlift.h"
#include "control.h"
#include "tbitmap.h"
#include "sasound.h"
#include "neocd/neocd.h"
#include "newmem.h" // GetMemoryPoolSize

static int return_mandatory = 0, use_transparency = 1;
int emulate_mouse_cursor = 0,keep_vga,gui_level;
static int mouse_erased,unicode;

extern int repeat_interval, repeat_delay; // in gui.cpp

void disp_cursor(SDL_Surface *s,int x,int y, int w, int h) {
  for (int my=1+y; my<y+h-1; my++) {
    UINT8 *pixel = ((UINT8*)s->pixels)+my*s->pitch+x*s->format->BytesPerPixel;
    for (int x=0; x<w*s->format->BytesPerPixel; x++) {
      // if (x % 3 == 0) continue;
      pixel[x] ^= 255;
    }
  }
  if (s == sdl_screen)
    SDL_UpdateRect(sdl_screen, x,y,w,h);
}

static int toggle_mouse(int sel) {
  if (emulate_mouse_cursor) {
    SDL_ShowCursor(SDL_DISABLE);
    mouse_erased = 1;
  }
  gui_options->draw();
  if (!(sdl_screen->flags & SDL_DOUBLEBUF) && !emulate_mouse_cursor)
    SDL_ShowCursor(SDL_ENABLE);
  return 0;
}

menu_item_t menu_options[] =
{
  { _("Return mandatory"), NULL, &return_mandatory, 2, { 0, 1 }, { _("No"), _("Yes") }},
  { _("GUI transparency"), NULL, &use_transparency, 2, { 0, 1 }, { _("No"), _("Yes") }},
  { _("Use custom mouse cursor"), &toggle_mouse, &emulate_mouse_cursor, 2,
    { 0,1 }, { _("No"), _("Yes") } },
  { _("Minimum GUI resolution = VGA"), NULL,&keep_vga, 2, { 0,1 }, { _("No"),_("Yes") }},
};

int fg_color, bg_color,fgframe_color,bgframe_color,cslider_border,
  cslider_bar,cslider_lift,bg_dialog_bar;

void save_menu_config() {
  raine_set_config_int("GUI", "return_mandatory", return_mandatory);
  raine_set_config_int("GUI", "use_transparency", use_transparency);

  raine_set_config_32bit_hex("GUI", "fg_color", fg_color);
  raine_set_config_32bit_hex("GUI", "bg_color", bg_color);
  raine_set_config_32bit_hex("GUI", "fgframe_color", fgframe_color);
  raine_set_config_32bit_hex("GUI", "bgframe_color", bgframe_color);

  raine_set_config_32bit_hex("GUI", "slider_border", cslider_border);
  raine_set_config_32bit_hex("GUI", "slider_bar", cslider_bar);
  raine_set_config_32bit_hex("GUI", "slider_lift", cslider_lift);

  raine_set_config_32bit_hex("GUI", "bg_dialog_bar", bg_dialog_bar);
  raine_set_config_int("GUI", "keep_vga", keep_vga);
}

void read_menu_config() {
  return_mandatory = raine_get_config_int("GUI", "return_mandatory", 0);
  use_transparency = raine_get_config_int("GUI", "use_transparency", 1);
  fg_color = raine_get_config_hex("GUI", "fg_color", mymakecol(255,255,255));
  bg_color = raine_get_config_hex("GUI", "bg_color", makecol_alpha(0x11,0x07,0x78,128));
  fgframe_color = raine_get_config_hex("GUI", "fgframe_color", mymakecol(255,255,255));
  bgframe_color = raine_get_config_hex("GUI", "bgframe_color", mymakecol(0,0,128));
  cslider_border = raine_get_config_hex("GUI", "slider_border", mymakecol(0,0,0));
  cslider_bar = raine_get_config_hex("GUI", "slider_bar", mymakecol(0xc0,0xc0,0xc0));
  cslider_lift = raine_get_config_hex("GUI", "slider_lift", mymakecol(0xff,0xff,0xff));
  bg_dialog_bar = raine_get_config_hex("GUI", "bg_dialog_bar", mymakecol(0,0,0));
  keep_vga = raine_get_config_int("GUI","keep_vga",1);
}

int add_menu_options(menu_item_t *menu) {
  menu[0] = menu_options[0];
  menu[1] = menu_options[1];
  menu[2] = menu_options[2];
  menu[3] = menu_options[3];
  return 4;
}

static SDL_Surface *cursor = NULL;

void setup_mouse_cursor(SDL_Surface *mycursor) {
  cursor = mycursor;
}

void sort_menu(menu_item_t *menu) {
  int n,ref,x;
  if (!menu)
    return;
  for (n=0; menu[n].label; n++) {
    if (menu[n].value_int && menu[n].values_list_size > 0 && menu[n].values_list_label[0]) {
      for (ref=0; ref<menu[n].values_list_size-1; ref++) {
	for (x=ref+1; x<menu[n].values_list_size; x++) {
	  if (strcmp(menu[n].values_list_label[ref],
	      menu[n].values_list_label[x]) > 0) {
	    char *s = menu[n].values_list_label[ref];
	    int nb = menu[n].values_list[ref];
	    menu[n].values_list_label[ref] = menu[n].values_list_label[x];
	    menu[n].values_list[ref] = menu[n].values_list[x];
	    menu[n].values_list_label[x] = s;
	    menu[n].values_list[x] = nb;
	  }
	}
      }
    }
  }
}

static TMenu *caller;

TMenu::TMenu(char *my_title, menu_item_t *my_menu, char *myfont, int myfg, int mybg, int myfg_frame, int mybg_frame,int to_translate) {
    header = NULL;
    h_child = NULL;
    focus = 0;
  top = 0;
  sel = -1; // compute first selection later (compute_nb_items)
  child = NULL;
  title = my_title;
  menu = my_menu;
  translated = to_translate && menu;

  if (translated) {
      /* Translation problem :
       * when using _() in the menu_item_t definition, it's called before the
       * gettext environment is initialized and so it does nothing. The reason
       * to use it is to mark the text for translation in the .po files. The
       * solution is to translate everything here.
       * But now there is the problem of dialogs which allocate dynamically
       * their entries, even if they are a minority. To avoid to mess things
       * up I use a copy of the menu_item_t passed. The downside is that it
       * makes dynamic dialogs harder to handle, explicit calls are needed to
       * update the strings in the dialogs in this case.
       * The copy of the menu passed has another advantage : it allows to
       * change the translated language without restarting since the original
       * text is preserved... */
      /* Now this thing is really starting to become bothersome, but for now
       * I see no way to get back to the easy dyanmic dialogs handling while
       * keeping the translations ! */
      int nb = 0;
      while (menu->label) {
	  nb++;
	  menu++;
      }
      int sz = sizeof(menu_item_t)*(nb+1);
      menu = (menu_item_t *)malloc(sz);
      memcpy(menu,my_menu,sz);
      my_menu = menu;
      while (menu && menu->label) {
	  if (*menu->label) {
	      menu->label = gettext(menu->label);
	      for (int n=0; n<menu->values_list_size && menu->values_list_label[n]; n++)
		  menu->values_list_label[n] = gettext(menu->values_list_label[n]);
	  }
	  menu++;
      }
      menu = my_menu;
  }

  fg_layer = bg_layer = NULL;
  font = NULL;
  menu_disp = NULL;
  parent = caller;
  cycle_up = cycle_down = 1;

  if (myfg == -1)
    fg = fg_color;
  else
    fg = myfg;
  if (mybg == -1)
    bg = bg_color;
  else
    bg = mybg;
  if (myfg_frame == -1)
    fg_frame = fgframe_color;
  else
    fg_frame = myfg_frame;
  if (mybg_frame == -1) {
    bg_frame = bgframe_color;
  } else
    bg_frame = mybg_frame;
  font_name = "Vera.ttf";
  lift = NULL;
  keybuf[0] = 0;
  SDL_GetMouseState(&mousex[0],&mousey[0]);
  mousex[1] = mousex[0]; mousey[1] = mousey[0];
  flip_page = 0;
  phase_repeat = jmoved = 0;
  work_area.h = 0;
  rows = 0;
  work_area.x = 0;
  work_area.w = sdl_screen->w;
  use_transparency = ::use_transparency;
}

void TMenu::update_label(int nb, char *str,int (*menu_func)(int)) {
    menu[nb].label = str;
    if (menu_func) menu[nb].menu_func = menu_func;
}

void TMenu::update_list_label(int nb, int index, char *str) {
    menu[nb].values_list_label[index] = str;
}

TMenu::~TMenu() {
    if (translated)
	free(menu);
  if (child) {
    for (int n=0; n<nb_items; n++)
      delete child[n];
    free(child);
    child = NULL;
  }
  if (h_child) {
      for (int n=0; header[n].label; n++)
	  free(h_child[n]);
      free(h_child);
      h_child = NULL;
  }

  delete font;
  if (menu_disp)
    free(menu_disp);
  if (lift)
    delete lift;
  if (bg_layer) {
    SDL_FreeSurface(bg_layer);
  }
  if (fg_layer)
    SDL_FreeSurface(fg_layer);
}

int TMenu::can_be_displayed(int n) {
  // can hide some menu entries at will. By default, show everything
  return 1;
}

int TMenu::can_be_selected(int n) {
  // same thing to say if an item can be selected
  // by default everything which can be displayed can also be selected
  return can_be_displayed(n) && child[n]->can_be_selected();
}

void TMenu::create_child(int n) {
  if (!menu[n].value_int)
    child[n] = new TStatic(&menu[n]);
  else if (menu[n].values_list_size > 0 && menu[n].value_int) {
    child[n] = new TOptions(&menu[n]);
  } else if (menu[n].values_list_size == ITEM_PROGRESS_BAR)
    child[n] = new TProgressBar(&menu[n]);
  else if (menu[n].values_list_size == ITEM_SLIDER)
    child[n] = new TSlider(&menu[n]);
  else if (menu[n].values_list_size == ITEM_EDIT)
    child[n] = new TEdit(&menu[n]);
  else if (menu[n].values_list_size == ITEM_TBITMAP)
    child[n] = new TBitmap(&menu[n]);
  else if (menu[n].values_list_size == ITEM_FLOATEDIT)
    child[n] = new TFloatEdit(&menu[n]);
  else if (menu[n].values_list_size == ITEM_HEXEDIT)
    child[n] = new THexEdit(&menu[n]);
  else if (menu[n].values_list_size == ITEM_INTEDIT)
    child[n] = new TIntEdit(&menu[n]);

  else {
    printf("unknown extension %d\n",menu[n].values_list_size);
    exit(1);
  }
}

void TMenu::compute_nb_items() {
  if (child) {
    for (int n=0; n<nb_items; n++)
      if (child[n]) delete child[n];
    free(child);
    child = NULL;
  }
  nb_items = 0;
  nb_disp_items = 0;
  if (menu)  {
    while (menu[nb_items].label) {
      if (can_be_displayed(nb_items)) {
	nb_disp_items++;
      }
      nb_items++;
    }
    if (menu_disp)
      free(menu_disp);
    if (nb_disp_items)
	menu_disp = (int*)malloc(sizeof(int)*(nb_disp_items));
    else
	menu_disp = NULL;
    child = (TStatic **)malloc(sizeof(TStatic*)*nb_items);
    int n=0;
    nb_disp_items = 0;
    while (menu[n].label) {
      create_child(n);

      if (can_be_displayed(n)) {
	menu_disp[nb_disp_items++] = n;
	if (sel < 0 && can_be_selected(n))
	  sel = n;
      }
      n++;
    }

    if (header) {
	TStatic **old_child = child;
	menu_item_t *old_menu = menu;
	int nb;
	for (nb=0; header[nb].label; nb++);
	h_child = child = (TStatic **)malloc(sizeof(TStatic*)*nb);
	menu = header;
	n = 0;
	while (menu[n].label) {
	    create_child(n);
	    n++;
	}
	menu = old_menu;
	child = old_child;
	find_new_sel();
    }

    if (sel >= nb_items) sel = 0;
  }
}

int TMenu::can_exit() {
  for (int n=0; n<nb_items; n++) {
    if (!child[n]->can_exit()) {
      if (can_be_selected(n)) {
	sel = n;
	reset_top();
      }
      return 0;
    }
  }
  return 1; // nobody refuses the exit
}

char* TMenu::get_emuname() {
  return EMUNAME " " VERSION;
}

void TMenu::draw_top_frame() {
  int w_title,h_title;
  font->dimensions(title,&w_title,&h_title);
  boxColor(sdl_screen,0,0,sdl_screen->w,h_title-1,bg_frame);
  font->put_string(HMARGIN,0,get_emuname(),fg_frame,bg_frame);
  int is_utf = test_utf(title);
  font->set_utf(is_utf);
  font->put_string(sdl_screen->w-w_title,0,title,fg_frame,bg_frame);
}
char* TMenu::get_bot_frame_text() {
  int size = GetMemoryPoolSize()/1024; // Minimum Kb
  static char game[100];
  snprintf(game,100,"%s",(current_game ? current_game->long_name :_("No game loaded")));
  if (current_game) {
      snprintf(&game[strlen(game)], 100-strlen(game),
	      " (%s)",current_game->main_name);
      if (size < 1024)
	  snprintf(&game[strlen(game)],100-strlen(game),
		  " (%d Kb)",size);
      else
	  snprintf(&game[strlen(game)], 100-strlen(game),
		  " (%d Mb)",size/1024);
  }
  game[99] = 0;
  return game;
}

int TMenu::get_max_bot_frame_dimensions(int &w, int &h) {
  char *game = get_bot_frame_text();
  if (font) font->dimensions(game,&w,&h);
  return strlen(game);
}

void TMenu::draw_bot_frame() {
  int base = work_area.y+work_area.h;
  char *game = get_bot_frame_text();
  boxColor(sdl_screen,0,base,sdl_screen->w,sdl_screen->h,bg_frame);
  font->put_string(HMARGIN,base,game,fg_frame,bg_frame);
}

void TMenu::draw_frame(SDL_Rect *r) {
  int w_game, h_game;
  int w_title,h_title;
  int len_top, len_bot;
  char top_string[512];
  TFont *old_font;
  len_bot = get_max_bot_frame_dimensions(w_game,h_game);

  sprintf(top_string,"%s %s",get_emuname(),title);
  len_top = strlen(top_string);

  old_font = font;
  font = NULL;
  /* if (!font) */ setup_font((len_top > len_bot ? len_top : len_bot));
  if (old_font && old_font->get_font_width() == font->get_font_width() &&
      old_font->get_font_height() == font->get_font_height()) {
    delete font;
    font = old_font;
  } else {
      if (old_font)
	  delete old_font;
    if (fg_layer) {
      /* In case the font just changed, then we must recreate fg_layer
       * Notice that this thing here is a particularity in windows
       * in linux when we arrive in the message loop, we start by normal events
       * (keyboard, mouse, timers...). In windows, 1 of the 1st events received
       * is an expose event. The consequence is a redraw which arrives here.
       * Since the 1st calculation of the font is an approximation, the 2nd
       * one is almost sure to be different here, and so we must absolutely
       * redraw fg_layer (otherwise the expose event would just blit the old
       * fg_layer, and then any mouse move would use the new font size over
       * a blit using the old font size). */
      setup_fg_layer();
      redraw_fg_layer();
    }
  }

  font->dimensions(title,&w_title,&h_title);
  len_bot = get_max_bot_frame_dimensions(w_game,h_game);

  int base = sdl_screen->h-h_game;

  work_area.y = h_title;
  work_area.h = (base - (h_title));

  if (!r || r->y < h_title) {
    draw_top_frame();
  }

  if (!r || r->y+r->h > base) {
    draw_bot_frame();
  }
}

void TMenu::setup_bg_layer(SDL_Surface *bitmap) {
  // called after work_area is initialized
  if (bg_layer)
    SDL_FreeSurface(bg_layer);
  if (bitmap) {
    int border;
    if (GameBitmap && bitmap == get_surface_from_bmp(GameBitmap))
      border = current_game->video->border_size;
    else
      border = 0;
    double ratio;
    double zoom;
    SDL_Rect src;
    src.x = border;
    src.y = border;
    src.w = bitmap->w - border*2;
    src.h = bitmap->h - border*2;
    ratio = src.w*1.0/src.h;
    if (ratio*work_area.h > work_area.w) {
      bgdst.w = work_area.w;
      bgdst.h = (Uint16)(work_area.w/ratio);
      zoom = bgdst.w*1.0/src.w;
    } else {
      bgdst.w = (Uint16)(ratio*work_area.h);
      bgdst.h = work_area.h;
      zoom = bgdst.h*1.0/src.h;
    }
    bgdst.x = (work_area.w-bgdst.w)/2+work_area.x;
    bgdst.y = (work_area.h-bgdst.h)/2+work_area.y;
    SDL_Surface *zoomed;
    if (!color_format) color_format = sdl_screen->format;
    if (border) {
      bg_layer = SDL_CreateRGBSurface(SDL_SWSURFACE,src.w,src.h,display_cfg.bpp,color_format->Rmask,color_format->Gmask,color_format->Bmask,color_format->Amask);
      if (display_cfg.bpp == 8)
	SDL_SetPalette(bg_layer,SDL_LOGPAL,(SDL_Color*)pal,0,256);

      SDL_BlitSurface(bitmap,&src,
	  bg_layer,NULL);
      zoomed = rotozoomSurface(bg_layer,0.0,zoom,1);
      SDL_FreeSurface(bg_layer);
    } else {
      zoomed = rotozoomSurface(bitmap, 0.0, zoom, 0);
    }
    bg_layer = zoomed;
    if (bg_layer->flags & SDL_SRCCOLORKEY) {
      SDL_SetColorKey(bg_layer,0,0); // We don't want transparency in the bg!
    }
  } else {
    bgdst = work_area;
    bg_layer = NULL;
  }
}

void TMenu::compute_width_from_font() {
  width_max = 0;
  int width_max_options = 0,hwidth_max_options = 0,n,w;
  // The problem with variable width fonts is that it's not because a string
  // is longer than another that it will require more space on screen
  // so we must restart the loop again and compute the real width on screen
  // for each string !
  if (header) {
      for (n=0; header[n].label; n++) {
	  w = h_child[n]->get_width(font);
	  if (w > width_max) {
	      width_max = w;
	  }
	  w = h_child[n]->get_width_max_options(font);
	  if (w > hwidth_max_options)
	      hwidth_max_options = w;
      }
  }
  width_max += 2*HMARGIN;
  hxoptions = width_max;
  for (int x=0; x<nb_disp_items; x++) {
      n = menu_disp[x];
    w = child[n]->get_width(font);
    if (w > width_max) {
      width_max = w;
    }
    w = child[n]->get_width_max_options(font);
    if (w > width_max_options)
      width_max_options = w;
  }
  if (width_max > hxoptions) width_max += 2*HMARGIN;
  if (width_max > work_area.w) width_max = work_area.w;
  if (hxoptions + hwidth_max_options + HMARGIN > width_max) {
      width_max = hxoptions + hwidth_max_options + HMARGIN;
  }
  w = get_fglayer_footer_width();
  if (w > width_max)
    width_max = w;
  xoptions = width_max;
  if (width_max_options) {
    width_max += width_max_options;
    width_max += HMARGIN;
  }
  if (width_max > work_area.w) width_max = work_area.w;
  if (width_max_options > work_area.w)
	  width_max_options = work_area.w;
}

void TMenu::adjust_len_max_options(unsigned int &len_max_options) {
  // Just in case some inheritance needs to adjust this...
}

void TMenu::setup_font(unsigned int len_frame) {
  int w,h,n;
  compute_nb_items();
  unsigned int len_max_options = 0,len_max = 0;
  UINT32 len;
  int nb=0;
  if (nb_items) {
    for (n=0; n<nb_items; n++) {
      len = child[n]->get_len();
      if (len > len_max) {
	len_max = len;
      }
      len = child[n]->get_len_max_options();
      if (len > len_max_options)
	len_max_options = len;
    }
    if (header) {
	for (nb=0; header[nb].label; nb++) {
	    len = h_child[nb]->get_len();
	    if (len > len_max) len_max = len;
	    len = h_child[nb]->get_len_max_options();
	    if (len > len_max_options) len_max_options = len;
	}
    }
    len = get_fglayer_footer_len();
    if (len > len_max + len_max_options)
      len_max = len;
  }

  adjust_len_max_options(len_max_options);

  if (font) delete font;
  if (len_max + len_max_options + 3 > len_frame) {
    w = sdl_screen->w/(len_max+len_max_options + 3); // ideal font width & height, with some
  } else {
    w = sdl_screen->w/(len_frame); // ideal font width & height, with some
  }
  if (nb_disp_items + nb == 0) return;
  int hheader = 0;
  if (!header) skip_fglayer_header(hheader);
  h = (sdl_screen->h - 40 - hheader)/(nb_disp_items+nb); // margin
  h = h*4/9; // This 5/11 is just the result of tests, so that the main
  // menu fits on the screen without scrollbar when loading bublbobl !
  // Actually it's probably dependant of the font (size w != size h).
  if (h<min_font_size) h = min_font_size;
  if (h < w) w=h; // take the minimum for the ttf...
  else while (h < min_font_size && (w+h)/2 > 2+min_font_size) {
    w = (w+h)/2; // take an average value when w much bigger than h
  }
  if (w < min_font_size) w = min_font_size;
  font = new TFont_ttf(w,font_name);
  if (lift) { // lift place changes with the font
    delete lift;
    lift = NULL;
  }
  compute_width_from_font();
}

int TMenu::compute_fglayer_height() {
  int h;
  int nbh = 0;
  if (header) {
      for (nbh=0; header[nbh].label; nbh++);
  }
  if (nb_disp_items+nbh == 0) return 0;
  rows = work_area.h / font->get_font_height()-1;
  if (rows > nb_disp_items)
    rows = nb_disp_items;
  reset_top();
  if (top+rows > nb_disp_items)
    rows = nb_disp_items - top;
  if (top >= 0) {
    do {
      h = 2*HMARGIN + get_fglayer_footer_height();
      skip_fglayer_header(h);
      if (menu_disp)
	  for (int n=top; n<top+rows; n++)
	      h += child[menu_disp[n]]->get_height(font);
      if (h > work_area.h)
	rows--;
    } while (h > work_area.h);
  } else
    h = 2*HMARGIN+font->get_font_height()*rows; // rough approximation
  return h;
}

void TMenu::setup_fg_layer() {
  int w,h;

  work_area.x = 0;
  work_area.w = sdl_screen->w;
  w = width_max;
  h = compute_fglayer_height();
  fgdst.x = (work_area.w-w)/2;
  fgdst.y = (work_area.h-h)/2+work_area.y;
  if (fgdst.y < 0) {
    fgdst.y = 0;
  }
  int had_lift = 0;
  if (lift) {
      delete lift;
      had_lift = 1;
      lift = NULL;
  }
  if (fg_layer)
    SDL_FreeSurface(fg_layer);
  if (nb_disp_items > rows) {
      if (!had_lift)
	  width_max += 10;
    w = width_max;
    int y = 0;
    skip_fglayer_header(y);
    lift = new TLift(width_max-20,y,h-y-get_fglayer_footer_height()-HMARGIN,
	    &top,&nb_disp_items,&rows,&update_count,fg_layer,cslider_border,cslider_bar,cslider_lift);
  }
  if (use_transparency)
    fg_layer = SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCALPHA,w,h,
	32,0xff0000,0x00ff00,0x0000ff,0xff000000);
  else
    fg_layer = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,
      sdl_screen->format->BitsPerPixel,
      sdl_screen->format->Rmask,
      sdl_screen->format->Gmask,
      sdl_screen->format->Bmask,
      sdl_screen->format->Amask);
  if (lift)
    lift->set_surface(fg_layer);
  bgsdl = gfx_to_sdlcolor(fg_layer,bg);
  if (!fg_layer) {
    printf("fg layer creation failed: %s\n",SDL_GetError());
    exit(1);
  }
  // SDL_SetAlpha(fg_layer,SDL_SRCALPHA | SDL_RLEACCEL,(fw > 10 ? 128 : 128+48));
  fgdst.w = fg_layer->w; // w & h are not used normaly, but just in case...
  fgdst.h = fg_layer->h;
}

int TMenu::get_list_index(int n) {
  return child[n]->get_list_index();
}

int TMenu::compute_selcolor() {
  int selcolor;
  if (display_cfg.bpp > 8) {
    selcolor = (update_count<<1) & 0xff;
    if (selcolor > 0x80)
      selcolor = 0x100-selcolor;
    selcolor = mymakecol(0x7f+selcolor,0x7f+selcolor,0x7f+selcolor);
  } else
    selcolor = fg;
  return selcolor;
}

void TMenu::disp_menu(int n,int y,int w,int h) {
  /* This is only a simplification function :
   * it's passed y,s,w,h from update_fg_layer so that it can concentrate
   * only on what to display, and forget about the layers (just update
   * fg_layer with what was passed)
   * This is needed because if the entry has list of values attached to it
   * then there is more to display than just the label passed in s, and this
   * function also handles the flashing background on the current selection */

  int fw = HMARGIN;
  int selcolor;
  int myfg = get_fgcolor(n);
  if ((!focus && n == sel)) {
    selcolor = compute_selcolor();
    child[n]->disp(fg_layer,font,fw,y,w,h,bg,selcolor,xoptions);
  } else {
    child[n]->disp(fg_layer,font,fw,y,w,h,myfg,0,xoptions);
  }
}

void TMenu::disp_header(int n,int y,int w,int h) {
  // Equivalent to disp_menu but for the header
  // Even if the code is almost the same it would be awkwared to share it
  // because we must know what is currently drawn to know if the selection must
  // be drawn or not
  int fw = HMARGIN;
  int selcolor;
  int myfg = fg; // for now no need to change the header colors...
  if ((focus && n == hsel)) {
    selcolor = compute_selcolor();
    h_child[n]->disp(fg_layer,font,fw,y,w,h,bg,selcolor,hxoptions);
  } else {
    h_child[n]->disp(fg_layer,font,fw,y,w,h,myfg,0,hxoptions);
  }
}

void TMenu::display_fglayer_header(int &y) {
  // a border, usefull when dialogs are opaque
  rectangleColor(fg_layer,0,0,fg_layer->w-1,fg_layer->h-1,fg);
  if (!font) return;
  if (header) {
      int w = width_max - HMARGIN;

      for (int n=0; header[n].label; n++) {
	  int h = h_child[n]->get_height(font);
	  disp_header(n,y,w,h);
	  y += h;
      }
  }
}

void TMenu::blit_area(int x,int y,int w,int h) {
    /* Blit only 1 entry, in this case, update bg, then fg, then screen */
    SDL_Rect from, to;
    from.x = x; from.y = y; from.h = h;
    from.w = w;
    to.x = fgdst.x+x;
    to.y = fgdst.y+y;
    to.w = from.w;
    to.h = from.h;
    SDL_Rect tmp = to;
    if (fg_layer->format->Amask)
	update_bg_layer(&to);
    int ret = SDL_BlitSurface(fg_layer,&from,sdl_screen,&tmp);
    if (ret) {
	printf("SDL_BlitSurface returned %d\n",ret);
	char *sdl_error = SDL_GetError( );

	if( sdl_error[0] != '\0' ) {
	    fprintf(stderr, "update_fg_layer: SDL error '%s'\n", sdl_error);
	    SDL_ClearError();
	}
	exit(1);
    }
    do_update(&to);
}

void TMenu::update_header_entry(int nb) {
    if (header) {
	int y = HMARGIN;
	int w = width_max - HMARGIN;
	for (int n=0; header[n].label; n++) {
	  int h = h_child[n]->get_height(font);
	  if (n == nb) {
	      // if there is only 1 indice to update, clear the bg for it
	      SDL_Rect dst;
	      dst.x = HMARGIN; dst.y = y; dst.w = w; dst.h = h;
	      SDL_FillRect(fg_layer,&dst,bgsdl);
	      disp_header(n,y,w,h);
	      blit_area(HMARGIN,y,w,h);
	      break;
	  }
	  y += h;
	}
    }
}

void TMenu::skip_fglayer_header(int &y) {
  // No default header
  if (header) {
      for (int n=0; header[n].label; n++) {
	  int h = h_child[n]->get_height(font);
	  y += h;
      }
  }
}

int TMenu::get_fglayer_footer_height() {
  return 0;
}

int TMenu::get_fglayer_footer_len() {
  return 0;
}

int TMenu::get_fglayer_footer_width() {
    if (font) {
	int w,h;
	font->dimensions("W",&w,&h);
	return w * get_fglayer_footer_len();
    }
  return 0;
}

void TMenu::display_fglayer_footer(int x,int &y, int w, int xoptions) {
}

void TMenu::fglayer_footer_update() {}

int TMenu::fglayer_footer_handle_key(SDL_Event *event) {
  return 0;
}

void TMenu::fglayer_footer_call_handler() {}

void TMenu::update_fg_layer(int nb_to_update) {
  int n,max;
  int fw = HMARGIN;
  /* Basic scrolling setup... */
  if(top > nb_disp_items-rows) top=nb_disp_items-rows;
  if(top < 0)		  top = 0;
  if(sel >= nb_items)	  sel = 0;

  int y = HMARGIN;
  if (nb_to_update < 0) {
    // Use SDL_FillRect instead of boxColor because we don't want blending here
    // Clear the whole fg layer here, not related to header, done only if
    // redrawing everything
    SDL_FillRect(fg_layer,NULL,bgsdl);
    display_fglayer_header(y);
  } else {
    skip_fglayer_header(y);
  }

  max = top+rows;
  if (nb_disp_items < max)
    max = nb_disp_items;

  int w = width_max - HMARGIN;

  if (lift)
    w -= 20;
  else
    w -= HMARGIN; // the lift should probably use HMARGIN width

  for (n=top; n<max; n++) {
    int index = menu_disp[n];
    int h;
    h = child[index]->get_height(font);

    if (nb_to_update < 0 || nb_to_update == index) {
      if (nb_to_update == index) {
	// if there is only 1 indice to update, clear the bg for it
	SDL_Rect dst;
	dst.x = fw; dst.y = y; dst.w = w; dst.h = h;
	SDL_FillRect(fg_layer,&dst,bgsdl);
      }
      disp_menu(index,y,w,h);
      if (nb_to_update == index) {
	/* If we update just 1 entry, then we must explicitely update
	 * 1st the bg layer for this entry and then blit the fg layer over
	 * it */
	  blit_area(fw,y,w,h);
      }
    }
    y += h;
  }

  if (nb_to_update == -1) {
    if (lift) {
      lift->draw();
    }
    display_fglayer_footer(fw,y,w,xoptions);
    // do_update(&fgdst);
  }
}

void TMenu::update_bg_layer(SDL_Rect *region) {
  SDL_Rect tmp;
  if (bgdst.w == 0 || bgdst.h == 0) {
      // In case a messagebox of error is displayed at the very start
      // of the program, then bgdst can be null (dialog)
      // or a loading progress dialog at start
      if (region)
	  boxColor(sdl_screen,region->x,region->y,region->x+region->w-1,
		  region->y+region->h-1,mymakecol(0,0,0));
      return;
  }
  if (region) {
    tmp = *region; // otherwise SDL_BlitSurface changes region
    if (tmp.y < work_area.y) tmp.y = work_area.y;
    if (tmp.y+tmp.h > work_area.y+work_area.h)
      tmp.h = work_area.y+work_area.h - tmp.y;
    if (tmp.h > 65000)
      return;
  }
  SDL_Rect src;
  if (!bg_layer) {
    if (region) {
      boxColor(sdl_screen,tmp.x,tmp.y,tmp.x+tmp.w-1,
	tmp.y+tmp.h-1,mymakecol(0,0,0));
    } else {
      SDL_FillRect(sdl_screen,&work_area,0);
    }
    return;
  } else if (!region) {
    tmp = work_area;
  }
  if (bgdst.x > tmp.x) {
    // Normally it can't be out in x and y at the same time
    boxColor(sdl_screen,tmp.x,tmp.y,bgdst.x,tmp.y+tmp.h-1,mymakecol(0,0,0));
  }
  if (bgdst.y > tmp.y) {
    boxColor(sdl_screen,tmp.x,tmp.y,tmp.x+tmp.w-1,bgdst.y,mymakecol(0,0,0));
  }
  if (bgdst.x+bgdst.w < tmp.x+tmp.w) {
    // out on right side !
    boxColor(sdl_screen,tmp.x,tmp.y,tmp.x+tmp.w-1,tmp.y+tmp.h-1,mymakecol(0,0,0));
  }
  if (bgdst.y+bgdst.h < tmp.y+tmp.h) {
    boxColor(sdl_screen,tmp.x,bgdst.y+bgdst.h,tmp.x+tmp.w-1,tmp.y+tmp.h-1,mymakecol(0,0,0));
  }
  src.x = tmp.x-bgdst.x;
  src.y = tmp.y-bgdst.y;
  src.w = tmp.w;
  src.h = tmp.h;
  // with the clipped coordinates !
  SDL_SetClipRect(sdl_screen,&tmp);
  SDL_BlitSurface(bg_layer,&src,sdl_screen,&tmp);
  SDL_SetClipRect(sdl_screen,NULL);
}

void TMenu::do_update(SDL_Rect *region) {
  SDL_Rect r;
  int drawn_mouse = 0;
  if (emulate_mouse_cursor && cursor) {
    if (!mouse_erased) {
      if (!region || (mousex[flip_page] >= region->x &&
	    mousex[flip_page] < region->x+region->w &&
	    mousey[flip_page] >= region->y &&
	    mousey[flip_page] < region->y+region->h))
	mouse_erased = 1;
    }
    if (mouse_erased) {
      r.x = mousex[flip_page];
      r.y = mousey[flip_page];

      SDL_BlitSurface(cursor,NULL,sdl_screen,&r);
      mouse_erased = 0;
      drawn_mouse = 1;
    }
  }
  if ( sdl_screen->flags & SDL_DOUBLEBUF ) {
    if (!emulate_mouse_cursor || !cursor)
      SDL_ShowCursor(SDL_ENABLE);
    SDL_Flip(sdl_screen);
    if (!emulate_mouse_cursor || !cursor) {
      SDL_ShowCursor(SDL_DISABLE);
      mouse_erased = 0;
    }
    flip_page ^= 1;
    if (mousex[flip_page] != mousex[flip_page ^ 1] ||
        mousey[flip_page] != mousey[flip_page ^ 1]) {
      /* Mouse is not handled at all by SDL when double buffering.
       * It's a little surprising, but it's not so hard to do...
       * The size 32x32 is probably too big, but since my converted .cur files
       * are 32x32, it seems to be a safe choice... */
      SDL_Rect r;
      r.x = mousex[flip_page];
      r.y = mousey[flip_page];
      r.w = 32;
      r.h = 32;
      redraw(&r);
      mousex[flip_page] = mousex[flip_page ^ 1];
      mousey[flip_page] = mousey[flip_page ^ 1];
    }
    redraw(region);
  } else {
	  if (region) {
		  if (region->x+region->w > sdl_screen->w)
			  region->w = sdl_screen->w - region->x;
		  if (region->y+region->h > sdl_screen->h)
			  region->h = sdl_screen->h - region->y;
		  SDL_UpdateRect(sdl_screen, region->x,region->y,region->w,region->h);
	  } else
		  SDL_UpdateRect(sdl_screen, 0,0,0,0);
	  if (emulate_mouse_cursor && cursor && drawn_mouse) {
		  if (region && (r.x < region->x || r.x >= region->x+region->w ||
					  r.y < region->y || r.y >= region->y + region->h ||
					  r.x+r.w > region->x+region->w || r.y+r.h > region->y+region->h)) {
			  r.w = 32;
			  r.h = 32;
			  if (r.x + r.w > sdl_screen->w) r.w = sdl_screen->w - r.x;
			  if (r.y + r.h > sdl_screen->h) r.h = sdl_screen->h - r.y;
			  SDL_UpdateRect(sdl_screen,r.x,r.y,r.w,r.h);
		  }
	  }
  }
}

void TMenu::draw() {

    if (!sdl_screen->pixels) {
	print_debug("returning from draw on null pixels\n");
	return;
    }
  draw_frame();

  if (!bg_layer) {
    if (GameBitmap)
      setup_bg_layer(get_surface_from_bmp(GameBitmap));
    else
      setup_bg_layer(NULL);
  }
  // SDL_BlitSurface(bg_layer,NULL,sdl_screen,&bgdst);
  update_bg_layer(NULL);
  setup_fg_layer();
  update_fg_layer();
  SDL_BlitSurface(fg_layer,NULL,sdl_screen,&fgdst);
  do_update(NULL);
}

void TMenu::redraw_fg_layer() {
  // this layer has become tricky to update finally !!!
  if (!fg_layer) {
      print_debug("rebuilding fg_layer\n");
      return draw();
  }
  if (!sdl_screen->pixels) {
      printf("adjust_gui_resolution from redraw_fg_layer\n");
      adjust_gui_resolution();
  }
  update_fg_layer(-1);
  // update_bg_layer must be called just before calling blitsurface to
  // sdl_screen or otherwise you see bglayer alone on screen during the update
  // (flashing effect), at least without double buffering.
  // Calling it here stops the flashing effect, at least on my machine.
  if (fg_layer->format->Amask)
    update_bg_layer(&fgdst);
  else
    printf("skip update bg\n");
  SDL_BlitSurface(fg_layer,NULL,sdl_screen,&fgdst);
  do_update(&fgdst);
}

static int axis_x,axis_y;

void TMenu::reset_top() {
    if (!rows) return;
    if (focus) {
	if (hsel != -1)
	    for (hsel=0; !h_child[hsel]->can_be_selected(); hsel++);
	// Don't return here, reset top for the main part too !
    }
    int seldisp = get_seldisp();
    if (seldisp > top+rows-1)
	top = seldisp-rows/2;
    else if (seldisp < top && seldisp >= 0) {
	top = seldisp;
	// In case there are non selectable lines upper, there will be no way
	// to display them again, so it's better to scroll up more in this case
	while (top > 0 && !can_be_selected(top-1))
	    top--;
    }
}

void TMenu::next_sel() {
    if (focus) {
	// in the header
	if (hsel < 0) return;
	int old = hsel;
	do {
	    hsel++;
	    if (!header[hsel].label) {
		hsel--;
		if (nb_disp_items > 0) {
		    toggle_header();
		    sel = menu_disp[0];
		}
		return;
	    }
	} while (!h_child[hsel]->can_be_selected() && hsel != old);
	return;
    }
  int old_sel = sel;
  if (sel < 0) {
      if (header) {
	  while (header[hsel].label)
	      hsel++;
	  hsel--;
      } else if (top+rows < nb_disp_items)
	  top ++;
      return;
  }
  do {
    sel++;
    if (sel > menu_disp[nb_disp_items-1]) {
      sel = menu_disp[0];
    }
  } while (sel < nb_items && !can_be_selected(sel));
  if (sel == 0 && !can_be_selected(sel)) {
    sel = old_sel; // failure to change selection
    if (top+rows < nb_disp_items) top++;
  } else if (old_sel == sel && top+rows < nb_disp_items)
      top++;
  else if (cycle_down) {
    reset_top();
  }
}

void TMenu::prev_sel() {
    if (focus) {
	// in the header
	if (hsel == -1) return;
	if (hsel == 0 && nb_disp_items) {
	    // Headers must feel like the normal dialog, if reaching the top
	    // we go directly to the end of the normal list
	    sel = menu_disp[nb_disp_items-1];
	    toggle_header();
	    reset_top();
	    return;
	}
	int nb;
	for (nb=0; header[nb].label; nb++);
	int old = hsel;
	do {
	    hsel--;
	    if (hsel < 0) hsel = nb-1;
	} while (!h_child[hsel]->can_be_selected() && hsel != old);
	return;
    }
  int old_sel = sel;
  if (sel < 0) {
      if (header) {
	  sel = 0;
	  toggle_header();
	  while (header[hsel].label)
	      hsel++;
	  hsel--;
	  return;
      }
      if (top > 0)
	  top--;
      return;
  }
  do {
    sel--;
    if (sel < 0) {
	if (header) {
	    sel = 0;
	    toggle_header();
	    while (header[hsel].label)
		hsel++;
	    hsel--;
	    return;
	}
      sel = menu_disp[nb_disp_items - 1];
    }
  } while (sel >= 0 && !can_be_selected(sel));
  if (!can_be_selected(sel))  {
    sel = old_sel; // failure to change selection
    if (top > 0) top--;
  } else if (old_sel == sel && top > 0)
      top--;
  else if (cycle_up) {
    int seldisp = get_seldisp();
    if (seldisp > top+rows-1)
      top = seldisp-rows+1;
    else if (seldisp < top)
      top = seldisp;
  }
}

void TMenu::find_new_sel() {
  // Find a new selection in the visible entries when top has just changed
  if (header) {
      for (hsel=0; header[hsel].label && !h_child[hsel]->can_be_selected();
	      hsel++);
      if (!header[hsel].label)
	  hsel = -1;
  }
  if (top > nb_disp_items || top + rows > nb_disp_items)
      top = 0;
  if (top + rows > nb_disp_items)
      rows = nb_disp_items;

  if (menu_disp)
      for (int n=top; n<top+rows; n++) {
	  int index = menu_disp[n];
	  if (can_be_selected(index)) {
	      sel = index;
	      break;
	  }
      }
  if (sel == -1 && header && !focus) {
      focus = 1;
  }
}

void TMenu::find_new_sel_from_end() {
  // Find a new selection in the visible entries when top has just changed
  for (int n=top+rows-1; n>=top; n--) {
    int index = menu_disp[n];
    if (can_be_selected(index)) {
      sel = index;
      break;
    }
  }
}

void TMenu::next_page() {
  if (top+rows < nb_disp_items) {
    top += rows;
    if (top + rows > nb_disp_items)
      top = nb_disp_items - rows;
    find_new_sel();
  } else if (sel < menu_disp[nb_disp_items-1])
    find_new_sel_from_end();
}

void TMenu::prev_page() {
  if (top > 0) {
    top -= rows;
    if (top < 0)
      top = 0;
    find_new_sel();
  } else if (sel > menu_disp[top])
    find_new_sel();
}

void TMenu::goto_top() {
  if (top > 0) {
    top = 0;
    find_new_sel();
  } else if (sel > menu_disp[0])
    find_new_sel();
}

void TMenu::goto_end() {
  if (top < nb_disp_items - rows) {
    top = nb_disp_items - rows;
    find_new_sel();
  } else if (sel < menu_disp[nb_disp_items-1])
    find_new_sel_from_end();
}

int TMenu::get_seldisp() {
  int n;
  if (sel == -1) return -1;
  for (n=0; n<nb_disp_items; n++) {
    if (menu_disp[n] == sel) break;
  }
  return n;
}

static int mystrcasestr(const char *s1,const char *s2) {
    /* Since super mingw doesn't know strcasestr, here is my version */
    /* returns an int, it's just a boolean */
    char lower1[256],lower2[256];
    int n;
    for (n=0; n<255 && s1[n]; n++)
	lower1[n] = tolower(s1[n]);
    lower1[n] = 0;
    for (n=0; n<255 && s2[n]; n++)
	lower2[n] = tolower(s2[n]);
    lower2[n] = 0;
    return strstr(lower1,lower2) != NULL;
}

void TMenu::set_header(menu_item_t *myheader) {
    header = myheader;
    // Translate the header...
    while (header && header->label) {
	header->label = gettext(header->label);
	for (int n=0; n<header->values_list_size && header->values_list_label[n]; n++)
	    header->values_list_label[n] = gettext(header->values_list_label[n]);
	header++;
    }
    header = myheader;
}

void TMenu::toggle_header() {
    if (focus && sel == -1) return;
    if (!focus && (hsel == -1 || !header)) return;
    focus ^= 1;
    update_fg_layer(sel);
    if (hsel >= 0) update_header_entry(hsel);
}

static const char *skip_esc(const char *s) {
    while (*s == 27 && s[1]=='[') {
	s+=2;
	while (*s >= '0' && *s <= '9') // color
	    s++;
	s++; // mode;
    }
    return s;
}

void TMenu::handle_key(SDL_Event *event) {
  int sym,ret;
  if ((!focus && sel >= 0 && (ret = child[sel]->handle_key(event))) ||
	  (focus && hsel >= 0 && (ret = h_child[hsel]->handle_key(event)))) {
    if (ret > 0) call_handler();
    return;
  }
  ret = fglayer_footer_handle_key(event);
  if (ret > 0) fglayer_footer_call_handler();
  if (ret) return;

  switch (event->type) {
    case SDL_KEYDOWN:
      sym = event->key.keysym.sym;
      switch(sym) {
	case SDLK_UP:
	  prev_sel();
	  keybuf[0] = 0;
	  break;
	case SDLK_DOWN:
	  next_sel();
	  keybuf[0] = 0;
	  break;
	case SDLK_PAGEDOWN:
	  next_page();
	  keybuf[0] = 0;
	  break;
	case SDLK_PAGEUP:
	  prev_page();
	  keybuf[0] = 0;
	  break;
	case SDLK_HOME:
	  goto_top();
	  keybuf[0] = 0;
	  break;
	case SDLK_END:
	  goto_end();
	  keybuf[0] = 0;
	  break;
	case SDLK_RIGHT:
	  next_list_item();
	  break;
	case SDLK_LEFT:
	  prev_list_item();
	  break;
	case SDLK_RETURN:
	  exec_menu_item();
	  break;
	case SDLK_ESCAPE:
	  exit_menu = can_exit();
	  break;
	case SDLK_TAB:
	  toggle_header();
	  break;
	default:
	  int unicode = event->key.keysym.unicode;
	  if (unicode) sym = unicode;
          if (sym >= ' ' && sym <= 'z' && sel >= 0) {
	    /* sym contains the "raw" key code, in windows it's the letter of
	     * a qwerty keyboard, ignoring the current keyboard mapping, but
	     * even in linux with some keyboard mappings in can also become
	     * the letter of an equivalent qwerty keyboard. So we must use the
	     * unicode value if available instead... */
	    int index = 0;
	    while (index < MAX_KEYBUF-1 && keybuf[index])
	      index++;
	    if (index < MAX_KEYBUF - 1) {
	      int n,seldisp;
	      keybuf[index++] = sym;
	      keybuf[index] = 0;
	      if (sel >= 0 && child[sel]->handle_key_buff(keybuf)) {
		update_fg_layer();
		call_handler();
	      } else {
		// look for the new selection then, starting at sel
		// 1 : find sel in the menu_disp array
		n = get_seldisp();
		int found = 0;
		for (; n<nb_disp_items; n++) {
		    const char *s = skip_esc(menu[menu_disp[n]].label);
		    if (can_be_selected(menu_disp[n]) &&
			    !strncasecmp(s,keybuf,index)) {
			found = 1;
			break;
		    }
		}
		if (!found) { // not found -> search from 0
		    for (n=0; n<=get_seldisp(); n++) {
			const char *s = skip_esc(menu[menu_disp[n]].label);
			if (can_be_selected(menu_disp[n]) &&
				!strncasecmp(s,keybuf,index)) {
			    found = 1;
			    break;
			}
		    }
		}

		if (!found) { // not found -> search substring
		    for (n=get_seldisp(); n<nb_disp_items; n++) {
			const char *s = skip_esc(menu[menu_disp[n]].label);
			if (can_be_selected(menu_disp[n]) &&
				mystrcasestr(s,keybuf)) {
			    found = 1;
			    break;
			}
		    }
		}
		if (!found) { // and from 0
		    for (n=0; n<nb_disp_items; n++) {
			const char *s = skip_esc(menu[menu_disp[n]].label);
			if (can_be_selected(menu_disp[n]) &&
				mystrcasestr(s,keybuf)) {
			    found = 1;
			    break;
			}
		    }
		}

		if (!found) {
		    // Let's say that the new key is the start of a new selection
		    // then...
		    if (index == 1) { // if it's already the 1st one, forget it
			keybuf[0] = 0;
			break;
		    }
		    // Otherwise just clear keybuf and process this event again
		    keybuf[0] = 0;
		    handle_key(event);
		    break;
		}
		sel = menu_disp[n];
		while (sel < menu_disp[top]) {
		    top--;
		}
		while (top+rows < nb_disp_items && sel >= menu_disp[top+rows]) {
		    top++;
		}
		if (!return_mandatory) {
		    // check if another entry matches keybuf
		    seldisp = n;
		    for (n=seldisp+1; n<nb_disp_items; n++) {
			const char *s = skip_esc(menu[menu_disp[n]].label);
			if (can_be_selected(menu_disp[n]) &&
				!strnicmp(s,keybuf,index))
			    break;
		    }
		    if (n == nb_disp_items) {
			for (n=0; n<seldisp; n++) {
			    const char *s = skip_esc(menu[menu_disp[n]].label);
			    if (can_be_selected(menu_disp[n]) &&
				    !strnicmp(s,keybuf,index))
				break;
			}
			if (n == seldisp) { // no other entry
			    exec_menu_item();
			}
		    }
		}
	      }
	    }
	  }
      }
      break;
  }
}

void TMenu::redraw(SDL_Rect *r) {
    if (!sdl_screen->pixels) {
	print_debug("adjust_gui_resolution from redraw\n");
	adjust_gui_resolution();
    }
  draw_frame(r);
  update_bg_layer(r);
  if (!r) {
    SDL_BlitSurface(fg_layer,NULL,sdl_screen,&fgdst);
    return;
  }
  SDL_Rect oldr = *r;
  if (r->x < fgdst.x+fgdst.w && r->y < fgdst.y+fgdst.h &&
      r->x+r->w >= fgdst.x && r->y+r->h >= fgdst.y) {
    SDL_Rect from;
    from.x = r->x - fgdst.x;
    from.y = r->y - fgdst.y;
    from.w = r->w;
    from.h = r->h;
    if (from.x < 0) {
      r->x -= from.x;
      from.w += from.x;
      r->w = from.w;
      from.x = 0;
    }
    if (from.y < 0) {
      r->y -= from.y;
      from.h += from.y;
      r->h = from.h;
      from.y = 0;
    }
    SDL_BlitSurface(fg_layer,&from,sdl_screen,r);
    *r = oldr; // preserve region
  }
}

void TMenu::handle_button(SDL_Event *event, int index) {
    if (event->type == SDL_MOUSEBUTTONUP ) {
	switch(event->button.button) {
	case 1: if ((!focus && index == sel) || (focus && hsel >= 0))
		    exec_menu_item();
	       	break;
		// Apparently in sdl button 2 is center button, and 3 is right
		// (hope it's standard in every os !)
	case 2: if ((!focus && index == sel) || (focus && index == hsel))
		    prev_list_item();
	       	break;
	case 3: exit_menu = can_exit(); break;
	case 4: prev_page(); break;
	case 5: next_page(); break;
	}
    }
}

void TMenu::handle_mouse(SDL_Event *event) {
  int mx,my;
  if (event->type == SDL_MOUSEMOTION) {
    mx = event->motion.x;
    my = event->motion.y;
    if (emulate_mouse_cursor || (sdl_screen->flags & SDL_DOUBLEBUF)) {
      if (!mouse_erased) {
	SDL_Rect r;
	r.x = mousex[flip_page]; // mx - event->motion.xrel;
	r.y = mousey[flip_page]; // my - event->motion.yrel;
	r.w = 32;
	r.h = 32;
	redraw(&r);
	mouse_erased = emulate_mouse_cursor;
	if (!(sdl_screen->flags & SDL_DOUBLEBUF)) {
	  // redraw can change r values, must be reset
	  r.x = mousex[flip_page]; // mx - event->motion.xrel;
	  r.y = mousey[flip_page]; // my - event->motion.yrel;
	  r.w = 32;
	  r.h = 32;
	  if (r.x + r.w > sdl_screen->w) r.w = sdl_screen->w - r.x;
	  if (r.y + r.h > sdl_screen->h) r.h = sdl_screen->h - r.y;
	  SDL_UpdateRect(sdl_screen,r.x,r.y,r.w,r.h);
	}
	mousex[flip_page] = mx;
	mousey[flip_page] = my;
      }
    }
  } else {
    mx = event->button.x;
    my = event->button.y;
  }
  // fix event coordinates for the children...
  if (event->type == SDL_MOUSEMOTION)  {
    event->motion.x -= fgdst.x;
    event->motion.y -= fgdst.y;
  } else {
    event->button.x -= fgdst.x;
    event->button.y -= fgdst.y;
  }
  if (lift && mx > fgdst.x+fgdst.w-lift->get_width()) {
    lift->handle_mouse(event);
    return;
  }
  switch (event->type) {
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
      if (my >= fgdst.y && my < fgdst.y+fgdst.h && mx >= fgdst.x && mx < fgdst.x+fgdst.w) {
	int ystart = fgdst.y + HMARGIN;
	int index,h=0;
	int n;
	if (header) {
	    for (n=0; header[n].label; n++) {
		h += h_child[n]->get_height(font);
		if (ystart + h > my) break;
	    }
	    if (header[n].label && h_child[n]->can_be_selected()) {
		if (!focus) {
		    toggle_header();
		}
		hsel = n;
		if (h_child[hsel]->handle_mouse(event)) {
		    call_handler();
		    return;
		}
	    } else if (!header[n].label && focus) {
		toggle_header();
	    }
	} else
	    skip_fglayer_header(ystart);
	for (index = 0; index < rows; index++) {
          h += child[index+top]->get_height(font);
	  if (ystart + h > my)
	    break;
	}
	if (index >= 0 && top+index < nb_disp_items)
	  index = menu_disp[top + index];
	else
	  index = -1;
	if (index >= 0 && index != sel && can_be_selected(index))
	  sel = index;
	if (sel >= 0 && child[sel]->handle_mouse(event)) {
	  call_handler();
	  return;
	}
	if (event->type != SDL_MOUSEMOTION && ((!focus && index >= 0) ||
		    (focus && hsel == n)))
	    handle_button(event,index);
      }
      break;
  }
}

void TMenu::produce_joystick_event() {
  // Produce a joystick event based on axis_x & axis_y
  if (sel >=0 && child[sel]->produce_joystick_event(axis_x,axis_y)) {
    call_handler();
    return;
  }
  if (axis_x == -1) {
    if (menu[sel].value_int)
      prev_list_item();
    else {
      prev_page();
    }
  } else if (axis_x == 1) {
    if (menu[sel].value_int)
      next_list_item();
    else
      next_page();
  }
  if (axis_y == -1) {
    prev_sel();
  } else if (axis_y == 1) {
    next_sel();
  }
}

void TMenu::handle_joystick(SDL_Event *event) {
  int hat;
  switch (event->type) {
    case SDL_JOYHATMOTION:
      /* Emulate joystick movement with a hat - what linux does automatically
       * but it's for windows... */
      hat = event->jhat.value;
      axis_x = 0;
      axis_y = 0;
      jmoved = 0;

      if (hat == SDL_HAT_UP)
	axis_y = -1;
      if (hat == SDL_HAT_DOWN)
	axis_y = 1;
      if (hat == SDL_HAT_LEFT)
	axis_x = -1;
      if (hat == SDL_HAT_RIGHT)
	axis_x = 1;
      if (hat) {
	jmoved = 1;
	timer = update_count;
	produce_joystick_event();
      } else
	phase_repeat = 0;
      break;
  case SDL_JOYAXISMOTION:
    switch(event->jaxis.axis) {
      case 0: // x axis normally
        if (event->jaxis.value < -16000) {
	  if (axis_x > -1) {
	    axis_x = -1;
	    jmoved = 1;
	    timer = update_count;
	    produce_joystick_event();
	  }
	} else if (event->jaxis.value > 16000) {
	  if (axis_x < 1) {
	    axis_x = 1;
	    jmoved = 1;
	    timer = update_count;
	    produce_joystick_event();
	  }
	} else if ((axis_x == -1 && event->jaxis.value > -16000) ||
	           (axis_x == 1 && event->jaxis.value < 16000)) {
	  axis_x = 0;
	  jmoved = 0;
	  phase_repeat = 0;
	}
	break;
      case 1: // y axis
        if (event->jaxis.value < -16000) {
	  if (axis_y > -1) {
	    axis_y = -1;
	    jmoved = 1;
	    timer = update_count;
	    produce_joystick_event();
	  }
	} else if (event->jaxis.value > 16000) {
	  if (axis_y < 1) {
	    axis_y = 1;
	    jmoved = 1;
	    timer = update_count;
	    produce_joystick_event();
	  }
	} else if ((axis_y == -1 && event->jaxis.value > -16000) ||
	           (axis_y == 1 && event->jaxis.value < 16000)) {
	  axis_y = 0;
	  jmoved = 0;
	  phase_repeat = 0;
	}
	break;
    } // end processing axis
    break;
  case SDL_JOYBUTTONUP:
    switch (event->jbutton.button) {
      case 0: exec_menu_item(); break;
      case 1: exit_menu = can_exit(); break;
    }
    break;
  } // end processing event type
}

void TMenu::call_handler() {
    int exit = -10;
    if (focus) {
	if (header[hsel].menu_func)
	    exit = (*header[hsel].menu_func)(hsel);
    } else {
	if (menu[sel].menu_func)
	    exit = (*menu[sel].menu_func)(sel);
    }
    if (exit != -10) exit_menu = exit; // hack but it should work always
    if (exit_menu) exit_menu = can_exit();
    // No need to force a redraw here, it's handled by execute...
}

void TMenu::next_list_item() {
  if (!focus && sel >= 0) {
    child[sel]->next_list_item();
    call_handler();
  } else if (focus && hsel >= 0) {
    h_child[hsel]->next_list_item();
    call_handler();
  }
}

void TMenu::prev_list_item() {
  if (!focus && sel >= 0) {
    child[sel]->prev_list_item();
    call_handler();
  } else if (focus && hsel >= 0) {
    h_child[hsel]->prev_list_item();
    call_handler();
  }
}

void TMenu::exec_menu_item() {
  /* Warning : try to never override this function or call the parent
   * because if call_handler is not called then the caller variable is not
   * changed, producing display bugs */
    keybuf[0] = 0; // reset key buffer
    if (focus) {
	if (hsel < 0) return;
	if (header[hsel].value_int)
	    next_list_item();
	else if (header[hsel].menu_func) {
	    call_handler();
	}
	return;
    }
  if (sel < 0) return;
  if (menu[sel].value_int)
    next_list_item();
  else /* if (menu[sel].menu_func)*/ {
      // call_handler must be called in all cases here if overloaded like for
      // the game selection dialog !
    call_handler();
  }
}

static int gui_init;

void TMenu::execute() {
    gui_level++;
    if (!sdl_screen->pixels) {
	printf("adjust gui res from execute\n");
	adjust_gui_resolution();
    }
  SDL_Event event;
  exit_menu = 0;
  if (!gui_init++) {
    parent = caller = NULL;
    adjust_gui_resolution();
    sa_pause_sound();
    unicode = SDL_EnableUNICODE(-1);
    if (!unicode) SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(repeat_delay,
	repeat_interval);
    if (sdl_game_bitmap) {
      work_area.x = work_area.y = 0;
      work_area.w = sdl_screen->w; work_area.h = sdl_screen->h;
      TMenu::setup_bg_layer(sdl_game_bitmap);
    }
  }
  if (sdl_screen->flags & SDL_HWSURFACE) {
    /* Hw surfaces are very bad to handle transparency because when you
     * blit a transparent surface to it, you need to read from the hw
     * surface to compute the transparency and this is extremely slow !
     * So we'll just use an intermediate surface for that... */
    printf("this gui doesn't work for now on hw surfaces\n");
    exit(1);
  }

  if (font) {
    delete font;
    font = NULL;
  }
  SDL_initFramerate(&fpsm);
  fpsm.use_cpu_frame_count = 0;
  SDL_setFramerate(&fpsm,30);
  if (caller != this) {
    parent = caller; // update parent for persistant dialogs
  }

  draw();
  caller = this; // init after calling draw

  while (!exit_menu) {
    int oldsel = sel;
    if (focus) oldsel = hsel;
    int oldtop = top;
    while (SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
	handle_key(&event);
	break;
      case SDL_MOUSEMOTION:
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN:
        handle_mouse(&event);
	break;
      case SDL_JOYAXISMOTION:
      case SDL_JOYBALLMOTION:
      case SDL_JOYHATMOTION:
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        handle_joystick(&event);
	break;
      case SDL_VIDEORESIZE:
	if (!display_cfg.fullscreen || display_cfg.auto_mode_change) {
	    display_cfg.screen_x = event.resize.w;
	    display_cfg.screen_y = event.resize.h;
		if (keep_vga) {
			if (display_cfg.screen_x < 640)
				display_cfg.screen_x = 640;
			if (display_cfg.screen_y < 480)
				display_cfg.screen_y = 480;
		}
	    resize();
	    if (font) {
		delete font;
		font = NULL;
	    }
	    setup_bg_layer(sdl_game_bitmap);
	    draw();

	}
	break;
      case SDL_VIDEOEXPOSE:
        /* Strangely the VideoExposeEvent does not give any region to be
	 * redrawn, so we are forced to update everything.
	 * To be verified : with screen = SWSURFACE, just a do_update should
	 * be enough */
	 print_debug("expose event\n");
	 // redraw(NULL);
	do_update(NULL);
	if (sdl_screen->flags & SDL_DOUBLEBUF) {
	  do_update(NULL);
	}
	break;
      case SDL_QUIT:
	exit(0);
      }
      if (exit_menu) break;
    }
    SDL_setFramerate(&fpsm,30);
    if (exit_menu) break;
    if (lift) {
      lift->update();
    }
    if (!focus && sel >= 0)
      child[sel]->update();
    else if (focus && hsel >= 0)
	h_child[hsel]->update();
    fglayer_footer_update();
    if (header)
	for (int n=0; header[n].label; n++)
	    h_child[n]->update();

    if (jmoved) { // joystick moved, handle auto-repeat...
      if (!phase_repeat) {
        if ((update_count - timer)*fpsm.rateticks >= repeat_delay) {
	  phase_repeat = 1;
	  produce_joystick_event();
	  timer = update_count;
        }
      } else if ((update_count - timer)*fpsm.rateticks >= repeat_interval) {
	produce_joystick_event();
	timer = update_count;
      }
    }
    update_count++;
    // if we want to handle animations on the bg layer 1 day...
    // update_bg_layer();
    if (top != oldtop)
      redraw_fg_layer();
    else if (!focus && sel != oldsel) {
      update_fg_layer(oldsel);
      if (sel >= 0 && child[sel]->can_draw_selection())
	update_fg_layer(sel);
    } else if (focus && hsel != oldsel) {
      update_header_entry(oldsel);
      if (hsel >= 0 && h_child[hsel]->can_draw_selection())
	update_header_entry(hsel);
    } else if (!focus && nb_disp_items && (sel >= top && sel <= menu_disp[top+rows-1])) {
      if (child[sel]->can_draw_selection())
       	update_fg_layer(sel);
    } else if (focus && hsel >= 0) {
	if (h_child[hsel]->can_draw_selection())
	    update_header_entry(hsel);
    } else if ((sdl_screen->flags & SDL_DOUBLEBUF) || (emulate_mouse_cursor && cursor)) {
      // If we are using double buffering, then update fg layer even if nothing
      // changes, or we wouldn't be able to see the mouse moving !!!
      update_fg_layer(top);
    }
    SDL_framerateDelay(&fpsm);
  }
  if (parent) {
    // restore the screen
    parent->draw();
    caller = parent;
  } else {
    clear_surface(sdl_screen);
    if ( sdl_screen->flags & SDL_DOUBLEBUF )
	SDL_Flip(sdl_screen);
    else
	SDL_UpdateRect(sdl_screen,0,0,0,0);
    caller = NULL;
  }
  gui_level--;
  if (!--gui_init) {
    SDL_ShowCursor(SDL_DISABLE);
    SDL_EnableKeyRepeat(0,0);
    SDL_EnableUNICODE(unicode);
    release_inputs();
    print_debug("calling ScreenChange on gui_init==0 (gui execute)\n");
    ScreenChange();
    if (!raine_cfg.req_pause_game)
	sa_unpause_sound();
  }
  parent = NULL; // to be on the safe side
}

// TBitmap_menu : a menu with a bitmap on top of it
// Is it better to handle bitmaps with a child of TMenu or with a type
// of menu_item ???
// For now it seems that it's easier to do it with a child, maybe I'll have
// to change my mind later

TBitmap_menu::TBitmap_menu(char *my_title, menu_item_t *mymenu, char *bitmap_path) :
  TMenu(my_title,mymenu)
{
  bmp = IMG_Load(bitmap_path);
  if (!bmp) {
    printf("TBitmap_menu: couldn't load %s\n",bitmap_path);
  }
}

TBitmap_menu::~TBitmap_menu() {
  if (bmp) {
    SDL_FreeSurface(bmp);
  }
}

void TBitmap_menu::setup_font(unsigned int len_frame) {
  TMenu::setup_font(len_frame);
  if (bmp) {
    if (bmp->w+2*HMARGIN > width_max)
      width_max = bmp->w+2*HMARGIN;
    int h;
    h = (sdl_screen->h-bmp->h-2)/(nb_items + 4 + 6); // margin
    if (h < font->get_font_height() && h < font->get_font_width()) {
      delete font;
      font = new TFont_ttf(h);
      compute_width_from_font();
    }
  }
}

void TBitmap_menu::display_fglayer_header(int &y) {
  if (bmp) {
    SDL_Rect dest;
    dest.x = (fg_layer->w - bmp->w)/2;
    dest.y = y;

    SDL_BlitSurface(bmp,NULL, fg_layer,&dest);
    y += bmp->h+2;
  }
}

void TBitmap_menu::skip_fglayer_header(int &y) {
  if (bmp) {
    y += bmp->h+2;
  }
}

// TDialog : a menu without frames (top & bottom) but with a title bar

TDialog::TDialog(char *my_title, menu_item_t *mymenu) :
  TMenu(my_title,mymenu)
{ htitle = 0;
}

void TDialog::setup_font(unsigned int len_frame) {
  TMenu::setup_font(len_frame);
  if (*title) {
    int w;
    font->dimensions(title,&w,&htitle);
    w+=2; htitle+=2; // with border
    if (w > width_max) {
      width_max = w;
    }
    int htotal = (sdl_screen->h-htitle)/(nb_items + 4 + 6); // margin
    if (rows)
      htotal = (sdl_screen->h-htitle)/rows;
    if (htotal < font->get_font_height() && htotal < font->get_font_width()) {
      delete font;
      font = new TFont_ttf(htotal,font_name);
      compute_width_from_font();
    }
  }
}

void TDialog::display_fglayer_header(int &y) {
  if (!parent && !bg_layer) {
    if (!color_format) color_format = sdl_screen->format;
    if (display_cfg.bpp == 8)
      // apparently it's better to force the mask when creating an 8bpp surface
      // risks of crashes otherwise !!!
      bg_layer = SDL_CreateRGBSurface(SDL_SWSURFACE,sdl_screen->w,sdl_screen->h,display_cfg.bpp,0xff000000,0xff0000,0xff00,0x0);
    else
      bg_layer = SDL_CreateRGBSurface(SDL_SWSURFACE,sdl_screen->w,sdl_screen->h,display_cfg.bpp,color_format->Rmask,color_format->Gmask,color_format->Bmask,color_format->Amask);
    if (!bg_layer) {
      printf("erreur création bg_layer\n");
      exit(1);
    }
    SDL_BlitSurface(sdl_screen,NULL,bg_layer,NULL);
  }
  if (*title) {
    boxColor(fg_layer,1,1,fg_layer->w-2,htitle-1,bg_dialog_bar);
    font->surf_string_tr(fg_layer,1,1,title,fg);
    rectangleColor(fg_layer,0,0,fg_layer->w-1,htitle,fg);
    y += htitle + 2;
  }
  TMenu::display_fglayer_header(y);
}

void TDialog::skip_fglayer_header(int &y) {
  if (*title) {
    y += htitle + 2;
  }
}

void TDialog::draw_frame(SDL_Rect *r) {
  if (!font) setup_font(0);
  work_area.x = 0;
  work_area.y = 0;
  work_area.w = sdl_screen->w;
  work_area.h = sdl_screen->h-40;
}

void TDialog::update_bg_layer(SDL_Rect *region) {
  if (parent) {
    parent->redraw(region);
  } else {
    TMenu::update_bg_layer(region);
  }
}

// TMenuMultiCol : a multi colomn version of TMenu

TMenuMultiCol::TMenuMultiCol(char *my_title, menu_item_t *mymenu, int nbcol, char **mycols) : TMenu(my_title,mymenu) {
  nb_cols = nbcol;
  cols = mycols;
  colpos = (int*)malloc(sizeof(int)*nb_cols);
}

TMenuMultiCol::~TMenuMultiCol() {
  if (colpos) free(colpos);
}

void TMenuMultiCol::adjust_len_max_options(unsigned int &len_max_options) {
  len_max_options += nb_cols;
  for (int c=0; c< nb_cols; c++) {
    int len_max = 0;
    for (int n=0; n<nb_disp_items; n++) {
      int index = menu_disp[n];
      int len = strlen(cols[index*nb_cols+c]);
      if (len > len_max) {
	len_max = len;
      }
    }
    len_max_options += len_max;
  }
}

void TMenuMultiCol::compute_width_from_font() {
  TMenu::compute_width_from_font();
  for (int c=0; c<nb_cols; c++) {
    colpos[c] = width_max;
    int wmax = 0;
    for (int n=0; n<nb_disp_items; n++) {
      int index = menu_disp[n],w,h;
      font->dimensions(cols[index*nb_cols+c],&w,&h);
      if (w > wmax) {
	wmax = w;
      }
    }
    width_max += wmax+HMARGIN;
  }
  width_max += HMARGIN;
  if (width_max > work_area.w) width_max = work_area.w;
}

void TMenuMultiCol::disp_menu(int n,int y,int w,int h) {
  // Just need to add the columns after the normal line
  TMenu::disp_menu(n,y,w,h);
  for (int c=0; c<nb_cols; c++) {
    if (n == sel) {
      int selcolor = compute_selcolor();
      font->surf_string(fg_layer,colpos[c],y,cols[n*nb_cols+c],bg,selcolor,w-colpos[c]);
    } else
      font->surf_string_tr(fg_layer,colpos[c],y,cols[n*nb_cols+c],fg,w-colpos[c]);
  }
}

// TMenuPostCb

void TMenuPostCb::adjust_len_max_options(unsigned int &len_max_options) {
    if (*legend)
	len_max_options += strlen(legend);
    else
	len_max_options++;
}

void TMenuPostCb::compute_width_from_font() {
  TMenu::compute_width_from_font();
  int h;
  pos_cb = width_max;
  font->dimensions("X",&wcb,&h);
  if (*legend) {
      int w;
      font->dimensions(legend,&w,&h);
      width_max += w+HMARGIN*2;
  } else
      width_max += wcb+HMARGIN*2;
}

int TMenuPostCb::can_be_selected(int n) {
    if (n == 0)
	return 0;
    return 1;
}

void TMenuPostCb::disp_menu(int n,int y,int w,int h) {
  // Just need to add the columns after the normal line
  TMenu::disp_menu(n,y,w,h);
  if (n == 0) {
      font->surf_string_tr(fg_layer,pos_cb,y,legend,fg);
  } else {
      int x = pos_cb + HMARGIN;
      rectangleColor(fg_layer,x,y,x+wcb,y+h-1,fg);
      if (cb[n]) {
	  lineColor(fg_layer,x,y,x+wcb,y+h-1,mymakecol(0,255,0));
	  lineColor(fg_layer,x+wcb,y,x,y+h-1,mymakecol(0,255,0));
      }
  }
}

void TMenuPostCb::handle_key(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE)
      cb[sel] ^= 1;
  else
      TMenu::handle_key(event);
}

void TMenuPostCb::handle_button(SDL_Event *event, int index) {
    if (event->type == SDL_MOUSEBUTTONUP ) {
	switch(event->button.button) {
	case 1:
	    if (event->button.x >= pos_cb + HMARGIN &&
		    event->button.x < pos_cb + HMARGIN + wcb) {
		cb[index] ^= 1;
		return;
	    }
	default:
	    TMenu::handle_button(event,index);
	}
    }
}

