#include "profile.h"
#include "conf-sound.h"
#include "../gui/menu.h"
#include "about.h"
#include <SDL_image.h>
#include "raine.h"
#include "version.h"
#include "files.h" // get_shared
#include "history.h"
#include "sdl/dialogs/messagebox.h"
#include "gui/tfont.h"
#include "control.h"
#include "sdl/control_internal.h"
#if HAS_NEO
#include <SDL_sound.h>
#endif
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "games.h"

class TAbout_menu : public TBitmap_menu
{
  private:
    UINT8 *CYC;
    int palette_size;

  public:
  TAbout_menu(char *mytitle, menu_item_t *myitem, char *path);
  ~TAbout_menu();
  virtual void update_fg_layer(int nb_to_update);
};

class TAbout : public TMenu
{
  public:
    TAbout(char *my_title, menu_item_t *mymenu,char *myfont = NULL,
      int myfg=-1, int mybg=-1,int myfg_frame=-1,int mybg_frame=-1,
      int to_translate=1) : TMenu(my_title,mymenu,myfont,myfg,mybg,myfg_frame,
	  mybg_frame,to_translate)
    { cycle_up = cycle_down = 0; }
    void reset_top() {
	// top = 0 always with this dialog, ignore any eventual url at the bottom
	top = 0;
    }
};

// A class to unify all the drawing functions for the command.dat symbols
// it will allow to share the scaling data without making it permanent
class TSketcher
{
    private:
	SDL_Surface *sf;
	int ox,oy,w,h,mw,mh;
	int filled_poly;
    public:
	TSketcher(SDL_Surface *_sf,int _ox,int _oy, int _w,int _h, int _mw, int _mh) {
	    // mw & mh : matrix width and height (original drawing)
	    sf = _sf;
	    ox = _ox; oy = _oy; w=_w; h=_h; mw=_mw; mh = _mh;
	}
	void set_filled_poly(int filled) {
	    filled_poly = filled;
	}
	void polytab(int nb,Sint16 *tabx,Sint16 *taby, int col);
	void poly(int col, ...);
	void lineC(int x1,int y1,int x2,int y2,int coul);
};

void TSketcher::polytab(int nb,Sint16 *tabx,Sint16 *taby, int col)
{
    int n;
    for (n=0; n<nb; n++) {
	tabx[n] = tabx[n]*w/mw+ox;
	taby[n] = taby[n]*h/mh+oy;
    }
    if (filled_poly)
	filledPolygonColor(sf,tabx,taby,nb,col);
    else
	polygonColor(sf,tabx,taby,nb,col);
}

void TSketcher::poly(int col, ...)
{
    va_list ap;
#define PMAX 16
    Sint16 tabx[PMAX],taby[PMAX];
    va_start(ap,col);
    int x,y;
    int nb = 0;
    do {
	x = va_arg(ap,int);
	y = va_arg(ap,int);
	if (x >= 0) {
	    if (nb == PMAX) {
		printf("poly overflow !\n");
		exit(1);
	    }
	    tabx[nb] = x;
	    taby[nb++] = y;
	}
    } while (x >= 0);
    va_end(ap);
    polytab(nb,tabx,taby,col);
}

void TSketcher::lineC(int x1,int y1,int x2,int y2,int coul)
{
    x1 = x1*w/mw+ox;
    y1 = y1*h/mh+oy;
    x2 = x2*w/mw+ox;
    y2 = y2*h/mh+oy;
    lineColor(sf,x1,y1,x2,y2,coul);
}

static void mirror(int nb, Sint16 *tab, Sint16 *res)
{
    int min = 1000, max = 0;
    int n;
    for (n=0; n<nb; n++) {
	if (tab[n] < min) min = tab[n];
	if (tab[n] > max) max = tab[n];
    }
    for (n=0; n<nb; n++)
	res[n] = (max+min)-tab[n];
}

void TMoveStatic::disp(SDL_Surface *sf, TFont *font, int x, int y, int w, int h,
  int myfg, int mybg, int xoptions) {
    int fg = myfg, bg = mybg;
    char buff[256];
    /* Copy the string to allow to modify it without problem */
    strcpy(buff,menu->label);
    char *s = buff;
    char *old = s;
    int old_min = min_font_size;
    min_font_size = 1;
    font->set_utf(is_utf);
    int white = mymakecol(255,255,255);
    // All the translations are taken from http://home.comcast.net/~plotor/command.html
    while (*s) {
	if (*s != '_' && *s != '^' && *s != '@') {
	    s++;
	    continue;
	}
	char pre = *s;
	if (s > old) {
	    // Eventually display what's before
	    *s = 0;
	    int w,h;
	    font->dimensions(old,&w,&h);
	    font->surf_string(sf,x,y,old,fg,bg,w);
	    x += w;
	    *s = pre;
	}
	s++;
	font->dimensions("mp",&w,&h);
	int col = 0;
	char str[4];
	TFont *f0 = NULL;
	str[0] = *s;
	str[1] = 0;
	TSketcher *d = new TSketcher(sf,x,y,w,h,10,9);
	if (pre == '_') {
	    switch(*s) {
	    case 'A':
	    case 'a':
	    case 'S':
	    case '5':	col = mymakecol(255,64,64); break;
	    case 'B':
	    case 'b':	col = mymakecol(255,238,0); break;
	    case 'C':
	    case 'c':	col = mymakecol(0,255,64); break;
	    case 'D':
	    case 'd':	col = mymakecol(0,170,255); break;
	    case 'P':
	    case 'e':	col = mymakecol(255,0,170); break;
	    case 'K':
	    case 'Z':
	    case 'f':	col = mymakecol(170,0,255); break;
	    case 'g': col = mymakecol(0,255,204); break;
	    case 'i': col = mymakecol(255,160,0); break;
	    case 'G': col = mymakecol(0,170,255); break;
	    case 'H':
	    case 'h': col = mymakecol(255,0,255); break;
	    case 'j': col = mymakecol(190,190,190); break;
	    }
	    if (*s >= 'a' && *s <= 'j')
		sprintf(str,"%d",*s-'a'+1);
	    else if (*s == 'L')
		sprintf(str,">>"); // too many drawings !!!
	    else if (*s == 'M')
		sprintf(str,"<<");
	    else if (*s == 'X')
		sprintf(str,"TAP");
	    else if (*s == '^')
		sprintf(str,"AIR");
	    else if (*s == '?')
		sprintf(str,"DIR");
	    else if (*s == 'S')
		sprintf(str,"St"); // tss...
	    else if (*s == '.')
		sprintf(str,"...");

	    d->set_filled_poly(1);

	} else if (pre == '^') {
	    d->set_filled_poly(0);
	    switch (*s) {
	    case 'S':
	    case 'E': col = mymakecol(255,238,0); break;
	    case 's':
	    case 'F': col = mymakecol(255,160,0); break;
	    case 'G':	col = mymakecol(255,64,64); break;
	    case 'H': col = mymakecol(190,190,190); break;
	    case 'I': col = mymakecol(0,255,204); break;
	    case 'J':	col = mymakecol(0,170,255); break;
	    case 'T':	col = mymakecol(170,0,255); break;
	    case 'W':
	    case 'U':	col = mymakecol(255,0,170); break;
	    case 'V':	col = mymakecol(170,0,255); break;
	    }
	    if (*s >= 'E' && *s <= 'J') {
		if (has_input(KB_DEF_P1_B6)) {
		    // Street fighter games
		    char *keys[] = { "lp","mp","sp","lk","mk","sk" };
		    sprintf(str,"%s",keys[*s-'E']);
		} else
		    sprintf(str,"b%d",*s-'E'+1); // button n for other games
	    } else if (*s == 'T')
		sprintf(str,"3K");
	    else if (*s == 'U')
		sprintf(str,"3P");
	    else if (*s == 'V')
		sprintf(str,"2K");
	    else if (*s == 'W')
		sprintf(str,"2P");
	    else if (*s == 'S')
		sprintf(str,"SE"); // ?!
	    else if (*s == 'M')
		sprintf(str,"MAX");
	} else if (pre == '@') {
	    if (!strncmp(s,"W-button",8)) {
		sprintf(str,"W");
		col = mymakecol(255,238,0);
		s += 7;
	    }
	}

	// I finally keep a constant base width to have all the circles of the
	// same size...
	// font->dimensions(str,&w,&h);
	// w += 2; // some small margin
	if (col)
	    filledEllipseColor(sf, x+w/2, y+h/2, w/2,h/2, col);

	if (strlen(str) > 2) {
	    // Try to find a font size which fits in this space !
	    f0 = font;
	    int h = f0->get_font_height()/2;
	    do {
		font = new TFont_ttf(h,"VeraMono.ttf");
		if (h <= 3) break;
		int w0,h0;
		font->dimensions(str,&w0,&h0);
		if (w0 > w) {
		    h--;
		    delete font;
		    font = NULL;
		}
	    } while (!font);
	}
	// The coordinates below are supposed to be on & 10x9 matrix, except
	// that the picture I am using has clearly been resized and so it's
	// only an approximation...

	// For the arrows they are rotated and mirrored, so I do the rotation/
	// mirror instead of risking more errors with more coordinates...
	Sint16 kx[13] = {1,3,6,4,4,7,7,9,9,7,4,2,2};
	Sint16 ky[13] = {3,1,3,3,5,5,3,3,5,7,7,5,3};
	Sint16 mkx[13],mky[13];
	mirror(13,kx,mkx);
	mirror(13,ky,mky);

	Sint16 ox[10] = {1,3,3,5,5,7,7,5,3,3};
	Sint16 oy[10] = {6,4,5,5,1,1,5,7,7,8};
	Sint16 mox[10],moy[10];
	mirror(10,ox,mox);
	mirror(10,oy,moy);

	Sint16 wx[16] = {3,1,1,3,6,8,8,10,7,5,7,5,3,3,5,4};
	Sint16 wy[16] = {8,6,3,1,1,3,5,5, 7,5,5,3,3,6,7,8},mwx[16],mwy[16];
	mirror(16,wx,mwx);
	mirror(16,wy,mwy);

	if (pre == '@') {
	    // Very special case, W Button, 1 letter.
	    font->surf_string(sf,x+w/4,y,str,(col ? 0 : fg),bg,w);
	    goto end_loop;
	}

	if (*s == '1')
	    d->poly(white,
		    6,1,
		    2,6,
		    1,5,
		    1,8,
		    4,8,
		    3,7,
		    8,2,
		    -1,-1);
	else if (*s == '2')
	    d->poly(white,
		    2,1,
		    2,6,
		    1,6,
		    3,8,
		    5,6,
		    4,6,
		    4,1,
		    -1,-1);
	else if (*s == '3')
	    d->poly(white,
		    0,2,
		    5,8,
		    4,9,
		    8,9,
		    8,5,
		    7,6,
		    3,1,
		    -1,-1);
	else if (*s == '4')
	    d->poly(white,
		    3,2,
		    0,5,
		    3,7,
		    3,6,
		    9,6,
		    9,4,
		    3,4,
		    -1,-1);
	else if (*s == '6')
	    d->poly(white,
		    1,4,
		    6,4,
		    6,2,
		    9,5,
		    6,7,
		    6,6,
		    1,6,
		    -1,-1);
	else if (*s == '7')
	    d->poly(white,
		    1,1,
		    1,5,
		    2,4,
		    8,9,
		    9,7,
		    4,2,
		    5,1,
		    -1,-1);
	else if (*s == '8')
	    d->poly(white,
		    2,8,
		    2,3,
		    1,3,
		    3,1,
		    5,3,
		    4,3,
		    4,8,
		    -1,-1);
	else if (*s == '9')
	    d->poly(white,
		    8,1,
		    8,5,
		    7,4,
		    1,9,
		    0,7,
		    5,2,
		    4,1,
		    -1,-1);
	else if (*s == 'k')
	    d->polytab(13,kx,ky,white);
	else if (*s == 'm') // horizontal mirror of k (10-x)
	    d->polytab(13,mkx,ky,white);
	else if (*s == 'l') // vertical mirror of m (8-y)
	    d->polytab(13,mkx,mky,white);
	else if (*s == 'n') // horizontal mirror of l (10-x)
	    d->polytab(13,kx,mky,white);
	else if (*s == 'o')
	    d->polytab(10,ox,oy,white);
	else if (*s == 'p')
	    d->polytab(10,moy,ox,white);
	else if (*s == 'q')
	    d->polytab(10,mox,moy,white);
	else if (*s == 'r')
	    d->polytab(10,oy,mox,white);
	else if (*s == 's' && pre == '_')
	    d->polytab(10,mox,oy,white);
	else if (*s == 't')
	    d->polytab(10,oy,ox,white);
	else if (*s == 'u')
	    d->polytab(10,ox,moy,white);
	else if (*s == 'v')
	    d->polytab(10,moy,mox,white);
	else if (*s == 'w')
	    d->polytab(16,wx,wy,white);
	else if (*s == 'x')
	    d->polytab(16,mwx,mwy,white);
	else if (*s == 'y')
	    d->polytab(16,wx,mwy,white);
	else if (*s == 'z')
	    d->polytab(16,mwx,wy,white);
	else if (*s == 'Q')
	    d->poly(white,
		    1,1,
		    1,3,
		    3,3,
		    3,4,
		    1,6,
		    7,6,
		    7,7,
		    9,5,
		    7,3,
		    7,4,
		    4,4,
		    4,3,
		    6,1,
		    -1,-1);
	else if (*s == 'R') // horiz mirror of Q (10-x)
	    d->poly(white,
		    9,1,
		    9,3,
		    7,3,
		    7,4,
		    9,6,
		    3,6,
		    3,7,
		    1,5,
		    3,3,
		    3,4,
		    6,4,
		    6,3,
		    4,1,
		    -1,-1);
	else if (*s == '-' && pre == '_') { // not used for any raine game afaik
	    d->lineC(3,1,7,1,white);
	    d->lineC(3,5,5,3,white);
	    d->lineC(5,3,7,5,white);
	    d->lineC(5,3,5,7,white);
	} else if (*s == '-' && pre == '^') {
	    d->lineC(1,4,6,4,white);
	    d->lineC(6,4,4,2,white);
	    d->lineC(6,4,4,6,white);
	    d->lineC(8,2,8,6,white);
	} else if (*s == '=' && pre == '^') {
	    d->lineC(1,4,6,4,white);
	    d->lineC(1,4,3,2,white);
	    d->lineC(1,4,3,6,white);
	    d->lineC(8,2,8,6,white);
	} else if (*s == '`' && pre == '_') {
	    filledCircleColor(sf, x+w/2, y+h/2, w/10, white);
	} else if (str[1] == 0) {
	    int ws,hs;
	    font->dimensions(str,&ws,&hs);
	    font->surf_string(sf,x+(w-ws)/2,y,str,(col ? 0 : fg),bg,w);
	} else {
	    int ws,hs;
	    font->dimensions(str,&ws,&hs);
	    font->surf_string(sf,x+(w-ws)/2,y,str,(col ? 0 : fg),bg,w);
	}
	if (f0) {
	    delete font;
	    font = f0;
	}
	delete d;

end_loop:
	s++;
	old = s;
	x += w;
    }

    if (*old)
	font->surf_string(sf,x,y,old,fg,bg,w);
    min_font_size = old_min;
}

int TMoveStatic::get_width(TFont *font) {
    // Now that commands use soem maximum width (string for mp), there can be
    // quite a big difference with the width of 2 random characters when there
    // are 3 buttons to display in the controls, so this function becomes
    // necessary...
    int w = TStatic::get_width(font);
    const char *s = menu->label;
    int w0,h0;
    font->dimensions("mp",&w0,&h0);
    while (*s != '_' && *s != '^' && *s) {
	s++;
	if (*s) {
	    char buf[3];
	    strncpy(buf,s,2);
	    buf[2] = 0;
	    int w1,h1;
	    font->dimensions(buf,&w1,&h1);
	    w += w0-w1;
	    s++;
	}
    }
    return w;
}

class TMoves_menu : public TMenu
{
    public:
	TMoves_menu(char *mytitle, menu_item_t *myitem) :
	    TMenu(mytitle,myitem,NULL,-1, -1,-1,-1, /* to_translate */ 0)
	{
	    font_name = "VeraMono.ttf";
	}
	void create_child(int n) {
	    if (!menu[n].value_int)
		child[n] = new TMoveStatic(&menu[n]);
	    else
		TMenu::create_child(n);
	}
};

TAbout_menu::TAbout_menu(char *mytitle, menu_item_t *myitem, char *path) :
  TBitmap_menu(mytitle,myitem,path) {

  /* This cycling color is inspired by the picture given by NoLogic on the
   * rainemu forum. The idea is to allow a cycling of color on any paletized
   * picture, but with a minimum of restrictions : color 0 is *always*
   * transparent, and the unused colors must either be set to black or not
   * appear on the picture */

#define NB_STEPS (palette_size <= 64 ? 128/palette_size : 2) // Number of steps from 1 color to another

   if (bmp == NULL || bmp->format->palette == NULL) {
     CYC = NULL;
     MessageBox(_("Error"),_("No raine logo, or it's a true color bitmap"));
   } else {
     palette_size = bmp->format->palette->ncolors;
     SDL_Color *colors = bmp->format->palette->colors;
     int n;
     for (n=1; n<palette_size; n++) {
       if (colors[n].r == 0 && colors[n].g == 0 && colors[n].b == 0)
	 break;
     }
     palette_size = n;
     // printf("preparation on %d colors, total size %d colorkey %d\n",palette_size,4*palette_size*NB_STEPS*palette_size,bmp->format->colorkey);
     if (bmp->format->colorkey != 0) {
       MessageBox(_("Error"),_("raine_logo.png must have the 1st color of the palette\n(color 0) as transparent"));
       CYC = NULL;
     } else {
       CYC = (UINT8 *)malloc(4*palette_size*NB_STEPS*(palette_size-1));

       int start;
       for (int n=0; n<palette_size-1; n++) {
	 for (int step=0; step<NB_STEPS; step++) {
	   start = step*palette_size*4+(n*NB_STEPS*palette_size*4);
	   int i;
	   for (i=1; i<palette_size-1; i++) {
	     CYC[start+i*4+0] = colors[i].r*((NB_STEPS-1)-step)/(NB_STEPS-1)+
	       colors[(i+1)].r*step/(NB_STEPS-1);
	     CYC[start+i*4+1] = colors[i].g*((NB_STEPS-1)-step)/(NB_STEPS-1)+
	       colors[(i+1)].g*step/(NB_STEPS-1);
	     CYC[start+i*4+2] = colors[i].b*((NB_STEPS-1)-step)/(NB_STEPS-1)+
	       colors[(i+1)].b*step/(NB_STEPS-1);
	   }
	   // last color of the palette takes color 1, not color 0
	   CYC[start+i*4+0] = colors[i].r*((NB_STEPS-1)-step)/(NB_STEPS-1)+
	     colors[(+1)].r*step/(NB_STEPS-1);
	   CYC[start+i*4+1] = colors[i].g*((NB_STEPS-1)-step)/(NB_STEPS-1)+
	     colors[(+1)].g*step/(NB_STEPS-1);
	   CYC[start+i*4+2] = colors[i].b*((NB_STEPS-1)-step)/(NB_STEPS-1)+
	     colors[(+1)].b*step/(NB_STEPS-1);
	 }
	 memcpy(colors,&CYC[start],palette_size*4);
       }
     }
   }
}

TAbout_menu::~TAbout_menu() {
  if (CYC) free(CYC);
}

void TAbout_menu::update_fg_layer(int nb_to_update) {
  static unsigned int tt = 0;
  if (nb_to_update >= 0 && bmp && CYC) {
     int indice = (tt*palette_size*4);
     // printf("indice %d\n",indice);
     if (indice >= (4*palette_size*NB_STEPS*(palette_size-1))) {
       indice = 0;
       tt = 0;
     }
     SDL_SetColors(bmp,(SDL_Color*)&CYC[indice],0,palette_size);
     tt++;
    SDL_Rect dest;

    dest.x = fgdst.x+(fg_layer->w-bmp->w)/2;
    dest.y = fgdst.y+HMARGIN;
    dest.w = bmp->w;
    dest.h = bmp->h;
    SDL_BlitSurface(bmp,NULL,sdl_screen,&dest);
    do_update(&dest);
  }
  TBitmap_menu::update_fg_layer(nb_to_update);
}

static menu_item_t *menu;

static void goto_url(char *url) {
#ifdef RAINE_UNIX
    // at least when using compiz, you can't switch to any other window while
    // in fullscreen mode, so it's better to leave it first !
    if (display_cfg.fullscreen)
	toggle_fullscreen();
#endif
    char cmd[2048];
#ifdef RAINE_UNIX
    // Now use xdg-open instead of www-browser
    // normally xdg-open knows about urls and lanches the best application...
    sprintf(cmd,"xdg-open \"%s\" &",url);
#else
    // windows
    sprintf(cmd,"explorer \"%s\"",url);
#endif
    system(cmd);
}

static int menu_goto_url(int sel) {
    if (menu[sel].values_list_label[0])
	goto_url(menu[sel].values_list_label[0]);
    return 0;
}

static int do_command = 0;

static int about_game(int sel) {
  int nb_lines = 10;
  menu = (menu_item_t *)malloc(sizeof(menu_item_t)*nb_lines);
  int used = 0;
  char *buff;
  if (do_command)
      buff = commands_buff[sel];
  else
      buff = history;

  if (buff) {
    char *s = buff;
    char *nl;
    char previous;
    TFont_ttf *font = new TFont_ttf(min_font_size);
    while ((nl = strchr(s,'\n'))) {
      char *q;
      previous = *nl;
      *nl = 0;
      if ((q=strstr(s,"<a href="))) {
	  /* Basic parsing for urls. We assume everything is lowercase with
	   * only 1 space and not more, and everything on 1 line of text.
	   * I don't was a general html parser here, just something to parse
	   * basic urls */
	  q+=8;
	  char *end;
	  char old;
	  if (*q == '"') {
	      q++;
	      end = strchr(q,'"');
	  } else
	      end = strchr(q,' ');
	  if (end) {
	      old = *end;
	      *end = 0;
	      menu[used].values_list_label[0] = strdup(q);
	      *end = old;
	      q = end+1;
	  } else
	      menu[used].values_list_label[0] = NULL;
	  q = strchr(q,'>');
	  if (q) {
	      q++;
	      end = strstr(q,"</a>");
	      if (end) {
		  old = *end;
		  *end = 0;
		  menu[used].label = strdup(q);
		  *end = old;
		  menu[used].menu_func = &menu_goto_url;
		  goto end_loop;
	      }
	  }
      }
      int w,h;
      font->dimensions(s,&w,&h);
      if (w > sdl_screen->w-50) {
	char start;
	if (s > buff) {
	  start = s[-1];
	  s[-1] = 0;
	}
	char *old = NULL;
	char *sp;
	do {
	    sp = strrchr(s,' ');
	    if (sp) {
		*sp = 0;
		if (old) *old = ' ';
		old = sp;
	    } else
		break;
	    font->dimensions(s,&w,&h);
	} while (w > sdl_screen->w-50);

	int maxlen = strlen(s);
	if (old)
	    *old = ' ';
	if (s>buff) {
	  s[-1] = start;
	}
	if (!sp)
	  sp = old;
	*nl = previous;
	if (sp && sp <= s+maxlen)
	  nl = sp;
	else
	  nl = s+maxlen;

	previous = *nl;
	*nl = 0;
      }
      while ((q = strchr(s,0x92)))
	*q = 0x27; // fix the stupid non standard ' code from krosoft

      menu[used].label = strdup(s);
      menu[used].menu_func = NULL;
      menu[used].values_list_label[0] = NULL;
end_loop:
      menu[used].value_int = NULL;
      used++;
      if (used == nb_lines) {
	nb_lines += 10;
	menu = (menu_item_t *)realloc(menu,sizeof(menu_item_t)*nb_lines);
      }
      *nl = previous;
      if (previous == ' ' || previous == '\n')
	s = nl+1;
      else
	s = nl;
    }
    delete font;
  } else {
      char *hist = get_shared("history.dat");
      if (!strcmp(hist,"history.dat")) { // No path info added -> no file !
	  int ret = MessageBox(_("Warning"),_("history.dat not found\nDownload it from http://www.arcade-history.com/index.php?page=download\nand install it in your raine directory\n"
		  "in linux ~/.raine or /usr/share/games/raine\n")
		  ,_("Open this page now !|Later maybe..."));
	  if (ret == 1)
	      goto_url("http://www.arcade-history.com/index.php?page=download");
      }
  }

  if (used) {
    menu[used].label = NULL;

    TMenu *about_menu;
    if (!do_command)
	about_menu = new TAbout(_("About this game"),menu, NULL,-1, -1,-1,-1, /* to_translate */ 0);
    else
	about_menu = new TMoves_menu((char*)menu_commands[sel].label,menu);
    about_menu->execute();
    delete about_menu;

    for (int n=0; n<used; n++) {
      free((void*)menu[n].label);
      if (menu[n].values_list_label[0])
	  free(menu[n].values_list_label[0]);
    }
  }
  free(menu);

  return 0;
}

int show_moves(int sel) {
    do_command = 1;
    int n;
    for (n=0; n<nb_commands; n++)
	menu_commands[n].menu_func = &about_game;
    TMenu *menu = new TMenu(_("Special moves..."),menu_commands,
	   NULL,-1, -1,-1,-1, /* to_translate */ 0);
    menu->execute();
    delete menu;
    do_command = 0;
    return 0;
}

static menu_item_t about_items[] =
{
  { EMUNAME " " VERSION " (c)1998-2015 " HANDLE, NULL, NULL },
  { "Compiled on " __DATE__ " " __TIME__ , NULL, NULL },
  { "gcc", NULL, NULL },
  { "cpu", NULL, NULL },
  { "SDL", },
  { "No SDL_sound" },
  { " ", NULL, NULL },
  { "http://raine.1emulation.com/", NULL, NULL },
  { " ", NULL, NULL, },
  { _("CPU emulators:"), NULL, NULL },
  {    _("Starscream 0.26r4 by Neill Corlett"), },
  {    _("MZ80 3.4raine3 by Neill Bradley") },
  {    _("M6502 1.6raine2 by Neill Bradley") },
  {    _("UAE 68020 Emulator : old hacked asm version from UAE") },
  {    _("MCU 68705: statically recompiled code by Richard Mitton") },
  { _("History..."), &about_game },
  { NULL, NULL, NULL },
};

static TAbout_menu *about_menu;
static char gcc_version[30];
static char about_cpu[64];

int do_about(int sel) {
    char *path;
#ifdef __GNUC__
    {
	int major = __GNUC__;
	int minor = __GNUC_MINOR__;
#ifdef __GNUC_PATCHLEVEL__
	int patchlevel = __GNUC_PATCHLEVEL__;
#else
	int patchlevel = 0;
#endif
#ifdef __clang__
	major = __clang_major__;
	minor = __clang_minor__;
	patchlevel = __clang_patchlevel__;
	sprintf(gcc_version,"with llvm/clang %d.%d.%d",major,minor,patchlevel);
#else
	sprintf(gcc_version,"with gcc %d.%d.%d",major,minor,patchlevel);
#endif
    }
#else
    sprintf(gcc_version,"with an unknown gcc ???");
#endif
    about_items[2].label = gcc_version;
    path = get_shared("bitmaps/raine_logo.png");
    sprintf(about_cpu, "CPU: %s", raine_cpu_model);
    about_items[3].label = about_cpu;
    char about_sdl[80];
#if HAS_NEO
    char about_sound[80];
#endif
    const SDL_version *version = SDL_Linked_Version();
    const SDL_version *img = IMG_Linked_Version();
    const SDL_version *ttf = TTF_Linked_Version();
    sprintf(about_sdl,"Linked with SDL-%d.%d.%d, SDL_image-%d.%d.%d, SDL_ttf-%d.%d.%d",version->major,version->minor,version->patch,
	    img->major,img->minor,img->patch,
	    ttf->major,ttf->minor,ttf->patch);
    about_items[4].label = about_sdl;
#if HAS_NEO
    Sound_Version sound;
    Sound_GetLinkedVersion(&sound);
    sprintf(about_sound,"SDL_sound-%d.%d.%d",
	    sound.major,sound.minor,sound.patch);

    about_items[5].label = about_sound;
#endif
#ifdef RDTSC_PROFILE
  if (cycles_per_second) {
    snprintf(about_cpu,64,"CPU: %s at %d MHz",raine_cpu_model,cycles_per_second/1000000);
  }
#endif
  about_menu = new TAbout_menu(_("About..."),about_items, path);
  about_menu->execute();
  delete about_menu;
  about_menu = NULL;
  return 0;
}
