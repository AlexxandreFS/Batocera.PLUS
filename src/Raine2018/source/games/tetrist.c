#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                 TAITO TETRIS (C) 1989 TAITO CORPORATION                    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "blit.h"
#include "bsystem.h"


static struct ROM_INFO rom_tetrist[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
              "c12-03.bin",  0x38f1ed41,   "c12-02.bin",  0xed9530bc),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
              "c12-05.bin",  0x128e9927,   "c12-04.bin",  0x5da7a319),
  { "c12-06.bin", 0x10000, 0xf2814b38, REGION_ROM2, 0, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_tetrist[] =
{
   INP0( COIN1, 0x05800E, 0x04 ),
   INP0( COIN2, 0x05800E, 0x08 ),
   INP0( TILT, 0x05800E, 0x01 ),
   INP0( SERVICE, 0x05800E, 0x02 ),

   INP0( P1_START, 0x05800E, 0x40 ),
   INP0( P1_UP, 0x058004, 0x01 ),
   INP0( P1_DOWN, 0x058004, 0x02 ),
   INP0( P1_LEFT, 0x058004, 0x04 ),
   INP0( P1_RIGHT, 0x058004, 0x08 ),
   INP0( P1_B1, 0x058004, 0x10 ),
   INP0( P1_B2, 0x058004, 0x20 ),

   INP0( P2_START, 0x05800E, 0x80 ),
   INP0( P2_UP, 0x058006, 0x01 ),
   INP0( P2_DOWN, 0x058006, 0x02 ),
   INP0( P2_LEFT, 0x058006, 0x04 ),
   INP0( P2_RIGHT, 0x058006, 0x08 ),
   INP0( P2_B1, 0x058006, 0x10 ),
   INP0( P2_B2, 0x058006, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_taito_sega_tetris_0[] =
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

static struct DSW_INFO dsw_tetrist[] =
{
   { 0x058000, 0xFF, dsw_data_taito_sega_tetris_0 },
   { 0x058002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static UINT8 *RAM_INPUT;

static void load_tetrist(void)
{
   RAMSize=0x60000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   memcpy(Z80ROM,load_region[REGION_CPU2],0x10000);

   if(!(PCMROM=AllocateMem(0x100000))) return;
   memset(PCMROM,0x80,0x100000);
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x01BE, 0x016A, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x58000);

   RAM_INPUT = RAM+0x58000;

   WriteLong68k(&ROM[0x072E],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0732],0x00AA0000);	// Speed Hack
   WriteWord68k(&ROM[0x0736],0x6100-10);	// <Loop>


   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

/*
 *  StarScream Stuff follows
 */

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x11000, 0x100, 0x10, 0x1000);
   ByteSwap(ROM,0x80000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x800000, 0x807FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x408FFF, NULL, RAM+0x008000);			// ??? RAM
   AddReadByte(0x410000, 0x413FFF, NULL, RAM+0x013000);			// ??? RAM
   AddReadByte(0xA00000, 0xA01FFF, NULL, RAM+0x011000);			// COLOR RAM
   AddReadByte(0x440000, 0x47FFFF, NULL, RAM+0x018000);			// PIXEL RAM
   AddReadByte(0x600000, 0x60000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x800000, 0x807FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x408FFF, NULL, RAM+0x008000);			// ??? RAM
   AddReadWord(0x410000, 0x413FFF, NULL, RAM+0x013000);			// SCREEN RAM
   AddReadWord(0xA00000, 0xA01FFF, NULL, RAM+0x011000);			// COLOR RAM
   AddReadWord(0x440000, 0x47FFFF, NULL, RAM+0x018000);			// PIXEL RAM
   AddReadWord(0x600000, 0x60000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x800000, 0x807FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x440000, 0x47FFFF, NULL, RAM+0x018000);		// PIXEL RAM
   AddWriteByte(0x400000, 0x408FFF, NULL, RAM+0x008000);		// ??? RAM
   AddWriteByte(0x410000, 0x413FFF, NULL, RAM+0x013000);		// SCREEN RAM
   AddWriteByte(0xA00000, 0xA01FFF, NULL, RAM+0x011000);		// COLOR RAM
   AddWriteByte(0x418000, 0x41801F, NULL, RAM+0x058100);		// SCROLL RAM
   AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x600000, 0x60000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x800000, 0x807FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x440000, 0x47FFFF, NULL, RAM+0x018000);		// PIXEL RAM
   AddWriteWord(0x400000, 0x408FFF, NULL, RAM+0x008000);		// ??? RAM
   AddWriteWord(0x410000, 0x413FFF, NULL, RAM+0x013000);		// ??? RAM
   AddWriteWord(0xA00000, 0xA01FFF, NULL, RAM+0x011000);		// COLOR RAM
   AddWriteWord(0x418000, 0x41801F, NULL, RAM+0x058100);		// SCROLL RAM
   AddWriteWord(0x600000, 0x60000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_tetrist(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);
   cpu_interrupt(CPU_68K_0, 4);

   Taito2610_Frame();				// Z80 and YM2610
}

static void DrawTaitoTetris(void)
{
    ClearPaletteMap();
    draw_taitob_fb(0x1a000,0x40,RAM[0x05810F],0,0,1);

}
static struct VIDEO_INFO video_tetrist =
{
   DrawTaitoTetris,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL
};
static struct DIR_INFO dir_tetrist[] =
{
   { "taito_tetris", },
   { "taito_sega_tetris", },
   { "tetrist", },
   { "tetris", },
   { NULL, },
};
GME( tetrist, "Taito Tetris", TAITO, 1989, GAME_PUZZLE,
	.long_name_jpn = "ƒeƒgƒŠƒX",
	.board = "C12",
);

