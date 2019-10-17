/******************************************************************************/
/*                                                                            */
/*                  BUBBLE BOBBLE (C) 1984 TAITO CORPORATION.                 */
/*                                                                            */
/*  Driver by Richard Mitton (richard.mitton@bigfoot.com)                     */
/*  Similiar hardware is used by Bobble Bobble, and Tokio/Scramble Formation. */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "2203intf.h"
#include "3812intf.h"
#include "savegame.h"
#include "blit.h" // clear_game_screen
#include "timer.h"
#include "decode.h"
#include "emumain.h"
#include "assoc.h"

/*

changes/spindizzy:

- put English/Japanese language switch back (?!)
- fixed 2P controls
- fixed EXTEND letters

- removed VIDEO_INFO struct and inserted SetScreenBitmap() :-P
- added sound (YM3812 doesn't work when using Raine functions though,
               only using inport/outport directly)
- well bugger me. The sound stops once you lose the game. Bummer.
- cleaned some bits up
- /me thinks it's time Antiriad had a lesson in whitespace/indentation...
- AAARGH!! Raine wants the MCU to be able to save it's state! (it doesn't)
           Moon on a friggin' stick, that's what you want...
- swapped buttons 1/2 for the inputs

*/

/*

changes/antiriad:

- remove SetScreenBitmap() and insert VIDEO_INFO sturct
- fixed it drawing over the edges of the screen bitmap (naughty)! :)
- removed procedure calls for common ram access (use raine modified mz80 for
  direct access)
- changed a few lines here and there (looking for the bug)...
- hmm, added 100 cpu slices per frame, and the game seems to run now =)
- improved the screen update (flipping, clipping, solid mask data, refresh
  palette when needed)
- er, stuck in some dsw and inputs, the inputs are far from complete, but
  the joystick will work too now anyway :).
- fixed ym3812 playing, you have to set multiple soundchips with saaddsound().
  don't ask me why, hiroshi coded it this way ;).
- added mz80 raine-customized bank switching, no more memcpy :).
- bankswitch is updated in loadgame callback.

27-August-99:

- Added Bobble Bobble and Super Bobble Bobble bootleg sets.
- Changed date from 1984 to 1986 (oops!).
- Removed up/down from inputs (unused, like rainbow islands).
- Cpu slices is now 16 per frame, or the music breaks on the bootlegs.
- I think it's safe to remove the FAKE_MCU stuff now ｦ_ｦ.

08-September-99:

- Added Bubble Bobble (romstar). That's all.
- The FAKE_MCU stuff is removed!

*/

/* This is a hack for the MCU. Increase it if the controls don't
 * seem responsive enough.
 */

#define BIH_COUNT 60
#define MAME_MCU

/******************************************************************************/

/*****************
   BUBBLE BOBBLE
 *****************/


static struct ROM_INFO rom_bublbobl[] =
{
    /* ROMs banked at 8000-bfff */
    { "a78-06.51", 0x08000, 0x32c8305b, REGION_CPU1, 0x00000, LOAD_NORMAL },
    /* 20000-2ffff empty */
    { "a78-05.52", 0x10000, 0x53f4bc6e, REGION_CPU1, 0x08000, LOAD_NORMAL },
   { "a78-08.37", 0x08000, 0xae11a07b, REGION_ROM2, 0x0000, LOAD_NORMAL },
   { "a78-07.46", 0x08000, 0x4f9a26e8, REGION_ROM3, 0x0000, LOAD_NORMAL },
   { "a78-09.12", 0x8000, 0x20358c22, REGION_GFX1, 0x00000, LOAD_NORMAL },
   { "a78-10.13", 0x8000, 0x930168a9, REGION_GFX1, 0x08000, LOAD_NORMAL },
   { "a78-11.14", 0x8000, 0x9773e512, REGION_GFX1, 0x10000, LOAD_NORMAL },
   { "a78-12.15", 0x8000, 0xd045549b, REGION_GFX1, 0x18000, LOAD_NORMAL },
   { "a78-13.16", 0x8000, 0xd0af35c5, REGION_GFX1, 0x20000, LOAD_NORMAL },
   { "a78-14.17", 0x8000, 0x7b5369a8, REGION_GFX1, 0x28000, LOAD_NORMAL },
   /* 0x30000-0x3ffff empty */
  FILL(          0x30000, 0x10000, 0, GFX1),
   { "a78-15.30", 0x8000, 0x6b61a413, REGION_GFX1, 0x40000, LOAD_NORMAL },
   { "a78-16.31", 0x8000, 0xb5492d97, REGION_GFX1, 0x48000, LOAD_NORMAL },
   { "a78-17.32", 0x8000, 0xd69762d5, REGION_GFX1, 0x50000, LOAD_NORMAL },
   { "a78-18.33", 0x8000, 0x9f243b68, REGION_GFX1, 0x58000, LOAD_NORMAL },
   { "a78-19.34", 0x8000, 0x66e9438c, REGION_GFX1, 0x60000, LOAD_NORMAL },
   { "a78-20.35", 0x8000, 0x9ef863ad, REGION_GFX1, 0x68000, LOAD_NORMAL },
   /* 0x70000-0x7ffff empty */
  FILL(          0x70000, 0x10000, 0, GFX1),
   { "68705.bin", 0x00000800, 0x78caa635, REGION_ROM4, 0, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_dland[] =
{
	/* ROMs banked at 8000-bfff */
  { "dl_3.u69", 0x08000, 0x01eb3e4f, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "dl_5.u67", 0x08000, 0x75740b61, REGION_CPU1, 0x08000, LOAD_NORMAL },
  { "dl_4.u68", 0x08000, 0xc6a3776f, REGION_CPU1, 0x10000, LOAD_NORMAL },
	/* 20000-2ffff empty */
  { "dl_6.58", 0x10000, 0x6352d3fa, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "dl_7.59", 0x10000, 0x37a38b69, REGION_GFX1, 0x10000, LOAD_NORMAL },
  { "dl_8.60", 0x10000, 0x509ee5b1, REGION_GFX1, 0x20000, LOAD_NORMAL },
	/* 0x30000-0x3ffff empty */
  FILL(          0x30000, 0x10000, 0, GFX1),
  { "dl_9.61", 0x10000, 0xae8514d7, REGION_GFX1, 0x40000, LOAD_NORMAL },
  { "dl_10.62", 0x10000, 0x6d406fb7, REGION_GFX1, 0x50000, LOAD_NORMAL },
  { "dl_11.63", 0x10000, 0xbdf9c0ab, REGION_GFX1, 0x60000, LOAD_NORMAL },
	/* 0x70000-0x7ffff empty */
  FILL(          0x70000, 0x10000, 0, GFX1),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_bublcave[] =
{
	/* ROMs banked at 8000-bfff */
  { "a78-06-1.51", 0x08000, 0xe8b9af5e, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "a78-05-1.52", 0x10000, 0xcfe14cb8, REGION_CPU1, 0x08000, LOAD_NORMAL },
	/* 20000-2ffff empty */
  FILL(          0x18000, 0x10000, 0, CPU1), // not sure it's used !
  { "a78-08.37", 0x08000, 0xa9384086, REGION_ROM2, 0x0000, LOAD_NORMAL },
  // { "a78-01.17", 0x1000, 0xb1bfb53d, REGION_ROM4, 0xf000, LOAD_NORMAL },
  { "a78-09.12", 0x8000, 0xb90b7eef, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "a78-10.13", 0x8000, 0x4fb22f05, REGION_GFX1, 0x08000, LOAD_NORMAL },
  { "a78-11.14", 0x8000, 0x9773e512, REGION_GFX1, 0x10000, LOAD_NORMAL },
  { "a78-12.15", 0x8000, 0xe49eb49e, REGION_GFX1, 0x18000, LOAD_NORMAL },
  { "a78-13.16", 0x8000, 0x61919734, REGION_GFX1, 0x20000, LOAD_NORMAL },
  { "a78-14.17", 0x8000, 0x7e3a13bd, REGION_GFX1, 0x28000, LOAD_NORMAL },
  { "a78-15.30", 0x8000, 0xc253c73a, REGION_GFX1, 0x40000, LOAD_NORMAL },
  /* 0x30000-0x3ffff empty */
  FILL(          0x30000, 0x10000, 0, GFX1),
  { "a78-16.31", 0x8000, 0xe66c92ee, REGION_GFX1, 0x48000, LOAD_NORMAL },
  { "a78-17.32", 0x8000, 0xd69762d5, REGION_GFX1, 0x50000, LOAD_NORMAL },
  { "a78-18.33", 0x8000, 0x47ee2544, REGION_GFX1, 0x58000, LOAD_NORMAL },
  { "a78-19.34", 0x8000, 0x1ceeb1fa, REGION_GFX1, 0x60000, LOAD_NORMAL },
  { "a78-20.35", 0x8000, 0x64322e24, REGION_GFX1, 0x68000, LOAD_NORMAL },
	/* 0x70000-0x7ffff empty */
  FILL(          0x70000, 0x10000, 0, GFX1),
	/* Located on CPU/Sound Board */
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_bublredux[] =
{
	/* ROMs banked at 8000-bfff */
  { "bb3", 0x08000, 0x198dc44e, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "bb5", 0x08000, 0xd29d3444, REGION_CPU1, 0x08000, LOAD_NORMAL },
  { "bb4", 0x08000, 0x9b819b62, REGION_CPU1, 0x10000, LOAD_NORMAL },
	/* 20000-2ffff empty */
   {           NULL,          0,          0, 0, 0, 0, },
};

#ifndef MAME_MCU
static struct INPUT_INFO input_bublbobl[] =
{
   INP1( COIN1, 0x010000, 0xFF ),
   INP1( COIN2, 0x010001, 0xFF ),
   INP1( TILT, 0x010002, 0xFF ),
   INP1( SERVICE, 0x010003, 0xFF ),

   INP1( P1_START, 0x010010, 0xFF ),
   INP1( P1_LEFT, 0x010013, 0xFF ),
   INP1( P1_RIGHT, 0x010014, 0xFF ),
   INP1( P1_B1, 0x010016, 0xFF ),
   INP1( P1_B2, 0x010015, 0xFF ),

   INP1( P2_START, 0x010020, 0xFF ),
   INP1( P2_LEFT, 0x010023, 0xFF ),
   INP1( P2_RIGHT, 0x010024, 0xFF ),
   INP1( P2_B1, 0x010026, 0xFF ),
   INP1( P2_B2, 0x010025, 0xFF ),

   END_INPUT
};
#else
static struct INPUT_INFO input_bublbobl[] =
{
   INP0( TILT,   0x010000, 1 ),
   INP0( SERVICE,0x010000, 2 ),
   INP1( COIN1,  0x010000, 4 ),
   INP1( COIN2,  0x010000, 8 ),

   INP0( P1_LEFT,  0x010003, 1 ),
   INP0( P1_RIGHT, 0x010003, 2 ),
   INP0( P1_B2,    0x010003, 0x10 ),
   INP0( P1_B1,    0x010003, 0x20 ),
   INP0( P1_START, 0x010003, 0x40 ),
   INP0( UNKNOWN,  0x010003, 0x80),

   INP0( P2_LEFT,  0x010004, 1 ),
   INP0( P2_RIGHT, 0x010004, 2 ),
   // INP0( TILT,     0x010004, 4 ),
   // INP0( SERVICE,  0x010004, 8 ),
   INP0( P2_B2,    0x010004, 0x10 ),
   INP0( P2_B1,    0x010004, 0x20 ),
   INP0( P2_START, 0x010004, 0x40 ),
   INP0( UNKNOWN,  0x010004, 0x80),

   END_INPUT
};
#endif

static struct DSW_DATA dsw_data_bubble_bobble_0[] =
{
   { _("Mode"),              0x05, 0x04 },
   { _("Japanese"),              0x05},
   { _("English"),               0x04},
   { _("Test (grid and input)"), 1 },
   { _("Test (ram and sound)/pause"), 0 },
   DSW_SCREEN( 0x02, 0x00),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_bubble_bobble_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("30k and 100k"),          0x0C},
   { _("20k and 80k"),           0x08},
   { _("40k and 200k"),          0x04},
   { _("50k and 250k"),          0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "5",                     0x20},
   { "1",                     0x10},
   { "2",                     0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("ROM type"),           0x80, 0x02 },
   { _("IC52=512kb, IC53=none"),    0x80},
   { _("IC52=256kb, IC53=256kb"),   0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_bublbobl[] =
{
#ifndef MAME_MCU
   { 0x010030, 0xFE, dsw_data_bubble_bobble_0 },
   { 0x010040, 0xFF, dsw_data_bubble_bobble_1 },
#else
   { 0x010001, 0xFE, dsw_data_bubble_bobble_0 },
   { 0x010002, 0xFF, dsw_data_bubble_bobble_1 },
#endif
   { 0,        0,    NULL,      },
};

static struct YM2203interface ym2203_interface =
{
     1,
     3000000,
     // { YM2203_VOL(255,255) },
     { 0x00ff20c0 },
   { 0 },
   { 0 },
   { 0 },
   { 0 },
   { z80_irq_handler },
};

static struct YM3812interface ym3526_interface =
{
   1,              // 1 chip
   3000000,        // 3.0 MHz
   { 255 },        // Volume (emu only)
   { NULL }
};

static struct SOUND_INFO sound_bublbobl[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { SOUND_YM3812,  &ym3526_interface,    },
   { 0,             NULL,                 },
};


/*************************************
   BUBBLE BOBBLE US with mode select
 *************************************/


static struct ROM_INFO rom_bublboblr[] =
{
	/* ROMs banked at 8000-bfff */
  { "a78-25.51", 0x08000, 0x2d901c9d, REGION_CPU1, 0x00000, LOAD_NORMAL },
	/* 20000-2ffff empty */
  { "a78-24.52", 0x10000, 0xb7afedc4, REGION_CPU1, 0x8000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};


/********************
   BUBBLE BOBBLE US
 ********************/


static struct ROM_INFO rom_bubboblr1[] =
{
	/* ROMs banked at 8000-bfff */
  { "a78-06.51", 0x08000, 0x32c8305b, REGION_CPU1, 0x00000, LOAD_NORMAL },
	/* 20000-2ffff empty */
  { "a78-21.52", 0x10000, 0x2844033d, REGION_CPU1, 0x08000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};


/*****************
   BOBBLE BOBBLE
 *****************/


static struct ROM_INFO rom_boblbobl[] =
{
	/* ROMs banked at 8000-bfff */
  { "bb3", 0x08000, 0x01f81936, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "bb5", 0x08000, 0x13118eb1, REGION_CPU1, 0x08000, LOAD_NORMAL },
  { "bb4", 0x08000, 0xafda99d8, REGION_CPU1, 0x10000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_sboblbob[] =
{
   INP0( COIN1, 0x00FF02, 0x08 ),
   INP0( COIN2, 0x00FF02, 0x04 ),
   INP0( TILT, 0x00FF03, 0x04 ),
   INP0( SERVICE, 0x00FF03, 0x08 ),

   INP0( P1_START, 0x00FF02, 0x40 ),
   INP0( P1_LEFT, 0x00FF02, 0x01 ),
   INP0( P1_RIGHT, 0x00FF02, 0x02 ),
   INP0( P1_B1, 0x00FF02, 0x20 ),
   INP0( P1_B2, 0x00FF02, 0x10 ),

   INP0( P2_START, 0x00FF03, 0x40 ),
   INP0( P2_LEFT, 0x00FF03, 0x01 ),
   INP0( P2_RIGHT, 0x00FF03, 0x02 ),
   INP0( P2_B1, 0x00FF03, 0x20 ),
   INP0( P2_B2, 0x00FF03, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_bobble_bobble_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("30k and 100k"),          0x0C},
   { _("20k and 80k"),           0x08},
   { _("40k and 200k"),          0x04},
   { _("50k and 250k"),          0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "5",                     0x20},
   { "1",                     0x10},
   { "2",                     0x00},
   { _("Monster Speed"),         0xC0, 0x04 },
   { _("Very High"),             0xC0},
   { _("High"),                  0x80},
   { _("Medium"),                0x40},
   { MSG_NORMAL,              0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_dland0[] =
{
  { _("Game"), 0x01, 2 },
  { _("Dream Land"), 0x01, 0x00 },
  { _("Super Dream Land"), 0x00, 0x00 },
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_dland1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("30k and 100k"),          0x0C},
   { _("20k and 80k"),           0x08},
   { _("40k and 200k"),          0x04},
   { _("50k and 250k"),          0x00},
  { MSG_LIVES, 0x30, 4 },
  { "1", 0x10, 0x00 },
  { "2", 0x00, 0x00 },
  { "3", 0x30, 0x00 },
  { _("100 (Cheat)"), 0x20, 0x00 },
   { _("Monster Speed"),         0x40, 0x04 },
   { _("Very High"),             0xC0},
   { _("High"),                  0x80},
   { _("Medium"),                0x40},
   { MSG_NORMAL,              0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_dland[] =
{
   { 0x00FF00, 0xFf, dsw_data_dland0 },
{ 0x00FF01, 0x7f, dsw_data_dland1 },
   { 0,        0,    NULL,      },
};

static struct DSW_INFO dsw_boblbobl[] =
{
   { 0x00FF00, 0xFE, dsw_data_bubble_bobble_0 },
   { 0x00FF01, 0x3F, dsw_data_bobble_bobble_1 },
   { 0,        0,    NULL,      },
};


/***********************
   SUPER BOBBLE BOBBLE
 ***********************/

static struct ROM_INFO rom_sboblbob[] =
{
	/* ROMs banked at 8000-bfff */
  { "bbb-3.rom", 0x08000, 0xf304152a, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "bb5", 0x08000, 0x13118eb1, REGION_CPU1, 0x08000, LOAD_NORMAL },
  { "bbb-4.rom", 0x08000, 0x94c75591, REGION_CPU1, 0x10000, LOAD_NORMAL },
	/* 20000-2ffff empty */
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_super_bobble_bobble_0[] =
{
   { _("Game"),                  0x01, 0x02 },
   { _("Super Bobble Bobble"),   0x00},
   { _("Bobble Bobble"),         0x01},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_super_bobble_bobble_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("30k and 100k"),          0x0C},
   { _("20k and 80k"),           0x08},
   { _("40k and 200k"),          0x04},
   { _("50k and 250k"),          0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "100",                   0x20},
   { "1",                     0x10},
   { "2",                     0x00},
   { _("Monster Speed"),         0xC0, 0x04 },
   { _("Very High"),             0xC0},
   { _("High"),                  0x80},
   { _("Medium"),                0x40},
   { MSG_NORMAL,              0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_sboblbob[] =
{
   { 0x00FF00, 0xFE, dsw_data_super_bobble_bobble_0 },
   { 0x00FF01, 0x3F, dsw_data_super_bobble_bobble_1 },
   { 0,        0,    NULL,      },
};


/******************************************************************************/

static UINT8 *RAM_INPUT;

static int mcu_addr;
static UINT8 mcu_latch;
#ifndef MAME_MCU
static UINT8 mcu_port_a, mcu_old_data;
#endif
static UINT8 *RAM_MCU, *ROM_SND, *RAM_SND;
static int nmi_enable, nmi_pending,irq_enable;

void BubbleBobble_mcu(int bih_count);
void BubbleBobble_mcu_reset(void);
static UINT8 portA_in,portA_out,ddrA;
static UINT8 portB_in,portB_out,ddrB;

UINT8 BubbleBobble_MCU_RDMEM(int a)
{
#ifdef MAME_MCU
    switch(a) {
    case 0: return (portA_out & ddrA) | (portA_in & ~ddrA);
    case 1: return (portB_out & ddrB) | (portB_in & ~ddrB);
    case 2: return RAM_INPUT[0] | 0xf0;
    default: return RAM_MCU[a];
    }
#else
   if (a == 0x02) /* COIN + TILT */
   {
      return 0xff - (RAM_INPUT[0x00] ? 4 : 0);
   }
   return RAM_MCU[a];
#endif
}

void BubbleBobble_MCU_WRMEM(int a, UINT8 data)
{
#ifdef MAME_MCU
   RAM_MCU[a] = data;
    switch(a) {
    case 0: portA_out = data; break;
    case 1:
	if ((ddrB & 0x01) && (~data & 0x01) && (portB_out & 0x01))
		portA_in = mcu_latch;
	if ((ddrB & 0x02) && (data & 0x02) && (~portB_out & 0x02)) /* positive edge trigger */
		mcu_addr = (mcu_addr & 0xff00) | portA_out;
//logerror("%04x: 68705 mcu_addr %02x\n",activecpu_get_pc(),portA_out);
	if ((ddrB & 0x04) && (data & 0x04) && (~portB_out & 0x04)) /* positive edge trigger */
		mcu_addr = (mcu_addr & 0x00ff) | ((portA_out & 0x0f) << 8);
	if ((ddrB & 0x10) && (~data & 0x10) && (portB_out & 0x10))
	{
		if (data & 0x08)	/* read */
		{
			if ((mcu_addr & 0x0800) == 0x0000)
			{
//logerror("%04x: 68705 read input port %02x\n",activecpu_get_pc(),mcu_addr);
				mcu_latch = RAM_INPUT[(mcu_addr & 3) + 1];
			}
			else if ((mcu_addr & 0x0c00) == 0x0c00)
			{
//logerror("%04x: 68705 read %02x from mcu_addr %04x\n",activecpu_get_pc(),bublbobl_mcu_sharedram[mcu_addr],mcu_addr);
				mcu_latch = RAM[0xfc00+(mcu_addr & 0x03ff)];
			}
			else {
			    print_debug("%04x: 68705 unknown read mcu_addr %04x\n",activecpu_get_pc(),mcu_addr);
			}
		}
		else	/* write */
		{
			if ((mcu_addr & 0x0c00) == 0x0c00)
			{
//logerror("%04x: 68705 write %02x to mcu_addr %04x\n",activecpu_get_pc(),portA_out,mcu_addr);
				RAM[0xfc00+(mcu_addr & 0x03ff)] = portA_out;
			}
			else {
			    print_debug("%04x: 68705 unknown write to mcu_addr %04x\n",activecpu_get_pc(),mcu_addr);
			}
		}
	}
	if ((ddrB & 0x20) && (~data & 0x20) && (portB_out & 0x20))
	{
		/* hack to get random EXTEND letters (who is supposed to do this? 68705? PAL?) */
	    // This part apparently happens during the irq, there is no irq
	    // for the68705 in raine, so we'll execute all this in the frame...
		RAM[0xfc7c] = rand()%6;
		cpu_interrupt(CPU_Z80_0, RAM[0xfc00]);

	}
	if ((ddrB & 0x40) && (~data & 0x40) && (portB_out & 0x40))
	{
	    print_debug("%04x: 68705 unknown port B bit %02x\n",activecpu_get_pc(),data);
	}
	if ((ddrB & 0x80) && (~data & 0x80) && (portB_out & 0x80))
	{
	    print_debug("%04x: 68705 unknown port B bit %02x\n",activecpu_get_pc(),data);
	}

	portB_out = data;
	break;
    case 4: ddrA = data; break;
    case 5: ddrB = data; break;
    }


#else
   UINT8 rising,falling;

   RAM_MCU[a] = data;
   if (a == 0x00) mcu_port_a = data;
   else if (a == 0x01) /* I/O control */
   {
      rising = (data ^ mcu_old_data) & data; /* only the rising-edge triggers these */
      falling = (data ^ mcu_old_data) & mcu_old_data; /* only the falling-edge triggers these */
      mcu_old_data = data;

      if (falling & 0x01) RAM_MCU[0x00] = mcu_latch;
      if (rising & 0x02) mcu_addr = (mcu_addr & 0xff00) | mcu_port_a;
      if (rising & 0x04) mcu_addr = (mcu_addr & 0x00ff) | ((mcu_port_a & 0x0f) << 8);
      if (falling & 0x10)
      {
         if (data & 0x08) /* read */
         {
            if ((mcu_addr & 0x0f00) == 0x0000)
            {
               switch(mcu_addr & 3)
               {
               case 0:        /* DSW0 */
                  mcu_latch = get_dsw(0); break;
               case 1:        /* DSW1 */
                  mcu_latch = get_dsw(1); break;
               case 2:        /* IN1 */
                  mcu_latch = 0xff - (RAM_INPUT[0x10] ? 0x40 : 0)
                                   - (RAM_INPUT[0x13] ? 0x01 : 0)
                                   - (RAM_INPUT[0x14] ? 0x02 : 0)
                                   - (RAM_INPUT[0x15] ? 0x10 : 0)
                                   - (RAM_INPUT[0x16] ? 0x20 : 0);
                  break;
               case 3:        /* IN2 */
                  mcu_latch = 0xff - (RAM_INPUT[0x20] ? 0x40 : 0)
                                   - (RAM_INPUT[0x23] ? 0x01 : 0)
                                   - (RAM_INPUT[0x24] ? 0x02 : 0)
                                   - (RAM_INPUT[0x25] ? 0x10 : 0)
                                   - (RAM_INPUT[0x26] ? 0x20 : 0);
                  break;
               }
            }
            else if ((mcu_addr & 0x0f00) == 0x0c00)
            {
               mcu_latch = RAM[0xfc00 + (mcu_addr & 0xff)];
            } else {
               /* reading from UNKNOWN? */
                  print_debug("Read from Unknown 0x%x\n", mcu_addr);
            }
         } else {    /* write */
            if ((mcu_addr & 0x0f00) == 0x0c00)
            {
               RAM[0xfc00 + (mcu_addr & 0xff)] = RAM_MCU[0x00];
            } else {
               /* writing to UNKNOWN? */
                  print_debug("Write to Unknown 0x%x=0x%x\n", mcu_addr, RAM_MCU[0x00]);
            }
         }
      }
      //if (falling & 0x20) set_IRQ_line((falling >> 5) & 1);
   }
#endif
}

/******************************************************************************/
/* Main Z80 read/write functions */
#if 0
/* A piece of history : how to update a real 256 colors palette in real time */
static void BublBobl_PalRAMWrite(UINT16 addr, UINT8 value)
{
   int n;
   UINT8 *p;

   if (RAM[addr] != value) {
     n = addr & 0x1fe;
     p = &RAM[0xf800 + n];
     n = (n >> 1) ^ 0x0f;

     RAM[addr] = value;
     pal[n].r = ((*p) & 0xf0) >> 2;
     pal[n].g = ((*p) & 0x0f) << 2;
     pal[n].b = ((*(p+1)) & 0xf0) >> 2;
   }
}
#endif

static void BublBobl_SoundCmd(UINT16 offset, UINT8 data)
{
	(void)(offset);
   latch = data;
   nmi_pending = 1;
   irq_enable = 1;
}

static UINT8 BublBobl_SoundCmd_read(UINT16 offset)
{
   return latch;
}

/******************************************************************************/
/* Bubble Bobble Z80 A Bankswitching                                          */
/******************************************************************************/

static UINT32 bank_sw;

static void init_bank_rom()
{
   setup_z80_frame(CPU_Z80_2,CPU_FRAME_MHz(3,60));

   z80_init_banks(0,REGION_ROM1,0x8000,0x4000);
   bank_sw = 0;
}

static void BublBobl_BankSwitch(UINT16 addr, UINT8 value)
{
    value = value & 3;
   if (bank_sw != (UINT32)(value))
   {
      bank_sw = value;
      z80_set_bank( 0,bank_sw );
      // memcpy(RAM+0x8000,ROM+0x8000+bank_sw*0x4000,0x4000);
   }
#if 0
   static int reset_mcu, reset_cpub;
   if ((value & 0x10) != reset_cpub) {
       reset_cpub = value & 10;
       cpu_reset(CPU_Z80_1);
   }
   if ((value & 0x20) != reset_mcu) {
       reset_mcu = value & 0x20;
       BubbleBobble_mcu_reset();
   }
#endif
}

/******************************************************************************/
/* Bubble Bobble YM2203                                                       */
/******************************************************************************/

// YM2203

static UINT8 BB_YM2203Read(UINT16 offset)
{
   /* Timer A controls SFX
    * Timer B controls MUSIC
    */
   if(!(offset&1)){
     return YM2203_status_port_0_r(offset); // Set timers ON
   }
   else{
      return YM2203_read_port_0_r(0);
   }
}

static void BB_YM2203Write(UINT16 offset, UINT8 data)
{
   if(!(offset&1)){
     YM2203_control_port_0_w(offset,data);
   }
   else{
      YM2203_write_port_0_w(offset,data);
   }
}

// YM3526

static UINT8 BB_YM3526Read(UINT16 offset)
{
	(void)(offset);
  //int status =  YM3526_status_port_0_r(offset);
  //return status;
  return 0x80;  //It ignores the timers anyway? Just set the IRQ bit.
}

static void BB_YM3526Write(UINT16 offset, UINT8 data)
{
   if(!(offset&1)){
     YM3526_control_port_0_w(offset,data);//      ym3526_reg = data;
   }
   else{
      YM3812_write_port_0_w(offset,data);
   }
}

static UINT8 BB_Unknown(UINT16 offset)
{
	(void)(offset);
   return 0x00;   /* b001 needs bit 0 to be clear */
}

static void SelectNMI(UINT16 offset, UINT8 data)
{
	(void)(data);
   switch(offset & 3)
   {
   case 0: RAM[0xfa00] = data; break;
   case 1: nmi_enable = 1;
	   if (nmi_pending) {
	       cpu_int_nmi(CPU_Z80_2);
	       nmi_pending = 0;
	   }
	   break;
   case 2: nmi_enable = 0; break;
   }
}

/******************************************************************************/
/* Bubble Bobble Load/Save Extra Stuff                                        */
/******************************************************************************/

static void BublBoblLoadUpdate(void)
{
   UINT32 ta;

   // force a bankswitch refresh

   ta = bank_sw;
   bank_sw = 0xFF;
   BublBobl_BankSwitch(0,ta);
   portA_out = RAM_MCU[0];
   portB_out = RAM_MCU[1];
   ddrA = RAM_MCU[4];
   ddrB = RAM_MCU[5];
   RAM[0x10000] = 0x03;
   if (!RAM[0x10001] && !RAM[0x10002]) {
       // Old dsw ? Copy to the new location
       RAM[0x10001] = RAM[0x10030];
       RAM[0x10002] = RAM[0x10040];
   }
}

static void BublBoblAddSaveData(void)
{
   AddLoadCallback(BublBoblLoadUpdate);

   AddSaveData(SAVE_USER_0, (UINT8 *)&bank_sw,        sizeof(bank_sw));
   AddSaveData(SAVE_USER_1, (UINT8 *)&mcu_addr,       sizeof(mcu_addr));
   AddSaveData(SAVE_USER_2, (UINT8 *)&mcu_latch,      sizeof(mcu_latch));
#ifdef MAME_MCU
   AddSaveData(SAVE_USER_4, (UINT8 *)&portA_in,     sizeof(portA_in));
#else
   AddSaveData(SAVE_USER_3, (UINT8 *)&mcu_port_a,     sizeof(mcu_port_a));
   AddSaveData(SAVE_USER_4, (UINT8 *)&mcu_old_data,   sizeof(mcu_old_data));
#endif
   AddSaveData(SAVE_USER_7, (UINT8 *)&latch,      sizeof(latch));
   AddSaveData(SAVE_USER_8, (UINT8 *)&nmi_enable,     sizeof(nmi_enable));
   AddSaveData(SAVE_USER_9, (UINT8 *)&nmi_pending,    sizeof(nmi_pending));
   AddSaveData(SAVE_USER_10, RAM_MCU,                 0x80);
}

/******************************************************************************/

static UINT8 HACK[3][2];

static int no_mcu;

static void bubl_reset() {
    memset(RAM+0xc000, 0, 0x3000); // RAM + common RAM !
    memset(RAM_SND, 0, 0x1000);
    irq_enable = 0;
    nmi_enable = 0;
    nmi_pending = 0;
}

static void load_bublbobl(void)
{
/*ﾄﾄﾄﾄ Set up ROM/RAM ﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄﾄ*/

    set_reset_function(bubl_reset);
    init_assoc( 3);
   RAMSize=0x10000 + 0x100 + 0x1000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM_INPUT = RAM + 0x10000;
   RAM_SND   = RAM + 0x10100;

   // Skip Idle Z80
   HACK[0][0] = ROM[0x01ED];
   HACK[0][1] = ROM[0x01EE];
   // Instead of 1ed: jr $1ed (infinite loop)
   ROM[0x01ED]=0xD3;  // OUTA (AAh)
   ROM[0x01EE]=0xAA;  //

   if (is_current_game("boblbobl")) {
       no_mcu = 1;
       // it's probably something to avoid to switch to a non existing blank
       // bank, it could be replaced by a rom_fill with 0, but I'll keep this.
       ROM[0x9a71 + 0xC000]=0x00;
       ROM[0x9a72 + 0xC000]=0x00;
       ROM[0x9a73 + 0xC000]=0x00;

       ROM[0xa4af + 0xC000]=0x00;
       ROM[0xa4b0 + 0xC000]=0x00;
       ROM[0xa4b1 + 0xC000]=0x00;

       ROM[0xa55d + 0xC000]=0x00;
       ROM[0xa55e + 0xC000]=0x00;
       ROM[0xa55f + 0xC000]=0x00;

       ROM[0xb561 + 0xC000]=0x00;
       ROM[0xb562 + 0xC000]=0x00;
       ROM[0xb563 + 0xC000]=0x00;
   } else if (is_current_game("sboblbob") || is_current_game("bublredux"))
       // Not sure if this one needs any bank adjustment, there was never
       // any before anyway...
       no_mcu = 1;
   else if (is_current_game("dland")) {
       no_mcu = 1;
       // rearrange gfx to original format
       int i;
       UINT8* src = load_region[REGION_GFX1];
       for (i = 0; i < 0x40000; i++)
	   src[i] = BITSWAP8(src[i],7,6,5,4,0,1,2,3);

       for (i = 0x40000; i < 0x80000; i++)
	   src[i] = BITSWAP8(src[i],7,4,5,6,3,0,1,2);
   } else
       no_mcu = 0;

   SetStopZ80Mode2(0x01ED);

   init_bank_rom();

   nmi_enable = 0;
   nmi_pending = 0;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k); // col_map_12bit_RRRRGGGGBBBBxxxx_Rev );
   InitPaletteMap(RAM+0xf800, 0x10, 0x10, 0x1000);

   /* Copy ROM code into our virtual image (copy 1st bank as well) */
   memcpy(RAM+0x0000, ROM, 0xC000);
   memset(RAM+0xC000, 0x00, 0x4000);

   AddZ80AROMBase(RAM, 0x38, 0x66);

   AddZ80AReadByte(0x01ed, 0x01ee, NULL, HACK[0]); // hide speed hack
   AddZ80AReadByte(0x0000, 0xBFFF, NULL,                    NULL);         // Z80 ROM (bank switched)
   // AddZ80ARead(0xfc22, 0xfc22, read_input, NULL);
   if (no_mcu)
       AddZ80AReadByte(0xC000, 0xFF03, NULL,                    RAM+0xC000);   // Z80 RAM
   else
       AddZ80AReadByte(0xC000, 0xFFFF, NULL,                    RAM+0xC000);   // Z80 RAM
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0xC000, 0xF9FF, NULL,                   RAM+0xC000);   // Z80 RAM + palette
   if (no_mcu)
       AddZ80AWriteByte(0xFC00, 0xFeFF, NULL,                   RAM+0xFC00);   // mostly ram
   else
       AddZ80AWriteByte(0xFC00, 0xFFFF, NULL,                   RAM+0xFC00);   // Z80/MCU RAM
   AddZ80AWriteByte(0xFB40, 0xFB40, BublBobl_BankSwitch,    NULL);         // Bank switch
   AddZ80AWriteByte(0xFA00, 0xFA00, BublBobl_SoundCmd,      NULL);         // Sound command
   // AddZ80AWriteByte(0xFA03, 0xFA03, BublBobl_resetsound,      NULL);
   // AddZ80AWriteByte(0xFA40, 0xFA40, NULL,                   RAM+0xFA40);   // ???
   // AddZ80AWriteByte(0xFA80, 0xFA80, NULL,                   RAM+0xFA80);   // Watchdog
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);         // <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   // Fix Checksum

   Z80ROM[0x018C]=0xC9;

   // Skip Idle Z80

   HACK[1][0] = Z80ROM[0x000A];
   HACK[1][1] = Z80ROM[0x000B];
   /* Replaces a jp $a, so this cpu is active only during irq */
   Z80ROM[0x000A]=0xD3;  // OUTA (AAh)
   Z80ROM[0x000B]=0xAA;  //

   SetStopZ80BMode2(0x000A);

   /* 2nd Z80 */
   AddZ80BROMBase(Z80ROM, 0x38, 0x66);

   AddZ80BReadByte(0x000a, 0x000b, NULL, HACK[1]); // hide speed hack
   AddZ80BReadByte(0x0000, 0x7FFF, NULL,                   Z80ROM+0x0000);  // ROM
   AddZ80BRW(0xE000, 0xF7FF, NULL,                   RAM+0xE000);  // COMMON RAM
   AddZ80BReadByte(0x8000, 0xFFFF, DefBadReadZ80,          NULL);  // <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);   // <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   /* Hell, lets have a 3rd Z80, why not... */

   ROM_SND = load_region[REGION_ROM3];

   // Skip Idle Z80
   // -------------

   HACK[2][0] = ROM_SND[0x0178];
   HACK[2][1] = ROM_SND[0x0179];
   ROM_SND[0x0178]=0xD3;  // OUT (AAh), A
   ROM_SND[0x0179]=0xAA;  //

   SetStopZ80CMode2(0x016D);

   AddZ80CROMBase(ROM_SND, 0x38, 0x66);

   AddZ80CReadByte(0x0178, 0x0179, NULL, HACK[2]); // hide speed hack
   AddZ80CReadByte(0x0000, 0x7FFF, NULL,              ROM_SND);      // ROM
   AddZ80CReadByte(0x8000, 0x8FFF, NULL,              RAM_SND);      // SOUND RAM
   AddZ80CReadByte(0x9000, 0x9001, BB_YM2203Read,     NULL);         // YM2203
   AddZ80CReadByte(0xA000, 0xA000, BB_YM3526Read,     NULL);         // YM3526
   //AddZ80CReadByte(0xB000, 0xB000, NULL,              &latch);   // SOUND COMMAND
   AddZ80CReadByte(0xB000, 0xB000, BublBobl_SoundCmd_read, NULL);   // SOUND COMMAND
   AddZ80CReadByte(0xB001, 0xB001, BB_Unknown,        NULL);         // ???
   AddZ80CReadByte(0xE000, 0xE000, BB_Unknown,        NULL);         // Diagnostic ROM (not used)
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,     NULL);         // <bad writes>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0x8000, 0x8FFF, NULL,             RAM_SND);      // SOUND RAM
   AddZ80CWriteByte(0x9000, 0x9001, BB_YM2203Write,   NULL);         // YM2203
   AddZ80CWriteByte(0xA000, 0xA001, BB_YM3526Write,   NULL);         // YM3526
   AddZ80CWriteByte(0xB000, 0xB002, SelectNMI,        NULL);         // NMI enable
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,   NULL);         // <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,         NULL);         // <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,        NULL);         // Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,       NULL);         // <bad reads>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   // MCU

   RAM_MCU = load_region[REGION_ROM4];

   mcu_addr = 0;
   BubbleBobble_mcu_reset();

   BublBoblAddSaveData();
}

static void execute_bublbobl(void)
{
   if (!no_mcu)
       BubbleBobble_mcu(BIH_COUNT);

   if (!irq_enable ) {
       // Use the old code while the audio cpu is not started
#define CPU_SLICE 16

       int ta;
       for(ta=0;ta<CPU_SLICE;ta++)
       {
	   if(cpu_get_pc(CPU_Z80_0) != 0x01ED)
	   {
	       cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(6,60)/CPU_SLICE);  // Main Z80 8MHz (60fps)
	   }

	   if(cpu_get_pc(CPU_Z80_1) != 0x000A)
	   {
	       cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(6,60)/CPU_SLICE);  // Sub Z80 8MHz (60fps)
	   }

	   if (nmi_pending && nmi_enable)
	   {
	       cpu_int_nmi(CPU_Z80_2);
	       nmi_pending = 0;
	   }
	   cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(3,60)/CPU_SLICE);  // Sound Z80 8MHz (60fps)

	   triger_timers();

       }
   } else {
       INT32 frame = CPU_FRAME_MHz(3,60); // audio cpu
       while (frame > 0) {
	   switch_cpu(CPU_Z80_2);
	   UINT32 elapsed = execute_one_z80_audio_frame(frame);
	   if(cpu_get_pc(CPU_Z80_0) != 0x01ED)
	   {
	       cpu_execute_cycles(CPU_Z80_0, elapsed*2);  // 6 MHz
	   }

	   if(cpu_get_pc(CPU_Z80_1) != 0x000A)
	   {
	       cpu_execute_cycles(CPU_Z80_1, elapsed*2);  // Sub Z80 6MHz
	   }

	   if (nmi_pending && nmi_enable)
	   {
	       cpu_int_nmi(CPU_Z80_2);
	       nmi_pending = 0;
	   }
	   frame -= elapsed;
       }
       /* Ok, now dirty hack :
	* apprently the game can be saturated with bubbles, in this case it
	* slows down, but then the cpus start to fill their stacks with
	* interrupts and since the stack is very small, it finally crashes
	* everything ! I guess there is a problem in the way raine handles
	* irqs for the z80 here, there should probably never be more than 1
	* irq waiting, and that's probably the reason why it crashes here.
	* Anyway the other fix is just to check if the cpus have finished
	* their normal work, in this case they are back to the pc expected
	* for the speed hack, and if not add some cycles. It works, it's dirty
	* and can't be done by the original hardware, but it's quite fun to
	* have the game never slowing down... I'll keep it for now ! */
       int round = 0;
       while(cpu_get_pc(CPU_Z80_0) != 0x01ED && round < 10) {
	   // printf("pc0 %x round %d sp %x\n",cpu_get_pc(CPU_Z80_0),round++,Z80_context[0].z80sp);
	   cpu_execute_cycles(CPU_Z80_0,CPU_FRAME_MHz(6,60));
	   round++;
       }
       /* There is something weird here. If sending irqs from the start, then
	* the main cpu does a double initialization, starting the small music
	* twice. This doesn't happen if the speed hack is enabled !
	* Now the speed hack shouldn't interfere with this, I should check it
	* later. Anyway the workaround is to enable irqs only once the audio
	* cpu starts to receive commands... for now I use this + the speed
	* hack without checking why it interferes... */
       if (no_mcu)
	   cpu_interrupt(CPU_Z80_0, 0x38);
       else
	   cpu_interrupt(CPU_Z80_0, RAM[0xfc00]);
       /*
	* This makes the EXTEND letters random. Neither the game nor the MCU
	* appears to be doing this (why not???), so we do...
	*/
       if (!no_mcu) {
	   RAM[0xfc7c] ++;
	   RAM[0xfc7c] %= 6;
       }

       round = 0;
       while(cpu_get_pc(CPU_Z80_1) != 0x000A &&
	      cpu_get_pc(CPU_Z80_1) != 0x1b3 && round < 10) {
	   // What's this 1b3 pc ? Apparently it can very rarely stop there
	   // but didn't find in which conditions. It's better to keep it here
	   // anyway just in case
	   // printf("pc1 %x round %d sp %x\n",cpu_get_pc(CPU_Z80_1),round++,Z80_context[1].z80sp);
	   cpu_execute_cycles(CPU_Z80_1,CPU_FRAME_MHz(6,60));
	   round++;
       }
       cpu_interrupt(CPU_Z80_1, 0x38);
   }

#if 0
   // Piece of history, I keep it here !
   /* The timers expire, on average, every 51.4 Hz.
    * This can be achieved by doing an interrupt 6 out of every 7 frames
    * from a 60Hz timer (51.4 = 60*6/7)
    *
    * NOTE: 51.4Hz is carefully calculated, and wasn't just obtained
    *       by twiddling it till it worked. Oh no. Honest, guv. ;-)
    */
   if (tq) cpu_interrupt(CPU_Z80_2, 0xff);
   tq++; tq %= 7;
#endif
}

static void draw_bubble_bobble(void)
{
   int ta,x,y;
   UINT8 *map;

   int offs, height, goffs;
   int sx,sy,xc,yc;
   int gfx_num,gfx_attr,gfx_offs;

   // Palette needs updating (eg. loadgame)

   // No Solid BG0

   ClearPaletteMap();
   MAP_PALETTE_MAPPED_NEW(
			  0xe,
			  16,
			  map
			  );

   clear_game_screen(ReadLong(&map[0]));

   // OBJECT

   sx = 0;
   for (offs=0;offs<0x300;offs+=4)
   {
      /* skip empty sprites */
      if (*(UINT32 *)(&RAM[offs+0xdd00]) == 0) continue;

      gfx_num = RAM[0xdd00 + offs + 1];
      gfx_attr = RAM[0xdd00 + offs + 3];

      if ((gfx_num & 0x80) == 0)      /* 16x16 sprites */
      {
         gfx_offs = ((gfx_num & 0x1f) * 0x80) + ((gfx_num & 0x60) >> 1) + 12;
         height = 2;
      }
      else    /* tilemaps (each sprite is a 16x256 column) */
      {
         gfx_offs = ((gfx_num & 0x3f) * 0x80);
         height = 32;
      }

      if ((gfx_num & 0xc0) == 0xc0)
         sx += 16;
      else
      {
         sx = RAM[0xdd00 + offs + 2];
         if (gfx_attr & 0x40) sx -= 256;
      }
      sy = 256 - height*8 - (RAM[0xdd00 + offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++)
         {
            ta = (ReadWord(&RAM[0xc000+goffs]) & 0x3FF) | ((gfx_attr << 10) & 0x3C00);
	    x = 32 + (sx + xc * 8);
	    y = 32 + (((sy + yc * 8) & 0xff) - 16);
	    drawspr_8x8_flip(0,x,y,ta,((RAM[0xc001 + goffs] >> 2) & 0xF),
		    (RAM[0xc001+goffs]>>6) & 3);


            goffs += 2;
         }

         gfx_offs += 64;
      }
   }
}

static gfx_layout charlayout =
{
	8, 8,
	RGN_FRAC(1,2),
	4,
	{ 0, 4, RGN_FRAC(1,2), RGN_FRAC(1,2)+4 },
	{ 3, 2, 1, 0, 8+3, 8+2, 8+1, 8+0 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
	16*8
};

static struct GFX_LIST bub_gfx[] =
{
    { REGION_GFX1, &charlayout, },
    { 0, NULL }
};

static struct VIDEO_INFO video_bublbobl =
{
   draw_bubble_bobble,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   bub_gfx
};
static struct DIR_INFO dir_boblbobl[] =
{
   { "bobble_bobble", },
   { "boblbobl", },
   { ROMOF("bublbobl"), },
   { CLONEOF("bublbobl"), },
   { NULL, },
};
static struct DIR_INFO dir_bublbobl[] =
{
   { "bubble_bobble", },
   { "bublbobl", },
   { "bublbob1", },
   { NULL, },
};
GME( bublbobl, "Bubble Bobble", TAITO, 1986, GAME_PLATFORM,
	.long_name_jpn = "バブルボブル",
	.board = "A78",
);
CLNE( boblbobl, bublbobl, "Bobble Bobble", BOOTLEG, 1986, GAME_PLATFORM,
	.input = input_sboblbob,
	.dsw = dsw_boblbobl,
	.long_name_jpn = "ボブルボブル",
);
CLNEI( dland, bublbobl, "Dream Land / Super dream land (bootleg of bubble bobble)", BOOTLEG, 1987, GAME_PLATFORM,
	.input = input_sboblbob,
	.dsw = dsw_dland,
);
static struct DIR_INFO dir_bublboblr[] =
{
   { "bubble_bobble_romstar", },
   { "bublbobr", },
   { "bublboblr", },
   { ROMOF("bublbobl"), },
   { CLONEOF("bublbobl"), },
   { NULL, },
};
CLNE( bublboblr, bublbobl, "Bubble Bobble (US mode select)", TAITO, 1986, GAME_PLATFORM,
	.long_name_jpn = "バブルボブル (US mode select)",
	.board = "A78",
);
CLNEI( bublcave, bublbobl, "Bubble Bobble Lost Cave (Ver 1.2)", HACK, 2013, GAME_PLATFORM);
CLNEI( bublredux, bublbobl, "Bubble Bobble Redux (With Level Skipper)", HACK, 2013, GAME_PLATFORM,
	.input = input_sboblbob,
	.dsw = dsw_boblbobl,
	);
static struct DIR_INFO dir_bubboblr1[] =
{
   { "bubble_bobble_romstar2", },
   { "bubbobr1", },
   { "bubbolbr1", },
   { ROMOF("bublbobl"), },
   { CLONEOF("bublbobl"), },
   { NULL, },
};
CLNE( bubboblr1, bublbobl,"Bubble Bobble (US)", TAITO, 1986, GAME_PLATFORM,
	.long_name_jpn = "バブルボブル (US)",
	.board = "A78",
);
static struct DIR_INFO dir_sboblbob[] =
{
   { "super_bobble_bobble", },
   { "sboblbob", },
   { ROMOF("bublbobl"), },
   { CLONEOF("bublbobl"), },
   //{ ROMOF("boblbobl"), },	// mulitple romof/cloneof if we want full merging
   //{ CLONEOF("boblbobl"), },	// but that will probably break rom merge tools ;)
   { NULL, },
};
CLNE( sboblbob, bublbobl,"Super Bobble Bobble", BOOTLEG, 1986, GAME_PLATFORM,
	.input = input_sboblbob,
	.dsw = dsw_sboblbob,
	.long_name_jpn = "スーパーボブルボブル",
);

