/*

Original MAME driver by Nicola Salmoria.
Converted to Raine by Anders Granlund.

A few bugs fixed by Emmanuel Anne. Interesting driver, by the way :
the first to render directly a true color bitmap in raine.
Well finally, I rewrote most of it, but I kept the code to convert colors
to 8bpp.

Notes : service mode in galpanic shows a bad palette in 8bpp.
This is normal : the 8bpp conversion relies on the initialisation of the
palette with the static colours of the game, but these colors are not there
while in service mode.
Anyway, I strongly discourage using 8bpp with these games : they often use
2000 colors on screen, and converting this to 8bpp takes a lot of time !

The ideal colour depth is 15 or 16 bpp (the games are true 15bpp games).

missw96 and fantsia2 do not seem to have any service mode ??!

*/


#include "gameinc.h"
#include "taitosnd.h"
#include "sasound.h"
#include "adpcm.h"
#include "blit.h"

static void   galpanic_closest_colour_init(void);
UINT16 galpanic_closest_colour(int r, int g, int b);


static struct ROM_INFO rom_galpanic[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x20000,
            "pm112.6",  0x7b972b58 , "pm111.5",  0x4eb7298d ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x80000,
            "pm005e.7",  0xd7ec650c,"pm004e.8",  0xd3af52bc  ),
  LOAD8_16(  REGION_ROM1,  0x200000,  0x80000,
            "pm001e.14",  0x90433eb1, "pm000e.15",  0x5d220f3f ),
  LOAD8_16(  REGION_ROM1,  0x300000,  0x80000,
            "pm003e.16",  0x6bb060fd, "pm002e.17",  0x713ee898 ),
  { "pm006e.67", 0x100000, 0x57aec037 , REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "pm008e.l", 0x80000, 0xd9379ba8 , REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "pm008e.l", 0x80000, 0xd9379ba8 , REGION_SMP1, 0x40000, LOAD_NORMAL },
  { "pm007e.u", 0x80000, 0xc7ed7950 , REGION_SMP1, 0xc0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_fantasia[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x80000,
            "prog2_16.rom",  0xe27c6c57 , "prog1_13.rom",  0x68d27413 ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x80000,
            "iscr6_09.rom",  0x2a588393 , "iscr5_05.rom",  0x6160e0f0 ),
  LOAD8_16(  REGION_ROM1,  0x200000,  0x80000,
            "iscr4_08.rom",  0xf776b743 , "iscr3_04.rom",  0x5df0dff2 ),
  LOAD8_16(  REGION_ROM1,  0x300000,  0x80000,
            "iscr2_07.rom",  0x5707d861 , "iscr1_03.rom",  0x36cb811a ),
  LOAD8_16(  REGION_ROM1,  0x400000,  0x80000,
            "imag2_10.rom",  0x1f14a395 , "imag1_06.rom",  0xfaf870e4 ),
  { "obj1_17.rom", 0x80000, 0xaadb6eb7 , REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "mus-1_01.rom", 0x80000, 0x22955efb , REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "mus-1_01.rom", 0x80000, 0x22955efb , REGION_SMP1, 0x40000, LOAD_NORMAL },
  { "mus-2_02.rom", 0x80000, 0x4cd4d6c3 , REGION_SMP1, 0xc0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_newfant[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x80000,
            "prog2_12.rom",  0xde43a457 , "prog1_07.rom",  0x370b45be ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x80000,
            "iscr2_10.rom",  0x4f2da2eb , "iscr1_05.rom",  0x63c6894f ),
  LOAD8_16(  REGION_ROM1,  0x200000,  0x80000,
            "iscr4_09.rom",  0x725741ec , "iscr3_04.rom",  0x51d6b362 ),
  LOAD8_16(  REGION_ROM1,  0x300000,  0x80000,
            "iscr6_08.rom",  0x178b2ef3 , "iscr5_03.rom",  0xd2b5c5fa ),
  LOAD8_16(  REGION_ROM1,  0x400000,  0x80000,
            "iscr8_11.rom",  0xf4148528 , "iscr7_06.rom",  0x2dee0c31 ),
  { "obj1_13.rom", 0x80000, 0xe6d1bc71 , REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "musc1_01.rom", 0x80000, 0x10347fce , REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "musc1_01.rom", 0x80000, 0x10347fce , REGION_SMP1, 0x40000, LOAD_NORMAL },
  { "musc2_02.rom", 0x80000, 0xb9646a8c , REGION_SMP1, 0xc0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_missw96[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x80000,
            "mw96_10.bin",  0xb1309bb1 , "mw96_06.bin",  0xa5892bb3 ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x80000,
            "mw96_09.bin",  0x7032dfdf , "mw96_05.bin",  0x91de5ab5 ),
  LOAD8_16(  REGION_ROM1,  0x200000,  0x80000,
            "mw96_08.bin",  0xb8e66fb5 , "mw96_04.bin",  0xe77a04f8 ),
  LOAD8_16(  REGION_ROM1,  0x300000,  0x80000,
            "mw96_07.bin",  0x26112ed3 , "mw96_03.bin",  0xe9374a46 ),
  { "mw96_11.bin", 0x80000, 0x3983152f , REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "mw96_01.bin", 0x80000, 0xe78a659e , REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "mw96_01.bin", 0x80000, 0xe78a659e , REGION_SMP1, 0x40000, LOAD_NORMAL },
  { "mw96_02.bin", 0x80000, 0x60fa0c00 , REGION_SMP1, 0xc0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_fantsia2[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x80000,
            "prog2.g17",  0x57c59972 , "prog1.f17",  0xbf2d9a26 ),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x80000,
            "scr2.g16",  0x887b1bc5 , "scr1.f16",  0xcbba3182 ),
  LOAD8_16(  REGION_ROM1,  0x200000,  0x80000,
            "scr4.g15",  0xce97e411 , "scr3.f15",  0x480cc2e8 ),
  LOAD8_16(  REGION_ROM1,  0x300000,  0x80000,
            "scr6.g14",  0xb29d49de , "scr5.f14",  0xd5f88b83 ),
  LOAD8_16(  REGION_ROM1,  0x400000,  0x80000,
            "scr8.g20",  0x694ae2b3 , "scr7.f20",  0x6068712c ),
  { "obj1.1i", 0x80000, 0x52e6872a , REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "obj2.2i", 0x80000, 0xea6e3861 , REGION_GFX1, 0x80000, LOAD_NORMAL },
  { "music2.1b", 0x80000, 0x23cc4f9c , REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "music2.1b", 0x80000, 0x23cc4f9c , REGION_SMP1, 0x40000, LOAD_NORMAL },
  { "music1.1a", 0x80000, 0x864167c2 , REGION_SMP1, 0xc0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_newfant[] =
{
   INP0( COIN1, 0x080005, 0x04 ),
   INP0( COIN2, 0x080005, 0x08 ),

   INP0( TILT, 0x080005, 0x20 ),
   INP0( SERVICE, 0x080005, 0x40 ),

   INP0( P1_START, 0x080005, 0x01 ),
   INP0( P1_UP, 0x080001, 0x01 ),
   INP0( P1_DOWN, 0x080001, 0x02 ),
   INP0( P1_LEFT, 0x080001, 0x04 ),
   INP0( P1_RIGHT, 0x080001, 0x08 ),
   INP0( P1_B1, 0x080001, 0x10 ),
   INP0( P1_B2, 0x080001, 0x20 ),

   INP0( P2_START, 0x080005, 0x02 ),
   INP0( P2_UP, 0x080003, 0x01 ),
   INP0( P2_DOWN, 0x080003, 0x02 ),
   INP0( P2_LEFT, 0x080003, 0x04 ),
   INP0( P2_RIGHT, 0x080003, 0x08 ),
   INP0( P2_B1, 0x080003, 0x10 ),
   INP0( P2_B2, 0x080003, 0x20 ),

   END_INPUT
};

static struct ROMSW_DATA romswd_galpanic[] =
{
  { "Japan", 0x1},
  { "US",0x2},
  { "World", 0x3},
  { NULL,                    0    },
};

static struct ROMSW_INFO romsw_galpanic[] =
{
   { 0x03ffff, 0x03, romswd_galpanic },
   { 0,        0,    NULL },
};

/* Dipswitch 2 */

static struct DSW_DATA dsw_data_galpanic_0[] =
{
  DSW_UNUSED( 0x0000, 0x0001),
  { MSG_UNKNOWN, 0x0002, 2 },
  { MSG_OFF, 0x0002},
  { MSG_ON, 0x0000},
  DSW_SERVICE( 0, 0x0004),
  DSW_UNUSED( 0x0000, 0x0008),
  { MSG_COIN1, 0x0030, 4 },
  { MSG_4COIN_1PLAY, 0x0000},
  { MSG_3COIN_1PLAY, 0x0010},
  { MSG_2COIN_1PLAY, 0x0020},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_1COIN_3PLAY, 0x0080},
  { MSG_1COIN_4PLAY, 0x0040},
  { MSG_1COIN_6PLAY, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_galpanic_1[] =
{
  { MSG_DIFFICULTY, 0x0003, 4 },
  { _("Easy") , 0x0002},
  { _("Normal") , 0x0003},
  { _("Hard") , 0x0001},
  { _("Hardest") , 0x0000},
  DSW_UNUSED( 0x0000, 0x0004),
  DSW_UNUSED( 0x0000, 0x0008),
  { MSG_LIVES, 0x0030, 4 },
  { "2" , 0x0010},
  { "3" , 0x0030},
  { "4" , 0x0020},
  { "5" , 0x0000},
  { MSG_UNKNOWN, 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  { _("Character Test"), 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_galpanic[] =
{
   { 0x080000, 0xFf, dsw_data_galpanic_0 },
   { 0x080002, 0xFF, dsw_data_galpanic_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_fantasia_0[] =
{
  { MSG_DIFFICULTY, 0x0003, 4 },
  { _("Easy") , 0x0002},
  { _("Normal") , 0x0003},
  { _("Hard") , 0x0001},
  { _("Hardest") , 0x0000},
  DSW_UNUSED( 0x0000, 0x0004),
  { MSG_UNKNOWN, 0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { MSG_LIVES, 0x0030, 4 },
  { "2" , 0x0010},
  { "3" , 0x0030},
  { "4" , 0x0020},
  { "5" , 0x0000},
  { MSG_UNKNOWN, 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  DSW_UNUSED( 0x0000, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_fantasia_1[] =
{
  DSW_UNUSED( 0x0000, 0x0001),
  { MSG_UNKNOWN, 0x0002, 2 },
  { MSG_OFF, 0x0002},
  { MSG_ON, 0x0000},
  DSW_SERVICE( 0, 0x0004),
  { _("Coin Mode"), 0x0008, 2 },
  { _("Mode 1") , 0x0008},
  { _("Mode 2") , 0x0000},
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0020},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_1COIN_1PLAY, 0x0010},
  { MSG_1COIN_6PLAY, 0x0000},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0080},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_1COIN_1PLAY, 0x0040},
  { MSG_1COIN_6PLAY, 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_newfant[] =
{
   { 0x080000, 0xFf, dsw_data_fantasia_0 },
   { 0x080002, 0xFF, dsw_data_fantasia_1 },
   { 0,        0,    NULL,      },
};

static struct DSW_DATA dsw_data_missw96_1[] =
{
  DSW_UNUSED( 0x0000, 0x0001),
  { MSG_UNKNOWN, 0x0002, 2 },
  { MSG_OFF, 0x0002},
  { MSG_ON, 0x0000},
  DSW_UNUSED( 0x0000, 0x0004),
  { _("Coin Mode"), 0x0008, 2 },
  { _("Mode 1") , 0x0008},
  { _("Mode 2") , 0x0000},
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0020},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_1COIN_1PLAY, 0x0010},
  { MSG_1COIN_6PLAY, 0x0000},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0080},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_1COIN_1PLAY, 0x0040},
  { MSG_1COIN_6PLAY, 0x0000},
  { NULL, 0}
};

// no service mode in missw96 ?!!!
static struct DSW_INFO dsw_fantsia2[] =
{
   { 0x080000, 0xFf, dsw_data_fantasia_0 },
   { 0x080002, 0xFF, dsw_data_missw96_1 },
   { 0,        0,    NULL,      },
};

static GfxLayout spritelayout =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0, 1, 2, 3 },
	{ 0*4, 1*4, 2*4, 3*4, 4*4, 5*4, 6*4, 7*4,
			64*4, 65*4, 66*4, 67*4, 68*4, 69*4, 70*4, 71*4 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32,
			16*32, 17*32, 18*32, 19*32, 20*32, 21*32, 22*32, 23*32 },
	128*8
};

static struct GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &spritelayout },
	{ 0, NULL } /* end of array */
};

static struct OKIM6295interface galpanic_m6295_interface =
{
	1,          /* 1 chip */
	{ 12000 },	/* 12000 KHz */
	{ REGION_SOUND1 },  	/* memory region (not yet !) */
	{ 255 }	/* volume */
};

static struct SOUND_INFO sound_newfant[] =
{
   { SOUND_M6295,   &galpanic_m6295_interface,     },
   { 0,             NULL,                 },
};


static UINT8 *GFX_SOLID;

static UINT8 *RAM_SPR;
static UINT8 *RAM_BG;
static UINT8 *RAM_FG;

static UINT8 *VIDEO_BG;
static UINT8 *VIDEO_FG;
static UINT8 *VIDEO_PAL;
static UINT8 *VIDEO_ALPHA;
static int clear_pal;;

// To choose if we want rotation or not
static void (*update_fg)(UINT32,UINT16);

static void galpanic_fg_write_b_rot( UINT32 address, UINT8 data ){
	UINT32 offs;

	// Write to real foreground data
	if((address&0x01)==1)	offs = address-0x500001;
	else				offs = address-0x4FFFFF;
	RAM[offs] = data;

	//
	//  Draw foreground layer.
	//
	//  The foreground layer use only the first 256 colors from
	//  the main palette.
	//
	//  We don't do much here other than to rotate the data 90 degrees.
	//
	if(offs<0x1E000){
		// Rotate screen
		offs>>=1;
		offs = (((~offs)<<8)&0xFF00) | (0xFF - (offs>>8));
		offs &= 0xFFFF;
		// Draw to foreground ram
		VIDEO_FG[ offs] = data;
	}
}

static void galpanic_fg_write_b_norot( UINT32 address, UINT8 data ){
	UINT32 offs;

	// Write to real foreground data
	if((address&0x01)==1)	offs = address-0x500001;
	else				offs = address-0x4FFFFF;
	RAM[offs] = data;

	//
	//  Draw foreground layer.
	//
	//  The foreground layer use only the first 256 colors from
	//  the main palette.
	//
	//  We don't do much here other than to rotate the data 90 degrees.
	//
	if(offs<0x1E000){
		offs>>=1;
		// Draw to foreground ram
		VIDEO_FG[ offs] = data;
	}
}

static void galpanic_fg_write_w_rot( UINT32 address, UINT16 data ){
	UINT32 offs;

	// Write to real background data
	if((address&0x01)==1)	offs = address-0x500001;
	else			offs = address-0x500000;
	WriteWord(&RAM[offs], data);

	//
	//  Draw foreground layer.
	//
	//  See the function above for comments...
	//
	if(offs<0x1E000){
		// rotate screen 90 degrees
		offs>>=1;
		offs = (((~offs)<<8)&0xFF00) | (0xFF-(offs>>8));
		offs &= 0xFFFF;
		// write to foreground ram
		VIDEO_FG[ offs] = data&0xFF;
		VIDEO_FG[ offs - 256] = data>>8;
	}
}

static void galpanic_fg_write_w_norot( UINT32 address, UINT16 data ){
	UINT32 offs;

	// Write to real background data
	if((address&0x01)==1)	offs = address-0x500001;
	else				offs = address-0x500000;
	WriteWord(&RAM[offs], data);

	//
	//  Draw foreground layer.
	//
	//  See the function above for comments...
	//
	if(offs<0x1E000){
		offs>>=1;
		// write to foreground ram
		WriteWord(&VIDEO_FG[ offs], data);
	}
}

// to chosse with or without rotation
static void (*update_bg)(UINT32,UINT16);

static void update_bg_rotation(UINT32 address, UINT16 data) {
  UINT32 col;
  UINT8 r,g,b;
  UINT16 offs;

  WriteWord(&RAM[address-0x500000],data);
  offs = (address - 0x520000)>>1;
  // rotate screen 90 degrees
  offs = (((~offs)<<8)&0xFF00) | (0xFF-(offs>>8));

  //  Draw background layer for 8bit video modes
  //
  //  The game feeds us 16bit RGB data, so we need to
  //  make a closest colour search to find a suitable palette entry
  //  instead (in 8bpp).
  //  We look for colours in the games dynamic palette of 1024 colors.
  //  Colors 384 to 512 seem to stay static during the game so we can take
  //  one of them.
  //
  //  Needless to say this is *very* cpu intensive. Luckily the game doesn't
  //  draw to the background layer very often
  //
  //  Also, the background layer RAM is shared with the games Work-Ram so
  //  we don't do any close-colour finding for all pixels in the background layer ram.
  //

    // decode color to 16bit "xRRRRRGGGGGBBBBB" format
  r = (data & 0x07C0) >> 3;
  g = (data & 0xF800) >> 8;
  b = (data & 0x003E) << 2;
  switch (display_cfg.bpp) {
  case 8:
    VIDEO_BG[offs] = galpanic_closest_colour(r>>3,g>>3,b>>3)-256;
    return;
  case 15:
    WriteWord(&VIDEO_BG[offs<<1], makecol15(r,g,b));
    return;
  case 16:
    WriteWord(&VIDEO_BG[offs<<1], makecol16(r,g,b));
    return;
  }
  // default : 32 bpp
  col = makecol32(r,g,b);
  WriteLong(&VIDEO_BG[offs<<2],col);
}

static void update_bg_no_rotation(UINT32 address, UINT16 data) {
  UINT32 col;
  UINT8 r,g,b;
  UINT16 offs;
  // same thing, without the rotation of the bitmap, and without comments !
  WriteWord(&RAM[address-0x500000],data);
  offs = (address - 0x520000)>>1;

  r = (data & 0x07C0) >> 3;
  g = (data & 0xF800) >> 8;
  b = (data & 0x003E) << 2;
  switch (display_cfg.bpp) {
  case 8:
    VIDEO_BG[offs] = galpanic_closest_colour(r>>3,g>>3,b>>3)-256;
    return;
  case 15: data = makecol15(r,g,b);
    WriteWord(&VIDEO_BG[offs<<1], data);
    return;
  case 16: data = makecol16(r,g,b);
    WriteWord(&VIDEO_BG[offs<<1], data);
    return;
  }
  // default : 32 bpp
  col = makecol32(r,g,b);
  WriteLong(&VIDEO_BG[offs<<2],col);
}

static void (*draw_sprites)();

static UINT16 kludge(UINT32 offset) {
  return rand() & 0x700;
}

static UINT16 kludge_b(UINT32 offset) {
  return rand() & 0x7;
}

static void pal_write(UINT32 offset, UINT16 data) {
  // This function is here because the palette is not updated very often
  // in the games, and we need all the time the 1st 512 colors.
  // So clearing the palette and recalculating all these colors for each
  // frame is simply a waste of time !

  WriteWord(&RAM_PAL[offset - 0x600000],data);
  clear_pal = 1;
}

// these variables change if the screen is rotated or not
static int xstart, xend, xinc;
static int ystart, yend, yinc;
static int video_offset;

static void load_galpanic_actual(void)
{
  int code_size = get_region_size(REGION_CPU1);
  int norot = 0; // rotation by default

   if(!(RAM=AllocateMem(0x150000)))    return;


   RAM_FG	= RAM + 0x000000;
   RAM_BG	= RAM + 0x020000;
   RAM_PAL	= RAM + 0x040000;
   VIDEO_ALPHA	= RAM + 0x040800; // used to know if a color is transparent
   RAM_SPR   	= RAM + 0x041000;
   VIDEO_PAL	= RAM + 0x046000; // used for 8bpp color conversions

   // These buffers are generated from the game bitmap
   // they should not be saved in savegames
   VIDEO_FG	= RAM + 0x100000;
   VIDEO_BG	= RAM + 0x110000;

   GFX_SOLID = NULL;

   // RAM
   memset(RAM+0x00000, 0x00, 0x80000);		// game ram
   memset(RAM+0x80000, 0xFF, 0x20000);		// extra raine ram
   memset(RAM+0x100000, 0x00, 0x10000);		// extra fg ram
   memset(RAM+0x110000, 0x00, 0x20000);		// extra bg ram

   // Color Palette
   InitPaletteMap(RAM_PAL, 0x40, 0x10, 0x8000);
   set_colour_mapper(&col_map_15bit_grbx);
   galpanic_closest_colour_init();

   if (VIDEO_ROTATE( current_game->video->flags ) == VIDEO_ROTATE_90) {
     update_bg = update_bg_rotation;
     update_fg = galpanic_fg_write_w_rot;
     xstart = 224;    xend = 0; xinc = -1;
     ystart = 256+31; yend = 31; yinc = -1;
     video_offset = 32;
   } else {
     update_bg = update_bg_no_rotation;
     update_fg = galpanic_fg_write_w_norot;
     norot = 1;
     xstart = 256; xend = 0; xinc = -1;
     ystart = 32;   yend = 224+31; yinc = 1;
     video_offset = 0;
   }

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,code_size);

   AddMemFetch(0x000000, code_size - 1, ROM);				// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadBW(0x000000, code_size-1, NULL, ROM+0x000000);			// MRA16_ROM
   AddReadBW(0x500000, 0x51FFFF, NULL, RAM_FG);			// MRA16_RAM
   AddReadBW(0x520000, 0x53FFFF, NULL, RAM_BG);			// MRA16_RAM
   // AddWriteWord(0x600000, 0x6007FF, galpanic_Palette_Write, NULL);                 // MRA16_RAM
   AddWriteWord(0x600000, 0x6007FF, pal_write, NULL);
   AddRWBW(0x600000, 0x6007FF, NULL, RAM_PAL);                 // MRA16_RAM
   //AddWriteByte(0x600000, 0x6007FF, palette_write_b, NULL);                 // MRA16_RAM
   AddRWBW(0x700000, 0x7047FF, NULL, RAM_SPR);                 // MRA16_RAM
   AddReadBW(0x800000, 0x800005, NULL, RAM+0x080000);	// inputs

   if (!strcmp(current_game->main_name,"galpanic")) {
     RAMSize = 0x50000;
     AddReadBW(0x400000, 0x400001, OKIM6295_status_0_r, NULL);  	      // ADPCM CHANNEL A
   } else if (!strcmp(current_game->main_name,"fantsia2")) {
     // fantasia 2
     RAMSize = 0x60000; // 1 more ram pages...
     AddRWBW(0xf80000, 0xf8ffff, NULL, RAM+0x50000); // fantasia
     AddReadWord(0x800008,0x800009, kludge, NULL); /* bits 8-a = timer? palette update code waits for them to be 111 */
     AddReadByte(0x800008,0x800009, kludge_b, NULL); /* bits 8-a = timer? palette update code waits for them to be 111 */
     AddReadByte(0xf00000, 0xf00000, OKIM6295_status_0_r, NULL);  	      // ADPCM CHANNEL A
     AddReadByte(0xc80000, 0xc80000, OKIM6295_status_0_r, NULL);  	      // ADPCM CHANNEL A
     AddWriteByte(0xc80000, 0xc80000, OKIM6295_data_0_w, NULL);		// ADPCM CHANNEL A
   } else {
     // Comad memory map
     RAMSize = 0x70000; // 2 more ram pages...
     AddRWBW(0xc00000, 0xc0ffff, NULL, RAM+0x50000); // missw96
     AddRWBW(0xc80000, 0xc8ffff, NULL, RAM+0x60000); // fantasia
     AddReadWord(0x80000a,0x80000d, kludge, NULL); /* bits 8-a = timer? palette update code waits for them to be 111 */
     AddReadByte(0x80000a,0x80000d, kludge_b, NULL); /* bits 8-a = timer? palette update code waits for them to be 111 */
     AddReadByte(0xf00000, 0xf00000, OKIM6295_status_0_r, NULL);  	      // ADPCM CHANNEL A
     AddReadByte(0xf80000, 0xf80000, OKIM6295_status_0_r, NULL);  	      // ADPCM CHANNEL A
     AddWriteByte(0xf00000, 0xf00000, OKIM6295_data_0_w, NULL);		// ADPCM CHANNEL A
     AddWriteByte(0xf80000, 0xf80000, OKIM6295_data_0_w, NULL);		// ADPCM CHANNEL A
   }

   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);


   AddReadWord(0x000000, 0xFFFFFF, DefBadReadByte, NULL);			// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x400000, 0x400001, OKIM6295_data_0_w, NULL);		// ADPCM CHANNEL A
   if (norot)
     AddWriteByte(0x500000, 0x51FFFF, galpanic_fg_write_b_norot, NULL);		// MWA16_RAM (video ram)
   else
     AddWriteByte(0x500000, 0x51FFFF, galpanic_fg_write_b_rot, NULL);		// MWA16_RAM (video ram)
   //AddWriteByte(0x520000, 0x53FFFF, galpanic_bg_write_b, NULL);		// MWA16_RAM (video + work ram)
   AddWriteByte(0x520000, 0x53FFFF, NULL, RAM_BG);		// MWA16_RAM (video + work ram)
   AddWriteByte(0x900000, 0x900001, M6295_A_WriteBank_68k, NULL);    	// ADPCM BANKSWITCH
   AddWriteByte(0xa00000, 0xa00001, NULL, RAM+0x80006);			// ???
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);   // Trap Idle 68000
   AddWriteByte(0xb00000, 0xb00001, NULL, RAM+0x80008);			// ???
   AddWriteByte(0xc00000, 0xc00001, NULL, RAM+0x8000A);			// ???
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);			// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);


   if (norot)
     AddWriteWord(0x500000, 0x51FFFF, galpanic_fg_write_w_norot, NULL);		// MWA16_RAM (fg_video ram)
   else
     AddWriteWord(0x500000, 0x51FFFF, galpanic_fg_write_w_rot, NULL);		// MWA16_RAM (fg_video ram)
   AddWriteWord(0x520000, 0x53FFFF, update_bg, NULL);		// MWA16_RAM (bg_video + work ram)
   AddWriteWord(0x900000, 0x900001, M6295_A_WriteBank_68k, NULL);		// ADPCM BANKSWITCH
   AddWriteWord(0x400000, 0x400001, OKIM6295_data_0_w, NULL);		// ADPCM CHANNEL A

   AddWriteWord(0xa00000, 0xa00001, NULL, RAM+0x80006);			// ???
   AddWriteWord(0xb00000, 0xb00001, NULL, RAM+0x80008);			// ???
   AddWriteWord(0xc00000, 0xc00001, NULL, RAM+0x8000A);			// ???
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);			// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   // speed hack
   if (!strcmp(current_game->main_name,"galpanic")) {
     WriteWord(&ROM[0x13b6],0x4eb9); // jmp $c0 (end of rom)
     WriteWord(&ROM[0x13b8],0x0);
     WriteWord(&ROM[0x13ba],0xc0);
   } else if (!strcmp(current_game->main_name,"fantsia2") ||
	      !strcmp(current_game->main_name,"missw96")) {
     WriteWord(&ROM[0x610],0x4eb9); // jmp $c0 (end of rom)
     WriteWord(&ROM[0x612],0x0);
     WriteWord(&ROM[0x614],0xc0);
   } else if (!strcmp(current_game->main_name,"fantasia") ||
	      !strcmp(current_game->main_name,"newfant")) {
     WriteWord(&ROM[0x61c],0x4eb9); // jmp $c0 (end of rom)
     WriteWord(&ROM[0x61e],0x0);
     WriteWord(&ROM[0x620],0xc0);
   }

   WriteWord(&ROM[0xc0],0x4239); // clr.b $aa0000
   WriteWord(&ROM[0xc2],0xaa);
   WriteWord(&ROM[0xc4],0);
   WriteWord(&ROM[0xc6],0x60f8); // brak 3FFFB0 (loop)

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_newfant(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));
   cpu_interrupt(CPU_68K_0, 5);					// int5 updates palette
   cpu_interrupt(CPU_68K_0, 3);					// int3 drives the game
}

static void draw_galpanic_sprites() {
   int sx,sy,x,y,offs;
   int code,color;
   UINT8 attr1,attr2,*map;

   sx = sy = 0;
   for(offs=0; offs<0x4800/2; offs+=16){

     attr2		= RAM_SPR[offs + (7<<1)];
     code		= RAM_SPR[offs + (6<<1)] + ((attr2 & 0x1f) << 8);

     attr1		= RAM_SPR[offs + (3<<1)];
     x		= RAM_SPR[offs + (4<<1)] - ((attr1 & 0x01) << 8);
     y		= RAM_SPR[offs + (5<<1)] + ((attr1 & 0x02) << 7);

     // bit 0 [offs + 0] is used but I don't know what for

     if (attr1 & 0x04){	// Multi sprite
       sx += x;
       sy += y;
     }else{			// Single sprite
       sx = x;
       sy = y;
     }

     color = 16+((attr1 & 0xf0) >> 4);

     if(GFX_SOLID[code]){

       if( sx>-32 && sy>0 && sx<256 && sy<288){
	 // set palette
	 MAP_PALETTE_MAPPED_NEW(color, 16, map);

	 // draw palette
	 if(GFX_SOLID[code]==1){			// Some pixels; trans
	   switch(attr2&0xC0){
	   case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[code<<8], sx+32, sy+16, map);        break;
	   case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[code<<8], sx+32, sy+16, map);  break;
	   case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[code<<8], sx+32, sy+16, map);  break;
	   case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[code<<8], sx+32, sy+16, map); break;
	   }
	 } else{						// all pixels; solid
	   switch(attr2&0xC0){
	   case 0x00: Draw16x16_Mapped_Rot(&GFX[code<<8], sx+32, sy+16, map);        break;
	   case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[code<<8], sx+32, sy+16, map);  break;
	   case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[code<<8], sx+32, sy+16, map);  break;
	   case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[code<<8], sx+32, sy+16, map); break;
	   }
	 }
       }
     }
   } // for...
}

static void draw_comad_sprites() {
   int sx,sy,offs;
   int code,color;
   UINT8 *map;

   for(offs=0; offs<0x1000; offs+=8){

     sx = (ReadWord(&RAM_SPR[offs + 2*2]) >> 6)+32;
     sy = (ReadWord(&RAM_SPR[offs + 3*2]) >> 6)+32;
     code = ReadWord(&RAM_SPR[offs + 1*2]);
     color = 16+((RAM_SPR[offs] & 0x3c) >> 2);

     if(GFX_SOLID[code]){

       if( sx>=0 && sy>=32 && sx<256+32 && sy<224+32){
	 // set palette
	 MAP_PALETTE_MAPPED_NEW(color, 16, map);

	 // draw palette
	 if(GFX_SOLID[code]==1){			// Some pixels; trans
	   switch(RAM_SPR[offs]&3){
	   case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[code<<8], sx, sy, map);        break;
	   case 0x2: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[code<<8], sx, sy, map);  break;
	   case 0x1: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[code<<8], sx, sy, map);  break;
	   case 0x3: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[code<<8], sx, sy, map); break;
	   }
	   //Draw16x16_Trans_Mapped_flip_Rot(&GFX[code<<8], sx, sy, map,RAM_SPR[offs] & 3);
	   //Draw16x16_Trans_Mapped_Rot(&GFX[code<<8], scx, scy, map);
	 } else{						// all pixels; solid
	   switch(RAM_SPR[offs]&3){
	   case 0x00: Draw16x16_Mapped_Rot(&GFX[code<<8], sx, sy, map);        break;
	   case 0x2: Draw16x16_Mapped_FlipY_Rot(&GFX[code<<8], sx, sy, map);  break;
	   case 0x1: Draw16x16_Mapped_FlipX_Rot(&GFX[code<<8], sx, sy, map);  break;
	   case 0x3: Draw16x16_Mapped_FlipXY_Rot(&GFX[code<<8], sx, sy, map); break;
	   }
	   //Draw16x16_Mapped_flip_Rot(&GFX[code<<8], sx, sy, map,RAM_SPR[offs] & 3);
	 }
       }
     }
   } // for...
}

static void DrawGalPanic(void)
{
   int x,y;
   UINT8 *video;
   UINT8 *map;
   static UINT8 transp[256]; // transparent color ?

   if (!GFX_SOLID) {
     GFX_SOLID = gfx_solid[0];
   }

   if (clear_pal) {
     ClearPaletteMap();
     clear_pal = 0;
     MAP_PALETTE_MAPPED_NEW(0, 512, map);
     for (x=0; x<256; x++)
       transp[x] = (ReadWord(&RAM_PAL[x<<1]) & 1);
   } else
     MAP_PALETTE_MAPPED_NEW(0, 512, map);


   //-----------------------------------------------------------------------------
   // VIDEO
   //-----------------------------------------------------------------------------
   video = VIDEO_FG + video_offset; // the bitmpa is 256x256 and we display 256x224
   // (because of the size of the real screen).

   if(RefreshBuffers){
     UINT32 ofs,ofs2;
     // This is to regenrate the fg and bg buffers after either a resolution
     // change or the loading of a savegame...
     // Restore FG
     for (ofs = 0x500000, ofs2=0; ofs < 0x51ffff; ofs += 2, ofs2 += 2)
       update_fg(ofs,ReadWord(&RAM_FG[ofs2]));

     // restore BG
     for (ofs = 0x520000, ofs2=0; ofs < 0x53ffff; ofs += 2, ofs2 += 2)
       update_bg(ofs,ReadWord(&RAM_BG[ofs2]));
   }

   // draw 256 lines high
   // forget the putpixel version. Apparently it's awfully slower.
   if (display_cfg.bpp == 8) {
     UINT8 *line;

     for(y=ystart; y!=yend; y+=yinc){

       line = GameBitmap->line[y]+32;

       // draw 240 pixels wide
       // (we are skipping the first 16 pixels since they are not used).
       for(x=xstart;x!=xend; x+=xinc){

	 // Transparency handled by bit 0 in palette ?
	 // It's true at least for galpanic...
	 if(!transp[*video]) {
	   // draw foreground
	   *line++ = map[*video];
	 }
	 else
	   {
	   // draw background
	     *line++ = map[*(video + 0x10000) + 256];
	 }
	 video++;
       }
       video+=video_offset;
     }
   } else if (display_cfg.bpp == 15 || display_cfg.bpp == 16) {
     UINT16 *map16 = (UINT16 *)map;
     UINT16 *line;
     UINT16 *videobg = (UINT16*)(VIDEO_BG)+video_offset;
     UINT16 offset = 0;
     for(y=ystart; y!=yend; y+=yinc){

       line = ((UINT16*)GameBitmap->line[y])+32;

       // draw 224 pixels wide
       // (skiping the border)

       for(x=xstart;x!=xend; x+=xinc){
	 if(!transp[video[offset]]) {
	   // draw foreground
	   *line++ = map16[video[offset]];
	 }
	 else
	   {
	   // draw background
	     *line++ = ReadWord(&videobg[offset]);
	   }

	 offset++;
       }
       offset+=video_offset;
     }
   } else if (display_cfg.bpp > 16) {
     UINT32 *map32 = (UINT32 *)map;
     UINT32 *line;
     UINT32 *videobg = (UINT32*)(VIDEO_BG)+video_offset;
     UINT16 offset = 0;

     for(y=ystart; y!=yend; y+=yinc){

       line = ((UINT32*)GameBitmap->line[y])+32;

       // draw 240 pixels wide
       // (we are skipping the first 16 pixels since they are not used).

       for(x=xstart;x!=xend; x+=xinc){

	 if(!transp[video[offset]]) {
	   // draw foreground
	   *line++ = map32[video[offset]];
	 }
	 else
	 {
	   // draw background
	   *line++ = ReadLong(&videobg[offset]);
	 }
	 offset++;
       }
       offset+=video_offset;
     }
   }

   //-----------------------------------------------------------------------------
   // SPRITES
   //-----------------------------------------------------------------------------
   draw_sprites();
}

/******************************************************************************/
/*                                                                            */
/*                     CLOSEST MATCHING COLOUR ROUTINE                        */
/*                                                                            */
/*	( Ripped from "palette.c" and modified to suit this game better )		*/
/*													*/
/******************************************************************************/

static UINT32 gal_col_diff[128*3];

static void galpanic_closest_colour_init(void)
{
   int i;
   for(i=1; i<64; i++){
      int k = i * i;
      gal_col_diff[0  +i] = gal_col_diff[0  +128-i] = k * (59 * 59);
      gal_col_diff[128+i] = gal_col_diff[128+128-i] = k * (30 * 30);
      gal_col_diff[256+i] = gal_col_diff[256+128-i] = k * (11 * 11);
   }
}

/*
Find the best fitting colour from the dynamic palette (512 colours)
*/

UINT16 galpanic_closest_colour(int r, int g, int b)
{
   int i, coldiff, lowest, bestfit, color;
   RGB rgb;

   bestfit = 0;
   lowest = 0xFFFF;

   // Let's choose from only colors in the range of 384 to 512.
   // We know that these colors stay static during the game
   // so it's a good idea to take one of them.
   i = 256+128;

   do{
	color = ReadWord(&RAM_PAL[i<<1]);
	rgb.g = (color >> 11) & 0x1F;
	rgb.r = (color >> 6)  & 0x1F;
	rgb.b = (color >> 1)  & 0x1F;

      coldiff = (gal_col_diff + 0) [ (rgb.g - g) & 0x7F ];
      if (coldiff < lowest) {
	 coldiff += (gal_col_diff + 128) [ (rgb.r - r) & 0x7F ];
	 if (coldiff < lowest) {
	    coldiff += (gal_col_diff + 256) [ (rgb.b - b) & 0x7F ];
	    if (coldiff < lowest) {
	       bestfit = i;
	       if (coldiff == 0)
		  return bestfit;
	       lowest = coldiff;
	    }
	 }
      }
       i++;
   }while(i<512);

   return bestfit;
}

static void load_galpanic() {
  draw_sprites = &draw_galpanic_sprites;
  load_galpanic_actual();
}

static void load_newfant() {
  draw_sprites = &draw_comad_sprites;
  load_galpanic_actual();
}

// Notice : the video is not really rotatable, but I get strange things
// if I remove ROTATABLE. I didn't investigate.
// it's not rotatable because of the fg and bg bitmaps (directly rendered).
// Adding rotation is possible, but boring, and useless for most people.






static struct VIDEO_INFO video_fantsia2 =
{
   DrawGalPanic,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   gfxdecodeinfo
};
static struct VIDEO_INFO video_newfant =
{
   DrawGalPanic,
   256,
   224,
   32,
   VIDEO_ROTATE_90 | VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   gfxdecodeinfo
};
static struct DIR_INFO dir_galpanic[] =
{
   { "galpanic", 		},
   { "GalPanic",		},
   { NULL, },
};
GAME( galpanic, "Gals Panic", KANEKO, 1990, GAME_ADULT,
	.input = input_newfant,
	.dsw = dsw_galpanic,
	.romsw = romsw_galpanic,
	.video = &video_newfant,
	.exec = execute_newfant,
	.long_name_jpn = "Gals Panic",
	.sound = sound_newfant,
);
GMEI( newfant, "New Fantasia", COMAD, 1995, GAME_ADULT);
CLNEI( fantasia, newfant,"Fantasia", COMAD, 1994, GAME_ADULT);
CLNEI( fantsia2, newfant, "Fantasia II", COMAD, 1997, GAME_ADULT,
	.dsw = dsw_fantsia2,
	.video = &video_fantsia2,
);
CLNEI( missw96, newfant,"Miss World '96 Nude", COMAD, 1996, GAME_ADULT,
	.dsw = dsw_fantsia2,
	.video = &video_fantsia2,
);

