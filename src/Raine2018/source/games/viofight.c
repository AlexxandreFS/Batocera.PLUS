#define DRV_DEF_SOUND taito_ym2203_m6295_sound
/******************************************************************************/
/*                                                                            */
/*                 VIOLENCE FIGHT (C)1989 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines


static struct ROM_INFO rom_viofight[] =
{
   {   "c16-01.rom", 0x00080000, 0x7059ce83, 0, 0, 0, },
   {   "c16-02.rom", 0x00080000, 0xb458e905, 0, 0, 0, },
   {   "c16-03.rom", 0x00080000, 0x515a9431, 0, 0, 0, },
   {   "c16-04.rom", 0x00080000, 0xebf285e2, 0, 0, 0, },
   {   "c16-05.rom", 0x00080000, 0xa49d064a, 0, 0, 0, },
   {   "c16-06.rom", 0x00020000, 0x043761d8, 0, 0, 0, },
   {   "c16-07.rom", 0x00020000, 0x64d1d059, 0, 0, 0, },
   {   "c16-11.rom", 0x00010000, 0x23dbd388, 0, 0, 0, },
   {   "c16-12.rom", 0x00010000, 0x6fb028c7, 0, 0, 0, },
   {   "c16-14.rom", 0x00010000, 0xdc934f6a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_violence_fight_0[] =
{
   DSW_CABINET( 0x00,1 ),
   DSW_SCREEN( 0x02, 0x00),
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

static struct DSW_DATA dsw_data_violence_fight_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};


static struct DSW_INFO dsw_viofight[] =
{
   { 0x000000, 0xFF, dsw_data_violence_fight_0 },
   { 0x000002, 0xFF, dsw_data_violence_fight_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_violence_fight_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_viofight[] =
{
   { 0x100FFFF, 0x03, romsw_data_violence_fight_0 },
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

static void load_viofight(void)
{
   int ta,tb,tc;

   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x440000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x400000;

   if(!load_rom("c16-03.rom", RAM+0x00000, 0x80000)) return;
   if(!load_rom("c16-04.rom", RAM+0x80000, 0x80000)) return;
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
   if(!load_rom("c16-01.rom", RAM+0x00000, 0x80000)) return;
   if(!load_rom("c16-02.rom", RAM+0x80000, 0x80000)) return;
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

   FreeMem(RAM);

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom("c16-11.rom", RAM, 0x10000)) return;	// 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c16-14.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   memset(ROM+0x20000,0xFF,0x20000);

   if(!load_rom("c16-07.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("c16-06.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("c16-12.rom", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x40000))) return;
   if(!load_rom("c16-05.rom", PCMROM, 0x40000)) return;	// M6295 ADPCM

   AddTaitoYM2203(0x01B1, 0x015D, 0x10000, PCMROM, 0x40000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_INPUT  = RAM+0x26000;
   RAM_VIDEO  = RAM+0x10000;
   RAM_COLOUR = RAM+0x24000;
   RAM_VIDEO_2= RAM+0x26100;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   WriteWord68k(&ROM[0x89EC],0x4E71);

   WriteWord68k(&ROM[0x1694],0x4EF9);
   WriteLong68k(&ROM[0x1696],0x00000300);

   WriteLong68k(&ROM[0x0300],0x46FC2000);

   WriteLong68k(&ROM[0x0304],0x13FC0000);
   WriteLong68k(&ROM[0x0308],0x00AA0000);
   WriteWord68k(&ROM[0x030C],0x6100-10);

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
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0xA00000, 0xA03FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x600000, 0x601FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadByte(0x800000, 0x80000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0xA00000, 0xA03FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x600000, 0x601FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadWord(0x800000, 0x80000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xA00000, 0xA03FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x600000, 0x601FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteByte(0x800000, 0x80000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xA00000, 0xA03FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x600000, 0x601FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteWord(0x800000, 0x80000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void ClearViolenceFight(void)
{
   RemoveTaitoYM2203();
}

static void execute_viofight(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);
   cpu_interrupt(CPU_68K_0, 4);

   Taito2203_Frame();			// Z80 and YM2203
}
static struct DIR_INFO dir_viofight[] =
{
   { "violence_fight", },
   { "viofight", },
   { NULL, },
};
GAME( viofight, "Violence Fight", TAITO, 1989, GAME_BEAT,
	.input = b_system_inputs_3_button,
	.dsw = dsw_viofight,
	.romsw = romsw_viofight,
	.clear = ClearViolenceFight,
	.video = &b_system_r180_video,
	.exec = execute_viofight,
	.long_name_jpn = "バイオレンスファイト",
	.board = "C16",
);

