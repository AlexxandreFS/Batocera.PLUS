#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                     KOSHIEN (C) 1991 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc200obj.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines

static struct ROM_INFO rom_koshien[] =
{
   {   "c81-01.bin", 0x00100000, 0x64b15d2a, 0, 0, 0, },
   {   "c81-02.bin", 0x00100000, 0x962461e8, 0, 0, 0, },
   {   "c81-03.bin", 0x00100000, 0x29bbf492, 0, 0, 0, },
   {   "c81-04.bin", 0x00080000, 0x1592b460, 0, 0, 0, },
   {   "c81-05.bin", 0x00080000, 0x9c3d71be, 0, 0, 0, },
   {   "c81-06.bin", 0x00080000, 0x927833b4, 0, 0, 0, },
   {   "c81-10.bin", 0x00020000, 0x8f98c40a, 0, 0, 0, },
   {   "c81-11.bin", 0x00020000, 0xb44ea8c9, 0, 0, 0, },
   {   "c81-12.bin", 0x00010000, 0x6e8625b6, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_koshien[] =
{
   INP0( COIN1, 0x03A106, 0x04 ),
   INP0( COIN2, 0x03A106, 0x08 ),
   INP0( TILT, 0x03A106, 0x01 ),
   INP0( SERVICE, 0x03A106, 0x02 ),

   INP0( P1_START, 0x03A104, 0x08 ),
   INP0( P1_UP, 0x03A10E, 0x01 ),
   INP0( P1_DOWN, 0x03A10E, 0x02 ),
   INP0( P1_LEFT, 0x03A10E, 0x04 ),
   INP0( P1_RIGHT, 0x03A10E, 0x08 ),
   INP0( P1_B1, 0x03A104, 0x01 ),
   INP0( P1_B2, 0x03A104, 0x02 ),
   INP0( P1_B3, 0x03A104, 0x04 ),

   INP0( P2_START, 0x03A104, 0x80 ),
   INP0( P2_UP, 0x03A10E, 0x10 ),
   INP0( P2_DOWN, 0x03A10E, 0x20 ),
   INP0( P2_LEFT, 0x03A10E, 0x40 ),
   INP0( P2_RIGHT, 0x03A10E, 0x80 ),
   INP0( P2_B1, 0x03A104, 0x10 ),
   INP0( P2_B2, 0x03A104, 0x20 ),
   INP0( P2_B3, 0x03A104, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_koshien_0[] =
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

static struct DSW_INFO dsw_koshien[] =
{
   { 0x03A100, 0xFF, dsw_data_koshien_0 },
   { 0x03A102, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_koshien_0[] =
{
   { "Taito Japan",           0x00 },
   { "Taito America",         0x01 },
   { "Taito Corporation",     0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_koshien[] =
{
   { 0x03FFFF, 0x00, romsw_data_koshien_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_OBJECT;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_INPUT;
static UINT8 *GFX_BANK;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void load_koshien(void)
{
   int ta,tb;

   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x200000+0x400000))) return;

   GFX_BG0	=GFX+0x000000;
   GFX_SPR	=GFX+0x200000;

   tb=0;
   if(!load_rom("c81-03.bin", RAM, 0x100000)) return;		// 8x8 TILES
   for(ta=0;ta<0x100000;ta+=2,tb+=4){
      GFX[tb+3]=RAM[ta]&15;
      GFX[tb+2]=RAM[ta]>>4;
      GFX[tb+1]=RAM[ta+1]&15;
      GFX[tb+0]=RAM[ta+1]>>4;
   }

   tb=0;
   if(!load_rom("c81-01.bin", RAM, 0x100000)) return;		// 16x16 SPRITES ($2000)
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }
   if(!load_rom("c81-02.bin", RAM, 0x100000)) return;		// 16x16 SPRITES ($2000)
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }

   if(!(RAM=AllocateMem(0x080000))) return;
   if(!(ROM=AllocateMem(0x100000))) return;

   if(!load_rom("c81-11.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c81-10.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   memset(ROM+0x40000,0x00,0x40000);
   if(!load_rom("c81-04.bin", ROM+0x80000, 0x80000)) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x48000;
   if(!load_rom("c81-12.bin", Z80ROM, 0x10000)) return;			// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("c81-05.bin", PCMROM+0x000000, 0x080000)) return;	// ADPCM A rom
   if(!load_rom("c81-06.bin", PCMROM+0x080000, 0x080000)) return;	// ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x01BA, 0x015A, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x20000;
   RAM_SCROLL = RAM+0x3A000;
   RAM_OBJECT = RAM+0x10000;
   RAM_COLOUR = RAM+0x30000;
   RAM_INPUT  = RAM+0x3A100;
   GFX_FG0    = RAM+0x40000;
   GFX_BANK   = RAM+0x3A200;

   RAMSize=0x68000;

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);


   // 68000 Speed Hack
   // ----------------
/*
   WriteWord68k(&ROM[0x084C],0x4EF9);		// jmp $300
   WriteLong68k(&ROM[0x084E],0x00000300);
   WriteLong68k(&ROM[0x00300],0x526DABF2);	// jsr <random gen>
   WriteLong68k(&ROM[0x00304],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x00308],0x00AA0000);
   WriteWord68k(&ROM[0x0030C],0x6100-14);	// bra.s <loop>
*/
   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX_BG0;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
// Mapper disabled
   tc0100scn[0].layer[0].tile_mask=0x7FFF;
   tc0100scn[0].layer[0].scr_x	=17;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX_BG0;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
// Mapper disabled
   tc0100scn[0].layer[1].tile_mask=0x7FFF;
   tc0100scn[0].layer[1].scr_x	=17;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=1;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
// Mapper disabled
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT+0x0000;
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
// Mapper disabled
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= -100;
   tc0200obj.ofs_y	= -16;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x300000, 0x30001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x320000, 0x320003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x300000, 0x30000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);		// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x320000, 0x320003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x300000, 0x30001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xB00000, 0xB0001F, NULL, GFX_BANK);			// BANK
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);		// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x300000, 0x30001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0xB00000, 0xB0001F, NULL, GFX_BANK);			// BANK
   AddWriteWord(0xA20000, 0xA20001, NULL, GFX_BANK+0x20);		// BANK
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_koshien(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 5);

   Taito2610_Frame();			// Z80 and YM2610
}

static void draw_koshien(void)
{
   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // OBJECT
   // ------

   make_object_bank_koshien(GFX_BANK+0x20);
   render_tc0200obj_mapped_soliltary_fighter();

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);
}
static struct VIDEO_INFO video_koshien =
{
   draw_koshien,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
GMEI( koshien, "Koshien", TAITO, 1990, GAME_SPORTS,
	.romsw = romsw_koshien,
	.board = "C81",
);

