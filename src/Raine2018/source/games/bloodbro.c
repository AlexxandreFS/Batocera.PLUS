/******************************************************************************/
/*                                                                            */
/*                    BLOOD BROS (C) 1990 TAD CORPORATION                     */
/*                                                                            */
/*                    WEST STORY (C) 1991 DATSU ALLIANCE                      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "3812intf.h"
#include "savegame.h"		// save/load game routines

static struct ROM_INFO rom_bloodbro[] =
{
   {    "bb_03.bin", 0x00020000, 0x18d3c460, 0, 0, 0, },
   {    "bb_01.bin", 0x00020000, 0x2d7e0fdf, 0, 0, 0, },
   {    "bb_02.bin", 0x00020000, 0xc0fdc3e4, 0, 0, 0, },
   {    "bb_04.bin", 0x00020000, 0xfd951c2c, 0, 0, 0, },
   {    "bb_05.bin", 0x00010000, 0x04ba6d19, 0, 0, 0, },
   {    "bb_06.bin", 0x00010000, 0x7092e35b, 0, 0, 0, },
   {    "bb_07.bin", 0x00010000, 0x411b94e8, 0, 0, 0, },
   {    "bb_08.bin", 0x00020000, 0xdeb1b975, 0, 0, 0, },
   {    "bloodb.bk", 0x00100000, 0x1aa87ee6, 0, 0, 0, },
   {   "bloodb.obj", 0x00100000, 0xd27c3952, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_bloodbro[] =
{
   INP0( COIN1, 0x020005, 0x10 ),
   INP0( TILT, 0x020005, 0x01 ),
   INP0( SERVICE, 0x020005, 0x02 ),

   INP0( P1_START, 0x020004, 0x01 ),
   INP0( P1_UP, 0x020002, 0x01 ),
   INP0( P1_DOWN, 0x020002, 0x02 ),
   INP0( P1_LEFT, 0x020002, 0x04 ),
   INP0( P1_RIGHT, 0x020002, 0x08 ),
   INP0( P1_B1, 0x020002, 0x10 ),
   INP0( P1_B2, 0x020002, 0x20 ),
   INP0( P1_B3, 0x020002, 0x40 ),

   INP0( P2_START, 0x020004, 0x10 ),
   INP0( P2_UP, 0x020003, 0x01 ),
   INP0( P2_DOWN, 0x020003, 0x02 ),
   INP0( P2_LEFT, 0x020003, 0x04 ),
   INP0( P2_RIGHT, 0x020003, 0x08 ),
   INP0( P2_B1, 0x020003, 0x10 ),
   INP0( P2_B2, 0x020003, 0x20 ),
   INP0( P2_B3, 0x020003, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_blood_bros_0[] =
{
   { _("Coin Mode"),             0x01, 0x02 },
   { "1",                     0x01},
   { "2",                     0x00},
   { _("Coinage Mode 1"),        0x1E, 0x10 },
   { MSG_1COIN_1PLAY,         0x1E},
   { MSG_2COIN_1PLAY,         0x1C},
   { MSG_3COIN_1PLAY,         0x1A},
   { MSG_4COIN_1PLAY,         0x18},
   { MSG_5COIN_1PLAY,         0x16},
   { MSG_6COIN_1PLAY,         0x14},
   { MSG_1COIN_2PLAY,         0x12},
   { MSG_1COIN_3PLAY,         0x10},
   { MSG_1COIN_4PLAY,         0x0E},
   { MSG_1COIN_5PLAY,         0x0C},
   { MSG_1COIN_6PLAY,         0x0A},
   { MSG_2COIN_3PLAY,         0x08},
   { MSG_3COIN_2PLAY,         0x06},
   { MSG_5COIN_3PLAY,         0x04},
   { MSG_8COIN_3PLAY,         0x02},
   { MSG_FREE_PLAY,              0x00},
   { _("Coin Start"),            0x20, 0x02 },
   { MSG_NORMAL,              0x20},
   { _("Double"),                0x00},
   { _("Rom Option"),            0xC0, 0x04 },
   { _("A"),                     0xC0},
   { _("B"),                     0x80},
   { _("C"),                     0x40},
   { _("D"),                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_blood_bros_1[] =
{
   { _("Lives"),                 0x03, 0x04 },
   { "3",                     0x03},
   { "2",                     0x02},
   { "5",                     0x01},
   { "1",                     0x00},
   { _("Bonus"),                 0x0C, 0x04 },
   { _("100k, every 200k"),      0x0C, 0x00 },
   { _("200k, every 300k"),      0x08, 0x00 },
   { _("500k only"),             0x04},
   { _("None"),                  0x00},
   { MSG_DIFFICULTY,          0x30, 0x04 },
   { MSG_NORMAL,              0x30},
   { MSG_EASY,                0x20},
   { MSG_HARD,                0x10},
   { MSG_HARDEST,             0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   DSW_DEMO_SOUND( 0x80, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_bloodbro[] =
{
   { 0x020000, 0xFF, dsw_data_blood_bros_0 },
   { 0x020001, 0xFF, dsw_data_blood_bros_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_weststry[] =
{
   {     "ws20.bin", 0x00020000, 0xf1245c16, 0, 0, 0, },
   {     "ws21.bin", 0x00020000, 0xe23d7296, 0, 0, 0, },
   {     "ws22.bin", 0x00020000, 0x7150a060, 0, 0, 0, },
   {     "ws23.bin", 0x00020000, 0x43d58e24, 0, 0, 0, },
   {     "ws24.bin", 0x00020000, 0x20a867ea, 0, 0, 0, },
   {     "ws25.bin", 0x00020000, 0x8092e8e9, 0, 0, 0, },
   {     "ws26.bin", 0x00020000, 0xf6a1f42c, 0, 0, 0, },
   {     "ws01.bin", 0x00020000, 0x32bda4bc, 0, 0, 0, },
   {     "ws02.bin", 0x00020000, 0xed9d682e, 0, 0, 0, },
   {     "ws03.bin", 0x00020000, 0x046b51f8, 0, 0, 0, },
   {     "ws04.bin", 0x00020000, 0x75f082e5, 0, 0, 0, },
   {     "ws05.bin", 0x00020000, 0x007c8dc0, 0, 0, 0, },
   {     "ws06.bin", 0x00020000, 0x459d075e, 0, 0, 0, },
   {     "ws07.bin", 0x00020000, 0x0f0c8d9a, 0, 0, 0, },
   {     "ws08.bin", 0x00020000, 0x4d6783b3, 0, 0, 0, },
   {     "ws13.bin", 0x00020000, 0x158e302a, 0, 0, 0, },
   {    "bb_04.bin", 0x00020000, 0xfd951c2c, 0, 0, 0, },
   {     "ws15.bin", 0x00020000, 0x672e9027, 0, 0, 0, },
   {    "bb_03.bin", 0x00020000, 0x18d3c460, 0, 0, 0, },
   {    "bb_08.bin", 0x00020000, 0xdeb1b975, 0, 0, 0, },
   {     "ws19.bin", 0x00020000, 0xc5dd0a96, 0, 0, 0, },
   {     "ws09.bin", 0x00010000, 0xf05b2b3e, 0, 0, 0, },
   {     "ws10.bin", 0x00010000, 0xefdf7c82, 0, 0, 0, },
   {     "ws11.bin", 0x00010000, 0x2b10e3d2, 0, 0, 0, },
   {     "ws12.bin", 0x00010000, 0xaf993578, 0, 0, 0, },
   {     "ws17.bin", 0x00010000, 0xe00a8f09, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_weststry[] =
{
   INP0( COIN1, 0x020004, 0x01 ),
   INP0( COIN2, 0x020004, 0x02 ),

   INP0( P1_START, 0x020004, 0x08 ),
   INP0( P1_UP, 0x020002, 0x01 ),
   INP0( P1_DOWN, 0x020002, 0x02 ),
   INP0( P1_LEFT, 0x020002, 0x04 ),
   INP0( P1_RIGHT, 0x020002, 0x08 ),
   INP0( P1_B1, 0x020002, 0x10 ),
   INP0( P1_B2, 0x020002, 0x20 ),
   INP0( P1_B3, 0x020002, 0x40 ),

   INP0( P2_START, 0x020004, 0x10 ),
   INP0( P2_UP, 0x020003, 0x01 ),
   INP0( P2_DOWN, 0x020003, 0x02 ),
   INP0( P2_LEFT, 0x020003, 0x04 ),
   INP0( P2_RIGHT, 0x020003, 0x08 ),
   INP0( P2_B1, 0x020003, 0x10 ),
   INP0( P2_B2, 0x020003, 0x20 ),
   INP0( P2_B3, 0x020003, 0x40 ),

   END_INPUT
};

static struct YM3812interface ym3812_interface =
{
   1,		// 1 chip
   3000000,	// 3 MHz  (emu only)
   { 255 },	// Volume (emu only)
   { NULL }
};

static struct SOUND_INFO sound_weststry[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { 0,             NULL,                 },
};


static void WriteSound68k(UINT32 address, UINT8 data)
{
	(void)(address);
	latch=data&0xFF;
      print_debug("68000 Sends:%02x\n",data);
   cpu_int_nmi(CPU_Z80_0);
   if(latch!=0){
   cpu_interrupt(CPU_Z80_0, 0x38);
   }
}

UINT16 WestStorySoundReadZ80(UINT16 offset)
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
         print_debug("Z80 Receives:%02x\n",latch);
         return latch;
      break;
      default:
         ta = 0xFF;
      break;
   }

   print_debug("Z80Read:%04x,%02x [%04x]\n",offset,ta,z80pc);
   return ta;
}

static void WestStorySoundWriteZ80(UINT16 offset, UINT8 data)
{
   switch(offset&0x1F){
      case 0x08:
      case 0x09:
         YM3812WriteZ80( (UINT16) (offset&1), data);
      break;
      default:
         print_debug("Z80Write:%04x,%02x [%04x]\n",offset,data,z80pc);
      break;
   }
}

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG1;
static UINT8 *GFX_SPR;
static UINT8 *GFX_FG0;

static UINT8 *GFX_BG0_SOLID;
static UINT8 *GFX_BG1_SOLID;
static UINT8 *GFX_SPR_SOLID;
static UINT8 *GFX_FG0_SOLID;

static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_SPR;
static UINT8 *RAM_FG0;

static UINT32 pal_bg0;
static UINT32 pal_bg1;
static UINT32 pal_spr;
static UINT32 pal_fg0;

static UINT8 *RAM_SCR;

static int romset;

static void load_weststry(void)
{
   int ta,tb,tc;

   romset = 1;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x440000))) return;

   GFX_BG0 = GFX + 0x100000;
   GFX_BG1 = GFX + 0x000000;
   GFX_SPR = GFX + 0x200000;
   GFX_FG0 = GFX + 0x400000;

   RAM_BG0 = RAM + 0x13000;
   RAM_BG1 = RAM + 0x12C00;
   RAM_SPR = RAM + 0x14000;
   RAM_FG0 = RAM + 0x13800;

   pal_bg0 = 0x30;
   pal_bg1 = 0x20;
   pal_spr = 0x00;
   pal_fg0 = 0x10;

   RAM_SCR = RAM + 0x05C34;

   if(!load_rom("ws04.bin", RAM+0x00000, 0x20000)) return;		// GFX BG1
   if(!load_rom("ws08.bin", RAM+0x20000, 0x20000)) return;		// GFX BG0
   if(!load_rom("ws19.bin", RAM+0x40000, 0x20000)) return;		// GFX SPR
   if(!load_rom("ws20.bin", RAM+0x60000, 0x20000)) return;		// GFX SPR
   for(ta=0;ta<0x10000;ta++){
      tb=RAM[ta+0x50000];
      RAM[ta+0x50000]=RAM[ta+0x60000];
      RAM[ta+0x60000]=tb;
   }
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
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("ws02.bin", RAM+0x00000, 0x20000)) return;		// GFX BG1
   if(!load_rom("ws06.bin", RAM+0x20000, 0x20000)) return;		// GFX BG0
   if(!load_rom("ws21.bin", RAM+0x40000, 0x20000)) return;		// GFX SPR
   if(!load_rom("ws22.bin", RAM+0x60000, 0x20000)) return;		// GFX SPR
   for(ta=0;ta<0x10000;ta++){
      tb=RAM[ta+0x50000];
      RAM[ta+0x50000]=RAM[ta+0x60000];
      RAM[ta+0x60000]=tb;
   }
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
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("ws03.bin", RAM+0x00000, 0x20000)) return;		// GFX
   if(!load_rom("ws07.bin", RAM+0x20000, 0x20000)) return;		// GFX
   if(!load_rom("ws23.bin", RAM+0x40000, 0x20000)) return;		// GFX
   if(!load_rom("ws24.bin", RAM+0x60000, 0x20000)) return;		// GFX
   for(ta=0;ta<0x10000;ta++){
      tb=RAM[ta+0x50000];
      RAM[ta+0x50000]=RAM[ta+0x60000];
      RAM[ta+0x60000]=tb;
   }
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
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("ws01.bin", RAM+0x00000, 0x20000)) return;		// GFX
   if(!load_rom("ws05.bin", RAM+0x20000, 0x20000)) return;		// GFX
   if(!load_rom("ws25.bin", RAM+0x40000, 0x20000)) return;		// GFX
   if(!load_rom("ws26.bin", RAM+0x60000, 0x20000)) return;		// GFX
   for(ta=0;ta<0x10000;ta++){
      tb=RAM[ta+0x50000];
      RAM[ta+0x50000]=RAM[ta+0x60000];
      RAM[ta+0x60000]=tb;
   }
   tb=0;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+0]|=((tc&0x80)>>7)<<3;
      GFX[tb+1]|=((tc&0x40)>>6)<<3;
      GFX[tb+2]|=((tc&0x20)>>5)<<3;
      GFX[tb+3]|=((tc&0x10)>>4)<<3;
      GFX[tb+4]|=((tc&0x08)>>3)<<3;
      GFX[tb+5]|=((tc&0x04)>>2)<<3;
      GFX[tb+6]|=((tc&0x02)>>1)<<3;
      GFX[tb+7]|=((tc&0x01)>>0)<<3;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta+0x40000];
      GFX[tb+0]|=((tc&0x80)>>7)<<3;
      GFX[tb+1]|=((tc&0x40)>>6)<<3;
      GFX[tb+3]|=((tc&0x20)>>5)<<3;	// REVERSED
      GFX[tb+2]|=((tc&0x10)>>4)<<3;
      GFX[tb+4]|=((tc&0x08)>>3)<<3;
      GFX[tb+5]|=((tc&0x04)>>2)<<3;
      GFX[tb+6]|=((tc&0x02)>>1)<<3;
      GFX[tb+7]|=((tc&0x01)>>0)<<3;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   for(ta=0;ta<0x200000;ta++){
      GFX[ta]^=15;
   }

   if(!load_rom("ws12.bin", RAM, 0x10000)) return;		// FG0 GFX
   tb=0x400000;
   for(ta=0x8000;ta<0x10000;ta++){
      tc=RAM[ta]^255;
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
   if(!load_rom("ws10.bin", RAM, 0x10000)) return;		// FG0 GFX
   tb=0x400000;
   for(ta=0x8000;ta<0x10000;ta++){
      tc=RAM[ta]^255;
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
   if(!load_rom("ws11.bin", RAM, 0x10000)) return;		// FG0 GFX
   tb=0x400000;
   for(ta=0x8000;ta<0x10000;ta++){
      tc=RAM[ta]^255;
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
   if(!load_rom("ws09.bin", RAM, 0x10000)) return;		// FG0 GFX
   tb=0x400000;
   for(ta=0x8000;ta<0x10000;ta++){
      tc=RAM[ta]^255;
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

   if(!load_rom("ws15.bin", RAM, 0x20000)) return;		// MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("ws13.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("bb_03.bin", RAM, 0x20000)) return;		// MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("bb_04.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x21000;
   if(!load_rom("ws17.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x012A]=0xD3;	// OUTA (AAh)
   Z80ROM[0x012B]=0xAA;	//

   SetStopZ80Mode2(0x012D);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x27FF, NULL,			NULL);	// Z80 ROM/RAM
   AddZ80AReadByte(0x8000, 0xFFFF, NULL,			NULL);	// Z80 ROM
   //AddZ80AReadByte(0x4008, 0x4009, YM3812ReadZ80,		NULL);	// YM3812
   AddZ80AReadByte(0x4000, 0x401F, WestStorySoundReadZ80,	NULL);	// 68000 + OTHER I/O
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);	// <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x2000, 0x27FF, NULL,			NULL);	// Z80 RAM
   //AddZ80AWriteByte(0x4008, 0x4009, YM3812WriteZ80,		NULL);	// YM3812
   AddZ80AWriteByte(0x4000, 0x401F, WestStorySoundWriteZ80,	NULL);	// 68000 + OTHER I/O
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);	// <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   /*---------------------------------*/

   memset(RAM+0x00000,0x00,0x20000);
   memset(RAM+0x20000,0xFF,0x01000);

   RAMSize=0x31000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x1000);
   GFX_BG1_SOLID = make_solid_mask_16x16(GFX_BG1, 0x1000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);
   GFX_FG0_SOLID = make_solid_mask_8x8  (GFX_FG0, 0x1000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr_rev);
   InitPaletteMap(RAM+0x18000, 0x40, 0x10, 0x1000);

   // 68000 Speed hack
   // ----------------

   WriteLong68k(&ROM[0x08E8],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x08EC],0x00AA0000);	//
   WriteLong68k(&ROM[0x08F0],0x4E714E71);	//

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x21000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x120000, 0x12FFFF, NULL, RAM+0x010000);			// VIDEO RAM
   AddReadByte(0x0C1000, 0x0C100F, NULL, RAM+0x020000);			// INPUT RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x120000, 0x12FFFF, NULL, RAM+0x010000);			// VIDEO RAM
   AddReadWord(0x0C1000, 0x0C100F, NULL, RAM+0x020000);			// INPUT RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x120000, 0x12FFFF, NULL, RAM+0x010000);		// VIDEO RAM
   AddWriteByte(0x0C1000, 0x0C1000, WriteSound68k, NULL);		// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x120000, 0x12FFFF, NULL, RAM+0x010000);		// VIDEO RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void ClearWestStry(void)
{
   /*#ifdef RAINE_DEBUG
      save_debug("ROM.bin",ROM,0x080000,1);
      save_debug("RAM.bin",RAM,0x040000,1);
      save_debug("GFX.bin",GFX,0x440000,0);
#endif*/
}

static void execute_weststry(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(10,60));	// M68000 10MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));	// Z80B 4MHz (60fps)
      print_debug("Z80PC0:%04x\n",z80pc);
   //cpu_interrupt(CPU_Z80_0, 0x38);
   //cpu_int_nmi(CPU_Z80_0);
}

UINT16 BloodBrosSoundReadZ80(UINT16 offset)
{
   UINT8 ta;

   switch(offset&31){
      /*case 0x08:
         ta=sp_status;
      break;
      case 0x0A:
         sp_status=0xFF;
         ta=latch;
            print_debug("Z80 Receives:%02x\n",latch);
      break;*/
      default:
         ta=0xFF;
      break;
   }

   print_debug("Z80Read:%04x,%02x [%04x]\n",offset,ta,z80pc);
   return(ta);
}

static void BloodBrosSoundWriteZ80(UINT16 offset, UINT8 data)
{
   switch(offset&31){
      default:
         print_debug("Z80Write:%04x,%02x [%04x]\n",offset,data,z80pc);
      break;
   }
}

static void load_bloodbro(void)
{
   int ta,tb,tc;

   romset = 0;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x440000))) return;

   GFX_BG0 = GFX + 0x040000;
   GFX_BG1 = GFX + 0x140000;
   GFX_SPR = GFX + 0x240000;
   GFX_FG0 = GFX + 0x000000;

   RAM_BG0 = RAM + 0x0C000;
   RAM_BG1 = RAM + 0x0D000;
   RAM_SPR = RAM + 0x0B000;
   RAM_FG0 = RAM + 0x0D800;

   pal_bg0 = 0x40;
   pal_bg1 = 0x50;
   pal_spr = 0x00;
   pal_fg0 = 0x70;

   RAM_SCR = RAM + 0x10020;

   if(!load_rom("bb_06.bin", RAM+0x00000, 0x10000)) return;	// FG0 GFX
   if(!load_rom("bb_05.bin", RAM+0x10000, 0x10000)) return;	// FG0 GFX
   tb=0;
   for(ta=0;ta<0x10000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+0x10000];
      GFX[tb+3]|=((tc&0x80)>>7)<<3;
      GFX[tb+2]|=((tc&0x40)>>6)<<3;
      GFX[tb+1]|=((tc&0x20)>>5)<<3;
      GFX[tb+0]|=((tc&0x10)>>4)<<3;
      GFX[tb+3]|=((tc&0x08)>>3)<<2;
      GFX[tb+2]|=((tc&0x04)>>2)<<2;
      GFX[tb+1]|=((tc&0x02)>>1)<<2;
      GFX[tb+0]|=((tc&0x01)>>0)<<2;
      tb+=4;
   }

   if(!load_rom("bloodb.bk", RAM, 0x100000)) return;	// BG0 GFX
   tb=0x40000;
   for(ta=0;ta<0x100000;ta+=4){
      tc=RAM[ta];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+1];
      GFX[tb+3]|=((tc&0x80)>>7)<<3;
      GFX[tb+2]|=((tc&0x40)>>6)<<3;
      GFX[tb+1]|=((tc&0x20)>>5)<<3;
      GFX[tb+0]|=((tc&0x10)>>4)<<3;
      GFX[tb+3]|=((tc&0x08)>>3)<<2;
      GFX[tb+2]|=((tc&0x04)>>2)<<2;
      GFX[tb+1]|=((tc&0x02)>>1)<<2;
      GFX[tb+0]|=((tc&0x01)>>0)<<2;
      tc=RAM[ta+2];
      GFX[tb+7]=((tc&0x80)>>7)<<1;
      GFX[tb+6]=((tc&0x40)>>6)<<1;
      GFX[tb+5]=((tc&0x20)>>5)<<1;
      GFX[tb+4]=((tc&0x10)>>4)<<1;
      GFX[tb+7]|=((tc&0x08)>>3)<<0;
      GFX[tb+6]|=((tc&0x04)>>2)<<0;
      GFX[tb+5]|=((tc&0x02)>>1)<<0;
      GFX[tb+4]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+3];
      GFX[tb+7]|=((tc&0x80)>>7)<<3;
      GFX[tb+6]|=((tc&0x40)>>6)<<3;
      GFX[tb+5]|=((tc&0x20)>>5)<<3;
      GFX[tb+4]|=((tc&0x10)>>4)<<3;
      GFX[tb+7]|=((tc&0x08)>>3)<<2;
      GFX[tb+6]|=((tc&0x04)>>2)<<2;
      GFX[tb+5]|=((tc&0x02)>>1)<<2;
      GFX[tb+4]|=((tc&0x01)>>0)<<2;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   if(!load_rom("bloodb.obj", RAM, 0x100000)) return;	// SPRITE GFX
   tb=0x240000;
   for(ta=0;ta<0x100000;ta+=4){
      tc=RAM[ta];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+1];
      GFX[tb+3]|=((tc&0x80)>>7)<<3;
      GFX[tb+2]|=((tc&0x40)>>6)<<3;
      GFX[tb+1]|=((tc&0x20)>>5)<<3;
      GFX[tb+0]|=((tc&0x10)>>4)<<3;
      GFX[tb+3]|=((tc&0x08)>>3)<<2;
      GFX[tb+2]|=((tc&0x04)>>2)<<2;
      GFX[tb+1]|=((tc&0x02)>>1)<<2;
      GFX[tb+0]|=((tc&0x01)>>0)<<2;
      tc=RAM[ta+2];
      GFX[tb+7]=((tc&0x80)>>7)<<1;
      GFX[tb+6]=((tc&0x40)>>6)<<1;
      GFX[tb+5]=((tc&0x20)>>5)<<1;
      GFX[tb+4]=((tc&0x10)>>4)<<1;
      GFX[tb+7]|=((tc&0x08)>>3)<<0;
      GFX[tb+6]|=((tc&0x04)>>2)<<0;
      GFX[tb+5]|=((tc&0x02)>>1)<<0;
      GFX[tb+4]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+3];
      GFX[tb+7]|=((tc&0x80)>>7)<<3;
      GFX[tb+6]|=((tc&0x40)>>6)<<3;
      GFX[tb+5]|=((tc&0x20)>>5)<<3;
      GFX[tb+4]|=((tc&0x10)>>4)<<3;
      GFX[tb+7]|=((tc&0x08)>>3)<<2;
      GFX[tb+6]|=((tc&0x04)>>2)<<2;
      GFX[tb+5]|=((tc&0x02)>>1)<<2;
      GFX[tb+4]|=((tc&0x01)>>0)<<2;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   for(ta=0;ta<0x440000;ta++){
      GFX[ta]^=15;
   }

   if(!load_rom("bb_01.bin", RAM, 0x20000)) return;	// MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("bb_02.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("bb_03.bin", RAM, 0x20000)) return;	// MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("bb_04.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x21000;
   if(!load_rom("bb_07.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x0123]=0xD3;	// OUTA (AAh)
   Z80ROM[0x0124]=0xAA;	//

   SetStopZ80Mode2(0x011A);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0010, 0x0018);

   AddZ80AReadByte(0x0000, 0x27FF, NULL,			NULL);	// Z80 ROM/RAM
   //AddZ80AReadByte(0x400E, 0x400F, YM2151ReadZ80,		NULL);	// YM2151 I/O
   AddZ80AReadByte(0x4000, 0x401F, BloodBrosSoundReadZ80,	NULL);	// 68000 + OTHER I/O
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);	// <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x2000, 0x27FF, NULL,			NULL);	// Z80 RAM
   //AddZ80AWriteByte(0x400E, 0x400F, YM2151WriteZ80,		NULL);	// YM2151 I/O
   AddZ80AWriteByte(0x4000, 0x401F, BloodBrosSoundWriteZ80,	NULL);	// 68000 + OTHER I/O
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);	// <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(-1, -1, NULL, NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2, NULL);
   AddZ80AWritePort(-1, -1, NULL, NULL);

   AddZ80AInit();

   /*---------------------------------*/

   memset(RAM+0x00000,0x00,0x20000);
   memset(RAM+0x20000,0xFF,0x01000);

   RAMSize=0x31000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x1000);
   GFX_BG1_SOLID = make_solid_mask_16x16(GFX_BG1, 0x1000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);
   GFX_FG0_SOLID = make_solid_mask_8x8  (GFX_FG0, 0x1000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr_rev);
   InitPaletteMap(RAM+0xE800, 0x80, 0x10, 0x1000);

   // Fix Sound Comm
   // --------------

   WriteWord68k(&ROM[0x0880],0x4E71);		// nop

   // 68000 Speed hack
   // ----------------

   WriteLong68k(&ROM[0x0988],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x098C],0x00AA0000);	//
   WriteLong68k(&ROM[0x0990],0x4E714E71);	//

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x14000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x0C0000, 0x0C01FF, NULL, RAM+0x010000);			// ??? RAM
   AddReadByte(0x0E0000, 0x0E000F, NULL, RAM+0x020000);			// INPUT RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x0C0000, 0x0C01FF, NULL, RAM+0x010000);			// ??? RAM
   AddReadWord(0x0E0000, 0x0E000F, NULL, RAM+0x020000);			// INPUT RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x0C0000, 0x0C01FF, NULL, RAM+0x010000);		// INPUT RAM
   AddWriteByte(0x0A0000, 0x0A0001, WriteSound68k, NULL);		// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x0C0000, 0x0C01FF, NULL, RAM+0x010000);		// INPUT RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_bloodbro(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(10,60));	// M68000 10MHz (60fps)
   cpu_interrupt(CPU_68K_0, 4);

   /*cpu_execute_cycles(CPU_Z80_0, 4000000/60);
      print_debug("Z80PC0:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_0, 0x0010);
   cpu_interrupt(CPU_Z80_0, 0x0018);*/
}

static void draw_blood_bros_object(int pri)
{
   int x,y,rx,ry,rxx,ryy,ryyy;
   int zz,ta;
   UINT8 *MAP;

   if(pri)

      pri = 0x80;

   for(zz=0xB7F8;zz>=0xB000;zz-=8){

   if((RAM[zz+1]&0x80) != pri){

   x=(32+ReadWord(&RAM[zz+4]))&0x1FF;
   y=(16+ReadWord(&RAM[zz+6]))&0x1FF;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   ta=ReadWord(&RAM[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         RAM[zz]&15,
         16,
         MAP
      );

      rx=(ReadWord(&RAM[zz])>>4)&7;
      ry=(ReadWord(&RAM[zz])>>7)&7;

      ryyy=y;

   switch(ReadWord(&RAM[zz])&0x6000){
   case 0x0000:
   for(ryy=0;ryy<=ry;ryy++){
   for(rxx=0;rxx<=rx;rxx++){

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,MAP);
   }

   ta++;
   y+=16;

   }
   x+=16;
   y=ryyy;
   }
   break;
   case 0x2000:
   x+=(ry<<4);
   for(ryy=0;ryy<=ry;ryy++){
   for(rxx=0;rxx<=rx;rxx++){

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,MAP);
   }

   ta++;
   y+=16;

   }
   x-=16;
   y=ryyy;
   }
   break;
   case 0x4000:
   for(ryy=0;ryy<=ry;ryy++){
   for(rxx=0;rxx<=rx;rxx++){

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,MAP);
   }

   ta++;
   y+=16;

   }
   x+=16;
   y=ryyy;
   }
   break;
   case 0x6000:
   x+=(ry<<4);
   for(ryy=0;ryy<=ry;ryy++){
   for(rxx=0;rxx<=rx;rxx++){

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,MAP);
   }

   ta++;
   y+=16;

   }
   x-=16;
   y=ryyy;
   }
   break;
   }

   }

   }

   }

   }

}

static void draw_west_story_object(int pri)
{
   int x,y;
   int zz,ta;
   UINT8 *MAP;

   if(pri==0){

   for(zz=0x147F6;zz>=0x14806;zz-=8){

   if((RAM[zz+1]&0x80)!=0){

   y=(256-ReadWord(&RAM[zz]))&0x1FF;
   x=(32+ReadWord(&RAM[zz+6]))&0x1FF;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   ta=ReadWord(&RAM[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               RAM[zz+5]>>4,
               16,        MAP
            );

      switch(RAM[zz+3]&0xC0){
      case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,MAP); break;
      }

   }

   }

   }else{zz=0x14006;}

   }

   }
   else{

   for(zz=0x14006;zz<0x14806;zz+=8){

   if((RAM[zz+1]&0x80)==0){

   y=(256-ReadWord(&RAM[zz]))&0x1FF;
   x=(32+ReadWord(&RAM[zz+6]))&0x1FF;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   ta=ReadWord(&RAM[zz+2])&0x1FFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               RAM[zz+5]>>4,
               16,        MAP
            );

      switch(RAM[zz+3]&0xC0){
      case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,MAP);        break;
      case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,MAP);  break;
      case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,MAP);  break;
      case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,MAP); break;
      }

   }

   }

   }else{zz=0x14806;}

   }


   }
}

static void DrawBloodBros(void)
{
   int x,y,x16,y16;
   int zz,zzz,zzzz,ta;
   UINT8 *MAP;

   ClearPaletteMap();

   // BG0

   MAKE_SCROLL_512x1024_2_16(
      ReadWord(&RAM_SCR[0x00]),
      ReadWord(&RAM_SCR[0x02])+16
   );

   START_SCROLL_512x1024_2_16(32,32,256,224);

      MAP_PALETTE_MAPPED_NEW(
         (ReadWord(&RAM_BG0[zz])>>12)|pal_bg0,
         16,
         MAP
      );

      Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord(&RAM_BG0[zz])&0xFFF)<<8],x,y,MAP);

   END_SCROLL_512x1024_2_16();

   // OBJECT LOW

   if(romset==0)
      draw_blood_bros_object(0);
   else
      draw_west_story_object(0);

   // BG1

   MAKE_SCROLL_512x1024_2_16(
      ReadWord(&RAM_SCR[0x04]),
      ReadWord(&RAM_SCR[0x06])+16
   );

   START_SCROLL_512x1024_2_16(32,32,256,224);

      if(zz<0x400){	// bleh

      ta=ReadWord(&RAM_BG1[zz])&0xFFF;

      if(GFX_BG1_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (ReadWord(&RAM_BG1[zz])>>12)|pal_bg1,
            16,
            MAP
         );

         if(GFX_BG1_SOLID[ta]==1)		// Some pixels; trans
            Draw16x16_Trans_Mapped_Rot(&GFX_BG1[ta<<8],x,y,MAP);
         else					// all pixels; solid
            Draw16x16_Mapped_Rot(&GFX_BG1[ta<<8],x,y,MAP);

      }

      }

   END_SCROLL_512x1024_2_16();

   // OBJECT HIGH

   if(romset==0)
      draw_blood_bros_object(0x80);
   else
      draw_west_story_object(0x80);

   // FG0

   MAKE_SCROLL_256x256_2_8(
      0,
      0+16
   );

   START_SCROLL_256x256_2_8(32,32,256,224);

      ta=ReadWord(&RAM_FG0[zz])&0xFFF;

      if(GFX_FG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (ReadWord(&RAM_FG0[zz])>>12)|pal_fg0,
            16,
            MAP
         );

         if(GFX_FG0_SOLID[ta]==1)		// Some pixels; trans
            Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,MAP);
         else					// all pixels; solid
            Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6],x,y,MAP);

      }

   END_SCROLL_256x256_2_8();

}

/*

Blood Bros Sprite List
----------------------

- 8 bytes/sprite entry
- 256 entries

Offset| Bit(s)         | Usage
------+7654321076543210+-----------------
  0/1 |............xxxx| Colour Bank
  0/1 |.........xxx....| Chain X
  0/1 |......xxx.......| Chain Y
  0/1 |.xx.............| Flip X/Y
  0/1 |x...............| Sprite:BG1 Priority
  2/3 |...xxxxxxxxxxxxx| Sprite Number
  4/5 |.......xxxxxxxxx| Sprite X
  6/7 |.......xxxxxxxxx| Sprite Y

West Story Sprite List
----------------------

- 8 bytes/sprite entry
- 256 entries

Offset| Bit(s)         | Usage
------+7654321076543210+-----------------
  0/1 |x...............| Sprite:BG1 Priority
  0/1 |.......xxxxxxxxx| Sprite Y
  2/3 |xx..............| Flip X/Y
  2/3 |...xxxxxxxxxxxxx| Sprite Number
  4/5 |............xxxx| Colour Bank
  6/7 |.......xxxxxxxxx| Sprite X


WEST STORY (C) 1991 DATSU ALLIANCE
----------------------------------

Main CPU....68000
Sound CPU...Z80


ROM CONTENTS
------------

Filename | Description
---------+----------------------------
WS01.BIN | 16x16 BG0 (0-3)
WS02.BIN | 16x16 BG0 (0-1)
WS03.BIN | 16x16 BG0 (0-2)
WS04.BIN | 16x16 BG0 (0-0)
WS05.BIN | 16x16 BG1 (0-3)
WS06.BIN | 16x16 BG1 (0-1)
WS07.BIN | 16x16 BG1 (0-2)
WS08.BIN | 16x16 BG1 (0-0)
WS09.BIN | 8x8 FG0 (0-3)
WS10.BIN | 8x8 FG0 (0-1)
WS11.BIN | 8x8 FG0 (0-2)
WS12.BIN | 8x8 FG0 (0-0)
WS13.BIN | 68000 ROM (block#1) (odd)
WS14.BIN | 68000 ROM (block#2) (odd)
WS15.BIN | 68000 ROM (block#1) (even)
WS16.BIN | 68000 ROM (block#2) (even)
WS17.BIN | Z80 ROM
WS18.BIN | ADPCM Sample Data
WS19.BIN | 16x16 SPR (0-0)
WS20.BIN | 16x16 SPR (1-0)
WS21.BIN | 16x16 SPR (0-1)
WS22.BIN | 16x16 SPR (1-1)
WS23.BIN | 16x16 SPR (0-2)
WS24.BIN | 16x16 SPR (1-2)
WS25.BIN | 16x16 SPR (0-3)
WS26.BIN | 16x16 SPR (1-3)

*/
static struct VIDEO_INFO video_weststry =
{
   DrawBloodBros,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_bloodbro[] =
{
   { "blood_bros", },
   { "bloodbro", },
   { NULL, },
};
GAME( bloodbro, "Blood Bros", TAD, 1990, GAME_SHOOT,
	.input = input_bloodbro,
	.dsw = dsw_bloodbro,
	.video = &video_weststry,
	.exec = execute_bloodbro,
	.long_name_jpn = "ブラッドブラザーズ Bootleg",
);
static struct DIR_INFO dir_weststry[] =
{
   { "west_story", },
   { "weststry", },
   { ROMOF("bloodbro"), },
   { CLONEOF("bloodbro"), },
   { NULL, },
};
GAME( weststry, "West Story", BOOTLEG, 1991, GAME_SHOOT,
	.input = input_weststry,
	.dsw = dsw_bloodbro,
	.clear = ClearWestStry,
	.video = &video_weststry,
	.exec = execute_weststry,
	.long_name_jpn = "ブラッドブラザーズ",
	.sound = sound_weststry,
);

