/******************************************************************************/
/*									      */
/*	INGAME (screen message list, rdtsc profile, timer)       */
/*									      */
/******************************************************************************/

#include <stdarg.h>

#include "raine.h"
#include "sasound.h"
#include "ingame.h"
#include "profile.h"
#include "palette.h"
#include "games.h"
#include "newspr.h"
#include "emumain.h"
#include "control.h"
#include "tilemod.h"
#include "arpro.h"
#include "demos.h"
#include "blit.h"
#include "config.h"
#ifdef HAS_CONSOLE
#include "sdl/console/scripts.h"
#endif
#include "sdl/opengl.h"
#include "video/str_opaque.h"

char fps_buff[32];		// fps() message string

/**[Message List Stuff]*************************************/

#define MSG_LIST_SIZE	10	// maximum messages onscreen

typedef struct MESSAGE
{
   INT32  messagetime;		// time before message expires
   char message[256];		// message string
} MESSAGE;

static struct MESSAGE MsgList[MSG_LIST_SIZE];

static int mbase;		// Which message is top of the list

// BlitScreen():
// Entry to screen blitting, takes care of pause mode, eagle mode

void BlitScreen(void)
{
  if(!raine_cfg.req_pause_game){
	 DrawNormal();
	 return;
  }

  DrawPaused();
}

// print_ingame():
// Add Message to Ingame Message List, using a printf() style format string.

void print_ingame(int showtime, const char *format, ...)
{
    if (silent_hud) return;
   va_list ap;
   va_start(ap,format);
   vsprintf(MsgList[mbase].message,format,ap);
   va_end(ap);

   MsgList[mbase].messagetime = showtime;

   mbase++;
   if(mbase>=MSG_LIST_SIZE) mbase=0;
}

// clear_ingame_message_list():
// Clear the ingame message list

void clear_ingame_message_list(void)
{
   int ta;

   mbase = 0;
   for(ta = 0; ta < MSG_LIST_SIZE; ta ++){
      MsgList[ta].messagetime = 0;
      sprintf(MsgList[ta].message," ");
   }
}

#ifndef round
#define     round(a)    (int)(((a)<0.0)?(a)-.5:(a)+.5)
#endif

void overlay_ingame_interface(int ogl)
{
   int ta,tb;
   int xoff2,yoff2,destx,desty,xxx,yyy;

   get_screen_coordinates(&xoff2,&yoff2,&destx,&desty,&xxx,&yyy);
   /*

   print ingame message list

   */

   update_arpro_cheats();
#ifdef HAS_CONSOLE
   update_scripts();
#endif

   if (!silent_hud)
       for(tb=0;tb<MSG_LIST_SIZE;tb++){

	   ta=tb+mbase;

	   if(ta>=MSG_LIST_SIZE)
	       ta-=MSG_LIST_SIZE;

	   if(MsgList[ta].messagetime>0){

	       MsgList[ta].messagetime -= (INT32) skip_frame_count;

#ifndef RAINE_DOS
	       if (ogl)
		   opengl_text(MsgList[ta].message,0,(((MSG_LIST_SIZE-1)-tb)));
	       else
#endif
		   textout_fast(MsgList[ta].message,xoff2,(yoff2+yyy-8)-(((MSG_LIST_SIZE-1)-tb)<<3),get_white_pen());

	   }

       }

   /*

   print speed profile (fps)

   */

   switch(raine_cfg.show_fps_mode){
   case 0x00:				// Show nothing
   break;
   case 0x01:				// Show Accurate FPS (changes rapidly)
      ta = read_ingame_timer();
      if((UINT32)ta >= timer_next_update){					// we have done 60 frames
	  if (display_cfg.limit_speed)
	      sprintf(fps_buff,"%02d/%g",render_frame_count-render_start_count,fps);  // make message string
	  else
	      sprintf(fps_buff,"%02d",render_frame_count-render_start_count);
	 // printf("%s timer %d start_count %d\n",fps_buff,ta,render_start_count);
	 render_start_count = render_frame_count;			// render count at start
	 timer_next_update = ta + fps;					// set time of next update
      }
#ifndef RAINE_DOS
      if (ogl)
	  opengl_text(fps_buff,-strlen(fps_buff),-1);
      else
#endif
	  textout_fast(fps_buff,xoff2+xxx-(strlen(fps_buff)*6),yoff2,get_white_pen());
   break;
   case 0x02:				// Show Average FPS (takes a while to adapt to changes)
     ta = read_ingame_timer();
     if((UINT32)ta >= timer_next_update){					// we have done 60 frames
	  if (display_cfg.limit_speed)
	      sprintf(fps_buff,"Avg:%02d/%g",round(((render_frame_count-render_start_count)*1.0/(ta-timer_start_count))*fps),fps);
	  else
	      sprintf(fps_buff,"Avg:%02d",round(((render_frame_count-render_start_count)*1.0/(ta-timer_start_count))*fps));
       timer_next_update = ta + fps;					// set time of next update
     }
#ifndef RAINE_DOS
      if (ogl)
	  opengl_text(fps_buff,-strlen(fps_buff),-1);
      else
#endif
	  textout_fast(fps_buff,xoff2+xxx-(strlen(fps_buff)*6),yoff2,get_white_pen());
     break;
   case 0x03:				// Show Profile results (percent)
      for(ta=0;ta<PRO_COUNT;ta++){
      sprintf(fps_buff,"%s: %2d%%",profile_results[ta].name, profile_results[ta].percent);
#ifndef RAINE_DOS
      if (ogl)
	  opengl_text(fps_buff,-10,-1-ta);
      else
#endif
	  textout_fast(fps_buff,xoff2+xxx-(10*6),yoff2+(ta*8),get_white_pen());
      }
   break;
   case 0x04:				// Show Profile results (cycles)
      for(ta=0;ta<PRO_COUNT;ta++){
      sprintf(fps_buff,"%s: %6x",profile_results[ta].name, profile_results[ta].cycles);
#ifndef RAINE_DOS
      if (ogl)
	  opengl_text(fps_buff,-13,-1-ta);
      else
#endif
	  textout_fast(fps_buff,xoff2+xxx-(13*6),yoff2+(ta*8),get_white_pen());
      }
   break;
   default:				// Show nothing
   break;
   }

   /*

   print <paused>

   */

   if((raine_cfg.req_pause_game) && (!(pause_time & 0x20))) {

#ifndef RAINE_DOS
      if (ogl)
	  opengl_text("<Paused>",-1000,-1000);
      else
#endif
	  textout_fast("<Paused>",xoff2+((xxx-(6*8))>>1),yoff2+((yyy-8)>>1),get_white_pen());
   }

}


/******************************************************************************/


/******************************************************************************/
/*									      */
/*			  VIDEO LAYER TOGGLE CONTROLS			      */
/*									      */
/******************************************************************************/


struct LAYER_INFO layer_info_list[MAX_LAYER_INFO];

int layer_info_count;

void reset_layer_switches(void)
{
   layer_info_count = 0;
}

#ifndef SDL
void check_layer_switches(void)
{
   int ta;

   for(ta=0; ta<layer_info_count; ta++){

      if( key[layer_info_list[ta].keycode] ){

	 if( ! layer_info_list[ta].flip ){

	    layer_info_list[ta].flip = 1;
	    layer_info_list[ta].enabled ^= 1;
	    print_ingame(60, "%s: %01d", layer_info_list[ta].name, layer_info_list[ta].enabled);

	 }

      }
      else{

	 layer_info_list[ta].flip = 0;

      }

   }
}
#endif

int add_layer_info(char *name)
{
   int ta;

   if(layer_info_count < MAX_LAYER_INFO){

      ta = layer_info_count;

      layer_info_list[ta].name	  = name;
#ifndef SDL
      layer_info_list[ta].keycode = key_data[ta];
#endif
      layer_info_list[ta].enabled = 1;
      layer_info_list[ta].flip	  = 0;
      layer_info_count++;

      return ta;

   }
   else{
      print_debug("add_layer_info(): error -- too many layers\n");
      return MAX_LAYER_INFO - 1;

   }
}

int check_layer_enabled(int layer)
{
  if(layer<layer_info_count){

      return  layer_info_list[layer].enabled;


   }
   else{

      print_debug("check_layer_enabled(): error - incorrectly initialized\n");

      return 1;

   }
}

