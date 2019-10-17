#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "gui.h"
#include "keys.h"

#include "control.h"

DIALOG input_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   272,  204,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Keyboard Setup"},
   { d_raine_list_proc,  48,   26+12,256,  112,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    inputlist_getter},
   { x_raine_button_proc,48,   174+16,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { key_edit_proc,      104,  174+16,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Edit"},
   { x_text_proc,        48,   156,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Keys for this game:"},
   { keys_radio_proc,    48,   166,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "Use Default settings"},
   { keys_radio_proc,    48,   176,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    1,    "Use Custom settings"},
   { x_text_proc,        180,  156,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Controls:"},
   { keys_radio_proc_2,  180,  166,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Default settings"},
   { keys_radio_proc_2,  180,  176,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Emulator settings"},
   { keys_radio_proc_2,  180,  186,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Custom for this game"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Keyboard Controls:"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG key_editing[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)             (bg)                 (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    0,    160,  50,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Keyboard Input"},
   { x_ctext_proc,       80,   26,   0,    0,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Press New Key..."},
   { key_select_proc,    0,    0,    0,    0,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

/*

Updated to allegro 3921 data

*/

static char key_name[20];

static char *modif[] =
{ "Shift ",
  "Ctrl ",
  "Alt ",
  "LWin ",
  "RWin ",
  "Menu ",
};

static void modifiers(char *buff,UINT8 flag)
{
  int n;
  strcpy(buff,"");
  for (n=0; n<=5; n++)
    if (flag & (1 << n))
      strcat(buff,modif[n]);
}

char *KeyName(UINT16 scancode)
{
   if (scancode > 0xff) {
     modifiers(key_name,scancode>>8);
     strcat(key_name,KeyName(scancode & 0xff));
     return key_name;
   }
   switch(scancode){
   case 0                     : return "<None>"; // #0
   case KEY_A                 : return "A"; // #1
   case KEY_B                 : return "B"; // #2
   case KEY_C                 : return "C"; // #3
   case KEY_D                 : return "D"; // #4
   case KEY_E                 : return "E"; // #5
   case KEY_F                 : return "F"; // #6
   case KEY_G                 : return "G"; // #7
   case KEY_H                 : return "H"; // #8
   case KEY_I                 : return "I"; // #9
   case KEY_J                 : return "J"; // #10
   case KEY_K                 : return "K"; // #11
   case KEY_L                 : return "L"; // #12
   case KEY_M                 : return "M"; // #13
   case KEY_N                 : return "N"; // #14
   case KEY_O                 : return "O"; // #15
   case KEY_P                 : return "P"; // #16
   case KEY_Q                 : return "Q"; // #17
   case KEY_R                 : return "R"; // #18
   case KEY_S                 : return "S"; // #19
   case KEY_T                 : return "T"; // #20
   case KEY_U                 : return "U"; // #21
   case KEY_V                 : return "V"; // #22
   case KEY_W                 : return "W"; // #23
   case KEY_X                 : return "X"; // #24
   case KEY_Y                 : return "Y"; // #25
   case KEY_Z                 : return "Z"; // #26
   case KEY_0                 : return "0"; // #27
   case KEY_1                 : return "1"; // #28
   case KEY_2                 : return "2"; // #29
   case KEY_3                 : return "3"; // #30
   case KEY_4                 : return "4"; // #31
   case KEY_5                 : return "5"; // #32
   case KEY_6                 : return "6"; // #33
   case KEY_7                 : return "7"; // #34
   case KEY_8                 : return "8"; // #35
   case KEY_9                 : return "9"; // #36
   case KEY_0_PAD             : return "0 (pad)"; // #37
   case KEY_1_PAD             : return "1 (pad)"; // #38
   case KEY_2_PAD             : return "2 (pad)"; // #39
   case KEY_3_PAD             : return "3 (pad)"; // #40
   case KEY_4_PAD             : return "4 (pad)"; // #41
   case KEY_5_PAD             : return "5 (pad)"; // #42
   case KEY_6_PAD             : return "6 (pad)"; // #43
   case KEY_7_PAD             : return "7 (pad)"; // #44
   case KEY_8_PAD             : return "8 (pad)"; // #45
   case KEY_9_PAD             : return "9 (pad)"; // #46
   case KEY_F1                : return "F1"; // #47
   case KEY_F2                : return "F2"; // #48
   case KEY_F3                : return "F3"; // #49
   case KEY_F4                : return "F4"; // #50
   case KEY_F5                : return "F5"; // #51
   case KEY_F6                : return "F6"; // #52
   case KEY_F7                : return "F7"; // #53
   case KEY_F8                : return "F8"; // #54
   case KEY_F9                : return "F9"; // #55
   case KEY_F10               : return "F10"; // #56
   case KEY_F11               : return "F11"; // #57
   case KEY_F12               : return "F12"; // #58
   case KEY_ESC               : return "Esc"; // #59
   case KEY_TILDE             : return "¦"; // #60 was ¼
   case KEY_MINUS             : return "-"; // #61
   case KEY_EQUALS            : return "="; // #62
   case KEY_BACKSPACE         : return "Backspace"; // #63
   case KEY_TAB               : return "Tab"; // #64
   case KEY_OPENBRACE         : return "{"; // #65
   case KEY_CLOSEBRACE        : return "}"; // #66
   case KEY_ENTER             : return "Enter"; // #67
   case KEY_COLON             : return ":"; // #68
   case KEY_QUOTE             : return "'"; // #69
   case KEY_BACKSLASH         : return "#"; // #70
   case KEY_BACKSLASH2        : return "\\"; // #71
   case KEY_COMMA             : return ","; // #72
   case KEY_STOP              : return "."; // #73
   case KEY_SLASH             : return "/"; // #74
   case KEY_SPACE             : return "Space"; // #75
   case KEY_INSERT            : return "Insert"; // #76
   case KEY_DEL               : return "Delete"; // #77
   case KEY_HOME              : return "Home"; // #78
   case KEY_END               : return "End"; // #79
   case KEY_PGUP              : return "Page Up"; // #80
   case KEY_PGDN              : return "Page Down"; // #81
   case KEY_LEFT              : return "Left"; // #82
   case KEY_RIGHT             : return "Right"; // #83
   case KEY_UP                : return "Up"; // #84
   case KEY_DOWN              : return "Down"; // #85
   case KEY_SLASH_PAD         : return "/ (pad)"; // #86
   case KEY_ASTERISK          : return "* (pad)"; // #87
   case KEY_MINUS_PAD         : return "- (pad)"; // #88
   case KEY_PLUS_PAD          : return "+ (pad)"; // #89
   case KEY_DEL_PAD           : return "Del (pad)"; // #90
   case KEY_ENTER_PAD         : return "Enter (pad)"; // #91
   case KEY_PRTSCR            : return "Print Scr"; // #92
   case KEY_PAUSE             : return "Pause"; // #93
   case KEY_LSHIFT            : return "Left Shift"; // #94
   case KEY_RSHIFT            : return "Right Shift"; // #95
   case KEY_LCONTROL          : return "Left Ctrl"; // #96
   case KEY_RCONTROL          : return "Right Ctrl"; // #97
   case KEY_ALT               : return "Left Alt"; // #98
   case KEY_ALTGR             : return "Right Alt"; // #99
   case KEY_LWIN              : return "Left Win"; // #100
   case KEY_RWIN              : return "Right Win"; // #101
   case KEY_MENU              : return "Menu Win"; // #102
   case KEY_SCRLOCK           : return "Scr Lock"; // #103
   case KEY_NUMLOCK           : return "Num Lock"; // #104
   case KEY_CAPSLOCK          : return "Caps Lock"; // #105
   default                    : return "<Undefined>"; // #???
   }
}

int key_view_mode = 0;

void set_use_custom(int ta)
{
   use_custom_keys = ta;

   input_select[KEY_TYPE_LIST+0].flags=0;
   input_select[KEY_TYPE_LIST+1].flags=0;

   input_select[KEY_TYPE_LIST+use_custom_keys].flags=D_SELECTED;
}

void set_key_view_mode(int ta)
{
   key_view_mode = ta;

   input_select[KEY_VIEW_LIST+0].flags=0;
   input_select[KEY_VIEW_LIST+1].flags=0;
   input_select[KEY_VIEW_LIST+2].flags=0;

   input_select[KEY_VIEW_LIST+key_view_mode].flags=D_SELECTED;
}

void do_key_edit(void)
{
   switch(key_view_mode){
      case 0:
	raine_set_scancode(input_select[1].d1,read_new_keycode());
      break;
      case 1:
	raine_set_emu_scancode(input_select[1].d1,read_new_keycode() |
		 ((key_shifts & 0x3f)<<8)); // GUI keys now know about modifiers...
      break;
      case 2:
         if(use_custom_keys){
	   raine_set_key(input_select[1].d1,read_new_keycode());
	   set_use_custom(1);
         }
      break;
   }
}



/*

key edit custom mode

*/

int keys_radio_proc(int msg, DIALOG *d, int c)
{
   int i;
   int ret=x_raine_radio_proc(msg, d, c);

   if((msg==MSG_KEY)||(msg==MSG_CLICK)){

      i = use_custom_keys;

      if((input_select[KEY_TYPE_LIST+0].flags)&D_SELECTED) use_custom_keys=0;
      if((input_select[KEY_TYPE_LIST+1].flags)&D_SELECTED) use_custom_keys=1;

      SEND_MESSAGE(&input_select[1], MSG_END, 0);

      if((use_custom_keys) && (!i)) reset_game_keys();

      SEND_MESSAGE(&input_select[1], MSG_START, 0);

      scare_mouse();
      broadcast_dialog_message(MSG_DRAW, 0);
      unscare_mouse();

      while(gui_mouse_b()){
         dialog_oxygen();
      };
   }

   return ret;
}


/*

key edit view mode

*/

int keys_radio_proc_2(int msg, DIALOG *d, int c)
{
   int ret=x_raine_radio_proc(msg, d, c);

   if((msg==MSG_KEY)||(msg==MSG_CLICK)){

      if((input_select[KEY_VIEW_LIST+0].flags)&D_SELECTED) key_view_mode=0;
      if((input_select[KEY_VIEW_LIST+1].flags)&D_SELECTED) key_view_mode=1;
      if((input_select[KEY_VIEW_LIST+2].flags)&D_SELECTED) key_view_mode=2;

      SEND_MESSAGE(&input_select[1], MSG_END, 0);

      SEND_MESSAGE(&input_select[1], MSG_START, 0);

      scare_mouse();
      broadcast_dialog_message(MSG_DRAW, 0);
      unscare_mouse();

      while(gui_mouse_b()){
         dialog_oxygen();
      };
   }

   return ret;
}

/*

keyboard edit dialog

*/

int input_select_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){

      Unselect_Button(d);
      FadeGUI();

      set_use_custom(use_custom_keys);
      set_key_view_mode(key_view_mode);

      ret=0;
      while((ret!=2)&&(ret!=-1)){
         ret=raine_do_dialog(input_select,-1);
         if((ret!=2)&&(ret!=-1)){

            do_key_edit();

         }
      }
      if (current_game && !use_custom_keys)
	init_inputs();

      ret = D_REDRAW;

   }

   return ret;
}

static UINT8 selected_key;

int key_select_proc(int msg, DIALOG *d, int c)
{
   int ta,tb;

   switch(msg){
      case MSG_START:
      case MSG_END:

         ta = 1;
         while(ta!=0){
            ta = 0;
            for(tb=1;tb<KEY_MAX;tb++){
               if(key[tb]){
	         if (key_view_mode == 1 && // Emulator keys
		     tb >= KEY_MODIFIERS)
	           continue;
		 ta = 1;
	       }
            }
         }
         clear_keybuf();

         return D_O_K;

      break;
      case MSG_IDLE:
         for(tb=1;tb<KEY_MAX;tb++){
            if(key[tb]){
	      if (key_view_mode == 1 && // Emulator keys
		  tb >= KEY_MODIFIERS)
	        continue;

              selected_key = tb;
              return D_EXIT;
            }
         }
         return D_O_K;
      break;
      default:
         return D_O_K;
      break;
   }
}

UINT8 read_new_keycode(void)
{
   FadeGUI();
   raine_do_dialog(key_editing,-1);
   return selected_key;
}

int key_edit_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      do_key_edit();
      ret = D_REDRAW;
   }
   return ret;
}

// control.c
extern char*inputlist_getter(int index, int *list_size);
