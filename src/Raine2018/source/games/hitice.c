/******************************************************************************/
/*                                                                            */
/*                    HIT THE ICE (C) 1990 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"


static struct ROM_INFO rom_hitice[] =
{
   {   "c59-08", 0x00010000, 0xd3cbc10b, 0, 0, 0, },
   {   "c59-02", 0x00080000, 0xaffb5e07, 0, 0, 0, },
   {   "c59-03", 0x00080000, 0x9e513048, 0, 0, 0, },
   { "c59-01", 0x00020000, 0x46ae291d, 0, 0, 0, },
   {   "c59-09", 0x00010000, 0xe243e3b0, 0, 0, 0, },
   {   "c59-10", 0x00020000, 0xe4ffad15, 0, 0, 0, },
   {   "c59-11", 0x00010000, 0x4d4dfa52, 0, 0, 0, },
   {   "c59-12", 0x00020000, 0xa080d7af, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_hitice[] =
{
   INP0( COIN1, 0x026106, 0x10 ),
   INP0( COIN2, 0x026106, 0x20 ),
   INP0( TILT, 0x026106, 0x01 ),
   INP0( SERVICE, 0x026106, 0x02 ),

   INP0( P1_START, 0x026106, 0x04 ),
   INP0( P1_UP, 0x02610E, 0x01 ),
   INP0( P1_DOWN, 0x02610E, 0x02 ),
   INP0( P1_LEFT, 0x02610E, 0x04 ),
   INP0( P1_RIGHT, 0x02610E, 0x08 ),
   INP0( P1_B1, 0x026104, 0x01 ),
   INP0( P1_B2, 0x026104, 0x02 ),
   INP0( P1_B3, 0x026104, 0x04 ),

   INP0( P2_START, 0x026106, 0x08 ),
   INP0( P2_UP, 0x02610E, 0x10 ),
   INP0( P2_DOWN, 0x02610E, 0x20 ),
   INP0( P2_LEFT, 0x02610E, 0x40 ),
   INP0( P2_RIGHT, 0x02610E, 0x80 ),
   INP0( P2_B1, 0x026104, 0x08 ),
   INP0( P2_B2, 0x026104, 0x10 ),
   INP0( P2_B3, 0x026104, 0x20 ),

   INP0( P3_START, 0x026200, 0x80 ),
   INP0( P3_UP, 0x026200, 0x01 ),
   INP0( P3_DOWN, 0x026200, 0x02 ),
   INP0( P3_LEFT, 0x026200, 0x04 ),
   INP0( P3_RIGHT, 0x026200, 0x08 ),
   INP0( P3_B1, 0x026200, 0x10 ),
   INP0( P3_B2, 0x026200, 0x20 ),
   INP0( P3_B3, 0x026200, 0x40 ),

   INP0( P4_START, 0x026201, 0x80 ),
   INP0( P4_UP, 0x026201, 0x01 ),
   INP0( P4_DOWN, 0x026201, 0x02 ),
   INP0( P4_LEFT, 0x026201, 0x04 ),
   INP0( P4_RIGHT, 0x026201, 0x08 ),
   INP0( P4_B1, 0x026201, 0x10 ),
   INP0( P4_B2, 0x026201, 0x20 ),
   INP0( P4_B3, 0x026201, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_hit_the_ice_0[] =
{
   { _("Max Players"),           0x01, 0x02 },
   { "4",                     0x01},
   { "2",                     0x00},
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { MSG_COINAGE,               0x70, 0x08 },
   { MSG_1COIN_1PLAY,         0x70},
   { MSG_2COIN_1PLAY,         0x60},
   { MSG_3COIN_1PLAY,         0x50},
   { MSG_1COIN_3PLAY,         0x40},
   { MSG_1COIN_2PLAY,         0x30},
   { MSG_1COIN_5PLAY,         0x20},
   { MSG_1COIN_4PLAY,         0x10},
   { MSG_1COIN_6PLAY,         0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_hitice[] =
{
   { 0x026100, 0xFF, dsw_data_hit_the_ice_0 },
   { 0x026102, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};


static struct ROMSW_DATA romsw_data_hit_the_ice_0[] =
{
   { "Taito",                 0x01 },
   { "Williams Electronics",  0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_hitice[] =
{
   { 0x05FFFF, 0x02, romsw_data_hit_the_ice_0 },
   { 0,        0,    NULL },
};


/*

Todo:

- Pixel Layer (not the B-System one, this one is larger and scrollable).
- BG2 (FG0) is scrolled (8 pixels too high in test hatch).

*/

static UINT8 *RAM_INPUT;
static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG2;
static UINT8 *GFX_BG2_SOLID;

static void load_hitice(void)
{
   int ta,tb,tc;

   RAMSize=0x38000+0x80000;

   if(!(ROM=AllocateMem(0x60000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x200000;

   if(!load_rom("c59-03", RAM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=RAM[ta+0];
      GFX[tb+0]=((tc&0x80)>>7)<<3;
      GFX[tb+1]=((tc&0x40)>>6)<<3;
      GFX[tb+2]=((tc&0x20)>>5)<<3;
      GFX[tb+3]=((tc&0x10)>>4)<<3;
      GFX[tb+4]=((tc&0x08)>>3)<<3;
      GFX[tb+5]=((tc&0x04)>>2)<<3;
      GFX[tb+6]=((tc&0x02)>>1)<<3;
      GFX[tb+7]=((tc&0x01)>>0)<<3;
      tc=RAM[ta+1];
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
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   for(ta=0;ta<0x10000;ta+=2){
      tc=RAM[ta+0];
      GFX[tb+0]=((tc&0x80)>>7)<<3;
      GFX[tb+1]=((tc&0x40)>>6)<<3;
      GFX[tb+2]=((tc&0x20)>>5)<<3;
      GFX[tb+3]=((tc&0x10)>>4)<<3;
      GFX[tb+4]=((tc&0x08)>>3)<<3;
      GFX[tb+5]=((tc&0x04)>>2)<<3;
      GFX[tb+6]=((tc&0x02)>>1)<<3;
      GFX[tb+7]=((tc&0x01)>>0)<<3;
      tc=RAM[ta+1];
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
   if(!load_rom("c59-02", RAM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=RAM[ta+0];
      GFX[tb+0]|=((tc&0x80)>>7)<<1;
      GFX[tb+1]|=((tc&0x40)>>6)<<1;
      GFX[tb+2]|=((tc&0x20)>>5)<<1;
      GFX[tb+3]|=((tc&0x10)>>4)<<1;
      GFX[tb+4]|=((tc&0x08)>>3)<<1;
      GFX[tb+5]|=((tc&0x04)>>2)<<1;
      GFX[tb+6]|=((tc&0x02)>>1)<<1;
      GFX[tb+7]|=((tc&0x01)>>0)<<1;
      tc=RAM[ta+1];
      GFX[tb+0]|=((tc&0x80)>>7)<<0;
      GFX[tb+1]|=((tc&0x40)>>6)<<0;
      GFX[tb+2]|=((tc&0x20)>>5)<<0;
      GFX[tb+3]|=((tc&0x10)>>4)<<0;
      GFX[tb+4]|=((tc&0x08)>>3)<<0;
      GFX[tb+5]|=((tc&0x04)>>2)<<0;
      GFX[tb+6]|=((tc&0x02)>>1)<<0;
      GFX[tb+7]|=((tc&0x01)>>0)<<0;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   for(ta=0;ta<0x10000;ta+=2){
      tc=RAM[ta+0];
      GFX[tb+0]|=((tc&0x80)>>7)<<1;
      GFX[tb+1]|=((tc&0x40)>>6)<<1;
      GFX[tb+2]|=((tc&0x20)>>5)<<1;
      GFX[tb+3]|=((tc&0x10)>>4)<<1;
      GFX[tb+4]|=((tc&0x08)>>3)<<1;
      GFX[tb+5]|=((tc&0x04)>>2)<<1;
      GFX[tb+6]|=((tc&0x02)>>1)<<1;
      GFX[tb+7]|=((tc&0x01)>>0)<<1;
      tc=RAM[ta+1];
      GFX[tb+0]|=((tc&0x80)>>7)<<0;
      GFX[tb+1]|=((tc&0x40)>>6)<<0;
      GFX[tb+2]|=((tc&0x20)>>5)<<0;
      GFX[tb+3]|=((tc&0x10)>>4)<<0;
      GFX[tb+4]|=((tc&0x08)>>3)<<0;
      GFX[tb+5]|=((tc&0x04)>>2)<<0;
      GFX[tb+6]|=((tc&0x02)>>1)<<0;
      GFX[tb+7]|=((tc&0x01)>>0)<<0;
      tb+=8;
   }

   if(!load_rom("c59-10", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c59-12", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("c59-09", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("c59-11", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   if(!load_rom( "c59-08", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x20000))) return;
   if(!load_rom( "c59-01", PCMROM, 0x20000)) return;	// M6295 ADPCM

   AddTaitoYM2203(0x01B1, 0x015D, 0x10000, PCMROM, 0x20000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);
   memset(RAM+0x26000,0xFF,0x02000);
   memset(RAM+0x28000,0x00,0x80000);

   RAM_INPUT  = RAM+0x26100;
   RAM_VIDEO  = RAM+0x04000;
   RAM_COLOUR = RAM+0x24000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   WriteWord68k(&ROM[0x002B6],0x4EF9);		// JMP $10
   WriteLong68k(&ROM[0x002B8],0x00000010);

   WriteLong68k(&ROM[0x00010],0x46FC2000);
   WriteLong68k(&ROM[0x00014],0x13FC0000);	// Stop 68000
   WriteLong68k(&ROM[0x00018],0x00AA0000);
   WriteWord68k(&ROM[0x0001C],0x6100-10);	// Loop

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO+0x18000;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x1FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x40,0xC0,0x80,0x40,0x00);

   // Init MC68000 emulation
   // ----------------------

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x28000);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x800000, 0x803FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0xB00000, 0xB7FFFF, NULL, RAM+0x038000);			// PIXEL RAM?
   AddReadByte(0xBFFFF0, 0xBFFFFF, NULL, RAM+0x026000);			// SCROLL RAM?
   AddReadByte(0x600000, 0x60000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x700000, 0x700003, tc0140syt_read_main_68k, NULL);	// SOUND
   AddReadByte(0x610000, 0x610001, NULL, RAM+0x026200);			// INPUT P3/P4?
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x800000, 0x803FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0xB00000, 0xB7FFFF, NULL, RAM+0x038000);			// PIXEL RAM?
   AddReadWord(0xBFFFF0, 0xBFFFFF, NULL, RAM+0x026000);			// SCROLL RAM?
   AddReadWord(0x600000, 0x60000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x800000, 0x803FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0xB00000, 0xB7FFFF, NULL, RAM+0x038000);		// PIXEL RAM?
   AddWriteByte(0xBFFFF0, 0xBFFFFF, NULL, RAM+0x026000);		// SCROLL RAM?
   AddWriteByte(0x700000, 0x700003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteByte(0x600000, 0x60000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x800000, 0x803FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xA00000, 0xA01FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0xB00000, 0xB7FFFF, NULL, RAM+0x038000);		// PIXEL RAM?
   AddWriteWord(0xBFFFF0, 0xBFFFFF, NULL, RAM+0x026000);		// SCROLL RAM?
   AddWriteWord(0x600000, 0x60000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void ClearHitTheIce(void)
{
   RemoveTaitoYM2203();
}

static void execute_hitice(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   if(s68000context.pc == 0x001C){	// Prevent game freezing up
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 4);
   }

//   Taito2203_Frame();			// Z80 and YM2203
   cpu_execute_cycles(CPU_Z80_0, (4000000/60)*2);
   cpu_interrupt(CPU_Z80_0, 0x0038);
}
static struct DIR_INFO dir_hitice[] =
{
   { "hit_the_ice", },
   { "hitice", },
   { NULL, },
};
GAME( hitice, "Hit the Ice", WILLIAMS, 1990, GAME_SPORTS,
	.input = input_hitice,
	.dsw = dsw_hitice,
	.romsw = romsw_hitice,
	.clear = ClearHitTheIce,
	.video = &b_system_r180_video,
	.exec = execute_hitice,
	.long_name_jpn = "ヒットジアイス",
	.board = "C59",
	.sound = taito_ym2203_m6295_sound,
);

