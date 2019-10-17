/******************************************************************************/
/*                                                                            */
/*               EARTH JOKER (C) 1993 TAITO VISCO CORPORATION                 */
/*                                                                            */
/*                 MAZE OF FLOTT (C) 1989 TAITO CORPORATION                   */
/*                                                                            */
/*                    GALMEDES (C) 1992 VISCO CORPORATION                     */
/*                                                                            */
/*           KOKONTOUZAI ETO MONOGATARI (C) 1994 VISCO CORPORATION            */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc002obj.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "msm5205.h"
#include "2151intf.h"
#include "timer.h"
#include "blit.h" // clear_game_screen
#include "asuka.h"
#include "def_dsw.h"

/******************************************************************************/


static struct ROM_INFO rom_earthjkr[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
               "ej_3b.rom",  0xbdd86fc2,    "ej_3a.rom",  0x9c8050c6),
   {   "ej_30e.rom", 0x00080000, 0x49d1f77f, REGION_ROM1, 0x080000, LOAD_NORMAL, },
  { "ej_chr.rom", 0x80000, 0xac675297, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "ej_obj.rom", 0x80000, 0x5f21ac47, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "ej_1.rom", 0x10000, 0xcb4891db, REGION_GFX2, 0x80000, LOAD_8_16 },
  { "ej_0.rom", 0x10000, 0xb612086f, REGION_GFX2, 0x80001, LOAD_8_16 },
  { "ej_2.rom", 0x10000, 0x42ba2566, REGION_ROM2, 0, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_mofflott[] =
{
   INP0( COIN1, 0x01A00E, 0x04 ),
   INP0( COIN2, 0x01A00E, 0x08 ),
   INP0( TILT, 0x01A00E, 0x01 ),
   INP0( SERVICE, 0x01A00E, 0x02 ),

   INP0( P1_START, 0x01A00E, 0x40 ),
   INP0( P1_UP, 0x01A004, 0x01 ),
   INP0( P1_DOWN, 0x01A004, 0x02 ),
   INP0( P1_LEFT, 0x01A004, 0x04 ),
   INP0( P1_RIGHT, 0x01A004, 0x08 ),
   INP0( P1_B1, 0x01A004, 0x10 ),
   INP0( P1_B2, 0x01A004, 0x20 ),

   INP0( P2_START, 0x01A00E, 0x80 ),
   INP0( P2_UP, 0x01A006, 0x01 ),
   INP0( P2_DOWN, 0x01A006, 0x02 ),
   INP0( P2_LEFT, 0x01A006, 0x04 ),
   INP0( P2_RIGHT, 0x01A006, 0x08 ),
   INP0( P2_B1, 0x01A006, 0x10 ),
   INP0( P2_B2, 0x01A006, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_earth_joker_0[] =
{
    DSW_TAITO_SCREEN_TEST_DEMO,
    DSW_TAITO_COINAGE_OLD_JAPAN,
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_earth_joker_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_UNKNOWN,             0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "1",                     0x00},
   { "2",                     0x30},
   { "3",                     0x20},
   { "4",                     0x10},
   { _("Romstar License"),       0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_earthjkr[] =
{
   { 0x01A000, 0xFF, dsw_data_earth_joker_0 },
   { 0x01A002, 0xEF, dsw_data_earth_joker_1 },
   { 0,        0,    NULL,      },
};



/******************************************************************************/


static struct ROM_INFO rom_mofflott[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
              "c17-09.bin",  0x05ee110f,   "c17-08.bin",  0xd0aacffd),
   {   "c17-03.bin", 0x00080000, 0x27047fc3, REGION_ROM1, 0x080000, LOAD_NORMAL, },
  { "c17-01.bin", 0x80000, 0xe9466d42, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "c17-02.bin", 0x80000, 0x8860a8db, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "c17-05.bin", 0x10000, 0x57ac4741, REGION_GFX2, 0x80000, LOAD_8_16 },
  { "c17-04.bin", 0x10000, 0xf4250410, REGION_GFX2, 0x80001, LOAD_8_16 },
  { "c17-07.bin", 0x10000, 0xcdb7bc2c, REGION_ROM2, 0, LOAD_NORMAL },
  { "c17-06.bin", 0x10000, 0x5c332125, REGION_SMP1, 0x00000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_maze_of_flott_0[] =
{
    DSW_TAITO_CAB_SCREEN_TEST_DEMO,
    DSW_REGION(3),
      DSW_TAITO_COINAGE_WORLD,
    DSW_DEFAULT_REGION,
      DSW_TAITO_COINAGE_OLD_JAPAN,
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_maze_of_flott_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("20k and every 50k"),     0x0C},
   { _("50k and every 100k"),    0x08},
   { _("100k only"),             0x04},
   { _("None"),                  0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x00},
   { "3",                     0x30},
   { "4",                     0x10},
   { "5",                     0x20},
   { _("Invulnerability"),       0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_mofflott[] =
{
   { 0x01A000, 0xFF, dsw_data_maze_of_flott_0 },
   { 0x01A002, 0xFF, dsw_data_maze_of_flott_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_maze_of_flott_0[] =
{
   { "Taito Japan (notice)",           0x01 },
   { "Taito Corporation",     0x02 },
   { "World", 3 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_mofflott[] =
{
   { 0x03FFFF, 0x01, romsw_data_maze_of_flott_0 },
   { 0,        0,    NULL },
};

static struct YM2151interface ym2151_interface =
{
  1,			// 1 chip
  4000000,		// 4 MHz
  { YM3012_VOL(160,OSD_PAN_LEFT,160,OSD_PAN_RIGHT) },
  { z80_irq_handler },
  { NULL }
};

static struct msm5205_adpcm_list maze_of_flott_adpcm[] =
{
  { 0x000000,0x000900-1 },
  { 0x000900,0x001980-1 },
  { 0x001A00,0x002700-1 },
  { 0x002700,0x008300-1 },
  { 0x008300,0x00AD00-1 },
  { 0x00AD00,0x00DD00-1 },
  { 0x00DD00,0x00F800-1 },
  { 0x00F800,0x00FF80-1 },
};

static struct MSM5205buffer_interface msm5205_interface =
{
   1,
   { 8000 },
   { 220 },
   { maze_of_flott_adpcm },
   { sizeof(maze_of_flott_adpcm) / sizeof(struct msm5205_adpcm_list) },
   { NULL },
   { 0 },
   { REGION_SOUND1 },
   MSM5205_MONO,
};

static struct SOUND_INFO sound_mofflott[] =
{
   { SOUND_YM2151J, &ym2151_interface,  },
   { SOUND_MSM5205_BUFF, &msm5205_interface, },
   { 0,             NULL,               },
};


/******************************************************************************/


static struct ROM_INFO rom_galmedes[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
             "gm-prg1.bin",  0x32a70753,  "gm-prg0.bin",  0xfae546a4),
   {   "gm-30.rom", 0x00080000, 0x4da2a407, REGION_ROM1, 0x080000, LOAD_NORMAL, },
  { "gm-scn.bin", 0x80000, 0x3bab0581, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "gm-obj.bin", 0x80000, 0x7a4a1315, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "gm-snd.bin", 0x10000, 0xd6f56c21, REGION_ROM2, 0, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_galmedes_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
   DSW_SERVICE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x00, 0x08),
   DSW_TEST_DSW(1,0x80,0x80),
   DSW_TAITO_COINAGE_OLD_JAPAN,
   DSW_TEST_DSW(1,0x80,0x00),
   DSW_TAITO_COINAGE_WORLD,
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_galmedes_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("Every 100k"),            0x08},
   { _("100k and every 200k"),   0x0C},
   { _("150k and every 200k"),   0x04},
   { _("Every 200k"),            0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "1",                     0x20},
   { "2",                     0x10},
   { "3",                     0x30},
   { "4",                     0x00},
   { MSG_UNKNOWN,             0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_COINAGE,             0x80, 0x02 },
   { _("Japanese"),              0x80},
   { _("World"),                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_galmedes[] =
{
   { 0x01A000, 0xF7, dsw_data_galmedes_0 },
   { 0x01A002, 0x7F, dsw_data_galmedes_1 },
   { 0,        0,    NULL,      },
};


/******************************************************************************/


static struct ROM_INFO rom_eto[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
                "eto-1.23",  0x44286597,      "eto-0.8",  0x57b79370),
   {     "eto-2.30", 0x00080000, 0x12f46fb5, REGION_ROM1, 0x080000, LOAD_NORMAL, },
  { "eto-4.3", 0x80000, 0xa8768939, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "eto-3.6", 0x80000, 0xdd247397, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "eto-5.27", 0x10000, 0xb3689da0, REGION_ROM2, 0, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_eto_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_UNKNOWN,             0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_eto[] =
{
   { 0x01A000, 0xFF, dsw_data_earth_joker_0},
   { 0x01A002, 0xFF, dsw_data_eto_1 },
   { 0,        0,    NULL,      },
};



/******************************************************************************/

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_OBJECT;
static UINT8 *RAM_INPUT;

static int romset;

static void Maze_of_Flott_M5205_W(UINT16 offset, UINT8 data);

/*

Supported romsets:

0 - Earth Joker
1 - Maze of Flott
2 - Galmedes

Problems:

- Maze of Flott MSM5205 is missing
- Some parts use background layer line-line scroll

*/

static void MemoryMap_EarthJoker(void)
{
   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x200000, 0x200007, tc0110pcr_rw, NULL);			// COLOUR PORTS
   AddReadWord(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x3E0000, 0x3E0003, tc0140syt_read_main_68k, NULL); 	// SOUND
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x103FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteBW(0x3A0000, 0x3A0001, NULL, &RAM[0x1b010]);		// SPRITE CTRL
   AddWriteByte(0x400000, 0x40000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x103FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0xC06000, 0xC06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x200000, 0x200007, tc0110pcr_ww, NULL);		// COLOUR PORTS
   AddWriteWord(0xC20000, 0xC2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x400000, 0x40000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x3E0000, 0x3E0003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);
}

static void MemoryMap_Eto(void)
{
   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x200000, 0x203FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xC00000, 0xC007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x300000, 0x30000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT (mirror)
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x200000, 0x203FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xC00000, 0xC007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x100000, 0x100007, tc0110pcr_rw, NULL);			// COLOUR PORTS
   AddReadWord(0x300000, 0x30000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT (mirror)
   AddReadWord(0x4E0000, 0x4E0003, tc0140syt_read_main_68k, NULL); 	// SOUND
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x200000, 0x203FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xC00000, 0xC007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0xD06000, 0xD06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM (mirror)
   AddWriteByte(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x4A0000, 0x4A0001, NULL, RAM+0x01B010);		// SPRITE CTRL
   AddWriteByte(0x300000, 0x30000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x203FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xC00000, 0xC007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0xD06000, 0xD06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM (mirror)
   AddWriteWord(0xD00000, 0xD0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x100000, 0x100007, tc0110pcr_ww, NULL);		// COLOUR PORTS
   AddWriteWord(0xD20000, 0xD2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x4A0000, 0x4A0001, NULL, RAM+0x01B010);		// SPRITE CTRL
   AddWriteWord(0x300000, 0x30000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x4E0000, 0x4E0003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);
}

static void AddEarthJoker68k(void)
{
   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.RAM	= RAM_OBJECT;
   if (romset==3) {
     tc0002obj.ofs_x	= 0;
     tc0002obj.ofs_y	= -8;
   }
   else {
     tc0002obj.ofs_x	= -8;
     tc0002obj.ofs_y	= 0;
   }

   // Init tc0100scn emulation
   // ------------------------

   setup_asuka_layers(RAM_VIDEO,RAM_SCROLL,GFX_FG0,17,8,&RAM[0x1B010]);

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   if (romset==3)
     MemoryMap_Eto();
   else
     MemoryMap_EarthJoker();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_earthjkr(void)
{
   romset=0;

   RAMSize=0x38000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   GFX_FG0 = RAM+0x20000;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   memcpy(Z80ROM,load_region[REGION_CPU2],0x10000);

   AddTaitoYM2151(0x01AF, 0x0143, 0x10000, NULL, NULL);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B000;
   RAM_OBJECT = RAM+0x18000;
   RAM_INPUT  = RAM+0x1A000;

   tc0110pcr_init(RAM+0x1C000, 1);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x8000);

   // Speed Hack
   // ----------

   WriteLong68k(&ROM[0x004D8],0x13FC0000);
   WriteLong68k(&ROM[0x004DC],0x00AA0000);

   // Fix ROM Checksum
   // ----------------

   WriteLong68k(&ROM[0x00B36],0x4E714E71);

   AddEarthJoker68k();
}

static void load_mofflott(void)
{

   romset=1;

   RAMSize=0x38000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   memcpy(Z80ROM,load_region[REGION_CPU2],0x10000);

   AddTaitoYM2151(0x01C0, 0x01AB, 0x10000, (UINT8 *) Maze_of_Flott_M5205_W, NULL);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B000;
   RAM_OBJECT = RAM+0x18000;
   RAM_INPUT  = RAM+0x1A000;

   tc0110pcr_init(RAM+0x1C000, 1);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x8000);

   GFX_FG0 = RAM+0x20000;

   // Speed Hack
   // ----------

   WriteLong68k(&ROM[0x005CA],0x13FC0000);
   WriteLong68k(&ROM[0x005CE],0x00AA0000);

   WriteLong68k(&ROM[0x0368C],0x13FC0000);
   WriteLong68k(&ROM[0x03690],0x00AA0000);

   // Fix ROM Checksum
   // ----------------

   WriteLong68k(&ROM[0x030F6],0x4E714E71);

   // Fix Bad Writes
   // --------------

   WriteLong68k(&ROM[0x14C6A],0x4E714E71);
   WriteLong68k(&ROM[0x14C7A],0x4E714E71);

   AddEarthJoker68k();
}

static void load_galmedes(void)
{
   romset=2;

   RAMSize=0x38000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   memcpy(Z80ROM,load_region[REGION_CPU2],0x10000);

   AddTaitoYM2151(0x01AF, 0x0143, 0x10000, NULL, NULL);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B000;
   RAM_OBJECT = RAM+0x18000;
   RAM_INPUT  = RAM+0x1A000;

   tc0110pcr_init(RAM+0x1C000, 1);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x8000);

   GFX_FG0 = RAM+0x20000;

   // Speed Hack
   // ----------

   WriteLong68k(&ROM[0x800A4],0x13FC0000);
   WriteLong68k(&ROM[0x800A8],0x00AA0000);

   AddEarthJoker68k();
}

static void load_eto(void)
{
   romset=3;

   RAMSize=0x38000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   memcpy(Z80ROM,load_region[REGION_CPU2],0x10000);

   AddTaitoYM2151(0x01CF, 0x01AB, 0x10000, NULL, NULL);		// 100% not sure

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B000;
   RAM_OBJECT = RAM+0x18000;
   RAM_INPUT  = RAM+0x1A000;

   tc0110pcr_init(RAM+0x1C000, 1);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x8000);

   GFX_FG0 = RAM+0x20000;

   // Speed Hack
   // ----------

   // ...

   AddEarthJoker68k();
}

static void execute_mofflott(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);

   Taito2151_Frame();			// Z80 and YM2151
}

/*-------[Maze of Flott MSM5205 Port]-------*/

static void Maze_of_Flott_M5205_W(UINT16 offset, UINT8 data)
{
  int ta;

  if((offset&15)==0){

    switch(data){
      case 0x00: ta=0; break;
      case 0x09: ta=1; break;
      case 0x1A: ta=2; break;
      case 0x27: ta=3; break;
      case 0x83: ta=4; break;
      case 0xAD: ta=5; break;
      case 0xDD: ta=6; break;
      case 0xF8: ta=7; break;
      default:  ta=-1; break;
    }

    if(ta>=0){
      MSM5205buffer_request( 0, ta );
    }
  }
}
static struct VIDEO_INFO video_eto =
{
   DrawAsuka,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL|VIDEO_ROTATABLE,
   asuka_gfx
};
static struct VIDEO_INFO video_mofflott =
{
   DrawAsuka,
   320,
   240,
   32,
   VIDEO_ROTATE_270|VIDEO_ROTATABLE,
   asuka_gfx
};
static struct DIR_INFO dir_eto[] =
{
   { "eto", },
   { NULL, },
};
GAME( eto, "Kokontouzai Eto Monogatari", VISCO, 1994, GAME_PUZZLE,
	.input = input_mofflott,
	.dsw = dsw_eto,
	.video = &video_eto,
	.exec = execute_mofflott,
	.sound = taito_ym2151_sound,
);
static struct DIR_INFO dir_galmedes[] =
{
   { "galmedes", },
   { NULL, },
};
GAME( galmedes, "Galmedes", VISCO, 1992, GAME_SHOOT,
	.input = input_mofflott,
	.dsw = dsw_galmedes,
	.video = &video_mofflott,
	.exec = execute_mofflott,
	.long_name_jpn = "ガルメデス",
	.sound = taito_ym2151_sound,
);
static struct DIR_INFO dir_earthjkr[] =
{
   { "earth_joker", },
   { "earthjkr", },
   { NULL, },
};
GAME( earthjkr, "Earth Joker", VISCO, 1993, GAME_SHOOT,
	.input = input_mofflott,
	.dsw = dsw_earthjkr,
	.video = &video_mofflott,
	.exec = execute_mofflott,
	.long_name_jpn = "アースジョーカー",
	.sound = taito_ym2151_sound,
);
static struct DIR_INFO dir_mofflott[] =
{
   { "maze_of_flott", },
   { "mofflott", },
   { NULL, },
};
GME( mofflott, "Maze of Flott", TAITO, 1989, GAME_RACE,
	.romsw = romsw_mofflott,
	.long_name_jpn = "メイズオブフロット",
	.board = "C17",
);

