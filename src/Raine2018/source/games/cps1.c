/*****************************************************************************/
/*									     */
/*		     CAPCOM SYSTEM 1 / CPS1 (C) 1990 CAPCOM		     */
/* Based on the mame source, but lots of things were rewritten...	     */
/* Thnaks to the mame team to show how all this works anyway !		     */
/* See cps1drv.c for the games related data...				     */
/*****************************************************************************/
/* A few notes about graphic effects :
 * - star fields are not emulated because they appear only in forgoten
 *   worlds and striders + it's really a bad effect, that's probably why
 *   it was used only in 2 games.
 * - line scrolls are now fully emulated. From the comments in the
 * mame source, here are the places where they appear :
 *
 * SF2
 * Mega Twins (underwater, cave)
 * Carrier Air Wing (hazy background at beginning of mission 8, put 07
 * at ff8501 to jump there)
 * Magic Sword (fire on floor 3; screen distort after continue)
 * Varth (title screen)
 * Bionic Commando (end game sequence)
 *
 * And I would add punisher at least in the tunnel between stage 1 and
 * 2. And Cadillac and dinosaurs at stage 2 at least.
 *
 * CPS2 support is now working.
 * 2009/01 : finally converted the config stuff to use the data extracted by
 * mame about the video pals. It allows to get rid of all the kludges, it gives
 * a better idea about where each layer is located in gfx1, and it probably
 * allows a slightly faster emulation (+ all future games dumped with the
 * right pal info should work out of the box). This is probably the last major
 * update for this driver.
 */

#include "gameinc.h"
#include "cps1.h"
#include "mame/eeprom.h"
#include "savegame.h"
#include "sasound.h"
#include "2151intf.h"
#include "adpcm.h"
#include "qsound.h"
#include "blit.h" // clear_game_screen
#include "timer.h" // execute_z80_audio_frame
#include "emumain.h" // set_reset_function
#include "lspr16.h"
#include "priorities.h"
#include "profile.h"
#include "pdraw.h"
#include "arpro.h"
#include "decode.h"
#include "cps2crpt.h"
#include "speed_hack.h"
#include "bld.h"
#include "alpha.h"

/* Output ports */
#define CPS1_OBJ_BASE		0x00	/* Base address of objects */
#define CPS1_SCROLL1_BASE	0x01	/* Base address of scroll 1 */
#define CPS1_SCROLL2_BASE	0x02	/* Base address of scroll 2 */
#define CPS1_SCROLL3_BASE	0x03	/* Base address of scroll 3 */
#define CPS1_OTHER_BASE 	0x04	/* Base address of other video */
#define CPS1_PALETTE_BASE	0x05	/* Base address of palette */
#define CPS1_SCROLL1_SCROLLX	0x06	/* Scroll 1 X */
#define CPS1_SCROLL1_SCROLLY	0x07	/* Scroll 1 Y */
#define CPS1_SCROLL2_SCROLLX	0x08	/* Scroll 2 X */
#define CPS1_SCROLL2_SCROLLY	0x09	/* Scroll 2 Y */
#define CPS1_SCROLL3_SCROLLX	0x0a	/* Scroll 3 X */
#define CPS1_SCROLL3_SCROLLY	0x0b	/* Scroll 3 Y */
#define CPS1_STARS1_SCROLLX	0x0c	/* Stars 1 X */
#define CPS1_STARS1_SCROLLY	0x0d	/* Stars 1 Y */
#define CPS1_STARS2_SCROLLX	0x0e	/* Stars 2 X */
#define CPS1_STARS2_SCROLLY	0x0f	/* Stars 2 Y */

#define CPS1_ROWSCROLL_OFFS	0x10	/* base of row scroll offsets in other RAM */

#define CPS1_SCROLL2_WIDTH	0x40
#define CPS1_SCROLL2_HEIGHT	0x40

#define qsound_rom (Z80RAM+0x4000)
#define qsound_decode (Z80RAM+0xc000)

static const int srcwidth = CPS1_SCROLL2_WIDTH * 0x10;
static const int srcheight = CPS1_SCROLL2_HEIGHT * 0x10;
static int scroll1xoff,scroll2xoff,scroll3xoff,sf2m3,sf2thndr;
static const int cps1_scroll1_size=0x4000;
static const int cps1_scroll2_size=0x4000;
static const int cps1_scroll3_size=0x4000;
static const int cps1_obj_size    =0x0800;
static const int cps1_other_size  =0x0800;
#define cps1_palette_entries (32*8)  /* Number colour schemes in palette */

static UINT8 *qsound_sharedram1,*qsound_sharedram2;
static UINT8 *GFX_SPR,*GFX_SPR16,*GFX_SPR32;
static UINT8 *GFX_SPR_SOLID;
static UINT8 *GFX_SPR_SOLID16,*GFX_SPR_SOLID32;
static UINT8 *cps1_gfxram,*cps1_palette,*old_palette;
static UINT8 *cps1_buffered_obj;
static UINT8 space_hack[32];
static int cps1_last_sprite_offset;	/* Offset of the last sprite */
static int cps1_layer_enabled[4];	/* Layer enabled [Y/N] */
static int cps1_stars_enabled;		/* Layer enabled [Y/N] */
//static int cps1_flip_screen;	/* Flip screen on / off unused in raine */
static int base1,base3,scrwidth,scrheight;
static int scrlx,scrly,size_code2,distort_scroll2;
static UINT32 max_sprites16,max_sprites32,max_sprites8;
static UINT32 frame_68k,default_frame; // 68k frame (in Hz)
static UINT16 pri_mask[4]; // priority masks (layers)

/********************************************************************
*
*  EEPROM
*  ======
*
*   The EEPROM is accessed by a serial protocol using the register
*   0xf1c006
*
********************************************************************/

static struct EEPROM_interface qsound_eeprom_interface =
{
	7,		/* address bits */
	8,		/* data bits */
	"0110", /*  read command */
	"0101", /* write command */
	"0111"  /* erase command */
};

struct EEPROM_interface pang3_eeprom_interface =
{
	6,		/* address bits */
	16,		/* data bits */
	"0110", /*  read command */
	"0101", /* write command */
	"0111"  /* erase command */
};

UINT16 cps1_eeprom_port_r(UINT32 offset)
{
  UINT16 bit = EEPROM_read_bit();
  return bit;
}

void cps1_eeprom_port_w(UINT32 offset,UINT16 data)
{
  /*
    bit 0 = data
    bit 6 = clock
    bit 7 = cs
  */
  EEPROM_write_bit(data & 0x01);
  EEPROM_set_cs_line((data & 0x80) ? CLEAR_LINE : ASSERT_LINE);
  EEPROM_set_clock_line((data & 0x40) ? ASSERT_LINE : CLEAR_LINE);
}

// Sound

static UINT8 cps1_sound_fade_timer;

static void qsound_banksw_w(UINT32 offset,UINT16 data)
{
  data &= 0xf;

  z80_set_data_bank(0,data);
}

/******************************************************************************/
/*									      */
/*			  PROTECTION DEVICES KTNXMAME			      */
/*									      */
/******************************************************************************/

#define GFXTYPE_SPRITES   (1<<0)
#define GFXTYPE_SCROLL1   (1<<1)
#define GFXTYPE_SCROLL2   (1<<2)
#define GFXTYPE_SCROLL3   (1<<3)
#define GFXTYPE_STARS     (1<<4)

struct gfx_range
{
	// start and end are as passed by the game (shift adjusted to be all
	// in the same scale a 8x8 tiles): they don't necessarily match the
	// position in ROM.
	int type;
	int start;
	int end;
	int bank;
};

/* Game specific data */
struct CPS1config
{
  char *name;		/* game driver name */

  /* Some games interrogate a couple of registers on bootup. */
  /* These are CPS1 board B self test checks. They wander from game to */
  /* game. */
  int cpsb_addr;	      /* CPS board B test register address */
  int cpsb_value;       /* CPS board B test register expected value */

  /* some games use as a protection check the ability to do 16-bit multiplies */
  /* with a 32-bit result, by writing the factors to two ports and reading the */
  /* result from two other ports. */
  /* It looks like this feature was introduced with 3wonders (CPSB ID = 08xx) */
  int mult_factor1;
  int mult_factor2;
  int mult_result_lo;
  int mult_result_hi;

  /* unknown registers which might be related to the multiply protection */
  int unknown1;
  int unknown2;
  int unknown3;

  int layer_control;
  int priority[4];
  /* palette control seems to be a bitmask telling if a pal bank can be updated
   * from ram or not. Still need to find a game where it's really used... */
  int palette_control;

  /* ideally, the layer enable masks should consist of only one bit, */
  /* but in many cases it is unknown which bit is which. */
  int layer_enable_mask[5];

  /* these depend on the B-board model and PAL */
  int bank_sizes[4];
  const struct gfx_range *bank_mapper;

  /* some C-boards have additional I/O for extra buttons/extra players */
  int in2_addr;
  int in3_addr;
  int out2_addr;

  int bootleg_kludge;
};

static struct CPS1config *cps1_game_config;

#define __not_applicable__	-1,-1,-1,-1,-1,-1,-1

/*                     CPSB ID    multiply protection      unknown      ctrl     priority masks   palctrl    layer enable masks  */
#define CPS_B_01      -1, 0x0000,          __not_applicable__,          0x26,{0x28,0x2a,0x2c,0x2e},0x30, {0x02,0x04,0x08,0x30,0x30}
#define CPS_B_02     0x20,0x0002,          __not_applicable__,          0x2c,{0x2a,0x28,0x26,0x24},0x22, {0x02,0x04,0x08,0x00,0x00}
#define CPS_B_03      -1, 0x0000,          __not_applicable__,          0x30,{0x2e,0x2c,0x2a,0x28},0x26, {0x20,0x10,0x08,0x00,0x00}
#define CPS_B_04     0x20,0x0004,          __not_applicable__,          0x2e,{0x26,0x30,0x28,0x32},0x2a, {0x02,0x04,0x08,0x00,0x00}
#define CPS_B_05     0x20,0x0005,          __not_applicable__,          0x28,{0x2a,0x2c,0x2e,0x30},0x32, {0x02,0x08,0x20,0x14,0x14}
#define CPS_B_11     0x32,0x0401,          __not_applicable__,          0x26,{0x28,0x2a,0x2c,0x2e},0x30, {0x08,0x10,0x20,0x00,0x00}
#define CPS_B_12     0x20,0x0402,          __not_applicable__,          0x2c,{0x2a,0x28,0x26,0x24},0x22, {0x02,0x04,0x08,0x00,0x00}
#define CPS_B_13     0x2e,0x0403,          __not_applicable__,          0x22,{0x24,0x26,0x28,0x2a},0x2c, {0x20,0x02,0x04,0x00,0x00}
#define CPS_B_14     0x1e,0x0404,          __not_applicable__,          0x12,{0x14,0x16,0x18,0x1a},0x1c, {0x08,0x20,0x10,0x00,0x00}
#define CPS_B_15     0x0e,0x0405,          __not_applicable__,          0x02,{0x04,0x06,0x08,0x0a},0x0c, {0x04,0x02,0x20,0x00,0x00}
#define CPS_B_16     0x00,0x0406,          __not_applicable__,          0x0c,{0x0a,0x08,0x06,0x04},0x02, {0x10,0x0a,0x0a,0x00,0x00}
#define CPS_B_17     0x08,0x0407,          __not_applicable__,          0x14,{0x12,0x10,0x0e,0x0c},0x0a, {0x08,0x10,0x02,0x00,0x00}
#define CPS_B_18     0x10,0x0408,          __not_applicable__,          0x1c,{0x1a,0x18,0x16,0x14},0x12, {0x10,0x08,0x02,0x00,0x00}
#define CPS_B_21_DEF 0x32,  -1,   0x00,0x02,0x04,0x06, 0x08, -1,  -1,   0x26,{0x28,0x2a,0x2c,0x2e},0x30, {0x02,0x04,0x08,0x30,0x30}	// pang3 sets layer enable to 0x26 on startup
#define CPS_B_21_BT1 0x32,0x0800, 0x0e,0x0c,0x0a,0x08, 0x06,0x04,0x02,  0x28,{0x26,0x24,0x22,0x20},0x30, {0x20,0x04,0x08,0x12,0x12}
#define CPS_B_21_BT2  -1,   -1,   0x1e,0x1c,0x1a,0x18,  -1, 0x0c,0x0a,  0x20,{0x2e,0x2c,0x2a,0x28},0x30, {0x30,0x08,0x30,0x00,0x00}
#define CPS_B_21_BT3  -1,   -1,   0x06,0x04,0x02,0x00, 0x0e,0x0c,0x0a,  0x20,{0x2e,0x2c,0x2a,0x28},0x30, {0x20,0x12,0x12,0x00,0x00}
#define CPS_B_21_BT4  -1,   -1,   0x06,0x04,0x02,0x00, 0x1e,0x1c,0x0a,  0x28,{0x26,0x24,0x22,0x20},0x30, {0x20,0x10,0x02,0x00,0x00}
#define CPS_B_21_BT5 0x32,  -1,   0x0e,0x0c,0x0a,0x08, 0x1e,0x1c,0x1a,  0x20,{0x2e,0x2c,0x2a,0x28},0x30, {0x20,0x04,0x02,0x00,0x00}
#define CPS_B_21_BT6  -1,   -1,    -1,  -1,  -1,  -1,   -1,  -1,  -1,   0x20,{0x2e,0x2c,0x2a,0x28},0x30, {0x20,0x14,0x14,0x00,0x00}
#define CPS_B_21_BT7  -1,   -1,    -1,  -1,  -1,  -1,   -1,  -1,  -1,   0x2c,{ -1,  -1,  -1,  -1 },0x12, {0x14,0x02,0x14,0x00,0x00}
#define CPS_B_21_QS1  -1,   -1,    -1,  -1,  -1,  -1,   -1,  -1,  -1,   0x22,{0x24,0x26,0x28,0x2a},0x2c, {0x10,0x08,0x04,0x00,0x00}
#define CPS_B_21_QS2  -1,   -1,    -1,  -1,  -1,  -1,   -1, 0x2e,0x20,  0x0a,{0x0c,0x0e,0x00,0x02},0x04, {0x16,0x16,0x16,0x00,0x00}
#define CPS_B_21_QS3 0x0e,0x0c00,  -1,  -1,  -1,  -1,  0x2c, -1,  -1,   0x12,{0x14,0x16,0x08,0x0a},0x0c, {0x04,0x02,0x20,0x00,0x00}
#define CPS_B_21_QS4 0x2e,0x0c01,  -1,  -1,  -1,  -1,  0x1c,0x1e,0x08,  0x16,{0x00,0x02,0x28,0x2a},0x2c, {0x04,0x08,0x10,0x00,0x00}
#define CPS_B_21_QS5 0x1e,0x0c02,  -1,  -1,  -1,  -1,  0x0c, -1,  -1,   0x2a,{0x2c,0x2e,0x30,0x32},0x1c, {0x04,0x08,0x10,0x00,0x00}
#define HACK_B_1      -1,   -1,    -1,  -1,  -1,  -1,   -1,  -1,  -1,   0x14,{0x12,0x10,0x0e,0x0c},0x0a, {0x0e,0x0e,0x0e,0x30,0x30}


/*
CPS_B_21_DEF is CPS-B-21 at default settings (no battery)
CPS_B_21_BTx are various battery configurations
CPS_B_21_QSx are various battery configurations in Q-Sound games
*/


// LWCHR and LW621 are equivalent as far as the game is concerned, though the
// equations are different

#define mapper_LWCHR	{ 0x8000, 0x8000, 0, 0 }, mapper_LWCHR_table
static const struct gfx_range mapper_LWCHR_table[] =
{
	// verified from PAL dump (PAL16P8B @ 3A):
	// bank 0 = pin 19 (ROMs 1,5,8,12)
	// bank 1 = pin 16 (ROMs 2,6,9,13)
	// pin 12 and pin 14 are always enabled (except for stars)
	// note that allowed codes go up to 0x1ffff but physical ROM is half that size

	/* type            start    end      bank */
	{ GFXTYPE_SPRITES, 0x00000, 0x07fff, 0 },
	{ GFXTYPE_SCROLL1, 0x00000, 0x1ffff, 0 },

	{ GFXTYPE_STARS,   0x00000, 0x1ffff, 1 },
	{ GFXTYPE_SCROLL2, 0x00000, 0x1ffff, 1 },
	{ GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 1 },
	{ 0 }
};

#define mapper_LW621	{ 0x8000, 0x8000, 0, 0 }, mapper_LW621_table
static const struct gfx_range mapper_LW621_table[] =
{
	// verified from PAL dump (PAL @ 1A):
	// bank 0 = pin 18
	// bank 1 = pin 14
	// pins 19, 16, 17, and 12 give an alternate half-size mapping which would
	// allow to use smaller ROMs:
	// pin 19
	// 0 00000-03fff
	// pin 16
	// 0 04000-07fff
	// 1 00000-1ffff
	// pin 17
	// 2 00000-1ffff
	// 3 00000-1ffff
	// 4 00000-1ffff
	// pin 12
	// 3 00000-1ffff
	//
	// note that allowed codes go up to 0x1ffff but physical ROM is half that size

	/* type            start    end      bank */
	{ GFXTYPE_SPRITES, 0x00000, 0x07fff, 0 },
	{ GFXTYPE_SCROLL1, 0x00000, 0x1ffff, 0 },

	{ GFXTYPE_STARS,   0x00000, 0x1ffff, 1 },
	{ GFXTYPE_SCROLL2, 0x00000, 0x1ffff, 1 },
	{ GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 1 },
	{ 0 }
};


// DM620, DM22A and DAM63B are equivalent as far as the game is concerned, though
// the equations are quite different

#define mapper_DM620	{ 0x8000, 0x2000, 0x2000, 0 }, mapper_DM620_table
static const struct gfx_range mapper_DM620_table[] =
{
	// verified from PAL dump (PAL16P8B @ 2A):
	// bank 0 = pin 19 (ROMs  5,6,7,8)
	// bank 1 = pin 16 (ROMs  9,11,13,15,18,20,22,24)
	// bank 2 = pin 14 (ROMs 10,12,14,16,19,21,23,25)
	// pin 12 is never enabled
	// note that bank 0 is enabled whenever banks 1 or 2 are not enabled,
	// which would make it highly redundant, so I'm relying on the table
	// to be scanned top to bottom and using a catch-all clause at the end.

	/* type            start   end     bank */
	{ GFXTYPE_SCROLL3, 0x8000, 0xbfff, 1 },

	{ GFXTYPE_SPRITES, 0x2000, 0x3fff, 2 },

	{ GFXTYPE_STARS | GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 0 },
	{ 0 }
};

#define mapper_DM22A	{ 0x4000, 0x4000, 0x2000, 0x2000 }, mapper_DM22A_table
static const struct gfx_range mapper_DM22A_table[] =
{
	// verified from PAL dump
	// bank 0 = pin 19
	// bank 1 = pin 16
	// bank 2 = pin 14
	// bank 3 = pin 12

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x00000, 0x01fff, 0 },
	{ GFXTYPE_SCROLL1, 0x02000, 0x03fff, 0 },

	{ GFXTYPE_SCROLL2, 0x04000, 0x07fff, 1 },

	{ GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 2 },

	{ GFXTYPE_SPRITES, 0x02000, 0x03fff, 3 },
	{ 0 }
};

#define mapper_DAM63B	{ 0x8000, 0x8000, 0, 0 }, mapper_DAM63B_table
static const struct gfx_range mapper_DAM63B_table[] =
{
	// verified from PAL dump:
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// bank1 = pin 17 (ROMs 5,7) & pin 16 (ROMs 6,8)
	// pins 12,13,14,15 are always enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x00000, 0x01fff, 0 },
	{ GFXTYPE_SCROLL1, 0x02000, 0x02fff, 0 },
	{ GFXTYPE_SCROLL2, 0x04000, 0x07fff, 0 },

	{ GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 1 },
	{ GFXTYPE_SPRITES, 0x02000, 0x03fff, 1 },
	{ 0 }
};


// ST24M1 and ST22B are equivalent except for the stars range which is
// different. This has no practical effect.

#define mapper_ST24M1	{ 0x8000, 0x8000, 0, 0 }, mapper_ST24M1_table
static const struct gfx_range mapper_ST24M1_table[] =
{
	// verified from PAL dump
	// bank 0 = pin 19 (ROMs 2,4,6,8)
	// bank 1 = pin 16 (ROMs 1,3,5,7)
	// pin 12 and pin 14 are never enabled

	/* type            start    end      bank */
	{ GFXTYPE_STARS,   0x00000, 0x003ff, 0 },
	{ GFXTYPE_SPRITES, 0x00000, 0x04fff, 0 },
	{ GFXTYPE_SCROLL2, 0x04000, 0x07fff, 0 },

	{ GFXTYPE_SCROLL3, 0x00000, 0x07fff, 1 },
	{ GFXTYPE_SCROLL1, 0x07000, 0x07fff, 1 },
	{ 0 }
};

#define mapper_ST22B	{ 0x4000, 0x4000, 0x4000, 0x4000 }, mapper_ST22B_table
static const struct gfx_range mapper_ST22B_table[] =
{
	// verified from PAL dump
	// bank 0 = pin 19 (ROMs 1,5, 9,13,17,24,32,38)
	// bank 1 = pin 16 (ROMs 2,6,10,14,18,25,33,39)
	// bank 2 = pin 14 (ROMs 3,7,11,15,19,21,26,28)
	// bank 3 = pin 12 (ROMS 4,8,12,16,20,22,27,29)

	/* type            start    end      bank */
	{ GFXTYPE_STARS,   0x00000, 0x1ffff, 0 },
	{ GFXTYPE_SPRITES, 0x00000, 0x03fff, 0 },

	{ GFXTYPE_SPRITES, 0x04000, 0x04fff, 1 },
	{ GFXTYPE_SCROLL2, 0x04000, 0x07fff, 1 },

	{ GFXTYPE_SCROLL3, 0x00000, 0x03fff, 2 },

	{ GFXTYPE_SCROLL3, 0x04000, 0x07fff, 3 },
	{ GFXTYPE_SCROLL1, 0x07000, 0x07fff, 3 },
	{ 0 }
};


#define mapper_TK22B	{ 0x4000, 0x4000, 0x4000, 0x4000 }, mapper_TK22B_table
static const struct gfx_range mapper_TK22B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 1,5, 9,13,17,24,32,38)
	// bank 1 = pin 16 (ROMs 2,6,10,14,18,25,33,39)
	// bank 2 = pin 14 (ROMs 3,7,11,15,19,21,26,28)
	// bank 3 = pin 12 (ROMS 4,8,12,16,20,22,27,29)

	/* type            start  end      bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x3fff, 0 },

	{ GFXTYPE_SPRITES, 0x4000, 0x5fff, 1 },
	{ GFXTYPE_SCROLL1, 0x6000, 0x7fff, 1 },

	{ GFXTYPE_SCROLL3, 0x0000, 0x3fff, 2 },

	{ GFXTYPE_SCROLL2, 0x4000, 0x7fff, 3 },
	{ 0 }
};


#define mapper_WL24B	{ 0x8000, 0x8000, 0, 0 }, mapper_WL24B_table
static const struct gfx_range mapper_WL24B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// bank 1 = pin 12 (ROMs 10,12,14,16,20,22,24,26)
	// pin 14 and pin 19 are never enabled

	/* type            start  end      bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x4fff, 0 },
	{ GFXTYPE_SCROLL3, 0x5000, 0x6fff, 0 },
	{ GFXTYPE_SCROLL1, 0x7000, 0x7fff, 0 },

	{ GFXTYPE_SCROLL2, 0x0000, 0x3fff, 1 },
	{ 0 }
};


#define mapper_S224B	{ 0x8000, 0, 0, 0 }, mapper_S224B_table
static const struct gfx_range mapper_S224B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// pin 12 & pin 14 give an alternate half-size mapping which would allow to
	// populate the 8-bit ROM sockets instead of the 16-bit ones:
	// pin 12
	// 0 00000 - 03fff
	// pin 14
	// 0 04000 - 043ff
	// 1 04400 - 04bff
	// 2 06000 - 07fff
	// 3 04c00 - 05fff
	// pin 19 is never enabled

	/* type            start  end      bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x43ff, 0 },
	{ GFXTYPE_SCROLL1, 0x4400, 0x4bff, 0 },
	{ GFXTYPE_SCROLL3, 0x4c00, 0x5fff, 0 },
	{ GFXTYPE_SCROLL2, 0x6000, 0x7fff, 0 },
	{ 0 }
};


#define mapper_YI24B	{ 0x8000, 0, 0, 0 }, mapper_YI24B_table
static const struct gfx_range mapper_YI24B_table[] =
{
	// verified from JED:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// pin 12 & pin 14 give an alternate half-size mapping which would allow to
	// populate the 8-bit ROM sockets instead of the 16-bit ones:
	// pin 12
	// 0 0000-1fff
	// 3 2000-3fff
	// pin 14
	// 1 4000-47ff
	// 2 4800-7fff
	// pin 19 is never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x1fff, 0 },
	{ GFXTYPE_SCROLL3, 0x2000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL1, 0x4000, 0x47ff, 0 },
	{ GFXTYPE_SCROLL2, 0x4800, 0x7fff, 0 },
	{ 0 }
};


// AR24B and AR22B are equivalent, but since we could dump both PALs we are
// documenting both.

#define mapper_AR24B	{ 0x8000, 0, 0, 0 }, mapper_AR24B_table
static const struct gfx_range mapper_AR24B_table[] =
{
	// verified from JED:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// pin 12 & pin 14 give an alternate half-size mapping which would allow to
	// populate the 8-bit ROM sockets instead of the 16-bit ones:
	// pin 12
	// 0 0000-2fff
	// 1 3000-3fff
	// pin 14
	// 2 4000-5fff
	// 3 6000-7fff
	// pin 19 is never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL1, 0x3000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL2, 0x4000, 0x5fff, 0 },
	{ GFXTYPE_SCROLL3, 0x6000, 0x7fff, 0 },
	{ 0 }
};

#define mapper_AR22B	{ 0x4000, 0x4000, 0, 0 }, mapper_AR22B_table
static const struct gfx_range mapper_AR22B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 1,5, 9,13,17,24,32,38)
	// bank 1 = pin 16 (ROMs 2,6,10,14,18,25,33,39)
	// pins 12 and 14 are tristated

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL1, 0x3000, 0x3fff, 0 },

	{ GFXTYPE_SCROLL2, 0x4000, 0x5fff, 1 },
	{ GFXTYPE_SCROLL3, 0x6000, 0x7fff, 1 },
	{ 0 }
};


#define mapper_O224B	{ 0x8000, 0x4000, 0, 0 }, mapper_O224B_table
static const struct gfx_range mapper_O224B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 2,4,6,8)
	// bank 1 = pin 12 (ROMs 10,12,14,16,20,22,24,26)
	// pin 16 & pin 14 appear to be an alternate half-size mapping for bank 0
	// but scroll1 is missing:
	// pin 16
	// 2 00c00 - 03bff
	// 3 03c00 - 03fff
	// pin 14
	// 3 04000 - 04bff
	// 0 04c00 - 07fff

	/* type            start   end     bank */
	{ GFXTYPE_SCROLL1, 0x0000, 0x0bff, 0 },
	{ GFXTYPE_SCROLL2, 0x0c00, 0x3bff, 0 },
	{ GFXTYPE_SCROLL3, 0x3c00, 0x4bff, 0 },
	{ GFXTYPE_SPRITES, 0x4c00, 0x7fff, 0 },

	{ GFXTYPE_SPRITES, 0x8000, 0xa7ff, 1 },
	{ GFXTYPE_SCROLL2, 0xa800, 0xb7ff, 1 },
	{ GFXTYPE_SCROLL3, 0xb800, 0xbfff, 1 },
	{ 0 }
};


#define mapper_MS24B	{ 0x8000, 0, 0, 0 }, mapper_MS24B_table
static const struct gfx_range mapper_MS24B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// pin 14 duplicates pin 16 allowing to populate the 8-bit ROM sockets
	// instead of the 16-bit ones.
	// pin 12 is enabled only for sprites:
	// 0 0000-3fff
	// pin 19 is never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL1, 0x4000, 0x4fff, 0 },
	{ GFXTYPE_SCROLL2, 0x5000, 0x6fff, 0 },
	{ GFXTYPE_SCROLL3, 0x7000, 0x7fff, 0 },
	{ 0 }
};


#define mapper_CK24B	{ 0x8000, 0, 0, 0 }, mapper_CK24B_table
static const struct gfx_range mapper_CK24B_table[] =
{
	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL1, 0x3000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL2, 0x4000, 0x6fff, 0 },
	{ GFXTYPE_SCROLL3, 0x7000, 0x7fff, 0 },
	{ 0 }
};


#define mapper_NM24B	{ 0x8000, 0, 0, 0 }, mapper_NM24B_table
static const struct gfx_range mapper_NM24B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// pin 12 & pin 14 give an alternate half-size mapping which would allow to
	// populate the 8-bit ROM sockets instead of the 16-bit ones:
	// pin 12
	// 0 00000 - 03fff
	// 2 00000 - 03fff
	// pin 14
	// 1 04000 - 047ff
	// 0 04800 - 067ff
	// 2 04800 - 067ff
	// 3 06800 - 07fff
	// pin 19 is never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL2, 0x0000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL1, 0x4000, 0x47ff, 0 },
	{ GFXTYPE_SPRITES, 0x4800, 0x67ff, 0 },
	{ GFXTYPE_SCROLL2, 0x4800, 0x67ff, 0 },
	{ GFXTYPE_SCROLL3, 0x6800, 0x7fff, 0 },
	{ 0 }
};


// CA24B and CA22B are equivalent, but since we could dump both PALs we are
// documenting both.

#define mapper_CA24B	{ 0x8000, 0, 0, 0 }, mapper_CA24B_table
static const struct gfx_range mapper_CA24B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// pin 12 & pin 14 give an alternate half-size mapping which would allow to
	// populate the 8-bit ROM sockets instead of the 16-bit ones:
	// pin 12
	// 0 0000-2fff
	// 2 0000-2fff
	// 3 3000-3fff
	// pin 14
	// 3 4000-4fff
	// 1 5000-57ff
	// 0 5800-7fff
	// 2 5800-7fff
	// pin 19 is never enabled (actually it is always enabled when PAL pin 1 is 1, purpose unknown)

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL2, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL3, 0x3000, 0x4fff, 0 },
	{ GFXTYPE_SCROLL1, 0x5000, 0x57ff, 0 },
	{ GFXTYPE_SPRITES, 0x5800, 0x7fff, 0 },
	{ GFXTYPE_SCROLL2, 0x5800, 0x7fff, 0 },
	{ 0 }
};

#define mapper_CA22B	{ 0x4000, 0x4000, 0, 0 }, mapper_CA22B_table
static const struct gfx_range mapper_CA22B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 1,5, 9,13,17,24,32,38)
	// bank 1 = pin 16 (ROMs 2,6,10,14,18,25,33,39)
	// pin 12 and pin 14 are never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL2, 0x0000, 0x2fff, 0 },
	{ GFXTYPE_SCROLL3, 0x3000, 0x3fff, 0 },

	{ GFXTYPE_SCROLL3, 0x4000, 0x4fff, 1 },
	{ GFXTYPE_SCROLL1, 0x5000, 0x57ff, 1 },
	{ GFXTYPE_SPRITES, 0x5800, 0x7fff, 1 },
	{ GFXTYPE_SCROLL2, 0x5800, 0x7fff, 1 },
	{ 0 }
};


#define mapper_STF29	{ 0x8000, 0x8000, 0x8000, 0 }, mapper_STF29_table
static const struct gfx_range mapper_STF29_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 5,6,7,8)
	// bank 1 = pin 14 (ROMs 14,15,16,17)
	// bank 2 = pin 12 (ROMS 24,25,26,27)

	/* type            start    end      bank */
	{ GFXTYPE_SPRITES, 0x00000, 0x07fff, 0 },

	{ GFXTYPE_SPRITES, 0x08000, 0x0ffff, 1 },

	{ GFXTYPE_SPRITES, 0x10000, 0x11fff, 2 },
	{ GFXTYPE_SCROLL3, 0x02000, 0x03fff, 2 },
	{ GFXTYPE_SCROLL1, 0x04000, 0x04fff, 2 },
	{ GFXTYPE_SCROLL2, 0x05000, 0x07fff, 2 },
	{ 0 }
};



// RT24B and RT22B are equivalent, but since we could dump both PALs we are
// documenting both.

#define mapper_RT24B	{ 0x8000, 0x8000, 0, 0 }, mapper_RT24B_table
static const struct gfx_range mapper_RT24B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 16 (ROMs 1,3,5,7)
	// bank 1 = pin 19 (ROMs 2,4,6,8)
	// pin 12 & pin 14 are never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x53ff, 0 },
	{ GFXTYPE_SCROLL1, 0x5400, 0x6fff, 0 },
	{ GFXTYPE_SCROLL3, 0x7000, 0x7fff, 0 },

	{ GFXTYPE_SCROLL3, 0x0000, 0x3fff, 1 },
	{ GFXTYPE_SCROLL2, 0x2800, 0x7fff, 1 },
	{ GFXTYPE_SPRITES, 0x5400, 0x7fff, 1 },
	{ 0 }
};

#define mapper_RT22B	{ 0x4000, 0x4000, 0x4000, 0x4000 }, mapper_RT22B_table
static const struct gfx_range mapper_RT22B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 1,5, 9,13,17,24,32,38)
	// bank 1 = pin 16 (ROMs 2,6,10,14,18,25,33,39)
	// bank 2 = pin 14 (ROMs 3,7,11,15,19,21,26,28)
	// bank 3 = pin 12 (ROMS 4,8,12,16,20,22,27,29)

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x3fff, 0 },

	{ GFXTYPE_SPRITES, 0x4000, 0x53ff, 1 },
	{ GFXTYPE_SCROLL1, 0x5400, 0x6fff, 1 },
	{ GFXTYPE_SCROLL3, 0x7000, 0x7fff, 1 },

	{ GFXTYPE_SCROLL3, 0x0000, 0x3fff, 2 },
	{ GFXTYPE_SCROLL2, 0x2800, 0x3fff, 2 },

	{ GFXTYPE_SCROLL2, 0x4000, 0x7fff, 3 },
	{ GFXTYPE_SPRITES, 0x5400, 0x7fff, 3 },
	{ 0 }
};


#define mapper_KD29B	{ 0x8000, 0x8000, 0, 0 }, mapper_KD29B_table
static const struct gfx_range mapper_KD29B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 1,2,3,4)
	// bank 1 = pin 14 (ROMs 10,11,12,13)
	// pin 12 is never enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x7fff, 0 },

	{ GFXTYPE_SPRITES, 0x8000, 0x8fff, 1 },
	{ GFXTYPE_SCROLL2, 0x9000, 0xbfff, 1 },
	{ GFXTYPE_SCROLL1, 0xc000, 0xd7ff, 1 },
	{ GFXTYPE_SCROLL3, 0xd800, 0xffff, 1 },
	{ 0 }
};


#define mapper_CC63B	{ 0x8000, 0x8000, 0, 0 }, mapper_CC63B_table
static const struct gfx_range mapper_CC63B_table[] =
{
	// verified from PAL dump:
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// bank1 = pin 17 (ROMs 5,7) & pin 16 (ROMs 6,8)
	// pins 12,13,14,15 are always enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x7fff, 0 },
	{ GFXTYPE_SCROLL2, 0x0000, 0x7fff, 0 },

	{ GFXTYPE_SPRITES, 0x8000, 0xffff, 1 },
	{ GFXTYPE_SCROLL1, 0x8000, 0xffff, 1 },
	{ GFXTYPE_SCROLL2, 0x8000, 0xffff, 1 },
	{ GFXTYPE_SCROLL3, 0x8000, 0xffff, 1 },
	{ 0 }
};


#define mapper_KR63B	{ 0x8000, 0x8000, 0, 0 }, mapper_KR63B_table
static const struct gfx_range mapper_KR63B_table[] =
{
	// verified from PAL dump:
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// bank1 = pin 17 (ROMs 5,7) & pin 16 (ROMs 6,8)
	// pins 12,13,14,15 are always enabled

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x7fff, 0 },
	{ GFXTYPE_SCROLL2, 0x0000, 0x7fff, 0 },

	{ GFXTYPE_SCROLL1, 0x8000, 0x9fff, 1 },
	{ GFXTYPE_SPRITES, 0x8000, 0xcfff, 1 },
	{ GFXTYPE_SCROLL2, 0x8000, 0xcfff, 1 },
	{ GFXTYPE_SCROLL3, 0xd000, 0xffff, 1 },
	{ 0 }
};


#define mapper_S9263B	{ 0x8000, 0x8000, 0x8000, 0 }, mapper_S9263B_table
static const struct gfx_range mapper_S9263B_table[] =
{
	// verified from PAL dump:
	// FIXME there is some problem with this dump since pin 14 is never enabled
	// instead of being the same as pin 15 as expected
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// bank1 = pin 17 (ROMs 5,7) & pin 16 (ROMs 6,8)
	// bank2 = pin 15 (ROMs 10,12) & pin 14 (ROMs 11,13)
	// pins 12 and 13 are the same as 14 and 15

	/* type            start    end      bank */
	{ GFXTYPE_SPRITES, 0x00000, 0x07fff, 0 },

	{ GFXTYPE_SPRITES, 0x08000, 0x0ffff, 1 },

	{ GFXTYPE_SPRITES, 0x10000, 0x11fff, 2 },
	{ GFXTYPE_SCROLL3, 0x02000, 0x03fff, 2 },
	{ GFXTYPE_SCROLL1, 0x04000, 0x04fff, 2 },
	{ GFXTYPE_SCROLL2, 0x05000, 0x07fff, 2 },
	{ 0 }
};


// VA22B and VA63B are equivalent, but since we could dump both PALs we are
// documenting both.

#define mapper_VA22B	{ 0x4000, 0x4000, 0, 0 }, mapper_VA22B_table
static const struct gfx_range mapper_VA22B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19 (ROMs 1,5, 9,13,17,24,32,38)
	// bank 1 = pin 16 (ROMs 2,6,10,14,18,25,33,39)
	// pin 12 and pin 14 are never enabled

	/* type                                                                  start    end      bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x03fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x04000, 0x07fff, 1 },
	{ 0 }
};

#define mapper_VA63B	{ 0x8000, 0, 0, 0 }, mapper_VA63B_table
static const struct gfx_range mapper_VA63B_table[] =
{
	// verified from PAL dump (PAL # uncertain):
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// pins 12,13,14,15,16,17 are never enabled

	/* type                                                                  start    end      bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x07fff, 0 },
	{ 0 }
};


#define mapper_Q522B	{ 0x8000, 0, 0, 0 }, mapper_Q522B_table
static const struct gfx_range mapper_Q522B_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x0000, 0x6fff, 0 },
	{ GFXTYPE_SCROLL3,                   0x7000, 0x77ff, 0 },
	{ GFXTYPE_SCROLL1,                   0x7800, 0x7fff, 0 },
	{ 0 }
};


#define mapper_TK263B	{ 0x8000, 0x8000, 0, 0 }, mapper_TK263B_table
static const struct gfx_range mapper_TK263B_table[] =
{
	// verified from PAL dump:
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// bank1 = pin 17 (ROMs 5,7) & pin 16 (ROMs 6,8)
	// pins 12,13,14,15 are always enabled

	/* type                                                                  start    end      bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x07fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x08000, 0x0ffff, 1 },
	{ 0 }
};


#define mapper_CD63B	{ 0x8000, 0x8000, 0, 0 }, mapper_CD63B_table
static const struct gfx_range mapper_CD63B_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SCROLL1,                   0x0000, 0x0fff, 0 },
	{ GFXTYPE_SPRITES,                   0x1000, 0x7fff, 0 },

	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x8000, 0xdfff, 1 },
	{ GFXTYPE_SCROLL3,                   0xe000, 0xffff, 1 },
	{ 0 }
};


#define mapper_PS63B	{ 0x8000, 0x8000, 0, 0 }, mapper_PS63B_table
static const struct gfx_range mapper_PS63B_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SCROLL1,                   0x0000, 0x0fff, 0 },
	{ GFXTYPE_SPRITES,                   0x1000, 0x7fff, 0 },

	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x8000, 0xdbff, 1 },
	{ GFXTYPE_SCROLL3,                   0xdc00, 0xffff, 1 },
	{ 0 }
};


#define mapper_MB63B	{ 0x8000, 0x8000, 0x8000, 0 }, mapper_MB63B_table
static const struct gfx_range mapper_MB63B_table[] =
{
	/* type                              start    end      bank */
	{ GFXTYPE_SCROLL1,                   0x00000, 0x00fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x01000, 0x07fff, 0 },

	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x08000, 0x0ffff, 1 },

	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x10000, 0x167ff, 2 },
	{ GFXTYPE_SCROLL3,                   0x16800, 0x17fff, 2 },
	{ 0 }
};


#define mapper_QD22B	{ 0x4000, 0, 0, 0 }, mapper_QD22B_table
static const struct gfx_range mapper_QD22B_table[] =
{
	// verified from PAL dump:
	// bank 0 = pin 19

	/* type            start   end     bank */
	{ GFXTYPE_SPRITES, 0x0000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL1, 0x0000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL2, 0x0000, 0x3fff, 0 },
	{ GFXTYPE_SCROLL3, 0x0000, 0x3fff, 0 },
	{ 0 }
};

#define mapper_QAD63B   { 0x8000, 0, 0, 0 }, mapper_QAD63B_table
static const struct gfx_range mapper_QAD63B_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SCROLL1,                   0x0000, 0x07ff, 0 },
	{ GFXTYPE_SCROLL3,                   0x0800, 0x1fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x2000, 0x7fff, 0 },
	{ 0 }
};

#define mapper_TN2292   { 0x8000, 0x8000, 0, 0 }, mapper_TN2292_table
static const struct gfx_range mapper_TN2292_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SCROLL1,                   0x0000, 0x0fff, 0 },
	{ GFXTYPE_SCROLL3,                   0x1000, 0x3fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x4000, 0x7fff, 0 },

	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x8000, 0xffff, 1 },
	{ 0 }
};

#define mapper_RCM63B	{ 0x8000, 0x8000, 0x8000, 0x8000 }, mapper_RCM63B_table
static const struct gfx_range mapper_RCM63B_table[] =
{
	// verified from PAL dump:
	// bank0 = pin 19 (ROMs 1,3) & pin 18 (ROMs 2,4)
	// bank1 = pin 17 (ROMs 5,7) & pin 16 (ROMs 6,8)
	// bank0 = pin 15 (ROMs 10,12) & pin 14 (ROMs 11,13)
	// bank1 = pin 13 (ROMs 14,16) & pin 12 (ROMs 15,17)

	/* type                                                                  start    end      bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x07fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x08000, 0x0ffff, 1 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x10000, 0x17fff, 2 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x18000, 0x1ffff, 3 },
	{ 0 }
};

#define mapper_PKB10B   { 0x8000, 0, 0, 0 }, mapper_PKB10B_table
static const struct gfx_range mapper_PKB10B_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SCROLL1,                   0x0000, 0x0fff, 0 },
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x1000, 0x5fff, 0 },
	{ GFXTYPE_SCROLL3,                   0x6000, 0x7fff, 0 },
	{ 0 }
};



#define mapper_pang3	{ 0x8000, 0x8000, 0, 0 }, mapper_pang3_table
static const struct gfx_range mapper_pang3_table[] =
{
	/* type                              start   end     bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x0000, 0x7fff, 0 },

	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL2, 0x8000, 0x9fff, 1 },
	{ GFXTYPE_SCROLL1,                   0xa000, 0xbfff, 1 },
	{ GFXTYPE_SCROLL3,                   0xc000, 0xffff, 1 },
	{ 0 }
};


#define mapper_sfzch	{ 0x20000, 0, 0, 0 }, mapper_sfzch_table
static const struct gfx_range mapper_sfzch_table[] =
{
	/* type                                                                  start    end      bank */
	{ GFXTYPE_SPRITES | GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 0 },
	{ 0 }
};

/*
  I don't know if CPS2 ROM boards use PALs as well; since all games seem to be
  well behaved, I'll just assume that there is no strong checking of gfx type.
  (sprites are not listed here because they are addressed linearly by the CPS2
  sprite code)
 */
#define mapper_cps2	{ 0x20000, 0x20000, 0, 0 }, mapper_cps2_table
static const struct gfx_range mapper_cps2_table[] =
{
	/* type                                                start    end      bank */
	{ GFXTYPE_SCROLL1 | GFXTYPE_SCROLL2 | GFXTYPE_SCROLL3, 0x00000, 0x1ffff, 1 },	// 20000-3ffff physical
	{ 0 }
};

static struct CPS1config cps1_config_table[]=
{
	/* name         CPSB          gfx mapper   in2  in3  out2   kludge */
	{"forgottn",    CPS_B_01,     mapper_LW621 },
	{"forgottnu",   CPS_B_01,     mapper_LW621 },
	{"forgottnu1",  CPS_B_01,     mapper_LWCHR },
	{"forgottnua",  CPS_B_01,     mapper_LWCHR },
	{"forgottnuaa", CPS_B_01,     mapper_LWCHR },
	{"lostwrld",    CPS_B_01,     mapper_LWCHR },
	{"lostwrldo",   CPS_B_01,     mapper_LWCHR },
	{"ghouls",      CPS_B_01,     mapper_DM620 },
	{"ghoulsu",     CPS_B_01,     mapper_DM620 },
	{"daimakai",    CPS_B_01,     mapper_DM22A },   // equivalent to DM620
	{"daimakair",   CPS_B_21_DEF, mapper_DAM63B },  // equivalent to DM620, also CPS_B_21_DEF is equivalent to CPS_B_01
	{"daimakr2",   CPS_B_21_DEF, mapper_DAM63B },  // equivalent to DM620, also CPS_B_21_DEF is equivalent to CPS_B_01
	{"strider",     CPS_B_01,     mapper_ST24M1 },
	{"striderua",   CPS_B_01,     mapper_ST24M1 },  // wrong, this set uses ST24B2, still not dumped
	{"striderj",    CPS_B_01,     mapper_ST22B },   // equivalent to ST24M1
	{"striderjr",   CPS_B_21_DEF, mapper_ST24M1 },  // wrong, this set uses STH63B, still not dumped
	{"dynwar",      CPS_B_02,     mapper_TK22B },   // wrong, this set uses TK24B1, dumped but equations still not added
	{"dynwaru",     CPS_B_02,     mapper_TK22B },
	{"dynwara",     CPS_B_02,     mapper_TK22B },
	{"dynwarj",     CPS_B_02,     mapper_TK22B },
	{"dynwarjr",    CPS_B_21_DEF, mapper_TK22B },   // wrong, this set uses TK163B, still not dumped
	{"willow",      CPS_B_03,     mapper_WL24B },
	{"willowo",     CPS_B_03,     mapper_WL24B },
	{"willowj",     CPS_B_03,     mapper_WL24B },   // wrong, this set uses WL22B, still not dumped
	{"ffight",      CPS_B_04,     mapper_S224B },
	{"ffighta",     CPS_B_04,     mapper_S224B },
	{"ffightu",     CPS_B_04,     mapper_S224B },
	{"ffightu1",    CPS_B_04,     mapper_S224B },
	{"ffightua",    CPS_B_01,     mapper_S224B },
	{"ffightub",    CPS_B_05,     mapper_S224B },
	{"ffightj",     CPS_B_04,     mapper_S224B },   // wrong, this set uses S222B, still not dumped
	{"ffightj1",    CPS_B_01,     mapper_S224B },   // wrong, this set uses S222B, still not dumped
	{"ffightj2",    CPS_B_02,     mapper_S224B },   // wrong, this set uses S222B, still not dumped
	{"ffightjh",    CPS_B_01,     mapper_S224B },   // wrong, ffightjh hack doesn't even use the S222B PAL, since replaced with a GAL.
	{"1941",        CPS_B_05,     mapper_YI24B },
	{"1941r1",      CPS_B_05,     mapper_YI24B },
	{"1941u",       CPS_B_05,     mapper_YI24B },
	{"1941j",       CPS_B_05,     mapper_YI24B },   // wrong, this set uses YI22B, still not dumped
	{"unsquad",     CPS_B_11,     mapper_AR24B },
	{"area88",      CPS_B_11,     mapper_AR22B },   // equivalent to AR24B
	{"area88r",     CPS_B_21_DEF, mapper_AR22B },   // wrong, this set uses ARA63B, still not dumped
	{"mercs",       CPS_B_12,     mapper_O224B,  0x36, 0, 0x34 },
	{"mercsu",      CPS_B_12,     mapper_O224B,  0x36, 0, 0x34 },
	{"mercsur1",    CPS_B_12,     mapper_O224B,  0x36, 0, 0x34 },
	{"mercsj",      CPS_B_12,     mapper_O224B,  0x36, 0, 0x34 },   // wrong, this set uses O222B, still not dumped
	{"msword",      CPS_B_13,     mapper_MS24B },
	{"mswordr1",    CPS_B_13,     mapper_MS24B },
	{"mswordu",     CPS_B_13,     mapper_MS24B },
	{"mswordj",     CPS_B_13,     mapper_MS24B },   // wrong, this set uses MS22B, still not dumped
	{"mtwins",      CPS_B_14,     mapper_CK24B },
	{"chikij",      CPS_B_14,     mapper_CK24B },   // wrong, this set uses CK22B, still not dumped
	{"nemo",        CPS_B_15,     mapper_NM24B },
	{"nemoj",       CPS_B_15,     mapper_NM24B },   // wrong, this set uses NM22B, still not dumped
	{"cawing",      CPS_B_16,     mapper_CA24B },
	{"cawingr1",    CPS_B_16,     mapper_CA24B },
	{"cawingu",     CPS_B_16,     mapper_CA24B },
	{"cawingj",     CPS_B_16,     mapper_CA22B },   // equivalent to CA24B
	{"cawingbl",    CPS_B_16,     mapper_CA22B },   // equivalent to CA24B
	{"sf2",         CPS_B_11,     mapper_STF29,  0x36 },
	{"sf2eb",       CPS_B_17,     mapper_STF29,  0x36 },
	{"sf2ee",       CPS_B_18,     mapper_STF29,  0x3c },
	{"sf2ebbl",     CPS_B_17,     mapper_STF29,  0x36, 0, 0, 1  },
	{"sf2stt",      CPS_B_17,     mapper_STF29,  0x36, 0, 0, 1  },
	{"sf2rk",       CPS_B_17,     mapper_STF29,  0x36, 0, 0, 1  },
	{"sf2ua",       CPS_B_17,     mapper_STF29,  0x36 },
	{"sf2ub",       CPS_B_17,     mapper_STF29,  0x36 },
	{"sf2uc",       CPS_B_12,     mapper_STF29,  0x36 },
	{"sf2ud",       CPS_B_05,     mapper_STF29,  0x36 },
	{"sf2ue",       CPS_B_18,     mapper_STF29,  0x3c },
	{"sf2uf",       CPS_B_15,     mapper_STF29,  0x36 },
	{"sf2ug",       CPS_B_11,     mapper_STF29,  0x36 },
	{"sf2ui",       CPS_B_14,     mapper_STF29,  0x36 },
	{"sf2uk",       CPS_B_17,     mapper_STF29,  0x36 },
	{"sf2j",        CPS_B_13,     mapper_STF29,  0x36 },
	{"sf2ja",       CPS_B_17,     mapper_STF29,  0x36 },
	{"sf2jc",       CPS_B_12,     mapper_STF29,  0x36 },
	{"sf2qp1",      CPS_B_17,     mapper_STF29,  0x36 },
	{"sf2thndr",    CPS_B_17,     mapper_STF29,  0x36 },

	/* from here onwards the CPS-B board has suicide battery and multiply protection */

	{"3wonders",    CPS_B_21_BT1, mapper_RT24B },
	{"3wondersr1",  CPS_B_21_BT1, mapper_RT24B },
	{"3wondersu",   CPS_B_21_BT1, mapper_RT24B },
	{"wonder3",     CPS_B_21_BT1, mapper_RT22B },   // equivalent to RT24B
	{"3wondersh",   CPS_B_02    , mapper_RT24B },   /* Not 100% sure of the CPS B-ID */
	{"kod",         CPS_B_21_BT2, mapper_KD29B,  0x36, 0, 0x34 },
	{"kodr1",       CPS_B_21_BT2, mapper_KD29B,  0x36, 0, 0x34 },
	{"kodu",        CPS_B_21_BT2, mapper_KD29B,  0x36, 0, 0x34 },
	{"kodj",        CPS_B_21_BT2, mapper_KD29B,  0x36, 0, 0x34 },
	{"kodja",       CPS_B_21_BT2, mapper_KD29B,  0x36, 0, 0x34 },   // wrong, this set uses KD22B, still not dumped
	{"kodb",        CPS_B_21_BT2, mapper_KD29B,  0x36, 0, 0x34 },   /* bootleg, doesn't use multiply protection */
	{"captcomm",    CPS_B_21_BT3, mapper_CC63B,  0x36, 0x38, 0x34 },
	{"captcommr1",  CPS_B_21_BT3, mapper_CC63B,  0x36, 0x38, 0x34 },
	{"captcommu",   CPS_B_21_BT3, mapper_CC63B,  0x36, 0x38, 0x34 },
	{"captcommj",   CPS_B_21_BT3, mapper_CC63B,  0x36, 0x38, 0x34 },
	{"captcommjr1", CPS_B_21_BT3, mapper_CC63B,  0x36, 0x38, 0x34 },
	{"captcommb",   CPS_B_21_BT3, mapper_CC63B,  0x36, 0x38, 0x34 },
	{"knights",     CPS_B_21_BT4, mapper_KR63B,  0x36, 0, 0x34 },
	{"knightsu",    CPS_B_21_BT4, mapper_KR63B,  0x36, 0, 0x34 },
	{"knightsj",    CPS_B_21_BT4, mapper_KR63B,  0x36, 0, 0x34 },
	{"knightsja",   CPS_B_21_BT4, mapper_KR63B,  0x36, 0, 0x34 },   // wrong, this set uses KR22B, still not dumped
	//{"knightsb",    CPS_B_21_BT4, mapper_KR63B,  0x36, 0, 0x34 },   // wrong, knightsb bootleg doesn't use the KR63B PAL
	{"sf2ce",       CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2ceea",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2ceua",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2ceub",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2ceuc",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2ceja",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2cejb",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2cejc",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2rb",       CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2rb2",      CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2rb3",      CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2red",      CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2v004",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2acc",      CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2acca",     CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2accp2",    CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2amf",      CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 }, // probably wrong but this set is not completely dumped anyway
	{"sf2dkot2",    CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2m1",       CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2m2",       CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2m3",       HACK_B_1,     mapper_S9263B, 0,    0, 0, 2 },
	{"sf2m4",       HACK_B_1,     mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2m5",       CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2m6",       CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2m7",       CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2m8",       HACK_B_1,     mapper_S9263B, 0,    0, 0, 2 },
	{"sf2dongb",    CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2yyc",      CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2koryu",    CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2mdt",      CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"sf2mdta",     CPS_B_21_DEF, mapper_S9263B, 0x36, 0, 0, 1 },
	{"varth",       CPS_B_04,     mapper_VA63B },   /* CPSB test has been patched out (60=0008) register is also written to, possibly leftover from development */  // wrong, this set uses VA24B, dumped but equations still not added
	{"varthr1",     CPS_B_04,     mapper_VA63B },   /* CPSB test has been patched out (60=0008) register is also written to, possibly leftover from development */  // wrong, this set uses VA24B, dumped but equations still not added
	{"varthu",      CPS_B_04,     mapper_VA63B },   /* CPSB test has been patched out (60=0008) register is also written to, possibly leftover from development */
	{"varthj",      CPS_B_21_BT5, mapper_VA22B },   /* CPSB test has been patched out (72=0001) register is also written to, possibly leftover from development */
	{"cworld2j",    CPS_B_21_BT6, mapper_Q522B,  0x36, 0, 0x34 },   /* (ports 36, 34 probably leftover input code from another game) */
	{"wof",         CPS_B_21_QS1, mapper_TK263B },
	{"wofr1",       CPS_B_21_DEF, mapper_TK263B },
	{"wofa",        CPS_B_21_DEF, mapper_TK263B },
	{"wofu",        CPS_B_21_QS1, mapper_TK263B },
	{"wofj",        CPS_B_21_QS1, mapper_TK263B },
	{"wofhfh",      CPS_B_21_DEF, mapper_TK263B, 0x36 },    /* Chinese bootleg */
	{"dino",        CPS_B_21_QS2, mapper_CD63B },   /* layer enable never used */
	{"dinou",       CPS_B_21_QS2, mapper_CD63B },   /* layer enable never used */
	{"dinoj",       CPS_B_21_QS2, mapper_CD63B },   /* layer enable never used */
	{"dinopic",     CPS_B_21_QS2, mapper_CD63B },   /* layer enable never used */
	{"dinopic2",    CPS_B_21_QS2, mapper_CD63B },   /* layer enable never used */
	{"dinohunt",    CPS_B_21_DEF, mapper_CD63B },   /* Chinese bootleg */
	{"punisher",    CPS_B_21_QS3, mapper_PS63B },
	{"punisheru",   CPS_B_21_QS3, mapper_PS63B },
	{"punisherh",   CPS_B_21_QS3, mapper_PS63B },
	{"punisherj",   CPS_B_21_QS3, mapper_PS63B },
	{"punipic",     CPS_B_21_QS3, mapper_PS63B },
	{"punipic2",    CPS_B_21_QS3, mapper_PS63B },
	{"punipic3",    CPS_B_21_QS3, mapper_PS63B },
	{"punisherbz",  CPS_B_21_DEF, mapper_PS63B },   /* Chinese bootleg */
	{"slammast",    CPS_B_21_QS4, mapper_MB63B },
	{"slammastu",   CPS_B_21_QS4, mapper_MB63B },
	{"mbomberj",    CPS_B_21_QS4, mapper_MB63B },
	{"mbombrd",     CPS_B_21_QS5, mapper_MB63B },
	{"mbombrdj",    CPS_B_21_QS5, mapper_MB63B },
	{"sf2hf",       CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2hfu",      CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"sf2hfj",      CPS_B_21_DEF, mapper_S9263B, 0x36 },
	{"qad",         CPS_B_21_BT7, mapper_QD22B,  0x36 },    /* TODO: layer enable (port 36 probably leftover input code from another game) */
	{"qadjr",       CPS_B_21_DEF, mapper_QAD63B, 0x36, 0x38, 0x34 },    /* (ports 36, 38, 34 probably leftover input code from another game) */
	{"qtono2j",     CPS_B_21_DEF, mapper_TN2292, 0x36, 0x38, 0x34 },    /* (ports 36, 38, 34 probably leftover input code from another game) */
	{"megaman",     CPS_B_21_DEF, mapper_RCM63B },
	{"megamana",    CPS_B_21_DEF, mapper_RCM63B },
	{"rockmanj",    CPS_B_21_DEF, mapper_RCM63B },
	{"pnickj",      CPS_B_21_DEF, mapper_PKB10B },
	{"pang3",       CPS_B_21_DEF, mapper_pang3 },   /* EEPROM port is among the CPS registers (handled by DRIVER_INIT) */   // should use one of these three CP1B1F,CP1B8K,CP1B9KA still not dumped
	{"pang3r1",     CPS_B_21_DEF, mapper_pang3 },   /* EEPROM port is among the CPS registers (handled by DRIVER_INIT) */   // should use one of these three CP1B1F,CP1B8K,CP1B9K
	{"pang3j",      CPS_B_21_DEF, mapper_pang3 },   /* EEPROM port is among the CPS registers (handled by DRIVER_INIT) */   // should use one of these three CP1B1F,CP1B8K,CP1B9K
	{"pang3b",      CPS_B_21_DEF, mapper_pang3 },   /* EEPROM port is among the CPS registers (handled by DRIVER_INIT) */   // should use one of these three CP1B1F,CP1B8K,CP1B9K
	{"ganbare",     CPS_B_21_DEF, mapper_sfzch },   // wrong, this set uses GBPR2, still not dumped

	/* CPS Changer */

	{"sfach",       CPS_B_21_DEF, mapper_sfzch },   // wrong, this set uses an unknown PAL, still not dumped
	{"sfzbch",      CPS_B_21_DEF, mapper_sfzch },   // wrong, this set uses an unknown PAL, still not dumped
	{"sfzch",       CPS_B_21_DEF, mapper_sfzch },   // wrong, this set uses an unknown PAL, still not dumped
	{"wofch",       CPS_B_21_DEF, mapper_TK263B },

	/* CPS2 games */

	{"cps2",        CPS_B_21_DEF, mapper_cps2 },

	{0}     /* End of table */
};

static UINT16 cps1_port[0x100],scroll2x,scroll2y;

static void cps1_find_last_sprite(void)    /* Find the offset of last sprite */
{
    int offset=0;
	/* Locate the end of table marker */
    while (offset < cps1_obj_size)
	{
	UINT8 colour=cps1_buffered_obj[offset+7];
		if (colour == 0xff)
		{
		  /* Marker found. This is the last sprite. */
		  cps1_last_sprite_offset=offset-8;
			return;
		}
	offset+=8;
	}
	/* Sprites must use full sprite RAM */
    cps1_last_sprite_offset=cps1_obj_size-8;
}

static INLINE UINT8 *cps1_base(int offset,int boundary)
{
	int base=cps1_port[offset]*256;
	/*
	The scroll RAM must start on a 0x4000 boundary.
	Some games do not do this.
	For example:
	   Captain commando	- continue screen will not display
	   Muscle bomber games	- will animate garbage during gameplay
	Mask out the irrelevant bits.
	*/
	base &= ~(boundary-1);
	return &cps1_gfxram[(base&0x3ffff)];
}

static UINT16 oldx,oldx2,oldy2;

typedef struct {
  int start,end;
  int base,mask;
} trange[3];
static trange scroll1_ranges,scroll2_ranges,scroll3_ranges,sprites_ranges;
static int nb_scroll1,nb_scroll2,nb_scroll3,nb_sprites;

static int gfxrom_bank_mapper(int type, trange ranges )
{
  const struct gfx_range *range = cps1_game_config->bank_mapper;
  int nb = 0;

/*  switch (type)
  {
    case GFXTYPE_SPRITES: shift = 1; break;
    case GFXTYPE_SCROLL1: shift = 0; break;
    case GFXTYPE_SCROLL2: shift = 1; break;
    case GFXTYPE_SCROLL3: shift = 3; break;
  } */

  while (range->type)
  {
/*    if (code >= range->start && code <= range->end)
    { */
      if (range->type & type)
      {
	int base = 0;
	int i;

	for (i = 0; i < range->bank; ++i)
	  base += cps1_game_config->bank_sizes[i];

	ranges[nb].start = range->start;
	ranges[nb].end   = range->end;
	ranges[nb].base  = base;
	ranges[nb].mask  = cps1_game_config->bank_sizes[range->bank] - 1;
	nb++;
//	return (base + (code & (cps1_game_config->bank_sizes[range->bank] - 1))) >> shift;
      }
//    }

    ++range;
  }

  return nb;
}

static int pbitmap_needed,no_pbitmap = 0;

static void cps1_init_machine(void)
{
  const char *gamename = current_game->main_name;
   struct CPS1config *pCFG=&cps1_config_table[0];
   int n;
   int size = get_region_size(REGION_GFX1); // size of packed region
   int max_sprites16 = size*2 / 0x100;
   int sf2ee;
   // memset(&input_buffer[0x1a],0xff,0x20);
   input_buffer[5] = 0xff; // for cawing, freezes after loading weapon otherwise
   no_pbitmap = !strncmp(gamename,"xmcot",5); // xmcota and clones

   input_buffer[0x15] &= ~16;
   cps1_sound_fade_timer = 0xff;
   size_code2 = get_region_size(REGION_ROM2);

   sf2ee = is_current_game("sf2ee") || is_current_game("sf2ue");
   sf2thndr = is_current_game("sf2thndr");
   oldx2 = oldx = 0xffff; // To have scroll1x != oldx

   while(pCFG->name)
   {
      if (is_current_game(pCFG->name))
      {
	 break;
      }
      pCFG++;
   }
   cps1_game_config=pCFG;

   if (!cps1_game_config->name)
     {
       gamename=_("cps2");
       pCFG=&cps1_config_table[0];
       while(pCFG->name)
	 {
	   if (strcmp(pCFG->name, gamename) == 0)
	     {
	       break;
	     }
	   pCFG++;
	 }
       cps1_game_config=pCFG;
     }

   /* Adjust the offsets : mame references some B registers, but I'd like to
    * keep the usual registers, so I must | 0x40 all their offsets... */
   int offset = 0x40;
   if (sf2ee)
       offset = 0xc0;
   cps1_game_config->cpsb_addr |= offset;
   cps1_game_config->mult_factor1 |= offset;
   cps1_game_config->mult_factor2 |= offset;
   cps1_game_config->mult_result_lo |= offset;
   cps1_game_config->mult_result_hi |= offset;
   cps1_game_config->layer_control |= offset;
   for (n=0; n<4; n++)
     cps1_game_config->priority[n] |= offset;
   cps1_game_config->palette_control |= offset;
   // The inx_addr must keep the 0x100 offset because they are read as bytes
   cps1_game_config->in2_addr |= 0x100 + offset;
   cps1_game_config->in3_addr |= 0x100 + offset;

   if (!strncmp(gamename,"forgott",7) ||
       !strncmp(gamename,"lostwrld",8)) // forgottn has digital input
     GameMouse=1;

   if (is_current_game("sf2rb"))
   {
      /* Patch out protection check */
      UINT16 *rom = (UINT16 *)load_region[REGION_ROM1];
      WriteWord68k(&rom[0xe5464/2], 0x6012);
   }

   if (is_current_game("sf2accp2"))
   {
      /* Patch out a odd branch which would be incorrectly interpreted
	 by the cpu core as a 32-bit branch. This branch would make the
	 game crash (address error, since it would branch to an odd address)
	 if location 180ca6 (outside ROM space) isn't 0. Protection check? */

      UINT16 *rom = (UINT16 *)load_region[REGION_ROM1];
      WriteWord68k(&rom[0x11756/2],0x4e71);
   }
   if (strcmp(gamename, "sf2rb2" )==0)
   {
     /* Patch out protection check */
     UINT16 *rom = (UINT16 *)load_region[REGION_ROM1];
     rom[0xe5332/2] = 0x6014;
   }


/*   base2 = cps1_game_config->bank_scroll2*0x04000;
   base1 = cps1_game_config->bank_scroll1*0x08000;
   base3 = cps1_game_config->bank_scroll3*0x01000; */
   nb_scroll1 = gfxrom_bank_mapper(GFXTYPE_SCROLL1,scroll1_ranges);
   base1 = scroll1_ranges[0].base;
   max_sprites8 = 0;
   for (n=0; n<nb_scroll1; n++) {
     scroll1_ranges[n].base -= base1;
     max_sprites8 = MAX(max_sprites8,(scroll1_ranges[n].base+scroll1_ranges[n].end));
   }
   max_sprites8++;
   // There is no need to change the base for scroll2 & sprites because
   // we keep the whole 16x16 layer.
   nb_scroll2 = gfxrom_bank_mapper(GFXTYPE_SCROLL2,scroll2_ranges);
   nb_scroll3 = gfxrom_bank_mapper(GFXTYPE_SCROLL3,scroll3_ranges);
   base3 = scroll3_ranges[0].base >> 3;
   for (n=1; n<nb_scroll3; n++)
     base3 = MIN(base3,(scroll3_ranges[0].base >> 3));
   max_sprites32 = 0;
   for (n=0; n<nb_scroll3; n++) {
     scroll3_ranges[n].base -= base3 << 3;
     max_sprites32 = MAX(max_sprites32,((scroll3_ranges[n].base+scroll3_ranges[n].end) >> 3));
   }
   max_sprites32++;
   max_sprites8 = MIN( max_sprites8, (size / 0x40 - base1));
   max_sprites32 = MIN(max_sprites32,(max_sprites16/4 - base3));
   nb_sprites = gfxrom_bank_mapper(GFXTYPE_SPRITES,sprites_ranges);

   scrwidth = current_game->video->screen_x+32;
   scrheight= current_game->video->screen_y+32;
   /* Put in some defaults */
   /* Apparently some games do not initialise completely and need these */
   /* defaults (captcomm)  */
   cps1_port[CPS1_OBJ_BASE]	  = 0x9200;
   cps1_port[CPS1_SCROLL1_BASE] = 0x9000;
   cps1_port[CPS1_SCROLL2_BASE] = 0x9040;
   cps1_port[CPS1_SCROLL3_BASE] = 0x9080;
   cps1_port[CPS1_OTHER_BASE]   = 0x9100;
   cps1_port[CPS1_PALETTE_BASE] = 0x90c0;
   for (n = 0;n < 4;n++)
     if (cps1_game_config->priority[n])
       cps1_port[(cps1_game_config->priority[n]/2)] = 0;
}

static int pang3;

static UINT16 protection_rw(UINT32 offset)
{
    // printf("protection_rw %x\n",offset);
    if (sf2thndr && offset >= 0xc0/2) // mirrored
	offset -= 0x80/2;
  /* Some games interrogate a couple of registers on bootup. */
  /* These are CPS1 board B self test checks. They wander from game to */
  /* game. */
  if (offset && offset == cps1_game_config->cpsb_addr/2) {
    return cps1_game_config->cpsb_value;
  }

   /* some games use as a protection check the ability to do 16-bit multiplies */
   /* with a 32-bit result, by writing the factors to two ports and reading the */
   /* result from two other ports. */
  if (offset && offset == cps1_game_config->mult_result_lo/2) {
    return (cps1_port[cps1_game_config->mult_factor1/2] *
	    cps1_port[cps1_game_config->mult_factor2/2]);
  }
  if (offset && offset == cps1_game_config->mult_result_hi/2) {
    return (cps1_port[cps1_game_config->mult_factor1/2] *
	    cps1_port[cps1_game_config->mult_factor2/2]) >> 16;
  }

   if (pang3 && offset == 0x7a/2)
      return cps1_eeprom_port_r(0);

   if (offset == 0x28) {
       // Hack for the rasters, the phoenix bootlegs wait for scanline 262 here
       // at boot...
       static int res;
       if (res)
	   res = 0;
       else
	   res = 262;
       return res;
   }

   return cps1_port[offset];
}

static void protection_ww(UINT32 offset, UINT16 data)
{
    if (sf2thndr && offset >= 0xc0/2) // mirrored
	offset -= 0x80/2;
   // printf("protection_ww %x,%x\n",offset*2-0x40,data);
   /* Pang 3 EEPROM interface */
   if (pang3 && offset == 0x7a/2)
   {
      cps1_eeprom_port_w(0,data);
      return;
   }

   if (sf2m3 && offset == 0xc4/2)
       cps1_port[cps1_game_config->layer_control/2] = data;
   else if (sf2m3 && offset >= 0xa0/2 && offset < 0xc4/2) {
       cps1_port[offset - 0xa0/2] = data;
   } else {
       // printf("cps1_port_w %x,%x pang3 %x\n",offset*2,data,pang3);
       cps1_port[offset] = data;
   }
   //data = COMBINE_DATA(&cps1_port[offset]);

}

static int dial[2]; // forgottn stuff

static void cps1_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x1FF;
   // printf("ioc_wb %x,%x\n",offset,data);
   if ((offset >= 0x188 && offset <= 0x18f) ||
	   (sf2m3 && offset >= 0x198 && offset <= 0x19f)) {
     cps1_sound_fade_timer = data;
   } else if ((offset >= 0x180 && offset <= 0x187) ||
	   (sf2m3 && offset >= 0x190 && offset <= 0x197)) {
     soundcmd_wb_nonmi(0,data);
   } else if (offset == 0x41) {
     /* Remarquable : this was probably never tested. dial[0] seems to be the
	position at rest. So it must be constant throughout the game or it's impossible
	to control it with the keyboard !!! */
     // dial[0] = ReadWord(&input_buffer[5*2]);
   } else if (offset == 0x49)
     dial[1] = input_buffer[6*2];
#ifdef RAINE_DEBUG
   else if (offset != 0x30 && offset != 0x31)
     fprintf(stderr,"UNKNOWN %x\n",offset);
#endif
   // Curiosity : it would seem the adresses 0x100 and above (ports) are
   // never accessed by byte (always by word).
}

static void cps1_ioc_ww(UINT32 offset, UINT16 data)
{
   offset &= 0x1FF;
   // printf("ioc_ww %x,%x\n",offset,data);
   if ((offset >= 0x188 && offset <= 0x18f) ||
	   (sf2m3 && offset >= 0x198 && offset <= 0x19f) ) {
     cps1_sound_fade_timer = data & 0xff;
   } else if ((offset >= 0x180 && offset <= 0x187) ||
	   (sf2m3 && offset >= 0x190 && offset <= 0x197)) {
     soundcmd_wb_nonmi(0,data);
   } else if (offset >= 0x100)
      protection_ww((offset - 0x100)>>1, data);
   else if (offset == 0x40) {
     dial[0] = ReadWord(&input_buffer[5*2]);
   } else if (offset == 0x48)
     dial[1] = input_buffer[6*2];
   else {
     print_debug("cps1_ioc_ww unmapped %x\n",offset);
   }
}

static UINT16 cps1_input2_r(UINT32 offset)
{
  int buttons=input_buffer[4];

  return (buttons << 8) | buttons;
}

static UINT16 cps1_input3_r(UINT32 offset)
{
  int buttons=input_buffer[6];
  return (buttons << 8) | buttons;
}

static UINT8 cps1_ioc_rb(UINT32 offset)
{
   offset &= 0x1FF;
    // printf("ioc_rb %x\n",offset);
   // I love byte accesses using starscream, they require the ^ 1 in the end
   // and games like sf2ce insist on reading the 2 bytes !
    if (abs(offset - cps1_game_config->in2_addr) <= 1)
	return input_buffer[(4+offset - cps1_game_config->in2_addr) ^ 1];
    else if (abs(offset - cps1_game_config->in3_addr) <= 1)
	return input_buffer[(6+offset - cps1_game_config->in3_addr) ^ 1];
    else if (sf2m3 && abs(offset - 0x186) <= 1)
	return input_buffer[5];
    else if (sf2m3 && (offset == 0x10 || offset == 0x11))
	return input_buffer[(2+offset-0x10)^1];
   if (offset <= 7 && !sf2m3) {
       offset = (offset & 1) ^ 1;
       return input_buffer[2+offset];
   } else if ((!sf2m3 && offset >= 0x18 && offset <= 0x1f) ||
	   (sf2m3 && offset >= 0x28 && offset <= 0x2f)) {
       if (sf2m3) offset -= 0x10;
       if (offset < 0x1a) offset -= 0x18; // input_buffer[0], then dsw
       offset &= (~1);
       return input_buffer[offset];
   }   else if (offset >= 0x100) {
     int ret = protection_rw((offset - 0x100)>>1);
     if (offset & 1) return ret & 0xff;
     else return ret >> 8;
   } else {
     print_debug("cps1_ioc_rb unmapped %x\n",offset);
   }
   return 0xFF;
}

static UINT16 cps1_ioc_rw(UINT32 offset)
{
    offset &= 0x1FF;
    // printf("ioc_rw %x\n",offset);

    if(offset < 0x100) {
	if (offset == cps1_game_config->in2_addr)
	    return ReadWord(&input_buffer[4]);
	else if (offset == cps1_game_config->in3_addr)
	    return ReadWord(&input_buffer[7]); // input port 3
	if (offset <= 7)
	    return ReadWord(&input_buffer[2]);
	else if ((!sf2m3 && offset >= 0x18 && offset <= 0x1f) ||
		(sf2m3 && offset >= 0x28 && offset <= 0x2f)) {
	    UINT8 input;
	    if (sf2m3) offset -= 0x10;
	    if (offset < 0x1a) offset -= 0x18; // input_buffer[0], then dsw
	    input = input_buffer[offset];
	    return input | (input << 8);
	} else if (offset == 0x52 || offset == 0x5a) {
	    return (ReadWord(&input_buffer[5*2]) - dial[0]) & 0xff;
	} else if (offset == 0x54 || offset == 0x5c) {
	    return ((ReadWord(&input_buffer[5*2]) - dial[0]) >> 8) & 0xff;
	}

	else {
	    print_debug("cps1_ioc_rw unmapped %x\n",offset);
	    return 0xFFFF;
	}
    } else {
	return protection_rw((offset - 0x100)>>1);
    }
}

static UINT8 *RAM_SCROLL1,*RAM_SCROLL2,*RAM_SCROLL3;
static INT16 *RAM_LSCROLL;

static int layer_id_data[4];

static char *layer_id_name[4] =
{
   "OBJECT", "SCROLL1", "SCROLL2", "SCROLL3",
};

static int hack_counter,max_hack_counter,z80_speed_hack;

static UINT16 sf2dongb_rw(UINT32 offset) {
    if (offset == 0x180000 || offset == 0x180000+0x77040)
	return 0x0210;
    return 0;
}

void finish_conf_cps1()
{
   AddZ80AInit();
   max_hack_counter = 22;
   z80_speed_hack = 0;

   int size_code = get_region_size(REGION_CPU1);
   if (is_current_game("sf2dongb"))
       AddReadWord(0x180000, 0x1fffff, sf2dongb_rw, NULL);
   AddMemFetch(size_code, size_code+32, space_hack - size_code);
   print_debug("space_hack mapped at %x\n",size_code);
   AddReadBW(size_code, size_code+32, NULL, space_hack);

   finish_conf_68000(0);
   RAM_SCROLL1 = NULL; // Init after the 1st frame...
   AddSaveData(SAVE_USER_1, (UINT8 *)&cps1_port, sizeof(UINT16)*0x100);
   AddSaveData(SAVE_USER_2, (UINT8 *)&latch, sizeof(int));
   if (!strcmp(current_game->main_name,"sf2rb2")) {
     /* Patch out protection check */
     UINT16 *rom = (UINT16 *)load_region[REGION_ROM1];
     WriteWord(&rom[0xe5332/2],0x6014);
   }

   // To access sfzch dips you must write this :
   // WriteWord(&ROM[0x152c],0x4e75);
   // But since the test mode seems disabled (the memory area is not tested)
   // I disable it. Demo sound, flip screen and maybe allow continue are
   // working though.
     if (cps1_game_config->bootleg_kludge == 1)
     {
       cps1_port[CPS1_OBJ_BASE] = 0x9100;
	 scroll1xoff = -0x0c;
	 scroll2xoff = -0x0e;
	 scroll3xoff = -0x10;
     } else if (cps1_game_config->bootleg_kludge == 2) {
	 // sf2m3 and co...
	 cps1_port[CPS1_OBJ_BASE] = 0x9100;
	 scroll1xoff = -0x0c;
	 scroll2xoff = -0x10;
	 scroll3xoff = -0x10;
     } else
       {
	 scroll1xoff = 0;
	 scroll2xoff = 0;
	 scroll3xoff = 0;
       }
}

static void cps1_set_z80()
{
   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

/*    Z80ROM[0x95]=0xD3; // OUTA (AAh) */
/*    Z80ROM[0x96]=0xAA; // */

   z80_init_banks(0,REGION_ROM2,0x8000,0x4000);

   AddZ80AReadByte(0x0000, 0xbfFF, NULL, NULL); // Z80 ROM + BANKS
   AddZ80AReadByte(0xd000, 0xd7ff, NULL, Z80RAM);

   AddZ80AReadByte(0xf001, 0xf001, YM2151_status_port_0_r, NULL);
   AddZ80AReadByte(0xf002, 0xf002, OKIM6295_status_0_r, NULL);
   AddZ80AReadByte(0xf008, 0xf008, NULL, (UINT8*)&latch);
   AddZ80AReadByte(0xf00a, 0xf00a, NULL, &cps1_sound_fade_timer);

   // kodb
   AddZ80AReadByte(0xe001, 0xe001, YM2151_data_port_0_w,   NULL);
   AddZ80AReadByte(0xe002, 0xe002, OKIM6295_status_0_r, NULL);
   AddZ80AReadByte(0xe008, 0xe008, NULL, (UINT8*)&latch);

   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);

   AddZ80AWriteByte(0xd000, 0xd7FF, NULL,			Z80RAM);

   AddZ80AWriteByte(0xf000, 0xf000, YM2151_register_port_0_w,	NULL);
   AddZ80AWriteByte(0xf001, 0xf001, YM2151_data_port_0_w,   NULL);
   AddZ80AWriteByte(0xf002, 0xf002, OKIM6295_data_0_w,	 NULL);
   AddZ80AWriteByte(0xf004, 0xf004, z80a_set_bank,   NULL);

   // kodb
   AddZ80AWriteByte(0xe000, 0xe000, YM2151_register_port_0_w,	NULL);
   AddZ80AWriteByte(0xe001, 0xe001, YM2151_data_port_0_w,   NULL);
   AddZ80AWriteByte(0xe002, 0xe002, OKIM6295_data_0_w,	 NULL);
   AddZ80AWriteByte(0xe004, 0xe004, z80a_set_bank,   NULL);

   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
}

static int cps_version;

static void qsound_set_z80()
{
  qsound_sharedram1 = Z80RAM;
  qsound_sharedram2 = Z80RAM + 0x1000;
  if (is_current_game("gigaman2")) {
      return;
  }
  z80_init_data_banks(0,REGION_ROM2,0x0,0x4000); // The rom seems to be counted as banks !

  if (cps_version==2) {
    AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
  } else
    AddZ80AROMBase(qsound_decode, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7fff, NULL, Z80ROM); // ROM (data decoded)
   AddZ80AReadByte(0x8000, 0xbfFF, NULL, NULL); // Z80 bank (data)

   AddZ80AReadByte(0xc000, 0xcfff, NULL, Z80RAM);
   AddZ80AReadByte(0xd007, 0xd007, qsound_status_r, NULL);
   // AddZ80AReadByte(0xf200, 0xf23f, my_read, NULL); //Z80RAM+0x1000 );
   AddZ80AReadByte(0xf000, 0xffff, NULL, Z80RAM+0x1000); // );
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);

   AddZ80AWriteByte(0xc000, 0xcfFf, NULL, Z80RAM);
   AddZ80AWriteByte(0xd000, 0xd000, qsound_data_h_w,   NULL);
   AddZ80AWriteByte(0xd001, 0xd001, qsound_data_l_w,   NULL);
//   AddZ80AWriteByte(0xd002, 0xd002, qsound_cmd_w,   NULL);

   if ((!strncmp(current_game->main_name,"punish",6)) ||
       (!strncmp(current_game->main_name,"mbombrd",7)))
     AddZ80AWriteByte(0xd002, 0xd002, qsound_cmd_w3,   NULL);
   else
     AddZ80AWriteByte(0xd002, 0xd002, qsound_cmd_w1,   NULL);

   AddZ80AWriteByte(0xd003, 0xd003, qsound_banksw_w,   NULL);
   AddZ80AWriteByte(0xf000, 0xffff, NULL,   Z80RAM+0x1000);
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
}

static int cps2_reset_ready;

static void cps2_reset() {
  const ROMSW_INFO *romsw_src;
  int region,ta;
  cps2_reset_ready = 0;

  ta=0;

  romsw_src = current_game->romsw;

  // copy the region switch from the data rom to the decoded rom
  if(romsw_src){
    while(romsw_src[ta].data){
      region = gen_cpu_read_byte(romsw_src[ta].offset);
      gen_cpu_write_byte(romsw_src[ta].offset,region);
      ta++;
    }
  }

  undo_hack();
}

static void myStop68000(UINT32 adr, UINT8 data) {
  if (hack_counter++ >= max_hack_counter) {
    Stop68000(0,0);
  }
}

/* static void my_stop_z80(UINT32 offset, UINT16 data) { */
/*   if (Z80RAM[1] == Z80RAM[2]) { */
/*     z80pc = 0x8e; */
/*     mz80ReleaseTimeslice(); */
/*   } */
/* } */

/* All the decoding stuff is directly from mame, thanks to them ! */
static void cps1_gfx_decode(UINT8 *cps1_gfx, int size) {
  int i,j;
  size /= 4;
  for (i = 0;i < size;i++)
    {
      UINT32 src = cps1_gfx[4*i] + (cps1_gfx[4*i+1]<<8) + (cps1_gfx[4*i+2]<<16) + (cps1_gfx[4*i+3]<<24);
      UINT32 dwval = 0;

      for (j = 0;j < 8;j++)
	{
	  int n = 0;
	  UINT32 mask = (0x80808080 >> j) & src;

	  if (mask & 0x000000ff) n |= 1;
	  if (mask & 0x0000ff00) n |= 2;
	  if (mask & 0x00ff0000) n |= 4;
	  if (mask & 0xff000000) n |= 8;

	  dwval |= n << (j * 4);
	}
      cps1_gfx[4*i  ] = dwval>>0;
      cps1_gfx[4*i+1] = dwval>>8;
      cps1_gfx[4*i+2] = dwval>>16;
      cps1_gfx[4*i+3] = dwval>>24;

    }
}

static void unshuffle(UINT64 *buf,int len)
{
  int i;
  UINT64 t;

  if (len == 2) return;

  if (len % 4) exit(1);   /* must not happen */

  len /= 2;

  unshuffle(buf,len);
  unshuffle(buf + len,len);

  for (i = 0;i < len/2;i++)
    {
      t = buf[len/2 + i];
      buf[len/2 + i] = buf[len + i];
      buf[len + i] = t;
    }
}

static void cps2_gfx_decode(void)
{
  const int banksize=0x200000;
  int size=get_region_size(REGION_GFX1);
  int i;

  for (i = 0;i < size;i += banksize)
    unshuffle((UINT64 *)(load_region[REGION_GFX1] + i),banksize/8);

  cps1_gfx_decode(load_region[REGION_GFX1],size);
}

const int cps2_obj_size    =0x2000;
static UINT8 *cps2_output, *cps2_objram1, *cps2_objram2, *cps2_objram_bank;
static UINT16 cps2_qsound_volume;

static UINT8 *cps2_buffered_obj;
static int pri_ctrl;				/* Sprite layer priorities */
static int cps2_last_sprite_offset;     /* Offset of the last sprite */

#define CPS2_OBJ_BASE	0x00	/* Unknown (not base address of objects). Could be bass address of bank used when object swap bit set? */
#define CPS2_OBJ_UK1	0x02	/* Unknown (nearly always 0x807d, or 0x808e when screen flipped) */
#define CPS2_OBJ_PRI	0x04	/* Layers priorities */
#define CPS2_OBJ_UK2	0x06	/* Unknown (usually 0x0000, 0x1101 in ssf2, 0x0001 in 19XX) */
#define CPS2_OBJ_XOFFS	0x08	/* X offset (usually 0x0040) */
#define CPS2_OBJ_YOFFS	0x0a	/* Y offset (always 0x0010) */

static INLINE UINT16 cps2_port(int offset)
{
  return ReadWord(&cps2_output[offset]);
}

struct COLOUR_MAPPER *color_mapper;

void load_common(int cps2)
{
   UINT32 ta,size;
   UINT32 *dest;
   int size_code;
   int rotate_screen = (current_game->video->flags) & 3;
   old_palette = NULL;

   set_reset_function(cps2_reset);
   RAMSize=0x80000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if (!(cps1_buffered_obj = AllocateMem(cps1_obj_size))) return;

   memset(cps1_buffered_obj,0,cps1_obj_size);

   if (cps2) {
     cps2_buffered_obj = AllocateMem (cps2_obj_size);
     if (!cps2_buffered_obj)
       return;
     memset(cps2_buffered_obj, 0x00, cps2_obj_size);
     color_mapper = &col_map_nnnn_rrrr_gggg_bbbb_cps2;
     cps_version = 2;
   } else {
     color_mapper = &col_map_nnnn_rrrr_gggg_bbbb_cps1;
     cps_version = 1;
   }

   cps1_gfxram = RAM+0x010000;
   Z80RAM=RAM+0x70000;

   memset(Z80RAM, 0x00, 0x10000);

   // No ports !
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);

   //AddZ80AWritePort(0xAA, 0xAA, my_stop_z80,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   GFX_SPR = load_region[REGION_GFX1];
   size = get_region_size(REGION_GFX1); // size of packed region

   load_message(_("Decoding GFX layer"));
   if (cps2)
     cps2_gfx_decode();
   else
     cps1_gfx_decode(GFX_SPR,size);

   cps1_init_machine();

   load_message(_("Rebuilding 16x16 layer"));
   /* We can't use base2 to save memory on GFX_SPR16 because it's shared with sprites ! */
   // printf("size of GFX_SPR16 %d Mb\n",size*2/1024/1024);
   GFX_SPR16 = AllocateMem(size*2);
   if (!GFX_SPR16) return;

   for(ta=0;ta<size;ta++)
   {
     GFX_SPR[ta] ^= 0xff;
     // Unpack 16x16 sprites (and 32x32)
     GFX_SPR16[(ta<<1)] = GFX_SPR[ta] & 0xf;
     GFX_SPR16[(ta<<1)+1] = GFX_SPR[ta] >> 4;
   }

   if (rotate_screen) {
     /* Need to separate 32x32 sprites for rotation... */
     /* This is a terrible waste of memory, but at least it allows more speed */
     GFX_SPR32 = AllocateMem(max_sprites32*32*32);
     if (!GFX_SPR32) return;
     memcpy(GFX_SPR32,GFX_SPR16+base3*32*32,max_sprites32*32*32);
   } else
     GFX_SPR32 = &GFX_SPR16[base3*32*32];

   /* rebuild 8x8 sprites */
   load_message(_("Rebuilding 8x8 layer"));
   /* Reallocating gfx_spr is useless : packed is twice the size, but it skips 8 pixels
      every 16 pixels, so in the end it's exactly the same size ! */
   // GFX_SPR = AllocateMem(size);
   FreeMem(GFX_SPR);
   GFX_SPR = load_region[REGION_GFX1] = AllocateMem(max_sprites8*8*8);
   if (!GFX_SPR) return;
   dest= (UINT32*)GFX_SPR;

   for (ta=8+base1 *8*8*2; ta <8+(base1+max_sprites8)*8*8*2; ta+=16) {
     *dest++ = ReadLong(&GFX_SPR16[ta]);
     *dest++ = ReadLong(&GFX_SPR16[ta+4]);
   }

   max_sprites16 = size*2 / 0x100;

   load_message(_("Transparent masks / rotation"));
   GFX_SPR_SOLID = make_solid_mask_8x8(GFX_SPR, max_sprites8);
   GFX_SPR_SOLID16 = make_solid_mask_16x16(GFX_SPR16, max_sprites16);
   GFX_SPR_SOLID32 = make_solid_mask_32x32(GFX_SPR32, max_sprites32);

   layer_id_data[0] = add_layer_info(layer_id_name[0]);
   layer_id_data[1] = add_layer_info(layer_id_name[1]);
   layer_id_data[2] = add_layer_info(layer_id_name[2]);
   layer_id_data[3] = add_layer_info(layer_id_name[3]);

   memset(RAM+0x00000,0x00,0x80000);

   speed_hack = 0; // Not found yet...
   frame_68k = CPU_FRAME_MHz(32,60); // 32 Mhz at the begining...

   if (cps2)
     return; // 68k memory map totally different !
/*
 *  StarScream Main 68000 Setup
 */
   size_code = get_region_size(REGION_ROM1);
   ByteSwap(ROM, size_code );

     if (is_current_game("pang3") || is_current_game("pang3r1") ||
	     is_current_game("pang3j")) {
       // never noticed the encryption !!!
       // this code comes from mame...
	UINT16 *rom = (UINT16 *)memory_region(REGION_CPU1);
	int A;
	UINT16 src,dst;
	for (A = 0x80000;A < 0x100000;A += 2)
	{
		/* only the low 8 bits of each word are encrypted */
		src = rom[A/2];
		dst = src & 0xff00;
		if ( src & 0x01) dst ^= 0x04;
		if ( src & 0x02) dst ^= 0x21;
		if ( src & 0x04) dst ^= 0x01;
		if (~src & 0x08) dst ^= 0x50;
		if ( src & 0x10) dst ^= 0x40;
		if ( src & 0x20) dst ^= 0x06;
		if ( src & 0x40) dst ^= 0x08;
		if (~src & 0x80) dst ^= 0x88;
		rom[A/2] = dst;
	}
     }

   AddResetHandler(&quiet_reset_handler);

   AddMemFetch(0x000000, size_code-1, ROM+0x000000-0x000000);
   AddReadBW(0x000000, size_code-1, NULL, ROM+0x000000);		 // 68000 ROM

   // Slammaster is executing some code at ff94be. I declare the whole ram
   // area as executable...
   AddMemFetch(0xff0000, 0xffffff, RAM+0x000000-0xff0000);
   AddRWBW(0xFF0000, 0xFFFFFF, NULL, RAM+0x000000);		    // 68000 RAM
   AddRWBW(0x900000, 0x92FFFF, NULL, cps1_gfxram);

   AddReadBW(0xf1c000, 0xf1c001, cps1_input2_r, NULL);
   AddReadBW(0xf1c002, 0xf1c003, cps1_input3_r, NULL);

   AddReadByte(0x800000, 0x8001FF, cps1_ioc_rb, NULL);			// IOC

   AddReadWord(0x800000, 0x8001FF, cps1_ioc_rw, NULL);			// IOC
   AddReadWord(0xf1c006, 0xf1c007, cps1_eeprom_port_r, NULL); // eeprom

   AddWriteByte(0x800000, 0x8001FF, cps1_ioc_wb, NULL); 		// IOC
   AddWriteByte(0xAA0000, 0xAA0001, myStop68000, NULL);			// Trap Idle 68000

   AddWriteWord(0x800000, 0x8001FF, cps1_ioc_ww, NULL); 		// IOC
   AddWriteWord(0xf1c006, 0xf1c007, cps1_eeprom_port_w, NULL);
}

void load_cps1()
{
    sf2m3 = 0;
   if (!strncmp(current_game->main_name, "pang3",5)) {
       // Pang3 & clones
     pang3 = 1;
     EEPROM_init(&pang3_eeprom_interface);
     load_eeprom();

   } else if (is_current_game("wofhfh") || is_current_game("dinohunt") ||
	   is_current_game("punisherbz")) {
       pang3 = 1;
     EEPROM_init(&qsound_eeprom_interface);
     load_eeprom();
   }

  load_common(0);
  if (load_error) return;

  cps1_set_z80();

  AddMemFetch(0x900000, 0x92ffff, cps1_gfxram+0x000000-0x900000);
  finish_conf_cps1();
  z80a_set_bank(0,0);
}

void load_cps1_10() {
    default_frame = CPU_FRAME_MHz(10,60);
    load_cps1();
}

void load_cps1_12() {
    default_frame = CPU_FRAME_MHz(12,60);
    load_cps1();
}

void load_sf2m3() {
    load_cps1_12();
    sf2m3 = 1;
}

void load_sf2m8() {
    UINT8 *grom = load_region[REGION_GFX1];
    UINT8 *urom = load_region[REGION_USER2];
    int i = 0x480000, j = 0;

    for (j = 0x20000; j < 0x80000; j+=2)
    {
	grom[i++] = urom[j];
	grom[i++] = urom[j|0x100000];
	grom[i++] = urom[j|0x000001];
	grom[i++] = urom[j|0x100001];
	grom[i++] = urom[j|0x080000];
	grom[i++] = urom[j|0x180000];
	grom[i++] = urom[j|0x080001];
	grom[i++] = urom[j|0x180001];
    }
    load_sf2m3();
}

unsigned char *rom;
UINT8 *qsd;

static void cps1_decode(int swap_key1,int swap_key2,int addr_key,int xor_key)
{
  unsigned char *backup = qsound_rom;
  rom = load_region[REGION_ROM2];
  qsd = qsound_decode;

  /* the main CPU can read the ROM and checksum it to verify that it hasn't been */
  /* replaced with a decrypted one. */
  if (backup)
      memcpy(backup,rom,0x8000);

  kabuki_decode(rom,qsound_decode,rom,0x0000,0x8000, swap_key1,swap_key2,addr_key,xor_key);
  z80_offdata = rom - qsound_decode;
}

static UINT16 qsound_rom_r(UINT32 offset)
{
  offset -= 0xf00000;
  return ReadByte(qsound_rom+(offset>>1));
}

static UINT16 qsound_sharedram1_r(UINT32 offset)
{
  UINT16 ret;
  offset &= 0x1fff;
  ret  = (qsound_sharedram1[offset>>1]);
  // The | 0xff00 is for qsound clones which expect to find ff in the high byte
  return ret | 0xff00;
}

static UINT8 qsound_sharedram1_rb(UINT32 offset)
{
  UINT8 ret;
  offset = ((offset & 0x1fff) >> 1);

  ret = qsound_sharedram1[offset];
  return ret;
}

static void qsound_sharedram1_w(UINT32 offset, UINT16 data)
{
  offset &= 0x1fff;
  offset>>=1;
  qsound_sharedram1[offset] = data & 0xff;
}

static void qsound_sharedram1_wb(UINT32 offset, UINT8 data)
{
  offset = ((offset & 0x1fff) >> 1);
  qsound_sharedram1[offset] = data;
}

static UINT16 qsound_sharedram2_r(UINT32 offset)
{
  offset &= 0x1fff;
  return qsound_sharedram2[offset>>1] | 0xff00;
}

static UINT8 qsound_sharedram2_rb(UINT32 offset)
{
  offset &= 0x1fff;
  return qsound_sharedram2[offset>>1];
}

static void qsound_sharedram2_w(UINT32 offset, UINT16 data)
{
  offset &= 0x1fff;

  qsound_sharedram2[offset>>1] = data & 0xff;
}

static void qsound_sharedram2_wb(UINT32 offset, UINT8 data)
{
  offset &= 0x1fff;
  qsound_sharedram2[offset>>1] = data;
}

void load_qsound()
{
  const char *name = parent_name();
  load_common(0);
  if (load_error) return;
  default_frame = CPU_FRAME_MHz(12,60);

  if (!strncmp(name,"wof",3))
    cps1_decode(0x01234567,0x54163072,0x5151,0x51);
  else if (!strncmp(name,"dino",4))
    cps1_decode(0x76543210,0x24601357,0x4343,0x43);
  else if (!strncmp(name,"slammas",7) || !strncmp(name,"mbomb",5))
    cps1_decode(0x54321076,0x65432107,0x3131,0x19);
  else if (!strncmp(name,"punish",6)) {
    cps1_decode(0x67452103,0x75316024,0x2222,0x22);
  }

  AddReadBW(0xf00000, 0xf0ffff, qsound_rom_r, NULL);

  // Too bad to access it this way. The 68k passes twice the offset
  // to access the z80 rom. We must have handlers for this.
#if 1
  AddReadWord(0xf18000, 0xf19fff, qsound_sharedram1_r, NULL);
  AddReadByte(0xf18000, 0xf19fff, qsound_sharedram1_rb, NULL);
  AddWriteWord(0xf18000, 0xf19fff, qsound_sharedram1_w, NULL);
  AddWriteByte(0xf18000, 0xf19fff, qsound_sharedram1_wb, NULL);
#else
  AddRWBW(0xf18000,0xf19fff,NULL,qsound_sharedram1);
#endif

#if 1
  AddReadWord(0xf1e000, 0xf1ffff, qsound_sharedram2_r, NULL);
  AddReadByte(0xf1e000, 0xf1ffff, qsound_sharedram2_rb, NULL);
  AddWriteWord(0xf1e000, 0xf1ffff, qsound_sharedram2_w, NULL);
  AddWriteByte(0xf1e000, 0xf1ffff, qsound_sharedram2_wb, NULL);
#else
  AddRWBW(0xf1e000, 0xf1ffff, NULL,qsound_sharedram2);
#endif

  qsound_set_z80();
  EEPROM_init(&qsound_eeprom_interface);
  load_eeprom();

  Z80SetDataBank(0,Z80ROM);
  finish_conf_cps1();
}

static UINT16 cps2_eeprom_port_r(UINT32 offset) {
  UINT16 res = (ReadWord(&input_buffer[4]) & 0xfffe) | EEPROM_read_bit();
  return res;
}

static UINT16 cps2_eeprom_port_rb(UINT32 offset) {
  if (offset & 1) {
    UINT8 res = (input_buffer[4] & 0xfe) | EEPROM_read_bit();
    return res;
  }
  return input_buffer[5];
}


// #if 0
static void cps2_eeprom_w_lo(UINT32 offset, UINT16 data) {
  /* bit 0 - coin counter 1 */
  /* bit 0 - coin counter 2 */
  /* bit 2 - Unused */
  /* bit 3 - Allows access to Z80 address space (Z80 reset) */
  /* bit 4 - lock 1  */
  /* bit 5 - lock 2  */
  /* bit 6 - */
  /* bit 7 - */

  /* Z80 Reset */
  if (data & 8)
    cps2_reset_ready = 1;
  if (!(data & 8) && cps2_reset_ready) {
    // the reset is *required* at leat in 1944 !!!
    cpu_reset(CPU_Z80_0);
    cps2_reset_ready = 0;
  }

/*       coin_counter_w(0, data & 0x0001); */
/*       coin_counter_w(1, data & 0x0002); */
}
// #endif

static void cps2_eeprom_w_hi(UINT32 offset, UINT16 data) {
	/* bit 0 - Unused */
	/* bit 1 - Unused */
	/* bit 2 - Unused */
	/* bit 3 - Unused? */
	/* bit 4 - Eeprom data  */
	/* bit 5 - Eeprom clock */
	/* bit 6 - */
	/* bit 7 - */

	/* EEPROM */
  EEPROM_write_bit(data & 0x10);
  EEPROM_set_clock_line((data & 0x20) ? ASSERT_LINE : CLEAR_LINE);
  EEPROM_set_cs_line((data & 0x40) ? CLEAR_LINE : ASSERT_LINE);
}

WRITE16_HANDLER( cps2_eeprom_port_w )
{
  cps2_eeprom_w_lo(offset, data & 0xff);
  cps2_eeprom_w_hi(offset, data >> 8);
}

static void cps2_objram_bank_w(UINT32 offset, UINT16 data) {
  *cps2_objram_bank = data & 1;
  if (data & 1) {
    set_68000_io( 0,  0x700000, 0x701fff, NULL, cps2_objram2);

    set_68000_io( 0,  0x708000, 0x709fff, NULL, cps2_objram1);
    set_68000_io( 0,  0x70a000, 0x70bfff, NULL, cps2_objram1);
    set_68000_io( 0,  0x70c000, 0x70dfff, NULL, cps2_objram1);
    set_68000_io( 0,  0x70e000, 0x70ffff, NULL, cps2_objram1);
  } else {
    set_68000_io( 0,  0x700000, 0x701fff, NULL, cps2_objram1);

    set_68000_io( 0,  0x708000, 0x709fff, NULL, cps2_objram2);
    set_68000_io( 0,  0x70a000, 0x70bfff, NULL, cps2_objram2);
    set_68000_io( 0,  0x70c000, 0x70dfff, NULL, cps2_objram2);
    set_68000_io( 0,  0x70e000, 0x70ffff, NULL, cps2_objram2);
  }
}

static UINT8 *cps2_objbase(void)
{
  int baseptr;
  baseptr = 0x7000;

  if (*cps2_objram_bank) baseptr ^= 0x0080;

/*usrintf_showmessage("%04x %d",cps2_port(CPS2_OBJ_BASE),cps2_objram_bank&1); */

  if (baseptr == 0x7000)
    return cps2_objram1;
  else /*if (baseptr == 0x7080) */
    return cps2_objram2;
}

void cps2_find_last_sprite(void)    /* Find the offset of last sprite */
{
  int offset=0;
  UINT8 *base=cps2_buffered_obj;

	/* Locate the end of table marker */
  while (offset < cps2_obj_size)
	{
	  if (ReadWord(&base[offset+2])>=0x8000
	      || ReadWord(&base[offset+6])>=0xff00) {
	    /* Marker found. This is the last sprite. */
	    cps2_last_sprite_offset=offset-8;
	    return;
	  }

	  offset+=8;
	}
  /* Sprites must use full sprite RAM */
  cps2_last_sprite_offset=cps2_obj_size-8;
}

static UINT16 *xor;


void load_cps2() {
  int  size_code, size_user1;
  // UINT16 *rom = load_region[REGION_ROM1];
/*   int size = get_region_size(REGION_USER1)/2,i,size_code; */
  size_code = get_region_size(REGION_ROM1);
  ByteSwap(ROM, size_code );
  cps2crpt();
  if (is_current_game("gigaman2")) {
      xor = (UINT16*)ROM;
      size_user1 = size_code / 2;
      ROM += size_code/2;
      size_code /= 2;
      int length = get_region_size(REGION_GFX1)/2,i;
      UINT16 *rom = (UINT16*) load_region[REGION_GFX1];
      UINT16 *buf = (UINT16*)AllocateMem(length);
      if (!buf) return;
      memcpy(buf,rom,length);
      for (i = 0; i < length/2; i++) {
	  rom[i] = buf[((i & ~7) >> 2) | ((i & 4) << 18) | ((i & 2) >> 1) | ((i & 1) << 21)];
      }
      /* Bad hack : apparently the code of the sprites are all outside the
       * normal range (they have the megaman2 range), and must be anded so that
       * the game works. Now, until now I could do without anding anything, if
       * I want to continue, I have to duplicate the sprites here.
       * It's a wonder so many games finally work without and finally... ! */
      /* Plus, the end of the 2 graphical roms are just empty... ! */
      memcpy(rom+length/2,rom,length);
      FreeMem((UINT8*)buf);
  } else {
      xor = (UINT16*)load_region[REGION_USER1];
      size_user1 = get_region_size(REGION_USER1);
  }
/*  save_debug("xor",xor,size_user1,1);
  ByteSwap(xor,size_user1); */

  // tmp = AllocateMem(size_user1);
  if (!init_tilequeue()) return;
  init_pbitmap();

  /* The decoded rom must go to the pc bus only.
     The xor table has a size <= the size of the cpu rom.
     So we must move to a temporary buffer the 1st part of the original rom
     (because the memfetch area must be in 1 block, but we can have 2 blocks for the data)
  */

  /* There is an optimization in starscream to read longs : it reads them
   * directly from the memory map. So if you read a long at ffffe and the last
   * byte of the region is at fffff (case of mshh), then it reads 2 bytes out
   * of the region and gets a bad long !
   * To work around that, I always allocate 2 more bytes while loading the
   * regions, and I copy manually the missing 2 bytes here */
  if (size_code > size_user1 && xor)
    WriteWord(((UINT8*)xor)+size_user1,ReadWord(&ROM[size_user1]));
  // save_file("xor",xor,size_user1);

  load_common(1);
  if (load_error) return;

  // ByteSwap((UINT8*)xor, size_user1 );

  // printf("region ? %x\n",xor[0x13ca/2]);
  // xor[0x13ca/2] = 0;
  AddResetHandler(&quiet_reset_handler);

  AddMemFetch(0x000000, size_code-1, ROM+0x000000-0x000000);
  AddMemFetch(0xff0000, 0xffffff, RAM+0x040000-0xff0000);
  /* This is a kabuki like encryption : "encrypted" on the data bus, decoded on the
     pc bus. No way to tell if a byte should go on 1 bus or the other, so we must keep
     the 2 versions at the same time... */
  //AddReadByte(0x8f685,0x8f685, my_read, NULL);
  // rom region codes :
  // mshh : c3
  // ssf2 (some risks) : 18c
  // vhunt2r1 (some risks) : 10ce
  // mpangj : 7a0
  // vsav2 : 10ce
  // AddWriteWord(0xff8090,0xff8091, my_write, NULL);
  cps2_output = RAM;

  if (xor) {
    // normal cps2 behaviour
  AddReadBW(0x000000, size_user1-1, NULL, (UINT8*)xor+0x000000);
  if (size_code > size_user1) {
    AddReadBW(size_user1, size_code-1, NULL, &ROM[size_user1]);
  }
  } else {
    // phoenix behaviour : no crypted rom !
/*
 ------------------------
 Phoenix bootleg sets
 ------------------------

 The Phoenix sets were created by Razoola as a method of allowing the games to run on
 CPS2 boards where the battery had died.  When this happens the boards run non-encrypted
 code, but the memory mapping is changed.  As the original games have encrypted code
 mixed with decrypted data the program roms must be carefully modified in order to
 correctly contain only decrypted code and data, as well as modification to compensate
 for the memory map changes that occur on the dead boards.  Due nature of this process
 there were sometimes errors introduced into the 'Phoenix' sets.

 Unfortunately the 'Phoenix' sets also ended up forming the basis of a mass cps2
 bootlegging operation whereby cheap CPS2 B boards were purchased, the encryption keys
 killed, and the boards converted to more desirable games.  These started off as single
 game bootlegs of in-demand titles, but soon started also forming the basis of xx-in-1
 bootlegs running on heavily customized B-boards.  These are not legitimate Capcom
 products despite appearing to be so.

 These bootlegs are often sold as 'Phoenix Edition' after Razoola's name, 'xx-in-1', or
 simply 'Suicide-Free' to further artificially inflate the price. Buyer Beware!

 All sets are marked as bootleg because they're unauthorized modifications of the
 original Capcom rom data, and were used for bootleg conversions.

 This may not be a complete list of sets, it was taken from MamePlus.  Other sets, and
 further customized bootlegs boards are known to exist.

 ------------------------
 Other bootlegs
 ------------------------

 There is a bootleg of Megaman 2 called 'Gigaman 2' which has SMT roms, and replaces
 the Qsound hardware with an OKI6295 / AD-65 chip.  No known complete dump exists.

*/
    AddReadBW(0, size_code-1, NULL, ROM);
  }

  if (xor)
  AddRWBW(0xFF0000, 0xFFFFFF, NULL, RAM+0x40000);		    // 68000 RAM
  else
    AddRWBW(0xFF0000, 0xFFFFeF, NULL, RAM+0x40000);		    // 68000 RAM
  AddRWBW(0x900000, 0x92FFFF, NULL, cps1_gfxram); // ram + 0x10000

  if (xor) AddRWBW(0x400000, 0x40000b, NULL, cps2_output);
  else {
    AddRWBW(0xfffff0, 0xfffffb, NULL, cps2_output);
      // the last byte fffffe actually is the region for at least mmatrixd
      // doesn't work for 1944d, so maybe it's unique
    AddReadBW(0xfffffc, 0xffffff, NULL, RAM+0x4fffc);
  }

  AddReadWord(0x618000, 0x619fff, qsound_sharedram1_r, NULL); // ram + 0x70000
  AddReadByte(0x618000, 0x619fff, qsound_sharedram1_rb, NULL);
  AddWriteWord(0x618000, 0x619fff, qsound_sharedram1_w, NULL);
  AddWriteByte(0x618000, 0x619fff, qsound_sharedram1_wb, NULL);

  // AddRWBW(0x662000, 0x662021, NULL, RAM+0xb); // network stuff (unemulated)

  AddRWBW(0x660000, 0x664001, NULL, RAM+0xc);
  cps2_objram1 = RAM + 0x4002 + 0xc;
  AddRWBW(0x700000, 0x701fff, NULL, cps2_objram1);
  cps2_objram2 = cps2_objram1 + 0x2000;
  AddRWBW(0x708000, 0x709fff, NULL, cps2_objram2);
  AddRWBW(0x70a000, 0x70bfff, NULL, cps2_objram2);
  AddRWBW(0x70c000, 0x70dfff, NULL, cps2_objram2);
  AddRWBW(0x70e000, 0x70ffff, NULL, cps2_objram2);

  AddReadByte(0x800100, 0x8001FF, cps1_ioc_rb, NULL);			// IOC
  AddReadWord(0x800100, 0x8001FF, cps1_ioc_rw, NULL);			// IOC
  AddReadByte(0x804100, 0x8041FF, cps1_ioc_rb, NULL);			// IOC
  AddReadWord(0x804100, 0x8041FF, cps1_ioc_rw, NULL);			// IOC

  AddWriteByte(0x800100, 0x8001FF, cps1_ioc_wb, NULL);			// IOC
  AddWriteWord(0x800100, 0x8001FF, cps1_ioc_ww, NULL);			// IOC
  AddWriteByte(0x804100, 0x8041FF, cps1_ioc_wb, NULL);			// IOC
  AddWriteWord(0x804100, 0x8041FF, cps1_ioc_ww, NULL);			// IOC

  AddReadBW(0x804000, 0x804001, NULL, input_buffer);
  AddReadBW(0x804010, 0x804011, NULL, input_buffer+2);
  AddReadWord(0x804020, 0x804021, cps2_eeprom_port_r, NULL);
  AddReadByte(0x804020, 0x804021, cps2_eeprom_port_rb, NULL);

  AddWriteWord(0x804040, 0x804041, cps2_eeprom_port_w, NULL);
  AddWriteByte(0x804040, 0x804040, cps2_eeprom_w_hi, NULL);
  // AddWriteByte(0x804041, 0x804041, cps2_eeprom_w_lo, NULL);

  cps2_objram_bank = RAM + 0x9000;
  AddWriteWord(0x8040e0, 0x8040e0, cps2_objram_bank_w, NULL);
  AddWriteByte(0x8040e1, 0x8040e1, cps2_objram_bank_w, NULL);

  // In fact it's a status word for the presence of more memory and a network adapter
  if (is_current_game("ssf2tb"))
    cps2_qsound_volume = 0x2021;
  else
    cps2_qsound_volume = 0xe021;
  AddReadBW(0x804030, 0x804031, NULL, (UINT8*)&cps2_qsound_volume);

  AddWriteByte(0xAA0000, 0xAA0001, myStop68000, NULL);			// Trap Idle 68000

  qsound_set_z80();
  EEPROM_init(&pang3_eeprom_interface);
  load_eeprom();

  Z80SetDataBank(0,Z80ROM);
  finish_conf_cps1();

  // WriteWord(&ROM[0xfa2],0x60fe);
}

#define SLICES 4
#define Z80_FRAME CPU_FRAME_MHz(4,60)/SLICES

static int undo_counter;

static void apply_long_hack(UINT32 loop_start,UINT32 loop_end,UINT32 exit) {
  // This is the worst speed hack so far. The code is too short to be
  // hacked. I have to insert a jump and patch the end of the rom with the
  // speed hack !!!
  // First find some place at the end of the rom

  UINT32 pc,dbf;
  int size_code = get_region_size(REGION_ROM1);
  UINT32 free = size_code; // space_hack address
  if (loop_end < 0x100) {
      // just insert some code at the end of the rom...
      int n;
      for (n=0; n<8; n+=2) {
	  pWriteWord(&space_hack[n],ReadWord(&ROM[loop_start+n]));
      }
      apply_rom_hack(space_hack,8,0);
      pWriteWord(&space_hack[14],0x4e75);

      pWriteWord(&ROM[loop_start],0x4eb9);
      pWriteWord(&ROM[loop_start+2],(free>>16));
      pWriteWord(&ROM[loop_start+4],(free & 0xffff));
      pWriteWord(&ROM[loop_start+6],0x4e71); // nop
      return;
  }
  free+=22;
  apply_rom_hack(space_hack,22-12,4);
  print_ingame(300,gettext("Long hack jump at %x..."),loop_end);
  print_debug("Long hack jump at %x to %x...",loop_end,free-16);
  dbf = ReadWord(&ROM[loop_end]);
  pWriteWord(&ROM[loop_end],0x4ef9); // jmp start of hack
  pWriteWord(&ROM[loop_end+2],(free-16) >> 16);
  pWriteWord(&ROM[loop_end+4],(free-16) & 0xffff);

  pWriteWord(&space_hack[22-22],0x4ef9); // jmp back
  pWriteWord(&space_hack[22-20],loop_start >> 16);
  pWriteWord(&space_hack[22-18],loop_start & 0xffff);
  pWriteWord(&space_hack[22-16],dbf);
  pWriteWord(&space_hack[22-14],0xfff8);
  // free-12...free-8 : speed hack
  pWriteWord(&space_hack[22-6],0x4ef9);

  // Normally the 1st loop is 12 bytes before the 2nd loop
  if (exit)
      pc = exit;
  else {
      pc = loop_start-12;
      if (ReadWord(&ROM[pc+2]) == 0x422d) // variation
	  pc+=2;
  }
  pWriteWord(&space_hack[22-4],(pc) >> 16);
  pWriteWord(&space_hack[22-2],(pc) & 0xffff);
}

static void dynamic_hack() {
  UINT32 pc = s68000context.pc;

  // Z80
#if 0
  if (!z80_speed_hack) {
    if (Z80ROM[z80pc] == 0xfb && Z80ROM[z80pc+1] == 0x18 && Z80ROM[z80pc+2] == 0xfd) {
      WriteMZ80Byte(z80pc+1,0x76); // halt
      print_ingame(180,gettext("Z80: applied HALT speed hack"));
      z80_speed_hack = 1;
    } else if (ReadLong68k(&Z80ROM[z80pc]) == 0x2102d03a &&
	       ReadLong68k(&Z80ROM[z80pc+4]) == 0x01d0be28 &&
	       Z80ROM[z80pc+8] == 0xf7) {
      WriteMZ80Byte(z80pc+7,0xd3); // outa (aa)
      WriteMZ80Byte(z80pc+8,0xaa); // outa (aa)
      print_ingame(180,gettext("Z80: speed hack applied"));
      z80_speed_hack = 1;
    }
  }
#endif

  if (cpu_frame_count < 800 && strcmp(current_game->main_name,"qad")) {
    if (ReadWord(&ROM[pc]) == 0x46fc && ReadWord(&ROM[pc+2]) == 0x2000 &&
	ReadWord(&ROM[pc+8]) == 0x67f6) { // pzloop2j
      apply_hack(pc+4,0);
      max_hack_counter = 0;
    } else {
      while (ReadWord(&ROM[pc]) == 0x51c8 || // skip dbf...
	     ReadWord(&ROM[pc]) == 0x46fc || // stupid move
	     ReadWord(&ROM[pc]) == 0x41e8) // lea
	pc+=4;
      while (ReadWord(&ROM[pc]) == 0x4a2d && ReadWord(&ROM[pc+4]) == 0x6600)
	pc+=8; // skip (tst.b, bne) -> 1st patern of qsound speed hack
      if (ReadWord(&ROM[pc]) == 0x4a2d &&
	  (ReadWord(&ROM[pc+4]) & 0xff00) == 0x6600)
	pc+=6;
    }

    // printf("testing %x\n",pc);
    if (ReadWord(&ROM[pc]) == 0x0C81 && ReadWord(&ROM[pc+2]) == 0x63A1 &&
	ReadWord(&ROM[pc+4])== 0xB8D3 && ReadWord(&ROM[pc+6]) == 0x52B9) {
	  // progear has the speed hack on its encryption instruction !
	  apply_hack(pc,0);
	  max_hack_counter = 0;
    } else if (ReadWord(&ROM[pc]) == 0x82d && ReadWord(&ROM[pc+6]) == 0x66f8) {
      // Type btst xxx, bne -2
      apply_hack(pc,1);
    } else if (ReadWord(&ROM[pc]) == 0x4a6d && ReadWord(&ROM[pc+4]) == 0x66fa) {
      // mpangj
      apply_hack(pc,0);
      max_hack_counter = 0;
    } else if (ReadWord(&ROM[pc]) == 0x66f8 && ReadWord(&ROM[pc-6]) == 0x4af9) {
      // mars matrix
      apply_hack(pc-6,1);
      max_hack_counter = 0; // hack counter useless here
    } else if (ReadWord(&ROM[pc]) == 0x67ee && ReadWord(&ROM[pc-4]) == 0x4a6d &&
	       ReadWord(&ROM[pc-10]) == 0x0c81) {
      /* Gigawing weird vbl test :
LAB_002E:
        BCLR    #1,-4337(A5)            ;000956: 08AD0001EF0F
LAB_002F:
        CMPI.L  #$19721027,D1           ;00095C: 0C8119721027
        TST     -4346(A5)               ;000962: 4A6DEF06
        BEQ.S   LAB_002E                ;000966: 67EE
	!!! */
      max_hack_counter = 0; // hack counter useless here
      apply_hack(pc-10,4);
    } else if (ReadWord(&ROM[pc+22]) == 0x82d && ReadWord(&ROM[pc+28]) == 0x66f8)
      apply_hack(pc+0x16,1);
    else if (ReadWord(&ROM[pc-6]) == 0x4a39 && ReadWord(&ROM[pc]) == 0x66f8)
      apply_hack(pc-6,1);
    else if (ReadWord(&ROM[pc-6]) == 0x4a79 && ReadWord(&ROM[pc]) == 0x6700) {
      apply_hack(pc-6,10);
      max_hack_counter = 0; // hack counter useless here
    } else if (ReadWord(&ROM[pc]) == 0x082d && ReadWord(&ROM[pc+6]) == 0x6708)
      // qsound (slammast)
      apply_hack(pc,3);
    else if (ReadWord(&ROM[pc]) == 0x4a2d && ReadWord(&ROM[pc+4]) == 0x67b8) {
      apply_hack(pc,4);
      print_debug("disabling speed hack counter\n");
      max_hack_counter = 0; // hack counter useless here
    }
    else if ((ReadWord(&ROM[pc-10]) == 0x46fc && // move #$xxx,sr
	      ReadWord(&ROM[pc-6]) == 0x4a2d && // tst.b xxx
	      (ReadWord(&ROM[pc])== 0x1228 || // move.b xxx(a0),d1
	       ReadWord(&ROM[pc]) == 0x0c28 || // or directly cmp.b #4,(a0)
	       ReadWord(&ROM[pc])== 0x1210) &&  // move.b (a0),d1
	      ReadWord(&ROM[pc+18]) == 0x51c8))  // dbf
      apply_long_hack(pc-10,pc+18,0);
    else if (ReadWord(&ROM[pc-0x1a]) == 0x46fc && // move #$xx,sr
	     ReadWord(&ROM[pc-0x1a+4]) == 0x4a2d && // tst.b xxx
	     ReadWord(&ROM[pc])== 0x3210 && // move (a0),d1
	     ReadWord(&ROM[pc+0x10]) == 0x51c8) {  // dbf
      // variant of the above hack for 19xx
      // apply_long_hack(pc-0x1a,pc+16,2);
      apply_long_hack(pc+8,8,0);
      max_hack_counter = 50;
    } else if (ReadWord(&ROM[pc-4]) == 0x46fc && // move #$xxx,sr
	       ReadWord(&ROM[pc+26]) == 0x41e8 && // lea 32(a0),a0
	       ReadWord(&ROM[pc+30]) == 0x51c8) { // dbf
      // marvel super heroes vs street fighter
      apply_long_hack(pc+22,8,0);
      max_hack_counter = 50;
    } else if (ReadWord(&ROM[pc+0x14]) == 0x46fc && // move #$xxx,sr
	       ReadWord(&ROM[pc+0x18]) == 0x41e8 && // lea 32(a0),a0
	       ReadWord(&ROM[pc+0x1c]) == 0x51c8) { // dbf
      // eco fighter
      apply_long_hack(pc+0x14,8,0);
      max_hack_counter = 50;
    } else if (ReadWord(&ROM[pc+4]) == 0x46fc && ReadWord(&ROM[pc+6]) == 0x2000 &&
	       ReadWord(&ROM[pc+8]) == 0x41e8) {
      // dimahoo
      apply_long_hack(pc+4,8,0);
      max_hack_counter = 50;
    } else if ((ReadWord(&ROM[pc-10]) == 0x46fc && // move #$xxx,sr
	      ReadWord(&ROM[pc-6]) == 0x4a2d && // tst.b xxx
	      (ReadWord(&ROM[pc])== 0x1210) &&  // move.b (a0),d1
	      ReadWord(&ROM[pc+16]) == 0x51c8))  // dbf
      // This is for megaman and friends
      apply_long_hack(pc-10,pc+16,0);
    else if ((ReadWord(&ROM[pc-12]) == 0x46fc && // move #$xxx,sr
	      ReadWord(&ROM[pc-8]) == 0x4a2d && // tst.b xxx
	      (ReadWord(&ROM[pc])== 0x1228) &&  // move.b xxx(a0),d1
	      ReadWord(&ROM[pc+20]) == 0x51c8))  // dbf
      // mercs and friends
      apply_long_hack(pc-12,pc+20,0);
    else if ((ReadWord(&ROM[pc-10]) == 0x46fc && // move #$xxx,sr
	      ReadWord(&ROM[pc-6]) == 0x4a2d && // tst.b xxx
	      (ReadWord(&ROM[pc])== 0x1228) && // move.b xxx(a0),d1
	      ReadWord(&ROM[pc+20]) == 0x51c8))  // dbf
      // dino and friends (qsound)
      apply_long_hack(pc-10,pc+20,0);
    else  // variation : ghouls does not use the same regs...
      if (ReadWord(&ROM[pc-4]) == 0x46fc && // move #$xxx,sr
	  ReadWord(&ROM[pc])== 0x162a && // move.b (a2),d3
	  ReadWord(&ROM[pc+20]) == 0x51c9)   // dbf
	apply_long_hack(pc-4,pc+20,0);
      else if (ReadWord(&ROM[pc-0x10]) == 0x46fc && // move #$xxx,$sr
	       ReadWord(&ROM[pc+38]) == 0x51c8) { // dbf
	apply_long_hack(pc-0x10,pc+38,pc+48); // fix for punisher
      } else if (ReadWord(&ROM[pc-4]) == 0x46fc && // move #$xx,sr
		 ReadWord(&ROM[pc+0x30-4]) == 0x51c8) { // dbf
	// variant for wof
	apply_long_hack(pc-4,pc+0x30-4,pc+0x3c-4);
	max_hack_counter = 0; // hack counter useless here
      }
  } else {
    print_ingame(120,gettext("Speed hack not found, slowing down..."));
    print_debug("Failed to find speed hack\n");
    speed_hack = 1;
      frame_68k = default_frame;
  }
  if (speed_hack)
    undo_counter = 10;
}

void execute_cps1_frame(void)
{
  int mx,my;
  hack_counter = 0;
  if (GameMouse) {
    GetMouseMickeys(&mx,&my);
    if (!(input_buffer[2] & 0x20)) // P1 B2 (unused in this game...)
      mx = -20;
    else if (!(input_buffer[2] & 0x40)) { // P1 B3
      mx = 20;
    }

    WriteWord(&input_buffer[5*2],mx & 0xfff);
#ifndef SDL
    // MouseB isn't handled in sdl, instead you can assign mouse buttons to
    // any control yourself (default mbtn1 = button 1 of course)
    if (*MouseB & 1) input_buffer[2] &= 0xef;
    if (*MouseB & 2) input_buffer[2] &= 0xdf;
#endif
  }
  cpu_execute_cycles(CPU_68K_0, frame_68k);	  // Main 68000

  if (!speed_hack) {
    dynamic_hack();
  }

   cpu_interrupt(CPU_68K_0, 2);
   execute_z80_audio_frame();
}

void execute_ganbare(void)
{
  hack_counter = 0;
  frame_68k = CPU_FRAME_MHz(10,60);
  cpu_interrupt(CPU_68K_0, 4);
  cpu_execute_cycles(CPU_68K_0, frame_68k);	  // Main 68000

  if (!speed_hack) {
    dynamic_hack();
  }

   cpu_interrupt(CPU_68K_0, 2);
   execute_z80_audio_frame();
}

#undef SLICES
#undef Z80_FRAME
#define SLICES 4
#define Z80_FRAME (CPU_FRAME_MHz(6,60)/SLICES)

void execute_qsound_frame(void)
{
  int n;
  hack_counter = 0;

  cpu_execute_cycles(CPU_68K_0, frame_68k);	  // Main 68000

  for (n=0; n< SLICES; n++) {

    cpu_execute_cycles(CPU_Z80_0, Z80_FRAME); // Z80_FRAME );	     // Sound Z80
    cpu_interrupt(CPU_Z80_0, 0x38);

  }
  if (!speed_hack) {
    dynamic_hack();
  }
  cpu_interrupt(CPU_68K_0, 2);
}

#undef SLICES
#undef Z80_FRAME
#define TICKS_PER_SEC 258
/* Thanks to mame for pointing super gem fighters to calibrate this timer.
   We don't seem to find the same number as mame, but on the other hand we use 60 fps
   and not 59.633 so maybe it counts for something ! */
#define Z80_FRAME CPU_FRAME_MHz(8,60)

static int nb_ticks, nb_executed;

void execute_cps2_frame(void)
{
  int n,slices;
  hack_counter = 0;

  cpu_execute_cycles(CPU_68K_0, frame_68k);	  // Main 68000

  slices = ((++nb_ticks)*TICKS_PER_SEC)/fps-nb_executed;
  if (nb_ticks >= fps) {
    nb_ticks = 0;
    nb_executed = 0;
  } else {
    nb_executed += slices;
  }

  if (Z80ROM) {
      for (n=0; n< slices; n++) {
	  cpu_execute_cycles(CPU_Z80_0, Z80_FRAME/slices);
	  cpu_interrupt(CPU_Z80_0, 0x38);
      }
  }
  if (!speed_hack) {
    dynamic_hack();
  }
  if (!hack_counter && speed_hack && cpu_frame_count < 800 && undo_counter--<=0)
    undo_hack();

  cpu_interrupt(CPU_68K_0, 2);
}

static void update_transmasks(void)
{
  int i;

  for (i = 0;i < 4;i++)
    {
      /* Get transparency registers */
      if (cps1_game_config->priority[i]) {
	pri_mask[i] = cps1_port[(cps1_game_config->priority[i]/2)];
      } else {
	pri_mask[i] = 0x0000;	/* completely transparent if priority masks not defined (mercs, qad) */
      }
    }
}

static UINT8* mask_sprite(int nb,UINT8 *sprite,int transp_index) {
  /* Priorities in cps1 are quite err... tricky ? */
  /* Each element of a tile can have some colors overwriting sprites. */
  /* If the color of a pixel corresponds to a cleared bit in the mask then */
  /* it has priority over the sprites layer. */
  /* The mask is set at run time (update_transmask) */

  UINT16 mask = pri_mask[transp_index];
  int shown = 0;
  static UINT8 dest[32*32];
  if (mask == 0x0) {// Completely transparent...
    return NULL;
  }

  for(; nb>=0; nb--) {
    UINT8 val = sprite[nb];
    if ((0x8000 >> val) & mask) {
      // if ((1 << val) & mask) {
      dest[nb] = val;
      shown=1;
    } else {
      dest[nb] = 0;
    }
  }
  if (shown) {
    return dest;
  }
  return NULL; // Nothing to show...
}

/* This layer is not linear, the reason why I had so many troubles to use
   the standard raine macros to draw it. The last bit of scrollx is used
   as the msb of scrolly ! Hence these macros are not standard and can not
   be included in scroll.h
   To add to the complexity, borderx = 64 and bordery = 16 and border of the
   screen in raine = 32. So we must adjust the coordinates when calling
   START_SCROLL_XXX */

#define MAKE_SCROLL_SCROLL1_4_8_YX(scr_x,scr_y)	\
   zzz=(scr_x);					\
   zzzz=(zzz&0x1f8)<<4;				\
   x16=zzz&7;					\
   zzz=(scr_y);					\
   zzzz|=(zzz&0xf8)>>1;				\
   zzzz|=((zzz&0x100)<<5);			\
   y16=zzz&7;


#define START_SCROLL_SCROLL1_4_8_YX(start_x,start_y,view_x,view_y) \
   zz=zzzz;                                           \
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=8){      \
   for(y=(start_y-y16);(UINT32)y<(view_y+start_y);y+=8){      \

// Since the layer is not linear, the best is to update the addresses
// directly from scrolly (instead of increasing it as usual).
#define END_SCROLL_SCROLL1_4_8_YX()			\
      scroll1y+=8; zz=(zz&0x1f80)|((scroll1y&0xf8)>>1)|((scroll1y&0x100)<<5); \
   }							\
   scroll1y=zzz; zz = zzzz = ((zzzz+0x80)&0x1FFF) | (zzzz&0x2000);	\
   }

// Macros for SCROLL3, same thing, not linear

#define MAKE_SCROLL_SCROLL3_4_32_YX(scr_x,scr_y)	\
   zzz=(scr_x);						\
   zzzz=(zzz&0x7e0)<<0;					\
   x16=zzz&31;						\
   zzz=(scr_y);						\
   zzzz|=(zzz&0xe0)>>3;					\
   zzzz|=((zzz&0x700)<<3);				\
   y16=zzz&31;

#define START_SCROLL_SCROLL3_4_32_YX(start_x,start_y,view_x,view_y)	\
   zz=zzzz;							\
   for(x=(start_x-x16);(UINT32)x<(view_x+start_x);x+=32){	\
   for(y=(start_y-y16-16);y<(view_y+start_y);y+=32){

#define END_SCROLL_SCROLL3_4_32_YX()			\
     scroll3y+=32; zz=(zz&0x7e0)|((scroll3y&0xe0)>>3)|((scroll3y&0x700)<<3);\
   }							\
   scroll3y=zzz; zz = zzzz = ((zzzz+0x20)&0x7FF) | (zzzz&0x3800); \
   }

static void render_scroll1(int mask)
{
   int x,y,n,code;
   UINT32 zzz,zzzz,zz,x16,y16;
   UINT16 scroll1x = cps1_port[CPS1_SCROLL1_SCROLLX]+56+scroll1xoff,
	  scroll1y = cps1_port[CPS1_SCROLL1_SCROLLY], colour;
   UINT8 *map,*dest;

   MAKE_SCROLL_SCROLL1_4_8_YX(scroll1x,scroll1y);

   START_SCROLL_SCROLL1_4_8_YX(24,16,384+8,224+16);

   code  =ReadWord(&RAM_SCROLL1[zz]) /* + base1 */;
   colour=ReadWord(&RAM_SCROLL1[(zz+2)]);

   for (n=0; n<nb_scroll1; n++) {
     if (code >= scroll1_ranges[n].start && code <= scroll1_ranges[n].end) {
       code = (scroll1_ranges[n].base + (code & (scroll1_ranges[n].mask)));
       break;
     }
   }
   if (n < nb_scroll1 && GFX_SPR_SOLID[code]) { // the range is ok

     MAP_PALETTE_MAPPED_NEW(
	 (colour&0x1F) | 0x20,
	 16,
	 map
	 );
     // printf("%d,%d code %x\n",x,y,code);
     if (mask) {
       if (cps_version == 2) {
	 if (GFX_SPR_SOLID[code]==1) // Some pixels transp
	   pdraw8x8_Mask_Trans_Mapped_flip_Rot(&GFX_SPR[code<<6],x,y,map,(colour & 0x60)>>5,mask);
	 else // all solid
	   pdraw8x8_Mask_Mapped_flip_Rot(&GFX_SPR[code<<6],x,y,map,(colour & 0x60)>>5,mask);
       } else {
	 dest = mask_sprite(8*8-1,&GFX_SPR[code<<6],(colour & 0x180)>>7);
	 if (dest) // we got something
	   Draw8x8_Trans_Mapped_flip_Rot(dest,x,y,map,(colour & 0x60)>>5);
       }
     } else {
       if (GFX_SPR_SOLID[code]==1) // Some pixels transp
	 Draw8x8_Trans_Mapped_flip_Rot(&GFX_SPR[code<<6],x,y,map,(colour & 0x60)>>5);
       else // all solid
	 Draw8x8_Mapped_flip_Rot(&GFX_SPR[code<<6],x,y,map,(colour & 0x60)>>5);
     }
   } // if...

   END_SCROLL_SCROLL1_4_8_YX();

}

static inline void alpha_sprite(UINT32 code, int x,int y,UINT8 *map,int flip) {
    int alpha = get_spr_alpha(code);
    if (!alpha) {
	if(GFX_SPR_SOLID16[code]==1)                    // Some pixels; trans
	    return Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip);
	return Draw16x16_Mapped_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip);
    }
    set_alpha(alpha);
    // printf("%x %d\n",code,alpha);
    if(GFX_SPR_SOLID16[code]==1)                    // Some pixels; trans
	Draw16x16_Trans_Mapped_Alpha_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip);
    else
	Draw16x16_Mapped_Alpha_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip);
}

static inline void alpha_sprite_pb(UINT32 code, int x,int y,UINT8 *map,int flip,int pri) {
    int alpha = get_spr_alpha(code);
    if (!alpha) {
	if(GFX_SPR_SOLID16[code]==1)                    // Some pixels; trans
	    return pdraw16x16_Trans_Mapped_back_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip,pri);
	return pdraw16x16_Mapped_back_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip,pri);
    }
    set_alpha(alpha);
    // printf("pb %x %d\n",code,alpha);
    if(GFX_SPR_SOLID16[code]==1)                    // Some pixels; trans
	pdraw16x16_Trans_Mapped_back_Alpha_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip,pri);
    else
	pdraw16x16_Mapped_back_Alpha_flip_Rot(&GFX_SPR16[code<<8],x,y,map,flip,pri);
}
// cps2 sprites do not use the ranges array
static void render_cps2_sprites()
{
  int i;
  UINT8 *base=cps2_buffered_obj;
  int xoffs = 64-cps2_port(CPS2_OBJ_XOFFS);
  int yoffs = 16-cps2_port(CPS2_OBJ_YOFFS);
  UINT8 *map;
  int last_prio = 0;
  pbitmap_needed = 0;
  // cps2_find_last_sprite();

  for (i=0; i<cps2_obj_size; i+=8) {
    int x=ReadWord(&base[i+0]);
    int y=ReadWord(&base[i+2]);
    int priority=(x>>13)&0x07;
    // priority = primasks[priority];
    int code  = ReadWord(&base[i+4])+((y & 0x6000) <<3);
    int colour= ReadWord(&base[i+6]);
    int col=colour&0x1f;
    if (y >= 0x8000 || colour >= 0xff00) {
      return;
    }
    // printf("%d,%d %d,%x\n",x,y,priority,code);
    if (priority < last_prio && !no_pbitmap) {
	// This pbitmap thing is a pain
	// csclub is one of the game where the pbitmap is the most needed
	// in the intro, you don't see the light without this.
	// but xmcota has a problem with it, so for now I have a no_pbitmap
	// variable, but I am not sure I understood everything there !
      if (GFX_SPR_SOLID16[code]) {
	pbitmap_needed = 1;
	// printf("pbitmap needed offset %d<%d priority %d last_priority %d\n",i,cps2_obj_size,priority,last_prio);
	return;
      }
    } else
      last_prio = priority;

    MAP_PALETTE_MAPPED_NEW(
			   col,
			   16,
			   map
			   );

    x-=0x20; // border
    y+=0x10;

    if(colour & 0x80) {
      x += cps2_port(CPS2_OBJ_XOFFS);  /* fix the offset of some games */
      y += cps2_port(CPS2_OBJ_YOFFS);  /* like Marvel vs. Capcom ending credits */
    }

    if (colour & 0xff00 ) {
      /* handle blocked sprites */
      int nx=(colour & 0x0f00) >> 8;
      int ny=(colour & 0xf000) >> 12;
      int nxs,nys,sx,sy;
      nx++;
      ny++;

      if (colour & 0x40) {
	/* Y flip */
	if (colour &0x20) {
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = code+(nx-1)-nxs+0x10*(ny-1-nys);
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  QueueTile(code2, sx,   sy,   map, 3, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8],sx, sy, map,3);
	      }
	    }
	  }
	} else { // flip y
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = code+nxs+0x10*(ny-1-nys);
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  QueueTile(code2, sx,   sy,   map, 2, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8],sx,sy,map,2 );
	      }
	    }
	  }
	}
      } else {
	if (colour &0x20) {
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = code+(nx-1)-nxs+0x10*nys;
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  QueueTile(code2, sx,   sy,   map, 1, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8], sx,sy,map,1);
	      }
	    }
	  }
	} else { // no flip
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = (code & ~0xf) + ((code + nxs) & 0xf) + 0x10*nys; /* pgear fix */
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  QueueTile(code2, sx,   sy,   map, 0, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8],sx,sy, map,0);
	      }
	    }
	  }
	}
      }
    } else {
      /* Simple case... 1 sprite */
      int sx = (x+xoffs) & 0x3ff;
      int sy = (y+yoffs) & 0x3ff;
      if (sx < scrwidth && sy < scrheight && code <= max_sprites16) {
	if (GFX_SPR_SOLID16[code]) {
	  QueueTile(code, sx,   sy,   map, (colour & 0x60)>>5, priority);
	}
	// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8], sx, sy, map,(colour & 0x60)>>5);
      }
    }
  }
}

#define draw_sprite(code,x,y,map,flip,priority)     \
      alpha_sprite_pb(code,x,y,map, flip,priority);

static void render_cps2_sprites_pbitmap()
{
  if (!check_layer_enabled(layer_id_data[0]))
    return;
  int i;
  UINT8 *base=cps2_buffered_obj;
  int xoffs = 64-cps2_port(CPS2_OBJ_XOFFS);
  int yoffs = 16-cps2_port(CPS2_OBJ_YOFFS);
  UINT8 *map;
  // cps2_find_last_sprite();
  // print_ingame(1,gettext("using pbitmap"));

  // for (i=cps2_last_sprite_offset; i>=0; i-=8) {
  for (i=0; i<cps2_obj_size; i+=8) {
    int x=ReadWord(&base[i+0]);
    int y=ReadWord(&base[i+2]);
    int priority=(x>>13)&0x07;
    int code  = ReadWord(&base[i+4])+((y & 0x6000) <<3);
    int colour= ReadWord(&base[i+6]);
    int col=colour&0x1f;
    if (y >= 0x8000 || colour >= 0xff00) {
      return;
    }
    // printf("%d,%d %d,%x\n",x,y,priority,code);
    // if (priority) priority--;

    MAP_PALETTE_MAPPED_NEW(
			   col,
			   16,
			   map
			   );

    x-=0x20; // border
    y+=0x10;

    if(colour & 0x80) {
      x += cps2_port(CPS2_OBJ_XOFFS);  /* fix the offset of some games */
      y += cps2_port(CPS2_OBJ_YOFFS);  /* like Marvel vs. Capcom ending credits */
    }

    if (colour & 0xff00 ) {
      /* handle blocked sprites */
      int nx=(colour & 0x0f00) >> 8;
      int ny=(colour & 0xf000) >> 12;
      int nxs,nys,sx,sy;
      nx++;
      ny++;

      if (colour & 0x40) {
	/* Y flip */
	if (colour &0x20) {
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = code+(nx-1)-nxs+0x10*(ny-1-nys);
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  draw_sprite(code2, sx,   sy,   map, 3, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8],sx, sy, map,3);
	      }
	    }
	  }
	} else { // flip y
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = code+nxs+0x10*(ny-1-nys);
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  draw_sprite(code2, sx,   sy,   map, 2, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8],sx,sy,map,2 );
	      }
	    }
	  }
	}
      } else {
	if (colour &0x20) {
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = code+(nx-1)-nxs+0x10*nys;
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  draw_sprite(code2, sx,   sy,   map, 1, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8], sx,sy,map,1);
	      }
	    }
	  }
	} else { // no flip
	  for (nys=0; nys<ny; nys++) {
	    for (nxs=0; nxs<nx; nxs++) {
	      int code2 = (code & ~0xf) + ((code + nxs) & 0xf) + 0x10*nys; /* pgear fix */
	      sx = (x+nxs*16+xoffs) & 0x3ff;
	      sy = (y+nys*16+yoffs) & 0x3ff;

	      if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		if (GFX_SPR_SOLID16[code2])
		  draw_sprite(code2, sx,   sy,   map, 0, priority);
		// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code2<<8],sx,sy, map,0);
	      }
	    }
	  }
	}
      }
    } else {
      /* Simple case... 1 sprite */
      int sx = (x+xoffs) & 0x3ff;
      int sy = (y+yoffs) & 0x3ff;
      if (sx < scrwidth && sy < scrheight && code <= max_sprites16) {
	if (GFX_SPR_SOLID16[code]) {
	  draw_sprite(code, sx,   sy,   map, (colour & 0x60)>>5, priority);
	}
	// Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8], sx, sy, map,(colour & 0x60)>>5);
      }
    }
  }
}

static void DrawTileQueue(int pri)
{
  struct TILE_Q *tile_ptr;
  UINT32 ta;

  tile_ptr = first_tile[pri];
  while(tile_ptr->next){
    ta = tile_ptr->tile;
    alpha_sprite(ta,tile_ptr->x,tile_ptr->y,tile_ptr->map, tile_ptr->flip);
    tile_ptr = tile_ptr->next;
  }
}

static void render_sprites()
{
  /* Draw the sprites */
  int i,baseadd;
  int n;

  UINT8 *base,*map;

  cps1_find_last_sprite();
  if (cps1_game_config->bootleg_kludge == 1 || cps1_game_config->bootleg_kludge == 2) {
    /* some sf2 hacks draw the sprites in reverse order */
    base = cps1_buffered_obj;
    baseadd = 8;
  } else {
    base = cps1_buffered_obj + (cps1_last_sprite_offset/8)*8;
    baseadd = -8;
  }
  /* Why are the sprites in the wrong order ??? */
  /* mame draws them from 0 to the end, and I must do the contrary !!! */

  for (i=cps1_last_sprite_offset; i>=0; i-=8) {
    UINT16 x=ReadWord(base) & 0x1ff;
    UINT16 y=ReadWord(base+2) & 0x1ff;
    UINT32 code=ReadWord(base+4) << 1;
    for (n=0; n<nb_sprites; n++) {
      if (code >= sprites_ranges[n].start && code <= sprites_ranges[n].end) {
	code = (sprites_ranges[n].base + (code & (sprites_ranges[n].mask))) >> 1;
	break;
      }
    }
    if (n < nb_sprites) { // the range is ok
      UINT16 colour=ReadWord(base+6);
      UINT16 col=colour&0x1f;

      MAP_PALETTE_MAPPED_NEW(
	  col,
	  16,
	  map
	  );

      /* in cawing, skyscrapers parts on level 2 have all the top bits of the */
      /* x coordinate set. Does this have a special meaning? */

      x-=0x20; // border
      y+=0x10;

      if (colour & 0xff00 ) {
	/* handle blocked sprites */
	UINT16 nx=(colour & 0x0f00) >> 8;
	UINT16 ny=(colour & 0xf000) >> 12;
	UINT16 nxs,nys,sx,sy;

	nx++;
	ny++;

	if (colour & 0x40) {
	  /* Y flip */
	  if (colour &0x20){ // flip xy
	    for (nys=0; nys<ny; nys++) {
	      for (nxs=0; nxs<nx; nxs++) {
		int code2 = (code+(nx-1)-nxs+0x10*(ny-1-nys));
		sx = (x+nxs*16) & 0x1ff;
		sy = (y+nys*16) & 0x1ff;
		if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16 ) {
		  if (GFX_SPR_SOLID16[code2])
		    alpha_sprite(code2,sx, sy, map,3);
		}
	      }
	    }
	  } else // flip y
	    for (nys=0; nys<ny; nys++) {
	      for (nxs=0; nxs<nx; nxs++) {
		int code2 = (code+nxs+0x10*(ny-1-nys));
		sx = (x+nxs*16) & 0x1ff;
		sy = (y+nys*16) & 0x1ff;

		if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		  if (GFX_SPR_SOLID16[code2])
		    alpha_sprite(code2,sx,sy,map,2 );
		}
	      }
	    }
	} else {
	  if (colour &0x20) { // flipy
	    for (nys=0; nys<ny; nys++) {
	      for (nxs=0; nxs<nx; nxs++) {
		int code2 = (code+(nx-1)-nxs+0x10*nys);
		sx = (x+nxs*16) & 0x1ff;
		sy = (y+nys*16) & 0x1ff;

		if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		  if (GFX_SPR_SOLID16[code2])
		    alpha_sprite(code2, sx,sy,map,1);
		}
	      }
	    }
	  } else { // no flip
	    for (nys=0; nys<ny; nys++) {
	      for (nxs=0; nxs<nx; nxs++) {
		int code2 = (code+nxs+0x10*nys);
		sx = (x+nxs*16) & 0x1ff;
		sy = (y+nys*16) & 0x1ff;

		if (sx < scrwidth && sy < scrheight && code2 <= max_sprites16) {
		  if (GFX_SPR_SOLID16[code2])
		    alpha_sprite(code2,sx,sy, map,0);
		}
	      }
	    }
	  } // no flip
	}
      } else {
	/* Simple case... 1 sprite does it happen ??? */
	if (x < scrwidth && y < scrheight && code <= max_sprites16) {
	  if (GFX_SPR_SOLID16[code])
	    alpha_sprite(code, x, y, map,(colour & 0x60)>>5);
	}
      }
    } // range ok
    base += baseadd;
  } // for i
}

static INT16 offsets[256];

// cps1_render_scroll2_bitmap : a real mess, mostly inspired from an old
// mame version. It has one advantage though : it allows to have the line
// scroll version and the normal version in only 1 function (!)
// Well, I must say this function is quite horrible. It tries to render the
// whole layer instead of drawing just what's relevant, that's why it can
// be used for line scroll too, but it's horribly unefficiant.
// If one day I feel extremely bored, I'll convert it to a shorter version
// for the normal drawing (no line scroll).
static void cps1_render_scroll2_bitmap(int mask)
{
  int sx, sy;
  int ny=(scroll2y>>4);   /* Rough Y */
  int nr;
  UINT8 *map,*dest;

  if (distort_scroll2) {
    // Check to see if using the lscroll version is really usefull...
    int otheroffs = cps1_port[CPS1_ROWSCROLL_OFFS],worthit=0;
    // RAM_LSCROLL must be computed here.
    RAM_LSCROLL = (INT16*)cps1_base(CPS1_OTHER_BASE,cps1_other_size);
    for (sx=0; sx<256; sx++) {
      offsets[sx] = -(RAM_LSCROLL[(sx+otheroffs)&0x3ff]);
      if (offsets[sx]) {
	worthit = offsets[sx];
      }
    }
    distort_scroll2 = worthit;
#ifdef RAINE_DEBUG
    if (worthit) {
      print_ingame(1,gettext("row scroll %d"),worthit);
    }
#endif
  }
  for (sx=CPS1_SCROLL2_WIDTH-1; sx>=0; sx--) {
    int n=ny;
    int offsx=(sx & 0x3f)<<6;
    int myx = (16*sx - scrlx) & 0x3ff;
    // if (myx < 0) myx += srcwidth;
    if (distort_scroll2 || (myx > 0 && myx <= scrwidth))
      for (sy=0x09*2-1; sy>=0; sy--) {
	int offsy, offs;
	UINT32 colour, code;

	n&=0x3f;
	offsy  = ((n&0x0f)*4 | ((n&0x30)*0x100))&0x3fff;
	offs=offsy+offsx;

	code=ReadWord(&RAM_SCROLL2[offs])<<1;
	for (nr=0; nr<nb_scroll2; nr++) {
	  if (code >= scroll2_ranges[nr].start && code <= scroll2_ranges[nr].end) {
	    code = (scroll2_ranges[nr].base + (code & (scroll2_ranges[nr].mask))) >> 1;
	    break;
	  }
	}
	if (nr < nb_scroll2 && GFX_SPR_SOLID16[code]) { // the range is ok

	    int myy = 16*n - scrly;
/*	    if (code && code != 0x2000) */

	      // We must warp around the bitmap... What a mess...
	      if (myy < 0) myy += srcheight;

	    if (myy> 0 && myy <= scrheight) {
	      colour=ReadWord(&RAM_SCROLL2[offs+2]);
	      INT16 *offs = &offsets[myy-16];
	      MAP_PALETTE_MAPPED_NEW(
				     (colour&0x1F) | 0x40,
				     16,
				     map
				     );
	      if (mask) {
		if (cps_version == 2) {
		  if (GFX_SPR_SOLID16[code]==1) {// Some pixels transp
		    if (distort_scroll2) {
		      pldraw16x16_Mask_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8], myx, myy, map,offs,(colour & 0x60)>>5,mask);
		    } else
		      pdraw16x16_Mask_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8],myx,myy,map,(colour & 0x60)>>5,mask);
		  } else { // all solid
		    if (distort_scroll2) {
		      pldraw16x16_Mask_Mapped_flip_Rot(&GFX_SPR16[code<<8], myx, myy, map,offs,(colour & 0x60)>>5,mask);
		    } else
		      pdraw16x16_Mask_Mapped_flip_Rot(&GFX_SPR16[code<<8],myx,myy,map,(colour & 0x60)>>5,mask);
		  }
		} else { // cps_version == 1 then...
		  dest = mask_sprite(16*16-1,&GFX_SPR16[code<<8],(colour & 0x180)>>7);

		  if (dest) {// We got something...
		    // line scrolls work correctly with priorities. Tested
		    // in 2nd stage of dino.
		    if (distort_scroll2)
		      ldraw16x16_Trans_Mapped_flip_Rot(dest, myx, myy, map,offs,(colour & 0x60)>>5);
		    else
		      Draw16x16_Trans_Mapped_flip_Rot(dest,myx,myy,map,(colour & 0x60)>>5);
		  }
#if VERBOSE
		  {
		    char buff[2];
		    sprintf(buff,"%x",(colour & 0x180)>>7);
		    textout_fast(buff,myx,myy,get_white_pen());
		  }
#endif
		}
	      } else {
		if (GFX_SPR_SOLID16[code]==1) {// Some pixels transp
		  if (distort_scroll2)
		    ldraw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8], myx, myy, map,offs,(colour & 0x60)>>5);
		  else
		    Draw16x16_Trans_Mapped_flip_Rot(&GFX_SPR16[code<<8],myx,myy,map,(colour & 0x60)>>5);
		} else { // all solid
		  if (distort_scroll2)
		    ldraw16x16_Mapped_flip_Rot(&GFX_SPR16[code<<8], myx, myy, map,offs,(colour & 0x60)>>5);
		  else
		    Draw16x16_Mapped_flip_Rot(&GFX_SPR16[code<<8],myx,myy,map,(colour & 0x60)>>5);
		}
	      }
	    }
	} // range ok
	n++;
      } // for (sy...
  } // for (sx...
}

static void cps1_render_scroll2(int mask)
{
  scroll2x=cps1_port[CPS1_SCROLL2_SCROLLX] + scroll2xoff;
  scroll2y=cps1_port[CPS1_SCROLL2_SCROLLY];
  if (scroll2x != oldx2 || scroll2y != oldy2) {
    oldx2 = scroll2x;
    oldy2 = scroll2y;
    scrly=-(scroll2y-0x20);
    scrlx=-(scroll2x+0x40-0x20);
#if 0
    if (cps1_flip_screen)
      {
	scrly=(CPS1_SCROLL2_HEIGHT*16)-scrly;
      }
#endif

    if (scrlx < 0) scrlx = (-scrlx) % srcwidth;
    else scrlx = srcwidth - scrlx % srcwidth;

    if (scrly < 0) scrly = (-scrly) % srcheight;
    else scrly = srcheight - (scrly % srcheight);
    scrly += 16;
  }

  cps1_render_scroll2_bitmap(mask);
}

static void render_scroll3(int mask)
{
  int x,y,code;
  UINT32 zzz,zzzz,zz,x16,y16;
  UINT16 scroll3x=cps1_port[CPS1_SCROLL3_SCROLLX]+scroll3xoff+64;
  UINT16 scroll3y=cps1_port[CPS1_SCROLL3_SCROLLY], colour;
  UINT8 *map,*dest;
  int n;

  MAKE_SCROLL_SCROLL3_4_32_YX(scroll3x,scroll3y);

  START_SCROLL_SCROLL3_4_32_YX(32,32,384,224);

  if (y >= 0) {
    code = (ReadWord(&RAM_SCROLL3[zz]) & 0x3fff) <<3;

    for (n=0; n<nb_scroll3; n++) {
      // printf("%d: %x <= %x <= %x (%d,%d)\n",n,scroll3_ranges[n].start,code,scroll3_ranges[n].end,x,y);
      if (code >= scroll3_ranges[n].start && code <= scroll3_ranges[n].end) {
	code = (scroll3_ranges[n].base + (code & (scroll3_ranges[n].mask))) >> 3;
	break;
      }
    }
    if (n < nb_scroll3 && GFX_SPR_SOLID32[code]) { // the range is ok
      colour=ReadWord(&RAM_SCROLL3[(zz+2)]);

      MAP_PALETTE_MAPPED_NEW(
	  (colour&0x1F) | 0x60,
	  16,
	  map
	  );

      // printf("%d,%d,%x (%x)\n",x,y,code,zz);
      if (mask) {
	if (cps_version == 2) {
	  if (GFX_SPR_SOLID32[code]==1) // Some pixels transp
	    pdraw32x32_Mask_Trans_Mapped_flip_Rot(&GFX_SPR32[code<<10],x,y,map,(colour & 0x60)>>5,mask);
	  else // all solid
	    pdraw32x32_Mask_Mapped_flip_Rot(&GFX_SPR32[code<<10],x,y,map,(colour & 0x60)>>5,mask);
	} else {
	  dest = mask_sprite(32*32-1,&GFX_SPR32[code<<10],(colour & 0x180)>>7);
	  if (dest) // we got something
	    Draw32x32_Trans_Mapped_flip_Rot(dest,x,y,map,(colour & 0x60)>>5);
	}
      } else {
	if (GFX_SPR_SOLID32[code]==1) // Some pixels transp
	  Draw32x32_Trans_Mapped_flip_Rot(&GFX_SPR32[code<<10],x,y,map,(colour & 0x60)>>5);
	else // all solid
	  Draw32x32_Mapped_flip_Rot(&GFX_SPR32[code<<10],x,y,map,(colour & 0x60)>>5);
      }
    }
  }
  END_SCROLL_SCROLL3_4_32_YX();
}

static void render_layer(int layer,int mask)
{
  // mask is one if we must draw the "high layer".
  // The high layer is the layer masked to show only a few colors. These
  // colors have priority over the sprites (hence the name).

  if (cps1_layer_enabled[layer] && check_layer_enabled(layer_id_data[layer])){

    switch(layer) {
    case 0: render_sprites(mask); break;
    case 1: render_scroll1(mask); break;
    case 2: cps1_render_scroll2(mask); break;
    case 3: render_scroll3(mask); break;
    }
  }
}

static void render_cps2_layer(int layer, int priority)
{
  // mask is one if we must draw the "high layer".
  // The high layer is the layer masked to show only a few colors. These
  // colors have priority over the sprites (hence the name).

  if (cps1_layer_enabled[layer] && check_layer_enabled(layer_id_data[layer])){

    switch(layer) {
    case 0: render_cps2_sprites(); break;
    case 1: render_scroll1(priority);
      break;
    case 2: cps1_render_scroll2(priority);
      break;
    case 3: render_scroll3(priority);
      break;
    }
  }
}

void draw_cps1(void)
{
   int layercontrol = cps1_port[cps1_game_config->layer_control/2];
   int l0 = (layercontrol >> 0x06) & 3,
     l1 = (layercontrol >> 0x08) & 3,
     l2 = (layercontrol >> 0x0a) & 3,
     l3 = (layercontrol >> 0x0c) & 3;
   // printf("lctrl %x l0 %x l1 %x l2 %x l3 %x\n",layercontrol,l0,l1,l2,l3);
   // UINT8 *map;

   // printf("%d %d %d %d\n",l0,l1,l2,l3);
   // printf("limits %x %x %x\n",base1,base2,base3);

   distort_scroll2 = cps1_port[0x11] & 0x01;
   // cps1_flip_screen=videocontrol&0x8000;
   RAM_SCROLL1 = cps1_base(CPS1_SCROLL1_BASE,cps1_scroll1_size);
   RAM_SCROLL2 = cps1_base(CPS1_SCROLL2_BASE,cps1_scroll2_size);
   RAM_SCROLL3 = cps1_base(CPS1_SCROLL3_BASE,cps1_scroll3_size);
   cps1_palette=cps1_base(CPS1_PALETTE_BASE,0x800);

     // Banks : 0..1f
     // pixel colors : 0..f.
   if (!old_palette) {
     InitPaletteMap(cps1_palette, 0xc0, 0x10, 0x10000);

     set_colour_mapper(color_mapper);
     old_palette = cps1_palette;
   } else {
     // sfzch for example is changing its palette all the time.
     // It does not show on screen. I suppose it is some kind of double buffering
     // and the 2 palettes are the same most of the time, but since there is no way
     // to tell, I am obliged to change the base like this (just does a RAM_PAL=src)
     silly_wgp_colour_ram(cps1_palette);
   }

   ClearPaletteMap();
   cps1_layer_enabled[0]=1;
   cps1_layer_enabled[1]=layercontrol & cps1_game_config->layer_enable_mask[0];
   cps1_layer_enabled[2]=layercontrol & cps1_game_config->layer_enable_mask[1];
   cps1_layer_enabled[3]=layercontrol & cps1_game_config->layer_enable_mask[2];
   cps1_stars_enabled	=layercontrol & cps1_game_config->layer_enable_mask[3];
   // printf("layer_enabled %d %d %d mask %x\n",cps1_layer_enabled[1],cps1_layer_enabled[2],cps1_layer_enabled[3],cps1_game_config->layer_enable_mask[0]);

   /* In the begining, I tried to draw the background with a solid layer... */
   /* Ecept that it does not work because the transparent color should not */
   /* be drawn at all (its palette is wrong sometimes). So I think the */
   /* best is simply to clear the screen this way... */
   /* Mame says cps1 uses color bff to clear the screen... well it's amazing
    * since there are only 0x800 colors used so far. Well their bff color seems
    * to work, but the orange background in the game selection for 3wonders
    * just looks wrong !!! So I'll keep it commented and continue to use the
    * black pen instead... */
/*   if (cps_version == 1) {
     MAP_PALETTE_MAPPED_NEW(
	 0xbf,
	 16,
	 map
	 );
     clear_game_screen(ReadLong(&map[0]));
   } else */
     clear_game_screen(0);

   update_transmasks();

   if (cps_version == 2) {
     int layer[3],layerpri[3];
     int nb = 0;
     int l0pri,l1pri,l2pri,l3pri;
/*      int primasks[8],i; */
     l0pri = (pri_ctrl >> 4*l0) & 0x0f;
     l1pri = (pri_ctrl >> 4*l1) & 0x0f;
     l2pri = (pri_ctrl >> 4*l2) & 0x0f;
     l3pri = (pri_ctrl >> 4*l3) & 0x0f;
     // printf("%d (%d) %d (%d) %d (%d) %d (%d)\n",l0,l0pri,l1,l1pri,l2,l2pri,l3,l3pri);

     /* No priorities handling yet. I have a feeling that I'll have to play again with
	the priority bitmap to handle them ! */
     /* Correction : very basic priority handling : we have l0, l1, l2, l3 which is the
	base order of the layers, and then the sprite order (from 0 to the end).
	There must be some problems left but a few games work this way ! */

     /* On this very basic priority emulation, if sprites are drawn first, then this
	is obviously wrong. They should be fixed using the color masks, but meanwhile
	I draw them at the end so that they show on screen at least !!! */

     ClearTileQueue();
     render_cps2_layer(0,0); // sprites
     TerminateTileQueue();

     if (l0) { layer[nb] = l0; layerpri[nb++] = l0pri; }
     if (l1) { layer[nb] = l1; layerpri[nb++] = l1pri; }
     if (l2) { layer[nb] = l2; layerpri[nb++] = l2pri; }
     if (l3) { layer[nb] = l3; layerpri[nb++] = l3pri; }

     if (nb) {
       if (pbitmap_needed) {
	 clear_bitmap(pbitmap);
	 render_cps2_sprites_pbitmap();
#if 0
	 render_cps2_layer(layer[2],layerpri[2]);
	 render_cps2_layer(layer[1],layerpri[1]);
	 render_cps2_layer(layer[0],layerpri[0]);
#else
	 render_cps2_layer(layer[0],layerpri[0]);
	 render_cps2_layer(layer[1],layerpri[1]);
	 render_cps2_layer(layer[2],layerpri[2]);
#endif
       } else {
	 for (nb=0; nb<=layerpri[0]; nb++) {
	   DrawTileQueue(nb);
	 }
	 render_cps2_layer(layer[0],0); // prio 1
	 for (nb=layerpri[0]+1; nb<=layerpri[1]; nb++) {
	   DrawTileQueue(nb);
	 }
	 render_cps2_layer(layer[1],0); // prio 2
	 for (nb=layerpri[1]+1; nb<=layerpri[2]; nb++) {
	   DrawTileQueue(nb);
	 }
	 render_cps2_layer(layer[2],0); // prio 4
	 for (nb=layerpri[2]+1; nb<=7; nb++) {
	   DrawTileQueue(nb);
	 }
       }
     }

     pri_ctrl = cps2_port(CPS2_OBJ_PRI);
     memcpy(cps2_buffered_obj, cps2_objbase(), cps2_obj_size);

   } else {

     render_layer(l0,0);
     render_layer(l1,0);
     if (l1==0) render_layer(l0,1); // masked
     render_layer(l2, 0);
     if (l2==0) render_layer(l1,1); // masked
     render_layer(l3,0);
     if (l3==0) render_layer(l2,1); // masked
     // delayed sprites
     if (cps1_game_config->bootleg_kludge)
	 cps1_port[CPS1_OBJ_BASE] = 0x9100;
     memcpy(cps1_buffered_obj, cps1_base(CPS1_OBJ_BASE, cps1_obj_size),cps1_obj_size);;
   }
}

