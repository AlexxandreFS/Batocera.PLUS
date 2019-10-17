#include "tbitmap.h"
#include "sdl/compat.h"
#include "raine.h"
#include "games.h"
#include "blit.h"
#include "sdl/blit_sdl.h"
#include "palette.h"

TBitmap::TBitmap(menu_item_t *my_menu) : TStatic(my_menu) 
{
  if (!current_game) throw "no current_game";
  bpp = display_cfg.bpp;
  display_cfg.bpp = menu->values_list[2];
  flags = current_game->video->flags;
  current_game->video->flags |= VIDEO_NEEDS_8BPP;
  width = current_game->video->screen_x;
  height = current_game->video->screen_y;
  border = current_game->video->border_size;
  current_game->video->screen_x = get_width();
  current_game->video->screen_y = get_height();
  current_game->video->border_size = 0;
  SetupScreenBitmap();

  int n;
  memset(pal,0,sizeof(pal));
  // setup a vga palette
  pal[1].r =  255;
  pal[2].g = 255;
  pal[3].r = pal[3].g = 255;
  pal[4].b = 255;
  pal[5].r = pal[5].b = 255;
  pal[6].g = pal[6].b = 255;
  pal[7].r = pal[7].g = pal[7].b = 255;
  for (n=9; n<=15; n++) {
    pal[n].r = pal[n-8].r/2;
    pal[n].g = pal[n-8].g/2;
    pal[n].b = pal[n-8].b/2;
  }
  memcpy(&pal[240],&pal[0],sizeof(SDL_Color)*16);
}

TBitmap::~TBitmap() {
  display_cfg.bpp = bpp;
  current_game->video->flags = flags;
  current_game->video->screen_x = width;
  current_game->video->screen_y = height;
  current_game->video->border_size = border;
  SetupScreenBitmap();
}

void TBitmap::disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h, 
  int fg, int bg, int xoptions) {

  (*menu->menu_func)(0);
  SDL_Rect dst; dst.x = x; dst.y = y;
  SDL_Rect src; src.x = src.y = 0; src.w = w; src.h = h;
  SDL_SetPalette(sdl_game_bitmap,SDL_LOGPAL,(SDL_Color*)pal,0,256);
  SDL_BlitSurface(sdl_game_bitmap,&src, s, &dst);
}

