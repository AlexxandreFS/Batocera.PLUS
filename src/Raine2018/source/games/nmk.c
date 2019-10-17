/******************************************************************************/
/*                                                                            */
/*                  NMK - NIHON MAICON KAIHATSU  UPL - ???                    */
/*   CPU: M68000                                                              */
/* SOUND: M6295x2                                                             */
/* VIDEO: VARIES [1/2 BG0; 1 OBJECT; 1 FG0]                                   */
/*                                                                            */
/* The NMK004 CPU might be a Toshiba TLCS-90 class CPU with internal ROM in the */
/* 0000-1fff range. */
/* See http://mamelife.blogspot.com/2005/03/nmk-sound.html
   and http://mamelife.blogspot.com/2005/03/how-to-dump-nmk004.html
   for the details about the findings about this chip */

/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "decode.h"
#include "3812intf.h"
#include "sasound.h"		// sample support routines
#include "adpcm.h"
#include "mame/handlers.h"
#include "emumain.h"
#include "timer.h"
#include "2203intf.h"
#include "savegame.h"
#include "blit.h" // clear_game_screen (when bg0 is disabled)
#include "nmk004.h"
#include "sdl/gui.h" // goto_debuger
#include "profile.h" // fps

static void (*ExecuteSoundFrame)();	// Pointer to ExecuteSoundFrame rountine (sound cpu work for 1 frame), used for pausegame + playsound

/*

About:

 NMK is an abbreviation of "Nihon Maicon Kaihatsu".
 "Nihon" means "Japan",
 "Maicon" is an abbrev. of "Micro Computer", with a Japanese accent,
 "Kaihatsu" means "Development".

 However, NMK no longer develop videogames.

Supported romsets:

0 - Bomb Jack Twin         - NMK [NMK]  9th Mar 1992 / Youichi Koyama
1 - Hacha Mecha Fighter    - NMK [NMK] 19th Sep 1991 / Youichi Koyama
2 - Bio Ship Paladin       - NMK [UPL]          1990 / Itsam Matarca
3 - Mustang                - NMK [UPL] 25th May 1990 / Youichi Koyama
4 - Task Force Harrier     - NMK [SAM]          1989 / ?
5 - Thunder Dragon         - NMK [TCM]  4th Jun 1991 / Youichi Koyama
6 - Thunder Dragon Bootleg - NMK [TCM]  4th Jun 1991 / Youichi Koyama
7 - Strahl                 - NMK [UPL]          1992 / ?
8 - Macross                - NMK [BAN] 11th Jun 1992 / Youichi Koyama
9 - Macross2               - NMK [BAN] ?

Macross2 does not work (yet) because the memory mapping is totally different.

Saboten Bombers - NMK - (c) 1992 <-- Undumped??
Black Heart - UPL - 1991.
	Saboten Bombers, Hacha Meche Fighter and Thunder Dragon all use the same
	Dipswitch settings.  Raine reads and uses these in reverse order.
	Bit1 of DSW1 (bit8 in the manual) is unused _most_ of the time. - BaT

Todo:

Hacha Mecha Fighter is protected, has no sound
Bio Ship Paladin is protected, has no sound
Mustang has no sound
Task Force Harrier protected (no controls) has no sound, scrolling problem.
Thunder Dragon and bootleg have no sound
Strahl has no sound, possible eeprom in test mode

Task Force Harrier  UPL-89050
USAAF Mustang       UPL-90058
Bio Ship Paladin    UPL-90062

*/

#define ROM_COUNT       9

static int romset,nb_sprites,req_int2;


static struct ROM_INFO rom_bioship[] =
{
   {            "1", 0x00020000, 0x820ef303, 0, 0, 0, },
   {            "2", 0x00020000, 0xacf56afb, 0, 0, 0, },
   {            "6", 0x00010000, 0x5f39a980, REGION_CPU2, 0, LOAD_NORMAL, },
   {            "7", 0x00010000, 0x2f3f5a10, 0, 0, 0, },
   {            "8", 0x00010000, 0x75a46fea, 0, 0, 0, },
   {            "9", 0x00010000, 0xd91448ee, 0, 0, 0, },
   {     "sbs-g.01", 0x00080000, 0x21302e78, 0, 0, 0, },
   {     "sbs-g.02", 0x00080000, 0xf31eb668, 0, 0, 0, },
   {     "sbs-g.03", 0x00080000, 0x60e00d7b, 0, 0, 0, },
   {     "sbs-g.04", 0x00080000, 0x7c74cc4e, REGION_SOUND1, 0x20000, LOAD_NORMAL, },
   {     "sbs-g.05", 0x00080000, 0xf0a782e3, REGION_SOUND2, 0x20000, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_tdragon2[] =
{
   INP0( COIN1, 0x010000, 0x01 ),
   INP0( COIN2, 0x010000, 0x02 ),
   INP0( TILT, 0x010000, 0x20 ),
   INP0( SERVICE, 0x010000, 0x04 ),

   INP0( P1_START, 0x010000, 0x08 ),
   INP0( P1_UP, 0x010002, 0x08 ),
   INP0( P1_DOWN, 0x010002, 0x04 ),
   INP0( P1_LEFT, 0x010002, 0x02 ),
   INP0( P1_RIGHT, 0x010002, 0x01 ),
   INP0( P1_B1, 0x010002, 0x10 ),
   INP0( P1_B2, 0x010002, 0x20 ),
   INP0( P1_B3, 0x010002, 0x40 ),
   INP0( P1_B4, 0x010002, 0x80 ),

   INP0( P2_START, 0x010000, 0x10 ),
   INP0( P2_UP, 0x010003, 0x08 ),
   INP0( P2_DOWN, 0x010003, 0x04 ),
   INP0( P2_LEFT, 0x010003, 0x02 ),
   INP0( P2_RIGHT, 0x010003, 0x01 ),
   INP0( P2_B1, 0x010003, 0x10 ),
   INP0( P2_B2, 0x010003, 0x20 ),
   INP0( P2_B3, 0x010003, 0x40 ),
   INP0( P2_B4, 0x010003, 0x80 ),

   END_INPUT
};

static struct INPUT_INFO input_ssmissin[] =
{
   INP0( COIN1, 0x010000, 0x01 ),
   INP0( COIN2, 0x010000, 0x02 ),
   INP0( TILT, 0x010000, 0x20 ),
   INP0( SERVICE, 0x010000, 0x04 ),

   INP0( P1_START, 0x010000, 0x08 ),
   INP0( P1_UP, 0x010004, 0x08 ),
   INP0( P1_DOWN, 0x010004, 0x04 ),
   INP0( P1_LEFT, 0x010004, 0x02 ),
   INP0( P1_RIGHT, 0x010004, 0x01 ),
   INP0( P1_B1, 0x010004, 0x10 ),
   INP0( P1_B2, 0x010004, 0x20 ),
   INP1( P1_B3, 0x010004, 0x40 ),
   INP1( P1_B4, 0x010004, 0x80 ),

   INP0( P2_START, 0x010000, 0x10 ),
   INP0( P2_UP, 0x010005, 0x08 ),
   INP0( P2_DOWN, 0x010005, 0x04 ),
   INP0( P2_LEFT, 0x010005, 0x02 ),
   INP0( P2_RIGHT, 0x010005, 0x01 ),
   INP0( P2_B1, 0x010005, 0x10 ),
   INP0( P2_B2, 0x010005, 0x20 ),
   INP1( P2_B3, 0x010005, 0x40 ),
   INP1( P2_B4, 0x010005, 0x80 ),

   END_INPUT
};

/* The inputs of tharrier are quite particular : instead of using the
 * input_mode of the other games, it uses a pointer from ram to read the
 * inputs, initalised by or.b #8,$f9f1a and or.b #2,$f9f1c which puts
 * $80202 in $f9f1a which is then used for the inputs instead of $80002.
 * $80002 is still used though, particularly for the hiscore table and to
 * start a game. */

static struct INPUT_INFO input_tforceh[] =
{
  INP1( COIN1, 0x10000, 0x01 ),
  INP1( COIN2, 0x10000, 0x02 ),
  INP1( SERVICE, 0x10000, 0x04 ),
  INP1( P1_START, 0x10000, 0x08 ),
  INP1( P2_START, 0x10000, 0x10 ),

  INP1( P1_START, 0x10002, 0x01 ),
  INP1( P2_START, 0x10002, 0x02 ),
  INP1( COIN2, 0x10002, 0x20 ),
  INP1( COIN1, 0x10002, 0x80 ),
  INP1( P2_START, 0x10003, 0x01 ),
  // hiscore :
   INP1( P1_RIGHT, 0x010002, 0x08 ),
   INP1( P1_B1, 0x010002, 0x02 ),
   INP1( P1_LEFT, 0x010002, 0x10 ),

  INP1( P1_B1, 0x10202, 0x02 ),
  INP1( P1_B2, 0x10202, 0x04 ),
  INP1( P1_RIGHT, 0x10202, 0x08 ),
  INP1( P1_LEFT, 0x10202, 0x10 ),
  INP1( P1_DOWN, 0x10202, 0x20 ),
  INP1( P1_UP, 0x10202, 0x40 ),
  INP1( P1_B3, 0x10202, 0x80 ),

  INP1( P2_B1, 0x10203, 0x02 ),
  INP1( P2_B2, 0x10203, 0x04 ),
  INP1( P2_RIGHT, 0x10203, 0x08 ),
  INP1( P2_LEFT, 0x10203, 0x10 ),
  INP1( P2_DOWN, 0x10203, 0x20 ),
  INP1( P2_UP, 0x10203, 0x40 ),
  INP1( P2_B3, 0x10203, 0x80 ),
   END_INPUT
};

static struct DSW_DATA dsw_data_ssmissin_2[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  DSW_UNUSED( 0x0000, 0x0002),
  { MSG_DIFFICULTY, 0x000c, 4 },
  { _("Easy") , 0x0004},
  { _("Normal") , 0x000c},
  { _("Hard") , 0x0008},
  { _("Hardest") , 0x0000},
  DSW_UNUSED( 0x0000, 0x0010),
  DSW_UNUSED( 0x0000, 0x0020),
  { MSG_LIVES, 0x00c0, 4 },
  { "1" , 0x0000},
  { "2" , 0x0040},
  { "3" , 0x00c0},
  { "4" , 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_ssmissin_8[] =
{
  { MSG_COINAGE, 0xe0, 8 },
  { MSG_4COIN_1PLAY, 0x20},
  { MSG_3COIN_1PLAY, 0xa0},
  { MSG_2COIN_1PLAY, 0x60},
  { MSG_1COIN_1PLAY, 0xe0},
  { MSG_1COIN_2PLAY, 0xc0},
  { MSG_1COIN_3PLAY, 0x40},
  { MSG_1COIN_4PLAY, 0x80},
  { MSG_FREE_PLAY, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_ssmissin[] =
{
  { 0x10006, 0xff, dsw_data_ssmissin_2 },
  { 0x10007, 0xe0, dsw_data_ssmissin_8 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_bio_ship_paladin_0[] =
{
   DSW_SCREEN( 0x01, 0x00),
   { MSG_DIFFICULTY,          0x06, 0x04 },
   { MSG_NORMAL,              0x06},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x04},
   { MSG_EASY,                0x00},
   DSW_TEST_MODE( 0x00, 0x08),
   DSW_DEMO_SOUND( 0x20, 0x00),
   { _("Lives"),                 0xC0, 0x04 },
   { "3",                     0xC0},
   { "5",                     0x40},
   { "4",                     0x80},
   { "2",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_bio_ship_paladin_1[] =
{
   { MSG_COIN2,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x1C},
   { MSG_1COIN_2PLAY,         0x0C},
   { MSG_1COIN_3PLAY,         0x14},
   { MSG_1COIN_4PLAY,         0x04},
   { MSG_2COIN_1PLAY,         0x18},
   { MSG_3COIN_1PLAY,         0x08},
   { MSG_4COIN_1PLAY,         0x10},
   { MSG_5COIN_1PLAY,         0x00},
   { MSG_COIN1,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0xE0},
   { MSG_1COIN_2PLAY,         0x60},
   { MSG_1COIN_3PLAY,         0xA0},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0xC0},
   { MSG_3COIN_1PLAY,         0x40},
   { MSG_4COIN_1PLAY,         0x80},
   { MSG_5COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_bioship[] =
{
   { 0x010008, 0xFF, dsw_data_bio_ship_paladin_0 },
   { 0x01000A, 0xFF, dsw_data_bio_ship_paladin_1 },
   { 0,        0,    NULL,      },
};

static struct YM2203interface ym2203_interface_15 =
{
	1,			/* 1 chip */
	1500000,
	{ YM2203_VOL(230,230) },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ z80_irq_handler }
};

static struct YM2203interface ym2203_nmk004_interface =
{
	1,			/* 1 chip */
	1500000,
	{ YM2203_VOL(230,230) },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ NMK004_irq }
	/* This irq handler obliges to simulate z80 timers on the 68000.
	   Easier than what I thought, see execute_bioship for the gory details ! */
};

static struct OKIM6295interface okim6295_interface_dual =
{
	2,              					/* 2 chips */
	{ 16000000/4/165, 16000000/4/165 },	/* 24242Hz frequency? */
	{ REGION_SOUND1, REGION_SOUND2 },	/* memory region */
	{ 100, 100 }							/* volume */
};

static struct OKIM6295interface okim6295_interface_ssmissin =
{
	1,              	/* 1 chip */
	{ 8000000/4/165 },	/* ? unknown */
	{ REGION_SOUND1 },	/* memory region */
	{ 255 }				/* volume */
};

static struct SOUND_INFO sound_tdragon2[] =
{
   { SOUND_YM2203,  &ym2203_interface_15, },
   { SOUND_M6295,   &okim6295_interface_dual, },
   { 0,             NULL,                 },
};

static struct SOUND_INFO sound_hachamf[] =
{
   { SOUND_YM2203,  &ym2203_nmk004_interface, },
   { SOUND_M6295,   &okim6295_interface_dual, },
   { 0,             NULL,                 },
};

static struct SOUND_INFO sound_ssmissin[] =
{
   { SOUND_M6295,   &okim6295_interface_ssmissin, },
   { 0,             NULL,                 },
};

static struct SOUND_INFO sound_bjtwin[] =
{
   { SOUND_M6295,   &okim6295_interface_dual, },
   { 0,             NULL,                 },
};


static struct ROM_INFO rom_bjtwin[] =
{
   {      "93087-5.bin", 0x00100000, 0xbb06245d, 0, 0, 0, },
   {      "93087-6.bin", 0x00100000, 0x372d46dd, REGION_SOUND1, 0x00000, LOAD_NORMAL, },
   {      "93087-7.bin", 0x00100000, 0x8da67808, REGION_SOUND2, 0x00000, LOAD_NORMAL, },
   {       "93087-4.bin", 0x00100000, 0x8a4f26d0, 0, 0, 0, },
   {       "93087-3.bin", 0x00010000, 0xaa13df7c, 0, 0, 0, },
   {       "93087-2.bin", 0x00020000, 0x30ff678a, 0, 0, 0, },
   {       "93087-1.bin", 0x00020000, 0x93c84e2d, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_bomb_jack_twin_0[] =
{
   DSW_SCREEN( 0x01, 0x00),
   { _("Start Level"),           0x0E, 0x08 },
   { _("Japan"),                 0x0E},
   { _("Nevada"),                0x0C},
   { _("England"),               0x0A},
   { _("Germany"),               0x08},
   { _("Korea"),                 0x06},
   { _("Thailand"),              0x04},
   { _("Hong Kong"),             0x02},
   { _("China"),                 0x00},
   { MSG_DIFFICULTY,          0x30, 0x04 },
   { MSG_NORMAL,              0x30},
   { MSG_EASY,                0x20},
   { MSG_HARD,                0x10},
   { MSG_HARDEST,             0x00},
   { _("Lives"),                 0xC0, 0x04 },
   { "3",                     0xC0},
   { "4",                     0x80},
   { "2",                     0x40},
   { "1",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_bomb_jack_twin_1[] =
{
   DSW_DEMO_SOUND( 0x00, 0x02),
   { MSG_COIN2,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x1C},
   { MSG_1COIN_2PLAY,         0x0C},
   { MSG_1COIN_3PLAY,         0x14},
   { MSG_1COIN_4PLAY,         0x04},
   { MSG_2COIN_1PLAY,         0x18},
   { MSG_3COIN_1PLAY,         0x08},
   { MSG_4COIN_1PLAY,         0x10},
   { MSG_FREE_PLAY,              0x00},
   { MSG_COIN1,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0xE0},
   { MSG_1COIN_2PLAY,         0x60},
   { MSG_1COIN_3PLAY,         0xA0},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0xC0},
   { MSG_3COIN_1PLAY,         0x40},
   { MSG_4COIN_1PLAY,         0x80},
   { MSG_FREE_PLAY,              0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_bjtwin[] =
{
   { 0x010008, 0xFF, dsw_data_bomb_jack_twin_0 },
   { 0x01000A, 0xFF, dsw_data_bomb_jack_twin_1 },
   { 0,        0,    NULL,      },
};


static struct ROM_INFO rom_sabotenb[] =
{
   {    "ic100.sb5", 0x00200000, 0xb20f166e, 0, 0, 0, },
   {     "ic30.sb6", 0x00100000, 0x288407af, REGION_SOUND1, 0x00000, LOAD_NORMAL, },
   {     "ic27.sb7", 0x00100000, 0x43e33a7e, REGION_SOUND2, 0x00000, LOAD_NORMAL, },
   {     "ic32.sb4", 0x00200000, 0x24c62205, 0, 0, 0, },
   {     "ic35.sb3", 0x00010000, 0xeb7bc99d, 0, 0, 0, },
   {     "ic75.sb2", 0x00040000, 0x367e87b7, 0, 0, 0, },
   {     "ic76.sb1", 0x00040000, 0xb2b0b2cf, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_saboten_bombers_0[] =
{
   DSW_SCREEN( 0x01, 0x00),
   { _("Language"),              0x02, 0x02 },
   { _("Japanese"),              0x02},
   { _("English"),               0x00},
   { MSG_DIFFICULTY,          0x0c, 0x04 },
   { MSG_NORMAL,              0x0c},
   { MSG_EASY,                0x08},
   { MSG_HARD,                0x04},
   { MSG_HARDEST,             0x00},
   { _("Lives"),                 0xC0, 0x04 },
   { "3",                     0xC0},
   { "2",                     0x80},
   { "4",                     0x40},
   { "1",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_saboten_bombers_1[] =
{
   DSW_DEMO_SOUND( 0x00, 0x02),
   { MSG_COIN1,               0xE0, 0x08 }, // Looks ugly and out of order, but it's correct!
   { MSG_1COIN_1PLAY,         0xE0},
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_1COIN_4PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x60},
   { MSG_3COIN_1PLAY,         0xA0},
   { MSG_4COIN_1PLAY,         0x20},
   { MSG_FREE_PLAY,              0x00},
   { MSG_COIN2,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x1C},
   { MSG_1COIN_2PLAY,         0x18},
   { MSG_1COIN_3PLAY,         0x08},
   { MSG_1COIN_4PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x0c},
   { MSG_3COIN_1PLAY,         0x14},
   { MSG_4COIN_1PLAY,         0x04},
   { MSG_FREE_PLAY,              0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_sabotenb[] =
{
   { 0x010008, 0xFF, dsw_data_saboten_bombers_0 },
   { 0x01000A, 0xFF, dsw_data_saboten_bombers_1 },
   { 0,        0,    NULL,      },
};





static struct ROM_INFO rom_macross[] =
{
  { "921a03", 0x80000, 0x33318d55 , REGION_ROM1, 0x00000, LOAD_SWAP_16 },
  { "921a02", 0x10000, 0x77c082c7 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "921a01", 0x020000, 0xbbd8242d , 0 /* REGION_GFX1 */, 0x000000, 0 },
  { "921a04", 0x200000, 0x4002e4bb , 0 /* REGION_GFX2 */, 0x000000, 0 },
  { "921a07", 0x200000, 0x7d2bf112 , 0 /* REGION_GFX3 */, 0x000000, 0 },
  { "921a05", 0x080000, 0xd5a1eddd , REGION_SMP1, 0x020000, LOAD_NORMAL },
  { "921a06", 0x080000, 0x89461d0f , REGION_SMP2, 0x020000, LOAD_NORMAL },
/*  { "921a08", 0x0100, 0xcfdbb86c , REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "921a09", 0x0100, 0x633ab1c9 , REGION_PROMS, 0x0100, LOAD_NORMAL },
  { "921a10", 0x0020, 0x8371e42d , REGION_PROMS, 0x0200, LOAD_NORMAL }, */
  /* Notice that the PROMS were in the mame struct, but they are unused ! */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_blkheart[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "blkhrt.7",  0x5bd248c0 , "blkhrt.6",  0x6449e50d ),
  { "4.bin", 0x10000, 0x7cefa295 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3.bin", 0x020000, 0xa1ab3a16 , 0, 0, 0 }, // REGION_GFX1, 0x000000, 0 },
  { "90068-5.bin", 0x100000, 0xa1ab4f24 , 0, 0, 0 }, // REGION_GFX2, 0x000000, 0 },
  { "90068-8.bin", 0x100000, 0x9d3204b2 , 0, 0, 0 }, // REGION_GFX3, 0x000000, 0 },
  { "90068-2.bin", 0x080000, 0x3a583184 , REGION_SMP1, 0x020000, LOAD_NORMAL },
  { "90068-1.bin", 0x080000, 0xe7af69d2 , REGION_SMP2, 0x020000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_blkhearj[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "7.bin",  0xe0a5c667 , "6.bin",  0x7cce45e8 ),
  { "4.bin", 0x10000, 0x7cefa295 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3.bin", 0x020000, 0xa1ab3a16 , 0, 0, 0 }, // REGION_GFX1, 0x000000, 0 },
  { "90068-5.bin", 0x100000, 0xa1ab4f24 , 0, 0, 0 }, // REGION_GFX2, 0x000000, 0 },
  { "90068-8.bin", 0x100000, 0x9d3204b2 , 0, 0, 0 }, // REGION_GFX3, 0x000000, 0 },
  { "90068-2.bin", 0x080000, 0x3a583184 , REGION_SMP1, 0x020000, LOAD_NORMAL },
  { "90068-1.bin", 0x080000, 0xe7af69d2 , REGION_SMP2, 0x020000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_macross2[] =
{
  { "mcrs2j.3", 0x80000, 0x36a618fe , REGION_ROM1, 0x00000, LOAD_SWAP_16 },
  { "mcrs2j.2", 0x20000, 0xb4aa8ac7 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "mcrs2j.2", 0x20000, 0xb4aa8ac7 , REGION_ROM2, 0x8000, LOAD_NORMAL },
  { "mcrs2j.1", 0x020000, 0xc7417410 , REGION_GFX1, 0x000000, 0 },
  { "bp932an.a04", 0x200000, 0xc4d77ff0 , REGION_GFX2, 0x000000, 0 },
  { "bp932an.a07", 0x200000, 0xaa1b21b9 , REGION_GFX3, 0x000000, LOAD_SWAP_16 },
  { "bp932an.a08", 0x200000, 0x67eb2901 , REGION_GFX3, 0x200000, LOAD_SWAP_16 },
  { "bp932an.a06", 0x200000, 0xef0ffec0 , REGION_SMP1, 0x40000, LOAD_NORMAL },
  { "bp932an.a05", 0x100000, 0xb5335abb , REGION_SMP2, 0x40000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_macross_2[] =
{
  DSW_SERVICE( 0, 0x01),
  { MSG_UNKNOWN, 0x02, 2 },
  { MSG_OFF, 0x02},
  { MSG_ON, 0x00},
  DSW_SCREEN( 0x04, 0x00),
  { _("Language"), 0x08, 2 },
  { _("English") , 0x00},
  { _("Japanese") , 0x08},
  { MSG_DIFFICULTY, 0x30, 4 },
  { _("Easy") , 0x10},
  { _("Normal") , 0x30},
  { _("Hard") , 0x20},
  { _("Hardest") , 0x00},
  { MSG_LIVES, 0xc0, 4 },
  { "1" , 0x00},
  { "2" , 0x40},
  { "3" , 0xc0},
  { "4" , 0x80},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_macross_3[] =
{
  { MSG_COIN2, 0x0f, 16 },
  { MSG_4COIN_1PLAY, 0x04},
  { MSG_3COIN_1PLAY, 0x0a},
  { MSG_2COIN_1PLAY, 0x01},
  { MSG_5COIN_3PLAY, 0x00},
  { MSG_3COIN_2PLAY, 0x02},
  { MSG_4COIN_3PLAY, 0x08},
  { MSG_1COIN_1PLAY, 0x0f},
  { MSG_3COIN_4PLAY, 0x0c},
  { MSG_2COIN_3PLAY, 0x0e},
  { MSG_1COIN_2PLAY, 0x07},
  { MSG_2COIN_5PLAY, 0x06},
  { MSG_1COIN_3PLAY, 0x0b},
  { MSG_1COIN_4PLAY, 0x03},
  { MSG_1COIN_5PLAY, 0x0d},
  { MSG_1COIN_6PLAY, 0x05},
  { MSG_1COIN_7PLAY, 0x09},
  { MSG_COIN1, 0xf0, 16 },
  { MSG_4COIN_1PLAY, 0x40},
  { MSG_3COIN_1PLAY, 0xa0},
  { MSG_2COIN_1PLAY, 0x10},
  { MSG_3COIN_2PLAY, 0x20},
  { MSG_4COIN_3PLAY, 0x80},
  { MSG_1COIN_1PLAY, 0xf0},
  { MSG_3COIN_4PLAY, 0xc0},
  { MSG_2COIN_3PLAY, 0xe0},
  { MSG_1COIN_2PLAY, 0x70},
  { MSG_2COIN_5PLAY, 0x60},
  { MSG_1COIN_3PLAY, 0xb0},
  { MSG_1COIN_4PLAY, 0x30},
  { MSG_1COIN_5PLAY, 0xd0},
  { MSG_1COIN_6PLAY, 0x50},
  { MSG_1COIN_7PLAY, 0x90},
  { MSG_FREE_PLAY, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_tdragon2[] =
{
   { 0x010008, 0xF7, dsw_data_macross_2 },
   { 0x01000A, 0xFF, dsw_data_macross_3 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_blkheart_2[] =
{
  DSW_SCREEN( 0x01, 0x00),
  DSW_SERVICE( 0, 0x02),
  { MSG_DIFFICULTY, 0x04, 2 },
  { _("Normal") , 0x04},
  { _("Hard") , 0x00},
  { MSG_UNKNOWN, 0x08, 2 },
  { MSG_OFF, 0x08},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x00},
  { MSG_LIVES, 0xc0, 4 },
  { "2" , 0x40},
  { "3" , 0xc0},
  { "4" , 0x80},
  { "5" , 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_blkheart_3[] =
{
  { MSG_UNKNOWN, 0x01, 2 },
  { MSG_OFF, 0x01},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x02, 2 },
  { MSG_OFF, 0x02},
  { MSG_ON, 0x00},
  { MSG_COIN2, 0x1c, 8 },
  { MSG_4COIN_1PLAY, 0x10},
  { MSG_3COIN_1PLAY, 0x08},
  { MSG_2COIN_1PLAY, 0x18},
  { MSG_1COIN_1PLAY, 0x1c},
  { MSG_1COIN_1PLAY, 0x0c},
  { MSG_1COIN_3PLAY, 0x14},
  { MSG_1COIN_4PLAY, 0x04},
  { MSG_FREE_PLAY, 0x00},
  { MSG_COIN1, 0xe0, 8 },
  { MSG_4COIN_1PLAY, 0x80},
  { MSG_3COIN_1PLAY, 0x40},
  { MSG_2COIN_1PLAY, 0xc0},
  { MSG_1COIN_1PLAY, 0xe0},
  { MSG_1COIN_1PLAY, 0x60},
  { MSG_1COIN_3PLAY, 0xa0},
  { MSG_1COIN_4PLAY, 0x20},
  { MSG_FREE_PLAY, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_blkheart[] =
{
   { 0x010008, 0xFF, dsw_data_blkheart_2 },
   { 0x01000A, 0xFF, dsw_data_blkheart_3 },
   { 0,        0,    NULL,      },
};


static struct ROM_INFO rom_hachamf[] =
{
   {   "hmf_02.rom", 0x00080000, 0x3f1e67f2, REGION_SOUND1, 0x20000, LOAD_NORMAL, },
   {   "hmf_03.rom", 0x00080000, 0xb25ed93b, REGION_SOUND2, 0x20000, LOAD_NORMAL, },
   {   "hmf_01.rom", 0x00010000, 0x9e6f48fc, REGION_ROM2, 0, LOAD_NORMAL, },
   {   "hmf_04.rom", 0x00080000, 0x05a624e3, 0, 0, 0, },
   {   "hmf_05.rom", 0x00020000, 0x29fb04a2, 0, 0, 0, },
  LOAD8_16(  REGION_CPU1,  0,  0x00020000,
              "hmf_07.rom",  0x9d847c31,   "hmf_06.rom",  0xde6408a0),
   {   "hmf_08.rom", 0x00100000, 0x7fd0f556, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_hachamf_2[] =
{
  { MSG_UNKNOWN, 0x01, 2 },
  { MSG_OFF, 0x01},
  { MSG_ON, 0x00},
  { _("Language"), 0x02, 2 },
  { _("English"), 0x00},
  { _("Japanese"), 0x02},
  { MSG_DIFFICULTY, 0x0c, 4 },
  { MSG_EASY, 0x04},
  { MSG_NORMAL, 0x0c},
  { MSG_HARD, 0x08},
  { MSG_HARDEST, 0x00},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x00},
  { MSG_LIVES, 0xc0, 4 },
  { "1", 0x00},
  { "2", 0x40},
  { "3", 0xc0},
  { "4", 0x80},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_hachamf_3[] =
{
  { MSG_COIN1, 0x7, 8 },
  { MSG_4COIN_1PLAY, 0x1},
  { MSG_3COIN_1PLAY, 0x2},
  { MSG_2COIN_1PLAY, 0x3},
  { MSG_1COIN_1PLAY, 0x7},
  { MSG_1COIN_1PLAY, 0x6},
  { MSG_1COIN_3PLAY, 0x5},
  { MSG_1COIN_4PLAY, 0x4},
  { MSG_FREE_PLAY, 0x0},
  { MSG_COIN2, 0x38, 8 },
  { MSG_4COIN_1PLAY, 0x8},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x18},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_1COIN_3PLAY, 0x28},
  { MSG_1COIN_4PLAY, 0x20},
  { MSG_FREE_PLAY, 0x0},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_hachamf[] =
{
  { 0x10008, 0xfd, dsw_data_hachamf_2 },
  { 0x10009, 0xff, dsw_data_hachamf_3 },
  { 0, 0, NULL }
};


static struct ROM_INFO rom_mustang[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "2.bin",  0xbd9f7c89, "3.bin",  0x0eec36a5),
  { "90058-7", 0x10000, 0x920a93c8, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "90058-1", 0x20000, 0x81ccfcad, 0 /* REGION_GFX1 */, 0x00000, 0 },
  { "90058-4", 0x80000, 0xa07a2002, 0 /* REGION_GFX2 */, 0x000000, 0 },
  { "90058-8", 0x80000, 0x560bff04, 0 /* REGION_GFX3 */, 0x00000, 0 },
  { "90058-9", 0x80000, 0xb9d72a03, 0 /* REGION_GFX3 */, 0x00001, 0 },
  { "90058-5", 0x80000, 0xc60c883e, REGION_SMP1, 0x20000, LOAD_NORMAL },
  { "90058-6", 0x80000, 0x233c1776, REGION_SMP2, 0x20000, LOAD_NORMAL },
  { "10.bpr", 0x100, 0x633ab1c9, REGION_PROMS, 0x00000, LOAD_NORMAL },
  { "90058-11", 0x100, 0xcfdbb86c, REGION_PROMS, 0x00100, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_tharrier_2[] =
{
   DSW_TEST_MODE( 0x00, 0x01),
   // The following bits are not read by tharrier, but maybe by mustang...
  DSW_DEMO_SOUND( 0x0002, 0x0000),
  { MSG_COIN2, 0x001c, 8 },
  { MSG_4COIN_1PLAY, 0x0010},
  { MSG_3COIN_1PLAY, 0x0008},
  { MSG_2COIN_1PLAY, 0x0018},
  { MSG_1COIN_1PLAY, 0x001c},
  { MSG_1COIN_2PLAY, 0x000c},
  { MSG_1COIN_3PLAY, 0x0014},
  { MSG_1COIN_4PLAY, 0x0004},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN1, 0x00e0, 8 },
  { MSG_4COIN_1PLAY, 0x0080},
  { MSG_3COIN_1PLAY, 0x0040},
  { MSG_2COIN_1PLAY, 0x00c0},
  { MSG_1COIN_1PLAY, 0x00e0},
  { MSG_1COIN_2PLAY, 0x0060},
  { MSG_1COIN_3PLAY, 0x00a0},
  { MSG_1COIN_4PLAY, 0x0020},
  { MSG_FREE_PLAY, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_mustang_3[] =
{
  DSW_SCREEN( 0x1, 0x0),
  { MSG_UNKNOWN, 0x2, 2 },
  { MSG_OFF, 0x2},
  { MSG_ON, 0x0},
  { MSG_DIFFICULTY, 0xc, 4 },
  { MSG_EASY, 0x4},
  { MSG_NORMAL, 0xc},
  { MSG_HARD, 0x8},
  { MSG_HARDEST, 0x0},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x0},
  { MSG_LIVES, 0xc0, 4 },
  { "2", 0x40},
  { "3", 0xc0},
  { "4", 0x80},
  { "5", 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_mustang[] =
{
   { 0x010005, 0xFF, dsw_data_tharrier_2 },
   { 0x010004, 0xFF, dsw_data_mustang_3 },
   { 0,        0,    NULL,      },
};



static struct DSW_DATA dsw_data_acrobatm_2[] =
{
  DSW_DEMO_SOUND( 0x0000, 0x0001),
  DSW_SCREEN( 0x0002, 0x0000),
  { MSG_COIN2, 0x001C, 8 },
  { MSG_5COIN_1PLAY, 0x0000},
  { MSG_4COIN_1PLAY, 0x0010},
  { MSG_3COIN_1PLAY, 0x0008},
  { MSG_2COIN_1PLAY, 0x0018},
  { MSG_1COIN_1PLAY, 0x001C},
  { MSG_1COIN_1PLAY, 0x000C},
  { MSG_1COIN_3PLAY, 0x0014},
  { MSG_1COIN_4PLAY, 0x0004},
  { MSG_COIN1, 0x00E0, 8 },
  { MSG_5COIN_1PLAY, 0x0000},
  { MSG_4COIN_1PLAY, 0x0080},
  { MSG_3COIN_1PLAY, 0x0040},
  { MSG_2COIN_1PLAY, 0x00C0},
  { MSG_1COIN_1PLAY, 0x00E0},
  { MSG_1COIN_1PLAY, 0x0060},
  { MSG_1COIN_3PLAY, 0x00A0},
  { MSG_1COIN_4PLAY, 0x0020},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_acrobatm_3[] =
{
  DSW_SERVICE( 0, 0x01),
  { MSG_EXTRA_LIFE, 0x06, 4 },
  { _("50k and 100k") , 0x02},
  { _("100k and 100k") , 0x06},
  { _("100k and 200k") , 0x04},
  { _("None") , 0x00},
  { _("Language"), 0x08, 2 },
  { _("English") , 0x00},
  { _("Japanese") , 0x08},
  { MSG_DIFFICULTY, 0x30, 4 },
  { _("Easy") , 0x00},
  { _("Normal") , 0x30},
  { _("Hard") , 0x10},
  { _("Hardest") , 0x20},
  { MSG_LIVES, 0xc0, 4 },
  { "2" , 0x40},
  { "3" , 0xc0},
  { "4" , 0x80},
  { "5" , 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_acrobatm[] =
{
  { 0x10008, 0xfe, dsw_data_acrobatm_2 },
  { 0x1000a, 0xf7, dsw_data_acrobatm_3 },
  { 0, 0, NULL }
};

static struct ROM_INFO rom_strahl[] =
{
   { "str6b1w1.776", 0x00080000, 0xbb1bb155, 0, 0, 0, },
   { "str7b2r0.275", 0x00040000, 0x5769e3e1, 0, 0, 0, },
   { "str8pmw1.540", 0x00080000, 0x01d6bb6a, REGION_SOUND1, 0x20000, LOAD_NORMAL, },
   { "str9pew1.639", 0x00080000, 0x6bb3eb9f, REGION_SOUND2, 0x20000, LOAD_NORMAL, },
   {  "strahl-1.83", 0x00020000, 0xafc3c4d6, 0, 0, 0, },
   {  "strahl-2.82", 0x00020000, 0xc9d008ae, 0, 0, 0, },
   {  "strahl-3.73", 0x00010000, 0x2273b33e, 0, 0, 0, },
   {  "strahl-4.66", 0x00010000, 0x60a799c4, REGION_CPU2, 0, LOAD_NORMAL, },
   {  "strl3-01.32", 0x00080000, 0xd8337f15, 0, 0, 0, },
   {  "strl4-02.57", 0x00080000, 0x2a38552b, 0, 0, 0, },
   {  "strl5-03.58", 0x00080000, 0xa0e7d210, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_acrobatm[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "02_ic100.bin",  0x3fe487f4 , "01_ic101.bin",  0x17175753 ),
  { "03_ic79.bin", 0x10000, 0xd86c186e , 0 /* REGION_GFX1 */, 0x000000, 0 },

  { "09_ic8.bin",  0x100000,0x7c12afed, 0 /* REGION_GFX2 */, 0x100000, 0 },

  { "07_ic42.bin", 0x100000,0x5672bdaa, 0 /* REGION_GFX3 */, 0x000000, 0 },
  { "08_ic29.bin", 0x80000, 0xb4c0ace3, 0 /* REGION_GFX3 */, 0x100000, 0 },


  { "04_ic74.bin", 0x10000, 0x176905fb , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "05_ic54.bin", 0x80000, 0x3b8c2b0e, REGION_SMP1, 0x020000, LOAD_NORMAL },
  { "06_ic53.bin", 0x80000, 0xc1517cd4, REGION_SMP2, 0x020000, LOAD_NORMAL },
  //{ "snd", 0x10000, 0x00000000 , REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_strahl_2[] =
{
  { MSG_COIN1, 0x07, 8 },
  { MSG_5COIN_1PLAY, 0x00},
  { MSG_4COIN_1PLAY, 0x01},
  { MSG_3COIN_1PLAY, 0x02},
  { MSG_2COIN_1PLAY, 0x03},
  { MSG_1COIN_1PLAY, 0x07},
  { MSG_1COIN_1PLAY, 0x06},
  { MSG_1COIN_3PLAY, 0x05},
  { MSG_1COIN_4PLAY, 0x04},
  { MSG_COIN2, 0x38, 8 },
  { MSG_5COIN_1PLAY, 0x00},
  { MSG_4COIN_1PLAY, 0x08},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x18},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_1COIN_3PLAY, 0x28},
  { MSG_1COIN_4PLAY, 0x20},
  DSW_SCREEN( 0x40, 0x00),
  DSW_DEMO_SOUND( 0x00, 0x80),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_strahl_3[] =
{
  { MSG_LIVES, 0x03, 4 },
  { "2" , 0x02},
  { "3" , 0x03},
  { "4" , 0x01},
  { "5" , 0x00},
  { MSG_DIFFICULTY, 0x0c, 4 },
  { _("Easy") , 0x08},
  { _("Normal") , 0x0c},
  { _("Hard") , 0x04},
  { _("Hardest") , 0x00},
  DSW_UNUSED( 0x00, 0x10),
  { MSG_EXTRA_LIFE, 0x60, 4 },
  { _("100k and every 200k") , 0x40},
  { _("200k and every 200k") , 0x60},
  { _("300k and every 300k") , 0x20},
  { _("None") , 0x00},
  DSW_SERVICE( 0, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_strahl[] =
{
   { 0x010008, 0xFF, dsw_data_strahl_2 },
   { 0x01000A, 0xFF, dsw_data_strahl_3 },
   { 0,        0,    NULL,      },
};


static struct ROM_INFO rom_tforceh[] =
{
   {            "1", 0x00010000, 0xc7402e4a, 0, 0, 0, },
  LOAD8_16(  REGION_CPU1,  0,  0x00020000,
                       "2",  0x78923aaa,            "3",  0x99cea259),
   {           "12", 0x00010000, 0xb959f837, REGION_CPU2, 0, LOAD_NORMAL, },
   {      "89050-4", 0x00080000, 0x64d7d687, 0, 0, 0, },
   {      "89050-8", 0x00080000, 0x11ee4c39, REGION_SOUND1, 0x20000, LOAD_NORMAL },
   {     "89050-10", 0x00080000, 0x893552ab, REGION_SOUND2, 0x20000, LOAD_NORMAL },
   {     "89050-13", 0x00080000, 0x24db3fa4, 0, 0, 0, },
   {     "89050-17", 0x00080000, 0x7f715421, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_INFO dsw_tforceh[] =
{
  { 0x10005, 0xff, dsw_data_tharrier_2 },
  // { 0x10004, 0xff, dsw_data_tharrier_3 }, (not read)
  { 0, 0, NULL }
};


static struct ROM_INFO rom_tdragon[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "thund.8",  0xedd02831, "thund.7",  0x52192fe5),
  { "thund.6", 0x20000, 0xfe365920, 0 /* REGION_GFX1 */, 0x000000, 0 },
  { "thund.5", 0x100000, 0xd0bde826, 0 /* REGION_GFX2 */, 0x000000, 0 },
  { "thund.4", 0x100000, 0x3eedc2fe, 0 /* REGION_GFX3 */, 0x000000, 0 },
  { "thund.1", 0x10000, 0xbf493d74, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "thund.3", 0x80000, 0xae6875a8, REGION_SMP1, 0x20000, LOAD_NORMAL },
  { "thund.2", 0x80000, 0xecfea43e, REGION_SMP2, 0x20000, LOAD_NORMAL },
/*   { "9.bin", 0x0100, 0xcfdbb86c, REGION_PROMS, 0x0000, LOAD_NORMAL }, */
/*   { "10.bin", 0x0100, 0xe6ead349, REGION_PROMS, 0x0100, LOAD_NORMAL }, */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_tdragonb[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "td_04.bin",  0xe8a62d3e, "td_03.bin",  0x2fa1aa04),
/* Ignored : 	ROM_COPY( REGION_CPU2, 0, 0x018000, 0x08000 ) */
  { "td_02.bin", 0x10000, 0x99ee7505, REGION_ROM2, 0, LOAD_NORMAL },
  { "td_08.bin", 0x20000, 0x5144dc69, 0 /* REGION_GFX1 */, 		0x000000, 0 },
  { "td_06.bin", 0x80000, 0xc1be8a4d, 0 /* REGION_GFX2 */, 		0x000000, 0 },
  { "td_07.bin", 0x80000, 0x2c3e371f, 0 /* REGION_GFX2 */, 		0x080000, 0 },
  { "td_10.bin", 0x080000, 0xbfd0ec5d, 0 /* REGION_GFX3 */, 	0x000000, 0 },
  { "td_09.bin", 0x080000, 0xb6e074eb, 0 /* REGION_GFX3 */, 	0x000001, 0 },
  { "td_01.bin", 0x10000, 0xf6f6c4bf, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_tdragon2[] =
{

  { "6.bin", 0x80000, 0x310d6bca , REGION_ROM1, 0x00000, LOAD_SWAP_16 },
  { "5.bin", 0x20000, 0xb870be61 , REGION_ROM2, 0x00000, LOAD_NORMAL },

  { "5.bin", 0x20000, 0xb870be61 , REGION_ROM2, 0x08000, LOAD_NORMAL },

  { "1.bin", 0x020000, 0xd488aafa , 0 /* REGION_GFX1 */, 0x000000, 0 },

  { "ww930914.2", 0x200000, 0xf968c65d , 0 /* REGION_GFX2 */, 0x000000, 0 },

  { "ww930917.7", 0x200000, 0xb98873cb , REGION_GFX3, 0x000000, LOAD_SWAP_16 },

  { "ww930918.8", 0x200000, 0xbaee84b2 , REGION_GFX3, 0x200000, LOAD_SWAP_16 },

  { "ww930916.4", 0x200000, 0x07c35fe6 , REGION_SMP1, 0x040000, LOAD_NORMAL },

  { "ww930915.3", 0x200000, 0x82025bab , REGION_SMP2, 0x040000, LOAD_NORMAL },
/*   { "9.bpr", 0x0100, 0x435653a2 , REGION_PROMS, 0x0000, LOAD_NORMAL }, */
/*   { "10.bpr", 0x0100, 0xe6ead349 , REGION_PROMS, 0x0100, LOAD_NORMAL }, */
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_ssmissin[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "ssm15.166",  0xaff15927, "ssm14.165",  0xeda61b74  ),

  { "ssm16.172", 0x20000, 0x5cf6eb1f , 0 /* REGION_GFX1 */, 0x000000, 0 },

  { "ssm17.147", 0x080000, 0xc9c28455 , REGION_GFX2,0x000000, LOAD_NORMAL },
  { "ssm18.148", 0x080000, 0xebfdaad6 , REGION_GFX2,0x080000, LOAD_NORMAL },

  LOAD8_16(  REGION_GFX3, 0x000000,  0x080000,
            "ssm19.33",  0xb1943657, "ssm20.34",  0xa0c16c4d ),

  { "ssm11.188", 0x08000, 0x8be6dce3 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "ssm13.190", 0x20000, 0x618f66f0 , REGION_SMP1, 0x00000, LOAD_NORMAL },

  { "ssm12.189", 0x80000, 0xe8219c83 , REGION_SMP1, 0x80000, LOAD_NORMAL },
/*   { "ssm-pr2.113", 0x0100, 0xcfdbb86c , REGION_PROMS, 0x0000, LOAD_NORMAL }, */
/*   { "ssm-pr1.114", 0x0200, 0xed0bd072 , REGION_PROMS, 0x0100, LOAD_NORMAL }, */
  { NULL, 0, 0, 0, 0, 0 }
};


static struct DSW_DATA dsw_data_tdragon_2[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  { MSG_UNKNOWN, 0x0002, 2 },
  { MSG_OFF, 0x0002},
  { MSG_ON, 0x0000},
  { MSG_DIFFICULTY, 0x000c, 4 },
  { MSG_EASY, 0x0004},
  { MSG_NORMAL, 0x000c},
  { MSG_HARD, 0x0008},
  { MSG_HARDEST, 0x0000},
  { MSG_UNKNOWN, 0x0010, 2 },
  { MSG_OFF, 0x0010},
  { MSG_ON, 0x0000},
  { MSG_UNKNOWN, 0x0020, 2 },
  { MSG_OFF, 0x0020},
  { MSG_ON, 0x0000},
  { MSG_LIVES, 0x00c0, 4 },
  { "1", 0x0000},
  { "2", 0x0040},
  { "3", 0x00c0},
  { "4", 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_tdragon_3[] =
{
  { MSG_COIN1, 0x0007, 8 },
  { MSG_4COIN_1PLAY, 0x0004},
  { MSG_3COIN_1PLAY, 0x0005},
  { MSG_2COIN_1PLAY, 0x0006},
  { MSG_1COIN_1PLAY, 0x0007},
  { MSG_1COIN_2PLAY, 0x0003},
  { MSG_1COIN_3PLAY, 0x0002},
  { MSG_1COIN_4PLAY, 0x0001},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x0038, 8 },
  { MSG_4COIN_1PLAY, 0x0020},
  { MSG_3COIN_1PLAY, 0x0028},
  { MSG_2COIN_1PLAY, 0x0030},
  { MSG_1COIN_1PLAY, 0x0038},
  { MSG_1COIN_2PLAY, 0x0018},
  { MSG_1COIN_3PLAY, 0x0010},
  { MSG_1COIN_4PLAY, 0x0008},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_UNKNOWN, 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  { MSG_UNKNOWN, 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_tdragon[] =
{
  { 0x010008, 0xff, dsw_data_tdragon_2 },
  { 0x01000a, 0xff, dsw_data_tdragon_3 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_tdragonb_2[] =
{
  { MSG_LIVES, 0x0003, 4 },
  { "1", 0x0000},
  { "2", 0x0002},
  { "3", 0x0003},
  { "4", 0x0001},
  { MSG_UNKNOWN, 0x0004, 2 },
  { MSG_OFF, 0x0004},
  { MSG_ON, 0x0000},
  { MSG_UNKNOWN, 0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { MSG_DIFFICULTY, 0x0030, 4 },
  { MSG_EASY, 0x0020},
  { MSG_NORMAL, 0x0030},
  { MSG_HARD, 0x0010},
  { MSG_HARDEST, 0x0000},
  { MSG_UNKNOWN, 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  DSW_SCREEN( 0x0080, 0x0000),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_tdragonb_3[] =
{
  { MSG_COIN1, 0x0007, 8 },
  { MSG_4COIN_1PLAY, 0x0004},
  { MSG_3COIN_1PLAY, 0x0005},
  { MSG_2COIN_1PLAY, 0x0006},
  { MSG_1COIN_1PLAY, 0x0007},
  { MSG_1COIN_2PLAY, 0x0003},
  { MSG_1COIN_3PLAY, 0x0002},
  { MSG_1COIN_4PLAY, 0x0001},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x0038, 8 },
  { MSG_4COIN_1PLAY, 0x0020},
  { MSG_3COIN_1PLAY, 0x0028},
  { MSG_2COIN_1PLAY, 0x0030},
  { MSG_1COIN_1PLAY, 0x0038},
  { MSG_1COIN_2PLAY, 0x0018},
  { MSG_1COIN_3PLAY, 0x0010},
  { MSG_1COIN_4PLAY, 0x0008},
  { MSG_FREE_PLAY, 0x0000},
  DSW_DEMO_SOUND( 0x0040, 0x0000),
  { MSG_UNKNOWN, 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_tdragonb[] =
{
   { 0x010008, 0xFF, dsw_data_tdragonb_2 },
   { 0x01000A, 0xFF, dsw_data_tdragonb_3 },
   { 0,        0,    NULL,      },
};


static int scr_x;
static int scr_y;

static UINT8 *RAM_COL,*RAM_FG0;

static UINT8 *GFX_FG0;
static UINT8 *FG0_Mask;

static UINT8 *GFX_SPR;
static UINT8 *SPR_Mask;

static UINT8 *GFX_BG1;
static UINT8 *BG1_Mask;

static UINT8 *GFX_BG0;
static UINT8 *BG0_Mask;

/**********************************************************/
static UINT8 sound_latch, sound_latch2;
static UINT32 macross2_hack;

static void WriteSound68k(UINT32 address, UINT16 data)
{
  if (macross2_hack && (data == 0xc3)) // this commande produces a volume fade out which never
    // ends. We can filter it out this way...
    return;
  sound_latch = data;
}

static UINT16 TDSoundReadZ80(UINT16 offset)
{
   UINT8 ta;

   switch(offset&0x1F){
      case 0x08:		// YM3812 TimerA/B
         return 0x60;
      break;
      case 0x10:
      case 0x11:
      case 0x12:
      //   return 0xFE;
      //break;
      case 0x13:
         print_debug("Z80 Receives:%02x\n",sound_latch);
         ta = sound_latch;
         sound_latch= 0;
         return ta;
      break;
      default:
         ta = 0xFF;
      break;
   }

   print_debug("Z80Read:%04x,%02x [%04x]\n",offset,ta,z80pc);
   return ta;
}

/**********************************************************/

static UINT8 input_mode;

static void macross2_oki6295_bankswitch_w(UINT32 offset, UINT8 data)
{
  /* The OKI6295 ROM space is divided in four banks, each one indepentently
     controlled. The sample table at the beginning of the addressing space is
     divided in four pages as well, banked together with the sample data. */
#define TABLESIZE 0x100
#define BANKSIZE 0x10000
  int chip = (offset & 4) >> 2;
  int banknum = offset & 3;
  unsigned char *rom = load_region[REGION_SOUND1 + chip];
  // get_region_size should return a value from a static array -> very fast
  int size = get_region_size( REGION_SOUND1+chip ) - 0x40000;
  int bankaddr = (data * BANKSIZE) & (size-1);

  // fprintf(stderr,"banksw %d %d data %x bankaddr %x size %x\n",chip,banknum,data,bankaddr,size);

  /* copy the samples */
  memcpy(rom + banknum * BANKSIZE,rom + 0x40000 + bankaddr,BANKSIZE);

  /* and also copy the samples address table */
  rom += banknum * TABLESIZE;
  memcpy(rom,rom + 0x40000 + bankaddr,TABLESIZE);
}

WRITE_HANDLER( bjtwin_oki6295_bankswitch_w )
{
  if ((data & 0x00ff0000) == 0)
	{
	  switch (offset&0xf)
		{
			case 0x00:	OKIM6295_set_bank_base(0, 0, (data & 0x0f) * 0x10000);	break;
			case 0x02:	OKIM6295_set_bank_base(0, 1, (data & 0x0f) * 0x10000);	break;
			case 0x04:	OKIM6295_set_bank_base(0, 2, (data & 0x0f) * 0x10000);	break;
			case 0x06:	OKIM6295_set_bank_base(0, 3, (data & 0x0f) * 0x10000);	break;
			case 0x08:	OKIM6295_set_bank_base(1, 0, (data & 0x0f) * 0x10000);	break;
			case 0x0a:	OKIM6295_set_bank_base(1, 1, (data & 0x0f) * 0x10000);	break;
			case 0x0c:	OKIM6295_set_bank_base(1, 2, (data & 0x0f) * 0x10000);	break;
			case 0x0e:	OKIM6295_set_bank_base(1, 3, (data & 0x0f) * 0x10000);	break;
		}
	}
}

static void NMKVideoWW(UINT32 addr, UINT16 data)
{
   static UINT8 command[2];
   addr &= 0x7FFF;

   WriteWord(&RAM[0x10000+addr],data);

   if((addr>=0x4000)&&(addr<0x4100)){

   data &= 0x00FF;

   switch(addr){
      case 0x4000:
         if(!(command[0]&0x80)){
            command[0] = 0x80;
         }
         else{
            if(data&0x80){
               command[0] = data&0x7F;
               data &= ~0x60;
            }
         }
	 if (romset != 7)
	   OKIM6295_data_0_w(0,data & 0xff);
         //M6295buffer_request(0,data&0xFF);
      break;
      case 0x4010:
         if(!(command[1]&0x80)){
            command[1] = 0x80;
         }
         else{
            if(data&0x80){
               command[1] = data&0x7F;
               data &= ~0x60;
            }
         }
	 if (romset != 7)
	   OKIM6295_data_1_w(1,data & 0xff);
         //M6295buffer_request(1,data&0xFF);
      break;
      default:
	if (romset != 7) {
	  if (addr>=0x4020 && addr<=0x402f) {
	    bjtwin_oki6295_bankswitch_w(addr,data);
	  }
	}
	  //PCMROM[((addr&0x0008)>>3)*0x100000+((addr&0x0006)>>1)*0x10000]=data&0xf;
	//m6295_bank[(addr&0x0008)>>3][(addr&0x0006)>>1] = data & 0x0F;
      break;
   }

   }
   if(addr==0x001E){
     if (romset == 3) // macross 2
       WriteSound68k(addr, data );
     else
       NMK004_w(addr,data);
   }
}

static void NMKVideoWB(UINT32 addr, UINT8 data)
{
   addr &= 0x7FFF;

   RAM[0x10000+(addr^1)]=data;

   // Mustang does not write anything here.
   if(addr==0x001f){
#ifdef RAINE_DEBUG
     print_debug("sound_write:%02x\n",data);
#endif
     if (romset == 3) // macross 2
       WriteSound68k(0x1f, data );
     else
       NMK004_w(addr,data);
   }
}

static UINT16 NMKVideoRW(UINT32 addr)
{
   addr&=0x7FFF;

   switch(addr){
   case 0x4000:
     return OKIM6295_status_0_r( 0 );
     break;
   case 0x4010:
     return OKIM6295_status_1_r( 1 );
     break;
   case 0xe:
     if (romset == 3) // macross 2
       return sound_latch2;

     return NMK004_r(addr);
   default:
         //if(addr>0x4000) print_debug("RW:%06x\n",addr);
         return ReadWord(&RAM[0x10000+addr]);
      break;
   }
   return 0;
}

int NMKDecodeFG0(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_FG0=AllocateMem(0x40000))) return 0;
   memset(GFX_FG0,0x00,0x40000);

   tb=0;
   for(ta=0;ta<size;ta++,tb+=2){
      GFX_FG0[tb+0]=(src[ta]>>4)^15;
      GFX_FG0[tb+1]=(src[ta]&15)^15;
   }

   FG0_Mask = make_solid_mask_8x8(GFX_FG0, size * 2 / 64);

   return 1;
}

int NMKDecodeSPR(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_SPR=AllocateMem(size<<1))) return 0;

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_SPR[tb+0]=(src[ta+0]>>4)^15;
      GFX_SPR[tb+1]=(src[ta+0]&15)^15;
      GFX_SPR[tb+2]=(src[ta+1]>>4)^15;
      GFX_SPR[tb+3]=(src[ta+1]&15)^15;
      GFX_SPR[tb+4]=(src[ta+2]>>4)^15;
      GFX_SPR[tb+5]=(src[ta+2]&15)^15;
      GFX_SPR[tb+6]=(src[ta+3]>>4)^15;
      GFX_SPR[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }


   nb_sprites = (size * 2 / 0x100)-1;

   SPR_Mask = make_solid_mask_pad_16x16(GFX_SPR, (size<<1)>>8, nb_sprites+1);
   return 1;
}

int NMKDecodeSPR_Mustang(UINT8 *src, UINT32 size)
{
   int ta,tb,ss;

   ss=size/2;

   if(!(GFX_SPR=AllocateMem(size<<1))) return 0;

   tb=0;
   for(ta=0;ta<ss;ta+=2){
      GFX_SPR[tb+0]=(src[   ta+0]>>4)^15;
      GFX_SPR[tb+1]=(src[   ta+0]&15)^15;
      GFX_SPR[tb+2]=(src[ss+ta+0]>>4)^15;
      GFX_SPR[tb+3]=(src[ss+ta+0]&15)^15;
      GFX_SPR[tb+4]=(src[   ta+1]>>4)^15;
      GFX_SPR[tb+5]=(src[   ta+1]&15)^15;
      GFX_SPR[tb+6]=(src[ss+ta+1]>>4)^15;
      GFX_SPR[tb+7]=(src[ss+ta+1]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   nb_sprites = size * 2 / 0x100-1;
   SPR_Mask = make_solid_mask_pad_16x16(GFX_SPR, (size<<1)>>8, nb_sprites+1);

   return 1;
}

int NMKDecodeBG1(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;
   UINT32 size2 = size*2;

   if (size2 < 0x100000) {
     // this buffer must be at least 0x100000 bytes to be used as a bg layer
     size2 = 0x100000;
   }
   if(!(GFX_BG1=AllocateMem(size2))) return(0);
   memset(GFX_BG1,0x00,size2);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG1[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG1[tb+1]=(src[ta+0]&15)^15;
      GFX_BG1[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG1[tb+3]=(src[ta+1]&15)^15;
      GFX_BG1[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG1[tb+5]=(src[ta+2]&15)^15;
      GFX_BG1[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG1[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG1_Mask = make_solid_mask_16x16(GFX_BG1, size2 / 0x100);

   return 1;
}

int NMKDecodeBG0(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG0=AllocateMem(size * 2))) return(0);
   memset(GFX_BG0,0x00,size * 2);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG0[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG0[tb+1]=(src[ta+0]&15)^15;
      GFX_BG0[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG0[tb+3]=(src[ta+1]&15)^15;
      GFX_BG0[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG0[tb+5]=(src[ta+2]&15)^15;
      GFX_BG0[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG0[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG0_Mask = make_solid_mask_16x16(GFX_BG0, size/0x80);
   return 1;
}

int NMKDecodeBG0_BJT(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG0=AllocateMem(size * 2))) return(0);
   memset(GFX_BG0,0x00,size * 2);

   tb=0;
   for(ta=0;ta<size;ta++){
      GFX_BG0[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG0[tb+1]=(src[ta+0]&15)^15;
      tb+=2;
   }

   BG0_Mask = make_solid_mask_8x8(GFX_BG0, size/0x20);

   return 1;
}

static void EmptySoundFrame(void)
{
}

static void NormalSoundFrame(void)
{
  execute_z80_audio_frame();
}

static int respcount;
static UINT8 latch2;

static void reset_input_mode() {
  sound_latch = sound_latch2 = latch2 = 0;
  input_mode = 0;
  respcount = 0;
  if (romset == 8 || romset == 2 || romset == 7 || romset == 5 || romset == 1) {
    NMK004_init();
  }
}

static UINT16 bg_size; // size of the bg layer (different for macross2)
static UINT16 videoshift; // shift to add to scrollx for some games
static UINT16 pal_fg; // bank for palette (draw_macross_2)

static int layer_id_data[4];

static char *layer_id_name[5] =
{
   "BG0", "BG1", "FG0", "SPR"
};

static int stopped_cpu;

static void myStop68000(UINT32 offset, UINT8 data) {
  Stop68000(offset,data);
  stopped_cpu = 1;
}

static void finish_nmk_conf(void)
{
  int ta;
  req_int2 = 0;
  macross2_hack = 0;
  AddMemFetch(-1, -1, NULL);
  AddWriteByte(0xAA0000, 0xAA0001, myStop68000, NULL); // speed hack

  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);
  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);

  AddRWBW(-1, -1, NULL, NULL);

  AddInitMemory();     // Set Starscream mem pointers...
  set_reset_function(reset_input_mode);
  memset(RAM+0x00000,0x00,0x30000);
  memset(RAM+0x10000,0xFF,0x00010);

  ExecuteSoundFrame=&EmptySoundFrame;

  if(romset==7)
    RAM_COL=RAM+0x1C000;
  else if (romset==9)
    RAM_COL=RAM+0x14000;
  else
    RAM_COL=RAM+0x18000;

  InitPaletteMap(RAM_COL, 0x40, 0x10, 0x8000);

  set_colour_mapper(&col_map_rrrr_gggg_bbbb_rgbx_rev);
  bg_size = 0x3fff; // size - 1 in fact, for the and.
  if (romset == 0)
    videoshift=64;
  else
    videoshift = 0;
   pal_fg = 0x20;
  for (ta=0; ta<4; ta++)
    layer_id_data[ta] = add_layer_info(layer_id_name[ta]);
}

UINT16 *mcu_shared_ram;
UINT16 *work_ram;

static void AddNMKMainCPU(UINT32 ram, UINT32 vram)
{
  // this function was here to make the memory mapping "general".
  // As a matter of fact, it does not work for all of them (acrobatm and
  // macross2 can't use this function).
  // As a result, it makes the code very unreadable and is not very usefull,
  // but I'll keep it not to rewrite drivers which already work.
  // At least now it's much shorter than what it used to be.
   int code_size = get_region_size(REGION_CPU1);
   if (code_size == 0) code_size = 0x80000; // manual loading

   AddMemFetch(0x000000, code_size-1, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, code_size-1, NULL, ROM+0x000000); // 68000 ROM
   AddRWBW(ram,    ram+0xFFFF, NULL, RAM+0x000000);   // 68000 main RAM

   // The vram area contains controls + ram + videoram...
   // That's why the write do not start at vram : these are the controls.   AddReadByte(vram+0xe,vram + 0xf, NMK004_r, NULL);
   if (romset == 4) // tharrier
       AddRWBW(vram, vram+0x1FFFF, NULL, RAM+0x010000);                 // SCREEN RAM
   else {
       AddReadByte(vram+0xe,vram + 0xf, NMK004_r, NULL);
       AddReadWord(vram, vram+0x07FFF, NMKVideoRW, NULL);                   // MISC SCREEN RAM
       AddWriteByte(vram, vram+0x07FFF, NMKVideoWB, NULL);                  // MISC SCREEN RAM
       AddWriteWord(vram, vram+0x07FFF, NMKVideoWW, NULL);                  // MISC SCREEN RAM

       AddRWBW(vram, vram+0x1FFFF, NULL, RAM+0x010000);                 // SCREEN RAM
   }
}

static void load_bjtwin(void)
{
   int ta;

   romset=0;

   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("93087-3.bin", ROM, 0x10000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(ROM,0x10000))return;

   if(!load_rom("93087-5.bin", ROM, 0x100000)) return; // 16x16 SPRITES (OK)
   DecodeBombJackTwin_OBJ(ROM,0x100000);
//   DecodeBombJackTwin_OBJ(ROM); kath
   if(!NMKDecodeSPR(ROM,0x100000))return;

   if(!load_rom("93087-4.bin", ROM, 0x100000)) return;  // 16x16 TILES (OK)
   DecodeBombJackTwin_BG0(ROM,0x100000);
   if(!NMKDecodeBG0_BJT(ROM,0x100000))return;

   if(!load_rom("93087-1.bin", RAM+0x00000, 0x20000)) return;   // MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("93087-2.bin", RAM+0x00000, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   RAMSize=0x40000;

   scr_x = 384;
   scr_y = 224;

   // 68000 Speed hack

   WriteLong68k(&ROM[0x096EA],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x096EE],0x00AA0000);       //

   // Input hack, so test mode is available

   WriteLong68k(&ROM[0x08F64],0x4E714E71);      //
   WriteLong68k(&ROM[0x08F68],0x4E714E71);      //
   WriteLong68k(&ROM[0x08F6C],0x4E714E71);      //
   WriteLong68k(&ROM[0x08F70],0x4E714E71);      //
   WriteLong68k(&ROM[0x08F74],0x4E714E71);      //

   // Checksum hack

   ROM[0x09172] = 0x60;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);

   AddNMKMainCPU(0x0F0000, 0x080000);

   finish_nmk_conf();
}

static void load_sabotenb(void)
{
   int ta;

   romset=0;

   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("ic35.sb3", ROM, 0x10000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(ROM,0x10000))return;

   if(!load_rom("ic100.sb5", ROM, 0x200000)) return; // 16x16 SPRITES (OK)
   DecodeBombJackTwin_OBJ(ROM,0x200000);
//   DecodeBombJackTwin_OBJ(ROM); kath
   if(!NMKDecodeSPR(ROM,0x200000))return;

   if(!load_rom("ic32.sb4", ROM, 0x200000)) return;  // 16x16 TILES (OK)
   DecodeBombJackTwin_BG0(ROM,0x200000);
   if(!NMKDecodeBG0_BJT(ROM,0x200000))return;

   if(!load_rom("ic76.sb1", RAM+0x00000, 0x40000)) return;   // MAIN 68000
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("ic75.sb2", RAM+0x00000, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   RAMSize=0x40000;

   scr_x = 384;
   scr_y = 224;

   // 68000 Speed hack

//   WriteLong68k(&ROM[0x096EA],0x13FC0000);       // move.b #$00,$AA0000
//   WriteLong68k(&ROM[0x096EE],0x00AA0000);       //

   // Input hack, so test mode is available

//   WriteLong68k(&ROM[0x08F64],0x4E714E71);      //
//   WriteLong68k(&ROM[0x08F68],0x4E714E71);      //
//   WriteLong68k(&ROM[0x08F6C],0x4E714E71);      //
//   WriteLong68k(&ROM[0x08F70],0x4E714E71);      //
//   WriteLong68k(&ROM[0x08F74],0x4E714E71);      //

   // Checksum hack

//   ROM[0x09172] = 0x60;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddNMKMainCPU(0x0F0000, 0x080000);

   finish_nmk_conf();
}

static void load_macross(void)
{
  //int ta;

  setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
   romset=8;

   if(!(RAM=AllocateMem(0x200000))) return;

   if(!load_rom("921a01", RAM, 0x20000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(RAM,0x20000))return;

   if(!load_rom("921a07", RAM, 0x200000)) return;  // 16x16 SPRITES (OK)
   DecodeBombJackTwin_OBJ(RAM,0x200000);
//   DecodeBombJackTwin_OBJ(RAM); kath
   if(!NMKDecodeSPR(RAM,0x200000))return;

   if(!load_rom("921a04", RAM, 0x200000)) return;  // 16x16 TILES (OK)
   DecodeBombJackTwin_BG0(RAM,0x200000);
//   DecodeBombJackTwin_BG0(RAM); kath
   if(!NMKDecodeBG0(RAM,0x200000))return;

   FreeMem(RAM);

   if(!(RAM=AllocateMem(0x60000))) return;

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   // 68000 Speed hack

   WriteLong68k(&ROM[0x052AA],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x052AE],0x00AA0000);       //

   WriteLong68k(&ROM[0x052CA],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x052CE],0x00AA0000);       //

   // Checksum hack
   /*
   ROM[0x09172] = 0x60;
*/

   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);

   AddNMKMainCPU(0x0F0000, 0x080000);

   RAM_FG0 = RAM+0x2c000;
   finish_nmk_conf();
}

static void test_68b(UINT32 adr, UINT16 data) {
  RAM[adr-0xf0000] =data;
  RAM[adr-0xf0000+1] =data;
  if (data == 1 || data == 2) {
    RAM[0x9068] = 11;
    RAM[0x906a] = 0;
    //RAM[0x902e] = 0;
  }
}

static void load_blkheart(void)
{
  //int ta;

  setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
  romset=8;

  if(!(RAM=AllocateMem(0x200000))) return;

   if(!load_rom("3.bin", RAM, 0x20000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(RAM,0x20000))return;

   if(!load_rom_swap_16("90068-8.bin", RAM, 0x100000)) return;  // 16x16 SPRITES (OK)
   if(!NMKDecodeSPR(RAM,0x100000))return;

   if(!load_rom("90068-5.bin", RAM, 0x100000)) return;  // 16x16 TILES (OK)
   if(!NMKDecodeBG0(RAM,0x100000))return;

   FreeMem(RAM);

   if(!(RAM=AllocateMem(0x60000))) return;

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   // 68000 Speed hack

   WriteLong68k(&ROM[0x6e2],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x6e6],0x00AA0000);       //

   WriteLong68k(&ROM[0x6f8],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x6fc],0x00AA0000);       //

   // Forbid restart counter = 0 on startup.
   WriteLong68k(&ROM[0x872],0x4e714e71);
   WriteWord68k(&ROM[0x876],0x4e71);

   // Fix word optimisation for starscream...
   WriteWord68k(&ROM[0x8d6],0x300);
   WriteWord68k(&ROM[0xe1c],0x300);
   WriteWord68k(&ROM[0x23dc],0x300);
   WriteWord68k(&ROM[0x3dea],0x300);

   // Swap byte order at this address (and init restart counter)
   AddWriteByte(0xf902a, 0xf902a,test_68b,NULL);

   /* Sound banks */
   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   // AddReadWord(0x8000e,0x8000f,macross_mcu_r,NULL);
   AddNMKMainCPU(0x0F0000, 0x080000);

   RAM_FG0 = RAM + 0x2c000;
   finish_nmk_conf();
}

static void sound_tdragon2_bank_w(UINT32 offset, UINT16 data) {
  data &= 7;
  // if (data) data--;
  z80a_set_bank(0,data);
}

static void sound_ssmissin_bank_w(UINT16 offset, UINT8 data) {
  unsigned char *rom = load_region[REGION_SOUND1];
  int bank;

  bank = data & 0x3;

  memcpy(rom + 0x20000,rom + 0x80000 + bank * 0x20000,0x20000);
}

static void sound_ssmissin_wb(UINT32 offset, UINT8 data) {
  sound_latch = data;
}
static void sound_ssmissin_ww(UINT32 offset, UINT16 data) {
  sound_latch = data & 0xff;
  if (data & 0x8000)
    cpu_interrupt(CPU_Z80_0, 0x38);
}

static void sound_ssmissin_frame(void)
{

  cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));
}

static void load_ssmissin(void)
{
  romset=3;

   if(!(RAM=AllocateMem(0x400000))) return;

   if(!load_rom("ssm16.172", RAM, 0x20000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(RAM,0x20000))return;

   decode_ssmissin();
   if(!NMKDecodeSPR(load_region[REGION_GFX3],0x100000))return;

   // DecodeThunderDragon_OBJ(load_region[REGION_GFX2]);
   if(!NMKDecodeBG0(load_region[REGION_GFX2],get_region_size(REGION_GFX2)))return;

   FreeMem(RAM);

   if(!(RAM=AllocateMem(0x60000))) return;

   RAMSize=0x50000;

   scr_x = 256;
   scr_y = 224;

/*
 *  StarScream Stuff follows
 */

   // Speed Hack

   WriteLong68k(&ROM[0x0802e],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x08032],0x00AA0000);       //

   ByteSwap(ROM,0x40000);

   RAM_FG0 = RAM+0x30000;
   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x03FFFF, NULL, ROM+0x000000); // 68000 ROM
   AddRWBW(0x0b0000,   0x0bffff, NULL, RAM+0x000000);   // 68000 main RAM

   AddReadByte(0x0c000e, 0x0c000f,  NULL, (UINT8*)&latch2);
   // AddReadWord(0xc000e,0xc000f,macross_mcu_r,NULL);
   AddWriteByte(0xc001e, 0x0c001f, sound_ssmissin_wb, NULL);  // MISC SCREEN RAM
   AddWriteWord(0xc001e, 0x0c001f, sound_ssmissin_ww, NULL);  // MISC SCREEN RAM
   AddRWBW(0x0c0000, 0x0c001f, NULL, RAM+0x010000);  // controls
   //AddReadWord(0x0c0000, 0x0c001f, NMKVideoRW, NULL);  // controls
   //AddWriteByte(0xc0000, 0x0c001d, NMKVideoWB, NULL);  // MISC SCREEN RAM
   //AddWriteWord(0xc0000, 0x0c001d, NMKVideoWW, NULL);  // MISC SCREEN RAM

   AddRWBW(0x0c8000,0x0c87ff, NULL, RAM+0x018000);    // palette
   AddRWBW(0x0c4000,0x0c4007, NULL, RAM+0x1c000);     // scroll registers
   AddRWBW(0x0cc000,0x0cffff, NULL, RAM+0x020000);    // bg videoram

   AddRWBW(0x0d0000,0x0d07ff, NULL, RAM+0x030000);    // txt videoram

   finish_nmk_conf();

   // setup the sound z80

   Z80ROM = load_region[REGION_ROM2];
   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
   AddZ80AReadByte(0x0000, 0x7fff, NULL, Z80ROM);
   // AddZ80AReadByte(0xa000, 0xa000, NULL, &blank); // nop
   AddZ80AReadByte(0x8000, 0x87ff, NULL, RAM+0x40000);
   AddZ80AWriteByte(0x8000, 0x87ff, NULL, RAM+0x40000);
   AddZ80AWriteByte(0x9000, 0x9000, sound_ssmissin_bank_w, NULL);
   AddZ80AReadByte(0x9800, 0x9800, OKIM6295_status_0_r, NULL);
   AddZ80AWriteByte(0x9800, 0x9800, OKIM6295_data_0_w, NULL);
   AddZ80AReadByte(0xa000, 0xa000, NULL, (UINT8*)&sound_latch);

   // end of z80 conf...

   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   ExecuteSoundFrame=&sound_ssmissin_frame;
}

static void memory_map_macross2(int type) {
   if(!(RAM=AllocateMem(0x60000))) return;

   RAMSize=0x50000;

   scr_x = 384;
   scr_y = 224;

/*
 *  StarScream Stuff follows
 */

   // Speed Hack

   if (type == 0) { // macross2
     WriteLong68k(&ROM[0x0ad30],0x13FC0000);       // move.b #$00,$AA0000
     WriteLong68k(&ROM[0x0ad34],0x00AA0000);       //
   } else { // tdragon2
     WriteLong68k(&ROM[0x0aeac],0x13FC0000);       // move.b #$00,$AA0000
     WriteLong68k(&ROM[0x0aeb0],0x00AA0000);       //
   }

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   RAM_FG0 = RAM+0x30000;
   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x07FFFF, NULL, ROM+0x000000); // 68000 ROM
   AddRWBW(0x1f0000,   0x1fffff, NULL, RAM+0x000000);   // 68000 main RAM

   AddReadByte(0x100000, 0x10000b, NULL, RAM+0x010000);  // controls

   AddReadByte(0x10000e, 0x10000f, NULL, (UINT8*)&latch2);

   AddReadWord(0x100000, 0x10000f, NMKVideoRW, NULL);  // controls
   AddWriteByte(0x10000, 0x117FFF, NMKVideoWB, NULL);  // MISC SCREEN RAM
   AddWriteWord(0x10000, 0x117FFF, NMKVideoWW, NULL);  // MISC SCREEN RAM

   AddRWBW(0x120000,0x1207ff, NULL, RAM+0x018000);    // palette
   AddRWBW(0x130000,0x130007, NULL, RAM+0x1c000);     // scroll registers
   AddRWBW(0x140000,0x14ffff, NULL, RAM+0x020000);    // bg videoram

   AddRWBW(0x170000,0x170fff, NULL, RAM+0x030000);    // txt videoram
   AddRWBW(0x171000,0x171fff, NULL, RAM+0x030000);    // txt videoram (mirror)

   finish_nmk_conf();
   bg_size = 0xffff;
   videoshift=64;
   pal_fg = 0x30;

   // setup the sound z80

   z80_init_banks(0,REGION_ROM2,0x8000,0x4000);
   AddZ80AReadByte(0x0000, 0xbfff, NULL, NULL); // bank
   // AddZ80AReadByte(0xa000, 0xa000, NULL, &blank); // nop
   AddZ80AReadByte(0xc000, 0xdfff, NULL, RAM+0x40000);
   AddZ80AWriteByte(0xc000, 0xdfff, NULL, RAM+0x40000);
   AddZ80AWriteByte(0xe001, 0xe001, sound_tdragon2_bank_w, NULL);
   AddZ80AReadByte(0xf000, 0xf000, NULL, (UINT8*)&sound_latch);
   AddZ80AWriteByte(0xf000, 0xf000, NULL, (UINT8*)&latch2);

   // z80 ports...

   AddZ80AReadPort(0x00, 0x00, YM2203_status_port_0_r, NULL);
   AddZ80AReadPort(0x01, 0x01, YM2203_read_port_0_r,   NULL);
   AddZ80AReadPort(0x80, 0x80, OKIM6295_status_0_r,    NULL);
   AddZ80AReadPort(0x88, 0x88, OKIM6295_status_1_r,    NULL);

   AddZ80AWritePort(0x00, 0x00, YM2203_control_port_0_w, NULL);
   AddZ80AWritePort(0x01, 0x01, YM2203_write_port_0_w,   NULL);
   AddZ80AWritePort(0x80, 0x80, OKIM6295_data_0_w,       NULL);
   AddZ80AWritePort(0x88, 0x88, OKIM6295_data_1_w,       NULL);
   AddZ80AWritePort(0x90, 0x97, macross2_oki6295_bankswitch_w, NULL);

   // end of z80 conf...

   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   z80a_set_bank(0,0);
   AddZ80AInit();

   ExecuteSoundFrame=&NormalSoundFrame;
   AddSaveData(SAVE_USER_0,&sound_latch,2);
}

static void load_macross2(void)
{
  romset=3;

   // if(!(RAM=AllocateMem(0x400000))) return;

   // if(!load_rom("mcrs2j.1", RAM, 0x20000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(load_region[REGION_GFX1],0x20000))return;

   // yeah I know, I waste some memory...
   if(!NMKDecodeSPR(load_region[REGION_GFX3],0x400000))return;

   // if(!load_rom("bp932an.a04", RAM, 0x200000)) return;  // 16x16 TILES (OK)
   if(!NMKDecodeBG0(load_region[REGION_GFX2],0x200000))return;

   // FreeMem(RAM);
   memory_map_macross2(0);
   macross2_hack = 1;
}

static void load_tdragon2(void)
{
  romset=3;

   if(!(RAM=AllocateMem(0x400000))) return;

   if(!load_rom("1.bin", RAM, 0x20000)) return;   // 8x8 FG0 TILES (OK)
   if(!NMKDecodeFG0(RAM,0x20000))return;

   // yeah I know, I waste some memory...
   if(!NMKDecodeSPR(load_region[REGION_GFX3],0x400000))return;

   if(!load_rom("ww930914.2", RAM, 0x200000)) return;  // 16x16 TILES (OK)
   if(!NMKDecodeBG0(RAM,0x200000))return;

   FreeMem(RAM);

   memory_map_macross2(1);
}

/******************************************************************************************

Taken from mame :

Thunder Dragon & Hacha Mecha Fighter shares some ram with the MCU,the job of the latter
is to provide some jsr vectors used by the game for gameplay calculations.Also it has
the job to give the vectors of where the inputs are to be read & to calculate the coin
settings,the latter is in the vidhrdw file to avoid sync problems.
To make a long story short,this MCU is an alternative version of the same protection
used by the MJ-8956 games (there are even the same kind of error codes!(i.e the number
printed on the up-left corner of the screen)...

Note: I'm 100% sure of the Thunder Dragon vectors because I've compared it with the
bootleg sets,I'm *not* 100% sure of the Hacha Mecha Fighter vectors because I don't have
anything to compare,infact

******************************************************************************************/

#define PROT_JSR(_offs_,_protvalue_,_pc_) \
	if(mcu_shared_ram[(_offs_)/2] == _protvalue_) \
	{ \
		mcu_shared_ram[(_offs_)/2] = 0xffff;  /*(MCU job done)*/ \
		mcu_shared_ram[(_offs_+2-0x10)/2] = 0x4ef9;/*JMP*/\
		mcu_shared_ram[(_offs_+4-0x10)/2] = 0x0000;/*HI-DWORD*/\
		mcu_shared_ram[(_offs_+6-0x10)/2] = _pc_;  /*LO-DWORD*/\
	} \

#define PROT_INPUT(_offs_,_protvalue_,_protinput_,_input_) \
	if(mcu_shared_ram[_offs_] == _protvalue_) \
	{\
		mcu_shared_ram[_protinput_] = ((_input_ & 0xffff0000)>>16);\
		mcu_shared_ram[_protinput_+1] = (_input_ & 0x0000ffff);\
	}

/*td     - hmf */
/*008D9E - 00796e */
/*
007B9E: bra     7b9c
007BA0: move.w  #$10, $f907a.l
007BA8: bsr     8106
007BAC: bsr     dfc4
007BB0: bsr     c44e
007BB4: bcs     7cfa
007BB8: bsr     d9c6
007BBC: bsr     9400
007BC0: bsr     7a54
007BC4: bsr     da06
007BC8: cmpi.w  #$3, $f907a.l
007BD0: bcc     7be2
007BD2: move.w  #$a, $f530e.l
007BDA: move.w  #$a, $f670e.l
007BE2: bsr     81aa
007BE6: bsr     8994
007BEA: bsr     8c36
007BEE: bsr     8d0c
007BF2: bsr     870a
007BF6: bsr     9d66
007BFA: bsr     b3f2
007BFE: bsr     b59e
007C02: bsr     9ac2
007C06: bsr     c366

thunder dragon algorithm (level 1):
90 - spriteram update
a0 - tilemap update
b0 - player inputs
c0 - controls sprite animation
d0 - player shoots
e0 - controls power-ups
f0 - player bombs
00 - controls player shoots
10 - ?
20 - level logic
30 - enemy appearence
40 - enemy energy
50 - enemy energy 2
60 - enemy shoots

hacha mecha fighter algorithm (level 1):
90 - spriteram update (d9c6)
a0 - tilemap update (d1f8?)
b0 - player inputs (da06)
c0 - controls sprite animation (81aa)
d0 - player shoots (8994)
e0 - controls power-ups & options (8d0c)
f0 - player bombs (8c36)
00 - controls player shoots (870a)
10 - ?
20 - level logic (9642)
30 - enemy appearence (9d66)
40 - enemy energy (b3f2)
50 - enemy energy 2 (b59e)
60 - enemy shoots (9ac2)
70 - ?
80 - <unused>

*/

static void hachamf_mcu_shared_w(UINT32 offset, UINT16 data)
{
  offset = (offset & 0xfff)>>1;
  mcu_shared_ram[offset] = data;

  switch(offset)
    {
    case 0x058/2: PROT_INPUT(0x058/2,0xc71f,0x000/2,0x00080000); break;
    case 0x182/2: PROT_INPUT(0x182/2,0x865d,0x004/2,0x00080002); break;
    case 0x51e/2: PROT_INPUT(0x51e/2,0x0f82,0x008/2,0x00080008); break;
    case 0x6b4/2: PROT_INPUT(0x6b4/2,0x79be,0x00c/2,0x0008000a); break;
    case 0x10e/2: PROT_JSR(0x10e,0x8007,0x870a);/*870a not 9d66 */
      PROT_JSR(0x10e,0x8000,0xd9c6); break;
    case 0x11e/2: PROT_JSR(0x11e,0x8038,0x972a);/*972a */
      PROT_JSR(0x11e,0x8031,0xd1f8); break;
    case 0x12e/2: PROT_JSR(0x12e,0x8019,0x9642);/*OK-9642 */
      PROT_JSR(0x12e,0x8022,0xda06); break;
    case 0x13e/2: PROT_JSR(0x13e,0x802a,0x9d66);/*9d66 not 9400 - OK */
      PROT_JSR(0x13e,0x8013,0x81aa); break;
    case 0x14e/2: PROT_JSR(0x14e,0x800b,0xb3f2);/*b3f2 - OK */
      PROT_JSR(0x14e,0x8004,0x8994); break;
    case 0x15e/2: PROT_JSR(0x15e,0x803c,0xb59e);/*b59e - OK */
      PROT_JSR(0x15e,0x8035,0x8d0c); break;
    case 0x16e/2: PROT_JSR(0x16e,0x801d,0x9ac2);/*9ac2 - OK */
      PROT_JSR(0x16e,0x8026,0x8c36); break;
    case 0x17e/2: PROT_JSR(0x17e,0x802e,0xc366);/*c366 - OK */
      PROT_JSR(0x17e,0x8017,0x870a); break;
    case 0x18e/2: PROT_JSR(0x18e,0x8004,0xd620);        /*unused */
      PROT_JSR(0x18e,0x8008,0x972a); break; /*unused */
    case 0x19e/2: PROT_JSR(0x19e,0x8030,0xd9c6);/*OK-d9c6 */
      PROT_JSR(0x19e,0x8039,0x9642); break;
    case 0x1ae/2: PROT_JSR(0x1ae,0x8011,0xd1f8);/*d1f8 not c67e */
      PROT_JSR(0x1ae,0x802a,0x9d66); break;
    case 0x1be/2: PROT_JSR(0x1be,0x8022,0xda06);/*da06 */
      PROT_JSR(0x1be,0x801b,0xb3f2); break;
    case 0x1ce/2: PROT_JSR(0x1ce,0x8003,0x81aa);/*81aa */
      PROT_JSR(0x1ce,0x800c,0xb59e); break;
    case 0x1de/2: PROT_JSR(0x1de,0x8034,0x8994);/*8994 - OK */
      PROT_JSR(0x1de,0x803d,0x9ac2); break;
    case 0x1ee/2: PROT_JSR(0x1ee,0x8015,0x8d0c);/*8d0c not 82f6 */
      PROT_JSR(0x1ee,0x802e,0xc366); break;
    case 0x1fe/2: PROT_JSR(0x1fe,0x8026,0x8c36);/*8c36 */
      PROT_JSR(0x1fe,0x8016,0xd620); break;  /*unused */
    case 0xf00/2:
      if(mcu_shared_ram[0xf00/2] == 0x60fe)
	{
	  mcu_shared_ram[0xf00/2] = 0x0000; /*this is the coin counter */
	  mcu_shared_ram[0xf02/2] = 0x0000;
	  mcu_shared_ram[0xf04/2] = 0x4ef9;
	  mcu_shared_ram[0xf06/2] = 0x0000;
	  mcu_shared_ram[0xf08/2] = 0x7dc2;
	}
      break;
    }
}

static void tdragon_mcu_shared_w(UINT32 offset, UINT16 data)
{
  offset = (offset & 0xfff)>>1;
  mcu_shared_ram[offset] = data;
  switch(offset)
    {
    case 0x066/2: PROT_INPUT(0x066/2,0xe23e,0x000/2,0x000c0000); break;
    case 0x144/2: PROT_INPUT(0x144/2,0xf54d,0x004/2,0x000c0002); break;
    case 0x60e/2: PROT_INPUT(0x60e/2,0x067c,0x008/2,0x000c0008); break;
    case 0x714/2: PROT_INPUT(0x714/2,0x198b,0x00c/2,0x000c000a); break;
    case 0x70e/2: PROT_JSR(0x70e,0x8007,0x9e22);
      PROT_JSR(0x70e,0x8000,0xd518); break;
    case 0x71e/2: PROT_JSR(0x71e,0x8038,0xaa0a);
      PROT_JSR(0x71e,0x8031,0x8e7c); break;
    case 0x72e/2: PROT_JSR(0x72e,0x8019,0xac48);
      PROT_JSR(0x72e,0x8022,0xd558); break;
    case 0x73e/2: PROT_JSR(0x73e,0x802a,0xb110);
      PROT_JSR(0x73e,0x8013,0x96da); break;
    case 0x74e/2: PROT_JSR(0x74e,0x800b,0xb9b2);
      PROT_JSR(0x74e,0x8004,0xa062); break;
    case 0x75e/2: PROT_JSR(0x75e,0x803c,0xbb4c);
      PROT_JSR(0x75e,0x8035,0xa154); break;
    case 0x76e/2: PROT_JSR(0x76e,0x801d,0xafa6);
      PROT_JSR(0x76e,0x8026,0xa57a); break;
    case 0x77e/2: PROT_JSR(0x77e,0x802e,0xc6a4);
      PROT_JSR(0x77e,0x8017,0x9e22); break;
    case 0x78e/2: PROT_JSR(0x78e,0x8004,0xaa0a);
      PROT_JSR(0x78e,0x8008,0xaa0a); break;
    case 0x79e/2: PROT_JSR(0x79e,0x8030,0xd518);
      PROT_JSR(0x79e,0x8039,0xac48); break;
    case 0x7ae/2: PROT_JSR(0x7ae,0x8011,0x8e7c);
      PROT_JSR(0x7ae,0x802a,0xb110); break;
    case 0x7be/2: PROT_JSR(0x7be,0x8022,0xd558);
      PROT_JSR(0x7be,0x801b,0xb9b2); break;
    case 0x7ce/2: PROT_JSR(0x7ce,0x8003,0x96da);
      PROT_JSR(0x7ce,0x800c,0xbb4c); break;
    case 0x7de/2: PROT_JSR(0x7de,0x8034,0xa062);
      PROT_JSR(0x7de,0x803d,0xafa6); break;
    case 0x7ee/2: PROT_JSR(0x7ee,0x8015,0xa154);
      PROT_JSR(0x7ee,0x802e,0xc6a4); break;
    case 0x7fe/2: PROT_JSR(0x7fe,0x8026,0xa57a);
      PROT_JSR(0x7fe,0x8016,0xa57a); break;
    case 0xf00/2:
      if(mcu_shared_ram[0xf00/2] == 0x60fe)
	{
	  mcu_shared_ram[0xf00/2] = 0x0000; /*this is the coin counter */
	  mcu_shared_ram[0xf02/2] = 0x0000;
	  mcu_shared_ram[0xf04/2] = 0x4ef9;
	  mcu_shared_ram[0xf06/2] = 0x0000;
	  mcu_shared_ram[0xf08/2] = 0x92f4;
	}
      break;
    }
}

static void load_hachamf(void)
{
  setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers

   romset=1;

   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("hmf_05.rom", RAM, 0x20000)) return;           // 8x8 FG0 TILES
   if(!NMKDecodeFG0(RAM,0x20000))return;

   if(!load_rom("hmf_08.rom", ROM, 0x100000)) return;   	// 16x16 SPRITES
   ByteSwap(ROM,0x100000);
   if(!NMKDecodeSPR(ROM,0x100000))return;

   if(!load_rom("hmf_04.rom", ROM+0x00000, 0x80000)) return;   // 16x16 TILES
   if(!NMKDecodeBG1(ROM,0x80000))return;

   if(!load_rom("hmf_04.rom", ROM+0x00000, 0x80000)) return;   // 16x16 TILES
   if(!NMKDecodeBG0(ROM,0x80000))return;

   FreeMem(ROM);
   ROM = load_region[REGION_CPU1];

   RAMSize=0x40000;

   memcpy(load_region[REGION_SOUND1],load_region[REGION_SOUND1]+0x20000,0x20000);
   memcpy(load_region[REGION_SOUND2],load_region[REGION_SOUND2]+0x20000,0x20000);

   scr_x = 256;
   scr_y = 224;

   // Protection

   // patch_rom(ROM,hacha_mecha_fighter_patch_0);

/*    WriteWord68k(&ROM[0x07E82],0x4279);		// */
/*    WriteLong68k(&ROM[0x07E84],0x000FEF00);	// */
/*    WriteLong68k(&ROM[0x07E88],0x4E714E71);	// */

/*    WriteLong68k(&ROM[0x07F2C],0x00007DC2);	// */

/*    WriteWord68k(&ROM[0x143B0],0x4E41);		// */

   // 68000 Speed hack

   WriteLong68k(&ROM[0x0810E],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x08112],0x00AA0000);      //

   // patch sound comm
   WriteWord68k(&ROM[0x048a],0x4e71);
   WriteWord68k(&ROM[0x04aa],0x4e71);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_ROM1));

   work_ram = (UINT16*)(RAM + 0x9000);
   mcu_shared_ram = (UINT16*)(RAM + 0xe000);
   AddMemFetch(0xfe000, 0xfefff, ((UINT8*)mcu_shared_ram) - 0xfe000); // code executed in mcu ram
   AddWriteWord(0x0fe000, 0x0fefff, hachamf_mcu_shared_w, NULL);
   AddNMKMainCPU(0x0F0000, 0x080000);

   finish_nmk_conf();
}

static void load_bioship(void)
{
   int ta;

   setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
   romset=2;

   if(!(ROM=AllocateMem(0xA0000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("7", RAM, 0x10000)) return;               // 8x8 FG0 TILES
   if(!NMKDecodeFG0(RAM,0x10000))return;

   if(!load_rom("sbs-g.03", ROM, 0x80000)) return;        // 16x16 SPRITES
   if(!NMKDecodeSPR(ROM,0x80000))return;

   if(!load_rom("sbs-g.01", ROM, 0x80000)) return;        // 16x16 TILES
   if(!NMKDecodeBG0(ROM,0x80000))return;

   if(!load_rom("sbs-g.02", ROM, 0x80000)) return;        // 16x16 TILES
   if(!NMKDecodeBG1(ROM,0x80000))return;

   if(!load_rom("2", RAM+0x00000, 0x20000)) return;       // 68000 ROM
   if(!load_rom("8", RAM+0x20000, 0x10000)) return;	  // DATA ROM (BG0)
   for(ta=0;ta<0x30000;ta++){
      ROM[ta+ta+0]=RAM[ta];
   }
   if(!load_rom("1", RAM+0x00000, 0x20000)) return;       // 68000 ROM
   if(!load_rom("9", RAM+0x20000, 0x10000)) return;	  // DATA ROM (BG0)
   for(ta=0;ta<0x30000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   memcpy(load_region[REGION_SOUND1],load_region[REGION_SOUND1]+0x20000,0x20000);
   memcpy(load_region[REGION_SOUND2],load_region[REGION_SOUND2]+0x20000,0x20000);

   // Fix Checksum
   // ------------

   WriteWord68k(&ROM[0x0E84C],0x4E75);

   // Fix something (protection/eeprom)
   // ---------------------------------

/*    WriteWord68k(&ROM[0x0F63C],0x4E75); */

   // 68000 Speed hack
   // ----------------

   WriteWord68k(&ROM[0x0498],0x4EF9);           // jmp    $300
   WriteLong68k(&ROM[0x049A],0x00000300);       //

   WriteLong68k(&ROM[0x0300],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0304],0x00AA0000);       //
   WriteWord68k(&ROM[0x0308],0x4879);           // pea    $00000498
   WriteLong68k(&ROM[0x030A],0x00000498);       //
   WriteWord68k(&ROM[0x030E],0x4EF9);           // jmp    $49E
   WriteLong68k(&ROM[0x0310],0x0000049E);       //

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddNMKMainCPU(0x0F0000, 0x080000);

   finish_nmk_conf();
   req_int2 = 1;
}

static void test_continue(UINT32 offset, UINT16 data) {
  if ((RAM[0x9001] & 3)) { // some player left
    return;
  }
  WriteWord(&RAM[0x906a],1);
}

static void load_mustang(void)
{
   setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
   romset=8;

   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("90058-1", RAM, 0x20000)) return;       // 8x8 FG0 TILES
   if(!NMKDecodeFG0(RAM,0x20000))return;

   if(!load_rom("90058-8", ROM+0x00000, 0x80000)) return;        // 16x16 TILES
   if(!load_rom("90058-9", ROM+0x80000, 0x80000)) return;        // 16x16 TILES
   if(!NMKDecodeSPR_Mustang(ROM,0x100000))return;

   if(!load_rom("90058-4", ROM+0x00000, 0x80000)) return;        // 16x16 TILES
   if(!NMKDecodeBG0(ROM,0x80000))return;

   FreeMem(ROM);
   ROM = load_region[REGION_CPU1];

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   // Speed Hack

   WriteLong68k(&ROM[0x006F0],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x006F4],0x00AA0000);       //

   WriteLong68k(&ROM[0x00706],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0070A],0x00AA0000);       //

   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

   // Uncomment to take the control of the demo (pretty useless...) !
   // WriteWord68k(&ROM[0x3c8e],0x4e71);

   // Forbid restart counter = 0 on startup.
   WriteLong68k(&ROM[0x85c],0x4e714e71);
   WriteWord68k(&ROM[0x860],0x4e71);

   // Make Test Mode Easier

   WriteLong68k(&ROM[0x3b0c],0x80004); // test dsw0 instead of input
   WriteWord68k(&ROM[0x3b12],0x0100);       // bit0 seems fine
   WriteWord68k(&ROM[0x3b3e],0x601a); // Only 1 test, not 2 !

   WriteLong68k(&ROM[0xfce],0xaa0002); // Write to test counter instead of real

   WriteWord68k(&ROM[0x8c0],0x300);
   WriteWord68k(&ROM[0xc00],0x300);
   WriteWord68k(&ROM[0x30b2],0x300);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_ROM1));
   // Swap byte order at this address (and init restart counter)
   AddWriteByte(0xf902a,0xf902a,test_68b,NULL);

   // The continue timeout starts whenever a player loose even if another
   // is still playing. Either an unlikely bug of the game, or some remains
   // of the protection... Make the test for the game :
   AddWriteWord(0xaa0002,0xaa0002,test_continue,NULL);

   AddNMKMainCPU(0x0F0000, 0x080000);

   finish_nmk_conf();
   req_int2 = 1;
}

static UINT8 tharrier_mcu_r(UINT32 offset) {
    if ((offset & 1) == 0)
    {
	static const UINT8 to_main[] =
	{
	    0x82,0xc7,0x00,0x2c,0x6c,0x00,0x9f,0xc7,0x00,0x29,0x69,0x00,0x8b,0xc7,0x00
	};
	static int prot_count;

	int res;

	if (s68000readPC()==0x8aa) {
	    res = (ReadWord(&RAM[0x9064]))|0x20; /* Task Force Harrier */
	} else if (s68000readPC()==0x8ce) {
	    res = (ReadWord(&RAM[0x9064]))|0x60; /* Task Force Harrier */
	} else if (s68000readPC()==0x8e4)
	    // At $8e4 the mcu just wants 0s !
	    res = 0;
	else
	{
	    res = to_main[prot_count++];
	    if (prot_count >= sizeof(to_main))
		prot_count = 0;
	}

	return res;
    }
    else {
	return RAM[0x10003]; // input_port_read(space->machine, "IN1");
    }
}

static void copy_bytes(UINT32 offset, UINT8 data) {
    offset &= 0xffff;
    RAM[offset] = RAM[offset ^ 1] = data;
}

static void tharrier_oki6295_bankswitch_0_w(UINT32 offset, UINT8 data)
{
	UINT8 *rom = load_region[REGION_SOUND1];

	data &= 3;
	if (data != 3)
		memcpy(rom + 0x20000,rom + 0x40000 + data * 0x20000,0x20000);
}

static void tharrier_oki6295_bankswitch_1_w(UINT32 offset, UINT8 data)
{
	UINT8 *rom = load_region[REGION_SOUND2];

	data &= 3;
	if (data != 3)
		memcpy(rom + 0x20000,rom + 0x40000 + data * 0x20000,0x20000);
}

static UINT8 soundlatch_read(UINT32 offset) {
    return sound_latch;
}

static void latch2_w(UINT32 offset, UINT8 data) {
    latch2 = data;
}

static void soundlatch_w(UINT32 offset, UINT16 data) {
    sound_latch = data;
}

static UINT16 soundlatch2_r(UINT32 offset) {
    return latch2;
}

static void load_tforceh(void)
{
   romset=4;
   /* The ym2203 depends directly on the z80 frequency, it's a very weird
    * setup here. So just keep 3 Mhz here. */
   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(3,60)); // no z80, but we will simulate it for the timers
   UINT8 *tmp;

   if(!(tmp=AllocateMem(0x100000))) return;

   if(!load_rom("1", tmp, 0x10000)) return;   		   	 // 8x8 FG0 TILES
   if(!NMKDecodeFG0(tmp,0x10000))return;

   if(!load_rom("89050-13", tmp+0x00000, 0x80000)) return;       // 16x16 TILES
   if(!load_rom("89050-17", tmp+0x80000, 0x80000)) return;       // 16x16 TILES
   if(!NMKDecodeSPR_Mustang(tmp,0x100000))return;

   if(!load_rom("89050-4", tmp+0x00000, 0x80000)) return;        // 16x16 TILES
   if(!NMKDecodeBG0(tmp,0x80000))return;
   FreeMem(tmp);
   if(!(RAM=AllocateMem(0x60000))) return;

   RAMSize=0x40800;
   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

   scr_x = 256;
   scr_y = 224;

   // Speed Hack

#if 0
   /* irq 1 is very sensitive for this driver.
    * If we enable a speed hack here, then the number of cycles between 2 irqs
    * 1 can't be constant anymore. Consequences : the mcu can decide we are not
    * allowed to play anymore, and even if it doesn't you don't see your plane
    * flashing anymore to show it's invincible when it 1st appears.
    * The easiest solution is just to disable the speed hack for now */
   WriteLong68k(&ROM[0x00738],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0073C],0x00AA0000);       //

   WriteLong68k(&ROM[0x00722],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00726],0x00AA0000);       //
#endif

   // Make Test Mode Easier

   WriteLong68k(&ROM[0x6dc4],0x80004); // test dsw0 instead of input
   WriteWord68k(&ROM[0x6dcc],0x0100);       // bit0 seems fine
   WriteLong68k(&ROM[0x6DCE],0x660006d2);
   WriteWord68k(&ROM[0x6dd2],0x604a);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);
   AddReadByte( 0x80002,0x80003,tharrier_mcu_r,NULL);
   // AddWriteByte(0xf9f1a, 0xf9f1d, NULL, &RAM[0x9f1a]);
   AddWriteByte(0xf0000,0xfffff,copy_bytes,NULL);
   AddWriteBW(0x8001e, 0x08001f, soundlatch_w, NULL);
   AddReadBW(0x8000e, 0x08000f, soundlatch2_r, NULL);
   AddNMKMainCPU(0x0F0000, 0x080000);

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80ARead(0x0000, 0xbfff, NULL, Z80ROM);
   AddZ80ARW(0xc000, 0xc7ff, NULL, Z80ROM+0xc000); // RAM+0x40000); // normal ram
   memcpy(RAM+0x40000,Z80ROM+0xc000,0x800);
   AddZ80ARead(0xf000, 0xf000, soundlatch_read, NULL);
   AddZ80AWrite(0xf000, 0xf000, latch2_w, NULL);

   AddZ80ARead(0xf400, 0xf400, OKIM6295_status_0_r, NULL);
   AddZ80ARead(0xf500, 0xf500, OKIM6295_status_1_r, NULL);
   AddZ80AWrite(0xf400, 0xf400, OKIM6295_data_0_w,       NULL);
   AddZ80AWrite(0xf500, 0xf500, OKIM6295_data_1_w,       NULL);
   AddZ80AWrite(0xf600, 0xf600, tharrier_oki6295_bankswitch_0_w, NULL);
   AddZ80AWrite(0xf700, 0xf700, tharrier_oki6295_bankswitch_1_w, NULL);

   AddZ80AReadPort(0x00, 0x00, YM2203_status_port_0_r, NULL);
   AddZ80AReadPort(0x01, 0x01, YM2203_read_port_0_r,   NULL);

   AddZ80AWritePort(0x00, 0x00, YM2203_control_port_0_w, NULL);
   AddZ80AWritePort(0x01, 0x01, YM2203_write_port_0_w,   NULL);
   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);

   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();

   finish_nmk_conf();
   set_reset_function(reset_input_mode);
   /* The big surprise of this driver :
    * This is some broken hardware, the ym2203 generates 1 irq for the z80
    * and the z80 never clears the ym2203 irq.
    * 2 consequences : the ym2203 never stands any other irq and remains with
    * its active irq line for ever
    * and the z80 keeps on accepting irqs.
    * This behaviour (the irq line) is NOT emulated by mz80, at all, no way to
    * do it !!! So the work-around is to patch the rom to make it loop on its
    * irq with a jump from the end to the begin, 2 bytes only, but these are
    * 2 quite surprising bytes !!! */
   // WriteWord68k(&Z80ROM[0x6d],0x18ca);
   /* The patch is done by a speed hack after all otherwise we waste an
    * incredible amount of cpu power just to call ym2203_status_r */
   WriteWord68k(&Z80ROM[0x6d],0xd3aa); // outa (aah)
   SetStopZ80Mode2(0x39);
   // also need to clear bit 8 of $10002 to say mcu is ready
   WriteWord(&RAM[0x10000],0xffff);
   WriteWord(&RAM[0x10002],0);
}

static void load_tdragon(void)
{
   setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
   romset=5;

   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("thund.6", RAM, 0x20000)) return;    	// 8x8 FG0 TILES
   if(!NMKDecodeFG0(RAM,0x20000))return;

   if(!load_rom("thund.4", ROM, 0x100000)) return;      // 16x16 TILES
   ByteSwap(ROM,0x100000);
   if(!NMKDecodeSPR(ROM,0x100000))return;

   if(!load_rom("thund.5", ROM, 0x100000)) return;      // 16x16 TILES
   if(!NMKDecodeBG0(ROM+0x00000,0x80000))return;
   if(!NMKDecodeBG1(ROM+0x80000,0x80000))return;
   FreeMem(ROM);
   ROM = load_region[REGION_CPU1];

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   // Protection

   /* Sorry I remove this big patch because it was breaking the sound and it was impossible
      to fix since there were no comments with it ! */
   // patch_rom(ROM,thunder_dragon_patch_0);

   // Missing Sprite Problem

   // WriteWord68k(&ROM[0x00308],0x4E71);

   // Speed Hack

   WriteLong68k(&ROM[0x09628],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0962C],0x00AA0000);       //

   WriteLong68k(&ROM[0x0963E],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x09642],0x00AA0000);       //

   // Make Test Mode Easier

   // WriteLong68k(&ROM[0x0053A],0x4E714E71);

   // patch sound comm
   WriteWord68k(&ROM[0x048a],0x4e71);
   WriteWord68k(&ROM[0x04aa],0x4e71);

   /* sound banks */
   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_ROM1));

   // AddReadBW(0x0be000, 0x0befff, NULL, RAM + 0xe000);
   work_ram = (UINT16*)(RAM + 0x9000);
   mcu_shared_ram = (UINT16*)(RAM + 0xe000);
   AddMemFetch(0xbe000, 0xbefff, ((UINT8*)mcu_shared_ram) - 0xbe000); // code executed in mcu ram
   AddWriteWord(0x0be000, 0x0befff, tdragon_mcu_shared_w, NULL);
   AddNMKMainCPU(0x0B0000, 0x0C0000);

   finish_nmk_conf();
}

static void load_tdragonb(void)
{
   romset=6;

   if(!(ROM=AllocateMem(0x100000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("td_08.bin", RAM, 0x20000)) return;   	   	 // 8x8 FG0 TILES
   if(!NMKDecodeFG0(RAM,0x20000))return;

   if(!load_rom("td_10.bin", ROM+0x00000, 0x80000)) return;      // 16x16 TILES
   if(!load_rom("td_09.bin", ROM+0x80000, 0x80000)) return;      // 16x16 TILES
   DecodeThunderDragon_OBJ(ROM);
   if(!NMKDecodeSPR_Mustang(ROM,0x100000))return;

   if(!load_rom("td_06.bin", ROM+0x00000, 0x80000)) return;        // 16x16 TILES
   DecodeThunderDragon_OBJ(ROM);
   if(!NMKDecodeBG0(ROM,0x80000))return;

   if(!load_rom("td_07.bin", ROM+0x00000, 0x80000)) return;        // 16x16 TILES
   DecodeThunderDragon_OBJ(ROM);
   if(!NMKDecodeBG1(ROM,0x80000))return;
   FreeMem(ROM);
   ROM=load_region[REGION_CPU1];

   DecodeThunderDragon_ROM(ROM);

   RAMSize=0x40000;

   /*-------[SOUND SYSTEM INIT]-------*/

   // Z80ROM=RAM+0x30000;
   // if(!load_rom("td_02.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   Z80ROM[0x0038]=0xCD;	//	CALL	$0010
   Z80ROM[0x0039]=0x10;	//
   Z80ROM[0x003A]=0x00;	//
   Z80ROM[0x003B]=0xED;	//	RETI
   Z80ROM[0x003C]=0x4D;	//

   Z80ROM[0x0066]=0xCD;	//	CALL	$0018
   Z80ROM[0x0067]=0x18;	//
   Z80ROM[0x0068]=0x00;	//
   Z80ROM[0x0069]=0xED;	//	RETN
   Z80ROM[0x006A]=0x45;	//

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x0123]=0xD3;	// OUTA (AAh)
   Z80ROM[0x0124]=0xAA;	//

   SetStopZ80Mode2(0x011A);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x27FF, NULL,			NULL);	// Z80 ROM/RAM
   AddZ80AReadByte(0x400E, 0x400F, YM2151ReadZ80,		NULL);	// YM2151 I/O
   AddZ80AReadByte(0x4000, 0x401F, TDSoundReadZ80,		NULL);	// 68000 + OTHER I/O
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);	// <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x2000, 0x27FF, NULL,			NULL);	// Z80 RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);	// <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   /*---------------------------------*/

   scr_x = 256;
   scr_y = 224;

   // Missing Sprite Problem

   WriteWord68k(&ROM[0x00308],0x4E71);

   // DSW reverse unwanted

   WriteWord68k(&ROM[0x09378],0x33C1);
   WriteLong68k(&ROM[0x0937A],0x000B9006);

   // Scroll Sync

   //WriteWord68k(&ROM[0x0959C],0x660C);

   // Speed Hack

   WriteLong68k(&ROM[0x09628],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0962C],0x00AA0000);       //

   WriteLong68k(&ROM[0x0963E],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x09642],0x00AA0000);       //

   // Make Test Mode Easier
/*
   WriteLong68k(&ROM[0x0053A],0x4E714E71);
*/

   ByteSwap(ROM,get_region_size(REGION_CPU1));

   AddNMKMainCPU(0x0B0000, 0x0C0000);

   finish_nmk_conf();
   // ExecuteSoundFrame=&NormalSoundFrame;
}

static void load_strahl(void)
{
   int ta;

   setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
   romset=7;

   if(!(ROM=AllocateMem(0x180000))) return;

   if(!load_rom("strahl-3.73", ROM, 0x10000)) return;               // 8x8 FG0 TILES
   if(!NMKDecodeFG0(ROM,0x10000))return;

   if(!load_rom("strl3-01.32", ROM+0x000000, 0x80000)) return;      // 16x16 TILES
   if(!load_rom("strl4-02.57", ROM+0x080000, 0x80000)) return;      // 16x16 TILES
   if(!load_rom("strl5-03.58", ROM+0x100000, 0x80000)) return;      // 16x16 TILES
   if(!NMKDecodeSPR(ROM,0x180000))return;

   if(!load_rom("str6b1w1.776", ROM+0x00000, 0x80000)) return;      // 16x16 TILES
   if(!NMKDecodeBG0(ROM,0x80000))return;

   if(!load_rom("str7b2r0.275", ROM+0x00000, 0x40000)) return;      // 16x16 TILES
   if(!NMKDecodeBG1(ROM,0x40000))return;

   FreeMem(ROM);
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x60000))) return;

   if(!load_rom("strahl-2.82", RAM+0x00000, 0x20000)) return;       // 68000 ROM
   memset(RAM+0x20000,0xFF,0x10000);
   for(ta=0;ta<0x30000;ta++){
      ROM[ta+ta+0]=RAM[ta];
   }
   if(!load_rom("strahl-1.83", RAM+0x00000, 0x20000)) return;
   memset(RAM+0x20000,0xFF,0x10000);
   for(ta=0;ta<0x30000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   // Fix Checksum

   WriteWord68k(&ROM[0x008B6],0x4E71);
   WriteWord68k(&ROM[0x0093E],0x4E71);

   // Protection (like task force harrier)

   WriteWord68k(&ROM[0x01CDE],0x6004);
   WriteWord68k(&ROM[0x01D0C],0x4E71);
   WriteWord68k(&ROM[0x01D36],0x4E71);

   WriteLong68k(&ROM[0x01D42],0x44FC0000);
   WriteWord68k(&ROM[0x01D46],0x4E75);

   WriteLong68k(&ROM[0x01D96],0x44FC0000);
   WriteWord68k(&ROM[0x01D9A],0x4E75);

   // Speed Hack

   WriteLong68k(&ROM[0x01462],0x13FC0000);       // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x01466],0x00AA0000);       //

   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddNMKMainCPU(0x0F0000, 0x080000);

   finish_nmk_conf();
   req_int2 = 1;
}

static void load_acrobatm(void)
{
   setup_z80_frame(0,CPU_FRAME_MHz(16,60)); // no z80, but we will simulate it for the timers
   romset=8;

   if(!(ROM=AllocateMem(0x200000))) return;

   if(!load_rom("03_ic79.bin", ROM, 0x10000)) return;               // 8x8 FG0 TILES
   if(!NMKDecodeFG0(ROM,0x10000))return;

   if(!load_rom("09_ic8.bin", ROM+0x00000, 0x100000)) return;      // 16x16 TILES
   if(!NMKDecodeBG0(ROM,0x100000))return;

   if(!load_rom("07_ic42.bin", ROM+0x000000, 0x100000)) return;      // 16x16 TILES
   if(!load_rom("08_ic29.bin", ROM+0x100000, 0x80000)) return;      // 16x16 TILES
   if(!NMKDecodeSPR(ROM,0x180000))return;

   FreeMem(ROM);

   ROM = load_region[REGION_ROM1];
   if(!(RAM=AllocateMem(0x60000))) return;

   RAMSize=0x40000;

   scr_x = 256;
   scr_y = 224;

   memcpy(load_region[REGION_SOUND1], load_region[REGION_SOUND1]+0x20000, 0x20000);
   memcpy(load_region[REGION_SOUND2], load_region[REGION_SOUND2]+0x20000, 0x20000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_ROM1));

   // speed hack
   WriteWord(&ROM[0x210c],0x4239);
   WriteWord(&ROM[0x210e],0xaa);
   WriteWord(&ROM[0x2110],0);

   // disable rom check (2 roms)
   WriteWord(&ROM[0x97a],6004);
   WriteWord(&ROM[0x9d6],6004);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x03FFFF, NULL, ROM+0x000000); // 68000 ROM
   AddRWBW(0x80000,    0x80000+0xFFFF, NULL, RAM+0x000000);   // 68000 main RAM

   AddReadByte(0xc0000, 0xc0000+0x3FFF, NULL, RAM+0x010000);                 // SCREEN RAM
   AddRWBW(0xc8000, 0xc8007, NULL, RAM+0x1c000); // scroll registers
   AddRWBW(0xcc000, 0xcffff, NULL, RAM+0x20000); // bg video ram
   AddRWBW(0xd4000, 0xd47ff, NULL, RAM+0x2c000); // txt video ram
   AddRWBW(0xc4000,0xc45ff, NULL, RAM+0x018000); // palette

   AddReadWord(0xc0000, 0xc0000+0x03FFF, NMKVideoRW, NULL);  // MISC SCREEN RAM

   AddWriteByte(0xc0000, 0xc0000+0x03FFF, NMKVideoWB, NULL); // MISC SCREEN RAM
   AddWriteByte(0xAA0000, 0xAA0001, myStop68000, NULL);        // Trap Idle 68000

   AddWriteWord(0xc0000, 0xc0000+0x03FFF, NMKVideoWW, NULL); // MISC SCREEN RAM

   finish_nmk_conf();
   RAM_FG0 = RAM+0x2C000;
   req_int2 = 1;
}

// Int#1 Timer (BPS).
// Need to hand tune this for Bomb Jack Twin music looping

static int int_rate[ROM_COUNT]=
{
   112,
   112,
   112,
   60,
   112,
   112,
   60,
   112,
   112,
};

static int tick;

static void execute_tdragon2(void)
{
   cpu_interrupt(CPU_68K_0, 2);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));
   //WriteWord(&RAM[0x9000],ReadWord(&RAM[0x9000]) | 1);
   //fprintf(stderr,"%x %x\n",ReadWord(&RAM[0x9000]),ReadWord(&RAM[0x9074]));

   tick += int_rate[romset];

   while(tick>=60){
     cpu_interrupt(CPU_68K_0, 1);
     // cpu_interrupt(CPU_68K_0, 2);
      tick-=60;
      if (tick >= 60)
	  cpu_execute_cycles(CPU_68K_0,1000);
   }
   cpu_interrupt(CPU_68K_0, 4);

   ExecuteSoundFrame();
}

// It's better to leave tharrier without speed hack -> 10 Mhz
// 12 MHz gives a little plus when there are 2 big ships on screen
#define FRAME_68K CPU_FRAME_MHz(12,60)

static void execute_tforceh(void)
{
   cpu_interrupt(CPU_68K_0, 2);
   static int remaining; // remaining cycles before irq 1
   int cycles = FRAME_68K;
   stopped_cpu = 0;
   while (cycles > 0) {
       /* Task force harrier is tricky because you can't just execute irq 1
	* as much as you want, you need to interleave it with normal code
	* execution. It's required for the mcu to get the correct values when
	* it compares to the values from ram. If you use the normal frame
	* then the mcu gets unhappy as soon as the demo (after the title screen)
	* starts. */
       if (!remaining)
	   remaining = FRAME_68K*60/int_rate[romset];
       if (remaining <= cycles) {
	   cpu_execute_cycles(CPU_68K_0, remaining);
	   cycles -= remaining;
	   remaining = 0;
	   cpu_interrupt(CPU_68K_0, 1);
       } else {
	   cpu_execute_cycles(CPU_68K_0, cycles);
	   remaining -= cycles;
	   cycles = 0;
       }
       if (stopped_cpu && cycles) {
	   // If you try a speed hack here, the invicible effect disappears
	   // so it's probably better to disable speed hacks for now here
	   if (remaining < cycles) {
	       cpu_interrupt(CPU_68K_0,1);
	       remaining = 0;
	   } else
	       remaining -= cycles;
	   cycles = 0;
       }
   }


   execute_z80_audio_frame();
   // cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(3,60));
   cpu_interrupt(CPU_68K_0, 4); // vbl
}

/* The crazy thing : the mcu runs the coin counter, so we must simulate it entierly ! */
static void mcu_run(UINT8 dsw_setting)
{
  static UINT8 read_coin;
  static UINT8 old_value;
  static UINT8 coina,coinb;
  UINT8 dsw_a,dsw_b;
  /*needed because of the uncompatibility of the dsw settings.*/
  if(dsw_setting)
    {
      dsw_a = (RAM[0x1000a] & 0x7);
      dsw_b = (RAM[0x1000a] & 0x38) >> 3;
    }
  else
    {
      dsw_a = (RAM[0x10009] & 0x07);
      dsw_b = (RAM[0x10009] & 0x38) >> 3;
    }

  read_coin = old_value;
  old_value = RAM[0x10000];

  if(dsw_a == 0 || dsw_b == 0)
    work_ram[0x000/2]|=0x4000; //free_play

  if(read_coin != old_value)
    {
      if(!(RAM[0x10000] & 0x01))//COIN1
	{
	  switch(dsw_a & 7)
	    {
	    case 1: mcu_shared_ram[0xf00/2]+=4; break;
	    case 2: mcu_shared_ram[0xf00/2]+=3; break;
	    case 3: mcu_shared_ram[0xf00/2]+=2; break;
	    case 4:
	      coina++;
	      if(coina >= 4)
		{
		  coina = 0;
		  mcu_shared_ram[0xf00/2]++;
		}
	      break;
	    case 5:
	      coina++;
	      if(coina >= 3)
		{
		  coina = 0;
		  mcu_shared_ram[0xf00/2]++;
		}
	      break;
	    case 6:
	      coina++;
	      if(coina >= 2)
		{
		  coina = 0;
		  mcu_shared_ram[0xf00/2]++;
		}
	      break;
	    case 7: mcu_shared_ram[0xf00/2]++; break;
	    }
	}

      if(!(RAM[0x10000] & 0x02))//COIN2
	{
	  switch(dsw_b & 7)
	    {
	    case 1: mcu_shared_ram[0xf00/2]+=4; break;
	    case 2: mcu_shared_ram[0xf00/2]+=3; break;
	    case 3: mcu_shared_ram[0xf00/2]+=2; break;
	    case 4:
	      coinb++;
	      if(coinb >= 4)
		{
		  coinb = 0;
		  mcu_shared_ram[0xf00/2]++;
		}
	      break;
	    case 5:
	      coinb++;
	      if(coinb >= 3)
		{
		  coinb = 0;
		  mcu_shared_ram[0xf00/2]++;
		}
	      break;
	    case 6:
	      coinb++;
	      if(coinb >= 2)
		{
		  coinb = 0;
		  mcu_shared_ram[0xf00/2]++;
		}
	      break;
	    case 7: mcu_shared_ram[0xf00/2]++; break;
	    }
	}

      if(!(RAM[0x10000] & 0x04))//SERVICE_COIN
	mcu_shared_ram[0xf00/2]++;

      if(mcu_shared_ram[0xf00/2] >= 1 && (work_ram[0x000/2] & 0x8000))/*enable start button*/
	{
	  /*Start a 1-player game,but don't decrement if the player 1 is already playing*/
	  if((!(RAM[0x10000] & 0x08)) /*START1*/
	     && (!(work_ram[0x000/2] & 0x0200)) /*PLAYER-1 playing*/
	     )
	    mcu_shared_ram[0xf00/2]--;

	  /*Start a 2-players game,but don't decrement if the player 2 is already playing*/
	  if((!(RAM[0x10000] & 0x10))
	     && (!(work_ram[0x000/2] & 0x0100))
	     )
	    {
	      if(!(work_ram[0x000/2] & 0x0200) && mcu_shared_ram[0xf00/2] >= 2)
		mcu_shared_ram[0xf00/2]-=2;
	      else
		mcu_shared_ram[0xf00/2]--;
	    }
	}

      if(mcu_shared_ram[0xf00/2] > 99) mcu_shared_ram[0xf00/2] = 99;
    }
}

static void execute_bioship(void)
{
  int frame = CPU_FRAME_MHz(16,60);
  int cycles;
  stopped_cpu = 0;
  if (romset == 5)
    mcu_run(1);
  else if (romset == 1)
    mcu_run(0);

  do {
    cycles = get_min_cycles(frame);
    dwElapsedTicks += cycles;
    frame -= cycles;
    if (!stopped_cpu)
      cpu_execute_cycles(CPU_68K_0, cycles);
    triger_timers();
  } while (cycles > 0);
   //WriteWord(&RAM[0x9000],ReadWord(&RAM[0x9000]) | 1);
   //fprintf(stderr,"%x %x\n",ReadWord(&RAM[0x9000]),ReadWord(&RAM[0x9074]));
   cpu_interrupt(CPU_68K_0, 4);
   if (req_int2)
     cpu_interrupt(CPU_68K_0, 2);

   tick += int_rate[romset];

   while(tick>=60){
     cpu_interrupt(CPU_68K_0, 1);
      tick-=60;
   }
}

/*

-----+--------+--------------------
Byte | Bit(s) | Use
-----+76543210+--------------------
  1  |.......x| Sprite Enable?
  2  |......x.| Flip X Axis alt?
  2  |.......x| Flip Y Axis alt?
  3  |xxxx....| Chain X Axis
  3  |....xxxx| Chain Y Axis
  6  |x.......| Flip X Axis
  6  |.x......| Flip Y Axis
  6  |...xxxxx| Tile Number (high)
  7  |xxxxxxxx| Tile Number (low)
  8  |.......x| X (high)
  9  |xxxxxxxx| X (low)
 12  |.......x| Y (high)
 13  |xxxxxxxx| Y (low)
 15  |...xxxxx| Colour Bank
-----+--------+--------------------

*/

static void RenderNMKSprites(int pri)
{
   int x,y,zz,r1,ta,xx,yy,xp,xxp;
   UINT8 *MAP;
   UINT8 col_bank;
   UINT8 x_ofs;

  if(! check_layer_enabled(3)) {
    return;
  }

   if(romset==7)
      zz=0xF000;
   else
      zz=0x8000;

   if(romset==2)
      col_bank = 0x20;
   else
      col_bank = 0x10;

   r1 = 255;

   x_ofs = 32+videoshift;

   do {
      if((ReadWord(&RAM[zz]))!=0){		// Strahl - Check other games are ok

      x=(ReadWord(&RAM[zz+ 8])+x_ofs)&0x1FF;
      y=(ReadWord(&RAM[zz+12])+16)&0x1FF;

      ta=ReadWord(&RAM[zz+ 6]);
      MAP_PALETTE_MAPPED_NEW(
			     (RAM[zz+14]&0x1F)+col_bank,
			     16,
			     MAP
			     );

      xx=(RAM[zz+2]&0x0F);
      yy=(RAM[zz+2]>>4);

      xp=x;
      xxp=xx;

      do{
	do{

	  if(ta <= nb_sprites && SPR_Mask[ta]!=0){                      // No pixels; skip
	      x = ((x+16)&0x1ff)-16;

	    if((x>16)&&(y>16)&&(x<scr_x+32)&&(y<scr_y+32)){

	      /* There does not seem to be some flipping for the sprites */
	      if(SPR_Mask[ta]==1){                      // Some pixels; trans

		Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,MAP);
	      }
	      else{                                     // all pixels; solid

		Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,MAP);

	      }

            }

	  }

	  ta++;
	  x=(x+16)&0x1FF;

	}while(--xx>=0);

	x=xp;
	xx=xxp;
	y=(y+16)&0x1FF;

      }while(--yy>=0);
      }
      zz+=16;
   } while(--r1>=0);
}

static void RenderNMKSprites_flip(int pri)
{
    int x,y,zz,r1,ta,xx,yy,xp,xxp;
    UINT8 *MAP;
    UINT8 col_bank;
    UINT8 x_ofs;

    if(! check_layer_enabled(3)) {
	return;
    }

    if(romset==7)
	zz=0xF000;
    else
	zz=0x8000;

    if(romset==2)
	col_bank = 0x20;
    else
	col_bank = 0x10;

    r1 = 255;

    x_ofs = 32+videoshift;

    do {
	if((ReadWord(&RAM[zz]))!=0){		// Strahl - Check other games are ok

	    x=(ReadWord(&RAM[zz+ 8]))&0x1FF;
	    y=(ReadWord(&RAM[zz+12]))&0x1FF;

	    ta=ReadWord(&RAM[zz+ 6]);
	    MAP_PALETTE_MAPPED_NEW(
		    (RAM[zz+14]&0x1F)+col_bank,
		    16,
		    MAP
		    );

	    xx=(RAM[zz+2]&0x0F);
	    yy=(RAM[zz+2]>>4);

	    xxp=xx;

	    int flip= (RAM[zz+3] & 0x03);
	    int flipx = flip & 1;
	    int flipy = flip & 2;
	    if (flipx) {
		x += 16*xx;
	    }
	    if (flipy) {
       	       y += 16*yy;
	    }
	    xp=x;
	    do{
		do{

		    if(ta <= nb_sprites && SPR_Mask[ta]!=0){                      // No pixels; skip
			x = ((x+16)&0x1ff)-16;
			if((x>-16)&&(y>-16)&&(x<scr_x+16)&&(y<scr_y+16)){

			    if(SPR_Mask[ta]==1){                      // Some pixels; trans

				Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR[ta<<8],x+x_ofs,y+16,MAP,flip);
			    }
			    else{                                     // all pixels; solid

				Draw16x16_Mapped_flip_Rot(&GFX_SPR[ta<<8],((x+16)&0x1ff)-16+x_ofs,y+16,MAP,flip);

			    }

			}

		    }

		    ta++;
		    x=(x+16*(flipx?-1:1));

		}while(--xx>=0);

		x=xp;
		xx=xxp;
		y=(y+16*(flipy?-1:1));
	    }while(--yy>=0);
	}
	zz+=16;
    } while(--r1>=0);
}

static int NMKLayerCount;

typedef struct NMKLAYER
{
   UINT8 *RAM;
   UINT8 *GFX16;
   UINT8 *GFX8;
   UINT8 *MSK16;
   UINT8 *MSK8;
   UINT8 *SCR;
   UINT8 PAL;
} NMKLAYER;

static struct NMKLAYER NMKLayers[3];

static void RenderNMKLayer(int layer)
{
   UINT8 *RAM_BG,*SCR_BG,*GFX_BG16,*MSK_BG16;
   UINT8 *GFX_BG8,*MSK_BG8,PAL_BG;
   UINT8 *MAP;
   int x,y,x16,y16,zz,zzz,zzzz,ta;

  if(! check_layer_enabled(layer)) {
    if (!layer)
      clear_game_screen(0);
    NMKLayerCount++;
    return;
  }

   RAM_BG       =NMKLayers[layer].RAM;
   SCR_BG       =NMKLayers[layer].SCR;
   GFX_BG16     =NMKLayers[layer].GFX16;
   MSK_BG16     =NMKLayers[layer].MSK16;
   GFX_BG8      =NMKLayers[layer].GFX8;
   MSK_BG8      =NMKLayers[layer].MSK8;
   PAL_BG       =NMKLayers[layer].PAL;

   if((ReadWord(&SCR_BG[4])&0x0010)==0){        // 16x16

   if(GFX_BG16!=NULL){                          // HAVE GFX

   if(NMKLayerCount==0){                     // **** SOLID ****


     switch(ReadWord(&SCR_BG[4])&0x0003){

     case 0x00:                                   // <<<<$1000x$200>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x0700)>>4)<<9;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x0FF0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz&=bg_size;
       zz=zzzz;

       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){

	   MAP_PALETTE_MAPPED_NEW(
				  (RAM_BG[1+zz]>>4)|PAL_BG,
				  16,
				  MAP
				  );

	   Draw16x16_Mapped_Rot(&GFX_BG16[(ReadWord(&RAM_BG[zz])&0xFFF)<<8],x,y,MAP);
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0x1FE0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0x1FE0)==0) zzzz-=0x2000;
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     case 0x01:                                   // <<<<$800x$400>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x0f00)>>4)<<8;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x07F0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){

	   MAP_PALETTE_MAPPED_NEW(
				  (RAM_BG[1+zz]>>4)|PAL_BG,
				  16,
				  MAP
				  );

	   Draw16x16_Mapped_Rot(&GFX_BG16[(ReadWord(&RAM_BG[zz])&0xFFF)<<8],x,y,MAP);
	   zz+=2;
	   if((zz&0x1F)==0) { zz+=0xFE0;zz&=bg_size; }
	 }
	 zzzz+=0x20;
	 if((zzzz&0xFE0)==0){zzzz-=0x1000;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     case 0x02:                                   // <<<<$400x$800>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x1f00)>>4)<<7;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x03F0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){

	   MAP_PALETTE_MAPPED_NEW(
				  (RAM_BG[1+zz]>>4)|PAL_BG,
				  16,
				  MAP
				  );

	   Draw16x16_Mapped_Rot(&GFX_BG16[(ReadWord(&RAM_BG[zz])&0xFFF)<<8],x,y,MAP);
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0x7E0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0x7E0)==0){zzzz-=0x800;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     case 0x03:                                   // <<<<$200x$1000>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x3F00)>>4)<<6;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x01F0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){

	   MAP_PALETTE_MAPPED_NEW(
				  (RAM_BG[1+zz]>>4)|PAL_BG,
				  16,
				  MAP
				  );

	   Draw16x16_Mapped_Rot(&GFX_BG16[(ReadWord(&RAM_BG[zz])&0xFFF)<<8],x,y,MAP);
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0x3E0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0x3E0)==0){zzzz-=0x400;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     }
     NMKLayerCount++;
   }                                            // END SOLID
   else{                                        // **** TRANSPARENT ****

     switch(ReadWord(&SCR_BG[4])&3){

     case 0x00:                                   // <<<<$1000x$200>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x0100)>>4)<<9;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x0FF0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){
	   ta=ReadWord(&RAM_BG[zz])&0xFFF;
	   if(MSK_BG16[ta]!=0){                      // No pixels; skip

	     MAP_PALETTE_MAPPED_NEW(
				    (RAM_BG[1+zz]>>4)|PAL_BG,
				    16,
				    MAP
				    );

	     if(MSK_BG16[ta]==1){                   // Some pixels; trans
	       Draw16x16_Trans_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	     else{                                  // all pixels; solid
	       Draw16x16_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	   }
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0x1FE0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0x1FE0)==0){zzzz-=0x2000;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     case 0x01:                                   // <<<<$800x$400>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x0300)>>4)<<8;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x07F0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){
	   ta=ReadWord(&RAM_BG[zz])&0xFFF;
	   if(MSK_BG16[ta]!=0){                      // No pixels; skip

	     MAP_PALETTE_MAPPED_NEW(
				    (RAM_BG[1+zz]>>4)|PAL_BG,
				    16,
				    MAP
				    );

	     if(MSK_BG16[ta]==1){                   // Some pixels; trans
	       Draw16x16_Trans_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	     else{                                  // all pixels; solid
	       Draw16x16_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	   }
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0xFE0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0xFE0)==0){zzzz-=0x1000;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     case 0x02:                                   // <<<<$400x$800>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x0700)>>4)<<7;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x03F0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){
	   ta=ReadWord(&RAM_BG[zz])&0xFFF;
	   if(MSK_BG16[ta]!=0){                      // No pixels; skip

	     MAP_PALETTE_MAPPED_NEW(
				    (RAM_BG[1+zz]>>4)|PAL_BG,
				    16,
				    MAP
				    );

	     if(MSK_BG16[ta]==1){                   // Some pixels; trans
	       Draw16x16_Trans_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	     else{                                  // all pixels; solid
	       Draw16x16_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	   }
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0x7E0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0x7E0)==0){zzzz-=0x800;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     case 0x03:                                   // <<<<$200x$1000>>>>
       zzz=(ReadWord(&SCR_BG[2])+16);
       zzzz =((zzz&0x00F0)>>4)<<1;                  // Y Offset (16-255)
       zzzz+=((zzz&0x0F00)>>4)<<6;                  // Y Offset (256-nn)
       y16=zzz&15;                                  // Y Offset (0-15)
       zzz=ReadWord(&SCR_BG[0])-videoshift;
       zzzz+=((zzz&0x01F0)>>4)<<5;                  // X Offset (16-nn)
       x16=zzz&15;                                  // X Offset (0-15)

       zzzz=zzzz&bg_size;
       zz=zzzz;
       for(x=(32-x16);x<(scr_x+32);x+=16){
	 for(y=(32-y16);y<(scr_y+32);y+=16){
	   ta=ReadWord(&RAM_BG[zz])&0xFFF;
	   if(MSK_BG16[ta]!=0){                      // No pixels; skip

	     MAP_PALETTE_MAPPED_NEW(
				    (RAM_BG[1+zz]>>4)|PAL_BG,
				    16,
				    MAP
				    );

	     if(MSK_BG16[ta]==1){                   // Some pixels; trans
	       Draw16x16_Trans_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	     else{                                  // all pixels; solid
	       Draw16x16_Mapped_Rot(&GFX_BG16[ta<<8],x,y,MAP);
	     }
	   }
	   zz+=2;
	   if((zz&0x1F)==0){zz+=0x3E0;zz&=bg_size;}
	 }
	 zzzz+=0x20;
	 if((zzzz&0x3E0)==0){zzzz-=0x400;}
	 zzzz&=bg_size;
	 zz=zzzz;
       }
       break;
     }
     NMKLayerCount++;
   }                                            // END TRANSPARENT
   }                                            // END HAVE GFX
   }                                            // END 16x16
   else{                                        // 8x8

     if(GFX_BG8!=NULL){                           // HAVE GFX

       if(NMKLayerCount==0){                     // **** SOLID ****

	 if(romset==0)
	   zz=4+(64*2);

	 for(x=32;x<scr_x+32;x+=8,zz+=8){
	   for(y=32;y<scr_y+32;y+=8,zz+=2){

	     MAP_PALETTE_MAPPED_NEW(
				    (ReadWord(&RAM_BG[zz])>>12)|PAL_BG,
				    16,
				    MAP
				    );

	     Draw8x8_Mapped_Rot(&GFX_BG8[(ReadWord(&RAM_BG[zz])&0xFFF)<<6],x,y,MAP);
	   }
	 }
	 NMKLayerCount++;
       }                                            // END SOLID
       else{                                        // **** TRANSPARENT ****

	 if(ReadLong(&SCR_BG[0])==0){

	   if(romset==0) zz=4+(64*2);
	   else zz=(4-64*videoshift/8) & 0xfff;

	   for(x=32;x<scr_x+32;x+=8,zz=(zz+8)&0xfff){
	     for(y=32;y<scr_y+32;y+=8,zz=(zz+2)&0xfff){
	       ta=ReadWord(&RAM_BG[zz])&0xFFF;
	       if(MSK_BG8[ta]!=0){

		 MAP_PALETTE_MAPPED_NEW(
					(ReadWord(&RAM_BG[zz])>>12)|PAL_BG,
					16,
					MAP
					);

		 if (MSK_BG8[ta] == 1)
		   Draw8x8_Trans_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		 else
		   Draw8x8_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
	       }
	     }
	   }

	 }
	 else{

	   // print_ingame(2,gettext("%04x"),ReadWord(&SCR_BG[4])&3);

	   switch(ReadWord(&SCR_BG[4])&3){

	   case 0x00:                                   // <<<<$800x$100>>>>
	     zzz=(ReadWord(&SCR_BG[2])+16);
	     zzzz =((zzz&0x00F8)>>3)<<1;                  // Y Offset (16-255)
	     zzzz+=((zzz&0x0000)>>3)<<9;                  // Y Offset (256-nn)
	     y16=zzz&7;                                   // Y Offset (0-15)
	     zzz=ReadWord(&SCR_BG[0])-videoshift;
	     zzzz+=((zzz&0x07F8)>>3)<<6;                  // X Offset (16-nn)
	     x16=zzz&7;                                   // X Offset (0-15)

	     zzzz=zzzz&bg_size;
	     zz=zzzz;
	     for(x=(32-x16);x<(scr_x+32);x+=8){
	       for(y=(32-y16);y<(scr_y+32);y+=8){
		 ta=ReadWord(&RAM_BG[zz])&0xFFF;
		 if(MSK_BG8[ta]!=0){                       // No pixels; skip

		   MAP_PALETTE_MAPPED_NEW(
					  (ReadWord(&RAM_BG[zz])>>12)|PAL_BG,
					  16,
					  MAP
					  );

		   if(MSK_BG8[ta]==1){                    // Some pixels; trans
		     Draw8x8_Trans_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		   else{                                  // all pixels; solid
		     Draw8x8_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		 }
		 zz+=2;
		 if((zz&0x3F)==0){zz+=0x3FC0;zz&=bg_size;}
	       }
	       zzzz+=0x40;
	       if((zzzz&0x3FC0)==0){zzzz-=0x4000;}
	       zzzz&=bg_size;
	       zz=zzzz;
	     }
	     break;
	   case 0x02:                                   // <<<<$400x$200>>>> (yes, this is reversed)
	     zzz=(ReadWord(&SCR_BG[2])+16);
	     zzzz =((zzz&0x00F8)>>3)<<1;                  // Y Offset (16-255)
	     zzzz+=((zzz&0x0100)>>3)<<8;                  // Y Offset (256-nn)
	     y16=zzz&7;                                   // Y Offset (0-15)
	     zzz=ReadWord(&SCR_BG[0])-videoshift;
	     zzzz+=((zzz&0x03F8)>>3)<<6;                  // X Offset (16-nn)
	     x16=zzz&7;                                   // X Offset (0-15)

	     zzzz=zzzz&bg_size;
	     zz=zzzz;
	     for(x=(32-x16);x<(scr_x+32);x+=8){
	       for(y=(32-y16);y<(scr_y+32);y+=8){
		 ta=ReadWord(&RAM_BG[zz])&0xFFF;
		 if(MSK_BG8[ta]!=0){                       // No pixels; skip

		   MAP_PALETTE_MAPPED_NEW(
					  (ReadWord(&RAM_BG[zz])>>12)|PAL_BG,
					  16,
					  MAP
					  );

		   if(MSK_BG8[ta]==1){                    // Some pixels; trans
		     Draw8x8_Trans_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		   else{                                  // all pixels; solid
		     Draw8x8_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		 }
		 zz+=2;
		 if((zz&0x3F)==0){zz+=0x1FC0;zz&=bg_size;}
	       }
	       zzzz+=0x40;
	       if((zzzz&0x1FC0)==0){zzzz-=0x2000;}
	       zzzz&=bg_size;
	       zz=zzzz;
	     }
	     break;
	   case 0x01:                                   // <<<<$200x$400>>>> (yes, this is reversed)
	     zzz=(ReadWord(&SCR_BG[2])+16);
	     zzzz =((zzz&0x00F8)>>3)<<1;                  // Y Offset (16-255)
	     zzzz+=((zzz&0x0300)>>3)<<7;                  // Y Offset (256-nn)
	     y16=zzz&7;                                   // Y Offset (0-15)
	     zzz=ReadWord(&SCR_BG[0])-videoshift;
	     zzzz+=((zzz&0x01F8)>>3)<<6;                  // X Offset (16-nn)
	     x16=zzz&7;                                   // X Offset (0-15)

	     zzzz=zzzz&bg_size;
	     zz=zzzz;
	     for(x=(32-x16);x<(scr_x+32);x+=8){
	       for(y=(32-y16);y<(scr_y+32);y+=8){
		 ta=ReadWord(&RAM_BG[zz])&0xFFF;
		 if(MSK_BG8[ta]!=0){                       // No pixels; skip

		   MAP_PALETTE_MAPPED_NEW(
					  (ReadWord(&RAM_BG[zz])>>12)|PAL_BG,
					  16,
					  MAP
					  );

		   if(MSK_BG8[ta]==1){                    // Some pixels; trans
		     Draw8x8_Trans_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		   else{                                  // all pixels; solid
		     Draw8x8_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		 }
		 zz+=2;
		 if((zz&0x3F)==0){zz+=0xFC0;zz&=bg_size;}
	       }
	       zzzz+=0x40;
	       if((zzzz&0xFC0)==0){zzzz-=0x1000;}
	       zzzz&=bg_size;
	       zz=zzzz;
	     }
	     break;
	   case 0x03:                                   // <<<<$100x$800>>>>
	     zzz=(ReadWord(&SCR_BG[2])+16);
	     zzzz =((zzz&0x00F8)>>3)<<1;                  // Y Offset (16-255)
	     zzzz+=((zzz&0x0700)>>3)<<6;                  // Y Offset (256-nn)
	     y16=zzz&7;                                   // Y Offset (0-15)
	     zzz=ReadWord(&SCR_BG[0])-videoshift;
	     zzzz+=((zzz&0x00F8)>>3)<<6;                  // X Offset (16-nn)
	     x16=zzz&7;                                   // X Offset (0-15)

	     zzzz=zzzz&bg_size;
	     zz=zzzz;
	     for(x=(32-x16);x<(scr_x+32);x+=8){
	       for(y=(32-y16);y<(scr_y+32);y+=8){
		 ta=ReadWord(&RAM_BG[zz])&0xFFF;
		 if(MSK_BG8[ta]!=0){                       // No pixels; skip

		   MAP_PALETTE_MAPPED_NEW(
					  (ReadWord(&RAM_BG[zz])>>12)|PAL_BG,
					  16,
					  MAP
					  );

		   if(MSK_BG8[ta]==1){                    // Some pixels; trans
		     Draw8x8_Trans_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		   else{                                  // all pixels; solid
		     Draw8x8_Mapped_Rot(&GFX_BG8[ta<<6],x,y,MAP);
		   }
		 }
		 zz+=2;
		 if((zz&0x3F)==0){zz+=0x7C0;zz&=bg_size;}
	       }
	       zzzz+=0x40;
	       if((zzzz&0x7C0)==0){zzzz-=0x800;}
	       zzzz&=bg_size;
	       zz=zzzz;
	     }
	     break;
	   }

	 }

	 NMKLayerCount++;
       }                                            // END TRANSPARENT
     }                                            // END HAVE GFX

   }                                            // END 8x8
}

static void DrawNMK(void)
{
   int ta,tb;

   ClearPaletteMap();

   NMKLayerCount=0;

   if(RefreshBuffers){
   NMKLayers[0].RAM          =RAM+0x22000;
   NMKLayers[0].GFX16        =GFX_BG1;
   NMKLayers[0].GFX8         =NULL;
   NMKLayers[0].MSK16        =BG1_Mask;
   NMKLayers[0].MSK8         =NULL;
   NMKLayers[0].SCR          =RAM+0x14208;
   NMKLayers[0].PAL          =0x00;

   NMKLayers[1].RAM          =RAM+0x20000;
   NMKLayers[1].GFX16        =GFX_BG0;
   NMKLayers[1].GFX8         =NULL;
   NMKLayers[1].MSK16        =BG0_Mask;
   NMKLayers[1].MSK8         =NULL;
   NMKLayers[1].SCR          =RAM+0x14200;
   NMKLayers[1].PAL          =0x10;

   NMKLayers[2].RAM          =RAM+0x2C000;
   NMKLayers[2].GFX16        =NULL;
   NMKLayers[2].GFX8         =GFX_FG0;
   NMKLayers[2].MSK16        =NULL;
   NMKLayers[2].MSK8         =FG0_Mask;
   NMKLayers[2].SCR          =RAM+0x14008;
   NMKLayers[2].PAL          =0x30;

   if(romset==1){
   NMKLayers[2].PAL          =0x20;
   }

   }

   for(tb=0;tb<16;tb+=2){
      ta = (RAM[0x1C001+tb+tb]<<8) | (RAM[0x1C003+tb+tb]);
      WriteWord(&RAM[0x14200+tb], ta);
   }

   WriteLong(&RAM[0x14008],0x00000000);
   WriteLong(&RAM[0x1400C],0xFFFFFFFF);

   if(romset!=1){
   //ta = (ReadWord(&RAM[0x000F0])&0x0F)<<13;
   ta = (ReadWord(&RAM[0x000F2])&0x07)<<13;
   NMKLayers[0].RAM = ROM+0x40000+ta;
   }

   RenderNMKLayer(0);

   RenderNMKSprites(0);

   RenderNMKLayer(1);

   RenderNMKLayer(2);
}

static void DrawMustang(void)
{
   int ta,tb;

   ClearPaletteMap();

   NMKLayerCount=0;

   if(RefreshBuffers){
   NMKLayers[1].RAM          =RAM+0x20000;
   NMKLayers[1].GFX16        =GFX_BG0;
   NMKLayers[1].GFX8         =NULL;
   NMKLayers[1].MSK16        =BG0_Mask;
   NMKLayers[1].MSK8         =NULL;
   NMKLayers[1].SCR          =RAM+0x14200;
   NMKLayers[1].PAL          =0x00;			// OK

   NMKLayers[2].RAM          =RAM+0x2C000;
   NMKLayers[2].GFX16        =NULL;
   NMKLayers[2].GFX8         =GFX_FG0;
   NMKLayers[2].MSK16        =NULL;
   NMKLayers[2].MSK8         =FG0_Mask;
   NMKLayers[2].SCR          =RAM+0x14008;
   NMKLayers[2].PAL          =0x20;
   }

   for(tb=0;tb<16;tb+=2){
      ta = (RAM[0x1C000+tb+tb]<<8) | (RAM[0x1C002+tb+tb]);
      WriteWord(&RAM[0x14200+tb], ta);
   }

   WriteLong(&RAM[0x14008],0x00000000);
   WriteLong(&RAM[0x1400C],0xFFFFFFFF);

   RenderNMKLayer(1);

   RenderNMKSprites(0);

   RenderNMKLayer(2);
}

// Apparently only 1 bg layer -> index 0

static void DrawBombJackTwin(void)
{
   int ta,x,y,zz;
   UINT8 *map;
   UINT8 *GFX_BG;

   ClearPaletteMap();

   GFX_BG = GFX_BG0 + (((RAM[0x24000]))*0x20000);

   zz = 0x2CE00+4;
   for(x=32;x<(scr_x+32);x+=8){
   for(y=32;y<(scr_y+32);y+=8){

      ta = ReadWord(&RAM[zz]);

      MAP_PALETTE_MAPPED_NEW(
         ta>>12,
         16,
         map
      );

      if((ta&0x800)==0)
	Draw8x8_Mapped_Rot(&GFX_FG0[(ta&0x7FF)<<6],x,y,map);
      else
	Draw8x8_Mapped_Rot(&GFX_BG[(ta&0x7FF)<<6],x,y,map);
      zz+=2;
   }
   zz+=8;
   }

   RenderNMKSprites(0);
}

static void DrawTaskForceHarrier(void)
{
  int ta,tb;
   ClearPaletteMap();

   NMKLayerCount=0;

   if(RefreshBuffers){
   NMKLayers[0].RAM          =RAM+0x20000;
   NMKLayers[0].GFX16        =GFX_BG0;
   NMKLayers[0].GFX8         =NULL;
   NMKLayers[0].MSK16        =BG0_Mask;
   NMKLayers[0].MSK8         =NULL;
   NMKLayers[0].SCR          =RAM+0x14200;
   NMKLayers[0].PAL          =0x00;

   NMKLayers[2].RAM          =RAM+0x2D000;
   NMKLayers[2].GFX16        =NULL;
   NMKLayers[2].GFX8         =GFX_FG0;
   NMKLayers[2].MSK16        =NULL;
   NMKLayers[2].MSK8         =FG0_Mask;
   NMKLayers[2].SCR          =RAM+0x14008; // 14008
   NMKLayers[2].PAL          =0x00;
   }

   for(tb=2;tb<16;tb+=2){
      ta = (RAM[0x1C000+tb+tb]<<8) | (RAM[0x1C002+tb+tb]);
      WriteWord(&RAM[0x14200+tb], ta);
   }
   WriteWord(&RAM[0x14200],ReadWord(&RAM[0x9f00])); // offset x
   // WriteWord(&RAM[0x14202],0); // offset y (no shift)

   WriteWord(&RAM[0x14008],0x00000000); // no scroll at all on this one
   WriteLong(&RAM[0x1400C],0xFFFFFFFF);

   RenderNMKLayer(0);

   RenderNMKSprites_flip(0);

   RenderNMKLayer(2);
}

static void DrawThunderDragon(void)
{
   int ta,tb;

   ClearPaletteMap();

   NMKLayerCount=0;

   if(RefreshBuffers){
   NMKLayers[0].RAM          =RAM+0x1C000;
   NMKLayers[0].GFX16        =GFX_BG0;
   NMKLayers[0].GFX8         =NULL;
   NMKLayers[0].MSK16        =BG0_Mask;
   NMKLayers[0].MSK8         =NULL;
   NMKLayers[0].SCR          =RAM+0x14800;
   NMKLayers[0].PAL          =0x00;

   NMKLayers[2].RAM          =RAM+0x20000;
   NMKLayers[2].GFX16        =NULL;
   NMKLayers[2].GFX8         =GFX_FG0;
   NMKLayers[2].MSK16        =NULL;
   NMKLayers[2].MSK8         =FG0_Mask;
   NMKLayers[2].SCR          =RAM+0x14A00;
   NMKLayers[2].PAL          =0x20;

   }

   // GFX BG0 bank switch

   if((ReadWord(&RAM[0x10018])&0x0001)==0){
   NMKLayers[0].GFX16 = GFX_BG0;
   NMKLayers[0].MSK16 = BG0_Mask;
   }
   else{
   NMKLayers[0].GFX16 = GFX_BG1;
   NMKLayers[0].MSK16 = BG1_Mask;
   }

   // Scroll BG0 fix

   for(tb=0;tb<16;tb+=2){
      ta = (RAM[0x14000+tb+tb]<<8) | (RAM[0x14002+tb+tb]);
      WriteWord(&RAM[0x14800+tb], ta);
   }

   WriteWord(&RAM[0x14800], ReadWord(&RAM[0x090E0]));
   WriteWord(&RAM[0x14802], ReadWord(&RAM[0x090E4]));

   // Scroll FG0 fix

   WriteLong(&RAM[0x14A00],0x00000000);
   WriteLong(&RAM[0x14A04],0xFFFFFFFF);

   RenderNMKLayer(0);

   RenderNMKSprites(0);

   RenderNMKLayer(2);
}

static void DrawStrahl(void)
{
   int ta,tb;

   ClearPaletteMap();

   NMKLayerCount=0;

   if(RefreshBuffers){
   NMKLayers[0].RAM          =RAM+0x20000;
   NMKLayers[0].GFX16        =GFX_BG1;
   NMKLayers[0].GFX8         =NULL;
   NMKLayers[0].MSK16        =BG1_Mask;
   NMKLayers[0].MSK8         =NULL;
   NMKLayers[0].SCR          =RAM+0x14100;
   NMKLayers[0].PAL          =0x30;

   NMKLayers[1].RAM          =RAM+0x24000;
   NMKLayers[1].GFX16        =GFX_BG0;
   NMKLayers[1].GFX8         =NULL;
   NMKLayers[1].MSK16        =BG0_Mask;
   NMKLayers[1].MSK8         =NULL;
   NMKLayers[1].SCR          =RAM+0x18100;
   NMKLayers[1].PAL          =0x20;

   NMKLayers[2].RAM          =RAM+0x2C000;
   NMKLayers[2].GFX16        =NULL;
   NMKLayers[2].GFX8         =GFX_FG0;
   NMKLayers[2].MSK16        =NULL;
   NMKLayers[2].MSK8         =FG0_Mask;
   NMKLayers[2].SCR          =RAM+0x14200;
   NMKLayers[2].PAL          =0x00;
   }

   for(tb=0;tb<16;tb+=2){
      ta = (RAM[0x14000+tb+tb]<<8) | (RAM[0x14002+tb+tb]);
      WriteWord(&RAM[0x14100+tb], ta);
      ta = (RAM[0x18000+tb+tb]<<8) | (RAM[0x18002+tb+tb]);
      WriteWord(&RAM[0x18100+tb], ta);
   }

   WriteLong(&RAM[0x14200],0x00000000);
   WriteLong(&RAM[0x14204],0xFFFFFFFF);

   RenderNMKLayer(0);

   RenderNMKLayer(1);

   RenderNMKSprites(0);

   RenderNMKLayer(2);
}

static void draw_macross_2(void)
{
   int ta,tb;

   ClearPaletteMap();

   NMKLayerCount=0;

   if(RefreshBuffers){
   NMKLayers[0].RAM          =RAM+0x20000;
   NMKLayers[0].GFX16        =GFX_BG0;
   NMKLayers[0].GFX8         =NULL;
   NMKLayers[0].MSK16        =BG0_Mask;
   NMKLayers[0].MSK8         =NULL;
   NMKLayers[0].SCR          =RAM+0x1C800;
   NMKLayers[0].PAL          =0x00;

   NMKLayers[2].RAM          =RAM_FG0;
   NMKLayers[2].GFX16        =NULL;
   NMKLayers[2].GFX8         =GFX_FG0;
   NMKLayers[2].MSK16        =NULL;
   NMKLayers[2].MSK8         =FG0_Mask;
   NMKLayers[2].SCR          =RAM+0x1CA00;
   NMKLayers[2].PAL          =pal_fg;

   }

   // GFX BG0 bank switch

   ta = ReadWord(&RAM[0x10018]) & 0x0003;

   NMKLayers[0].GFX16 = GFX_BG0 + (ta * 0x100000);
   NMKLayers[0].MSK16 = BG0_Mask + (ta * 0x1000);

   // Scroll BG0 fix

   for(tb=0;tb<16;tb+=2){
      ta = (RAM[0x1C000+tb+tb]<<8) | (RAM[0x1C002+tb+tb]);
      WriteWord(&RAM[0x1C800+tb], ta);
   }

/*    WriteWord(&RAM[0x1C800], ReadWord(&RAM[0x090E0])); */
/*    WriteWord(&RAM[0x1C802], ReadWord(&RAM[0x090E4])); */

   // Scroll FG0 fix

   WriteLong(&RAM[0x1CA00],0x00000000);
   WriteLong(&RAM[0x1CA04],0xFFFFFFFF);

   RenderNMKLayer(0);

   RenderNMKSprites(0);

   RenderNMKLayer(2);
}

// video













// Game drivers...
















/* tdragonb uses the infamous seibu sound system !!! */
static struct VIDEO_INFO video_bioship =
{
   DrawNMK,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_bjtwin =
{
  DrawBombJackTwin,
   384,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_blkheart =
{
   draw_macross_2,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   NULL,
   56.18
};
static struct VIDEO_INFO video_macross2 =
{
   draw_macross_2,
   384,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_mustang =
{
   DrawMustang,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_sabotenb =
{
   DrawBombJackTwin,
   384,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_ssmissin =
{
   draw_macross_2,
   256,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_strahl =
{
   DrawStrahl,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_tdragon =
{
   DrawThunderDragon,
   256,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_tdragon2 =
{
  draw_macross_2,
   384,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct VIDEO_INFO video_tforceh =
{
   DrawTaskForceHarrier,
   256,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   NULL,
   56
};
static struct DIR_INFO dir_acrobatm[] =
{
   { "acrobatm", },
   { NULL, },
};
GAME( acrobatm, "Acrobat Mission", UPL, 1992, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_acrobatm,
	.video = &video_ssmissin,
	.exec = execute_bioship,
	.long_name_jpn = "âVâàâgâëü[âï",
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_bioship[] =
{
   { "bio_ship_paladin", },
   { "bioship", },
   { "bshippal", },
   { NULL, },
};
GAME( bioship, "Bio Ship Paladin", UPL, 1990, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_bioship,
	.video = &video_bioship,
	.exec = execute_bioship,
	.long_name_jpn = "ëFÆêÉíèÍâSâéâë",
	.board = "UPL-90062",
	.sound = sound_hachamf, //sound_bjtwin,
);
#define load_blkhearj load_blkheart
static struct DIR_INFO dir_blkhearj[] =
{
   { "blkhearj", },
   { "blkheart", },
   { NULL, },
};
GAME( blkhearj, "Black Heart (Japan)", UPL, 1991, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_tdragon2,
	.video = &video_blkheart,
	.exec = execute_bioship,
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_blkheart[] =
{
   { "blkheart", },
   { ROMOF( "blkhearj" ), },
   { CLONEOF( "blkhearj" ), },
   { NULL, },
};
GAME( blkheart, "Black Heart", UPL, 1991, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_blkheart,
	.video = &video_blkheart,
	.exec = execute_bioship,
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_bjtwin[] =
{
   { "bomb_jack_twin", },
   { "bjtwin", },
   { "bjt", },
   { NULL, },
};
GAME( bjtwin, "Bomb Jack Twin", NMK, 1993, GAME_PLATFORM,
	.input = input_tdragon2,
	.dsw = dsw_bjtwin,
	.video = &video_bjtwin,
	.exec = execute_tdragon2,
	.long_name_jpn = "â{âôâWâââbâNâcâCâô",
	.sound = sound_bjtwin,
);
static struct DIR_INFO dir_hachamf[] =
{
   { "hacha_mecha_fighter", },
   { "hachamf", },
   { NULL, },
};
GAME( hachamf, "Hacha Mecha Fighter", NMK, 1991, GAME_NOT_WORKING,
	.input = input_tdragon2,
	.dsw = dsw_hachamf,
	.video = &video_bioship,
	.exec = execute_bioship,
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_macross[] =
{
   { "macross", },
   { "sdf_macross", },
   { NULL, },
};
GAME( macross, "SDF Macross", BANPREST, 1992, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_tdragon2,
	.video = &video_ssmissin,
	.exec = execute_bioship,
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_macross2[] =
{
   { "macross2", },
   { "sdf_macross2", },
   { NULL, },
};
GAME( macross2, "Macross 2", BANPREST, 1992, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_tdragon2,
	.video = &video_macross2,
	.exec = execute_tdragon2,
	.sound = sound_tdragon2,
);
static struct DIR_INFO dir_mustang[] =
{
   { "mustang", },
   { NULL, },
};
GAME( mustang, "USAAF Mustang", UPL, 1990, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_mustang,
	.video = &video_mustang,
	.exec = execute_bioship,
	.board = "UPL-90058",
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_sabotenb[] =
{
   { "saboten_bombers", },
   { "sabotenb", },
   { NULL, },
};
GAME( sabotenb, "Saboten Bombers", NMK, 1992, GAME_PLATFORM,
	.input = input_tdragon2,
	.dsw = dsw_sabotenb,
	.video = &video_sabotenb,
	.exec = execute_tdragon2,
	.sound = sound_bjtwin,
);
static struct DIR_INFO dir_ssmissin[] =
{
   { "ssmissin", },
   { NULL, },
};
GAME( ssmissin, "S.S. Mission", COMAD, 1992, GAME_SHOOT,
	.input = input_ssmissin,
	.dsw = dsw_ssmissin,
	.video = &video_ssmissin,
	.exec = execute_tdragon2,
	.sound = sound_ssmissin,
);
static struct DIR_INFO dir_strahl[] =
{
   { "strahl", },
   { NULL, },
};
GAME( strahl, "Strahl", UPL, 1992, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_strahl,
	.video = &video_strahl,
	.exec = execute_bioship,
	.long_name_jpn = "âVâàâgâëü[âï",
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_tforceh[] =
{
   { "task_force_harrier", },
   { "tforceh", },
   { "tskfrceh", },
   { "tharrier", },
   { "tharierj", },
   { NULL, },
};
GAME( tforceh, "Task Force Harrier", UPL, 1989, GAME_SHOOT,
	.input = input_tforceh,
	.dsw = dsw_tforceh,
	.video = &video_tforceh,
	.exec = execute_tforceh,
	.board = "UPL-89050",
	.sound = sound_tdragon2,
);
static struct DIR_INFO dir_tdragon2[] =
{
   { "thunder_dragon2", },
   { "tdragon2", },
   { NULL, },
};
GME( tdragon2, "Thunder Dragon 2", NMK, 1993, GAME_SHOOT);
static struct DIR_INFO dir_tdragon[] =
{
   { "thunder_dragon", },
   { "tdragon", },
   { "thunderd", },
   { NULL, },
};
GAME( tdragon, "Thunder Dragon", NMK, 1991, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_tdragon,
	.video = &video_tdragon,
	.exec = execute_bioship,
	.long_name_jpn = "ùïù´",
	.sound = sound_hachamf,
);
static struct DIR_INFO dir_tdragonb[] =
{
   { "thunder_dragon_bl", },
   { "thndrdbl", },
   { "tdragonb", },
   { "thunderd", },
   { ROMOF("tdragon"), },
   { CLONEOF("tdragon"), },
   { NULL, },
};
GAME( tdragonb, "Thunder Dragon (bootleg)", BOOTLEG, 1991, GAME_SHOOT,
	.input = input_tdragon2,
	.dsw = dsw_tdragonb,
	.video = &video_tdragon,
	.exec = execute_tdragon2,
	.long_name_jpn = "ùïù´ (bootleg)",
);

