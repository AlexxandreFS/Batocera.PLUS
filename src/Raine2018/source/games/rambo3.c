#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                      RAMBO 3 (C) 1990 TAITO CORPORATION                    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"

/*

First set:

Thursday 10th Jan 1989

Second set:

Monday 22nd May 1989

*/


static struct ROM_INFO rom_rambo3[] =
{
   {    "r3-00.rom", 0x00010000, 0xdf7a6ed6, 0, 0, 0, },
   {    "r3-0e.rom", 0x00010000, 0x3efa4177, 0, 0, 0, },
   {    "r3-0o.rom", 0x00010000, 0x55c38d92, 0, 0, 0, },
   {    "r3-1e.rom", 0x00020000, 0x40e363c7, 0, 0, 0, },
   {    "r3-1o.rom", 0x00020000, 0x7f1fe6ab, 0, 0, 0, },
   {    "r3-a1.rom", 0x00020000, 0x4396fa19, 0, 0, 0, },
   {    "r3-a2.rom", 0x00020000, 0x41fe53a8, 0, 0, 0, },
   {    "r3-a3.rom", 0x00020000, 0xe89249ba, 0, 0, 0, },
   {    "r3-a4.rom", 0x00020000, 0x9cf4c21b, 0, 0, 0, },
   { "r3-ch0hh.rom", 0x00020000, 0x4dc69751, 0, 0, 0, },
   { "r3-ch0hl.rom", 0x00020000, 0xa4cad36d, 0, 0, 0, },
   { "r3-ch0lh.rom", 0x00020000, 0x76a330a2, 0, 0, 0, },
   { "r3-ch0ll.rom", 0x00020000, 0xb416f1bf, 0, 0, 0, },
   { "r3-ch1hh.rom", 0x00020000, 0xe39cff37, 0, 0, 0, },
   { "r3-ch1hl.rom", 0x00020000, 0x7525eb92, 0, 0, 0, },
   { "r3-ch1lh.rom", 0x00020000, 0x75568cf0, 0, 0, 0, },
   { "r3-ch1ll.rom", 0x00020000, 0xc86ea5fc, 0, 0, 0, },
   { "r3-ch2hh.rom", 0x00020000, 0xbf37dfac, 0, 0, 0, },
   { "r3-ch2hl.rom", 0x00020000, 0x837d8677, 0, 0, 0, },
   { "r3-ch2lh.rom", 0x00020000, 0xdf3bc48f, 0, 0, 0, },
   { "r3-ch2ll.rom", 0x00020000, 0xd0ce3051, 0, 0, 0, },
   { "r3-ch3hh.rom", 0x00020000, 0xabe58fdb, 0, 0, 0, },
   { "r3-ch3hl.rom", 0x00020000, 0x80e5647e, 0, 0, 0, },
   { "r3-ch3lh.rom", 0x00020000, 0x5a155c04, 0, 0, 0, },
   { "r3-ch3ll.rom", 0x00020000, 0xabe54b1e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_INFO dsw_rambo3[] =
{
   { 0x000000, 0xFF, dsw_data_default_0 },
   { 0x000002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_rambo_3_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito Europe",          0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_rambo3[] =
{
   { 0x100FFFF, 0x03, romsw_data_rambo_3_0 },
   { 0,        0,    NULL },
};



static struct ROM_INFO rom_rambo3a[] =
{
   { "ramb3-01.bin", 0x00080000, 0xc55fcf54, 0, 0, 0, },
   { "ramb3-02.bin", 0x00080000, 0x9dd014c6, 0, 0, 0, },
   { "ramb3-03.bin", 0x00080000, 0xf5808c41, 0, 0, 0, },
   { "ramb3-04.bin", 0x00080000, 0xc57831ce, 0, 0, 0, },
   { "ramb3-05.bin", 0x00080000, 0x0179dc40, 0, 0, 0, },
   { "ramb3-06.bin", 0x00020000, 0xa83d3fd5, 0, 0, 0, },
   { "ramb3-07.bin", 0x00020000, 0xc973ff6f, 0, 0, 0, },
   { "ramb3-10.bin", 0x00010000, 0xb18bc020, 0, 0, 0, },
   { "ramb3-11.bin", 0x00020000, 0x1cc42247, 0, 0, 0, },
   { "ramb3-13.bin", 0x00020000, 0x0a964cb7, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_rambo3a[] =
{
   INP1( COIN1, 0x000006, 0x10 ),
   INP1( COIN2, 0x000006, 0x20 ),
   INP0( TILT, 0x000006, 0x01 ),
   INP0( SERVICE, 0x000006, 0x02 ),

   INP0( P1_START, 0x000006, 0x04 ),
   INP0( P1_UP, 0x00000E, 0x01 ),
   INP0( P1_DOWN, 0x00000E, 0x02 ),
   INP0( P1_LEFT, 0x00000E, 0x04 ),
   INP0( P1_RIGHT, 0x00000E, 0x08 ),
   INP0( P1_B1, 0x000004, 0x01 ),
   INP0( P1_B2, 0x000004, 0x02 ),
   INP0( P1_B3, 0x000004, 0x04 ),

   INP0( P2_START, 0x000006, 0x08 ),
   INP0( P2_UP, 0x00000E, 0x10 ),
   INP0( P2_DOWN, 0x00000E, 0x20 ),
   INP0( P2_LEFT, 0x00000E, 0x40 ),
   INP0( P2_RIGHT, 0x00000E, 0x80 ),
   INP0( P2_B1, 0x000004, 0x08 ),
   INP0( P2_B2, 0x000004, 0x10 ),
   INP0( P2_B3, 0x000004, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_rambo_3_alternate_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
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

static struct DSW_INFO dsw_rambo3a[] =
{
   { 0x000000, 0xFF, dsw_data_rambo_3_alternate_0 },
   { 0x000002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_rambo_3_alternate_0[] =
{
   { "Taito Japan (notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Europe",          0x03 },
   { "Taito Japan",           0x04 },
   { "Taito World",           0x05 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_rambo3a[] =
{
   { 0x03FFFF, 0x02, romsw_data_rambo_3_alternate_0 },
   { 0,        0,    NULL },
};


static UINT8 *RAM_INPUT;
static UINT8 *RAM_VIDEO;
static UINT8 *RAM_VIDEO_2;
static UINT8 *RAM_COLOUR;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG2;
static UINT8 *GFX_BG2_SOLID;

static void load_rambo3(void)
{
   int ta,tb,tc;

   if(!(RAM=AllocateMem(0xC0000))) return;
   if(!(GFX=AllocateMem(0x440000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x400000;

   if(!load_rom("r3-ch0lh.rom", RAM+0x00000, 0x20000)) return;
   if(!load_rom("r3-ch0hh.rom", RAM+0x20000, 0x20000)) return;
   if(!load_rom("r3-ch2lh.rom", RAM+0x40000, 0x20000)) return;
   if(!load_rom("r3-ch2hh.rom", RAM+0x60000, 0x20000)) return;
   tb=0x400000;
   for(ta=0;ta<0x8000;ta++){
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
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   if(!load_rom("r3-ch0ll.rom", RAM+0x00000, 0x20000)) return;
   if(!load_rom("r3-ch0hl.rom", RAM+0x20000, 0x20000)) return;
   if(!load_rom("r3-ch2ll.rom", RAM+0x40000, 0x20000)) return;
   if(!load_rom("r3-ch2hl.rom", RAM+0x60000, 0x20000)) return;
   tb=0x400000;
   for(ta=0;ta<0x8000;ta++){
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
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   if(!load_rom("r3-ch1lh.rom", RAM+0x00000, 0x20000)) return;
   if(!load_rom("r3-ch1hh.rom", RAM+0x20000, 0x20000)) return;
   if(!load_rom("r3-ch3lh.rom", RAM+0x40000, 0x20000)) return;
   if(!load_rom("r3-ch3hh.rom", RAM+0x60000, 0x20000)) return;
   tb=0x400000;
   for(ta=0;ta<0x8000;ta++){
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
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   if(!load_rom("r3-ch1ll.rom", RAM+0x00000, 0x20000)) return;
   if(!load_rom("r3-ch1hl.rom", RAM+0x20000, 0x20000)) return;
   if(!load_rom("r3-ch3ll.rom", RAM+0x40000, 0x20000)) return;
   if(!load_rom("r3-ch3hl.rom", RAM+0x60000, 0x20000)) return;
   tb=0x400000;
   for(ta=0;ta<0x8000;ta++){
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
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }

   FreeMem(RAM);

   RAMSize=0xA0000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom("r3-0e.rom", RAM, 0x10000)) return;	// 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("r3-0o.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   memset(ROM+0x20000,0xFF,0x20000);

   if(!load_rom("r3-1e.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("r3-1o.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0xA0000;
   if(!load_rom("r3-00.rom", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("r3-a1.rom",PCMROM+0x00000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("r3-a2.rom",PCMROM+0x20000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("r3-a3.rom",PCMROM+0x40000,0x20000)) return;	// ADPCM A rom
   if(!load_rom("r3-a4.rom",PCMROM+0x60000,0x20000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x0338, 0x02A5, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0xA0000);

   RAM_INPUT  = RAM+0x92000;
   RAM_VIDEO  = RAM+0x10000;
   RAM_COLOUR = RAM+0x90000;
   RAM_VIDEO_2= RAM_VIDEO+0x18000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   //WriteWord68k(&ROM[0x89EC],0x4E71);

   // SPEED HACK
   // ----------

   WriteWord68k(&ROM[0x028E],0x4EF9);
   WriteLong68k(&ROM[0x0290],0x000000C0);

   WriteLong68k(&ROM[0x00C0],0x46FC2000);

   WriteLong68k(&ROM[0x00C4],0x13FC0000);
   WriteLong68k(&ROM[0x00C8],0x00AA0000);
   WriteWord68k(&ROM[0x00CC],0x6100-10);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO_2;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x3FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x40,0xC0,0x80,0x40,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0xA0000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x800000, 0x803FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x600000, 0x60000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x800000, 0x803FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x600000, 0x60000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x800000, 0x803FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x600000, 0x60000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x800000, 0x803FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x600000, 0x60000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_rambo3a(void)
{
   int ta,tb,tc;

   if(!(GFX=AllocateMem(0x440000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x400000;

   if(!load_rom("ramb3-01.bin", RAM+0x00000, 0x80000)) return;
   if(!load_rom("ramb3-02.bin", RAM+0x80000, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]=((tc&0x80)>>7)<<0;
      GFX[tb+1]=((tc&0x40)>>6)<<0;
      GFX[tb+2]=((tc&0x20)>>5)<<0;
      GFX[tb+3]=((tc&0x10)>>4)<<0;
      GFX[tb+4]=((tc&0x08)>>3)<<0;
      GFX[tb+5]=((tc&0x04)>>2)<<0;
      GFX[tb+6]=((tc&0x02)>>1)<<0;
      GFX[tb+7]=((tc&0x01)>>0)<<0;
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
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   tb=0x400000;
   for(ta=0;ta<0x10000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]=((tc&0x80)>>7)<<0;
      GFX[tb+1]=((tc&0x40)>>6)<<0;
      GFX[tb+2]=((tc&0x20)>>5)<<0;
      GFX[tb+3]=((tc&0x10)>>4)<<0;
      GFX[tb+4]=((tc&0x08)>>3)<<0;
      GFX[tb+5]=((tc&0x04)>>2)<<0;
      GFX[tb+6]=((tc&0x02)>>1)<<0;
      GFX[tb+7]=((tc&0x01)>>0)<<0;
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
   if(!load_rom("ramb3-03.bin", RAM+0x00000, 0x80000)) return;
   if(!load_rom("ramb3-04.bin", RAM+0x80000, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]|=((tc&0x80)>>7)<<2;
      GFX[tb+1]|=((tc&0x40)>>6)<<2;
      GFX[tb+2]|=((tc&0x20)>>5)<<2;
      GFX[tb+3]|=((tc&0x10)>>4)<<2;
      GFX[tb+4]|=((tc&0x08)>>3)<<2;
      GFX[tb+5]|=((tc&0x04)>>2)<<2;
      GFX[tb+6]|=((tc&0x02)>>1)<<2;
      GFX[tb+7]|=((tc&0x01)>>0)<<2;
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
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   tb=0x400000;
   for(ta=0;ta<0x10000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]|=((tc&0x80)>>7)<<2;
      GFX[tb+1]|=((tc&0x40)>>6)<<2;
      GFX[tb+2]|=((tc&0x20)>>5)<<2;
      GFX[tb+3]|=((tc&0x10)>>4)<<2;
      GFX[tb+4]|=((tc&0x08)>>3)<<2;
      GFX[tb+5]|=((tc&0x04)>>2)<<2;
      GFX[tb+6]|=((tc&0x02)>>1)<<2;
      GFX[tb+7]|=((tc&0x01)>>0)<<2;
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

   FreeMem(RAM);

   RAMSize=0xA0000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom("ramb3-11.bin", RAM, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("ramb3-13.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("ramb3-07.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("ramb3-06.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0xA0000;
   if(!load_rom("ramb3-10.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("ramb3-05.bin",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x0338, 0x02A5, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0xA0000);

   RAM_INPUT  = RAM+0x92000;
   RAM_VIDEO  = RAM+0x10000;
   RAM_COLOUR = RAM+0x90000;
   RAM_VIDEO_2= RAM_VIDEO+0x18000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   // fix rom checksum

   WriteLong68k(&ROM[0x2F5BA],0x4E714E71);

   // speed hack

   WriteWord68k(&ROM[0x02E0],0x4EF9);
   WriteLong68k(&ROM[0x02E2],0x000000C0);

   WriteLong68k(&ROM[0x00C0],0x46FC2000);

   WriteLong68k(&ROM[0x00C4],0x13FC0000);
   WriteLong68k(&ROM[0x00C8],0x00AA0000);
   WriteWord68k(&ROM[0x00CC],0x6100-10);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO_2;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x3FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x10,0x30,0x20,0x10,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0xA0000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x800000, 0x803FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x600000, 0x60000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x800000, 0x803FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x600000, 0x60000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x800000, 0x803FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x600000, 0x60000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x800000, 0x803FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x47FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x600000, 0x60000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_rambo3(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);
   cpu_execute_cycles(CPU_68K_0, 6000);
   cpu_interrupt(CPU_68K_0, 6);
   Taito2610_Frame();			// Z80 and YM2610
}
static struct DIR_INFO dir_rambo3[] =
{
   { "rambo_3", },
   { "rambo3", },
   { NULL, },
};
GAME( rambo3, "Rambo 3", TAITO, 1989, GAME_SHOOT,
	.input = b_system_inputs,
	.dsw = dsw_rambo3,
	.romsw = romsw_rambo3,
	.video = &b_system_r180_video,
	.exec = execute_rambo3,
	.long_name_jpn = "ÉâÉìÉ{Å[ÇR",
	.board = "B93",
);
static struct DIR_INFO dir_rambo3a[] =
{
   { "rambo_3_alternate", },
   { "rambo3a", },
   { ROMOF("rambo3"), },
   { CLONEOF("rambo3"), },
   { NULL, },
};
GAME( rambo3a, "Rambo 3 (release 2)", TAITO, 1989, GAME_SHOOT,
	.input = input_rambo3a,
	.dsw = dsw_rambo3a,
	.romsw = romsw_rambo3a,
	.video = &b_system_r180_video,
	.exec = execute_rambo3,
	.long_name_jpn = "ÉâÉìÉ{Å[ÇR (release 2)",
	.board = "B93",
);

