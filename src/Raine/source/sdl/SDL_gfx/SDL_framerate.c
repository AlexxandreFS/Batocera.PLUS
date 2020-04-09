
/*

 SDL_framerate: framerate manager

 LGPL (c) A. Schiffler
 comes from : SDL_gfx

 Actually the code must be extracted from SDL_gfx to be able to precisely
 compensate when we drop frames (easy to do when rendering 8bpp in 16bpp !)

 */

#include "SDL_framerate.h"

extern unsigned int pc_timer,cpu_frame_count;

/*
   Initialize the framerate manager
*/

void SDL_initFramerate(FPSmanager * manager)
{
    /*
     * Store some sane values
     */
    manager->framecount = 0;
    manager->rateticks = (1000.0 / (float) FPS_DEFAULT);
    manager->lastticks = SDL_GetTicks();
}

/*
   Set the framerate in Hz
*/

int SDL_setFramerate(FPSmanager * manager, float frate)
{
    if ((frate >= FPS_LOWER_LIMIT) && (frate <= FPS_UPPER_LIMIT)) {
	manager->rateticks = (1000.0 / frate);
	if (manager->use_cpu_frame_count) {
	  manager->framecount = cpu_frame_count;
	} else
	  manager->framecount = 0;
	manager->lastticks = SDL_GetTicks() - manager->framecount*manager->rateticks;
	return (0);
    } else {
	return (-1);
    }
}

/*
  Return the current target framerate in Hz
*/

float SDL_getFramerate(FPSmanager * manager)
{
    if (manager == NULL || manager->rateticks < 0.001) {
	return (-1);
    } else {
	return (1000.0/manager->rateticks);
    }
}

/* Get the current framecount, usefull when you don't want to maintain
 * a constant framerate but get framerate stats anyway */
int SDL_get_frame_count(FPSmanager * manager) {
  if (manager->rateticks > 0) {
    if (manager->use_cpu_frame_count) manager->framecount = cpu_frame_count;
    pc_timer = (SDL_GetTicks() - manager->lastticks) / manager->rateticks;
    return pc_timer;
  }
  return 0;
}

/*
  Delay execution to maintain a constant framerate. Calculate fps.
*/

extern Uint32 cpu_frame_count;


void SDL_framerateDelay(FPSmanager * manager)
{
    Uint32 current_ticks;
    Uint32 target_ticks;
    Uint32 the_delay;

    /*
     * Next frame
     */
    if (manager->use_cpu_frame_count) {
      manager->framecount = cpu_frame_count;
    } else {
      manager->framecount++;
    }

    /*
     * Get/calc ticks
     */
    current_ticks = SDL_GetTicks();
    target_ticks = manager->lastticks + (Uint32) ((float) manager->framecount * manager->rateticks);

    if (current_ticks <= target_ticks) {
	the_delay = target_ticks - current_ticks;
	if (the_delay > 1000) {
	  // SDL was initialised AFTER the manager -> reinit
	  manager->lastticks = current_ticks - manager->framecount*manager->rateticks;
	} else {
	  SDL_Delay(the_delay);
	  pc_timer = (SDL_GetTicks() - manager->lastticks)/manager->rateticks;
	  // printf("delay %d timer %d cpu_frame %d manager frame %d\n",the_delay,pc_timer,cpu_frame_count,manager->framecount);
	}
    } else {
#if 1
      pc_timer = (current_ticks - manager->lastticks)/manager->rateticks;
      // printf("reset pc_timer : %d target ticks %d current %d manager frame %d\n",pc_timer,target_ticks,current_ticks,manager->framecount);
#else
      pc_timer = (current_ticks - manager->lastticks)/manager->rateticks;
	  manager->framecount = pc_timer;
	  manager->lastticks = current_ticks - manager->framecount*manager->rateticks;
#endif
/*      manager->framecount = 0;
      manager->lastticks = current_ticks;  */
    }
}
