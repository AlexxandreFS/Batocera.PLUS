#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "gui.h"
#include "sound.h"
#include "palette.h"
#include "ingame.h"
#include "sasound.h"
#include "streams.h"
#include "blit.h"
#include "3812intf.h"

extern char soundname[96];
#define SND_RATE_LIST		6
#if defined(ALLEGRO_SOUND) || defined(SEAL)
#define MAX_VOL_BTN  9
#define RECORD_BTN 10
#else
#define RECORD_BTN 9
#endif
// #define STEREO_BTN RECORD_BTN+2
#define MONITOR_BTN RECORD_BTN+2 /* STEREO_BTN+1 */
#define ENH_BTN MONITOR_BTN+1

DIALOG sound_setup_dialog[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)             (bg)                 (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    0,    216,  190,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Sound Setup"},
   { d_raine_list_proc,  8,    28,   180,  60,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    soundcardlist_getter},
   { x_raine_button_proc,8,    166,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Okay"},
   { x_raine_button_proc,64,   166,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Cancel"},
   { x_text_proc,        8,    16,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Choose Sound Driver:"},
   { x_text_proc,        8,    94,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Sample Rate:"},
   { x_raine_radio_proc, 8,    104,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "11025"},
   { x_raine_radio_proc, 8,    114,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "22050"},
   { x_raine_radio_proc, 8,    124,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "44100"},
#ifdef ALLEGRO_SOUND
   { d_raine_check_proc, 100,    94,  200,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Max Mixer Volume"},
#elif defined(SEAL)
   { d_raine_check_proc, 100,    94,  200,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Emulated YM3812"},
#endif
   { d_raine_check_proc, 100,    104,  200,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Record to wav"},
   { x_text_proc,        100,    124,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Recording options:"},
   //   { d_raine_check_proc, 100,    134,  200,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Stereo"},
   { d_raine_check_proc, 100,    144,  200,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Monitor"},
   { d_raine_check_proc, 8,    144,  200,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Enh. Stereo"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};


char *soundcardlist_getter(int index, int *list_size)
{
   if(index==-1){
      *list_size = RaineSoundCardTotal;
      return NULL;
   }
   else{
      if((index >= 0)&&(index<RaineSoundCardTotal))
         return sound_card_name(index);
      else
         return NULL;
   }
}

#ifdef ALLEGRO_SOUND
extern int max_mixer_volume; // allegro specific : disable volume correction
// and make it maximum.
#endif

void get_sound_variables(void)
{
      // Initialize Sample Rate switch
      // -----------------------------

      sound_setup_dialog[SND_RATE_LIST].flags=0;
      sound_setup_dialog[SND_RATE_LIST+1].flags=0;
      sound_setup_dialog[SND_RATE_LIST+2].flags=0;

#ifdef ALLEGRO_SOUND
      sound_setup_dialog[MAX_VOL_BTN].flags=(max_mixer_volume ? D_SELECTED : 0);
#endif
#ifdef SEAL
      sound_setup_dialog[MAX_VOL_BTN].flags=(use_emulated_ym3812 ? D_SELECTED : 0);
#endif

      sound_setup_dialog[RECORD_BTN].flags=(recording ? D_SELECTED : 0);
/*       sound_setup_dialog[STEREO_BTN].flags=(mixing_stereo ? D_SELECTED : 0); */
      sound_setup_dialog[MONITOR_BTN].flags=(monitoring ? D_SELECTED : 0);
      sound_setup_dialog[ENH_BTN].flags=(enh_stereo ? D_SELECTED : 0);
      switch(audio_sample_rate){
          case 11025:
             sound_setup_dialog[SND_RATE_LIST+0].flags=D_SELECTED;
          break;
          case 44100:
             sound_setup_dialog[SND_RATE_LIST+2].flags=D_SELECTED;
          break;
          case 22050:
          default:
             audio_sample_rate=22050;
             sound_setup_dialog[SND_RATE_LIST+1].flags=D_SELECTED;
          break;
      }

      // Initialize Soundcard switch
      // ---------------------------

      sound_setup_dialog[1].d1=RaineSoundCard;
}

extern void end_recording();

void set_sound_variables(UINT8 update)
{
  int old_soundcard = RaineSoundCard,
    old_sample_rate = audio_sample_rate;

   if(update){
     RaineSoundCard=sound_setup_dialog[1].d1;

     if((sound_setup_dialog[SND_RATE_LIST].flags)&D_SELECTED)   audio_sample_rate=11025;
     if((sound_setup_dialog[SND_RATE_LIST+1].flags)&D_SELECTED) audio_sample_rate=22050;
     if((sound_setup_dialog[SND_RATE_LIST+2].flags)&D_SELECTED) audio_sample_rate=44100;

#ifdef ALLEGRO_SOUND
     max_mixer_volume = sound_setup_dialog[MAX_VOL_BTN].flags & D_SELECTED;
#elif defined(SEAL)
     use_emulated_ym3812 = sound_setup_dialog[MAX_VOL_BTN].flags & D_SELECTED;
#endif
     if (recording)
       end_recording();
     if (recording_video) {
       end_recording();
       recording_video = 0;
       printf("stopping video\n");
     }
     /*    mixing_stereo = sound_setup_dialog[STEREO_BTN].flags & D_SELECTED; */
     recording = sound_setup_dialog[RECORD_BTN].flags & D_SELECTED;
     monitoring = sound_setup_dialog[MONITOR_BTN].flags & D_SELECTED;
     enh_stereo = sound_setup_dialog[ENH_BTN].flags & D_SELECTED;
     if (old_soundcard != RaineSoundCard || old_sample_rate != audio_sample_rate)
       change_sample_rate = 1;
   }

   sprintf(soundname, "Sound: %s; %02dkHz",sound_card_name(RaineSoundCard),audio_sample_rate/1000);
}

// sound_setup_proc():
// Does sound setup options dialog

int sound_setup_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      get_sound_variables();

      ret=raine_do_dialog(sound_setup_dialog,-1);
      if((ret!=3)&&(ret!=-1)){
         set_sound_variables(1);
      }

      return D_REDRAW;
   }
   return ret;
}

void *old_draw = NULL;
extern int screen_valid;
extern int SampleVol[MAX_STREAM_CHANNELS];
static void *player = NULL;
extern BITMAP *BlitSource;

static void INLINE helper(DIALOG *dlg,AL_METHOD(int, proc, (int, struct DIALOG *, int )),
   int x, int y, int w, int h,   /* position and size of the object */
   int fg, int bg,               /* foreground and background colors */
   int key,                      /* keyboard shortcut (ASCII code) */
   int flags,                    /* flags about the object state */
   int d1, int d2,               /* any data the object might require */
   void *dp,void *dp2,void *dp3) {       /* pointers to more object data */
  dlg->proc = proc;
  dlg->x=x; dlg->y=y; dlg->w=w; dlg->h=h;
  dlg->fg=fg; dlg->bg=bg;
  dlg->flags=flags;
  dlg->d1=d1; dlg->d2=d2;
  dlg->dp = dp; dlg->dp2 = dp2; dlg->dp3 = dp3;
}

static int mixer_slider(void *dp3,int d2) {
  int *pvol = ((int*)dp3);
  int id = pvol - SampleVol;
  stream_set_volume(id,d2);
  return D_O_K;
}

static int kill; // indicate wether to kill the gui_screen...
extern int get_stream_sample_rate(int channel); // used only here, defined in streams.c

static void mixer_draw(int *kill) {
  static DIALOG mixer[64];
  const char *name;
  int x=25, y=0,n=1,channel,ymax=0;
  int old_valid = screen_valid;
  static char rate[MAX_STREAM_CHANNELS][7];
  screen_valid = 1;
  screen_valid = old_valid;
  setup_gui();
  setup_gui_screen(kill); // also shows mouse

  helper(mixer,d_raine_window_proc,x,   y,   270,  240,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Mixer",NULL,NULL);
  x+=10; y+=20;
  for (channel = 0;channel < MAX_STREAM_CHANNELS;channel ++) {
    sprintf(&rate[channel][0],"%dK",get_stream_sample_rate(channel)/1000);
    name = stream_get_name(channel);
    if (name) {

      helper(&mixer[n++],x_text_proc,x, y, 1, 1, GUI_COL_TEXT_2, GUI_BOX_COL_MIDDLE, 0, 0, 0, 0, ((void*)name),NULL,NULL);
      y+=10;
      helper(&mixer[n++],raine_slider_proc,x,y,100,10,GUI_COL_TEXT_2,GUI_BOX_COL_MIDDLE,0,0,255,SampleVol[channel],NULL,mixer_slider,&SampleVol[channel]);
      helper(&mixer[n++],x_text_proc,x+105,y,1,1,GUI_COL_TEXT_2,GUI_BOX_COL_MIDDLE,0,0,0,0,(void*)rate[channel],NULL,NULL);
      y+=10;
      if (y>180){
	ymax = y;
	x+=130; y=20;
      }
    }
  }

  if (ymax) { // The button is at the bottom !
    y = ymax;
    x-= 130;
  }

  if (y == 20) { // No sound
    helper(&mixer[n++],x_text_proc,x, y, 1, 1, GUI_COL_TEXT_2, GUI_BOX_COL_MIDDLE, 0, 0, 0, 0, "No stream allocated",NULL,NULL);
    y+=20;
  } else
    y+=10;

  // Exit button
  helper(&mixer[n++],x_raine_button_proc,x,y, 48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Exit",NULL,NULL);
/*   helper(&mixer[n++],x_text_proc,x,y, 1,  1,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,  0,  0,    0,    "Press mixer key to exit",NULL,NULL); */

  helper(&mixer[n],NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL,NULL,NULL);
  if (ymax)
    x += 130; // To centre...
  mixer[0].w = x+130;
  mixer[0].h = y+25;
  raine_centre_dialog(mixer);
  player = init_dialog(mixer,n-1);
}

static void my_update_dlg() {
  if (!update_dialog(player)) {
    switch_mixer();
  }
}

void switch_mixer() {
   VIDEO_INFO *vid_info;
   vid_info = (VIDEO_INFO*)current_game->video;
   if (old_draw) { // restores normal screen
     if (player) {
       shutdown_dialog(player);
       player = NULL;
     }
     release_gui();
     done_gui_screen(&kill);
     vid_info->draw_game = old_draw;
     old_draw=NULL;
     RefreshBuffers = 1;
     vid_info->draw_game();
   } else {
     old_draw = vid_info->draw_game;
     vid_info->draw_game = my_update_dlg;
     mixer_draw(&kill);
   }
}
