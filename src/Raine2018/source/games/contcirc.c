#define DRV_DEF_SOUND contcirc_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*            CONTINENTAL CIRCUS (C) 1987/1989 TAITO CORPORATION              */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc150rod.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "zoom/16x8.h"		// 16x8 zoomed sprite routines
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines
#include "2610intf.h"
#ifdef SDL
#include "sdl/control_internal.h"
#endif

#include "taito_z.h"


static struct INPUT_INFO input_contcirc[] =
{
   INP1( COIN1, 0x022804, 0x08 ),
   INP1( COIN2, 0x022804, 0x04 ),
   INP0( TILT, 0x022806, 0x04 ),
   INP0( SERVICE, 0x022804, 0x10 ),

   INP0( P1_START, 0x022806, 0x08 ),
   INP1( P1_LEFT, 0x022818, 0xFF ),
   INP1( P1_RIGHT, 0x02281A, 0xFF ),

   { KB_DEF_P1_B1,        "Accelerate",            0x022820, 0xFF, BIT_ACTIVE_1 },	// Accelerate - Analogue uses bit#567
   { KB_DEF_P1_B2,        "Brake",                 0x022822, 0xFF, BIT_ACTIVE_1 },	// Brake      - Analogue uses bit#567 (not available in digital mode!)
   { KB_DEF_P1_B3,        "Gear Shift",            0x022824, 0xFF, BIT_ACTIVE_1 },	// Gear Shift - High/Low
   { KB_DEF_P1_B4,        "Gear Low",            0x022825, 0x01, BIT_ACTIVE_0 },	// Gear Shift - High/Low
   { KB_DEF_P1_B5,        "Gear High",           0x022825, 0x02, BIT_ACTIVE_0 },	// Gear Shift - High/Low

   END_INPUT
};

#define TAITO_Z_COINAGE_WORLD_8 \
  { MSG_COIN1, 0x30, 4 },\
  { MSG_4COIN_1PLAY, 0x00, 0x00 },\
  { MSG_3COIN_1PLAY, 0x10, 0x00 },\
  { MSG_2COIN_1PLAY, 0x20, 0x00 },\
  { MSG_1COIN_1PLAY, 0x30, 0x00 },\
  { MSG_COIN2, 0xc0, 4 },\
  { MSG_1COIN_2PLAY, 0xc0, 0x00 },\
  { MSG_1COIN_3PLAY, 0x80, 0x00 },\
  { MSG_1COIN_4PLAY, 0x40, 0x00 },\
  { MSG_1COIN_6PLAY, 0x00, 0x00 },\

static struct DSW_DATA dsw_data_contcirc_0[] =
{
  { MSG_CABINET, 0x01, 2 },
  { MSG_UPRIGHT, 0x01},
  { _("Cockpit"), 0x00},	// analogue accelerator pedal
  { MSG_UNKNOWN, 0x02, 2 },
  { MSG_OFF, 0x02},
  { MSG_ON, 0x00},
  { MSG_SERVICE, 0x04,2 },
  { MSG_ON, 0},
  { MSG_OFF, 0x04},
	TAITO_Z_COINAGE_WORLD_8
  { MSG_DEMO_SOUND, 0x08, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x08},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_contcirc_1[] =
{
  { _("Difficulty 1 (time/speed)"), 0x03, 4 },
  { MSG_EASY, 0x02},
  { MSG_NORMAL, 0x03},
  { MSG_HARD, 0x01},
  { MSG_HARDEST, 0x00},
  { _("Difficulty 2 (other cars)"), 0x0c, 4 },
  { MSG_EASY, 0x08},
  { MSG_NORMAL, 0x0c},
  { MSG_HARD, 0x04},
  { MSG_HARDEST, 0x00},
  { _("Steering wheel"), 0x10, 2 },
  { _("Free"), 0x10},
  { _("Locked"), 0x00},
  { _("Enable 3d alternate frames"), 0x20, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x20},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_contcirc[] =
{
   { 0x022800, 0xFF, dsw_data_contcirc_0 },
   { 0x022802, 0xDF, dsw_data_contcirc_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_continental_circus_0[] =
{
   { "Taito Japan",                     0x01 },
   { "Taito America (US Navy License)", 0x02 },
   { "Taito Japan (US Navy License)",   0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_contcirc[] =
{
   { 0x07FFFF, 0x03, romsw_data_continental_circus_0 },
   { 0,        0,    NULL },
};


static struct ROM_INFO rom_contcrcu[] =
{
  // road lines
  { "b33-01.3", 0x80000, 0xf11f2be8, REGION_GFX3, 0x00000, LOAD_NORMAL },
  // GFX1 : scr (8x8)
  { "b33-02.57", 0x80000, 0xf6fb3ba2, REGION_GFX1, 0x00000, LOAD_NORMAL },
   {  "b33_03", 0x00080000, 0x4f6c36d9, 0, 0, 0, },
   {  "b33_04", 0x00080000, 0x8df866a2, 0, 0, 0, },
   {  "b33_05", 0x00080000, 0xbddf9eea, 0, 0, 0, },
   {  "b33_06", 0x00080000, 0x2cb40599, 0, 0, 0, },
  // sprite map
  { "b33-07.64", 0x80000, 0x151e1f52, REGION_USER1, 0x00000, LOAD_NORMAL },
  { "b33-09.18", 0x80000, 0x1e6724b5, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "b33-10.17", 0x80000, 0xe9ce03ab, REGION_SMP1, 0x80000, LOAD_NORMAL },
  { "b33-08.19", 0x80000, 0xcaa1c4c8, REGION_SMP2, 0x00000, LOAD_NORMAL },
   {  "b33_30", 0x00010000, 0xd8746234, 0, 0, 0, },
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "ic25",  0xf5c92e42, "ic26",  0xe7c1d1fa),
  LOAD8_16(  REGION_CPU1,  0x40000,  0x20000,
            "ic35",  0x16522f2d, "ic36",  0xd6741e33),
   {  "b14-30", 0x00010000, 0xdccb0c7f, 0, 0, 0, },
   {       "b14-31", 0x00002000, 0x5c6b013d, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_contcirc[] =
{
  // road lines
  { "b33-01.3", 0x80000, 0xf11f2be8, REGION_GFX3, 0x00000, LOAD_NORMAL },
  // GFX1 : scr (8x8)
  { "b33-02.57", 0x80000, 0xf6fb3ba2, REGION_GFX1, 0x00000, LOAD_NORMAL },
   // sprites 16x8
  { "b33-06", 0x080000, 0x2cb40599, REGION_GFX2, 0x000000, LOAD_8_32 },
  { "b33-05", 0x080000, 0xbddf9eea, REGION_GFX2, 0x000001, LOAD_8_32 },
  { "b33-04", 0x080000, 0x8df866a2, REGION_GFX2, 0x000002, LOAD_8_32 },
  { "b33-03", 0x080000, 0x4f6c36d9, REGION_GFX2, 0x000003, LOAD_8_32 },
  // sprite map
  { "b33-07.64", 0x80000, 0x151e1f52, REGION_USER1, 0x00000, LOAD_NORMAL },
  { "b33-09.18", 0x80000, 0x1e6724b5, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "b33-10.17", 0x80000, 0xe9ce03ab, REGION_SMP1, 0x80000, LOAD_NORMAL },
  { "b33-08.19", 0x80000, 0xcaa1c4c8, REGION_SMP2, 0x00000, LOAD_NORMAL },
  { "b33-30.11", 0x10000, 0xd8746234, 0, 0, 0 },
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "ic25",  0xf5c92e42, "ic26",  0xe7c1d1fa),
  LOAD8_16(  REGION_ROM1,  0x40000,  0x00020000,
             "ic35",  0x16522f2d,  "cc_36.bin",  0xa1732ea5),
   {  "b14-30", 0x00010000, 0xdccb0c7f, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_INFO romsw_contcrcu[] =
{
   { 0x07FFFF, 0x02, romsw_data_continental_circus_0 },
   { 0,        0,    NULL },
};


#define OBJ_A_COUNT	(0x4D61)

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
static UINT8 *GFX_OBJ_A_SOLID;

static UINT8 *zoom16_ofs;
static UINT8 *zoom8_ofs;

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_LINES;

/* road - line - left - right */

static UINT8 PAL_MAP[0x100] =
{
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0xC, 0x9, 0xA, 0xB, 0x0, 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
};

static void load_actual(int romset)
{
   GFX_BG0_SOLID = NULL;

   if (!(GFX_LINES = process_lines(REGION_GFX3))) return;

   OBJECT_MAP = load_region[REGION_USER1];


   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;

   /*-----[Sound Setup]-----*/

   // Better to keep the manual loading for this for now : the ram is
   // used in the Z80ROM area and would not be saved if we used automatic
   // loading.
   Z80ROM=RAM+0x50000;
   if(!load_rom_index(10, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   AddTaitoYM2610(0x034D, 0x02BF, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x22800,0xFF,0x00800);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x29000;
   GFX_FG0    = RAM+0x3C000;
   RAM_INPUT  = RAM+0x22800;

   tc0110pcr_init_typeb(RAM+0x20000, 1, 0);

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
   InitPaletteMap(RAM+0x20000, 0x100, 0x10, 0x8000);

   // Main Checksum
   // -------------

   WriteLong68k(&ROM[0x00AB4],0x4E714E71);	//	nop; nop
   WriteLong68k(&ROM[0x00AB8],0x4E714E71);	//	nop; nop

   // Main Checksum
   // -------------

   WriteLong68k(&ROM[0x409AC],0x4E714E71);	//	nop; nop
   WriteLong68k(&ROM[0x409B0],0x4E714E71);	//	nop; nop
   WriteWord68k(&ROM[0x409B4],0x4E71);		//	nop

   // Main 68000 Speed Hack
   // ---------------------

   WriteLong68k(&ROM[0x00844],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x00848],0x00AA0000);	//
   WriteWord68k(&ROM[0x0084C],0x6100-10);	//	bra.s	<loop>

   // Sub 68000 Speed Hack
   // --------------------

   WriteLong68k(&ROM[0x40850],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x40854],0x00AA0000);	//
   WriteWord68k(&ROM[0x40858],0x6100-26);	//	bra.s	<loop>

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0150rod emulation
   // ------------------------

   tc0150rod.RAM  	= RAM + 0x38000;
   tc0150rod.GFX  	= GFX_LINES;
   tc0150rod.PAL  	= PAL_MAP;
   // tc0150rod.mapper	= &Map_15bit_xRGB;
   tc0150rod.bmp_x	= 32;
   tc0150rod.bmp_y	= 32;
   tc0150rod.bmp_w	= 320;
   tc0150rod.bmp_h	= 224;
   tc0150rod.scr_x	= 0;
   tc0150rod.scr_y	= 0 - (15 + 6);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=16;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=16;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=16;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;


   init_16x8_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1z();
   zoom8_ofs  = make_16x8_zoom_ofs_type1z();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_CPU1));

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadBW(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddRWBW(0x080000, 0x087FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadBW(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddRWBW(0x300000, 0x301FFF, NULL, RAM+0x038000);			// ROOT RAM
   AddRWBW(0x400000, 0x4007FF, NULL, RAM+0x022000);			// OBJECT RAM
   AddReadByte(0x420000, 0x420003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x100000, 0x100007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x206000, 0x206FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x206000, 0x206FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x220000, 0x22000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x100000, 0x100007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM+0x040000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x040000);			// 68000 ROM
   AddReadByteMC68000B(0x080000, 0x083FFF, NULL, RAM+0x008000);			// MAIN RAM
   AddReadByteMC68000B(0x084000, 0x087FFF, NULL, RAM+0x004000);			// COMMON RAM
   AddReadByteMC68000B(0x100000, 0x100003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x040000);			// 68000 ROM
   AddReadWordMC68000B(0x080000, 0x083FFF, NULL, RAM+0x008000);			// MAIN RAM
   AddReadWordMC68000B(0x084000, 0x087FFF, NULL, RAM+0x004000);			// COMMON RAM
   AddReadWordMC68000B(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadWordMC68000B(0x100000, 0x100003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x080000, 0x083FFF, NULL, RAM+0x008000);		// MAIN RAM
   AddWriteByteMC68000B(0x084000, 0x087FFF, NULL, RAM+0x004000);		// COMMON RAM
   AddWriteByteMC68000B(0x100000, 0x100003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x080000, 0x083FFF, NULL, RAM+0x008000);		// MAIN RAM
   AddWriteWordMC68000B(0x084000, 0x087FFF, NULL, RAM+0x004000);		// COMMON RAM
   AddWriteWordMC68000B(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWordMC68000B(0x100000, 0x100003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void load_contcirc(void)
{
   load_actual(0);
}

static void load_contcrcu(void)
{
   load_actual(1);
}

// Strange non linear mapping for accelerate & brake
static int accelerate_mapping[] = {0,1,3,2,6,7,5,4,4};

static void execute_contcirc(void)
{
   static int gear=0;
   static int gearflip=1;
   int using_wheel = !(RAM_INPUT[0] & 1);
#ifdef SDL
   if (analog_num < 0) using_wheel = 0;
#endif

   // Gear Control Hack

   if(RAM_INPUT[0x24]){
      if(!gearflip){
         gearflip=1;
         gear^=1;
         if(gear)
            print_ingame(60,gettext("Changed to High Gear"));
         else
            print_ingame(60,gettext("Changed to Low Gear"));
      }
   }
   else{
      gearflip=0;
      if (!(RAM_INPUT[0x25] & 1)) {
	gear = 0;
	print_ingame(1,gettext("Changed to Low Gear"));
      } else if (!(RAM_INPUT[0x25] & 2)) {
	gear = 1;
	print_ingame(1,gettext("Changed to High Gear"));
      }
   }

   if(gear)
      RAM_INPUT[0x06] &= ~0x10;
   else
      RAM_INPUT[0x06] |=  0x10;

   RAM_INPUT[0x04] &= 0x1F;
   RAM_INPUT[0x06] &= 0x1F;

   if (using_wheel) {
#ifdef SDL
     if (analog_normy < 0)  {
       int pos = -analog_normy/2048;
       RAM_INPUT[0x04] = (RAM_INPUT[4] & 0x1f) | (accelerate_mapping[((pos))]<<5);
     } else
       RAM_INPUT[4] &= 0x1f;
#else
     int pos = joy[0].stick[0].axis[1].pos;
     if (pos < 0)  {
       pos = -pos;
       if (pos > 63) pos = 63;
       RAM_INPUT[0x04] = (RAM_INPUT[4] & 0x1f) | (accelerate_mapping[((pos >> 3) & 7)]<<5);
     } else
       RAM_INPUT[4] &= 0x1f;
#endif
   } else if(RAM_INPUT[0x20]) {
     RAM_INPUT[0x04] |= 0x80;
   }
    // On the joystick/steering wheel, acceleration is on the axis 1, ranging
    // from 0 to -80 approx...


   if (using_wheel) { // same thing for the brake
#ifdef SDL
     if (analog_normy > 0) {
       int pos = analog_normy/2048;
       RAM_INPUT[0x06] = (RAM_INPUT[6] & 0x1f) | (accelerate_mapping[((pos))]<<5);
     } else
       RAM_INPUT[6] &= 0x1f;
#else
     int pos = joy[0].stick[0].axis[1].pos;
     if (pos > 0) {
       if (pos > 63) pos = 63;
       RAM_INPUT[0x06] = (RAM_INPUT[6] & 0x1f) | (accelerate_mapping[((pos >> 3) & 7)]<<5);
     } else
       RAM_INPUT[6] &= 0x1f;
#endif
   } else if(RAM_INPUT[0x22])
     RAM_INPUT[0x06] |= 0x80;

   // Wheel Hack

   RAM_INPUT[0x10] = 0x00;
   RAM_INPUT[0x12] = 0x00;

  if (using_wheel) {
     // steering wheel from -127 to +128 mapped to -32,+32
#ifdef SDL
     RAM_INPUT[0x10] = (-analog_normx)>>9;
     RAM_INPUT[0x12] = (-analog_normx)>>15;
#else
     int pos = joy[0].stick[0].axis[0].pos;
     RAM_INPUT[0x10] = -pos;
     if (pos < 0)
       RAM_INPUT[0X12] = 0x00;
     else if (pos > 0)
      RAM_INPUT[0x12] = 0xff;
#endif
   } else if(RAM_INPUT[0x18]){
     RAM_INPUT[0x10] = 0x50;
     RAM_INPUT[0x12] = 0x00;
   } else if(RAM_INPUT[0x1A]){
     RAM_INPUT[0x10] = 0xB0;
     RAM_INPUT[0x12] = 0xFF;
   }

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
      print_debug("PC0:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 6);

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
      print_debug("PC1:%06x SR1:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 6);

   Taito2610_Frame();			// Z80 and YM2610
}

/*

---+-------------------+--------------
 0 | xxxxxxx. ........ | zoom y
 0 | .......x xxxxxxxx | sprite y
 2 | .....xxx xxxxxxxx | tile number
 4 | x....... ........ | pri???
 4 | .x...... ........ | flip x
 4 | .......x xxxxxxxx | sprite x
 6 | xxxxxxxx ........ | colour bank
 6 | ........ .xxxxxxx | zoom x
---+-------------------+--------------

*/

static void render_z_system_sprites(int pri)
{
   int x,y,ta,tb,zz;
   int zx,zy,rx,ry,xx,zzx,zzy;
   UINT8 *map,*SPR_MAP;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;

   if(pri==0)
      pri = 0x80;
   else
      pri = 0x00;

   // OBJECT Z-SYSTEM
   // ---------------

   for(zz=0x227F8;zz>=0x22000;zz-=8){

      if((RAM[zz+5]&0x80)==pri){

      zx=(ReadWord(&RAM[zz+6])>>0)&0x7F;
      zy=(ReadWord(&RAM[zz+0])>>9)&0x7F;
      if((zx!=0)&&(zy!=0)){

         ta = ReadWord(&RAM[zz+2])&0x7FF;
         if(ta!=0){

            x=(0+32+ReadWord(&RAM[zz+4]))&0x1FF;

            y=(16+128+ReadWord(&RAM[zz+0])-zy)&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+6])>>8)&0xFF,
               16,
               map
            );

            zoom_dat_x = zoom16_ofs+(zx<<3);
            zoom_dat_y = zoom8_ofs+(zy<<4);

            SPR_MAP = OBJECT_MAP + (ta<<8);

            switch(RAM[zz+5]&0x40){
            case 0x00:

            xx=x;

            for(ry=0;ry<16;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<16;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            }

         }
      }
   }

   }
}

static void draw_continental_circus(void)
{
   ClearPaletteMap();
   if (!GFX_BG0_SOLID) {
     GFX_OBJ_A = gfx[0];
     GFX_OBJ_A_SOLID = gfx_solid[0]; // make_solid_mask_16x8(GFX_OBJ_A, OBJ_A_COUNT);
     GFX_BG0_SOLID   = gfx_solid[1]; // make_solid_mask_8x8 (GFX,       0x4000);
     tc0100scn[0].layer[0].GFX	=GFX;
     tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
     tc0100scn[0].layer[1].GFX	=GFX;
     tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
     init_tc0100scn(0);
   }


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

   // Z-SYSTEM OBJECT
   // ---------------

   render_z_system_sprites(0);

   // 3D-ROAD Z-SYSTEM
   // ----------------

   tc0150rod_init_palette();
   tc0150rod_render(0x000,0x800);

   // Z-SYSTEM OBJECT
   // ---------------

   render_z_system_sprites(1);

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);

   //tc0150rod_show_palette();
}




static struct VIDEO_INFO video_contcirc =
{
   draw_continental_circus,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
   taitoz_gfxdecodeinfo
};
static struct DIR_INFO dir_contcirc[] =
{
   { "continental_circus", },
   { "contcirc", },
   { "ctcircus", },
   { NULL, },
};
GME( contcirc, "Continental Circus", TAITO, 1989, GAME_RACE,
	.romsw = romsw_contcirc,
	.board = "B33",
);
static struct DIR_INFO dir_contcrcu[] =
{
   { "continental_circus_us", },
   { "continental_circus_usernate", },
   { "contcalt", },
   { "contcrcu", },
   { ROMOF("contcirc"), },
   { CLONEOF("contcirc"), },
   { NULL, },
};
GAME( contcrcu, "Continental Circus (US Set 1)", TAITO, 1987, GAME_RACE,
	.input = input_contcirc,
	.dsw = dsw_contcirc,
	.romsw = romsw_contcrcu,
	.video = &video_contcirc,
	.exec = execute_contcirc,
	.board = "B33",
);

