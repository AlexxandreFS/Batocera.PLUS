/******************************************************************************
*                  TETRIS 2 PLUS (C) JALECO
******************************************************************************/

#include "gameinc.h"
#include "debug.h"
#include "ymz280b.h"
#include "blit.h"
#include "sasound.h"

static struct YMZ280Binterface ymz280b_intf =
{
  1,
  { 16934400 },
  { REGION_SOUND1 },
   { YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT) },
   { NULL }
};

static struct SOUND_INFO sound_tetrisp2[] =
{
   { SOUND_YMZ280B,  &ymz280b_intf,  },
   { 0,             NULL,               },
};


static struct ROM_INFO rom_tetrisp2[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "t2p_04.rom",  0xe67f9c51, "t2p_01.rom",  0x5020a4ed),
  { "96019-01.9", 0x400000, 0x06f7dc64, REGION_GFX1, 0x000000, LOAD_16_32 },
	/* If t2p_m01&2 from this board were correctly read, since they
       hold the same data of the above but with swapped halves, it
       means they had to invert the top bit of the "page select"
       register in the sprite's hardware on this board! */
  { "96019-02.8", 0x400000, 0x3e613bed, REGION_GFX1, 0x000002, LOAD_16_32 },
  { "96019-06.13", 0x400000, 0x16f7093c, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "96019-04.6", 0x100000, 0xb849dec9, REGION_GFX2, 0x400000, LOAD_NORMAL },
  { "96019-04.6", 0x100000, 0xb849dec9, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "tetp2-10.bin", 0x080000, 0x34dd1bad, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "96019-07.7", 0x400000, 0xa8a61954, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_tetrisp2[] =
{
   INP0( COIN1, 0x0a0004, 0x40 ),
   INP0( COIN2, 0x0a0004, 0x80 ),
   INP0( SERVICE, 0x0a0004, 0x20 ),

   INP0( P1_START, 0x0a0004, 0x04 ),
   INP0( P1_UP, 0x0a0002, 0x01 ),
   INP0( P1_DOWN, 0x0a0002, 0x02 ),
   INP0( P1_LEFT, 0x0a0002, 0x04 ),
   INP0( P1_RIGHT, 0x0a0002, 0x08 ),
   INP0( P1_B1, 0x0a0002, 0x10 ),
   INP0( P1_B2, 0x0a0002, 0x20 ),
   INP0( P1_B3, 0x0a0002, 0x40 ),
   INP0( P1_B4, 0x0a0002, 0x80 ),

   INP0( P2_START, 0x0a0004, 0x08 ),
   INP0( P2_UP, 0x0a0003, 0x01 ),
   INP0( P2_DOWN, 0x0a0003, 0x02 ),
   INP0( P2_LEFT, 0x0a0003, 0x04 ),
   INP0( P2_RIGHT, 0x0a0003, 0x08 ),
   INP0( P2_B1, 0x0a0003, 0x10 ),
   INP0( P2_B2, 0x0a0003, 0x20 ),
   INP0( P2_B3, 0x0a0003, 0x40 ),
   INP0( P2_B4, 0x0a0003, 0x80 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_tetrisp2_0[] =
{
   { MSG_COIN1,               0x07, 0x08 },
   { MSG_1COIN_1PLAY,         0x07},
   { MSG_1COIN_2PLAY,         0x06},
   { MSG_1COIN_3PLAY,         0x05},
   { MSG_1COIN_4PLAY,         0x04},
   { MSG_2COIN_1PLAY,         0x03},
   { MSG_3COIN_1PLAY,         0x02},
   { MSG_4COIN_1PLAY,         0x01},
   { MSG_5COIN_1PLAY,         0x00},
   { MSG_COIN2,               0x38, 0x08 },
   { MSG_1COIN_1PLAY,         0x38},
   { MSG_1COIN_2PLAY,         0x30},
   { MSG_1COIN_3PLAY,         0x28},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x18},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x08},
   { MSG_5COIN_1PLAY,         0x00},
   { MSG_FREE_PLAY,             0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   DSW_TEST_MODE( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_tetrisp2_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_HARDEST,             0x02},
   { MSG_HARD,                0x01},
   { MSG_EASY,                0x00},
   { _("Vs Mode Rounds"),        0x04, 0x02 },
   { "3",                     0x04},
   { "1",                     0x00},
   { _("Language"),              0x08, 0x02 },
   { _("Japanese"),              0x08},
   { _("English"),               0x00},
   { _("FBI Logo"),              0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { _("Voice"),                 0x20, 0x02 },
   { MSG_ON,                  0x20},
   { MSG_OFF,                 0x00},
   DSW_DEMO_SOUND( 0x40, 0x00),
   DSW_SCREEN( 0x80, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_tetrisp2[] =
{
   { 0x0a0008, 0xFF, dsw_data_tetrisp2_0 },
   { 0x0a0009, 0xFF, dsw_data_tetrisp2_1 },
   { 0,        0,    NULL,      },
};

static GfxLayout layout_8x8x8 =
{
	8,8,
	RGN_FRAC(1,1),
	8,
	{ STEP8(0,1) },
	{ STEP8(0,8) },
	{ STEP8(0,8*8) },
	8*8*8
};

static GfxLayout layout_16x16x8 =
{
	16,16,
	RGN_FRAC(1,1),
	8,
	{ STEP8(0,1) },
	{ STEP16(0,8) },
	{ STEP16(0,16*8) },
	16*16*8
};

static struct GFX_LIST tetrisp2_gfx[] =
{
	{ REGION_GFX1, &layout_8x8x8 }, // 0x10 color banks (sprites)
	{ REGION_GFX2, &layout_16x16x8 }, // 0x10 color banks (background)
	{ REGION_GFX3, &layout_16x16x8 }, // 0x10 color banks (rotation)
	{ REGION_GFX4, &layout_8x8x8 }, // 0x10 color banks (foreground)
	{ 0, NULL }
};

static void sound_tetrisp2_w(UINT32 offset, UINT16 data)
{
  if (offset & 2)	YMZ280B_data_0_w     (offset, data & 0xff);
  else		YMZ280B_register_0_w (offset, data & 0xff);
}

static UINT8 *ram_spr,
  *ram_pri,
  *ram_fg,
  *ram_bg,
  *ram_rot,
  *nvram,
  *ram_scroll_fg,
  *ram_scroll_bg,
  *ram_rotregs,
  *ram_sysregs,
  *ram_pal;

static char *layer_id_name[4] =
{
   "rot", "bg", "fg", "sprites",
};
static int layer_id_data[4];

static void nvram_w(UINT32 offset,UINT8 data) {
  // swaps the normal order of starscream
  RAM[(0x01a000 + (offset & 0x3fff))] = data;
}

static int clear_pal;

/* This handler does not speed up the game very much (less than 1% at 1900 Mhz),
   but since the palette is big, and the game does not change it all the time, it's
   usefull */
static void write_pal(UINT32 offset, UINT16 data) {
  offset &= 0x1FFFF;
  if (ReadWord(&ram_pal[offset]) != data) {
    WriteWord(&ram_pal[offset],data);
    clear_pal = 1;
  }
}

static void load_tetrisp2(void)
{
   int n;

   for (n=0; n<4; n++) {
     layer_id_data[n] = add_layer_info(layer_id_name[n]);
   }

   RAMSize=0xa0010 + 0x40 + 0x30 + 0x20;

   if(!(RAM=AllocateMem(RAMSize))) return;
   memset(RAM+0x00000,0x00,0xa0000);
   memset(RAM+0xa0000,0xFF,0x00010);

   WriteWord68k(&ROM[0x02D4A],0x4E71);

   WriteWord68k(&ROM[0x02D54],0x4E71);
   // WriteWord68k(&ROM[0x04e6e],0x4E71); // prevent a weird div by 0 at the end of a game ?

/*    WriteLong68k(&ROM[0x02D98],0x4E714E71); */

/*    WriteWord68k(&ROM[0x02DA4],0x6000); */

   InitPaletteMap(RAM+0x60000, 0x80, 0x100, 0x8000);

   set_colour_mapper(&col_map_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x080000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   ram_spr = RAM;
   ram_pri = RAM+0x020000;
   ram_fg = RAM+0x010000;
   ram_bg = RAM+0x014000;
   ram_rot = RAM+0x088000;
   nvram = RAM+0x01a000;
   ram_scroll_fg = RAM+0xa0010;
   ram_scroll_bg = RAM+0xa0020;
   ram_rotregs = RAM+0xa0050;
   ram_sysregs = RAM+0xa0080;
   ram_pal = RAM + 0x60000;

   AddReadBW(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddRWBW(0x400000, 0x409FFF, NULL, RAM+0x010000);			// FG0/BG0 RAM

   // the nvram is special as often with the nvram anyway : it writes in bytes
   // and read in words, but expects that bytes are inverted when reading !
   AddReadWord(0x900000, 0x903fff, NULL, RAM+0x01a000); // nvram
   AddReadWord(0x904000, 0x907fff, NULL, RAM+0x01a000); // nvram (mirror)
   AddWriteByte(0x900000, 0x903fff, nvram_w, NULL); // nvram
   AddWriteByte(0x904000, 0x907fff, nvram_w, NULL); // nvram (mirror)

   // AddRWBW(0x904000, 0x907fff, NULL, RAM+0x01a000); // nvram (mirror)
   AddRWBW(0x200000, 0x23FFFF, NULL, RAM+0x020000);			// ? RAM
   AddWriteWord(0x300000, 0x31ffff, write_pal, NULL);
   AddRWBW(0x300000, 0x31FFFF, NULL, RAM+0x060000);			// COLOR RAM
   AddRWBW(0x500000, 0x50fFFF, NULL, RAM+0x080000);			// ? RAM
   AddRWBW(0x600000, 0x60FFFF, NULL, RAM+0x090000);			// rot RAM
   AddRWBW(0x650000, 0x65FFFF, NULL, RAM+0x090000);			// rot RAM (mirror)
   AddReadBW(0xBE0000, 0xBE000F, NULL, RAM+0x0a0000);			// inputs
   AddRWBW(0xb40000, 0xb4003f, NULL,   RAM+0x0a0010);
   AddRWBW(0xb60000, 0xb6002f, NULL,   RAM+0x0a0050);
   AddRWBW(0xba0000, 0xba001f, NULL,   RAM+0x0a0080);
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x800000, 0x800003, sound_tetrisp2_w, NULL);

   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_tetrisp2(void)
{
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
  cpu_interrupt(CPU_68K_0, 2);
}

/* From mame :
    [ 2 Scrolling Layers ]

    The Background is a 64 x 64 Tilemap with 16 x 16 x 8 tiles (1024 x 1024).
    The Foreground is a 64 x 64 Tilemap with 8 x 8 x 8 tiles (512 x 512).
    Each tile needs 4 bytes.

    [ 1024? Sprites ]

    Sprites are "nearly" tile based: if the data in the ROMs is decoded
    as 8x8 tiles, and each 32 consecutive tiles are drawn like a column
    of 256 pixels, it turns out that every 32 x 32 tiles form a picture
    of 256 x 256 pixels (a "page").

    Sprites are portions of any size from those page's graphics rendered
    to screen
*/

static void draw_tilemap16(int width, int height, UINT8 *gfx, UINT8 *gfx_solid, int scrollx, int scrolly, UINT8 *ram, int colbase) {
  int x,y, zz, zzz, zzzz, x16, y16;
  UINT16 code;
  UINT8 *map;

  MAKE_SCROLL_n_16(width,height,4,scrollx,scrolly);
  START_SCROLL_16(32,32,320,224);
  {
    code = ReadWord(&ram[zz]);
    if (gfx_solid[code]) {
      MAP_PALETTE_MAPPED_NEW(
			     colbase | (ram[zz+2] & 0xf),
			     256,
			     map);
      if (gfx_solid[code] == 1)
	Draw16x16_Trans_Mapped_Rot(&gfx[code<<8],x,y,map);
      else
	Draw16x16_Mapped_Rot(&gfx[code<<8],x,y,map);
    }
  }
  END_SCROLL_n_16(width,height,4);
}

// This one is not generic, we have only 1 8x8 tilemap
static void draw_tilemap8( UINT8 *gfx, UINT8 *gfx_solid, int scrollx, int scrolly, int colbase) {
  int x,y, zz, zzz, zzzz, x16, y16;
  UINT16 code;
  UINT8 *map;

  MAKE_SCROLL_512x512_4_16(scrollx,scrolly);
  START_SCROLL_512x512_4_16(32,32,320,224);
  {
    code = ReadWord(&ram_fg[zz]);
    if (gfx_solid[code]) {
      MAP_PALETTE_MAPPED_NEW(
			     colbase | (ram_fg[zz+2] & 0xf),
			     256,
			     map);
      if (gfx_solid[code] == 1)
	Draw8x8_Trans_Mapped_Rot(&gfx[code<<6],x,y,map);
      else
	Draw8x8_Mapped_Rot(&gfx[code<<6],x,y,map);
    }
  }
  END_SCROLL_512x512_4_16();
}

static void draw_sprites() {
  INT16 *source = (INT16 *)ram_spr;
  INT16 *debut = source;
  INT16 *finish = source + (0x4000-0x10)/2;
  /* priority ram is totally ignored.
     I guess this would be used in any multi layers game, but for a tetris, it's a little
     over done... and their priority system is super complex. I found out that you get
     a near perfect result by just drawing the sprites after the layers, starting from the
     end of the sprites area. Much easier and much faster. */
  // UINT16 *priority_ram = (UINT16*)ram_pri;
  UINT8 *spr = gfx[0];
  UINT8 *spr_solid = gfx_solid[0];
  UINT8 *map;

  for (source = finish; source >= debut; source -= 0x10/2 ) {
    INT16 sx, sy, xnum, ynum, xstart, ystart, xend, yend, xinc, yinc, x, y;
    UINT16 attr, flipx, flipy, color, tx, ty, xsize, ysize, size;
    UINT32 code;

    attr	=	source[ 0 ];

    if ((attr & 0x0004) == 0)			continue;

    flipx	=	attr & 1;
    flipy	=	attr & 2;

    code	=	source[ 1 ];
    color	=	source[ 2 ];

    tx		=	(code >> 0) & 0xff;
    ty		=	(code >> 8) & 0xff;

    code	=	(tx / 8) +
      (ty / 8) * (0x100/8) +
      (color & 0x7f) * (0x100/8) * (0x100/8);

    color	=	(color >> 12) & 0xf;

    size	=	source[ 3 ];

    xsize	=	((size >> 0) & 0xff) + 1;
    ysize	=	((size >> 8) & 0xff) + 1;

    xnum	=	( ((tx + xsize) & ~7) + (((tx + xsize) & 7) ? 8 : 0) - (tx & ~7) ) / 8;
    ynum	=	( ((ty + ysize) & ~7) + (((ty + ysize) & 7) ? 8 : 0) - (ty & ~7) ) / 8;

    sy		=	source[ 4 ];
    sx		=	source[ 5 ];

    sx		=	(sx & 0x3ff) - (sx & 0x400) + 32;
    sy		=	(sy & 0x1ff) - (sy & 0x200) + 32;

    if (sx > 320+32 || sx + xsize - 1 < 32 || sy > 224+32 || sy + ysize -1 < 32) continue;

    if (flipx)	{ xstart = xnum-1;  xend = -1;    xinc = -1;  sx -= xnum*8 - xsize - (tx & 7); }
    else		{ xstart = 0;       xend = xnum;  xinc = +1;  sx -= tx & 7; }

    if (flipy)	{ ystart = ynum-1;  yend = -1;    yinc = -1;  sy -= ynum*8 - ysize - (ty & 7); }
    else		{ ystart = 0;       yend = ynum;  yinc = +1;  sy -= ty & 7; }

    MAP_PALETTE_MAPPED_NEW(
			   color,
			   256,
			   map);

    for (y = ystart; y != yend; y += yinc)
      {
	int dy = sy+y*8;
	if (dy > 224 + 32) break;
	if (dy < 24) { code	+=	(0x100/8) - xnum + (xend-xstart)/xinc; continue; }
	for (x = xstart; x != xend; x += xinc)
	  {
	    if (spr_solid[code]) {
	      int dx = sx+x*8;
	      if (dx > 320+32) { code++; continue; }

	      if (spr_solid[code] == 1)
		Draw8x8_Trans_Mapped_flip_Rot(&spr[code<<6],dx,dy,map,flipx | flipy);
	      else
		Draw8x8_Mapped_flip_Rot(&spr[code<<6],dx,dy,map,flipx | flipy);
	    }
	    code++;
	  }
	code	+=	(0x100/8) - xnum;
      }
  }	/* end sprite loop */
}

static void draw_tetrisp2(void)
{
   int asc_pri = 0, scr_pri = 0, rot_pri = 0;

   if (clear_pal) {
     ClearPaletteMap();
     clear_pal = 0;
   }

   clear_game_screen(0); // usefull ?

   if((ram_pri[0x2b00]) == 0x0034)
     asc_pri++;
   else
     rot_pri++;

   if((ram_pri[0x2e00]) == 0x0034)
     asc_pri++;
   else
     scr_pri++;

   if((ram_pri[0x3a00]) == 0x000c)
     scr_pri++;
   else
     rot_pri++;

   /* I am not convinced that sprite priorities are usefull for a tetris game ! */
   if (rot_pri == 0 && check_layer_enabled(layer_id_data[0]))
     draw_tilemap16(2048, 2048, gfx[2],gfx_solid[2], ReadWord(&ram_rotregs[0])-0x400,
		    ReadWord(&ram_rotregs[4]), ram_rot, 0x20);
   else if (scr_pri == 0 && check_layer_enabled(layer_id_data[1]))
     draw_tilemap16(1024, 1024, gfx[1], gfx_solid[1], (ReadWord(&ram_scroll_bg[0])+0x14 + ReadWord(&ram_scroll_bg[4])) & 0xffff, (ReadWord(&ram_scroll_bg[6]) + ReadWord(&ram_scroll_bg[10])) & 0xffff, ram_bg, 0x10);
   else if (asc_pri == 0 && check_layer_enabled(layer_id_data[2]))
     draw_tilemap8(gfx[3],gfx_solid[3],ReadWord(&ram_scroll_fg[4]),ReadWord(&ram_scroll_fg[10]),0x60);

   if (rot_pri == 1 && check_layer_enabled(layer_id_data[0]))
     draw_tilemap16(2048, 2048, gfx[2],gfx_solid[2], ReadWord(&ram_rotregs[0])-0x400,
		    ReadWord(&ram_rotregs[4]), ram_rot, 0x20);
   else if (scr_pri == 1 && check_layer_enabled(layer_id_data[1]))
     draw_tilemap16(1024, 1024, gfx[1], gfx_solid[1], (ReadWord(&ram_scroll_bg[0])+0x14 + ReadWord(&ram_scroll_bg[4])) & 0xffff, (ReadWord(&ram_scroll_bg[6]) + ReadWord(&ram_scroll_bg[10])) & 0xffff, ram_bg, 0x10);
   else if (asc_pri == 1 && check_layer_enabled(layer_id_data[2]))
     draw_tilemap8(gfx[3],gfx_solid[3],ReadWord(&ram_scroll_fg[4]),ReadWord(&ram_scroll_fg[10]),0x60);

   if (rot_pri == 2 && check_layer_enabled(layer_id_data[0]))
     draw_tilemap16(2048, 2048, gfx[2],gfx_solid[2], ReadWord(&ram_rotregs[0])-0x400,
		    ReadWord(&ram_rotregs[4]), ram_rot, 0x20);
   else if (scr_pri == 2 && check_layer_enabled(layer_id_data[1]))
     draw_tilemap16(1024, 1024, gfx[1], gfx_solid[1], (ReadWord(&ram_scroll_bg[0])+0x14 + ReadWord(&ram_scroll_bg[4])) & 0xffff, (ReadWord(&ram_scroll_bg[6]) + ReadWord(&ram_scroll_bg[10])) & 0xffff, ram_bg, 0x10);
   else if (asc_pri == 2 && check_layer_enabled(layer_id_data[2]))
     draw_tilemap8(gfx[3],gfx_solid[3],ReadWord(&ram_scroll_fg[4]),ReadWord(&ram_scroll_fg[10]),0x60);

   if (check_layer_enabled(layer_id_data[3]))
       draw_sprites();
}

/*

JALECO MEGA SYSTEM-32
---------------------

CPU: 68000 (68020?)

-------+--------+-------------------
Start  | End    | Contents
-------+--------+-------------------
000000 | 0FFFFF | PROGRAM  ROM
108000 | 10FFFF | SCRATCH  RAM
400000 | 403FFF | ASCII    RAM (FG0)
404000 | 407FFF | SCROLL   RAM (BG0)
500000 | 507FFF | ROTATE   RAM
100000 | 103FFF | OBJECT   RAM
300000 | 301FFF | COLOR    RAM
304000 | 305FFF | COLOR    RAM
308000 | 30BFFF | COLOR    RAM
318000 | 31BFFF | COLOR    RAM (FG0)
200000 | 23FFFF | PRIORITY RAM
-------+--------+-------------------

FG0 RAM
-------

- 8x8 tiles
- 4 bytes per tile
- 64x64 tiles; 512x512 layer

-----+--------+---------------------
Byte | Bit(s) | Use
-----+76543210+---------------------
  1  |xxxxxxxx| Tile Number
  3  |....xxxx| Colour Bank
-----+--------+---------------------

BG0 RAM
-------

- 16x16 tiles
- 4 bytes per tile
- 64x64 tiles; 1024x1024 layer

-----+--------+---------------------
Byte | Bit(s) | Use
-----+76543210+---------------------
  0  |...xxxxx| Tile Number (high)
  1  |xxxxxxxx| Tile Number (low)
  3  |....xxxx| Colour Bank
-----+--------+---------------------

*/


static struct VIDEO_INFO video_tetrisp2 =
{
   draw_tetrisp2,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP, // 604 colors on the title screen !
   tetrisp2_gfx,
};
static struct DIR_INFO dir_tetrisp2[] =
{
   { "tetris_2_plus", },
   { "tetris2p", },
   { "tetrisp2", },
   { NULL, },
};
GME( tetrisp2, "Tetris 2 Plus", JALECO, 1996, GAME_PUZZLE);

