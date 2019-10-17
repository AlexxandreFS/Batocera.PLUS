/* Resolution routines (mode selection...) */
#include "games/games.h"
#include "raine.h"
#include "blit.h"
#include "bezel.h"

#ifdef DARWIN
#undef RAINE_UNIX
#endif

#ifdef RAINE_UNIX
UINT32   *_LUT16to32;
UINT32   *_RGBtoYUV;
#define LUT16to32 _LUT16to32
#define RGBtoYUV _RGBtoYUV
#else
UINT32   *LUT16to32;
UINT32   *RGBtoYUV;
#endif

void InitLUTs(void)
{
  int i, j, k, r, g, b, Y, u, v;
  if (display_cfg.stretch == 3) { // hq2x selected
    if (!LUT16to32) {
      LUT16to32 = malloc(sizeof(UINT32)*65536);
      RGBtoYUV = malloc(sizeof(UINT32)*65536);
    } else
      return; // already initialised
  } else {
    if (LUT16to32) {
      free(LUT16to32);
      free(RGBtoYUV);
      LUT16to32 = NULL;
    }
    return;
  }

  for (i=0; i<65536; i++)
    LUT16to32[i] = ((i & 0xF800) << 8) + ((i & 0x07E0) << 5) + ((i & 0x001F) << 3);

  for (i=0; i<32; i++)
  for (j=0; j<64; j++)
  for (k=0; k<32; k++)
  {
    r = i << 3;
    g = j << 2;
    b = k << 3;
    Y = (r + g + b) >> 2;
    u = 128 + ((r - b) >> 2);
    v = 128 + ((-r + 2*g -b)>>3);
    RGBtoYUV[ (i << 11) + (j << 5) + k ] = (Y<<16) + (u<<8) + v;
  }
}

int wants_switch_res;
int stretchx, stretchy; // max stretch size, keeping ratio
int use_scale2x;

// chooses the best possible resolution for the video info passed (usually from the
// current game)
void get_best_resolution(const VIDEO_INFO *vid,int *w,int *h) {
  int ta;
  *w = vid->screen_x;
  *h = vid->screen_y;
  bezel_fix_screen_size(w,h);

  if (vid->flags & VIDEO_ROTATE_90 || (vid->flags & 3)==VIDEO_ROTATE_270) {
    ta = *w; *w = *h; *h = ta; // vertiacal inversion...
  }
  if (display_cfg.user_rotate == 1 || display_cfg.user_rotate == 3) {
    ta = *w; *w = *h; *h = ta; // vertiacal inversion...
  }
  if (display_cfg.scanlines == 2) {// halfheight...
    *h*=2;
  }
  // in sdl the way it works has changed : choose to set the resolution first
  // and then use the doubling/tripling functions if there is still some room
#ifndef SDL
  if (
    display_cfg.pixel_double==1 || display_cfg.eagle_fx ||
    use_scale2x == 1) {
    *h*=2; *w*=2;
  } else if (use_scale2x == 2) {
    *h *= 3; *w *= 3;
  } else if (display_cfg.pixel_double==2) {// double width
    *w*=2;
  }
#endif
}


#define min(a,b) (a<b ? a : b)

void update_stretch()
{
  double scalex, scaley,scale;
  int w,h,ta,flags;

  if (current_game) {
    w = current_game->video->screen_x;
    h = current_game->video->screen_y;
    flags = current_game->video->flags;
    if ( flags & VIDEO_ROTATE_90 || flags & VIDEO_ROTATE_270) {
      ta = w; w = h; h = ta; // vertiacal inversion...
    }

    scalex = display_cfg.screen_x * 1.0 / w;
    scaley = display_cfg.screen_y * 1.0 / h;
    scale = min(scalex,scaley);

    stretchx =	w * scale;
    stretchy = h * scale;
  }
}
