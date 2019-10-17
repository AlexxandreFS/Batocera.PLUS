/******************************************************************************/
/*                                                                            */
/*                DYNAMITE LEAGUE (C) 1990 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc004vcu.h"
#include "tc140syt.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines


// Each LOAD_8_16 in GFX1 is doubled to make padding...
static struct ROM_INFO rom_dleague[] =
{
  {"c02-19a.33", 0x00020000, 0x7e904e45, REGION_ROM1, 0x000000, LOAD_8_16,   },
  {"c02-21a.36", 0x00020000, 0x18c8a32b, REGION_ROM1, 0x000001, LOAD_8_16,   },
  {"c02-20.34",  0x00010000, 0xcdf593f3, REGION_ROM1, 0x040000, LOAD_8_16,   },
  {"c02-22.37",  0x00010000, 0xf50db2d7, REGION_ROM1, 0x040001, LOAD_8_16,   },

  {"c02-23.40", 0x00010000, 0x5632ee49, REGION_ROM2, 0x000000, LOAD_NORMAL, },

  {"c02-02.15", 0x00080000, 0xb273f854, REGION_GFX1, 0x000000, LOAD_NORMAL, },
  {"c02-06.6",  0x00020000, 0xb8473c7b, REGION_GFX1, 0x080000, LOAD_8_16, },
  {"c02-10.14", 0x00020000, 0x50c02f0f, REGION_GFX1, 0x080001, LOAD_8_16, },
  {"c02-06.6",  0x00020000, 0xb8473c7b, REGION_GFX1, 0x080000, LOAD_8_16, },
  {"c02-10.14", 0x00020000, 0x50c02f0f, REGION_GFX1, 0x080001, LOAD_8_16, },

  {"c02-03.17", 0x00080000, 0xc3fd0dcd, REGION_GFX1, 0x100000, LOAD_NORMAL, },
  {"c02-07.7",  0x00020000, 0x8c1e3296, REGION_GFX1, 0x180000, LOAD_8_16, },
  {"c02-11.16", 0x00020000, 0xfbe548b8, REGION_GFX1, 0x180001, LOAD_8_16, },
  {"c02-06.6",  0x00020000, 0xb8473c7b, REGION_GFX1, 0x080000, LOAD_8_16, },
  {"c02-10.14", 0x00020000, 0x50c02f0f, REGION_GFX1, 0x080001, LOAD_8_16, },

  {"c02-24.19", 0x00080000, 0x18ef740a, REGION_GFX1, 0x200000, LOAD_NORMAL, },
  {"c02-08.8",  0x00020000, 0x1a3c2f93, REGION_GFX1, 0x280000, LOAD_8_16, },
  {"c02-12.18", 0x00020000, 0xb1c151c5, REGION_GFX1, 0x280001, LOAD_8_16, },
  {"c02-06.6",  0x00020000, 0xb8473c7b, REGION_GFX1, 0x080000, LOAD_8_16, },
  {"c02-10.14", 0x00020000, 0x50c02f0f, REGION_GFX1, 0x080001, LOAD_8_16, },

  {"c02-05.21", 0x00080000, 0xfe3a5179, REGION_GFX1, 0x300000, LOAD_NORMAL, },
  {"c02-09.9",  0x00020000, 0xa614d234, REGION_GFX1, 0x380000, LOAD_8_16, },
  {"c02-13.20", 0x00020000, 0x8eb3194d, REGION_GFX1, 0x380001, LOAD_8_16, },
  {"c02-06.6",  0x00020000, 0xb8473c7b, REGION_GFX1, 0x080000, LOAD_8_16, },
  {"c02-10.14", 0x00020000, 0x50c02f0f, REGION_GFX1, 0x080001, LOAD_8_16, },


  {"c02-18.22", 0x00002000, 0xc88f0bbe, REGION_GFX2, 0x000000, LOAD_NORMAL, },

  {"c02-01.31", 0x00080000, 0xd5a3d1aa, REGION_SMP1,0x00000, LOAD_NORMAL, },

  {           NULL,          0,          0,           0,        0,           0, },
};

static struct INPUT_INFO input_dleague[] =
{
   INP0( COIN1, 0x032004, 0x04 ),
   INP0( COIN2, 0x032004, 0x08 ),
   INP0( TILT, 0x032004, 0x02 ),
   INP0( SERVICE, 0x032004, 0x01 ),

   INP0( P1_START, 0x032004, 0x10 ),
   INP0( P1_UP, 0x032006, 0x01 ),
   INP0( P1_DOWN, 0x032006, 0x02 ),
   INP0( P1_LEFT, 0x032006, 0x04 ),
   INP0( P1_RIGHT, 0x032006, 0x08 ),
   INP0( P1_B1, 0x03200E, 0x01 ),
   INP0( P1_B2, 0x03200E, 0x02 ),
   INP0( P1_B3, 0x03200E, 0x04 ),

   INP0( P2_START, 0x032004, 0x20 ),
   INP0( P2_UP, 0x032006, 0x10 ),
   INP0( P2_DOWN, 0x032006, 0x20 ),
   INP0( P2_LEFT, 0x032006, 0x40 ),
   INP0( P2_RIGHT, 0x032006, 0x80 ),
   INP0( P2_B1, 0x03200E, 0x10 ),
   INP0( P2_B2, 0x03200E, 0x20 ),
   INP0( P2_B3, 0x03200E, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_dynamite_league_0[] =
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

static struct DSW_INFO dsw_dleague[] =
{
   { 0x032000, 0xFF, dsw_data_dynamite_league_0 },
   { 0x032002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_dynamite_league_0[] =
{
   { "Taito Japan (Japanese)", 0x00 },
   { "Taito America",          0x01 },
   { "Taito Japan",            0x02 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_dleague[] =
{
   { 0x05FFFF, 0x00, romsw_data_dynamite_league_0 },
   { 0,        0,    NULL },
};

static gfx_layout tilelayout =
{
	16,16,	/* 16x16 pixels */
	32768,	/* 32768 tiles */
	4,
	{ 0, 1, 2, 3 },
	{ 4, 0, 12, 8, 0x100000*8+4, 0x100000*8, 0x100000*8+12, 0x100000*8+8,
	    0x200000*8+4, 0x200000*8, 0x200000*8+12, 0x200000*8+8, 0x300000*8+4, 0x300000*8, 0x300000*8+12, 0x300000*8+8 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16,
		8*16, 9*16, 10*16, 11*16, 12*16, 13*16, 14*16, 15*16 },
	16*16
};

static gfx_layout charlayout =
{
	8, 8,	/* 8x8 pixels */
	256,	/* 256 chars */
	4,		/* 4 bit per pixel */
	{ 0x1000*8 + 8, 0x1000*8, 8, 0 },
	{ 0, 1, 2, 3, 4, 5, 6, 7 },
	{ 16*0, 16*1, 16*2, 16*3, 16*4, 16*5, 16*6, 16*7 },
	16*8
};

static struct GFX_LIST dleague_gfx[] =
{
	{ REGION_GFX1, &tilelayout },
	{ REGION_GFX2, &charlayout },
	{ 0,           NULL        },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_FG0;

static void setup_dleague() {
/*    YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000); */

   AddTaitoYM2610(0x033A, 0x02A7, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   GFX_FG0   = RAM+0x40000;
   RAM_VIDEO = RAM+0x10000;
   RAM_COLOUR= RAM+0x31000+0x800;
   RAM_INPUT = RAM+0x32000;

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x8000);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x0464],0x4EF9);		//	jmp	$300
   WriteLong68k(&ROM[0x0466],0x00000300);

   WriteLong68k(&ROM[0x0300],0x46FC2000);	//	move	#$2000,SR
   WriteLong68k(&ROM[0x0304],0x13FC0000);	// 	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0308],0x00AA0000);
   WriteWord68k(&ROM[0x030C],0x6100-10);	//	bra.s	<loop>

   // Init tc0004vcu emulation
   // ------------------------

   tc0004vcu.RAM	= RAM_VIDEO;
   tc0004vcu.GFX_BG0	= NULL;
   tc0004vcu.GFX_FG0	= GFX_FG0;
   tc0004vcu.tile_mask	= 0x7FFF;
   tc0004vcu.bmp_x	= 64;
   tc0004vcu.bmp_y	= 64;
   tc0004vcu.bmp_w	= 320;
   tc0004vcu.bmp_h	= 240;
   tc0004vcu.scr_x	= 16-1;
   tc0004vcu.scr_y	= 32-1;

   tc0004vcu_init();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x420FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByte(0x500000, 0x500FFF, NULL, RAM+0x031000);			// COLOR RAM
   AddReadByte(0x200000, 0x20000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x300000, 0x300003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x420FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWord(0x500000, 0x500FFF, NULL, RAM+0x031000);			// COLOR RAM
   AddReadWord(0x200000, 0x20000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x420FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0x500000, 0x500FFF, NULL, RAM+0x031000);		// COLOR RAM
   AddWriteByte(0x200000, 0x20000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0x300000, 0x300003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x420FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0x500000, 0x500FFF, NULL, RAM+0x031000);		// COLOR RAM
   AddWriteWord(0x200000, 0x20000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

void load_dleague(void)
{
   if(!(RAM=AllocateMem(0x80000))) return;

   RAMSize=0x48000+0x10000;

   setup_dleague();
}

void ClearDLeague(void)
{
   RemoveTaitoYM2610();
}

void execute_dleague(void)
{
   //print_ingame(60,gettext("%04x"),ReadWord(&RAM[0x30800]));

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);
   cpu_interrupt(CPU_68K_0, 3);

   Taito2610_Frame();			// Z80 and YM2610
}

void DrawDLeague(void)
{
   ClearPaletteMap();

   if (!tc0004vcu.GFX_BG0) {
     tc0004vcu.GFX_BG0 = GFX;
     tc0004vcu.GFX_BG0_MSK = gfx_solid[0];
   }

   // Init tc0180vcu emulation
   // ------------------------

   tc0004vcu_layer_count = 0;

   // BG0
   // ---

   tc0004vcu_render_bg0();

   // BG1
   // ---

   tc0004vcu_render_bg1();

   // OBJECT
   // ------

   tc0004vcu_render_obj();

   // FG0
   // ---

   //tc0004vcu_render_fg0();
}
static struct VIDEO_INFO video_dleague =
{
   DrawDLeague,
   320,
   240,
   64,
   VIDEO_ROTATE_NORMAL,
   dleague_gfx,
};
static struct DIR_INFO dir_dleague[] =
{
   { "dynamite_league", },
   { "dleague", },
   { NULL, },
};
GAME( dleague, "Dynamite League (Mame)", TAITO, 1990, GAME_SPORTS | GAME_PARTIALLY_WORKING,
	.input = input_dleague,
	.dsw = dsw_dleague,
	.romsw = romsw_dleague,
	.clear = ClearDLeague,
	.video = &video_dleague,
	.exec = execute_dleague,
	.board = "C02",
	.sound = taito_ym2610_sound,
);

