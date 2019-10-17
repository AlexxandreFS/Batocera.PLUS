#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*      METAL BLACK (C) 1991 TAITO CORPORATION (PROJECT: GUN FRONTIER 2)      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "tc006vcu.h"
#include "tc200obj.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines


static struct ROM_INFO rom_metalb[] =
{
   {   "d12-01.20", 0x00100000, 0xb81523b9, 0, 0, 0, },
   {   "d12-02.10", 0x00100000, 0x79263e74, 0, 0, 0, },
   {   "d12-03.14", 0x00080000, 0x46b498c0, 0, 0, 0, },
   {   "d12-04.13", 0x00080000, 0xab66d141, 0, 0, 0, },
   {   "d12-05.16", 0x00080000, 0x7fd036c5, 0, 0, 0, },
   {   "d12-06.6", 0x00020000, 0x131df731, 0, 0, 0, },
   {   "d12-07.9", 0x00020000, 0xe07f5136, 0, 0, 0, },
   {   "d16-18.7", 0x00040000, 0x5216d092, 0, 0, 0, },
   {   "d16-16.8", 0x00040000, 0x3150be61, 0, 0, 0, },
   {   "d12-13.5", 0x00020000, 0xbcca2649, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_metalb[] =
{
   INP0( COIN1, 0x00000E, 0x04 ),
   INP0( COIN2, 0x00000E, 0x08 ),
   INP0( TILT, 0x00000E, 0x01 ),
   INP0( SERVICE, 0x00000E, 0x02 ),

   INP0( P1_START, 0x000004, 0x80 ),
   INP0( P1_UP, 0x000004, 0x01 ),
   INP0( P1_DOWN, 0x000004, 0x02 ),
   INP0( P1_LEFT, 0x000004, 0x04 ),
   INP0( P1_RIGHT, 0x000004, 0x08 ),
   INP0( P1_B1, 0x000004, 0x10 ),
   INP0( P1_B2, 0x000004, 0x20 ),
   INP0( P1_B3, 0x000004, 0x40 ),

   INP0( P2_START, 0x000006, 0x80 ),
   INP0( P2_UP, 0x000006, 0x01 ),
   INP0( P2_DOWN, 0x000006, 0x02 ),
   INP0( P2_LEFT, 0x000006, 0x04 ),
   INP0( P2_RIGHT, 0x000006, 0x08 ),
   INP0( P2_B1, 0x000006, 0x10 ),
   INP0( P2_B2, 0x000006, 0x20 ),
   INP0( P2_B3, 0x000006, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_metal_black_0[] =
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

static struct DSW_DATA dsw_data_metal_black_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_DSWB_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT4,           0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "5",                     0x20},
   { "2",                     0x10},
   { "1",                     0x00},
   { _("Continue Mode"),         0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Simultaneous Play"),     0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_metalb[] =
{
   { 0x000000, 0xFF, dsw_data_metal_black_0 },
   { 0x000002, 0xFF, dsw_data_metal_black_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_metal_black_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito",                 0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_metalb[] =
{
   { 0x07FFFF, 0x03, romsw_data_metal_black_0 },
   { 0,        0,    NULL },
};




static struct ROM_INFO rom_metalbj[] =
{
   {   "d12-01.20", 0x00100000, 0xb81523b9, 0, 0, 0, },
   {   "d12-02.10", 0x00100000, 0x79263e74, 0, 0, 0, },
   {   "d12-03.14", 0x00080000, 0x46b498c0, 0, 0, 0, },
   {   "d12-04.13", 0x00080000, 0xab66d141, 0, 0, 0, },
   {   "d12-05.16", 0x00080000, 0x7fd036c5, 0, 0, 0, },
   {   "d12-06.6", 0x00020000, 0x131df731, 0, 0, 0, },
   {   "d12-07.9", 0x00020000, 0xe07f5136, 0, 0, 0, },
   {   "d12-11.7", 0x00040000, 0xaf9ee28d, 0, 0, 0, },
   {   "d12-12.8", 0x00040000, 0x556f82b2, 0, 0, 0, },
   {   "d12-13.5", 0x00020000, 0xbcca2649, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_INFO romsw_metalbj[] =
{
   { 0x07FFFF, 0x01, romsw_data_metal_black_0 },
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

static UINT8 *RAM_OBJECT;
static UINT8 *RAM_INPUT;

static void BadWriteWord(UINT32 address, UINT16 data)
{
#ifdef RAINE_DEBUG
      if(address!=0x600000) print_debug("Ww(%06x,%04x) [%06x]\n",address,data,s68000context.pc);
#endif
}

static void load_metalb(void)
{
   int ta,tb;

   if(!(GFX=AllocateMem(0x400000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x200000;

   tb=0;
   if(!load_rom_index(0, RAM, 0x100000)) return;	// 16x16 SPRITES ($2000)
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }

   tb=0;
   if(!load_rom_index(2, RAM, 0x80000)) return;	// 16x16 TILES ($2000)
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      GFX_BG0[tb+0]=RAM[ta]&15;
      GFX_BG0[tb+1]=RAM[ta]>>4;
      GFX_BG0[tb+2]=RAM[ta+1]&15;
      GFX_BG0[tb+3]=RAM[ta+1]>>4;
   }
   tb=4;
   if(!load_rom_index(3, RAM, 0x80000)) return;	// 16x16 TILES
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      GFX_BG0[tb+0]=RAM[ta]&15;
      GFX_BG0[tb+1]=RAM[ta]>>4;
      GFX_BG0[tb+2]=RAM[ta+1]&15;
      GFX_BG0[tb+3]=RAM[ta+1]>>4;
   }

   FreeMem(RAM);

   memset(GFX_SPR+0x000F00,0x00,0x100);			// Mask Sprite
   memset(GFX_SPR+0x168C00,0x00,0x100);			// Sun Sprite

   RAMSize=0x40000+0x20000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0xC0000))) return;

   if(!load_rom_index(8, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(7, RAM, 0x40000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom_index(6, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom_index(5, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom_index(9, Z80ROM, 0x20000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x180000))) return;
   if(!load_rom_index(4,PCMROM+0x00000,0x080000)) return;	// ADPCM A rom
   if(!load_rom_index(1,PCMROM+0x80000,0x100000)) return;	// ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x080000, 0x100000);

   AddTaitoYM2610(0x0217, 0x0180, 0x20000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x34100,0xFF,0x00020);

   if(is_current_game("metalb")){

   WriteWord68k(&ROM[0x0248E],0x4EF9);		// jmp $300
   WriteLong68k(&ROM[0x02490],0x00000300);
   WriteLong68k(&ROM[0x00300],0x4EB820DE);	// jsr <random gen>
   WriteLong68k(&ROM[0x00304],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00308],0x00AA0000);
   WriteWord68k(&ROM[0x0030C],0x6100-14);	// bra.s <loop>

   }
   else{

   WriteWord68k(&ROM[0x024BA],0x4EF9);		// jmp $300
   WriteLong68k(&ROM[0x024BC],0x00000300);
   WriteLong68k(&ROM[0x00300],0x4EB8210A);	// jsr <random gen>
   WriteLong68k(&ROM[0x00304],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00308],0x00AA0000);
   WriteWord68k(&ROM[0x0030C],0x6100-14);	// bra.s <loop>

   }

   RAM_OBJECT = RAM+0x10000;
   RAM_INPUT  = RAM+0x34100;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);

   InitPaletteMap(RAM+0x30000, 0x200, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   RAM_BG0=RAM+0x23000;
   RAM_BG1=RAM+0x22000;
   RAM_BG2=RAM+0x21000;
   RAM_BG3=RAM+0x20000;

   RAM_SCR0=RAM+0x34006;
   RAM_SCR1=RAM+0x34004;
   RAM_SCR2=RAM+0x34002;
   RAM_SCR3=RAM+0x34000;
   RAM_SCR4=RAM+0x34018;

   SCR0_XOFS=0x0036;
   SCR1_XOFS=0x0032;
   SCR2_XOFS=0x002E;
   SCR3_XOFS=0x002A;
   SCR4_XOFS=0x0039;

   SCR0_YOFS=0x0014;
   SCR1_YOFS=0x0014;
   SCR2_YOFS=0x0014;
   SCR3_YOFS=0x0014;
   SCR4_YOFS=0x0014;

   // Init tc0006vcu emulation
   // ------------------------

   if(!(tc0006vcu.GFX_FG = AllocateMem(0x4000))) return;

   tc0006vcu.RAM	= RAM+0x20000;
   tc0006vcu.RAM_SCR	= RAM+0x34000;
   tc0006vcu.GFX_BG	= GFX_BG0;
   tc0006vcu.GFX_BG_MASK= GFX_BG0_SOLID;
   tc0006vcu.tile_mask  = 0x1FFF;
   tc0006vcu.mapper	= &Map_12bit_RGBx;
   tc0006vcu.pal_ofs	= 0x100;
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

   tc0200obj.RAM	= RAM_OBJECT+0x0000;
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 48;
   tc0200obj.bmp_y	= 48;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_12bit_RGBx;
   tc0200obj.tile_mask	= 0x1FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;
   tc0200obj.cols	= 16;

   init_tc0200obj();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xC0000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x0BFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x300000, 0x30FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x500000, 0x50FFFF, NULL, RAM+0x020000);			// SCREEN RAM
   AddReadByte(0x700000, 0x703FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadByte(0x800000, 0x80000F, tc0220ioc_rb_bswap, NULL);		// INPUT
   AddReadByte(0x900000, 0x900003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x300000, 0x30FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0x500000, 0x50FFFF, NULL, RAM+0x020000);			// SCREEN RAM
   AddReadWord(0x700000, 0x703FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadWord(0x800000, 0x80000F, tc0220ioc_rw_bswap, NULL);		// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x300000, 0x30FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0x500000, 0x50DFFF, NULL, RAM+0x020000);		// SCREEN RAM
   AddWriteByte(0x50E000, 0x50FFFF, tc0006vcu_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x700000, 0x703FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteByte(0x900000, 0x900003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x800000, 0x80000F, tc0220ioc_wb_bswap, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x300000, 0x30FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x500000, 0x50DFFF, NULL, RAM+0x020000);		// SCREEN RAM
   AddWriteWord(0x50E000, 0x50FFFF, tc0006vcu_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x700000, 0x703FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteWord(0x530000, 0x5300FF, NULL, RAM+0x034000);		// SCROLL
   AddWriteWord(0x800000, 0x80000F, tc0220ioc_ww_bswap, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_metalb(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 5);

   Taito2610_Frame();			// Z80 and YM2610

   // IntF3System();

   debug_tc0006vcu();
}

static UINT8 bg_pri[32][4] =
{
   { 0, 1, 2, 3, },	// 0x00
   { 0, 1, 2, 3, },	// 0x01
   { 0, 1, 2, 3, },	// 0x02
   { 0, 1, 2, 3, },	// 0x03
   { 0, 1, 2, 3, },	// 0x04
   { 0, 1, 2, 3, },	// 0x05
   { 0, 1, 2, 3, },	// 0x06
   { 0, 1, 2, 3, },	// 0x07
   { 0, 1, 2, 3, },	// 0x08
   { 0, 1, 2, 3, },	// 0x09
   { 0, 1, 2, 3, },	// 0x0A
   { 0, 1, 2, 3, },	// 0x0B
   { 0, 3, 1, 2, },	// 0x0C
   { 0, 1, 2, 3, },	// 0x0D
   { 0, 1, 2, 3, },	// 0x0E
   { 3, 0, 1, 2, },	// 0x0F
   { 3, 0, 1, 2, },	// 0x10
   { 0, 1, 2, 3, },	// 0x11
   { 3, 2, 1, 0, },	// 0x12
   { 3, 2, 1, 0, },	// 0x13
   { 0, 1, 2, 3, },	// 0x14
   { 0, 1, 2, 3, },	// 0x15
   { 0, 1, 2, 3, },	// 0x16
   { 0, 1, 2, 3, },	// 0x17
   { 0, 1, 2, 3, },	// 0x18
   { 0, 1, 2, 3, },	// 0x19
   { 0, 1, 2, 3, },	// 0x1A
   { 0, 1, 2, 3, },	// 0x1B
   { 0, 1, 2, 3, },	// 0x1C
   { 0, 1, 2, 3, },	// 0x1D
   { 0, 3, 2, 1, },	// 0x1E
   { 0, 3, 2, 1, },	// 0x1F
};

static void DrawMetalBlack(void)
{
   UINT32 i;

   ClearPaletteMap();

   tc0006vcu_layer_count = 0;

   i = ReadWord(RAM+0x3401E) & 0x1F;

   tc0006vcu_render_layer(bg_pri[i][0]);

   tc0006vcu_render_layer(bg_pri[i][1]);

   tc0006vcu_render_layer(bg_pri[i][2]);

   tc0006vcu_render_layer(bg_pri[i][3]);

   render_tc0200obj_mapped(255);

   tc0006vcu_render_fg0();
}


static struct VIDEO_INFO video_metalb =
{
   DrawMetalBlack,
   320,
   224,
   48,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_metalb[] =
{
   { "metal_black", },
   { "metalb", },
   { NULL, },
};
GME( metalb, "Metal Black", TAITO, 1991, GAME_SHOOT,
	.romsw = romsw_metalb,
	.board = "D16",
);
static struct DIR_INFO dir_metalbj[] =
{
   { "metal_black_japanese", },
   { "metalbj", },
   { ROMOF("metalb"), },
   { CLONEOF("metalb"), },
   { NULL, },
};
CLNE( metalbj,metalb, "Metal Black Japanese", TAITO, 1991, GAME_SHOOT,
	.romsw = romsw_metalbj,
	.board = "D12",
);

