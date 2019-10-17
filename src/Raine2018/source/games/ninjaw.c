#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                  NINJA WARRIORS (C) 1987 TAITO CORPORATION                 */
/*                                                                            */
/*                     DARIUS 2 (C) 1989 TAITO CORPORATION                    */
/*                                                                            */
/******************************************************************************
 * Description of the hardware from mame :
 *
The triple screen games operate on hardware with various similarities to
the Taito F2 system, as they share some custom ics e.g. the TC0100SCN.

According to Sixtoe: "The multi-monitor systems had 2 or 3 13" screens;
one in the middle facing the player, and the other 1 or 2 on either side
mounted below and facing directly up reflecting off special semi-reflecting
mirrors, with about 1" of the graphics being overlapped on each screen.
This was the only way to get uninterrupted screens and to be able to see
through both ways. Otherwise you`d have the monitors' edges visible.
You can tell if your arcade has been cheap (like one near me) when you
look at the screens and can see black triangles on the left or right, this
means they bought ordinary mirrors and you can't see through them the
wrong way, as the semi-reflecting mirrors were extremely expensive."

For each screen the games have 3 separate layers of graphics:- one
128x64 tiled scrolling background plane of 8x8 tiles, a similar
foreground plane, and a 128x32 text plane with character definitions
held in ram.

Writing to the first TC0100SCN "writes through" to the two subsidiary
chips so that all three have identical contents. The subsidiary ones are
only addressed individually during initial memory checks, I think. (?)

There is a single sprite plane which covers all 3 screens.
The sprites are 16x16 and are not zoomable.

Twin 68000 processors are used; both have access to sprite ram and
the tilemap areas, and they communicate via 64K of shared ram.

Sound is dealt with by a Z80 controlling a YM2610. Sound commands
are written to the Z80 by the 68000 (the same as in Taito F2 games).


Tilemaps
========

TC0100SCN has tilemaps twice as wide as usual. The two BG tilemaps take
up twice the usual space, $8000 bytes each. The text tilemap takes up
the usual space, because its height is halved.

The triple palette generator (one for each screen) is probably just a
result of the way the hardware works: the colors in each are the same.

*/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "2610intf.h"
#include "taitosnd.h"
#include "timer.h"

/*

Todo:

- Priorities later in Ninja Warriors (easy)
- Line-line scroll (not so easy without losing speed)
- Why do the games not use the same ym2610 frame?

*/

/******************
   NINJA WARRIORS
 ******************/


static struct ROM_INFO rom_ninjaw[] =
{
   {       "b31_27.31", 0x00010000, 0x2f3ff642, 0, 0, 0, },
   {       "b31_29.34", 0x00010000, 0xf2941a37, 0, 0, 0, },
   {       "b31_31.85", 0x00010000, 0x837f47e2, 0, 0, 0, },
   {       "b31_32.86", 0x00010000, 0xe6025fec, 0, 0, 0, },
   {       "b31_33.87", 0x00010000, 0x6ce9af44, 0, 0, 0, },
   {       "b31_34.95", 0x00010000, 0xd6b5fb2a, 0, 0, 0, },
   {       "b31_35.96", 0x00010000, 0x70d9a89f, 0, 0, 0, },
   {       "b31_36.97", 0x00010000, 0xba20b0d4, 0, 0, 0, },
   {       "b31_37.11", 0x00020000, 0x0ca5799d, 0, 0, 0, },
   {       "b31_38.3", 0x00020000, 0xbc68cd99, 0, 0, 0, },
   {       "b31_39.2", 0x00020000, 0xe9197c3c, 0, 0, 0, },
   {       "b31_40.6", 0x00020000, 0x2ce0f24e, 0, 0, 0, },
   {       "b31_41.5", 0x00020000, 0x0daef28a, 0, 0, 0, },
   {       "b31-45", 0x00010000, 0x107902c3, 0, 0, 0, },
   {       "b31-47", 0x00010000, 0xbd536b1e, 0, 0, 0, },
   {       "b31-01.23", 0x00080000, 0x8e8237a7, 0, 0, 0, },
   {       "b31-02.24", 0x00080000, 0x4c3b4e33, 0, 0, 0, },
   {       "b31-04.173", 0x00080000, 0x2e1e4cb5, 0, 0, 0, },
   {       "b31-05.174", 0x00080000, 0x0a1fc9fb, 0, 0, 0, },
   {       "b31-06.175", 0x00080000, 0x0d59439e, 0, 0, 0, },
   {       "b31-07.176", 0x00080000, 0x33568cdb, 0, 0, 0, },
  { "b31-09.18", 0x80000, 0x60a73382, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "b31-10.17", 0x80000, 0xc6434aef, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "b31-11.16", 0x80000, 0x8da531d4, REGION_SMP1, 0x100000, LOAD_NORMAL },
  { "b31-08.19", 0x80000, 0xa0a1f87d, REGION_SMP2, 0x000000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ninjaw[] =
{
   INP1( COIN1, 0x03B004, 0x04 ),
   INP1( COIN2, 0x03B004, 0x08 ),
   INP0( TILT, 0x03B00E, 0x02 ),
   INP0( SERVICE, 0x03B00E, 0x01 ),

   INP0( P1_START, 0x03B00E, 0x04 ),
   INP0( P1_UP, 0x03B006, 0x01 ),
   INP0( P1_DOWN, 0x03B006, 0x02 ),
   INP0( P1_LEFT, 0x03B006, 0x08 ),
   INP0( P1_RIGHT, 0x03B006, 0x04 ),
   INP0( P1_B1, 0x03B00E, 0x10 ),
   INP0( P1_B2, 0x03B00E, 0x20 ),

   INP0( P2_START, 0x03B00E, 0x08 ),
   INP0( P2_UP, 0x03B006, 0x10 ),
   INP0( P2_DOWN, 0x03B006, 0x20 ),
   INP0( P2_LEFT, 0x03B006, 0x80 ),
   INP0( P2_RIGHT, 0x03B006, 0x40 ),
   INP0( P2_B1, 0x03B00E, 0x40 ),
   INP0( P2_B2, 0x03B00E, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_ninja_warriors_0[] =
{
   { MSG_CONTINUE_PLAY,       0x01, 0x02 },
   { MSG_ON,                  0x01},
   { MSG_OFF,                 0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
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

static struct DSW_DATA dsw_data_ninja_warriors_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ninjaw[] =
{
   { 0x03B000, 0xFF, dsw_data_ninja_warriors_0 },
   { 0x03B002, 0xFF, dsw_data_ninja_warriors_1 },
   { 0,        0,    NULL,      },
};

/*
static struct ROMSW_DATA romsw_data_ninja_warriors_0[] =
{
   { "Taito Worldwide",       0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};
*/

/*
static struct ROMSW_INFO ninja_warriors_romsw[] =
{
   { 0x01FFFF, 0x03, romsw_data_ninja_warriors_0 },
   { 0,        0,    NULL },
};
*/



/************************
   NINJA WARRIORS JAPAN
 ************************/


static struct ROM_INFO rom_ninjawj[] =
{
   {       "b31_27.31", 0x00010000, 0x2f3ff642, 0, 0, 0, },
   {       "b31_29.34", 0x00010000, 0xf2941a37, 0, 0, 0, },
   {       "b31_31.85", 0x00010000, 0x837f47e2, 0, 0, 0, },
   {       "b31_32.86", 0x00010000, 0xe6025fec, 0, 0, 0, },
   {       "b31_33.87", 0x00010000, 0x6ce9af44, 0, 0, 0, },
   {       "b31_34.95", 0x00010000, 0xd6b5fb2a, 0, 0, 0, },
   {       "b31_35.96", 0x00010000, 0x70d9a89f, 0, 0, 0, },
   {       "b31_36.97", 0x00010000, 0xba20b0d4, 0, 0, 0, },
   {       "b31_37.11", 0x00020000, 0x0ca5799d, 0, 0, 0, },
   {       "b31_38.3", 0x00020000, 0xbc68cd99, 0, 0, 0, },
   {       "b31_39.2", 0x00020000, 0xe9197c3c, 0, 0, 0, },
   {       "b31_40.6", 0x00020000, 0x2ce0f24e, 0, 0, 0, },
   {       "b31_41.5", 0x00020000, 0x0daef28a, 0, 0, 0, },
   {   "b31_30.35", 0x00010000, 0x056edd9f, 0, 0, 0, },
   {   "b31_28.32", 0x00010000, 0xcfa7661c, 0, 0, 0, },
   {       "b31-01.23", 0x00080000, 0x8e8237a7, 0, 0, 0, },
   {       "b31-02.24", 0x00080000, 0x4c3b4e33, 0, 0, 0, },
   {       "b31-04.173", 0x00080000, 0x2e1e4cb5, 0, 0, 0, },
   {       "b31-05.174", 0x00080000, 0x0a1fc9fb, 0, 0, 0, },
   {       "b31-06.175", 0x00080000, 0x0d59439e, 0, 0, 0, },
   {       "b31-07.176", 0x00080000, 0x33568cdb, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_ninja_warriors_jp_0[] =
{
   { MSG_CONTINUE_PLAY,       0x01, 0x02 },
   { MSG_ON,                  0x01},
   { MSG_OFF,                 0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
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

static struct DSW_INFO dsw_ninjawj[] =
{
   { 0x03B000, 0xFF, dsw_data_ninja_warriors_jp_0 },
   { 0x03B002, 0xFF, dsw_data_ninja_warriors_1 },
   { 0,        0,    NULL,      },
};


/************
   DARIUS 2
 ************/


static struct YM2610interface ym2610_interface =
{
  1,
  8000000,
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { z80_irq_handler },
  { REGION_SOUND2 },			// delta-t
  { REGION_SOUND1 },			// adpcm
  { YM3012_VOL(255,OSD_PAN_LEFT,255,OSD_PAN_RIGHT) },
};

static struct SOUND_INFO sound_darius2[] =
{
   { SOUND_YM2610,  &ym2610_interface,	},
   { 0, 	    NULL,		},
};

static struct ROM_INFO rom_darius2[] =
{
   {       "c07-01", 0x00080000, 0x3cf0f050, 0, 0, 0, },
   {       "c07-02", 0x00080000, 0x75d16d4b, 0, 0, 0, },
   {       "c07-03.12", 0x00080000, 0x189bafce, 0, 0, 0, },
   {       "c07-04.11", 0x00080000, 0x50421e81, 0, 0, 0, },
  { "c07-10.95", 0x80000, 0x4bbe0ed9, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "c07-11.96", 0x80000, 0x3c815699, REGION_SMP1, 0x80000, LOAD_NORMAL },
  { "c07-12.107", 0x80000, 0xe0b71258, REGION_SMP2, 0x00000, LOAD_NORMAL },
   {       "c07-27", 0x00020000, 0x0a6f7b6c, 0, 0, 0, },
   {       "c07-25", 0x00020000, 0x059f40ce, 0, 0, 0, },
   {       "c07-26", 0x00020000, 0x1f411242, 0, 0, 0, },
   {       "c07-24", 0x00020000, 0x486c9c20, 0, 0, 0, },
   {       "c07-28", 0x00020000, 0xda304bc5, 0, 0, 0, },
   {     "c07-29-1", 0x00010000, 0x48de567f, 0, 0, 0, },
   {     "c07-30-1", 0x00010000, 0x6122e400, 0, 0, 0, },
   {     "c07-31-1", 0x00010000, 0x8279d2f8, 0, 0, 0, },
   {     "c07-32-1", 0x00010000, 0x216c8f6a, 0, 0, 0, },
   {     "c07-33-1", 0x00010000, 0x2da03a3f, 0, 0, 0, },
   {     "c07-34-1", 0x00010000, 0x296984b8, 0, 0, 0, },
   {     "c07-35-1", 0x00010000, 0xdd8c4723, 0, 0, 0, },
   {     "c07-36-1", 0x00010000, 0x02cf2b1c, 0, 0, 0, },
   {     "c07-37-1", 0x00010000, 0x8b7d461f, 0, 0, 0, },
   {     "c07-38-1", 0x00010000, 0x46afb85c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_darius_2_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { _("Continuous Fire"),       0x02, 0x02 },
   { MSG_NORMAL,              0x02},
   { _("Fast"),                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
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

static struct DSW_DATA dsw_data_darius_2_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("Every 700k"),            0x0C},
   { _("Every 800k"),            0x08},
   { _("Every 900k"),            0x04},
   { _("Every 500k"),            0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "6",                     0x00},
   { MSG_CHEAT,               0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_CONTINUE_PLAY,       0x80, 0x02 },
   { MSG_ON,                  0x80},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_darius2[] =
{
   { 0x03B000, 0xFF, dsw_data_darius_2_0 },
   { 0x03B002, 0xFF, dsw_data_darius_2_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_darius_2_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America (Sagaia)", 0x02 },
   { "Taito Japan (Sagaia)",   0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_darius2[] =
{
   { 0x03FFFF, 0x01, romsw_data_darius_2_0 },
   { 0,        0,    NULL },
};


static int romset;

static UINT8 *RAM2;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *RAM_INPUT;

static void load_ninjaw(void)
{
   int ta,tb,tc,td;
   UINT8 *TMP;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(4.5,60));
   romset = 0;

   if(!(TMP=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x600000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x200000;

   tb=0;
   if(!load_rom("b31-01.23", TMP, 0x80000)) return;		// 8x8 BACKGROUND TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      tb+=4;
   }
   if(!load_rom("b31-02.24", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      tb+=4;
   }
   if(!load_rom("b31-07.176", TMP, 0x80000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x80000;ta+=0){
      for(td=0;td<2;td++){
      tc=TMP[ta++];
      GFX[tb+3]=(((tc&0x80)>>7)<<1);
      GFX[tb+2]=(((tc&0x40)>>6)<<1);
      GFX[tb+1]=(((tc&0x20)>>5)<<1);
      GFX[tb+0]=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tc=TMP[ta++];
      GFX[tb+3]|=(((tc&0x80)>>7)<<3);
      GFX[tb+2]|=(((tc&0x40)>>6)<<3);
      GFX[tb+1]|=(((tc&0x20)>>5)<<3);
      GFX[tb+0]|=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=4;
      }
      tb+=8;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("b31-06.175", TMP, 0x80000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x80000;ta+=0){
      for(td=0;td<2;td++){
      tc=TMP[ta++];
      GFX[tb+3]=(((tc&0x80)>>7)<<1);
      GFX[tb+2]=(((tc&0x40)>>6)<<1);
      GFX[tb+1]=(((tc&0x20)>>5)<<1);
      GFX[tb+0]=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tc=TMP[ta++];
      GFX[tb+3]|=(((tc&0x80)>>7)<<3);
      GFX[tb+2]|=(((tc&0x40)>>6)<<3);
      GFX[tb+1]|=(((tc&0x20)>>5)<<3);
      GFX[tb+0]|=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=4;
      }
      tb+=8;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("b31-05.174", TMP, 0x80000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x80000;ta+=0){
      for(td=0;td<2;td++){
      tc=TMP[ta++];
      GFX[tb+3]=(((tc&0x80)>>7)<<1);
      GFX[tb+2]=(((tc&0x40)>>6)<<1);
      GFX[tb+1]=(((tc&0x20)>>5)<<1);
      GFX[tb+0]=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tc=TMP[ta++];
      GFX[tb+3]|=(((tc&0x80)>>7)<<3);
      GFX[tb+2]|=(((tc&0x40)>>6)<<3);
      GFX[tb+1]|=(((tc&0x20)>>5)<<3);
      GFX[tb+0]|=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=4;
      }
      tb+=8;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("b31-04.173", TMP, 0x80000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x80000;ta+=0){
      for(td=0;td<2;td++){
      tc=TMP[ta++];
      GFX[tb+3]=(((tc&0x80)>>7)<<1);
      GFX[tb+2]=(((tc&0x40)>>6)<<1);
      GFX[tb+1]=(((tc&0x20)>>5)<<1);
      GFX[tb+0]=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tc=TMP[ta++];
      GFX[tb+3]|=(((tc&0x80)>>7)<<3);
      GFX[tb+2]|=(((tc&0x40)>>6)<<3);
      GFX[tb+1]|=(((tc&0x20)>>5)<<3);
      GFX[tb+0]|=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=4;
      }
      tb+=8;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   FreeMem(TMP);

   RAMSize=0xA0000;

   if(!(ROM=AllocateMem(0x120000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2=RAM+0x40000;

   if(!load_rom_index(13, RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(14, RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("b31_29.34", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("b31_27.31", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("b31_41.5", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("b31_39.2", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }
   if(!load_rom("b31_40.6", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom("b31_38.3", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   if(!load_rom("b31_33.87", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xC0000]=RAM[ta];
   }
   if(!load_rom("b31_36.97", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xC0001]=RAM[ta];
   }
   if(!load_rom("b31_32.86", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xE0000]=RAM[ta];
   }
   if(!load_rom("b31_35.96", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xE0001]=RAM[ta];
   }
   if(!load_rom("b31_31.85", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x100000]=RAM[ta];
   }
   if(!load_rom("b31_34.95", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x100001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x80000;
   if(!load_rom("b31_37.11", Z80ROM, 0x20000)) return;		// Z80 SOUND ROM

   AddTaitoYM2610(0x0345, 0x02B7, 0x20000);

   /*-----------------------*/

   // This one avoids to send an explicit start command to the 2nd 68k (cpua_w)
   // this is used only at start of the game, so it's easier to just disable it
   ROM[0x199C]=0x4E;	// Fix small 68000 communication problem
   ROM[0x199D]=0x71;

   ROM[0x07BA]=0x13;		// move.b #$00,$AA0000
   ROM[0x07BB]=0xFC;		// Speed Hack
   ROM[0x07BC]=0x00;
   ROM[0x07BD]=0x00;
   ROM[0x07BE]=0x00;
   ROM[0x07BF]=0xAA;
   ROM[0x07C0]=0x00;
   ROM[0x07C1]=0x00;

   ROM[0x07C2]=0x60;
   ROM[0x07C3]=0xE2;

   ROM[0xC07A6]=0x13;		// move.b #$00,$AA0000
   ROM[0xC07A7]=0xFC;		// Speed Hack
   ROM[0xC07A8]=0x00;
   ROM[0xC07A9]=0x00;
   ROM[0xC07AA]=0x00;
   ROM[0xC07AB]=0xAA;
   ROM[0xC07AC]=0x00;
   ROM[0xC07AD]=0x00;

   ROM[0xC07AE]=0x60;
   ROM[0xC07AF]=0xEE;
   // WriteWord68k(&ROM[0xc0ad4],0x4e71); // fast start, don't wait for the other

   memset(RAM+0x00000,0x00,0x80000);

   GFX_FG0    = RAM+0x64000;
   RAM_INPUT  = RAM+0x3B000;

   tc0100scn[0].RAM     = RAM+0x21000-0x6000;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);
   tc0100scn_0_copy_gfx_fg0(ROM+0x22000, 0x1000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   init_tile_cachex4();
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   tc0110pcr_init_typeb(RAM+0x38000, 1, 0);
   tc0110pcr_init_typeb_2(RAM+0x39000, 1, 0);
   tc0110pcr_init_typeb_3(RAM+0x3A000, 1, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x38000, 0x100, 0x10, 0x8000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   memset(RAM_INPUT,0x00,0x20);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x120000);
   ByteSwap(RAM,0x50000);

   AddMemFetch(0x000000, 0x0BFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadByte(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadByte(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByte(0x200000, 0x200003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadWord(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadWord(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWord(0x340000, 0x340007, tc0110pcr_rw, NULL);			// COLOR RAM SCREEN A
   AddReadWord(0x350000, 0x350007, tc0110pcr_rw_2, NULL);		// COLOR RAM SCREEN B
   AddReadWord(0x360000, 0x360007, tc0110pcr_rw_3, NULL);		// COLOR RAM SCREEN C
   AddReadWord(0x200000, 0x200003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWord(0x220000, 0x220003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteByte(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteByte(0x280000, 0x293FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0x200000, 0x200003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteWord(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteWord(0x280000, 0x293FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0x340000, 0x340007, tc0110pcr_ww, NULL);		// COLOR RAM SCREEN A
   AddWriteWord(0x350000, 0x350007, tc0110pcr_ww_2, NULL);		// COLOR RAM SCREEN B
   AddWriteWord(0x360000, 0x360007, tc0110pcr_ww_3, NULL);		// COLOR RAM SCREEN C
   AddWriteWord(0x200000, 0x200003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWord(0x2A0000, 0x2A000F, NULL, RAM+0x03B100);		// SCROLL A
   AddWriteWord(0x2E0000, 0x2E000F, NULL, RAM+0x03B200);		// SCROLL B
   AddWriteWord(0x320000, 0x32000F, NULL, RAM+0x03B300);		// SCROLL C
   AddWriteWord(0x220000, 0x220003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...


   AddMemFetchMC68000B(0x000000, 0x05FFFF, ROM+0x0C0000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x05FFFF, NULL, ROM+0x0C0000);			// 68000 ROM
   AddReadByteMC68000B(0x080000, 0x08FFFF, NULL, RAM2+0x000000);		// SUB LOCAL RAM
   AddReadByteMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadByteMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadByteMC68000B(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByteMC68000B(0x200000, 0x200003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x05FFFF, NULL, ROM+0x0C0000);			// 68000 ROM
   AddReadWordMC68000B(0x080000, 0x08FFFF, NULL, RAM2+0x000000);		// SUB LOCAL RAM
   AddReadWordMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadWordMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadWordMC68000B(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWordMC68000B(0x340000, 0x340007, tc0110pcr_rw, NULL);			// COLOR RAM SCREEN A
   AddReadWordMC68000B(0x350000, 0x350007, tc0110pcr_rw_2, NULL);		// COLOR RAM SCREEN B
   AddReadWordMC68000B(0x360000, 0x360007, tc0110pcr_rw_3, NULL);		// COLOR RAM SCREEN C
   AddReadWordMC68000B(0x200000, 0x200003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x080000, 0x08FFFF, NULL, RAM2+0x000000);		// SUB LOCAL RAM
   AddWriteByteMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteByteMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteByteMC68000B(0x280000, 0x293FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByteMC68000B(0x200000, 0x200003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x080000, 0x08FFFF, NULL, RAM2+0x000000);		// SUB LOCAL RAM
   AddWriteWordMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteWordMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteWordMC68000B(0x280000, 0x293FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWordMC68000B(0x340000, 0x340007, tc0110pcr_ww, NULL);		// COLOR RAM SCREEN A
   AddWriteWordMC68000B(0x350000, 0x350007, tc0110pcr_ww_2, NULL);		// COLOR RAM SCREEN B
   AddWriteWordMC68000B(0x360000, 0x360007, tc0110pcr_ww_3, NULL);		// COLOR RAM SCREEN C
   AddWriteWordMC68000B(0x200000, 0x200003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void load_darius2(void)
{
   int ta,tb,tc,td;
   UINT8 *TMP;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(8,60));
   romset = 1;

   if(!(TMP=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x400000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x200000;

   tb=0;
   if(!load_rom("c07-03.12", TMP, 0x80000)) return;		// 8x8 BACKGROUND TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      tb+=4;
   }
   if(!load_rom("c07-04.11", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      tb+=4;
   }
   if(!load_rom("c07-01", TMP, 0x80000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x80000;ta+=0){
      for(td=0;td<2;td++){
      tc=TMP[ta++];
      GFX[tb+3]=(((tc&0x80)>>7)<<1);
      GFX[tb+2]=(((tc&0x40)>>6)<<1);
      GFX[tb+1]=(((tc&0x20)>>5)<<1);
      GFX[tb+0]=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tc=TMP[ta++];
      GFX[tb+3]|=(((tc&0x80)>>7)<<3);
      GFX[tb+2]|=(((tc&0x40)>>6)<<3);
      GFX[tb+1]|=(((tc&0x20)>>5)<<3);
      GFX[tb+0]|=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=4;
      }
      tb+=8;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("c07-02", TMP, 0x80000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x80000;ta+=0){
      for(td=0;td<2;td++){
      tc=TMP[ta++];
      GFX[tb+3]=(((tc&0x80)>>7)<<1);
      GFX[tb+2]=(((tc&0x40)>>6)<<1);
      GFX[tb+1]=(((tc&0x20)>>5)<<1);
      GFX[tb+0]=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tc=TMP[ta++];
      GFX[tb+3]|=(((tc&0x80)>>7)<<3);
      GFX[tb+2]|=(((tc&0x40)>>6)<<3);
      GFX[tb+1]|=(((tc&0x20)>>5)<<3);
      GFX[tb+0]|=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=4;
      }
      tb+=8;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   FreeMem(TMP);

   RAMSize=0xA0000+0x20000;

   if(!(ROM=AllocateMem(0x120000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;

   if(!load_rom("c07-32-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c07-29-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("c07-31-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("c07-30-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }

   //if(!load_rom("c07-09.bin", ROM+0x40000, 0x80000)) return;
   //ByteSwap(ROM+0x40000,0x80000);
   if(!load_rom("c07-27", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("c07-25", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }
   if(!load_rom("c07-26", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom("c07-24", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   if(!load_rom("c07-35-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xC0000]=RAM[ta];
   }
   if(!load_rom("c07-38-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xC0001]=RAM[ta];
   }
   if(!load_rom("c07-34-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xE0000]=RAM[ta];
   }
   if(!load_rom("c07-37-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xE0001]=RAM[ta];
   }
   if(!load_rom("c07-33-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x100000]=RAM[ta];
   }
   if(!load_rom("c07-36-1", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x100001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0xA0000;
   if(!load_rom("c07-28", Z80ROM, 0x20000)) return;		// Z80 SOUND ROM

   AddTaitoYM2610(0x0247, 0x01C7, 0x20000);

   /*-----------------------*/

   ROM[0x10F4]=0x60;	// Fix Main Checksum
   ROM[0x1172]=0x60;	// Fix Sub Checksum/communication problem

   ROM[0x11E4]=0x4E;	// jmp $300
   ROM[0x11E5]=0xF9;
   ROM[0x11E6]=0x00;
   ROM[0x11E7]=0x00;
   ROM[0x11E8]=0x03;
   ROM[0x11E9]=0x00;

   ROM[0x0300]=0x52;	// addq #1,$C10A0
   ROM[0x0301]=0x79;
   ROM[0x0302]=0x00;
   ROM[0x0303]=0x0C;
   ROM[0x0304]=0x10;
   ROM[0x0305]=0xA0;

   ROM[0x0306]=0x13;	// move.b #$00,$AA0000
   ROM[0x0307]=0xFC;	// Speed Hack
   ROM[0x0308]=0x00;
   ROM[0x0309]=0x00;
   ROM[0x030A]=0x00;
   ROM[0x030B]=0xAA;
   ROM[0x030C]=0x00;
   ROM[0x030D]=0x00;

   ROM[0x030E]=0x60;
   ROM[0x030F]=0x100-16;

   ROM[0xC0932]=0x60;	// Fix Sub Checksum

   ROM[0xC097E]=0x4E;	// jmp $300
   ROM[0xC097F]=0xF9;
   ROM[0xC0980]=0x00;
   ROM[0xC0981]=0x00;
   ROM[0xC0982]=0x03;
   ROM[0xC0983]=0x00;

   ROM[0xC0300]=0x52;	// addq #1,$C10A0
   ROM[0xC0301]=0x79;
   ROM[0xC0302]=0x00;
   ROM[0xC0303]=0x08;
   ROM[0xC0304]=0x0C;
   ROM[0xC0305]=0x94;

   ROM[0xC0306]=0x13;	// move.b #$00,$AA0000
   ROM[0xC0307]=0xFC;	// Speed Hack
   ROM[0xC0308]=0x00;
   ROM[0xC0309]=0x00;
   ROM[0xC030A]=0x00;
   ROM[0xC030B]=0xAA;
   ROM[0xC030C]=0x00;
   ROM[0xC030D]=0x00;

   ROM[0xC030E]=0x60;
   ROM[0xC030F]=0x100-16;

   memset(RAM+0x00000,0x00,0xA0000);

   GFX_FG0    = RAM+0x64000;
   RAM_INPUT  = RAM+0x3B000;

   tc0100scn[0].RAM     = RAM+0x21000-0x6000;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   init_tile_cachex4();
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);

   tc0110pcr_init_typeb(RAM+0x38000, 1, 0);
   tc0110pcr_init_typeb_2(RAM+0x39000, 1, 0);
   tc0110pcr_init_typeb_3(RAM+0x3A000, 1, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x38000, 0x80, 0x10, 0x8000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   memset(RAM_INPUT,0x00,0x20);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x120000);
   ByteSwap(RAM,0x60000);

   AddMemFetch(0x000000, 0x0BFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadByte(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadByte(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByte(0x200000, 0x200003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadWord(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadWord(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWord(0x340000, 0x340007, tc0110pcr_rw, NULL);			// COLOR RAM SCREEN A
   AddReadWord(0x350000, 0x350007, tc0110pcr_rw_2, NULL);		// COLOR RAM SCREEN B
   AddReadWord(0x360000, 0x360007, tc0110pcr_rw_3, NULL);		// COLOR RAM SCREEN C
   AddReadWord(0x200000, 0x200003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWord(0x2C0000, 0x2D3FFF, NULL, RAM+0x050000);			// CUSTOM2
   AddReadWord(0x300000, 0x313FFF, NULL, RAM+0x064000);			// CUSTOM3
   AddReadWord(0x220000, 0x220003, tc0140syt_read_main_68k, NULL);	// SOUND
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteByte(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteByte(0x280000, 0x290FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0x291000, 0x291FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x292000, 0x293FFF, NULL, RAM+0x022000);		// FG0 RAM
   AddWriteByte(0x200000, 0x200003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x0C0000, 0x0CFFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteWord(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteWord(0x280000, 0x290FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0x291000, 0x291FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x292000, 0x293FFF, NULL, RAM+0x022000);		// FG0 RAM
   AddWriteWord(0x340000, 0x340007, tc0110pcr_ww, NULL);		// COLOR RAM SCREEN A
   AddWriteWord(0x350000, 0x350007, tc0110pcr_ww_2, NULL);		// COLOR RAM SCREEN B
   AddWriteWord(0x360000, 0x360007, tc0110pcr_ww_3, NULL);		// COLOR RAM SCREEN C
   AddWriteWord(0x200000, 0x200003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWord(0x2A0000, 0x2A000F, NULL, RAM+0x03B100);		// SCROLL A
   AddWriteWord(0x2E0000, 0x2E000F, NULL, RAM+0x03B200);		// SCROLL B
   AddWriteWord(0x320000, 0x32000F, NULL, RAM+0x03B300);		// SCROLL C
   AddWriteWord(0x2C0000, 0x2D3FFF, NULL, RAM+0x050000);		// CUSTOM2
   AddWriteWord(0x300000, 0x313FFF, NULL, RAM+0x064000);		// CUSTOM3
   AddWriteWord(0x220000, 0x220003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...


   AddMemFetchMC68000B(0x000000, 0x05FFFF, ROM+0x0C0000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x05FFFF, NULL, ROM+0x0C0000);			// 68000 ROM
   AddReadByteMC68000B(0x080000, 0x08FFFF, NULL, RAM+0x040000);			// SUB LOCAL RAM
   AddReadByteMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadByteMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadByteMC68000B(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByteMC68000B(0x200000, 0x200003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x05FFFF, NULL, ROM+0x0C0000);			// 68000 ROM
   AddReadWordMC68000B(0x080000, 0x08FFFF, NULL, RAM+0x040000);			// SUB LOCAL RAM
   AddReadWordMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);			// COMMON RAM
   AddReadWordMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);			// OBJECT RAM
   AddReadWordMC68000B(0x280000, 0x293FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWordMC68000B(0x340000, 0x340007, tc0110pcr_rw, NULL);			// COLOR RAM SCREEN A
   AddReadWordMC68000B(0x350000, 0x350007, tc0110pcr_rw_2, NULL);		// COLOR RAM SCREEN B
   AddReadWordMC68000B(0x360000, 0x360007, tc0110pcr_rw_3, NULL);		// COLOR RAM SCREEN C
   AddReadWordMC68000B(0x200000, 0x200003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x080000, 0x08FFFF, NULL, RAM+0x040000);		// SUB LOCAL RAM
   AddWriteByteMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteByteMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteByteMC68000B(0x280000, 0x290FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByteMC68000B(0x291000, 0x291FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByteMC68000B(0x292000, 0x293FFF, NULL, RAM+0x022000);		// FG0 RAM
   AddWriteByteMC68000B(0x200000, 0x200003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x080000, 0x08FFFF, NULL, RAM+0x040000);		// SUB LOCAL RAM
   AddWriteWordMC68000B(0x240000, 0x24FFFF, NULL, RAM+0x024000);		// COMMON RAM
   AddWriteWordMC68000B(0x260000, 0x263FFF, NULL, RAM+0x034000);		// OBJECT RAM
   AddWriteWordMC68000B(0x280000, 0x290FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWordMC68000B(0x291000, 0x291FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWordMC68000B(0x292000, 0x293FFF, NULL, RAM+0x022000);		// FG0 RAM
   AddWriteWordMC68000B(0x340000, 0x340007, tc0110pcr_ww, NULL);		// COLOR RAM SCREEN A
   AddWriteWordMC68000B(0x350000, 0x350007, tc0110pcr_ww_2, NULL);		// COLOR RAM SCREEN B
   AddWriteWordMC68000B(0x360000, 0x360007, tc0110pcr_ww_3, NULL);		// COLOR RAM SCREEN C
   AddWriteWordMC68000B(0x200000, 0x200003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void execute_ninjaw(void)
{
   cpu_execute_cycles(CPU_68K_0,CPU_FRAME_MHz(12,60));
   cpu_interrupt(CPU_68K_0,4);

   cpu_execute_cycles(CPU_68K_1,CPU_FRAME_MHz(12,60));
   cpu_interrupt(CPU_68K_1,4);

   execute_z80_audio_frame();
}

static void draw_ninja_warriors(void)
{
   int x,y,ta,tb,zz,zzz,zzzz,x16,y16,spr_mask;
   UINT8 *map;

   ClearPaletteMap();

   // BG0
   // ---

   if(romset==0){

   MAKE_SCROLL_1024x512_4_8(
      38-(ReadWord(&RAM[0x3B100])),
      16-(ReadWord(&RAM[0x3B106]))
   );

   }
   else{

   MAKE_SCROLL_1024x512_4_8(
      38-(ReadWord(&RAM[0x3B100])+ReadWord(&RAM[0x20100])),  // Add one of the line-line offsets
      16-(ReadWord(&RAM[0x3B106]))
   );

   }

   clear_tile_cache();
   START_SCROLL_1024x512_4_8(32,32,864,224);

      ta = ReadWord(&RAM[0x10002+zz])&0x7FFF;
      tb = ta*4;

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x10000+zz]&0x7F,
         16,
         map
      );

      switch(RAM[0x10001+zz]&0xC0){
         case 0x00:
	   if (tile_cache[tb] && (cache_map[tb] == map)) {
	     Move8x8_Rot(tile_cache[tb],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb);
	     cache_map[tb] = map;
	   }
	   break;
         case 0x40:
	   if (tile_cache[tb+1] && (cache_map[tb+1] == map)) {
	     Move8x8_Rot(tile_cache[tb+1],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb+1);
	     cache_map[tb+1] = map;
	   }
	   break;
         case 0x80:
	   if (tile_cache[tb+2] && (cache_map[tb+2] == map)) {
	     Move8x8_Rot(tile_cache[tb+2],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb+2);
	     cache_map[tb+2] = map;
	   }
	   break;
         case 0xC0:
	   if (tile_cache[tb+3] && (cache_map[tb+3] == map)) {
	     Move8x8_Rot(tile_cache[tb+3],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb+3);
	     cache_map[tb+3] = map;
	   }
	   break;
      }

   END_SCROLL_1024x512_4_8();

   // BG1
   // ---

   MAKE_SCROLL_1024x512_4_8(
      38-(ReadWord(&RAM[0x3B102])),
      16-(ReadWord(&RAM[0x3B108]))
   );

   clear_tile_cache();
   START_SCROLL_1024x512_4_8(32,32,864,224);

   ta=ReadWord(&RAM[0x18002+zz])&0x7FFF;
   if(GFX_BG0_SOLID[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x18000+zz]&0x7F,
         16,
         map
      );

      if(GFX_BG0_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM[0x18001+zz]&0xC0){
            case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
            case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
         }
      }
      else{					// all pixels; solid
	tb = ta*4;
         switch(RAM[0x18001+zz]&0xC0){
	 case 0x00:
	   if (tile_cache[tb] && (cache_map[tb] == map)) {
	     Move8x8_Rot(tile_cache[tb],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb);
	     cache_map[tb] = map;
	   }
	   break;
	 case 0x40:
	   if (tile_cache[tb+1] && (cache_map[tb+1] == map)) {
	     Move8x8_Rot(tile_cache[tb+1],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb+1);
	     cache_map[tb+1] = map;
	   }
	   break;
	 case 0x80:
	   if (tile_cache[tb+2] && (cache_map[tb+2] == map)) {
	     Move8x8_Rot(tile_cache[tb+2],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb+2);
	     cache_map[tb+2] = map;
	   }
	   break;
	 case 0xC0:
	   if (tile_cache[tb+3] && (cache_map[tb+3] == map)) {
	     Move8x8_Rot(tile_cache[tb+3],x,y,NULL);
	   } else {
	     Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map);
	     add_tile_cache_Rot(NULL,x,y,tb+3);
	     cache_map[tb+3] = map;
	   }
	   break;
         }
      }

   }

   END_SCROLL_1024x512_4_8();

   // OBJECT
   // ------

   if(romset==0)
      spr_mask = 0x3FFF;
   else
      spr_mask = 0x1FFF;

   for(zz=0x37FF8;zz>=0x34000;zz-=8){
   x = ((-16)+ReadWord(&RAM[zz+0]))&0x3FF;
   y = (( 16)+ReadWord(&RAM[zz+2]))&0x1FF;

   if((x>16)&&(y>16)&&(x<864+32)&&(y<224+32)){

   ta=ReadWord(&RAM[zz+4])&spr_mask;

   if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[zz+7]&0x7F,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM[zz+6]&0x03){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);         break;
         case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);   break;
         case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);   break;
         case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         }
      }
      else{					// all pixels; solid
         switch(RAM[zz+6]&0x03){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);         break;
         case 0x01: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);   break;
         case 0x02: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);   break;
         case 0x03: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         }
      }

   }

   }

   }

   // FG0
   // ---

   MAKE_SCROLL_1024x256_2_8(
      38-(ReadWord(&RAM[0x3B104])),
      16-(ReadWord(&RAM[0x3B10A]))
   );

   START_SCROLL_1024x256_2_8(32,32,864,224);

      ta = ReadWord(&RAM[0x22000+zz]);

      if(ta&0x00FF){

         MAP_PALETTE_MAPPED_NEW(
            (ta>>8)&0x3F,
            4,
            map
         );

         switch(ta&0xC000){
            case 0x0000: Draw8x8_Trans_Mapped_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);        break;
            case 0x4000: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);  break;
            case 0x8000: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map);  break;
            case 0xC000: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_FG0[(ta&0x00FF)<<6],x,y,map); break;
         }

      }

   END_SCROLL_1024x256_2_8();

}

/*

280000 - 287FFF | BG0 (1024x512 - 4 bytes/tile)
288000 - 28FFFF | BG1 (1024x512 - 4 bytes/tile)
290000 - 2903FF | BG0 LINE
290400 - 2907FF | BG1 LINE
291000 - 291FFF | FG0 GFX (8x8x4 - 16 bytes/tile)
292000 - 293FFF | FG0 (1024x256 - 2 bytes/tile)

*/
static struct VIDEO_INFO video_ninjaw =
{
   draw_ninja_warriors,
   864,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_darius2[] =
{
   { "darius_2", },
   { "darius2", },
   { "darius2d", },
   { NULL, },
};
GAME( darius2, "Darius 2", TAITO, 1989, GAME_SHOOT,
	.input = input_ninjaw,
	.dsw = dsw_darius2,
	.romsw = romsw_darius2,
	.video = &video_ninjaw,
	.exec = execute_ninjaw,
	.long_name_jpn = "â_âëâCâAâXéQ",
	.board = "C07",
	.sound = sound_darius2,
);
static struct DIR_INFO dir_ninjaw[] =
{
   { "ninja_warriors", },
   { "ninjaw", },
   { NULL, },
};
GME( ninjaw, "Ninja Warriors", TAITO, 1987, GAME_BEAT,
	.long_name_jpn = "öEÄÒâEâHü[âèâAü[âY",
	.board = "B31",
);
static struct DIR_INFO dir_ninjawj[] =
{
   { "ninja_warriors_jp", },
   { "ninjawj", },
   { ROMOF("ninjaw"), },
   { CLONEOF("ninjaw"), },
   { NULL, },
};
CLNE( ninjawj,ninjaw, "Ninja Warriors (Japan)", TAITO, 1987, GAME_BEAT,
	.dsw = dsw_ninjawj,
	.long_name_jpn = "öEÄÒâEâHü[âèâAü[âY (Japan)",
	.board = "B31",
);

