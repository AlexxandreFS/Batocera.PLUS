/* Demos : based on savegame.c. A demo is just a savegame plus all the
 * inputs the game receives... */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include "cpumain.h"
#include "files.h"
#include "sasound.h"
#ifndef SDL
#include "gui.h"
#include "rgui.h"
#else
#include "dialogs/fsel.h"
#endif

#include "raine.h"
#include "savegame.h"

#include "config.h"
#include "memory.h"

#include "games.h"		// Games List

#include "ingame.h"
#include "control.h"
#include "profile.h" // timer, cpu_frame_count
#include "blit.h"

int recording_demo = 0, reading_demo = 0;

static gzFile fdemo;
static int nb; // nb of inputs to watch
static UINT32 current_frame; // Current frame read from the demo file
#define MAX_OFS 32
#define MOUSE_ID 50
static UINT32 offsets[MAX_OFS];
static UINT16 contents[MAX_OFS];
static int oldmx, oldmy,newmx,newmy,oldb,newb; // mouse vars

static void demo_mouse_mickeys(int *mx,int *my)
{
  *mx = oldmx;
  *my = oldmy;
}

static void do_save_demo(char *str) {
   char *disp_str;

   if(RAMSize){
     disp_str = strstr(str,"demos");
     if (!disp_str) disp_str = str;
     if (!(fdemo=gzopen(str,"wb9"))){
      print_ingame(120,gettext("Unable to save: %s"),disp_str);
      return;
     }

     NewSave(fdemo);
     iputl(0,fdemo); // Size parameter for END

     print_ingame(120,gettext("Recording demo to: %s"),disp_str);
     start_cpu_main();
   }
   else{
      print_ingame(120,gettext("Game does not support Saving."));
   }

   print_debug("END: GameSaveDemo()\n");
}

static inline UINT8 read_input(UINT32 offset)
{
  if (offset < 0x100)
    return input_buffer[offset];
  return RAM[offset];
}

static int cmp_offs(const void *c1, const void *c2)
{
  return *((UINT32 *)c1) - *((UINT32 *)c2);
}

static void build_offsets_table()
{
// builds a table of the offsets of the controls. Easier to handle here.
// The table must be sorted.
  const INPUT_INFO *inp=current_game->input;
  int n,found;
  nb = 0;

  while (inp->name) {
    found = 0;
    for (n=0; n<nb; n++)
      if (offsets[n] == inp->offset)
	found = 1;
    if (!found) {
      offsets[nb++] = inp->offset;
      if (nb >= MAX_OFS) {
	allegro_message("buffer overflow for the demo.");
	exit(1);
      }
    }
    inp++;
  }
  qsort(offsets,nb,4,cmp_offs);
  // Now init the contents array...
  for (n=0; n<nb; n++)
    contents[n] = 0x100; // impossible value
}

void GameSaveDemo(void)
{
  char str[FILENAME_MAX];

   print_debug("BEGIN: GameSaveDemo()\n");

   snprintf(str,FILENAME_MAX,"%s" SLASH "demos" SLASH "%s" SLASH,dir_cfg.exe_path,current_game->main_name);
   mkdir_rwx(str);
   sa_pause_sound();
   stop_cpu_main();
#ifndef SDL
   setup_gui();
   if (raine_file_select("Save demo",str,NULL)) {
     recording_demo = 1;
     GetMouseMickeys = &demo_mouse_mickeys; // obliged to do this even for
     // recording...
     build_offsets_table();
     do_save_demo(str);
   }
   release_gui();
#else
   char path[FILENAME_MAX];
   strcpy(path,str);
   *str = 0;
   fsel_save(path,NULL,str,"Save demo");
   if (*str) {
     recording_demo = 1;
     GetMouseMickeys = &demo_mouse_mickeys; // obliged to do this even for
     // recording...
     build_offsets_table();
     do_save_demo(str);
   }
#endif
   sa_unpause_sound();
   reset_ingame_timer();
}

void save_demo_inputs()
{
// See if inputs have changed, and save as little as possible
// Should be called after inputs have been processed, for each frame
// The mouse is handled with a hack... Oh well, it works !
  int n;
  int first = -1,last=-1; // init last is useless, but it makes a warning...
  int mx,my;
  int mouse_flag = 0;

  for (n=0; n<nb; n++)
    if (contents[n] != read_input(offsets[n])) {
      first = n;
      break;
    }
  if (GameMouse)
    get_mouse_mickeys(&mx,&my);
  if (first >= 0) {
    for (n=nb-1; n>=0; n--)
      if (contents[n] != read_input(offsets[n])) {
        last = n;
        break;
      }

    if (mx != oldmx || my != oldmy || mouse_b != oldb)
      mouse_flag = 0x80;
    iputl(cpu_frame_count,fdemo);
    iputw(first | (last << 8) | mouse_flag,fdemo);
    for (n=first; n<=last; n++)
      contents[n] = read_input(offsets[n]);
    gzwrite(fdemo,&contents[first],(last-first+1)*2);
  } else if (GameMouse && (mx != oldmx || my != oldmy || mouse_b != oldb)) {
    mouse_flag = 1;
    iputl(cpu_frame_count,fdemo);
    iputw(MOUSE_ID,fdemo);
  }

  if (mouse_flag) {
    oldmx = mx; oldmy = my; oldb = mouse_b;
    iputw(oldmx,fdemo);
    iputw(oldmy,fdemo);
    iputw(oldb,fdemo);
  }
}

extern void end_recording();

void stop_demo()
{
  if (reading_demo || recording_demo) {
    gzclose(fdemo);
    fdemo = NULL;
    if (reading_demo) {
      reading_demo = 0;
      ReClipScreen();
      raine_cfg.req_pause_game = 1;
    }
    recording_demo = 0;
    MouseB = ((int*)&mouse_b);
    GetMouseMickeys = &get_mouse_mickeys;
  }
  if (recording_video) {
    recording_video = 0;
    if (recording)
	end_recording();
  }
}

/******************************************************************************/

INLINE static void write_input(UINT32 offset,UINT8 data)
{
  if (offset < 0x100)
    input_buffer[offset] = data;
  else
    RAM[offset] = data;
}

void write_demo_inputs()
{
// The counter part of save_demo_inputs
  static int  first,last;  // first and last offsets concerned for the frame.
  int n,mouse_flag = 0;
    if (raine_cfg.req_pause_game)
	return;

  if (current_frame < cpu_frame_count) {
    // Need to read from the file
    if (gzeof(fdemo)) {
      stop_demo();
      return;
    } else {
      int new_frame = igetl(fdemo);
      if (!current_frame)
	restore_ingame_timer(new_frame);
      current_frame = new_frame;
      n = igetw(fdemo);
      first = n & 0x7f;
      last = n>>8;
      mouse_flag = ((n & 0x80) || (n == MOUSE_ID));
      if (n != MOUSE_ID)
        gzread(fdemo,&contents[first],(last-first+1)*2);
      if (mouse_flag) {
	newmx = igetw(fdemo);
	newmy = igetw(fdemo);
	newb = igetw(fdemo);
      }
    }
  }

  if (current_frame == cpu_frame_count) {
    for (n=first; n<=last; n++)
       write_input(offsets[n],contents[n]);
    if (GameMouse) {
      oldmx = newmx; oldmy = newmy; oldb = newb;
    }
  }
}

static void do_load_demo(char *str) {
  int ta;
  char *disp_str;

   if(RAMSize){
   disp_str = strstr(str,"demos");
   if (!disp_str) disp_str = str;
   if(!(fdemo=gzopen(str,"rb"))){
        print_ingame(120,gettext("Unable to load: %s"), disp_str);
        return;
   }

   ta = mgetl(fdemo);

   switch(ta){
      case SAVE_FILE_TYPE_0:
	print_ingame(120,gettext("%s is too ancient!"), disp_str);
         gzclose(fdemo);
         return;
      break;
      case SAVE_FILE_TYPE_1:
      case SAVE_FILE_TYPE_2:
         NewLoad(fdemo);
      break;
      default:
	print_ingame(120,gettext("%s is not recognised"), disp_str);
         gzclose(fdemo);
         return;
      break;
   }

   print_ingame(120,gettext("Playing from: %s"), disp_str);

   RefreshBuffers=1;

   MouseB = &oldb;
   GetMouseMickeys = &demo_mouse_mickeys;

   start_cpu_main();
   current_frame = 0; // Need reading from file
   reading_demo = 1;
   oldmx = oldmy = oldb = 0;
   build_offsets_table();
   ReClipScreen();
   write_demo_inputs(); // when recording the inputs are written immediately
   // so to keep in sync we must read them from here !

   }
   else{
      print_ingame(120,gettext("Game does not support Loading."));
   }

   print_debug("END: GameLoadDemo()\n");
}

void GameLoadDemo(void)
{
  char str[FILENAME_MAX];

   print_debug("BEGIN: GameLoadDemo()\n");

   snprintf(str,FILENAME_MAX,"%s" SLASH "demos" SLASH "%s" SLASH,dir_cfg.exe_path,current_game->main_name);
   sa_pause_sound();
   stop_cpu_main();
#ifndef SDL
   setup_gui();
   if (raine_file_select("Load demo",str,NULL))
     do_load_demo(str);
   release_gui();
#else
   char path[FILENAME_MAX];
   strcpy(path,str);
   *str = 0;
   fsel(path,NULL,str,"Load demo");
   if (*str)
     do_load_demo(str);
#endif
   sa_unpause_sound();
   reset_ingame_timer();
}


