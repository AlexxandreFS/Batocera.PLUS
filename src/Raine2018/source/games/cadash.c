#define DRV_DEF_SOUND taito_ym2151_sound
/******************************************************************************/
/*                                                                            */
/*                    CADASH (C) 1988 TAITO CORPORATION                       */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc002obj.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "asuka.h"
#include "def_dsw.h"


static struct ROM_INFO rom_cadash[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
                  "c21-14",  0x5daf13fb,       "c21-16",  0xcbaa2e75),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
                  "c21-13",  0x6b9e0ee9,       "c21-17",  0xbf9a578a),
   {       "c21-02.9", 0x00080000, 0x205883b9, REGION_GFX1, 0x000000, LOAD_NORMAL, },
   {       "c21-01.1", 0x00080000, 0x1ff6f39c, REGION_GFX2, 0x000000, LOAD_NORMAL, },
  { "c21-08.38", 0x10000, 0xdca495a0, REGION_ROM2, 0, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_cadashg[] =
{
  { "c21-23-1.12", 0x20000, 0x30ddbabe, REGION_CPU1, 0x00000, LOAD_8_16 },
  { "c21-25-1.16", 0x20000, 0x24e10611, REGION_CPU1, 0x00001, LOAD_8_16 },
  { "c21-22-1.11", 0x20000, 0xdaf58b2d, REGION_CPU1, 0x40000, LOAD_8_16 },
  { "c21-24-1.15", 0x20000, 0x2359b93e, REGION_CPU1, 0x40001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_cadash[] =
{
   INP0( COIN1, 0x01A00E, 0x01 ),
   INP0( COIN2, 0x01A00E, 0x02 ),
   INP0( TILT, 0x01A00E, 0x20 ),
   INP0( SERVICE, 0x01A00E, 0x10 ),

   INP0( P1_START, 0x01A00E, 0x08 ),
   INP0( P1_UP, 0x01A004, 0x80 ),
   INP0( P1_DOWN, 0x01A004, 0x40 ),
   INP0( P1_LEFT, 0x01A004, 0x20 ),
   INP0( P1_RIGHT, 0x01A004, 0x10 ),
   INP0( P1_B1, 0x01A004, 0x08 ),
   INP0( P1_B2, 0x01A004, 0x04 ),

   INP0( P2_START, 0x01A00E, 0x04 ),
   INP0( P2_UP, 0x01A006, 0x80 ),
   INP0( P2_DOWN, 0x01A006, 0x40 ),
   INP0( P2_LEFT, 0x01A006, 0x20 ),
   INP0( P2_RIGHT, 0x01A006, 0x10 ),
   INP0( P2_B1, 0x01A006, 0x08 ),
   INP0( P2_B2, 0x01A006, 0x04 ),

   END_INPUT
};

/* Stephh notes :
  - Region stored at 0x07fffe.w
  - Sets :
      * 'cadash'   : region = 0x0003
      * 'cadashj'  : region = 0x0001
      * 'cadashu'  : region = 0x0002
      * 'cadashfr' : region = 0x0003
      * 'cadashit' : region = 0x0003
  - These 5 games are 100% the same, only region differs !
    However each version requires its specific texts
  - Coinage relies on the region (code at 0x0013d6) :
      * 0x0001 (Japan) uses TAITO_COINAGE_JAPAN_OLD_LOC()
      * 0x0002 (US) uses TAITO_COINAGE_US_LOC()
      * 0x0003 (World) uses TAITO_COINAGE_WORLD_LOC()
  - Notice screen only if region = 0x0001 or region = 0x0002
  - FBI logo only if region = 0x0002
*/
static struct DSW_DATA dsw_data_cadash_0[] =
{
    DSW_TAITO_SCREEN_TEST_DEMO,
    DSW_REGION(1),
      DSW_TAITO_COINAGE_OLD_JAPAN,
    DSW_REGION(2),
      DSW_TAITO_COINAGE_US,
    DSW_REGION(3),
      DSW_TAITO_COINAGE_WORLD,
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_cadash_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Start Time"),            0x0C, 0x04 },
   { _("7 Mins"),                0x0C},
   { _("8 Mins"),                0x08},
   { _("6 Mins"),                0x04},
   { _("5 Mins"),                0x00},
   { _("Extra Clear Time"),      0x30, 0x04 },
   { _("None"),                  0x30},
   { _("+1 Min"),                0x20},
   { _("-1 Min"),                0x10},
   { _("-2 Mins"),               0x00},
   { _("Communication"),         0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Status for Comm"),       0x80, 0x02 },
   { _("Master"),                0x80},
   { _("Slave"),                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_cadash[] =
{
   { 0x01A000, 0xFF, dsw_data_cadash_0 },
   { 0x01A002, 0xFF, dsw_data_cadash_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_cadash_0[] =
{
   { "Taito Japan (cadashj)",          0x01 },
   { "Taito America (cadashu)",          0x02 },
   { "Taito Japan (World)",            0x03 },
   { NULL,                     0    },
};

static struct ROMSW_INFO romsw_cadash[] =
{
   { 0x07FFFF, 0x03, romsw_data_cadash_0 },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_cadashf[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
                  "c21-19",  0x4d70543b,       "c21-21",  0x0e5b9950),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
                  "c21-18",  0x8a19e59b,       "c21-20",  0xb96acfd9),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_cadashi[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
                "c21-14it",  0xd1d9e613,     "c21-16it",  0x142256ef),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
                "c21-13it",  0xc9cf6e30,     "c21-17it",  0x641fc9dd),
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_cadashj[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
             "c21-04.11",  0xcc22ebe5,  "c21-06.15",  0x26e03304),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
             "c21-03.10",  0xc54888ed,  "c21-05.14",  0x834018d2),
   {           NULL,          0,          0, 0, 0, 0, },
};

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *RAM_OBJECT;

static void load_cadash(void)
{
   RAMSize=0x34000;
   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x24000;
   memcpy(Z80ROM,load_region[REGION_CPU2],0x10000);

   AddTaitoYM2151(0x01AF, 0x0143, 0x10000, NULL, NULL);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x20000);

   tc0110pcr_init(RAM+0x1C000, 1);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x1000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B000;
   RAM_OBJECT = RAM+0x18000;
   RAM_INPUT  = RAM+0x1A000;
   GFX_FG0    = RAM+0x20000;

   // 68000 Speed Hack

   if(is_current_game("cadashj") || is_current_game("cadashg"))
   {
   WriteLong68k(&ROM[0x0132A],0x4EF84F00);

   WriteLong68k(&ROM[0x04F00],0x13FC0000);
   WriteLong68k(&ROM[0x04F04],0x00AA0000);

   WriteLong68k(&ROM[0x04F08],0x4EF8124C);
   }
   else
   {
   WriteLong68k(&ROM[0x013AC],0x4EF84F00);

   WriteLong68k(&ROM[0x04F00],0x13FC0000);
   WriteLong68k(&ROM[0x04F04],0x00AA0000);

   WriteLong68k(&ROM[0x04F08],0x4EF812CE);
   }

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------
   setup_asuka_layers(RAM_VIDEO,RAM_SCROLL,GFX_FG0,16,8,&RAM[0x1b010]);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.RAM	= RAM_OBJECT;
   tc0002obj.ofs_x	= 0;
   tc0002obj.ofs_y	= -8;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x107FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xB00000, 0xB007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x800000, 0x800FFF, NULL, RAM+0x018800);			// ??? RAM
   AddReadByte(0x900000, 0x90001F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x107FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xB00000, 0xB007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x800000, 0x800FFF, NULL, RAM+0x018800);			// ??? RAM
   AddReadWord(0x900000, 0x90001F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x0C0000, 0x0C0003, tc0140syt_read_main_68k, NULL); 	// SOUND
   AddReadWord(0xA00000, 0xA00007, tc0110pcr_rw, NULL);			// COLOUR RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x107FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xB00000, 0xB007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x800000, 0x800FFF, NULL, RAM+0x018800);		// ??? RAM
   AddWriteByte(0x900000, 0x90001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x107FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xB00000, 0xB007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xA00000, 0xA00007, tc0110pcr_ww, NULL);		// COLOUR RAM
   AddWriteWord(0x800000, 0x800FFF, NULL, RAM+0x018800);		// ??? RAM
   AddWriteWord(0x900000, 0x90001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x0C0000, 0x0C0003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteWord(0x080000, 0x080001, NULL, RAM+0x01B010);		// CTRL RAM
   AddWriteWord(0xC20000, 0xC2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_cadash(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 4);

   Taito2151_FrameRI();					// Z80 and YM2151
}

static struct VIDEO_INFO video_cadash =
{
   DrawAsuka,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
   asuka_gfx,
};
GMEI( cadash, "Cadash (World)", TAITO, 1989, GAME_BEAT,
	.romsw = romsw_cadash,
	.long_name_jpn = "カダッシュ American",
	.board = "C21",
);
static struct DIR_INFO dir_cadashf[] =
{
   { "cadash_french", },
   { "cadashfr", },
   { "cadashf", },
   { ROMOF("cadash"), },
   { CLONEOF("cadash"), },
   { NULL, },
};
CLNE( cadashf, cadash, "Cadash (France)", TAITO, 1989, GAME_BEAT,
	.romsw = romsw_cadash,
	.long_name_jpn = "カダッシュ French",
	.board = "C21",
);
static struct DIR_INFO dir_cadashi[] =
{
   { "cadash_italian", },
   { "cadashit", },
   { "cadashi", },
   { ROMOF("cadash"), },
   { CLONEOF("cadash"), },
   { NULL, },
};
CLNE( cadashi, cadash,"Cadash (Italy)", TAITO, 1989, GAME_BEAT,
	.romsw = romsw_cadash,
	.long_name_jpn = "カダッシュ Italian",
	.board = "C21",
);
static struct DIR_INFO dir_cadashj[] =
{
   { "cadash_japanese", },
   { "cadashj", },
   { ROMOF("cadash"), },
   { CLONEOF("cadash"), },
   { NULL, },
};
CLNE( cadashj, cadash, "Cadash (Japan)", TAITO, 1989, GAME_BEAT,
	.long_name_jpn = "カダッシュ",
	.board = "C21",
);
CLNEI( cadashg, cadash, "Cadash (Germany)", TAITO, 1989, GAME_MISC);

