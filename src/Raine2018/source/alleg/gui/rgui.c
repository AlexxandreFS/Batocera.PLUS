/******************************************************************************/
/*                                                                            */
/*                              R-GUI: RAINE GUI                              */
/*                                                                            */
/******************************************************************************/

#include <allegro.h>
#ifdef RAINE_WIN32
#include <winalleg.h>
#endif
#ifdef GFX_SVGA
#include <vga.h> // Thanks allegro !
#endif
#ifdef GFX_XDGA2
#include <xalleg.h> // _xwin struct
#endif

#ifdef RAINE_UNIX
#include <sys/time.h>
#endif

#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "debug.h"
#include "gui.h" // gui_pal
#include <math.h> // sin (allegro 4.0 broke the fsin function in mingw32 !!!)
#include "display.h"
#include "video/res.h"
#include "bezel.h"

#ifndef round
#define     round(a)    (int)(((a)<0.0)?(a)-.5:(a)+.5)
#endif
#ifndef PI
// wibbles !
#define PI            3.14159265358979323846
#endif

#define GFX_CANCEL        3
#define GFX_DRIVER_LIST    4
#define DGFX_MODE_LIST      5
#define GFX_SCAN_LIST      7
#define GFX_FSKIP_LIST     11
#define GFX_EAGLE_LIST     13
#define GFX_TRIPLE_LIST    14
#define GFX_SPEED_LIST     15
#define GFX_VSYNC_LIST     16
#define GFX_BPP_LIST       19
#define GFX_AUTO_MODE      23

extern DIALOG gfx_mode_dialog[];

typedef struct GFX_MODE_DATA
{
   int w;
   int h;
   char *s;
} GFX_MODE_DATA;

static GFX_MODE_DATA *dyn_list[16]; // initialised to NULL by the compiler

static GFX_MODE_DATA gfx_mode_data_autodetect[] =
{
   { 224,   320,  " 224 x 320"  },
   { 240,   320,  " 240 x 320"  },
   { 256,   200,  " 256 x 200"  },
   { 256,   224,  " 256 x 224"  },
   { 256,   240,  " 256 x 240"  },
   { 256,   256,  " 256 x 256"  },
   { 320,   200,  " 320 x 200"  },
   { 320,   240,  " 320 x 240"  },
   { 320,   256,  " 320 x 256"  },
   { 320,   350,  " 320 x 350"  },
   { 320,   400,  " 320 x 400"  },
   { 320,   480,  " 320 x 480"  },
   { 320,   600,  " 320 x 600"  },
   { 360,   200,  " 360 x 200"  },
   { 360,   240,  " 360 x 240"  },
   { 360,   270,  " 360 x 270"  },
   { 360,   360,  " 360 x 360"  },
   { 360,   400,  " 360 x 400"  },
   { 360,   480,  " 360 x 480"  },
   { 360,   600,  " 360 x 600"  },
   { 376,   282,  " 376 x 282"  },
   { 376,   308,  " 376 x 308"  },
   { 376,   564,  " 376 x 564"  },
   { 400,   300,  " 400 x 300"  },
   { 400,   320,  " 400 x 320"  },
   { 400,   600,  " 400 x 600"  },
   { 448,   576,  " 448 x 576"  },
   { 448,   640,  " 448 x 640"  },
   { 480,   640,  " 480 x 640"  },
   { 512,   384,  " 512 x 384"  },
   { 640,   200,  " 640 x 200"  },
   { 640,   240,  " 640 x 240"  },
   { 640,   400,  " 640 x 400"  },
   { 640,   480,  " 640 x 480"  },
   { 800,   200,  " 800 x 200"  },
   { 800,   300,  " 800 x 300"  },
   { 800,   600,  " 800 x 600"  },
   { 1024,  256,  "1024 x 256"  },
   { 1024,  384,  "1024 x 384"  },
   { 1024,  768,  "1024 x 768"  },
   { 1280,  1024, "1280 x 1024" },
   { 1600,  1200, "1600 x 1200" },
   { 0,     0,    NULL          }
};

#ifdef GFX_MODEX
static GFX_MODE_DATA gfx_mode_data_modex[] =
{
   { 256,   200,  " 256 x 200"  },
   { 256,   224,  " 256 x 224"  },
   { 256,   240,  " 256 x 240"  },
   { 256,   256,  " 256 x 256"  },
   { 320,   200,  " 320 x 200"  },
   { 320,   240,  " 320 x 240"  },
   { 320,   256,  " 320 x 256"  },
#ifndef RAINE_UNIX
   { 320,   350,  " 320 x 350"  },
#endif
   { 320,   400,  " 320 x 400"  },
   { 320,   480,  " 320 x 480"  },
   { 320,   600,  " 320 x 600"  },
   { 360,   200,  " 360 x 200"  },
   { 360,   240,  " 360 x 240"  },
   { 360,   270,  " 360 x 270"  },
   { 360,   360,  " 360 x 360"  },
   { 360,   400,  " 360 x 400"  },
   { 360,   480,  " 360 x 480"  },
   { 360,   600,  " 360 x 600"  },
   { 376,   282,  " 376 x 282"  },
   { 376,   308,  " 376 x 308"  },
   { 376,   564,  " 376 x 564"  },
   { 400,   300,  " 400 x 300"  },
   { 400,   600,  " 400 x 600"  },

   { 0,     0,    NULL          }
};

static GFX_MODE_DATA gfx_mode_data_arcade_monitor[] =
{
   { 320,   240,  " 320 x 240"  },
   { 0,     0,    NULL          }
};
#endif

#ifdef GFX_VGA
static GFX_MODE_DATA gfx_mode_data_vga[] =
{
   { 320,   200,  " 320 x 200"  },
   { 0,     0,    NULL          }
};
#endif

#ifdef GFX_DRIVER_XTENDED
static GFX_MODE_DATA gfx_mode_data_extended[] =
{
   { 640,   400,  " 640 x 400"  },
   { 0,     0,    NULL          }
};
#endif

#ifdef GFX_XDGA2

#define MAX_DGAMODES 20
static GFX_MODE_DATA gfx_mode_data_dga[MAX_DGAMODES],
  gfx_mode_data_xfs[MAX_DGAMODES];
#endif

#ifdef GFX_FBCON
#define MAX_FBMODES 32
// 20 should be much enough !!!
static GFX_MODE_DATA gfx_mode_data_fb[MAX_FBMODES] =
{
  { 640,   480,  " 640 x 480"  },
  { 800,   600,  " 800 x 600"  },
  { 1024,  768,  "1024 x 768"  },
  { 0,     0,    NULL          }
};
#endif

#ifdef GFX_DRIVER_VESA1
static GFX_MODE_DATA gfx_mode_data_vesa[] =
{
   { 320,   200,  " 320 x 200"  },
   { 320,   240,  " 320 x 240"  },
   { 400,   300,  " 400 x 300"  },
   { 512,   384,  " 512 x 384"  },
   { 640,   400,  " 640 x 400"  },
   { 640,   480,  " 640 x 480"  },
   { 800,   600,  " 800 x 600"  },
   { 1024,  768,  "1024 x 768"  },
   { 1280,  1024, "1280 x 1024" },
   { 1600,  1200, "1600 x 1200" },

   { 320,   400,  " 320 x 400"  },
   { 320,   480,  " 320 x 480"  },
   { 400,   600,  " 400 x 600"  },
   { 640,   200,  " 640 x 200"  },
   { 640,   240,  " 640 x 240"  },
   { 800,   200,  " 800 x 200"  },
   { 800,   300,  " 800 x 300"  },
   { 1024,  256,  "1024 x 256"  },
   { 1024,  384,  "1024 x 384"  },

   { 0,     0,    NULL          }
};
#endif

#if !defined(RAINE_DOS) && !defined(RAINE_UNIX)
static GFX_MODE_DATA gfx_mode_data_directx[] =
{
   { 320,   200,  " 320 x 200"  },
   { 320,   240,  " 320 x 240"  },
   { 400,   300,  " 400 x 300"  },
   { 512,   384,  " 512 x 384"  },
   { 640,   400,  " 640 x 400"  },
   { 640,   480,  " 640 x 480"  },
   { 800,   600,  " 800 x 600"  },
   { 1024,  768,  "1024 x 768"  },
   { 1280,  1024, "1280 x 1024" },
   { 1600,  1200, "1600 x 1200" },

   { 0,     0,    NULL          }
};
#endif
// gfx_mode_getter():
// Listbox data getter routine for the graphics mode list.

static GFX_MODE_DATA *res_data;
static UINT32 res_data_length;

static char *gfx_mode_getter(int index, int *list_size)
{
   UINT32 ta;

   if(index == -1){
      if(list_size){
         if(!res_data_length){
            ta = 0;
            while(res_data[ta].s){
               ta++;
            }
            res_data_length = ta;
         }
	 *list_size = res_data_length;
      }
      return NULL;
   }

   if((index >= 0)&&((UINT32)index < res_data_length))
      return raine_translate_text(res_data[index].s);
   else
      return NULL;
}

typedef struct GFX_CARD_DATA
{
   UINT32 id;
   char *name;
   GFX_MODE_DATA *res_list;
} GFX_CARD_DATA;

#ifdef GFX_SVGA
GFX_MODE_DATA *gfx_mode_data_svga = NULL;

#endif

struct GFX_CARD_DATA gfx_card_data[] =
{
	{ GFX_AUTODETECT,     "Autodetect",           gfx_mode_data_autodetect },
#ifdef GFX_VGA
	{ GFX_VGA,            "VGA",                  gfx_mode_data_vga },
#endif
#ifdef GFX_MODEX
	{ GFX_MODEX,          "Mode-X",               gfx_mode_data_modex },
	{ GFX_ARCMON,         "Arcade Monitor",       gfx_mode_data_arcade_monitor },
#endif
#ifdef GFX_DRIVER_VESA1
	{ GFX_VESA1,          "VESA 1.2",             gfx_mode_data_vesa },
#endif
#ifdef GFX_DRIVER_VESA2B
	{ GFX_VESA2B,         "VESA 2.0 (banked)",    gfx_mode_data_vesa },
#endif
#ifdef GFX_DRIVER_VESA2L
	{ GFX_VESA2L,         "VESA 2.0 (linear)",    gfx_mode_data_vesa },
#endif
#ifdef GFX_DRIVER_VESA3
	{ GFX_VESA3,          "VESA 3.0",             gfx_mode_data_vesa },
#endif
#ifdef GFX_DRIVER_VBEAF
	{ GFX_VBEAF,          "VBE/AF",               gfx_mode_data_vesa },
#endif
#ifdef GFX_DRIVER_XTENDED
	{ GFX_XTENDED,        "Extended Mode",        gfx_mode_data_extended },
#endif
#ifdef GFX_DRIVER_DIRECTX
	{ GFX_DIRECTX_ACCEL,  "Accelerated", gfx_mode_data_directx },
	{ GFX_DIRECTX_SAFE,   "Safe",        gfx_mode_data_directx },
	{ GFX_DIRECTX_SOFT,   "Soft",        gfx_mode_data_directx },
	{ GFX_DIRECTX_OVL,    "Overlay",     gfx_mode_data_autodetect },
	{ GFX_DIRECTX_WIN,    "Windowed",    gfx_mode_data_autodetect },
#endif
#ifdef GFX_SVGA
	{ GFX_SVGALIB,   "SVGA", NULL	 },
#endif
};

#ifdef RAINE_UNIX
struct GFX_CARD_DATA gfx_card_data_xfree[] =
{
  { GFX_XWINDOWS, "standard X Windows", gfx_mode_data_autodetect },
#ifdef GFX_XWINDOWS_FULLSCREEN
  { GFX_XWINDOWS_FULLSCREEN, "X11 Fullscreen", gfx_mode_data_xfs },
#endif
#ifdef GFX_XDGA2
  { GFX_XDGA2, "DGA 2.0 mode", gfx_mode_data_dga },
  { GFX_XDGA2_SOFT, "DGA 2.0 software only mode", gfx_mode_data_dga },
#endif
};
#endif

int fbcon_enabled = 0;

static int update_scanline() {
  int sl;
  if((gfx_mode_dialog[GFX_SCAN_LIST].flags)&D_SELECTED) sl=0;
  else if((gfx_mode_dialog[GFX_SCAN_LIST+1].flags)&D_SELECTED) sl=1;
  else if((gfx_mode_dialog[GFX_SCAN_LIST+2].flags)&D_SELECTED) sl=2;
  else // nothing selected -> dialog uninitialised
    sl = display_cfg.scanlines;
  return sl;
}

static int update_bpp() {
  int bpp;
   if((gfx_mode_dialog[GFX_BPP_LIST].flags)&D_SELECTED)
     bpp=8;
   else if((gfx_mode_dialog[GFX_BPP_LIST+1].flags)&D_SELECTED)
     bpp=15;
   else if((gfx_mode_dialog[GFX_BPP_LIST+2].flags)&D_SELECTED)
     bpp=16;
   else if((gfx_mode_dialog[GFX_BPP_LIST+3].flags)&D_SELECTED)
     bpp=32;
   else bpp = display_cfg.bpp; // called when the dialog is NOT initialised
   return bpp;
}

// gfx_card_id():
// Get card ID for card number

int gfx_card_id(int index)
{

#ifdef RAINE_UNIX
   if (x_display) {
     if((index>=0)&&(index<(sizeof(gfx_card_data_xfree) / sizeof(GFX_CARD_DATA)))){
       return gfx_card_data_xfree[index].id;
     }

     return gfx_card_data_xfree[0].id;		// XWindows (default)
   }
#endif

   if((index>=0)&&(index<(sizeof(gfx_card_data) / sizeof(GFX_CARD_DATA)))){
     return gfx_card_data[index].id;
   }

   return gfx_card_data[0].id;		// Autodetect
}

// Chosses if we want automatic mode switching or not.
// we want it only if we are sure about the list of available modes
static void update_switch_res(int screen_type) {
  wants_switch_res = 1; // default : ON
  if (dyn_list[screen_type]
#ifdef GFX_SVGA
		  || gfx_card_data[screen_type].id == GFX_SVGALIB
#endif
#ifdef RAINE_WIN32
                  || display_cfg.screen_type == GFX_DIRECTX_WIN ||
       display_cfg.screen_type == GFX_GDI
#endif
		  )
    wants_switch_res = 1; // Super safe (theory...)
  else
#ifdef RAINE_UNIX
    if (!x_display) // In X, every reported mode should exist too...
#endif
      wants_switch_res = 0;
  if (!display_cfg.auto_mode_change)
    wants_switch_res = 0;
  print_debug("update_switch_res: %d auto_mode_change %d\n",wants_switch_res,display_cfg.auto_mode_change);
}

static void select_closest_mode(int w,int h) {
  // Choose the closest mode to wxh
   int i;
   gfx_mode_dialog[DGFX_MODE_LIST].d1 = 0;

   for(i=0; res_data[i].s; i++){
      if((res_data[i].w >= w)&&(res_data[i].h >= h)){
	 gfx_mode_dialog[DGFX_MODE_LIST].d1 = i;
	 return;
      }
   }
   gfx_mode_dialog[DGFX_MODE_LIST].d1 = i-1;
}

// Change the list of modes based on the screen_mode driver, and selects the closest
// mode to wxh (passed as parameters)
void switch_gfx_res_data(int screen_mode, int w, int h)
{
#ifdef RAINE_UNIX
   if (x_display)
     res_data = gfx_card_data_xfree[screen_mode].res_list;
   else
#endif
     res_data = gfx_card_data[screen_mode].res_list;

   update_switch_res(screen_mode);
   if (dyn_list[screen_mode]) {
     res_data = dyn_list[screen_mode];
   }
   res_data_length = 0;

   select_closest_mode(w,h);
}

static void update_mode_list_dlg() {
  // Restart the list of modes
  SEND_MESSAGE(&gfx_mode_dialog[DGFX_MODE_LIST], MSG_END, 0);
  SEND_MESSAGE(&gfx_mode_dialog[DGFX_MODE_LIST], MSG_START, 0);
  SEND_MESSAGE(&gfx_mode_dialog[DGFX_MODE_LIST], MSG_DRAW, 0);
}

// chooses the best possible resolution for the video info passed (usually from the
// current game). This version chooses from the video preferences dialog status.
static void get_best_resolution_dlg(const VIDEO_INFO *vid,int *w,int *h) {
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
  if (gfx_mode_dialog[GFX_SCAN_LIST+2].flags&D_SELECTED) {// halfheight...
    *h*=2;
  }
  if (gfx_mode_dialog[GFX_EAGLE_LIST].d1 >= 1 && // eagle, scale2x or double
      gfx_mode_dialog[GFX_EAGLE_LIST].d1 <= 3) {
    *h*=2; *w*=2;
  } else if (gfx_mode_dialog[GFX_EAGLE_LIST].d1 == 4) {// double width
    *w*=2;
  }
}

/* gfx_card_getter:
 *  Listbox data getter routine for the graphics card list.
 */
static char *gfx_card_getter(int index, int *list_size)
{

  if(index == -1){
    if(list_size){
#ifdef RAINE_UNIX
      if (x_display)
	if (geteuid()>0) // Non root -> only xfree standard
	  *list_size = 2; // X11 & X11FS
	else
	  *list_size = (sizeof(gfx_card_data_xfree) / sizeof(GFX_CARD_DATA));
      else
#endif
#ifdef GFX_FBCON
	if (fbcon_enabled)
#ifdef GFX_SVGA
	  *list_size = 2;
#else
	  *list_size = 1;
#endif
	else
#endif
	*list_size = (sizeof(gfx_card_data) / sizeof(GFX_CARD_DATA));
    }
      return NULL;
   }

   if(index == -4){

     if (current_game && current_game->video) {
       int w,h;
       get_best_resolution_dlg(current_game->video,&w,&h);

       switch_gfx_res_data(
         *list_size,
         w,
         h
      );
     } else
      switch_gfx_res_data(
         *list_size,
         res_data[gfx_mode_dialog[DGFX_MODE_LIST].d1].w,
         res_data[gfx_mode_dialog[DGFX_MODE_LIST].d1].h
      );

      update_mode_list_dlg();

      return NULL;
   }

   if(index >= 0)
#ifdef RAINE_UNIX
     if (x_display)
       return raine_translate_text(gfx_card_data_xfree[index].name);
     else
#endif
       return raine_translate_text(gfx_card_data[index].name);
   else
      return NULL;
}

static void update_eagle() {
    int bpp = update_bpp();
    if (bpp != 8) {
      if (gfx_mode_dialog[GFX_EAGLE_LIST].d1 == 1) {
	gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 2;
	SEND_MESSAGE(&gfx_mode_dialog[GFX_EAGLE_LIST], MSG_DRAW, 0);
      }
    }
}

static char *screen_effect_getter(int index, int *list_size)
{
   static char *list_data[] =
   {
      "None",
      "Eagle",
      "Scale 2x",
      "Pixel Double",
      "Double Width",
      "Stretch Max",
      "Stretch FS",
   };

   if(index == -1){
      if(list_size)
	 *list_size = sizeof(list_data) / sizeof(char *);
   } else if (index == -4) { // selection in the list
     update_eagle();
     if (current_game) {
       int w,h;
       get_best_resolution_dlg(current_game->video,&w,&h);
       select_closest_mode(w,h);
       update_mode_list_dlg();
     }
   }


   if(index >= 0)
      return raine_translate_text(list_data[index]);
   else
      return NULL;
}

static int bpp_radio_proc(int msg, DIALOG *d, int c) {
  int res = x_raine_radio_proc(msg,d,c);
  if (msg == MSG_CLICK) {
    int w = res_data[gfx_mode_dialog[DGFX_MODE_LIST].d1].w,
      h = res_data[gfx_mode_dialog[DGFX_MODE_LIST].d1].h;
    update_eagle(); // disable eagle if bpp > 8 (replace by double)
    build_mode_list();
     if (current_game)
       get_best_resolution_dlg(current_game->video,&w,&h);
    switch_gfx_res_data(gfx_mode_dialog[GFX_DRIVER_LIST].d1,w,h);
    update_mode_list_dlg();
  }
  return res;
}

int qsort_modes(const void *a, const void *b) {
  char *s1 = ((GFX_MODE_DATA*)a)->s;
  char *s2 = ((GFX_MODE_DATA*)b)->s;
  int diff = strlen(s1)-strlen(s2);
  if (diff)
    return diff;
  return stricmp(s1,s2);
}

#ifdef GFX_XWINDOWS_FULLSCREEN
void setup_xfs_modes() {
  // A copy of the dga version for x11 full screen
   int  i, trouve,nb=0,w,h,j;
   char name[10];
   XF86VidModeModeInfo *mode;

   if (x_display) {
     /* Get list of modelines.  */
     if (!XF86VidModeGetAllModeLines(_xwin.display, _xwin.screen,
				     &_xwin.num_modes, &_xwin.modesinfo)) {
       return;
     }

     for (i=0; i<_xwin.num_modes; i++) {
       mode = _xwin.modesinfo[i];
       w = mode->hdisplay;
       h = mode->vdisplay;

       // Check if current mode is already in (with a different refresh rate...)
       trouve = 0;
       for (j=0; j<nb; j++) {
	 if (gfx_mode_data_xfs[j].w == w && gfx_mode_data_xfs[j].h == h) {
	   trouve = 1;
	   break;
	 }
       }

       if (!trouve && nb < MAX_DGAMODES-1) {
	 gfx_mode_data_xfs[nb].w = w;
	 gfx_mode_data_xfs[nb].h = h;
	 sprintf(name,"%dx%d",w,h);
	 gfx_mode_data_xfs[nb++].s = strdup(name);

       }
     }

     gfx_mode_data_xfs[nb].w =
       gfx_mode_data_xfs[nb].h = 0;
     gfx_mode_data_xfs[nb].s = NULL;
     // The array must be sorted for the auto-change res...
     qsort(gfx_mode_data_xfs,nb,sizeof(GFX_MODE_DATA),qsort_modes);
   }
}
#endif

#ifdef GFX_SVGA
static void setup_svga_modes() {
  /* Normally this should be done by allegro... */
  // Call this BEFORE allegro_init. It seems to crash ModeX in allegro.

  int i;
  int nb = 0;
  char name[10];
  vga_modeinfo *info;

  if (!x_display && !fbcon_enabled) { // Where it is needed...
    // How many modes...
#ifdef SVGALIB_VER
    if (SVGALIB_VER >= 0x010900) {
	    /* Most 1.9 versions have a bug : they call exit if they
	     * can't open /dev/svga, which is completely stupid ! */
	    FILE *f;
	    f=fopen("/dev/svga","rb");
	    if (!f) {
		    fprintf(stderr,"Raine was compiled with SVGALib version 1.9, but I can't open /dev/svga\n");
		    fprintf(stderr,"disabling svgalib for now. You probably need to load the svgalib_helper module\n");
		    return;
	    }
	    fclose(f);
    }
#endif
    for (i = G320x200x16; i <= GLASTMODE; i++) {
      if (vga_hasmode(i)
	  && vga_getmodeinfo(i)->bytesperpixel == 1){
	nb++;
      }
    }
    if (nb) {
      gfx_mode_data_svga = malloc(sizeof(GFX_MODE_DATA)*(nb+1));
      nb = 0;
      for (i = G320x200x16; i <= GLASTMODE; i++) {
	if (vga_hasmode(i)
	    && vga_getmodeinfo(i)->bytesperpixel == 1) {
	  info = vga_getmodeinfo(i);
	  gfx_mode_data_svga[nb].w = info->width;
	  gfx_mode_data_svga[nb].h = info->height;
	  sprintf(name,"%dx%d",info->width,info->height);

	  gfx_mode_data_svga[nb].s = strdup(name);
	  // This allocation is freed implicitly when the program quits
	  nb++;
	}
      }
      gfx_mode_data_svga[nb].w =
	gfx_mode_data_svga[nb].h = 0;
      gfx_mode_data_svga[nb].s = NULL;

      // The array must be sorted for the auto-change res...
      qsort(gfx_mode_data_svga,nb,sizeof(GFX_MODE_DATA),qsort_modes);

      gfx_card_getter(-1,&nb); // Get the number of drivers
      for(i=0; i < nb; i++)
	if (gfx_card_data[i].id == GFX_SVGALIB){
	  gfx_card_data[i].res_list = gfx_mode_data_svga;
	}
    }
  }
}
#endif

#ifdef GFX_FBCON

// This is taken directly from fbcon.c (allegro)
// I just modify it to store its info in an array instead of opening the file
// for EVERY mode change. What are they thinking about ???

/* helper to read the relevant parts of a line from fb.modes */
static char *get_line (FILE *file)
{
   static char buffer[1024];
   char *ch;
   if (feof (file)) return NULL;
   fgets (buffer, sizeof buffer, file);
   if (!strchr (buffer, '\n') && !feof(file)) {
      do {
	 fgets (buffer, sizeof buffer, file);
      } while (!strchr (buffer, '\n'));
      return NULL;
   }
   ch = strchr (buffer, '#');
   if (ch) *ch = '\0';
   ch = strchr (buffer, '\n');
   if (ch) *ch = '\0';
   ch = buffer;
   while (uisspace(*ch)) ch++;
   return ch;
}

/* read_fbmodes_file:
 *  Assigns timing settings from the fbmodes file or returns 0.
 */
static void read_fbmodes_file ()
{
   char *mode_id = NULL;
   char *geometry = NULL;
   char *timings = NULL;
   int sync = 0;
   char *s, *t;
   FILE *fbmodes;
   int nb=0,i,trouve;
   char name[10];

   fbmodes = fopen ("/etc/fb.modes", "r");
   if (!fbmodes) return;

   do {
      s = get_line (fbmodes);
      if (!s) break;
      t = strchr (s, ' ');
      if (t) {
	 *t++ = '\0';
	 while (uisspace(*t)) t++;
      } else {
	 t = strchr (s, '\0');
      }

      if (!strcmp (s, "mode")) {
	 free (mode_id);
	 free (geometry);
	 free (timings);
	 mode_id = strdup (t);
	 geometry = timings = NULL;
	 sync = 0;
      } else if (!strcmp (s, "endmode")) {
	 if (geometry && timings) {
	    int mw, mh;
	    sscanf (geometry, "%d %d", &mw, &mh);

	    if (mw < 2000) { // There is a 10224x768 mode in my config !!!
	      trouve = 0;
	      for(i=0; i<nb; i++)
		if (gfx_mode_data_fb[i].w == mw && gfx_mode_data_fb[i].h == mh)
		  trouve = 1;

	      if (!trouve && nb < MAX_FBMODES) {
		sprintf(name, "%dx%d",mw,mh);
		gfx_mode_data_fb[nb].w = mw;
		gfx_mode_data_fb[nb].h = mh;
		gfx_mode_data_fb[nb].s = strdup(name);
		nb++;
	      }
	    }
	    free (mode_id);
	    free (geometry);
	    free (timings);
	    mode_id = geometry = timings = NULL;
	 }
      } else if (!strcmp (s, "geometry")) {
	 free (geometry);
	 geometry = strdup (t);
      } else if (!strcmp (s, "timings")) {
	 free (timings);
	 timings = strdup (t);
      }
   } while (s);

   free (mode_id);
   free (geometry);
   free (timings);

   fclose (fbmodes);
   gfx_mode_data_fb[nb].w =
     gfx_mode_data_fb[nb].h = 0;
   gfx_mode_data_fb[nb].s = NULL;
}

void setup_fb_modes() {
// Frame buffer does not like other modes :-(
        gfx_card_data[0].id = GFX_FBCON;
        gfx_card_data[0].name = "Frame buffer";
        gfx_card_data[0].res_list = gfx_mode_data_fb;

#ifdef GFX_SVGA
        gfx_card_data[1].id = GFX_SVGALIB;
        gfx_card_data[1].name = "SVGA";
        gfx_card_data[1].res_list = gfx_mode_data_svga;
#endif
	// I read ONLY the /etc/fb.modes file.
	// I don't bother with the allegro config file.
	read_fbmodes_file();
	fbcon_enabled = 1;
}
#endif


// gfx_card_name():
// Get card name for card ID

char *gfx_card_name(UINT32 index)
{
   int ta,tb;

#ifdef RAINE_UNIX
   if (x_display) {
     tb = (sizeof(gfx_card_data_xfree) / sizeof(GFX_CARD_DATA));
     for(ta=0;ta<tb;ta++){
       if(gfx_card_data_xfree[ta].id == index){
         return gfx_card_data_xfree[ta].name;
       }
     }

     return gfx_card_data_xfree[0].name;			// Autodetect
   }
#endif
   tb = (sizeof(gfx_card_data) / sizeof(GFX_CARD_DATA));
   for(ta=0;ta<tb;ta++){
     if(gfx_card_data[ta].id == index){
         return gfx_card_data[ta].name;
     }
   }

   return gfx_card_data[0].name;			// Autodetect
}

// gfx_card_number():
// Get card number for card ID

int gfx_card_number(UINT32 index)
{
   int ta,tb;

#ifdef RAINE_UNIX
   if (x_display) {
     tb = (sizeof(gfx_card_data_xfree) / sizeof(GFX_CARD_DATA));
     for(ta=0;ta<tb;ta++){
       if(gfx_card_data_xfree[ta].id == index){
         return ta;
       }
     }
   } else {
#endif
     tb = (sizeof(gfx_card_data) / sizeof(GFX_CARD_DATA));
     for(ta=0;ta<tb;ta++){
       if(gfx_card_data[ta].id == index){
         return ta;
       }
     }
#ifdef RAINE_UNIX
   }
#endif
   return 0;				// Autodetect
}

static char *frame_skip_getter(int index, int *list_size)
{
   static char *list_data[] =
   {
      "Automatic",
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "9",
   };

   if(index == -1){
      if(list_size)
	 *list_size = 10;
      return NULL;
   }

   if(index >= 0)
      return raine_translate_text(list_data[index]);
   else
      return NULL;
}


int screen_radio_proc(int msg, DIALOG *d, int c);
int screen_def_edit_proc(int msg, DIALOG *d, int c);

DIALOG gfx_mode_dialog[] =
{
   /* (dialog proc)          (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp1) (dp2) (dp3) */
   { d_raine_window_proc,     0,    0,    280,  224-20,  255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Screen Setup", NULL, NULL},

   { x_text_proc,             8,    16,   1,    1,    254,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Screen Mode:", NULL, NULL},
   { x_raine_button_proc,     8,    200-20,  48,   16,   255,  GUI_BOX_COL_MIDDLE,    'O',  D_EXIT,  0,    0,    "&Okay", NULL, NULL},
   { x_raine_button_proc,     64,   200-20,  48,   16,   255,  GUI_BOX_COL_MIDDLE,    'C',  D_EXIT,  0,    0,    "&Cancel", NULL, NULL},
   { d_raine_list_proc,       8,    28,   120,  48,   255,  GUI_BOX_COL_MIDDLE,    0,    D_EXIT,  0,    0,    gfx_card_getter, NULL, NULL},
   { d_raine_list_proc,       150,  28,   110,  48,   255,  GUI_BOX_COL_MIDDLE,    0,    D_EXIT,  3,    0,    gfx_mode_getter, NULL, NULL},

   { x_text_proc,             150,  141,1,    1,    254,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Scanlines:", NULL, NULL},
   { bpp_radio_proc,      150,  151,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    1,    "Off", NULL, NULL},
   { bpp_radio_proc,      150,  161,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    1,    "Halfheight", NULL, NULL},
   { bpp_radio_proc,      150,  171,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    1,    "Fullheight", NULL, NULL},

   { x_text_proc,             8,    87,  1,    1,    254,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Frame Skip:", NULL, NULL},
   { d_raine_list_proc,       8,    97,  80,   20,   255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    frame_skip_getter, NULL, NULL},

   { x_text_proc,             150,  87,1,    1,    254,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Screen Effect:", NULL, NULL},
   { d_raine_list_proc,    150,  97,99,   30,   255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    screen_effect_getter, NULL, NULL},

   { d_raine_check_proc,             8,    132+6,50,    9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,    0,    0,       1,    1,    "Triple Buffer", NULL, NULL},
   { d_raine_check_proc,           8,  148,  50,    9,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,    0,    0,       1,    1,    "Limit Speed", NULL, NULL},
   { d_raine_check_proc,             8,  158,  50,    9,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,    0,    0,       1,    1,    "VSync Palette", NULL, NULL},

   { x_text_proc,             150,  16,   1,    1,    254,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Screen Size:", NULL, NULL},

   { x_text_proc,             235,  141,1,    1,    254,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Bpp:", NULL, NULL},
   { bpp_radio_proc,      235,  151,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       6,    1,    "8", NULL, NULL},
   { bpp_radio_proc,      235,  161,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       6,    1,    "15", NULL, NULL},
   { bpp_radio_proc,      235,  171,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       6,    1,    "16", NULL, NULL},
   { bpp_radio_proc,      235,  181,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       6,    1,    "32", NULL, NULL},

   { d_raine_check_proc,           8,    128,100,    9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,    0,    0,       1,    1,    "Auto Mode Change", NULL, NULL},
   { NULL,              0,    0,    0,    0,    0,    0,    0,    0,       0,                      0,    NULL,             NULL, NULL  }
};

// raine_gfx_mode_select():
// Displays the Allegro graphics mode selection dialog, which allows the
// user to select a screen mode and graphics card. Stores the selection
// in the three variables, and returns zero if it was closed with the
// Cancel button, or non-zero if it was OK'd.

int raine_gfx_mode_select(void)
{
  int ret; //i;

   // Wait for user

   clear_keybuf();
   while(gui_mouse_b()){
      dialog_oxygen();
   };

   // Init stuff

   if(display_cfg.scanlines>2)display_cfg.scanlines=2;

   gfx_mode_dialog[GFX_SCAN_LIST].flags=0;
   gfx_mode_dialog[GFX_SCAN_LIST+1].flags=0;
   gfx_mode_dialog[GFX_SCAN_LIST+2].flags=0;

   gfx_mode_dialog[GFX_SCAN_LIST+display_cfg.scanlines].flags=D_SELECTED;

   if(display_cfg.frame_skip>9) display_cfg.frame_skip = 0;

   gfx_mode_dialog[GFX_FSKIP_LIST].d1 = display_cfg.frame_skip;

   if(display_cfg.vsync>1)display_cfg.vsync=0;

   gfx_mode_dialog[GFX_VSYNC_LIST].flags =
     (display_cfg.vsync ? D_SELECTED : 0);

   if(display_cfg.limit_speed>1) display_cfg.limit_speed=1;

   gfx_mode_dialog[GFX_SPEED_LIST].flags=
     (display_cfg.limit_speed ? D_SELECTED : 0);

   gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 0;

   if(display_cfg.eagle_fx)

      gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 1;

   else if (use_scale2x)
      gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 2;
   else if(display_cfg.pixel_double==1)

      gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 3;

   else if(display_cfg.pixel_double==2)

      gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 4;

   else if (display_cfg.stretch==1)

     gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 5;

   else if (display_cfg.stretch==2)

     gfx_mode_dialog[GFX_EAGLE_LIST].d1 = 6;

   if(display_cfg.triple_buffer>1)display_cfg.triple_buffer=1;

   gfx_mode_dialog[GFX_TRIPLE_LIST].flags =
     (display_cfg.triple_buffer ? D_SELECTED : 0);

   gfx_mode_dialog[GFX_AUTO_MODE].flags =
     (display_cfg.auto_mode_change ? D_SELECTED : 0);

   gfx_mode_dialog[GFX_BPP_LIST].flags = // 8 bpp
     gfx_mode_dialog[GFX_BPP_LIST+1].flags= // 15
     gfx_mode_dialog[GFX_BPP_LIST+2].flags= // 16
     gfx_mode_dialog[GFX_BPP_LIST+3].flags= 0; // 32
   if (display_cfg.bpp > 32 || display_cfg.bpp == 24) display_cfg.bpp = 32;
   if (display_cfg.bpp < 8) display_cfg.bpp = 8;

   switch(display_cfg.bpp) {
   case 8 : gfx_mode_dialog[GFX_BPP_LIST+0].flags=D_SELECTED; break;
   case 15: gfx_mode_dialog[GFX_BPP_LIST+1].flags=D_SELECTED; break;
   case 16: gfx_mode_dialog[GFX_BPP_LIST+2].flags=D_SELECTED; break;
   case 32: gfx_mode_dialog[GFX_BPP_LIST+3].flags=D_SELECTED; break;
   }


   gfx_mode_dialog[GFX_DRIVER_LIST].d1 = gfx_card_number(display_cfg.screen_type);
   switch_gfx_res_data(
      gfx_card_number(display_cfg.screen_type),
      display_cfg.screen_x,
      display_cfg.screen_y
   );

   // Do the selection

   ret = raine_do_dialog(gfx_mode_dialog, GFX_DRIVER_LIST);

   if (ret != GFX_CANCEL && ret != -1) {

     // Set the results

     display_cfg.screen_type = gfx_card_id(gfx_mode_dialog[GFX_DRIVER_LIST].d1);

     display_cfg.screen_x = res_data[gfx_mode_dialog[DGFX_MODE_LIST].d1].w;
     display_cfg.screen_y = res_data[gfx_mode_dialog[DGFX_MODE_LIST].d1].h;

     display_cfg.scanlines = update_scanline();

     display_cfg.frame_skip = gfx_mode_dialog[GFX_FSKIP_LIST].d1;

     display_cfg.vsync=
       ((gfx_mode_dialog[GFX_VSYNC_LIST].flags & D_SELECTED) ? 1 : 0);

     display_cfg.limit_speed=
       ((gfx_mode_dialog[GFX_SPEED_LIST].flags & D_SELECTED) ? 1 : 0);

     display_cfg.eagle_fx =
       use_scale2x =
       display_cfg.stretch =
       display_cfg.pixel_double = 0;

     switch(gfx_mode_dialog[GFX_EAGLE_LIST].d1){
     case 1:
       display_cfg.eagle_fx = 1;
       break;
     case 2:
       use_scale2x = 1; break;
     case 3:
       display_cfg.pixel_double = 1;
       break;
     case 4:
       display_cfg.pixel_double = 2;
       break;
     case 5:
       display_cfg.stretch = 1;
       break;
     case 6:
       display_cfg.stretch = 2;
       break;
     }

     if (display_cfg.scanlines)
       display_cfg.stretch = 0;

     display_cfg.triple_buffer =
       ((gfx_mode_dialog[GFX_TRIPLE_LIST].flags & D_SELECTED) ? 1 : 0);

     display_cfg.auto_mode_change =
       ((gfx_mode_dialog[GFX_AUTO_MODE].flags & D_SELECTED) ? 1 : 0);
     if (!display_cfg.auto_mode_change)
       wants_switch_res = 0;

     display_cfg.bpp = update_bpp();

     return(TRUE);
   }
   return (FALSE); // cancel
}



static DIALOG alert_dialog[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,   0,    0,    0,    255,  0,  0,    0,       0,    0,    NULL },
   { x_ctext_proc,       0,   0,    0,    0,    254,  -1,  0,    0,       0,    0,    NULL },
   { x_ctext_proc,       0,   0,    0,    0,    254,  -1,  0,    0,       0,    0,    NULL },
   { x_ctext_proc,       0,   0,    0,    0,    254,  -1,  0,    0,       0,    0,    NULL },
   { d_raine_button_proc,0,   0,    0,    0,    255,  0,  0,    D_EXIT,  0,    0,    NULL },
   { d_raine_button_proc,0,   0,    0,    0,    255,  0,  0,    D_EXIT,  0,    0,    NULL },
   { d_raine_button_proc,0,   0,    0,    0,    255,  0,  0,    D_EXIT,  0,    0,    NULL },
   { x_edit_proc,        0,   0,   30,   10,    255,  0,  0,    D_EXIT,  0,    0,    NULL },
   { NULL }
};

#define A_T1  0
#define A_S1  1
#define A_S2  2
#define A_S3  3
#define A_B1  4
#define A_B2  5
#define A_B3  6
#define A_EDIT 7

// raine_alert3():
// Displays a simple alert box, containing three lines of text (s1-s3),
// and with either one, two, or three buttons. The text for these buttons
// is passed in b1, b2, and b3 (NULL for buttons which are not used), and
// the keyboard shortcuts in c1 and c2. Returns 1, 2, or 3 depending on
// which button was selected.

void prepare_alert(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, char *b3, int c1, int c2, int c3)
{
   int maxlen = 0;
   int len1, len2, len3;
   int avg_w = text_length(font, " ");
   int avg_h = text_height(font);
   int buttons = 0;
   int b[3];

#define SORT_OUT_BUTTON(x) {				\
      if (b##x) {					\
	 alert_dialog[A_B##x].flags &= ~D_HIDDEN;	\
	 alert_dialog[A_B##x].key = c##x;		\
	 alert_dialog[A_B##x].dp = b##x;		\
	 len##x = gui_strlen(b##x);			\
	 b[buttons++] = A_B##x;				\
      }							\
      else {						\
	 alert_dialog[A_B##x].flags |= D_HIDDEN;	\
	 len##x = 0;					\
      }							\
   }

   alert_dialog[A_S1].dp = alert_dialog[A_S2].dp = alert_dialog[A_S3].dp =
			   alert_dialog[A_B1].dp = alert_dialog[A_B2].dp =
                           alert_dialog[A_T1].dp = "";

   alert_dialog[A_EDIT].proc = NULL;

   if (s1) {
      alert_dialog[A_S1].dp = s1;
      maxlen = text_length(font, s1);
   }

   if (s2) {
      alert_dialog[A_S2].dp = s2;
      len1 = text_length(font, s2);
      if (len1 > maxlen)
	 maxlen = len1;
   }

   if (s3) {
      alert_dialog[A_S3].dp = s3;
      len1 = text_length(font, s3);
      if (len1 > maxlen)
	 maxlen = len1;
   }

   if (title) {
      alert_dialog[A_T1].dp = title;
      len1 = text_length(font, title);
      if (len1 > maxlen)
	 maxlen = len1;
   }

   SORT_OUT_BUTTON(1);
   SORT_OUT_BUTTON(2);
   SORT_OUT_BUTTON(3);

   len1 = MAX(len1, MAX(len2, len3)) + avg_w*3;
   if (len1*buttons > maxlen)
      maxlen = len1*buttons;

   maxlen += avg_w*4;
   alert_dialog[0].w = maxlen;
   alert_dialog[A_S1].x = alert_dialog[A_S2].x = alert_dialog[A_S3].x =
						alert_dialog[0].x + maxlen/2;

   alert_dialog[A_B1].w = alert_dialog[A_B2].w = alert_dialog[A_B3].w = len1;

   alert_dialog[A_B1].x = alert_dialog[A_B2].x = alert_dialog[A_B3].x =
				       alert_dialog[0].x + maxlen/2 - len1/2;

   if (buttons == 3) {
      alert_dialog[b[0]].x = alert_dialog[0].x + maxlen/2 - len1*3/2 - avg_w;
      alert_dialog[b[2]].x = alert_dialog[0].x + maxlen/2 + len1/2 + avg_w;
   }
   else if (buttons == 2) {
      alert_dialog[b[0]].x = alert_dialog[0].x + maxlen/2 - len1 - avg_w;
      alert_dialog[b[1]].x = alert_dialog[0].x + maxlen/2 + avg_w;
   }

   alert_dialog[0].y += 10;
   alert_dialog[0].h = 10 + avg_h*8;
   alert_dialog[A_S1].y = alert_dialog[0].y + avg_h;
   alert_dialog[A_S2].y = alert_dialog[0].y + avg_h*2;
   alert_dialog[A_S3].y = alert_dialog[0].y + avg_h*3;
   alert_dialog[A_S1].h = alert_dialog[A_S2].h = alert_dialog[A_S2].h = avg_h;

   alert_dialog[A_B1].y = alert_dialog[A_B2].y = alert_dialog[A_B3].y =
						alert_dialog[0].y + avg_h*5;

   alert_dialog[A_B1].h = alert_dialog[A_B2].h = alert_dialog[A_B3].h = avg_h*2;

   alert_dialog[0].y -= 10;

   raine_centre_dialog(alert_dialog);
}

static int exec_alert(int focus) {
  int c;
  clear_keybuf();
  while(gui_mouse_b()){
    dialog_oxygen();
  };

  c = raine_window_dialog(alert_dialog, focus);

  if (c == A_B1 || c == A_EDIT)
      return 1;
  else if (c == A_B2)
    return 2;
  else if (c== A_B3)
    return 3;
  else
    return c;
}

int raine_alert3(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, char *b3, int c1, int c2, int c3)
{
  prepare_alert(title,s1,s2,s3,b1,b2,b3,c1,c2,c3);
  return exec_alert(A_B1);
}

int raine_edit_int(char *title, char *s1, char *b1, char *b2, int c1, int c2, int inf, int supp, int def)
{
  char s2[10],s3[10];
  int len1,ret,val;
  char def_value[10],s1_bidon[25];

  sprintf(s1_bidon,"%d <= 32767 <= %d",inf,supp);
  sprintf(s2,"%d <=",inf);
  sprintf(s3,"<= %d",supp);

  prepare_alert(title,strlen(s1_bidon) > strlen(s1) ? s1_bidon : s1,
		s2,s3,b1,b2,NULL,c1,c2,0);
  alert_dialog[A_EDIT].proc = x_edit_proc;
  alert_dialog[A_S1].dp = s1;
/*   alert_dialog[A_S1].x = */
  alert_dialog[A_S2].x = alert_dialog[0].x + 15;

  len1 = text_length(font, s2);
  alert_dialog[A_EDIT].x = alert_dialog[A_S2].x + len1 + 5;
  alert_dialog[A_EDIT].y = alert_dialog[A_S2].y;
  alert_dialog[A_EDIT].d1 = 5; // Max len
  alert_dialog[A_EDIT].dp = def_value;
  sprintf(def_value,"%d",def);

  alert_dialog[A_S3].x = alert_dialog[A_EDIT].x + 35;
  alert_dialog[A_S3].y = alert_dialog[A_S2].y;

  do {
    ret = exec_alert(A_EDIT);
    if (ret==1) val = atoi(def_value);
  } while ((val < inf || val > supp) && ret==1);
  return (ret == 1 ? val : def);
}

// raine_alert():
// Displays a simple alert box, containing three lines of text (s1-s3),
// and with either one or two buttons. The text for these buttons is passed
// in b1 and b2 (b2 may be null), and the keyboard shortcuts in c1 and c2.
// Returns 1 or 2 depending on which button was selected.

int raine_alert(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, int c1, int c2)
{
   int ret;

   ret = raine_alert3(title, s1, s2, s3, b1, b2, NULL, c1, c2, 0);

   if (ret > 2)
      ret = 2;

   return ret;
}

/* raine_do_dialog:
 *  The basic dialog manager. The list of dialog objects should be
 *  terminated by one with a null dialog procedure. Returns the index of
 *  the object which caused it to exit.
 */

#define BUFFER_GUI

#ifdef BUFFER_GUI
static BITMAP *screen_old=NULL;
static BITMAP *screen_new=NULL;
static int oxygen_level;
#endif

// prepare screen for displaying dialogs (bpp, mouse, etc...)


void setup_gui_screen(int *kill) {
#ifdef BUFFER_GUI
   if(!(screen_new)){
      show_mouse(NULL);
      // This bitmap is used to draw the GUI.
      // GUI colors are in 8bpp. If one day we decide to convert it to 16,
      // then we will have to change this. But it is very unlikely !!!
#ifdef RAINE_DEBUG
      print_debug("allocated screen\n");
#endif
      screen_new = create_bitmap( display_cfg.screen_x,display_cfg.screen_y);
      screen_old = screen;
      screen     = screen_new;
      *kill       = 1;
      blit(screen_old,screen_new,0,0,0,0,display_cfg.screen_x,display_cfg.screen_y);
   }
   else{
      *kill       = 0;
   }
#endif
   show_mouse(screen);
}

void done_gui_screen(int *kill) {
#ifdef BUFFER_GUI
  if(*kill){
    print_debug("Freeing screen\n");
    show_mouse(NULL);
    dialog_oxygen();
    destroy_bitmap(screen_new);
    screen     = screen_old;
    screen_new = screen_old = NULL;
   }
#endif
}

int raine_do_dialog(DIALOG *dialog, int focus_obj)
{
#if ALLEGRO_VERSION==4 && ALLEGRO_SUB_VERSION ==0
  // Allegro bug : in 4.0.1 and probably before, the drivers menu in the
  // game selection dialog freezes the mouse in blit mode (dialog_oxygen)

  // Sadly, it seems we are obliged to use the standard do_dialog EVERYWHERE
  // to avoid this bug.
   return do_dialog(dialog,focus_obj);
#else
   void *player;
   int ta,kill;
   int desk = desktop_color_depth();

   if ((desk && display_cfg.bpp != desk)) {

     // The color conversion in the gui is too expensive when in a window...
     return do_dialog(dialog,focus_obj);
   }

#ifdef RAINE_DEBUG
   print_debug("raine_do_dialog(): setup_gui_screen\n");
#endif
   setup_gui_screen(&kill);
#ifdef RAINE_DEBUG
   print_debug("raine_do_dialog(): init_dialog focus %d\n",focus_obj);
#endif

   player = init_dialog(dialog, focus_obj);

   oxygen_level=0;

   while(update_dialog(player)){
      if(oxygen_level==0){		// Gasp! Ack!
         dialog_oxygen();
      }
      oxygen_level=0;
   }

   //show_mouse(mouse_screen);

   ta = shutdown_dialog(player);

   done_gui_screen(&kill);
   return ta;
#endif
}

// Stop the mouse freezing, when the game is loading and there
// is no oxygen coming in.

void mouse_on_real_screen(void)
{
   show_mouse(NULL);
   dialog_oxygen();
   if (screen_old)
     show_mouse(screen_old);
}

// Restore the mouse to the buffer screen, when oxygen supply
// returns.

void mouse_on_buffer_screen(void)
{
   show_mouse(screen);
   dialog_oxygen();
}

// Stop the dialog freezing, when the game is loading and there
// is no oxygen coming in.

void dialog_on_real_screen(void)
{
  if (screen_old)
    screen = screen_old;
}

// Restore the dialog to the buffer screen, when oxygen supply
// returns.

void dialog_on_buffer_screen(void)
{
  if (screen_new) // if raine_do_dialog was not disabled...
    screen = screen_new;
}

static void save_gui_screen(void)
{
   char full_name[256];
   char file_name[32];

   raine_cfg.req_save_screen = 0;

   /*

   first try gui.pcx

   */

   sprintf(file_name, "%s.pcx", "gui");

   sprintf(full_name, "%s%s", dir_cfg.screen_dir, file_name);

   /*

   otherwise, find the next gui_NNN.pcx (or guiNNN.pcx)

   */

   while( exists(full_name) ){

      if(dir_cfg.last_screenshot_num > 999)

         return;

      if(dir_cfg.long_file_names)

         sprintf(file_name, "%s_%03d.pcx", "gui", dir_cfg.last_screenshot_num++);

      else

         sprintf(file_name, "%.5s%03d.pcx", "gui", dir_cfg.last_screenshot_num++);

      sprintf(full_name, "%s%s", dir_cfg.screen_dir, file_name);

   };

   save_pcx(full_name, screen, gui_pal);

   //print_ingame(120, "Screen Saved to %s", file_name);
}

void dialog_oxygen(void)
{

#ifdef RAINE_UNIX
  struct timeval timeout;
#endif

#ifdef BUFFER_GUI
   static int z,z1,z2,z3;
   int ta;
   int x;

   if(raine_cfg.hide){

     oxygen_level=1;

   }
   else{

     if(screen_new){		// Ahhhhhhh.... That's better :)
       oxygen_level=1;

       if(!raine_cfg.wibble){
	 if (screen_old)
	   blit(screen,screen_old,0,0,0,0,display_cfg.screen_x,display_cfg.screen_y);

	 if(key[KEY_0]) {
	   save_gui_screen();
	 }


       }
       else{
	 z++;

	 z1=z/7;
	 z1&=255;

	 z2=z/5;
	 z2&=255;

	 z3=z/1;
	 z3&=255;
	 z3^=255;
	 for(ta=0;ta<display_cfg.screen_y;ta++){
	   x = round ( (sin((ta+z1)) * 16.0*PI/180) + (sin((z2-(ta*16.0))*PI/180) * 2) + (sin((z3-(ta*3.0))*PI/180) * 4));
	   blit(screen,screen_old,0,ta,x,ta,display_cfg.screen_x,1);
	 }

       }
     }

   }

   // wait 1/60s to be sure the cpu will not get too much load for nothing...
#ifdef RAINE_WIN32
  // As usual windows is not standard
  // its sleep function has a 1ms resolution instead of 1us. Too bad...
   Sleep(1000/60);
#elif defined(RAINE_UNIX)
  timeout.tv_sec = 0;
  timeout.tv_usec = 1000000/60;
  select(0, NULL, NULL, NULL, &timeout);
#endif
  // Nothing in dos to put the cpu in sleep mode, AFAIK

#endif

}

void setup_gfx_modes() {
#ifdef RAINE_UNIX
  if (getenv("DISPLAY")) {
    print_debug("DISPLAY = %s\n",getenv("DISPLAY"));
    //	   int bpp = desktop_color_depth();
    //	   printf("depth detected : %d\n",bpp);
    //	   if (bpp>8)
    x_display=1;
    wants_switch_res = 1;
  }
#ifdef GFX_SVGA
  else
     setup_svga_modes(); // return in allegro 4.0.0... Too bad !!!
#endif
#endif

  set_default_video_mode();
}

// Sadly, I have to make this because I can't switch res as soon as I want.
// I have to indicate to the game being loaded the mode it will work in
// but wait for the gui to be redrawn before switching the res for real...
// Note also that the default values are 0 (no change)
int bestw,besth,bestbpp;

// Chooses a resolution with the variables bestw, besth and bestbpp
int switch_res(const VIDEO_INFO *vid)
{
   int ta;
   int w,h,i,mindiff,minindice,diff;
   GFX_MODE_DATA *res_data;

   get_best_resolution(vid,&w,&h);
   print_debug("trying to find a resolution close to %dx%d\n",w,h);
   if (vid->flags & VIDEO_NEEDS_16BPP) {
     if (display_cfg.bpp < 15 || display_cfg.bpp > 16)
       bestbpp = 16;
     else bestbpp = 0;
   } else if (vid->flags & VIDEO_NEEDS_8BPP)
     bestbpp = 8;

   //if (w<320) w=320;
   //if (h<240) h=240;
   bestw = besth = 9999;

   // It's quite dangerous to change the type of driver...
   // For what I know, we could fall in Arcade Monitor mode !!!
   // Let's stuck to the driver we use now...
   ta = gfx_card_number(display_cfg.screen_type);
   print_debug("for screen type %d\n",ta);
#ifdef RAINE_UNIX
   if (x_display)
     res_data = gfx_card_data_xfree[ta].res_list;
   else
#endif
     res_data = gfx_card_data[ta].res_list;
   if (!res_data) {
	   res_data = gfx_card_data[0].res_list;
	   ta=0;
   }
   if (dyn_list[ta]) res_data = dyn_list[ta]; // dynamic list of modes
#ifdef RAINE_UNIX
   if (display_cfg.screen_type == GFX_XWINDOWS ||
       display_cfg.screen_type == 0){
     bestw = w; besth = h; // EVERY mode is available for a window
   } else
#else
#ifdef RAINE_WIN32
   if (display_cfg.screen_type == GFX_DIRECTX_WIN ||
       display_cfg.screen_type == GFX_GDI){
	bestw = w; besth = h; // same thing for windows !
   } else
#endif
#endif
   { // for the else in win32 and linux
     mindiff = 9999;
     minindice = 0; // totally useless, but avoid 1 warning...
     for(i=0; res_data[i].s; i++){
       if((res_data[i].w<w)||(res_data[i].h < h))
	 continue;
       if (res_data[i].w<bestw || res_data[i].h<besth){
	 diff = res_data[i].w - w + res_data[i].h -h;
	 if (diff == mindiff) {
		 // special case. Equality for the diff.
		 // The winner is the one with the max ratio (closest to 1.333)
		 float ratio1 = 1.3333-(bestw*1.0/besth);
		 float ratio2 = 1.3333-(res_data[i].w*1.0/res_data[i].h);
		 if (ratio2 < ratio1)
			 mindiff++; // the new mode has a better ratio !
	 }
	 if (diff < mindiff) {
	   mindiff = diff;
	   minindice = i;
	 }
       }
     }
     if (mindiff == 9999) { // found nothing, do it again being more tolerant...
       for(i=0; res_data[i].s; i++){
	 if (res_data[i].w<bestw || res_data[i].h<besth){
	   diff = abs(res_data[i].w - w) + abs(res_data[i].h -h);
	   if (diff == mindiff) {
	     // special case. Equality for the diff.
	     // The winner is the one with the max ratio (closest to 1.333)
	     float ratio1 = 1.3333-(bestw*1.0/besth);
	     float ratio2 = 1.3333-(res_data[i].w*1.0/res_data[i].h);
	     if (ratio2 < ratio1)
	       mindiff++; // the new mode has a better ratio !
	   }
	   if (diff < mindiff) {
	     mindiff = diff;
	     minindice = i;
	   }
	 }
       }
     }
     bestw = res_data[minindice].w; besth = res_data[minindice].h;
   }

   memcpy(&prev_display_cfg, &display_cfg, sizeof(DISPLAY_CFG));

   // We can't set the bpp because changing the depth can change the list of
   // modes, for modex or svgalib for example.

#ifdef RAINE_DEBUG
   print_debug("resolution selected %dx%dx%d actuel %dx%dx%d (diff %d)\n",bestw,besth,bestbpp,display_cfg.screen_x,display_cfg.screen_y,display_cfg.bpp,minindice);
#endif
   if (display_cfg.screen_x != bestw || display_cfg.screen_y != besth
       || (display_cfg.bpp != (UINT32)bestbpp && bestbpp))
     return 1;
   print_debug("no resolution change\n");
   bestw = besth = bestbpp = 0; // No change !!!
   return 0;
}

void build_mode_list() {
#if ALLEGRO_WIP_VERSION >= 39 || ALLEGRO_VERSION >= 4
  int screen_mode;
  int nb = sizeof(gfx_card_data)/sizeof(GFX_CARD_DATA);
  GFX_MODE_LIST *list;
  for (screen_mode = 0; screen_mode < nb; screen_mode++) {
    if (dyn_list[screen_mode])
      free(dyn_list[screen_mode]);
    list = get_gfx_mode_list(gfx_card_id(screen_mode));
    if (list) {
      int nb2=0,n;
      char name[20];
      GFX_MODE_DATA *my_list;
      int bpp = update_bpp();
      for (n=0; n<list->num_modes; n++)
	if (list->mode[n].bpp == bpp)
	  nb2++;
#ifdef RAINE_DEBUG
      print_debug("build_mode_list: driver %s index %d modes %d\n",gfx_card_data[screen_mode].name,screen_mode,nb2);
#endif
      my_list = dyn_list[screen_mode] = malloc(sizeof(GFX_MODE_DATA)*(nb2+1));
      nb2 = 0;
      for (n=0; n<list->num_modes; n++)
	if (list->mode[n].bpp == bpp) {
	  int w = list->mode[n].width;
	  int h = list->mode[n].height;
	  my_list[nb2].w = w;
	  my_list[nb2].h = h;
	  sprintf(name,"%dx%d",my_list[nb2].w,my_list[nb2].h);
	  my_list[nb2].s = strdup(name);
	  nb2++;
	}
      my_list[nb2].w = my_list[nb2].h = 0;
      my_list[nb2].s = NULL;
      destroy_gfx_mode_list(list);
    }
#ifdef RAINE_DEBUG
    else
      print_debug("build_mode_list: driver %s no mode list\n",gfx_card_data[screen_mode].name);
#endif
  }
  update_switch_res(gfx_card_number(display_cfg.screen_type));
#else
#warning ******************************************************************
#warning *** You need allegro 3.9.38 at least for the gfx_mode_list support
#warning ******************************************************************
#endif
}

/******************************************************************************/

