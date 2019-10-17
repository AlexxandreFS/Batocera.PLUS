/******************************************************************************
 *                                                                            *
 *                 DEAD CONNECTION (C) 1991 TAITO CORPORATION                 *
 *                                                                            *
 ******************************************************************************

	Dead Connection Japan removed becuase the only difference in the roms
	were the Taito Region byte.  This byte is set with the ROM Version
	routine so this set becomes redundant and null if you use it and set
	the ROM version to something else
*/

#include "gameinc.h"
#include "tc006vcu.h"
#include "tc200obj.h"
#include "f3system.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines


static struct ROM_INFO rom_deadconx[] =
{
   {   "d28_01.8", 0x00100000, 0x181d7b69, 0, 0, 0, },
   {   "d28_02.9", 0x00100000, 0xd301771c, 0, 0, 0, },
   {   "d28_03.10", 0x00100000, 0xa1804b52, 0, 0, 0, },
   {   "d28_04.16", 0x00080000, 0xdcabc26b, 0, 0, 0, },
   {   "d28_05.17", 0x00080000, 0x862f9665, 0, 0, 0, },
   {   "d28_06.3", 0x00040000, 0x5b4bff51, 0, 0, 0, },
   {   "d28_08.4", 0x00040000, 0x4c872bd9, 0, 0, 0, },
   {   "d28_09.2", 0x00040000, 0x143a0cc1, 0, 0, 0, },
   {   "d28_10.6", 0x00010000, 0x40805d74, 0, 0, 0, },
   {   "d28_12.5", 0x00040000, 0x9b74e631, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_deadconx[] =
{
   INP0( COIN1, 0x034104, 0x01 ),
   INP0( COIN2, 0x034104, 0x02 ),
   INP0( COIN3, 0x034104, 0x04 ),
   INP0( COIN4, 0x034104, 0x08 ),
   INP0( TILT, 0x034104, 0x80 ),
   INP0( SERVICE, 0x034104, 0x70 ),

   INP0( P1_START, 0x03410A, 0x80 ),
   INP0( P1_UP, 0x03410A, 0x01 ),
   INP0( P1_DOWN, 0x03410A, 0x02 ),
   INP0( P1_LEFT, 0x03410A, 0x04 ),
   INP0( P1_RIGHT, 0x03410A, 0x08 ),
   INP0( P1_B1, 0x03410A, 0x10 ),
   INP0( P1_B2, 0x03410A, 0x20 ),

   INP0( P2_START, 0x03410C, 0x80 ),
   INP0( P2_UP, 0x03410C, 0x01 ),
   INP0( P2_DOWN, 0x03410C, 0x02 ),
   INP0( P2_LEFT, 0x03410C, 0x04 ),
   INP0( P2_RIGHT, 0x03410C, 0x08 ),
   INP0( P2_B1, 0x03410C, 0x10 ),
   INP0( P2_B2, 0x03410C, 0x20 ),

   INP0( P3_START, 0x03410E, 0x80 ),
   INP0( P3_UP, 0x03410E, 0x01 ),
   INP0( P3_DOWN, 0x03410E, 0x02 ),
   INP0( P3_LEFT, 0x03410E, 0x04 ),
   INP0( P3_RIGHT, 0x03410E, 0x08 ),
   INP0( P3_B1, 0x03410E, 0x10 ),
   INP0( P3_B2, 0x03410E, 0x20 ),

   INP0( P4_START, 0x034110, 0x80 ),
   INP0( P4_UP, 0x034110, 0x01 ),
   INP0( P4_DOWN, 0x034110, 0x02 ),
   INP0( P4_LEFT, 0x034110, 0x04 ),
   INP0( P4_RIGHT, 0x034110, 0x08 ),
   INP0( P4_B1, 0x034110, 0x10 ),
   INP0( P4_B2, 0x034110, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_dead_connection_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
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

static struct DSW_DATA dsw_data_dead_connection_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_DSWB_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { _("Damage"),                0x18, 0x04 },
   { MSG_NORMAL,              0x18},
   { _("Small"),                 0x10},
   { _("Big"),                   0x08},
   { _("Biggest"),               0x00},
   { MSG_DSWB_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Game Type"),             0x80, 0x02 },
   { _("1 Player"),              0x80},
   { _("Multiplayer"),           0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_deadconx[] =
{
   { 0x034100, 0xFF, dsw_data_dead_connection_0 },
   { 0x034102, 0xFF, dsw_data_dead_connection_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_dead_connection_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Japan",            0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_deadconx[] =
{
   { 0x07FFFF, 0x03, romsw_data_dead_connection_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;
//static UINT8 *RAM_BG4;

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;
static UINT8 *RAM_SCR4;

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;
static UINT32 SCR4_XOFS;

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;
static UINT32 SCR4_YOFS;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static int BadReadWord(UINT32 address)
{
       print_debug("Rw(%06x) [%06x]\n",address,s68000context.pc);
   return(0xFFFF);
}

static void BadWriteWord(UINT32 address, UINT16 data)
{
#ifdef RAINE_DEBUG
      if(address!=0x800000) print_debug("Ww(%06x,%04x) [%06x]\n",address,data,s68000context.pc);
#endif
}

static void load_deadconx(void)
{
   int ta,tb;
   UINT8 *TMP;

   if(!(GFX=AllocateMem(0x600000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;			// TEMP BUFFER

   GFX_BG0=GFX+0x000000;
   GFX_SPR=GFX+0x200000;

   tb=0;
   if(!load_rom_index(0, TMP, 0x100000)) return;	// 16x16 SPRITES ($4000)
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }
   if(!load_rom_index(1, TMP, 0x100000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   tb=0;
   if(!load_rom_index(3, TMP, 0x80000)) return;	// 16x16 TILES ($2000)
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      GFX_BG0[tb+0]=TMP[ta]&15;
      GFX_BG0[tb+1]=TMP[ta]>>4;
      GFX_BG0[tb+2]=TMP[ta+1]&15;
      GFX_BG0[tb+3]=TMP[ta+1]>>4;
   }
   tb=4;
   if(!load_rom_index(4, TMP, 0x80000)) return;	// 16x16 TILES
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      GFX_BG0[tb+0]=TMP[ta]&15;
      GFX_BG0[tb+1]=TMP[ta]>>4;
      GFX_BG0[tb+2]=TMP[ta+1]&15;
      GFX_BG0[tb+3]=TMP[ta+1]>>4;
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   if(!(RAM=AllocateMem(0x60000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   if(!load_rom_index(5, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(9, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom_index(7, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom_index(6, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom_index(8, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom_index(2, PCMROM, 0x100000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x01D5, 0x0175, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x34100,0xFF,0x04000);

   RAMSize=0x40000+0x20000;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   RAM_BG0=RAM+0x20000;
   RAM_BG1=RAM+0x21000;
   RAM_BG2=RAM+0x22000;
   RAM_BG3=RAM+0x23000;

   RAM_SCR0=RAM+0x34000;
   RAM_SCR1=RAM+0x34002;
   RAM_SCR2=RAM+0x34004;
   RAM_SCR3=RAM+0x34006;
   RAM_SCR4=RAM+0x34018;

   SCR0_XOFS=0x0022 - 1;
   SCR1_XOFS=0x001E - 1;
   SCR2_XOFS=0x001A - 1;
   SCR3_XOFS=0x0016 - 1;
   SCR4_XOFS=0x0022 + 1;

   SCR0_YOFS=0x0008;
   SCR1_YOFS=0x0008;
   SCR2_YOFS=0x0008;
   SCR3_YOFS=0x0008;
   SCR4_YOFS=0x0008;

   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x1AE2],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x1AE6],0x00AA0000);
   WriteWord68k(&ROM[0x1AEA],0x6100-10);	// bra.s <loop>

   ROM[0x7FFFD] = 0x10;

   // Init tc0006vcu emulation
   // ------------------------

   if(!(tc0006vcu.GFX_FG = AllocateMem(0x4000))) return;

   tc0006vcu.RAM	= RAM+0x20000;
   tc0006vcu.RAM_SCR	= RAM+0x34000;
   tc0006vcu.GFX_BG	= GFX_BG0;
   tc0006vcu.GFX_BG_MASK= GFX_BG0_SOLID;
   tc0006vcu.tile_mask  = 0x1FFF;
// Mapper disabled
   tc0006vcu.pal_ofs	= 0;
   tc0006vcu.bmp_x	= 48;
   tc0006vcu.bmp_y	= 48;
   tc0006vcu.bmp_w	= 320;
   tc0006vcu.bmp_h	= 224;
   tc0006vcu.scr_x[0]	= SCR0_XOFS;
   tc0006vcu.scr_x[1]	= SCR1_XOFS;
   tc0006vcu.scr_x[2]	= SCR2_XOFS;
   tc0006vcu.scr_x[3]	= SCR3_XOFS;
   tc0006vcu.scr_x[4]	= SCR4_XOFS;
   tc0006vcu.scr_y[0]	= SCR0_YOFS;
   tc0006vcu.scr_y[1]	= SCR1_YOFS;
   tc0006vcu.scr_y[2]	= SCR2_YOFS;
   tc0006vcu.scr_y[3]	= SCR3_YOFS;
   tc0006vcu.scr_y[4]	= SCR4_YOFS;

   init_tc0006vcu();

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x10000;
   tc0200obj.RAM_B	= RAM+0x18000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 48;
   tc0200obj.bmp_y	= 48;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
// Mapper disabled
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;

   tc0200obj.cols	= 16;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x200000, 0x20FFFF, NULL, RAM+0x010000);			// OBJECT RAM
   AddReadByte(0x400000, 0x40FFFF, NULL, RAM+0x020000);			// SCREEN RAM
   AddReadByte(0x600000, 0x603FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadByte(0x700000, 0x70001F, NULL, RAM+0x034100);			// INPUT
   AddReadByte(0xA00000, 0xA00003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x200000, 0x20FFFF, NULL, RAM+0x010000);			// OBJECT RAM
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM+0x020000);			// SCREEN RAM
   AddReadWord(0x600000, 0x603FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM+0x010000);		// OBJECT RAM
   AddWriteByte(0x400000, 0x40DFFF, NULL, RAM+0x020000);		// SCREEN RAM
   AddWriteByte(0x40E000, 0x40FFFF, tc0006vcu_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x600000, 0x603FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteByte(0xA00000, 0xA00003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM+0x010000);		// OBJECT RAM
   AddWriteWord(0x400000, 0x40DFFF, NULL, RAM+0x020000);		// SCREEN RAM
   AddWriteWord(0x40E000, 0x40FFFF, tc0006vcu_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x600000, 0x603FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteWord(0x430000, 0x4300FF, NULL, RAM+0x034000);		// SCROLL
   AddWriteWord(0x300000, 0x30000F, NULL, RAM+0x034200);		// SPRITE BANKING
   AddWriteWord(0x500000, 0x50001F, NULL, RAM+0x034300);		// ???
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void ClearDeadConnection(void)
{
   RemoveTaitoYM2610();
}

static void execute_deadconx(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 5);

   Taito2610_Frame();			// Z80 and YM2610

   IntF3System();

   debug_tc0006vcu();
}

static void DrawDeadConnection(void)
{
   ClearPaletteMap();

   make_object_bank(RAM+0x034200);

   tc0006vcu_layer_count = 0;

   tc0006vcu_render_layer(0);

   render_tc0200obj_mapped_fchamp(0x40);

   tc0006vcu_render_layer(1);

   render_tc0200obj_mapped_fchamp(0x80);

   tc0006vcu_render_layer(2);

   render_tc0200obj_mapped_fchamp(0xC0);

   tc0006vcu_render_layer(3);

   render_tc0200obj_mapped_fchamp(0x00);

   tc0006vcu_render_fg0();
}


/*

-----------+-----------------------
File       | Contents
-----------+-----------------------
d28-01.rom | 16x16 Sprite Tiles (odd)
d28-02.rom | 16x16 Sprite Tiles (even)
d28-03.rom | YM2610 ADPCM
d28-04.rom | 16x16 BG0 Tiles (odd)
d28-05.rom | 16x16 BG0 Tiles (even)
d28-06.rom | 68000 (block 0; even)
d28-08.rom | 68000 (block 1; odd)
d28-09.rom | 68000 (block 1; even)
d28-10.rom | Z80
d28-12.rom | 68000 (block 0; odd)
-----------+-----------------------

*/
static struct VIDEO_INFO video_deadconx =
{
   DrawDeadConnection,
   320,
   224,
   48,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_deadconx[] =
{
   { "dead_connection", },
   { "deadconx", },
   { NULL, },
};
GAME( deadconx, "Dead Connection", TAITO, 1992, GAME_SHOOT,
	.input = input_deadconx,
	.dsw = dsw_deadconx,
	.romsw = romsw_deadconx,
	.clear = ClearDeadConnection,
	.video = &video_deadconx,
	.exec = execute_deadconx,
	.board = "D28",
	.sound = taito_ym2610_sound,
);

