#include "widget.h"
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "sdl/compat.h"

/* Basic widgets for TMenu, see menu.cpp comments at the top for an
 * introduction to the gui.
 *
 * These basic widgets are :
 * TStatic : a simple string in the menu, eventually linked to a command
 * TOptions : a title associated with a list of values (either strings or
 * numbers, see the definition of menu_item_t in menu.cpp.
 * TProgressBar : a progression bar used in raine to load roms.
 */

static int ansi_color[] =
{
  0,
  0xff0000, // red
  0x00ff00, // green
  0xffff00, // yellow
  0x0000ff, // blue
  0xff00ff, // magenta
  0x00ffff, // cyan
  0xffffff, // white
};

static void process_piece(TFont *font, char *s, int *width, int *height) {
  int w0,h0;
  font->dimensions(s,&w0,&h0);
  *width += w0;
  if (*height < h0) *height = h0;
}

static void ansi_font_dim(TFont *font, char *str, int *width, int *height) {
  char *s = str,*old = str;
  *width = 0; *height = 0;
  while ((s = strstr(old,"\E["))) {
    char oldc = *s;
    *s = 0;
    process_piece(font,old,width,height);
    *s = oldc;
    while (*s != 'm' && *s != 0)
      s++;
    if (*s == 'm') {
      old = s+1;
    } else
      return;
  }
  process_piece(font,old,width,height);
}

/* The curse with this function is that it cas only tell if a string is NOT
 * utf8. It's what is really annoying about utf8 anyway...
 * So with it most english strings will be seen as utf8.
 * I'll keep calling it for now anyway just in case but maybe it would be best
 * to assume everything is utf8 now and never call it ? */
int test_utf(const char *s) {
    if (!s) return 0;

    // This code is taken from http://stackoverflow.com/questions/1031645/how-to-detect-utf-8-in-plain-c

    const unsigned char * bytes = (const unsigned char *)s;
    while(*bytes)
    {
	if( (// ASCII
		    // use bytes[0] <= 0x7F to allow ASCII control characters
		    bytes[0] == 0x09 ||
		    bytes[0] == 0x0A ||
		    bytes[0] == 0x0D ||
		    (0x20 <= bytes[0] && bytes[0] <= 0x7E)
	    )
	  ) {
	    bytes += 1;
	    continue;
	}

	if( (// non-overlong 2-byte
		    (0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
		    (0x80 <= bytes[1] && bytes[1] <= 0xBF)
	    )
	  ) {
	    bytes += 2;
	    continue;
	}

	if( (// excluding overlongs
		    bytes[0] == 0xE0 &&
		    (0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
		    (0x80 <= bytes[2] && bytes[2] <= 0xBF)
	    ) ||
		(// straight 3-byte
		 ((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
		  bytes[0] == 0xEE ||
		  bytes[0] == 0xEF) &&
		 (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
		 (0x80 <= bytes[2] && bytes[2] <= 0xBF)
		) ||
		(// excluding surrogates
		 bytes[0] == 0xED &&
		 (0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
		 (0x80 <= bytes[2] && bytes[2] <= 0xBF)
		)
	  ) {
	    bytes += 3;
	    continue;
	}

	if( (// planes 1-3
		    bytes[0] == 0xF0 &&
		    (0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
		    (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
		    (0x80 <= bytes[3] && bytes[3] <= 0xBF)
	    ) ||
		(// planes 4-15
		 (0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
		 (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
		 (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
		 (0x80 <= bytes[3] && bytes[3] <= 0xBF)
		) ||
		(// plane 16
		 bytes[0] == 0xF4 &&
		 (0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
		 (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
		 (0x80 <= bytes[3] && bytes[3] <= 0xBF)
		)
	  ) {
	    bytes += 4;
	    continue;
	}

	return 0;
    }

    return 1;
}

TStatic::TStatic(menu_item_t *my_menu) {
    menu = my_menu;
    is_utf = test_utf(menu->label);
}

int TStatic::get_len() {
  return strlen(menu->label);
}

int TStatic::can_be_selected() {
  if (menu->menu_func)
    return 1;
  return 0;
}

int TStatic::can_draw_selection() {
  // Tells if we want to be redraw all the time to update the background
  // when selection is upon us (default = yes always)
  return 1;
}

int TStatic::get_len_max_options() {
  return 0;
}

int TStatic::get_width(TFont *font) {
  int w,h;
  font->set_utf(is_utf);
  ansi_font_dim(font,(char*)menu->label,&w,&h);
  return w;
}

int TStatic::get_width_max_options(TFont *font) {
    int w,h;
    font->dimensions("W",&w,&h);
  return w*get_len_max_options();
}

int TStatic::get_list_index() {
  return 0;
}

int TStatic::get_height(TFont *font) {
  int w,h;
  ansi_font_dim(font,(char*)menu->label,&w,&h);
  return h;
}

void TStatic::disp(SDL_Surface *sf, TFont *font, int x, int y, int w, int h,
  int myfg, int mybg, int xoptions) {
  int fg = myfg, bg = mybg;
  char *s = (char*)menu->label;
  char *old = s;
  font->set_utf(is_utf);
  while ((s = strstr(s,"\E["))) {
    if (s > menu->label) {
      *s = 0;
      int w,h;
      font->dimensions(old,&w,&h);
      font->surf_string(sf,x,y,old,fg,bg,w);
      x += w;
      *s = 27;
    }
    int col = 0;
    s+=2;
    do {
      while (*s >= '0' && *s <= '9') {
	col = (col*10) + (*s - '0');
	s++;
      }
      if (*s == 'm' || *s == ';') {
	if (col >= 30 && col <= 37)
	  fg = (ansi_color[col - 30]<<8) | 255;
	else if (col >= 40 && col <= 47)
	  bg = (ansi_color[col - 40]<<8) | 255;
	else if (col == 1)
	    font->set_style(TTF_STYLE_BOLD);
	else if (col == 0) {
	  fg = myfg;
	  bg = mybg;
	  font->set_style(TTF_STYLE_NORMAL);
	} else if (col == 39)
	  fg = myfg;
	else if (col == 49)
	  bg = mybg;
      }
      s++;
      old = s;
    } while (s[-1] != 'm' && s[-1] != 0);
  }

  font->surf_string(sf,x,y,old,fg,bg,w);
}

void TStatic::next_list_item() {}
void TStatic::prev_list_item() {}

void TProgressBar::disp(SDL_Surface *s, TFont *font, int x, int y, int w,int h,
  int fg, int bg, int xoptions) {
  x = (s->w-w)/2;
  rectangleColor(s,x,y,x+w-1,y+h-1,mymakecol(255,255,255));
  int pcent;
  int prev = x+1;
  for (pcent=5; pcent<=*(menu->value_int); pcent += 5) {
    int cur = x+(pcent * (w-2)/100);
    int color = 255*pcent/100;
    boxColor(s,prev,y+1,cur,y+h-2,mymakecol(color,0,0));
    prev = cur;
  }
  char buff[8];
  sprintf(buff,"%d %%",*(menu->value_int));
  int myw,myh;
  font->dimensions(buff,&myw,&myh);
  font->surf_string_tr(s,x+(w-myw)/2,y+1,buff,mymakecol(255,255,255));
}

int TProgressBar::get_width(TFont *font) {
  return sdl_screen->w/2;
}

int TProgressBar::get_height(TFont *font) {
  int h = TStatic::get_height(font);
  h+=2;
  return h;
}

int TOptions::get_list_index() {
  // return the index of the selected value in the list
  int index;
  for (index=0; index<menu->values_list_size; index++) {
    if (menu->values_list[index] == *(menu->value_int))
      break;
  }
  return index;
}

int TOptions::get_len_max_options() {
  unsigned int len_max_options = 0;
  if (menu->values_list_label[0] &&
	  !strcmp(menu->values_list_label[0],"hidden"))
      return 0;
  if (menu->value_int && menu->values_list_size) {
      for (int l=0; l<menu->values_list_size; l++) {
	  unsigned int len2;
	  if (!menu->values_list_label[l]) {
	      char s2[20];
	      sprintf(s2,"%d",menu->values_list[l]);
	      len2 = strlen(s2);
	  } else
	      len2 = strlen(menu->values_list_label[l]);
	  if (len2 > len_max_options) {
	      len_max_options = len2;
	  }
      }
  }
  return len_max_options;
}

int TOptions::get_width_max_options(TFont *font) {
  int w,h,width_max_options = 0;
  if (menu->values_list_label[0] &&
	  !strcmp(menu->values_list_label[0],"hidden"))
      return 0;
  if (menu->value_int && menu->values_list_size) {
      for (int l=0; l<menu->values_list_size; l++) {
	  if (!menu->values_list_label[l]) {
	      char s2[20];
	      sprintf(s2,"%d",menu->values_list[l]);
	      font->dimensions(s2,&w,&h);
	  } else
	      font->dimensions(menu->values_list_label[l],&w,&h);
	  if (w > width_max_options)
	      width_max_options = w;
      }
  }
  return width_max_options;
}

void TOptions::disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions) {
  TStatic::disp(s,font,x,y,w,h,fg,bg,xoptions);
  if (menu->values_list_label[0] &&
	  !strcmp(menu->values_list_label[0],"hidden"))
      return;

  int index = 0;
  if (menu->values_list_size != 3 || menu->values_list_label[0]) {
    index = get_list_index();
    if (index >= menu->values_list_size) { // not found !
      // It isn't supposed to happen, but I'd better handle it anyway, just
      // in case
      index = 0;
      *(menu->value_int) = menu->values_list[0];
    }
  }
  char *disp_string,buff[10];
  if (menu->values_list_label[index]) {
    disp_string = menu->values_list_label[index];
  } else {
    // no labels -> display the int value directly
    sprintf(buff,"%d",*(menu->value_int));
    disp_string = buff;
  }
  font->surf_string(s,xoptions,y,disp_string,fg,bg,w);
}

/* About cycling of next_list_item and prev_list_item : this is mandatory with
 * the mouse, or it would be impossible to return to the start of the list
 * (only 1 button to browse since the right button is to exit and the middle
 * one is not convinient at all for this */
void TOptions::next_list_item() {
  if (menu->values_list_size == 3 &&
	  (!menu->values_list_label[0] ||
	   !strcmp(menu->values_list_label[0],"hidden"))) {
    // special interval list
    *(menu->value_int) += menu->values_list[2];
    if (*(menu->value_int) > menu->values_list[1])
      *(menu->value_int) = menu->values_list[0];
  } else {
    int index = get_list_index();
    if (index < menu->values_list_size - 1)
      index++;
    else
      index = 0; // cycling
    *(menu->value_int) = menu->values_list[index];
  }
}

void TOptions::prev_list_item() {
  if (menu->values_list_size == 3 &&
	  (!menu->values_list_label[0] ||
	   !strcmp(menu->values_list_label[0],"hidden"))) {
    // special interval list
    *(menu->value_int) -= menu->values_list[2];
    if (*(menu->value_int) < menu->values_list[0])
      *(menu->value_int) = menu->values_list[1];
  } else {
    int index = get_list_index();
    if (index > 0)
      index--;
    else
      index = menu->values_list_size - 1; // cycling
    *(menu->value_int) = menu->values_list[index];
  }
}

int TOptions::handle_key_buff(char *buff) {
    // If we are on a list of values, then use the keys to browse
    // the list
    int index = strlen(buff);
    int n;
    for (n=0; n<menu->values_list_size; n++) {
	if (menu->values_list_label[n] &&
		!strnicmp(menu->values_list_label[n],buff,index))
	    break;
    }
    if (n<menu->values_list_size) { // found
	*(menu->value_int) = n;
	return 1;
    }
    return 0;
}
