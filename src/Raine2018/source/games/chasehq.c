#define DRV_DEF_SOUND taito_ym2610b_sound
/******************************************************************************/
/*                                                                            */
/*                    CHASE HQ (C) 1988 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc150rod.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "zoom/16x16.h"		// 16x8 zoomed sprite routines
#ifdef SDL
#include "sdl/control_internal.h" // analog support
#endif


static struct ROM_INFO rom_chasehq[] =
{
   {  "b52-28.4", 0x00080000, 0x963bc82b, 0, 0, 0, },
   {  "b52-29.27", 0x00080000, 0x8366d27c, 0, 0, 0, },
   {  "b52-30.4", 0x00080000, 0x1b8cc647, 0, 0, 0, },
   {  "b52-31.6", 0x00080000, 0xf1998e20, 0, 0, 0, },
   {  "b52-32.8", 0x00080000, 0x8620780c, 0, 0, 0, },
   {  "b52-33.10", 0x00080000, 0xe6f4b8c4, 0, 0, 0, },
   {  "b52-34.5", 0x00080000, 0x7d8dce36, 0, 0, 0, },
   {  "b52-35.7", 0x00080000, 0x78eeec0d, 0, 0, 0, },
   {  "b52-36.9", 0x00080000, 0x61e89e91, 0, 0, 0, },
   {  "b52-37.11", 0x00080000, 0xf02e47b9, 0, 0, 0, },
   {  "b52-38.34", 0x00080000, 0x5b5bf7f6, 0, 0, 0, },
   {   "b52-50.66", 0x00010000, 0xc189781c, 0, 0, 0, },
   {   "b52-51.65", 0x00010000, 0x30cc1f79, 0, 0, 0, },
   {  "b52-129.30", 0x00020000, 0x0eaebc08, 0, 0, 0, },
   {  "b52-130.36", 0x00020000, 0x4e7beb46, 0, 0, 0, },
   {  "b52-131.37", 0x00020000, 0xaa945d83, 0, 0, 0, },
   {  "b52-132.39", 0x00010000, 0xa2f54789, 0, 0, 0, },
   {  "b52-133.55", 0x00010000, 0x12232f95, 0, 0, 0, },
   {  "b52-136.29", 0x00020000, 0x2f414df0, 0, 0, 0, },
   {  "b52-137.51", 0x00010000, 0x37abb74a, 0, 0, 0, },
   { "b52-113.73", 0x00080000, 0x2c6a3a05, 0, 0, 0, },
   { "b52-114.72", 0x00080000, 0x3a73d6b1, 0, 0, 0, },
   { "b52-115.71", 0x00080000, 0x4e117e93, 0, 0, 0, },
   { "b52-116.70", 0x00080000, 0xad46983c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_chasehq[] =
{
   INP1( COIN1, 0x022804, 0x04 ),
   INP1( COIN2, 0x022804, 0x08 ),
   INP0( TILT, 0x022806, 0x02 ),
   INP0( SERVICE, 0x022804, 0x10 ),
   INP0( P1_START, 0x022806, 0x08 ),

// Fake wheel addresses, used for keyboard support
   INP0( P1_LEFT, 0x022818, 0x7F ),
   INP0( P1_RIGHT, 0x02281A, 0x7F ),

// Fake pedal addresses, used for keyboard support - Unsure if adresses are really unused
   { KB_DEF_P1_B1,        "Accelerator",           0x022807, 0xFF, BIT_ACTIVE_1 },
   { KB_DEF_P1_B2,        "Brake",                 0x022809, 0xFF, BIT_ACTIVE_1 },

   { KB_DEF_P1_B3,        "Gear Change",           0x022820, 0xFF, BIT_ACTIVE_1 },
   { KB_DEF_P1_B4,        "Turbo",                 0x022806, 0x01, BIT_ACTIVE_0 },

   END_INPUT
};

static struct DSW_DATA dsw_data_chase_hq_0[] =
{
/* User is not allowed to select cabinet type.
   Dipswitches are locked at the only setting with PC compatible controls.
*/

   // Notice : in the sdl version, you can't assign a value to an unmapped dsw
   // because some games share dsw with controls, so any value writen to a dsw
   // is now masked with the declared mask. Hence we declare the right dsw here
   // with only 1 possible value
   { _("Cabinet Type"),          0x03, 0x01 },	// Motor Enable (?)
//   { _("Upright/Steering Lock"), 0x03},
//   { _("Upright No Steer Lock"),  0x02},
   { _("Full Throttle Convrt"),  0x01},
//   { _("Full Thrtle Dlx Cnvrt"), 0x00},
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_input_fake[] =
{
   { _("Gear Mode"),             0x01, 0x02 },
   { _("Low while pressed"),     0x01},
   { _("Toggle"),                0x00},
#ifndef SDL
   { _("Wheel"),                 0x02, 0x02 },
   { _("Keyboard/Digital"),      0x02},
   { _("PC Steering Wheel"),     0x00},
   { _("Accelerator"),           0x04, 0x02 },
   { _("Keyboard/Digital"),      0x04},
   { _("PC Pedal (analog)"),     0x00},
   { _("Brake"),                 0x08, 0x02 },
   { _("Keyboard/Digital"),      0x08},
   { _("PC Pedal (analog)"),     0x00},
#endif
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_chase_hq_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Start Time"),            0x0C, 0x04 },
   { "60",                    0x0C},
   { "70",                    0x08},
   { "65",                    0x04},
   { "55",                    0x00},
   { _("Start Turbos"),          0x10, 0x02 },
   { "3",                     0x10},
   { "5",                     0x00},
   { _("Clear Damage on Cont."), 0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   DSW_CONTINUE_PLAY( 0x80, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_chasehq[] =
{
   { 0x022800, 0xFD, dsw_data_chase_hq_0 },
   { 0x022802, 0xFF, dsw_data_chase_hq_1 },
   { 0x022801, 0xFE, dsw_input_fake },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_chasehqj[] =
{
   {  "b52-28.4", 0x00080000, 0x963bc82b, 0, 0, 0, },
   {  "b52-29.27", 0x00080000, 0x8366d27c, 0, 0, 0, },
   {  "b52-30.4", 0x00080000, 0x1b8cc647, 0, 0, 0, },
   {  "b52-31.6", 0x00080000, 0xf1998e20, 0, 0, 0, },
   {  "b52-32.8", 0x00080000, 0x8620780c, 0, 0, 0, },
   {  "b52-33.10", 0x00080000, 0xe6f4b8c4, 0, 0, 0, },
   {  "b52-34.5", 0x00080000, 0x7d8dce36, 0, 0, 0, },
   {  "b52-35.7", 0x00080000, 0x78eeec0d, 0, 0, 0, },
   {  "b52-36.9", 0x00080000, 0x61e89e91, 0, 0, 0, },
   {  "b52-37.11", 0x00080000, 0xf02e47b9, 0, 0, 0, },
   {  "b52-38.34", 0x00080000, 0x5b5bf7f6, 0, 0, 0, },
   {   "b52-50.66", 0x00010000, 0xc189781c, 0, 0, 0, },
   {   "b52-51.65", 0x00010000, 0x30cc1f79, 0, 0, 0, },
   {  "b52-129.30", 0x00020000, 0x0eaebc08, 0, 0, 0, },
   {      "b52-140.36", 0x00020000, 0xc1298a4b, 0, 0, 0, },
   {  "b52-131.37", 0x00020000, 0xaa945d83, 0, 0, 0, },
   {  "b52-132.39", 0x00010000, 0xa2f54789, 0, 0, 0, },
   {  "b52-133.55", 0x00010000, 0x12232f95, 0, 0, 0, },
   {      "b52-139.29", 0x00020000, 0x997f732e, 0, 0, 0, },
   {      "b52-134.51", 0x00010000, 0x91faac7f, 0, 0, 0, },
   {       "b52-39.73", 0x00080000, 0xac9cbbd3, 0, 0, 0, },
   {       "b52-40.72", 0x00080000, 0xf0551055, 0, 0, 0, },
   {       "b52-41.71", 0x00080000, 0x8204880c, 0, 0, 0, },
   {       "b52-42.70", 0x00080000, 0x6e617df1, 0, 0, 0, },
   {       "b52-49.68", 0x00002000, 0x60dd2ed1, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};



static struct ROM_INFO rom_nightstr[] =
{
   {   "b91-01.bin", 0x00080000, 0x3731d94f, 0, 0, 0, },
   {   "b91-02.bin", 0x00080000, 0x457c64b8, 0, 0, 0, },
   {   "b91-03.bin", 0x00080000, 0xcd5fed39, 0, 0, 0, },
   {   "b91-04.bin", 0x00080000, 0x8ca1970d, 0, 0, 0, },
   {   "b91-05.bin", 0x00080000, 0x5e72ac90, 0, 0, 0, },
   {   "b91-06.bin", 0x00080000, 0xa34dc839, 0, 0, 0, },
   {   "b91-07.bin", 0x00080000, 0x4d8ec6cf, 0, 0, 0, },
   {   "b91-08.bin", 0x00080000, 0x66f35c34, 0, 0, 0, },
   {   "b91-09.bin", 0x00080000, 0x5f247ca2, 0, 0, 0, },
   {   "b91-10.bin", 0x00080000, 0x1d8f05b4, 0, 0, 0, },
   {   "b91-11.bin", 0x00080000, 0xfff8ce31, 0, 0, 0, },
   {   "b91-12.bin", 0x00080000, 0xda77c7af, 0, 0, 0, },
   {   "b91-13.bin", 0x00080000, 0x8c7bf0f5, 0, 0, 0, },
   {   "b91-14.bin", 0x00080000, 0x6bc314d3, 0, 0, 0, },
   {   "b91-26.bin", 0x00000400, 0x77682a4f, 0, 0, 0, },
   {   "b91-27.bin", 0x00000400, 0xa3f8490d, 0, 0, 0, },
   {   "b91-28.bin", 0x00000400, 0xfa2f840e, 0, 0, 0, },
   {   "b91-29.bin", 0x00002000, 0xad685be8, 0, 0, 0, },
   {   "b91-30.bin", 0x00010000, 0x30cc1f79, 0, 0, 0, },
   {   "b91-31.bin", 0x00010000, 0xc189781c, 0, 0, 0, },
   {   "b91-32.bin", 0x00000100, 0xfbf81f30, 0, 0, 0, },
   {   "b91-33.bin", 0x00000100, 0x89719d17, 0, 0, 0, },
   {   "b91-39.bin", 0x00020000, 0x725b23ae, 0, 0, 0, },
   {   "b91-40.bin", 0x00020000, 0x81fb364d, 0, 0, 0, },
   {   "b91-41.bin", 0x00020000, 0x2694bb42, 0, 0, 0, },
   {   "b91-43.bin", 0x00020000, 0x3e6f727a, 0, 0, 0, },
   {   "b91-44.bin", 0x00020000, 0x4bc30adf, 0, 0, 0, },
   {   "b91-45.bin", 0x00020000, 0x7ad63421, 0, 0, 0, },
   {   "b91-46.bin", 0x00020000, 0xe870be95, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_nightstr[] =
{
   INP0( COIN1, 0x022804, 0x20 ),
   INP0( COIN2, 0x022804, 0x10 ),
   INP0( TILT, 0x022804, 0x80 ),
   INP0( SERVICE, 0x022804, 0x40 ),

   INP0( P1_START, 0x02280E, 0x01 ),
   INP1( P1_UP, 0x022910, 0xFF ),
   INP1( P1_DOWN, 0x022911, 0xFF ),
   INP1( P1_LEFT, 0x022912, 0xFF ),
   INP1( P1_RIGHT, 0x022913, 0xFF ),
   INP0( P1_B1, 0x02280E, 0x40 ),
   INP0( P1_B2, 0x02280E, 0x80 ),

   INP0( P2_START, 0x02280E, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_night_striker_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_DSWA_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_nightstr[] =
{
   { 0x022800, 0xFF, dsw_data_night_striker_0 },
   { 0x022802, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};


#define OBJ_A_COUNT	(0x3EE7)
#define OBJ_B_COUNT	(0x3E87)

static int obj_id,rod_id;
static int romset;

/*

Type#1
------

- A - Chase HQ
- A - Night Striker

00000-3FFFF = Object 128x128 [16x16] [19900/80:0332] gfx bank#1
40000-5FFFF = Object  64x128 [16x16] [0CC80/40:0332] gfx bank#2
60000-7FFFF = Object  32x128 [16x16] [06640/20:0332] gfx bank#2

Type#2
------

- A - Top Speed
- A - Full Throttle
- B - Continental Circus

00000-7FFFF = Object 128x128 [16x8] [xxxxx/100:xxxx] gfx bank#1

Type#3
------

- Aqua Jack
- Chase HQ 2
- Battle Shark
- Space Gun
- Operation Thunderbolt

00000-7FFFF = Object 64x64 [16x8] [xxxxx/40:xxxx] gfx bank#1

Todo:

- Roadscroll layer (mainly colours)
- Zooming accuracy could maybe be improved
- Sample looping problem (helicopter sound doesn't stop)

*/

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
static UINT8 *GFX_OBJ_A_SOLID;

// 16x16 OBJECT TILES BANK B

static UINT8 *GFX_OBJ_B;
static UINT8 *GFX_OBJ_B_SOLID;

static UINT8 *zoom16_ofs;

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_LINES;

/* road - line - left - right */

static UINT8 PAL_MAP[0x100] =
{
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
   0x1C, 0x1D, 0x1E, 0x1F, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7, 0x4, 0x5, 0x6, 0x7,
};

static UINT8 PAL_MAP_2[0x100] =
{
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
   0x1C, 0x1D, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17, 0x14, 0x15, 0x16, 0x17,
};

static void load_actual(int set)
{
   int ta,tb,tc;
   UINT8 *TMP;

   romset = set;

   if(!(GFX=AllocateMem(0x100000))) return;

   if(!(GFX_LINES=AllocateMem(0x200000))) return;

   if(!(GFX_OBJ_A=AllocateMem(OBJ_A_COUNT*0x100))) return;
   if(!(GFX_OBJ_B=AllocateMem(OBJ_B_COUNT*0x100))) return;

   if(!(OBJECT_MAP=AllocateMem(0x80000))) return;

   if(!(TMP=AllocateMem(0x80000))) return;

   if(!load_rom_index(0, TMP, 0x80000)) return;	// 1024x1 ROAD LINES
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_LINES[tb+0] =((tc&0x8000)>>(14));
      GFX_LINES[tb+1] =((tc&0x4000)>>(13));
      GFX_LINES[tb+2] =((tc&0x2000)>>(12));
      GFX_LINES[tb+3] =((tc&0x1000)>>(11));
      GFX_LINES[tb+4] =((tc&0x0800)>>(10));
      GFX_LINES[tb+5] =((tc&0x0400)>>( 9));
      GFX_LINES[tb+6] =((tc&0x0200)>>( 8));
      GFX_LINES[tb+7] =((tc&0x0100)>>( 7));
      GFX_LINES[tb+0]|=((tc&0x0080)>>( 7));
      GFX_LINES[tb+1]|=((tc&0x0040)>>( 6));
      GFX_LINES[tb+2]|=((tc&0x0020)>>( 5));
      GFX_LINES[tb+3]|=((tc&0x0010)>>( 4));
      GFX_LINES[tb+4]|=((tc&0x0008)>>( 3));
      GFX_LINES[tb+5]|=((tc&0x0004)>>( 2));
      GFX_LINES[tb+6]|=((tc&0x0002)>>( 1));
      GFX_LINES[tb+7]|=((tc&0x0001)>>( 0));
      tb+=8;
   }

   if(!load_rom_index(9, TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_A[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_A[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_A[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_A[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_A[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_A[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_A[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_A[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom_index(8, TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom_index(7, TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom_index(6, TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }



   if(!load_rom_index(5, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_B[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_B[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_B[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_B[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_B[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_B[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_B[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_B[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_B[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_B[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_B[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_B[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_B[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_B[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_B[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom_index(4, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_B[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_B[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_B[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_B[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_B[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_B[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_B[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_B[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_B[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_B[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_B[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_B[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_B[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_B[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_B[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom_index(3, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_B[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_B[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_B[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_B[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_B[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_B[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_B[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_B[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_B[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_B[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_B[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_B[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_B[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_B[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_B[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom_index(2, TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_B[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_B[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_B[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_B[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_B[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_B[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_B[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_B[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_B[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_B[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_B[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_B[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_B[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_B[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_B[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }

   if(!load_rom_index(10, OBJECT_MAP, 0x80000)) return; // TILE MAPPING

   memset(OBJECT_MAP+0x00000+(0x0331*0x80),0x00,0x80);
   memset(OBJECT_MAP+0x40000+(0x0331*0x40),0x00,0x40);
   memset(OBJECT_MAP+0x60000+(0x0331*0x20),0x00,0x20);

   if(!load_rom_index(1, TMP, 0x80000)) return;	// 8x8 BG0 TILES
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX[tb+0] = ((tc&0xF000)>>12);
      GFX[tb+1] = ((tc&0x0F00)>> 8);
      GFX[tb+2] = ((tc&0x00F0)>> 4);
      GFX[tb+3] = ((tc&0x000F)>> 0);
      tb+=4;
   }

   FreeMem(TMP);

   GFX_OBJ_A_SOLID = make_solid_mask_16x16(GFX_OBJ_A, OBJ_A_COUNT);
   GFX_OBJ_B_SOLID = make_solid_mask_16x16(GFX_OBJ_B, OBJ_B_COUNT);
   GFX_BG0_SOLID   = make_solid_mask_8x8  (GFX,       0x4000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0xA0000))) return;

   if(!load_rom_index(14, RAM+0x00000, 0x20000)) return;	// 68000 MAIN ROM
   if(!load_rom_index(15, RAM+0x20000, 0x20000)) return;	// 68000 MAIN ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(18, RAM+0x00000, 0x20000)) return;
   if(!load_rom_index(13, RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom_index(16, RAM, 0x10000)) return;	// 68000 SUB ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom_index(17, RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x50000;
   if(!load_rom_index(19, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x200000))) return;
   if(!load_rom_index(23,PCMROM+0x000000,0x80000)) return;	// Delta-T
   if(!load_rom_index(22,PCMROM+0x080000,0x80000)) return;	// Main
   if(!load_rom_index(21,PCMROM+0x100000,0x80000)) return;	// Main
   if(!load_rom_index(20,PCMROM+0x180000,0x80000)) return;	// Main
   YM2610SetBuffers(PCMROM+0x00000, PCMROM+0x80000, 0x80000, 0x180000);

   //Z80ROM[0x0327] = 0x00;	// NOP
   //Z80ROM[0x0328] = 0x00;	// NOP
/*
   Z80ROM[0x0BBC] = 0x00;	// NOP
   Z80ROM[0x0BBD] = 0x00;	// NOP
   Z80ROM[0x0BBE] = 0x00;	// NOP
*/
   AddTaitoYM2610B(0x0317, 0x02A8, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x29000;
   GFX_FG0    = RAM+0x3C000;
   RAM_INPUT  = RAM+0x22800;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x4000);

   tc0110pcr_init_typeb(RAM+0x20000, 1, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x20000, 0x100, 0x10, 0x8000);

#if 0
   ROM[0xA818]=0x60;		// Sound Comm Fix?
   //WriteWord68k(&ROM[0xA78A],0x4E71);

   WriteWord68k(&ROM[0x00728],0x4E75);
#endif
   WriteWord68k(&ROM[0x0072C],0x4E75);

   ROM[0x9E6]=0x60;		// FIX ROOT MPU STOP ERROR

   // Speed Hack M68000A

   WriteWord68k(&ROM[0x0024E],0x4EF9);
   WriteLong68k(&ROM[0x00250],0x00036000);

   WriteLong68k(&ROM[0x36000],0x46FC2000);	//	move.w	#$2000,sr
   WriteLong68k(&ROM[0x36004],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x36008],0x00AA0000);	//
   WriteWord68k(&ROM[0x3600C],0x6100-10);

   // Speed Hack M68000B

   WriteWord68k(&ROM[0x804D8],0x4EF9);
   WriteLong68k(&ROM[0x804DA],0x00005B00);
   WriteWord68k(&ROM[0x804DE],0x4E71);

   WriteLong68k(&ROM[0x85B00],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x85B04],0x00AA0000);	//
   WriteWord68k(&ROM[0x85B08],0x4A79);
   WriteLong68k(&ROM[0x85B0A],0x00100804);	//	tst.w	$100804
   WriteWord68k(&ROM[0x85B0E],0x67F8);

   WriteWord68k(&ROM[0x85B10],0x4EF9);
   WriteLong68k(&ROM[0x85B12],0x000004E0);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0150rod emulation
   // ------------------------

   tc0150rod.RAM  	= RAM + 0x38000;
   tc0150rod.GFX  	= GFX_LINES;
   tc0150rod.PAL  	= PAL_MAP;
   // tc0150rod.mapper	= &Map_15bit_xBGR;
   tc0150rod.bmp_x	= 32;
   tc0150rod.bmp_y	= 32;
   tc0150rod.bmp_w	= 320;
   tc0150rod.bmp_h	= 240;
   tc0150rod.scr_x	= 0;
   tc0150rod.scr_y	= -15;

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   // tc0100scn[0].layer[0].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   // tc0100scn[0].layer[1].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=240;
   // tc0100scn[0].layer[2].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   init_16x16_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1z();

   obj_id = add_layer_info(gettext("Zooming Object"));
   rod_id = add_layer_info(gettext("Roadscroll"));

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xA0000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x400000, 0x400003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByte(0x820000, 0x820003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xD00000, 0xD007FF, NULL, RAM+0x022000);			// OBJECT RAM
   AddReadWord(0xA00000, 0xA00007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x400000, 0x400003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x400000, 0x400003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByte(0x820000, 0x820003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xD00000, 0xD007FF, NULL, RAM+0x022000);		// OBJECT RAM
   AddWriteWord(0xC20000, 0xC2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xA00000, 0xA00007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x400000, 0x400003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x01FFFF, ROM+0x080000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x01FFFF, NULL, ROM+0x080000);		// 68000 ROM
   AddReadByteMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);		// MAIN RAM
   AddReadByteMC68000B(0x108000, 0x10FFFF, NULL, RAM+0x008000);		// COMMON RAM
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);	// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x01FFFF, NULL, ROM+0x080000);		// 68000 ROM
   AddReadWordMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);		// MAIN RAM
   AddReadWordMC68000B(0x108000, 0x10FFFF, NULL, RAM+0x008000);		// COMMON RAM
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);	// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);	// MAIN RAM
   AddWriteByteMC68000B(0x108000, 0x10FFFF, NULL, RAM+0x008000);	// COMMON RAM
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);	// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);	// MAIN RAM
   AddWriteWordMC68000B(0x108000, 0x10FFFF, NULL, RAM+0x008000);	// COMMON RAM
   AddWriteWordMC68000B(0x800000, 0x801FFF, NULL, RAM+0x038000);	// ROADSCROLL RAM
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);	// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void load_chasehq(void)
{
   load_actual(0);
}

static void load_chasehqj(void)
{
   load_actual(1);
}

static void clear_chase_hq(void)
{
   RemoveTaitoYM2610();

}

static void load_nightstr(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   romset=2;

   if(!(GFX=AllocateMem(0x100000))) return;

   if(!(GFX_LINES=AllocateMem(0x200000))) return;

   if(!(GFX_OBJ_A=AllocateMem(OBJ_A_COUNT*0x100))) return;
   if(!(GFX_OBJ_B=AllocateMem(OBJ_B_COUNT*0x100))) return;

   if(!(OBJECT_MAP=AllocateMem(0x80000))) return;

   if(!(TMP=AllocateMem(0x80000))) return;

   if(!load_rom("b91-10.bin", TMP, 0x80000)) return;	// 1024x1 ROAD LINES
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_LINES[tb+0] =((tc&0x8000)>>(14));
      GFX_LINES[tb+1] =((tc&0x4000)>>(13));
      GFX_LINES[tb+2] =((tc&0x2000)>>(12));
      GFX_LINES[tb+3] =((tc&0x1000)>>(11));
      GFX_LINES[tb+4] =((tc&0x0800)>>(10));
      GFX_LINES[tb+5] =((tc&0x0400)>>( 9));
      GFX_LINES[tb+6] =((tc&0x0200)>>( 8));
      GFX_LINES[tb+7] =((tc&0x0100)>>( 7));
      GFX_LINES[tb+0]|=((tc&0x0080)>>( 7));
      GFX_LINES[tb+1]|=((tc&0x0040)>>( 6));
      GFX_LINES[tb+2]|=((tc&0x0020)>>( 5));
      GFX_LINES[tb+3]|=((tc&0x0010)>>( 4));
      GFX_LINES[tb+4]|=((tc&0x0008)>>( 3));
      GFX_LINES[tb+5]|=((tc&0x0004)>>( 2));
      GFX_LINES[tb+6]|=((tc&0x0002)>>( 1));
      GFX_LINES[tb+7]|=((tc&0x0001)>>( 0));
      tb+=8;
   }

   if(!load_rom("b91-01.bin", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_A[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_A[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_A[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_A[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_A[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_A[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_A[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_A[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom("b91-02.bin", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom("b91-03.bin", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom("b91-04.bin", TMP, OBJ_A_COUNT*0x20)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }



   if(!load_rom("b91-05.bin", TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_B[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_B[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_B[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_B[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_B[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_B[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_B[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_B[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_B[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_B[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_B[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_B[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_B[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_B[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_B[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom("b91-06.bin", TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_B[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_B[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_B[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_B[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_B[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_B[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_B[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_B[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_B[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_B[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_B[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_B[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_B[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_B[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_B[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom("b91-07.bin", TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_B[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_B[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_B[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_B[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_B[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_B[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_B[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_B[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_B[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_B[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_B[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_B[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_B[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_B[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_B[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom("b91-08.bin", TMP, OBJ_B_COUNT*0x20)) return;	// 16x16 OBJ B
   tb=0;
   for(ta=0;ta<OBJ_B_COUNT*0x20;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_B[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_B[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_B[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_B[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_B[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_B[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_B[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_B[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_B[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_B[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_B[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_B[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_B[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_B[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_B[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_B[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }

   if(!load_rom("b91-09.bin", OBJECT_MAP, 0x80000)) return; // TILE MAPPING

   if(!load_rom("b91-11.bin", TMP, 0x80000)) return;	// 8x8 BG0 TILES
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      tb+=4;
   }

   FreeMem(TMP);

   GFX_OBJ_A_SOLID = make_solid_mask_16x16(GFX_OBJ_A, OBJ_A_COUNT);
   GFX_OBJ_B_SOLID = make_solid_mask_16x16(GFX_OBJ_B, OBJ_B_COUNT);
   GFX_BG0_SOLID   = make_solid_mask_8x8  (GFX,       0x4000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0xC0000))) return;

   if(!load_rom("b91-45.bin", RAM+0x00000, 0x20000)) return;	// 68000 MAIN ROM
   if(!load_rom("b91-43.bin", RAM+0x20000, 0x20000)) return;	// 68000 MAIN ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("b91-44.bin", RAM+0x00000, 0x20000)) return;
   if(!load_rom("b91-46.bin", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("b91-39.bin", RAM, 0x20000)) return;	// 68000 SUB ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom("b91-40.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x50000;
   if(!load_rom("b91-41.bin", Z80ROM, 0x20000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x180000))) return;
   if(!load_rom("b91-14.bin",PCMROM+0x000000,0x80000)) return;	// Delta-T ADPCM
   if(!load_rom("b91-13.bin",PCMROM+0x080000,0x80000)) return;	// Main ADPCM 1/2
   if(!load_rom("b91-12.bin",PCMROM+0x100000,0x80000)) return;	// Main ADPCM 2/2
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x180000, 0x180000);

   AddTaitoYM2610B(0x0246, 0x01BA, 0x20000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x29000;
   GFX_FG0    = RAM+0x3C000;
   RAM_INPUT  = RAM+0x22800;

   tc0110pcr_init_typeb(RAM+0x20000, 1, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x20000, 0x100, 0x10, 0x8000);


   ROM[0x0FE92]=0x60;

   ROM[0x0FEB2]=0x4E;
   ROM[0x0FEB3]=0x71;
   ROM[0x0FEB4]=0x4E;
   ROM[0x0FEB5]=0x71;

   ROM[0x0F3AA]=0x4E;		// SKIP OLD CODE (NO ROOM FOR HACK)
   ROM[0x0F3AB]=0xF9;		// (JMP $008000)
   ROM[0x0F3AC]=0x00;
   ROM[0x0F3AD]=0x00;
   ROM[0x0F3AE]=0x80;
   ROM[0x0F3AF]=0x00;

   ROM[0x8000]=0x13;		// move.b #$00,$AA0000
   ROM[0x8001]=0xFC;		// (Speed Hack)
   ROM[0x8002]=0x00;
   ROM[0x8003]=0x00;
   ROM[0x8004]=0x00;
   ROM[0x8005]=0xAA;
   ROM[0x8006]=0x00;
   ROM[0x8007]=0x00;

   ROM[0x8008]=0x4E;		// GO BACK...
   ROM[0x8009]=0xF9;		// (JMP $00F200)
   ROM[0x800A]=0x00;
   ROM[0x800B]=0x00;
   ROM[0x800C]=0xF2;
   ROM[0x800D]=0x00;


   ROM[0x80856]=0x4E;		// SKIP OLD CODE (NO ROOM FOR HACK)
   ROM[0x80857]=0xF9;		// (JMP $30000)
   ROM[0x80858]=0x00;
   ROM[0x80859]=0x03;
   ROM[0x8085A]=0x00;
   ROM[0x8085B]=0x00;

   ROM[0xB0000]=0x4E;		// jsr $412
   ROM[0xB0001]=0xB9;
   ROM[0xB0002]=0x00;
   ROM[0xB0003]=0x00;
   ROM[0xB0004]=0x04;
   ROM[0xB0005]=0x12;

   ROM[0xB0006]=0x13;		// move.b #$00,$AA0000
   ROM[0xB0007]=0xFC;		// (Speed Hack)
   ROM[0xB0008]=0x00;
   ROM[0xB0009]=0x00;
   ROM[0xB000A]=0x00;
   ROM[0xB000B]=0xAA;
   ROM[0xB000C]=0x00;
   ROM[0xB000D]=0x00;

   ROM[0xB000E]=0x60;		// loop
   ROM[0xB000F]=0x100-10;

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0150rod emulation
   // ------------------------

   tc0150rod.RAM  	= RAM + 0x38000;
   tc0150rod.GFX  	= GFX_LINES;
   tc0150rod.PAL  	= PAL_MAP_2;
   // tc0150rod.mapper	= &Map_15bit_xBGR;
   tc0150rod.bmp_x	= 32;
   tc0150rod.bmp_y	= 32;
   tc0150rod.bmp_w	= 320;
   tc0150rod.bmp_h	= 240;
   tc0150rod.scr_x	= 0;
   tc0150rod.scr_y	= -15;

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   // tc0100scn[0].layer[0].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   // tc0100scn[0].layer[1].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=240;
   // tc0100scn[0].layer[2].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   init_16x16_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1z();

   obj_id = add_layer_info(gettext("Zooming Object"));
   rod_id = add_layer_info(gettext("Roadscroll"));

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xC0000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x110000, 0x113FFF, NULL, RAM+0x034000);			// COMMON RAM
   AddReadByte(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0xE40000, 0xE40007, NULL, RAM+0x022900);			// WHEEL
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x110000, 0x113FFF, NULL, RAM+0x034000);			// COMMON RAM
   AddReadWord(0xD00000, 0xD007FF, NULL, RAM+0x022000);			// OBJECT RAM
   AddReadWord(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0xE40000, 0xE40007, NULL, RAM+0x022900);			// WHEEL
   AddReadWord(0xA00000, 0xA00007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x820000, 0x820003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x110000, 0x113FFF, NULL, RAM+0x034000);		// COMMON RAM
   AddWriteByte(0x400000, 0x40000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xD00000, 0xD007FF, NULL, RAM+0x022000);		// OBJECT RAM
   AddWriteWord(0x110000, 0x113FFF, NULL, RAM+0x034000);		// COMMON RAM
   AddWriteWord(0xC20000, 0xC2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xA00000, 0xA00007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x820000, 0x820003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWord(0x400000, 0x40000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM+0x080000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x080000);			// 68000 ROM
   AddReadByteMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);			// WORK+COMMON RAM
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x080000);			// 68000 ROM
   AddReadWordMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);			// WORK+COMMON RAM
   AddReadWordMC68000B(0x800000, 0x801FFF, NULL, RAM+0x038000);			// ??? RAM
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);		// WORK+COMMON RAM
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x100000, 0x107FFF, NULL, RAM+0x030000);		// WORK+COMMON RAM
   AddWriteWordMC68000B(0x800000, 0x801FFF, NULL, RAM+0x038000);		// ??? RAM
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}


static void ClearNightStr(void)
{
   RemoveTaitoYM2610();
}

static void execute_nightstr(void)
{
   // Wheel Hack
   static int wx,wy;

   if(wx >  0) wx-=4;
   if(wx <  0) wx+=4;
   if(wy >  0) wy-=4;
   if(wy <  0) wy+=4;

   if(RAM_INPUT[0x112]!=0){		// L
      wx -= 16;
   }
   if(RAM_INPUT[0x113]!=0){		// R
      wx += 16;
   }
   if(RAM_INPUT[0x110]!=0){		// U
      wy -= 16;
   }
   if(RAM_INPUT[0x111]!=0){		// D
      wy += 16;
   }

   if(wx >  127) wx=  127;
   if(wx < -128) wx= -128;
   if(wy >  127) wy=  127;
   if(wy < -128) wy= -128;

   RAM_INPUT[0x100] = wx&0xFF;
   RAM_INPUT[0x104] = wy&0xFF;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   /*#ifdef RAINE_DEBUG
      print_debug("PC0:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
#endif*/
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 4);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   /*#ifdef RAINE_DEBUG
      print_debug("PC1:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
#endif*/
   cpu_interrupt(CPU_68K_1, 4);

   Taito2610_Frame();			// Z80 and YM2610

   //print_ingame(60,gettext("%04x"),ReadWord(&RAM[0x39FFE]));
}

static void execute_chasehq(void)
{

/*
Analog Controls Description by Warlock

RAINE is based on the upright deluxe version. I call it deluxe because it has a more expensive steering wheel, which behaves like the PC standard. This version is selectable by forcing dipswitches A1 and A2 to:

A1 - H
A2 - L

Machine Input RAM Map

Address [0x022804]
------------------

0 - Unknown
1 - Unknown
2 - Coin 1
3 - Coin 2
4 - Service
5 - Analog Brake
6 - Analog Brake
7 - Analog Brake

Address [0x022806]
------------------

0 - Turbo
1 - Tilt
2 - Unknwown
3 - P1 Start
4 - Gear
5 - Analog Accelerator
6 - Analog Accelerator
7 - Analog Accelerator

Address [0x02281A]+[0x022818]
-----------------------------

Steering Wheel


Steering Wheel Behaviour (Linear)
---------------------------------

256 possible states

Full Left  - FF80
Half Left  - FFC0
Center     - 0000
Half Right - 0040
Full Right - 0080


Pedals Behaviour (Non-Linear)
-----------------------------

8 possible states

(Speed - RAM)

0 - 000xxxxx
1 - 001xxxxx
2 - 011xxxxx
3 - 010xxxxx
4 - 110xxxxx
5 - 111xxxxx
6 - 101xxxxx
7 - 100xxxxx

*/


// Analog Controls Support by Warlock

   static int accel,brake;
   // 9 entries to avoid to have to round the number...
   static int analog_mask[9] = { 0x00, 0x20, 0x60, 0x40, 0xC0, 0xE0, 0xA0, 0x80, 0x80 };
   static int gear=0;
   static int gearflip=0;



/*----[Start of Gear Options]----*/

// User requests arcade version gear control
if (RAM[0x022801] &0x01){
 if(RAM_INPUT[0x20]!=0){RAM_INPUT[0x06] |= 0x10;}
  else {RAM_INPUT[0x06] &= ~0x10;}
}

// User requests home version gear control
else
{
   // Gear Control Hack

   if(RAM_INPUT[0x20]!=0){
      if(gearflip==0){
         gearflip=1;
         gear^=1;
         if(gear==1) print_ingame(60,gettext("Changed to High Gear"));
         else        print_ingame(60,gettext("Changed to Low Gear"));
      }
   }
   else{
      gearflip=0;
   }

   if(gear==1) RAM_INPUT[0x06] &= ~0x10;
   else        RAM_INPUT[0x06] |=  0x10;

  }

/*----[End of Gear Options]----*/


/*----[Start of Steering Wheel Emulation]----*/

// User requests Keyboard Control
#ifdef SDL
if (analog_num < 0) {
#else
if (RAM[0x022801] &0x02){
#endif
   RAM_INPUT[0x18] |=  0x80;
   RAM_INPUT[0x1A] |=  0x80;
}

// User requests Standard PC Joystick/Wheel Control
else{
#ifdef SDL
  RAM_INPUT[0x18] = (analog_normx>>7) & 0xff;
  RAM_INPUT[0x1A] = (analog_normx>>15);
#else
   RAM_INPUT[0x18] =  joy[0].stick[0].axis[0].pos;
   RAM_INPUT[0x1A] =  joy[0].stick[0].axis[0].pos>>8;
#endif
}
/*----[End of Steering Wheel Emulation]----*/


/*----[Start of Pedals Emulation]----*/

// User requests Keyboard Accelerator Control
#ifdef SDL
if (analog_num < 0) {
#else
if (RAM[0x022801] &0x04){
#endif

//Player presses accelerator on keyboard
 if (RAM[0x022807]) { RAM[0x022806]=(RAM[0x022806] & 0x1f) | 0x80;}
 else {RAM[0x022806]=(RAM[0x022806] & 0x1f) | 0x00;}
}

// User requests analog accelerator control
else{

#ifdef SDL
accel = -analog_normy/2048;
#else
accel=-joy[0].stick[0].axis[1].pos/16;
#endif
if (accel >= 0) {RAM[0x022806] = ((RAM[0x022806] & 0x1f) | analog_mask[accel]);}

}

// User requests keyboard brake Control
#ifdef SDL
if (analog_num < 0) {
#else
if (RAM[0x022801] &0x08){
#endif
//Player presses brake on keyboard
 if (RAM[0x022809]) { RAM[0x022804]=(RAM[0x022804] & 0x1f) | 0x80;}
 else {RAM[0x022804]=(RAM[0x022804] & 0x1f) | 0x00;}
}

// User requests analog brake control
else{

#ifdef SDL
brake = analog_normy/2048;
#else
brake=joy[0].stick[0].axis[1].pos/16;
#endif
if (brake >= 0) {RAM[0x022804] = ((RAM[0x022804] & 0x1f) | analog_mask[brake]);}

}

/*----[End of Pedals Emulation]----*/


   // CPU Emulation

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));		// M68000 16MHz (60fps)
      print_debug("PC0:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 5);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(16,60));		// M68000 16MHz (60fps)
      print_debug("PC1:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 4);

   Taito2610_Frame();				// Z80 and YM2610

   //print_ingame(60,gettext("%04x"),ReadWord(&RAM[0x39FFE]));
}

static void render_z_system_sprites(int start, int end)
{
   int x,y,ta,tb,zz;
   int zx,zy,rx,ry,xx,zzx,zzy;
   UINT8 *map,*SPR_MAP;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;

   // OBJECT Z-SYSTEM
   // ---------------

   for(zz=0x22000+start;zz<0x22000+end;zz+=8){

      zx=(RAM[zz+2]>>0)&0x7F;
      zy=(RAM[zz+1]>>1)&0x7F;
      if((zx!=0)&&(zy!=0)){

         ta = ReadWord(&RAM[zz+6])&0x7FF;
         if(ta!=0){

            x=(32+ReadWord(&RAM[zz+4]))&0x1FF;

            //y=(32+ReadWord(&RAM[zz+0])+(0x3F-(zy>>1)))&0x1FF;

            y=(((128-16)+32+7)+(ReadWord(&RAM[zz+0])-zy))&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+2])>>7)&0xFF,
               16,
               map
            );

            if((zx&0x40)!=0){					// [128x128]

            zoom_dat_x = zoom16_ofs+(zx<<3);
            zoom_dat_y = zoom16_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + (ta<<7);

            switch(RAM[zz+5]&0xC0){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_A[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=16;
            x=xx;
            }

            break;
            }


            }
            else{

            if((zy&0x20)!=0){					// [64x128]

            zoom_dat_x = zoom16_ofs+(((zx<<1)|1)<<3);
            zoom_dat_y = zoom16_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + 0x40000 + (ta<<6);

            switch(RAM[zz+5]&0xC0){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=8;
            x=xx;
            }

            break;
            }


            }
            else{						// [32x128]

            zoom_dat_x = zoom16_ofs+(((zx<<2)|3)<<3);
            zoom_dat_y = zoom16_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + 0x60000 + (ta<<5);

            switch(RAM[zz+5]&0xC0){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=4;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=4;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=4;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<2;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x3FFF;
               if(GFX_OBJ_B_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_B_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_B[tb<<8],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=4;
            x=xx;
            }

            break;
            }


            }


            }

         }
      }
   }
}

static void DrawChaseHQ(void)
{
   int y,ta,tb,tb2,zz,zy;
   int mask_count;
   int mask_pos[32];
   int mask_pos_y[32];
   UINT16 scroll_store;

   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   scroll_store = ReadWord(RAM_SCROLL+0);

   WriteWord(RAM_SCROLL+0,scroll_store+ReadWord(RAM_VIDEO+0xC100));
   WriteWord(RAM_SCROLL+2,scroll_store+ReadWord(RAM_VIDEO+0xC400));

   // Find Mask Sprites
   // -----------------

   mask_count=0;

   if(romset<2){
   mask_pos[mask_count]   = 0x000;
   mask_pos_y[mask_count] = 0x000;
   mask_count++;
   tb=0;
   tb2=0;
   for(zz=0x22000;zz<0x22800;zz+=8){

      ta = ReadWord(&RAM[zz+6])&0x7FF;

      //if((ta==0x0123) && (((ReadWord(&RAM[zz+2])>>7)&0x7F)==0x7F) ){
      if((ta==0x0123) && ((ReadWord(&RAM[zz+2])&0x8000)==0x8000) ){
      //if((ta==0x0331)||(ta==0x011A)){
         //if(ta!=0x011A)
         //WriteWord(&RAM[zz+6],0x0000);
         if(tb2==0){
            zy=(RAM[zz+1]>>1)&0x7F;
            y=(((128-16)+32+7)+(ReadWord(&RAM[zz+0])-zy))&0x1FF;
            //y=(((128-16)+32+7)+(ReadWord(&RAM[zz+0])-0))&0x1FF;
            y = ((y-(15+4))<<3);

            if(y<0) y=0;
            if(y>0x800) y=0x800;

            if(y>mask_pos_y[mask_count-1]){

            tb2=1;
            mask_pos[mask_count]   = zz&0x7FF;
            mask_pos_y[mask_count] = y;

            mask_count++;
            }
            else{

            //print_ingame(60,gettext("MASK REDUCED"));

            tb2=1;

            while(y>mask_pos_y[mask_count-1]){
               mask_count--;
            }

            mask_count=0;

            mask_pos[mask_count]   = 0x000;
            mask_pos_y[mask_count] = 0x000;
            mask_count++;

            mask_pos[mask_count]   = zz&0x7FF;
            mask_pos_y[mask_count] = y;

            mask_count++;

            }
         }
         else{
            mask_pos[mask_count-1]   = zz&0x7FF;
         }
      }
      else{
         if(tb2){
            tb2=0;
            mask_pos[mask_count-1]   = zz&0x7FF;
         }
      }

      if(ta==0x0331){
      //if((ta==0x0331)||(ta==0x011A)){
         //if(ta!=0x011A)
         //WriteWord(&RAM[zz+6],0x0000);
         if(tb==0){
            zy=(RAM[zz+1]>>1)&0x7F;
            y=(((128-16)+32+7)+(ReadWord(&RAM[zz+0])-zy))&0x1FF;
            y = ((y-(15+4))<<3);

            if(y<0) y=0;
            if(y>0x800) y=0x800;

            if(y>mask_pos_y[mask_count-1]){

            tb=1;
            mask_pos[mask_count]   = zz&0x7FF;
            mask_pos_y[mask_count] = y;

            mask_count++;
            }
            else{

            //print_ingame(60,gettext("MASK REDUCED"));

            tb=1;

            while(y>mask_pos_y[mask_count-1]){
               mask_count--;
            }

            mask_count=0;

            mask_pos[mask_count]   = 0x000;
            mask_pos_y[mask_count] = 0x000;
            mask_count++;

            mask_pos[mask_count]   = zz&0x7FF;
            mask_pos_y[mask_count] = y;

            mask_count++;

            }
         }
         else{
            mask_pos[mask_count-1]   = zz&0x7FF;
         }
      }
      else{
         tb=0;
      }

   }

   //print_ingame(60,gettext("MSK: %04x"),mask_count);
   mask_pos[mask_count]   = 0x800;
   mask_pos_y[mask_count] = 0x800;
   }

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // 3D-ROAD Z-SYSTEM
   // ----------------

   if(check_layer_enabled(rod_id))
      tc0150rod_init_palette();

   if(mask_count==0){

   if(check_layer_enabled(rod_id))
      tc0150rod_render(0x000,0x800);
   if(check_layer_enabled(obj_id))
      render_z_system_sprites(0x000,0x800);
   }
   else{

   for(ta=0;ta<mask_count;ta++){
   if(check_layer_enabled(rod_id))
      tc0150rod_render(mask_pos_y[ta],mask_pos_y[ta+1]);
   if(check_layer_enabled(obj_id))
      render_z_system_sprites(mask_pos[ta],mask_pos[ta+1]);

   }

   }

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);

   WriteWord(RAM_SCROLL+0,scroll_store);

   tc0150rod_show_palette();
}

/*

AraCORN
-------

Name         | Description
-------------+---------------------------------
b52-129.rom  | 68000 Main (block2; odd)
b52-130.rom  | 68000 Main (block1; even)
b52-131.rom  | 68000 Main (block2; even)
b52-132.rom  | 68000 Sub  (block1; even)
b52-133.rom  | 68000 Sub  (block1; odd)
b52-136.rom  | 68000 Main (block1; odd)
b52-137.rom  | Z80 Sound ROM (english)
b52-50.rom   | ?
b52-51.rom   | ?
b52-m113.rom | Samples (adpcm) (bad)
b52-m114.rom | Samples (adpcm) (bad)
b52-m115.rom | Samples (adpcm) (bad)
b52-m116.rom | Samples (adpcm) (bad)
b52-m28.rom  | Road Lines
b52-m29.rom  | 8x8 BG0 Tiles
b52-m30.rom  | 16x16 Sprites bank#2 (plane3) (for 64x64)
b52-m31.rom  | 16x16 Sprites bank#2 (plane2)
b52-m32.rom  | 16x16 Sprites bank#2 (plane1)
b52-m33.rom  | 16x16 Sprites bank#2 (plane0)
b52-m34.rom  | 16x16 Sprites bank#1 (plane3) (for 128x128)
b52-m35.rom  | 16x16 Sprites bank#1 (plane2)
b52-m36.rom  | 16x16 Sprites bank#1 (plane1)
b52-m37.rom  | 16x16 Sprites bank#1 (plane0)
b52-m38.rom  | Sprite Maps (bad)


malcor
------

Name         | Description
-------------+---------------------------------
B52-01.BPR   | ---
B52-03.BPR   | ---
B52-06.BPR   | ---
B52-118.PLD  | ---
B52-119.PLD  | ---
B52-120.PLD  | ---
B52-121.PLD  | ---
B52-122.PLD  | ---
B52-123.PLD  | ---
B52-124.PLD  | ---
B52-125.PLD  | ---
B52-126.BPR  | ---
B52-127.BPR  | ---
B52-129      | 68000 Main (block2; odd) (same)
B52-131      | 68000 Main (block2; even) (same)
B52-132      | 68000 Sub  (block1; even) (same)
B52-133      | 68000 Sub  (block1; odd) (same)
B52-134      | Z80 Sound ROM (japanese)
B52-139      | 68000 Main (block1; odd)
B52-140      | 68000 Main (block1; even)
B52-16.BPR   | ---
B52-17.PLD   | ---
B52-18.BPR   | ---
B52-19.PLD   | ---
B52-20.PLD   | ---
B52-21.PLD   | ---
B52-25.PLD   | ---
B52-26.PLD   | ---
B52-27.PLD   | ---
B52-28       | Road Lines (same)
B52-29       | 8x8 BG0 Tiles (same)
B52-30       | 16x16 Sprites bank#2 (plane3) (for 64x64) (same)
B52-31       | 16x16 Sprites bank#2 (plane2) (same)
B52-32       | 16x16 Sprites bank#2 (plane1) (same)
B52-33       | 16x16 Sprites bank#2 (plane0) (same)
B52-34       | 16x16 Sprites bank#1 (plane3) (for 128x128) (same)
B52-35       | 16x16 Sprites bank#1 (plane2) (same)
B52-36       | 16x16 Sprites bank#1 (plane1) (same)
B52-37       | 16x16 Sprites bank#1 (plane0) (same)
B52-38       | Sprite Maps
B52-39       | Samples (adpcm) (japanese)
B52-40       | Samples (adpcm) (japanese)
B52-41       | Samples (adpcm) (japanese) (bad?)
B52-42       | Samples (adpcm) (japanese)
B52-49       | ?
B52-50       | ?
B52-51       | ?


Sprite List Format (8 bytes/sprite)
===================================

Byte | Bit(s) | Description
-----+76543210+--------------------
  0  |xxxxxxx.| Zoom Y (0-127)
  0  |.......x| Y Position (High)
  1  |xxxxxxxx| Y Position (Low)
  2  |x.......| Sprite:Road Priority
  2  |.xxxxxxx| Color Bank (High)
  3  |x.......| Color Bank (Low)
  3  |.xxxxxxx| Zoom X (0-127)
  4  |x.......| Flip X Axis
  4  |.x......| Flip Y Axis
  4  |.......x| X Position (High)
  5  |xxxxxxxx| X Position (Low)
  6  |....xxxx| Sprite Number (High)
  7  |xxxxxxxx| Sprite Number (Low)

*/

static struct VIDEO_INFO video_nightstr =
{
   DrawChaseHQ,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_chasehq[] =
{
   { "chase_hq", },
   { "chasehq", },
   { NULL, },
};
GAME( chasehq, "Chase HQ", TAITO, 1988, GAME_RACE,
	.input = input_chasehq,
	.dsw = dsw_chasehq,
	.clear = clear_chase_hq,
	.video = &video_nightstr,
	.exec = execute_chasehq,
	.long_name_jpn = "ƒ`ƒFƒCƒX‚g‚p American",
	.board = "B52",
);
static struct DIR_INFO dir_chasehqj[] =
{
   { "chase_hq_japanese", },
   { "chasehqj", },
   { ROMOF("chasehq"), },
   { CLONEOF("chasehq"), },
   { NULL, },
};
GAME(chasehqj, "Chase HQ (Japan)", TAITO, 1988, GAME_RACE,
	.input = input_chasehq,
	.dsw = dsw_chasehq,
	.clear = clear_chase_hq,
	.video = &video_nightstr,
	.exec = execute_chasehq,
	.long_name_jpn = "ƒ`ƒFƒCƒX‚g‚p",
	.board = "B52",
);
static struct DIR_INFO dir_nightstr[] =
{
   { "night_striker", },
   { "nightstr", },
   { NULL, },
};
GME( nightstr, "Night Striker", TAITO, 1989, GAME_RACE | GAME_SHOOT | GAME_PARTIALLY_WORKING,
	.clear = ClearNightStr,
	.board = "b91",
);

