#define DRV_DEF_EXEC execute_kurikint
#define DRV_DEF_SOUND taito_ym2203_sound
#define DRV_DEF_VIDEO &video_kurikint
/******************************************************************************/
/*                                                                            */
/*              TAITO L-SYSTEM (C) 1988-1990 TAITO CORPORATION                */
/*                                                                            */
/*              Z80+YM2203 or Z80+Z80+YM2610 or Z80+Z80+YM2203                */
/*                                                                            */
/******************************************************************************/
// Started to cleanup the code, not sure I'll finish this... !

#include "gameinc.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "savegame.h"
#include "sasound.h"		// sample support routines
#include "emumain.h" // set_reset_function
#include "blit.h" // clear_game_screen

static struct ROMSW_DATA romsw_data_fighting_hawk_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { "Taito Corporation",     0x04 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_fhawk[] =
{
   { 0x007FFF, 0x01, romsw_data_fighting_hawk_0 },
   { 0,        0,    NULL },
};

/************************
   AMERICAN HORSESHOES
 ************************/


static struct ROM_INFO rom_horshoes[] =
{
   {   "c47.01", 0x00020000, 0x031c73d8, 0, 0, 0, },
   {   "c47.02", 0x00020000, 0x35f96526, 0, 0, 0, },
   {   "c47.03", 0x00020000, 0x37e15b20, 0, 0, 0, },
   {   "c47.04", 0x00020000, 0xaeac7121, 0, 0, 0, },
   {   "c47.05", 0x00020000, 0xb2a3dafe, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_horshoes[] =
{
   INP0( COIN1, 0x02C200, 0x02 ),
   INP0( COIN2, 0x02C201, 0x02 ),
   INP0( TILT, 0x02C201, 0x01 ),
   INP0( SERVICE, 0x02C200, 0x01 ),

   INP1( P1_UP, 0x02C208, 0xFF ),
   INP1( P1_DOWN, 0x02C209, 0xFF ),
   INP1( P1_LEFT, 0x02C20A, 0xFF ),
   INP1( P1_RIGHT, 0x02C20B, 0xFF ),
   INP0( P1_B1, 0x02C200, 0x80 ),
   INP0( P1_B2, 0x02C201, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_american_horseshoes_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_american_horseshoes_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Time"),                  0x04, 0x02 },
   { _("30 seconds"),            0x04},
   { _("20 seconds"),            0x00},
   { MSG_DSWA_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { _("Innings"),               0x10, 0x02 },
   { _("3 per Credit"),          0x10},
   { _("9 per Credit"),          0x00},
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

static struct DSW_INFO dsw_horshoes[] =
{
   { 0x02C202, 0xFF, dsw_data_american_horseshoes_0 },
   { 0x02C203, 0xFF, dsw_data_american_horseshoes_1 },
   { 0,        0,    NULL,      },
};

#define O 8*8*2
#define O2 2*O
static gfx_layout sp1_layout =
{
        16, 16,
        RGN_FRAC(1,2),
        4,
        { RGN_FRAC(1,2)+0, RGN_FRAC(1,2)+4, 0, 4 },
        { 3, 2, 1, 0, 8+3, 8+2, 8+1, 8+0, O+3, O+2, O+1, O+0, O+8+3, O+8+2, O+8+1, O+8+0 },
        { 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16, O2+0*16, O2+1*16, O2+2*16, O2+3*16, O2+4*16, O2+5*16, O2+6*16, O2+7*16 },
        8*8*2*4
};
#undef O
#undef O2

static GFX_LAYOUT bg2_layout =
{
	8, 8,
	RGN_FRAC(1,1),
	4,
	{ 8, 12, 0, 4 },
	{ 3, 2, 1, 0, 19, 18, 17, 16 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	8*8*4
};

#define O 8*8*4
#define O2 2*O
static GFX_LAYOUT sp2_layout =
{
	16, 16,
	RGN_FRAC(1,1),
	4,
	{ 8, 12, 0, 4 },
	{ 3, 2, 1, 0, 19, 18, 17, 16, O+3, O+2, O+1, O+0, O+19, O+18, O+17, O+16 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32, O2+0*32, O2+1*32, O2+2*32, O2+3*32, O2+4*32, O2+5*32, O2+6*32, O2+7*32 },
	8*8*4*4
};
#undef O
#undef O2

static GFX_LIST gfxdecodeinfo2[] =
{
	{ REGION_GFX1, &bg2_layout, },
	{ REGION_GFX1, &sp2_layout, },
	{ 0,           NULL}, // Ram-based
	{ -1 }
};


static gfx_layout bg1_layout =
{
        8, 8,
        RGN_FRAC(1,2),
        4,
        { RGN_FRAC(1,2)+0, RGN_FRAC(1,2)+4, 0, 4 },
        { 3, 2, 1, 0, 8+3, 8+2, 8+1, 8+0 },
        { 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
        8*8*2
};

static GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &bg1_layout, },
	{ REGION_GFX1, &sp1_layout, },
	{ 0,           NULL}, // Ram-based
	{ -1 }
};



#define LSYS_INT0	1		// Usually does nothing
#define LSYS_INT1	2		// Usually main int (frame start?)
#define LSYS_INT2	4		// Usually second main int (frame end?)

static int romset;

static UINT8 *RAM2;
static UINT8 *ROM2;
static UINT8 *RAM_INP;

static int spr_mask;
static int tile_mask;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;
static UINT8 VectorData[4];

static void TrackBall(void)
{
   int px,py;

   if(*MouseB&1) RAM_INP[0] &= ~0x80;
   if(*MouseB&2) RAM_INP[1] &= ~0x80;

   GetMouseMickeys(&px,&py);
   WriteWord(&RAM_INP[0x04], py<<3);
   WriteWord(&RAM_INP[0x06], px<<3);

}

static void execute_kurikint(void)
{
   if(romset==1)
      TrackBall();

   cpu_execute_cycles(CPU_Z80_1, 16);	// Main Z80 8MHz (60fps)
   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(8,60));	// Main Z80 8MHz (60fps)
   if(romset==9)
   {
       if(VectorData[3] & LSYS_INT2){
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(1,60));
       }
   }
   else
   {
       if(VectorData[3] & LSYS_INT2){
	   cpu_interrupt(CPU_Z80_1, VectorData[2]);
	   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(8,60));
       }
   }
   if(VectorData[3] & LSYS_INT1){
       cpu_interrupt(CPU_Z80_1, VectorData[1]);
   }
   if(VectorData[3] & LSYS_INT0){
       cpu_interrupt(CPU_Z80_1, VectorData[0]);
   }

   if(romset==0){
       cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));	// Sub Z80 8MHz (60fps)
   }

   if(romset==3){
       cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));	// Sub Z80 8MHz (60fps)
       if(z80pc==0x10D) cpu_interrupt(CPU_Z80_2, 0x38);
   }

   if(romset==4){
       cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));	// Sub Z80 8MHz (60fps)
       /*#ifdef RAINE_DEBUG
	 print_debug("Z80PC_SUB:%04x\n",z80pc);
#endif*/
       if(z80pc==0x025) cpu_interrupt(CPU_Z80_2, 0x38);
   }

   if(romset==5){
       cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));	// Sub Z80 8MHz (60fps)
       /*#ifdef RAINE_DEBUG
	 print_debug("Z80PC_SUB:%04x\n",z80pc);
#endif*/
       if(z80pc==0x11B) cpu_interrupt(CPU_Z80_2, 0x38);
   }

   if(romset==0)
       Taito2610_Frame();		// Z80 and YM2610

   if((romset==3)||(romset==4))
       Taito2203_Frame();		// Z80 and YM2203
}


/***************************
   CHAMPION WRESTLER WORLD
 ***************************/


static struct ROM_INFO rom_champwr[] =
{
  { "c01-13.rom", 0x20000, 0x7ef47525, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "c01-13.rom", 0x20000, 0x7ef47525, REGION_ROM1, 0x06000, LOAD_NORMAL },
  { "c01-04.rom", 0x20000, 0x358bd076, REGION_ROM1, 0x26000, LOAD_NORMAL },
  { "c01-08.rom", 0x10000, 0x810efff8, REGION_ROM2, 0, LOAD_NORMAL },
  { "c01-07.rom", 0x20000, 0x5117c98f, REGION_CPU3, 0x00000, LOAD_NORMAL },
  { "c01-07.rom", 0x20000, 0x5117c98f, REGION_CPU3, 0x08000, LOAD_NORMAL },
  { "c01-01.rom", 0x80000, 0xf302e6e9, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "c01-02.rom", 0x80000, 0x1e0476c4, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "c01-03.rom", 0x80000, 0x2a142dbc, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "c01-05.rom", 0x20000, 0x22efad4a, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROMSW_INFO romsw_champwr[] =
{
   { 0x1025fff, 0x03, romsw_data_fighting_hawk_0 },
   { 0,        0,    NULL },
};

static struct INPUT_INFO input_champwr[] =
{
   INP0( COIN1, 0x02C206, 0x02 ),
   INP0( COIN2, 0x02C206, 0x01 ),
   INP0( TILT, 0x02C204, 0x40 ),
   INP0( SERVICE, 0x02C204, 0x80 ),

   INP0( P1_START, 0x02C204, 0x04 ),
   INP0( P1_UP, 0x02C20E, 0x80 ),
   INP0( P1_DOWN, 0x02C20E, 0x40 ),
   INP0( P1_LEFT, 0x02C20E, 0x20 ),
   INP0( P1_RIGHT, 0x02C20E, 0x10 ),
   INP0( P1_B1, 0x02C204, 0x02 ),
   INP0( P1_B2, 0x02C204, 0x01 ),

   INP0( P2_START, 0x02C204, 0x08 ),
   INP0( P2_UP, 0x02C20E, 0x08 ),
   INP0( P2_DOWN, 0x02C20E, 0x04 ),
   INP0( P2_LEFT, 0x02C20E, 0x02 ),
   INP0( P2_RIGHT, 0x02C20E, 0x01 ),
   INP0( P2_B1, 0x02C204, 0x20 ),
   INP0( P2_B2, 0x02C204, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_champion_wrestler_0[] =
{
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
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_champion_wrestler_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Time"),                  0x0C, 0x04 },
   { _("3 Minutes"),             0x0C},
   { _("2 Minutes"),             0x08},
   { _("4 Minutes"),             0x04},
   { _("5 Minutes"),             0x00},
   { _("1 Minute Lenght"),       0x30, 0x04 },
   { _("50 seconds"),            0x30},
   { _("60 seconds"),            0x20},
   { _("40 seconds"),            0x10},
   { _("30 seconds"),            0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_champwr[] =
{
   { 0x02C200, 0xFF, dsw_data_champion_wrestler_0 },
   { 0x02C202, 0xFF, dsw_data_champion_wrestler_1 },
   { 0,        0,    NULL,      },
};


/************************
   CHAMPION WRESTLER US
 ************************/


static struct ROM_INFO rom_champwru[] =
{
  { "c01-12.rom", 0x20000, 0x09f345b3, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "c01-12.rom", 0x20000, 0x09f345b3, REGION_ROM1, 0x06000, LOAD_NORMAL },
  { "c01-04.rom", 0x20000, 0x358bd076, REGION_ROM1, 0x26000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_champion_wrestler_us_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_COIN_SLOTS,          0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { _("Continue cost"),         0xC0, 0x04 },
   { _("Same as play"),          0xC0},
   { _("1 extra coin"),          0x80},
   { _("2 extra coins"),         0x40},
   { _("3 extra coins"),         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_champwru[] =
{
   { 0x02C200, 0xFF, dsw_data_champion_wrestler_us_0 },
   { 0x02C202, 0xFF, dsw_data_champion_wrestler_1 },
   { 0,        0,    NULL,      },
};


/***************************
   CHAMPION WRESTLER JAPAN
 ***************************/


static struct ROM_INFO rom_champwrj[] =
{
  { "c01-06.bin", 0x20000, 0x90fa1409, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "c01-06.bin", 0x20000, 0x90fa1409, REGION_ROM1, 0x06000, LOAD_NORMAL },
  { "c01-04.rom", 0x20000, 0x358bd076, REGION_ROM1, 0x26000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_champion_wrestler_jp_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_champwrj[] =
{
   { 0x02C200, 0xFF, dsw_data_champion_wrestler_jp_0 },
   { 0x02C202, 0xFF, dsw_data_champion_wrestler_1 },
   { 0,        0,    NULL,      },
};


/**********
   CACHAT
 **********/


static struct ROM_INFO rom_cachat[] =
{
   {         "cac6", 0x00020000, 0x8105cf5f, 0, 0, 0, },
   {         "cac7", 0x00020000, 0x7fb71578, 0, 0, 0, },
   {         "cac8", 0x00020000, 0xd2a63799, 0, 0, 0, },
   {         "cac9", 0x00020000, 0xbc462914, 0, 0, 0, },
   {        "cac10", 0x00020000, 0xecc64b31, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_cachat[] =
{
   INP0( COIN1, 0x02C200, 0x04 ),
   INP0( COIN2, 0x02C200, 0x08 ),
   INP0( TILT, 0x02C200, 0x02 ),
   INP0( SERVICE, 0x02C200, 0x01 ),

   INP0( P1_START, 0x02C200, 0x10 ),
   INP0( P1_UP, 0x02C202, 0x01 ),
   INP0( P1_DOWN, 0x02C202, 0x02 ),
   INP0( P1_LEFT, 0x02C202, 0x04 ),
   INP0( P1_RIGHT, 0x02C202, 0x08 ),
   INP0( P1_B1, 0x02C200, 0x40 ),
   INP0( P1_B2, 0x02C200, 0x80 ),

   INP0( P2_START, 0x02C200, 0x20 ),
   INP0( P2_UP, 0x02C202, 0x10 ),
   INP0( P2_DOWN, 0x02C202, 0x20 ),
   INP0( P2_LEFT, 0x02C202, 0x40 ),
   INP0( P2_RIGHT, 0x02C202, 0x80 ),
   INP0( P2_B1, 0x02C204, 0x01 ),
   INP0( P2_B2, 0x02C204, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_cachat_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x00, 0x02),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_3COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_cachat_1[] =
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
   { MSG_DSWB_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_cachat[] =
{
   { 0x02C210, 0xFD, dsw_data_cachat_0 },
   { 0x02C212, 0xFF, dsw_data_cachat_1 },
   { 0,        0,    NULL,      },
};


/*****************
   FIGHTING HAWK
 *****************/


static struct ROM_INFO rom_fhawk[] =
{
   {   "b70-01.bin", 0x00080000, 0xfcdf67e2, 0, 0, 0, },
   {   "b70-02.bin", 0x00080000, 0x35f7172e, 0, 0, 0, },
   {   "b70-03.bin", 0x00080000, 0x42d5a9b8, 0, 0, 0, },
   {   "b70-07.bin", 0x00020000, 0x939114af, 0, 0, 0, },
   {   "b70-08.bin", 0x00020000, 0x4d795f48, 0, 0, 0, },
   {   "b70-09.bin", 0x00010000, 0x85cccaa2, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_fhawk[] =
{
   INP0( COIN1, 0x02C20E, 0x04 ),
   INP0( COIN2, 0x02C20E, 0x08 ),
   INP0( TILT, 0x02C20E, 0x01 ),
   INP0( SERVICE, 0x02C20E, 0x02 ),

   INP0( P1_START, 0x02C20E, 0x40 ),
   INP0( P1_UP, 0x02C204, 0x01 ),
   INP0( P1_DOWN, 0x02C204, 0x02 ),
   INP0( P1_LEFT, 0x02C204, 0x04 ),
   INP0( P1_RIGHT, 0x02C204, 0x08 ),
   INP0( P1_B1, 0x02C204, 0x10 ),
   INP0( P1_B2, 0x02C204, 0x20 ),

   INP0( P2_START, 0x02C20E, 0x80 ),
   INP0( P2_UP, 0x02C206, 0x01 ),
   INP0( P2_DOWN, 0x02C206, 0x02 ),
   INP0( P2_LEFT, 0x02C206, 0x04 ),
   INP0( P2_RIGHT, 0x02C206, 0x08 ),
   INP0( P2_B1, 0x02C206, 0x10 ),
   INP0( P2_B2, 0x02C206, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_fighting_hawk_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_fighting_hawk_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "6",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_fhawk[] =
{
   { 0x02C200, 0xFE, dsw_data_fighting_hawk_0 },
   { 0x02C202, 0xFF, dsw_data_fighting_hawk_1 },
   { 0,        0,    NULL,      },
};


/***************
   KURI KINTON
 ***************/


static struct ROM_INFO rom_kurikina[] =
{
   {   "kk_ic2.rom", 0x00020000, 0x908603f2, 0, 0, 0, },
   {  "b42-07.22", 0x00010000, 0x0f2719c0, 0, 0, 0, },
   {   "kk_ic6.rom", 0x00020000, 0xa4a957b1, 0, 0, 0, },
   {  "kk_1-1l.rom", 0x00020000, 0xdf1d4fcd, 0, 0, 0, },
   {  "kk_2-2l.rom", 0x00020000, 0xfca7f647, 0, 0, 0, },
   {  "kk_3-1h.rom", 0x00020000, 0x71af848e, 0, 0, 0, },
   {  "kk_4-2h.rom", 0x00020000, 0xcebb5bac, 0, 0, 0, },
   {  "kk_5-3l.rom", 0x00020000, 0xd080fde1, 0, 0, 0, },
   {  "kk_6-3h.rom", 0x00020000, 0x322e3752, 0, 0, 0, },
   {  "kk_7-4l.rom", 0x00020000, 0xf5bf6829, 0, 0, 0, },
   {  "kk_8-4h.rom", 0x00020000, 0x117bde99, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_kurikint[] =
{
   INP1( COIN1, 0x02C20E, 0x04 ),
   INP1( COIN2, 0x02C20E, 0x08 ),
   INP0( TILT, 0x02C20E, 0x01 ),
   INP0( SERVICE, 0x02C20E, 0x02 ),

   INP0( P1_START, 0x02C20E, 0x40 ),
   INP0( P1_UP, 0x02C204, 0x01 ),
   INP0( P1_DOWN, 0x02C204, 0x02 ),
   INP0( P1_LEFT, 0x02C204, 0x04 ),
   INP0( P1_RIGHT, 0x02C204, 0x08 ),
   INP0( P1_B1, 0x02C204, 0x10 ),
   INP0( P1_B2, 0x02C204, 0x20 ),

   INP0( P2_START, 0x02C20E, 0x80 ),
   INP0( P2_UP, 0x02C206, 0x01 ),
   INP0( P2_DOWN, 0x02C206, 0x02 ),
   INP0( P2_LEFT, 0x02C206, 0x04 ),
   INP0( P2_RIGHT, 0x02C206, 0x08 ),
   INP0( P2_B1, 0x02C206, 0x10 ),
   INP0( P2_B2, 0x02C206, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_kuri_kinton_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_kurikina[] =
{
   { 0x02C200, 0xFF, dsw_data_kuri_kinton_0 },
   { 0x02C202, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

/* Kuri kinton has quite a special romsw, it's in the data bank, bank 0xf
 * See read_kurikint_region and write_kurikint_region */
static struct ROMSW_DATA romsw_data_kuri_kinton_0[] =
{
   { "Taito Japan (Notice)",       0x00 },
   { "Taito America",              0x01 },
   { "Taito Japan",                0x02 },
   { "Taito Japan (Osaka Office)", 0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_kurikint[] =
{
   { 0x007FFF, 0x02, romsw_data_kuri_kinton_0 },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_kurikint[] =
{
   {     "b42-09.2", 0x00020000, 0xe97c4394, 0, 0, 0, },
   {  "b42-07.22", 0x00010000, 0x0f2719c0, 0, 0, 0, },
   {     "b42-06.6", 0x00020000, 0xfa15fd65, 0, 0, 0, },
   {     "b42-01.1", 0x00080000, 0x7d1a1fec, 0, 0, 0, },
   {     "b42-02.5", 0x00080000, 0x1a52e65c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_kurikinj[] =
{
   {     "b42_05.2", 0x00020000, 0x077222b8, 0, 0, 0, },
   {  "b42-07.22", 0x00010000, 0x0f2719c0, 0, 0, 0, },
   {     "b42-06.6", 0x00020000, 0xfa15fd65, 0, 0, 0, },
   {     "b42-01.1", 0x00080000, 0x7d1a1fec, 0, 0, 0, },
   {     "b42-02.5", 0x00080000, 0x1a52e65c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_kuri_kinton_alt_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_kurikint[] =
{
   { 0x02C200, 0xFF, dsw_data_kuri_kinton_alt_0 },
   { 0x02C202, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};



/************
   PLOTTING
 ************/

static struct ROM_INFO rom_plotting[] =
{
  { "ic10", 0x10000, 0xbe240921, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "b96-07.ic9", 0x10000, 0x0713a387, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "b96-08.ic8", 0x10000, 0x55b8e294, REGION_GFX1, 0x10000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_plottinga[] = // clone of plotting
{
  { "plot01.ic10", 0x10000, 0x5b30bc25, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "b96-02.ic9", 0x10000, 0x6e0bad2a, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "b96-03.ic8", 0x10000, 0xfb5f3ca4, REGION_GFX1, 0x10000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_plottingb[] = // clone of plotting
{
  { "b96-06.ic10", 0x10000, 0xf89a54b1, REGION_CPU1, 0x00000, LOAD_NORMAL },
  { "b96-02.ic9", 0x10000, 0x6e0bad2a, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "b96-03.ic8", 0x10000, 0xfb5f3ca4, REGION_GFX1, 0x10000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_plotting[] =
{
   INP0( COIN1, 0x02C200, 0x02 ),
   INP0( COIN2, 0x02C201, 0x02 ),
   INP0( TILT, 0x02C201, 0x01 ),
   INP0( SERVICE, 0x02C200, 0x01 ),

   INP0( P1_START, 0x02C200, 0x04 ),
   INP0( P1_UP, 0x02C200, 0x08 ),
   INP0( P1_DOWN, 0x02C200, 0x10 ),
   INP0( P1_LEFT, 0x02C200, 0x20 ),
   INP0( P1_RIGHT, 0x02C200, 0x40 ),
   INP0( P1_B1, 0x02C200, 0x80 ),

   INP0( P2_START, 0x02C201, 0x04 ),
   INP0( P2_UP, 0x02C201, 0x08 ),
   INP0( P2_DOWN, 0x02C201, 0x10 ),
   INP0( P2_LEFT, 0x02C201, 0x20 ),
   INP0( P2_RIGHT, 0x02C201, 0x40 ),
   INP0( P2_B1, 0x02C201, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_plotting_0[] =
{
   { _("Max Players"),           0x01, 0x02 },
   { "2",                     0x01},
   { "1",                     0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN_SLOTS,          0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { _("Continue cost"),         0xC0, 0x04 },
   { _("Same as play"),          0xC0},
   { _("1 extra coin"),          0x80},
   { _("2 extra coins"),         0x40},
   { _("3 extra coins"),         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_plotting_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Wild blocks"),           0x30, 0x04 },
   { "2",                     0x30},
   { "1",                     0x20},
   { "3",                     0x10},
   { "4",                     0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_plotting[] =
{
   { 0x02C202, 0xFF, dsw_data_plotting_0 },
   { 0x02C203, 0xFF, dsw_data_plotting_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_plotting_0[] =
{
   { "Taito Japan (Flipull)", 0x00 },
   { "Taito America",         0x01 },
   { "Taito Japan",           0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO plotting_romsw[] =
{
   { 0x007FFF, 0x02, romsw_data_plotting_0 },
   { 0,        0,    NULL },
};

/***********
   PUZZNIC
 ***********/


static struct ROM_INFO rom_puzznic[] =
{
   {      "u09.rom", 0x00020000, 0x3c115f8b, 0, 0, 0, },
   {      "u10.rom", 0x00020000, 0x4264056c, 0, 0, 0, },
   {      "u11.rom", 0x00020000, 0xa4150b6c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_puzznic[] =
{
   INP0( COIN1, 0x02C200, 0x02 ),
   INP0( SERVICE, 0x02C200, 0x01 ),

   INP0( P1_START, 0x02C200, 0x04 ),
   INP0( P1_UP, 0x02C200, 0x08 ),
   INP0( P1_DOWN, 0x02C200, 0x10 ),
   INP0( P1_LEFT, 0x02C200, 0x20 ),
   INP0( P1_RIGHT, 0x02C200, 0x40 ),
   INP0( P1_B1, 0x02C201, 0x01 ),
   INP0( P1_B2, 0x02C200, 0x80 ),

   INP0( P2_START, 0x02C201, 0x04 ),
   INP0( P2_UP, 0x02C201, 0x08 ),
   INP0( P2_DOWN, 0x02C201, 0x10 ),
   INP0( P2_LEFT, 0x02C201, 0x20 ),
   INP0( P2_RIGHT, 0x02C201, 0x40 ),
   INP0( P2_B1, 0x02C201, 0x02 ),
   INP0( P2_B2, 0x02C201, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_puzznic_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN_SLOTS,          0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_puzznic_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Retries"),               0x0C, 0x04 },
   { "2",                     0x0C},
   { "3",                     0x08},
   { "1",                     0x04},
   { "0",                     0x00},
   { _("Bombs"),                 0x10, 0x02 },
   { "0",                     0x10},
   { "2",                     0x00},
   { _("Girls"),                 0x20, 0x02 },
   { MSG_ON,                  0x20},
   { MSG_OFF,                 0x00},
   { _("Terms of Replay"),       0xC0, 0x04 },
   { _("Stage Start/Timer Cont"),0xC0},
   { _("Stage & Timer Start"),   0x80},
   { _("One step back/Time Cnt"),0x40},
   { _("No Use"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_puzznic[] =
{
   { 0x02C202, 0xFE, dsw_data_puzznic_0 },
   { 0x02C203, 0x7F, dsw_data_puzznic_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_puzznic_0[] =
{
   { "Animation 20/Taito Japan", 0x01 },
   { "Taito America",            0x02 },
   { "Taito Japan",              0x03 },
   { NULL,                       0    },
};

static struct ROMSW_INFO romsw_puzznic[] =
{
   { 0x007FFF, 0x01, romsw_data_puzznic_0 },
   { 0,        0,    NULL },
};


/**************
   PLAY GIRLS
 **************/


static struct ROM_INFO rom_plgirls[] =
{
   {     "pg01.ic7", 0x00040000, 0x79e41e74, 0, 0, 0, },
   {     "pg02.ic9", 0x00040000, 0x3cf05ca9, 0, 0, 0, },
   {     "pg03.ic6", 0x00040000, 0x6ca73092, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_plgirls[] =
{
   INP0( COIN1, 0x0A800, 0x04 ),
   INP0( COIN2, 0x0A800, 0x08 ),
   INP0( TILT, 0x0A800, 0x02 ),
   INP0( SERVICE, 0x0A800, 0x01 ),

   INP0( P1_START, 0x0A800, 0x10 ),
   INP0( P1_UP, 0x0A801, 0x01 ),
   INP0( P1_DOWN, 0x0A801, 0x02 ),
   INP0( P1_LEFT, 0x0A801, 0x04 ),
   INP0( P1_RIGHT, 0x0A801, 0x08 ),
   INP0( P1_B1, 0x0A800, 0x40 ),
   INP0( P1_B2, 0x0A800, 0x80 ),

   INP0( P2_START, 0x0A800, 0x20 ),
   INP0( P2_UP, 0x0A801, 0x10 ),
   INP0( P2_DOWN, 0x0A801, 0x20 ),
   INP0( P2_LEFT, 0x0A801, 0x40 ),
   INP0( P2_RIGHT, 0x0A801, 0x80 ),
   INP0( P2_B1, 0x0A802, 0x01 ),
   INP0( P2_B2, 0x0A802, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_plgirls_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   { MSG_COIN_SLOTS,          0x38, 0x08 },
   { MSG_1COIN_1PLAY,         0x38},
// { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x28},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x18},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x08},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_plgirls_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_DSWA_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
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

static struct DSW_INFO dsw_plgirls[] =
{
   { 0x02C202, 0xFE, dsw_data_plgirls_0 },
   { 0x02C203, 0x7F, dsw_data_plgirls_1 },
   { 0,        0,    NULL,      },
};


/****************
   PLAY GIRLS 2
 ****************/


static struct ROM_INFO rom_plgirls2[] =
{
   {    "cho-h.ic7", 0x00080000, 0x992f99b1, 0, 0, 0, },
   {    "cho-l.ic9", 0x00080000, 0x956384ec, 0, 0, 0, },
   {   "pg2_1j.ic6", 0x00040000, 0xf924197a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_plgirls2[] =
{
   INP0( COIN1, 0x0A800, 0x04 ),
   INP0( COIN2, 0x0A800, 0x08 ),
   INP0( TILT, 0x0A800, 0x02 ),
   INP0( SERVICE, 0x0A800, 0x01 ),

   INP0( P1_START, 0x0A800, 0x10 ),
   INP0( P1_UP, 0x0A801, 0x01 ),
   INP0( P1_DOWN, 0x0A801, 0x02 ),
   INP0( P1_LEFT, 0x0A801, 0x04 ),
   INP0( P1_RIGHT, 0x0A801, 0x08 ),
   INP0( P1_B1, 0x0A800, 0x40 ),
   INP0( P1_B2, 0x0A800, 0x80 ),

   INP0( P2_START, 0x0A800, 0x20 ),
   INP0( P2_UP, 0x0A801, 0x10 ),
   INP0( P2_DOWN, 0x0A801, 0x20 ),
   INP0( P2_LEFT, 0x0A801, 0x40 ),
   INP0( P2_RIGHT, 0x0A801, 0x80 ),
   INP0( P2_B1, 0x0A802, 0x01 ),
   INP0( P2_B2, 0x0A802, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_plgirls2_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   { MSG_DSWA_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_plgirls2_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_DSWA_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { _("Life"),                  0x18, 0x04 },
   { "4/3/4",                 0x18},
   { "3/2/3",                 0x10},
   { "5/4/5",                 0x08},
   { "6/5/6",                 0x00},
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

static struct DSW_INFO dsw_plgirls2[] =
{
   { 0x02C202, 0xFE, dsw_data_plgirls2_0 },
   { 0x02C203, 0x7F, dsw_data_plgirls2_1 },
   { 0,        0,    NULL,      },
};


/*************
   PALAMEDES
 *************/


static struct ROM_INFO rom_palamed[] =
{
   {       "c63.02", 0x00020000, 0x55a82bb2, 0, 0, 0, },
   {       "c63.03", 0x00020000, 0xfcd86e44, 0, 0, 0, },
   {       "c63.04", 0x00020000, 0xc7bbe460, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_palamed[] =
{
   INP0( COIN1, 0x02C200, 0x04 ),
   INP0( COIN2, 0x02C200, 0x08 ),
   INP0( TILT, 0x02C200, 0x02 ),
   INP0( SERVICE, 0x02C200, 0x01 ),

   INP0( P1_START, 0x02C200, 0x10 ),
   INP0( P1_UP, 0x02C202, 0x01 ),
   INP0( P1_DOWN, 0x02C202, 0x02 ),
   INP0( P1_LEFT, 0x02C202, 0x04 ),
   INP0( P1_RIGHT, 0x02C202, 0x08 ),
   INP0( P1_B1, 0x02C200, 0x40 ),
   INP0( P1_B2, 0x02C200, 0x80 ),

   INP0( P2_START, 0x02C200, 0x20 ),
   INP0( P2_UP, 0x02C202, 0x10 ),
   INP0( P2_DOWN, 0x02C202, 0x20 ),
   INP0( P2_LEFT, 0x02C202, 0x40 ),
   INP0( P2_RIGHT, 0x02C202, 0x80 ),
   INP0( P2_B1, 0x02C204, 0x01 ),
   INP0( P2_B2, 0x02C204, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_palamedes_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN_SLOTS,          0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_palamedes_1[] =
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
   { MSG_DSWB_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Versus Mode"),           0x80, 0x02 },
   { MSG_ON,                  0x80},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_palamed[] =
{
   { 0x02C210, 0xFF, dsw_data_palamedes_0 },
   { 0x02C212, 0xFF, dsw_data_palamedes_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_palamedes_0[] =
{
   { "Taito Japan (Japanese)",   0x00 },
   { "Taito America",            0x01 },
   { "Taito Japan",              0x02 },
   { "Hot-B America",            0x03 },
   { NULL,                       0    },
};

static struct ROMSW_INFO romsw_palamed[] =
{
   { 0x007FFF, 0x00, romsw_data_palamedes_0 },
   { 0,        0,    NULL },
};


/*************
   CUBYBOP
 *************/


static struct ROM_INFO rom_cubybop[] =
{
   {       "cb06.6", 0x00040000, 0x66b89a85, 0, 0, 0, },
   {       "cb07.7", 0x00040000, 0x3582de99, 0, 0, 0, },
   {       "cb08.8", 0x00040000, 0x09e18a51, 0, 0, 0, },
   {       "cb09.9", 0x00040000, 0x5f831e59, 0, 0, 0, },
   {      "cb10.10", 0x00040000, 0x430510fc, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_cubybop[] =
{
   INP0( COIN1, 0x02C200, 0x04 ),
   INP0( COIN2, 0x02C200, 0x08 ),
   INP0( TILT, 0x02C200, 0x02 ),
   INP0( SERVICE, 0x02C200, 0x01 ),

   INP0( P1_START, 0x02C200, 0x10 ),
   INP0( P1_UP, 0x02C202, 0x01 ),
   INP0( P1_DOWN, 0x02C202, 0x02 ),
   INP0( P1_LEFT, 0x02C202, 0x04 ),
   INP0( P1_RIGHT, 0x02C202, 0x08 ),
   INP0( P1_B1, 0x02C200, 0x40 ),
   INP0( P1_B2, 0x02C200, 0x80 ),

   INP0( P2_START, 0x02C200, 0x20 ),
   INP0( P2_UP, 0x02C202, 0x10 ),
   INP0( P2_DOWN, 0x02C202, 0x20 ),
   INP0( P2_LEFT, 0x02C202, 0x40 ),
   INP0( P2_RIGHT, 0x02C202, 0x80 ),
   INP0( P2_B1, 0x02C204, 0x01 ),
   INP0( P2_B2, 0x02C204, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_cubybop_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN_SLOTS,          0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_cubybop_1[] =
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
   { MSG_DSWB_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Versus Mode"),           0x80, 0x02 },
   { MSG_ON,                  0x80},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_cubybop[] =
{
   { 0x02C210, 0xFF, dsw_data_cubybop_0 },
   { 0x02C212, 0xFF, dsw_data_cubybop_1 },
   { 0,        0,    NULL,      },
};


/*************
   TUBE IT
 *************/


static struct ROM_INFO rom_tubeit[] =
{
   {     "t-i_02.6", 0x00020000, 0x54730669, 0, 0, 0, },
   {     "t-i_03.7", 0x00040000, 0xe1c3fed0, 0, 0, 0, },
   {     "t-i_04.9", 0x00040000, 0xb4a6e31d, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


/***********
   RAIMAIS
 ***********/


static struct ROM_INFO rom_raimais[] =
{
   {   "b36-01.bin", 0x00080000, 0x89355cb2, 0, 0, 0, },
   {   "b36-02.bin", 0x00080000, 0xe71da5db, 0, 0, 0, },
   {   "b36-03.bin", 0x00080000, 0x96166516, 0, 0, 0, },
   {   "b36-06.bin", 0x00010000, 0x29bbc4f8, 0, 0, 0, },
   {   "b36-07.bin", 0x00010000, 0x4f3737e6, 0, 0, 0, },
   { "b36-08-1.bin", 0x00020000, 0x6cc8f79f, 0, 0, 0, },
   {   "b36-09.bin", 0x00020000, 0x9c466e43, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_raimais[] =
{
   INP1( COIN1, 0x02C20E, 0x04 ),
   INP1( COIN2, 0x02C20E, 0x08 ),
   INP0( TILT, 0x02C20E, 0x01 ),
   INP0( SERVICE, 0x02C20E, 0x02 ),

   INP0( P1_START, 0x02C20E, 0x40 ),
   INP0( P1_UP, 0x02C204, 0x01 ),
   INP0( P1_DOWN, 0x02C204, 0x02 ),
   INP0( P1_LEFT, 0x02C204, 0x04 ),
   INP0( P1_RIGHT, 0x02C204, 0x08 ),
   INP0( P1_B1, 0x02C204, 0x10 ),
   INP0( P1_B2, 0x02C204, 0x20 ),

   INP0( P2_START, 0x02C20E, 0x80 ),
   INP0( P2_UP, 0x02C206, 0x01 ),
   INP0( P2_DOWN, 0x02C206, 0x02 ),
   INP0( P2_LEFT, 0x02C206, 0x04 ),
   INP0( P2_RIGHT, 0x02C206, 0x08 ),
   INP0( P2_B1, 0x02C206, 0x10 ),
   INP0( P2_B2, 0x02C206, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_raimais_0[] =
{
   DSW_CABINET( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_raimais_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("80k only"),              0x0C},
   { _("80k and 160k"),          0x08},
   { _("160k only"),             0x04},
   { _("None"),                  0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "6",                     0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_raimais[] =
{
   { 0x02C200, 0xFE, dsw_data_raimais_0 },
   { 0x02C202, 0x7F, dsw_data_raimais_1 },
   { 0,        0,    NULL,      },
};


/*

TAITO L-SYSTEM
--------------

Supported romsets:

0 - B36 - Raimais               - 1988 - L-System
1 - C47 - American Horseshoes   - 1990 - L-System (vertical) (trackball) (gfx bank)
2 - B96 - Plotting              - 1989 - L-System
3 - C01 - Champion Wrestler     - 1989 - L-System
4 - B70 - Fighting Hawk         - 1988 - L-System (vertical)
5 - B42 - Kuri Kinton           - 1988 - L-System
. - ... - Kuri Kinton alternate - 1988 - L-System
6 - C20 - Puzznic               - 1989 - L-System (mcu)
7 - C63 - Palamedes             - 1990 - L-System
8 - D?? - Cachat                - 1993 - L-System
9 - ??? - Cuby Bop              - 1990 - L-System

Z80 has banked Video RAM, it has 4 bank slots:

C000-CFFF
D000-DFFF
E000-EFFF
F000-FDFF (last 512 bytes are not accessable in this bank)

Each bank can access any one of the following:

------+--------------+----------
 Byte | Access       | Range
------+--------------+----------
  14  | FG0 GFX RAM  | 0000-0FFF
  15  | FG0 GFX RAM  | 1000-1FFF
  16  | FG0 GFX RAM  | 2000-2FFF
  17  | FG0 GFX RAM  | 3000-3FFF
  18  | SCREEN RAM   | 0000-0FFF
  19  | SCREEN RAM   | 1000-1FFF
  1A  | SCREEN RAM   | 2000-2FFF
  1B  | SCREEN RAM   | 3000-3FFF
  1C  | FG0 GFX RAM  | 4000-4FFF (Champion Wrestler)
  1D  | FG0 GFX RAM  | 5000-5FFF (Champion Wrestler)
  1E  | FG0 GFX RAM  | 6000-6FFF (Champion Wrestler)
  1F  | FG0 GFX RAM  | 7000-7FFF (Champion Wrestler)
  80  | COLOR RAM    | 0000-01FF
------+--------------+----------

SCREEN RAM
----------

----------+----
 Offset   | Use
----------+----
0000-0FFF | BG1
1000-1FFF | BG0
2000-2FFF | FG0
3000-33FF | SPR
----------+----

INTERRUPT VECTORS
-----------------

0 - Interrupt#0
1 - Interrupt#1
2 - Interrupt#2
3 - Bit#0 = Interrupt#0 Enable
    Bit#1 = Interrupt#1 Enable
    Bit#2 = Interrupt#2 Enable

TILE BANK
---------

0 - Bank#0
1 - Bank#1
2 - Bank#2
3 - Bank#3
4 - Bit#3 = Sprite Dual Priority <?>
    Bit#4 = Screen Normal/Invert
    Bit#5 = Disable Layer <???>
    Bit#6 = Disable Layer <???>
    Bit#7 = Disable Layer <???>
5 - Unused <?>
6 - Unused <?>
7 - Unused <?>

OBJECT RAM
----------

-----+--------+-------------------------
Byte | Bit(s) | Use
-----+76543210+-------------------------
  1  |..xxxxxx| Sprite Tile (high)
  0  |xxxxxxxx| Sprite Tile (low)
  3  |......xx| Flip XY
  2  |....xxxx| Colour Bank
  5  |.......x| Sprite X (high)
  4  |xxxxxxxx| Sprite X (low)
  7  |........| Sprite Y (high)
  6  |xxxxxxxx| Sprite Y (low)
-----+--------+-------------------------

Todo:

- Language switches (Raimais).
- Stuff not in RAM[] is unsaved.
- American Horseshoes trackball emulation needs improving.

*/

static UINT8 ReadTrackBall(UINT16 offset)
{
   return RAM_INP[4|((offset>>2)&3)];
}

/******************************************************************************/
/* L-SYSTEM INTERRUPT VECTORS                                                 */
/******************************************************************************/

static void LSystemIntVecWrite(UINT16 offset, UINT8 data)
{
   VectorData[offset&3] = data;
}

static UINT8 LSystemIntVecRead(UINT16 offset)
{
   return VectorData[offset&3];
}

static UINT8 ah_gfx_bank;

static void LSystemTileBank2Write(UINT16 offset, UINT8 data)
{
   static int kkk[4] =
   {
      0,2,1,3,
   };

   ah_gfx_bank = kkk[data];

   /*#ifdef RAINE_DEBUG
   print_ingame(8000,gettext("ah_gfx_bank Bank(%04x,%02x) [%02x]\n"),offset,data,ah_gfx_bank);
#endif*/
}

/******************************************************************************/
/* L-SYSTEM TILE BANKING                                                      */
/******************************************************************************/

static UINT8 TileBank[8];

static void LSystemTileBankWrite(UINT16 offset, UINT8 data)
{
   TileBank[offset&7] = data;
#ifdef RAINE_DEBUG
   if((offset&7)>3) print_debug("Tile Bank(%02x,%02x)\n",offset&7,data);
#endif
}

static UINT8 LSystemTileBankRead(UINT16 offset)
{
   return TileBank[offset&7];
}

/******************************************************************************/
/* L-SYSTEM Z80 ROM BANKING                                                   */
/******************************************************************************/

static UINT8 Z80BankCount;

static void LSystemNewBankWrite(UINT16 offset, UINT8 data)
{
  z80_set_bank(1,data);
}

static UINT8 LSystemBankRead(UINT16 offset)
{
  return z80_get_current_bank(1);
}

extern UINT8 *ROM_BANK[];
static UINT8 lsystem_ym2203_reg;
static UINT8 VRAMBank[4];

static void init_bank_rom(UINT8 *src )
{
  int i;
  UINT8 *dest;
  ah_gfx_bank = 0;
  lsystem_ym2203_reg = 0;
  memset(TileBank,0,8);
  memset(VRAMBank,0,4);

  z80_init_banks_area_ofs(1,src,Z80BankCount * 0x2000,0x6000,0x2000,3);
  // Here the first banks contain a copy of the roms (stupid !)
  for (i=0; i<3; i++) {
    dest = ROM_BANK[1] + i * 0x8000 + 0x6000;
    memcpy(dest,src+i*0x2000,0x2000);
  }
}

/******************************************************************************/
/* L-SYSTEM SUB Z80 ROM BANKING                                               */
/******************************************************************************/

static UINT8 Z802Bank;
static UINT8 Z802BankCount;

static void LSystemSubCpuNewBankWrite(UINT16 offset, UINT8 data)
{
  Z802Bank = data;
  z80_set_bank(2,data & 0xf);
/*    if((data&0x20)==0x20){	// WAS: 0xF0 */

/*    data&=0x0F; */
/*    if(data != Z802Bank){ */
/*       if(data<Z802BankCount){ */
/*          Z802Bank = data; */
/*          Z80CSetBank( ROM_BANK_2[Z802Bank] ); */
/*       } */
/*       else{ */
/*          print_debug("SUB Z80 ROM Bank out of range: %02x [%04x]\n", data, z80pc); */
/*       } */
/*    } */

/*    } */
/*    else{ */
/*       print_debug("SUB Z80 ROM Bank strange: %02x [%04x]\n", data, z80pc); */
/*    } */
}

static UINT8 LSystemSubCpuBankRead(UINT16 offset)
{
   return Z802Bank;
}

static void init_bank_rom2(UINT8 *src)
{
  int i;
  UINT8 *dest;
  Z802Bank = -1;
  z80_init_banks_area_ofs(2,src,Z802BankCount * 0x4000,0x8000,0x4000,2);
  // Here the first banks contain a copy of the roms (stupid !)
  for (i=0; i<3; i++) {
    dest = ROM_BANK[2] + i * 0xc000 + 0x8000;
    memcpy(dest,src+i*0x4000,0x4000);
  }
}

/******************************************************************************/
/* L-SYSTEM FG0 GFX RAM                                                       */
/******************************************************************************/

static UINT8 *RAM_FG0;		// $4000*2 bytes
static UINT8 *GFX_FG0;		// $8000*2 bytes

static UINT32 gfx_fg0_dirty_count;
static UINT32 GFX_FG0_DIRTY[0x400];
static UINT8 GFX_FG0_SOLID[0x400];

static void update_gfx_fg0(void)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *source;

   for(ta = 0; ta < gfx_fg0_dirty_count; ta++){

      tb = GFX_FG0_DIRTY[ta];
      source = GFX_FG0 + (tb << 6);

      td=0;
      te=0;
      for(tc=0;tc<0x40;tc++){
         if(source[tc])
            td=1;
         else
            te=1;
      }
      if((td==0)&&(te==1)) GFX_FG0_SOLID[tb]=0;		// All pixels are 0: Don't Draw
      if((td==1)&&(te==1)) GFX_FG0_SOLID[tb]=1;		// Mixed: Draw Trans
      if((td==1)&&(te==0)) GFX_FG0_SOLID[tb]=2;		// All pixels are !0: Draw Solid

   }

   gfx_fg0_dirty_count = 0;
}

static DEF_INLINE void LSystem_GFX_FG0_Write(UINT16 offset, UINT8 data)
{
   UINT32 i,j,k;
   UINT8 *GFX_FG;

   if(data == RAM_FG0[offset])

      return;

   RAM_FG0[offset] = data;

   i = (offset & 0x001E) << 1;
   k = (offset & 0x7FE0) >> 5;

   GFX_FG = GFX_FG0 + (k<<6);

   if(!(offset&1)){
      j = tile_8x8_map[ i + 0 ];
      GFX_FG[j] = (GFX_FG[j]&0x0C)|(((data&0x01)>>0)<<0)|(((data&0x10)>>4)<<1);
      j = tile_8x8_map[ i + 1 ];
      GFX_FG[j] = (GFX_FG[j]&0x0C)|(((data&0x02)>>1)<<0)|(((data&0x20)>>5)<<1);
      j = tile_8x8_map[ i + 2 ];
      GFX_FG[j] = (GFX_FG[j]&0x0C)|(((data&0x04)>>2)<<0)|(((data&0x40)>>6)<<1);
      j = tile_8x8_map[ i + 3 ];
      GFX_FG[j] = (GFX_FG[j]&0x0C)|(((data&0x08)>>3)<<0)|(((data&0x80)>>7)<<1);
   }
   else{
      j = tile_8x8_map[ i + 0 ];
      GFX_FG[j] = (GFX_FG[j]&0x03)|(((data&0x01)>>0)<<2)|(((data&0x10)>>4)<<3);
      j = tile_8x8_map[ i + 1 ];
      GFX_FG[j] = (GFX_FG[j]&0x03)|(((data&0x02)>>1)<<2)|(((data&0x20)>>5)<<3);
      j = tile_8x8_map[ i + 2 ];
      GFX_FG[j] = (GFX_FG[j]&0x03)|(((data&0x04)>>2)<<2)|(((data&0x40)>>6)<<3);
      j = tile_8x8_map[ i + 3 ];
      GFX_FG[j] = (GFX_FG[j]&0x03)|(((data&0x08)>>3)<<2)|(((data&0x80)>>7)<<3);
   }

   // request mask update

   if(GFX_FG0_SOLID[k] != 3){
      GFX_FG0_SOLID[k] = 3;
      GFX_FG0_DIRTY[gfx_fg0_dirty_count++] = k;
   }
}

static DEF_INLINE UINT16 LSystem_GFX_FG0_Read(UINT16 offset)
{
   return RAM_FG0[offset];
}

/******************************************************************************/
/* L-SYSTEM BG0 RAM                                                           */
/******************************************************************************/

static UINT8 *RAM_BG0;		// $4000 bytes

static DEF_INLINE void LSystem_BG0_Write(UINT16 offset, UINT8 data)
{
   RAM_BG0[offset] = data;
}

static DEF_INLINE UINT16 LSystem_BG0_Read(UINT16 offset)
{
   return RAM_BG0[offset];
}

/******************************************************************************/
/* L-SYSTEM COLOUR RAM                                                        */
/******************************************************************************/

static DEF_INLINE void LSystem_PAL_Write(UINT16 offset, UINT8 data)
{
   RAM_PAL[offset&0x1FF] = data;
}

static DEF_INLINE UINT16 LSystem_PAL_Read(UINT16 offset)
{
   return RAM_PAL[offset&0x1FF];
}

/******************************************************************************/
/* L-SYSTEM VRAM BANKING                                                      */
/******************************************************************************/

static void LSystemVRAMBankWrite(UINT16 offset, UINT8 data)
{
   VRAMBank[offset&3] = data;
}

static UINT8 LSystemVRAMBankRead(UINT16 offset)
{
   return VRAMBank[offset&3];
}

/******************************************************************************/
/* L-SYSTEM BANKED VRAM ACCESS                                                */
/******************************************************************************/

static void LSystemVRAMWrite(UINT16 offset, UINT8 data)
{
   int bank;

   bank=VRAMBank[(offset>>12)&3];
   offset&=0xFFF;

   switch(bank){
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
         LSystem_GFX_FG0_Write((UINT16) (offset|((bank&3)<<12)), data);
      break;
      case 0x18:
      case 0x19:
      case 0x1A:
      case 0x1B:
         LSystem_BG0_Write((UINT16) (offset|((bank&3)<<12)), data);
      break;
      case 0x1C:
      case 0x1D:
      case 0x1E:
      case 0x1F:
         LSystem_GFX_FG0_Write((UINT16) (offset|(((bank&3)|4)<<12)), data);
      break;
      case 0x80:
         LSystem_PAL_Write(offset, data);
      break;
      default:
             print_debug("VRAM Write to Strange Bank(%02x:%04x,%02x) [%04x]\n",bank,offset,data,z80pc);
      break;
   }
}

static UINT8 LSystemVRAMRead(UINT16 offset)
{
   int bank;

   bank=VRAMBank[(offset>>12)&3];
   offset&=0xFFF;

   switch(bank){
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
         return(LSystem_GFX_FG0_Read((UINT16) (offset|((bank&3)<<12))));
      break;
      case 0x18:
      case 0x19:
      case 0x1A:
      case 0x1B:
         return(LSystem_BG0_Read((UINT16) (offset|((bank&3)<<12))));
      break;
      case 0x1C:
      case 0x1D:
      case 0x1E:
      case 0x1F:
         return(LSystem_GFX_FG0_Read((UINT16) (offset|(((bank&3)|4)<<12))));
      break;
      case 0x80:
         return(LSystem_PAL_Read(offset));
      break;
      default:
             print_debug("VRAM Read from Strange Bank(%02x:%04x) [%04x]\n",bank,offset,z80pc);
         return(0xFF);
      break;
   }
}

static int layer_id_data[5];
static void lsystem_vcu_init(int fg0_size)
{
   memset(RAM_BG0,0x00,0x4000);
   memset(RAM_PAL,0x00,0x0200);

   VRAMBank[0] = 0;
   VRAMBank[1] = 0;
   VRAMBank[2] = 0;
   VRAMBank[3] = 0;

   memset(RAM_FG0,0x00,0x4000<<fg0_size);
   memset(GFX_FG0,0x00,0x8000<<fg0_size);

   gfx_fg0_dirty_count = 0;
   memset(GFX_FG0_DIRTY,0x00,0x400*4);
   memset(GFX_FG0_SOLID,0x00,0x400);
   layer_id_data[0] = add_layer_info(gettext("BG0"));
   layer_id_data[1] = add_layer_info(gettext("OBJ"));
   layer_id_data[2] = add_layer_info(gettext("BG1"));
   layer_id_data[3] = add_layer_info(gettext("OBJ 2"));
   layer_id_data[4] = add_layer_info(gettext("FG"));
   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);
   InitPaletteMap(RAM_PAL, 0x10, 0x10, 0x8000);
}

/******************************************************************************/
/* L-SYSTEM YM2203                                                            */
/******************************************************************************/

// YM2203 with dsw and inputs

static UINT8 lsystem_ym2203_input_dsw_rb(UINT16 offset)
{
   if(!(offset&1)){
      return YM2203_status_port_0_r(offset);
   }
   else{
      switch(lsystem_ym2203_reg){
         case 0x0e: return get_dsw((offset>>1)&1);
         case 0x0f: return RAM_INP[(offset>>1)&1];
      }
      return YM2203_read_port_0_r(offset);
   }
}

// YM2203 with dsw

static UINT8 lsystem_ym2203_dsw_rb(UINT16 offset)
{
   if(!(offset&1)){
      return YM2203_status_port_0_r(offset);
   }
   else{
      switch(lsystem_ym2203_reg){
         case 0x0e: return get_dsw(0);
         case 0x0f: return get_dsw(1);
      }
      return YM2203_read_port_0_r(offset);
   }
}

// YM2203 with nothing

static UINT8 lsystem_ym2203_rb(UINT16 offset)
{
   if(!(offset&1)){
      return YM2203_status_port_0_r(offset);
   }
   else{
      return YM2203_read_port_0_r(offset);
   }
}

static void lsystem_ym2203_wb(UINT16 offset, UINT8 data)
{
   if(!(offset&1)){
      lsystem_ym2203_reg = data;
      YM2203_control_port_0_w(offset,data);
   }
   else{
      YM2203_write_port_0_w(offset,data);
   }
}

/******************************************************************************/
/* PUZZNIC MCU                                                                */
/******************************************************************************/

static void PuzznicMCUWrite(UINT16 offset, UINT8 data)
{
   if((offset&1)==0){
      RAM[0xB800] = data;
   }
}

static UINT8 PuzznicMCURead(UINT16 offset)
{
   int ret;

   if((offset&1)==0){
      switch(RAM[0xB800]){
         case 0x43: ret = 0x50; RAM[0xB800]++; break;	// ID Check
         case 0x44: ret = 0x1F; RAM[0xB800]++; break;	// Mask value
         case 0x45: ret = 0xA6; RAM[0xB800]++; break;	// RAM A high +6
         case 0x46: ret = 0xB6; RAM[0xB800]++; break;	// RAM B high +6
         case 0x47: ret = 0x06; RAM[0xB800]++; break;	// RAM A/B low +6
         case 0x48: ret = 0x03; RAM[0xB800]++; break;
         case 0x49: ret = 0x47; RAM[0xB800]++; break;
         case 0x4A: ret = 0x05; RAM[0xB800]++; break;
         case 0x4B: ret = 0x00; RAM[0xB800]++; break;
         default:   ret = 0x00;                break;
      }
   }
   else{
      ret = 0x01;
   }
   return ret;
}

/******************************************************************************/
/* PALAMEDES LED                                                              */
/******************************************************************************/

static void palamedes_led_write(UINT16 offset, UINT8 data)
{
   tc0220ioc_wb_z80(4, (UINT8) (((data>>4)&0x03) | ((data>>0)&0x0C)) );
}

/******************************************************************************/

static void LSystemAddSaveData(void)
{
	memset(VectorData,0,4);
   AddSaveData(SAVE_USER_0, (UINT8 *) &VectorData,          sizeof(VectorData));
   AddSaveData(SAVE_USER_1, (UINT8 *) &ah_gfx_bank,         sizeof(ah_gfx_bank));
   AddSaveData(SAVE_USER_2, (UINT8 *) &TileBank,            sizeof(TileBank));
   AddSaveData(SAVE_USER_4, (UINT8 *) &Z802Bank,            sizeof(Z802Bank));
   AddSaveData(SAVE_USER_5, (UINT8 *) &VRAMBank,            sizeof(VRAMBank));
   AddSaveData(SAVE_USER_6, (UINT8 *) &lsystem_ym2203_reg,  sizeof(lsystem_ym2203_reg));

   AddSaveData(SAVE_USER_7, (UINT8 *) &gfx_fg0_dirty_count, sizeof(gfx_fg0_dirty_count));
   AddSaveData(SAVE_USER_8, (UINT8 *) &GFX_FG0_DIRTY,       sizeof(GFX_FG0_DIRTY));
   AddSaveData(SAVE_USER_9, (UINT8 *) &GFX_FG0_SOLID,       sizeof(GFX_FG0_SOLID));
}

/******************************************************************************/

static void DrawNibble0(UINT8 *out, int plane, UINT8 c)
{
   int count, t;

   count = 4;
      do {
         t = c & 1;
         *out = t << plane;
         out++;
         c >>= 1;
      } while(--count);
}

static void DrawNibble(UINT8 *out, int plane, UINT8 c)
{
   int count, t;

   count = 4;
      do {
         t = c & 1;
         *out |= t << plane;
         out++;
         c >>= 1;
      } while(--count);
}

static void load_raimais(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=0;
   Z80BankCount=0x40000/0x2000;
   Z802BankCount=0x10000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;
   if(!(ROM2 =AllocateMem(0xC000*Z802BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;
   Z80ROM =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20;
   RAM2   =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000;

   if(!(TMP =AllocateMem(0x40000))) return;

   /*-----[Sound Setup]-----*/

   if(!load_rom("b36-06.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("b36-03.bin",PCMROM,0x80000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x080000, 0x080000);

   AddTaitoYM2610(0x02BA, 0x025E, 0x10000);

   /*-----------------------*/

   if(!load_rom("b36-08-1.bin",TMP+0x00000,0x20000)) return;	// Z80 MAIN ROM
   if(!load_rom("b36-09.bin",  TMP+0x20000,0x20000)) return;	// Z80 MAIN ROM

   // Skip Idle Z80
   // -------------

   TMP[0x0121]=0xD3;  // OUTA (AAh)
   TMP[0x0122]=0xAA;  //

   SetStopZ80BMode2(0x0121);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x87FF, NULL,			RAM+0x08000);	// COMMON RAM
   AddZ80BReadByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0x8800, 0x8801, tc0220ioc_rb_z80_port,	NULL);		// INPUT
   AddZ80BReadByte(0x8C00, 0x8C01, tc0140syt_read_main_z80,     NULL);		// SOUND COMM
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x87FF, NULL,			RAM+0x08000);	// COMMON RAM
   AddZ80BWriteByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0x8800, 0x8801, tc0220ioc_wb_z80_port,	NULL);		// INPUT *
   AddZ80BWriteByte(0x8C00, 0x8C01, tc0140syt_write_main_z80,   NULL);		// SOUND COMM
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK *
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);	// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("b36-07.bin", TMP, 0x10000)) return;		// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   TMP[0x0038]=0xD3;  // OUTA (AAh)
   TMP[0x0039]=0xAA;  //

   SetStopZ80CMode2(0x0012);

   init_bank_rom2(TMP);

   memcpy(RAM2, TMP, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xBFFF, NULL,			NULL);		// BANK ROM
   AddZ80CReadByte(0xC000, 0xDFFF, NULL,			RAM2+0x0C000);	// WORK RAM
   AddZ80CReadByte(0xE000, 0xE7FF, NULL,			RAM +0x08000);	// COMMON RAM
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xDFFF, NULL,			RAM2+0x0C000);	// WORK RAM
   AddZ80CWriteByte(0xE000, 0xE7FF, NULL,			RAM +0x08000);	// COMMON RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   if(!(GFX=AllocateMem(0x200000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   tb=0;
   if(!load_rom("b36-01.bin", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=4,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+2]&15) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+2]>>4) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+3]&15) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+3]>>4) );
   }
   if(!load_rom("b36-02.bin", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=4,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+2]&15) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+2]>>4) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+3]&15) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+3]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x8000);

   spr_mask = 0x1FFF;
   tile_mask = 0x7FFF;

   lsystem_vcu_init(0);

   set_white_pen(127);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

static void load_horshoes(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=1;
   Z80BankCount=0x20000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x10+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x20000))) return;

   if(!load_rom("c47.03", TMP,0x20000)) return;	// Z80 MAIN ROM

   // Skip Idle Z80
   // -------------

   TMP[0x0151]=0xD3;  // OUTA (AAh)
   TMP[0x0152]=0xAA;  //

   SetStopZ80BMode2(0x0151);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM/COMMON RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA003, lsystem_ym2203_input_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xA800, 0xA810, ReadTrackBall,		NULL);		// TRACKBALL INPUT
   AddZ80BReadByte(0xB801, 0xB801, NULL,			RAM+0x0B800);	// ???
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM/COMMON RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,	        NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA003, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xB802, 0xB802, LSystemTileBank2Write,	NULL);		// EXTRA TILE BANK
   AddZ80BWriteByte(0xBC00, 0xBC00, NULL,			RAM+0x0BC00);	// ???
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x100000))) return;
   if(!(TMP=AllocateMem(0x040000))) return;

   tb=0;
   if(!load_rom("c47.02", TMP+0x00000, 0x20000)) return;
   if(!load_rom("c47.04", TMP+0x20000, 0x20000)) return;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }
   if(!load_rom("c47.01", TMP+0x00000, 0x20000)) return;
   if(!load_rom("c47.05", TMP+0x20000, 0x20000)) return;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x4000);

   spr_mask = 0x03FF;
   tile_mask = 0x0FFF;

   lsystem_vcu_init(0);

   set_white_pen(240);

   LSystemAddSaveData();

   GameMouse=1;
}

static void load_plotting(void)
{
   romset=2;
   Z80BankCount=get_region_size(REGION_CPU1)/0x2000;
   Z802BankCount=0;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x10+0x10000;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(ReadLong68k(&ROM[0])==0xC3A2C000) DecodePlotting(ROM);

   // Fix ROM Checksum
   // ----------------

   if (ReadWord68k(&ROM[0x434]) == 0xc2af) {
       ROM[0x434]=0x00;  // NOP
       ROM[0x435]=0x00;  // NOP
       ROM[0x436]=0x00;  // NOP
       // Skip Idle Z80
       // -------------

       ROM[0x0bb]=0xC3;
       ROM[0x0bc]=0x18;
       ROM[0x0bd]=0x00;
       SetStopZ80BMode2(0x0Be);
   } else {
       ROM[0x396]=0x00;  // NOP
       ROM[0x397]=0x00;  // NOP
       ROM[0x398]=0x00;  // NOP
       //
       // Skip Idle Z80
       // -------------

       ROM[0x0AF]=0xC3;
       ROM[0x0B0]=0x18;
       ROM[0x0B1]=0x00;
       SetStopZ80BMode2(0x0B2);
   }


   ROM[0x018]=0x3A;
   ROM[0x019]=0x31;
   ROM[0x01A]=0x82;

   ROM[0x01B]=0xD3;  // OUTA (AAh)
   ROM[0x01C]=0xAA;  //


   init_bank_rom(ROM);

   memcpy(RAM, ROM,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM/COMMON RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA003, lsystem_ym2203_input_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM/COMMON RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA003, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   /*-----------------------*/

   spr_mask = 0x03FF;
   tile_mask = 0x0FFF;

   lsystem_vcu_init(0);

   LSystemAddSaveData();
}


static void load_champwr(void)
{

   romset=3;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000+0x10000;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;
   RAM2   =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000;

   /*-----[Sound Setup]-----*/

   AddTaitoYM2203(0x02CE, 0x025A, 0x10000, NULL, 0x00000);

   /*-----------------------*/

   // Skip Idle Z80
   // -------------

//  if (is_current_game("champwr")) {
    ROM[0x0791]=0x00;  //
    ROM[0x0792]=0x00;  //

    ROM[0x01CD]=0xD3;  // OUTA (AAh)
    ROM[0x01CE]=0xAA;  //
    SetStopZ80BMode2(0x01CA);
//  }

   z80_init_banks(1,REGION_ROM1,0x6000,0x2000);

   // memcpy(RAM,ROM,0x10000);

   AddZ80BROMBase(ROM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0xBFFF, NULL,			RAM+0x08000);	// WORK RAM/COMMON RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0xBFFF, NULL,			RAM+0x08000);	// WORK RAM/COMMON RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   // Skip Idle Z80
   // -------------
   ROM = load_region[REGION_CPU3];

   ROM[0x037A]=0x00;  //
   ROM[0x037B]=0x00;  //
   ROM[0x037F]=0x18;  //

   ROM[0x010D]=0xD3;  // OUTA (AAh)
   ROM[0x010E]=0xAA;  //

   SetStopZ80CMode2(0x010D);

   z80_init_banks(2,REGION_ROM3,0x8000,0x4000);

   memcpy(RAM2, ROM, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xBFFF, NULL,			NULL);		// BANK ROM
   AddZ80CReadByte(0xD000, 0xDFFF, NULL,			RAM2+0x0D000);	// WORK RAM
   AddZ80CReadByte(0xC000, 0xCFFF, NULL,			RAM +0x0A000);	// COMMON RAM
   AddZ80CReadByte(0xE000, 0xE007, tc0220ioc_rb_z80,		NULL);		// INPUT
   AddZ80CReadByte(0xE008, 0xE00F, NULL,			RAM +0x0E008);	// PROTECTION?
   AddZ80CReadByte(0xE800, 0xE801, tc0140syt_read_main_z80,     NULL);		// SOUND COMM
   AddZ80CReadByte(0xF000, 0xF000, LSystemSubCpuBankRead,	NULL);		// ROM BANK
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xD000, 0xDFFF, NULL,			RAM2+0x0D000);	// WORK RAM
   AddZ80CWriteByte(0xC000, 0xCFFF, NULL,			RAM +0x0A000);	// COMMON RAM
   AddZ80CWriteByte(0xE000, 0xE007, tc0220ioc_wb_z80,		NULL);		// VSYNC
   AddZ80CWriteByte(0xE800, 0xE801, tc0140syt_write_main_z80,   NULL);		// SOUND COMM
   AddZ80CWriteByte(0xF000, 0xF000, LSystemSubCpuNewBankWrite,	NULL);		// ROM BANK
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   spr_mask = 0x3FFF;
   tile_mask = 0xFFFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

static void load_fhawk(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=4;
   Z80BankCount=0xA0000/0x2000;
   Z802BankCount=0x20000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;
   if(!(ROM2 =AllocateMem(0xC000*Z802BankCount))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;
   Z80ROM =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20;
   RAM2   =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000;

   /*-----[Sound Setup]-----*/

   if(!load_rom("b70-09.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   AddTaitoYM2203_B(0x02C3, 0x0254, 0x10000, NULL, 0x00000);

   /*-----------------------*/

   if(!(TMP =AllocateMem(0xA0000))) return;

   if(!load_rom("b70-07.bin",TMP+0x00000,0x20000)) return;	// Z80 MAIN ROM
   if(!load_rom("b70-03.bin",TMP+0x20000,0x80000)) return;	// DATA ROM

   // Skip Idle Z80
   // -------------

   TMP[0x010D]=0xD3;  // OUTA (AAh)
   TMP[0x010E]=0xAA;  //

   SetStopZ80BMode2(0x010D);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// Z80 ROM
   AddZ80BReadByte(0x8000, 0xBFFF, NULL,			RAM+0x08000);	// COMMUNICATE RAM/WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0xBFFF, NULL,			RAM+0x08000);	// COMMUNICATE RAM/WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,	        NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("b70-08.bin", TMP, 0x20000)) return;		// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   TMP[0x003E]=0x00;  // nop
   TMP[0x003F]=0x00;  // nop

   TMP[0x0025]=0xD3;  // OUTA (AAh)
   TMP[0x0026]=0xAA;  //

   SetStopZ80CMode2(0x0025);

   init_bank_rom2(TMP);

   memcpy(RAM2, TMP, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xBFFF, NULL,			NULL);		// BANK ROM
   AddZ80CReadByte(0xE000, 0xFFFF, NULL,			RAM +0x08000);	// COMMON RAM
   AddZ80CReadByte(0xC800, 0xC801, tc0140syt_read_main_z80,     NULL);		// SOUND COMM
   AddZ80CReadByte(0xD000, 0xD007, tc0220ioc_rb_z80,		NULL);		// INPUT
   AddZ80CReadByte(0xC000, 0xC000, LSystemSubCpuBankRead,	NULL);		// ROM BANK
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xE000, 0xFFFF, NULL,			RAM +0x08000);	// COMMON RAM
   AddZ80CWriteByte(0xC800, 0xC801, tc0140syt_write_main_z80,   NULL);		// SOUND COMM
   AddZ80CWriteByte(0xD000, 0xD007, tc0220ioc_wb_z80,		NULL);		// INPUT
   AddZ80CWriteByte(0xC000, 0xC000, LSystemSubCpuNewBankWrite,	NULL);		// ROM BANK
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   if(!(GFX=AllocateMem(0x200000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   tb=0;
   if(!load_rom("b70-01.bin", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=4,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+2]&15) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+2]>>4) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+3]&15) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+3]>>4) );
   }
   if(!load_rom("b70-02.bin", TMP, 0x80000)) return;
   for(ta=0;ta<0x80000;ta+=4,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+2]&15) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+2]>>4) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+3]&15) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+3]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x8000);

   spr_mask = 0x1FFF;
   tile_mask = 0x7FFF;

   lsystem_vcu_init(0);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

// read/write region from/to bank 0xf !
static int read_kurikint_region() {
    return read_z80_bank(1,0xf,0x7fff);
}
static void write_kurikint_region(int data) {
    write_z80_bank(1,0xf,0x7fff,data);
}

static void load_kurikint()
{
   int ta, tb,romset_2;
   UINT8 *TMP;
   read_region_byte = &read_kurikint_region;
   write_region_byte = &write_kurikint_region;

   if (is_current_game("kurikina"))
       romset_2 = 0;
   else if (is_current_game("kurikint"))
       romset_2 = 1;
   else if (is_current_game("kurikinj"))
       romset_2 = 2;

   romset=5;
   Z80BankCount=0x40000/0x2000;
   Z802BankCount=0x10000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;
   if(!(ROM2 =AllocateMem(0xC000*Z802BankCount))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;
   Z80ROM =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20;
   RAM2   =RAM+0x10000+0x8000+0x10000+0x4000+0x200+0x20+0x10000;

   if(!(TMP =AllocateMem(0x40000))) return;

   if(!load_rom_index(0, TMP+0x00000, 0x20000)) return;	// Z80 MAIN ROM
   if(!load_rom_index(2, TMP+0x20000, 0x20000)) return;	// DATA ROM

   // Skip Idle Z80
   // -------------

   if(romset_2 == 0){

   TMP[0x0241]=0xD3;  // OUTA (AAh)
   TMP[0x0242]=0xAA;  //

   SetStopZ80BMode2(0x023E);

   }
   else{

   TMP[0x0290]=0xD3;  // OUTA (AAh)
   TMP[0x0291]=0xAA;  //

   SetStopZ80BMode2(0x028D);

   }

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// Z80 ROM
   AddZ80BReadByte(0x8000, 0xA7FF, NULL,			RAM+0x08000);	// COMMUNICATE RAM/WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA800, 0xA801, tc0220ioc_rb_z80_port,	NULL);		// INPUT
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0xA7FF, NULL,			RAM+0x08000);	// COMMUNICATE RAM/WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA800, 0xA801, tc0220ioc_wb_z80_port,	NULL);		// INPUT
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom_index(1, TMP, 0x10000)) return;		// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   TMP[0x011E]=0xD3;  // OUTA (AAh)
   TMP[0x011F]=0xAA;  //

   SetStopZ80CMode2(0x011B);

   init_bank_rom2(TMP);

   memcpy(RAM2, TMP, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xBFFF, NULL,			NULL);		// BANK ROM
   AddZ80CReadByte(0xC000, 0xDFFF, NULL,			RAM2+0x0C000);	// WORK RAM
   AddZ80CReadByte(0xE000, 0xE7FF, NULL,			RAM +0x0A000);	// COMMON RAM
   AddZ80CReadByte(0xE800, 0xE801, lsystem_ym2203_rb,		NULL);		// YM2203
   AddZ80CReadByte(0xF000, 0xF000, LSystemSubCpuBankRead,	NULL);		// ROM BANK
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xDFFF, NULL,			RAM2+0x0C000);	// WORK RAM
   AddZ80CWriteByte(0xE000, 0xE7FF, NULL,			RAM +0x0A000);	// COMMON RAM
   AddZ80CWriteByte(0xE800, 0xE801, lsystem_ym2203_wb,		NULL);		// YM2203
   AddZ80CWriteByte(0xF000, 0xF000, LSystemSubCpuNewBankWrite,	NULL);		// ROM BANK
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x200000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   if (!strcmp(current_game->main_name,"kurikina"))
   {
     tb=0;
     if(!load_rom_index(3, TMP+0x00000, 0x20000)) return;
     if(!load_rom_index(4, TMP+0x20000, 0x20000)) return;
     if(!load_rom_index(5, TMP+0x40000, 0x20000)) return;
     if(!load_rom_index(6, TMP+0x60000, 0x20000)) return;
     for(ta=0;ta<0x40000;ta+=2,tb+=8){
        DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
        DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
        DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
        DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
        DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x40000]&15) );
        DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x40001]&15) );
        DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x40000]>>4) );
        DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x40001]>>4) );
     }
     if(!load_rom_index( 7, TMP+0x00000, 0x20000)) return;
     if(!load_rom_index( 9, TMP+0x20000, 0x20000)) return;
     if(!load_rom_index( 8, TMP+0x40000, 0x20000)) return;
     if(!load_rom_index(10, TMP+0x60000, 0x20000)) return;
     for(ta=0;ta<0x40000;ta+=2,tb+=8){
        DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
        DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
        DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
        DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
        DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x40000]&15) );
        DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x40001]&15) );
        DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x40000]>>4) );
        DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x40001]>>4) );
     }
   }
   else
   {
     tb=0;
     if(!load_rom_index(3, TMP, 0x80000)) return;
     for(ta=0;ta<0x80000;ta+=4,tb+=8){
        DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
        DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
        DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+1]&15) );
        DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+1]>>4) );
        DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+2]&15) );
        DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+2]>>4) );
        DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+3]&15) );
        DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+3]>>4) );
     }
     if(!load_rom_index(4, TMP, 0x80000)) return;
     for(ta=0;ta<0x80000;ta+=4,tb+=8){
        DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
        DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
        DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+1]&15) );
        DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+1]>>4) );
        DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+2]&15) );
        DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+2]>>4) );
        DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+3]&15) );
        DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+3]>>4) );
     }
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x8000);

   spr_mask = 0x1FFF;
   tile_mask = 0x7FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

}

static void load_puzznic(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=6;
   Z80BankCount=0x20000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x10+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x20000))) return;

   if(!load_rom("u11.rom",TMP,0x20000)) return;      // Z80 MAIN ROM

   TMP[0x0706]=0xC9;  // RET

   TMP[0x01B1]=0xD3;  // OUTA (AAh)
   TMP[0x01B2]=0xAA;  //

   SetStopZ80BMode2(0x01B1);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA003, lsystem_ym2203_input_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xB800, 0xB801, PuzznicMCURead,		NULL);		// MCU
   AddZ80BReadByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// HACK RAM
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA003, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xB800, 0xB801, PuzznicMCUWrite,		NULL);		// MCU
   AddZ80BWriteByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// HACK RAM
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x080000))) return;
   if(!(TMP=AllocateMem(0x040000))) return;

   if(!load_rom("u10.rom", TMP+0x00000, 0x20000)) return;
   if(!load_rom("u09.rom", TMP+0x20000, 0x20000)) return;

   tb=0;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x2000);

   spr_mask = 0x07FF;
   tile_mask = 0x1FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();
}

static void load_plgirls(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=7;
   Z80BankCount=0x40000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x10+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x40000))) return;

   if(!load_rom("pg03.ic6",TMP,0x40000)) return;      // Z80 MAIN ROM

   // TMP[0x0706]=0xC9;  // RET

   // TMP[0x01B1]=0xD3;  // OUTA (AAh)
   // TMP[0x01B2]=0xAA;  //

   // SetStopZ80BMode2(0x01B1);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA003, lsystem_ym2203_dsw_rb, NULL);          // YM2203; INPUT
   AddZ80BReadByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// HACK RAM
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA003, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// HACK RAM
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);


   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x200000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   if(!load_rom("pg02.ic9", TMP+0x00000, 0x40000)) return;
   if(!load_rom("pg01.ic7", TMP+0x40000, 0x40000)) return;

   tb=0;
   for(ta=0;ta<0x40000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x40000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x40001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x40000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x40001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x8000);

   spr_mask = 0x1FFF;
   tile_mask = 0x7FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   //tc0220ioc.RAM  = RAM_INP;
   //tc0220ioc.ctrl = 0;          //TC0220_STOPCPU;
   //reset_tc0220ioc();
}

static void load_plgirls2(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=7;
   Z80BankCount=0x40000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x10+0x10000;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x40000))) return;

   if(!load_rom("pg2_1j.ic6",TMP,0x40000)) return;      // Z80 MAIN ROM

   // TMP[0x0706]=0xC9;  // RET

   // TMP[0x01B1]=0xD3;  // OUTA (AAh)
   // TMP[0x01B2]=0xAA;  //

   // SetStopZ80BMode2(0x01B1);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA003, lsystem_ym2203_dsw_rb, NULL);          // YM2203; INPUT
   AddZ80BReadByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// HACK RAM
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA003, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xA000, 0xBFFF, NULL,			RAM+0x0A000);	// HACK RAM
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);


   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x400000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   if(!load_rom("cho-l.ic9", TMP+0x00000, 0x80000)) return;
   if(!load_rom("cho-h.ic7", TMP+0x80000, 0x80000)) return;

   tb=0;
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x80000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x80001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x80000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x80001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x8000);

   spr_mask = 0x1FFF;
   tile_mask = 0x7FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   //tc0220ioc.RAM  = RAM_INP;
   //tc0220ioc.ctrl = 0;          //TC0220_STOPCPU;
   //reset_tc0220ioc();
}

static void load_palamed(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=7;
   Z80BankCount=0x20000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x20000))) return;

   if(!load_rom("c63.02",TMP,0x20000)) return;      // Z80 MAIN ROM

   TMP[0x0120]=0xD3;  // OUTA (AAh)
   TMP[0x0121]=0xAA;  //

   SetStopZ80BMode2(0x0120);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA001, lsystem_ym2203_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xA800, 0xA807, tc0220ioc_rb_z80,		NULL);		// INPUT
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA001, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xA800, 0xA807, tc0220ioc_wb_z80,		NULL);		// INPUT
   AddZ80BWriteByte(0xB000, 0xB000, palamedes_led_write,	NULL);		// LEDS
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x080000))) return;
   if(!(TMP=AllocateMem(0x040000))) return;

   if(!load_rom("c63.04", TMP+0x00000, 0x20000)) return;
   if(!load_rom("c63.03", TMP+0x20000, 0x20000)) return;

   tb=0;
   for(ta=0;ta<0x20000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x20000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x20001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x20000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x20001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x2000);

   spr_mask = 0x07FF;
   tile_mask = 0x1FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

static void load_cubybop(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=9;
   Z80BankCount=0x40000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x40000))) return;

   if(!load_rom("cb06.6",TMP,0x40000)) return;      // Z80 MAIN ROM
/*
   TMP[0x0120]=0xD3;  // OUTA (AAh)
   TMP[0x0121]=0xAA;  //

   SetStopZ80BMode2(0x0120);
*/
   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA001, lsystem_ym2203_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xA800, 0xA807, tc0220ioc_rb_z80,		NULL);		// INPUT
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA001, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xA800, 0xA807, tc0220ioc_wb_z80,		NULL);		// INPUT
   AddZ80BWriteByte(0xB000, 0xB000, palamedes_led_write,	NULL);		// LEDS
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x200000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   if(!load_rom("cb09.9", TMP+0x000000, 0x40000)) return;
   if(!load_rom("cb10.10",TMP+0x040000, 0x40000)) return;
   if(!load_rom("cb07.7", TMP+0x080000, 0x40000)) return;
   if(!load_rom("cb08.8", TMP+0x0C0000, 0x40000)) return;

   tb=0;
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x80000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x80001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x80000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x80001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x8000);

   spr_mask = 0x1FFF;
   tile_mask = 0x7FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

static void load_tubeit(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=7;
   Z80BankCount=0x20000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x20000))) return;

   if(!load_rom("t-i_02.6",TMP,0x20000)) return;      // Z80 MAIN ROM
/*
   TMP[0x0120]=0xD3;  // OUTA (AAh)
   TMP[0x0121]=0xAA;  //

   SetStopZ80BMode2(0x0120);
*/
   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA001, lsystem_ym2203_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xA800, 0xA807, tc0220ioc_rb_z80,		NULL);		// INPUT
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0xFFF8, 0xFFF8, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA001, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xA800, 0xA807, tc0220ioc_wb_z80,		NULL);		// INPUT
   AddZ80BWriteByte(0xB000, 0xB000, palamedes_led_write,	NULL);		// LEDS
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0xFFF8, 0xFFF8, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x100000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   if(!load_rom("t-i_04.9", TMP+0x000000, 0x40000)) return;
   if(!load_rom("t-i_03.7", TMP+0x040000, 0x40000)) return;

   tb=0;
   for(ta=0;ta<0x40000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x40000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x40001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x40000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x40001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x4000);

   spr_mask = 0x0FFF;
   tile_mask = 0x3FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

// Cachat supports a region in 7fff (in a bank !), but us region has its fbi
// screen empty, and us and world look weird on the title screen, so it's
// probably better to leave the default region (japan)
static void load_cachat(void)
{
   int ta, tb;
   UINT8 *TMP;

   romset=8;
   Z80BankCount=0x20000/0x2000;
   Z802BankCount=0x00000/0x4000;

   RAMSize=0x10000+0x8000+0x10000+0x4000+0x200+0x20;

   if(!(ROM  =AllocateMem(0x8000*Z80BankCount))) return;

   if(!(RAM  =AllocateMem(RAMSize))) return;
   memset(RAM, 0x00, RAMSize);

   RAM_FG0=RAM+0x10000;
   GFX_FG0=RAM+0x10000+0x8000;
   RAM_BG0=RAM+0x10000+0x8000+0x10000;
   RAM_PAL=RAM+0x10000+0x8000+0x10000+0x4000;
   RAM_INP=RAM+0x10000+0x8000+0x10000+0x4000+0x200;

   if(!(TMP =AllocateMem(0x20000))) return;

   if(!load_rom("cac6",TMP,0x20000)) return;      // Z80 MAIN ROM

   TMP[0x0287]=0xD3;  // OUTA (AAh)
   TMP[0x0288]=0xAA;  //

   SetStopZ80BMode2(0x0289);

   init_bank_rom(TMP);

   memcpy(RAM, TMP,  0x6000+0x2000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,			NULL);		// BANK ROM
   AddZ80BReadByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BReadByte(0xC000, 0xFDFF, LSystemVRAMRead,		NULL);		// VIDEO RAM
   AddZ80BReadByte(0xA000, 0xA001, lsystem_ym2203_dsw_rb,	NULL);		// YM2203; INPUT
   AddZ80BReadByte(0xA800, 0xA807, tc0220ioc_rb_z80,		NULL);		// INPUT
   AddZ80BReadByte(0xFE00, 0xFE07, LSystemTileBankRead,		NULL);		// TILE BANK
   AddZ80BReadByte(0xFF00, 0xFF03, LSystemIntVecRead,		NULL);		// INTERRUPT
   AddZ80BReadByte(0xFF04, 0xFF07, LSystemVRAMBankRead,		NULL);		// VRAM BANK
   AddZ80BReadByte(0xFF08, 0xFF08, LSystemBankRead,		NULL);		// ROM BANK
   AddZ80BReadByte(0xFFF8, 0xFFF8, LSystemBankRead,		NULL);		// ROM BANK [MIRROR]
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0x8000, 0x9FFF, NULL,			RAM+0x08000);	// WORK RAM
   AddZ80BWriteByte(0xC000, 0xFDFF, LSystemVRAMWrite,		NULL);		// VIDEO RAM
   AddZ80BWriteByte(0xA000, 0xA001, lsystem_ym2203_wb,		NULL);		// YM2203; INPUT
   AddZ80BWriteByte(0xA800, 0xA807, tc0220ioc_wb_z80,		NULL);		// INPUT
   AddZ80BWriteByte(0xB000, 0xB000, palamedes_led_write,	NULL);		// LEDS
   AddZ80BWriteByte(0xFE00, 0xFE07, LSystemTileBankWrite,	NULL);		// TILE BANK
   AddZ80BWriteByte(0xFF00, 0xFF03, LSystemIntVecWrite,		NULL);		// INTERRUPT
   AddZ80BWriteByte(0xFF04, 0xFF07, LSystemVRAMBankWrite,	NULL);		// VRAM BANK
   AddZ80BWriteByte(0xFF08, 0xFF08, LSystemNewBankWrite,	NULL);		// ROM BANK
   AddZ80BWriteByte(0xFFF8, 0xFFF8, LSystemNewBankWrite,	NULL);		// ROM BANK [MIRROR]
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(GFX=AllocateMem(0x100000))) return;
   if(!(TMP=AllocateMem(0x080000))) return;

   if(!load_rom("cac9", TMP+0x00000, 0x20000)) return;
   if(!load_rom("cac10",TMP+0x20000, 0x20000)) return;
   if(!load_rom("cac7", TMP+0x40000, 0x20000)) return;
   if(!load_rom("cac8", TMP+0x60000, 0x20000)) return;

   tb=0;
   for(ta=0;ta<0x40000;ta+=2,tb+=8){
      DrawNibble0(&GFX[tb+0],0, (UINT8) (TMP[ta+0]&15) );
      DrawNibble0(&GFX[tb+4],0, (UINT8) (TMP[ta+1]&15) );
      DrawNibble(&GFX[tb+0], 1, (UINT8) (TMP[ta+0]>>4) );
      DrawNibble(&GFX[tb+4], 1, (UINT8) (TMP[ta+1]>>4) );
      DrawNibble(&GFX[tb+0], 2, (UINT8) (TMP[ta+0x40000]&15) );
      DrawNibble(&GFX[tb+4], 2, (UINT8) (TMP[ta+0x40001]&15) );
      DrawNibble(&GFX[tb+0], 3, (UINT8) (TMP[ta+0x40000]>>4) );
      DrawNibble(&GFX[tb+4], 3, (UINT8) (TMP[ta+0x40001]>>4) );
   }

   FreeMem(TMP);

   GFX_BG0 = GFX+0x000000;
   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x4000);

   spr_mask = 0x0FFF;
   tile_mask = 0x3FFF;

   lsystem_vcu_init(1);

   LSystemAddSaveData();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INP;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
}

static void DrawLSystem(void)
{
   int w,x,y,code,ta;
   int zz,zzz,zzzz,x16,y16;
   UINT8 *p,colour,*map;
   UINT8 *GFX_BG,*MSK_BG;
   if (!GFX_BG0_SOLID) {
     GFX_BG0_SOLID = gfx_solid[0];
     if (!GFX_BG0) {
       GFX_BG0 = gfx[0];
     }
   }

   ClearPaletteMap();

   GFX_BG = GFX_BG0;
   MSK_BG = GFX_BG0_SOLID;

   // American Horseshoes has an extra gfx bank switch

   if(romset==1){
   GFX_BG = GFX_BG0 + (ah_gfx_bank*0x1000*0x40);
   MSK_BG = GFX_BG0_SOLID + (ah_gfx_bank*0x1000);
   }

   // BG0
   // ---

   if(check_layer_enabled(layer_id_data[0])) {
       MAKE_SCROLL_512x256_2_8(
	       0-(ReadWord(&RAM_BG0[0x33FC])+28+10),
	       16-(ReadWord(&RAM_BG0[0x33FE]))
	       );

       START_SCROLL_512x256_2_8(32,32,320,224);

       code = ReadWord(&RAM_BG0[0x1000+zz]);
       ta   = ((code&0x3FF)|(TileBank[(code>>10)&3]<<10))&tile_mask;
       colour = (UINT8) ((code>>8)&0xF0)>>4;
       MAP_PALETTE_MAPPED_NEW(colour,
	       16,
	       map);

       Draw8x8_Mapped_Rot(&GFX_BG[ta<<6], x, y, map);

       END_SCROLL_512x256_2_8();
   } else
       clear_game_screen(0);

   // OBJECT
   // ------

   if(check_layer_enabled(layer_id_data[1])) {
       if((TileBank[4]&0x08)==0){

	   p = &RAM_BG0[0x33F0];
	   w = 0x7E;
	   do {
	       p -= 8;
	       code = ReadWord(p) & spr_mask;

	       if(code!=0){
		   if((colour = ((*(p+2)) & 15))>=8){

		       x = (ReadWord(p+4)+32)&0x1FF;
		       y = (ReadWord(p+6)+16)&0xFF;

		       if((x>16)&&(y>16)&&(x<320+32)&&(y<224+32)){

			   code <<= 8;
			   MAP_PAL(colour,
				   16,
				   map);

			   switch((*(p+3)) & 3){
			   case 0x00:
			       Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0x00], x,   y,   map);
			       Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0x40], x+8, y,   map);
			       Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0x80], x,   y+8, map);
			       Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0xC0], x+8, y+8, map);
			       break;
			   case 0x01:
			       Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0x00], x+8, y,   map);
			       Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0x40], x,   y,   map);
			       Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0x80], x+8, y+8, map);
			       Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0xC0], x,   y+8, map);
			       break;
			   case 0x02:
			       Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0x00], x,   y+8, map);
			       Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0x40], x+8, y+8, map);
			       Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0x80], x,   y,   map);
			       Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0xC0], x+8, y,   map);
			       break;
			   case 0x03:
			       Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0x00], x+8, y+8, map);
			       Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0x40], x,   y+8, map);
			       Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0x80], x+8, y,   map);
			       Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0xC0], x,   y,   map);
			       break;
			   }
		       }
		   }}
	   } while(--w);
       }
   }

   // BG1
   // ---

   if(check_layer_enabled(layer_id_data[2])) {
       MAKE_SCROLL_512x256_2_8(
	       0-(ReadWord(&RAM_BG0[0x33F4])+28),
	       16-(ReadWord(&RAM_BG0[0x33F6]))
	       );

       START_SCROLL_512x256_2_8(32,32,320,224);

       code = ReadWord(&RAM_BG0[0x0000+zz]);
       ta   = ((code&0x3FF)|(TileBank[(code>>10)&3]<<10))&tile_mask;
       colour = (UINT8) ((code>>8)&0xF0)>>4;
       MAP_PAL(colour,
	       16,
	       map);

       if(MSK_BG[ta]!=0){			// No pixels; skip

	   if(MSK_BG[ta]==1){			// Some pixels; trans
	       Draw8x8_Trans_Mapped_Rot(&GFX_BG[ta<<6], x, y, map);
	   }
	   else{					// all pixels; solid
	       Draw8x8_Mapped_Rot(&GFX_BG[ta<<6], x, y, map);
	   }

       }

       END_SCROLL_512x256_2_8();
   }

   // OBJECT
   // ------

   if(check_layer_enabled(layer_id_data[3])) {
       if((TileBank[4]&0x08)==0){
	   ta = 8;
       }
       else{
	   ta = 16;
       }

       p = &RAM_BG0[0x33F0];
       w = 0x7E;
       do {
	   p -= 8;
	   code = ReadWord(p) & spr_mask;

	   if(code!=0){
	       if((colour = ((*(p+2)) & 15))<ta){
		   x = (ReadWord(p+4)+32)&0x1FF;
		   y = (ReadWord(p+6)+16)&0x0FF;

		   if((x>16)&&(y>16)&&(x<320+32)&&(y<224+32)){

		       MAP_PAL(colour,
			       16,
			       map);
		       code <<= 8;

		       switch((*(p+3)) & 3){
		       case 0x00:
			   Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0x00], x,   y,   map);
			   Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0x40], x+8, y,   map);
			   Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0x80], x,   y+8, map);
			   Draw8x8_Trans_Mapped_Rot(&GFX_BG[code+0xC0], x+8, y+8, map);
			   break;
		       case 0x01:
			   Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0x00], x+8, y,   map);
			   Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0x40], x,   y,   map);
			   Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0x80], x+8, y+8, map);
			   Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG[code+0xC0], x,   y+8, map);
			   break;
		       case 0x02:
			   Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0x00], x,   y+8, map);
			   Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0x40], x+8, y+8, map);
			   Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0x80], x,   y,   map);
			   Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG[code+0xC0], x+8, y,   map);
			   break;
		       case 0x03:
			   Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0x00], x+8, y+8, map);
			   Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0x40], x,   y+8, map);
			   Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0x80], x+8, y,   map);
			   Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG[code+0xC0], x,   y,   map);
			   break;
		       }
		   }
	       }}
       } while(--w);
   }

   // FG0
   // ---

   if(check_layer_enabled(layer_id_data[4])) {
       update_gfx_fg0();

       MAKE_SCROLL_512x256_2_8(
	       8,
	       16
	       );

       START_SCROLL_512x256_2_8(32,32,320,224);

       code = ReadWord(&RAM_BG0[0x2000+zz]);
       ta = (code&0x1FF)|((code&0x400)>>1);
       MAP_PAL((UINT8) ((code>>8)&0xF0)>>4,
	       16,
	       map);

       if(GFX_FG0_SOLID[ta]){			// No pixels; skip

	   if(GFX_FG0_SOLID[ta]==1){		// Some pixels; trans
	       Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);
	   }
	   else{					// all pixels; solid
	       Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);
	   }

       }

       END_SCROLL_512x256_2_8();
   }
}

static struct VIDEO_INFO video_champwr =
{
   DrawLSystem,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   gfxdecodeinfo2
};
static struct VIDEO_INFO video_fhawk =
{
   DrawLSystem,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
};
static struct VIDEO_INFO video_kurikint =
{
   DrawLSystem,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   gfxdecodeinfo
};
static struct DIR_INFO dir_horshoes[] =
{
   { "american_horseshoes", },
   { "amhorse", },
   { "horshoes", },
   { NULL, },
};
GAME( horshoes, "American Horseshoes", TAITO, 1990, GAME_SPORTS | GAME_NOT_WORKING,
	.input = input_horshoes,
	.dsw = dsw_horshoes,
	.video = &video_fhawk,
	.long_name_jpn = "アメリカンホースシュー",
	.board = "C47",
);
static struct DIR_INFO dir_cachat[] =
{
   { "cachat", },
   { NULL, },
};
GAME( cachat, "Cachat", TAITO, 1993, GAME_PUZZLE,
	.input = input_cachat,
	.dsw = dsw_cachat,
);
static struct DIR_INFO dir_champwr[] =
{
   { "champion_wrestler", },
   { "champwr", },
   { NULL, },
};
GME( champwr, "Champion Wrestler", TAITO, 1989, GAME_SPORTS,
	.romsw = romsw_champwr,
	.video = &video_champwr,
	.long_name_jpn = "チャンピオンレスラー",
	.board = "C01",
);
static struct DIR_INFO dir_champwrj[] =
{
   { "champion_wrestler_jp", },
   { "champwrj", },
   { ROMOF("champwr"), },
   { CLONEOF("champwr"), },
   { NULL, },
};
CLNE( champwrj, champwr, "Champion Wrestler (Japan)", TAITO, 1989, GAME_SPORTS,
	.dsw = dsw_champwrj,
	.video = &video_champwr,
	.long_name_jpn = "秡粐糜龝礫糜粽禮粱�[ (Japan)",
	.board = "C01",
);
static struct DIR_INFO dir_champwru[] =
{
   { "champion_wrestler_us", },
   { "champwru", },
   { ROMOF("champwr"), },
   { CLONEOF("champwr"), },
   { NULL, },
};
CLNE( champwru, champwr, "Champion Wrestler (US)", TAITO, 1989, GAME_SPORTS,
	.dsw = dsw_champwru,
	.video = &video_champwr,
	.long_name_jpn = "秡粐糜龝礫糜粽禮粱�[ (US)",
	.board = "C01",
);
static struct DIR_INFO dir_cubybop[] =
{
   { "cuby_bop", },
   { "cubybop", },
   { NULL, },
};
GAME( cubybop, "Cuby Bop", TAITO, 1990, GAME_PUZZLE,
	.input = input_cubybop,
	.dsw = dsw_cubybop,
);
static struct DIR_INFO dir_fhawk[] =
{
   { "fighting_hawk", },
   { "fhawk", },
   { "fhawkj", },
   { NULL, },
};
GAME( fhawk, "Fighting Hawk", TAITO, 1988, GAME_SHOOT,
	.input = input_fhawk,
	.dsw = dsw_fhawk,
	.romsw = romsw_fhawk,
	.video = &video_fhawk,
	.long_name_jpn = "ファイティングホーク",
	.board = "B70",
);
static struct DIR_INFO dir_kurikina[] =
{
   { "kuri_kinton_alt", },
   { "kurikina", },
   { ROMOF("kurikint"), },
   { CLONEOF("kurikint"), },
   { NULL, },
};
CLNE( kurikina,kurikint, "Kuri Kinton (Alternate)", TAITO, 1988, GAME_BEAT,
	.dsw = dsw_kurikina,
	.romsw = romsw_kurikint,
	.long_name_jpn = "公李金団 (Alternate)",
	.board = "B42",
);
static struct DIR_INFO dir_kurikint[] =
{
   { "kuri_kinton", },
   { "kurikint", },
   { NULL, },
};
GME( kurikint, "Kuri Kinton", TAITO, 1988, GAME_BEAT,
	.romsw = romsw_kurikint,
	.long_name_jpn = "公李金団",
	.board = "B42",
);
static struct DIR_INFO dir_kurikinj[] =
{
   { "kuri_kinton_jap", },
   { "kurikinj", },
   { "kurikina", },
   { ROMOF("kurikint"), },
   { CLONEOF("kurikint"), },
   { NULL, },
};
CLNE( kurikinj,kurikint, "Kuri Kinton (JPN Ver.)", TAITO, 1988, GAME_BEAT,
	.long_name_jpn = "公李金団 (alternate)",
	.romsw = romsw_kurikint,
	.board = "B42",
);
static struct DIR_INFO dir_palamed[] =
{
   { "palamedes", },
   { "palamed", },
   { NULL, },
};
GAME( palamed, "Palamedes", TAITO, 1990, GAME_PUZZLE,
	.input = input_palamed,
	.dsw = dsw_palamed,
	.romsw = romsw_palamed,
	.long_name_jpn = "パラメデス",
	.board = "C63",
);
static struct DIR_INFO dir_plgirls[] =
{
   { "plgirls", },
   { NULL, },
};
GAME( plgirls, "Play Girls", HOT_B, 1992, GAME_BREAKOUT | GAME_ADULT,
	.input = input_plgirls,
	.dsw = dsw_plgirls,
	.video = &video_fhawk,
	.long_name_jpn = "Play Girls",
	.board = "???",
);
static struct DIR_INFO dir_plgirls2[] =
{
   { "plgirls2", },
   { NULL, },
};
GAME( plgirls2, "Play Girls 2", HOT_B, 1993, GAME_SHOOT | GAME_ADULT,
	.input = input_plgirls2,
	.dsw = dsw_plgirls2,
	.video = &video_fhawk,
);
static struct DIR_INFO dir_puzznic[] =
{
   { "puzznic", },
   { "puzznicj", },
   { NULL, },
};
GAME( puzznic, "Puzznic", TAITO, 1989, GAME_PUZZLE | GAME_ADULT,
	.input = input_puzznic,
	.dsw = dsw_puzznic,
	.romsw = romsw_puzznic,
	.long_name_jpn = "パズニック",
	.board = "C20",
);
static struct DIR_INFO dir_raimais[] =
{
   { "raimais", },
   { "raimaisj", },
   { NULL, },
};
GAME( raimais, "Raimais", TAITO, 1988, GAME_MISC,
	.input = input_raimais,
	.dsw = dsw_raimais,
	.long_name_jpn = "レイメイズ",
	.board = "B36",
	.sound = taito_ym2610_sound,
);
static struct DIR_INFO dir_tubeit[] =
{
   { "tube_it", },
   { "tubeit", },
   { ROMOF("cachat"), },
   { CLONEOF("cachat"), },
   { NULL, },
};
GAME( tubeit, "Tube It", TAITO, 1990, GAME_PUZZLE,
	.input = input_cachat,
	.dsw = dsw_cachat,
);

GMEI( plotting ,"Plotting",TAITO,1989,GAME_PUZZLE,
	.romsw = plotting_romsw);
CLNEI( plottinga,plotting,"Plotting (World set 2, protected)",TAITO,1989,GAME_PUZZLE,
	.romsw = plotting_romsw);
CLNEI( plottingb,plotting,"Plotting (World set 3, earliest version)",TAITO,1989,GAME_PUZZLE,
	.romsw = plotting_romsw);
