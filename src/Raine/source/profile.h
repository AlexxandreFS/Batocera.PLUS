
#ifdef __cplusplus
extern "C" {
#endif
#include "deftypes.h"

// RDTSC Profiler
// --------------

// fps : frames per second. 60 normally. In a "good" implementation it should
// be declared read-only (by hiding the variable). But this is not c++, and
// I need to access this variable very quickly for the timers (see timer.c)
// If you want to change this variable, do it in the load_game function only !
extern float fps,default_fps;

void switch_fps_mode(void);
void init_fps(void);

extern UINT32 timer_next_update, // timer_frame_count at next fps() update
  timer_start_count,	// timer_frame_count at fps() start
  render_start_count,	// render_frame_count at fps() start

  cpu_frame_count,		// number of frames of cpu emulation
  render_frame_count,	// number of frames of video emulation
  skip_frame_count;		// number of frames since last video emulation

extern UINT32 cycles_per_second; // cpu cycles per second

void start_ingame_timer(void);
void stop_ingame_timer(void);
double timer_get_time();
#ifdef RDTSC_PROFILE


extern UINT32 cycles_per_frame;			// cpu cycles per frame, or 0 if not computed

UINT32 read_ingame_cycles(UINT64 *last_rdtsc_counter);
void reset_rdtsc_timer(UINT64 *last_rdtsc_counter);
#endif
UINT32 read_ingame_timer(void);

void reset_ingame_timer(void);
extern int use_rdtsc; // Not sure it will be usefull outside allegro...

typedef struct PROFILE_RESULTS
{
   char *name;
   UINT32 percent;
   UINT32 cycles;
} PROFILE_RESULTS;

enum profile_section
{
   PRO_FRAME = 0,
   PRO_CPU,
   PRO_SOUND,
   PRO_RENDER,
   PRO_BLIT,
   PRO_PAL,
   PRO_FREE,
   PRO_COUNT,			// End marker and list size
};

void ProfileStart(UINT8 mode);
void ProfileStop(UINT8 mode);
void UpdateProfile(void);
extern void restore_ingame_timer(UINT32 timer);

extern struct PROFILE_RESULTS profile_results[PRO_COUNT];

#ifdef __cplusplus
}
#endif
