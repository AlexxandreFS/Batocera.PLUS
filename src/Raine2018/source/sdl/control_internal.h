#ifndef __CONTROL_INTERNAL
#define __CONTROL_INTERNAL

/* These types/variables are only needed by the gui to be able to change
 * the inputs, no game driver should need those */

#ifdef __cplusplus
extern "C" {
#endif

#include "deftypes.h"

/* DEF_INPUT_EMU : these one on the other hand are gui only, which means that
 * one key press makes an action to happen immediately, we don't care if the
 * key stays down or not, and there are no custom controls for this ->
 * we can add the function to execute in the struct */
typedef struct DEF_INPUT_EMU
{
   UINT32 scancode;
   UINT32 joycode;
   char *name;
   void  (*proc)();
} DEF_INPUT_EMU;

/* This is the "direct mapping" of the joystick or digital, that is moved or
 * not moved, nothing in the middle. For "analog" mode, we'll add something
 * different (new type of input probably). So the weird way to handle joystick
 * axes... */
#define JOY(NUM_JOY, AXE, BUTTON, HAT_NUM) \
  (NUM_JOY) | (AXE<<8) | ((BUTTON)<<16) | ((HAT_NUM)<<24)
/* Notice : which must start at 1 otherwise joystick1 left is mapeed to 0
 * which is equivalent to no mapping.
 * Same thing for button number which must start at 1
 * and probably the hat number too (not tested yet !) */

#define AXIS_LEFT(NUM) (NUM)*2
#define AXIS_RIGHT(NUM) ((NUM)*2+1)

   /* Use this way : HAT(1,SDL_HAT_UP)
      the positions are a bit mask in sdl from 0 to 8, it should not change
      soon, so it uses the first 4 bits in this byte. The upper 4 bits are the
      hat number but I don't expect to have so many hats one day ! */
#define HAT(NUM,POS) ((NUM<<4)|pos)

#define MAX_AXIS 16
#define MAX_JOY 16
#define MAX_HAT 16

extern SDL_Joystick *joy[MAX_JOY];
extern char* joy_name[MAX_JOY];
extern int bad_axes[MAX_JOY*MAX_AXIS];
extern char analog_name[80]; // analog device saved by name because its index
// can change if it's pluged differently

extern int analog_num,analog_stick,analog_minx,analog_maxx,analog_miny,
  analog_maxy,analog_normx,analog_normy, app_state, pause_on_focus;
// analog_normx & normy are the normalized position of the stick after
// calibration (between -16384 and +16384 inclusive).

extern struct DEF_INPUT_EMU def_input_emu[];

// allows drivers to register their own emu keys
void register_driver_emu_keys(struct DEF_INPUT_EMU *list, int nb);
void unregister_driver_emu_keys();

void toggle_fullscreen();

/* Active inputs (allows to switch from default to custom inputs/game) */
typedef struct INPUT
{
   UINT16 Key;			// keyboard code for this input
   UINT32 Joy;			// joystick code for this input
   UINT32 mousebtn;
   char *InputName;		// input name string
   UINT32 Address;		// address in RAM[] for this input
   UINT8 Bit;			// bit mask for this input
   UINT8 high_bit;		// input is acitve high or active low
   UINT16 default_key;		// index in default controls array (to retrieve defaults)
   int auto_rate;		// autofire frame rate
   UINT32 active_time;		// frames since the input became active (used for coin time)
   int link; // linked input : allows to create another input for autofire
} INPUT;

enum { // categories of inputs
    P1S = 0x10, // start
    P1D,  // p1 directions
    P1B, // buttons
    P1C, // combinations
    P2S = 0x20,
    P2D,
    P2B, // buttons
    P2C,
    P3S = 0x30,
    P3D,
    P3B, // buttons
    P3C,
    P4S = 0x40,
    P4D,
    P4B, // buttons
    P4C, // comb
    SYS = 0x100
};

#define MAX_INPUTS 64

extern struct INPUT InputList[MAX_INPUTS];	// Max 64 control inputs in a game

extern int InputCount;			// Number of Inputs in InputList

/* DEF_INPUT : ingame controls, these controls are index by a KB_xxx const
 * and make a bitmask to change usually. Also you can have the default inputs
 * or the custom inputs for these */
typedef struct DEF_INPUT
{
   UINT32 scancode;
   UINT32 joycode;
   UINT32 mousebtn;
   char *name;
   UINT32 categ;
} DEF_INPUT;

extern struct DEF_INPUT def_input[KB_DEF_COUNT];

void inputs_preinit();
void inputs_done();
int get_axis_from_hat(int which, int hat);
int get_console_key();
int has_input(int inp);

#ifdef __cplusplus
}
#endif

#endif

