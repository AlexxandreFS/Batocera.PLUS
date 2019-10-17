#include "raine.h"
#include "blit.h"
#include "SDL.h"
#include "games.h"
#include "video/tilemod.h"
#include "compat.h"
#include "ingame.h"
#include "profile.h"
#include "gen_conv.h"
#include "video/res.h"
#include "loadpng.h"
#include "bezel.h"
#include "video/scale2x.h"
#include "video/scale3x.h"
#include "sdl/SDL_gfx/SDL_framerate.h"
#include "sasound.h" // sa_pause_sound
#include "palette.h"
#include <math.h>
#include "cpuid.h"
#include "sdl/display_sdl.h"
#include "emudx.h"
#include "blit_x2.h"
#include "blit_sdl.h"
#include "hq2x.h"
#include "newspr.h" // init_video_core
#include "video/priorities.h"
#include "neocd/neocd.h"
#include "sdl/opengl.h"
#include "demos.h"

SDL_Surface *sdl_game_bitmap;
extern int disp_screen_x, disp_screen_y;
BITMAP *GameBitmap = NULL; 	// *Full* Bitmap for generating the game screen (eg. 0,0 to 320+32,240+32)
BITMAP *GameViewBitmap; 	// *Viewable* Bitmap for saving (pcx) the game screen (eg. 16,16 to 320+16,240+16)

UINT32 pause_time;
int recording_video = 0,last_video_frame,video_fps;

RAINEBITMAP GameScreen;

static int destx, desty, xxx, yyy, xoff2, yoff2;

static void my_save_png(char *full_name) {
    if ((sdl_screen->flags & SDL_OPENGL) && ogl.save)
	ogl_save_png(full_name);
    else
	save_png(full_name, GameViewBitmap, pal);
}

static void do_save_screen(void)
{
   char full_name[256];
   char file_name[32];
   char *extension = "png";

   raine_cfg.req_save_screen = 0;

   /*

   first try gamename.pcx

   */

   snprintf(file_name, 32,"%s.%s", current_game->main_name,extension);

   snprintf(full_name, 256,"%s%s", dir_cfg.screen_dir, file_name);


   if (recording_video) {
     int current_video_frame = cpu_frame_count*video_fps / fps;

     if (current_video_frame != last_video_frame) {
       snprintf(full_name,256,"%s%s_%06d.%s",dir_cfg.screen_dir, current_game->main_name,cpu_frame_count,extension);
       my_save_png(full_name);
       last_video_frame = current_video_frame;
     }
   } else {

     /*

     otherwise, find the next gamename_NNN.pcx (or gamenNNN.pcx)

     */

     while( exists(full_name) ){
       if(dir_cfg.last_screenshot_num > 999)
	 return;
       if(dir_cfg.long_file_names)
	 snprintf(file_name,32, "%s_%03d.%s", current_game->main_name, dir_cfg.last_screenshot_num++,extension);
       else
	 snprintf(file_name,32, "%.5s%03d.%s", current_game->main_name, dir_cfg.last_screenshot_num++,extension);
       snprintf(full_name,256, "%s%s", dir_cfg.screen_dir, file_name);
     };
     my_save_png(full_name);
     print_ingame(120, gettext("Screen Saved to %s"), file_name);
   }

}

SDL_Rect area_overlay,area2;

void get_overlay_area(int *x, int *y, int *w, int *h) {
  *x = area_overlay.x;
  *y = area_overlay.y;
  *w = area_overlay.w;
  *h = area_overlay.h;
}

void ReClipScreen(void)
{
   // clip x
 int game_x,game_y;
 double ratio1, ratio2;

  // I need to use 2 sets of xview/yview because destx/desty must be calculated
  // taking into account the scaling factor, but the width and height must be
  // unscaled (it's automatically multiplied during the blit)
  int xview,yview,xview2,yview2;

  xview2 = xview = GameScreen.xview;
  yview2 = yview = GameScreen.yview;
  // This code is broken, if this function is called just once with -nogui
  // then yyy isn't initialized... !
  if (!yyy) yyy = yview;

  // bezel_fix_screen_size(&xview,&yview);

  if (use_scale2x == 1) {
    xview2 *= 2;
    yview2 *= 2;
  } else if (use_scale2x == 2) {
    xview2 *= 3;
    yview2 *= 3;
  }

  if (display_cfg.scanlines >= 2) { // fullheight
    yview2 *= 2;
    if (display_cfg.scanlines == 3) // add double width
      xview2 *= 2;
  }

  if(xview2 < disp_screen_x){
    destx = (disp_screen_x - xview2)>>1;
  }
  else{
    destx = 0;
  }
  if (xview < disp_screen_x || sdl_overlay) {
    // We can't write outside the game bitmap so we have to use xview
    xxx = xview;
    xoff2 = GameScreen.xtop;
  } else {
    // If the game bitmap is bigger than the screen, then no risk (if stretched)
    if(xview <= disp_screen_x){
      xxx = xview;
      xoff2 = GameScreen.xtop;
    } else {
      xxx = disp_screen_x;
      xoff2 = GameScreen.xtop + ((xview - disp_screen_x)>>1);
    }
  }

  // clip y

  if(yview2 < disp_screen_y){
    desty = (disp_screen_y - yview2)>>1;
  }
  else{
    desty = 0;
  }

 if (current_game) {
     // if (reading_demo) display_cfg.screen_y -= 8;
     game_x = xxx;
     game_y = yyy;
     ratio1 = display_cfg.screen_x*1.0/game_x;
     ratio2 = display_cfg.screen_y*1.0/game_y;
     // printf("ratio1 %g ratio2 %g game_x %d game_y %d\n",ratio1,ratio2,game_x,game_y);

     if (sdl_overlay || sdl_screen->flags & SDL_OPENGL) {
	 if (display_cfg.fix_aspect_ratio ) {
	     /* Fixing the aspect ratio must be done on the game resolution and not
	      * on the screen resolution, otherwise the screen size will change
	      * everytime we return to the game */
	     if (game_x > game_y) {
		 double ratio = game_y*1.0/game_x;
		 double dif_ratio = fabs(ratio-0.75);
		 if (dif_ratio > 0.001 && dif_ratio < 0.05) {
		     game_y = 0.75*game_x;
		     printf("fixing aspect ratio to 0.75 - new res %d x %d\n",game_x,game_y);
		 }
	     } else {
		 double ratio = game_x*1.0/game_x;
		 double dif_ratio = fabs(ratio-0.75);
		 if (dif_ratio > 0.001 && dif_ratio < 0.05) {
		     game_x = 0.75*game_y;
		     printf("fixing aspect ratio to 0.75 - new res %d x %d\n",game_x,game_y);
		 }
	     }
	 }

	 /* Now fix the aspect ratio of the overlay inside the game screen */
	 int xxx2,yyy2,destx2,desty2;
	 if (ratio1 < ratio2) {
	     xxx2 = display_cfg.screen_x;
	     yyy2 = round(ratio1 * game_y);
	     destx2 = 0;
	     desty2 = (display_cfg.screen_y - yyy2)/2;
	     if (desty2 < 0) {
		 /* Out of limits, harmless for texture, creates black screen
		  * in win32 when using drawpixels.
		  * Anyway should investigate why screen_y < game_y*ratio1
		  * here one day, all this will be rewritten for sdl2 anyway */
		 desty2 = 0;
		 yyy2 = display_cfg.screen_y;
	     }
	 } else {
	     yyy2 = display_cfg.screen_y;
	     xxx2 = round(ratio2 * game_x);
	     desty2 = 0;
	     destx2 = (display_cfg.screen_x - xxx2) /2;
	     if (destx2 < 0) {
		 // copy the out of limits code from ratio1 < ratio2
		 destx2 = 0;
		 xxx2 = display_cfg.screen_x;
	     }
	 }
	 bezel_fix_screen_size(&xxx2,&yyy2);
	 bezel_fix_screen_coordinates(&destx2,&desty2,xxx2,yyy2,display_cfg.screen_x,display_cfg.screen_y);
#ifdef DARWIN
	 if (display_cfg.video_mode == 1 && overlays_workarounds) {
	     // I have a bug here which makes the overlay invisible if it doesn't start
	     // at the top of the screen !!!
	     // It seems so stupid that it's probably a bug of my video driver, but to
	     // be sure I'll put a fix here, it's better than a black screen...
	     area_overlay.x = destx2 = 0;
	     area_overlay.y = desty2 = 0;
	 }
#endif
	 if (display_cfg.keep_ratio) {
	     area_overlay.x = destx2;
	     area_overlay.y = desty2;
	     area_overlay.w = xxx2;
	     area_overlay.h = yyy2;
	 } else {
	     area_overlay.x = area_overlay.y = 0;
	     area_overlay.w = display_cfg.screen_x;
	     area_overlay.h = display_cfg.screen_y;
	 }
	 print_debug("area overlay %d %d %d %d with xxx %d yyy %d display %d %d ratio1 %g ratio2 %g\n",destx2,desty2,xxx2,yyy2,xxx,yyy,display_cfg.screen_x,display_cfg.screen_y,ratio1,ratio2);
     } else {
	 if (display_cfg.stretch >= 1 && !display_cfg.scanlines) {
	     if (ratio1 >= 3.0 && ratio2 >= 3.0 && (display_cfg.stretch == 1 ||
			 display_cfg.stretch == 3)) {
		 if (use_scale2x != 2) {
		     use_scale2x = 2;
		     return SetupScreenBitmap();
		 }
	     } else if (ratio1 >= 2.0 && ratio2 >= 2.0) {
		 if (use_scale2x != 1) {
		     use_scale2x = 1;
		     return SetupScreenBitmap();
		 }
	     } else
		 use_scale2x = 0;
	 } else
	     use_scale2x = 0;
     }
     area2.x = destx; // x2;
     area2.y = desty; // y2;
     if (use_scale2x == 1) {
	 area2.w = xxx*2;
	 area2.h = yyy*2;
     } else if (use_scale2x == 2) {
	 area2.w = xxx*3;
	 area2.h = yyy*3;
     } else {
	 area2.w = xxx;
	 area2.h = yyy;
     }
     if (!sdl_overlay) {
	 int x = area2.x, y = area2.y, w = area2.w, h = area2.h;
	 // printf("fixing bezel %d %d %d %d - zone du jeu %d %d %d %d scale %d\n",x,y,w,h,xxx,yyy,destx,desty,use_scale2x);
	 bezel_fix_screen_size(&w,&h);
	 bezel_fix_screen_coordinates(&x,&y,area2.w,area2.h,display_cfg.screen_x,display_cfg.screen_y);
	 area2.x = x; area2.y = y; // area2.w = w; area2.h = h;
	 // printf("result bezel %d %d %d %d\n",x,y,w,h);
     }

     display_bezel();
     if (GameViewBitmap)
	 clear_bitmap(GameViewBitmap);

     RefreshBuffers=1;
     if (pbitmap)
	 init_pbitmap();
     // if (reading_demo) display_cfg.screen_y += 8;
 }

  if(yview2 <= disp_screen_y && xview2 <= disp_screen_x && current_game)
    bezel_fix_screen_coordinates(&destx,&desty,xview2,yview2,disp_screen_x,disp_screen_y);
  if(yview < disp_screen_y){
    yyy = yview;
    yoff2 = GameScreen.ytop;
  } else {
    if(yview <= disp_screen_y){
      yyy = yview;
      yoff2 = GameScreen.ytop;
    } else {
      yyy = disp_screen_y;
      yoff2 = GameScreen.ytop + ((yview - disp_screen_y)>>1);
    }
  }

  // GameScreen.xview = oldxview;
  // GameScreen.yview = oldyview;
  if (sdl_screen->flags & SDL_OPENGL)
      opengl_reshape(sdl_screen->w,sdl_screen->h);
}

void DrawPaused(void)
{
   // blit(pause_buffer, GameBitmap, xoff2, yoff2, xoff2, yoff2, xxx, yyy);

   DrawNormal();		// Overlay text interface, blit to screen

   pause_time++;

   if(display_cfg.limit_speed==1){
	      SDL_framerateDelay(&fpsm);
   }
}

static void SetScreenBitmap(int xfull, int yfull, int xtop, int ytop, int xview, int yview)
{
   const VIDEO_INFO *vid_info;

   vid_info = current_game->video;

   display_cfg.rotate = 0;
   display_cfg.flip = 0;

   if(vid_info->flags & VIDEO_ROTATABLE){

      /*

      check if we use the game rotation

      */

      if(!display_cfg.no_rotate)

	 display_cfg.rotate = VIDEO_ROTATE( vid_info->flags );

      /*

      check if we use the game flipping

      */

      if(!display_cfg.no_flip)

	 display_cfg.flip = VIDEO_FLIP( vid_info->flags );

      /*

      add user rotation

      */

      display_cfg.rotate += display_cfg.user_rotate;
      display_cfg.rotate &= 3;

      /*

      add user flipping

      */

      display_cfg.flip ^= display_cfg.user_flip;

   }

   switch(display_cfg.rotate){
   case 0x00:
   case 2:
      GameScreen.xfull=xfull;
      GameScreen.yfull=yfull;
      GameScreen.xtop =xtop;
      GameScreen.ytop =ytop;
      GameScreen.xview=xview;
      GameScreen.yview=yview;
   break;
   case 0x01:
   case 3:
      GameScreen.xfull=yfull;
      GameScreen.yfull=xfull;
      GameScreen.xtop =ytop;
      GameScreen.ytop =xtop;
      GameScreen.xview=yview;
      GameScreen.yview=xview;
   break;
   }

   check_tile_rotation();

   /*

   these modes double the image size (it's simpler to consider
   them as halving the display resolution)

   */


   disp_screen_y = display_cfg.screen_y;
   disp_screen_x = display_cfg.screen_x;

   ReClipScreen();
}

void SetupScreenBitmap(void)
{
 const VIDEO_INFO *vid_info;
 int oldbpp;

 if (!current_game)
   return;

 vid_info = current_game->video;

 SetScreenBitmap(
    vid_info->screen_x + vid_info->border_size + vid_info->border_size,
    vid_info->screen_y + vid_info->border_size + vid_info->border_size,
    vid_info->border_size,
    vid_info->border_size,
    vid_info->screen_x,
    vid_info->screen_y
 );

 if (!GameBitmap || (GameBitmap->w != GameScreen.xfull || GameBitmap->h != GameScreen.yfull || sdl_game_bitmap->format->BitsPerPixel != display_cfg.bpp) ||
	 (display_cfg.video_mode == 0 && display_cfg.bpp != 16) ||
     (sdl_overlay && display_cfg.video_mode != 1) ||
     (!sdl_overlay && display_cfg.video_mode == 1)) {
   print_debug("regen GameBitmap\n");
   if (display_cfg.video_mode != 1 && sdl_overlay) {
     SDL_FreeYUVOverlay(sdl_overlay);
     sdl_overlay = NULL;
   }
   do {
     oldbpp = display_cfg.bpp;
     if (GameBitmap) {
       DestroyScreenBitmap(); // destroys gameviewbitmap too
     }
     GameBitmap = sdl_create_bitmap_ex(internal_bpp(display_cfg.bpp), GameScreen.xfull, GameScreen.yfull);
     sdl_game_bitmap = get_surface_from_bmp(GameBitmap);
     // GameBitmap = sdl_create_overlay(GameScreen.xfull, GameScreen.yfull);
     // GameBitmap = create_system_bitmap( GameScreen.xfull, GameScreen.yfull);
     GameViewBitmap = sdl_create_sub_bitmap(GameBitmap, GameScreen.xtop, GameScreen.ytop, GameScreen.xview, GameScreen.yview);
   } while (oldbpp != display_cfg.bpp);
   init_video_core(); // GameBitmap just changed -> regen all the functions
   // which depend on it !
 }
}

void DestroyScreenBitmap(void)
{
  destroy_bitmap(GameBitmap);
  destroy_bitmap(GameViewBitmap);
  GameBitmap = NULL;
  GameViewBitmap = NULL;
  sdl_game_bitmap = NULL;
}

extern void *old_draw; // dlg_sound

#ifndef NO_ASM
static void raine_blit_scale2x(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
   UINT32 ta;

   ta = 0;
   if (d_y >= dest->h) return;
   h = MIN(h,(dest->h - d_y)/2);

#define SCALE2X(DEPTH,TYPE)							\
   scale2x_##DEPTH##_##TYPE(							\
			  (((UINT##DEPTH *)dest->line[d_y])+d_x),		\
			  (((UINT##DEPTH *)dest->line[d_y+1])+d_x),		\
			  (((UINT##DEPTH *)src->line[s_y])+s_x),		\
			  (((UINT##DEPTH *)src->line[s_y])+s_x),		\
			  (((UINT##DEPTH *)src->line[s_y+1])+s_x),		\
			  (UINT16) w						\
   );										\
										\
   for(ta=1;ta<(UINT32)(h-1);ta++){						\
										\
     scale2x_##DEPTH##_##TYPE(							\
			    (((UINT##DEPTH *)dest->line[ta*2+d_y])+d_x),	\
			    (((UINT##DEPTH *)dest->line[ta*2+d_y+1])+d_x),	\
			    (((UINT##DEPTH *)src->line[ta+s_y-1])+s_x),		\
			    (((UINT##DEPTH *)src->line[ta+s_y])+s_x),		\
			    (((UINT##DEPTH *)src->line[ta+s_y+1])+s_x),		\
			    (UINT16) w						\
			    );							\
										\
   }										\
										\
   ta = (h-1);									\
										\
   scale2x_##DEPTH##_##TYPE(							\
			  (((UINT##DEPTH *)dest->line[ta*2+d_y])+d_x),		\
			  (((UINT##DEPTH *)dest->line[ta*2+d_y+1])+d_x),	\
			  (((UINT##DEPTH *)src->line[ta+s_y-1])+s_x),		\
			  (((UINT##DEPTH *)src->line[ta+s_y])+s_x),		\
			  (((UINT##DEPTH *)src->line[ta+s_y])+s_x),		\
			  (UINT16) w						\
			  );

#ifndef NO_ASM
#ifdef RAINE_DOS
   es = dest->seg;
   asm(" mov %es,_oldes\n mov _es,%es");
#endif
   if (raine_cpu_capabilities & CPU_MMX) {
     switch (display_cfg.bpp) {
     case 8:
       SCALE2X(8,mmx); break;
     case 15:
     case 16:
       SCALE2X(16,mmx);
       break;
     case 32:
       SCALE2X(32,mmx); break;
     }
     __asm__ __volatile__("finit\n"); // restore fpu status after mmx code
   } else {
#endif
     switch (display_cfg.bpp) {
     case 8:
       SCALE2X(8,def); break;
     case 15:
     case 16:
       SCALE2X(16,def); break;
     case 32:
       SCALE2X(32,def); break;
     }
#ifndef NO_ASM
   }
#ifdef RAINE_DOS
   asm("mov _oldes,%es");
#endif
#endif
}

static void raine_blit_scale3x(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
   UINT32 ta;

   ta = 0;
   if (d_y >= dest->h) return;
   h = MIN(h,(dest->h - d_y)/2);

#define SCALE3X(DEPTH,TYPE)							\
   scale3x_##DEPTH##_##TYPE(							\
			  (((UINT##DEPTH *)dest->line[d_y])+d_x),		\
			  (((UINT##DEPTH *)dest->line[d_y+1])+d_x),		\
			  (((UINT##DEPTH *)dest->line[d_y+2])+d_x),		\
			  (((UINT##DEPTH *)src->line[s_y])+s_x),		\
			  (((UINT##DEPTH *)src->line[s_y])+s_x),		\
			  (((UINT##DEPTH *)src->line[s_y+1])+s_x),		\
			  (UINT16) w						\
   );										\
										\
   for(ta=1;ta<(UINT32)(h-2);ta++){						\
										\
     scale3x_##DEPTH##_##TYPE(							\
			    (((UINT##DEPTH *)dest->line[ta*3+d_y])+d_x),	\
			    (((UINT##DEPTH *)dest->line[ta*3+d_y+1])+d_x),	\
			    (((UINT##DEPTH *)dest->line[ta*3+d_y+2])+d_x),	\
			    (((UINT##DEPTH *)src->line[ta+s_y-1])+s_x),		\
			    (((UINT##DEPTH *)src->line[ta+s_y])+s_x),		\
			    (((UINT##DEPTH *)src->line[ta+s_y+1])+s_x),		\
			    (UINT16) w						\
			    );							\
										\
   }										\
										\
   ta = (h-2);									\
										\
   scale3x_##DEPTH##_##TYPE(							\
			  (((UINT##DEPTH *)dest->line[ta*3+d_y])+d_x),		\
			  (((UINT##DEPTH *)dest->line[ta*3+d_y+1])+d_x),	\
			  (((UINT##DEPTH *)dest->line[ta*3+d_y+1])+d_x),	\
			  (((UINT##DEPTH *)src->line[ta+s_y-1])+s_x),		\
			  (((UINT##DEPTH *)src->line[ta+s_y])+s_x),		\
			  (((UINT##DEPTH *)src->line[ta+s_y+1])+s_x),		\
			  (UINT16) w						\
			  );

#ifdef RAINE_DOS
   es = dest->seg;
   asm(" mov %es,_oldes\n mov _es,%es");
#endif
/*
 * No mmx version for scale3x !
   if (raine_cpu_capabilities & CPU_MMX) {
     switch (display_cfg.bpp) {
     case 8:
       SCALE3X(8,mmx); break;
     case 15:
     case 16:
       SCALE3X(16,mmx);
       break;
     case 32:
       SCALE3X(32,mmx); break;
     }
     __asm__ __volatile__("finit\n"); // restore fpu status after mmx code
   } else {
     */
     switch (display_cfg.bpp) {
     case 8:
       SCALE3X(8,def); break;
     case 15:
     case 16:
       SCALE3X(16,def); break;
     case 32:
       SCALE3X(32,def); break;
     }
/*   } */
#ifdef RAINE_DOS
   asm("mov _oldes,%es");
#endif
}
#endif

#if 0
static void RGBtoYUV(Uint8 *rgb, int *yuv, int monochrome, int luminance)
{
    if (monochrome)
    {
#if 1 /* these are the two formulas that I found on the FourCC site... */
        yuv[0] = 0.299*rgb[2] + 0.587*rgb[1] + 0.114*rgb[0];
        yuv[1] = 128;
        yuv[2] = 128;
#else
        yuv[0] = (0.257 * rgb[0]) + (0.504 * rgb[1]) + (0.098 * rgb[2]) + 16;
        yuv[1] = 128;
        yuv[2] = 128;
#endif
    }
    else
    {
#if 1 /* these are the two formulas that I found on the FourCC site... */
        yuv[0] = 0.299*rgb[2] + 0.587*rgb[1] + 0.114*rgb[0];
        yuv[1] = (rgb[0]-yuv[0])*0.565 + 128;
        yuv[2] = (rgb[2]-yuv[0])*0.713 + 128;
#else
        yuv[0] = (0.257 * rgb[0]) + (0.504 * rgb[1]) + (0.098 * rgb[2]) + 16;
        yuv[1] = 128 - (0.148 * rgb[0]) - (0.291 * rgb[1]) + (0.439 * rgb[2]);
        yuv[2] = 128 + (0.439 * rgb[0]) - (0.368 * rgb[1]) - (0.071 * rgb[2]);
#endif
    }

    if (luminance!=100)
    {
        yuv[0]=yuv[0]*luminance/100;
        if (yuv[0]>255)
            yuv[0]=255;
    }
}

static void ConvertRGBtoYV12(SDL_Surface *s, SDL_Overlay *o, int monochrome, int luminance, int border)
{
	int x,y;
	int yuv[3];
	Uint8 *p,*op[3];

	/* Convert */
	for(y=0; y<s->h && y<o->h; y++)
	{
		p=((Uint8 *) s->pixels)+s->pitch*(y+border)+border*s->format->BytesPerPixel;
		op[0]=o->pixels[0]+o->pitches[0]*y;
		op[1]=o->pixels[1]+o->pitches[1]*(y/2);
		op[2]=o->pixels[2]+o->pitches[2]*(y/2);
		for(x=0; x<s->w && x<o->w; x++)
		{
			RGBtoYUV(p, yuv, monochrome, luminance);
			*(op[0]++)=yuv[0];
			if(x%2==0 && y%2==0)
			{
				*(op[1]++)=yuv[2];
				*(op[2]++)=yuv[1];
			}
			p+=s->format->BytesPerPixel;
		}
	}
}
#endif

static void raine_fast_blit(BITMAP *source, BITMAP *dest, UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2, UINT32 w, UINT32 h)
{
  SDL_Rect area1;
  int ret;

  if (sdl_overlay) {
    // convert source to yuy2 format in the overlay
    unsigned char *src,*dest;
    SDL_LockYUVOverlay(sdl_overlay);
#ifndef NO_ASM
    if (sdl_overlay->format == SDL_YUY2_OVERLAY) {
      src = GameBitmap->line[GameScreen.ytop]+x1*2;
      dest = sdl_overlay->pixels[0]; // +y*sdl_overlay->pitches[0];
      /* Principle : when using an overlay, the color format is forced to
       * overlay_format in compat.c so that we are able to use the rgb565_
       * conversion functions everywhere.
       * Of course if you switch to normal blits after having loaded an emudx
       * game with an overlay enabled, don't complain if the red and blue get
       * inverted. This is an extreme case, and it would be bothersome to work
       * around it, so just don't do that ! */
	mmx_rgb565_yuyv(dest, src, w, sdl_overlay->h, sdl_overlay->pitches[0], sdl_game_bitmap->pitch);
    } else if (sdl_overlay->format == SDL_YV12_OVERLAY) {
	src = GameBitmap->line[GameScreen.ytop /* +y */ ]+x1*2;
	mmx_rgb565_yuv420(sdl_overlay->pixels[0], // +y*sdl_overlay->pitches[0],
	    sdl_overlay->pixels[2], // +(y/2)*sdl_overlay->pitches[2],
	    sdl_overlay->pixels[1], // +(y/2)*sdl_overlay->pitches[1],
	    src, w, sdl_overlay->h, sdl_overlay->pitches[0], sdl_overlay->pitches[1], sdl_game_bitmap->pitch);
    }
#endif
    SDL_UnlockYUVOverlay(sdl_overlay);

    SDL_DisplayYUVOverlay(sdl_overlay,&area_overlay);
    /* The SDL_DisplayYUVOverlay is a magical function :
     *  - it stretches the overlay to the desired size without bothering the cpu
     *  - it's automatically updated on screen (no SDL_UpdateRect to call)
     *  - it automatically synchronizes on the monitor refresh rate (verified
     *  by playing without limiting the framerate).
     *  So no SDL_Flip nor SDL_UpdateRect required here */
    if ( (sdl_screen->flags & SDL_DOUBLEBUF) && display_cfg.double_buffer == 2 ) {
      /* Now there is still a problem about double buffering : normaly it can
       * be configured with some video utility on the system basis (it can be
       * done in linux). But the problem is that in windows, it's very hard to
       * do, and the default is NOT to use double buffer on the overlays.
       * So if we want to have double buffer here, we must call flip
       * explicitely. */
      SDL_Flip(sdl_screen);
    }
    return;
  } else { // no overlay, classical blit
    int locked;

    if (display_cfg.stretch && use_scale2x) {
      // use_scale2x gives the factor : 1 = 2x, 2 = 3x, etc...
#ifndef NO_ASM
      switch(display_cfg.stretch) {
	case 1: // scale2x/3x
	  locked = lock_surface(sdl_screen);
	  if (locked > -1) {
	    if (use_scale2x == 1) {
	      raine_blit_scale2x(source, screen, x1, y1, x2, y2, w, h);
	    } else if (use_scale2x == 2) {
	      raine_blit_scale3x(source, screen, x1, y1, x2, y2, w, h);
	    }
	    if (locked) SDL_UnlockSurface(sdl_screen);
	  }
	  break;
	case 2: // pixel double
	  locked = lock_surface(sdl_screen);
	  if (locked > -1) {
	    my_blit_x2_y2(source,screen,x1,y1,x2,y2,w,h);
	    if (locked) SDL_UnlockSurface(sdl_screen);
	  }
	  break;
	case 3: // hq2x,3x
	  if (display_cfg.bpp == 8)
	    display_cfg.stretch = 1; // hq2x doesn't work in 8bpp, use scale2x
	  locked = lock_surface(sdl_screen);
	  if (locked > -1) {
	    if (use_scale2x == 1)
		switch(sdl_screen->format->BitsPerPixel) {
		case 16: hq2x_16(source,screen,x1,y1,x2,y2,w,h); break;
		case 32: hq2x_32(source,screen,x1,y1,x2,y2,w,h); break;
			 // Notice : in 32bpp, this thing needs a 16bpp source, so we must
			 // setup a special format for it in compat.c
		}
	    else if (use_scale2x == 2)
		switch(sdl_screen->format->BitsPerPixel) {
		case 16: hq3x_16(source,screen,x1,y1,x2,y2,w,h); break;
		case 32: hq3x_32(source,screen,x1,y1,x2,y2,w,h); break;
		}
	    __asm__ __volatile__("finit\n"); // restore fpu status after mmx code
	    if (locked) SDL_UnlockSurface(sdl_screen);
	  }
	  break;
      }
#endif
    } else {
      area1.x = x1;
      area1.y = y1;
      area1.w = w;
      area1.h = h;

      /* Notice : SDL_BlitSurface takes care of the palette handling,
       * which forces me to update the logical palette of the game
       * screen and the game bitmap at the same time before the blit.
       * Maybe it would be faster to update only the screen palette and
       * then use some memcpys here instead of SDL_BlitSurface for 8bpp.
       * But since the vast majority of games now run in 16bpp, it's probably
       * not worth the trouble */
      ret = SDL_BlitSurface(sdl_game_bitmap, &area1,
	  sdl_screen, &area2);
      if (ret) printf("got %d\n",ret);
    }
  }
  if ( sdl_screen->flags & SDL_DOUBLEBUF ) {
    SDL_Flip(sdl_screen);
  } else {
    SDL_UpdateRects(sdl_screen,1,&area2);
  }
}

static void update_screen_palette(PALETTE palette)
{
/*  PALETTE pal2;

  memcpy(pal2,pal,sizeof(PALETTE));
  for (ret=0; ret<256; ret++) {
    pal2[ret].r <<= 2;
    pal2[ret].g <<= 2;
    pal2[ret].b <<= 2;
  } */

  if (display_cfg.bpp != 8) return;
#ifdef RDTSC_PROFILE
   if(raine_cfg.show_fps_mode>2){
      ProfileStop(PRO_BLIT);
      ProfileStart(PRO_PAL);
   }
#endif

   // apparently calling sdl_setpalette waits for a vsync, so it's more
   // efficient to call a memcmp like this than calling sdl_setpalette all the
   // time !!! and for I don't know which reason, calling memcpy directly to
   // just copy pal over sdl_screen->format->palette->colors doesn't work
   if (memcmp(pal,sdl_screen->format->palette->colors,sizeof(SDL_Color)*256)){
   if (use_scale2x == 0) { // must test use_scale2x
     // display_cfg.stretch is the desired scaler, but use_scale2x is the
     // amount of scaling actually used (0 = normal blits).
     SDL_SetPalette(sdl_game_bitmap,SDL_LOGPAL,(SDL_Color*)pal,0,256);
     SDL_SetPalette(sdl_screen,SDL_LOGPAL|SDL_PHYSPAL,(SDL_Color*)pal,0,256);
   } else {
     // with scalers, only the physical palette needs to be updated
     // ret = SDL_SetPalette(sdl_screen,SDL_PHYSPAL,(SDL_Color*)pal,0,256);
     // optimisation disabled : it prevents bg_layer to use game bitmap since
     // its logical palette isn't updated anymore !!!
     SDL_SetPalette(sdl_game_bitmap,SDL_LOGPAL,(SDL_Color*)pal,0,256);
     SDL_SetPalette(sdl_screen,SDL_LOGPAL|SDL_PHYSPAL,(SDL_Color*)pal,0,256);
   }
   }

#ifdef RDTSC_PROFILE
   if(raine_cfg.show_fps_mode>2){
      ProfileStop(PRO_PAL);
      ProfileStart(PRO_BLIT);
   }
#endif
}

void DrawNormal(void)
{
  int i,locked;
  SDL_Rect s1,s2;

   /*

   save screenshots now (before we overwrite the image)

   */
  if (old_draw) return;

   /*

   scroll game screen

   */

   if (raine_cfg.req_pause_scroll) {
     if(raine_cfg.req_pause_scroll & 1)
        if(yoff2 > GameScreen.ytop)
  	  yoff2--;

     if(raine_cfg.req_pause_scroll & 2)
        if((yoff2 + disp_screen_y) < (GameScreen.ytop + GameScreen.yview))
	  yoff2++;

     if(raine_cfg.req_pause_scroll & 4)
        if(xoff2 > GameScreen.xtop)
	  xoff2--;

     if(raine_cfg.req_pause_scroll & 8)
        if((xoff2 + disp_screen_x) < (GameScreen.xtop + GameScreen.xview))
	  xoff2++;

     raine_cfg.req_pause_scroll = 0;
   }

   if(raine_cfg.req_save_screen == 1)
      do_save_screen();

   /*

   draw the ingame 'interface' (message list, fps)

   */

   if (!ogl.overlay || !(sdl_screen->flags & SDL_OPENGL))
       overlay_ingame_interface(0);
   else
       overlay_ingame_interface(1);
   if (sdl_screen->flags & SDL_OPENGL)
       finish_opengl(); // overlay interface eventually !

   /*

   update host (pc) palette

   */

   update_screen_palette(pal);

   /*

   blit image to host (pc) videoram

   */

   if (sdl_screen->flags & SDL_OPENGL) {
       draw_opengl(ogl.filter);
       RefreshBuffers = 0;
       return;
   }

   switch(display_cfg.scanlines){
     // scanlines must be able to work with other video effects, at least
     // for double width. But there were too many modes which worked badly
     // with the previous hack (modifying directly the line pointers in the
     // screen bitmap). This way should be a little slower but much more
     // reliable.

     case 0:
       raine_fast_blit(GameBitmap, screen, xoff2, yoff2, destx, desty, xxx, yyy);
       break;
     case 1:
       // half height
       s1.x = xoff2;
       s1.w = xxx;
       s1.h = 1;
       s2.x = destx;
       s2.w = s1.w;
       s2.h = s1.h;
       for (i=0; i<yyy; i+=2) {
	   s1.y = yoff2+i;
	   s2.y = desty+i;
	   SDL_BlitSurface(sdl_game_bitmap, &s1, sdl_screen, &s2);
       }
       if ( sdl_screen->flags & SDL_DOUBLEBUF ) {
	 SDL_Flip(sdl_screen);
       } else {
	 SDL_UpdateRects(sdl_screen,1,&area2);
       }
       break;
     case 2: {
       int end;
       end = MIN(2*yyy,screen->h-1)/2;
       // full height scanlines
       s1.x = xoff2;
       s1.w = xxx;
       s1.h = 1;
       s2.x = destx;
       s2.w = s1.w;
       s2.h = s1.h;
       for (i=0; i<end; i++) {
	   s1.y = yoff2+i;
	   s2.y = desty+i*2;
	   SDL_BlitSurface(sdl_game_bitmap, &s1, sdl_screen, &s2);
       }
       if ( sdl_screen->flags & SDL_DOUBLEBUF ) {
	 SDL_Flip(sdl_screen);
       } else {
	 s2.y = desty;
	 s2.h = end*2;
	 SDL_UpdateRects(sdl_screen,1,&s2);
       }
       break;
	     }
     case 3:
	     { // fullheight + double width
	     int end = 0;
	     locked = lock_surface(sdl_screen);
	     if (locked > -1) {
	       end = MIN(2*yyy,screen->h-1)/2;
	       // full height scanlines
	       s1.x = xoff2;
	       s1.w = xxx;
	       s1.h = 1;
	       s2.x = destx;
	       s2.w = s1.w;
	       s2.h = s1.h;
	       for (i=0; i<end; i++) {
		 s1.y = yoff2+i;
		 s2.y = desty+i*2;
		 // SDL_BlitSurface(sdl_game_bitmap, &s1, sdl_screen, &s2);
		 my_blit_x2_y1(GameBitmap,screen,s1.x,s1.y,s2.x,s2.y,s1.w,s1.h);
	       }

	       if (locked) SDL_UnlockSurface(sdl_screen);
	     }
	     if ( sdl_screen->flags & SDL_DOUBLEBUF ) {
	       SDL_Flip(sdl_screen);
	     } else {
	       s2.y = desty;
	       s2.h = end*2;
	       s2.w = xxx*2;
	       SDL_UpdateRects(sdl_screen,1,&s2);
	     }
	     break;
	     }
   }
   RefreshBuffers = 0;
}

void clear_game_screen(int pen)
{
  int x,y,len;
  switch(display_cfg.bpp) {
  case 8:
    len = GameViewBitmap->w;
    for (y=0; y<GameViewBitmap->h; y++)
      memset(GameViewBitmap->line[y],pen,len);
    break;
  case 15:
  case 16:
    len = GameViewBitmap->w*2;
    pen = (pen & 0xffff) | (pen<<16);
    for (y=0; y<GameViewBitmap->h; y++) {
      unsigned char *src = GameViewBitmap->line[y];
      for (x=0; x<len; x+= 4) {
	WriteLong(&src[x],pen);
      }
    }
    break;
  case 32:
    len = GameViewBitmap->w*4;
    for (y=0; y<GameViewBitmap->h; y++) {
      unsigned char *src = GameViewBitmap->line[y];
      for (x=0; x<len; x+= 4) {
	WriteLong(&src[x],pen);
      }
    }
    break;
  }
}

void get_screen_coordinates(int *Xoff2,int *Yoff2, int *Destx, int *Desty, int *Xxx, int *Yyy){
  *Xoff2 = xoff2;
  *Yoff2 = yoff2;
  *Xxx = xxx;
  *Yyy = yyy;
  *Destx = destx;
  *Desty = desty;
}

