/*
  Raine notes :

  The bank switch for the z80 is particularly stupid : it's a bank of 0x8000 bytes
  but it changes by increments of 0x4000 bytes only !!! Since it's the first bank I see
  with a size > 0x4000 bytes, I made a hack in mz80help.c to always have a maximum size
  of 0x4000 bytes. (and it's really a rom bank apparently, not a data bank).

  priorities now use the priority bitmap because they don't apply between sprites (only
  between tiles or between a sprite and a tile). So the old priority queue becomes useless

*/

// Here are the comments from mame :

/******************************************************************************

  'Face' LINDA board
 driver by Paul Priest + David Haywood

*******************************************************************************

 Games on this Hardware

 Magical Cat Adventure (c)1993 Wintechno
 Nostradamus (c)1993 Face

*******************************************************************************

 Hardware Overview:

 Board Name : LINDA5 (Magical Cat) / LINDA25 (Nostradamus)

 Main CPU: 68000-16
 Sound CPU: Z80
 Sound Chip: YMF286-K

 Custom: FACE FX1037 x1
         038 x2 (As in Cave)

*******************************************************************************

Stephh's notes (based on the games M68000 code and some tests) :

1) "mcatadv*'

  - Player 1 Button 3 is only used in the "test" mode :
      * to select "OBJECT ROM CHECK"
      * in "BG ROM", to change the background number

  - Do NOT trust the "NORMAL TESTMODE" for the system inputs !

  - The Japan version has extra GFX/anims and it's harder than the other set.

2) 'nost*'

  - When entering the "test mode", you need to press SERVICE1 to cycle through
    the different screens.

*******************************************************************************

 todo:

 Flip Screen

*******************************************************************************

 trivia:

 Magical Cat Adventure tests for 'MASICAL CAT ADVENTURE' in RAM on start-up
 and will write it there if not found, expecting a reset, great engrish ;-)

******************************************************************************/

#include "gameinc.h"
#include "2610intf.h"
#include "sasound.h"
#include "timer.h"
#include "blit.h"
#include "emumain.h" // reset_game_hardware
#include "pdraw.h"
#include "priorities.h"

static struct ROM_INFO rom_mcatadv[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "mca-u30e",  0xc62fbb65, "mca-u29e",  0xcf21227c),
  { "u9.bin", 0x20000, 0xfda05171, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "u9.bin", 0x20000, 0xfda05171, REGION_ROM2, 0x04000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x100000,
            "mca-u82.bin",  0x5f01d746, "mca-u83.bin",  0x4e1be5a6),
  LOAD8_16(  REGION_GFX1,  0x200000,  0x080000,
            "mca-u84.bin",  0xdf202790, "mca-u85.bin",  0xa85771d2),
  LOAD8_16(  REGION_GFX1,  0x400000,  0x080000,
            "mca-u86e",  0x017bf1da, "mca-u87e",  0xbc9dc9b9),
  { "mca-u58.bin", 0x080000, 0x3a8186e2, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "mca-u60.bin", 0x100000, 0xc8942614, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "mca-u61.bin", 0x100000, 0x51af66c9, REGION_GFX3, 0x100000, LOAD_NORMAL },
  { "mca-u100", 0x080000, 0xb273f1b0, REGION_GFX3, 0x200000, LOAD_NORMAL },
  { "mca-u53.bin", 0x80000, 0x64c76e05, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mcatadvj[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "u30.bin",  0x05762f42, "u29.bin",  0x4c59d648),
  LOAD8_16(  REGION_GFX1,  0x000000,  0x100000,
            "mca-u82.bin",  0x5f01d746, "mca-u83.bin",  0x4e1be5a6),
  LOAD8_16(  REGION_GFX1,  0x200000,  0x080000,
            "mca-u84.bin",  0xdf202790, "mca-u85.bin",  0xa85771d2),
  LOAD8_16(  REGION_GFX1,  0x400000,  0x080000,
            "u86.bin",  0x2d3725ed, "u87.bin",  0x4ddefe08),
  { "mca-u60.bin", 0x100000, 0xc8942614, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "mca-u61.bin", 0x100000, 0x51af66c9, REGION_GFX3, 0x100000, LOAD_NORMAL },
  { "u100.bin", 0x080000, 0xe2c311da, REGION_GFX3, 0x200000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_nost[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "nos-pe-u.bin",  0x4b080149, "nos-po-u.bin",  0x9e3cd6d9),
  { "nos-ps.u9", 0x40000, 0x832551e9, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "nos-ps.u9", 0x40000, 0x832551e9, REGION_ROM2, 0x08000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x100000,
            "nos-se-0.u82",  0x9d99108d, "nos-so-0.u83",  0x7df0fc7e),
  LOAD8_16(  REGION_GFX1,  0x200000,  0x100000,
            "nos-se-1.u84",  0xaad07607, "nos-so-1.u85",  0x83d0012c),
  LOAD8_16(  REGION_GFX1,  0x400000,  0x080000,
            "nos-se-2.u86",  0xd99e6005, "nos-so-2.u87",  0xf60e8ef3),
  { "nos-b0-0.u58", 0x100000, 0x0214b0f2, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "nos-b0-1.u59", 0x080000, 0x3f8b6b34, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "nos-b1-0.u60", 0x100000, 0xba6fd0c7, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "nos-b1-1.u61", 0x080000, 0xdabd8009, REGION_GFX3, 0x100000, LOAD_NORMAL },
  { "nossn-00.u53", 0x100000, 0x3bd1bcbc, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_mcatadv[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( P1_DOWN, 0x00, 0x02 ),
  INP0( P1_LEFT, 0x00, 0x04 ),
  INP0( P1_RIGHT, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),
  INP0( P1_B3, 0x00, 0x40 ),
  INP0( P1_START, 0x00, 0x80 ),
  INP0( COIN1, 0x01, 0x01 ),

  INP0( P2_UP, 0x02, 0x01 ),
  INP0( P2_DOWN, 0x02, 0x02 ),
  INP0( P2_LEFT, 0x02, 0x04 ),
  INP0( P2_RIGHT, 0x02, 0x08 ),
  INP0( P2_B1, 0x02, 0x10 ),
  INP0( P2_B2, 0x02, 0x20 ),
  INP0( P2_START, 0x02, 0x80 ),
  INP0( COIN2, 0x03, 0x01 ),
  INP0( SERVICE, 0x03, 0x02 ),
   END_INPUT
};

static struct DSW_DATA dsw_data_mcatadv_2[] =
{
  DSW_DEMO_SOUND( 0x01, 0x00),
  DSW_SCREEN( 0x02, 0x00),
  DSW_SERVICE( 0, 0x04),
  { _("Coin Mode"), 0x08, 2 },
  { _("Mode 1") , 0x08},
  { _("Mode 2") , 0x00},
  { MSG_COIN1, 0x30, 4 },
  { MSG_2COIN_1PLAY, 0x10},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_2COIN_3PLAY, 0x00},
  { MSG_1COIN_1PLAY, 0x20},
  { MSG_COIN2, 0xc0, 4 },
  { MSG_2COIN_1PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0xc0},
  { MSG_2COIN_3PLAY, 0x00},
  { MSG_1COIN_1PLAY, 0x80},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_mcatadv_3[] =
{
  { MSG_DIFFICULTY, 0x03, 4 },
  { _("Easy") , 0x02},
  { _("Normal") , 0x03},
  { _("Hard") , 0x01},
  { _("Hardest") , 0x00},
  { MSG_LIVES, 0x0c, 4 },
  { "2" , 0x04},
  { "3" , 0x0c},
  { "4" , 0x08},
  { "5" , 0x00},
  { _("Energy"), 0x30, 4 },
  { "3" , 0x30},
  { "4" , 0x20},
  { "5" , 0x10},
  { "8" , 0x00},
  { MSG_CABINET, 0xc0, 3 },
  { _("Upright 1 Player") , 0x40},
  { _("Upright 2 Players") , 0xc0},
  { MSG_TABLE, 0x80},
  { NULL, 0}
};

static struct DSW_INFO dsw_mcatadv[] =
{
  { 0x5, 0xff, dsw_data_mcatadv_2 },
  { 0x7, 0xff, dsw_data_mcatadv_3 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_nost_2[] =
{
  { MSG_LIVES, 0x03, 4 },
  { "2", 0x02},
  { "3", 0x03},
  { "4", 0x01},
  { "5", 0x00},
  { MSG_DIFFICULTY, 0x0c, 4 },
  { MSG_EASY, 0x08},
  { MSG_NORMAL, 0x0c},
  { MSG_HARD, 0x04},
  { MSG_HARDEST, 0x00},
  DSW_SCREEN( 0x10, 0x00),
  DSW_DEMO_SOUND( 0x20, 0x00),
  { MSG_EXTRA_LIFE, 0xc0, 4 },
  { _("500k 1000k"), 0x80},
  { _("800k 1500k"), 0xc0},
  { _("1000k 2000k"), 0x40},
  { MSG_UNKNOWN, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_nost_3[] =
{
  { MSG_COIN1, 0x07, 8 },
  { MSG_3COIN_1PLAY, 0x02},
  { MSG_2COIN_1PLAY, 0x04},
  { MSG_3COIN_2PLAY, 0x01},
  { MSG_1COIN_1PLAY, 0x07},
  { MSG_2COIN_3PLAY, 0x03},
  { MSG_1COIN_1PLAY, 0x06},
  { MSG_1COIN_3PLAY, 0x05},
  { MSG_FREE_PLAY, 0x00},
  { MSG_COIN2, 0x38, 8 },
  { MSG_4COIN_1PLAY, 0x00},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x20},
  { MSG_3COIN_2PLAY, 0x08},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_2COIN_3PLAY, 0x18},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_1COIN_3PLAY, 0x28},
  DSW_UNUSED( 0x00, 0x40),
  DSW_SERVICE( 0, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_nost[] =
{
  { 0x5, 0xff, dsw_data_nost_2 },
  { 0x7, 0xff, dsw_data_nost_3 },
  { 0, 0, NULL }
};

static void  mcat_soundlatch_w (UINT32 offset, UINT16 data) {
  latch = data;
  cpu_int_nmi(CPU_Z80_0);
  ExitOnEI=1;
  cpu_execute_cycles(CPU_Z80_0, 1000);
}

static UINT16  mcat_wd_r (UINT32 offset) {
  // watchdog_reset_r(0);
  return 0xc00;
}

static GfxLayout mcatadv_tiles16x16x4_layout =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ STEP4(0,1) },
	{ STEP8(0,4), STEP8(32*8,4) },
	{ STEP8(0,32), STEP8(64*8,32) },
	128*8
};

static struct GFX_LIST mcatadv_gfxdecodeinfo[] =
{
 	{ REGION_GFX2, &mcatadv_tiles16x16x4_layout }, // 0x200 color banks
 	{ REGION_GFX3, &mcatadv_tiles16x16x4_layout }, // 0x200 color banks
	{ 0, NULL }
};

static struct YM2610interface mcatadv_ym2610_interface =
{
	1,
	16000000/2,	/* ? */
	{ (180 | (OSD_PAN_CENTER<<8) ) },
	{ 0 },	/* A_r */
	{ 0 },	/* B_r */
	{ 0 },	/* A_w */
	{ 0 },	/* B_w */
	{ z80_irq_handler },	/* irq */
	{ REGION_SOUND1 },	/* delta_t */
	{ REGION_SOUND1 },	/* adpcm */
	{ YM3012_VOL(220,MIXER_PAN_LEFT,220,MIXER_PAN_RIGHT) }
};

struct SOUND_INFO sound_mcatadv[] =
  {
    { SOUND_YM2610, &mcatadv_ym2610_interface },
    { 0,             NULL,               },
  };

static UINT8 *scroll0, *scroll1, *ram_bg0, *ram_bg1, *ram_pal, *ram_spr, *video_regs,
  *ram_z80,*soundlatch2,*gfx_obj_solid,*gfx_obj_a,*gfx_obj_b,
  *gfx_obj_size;
static UINT32 sprite_size;

static int tile_max0, tile_max1;
static int layer_id_data[3];
static UINT16 *spriteram_old;
static UINT16 *vidregs_old;

#define spriteram_size 0x8000

static void write_soundlatch2(UINT32 offset, UINT8 data) {
  *soundlatch2 = data;
}

#define FRAME_Z80 CPU_FRAME_MHz(4,60)

static void mcatadv_setbank(UINT32 offset, UINT8 data)
{
  z80a_set_bank(0,data);
}

#ifdef RAINE_DEBUG
static void watchdog_reset16_w(UINT32 offset, UINT16 data) {
}
#endif

static int hack_applied,hack_adr,frame_68k;
static UINT8 hack_buffer[7];

static void undo_hack() {
  if (hack_applied) {
    memcpy(&ROM[hack_adr],hack_buffer,6);
    hack_applied = 0;
    frame_68k = CPU_FRAME_MHz(16,60);
  }
}

static void load_mcatadv() {
  RAMSize = 0x2901d; // 2721e
  hack_applied = 0;
  frame_68k = CPU_FRAME_MHz(16,60);
  set_reset_function(undo_hack);
  if(!(RAM=AllocateMem(RAMSize+0x10000)))     return;
  if(!(spriteram_old=(UINT16*)AllocateMem(spriteram_size)))     return;
  if (!(vidregs_old = (UINT16*)AllocateMem(16))) return;
  init_pbitmap();

  memset(spriteram_old,0,spriteram_size);
  memset(RAM,0,RAMSize);

  tile_max0 = 0;

  unpack_region_lsb(REGION_GFX1);
  gfx_obj_a = load_region[REGION_GFX1];

  // See the explanation of the copy of the sprites in draw_sprites
  // basically it's to be able to draw "sprites tiles"
  if (!(gfx_obj_b = AllocateMem(get_region_size(REGION_GFX1)))) return;
  sprite_size = get_region_size(REGION_GFX1)/0x100;
  if(!(gfx_obj_size=AllocateMem(sprite_size))) return;
  memset(gfx_obj_size,0x01,sprite_size);
  memcpy(gfx_obj_b,gfx_obj_a,sprite_size*0x100);
  gfx_obj_solid = make_solid_mask_16x16(gfx_obj_b, sprite_size);

  ByteSwap(ROM,get_region_size(REGION_ROM1));

  AddMemFetch(0x000000,0x0fffff,ROM);
  AddMemFetch(-1, -1, NULL);

  AddReadBW( 0x000000, 0x0fffff, NULL, ROM);
  AddRWBW(   0x100000, 0x10ffff, NULL, RAM);

  scroll0 = RAM + 0x10000;
  scroll1 = scroll0 + 6;

  AddRWBW(   0x200000, 0x200005, NULL, scroll0);
  AddRWBW(   0x300000, 0x300005, NULL, scroll1);

  ram_bg0 = scroll1 + 6;
  ram_bg1 = ram_bg0 + 0x2000;

  AddRWBW(   0x400000, 0x401fff, NULL, ram_bg0);
  AddRWBW(   0x500000, 0x501fff, NULL, ram_bg1);

  ram_pal = ram_bg1 + 0x2000;

  AddRWBW(   0x600000, 0x602fff, NULL, ram_pal);

  InitPaletteMap(ram_pal, 0x100, 16, 0x8000);
  set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

  ram_spr = ram_pal + 0x3000;

  AddRWBW(   0x700000, 0x70ffff, NULL, ram_spr);

  video_regs = ram_spr + 0x10000;

  memset(input_buffer,0,4); // for nost startup, tests bit11 of 800000
  AddRWBW(0x800000, 0x800003, NULL, input_buffer); // inputs
  AddRWBW(0xa00000, 0xa00003, NULL, input_buffer + 4); // dsw

  AddRWBW(   0xb00000, 0xb0000f, NULL, video_regs);
  AddReadBW(  0xb0001e, 0xb0001f, mcat_wd_r, NULL);
#ifdef RAINE_DEBUG
  AddWriteBW(0xb00018, 0xb00019, watchdog_reset16_w,NULL); /* NOST Only */
#endif
  AddWriteBW( 0xc00000, 0xc00001, mcat_soundlatch_w, NULL);

  AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000

  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
  ram_z80 = video_regs + 0x10;

  z80_init_banks(0,REGION_ROM2,0x4000,0x8000);
  // z80_init_data_banks(0,REGION_ROM2,0,0x4000);
  // AddZ80ARead( 0x0000, 0x3fff, NULL, Z80ROM);
  AddZ80ARead( 0x0000, 0xbfff, NULL, NULL); // rom + bank
  AddZ80ARead( 0xc000, 0xdfff, NULL, ram_z80);
  AddZ80AWrite(0xc000, 0xdfff, NULL, ram_z80);

  if (!is_current_game("nost")) {
    AddZ80ARead( 0xe000, 0xe000, YM2610_status_port_0_A_r, NULL);
    AddZ80ARead( 0xe002, 0xe002, YM2610_status_port_0_B_r, NULL);
  }
  AddZ80ARead( 0x0000, 0xFFFF, DefBadReadZ80,		NULL);

  if (!is_current_game("nost")) {
    AddZ80AWrite(0xe000, 0xe000, YM2610_control_port_0_A_w, NULL);
    AddZ80AWrite(0xe001, 0xe001, YM2610_data_port_0_A_w, NULL);
    AddZ80AWrite(0xe002, 0xe002, YM2610_control_port_0_B_w, NULL);
    AddZ80AWrite(0xe003, 0xe003, YM2610_data_port_0_B_w, NULL);
    AddZ80AWrite(0xf000, 0xf000, mcatadv_setbank, NULL);
  }
  AddZ80AWrite(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);

  soundlatch2 = ram_z80 + 0x2000;

  AddZ80AReadPort(0x80, 0x80, soundlatch_lo_r, NULL);
  AddZ80AWritePort(0x80, 0x80, write_soundlatch2, NULL);

  // specific to nost
  if (is_current_game("nost")) {
    AddZ80AReadPort(0x04, 0x05, YM2610_status_port_0_A_r, NULL);
    AddZ80AReadPort(0x06, 0x07, YM2610_status_port_0_B_r, NULL);

    AddZ80AWritePort(0x00, 0x00, YM2610_control_port_0_A_w, NULL);
    AddZ80AWritePort(0x01, 0x01, YM2610_data_port_0_A_w, NULL);
    AddZ80AWritePort(0x02, 0x02, YM2610_control_port_0_B_w, NULL);
    AddZ80AWritePort(0x03, 0x03, YM2610_data_port_0_B_w, NULL);
    AddZ80AWritePort(0x40, 0x40, mcatadv_setbank, NULL);
  }

  AddZ80AReadPort(0, 0xff, DefBadReadPort, NULL);
  AddZ80AWritePort(0, 0xff, DefBadWritePort, NULL);

  AddReadBW(  0xc00000, 0xc00001, NULL, soundlatch2);
  //  z80a_set_bank(0,0);
  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);      // <Bad Reads>
  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);      // <Bad Reads>
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);    // <Bad Writes>
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);    // <Bad Writes>
  AddRWBW(-1, -1, NULL, NULL);
  AddZ80AReadPort(-1, -1, NULL, NULL);
  AddZ80AWritePort(-1, -1, NULL, NULL);

  AddZ80AInit();
  AddInitMemory();   // Set Starscream mem pointers...
  layer_id_data[0] = add_layer_info(gettext("BG0"));
  layer_id_data[1] = add_layer_info(gettext("BG1"));
  layer_id_data[2] = add_layer_info(gettext("OBJ"));

  setup_z80_frame(CPU_Z80_0,FRAME_Z80);
}

static void draw_tile(UINT8 *RAM_BG, UINT8 *scroll,int tile_max, int pal_base, UINT8 *GFX, UINT8 *GFX_SOLID) {
  int zzz,zzzz,x16,y16,zz,x,y,ta;
  UINT8 pri;

    UINT8 *MAP;

    MAKE_SCROLL_512x512_4_16(
      (ReadWord(&scroll[0])&0x1ff)-0x194,
      (ReadWord(&scroll[2])&0x1ff)-0x1df
      );

    START_SCROLL_512x512_4_16(16,16,320,224);

    ta=(ReadWord(&RAM_BG[2+zz]));

    if( ta && ta <= tile_max) {
      pri = RAM_BG[zz+1];

      MAP_PALETTE_MAPPED_NEW(
			     (pri&0x3F) | (pal_base),
			     16,
			     MAP
			     );

      pri = (pri>>6)+1; /* | i */;

      // QueueTile(ta, x,   y,   MAP, 0, pri);
      if(GFX_SOLID[ta]!=0){                      // No pixels; skip
	if((x > 0) && (x < 320+16) && (y > 0) && (y < 224+16)){
	  if(GFX_SOLID[ta]==1) {                   // Some pixels; trans
	    pdraw16x16_Mask_Trans_Mapped_Rot(&GFX[ta<<8],x,y,MAP,pri);
/* 	    Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8],x,y,map); */
/* 	    Draw16x16_Mask_Trans_Rot(&GFX[ta<<8],x,y,my_pri); */
	  } else {                                        // all pixels; solid
	    pdraw16x16_Mask_Mapped_Rot(&GFX[ta<<8],x,y,MAP,pri);
/* 	    Draw16x16_Mapped_Rot(&GFX[ta<<8],x,y,map); */
/* 	    Draw16x16_Mask_Rot(&GFX[ta<<8],x,y,my_pri); */
	  }
	}
      }

    }

    END_SCROLL_512x512_4_16();
}

static void draw_sprites() {
  UINT16 *source = spriteram_old;
  UINT16 *finish = source + (spriteram_size/2)/2;
  int global_x = ReadWord(&video_regs[0])-0x184-16;
  int global_y = ReadWord(&video_regs[1*2])-0x1f1-16;

    /* Also double buffered because working on the old sprite ram */
    if( vidregs_old[2] == 0x0001 ) { /* Double Buffered */
      source += (spriteram_size/2)/2;
      finish += (spriteram_size/2)/2;
    }

    while ( source<finish ) {
      int pen = (source[0]&0x3f00)>>8;
      int tileno = source[1];
      int pri = source[0]>>14;
      int x = source[2]&0x3ff;
      int y = source[3]&0x3ff;
      int flip = ((source[0] & 0x0040) >> 5) | // flipy
	((source[0] & 0x0080) >> 7); // flipx

      int height = ((source[3]&0xf000)>>12);
      int width = ((source[2]&0xf000)>>12);

      if (width && height) {
	if (x & 0x200) x-=0x400;
	if (y & 0x200) y-=0x400;

#if 0 /* For Flipscreen/Cocktail */
	if(mcatadv_vidregs[0]&0x8000)
	  {
	    flipx = !flipx;
	  }
	if(mcatadv_vidregs[1]&0x8000)
	  {
	    flipy = !flipy;
	  }
#endif

	if (source[3] != source[0] && /* 'hack' don't draw sprites while its testing the ram! */
	    tileno <= sprite_size) {
	  UINT8 *map;
	  int xx,w;

	  x -= global_x;
	  y -= global_y;

	  MAP_PALETTE_MAPPED_NEW(
				 pen,
				 16,
				 map
				 );

       /* This is taken directly from the cave driver. Except that the sprites are not
	  zoomed here, just flipped
	  Just a question : wouldn't it be faster to have something to draw directly
	  a sprite of wx16 x hx16 instead of recomputing the tiles everytime the size
	  changes ??? Since the size does not change often there must not be a big
	  difference of speed anyway, and writing such a drawing function would be much
	  longer... */

	  switch(flip){
	  case 0:
	    do{
	      if(gfx_obj_size[tileno] != width)
		make_tile_new(tileno, width,gfx_obj_a,gfx_obj_b,gfx_obj_solid,gfx_obj_size);
	      xx = x;
	      w = width;

	      do{
		if((xx > 0) && (xx < 320+16) && (y > 0) && (y < 224+16)){

		  if(gfx_obj_solid[tileno]){
		    if(gfx_obj_solid[tileno]==1)      // Some pixels; trans
		      pdraw16x16_Trans_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 0,
						       pri);
		    else {                         // all pixels; solid
		      pdraw16x16_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 0,
						pri);
		    }
		  }
		}
		xx = (xx + 16) & 0x3FF;
		tileno++; //tileno = (tileno + 1) & 0xFFFF;

	      }while(--w);

	      y = (y + 16) & 0x3FF;

	    }while(--height);
	    break;
	  case 1:
	    x = (x + ((width - 1) * 16)) & 0x3FF;
	    do{

	      if(gfx_obj_size[tileno] != width)
		make_tile_new(tileno, width,gfx_obj_a,gfx_obj_b,gfx_obj_solid,gfx_obj_size);
	      xx = x;
	      w = width;

	      do{

		if(gfx_obj_solid[tileno]){
		  if((xx > 0) && (xx < 320+16) && (y > 0) && (y < 224+16)){

		    if(gfx_obj_solid[tileno]==1)      // Some pixels; trans
		      pdraw16x16_Trans_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 1,
						       pri);
		    else                          // all pixels; solid
		      pdraw16x16_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 1,
						 pri);
		  }
		}

		xx = (xx - 16) & 0x3FF;
		tileno++;
	      }while(--w);

	      y = (y + 16) & 0x3FF;

	    }while(--height);
	    break;
	  case 2:
	    y = (y + ((height - 1) * 16)) & 0x3FF;
	    do{

	      if(gfx_obj_size[tileno] != width)
		make_tile_new(tileno, width,gfx_obj_a,gfx_obj_b,gfx_obj_solid,gfx_obj_size);
	      xx = x;
	      w = width;

	      do{

		if(gfx_obj_solid[tileno]){
		  if((xx > 0) && (xx < 320+16) && (y > 0) && (y < 224+16)){
		    if(gfx_obj_solid[tileno]==1)      // Some pixels; trans
		      pdraw16x16_Trans_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 2,
						       pri);
		    else {                         // all pixels; solid
		      pdraw16x16_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 2,
						 pri);
		    }
		  }
		}

		xx = (xx + 16) & 0x3FF;
		tileno++;

	      }while(--w);

	      y = (y - 16) & 0x3FF;

	    }while(--height);
	    break;
	  case 3:
	    x = (x + ((width - 1) * 16)) & 0x3FF;
	    y = (y + ((height - 1) * 16)) & 0x3FF;
	    do{

	      if(gfx_obj_size[tileno] != width)
		make_tile_new(tileno, width,gfx_obj_a,gfx_obj_b,gfx_obj_solid,gfx_obj_size);
	      xx = x;
	      w = width;

	      do{

		if((xx > 0) && (xx < 320+16) && (y > 0) && (y < 224+16)){

		  if(gfx_obj_solid[tileno]){
		    if(gfx_obj_solid[tileno]==1)      // Some pixels; trans
		      pdraw16x16_Trans_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 3,
						       pri);
		    else {                         // all pixels; solid
		      pdraw16x16_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 3,
						 pri);
		    }
		    // textout_fast(buff,xx,y,get_white_pen());
		  }
		}
		xx = (xx - 16) & 0x3FF;
		tileno++;

	      }while(--w);

	      y = (y - 16) & 0x3FF;

	    }while(--height);
	    break;
	  } // switch(flip)

	  // QueueTileSize(tileno,x-global_x,y-global_y,map,flip,pri,width,height);
	} // tileno <= sprite_size
      } // width && height
      source+=4;
    } // while source < finish
}

static void draw_mcatadv() {
  UINT8 pal_base1 = ReadWord(&scroll0[4]) << 6;
  UINT8 pal_base2 = ReadWord(&scroll1[4]) << 6;
  clear_game_screen(0);
  ClearPaletteMap();
  // ClearTileQueue();

  if (!tile_max0) {
    tile_max0 = get_region_size(REGION_GFX2)/0x100-1;
    tile_max1 = get_region_size(REGION_GFX3)/0x100-1;
  }
  clear_bitmap(pbitmap);

  // The priorities seem to be layer 0 first, then layer 1 and finally sprites
  // sprites are at the end or they hide the text in the japenese version intro
  if(check_layer_enabled(layer_id_data[0]))
    draw_tile(ram_bg0, scroll0,tile_max0,pal_base1, load_region[REGION_GFX2], gfx_solid[0]);
  if(check_layer_enabled(layer_id_data[1]))
    draw_tile(ram_bg1, scroll1,tile_max1,pal_base2, load_region[REGION_GFX3], gfx_solid[1]);

  if(check_layer_enabled(layer_id_data[2]))
    draw_sprites(); // outside the tile queue...

  // DrawTileQueue();

  memcpy(vidregs_old,video_regs,16);
  memcpy(spriteram_old,ram_spr,spriteram_size);
}






static void execute_mcatadv() {
  cpu_execute_cycles(CPU_68K_0, frame_68k);
   if (s68000context.pc == 0x36c ||
       (s68000context.pc == 0x11e && is_current_game("nost"))) {
     reset_game_hardware();
   } else if (s68000context.pc == 0x5a8c && !hack_applied && is_current_game("nost")) {
     memcpy(hack_buffer,&ROM[0x5a8a],6);
     WriteWord(&ROM[0x5a8a],0x4239);
     WriteWord(&ROM[0x5a8c],0xaa);
     WriteWord(&ROM[0x5a8e],0x0);
     hack_applied = 1;
     hack_adr = 0x5a8a;
     frame_68k = CPU_FRAME_MHz(32,60);
   }

  cpu_interrupt(CPU_68K_0, 1);

  execute_z80_audio_frame();
}



static struct VIDEO_INFO video_mcatadv =
  {
   draw_mcatadv,
   320,
   224,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
    mcatadv_gfxdecodeinfo
  };
static struct VIDEO_INFO video_nost =
  {
   draw_mcatadv,
   320,
   224,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
    mcatadv_gfxdecodeinfo
  };
GMEI( mcatadv, "Magical Cat Adventure", WINTECHNO, 1993, GAME_PLATFORM);
CLNEI( mcatadvj, mcatadv,"Magical Cat Adventure (jap - harder)", WINTECHNO, 1993, GAME_PLATFORM);
CLNEI( nost, mcatadv,"Nostradamus", FACE, 1993, GAME_SHOOT,
	.dsw = dsw_nost,
	.video = &video_nost,
);

