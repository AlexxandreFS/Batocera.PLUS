#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "gui.h"
#include "joystick.h"

#include "control.h"
#include "alleg/alleg_ctrl.h"


DIALOG joy_input_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   272,  204,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Joystick Setup"},
   { d_raine_list_proc,  48,   26+12,256,  112,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    joy_inputlist_getter},
   { x_raine_button_proc,48,   174+16,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { joy_key_edit_proc,  104,  174+16,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Edit"},
   { x_text_proc,        48,   156,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Joy for this game:"},
   { joy_keys_radio_proc,48,   166,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "Use Default settings"},
   { joy_keys_radio_proc,48,   176,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "Use Custom settings"},
   { x_text_proc,        180,  156,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Controls:"},
   { joy_keys_radio_proc_2,180,166,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Default settings"},
   { joy_keys_radio_proc_2,180,176,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Emulator settings"},
   { joy_keys_radio_proc_2,180,186,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Custom for this game"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Joystick Controls:"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG joy_key_editing[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)             (bg)                 (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    0,    160,  50,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Joystick Input"},
   { x_ctext_proc,       80,   26,   0,    0,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Push Joystick..."},
   { joy_key_select_proc,0,    0,    0,    0,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

static char dlg_axis_name[40],axis_legend[40];
static char *joy_axis_getter(int index, int *list_size);

DIALOG joy_axis_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,   0,   140,  146,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    dlg_axis_name},
   { x_text_proc,        8,    16,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    axis_legend},
   { d_raine_list_proc,  10,   30, 120,  80,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,       0,    0,    joy_axis_getter},
   { x_raine_button_proc,46,   120,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

   static char *joy_switches[] =
   {
   "<None>",

   "Joy1 Up",
   "Joy1 Down",
   "Joy1 Left",
   "Joy1 Right",

   "Joy1 Button 1",
   "Joy1 Button 2",
   "Joy1 Button 3",
   "Joy1 Button 4",
   "Joy1 Button 5",
   "Joy1 Button 6",
   "Joy1 Button 7",
   "Joy1 Button 8",

   "Joy2 Up",
   "Joy2 Down",
   "Joy2 Left",
   "Joy2 Right",

   "Joy2 Button 1",
   "Joy2 Button 2",
   "Joy2 Button 3",
   "Joy2 Button 4",
   "Joy2 Button 5",
   "Joy2 Button 6",
   "Joy2 Button 7",
   "Joy2 Button 8",

   "Joy3 Up",
   "Joy3 Down",
   "Joy3 Left",
   "Joy3 Right",

   "Joy3 Button 1",
   "Joy3 Button 2",
   "Joy3 Button 3",
   "Joy3 Button 4",
   "Joy3 Button 5",
   "Joy3 Button 6",
   "Joy3 Button 7",
   "Joy3 Button 8",

   "Joy4 Up",
   "Joy4 Down",
   "Joy4 Left",
   "Joy4 Right",

   "Joy4 Button 1",
   "Joy4 Button 2",
   "Joy4 Button 3",
   "Joy4 Button 4",
   "Joy4 Button 5",
   "Joy4 Button 6",
   "Joy4 Button 7",
   "Joy4 Button 8",

   "Joy1 Button 9",
   "Joy1 Button 10",
   "Joy1 Button 11",
   "Joy1 Button 12",

   "Joy2 Button 9",
   "Joy2 Button 10",
   "Joy2 Button 11",
   "Joy2 Button 12",

   "Joy3 Button 9",
   "Joy3 Button 10",
   "Joy3 Button 11",
   "Joy3 Button 12",

   "Joy4 Button 9",
   "Joy4 Button 10",
   "Joy4 Button 11",
   "Joy4 Button 12",

   "Joy1 Button 13",
   "Joy1 Button 14",
   "Joy1 Button 15",
   "Joy1 Button 16",
   "Joy1 Button 16",
   "Joy1 Button 17",
   "Joy1 Button 18",
   "Joy1 Button 19",
   "Joy1 Button 20",
   "Joy1 Button 21",
   "Joy1 Button 22",
   "Joy1 Button 23",
   "Joy1 Button 24",

   "Joy2 Button 13",
   "Joy2 Button 14",
   "Joy2 Button 15",
   "Joy2 Button 16",
   "Joy2 Button 16",
   "Joy2 Button 17",
   "Joy2 Button 18",
   "Joy2 Button 19",
   "Joy2 Button 20",
   "Joy2 Button 21",
   "Joy2 Button 22",
   "Joy2 Button 23",
   "Joy2 Button 24",

   "Joy3 Button 13",
   "Joy3 Button 14",
   "Joy3 Button 15",
   "Joy3 Button 16",
   "Joy3 Button 16",
   "Joy3 Button 17",
   "Joy3 Button 18",
   "Joy3 Button 19",
   "Joy3 Button 20",
   "Joy3 Button 21",
   "Joy3 Button 22",
   "Joy3 Button 23",
   "Joy3 Button 24",

   "Joy4 Button 13",
   "Joy4 Button 14",
   "Joy4 Button 15",
   "Joy4 Button 16",
   "Joy4 Button 16",
   "Joy4 Button 17",
   "Joy4 Button 18",
   "Joy4 Button 19",
   "Joy4 Button 20",
   "Joy4 Button 21",
   "Joy4 Button 22",
   "Joy4 Button 23",
   "Joy4 Button 24",

   };

#define RJOY_COUNT (sizeof(joy_switches) / sizeof(char*))

/* Allegro specific code in control.c : */
void raine_set_joycode(int index, int code);
void raine_set_emu_joycode(int index, int code);
int raine_get_joycode(int index);
int raine_get_emu_joycode(int index);
void raine_set_input_joycode(int index, int code);
int raine_get_input_joycode(int index);

extern UINT8 rjoy[RJOY_COUNT];

static char *JoyName(int scancode)
{

   if(scancode>=RJOY_COUNT) scancode=0;

   return joy_switches[scancode];
}

static int joy_key_view_mode = 0;

void joy_set_use_custom(int ta)
{
   joy_use_custom_keys = ta;

   joy_input_select[JOY_KEY_TYPE_LIST+0].flags=0;
   joy_input_select[JOY_KEY_TYPE_LIST+1].flags=0;

   joy_input_select[JOY_KEY_TYPE_LIST+joy_use_custom_keys].flags=D_SELECTED;
}

void set_joy_key_view_mode(int ta)
{
   joy_key_view_mode = ta;

   joy_input_select[JOY_KEY_VIEW_LIST+0].flags=0;
   joy_input_select[JOY_KEY_VIEW_LIST+1].flags=0;
   joy_input_select[JOY_KEY_VIEW_LIST+2].flags=0;

   joy_input_select[JOY_KEY_VIEW_LIST+joy_key_view_mode].flags=D_SELECTED;
}

void do_joy_edit(void)
{
   switch(joy_key_view_mode){
      case 0:
	raine_set_joycode(joy_input_select[1].d1,joy_read_new_keycode());
      break;
      case 1:
	raine_set_emu_joycode(joy_input_select[1].d1,joy_read_new_keycode());
      break;
      case 2:
         if((raine_get_input_count())&&(joy_use_custom_keys)){
	   raine_set_input_joycode(joy_input_select[1].d1,joy_read_new_keycode());
	   joy_set_use_custom(1);
         }
      break;
   }
}

static int current_joy;

static char *joy_axis_getter(int index, int *list_size)
{
   static char S[128];

   switch(index){
   case -1:			// Return List Size
      *list_size = joy[current_joy].num_sticks;
      return NULL;
   break;
#if 0
   case -2:			// Act upon List Object Selection
      do_joy_edit();
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
#endif
   default:
      if((index >= 0)&&(index < joy[current_joy].num_sticks)){
	sprintf(S,"%d: %s",index,joy[current_joy].stick[index].name);
	return S;
      }
      else
         return NULL;
   break;
   }
}

char *joy_inputlist_getter(int index, int *list_size)
{
   static char S[128];

   switch(joy_key_view_mode){

   case 0:

   switch(index){
   case -1:			// Return List Size
      *list_size = KB_DEF_COUNT;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      do_joy_edit();
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < KB_DEF_COUNT)){
         sprintf(S,"%-21s %s",raine_get_key_name(index), JoyName(raine_get_joycode(index)));
         return S;
      }
      else
         return NULL;
   break;
   }

   break;
   case 1:

   switch(index){
   case -1:			// Return List Size
      *list_size = KB_EMU_DEF_COUNT;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      do_joy_edit();
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < KB_EMU_DEF_COUNT)){
         sprintf(S,"%-21s %s",raine_get_emu_key_name(index), JoyName(raine_get_emu_joycode(index)));
         return S;
      }
      else
         return NULL;
   break;
   }

   break;
   case 2:

   if(!joy_use_custom_keys){

      if(index==-1){
         *list_size=1;
         return NULL;
      }
      if(index==0){
         return raine_translate_text("<Using Default Settings>");
      }
      return NULL;

   }

   if(!raine_get_input_count()){

      if(index==-1){
         *list_size=1;
         return NULL;
      }
      if(index==0){
         return raine_translate_text("<No Inputs Mapped>");
      }
      return NULL;

   }

   switch(index){
   case -1:			// Return List Size
      *list_size = raine_get_input_count();
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      do_joy_edit();
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < raine_get_input_count())){
         sprintf(S,"%-21s %s",raine_input_name(index), JoyName(raine_get_input_joycode(index)));
         return S;
      }
      else
         return NULL;
   break;
   }

   break;
   }

   return NULL;
}

int joy_keys_radio_proc(int msg, DIALOG *d, int c)
{
   int i;
   int ret=x_raine_radio_proc(msg, d, c);

   if((msg==MSG_KEY)||(msg==MSG_CLICK)){

      i = joy_use_custom_keys;

      if((joy_input_select[JOY_KEY_TYPE_LIST+0].flags)&D_SELECTED) joy_use_custom_keys=0;
      if((joy_input_select[JOY_KEY_TYPE_LIST+1].flags)&D_SELECTED) joy_use_custom_keys=1;

      SEND_MESSAGE(&joy_input_select[1], MSG_END, 0);

      if((joy_use_custom_keys) && (!i)) joy_reset_game_keys();

      SEND_MESSAGE(&joy_input_select[1], MSG_START, 0);

      scare_mouse();
      broadcast_dialog_message(MSG_DRAW, 0);
      unscare_mouse();

      while(gui_mouse_b()){
         dialog_oxygen();
      };
   }

   return ret;
}

int joy_keys_radio_proc_2(int msg, DIALOG *d, int c)
{
   int ret=x_raine_radio_proc(msg, d, c);

   if((msg==MSG_KEY)||(msg==MSG_CLICK)){

      if((joy_input_select[JOY_KEY_VIEW_LIST+0].flags)&D_SELECTED) joy_key_view_mode=0;
      if((joy_input_select[JOY_KEY_VIEW_LIST+1].flags)&D_SELECTED) joy_key_view_mode=1;
      if((joy_input_select[JOY_KEY_VIEW_LIST+2].flags)&D_SELECTED) joy_key_view_mode=2;

      SEND_MESSAGE(&joy_input_select[1], MSG_END, 0);

      SEND_MESSAGE(&joy_input_select[1], MSG_START, 0);

      scare_mouse();
      broadcast_dialog_message(MSG_DRAW, 0);
      unscare_mouse();

      while(gui_mouse_b()){
         dialog_oxygen();
      };
   }

   return ret;
}

int joy_select_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      joy_set_use_custom(joy_use_custom_keys);
      set_joy_key_view_mode(joy_key_view_mode);

      ret=0;
      while((ret!=2)&&(ret!=-1)){
         ret=raine_do_dialog(joy_input_select,-1);
         if((ret!=2)&&(ret!=-1)){

            do_joy_edit();

         }
      }
      return D_REDRAW;
   }
   return ret;
}

void joy_axis_proc(int num)
{
  current_joy = num;
  sprintf(dlg_axis_name,"Joystick %d",num);
  sprintf(axis_legend,"Axis for direction ?");
  joy_axis_select[2].d1 = direction_stick[num];
  raine_do_dialog(joy_axis_select,-1);
  direction_stick[num] = joy_axis_select[2].d1;
}

static UINT8 joy_selected_key;
static int ignored_inputs[256];
static int nb_ignored = 0;

int joy_key_select_proc(int msg, DIALOG *d, int c)
{
   int ta,tb;

   switch(msg){
      case MSG_START:
      case MSG_END:

	 if (msg == MSG_START)
	   nb_ignored = 0;

         ta = 1;
         while(ta){
            ta = 0;
            update_rjoy_list();
            for(tb=0;tb<RJOY_COUNT;tb++){
               if(rjoy[tb]) {
		 if (msg == MSG_START) {
		   /* The microsoft digital keyboard is recgnized as a joystick in linux, with a stick
		    * always in the extreme direction. So here is the workaround : we just ignore any
		    * input enabled when the dialog starts */
		   ignored_inputs[nb_ignored++] = tb;
		   if (nb_ignored >= 256) {
		     printf("too many joystick inputs to ignore, bye bye...\n");
		     exit(1);
		   }
		 } else {
		   int found = 0;
		   int n;
		   for (n=0; n<nb_ignored; n++) {
		     if (ignored_inputs[n] == tb) {
		       found = 1;
		       break;
		     }
		   }
		   if (!found) {
		     ta = 1;
		   }
		 }
	       }
            }
         }

         ta = 1;
         while(ta){
            ta = 0;
            for(tb=1;tb<KEY_MAX;tb++){
               if(key[tb]) ta = 1;
            }
         }
         clear_keybuf();

         return D_O_K;

      break;
      case MSG_IDLE:

         update_rjoy_list();
         for(tb=0;tb<RJOY_COUNT;tb++){
            if(rjoy[tb]){
		   int found = 0;
		   int n;
		   for (n=0; n<nb_ignored; n++) {
		     if (ignored_inputs[n] == tb) {
		       found = 1;
		       break;
		     }
		   }
		   if (!found) {
		     joy_selected_key = tb;
		     return D_EXIT;
		   }
            }
         }

         if(key[KEY_ESC]){
            joy_selected_key = 0;
            return D_EXIT;
         }

         return D_O_K;
      break;
      default:
         return D_O_K;
      break;
   }
}

UINT8 joy_read_new_keycode(void)
{
   FadeGUI();
   raine_do_dialog(joy_key_editing,-1);
   return joy_selected_key;
}

int joy_key_edit_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      do_joy_edit();
      ret = D_REDRAW;
   }
   return ret;
}
