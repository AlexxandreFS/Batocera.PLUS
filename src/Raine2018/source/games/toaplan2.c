/******************************************************************************/
/*                                                                            */
/*                          TOAPLAN 68000 SYSTEM#2                            */
/*                          ----------------------                            */
/*   CPU: 68000 (Z80)                                                         */
/* SOUND: YM2151 M6295 (YM3812)                                               */
/* VIDEO: 320x240 TOAPLAN CUSTOM <3xBG0 1xSPR (1xFG0)>                        */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "2151intf.h"
#include "3812intf.h"
#include "decode.h"
#include "sasound.h"		// sample support routines
#include "ymz280b.h"
#include "adpcm.h"
#include "savegame.h"
#include "blit.h" // clear_game_screen
#include "timer.h"
#include "mame/eeprom.h"
#include "video/priorities.h"
#include "sound/toaplan2.h"

// use cache for solid tiles/sprites...
#define USE_CACHE

static GfxLayout raizing_textlayout =
{
	8,8,	/* 8x8 characters */
	1024,	/* 1024 characters */
	4,		/* 4 bits per pixel */
	{ 0, 1, 2, 3 },
	{ 0, 4, 8, 12, 16, 20, 24, 28 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	8*32
};

static struct GFX_LIST raizing_gfxdecodeinfo[] =
{
	{ REGION_GFX2, &raizing_textlayout, },		/* Extra-text layer */
	{ -1 } /* end of array */
};

static struct INPUT_INFO input_vfive[] =
{
   INP1( COIN1, 0x000000, 0x08 ),
   INP1( COIN2, 0x000000, 0x10 ),
   INP1( TILT, 0x000000, 0x02 ),
   INP1( SERVICE, 0x000000, 0x01 ),

   INP1( P1_START, 0x000000, 0x20 ),
   INP1( P1_UP, 0x000001, 0x01 ),
   INP1( P1_DOWN, 0x000001, 0x02 ),
   INP1( P1_LEFT, 0x000001, 0x04 ),
   INP1( P1_RIGHT, 0x000001, 0x08 ),
   INP1( P1_B1, 0x000001, 0x10 ),
   INP1( P1_B2, 0x000001, 0x20 ),

   INP1( P2_START, 0x000000, 0x40 ),
   INP1( P2_UP, 0x000002, 0x01 ),
   INP1( P2_DOWN, 0x000002, 0x02 ),
   INP1( P2_LEFT, 0x000002, 0x04 ),
   INP1( P2_RIGHT, 0x000002, 0x08 ),
   INP1( P2_B1, 0x000002, 0x10 ),
   INP1( P2_B2, 0x000002, 0x20 ),

   END_INPUT
};

/*************
   FIX EIGHT
 *************/


/* The bankswitch code is directly taken from mame.
   I am not familliar with this, and I have not much time right now... */

static unsigned long PCMBanksize;

static void raizing_oki6295_set_bankbase( int chip, int channel, int base )
{
	/* The OKI6295 ROM space is divided in four banks, each one indepentently
	   controlled. The sample table at the beginning of the addressing space is
	   divided in four pages as well, banked together with the sample data. */
  unsigned char *rom = PCMROM + chip*PCMBanksize;
  /* copy the samples */
  memcpy(rom + channel * 0x10000, rom + 0x40000 + base, 0x10000);
  /* and also copy the samples address table */
  rom += channel * 0x100;
  memcpy(rom, rom + 0x40000 + base, 0x100);

}

static WRITE_HANDLER( raizing_okim6295_bankselect_0 )
{
	raizing_oki6295_set_bankbase( 0, 0,  (data       & 0x0f) * 0x10000);
	raizing_oki6295_set_bankbase( 0, 1, ((data >> 4) & 0x0f) * 0x10000);
}

static WRITE_HANDLER( raizing_okim6295_bankselect_1 )
{
	raizing_oki6295_set_bankbase( 0, 2,  (data       & 0x0f) * 0x10000);
	raizing_oki6295_set_bankbase( 0, 3, ((data >> 4) & 0x0f) * 0x10000);
}

// code from mame:
// the last 0x10000 bytes of the oki6295 are banked
// i suspect this is only on the bootleg
static WRITE_HANDLER( fixeighb_oki_bankswitch_w )
{
  data &= 7;
  if (data <= 4)
    OKIM6295_bankswitch(0, data);
}

static struct ROM_INFO rom_fixeight[] =
{
  { "tp-026-1", 0x080000, 0xf7b1746a, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
   {     "tp-026-2", 0x00040000, 0x85063f1f, REGION_SOUND1, 0, LOAD_NORMAL, },
   {     "tp-026-3", 0x00200000, 0xe5578d98, 0, 0, 0, },
   {     "tp-026-4", 0x00200000, 0xb760cb53, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_fixeight[] =
{
   INP1( COIN1, 0x01F010, 0x08 ),
   INP1( COIN2, 0x01F010, 0x10 ),
   INP1( TILT, 0x01F010, 0x02 ),
   INP1( SERVICE, 0x01F010, 0x01 ),

   INP1( P1_START, 0x01F010, 0x20 ),
   INP1( P1_UP, 0x01F000, 0x01 ),
   INP1( P1_DOWN, 0x01F000, 0x02 ),
   INP1( P1_LEFT, 0x01F000, 0x04 ),
   INP1( P1_RIGHT, 0x01F000, 0x08 ),
   INP1( P1_B1, 0x01F000, 0x10 ),
   INP1( P1_B2, 0x01F000, 0x20 ),

   INP1( P2_START, 0x01F010, 0x40 ),
   INP1( P2_UP, 0x01F004, 0x01 ),
   INP1( P2_DOWN, 0x01F004, 0x02 ),
   INP1( P2_LEFT, 0x01F004, 0x04 ),
   INP1( P2_RIGHT, 0x01F004, 0x08 ),
   INP1( P2_B1, 0x01F004, 0x10 ),
   INP1( P2_B2, 0x01F004, 0x20 ),

   INP1( P3_START, 0x01F008, 0x40 ),
   INP1( P3_UP, 0x01F008, 0x01 ),
   INP1( P3_DOWN, 0x01F008, 0x02 ),
   INP1( P3_LEFT, 0x01F008, 0x04 ),
   INP1( P3_RIGHT, 0x01F008, 0x08 ),
   INP1( P3_B1, 0x01F008, 0x10 ),
   INP1( P3_B2, 0x01F008, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_fix_eight_0[] =
{
   { _("Max Players"),           0x01, 0x02 },
   { "2",                     0x00},
   { "3",                     0x01},
   DSW_SCREEN( 0x00, 0x02),
   { _("Shooting Style"),        0x04, 0x02 },
   { _("Fully-auto"),            0x00},
   { _("Semi-auto"),             0x04},
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x20},
   { MSG_4COIN_1PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0x00},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_1COIN_4PLAY,         0x80},
   { MSG_1COIN_6PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_fix_eight_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("Every 500k"),            0x00},
   { _("Every 300k"),            0x04},
   { _("300k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_fix_eight_2[] =
{
   { _("Territory"),             0x0F, 0x0E },     // WHY was there 0x10 ? There are 14 values !
   { _("Europe"),                0x09},
   { _("Korea (Taito)"),         0x00},
   { _("Korea"),                 0x01},
   { _("Hong Kong (Taito)"),     0x02},
   { _("Hong Kong"),             0x03},
   { _("Taiwan (Taito)"),        0x04},
   { _("Taiwan"),                0x05},
   { _("Asia (Taito)"),          0x06},
   { _("Asia"),                  0x07},
   { _("Europe (Taito)"),        0x08},
   { _("USA (Taito America)"),   0x0A},
   { _("USA"),                   0x0B},
   { _("Japan"),                 0x0E},
   { _("Japan (Taito)"),         0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_fixeight[] =
{
   { 0x01F08C, 0x00, dsw_data_fix_eight_0 },
   { 0x01F090, 0x00, dsw_data_fix_eight_1 },
   { 0x01F094, 0x00, dsw_data_fix_eight_2 },
   { 0,        0,    NULL,      },
};

static struct YM2151interface ym2151_interface =
{
   1,                   	// 1 chip
   3580000,             	// dogyuun says 3.58MHz...
   { YM3012_VOL(160,OSD_PAN_LEFT,160,OSD_PAN_RIGHT) },
   { NULL },
   { NULL },
};

static struct OKIM6295interface m6295_interface =
{
   1,				// 1 chip
   { 27000000/10/132 },			// guessed
   { REGION_SOUND1 },	// rom list
   { 120 },
};

static struct OKIM6295interface kbash2_interface =
{
   2,				// 1 chip
   { 16000000/16/132, 16000000/16/132 },			// guessed
   { REGION_SOUND1, REGION_SOUND2 },	// rom list
   { 120,120 },
};

static struct OKIM6295interface raizing_m6295_interface =
{
   1,				// 1 chip
   { 7575 },			// guessed
   { REGION_SMP1 },	// rom list
   { 160 },
};

/* Now that fixeight has a REGION_SOUND1 in its roms, we must define this
 * separately since loading of sample is manual here because of the banks */
static struct OKIM6295interface fix_eight_bootleg_m6295_interface =
{
   1,				// 1 chip
   { 14000000/16/165 },			// taken from mame
   { 0 },	// rom list
   { 120 },
};

static struct OKIM6295interface fixeight_m6295_interface =
{
   1,				// 1 chip
   { 14000000/16/165 },			// taken from mame
   { REGION_SOUND1 },	// rom list
   { 120 },
};

static struct YMZ280Binterface ymz280b_interface =
{
	1,
	{ 16934400 },
	{ REGION_SOUND1 },
	{ YM3012_VOL(200,MIXER_PAN_CENTER,200,MIXER_PAN_CENTER) }, // mono
	{ NULL }
};

static struct SOUND_INFO sound_truxton2[] =
{
   { SOUND_YM2151J, &ym2151_interface,    },
   { SOUND_M6295,   &m6295_interface,     },
   { 0,             NULL,                 },
};

static struct SOUND_INFO sound_kbash[] =
{
   { SOUND_YM2151J, &ym2151_interface,    	  },
   { SOUND_M6295,   &raizing_m6295_interface,     },
   { 0,             NULL,                 	  },
};

static struct SOUND_INFO sound_kbash2[] =
{
   { SOUND_M6295,   &kbash2_interface,     },
   { 0,             NULL,                 	  },
};

static struct SOUND_INFO sound_bbakraid[] =
{
   { SOUND_YMZ280B,   &ymz280b_interface,     },
   { 0,             NULL,                 },
};

static struct SOUND_INFO sound_fixeighb[] =
{
   { SOUND_M6295,   &fix_eight_bootleg_m6295_interface,     },
   { 0,             NULL,                 },
};

static struct SOUND_INFO sound_vfive[] =
{
   { SOUND_M6295,   &fixeight_m6295_interface,     },
   { 0,             NULL,                 },
};

/*************
   FIX EIGHT BOOTLEG
 *************/


static struct ROM_INFO rom_fixeighb[] =
{
   {     "tp-026-3", 0x00200000, 0xe5578d98, 0, 0, 0, },
   {     "tp-026-4", 0x00200000, 0xb760cb53, 0, 0, 0, },
   { "1.bin", 0x80000, 0x888f19ac, 0, 0, 0 }, // REGION_SMP1, 0, LOAD_NORMAL },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x80000,
            "3.bin",  0xcc77d4b4, "2.bin",  0xed715488),
   {        "4.bin", 0x00008000, 0xa6aca465, 0, 0, 0, },
   {        "5.bin", 0x00008000, 0x456dd16e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

/***************
   KNUCLE BASH
 ***************/



static struct ROM_INFO rom_kbash[] =
{
  { "kbash01.bin", 0x080000, 0x2965f81d, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
   {  "kbash02.bin", 0x00008000, 0x4cd882a1, 0, 0, 0, },
   {  "kbash03.bin", 0x00200000, 0x32ad508b, 0, 0, 0, },
   {  "kbash04.bin", 0x00200000, 0xe493c077, 0, 0, 0, },
   {  "kbash05.bin", 0x00200000, 0xb84c90eb, 0, 0, 0, },
   {  "kbash06.bin", 0x00200000, 0x9084b50a, 0, 0, 0, },
   {  "kbash07.bin", 0x00040000, 0x3732318f, REGION_SOUND1, 0, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_kbash2[] =
{
  { "mecat-m", 0x80000, 0xbd2263c6, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "mecat-34", 0x400000, 0x6be7b37e, 0, 0, 0, },
  { "mecat-12", 0x400000, 0x49e46b1f, 0, 0, 0, },
  { "mecat-s", 0x80000, 0x3eb7adf4, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "eprom", 0x40000, 0x31115cb9, REGION_SMP2, 0x00000, LOAD_NORMAL },
  { "050917-10", 0x10000, 0x6b213183, REGION_USER1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_kbash[] =
{
   INP1( COIN1, 0x01F018, 0x08 ),
   INP1( COIN2, 0x01F018, 0x10 ),
   INP1( TILT, 0x01F018, 0x02 ),
   INP1( SERVICE, 0x01F018, 0x01 ),
   INP1( TEST, 0x01F018, 0x04 ),

   INP1( P1_START, 0x01F018, 0x20 ),
   INP1( P1_UP, 0x01F010, 0x01 ),
   INP1( P1_DOWN, 0x01F010, 0x02 ),
   INP1( P1_LEFT, 0x01F010, 0x04 ),
   INP1( P1_RIGHT, 0x01F010, 0x08 ),
   INP1( P1_B1, 0x01F010, 0x10 ),
   INP1( P1_B2, 0x01F010, 0x20 ),
   INP1( P1_B3, 0x01F010, 0x40 ),

   INP1( P2_START, 0x01F018, 0x40 ),
   INP1( P2_UP, 0x01F014, 0x01 ),
   INP1( P2_DOWN, 0x01F014, 0x02 ),
   INP1( P2_LEFT, 0x01F014, 0x04 ),
   INP1( P2_RIGHT, 0x01F014, 0x08 ),
   INP1( P2_B1, 0x01F014, 0x10 ),
   INP1( P2_B2, 0x01F014, 0x20 ),
   INP1( P2_B3, 0x01F014, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_knuckle_bash_0[] =
{
   { _("Discount"),              0x01, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x01},
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_knuckle_bash_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("100k then every 400k"),  0x00},     // "100000 400000" in _("test mode")
   { _("100k only"),             0x04},
   { _("200k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x00},
   { "4",                     0x10},
   { "3",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },     // This has an effect only in _("test mode")
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_knuckle_bash_2[] =
{
   { _("Territory"),             0x0F, 0x09 },     // WHY was there 0x10 ? There are 9 values !
   { _("Japan"),                 0x00},
   { _("USA, Europe (Atari)"),   0x01, 0x00 },
   { _("Europe, USA (Atari)"),   0x02, 0x00 },
   { _("Korea"),                 0x03},
   { _("Hong Kong"),             0x04},
   { _("South East Asia"),       0x06},
   { _("Taiwan"),                0x07},
   { _("USA"),                   0x09},
   { _("Europe"),                0x0A},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_kbash2[] =
{
   { _("Territory"),             0x0F, 0x07 },     // WHY was there 0x10 ? There are 9 values !
   { _("Japan (taito license)"),                 0x00},
   { _("Korea (Unite license)"), 0x03},
   { _("Hong Kong"),             0x04},
   { _("Taiwan"),                0x05},
   { _("South East Asia (Charterfield License)"),             0x06},
   { _("South East Asia"),       0x0e},
   { _("Korea"),                0x0b},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_kbash[] =
{
   { 0x01F004, 0x00, dsw_data_knuckle_bash_0 },
   { 0x01F006, 0x00, dsw_data_knuckle_bash_1 },
   { 0x01F008, 0x02, dsw_data_knuckle_bash_2 },
   { 0,        0,    NULL,      },
};

static struct DSW_INFO dsw_kbash2[] =
{
   { 0x01F004, 0x00, dsw_data_knuckle_bash_0 },
   { 0x01F008, 0x00, dsw_data_knuckle_bash_1 },
   { 0x01F00c, 0x06, dsw_data_kbash2 },
   { 0,        0,    NULL,      },
};

/***************
   SNOW BROS 2
 ***************/


static struct ROM_INFO rom_snowbro2[] =
{
  { "pro-4", 0x080000, 0x4c7ee341, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
   {       "rom3-l", 0x00100000, 0xeb06e332, 0, 0, 0, },
   {       "rom3-h", 0x00080000, 0xdf4a952a, 0, 0, 0, },
   {       "rom2-l", 0x00100000, 0xe9d366a9, 0, 0, 0, },
   {       "rom2-h", 0x00080000, 0x9aab7a62, 0, 0, 0, },
  { "rom4", 0x80000, 0x638f341e, REGION_SMP1, 0x00000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_snowbro2[] =
{
   INP1( COIN1, 0x01F01C, 0x08 ),
   INP1( COIN2, 0x01F01C, 0x10 ),
   INP1( TILT, 0x01F01C, 0x02 ),
   INP1( SERVICE, 0x01F01C, 0x01 ),

   INP1( P1_START, 0x01F01C, 0x20 ),
   INP1( P1_UP, 0x01F00C, 0x01 ),
   INP1( P1_DOWN, 0x01F00C, 0x02 ),
   INP1( P1_LEFT, 0x01F00C, 0x04 ),
   INP1( P1_RIGHT, 0x01F00C, 0x08 ),
   INP1( P1_B1, 0x01F00C, 0x10 ),
   INP1( P1_B2, 0x01F00C, 0x20 ),

   INP1( P2_START, 0x01F01C, 0x40 ),
   INP1( P2_UP, 0x01F010, 0x01 ),
   INP1( P2_DOWN, 0x01F010, 0x02 ),
   INP1( P2_LEFT, 0x01F010, 0x04 ),
   INP1( P2_RIGHT, 0x01F010, 0x08 ),
   INP1( P2_B1, 0x01F010, 0x10 ),
   INP1( P2_B2, 0x01F010, 0x20 ),

   INP1( P3_START, 0x01F014, 0x40 ),
   INP1( P3_UP, 0x01F014, 0x01 ),
   INP1( P3_DOWN, 0x01F014, 0x02 ),
   INP1( P3_LEFT, 0x01F014, 0x04 ),
   INP1( P3_RIGHT, 0x01F014, 0x08 ),
   INP1( P3_B1, 0x01F014, 0x10 ),
   INP1( P3_B2, 0x01F014, 0x20 ),

   INP1( P4_START, 0x01F018, 0x40 ),
   INP1( P4_UP, 0x01F018, 0x01 ),
   INP1( P4_DOWN, 0x01F018, 0x02 ),
   INP1( P4_LEFT, 0x01F018, 0x04 ),
   INP1( P4_RIGHT, 0x01F018, 0x08 ),
   INP1( P4_B1, 0x01F018, 0x10 ),
   INP1( P4_B2, 0x01F018, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_snow_bros_2_0[] =
{
   { _("Discount"),              0x01, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x01},
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_snow_bros_2_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("100k only"),             0x00},
   { _("100k and 500k"),         0x04},     // "100000 500000" in _("test mode")
   { _("200k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "4",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Max Players"),           0x80, 0x02 },
   { "4",                     0x00},
   { "2",                     0x80},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_snow_bros_2_2[] =
{
   { _("Language"),              0x1C, 0x07 },     // WHY was there 0x3C ? Bit 5 is used below !
   { _("Japan/Japanese"),        0x00},
   { _("America/English"),       0x04},
   { _("Europe/English"),        0x08},
   { _("Korea/Japanese"),        0x0C},
   { _("HongKong/Japanese"),     0x10},
   { _("Taiwan/Japanese"),       0x14},
   { _("Asia/Japanese"),         0x18},
   { _("All Rights Reserved"),   0x20, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x20},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_snowbro2[] =
{
   { 0x01F004, 0x00, dsw_data_snow_bros_2_0 },
   { 0x01F008, 0x00, dsw_data_snow_bros_2_1 },
   { 0x01F001, 0x08, dsw_data_snow_bros_2_2 },
   { 0,        0,    NULL,      },
};

/*************
   TRUXTON 2
 *************/


static struct ROM_INFO rom_truxton2[] =
{
  { "tp024_1.bin", 0x080000, 0xf5cfe6ee, REGION_ROM1, 0x000000, LOAD_NORMAL },
  { "tp024_2.bin", 0x80000, 0xf2f6cae4, REGION_SMP1, 0x00000, LOAD_NORMAL },
   { "tp024_3.bin", 0x00100000, 0x47587164, 0, 0, 0, },
   { "tp024_4.bin", 0x00100000, 0x805c449e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_truxton2[] =
{
   INP1( COIN1, 0x01F00A, 0x08 ),
   INP1( COIN2, 0x01F00A, 0x10 ),
   INP1( TILT, 0x01F00A, 0x02 ),
   INP1( SERVICE, 0x01F00A, 0x01 ),

   INP1( P1_START, 0x01F00A, 0x20 ),
   INP1( P1_UP, 0x01F006, 0x01 ),
   INP1( P1_DOWN, 0x01F006, 0x02 ),
   INP1( P1_LEFT, 0x01F006, 0x04 ),
   INP1( P1_RIGHT, 0x01F006, 0x08 ),
   INP1( P1_B1, 0x01F006, 0x10 ),
   INP1( P1_B2, 0x01F006, 0x20 ),
   INP1( P1_B3, 0x01F006, 0x40 ),

   INP1( P2_START, 0x01F00A, 0x40 ),
   INP1( P2_UP, 0x01F008, 0x01 ),
   INP1( P2_DOWN, 0x01F008, 0x02 ),
   INP1( P2_LEFT, 0x01F008, 0x04 ),
   INP1( P2_RIGHT, 0x01F008, 0x08 ),
   INP1( P2_B1, 0x01F008, 0x10 ),
   INP1( P2_B2, 0x01F008, 0x20 ),
   INP1( P2_B3, 0x01F008, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_tatsujin_2_0[] =
{
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_tatsujin_2_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("70k then every 200k"),   0x00},     // "70000 200000" in _("test mode")
   { _("100k then every 250k"),  0x04},     // "100000 250000" in _("test mode")
   { _("100k only"),             0x08},
   { _("200k only"),             0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "4",                     0x20},
   { "2",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_tatsujin_2_2[] =
{
   { _("Language"),              0x0F, 0x07 },
   { _("Japan/Tatsujin2"),       0x00},
   { _("USA/Truxton2"),          0x01},
   { _("Europe/Truxton2"),       0x02},
   { _("HongKong/Tatsujin2"),    0x03},
   { _("Korea/Tatsujin2"),       0x04},
   { _("Taiwan/Tatsujin2"),      0x05},
   { _("SE Asia/Tatsujin2"),     0x06},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_truxton2[] =
{
   { 0x01F000, 0x00, dsw_data_tatsujin_2_0 },
   { 0x01F002, 0x00, dsw_data_tatsujin_2_1 },
   { 0x01F004, 0x00, dsw_data_tatsujin_2_2 },
   { 0,        0,    NULL,      },
};

/***********
   DOGYUUN
 ***********/


static struct ROM_INFO rom_dogyuun[] =
{
  { "tp022_01.r16", 0x080000, 0x79eb2429, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
   { "tp022_2.w30", 0x40000, 0x043271b3, REGION_SMP1, 0x00000, LOAD_NORMAL },
   {  "tp022_3.r16", 0x00100000, 0x191b595f, 0, 0, 0, },
   {  "tp022_4.r16", 0x00100000, 0xd58d29ca, 0, 0, 0, },
   {  "tp022_5.r16", 0x00200000, 0xd4c1db45, 0, 0, 0, },
   {  "tp022_6.r16", 0x00200000, 0xd48dc74f, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_dogyuun[] =
{
   INP1( COIN1, 0x01F018, 0x08 ),
   INP1( COIN2, 0x01F018, 0x10 ),
   INP1( TILT, 0x01F018, 0x02 ),
   INP1( SERVICE, 0x01F018, 0x01 ),

   INP1( P1_START, 0x01F018, 0x20 ),
   INP1( P1_UP, 0x01F010, 0x01 ),
   INP1( P1_DOWN, 0x01F010, 0x02 ),
   INP1( P1_LEFT, 0x01F010, 0x04 ),
   INP1( P1_RIGHT, 0x01F010, 0x08 ),
   INP1( P1_B1, 0x01F010, 0x10 ),
   INP1( P1_B2, 0x01F010, 0x20 ),
   INP1( P1_B3, 0x01F010, 0x40 ),

   INP1( P2_START, 0x01F018, 0x40 ),
   INP1( P2_UP, 0x01F014, 0x01 ),
   INP1( P2_DOWN, 0x01F014, 0x02 ),
   INP1( P2_LEFT, 0x01F014, 0x04 ),
   INP1( P2_RIGHT, 0x01F014, 0x08 ),
   INP1( P2_B1, 0x01F014, 0x10 ),
   INP1( P2_B2, 0x01F014, 0x20 ),
   INP1( P2_B3, 0x01F014, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_dogyuun_0[] =
{
   { MSG_FREE_PLAY,              0x01, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x01},
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_dogyuun_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("200k only"),             0x00},
   { _("200k, 400k and 600k"),   0x04, 0x00 },     // _("200000 every - max 3") in _("test mode")
   { _("400k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_dogyuun_2[] =
{
   { _("Version"),               0x0F, 0x09 },
   { _("Japan"),                 0x00},
   { _("America"),               0x01},
   { _("America - Atari"),       0x02},
   { _("Europe"),                0x03},
   { _("Hong Kong"),             0x04},
   { _("Korea"),                 0x05},
   { _("Taiwan"),                0x06},
   { _("SE Asia"),               0x08},
   { _("Japan - Taito"),         0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_dogyuun[] =
{
   { 0x01F08C, 0x00, dsw_data_dogyuun_0 },
   { 0x01F090, 0x00, dsw_data_dogyuun_1 },
   { 0x01F094, 0x00, dsw_data_dogyuun_2 },
   { 0,        0,    NULL,      },
};

/***********
   WHOOPEE
 ***********/


static struct ROM_INFO rom_whoopee[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "whoopee.1",  0x28882e7e, "whoopee.2",  0x6796f133),
  { "hd647180.025", 0x08000, 0x101c0358, REGION_ROM2, 0x00000, LOAD_NORMAL },
   {  "tp025-4.bin", 0x00100000, 0xab97f744, 0, 0, 0, },
   {  "tp025-3.bin", 0x00100000, 0x7b16101e, 0, 0, 0, },
 //{   "ppbb07.bin", 0x00008000, 0x456dd16e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_tekipaki[] =
{
   INP1( COIN1, 0x00E020, 0x08 ),
   INP1( COIN2, 0x00E020, 0x10 ),
   INP1( TILT, 0x00E020, 0x02 ),
   INP1( SERVICE, 0x00E020, 0x01 ),

   INP1( P1_START, 0x00E020, 0x20 ),
   INP1( P1_UP, 0x00E050, 0x01 ),
   INP1( P1_DOWN, 0x00E050, 0x02 ),
   INP1( P1_LEFT, 0x00E050, 0x04 ),
   INP1( P1_RIGHT, 0x00E050, 0x08 ),
   INP1( P1_B1, 0x00E050, 0x10 ),
   INP1( P1_B2, 0x00E050, 0x20 ),

   INP1( P2_START, 0x00E020, 0x40 ),
   INP1( P2_UP, 0x00E060, 0x01 ),
   INP1( P2_DOWN, 0x00E060, 0x02 ),
   INP1( P2_LEFT, 0x00E060, 0x04 ),
   INP1( P2_RIGHT, 0x00E060, 0x08 ),
   INP1( P2_B1, 0x00E060, 0x10 ),
   INP1( P2_B2, 0x00E060, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_whoopee_0[] =
{
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_whoopee_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("200k then every 300k"),  0x00},     // _("200000 300000 every") in _("test mode")
   { _("150k then every 200k"),  0x04},     // _("150000 200000 every") in _("test mode")
   { _("200k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_whoopee_2[] =
{
   { _("Language"),              0x07, 0x08 },     // WHY was there 0x0F ? Bit 3 is used below !
   { _("Japan/Whoopee"),         0x00},
   { _("Asia/PipiBibi"),         0x01},
   { _("HongKong/PipiBibi"),     0x02},
   { _("Taiwan/PipiBibi"),       0x03},
   { _("USA/PipiBibi"),          0x04},
   { _("USA (Romstar)/PipiBibi"),0x05},
   { _("Europe/PipiBibi"),       0x06},
   { _("Europe (Nova)/PipiBibi"),0x07},
   { _("Nudity"),                0x08, 0x02 },
   { _("Low"),                   0x00},
   { _("High, but censored"),    0x08, 0x00 },
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_whoopee[] =
{
   { 0x00E000, 0x00, dsw_data_whoopee_0 },
   { 0x00E010, 0x00, dsw_data_whoopee_1 },
   { 0x00E030, 0x00, dsw_data_whoopee_2 },
   { 0,        0,    NULL,      },
};

static struct YM3812interface ym3812_interface =
{
   1,                   // 1 x YM3812
   3000000,             // 3 MHz  (emu only)
   { 200 },             // Volume (emu only)
   { NULL }
};

static struct SOUND_INFO sound_whoopee[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { 0,             NULL,                 },
};


/*****************
   PIPI AND BIBI
 *****************/


static struct ROM_INFO rom_pipibibi[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "ppbb05.bin",  0x3d51133c, "ppbb06.bin",  0x14c92515 ),
  { "ppbb08.bin", 0x8000, 0x101c0358, REGION_ROM2, 0x0000, LOAD_NORMAL },
   {   "ppbb01.bin", 0x00080000, 0x0fcae44b, 0, 0, 0, },
   {   "ppbb02.bin", 0x00080000, 0x8bfcdf87, 0, 0, 0, },
   {   "ppbb03.bin", 0x00080000, 0xabdd2b8b, 0, 0, 0, },
   {   "ppbb04.bin", 0x00080000, 0x70faa734, 0, 0, 0, },
 //{   "ppbb07.bin", 0x00008000, 0x456dd16e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_pipibibi[] =
{
   INP1( COIN1, 0x00E02C, 0x08 ),
   INP1( COIN2, 0x00E02C, 0x10 ),
   INP1( TILT, 0x00E02C, 0x02 ),
   INP1( SERVICE, 0x00E02C, 0x01 ),

   INP1( P1_START, 0x00E02C, 0x20 ),
   INP1( P1_UP, 0x00E030, 0x01 ),
   INP1( P1_DOWN, 0x00E030, 0x02 ),
   INP1( P1_LEFT, 0x00E030, 0x04 ),
   INP1( P1_RIGHT, 0x00E030, 0x08 ),
   INP1( P1_B1, 0x00E030, 0x10 ),
   INP1( P1_B2, 0x00E030, 0x20 ),

   INP1( P2_START, 0x00E02C, 0x40 ),
   INP1( P2_UP, 0x00E034, 0x01 ),
   INP1( P2_DOWN, 0x00E034, 0x02 ),
   INP1( P2_LEFT, 0x00E034, 0x04 ),
   INP1( P2_RIGHT, 0x00E034, 0x08 ),
   INP1( P2_B1, 0x00E034, 0x10 ),
   INP1( P2_B2, 0x00E034, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_pipi_and_bibi_0[] =
{
DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_pipi_and_bibi_2[] =
{
   { _("Language"),              0x07, 0x07 },     // WHY was there 0x0F ? Bit 3 is used below !
   { _("Japan (Ryouta)/Whoopee"),0x00},
   { _("HongKong/PipiBibi"),     0x01},
   { _("World/PipiBibi"),        0x02},
   { _("America/PipiBibi"),      0x04},
   { _("Europe/PipiBibi"),       0x05},
   { _("Spain&Portugal/PipiBibi"),0x06},
   { _("World (Ryouta)/PipiBibi"),0x07},
   { _("Nudity"),                0x08, 0x02 },
   { _("Low"),                   0x00},
   { _("High, but censored"),    0x08, 0x00 },
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_pipibibi[] =
{
   { 0x00E020, 0x00, dsw_data_pipi_and_bibi_0 },
   { 0x00E024, 0x00, dsw_data_whoopee_1 },
   { 0x00E028, 0x05, dsw_data_pipi_and_bibi_2 },
   { 0,        0,    NULL,      },
};

/*************
   TEKI PAKI
 *************/


static struct ROM_INFO rom_tekipaki[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x010000,
            "tp020-1.bin",  0xd8420bd5, "tp020-2.bin",  0x7222de8e),
   { "tp020-3.bin", 0x00080000, 0x2d5e2201, 0, 0, 0, },
   { "tp020-4.bin", 0x00080000, 0x3ebbe41e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_teki_paki_0[] =
{
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_teki_paki_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_teki_paki_2[] =
{
   { _("Version"),               0x0F, 0x0A },
   { _("Japan"),                 0x00},
   { _("America"),               0x01},
   { _("Europe"),                0x02},
   { _("Hong Kong"),             0x03},
   { _("Korea"),                 0x04},
   { _("Taiwan"),                0x05},
   { _("Taiwan - Spacy"),        0x06},
   { _("America - Romstar"),     0x07},
   { _("Hong Kong - Honest"),    0x08},
   { _("Japan - Tecmo"),         0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_tekipaki[] =
{
   { 0x00E000, 0x00, dsw_data_teki_paki_0 },
   { 0x00E010, 0x00, dsw_data_teki_paki_1 },
   { 0x00E030, 0x00, dsw_data_teki_paki_2 },
   { 0,        0,    NULL,      },
};

/********
   GHOX
 ********/


static struct ROM_INFO rom_ghox[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "tp021-01.u10",  0x9e56ac67, "tp021-02.u11",  0x15cac60f),
   { "tp021-03.u36", 0x00080000, 0xa15d8e9d, 0, 0, 0, },
   { "tp021-04.u37", 0x00080000, 0x26ed1c9a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_ghox_0[] =
{
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_ghox_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("100k then every 200k"),  0x00},     // _("100000 200000 every") in _("test mode")
   { _("100k then every 300k"),  0x04},     // _("100000 300000 every") in _("test mode")
   { _("100k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_ghox_2[] =
{
   { _("Language"),              0x0F, 0x10 },
   { _("Japan"),                 0x00},
   { _("America"),               0x01},
   { _("Europe"),                0x02},
   { _("Hong Kong (Honest)"),    0x03},
   { _("Korea"),                 0x04},
   { _("Taiwan"),                0x05},
   { _("Spain & Portugal (APM)"),0x06},
   { _("Italy (Star Elect)"),    0x07},
   { _("UK (JP Leisure)"),       0x08},
   { _("America (Romstar)"),     0x09},
   { _("Europe (Nova)"),         0x0A},
   { _("USA (Taito America)"),   0x0B},
   { _("USA (Taito Japan)"),     0x0C},
   { _("Europe (Taito Japan)"),  0x0D},
   { _("Japan (null)"),          0x0E},
   { _("Japan (Taito Corp)"),    0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ghox[] =
{
   { 0x000003, 0x00, dsw_data_ghox_0 },
   { 0x000004, 0x00, dsw_data_ghox_1 },
   { 0x000005, 0x00, dsw_data_ghox_2 },
   { 0,        0,    NULL,      },
};

/************
   V - FIVE
 ************/


static struct ROM_INFO rom_vfive[] =
{
   { "tp027_01.bin", 0x00080000, 0x731d50f4, REGION_ROM1,0,LOAD_SWAP_16 },
   { "tp027_02.bin", 0x00100000, 0x877b45e8, 0, 0, 0, },
   { "tp027_03.bin", 0x00100000, 0xb1fc6362, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_v_five_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_v_five_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("300k and 800k"),         0x00},
   { _("300k then every 800k"),  0x04},     // _("300000 800000 every") in _("test mode")
   { _("200k only"),             0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_v_five_2[] =
{
   { _("Language"),              0x0F, 0x02 },
   { _("Japanese (Toaplan)"),    0x00},
   { _("Japanese (Taito)"),      0x03},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_vfive[] =
{
   { 0x000003, 0x00, dsw_data_v_five_0 },
   { 0x000004, 0x00, dsw_data_v_five_1 },
   { 0x000005, 0x00, dsw_data_v_five_2 },
   { 0,        0,    NULL,      },
};


/*****************
   GRIND STORMER
 *****************/


static struct ROM_INFO rom_grindstm[] =
{
   {       "01.bin", 0x00080000, 0x4923f790, REGION_ROM1,0,LOAD_SWAP_16 },
   { "tp027_02.bin", 0x00100000, 0x877b45e8, 0, 0, 0, },
   { "tp027_03.bin", 0x00100000, 0xb1fc6362, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_grind_stormer_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x20},
   { MSG_4COIN_1PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0x00},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_2COIN_4PLAY,         0x80},
   { MSG_2COIN_6PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_grind_stormer_2[] =
{
   { _("Language"),              0x0F, 0x0B },
   { _("Korea, Unite Trading")},
   { _("Korea"),                 0x01},
   { _("Hong Kong"),             0x02},
   { _("Hong Kong, Charterfield"),0x03, 0x00 },
   { _("Taiwan, Anomoto Int."),  0x04, 0x00 },
   { _("Taiwan"),                0x05},
   { _("SE Asia, Charterfield"), 0x06, 0x00 },
   { _("SE Asia"),               0x07},
   { _("Europe"),                0x08},
   { _("USA, Sammy Corp."),      0x0A, 0x00 },
   { _("USA"),                   0x0B},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_grindstm[] =
{
   { 0x000003, 0x00, dsw_data_grind_stormer_0 },
   { 0x000004, 0x00, dsw_data_v_five_1 },
   { 0x000005, 0x08, dsw_data_grind_stormer_2 },
   { 0,        0,    NULL,      },
};

/***************************
   SHIPPU MAHOU DAISAKUSEN
 ***************************/

#define rom_shippumd rom_kgpe // very special clone
static struct ROM_INFO rom_kgpe[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "ma02rom1.bin",  0xa678b149, "ma02rom0.bin",  0xf226a212),
  { "ma02rom2.bin", 0x10000, 0xdde8a57e, REGION_ROM2, 0x00000, LOAD_NORMAL },
   { "ma02rom3.bin", 0x00200000, 0x0e797142, 0, 0, 0, },
   { "ma02rom4.bin", 0x00200000, 0x72a6fa53, 0, 0, 0, },
   { "ma02rom5.bin", 0x00008000, 0x116ae559, 0, 0, 0, },
  { "ma02rom6.bin", 0x80000, 0x199e7cae, REGION_SMP1, 0x00000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_bgaregh[] =
{
   INP1( COIN1, 0x000000, 0x08 ),
   INP1( COIN2, 0x000000, 0x10 ),
   INP1( TILT, 0x000000, 0x02 ),
   INP1( SERVICE, 0x000000, 0x01 ),
   INP1( TEST, 0x000000, 0x04 ),

   INP1( P1_START, 0x000000, 0x20 ),
   INP1( P1_UP, 0x000001, 0x01 ),
   INP1( P1_DOWN, 0x000001, 0x02 ),
   INP1( P1_LEFT, 0x000001, 0x04 ),
   INP1( P1_RIGHT, 0x000001, 0x08 ),
   INP1( P1_B1, 0x000001, 0x10 ),
   INP1( P1_B2, 0x000001, 0x20 ),
   INP1( P1_B3, 0x000001, 0x40 ),

   INP1( P2_START, 0x000000, 0x40 ),
   INP1( P2_UP, 0x000002, 0x01 ),
   INP1( P2_DOWN, 0x000002, 0x02 ),
   INP1( P2_LEFT, 0x000002, 0x04 ),
   INP1( P2_RIGHT, 0x000002, 0x08 ),
   INP1( P2_B1, 0x000002, 0x10 ),
   INP1( P2_B2, 0x000002, 0x20 ),
   INP1( P2_B3, 0x000002, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_shippu_mahoudai_0[] =
{
   { MSG_FREE_PLAY,              0x01, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x01},
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_shippu_mahoudai_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("Every 300k"),            0x00},
   { _("200k and 500k"),         0x04},
   { _("200k"),                  0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_shippu_mahoudai_2[] =
{
   { _("Language"),              0x0F, 0x08 },
   { _("Japan"),                 0x00},
   { _("USA"),                   0x02},
   { _("Europe"),                0x04},
   { _("South East Asia"),       0x06},
   { _("China"),                     0x08},
   { _("Korea"),                     0x0A},
   { _("Hong Kong"),                     0x0C},
   { _("Taiwan"),                     0x0E},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_shippumd[] =
{
   { 0x000003, 0x00, dsw_data_shippu_mahoudai_0 },
   { 0x000004, 0x00, dsw_data_shippu_mahoudai_1 },
   { 0x000005, 0x00, dsw_data_shippu_mahoudai_2 },
   { 0,        0,    NULL,      },
};

static struct DSW_INFO sstriker_dsw[] =
{
   { 0x000003, 0x00, dsw_data_shippu_mahoudai_0 },
   { 0x000004, 0x00, dsw_data_shippu_mahoudai_1 },
   { 0x000005, 0x04, dsw_data_shippu_mahoudai_2 },
   { 0,        0,    NULL,      },
};

static struct DSW_INFO dsw_kgpe[] =
{
   { 0x000003, 0x00, dsw_data_shippu_mahoudai_0 },
   { 0x000004, 0x00, dsw_data_shippu_mahoudai_1 },
   { 0x000005, 0x02, dsw_data_shippu_mahoudai_2 },
   { 0,        0,    NULL,      },
};

/********************
   MAHOU DAISAKUSEN
 ********************/


static struct ROM_INFO rom_mahoudai[] =
{
  { "ra_ma_01.01", 0x080000, 0x970ccc5c, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "ra_ma_01.02", 0x10000, 0xeabfa46d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "ra_ma_01.03", 0x100000, 0x54e2bd95, 0,0,0 }, // GFX1
  { "ra_ma_01.04", 0x100000, 0x21cd378f, 0,0,0 },
  { "ra_ma_01.05", 0x008000, 0xc00d1e80, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "ra_ma_01.06", 0x40000, 0x6edb2ab8, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_INFO dsw_mahoudai[] =
{
   { 0x000003, 0x00, dsw_data_shippu_mahoudai_0 },
   { 0x000004, 0x00, dsw_data_shippu_mahoudai_1 },
// { 0x000005, 0x00, dsw_data_mahoudai_2 },     // These Dip Switches have NO effect !
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_sstriker[] =
{
  { "ra-ma-01.01", 0x080000, 0x92259f84, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "ra_ma_01.03", 0x100000, 0x54e2bd95, 0,0,0 },
  { "ra_ma_01.04", 0x100000, 0x21cd378f, 0,0,0 },
  { "ra-ma-01.05", 0x008000, 0x88b58841, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/***************************
   ARMED POLICE BATRIDER B
 ***************************/


static struct ROM_INFO rom_batrider[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "prg0b.u22",  0x4f3fc729, "prg1b.u23",  0x8e70b492),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x080000,
            "prg2.u21" ,  0xbdaa5fbf, "prg3.u24" ,  0x7aa9f941),
  { "snd.u77", 0x40000, 0x56682696, 0,0,0 },
   {    "rom-1.bin", 0x00400000, 0x0df69ca2, 0, 0, 0, },
   {    "rom-2.bin", 0x00400000, 0x1bfea593, 0, 0, 0, },
   {    "rom-3.bin", 0x00400000, 0x60167d38, 0, 0, 0, },
   {    "rom-4.bin", 0x00400000, 0xbee03c94, 0, 0, 0, },
  { "rom-5.bin", 0x100000, 0x4274daf6, 0, 0, 0 },
  { "rom-6.bin", 0x100000, 0x2a1c2426, 0, 0, 0 },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_batrider_0[] =
{
   DSW_TEST_MODE( 0x01, 0x00),
   { _("Credits to Start"),      0x02, 0x02 },     // _("Stick Mode") when _("Free Play")
   { _("1 Credit"),              0x00},     //   - _("Normal")
   { _("2 Credits"),             0x02},     //   - _("Special")
   { MSG_COIN1,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x04},
   { MSG_1COIN_3PLAY,         0x08},
   { MSG_1COIN_4PLAY,         0x0C},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x14},
   { MSG_4COIN_1PLAY,         0x18},
   { MSG_FREE_PLAY,              0x1C},
   { MSG_COIN2,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_1COIN_4PLAY,         0x60},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_3COIN_1PLAY,         0xA0},
   { MSG_4COIN_1PLAY,         0xC0},
   { MSG_1COIN_1PLAY,         0xE0},
/* Dip Switches when _("Free Play") :
   { _("Hit Score"),             0x20, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x20},
   { _("Sound Effect"),          0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Music"),                 0x80, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
*/
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_batrider_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { _("Timer"),                 0x0C, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x04},
   { MSG_HARD,                0x08},
   { MSG_HARDEST,             0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "4",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_EXTRA_LIFE,          0xC0, 0x04 },
   { _("every 1500k"),           0x00},
   { _("every 1000k"),           0x40},
   { _("every 2000k"),           0x80},
   { _("None"),                  0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_batrider_2[] =
{
   DSW_SCREEN( 0x00, 0x01),
   DSW_DEMO_SOUND( 0x00, 0x02),
   { _("Stage Edit"),            0x04, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON ,                 0x04},
   DSW_CONTINUE_PLAY( 0x00, 0x08),
   { MSG_CHEAT,               0x10, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x10},
   { _("Guest Player"),           0x20, 0x02 },     // _("Guest Player") when _("Free Play")
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x20},
   { _("Player Select"),           0x40, 0x02 },     // _("Player Select") when _("Free Play")
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Special Course"),           0x80, 0x02 },     // _("Special Course") when _("Free Play")
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_batrider[] =
{
   { 0x000003, 0x00, dsw_data_batrider_0 },
   { 0x000004, 0x00, dsw_data_batrider_1 },
   { 0x000005, 0x00, dsw_data_batrider_2 },
   { 0,        0,    NULL,      },
};

static struct YM2151interface batrider_ym2151 =
{
   1,
   32000000/8,
   { YM3012_VOL(115,OSD_PAN_LEFT,115,OSD_PAN_RIGHT) },
   { NULL },
   { NULL },
};

static struct OKIM6295interface batrider_m6295 =
{
   2,
   //{ 20000, 20000 },
   { 32000000/10/132, 32000000/10/165 },
   { REGION_SOUND1,REGION_SOUND2 }, // If !=0 then these are REGION numbers !!!
   { 120,120 }
};

static struct SOUND_INFO sound_batrider[] =
{
   { SOUND_YM2151J, &batrider_ym2151,     },
   { SOUND_M6295,   &batrider_m6295,      },
   { 0,             NULL,                 },
};

/***************************
   ARMED POLICE BATRIDER A
 ***************************/


static struct ROM_INFO rom_batridra[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "prg0.bin",  0xf93ea27c, "prg1.bin",  0x8ae7f592),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x080000,
            "prg2.u21",  0xbdaa5fbf, "prg3.u24",  0x7aa9f941),
   {    "rom-1.bin", 0x00400000, 0x0df69ca2, 0, 0, 0, },
   {    "rom-2.bin", 0x00400000, 0x1bfea593, 0, 0, 0, },
   {    "rom-3.bin", 0x00400000, 0x60167d38, 0, 0, 0, },
   {    "rom-4.bin", 0x00400000, 0xbee03c94, 0, 0, 0, },
   {    "rom-5.bin", 0x00100000, 0x4274daf6, 0, 0, 0, },
   {    "rom-6.bin", 0x00100000, 0x2a1c2426, 0, 0, 0, },
   {      "snd.u77", 0x00040000, 0x56682696, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

/******************
   BATTLE GAREGGA
 ******************/

static struct YM2151interface battleg_ym2151 =
{
   1,
   32000000/8,
   { YM3012_VOL(100,OSD_PAN_LEFT,100,OSD_PAN_RIGHT) },
   { NULL },
   { NULL },
};

static struct OKIM6295interface battleg_m6295 =
{
   1,
   { 32000000/16/132 },
   { 0 },
   { 220 }
};

static struct OKIM6295interface batsugun_m6295 =
{
   1,
   { 20000 },			// guessed
   { 0 },
   { 220 }
};

static struct SOUND_INFO sound_battleg[] =
{
   { SOUND_YM2151J, &battleg_ym2151,     },
   { SOUND_M6295,   &battleg_m6295,    },
   { 0,             NULL,                },
};

static struct SOUND_INFO sound_batsugun[] =
{
   { SOUND_M6295,   &batsugun_m6295,    },
   { 0,             NULL,                },
};




static struct ROM_INFO rom_battleg[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "prg0.bin",  0xf80c2fc2, "prg1.bin",  0x2ccfdd1e),
   {     "rom1.bin", 0x00200000, 0x7eafdd70, 0, 0, 0, },
   {     "rom2.bin", 0x00200000, 0xb330e5e2, 0, 0, 0, },
   {     "rom3.bin", 0x00200000, 0x51b9ebfb, 0, 0, 0, },
   {     "rom4.bin", 0x00200000, 0xb333d81f, 0, 0, 0, },
   {     "rom5.bin", 0x00100000, 0xf6d49863, 0, 0, 0, },
   {      "snd.bin", 0x00020000, 0x68632952, 0, 0, 0, },
   {     "text.bin", 0x00008000, 0xe67fd534, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_bgaregc[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "u123",  0x88a4e66a, "u65",  0x5dea32a3),
  { "snd.bin", 0x20000, 0x68632952, 0, 0, 0 },
   {     "rom1.bin", 0x00200000, 0x7eafdd70, 0, 0, 0, },
   {     "rom2.bin", 0x00200000, 0xb330e5e2, 0, 0, 0, },
   {     "rom3.bin", 0x00200000, 0x51b9ebfb, 0, 0, 0, },
   {     "rom4.bin", 0x00200000, 0xb333d81f, 0, 0, 0, },
   {     "rom5.bin", 0x00100000, 0xf6d49863, 0, 0, 0, },
   {      "snd.bin", 0x00020000, 0x68632952, 0, 0, 0, },
   {     "text.bin", 0x00008000, 0xe67fd534, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_bgaregh[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "prg_0.bin",  0x951ecc07, "prg_1.bin",  0x729a60c6),
   {     "rom1.bin", 0x00200000, 0x7eafdd70, 0, 0, 0, },
   {     "rom2.bin", 0x00200000, 0xb330e5e2, 0, 0, 0, },
   {     "rom3.bin", 0x00200000, 0x51b9ebfb, 0, 0, 0, },
   {     "rom4.bin", 0x00200000, 0xb333d81f, 0, 0, 0, },
   {     "rom5.bin", 0x00100000, 0xf6d49863, 0, 0, 0, },
   {      "snd.bin", 0x00020000, 0x68632952, 0, 0, 0, },
   {     "text.bin", 0x00008000, 0xe67fd534, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_battle_garegga_0[] =
{
   DSW_TEST_MODE( 0x01, 0x00),
   { _("Credits to Start"),      0x02, 0x02 },
   { _("1 Credit"),              0x00},
   { _("2 Credits"),             0x02},
   { MSG_COIN1,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x04},
   { MSG_1COIN_3PLAY,         0x08},
   { MSG_1COIN_4PLAY,         0x0C},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x14},
   { MSG_4COIN_1PLAY,         0x18},
   { MSG_FREE_PLAY,           0x1C},
   { MSG_COIN2,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_1COIN_4PLAY,         0x60},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_3COIN_1PLAY,         0xA0},
   { MSG_4COIN_1PLAY,         0xC0},
   { MSG_1COIN_1PLAY,         0xE0},
/* Dip Switches when _("Free Play") :
   { _("Stick Mode"),            0x20, 0x02 },
   { _("Special"),               0x00},
   { _("Normal"),                0x20},
   { _("Sound Effect"),          0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Music"),                 0x80, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
*/
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_battle_garegga_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   DSW_SCREEN( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_LIVES,               0x70, 0x08 },
   { "3",                     0x00},
   { "4",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { "5",                     0x40},
   { "6",                     0x50},
   { _("Unlimited"),             0x60},
   { _("Invincibility"),         0x70},
   { MSG_EXTRA_LIFE,          0x80, 0x02 },     // New values if _("Territory") != _("Japan") :
   { _("Every 1000k"),           0x00},     //   - _("Every 2000k")
   { _("1000k and 2000k"),       0x80},     //   - _("None")
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_battle_garegga_2[] =
{
   { _("Territory"),             0x03, 0x04 },
   { _("Japan"),                 0x00},
   { _("Europe"),                0x01},
   { _("USA"),                   0x02},
   { _("Asia"),                  0x03},
   DSW_CONTINUE_PLAY( 0x00, 0x04),
   { _("Stage Edit"),            0x08, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON ,                 0x08},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_battle_garegc_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   DSW_SCREEN( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_LIVES,               0x70, 0x08 },
   { "3",                     0x00},
   { "4",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { "5",                     0x40},
   { "6",                     0x50},
   { _("Unlimited"),             0x60},
   { _("Invincibility"),         0x70},
   { MSG_EXTRA_LIFE,          0x80, 0x02 },     // New values if _("Territory") == _("Japan") :
   { _("Every 2000k"),           0x00},     //   - _("Every 1000k")
   { _("None"),                  0x80},     //   - _("1000k and 2000k")
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_battle_garegc_2[] =
{
   { _("Territory"),             0x03, 0x04 },
   { _("Japan"),                 0x00},
   { _("Denmark"),               0x01},
   { _("USA"),                   0x02},
   { _("China"),                 0x03},
   DSW_CONTINUE_PLAY( 0x00, 0x04),
   { _("Stage Edit"),            0x08, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON ,                 0x08},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_battleg[] =
{
   { 0x000003, 0x00, dsw_data_battle_garegga_0 },
   { 0x000004, 0x00, dsw_data_battle_garegga_1 },
   { 0x000005, 0x00, dsw_data_battle_garegga_2 },
   { 0,        0,    NULL,      },
};

static struct DSW_INFO dsw_bgaregh[] =
{
   { 0x000003, 0x00, dsw_data_battle_garegga_0 },
   { 0x000004, 0x00, dsw_data_battle_garegc_1 },
   { 0x000005, 0x03, dsw_data_battle_garegc_2 },
   { 0,        0,    NULL,      },
};

/************
   BATSUGUN
 ************/


static struct ROM_INFO rom_batsugun[] =
{
   {     "tp030_2.bin", 0x00040000, 0x276146f5, 0, 0, 0, },
   {    "tp030_3h.bin", 0x00100000, 0xed75730b, 0, 0, 0, },
   {    "tp030_3l.bin", 0x00100000, 0x3024b793, 0, 0, 0, },
   {    "tp030_4h.bin", 0x00100000, 0xd482948b, 0, 0, 0, },
   {    "tp030_4l.bin", 0x00100000, 0xfedb9861, 0, 0, 0, },
   {     "tp030_5.bin", 0x00100000, 0xbcf5ba05, 0, 0, 0, },
   {     "tp030_6.bin", 0x00100000, 0x0666fecd, 0, 0, 0, },
  { "tp030_01.bin", 0x080000, 0x3873d7dd, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_batsugun_0[] =
{
   { _("Continue"),              0x01, 0x02 },
   { MSG_NORMAL,              0x00},
   { _("Discount"),              0x01},
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x04, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x08),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x30},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_batsugun_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("1000k only"),            0x00},
   { _("500k and every 600k"),   0x04},
   { _("1500k only"),            0x08},
   { _("None"),                  0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "5",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_batsugun_2[] =
{
   { _("Territory"),             0x09, 14 },
   { _("Korea (Unite Trading)"), 0x00},
   { _("Korea"),                 0x01},
   { _("Hong Kong (Taito)"),     0x02},
   { _("Hong Kong"),             0x03},
   { _("Taiwan (Taito)"),        0x04},
   { _("Taiwan"),                0x05},
   { _("South East Asia(Taito)"),0x06},
   { _("South East Asia"),       0x07},
   { _("Europe (Taito)"),        0x08},
   { _("Europe"),                0x09},
   { _("USA (Taito)"),           0x0A},
   { _("USA"),                   0x0B},
   { _("Japan (Taito)"),         0x0C},
   { _("Japan"),                 0x0E},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_batsugun[] =
{
   { 0x000003, 0x00, dsw_data_batsugun_0 },
   { 0x000004, 0x00, dsw_data_batsugun_1 },
   { 0x000005, 0x09, dsw_data_batsugun_2 },
   { 0,        0,    NULL,      },
};

#define ROM_COUNT       16

/*

 Supported romsets:

  0 - Tatsujin 2              - 1992 - TOAPLAN
  1 - Snow Bros 2             - 1994 - HANAFRAM/TOAPLAN
  2 - Pipi Bibi               - 1991 - RYOUTA KIKAKU (BOOTLEG)
  3 - Whoopee                 - 1991 - TOAPLAN
  4 - Knuckle Bash            - 1993 - TOAPLAN/ATARI
  5 - Fix Eight               - 1992 - TOAPLAN
  6 - Dogyuun                 - 1992 - TOAPLAN
  7 - Teki Paki               - 1991 - TOAPLAN
  8 - Ghox                    - 1991 - TOAPLAN
  9 - Shippu Mahou Daisakusen - 1993 - RAIZING
 10 - Mahou Daisakusen        - 1994 - RAIZING
 11 - Batrider                - 1998 - RAIZING
 12 - V Five                  - 1992 - TOAPLAN
 13 - Batsugun                - 1993 - TOAPLAN
 14 - Battle Garegga          - 1996 - RAIZING
 15 - Fix Eight Bootleg       - 1992 - BOOTLEG

 Todo:

 - Screen draw is a bit slow
 - Knuckle Bash has no sound (turbo)
 - Fix Eight has protection and no sound (turbo)
 - Dogyuun has no sound (turbo)
 - Ghox has no sound and bad hiscores (protection/no sound rom)
 - Teki Paki has no sound (protection/no sound rom)

*/

static int romset;

static UINT8 *GFX_BG0_SOLID;

static UINT8 *RAM_FG0;
static UINT8 *RAM_GFX_FG0;

static UINT8 *GFX_FG0;
static UINT8 *GFX_FG0_SOLID;

/*------------------------------------*/

// YM2151 Handler
// --------------

static UINT16 YM2151Read68k(UINT32 offset)
{
   return YM2151_status_port_0_r(0)&0xFF;
}

static void YM2151Write68k(UINT32 offset,UINT16 data)
{
   static int reg;

   if((offset&3)<2){
      reg=data&0xFF;
   }
   else{
     YM2151_register_port_0_w(offset,reg);
     YM2151_data_port_0_w(offset,data&0xFF);
   }
}

static void ym2151_z80_wb(UINT16 offset, UINT8 data)
{
  if(!(offset & 1))
      YM2151_register_port_0_w(offset, data);
   else
      YM2151_data_port_0_w(offset, data);
}

static void M6295WriteBank68k(UINT32 offset,UINT16 data)
{
  //OKIM6295_bankswitch(0,data&1);
  OKIM6295_set_bank_base(0, ALL_VOICES, (data & 1) * 0x40000);
  //M6295buffer_bankswitch(0,data&0x01);
}

static void M6295Write68k(UINT32 offset,UINT16 data)
{
  OKIM6295_data_0_w( 0, data&0xFF );
  //M6295buffer_request(0,data&0xFF);
}

#if 0
// unused ?!
static void m6295_bank_z80_wb(UINT16 offset, UINT8 data)
{
   M6295buffer_bankswitch(0, data & 1);
}
#endif

static void m6295_z80_wb(UINT16 offset, UINT8 data)
{
  OKIM6295_data_0_w( 0, data&0xFF );
  //M6295buffer_request(0, data);
}

static UINT8 m6295_z80_rb(UINT16 offset)
{
  //return M6295buffer_status(0);
  return OKIM6295_status_0_r( 0 );
   //return 0;
}

/*------------------------------------*/

/*

0000-0FFF | BG0
1000-1FFF | BG1
2000-2FFF | BG2
3000-37FF | OBJECT

*/

typedef struct TP2VCU				// information about 1 chip
{
   UINT8 *VRAM;					// VRAM (0x4000 bytes)
   UINT8 *SCROLL;				// SCROLL (0x20 bytes)
   UINT32 vram_pos;				// current offset in VRAM
   UINT32 scroll_pos;				// current offset in SCROLL
   UINT32 status;				// some status read
   UINT8 *GFX_BG;				// GFX data
   UINT8 *MASK_BG;				// MASK data
   UINT32 tile_max;				// tile count
} TP2VCU;

static int vcu_num;


static struct TP2VCU tp2vcu[2];			// max 2 chips

static char *layer_id_name[2][4] =
{
   { "BG0",   "BG1",   "BG2",   "OBJ",   },
   { "BG0#2", "BG1#2", "BG2#2", "OBJ#2", },
};

static int layer_id_data[2][4];

static void init_tp2vcu(UINT32 num)
{
   tp2vcu[num].vram_pos   = 0x0000;
   tp2vcu[num].scroll_pos = 0x0000;
   tp2vcu[num].status     = 0x0000;

   layer_id_data[num][0] = add_layer_info(layer_id_name[num][0]);
   layer_id_data[num][1] = add_layer_info(layer_id_name[num][1]);
   layer_id_data[num][2] = add_layer_info(layer_id_name[num][2]);
   layer_id_data[num][3] = add_layer_info(layer_id_name[num][3]);

   vcu_num = num+1;
}

static void tp2vcu_0_ww(UINT32 offset, UINT16 data)
{
   switch(offset&0x0E){
      case 0x00:                        // Port Address
         tp2vcu[0].vram_pos = (data<<1) & 0x3FFE;
      break;
      case 0x04:                        // Port Data
         WriteWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos], data);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x06:                        // Port Data
         WriteWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos], data);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x08:                        // Port Address
         tp2vcu[0].scroll_pos = (data<<1) & 0x001E;
      break;
      case 0x0C:                        // Port Data
         WriteWord(&tp2vcu[0].SCROLL[tp2vcu[0].scroll_pos], data);
         tp2vcu[0].scroll_pos += 0x0002;
         tp2vcu[0].scroll_pos &= 0x001E;
      break;
      default:
         print_debug("tp2vcu[0] ww(%04x,%04x)\n", offset&0x0E, data);
      break;
   }
}

static UINT16 tp2vcu_0_rw(UINT32 offset)
{
   UINT16 ret;

   switch(offset&0x0E){
      case 0x04:                        // Port Data
         ret = ReadWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos]);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x06:                        // Port Data
         ret = ReadWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos]);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x0C:                        // Status
         ret = tp2vcu[0].status;
         tp2vcu[0].status ^= 1;
      break;
      default:
         ret = 0x0000;
         print_debug("tp2vcu[0] rw(%04x)\n", offset&0x0E);
      break;
   }

   return ret;
}

static UINT8 tp2vcu_0_rb(UINT32 offset)
{
   UINT16 ret;

   ret = tp2vcu_0_rw(offset);

   if((offset&1)==0)
      return (UINT8) ((ret>>8)&0xFF);
   else
      return (UINT8) ((ret>>0)&0xFF);
}

static void tp2vcu_0_ww_alt(UINT32 offset, UINT16 data)
{
   switch(offset&0x0E){
      case 0x0C:                        // Port Address
         tp2vcu[0].vram_pos = (data<<1) & 0x3FFE;
      break;
      case 0x08:                        // Port Data
         WriteWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos], data);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x0A:                        // Port Data
         WriteWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos], data);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x04:                        // Port Address
         tp2vcu[0].scroll_pos = (data<<1) & 0x001E;
      break;
      case 0x00:                        // Port Data
         WriteWord(&tp2vcu[0].SCROLL[tp2vcu[0].scroll_pos], data);
         tp2vcu[0].scroll_pos += 0x0002;
         tp2vcu[0].scroll_pos &= 0x001E;
      break;
      default:
         print_debug("tp2vcu[0] ww(%04x,%04x)\n", offset&0x0E, data);
      break;
   }
}

static UINT16 tp2vcu_0_rw_alt(UINT32 offset)
{
   UINT16 ret;

   switch(offset&0x0E){
      case 0x08:                        // Port Data
         ret = ReadWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos]);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x0A:                        // Port Data
         ret = ReadWord(&tp2vcu[0].VRAM[tp2vcu[0].vram_pos]);
         tp2vcu[0].vram_pos += 0x0002;
         tp2vcu[0].vram_pos &= 0x3FFE;
      break;
      case 0x00:                        // Status
         ret = tp2vcu[0].status;
         tp2vcu[0].status ^= 1;
      break;
      default:
         ret = 0x0000;
         print_debug("tp2vcu[0] rw(%04x)\n", offset&0x0E);
      break;
   }

   return ret;
}

static UINT8 tp2vcu_0_rb_alt(UINT32 offset)
{
   UINT16 ret;

   ret = tp2vcu_0_rw_alt(offset);

   if((offset&1)==0)
      return (UINT8) ((ret>>8)&0xFF);
   else
      return (UINT8) ((ret>>0)&0xFF);
}


static void tp2vcu_1_ww(UINT32 offset, UINT16 data)
{
   switch(offset&0x0E){
      case 0x00:                        // Port Address
         tp2vcu[1].vram_pos = (data<<1) & 0x3FFE;
      break;
      case 0x04:                        // Port Data
         WriteWord(&tp2vcu[1].VRAM[tp2vcu[1].vram_pos], data);
         tp2vcu[1].vram_pos += 0x0002;
         tp2vcu[1].vram_pos &= 0x3FFE;
      break;
      case 0x06:                        // Port Data
         WriteWord(&tp2vcu[1].VRAM[tp2vcu[1].vram_pos], data);
         tp2vcu[1].vram_pos += 0x0002;
         tp2vcu[1].vram_pos &= 0x3FFE;
      break;
      case 0x08:                        // Port Address
         tp2vcu[1].scroll_pos = (data<<1) & 0x001E;
      break;
      case 0x0C:                        // Port Data
         WriteWord(&tp2vcu[1].SCROLL[tp2vcu[1].scroll_pos], data);
         tp2vcu[1].scroll_pos += 0x0002;
         tp2vcu[1].scroll_pos &= 0x001E;
      break;
      default:
         print_debug("tp2vcu[1] ww(%04x,%04x)\n", offset&0x0E, data);
      break;
   }
}

static UINT16 tp2vcu_1_rw(UINT32 offset)
{
   UINT16 ret;

   switch(offset&0x0E){
      case 0x04:                        // Port Data
         ret = ReadWord(&tp2vcu[1].VRAM[tp2vcu[1].vram_pos]);
         tp2vcu[1].vram_pos += 0x0002;
         tp2vcu[1].vram_pos &= 0x3FFE;
      break;
      case 0x06:                        // Port Data
         ret = ReadWord(&tp2vcu[1].VRAM[tp2vcu[1].vram_pos]);
         tp2vcu[1].vram_pos += 0x0002;
         tp2vcu[1].vram_pos &= 0x3FFE;
      break;
      case 0x0C:                        // Status
         ret = tp2vcu[1].status;
         tp2vcu[1].status ^= 1;
      break;
      default:
         ret = 0x0000;
         print_debug("tp2vcu[1] rw(%04x)\n", offset&0x0E);
      break;
   }

   return ret;
}

static UINT8 tp2vcu_1_rb(UINT32 offset)
{
   UINT16 ret;

   ret = tp2vcu_1_rw(offset);

   if((offset&1)==0)
      return (UINT8) ((ret>>8)&0xFF);
   else
      return (UINT8) ((ret>>0)&0xFF);
}

/******************************************************************************/
/*  SCANLINE TIMER                                                            */
/******************************************************************************/
static UINT16 timer_faked;

static UINT16 TimerRead(UINT32 offset)
{
   timer_faked = (timer_faked+0x17)&0x1FF;

   return timer_faked;
}

/******************************************************************************/
/*  IOC                                                                       */
/******************************************************************************/

static void set_toaplan2_leds(UINT8 data)
{
   switch_led(0,(data>>0)&1);		// Coin A [Coin Inserted]
   switch_led(1,(data>>1)&1);		// Coin B [Coin Inserted]
   switch_led(2,(data>>2)&1);		// Coin A [Ready for coins]
   //switch_led(3,(data>>3)&1);		// Coin B [Ready for coins]
}

static void fix_eight_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x003C;		// 4 byte alignment
   offset |= 0x0001;


   switch(offset){
      case 0x1D:
         set_toaplan2_leds(data);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void fix_eight_ioc_ww(UINT32 offset, UINT16 data)
{
   fix_eight_ioc_wb(offset, (UINT8) (data&0xFF) );
}

static void dogyuun_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x003C;		// 4 byte alignment
   offset |= 0x0001;

   switch(offset){
      case 0x1D:
         set_toaplan2_leds(data);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void dogyuun_ioc_ww(UINT32 offset, UINT16 data)
{
   dogyuun_ioc_wb(offset, (UINT8) (data&0xFF) );
}


static void tatsujin_2_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x003E;		// 2 byte alignment
   offset |= 0x0001;

   switch(offset){
      case 0x1F:
         set_toaplan2_leds(data);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void tatsujin_2_ioc_ww(UINT32 offset, UINT16 data)
{
   tatsujin_2_ioc_wb(offset, (UINT8) (data&0xFF) );
}

static void whoopee_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x0070;		// 16 byte alignment
   offset |= 0x0001;

   switch(offset){
      case 0x41:
         set_toaplan2_leds(data);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void whoopee_ioc_ww(UINT32 offset, UINT16 data)
{
   whoopee_ioc_wb(offset, (UINT8) (data&0xFF) );
}

static void snow_bros_2_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x003C;		// 4 byte alignment
   offset |= 0x0001;

   switch(offset){
   case 0x31:
     M6295WriteBank68k(offset,data);
     break;
   case 0x35:
     set_toaplan2_leds(data);
     break;
   default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void snow_bros_2_ioc_ww(UINT32 offset, UINT16 data)
{
   snow_bros_2_ioc_wb(offset, (UINT8) (data&0xFF) );
}

static void knuckle_bash_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x003C;		// 4 byte alignment
   offset |= 0x0001;

   switch(offset){
      case 0x1D:
         set_toaplan2_leds(data);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void knuckle_bash_ioc_ww(UINT32 offset, UINT16 data)
{
   knuckle_bash_ioc_wb(offset, (UINT8) (data&0xFF) );
}

static void ghox_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0xFFFF;
   offset |= 0x0001;

   switch(offset){
      case 0x1001:
         set_toaplan2_leds(data);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void ghox_ioc_ww(UINT32 offset, UINT16 data)
{
   ghox_ioc_wb(offset, (UINT8) (data&0xFF) );
}

static UINT8 ghox_ioc_rb(UINT32 offset)
{
   UINT8 ret;

   offset &= 0xFFFF;
   offset |= 0x0001;

   switch(offset){
      case 0x0001:                      // status
         ret = 0xFF;
      break;
/*
      case 0x03:                        // sound comm?
         ret = 0x00;
      break;
      case 0x05:                        // credits?
         ret = 0x01;
      break;
*/
      case 0x0007:                      // dswa
         ret = get_dsw(0);
      break;
      case 0x0009:                      // dswb
         ret = get_dsw(1);
      break;
      case 0x000D:                      // p1 input
         ret = input_buffer[1];
      break;
      case 0x000F:                      // p2 input
         ret = input_buffer[2];
      break;
      case 0x0011:                      // misc input
         ret = input_buffer[0];
      break;
      case 0x100D:                      // dswc
         ret = get_dsw(2) & 0x0F;
      break;
      default:
         ret = 0x01;
         print_debug("ghox_z80_rb(%04x)\n", offset&0xFFFF);
      break;
   }

   return ret;
}

static UINT16 ghox_ioc_rw(UINT32 offset)
{
   return (UINT16) ghox_ioc_rb(offset);
}

static UINT8 v_five_ioc_rb(UINT32 offset)
{
   UINT8 ret;

   offset &= 0x003C;		// 4 byte alignment
   offset |= 0x0001;

   switch(offset){
      case 0x11:
         return input_buffer[1];
      break;
      case 0x15:
         return input_buffer[2];
      break;
      case 0x19:
         return input_buffer[0];
      break;
      default:
         ret = 0x00;
         print_debug("v_five_ioc_rb(%04x)\n", offset);
      break;
   }

   return ret;
}

static UINT16 v_five_ioc_rw(UINT32 offset)
{
   return (UINT16) v_five_ioc_rb(offset);
}

/******************************************************************************/
/*  PADDLE (GHOX)                                                             */
/******************************************************************************/

static UINT32 paddle_1_x;
static UINT32 paddle_2_x;

static UINT8 ghox_paddle_rb(UINT32 offset)
{
   if(offset == 0x100001)

      return paddle_1_x;

   else

      return paddle_2_x;
}

static void update_paddle(void)
{
   int px,py;

   paddle_1_x = 0;
   paddle_2_x = 0;

   /*

   emulate buttons with mouse buttons

   */

   if(*MouseB&1) RAM[0x00E004] |= 0x10;
   if(*MouseB&2) RAM[0x00E004] |= 0x20;

   /*

   emulate paddle with mouse x axis

   */

   GetMouseMickeys(&px,&py);

   px /= 4;
   py /= 4;

   paddle_1_x += px;

   /*

   hack -- use mouse y for emulating up/down
   not sure about this (is the game paddle
   only supposed to move on one axis?)

   */

   if(py < 0) input_buffer[1] |= 0x01;
   if(py > 0) input_buffer[1] |= 0x02;

   /*

   emulate paddle with joystick

   */

   // if(RAM[0x00E004] & 0x04) paddle_1_x -= 3;
   if(input_buffer[1] & 0x04) paddle_1_x -= 3;
   // if(RAM[0x00E004] & 0x08) paddle_1_x += 3;
   if(input_buffer[1] & 0x08) paddle_1_x += 3;

   // if(RAM[0x00E005] & 0x04) paddle_2_x -= 3;
   if(input_buffer[2] & 0x04) paddle_2_x -= 3;
   if(input_buffer[2] & 0x08) paddle_2_x += 3;
}

/******************************************************************************/
/*  TS-001-TURBO                                                              */
/******************************************************************************/

static UINT8 *RAM_TURBO;

static UINT8 TS_001_Turbo_RB(UINT32 offset)
{
   UINT8 ret;

   offset &= 0xFFFF;
   offset |= 0x0001;

   switch(offset){
      case 0xF001:		// CPU STATUS AA/FF/FE/FE/??
         ret = 0xFF;
      break;
      case 0xF005:		// DSWA
         ret = get_dsw(0);
      break;
      case 0xF007:		// DSWB
         ret = get_dsw(1);
      break;
      case 0xF009:		// DSWC
         ret = get_dsw(2);
      break;
      case 0xF00D:		// PROTECTION UNUSED? - STATUS
         ret = 0x00;
      break;
      case 0xF00F:		// PROTECTION UNUSED? - NOT READ
         ret = 0x00;
      break;
      case 0xF011:		// PROTECTION UNUSED? - READ RESULT
         ret = 0x00;
      break;
      case 0xF013:		// PROTECTION UNUSED? - READ RESULT
         ret = 0x00;
      break;
      default:
         ret = 0x00;
      break;
   }

   return ret;
}

static UINT16 TS_001_Turbo_RW(UINT32 offset)
{
   return TS_001_Turbo_RB(offset);
}

static void TS_001_Turbo_WB(UINT32 offset, UINT8 data)
{
   offset &= 0xFFFF;
   offset |= 0x0001;

   RAM_TURBO[offset>>1]=data;

   switch(offset){
      case 0xF001: if (romset == 6)
		     dogyuun_okisnd_w(data);
		   else
		     batsugun_okisnd_w(data);		// SOUND COMMAND LOW
      break;
      case 0xF003:		// SOUND COMMAND HIGH
      print_debug("TURBO: sound command: %02x%02x\n",RAM_TURBO[0xF003>>1],RAM_TURBO[0xF001>>1]);
      break;
      case 0xF005:		// DSWA
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      case 0xF007:		// DSWB
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      case 0xF009:		// DSWC
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      case 0xF00D:		// PROTECTION UNUSED? - COMMAND
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      case 0xF00F:		// PROTECTION UNUSED? - DATA
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      case 0xF011:		// PROTECTION UNUSED? - DATA
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      case 0xF013:		// PROTECTION UNUSED? - DATA
      print_debug("TURBO: %04x %02x\n",offset,data);
      break;
      default:
      //print_debug("TURBO: %04x %02x\n",offset,data);
      break;
   }
}

static void TS_001_Turbo_WW(UINT32 offset, UINT16 data)
{
   TS_001_Turbo_WB(offset, (UINT8) (data&0xFF) );
}

static void load_tp2_gfx(char *name1,char *name2, int size, UINT8 *RAM,
			 UINT8 *GFX)
{
  int ta,tb,tc;
  if(!load_rom(name1, RAM, size))return;           // GFX
  tb=0;
  for(ta=0;ta<size;ta+=2){
    tc=RAM[ta];
    GFX[tb+0] = (((tc&0x80)>>7)<<0);
    GFX[tb+1] = (((tc&0x40)>>6)<<0);
    GFX[tb+2] = (((tc&0x20)>>5)<<0);
    GFX[tb+3] = (((tc&0x10)>>4)<<0);
    GFX[tb+4] = (((tc&0x08)>>3)<<0);
    GFX[tb+5] = (((tc&0x04)>>2)<<0);
    GFX[tb+6] = (((tc&0x02)>>1)<<0);
    GFX[tb+7] = (((tc&0x01)>>0)<<0);
    tc=RAM[ta+1];
    GFX[tb+0] |= (((tc&0x80)>>7)<<1);
    GFX[tb+1] |= (((tc&0x40)>>6)<<1);
    GFX[tb+2] |= (((tc&0x20)>>5)<<1);
    GFX[tb+3] |= (((tc&0x10)>>4)<<1);
    GFX[tb+4] |= (((tc&0x08)>>3)<<1);
    GFX[tb+5] |= (((tc&0x04)>>2)<<1);
    GFX[tb+6] |= (((tc&0x02)>>1)<<1);
    GFX[tb+7] |= (((tc&0x01)>>0)<<1);
    tb+=8;
  }

  if(!load_rom(name2, RAM, size))return;           // GFX
  tb=0;
  for(ta=0;ta<size;ta+=2){
    tc=RAM[ta];
    GFX[tb+0] |= (((tc&0x80)>>7)<<2);
    GFX[tb+1] |= (((tc&0x40)>>6)<<2);
    GFX[tb+2] |= (((tc&0x20)>>5)<<2);
    GFX[tb+3] |= (((tc&0x10)>>4)<<2);
    GFX[tb+4] |= (((tc&0x08)>>3)<<2);
    GFX[tb+5] |= (((tc&0x04)>>2)<<2);
    GFX[tb+6] |= (((tc&0x02)>>1)<<2);
    GFX[tb+7] |= (((tc&0x01)>>0)<<2);
    tc=RAM[ta+1];
    GFX[tb+0] |= (((tc&0x80)>>7)<<3);
    GFX[tb+1] |= (((tc&0x40)>>6)<<3);
    GFX[tb+2] |= (((tc&0x20)>>5)<<3);
    GFX[tb+3] |= (((tc&0x10)>>4)<<3);
    GFX[tb+4] |= (((tc&0x08)>>3)<<3);
    GFX[tb+5] |= (((tc&0x04)>>2)<<3);
    GFX[tb+6] |= (((tc&0x02)>>1)<<3);
    GFX[tb+7] |= (((tc&0x01)>>0)<<3);
    tb+=8;
  }
}

/******************************************************************************/

static void load_truxton2(void)
{
   UINT8 *TMP;
   int ta,tb;

   romset=0;
   _z80iff = 3; // make sure the timers won't believe ints are disabled !

   if(!(GFX=AllocateMem(0x400000)))return;
   if(!(TMP=AllocateMem(0x100000)))return;

   load_tp2_gfx("tp024_4.bin","tp024_3.bin",0x100000,TMP,GFX);

   FreeMem(TMP);
   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x10000);

   RAMSize=0x34000+0x10000;

   if(!(RAM=AllocateMem(RAMSize)))return;

   memset(RAM+0x00000,0x00,0x34000);

   RAM_FG0 = RAM+0x20000;
   GFX_FG0 = RAM+0x34000;

   tb=0;
   for(ta=0x40000;ta<0x48000;ta++){
      GFX_FG0[tb++]=(ROM[ta]&0xF0)>>4;
      GFX_FG0[tb++]=(ROM[ta]&0x0F)>>0;
   }

   GFX_FG0_SOLID = make_solid_mask_8x8(GFX_FG0, 0x400);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x0FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // Fix Checksum

   WriteWord68k(&ROM[0x2EC10],0x4E71);          // nop

   // Input Check

   ROM[0x2EAFC]=0x60;

   // Fix 60000=Timer ???

   WriteWord68k(&ROM[0x1F6E8],0x4E75);          // rts

   WriteWord68k(&ROM[0x009FE],0x4E71);          // nop
   WriteWord68k(&ROM[0x01276],0x4E71);          // nop
   WriteWord68k(&ROM[0x012BA],0x4E71);          // nop
   WriteWord68k(&ROM[0x03150],0x4E71);          // nop
   WriteWord68k(&ROM[0x031B4],0x4E71);          // nop
   WriteWord68k(&ROM[0x0F20C],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EBFA],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EC7A],0x4E71);          // nop
   WriteWord68k(&ROM[0x1ECE8],0x4E71);          // nop
   WriteWord68k(&ROM[0x1ED00],0x4E71);          // nop
   WriteWord68k(&ROM[0x1ED5E],0x4E71);          // nop
   WriteWord68k(&ROM[0x1ED9A],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EDB2],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EEA2],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EEBA],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EEE6],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EF72],0x4E71);          // nop
   WriteWord68k(&ROM[0x1EFD0],0x4E71);          // nop
   WriteWord68k(&ROM[0x1F028],0x4E71);          // nop
   WriteWord68k(&ROM[0x1F05E],0x4E71);          // nop
   WriteWord68k(&ROM[0x1F670],0x4E71);          // nop
   WriteWord68k(&ROM[0x1F6C0],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FA08],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FAA4],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FADA],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FBA2],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FBDC],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FC1C],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FC8A],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FD24],0x4E71);          // nop
   WriteWord68k(&ROM[0x1FD7A],0x4E71);          // nop
   WriteWord68k(&ROM[0x2775A],0x4E71);          // nop
   WriteWord68k(&ROM[0x277D8],0x4E71);          // nop
   WriteWord68k(&ROM[0x2788C],0x4E71);          // nop
   WriteWord68k(&ROM[0x278BA],0x4E71);          // nop
   WriteWord68k(&ROM[0x2EC54],0x4E71);          // nop
   WriteWord68k(&ROM[0x2EC90],0x4E71);          // nop
   WriteWord68k(&ROM[0x2ECAC],0x4E71);          // nop
   WriteWord68k(&ROM[0x2ECCA],0x4E71);          // nop
   WriteWord68k(&ROM[0x2ECE6],0x4E71);          // nop
   WriteWord68k(&ROM[0x2ED1E],0x4E71);          // nop

   // Scrll Sync

   WriteLong68k(&ROM[0x0011C],0x001003E2);      //

   WriteLong68k(&ROM[0x001CC],0x4EB800C0);      // jmp  $C0.w
   WriteWord68k(&ROM[0x001D0],0x4E71);          // nop

   WriteLong68k(&ROM[0x000C0],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x000C4],0x00AA0000);      //

   WriteWord68k(&ROM[0x000C8],0x4EF9);          // jmp $2526C
   WriteLong68k(&ROM[0x000CA],0x0002526C);      //

   // 68000 Speed hack

   WriteLong68k(&ROM[0x0027E],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00282],0x00AA0000);      //

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x2EAC6],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x34000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x200000, 0x20000F, tp2vcu_0_rb, NULL);                 // GCU RAM (SCREEN)
   AddReadByte(0x700000, 0x70000F, NULL, RAM+0x01F000);                 // INPUT
   AddReadByte(0x700010, 0x700011, OKIM6295_status_0_r, NULL);                 // M6295
   AddReadByte(0x700014, 0x700017, YM2151Read68k, NULL);                // YM2151
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x200000, 0x20000F, tp2vcu_0_rw, NULL);                 // GCU RAM (SCREEN)
   AddReadWord(0x700000, 0x70000F, NULL, RAM+0x01F000);                 // INPUT
   AddReadWord(0x700010, 0x700011, OKIM6295_status_0_r, NULL);                 // M6295
   AddReadWord(0x700014, 0x700017, YM2151Read68k, NULL);                // YM2151
   AddReadWord(0x600000, 0x600001, TimerRead, NULL);                    // TIMER
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x700010, 0x700011, M6295Write68k, NULL);               // M6295
   AddWriteByte(0x700014, 0x700017, YM2151Write68k, NULL);              // YM2151
   AddWriteByte(0x700000, 0x70003F, tatsujin_2_ioc_wb, NULL);           // INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x200000, 0x20000F, tp2vcu_0_ww, NULL);               // GCU RAM (SCREEN)
   AddWriteWord(0x300000, 0x300FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x400000, 0x403FFF, NULL, RAM+0x020000);                // TEXT RAM (FG0 RAM)
   AddWriteWord(0x500000, 0x50FFFF, NULL, RAM+0x024000);                // CG RAM (FG0 GFX RAM)
   AddWriteWord(0x700010, 0x700011, M6295Write68k, NULL);               // M6295
   AddWriteWord(0x700014, 0x700017, YM2151Write68k, NULL);              // YM2151
   AddWriteWord(0x700000, 0x70003F, tatsujin_2_ioc_ww, NULL);           // INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void load_snowbro2(void)
{
   UINT8 *TMP;

   romset=1;
   _z80iff = 3; // make sure the timers won't believe ints are disabled !

   if(!(GFX=AllocateMem(0x600000)))return;
   if(!(TMP=AllocateMem(0x100000)))return;

   load_tp2_gfx("rom2-l","rom3-l",0x100000,TMP,GFX);
   load_tp2_gfx("rom2-h","rom3-h",0x80000,TMP,&GFX[0x400000]);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x18000);

   if(!(RAM=AllocateMem(0x20000)))return;

   memset(RAM+0x00000,0x00,0x20000);

   RAMSize=0x20000;

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x1FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // 68000 Speed hack
   // ----------------

   WriteLong68k(&ROM[0x060C2],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x060C6],0x00AA0000);      //

   // Kill the annoying reset instruction
   // -----------------------------------

   WriteWord68k(&ROM[0x006F8],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                 // SCREEN RAM
   AddReadByte(0x500000, 0x500003, YM2151Read68k, NULL);                // YM2151
   AddReadByte(0x700000, 0x7000FF, NULL, RAM+0x01F000);                 // INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x700000, 0x7000FF, NULL, RAM+0x01F000);                 // INPUT
   AddReadWord(0x600000, 0x600001, OKIM6295_status_0_r, NULL);                 // M6295
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x500000, 0x500003, YM2151Write68k, NULL);              // YM2151
   AddWriteByte(0x700000, 0x70003F, snow_bros_2_ioc_wb, NULL);          // INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);               // SCREEN RAM
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x600000, 0x600001, M6295Write68k, NULL);               // M6295
   AddWriteWord(0x700000, 0x70003F, snow_bros_2_ioc_ww, NULL);          // INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

/*-------[Sound Communication]--------*/

static UINT8 sport;

static void SoundWrite68k(UINT32 offset,UINT16 data)
{
   sport=data&0xFF;
}

static UINT16 SoundRead68k(UINT32 offset)
{
   return sport;
}

static void SoundWriteZ80(UINT16 address, UINT8 data)
{
   sport=data&0xFF;
}

static UINT16 SoundReadZ80(UINT16 address)
{
   return sport;
}

/*------------------------------------*/

static void LoadActual(void)
{
   int ta,tb,tc;
   UINT8 *Z80RAM;

   if(!(RAM=AllocateMem(0x100000)))return;
   Z80RAM = RAM+0x20000;
   if(!(GFX=AllocateMem(0x400000)))return;

   if(romset==2){
      if(!load_rom("ppbb01.bin", RAM, 0x80000))return;           // GFX
      tb=0;
      for(ta=0;ta<0x80000;ta++){
         tc=RAM[ta];
         GFX[tb+0]=((tc&0x80)>>7)<<0;
         GFX[tb+1]=((tc&0x40)>>6)<<0;
         GFX[tb+2]=((tc&0x20)>>5)<<0;
         GFX[tb+3]=((tc&0x10)>>4)<<0;
         GFX[tb+4]=((tc&0x08)>>3)<<0;
         GFX[tb+5]=((tc&0x04)>>2)<<0;
         GFX[tb+6]=((tc&0x02)>>1)<<0;
         GFX[tb+7]=((tc&0x01)>>0)<<0;
         tb+=8;
      }
      if(!load_rom("ppbb02.bin", RAM, 0x80000))return;           // GFX
      tb=0;
      for(ta=0;ta<0x80000;ta++){
         tc=RAM[ta];
         GFX[tb+0]|=((tc&0x80)>>7)<<1;
         GFX[tb+1]|=((tc&0x40)>>6)<<1;
         GFX[tb+2]|=((tc&0x20)>>5)<<1;
         GFX[tb+3]|=((tc&0x10)>>4)<<1;
         GFX[tb+4]|=((tc&0x08)>>3)<<1;
         GFX[tb+5]|=((tc&0x04)>>2)<<1;
         GFX[tb+6]|=((tc&0x02)>>1)<<1;
         GFX[tb+7]|=((tc&0x01)>>0)<<1;
         tb+=8;
      }
      if(!load_rom("ppbb03.bin", RAM, 0x80000))return;           // GFX
      tb=0;
      for(ta=0;ta<0x80000;ta++){
         tc=RAM[ta];
         GFX[tb+0]|=((tc&0x80)>>7)<<2;
         GFX[tb+1]|=((tc&0x40)>>6)<<2;
         GFX[tb+2]|=((tc&0x20)>>5)<<2;
         GFX[tb+3]|=((tc&0x10)>>4)<<2;
         GFX[tb+4]|=((tc&0x08)>>3)<<2;
         GFX[tb+5]|=((tc&0x04)>>2)<<2;
         GFX[tb+6]|=((tc&0x02)>>1)<<2;
         GFX[tb+7]|=((tc&0x01)>>0)<<2;
         tb+=8;
      }
      if(!load_rom("ppbb04.bin", RAM, 0x80000))return;           // GFX
      tb=0;
      for(ta=0;ta<0x80000;ta++){
         tc=RAM[ta];
         GFX[tb+0]|=((tc&0x80)>>7)<<3;
         GFX[tb+1]|=((tc&0x40)>>6)<<3;
         GFX[tb+2]|=((tc&0x20)>>5)<<3;
         GFX[tb+3]|=((tc&0x10)>>4)<<3;
         GFX[tb+4]|=((tc&0x08)>>3)<<3;
         GFX[tb+5]|=((tc&0x04)>>2)<<3;
         GFX[tb+6]|=((tc&0x02)>>1)<<3;
         GFX[tb+7]|=((tc&0x01)>>0)<<3;
         tb+=8;
      }
   }
   else{
      if(!load_rom("tp025-4.bin", RAM, 0x100000))return;           // GFX
      tb=0;
      for(ta=0;ta<0x100000;ta+=2){
         tc=RAM[ta];
         GFX[tb+0]=((tc&0x80)>>7)<<0;
         GFX[tb+1]=((tc&0x40)>>6)<<0;
         GFX[tb+2]=((tc&0x20)>>5)<<0;
         GFX[tb+3]=((tc&0x10)>>4)<<0;
         GFX[tb+4]=((tc&0x08)>>3)<<0;
         GFX[tb+5]=((tc&0x04)>>2)<<0;
         GFX[tb+6]=((tc&0x02)>>1)<<0;
         GFX[tb+7]=((tc&0x01)>>0)<<0;
         tc=RAM[ta+1];
         GFX[tb+0]|=((tc&0x80)>>7)<<1;
         GFX[tb+1]|=((tc&0x40)>>6)<<1;
         GFX[tb+2]|=((tc&0x20)>>5)<<1;
         GFX[tb+3]|=((tc&0x10)>>4)<<1;
         GFX[tb+4]|=((tc&0x08)>>3)<<1;
         GFX[tb+5]|=((tc&0x04)>>2)<<1;
         GFX[tb+6]|=((tc&0x02)>>1)<<1;
         GFX[tb+7]|=((tc&0x01)>>0)<<1;
         tb+=8;
      }
      if(!load_rom("tp025-3.bin", RAM, 0x100000))return;           // GFX
      tb=0;
      for(ta=0;ta<0x100000;ta+=2){
         tc=RAM[ta];
         GFX[tb+0]|=((tc&0x80)>>7)<<2;
         GFX[tb+1]|=((tc&0x40)>>6)<<2;
         GFX[tb+2]|=((tc&0x20)>>5)<<2;
         GFX[tb+3]|=((tc&0x10)>>4)<<2;
         GFX[tb+4]|=((tc&0x08)>>3)<<2;
         GFX[tb+5]|=((tc&0x04)>>2)<<2;
         GFX[tb+6]|=((tc&0x02)>>1)<<2;
         GFX[tb+7]|=((tc&0x01)>>0)<<2;
         tc=RAM[ta+1];
         GFX[tb+0]|=((tc&0x80)>>7)<<3;
         GFX[tb+1]|=((tc&0x40)>>6)<<3;
         GFX[tb+2]|=((tc&0x20)>>5)<<3;
         GFX[tb+3]|=((tc&0x10)>>4)<<3;
         GFX[tb+4]|=((tc&0x08)>>3)<<3;
         GFX[tb+5]|=((tc&0x04)>>2)<<3;
         GFX[tb+6]|=((tc&0x02)>>1)<<3;
         GFX[tb+7]|=((tc&0x01)>>0)<<3;
         tb+=8;
      }
   }

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x10000);

   if(ReadLong68k(&ROM[0])==0x0080577F) DecodePipiBibi(ROM);

   Z80ROM[0x0059]=0x00; // NOP
   Z80ROM[0x005A]=0x00; // NOP

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x01B3]=0xD3; // OUTA (AAh)
   Z80ROM[0x01B4]=0xAA; //

   SetStopZ80Mode2(0x01B2);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,                        Z80ROM+0x0000); // Z80 ROM
   AddZ80AReadByte(0x8001, 0x87FF, NULL,                        Z80RAM); // Z80 RAM
   AddZ80AReadByte(0x8000, 0x8000, SoundReadZ80,                NULL);          // SOUND COMM
   AddZ80AReadByte(0xE000, 0xE001, YM3526ReadZ80,               NULL);          // YM3526
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0x8001, 0x87FF, NULL,                       Z80RAM); // Z80 RAM
   AddZ80AWriteByte(0x8000, 0x8000, SoundWriteZ80,              NULL);          // SOUND COMM
   AddZ80AWriteByte(0xE000, 0xE001, YM3526WriteZ80,             NULL);          // YM3526
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   sport=0xFF;

   memset(RAM+0x00000,0x00,0x20000);

   RAMSize=0x20000+0x10000;

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x0FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   if(romset==2){

   // Kill the annoying reset instruction
   // -----------------------------------

   WriteWord68k(&ROM[0x1247A],0x4E71);          // nop

   }
   else{

   // Kill the annoying reset instruction
   // -----------------------------------

   WriteWord68k(&ROM[0x128B8],0x4E71);          // nop

   // VRAM Wait
   // ---------

   WriteWord68k(&ROM[0x0046C],0x4E71);          // nop
   WriteWord68k(&ROM[0x00496],0x4E71);          // nop
   WriteWord68k(&ROM[0x004B2],0x4E71);          // nop
   WriteWord68k(&ROM[0x004D6],0x4E71);          // nop

   // Sound Response
   // --------------

   WriteWord68k(&ROM[0x004F6],0x4E71);          // nop

   }


   if(romset==2){
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadByte(0x120000, 0x120FFF, NULL, RAM+0x014000);                 // ??? RAM
   AddReadByte(0x180000, 0x183FFF, NULL, RAM+0x011000);                 // ??? RAM
   AddReadByte(0x19C000, 0x19C0FF, NULL, RAM+0x00E000);                 // INPUT/DSW
   AddReadByte(0x190003, 0x190003, SoundRead68k, NULL);                 // SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadWord(0x120000, 0x120FFF, NULL, RAM+0x014000);                 // OBJECT RAM
   AddReadWord(0x180000, 0x183FFF, NULL, RAM+0x011000);                 // BG0/1/2 RAM
   AddReadWord(0x19C000, 0x19C0FF, NULL, RAM+0x00E000);                 // INPUT/DSW
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteByte(0x120000, 0x120FFF, NULL, RAM+0x014000);                // ??? RAM
   AddWriteByte(0x180000, 0x183FFF, NULL, RAM+0x011000);                // SCREEN RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteWord(0x120000, 0x120FFF, NULL, RAM+0x014000);                // ??? RAM
   AddWriteWord(0x180000, 0x183FFF, NULL, RAM+0x011000);                // ??? RAM
   AddWriteWord(0x188000, 0x18800F, NULL, RAM+0x019000);                // SCROLL RAM
   AddWriteWord(0x190010, 0x190011, SoundWrite68k, NULL);               // SOUND COMM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...

   }
   else{
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadByte(0x140000, 0x14000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x180000, 0x18006F, NULL, RAM+0x00E000);                 // INPUT/DSW
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadWord(0x140000, 0x14000F, tp2vcu_0_rw, NULL);                 // GCU RAM (SCREEN)
   AddReadWord(0x180000, 0x18006F, NULL, RAM+0x00E000);                 // INPUT/DSW
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteByte(0x180000, 0x18007F, whoopee_ioc_wb, NULL);              // INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteWord(0x140000, 0x14000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x180070, 0x180071, SoundWrite68k, NULL);               // SOUND COMM
   AddWriteWord(0x180000, 0x18007F, whoopee_ioc_ww, NULL);              // INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...

   }

}

static void load_tekipaki(void)
{
   romset=7;

   if(!(RAM=AllocateMem(0x80000)))return;
   if(!(GFX=AllocateMem(0x200000)))return;

   load_tp2_gfx("tp020-4.bin","tp020-3.bin",0x80000,RAM,GFX);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x08000);

   memset(RAM+0x00000,0x00,0x20000);

   RAMSize=0x20000+0x10000;

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x07FFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // Fix Checksum

   WriteWord68k(&ROM[0x003BA],0x4E71);          // nop

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x0030C],0x4E71);          // nop

   // 68000 Speed hack

   WriteLong68k(&ROM[0x01C3C],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x01C40],0x00AA0000);      //

   // Sound Check

   WriteWord68k(&ROM[0x0042C],0x600C);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x20000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x01FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x01FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadByte(0x140000, 0x14000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x180000, 0x18006F, NULL, RAM+0x00E000);                 // INPUT/DSW
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x01FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadWord(0x140000, 0x14000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x180000, 0x18006F, NULL, RAM+0x00E000);                 // INPUT/DSW
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteByte(0x180000, 0x18007F, whoopee_ioc_wb, NULL);              // INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteWord(0x140000, 0x14000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x180070, 0x180071, SoundWrite68k, NULL);               // SOUND COMM
   AddWriteWord(0x180000, 0x18007F, whoopee_ioc_ww, NULL);              // INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...

}

static void load_ghox(void)
{
   romset=8;

   if(!(RAM=AllocateMem(0x80000)))return;
   if(!(GFX=AllocateMem(0x200000)))return;

   load_tp2_gfx("tp021-03.u36","tp021-04.u37",0x80000,RAM,GFX);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x08000);

   memset(RAM+0x00000,0x00,0x20000);

   RAMSize=0x20000+0x10000;

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x07FFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // Fix Checksum

   WriteWord68k(&ROM[0x0FABA],0x7400);          // nop

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x0F7EA],0x4E71);          // nop

   // 68000 Speed hack

   WriteLong68k(&ROM[0x01C30],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x01C34],0x00AA0000);      //
   WriteWord68k(&ROM[0x01C38],0x4E71);

   // protection (02e2e-02e7b) - D1

   WriteWord68k(&ROM[0x02E70],0x4E71);

   // protection (06764-067c3) - D4

   WriteLong68k(&ROM[0x067A8],0x4E714E71);
   WriteWord68k(&ROM[0x067AC],0x4E71);

   // protection (0da62-?????) - D0

   WriteWord68k(&ROM[0x0DAA6],0x4E71);

   // protection (0f7f6-0f82d) - init / sound check

   WriteLong68k(&ROM[0x0F828],0x4E714E71);
   WriteWord68k(&ROM[0x0F82C],0x4E71);

   // protection (0fb40-0fba1) - D3

   WriteLong68k(&ROM[0x0FB84],0x4E714E71);
   WriteWord68k(&ROM[0x0FB88],0x4E71);

   // protection (103dc-1043d) - D2

   WriteLong68k(&ROM[0x10420],0x4E714E71);
   WriteWord68k(&ROM[0x10424],0x4E71);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadByte(0x140000, 0x14000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x180000, 0x18FFFF, ghox_ioc_rb, NULL);                  // SUB CPU
   AddReadByte(0x100000, 0x100001, ghox_paddle_rb, NULL);               // PADDLE#1
   AddReadByte(0x040000, 0x040001, ghox_paddle_rb, NULL);               // PADDLE#2
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadWord(0x140000, 0x14000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x180000, 0x18FFFF, ghox_ioc_rw, NULL);                  // SUB CPU
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteByte(0x180000, 0x18FFFF, ghox_ioc_wb, NULL);                 // SUB CPU
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x087FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteWord(0x140000, 0x14000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x180000, 0x18FFFF, ghox_ioc_ww, NULL);                 // SUB CPU
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...

   GameMouse=1;
}

static void load_vfive(void)
{
   romset=12;

   if(!(RAM=AllocateMem(0x100000)))return;
   if(!(GFX=AllocateMem(0x400000)))return;

   load_tp2_gfx("tp027_02.bin","tp027_03.bin",0x100000,RAM,GFX);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x10000);

   memset(RAM+0x00000,0x00,0x38000);

   RAM_TURBO = RAM+0x30000;

   RAMSize=0x20000+0x10000+0x8000;

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x0FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   if(is_current_game("grindstm")){

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x207F2],0x4E71);          // nop

   // Protection

   WriteWord68k(&ROM[0x20B64],0x4E71);          // nop

   // 68000 Speed hack

   WriteLong68k(&ROM[0x055D6],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x055DA],0x00AA0000);      //
   WriteWord68k(&ROM[0x055DE],0x4E71);

   }
   else{

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x2088C],0x4E71);          // nop

   // Protection

   WriteWord68k(&ROM[0x20BF4],0x4E71);          // nop

   // 68000 Speed hack

   WriteLong68k(&ROM[0x05770],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x05774],0x00AA0000);      //
   WriteWord68k(&ROM[0x05778],0x4E71);

   }

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x107FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x400000, 0x400FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x210000, 0x21FFFF, TS_001_Turbo_RB, NULL);              // SUB CPU
   AddReadByte(0x200000, 0x20003F, v_five_ioc_rb, NULL);                // INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x107FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x210000, 0x21FFFF, TS_001_Turbo_RW, NULL);              // SUB CPU
   AddReadWord(0x200000, 0x20003F, v_five_ioc_rw, NULL);                // INPUT
   AddReadWord(0x700000, 0x700001, TimerRead, NULL);                    // TIMER
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x107FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteByte(0x210000, 0x21FFFF, TS_001_Turbo_WB, NULL);             // SUB CPU
   AddWriteByte(0x200000, 0x20003F, fix_eight_ioc_wb, NULL);            // INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x107FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x210000, 0x21FFFF, TS_001_Turbo_WW, NULL);             // SUB CPU
   AddWriteWord(0x200000, 0x20003F, fix_eight_ioc_ww, NULL);            // INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void oki_bankswitch_w(UINT32 offset, UINT8 data)
{
  if ((data & 0x80) == 0)
    OKIM6295_set_bank_base(0, ALL_VOICES, (data & 1) * 0x40000);
}

static void load_kbash(void)
{
   UINT8 *TMP;

   romset=4;

   if(!(GFX=AllocateMem(0x1000000)))return;
   if(!(TMP=AllocateMem(0x400000)))return;

   if (is_current_game("kbash2")) {
     load_tp2_gfx("mecat-34","mecat-12",0x400000,TMP,GFX);
   } else {
     load_tp2_gfx("kbash03.bin","kbash04.bin",0x200000,TMP,GFX);
     load_tp2_gfx("kbash05.bin","kbash06.bin",0x200000,TMP,&GFX[0x800000]);
   }

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x40000);

   if(!(RAM=AllocateMem(0x20000)))return;

   memset(RAM+0x00000,0x00,0x20000);

   RAMSize=0x20000;

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x3FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   WriteWord68k(&ROM[0x043A4],0x4E71);          // nop (already in kbash2)

   WriteLong68k(&ROM[0x00400],0x4E714E71);      // nop (same in kbash2)
   WriteLong68k(&ROM[0x00414],0x4E714E71);      // nop (applied in kbash2)
   WriteLong68k(&ROM[0x00422],0x4E714E71);      // nop (same in kbash2)
   WriteLong68k(&ROM[0x00430],0x4E714E71);      // nop (same in kbash2)
   WriteLong68k(&ROM[0x0043E],0x4E714E71);      // nop "              "
   WriteLong68k(&ROM[0x00450],0x4E714E71);      // nop "              "
   WriteLong68k(&ROM[0x00468],0x4E714E71);      // nop applied in kbash2
   WriteLong68k(&ROM[0x00486],0x4E714E71);      // nop "              "
   WriteLong68k(&ROM[0x0051C],0x4E714E71);      // nop same in kbash2

   // VRAM Wait
   // ---------

   WriteWord68k(&ROM[0x0052E],0x4E71);          // nop (ram check) same in kbash2
   WriteWord68k(&ROM[0x00550],0x4E71);          // nop (ram check)

   // 68000 Speed hack
   // ----------------

   WriteLong68k(&ROM[0x05270],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x05274],0x00AA0000);      //

   // Kill the annoying reset instruction
   // -----------------------------------

   WriteWord68k(&ROM[0x003A6],0x4E71);          // nop
   WriteWord68k(&ROM[0x003A8],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                 // SCREEN RAM
   //AddReadByte(0x200000, 0x200003, YM2151Read68k, NULL);              // YM2151
   AddReadByte(0x200004, 0x20000F, NULL, RAM+0x01F004);                 // INPUT
   if (is_current_game("kbash2")) {
     AddReadBW(0x200010, 0x20001b, NULL, RAM+0x01F010); // inputs
     AddReadBW(0x200020, 0x200021, OKIM6295_status_1_r, NULL);
     AddReadBW(0x200024, 0x200025, OKIM6295_status_0_r, NULL);
     AddWriteBW(0x200020, 0x200021, OKIM6295_data_1_w, NULL);
     AddWriteBW(0x200024, 0x200025, OKIM6295_data_0_w, NULL);
     AddWriteBW(0x200028, 0x200029, oki_bankswitch_w, NULL);
   } else {
     AddReadBW(0x208010, 0x20801F, NULL, RAM+0x01F010);                 // INPUT
   }
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_0_rw, NULL);                 // SCREEN RAM
   AddReadWord(0x700000, 0x700001, NULL, RAM+0x01F020);                 // TIMER/VSYNC?
   AddReadWord(0x200000, 0x200001, OKIM6295_status_0_r, NULL);               // M6295
   AddReadWord(0x200004, 0x20000F, NULL, RAM+0x01F004);                 // INPUT
   AddReadWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                 // COLOUR RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   //AddWriteByte(0x200000, 0x200003, YM2151Write68k, NULL);            // YM2151
   if (is_current_game("kbash")) {
     AddWriteByte(0x200000, 0x200003, kbash_okisnd_w, NULL);               // M6295
     AddWriteByte(0x208000, 0x20803F, knuckle_bash_ioc_wb, NULL);         // INPUT
   }
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);               // SCREEN RAM
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x208000, 0x20803F, knuckle_bash_ioc_ww, NULL);         // INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddReadByte(-1, -1, NULL, NULL);
   AddReadWord(-1, -1,NULL, NULL);
   AddWriteByte(-1, -1, NULL, NULL);
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void load_pipibibi(void)
{
   romset=2;
   LoadActual();
}

static void load_whoopee(void)
{
   romset=3;
   LoadActual();
}

static void load_fixeight(void)
{
   UINT8 *TMP;
   int ta,tb;

   if(is_current_game("fixeight"))
     romset=5;
   else
     romset = 15;

   if(!(GFX=AllocateMem(0x800000)))return;
   if(!(TMP=AllocateMem(0x200000)))return;

   load_tp2_gfx("tp-026-3","tp-026-4",0x200000,TMP,GFX);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x20000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(RAMSize)))return;

   if(is_current_game("fixeight"))
   {
     // ByteSwap(ROM,0x80000);
   }
   else
   {
     ByteSwap(ROM + 0x80000, 0x80000);
   }

   /*-----[Sound Setup]-----*/


   if(!is_current_game("fixeight"))
   {
     if(!(PCMROM = AllocateMem(0x40000 + 0x50000))) return;
     if(!load_rom("1.bin", RAM, 0x80000)) return;
     // base rom
     memcpy(PCMROM, RAM, 0x30000);
     // bank rom
     memcpy(PCMROM + 0x40000, RAM + 0x30000, 0x50000);
     ADPCMSetBuffers(((struct ADPCMinterface*)&fix_eight_bootleg_m6295_interface),PCMROM,0x40000);
   }

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x54000);

   RAM_TURBO = RAM+0x34000;
   RAM_FG0   = RAM+0x24000;
   GFX_FG0   = RAM+0x54000;

   if(is_current_game("fixeight"))
   {
     // copy fg0 tiles from the 68000 rom
     for(ta = 0x68000, tb = 0; ta < 0x70000; ta ++)
     {
       GFX_FG0[tb++]=(ROM[ta]&0xF0)>>4;
       GFX_FG0[tb++]=(ROM[ta]&0x0F)>>0;
     }
   }
   else
   {
     // load fg0 tiles from the bootleg rom
     if(!load_rom("4.bin", RAM, 0x8000)) return;
     // unpack fg0 tiles
     for(ta = 0, tb = 0; ta < 0x8000; ta ++)
     {
       GFX_FG0[tb ++] = (RAM[ta] & 0xF0) >> 4;
       GFX_FG0[tb ++] = (RAM[ta] & 0x0F) >> 0;
       RAM[ta] = 0;
     }
   }

   GFX_FG0_SOLID = make_solid_mask_8x8(GFX_FG0, 0x400);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x1FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   if(is_current_game("fixeight"))
   {
     // VRAM Wait

     WriteWord68k(&ROM[0x00438],0x4E71);          // nop

     // Sound protection and shit

     WriteWord68k(&ROM[0x043F2],0x4E71);          // nop
     WriteWord68k(&ROM[0x04400],0x4E71);          // nop

     // Background data decoding

     WriteWord68k(&ROM[0x0457C],0x4E75);
     WriteWord68k(&ROM[0x0459E],0x4E75);

     WriteWord68k(&ROM[0x044BA],0x4E75);
     WriteWord68k(&ROM[0x0455C],0x4E75);

     // More

     WriteWord68k(&ROM[0x04414],0x4E75);
     WriteWord68k(&ROM[0x0443C],0x4E75);
     WriteWord68k(&ROM[0x04464],0x4E75);

     WriteWord68k(&ROM[0x0448C],0x4E75);
     WriteWord68k(&ROM[0x04506],0x6010);
     WriteWord68k(&ROM[0x04600],0x6010);
     WriteWord68k(&ROM[0x0467E],0x4E75);

     // Ram Checks

     WriteLong68k(&ROM[0x05054],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x050B8],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x050CA],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x050D8],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x050F2],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x05106],0x4E714E71);      // nop
     WriteWord68k(&ROM[0x05118],0x4E71);          // nop
     WriteLong68k(&ROM[0x05126],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x05136],0x4E714E71);      // nop

     WriteLong68k(&ROM[0x051AE],0x4E714E71);      // nop
     WriteLong68k(&ROM[0x051C6],0x4E714E71);      // nop

     ROM[0x051D4]=0x60;

     WriteLong68k(&ROM[0x05214],0x4E714E71);      // nop

     // Kill the annoying reset instruction

     WriteWord68k(&ROM[0x0504C],0x4E71);          // nop
   }
   else
   {
     WriteWord68k(&ROM[0x009AA],0x4E71);          // nop

     // Kill the annoying reset instruction

     WriteWord68k(&ROM[0x05066],0x4E71);          // nop

     // scroll hack

     WriteLong68k(&ROM[0x00420],0x0010035C);      //

     WriteLong68k(&ROM[0x00442],0x13FC0000);      // move.b #$00,$AA0000
     WriteLong68k(&ROM[0x00446],0x00AA0000);      //

   }

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x54000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                 // GCU RAM (SCREEN)
   AddReadByte(0x200018, 0x200019, OKIM6295_status_0_r, NULL);               // M6295
   AddReadByte(0x200000, 0x20003F, NULL, RAM+0x01F000);                 // INPUT
	if(!is_current_game("fixeight")) {
		AddReadByte(0x700000, 0x700001, TimerRead, NULL);               // TIMER
	}
   AddReadByte(0x280000, 0x28FFFF, TS_001_Turbo_RB, NULL);              // TS-001-TURBO
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                 // COLOUR RAM
   AddReadWord(0x200018, 0x200019, OKIM6295_status_0_r, NULL);               // M6295
   AddReadWord(0x200000, 0x20003F, NULL, RAM+0x01F000);                 // INPUT
   AddReadWord(0x600000, 0x60FFFF, NULL, RAM+0x044000);                 // CG RAM (FG0 GFX RAM)
	if(is_current_game("fixeight")) {
   AddReadWord(0x800000, 0x800001, TimerRead, NULL);                    // TIMER
	} else
	{
		AddReadWord(0x700000, 0x700001, TimerRead, NULL);               // TIMER
		AddReadWord(0x800000, 0x87FFFF, NULL, ROM+0x080000);            // UNPROTECTED MAPS :)
	}
   AddReadWord(0x280000, 0x28FFFF, TS_001_Turbo_RW, NULL);              // TS-001-TURBO
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x200014, 0x200015, fixeighb_oki_bankswitch_w, NULL);   // M6295 BANKING
   if (is_current_game("fixeight")) {
     AddWriteByte(0x28f000, 0x28f001, fixeight_okisnd_w, NULL);               // M6295
   } else {
     AddWriteByte(0x200018, 0x200019, M6295Write68k, NULL);               // M6295
   }
   AddWriteByte(0x200000, 0x20003F, fix_eight_ioc_wb, NULL);            // INPUT
   AddWriteByte(0x280000, 0x28FFFF, TS_001_Turbo_WB, NULL);             // TS-001-TURBO
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);               // GCU RAM (SCREEN)
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x500000, 0x503FFF, NULL, RAM_FG0);                     // TEXT RAM (FG0 RAM)
   AddWriteWord(0x600000, 0x60FFFF, NULL, RAM+0x044000);                // CG RAM (FG0 GFX RAM)
   AddWriteWord(0x200018, 0x200019, M6295Write68k, NULL);             // M6295
   AddWriteWord(0x200000, 0x20003F, fix_eight_ioc_ww, NULL);            // INPUT
   AddWriteWord(0x280000, 0x28FFFF, TS_001_Turbo_WW, NULL);             // TS-001-TURBO
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void load_dogyuun(void)
{
   UINT8 *TMP;
   int ta,tb,tc;
   romset=6;

   if(!(GFX=AllocateMem(0xC00000)))return;
   if(!(TMP=AllocateMem(0x200000)))return;

   tb=0;
   if(!load_rom("tp022_5.r16", TMP, 0x200000))return;                // GFX
   for(ta=0;ta<0x200000;ta+=2){
      tc=TMP[ta+1];
      GFX[tb+0] = (((tc&0x80)>>7)<<0);
      GFX[tb+1] = (((tc&0x40)>>6)<<0);
      GFX[tb+2] = (((tc&0x20)>>5)<<0);
      GFX[tb+3] = (((tc&0x10)>>4)<<0);
      GFX[tb+4] = (((tc&0x08)>>3)<<0);
      GFX[tb+5] = (((tc&0x04)>>2)<<0);
      GFX[tb+6] = (((tc&0x02)>>1)<<0);
      GFX[tb+7] = (((tc&0x01)>>0)<<0);
      tc=TMP[ta];
      GFX[tb+0] |= (((tc&0x80)>>7)<<1);
      GFX[tb+1] |= (((tc&0x40)>>6)<<1);
      GFX[tb+2] |= (((tc&0x20)>>5)<<1);
      GFX[tb+3] |= (((tc&0x10)>>4)<<1);
      GFX[tb+4] |= (((tc&0x08)>>3)<<1);
      GFX[tb+5] |= (((tc&0x04)>>2)<<1);
      GFX[tb+6] |= (((tc&0x02)>>1)<<1);
      GFX[tb+7] |= (((tc&0x01)>>0)<<1);
      tb+=8;
   }
   if(!load_rom("tp022_3.r16", TMP, 0x100000))return;                // GFX
   for(ta=0;ta<0x100000;ta+=2){
      tc=TMP[ta+1];
      GFX[tb+0] = (((tc&0x80)>>7)<<0);
      GFX[tb+1] = (((tc&0x40)>>6)<<0);
      GFX[tb+2] = (((tc&0x20)>>5)<<0);
      GFX[tb+3] = (((tc&0x10)>>4)<<0);
      GFX[tb+4] = (((tc&0x08)>>3)<<0);
      GFX[tb+5] = (((tc&0x04)>>2)<<0);
      GFX[tb+6] = (((tc&0x02)>>1)<<0);
      GFX[tb+7] = (((tc&0x01)>>0)<<0);
      tc=TMP[ta];
      GFX[tb+0] |= (((tc&0x80)>>7)<<1);
      GFX[tb+1] |= (((tc&0x40)>>6)<<1);
      GFX[tb+2] |= (((tc&0x20)>>5)<<1);
      GFX[tb+3] |= (((tc&0x10)>>4)<<1);
      GFX[tb+4] |= (((tc&0x08)>>3)<<1);
      GFX[tb+5] |= (((tc&0x04)>>2)<<1);
      GFX[tb+6] |= (((tc&0x02)>>1)<<1);
      GFX[tb+7] |= (((tc&0x01)>>0)<<1);
      tb+=8;
   }

   tb=0;
   if(!load_rom("tp022_6.r16", TMP, 0x200000))return;                // GFX
   for(ta=0;ta<0x200000;ta+=2){
      tc=TMP[ta+1];
      GFX[tb+0] |= (((tc&0x80)>>7)<<2);
      GFX[tb+1] |= (((tc&0x40)>>6)<<2);
      GFX[tb+2] |= (((tc&0x20)>>5)<<2);
      GFX[tb+3] |= (((tc&0x10)>>4)<<2);
      GFX[tb+4] |= (((tc&0x08)>>3)<<2);
      GFX[tb+5] |= (((tc&0x04)>>2)<<2);
      GFX[tb+6] |= (((tc&0x02)>>1)<<2);
      GFX[tb+7] |= (((tc&0x01)>>0)<<2);
      tc=TMP[ta];
      GFX[tb+0] |= (((tc&0x80)>>7)<<3);
      GFX[tb+1] |= (((tc&0x40)>>6)<<3);
      GFX[tb+2] |= (((tc&0x20)>>5)<<3);
      GFX[tb+3] |= (((tc&0x10)>>4)<<3);
      GFX[tb+4] |= (((tc&0x08)>>3)<<3);
      GFX[tb+5] |= (((tc&0x04)>>2)<<3);
      GFX[tb+6] |= (((tc&0x02)>>1)<<3);
      GFX[tb+7] |= (((tc&0x01)>>0)<<3);
      tb+=8;
   }
   if(!load_rom("tp022_4.r16", TMP, 0x100000))return;                // GFX
   for(ta=0;ta<0x100000;ta+=2){
      tc=TMP[ta+1];
      GFX[tb+0] |= (((tc&0x80)>>7)<<2);
      GFX[tb+1] |= (((tc&0x40)>>6)<<2);
      GFX[tb+2] |= (((tc&0x20)>>5)<<2);
      GFX[tb+3] |= (((tc&0x10)>>4)<<2);
      GFX[tb+4] |= (((tc&0x08)>>3)<<2);
      GFX[tb+5] |= (((tc&0x04)>>2)<<2);
      GFX[tb+6] |= (((tc&0x02)>>1)<<2);
      GFX[tb+7] |= (((tc&0x01)>>0)<<2);
      tc=TMP[ta];
      GFX[tb+0] |= (((tc&0x80)>>7)<<3);
      GFX[tb+1] |= (((tc&0x40)>>6)<<3);
      GFX[tb+2] |= (((tc&0x20)>>5)<<3);
      GFX[tb+3] |= (((tc&0x10)>>4)<<3);
      GFX[tb+4] |= (((tc&0x08)>>3)<<3);
      GFX[tb+5] |= (((tc&0x04)>>2)<<3);
      GFX[tb+6] |= (((tc&0x02)>>1)<<3);
      GFX[tb+7] |= (((tc&0x01)>>0)<<3);
      tb+=8;
   }
   // We can't use the generic function, or we would need to byte swap the
   // result...
   //load_tp2_gfx("tp022_5.r16","tp022_6.r16",0x200000,TMP,GFX);
   //load_tp2_gfx("tp022_3.r16","tp022_4.r16",0x100000,TMP,&GFX[0x800000]);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x30000);

   RAMSize=0x34000+0x10000+0x10000+0x10000;

   if(!(RAM=AllocateMem(RAMSize)))return;

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x54000);

   RAM_TURBO = RAM+0x34000;
   RAM_FG0   = RAM+0x24000;
   GFX_FG0   = RAM+0x54000;

   tp2vcu[0].VRAM     = RAM+0x11000+0x0000;
   tp2vcu[0].SCROLL   = RAM+0x19000+0x0000;
   tp2vcu[0].GFX_BG   = GFX+0x000000;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID+0x00000;
   tp2vcu[0].tile_max = 0x1FFFF;
   init_tp2vcu(0);

   tp2vcu[1].VRAM     = RAM+0x11000+0x4000;
   tp2vcu[1].SCROLL   = RAM+0x19000+0x0100;
   tp2vcu[1].GFX_BG   = GFX+0x800000;
   tp2vcu[1].MASK_BG  = GFX_BG0_SOLID+0x20000;
   tp2vcu[1].tile_max = 0x0FFFF;
   init_tp2vcu(1);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // VRAM Wait

   WriteWord68k(&ROM[0x002B6],0x4E71);          // nop
   WriteWord68k(&ROM[0x002CC],0x4E71);          // nop

   // Sound protection and shit

   WriteWord68k(&ROM[0x3039C],0x4E71);          // nop
   WriteWord68k(&ROM[0x303AA],0x4E71);          // nop
/*
   // More

   WriteWord68k(&ROM[0x04414],0x4E75);
   WriteWord68k(&ROM[0x0443C],0x4E75);
   WriteWord68k(&ROM[0x04464],0x4E75);

   WriteWord68k(&ROM[0x0448C],0x4E75);
   WriteWord68k(&ROM[0x04506],0x6010);
   WriteWord68k(&ROM[0x04600],0x6010);
   WriteWord68k(&ROM[0x0467E],0x4E75);

   // Ram Checks

   WriteLong68k(&ROM[0x05054],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x050B8],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x050CA],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x050D8],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x050F2],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x05106],0x4E714E71);      // nop
   WriteWord68k(&ROM[0x05118],0x4E71);          // nop
   WriteLong68k(&ROM[0x05126],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x05136],0x4E714E71);      // nop

   WriteLong68k(&ROM[0x051AE],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x051C6],0x4E714E71);      // nop

   ROM[0x051D4]=0x60;
*/
   WriteLong68k(&ROM[0x30734],0x4E714E71);      // nop

   // Fix Checksum

   WriteLong68k(&ROM[0x3076A],0x4E714E71);      // nop

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x30628],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x54000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_1_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x500000, 0x50000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x200000, 0x20003F, NULL, RAM+0x01F000);                 // INPUT
   //AddReadByte(0x700010, 0x700011, OKIM6295_status_0_r, NULL);               // M6295
   //AddReadByte(0x700014, 0x700017, YM2151Read68k, NULL);              // YM2151
   AddReadByte(0x210000, 0x21FFFF, TS_001_Turbo_RB, NULL);              // TS-001-TURBO
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_1_rw, NULL);                 // GCU RAM (SCREEN)
   AddReadWord(0x500000, 0x50000F, tp2vcu_0_rw, NULL);                 // GCU RAM (SCREEN)
   AddReadWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddReadWord(0x200000, 0x20003F, NULL, RAM+0x01F000);                 // INPUT
   AddReadWord(0x700010, 0x700011, OKIM6295_status_0_r, NULL);               // M6295
   AddReadWord(0x700014, 0x700017, YM2151Read68k, NULL);              // YM2151
   AddReadWord(0x700000, 0x700001, TimerRead, NULL);                    // TIMER
   AddReadWord(0x210000, 0x21FFFF, TS_001_Turbo_RW, NULL);              // TS-001-TURBO
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   //AddWriteByte(0x200008, 0x200009, M6295Write68k, NULL);             // M6295
//   AddWriteByte(0x700014, 0x700017, YM2151Write68k, NULL);            // YM2151
   AddWriteByte(0x200000, 0x20003F, dogyuun_ioc_wb, NULL);              // INPUT
   AddWriteByte(0x210000, 0x21FFFF, TS_001_Turbo_WB, NULL);             // TS-001-TURBO
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_1_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x500000, 0x50000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   //AddWriteWord(0x200008, 0x200009, M6295Write68k, NULL);             // M6295
   //   AddWriteWord(0x700010, 0x700011, M6295Write68k, NULL);             // M6295
//   AddWriteWord(0x700014, 0x700017, YM2151Write68k, NULL);            // YM2151
   AddWriteWord(0x200000, 0x20003F, dogyuun_ioc_ww, NULL);              // INPUT
   AddWriteWord(0x210000, 0x21FFFF, TS_001_Turbo_WW, NULL);             // TS-001-TURBO
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void load_batsugun(void)
{
   UINT8 *TMP;

   romset=13;
   // Batsugun uses 1 unmapped bit in these 3 inputs, if it's not set to 0
   // the copyright screen disappears instantly and if you start a game you
   // finish stage 4 before even starting to play !!!
   memset(input_buffer,0,3);

   if(!(GFX=AllocateMem(0x0C00000)))return;
   if(!(TMP=AllocateMem(0x0100000)))return;

   load_tp2_gfx("tp030_5.bin","tp030_6.bin",0x100000,TMP,GFX);
   load_tp2_gfx("tp030_3l.bin","tp030_4l.bin",0x100000,TMP,&GFX[0x400000]);
   load_tp2_gfx("tp030_3h.bin","tp030_4h.bin",0x100000,TMP,&GFX[0x800000]);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x30000);

   RAMSize=0x34000+0x10000+0x10000+0x10000;

   if(!(RAM=AllocateMem(RAMSize)))return;

   /*-----[Sound Setup]-----*/

   if(!(PCMROM = AllocateMem(0x40000))) return;
   if(!load_rom("tp030_2.bin", PCMROM, 0x40000)) return;     // ADPCM ROM <1 bank>
   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),PCMROM,0x40000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x54000);

   RAM_TURBO = RAM+0x34000;
   RAM_FG0   = RAM+0x24000;
   GFX_FG0   = RAM+0x54000;

   tp2vcu[0].VRAM     = RAM+0x11000+0x0000;
   tp2vcu[0].SCROLL   = RAM+0x19000+0x0000;
   tp2vcu[0].GFX_BG   = GFX+0x000000;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID+0x00000;
   tp2vcu[0].tile_max = 0x0FFFF;
   init_tp2vcu(0);

   tp2vcu[1].VRAM     = RAM+0x11000+0x4000;
   tp2vcu[1].SCROLL   = RAM+0x19000+0x0100;
   tp2vcu[1].GFX_BG   = GFX+0x400000;
   tp2vcu[1].MASK_BG  = GFX_BG0_SOLID+0x10000;
   tp2vcu[1].tile_max = 0x1FFFF;
   init_tp2vcu(1);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // 68000 Speed hack

   WriteLong68k(&ROM[0x00670],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00674],0x00AA0000);      //
   WriteWord68k(&ROM[0x00678],0x4E71);          // nop

   // Sound protection and shit

   WriteWord68k(&ROM[0x3BB70],0x4E71);          // nop
   WriteWord68k(&ROM[0x3BBA8],0x4E71);          // nop

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x3B888],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x54000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_1_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x500000, 0x50000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x200000, 0x20003F, v_five_ioc_rb, NULL);                // INPUT
   AddReadByte(0x210000, 0x21FFFF, TS_001_Turbo_RB, NULL);              // TS-001-TURBO
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_1_rw, NULL);                 // GCU RAM (SCREEN)
   AddReadWord(0x500000, 0x50000F, tp2vcu_0_rw, NULL);                 // GCU RAM (SCREEN)
   AddReadWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddReadWord(0x200000, 0x20003F, v_five_ioc_rw, NULL);                // INPUT
   AddReadWord(0x700000, 0x700001, TimerRead, NULL);                    // TIMER
   AddReadWord(0x210000, 0x21FFFF, TS_001_Turbo_RW, NULL);              // TS-001-TURBO
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x200000, 0x20003F, dogyuun_ioc_wb, NULL);              // INPUT
   AddWriteByte(0x210000, 0x21FFFF, TS_001_Turbo_WB, NULL);             // TS-001-TURBO
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_1_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x500000, 0x50000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x200000, 0x20003F, dogyuun_ioc_ww, NULL);              // INPUT
   AddWriteWord(0x210000, 0x21FFFF, TS_001_Turbo_WW, NULL);             // TS-001-TURBO
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static UINT8 shippu_z80_rb(UINT16 offset)
{
   switch(offset){
/*        case 0xE000: */
/*           return YM2151_status_port_0_r(offset); */
/*        break; */
      case 0xE001:
         return YM2151_status_port_0_r(offset);
      break;
      case 0xE004:
         return m6295_z80_rb(offset);
      break;
      case 0xE010:
         return input_buffer[1];
      break;
      case 0xE012:
         return input_buffer[2];
      break;
      case 0xE014:
         return input_buffer[0];
      break;
      case 0xE016:
         return get_dsw(0);
      break;
      case 0xE018:
         return get_dsw(1);
      break;
      case 0xE01A:
         return get_dsw(2) & 0x0F;
      break;
      default:
            print_debug("shippu_ioc_rb(%04x)\n", offset);
         return 0x00;
      break;
   }
}

static void shippu_z80_wb(UINT16 offset, UINT8 data)
{
   switch(offset){
      case 0xE000:
         ym2151_z80_wb(offset, data);
      break;
      case 0xE001:
         ym2151_z80_wb(offset, data);
      break;
      case 0xE004:
         m6295_z80_wb(offset, data);
      break;
      case 0xE00E:
         set_toaplan2_leds(data);
      break;
      default:
            print_debug("shippu_ioc_wb(%04x,%02x)\n", offset, data);
      break;
   }
}

static UINT8 turbo_68k_rb(UINT32 offset)
{
   offset >>= 1;
   offset  &= 0x3FFF;

   if(offset<0x2000)
      return Z80RAM[offset];
   else
      return shippu_z80_rb(offset+0xc000);
}

static UINT16 turbo_68k_rw(UINT32 offset)
{
   return turbo_68k_rb(offset);
}

static void turbo_68k_wb(UINT32 offset, UINT8 data)
{
   offset >>= 1;
   offset  &= 0x3FFF;

   if(offset<0x2000)
      Z80RAM[offset] = data;
   else
      shippu_z80_wb(offset+0xc000, data);
}

static void turbo_68k_ww(UINT32 offset, UINT16 data)
{
   turbo_68k_wb(offset, data);
}

static void load_shippumd(void)
{
   UINT8 *TMP;
   int ta,tb;

   romset=9;

   if(!(GFX=AllocateMem(0x800000)))return;
   if(!(TMP=AllocateMem(0x200000)))return;

   load_tp2_gfx("ma02rom3.bin","ma02rom4.bin",0x200000,TMP,GFX);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x20000);

   RAMSize=0x34000+0x10000+0x10000;

   if(!(RAM=AllocateMem(0x080000)))return;

   Z80RAM=RAM+0x34000+0x10000;

   Z80ROM[0x0082]=0x00; // NOP
   Z80ROM[0x0083]=0x00; // NOP

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x00C1]=0xD3; // OUTA (AAh)
   Z80ROM[0x00C2]=0xAA; //

   SetStopZ80Mode2(0x00C3);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,                        Z80ROM+0x0000); // Z80 ROM
   AddZ80AReadByte(0xC000, 0xDFFF, NULL,                        Z80RAM); // COMM RAM
   AddZ80AReadByte(0xE000, 0xFFFF, shippu_z80_rb,               NULL);          // IOC
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xC000, 0xDFFF, NULL,                       Z80RAM); // COMM RAM
   AddZ80AWriteByte(0xE000, 0xFFFF, shippu_z80_wb,              NULL);          // IOC
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   /*-----------------------*/

   RAM_FG0 = RAM+0x20000;
   GFX_FG0 = RAM+0x34000;

   if(!load_rom("ma02rom5.bin", RAM, 0x08000))return;
   tb=0;
   for(ta=0x00000;ta<0x08000;ta++){
      GFX_FG0[tb++]=(RAM[ta]&0xF0)>>4;
      GFX_FG0[tb++]=(RAM[ta]&0x0F)>>0;
   }

   memset(RAM+0x00000,0x00,0x34000);

   GFX_FG0_SOLID = make_solid_mask_8x8(GFX_FG0, 0x400);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x1FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // Skip Hardware Check

   WriteWord68k(&ROM[0x02264],0x4E71);          // nop

   // 68000 Speed hack

   WriteLong68k(&ROM[0x05822],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x05826],0x00AA0000);      //

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x02210],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x34000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x218000, 0x21FFFF, turbo_68k_rb, NULL);                 // turbo comm ram
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x21C03C, 0x21C03D, TimerRead, NULL);                    // TIMER
   AddReadWord(0x218000, 0x21FFFF, turbo_68k_rw, NULL);                 // turbo comm ram
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x218000, 0x21FFFF, turbo_68k_wb, NULL);                // turbo comm ram
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x500000, 0x503FFF, NULL, RAM+0x020000);                // TEXT RAM (FG0 RAM)
   AddWriteWord(0x218000, 0x21FFFF, turbo_68k_ww, NULL);                // turbo comm ram
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void load_mahoudai(void)
{
   UINT8 *TMP;

   romset=10;

   if(!(GFX=AllocateMem(0x400000)))return;
   if(!(TMP=AllocateMem(0x100000)))return;

   load_tp2_gfx("ra_ma_01.03","ra_ma_01.04",0x100000,TMP,GFX);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x10000);

   RAMSize=0x34000+0x10000+0x10000;

   if(!(RAM=AllocateMem(0x080000)))return;

   /*-----[Sound Setup]-----*/

   Z80RAM = Z80ROM + 0xc000;
   Z80ROM[0x0074]=0x00; // NOP
   Z80ROM[0x0075]=0x00; // NOP

   Z80ROM[0x0082]=0x00; // NOP
   Z80ROM[0x0083]=0x00; // NOP

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x00C1]=0xD3; // OUTA (AAh)
   Z80ROM[0x00C2]=0xAA; //

   SetStopZ80Mode2(0x00C3);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,                        Z80ROM+0x0000); // Z80 ROM
   AddZ80AReadByte(0xC000, 0xDFFF, NULL,                        Z80ROM+0xC000); // COMM RAM
   AddZ80AReadByte(0xE000, 0xFFFF, shippu_z80_rb,               NULL);          // IOC
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xC000, 0xDFFF, NULL,                       Z80ROM+0xC000); // COMM RAM
   AddZ80AWriteByte(0xE000, 0xFFFF, shippu_z80_wb,              NULL);          // IOC
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   /*-----------------------*/

   RAM_FG0 = RAM+0x20000;
   GFX_FG0 = NULL;

   memset(RAM+0x00000,0x00,0x34000);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x0FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   if (is_current_game("sstriker")) {
     // Skip Hardware Check

     WriteWord68k(&ROM[0x014Ca],0x4E71);          // nop

     // 68000 Speed hack

     WriteLong68k(&ROM[0x03858],0x13FC0000);      // move.b #$00,$AA0000
     WriteLong68k(&ROM[0x0385c],0x00AA0000);      //
   } else {
     // Skip Hardware Check

     WriteWord68k(&ROM[0x014C2],0x4E71);          // nop

     // 68000 Speed hack

     WriteLong68k(&ROM[0x03850],0x13FC0000);      // move.b #$00,$AA0000
     WriteLong68k(&ROM[0x03854],0x00AA0000);      //
   }

   AddResetHandler(&quiet_reset_handler);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x34000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x218000, 0x21FFFF, turbo_68k_rb, NULL);                 // turbo comm ram
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x21C03C, 0x21C03D, TimerRead, NULL);                    // TIMER
   AddReadWord(0x218000, 0x21FFFF, turbo_68k_rw, NULL);                 // turbo comm ram
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x218000, 0x21FFFF, turbo_68k_wb, NULL);                // turbo comm ram
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x500000, 0x503FFF, NULL, RAM+0x020000);                // TEXT RAM (FG0 RAM)
   AddWriteWord(0x218000, 0x21FFFF, turbo_68k_ww, NULL);                // turbo comm ram
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

/******************************************************************************/

#define GFX_FG0_COUNT	0x400

static UINT32 gfx_fg0_dirty_count;
static UINT32 GFX_FG0_DIRTY[GFX_FG0_COUNT];
static UINT8 GFX_FG0_SOLID_2[GFX_FG0_COUNT];

static int tp3vcu_layer_id_data[1];

static char *tp3vcu_layer_id_name[1] =
{
   "FG0",
};

static void tp3vcu_load_update(void);
static void tp3vcu_update_gfx_fg0(void);
static void tp3vcu_gfx_fg0_ww(UINT32 addr, UINT16 data);

static void init_tp3vcu(void)
{
   GFX_FG0_SOLID = GFX_FG0_SOLID_2;

   gfx_fg0_dirty_count = 0;
   memset(GFX_FG0_DIRTY, 0x00, GFX_FG0_COUNT*4);
   memset(GFX_FG0_SOLID, 0x00, GFX_FG0_COUNT);

   tp3vcu_layer_id_data[0] = add_layer_info(tp3vcu_layer_id_name[0]);

   memset(GFX_FG0,0x00, 0x10000);
   memset(RAM_GFX_FG0,0x00, 0x08000);

   AddLoadCallback(tp3vcu_load_update);
}

#undef  RAM_PTR
#undef  GFX_PTR
#define RAM_PTR		RAM_GFX_FG0
#define GFX_PTR		GFX_FG0

static void tp3vcu_load_update(void)
{
   UINT32 i,j;

   gfx_fg0_dirty_count = 0;

   for(i = 0; i < 0x8000; i += 2){
      j = ReadWord(&RAM_PTR[i]);
      WriteWord(&RAM_PTR[i], ~j);
      tp3vcu_gfx_fg0_ww(i, j);
   }

   tp3vcu_update_gfx_fg0();
}

static void tp3vcu_update_gfx_fg0(void)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *source;

   for(ta = 0; ta < gfx_fg0_dirty_count; ta++){

      tb = GFX_FG0_DIRTY[ta];
      source = GFX_PTR + (tb << 6);

      td=0;
      te=0;
      for(tc=0;tc<0x40;tc++){
         if(source[tc])
            td=1;
         else
            te=1;
      }
      if((td==0)&&(te==1)) GFX_FG0_SOLID[tb]=0;	// All pixels are 0: Don't Draw
      if((td==1)&&(te==1)) GFX_FG0_SOLID[tb]=1;	// Mixed: Draw Trans
      if((td==1)&&(te==0)) GFX_FG0_SOLID[tb]=2;	// All pixels are !0: Draw Solid

   }

   gfx_fg0_dirty_count = 0;
}

static void tp3vcu_gfx_fg0_ww(UINT32 addr, UINT16 data)
{
   UINT32 i,k;
   UINT8 *TILE;

   addr &= 0x7FFE;

   if(ReadWord(&RAM_PTR[addr])!=data){

   // Write to RAM

   WriteWord(&RAM_PTR[addr],data);

   // Write to 8x8 GFX

   i = (addr & 0x001E) << 1;
   k = (addr & 0x7FE0) >> 5;

   TILE = GFX_PTR + (k<<6);

   TILE[tile_8x8_map[i+0]] = (data >>  4) & 0x0F;
   TILE[tile_8x8_map[i+1]] = (data >>  0) & 0x0F;
   TILE[tile_8x8_map[i+2]] = (data >> 12) & 0x0F;
   TILE[tile_8x8_map[i+3]] = (data >>  8) & 0x0F;

   // request mask update

   if(GFX_FG0_SOLID[k] != 3){
      GFX_FG0_SOLID[k] = 3;
      GFX_FG0_DIRTY[gfx_fg0_dirty_count++] = k;
   }

   }
}

/******************************************************************************/

static UINT32 object_bank[8];
static UINT32 sound_data[8];
static UINT32 sound_nmi;

static UINT8 *BR_Z80_ROM;
static UINT8 *BR_Z80_BANK[0x10];
static UINT32  br_z80_bank;

/*

 0x48 0x4A | info
 ----------+-------------
 0x00  n   | play tune n
 0x55 0x00 | init
 0x01 0x00 | stop

*/

static UINT8 batrider_z80_port_rb(UINT8 offset)
{
   switch(offset){
      case 0x48:
         return sound_data[0];
      break;
      case 0x4A:
         return sound_data[1];
      break;
      case 0x80:
	break;
      case 0x81:
	return YM2151_status_port_0_r(offset);
      break;
      case 0x82:
         //return M6295buffer_status(0);
	return OKIM6295_status_0_r(0);
        //return 0;
      break;
      case 0x84:
         //return M6295buffer_status(1);
	return OKIM6295_status_1_r(1);
	//return 0;
      break;
      default:
            print_debug("batrider_ioc_z80_rb(%02x)\n", offset);
      break;
   }
   return 0x00;
}

static UINT8 bbakraid_z80_port_rb(UINT8 offset)
{
  //fprintf(stderr,"bakraid_read_port(%02x)\n", offset);
   switch(offset){
      case 0x48:
         return sound_data[0];
      break;
      case 0x4A:
         return sound_data[1];
      break;
      case 0x80:
	break;
      case 0x81:
	return YMZ280B_status_0_r(offset);
      break;
      default:
	print_debug("batrider_ioc_z80_rb(%02x)\n", offset);
	break;
   }
   return 0x00;
}

static UINT8 m6295_bank[2][4];
static UINT8 command[2];

static void batrider_z80_port_wb(UINT8 offset, UINT8 data)
{
   UINT32 ta;
   switch(offset){
      case 0x40:
      case 0x42:
      case 0x44:
      case 0x46:
         sound_data[4 | ((offset>>1)&3)] = data;
      break;
      case 0x80:
         ym2151_z80_wb(offset, data);
      break;
      case 0x81:
         ym2151_z80_wb(offset, data);
      break;
      case 0x82:
	if(!(command[0]&0x80)){
            command[0] = 0x80;
            ta=0;
            if(data&0x20) ta=1;
            if(data&0x40) ta=2;
            if(data&0x80) ta=3;
	    // OKIM6295_set_bank_base(0, ALL_VOICES, ta * 0x10000);
	    raizing_oki6295_set_bankbase(0,ta,m6295_bank[0][ta] * 0x10000);
            // M6295buffer_bankswitch(0, m6295_bank[0][ta]);
         }
	else{
	  if(data&0x80){
	    command[0] = data & 0x7F;
	    // This line prevents the sound "Raizing !" in the title screen!
	    //data &= ~0x60;
            }
         }
	OKIM6295_data_0_w(0,data);
         //M6295buffer_request(0, data);
      break;
      case 0x84:
	if(!(command[1]&0x80)){
            command[1] = 0x80;
            ta=0;
            if(data&0x20) ta=1;
            if(data&0x40) ta=2;
            if(data&0x80) ta=3;
	    raizing_oki6295_set_bankbase(1,ta,m6295_bank[1][ta] * 0x10000);
	    //  OKIM6295_set_bank_base(1, ALL_VOICES, ta  * 0x10000);
            // M6295buffer_bankswitch(1, m6295_bank[1][ta]);
         }
         else{
            if(data&0x80){
               command[1] = data & 0x7F;
	       //data &= ~0x60;
            }
         }
	OKIM6295_data_1_w(1,data);
         //M6295buffer_request(1, data);
      break;
      case 0x88:
         data &= 0x0F;
         if(br_z80_bank != data){
            br_z80_bank = data;
            Z80ASetBank(BR_Z80_BANK[br_z80_bank]);
         }
      break;
      case 0xC0:
	//raizing_okim6295_bankselect_0(offset,data);
	//m6295_bank[0][0] = data;
	m6295_bank[0][0] = (data >> 0) & 0x0F;
	m6295_bank[0][1] = (data >> 4) & 0x0F;
      break;
      case 0xC2:
	//raizing_okim6295_bankselect_1(offset,data);
	//m6295_bank[0][2] = data;
	m6295_bank[0][2] = (data >> 0) & 0x0F;
	m6295_bank[0][3] = (data >> 4) & 0x0F;
      break;
      case 0xC4:
	//raizing_okim6295_bankselect_2(offset,data);
	//m6295_bank[1][0] = data;
	m6295_bank[1][0] = (data >> 0) & 0x0F;
        m6295_bank[1][1] = (data >> 4) & 0x0F;
	break;
      case 0xC6:
	//raizing_okim6295_bankselect_3(offset,data);
	//m6295_bank[0][2] = data;
	m6295_bank[1][2] = (data >> 0) & 0x0F;
	m6295_bank[1][3] = (data >> 4) & 0x0F;
      break;
      default:
            print_debug("batrider_ioc_z80_wb(%02x,%02x)\n", offset, data);
      break;
   }
}

static void bbakraid_z80_port_wb(UINT8 offset, UINT8 data)
{
  //fprintf(stderr,"bakraid_write_port(%02x,%02x)\n", offset, data);
  switch(offset){
      case 0x40:
      case 0x42:
      case 0x44:
      case 0x46:
         sound_data[4 | ((offset>>1)&3)] = data;
      break;
      case 0x80:
         YMZ280B_register_0_w(offset, data);
      break;
      case 0x81:
         YMZ280B_data_0_w(offset, data);
      break;
      case 0x88:
         data &= 0x0F;
         if(br_z80_bank != data){
            br_z80_bank = data;
            Z80ASetBank(BR_Z80_BANK[br_z80_bank]);
         }
      break;
      default:
            print_debug("batrider_ioc_z80_wb(%02x,%02x)\n", offset, data);
      break;
   }
}

UINT8 bakraid_w11,bakraid_w13; // ???

// From mame. Thanks to the person over there who understands the eeproms.
// I really had no chance to find out here.
/*###################### Battle Bakraid ##############################*/
static int raizing_Z80_busreq;

static struct EEPROM_interface eeprom_interface_93C66 =
{
  /* Pin 6 of the 93C66 is connected to Gnd!
     So it's configured for 512 bytes */

  9,			/* address bits */
  8,			/* data bits */
  "*110",		/* read			110 aaaaaaaaa */
  "*101",		/* write		101 aaaaaaaaa dddddddd */
  "*111",		/* erase		111 aaaaaaaaa */
  "*10000xxxxxxx",/* lock			100x 00xxxx */
  "*10011xxxxxxx",/* unlock		100x 11xxxx */
  /*	"*10001xxxx",	// write all	1 00 01xxxx dddddddd */
  /*	"*10010xxxx"	// erase all	1 00 10xxxx */
};

static UINT8 bbakraid_nvram_r(UINT16 offset)
{
  /* Bit 1 returns the status of BUSAK from the Z80.
     BUSRQ is activated via bit 0x10 on the NVRAM write port.
     These accesses are made when the 68K wants to read the Z80
     ROM code. Failure to return the correct status incurrs a Sound Error.
  */

  int data;
  data  = ((EEPROM_read_bit() & 0x01) << 4);
  data |= ((raizing_Z80_busreq >> 4) & 0x01);	/* Loop BUSRQ to BUSAK */

  return data;
}

static void bbakraid_nvram_w(UINT16 offset, UINT8 data)
{
  /* chip select */
  EEPROM_set_cs_line((data & 0x01) ? CLEAR_LINE : ASSERT_LINE );

  /* latch the bit */
  EEPROM_write_bit( (data & 0x04) >> 2 );

  /* clock line asserted: write latch or select next bit to read */
  EEPROM_set_clock_line((data & 0x08) ? ASSERT_LINE : CLEAR_LINE );
  raizing_Z80_busreq = data & 0x10;	/* see bbakraid_nvram_r above */
}

static UINT8 batrider_ioc_68k_rb(UINT32 offset)
{
   offset &= 0xFF;

   switch(offset){
      case 0x00:
         return input_buffer[2];
      break;
      case 0x01:
         return input_buffer[1];
      break;
      case 0x02:
         return get_dsw(2);
      break;
      case 0x03:
         return input_buffer[0];
      break;
      case 0x04:
         return get_dsw(1);
      break;
      case 0x05:
         return get_dsw(0);
      break;
      case 0x06:
         return 0x80;
      break;

      case 0x07:
	return TimerRead(0);
      break;
      case 0x09:
      case 0x0B:
      case 0x0D:
      case 0x0F:
         return sound_data[4 | ((offset>>1)&3)];
      break;
      // These are for bakraid
   case 0x19: // ??? Only bit 4 is tested (freeze the game)
     return bbakraid_nvram_r(0); // 0x10; // This one is read many times in frame
     //case 0x10: // bbakraid soundcmd buffer...
   case 0x11:
     //case 0x12:
   case 0x13:
/*      if (sound_data[4 | ((offset>>1)&3)]) */
     return sound_data[4 | ((offset>>1)&3)];
     //return bakraid_w13;

   case 0x18:
     return input_buffer[1];
     // end of bakraid
      case 0x08:
      case 0x0A:
      case 0x0C:
      case 0x0E:
         return 0;
      break;
      default:
         return 0;
      break;
   }

}

static UINT16 batrider_ioc_68k_rw(UINT32 offset)
{
  //fprintf(stderr,"rw %x\n",offset);
   return (batrider_ioc_68k_rb(offset+0) << 8) |
          (batrider_ioc_68k_rb(offset+1) << 0);
}

static void batrider_ioc_68k_wb(UINT32 offset, UINT8 data)
{
   offset &= 0xFF;

   switch(offset){
   case 9: // bakraid irq ?
     // sound_irq = 1;
     // cpu_interrupt(CPU_Z80_0,0x38);
     break;
   case 0x11:
     set_toaplan2_leds(data);
     break;

      // These are for bakraid
   case 0x14:
   case 0x16:
      //case 0x16:
      break;
   case 0x15:
     //bakraid_w11 = data;
     cpu_int_nmi(CPU_Z80_0);
     // fprintf(stderr,"bankraid sound 0 %x\n",data);
     sound_data[0] = data;
     break;
   case 0x17:
     //bakraid_w13 = data;
     cpu_int_nmi(CPU_Z80_0);
     // fprintf(stderr,"bankraid sound 1 %x\n",data);
     sound_data[1] = data;
     break;
     // The 2 last (0x15 & 0x17) are read in 0x11 and 0x13.
     // Apparently it is not just RAM. It is some kind of hardware.
     // Maybe sound... ?

     // while testing hardware, these addresses receive 0,0,2,ff for each vbl.
     break;
     //case 0x1a:
     //case 0x1b:
     // These 2 receive 0,ff for each vbl during the init...
     //break;
   case 0x1c: // This one receives values which are sent to 0x82 afterwards...
     break;
   case 0x1d:
      break;
   case 0x1e:
     break;
   case 0x1f: // This one receives bytes <= 0xf, many times per frame
     bbakraid_nvram_w(0,data);
     // A bank ??? (related to z80 bank)
     break;
     // end of bakraid
      case 0x20:
      case 0x22:
      case 0x24:
      case 0x26:

      break;
      case 0x21:
      case 0x23:
         sound_nmi = 1;
      case 0x25:
      case 0x27:
         sound_data[(offset>>1)&3] = data;
      break;

      case 0x80:
         memcpy(RAM_GFX_FG0,RAM+0x00000,0x8000);
         tp3vcu_load_update();
      break;
      case 0xC1:
      case 0xC3:
      case 0xC5:
      case 0xC7:
      case 0xC9:
      case 0xCB:
      case 0xCD:
      case 0xCF:
         object_bank[(offset>>1)&7] = (data & 0x0F) << 15;
      break;
      case 0xC0:
      case 0xC2:
      case 0xC4:
      case 0xC6:
      case 0xC8:
      case 0xCA:
      case 0xCC:
      case 0xCE:
      break;
      default:
      break;
   }

}

static void batrider_ioc_68k_ww(UINT32 offset, UINT16 data)
{
  //fprintf(stderr,"ww %x,%x\n",offset,data);
   batrider_ioc_68k_wb(offset+0, data >> 8);
   batrider_ioc_68k_wb(offset+1, data >> 0);
}

static void br_refresh_z80_bank(void)
{
   Z80ASetBank(BR_Z80_BANK[br_z80_bank]);
}

static void br_init_z80_bank(UINT8 *src)
{
   UINT32 i;

   for(i = 0; i < 0x10; i++){

      BR_Z80_BANK[i] = BR_Z80_ROM + (i * 0xC000);

      memcpy(BR_Z80_BANK[i]+0x0000, src,              0x8000);
      memcpy(BR_Z80_BANK[i]+0x8000, src+(i * 0x4000), 0x4000);

   }

   memcpy(Z80ROM, BR_Z80_BANK[2], 0xC000);
   memset(Z80ROM+0xC000, 0x00,    0x4000);

   br_z80_bank = 2;

   AddLoadCallback(br_refresh_z80_bank);

   AddSaveData(SAVE_USER_0, (UINT8 *) &br_z80_bank,         sizeof(br_z80_bank));
   AddSaveData(SAVE_USER_1, (UINT8 *) &object_bank,         sizeof(object_bank));
   AddSaveData(SAVE_USER_2, (UINT8 *) &sound_data,          sizeof(sound_data));
   AddSaveData(SAVE_USER_3, (UINT8 *) &sound_nmi,           sizeof(sound_nmi));
}

static UINT8 batrider_68k_z80rom_rb(UINT32 offset)
{
   offset >>= 1;
   offset  &= 0x3FFFF;
   // fprintf(stderr,"read from %x\n",s68000readPC());
   if (offset < 0x8000)
     return BR_Z80_BANK[0][offset];
   return BR_Z80_BANK[offset >> 14][(offset & 0x3FFF)|0x8000];
}

static UINT16 batrider_68k_z80rom_rw(UINT32 offset)
{
   offset >>= 1;
   offset  &= 0x3FFFF;

   if (offset < 0x8000)
     return BR_Z80_BANK[0][offset];
   return BR_Z80_BANK[offset >> 14][(offset & 0x3FFF)|0x8000];
}

static void load_batrider(void)
{
   UINT8 *TMP;

   romset=11;

   if(!(GFX=AllocateMem(0x2000000)))return;
   if(!(TMP=AllocateMem(0x0400000)))return;

   load_tp2_gfx("rom-1.bin","rom-2.bin",0x400000,TMP,GFX);
   load_tp2_gfx("rom-3.bin","rom-4.bin",0x400000,TMP,&GFX[0x1000000]);

   FreeMem(TMP);

   if (!init_tilequeue()) return;

   RAMSize=0x34000+0x10000+0x10000;

   if(!(RAM=AllocateMem(0x080000)))return;

   if(!(PCMROM = AllocateMem(0x140000*2))) return;
   if(!load_rom("rom-5.bin", PCMROM+0x040000, 0x100000)) return;
   if(!load_rom("rom-6.bin", PCMROM+0x140000 + 0x40000, 0x100000)) return;
   ADPCMSetBuffers(((struct ADPCMinterface*)&batrider_m6295),PCMROM+0x00000,0x140000);
   PCMBanksize=0x140000;

   Z80ROM = RAM+0x34000+0x10000;

   if(!(BR_Z80_ROM = AllocateMem(0x10*0xC000))) return;
   if(!load_rom("snd.u77", RAM, 0x40000)) return;          // Z80 SOUND ROM

   // Apply Speed Patch

   RAM[0x029F]=0xD3; // OUTA (AAh)
   RAM[0x02A0]=0xAA; //

   br_init_z80_bank(RAM);

   SetStopZ80Mode2(0x0299);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,                        NULL); 		// Z80 ROM
   AddZ80AReadByte(0xC000, 0xDFFF, NULL,                        Z80ROM+0xC000); // COMM RAM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xC000, 0xDFFF, NULL,                       Z80ROM+0xC000); // COMM RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, batrider_z80_port_rb,            NULL);          // IOC
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,                   NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                            NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,                   NULL);
   AddZ80AWritePort(0x00, 0xFF, batrider_z80_port_wb,           NULL);          // IOC
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,                 NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                           NULL);

   AddZ80AInit();

   /*-----------------------*/

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x80000);

   RAM_FG0 = RAM+0x00000;
   RAM_GFX_FG0 = RAM+0x24000;
   GFX_FG0 = RAM+0x34000;

   memset(RAM+0x00000,0x00,0x34000);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x3FFFF;
   init_tp2vcu(0);

   init_tp3vcu();

   InitPaletteMap(RAM+0x02000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   if(is_current_game("batridra")){

   // Fix bad checksums

   WriteWord68k(&ROM[0x177A4],0x6100 - 0x18);

   // Fix some comm timeouts

   WriteLong68k(&ROM[0x16CEC],0x4E714E71);      // nop
   WriteWord68k(&ROM[0x170B0],0x4E71);          // nop

   }
   else{

   // Fix bad checksums

   WriteWord68k(&ROM[0x177E4],0x6100 - 0x18);

   // Fix some comm timeouts

   WriteLong68k(&ROM[0x16D2C],0x4E714E71);      // nop
   WriteWord68k(&ROM[0x170F0],0x4E71);          // nop

   }

   // Fix some comm timeouts

   WriteLong68k(&ROM[0x02EC8],0x4E714E71);      // nop
   WriteWord68k(&ROM[0x03118],0x6000);
   WriteWord68k(&ROM[0x0313E],0x6000);

   // 68000 Speed hack

   WriteLong68k(&ROM[0x01FF6],0x13FC0000);      // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x01FFA],0x00AA0000);      //
   WriteWord68k(&ROM[0x01FFE],0x4E71);          // nop

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x00248],0x4E71);          // nop

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x200000);
   ByteSwap(RAM,0x034000);

   AddMemFetch(0x000000, 0x1FFFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x1FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x200000, 0x20FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x400000, 0x40000F, tp2vcu_0_rb_alt, NULL);              // GCU RAM (SCREEN)
   AddReadByte(0x500000, 0x5000FF, batrider_ioc_68k_rb, NULL);          // turbo comm ram
   AddReadByte(0x300000, 0x37FFFF, batrider_68k_z80rom_rb, NULL);       // z80 rom check
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x1FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x200000, 0x20FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x400000, 0x40000F, tp2vcu_0_rw_alt, NULL);              // GCU RAM (SCREEN)
   AddReadWord(0x500000, 0x5000FF, batrider_ioc_68k_rw, NULL);          // turbo comm ram
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x500000, 0x5000FF, batrider_ioc_68k_wb, NULL);         // turbo comm ram
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x400000, 0x40000F, tp2vcu_0_ww_alt, NULL);             // GCU RAM (SCREEN)
   AddWriteWord(0x500000, 0x5000FF, batrider_ioc_68k_ww, NULL);         // turbo comm ram
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

/******* Sound Comm by BouKiCHi *******/

UINT8 commram[0x100];

static UINT8 batcomm_rb(UINT16 addr)
{
   switch(addr){
      case 0xE001:
	return YM2151_status_port_0_r(addr);
      case 0xE004:
	//return 0x0;
	return m6295_z80_rb(addr);
      break;
      case 0xE01C:
	return commram[0x01];
      break;
   case 0xE01D:
	return commram[0x03];
      break;
   }
   return 0x00;
}

UINT8 pcmbank=0;

static void batcomm_wb(UINT16 addr,UINT8 data)
{
   UINT8 ta;
   switch(addr){
      case 0xE000:
         ym2151_z80_wb(addr, data);
      break;
      case 0xE001:
         ym2151_z80_wb(addr, data);
      break;
      case 0xE004:
	if (romset != 14) {
	  if(!(command[0]&0x80)){
            command[0] = 0x80;
            ta=0;
            if(data&0x20) ta=1;
            if(data&0x20) ta=1;
            if(data&0x40) ta=2;
            if(data&0x80) ta=3;
	    raizing_oki6295_set_bankbase(0,ta,m6295_bank[0][ta] * 0x10000);
            //M6295buffer_bankswitch(0, m6295_bank[0][ta]);
	  }
	  else{
            if(data&0x80){
	      command[0] = data & 0x7F;
	      //data &= ~0x60;
            }
	  }
	}
	OKIM6295_data_0_w(0,data);
	//M6295buffer_request(0, data);
      break;
      case 0xE006:
	raizing_okim6295_bankselect_0(addr,data);
	//m6295_bank[0][0] = (data >> 0) & 0x0F;
	//m6295_bank[0][1] = (data >> 4) & 0x0F;
      break;
      case 0xE008:
	raizing_okim6295_bankselect_1(addr,data);
	//m6295_bank[0][2] = (data >> 0) & 0x0F;
	//m6295_bank[0][3] = (data >> 4) & 0x0F;
      break;
      case 0xE00A:

         data &= 0x0F;
         data-=0x8; // A-2
         if(br_z80_bank != data){
            br_z80_bank = data;
            Z80ASetBank(BR_Z80_BANK[br_z80_bank]);
         }
      break;
      case 0xE00C:
	commram[0x01]=data;
      break;
#ifdef RAINE_DEBUG
      default:
        print_debug("batcomm_wb(%04x,%02x)\n", addr,data);
#endif
   }
   //commram[addr&0xFF]=data;
}


static UINT8 battleg_z80_port_rb(UINT8 offset)
{
   print_debug("batleg_z80_rb(%02x)\n", offset);
   return 0x00;
}

static void battleg_z80_port_wb(UINT8 offset, UINT8 data)
{
         print_debug("batleg_z80_wb(%02x,%02x)\n", offset, data);
}


static void sound_battleg_wb(UINT32 offset, UINT8 data)
{
        print_debug("batleg_sound(%04x,%02x)\n", offset,data);
//   sound_nmi=1;
   offset &= 0x0FF;
   commram[offset]=data;

   cpu_interrupt(CPU_Z80_0, 0x38);
   cpu_execute_cycles(CPU_Z80_0,1000); // We don't cut the frame so we can
   // allow this...
}


static void sound_battleg_ww(UINT32 offset, UINT16 data)
{
  // Should not be called normally (or there would twice too much interrupts!)
  sound_battleg_wb(offset+0, data >> 8);
  sound_battleg_wb(offset+1, data >> 0);
}

// Battle bakraid

static struct ROM_INFO rom_bbakraid[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "prg0u022.new",  0xfa8d38d3 , "prg1u023.new",  0x4ae9aa64 ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x080000,
            "prg2u021.bin",  0xffba8656 , "prg3u024.bin",  0x834b8ad6 ),
  { "sndu027.bin", 0x20000, 0xe62ab246 , 0,0,0 },//REGION_ROM2, 0, LOAD_NORMAL },
  { "gfxu0510.bin", 0x400000, 0x9cca3446 , 0,0,0 }, // REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "gfxu0511.bin", 0x400000, 0xe16472c0 , 0,0,0 }, // REGION_GFX1, 0x400000, LOAD_NORMAL },
  { "gfxu0512.bin", 0x400000, 0xa2a281d5 , 0,0,0 }, // REGION_GFX1, 0x800000, LOAD_NORMAL },
  { "gfxu0513.bin", 0x400000, 0x8bb635a0 , 0,0,0 }, // REGION_GFX1, 0xc00000, LOAD_NORMAL },

  { "rom6.829", 0x400000, 0x8848b4a0 /*0x464f2900*/ , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "rom7.830", 0x400000, 0xd6224267 /*0xa1c27c04*/ , REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "rom8.831", 0x400000, 0xa101dfb0 /*0x262914c3*/ , REGION_SMP1, 0x800000, LOAD_NORMAL },

  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_bbakrada[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "prg0u022.bin",  0x0dd59512 , "prg1u023.bin",  0xfecde223 ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x080000,
            "prg2u021.bin",  0xffba8656 , "prg3u024.bin",  0x834b8ad6 ),
  { "sndu027.bin", 0x20000, 0xe62ab246 , 0,0,0 }, // REGION_ROM2, 0, LOAD_NORMAL },
  { "gfxu0510.bin", 0x400000, 0x9cca3446 , 0,0,0 }, // REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "gfxu0511.bin", 0x400000, 0xe16472c0 , 0,0,0 }, // REGION_GFX1, 0x400000, LOAD_NORMAL },
  { "gfxu0512.bin", 0x400000, 0xa2a281d5 , 0,0,0 }, // REGION_GFX1, 0x800000, LOAD_NORMAL },
  { "gfxu0513.bin", 0x400000, 0x8bb635a0 , 0,0,0 }, // REGION_GFX1, 0xc00000, LOAD_NORMAL },

  { "rom6.829", 0x400000, 0x8848b4a0 /*0x464f2900*/ , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "rom7.830", 0x400000, 0xd6224267 /*0xa1c27c04*/ , REGION_SMP1, 0x400000, LOAD_NORMAL },
  { "rom8.831", 0x400000, 0xa101dfb0 /*0x262914c3*/ , REGION_SMP1, 0x800000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static void setup_garega_z80(char *name) {
  if(!(BR_Z80_ROM = AllocateMem(0x10*0xC000))) return;
  if(!load_rom(name, RAM, 0x20000)) return;          // Z80 SOUND ROM

   // Apply Speed Patch
/* katharsis let's see what happens without the patch
   RAM[0x029F]=0xD3; // OUTA (AAh)
   RAM[0x02A0]=0xAA; //
*/
   br_init_z80_bank(RAM);

   SetStopZ80Mode2(0x0299);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,                        NULL); 		// Z80 ROM
   AddZ80AReadByte(0xC000, 0xDFFF, NULL,                        Z80ROM+0xC000); // COMM RAM
   AddZ80AReadByte(0xE000, 0xE0FF, batcomm_rb,                  NULL); // COMM RAM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xC000, 0xDFFF, NULL,                       Z80ROM+0xC000); // COMM RAM
   AddZ80AWriteByte(0xE000, 0xE0FF, batcomm_wb,                 NULL); // COMM RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, battleg_z80_port_rb,            NULL);          // IOC
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,                   NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                            NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,                   NULL);
   AddZ80AWritePort(0x00, 0xFF, battleg_z80_port_wb,           NULL);          // IOC
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,                 NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                           NULL);

   AddZ80AInit();
}

static void setup_bakraid_z80(char *name) {
  if(!(BR_Z80_ROM = AllocateMem(0x10*0xC000))) return;
  if(!load_rom(name, RAM, 0x20000)) return;          // Z80 SOUND ROM

  // speed hack
  RAM[0x103d] = 0xD3; // OUTA (AAh)
  RAM[0x103e] = 0xaa;

   br_init_z80_bank(RAM);

   // SetStopZ80Mode2(0x0299);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,                        NULL); 		// Z80 ROM
   AddZ80AReadByte(0xC000, 0xffff, NULL,         Z80ROM+0xc000); // RAM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xC000, 0xffff, NULL,        Z80ROM+0xc000); // COMM RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, bbakraid_z80_port_rb,            NULL);          // IOC
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,                   NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                            NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80,                   NULL);
   AddZ80AWritePort(0x00, 0xFF, bbakraid_z80_port_wb,           NULL);          // IOC
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,                 NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                           NULL);

   AddZ80AInit();
}

// Well maybe we don't need all these 512 bytes, but I really don't know what
// to cut !
// Anyway, this eeprom makes bbakraid really unlimited (all ships, all modes).
// There are 2 ways to reproduce this effect : disable completely the eeprom
// but I'd prefer to keep it
// or use the cheat codes !
static UINT8 bbakraid_eeprom[] =
  {
    0xc2,0x49,0x00,0x07,0xa1,0x20,0x2a,0x2a,0x2a,0x90,0x90,0x90,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x06,0x1a,0x80,
    0x2a,0x2a,0x2a,0x94,0x94,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x04,0x93,0xe0,0x2a,0x2a,0x2a,0x98,0x98,0x98,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,
    0x0d,0x40,0x2a,0x2a,0x2a,0x9c,0x9c,0x9c,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x01,0x86,0xa0,0x2a,0x2a,0x2a,0xa0,
    0xa0,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
    0x00,0x07,0xa1,0x20,0x2b,0x2b,0x2b,0x90,0x90,0x90,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x06,0x1a,0x80,0x2b,0x2b,
    0x2b,0x94,0x94,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x02,0x00,0x04,0x93,0xe0,0x2b,0x2b,0x2b,0x98,0x98,0x98,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,0x0d,0x40,
    0x2b,0x2b,0x2b,0x9c,0x9c,0x9c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x01,0x86,0xa0,0x2b,0x2b,0x2b,0xa0,0xa0,0xa0,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x07,
    0xa1,0x20,0x23,0x23,0x23,0x90,0x90,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x06,0x1a,0x80,0x23,0x23,0x23,0x94,
    0x94,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
    0x00,0x04,0x93,0xe0,0x23,0x23,0x23,0x98,0x98,0x98,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,0x0d,0x40,0x23,0x23,
    0x23,0x9c,0x9c,0x9c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x02,0x00,0x01,0x86,0xa0,0x23,0x23,0x23,0xa0,0xa0,0xa0,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x07,0xa1,0x20,
    0x3f,0x3f,0x3f,0x90,0x90,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x02,0x00,0x06,0x1a,0x80,0x3f,0x3f,0x3f,0x94,0x94,0x94,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x04,
    0x93,0xe0,0x3f,0x3f,0x3f,0x98,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,0x0d,0x40,0x3f,0x3f,0x3f,0x9c,
    0x9c,0x9c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
    0x00,0x01,0x86,0xa0,0x3f,0x3f,0x3f,0xa0,0xa0,0xa0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x04,0xc2,0x49,0xc2,0x49,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0xcf,
    0x00,0x04,0x00,0x00,0x21,0xd5,0x00,0x05,0x06,0xff,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xff,0xc2,0x49 };

static void myStop68000(UINT32 address, UINT8 data)
{
	(void)(address);
	(void)(data);
   s68000releaseTimeslice();
   cycles = 0;
   print_debug("[Stop68000]\n");
}

static void load_bbakraid() {
  UINT8 *TMP;

  default_eeprom = bbakraid_eeprom;
  default_eeprom_size = sizeof(bbakraid_eeprom);
  EEPROM_init(&eeprom_interface_93C66);
  load_eeprom();

  ByteSwap(ROM,get_region_size(REGION_ROM1));

  romset=11; // batrider... Used for drawing.

   if (!init_tilequeue()) return;
   RAMSize=0x34000+0x10000+0x10000;

   if(!(RAM=AllocateMem(0x080000)))return;
   Z80ROM = RAM+0x34000+0x10000;
   setup_bakraid_z80("sndu027.bin");

   if(!(GFX=AllocateMem(0x2000000)))return;
   if(!(TMP=AllocateMem(0x0400000)))return;

   load_tp2_gfx("Gfxu0510.bin","Gfxu0511.bin",0x400000,TMP,GFX);
   load_tp2_gfx("Gfxu0512.bin","Gfxu0513.bin",0x400000,TMP,&GFX[0x1000000]);

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x80000);

   RAM_FG0 = RAM+0x00000;
   RAM_GFX_FG0 = RAM+0x24000;
   GFX_FG0 = RAM+0x34000;

   memset(RAM+0x00000,0x00,0x34000);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x3FFFF;
   init_tp2vcu(0);

   init_tp3vcu();

   InitPaletteMap(RAM+0x02000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // Starscream

   AddMemFetch(0x000000, 0x1FFFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadBW(0x000000, 0x1FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddRWBW(0x200000, 0x20FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x400000, 0x40000F, tp2vcu_0_rb_alt, NULL);              // GCU RAM (SCREEN)
   AddReadByte(0x500000, 0x5000FF, batrider_ioc_68k_rb, NULL);          // turbo comm ram
   AddReadByte(0x300000, 0x37FFFF, batrider_68k_z80rom_rb, NULL);       // z80 rom check
   AddReadByte(0x300000, 0x37FFFF, batrider_68k_z80rom_rw, NULL);       // z80 rom check
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x400000, 0x40000F, tp2vcu_0_rw_alt, NULL);              // GCU RAM (SCREEN)
   AddReadWord(0x500000, 0x5000FF, batrider_ioc_68k_rw, NULL);          // turbo comm ram
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x500000, 0x5000FF, batrider_ioc_68k_wb, NULL);         // turbo comm ram
   AddWriteByte(0xAA0000, 0xAA0001, myStop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x400000, 0x40000F, tp2vcu_0_ww_alt, NULL);             // GCU RAM (SCREEN)
   AddWriteWord(0x500000, 0x5000FF, batrider_ioc_68k_ww, NULL);         // turbo comm ram
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddResetHandler(&quiet_reset_handler);
   AddInitMemory();     // Set Starscream mem pointers...

   // Hacks

  // Speed hacks : vbl seems tested in $203d5b (byte). Blanked at each vbl.

   // This one works better !
   WriteWord(&ROM[0x1ff0],0x4239);
   WriteWord(&ROM[0x1ff2],0xaa);
   WriteWord(&ROM[0x1ff4],0);
   WriteWord(&ROM[0x1ff6],0x4e71);
   WriteWord(&ROM[0x1ff8],0x4e71);

   // WriteWord(&ROM[0x17fbc],0x60fe);
   ROM[0x17fb9] = 0x60; // rom check

/*    WriteWord(&ROM[0x19364],0x4e71); */

   ROM[0x17fd9] = 0x60; // rom check
}

#define SLICE 8

static void execute_bbakraid() {
  int n;
  int z80ok = 1;
  cycles = 1;

  for (n=0; n<SLICE; n++) {
    //if (z80ok) {
      cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(7,60)/SLICE);    // Z80 4MHz (60fps)
      cpu_interrupt(CPU_Z80_0,0x38);
    if (cycles) // not reached the speed hack
      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(28,60)/SLICE);    // M68000 28MHz (60fps)
    else {
      if (!z80ok)
	break;
    }
  }
  // Which is best ? Int 1 or 3 ? Int 3 calls more things, but is it usefull ?
  // Anyway both these interrupts handle controls, so they are necessary (1
  // of them is at least).
  cpu_interrupt(CPU_68K_0, 3);
  // The z80 seems to stop or have a bad mapping (not surprising !)
  // Since I don't know anything to z80 asm, I'll leave it for now...
#if 0
  if (sound_nmi) {
    cpu_int_nmi(CPU_Z80_0);
    sound_nmi = 0;
  }
  cpu_interrupt(CPU_Z80_0, 0x38);
#endif
}

static struct DSW_DATA dsw_data_bbakraid_0[] =
{
   DSW_TEST_MODE( 0x01, 0x00),
   { _("Credits to Start"),      0x02, 0x02 },
   { _("1 Credit"),              0x00},
   { _("2 Credits"),             0x02},
   { MSG_COIN1,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x04},
   { MSG_1COIN_3PLAY,         0x08},
   { MSG_1COIN_4PLAY,         0x0C},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x14},
   { MSG_4COIN_1PLAY,         0x18},
   { MSG_FREE_PLAY,           0x1C},
   { MSG_COIN2,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_1COIN_4PLAY,         0x60},
   { MSG_2COIN_1PLAY,         0x80},
   { MSG_3COIN_1PLAY,         0xA0},
   { MSG_4COIN_1PLAY,         0xC0},
   { MSG_1COIN_1PLAY,         0xE0},
/* Dip Switches when _("Free Play") :
   { _("Stick Mode"),            0x20, 0x02 },
   { _("Normal"),                0x00},
   { _("Special"),               0x20},
   { _("Hit Score"),             0x20, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x20},
   { _("Sound Effect"),          0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Music"),                 0x80, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
*/
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_bbakraid_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { _("Timer"),                 0x0C, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x04},
   { MSG_HARD,                0x08},
   { MSG_HARDEST,             0x0C},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x00},
   { "4",                     0x10},
   { "2",                     0x20},
   { "1",                     0x30},
   { MSG_EXTRA_LIFE,          0xC0, 0x04 },
   { _("every 2000k"),           0x00},     // "200000" is displayed in 'bbakraid'
   { _("every 3000k"),           0x40},     // "300000" is displayed in 'bbakraid'
   { _("every 4000k"),           0x80},     // "400000" is displayed in 'bbakraid'
   { _("None"),                  0xC0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_bbakraid_2[] =
{
   DSW_SCREEN( 0x00, 0x01),
   DSW_DEMO_SOUND( 0x00, 0x02),
   { _("Stage Edit"),            0x04, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON ,                 0x04},
   DSW_CONTINUE_PLAY( 0x00, 0x08),
   { MSG_CHEAT,               0x10, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x10},
   { _("Score Ranking"),         0x20, 0x02 },     // What is this Dip Switch supposed to do ?
   { _("Save"),                  0x00},
   { _("No Save"),               0x20},     // I can't confirm this one 8(
   { MSG_DSWC_BIT7,           0x40, 0x02 },     // Unknown ! Region switch ?
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { MSG_DSWC_BIT8,           0x80, 0x02 },     // Unknown ! Region switch ?
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_bbakraid[] =
{
   { 0x000003, 0x00, dsw_data_bbakraid_0 },
   { 0x000004, 0x00, dsw_data_bbakraid_1 },
   { 0x000005, 0x00, dsw_data_bbakraid_2 },
   { 0,        0,    NULL,      },
};

/**************** Battle Garegga ********************/

static UINT8 battleg_ioc_68k_rb(UINT32 offset)
{
   offset &= 0x7FFF;

   switch(offset){
      case 0x21:
	return Z80ROM[0xC010];
      //case 0x0023: return commram[0x23];
      case 0x4021:
         return input_buffer[1];
      break;
      case 0x4025:
         return input_buffer[2];
      break;
      case 0x4029:
         return input_buffer[0];
      break;
      case 0x402D:
         return get_dsw(0);
      break;
      case 0x4031:
         return get_dsw(1);
      break;
      case 0x4035:
         return get_dsw(2);
      break;
      case 0x403C:
         return 0x80;
      break;
      case 0x403D:
         return TimerRead(0);
      break;
      default:
            print_debug("battleg_ioc_68k_rb(%04x)\n", offset);
         return 0;
      break;
   }

}

static UINT16 battleg_ioc_68k_rw(UINT32 offset)
{
   return (battleg_ioc_68k_rb(offset+0) << 8) |
          (battleg_ioc_68k_rb(offset+1) << 0);
}

static void battleg_ioc_68k_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x7FFF;

   switch(offset){
      case 0x401D:
         set_toaplan2_leds(data);
      break;
      default:
            print_debug("battleg_ioc_68k_wb(%02x,%02x)\n", offset, data);
      break;
   }

}

static void battleg_ioc_68k_ww(UINT32 offset, UINT16 data)
{
   battleg_ioc_68k_wb(offset+0, data >> 8);
   battleg_ioc_68k_wb(offset+1, data >> 0);
}

static void load_battleg(void)
{
   UINT8 *TMP;
   int ta,tb;

   if(!(GFX=AllocateMem(0x1000000)))return;
   if(!(TMP=AllocateMem(0x0200000)))return;

   load_tp2_gfx("rom4.bin","rom2.bin",0x200000,TMP,GFX);
   load_tp2_gfx("rom3.bin","rom1.bin",0x200000,TMP,&GFX[0x800000]);

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x40000);

   romset=14;

   if (!init_tilequeue()) return;
   RAMSize=0x34000+0x10000+0x10000;

   if(!(RAM=AllocateMem(0x080000)))return;

   /*-----[Sound Setup]-----*/

   if(!(PCMROM = AllocateMem(0x140000))) return;
   if(!load_rom("rom5.bin", PCMROM+0x040000, 0x100000)) return;
   ADPCMSetBuffers(((struct ADPCMinterface*)&battleg_m6295),PCMROM+0x00000,0x140000);
   PCMBanksize = 0x140000;

   Z80ROM = RAM+0x34000+0x10000;
   setup_garega_z80("snd.bin");

   /*-----------------------*/

   RAM_FG0 = RAM+0x20000;
   GFX_FG0 = RAM+0x34000;

   if(!load_rom("text.bin", RAM, 0x08000))return;
   tb=0;
   for(ta=0x00000;ta<0x08000;ta++){
      GFX_FG0[tb++]=(RAM[ta]&0xF0)>>4;
      GFX_FG0[tb++]=(RAM[ta]&0x0F)>>0;
   }

   memset(RAM+0x00000,0x00,0x34000);

   GFX_FG0_SOLID = make_solid_mask_8x8(GFX_FG0, 0x400);

   tp2vcu[0].VRAM     = RAM+0x11000;
   tp2vcu[0].SCROLL   = RAM+0x11000+0x8000;
   tp2vcu[0].GFX_BG   = GFX;
   tp2vcu[0].MASK_BG  = GFX_BG0_SOLID;
   tp2vcu[0].tile_max = 0x3FFFF;
   init_tp2vcu(0);

   InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);
   init_tile_cache();

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
/*
   // Fix some comm timeouts

   WriteWord68k(&ROM[0x03118],0x6000);
   WriteWord68k(&ROM[0x0313E],0x6000);
   WriteWord68k(&ROM[0x170F0],0x4E71);          // nop
   // WriteLong68k(&ROM[0x02EA0],0x4E714E71);      // nop
   // WriteLong68k(&ROM[0x02EB0],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x02EC8],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x16D2C],0x4E714E71);      // nop
*/

/*
 *  StarScream Stuff follows
 */
   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x034000);

   if (!strcmp(current_game->main_name,"bgaregc") ||
       !strcmp(current_game->main_name,"bgaregh")) { // Korean version
     // Prevents ROM test
     WriteLong(&ROM[0x15b64],0x4e714e71); // nop
     // Prevents RAM test
     WriteLong(&ROM[0x15b68],0x4e714e71); // nop

     // Prevents bad tests from looping
     WriteWord(&ROM[0x15aa0],0x4e71); // nop

     // Remove insert coin while playing
     WriteWord(&ROM[0x222a],0x4e71);

     // Speed hack
     WriteWord(&ROM[0x1f5e],0x4239);
     WriteWord(&ROM[0x1f60],0xaa);
     WriteWord(&ROM[0x1f62],0);
     WriteWord(&ROM[0x1f64],0x4e71);
   } else { // Normal version
     // Prevents ROM test
     WriteLong(&ROM[0x15acc],0x4e714e71); // nop
     // Prevents RAM test
     WriteLong(&ROM[0x15ad0],0x4e714e71); // nop

     // Fix bad checksums

     WriteWord(&ROM[0x15B24],0x6100 - 0x1E);

     /* Skip video count check (remove insert coin while playing) */
     WriteWord(&ROM[0x021FA],0x4E71);

     // Speed hack
     WriteWord(&ROM[0x1f2e],0x4239);
     WriteWord(&ROM[0x1f30],0xaa);
     WriteWord(&ROM[0x1f32],0);
     WriteWord(&ROM[0x1f34],0x4e71);
   }

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);
   AddResetHandler(&quiet_reset_handler);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x300000, 0x30000F, tp2vcu_0_rb, NULL);                  // GCU RAM (SCREEN)
   AddReadByte(0x218000, 0x21FFFF, battleg_ioc_68k_rb, NULL);           // turbo comm ram
   AddReadByte(0x600000, 0x6000ff, NULL, commram);             // sound comm
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x300000, 0x30000F, tp2vcu_0_rw, NULL);                  // GCU RAM (SCREEN)
   AddReadWord(0x218000, 0x21FFFF, battleg_ioc_68k_rw, NULL);           // turbo comm ram
   AddReadWord(0x600000, 0x6000ff, NULL, commram);             // sound comm
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x218000, 0x21FFFF, battleg_ioc_68k_wb, NULL);          // turbo comm ram
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x600000, 0x601000, sound_battleg_wb, NULL);            // sound comm
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x300000, 0x30000F, tp2vcu_0_ww, NULL);                 // GCU RAM (SCREEN)
   AddWriteWord(0x400000, 0x400FFF, NULL, RAM+0x010000);                // COLOUR RAM
   AddWriteWord(0x500000, 0x503FFF, NULL, RAM+0x020000);                // TEXT RAM (FG0 RAM)
   AddWriteWord(0x600000, 0x601000, sound_battleg_ww, NULL);            // sound comm
   AddWriteWord(0x218000, 0x21FFFF, battleg_ioc_68k_ww, NULL);          // turbo comm ram
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static const int toaplan2_interrupt[ROM_COUNT] =
{
   2,                   //  0 - Tatsujin 2
   4,                   //  1 - Snow Bros 2
   4,                   //  2 - Pipi Bibi/Whoopee (bootleg)
   4,                   //  3 - Whoopee/Pipi Bibi (original)
   4,                   //  4 - Knuckle Bash
   4,                   //  5 - Fix Eight
   4,                   //  6 - Dogyuun
   4,                   //  7 - Teki Paki
   4,                   //  8 - Ghox
   4,                   //  9 - Shippu
   4,                   // 10 - Mahou
   4,                   // 11 - Batrider
   4,                   // 12 - V Five
   4,                   // 13 - Batsugun
   4,                   // 14 - Battle Garegga
   2,                   // 15 - Fix Eight Bootleg
};

extern UINT16 z80sp;
static void execute_kbash(void)
{
   if((romset==8)){

      update_paddle();

   }

   if((romset==11)){

      cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(28,60));    // M68000 28MHz (60fps)
      cpu_interrupt(CPU_68K_0, 4);
      cpu_interrupt(CPU_68K_0, 2);

   }
   else{

     cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(28,60));    // M68000 20MHz (60fps) (real game is only 16MHz)

     cpu_interrupt(CPU_68K_0, toaplan2_interrupt[romset]);

   }

   if((romset==2)||(romset==3)){

      cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));    // Z80 4MHz (60fps)
      cpu_interrupt(CPU_Z80_0, 0x38);

   }

   if((romset==9)||(romset==10)){

     // The timers seem totally useless here, so I leave the old execs alone
     // (no need to handle timers which are never used !)
     // Notice : you must have 2 execs because of the speed hack.
     // execute_z80_audio_frame();
     // execute_z80_audio_frame();
      cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));    // Z80 4MHz (60fps)
      cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));    // Z80 4MHz (60fps)
      //cpu_interrupt(CPU_Z80_0, 0x38);
   }

   if((romset==11)){

     if(sound_nmi){
       sound_nmi = 0;
       cpu_int_nmi(CPU_Z80_0);
     }
     execute_z80_audio_frame();


   }
   if((romset==14)){
     execute_z80_audio_frame();
   }

   if (!MZ80Engine) {
     // We have a problem here. The timers must be trigered but normally
     // they depend upon the z80. I don't want to rewrite the timers now
     // to handle the 68k, so I will just simulate a fake z80 !
     // All is needed is the number of cycles...
     dwElapsedTicks += CPU_FRAME_MHz(4,60);
     triger_timers();
   }

}

static void execute_truxton2(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(20,60));    // M68000 20MHz (60fps) (real game is only 16MHz)
   cpu_interrupt(CPU_68K_0, toaplan2_interrupt[romset]);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(2,60));     // Sync

   if((romset==2)||(romset==3)){
      cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));    // Z80 4MHz (60fps)
      // cpu_interrupt(CPU_Z80_0, 0x38);
   } else {
     // We have a problem here. The timers must be trigered but normally
     // they depend upon the z80. I don't want to rewrite the timers now
     // to handle the 68k, so I will just simulate a fake z80 !
     // All is needed is the number of cycles...
     dwElapsedTicks += CPU_FRAME_MHz(4,60);
     triger_timers();
   }
}

static void DrawTileQueue(void)
{
   struct TILE_Q *tile_ptr;
   UINT32 ta,pri;

   TerminateTileQueue();

   if(romset == 11){

   for(pri=0;pri<MAX_PRI;pri++){
      tile_ptr = first_tile[pri];

#ifdef USE_CACHE
      clear_tile_cache();
#endif
      switch(pri&3){

      case 0x00:        // BG: skip blank, check solid
      case 0x01:
      case 0x02:

      while(tile_ptr->next){
         ta = tile_ptr->tile;
         ta = object_bank[ta>>15] | (ta & 0x7FFF);
         if(GFX_BG0_SOLID[ta]!=0){                      // No pixels; skip
	   if(GFX_BG0_SOLID[ta]==1)                    // Some pixels; trans
               Draw8x8_Trans_Mapped_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
            else {                                        // all pixels; solid
#ifdef USE_CACHE
	      if ((tile_cache[ta]) && (cache_map[ta] == tile_ptr->map)) {
		Move8x8_Rot(tile_cache[ta],tile_ptr->x,tile_ptr->y,NULL);
	      } else {
#endif
		Draw8x8_Mapped_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
#ifdef USE_CACHE
		add_tile_cache_Rot(NULL,tile_ptr->x,tile_ptr->y,ta);
		cache_map[ta] = tile_ptr->map;
	      }
#endif
	    }
         }
         tile_ptr = tile_ptr->next;
      }

      break;
      case 0x03:        // OBJECT: skip blank, check solid, *flipping*

      while(tile_ptr->next){
         ta = tile_ptr->tile;
         ta = object_bank[ta>>15] | (ta & 0x7FFF);
         if(GFX_BG0_SOLID[ta]!=0){                      // No pixels; skip
            if(GFX_BG0_SOLID[ta]==1)                    // Some pixels; trans
               Draw8x8_Trans_Mapped_flip_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map, tile_ptr->flip);
            else {                                       // all pixels; solid
#ifdef USE_CACHE
	      if (tile_cache[ta] && (cache_map[ta] == tile_ptr->map)) {
		Move8x8_Rot(tile_cache[ta],tile_ptr->x,tile_ptr->y,NULL);
	      } else {
#endif
		Draw8x8_Mapped_flip_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map, tile_ptr->flip);
#ifdef USE_CACHE
		add_tile_cache_Rot(NULL,tile_ptr->x,tile_ptr->y,ta);
		cache_map[ta] = tile_ptr->map;
	    }
#endif
	    }
         }
         tile_ptr = tile_ptr->next;
      }

      break;
      }

   }

   }
   else{

   for(pri=0;pri<MAX_PRI;pri++){
      tile_ptr = first_tile[pri];

#ifdef USE_CACHE
      clear_tile_cache();
#endif
      switch(pri&3){

      case 0x00:        // BG: skip blank, check solid
      case 0x01:
      case 0x02:

      while(tile_ptr->next){
         ta = tile_ptr->tile;
         if(GFX_BG0_SOLID[ta]!=0){                      // No pixels; skip
            if(GFX_BG0_SOLID[ta]==1)                    // Some pixels; trans
               Draw8x8_Trans_Mapped_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
            else {                                        // all pixels; solid
#ifdef USE_CACHE
	      if (tile_cache[ta] && cache_map[ta] == tile_ptr->map) {
		Move8x8_Rot(tile_cache[ta],tile_ptr->x,tile_ptr->y,NULL);
	      } else {
#endif
		Draw8x8_Mapped_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
#ifdef USE_CACHE
		add_tile_cache_Rot(NULL,tile_ptr->x,tile_ptr->y,ta);
		cache_map[ta] = tile_ptr->map;
	      }
#endif
	    }
         }
         tile_ptr = tile_ptr->next;
      }

      break;
      case 0x03:        // OBJECT: skip blank, check solid, *flipping*

      while(tile_ptr->next){
         ta = tile_ptr->tile;
         if(GFX_BG0_SOLID[ta]!=0){                      // No pixels; skip
            if(GFX_BG0_SOLID[ta]==1)                    // Some pixels; trans
               Draw8x8_Trans_Mapped_flip_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map, tile_ptr->flip);
            else {                                       // all pixels; solid
/* It's better NOT to use the cache for sprites, because some games are using
 * a flip effect to draw 2 halves of a big sprite -> with the cache you loose
 * the fliping effect ! */
//#ifdef USE_CACHE
//	      if (tile_cache[ta] && cache_map[ta] == tile_ptr->map) {
//		Move8x8_Rot(tile_cache[ta],tile_ptr->x,tile_ptr->y,NULL);
//	      } else {
//#endif
		Draw8x8_Mapped_flip_Rot(&GFX[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map, tile_ptr->flip);
//#ifdef USE_CACHE
//		add_tile_cache_Rot(NULL,tile_ptr->x,tile_ptr->y,ta);
//		cache_map[ta] = tile_ptr->map;
//	      }
//#endif
	    }
	 }
         tile_ptr = tile_ptr->next;
      }

      break;
      }

   }

   }

}

static const UINT16 scr_ofs[ROM_COUNT][8] =
{
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 },
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x000 },
   { 0x1F5,0x000,0x1F5,0x000,0x1F5,0x000,0x008,0x008 }, //  2 - Whoopee (bootleg)
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 },
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x000 }, //  4 - Knuckle Bash
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, //  5 - Fix Eight
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, //  6 - Dogyuun
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x000 }, //  7 - Teki Paki
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, //  8 - Ghox
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, //  9 - Shippu
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, // 10 - Mahou
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, // 11 - Batrider
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, // 12 - V Five
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, // 13 - Batsugun
   { 0x1D6,0x1EF,0x1D8,0x1EF,0x1DA,0x1EF,0x008,0x008 }, // 14 - Battle Garegga
   { 0x1f0,0x1fe,0x1ee,0x1fe,0x1ec,0x1fe,0x008,0x008 }, // 15 - Fix Eight Bootleg
};

static void DrawToaplan2(void)
{
   int x,y,ta,x_ofs,y_ofs;
   int zz,zzz,zzzz,x16,y16,i,z,loop_start,loop_end,loop_inc;
   int xx,xxx,xxxx,yyy,old_x,old_y;
   UINT8 *MAP,*RAM_BG;
   UINT32 tile_max,spr_max,pri;

   if (!GFX_FG0) {
     GFX_FG0 = gfx[0];
     GFX_FG0_SOLID = gfx_solid[0];
   }

   ClearPaletteMap();

   MAP_PALETTE_MAPPED_NEW(
      0,
      16,
      MAP
   );

   // Same problem as for the cave driver : the priorities makes clearing
   // the screen much harder, so the only way I found until now is
   // clear_game_screen
   clear_game_screen(MAP[0]);

   ClearTileQueue();

   // From mame source (why did Antiriad leave so few comments in the sources!)
/***************************************************************************

  Functions to emulate the video hardware of some Toaplan games,
  which use one or more Toaplan L7A0498 GP9001 graphic controllers.

  The simpler hardware of these games use one GP9001 controller.
  Next we have games that use two GP9001 controllers, whose priority
  schemes between the two controllers is unknown at this time, and
  may be game dependant.
  Finally we have games using one GP9001 controller and an additional
  text tile layer, which has highest priority. This text tile layer
  appears to have line-scroll support. Some of these games copy the
  text tile gfx data to RAM from the main CPU ROM, which easily allows
  for effects to be added to the tiles, by manipulating the text tile
  gfx data. The tiles are then dynamically decoded from RAM before
  displaying them.


 To Do / Unknowns
	-  Hack is needed to reset sound CPU and sound chip when machine
		is 'tilted' in Pipi & Bibis. Otherwise sound CPU interferes
		with the main CPU test of shared RAM. You get a 'Sub CPU RAM Error'
	-  What do Scroll registers 0Eh and 0Fh really do ????
	-  Snow Bros 2 sets bit 6 of the sprite X info word during weather
		world map, and bits 4, 5 and 6 of the sprite X info word during
		the Rabbit boss screen - reasons are unknown.
	-  Fourth set of scroll registers have been used for Sprite scroll
		though it may not be correct. For most parts this looks right
		except for Snow Bros 2 when in the rabbit boss screen (all sprites
		jump when big green nasty (which is the foreground layer) comes
		in from the left)
	-  Teki Paki tests video RAM from address 0 past SpriteRAM to $37ff.
		This seems to be a bug in Teki Paki's vram test routine !
	-  Batsugun, relationship between the two video controllers (priority
		wise) is wrong and unknown.
*/

   if (romset == 13) { // batsugun
     // Batsugun apparently needs to start by its 2nd gfx controler (unsure)
     tile_start = tp2vcu[0].tile_max + 1;
     loop_start = 1; loop_end = 0-1; loop_inc = -1;
   } else {
     tile_start = 0;
     loop_start = 0; loop_end = vcu_num; loop_inc = 1;
   }

   for(i = loop_start; i != loop_end; i+=loop_inc){

   // BG0
   // ---

   tile_max = tp2vcu[i].tile_max;
   if(check_layer_enabled(layer_id_data[i][0])){

   RAM_BG = tp2vcu[i].VRAM;

   MAKE_SCROLL_512x512_4_16(
      ReadWord(&tp2vcu[i].SCROLL[0])-(scr_ofs[romset][0]),
      ReadWord(&tp2vcu[i].SCROLL[2])-(scr_ofs[romset][1])
   );

   START_SCROLL_512x512_4_16(32,32,320,240);

   ta=(ReadWord(&RAM_BG[2+zz])<<2)&tile_max;

      if(ta!=0){
	pri = ReadWord(&RAM_BG[zz]);
	MAP_PALETTE_MAPPED_NEW(
			       (pri&0x7F),
         16,
         MAP
	 );

      pri = ((pri&0x0E00)>>7);

      QueueTile(ta+0, x,   y,   MAP, 0, pri);
      QueueTile(ta+1, x+8, y,   MAP, 0, pri);
      QueueTile(ta+2, x,   y+8, MAP, 0, pri);
      QueueTile(ta+3, x+8, y+8, MAP, 0, pri);

      }

   END_SCROLL_512x512_4_16();

   }

   // BG1
   // ---

   if(check_layer_enabled(layer_id_data[i][1])){

   RAM_BG = tp2vcu[i].VRAM + 0x1000;

   MAKE_SCROLL_512x512_4_16(
      ReadWord(&tp2vcu[i].SCROLL[4])-(scr_ofs[romset][2]),
      ReadWord(&tp2vcu[i].SCROLL[6])-(scr_ofs[romset][3])
   );

   START_SCROLL_512x512_4_16(32,32,320,240);

      ta=(ReadWord(&RAM_BG[2+zz])<<2)&tile_max;

      if(ta!=0){


      MAP_PALETTE_MAPPED_NEW(
         RAM_BG[zz]&0x7F,
         16,
         MAP
      );

      pri = 1+ ((ReadWord(&RAM_BG[zz])&0x0E00)>>7);

      QueueTile(ta+0, x,   y,   MAP, 0, pri);
      QueueTile(ta+1, x+8, y,   MAP, 0, pri);
      QueueTile(ta+2, x,   y+8, MAP, 0, pri);
      QueueTile(ta+3, x+8, y+8, MAP, 0, pri);

      }

   END_SCROLL_512x512_4_16();

   }

   // BG2
   // ---

   if(check_layer_enabled(layer_id_data[i][2])){

   RAM_BG = tp2vcu[i].VRAM + 0x2000;

   MAKE_SCROLL_512x512_4_16(
      ReadWord(&tp2vcu[i].SCROLL[8])-(scr_ofs[romset][4]),
      ReadWord(&tp2vcu[i].SCROLL[10])-(scr_ofs[romset][5])
   );

   START_SCROLL_512x512_4_16(32,32,320,240);

      ta=(ReadWord(&RAM_BG[2+zz])<<2)&tile_max;

      if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         RAM_BG[zz]&0x7F,
         16,
         MAP
      );

      pri = 2+ ((ReadWord(&RAM_BG[zz])&0x0E00)>>7);

      QueueTile(ta+0, x,   y,   MAP, 0, pri);
      QueueTile(ta+1, x+8, y,   MAP, 0, pri);
      QueueTile(ta+2, x,   y+8, MAP, 0, pri);
      QueueTile(ta+3, x+8, y+8, MAP, 0, pri);

      }

   END_SCROLL_512x512_4_16();

   }

   // OBJECT
   // ------

   if(check_layer_enabled(layer_id_data[i][3])){

   RAM_BG = tp2vcu[i].VRAM + 0x3000;

   x_ofs = scr_ofs[romset][6];
   y_ofs = scr_ofs[romset][7];

   /*

   hack -- pipi bibi bootleg has an odd terminator

   */

   spr_max = 0x800;

   if(romset == 2){

      for(zz = 0; zz < 0x800; zz += 8){

         if(ReadWord(&RAM_BG[zz]) == 0x0001){

            spr_max = zz;
            zz = 0x800;

         }

      }

   }

   old_x = (32-x_ofs)&0x1FF;
   old_y = (32-y_ofs)&0x1FF;

   for(zz = 0; (UINT32)zz < spr_max; zz += 8){

     if((ReadWord(&RAM_BG[zz])&0x8000)!=0){

      if((ReadWord(&RAM_BG[zz])&0x4000)==0){

         x=((ReadWord(&RAM_BG[zz+4])>>7)+32-x_ofs)&0x1FF;
         y=((ReadWord(&RAM_BG[zz+6])>>7)+32-y_ofs)&0x1FF;

      }
      else{

         x=(old_x+(ReadWord(&RAM_BG[zz+4])>>7))&0x1FF;
         y=(old_y+(ReadWord(&RAM_BG[zz+6])>>7))&0x1FF;

      }

      old_x = x;
      old_y = y;
      ta  = (ReadWord(&RAM_BG[zz]) << 16) | (ReadWord(&RAM_BG[zz+2]));
      ta &= tile_max;

      MAP_PALETTE_MAPPED_NEW(
         (ReadWord(&RAM_BG[zz])>>2)&0x3F,
         16,
         MAP
      );

      xxx=RAM_BG[zz+4]&15;
      yyy=RAM_BG[zz+6]&15;

      pri = 3+ ((ReadWord(&RAM_BG[zz])&0x0E00)>>7);

      switch((ReadWord(&RAM_BG[zz])>>12)&3){ // flip x/y
      case 0x00:
      xxxx=x;
      do{
      x=xxxx;
      xx=xxx;
      do{
         if((x>24)&&(y>24)&&(x<320+32)&&(y<240+32)){
            QueueTile(ta, x, y, MAP, 0, pri);
         }
         ta++;
         x=(x+8)&0x1FF;
      }while(xx--);
      y=(y+8)&0x1FF;
      }while(yyy--);
      break;
      case 0x01:
      x=(x-7)&0x1FF;
      xxxx=x;
      do{
      x=xxxx;
      xx=xxx;
      do{
         if((x>24)&&(y>24)&&(x<320+32)&&(y<240+32)){
            QueueTile(ta, x, y, MAP, 1, pri);
         }
         ta++;
         x=(x-8)&0x1FF;
      }while(xx--);
      y=(y+8)&0x1FF;
      }while(yyy--);
      break;
      case 0x02:
      y=(y-7)&0x1FF;
      xxxx=x;
      do{
      x=xxxx;
      xx=xxx;
      do{
         if((x>24)&&(y>24)&&(x<320+32)&&(y<240+32)){
            QueueTile(ta, x, y, MAP, 2, pri);
         }
         ta++;
         x=(x+8)&0x1FF;
      }while(xx--);
      y=(y-8)&0x1FF;
      }while(yyy--);
      break;
      case 0x03:
      x=(x-7)&0x1FF;
      y=(y-7)&0x1FF;
      xxxx=x;
      do{
      x=xxxx;
      xx=xxx;
      do{
         if((x>24)&&(y>24)&&(x<320+32)&&(y<240+32)){
            QueueTile(ta, x, y, MAP, 3, pri);
         }
         ta++;
         x=(x-8)&0x1FF;
      }while(xx--);
      y=(y-8)&0x1FF;
      }while(yyy--);
      break;
      }

     } // if (RAM_BG[zz] & 0x8000)...

   }

   }

   if (romset == 13) // batsugun
     tile_start = 0;
   else
     tile_start = tp2vcu[i].tile_max + 1;

   }

   DrawTileQueue();

   // EXTRA FG0 LAYER (Tatsujin 2, Fix Eight)

   if((romset==0)||(romset==5)||(romset==9)||(romset==10)||(romset==11)||(romset==14)||(romset==15)){

     if(check_layer_enabled(tp3vcu_layer_id_data[0])){

   zz=0;
#ifdef USE_CACHE
   clear_tile_cache();
#endif
   for(y=32;y<240+32;y+=8,zz+=48){
   for(x=32;x<320+32;x+=8,zz+=2){
      z=ReadWord(&RAM_FG0[zz])&0x3FF;
      if(GFX_FG0_SOLID[z]){

         MAP_PALETTE_MAPPED_NEW(
            (ReadWord(&RAM_FG0[zz])>>10)|0x40,
            16,
            MAP
         );

         if(GFX_FG0_SOLID[z]==1)		// Some pixels; trans
            Draw8x8_Trans_Mapped_Rot(&GFX_FG0[z<<6],x,y,MAP);
         else {					// all pixels; solid
#ifdef USE_CACHE
	    if (tile_cache[z] && cache_map[z] == MAP) {
	      Move8x8_Rot(tile_cache[z],x,y,NULL);
	    } else {
#endif
	      Draw8x8_Mapped_Rot(&GFX_FG0[z<<6],x,y,MAP);
#ifdef USE_CACHE
	      add_tile_cache_Rot(NULL,x,y,z);
	      cache_map[z] = MAP;
	    }
#endif
	 }
      }
   }
   }

   }

   }

}

/*

PIPI BIBI (C) 1991 RYOUTA KIKAKU
--------------------------------

Main CPU....68000
Sound CPUs..Z80; YM3812

Memory Map - 68000
------------------

Location      | Usage
--------------+------------
000000-03FFFF | 68000 ROM
080000-087FFF | 68000 RAM
0C0000-0C0FFF | Colour RAM
120000-120FFF | Sprite RAM
180000-180FFF | BG0 RAM
181000-181FFF | BG1 RAM
182000-182FFF | FG0 RAM
188000-18800F | Scroll RAM
190000-190011 | Sound Comm
19C000-19C0xx | Input

- Colour RAM is 15-bit bgr, 16 colours per bank, 128 banks

Sprite RAM
----------

- 8 bytes/sprite entry
- 256 sprite entries

Byte | Bit(s) | Usage
-----+76543210+---------------------
  0  |x.......| Sprite Enable
  0  |.x......| Sprite Chain
  0  |..x.....| Sprite Flip X Axis
  0  |...x....| Sprite Flip Y Axis
  0  |....xxx.| Priority
  0  |.......x| Palette (high)
  1  |xxxxxx..| Palette (low)
  1  |......xx| Tile Number (high)
  2  |xxxxxxxx| Tile Number (mid)
  3  |xxxxxxxx| Tile Number (low)
  4  |xxxxxxxx| X Position (bit 1-8)
  5  |x.......| X Position (bit 0)
  5  |....xxxx| X Chain
  6  |xxxxxxxx| Y Position (bit 1-8)
  7  |x.......| Y Position (bit 0)
  7  |....xxxx| Y Chain

BG0/1/2 RAM
-----------

Byte | Bit(s) | Usage
-----+76543210+---------------------
  0  |....xxx.| Priority
  1  |.xxxxxxx| Palette
  2  |xxxxxxxx| Tile Number (high)
  3  |xxxxxxxx| Tile Number (low)

Teki Paki: 00 02 06
Dogyuun:   00 04 0E - 00 02 04 06

Memory Map - Z80
----------------

Location  | Usage
----------+------------
0000-7FFF | Z80 ROM
8000-8000 | Sound Comm
8001-87FF | Z80 RAM
E000-E001 | YM3812


VRAM WW: 0008:0000
VRAM WW: 000c:01d6      ; BG0_X
VRAM WW: 0008:0001
VRAM WW: 000c:01ef      ; BG0_Y
VRAM WW: 0008:0002
VRAM WW: 000c:01d8      ; BG1_X
VRAM WW: 0008:0003
VRAM WW: 000c:01ef      ; BG1_Y
VRAM WW: 0008:0004
VRAM WW: 000c:01da      ; BG2_X
VRAM WW: 0008:0005
VRAM WW: 000c:01ef      ; BG2_Y
VRAM WW: 0008:0006
VRAM WW: 000c:01d4      ; ???_X
VRAM WW: 0008:0007
VRAM WW: 000c:01ef      ; ???_X
VRAM WW: 0008:000f
VRAM WW: 000c:000f      ; Screen Control

Screen Control
--------------

bit#7 = Screen Invert

*/

static struct VIDEO_INFO video_bgaregh =
{
   DrawToaplan2,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   raizing_gfxdecodeinfo
};
static struct VIDEO_INFO video_kbash =
{
   DrawToaplan2,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_batrider[] =
{
   { "armed_police_batrider_version_b", },
   { "batrider", },
   { "batrideb", },
   { NULL, },
};
GAME( batrider, "Armed Police Batrider (B)" /* "Feb 13 1998" */, RAIZING, 1998, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_batrider,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.sound = sound_batrider,
);
static struct DIR_INFO dir_batridra[] =
{
   { "armed_police_batrider", },
   { "batridra", },
   { ROMOF("batrider"), },
   { CLONEOF("batrider"), },
   { NULL, },
};
CLONE(batridra, batrider, "Armed Police Batrider (A)" /* "Dec 22 1997" */, RAIZING, 1997 /* 1998 on title screen */, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_batrider,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.sound = sound_batrider,
);
static struct DIR_INFO dir_batsugun[] =
{
   { "batsugun", },
   { NULL, },
};
GAME( batsugun, "Batsugun", TOAPLAN, 1993, GAME_SHOOT,
	.input = input_vfive,
	.dsw = dsw_batsugun,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.board = "TP030",
	.sound = sound_batsugun,
);
static struct DIR_INFO dir_bgaregc[] =
{
   { "battle_gareggc", },
   { "bgaregc", },
   { CLONEOF("battleg"), },
   { ROMOF("battleg"), },
   { NULL, },
};
CLONE(bgaregc, battleg, "Battle Garegga Chinese version" /* "Apr 2 1996" */, RAIZING, 1996, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_bgaregh,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.sound = sound_battleg,
);
static struct DIR_INFO dir_battleg[] =
{
   { "battle_garegga", },
   { "battleg", },
   { "battlega", },
   { "battlegb", },
   { "battlegc", },
   { NULL, },
};
GAME( battleg, "Battle Garegga" /* "Feb 3 1996" */, RAIZING, 1996, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_battleg,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.sound = sound_battleg,
);
static struct DIR_INFO dir_bgaregh[] =
{
   { "battle_garegga_sat_mar_2_1996", },
   { "bgaregh", },
   { CLONEOF("battleg"), },
   { ROMOF("battleg"), },
   { NULL, },
};
CLONE(bgaregh, battleg, "Battle Garegga Hong Kong Ver.", RAIZING, 1996, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_bgaregh,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.sound = sound_battleg,
);
static struct DIR_INFO dir_bbakrada[] =
{
   { "bbakrada", },
   { "battlebakraid(japan)", },
   { ROMOF("bbakraid"), },
   { CLONEOF("bbakraid"), },
   { NULL, },
};
CLONE(bbakrada, bbakraid, "Battle Bakraid normal version" /* "Apr 7 1999" */, RAIZING, 1999, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_bbakraid,
	.video = &video_bgaregh,
	.exec = execute_bbakraid,
	.long_name_jpn = "???",
	.board = "TP021",
	.sound = sound_bbakraid,
);
static struct DIR_INFO dir_bbakraid[] =
{
   { "bbakraid", },
   { "bbakradu", },
   { "bbakraid_prg", },
   { NULL, },
};
GAME( bbakraid, "Battle Bakraid unlimited version" /* "Jun 8 1999" */, RAIZING, 1999, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_bbakraid,
	.video = &video_bgaregh,
	.exec = execute_bbakraid,
	.long_name_jpn = "???",
	.board = "TP021",
	.sound = sound_bbakraid,
);
static struct DIR_INFO dir_dogyuun[] =
{
   { "dogyuun", },
   { NULL, },
};
GAME( dogyuun, "Dogyuun", TOAPLAN, 1992 /* check the "notice" screen */, GAME_SHOOT,
	.input = input_dogyuun,
	.dsw = dsw_dogyuun,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.long_name_jpn = "âhâMâàü[âô",
	.board = "TP022",
	.sound = sound_vfive,
);
static struct DIR_INFO dir_fixeight[] =
{
   { "fix_eight", },
   { "fixeight", },
   { NULL, },
};
GAME( fixeight, "Fix Eight", TOAPLAN, 1992, GAME_SHOOT | GAME_PARTIALLY_WORKING,
	.input = input_fixeight,
	.dsw = dsw_fixeight,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.board = "TP026",
	.sound = sound_vfive,
);
static struct DIR_INFO dir_fixeighb[] =
{
   { "fix_eight_bootleg", },
   { "fixeighb", },
   { "fixeightb", },
   { ROMOF("fixeight"), },
   { CLONEOF("fixeight"), },
   { NULL, },
};
CLONE(fixeighb, fixeight, "Fix Eight Bootleg", BOOTLEG, 1992, GAME_SHOOT,
	.input = input_fixeight,
	.dsw = dsw_fixeight,
	.video = &video_bgaregh,
	.exec = execute_truxton2,
	.board = "TP026",
	.sound = sound_fixeighb,
);
static struct DIR_INFO dir_ghox[] =
{
   { "ghox", },
   { NULL, },
};
GAME( ghox, "Ghox", TOAPLAN, 1991, GAME_BREAKOUT,
	.input = input_vfive,
	.dsw = dsw_ghox,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.long_name_jpn = "âSü[âNâX",
	.board = "TP021",
);
static struct DIR_INFO dir_grindstm[] =
{
   { "grind_stormer", },
   { "grindstm", },
   { ROMOF("vfive"), },
   { CLONEOF("vfive"), },
   { NULL, },
};
CLONE(grindstm, vfive, "Grind Stormer", TOAPLAN, 1992, GAME_SHOOT,
	.input = input_vfive,
	.dsw = dsw_grindstm,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.board = "TP027",
	.sound = sound_vfive,
);
static struct DIR_INFO dir_kgpe[] =
{
   { "kgpe", },
   { ROMOF("shippumd"), },
   { CLONEOF("shippumd"), },
   { NULL, },
};
CLONE(kgpe, shippumd, "Kingdom Grand Prix", RAIZING, 1994, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_kgpe,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.long_name_jpn = "Ä¾òùûéû@‘†ìÉí",
	.sound = sound_kbash,
);
static struct DIR_INFO dir_kbash[] =
{
   { "knuckle_bash", },
   { "kbash", },
   { NULL, },
};
GME( kbash, "Knuckle Bash", TOAPLAN, 1993, GAME_BEAT,
	.long_name_jpn = "âiâbâNâïâoâbâVâà",
	.board = "TP023",
);
static struct DIR_INFO dir_kbash2[] =
{
   { "knuckle_bash2", },
   { "kbash2", },
   { NULL, },
};
CLONE( kbash2, kbash, "Knuckle Bash 2 (bootleg)", TOAPLAN, 1993, GAME_BEAT,
	.input = input_kbash,
	.dsw = dsw_kbash2,
	.video = &video_kbash,
	.exec = execute_kbash,
	.long_name_jpn = "âiâbâNâïâoâbâVâà",
	.board = "TP023",
	.sound = sound_kbash2,
);
static struct DIR_INFO dir_mahoudai[] =
{
   { "mahou_daisakusen", },
   { "mahoudai", },
   { NULL, },
};
GAME( mahoudai, "Mahou Daisakusen", RAIZING, 1993, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_mahoudai,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.long_name_jpn = "ûéû@‘†ìÉí",
	.sound = sound_kbash,
);
static struct DIR_INFO dir_pipibibi[] =
{
   { "pipi_and_bibi", },
   { "pipibibi", },
   { ROMOF("whoopee"), },
   { CLONEOF("whoopee"), },
   { NULL, },
};
GAME(pipibibi, "Pipi and Bibi's", BOOTLEG, 1991, GAME_PLATFORM | GAME_ADULT,
	.input = input_pipibibi,
	.dsw = dsw_pipibibi,
	.video = &video_kbash,
	.exec = execute_kbash,
	.long_name_jpn = "âtü[ârü[ (bootleg)",
	.sound = sound_whoopee,
);
static struct DIR_INFO dir_shippumd[] =
{
   { "shippu_mahou_daisakusen", },
   { "shippumd", },
   { NULL, },
};
GAME( shippumd, "Shippu Mahou Daisakusen", RAIZING, 1994, GAME_SHOOT,
	.input = input_bgaregh,
	.dsw = dsw_shippumd,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.long_name_jpn = "Ä¾òùûéû@‘†ìÉí",
	.sound = sound_kbash,
);
static struct DIR_INFO dir_snowbro2[] =
{
   { "snow_bros_2", },
   { "snowbro2", },
   { NULL, },
};
GAME( snowbro2, "Snow Bros 2", TOAPLAN, 1994, GAME_PLATFORM,
	.input = input_snowbro2,
	.dsw = dsw_snowbro2,
	.video = &video_kbash,
	.exec = execute_kbash,
	.long_name_jpn = "âXâmü[âuâëâUü[âYéQ",
	.sound = sound_truxton2,
);
static struct DIR_INFO dir_truxton2[] =
{
   { "tatsujin_2", },
   { "tatsujn2", },
   { "truxton2", },
   { NULL, },
};
GAME( truxton2, "Tatsujin 2", TOAPLAN, 1992, GAME_SHOOT,
	.input = input_truxton2,
	.dsw = dsw_truxton2,
	.video = &video_bgaregh,
	.exec = execute_truxton2,
	.long_name_jpn = "ÆBÉlë¤",
	.board = "TP024",
	.sound = sound_truxton2,
);
static struct DIR_INFO dir_tekipaki[] =
{
   { "teki_paki", },
   { "tekipaki", },
   { NULL, },
};
GAME( tekipaki, "Teki Paki", TOAPLAN, 1991, GAME_PUZZLE,
	.input = input_tekipaki,
	.dsw = dsw_tekipaki,
	.video = &video_kbash,
	.exec = execute_kbash,
	.long_name_jpn = "É“”]âQü[âÇü@âeâLâpâL",
	.board = "TP020",
);
static struct DIR_INFO dir_vfive[] =
{
   { "v_five", },
   { "vfive", },
   { ROMOF("dogyuun"), },
   { CLONEOF("dogyuun"), },
   { NULL, },
};
GAME(vfive, "V Five", TOAPLAN, 1993, GAME_SHOOT,
	.input = input_vfive,
	.dsw = dsw_vfive,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.board = "TP027",
	.sound = sound_vfive,
);
static struct DIR_INFO dir_whoopee[] =
{
   { "whoopee", },
   { "pipibibs", },
   { NULL, },
};
GAME( whoopee, "Whoopee", TOAPLAN, 1991, GAME_PLATFORM | GAME_ADULT,
	.input = input_tekipaki,
	.dsw = dsw_whoopee,
	.video = &video_kbash,
	.exec = execute_kbash,
	.long_name_jpn = "âtü[ârü[",
	.sound = sound_whoopee,
);

CLONEI(sstriker, mahoudai, "Sorcer Striker (World)", TOAPLAN, 1993, GAME_SHOOT,
	.dsw = sstriker_dsw,
	.input = input_bgaregh,
	.video = &video_bgaregh,
	.exec = execute_kbash,
	.sound = sound_kbash
	);
