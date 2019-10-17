#ifdef RAINE_WIN32
#include <allegro.h>
#include <winalleg.h>
#elif defined(RAINE_UNIX)
#include <sys/time.h>
#endif
#include "blit_x2.h"
#include "eagle.h"
#include "games.h" // current_game for save_screen
#include "ingame.h" // print_ingame
#include "deftypes.h"
#include "blit.h"
#include "palette.h"
#include "sasound.h" // sa_pause_sound
#include "emumain.h" // init_gui_inputs_paused
#include "profile.h" // reset_ingame_timer
#include "tilemod.h"
#include "scale2x.h"
#include "cpuid.h"
#include "blitasm.h"
#include "video/res.h"
#include "loadpng.h"
#include "bezel.h"
#ifndef RAINE_DOS
#include "sdl/SDL_gfx/SDL_framerate.h"
#endif

/* Still a collision here between winalleg.h and control.h */
void init_gui_inputs_paused(void);
void init_gui_inputs(void);
BITMAP *GameBitmap; 	// *Full* Bitmap for generating the game screen (eg. 0,0 to 320+32,240+32)
BITMAP *GameViewBitmap; 	// *Viewable* Bitmap for saving (pcx) the game screen (eg. 16,16 to 320+16,240+16)

static int triple_frame;
static int destx, desty, xxx, yyy, xoff2, yoff2;
static int disp_screen_x;
static int disp_screen_y;
UINT32 pause_time;
int recording_video = 0,last_video_frame,video_fps;

int key_data[MAX_LAYER_INFO]=
{
   KEY_F5,
   KEY_F6,
   KEY_F7,
   KEY_F8,
   KEY_F9,
   KEY_F10,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
   KEY_F12,
};

static void scroll_async(int page);

RAINEBITMAP GameScreen;

BITMAP *BlitSource;		// *Full*
BITMAP *BlitViewSource; 	// *Viewable* part of bitmap

void get_screen_coordinates(int *Xoff2,int *Yoff2, int *Destx, int *Desty, int *Xxx, int *Yyy){
  *Xoff2 = xoff2;
  *Yoff2 = yoff2;
  *Xxx = xxx;
  *Yyy = yyy;
  *Destx = destx;
  *Desty = desty;
}

/*

.----.
|    | Current Onscreen Frame
|----|
|    | Next Frame - Blit here then request to display it (it's not immediately shown)
|----|
|    | Next-Next Frame - Incase the pc refresh rate is less than the game refresh rate
'----'

*/

void raine_blit_eagle(BITMAP *src, BITMAP *dest, int s_x, int s_y, int d_x, int d_y, int w, int h)
{
   UINT32 ta;

   for(ta=0;ta<(UINT32)(h-1);ta++){

   eagle(
      (unsigned long *) (src->line[ta+s_y]+s_x),
      (unsigned long *) (src->line[ta+s_y+1]+s_x),
      (UINT16) w,
      dest->seg,
      (UINT32) (dest->line[ta*2+d_y]+d_x),
      (UINT32) (dest->line[ta*2+d_y+1]+d_x)
   );

   }

   ta = (h-1);

   eagle(
      (unsigned long *) (src->line[ta+s_y]+s_x),
      (unsigned long *) (src->line[ta+s_y]+s_x),
      (UINT16) w,
      dest->seg,
      (UINT32) (dest->line[ta*2+d_y]+d_x),
      (UINT32) (dest->line[ta*2+d_y]+d_x)
   );
}

extern void _xwin_update_screen (int x, int y, int w, int h);
extern int _xwin_in_gfx_call;
static UINT32 ds;
#ifdef RAINE_DOS
UINT32 es,oldes;
#endif

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
     switch (display_cfg.bpp) {
     case 8:
       SCALE2X(8,def); break;
     case 15:
     case 16:
       SCALE2X(16,def); break;
     case 32:
       SCALE2X(32,def); break;
     }
   }
#ifdef RAINE_DOS
   asm("mov _oldes,%es");
#endif
}

// Set changed colours. Since this is a slow thing on the pc,
// I must try to reduce it to be called when only needed.

extern int fbcon_enabled;
extern PALETTE pal_screen; // used to know if a color has changed or not...

static void my_set_palette_range(const PALETTE p, int from, int to, int vsync) {
  /* using set_palette should go faster in a normal world
   * except that allegro is full of bugs, and if you call that with a screen
   * in 16bpp or more, then this stupid thing will wait for vsync and you'll
   * spend 90% of cpu time in here !!! What a piece of crap... */
  if (from == 0 && to == 255)
    set_palette(p);
  else
    set_palette_range(p,from,to,vsync);
}

static void update_screen_palette(PALETTE palette)
{
#ifdef RDTSC_PROFILE
   if(raine_cfg.show_fps_mode>2){
      ProfileStop(PRO_BLIT);
      ProfileStart(PRO_PAL);
   }
#endif

   // In non 8 bpp modes it is pointless to update the palette as it is not required
	// or usable.
   if( internal_bpp(display_cfg.bpp) == 8 ){
#ifdef RAINE_UNIX
   if(display_cfg.fast_set_pal && !x_display)
#ifdef GFX_FBCON
     if (display_cfg.screen_type == GFX_FBCON){
        fast_palette_update_8(palette,pal_screen,display_cfg.vsync);
     } else		// User has a lame gfx card/vesa driver
#endif
      fast_palette_update(palette,pal_screen,display_cfg.vsync);
   else		// User has a lame gfx card/vesa driver
	  my_set_palette_range(palette,0,255,display_cfg.vsync);
#else
   if(display_cfg.fast_set_pal)
#ifdef RAINE_WIN32
  // Avoid windowed mode. Windows is stupid enough to authorize direct
  // palette update in windowed mode, but it trashes the screen if the desktop
  // is in 16bpp (or over) !!!
     // os_version <=4 uses only win9x. Crashes in win2k.
     // Not checked in millenium or xp.
      if (os_version <=4 && display_cfg.screen_type != GFX_GDI &&
	    display_cfg.screen_type != GFX_DIRECTX_OVL &&
	    display_cfg.screen_type != GFX_AUTODETECT &&
	    display_cfg.screen_type != GFX_DIRECTX_WIN) {
	if (display_cfg.fast_set_pal == 1)
	      fast_palette_update_8(palette,pal_screen,display_cfg.vsync);
	else
	      fast_palette_update(palette,pal_screen,display_cfg.vsync);
      } else
        my_set_palette_range(palette,0,255,display_cfg.vsync);
#else
      fast_palette_update(palette,pal_screen,display_cfg.vsync);
#endif
   else		// User has a lame gfx card/vesa driver
      my_set_palette_range(palette,0,255,display_cfg.vsync);
#endif // RAINE_UNIX
   }

#ifdef RDTSC_PROFILE
   if(raine_cfg.show_fps_mode>2){
      ProfileStop(PRO_PAL);
      ProfileStart(PRO_BLIT);
   }
#endif
}

extern BITMAP *tpage[3];

void raine_fast_blit(BITMAP *source, BITMAP *dest, UINT32 x1, UINT32 y1, UINT32 x2, UINT32 y2, UINT32 w, UINT32 h)
{
#if defined(RAINE_UNIX) || defined(RAINE_WIN32)
  int force_update = (display_cfg.bpp > 8);
#endif

   /*

   hack -- fool allegro into allowing offscreen blits

   */

#ifdef TRIPLE_BUFFER

   if(display_cfg.triple_buffer){

     dest = tpage[triple_frame];

   }

#endif

   /*

   do the required blit

   */

//   print_debug("(0x%04x, 0x%04x) (0x%04x, 0x%04x)\n", x1, y1, x2, y2);

   if (display_cfg.stretch && !display_cfg.scanlines) {
     if (display_cfg.stretch == 1) {
       stretch_blit(source, dest, x1, y1, w, h, x2, y2, stretchx, stretchy);
     } else
       stretch_blit(source, dest, x1, y1, w, h, x2, y2, display_cfg.screen_x,
		    display_cfg.screen_y);
   } else

#if defined(TRIPLE_BUFFER)

   if(is_linear_bitmap(dest) && (gfx_driver->linear)){

      if(display_cfg.pixel_double){

	 if(display_cfg.pixel_double == 1)
	 {
	    switch(display_cfg.bpp)
	    {
	       case 8:
		  raine_blit_x2_y2(source, dest, x1, y1, x2*2, (y2*2), w, h);
	       break;
	       case 15:
	       case 16:
		  raine_blit_x2_y2_16(source, dest, x1, y1, x2*2, (y2*2), w, h);
	       break;
	       case 24:
		  raine_blit_x2_y2_24(source, dest, x1, y1, x2*2, (y2*2), w, h);
	       break;
	       case 32:
		  raine_blit_x2_y2_32(source, dest, x1, y1, x2*2, (y2*2), w, h);
	       break;
	    }
	 }
	 else
	 {
	    switch(display_cfg.bpp)
	    {
	       case 8:
		  raine_blit_x2_y1(source, dest, x1, y1, x2*2, (y2*1), w, h);
	       break;
	       case 15:
	       case 16:
		  raine_blit_x2_y1_16(source, dest, x1, y1, x2*2, (y2*1), w, h);
	       break;
	       case 24:
		  raine_blit_x2_y1_24(source, dest, x1, y1, x2*2, (y2*1), w, h);
	       break;
	       case 32:
		  raine_blit_x2_y1_32(source, dest, x1, y1, x2*2, (y2*1), w, h);
	       break;
	    }
	 }

      } else if(display_cfg.eagle_fx && display_cfg.bpp == 8) {
	raine_blit_eagle(source, dest, x1, y1, x2*2, (y2*2), w, h);
      } else if (use_scale2x) {
	raine_blit_scale2x(source, dest, x1, y1, x2*2, (y2*2), w, h);
      } else {
	blit(source, dest, x1, y1, x2, y2, w, h);
#if defined(RAINE_UNIX) || defined(RAINE_WIN32)
	force_update = 0;
#endif
      }
      // Fixes video effects in windowed modes
      /* For now (allegro-4.1.11), there is no "standard" way to do it, but it's
	 posted to the allegro-dev list, and they are working on a solution */
#ifdef RAINE_UNIX
      // the x11 fullscreen mode is handled like a windowed mode (where you can't see
      // the window decorations)

      if (force_update && (display_cfg.screen_type == GFX_XWINDOWS
#ifdef GFX_XWINDOWS_FULLSCREEN
			      ||
			   display_cfg.screen_type == GFX_XWINDOWS_FULLSCREEN
#endif
			   )) {
	if(display_cfg.pixel_double==1 || use_scale2x)
	  _xwin_update_screen(x2*2,y2*2,w*2,h*2);
	else if (display_cfg.pixel_double)
	  _xwin_update_screen(x2*2,y2,w*2,h);
      }
#elif defined(RAINE_WIN32)
      if (force_update && (display_cfg.screen_type == GFX_DIRECTX_WIN)) {
	RECT r;
	r.left = x2*2; r.top = y2*2;
	r.right = (x2+w)*2;
	if(display_cfg.pixel_double==1 || use_scale2x) {
	  r.bottom = (y2+h)*2;
	  win_gfx_driver->paint(&r);
	} else if (display_cfg.pixel_double) {
	  r.bottom = y2*2+h;
	  win_gfx_driver->paint(&r);
	}
      }
#endif
   } else{ // not linear

     blit(source, dest, x1, y1, x2, y2, w, h);
   }

#else

   blit(source, dest, x1, y1, x2, y2, w, h);

#endif

}

/**[Screenshot Saving]*****************************************/

static void do_save_screen(void)
{
   char full_name[256];
   char file_name[32];
   char *extension = (display_cfg.screenshot_png ? "png" : "pcx");

   raine_cfg.req_save_screen = 0;

   /*

   first try gamename.pcx

   */

   sprintf(file_name, "%s.%s", current_game->main_name,extension);

   sprintf(full_name, "%s%s", dir_cfg.screen_dir, file_name);


   if (recording_video) {
     int current_video_frame = cpu_frame_count*video_fps / fps;

     if (current_video_frame != last_video_frame) {
       sprintf(full_name,"%s%s_%06d.%s",dir_cfg.screen_dir, current_game->main_name,cpu_frame_count,extension);
       if (display_cfg.screenshot_png)
	 save_png(full_name, BlitViewSource, pal);
       else
	 save_pcx(full_name, BlitViewSource, pal);
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
	 sprintf(file_name, "%s_%03d.%s", current_game->main_name, dir_cfg.last_screenshot_num++,extension);
       else
	 sprintf(file_name, "%.5s%03d.%s", current_game->main_name, dir_cfg.last_screenshot_num++,extension);
       sprintf(full_name, "%s%s", dir_cfg.screen_dir, file_name);
     };
     if (display_cfg.screenshot_png)
       save_png(full_name, BlitViewSource, pal);
     else
       save_pcx(full_name, BlitViewSource, pal);
     print_ingame(120, "Screen Saved to %s", file_name);
   }

}

// DrawNormal():
// Clips/Blits game screen from pc memory > pc vram
// Also overlays the messages, fps counter...

extern void *old_draw; // dlg_sound

void DrawNormal(void)
{
  UINT16 i;
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

   if(raine_cfg.req_save_screen || recording_video)
      do_save_screen();

   /*

   draw the ingame 'interface' (message list, fps)

   */

   overlay_ingame_interface(0);

   /*

   update host (pc) palette

   */

   update_screen_palette(pal);

   /*

   blit image to host (pc) videoram

   */

   switch(display_cfg.scanlines){
     // scanlines must be able to work with other video effects, at least
     // for double width. But there were too many modes which worked badly
     // with the previous hack (modifying directly the line pointers in the
     // screen bitmap). This way should be a little slower but much more
     // reliable.

   case 0:
     raine_fast_blit(BlitSource, screen, xoff2, yoff2, destx, desty, xxx, yyy);
     break;
   case 1:
     // full height scanlines
     for (i=0; i<yyy; i+=2)
       raine_fast_blit(BlitSource, screen, xoff2, yoff2+i, destx, i, xxx, 1);
     break;
   case 2: {
     int end = MIN(2*yyy,screen->h-1)/2;
     // half height scanlines
     for (i=0; i<end; i++)
       raine_fast_blit(BlitSource, screen, xoff2, yoff2+i, destx, i*2, xxx, 1);
     break;
   }
   }

   if (display_cfg.bpp > 8 && display_cfg.vsync) {
       // on depths > 8, palette is not updated, so vsync must be taken care
       // of
       show_video_bitmap(screen);
   }

   if (display_cfg.triple_buffer) {
     scroll_async(triple_frame);
     triple_frame ++;

     if(triple_frame > 2)
       triple_frame = 0;
   }

   if(raine_cfg.req_save_screen == 2)
      do_save_screen();

   RefreshBuffers = 0;
}

void DrawPaused(void)
{
   DrawNormal();		// Overlay text interface, blit to screen

   pause_time++;

   if(display_cfg.limit_speed==1){
#ifndef RAINE_DOS
	      SDL_framerateDelay(&fpsm);
#else
      while( read_ingame_timer() < cpu_frame_count){
// No way to save cpu power in dos AFAIK
      }
#endif
   }
}

void ReClipScreen(void)
{
   // clip x

  int oldxview,oldyview;

  oldxview = GameScreen.xview;
  oldyview = GameScreen.yview;
  if (display_cfg.stretch && GameScreen.xview > 0) {
    if (display_cfg.stretch == 1) {
      GameScreen.xview = stretchx;
      GameScreen.yview = stretchy;
    } else {
      GameScreen.xview = disp_screen_x;
      GameScreen.yview = disp_screen_y;
    }
  }

  if(GameScreen.xview < disp_screen_x){
    destx = (disp_screen_x - GameScreen.xview)>>1;
  }
  else{
    destx = 0;
  }
  if (oldxview < disp_screen_x) {
    // We can't write outside the game bitmap so we have to use oldxview
    xxx = oldxview;
    xoff2 = GameScreen.xtop;
  } else {
    // If the game bitmap is bigger than the screen, then no risk (if stretched)
    if(GameScreen.xview <= disp_screen_x){
      xxx = oldxview;
      xoff2 = GameScreen.xtop;
    } else {
      xxx = disp_screen_x;
      xoff2 = GameScreen.xtop + ((GameScreen.xview - disp_screen_x)>>1);
    }
  }

  // clip y

  if(GameScreen.yview < disp_screen_y){
    desty = (disp_screen_y - GameScreen.yview)>>1;
  }
  else{
    desty = 0;
  }

  if(GameScreen.yview < disp_screen_y && GameScreen.xview < disp_screen_x)
    bezel_fix_screen_coordinates(&destx,&desty,GameScreen.xview,GameScreen.yview,disp_screen_x,disp_screen_y);

  if(oldyview < disp_screen_y){
    yyy = oldyview;
    yoff2 = GameScreen.ytop;
  } else {
    if(GameScreen.yview <= disp_screen_y){
      yyy = oldyview;
      yoff2 = GameScreen.ytop;
    } else {
      yyy = disp_screen_y;
      yoff2 = GameScreen.ytop + ((GameScreen.yview - disp_screen_y)>>1);
    }
  }

  GameScreen.xview = oldxview;
  GameScreen.yview = oldyview;
}

void clear_game_screen(int pen)
{
   clear_to_color(GameViewBitmap, pen);
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
      GameScreen.xfull=xfull;
      GameScreen.yfull=yfull;
      GameScreen.xtop =xtop;
      GameScreen.ytop =ytop;
      GameScreen.xview=xview;
      GameScreen.yview=yview;
   break;
   case 0x01:
      GameScreen.xfull=yfull;
      GameScreen.yfull=xfull;
      GameScreen.xtop =ytop;
      GameScreen.ytop =xtop;
      GameScreen.xview=yview;
      GameScreen.yview=xview;
   break;
   case 0x02:
      GameScreen.xfull=xfull;
      GameScreen.yfull=yfull;
      GameScreen.xtop =xtop;
      GameScreen.ytop =ytop;
      GameScreen.xview=xview;
      GameScreen.yview=yview;
   break;
   case 0x03:
      GameScreen.xfull=yfull;
      GameScreen.yfull=xfull;
      GameScreen.xtop =ytop;
      GameScreen.ytop =xtop;
      GameScreen.xview=yview;
      GameScreen.yview=xview;
   break;
   }

   check_tile_rotation();

   disp_screen_y = display_cfg.screen_y;
   disp_screen_x = display_cfg.screen_x;

   /*

   these modes double the image size (it's simpler to consider
   them as halving the display resolution)

   */

   if(is_linear_bitmap(screen) && (gfx_driver->linear)){

     if (use_scale2x) {
       disp_screen_x /= 2;
       disp_screen_y /= 2;
     } else if(display_cfg.pixel_double){

	 if(display_cfg.pixel_double == 1){

	    disp_screen_x /= 2;
	    disp_screen_y /= 2;

	 }
	 else{

	    disp_screen_x /= 2;

	 }

      }
      else{

	 if(display_cfg.bpp == 8){

	    if(display_cfg.eagle_fx){

	       disp_screen_x /= 2;
	       disp_screen_y /= 2;

	    }

	 }

      }

   }

   ReClipScreen();
}

void SetupScreenBitmap(void)
{
   const VIDEO_INFO *vid_info;

   vid_info = current_game->video;

   SetScreenBitmap(
      vid_info->screen_x + vid_info->border_size + vid_info->border_size,
      vid_info->screen_y + vid_info->border_size + vid_info->border_size,
      vid_info->border_size,
      vid_info->border_size,
      vid_info->screen_x,
      vid_info->screen_y
   );

   GameBitmap = create_bitmap_ex(internal_bpp(display_cfg.bpp), GameScreen.xfull, GameScreen.yfull);
   // GameBitmap = create_system_bitmap( GameScreen.xfull, GameScreen.yfull);
   if (!GameBitmap->seg) {
     /* This means that allegro was compiled with the C graphics core
	only, which is a stupidity. Anyway, we try to guess the correct value
	for ds here. It should work in linux, unix, etc... but maybe not in
	djgpp. If you crash in raine_fast_blit, you'll know where it comes
	from ! */
       ds = 3; // must init it here, or the optimizer removes ds as unused
       // static variable, quite unfortunate !
#ifndef RAINE_UNIX
     asm(" mov %ds,_ds ");
#else
     asm(" mov %ds,ds ");
#endif
     GameBitmap->seg = ds;
     screen->seg = ds;
   }
   GameViewBitmap = create_sub_bitmap(GameBitmap, GameScreen.xtop, GameScreen.ytop, GameScreen.xview, GameScreen.yview);
   InitLUTs();

   display_bezel();
   clear_bitmap(GameViewBitmap);

   BlitSource = GameBitmap;
   BlitViewSource = GameViewBitmap;

   RefreshBuffers=1;
}

void DestroyScreenBitmap(void)
{
   if (GameViewBitmap) {
     destroy_bitmap(GameViewBitmap);
     destroy_bitmap(GameBitmap);
     GameViewBitmap = NULL;
     GameBitmap = NULL;
   }
}

void reset_triple_buffer(void)
{
   if(display_cfg.triple_buffer){
      triple_frame = 0;
      scroll_async(0);
   }
}

#ifdef TRIPLE_BUFFER

#define ALLEGRO_SCROLL_CHANGED

#ifdef ALLEGRO_SCROLL_CHANGED

/*

This version requires modifications to allegro (works in vbe/af and stuff)

*/

static void scroll_async(int page )
{
  /* make sure the last flip request has actually happened */
  do {
  } while (poll_scroll());

  /* post a request to display the page we just drew */
  request_video_bitmap(tpage[page]);
}

#else

/*

This version is the mame hack of allegro (works in less modes, because it
is only based on the vesa 1/2/3 code)

*/

static int scroll_async(int x, int y)
{
   int ret, seg;
   long a;
	extern void (*_pm_vesa_scroller)(void); /* in Allegro */
	extern int _mmio_segment;	/* in Allegro */
	#define BYTES_PER_PIXEL(bpp)	 (((int)(bpp) + 7) / 8) /* in Allegro */
	extern __dpmi_regs _dpmi_reg;	/* in Allegro... I think */

   if (_pm_vesa_scroller) {	       /* use protected mode interface? */
      seg = _mmio_segment ? _mmio_segment : _my_ds();

      a = ((x * BYTES_PER_PIXEL(screen->vtable->color_depth)) +
	   (y * ((unsigned long)screen->line[1] - (unsigned long)screen->line[0]))) / 4;

      asm (
	 "  pushw %%es ; "
	 "  mov %w1, %%es ; "         /* set the IO segment */
	 "  call *%0 ; "               /* call the VESA function */
	 "  popw %%es "

      : 			       /* no outputs */

      : "S" (_pm_vesa_scroller),       /* function pointer in esi */
	"a" (seg),                     /* IO segment in eax */
	"b" (0x00),                    /* mode in ebx */
	"c" (a & 0xFFFF),              /* low word of address in ecx */
	"d" (a >> 16)                  /* high word of address in edx */

      : "memory", "%edi", "%cc"        /* clobbers edi and flags */
      );

      ret = 0;
   }
   else {			       /* use a real mode interrupt call */
      _dpmi_reg.x.ax = 0x4F07;
      _dpmi_reg.x.bx = 0;
      _dpmi_reg.x.cx = x;

      if(display_cfg.scanlines == 2)
	 _dpmi_reg.x.dx = y * 2;
      else
	 _dpmi_reg.x.dx = y;

      __dpmi_int(0x10, &_dpmi_reg);
      ret = _dpmi_reg.h.ah;

   }

   return (ret ? -1 : 0);
}

#endif // ALLEGRO_SCROLL_CHANGED

#endif // TRIPLE_BUFFER
