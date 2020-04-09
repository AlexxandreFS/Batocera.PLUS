
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                       RAINE CONTROL / INPUT / LED                          */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

extern int GameMouse;

/******************************************************************************/

#define BIT_ACTIVE_0 (0)
#define BIT_ACTIVE_1 (1)
#define INPUT_INCLUDE (2)

/******************************************************************************/
/*                                                                            */
/*                           DEFAULT KEY SETTINGS                             */
/*                                                                            */
/******************************************************************************/

enum {
   KB_DEF_COIN1 = 0x100,	// Coin A
   KB_DEF_COIN2,		// Coin B
   KB_DEF_COIN3,		// Coin C
   KB_DEF_COIN4,		// Coin D

   KB_DEF_TILT,			// Tilt
   KB_DEF_SERVICE,		// Service
   KB_DEF_TEST,			// Test

   KB_DEF_P1_START,		// P1 Start

   KB_DEF_P1_UP,		// P1 Joystick
   KB_DEF_P1_DOWN,
   KB_DEF_P1_LEFT,
   KB_DEF_P1_RIGHT,

   KB_DEF_P1_B1,		// 8 Buttons
   KB_DEF_P1_B2,
   KB_DEF_P1_B3,
   KB_DEF_P1_B4,
   KB_DEF_P1_B5,
   KB_DEF_P1_B6,
   KB_DEF_P1_B7,
   KB_DEF_P1_B8,

   KB_DEF_P2_START,		// P2 Start
   KB_DEF_P2_UP,		// P2 Joystick
   KB_DEF_P2_DOWN,
   KB_DEF_P2_LEFT,
   KB_DEF_P2_RIGHT,

   KB_DEF_P2_B1,		// 8 Buttons
   KB_DEF_P2_B2,
   KB_DEF_P2_B3,
   KB_DEF_P2_B4,
   KB_DEF_P2_B5,
   KB_DEF_P2_B6,
   KB_DEF_P2_B7,
   KB_DEF_P2_B8,

   KB_DEF_P3_START,		// P3 Start

   KB_DEF_P3_UP,		// P3 Joystick
   KB_DEF_P3_DOWN,
   KB_DEF_P3_LEFT,
   KB_DEF_P3_RIGHT,

   KB_DEF_P3_B1,		// 8 Buttons
   KB_DEF_P3_B2,
   KB_DEF_P3_B3,
   KB_DEF_P3_B4,
   KB_DEF_P3_B5,
   KB_DEF_P3_B6,
   KB_DEF_P3_B7,
   KB_DEF_P3_B8,

   KB_DEF_P4_START,		// P4 Start

   KB_DEF_P4_UP,		// P4 Joystick
   KB_DEF_P4_DOWN,
   KB_DEF_P4_LEFT,
   KB_DEF_P4_RIGHT,

   KB_DEF_P4_B1,		// 8 Buttons
   KB_DEF_P4_B2,
   KB_DEF_P4_B3,
   KB_DEF_P4_B4,
   KB_DEF_P4_B5,
   KB_DEF_P4_B6,
   KB_DEF_P4_B7,
   KB_DEF_P4_B8,

   KB_DEF_FLIPPER_1_L,		// Pinball Controls
   KB_DEF_FLIPPER_1_R,
   KB_DEF_FLIPPER_2_L,
   KB_DEF_FLIPPER_2_R,
   KB_DEF_TILT_L,
   KB_DEF_TILT_R,
   KB_DEF_B1_L,
   KB_DEF_B1_R,

   KB_DEF_P1_A,    // Mahjong controls, at least in mahjong quest...
   KB_DEF_P1_E,
   KB_DEF_P1_I,
   KB_DEF_P1_M,
   KB_DEF_P1_KAN,

   KB_DEF_P1_B,
   KB_DEF_P1_F,
   KB_DEF_P1_J,
   KB_DEF_P1_N,
   KB_DEF_P1_REACH,

   KB_DEF_P1_C,
   KB_DEF_P1_G,
   KB_DEF_P1_K,
   KB_DEF_P1_CHI,
   KB_DEF_P1_RON,

   KB_DEF_P1_D,
   KB_DEF_P1_H,
   KB_DEF_P1_L,
   KB_DEF_P1_PON,

   KB_DEF_SERVICE_A,
   KB_DEF_SERVICE_B,
   KB_DEF_SERVICE_C,

   KB_DEF_B2_L,
   KB_DEF_B2_R,

#ifndef RAINE_DOS
   // The dos inputs can't handle combinations, all inputs which are not pressed
   // are cleared at each frame, so all the combinations are cleared and no
   // button can be pressed in these conditions ! In other words : this code
   // sucks !
   KB_DEF_P1_B1B2,
   KB_DEF_P1_B3B4,
   KB_DEF_P1_B2B3,
   KB_DEF_P1_B1B2B3,
   KB_DEF_P1_B2B3B4,

   KB_DEF_P2_B1B2,
   KB_DEF_P2_B3B4,
   KB_DEF_P2_B2B3,
   KB_DEF_P2_B1B2B3,
   KB_DEF_P2_B2B3B4,
   KB_DEF_P1_B4B5B6,
#endif

   KB_DEF_NEXT_GAME,
   KB_DEF_PREV_GAME,

   // These 2 are special and should not be displayed in the dialogs
   KB_DEF_UNKNOWN,
   KB_DEF_SPECIAL,
   KB_DEF_UNUSED,

   KB_DEF_END,
};

#define KB_DEF_COUNT	(KB_DEF_END-0x100)

extern UINT32 p1_trackball_x; // Mouse x,y
extern UINT32 p1_trackball_y;

/******************************************************************************/

extern int JoystickType;		// Type of Joystick chosen (see raine.cfg)
extern volatile int *MouseB;
extern int direction_stick[4]; // 4 joysticks max !
extern int use_custom_keys;
extern int joy_use_custom_keys;
void set_pulse_time(int time);

extern void (*GetMouseMickeys)(int *mx,int *my);

void init_inputs(void);
void release_inputs(void);

extern UINT8 input_buffer[0x100];

void reset_game_keys(void);
void joy_reset_game_keys(void);

void load_game_keys(char *section);
void save_game_keys(char *section);
#ifndef SDL
void load_game_joys(char *section);
void save_game_joys(char *section);
#endif

void load_default_keys(char *section);
void save_default_keys(char *section);
#ifndef SDL
void load_default_joys(char *section);
void save_default_joys(char *section);
#endif

void load_emulator_keys(char *section);
void save_emulator_keys(char *section);
void load_emulator_joys(char *section);
void save_emulator_joys(char *section);

void update_gui_inputs(void);
void init_gui_inputs_paused(void);
void init_gui_inputs(void);

// ProcessInputs():
// Goes through the input list setting/clearing the mapped RAM[] bits

void update_rjoy_list(void);

void update_inputs(void);

extern int use_leds;

void switch_led(int num, int on);
void update_leds(void);
void init_leds(void);
void force_update_leds(void);

extern char MSG_COIN1[];
extern char MSG_COIN2[];
extern char MSG_COIN3[];
extern char MSG_COIN4[];

extern char MSG_TILT[];
extern char MSG_SERVICE[];
extern char MSG_TEST[];
extern char MSG_UNKNOWN[];
extern char MSG_UNUSED[];
extern char MSG_YES[];
extern char MSG_NO[];
extern char MSG_FREE_PLAY[];
extern char MSG_UNUSED[];
extern char MSG_COINAGE[];

extern char MSG_P1_START[];

extern char MSG_P1_UP[];
extern char MSG_P1_DOWN[];
extern char MSG_P1_LEFT[];
extern char MSG_P1_RIGHT[];

extern char MSG_P1_B1[];
extern char MSG_P1_B2[];
extern char MSG_P1_B3[];
extern char MSG_P1_B4[];
extern char MSG_P1_B5[];
extern char MSG_P1_B6[];
extern char MSG_P1_B7[];
extern char MSG_P1_B8[];

extern char MSG_P1_B1B2[];
extern char MSG_P1_B1B2B3[];
extern char MSG_P1_B4B5B6[];
extern char MSG_P1_AB[];

extern char MSG_P1_A[];    // Mahjong controls[]; at least in mahjong quest...
extern char MSG_P1_E[];
extern char MSG_P1_I[];
extern char MSG_P1_M[];
extern char MSG_P1_KAN[];

extern char MSG_P1_B[];
extern char MSG_P1_F[];
extern char MSG_P1_J[];
extern char MSG_P1_N[];
extern char MSG_P1_REACH[];

extern char MSG_P1_C[];
extern char MSG_P1_G[];
extern char MSG_P1_K[];
extern char MSG_P1_CHI[];
extern char MSG_P1_RON[];

extern char MSG_P1_D[];
extern char MSG_P1_H[];
extern char MSG_P1_L[];
extern char MSG_P1_PON[];

extern char MSG_P2_START[];

extern char MSG_P2_UP[];
extern char MSG_P2_DOWN[];
extern char MSG_P2_LEFT[];
extern char MSG_P2_RIGHT[];

extern char MSG_P2_B1[];
extern char MSG_P2_B2[];
extern char MSG_P2_B3[];
extern char MSG_P2_B4[];
extern char MSG_P2_B5[];
extern char MSG_P2_B6[];
extern char MSG_P2_B7[];
extern char MSG_P2_B8[];

extern char MSG_P2_B1B2[];
extern char MSG_P2_B1B2B3[];

extern char MSG_P3_START[];

extern char MSG_P3_UP[];
extern char MSG_P3_DOWN[];
extern char MSG_P3_LEFT[];
extern char MSG_P3_RIGHT[];

extern char MSG_P3_B1[];
extern char MSG_P3_B2[];
extern char MSG_P3_B3[];
extern char MSG_P3_B4[];
extern char MSG_P3_B5[];
extern char MSG_P3_B6[];
extern char MSG_P3_B7[];
extern char MSG_P3_B8[];

extern char MSG_P4_START[];

extern char MSG_P4_UP[];
extern char MSG_P4_DOWN[];
extern char MSG_P4_LEFT[];
extern char MSG_P4_RIGHT[];

extern char MSG_P4_B1[];
extern char MSG_P4_B2[];
extern char MSG_P4_B3[];
extern char MSG_P4_B4[];
extern char MSG_P4_B5[];
extern char MSG_P4_B6[];
extern char MSG_P4_B7[];
extern char MSG_P4_B8[];

extern char MSG_FLIPPER_1_L[];
extern char MSG_FLIPPER_1_R[];
extern char MSG_FLIPPER_2_L[];
extern char MSG_FLIPPER_2_R[];
extern char MSG_TILT_L[];
extern char MSG_TILT_R[];
extern char MSG_B1_L[];
extern char MSG_B1_R[];
extern char MSG_B2_L[];
extern char MSG_B2_R[];

extern char MSG_DSWA_BIT1[];
extern char MSG_DSWA_BIT2[];
extern char MSG_DSWA_BIT3[];
extern char MSG_DSWA_BIT4[];
extern char MSG_DSWA_BIT5[];
extern char MSG_DSWA_BIT6[];
extern char MSG_DSWA_BIT7[];
extern char MSG_DSWA_BIT8[];

extern char MSG_DSWB_BIT1[];
extern char MSG_DSWB_BIT2[];
extern char MSG_DSWB_BIT3[];
extern char MSG_DSWB_BIT4[];
extern char MSG_DSWB_BIT5[];
extern char MSG_DSWB_BIT6[];
extern char MSG_DSWB_BIT7[];
extern char MSG_DSWB_BIT8[];

extern char MSG_DSWC_BIT1[];
extern char MSG_DSWC_BIT2[];
extern char MSG_DSWC_BIT3[];
extern char MSG_DSWC_BIT4[];
extern char MSG_DSWC_BIT5[];
extern char MSG_DSWC_BIT6[];
extern char MSG_DSWC_BIT7[];
extern char MSG_DSWC_BIT8[];

extern char MSG_COIN_SLOTS[];

extern char MSG_1COIN_1PLAY[];
extern char MSG_1COIN_2PLAY[];
extern char MSG_1COIN_3PLAY[];
extern char MSG_1COIN_4PLAY[];
extern char MSG_1COIN_5PLAY[];
extern char MSG_1COIN_6PLAY[];
extern char MSG_1COIN_7PLAY[];
extern char MSG_1COIN_8PLAY[];
extern char MSG_1COIN_9PLAY[];

extern char MSG_2COIN_1PLAY[];
extern char MSG_2COIN_2PLAY[];
extern char MSG_2COIN_3PLAY[];
extern char MSG_2COIN_4PLAY[];
extern char MSG_2COIN_5PLAY[];
extern char MSG_2COIN_6PLAY[];
extern char MSG_2COIN_7PLAY[];
extern char MSG_2COIN_8PLAY[];

extern char MSG_3COIN_1PLAY[];
extern char MSG_3COIN_2PLAY[];
extern char MSG_3COIN_3PLAY[];
extern char MSG_3COIN_4PLAY[];
extern char MSG_3COIN_5PLAY[];
extern char MSG_3COIN_6PLAY[];
extern char MSG_3COIN_7PLAY[];
extern char MSG_3COIN_8PLAY[];

extern char MSG_4COIN_1PLAY[];
extern char MSG_4COIN_2PLAY[];
extern char MSG_4COIN_3PLAY[];
extern char MSG_4COIN_4PLAY[];
extern char MSG_4COIN_5PLAY[];
extern char MSG_4COIN_6PLAY[];
extern char MSG_4COIN_7PLAY[];
extern char MSG_4COIN_8PLAY[];

extern char MSG_5COIN_1PLAY[];
extern char MSG_5COIN_2PLAY[];
extern char MSG_5COIN_3PLAY[];
extern char MSG_5COIN_4PLAY[];

extern char MSG_6COIN_1PLAY[];
extern char MSG_6COIN_2PLAY[];
extern char MSG_6COIN_3PLAY[];
extern char MSG_6COIN_4PLAY[];

extern char MSG_7COIN_1PLAY[];
extern char MSG_7COIN_2PLAY[];
extern char MSG_7COIN_3PLAY[];
extern char MSG_7COIN_4PLAY[];

extern char MSG_8COIN_1PLAY[];
extern char MSG_8COIN_2PLAY[];
extern char MSG_8COIN_3PLAY[];
extern char MSG_8COIN_4PLAY[];

extern char MSG_9COIN_1PLAY[];

extern char MSG_OFF[];
extern char MSG_ON[];

extern char MSG_SCREEN[];
extern char MSG_NORMAL[];
extern char MSG_INVERT[];

extern char MSG_TEST_MODE[];

extern char MSG_DEMO_SOUND[];

extern char MSG_CONTINUE_PLAY[];
extern char MSG_EXTRA_LIFE[];
extern char MSG_LIVES[];

extern char MSG_CHEAT[];

extern char MSG_DIFFICULTY[];
extern char MSG_EASY[];
extern char MSG_VERY_EASY[];
extern char MSG_HARD[];
extern char MSG_VERY_HARD[];
extern char MSG_HARDEST[];
extern char MSG_MEDIUM[];
extern char MSG_CABINET[];
extern char MSG_UPRIGHT[];
extern char MSG_TABLE[];
extern char MSG_ALT[];

#define DSW_REGION( region ) \
{ "\x01region", region, 0 }

#define DSW_DEFAULT_REGION \
{ "\x01region", 255, 255 }

#define DSW_TEST_DSW(dsw,mask,value) \
{ "\x01""dsw:"#dsw, mask, value }

#define DSW_SCREEN( normal, invert)                  \
   { MSG_SCREEN,              normal|invert, 0x02 }, \
   { MSG_NORMAL,              normal },              \
   { MSG_INVERT,              invert }

#define DSW_DEMO_SOUND( on, off )         \
   { MSG_DEMO_SOUND,      on|off, 0x02 }, \
   { MSG_ON,              on },           \
   { MSG_OFF,             off }

#define DSW_TEST_MODE( on, off )         \
   { MSG_TEST_MODE,      on|off, 0x02 }, \
   { MSG_ON,              on },          \
   { MSG_OFF,             off }

#define DSW_SERVICE( on, off )         \
   { MSG_SERVICE,      off|on, 0x02 }, \
   { MSG_ON,              on },        \
   { MSG_OFF,             off }

#define DSW_CONTINUE_PLAY( on, off )       \
   { MSG_CONTINUE_PLAY,    on|off, 0x02 }, \
   { MSG_ON,              on },            \
   { MSG_OFF,             off }

#define DSW_CABINET( upright, table )       \
   { MSG_CABINET,    upright|table, 0x02 }, \
   { MSG_UPRIGHT,     upright },            \
   { MSG_TABLE,      table }                \

#define DSW_UNUSED( on, off )         \
   { MSG_UNUSED,      off|on, 0x02 }, \
   { MSG_ON,              on },       \
   { MSG_OFF,             off }

#define DSW_ON_OFF( msg, on, off )          \
   { msg,      (off ? off : on), 0x02 },     \
   { MSG_ON,              on },        \
   { MSG_OFF,             off }

#define INCL_INP( other ) \
   { 1, (char*)input_##other, 0, 0, INPUT_INCLUDE }
#define INP0( input, adr, mask ) \
   { KB_DEF_##input, MSG_##input, adr, mask, BIT_ACTIVE_0 }
#define INP1( input, adr, mask ) \
   { KB_DEF_##input, MSG_##input, adr, mask, BIT_ACTIVE_1 }

#define END_INPUT \
   { 0, NULL, 0, 0, 0 },

void raine_set_scancode(int index, int code);
void raine_set_emu_scancode(int index, int code);
char* raine_get_key_name(int index);
int raine_get_scancode(int index);
char* raine_get_emu_key_name(int index);
int raine_get_emu_scancode(int index);
int raine_get_emu_nb_ctrl();

void raine_increase_auto_rate(int index);
char* raine_input_name(int index);
char *raine_auto_name(int index);
int raine_get_input_count();

void raine_set_key(int index, int key);
int raine_get_key(int index);

#ifdef __cplusplus
}
#endif
