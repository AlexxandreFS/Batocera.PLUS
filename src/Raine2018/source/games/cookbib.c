/*

Cookie & Bibi
Hatch Catch

--

this hardware is basically a copy of the hardware Data East used
for games like Tumble Pop.

unlike Tumble Pop these use a simple Z80 for sound, and the GFX
are not encrypted.

Should somebody want to it should be possible to add Tumble Pop,
Diet Go Go and maybe a number of other Data East titles to this
driver.  Likewise several other Korean games run on very similar
hardawre

---

The layers in these games never seem perfectly aligned, I think
there is probably a 1 pixel gap at times even on the real hardware

Tilemap implementation is incomplete

*/

/* I haven't checked which of these we need */
#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "2151intf.h"
#include "adpcm.h"
#include "3812intf.h"
#include "timer.h"
#include "savegame.h"
#include "emumain.h" // set_reset_function
#include "scroll.h"

static UINT8 *RAM_Z80;
static UINT8 *RAM_MAIN;
static UINT8 *RAM_EXTRAWORK;
static UINT8 *RAM_SPRITE;
static UINT8 *RAM_SPRITEBUF;
static UINT8 *RAM_PF1;
static UINT8 *RAM_PF2;
static UINT8 *RAM_PALETTE;
static UINT8 *RAM_PFCTRL;
static UINT8 *RAM_TILEBANK;

static UINT8 *GFX_SPR,      *GFX_SPR_SOLID;
static UINT8 *GFX_TILE8x8,  *GFX_TILE8x8_SOLID;
static UINT8 *GFX_TILE16x16,*GFX_TILE16x16_SOLID;

static int cookbib_vblank;

static int pf1_xoffset, pf1_yoffset;
static int pf2_xoffset, pf2_yoffset;
static int spr_xoffset, spr_yoffset;

/* Cookie & Bibi Directories and (automatic) Rom loading */


static struct ROM_INFO rom_cookbib[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,    0x020000,
            "prg2.ub17",  0x2664a335, "prg1.ub16",  0xcda6335f),
	{ "prg-s.ub5",   0x010000, 0x547d6ea3, REGION_ROM2, 0x000000, LOAD_NORMAL },
	{ "sound.uc1",   0x020000, 0x545e19b6, REGION_SMP1, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,     0x020000,
            "uor1.bin",  0xa7d91f23, "uor2.bin",  0x9aacbec2),
  LOAD8_16(  REGION_GFX1,  0x040000,     0x020000,
            "uor3.bin",  0x3fee0c3c, "uor4.bin",  0xbed9ed2d),
  LOAD8_16(  REGION_GFX2,  0x000000,    0x040000,
            "srom6.bin",  0xade2dbec,"srom5.bin",  0x73a46e43 ),
	{ "protdata.bin",0x000200, 0xa77d13f4, REGION_PROMS,0x000000, LOAD_NORMAL, },
	{ NULL, 0, 0, 0, 0, 0 }
};

/* Hatch Catch Directories and (automatic) Rom loading */

static struct ROM_INFO rom_htchctch[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,      0x020000,
            "p04.b17",  0x6991483a, "p03.b16",  0xeff14c40),
	{ "p02.b5",      0x010000, 0xc5a03186, REGION_ROM2, 0x000000, LOAD_NORMAL },
	{ "p01.c1",      0x020000, 0x18c06829, REGION_SMP1, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x020000,
            "p08uor1.bin",  0x6811e7b6, "p09uor2.bin",  0x1c6549cf),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x020000,
            "p10uor3.bin",  0x6462e6e0, "p11uor4.bin",  0x9c511d98),
  LOAD8_16(  REGION_GFX2,  0x000000, 0x040000,
            "p07srom6.bin",  0x0207949c, "p06srom5.bin",  0x3d2cbb0d ),
	{ "protdata.bin",0x000200, 0x5b27adb6, REGION_PROMS,0x000000, LOAD_NORMAL, },
	{ NULL, 0, 0, 0, 0, 0 }
};

/* Choky Choky Directories and (automatic) Rom loading */

static struct ROM_INFO rom_chokchok[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,      0x040000,
            "ub17.bin",  0xecdb45ca, "ub18.bin",  0xb183852a),
	{ "ub5.bin",      0x010000, 0x30c2171d, REGION_ROM2, 0x000000, LOAD_NORMAL },
	{ "uc1.bin",      0x040000, 0xf3f57abd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,      0x080000,
            "uor1.bin",  0xded6642a, "uor2.bin",  0x493f9516),
  LOAD8_16(  REGION_GFX1,  0x100000,      0x080000,
            "uor3.bin",  0xe2dc3e12, "uor4.bin",  0x6f377530),
  LOAD8_16(  REGION_GFX2,  0x000000,     0x080000,
            "srom6.bin",  0x31d5715d,"srom5.bin",  0x836608b8),
	{ "protdata.bin", 0x000200, 0x0bd39834, REGION_PROMS,0x000000, LOAD_NORMAL, },
	{ NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_jumppop[] =
{
  { "68k_prg.bin", 0x80000, 0x123536b9, REGION_ROM1, 0x00000, LOAD_SWAP_16 },
  { "z80_prg.bin", 0x40000, 0xa88d4424, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "z80_prg.bin", 0x40000, 0xa88d4424, REGION_ROM2, 0x08000, LOAD_NORMAL },
  // GFX1 & GFX2 are inverted compared to mame
  { "bg0.bin", 0x100000, 0x35a1363d, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "bg1.bin", 0x100000, 0x5b37f943, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "sp0.bin", 0x100000, 0x7c5d0633, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "sp1.bin", 0x100000, 0x7eae782e, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "samples.bin", 0x40000, 0x066f30a7, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/* Inputs and Dipswitches */

/* if the address (3rd param) here is <0x100 the input is stored in INPUT buffer..
  otherwise its shoved straight into RAM[address] which you allocate on rom loading
  and doesn't even represent the real address .. ouch ouch ouch!

  this caused me no end of pain until checked the code and saw what was going on ;-)
  */

static struct INPUT_INFO input_cookbib[] =
{
	INP0( P1_UP, 0x0000, 0x01 ),
	INP0( P1_DOWN, 0x0000, 0x02 ),
	INP0( P1_LEFT, 0x0000, 0x04 ),
	INP0( P1_RIGHT, 0x0000, 0x08 ),
	INP0( P1_B1, 0x0000, 0x10 ),
	INP0( P1_B2, 0x0000, 0x20 ),
	INP0( P1_B3, 0x0000, 0x40 ),
	INP0( P1_START, 0x0000, 0x80 ),

	INP0( P2_UP, 0x0001, 0x01 ),
	INP0( P2_DOWN, 0x0001, 0x02 ),
	INP0( P2_LEFT, 0x0001, 0x04 ),
	INP0( P2_RIGHT, 0x0001, 0x08 ),
	INP0( P2_B1, 0x0001, 0x10 ),
	INP0( P2_B2, 0x0001, 0x20 ),
	INP0( P2_B3, 0x0001, 0x40 ),
	INP0( P2_START, 0x0001, 0x80 ),

	INP0( COIN1, 0x0009, 0x01 ),
	INP0( COIN2, 0x0009, 0x02 ),
	INP0( COIN3, 0x0009, 0x04 ),
/*                                            0x08, VBLANK          */
	END_INPUT
};

static struct INPUT_INFO jumppop_inputs[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( P1_DOWN, 0x00, 0x02 ),
  INP0( P1_LEFT, 0x00, 0x04 ),
  INP0( P1_RIGHT, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),
  INP0( P2_UP, 0x01, 0x01 ),
  INP0( P2_DOWN, 0x01, 0x02 ),
  INP0( P2_LEFT, 0x01, 0x04 ),
  INP0( P2_RIGHT, 0x01, 0x08 ),
  INP0( P2_B1, 0x01, 0x10 ),
  INP0( P2_B2, 0x01, 0x20 ),

  INP0( COIN1, 0x02, 0x01 ),
  INP0( COIN2, 0x02, 0x02 ),
  INP0( P1_START, 0x02, 0x04 ),
  INP0( P2_START, 0x02, 0x08 ),
   END_INPUT
};

static struct DSW_DATA dsw_data_cookbib_3[] =
{
  { _("Stage Skip"), 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_cookbib_4[] =
{
  DSW_SERVICE( 0, 0x01),
  { MSG_DIFFICULTY, 0x06, 4 },
  { MSG_EASY, 0x00},
  { MSG_NORMAL, 0x06},
  { MSG_HARD, 0x02},
  { MSG_VERY_HARD, 0x04},
  { MSG_COINAGE, 0x38, 8 },
  { MSG_5COIN_1PLAY, 0x00},
  { MSG_4COIN_1PLAY, 0x20},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_2COIN_3PLAY, 0x28},
  { MSG_1COIN_2PLAY, 0x18},
  { MSG_1COIN_3PLAY, 0x08},
  { _("VS Round"), 0x40, 2 },
  { "3", 0x40},
  { "1", 0x00},
  DSW_DEMO_SOUND( 0x00, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_cookbib[] =
{
  { 0x2, 0xff, dsw_data_cookbib_3 },
  { 0x3, 0x7f, dsw_data_cookbib_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_jumppop_3[] =
{
  DSW_SERVICE( 0, 0x0001),
  DSW_SCREEN( 0x0002, 0x0000),
  { MSG_COIN2, 0x001c, 8 },
  { MSG_3COIN_1PLAY, 0x0000},
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x001c},
  { MSG_1COIN_2PLAY, 0x000c},
  { MSG_1COIN_3PLAY, 0x0014},
  { MSG_1COIN_4PLAY, 0x0004},
  { MSG_1COIN_5PLAY, 0x0018},
  { MSG_1COIN_6PLAY, 0x0008},
  { MSG_COIN1, 0x00e0, 8 },
  { MSG_3COIN_1PLAY, 0x0000},
  { MSG_2COIN_1PLAY, 0x0080},
  { MSG_1COIN_1PLAY, 0x00e0},
  { MSG_1COIN_2PLAY, 0x0060},
  { MSG_1COIN_3PLAY, 0x00a0},
  { MSG_1COIN_4PLAY, 0x0020},
  { MSG_1COIN_5PLAY, 0x00c0},
  { MSG_1COIN_6PLAY, 0x0040},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_jumppop_4[] =
{
  DSW_DEMO_SOUND( 0x0, 0x1),
  { MSG_CONTINUE_PLAY, 0x2, 2 },
  { MSG_NO, 0x0},
  { MSG_YES, 0x2},
  { _("Picture Viewer"), 0x4, 2 },
  { MSG_OFF, 0x4},
  { MSG_ON, 0x0},
  { _("BG Type"), 0x8, 2 },
  { "1", 0x8},
  { "2", 0x0},
  { MSG_DIFFICULTY, 0x30, 4 },
  { MSG_EASY, 0x20},
  { MSG_NORMAL, 0x30},
  { MSG_HARD, 0x10},
  { MSG_HARDEST, 0x0},
  { MSG_LIVES, 0xc0, 4 },
  { "1", 0x80},
  { "2", 0x0},
  { "3", 0xc0},
  { "4", 0x40},
  { NULL, 0}
};

static struct DSW_INFO jumppop_dsw[] =
{
  { 0x4, 0xff, dsw_data_jumppop_3 },
  { 0x5, 0xfe, dsw_data_jumppop_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_htchctch_4[] =
{
  DSW_SERVICE( 0, 0x01),
  { MSG_DIFFICULTY, 0x06, 4 },
  { MSG_EASY, 0x00},
  { MSG_NORMAL, 0x06},
  { MSG_HARD, 0x02},
  { MSG_VERY_HARD, 0x04},
  { MSG_COINAGE, 0x38, 8 },
  { MSG_5COIN_1PLAY, 0x00},
  { MSG_4COIN_1PLAY, 0x20},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_2COIN_3PLAY, 0x28},
  { MSG_1COIN_2PLAY, 0x18},
  { MSG_1COIN_3PLAY, 0x08},
  { _("Stage Skip"), 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x00},
  DSW_DEMO_SOUND( 0x00, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_htchctch[] =
{
  { 0x3, 0x7f, dsw_data_htchctch_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_chokchok_3[] =
{
  { _("VS Round"), 0x01, 2 },
  { "3", 0x01},
  { "2", 0x00},
  { MSG_DIFFICULTY, 0x06, 4 },
  { MSG_EASY, 0x00},
  { MSG_NORMAL, 0x06},
  { MSG_HARD, 0x02},
  { MSG_VERY_HARD, 0x04},
  { MSG_UNKNOWN, 0x08, 2 },
  { MSG_OFF, 0x08},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x00},
  { _("Time"), 0x20, 2 },
  { _("60 Seconds"), 0x20},
  { _("90 Seconds"), 0x00},
  { _("Starting Balls"), 0xc0, 4 },
  { "3", 0x00},
  { "4", 0xc0},
  { "5", 0x40},
  { "6", 0x80},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_chokchok_4[] =
{
  DSW_SERVICE( 0, 0x01),
  { MSG_UNKNOWN, 0x02, 2 },
  { MSG_OFF, 0x02},
  { MSG_ON, 0x00},
  { MSG_UNKNOWN, 0x04, 2 },
  { MSG_OFF, 0x04},
  { MSG_ON, 0x00},
  { MSG_COINAGE, 0x38, 8 },
  { MSG_5COIN_1PLAY, 0x00},
  { MSG_4COIN_1PLAY, 0x20},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_2COIN_3PLAY, 0x28},
  { MSG_1COIN_2PLAY, 0x18},
  { MSG_1COIN_3PLAY, 0x08},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x00},
  DSW_DEMO_SOUND( 0x00, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_chokchok[] =
{
  { 0x2, 0xff, dsw_data_chokchok_3 },
  { 0x3, 0x7f, dsw_data_chokchok_4 },
  { 0, 0, NULL }
};

/* Sound Hardware  */

/* remember, in RAINE the memory maps are set up in the load function, manually */

/* note: the sound system is the same as hyperpcb.c */

static struct YM2151interface ym2151_interface =
{
	1,
	4000000,	/* 4 MHz??? */
	{ YM3012_VOL(25,MIXER_PAN_LEFT,25,MIXER_PAN_RIGHT) },
	{ z80_irq_handler }
};

static struct OKIM6295interface okim6295_interface =
{
	1,			/* 1 chip */
	{ 7575 },		/* 7575Hz playback? */
	{ REGION_SOUND1 },
	{ 240 }
};

static struct SOUND_INFO sound_cookbib[] =
{
   { SOUND_YM2151J,  &ym2151_interface,    },
   { SOUND_M6295,    &okim6295_interface   },
   { 0,              NULL,                 },
};



/* Video Hardware (drawing!) */

static UINT8 *map;

static void cookbib_draw_8x8_layer(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	UINT8  colour;
	int x16,y16,zzz,zzzz;
	int zz;

//	print_debug("RAM_TILEBANK %02x %02x\n",RAM_TILEBANK[0],RAM_TILEBANK[1]);

	MAKE_SCROLL_512x256_2_8(scrollx,scrolly);
	START_SCROLL_512x256_2_8(32,32,320,240);
	{
	  tileno = ReadWord(&PFRAM[zz]);
	  colour = tileno>>12;
	  colour += palbase;
	  tileno &= 0x0fff;

	  tileno += RAM_TILEBANK[1]<<7;

	  if( GFX_TILE8x8_SOLID[tileno] )
	    {
	      MAP_PALETTE_MAPPED_NEW(
				     colour,
				     16,
				     map
				     );

	      if((GFX_TILE8x8_SOLID[tileno]==1))
		{
		  Draw8x8_Trans_Mapped_Rot(&GFX_TILE8x8[tileno<<6], x, y, map);
		}
	      else
		{
		  Draw8x8_Mapped_Rot(&GFX_TILE8x8[tileno<<6], x, y, map);
		}
	    }
	}
	END_SCROLL_512x256_2_8();
}

static void cookbib_draw_16x16_layer(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	UINT8  colour;
	int x16,y16,zzz,zzzz;
	int zz;

//	print_debug("RAM_TILEBANK %02x %02x\n",RAM_TILEBANK[0],RAM_TILEBANK[1]);

	MAKE_SCROLL_512x512_2_16(scrollx,scrolly);
	START_SCROLL_512x512_2_16(32,32,320,240);
	{
	  tileno = ReadWord(&PFRAM[zz]);
	  colour = tileno>>12;
	  colour += palbase;
	  tileno &= 0x0fff;

	  /* note, if we add BC Story the tilebank isn't the same */
	  tileno += RAM_TILEBANK[1]<<7;

	  MAP_PALETTE_MAPPED_NEW(
				 colour,
				 16,
				 map
				 );

	  Draw16x16_Mapped_Rot(&GFX_TILE16x16[tileno<<8], x, y, map);
	}
	END_SCROLL_512x512_2_16();
}

static void jumppop_draw_solid_layer16(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	int x16,y16,zzz,zzzz;
	int zz;

	MAP_PALETTE_MULTI_MAPPED_NEW(
				     0x20, // ???
				     256,
				     map
				     );


	MAKE_SCROLL_1024x1024_2_16(scrollx,scrolly);
	START_SCROLL_1024x1024_2_16(32,32,320,240);
	{
	  tileno = ReadWord(&PFRAM[zz]);
	  tileno &= 0x1fff;

	  /* note, if we add BC Story the tilebank isn't the same */
	  // tileno += RAM_TILEBANK[1]<<7;

	  Draw16x16_Mapped_Rot(&GFX_TILE16x16[tileno<<8], x, y, map);
	}
	END_SCROLL_1024x1024_2_16();
}

static void jumppop_draw_solid_layer8(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	int x16,y16,zzz,zzzz;
	int zz;

	MAP_PALETTE_MULTI_MAPPED_NEW(
				     0x20, // ???
				     256,
				     map
				     );


	MAKE_SCROLL_1024x512_2_8(scrollx,scrolly);
	START_SCROLL_1024x512_2_8(32,32,320,240);
	{
	  tileno = ReadWord(&PFRAM[zz]);
	  tileno &= 0x7fff;

	  /* note, if we add BC Story the tilebank isn't the same */
	  // tileno += RAM_TILEBANK[1]<<7;

	  Draw8x8_Mapped_Rot(&GFX_TILE8x8[tileno<<6], x, y, map);
	}
	END_SCROLL_1024x512_2_8();
}

static void jumppop_draw_layer8(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	int x16,y16,zzz,zzzz;
	int zz;

//	print_debug("RAM_TILEBANK %02x %02x\n",RAM_TILEBANK[0],RAM_TILEBANK[1]);

	MAP_PALETTE_MULTI_MAPPED_NEW(
				     0x10, // ???
				     256,
				     map
				     );

	MAKE_SCROLL_1024x512_2_8(scrollx,scrolly);
	START_SCROLL_1024x512_2_8(32,32,320,240);
	{
	  tileno = ReadWord(&PFRAM[zz]);
	  tileno &= 0x7fff;

	  if( GFX_TILE8x8_SOLID[tileno] )
	    {
	      if((GFX_TILE8x8_SOLID[tileno]==1))
		{
		  Draw8x8_Trans_Mapped_Rot(&GFX_TILE8x8[tileno<<6], x, y, map);
		}
	      else
		{
		  Draw8x8_Mapped_Rot(&GFX_TILE8x8[tileno<<6], x, y, map);
		}
	    }
	}
	END_SCROLL_1024x512_2_8();
}

static void jumppop_draw_layer16(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	int x16,y16,zzz,zzzz;
	int zz;

//	print_debug("RAM_TILEBANK %02x %02x\n",RAM_TILEBANK[0],RAM_TILEBANK[1]);

	MAP_PALETTE_MULTI_MAPPED_NEW(
				     0x10, // ???
				     256,
				     map
				     );

	MAKE_SCROLL_1024x1024_2_16(scrollx,scrolly);
	START_SCROLL_1024x1024_2_16(32,32,320,240);
	{
	  tileno = ReadWord(&PFRAM[zz]);
	  tileno &= 0x3fff;

	  if( GFX_TILE16x16_SOLID[tileno] )
	    {
	      if((GFX_TILE16x16_SOLID[tileno]==1))
		{
		  Draw16x16_Trans_Mapped_Rot(&GFX_TILE16x16[tileno<<8], x, y, map);
		}
	      else
		{
		  Draw16x16_Mapped_Rot(&GFX_TILE16x16[tileno<<8], x, y, map);
		}
	    }
	}
	END_SCROLL_1024x1024_2_16();
}

/* this doesn't take into account priority, but afaik these games don't really care */

static void cookbib_drawsprites(int hack_flipx)
{
	int offs;
	static int frame=0;

	frame++;

	for (offs = 0;offs<0x1000;offs+=8)
	{
		int x,y,sprite,colour,multi,/* fx,*/ fy,inc,flash,mult,flipyx,xdraw;

//		print_debug("sprite %04x\n",offs);

		sprite = (RAM_SPRITE[offs+2]|(RAM_SPRITE[offs+3]<<8));

		if (!sprite) continue; // careful.. not all games have sprite 0 as blank, these AFAIK do however

		y =      ReadWord(&RAM_SPRITE[offs+0]);

//		sprite &=0x7fff;

		flash=y&0x1000;
		if ((flash) && (frame & 1) ) continue;

		x =      ReadWord(&RAM_SPRITE[offs+4]);
		colour = (x >>9) & 0xf;

		// fx = y & 0x2000;
		fy = y & 0x4000;
		flipyx = (y&0x6000)>>13;

		multi = (1 << ((y & 0x0600) >> 9)) - 1;	// 1x, 2x, 4x, 8x height

		x = x & 0x01ff;
		y = y & 0x01ff;
		if (x >= 320) x -= 512;
		if (y >= 256) y -= 512;
		y = 240 - y;
		if (hack_flipx) {
		  flipyx ^= 1;
		} else
		  x = 304 - x;

		xdraw = x+32+spr_xoffset; // x-1 for bcstory .. realign other layers?

		if((xdraw<=16)||(xdraw>=320+32)) continue;

	//  sprite &= ~multi; // Todo:  I bet TumblePop bootleg doesn't do this either
		if (fy)
			inc = -1;
		else
		{
			sprite += multi;
			inc = 1;
		}

//		if (flipscreen)
//		{
//			y=240-y;
//			x=304-x;
//			if (fx) fx=0; else fx=1;
//			if (fy) fy=0; else fy=1;
//			mult=16;
//		}
//		else
		mult=-16;

		while (multi >= 0)
		{
			int ydraw = (y+mult*multi)+25+spr_yoffset;
			int spriteno = sprite - multi * inc;
/*
			drawgfx(bitmap,Machine->gfx[3],
					spriteno,
					colour,
					fx,fy,
					xdraw,ydraw,
					cliprect,TRANSPARENCY_PEN,0);
*/


			if ((ydraw>16)&&(ydraw<240+32) && spriteno<max_sprites[0])
			{
//				print_debug("sprite draw %04x %04x %04x\n",xdraw,ydraw,spriteno);

				if(GFX_SPR_SOLID[spriteno])
				{            // No pixels; skip

					MAP_PALETTE_MAPPED_NEW(
						colour,
						16,
						map
					);

					if(GFX_SPR_SOLID[spriteno]==1)
					{         // Some pixels; trans
						switch(flipyx)
						{
							case 0x00: Draw16x16_Trans_Mapped_Rot       (&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
							case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot (&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
							case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot (&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
							case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
						}
					}
					else
					{                  // all pixels; solid
						switch(flipyx)
						{
							case 0x00: Draw16x16_Mapped_Rot       (&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
							case 0x01: Draw16x16_Mapped_FlipY_Rot (&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
							case 0x02: Draw16x16_Mapped_FlipX_Rot (&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
							case 0x03: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[spriteno<<8], xdraw, ydraw, map); break;
						}
					}
				}
			}

			multi--;
		}

	}
}

static void draw_cookbib(void)
{
	int scrollx,scrolly;

	ClearPaletteMap();

	if (!GFX_SPR) {
	  GFX_SPR             = gfx[0];
	  GFX_SPR_SOLID       = gfx_solid[0];

	  GFX_TILE8x8         = gfx[1];
	  GFX_TILE8x8_SOLID   = gfx_solid[1];

	  GFX_TILE16x16       = gfx[2];
	  GFX_TILE16x16_SOLID = gfx_solid[2];
	}

	scrollx = ReadWord(&RAM_PFCTRL[6]);
	scrolly = ReadWord(&RAM_PFCTRL[8]);
	scrollx += pf2_xoffset;
	scrolly += pf2_yoffset;

	cookbib_draw_16x16_layer(scrollx,scrolly,0x20,RAM_PF2);

	scrollx = ReadWord(&RAM_PFCTRL[2]);
	scrolly = ReadWord(&RAM_PFCTRL[4]);
	scrollx += pf1_xoffset;
	scrolly += pf1_yoffset;
	cookbib_draw_8x8_layer  (scrollx,scrolly,0x10,RAM_PF1);

	cookbib_drawsprites(0);
}

static void draw_jumppop(void)
{
	int scrollx,scrolly;

	ClearPaletteMap();

	if (!GFX_SPR) {
	  GFX_SPR             = gfx[0];
	  GFX_SPR_SOLID       = gfx_solid[0];

	  GFX_TILE8x8         = gfx[1];
	  GFX_TILE8x8_SOLID   = gfx_solid[1];

	  GFX_TILE16x16       = gfx[2];
	  GFX_TILE16x16_SOLID = gfx_solid[2];
	}

	scrollx = ReadWord(&RAM_PFCTRL[0])-0x3a2;
	scrolly = ReadWord(&RAM_PFCTRL[2])+8;
	if (RAM_PFCTRL[7*2] & 1)
	  jumppop_draw_solid_layer16(scrollx,scrolly,0x10,RAM_PF2);
	else
	  jumppop_draw_solid_layer8(scrollx,scrolly,0x10,RAM_PF2);

	scrollx = ReadWord(&RAM_PFCTRL[4])-0x3a0;
	scrolly = ReadWord(&RAM_PFCTRL[6])+8;
	if (RAM_PFCTRL[7*2] & 2) {
	  jumppop_draw_layer16(scrollx,scrolly,0x10,RAM_PF1);
	} else {
	  jumppop_draw_layer8(scrollx,scrolly,0x10,RAM_PF1);
	}

	cookbib_drawsprites(1);
}

/* Video Hardware (setup) */

/* The GFX decodes are basically the same as MAME */


static gfx_layout cookbib_8x8tiles =
{
	8,8,
	RGN_FRAC(1,2),
	4,
	{ RGN_FRAC(1,2)+8, RGN_FRAC(1,2)+0, 8, 0 },
	{ 0, 1, 2, 3, 4, 5, 6, 7 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
	16*8
};


static gfx_layout cookbib_16x16tiles =
{
	16,16,
	RGN_FRAC(1,2),
	4,
	{ RGN_FRAC(1,2)+8, RGN_FRAC(1,2)+0, 8, 0 },
	{ 32*8+0, 32*8+1, 32*8+2, 32*8+3, 32*8+4, 32*8+5, 32*8+6, 32*8+7,
			0, 1, 2, 3, 4, 5, 6, 7 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16,
			8*16, 9*16, 10*16, 11*16, 12*16, 13*16, 14*16, 15*16 },
	64*8
};

static GfxLayout jumppop_tcharlayout =
{
	8,8,
	RGN_FRAC(1,2),
	8,
	{ 0,1,2,3,4,5,6,7 },
	{RGN_FRAC(1,2)+0,RGN_FRAC(1,2)+8,0,8,RGN_FRAC(1,2)+16,RGN_FRAC(1,2)+24,16,24 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8
};

static GfxLayout jumpop_tlayout =
{
	16,16,
	RGN_FRAC(1,2),
	8,
	{ 0,1,2,3,4,5,6,7 },
	{RGN_FRAC(1,2)+0,RGN_FRAC(1,2)+8,0,8,RGN_FRAC(1,2)+16,RGN_FRAC(1,2)+24,16,24,
	256+RGN_FRAC(1,2)+0,256+RGN_FRAC(1,2)+8,256+0,256+8,256+RGN_FRAC(1,2)+16,256+RGN_FRAC(1,2)+24,256+16,256+24
	},
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32,
	512+0*32, 512+1*32, 512+2*32, 512+3*32, 512+4*32, 512+5*32, 512+6*32, 512+7*32
	},
	128*8
};

static struct GFX_LIST cookbib_gfx[] =
{
   { REGION_GFX1, &cookbib_16x16tiles, },
   { REGION_GFX2, &cookbib_8x8tiles,   }, // done when loading
   { REGION_GFX2, &cookbib_16x16tiles, }, // done when loading
   { 0,           NULL,           },
};

static struct GFX_LIST jumppop_gfx[] =
{
  { REGION_GFX1, &cookbib_16x16tiles, },
  { REGION_GFX2, &jumppop_tcharlayout, }, // done when loading
  { REGION_GFX2, &jumpop_tlayout, }, // done when loading
  { 0,           NULL,           },
};



/* System (execute) */

/* instead of a MACHINE_DRIVER (as in MAME) the CPU speeds etc. are handled
   here by calling the execute functions for each CPU core, likewise the
   interrupts */

#define FRAME CPU_FRAME_MHz(16,60)

static void execute_cookbib(void)
{
	cookbib_vblank = 0x00;
	cpu_execute_cycles(CPU_68K_0, FRAME); // Main 68000
	cookbib_vblank = 0x08;
	cpu_interrupt(CPU_68K_0, 6);


	if (RaineSoundCard)
		execute_z80_audio_frame();

	cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(1,60)); // run a bit of code with vbl set
}

#define FRAME_Z80 CPU_FRAME_MHz(4,60)

static void execute_jumppop(void)
{
  if (RaineSoundCard) {
    execute_z80_audio_frame_with_nmi(32);
  } else {
    cpu_execute_cycles(CPU_68K_0, FRAME); // Main 68000
  }
  cpu_interrupt(CPU_68K_0, 6);
}

/* Load Roms / Set Memory Map */


static void install_protdata() {
/* The SemiCom titles have an MCU which provides 0x200 bytes of code in RAM
   when the machine boots up */
	print_debug("Installing Protection Data\n");
	memcpy(RAM_MAIN,load_region[REGION_PROMS],0x200);
	ByteSwap(RAM_MAIN,0x200);
}

UINT8 cookbib_inputs_8r (UINT32 offset)
{
	int retdata;
	offset &=0xf;// in RAINE the offset contains the complete address
	retdata = input_buffer[offset];

	if (offset==9)
	{
		retdata&=0xf7;
		retdata|=cookbib_vblank;
	}

	return retdata;
}

UINT16 input_cookbib_16r (UINT32 offset)
{
	int retdata;
	offset &=0xf;// in RAINE the offset contains the complete address
	retdata = cookbib_inputs_8r(offset)|(cookbib_inputs_8r(offset+1)<<8);
	return retdata;
}

static void chokchok_tile_swap(void)
{
	data8_t *buf = malloc(get_region_size(REGION_GFX2));
	data8_t *src = load_region[REGION_GFX2];
	int len = get_region_size(REGION_GFX2);
	int cnt;

	if (!buf) return;

	for (cnt=0;cnt<len;cnt++)
	{
		int i;

		i = cnt;

		if (cnt&0x40000) i ^=0xc0000;
		if (cnt&0x80000) i ^=0xc0000;

		buf[i]=src[cnt];
	}

	memcpy(src,buf,len);

	free(buf);

	// 000000 - 03ffff = 000000 - 03ffff
	// 040000 - 07ffff = 080000 - 0bffff
	// 080000 - 0bffff = 040000 - 07ffff
	// 0c0000 - 0fffff = 0c0000 - 0fffff
}

static void cookbib_tile_swap(void)
{
	data8_t *rom = load_region[REGION_GFX2];
	int len = get_region_size(REGION_GFX2);
	int i;

	/* gfx data is in the wrong order */
	for (i = 0;i < len;i++)
	{
		if ((i & 0x20) == 0)
		{
			int t = rom[i]; rom[i] = rom[i + 0x20]; rom[i + 0x20] = t;
		}
	}
	/* low/high half are also swapped */
	for (i = 0;i < len/2;i++)
	{
		int t = rom[i]; rom[i] = rom[i + len/2]; rom[i + len/2] = t;
	}
}

static void jumppop_sound_w(UINT32 offset, UINT16 data) {
  latch = data;
  cpu_interrupt(CPU_Z80_0, 0x38); // to check
}

static UINT8 jumppop_z80latch_r(UINT32 offset) {
  return latch;
}

static void load_cookbib(void)
{
	/* In RAINE we allocate one big block of RAM to contain all emulated RAM then set some pointers to it

		Z80:
		0x10000 bytes z80

		68000:
	    0x04000 bytes MAIN ram
	    0x02000 bytes EXTRA work ram
	    0x01000 bytes SPRITE ram
	    0x01000 bytes SPRITE buffer ram
	    0x01000 bytes TILEMAP1 (PF1) data ram
	    0x01000 bytes TILEMAP2 (PF2) data ram
	    0x00800 bytes PALETTE ram
	    0x00010 bytes TILEMAP  (PF)  conrol ram

	*/

	/* Calculate how much RAM we need to allocate */
  if (is_current_game("jumppop")) {
    RAMSize=0x10000
      +0x04000
      +0x02000
      +0x01000
      +0x08000
      +0x04000
      +0x04000
      +0x00800
      +0x00010
      +0x00010;
  } else {
    RAMSize=0x10000
      +0x04000
      +0x02000
      +0x01000
      +0x01000
      +0x01000
      +0x01000
      +0x00800
      +0x00010
      +0x00010;
  }
  /* Allocate the RAM */
	if(!(RAM=AllocateMem(RAMSize*2))) return;  // I must be doing something wrong somewhere?  I get a heap error exiting RAINE unless I allocate double the RAM.. but I can't find track the bug

	/* Set Up the Pointers */
	RAM_Z80       = &RAM[0x00000];
	RAM_MAIN      = &RAM[0x00000+0x10000];
	RAM_EXTRAWORK = &RAM[0x00000+0x10000+0x04000];
	RAM_SPRITE    = &RAM[0x00000+0x10000+0x04000+0x02000];
	RAM_SPRITEBUF = &RAM[0x00000+0x10000+0x04000+0x02000+0x01000];
	RAM_PF1       = RAM_SPRITEBUF + (is_current_game("jumppop") ? 0x8000 : 0x01000);
	RAM_PF2       = RAM_PF1 + (is_current_game("jumppop") ? 0x4000 : 0x01000);
	RAM_PALETTE   = RAM_PF2 + (is_current_game("jumppop") ? 0x4000 : 0x01000);
	RAM_PFCTRL    = RAM_PALETTE + 0x00800;
	RAM_TILEBANK  = RAM_PFCTRL + 0x0010;

	/* Set up the Z80 Memory Map (Sound CPU) */

	AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
	if (is_current_game("jumppop")) {
	  z80_init_banks(0, REGION_ROM2, 0x8000, 0x4000);
	  AddZ80AReadByte (0x0000, 0xbfff, NULL,                     NULL ); // Z80 ROM + bank
	  AddZ80ARW (0xf800, 0xffff, NULL,                     RAM_Z80                  );

	  AddZ80AWritePort(0, 0, YM3812_control_port_0_w, NULL);
	  AddZ80AWritePort(1, 1, YM3812_write_port_0_w, NULL);
	  AddZ80AReadPort(2, 2, OKIM6295_status_0_r, NULL);
	  AddZ80AWritePort(2, 2, OKIM6295_data_0_w, NULL);
	  AddZ80AReadPort(3, 3, jumppop_z80latch_r, NULL);
	  AddZ80AWritePort(5, 5, z80a_set_bank, NULL);
	} else {
	  AddZ80AReadByte (0x0000, 0xcfff, NULL,                     load_region[REGION_ROM2] ); // Z80 ROM
	  AddZ80AReadByte (0xd000, 0xd7ff, NULL,                     RAM_Z80                  );
	  AddZ80AReadByte (0xf001, 0xf001, YM2151_status_port_0_r,   NULL                     );
	  AddZ80AReadByte (0xf008, 0xf008, NULL,                     (UINT8*)&latch           );

	  AddZ80AWriteByte(0xd000, 0xd7FF, NULL,                     RAM_Z80                  ); // Z80 RAM
	  AddZ80AWriteByte(0xf000, 0xf000, YM2151_register_port_0_w, NULL                     );
	  AddZ80AWriteByte(0xf001, 0xf001, YM2151_data_port_0_w,     NULL                     );
	  AddZ80AWriteByte(0xf002, 0xf002, OKIM6295_data_0_w,        NULL                     );
	}
	/* all unmapped reads go here */
	AddZ80AReadByte (0x0000, 0xFFFF, DefBadReadZ80,            NULL                     );
	AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,           NULL                     );
	AddZ80AReadPort (  0x00,   0xFF, DefBadReadPortZ80,            NULL                     );
	AddZ80AWritePort(  0x00,   0xFF, DefBadWritePortZ80,           NULL                     );

	AddZ80AInit();

   // apparently we need to be a little higher than 4 Mhz...
   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(7,60)); // for the Z80 we need to set up the speed here..


	print_debug("z80 Init Done\n");

	/* Setup Starscream 68000 core */

	/* ROM is a pointer to the ROM1 region.. automatically set up? */

	/* byteswap the ROM area.. */
	ByteSwap(ROM,get_region_size(REGION_CPU1));

	if (!is_current_game("jumppop"))
	  set_reset_function(install_protdata); // we need to copy protection data every time we reset .. this is like MACHINE_INIT in MAME

	/*
	   AddMemFetch = For Running Program Code

	   AddReadByte = Add Read Handler for Bytes
	   AddReadWord = Add Read Handler for Words
	   AddReadBW   = Add Read Handler for Bytes+Words

	   AddWriteByte = Add Write Handler for Bytes
	   AddWriteWord = Add Write Handler for Words
	   AddWriteBW   = Add Write Handler for Bytes+Words

	   AddRWBW     = Add Read+Write Handler for Bytes+Words

	*/


	/* It runs from ROM and an area of RAM */
	AddMemFetch (0x000000, 0x07ffff,                        ROM                      );
	AddMemFetch (0x120000, 0x123fff,                        RAM_MAIN-0x120000        ); // note: you need to subtract the address?!
	AddMemFetch (0x341000, 0x342fff,                        RAM_EXTRAWORK-0x341000   ); // note: you need to subtract the address?!
	AddMemFetch (-1, -1, NULL);

	/* ROM for normal READ Operations -- we don't want to allow writing to ROM! */
	AddReadBW   (0x000000, get_region_size(REGION_CPU1)-1,     NULL,              ROM             );   // 68000 ROM
	/* Set Up the RAM, we allow all types of READ/WRITE operations */
	AddRWBW     (0x120000, 0x123fff,     NULL,              RAM_MAIN        );   // MAIN RAM
	AddRWBW     (0x140000, 0x1407ff,     NULL,              RAM_PALETTE     );   // PALETTE RAM
	AddRWBW     (0x160000, 0x160fff,     NULL,              RAM_SPRITE      );   // SPRITE RAM

	AddWriteByte(0x100001, 0x100001,     NULL,              (UINT8*)&latch+1);   // sound
	AddRWBW     (0x100002, 0x100003,     NULL,              RAM_TILEBANK    );   // Tile Banking
	if (is_current_game("jumppop")) {
	  AddRWBW     (0x1a0000, 0x1a7fff,     NULL,              RAM_SPRITEBUF   );   // BUFFER RAM
	  AddRWBW     (0x380000, 0x38000f,     NULL,              RAM_PFCTRL      );   // PLAYFIELD CONTROL
	  AddRWBW     (0x320000, 0x323fff,     NULL,              RAM_PF1         );   // PLAYFIELD 1 DATA
	  AddRWBW     (0x300000, 0x303fff,     NULL,              RAM_PF2         );   // PLAYFIELD 2 DATA
	  AddWriteWord(0x18000c, 0x18000d, jumppop_sound_w, NULL);
	  AddReadBW(0x180002, 0x18000f, NULL, input_buffer);
	  memset(input_buffer,0xff,0x10);
	} else {
	  AddRWBW     (0x1a0000, 0x1a0fff,     NULL,              RAM_SPRITEBUF   );   // BUFFER RAM
	  AddRWBW     (0x300000, 0x30000f,     NULL,              RAM_PFCTRL      );   // PLAYFIELD CONTROL
	  AddRWBW     (0x320000, 0x320fff,     NULL,              RAM_PF1         );   // PLAYFIELD 1 DATA
	  AddRWBW     (0x322000, 0x322fff,     NULL,              RAM_PF2         );   // PLAYFIELD 2 DATA
	  AddReadByte (0x180000, 0x18000f,     cookbib_inputs_8r, NULL            );   // Inputs
	  AddReadWord (0x180000, 0x18000f,     input_cookbib_16r,NULL            );   // Inputs
	}
	AddRWBW     (0x341000, 0x342fff,     NULL,              RAM_EXTRAWORK   );   // EXTRA WORK RAM

	finish_conf_68000(0);


	print_debug("Starscream Memory Init Done\n");

	/* Setting up the GFX */

	GFX_SPR             = NULL;

	/* Choky Choky has more tiles.. we have to rearrange before we can decode */
	if (is_current_game("chokchok"))
	  chokchok_tile_swap();

	/* tile data is in the wrong order, fix it */
	if (!is_current_game("jumppop"))
	  cookbib_tile_swap();

	/* Initialize Some Variables */
	RAM_TILEBANK[1]=0;
	pf1_xoffset = pf1_yoffset = 0;
	pf2_xoffset = pf2_yoffset = 0;
	spr_xoffset = spr_yoffset = 0;

	if (is_current_game("cookbib"))
	{
		pf1_xoffset = -4;
		pf1_yoffset = 9;
		pf2_xoffset = -1;
		pf2_yoffset = 9;
		spr_xoffset = 0;
		spr_yoffset = 0;
	}
	else if (is_current_game("htchctch"))
	{
		pf1_xoffset = -14; // how to play text..
		pf1_yoffset = 9;
		pf2_xoffset = -1;
		pf2_yoffset = 9;
		spr_xoffset = 0;
		spr_yoffset = -1;
	}
	else if (is_current_game("chokchok"))
	{
		pf1_xoffset = -6; // playfield
		pf1_yoffset = 9;
		pf2_xoffset = -1;
		pf2_yoffset = 9;
		spr_xoffset = 0;
		spr_yoffset = -1;
	}

	/* Note: In RAINE the palette is handled like this */
	InitPaletteMap(RAM_PALETTE, 0x30, 0x10, 0x8000);

	if (is_current_game("chokchok"))
	{
		/* Choky Choky has a different palette format */
		set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);
	}
	else if (is_current_game("jumppop")) {
	  set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
	} else
	{
		set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

	}
	print_debug("GFX are Set Up\n");


}

/* GAME definitions */

/* Cookie & Bibi / Hatch Catch are Identical Hardware */




static struct YM3812interface ym3812_interface =
{
   1,              // 1 chip
   3500000,	/**/
   { 175 },        // Volume (emu only)
   { NULL }
};

static struct OKIM6295interface jumppop_okim6295_interface =
{
	1,			/* 1 chip */
	{ 875000/132 },		/* 7575Hz playback? */
	{ REGION_SOUND1 },
	{ 127 }
};

static struct SOUND_INFO jumppop_sound[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { SOUND_M6295,    &jumppop_okim6295_interface   },
   { 0,              NULL,                 },
};

static struct VIDEO_INFO jumppop_video =
{
   draw_jumppop,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   jumppop_gfx,
};
static struct VIDEO_INFO video_cookbib =
{
   draw_cookbib,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   cookbib_gfx,
};
static struct DIR_INFO dir_chokchok[] =
{
   { "choky_choky", },
   { "chokchok", },
   { NULL, },
};
CLNE( chokchok, cookbib,"Choky Choky", SEMICOM, 1995, GAME_MISC,
	.dsw = dsw_chokchok,
);
static struct DIR_INFO dir_cookbib[] =
{
   { "cookie_and_bibi", },
   { "cookbib", },
   { NULL, },
};
GME( cookbib, "Cookie and Bibi", SEMICOM, 1995, GAME_MISC);
static struct DIR_INFO dir_htchctch[] =
{
   { "hatch_catch", },
   { "htchctch", },
   { NULL, },
};
CLNE( htchctch, cookbib, "Hatch Catch", SEMICOM, 1995, GAME_MISC,
	.dsw = dsw_htchctch,
);

CLNEI( jumppop,cookbib, "Jumping Pop", ESD, 2001, GAME_PLATFORM,
	.input = jumppop_inputs,
	.dsw = jumppop_dsw,
	.exec = execute_jumppop,
	.video = &jumppop_video,
	.sound = jumppop_sound);
