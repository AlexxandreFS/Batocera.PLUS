/******************************************************************************/
/*									      */
/*	    RAINE MAIN EMULATION ROUTINES (run game, reset game etc)	      */
/*									      */
/******************************************************************************/

#include "conf-cpu.h"
#ifndef SDL
#ifdef RAINE_WIN32
#include <allegro.h>
#include <winalleg.h>
#endif
#endif

#ifdef RAINE_UNIX
#include <sys/time.h>
#endif

#include "raine.h"              // General defines and stuff
#ifndef SDL
#include "gui.h"                // Interface stuff
#ifdef RAINE_DEBUG
#include "alleg/debug/dbg_gui.h"
#endif
#include "alleg/gui/sound.h" // old_draw
#else
#include "sdl/gui.h"
#endif
#include "sasound.h"            // Sound Sample stuff
#include "dsw.h"                // Dipswitch stuff
#include "ingame.h"             // screen handling routines
#include "hiscore.h"
#include "palette.h"

#ifdef HAVE_6502
#include "m6502.h"              // M6502 Engine
#include "m6502hlp.h"           // M6502 Support Interface
#endif
#ifndef NO020
#include "68020.h"              // M68020 Engine + Support Interface
#endif
#include "games.h"              // Game list

#include "cpumain.h"            // main loops
#include "newspr.h"
#include "demos.h"
#include "blit.h" // Triple buffer functions
#include "profile.h"
#include "timer.h"
#include "savegame.h" // do_load/save-state
#include "mz80help.h"
#include "config.h"             // Command Line + Config file routines
#include "history.h" // hist_open
#ifndef RAINE_DOS
#include "sdl/SDL_gfx/SDL_framerate.h"
#endif
#include "neocd/cdda.h"

/* Including control.h in windows makes a collision with windows.h. Sigh...
   I can avoid to fix this by just adding these declarations here : */
/* The collision is because of INPUT in control.h.
   The fact that Antiriad declared a type named INPUT in 98 is easy to understand
   The fact that windows did the same in a standard include file used by millions of
   program is yet another stupidity from microsoft */
/* Including emumain.h makes yet another collision in windows, this time for the type
   returned by a function. 2nd sigh */

extern int GameMouse;
#ifndef SDL
extern void init_gui_inputs();
extern void update_leds(void);
extern void init_leds(void);
extern void force_update_leds(void);
#endif

extern void update_rjoy_list(void);
extern void update_inputs(void);
extern void update_gui_inputs(void);

UINT32 cpu_fps;
UINT32 quit_loop;

int req_fwd;

static int pause_frame;

void key_pause_fwd()
{
  if (raine_cfg.req_pause_game) {// only makes sense while in pause...
      cpu_frame_count = pause_frame++;
      reset_ingame_timer();
      req_fwd = 1; // could contain more than 1 frame...
      raine_cfg.req_pause_game = 0;
  }
}

void key_pause_game(void)
{
	raine_cfg.req_pause_game ^= 1;
	/* There would also be the possibility to stop cpu_frame_count while
	 * in pause, but actually the variable has not exactly a good name
	 * anymore since it's used to count the number of drawn frames and to
	 * limit the display to 60 fps. So if we stop cpu_frame_count then
	 * the screen is updated as often as possible while in pause mode,
	 * which is not a good idea... */
	if (raine_cfg.req_pause_game) {
	    sa_pause_sound();
	    pause_frame = cpu_frame_count;
	} else {
	    sa_unpause_sound();
	    cpu_frame_count = pause_frame; // for the demos eventually
	    reset_ingame_timer();
	}
}

void key_stop_emulation_esc(void)
{
#ifndef SDL
  if (!old_draw) {
#endif
    quit_loop = 1;
#ifndef SDL
  }
#endif
}

void key_stop_emulation_tab(void)
{
#ifndef SDL
  if (!old_draw) {
#endif
   quit_loop = 2;
#ifndef SDL
  }
#endif
}

extern int recording;
extern void update_monitoring();
#ifdef SDL
FPSmanager fpsm;
#endif

UINT32 run_game_emulation(void)
{
   UINT32 cpu_tick;
   UINT32 draw_screen;
   const VIDEO_INFO *vid_info;
   char str[256];

   print_debug("run_game_emulation(): Setting up...\n");

   cpu_tick = 0;
   quit_loop = 0;
   raine_cfg.req_save_screen = 0;

   print_debug("Init Timer...\n");

   start_ingame_timer();

#ifndef SDL
   print_debug("Init Keyboard...\n");
   install_keyboard();

   init_gui_inputs();
#endif

   // For neocd, video initialization is done BEFORE loading
   print_debug("Init Screen Buffer...\n");
   SetupScreenBitmap();

   print_debug("Init Video Core...\n");
   init_video_core();

#ifndef SDL
#ifdef RAINE_WIN32
   install_mouse();
   show_mouse(NULL);
#else
   if(GameMouse){
   print_debug("Init mouse...\n");
   install_mouse();
   show_mouse(NULL);
   }
#endif

   print_debug("Init LED Emulation...\n");
   force_update_leds();
#endif

   print_debug("Init Colour Mapping...\n");
   reset_palette_map();

#ifdef TRIPLE_BUFFER
   print_debug("Init triple buffer...\n");
   reset_triple_buffer();
#endif

   print_debug("Init cpu emulation...\n");
   start_cpu_main();

   print_debug("run_game_emulation(): Running main loop...\n");

   vid_info = current_game->video;

   if(!vid_info->draw_game) {
       print_debug("quit game emulation because no draw_game function\n");
       quit_loop = 1; // I want the game to always draw
   }

   if (!raine_cfg.req_pause_game) {

       // Placing sound init just after the timer init should avoid begining
       // streaming out of a frame limit (it happens sometimes in linux !)
       print_debug("Init Sound...\n");
       if(GameSound){
	   // if(RaineSoundCard) {
	   // Call saInitSoundCard, and thus init_sound_emulators even if sound is disabled
	   // this fixes the rare game drivers which can't work without sound, like acrobat mission
	       saInitSoundCard( RaineSoundCard, audio_sample_rate );
	       if (is_neocd())
		   sa_unpause_sound();
	       // restore_cdda();
	   // }
       }
       print_debug("Reset ingame timer...\n");
       reset_ingame_timer();
   }

   // auto-save

   if (raine_cfg.auto_save & FLAG_AUTO_LOAD)
   {
      sprintf(str,"%s.sva",current_game->main_name);
      do_load_state(str);
   }
#ifdef SDL
   fpsm.use_cpu_frame_count = 1;
#endif

   while(!quit_loop && current_game){

     /* Handle sound FIRST : it is the most sensitive part for synchronisatino
      * So it MUST be at the begining (before getting any chance to be out
      * of sync !!! Too bad allegro does not seem to care very much about this
      */

      if (!raine_cfg.req_pause_game) {
#ifdef RDTSC_PROFILE
	  if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_FRAME);
	  if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_SOUND);
#endif

	  saUpdateSound(1);

#ifdef RDTSC_PROFILE
	  if(raine_cfg.show_fps_mode>2) ProfileStop(PRO_SOUND);
	  if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_CPU);
#endif
	  hs_update();
	  cpu_tick++;
	  if(cpu_tick>=cpu_fps){
	      cpu_tick=0;
	      if(current_game->exec) {
		  current_game->exec();
	      }
	  }

#ifdef RDTSC_PROFILE
	  if(raine_cfg.show_fps_mode>2) {
	      ProfileStop(PRO_CPU);
	  }
#endif
      }

      draw_screen = 0;
      cpu_frame_count ++;
      skip_frame_count ++;
      // extern UINT32 pc_timer;
      // printf("pc_timer %d render %d cpu %d skip %d\n",read_ingame_timer(),render_frame_count,cpu_frame_count,skip_frame_count);

      if(display_cfg.frame_skip){		// Manual frame skip
	 if(skip_frame_count >= display_cfg.frame_skip)
	    draw_screen = 1;
      }
      else if((read_ingame_timer() <= cpu_frame_count)||(skip_frame_count >= 60)) // Automatic frame skip
	draw_screen = 1;
      /* Notice : avoiding the frame skips while recording a video does not help because
	 of the sound ! */

      // Cheats are now updated in the overlay_interface in ingame.c (watches)
      if(draw_screen){

	// update video emulation bitmap


#ifdef RDTSC_PROFILE
	if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_RENDER);
#endif

	if (!raine_cfg.req_pause_game || RefreshBuffers)
	    vid_info->draw_game();
#ifdef RDTSC_PROFILE
	if(raine_cfg.show_fps_mode>2) ProfileStop(PRO_RENDER);
#endif

	// blit video emulation to pc hardware, also prints ingame messages

	if (recording) {
	  update_monitoring();
	}

#ifdef RDTSC_PROFILE
	if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_BLIT);
#endif

        // printf("blit at %d\n",SDL_GetTicks());
	BlitScreen();
	// printf("end of blit %d\n",SDL_GetTicks());

#ifdef RDTSC_PROFILE
	if(raine_cfg.show_fps_mode>2) ProfileStop(PRO_BLIT);
#endif

	skip_frame_count = 0;
	render_frame_count ++;

	// limit speed if we need to

	if((display_cfg.limit_speed) && (read_ingame_timer() <= cpu_frame_count)){
#ifdef RDTSC_PROFILE
	  if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_FREE);
#endif

#ifndef RAINE_DOS
	      SDL_framerateDelay(&fpsm);
#else
	      while(read_ingame_timer() < cpu_frame_count){	// Yikes! We're going TOO FAST!!
		// No way to save cpu power in dos AFAIK
	      }
#endif
#ifdef RDTSC_PROFILE
	  if(raine_cfg.show_fps_mode>2) ProfileStop(PRO_FREE);
#endif

	} // if (display_cfg.limit_speed...
#ifndef RAINE_DOS
	  else {
	    SDL_get_frame_count(&fpsm);
	    // printf("frame dropped\n");
	  }
#endif
      } else if (recording_video) { // if draw_screen
	int current_video_frame = cpu_frame_count*video_fps / fps;
	if (current_video_frame != last_video_frame) {
	  char full_name1[256],full_name2[256];
	  FILE *f,*f2;
	  char buffer[1024];
	  int lus,n;
#ifdef SDL
	  char *extension = "png";
#else
	  char *extension = (display_cfg.screenshot_png ? "png" : "pcx");
#endif

	  last_video_frame = current_video_frame;
	  snprintf(full_name2,256,"%s%s_%06d.%s",dir_cfg.screen_dir, current_game->main_name,cpu_frame_count,extension);
	  n = 1;
	  do {
	    snprintf(full_name1,256,"%s%s_%06d.%s",dir_cfg.screen_dir, current_game->main_name,cpu_frame_count-(n++),extension);
	    f = fopen(full_name1,"rb");
	  } while (!f && n < 15);
	  if (f) {
	    f2 = fopen(full_name2,"wb");
	    do {
	      lus = fread(buffer,1,1024,f);
	      fwrite(buffer,1,lus,f2);
	    } while (lus == 1024);
	    fclose(f);
	    fclose(f2);
	    fprintf(stderr,"compensated\n");
	  } else {
	    fprintf(stderr,"*** too bad !!! %s ***\n",full_name1);
	    exit(1);
	  }
	}
      }
#ifdef SDL
      else {
	SDL_framerateDelay(&fpsm);
	// printf("2nd frame drop\n");
      }
#endif


#ifndef SDL
      update_leds();
#endif

      update_rjoy_list();

      if (req_fwd) { // Fwd n frames
	  req_fwd--;
	  if (!req_fwd) {
	      // if pause is set, then update_inputs returns immediately, so
	      // call it before that !
	      update_inputs();
	      raine_cfg.req_pause_game = 1;
	  }
      }
      update_inputs();

#ifdef RDTSC_PROFILE
      if(raine_cfg.show_fps_mode>2){
	 ProfileStop(PRO_FRAME);
	 UpdateProfile();
      }
#endif

#if defined(SDL) || defined(RAINE_DEBUG)
      if (goto_debuger)
	quit_loop = 1;
#endif
   } // while...

   // auto-save

   if (raine_cfg.auto_save & FLAG_AUTO_SAVE)
   {
      sprintf(str,"%s.sva",current_game->main_name);
      do_save_state(str);
   }

   stop_demo();

   print_debug("run_game_emulation(): Closing down...\n");

#ifndef SDL
#ifdef RAINE_WIN32
   remove_mouse();
#else
   if(GameMouse){
   print_debug("Free mouse...\n");
   remove_mouse();
   }
#endif
#endif

   #ifdef TRIPLE_BUFFER
   print_debug("Free triple buffer...\n");
   reset_triple_buffer();
#endif

#ifndef SDL
  // keep it for later
   DestroyScreenBitmap();
#endif

   if (!raine_cfg.req_pause_game) {
       if (is_neocd())
	   sa_pause_sound();
       else
	   saDestroySound(0);
   }

#ifndef SDL
   clear_keybuf();

   remove_keyboard();
#endif

   print_debug("Free cpu emulation...\n");
   stop_cpu_main();

   print_debug("Free ingame timer...\n");
   stop_ingame_timer();

   print_debug("run_game_emulation(): Completed.\n");

   return quit_loop - 1;
}

#ifndef NO020
extern int MC68020; // newcpu.c
#endif

static void (*reset_function)();

void set_reset_function(void (*my_func)()) {
  reset_function = my_func;
}

void cpu_slow_down(void)
{
   if(cpu_fps<16){
      cpu_fps++;
      print_ingame(300,gettext("cpusldn:Running CPU Every %01d Frames"),cpu_fps);
   }
}

void cpu_speed_up(void)
{
   if(cpu_fps>1){
      cpu_fps--;
      if(cpu_fps==1)
	 print_ingame(120,gettext("Running CPU All Frames"));
      else
	 print_ingame(120,gettext("Running CPU Every %01d Frames"),cpu_fps);
   }
}

void reset_game_hardware(void)
{
   print_debug("reset_game_hardware(): Start\n");

   hs_close(); // in case...

   sa_pause_sound();
   saStopSoundEmulators();

   cpu_fps = 1;
   reset_timers(); // this must absolutely be called BEFORE init_sound_emulators

   clear_ingame_message_list();

   // Must be restarted here in case we are called from a game hardware
   // if(GameSound && RaineSoundCard){
     init_sound_emulators();
     sa_unpause_sound();
   // }

   start_cpu_main();

   restore_ingame_timer(0);

#if HAVE_68000
   if(StarScreamEngine>=1){
      cpu_reset(CPU_68K_0);
      print_ingame(120,gettext("CPU M68000#0 Reset"));
   }
   if(StarScreamEngine>=2){
      cpu_reset(CPU_68K_1);
      print_ingame(120,gettext("CPU M68000#1 Reset"));
   }
#endif

#ifndef NO020
   if(MC68020){
      cpu_reset(CPU_M68020_0);
      print_ingame(120,gettext("CPU M68020#0 Reset"));
   }
#endif

#if HAVE_Z80
   if(MZ80Engine>=1 && mz80GetBase(0)){
      cpu_reset(CPU_Z80_0);
      print_ingame(120,gettext("CPU Z80#0 Reset"));
   }
   if(MZ80Engine>=2){
      cpu_reset(CPU_Z80_1);
      print_ingame(120,gettext("CPU Z80#1 Reset"));
   }
   if(MZ80Engine>=3){
      cpu_reset(CPU_Z80_2);
      print_ingame(120,gettext("CPU Z80#2 Reset"));
   }
   if(MZ80Engine>=4){
      cpu_reset(CPU_Z80_3);
      print_ingame(120,gettext("CPU Z80#3 Reset"));
   }
#endif

#ifdef HAVE_6502
   if(M6502Engine>=1){
      m6502SetContext(&M6502_context[0]);
      m6502reset();
      m6502GetContext(&M6502_context[0]);

      print_ingame(120,gettext("CPU M6502#0 Reset"));
   }
   if(M6502Engine>=2){
      m6502SetContext(&M6502_context[1]);
      m6502reset();
      m6502GetContext(&M6502_context[1]);

      print_ingame(120,gettext("CPU M6502#1 Reset"));
   }
   if(M6502Engine>=3){
      m6502SetContext(&M6502_context[2]);
      m6502reset();
      m6502GetContext(&M6502_context[2]);

      print_ingame(120,gettext("CPU M6502#2 Reset"));
   }
#endif

   stop_cpu_main();

#ifndef SDL
   init_leds();
#endif

   if (reset_function) reset_function();

   if (current_game) {
     hs_open();
     hs_init();

     hist_open("history.dat",current_game->main_name);
     if (!history)
	 hist_open("history.dat",parent_name());
     hist_open("command.dat",current_game->main_name);
   }

   print_debug("reset_game_hardware(): OK\n");
}
