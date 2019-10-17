#include "raine.h"
#include "profile.h"
#include "ingame.h" // print_ingame
#ifdef RAINE_DEBUG
#include "debug.h"
#endif
#include <SDL.h>
#include <sdl/SDL_gfx/SDL_framerate.h>

float fps = 60.0,default_fps;

/* Profiling in SDL : */
/* They announce RDTSC for v1.3. */
/* But I need it now for RDTSC profiling (the rdtsc timer has 1 million */
/* ticks / second, where the default SDL timer has now 1000 ticks / */
/* second... It's clearly not enough. */

/* In fact this file is necessary only if you want to use SDL alone.
   If you want to use SDL AND Allegro, then just forget about it. */

int use_rdtsc;
UINT32 timer_next_update;	// timer_frame_count at next fps() update
UINT32 timer_start_count;	// timer_frame_count at fps() start
UINT32 render_start_count;	// render_frame_count at fps() start

UINT32 cpu_frame_count;		// number of frames of cpu emulation
UINT32 render_frame_count;	// number of frames of video emulation
UINT32 skip_frame_count;		// number of frames since last video emulation

struct PROFILE_RESULTS profile_results[PRO_COUNT] =
{
   { " Misc", 0, 0 },
   { "  Cpu", 0, 0 },
   { "Sound", 0, 0 },
   { " Draw", 0, 0 },
   { " Blit", 0, 0 },
   { "  Pal", 0, 0 },
   { " Free", 0, 0 },
};

#ifdef RDTSC_PROFILE

#if defined(RAINE_DOS) || defined(RAINE_UNIX) || defined(__MINGW32__)
#define RDTSC_32(dest) ({				    \
   __asm__ __volatile__ (				    \
   " rdtsc "                                                \
   : "=a" (((UINT32 *)dest)[0])                             \
   :							    \
   : "%edx" ); })                                           \

#define RDTSC_64(dest) ({				    \
   __asm__ __volatile__ (				    \
   " rdtsc "                                                \
   : "=a" (((UINT32 *)dest)[0]), "=d" (((UINT32 *)dest)[1]) \
   : ); })						    \

#else

#undef UINT64
#define UINT64 __int64

DEF_INLINE UINT32 read_rdtsc_32(void)
{
	UINT32 time_rdtsc;

	__asm
	{
		push	eax
		push	edx
//		rdtsc
		_emit	0x0f
		_emit	0x31
		mov		time_rdtsc, eax
		pop		edx
		pop		eax
	}

	return time_rdtsc;
}

DEF_INLINE UINT64 read_rdtsc_64(void)
{
   UINT32 time_rdtsc_low,time_rdtsc_high;

   __asm
   {
      push	eax
      push	edx
    //rdtsc
      _emit	0x0f
      _emit	0x31
      mov	time_rdtsc_low, eax
      mov	time_rdtsc_high, edx
      pop	edx
      pop	eax
   }

   return ( (time_rdtsc_high<<32) | (time_rdtsc_low));
}

#define RDTSC_32(dest)		((UINT32 *)dest)[0] = read_rdtsc_32()

#define RDTSC_64(dest)		((UINT64 *)dest)[0] = read_rdtsc_64()

#endif

typedef struct PROFILE
{
   UINT32 start;			// Internal (start time)
   UINT32 stop; 		// Internal (stop time)
   UINT32 cycles;		// Cycle Count
   UINT8 state; 		// 0 - Empty; 1 - started; 2 - stopped
} PROFILE;

static struct PROFILE Profile[PRO_COUNT];

void ProfileStart(UINT8 mode)
{
   UINT32 rdtsc_cycles;

   if(Profile[mode].state!=1){

   RDTSC_32( &rdtsc_cycles );

   Profile[mode].start = rdtsc_cycles;

   Profile[mode].state = 1;

   }
}

void ProfileStop(UINT8 mode)
{
   UINT32 rdtsc_cycles;

   if(Profile[mode].state==1){

   RDTSC_32( &rdtsc_cycles );

   Profile[mode].stop = rdtsc_cycles;

   Profile[mode].cycles += (Profile[mode].stop - Profile[mode].start);

   Profile[mode].state = 2;

   }
}

#define P_UPDATE_RATE	(8)

static int pcount;

/* The computation is now done in UINT64 to avoid any overflow */
void UpdateProfile(void)
{
   if(Profile[0].state==2){

   INT64 total,total2;
   int ta;

   pcount++;

   if(pcount>P_UPDATE_RATE){
       pcount=0;


       for(ta=0;ta<PRO_COUNT;ta++){
	   Profile[ta].cycles = Profile[ta].cycles / P_UPDATE_RATE;
       }


       total2 = total = Profile[0].cycles;

       if(raine_cfg.show_fps_mode==3){

	   for(ta=1;ta<PRO_COUNT;ta++){
	       if(Profile[ta].state==2){
		   profile_results[ta].percent = (Profile[ta].cycles * (UINT64)100)/total;
		   total2 -= (Profile[ta].cycles);
	       }
	       else{
		   profile_results[ta].percent = 0;
	       }
	   }
	   if(total2>0){
	       profile_results[0].percent = (total2 * (UINT64)100)/total;
	   }
	   else{
	       profile_results[0].percent = 0;
	   }

       }
       else{

	   for(ta=1;ta<PRO_COUNT;ta++){
	       if(Profile[ta].state==2){
		   profile_results[ta].cycles = Profile[ta].cycles;
		   total2 -= (Profile[ta].cycles);
	       }
	       else{
		   profile_results[ta].cycles = 0;
	       }
	   }
	   profile_results[0].cycles = total2;

       }


       for(ta=0;ta<PRO_COUNT;ta++){
	   Profile[ta].state=0;
	   Profile[ta].cycles=0;
       }

   }

   }

}

#endif

static void update_fps(int quiet)
{
  if(raine_cfg.show_fps_mode>4) raine_cfg.show_fps_mode=0;
  if((use_rdtsc==0)&&(raine_cfg.show_fps_mode>2)) raine_cfg.show_fps_mode=0;

  switch(raine_cfg.show_fps_mode){
  case 0x00:
    if(quiet) print_ingame(120,gettext("FPS Counter Disabled"));
    return;
    break;
  case 0x01:
    timer_next_update = read_ingame_timer() + fps;	// set time of next update
    render_start_count = render_frame_count;	// render count at start
    sprintf(fps_buff,"\?\?/%g",fps);
    if(quiet) print_ingame(120,gettext("FPS Counter Enabled"));
    return;
    break;
  case 0x02:
    timer_start_count = read_ingame_timer();		// start time
    timer_next_update = timer_start_count + fps;	// set time of next update
    render_start_count = render_frame_count;	// render count at start
    sprintf(fps_buff,"\?\?/%g",fps);
    if(quiet) print_ingame(120,gettext("Average FPS Counter Enabled"));
    return;
    break;
  case 0x03:
    if(quiet) print_ingame(120,gettext("RDTSC Timing Enabled (percentages)"));
    return;
    break;
  case 0x04:
    if(quiet) print_ingame(120,gettext("RDTSC Timing Enabled (cycles)"));
    return;
    break;
  }
}

void switch_fps_mode(void)
{
   raine_cfg.show_fps_mode++;
   update_fps(1);
}

void init_fps(void)
{
   update_fps(0);
}

/******************************************************************************/

volatile UINT32 pc_timer;			// timer, returned by read_ingame_timer()

#ifdef RDTSC_PROFILE

volatile static UINT64 rdtsc_times[6];		// timer, returned by read_ingame_timer()

static UINT64 last_rdtsc_counter;		// rdtsc count from last read_ingame_timer()
UINT32 cycles_per_frame;			// cpu cycles per frame, or 0 if not computed
UINT32 cycles_per_second;		// cpu cycles per second
static UINT32 remained_cycles;			// left over cycles from last read_ingame_timer()

#endif

#ifdef RDTSC_PROFILE

static UINT32 timer_setup_rdtsc(UINT32 timer_interval, void *param)
{
  if(pc_timer<6){
    RDTSC_64( &rdtsc_times[pc_timer] );
    pc_timer++;
  }
  return timer_interval;
}

/*  static void ingame_timer_proc_rdtsc(void) */
/*  { */
/*     saUpdateSound(0);		// HIRO-SHI: check stream buffer */
/*  } */

/*  END_OF_FUNCTION(ingame_timer_proc_rdtsc); */

#endif

static UINT32 ingame_timer_proc_nordtsc(UINT32 timer_interval, void *param)
{
  // saUpdateSound(0);		// HIRO-SHI: check stream buffer
   (*((UINT32 *)param))++;
   return timer_interval;
}

static SDL_TimerID id;

void reset_ingame_timer(void)
{
#ifdef RDTSC_PROFILE
  if (use_rdtsc && !cycles_per_frame)
    return;
  if(use_rdtsc){
    RDTSC_64( &last_rdtsc_counter );
    remained_cycles = 0;
  }
#endif
  pc_timer = cpu_frame_count;
  SDL_initFramerate(&fpsm);
  SDL_setFramerate(&fpsm,fps);
  init_fps();
}

void start_ingame_timer(void)
{
#ifdef RDTSC_PROFILE
   if(!use_rdtsc){
#endif
     // Notice that the minimum granularity of the timer is now 10ms
     // So this function has very little chances to be called 60 times
     // / second. It's just something like "hope for the best" !

     id = SDL_AddTimer(1000/60,ingame_timer_proc_nordtsc,(void*)&pc_timer);

#ifdef RDTSC_PROFILE
   }
   else{

      if(!cycles_per_frame){		// Need to work out cycles/frame, this takes about 1/2 second

      pc_timer = 0;

      memset((void*)rdtsc_times,0,sizeof(rdtsc_times));
      id = SDL_AddTimer(100,timer_setup_rdtsc,(void*)rdtsc_times);

      while (!rdtsc_times[5]);

      SDL_RemoveTimer(id);
      id = 0;

      cycles_per_second = (UINT32) ((rdtsc_times[5] - rdtsc_times[0])*2);

      cycles_per_frame = cycles_per_second / fps;

#ifdef RAINE_DEBUG
      print_debug("Approx CPU Speed: %d MHz\n", cycles_per_second/1000000);
      print_debug("RDTSC Cycles/frame: %d/%d = %d\n", cycles_per_second, fps, cycles_per_frame);
#endif
      }
   }
#endif
   reset_ingame_timer();
}

void stop_ingame_timer(void)
{
#ifdef RDTSC_PROFILE
/*     if(use_rdtsc) */
/*        remove_int(ingame_timer_proc_rdtsc); */
/*     else */
#endif
  if (id)
    SDL_RemoveTimer(id);
}

double timer_get_time() {
#ifndef RAINE_DOS
  return SDL_GetTicks() / 1000.0;
#elif defined(RDTSC_PROFILE)
  RDTSC_64( &rdtsc_times[0] );
  return (rdtsc_times[0]/((double)cycles_per_second));
#else
  return 0; // !!!
#endif
}

#ifdef RDTSC_PROFILE
UINT32 read_ingame_cycles(UINT64 *last_rdtsc_counter) {
  UINT64 rdtsc_counter;
  UINT32 dif=0;
  if(use_rdtsc){
    RDTSC_64( &rdtsc_counter );

    dif = (rdtsc_counter - *last_rdtsc_counter);
    *last_rdtsc_counter = rdtsc_counter;
  }
  return dif;
}
#endif

#ifndef SDL
UINT32 read_ingame_timer(void)
{
#ifdef RDTSC_PROFILE
   if(use_rdtsc){

      UINT64 rdtsc_counter;
      UINT64 dif;

      RDTSC_64( &rdtsc_counter );

      dif = (rdtsc_counter - last_rdtsc_counter) + remained_cycles;

      if(dif >= cycles_per_frame){
	 last_rdtsc_counter = rdtsc_counter;
#ifdef RAINE_DOS
       /* In windows and linux, pc_timer is now only updated in
        * SDL_framerate.c, no more update based on the rdtsc to work
        * around variable cpu frequency ! */
	 while(dif >= cycles_per_frame){
	    dif -= cycles_per_frame;
	    pc_timer++;
	 }
	 remained_cycles = dif;
#endif
      }

   }
#endif
   return pc_timer;
}
#else
#ifdef read_ingame_timer
#undef read_ingame_timer
#endif
UINT32 read_ingame_timer() {
  return SDL_get_frame_count(&fpsm);
}
#endif

#ifdef RDTSC_PROFILE
void reset_rdtsc_timer(UINT64 *last_rdtsc_counter) {
   if(use_rdtsc){
      RDTSC_64( last_rdtsc_counter );
   }
}
#endif

// usefull after using read_ingame_timer during a pause
void restore_ingame_timer(UINT32 timer) {
  pc_timer = timer;
  fpsm.framecount = timer;
  cpu_frame_count = timer; // when reading a demo !
}


