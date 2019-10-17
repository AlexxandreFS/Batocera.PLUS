#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                    NINJA KIDS (C) 1990 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc200obj.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_ninjak[] =
{
   { "c85-04.1", 0x00080000, 0x5afb747e, 0, 0, 0, },
   {    "c85_xx.5", 0x00020000, 0x0ac2cba2, 0, 0, 0, },
   {   "c85_07.18", 0x00020000, 0x3eccfd0a, 0, 0, 0, },
   {   "c85_06.4", 0x00020000, 0xd126ded1, 0, 0, 0, },
   { "c85-01.16", 0x00100000, 0xa711977c, 0, 0, 0, },
   { "c85-02.15", 0x00100000, 0xa6ad0f3d, 0, 0, 0, },
   {    "c85_10x.19", 0x00020000, 0xba7e6e74, 0, 0, 0, },
   { "c85-05.11", 0x00080000, 0x3c1b0ed0, 0, 0, 0, },
   {  "c85-03.10", 0x00080000, 0x4cc7b9df, 0, 0, 0, },
   {   "c85-14.6", 0x00010000, 0xf2a52a51, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ninjak[] =
{
   INP0( COIN1, 0x02510D, 0x10 ),
   INP0( COIN2, 0x02510D, 0x20 ),
   INP0( TILT, 0x02510D, 0x01 ),
   INP0( SERVICE, 0x02510D, 0x02 ),

   INP0( P1_START, 0x025105, 0x80 ),
   INP0( P1_UP, 0x025105, 0x01 ),
   INP0( P1_DOWN, 0x025105, 0x02 ),
   INP0( P1_LEFT, 0x025105, 0x04 ),
   INP0( P1_RIGHT, 0x025105, 0x08 ),
   INP0( P1_B1, 0x025105, 0x10 ),
   INP0( P1_B2, 0x025105, 0x20 ),

   INP0( P2_START, 0x025107, 0x80 ),
   INP0( P2_UP, 0x025107, 0x01 ),
   INP0( P2_DOWN, 0x025107, 0x02 ),
   INP0( P2_LEFT, 0x025107, 0x04 ),
   INP0( P2_RIGHT, 0x025107, 0x08 ),
   INP0( P2_B1, 0x025107, 0x10 ),
   INP0( P2_B2, 0x025107, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_ninja_kids_0[] =
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

static struct DSW_INFO dsw_ninjak[] =
{
   { 0x025101, 0xFF, dsw_data_ninja_kids_0 },
   { 0x025103, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};


static struct ROMSW_DATA romsw_data_ninja_kids_0[] =
{
   { "Taito Japan (Japanese)", 0x01 },
   { "Taito America",          0x02 },
   { "Taito Japan",            0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_ninjak[] =
{
   { 0x03FFFF, 0x03, romsw_data_ninja_kids_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_OBJECT;
static UINT8 *RAM_SCROLL;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static int BadReadWord(UINT32 address)
{
       print_debug("Rw(%06x) [%06x]\n",address,s68000context.pc);
   return(0xFFFF);
}

static void load_ninjak(void)
{
   int ta,tb;

   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x500000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x100000;

   tb=0;
   if(!load_rom("c85-03.10", RAM, 0x80000)) return;		// 8x8 TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+0]=RAM[ta+1]>>4;
      GFX[tb+1]=RAM[ta+1]&15;
      GFX[tb+2]=RAM[ta+0]>>4;
      GFX[tb+3]=RAM[ta+0]&15;
      tb+=4;
   }
   if(!load_rom("c85-01.16", RAM, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++){
      GFX[tb++]=RAM[ta]&15;
      GFX[tb++]=RAM[ta]>>4;
   }
   if(!load_rom("c85-02.15", RAM, 0x100000)) return;
   for(ta=0;ta<0x100000;ta++){
      GFX[tb++]=RAM[ta]&15;
      GFX[tb++]=RAM[ta]>>4;
   }

   RAMSize=0x50000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom("c85_10x.19", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c85_xx.5", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("c85_07.18", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("c85_06.4", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("c85-14.6", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("c85-05.11",PCMROM+0x00000,0x80000)) return; // ADPCM A rom
   if(!load_rom("c85-04.1",PCMROM+0x80000,0x80000)) return; // ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x01BB, 0x015B, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x25100,0xFF,0x01000);

   RAM_VIDEO  = RAM+0x04000;
   RAM_OBJECT = RAM+0x14000;
   RAM_SCROLL = RAM+0x25000;

   GFX_FG0    = RAM+0x30000;

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x24000, 0x100, 0x10, 0x1000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x4000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   ROM[0x3F32]=0x4E;		// SKIP OLD CODE (NO ROOM FOR HACK)
   ROM[0x3F33]=0xF9;		// (JMP $7FF00)
   ROM[0x3F34]=0x00;
   ROM[0x3F35]=0x07;
   ROM[0x3F36]=0xFF;
   ROM[0x3F37]=0x00;

   ROM[0x7FF00]=0x46;		// MOVE #$2000,SR
   ROM[0x7FF01]=0xFC;
   ROM[0x7FF02]=0x20;
   ROM[0x7FF03]=0x00;

   ROM[0x7FF04]=0x13;		// move.b #$00,$AA0000
   ROM[0x7FF05]=0xFC;		// (Speed Hack)
   ROM[0x7FF06]=0x00;
   ROM[0x7FF07]=0x00;
   ROM[0x7FF08]=0x00;
   ROM[0x7FF09]=0xAA;
   ROM[0x7FF0A]=0x00;
   ROM[0x7FF0B]=0x00;

   ROM[0x7FF0C]=0x60;		// Loop
   ROM[0x7FF0D]=0x100-0x0A;

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
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
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
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
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
   tc0200obj.ofs_x	= 0 - 0x13;
   tc0200obj.ofs_y	= 0 - 0x60;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x2C000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x300000, 0x30000F, NULL, RAM+0x025100);			// INPUT
   AddReadByte(0x400000, 0x400003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0x200000, 0x200FFF, NULL, RAM+0x024000);			// COLOR RAM
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x100000, 0x103FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0x400000, 0x400003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x103FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x200000, 0x200FFF, NULL, RAM+0x024000);		// COLOR RAM
   AddWriteWord(0x820000, 0x82000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x380000, 0x38000F, NULL, RAM+0x025180);		// ???
   AddWriteWord(0x600000, 0x60000F, NULL, RAM+0x025280);		// SPRITE BANK
   AddWriteWord(0xB00000, 0xB0001F, NULL, RAM+0x025300);		// ?
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_ninjak(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610
}

static void DrawNinjaK(void)
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

   if(tc0100scn_layer_count==0){	// Check if Screen needs cleaning
      tc0100scn_layer_count++;
      clear_game_screen(0);
   }

   make_object_bank(RAM+0x025280);
   render_tc0200obj_mapped_soliltary_fighter();

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);

}

/*

NINJA KIDS (C)1990 TAITO CORP
-----------------------------

 System: Taito F2 System
    Cpu: 68000
Monitor: 320x224; Horizontal

68000 Memory Map
----------------

Start  | End    | Description
-------+--------+------------
000000 | 07FFFF | 68000 ROM
100000 | 103FFF | 68000 RAM
200000 | 200FFF | COLOR RAM
300000 | 30000F | INPUT/DSW
400000 | 400003 | SOUND COMM
800000 | 803FFF | BG0 RAM
804000 | 804FFF | FG0 RAM
806000 | 806FFF | FG0 GFX RAM
808000 | 80BFFF | BG1 RAM
820000 | 82000F | SCROLL RAM
900000 | 907FFF | OBJECT A RAM
908000 | 907FFF | OBJECT B RAM


Byte | Bit(s) | Function
-----+76543210+-----------------------------
  0  |...xxxxx| Sprite Number (high 5 bits)
  1  |xxxxxxxx| Sprite Number (low 8 bits)
  2  |........| <Unused> (Zoom-X)
  3  |........| <Unused> (Zoom-Y)
  4  |.......x| Y Position
  5  |xxxxxxxx| Y Position
  6  |.......x| X Position
  7  |xxxxxxxx| X Position
  8  |.......x| Flip X-Axis
  8  |......x.| Flip Y-Axis
  8  |.....x..| Use Previous X,Y,Colour Bank
  8  |....x...| ???
  8  |xxxx....| X/Y Relative Stuff
  9  |.xxxxxxx| Colour Bank (0-127)
  A  |........| <Unused>
  B  |........| <Unused>
  C  |........| <Unused>
  D  |........| <Unused>
  E  |........| <Unused>
  F  |........| <Unused>

*/
static struct VIDEO_INFO video_ninjak =
{
   DrawNinjaK,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ninjak[] =
{
   { "ninja_kids", },
   { "ninjak", },
   { NULL, },
};
GME( ninjak, "Ninja Kids", TAITO, 1990, GAME_BEAT,
	.romsw = romsw_ninjak,
	.long_name_jpn = "ニンジャキッズ",
	.board = "C85",
);

