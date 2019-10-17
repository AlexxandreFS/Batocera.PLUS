#define DRV_DEF_INPUT input_outzone
#define DRV_DEF_SOUND sound_tp1
/******************************************************************************/
/*                                                                            */
/*                          TOAPLAN 68000 SYSTEM#1                            */
/*                          ----------------------                            */
/*   CPU: 68000 Z80 <PROTECTED>                                               */
/* SOUND: YM3812                                                              */
/* VIDEO: 320x240 TOAPLAN CUSTOM <4xBG0 1xSPR>                                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "3812intf.h"
#include "sasound.h"		// sample support routines
#include "blit.h" // clear_game_screen
#include "timer.h"
#include "profile.h" // fps

static struct INPUT_INFO input_outzone[] =
{
   INP1( COIN1, 0x023003, 0x08 ),
   INP1( COIN2, 0x023003, 0x10 ),
   INP1( TILT, 0x023003, 0x02 ),
   INP1( SERVICE, 0x023003, 0x01 ),

   INP1( P1_START, 0x023003, 0x20 ),
   INP1( P1_UP, 0x023004, 0x01 ),
   INP1( P1_DOWN, 0x023004, 0x02 ),
   INP1( P1_LEFT, 0x023004, 0x04 ),
   INP1( P1_RIGHT, 0x023004, 0x08 ),
   INP1( P1_B1, 0x023004, 0x10 ),
   INP1( P1_B2, 0x023004, 0x20 ),

   INP1( P2_START, 0x023003, 0x40 ),
   INP1( P2_UP, 0x023005, 0x01 ),
   INP1( P2_DOWN, 0x023005, 0x02 ),
   INP1( P2_LEFT, 0x023005, 0x04 ),
   INP1( P2_RIGHT, 0x023005, 0x08 ),
   INP1( P2_B1, 0x023005, 0x10 ),
   INP1( P2_B2, 0x023005, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_rally_bike_0[] =
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

static struct DSW_DATA dsw_data_rally_bike_1[] =
{
   { MSG_DIFFICULTY,          0x00, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { _("Unknown"),               0x04, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x04},
   { _("Unknown"),               0x04, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x04},
   { _("Territory/Copyright"),   0x20, 0x04 },
   { _("World/Taito Corp Japan"),0x20},
   { _("USA/Taito America"),     0x10},
   { _("Japan/Taito Corp"),      0x00},
   { _("USA/Taito America (Romstar)"), 0x30},
   { _("Dipsw display"),         0x00, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Continue"),              0x80, 0x02 },
   { MSG_ON,                  0x00},
   { MSG_OFF,                 0x80},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_hellfire_0[] =
{
   DSW_UNUSED( 0x01, 0x00),
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

static struct DSW_DATA dsw_data_truxton_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { _("Extra Life"),            0x00, 0x04 },
   { _("50K, every 150K"),       0x04, 0x00 },
   { _("70K, every 200K")},
   { _("100k only"),             0x08},
   { _("none"),                  0x0C},
   { _("Lives"),                 0x00, 0x04 },
   { "2",                     0x30},
   { "3",                     0x00},
   { "4",                     0x20},
   { "5",                     0x10},
   { _("Dipsw display"),         0x00, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { _("Continue"),              0x80, 0x02 },
   { MSG_ON,                  0x00},
   { MSG_OFF,                 0x80},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_hellfire_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { _("Extra Life"),            0x00, 0x04 },
   { _("70K, every 200K")},
   { _("50K, every 250K"),       0x04, 0x00 },
   { _("100k only"),             0x08},
   { _("200k only"),             0x0C},
   { _("Lives"),                 0x00, 0x04 },
   { "2",                     0x30},
   { "3",                     0x00},
   { "4",                     0x20},
   { "5",                     0x10},
   { _("Invulnerability"),       0x00, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_fire_shark_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x00},
   { MSG_EASY,                0x01},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x03},
   { _("Extra Life"),            0x00, 0x04 },
   { _("70K, every 150K")},
   { _("50K, every 200K"),       0x04, 0x00 },
   { _("100k only"),             0x08},
   { _("None"),                  0x0C},
   { _("Lives"),                 0x00, 0x04 },
   { "2",                     0x30},
   { "3",                     0x00},
   { "4",                     0x20},
   { "5",                     0x10},
   { _("Invulnerability"),       0x00, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_vimana_1[] =
{
  { MSG_DIFFICULTY, 0x03, 4 },
  { _("Easy") , 0x01},
  { _("Medium") , 0x00},
  { _("Hard") , 0x02},
  { _("Hardest") , 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("70K and 200K") , 0x00},
  { _("100K and 250K") , 0x04},
  { _("100K") , 0x08},
  { _("200K") , 0x0c},
  { MSG_LIVES, 0x30, 4 },
  { "2" , 0x30},
  { "3" , 0x00},
  { "4" , 0x20},
  { "5" , 0x10},
  { _("Invulnerability"),    0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  { _("Allow Continue"), 0x80, 2 },
  { MSG_NO, 0x80},
  { MSG_YES, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_vimana_2[] =
{
  { _("Territory"), 0x0f, 16 },
  { _("Europe") , 0x02},
  { _("US") , 0x01},
  { _("Japan") , 0x00},
  { _("Hong Kong") , 0x03},
  { _("Korea") , 0x04},
  { _("Taiwan") , 0x05},
  { _("Taiwan") , 0x06},
  { _("US") , 0x07},
  { _("Hong Kong") , 0x08},
  { MSG_UNUSED, 0x09},
  { MSG_UNUSED, 0x0a},
  { MSG_UNUSED, 0x0b},
  { MSG_UNUSED, 0x0c},
  { MSG_UNUSED, 0x0d},
  { MSG_UNUSED, 0x0e},
  { _("Japan") , 0x0f},
  { NULL, 0}
};

static struct DSW_INFO dsw_vimana[] =
{
   { 0, 0x00, dsw_data_hellfire_0 },
   { 1, 0x00, dsw_data_vimana_1 },
   { 2, 0x02, dsw_data_vimana_2 },
   { 0,        0,    NULL,      },
};

static gfx_layout tilelayout =
{
        8,8,            /* 8x8 */
        RGN_FRAC(1,2),  /* 16384/32768 tiles */
        4,              /* 4 bits per pixel */
        { RGN_FRAC(1,2)+8, RGN_FRAC(1,2), 8, 0 },
        { 0, 1, 2, 3, 4, 5, 6, 7 },
        { 0, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
        16*8            /* every tile takes 16 consecutive bytes */
};

static gfx_layout rallybik_spr_layout =
{
	16,16,	/* 16*16 sprites */
	2048,	/* 2048 sprites */
	4,		/* 4 bits per pixel */
	{ 0*2048*32*8, 1*2048*32*8, 2*2048*32*8, 3*2048*32*8 },
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16,
			8*16, 9*16, 10*16, 11*16, 12*16, 13*16, 14*16, 15*16 },
	32*8	/* every sprite takes 32 consecutive bytes */
};

static struct GFX_LIST toaplan1_gfx[] =
{
   { REGION_GFX1, &tilelayout, },
   { REGION_GFX2, &tilelayout, },
   { 0,           NULL,        },
};

static struct GFX_LIST rally_bike_gfx[] =
{
   { REGION_GFX1, &tilelayout,           },
   { REGION_GFX2, &rallybik_spr_layout,  },
   { 0,           NULL,                  },
};

static struct YM3812interface ym3812_interface =
{
   1,              // 1 chip
   3500000,        // 3.5 MHz
   { 255 },        // volume
   { z80_irq_handler }
};

static struct SOUND_INFO sound_tp1[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { 0,             NULL,                 },
};

static struct ROM_INFO rom_vimana[] =         /* From board serial number 1547.04 (July '94) */
{
  { "tp019-7a.bin", 0x20000, 0x5a4bf73e, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "tp019-8a.bin", 0x20000, 0x03ba27e8, REGION_CPU1, 0x000001, LOAD_8_16 },
	/* sound CPU is a HD647180 (Z180) with internal ROM */
  { "hd647180.019", 0x08000, 0x41a97ebe, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "vim6.bin", 0x20000, 0x2886878d, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "vim5.bin", 0x20000, 0x61a63d7a, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "vim4.bin", 0x20000, 0xb0515768, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "vim3.bin", 0x20000, 0x0b539131, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "vim1.bin", 0x80000, 0xcdde26cd, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "vim2.bin", 0x80000, 0x1dbfc118, REGION_GFX2, 0x80000, LOAD_NORMAL },
  { "tp019-09.bpr", 0x20, 0xbc88cced, REGION_PROMS, 0x00, LOAD_NORMAL },
  { "tp019-10.bpr", 0x20, 0xa1e17492, REGION_PROMS, 0x20, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_vimanaj[] = // clone of vimana
{
  { "vim07.bin", 0x20000, 0x1efaea84, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "vim08.bin", 0x20000, 0xe45b7def, REGION_CPU1, 0x000001, LOAD_8_16 },
	/* sound CPU is a HD647180 (Z180) with internal ROM */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_outzone[] =
{
  { "prg2.bin", 0x20000, 0x9704db16, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "prg1.bin", 0x20000, 0x127a38d7, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "rom9.bin", 0x8000, 0x73d8e235, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "rom5.bin", 0x80000, 0xc64ec7b6, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "rom6.bin", 0x80000, 0x64b6c5ac, REGION_GFX1, 0x80000, LOAD_NORMAL },
  { "rom2.bin", 0x20000, 0x6bb72d16, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "rom1.bin", 0x20000, 0x0934782d, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "rom3.bin", 0x20000, 0xec903c07, REGION_GFX2, 0x40000, LOAD_8_16 },
  { "rom4.bin", 0x20000, 0x50cbf1a8, REGION_GFX2, 0x40001, LOAD_8_16 },
//  { "tp018_10.bpr", 0x20, 0xbc88cced, REGION_PROMS, 0x00, LOAD_NORMAL },
//  { "tp018_11.bpr", 0x20, 0xa1e17492, REGION_PROMS, 0x20, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_outzoneh[] = // clone of outzone
{
  { "tp018_7.bin", 0x20000, 0x0c2ac02d, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "tp018_8.bin", 0x20000, 0xca7e48aa, REGION_CPU1, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_outzonec[] =                   /* From board serial number 2122 clone of outzone */
{
  { "rom7.bin", 0x20000, 0x936e25d8, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "rom8.bin", 0x20000, 0xd19b3ecf, REGION_CPU1, 0x000001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_outzone_1[] =
{
  { MSG_DIFFICULTY, 0x03, 4 },
  { _("Easy") , 0x01},
  { _("Medium") , 0x00},
  { _("Hard") , 0x02},
  { _("Hardest") , 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("Every 300K") , 0x00},
  { _("200K and 500K") , 0x04},
  { _("300K only") , 0x08},
  { _("None") , 0x0c},
  { MSG_LIVES, 0x30, 4 },
  { "1" , 0x30},
  { "2" , 0x20},
  { "3" , 0x00},
  { "5" , 0x10},
  { _("Invulnerability"), 0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  DSW_UNUSED( 0x80, 0x00),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_outzone_2[] =
{
  { _("Territory"), 0x07, 6 },
  { _("Europe") , 0x02},
  { _("US") , 0x01},
  { _("Japan") , 0x00},
  { _("Hong Kong") , 0x03},
  { _("Korea") , 0x04},
  { _("Taiwan") , 0x05},
  { MSG_UNKNOWN, 0x08, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x08},
  { NULL, 0}
};

static struct DSW_INFO dsw_outzone[] =
{
   { 0, 0x00, dsw_data_hellfire_0 },
   { 1, 0x00, dsw_data_outzone_1 },
   { 2, 0x02, dsw_data_outzone_2 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_rallybik[] =
{
  { "b45-02.rom", 0x08000, 0x383386d7, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "b45-01.rom", 0x08000, 0x7602f6a7, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "b45-04.rom", 0x20000, 0xe9b005b1, REGION_CPU1, 0x040000, LOAD_8_16 },
  { "b45-03.rom", 0x20000, 0x555344ce, REGION_CPU1, 0x040001, LOAD_8_16 },
  { "b45-05.rom", 0x4000, 0x10814601, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "b45-09.bin", 0x20000, 0x1dc7b010, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "b45-08.bin", 0x20000, 0xfab661ba, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "b45-07.bin", 0x20000, 0xcd3748b4, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "b45-06.bin", 0x20000, 0x144b085c, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "b45-11.rom", 0x10000, 0x0d56e8bb, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "b45-10.rom", 0x10000, 0xdbb7c57e, REGION_GFX2, 0x10000, LOAD_NORMAL },
  { "b45-12.rom", 0x10000, 0xcf5aae4e, REGION_GFX2, 0x20000, LOAD_NORMAL },
  { "b45-13.rom", 0x10000, 0x1683b07c, REGION_GFX2, 0x30000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_rally_bike_2[] =
{
   { _("Language"),              0x0F, 0x10 },
   { "0",                     0x00},
   { "1",                     0x01},
   { "2",                     0x02},
   { "3",                     0x03},
   { "4",                     0x04},
   { "5",                     0x05},
   { "6",                     0x06},
   { "7",                     0x07},
   { "8",                     0x08},
   { "9",                     0x09},
   { _("A"),                     0x0A},
   { _("B"),                     0x0B},
   { _("C"),                     0x0C},
   { _("D"),                     0x0D},
   { _("E"),                     0x0E},
   { _("F"),                     0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_rallybik[] =
{
   { 0, 0x00, dsw_data_rally_bike_0 },
   { 1, 0x00, dsw_data_rally_bike_1 },
   { 2, 0x00, dsw_data_rally_bike_2 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_zerowing[] = /* 2 player simultaneous version */
{
  { "o15-11ii.bin", 0x08000, 0xe697ecb9, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "o15-12ii.bin", 0x08000, 0xb29ee3ad, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "o15-09.rom", 0x20000, 0x13764e95, REGION_CPU1, 0x040000, LOAD_8_16 },
  { "o15-10.rom", 0x20000, 0x351ba71a, REGION_CPU1, 0x040001, LOAD_8_16 },
  { "o15-13.rom", 0x8000, 0xe7b72383, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "o15-05.rom", 0x20000, 0x4e5dd246, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "o15-06.rom", 0x20000, 0xc8c6d428, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "o15-07.rom", 0x20000, 0xefc40e99, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "o15-08.rom", 0x20000, 0x1b019eab, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "o15-03.rom", 0x20000, 0x7f245fd3, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "o15-04.rom", 0x20000, 0x0b1a1289, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "o15-01.rom", 0x20000, 0x70570e43, REGION_GFX2, 0x40000, LOAD_8_16 },
  { "o15-02.rom", 0x20000, 0x724b487f, REGION_GFX2, 0x40001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_zerowing_1[] =
{
  { MSG_DIFFICULTY, 0x03, 4 },
  { _("Easy") , 0x01},
  { _("Medium") , 0x00},
  { _("Hard") , 0x02},
  { _("Hardest") , 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("200Kevery 500K") , 0x00},
  { _("500Kevery 1M") , 0x04},
  { _("500K") , 0x08},
  { _("None") , 0x0c},
  { MSG_LIVES, 0x30, 4 },
  { "2" , 0x30},
  { "3" , 0x00},
  { "4" , 0x20},
  { "5" , 0x10},
  { _("Invulnerability"),    0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  { _("Allow Continue"), 0x80, 2 },
  { MSG_NO, 0x80},
  { MSG_YES, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_zerowing_2[] =
{
  { _("Territory"), 0x03, 4 },
  { _("Europe") , 0x02},
  { _("Europe") , 0x03},
  { _("US") , 0x01},
  { _("Japan") , 0x00},
  DSW_UNUSED( 0x04, 0x00),
  DSW_UNUSED( 0x08, 0x00),
  { NULL, 0}
};

static struct DSW_INFO dsw_zerowing[] =
{
   { 0, 0x01, dsw_data_rally_bike_0 },
   { 1, 0x00, dsw_data_zerowing_1 },
   { 2, 0x02, dsw_data_zerowing_2 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_demonwld[] =
{
  { "o16-10.v2", 0x20000, 0xca8194f3, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "o16-09.v2", 0x20000, 0x7baea7ba, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "rom11.v2", 0x8000, 0xdbe08c85, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "rom05", 0x20000, 0x6506c982, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "rom07", 0x20000, 0xa3a0d993, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "rom06", 0x20000, 0x4fc5e5f3, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "rom08", 0x20000, 0xeb53ab09, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "rom01", 0x20000, 0x1b3724e9, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "rom02", 0x20000, 0x7b20a44d, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "rom03", 0x20000, 0x2cacdcd0, REGION_GFX2, 0x40000, LOAD_8_16 },
  { "rom04", 0x20000, 0x76fd3201, REGION_GFX2, 0x40001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_demonwld2[] = // clone of demonwld
{
  { "o16-10.rom", 0x20000, 0x036ee46c, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "o16-09.rom", 0x20000, 0xbed746e3, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "rom11", 0x8000, 0x397eca1b, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_demonwld_1[] =
{
  { MSG_DIFFICULTY, 0x03, 4 },
  { _("Easy") , 0x01},
  { _("Medium") , 0x00},
  { _("Hard") , 0x02},
  { _("Hardest") , 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("30Kevery 100K") , 0x00},
  { _("50K and 100K") , 0x04},
  { _("100k only") , 0x08},
  { _("None") , 0x0c},
  { MSG_LIVES, 0x30, 4 },
  { "1" , 0x30},
  { "2" , 0x20},
  { "3" , 0x00},
  { "5" , 0x10},
  { _("Invulnerability"),    0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  DSW_UNUSED( 0x80, 0x00),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_demonwld_2[] =
{
  { _("Territory/Copyright"), 0x01, 2 },
  { _("Toaplan") , 0x01},
  { _("Japan/Taito Corp") , 0x00},
  { MSG_UNKNOWN, 0x02, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x02},
  { MSG_UNKNOWN, 0x04, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x04},
  { MSG_UNKNOWN, 0x08, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x08},
  { NULL, 0}
};

static struct DSW_INFO dsw_demonwld[] =
{
   { 0, 0x00, dsw_data_hellfire_0 },
   { 1, 0x00, dsw_data_demonwld_1 },
   { 2, 0x01, dsw_data_demonwld_2 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_samesame[] = // clone of fireshrk
{
  { "o17_09.8j", 0x08000, 0x3f69e437, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "o17_10.8l", 0x08000, 0x4e723e0a, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "o17_11.7j", 0x20000, 0xbe07d101, REGION_CPU1, 0x040000, LOAD_8_16 },
  { "o17_12.7l", 0x20000, 0xef698811, REGION_CPU1, 0x040001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_fireshrk[] =
{
  { "09.8j", 0x08000, 0xf0c70e6f, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "10.8l", 0x08000, 0x9d253d77, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "o17_11ii.7j", 0x20000, 0x6beac378, REGION_CPU1, 0x040000, LOAD_8_16 },
  { "o17_12ii.7l", 0x20000, 0x6adb6eb5, REGION_CPU1, 0x040001, LOAD_8_16 },
  { "hd647180.017", 0x08000, 0x43523032, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "o17_05.12j", 0x20000, 0x565315f8, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "o17_06.13j", 0x20000, 0x95262d4c, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "o17_07.12l", 0x20000, 0x4c4b735c, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "o17_08.13l", 0x20000, 0x95c6586c, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "o17_01.1d", 0x20000, 0xea12e491, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "o17_02.3d", 0x20000, 0x32a13a9f, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "o17_03.5d", 0x20000, 0x68723dc9, REGION_GFX2, 0x40000, LOAD_8_16 },
  { "o17_04.7d", 0x20000, 0xfe0ecb13, REGION_GFX2, 0x40001, LOAD_8_16 },
//  { "prom14.25b", 0x20, 0xbc88cced, REGION_PROMS, 0x00, LOAD_NORMAL },
//  { "prom15.20c", 0x20, 0xa1e17492, REGION_PROMS, 0x20, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_fire_shark_2[] =
{
   { _("Language"),              0x0F, 0x10 },
   { "0",                     0x00},
   { "1",                     0x01},
   { "2",                     0x02},
   { "3",                     0x03},
   { "4",                     0x04},
   { "5",                     0x05},
   { "6",                     0x06},
   { "7",                     0x07},
   { "8",                     0x08},
   { "9",                     0x09},
   { _("A"),                     0x0A},
   { _("B"),                     0x0B},
   { _("C"),                     0x0C},
   { _("D"),                     0x0D},
   { _("E"),                     0x0E},
   { _("F"),                     0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_fireshrk[] =
{
   { 0, 0x00, dsw_data_hellfire_0 },
   { 1, 0x00, dsw_data_fire_shark_1 },
   { 2, 0x00, dsw_data_fire_shark_2 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_samesame_1[] =
{
  { MSG_DIFFICULTY, 0x03, 4 },
  { _("Easy") , 0x01},
  { _("Medium") , 0x00},
  { _("Hard") , 0x02},
  { _("Hardest") , 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { _("50Kevery 150K") , 0x04},
  { _("70Kevery 200K") , 0x00},
  { _("100K") , 0x08},
  { _("None") , 0x0c},
  { MSG_LIVES, 0x30, 4 },
  { "2" , 0x30},
  { "3" , 0x00},
  { "4" , 0x20},
  { "5" , 0x10},
  { _("Invulnerability"),    0x40, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x40},
  { _("Allow Continue"), 0x80, 2 },
  { MSG_NO, 0x80},
  { MSG_YES, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_same_same_same_2[] =
{
   { _("Language"),              0x0F, 0x10 },
   { "0",                     0x00},
   { "1",                     0x01},
   { "2",                     0x02},
   { "3",                     0x03},
   { "4",                     0x04},
   { "5",                     0x05},
   { "6",                     0x06},
   { "7",                     0x07},
   { "8",                     0x08},
   { "9",                     0x09},
   { _("A"),                     0x0A},
   { _("B"),                     0x0B},
   { _("C"),                     0x0C},
   { _("D"),                     0x0D},
   { _("E"),                     0x0E},
   { _("F"),                     0x0F},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_samesame[] =
{
   { 0, 0x00, dsw_data_rally_bike_0 },
   { 1, 0x00, dsw_data_samesame_1 },
   { 2, 0xf0, dsw_data_same_same_same_2 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_hellfire[] =
{
  { "b90_14.0", 0x20000, 0x101df9f5, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "b90_15.1", 0x20000, 0xe67fd452, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "b90_03.2", 0x8000, 0x4058fa67, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "b90_04.3", 0x20000, 0xea6150fc, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "b90_05.4", 0x20000, 0xbb52c507, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "b90_06.5", 0x20000, 0xcf5b0252, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "b90_07.6", 0x20000, 0xb98af263, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "b90_11.10", 0x20000, 0xc33e543c, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "b90_10.9", 0x20000, 0x35fd1092, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "b90_09.8", 0x20000, 0xcf01009e, REGION_GFX2, 0x40000, LOAD_8_16 },
  { "b90_08.7", 0x20000, 0x3404a5e3, REGION_GFX2, 0x40001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_hell_fire_2[] =
{
   { _("Territory"),   0x03, 3 },
   { _("Europe") , 0x02},
   { _("US") , 0x01},
   { _("Japan") , 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_hellfire[] =
{
   { 0, 0x00, dsw_data_hellfire_0 },
   { 1, 0x00, dsw_data_hellfire_1 },
   { 2, 0x02, dsw_data_hell_fire_2 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_truxton[] =
{
  { "b65_11.bin", 0x20000, 0x1a62379a, REGION_CPU1, 0x000000, LOAD_8_16 },
  { "b65_10.bin", 0x20000, 0xaff5195d, REGION_CPU1, 0x000001, LOAD_8_16 },
  { "b65_09.bin", 0x4000, 0x1bdd4ddc, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "b65_08.bin", 0x20000, 0xd2315b37, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "b65_07.bin", 0x20000, 0xfb83252a, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "b65_06.bin", 0x20000, 0x36cedcbe, REGION_GFX1, 0x40000, LOAD_8_16 },
  { "b65_05.bin", 0x20000, 0x81cd95f1, REGION_GFX1, 0x40001, LOAD_8_16 },
  { "b65_04.bin", 0x20000, 0x8c6ff461, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "b65_03.bin", 0x20000, 0x58b1350b, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "b65_02.bin", 0x20000, 0x1dd55161, REGION_GFX2, 0x40000, LOAD_8_16 },
  { "b65_01.bin", 0x20000, 0xe974937f, REGION_GFX2, 0x40001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_truxton_2[] =
{
  { _("Territory"), 0x07, 6 },
  { _("Europe") , 0x02},
  { _("US") , 0x05},
  { _("USA Romstar License") , 0x01},
  { _("Japan") , 0x00},
  // higher bits unused
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_truxton[] =
{
   { 3, 0x00, dsw_data_rally_bike_0 },
   { 4, 0x00, dsw_data_truxton_1 },
   { 5, 0x02, dsw_data_truxton_2 },
   { 0,        0,    NULL,      },
};


// Store Tiles in priority lists (good idea from Shark!).

#define MAX_PRI         32              // 32 levels of priority
#define MAX_TILES       0x8000          // 0x4000*0x14=0x60000

static struct TILE_Q
{
   UINT32 tile;                          // Tile number
   UINT32 x,y;                           // X,Y position
   UINT8 *map;                          // Colour map data
   struct TILE_Q *next;                 // Next item with equal priority
} TILE_Q;

static struct TILE_Q *TileQueue;               // full list
static struct TILE_Q *last_tile;               // last tile in use
static struct TILE_Q *prilist[MAX_PRI];        // start node for each priority list

#define ROM_COUNT       10

/*

 Supported romsets:

  0 - Vimana              - 1991 - TOAPLAN
  1 - Vimana alt set      - 1991 - TOAPLAN
  2 - Outzone             - 1990 - TOAPLAN
  3 - Rally Bike          - 1988 - TOAPLAN
  4 - Zero Wing           - 1990 - TOAPLAN
  5 - Demon's World       - 1990 - TOAPLAN
  6 - Fire Shark          - 19.. - TOAPLAN
  7 - Same Same Same      - 19.. - TOAPLAN
  8 - Hell Fire           - 19.. - TOAPLAN
  9 - Truxton             - 1988 - TOAPLAN

 Todo:

 - Lots

Vimana:

 - Sound Z80 is not dumped

Rally Bike:

 - Object ram is directly accessed (no port) bootleg?

Fire Shark:

 - Sound Z80 is not dumped

Same Same Same:

 - Sound Z80 is not dumped

*/

static int romset;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

/******************************************************************************/
/*  VCU CHIP                                                                  */
/******************************************************************************/

typedef struct TP1VCU				// information about 1 chip
{
   UINT8 *VRAM;					// layer ram (0x10000 bytes)
   UINT8 *RAM_OBJ;				// object ram (0x800 + 0x80 bytes)
   UINT8 *SCROLL;				// scroll ram (0x10 bytes)
   UINT32 obj_pos;				// current offset in object ram
   UINT32 bg_pos;				// current offset in layer ram
   UINT32 scroll_pos;				// current offset in SCROLL
   UINT32 status;				// some status read
   UINT8 *GFX_BG;				// GFX data
   UINT8 *MASK_BG;				// MASK data
   UINT32 tile_mask_bg;				// tile count
   UINT32 tile_mask_obj;				// tile count
   UINT32 tile_ofs_obj;				// tile offset
} TP1VCU;

static struct TP1VCU tp1vcu[1];			// max 1 chips

static void init_tp1vcu(UINT32 num)
{
   tp1vcu[num].obj_pos    = 0x0000;
   tp1vcu[num].bg_pos     = 0x0000;
   tp1vcu[num].scroll_pos = 0x0000;
   tp1vcu[num].status     = 0x0000;
}

static void tp1vcu_obj_ww(UINT32 offset, UINT16 data)
{
   switch(offset&0x0E){
      case 0x02:                        // Port Address
         tp1vcu[0].obj_pos = (data<<1) & 0x7FE;
      break;
      case 0x04:                        // Port Data
         WriteWord(&tp1vcu[0].RAM_OBJ[tp1vcu[0].obj_pos], data);
         tp1vcu[0].obj_pos += 0x002;
         tp1vcu[0].obj_pos &= 0x7FE;
      break;
      case 0x06:                        // Port Data
         WriteWord(&tp1vcu[0].RAM_OBJ[tp1vcu[0].obj_pos+0x800], data);
         tp1vcu[0].obj_pos += 0x002;
         tp1vcu[0].obj_pos &= 0x7FE;
      break;
      default:
         print_debug("tp1vcu[0] ww(%04x,%04x)\n", offset&0x0E, data);
      break;
   }
}

static UINT16 tp1vcu_obj_rw(UINT32 offset)
{
   UINT16 ret;

   switch(offset&0x0E){
      case 0x00:                        // Status
         ret = tp1vcu[0].status;
         tp1vcu[0].status ^= 1;
      break;
      case 0x04:                        // Port Data
         ret = ReadWord(&tp1vcu[0].RAM_OBJ[tp1vcu[0].obj_pos]);
         tp1vcu[0].obj_pos += 0x002;
         tp1vcu[0].obj_pos &= 0x7FE;
      break;
      case 0x06:                        // Port Data
         ret = ReadWord(&tp1vcu[0].RAM_OBJ[tp1vcu[0].obj_pos+0x800]);
         tp1vcu[0].obj_pos += 0x002;
         tp1vcu[0].obj_pos &= 0x7FE;
      break;
      default:
         ret = 0x0000;
         print_debug("tp1vcu[0] rw(%04x)\n", offset&0x0E);
      break;
   }

   return ret;
}

static UINT8 tp1vcu_obj_rb(UINT32 offset)
{
   UINT16 ret;
   ret = tp1vcu_obj_rw(offset);

   if((offset&1)==0)
      return (UINT8) ((ret>>8)&0xFF);
   else
      return (UINT8) ((ret>>0)&0xFF);
}

static UINT16 tp1_flipscreen;

static void tp1vcu_bg_ww(UINT32 offset, UINT16 data)
{
   switch(offset&0x1E){
   case 0:
     tp1_flipscreen = data;
     break;
   case 0x02:                        // Port Address
     tp1vcu[0].bg_pos = (data<<2) & 0xFFFE;
     break;
   case 0x04:                        // Port Data
     WriteWord(&tp1vcu[0].VRAM[tp1vcu[0].bg_pos], data);
     break;
   case 0x06:                        // Port Data
     WriteWord(&tp1vcu[0].VRAM[tp1vcu[0].bg_pos+2], data);
     tp1vcu[0].bg_pos += 0x0002;
     tp1vcu[0].bg_pos &= 0xFFFE;
     break;
   case 0x10:                        // Scroll
   case 0x12:                        // Scroll
   case 0x14:                        // Scroll
   case 0x16:                        // Scroll
   case 0x18:                        // Scroll
   case 0x1A:                        // Scroll
   case 0x1C:                        // Scroll
   case 0x1E:                        // Scroll
     WriteWord(&tp1vcu[0].SCROLL[offset&0x0E], data);
     break;
   default:
     print_debug("tp1vcu[0] ww(%04x,%04x)\n", offset&0x1E, data);
     break;
   }
}

static UINT16 tp1vcu_bg_rw(UINT32 offset)
{
   UINT16 ret;

   switch(offset&0x1E){
   case 0x00:                        // Status
     ret = tp1vcu[0].status;
     tp1vcu[0].status ^= 1;
     break;
   case 2:
     return tp1vcu[0].bg_pos>>2;
   case 0x04:                        // Port Data
     ret = ReadWord(&tp1vcu[0].VRAM[tp1vcu[0].bg_pos]);
     break;
   case 0x06:                        // Port Data
     ret = ReadWord(&tp1vcu[0].VRAM[tp1vcu[0].bg_pos+2]);
     break;

   case 0x10:                        // Scroll
   case 0x12:                        // Scroll
   case 0x14:                        // Scroll
   case 0x16:                        // Scroll
   case 0x18:                        // Scroll
   case 0x1A:                        // Scroll
   case 0x1C:                        // Scroll
   case 0x1E:                        // Scroll
     ret = ReadWord(&tp1vcu[0].SCROLL[offset&0x0E]);
     break;
   default:
     ret = 0x0000;
     print_debug("tp1vcu[0] rw(%04x)\n", offset&0x0E);
     break;
   }

   return ret;
}

static UINT8 tp1vcu_bg_rb(UINT32 offset)
{
   UINT16 ret;

   ret = tp1vcu_bg_rw(offset);

   if((offset&1)==0)
      return (UINT8) ((ret>>8)&0xFF);
   else
      return (UINT8) ((ret>>0)&0xFF);
}

/******************************************************************************/
/*  VBLANK/INTERRUPT THINGY                                                   */
/******************************************************************************/

static UINT32 want_int;

// static int x_ofs[4];

static UINT8 tp_vblank_rb(UINT32 offset)
{
   static UINT8 status;

   switch(offset & 0x0E){
   case 0x00:
      status ^= 1;
      return status;
   break;
   default:
      return 0;
   break;
   }
}

static UINT16 tp_vblank_rw(UINT32 offset)
{
   return (UINT16) (tp_vblank_rb(offset));
}

static void tp_vblank_wb(UINT32 offset, UINT8 data)
{
   switch(offset & 0x0E){
   case 0x02:
     if (data != 1 || want_int != 1)
     want_int = data & 1;
      print_debug("want_int: %d\n", want_int);
   break;
   /* Incredible : apparently these offsets are not used ?!!!!! */
   /* But then why did Antiriad think they were usefull ?!????  */
/*    case 0x08: */
/*       x_ofs[0] = (data&0xFF) - 0xd8; */
/*    break; */
/*    case 0x0A: */
/*       x_ofs[1] = (data&0xFF) - 0x17; */
/*    break; */
/*    case 0x0C: */
/*       x_ofs[2] = (data&0xFF) - 0x88; */
/*    break; */
/*    case 0x0E: */
/*       x_ofs[3] = (data&0xFF) - 0x07; */
/*    break; */
/*    default: */
/*    break; */
   }
}

static void tp_vblank_ww(UINT32 offset, UINT16 data)
{
   tp_vblank_wb(offset, (UINT8)(data&0xFF));
}

static int bg_x_ofs;
static int bg_y_ofs,dy;

static void tp1vcu_ofsreg_ww(UINT32 offset, UINT16 data)
{
  switch (offset & 6) {
  case 0:
    bg_x_ofs = data;
    break;
  case 2:
    bg_y_ofs = data;
    break;
  case 6:
    break;
  }
}

static UINT8 fshark_z80_rb(UINT32 offset)
{
   UINT16 ret;

   offset |= 1;
   switch(offset&0xFF){
      case 0x01:                        // p1 controls
	ret = RAM[0x023004];
      break;
      case 0x03:                        // p2 input
         ret = RAM[0x023005];
      break;
      case 0x05:                        // dsw a
         ret = get_dsw(0);
      break;
      case 0x07:                        // dswb
         ret = get_dsw(1);
      break;
      case 0x09:                        // misc input
	ret = RAM[0x023003];
      break;
      case 0x0B:                        // dsw c
	ret = get_dsw(2) | 0x80;
      break;
      default:
         ret = 0x00;
         print_debug("fshark_z80_rb(%04x)\n", offset&0xFF);
      break;
   }

   return ret;
}

static UINT16 fshark_z80_rw(UINT32 offset)
{
  // fprintf(stderr,"called %x\n",offset);
  return (UINT16) (fshark_z80_rb(offset|1));
}

/******************************************************************************/
/*  Z80 NORMAL                                                                */
/******************************************************************************/

static UINT8 tp1_z80_rb(UINT32 offset)
{
   offset  &= 0xFFF;
   offset >>= 1;

   return Z80RAM[ offset];
}

static UINT16 tp1_z80_rw(UINT32 offset)
{
   offset  &= 0xFFF;
   offset >>= 1;

   return (UINT16) (Z80RAM[ offset]);
}

static void tp1_z80_wb(UINT32 offset, UINT8 data)
{
   offset  &= 0xFFF;
   offset >>= 1;

   Z80RAM[ offset] = data;
}

static void tp1_z80_ww(UINT32 offset, UINT16 data)
{
   offset  &= 0xFFF;
   offset >>= 1;

   Z80RAM[ offset] = (UINT8) (data&0xFF);
}

static UINT8 zero_wing_port_rb(UINT16 offset)
{
   switch(offset&0xFF){
      case 0x00:
         return RAM[0x023004];
      break;
      case 0x08:
         return RAM[0x023005];
      break;
      case 0x20:
         return get_dsw(0);
      break;
      case 0x28:
         return get_dsw(1);
      break;
      case 0x80:
         return RAM[0x023003];
      break;
      case 0x88:
         return get_dsw(2);
      break;
      case 0xA8:
	return YM3812ReadZ80(0);
      break;
      default:
         return 0x00;
      break;
   }
}

static void zero_wing_port_wb(UINT16 offset, UINT8 data)
{
   switch(offset&0xFF){
      case 0xA8:
         YM3812WriteZ80(0,data);
      break;
      case 0xA9:
         YM3812WriteZ80(1,data);
      break;
      default:
      break;
   }
}

static UINT8 demons_world_port_rb(UINT16 offset)
{
   switch(offset&0xFF){
      case 0x00:
         return YM3812ReadZ80(0);
      break;
      case 0x20:
         return get_dsw(2);
      break;
      case 0x60:
         return RAM[0x023003];
      break;
      case 0x80:
         return RAM[0x023004];
      break;
      case 0xA0:
         return get_dsw(1);
      break;
      case 0xC0:
         return RAM[0x023005];
      break;
      case 0xE0:
         return get_dsw(0);
      break;
      default:
         return 0xFF;
      break;
   }
}

static void demons_world_port_wb(UINT16 offset, UINT8 data)
{
   switch(offset&0xFF){
      case 0x00:
         YM3812WriteZ80(0,data);
      break;
      case 0x01:
         YM3812WriteZ80(1,data);
      break;
      default:
      break;
   }
}

static UINT8 truxton_port_rb(UINT16 offset)
{
   switch(offset&0xFF){
      case 0x00:
         return RAM[0x023004]; // p1
      case 0x10:
         return RAM[0x023005]; // p2
      case 0x20:
         return RAM[0x023003]; // system
      case 0x40:
         return get_dsw(0);
      case 0x50:
         return get_dsw(1);
      case 0x60:
         return YM3812ReadZ80(0);
      case 0x70:
         return get_dsw(2);
      default:
         return 0xFF;
   }
}

static void truxton_port_wb(UINT16 offset, UINT8 data)
{
   switch(offset&0xFF){
   case 0x60:
     YM3812WriteZ80(0,data);
     break;
   case 0x61:
     YM3812WriteZ80(1,data);
     break;
   default:
     break;
   }
}

static UINT8 vimana_port_rb(UINT16 offset)
{
   switch(offset&0xFF){
      case 0x60: return get_dsw(1) ^ 255;
      case 0x66: return (get_dsw(2) ^ 255)|0xc0;
      case 0x80: return RAM[0x023004]; // p1
      case 0x81: return RAM[0x023005]; // p2
      case 0x82: return get_dsw(0);
      case 0x83: return RAM[0x023003]; // system
      case 0x87: return YM3812ReadZ80(0);
      case 0x8f: return YM3812ReadZ80(1);
      default:
         return 0xFF;
      break;
   }
}

static void vimana_port_wb(UINT16 offset, UINT8 data)
{
   switch(offset&0xFF){
   case 0x87: YM3812WriteZ80(0,data); break;
   case 0x8f: YM3812WriteZ80(1,data); break;
   default:
     break;
   }
}

static UINT8 outzone_port_rb(UINT16 offset)
{
   switch(offset&0xFF){
      case 0x00:
      case 1:
         return YM3812ReadZ80(offset);
      break;
      case 0x08:
         return get_dsw(0);
      break;
      case 0x0C:
         return get_dsw(1);
      break;
      case 0x10:
         return RAM[0x023003];
      break;
      case 0x14:
         return RAM[0x023004];
      break;
      case 0x18:
         return RAM[0x023005];
      break;
      case 0x1C:
         return get_dsw(2);
      break;
      default:
         return 0xFF;
      break;
   }
}

static void outzone_port_wb(UINT16 offset, UINT8 data)
{
   switch(offset&0xFF){
      case 0x00:
         YM3812WriteZ80(0,data);
      break;
      case 0x01:
         YM3812WriteZ80(1,data);
      break;
      default:
      break;
   }
}


static UINT8 hell_fire_port_rb(UINT16 offset)
{
   switch(offset&0xFF){
      case 0x00:
         return get_dsw(0);
      break;
      case 0x10:
         return get_dsw(1);
      break;
      case 0x20:
         return get_dsw(2);
      break;
      case 0x40:
         return RAM[0x023004];
      break;
      case 0x50:
         return RAM[0x023005];
      break;
      case 0x60:
         return RAM[0x023003];
      break;
      case 0x70:
         return YM3812ReadZ80(0);
      break;
      default:
         return 0xFF;
      break;
   }
}

static void hell_fire_port_wb(UINT16 offset, UINT8 data)
{
   switch(offset&0xFF){
      case 0x70:
         YM3812WriteZ80(0,data);
      break;
      case 0x71:
         YM3812WriteZ80(1,data);
      break;
      default:
      break;
   }
}

/******************************************************************************/

static int layer_id_data[5];

static char *layer_id_name[5] =
{
   "PF1", "PF2", "PF3", "PF4", "OBJECT",
};

static int tp1_setup_gfx() {
  GFX_BG0 = NULL;
  if(!(TileQueue = (struct TILE_Q *) AllocateMem(sizeof(TILE_Q)*MAX_TILES)))return -1;
  AddResetHandler(&quiet_reset_handler);
  return 0;
}

static void tp1_finish_setup_gfx() {
  int nb_bg0 = max_sprites[0];
  int nb_obj = max_sprites[1];
  int i;

  for (i=0; i<5; i++)
    layer_id_data[i] = add_layer_info(layer_id_name[i]);

  GFX_BG0 = gfx1;
  GFX_SPR = gfx2;

  GFX_BG0_SOLID = gfx1_solid;
  GFX_SPR_SOLID = gfx2_solid;

  tp1vcu[0].VRAM          = RAM+0x11000;
  tp1vcu[0].RAM_OBJ       = RAM+0x21000;
  tp1vcu[0].SCROLL        = RAM+0x22000;
  tp1vcu[0].GFX_BG        = GFX_BG0;
  tp1vcu[0].MASK_BG       = GFX_BG0_SOLID;
  tp1vcu[0].tile_mask_bg  = nb_bg0-1;
  tp1vcu[0].tile_mask_obj = nb_obj-1;
  tp1vcu[0].tile_ofs_obj  = nb_bg0;
  init_tp1vcu(0);

  InitPaletteMap(RAM+0x10000, 0x80, 0x10, 0x8000);

  set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
}

static void load_vimana()
{
   romset = 0;
   dy = 0;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   memset(RAM+0x00000,0x00,0x40000);
   RAMSize=0x40000+0x10000;
   Z80RAM = RAM + 0x40000;
   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(4,fps));

   // It's a z180, not a z80, but it's worth a try... !
   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fff, NULL,                Z80ROM+0x0000); // Z80 ROM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);
   AddZ80ARW(0xfe00, 0xffff, NULL, Z80RAM+0x800); // more ram

   AddZ80AReadPort(0x00, 0xFF, vimana_port_rb,         NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, vimana_port_wb,        NULL);

   finish_conf_z80_ports(0);

   if(is_current_game("vimanaj"))
   {

       // Kill the annoying reset instruction

       WriteWord68k(&ROM[0x1A830],0x4E71);          // nop

       // Something failed a test

       WriteWord68k(&ROM[0x1AA3E],0x4E71);          // nop

       // 68000 speed hack

       WriteLong68k(&ROM[0x17918],0x13FC0000);
       WriteLong68k(&ROM[0x1791C],0x00AA0000);

   }
   else{ // vimana

       // Kill the annoying reset instruction

       WriteWord68k(&ROM[0x1ab1c],0x4E71);          // nop

       // Something failed a test

       WriteWord68k(&ROM[0x1ad2a],0x4E71);          // nop

       // 68000 speed hack

       WriteLong68k(&ROM[0x17c04],0x13FC0000);
       WriteLong68k(&ROM[0x17c08],0x00AA0000);

   }

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);

   add_68000_rom(0, 0x000000, 0x03FFFF, ROM+0x000000);                 // 68000 ROM
   add_68000_ram(0, 0x480000, 0x483FFF, RAM+0x000000);                 // 68000 RAM
   add_68000_ram(0, 0x404000, 0x4047FF, RAM+0x010000);                 // COLOR RAM
   add_68000_ram(0, 0x406000, 0x4067FF, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0x0C0000, 0x0C000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x4C0000, 0x4C001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x400000, 0x40000F, tp_vblank_rb, NULL);                 // VSYNC
   // AddReadByte(0x440000, 0x440FFF, vimana_z80_rb, NULL);                // SOUND COMM
   AddReadByte(0x440000, 0x4407FF, tp1_z80_rb, NULL);                // SOUND COMM

   AddReadWord(0x0C0000, 0x0C000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x4C0000, 0x4C001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x400000, 0x40000F, tp_vblank_rw, NULL);                 // VSYNC
   // AddReadWord(0x440000, 0x440FFF, vimana_z80_rw, NULL);                // SOUND COMM
   AddReadWord(0x440000, 0x4407FF, tp1_z80_rw, NULL);                // SOUND COMM

   AddWriteByte(0x400000, 0x40000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x440000, 0x4407FF, tp1_z80_wb, NULL);                // SOUND COMM

   AddWriteWord(0x0C0000, 0x0C000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x4C0000, 0x4C001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x400000, 0x40000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x080000, 0x080003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   AddWriteWord(0x440000, 0x4407FF, tp1_z80_ww, NULL);                // SOUND COMM
   finish_conf_68000(0);     // Set Starscream mem pointers...
}

static void load_outzone(void)
{
   romset = 2;
   dy = 0;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(4,fps));

   if(!(RAM=AllocateMem(0x80000)))return;
   Z80RAM = RAM + 0x40000;
   memset(Z80RAM,0,0x8000);
   if (tp1_setup_gfx()) return;

   memset(RAM+0x00000,0x00,0x40000);
   RAMSize=0x40000+0x10000;

   /* Sound Setup */

/*
   // Fix Checksum

   Z80ROM[0x0156]=0x00; // NOP
   Z80ROM[0x0157]=0x00; // NOP
   Z80ROM[0x0158]=0x00; // NOP

   // Apply Speed Patch

   Z80ROM[0x019D]=0xD3; // OUTA (AAh)
   Z80ROM[0x019E]=0xAA; //

   SetStopZ80Mode2(0x019C);
*/
   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fff, NULL,                Z80ROM+0x0000); // Z80 ROM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);

   AddZ80AReadPort(0x00, 0xFF, outzone_port_rb,         NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, outzone_port_wb,        NULL);

   finish_conf_z80_ports(0);

   // Kill the annoying reset instruction

   // WriteWord68k(&ROM[0x13930],0x4E71);          // nop
/*
   // Something failed a test

   WriteWord68k(&ROM[0x1AA3E],0x4E71);          // nop

   // 68000 speed hack

   WriteLong68k(&ROM[0x17918],0x13FC0000);
   WriteLong68k(&ROM[0x1791C],0x00AA0000);
*/
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);

   add_68000_rom(0,0,0x3ffff, ROM);
   add_68000_ram(0,0x240000, 0x243fff,RAM);
   add_68000_ram(0,0x304000, 0x3047FF,RAM + 0x10000);
   add_68000_ram(0,0x306000, 0x3067FF,RAM + 0x10800);
   AddReadByte(0x100000, 0x10000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x200000, 0x20001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x300000, 0x30000F, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x140000, 0x140FFF, tp1_z80_rb, NULL);                   // SOUND COMM

   AddReadWord(0x100000, 0x10000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x200000, 0x20001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x300000, 0x30000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x140000, 0x140FFF, tp1_z80_rw, NULL);                   // SOUND COMM

   AddWriteByte(0x300000, 0x30000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0x140000, 0x140FFF, tp1_z80_wb, NULL);                  // SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000

   AddWriteWord(0x100000, 0x10000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x200000, 0x20001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x300000, 0x30000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x140000, 0x140FFF, tp1_z80_ww, NULL);                  // SOUND COMM
   AddWriteWord(0x340000, 0x340003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   finish_conf_68000(0);
}

static void load_rallybik(void)
{
   romset = 3;
   dy = 0;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   memset(RAM+0x00000,0x00,0x40000);
   RAMSize=0x40000+0x10000;

   Z80RAM=RAM+0x40000;
/*
   // Fix Checksum

   Z80ROM[0x0156]=0x00; // NOP
   Z80ROM[0x0157]=0x00; // NOP
   Z80ROM[0x0158]=0x00; // NOP

   // Apply Speed Patch

   Z80ROM[0x019D]=0xD3; // OUTA (AAh)
   Z80ROM[0x019E]=0xAA; //

   SetStopZ80Mode2(0x019C);
*/
   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fff, NULL,                Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);

   AddZ80AReadPort(0x00, 0xFF, truxton_port_rb,         NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, truxton_port_wb,        NULL);
   finish_conf_z80_ports(0);

   // Something failed a test

   WriteWord68k(&ROM[0x0193E],0x6000);

   // Fix rom checksum

   WriteWord68k(&ROM[0x01A66],0x7400);

   // 68000 speed hack

   WriteLong68k(&ROM[0x01BA0],0x13FC0000);
   WriteLong68k(&ROM[0x01BA4],0x00AA0000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x080000, 0x083FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x144000, 0x1447FF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadByte(0x146000, 0x1467FF, NULL, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x021000);                 // OBJECT
   AddReadByte(0x100000, 0x10001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x140000, 0x14000F, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x180000, 0x180FFF, tp1_z80_rb, NULL);                   // SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x080000, 0x083FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x144000, 0x1447FF, NULL, RAM+0x010000);                 // COLOR RAM
   AddReadWord(0x146000, 0x1467FF, NULL, RAM+0x010800);                 // COLOR RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x021000);                 // OBJECT
   AddReadWord(0x100000, 0x10001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x140000, 0x14000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x180000, 0x180FFF, tp1_z80_rw, NULL);                   // SOUND COMM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x083FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x144000, 0x1447FF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteByte(0x146000, 0x1467FF, NULL, RAM+0x010800);                // COLOR RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x021000);                // OBJECT
   AddWriteByte(0x140000, 0x14000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0x180000, 0x180FFF, tp1_z80_wb, NULL);                  // SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x083FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x144000, 0x1447FF, NULL, RAM+0x010000);                // COLOR RAM
   AddWriteWord(0x146000, 0x1467FF, NULL, RAM+0x010800);                // COLOR RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x021000);                // OBJECT
   AddWriteWord(0x100000, 0x10001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x140000, 0x14000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x180000, 0x180FFF, tp1_z80_ww, NULL);                  // SOUND COMM
   AddWriteWord(0x1C0000, 0x1C0003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...

}

static void load_zerowing(void)
{
   romset = 4;
   dy = 16;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   RAMSize=0x40000+0x10000;
   memset(RAM+0x00000,0x00,RAMSize);

   Z80RAM=RAM+0x40000;
/*
   // Fix Checksum

   Z80ROM[0x0156]=0x00; // NOP
   Z80ROM[0x0157]=0x00; // NOP
   Z80ROM[0x0158]=0x00; // NOP

   // Apply Speed Patch

   Z80ROM[0x019D]=0xD3; // OUTA (AAh)
   Z80ROM[0x019E]=0xAA; //

   SetStopZ80Mode2(0x019C);
*/
   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fFF, NULL,                Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);

   AddZ80AReadPort(0x00, 0xFF, zero_wing_port_rb,       NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, zero_wing_port_wb,      NULL);
   finish_conf_z80_ports(0);

   // Actually the game works very well without these hacks now, even the speed hack is not really needed...
   // But speed hacks are fun ! ;-)
#if 1
   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x00236],0x4E71);          // nop

   // Fix rom checksum

   WriteLong68k(&ROM[0x00568],0x4E714E71);      // nop

   // Fix sound error

   // WriteLong68k(&ROM[0x004E6],0x4E714E71);      // nop
   // WriteLong68k(&ROM[0x0050C],0x4E714E71);      // nop

   // 68000 speed hack

   WriteLong68k(&ROM[0x5a0a],0x13FC0000);
   WriteLong68k(&ROM[0x5a0a+4],0x00AA0000);
#endif

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);

   add_68000_rom(0,0x000000, 0x07FFFF, ROM+0x000000);                 // 68000 ROM
   add_68000_ram(0,0x080000, 0x083FFF, RAM+0x000000);                 // 68000 RAM
   add_68000_ram(0,0x404000, 0x4047FF, RAM+0x010000);                 // COLOR RAM
   add_68000_ram(0,0x406000, 0x4067FF, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0x4C0000, 0x4C000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x480000, 0x48001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x400000, 0x40000F, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x440000, 0x440FFF, tp1_z80_rb, NULL);                   // SOUND COMM

   AddReadWord(0x4C0000, 0x4C000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x480000, 0x48001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x400000, 0x40000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x440000, 0x440FFF, tp1_z80_rw, NULL);                   // SOUND COMM

   AddWriteByte(0x400000, 0x40000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0x440000, 0x440FFF, tp1_z80_wb, NULL);                  // SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000

   AddWriteWord(0x4C0000, 0x4C000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x480000, 0x48001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x400000, 0x40000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x440000, 0x440FFF, tp1_z80_ww, NULL);                  // SOUND COMM
   AddWriteWord(0x0c0000, 0x0c0003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   finish_conf_68000(0);
}

static void load_demonwld(void)
{
   romset = 5;
   dy = 16;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   memset(RAM+0x00000,0x00,0x40000);
   RAMSize=0x40000+0x10000;

   /* Sound Setup */

   Z80RAM=RAM+0x40000;
/*
   // Fix Checksum

   Z80ROM[0x0156]=0x00; // NOP
   Z80ROM[0x0157]=0x00; // NOP
   Z80ROM[0x0158]=0x00; // NOP

   // Apply Speed Patch

   Z80ROM[0x019D]=0xD3; // OUTA (AAh)
   Z80ROM[0x019E]=0xAA; //

   SetStopZ80Mode2(0x019C);
*/
   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fff, NULL,                Z80ROM+0x0000); // Z80 ROM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);

   AddZ80AReadPort(0x00, 0xFF, demons_world_port_rb,    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, demons_world_port_wb,   NULL);
   finish_conf_z80_ports(0);

   // Kill the annoying reset instruction
/*
   WriteWord68k(&ROM[0x0023C],0x4E71);          // nop

   // Fix rom checksum

   WriteLong68k(&ROM[0x004DA],0x4E714E71);      // nop
*/
    if (is_current_game("demonwld2")) {
	// 68000 speed hack

	WriteLong68k(&ROM[0x454a],0x13FC0000);
	WriteLong68k(&ROM[0x454a+4],0x00AA0000);

	// Fix protection/mcu?
	// Yeah that's what mame calls a "dsp"
	// never saw such a useless dsp !
	// In this case it's a very low level mcu, a shame for a so-called dsp !

	WriteWord68k(&ROM[0x0181C],0x4E71);
	WriteWord68k(&ROM[0x01824],0x600A);
    } else if (is_current_game("demonwld")) {
	// dsp
	WriteWord68k(&ROM[0x01430],0x4E71);
	WriteWord68k(&ROM[0x01438],0x600A);
	// checksum
	WriteWord68k(&ROM[0x0145e],0x4E71);
	WriteWord68k(&ROM[0x01474],0x6020);
	// speed hack
	WriteLong68k(&ROM[0x439c],0x13FC0000);
	WriteLong68k(&ROM[0x439c+4],0x00AA0000);
    }

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);

   add_68000_rom(0,0x000000, 0x03FFFF, ROM+0x000000);                 // 68000 ROM
   add_68000_ram(0,0xC00000, 0xC03FFF, RAM+0x000000);                 // 68000 RAM
   add_68000_ram(0,0x404000, 0x4047FF, RAM+0x010000);                 // COLOR RAM
   add_68000_ram(0,0x406000, 0x4067FF, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0xA00000, 0xA0000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x800000, 0x80001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x400000, 0x40000F, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x600000, 0x600FFF, tp1_z80_rb, NULL);                   // SOUND COMM

   AddReadWord(0xA00000, 0xA0000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x800000, 0x80001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x400000, 0x40000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x600000, 0x600FFF, tp1_z80_rw, NULL);                   // SOUND COMM

   AddWriteByte(0x400000, 0x40000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0x600000, 0x600FFF, tp1_z80_wb, NULL);                  // SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000

   AddWriteWord(0xA00000, 0xA0000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x800000, 0x80001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x400000, 0x40000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x600000, 0x600FFF, tp1_z80_ww, NULL);                  // SOUND COMM
   AddWriteWord(0xE00000, 0xE00003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   finish_conf_68000(0);
}

static void load_fireshrk(void)
{
   romset = 6;
   dy = 0;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   memset(RAM+0x00000,0x00,0x40000);
   RAMSize=0x40000+0x10000;

   if(is_current_game("fireshrk"))
   {

   // Kill the annoying reset instruction

     WriteWord68k(&ROM[0x06f6c],0x4E71);          // nop

     // Something failed a test

     WriteWord68k(&ROM[0x0706e],0x4e71);          // nop
     //WriteWord68k(&ROM[0x05f0a],0x4e71);          // nop

     // 68000 speed hack

     WriteLong68k(&ROM[0x5f04],0x13FC0000);
     WriteLong68k(&ROM[0x5f08],0x00AA0000);
   }
   else
   {

   // Kill the annoying reset instruction

   WriteWord68k(&ROM[0x06c56],0x4E71);          // nop

   // Something failed a test

   WriteWord68k(&ROM[0x06d62],0x4e71);          // nop

   // 68000 speed hack

   WriteLong68k(&ROM[0x58c8],0x13FC0000);
   WriteLong68k(&ROM[0x58cc],0x00AA0000);

   }

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);

   add_68000_rom(0,0x000000, 0x07FFFF, ROM+0x000000);                 // 68000 ROM
   //AddReadBW(0x000000, 0x00ffff, NULL, ROM+0x000000);                 // 68000 ROM
   //AddReadBW(0x040000, 0x07FFFF, NULL, ROM+0x040000);                 // 68000 ROM
   add_68000_ram(0,0x0C0000, 0x0C3FFF, RAM+0x000000);                 // 68000 RAM
   add_68000_ram(0,0x104000, 0x1047FF, RAM+0x010000);                 // COLOR RAM
   add_68000_ram(0,0x106000, 0x1067FF, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0x1C0000, 0x1C000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x180000, 0x18001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x100000, 0x100001, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x140000, 0x140FFF, fshark_z80_rb, NULL);                // SOUND COMM

   AddReadWord(0x1C0000, 0x1C000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x180000, 0x18001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x100000, 0x10000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x140000, 0x140FFF, fshark_z80_rw, NULL);                // SOUND COMM

   AddWriteByte(0x100000, 0x10000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000

   AddWriteWord(0x1C0000, 0x1C000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x180000, 0x18001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x100000, 0x10000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x080000, 0x080007, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   finish_conf_68000(0);
}

static void load_hellfire(void)
{
   romset = 8;
   dy = 16;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   memset(RAM+0x00000,0x00,0x40000);
   RAMSize=0x40000+0x10000;

   /* Sound Setup */

   Z80RAM=RAM+0x40000;
/*
   // Fix Checksum

   Z80ROM[0x0156]=0x00; // NOP
   Z80ROM[0x0157]=0x00; // NOP
   Z80ROM[0x0158]=0x00; // NOP

   // Apply Speed Patch

   Z80ROM[0x019D]=0xD3; // OUTA (AAh)
   Z80ROM[0x019E]=0xAA; //

   SetStopZ80Mode2(0x019C);
*/
   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fFF, NULL,                Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);

   AddZ80AReadPort(0x00, 0xFF, hell_fire_port_rb,       NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, hell_fire_port_wb,      NULL);
   finish_conf_z80_ports(0);

   // Kill the annoying reset instruction
/*
   WriteWord68k(&ROM[0x0023C],0x4E71);          // nop

   // Fix rom checksum

   WriteLong68k(&ROM[0x004DA],0x4E714E71);      // nop
*/
   // Fix sound error
/*
   WriteLong68k(&ROM[0x0188C],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x018B2],0x4E714E71);      // nop
*/
/*
   // 68000 speed hack

   WriteLong68k(&ROM[0x17918],0x13FC0000);
   WriteLong68k(&ROM[0x1791C],0x00AA0000);
*/
   // Fix protection/mcu?
/*
   WriteWord68k(&ROM[0x0181C],0x4E71);
   WriteWord68k(&ROM[0x01824],0x600A);
*/
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);

   add_68000_rom(0,0x000000, 0x03FFFF, ROM+0x000000);                 // 68000 ROM
   add_68000_ram(0,0x040000, 0x043FFF, RAM+0x000000);                 // 68000 RAM
   add_68000_ram(0,0x084000, 0x0847FF, RAM+0x010000);                 // COLOR RAM
   add_68000_ram(0,0x086000, 0x0867FF, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0x140000, 0x14000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x100000, 0x10001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x080000, 0x08000F, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x0C0000, 0x0C0FFF, tp1_z80_rb, NULL);                   // SOUND COMM

   AddReadWord(0x140000, 0x14000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x100000, 0x10001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x080000, 0x08000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x0C0000, 0x0C0FFF, tp1_z80_rw, NULL);                   // SOUND COMM

   AddWriteByte(0x080000, 0x08000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0x0C0000, 0x0C0FFF, tp1_z80_wb, NULL);                  // SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000

   AddWriteWord(0x140000, 0x14000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x100000, 0x10001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x080000, 0x08000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x0C0000, 0x0C0FFF, tp1_z80_ww, NULL);                  // SOUND COMM
   AddWriteWord(0x180000, 0x180003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
    finish_conf_68000(0);
}

static void load_truxton(void)
{
   romset = 9;
   dy = 0;

   if(!(RAM=AllocateMem(0x80000)))return;
   if (tp1_setup_gfx()) return;

   RAMSize=0x40000+0x10000;
   memset(RAM+0x00000,0x00,RAMSize);

   /* Sound Setup */

   Z80RAM=RAM+0x40000;
/*
   // Fix Checksum

   Z80ROM[0x0156]=0x00; // NOP
   Z80ROM[0x0157]=0x00; // NOP
   Z80ROM[0x0158]=0x00; // NOP

   // Apply Speed Patch

   Z80ROM[0x019D]=0xD3; // OUTA (AAh)
   Z80ROM[0x019E]=0xAA; //

   SetStopZ80Mode2(0x019C);
*/
   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fff, NULL,                        Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80ARW(0x8000, 0x87ff, NULL, Z80RAM);

   AddZ80AReadPort(0x00, 0xFF, truxton_port_rb,         NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, truxton_port_wb,        NULL);

   finish_conf_z80_ports(0);

   // 68000 speed hack

   WriteLong68k(&ROM[0x26ce],0x13FC0000);
   WriteLong68k(&ROM[0x26d2],0x00AA0000);
   WriteWord68k(&ROM[0x5076],0x4e71);

   // Kill the annoying reset instruction
/*
   WriteWord68k(&ROM[0x0023C],0x4E71);          // nop

   // Fix rom checksum

   WriteLong68k(&ROM[0x004DA],0x4E714E71);      // nop
*/
   // Fix sound error
/*
   WriteLong68k(&ROM[0x0188C],0x4E714E71);      // nop
   WriteLong68k(&ROM[0x018B2],0x4E714E71);      // nop
*/
/*
*/
   // Fix protection/mcu?
/*
   WriteWord68k(&ROM[0x0181C],0x4E71);
   WriteWord68k(&ROM[0x01824],0x600A);
*/
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);

   add_68000_rom(0,0x000000, 0x03FFFF, ROM+0x000000);                 // 68000 ROM
   add_68000_ram(0,0x080000, 0x083FFF, RAM+0x000000);                 // 68000 RAM
   add_68000_ram(0,0x144000, 0x1447FF, RAM+0x010000);                 // COLOR RAM
   add_68000_ram(0,0x146000, 0x1467FF, RAM+0x010800);                 // COLOR RAM
   AddReadByte(0x0C0000, 0x0C000F, tp1vcu_obj_rb, NULL);                // OBJECT
   AddReadByte(0x100000, 0x10001F, tp1vcu_bg_rb, NULL);                 // LAYER
   AddReadByte(0x140000, 0x14000F, tp_vblank_rb, NULL);                 // VSYNC
   AddReadByte(0x180000, 0x180FFF, tp1_z80_rb, NULL);                   // SOUND COMM

   AddReadWord(0x0C0000, 0x0C000F, tp1vcu_obj_rw, NULL);                // OBJECT
   AddReadWord(0x100000, 0x10001F, tp1vcu_bg_rw, NULL);                 // LAYER
   AddReadWord(0x140000, 0x14000F, tp_vblank_rw, NULL);                 // VSYNC
   AddReadWord(0x180000, 0x180FFF, tp1_z80_rw, NULL);                   // SOUND COMM

   AddWriteByte(0x140000, 0x14000F, tp_vblank_wb, NULL);                // VSYNC
   AddWriteByte(0x180000, 0x180FFF, tp1_z80_wb, NULL);                  // SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000

   AddWriteWord(0x0C0000, 0x0C000F, tp1vcu_obj_ww, NULL);               // OBJECT
   AddWriteWord(0x100000, 0x10001F, tp1vcu_bg_ww, NULL);                // LAYER
   AddWriteWord(0x140000, 0x14000F, tp_vblank_ww, NULL);                // VSYNC
   AddWriteWord(0x180000, 0x180FFF, tp1_z80_ww, NULL);                  // SOUND COMM
   AddWriteWord(0x1C0000, 0x1C0003, tp1vcu_ofsreg_ww, NULL);            // OFFSET
   finish_conf_68000(0);
}

static void execute_fireshrk(void)
{
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));    // M68000 16MHz (60fps) (real game is only ??MHz)
   if(want_int) {
     cpu_interrupt(CPU_68K_0, 4);
   }
   // samesame / fireshark need int 2...
   if (romset == 6) {
     // If we don't execute these few cycles, then int4 is simply ignored !!!
     cpu_execute_cycles(CPU_68K_0, 1000);
     cpu_interrupt(CPU_68K_0, 2);
   }
}

static void execute_outzone(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));    // M68000 16MHz (60fps) (real game is only ??MHz)
   if(want_int){
      cpu_interrupt(CPU_68K_0, 4);
   }

   execute_z80_audio_frame();
}

static void ClearTileQueue(void)
{
   int ta;

   for(ta=0;ta<MAX_PRI;ta++){
     prilist[ta] = NULL;
   }

   last_tile = TileQueue;
}

static DEF_INLINE void QueueTile(int tile, int x, int y, UINT8 *map, int pri)
{
   last_tile->tile = tile;
   last_tile->x    = x;
   last_tile->y    = y;
   last_tile->map  = map;
   last_tile->next = prilist[pri];
   prilist[pri]    = last_tile;
   last_tile       = last_tile+1;
}

// static int wanted_pri = -1;

static void DrawTileQueue(void)
{
   struct TILE_Q *tile_ptr;
   UINT32 ta,pri,pri_start;
#if 0
   static int pressed;
   int pri_end;

   if (pressed && !key[SDLK_F10]) {
       pressed = 0;
   } else if (!pressed && key[SDLK_F10]) {
       pressed = 1;
       wanted_pri++;
       if (wanted_pri >= MAX_PRI)
	   wanted_pri = -1;
       print_ingame(60,"wanted_pri : %d",wanted_pri);
   }
#endif

   // priority 0 is for "off" sprites.
   if (romset == 2) // but outzone does not have sprites turned off !
     pri_start = 0;
   else
     pri_start = 2;
#if 0
   if (wanted_pri == -1)
       pri_end = MAX_PRI;
   else if (wanted_pri >= 0 && wanted_pri < MAX_PRI) {
       pri_start = pri_end = wanted_pri;
       pri_end++;
   }
#endif

   for(pri=pri_start; pri<MAX_PRI; pri++)
   {
      tile_ptr = prilist[pri];

      if((pri & 1))
      {
         while(tile_ptr){
            ta = tile_ptr->tile;
            if(GFX_BG0_SOLID[ta]!=0){                      // No pixels; skip
               if(GFX_BG0_SOLID[ta]==1)                    // Some pixels; trans
                  Draw8x8_Trans_Mapped_Rot(&GFX_BG0[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
               else                                        // all pixels; solid
                  Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
            }
            tile_ptr = tile_ptr->next;
         }
      }
      else
      {
         while(tile_ptr){
            ta = tile_ptr->tile;
            if(GFX_SPR_SOLID[ta]!=0){                      // No pixels; skip
               if(GFX_SPR_SOLID[ta]==1)                    // Some pixels; trans
                  Draw8x8_Trans_Mapped_Rot(&GFX_SPR[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
               else                                        // all pixels; solid
                  Draw8x8_Mapped_Rot(&GFX_SPR[ta<<6],tile_ptr->x,tile_ptr->y,tile_ptr->map);
            }
            tile_ptr = tile_ptr->next;
         }
      }

   }

}

static UINT16 vram_ofs[ROM_COUNT][4] =
{
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 },
   { 0x0000,0x4000,0x8000,0xC000 }, // Truxton
};

#define OBJ_X_MASK	0x1FF
#define OBJ_Y_MASK	0x1FF

static void DrawToaplan1(void)
{
   int x,y,ta,pri,layer;
   int zz,zzz,zzzz,x16,y16;
   int xx,xxx,xxxx,yyy,x1,y1;
   UINT8 *MAP,*RAM_BG,*RAM_BG2;
   UINT32 tile_mask;
   UINT16 ctrl;
   if (!GFX_BG0)
     tp1_finish_setup_gfx();

   ClearPaletteMap();

	 MAP_PALETTE_MAPPED_NEW(
				0x12,
				16,
				MAP
				);
   clear_game_screen(ReadLong(&MAP[0]));

   ClearTileQueue();

   // tp1_flipscreen changes layer alignement, but it seems to be only related
   // to the invert screen dip. So we just don't use it for now.

   // BG0123

   /* Bg info from mame... Don't ask me why Antiriad NEVER puts any interesting comments
      in his source code...

  There are 4 scrolling layers of graphics, stored in planes of 64x64 tiles.
  Each tile in each plane is assigned a priority between 1 and 15, higher
  numbers have greater priority.

 BCU controller. Each tile takes up 32 bits - the format is:

  0         1         2         3
  ---- ---- ---- ---- -ttt tttt tttt tttt = Tile number (0 - $7fff)
  ---- ---- ---- ---- h--- ---- ---- ---- = Hidden
  ---- ---- --cc cccc ---- ---- ---- ---- = Color (0 - $3f)
  pppp ---- ---- ---- ---- ---- ---- ---- = Priority (0-$f)
  ---- ???? ??-- ---- ---- ---- ---- ---- = Unknown / Unused

  Scroll Reg

  0         1         2         3
  xxxx xxxx x--- ---- ---- ---- ---- ---- = X position
  ---- ---- ---- ---- yyyy yyyy y--- ---- = Y position
  ---- ---- -??? ???? ---- ---- -??? ???? = Unknown / Unused

  And the layers :
  0         1         2         3
  ---- ---- ---- ---- -ttt tttt tttt tttt = Tile number (0 - $7fff)
  ---- ---- ---- ---- h--- ---- ---- ---- = Hidden
  ---- ---- --cc cccc ---- ---- ---- ---- = Color (0 - $3f)
  pppp ---- ---- ---- ---- ---- ---- ---- = Priority (0-$f)
  ---- ???? ??-- ---- ---- ---- ---- ---- = Unknown / Unused

   */

   for(layer=0; layer<4; layer++){

     if(! check_layer_enabled(layer_id_data[layer]))
       continue;
     tile_mask = tp1vcu[0].tile_mask_bg;

     RAM_BG = tp1vcu[0].VRAM + vram_ofs[romset][layer];

     x1 = ReadWord(&tp1vcu[0].SCROLL[0+(layer<<2)])>>7;
     // There was an exception for outzone (romset 2)
     // But it's better without it !
     x1 += 0x1ef + 6-2*layer - bg_x_ofs;
     // x1 += x_ofs[layer];
     x1 &= 0x1FF;

     y1 = ReadWord(&tp1vcu[0].SCROLL[2+(layer<<2)])>>7;
     y1 += (0x101 - bg_y_ofs) + dy;
     y1 &= 0x1FF;

     //-(scr_ofs[romset][0+(layer<<1)]),
     //-(scr_ofs[romset][1+(layer<<1)])

     MAKE_SCROLL_512x512_4_8(
			     x1,
			     y1
			     );

     START_SCROLL_512x512_4_8(32,32,320,240);

     pri = ReadWord(&RAM_BG[zz]);
     if (!pri) pri=1;

     ta = ReadWord(&RAM_BG[2+zz]);

     if (!(ta & 0x8000)) { // hidden, thanks to mame
       ta &= tile_mask;

       if (romset == 5 && layer == 0) {
	 int my_pri = RAM_BG[zz+1]>>4;
	 if (my_pri<=1) {
	   // This removes all the annoying black squares in the background
	   MAP_PALETTE_MAPPED_NEW(
				  pri&0x3F,
				  16,
				  MAP
				  );

	   pri = (pri >> 11) & 0x1E;
	   Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,MAP);
	 }
       } else if(GFX_BG0_SOLID[ta]!=0){

	 MAP_PALETTE_MAPPED_NEW(
				pri&0x3F,
				16,
				MAP
				);

	 // priority : it's in the 4 highest bits, here bit 0 is kept to make the difference between
	 // layers (bit0 = 1) and sprites (bit0 = 0)
	 // this way sprites of same priority are drawn behind layers, it shows when entering a highscore in hellfire
	 // the letters are in a layer, and a sprite with the same priority serves as a cursor. Here if you draw the sprite over the layer, you hide the character.
	 // So I draw the layer on top, didn't find any place where it's a problem yet, there shouldn't be any.
	 pri = ((pri >> 11) & 0x1E)|1;
	 QueueTile(ta, x, y, MAP, pri);
#if 0
       } else {
	 /* I could not find any place yet where it's necessary.
	    All this comes from mame. I leave it here in case one day it's usefull */
	 else { // toaplan1 "usual"
	   if ((layer == 3 && my_pri==0) ||
	       (layer == 0 && my_pri >= 8)) { // thanks again to mame for that
	     MAP_PALETTE_MAPPED_NEW(
				    pri&0x3F,
				    16,
				    MAP
				    );

	     pri = (pri >> 11) & 0x1E;
	     Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,MAP);
	   }
	 }
#endif
       }
     } // hidden

     END_SCROLL_512x512_4_8();

   } // for

   // OBJECT

   if(check_layer_enabled(layer_id_data[4])) {
     tile_mask = tp1vcu[0].tile_mask_obj;

     RAM_BG  = tp1vcu[0].RAM_OBJ;
     RAM_BG2 = tp1vcu[0].RAM_OBJ+0x800;

     zz = 0x7F8;
     do{
       ctrl = ReadWord(&RAM_BG[zz+2]);

       pri = ReadWord(&RAM_BG2[(ctrl>>5)&0x7E]);

       if(pri&0xFF){

	 ta = (ReadWord(&RAM_BG[zz+0])&tile_mask);

	 x = ((ReadWord(&RAM_BG[zz+4])>>7)+32) & OBJ_X_MASK;
	 y = ((ReadWord(&RAM_BG[zz+6])>>7)+32-dy) & OBJ_Y_MASK;

	 MAP_PALETTE_MAPPED_NEW(
				(ctrl&0x3F)|0x40,
				16,
				MAP
				);

	 xxx = (pri>>0) & 0x0F;
	 yyy = (pri>>4) & 0x0F;

	 pri = ((ctrl >> 11) & 0x1E);

	 xxxx=x;
	 while((--yyy)>=0){
	   x=xxxx;
	   xx=xxx;
	   while((--xx)>=0){

	     if(GFX_SPR_SOLID[ta]!=0){

	       if((x>24)&&(y>24)&&(x<320+32)&&(y<240+32)){
		 QueueTile(ta, x, y, MAP, pri);
	       }

	     }

	     ta++;
	     x = (x + 8) & OBJ_X_MASK;
	   };
	   y = (y + 8) & OBJ_Y_MASK;
	 };

       }

     }while((zz-=8)>=0);
   } // if sprites enabled

   DrawTileQueue();
}
static struct VIDEO_INFO video_fireshrk =
{
   DrawToaplan1,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   toaplan1_gfx,
   57.61
};
static struct VIDEO_INFO video_hellfire =
{
   DrawToaplan1,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   toaplan1_gfx,
   57.61
};
static struct VIDEO_INFO video_outzone =
{
   DrawToaplan1,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   toaplan1_gfx,
   55.16
};
static struct VIDEO_INFO video_rallybik =
{
   DrawToaplan1,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   rally_bike_gfx,
   55.16
};
static struct DIR_INFO dir_demonwld[] =
{
   { "demons_world", },
   { "demonwld", },
   { NULL, },
};
#define video_demonwld video_hellfire
#define execute_demonwld execute_outzone
GME( demonwld, "Demon's World / Horror story (set 1)", TOAPLAN, 1989, GAME_SHOOT,
	.board = "TP016",
);
CLNEI( demonwld2,demonwld,"Demon's World / Horror Story (set 3/old raine version)",TOAPLAN,1989, GAME_PLATFORM );
static struct DIR_INFO dir_fireshrk[] =
{
   { "fire_shark", },
   { "fireshrk", },
   { NULL, },
};
GME( fireshrk, "Fire Shark", TOAPLAN, 1990, GAME_SHOOT,
	.board = "TP017",
	.sound = NULL
);
static struct DIR_INFO dir_hellfire[] =
{
   { "hell_fire", },
   { "hellfire", },
   { NULL, },
};
GAME( hellfire, "Hell Fire", TOAPLAN, 1989, GAME_SHOOT,
	.dsw = dsw_hellfire,
	.video = &video_hellfire,
	.exec = execute_outzone,
	.board = "B90",
);
GMEI( outzone,"Out Zone",TOAPLAN,1990, GAME_SHOOT,
	.board = "TP018",);
CLNEI( outzoneh,outzone,"Out Zone (harder)",TOAPLAN,1990, GAME_SHOOT );
CLNEI( outzonec,outzone,"Out Zone (oldest set)",TOAPLAN,1990, GAME_SHOOT );
// CLNEI( outzonecv,outzone,"Out Zone (Zero Wing TP-015 PCB conversion)",TOAPLAN,1990, GAME_SHOOT );
static struct DIR_INFO dir_rallybik[] =
{
   { "rally_bike", },
   { "rallybik", },
   { "rallyb", },
   { NULL, },
};
GAME( rallybik, "Rally Bike", TOAPLAN, 1988, GAME_RACE | GAME_NOT_WORKING,
	.dsw = dsw_rallybik,
	.video = &video_rallybik,
	.exec = execute_outzone,
	.board = "TP012",
);
static struct DIR_INFO dir_samesame[] =
{
   { "same_same_same", },
   { "same3", },
   { "samesame", },
   { ROMOF("fireshrk"), },
   { CLONEOF("fireshrk"), },
   { NULL, },
};
CLNE(samesame, fireshrk, "Same Same Same", TOAPLAN, 1989, GAME_SHOOT,
	.dsw = dsw_samesame,
	.board = "TP017",
	.sound = NULL
);
static struct DIR_INFO dir_truxton[] =
{
   { "truxton", },
   { NULL, },
};
GAME( truxton, "Truxton / Tatsujin", TOAPLAN, 1988, GAME_SHOOT,
	.dsw = dsw_truxton,
	.video = &video_fireshrk,
	.exec = execute_outzone,
	.board = "B65",
);
#define execute_vimana execute_outzone
#define video_vimana video_fireshrk
static struct DIR_INFO dir_vimana[] =
{
   { "vimana2", },
   { "vimana", },
   { NULL, },
};
GAME( vimana, "Vimana (world set 1)", TOAPLAN, 1991, GAME_SHOOT,
	.dsw = dsw_vimana,
	.video = &video_fireshrk,
	.exec = execute_outzone,
	.board = "TP019",
);
CLNEI(vimanaj, vimana, "Vimana (Japan)", TOAPLAN, 1991, GAME_SHOOT,
	.board = "TP019",
);
static struct DIR_INFO dir_zerowing[] =
{
   { "zero_wing", },
   { "zerowing", },
   { NULL, },
};
GAME( zerowing, "Zero Wing (2p set)", TOAPLAN, 1989, GAME_SHOOT,
	.dsw = dsw_zerowing,
	.video = &video_hellfire,
	.exec = execute_outzone,
	.board = "TP015",
);

