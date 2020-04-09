#include "raine.h"
#include "games.h"
#include "video/res.h" // wants_switch_res
#include "display.h" // switch_res
#include "newmem.h"
#include "sasound.h"
#include "emudx.h"
#include "unzip.h"
#include "gui.h" // load_progress (through load_explicit_progress)
#include "loadpng.h"

/* This is the support for the graphics emudx files. For the sound, see dxsmp.c in the
   sound directory. */

BITMAP **emudx_tiles;
UINT8 *emudx_sprites,*emudx_sprites32,*emudx_chars;
UINT32 emudx_nb_tiles,emudx_transp;

static int emudx_oldwidth, emudx_oldheight, emudx_oldflags;
static void (*emudx_olddraw)();

static char str[256];

char *exists_emudx_file(const char *db_filename) {
  FILE *f;
  snprintf(str,256,"%s%s", dir_cfg.emudx_dir,db_filename);
  f = fopen(str,"rb");
  if (!f) {
    strcpy(str,db_filename);
    f = fopen(str,"rb");
  }
  if (!f) {
    snprintf(str,256,"%s%s", dir_cfg.share_path,db_filename);
    f = fopen(str,"rb");
  }
  if (f) {
    fclose(f);
    return str;
  }
  return NULL;
}

emudx_file open_emudx_file(const char *name) {
  unzFile dat;
  if (!exists_emudx_file(name)) return NULL;
  dat = unzOpen(str);

  return dat;
}

void close_emudx(emudx_file dat) {
  if (dat) {
    unzClose(dat);
  }
}

BITMAP *emudx_bitmap(emudx_file dat, int nb) {
  char name[10];
  int err;
  BITMAP *bmp;
  PALETTE pal;

  sprintf(name,"%03d.png",nb);
  err = unzLocateFile(dat,name,2);
  if(err!=UNZ_OK){
    print_debug("emudx: not found %s.\n",name);
    unzClose(dat);
    return NULL;		// Fail: File not in zip
  }

  err = unzOpenCurrentFile(dat);
  if(err!=UNZ_OK){
    print_debug("emudx: unzOpenCurrentFile(): Error #%d\n",err);
    unzCloseCurrentFile(dat);	// Is this needed when open failed?
    unzClose(dat);
    return NULL;			// Fail: Something internal
  }

  bmp = load_png_from_zip(dat,pal);
  return bmp;
}

void load_emudx(const char *name, int tiles, int sprites,
		int start_sprites32, int sprites32, int first_char, int last_char,
		int width, int height,
		int transp,void (*draw_emudx)()) {
  /* sprites of tiles and real sprites can overlap (0xd0 tiles in pacman at
   * least).
     So we are obliged to have tiles = nb of tiles, and then start_sprites32 */
  /* Chars are special 16x16 sprites : every non transparent colors are
   * converted to
     color 1, on a 2 colors palette, and the driver must handle the palette for
     these sprites */
  emudx_file dat;
  BITMAP *obj,*bmp;
  int i,ta;
  VIDEO_INFO *video = (VIDEO_INFO*)current_game->video;
  int dkong_exception = (strstr(name,"dkongg.dx") != NULL);

  emudx_nb_tiles = tiles;

  emudx_oldwidth = video->screen_x;
  emudx_oldheight = video->screen_y;
  emudx_oldflags = video->flags;
  emudx_olddraw = video->draw_game;

  if (video->flags & VIDEO_ROTATE_90 || (video->flags & 3)==VIDEO_ROTATE_270) {
    ta = width; width = height; height = ta; // vertiacal inversion...
  }
  if (display_cfg.user_rotate == 1 || display_cfg.user_rotate == 3) {
    ta = width; width = height; height = ta; // vertiacal inversion...
  }
  video->screen_x = width;
  video->screen_y = height;

  dat = open_emudx_file(name);

  if (!dat) {
    allegro_message("couldn't load the dx file.\n");
    video->screen_x = emudx_oldwidth;
    video->screen_y = emudx_oldheight;
    if(wants_switch_res)
      switch_res(current_game->video);
    return;
  }
  video->draw_game = draw_emudx;

  // one more tile for dkong but different dimensions (so... crazy !!!)
  if (!(emudx_tiles = (BITMAP **)AllocateMem(sizeof(BITMAP*)*tiles))) return;
  int bpp = display_cfg.bpp / 8;
  if (!(emudx_sprites = AllocateMem(16*16*bpp*(sprites)))) return;
  if (!(emudx_sprites32 = AllocateMem(32*32*bpp*(sprites32-start_sprites32+1)))) return;
  if (first_char > 0 && last_char > 0) {
    if (!(emudx_chars = AllocateMem(16*16*(last_char-first_char+1)))) return;
  }

  emudx_transp = transp;

  /* Put back width and height in the original order for tiles resizing */
  if (video->flags & VIDEO_ROTATE_90 || (video->flags & 3)==VIDEO_ROTATE_270) {
    ta = width; width = height; height = ta; // vertiacal inversion...
  }
  if (display_cfg.user_rotate == 1 || display_cfg.user_rotate == 3) {
    ta = width; width = height; height = ta; // vertiacal inversion...
  }

  load_message(_("loading EmuDX tiles"));
  for (i=1; i<=tiles; i++) {
    load_explicit_progress(i,sprites32);
    obj = emudx_bitmap(dat,i);
    emudx_tiles[i-1] = create_bitmap(width,height);
    if (!emudx_tiles[i-1]) {
      printf("failed to alloc bitmap %dx%d\n",obj->w,obj->h);
      exit(1);
    }
    if (width != obj->w || height != obj->h) {
      if (dkong_exception) {// exception : border of 48 pixels !!!
	stretch_blit(obj,emudx_tiles[i-1],48,0,obj->w-96,obj->h,0,0,width,height);
      } else {
	stretch_blit(obj,emudx_tiles[i-1],0,0,obj->w,obj->h,0,0,width,height);
      }
    } else
      blit(obj,emudx_tiles[i-1],0,0,0,0,obj->w,obj->h);
    destroy_bitmap(obj);
  }
  if (dkong_exception) {
    /* This is something which should have been done by the creator of the dx file :
       convert the big sprite of the monkey when starting a level to little sprites
       components to be able to draw it in the driver with no change. Too bad I have
       to do it here */
    int x,y,dy;
    obj = emudx_bitmap(dat,261);
    bmp = create_bitmap(96,64);
    stretch_blit(obj,bmp,0,0,obj->w,obj->h,0,0,96,64);
    switch(display_cfg.bpp) {
    case 15:
    case 16:
	{
	    UINT16 *src,*dest;
	    for (x=5; x>=0; x--) {
		for (y=3; y>=0; y--) {
		    dest = (UINT16*)(emudx_sprites+(0x50+(3-y)+(5-x)*4)*0x200);
		    for (dy=0; dy<16; dy++) {
			src = (UINT16*)(bmp->line[y*16+dy]+x*16*2);
			memcpy(dest+dy*16,src,16*2);
		    }
		}
	    }
	}
	break;
    case 32:
	{
	    UINT32 *src,*dest;
	    for (x=5; x>=0; x--) {
		for (y=3; y>=0; y--) {
		    dest = (UINT32*)(emudx_sprites+(0x50+(3-y)+(5-x)*4)*0x400);
		    for (dy=0; dy<16; dy++) {
			src = (UINT32*)(bmp->line[y*16+dy]+x*16*4);
			memcpy(dest+dy*16,src,16*4);
		    }
		}
	    }
	}
	break;
    }
    destroy_bitmap(obj);
    destroy_bitmap(bmp);
  }
  tiles++; // points to start of sprites;
  load_message(_("loading EmuDX sprites"));
  bmp = create_bitmap(16,16); // 16x16, 16bpp
  UINT8 *transp_sprite = AllocateMem(16*16*bpp);
  if (!transp_sprite) return;
  switch(bpp) {
  case 2:
      for (i=0; i<16*16; i++)
	  WriteWord(&transp_sprite[i*2],0xf81f);
      break;
  case 4:
      for (i=0; i<16*16; i++)
	  WriteLong(&transp_sprite[i*4], 0xff00ff);
      break;
  }
  for (i=tiles; i<tiles+sprites; i++) {
    memcpy(bmp->line[0],transp_sprite,16*16*bpp);
    load_explicit_progress(i,sprites32);
    obj = emudx_bitmap(dat,i);
    stretch_blit(obj,bmp,0,0,obj->w,obj->h,0,0,16,16);
    if (i>= first_char && i <= last_char) {
      int sx;
      switch(display_cfg.bpp) {
      case 15:
      case 16:
	  {
	      UINT16 *src = (UINT16*)bmp->line[0];
	      UINT8 *dest = emudx_chars + (i-first_char)*0x100;
	      for (sx=0; sx<16*16; sx++)
		  if (src[sx] != 0xf81f) {
		      dest[sx] = 1;
		  } else
		      dest[sx] = 0;
	  }
	  break;
      case 32:
	  {
	      UINT32 *src = (UINT32*)bmp->line[0];
	      UINT8 *dest = emudx_chars + (i-first_char)*0x100;
	      for (sx=0; sx<16*16; sx++)
		  if (src[sx] != 0xff00ff) {
		      dest[sx] = 1;
		  } else
		      dest[sx] = 0;
	  }
	  break;
      }
    } else {
      memcpy(emudx_sprites + (i-tiles)*0x100*bpp,bmp->line[0],0x100*bpp);
    }
    destroy_bitmap(obj);
  }
  FreeMem(transp_sprite);
  destroy_bitmap(bmp);
  load_message(_("loading EmuDX big sprites"));
  bmp = create_bitmap(32,32); // 32x32, 16bpp
  for (i=start_sprites32; i<=sprites32; i++) {
    load_explicit_progress(i,sprites32);
    obj = emudx_bitmap(dat,i);
    if (obj->w != 32 || obj->h != 32) {
      stretch_blit(obj,bmp,0,0,obj->w,obj->h,0,0,32,32);
      memcpy(emudx_sprites32 + (i-start_sprites32)*0x20*0x20*bpp,bmp->line[0],0x20*0x20*bpp);
    } else {
#ifdef SDL
      if (get_surface_from_bmp(obj)->format->BitsPerPixel > 16) {
	SDL_BlitSurface(get_surface_from_bmp(obj),NULL,
	  get_surface_from_bmp(bmp),NULL);
	memcpy(emudx_sprites32 + (i-start_sprites32)*0x20*0x20*bpp,bmp->line[0],0x20*0x20*bpp);
      } else
#endif
	memcpy(emudx_sprites32 + (i-start_sprites32)*0x20*0x20*bpp,obj->line[0],0x20*0x20*bpp);
    }
    destroy_bitmap(obj);
  }
  destroy_bitmap(bmp);
  close_emudx(dat);
}

void free_emudx() {
  VIDEO_INFO *video = (VIDEO_INFO*)current_game->video;

  if (emudx_tiles) {
    unsigned int i;
    for (i=0; i<emudx_nb_tiles; i++) {
      destroy_bitmap(emudx_tiles[i]);
    }
    emudx_tiles = NULL;
    emudx_nb_tiles = 0;
    if (video) {
      video->screen_x = emudx_oldwidth;
      video->screen_y = emudx_oldheight;
      video->flags = emudx_oldflags;
      video->draw_game = emudx_olddraw;
    } else
      printf("can't restore video\n");
  }
  if (emudx_sprites) {
    FreeMem(emudx_sprites);
    emudx_sprites = NULL;
  }
  if (emudx_sprites32) {
    FreeMem(emudx_sprites32);
    emudx_sprites32 = NULL;
  }
  if (emudx_chars) {
    FreeMem(emudx_chars);
    emudx_chars = NULL;
  }
}

