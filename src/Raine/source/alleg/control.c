/******************************************************************************/
/*                                                                            */
/*                 CONTROL SUPPORT [KEYBOARD/JOYSTICK/LEDS]                   */
/*                                                                            */
/******************************************************************************/
/*
  How the controls work :

  the game drivers expect a bit to be cleared or set when a specific control
  changes (like a button pressed/released or a movement of the stick).
  So for each bit of the controls to test, we have the index in our array of
  controls to test.

  For example :
   { KB_DEF_P1_B1,        MSG_P1_B1,               0x000001, 0x10, BIT_ACTIVE_0 },

   means : the key for p1_b1, which is called MSG_P1_B1 in the gui should change
   bitmask 0x10 at offset 1 in the controls so that the bit is 0 if the key is
   pressed.

   For the keyboard, KB_DEF_P1_B1 just gives an index in the allegro key array
   to check.
   For the joysticks, we reproduce the same behaviour by updating our own
   rjoy array based on the joystick changes (see update_rjoy_lists)

   Note : that's not the right way to test the joystick anymore. This test is relevant
   for the simplest joysticks (1 stick + a few buttons) but even when only the number of
   button becomes high it shows its limits, and when there is more than 1 stick on the
   joystick, the 2nd one can not be tested at the same time.
   We'll try a new joystick poll method in sdl, and maybe this new method will be backported
   one day to allegro, but it's not sure, allegro has really become outdated on quite
   a few important things.
*/

/* TODO : all these functions to handle def_input, def_input_emu and then INPUT
   look like a waste of space. It should be possible to rewrite all this by using C++
   for example. But for now I have too much to rewrite to take the time to improve this.

   I'll probably have to rewrite all this when building the sdl gui anyway... */

#include "raine.h"
#include "games.h"
#include "control.h"
#include "demos.h"
#include "ingame.h"
#include "savegame.h"           // Save/Load game stuff
#include "profile.h" // switch_fps_mode
#include "gui/sound.h"
#include "emumain.h" // key_pause_fwd
#include "sasound.h"
#include "blit.h"
#include "keys.h"
#include "alleg/alleg_ctrl.h"

int GameMouse,use_leds,JoystickType,direction_stick[4];
UINT8 input_buffer[0x100];
int use_custom_keys;
int joy_use_custom_keys;

typedef struct DEF_INPUT
{
   UINT16 scancode;
   UINT8 joycode;
   char *name;
} DEF_INPUT;

volatile int *MouseB;
UINT32 p1_trackball_x;
UINT32 p1_trackball_y;

void (*GetMouseMickeys)(int *mx,int *my) = &get_mouse_mickeys;

enum {
   RJOY_NULL = 0,

   RJOY_1_UP,
   RJOY_1_DOWN,
   RJOY_1_LEFT,
   RJOY_1_RIGHT,

   RJOY_1_BUTTON1,
   RJOY_1_BUTTON2,
   RJOY_1_BUTTON3,
   RJOY_1_BUTTON4,
   RJOY_1_BUTTON5,
   RJOY_1_BUTTON6,
   RJOY_1_BUTTON7,
   RJOY_1_BUTTON8,

   RJOY_2_UP,
   RJOY_2_DOWN,
   RJOY_2_LEFT,
   RJOY_2_RIGHT,

   RJOY_2_BUTTON1,
   RJOY_2_BUTTON2,
   RJOY_2_BUTTON3,
   RJOY_2_BUTTON4,
   RJOY_2_BUTTON5,
   RJOY_2_BUTTON6,
   RJOY_2_BUTTON7,
   RJOY_2_BUTTON8,

   RJOY_3_UP,
   RJOY_3_DOWN,
   RJOY_3_LEFT,
   RJOY_3_RIGHT,

   RJOY_3_BUTTON1,
   RJOY_3_BUTTON2,
   RJOY_3_BUTTON3,
   RJOY_3_BUTTON4,
   RJOY_3_BUTTON5,
   RJOY_3_BUTTON6,
   RJOY_3_BUTTON7,
   RJOY_3_BUTTON8,

   RJOY_4_UP,
   RJOY_4_DOWN,
   RJOY_4_LEFT,
   RJOY_4_RIGHT,

   RJOY_4_BUTTON1,
   RJOY_4_BUTTON2,
   RJOY_4_BUTTON3,
   RJOY_4_BUTTON4,
   RJOY_4_BUTTON5,
   RJOY_4_BUTTON6,
   RJOY_4_BUTTON7,
   RJOY_4_BUTTON8,

   RJOY_1_BUTTON9,
   RJOY_1_BUTTON10,
   RJOY_1_BUTTON11,
   RJOY_1_BUTTON12,

   RJOY_2_BUTTON9,
   RJOY_2_BUTTON10,
   RJOY_2_BUTTON11,
   RJOY_2_BUTTON12,

   RJOY_3_BUTTON9,
   RJOY_3_BUTTON10,
   RJOY_3_BUTTON11,
   RJOY_3_BUTTON12,

   RJOY_4_BUTTON9,
   RJOY_4_BUTTON10,
   RJOY_4_BUTTON11,
   RJOY_4_BUTTON12,

   // How many buttons are possible ? 16 at least, from the forum.
   // Let's go for 24 now...

   RJOY_1_BUTTON13,
   RJOY_1_BUTTON14,
   RJOY_1_BUTTON15,
   RJOY_1_BUTTON16,
   RJOY_1_BUTTON17,
   RJOY_1_BUTTON18,
   RJOY_1_BUTTON19,
   RJOY_1_BUTTON20,
   RJOY_1_BUTTON21,
   RJOY_1_BUTTON22,
   RJOY_1_BUTTON23,
   RJOY_1_BUTTON24,

   RJOY_2_BUTTON13,
   RJOY_2_BUTTON14,
   RJOY_2_BUTTON15,
   RJOY_2_BUTTON16,
   RJOY_2_BUTTON17,
   RJOY_2_BUTTON18,
   RJOY_2_BUTTON19,
   RJOY_2_BUTTON20,
   RJOY_2_BUTTON21,
   RJOY_2_BUTTON22,
   RJOY_2_BUTTON23,
   RJOY_2_BUTTON24,

   RJOY_3_BUTTON13,
   RJOY_3_BUTTON14,
   RJOY_3_BUTTON15,
   RJOY_3_BUTTON16,
   RJOY_3_BUTTON17,
   RJOY_3_BUTTON18,
   RJOY_3_BUTTON19,
   RJOY_3_BUTTON20,
   RJOY_3_BUTTON21,
   RJOY_3_BUTTON22,
   RJOY_3_BUTTON23,
   RJOY_3_BUTTON24,

   RJOY_4_BUTTON13,
   RJOY_4_BUTTON14,
   RJOY_4_BUTTON15,
   RJOY_4_BUTTON16,
   RJOY_4_BUTTON17,
   RJOY_4_BUTTON18,
   RJOY_4_BUTTON19,
   RJOY_4_BUTTON20,
   RJOY_4_BUTTON21,
   RJOY_4_BUTTON22,
   RJOY_4_BUTTON23,
   RJOY_4_BUTTON24,

   RJOY_COUNT,
};

// rjoy[] is an array, which should act just like allegro's key[] array.
// only difference is that it must be updated by the user by calling
// update_rjoy_list().

UINT8 rjoy[RJOY_COUNT];

/******************************************************************************/
/*                                                                            */
/*                        DEFAULT GAME KEY SETTINGS                           */
/*                                                                            */
/******************************************************************************/

static struct DEF_INPUT def_input[KB_DEF_COUNT] =
{
 { KEY_3,       RJOY_1_BUTTON10,"Def Coin A",           },      // KB_DEF_COIN1,
 { KEY_4,       RJOY_2_BUTTON10,"Def Coin B",           },      // KB_DEF_COIN2,
 { KEY_7,       RJOY_3_BUTTON10,"Def Coin C",           },      // KB_DEF_COIN3,
 { KEY_8,       RJOY_4_BUTTON10,"Def Coin D",           },      // KB_DEF_COIN4,

 { KEY_T,       0x00,           "Def Tilt",             },      // KB_DEF_TILT,
 { KEY_Y,       0x00,           "Def Service",          },      // KB_DEF_SERVICE,
 { KEY_U,       0x00,           "Def Test",             },      // KB_DEF_TEST,

 { KEY_1,       RJOY_1_BUTTON9, "Def P1 Start",         },      // KB_DEF_P1_START,

 { KEY_UP,      RJOY_1_UP,      "Def P1 Up",            },      // KB_DEF_P1_UP,
 { KEY_DOWN,    RJOY_1_DOWN,    "Def P1 Down",          },      // KB_DEF_P1_DOWN,
 { KEY_LEFT,    RJOY_1_LEFT,    "Def P1 Left",          },      // KB_DEF_P1_LEFT,
 { KEY_RIGHT,   RJOY_1_RIGHT,   "Def P1 Right",         },      // KB_DEF_P1_RIGHT,

 { KEY_V,       RJOY_1_BUTTON1, "Def P1 Button 1",      },      // KB_DEF_P1_B1,
 { KEY_B,       RJOY_1_BUTTON2, "Def P1 Button 2",      },      // KB_DEF_P1_B2,
 { KEY_N,       RJOY_1_BUTTON3, "Def P1 Button 3",      },      // KB_DEF_P1_B3,
 { KEY_G,       RJOY_1_BUTTON4, "Def P1 Button 4",      },      // KB_DEF_P1_B4,
 { KEY_H,       RJOY_1_BUTTON5, "Def P1 Button 5",      },      // KB_DEF_P1_B5,
 { KEY_J,       RJOY_1_BUTTON6, "Def P1 Button 6",      },      // KB_DEF_P1_B6,
 { KEY_M,       RJOY_1_BUTTON7, "Def P1 Button 7",      },      // KB_DEF_P1_B7,
 { KEY_K,       RJOY_1_BUTTON8, "Def P1 Button 8",      },      // KB_DEF_P1_B8,

 { KEY_2,       RJOY_2_BUTTON9, "Def P2 Start",         },      // KB_DEF_P2_START,

 { KEY_S,       RJOY_2_UP,      "Def P2 Up",            },      // KB_DEF_P2_UP,
 { KEY_X,       RJOY_2_DOWN,    "Def P2 Down",          },      // KB_DEF_P2_DOWN,
 { KEY_Z,       RJOY_2_LEFT,    "Def P2 Left",          },      // KB_DEF_P2_LEFT,
 { KEY_C,       RJOY_2_RIGHT,   "Def P2 Right",         },      // KB_DEF_P2_RIGHT,

 { KEY_Q,       RJOY_2_BUTTON1, "Def P2 Button 1",      },      // KB_DEF_P2_B1,
 { KEY_W,       RJOY_2_BUTTON2, "Def P2 Button 2",      },      // KB_DEF_P2_B2,
 { KEY_E,       RJOY_2_BUTTON3, "Def P2 Button 3",      },      // KB_DEF_P2_B3,
 { KEY_R,       RJOY_2_BUTTON4, "Def P2 Button 4",      },      // KB_DEF_P2_B4,
 { KEY_A,       RJOY_2_BUTTON5, "Def P2 Button 5",      },      // KB_DEF_P2_B5,
 { KEY_D,       RJOY_2_BUTTON6, "Def P2 Button 6",      },      // KB_DEF_P2_B6,
 { KEY_F,       RJOY_2_BUTTON7, "Def P2 Button 7",      },      // KB_DEF_P2_B7,
 { KEY_G,       RJOY_2_BUTTON8, "Def P2 Button 8",      },      // KB_DEF_P2_B8,

 { KEY_5,       RJOY_3_BUTTON9, "Def P3 Start",         },      // KB_DEF_P3_START,

 { 0x00,        RJOY_3_UP,      "Def P3 Up",            },      // KB_DEF_P3_UP,
 { 0x00,        RJOY_3_DOWN,    "Def P3 Down",          },      // KB_DEF_P3_DOWN,
 { 0x00,        RJOY_3_LEFT,    "Def P3 Left",          },      // KB_DEF_P3_LEFT,
 { 0x00,        RJOY_3_RIGHT,   "Def P3 Right",         },      // KB_DEF_P3_RIGHT,

 { 0x00,        RJOY_3_BUTTON1, "Def P3 Button 1",      },      // KB_DEF_P3_B1,
 { 0x00,        RJOY_3_BUTTON2, "Def P3 Button 2",      },      // KB_DEF_P3_B2,
 { 0x00,        RJOY_3_BUTTON3, "Def P3 Button 3",      },      // KB_DEF_P3_B3,
 { 0x00,        RJOY_3_BUTTON4, "Def P3 Button 4",      },      // KB_DEF_P3_B4,
 { 0x00,        RJOY_3_BUTTON5, "Def P3 Button 5",      },      // KB_DEF_P3_B5,
 { 0x00,        RJOY_3_BUTTON6, "Def P3 Button 6",      },      // KB_DEF_P3_B6,
 { 0x00,        RJOY_3_BUTTON7, "Def P3 Button 7",      },      // KB_DEF_P3_B7,
 { 0x00,        RJOY_3_BUTTON8, "Def P3 Button 8",      },      // KB_DEF_P3_B8,

 { KEY_6,       RJOY_4_BUTTON9, "Def P4 Start",         },      // KB_DEF_P4_START,

 { 0x00,        RJOY_4_UP,      "Def P4 Up",            },      // KB_DEF_P4_UP,
 { 0x00,        RJOY_4_DOWN,    "Def P4 Down",          },      // KB_DEF_P4_DOWN,
 { 0x00,        RJOY_4_LEFT,    "Def P4 Left",          },      // KB_DEF_P4_LEFT,
 { 0x00,        RJOY_4_RIGHT,   "Def P4 Right",         },      // KB_DEF_P4_RIGHT,

 { 0x00,        RJOY_4_BUTTON1, "Def P4 Button 1",      },      // KB_DEF_P4_B1,
 { 0x00,        RJOY_4_BUTTON2, "Def P4 Button 2",      },      // KB_DEF_P4_B2,
 { 0x00,        RJOY_4_BUTTON3, "Def P4 Button 3",      },      // KB_DEF_P4_B3,
 { 0x00,        RJOY_4_BUTTON4, "Def P4 Button 4",      },      // KB_DEF_P4_B4,
 { 0x00,        RJOY_4_BUTTON5, "Def P4 Button 5",      },      // KB_DEF_P4_B5,
 { 0x00,        RJOY_4_BUTTON6, "Def P4 Button 6",      },      // KB_DEF_P4_B6,
 { 0x00,        RJOY_4_BUTTON7, "Def P4 Button 7",      },      // KB_DEF_P4_B7,
 { 0x00,        RJOY_4_BUTTON8, "Def P4 Button 8",      },      // KB_DEF_P4_B8,

 { KEY_LCONTROL,0x00,           "Def Flipper 1 Left",   },      // KB_DEF_FLIPPER_1_L,
 { KEY_RCONTROL,0x00,           "Def Flipper 1 Right",  },      // KB_DEF_FLIPPER_1_R,
 { KEY_LSHIFT,  0x00,           "Def Flipper 2 Left",   },      // KB_DEF_FLIPPER_2_L,
 { KEY_RSHIFT,  0x00,           "Def Flipper 2 Right",  },      // KB_DEF_FLIPPER_2_R,
 { KEY_BACKSLASH2,0x00,         "Def Tilt Left",        },      // KB_DEF_TILT_L,
 { KEY_SLASH,   0x00,           "Def Tilt Right",       },      // KB_DEF_TILT_R,
 { KEY_Z,       0x00,           "Def Button 1 Left",    },      // KB_DEF_B1_L,
 { KEY_STOP,    0x00,           "Def Button 1 Right",   },      // KB_DEF_B1_R,

 // Mahjong controls, at least in mahjong quest...
 { KEY_A,       0x00,           "Def P1 A",             }, // KB_DEF_P1_A
 { KEY_E,       0x00,           "Def P1 E",             }, // KB_DEF_P1_E
 { KEY_I,       0x00,           "Def P1 I",             }, // KB_DEF_P1_I
 { KEY_M,       0x00,           "Def P1 M",             }, // KB_DEF_P1_M
 { KEY_LCONTROL,0x00,           "Def P1 Kan/Deal",      }, // KB_DEF_P1_KAN
 { KEY_B,       0x00,           "Def P1 B",             }, // KB_DEF_P1_B
 { KEY_F,       0x00,           "Def P1 F",             }, // KB_DEF_P1_F
 { KEY_J,       0x00,           "Def P1 J",             }, // KB_DEF_P1_J
 { KEY_N,       0x00,           "Def P1 N",             }, // KB_DEF_P1_N
 { KEY_LSHIFT,  0x00,           "Def P1 Reach",         }, // KB_DEF_P1_REACH
 { KEY_C,       0x00,           "Def P1 C",             }, // KB_DEF_P1_C
 { KEY_G,       0x00,           "Def P1 G",             }, // KB_DEF_P1_G
 { KEY_K,       0x00,           "Def P1 K",             }, // KB_DEF_P1_K
 { KEY_SPACE,   0x00,           "Def P1 Chi/Flip",      }, // KB_DEF_P1_CHI
 { KEY_Z,       0x00,           "Def P1 Ron",           }, // KB_DEF_P1_RON,
 { KEY_D,       0x00,           "Def P1 D",             }, // KB_DEF_P1_D
 { KEY_H,       0x00,           "Def P1 H",             }, // KB_DEF_P1_H
 { KEY_L,       0x00,           "Def P1 L",             }, // KB_DEF_P1_L
 { KEY_ALT,     0x00,           "Def P1 Pon/Cancel",    }, // KB_DEF_P1_PON

 { 0,           0,              "Def Service A", }, // KB_DEF_SERVICE_A
 { 0,           0,              "Def Service B", }, // KB_DEF_SERVICE_B
 { 0,           0,              "Def Service C", }, // KB_DEF_SERVICE_C

 { KEY_R,       0x00,           "Def Button 2 Left",    },      // KB_DEF_B2_L,
 { KEY_T,    0x00,           "Def Button 2 Right",   },      // KB_DEF_B2_R,

#ifndef RAINE_DOS
 { 0,           0,  "Player1 B1+B2", }, // p1_b1B2
 { 0,           0,  "Player1 B3+B4", },
 { 0,           0,  "Player1 B2+B3", },
 { 0,           0,  "Player1 B1+B2+B3", },
 { 0,           0,  "Player1 B2+B3+B4", },

 { 0,           0,  "Player2 B1+B2", }, // p2_b1B2
 { 0,           0,  "Player2 B3+B4", },
 { 0,           0,  "Player2 B2+B3", },
 { 0,           0,  "Player2 B1+B2+B3", },
 { 0,           0,  "Player2 B2+B3+B4", },
 { 0,           0,  "Player1 B4+B5+B6", },
#endif

 { 0,           0,  "Next Game", },
 { 0,           0,  "Prev Game", },

 { 0,           0,  "", }, // unknown, should be hidden
 { 0,           0,  "", }, // special, should be hidden
 { 0,           0,  "", }, // unused, should be hidden
};

/******************************************************************************/
/*                                                                            */
/*                       DEFAULT EMULATOR KEY SETTINGS                        */
/*                                                                            */
/******************************************************************************/

char *inputlist_getter(int index, int *list_size)
{
   static char S[128];

   switch(key_view_mode){

   case 0:

   switch(index){
   case -1:			// Return List Size
      *list_size = KB_DEF_COUNT;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      do_key_edit();
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < KB_DEF_COUNT)){
         sprintf(S,"%-21s %s",raine_get_key_name(index), KeyName(raine_get_scancode(index)));
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
      do_key_edit();
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < KB_DEF_COUNT)){
         sprintf(S,"%-21s %s",raine_get_emu_key_name(index), KeyName(raine_get_emu_scancode(index)));
         return S;
      }
      else
         return NULL;
   break;
   }

   break;
   case 2:

   if(!use_custom_keys){

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
      do_key_edit();
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < raine_get_input_count())){
         sprintf(S,"%-21s %s",raine_input_name(index), KeyName(raine_get_key(index)));
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
static struct DEF_INPUT def_input_emu[KB_EMU_DEF_COUNT] =
{
 { KEY_0,       0x00,           "Save Screenshot",      },      // KB_EMU_SCREENSHOT,
 { KEY_PGUP,    0x00,           "Increase frameskip",   },      // KB_EMU_INC_FRAMESKIP,
 { KEY_PGDN,    0x00,           "Decrease frameskip",   },      // KB_EMU_DEC_FRAMESKIP,
 { KEY_HOME,    0x00,           "Increase cpu skip",    },      // KB_EMU_INC_CPU_FRAMESKIP,
 { KEY_END,     0x00,           "Decrease cpu skip",    },      // KB_EMU_DEC_CPU_FRAMESKIP,
 { KEY_F2,      0x00,           "Save game",            },      // KB_EMU_SAVE_GAME,
 { KEY_F3,      0x00,           "Switch save slot",     },      // KB_EMU_SWITCH_SAVE_SLOT,
 { KEY_F4,      0x00,           "Load game",            },      // KB_EMU_LOAD_GAME,
 { KEY_F11,     0x00,           "Switch fps display",   },      // KB_EMU_SWITCH_FPS,
 { KEY_F1,      0x00,           "Reset game",           },      // KB_EMU_RESET_GAME,
 { KEY_P,       0x00,           "Pause game",           },      // KB_EMU_PAUSE_GAME,
 { KEY_ESC,     0x00,           "Stop emulation",       },      // KB_EMU_STOP_EMULATION,
 { KEY_TAB,     0x00,           "Return to gui",        },      // KB_EMU_OPEN_GUI,
 { KEY_UP | (KB_CTRL_FLAG<<8),      0,      "Screen up",            },      // KB_EMU_SCREEN_UP,
 { KEY_DOWN | (KB_CTRL_FLAG<<8),    0,    "Screen down",          },      // KB_EMU_SCREEN_DOWN,
 { KEY_LEFT | (KB_CTRL_FLAG<<8),    0,    "Screen left",          },      // KB_EMU_SCREEN_LEFT,
 { KEY_RIGHT | (KB_CTRL_FLAG<<8),   0,   "Screen right",         },      // KB_EMU_SCREEN_RIGHT,
 { KEY_TILDE,   0x00,           "Switch Mixer",         },      // Mixer
 { KEY_F2 | (KB_CTRL_FLAG<<8), 0x00, "Save game with name",  },      // KB_EMU_SAVE_GAME,
 { KEY_F4 | (KB_CTRL_FLAG<<8), 0x00, "Load game with name",  },      // KB_EMU_LOAD_GAME,
 { KEY_F2 | (KB_SHIFT_FLAG<<8), 0x00, "Save demo",  },      // KB_EMU_SAVE_DEMO,
 { KEY_F4 | (KB_SHIFT_FLAG<<8), 0x00, "Load demo",  },      // KB_EMU_LOAD_DEMO,
 { KEY_SPACE, 0x00, "Fwd 1 frame in pause", },
 { KEY_V | (KB_CTRL_FLAG<<8), 0x00, "Save video", },
};

/* Active inputs (allows to switch from default to custom inputs/game) */
typedef struct INPUT
{
   UINT8 Key;			// keyboard code for this input
   UINT8 Joy;			// joystick code for this input
   char *InputName;		// input name string
   UINT32 Address;		// address in RAM[] for this input
   UINT8 Bit;			// bit mask for this input
   UINT8 high_bit;		// input is acitve high or active low
   UINT16 default_key;		// default button for this input
   UINT8 auto_rate;		// autofire frame rate
   UINT32 active_time;		// frames since the input became active (used for coin time)
} INPUT;

#define MAX_INPUTS 64

static struct INPUT InputList[MAX_INPUTS];	// Max 64 control inputs in a game

static int InputCount;			// Number of Inputs in InputList

static void set_key_from_default(INPUT *inp)
{

  if(!(inp->default_key&0x0100))

    inp->Key = inp->default_key & 0xFF;

  else

    inp->Key = def_input[inp->default_key & 0xFF].scancode;

}

static void set_joy_from_default(INPUT *inp)
{

  if((!(inp->default_key&0x0100)))

    inp->Joy = 0;

  else {
    inp->Joy = def_input[inp->default_key & 0xFF].joycode;
  }

}

static void update_input_buffer(int ta, int input_valid) {
  UINT8 *buffer;

  if(InputList[ta].Address < 0x100)
     buffer = input_buffer;
   else
     buffer = RAM;

  buffer += InputList[ta].Address;

  if(input_valid ^ InputList[ta].high_bit)
    *buffer &= ~ InputList[ta].Bit;
   else
     *buffer |=   InputList[ta].Bit;
}

static void merge_inputs(const INPUT_INFO *input_src) {
    int srcCount = 0;
    int included = 0;
    while(input_src[srcCount].name){

	if (input_src[srcCount].flags == INPUT_INCLUDE) {
	    merge_inputs((const INPUT_INFO *)input_src[srcCount].name);
	    srcCount++;
	    included = 1;
	    continue;
	}

	int n,old = -1;
	// Input overwrite : it happens in case another input is included and
	// then modified
	if (included) { // only if some inputs were included
	    // Otherwise it prevents combinations like A+B in neocd from
	    // working !
	    for (n=0; n<InputCount; n++)
		if (input_src[srcCount].offset == InputList[n].Address &&
			input_src[srcCount].bit_mask & InputList[n].Bit) {
		    old = InputCount;
		    InputCount = n;
		    break;
		}
	}

	UINT16 def = InputList[InputCount].default_key = input_src[srcCount].default_key;
	InputList[InputCount].InputName   = input_src[srcCount].name;
	InputList[InputCount].Address     = input_src[srcCount].offset;
	InputList[InputCount].Bit         = input_src[srcCount].bit_mask;
	InputList[InputCount].high_bit    = input_src[srcCount].flags;
	InputList[InputCount].auto_rate   = 0;
	InputList[InputCount].active_time = 0;
	// InputList[InputCount].link = 0;

	set_key_from_default(&InputList[InputCount]);

	update_input_buffer(InputCount,0); // say input is not valid for now

	if (def != KB_DEF_UNKNOWN && def != KB_DEF_SPECIAL &&
		def != KB_DEF_UNUSED) {
	    // Skip unknown and special inputs after they have been initialized
	    InputCount++;
	} else if (old > -1) {
	    // input overwritten by a hidden input, we must move the list...
	    if (old > InputCount+1)
		memmove(&InputList[InputCount],&InputList[InputCount+1],
			(old-(InputCount+1))*sizeof(struct INPUT));
	    old--;
	}
	if (old > -1) {
	    // Check if some other inputs match the bit mask and remove them
	    for (n=InputCount; n<old; n++) {
		if (input_src[srcCount].offset == InputList[n].Address &&
			input_src[srcCount].bit_mask & InputList[n].Bit) {
		    if (old > n+1)
			memmove(&InputList[n],&InputList[n+1],
				(old-(n+1))*sizeof(struct INPUT));
		    old--;
		    n--;
		}
	    }
	    InputCount = old;
	}
	srcCount++;
    }
}

void init_inputs(void)
{
   const INPUT_INFO *input_src;

   InputCount = 0;

   input_src = current_game->input;

   if(input_src)
       merge_inputs(&input_src[InputCount]);
}

void reset_game_keys(void)
{
   int ta;

   for(ta=0;ta<InputCount;ta++)
      set_key_from_default(&InputList[ta]);
}

void joy_reset_game_keys(void)
{
   int ta;

   for(ta=0;ta<InputCount;ta++)
      set_joy_from_default(&InputList[ta]);
}

void no_spaces(char *str)
{
   int ta,tb;

   tb=strlen(str);

   for(ta=0;ta<tb;ta++){
      if(((str[ta]<'A')||(str[ta]>'Z'))&&
         ((str[ta]<'a')||(str[ta]>'z'))&&
         ((str[ta]<'0')||(str[ta]>'9'))){
         str[ta]='_';
      }
   }
}

void load_game_keys(char *section)
{
   int ta;
   char key_name[64];

   use_custom_keys = raine_get_config_int(section,"use_custom_keys",0);

   // load keys if using custom keys

   if(use_custom_keys){

      for(ta=0;ta<InputCount;ta++){
         sprintf(key_name,"%s",InputList[ta].InputName);
         no_spaces(key_name);
         InputList[ta].Key = raine_get_config_int(section,key_name,InputList[ta].Key);
      }

   }
}

void save_game_keys(char *section)
{
   int ta;
   char key_name[64];

   // clear the old settings first (keep the file tidy)

   raine_clear_config_section(section);

   // save keys if using custom keys

   if(use_custom_keys){

      raine_set_config_int(section,"use_custom_keys",use_custom_keys);

      for(ta=0;ta<InputCount;ta++){
         sprintf(key_name,"%s",InputList[ta].InputName);
         no_spaces(key_name);
         raine_set_config_int(section,key_name,InputList[ta].Key);
      }

   }
}

void load_game_joys(char *section)
{
   int ta;
   char joy_name[64];

   joy_use_custom_keys = raine_get_config_int(section,"use_custom_joystick",0);

   // load joys if using custom joys

   if(joy_use_custom_keys){

      for(ta=0;ta<InputCount;ta++){
         sprintf(joy_name,"%s",InputList[ta].InputName);
         no_spaces(joy_name);
         InputList[ta].Joy = raine_get_config_int(section,joy_name,InputList[ta].Joy);
      }

   }
}

void save_game_joys(char *section)
{
   int ta;
   char joy_name[64];

   // clear the old settings first (keep the file tidy)

   raine_clear_config_section(section);

   // save joys if using custom joys

   if(joy_use_custom_keys){

      raine_set_config_int(section,"use_custom_joystick",joy_use_custom_keys);

      for(ta=0;ta<InputCount;ta++){
         sprintf(joy_name,"%s",InputList[ta].InputName);
         no_spaces(joy_name);
         raine_set_config_int(section,joy_name,InputList[ta].Joy);
      }

   }
}

void load_default_keys(char *section)
{
   int ta;
   char key_name[64];

   use_custom_keys = 0;

   for(ta=0;ta<KB_DEF_COUNT;ta++){
      sprintf(key_name,"%s",def_input[ta].name);
      no_spaces(key_name);
      def_input[ta].scancode = raine_get_config_int(section,key_name,def_input[ta].scancode);
   }
}

void save_default_keys(char *section)
{
   int ta;
   char key_name[64];

   for(ta=0;ta<KB_DEF_COUNT;ta++){
      sprintf(key_name,"%s",def_input[ta].name);
      no_spaces(key_name);
      if (*key_name)
	  raine_set_config_int(section,key_name,def_input[ta].scancode);
   }
}

void load_default_joys(char *section)
{
   int ta;
   char joy_name[64];

   joy_use_custom_keys = 0;

   for(ta=0;ta<KB_DEF_COUNT;ta++){
      sprintf(joy_name,"%s",def_input[ta].name);
      no_spaces(joy_name);
      def_input[ta].joycode = raine_get_config_int(section,joy_name,def_input[ta].joycode);
   }
}

void save_default_joys(char *section)
{
   int ta;
   char joy_name[64];

   for(ta=0;ta<KB_DEF_COUNT;ta++){
      sprintf(joy_name,"%s",def_input[ta].name);
      no_spaces(joy_name);
      if (*joy_name)
	  raine_set_config_int(section,joy_name,def_input[ta].joycode);
   }
}

void load_emulator_keys(char *section)
{
   int ta,scan;
   char key_name[64];

   for(ta=0;ta<KB_EMU_DEF_COUNT;ta++){
      sprintf(key_name,"%s",def_input_emu[ta].name);
      no_spaces(key_name);
      scan = raine_get_config_int(section,key_name,def_input_emu[ta].scancode);
      if (strncmp(key_name,"Screen_",7) || scan < KEY_LEFT || scan > KEY_DOWN) {
	// Forces modifiers for scrolling keys (previously in pause only)
	def_input_emu[ta].scancode = scan;
      }
   }
}

void save_emulator_keys(char *section)
{
   int ta;
   char key_name[64];

   for(ta=0;ta<KB_EMU_DEF_COUNT;ta++){
      sprintf(key_name,"%s",def_input_emu[ta].name);
      no_spaces(key_name);
      raine_set_config_int(section,key_name,def_input_emu[ta].scancode);
   }
}

void load_emulator_joys(char *section)
{
   int ta;
   char joy_name[64];

   for(ta=0;ta<KB_EMU_DEF_COUNT;ta++){
      sprintf(joy_name,"%s",def_input_emu[ta].name);
      no_spaces(joy_name);
      def_input_emu[ta].joycode = raine_get_config_int(section,joy_name,def_input_emu[ta].joycode);
   }
}

void save_emulator_joys(char *section)
{
   int ta;
   char joy_name[64];

   for(ta=0;ta<KB_EMU_DEF_COUNT;ta++){
      sprintf(joy_name,"%s",def_input_emu[ta].name);
      no_spaces(joy_name);
      raine_set_config_int(section,joy_name,def_input_emu[ta].joycode);
   }
}

void update_rjoy_list(void)
{
  int n,max;

  if(JoystickType){

    poll_joystick();
    rjoy[0]=			FALSE;

    rjoy[RJOY_1_UP]=	joy[0].stick[direction_stick[0]].axis[1].d1;
    rjoy[RJOY_1_DOWN]=	joy[0].stick[direction_stick[0]].axis[1].d2;
    rjoy[RJOY_1_LEFT]=	joy[0].stick[direction_stick[0]].axis[0].d1;
    rjoy[RJOY_1_RIGHT]=	joy[0].stick[direction_stick[0]].axis[0].d2;

    // The buttons were added in 3 times. To keep compatibility with older
    // config files, we'll keep the update order...

    for (n=0; n<8; n++)
      rjoy[RJOY_1_BUTTON1+n]=	joy[0].button[n].b;

    // Then 9..12
    if (joy[0].num_buttons > 8) {
      max = MIN(joy[0].num_buttons,12) - 9;
      for (n=0; n<=max; n++)
	rjoy[RJOY_1_BUTTON9+n]=	joy[0].button[n+8].b;

      // and finally 13 to 24
      if (joy[0].num_buttons > 12) {
	max = MIN(joy[0].num_buttons,24) - 13;
	for (n=0; n<=max; n++)
	  rjoy[RJOY_1_BUTTON13+n]=	joy[0].button[n+12].b;
      }
    }

    if (num_joysticks >= 2) {
      rjoy[RJOY_2_UP]=		joy[1].stick[0].axis[1].d1;
      rjoy[RJOY_2_DOWN]=	joy[1].stick[0].axis[1].d2;
      rjoy[RJOY_2_LEFT]=	joy[1].stick[0].axis[0].d1;
      rjoy[RJOY_2_RIGHT]=	joy[1].stick[0].axis[0].d2;

      for (n=0; n<8; n++)
	rjoy[RJOY_2_BUTTON1+n]=	joy[1].button[n].b;

      // Then 9..12
      if (joy[1].num_buttons > 8) {
	max = MIN(joy[1].num_buttons,12) - 9;
	for (n=0; n<=max; n++)
	  rjoy[RJOY_2_BUTTON9+n]=	joy[1].button[n+8].b;

	// and finally 13 to 24
	if (joy[1].num_buttons > 12) {
	  max = MIN(joy[1].num_buttons,24) - 13;
	  for (n=0; n<=max; n++)
	    rjoy[RJOY_2_BUTTON13+n]=	joy[1].button[n+12].b;
	}
      }

      if (num_joysticks >= 3) {
	rjoy[RJOY_3_UP]=		joy[2].stick[0].axis[1].d1;
	rjoy[RJOY_3_DOWN]=	joy[2].stick[0].axis[1].d2;
	rjoy[RJOY_3_LEFT]=	joy[2].stick[0].axis[0].d1;
	rjoy[RJOY_3_RIGHT]=	joy[2].stick[0].axis[0].d2;

	for (n=0; n<8; n++)
	  rjoy[RJOY_3_BUTTON1+n]=	joy[2].button[n].b;

	// Then 9..12
	if (joy[2].num_buttons > 8) {
	  max = MIN(joy[2].num_buttons,12) - 9;
	  for (n=0; n<=max; n++)
	    rjoy[RJOY_3_BUTTON9+n]=	joy[2].button[n+8].b;

	  // and finally 13 to 24
	  if (joy[2].num_buttons > 12) {
	    max = MIN(joy[2].num_buttons,24) - 13;
	    for (n=0; n<=max; n++)
	      rjoy[RJOY_3_BUTTON13+n]=	joy[2].button[n+12].b;
	  }
	}

	if (num_joysticks >= 4) {
	  rjoy[RJOY_4_UP]=		joy[3].stick[0].axis[1].d1;
	  rjoy[RJOY_4_DOWN]=	joy[3].stick[0].axis[1].d2;
	  rjoy[RJOY_4_LEFT]=	joy[3].stick[0].axis[0].d1;
	  rjoy[RJOY_4_RIGHT]=	joy[3].stick[0].axis[0].d2;

	  for (n=0; n<8; n++)
	    rjoy[RJOY_4_BUTTON1+n]=	joy[3].button[n].b;

	  // Then 9..12
	  if (joy[3].num_buttons > 8) {
	    max = MIN(joy[3].num_buttons,12) - 9;
	    for (n=0; n<=max; n++)
	      rjoy[RJOY_4_BUTTON9+n]=	joy[3].button[n+8].b;

	    // and finally 13 to 24
	    if (joy[3].num_buttons > 12) {
	      max = MIN(joy[3].num_buttons,24) - 13;
	      for (n=0; n<=max; n++)
		rjoy[RJOY_4_BUTTON13+n]=	joy[3].button[n+12].b;
	    }
	  }
	} // >= 4
      } // >= 3
    } // >= 2
  } // if (JoystickType)
}

static int pulse_time;

void set_pulse_time(int time)
{
  pulse_time = time;
}

// update_inputs():
// Goes through the input list setting/clearing the mapped RAM[] bits

void update_inputs(void)
{
   static UINT8 autofire_timer[6];

   UINT8  stick_logic[4];
   UINT8 *buffer;
   int    ta;
   int    input_valid;

   if (reading_demo) {
     write_demo_inputs();
     return;
   }

   stick_logic[0]=0x00;
   stick_logic[1]=0x00;
   stick_logic[2]=0x00;
   stick_logic[3]=0x00;

   // Autofire timer emulation

   for(ta=0;ta<6;ta++){
      autofire_timer[ta] ++;
      if(autofire_timer[ta] >= (ta<<1))
         autofire_timer[ta] = 0;
   }

   for(ta=0;ta<InputCount;ta++){

      if((key[InputList[ta].Key])||(rjoy[InputList[ta].Joy])){

      // Increment active timer

      InputList[ta].active_time ++;

      // Assume Input is valid

      input_valid=1;

      // Toggle Autofire settings

      if(InputList[ta].auto_rate){
         if(autofire_timer[InputList[ta].auto_rate] >= InputList[ta].auto_rate) input_valid=0;
      }

      // Disable the following situations:
      // 1) Impossible joystick inputs (joystick can be up or down, but not both)
      // 2) Coin inputs must last approx 250ms (prevent taito coin error)

      switch(InputList[ta].default_key){
         case KB_DEF_P1_UP:
            stick_logic[0] |= 0x01;
            if((stick_logic[0]&0x02)) input_valid=0;
         break;
         case KB_DEF_P1_DOWN:
            stick_logic[0] |= 0x02;
            if((stick_logic[0]&0x01)) input_valid=0;
         break;
         case KB_DEF_P1_LEFT:
            stick_logic[0] |= 0x04;
            if((stick_logic[0]&0x08)) input_valid=0;
         break;
         case KB_DEF_P1_RIGHT:
            stick_logic[0] |= 0x08;
            if((stick_logic[0]&0x04)) input_valid=0;
         break;
         case KB_DEF_P2_UP:
            stick_logic[1] |= 0x01;
            if((stick_logic[1]&0x02)) input_valid=0;
         break;
         case KB_DEF_P2_DOWN:
            stick_logic[1] |= 0x02;
            if((stick_logic[1]&0x01)) input_valid=0;
         break;
         case KB_DEF_P2_LEFT:
            stick_logic[1] |= 0x04;
            if((stick_logic[1]&0x08)) input_valid=0;
         break;
         case KB_DEF_P2_RIGHT:
            stick_logic[1] |= 0x08;
            if((stick_logic[1]&0x04)) input_valid=0;
         break;
         case KB_DEF_P3_UP:
            stick_logic[2] |= 0x01;
            if((stick_logic[2]&0x02)) input_valid=0;
         break;
         case KB_DEF_P3_DOWN:
            stick_logic[2] |= 0x02;
            if((stick_logic[2]&0x01)) input_valid=0;
         break;
         case KB_DEF_P3_LEFT:
            stick_logic[2] |= 0x04;
            if((stick_logic[2]&0x08)) input_valid=0;
         break;
         case KB_DEF_P3_RIGHT:
            stick_logic[2] |= 0x08;
            if((stick_logic[2]&0x04)) input_valid=0;
         break;
         case KB_DEF_P4_UP:
            stick_logic[3] |= 0x01;
            if((stick_logic[3]&0x02)) input_valid=0;
         break;
         case KB_DEF_P4_DOWN:
            stick_logic[3] |= 0x02;
            if((stick_logic[3]&0x01)) input_valid=0;
         break;
         case KB_DEF_P4_LEFT:
            stick_logic[3] |= 0x04;
            if((stick_logic[3]&0x08)) input_valid=0;
         break;
         case KB_DEF_P4_RIGHT:
            stick_logic[3] |= 0x08;
            if((stick_logic[3]&0x04)) input_valid=0;
         break;
         case KB_DEF_COIN1:
         case KB_DEF_COIN2:
         case KB_DEF_COIN3:
         case KB_DEF_COIN4:
            if(InputList[ta].active_time > pulse_time) input_valid=0;
         break;
         default:
         break;
      }

      }
      else{
         InputList[ta].active_time = 0;
         input_valid = 0;
      }


      if(InputList[ta].Address < 0x100)

         buffer = input_buffer;

      else

         buffer = RAM;

      buffer += InputList[ta].Address;


      if(input_valid ^ InputList[ta].high_bit)

         *buffer &= ~ InputList[ta].Bit;

      else

         *buffer |=   InputList[ta].Bit;

   }
   if (recording_demo)
     save_demo_inputs();
   update_gui_inputs();
}

/******************************************************************************/
/*                                                                            */
/*                              GLOBAL STRINGS                                */
/*                                                                            */
/******************************************************************************/

char MSG_COIN1[]        = "Coin A";
char MSG_COIN2[]        = "Coin B";
char MSG_COIN3[]        = "Coin C";
char MSG_COIN4[]        = "Coin D";

char MSG_TILT[]         = "Tilt";
char MSG_SERVICE[]      = "Service";
char MSG_TEST[]         = "Test";
char MSG_UNKNOWN[]      = "Unknown";
char MSG_YES[] = "Yes";
char MSG_NO[] = "No";
char MSG_FREE_PLAY[] = "Free Play";
char MSG_UNUSED[] = "Unused";
char MSG_COINAGE[] = "Coinage";

char MSG_P1_START[]     = "Player1 Start";

char MSG_P1_UP[]        = "Player1 Up";
char MSG_P1_DOWN[]      = "Player1 Down";
char MSG_P1_LEFT[]      = "Player1 Left";
char MSG_P1_RIGHT[]     = "Player1 Right";

char MSG_P1_B1[]        = "Player1 Button1";
char MSG_P1_B2[]        = "Player1 Button2";
char MSG_P1_B3[]        = "Player1 Button3";
char MSG_P1_B4[]        = "Player1 Button4";
char MSG_P1_B5[]        = "Player1 Button5";
char MSG_P1_B6[]        = "Player1 Button6";
char MSG_P1_B7[]        = "Player1 Button7";
char MSG_P1_B8[]        = "Player1 Button8";

char MSG_P2_START[]     = "Player2 Start";

char MSG_P2_UP[]        = "Player2 Up";
char MSG_P2_DOWN[]      = "Player2 Down";
char MSG_P2_LEFT[]      = "Player2 Left";
char MSG_P2_RIGHT[]     = "Player2 Right";

char MSG_P2_B1[]        = "Player2 Button1";
char MSG_P2_B2[]        = "Player2 Button2";
char MSG_P2_B3[]        = "Player2 Button3";
char MSG_P2_B4[]        = "Player2 Button4";
char MSG_P2_B5[]        = "Player2 Button5";
char MSG_P2_B6[]        = "Player2 Button6";
char MSG_P2_B7[]        = "Player2 Button7";
char MSG_P2_B8[]        = "Player2 Button8";

char MSG_P3_START[]     = "Player3 Start";

char MSG_P3_UP[]        = "Player3 Up";
char MSG_P3_DOWN[]      = "Player3 Down";
char MSG_P3_LEFT[]      = "Player3 Left";
char MSG_P3_RIGHT[]     = "Player3 Right";

char MSG_P3_B1[]        = "Player3 Button1";
char MSG_P3_B2[]        = "Player3 Button2";
char MSG_P3_B3[]        = "Player3 Button3";
char MSG_P3_B4[]        = "Player3 Button4";
char MSG_P3_B5[]        = "Player3 Button5";
char MSG_P3_B6[]        = "Player3 Button6";
char MSG_P3_B7[]        = "Player3 Button7";
char MSG_P3_B8[]        = "Player3 Button8";

char MSG_P4_START[]     = "Player4 Start";

char MSG_P4_UP[]        = "Player4 Up";
char MSG_P4_DOWN[]      = "Player4 Down";
char MSG_P4_LEFT[]      = "Player4 Left";
char MSG_P4_RIGHT[]     = "Player4 Right";

char MSG_P4_B1[]        = "Player4 Button1";
char MSG_P4_B2[]        = "Player4 Button2";
char MSG_P4_B3[]        = "Player4 Button3";
char MSG_P4_B4[]        = "Player4 Button4";
char MSG_P4_B5[]        = "Player4 Button5";
char MSG_P4_B6[]        = "Player4 Button6";
char MSG_P4_B7[]        = "Player4 Button7";
char MSG_P4_B8[]        = "Player4 Button8";

char MSG_FLIPPER_1_L[]  = "Flipper 1 Left";
char MSG_FLIPPER_1_R[]  = "Flipper 1 Right";
char MSG_FLIPPER_2_L[]  = "Flipper 2 Left";
char MSG_FLIPPER_2_R[]  = "Flipper 2 Right";
char MSG_TILT_L[]       = "Tilt Left";
char MSG_TILT_R[]       = "Tilt Right";
char MSG_B1_L[]         = "Button 1 Left";
char MSG_B1_R[]         = "Button 1 Right";
char MSG_B2_L[]         = "Button 2 Left";
char MSG_B2_R[]         = "Button 2 Right";

char MSG_P1_A[]         = "P1 A";    // Mahjong controls[]; at least in mahjong quest...
char MSG_P1_E[]         = "P1 E";
char MSG_P1_I[]         = "P1 I";
char MSG_P1_M[]         = "P1 M";
char MSG_P1_KAN[]       = "P1 Kan/Deal";

char MSG_P1_B[]         = "P1 B";
char MSG_P1_F[]         = "P1 F";
char MSG_P1_J[]         = "P1 J";
char MSG_P1_N[]         = "P1 N";
char MSG_P1_REACH[]     = "P1 Reach";

char MSG_P1_C[]         = "P1 C";
char MSG_P1_G[]         = "P1 G";
char MSG_P1_K[]         = "P1 K";
char MSG_P1_CHI[]       = "P1 Chi/Flip";
char MSG_P1_RON[]       = "P1 Ron";

char MSG_P1_D[]         = "P1 D";
char MSG_P1_H[]         = "P1 H";
char MSG_P1_L[]         = "P1 L";
char MSG_P1_PON[]       = "P1 Pon/Cancel";

char *MSG_P1_SERVICE_A  = "Service A";
char *MSG_P1_SERVICE_B  = "Service B";
char *MSG_P1_SERVICE_C  = "Service C";

/* DSW SECTION */

char MSG_DSWA_BIT1[]    = "DSW A Bit 1";        // Since most dsw info sheets
char MSG_DSWA_BIT2[]    = "DSW A Bit 2";        // number the bits 1-8, we will
char MSG_DSWA_BIT3[]    = "DSW A Bit 3";        // too, although 0-7 is a more
char MSG_DSWA_BIT4[]    = "DSW A Bit 4";        // correct syntax for progammers.
char MSG_DSWA_BIT5[]    = "DSW A Bit 5";
char MSG_DSWA_BIT6[]    = "DSW A Bit 6";
char MSG_DSWA_BIT7[]    = "DSW A Bit 7";
char MSG_DSWA_BIT8[]    = "DSW A Bit 8";

char MSG_DSWB_BIT1[]    = "DSW B Bit 1";
char MSG_DSWB_BIT2[]    = "DSW B Bit 2";
char MSG_DSWB_BIT3[]    = "DSW B Bit 3";
char MSG_DSWB_BIT4[]    = "DSW B Bit 4";
char MSG_DSWB_BIT5[]    = "DSW B Bit 5";
char MSG_DSWB_BIT6[]    = "DSW B Bit 6";
char MSG_DSWB_BIT7[]    = "DSW B Bit 7";
char MSG_DSWB_BIT8[]    = "DSW B Bit 8";

char MSG_DSWC_BIT1[]    = "DSW C Bit 1";
char MSG_DSWC_BIT2[]    = "DSW C Bit 2";
char MSG_DSWC_BIT3[]    = "DSW C Bit 3";
char MSG_DSWC_BIT4[]    = "DSW C Bit 4";
char MSG_DSWC_BIT5[]    = "DSW C Bit 5";
char MSG_DSWC_BIT6[]    = "DSW C Bit 6";
char MSG_DSWC_BIT7[]    = "DSW C Bit 7";
char MSG_DSWC_BIT8[]    = "DSW C Bit 8";

char MSG_COIN_SLOTS[]   = "Coin Slots";

char MSG_1COIN_1PLAY[]  = "1 Coin/1 Credit";
char MSG_1COIN_2PLAY[]  = "1 Coin/2 Credits";
char MSG_1COIN_3PLAY[]  = "1 Coin/3 Credits";
char MSG_1COIN_4PLAY[]  = "1 Coin/4 Credits";
char MSG_1COIN_5PLAY[]  = "1 Coin/5 Credits";
char MSG_1COIN_6PLAY[]  = "1 Coin/6 Credits";
char MSG_1COIN_7PLAY[]  = "1 Coin/7 Credits";
char MSG_1COIN_8PLAY[]  = "1 Coin/8 Credits";
char MSG_1COIN_9PLAY[]  = "1 Coin/9 Credits";

char MSG_2COIN_1PLAY[]  = "2 Coins/1 Credit";
char MSG_2COIN_2PLAY[]  = "2 Coins/2 Credits";
char MSG_2COIN_3PLAY[]  = "2 Coins/3 Credits";
char MSG_2COIN_4PLAY[]  = "2 Coins/4 Credits";
char MSG_2COIN_5PLAY[]  = "2 Coins/5 Credits";
char MSG_2COIN_6PLAY[]  = "2 Coins/6 Credits";
char MSG_2COIN_7PLAY[]  = "2 Coins/7 Credits";
char MSG_2COIN_8PLAY[]  = "2 Coins/8 Credits";

char MSG_3COIN_1PLAY[]  = "3 Coins/1 Credit";
char MSG_3COIN_2PLAY[]  = "3 Coins/2 Credits";
char MSG_3COIN_3PLAY[]  = "3 Coins/3 Credits";
char MSG_3COIN_4PLAY[]  = "3 Coins/4 Credits";
char MSG_3COIN_5PLAY[]  = "3 Coins/5 Credits";
char MSG_3COIN_6PLAY[]  = "3 Coins/6 Credits";
char MSG_3COIN_7PLAY[]  = "3 Coins/7 Credits";
char MSG_3COIN_8PLAY[]  = "3 Coins/8 Credits";

char MSG_4COIN_1PLAY[]  = "4 Coins/1 Credit";
char MSG_4COIN_2PLAY[]  = "4 Coins/2 Credits";
char MSG_4COIN_3PLAY[]  = "4 Coins/3 Credits";
char MSG_4COIN_4PLAY[]  = "4 Coins/4 Credits";
char MSG_4COIN_5PLAY[]  = "4 Coins/5 Credits";
char MSG_4COIN_6PLAY[]  = "4 Coins/6 Credits";
char MSG_4COIN_7PLAY[]  = "4 Coins/7 Credits";
char MSG_4COIN_8PLAY[]  = "4 Coins/8 Credits";

char MSG_5COIN_1PLAY[]  = "5 Coins/1 Credit";
char MSG_5COIN_2PLAY[]  = "5 Coins/2 Credits";
char MSG_5COIN_3PLAY[]  = "5 Coins/3 Credits";
char MSG_5COIN_4PLAY[]  = "5 Coins/4 Credits";

char MSG_6COIN_1PLAY[]  = "6 Coins/1 Credit";
char MSG_6COIN_2PLAY[]  = "6 Coins/2 Credits";
char MSG_6COIN_3PLAY[]  = "6 Coins/3 Credits";
char MSG_6COIN_4PLAY[]  = "6 Coins/4 Credits";

char MSG_7COIN_1PLAY[]  = "7 Coins/1 Credit";
char MSG_7COIN_2PLAY[]  = "7 Coins/2 Credits";
char MSG_7COIN_3PLAY[]  = "7 Coins/3 Credits";
char MSG_7COIN_4PLAY[]  = "7 Coins/4 Credits";

char MSG_8COIN_1PLAY[]  = "8 Coins/1 Credit";
char MSG_8COIN_2PLAY[]  = "8 Coins/2 Credits";
char MSG_8COIN_3PLAY[]  = "8 Coins/3 Credits";
char MSG_8COIN_4PLAY[]  = "8 Coins/4 Credits";

char MSG_9COIN_1PLAY[] = "9 Coins/1 Credit";

char MSG_OFF[]          = "Off";
char MSG_ON[]           = "On";

char MSG_SCREEN[]       = "Flip Screen";
char MSG_NORMAL[]       = "Normal";
char MSG_INVERT[]       = "Invert";

char MSG_TEST_MODE[]    = "Test Mode";

char MSG_DEMO_SOUND[]   = "Demo Sound";

char MSG_CONTINUE_PLAY[]= "Continue Play";
char MSG_EXTRA_LIFE[]   = "Extra Life";
char MSG_LIVES[]        = "Lives";

char MSG_CHEAT[]        = "Cheat";

char MSG_DIFFICULTY[]   = "Difficulty";
char MSG_EASY[]         = "Easy";
char MSG_VERY_EASY[]         = "Very Easy";
char MSG_HARD[]         = "Hard";
char MSG_VERY_HARD[]         = "Very Hard";
char MSG_HARDEST[]      = "Hardest";
char MSG_MEDIUM[]       = "Medium";

char MSG_CABINET[]      = "Cabinet";
char MSG_UPRIGHT[]      = "Upright";
char MSG_TABLE[]        = "Table";
char MSG_ALT[]        = "Alternate";

/******************************************************************************/
/*                                                                            */
/*                          KEYBOARD LED SUPPORT                              */
/*                                                                            */
/******************************************************************************/

// status of leds and old status (internal)

static UINT32 leds,oldleds;

#if 0
static UINT32 led_data;
#endif

// switch led: call this to turn a led on/off

void switch_led(int num, int on)
{
   static const UINT32 led_flags[3] =
   {
      KB_NUMLOCK_FLAG,
      KB_CAPSLOCK_FLAG,
      KB_SCROLOCK_FLAG
   };

   // Update Keyboard LEDS (support only 3)

   if(num<3){

      if(on&1)

	 leds |=  (led_flags[num]);

      else

	 leds &= ~(led_flags[num]);

   }
}

// update leds: call this once a frame

void update_leds(void)
{
   if(use_leds){

   if(leds!=oldleds){
      oldleds=leds;
      set_leds(leds);
   }

   }
}

// turn off all leds: call this when resetting game

void init_leds(void)
{
   if(use_leds){

      leds = 0;
      oldleds = 1;

   }
}

// forced update leds: call this when going back into game

void force_update_leds(void)
{
   if(use_leds)

      set_leds(leds);

}

/******************************************************************************/
static void frame_skip_up(void)
{
   if((display_cfg.frame_skip<9) && (display_cfg.frame_skip)){
      display_cfg.frame_skip++;
      print_ingame(120,"Drawing Every %1d Frames",display_cfg.frame_skip);
   }
}

static void frame_skip_down(void)
{
   if((display_cfg.frame_skip>1) && (display_cfg.frame_skip)){
      display_cfg.frame_skip--;
      if(display_cfg.frame_skip==1)
	 print_ingame(120,"Drawing All Frames");
      else
	 print_ingame(120,"Drawing Every %1d Frames",display_cfg.frame_skip);
   }
}

static void key_save_screen(void)
{
   raine_cfg.req_save_screen = 1;
}

static void key_pause_scroll_up(void)
{
   raine_cfg.req_pause_scroll |= 1;
}

static void key_pause_scroll_down(void)
{
   raine_cfg.req_pause_scroll |= 2;
}

static void key_pause_scroll_left(void)
{
   raine_cfg.req_pause_scroll |= 4;
}

static void key_pause_scroll_right(void)
{
   raine_cfg.req_pause_scroll |= 8;
}

typedef struct CORE_CTRL
{
   UINT16 key;
   void  (*proc)();
   UINT16 status; // The status is usefull to make the difference between
   // keys with only 1 action when you press them
   // and keys which work until you unpress them (key & 0x400)
} CORE_CTRL;

/*

ingame emulator controls

*/

extern void key_stop_emulation_esc(void);
extern void key_stop_emulation_tab(void);
extern void cpu_speed_up();
extern void cpu_slow_down();

static void save_video() {
  print_ingame(60,"starting recording video at %d fps",video_fps);
  recording_video = 1;
  recording = 1;
  monitoring = 0;
  last_video_frame = 0;
  // the recording is stopped in sound.c (set_sound_variables) when the game is paused
  // either by the pause key or by calling the gui
}

static struct CORE_CTRL core_ctrl_list[] =
{
   { KB_EMU_SCREENSHOT,        key_save_screen,        },
   { KB_EMU_INC_FRAMESKIP,     frame_skip_up,	       },
   { KB_EMU_DEC_FRAMESKIP,     frame_skip_down,        },
   { KB_EMU_INC_CPU_FRAMESKIP, cpu_speed_up,	       },
   { KB_EMU_DEC_CPU_FRAMESKIP, cpu_slow_down,	       },
   { KB_EMU_SAVE_GAME,	       GameSave,	       },
   { KB_EMU_SAVE_GAME_NAME,    GameSaveName,	       },
   { KB_EMU_SAVE_DEMO,	       GameSaveDemo,	       },
   { KB_EMU_SWITCH_SAVE_SLOT,  next_save_slot,	       },
   { KB_EMU_LOAD_GAME,	       GameLoad,	       },
   { KB_EMU_LOAD_GAME_NAME,    GameLoadName,	       },
   { KB_EMU_LOAD_DEMO,	       GameLoadDemo,	       },
   { KB_EMU_SWITCH_FPS,        switch_fps_mode,        },
   { KB_EMU_RESET_GAME,        reset_game_hardware,    },
   { KB_EMU_PAUSE_GAME,        key_pause_game,	       },
   { KB_EMU_STOP_EMULATION,    key_stop_emulation_esc, },
   { KB_EMU_OPEN_GUI,	       key_stop_emulation_tab, },
   { KB_EMU_SWITCH_MIXER,      switch_mixer, },
   { KB_EMU_SCREEN_UP	 | 0x4000, key_pause_scroll_up,    },
   { KB_EMU_SCREEN_DOWN  | 0x4000, key_pause_scroll_down,  },
   { KB_EMU_SCREEN_LEFT  | 0x4000, key_pause_scroll_left,  },
   { KB_EMU_SCREEN_RIGHT | 0x4000, key_pause_scroll_right, },
   { KB_EMU_SAVE_VIDEO, save_video, },
   { KB_EMU_REQ_FWD, key_pause_fwd, },
   { 0, 		       NULL,		       },
};

/*

pause mode emulator controls

*/
void init_gui_inputs(void)
{
  // pause key : normal mapping
  CORE_CTRL *ctrl_list = core_ctrl_list;
   while(ctrl_list->proc){

      if(ctrl_list->key == KB_EMU_PAUSE_GAME)

	ctrl_list->proc = &key_pause_game;
      ctrl_list++;
   }
}


static void parse_control_list(CORE_CTRL *ctrl_list)
{
  // This function parses the CORE_CTRL list, which is the emu inputs.
  // Contrary to the normal game inputs, this function takes care about
  // modifiers (ctrl, shift, alt, left & right win, and menu).
  DEF_INPUT *inp;
   while(ctrl_list->proc){
      inp = &def_input_emu[ctrl_list->key & 0xFF];
      if(ctrl_list->key & 0x4000){ // ignore status code

	 if((key[inp->scancode & 0xff] && ((key_shifts & 0x3f) == inp->scancode>>8)) ||
	   (rjoy[inp->joycode])){
	       ctrl_list->proc();
	 }

      }
      else{

	 if((key[inp->scancode & 0xff] && ((key_shifts & 0x3f) == inp->scancode>>8)) ||
	   (rjoy[inp->joycode])){
	    if(!ctrl_list->status){
	       ctrl_list->status = 1;
	       ctrl_list->proc();
	    }
	 }
	 else{
	    ctrl_list->status = 0;
	 }

      }

      ctrl_list++;

   }

}


void update_gui_inputs(void)
{
   parse_control_list(core_ctrl_list);

   check_layer_switches();
}

void raine_set_scancode(int index, int code) {
  def_input[index].scancode = code;
}

void raine_set_emu_scancode(int index, int code) {
  def_input_emu[index].scancode = code;
}

char* raine_get_key_name(int index) {
  return def_input[index].name;
}

int raine_get_scancode(int index) {
  return def_input[index].scancode;
}

char* raine_get_emu_key_name(int index) {
  return def_input_emu[index].name;
}

int raine_get_emu_scancode(int index) {
  return def_input_emu[index].scancode;
}

void raine_increase_auto_rate(int index) {
  if (index < InputCount) {
    InputList[index].auto_rate ++;
    if(InputList[index].auto_rate>5) InputList[index].auto_rate = 0;
  }
}

char *raine_auto_name(int index)
{
   switch(InputList[index].auto_rate){
   case 1:  return "1 (30 fps)";
   case 2:  return "2 (15 fps)";
   case 3:  return "3 (10 fps)";
   case 4:  return "4 (07 fps)";
   case 5:  return "5 (06 fps)";
   default: return "Off";
   }
}

char* raine_input_name(int index) {
  return InputList[index].InputName;
}

int raine_get_input_count() {
  return InputCount;
}

void raine_set_key(int index, int key) {
  InputList[index].Key = key;
}

int raine_get_key(int index) {
  return InputList[index].Key;
}

/* Allegro specific code :
   we can't map the joystick anymore to just 1 byte.
   We keep this code only in allegro for now (old compatibility) */

void raine_set_joycode(int index, int code) {
  def_input[index].joycode = code;
}

void raine_set_emu_joycode(int index, int code) {
  def_input_emu[index].joycode = code;
}

int raine_get_joycode(int index) {
  return def_input[index].joycode;
}

int raine_get_emu_joycode(int index) {
  return def_input_emu[index].joycode;
}

void raine_set_input_joycode(int index, int code) {
  InputList[index].Joy = code;
}

int raine_get_input_joycode(int index) {
  return   InputList[index].Joy;
}
