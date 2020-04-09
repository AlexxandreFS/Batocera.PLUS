#include "../gui/menu.h"
#include "raine.h"
#include "blit.h"
#include "palette.h"
#include "tilemod.h"
#include "newspr.h"
#include "sdl/gui/tbitmap.h"
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "sprite_viewer.h"

static int layer = 0;
static UINT32 start_sprite = 0, last_sprite = 0;
static UINT16 tabsprite[640/8*480/8];

static void get_sprite_layer_info(int &w, int &h,int &count, UINT8 *&mask, UINT8 *&gfx) {
  w = tile_list[layer].width;
  h = tile_list[layer].height;
  count = tile_list[layer].count;
  mask = tile_list[layer].mask;
  gfx = tile_list[layer].data;
}

static int sprite_x, sprite_y, sprite_no;

class TSpriteMenu : public TMenu {
  public:
  TSpriteMenu(char *my_title, menu_item_t *mymenu) : TMenu(my_title,mymenu)
  { sprite_x = sprite_y = -1; }
  virtual void create_child(int n);
  virtual void draw_bot_frame();
};

static TSpriteMenu *sprite_menu;

static int draw_sprites(int sel) {
  if (bitmap_color_depth(GameBitmap) != 8) {
    printf("direct draw detected !\n");
    sprite_menu->draw();
    return 0;
  }
  clear_game_screen(0);
  ClearPaletteMap();
  UINT8 map[16];

  int w,h,count;
  UINT8 *mask, *gfx;
  get_sprite_layer_info(w,h,count,mask,gfx);
  int x = 0, y = 0;
  int n;
  for (n=0; n<16; n++)
    map[n] = n; // direct mapping
  n = start_sprite;
  int no_sprite = 0;

  while (count > n) {
    while (n < count && mask[n] == 0)
      n++;
    if (n == count) break;
    // printf("%d,%d,%x\n",x,y,n);
    tabsprite[no_sprite++] = n;
    if (w == 16 && h == 16) {
      Draw16x16_Trans_Mapped_8(&gfx[n<<8],x,y,map);
      x += 16;
      if (x+w > GameBitmap->w) {
	x = 0;
	y += 16;
	if (y+h > GameBitmap->h) break;
      }
    } else if (w == 8 && h == 8) {
	if (is_neocd()) {
	    // layer 0 is packed in neocd and apparently there is no way to store
	    // this info in tile_list... maybe one day, but until then...
	    Draw8x8_Trans_Packed_Mapped_8(&gfx[n<<5],x,y,map);
	} else
	    Draw8x8_Trans_Mapped_8(&gfx[n<<6],x,y,map);
      x += 8;
      if (x+w > GameBitmap->w) {
	x = 0;
	y += 8;
	if (y+h > GameBitmap->h) break;
      }
    } else if (w == 32 && h == 32) {
      Draw32x32_Trans_Mapped_8(&gfx[n<<10],x,y,map);
      x += 32;
      if (x+w > GameBitmap->w) {
	x = 0;
	y += 32;
	if (y+h > GameBitmap->h) break;
      }
    }
    n++;
  }
  last_sprite = n;

  return 0;
}

class TMyBitmap : public TBitmap {
  private:
    int myx, myy;
  public:
    TMyBitmap(menu_item_t *my_menu) : TBitmap(my_menu)
      { myx = myy = 0; }
    virtual int handle_mouse(SDL_Event *event);
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions) {
      myx = x; myy =y;
      TBitmap::disp(s,font,x,y,w,h,fg,bg,xoptions);
    }
};

int TMyBitmap::handle_mouse(SDL_Event *event) {
  if (event->type == SDL_MOUSEMOTION) {
    if (myx || myy) {
      int mx = event->motion.x;
      int my = event->motion.y;
      int w,h,count;
      UINT8 *mask, *gfx;
      get_sprite_layer_info(w,h,count,mask,gfx);
      sprite_x = (mx -myx)/w;
      sprite_y = (my - myy)/h;
      sprite_no = tabsprite[sprite_x+sprite_y*(640/w)];
      sprite_menu->draw_bot_frame();
    }
  } else if (event->type == SDL_MOUSEBUTTONDOWN)  {
    start_sprite = last_sprite;
    printf("start_sprite %x count %x\n",start_sprite,tile_list[layer].count);
    if (start_sprite >= tile_list[layer].count) {
      start_sprite = 0;
    }
  }
  return 0;
}

void TSpriteMenu::create_child(int n) {
  if (menu[n].values_list_size == ITEM_TBITMAP) {
    child[n] = new TMyBitmap(&menu[n]);
  } else
    TMenu::create_child(n);
}

void TSpriteMenu::draw_bot_frame() {
  int base = work_area.y+work_area.h;
  char s[80];
  boxColor(sdl_screen,0,base,sdl_screen->w,sdl_screen->h,bg_frame);
  if (sprite_x >= 0) {
    sprintf(s,"sprite %d,%d:%x",sprite_x,sprite_y,sprite_no);
    font->put_string(HMARGIN,base,s,fg_frame,bg_frame);
  SDL_Rect area;
  area.x = 0; area.y = base; area.w = sdl_screen->w; area.h = sdl_screen->h-base;
  if (!(sdl_screen->flags & SDL_DOUBLEBUF))
    do_update(&area);
  }
}

static int redraw(int sel) {
  if (sprite_menu) {
    start_sprite = last_sprite = 0;
    sprite_menu->draw();
  }
  return 0;
}

static menu_item_t sprites_menu[] =
{
  { _("layer"), &redraw, &layer, 1 }, // init in sprite_viewer
  { "", &draw_sprites, NULL, ITEM_TBITMAP, { 640, 480, 8 } },
  { NULL, NULL, NULL }
};

int sprite_viewer(int sel) {
  sprites_menu[0].values_list_size = tile_list_count;
  UINT32 n;
  for (n=0; n<tile_list_count; n++) {
    sprites_menu[0].values_list[n] = n;
    char buff[10];
    sprintf(buff,"%d: %dx%d",n,
	tile_list[n].width, tile_list[n].height);
    sprites_menu[0].values_list_label[n] = strdup(buff);
  }
  sprite_menu = new TSpriteMenu(_("Sprites viewer"),sprites_menu);
  sprite_menu->execute();
  delete sprite_menu;
  sprite_menu = NULL;
  for (n=0; n<tile_list_count; n++) {
    free(sprites_menu[0].values_list_label[n]);
  }
  return 0;
}

