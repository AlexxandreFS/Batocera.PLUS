#define DRV_DEF_SOUND taito_ym2151_sound
/******************************************************************************/
/*                                                                            */
/*                 ASUKA & ASUKA (C) 1988 TAITO CORPORATION                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc002obj.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "def_dsw.h"

static struct ROM_INFO rom_asuka[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "asuka_13.rom",  0x855efb3e, "asuka_12.rom",  0x271eeee9),
  { "asuka_03.rom", 0x80000, 0xd3a59b10, REGION_ROM1, 0x80000, LOAD_NORMAL },
  { "asuka_01.rom", 0x80000, 0x89f32c94, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "asuka_02.rom", 0x80000, 0xf5018cd3, REGION_GFX2, 0x00000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  0x80000,  0x10000,
            "asuka_07.rom",  0xc113acc8, "asuka_06.rom",  0xf517e64d),
  { "asuka_11.rom", 0x10000, 0xc378b508, REGION_ROM2, 0, LOAD_NORMAL },
  { "asuka_10.rom", 0x10000, 0x387aaf40, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_asuka[] =
{
   INP0( TILT, 0x01A00E, 0x01 ),
   INP0( SERVICE, 0x01A00E, 0x02 ),
   INP0( COIN1, 0x01A00E, 0x04 ),
   INP0( COIN2, 0x01A00E, 0x08 ),

   INP0( P1_START, 0x01A00E, 0x40 ),
   INP0( P2_START, 0x01A00E, 0x80 ),

   INP0( P1_UP, 0x01A004, 0x01 ),
   INP0( P1_DOWN, 0x01A004, 0x02 ),
   INP0( P1_LEFT, 0x01A004, 0x04 ),
   INP0( P1_RIGHT, 0x01A004, 0x08 ),
   INP0( P1_B1, 0x01A004, 0x10 ),
   INP0( P1_B2, 0x01A004, 0x20 ),

   INP0( P2_UP, 0x01A006, 0x01 ),
   INP0( P2_DOWN, 0x01A006, 0x02 ),
   INP0( P2_LEFT, 0x01A006, 0x04 ),
   INP0( P2_RIGHT, 0x01A006, 0x08 ),
   INP0( P2_B1, 0x01A006, 0x10 ),
   INP0( P2_B2, 0x01A006, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_asuka_and_asuka_0[] =
{
    DSW_TAITO_SCREEN_TEST_DEMO,
    DSW_TAITO_COINAGE_OLD_JAPAN,
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_asuka_and_asuka_1[] =
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
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "1",                     0x10},
   { "4",                     0x00},
   { MSG_CONTINUE_PLAY,       0xC0, 0x04 },
   { _("Up to Level 2"),         0xC0},
   { _("Up to Level 3"),         0x80},
   { MSG_ON,                  0x40},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_asuka[] =
{
   { 0x01A000, 0xFF, dsw_data_asuka_and_asuka_0 },
   { 0x01A002, 0xFF, dsw_data_asuka_and_asuka_1 },
   { 0,        0,    NULL,      },
};

static GfxLayout charlayout =
{
	8,8,
	RGN_FRAC(1,1),
	4,
	{ 0, 1, 2, 3 },
	{ 2*4, 3*4, 0*4, 1*4, 6*4, 7*4, 4*4, 5*4 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8
};

static GfxLayout tilelayout =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0, 1, 2, 3 },
	{ 2*4, 3*4, 0*4, 1*4, 6*4, 7*4, 4*4, 5*4,
	  10*4, 11*4, 8*4, 9*4, 14*4, 15*4, 12*4, 13*4 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64,
	  8*64, 9*64, 10*64, 11*64, 12*64, 13*64, 14*64, 15*64 },
	128*8
};

struct GFX_LIST asuka_gfx[] =
{
	{ REGION_GFX1, &charlayout }, // 256 color banks
	{ REGION_GFX2, &tilelayout }, // 256 color banks
	{ 0, NULL } /* end of array */
};

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *sctrl;

void setup_asuka_layers(UINT8 *rv, UINT8 *rs, UINT8 *gf, int s_x, int s_y,UINT8 *ctrl)
{
    RAM_VIDEO = rv;
    RAM_SCROLL = rs;
    GFX_FG0 = gf;
    VIDEO_INFO *v = current_game->video;
    sctrl = ctrl;

   // Init tc0100scn emulation
   // ------------------------

   tc0002obj.MASK = NULL;
   tc0100scn[0].layer[0].RAM	= RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].SCR	= RAM_SCROLL+0;
   tc0100scn[0].layer[1].type	=
   tc0100scn[0].layer[0].type	= 0;
   tc0002obj.bmp_x =
   tc0100scn[0].layer[1].bmp_x	=
   tc0100scn[0].layer[0].bmp_x	= v->border_size;
   tc0100scn[0].layer[1].bmp_y	=
   tc0002obj.bmp_y =
   tc0100scn[0].layer[0].bmp_y	= v->border_size;
   tc0002obj.bmp_w =
   tc0100scn[0].layer[1].bmp_w	=
   tc0100scn[0].layer[0].bmp_w	= v->screen_x;
   tc0002obj.bmp_h =
   tc0100scn[0].layer[1].bmp_h	=
   tc0100scn[0].layer[0].bmp_h	= v->screen_y;
   tc0100scn[0].layer[1].scr_x	=
   tc0100scn[0].layer[0].scr_x	= s_x;
   tc0100scn[0].layer[1].scr_y	=
   tc0100scn[0].layer[0].scr_y	= s_y;

   tc0100scn[0].layer[1].RAM	= RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].SCR	= RAM_SCROLL+2;

   if (GFX_FG0) {
       tc0100scn[0].layer[2].RAM	= RAM_VIDEO+0x4000;
       tc0100scn[0].layer[2].GFX	= GFX_FG0;
       tc0100scn[0].layer[2].SCR	= RAM_SCROLL+4;
       tc0100scn[0].layer[2].type	= 1;
       tc0100scn[0].layer[2].bmp_x	= v->border_size;
       tc0100scn[0].layer[2].bmp_y	= v->border_size;
       tc0100scn[0].layer[2].bmp_w	= v->screen_x;
       tc0100scn[0].layer[2].bmp_h	= v->screen_y;
       tc0100scn[0].layer[2].scr_x	= s_x;
       tc0100scn[0].layer[2].scr_y	= s_y;
   }

   tc0100scn[0].RAM	= RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;
   init_tc0100scn(0);
}

static UINT8 *RAM_OBJECT;
static UINT8 *RAM_INPUT;

static void load_asuka(void)
{
   RAMSize=0x38000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   /*-----[Sound Setup]-----*/

   AddTaitoYM2151(0x01C0, 0x01AB, 0x10000, NULL, NULL);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B000;
   RAM_OBJECT = RAM+0x18000;
   RAM_INPUT  = RAM+0x1A000;

   tc0110pcr_init(RAM+0x1C000, 1);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x8000);

   WriteWord68k(&ROM[0x0137E],0x4EF9);
   WriteLong68k(&ROM[0x01380],0x00000300);

   WriteLong68k(&ROM[0x00300],0x13FC0000);
   WriteLong68k(&ROM[0x00304],0x00AA0000);
   WriteWord68k(&ROM[0x00308],0x6100-10);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   //reset_tc0220ioc();

    setup_asuka_layers(RAM_VIDEO,RAM_SCROLL,NULL,16,16,&RAM[0x20010]);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.RAM	= RAM_OBJECT;
   tc0002obj.ofs_x	= -16;
   tc0002obj.ofs_y	= 0;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x3E0000, 0x3E0003, tc0140syt_read_main_68k, NULL); 	// SOUND
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x103FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x200000, 0x200007, tc0110pcr_rw, NULL);			// COLOUR PORTS
   AddReadWord(0x200000, 0x200FFF, NULL, RAM+0x01C000);			// COLOUR DIRECT?
   AddReadWord(0x400000, 0x40000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x103FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteBW(0x3A0000, 0x3A0001, NULL, RAM+0x020010);		// sprite ctrl
   AddWriteByte(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x3E0000, 0x3E0003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteByte(0x400000, 0x40000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x103FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xD00000, 0xD007FF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x200000, 0x200007, tc0110pcr_ww, NULL);		// COLOUR PORTS
   AddWriteWord(0x200000, 0x200FFF, NULL, RAM+0x01C000);		// COLOUR DIRECT?
   AddWriteWord(0xC20000, 0xC2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x400000, 0x40000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_asuka(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);

   Taito2151_Frame();			// Z80 and YM2151
}

void DrawAsuka(void)
{
   ClearPaletteMap();

   if (!tc0002obj.MASK) {
     tc0100scn[0].layer[0].MASK	= gfx_solid[0];
     tc0100scn[0].layer[1].MASK	= gfx_solid[0];
     tc0100scn[0].layer[0].GFX	= gfx[0];
     tc0100scn[0].layer[1].GFX	= gfx[0];
     tc0002obj.MASK	= gfx_solid[1];
     tc0002obj.GFX	= gfx[1];
     tc0100scn[0].layer[0].tile_mask=
     tc0100scn[0].layer[1].tile_mask=
	 get_mask(get_region_size(REGION_GFX1)/64);
     tc0002obj.tile_mask	= get_mask(get_region_size(REGION_GFX2)/256);
   }

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.ctrl = ReadWord(sctrl);

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1+OBJECT
   // ----------

   if((tc0002obj.ctrl & 0x2000)==0){
      render_tc0100scn_layer_mapped(0,1,1);
      render_tc0002obj_mapped();
   }
   else{
      render_tc0002obj_mapped();
      render_tc0100scn_layer_mapped(0,1,1);
   }

   if (GFX_FG0) {
       // FG0
       // ---

       render_tc0100scn_layer_mapped(0,2,1);
   }
}



struct VIDEO_INFO video_asuka =
{
   DrawAsuka,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   asuka_gfx
};
static struct DIR_INFO dir_asuka[] =
{
   { "asuka_and_asuka", },
   { "asuka", },
   { NULL, },
};
GME( asuka, "Asuka and Asuka", TAITO, 1988, GAME_SHOOT,
	.long_name_jpn = "˜ÚíπÅï˜Úíπ",
);

