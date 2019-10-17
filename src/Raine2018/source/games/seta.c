#define DRV_DEF_SOUND sound_arbalest
/******************************************************************************/
/*                                                                            */
/*                        LAME SETA GAMES (C) 19xx SETA                       */
/*                                                                            */
/******************************************************************************/

/* Not so lame actually, but I keep the original comment (funny).
   This comment from Antiriad was probably out of frustration since he was trying
   to emulate a 65ce02 without knowing it was a 65ce02 and his cpu emulator didn't
   support it !

   So I used this driver to first upgrade our 6502 emulator to support the 65ce02
   and since the seta games were not bad at all after all, I added a few pure 68k
   games too. As often in these times, big thanks go to the mame devs for their source
   code which was an unvaluable source of information !

   About the pure 68k games : this driver shows a few tricks to make them to work,
   from the weird palette mappings, to the weird use of interrupts (rezon).
   There are also a few oddities in the way roms are loaded/decoded sometimes.

   I like this driver a lot in fact, some of the games are as good as the cave games
   without all their stupid sprite size changes !

   TODO : some games use dipswitches on 16 bits. We can't handle them for now.
          Maybe I can find a trick to handle this differently, or extend the dipswitches
	  to allow 16 bits entries...
	  For now it's handled by adding the "alt license" dip switch on the 2nd byte
	  This "feature" is used only by the games reading their dsw with a 6502, I think
	  this "alt license" dsw is more than enough to handle it.
*/

/* Use the xsystem1 video engine to draw the sprites ?
   You'd better leave this commented : for one thing this engine starts by clearing
   the screen, it's not supposed to work with layers.
   For another, it does not support sprites banks and finally it adapts very badly
   to borders != 32 (it can be adapted but the code is really old and used by quite lots
   of games, so I prefer to handle the sprites here, locally)
   Maybe the 2 versions should be merged, but only once I am sure the one in this driver
   is perfect !
 */
// #define USE_XSYSTEM

#include "gameinc.h"
#include "m6502.h"
#include "m6502hlp.h"		// M6502/M6510 support interface
#include "sasound.h"
#include "x1_010.h"
#include "2203intf.h"
#include "3812intf.h"
#include "adpcm.h"
#include "blit.h" // clear_game_screen
#ifdef USE_XSYSTEM
#include "setax1.h"
#endif
#include "gun.h"

static struct INPUT_INFO input_arbalest[] =
{
  INP0( TILT, 0xb000, 0x10 ),
  INP0( SERVICE, 0xb000, 0x20 ),
  INP0( COIN2, 0x0b000, 0x40 ),
  INP0( COIN1, 0x0b000, 0x80 ),

   INP0( P1_UP, 0x0b002, 0x01 ),
   INP0( P1_DOWN, 0x0b002, 0x02 ),
   INP0( P1_LEFT, 0x0b002, 0x04 ),
   INP0( P1_RIGHT, 0x0b002, 0x08 ),
   INP0( P1_B1, 0x0b002, 0x10 ),
   INP0( P1_B2, 0x0b002, 0x20 ),
   INP0( P1_START, 0x0b002, 0x80 ),

   INP0( P2_UP, 0x0b006, 0x01 ),
   INP0( P2_DOWN, 0x0b006, 0x02 ),
   INP0( P2_LEFT, 0x0b006, 0x04 ),
   INP0( P2_RIGHT, 0x0b006, 0x08 ),
   INP0( P2_B1, 0x0b006, 0x10 ),
   INP0( P2_B2, 0x0b006, 0x20 ),
   INP0( P2_START, 0x0b006, 0x80 ),

   END_INPUT
};

static struct INPUT_INFO input_calibr50[] =
{
   INP0( P1_UP, 0xc000, 0x01 ),
   INP0( P1_DOWN, 0xc000, 0x02 ),
   INP0( P1_LEFT, 0xc000, 0x04 ),
   INP0( P1_RIGHT, 0xc000, 0x08 ),
   INP0( P1_B1, 0xc000, 0x10 ),
   INP0( P1_B2, 0xc000, 0x20 ),
   INP0( P1_START, 0xc000, 0x80 ),

   INP0( B1_L, 0x0c001, 0x01 ),
   INP0( B1_R, 0x0c001, 0x02 ),
   INP0( B2_L, 0x0c001, 0x04 ),
   INP0( B2_R, 0x0c001, 0x08 ),

   INP0( P2_UP, 0xc002, 0x01 ),
   INP0( P2_DOWN, 0xc002, 0x02 ),
   INP0( P2_LEFT, 0xc002, 0x04 ),
   INP0( P2_RIGHT, 0xc002, 0x08 ),
   INP0( P2_B1, 0xc002, 0x10 ),
   INP0( P2_B2, 0xc002, 0x20 ),
   INP0( P2_START, 0xc002, 0x80 ),

  INP0( TILT, 0xc008, 0x10 ),
  INP0( SERVICE, 0xc008, 0x20 ),
  INP0( COIN2, 0xc008, 0x40 ),
  INP0( COIN1, 0xc008, 0x80 ),

   END_INPUT
};

static struct INPUT_INFO input_downtown[] =
{
  INP0( TILT, 0xb000, 0x10 ),
  INP0( SERVICE, 0xb000, 0x20 ),
  INP0( COIN2, 0x0b000, 0x40 ),
  INP0( COIN1, 0x0b000, 0x80 ),

   INP0( P1_UP, 0x0b002, 0x01 ),
   INP0( P1_DOWN, 0x0b002, 0x02 ),
   INP0( P1_LEFT, 0x0b002, 0x04 ),
   INP0( P1_RIGHT, 0x0b002, 0x08 ),
   INP0( P1_B1, 0x0b002, 0x10 ),
   INP0( P1_B2, 0x0b002, 0x20 ),
   INP0( P1_B3, 0x000000, 0x40 ),
   INP0( P1_START, 0x0b002, 0x80 ),

   INP0( P2_UP, 0x0b006, 0x01 ),
   INP0( P2_DOWN, 0x0b006, 0x02 ),
   INP0( P2_LEFT, 0x0b006, 0x04 ),
   INP0( P2_RIGHT, 0x0b006, 0x08 ),
   INP0( P2_B1, 0x0b006, 0x10 ),
   INP0( P2_B2, 0x0b006, 0x20 ),
   INP0( P2_START, 0x0b006, 0x80 ),

   INP0( B1_L, 0x0b007, 0x01 ),
   INP0( B1_R, 0x0b007, 0x02 ),
   INP0( B2_L, 0x0b007, 0x04 ),
   INP0( B2_R, 0x0b007, 0x08 ),

   END_INPUT
};

static struct INPUT_INFO input_tndrcade[] =
{
   INP0( P1_LEFT, 0x0b000, 0x01 ),
   INP0( P1_RIGHT, 0x0b000, 0x02 ),
   INP0( P1_UP, 0x0b000, 0x04 ),
   INP0( P1_DOWN, 0x0b000, 0x08 ),
   INP0( P1_B1, 0x0b000, 0x10 ),
   INP0( P1_B2, 0x0b000, 0x20 ),
   INP0( P1_B3, 0x000000, 0x40 ),
   INP0( P1_START, 0x0b000, 0x80 ),

   INP0( P2_LEFT, 0x0b001, 0x01 ),
   INP0( P2_RIGHT, 0x0b001, 0x02 ),
   INP0( P2_UP, 0x0b001, 0x04 ),
   INP0( P2_DOWN, 0x0b001, 0x08 ),
   INP0( P2_B1, 0x0b001, 0x10 ),
   INP0( P2_B2, 0x0b001, 0x20 ),
   INP0( P2_START, 0x0b001, 0x80 ),

  INP0( COIN1, 0x0b002, 0x01 ),
  INP0( COIN2, 0x0b002, 0x02 ),
   INP0( P1_START, 0x0b002, 0x4 ),
   INP0( P2_START, 0x0b002, 0x8 ),
  INP0( SERVICE, 0xb002, 0x10 ),
  INP0( TILT, 0xb002, 0x20 ),

   END_INPUT
};

static struct INPUT_INFO input_blandia[] =
{
   INP0( P1_LEFT, 0x02, 0x01 ),
   INP0( P1_RIGHT, 0x02, 0x02 ),
   INP0( P1_UP, 0x02, 0x04 ),
   INP0( P1_DOWN, 0x02, 0x08 ),
   INP0( P1_B1, 0x02, 0x10 ),
   INP0( P1_B2, 0x02, 0x20 ),
   INP0( P1_B3, 0x02, 0x40 ),
   INP0( P1_START, 0x02, 0x80 ),

   INP0( P2_LEFT, 0x04, 0x01 ),
   INP0( P2_RIGHT, 0x04, 0x02 ),
   INP0( P2_UP, 0x04, 0x04 ),
   INP0( P2_DOWN, 0x04, 0x08 ),
   INP0( P2_B1, 0x04, 0x10 ),
   INP0( P2_B2, 0x04, 0x20 ),
   INP0( P2_B3, 0x04, 0x40 ),
   INP0( P2_START, 0x04, 0x80 ),

  INP0( COIN1, 0x06, 0x01 ),
  INP0( COIN2, 0x06, 0x02 ),
  INP0( SERVICE, 0x06, 0x04 ),
  INP0( TILT, 0x06, 0x08 ),

   // daioh specific buttons
   INP0( P1_B4, 0x08, 0x1 ),
   INP0( P1_B5, 0x08, 0x2 ),
   INP0( P1_B6, 0x08, 0x4 ),
   INP0( P2_B4, 0x08, 0x8 ),
   INP0( P2_B5, 0x08, 0x10 ),
   INP0( P2_B6, 0x08, 0x20 ),

   INP0( P3_LEFT, 0x0a, 0x01 ),
   INP0( P3_RIGHT, 0x0a, 0x02 ),
   INP0( P3_UP, 0x0a, 0x04 ),
   INP0( P3_DOWN, 0x0a, 0x08 ),
   INP0( P3_B1, 0x0a, 0x10 ),
   INP0( P3_B2, 0x0a, 0x20 ),
   INP0( P3_B3, 0x0a, 0x40 ),
   INP0( P3_START, 0x0a, 0x80 ),

   INP0( P4_LEFT, 0x0c, 0x01 ),
   INP0( P4_RIGHT, 0x0c, 0x02 ),
   INP0( P4_UP, 0x0c, 0x04 ),
   INP0( P4_DOWN, 0x0c, 0x08 ),
   INP0( P4_B1, 0x0c, 0x10 ),
   INP0( P4_B2, 0x0c, 0x20 ),
   INP0( P4_B3, 0x0c, 0x40 ),
   INP0( P4_START, 0x0c, 0x80 ),

   END_INPUT
};

static struct INPUT_INFO input_usclssic[] =
{
  // the inputs are weird because the first 2 words are used by the trackball
   INP1( P1_B1, 0x03, 0x20 ),
   INP1( P1_START, 0x03, 0x40 ),

  INP1( COIN2, 4, 0x10 ),
  INP1( COIN1, 4, 0x20 ),
  INP1( SERVICE, 4, 0x40 ),
  INP1( TILT, 4, 0x80 ),

   // for those who do not want to use the mouse
   INP0( P1_LEFT, 0x08, 0x01 ),
   INP0( P1_RIGHT, 0x08, 0x02 ),
   INP0( P1_UP, 0x08, 0x04 ),
   INP0( P1_DOWN, 0x08, 0x08 ),

   END_INPUT
};


static UINT8 *GFX_SPR,latch1;
static UINT16 latch2; // need 16 bit because direct access (ReadBW)
static UINT8 *GFX_SPR_SOLID;
static UINT8 *RAM_BG0,*RAM_BG1,*RAM_CTRL,*RAM_CTRL2,*RAM_SPR,*RAM_SPR2;
static int layer_id_data[4],buffered_sprites,fixed_layers,double_mapping;

static struct x_offset *global_offsets;

struct x_offset
{
	/* 2 values, for normal and flipped */
	char *gamename;
	int sprite_offs[2];
	int tilemap_offs[2];
};

/* note that drgnunit, stg and qzkklogy run on the same board, yet they need different alignment */
static struct x_offset game_offsets[] =
{
	/* only sprites */
	{ "tndrcade", { -1,  0 } },				/* correct (wall at beginning of game) */
	{ "tndrcadj", { -1,  0 } },				/* correct (wall at beginning of game) */
	{ "wits",     {  0,  0 } },				/* unknown */
	{ "thunderl", {  0,  0 } },				/* unknown */
	{ "blockcar", {  0,  0 } },				/* unknown */
	{ "umanclub", {  0,  0 } },				/* unknown */
	{ "atehate",  {  0,  0 } },				/* correct (test grid) */
	{ "kiwame",   {  0,-16 } },				/* correct (test grid) */
	{ "krzybowl", {  0,  0 } },				/* correct (test grid) */

	/* 1 layer */
	{ "twineagl", {  0,  0 }, {  0, -3 } },	/* unknown */
	{ "downtown", {  1,  0 }, { -1,  0 } },	/* sprites correct (test grid), tilemap unknown but at least -1 non-flipped to fix glitches later in the game */
	{ "usclssic", {  1,  2 }, {  0, -1 } },	/* correct (test grid and bg) */
	{ "calibr50", { -1,  2 }, { -3, -2 } },	/* correct (test grid and roof in animation at beginning of game) */
	{ "arbalest", {  0,  1 }, { -2, -1 } },	/* correct (test grid and landing pad at beginning of game) */
	{ "metafox",  {  0,  0 }, { 0,-3 } },	/* sprites unknown, tilemap correct (test grid) */
	// for metafox, when the test grid is aligned then the ship (layer 0) and the
	// sprites above it are misaligned at the end of level 1. Maybe there is some other
	// register for alignement somewhere ???

	{ "drgnunit", {  2,  2 }, { -2, -2 } },	/* correct (test grid and I/O test) */
	{ "stg",      {  0,  0 }, { -2, -2 } },	/* sprites correct? (panel), tilemap correct (test grid) */
	{ "qzkklogy", {  1,  1 }, { -1, -1 } },	/* correct (timer, test grid) */
	{ "qzkklgy2", {  0,  0 }, { -1, -3 } },	/* sprites unknown, tilemaps correct (test grid) */

	/* 2 layers */
	{ "rezon",    {  0,  0 }, { -2, -2 } },	/* correct (test grid) */
	{ "blandia",  {  0,  8 }, { -2,  6 } },	/* correct (test grid, startup bg) */
	{ "blandiap", {  0,  8 }, { -2,  6 } },	/* correct (test grid, startup bg) */
	{ "zingzip",  {  0,  0 }, { -1, -2 } },	/* sprites unknown, tilemaps correct (test grid) */
	{ "eightfrc", {  3,  4 }, {  0,  0 } },	/* unknown */
	{ "daioh",    {  1,  1 }, { -1, -1 } },	/* correct? (launch window and test grid are right, but planet is wrong) */
	{ "msgundam", {  0,  0 }, { -2, -2 } },	/* correct (test grid, banpresto logo) */
	{ "msgunda1", {  0,  0 }, { -2, -2 } },	/* correct (test grid, banpresto logo) */
	{ "oisipuzl", {  0,  0 }, { -1, -1 } },	/* correct (test mode) flip screen not supported? */
	{ "triplfun", {  0,  0 }, { -1, -1 } },	/* correct (test mode) flip screen not supported? */
	{ "wrofaero", {  0,  0 }, {  0,  0 } },	/* unknown */
	{ "jjsquawk", {  1,  1 }, { -1, -1 } },	/* correct (test mode) */
	{ "kamenrid", {  0,  0 }, { -2, -2 } },	/* correct (map, banpresto logo) */
	{ "extdwnhl", {  0,  0 }, { -2, -2 } },	/* correct (test grid, background images) */
	{ "sokonuke", {  0,  0 }, { -2, -2 } },	/* correct (game selection, test grid) */
	{ "gundhara", {  0,  0 }, {  0,  0 } },	/* unknown, flip screen not supported? */
	{ "zombraid", {  0,  0 }, { -2, -2 } },	/* correct for normal, flip screen not working yet */
	{ "madshark", {  0,  0 }, {  0,  0 } },	/* unknown (wrong when flipped, but along y) */
	{ "utoukond", {  0,  0 }, { -2,  0 } }, /* unknown (wrong when flipped, but along y) */
	{ NULL }
};

static int sprites_mask,limitx,limity,visuy;
static UINT16 twineagl_tilebank[4],tile_hack;

static void find_offsets(void)
{
  global_offsets = game_offsets;
  while (global_offsets->gamename && !is_current_game(global_offsets->gamename))
		global_offsets++;
}

static int global_flip;
static UINT16 seta_vregs[7];
static int seta_samples_bank;
static int seta_tiles_offset;
static int draw_crosshair,bank_bg0;
static UINT16 ctrl,ctrl2,id_sprites,min_y;

static void seta_vregs_w(UINT32 offset, UINT16 data) {
  int new_bank;
  offset &= 6;
  offset >>= 1;

  seta_vregs[offset] = data;
  switch (offset) {
  case 2/2:
    /* It's because of this offset that I need a handler here : the sound bankswitch.
       It must be executed immediately ! (not sure, but it's better this way) */

    /*
    fedc ba98 76-- ----
    ---- ---- --54 3---		Samples Bank (in blandia, eightfrc, zombraid)
    ---- ---- ---- -2--
    ---- ---- ---- --1-		Sprites Above Frontmost Layer
    ---- ---- ---- ---0		Layer 0 Above Layer 1
    */

    new_bank = (data >> 3) & 0x7;

    if (new_bank != seta_samples_bank) {
      unsigned char *rom = load_region[REGION_SOUND1];
      int samples_len = get_region_size(REGION_SOUND1);
      int addr;
      seta_samples_bank = new_bank;

      if (samples_len == 0x1c0000 || samples_len == 0x240000) {	/* blandia, eightfrc */
	addr = 0x40000 * new_bank;
	if (new_bank >= 3)	addr += 0x40000;

	if ( (samples_len > 0x100000) && ((addr+0x40000) <= samples_len) )
	  memcpy(&rom[0xc0000],&rom[addr],0x40000);
#ifdef RAINE_DEBUG
	else
	  fprintf(stderr,"invalid sample bank\n");
#endif
      } else if (samples_len == 0x480000) {	/* zombraid */
	/* bank 1 is never explicitly selected, 0 is used in its place */
	if (new_bank == 0) new_bank = 1;
	addr = 0x80000 * new_bank;
	if (new_bank > 0) addr += 0x80000;
	memcpy(&rom[0x80000],&rom[addr],0x80000);
      }
    }
  }
}

static void msgundam_vregs_w(UINT32 offset, UINT16 data) {
  offset &= 6;
  if (offset == 4)
    offset = 2;
  else if (offset == 2)
    offset = 4;
  seta_vregs_w(offset,data);
}

static void draw_layer(UINT8 *RAM_CTRL, UINT8 *RAM_BG, UINT8 *GFX_BG_SOLID,
		       int max, int bank, UINT8 *GFX, int id) {
  // Draw "blandia's like" layers
  // The layers can be transparant
  // The mapping of the colours is chosen from fixed_layers

  if( check_layer_enabled(layer_id_data[id]) && GFX) {
    int zz,zzz,zzzz,x16,y16,x,y,ta;
    int dx = ReadWord(&RAM_CTRL[0]), dy = ReadWord(&RAM_CTRL[2]);
    UINT8 *map,*BG;
    dx += 0x10 - global_offsets->tilemap_offs[global_flip ? 1 : 0];
    // dy -= (256 - visuy)/2;
    if (global_flip)
      {
	dx = -dx - 512;
	dy = dy - visuy;
      }
    MAKE_SCROLL_1024x512_2_16(
			      dx,
			      (dy)
			      );

    if (RAM_CTRL[4] & 8) {// What mame calls bg1
      BG = RAM_BG + 0x2000;
    } else {
      BG = RAM_BG;
    }

    if (double_mapping) {
      if (id == 0)
	fixed_layers = 2; // 64 colors, banks of 16 colors
      else {
	fixed_layers = 0;
      }
    }

    if (fixed_layers == 1) {
      MAP_PALETTE_MULTI_MAPPED_NEW(
				 bank,
				 64,
				 map
				 );
      START_SCROLL_1024x512_2_16(16,16,384,visuy);

      ta = ReadWord(&BG[zz]);
      ta &= 0x3fff;
      if (ta < max && GFX_BG_SOLID[ta]) {
	if (GFX_BG_SOLID[ta] == 1) { // transp
	  switch(BG[zz+1]&0xC0){
	  case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
	  case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
	  }
	} else { // all solid
	  switch(BG[zz+1]&0xC0){
	  case 0x00: Draw16x16_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
	  case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
	  }
	}
      }
      END_SCROLL_1024x512_2_16();
    }  else if (fixed_layers == 2) {
      // These layers use the banks but banks of 64 colors...
      // The banks in between do not count -> take only 1 bank over 4.
      START_SCROLL_1024x512_2_16(16,16,384,visuy);

      ta = ReadWord(&BG[zz]);
      ta &= 0x3fff;
      if (ta < max && GFX_BG_SOLID[ta]) {
	MAP_PALETTE_MULTI_MAPPED_NEW((BG[0x1000+zz]&0x1c) | bank,64,map);

	if (GFX_BG_SOLID[ta] == 1) { // transp
	  switch(BG[zz+1]&0xC0){
	  case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
	  case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
	  }
	} else { // all solid
	  switch(BG[zz+1]&0xC0){
	  case 0x00: Draw16x16_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
	  case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
	  }
	}
      }
      END_SCROLL_1024x512_2_16();
    } else { // normal banks of 16 colors
      START_SCROLL_1024x512_2_16(16,16,384,visuy);

      ta = ReadWord(&BG[zz]);
      ta &= 0x3fff;
      if (ta < max && GFX_BG_SOLID[ta]) {
	MAP_PALETTE_MAPPED_NEW((BG[0x1000+zz]&0x1F) | bank,16,map);

	if (GFX_BG_SOLID[ta] == 1) { // transp
	  switch(BG[zz+1]&0xC0){
	  case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
	  case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
	  }
	} else { // all solid
	  switch(BG[zz+1]&0xC0){
	  case 0x00: Draw16x16_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
	  case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
	  case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
	  }
	}
      }
      END_SCROLL_1024x512_2_16();
    }
  }
}

#define max_y (0xf0)

static void draw_sprites() {
  UINT8 *map;
  int col, offs;
  int numcol	=	ctrl2 & 0x000f;

  /* Sprites Banking and/or Sprites Buffering */
  UINT16 *src = (UINT16*)(RAM_SPR2 + ( ((ctrl2 ^ (~ctrl2<<1)) & 0x40) ? 0x2000 : 0 ));
  if (!GFX_SPR) {
    GFX_SPR = load_region[REGION_GFX1];
    GFX_SPR_SOLID = gfx_solid[0];
    sprites_mask = max_sprites[0] - 1;
    GFX = load_region[REGION_GFX2];
  }

  if( check_layer_enabled(layer_id_data[id_sprites])) {
    // BG
    int upper	=	( RAM_SPR[ 0x604 ] ) + ( RAM_SPR[ 0x606 ] ) * 256;

    int col0;		/* Kludge, needed for krzybowl and kiwame */
    int xoffs = 0;
    int yoffs = (global_flip ? 1 : -1);
    switch (ctrl & 0x0f)
      {
      case 0x01:	col0	=	0x4;	break;	/* krzybowl */
      case 0x06:	col0	=	0x8;	break;	/* kiwame */
      default:	col0	=	0x0;
      }

    /* Number of columns to draw - the value 1 seems special, meaning:
       draw every column */
    if (numcol == 1)	numcol = 16;

    /* The first column is the frontmost, see twineagl test mode */
    // The map...
    for ( col = numcol - 1 ; col >= 0; col -- ) {
      int x	=	RAM_SPR[(col * 0x20 + 0x08 + 0x400)] ;
      int y	=	RAM_SPR[(col * 0x20 + 0x00 + 0x400)] ;

      /* draw this column */
      for ( offs = 0 ; offs < 0x40/2; offs += 2/2 ) {
	int	code	=	src[((col+col0)&0xf) * 0x40/2 + offs + 0x800/2];
	int	color	=	src[((col+col0)&0xf) * 0x40/2 + offs + 0xc00/2];

	// int	flipx	=	code & 0x8000;
	// int	flipy	=	code & 0x4000;
	int flip = (code >> 8) & 0xc0;

	int bank	=	(color & 0x0600) >> 9;

	int sx		=	  x + xoffs  + (offs & 1) * 16;
	int sy		=	-(y + yoffs) + (offs / 2) * 16;
	// int sy		=	(sprites_dy - y) + (offs / 2) * 16;

	if (upper & (1 << col))	sx += 256;

	if (global_flip)
	  {
	    sy = max_y - sy;
	    flip ^= 0xc0;
	  }

	color	=	( color >> (16-5));
	code	=	(code & 0x3fff) + (bank * 0x4000);
	//if (code > max_sprites)
	code &= sprites_mask;

	if (GFX_SPR_SOLID[code]) {

	  sx = (sx + 0x10) & 0x1ff;
	  sy = ((sy + 8) & 0xff) - min_y;

	  if (sx >=0 && sy >= 0 && sx < limitx && sy < limity) {
	    MAP_PALETTE_MAPPED_NEW(color,16,map);

	    if (GFX_SPR_SOLID[code] == 1) { // transp

	      switch(flip){
	      case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[(code<<8)], sx, sy, map);        break;
	      case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	      case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	      case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	      }
	    } else {
	      switch(flip){
	      case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	      }
	    }
	  }
	} // if solid
      } // offs
    } // next col
  }


  if( check_layer_enabled(layer_id_data[id_sprites+1])) {
    // sprites FG
    int offs;
    int xoffs = global_offsets->sprite_offs[global_flip ? 1 : 0];

    for ( offs = (0x400-2)/2 ; offs >= 0/2; offs -= 2/2 ) {
      int	code	=	src[offs + 0x000/2];
      int	x		=	src[offs + 0x400/2];

      int	y		=	RAM_SPR[offs*2 + 0x000];

      //int	flipx	=	code & 0x8000;
      //int	flipy	=	code & 0x4000;
      int flip = (code & 0xc000) >> 8;

      int bank	=	(x & 0x0600) >> 9;
      int color	=	x >> (16-5);

      if (global_flip)
	{
	  flip ^= 0xc0;
	} else
      y = max_y - y; // inversion

      code = (code & 0x3fff) + (bank * 0x4000);
      code &= sprites_mask;

      if (GFX_SPR_SOLID[code]) {
	int sx = ((x + xoffs + 0x10) & 0x1ff);
	int sy = ((y + 2 + 8) & 0x0ff) - min_y; // (y ) & 0xff;

	if (sx >0 && sy > 0 && sx < limitx && sy < limity) {
	  // printf("%d,%d,%x src %x (%x)\n",sx,sy,code,src-(UINT16*)RAM_SPR2,offs);

	  MAP_PALETTE_MAPPED_NEW(color ,16,map);

	  if (GFX_SPR_SOLID[code] == 1) { // transp

	    switch(flip){
	    case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[(code<<8)], sx, sy, map);        break;
	    case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	    case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	    case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    }
	  } else {
	    switch(flip){
	    case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	    case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    }
	  }
	}
      } // if solid
    }
  }
}

static void draw_usclssic_sprites(int id)
{
  UINT8 *map;

  /* Sprites Banking and/or Sprites Buffering */
  UINT16 *src = (UINT16*)(RAM_SPR2 + ( ((ctrl2 ^ (~ctrl2<<1)) & 0x40) ? 0x2000 : 0 ));


  if( check_layer_enabled(layer_id_data[id+1])) {
    // sprites FG
    int offs;
    int xoffs = global_offsets->sprite_offs[global_flip ? 1 : 0];

    for ( offs = (0x400-2)/2 ; offs >= 0/2; offs -= 2/2 ) {
      int	code	=	src[offs + 0x000/2];
      int	x		=	src[offs + 0x400/2];

      int	y		=	RAM_SPR[offs*2 + 0x000];

      //int	flipx	=	code & 0x8000;
      //int	flipy	=	code & 0x4000;
      int flip = (code & 0xc000) >> 8;

      int bank	=	(x & 0x0600) >> 9;
      int color	=	x >> (16-5);

      if (global_flip)
      {
	flip ^= 0xc0;
      } else
	y = max_y - y; // inversion

      code = (code & 0x3fff) + (bank * 0x4000);
      code &= sprites_mask;
      if (code > max_sprites[0])
	continue;

      if (GFX_SPR_SOLID[code]) {

	int sx = ((x + xoffs + 0x10) & 0x1ff);
	int sy = ((y + 2 + 8) & 0x0ff) - min_y; // (y ) & 0xff;

	if (sx >0 && sy > 0 && sx < limitx && sy < limity) {
	  // Each layer has some colors in ram, and some colors in the proms.
	  if (color < 0x10 ) {
	    MAP_PALETTE_MAPPED_NEW(color | 0x10,16,map);
	  } else {
	    MAP_PALETTE_MAPPED_NEW(color | 0x20,16,map);
	  }

	  if (GFX_SPR_SOLID[code] == 1) { // transp

	    switch(flip){
	    case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[(code<<8)], sx, sy, map);        break;
	    case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	    case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	    case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    }
	  } else {
	    switch(flip){
	    case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[(code<<8)], sx, sy, map);  break;
	    case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[(code<<8)], sx, sy, map); break;
	    }
	  }
	}
      } // if solid
    }
  }
}

static void draw_metafox(void)
{
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;
  UINT8 *BG;
  ClearPaletteMap();

  ctrl	=	ReadWord(&RAM_SPR[ 0x600 ]);
  global_flip = (ctrl & 0x40) >> 6;
  ctrl2 =	ReadWord(&RAM_SPR[ 0x602 ]);

  // BG0
  // ---
  /* This layer is specific to metafox and twineagl : solid and with a hack in twineagl
     for the water animation */
  if( check_layer_enabled(layer_id_data[0]) && GFX) {
    int dx = ReadWord(&RAM_CTRL[0]), dy = ReadWord(&RAM_CTRL[2]);
    dx += 0x10 - global_offsets->tilemap_offs[global_flip ? 1 : 0];
    // dy -= (256 - visuy)/2;
    if (global_flip)
      {
	dx = -dx - 512;
	dy = dy - visuy;
      }
    MAKE_SCROLL_1024x512_2_16(
			      dx,
			      dy
			      );

    if (RAM_CTRL[4] & 8) // What mame calls bg1
      BG = RAM_BG0 + 0x2000;
    else
      BG = RAM_BG0;

    START_SCROLL_1024x512_2_16(16,16,384,visuy);

    ta = ReadWord(&BG[zz]);

    // From mame... !!!
    if (tile_hack) {
      if ((ta & 0x3e00) == 0x3e00) {
	ta = (ta & 0xc07f) | ((twineagl_tilebank[(ta & 0x0180) >> 7] >> 1) << 7);
      }
    }
    ta &= 0x3fff;

    if (ta < max_sprites[1]) {
      MAP_PALETTE_MAPPED_NEW(
			     (BG[0x1000+zz]&0x1F),
			     16,
			     map
			     );

      switch(BG[zz+1]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
      }
    }
    END_SCROLL_1024x512_2_16();
  } else
    clear_game_screen(0);

  draw_sprites();
}

static void draw_usclssic()
{
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;
  UINT8 *BG;
  ClearPaletteMap();

  ctrl	=	ReadWord(&RAM_SPR[ 0x600 ]);
  global_flip = (ctrl & 0x40) >> 6;
  ctrl2 =	ReadWord(&RAM_SPR[ 0x602 ]);

  if (!GFX_SPR) {
    GFX_SPR = load_region[REGION_GFX1];
    GFX_SPR_SOLID = gfx_solid[0];
    sprites_mask = max_sprites[0] - 1;
    GFX = load_region[REGION_GFX2];
  }

  // BG0
  // ---
  /* This layer is specific to metafox and twineagl : solid and with a hack in twineagl
     for the water animation */
  if( check_layer_enabled(layer_id_data[0]) && GFX) {
    int dx = ReadWord(&RAM_CTRL[0]), dy = ReadWord(&RAM_CTRL[2]);
    dx += 0x10 - global_offsets->tilemap_offs[global_flip ? 1 : 0];
    // dy -= (256 - visuy)/2;
    if (global_flip)
      {
	dx = -dx - 512;
	dy = dy - visuy;
      }
    MAKE_SCROLL_1024x512_2_16(
			      dx,
			      dy
			      );

    if (RAM_CTRL[4] & 8) // What mame calls bg1
      BG = RAM_BG0 + 0x2000;
    else
      BG = RAM_BG0;

    // special color mapping (usclssic)
    START_SCROLL_1024x512_2_16(16,16,384,visuy);

    ta = (ReadWord(&BG[zz]) & 0x3fff) + seta_tiles_offset;
    if (ta < max_sprites[1]) {
      UINT8 col = BG[0x1000+zz] & 0x1c;
      if (col < 0x10) {
	// bank in ram
	MAP_PALETTE_MULTI_MAPPED_NEW(col,64,map);
      } else {
	// bank in prom
	MAP_PALETTE_MULTI_MAPPED_NEW(0x10+col,64,map);
      }


      switch(BG[zz+1]&0xC0){
      case 0x00: Draw16x16_Mapped_Rot(&GFX[(ta<<8)], x, y, map);        break;
      case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[(ta<<8)], x, y, map);  break;
      case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[(ta<<8)], x, y, map);  break;
      case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[(ta<<8)], x, y, map); break;
      }
    }
    END_SCROLL_1024x512_2_16();
  } else
    clear_game_screen(0);

  // usclssic is the only game using a special color mapping here
  draw_usclssic_sprites(1);
}

static int fixed_bg1;

static void draw_blandia() {
  UINT16 order = seta_vregs[1];
  UINT8 *map;

  ClearPaletteMap();

  if (gfx[2] && !fixed_bg1 && is_current_game("blandia")) {
    UINT8 *GFX1 = gfx[2];
    int n;
    // The bg1 layer seems broken : its pixels seem to map as if they had only 16 colors
    // instead of 64. So I fix them here to avoid difficulties with the colors.
    for (n=0; n< max_sprites[2]*256; n++) {
      GFX1[n] &= 15;
    }
    fixed_bg1 = 1;
  }

  MAP_PALETTE_MAPPED_NEW(
      0x40,
      16,
      map
   );

  clear_game_screen(ReadLong(&map[0]));

  ctrl	=	ReadWord(&RAM_SPR[ 0x600 ]);
  global_flip = (ctrl & 0x40) >> 6;
  ctrl2=	ReadWord(&RAM_SPR[ 0x602 ]);

  if (order & 1) { // swap layers ?
    draw_layer(RAM_CTRL2,RAM_BG1,gfx_solid[2],max_sprites[2],0x20,gfx[2],1);
    if (order & 2) { // sprites before ?
#ifdef USE_XSYSTEM
      render_seta_x1_68000();
#else
      draw_sprites();
#endif
      draw_layer(RAM_CTRL,RAM_BG0,gfx_solid[1],max_sprites[1],bank_bg0,gfx[1],0);
    } else {
      draw_layer(RAM_CTRL,RAM_BG0,gfx_solid[1],max_sprites[1],bank_bg0,gfx[1],0);
#ifdef USE_XSYSTEM
      render_seta_x1_68000();
#else
      draw_sprites();
#endif
    }
  } else {
    draw_layer(RAM_CTRL,RAM_BG0,gfx_solid[1],max_sprites[1],bank_bg0,gfx[1],0);
    if (order & 2) { // sprites before ?
#ifdef USE_XSYSTEM
      render_seta_x1_68000();
#else
      draw_sprites();
#endif
      draw_layer(RAM_CTRL2,RAM_BG1,gfx_solid[2],max_sprites[2],0x20,gfx[2],1);
    } else {
      draw_layer(RAM_CTRL2,RAM_BG1,gfx_solid[2],max_sprites[2],0x20,gfx[2],1);
#ifdef USE_XSYSTEM
      render_seta_x1_68000();
#else
      draw_sprites();
#endif
    }
  }

  // handle buffered sprites
  if (buffered_sprites) {
    if (~ctrl2 & 0x20) {
      if (ctrl2 & 0x40)
	memcpy(&RAM_SPR2[0x0000],&RAM_SPR2[0x2000],0x2000);
      else
	memcpy(&RAM_SPR2[0x2000],&RAM_SPR2[0x0000],0x2000);
    }
  }

  if (draw_crosshair) {
    int p1_x = ReadWord(&RAM[0x1a000+0xC4AA]);
    int p1_y = ReadWord(&RAM[0x1a000+0xC4AC]);
    int p2_x = ReadWord(&RAM[0x1a000+0xC4AE]);
    int p2_y = ReadWord(&RAM[0x1a000+0xC4B0]);
    if (p1_x || p1_y)
      disp_gun(0,p1_x+16-8,0x08+0xff - p1_y+8+1-8);
    if (p2_x || p2_y)
      disp_gun(1,p2_x+16-8,0x08+0xff - p2_y+8+1-8);
  }
}

static GfxLayout layout_planes_2roms =
{
	16,16,
	RGN_FRAC(1,2),
	4,
	{RGN_FRAC(1,2)+8, RGN_FRAC(1,2)+0, 8, 0},
	{0,1,2,3,4,5,6,7, 128,129,130,131,132,133,134,135},
	{0*16,1*16,2*16,3*16,4*16,5*16,6*16,7*16,
	 16*16,17*16,18*16,19*16,20*16,21*16,22*16,23*16 },
	16*16*2
};

static GfxLayout layout_planes_2roms_split =
{
	16,16,
	RGN_FRAC(1,2),
	4,
	{0,4, RGN_FRAC(1,2)+0,RGN_FRAC(1,2)+4},
	{128+64,128+65,128+66,128+67, 128+0,128+1,128+2,128+3,
	 8*8+0,8*8+1,8*8+2,8*8+3, 0,1,2,3},
	{0*8,1*8,2*8,3*8,4*8,5*8,6*8,7*8,
	 32*8,33*8,34*8,35*8,36*8,37*8,38*8,39*8},
	16*16*2
};

static struct GFX_LIST downtown_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_planes_2roms }, // 32 color banks
	{ REGION_GFX2, &layout_planes_2roms_split }, // 32 color banks
	{ 0, NULL }
};

static GfxLayout layout_packed_6bits_3roms =
{
	16,16,
	RGN_FRAC(1,3),
	6,
	{RGN_FRAC(0,3)+0,RGN_FRAC(0,3)+4,  RGN_FRAC(1,3)+0,RGN_FRAC(1,3)+4,  RGN_FRAC(2,3)+0,RGN_FRAC(2,3)+4},
	{128+64,128+65,128+66,128+67, 128+0,128+1,128+2,128+3,
	 64,65,66,67, 0,1,2,3},
	{0*8,1*8,2*8,3*8,4*8,5*8,6*8,7*8,
	 32*8,33*8,34*8,35*8,36*8,37*8,38*8,39*8},
	16*16*2
};

static GfxLayout layout_packed =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{2*4,3*4,0*4,1*4},
	{256+128,256+129,256+130,256+131, 256+0,256+1,256+2,256+3,
	 128,129,130,131, 0,1,2,3},
	{0*16,1*16,2*16,3*16,4*16,5*16,6*16,7*16,
	 32*16,33*16,34*16,35*16,36*16,37*16,38*16,39*16},
	16*16*4
};

static GfxLayout layout_packed_6bits_2roms =
{
	16,16,
	RGN_FRAC(1,2),
	6,
	{RGN_FRAC(1,2)+0*4, RGN_FRAC(1,2)+1*4, 2*4,3*4,0*4,1*4},
	{256+128,256+129,256+130,256+131, 256+0,256+1,256+2,256+3,
	 128,129,130,131, 0,1,2,3},
	{0*16,1*16,2*16,3*16,4*16,5*16,6*16,7*16,
	 32*16,33*16,34*16,35*16,36*16,37*16,38*16,39*16},
	16*16*4
};

static GfxLayout wiggie_layout =
{
	16,16,
	RGN_FRAC(1,4),
	4,
	{ RGN_FRAC(0,4),RGN_FRAC(1,4),RGN_FRAC(2,4),RGN_FRAC(3,4) },
	{ 0,1,2,3,4,5,6,7,
	 64,65,66,67,68,69,70,71 },
	{ 0*8, 16*8, 4*8, 20*8,
	  2*8, 18*8, 6*8, 22*8,
	  1*8, 17*8, 5*8, 21*8,
	  3*8, 19*8, 7*8, 23*8,	},
	16*16
};

static struct GFX_LIST wiggie_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &wiggie_layout },
	{ 0, NULL }
};

static struct GFX_LIST zingzip_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_planes_2roms }, // 32 color banks
	{ REGION_GFX2, &layout_packed_6bits_2roms }, // 32 color banks
	{ REGION_GFX3, &layout_packed }, // 32 color banks
	{ 0, NULL }
};

static struct GFX_LIST blandia_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_planes_2roms }, //           32 color banks
	{ REGION_GFX2, &layout_packed_6bits_3roms }, // 32 color banks (decoded later)
	{ REGION_GFX3, &layout_packed_6bits_3roms }, //       32 color banks
	{ 0, NULL }
};

static struct GFX_LIST msgundam_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_planes_2roms }, // 32 color banks
	{ REGION_GFX2, &layout_packed }, // 32 color banks
	{ REGION_GFX3, &layout_packed }, // 32 color banks
	{ 0, NULL }
};

static struct GFX_LIST jjsquawk_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_planes_2roms }, //             32 color banks
	{ REGION_GFX2, &layout_packed_6bits_2roms }, // 32 color banks
	{ REGION_GFX3, &layout_packed_6bits_2roms }, // 32 color banks
	{ 0, NULL }
};

static struct GFX_LIST usclssic_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_planes_2roms }, // 32/2 color banks
	{ REGION_GFX2, &layout_packed_6bits_3roms }, // 32 color banks
	{ 0, NULL }
};





















static struct ROM_INFO rom_daioh[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "fg1-001",  0x104ae74a, "fg1-002",  0xe39a4e67),
  { "fg1-004", 0x100000, 0x9ab0533e, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "fg1-003", 0x100000, 0x1c9d51e2, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "fg1-005", 0x200000, 0xc25159b9, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "fg1-006", 0x200000, 0x2052c39a, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "fg1-007", 0x100000, 0x4a2fe9e0, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_neobattl[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "bp923001.u45",  0x0d0aeb73, "bp923002.u46",  0x9731fbbc),
  { "bp923003.u15", 0x80000, 0x91ca98a1, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "bp923004.u9", 0x80000, 0x15c678e3, REGION_GFX1, 0x80000, LOAD_NORMAL },
  { "bp923005.u4", 0x100000, 0x7c0e37be, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_msgundam[] =
{
  { "fa003002.u25", 0x080000, 0x1cc72d4c, REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "fa001001.u20", 0x100000, 0xfca139d0, REGION_ROM1, 0x100000, LOAD_SWAP_16 },
  { "fa001008.u21", 0x200000, 0xe7accf48, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "fa001007.u22", 0x200000, 0x793198a6, REGION_GFX1, 0x200000, LOAD_NORMAL },
  { "fa001006.u23", 0x100000, 0x3b60365c, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "fa001005.u24", 0x080000, 0x8cd7ff86, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "fa001004.u26", 0x100000, 0xb965f07c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_umanclub[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "uw001006.u48",  0x3dae1e9d, "uw001007.u49",  0x5c21e702),
  { "bp-u-002.u2", 0x080000, 0x936cbaaa, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bp-u-001.u1", 0x080000, 0x87813c48, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "uw003.u13", 0x100000, 0xe2f718eb, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_wiggie[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x10000,
            "wiggie.f19",  0x24b58f16, "wiggie.f21",  0x83ba6edb),
  { "wiggie.a5", 0x10000, 0x8078d77b, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "wiggie.d1", 0x40000, 0x27fbe12a, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "wiggie.k16", 0x20000, 0x4fb40b8a, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "wiggie.k18", 0x20000, 0xebc418e9, REGION_GFX1, 0x20000, LOAD_NORMAL },
  { "wiggie.k19", 0x20000, 0xc073501b, REGION_GFX1, 0x40000, LOAD_NORMAL },
  { "wiggie.k21", 0x20000, 0x22f6fa39, REGION_GFX1, 0x60000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_stg[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "att01003.u27",  0x7a640a93, "att01001.u9",  0x4fa88ad3),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x020000,
            "att01004.u33",  0xbbd45ca1, "att01002.u17",  0x2f8fd80c),
  { "att01006.u32", 0x080000, 0x6ad78ea2, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "att01005.u26", 0x080000, 0xa347ff00, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "att01008.u39", 0x080000, 0x20c47457, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "att01007.u42", 0x080000, 0xac975544, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "att01009.u47", 0x080000, 0x4276b58d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "att01010.u55", 0x080000, 0xfffb2f53, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_drgnunit[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "prg-e.bin",  0x728447df, "prg-o.bin",  0xb2f58ecf),
  LOAD8_16(  REGION_GFX1,  0x000000,  0x020000,
            "obj-2.bin",  0xd7f6ab5a, "obj-1.bin",  0x53a95b13),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x020000,
            "obj-6.bin",  0x80b801f7, "obj-5.bin",  0x6b87bc20),
  LOAD8_16(  REGION_GFX1,  0x080000,  0x020000,
            "obj-4.bin",  0x60d17771, "obj-3.bin",  0x0bccd4d5),
  LOAD8_16(  REGION_GFX1,  0x0c0000,  0x020000,
            "obj-8.bin",  0x826c1543, "obj-7.bin",  0xcbaa7f6a),
  { "scr-1o.bin", 0x020000, 0x671525db, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "scr-2o.bin", 0x020000, 0x2a3f2ed8, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "scr-3o.bin", 0x020000, 0x4d33a92d, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "scr-4o.bin", 0x020000, 0x79a0aa61, REGION_GFX2, 0x060000, LOAD_NORMAL },
  { "scr-1e.bin", 0x020000, 0xdc9cd8c9, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "scr-2e.bin", 0x020000, 0xb6126b41, REGION_GFX2, 0x0a0000, LOAD_NORMAL },
  { "scr-3e.bin", 0x020000, 0x1592b8c2, REGION_GFX2, 0x0c0000, LOAD_NORMAL },
  { "scr-4e.bin", 0x020000, 0x8201681c, REGION_GFX2, 0x0e0000, LOAD_NORMAL },
  { "snd-1.bin", 0x020000, 0x8f47bd0d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "snd-2.bin", 0x020000, 0x65c40ef5, REGION_SMP1, 0x020000, LOAD_NORMAL },
  { "snd-3.bin", 0x020000, 0x71fbd54e, REGION_SMP1, 0x040000, LOAD_NORMAL },
  { "snd-4.bin", 0x020000, 0xac50133f, REGION_SMP1, 0x060000, LOAD_NORMAL },
  { "snd-5.bin", 0x020000, 0x70652f2c, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { "snd-6.bin", 0x020000, 0x10a1039d, REGION_SMP1, 0x0a0000, LOAD_NORMAL },
  { "snd-7.bin", 0x020000, 0xdecbc8b0, REGION_SMP1, 0x0c0000, LOAD_NORMAL },
  { "snd-8.bin", 0x020000, 0x3ac51bee, REGION_SMP1, 0x0e0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_arbalest[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "uk001.03",  0xee878a2c, "uk001.04",  0x902bb4e3),
  { "uk001.05", 0x002000, 0x0339fc53, REGION_ROM2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x040000,
            "uk001.06",  0x11c75746, "uk001.07",  0x01b166c7),
  LOAD8_16(  REGION_GFX1,  0x080000,  0x040000,
            "uk001.08",  0x78d60ba3, "uk001.09",  0xb4748ae0),
  { "uk001.10", 0x080000, 0xc1e2f823, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "uk001.11", 0x080000, 0x09dfe56a, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "uk001.12", 0x080000, 0x818a4085, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "uk001.13", 0x080000, 0x771fa164, REGION_GFX2, 0x180000, LOAD_NORMAL },
  { "uk001.15", 0x080000, 0xce9df5dd, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "uk001.14", 0x080000, 0x016b844a, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_tndrcade[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "ua0-4.1l",  0x73bd63eb, "ua0-2.1h",  0xe96194b1),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x020000,
            "ua0-3.1k",  0x0a7b1c41, "ua0-1.1g",  0xfa906626),
  { "ua10-5.8m", 0x020000, 0x8eff6122, REGION_ROM2, 0x000000, LOAD_NORMAL },
  { "ua0-10", 0x040000, 0xaa7b6757, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "ua0-11", 0x040000, 0x11eaf931, REGION_GFX1, 0x040000, LOAD_NORMAL },
  { "ua0-12", 0x040000, 0x00b5381c, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "ua0-13", 0x040000, 0x8f9a0ed3, REGION_GFX1, 0x0c0000, LOAD_NORMAL },
  { "ua0-6", 0x040000, 0x14ecc7bb, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "ua0-7", 0x040000, 0xff1a4e68, REGION_GFX1, 0x140000, LOAD_NORMAL },
  { "ua0-8", 0x040000, 0x936e1884, REGION_GFX1, 0x180000, LOAD_NORMAL },
  { "ua0-9", 0x040000, 0xe812371c, REGION_GFX1, 0x1c0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_metafox[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "p1003161",  0x4fd6e6a1 , "p1004162",  0xb6356c9a ),
  LOAD8_16(  REGION_ROM1,  0x080000,  0x010000,
            "up001002",  0xce91c987 , "up001001",  0x0db7a505 ),
  { "up001005", 0x002000, 0x2ac5e3e3 , REGION_ROM2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x040000,
            "p1006163",  0x80f69c7c , "p1007164",  0xd137e1a3 ),
  LOAD8_16(  REGION_GFX1,  0x080000,  0x040000,
            "p1008165",  0x57494f2b , "p1009166",  0x8344afd2 ),
  { "up001010", 0x080000, 0xbfbab472 , REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "up001011", 0x080000, 0x26cea381 , REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "up001012", 0x080000, 0xfed2c5f9 , REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "up001013", 0x080000, 0xadabf9ea , REGION_GFX2, 0x180000, LOAD_NORMAL },
  { "up001015", 0x080000, 0x2e20e39f , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "up001014", 0x080000, 0xfca6315e , REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_downtown[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "ud2001.000",  0xf1965260, "ud2001.003",  0xe7d5fa5f),
  LOAD8_16(  REGION_ROM1,  0x080000,  0x010000,
            "ud2000.002",  0xa300e3ac, "ud2000.001",  0xd2918094),
  { "ud2002.004", 0x040000, 0xbbd538b1, REGION_ROM2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x080000,
            "ud2005.t01",  0x77e6d249, "ud2006.t02",  0x6e381bf2),
  LOAD8_16(  REGION_GFX1,  0x100000,  0x080000,
            "ud2007.t03",  0x737b4971, "ud2008.t04",  0x99b9d757),
  { "ud2009.t05", 0x080000, 0xaee6c581, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "ud2010.t06", 0x080000, 0x3d399d54, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "ud2011.t07", 0x080000, 0x9c9ff69f, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_thunderl[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x008000,
            "m4",  0x1e6b9462, "m5",  0x7e82793e),
  LOAD8_16(  REGION_GFX1,  0x000000,  0x020000,
            "t17",  0x599a632a, "t16",  0x3aeef91c),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x020000,
            "t15",  0xb97a7b56, "t14",  0x79c707be),
  { "r28", 0x080000, 0xa043615d, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "r27", 0x080000, 0xcb8425a3, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_wits[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x008000,
            "un001001.u1",  0x416c567e, "un001002.u4",  0x497a3fa6),
  LOAD8_16(  REGION_GFX1,  0x000000,  0x020000,
            "un001008.7l",  0x1d5d0b2b, "un001007.5l",  0x9e1e6d51),
  LOAD8_16(  REGION_GFX1,  0x040000,  0x020000,
            "un001006.4l",  0x98a980d4, "un001005.2l",  0x6f2ce3c0),
  { "un001004.12a", 0x020000, 0xa15ff938, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "un001003.10a", 0x020000, 0x3f4b9e55, REGION_SMP1, 0x020000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_twineagl[] =
{
  { "ua2-1", 0x080000, 0x5c3fe531, REGION_ROM1, 0x000000, LOAD_NORMAL },
  { "ua2-2", 0x002000, 0x783ca84e, REGION_ROM2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x040000,
            "ua2-4",  0x8b7532d6, "ua2-3",  0x1124417a),
  LOAD8_16(  REGION_GFX1,  0x080000,  0x040000,
            "ua2-6",  0x99d8dbba, "ua2-5",  0x6e450d28),
  { "ua2-8", 0x080000, 0x7d3a8d73, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "ua2-10", 0x080000, 0x5bbe1f56, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "ua2-7", 0x080000, 0xfce56907, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "ua2-9", 0x080000, 0xa451eae9, REGION_GFX2, 0x180000, LOAD_NORMAL },
  { "ua2-11", 0x080000, 0x624e6057, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "ua2-12", 0x080000, 0x3068ff64, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_blandia[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "ux001001.003",  0x2376a1f3, "ux001002.004",  0xb915e172),
  { "ux001003.202", 0x100000, 0x98052c63, REGION_ROM1, 0x100000, LOAD_SWAP_16 },
  { "ux001005.200", 0x100000, 0xbea0c4a5, REGION_GFX1, 0x300000, LOAD_NORMAL },
  { "ux001007.201", 0x100000, 0x4440fdd1, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "ux001006.063", 0x100000, 0xabc01cf7, REGION_GFX1, 0x200000, LOAD_NORMAL },
  { "ux001008.064", 0x100000, 0x413647b6, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "ux001009.065", 0x080000, 0xbc6f6aea, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "ux001010.066", 0x080000, 0xbd7f7614, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "ux001011.067", 0x080000, 0x5efe0397, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "ux001012.068", 0x080000, 0xf29959f6, REGION_GFX3, 0x040000, LOAD_NORMAL },
	/* The c0000-fffff region is bankswitched */
	/* skip c0000-fffff (banked region) */
  { "ux001013.069", 0x100000, 0x5cd273cd, REGION_SMP1, 0, LOAD_NORMAL },
  { "ux001014.070", 0x080000, 0x86b49b4e, REGION_SMP1, 0x140000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_eightfrc[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "uy2-u4.u3",  0xf1f249c5, "uy2-u3.u4",  0x6f2d8618),
  { "u64.bin", 0x080000, 0xf561ff2e, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "u63.bin", 0x080000, 0x4c3f8366, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "u66.bin", 0x100000, 0x6fad2b7f, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "u68.bin", 0x100000, 0xc17aad22, REGION_GFX3, 0x000000, LOAD_NORMAL },
	/* skip c0000-fffff (banked region) */
  { "u70.bin", 0x100000, 0xdfdb67a3, REGION_SMP1, 0, LOAD_NORMAL },
  { "u69.bin", 0x100000, 0x82ec08f1, REGION_SMP1, 0x140000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gundhara[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "bpgh-003.u3",  0x14e9970a, "bpgh-004.u4",  0x96dfc658),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x080000,
            "bpgh-002.103",  0x312f58e2, "bpgh-001.102",  0x8d23a23c),
  { "bpgh-008.u64", 0x200000, 0x7ed9d272, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bpgh-006.201", 0x200000, 0x5a81411d, REGION_GFX1, 0x200000, LOAD_NORMAL },
  { "bpgh-007.u63", 0x200000, 0xaa49ce7b, REGION_GFX1, 0x400000, LOAD_NORMAL },
  { "bpgh-005.200", 0x200000, 0x74138266, REGION_GFX1, 0x600000, LOAD_NORMAL },
  { "bpgh-010.u66", 0x100000, 0xb742f0b8, REGION_GFX2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  0x100000,  0x080000,
            "bpgh-009.u65",  0xb768e666, "bpgh-009.u65",  0xb768e666),
  { "bpgh-012.u68", 0x200000, 0xedfda595, REGION_GFX3, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX3,  0x200000,  0x100000,
            "bpgh-011.u67",  0x49aff270, "bpgh-011.u67",  0x49aff270),
  { "bpgh-013.u70", 0x100000, 0x0fa5d503, REGION_SMP1, 0, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_jjsquawk[] =
{
  LOAD8_16(  REGION_ROM1,  0,  0x80000,
            "jj-rom1.040",  0x7b9af960, "jj-rom2.040",  0x47dd71a3),
  // reserve 0x80000 bytes to move a part of the rom...
  { "jj-rom2.040", 0x80000, 0x47dd71a3, REGION_ROM1, 0x100000, LOAD_NORMAL },
  { "jj-rom9", 0x080000, 0x27441cd3, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "jj-rom10", 0x080000, 0xca2b42c4, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "jj-rom7", 0x080000, 0x62c45658, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "jj-rom8", 0x080000, 0x2690c57b, REGION_GFX1, 0x180000, LOAD_NORMAL },
  { "jj-rom11", 0x080000, 0x98b9f4b4, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "jj-rom12", 0x080000, 0xd4aa916c, REGION_GFX2, 0x080000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  0x100000,  0x080000,
            "jj-rom3.040",  0xa5a35caf, "jj-rom3.040",  0xa5a35caf),
  { "jj-rom14", 0x080000, 0x274bbb48, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "jj-rom13", 0x080000, 0x51e29871, REGION_GFX3, 0x080000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX3,  0x100000,  0x080000,
            "jj-rom4.040",  0xa235488e, "jj-rom4.040",  0xa235488e),
  { "jj-rom5.040", 0x080000, 0xd99f2879, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "jj-rom6.040", 0x080000, 0x9df1e478, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_rezon[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "us001001.u3",  0xab923052, "us001002.u4",  0x3dafa0d5),
	/* empty gap */
  LOAD8_16(  REGION_ROM1,  0x100000,  0x020000,
            "us001004.103",  0x54871c7c, "us001003.102",  0x1ac3d272),
  { "us001006.u64", 0x080000, 0xa4916e96, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "us001005.u63", 0x080000, 0xe6251ebc, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "us001007.u66", 0x080000, 0x3760b935, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "us001008.u68", 0x080000, 0x0ab73910, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "us001009.u70", 0x100000, 0x0d7d2e2b, REGION_SMP1, 0x000000, LOAD_SWAP_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_wrofaero[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "u3.bin",  0x9b896a97, "u4.bin",  0xdda84846),
  { "u64.bin", 0x080000, 0xf06ccd78, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "u63.bin", 0x080000, 0x2a602a1b, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "u66.bin", 0x080000, 0xc9fc6a0c, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "u68.bin", 0x080000, 0x25c0c483, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "u69.bin", 0x080000, 0x957ecd41, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "u70.bin", 0x080000, 0x8d756fdf, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_zombraid[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x080000,
            "fy001003.3",  0x0b34b8f7, "fy001004.4",  0x71bfeb1a),
  LOAD8_16(  REGION_ROM1,  0x100000,  0x080000,
            "fy001002.103",  0x313fd68f, "fy001001.102",  0xa0f61f13),
  { "fy001006.200", 0x200000, 0xe9ae99f7, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "fy001008.66", 0x200000, 0x73d7b0e1, REGION_GFX2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  0x200000,  0x100000,
            "fy001007.65",  0xb2fc2c81, "fy001007.65",  0xb2fc2c81),

  { "fy001010.68", 0x200000, 0x8b40ed7a, REGION_GFX3, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX3,  0x200000,  0x100000,
            "fy001009.67",  0x6bcca641, "fy001009.67",  0x6bcca641),

	/* skip 80000-fffff (banked region) */
  { "fy001012.b", 0x200000, 0xfd30e102, REGION_SMP1, 0, LOAD_NORMAL },
  { "fy001011.a", 0x200000, 0xe3c431de, REGION_SMP1, 0x280000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};










static struct ROM_INFO rom_usclssic[] = {
  LOAD8_16(  REGION_ROM1,  0x000000,  0x020000,
            "ue2001.u20",  0x18b41421, "ue2000.u14",  0x69454bc2),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x020000,
            "ue2002.u22",  0xa7bbe248, "ue2003.u30",  0x29601906),
  { "ue002u61.004", 0x040000, 0x476e9f60, REGION_ROM2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x080000,
            "ue001009.119",  0xdc065204, "ue001008.118",  0x5947d9b5),
  LOAD8_16(  REGION_GFX1,  0x100000,  0x080000,
            "ue001007.117",  0xb48a885c, "ue001006.116",  0xa6ab6ef4),

  { "ue001010.120", 0x080000, 0xdd683031, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "ue001011.121", 0x080000, 0x0e27bc49, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "ue001012.122", 0x080000, 0x961dfcdc, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "ue001013.123", 0x080000, 0x03e9eb79, REGION_GFX2, 0x180000, LOAD_NORMAL },

  { "ue001014.124", 0x080000, 0x9576ace7, REGION_GFX2, 0x200000, LOAD_NORMAL },
  { "ue001015.125", 0x080000, 0x631d6eb1, REGION_GFX2, 0x280000, LOAD_NORMAL },
  { "ue001016.126", 0x080000, 0xf44a8686, REGION_GFX2, 0x300000, LOAD_NORMAL },
  { "ue001017.127", 0x080000, 0x7f568258, REGION_GFX2, 0x380000, LOAD_NORMAL },

  { "ue001018.128", 0x080000, 0x4bd98f23, REGION_GFX2, 0x400000, LOAD_NORMAL },
  { "ue001019.129", 0x080000, 0x6d9f5a33, REGION_GFX2, 0x480000, LOAD_NORMAL },
  { "ue001020.130", 0x080000, 0xbc07403f, REGION_GFX2, 0x500000, LOAD_NORMAL },
  { "ue001021.131", 0x080000, 0x98c03efd, REGION_GFX2, 0x580000, LOAD_NORMAL },

  LOAD8_16(  REGION_PROMS,  0x000,  0x200,
            "ue1-023.prm",  0xa13192a4, "ue1-022.prm",  0x1a23129e),

  { "ue001005.132", 0x080000, 0xc5fea37c, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_calibr50[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "uh002001.u45",  0xeb92e7ed, "uh002004.u41",  0x5a0ed31e),
  LOAD8_16(  REGION_ROM1,  0x080000,  0x010000,
            "uh001003.9a",  0x0d30d09f, "uh001002.7a",  0x7aecc3f9),
  { "uh001005.u61", 0x040000, 0x4a54c085, REGION_ROM2, 0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x080000,
            "uh001006.ux2",  0xfff52f91, "uh001007.ux1",  0xb6c19f71),
  LOAD8_16(  REGION_GFX1,  0x100000,  0x080000,
            "uh001008.ux6",  0x7aae07ef, "uh001009.ux0",  0xf85da2c5),
  { "uh001010.u3x", 0x080000, 0xf986577a, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "uh001011.u50", 0x080000, 0x08620052, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "uh001013.u60", 0x080000, 0x09ec0df6, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "uh001012.u46", 0x080000, 0xbb996547, REGION_SMP1, 0x080000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};


static struct ROM_INFO rom_zingzip[] =
{
  LOAD8_16(  REGION_ROM1,  	0x000000,  0x040000,
            "uy001001.3",  0x1a1687ec, "uy001002.4",  0x62e3b0c4),
  { "uy001006.64", 0x080000, 0x46e4a7d8, REGION_GFX1, 		0x000000, LOAD_NORMAL },
  { "uy001005.63", 0x080000, 0x4aac128e, REGION_GFX1, 		0x080000, LOAD_NORMAL },
  { "uy001008.66", 0x100000, 0x1dff7c4b, REGION_GFX2, 		0x000000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX2,  	0x100000,  0x080000,
            "uy001007.65",  0xec5b3ab9, "uy001007.65",  0xec5b3ab9),
  { "uy001010.68", 0x100000, 0xbdbcdf03, REGION_GFX3, 		0x000000, LOAD_NORMAL },
  { "uy001011.70", 0x100000, 0xbd845f55, REGION_SMP1, 		0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/*

Comment left by Antiriad, let's leave it this way ;-) :

6502 Info
---------

- I really hate this chip

- 0xFFFA = [7117] NMI Vector
- 0xFFFC = [7000] PC Reset Vector
- 0xFFFE = [70E1] Interrupt Vector

Seta 6502 Info
--------------

- Due to some of the opcodes in the rom, it seems to be a 6510

E000-FFFF = ROM?
6000-7FFF = ROM MIRROR?

*/

UINT8 ReadROM(UINT16 offset)
{
   return M6502ROM[offset&0x7FFF];
}

static int old_bank;

static void sub_bankswitch(UINT16 adr, UINT8 data) {
  int bank = (data >> 4);
  if (bank != old_bank) {
    if (0x4000 * bank + 0x4000 <= get_region_size(REGION_ROM2)) {
      memcpy(M6502ROM + 0x8000, load_region[REGION_ROM2] + 0x4000*bank, 0x4000);
      old_bank = bank;
    }
  }
}

static struct x1_010_interface seta_sound_intf_8MHz =
{
	8000000,	/* clock */
	YM3012_VOL(250,MIXER_PAN_LEFT,250,MIXER_PAN_RIGHT),	/* volume */
	0x0000,		/* address */
};

static struct x1_010_interface seta_sound_intf_16MHz =
{
  16000000,	/* clock */
  YM3012_VOL(250,MIXER_PAN_LEFT,250,MIXER_PAN_RIGHT),	/* volume */
  0x0000,		/* address */
};

static struct SOUND_INFO sound_arbalest[] =
  {
   { SOUND_X1_010, &seta_sound_intf_16MHz },
   { 0,             NULL,                 },
  };

static struct SOUND_INFO sound_downtown[] =
  {
   { SOUND_X1_010, &seta_sound_intf_8MHz },
   { 0,             NULL,                 },
  };

static struct OKIM6295interface wiggie_okim6295_interface =
{
	1,						/* 1 chip */
	{ 1000000/132 },	/* 1Mhz / 132 (pin 7 = 5v)*/
	{ REGION_SOUND1 },		/* memory region */
	{ 255 }
};

static struct SOUND_INFO sound_wiggie[] =
  {
   { SOUND_M6295, &wiggie_okim6295_interface },
   { 0,             NULL,                 },
  };

static UINT8 dsw1_r(UINT32 offset)
{
	return input_buffer[7];
}

static UINT8 dsw2_r(UINT32 offset)
{
	return input_buffer[6];
}

static struct YM2203interface tndrcade_ym2203_interface =
{
	1,
	2000000,		/* ? */
	{ YM2203_VOL(100,100) },
	{ dsw1_r },		/* input A: DSW 1 */
	{ dsw2_r },		/* input B: DSW 2 */
	{ 0 },
	{ 0 },
	{ NULL }
};

static struct YM3812interface ym3812_interface =
{
	1,
	4000000,	/* ? */
	{ 250,250 },	/* mixing level */
	{ NULL },
};

static struct SOUND_INFO sound_tndrcade[] =
  {
   { SOUND_YM2203, &tndrcade_ym2203_interface },
   { SOUND_YM3812, &ym3812_interface },
   { 0,             NULL,                 },
  };

/*

 Shared RAM:

 The 65c02 sees a linear array of bytes that is mapped, for the 68000,
 to a linear array of words whose low order bytes hold the data
 (from mame)

*/

static UINT8 *sharedram;

static UINT16 sharedram_68000_r(UINT32 offset)
{
  offset &= 0xfff;
  return sharedram[offset>>1];
}

static void sharedram_68000_w(UINT32 offset, UINT16 data)
{
  offset &= 0xfff;
  sharedram[offset>>1] = data;
}

/*

 Sub CPU Control

*/

static void sub_ctrl_w(UINT32 offset, UINT16 data)
{
  static int old_data = 0;

  switch(offset & 6)
    {
    case 0:	/* bit 0: reset sub cpu? */
      if ( !(old_data&1) && (data&1) ) {
	m6502reset();
      }
      old_data = data;
      break;

    case 2:	/* ? */
      break;

    case 4:	/* not sure */
      M6502ROM[0x800] = latch1 = data & 0xff;
      break;

    case 6:	/* not sure */
      M6502ROM[0x801] = latch2 = data & 0xff;
      break;
    }

}

/* Protection? NVRAM is handled writing commands here */
static UINT8 downtown_protection[0x200];

static unsigned char downtown_word[] = _("WALTZ0");

static UINT16 downtown_protection_rb(UINT32 offset)
{
  int job = downtown_protection[0xf8];

  offset &= 0x1ff;

  switch (job)
    {
    case 0xa3:
      {
	if (offset >= 0x100 && offset <= 0x10b)	return downtown_word[(offset-0x100)/2];
	else
	  return 0;
      }
    default:
      return downtown_protection[offset];
    }
}

static struct DSW_DATA dsw_data_daioh_2[] =
{
  DSW_UNUSED( 0x0000, 0x0010),
  DSW_UNUSED( 0x0000, 0x0020),
  DSW_UNUSED( 0x0000, 0x0040),
  { _("Country") , 0x0080, 2 },
  { _("USA (6 buttons)") , 0x0080},
  { _("Japan (2 buttons)") , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_daioh_3[] =
{
  { MSG_COIN1, 0x0007, 8 },
  { MSG_4COIN_1PLAY, 0x0001},
  { MSG_3COIN_1PLAY, 0x0002},
  { MSG_2COIN_1PLAY, 0x0004},
  { MSG_1COIN_1PLAY, 0x0007},
  { MSG_2COIN_3PLAY, 0x0003},
  { MSG_1COIN_1PLAY, 0x0006},
  { MSG_1COIN_3PLAY, 0x0005},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x0038, 8 },
  { MSG_4COIN_1PLAY, 0x0008},
  { MSG_3COIN_1PLAY, 0x0010},
  { MSG_2COIN_1PLAY, 0x0020},
  { MSG_1COIN_1PLAY, 0x0038},
  { MSG_2COIN_3PLAY, 0x0018},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_1COIN_3PLAY, 0x0028},
  { MSG_FREE_PLAY, 0x0000},
  DSW_DEMO_SOUND( 0x0040, 0x0000),
  { _("Auto Shot") , 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_daioh_4[] =
{
  DSW_SCREEN( 0x1, 0x0),
  DSW_SERVICE( 0, 0x2),
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy") , 0x8},
  { _("Normal") , 0xc},
  { _("Hard") , 0x4},
  { _("Hardest") , 0x0},
  { MSG_LIVES, 0x30, 4 },
  { "1" , 0x0},
  { "2" , 0x10},
  { "3" , 0x30},
  { "5" , 0x20},
  { MSG_EXTRA_LIFE, 0xc0, 4 },
  { _("300k and every 800k") , 0x80},
  { _("500k and every 1000k") , 0xc0},
  { _("800k and 2000k only") , 0x40},
  { _("1000k only") , 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_daioh[] =
{
  { 0x6, 0xf0, dsw_data_daioh_2 },
  { 0x0, 0x7f, dsw_data_daioh_3 },
  { 0x1, 0xff, dsw_data_daioh_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_neobattl_3[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  DSW_DEMO_SOUND( 0x0002, 0x0000),
  { MSG_UNKNOWN, 0x0004, 2 },
  { MSG_OFF, 0x0004},
  { MSG_ON, 0x0000},
  { _("Stage Select") ,    0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { MSG_UNKNOWN, 0x0010, 2 },
  { MSG_OFF, 0x0010},
  { MSG_ON, 0x0000},
  { MSG_UNKNOWN, 0x0020, 2 },
  { MSG_OFF, 0x0020},
  { MSG_ON, 0x0000},
  { MSG_UNKNOWN, 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  DSW_SERVICE( 0, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_neobattl_4[] =
{
  { MSG_LIVES, 0x3, 4 },
  { "1" , 0x2},
  { "2" , 0x3},
  { "3" , 0x1},
  { "4" , 0x0},
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy")    , 0x8},
  { _("Normal")  , 0xc},
  { _("Hard")    , 0x4},
  { _("Hardest") , 0x0},
  { MSG_COINAGE, 0xf0, 16 },
  { MSG_6COIN_1PLAY, 0xa0},
  { MSG_5COIN_1PLAY, 0xb0},
  { MSG_4COIN_1PLAY, 0xc0},
  { MSG_3COIN_1PLAY, 0xd0},
  { MSG_8COIN_3PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0xe0},
  { MSG_5COIN_3PLAY, 0x20},
  { MSG_3COIN_2PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0xf0},
  { MSG_2COIN_3PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x90},
  { MSG_1COIN_3PLAY, 0x80},
  { MSG_1COIN_4PLAY, 0x70},
  { MSG_1COIN_5PLAY, 0x60},
  { MSG_1COIN_6PLAY, 0x50},
  { MSG_FREE_PLAY, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_neobattl[] =
{
  { 0x0, 0xff, dsw_data_neobattl_3 },
  { 0x1, 0xff, dsw_data_neobattl_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_msgundam_2[] =
{
  { _("Language") , 0x0080, 2 },
  { _("English") , 0x0080},
  { _("Japanese") , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_msgundam_3[] =
{
  { MSG_COIN1, 0x0007, 8 },
  { MSG_4COIN_1PLAY, 0x0000},
  { MSG_3COIN_1PLAY, 0x0001},
  { MSG_2COIN_1PLAY, 0x0002},
  { MSG_1COIN_1PLAY, 0x0007},
  { MSG_1COIN_1PLAY, 0x0006},
  { MSG_1COIN_3PLAY, 0x0005},
  { MSG_1COIN_4PLAY, 0x0003},
  { MSG_1COIN_5PLAY, 0x0004},
  { MSG_COIN2, 0x0038, 8 },
  { MSG_4COIN_1PLAY, 0x0000},
  { MSG_3COIN_1PLAY, 0x0008},
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0038},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_1COIN_3PLAY, 0x0028},
  { MSG_1COIN_4PLAY, 0x0018},
  { MSG_1COIN_5PLAY, 0x0020},
  { _("Unknown 2-6") , 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  { MSG_FREE_PLAY, 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_msgundam_4[] =
{
  DSW_DEMO_SOUND( 0x1, 0x0),
  { MSG_DIFFICULTY, 0x6, 4 },
  { _("Easy")    , 0x4},
  { _("Normal")  , 0x6},
  { _("Hard")    , 0x2},
  { _("Hardest") , 0x0},
  { _("Unknown 1-3") , 0x8, 2 },
  { MSG_OFF, 0x8},
  { MSG_ON, 0x0},
  DSW_SCREEN( 0x10, 0x0),
  { _("Memory Check") , 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x0},
  { _("Unknown 1-6") , 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x0},
  DSW_SERVICE( 0, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_msgundam[] =
{
  { 0x6, 0x80, dsw_data_msgundam_2 },
  { 0x0, 0xff, dsw_data_msgundam_3 },
  { 0x1, 0xff, dsw_data_msgundam_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_umanclub_3[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  DSW_DEMO_SOUND( 0x0002, 0x0000),
  { _("Unknown 2-2*") , 0x0004, 2 },
  { MSG_OFF, 0x0004},
  { MSG_ON, 0x0000},
  { _("Stage Select") ,    0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { _("Unknown 2-4") , 0x0010, 2 },
  { MSG_OFF, 0x0010},
  { MSG_ON, 0x0000},
  { _("Unknown 2-5") , 0x0020, 2 },
  { MSG_OFF, 0x0020},
  { MSG_ON, 0x0000},
  { _("Unknown 2-6") , 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  DSW_SERVICE( 0, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_umanclub_4[] =
{
  { MSG_LIVES, 0x3, 4 },
  { "1" , 0x2},
  { "2" , 0x3},
  { "3" , 0x1},
  { "4" , 0x0},
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy")    , 0x8},
  { _("Normal")  , 0xc},
  { _("Hard")    , 0x4},
  { _("Hardest") , 0x0},
  { MSG_COINAGE, 0xf0, 16 },
  { MSG_6COIN_1PLAY, 0xa0},
  { MSG_5COIN_1PLAY, 0xb0},
  { MSG_4COIN_1PLAY, 0xc0},
  { MSG_3COIN_1PLAY, 0xd0},
  { MSG_8COIN_3PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0xe0},
  { MSG_5COIN_3PLAY, 0x20},
  { MSG_3COIN_2PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0xf0},
  { MSG_2COIN_3PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x90},
  { MSG_1COIN_3PLAY, 0x80},
  { MSG_1COIN_4PLAY, 0x70},
  { MSG_1COIN_5PLAY, 0x60},
  { MSG_1COIN_6PLAY, 0x50},
  { MSG_FREE_PLAY, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_umanclub[] =
{
  { 0x0, 0xff, dsw_data_umanclub_3 },
  { 0x1, 0xff, dsw_data_umanclub_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_stg_3[] =
{
  { MSG_DIFFICULTY, 0x0003, 4 },
  { _("Easy")    , 0x0002},
  { _("Normal")  , 0x0003},
  { _("Hard")    , 0x0001},
  { _("Hardest") , 0x0000},
  { _("Unknown 1-2") , 0x0004, 2 },
  { MSG_OFF, 0x0004},
  { MSG_ON, 0x0000},
  { _("Unknown 1-3") , 0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { MSG_LIVES, 0x0030, 4 },
  { "1" , 0x0010},
  { "2" , 0x0000},
  { "3" , 0x0030},
  { "5" , 0x0020},
  { _("Unknown 1-6") , 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  { _("Unknown 1-7") , 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_stg_4[] =
{
  { _("Unknown 2-0") , 0x1, 2 },
  { MSG_OFF, 0x1},
  { MSG_ON, 0x0},
  DSW_SCREEN( 0x2, 0x0),
  DSW_SERVICE( 0, 0x4),
  { _("Unknown 2-3") , 0x8, 2 },
  { MSG_OFF, 0x8},
  { MSG_ON, 0x0},
  { MSG_COIN1, 0x30, 4 },
  { MSG_2COIN_1PLAY, 0x10},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_2COIN_3PLAY, 0x0},
  { MSG_1COIN_1PLAY, 0x20},
  DSW_DEMO_SOUND( 0x40, 0x0),
  { _("Unknown 2-7") , 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_stg[] =
{
  { 0x0, 0xff, dsw_data_stg_3 },
  { 0x1, 0xff, dsw_data_stg_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_downtown_3[] =
{
  { _("Sales"), 0x0001, 2 },
  { _("Japan Only") , 0x0001},
  { _("World") , 0x0000},
  DSW_SCREEN( 0x0002, 0x0000),
  DSW_SERVICE( 0, 0x0004),
  DSW_DEMO_SOUND( 0x0000, 0x0008),
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0080},
#if 0
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
#endif
  { NULL, 0}
};

static struct DSW_DATA dsw_data_downtown_4[] =
{
  { _("Unknown 2-0&1"), 0x3, 4 },
  { "2" , 0x2},
  { "3" , 0x3},
  { "4" , 0x1},
  { "5" , 0x0},
  { MSG_EXTRA_LIFE, 0xc, 4 },
  { _("Never") , 0xc},
  { _("50K Only") , 0x8},
  { _("100k only") , 0x4},
  { _("50K Every 150K") , 0x0},
  { MSG_LIVES, 0x30, 4 },
  { "2" , 0x10},
  { "3" , 0x30},
  { "4" , 0x0},
  { "5" , 0x20},
  { _("World License"), 0x40, 2 },
  { _("Romstar") , 0x40},
  { _("Taito") , 0x0},
  { _("Coinage Type"), 0x80, 2 },
  { "1" , 0x80},
  { "2" , 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_downtown[] =
{
  { 0x0, 0xf6, dsw_data_downtown_3 },
  { 0x1, 0xbf, dsw_data_downtown_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_calibr50_3[] =
{
  { _("Licensed To") , 0x001, 2 },
  { _("Romstar")       , 0x0001},
  { _("None (Japan)")  , 0x0000},
  DSW_SCREEN( 0x0002, 0x0000),
  DSW_SERVICE( 0, 0x0004),
  DSW_DEMO_SOUND( 0x0008, 0x0000),
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_calibr50_4[] =
{
  { MSG_DIFFICULTY, 0x3, 4 },
  { _("Easiest") , 0x3},
  { _("Easy") , 0x2},
  { _("Normal") , 0x1},
  { _("Hard") , 0x0},
  { _("Score Digits") , 0x4, 2 },
  { "7" , 0x4},
  { "3" , 0x0},
  { MSG_LIVES, 0x8, 2 },
  { "3" , 0x8},
  { "4" , 0x0},
  { _("Display Score") , 0x10, 2 },
  { MSG_OFF, 0x0},
  { MSG_ON, 0x10},
  { _("Erase Backup Ram") , 0x20, 2 },
  { MSG_OFF, 0x0},
  { MSG_ON, 0x20},
  { _("Alt License") , 0x40, 2 },
  { MSG_OFF, 0x0},
  { MSG_ON, 0x40},
  { _("Unknown 2-7") , 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_calibr50[] =
{
  { 0x0, 0xfe, dsw_data_calibr50_3 },
  { 0x1, 0xbd, dsw_data_calibr50_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_metafox_3[] =
{
  { _("Licensed To")    , 0x0001, 2 },
  { _("Jordan")        , 0x0001},
  { _("Taito America") , 0x0000},
  DSW_SCREEN( 0x0002, 0x0000),
  DSW_SERVICE( 0, 0x0004),
  DSW_DEMO_SOUND( 0x0008, 0x0000),
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_metafox_4[] =
{
  { MSG_DIFFICULTY, 0x3, 4 },
  { _("Normal")  , 0x3},
  { _("Easy")    , 0x2},
  { _("Hard")    , 0x1},
  { _("Hardest") , 0x0},
  { _("Unknown 2-2"), 0x4, 2 },
  { MSG_OFF, 0x4},
  { MSG_ON, 0x0},
  { _("Unknown 2-3"), 0x8, 2 },
  { MSG_OFF, 0x8},
  { MSG_ON, 0x0},
  { MSG_LIVES, 0x30, 4 },
  { "1" , 0x10},
  { "2" , 0x0},
  { "3" , 0x30},
  { "5" , 0x20},
  { _("Alt License") , 0x40, 2 },
  { MSG_OFF, 0x0},
  { MSG_ON, 0x40},
  { _("Coinage Type"), 0x0080, 2 },
  { "1" , 0x0080},
  { "2" , 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_metafox[] =
{
  { 0x0, 0xfe, dsw_data_metafox_3 },
  { 0x1, 0xbd, dsw_data_metafox_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_arbalest_3[] =
{
  { _("Licensed To") , 0x0000, 3 },
  { _("Taito") , 0x0000},
  { _("Romstar") , 0x0001},
  DSW_SCREEN( 0x0002, 0x0000),
  DSW_SERVICE( 0, 0x0004),
  { _("Unknown 2-4") , 0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_arbalest_4[] =
{
  { MSG_DIFFICULTY, 0x3, 4 },
  { _("Easy") , 0x3},
  { _("Hard") , 0x2},
  { _("Harder") , 0x1},
  { _("Hardest") , 0x0},
  { MSG_EXTRA_LIFE, 0xc, 4 },
  { _("Never") , 0xc},
  { _("300k Only") , 0x8},
  { _("600k Only") , 0x4},
  { _("300k & 600k") , 0x0},
  { MSG_LIVES, 0x30, 4 },
  { "1" , 0x10},
  { "2" , 0x0},
  { "3" , 0x30},
  { "5" , 0x20},
  { _("Alt License") , 0x00, 2 },
  { MSG_OFF, 0x0},
  { MSG_ON, 0x40},
  { _("Coinage Type") , 0x80, 2 },
  { "1" , 0x80},
  { "2" , 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_arbalest[] =
{
  { 0x0, 0xfe, dsw_data_arbalest_3 },
  { 0x1, 0xbf, dsw_data_arbalest_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_drgnunit_2[] =
{
  { _("Coinage Type") , 0x0010, 2 },
  { "1" , 0x0010},
  { "2" , 0x0000},
  { _("Title") , 0x0020, 2 },
  { _("Dragon Unit") , 0x0020},
  { _("Castle of Dragon") , 0x0000},
  { "(C) / License" , 0x00c0, 4 },
  { _("Athena (Japan)") , 0x00c0},
  { _("Athena / Taito (Japan)") , 0x0080},
  { _("Seta USA / Taito America") , 0x0040},
  { _("Seta USA / Romstar") , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_drgnunit_3[] =
{
  { MSG_DIFFICULTY, 0x0003, 4 },
  { _("Easy") , 0x0003},
  { _("Normal") , 0x0002},
  { _("Hard") , 0x0001},
  { _("Hardest") , 0x0000},
  { MSG_EXTRA_LIFE, 0x000c, 4 },
  { _("150K Every 300K") , 0x0008},
  { _("200K Every 400K") , 0x000c},
  { _("300K Every 500K") , 0x0004},
  { _("400K Only") , 0x0000},
  { MSG_LIVES, 0x0030, 4 },
  { "1" , 0x0000},
  { "2" , 0x0010},
  { "3" , 0x0030},
  { "5" , 0x0020},
  { _("Unknown 1-6") , 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  { _("Unknown 1-7*") , 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_drgnunit_4[] =
{
  { _("Unknown 2-0") , 0x1, 2 },
  { MSG_OFF, 0x1},
  { MSG_ON, 0x0},
  DSW_SCREEN( 0x2, 0x0),
  { MSG_DEMO_SOUND, 0x4, 2 },
  { _("1 of 4 Scenes"), 0x4 },
  { _("1 of 8 Scenes"), 0x0 },
  DSW_SERVICE( 0, 0x8),
  { MSG_COIN1, 0x30, 4 },
  { MSG_2COIN_1PLAY, 0x10},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_2COIN_3PLAY, 0x0},
  { MSG_1COIN_1PLAY, 0x20},
  { MSG_COIN2, 0xc0, 4 },
  { MSG_2COIN_1PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0xc0},
  { MSG_2COIN_3PLAY, 0x0},
  { MSG_1COIN_1PLAY, 0x80},
  { NULL, 0}
};

static struct DSW_INFO dsw_drgnunit[] =
{
  { 0x6, 0xf0, dsw_data_drgnunit_2 },
  { 0x0, 0xfe, dsw_data_drgnunit_3 },
  { 0x1, 0xff, dsw_data_drgnunit_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_twineagl_3[] =
{
  DSW_SCREEN( 0x0002, 0x0000),
  DSW_SERVICE( 0, 0x0004),
  DSW_CABINET( 0x0000, 0x0008),
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_twineagl_4[] =
{
  { MSG_DIFFICULTY, 0x3, 4 },
  { _("Normal")  , 0x3},
  { _("Easy")    , 0x2},
  { _("Hard")    , 0x1},
  { _("Hardest") , 0x0},
  { MSG_EXTRA_LIFE, 0xc, 4 },
  { _("Never") , 0xc},
  { _("500K Only") , 0x8},
  { _("1000k only") , 0x4},
  { _("500K Every 1500K") , 0x0},
  { MSG_LIVES, 0x30, 4 },
  { "1" , 0x10},
  { "2" , 0x0},
  { "3" , 0x30},
  { "5" , 0x20},
  { _("Coinage Type"), 0x0080, 2 },
  { "1" , 0x0080},
  { "2" , 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_twineagl[] =
{
  { 0x0, 0xf6, dsw_data_twineagl_3 },
  { 0x1, 0xb3, dsw_data_twineagl_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_thunderl_2[] =
{
  { _("Force 1 Life"), 0x0010, 2 },
  { MSG_OFF, 0x0000},
  { MSG_ON, 0x0010},
  { _("Copyright"), 0x00e0, 5 },
  { _("Romstar") , 0x0080},
  { _("Seta (Romstar License)") , 0x00c0},
  { _("Seta (Visco License)") , 0x00e0},
  { _("Visco") , 0x00a0},
  { _("None") , 0x0060},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_thunderl_3[] =
{
  { MSG_COIN1, 0x000f, 16 },
  { MSG_4COIN_1PLAY, 0x000c},
  { MSG_3COIN_1PLAY, 0x000d},
  { MSG_4COIN_2PLAY, 0x0008},
  { MSG_2COIN_1PLAY, 0x000e},
  { MSG_3COIN_2PLAY, 0x0009},
  { MSG_4COIN_3PLAY, 0x0004},
  { MSG_4COIN_4PLAY, 0x0000},
  { MSG_3COIN_3PLAY, 0x0005},
  { MSG_2COIN_2PLAY, 0x000a},
  { MSG_1COIN_1PLAY, 0x000f},
  { MSG_3COIN_4PLAY, 0x0001},
  { MSG_2COIN_3PLAY, 0x0006},
  { MSG_2COIN_4PLAY, 0x0002},
  { MSG_1COIN_1PLAY, 0x000b},
  { MSG_1COIN_3PLAY, 0x0007},
  { MSG_1COIN_4PLAY, 0x0003},
  { MSG_COIN2, 0x00f0, 16 },
  { MSG_4COIN_1PLAY, 0x00c0},
  { MSG_3COIN_1PLAY, 0x00d0},
  { MSG_4COIN_2PLAY, 0x0080},
  { MSG_2COIN_1PLAY, 0x00e0},
  { MSG_3COIN_2PLAY, 0x0090},
  { MSG_4COIN_3PLAY, 0x0040},
  { MSG_4COIN_4PLAY, 0x0000},
  { MSG_3COIN_3PLAY, 0x0050},
  { MSG_2COIN_2PLAY, 0x00a0},
  { MSG_1COIN_1PLAY, 0x00f0},
  { MSG_3COIN_4PLAY, 0x0010},
  { MSG_2COIN_3PLAY, 0x0060},
  { MSG_2COIN_4PLAY, 0x0020},
  { MSG_1COIN_1PLAY, 0x00b0},
  { MSG_1COIN_3PLAY, 0x0070},
  { MSG_1COIN_4PLAY, 0x0030},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_thunderl_4[] =
{
  DSW_SERVICE( 0, 0x01),
  DSW_SCREEN( 0x0, 0x2),
  DSW_CABINET( 0x0, 0x4),
  { _("Controls"), 0x8, 2 },
  { "2" , 0x8},
  { "1" , 0x0},
  DSW_DEMO_SOUND( 0x0, 0x10),
  { MSG_LIVES, 0x20, 2 },
  { "3" , 0x20},
  { "2" , 0x0},
  { MSG_DIFFICULTY, 0x00c0, 4 },
  { _("Easy") , 0x0080},
  { _("Normal") , 0x00c0},
  { _("Hard") , 0x0040},
  { _("Hardest") , 0x0000},
  { NULL, 0}
};

static struct DSW_INFO dsw_thunderl[] =
{
  { 0x6, 0xe0, dsw_data_thunderl_2 },
  { 0x0, 0xff, dsw_data_thunderl_3 },
  { 0x1, 0xe9, dsw_data_thunderl_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_wits_2[] =
{
  { _("Unknown 3-4*"), 0x0010, 2 },
  { MSG_OFF, 0x0010},
  { MSG_ON, 0x0000},
  { _("Unknown 3-5*"), 0x0020, 2 },
  { MSG_OFF, 0x0020},
  { MSG_ON, 0x0000},
  { _("License"), 0x00c0, 4 },
  { _("Romstar") , 0x00c0},
  { _("Seta U.S.A") , 0x0080},
  { _("Visco (Japan Only)") , 0x0040},
  { _("Athena (Japan Only)") , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_wits_3[] =
{
  { MSG_DIFFICULTY, 0x0003, 4 },
  { _("Easy") , 0x0002},
  { _("Normal") , 0x0003},
  { _("Hard") , 0x0001},
  { _("Hardest") , 0x0000},
  { MSG_EXTRA_LIFE, 0x000c, 4 },
  { _("150k, 350k") , 0x0008},
  { _("200k, 500k") , 0x000c},
  { _("300k, 600k") , 0x0004},
  { _("400k") , 0x0000},
  { MSG_LIVES, 0x0030, 4 },
  { "1" , 0x0000},
  { "2" , 0x0010},
  { "3" , 0x0030},
  { "5" , 0x0020},
  { _("Max Players"), 0x0040, 2 },
  { "2" , 0x0040},
  { "4" , 0x0000},
  { _("Unknown 1-7*"), 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_wits_4[] =
{
  { _("Unknown 2-0"), 0x1, 2 },
  { MSG_OFF, 0x1},
  { MSG_ON, 0x0},
  DSW_SCREEN( 0x2, 0x0),
  { _("Unknown 2-2*"), 0x4, 2 },
  { MSG_OFF, 0x4},
  { MSG_ON, 0x0},
  DSW_SERVICE( 0, 0x08),
  { MSG_COIN1, 0x30, 4 },
  { MSG_4COIN_1PLAY, 0x0},
  { MSG_3COIN_1PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0x20},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_COIN2, 0xc0, 4 },
  { MSG_1COIN_1PLAY, 0xc0},
  { MSG_1COIN_3PLAY, 0x80},
  { MSG_1COIN_4PLAY, 0x40},
  { MSG_1COIN_6PLAY, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_wits[] =
{
  { 0x6, 0x70, dsw_data_wits_2 },
  { 0x0, 0xff, dsw_data_wits_3 },
  { 0x1, 0xff, dsw_data_wits_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_blandia_3[] =
{
  DSW_DEMO_SOUND( 0x0001, 0x0000),
  { _("Coinage Type"), 0x0002, 2 },
  { "1" , 0x0002},
  { "2" , 0x0000},
  { MSG_COIN1, 0x001c, 8 },
  { MSG_3COIN_1PLAY, 0x0010},
  { MSG_2COIN_1PLAY, 0x000c},
  { MSG_1COIN_1PLAY, 0x001c},
  { MSG_2COIN_3PLAY, 0x0004},
  { MSG_1COIN_1PLAY, 0x0018},
  { MSG_2COIN_5PLAY, 0x0008},
  { MSG_1COIN_3PLAY, 0x0014},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x00e0, 8 },
  { MSG_1COIN_1PLAY, 0x00e0},
  { MSG_2COIN_4PLAY, 0x0060},
  { MSG_1COIN_1PLAY, 0x00c0},
  { _("3 Coins/7 Credit") , 0x0080},
  { MSG_2COIN_5PLAY, 0x0020},
  { MSG_2COIN_6PLAY, 0x0040},
  { MSG_1COIN_3PLAY, 0x00a0},
  { MSG_FREE_PLAY, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_blandia_4[] =
{
  { MSG_LIVES, 0x3, 4 },
  { "1" , 0x2},
  { "2" , 0x3},
  { "3" , 0x1},
  { "4" , 0x0},
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy")    , 0x8},
  { _("Normal")  , 0xc},
  { _("Hard")    , 0x4},
  { _("Hardest") , 0x0},
  { _("2 Player Game"), 0x10, 2 },
  { _("2 Credits") , 0x10},
  { _("1 Credit")  , 0x0},
  { _("Continue"), 0x20, 2 },
  { _("1 Credit") , 0x20},
  { _("1 Coin")   , 0x0},
  DSW_SCREEN( 0x40, 0x0),
  DSW_SERVICE( 0, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_blandia[] =
{
  { 0x0, 0xff, dsw_data_blandia_3 },
  { 0x1, 0xff, dsw_data_blandia_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_eightfrc_3[] =
{
  { MSG_COIN1, 0x0007, 8 },
  { MSG_4COIN_1PLAY, 0x0004},
  { MSG_3COIN_1PLAY, 0x0005},
  { MSG_2COIN_1PLAY, 0x0006},
  { MSG_1COIN_1PLAY, 0x0007},
  { MSG_1COIN_1PLAY, 0x0003},
  { MSG_1COIN_3PLAY, 0x0002},
  { MSG_1COIN_4PLAY, 0x0001},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x0038, 8 },
  { MSG_4COIN_1PLAY, 0x0020},
  { MSG_3COIN_1PLAY, 0x0028},
  { MSG_2COIN_1PLAY, 0x0030},
  { MSG_1COIN_1PLAY, 0x0038},
  { MSG_1COIN_1PLAY, 0x0018},
  { MSG_1COIN_3PLAY, 0x0010},
  { MSG_1COIN_4PLAY, 0x0008},
  { MSG_FREE_PLAY, 0x0000},
  { _("Shared Credits"), 0x0040, 2 },
  { MSG_OFF, 0x0000},
  { MSG_ON, 0x0040},
  { _("Credits To Start"), 0x0080, 2 },
  { "1" , 0x0080},
  { "2" , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_eightfrc_4[] =
{
  DSW_SERVICE( 0, 0x01),
  DSW_SCREEN( 0x2, 0x0),
  DSW_DEMO_SOUND( 0x0, 0x4),
  { MSG_DIFFICULTY, 0x18, 4 },
  { _("Easy") , 0x10},
  { _("Normal") , 0x18},
  { _("Hard") , 0x8},
  { _("Hardest") , 0x0},
  { MSG_LIVES, 0x60, 4 },
  { "2" , 0x40},
  { "3" , 0x60},
  { "4" , 0x20},
  { "5" , 0x0},
  { _("Language"), 0x80, 2 },
  { _("English"), 0x00 },
  { _("Japanese"), 0x80},
  { NULL, 0}
};

static struct DSW_INFO dsw_eightfrc[] =
{
  { 0x0, 0xff, dsw_data_eightfrc_3 },
  { 0x1, 0x7b, dsw_data_eightfrc_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_gundhara_3[] =
{
  { MSG_COIN1, 0x000f, 16 },
  { MSG_4COIN_1PLAY, 0x0002},
  { MSG_3COIN_1PLAY, 0x0005},
  { MSG_2COIN_1PLAY, 0x0008},
  { MSG_3COIN_2PLAY, 0x0004},
  { MSG_4COIN_3PLAY, 0x0001},
  { MSG_1COIN_1PLAY, 0x000f},
  { MSG_3COIN_4PLAY, 0x0003},
  { MSG_2COIN_3PLAY, 0x0007},
  { MSG_1COIN_1PLAY, 0x000e},
  { MSG_2COIN_5PLAY, 0x0006},
  { MSG_1COIN_3PLAY, 0x000d},
  { MSG_1COIN_4PLAY, 0x000c},
  { MSG_1COIN_5PLAY, 0x000b},
  { MSG_1COIN_6PLAY, 0x000a},
  { MSG_1COIN_7PLAY, 0x0009},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x0030, 4 },
  { MSG_3COIN_1PLAY, 0x0000},
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_1COIN_1PLAY, 0x0020},
  { _("Country"), 0x00c0, 2 },
  { _("Japan") , 0x00c0},
  { _("World") , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_gundhara_4[] =
{
  { MSG_DIFFICULTY, 0x3, 4 },
  { _("Easy") , 0x2},
  { _("Normal") , 0x3},
  { _("Hard") , 0x1},
  { _("Hardest") , 0x0},
  { MSG_LIVES, 0xc, 4 },
  { "1" , 0x8},
  { "2" , 0xc},
  { "3" , 0x4},
  { "4" , 0x0},
  { MSG_EXTRA_LIFE, 0x30, 4 },
  { _("200K") , 0x30},
  { _("200K Every 200K") , 0x20},
  { _("400K") , 0x10},
  { _("None") , 0x0},
  DSW_DEMO_SOUND( 0x0, 0x40),
  DSW_SERVICE( 0x0, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_gundhara[] =
{
  { 0x0, 0xff, dsw_data_gundhara_3 },
  { 0x1, 0xbf, dsw_data_gundhara_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_zombraid_3[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  { _("Mirror") , 0x0002, 2 },
  { MSG_OFF, 0x0000},
  { MSG_ON, 0x0002},
  DSW_DEMO_SOUND( 0x0004, 0x0000),
  { MSG_DIFFICULTY, 0x0018, 4 },
  { _("Easy")    , 0x0010},
  { _("Normal")  , 0x0018},
  { _("Hard")    , 0x0008},
  { _("Hardest") , 0x0000},
  { _("Allow Continue") , 0x0020, 2 },
  { MSG_OFF, 0x0000},
  { MSG_ON, 0x0020},
  DSW_UNUSED( 0x0000, 0x0040),
  DSW_SERVICE( 0, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_zombraid_4[] =
{
  { MSG_COIN1, 0x7, 8 },
  { MSG_3COIN_1PLAY, 0x5},
  { MSG_2COIN_1PLAY, 0x6},
  { MSG_1COIN_1PLAY, 0x7},
  { MSG_1COIN_1PLAY, 0x4},
  { MSG_1COIN_3PLAY, 0x3},
  { MSG_1COIN_4PLAY, 0x2},
  { MSG_1COIN_5PLAY, 0x1},
  { MSG_1COIN_6PLAY, 0x0},
  { MSG_COIN2, 0x38, 8 },
  { MSG_3COIN_1PLAY, 0x28},
  { MSG_2COIN_1PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0x38},
  { MSG_1COIN_1PLAY, 0x20},
  { MSG_1COIN_3PLAY, 0x18},
  { MSG_1COIN_4PLAY, 0x10},
  { MSG_1COIN_5PLAY, 0x8},
  { MSG_1COIN_6PLAY, 0x0},
  { _("2 Coins to Start,1 to Continue") , 0x40, 2 },
  { MSG_NO, 0x40},
  { MSG_YES, 0x0},
  DSW_UNUSED( 0x0, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_zombraid[] =
{
  { 0x0, 0xfd, dsw_data_zombraid_3 },
  { 0x1, 0xff, dsw_data_zombraid_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_jjsquawk_3[] =
{
  { MSG_COIN1, 0x0007, 8 },
  { MSG_4COIN_1PLAY, 0x0001},
  { MSG_3COIN_1PLAY, 0x0002},
  { MSG_2COIN_1PLAY, 0x0004},
  { MSG_1COIN_1PLAY, 0x0007},
  { MSG_2COIN_3PLAY, 0x0003},
  { MSG_1COIN_1PLAY, 0x0006},
  { MSG_1COIN_3PLAY, 0x0005},
  { MSG_FREE_PLAY, 0x0000},
  { MSG_COIN2, 0x0038, 8 },
  { MSG_4COIN_1PLAY, 0x0008},
  { MSG_3COIN_1PLAY, 0x0010},
  { MSG_2COIN_1PLAY, 0x0020},
  { MSG_1COIN_1PLAY, 0x0038},
  { MSG_2COIN_3PLAY, 0x0018},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_1COIN_3PLAY, 0x0028},
  { MSG_FREE_PLAY, 0x0000},
  DSW_DEMO_SOUND( 0x0000, 0x0040),
  { _("Unknown 2-7"), 0x0080, 2 },
  { MSG_OFF, 0x0080},
  { MSG_ON, 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_jjsquawk_4[] =
{
  DSW_SCREEN( 0x1, 0x0),
  DSW_SERVICE( 0, 0x2),
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy")    , 0x8},
  { _("Normal")  , 0xc},
  { _("Hard")    , 0x4},
  { _("Hardest") , 0x0},
  { _("Energy"), 0x30, 4 },
  { "2" , 0x20},
  { "3" , 0x30},
  { "4" , 0x10},
  { "5" , 0x0},
  { MSG_EXTRA_LIFE, 0xc0, 4 },
  { _("20K Every 100K") , 0x80},
  { _("50K Every 200K") , 0xc0},
  { _("70K 200K Only") , 0x40},
  { _("100k only") , 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_jjsquawk[] =
{
  { 0x0, 0xbf, dsw_data_jjsquawk_3 },
  { 0x1, 0xff, dsw_data_jjsquawk_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_rezon_3[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  DSW_DEMO_SOUND( 0x0002, 0x0000),
  DSW_UNUSED( 0x0000, 0x0004),
  { MSG_CABINET, 0x0018, 3 },
  { _("Upright 1 Controller") , 0x0000},
  { _("Upright 2 Controllers") , 0x0018},
  { MSG_TABLE, 0x0008},
  DSW_UNUSED( 0x0000, 0x0020),
  DSW_UNUSED( 0x0000, 0x0040),
  DSW_SERVICE( 0, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_rezon_4[] =
{
  { MSG_LIVES, 0x3, 4 },
  { "2" , 0x2},
  { "3" , 0x3},
  { "4" , 0x1},
  { "5" , 0x0},
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy") , 0x8},
  { _("Normal") , 0xc},
  { _("Hard") , 0x4},
  { _("Hardest") , 0x0},
  { MSG_COINAGE, 0xf0, 16 },
  { MSG_6COIN_1PLAY, 0xa0},
  { MSG_5COIN_1PLAY, 0xb0},
  { MSG_4COIN_1PLAY, 0xc0},
  { MSG_3COIN_1PLAY, 0xd0},
  { MSG_8COIN_3PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0xe0},
  { MSG_5COIN_3PLAY, 0x20},
  { MSG_3COIN_2PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0xf0},
  { MSG_2COIN_3PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x90},
  { MSG_1COIN_3PLAY, 0x80},
  { MSG_1COIN_4PLAY, 0x70},
  { MSG_1COIN_5PLAY, 0x60},
  { MSG_1COIN_6PLAY, 0x50},
  { MSG_FREE_PLAY, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_rezon[] =
{
  { 0x0, 0xff, dsw_data_rezon_3 },
  { 0x1, 0xff, dsw_data_rezon_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_wrofaero_3[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  { _("Unknown 1-1*"), 0x0002, 2 },
  { MSG_OFF, 0x0002},
  { MSG_ON, 0x0000},
  { _("Unknown 1-2*"), 0x0004, 2 },
  { MSG_OFF, 0x0004},
  { MSG_ON, 0x0000},
  { _("Stage & Weapon Select"),    0x0008, 2 },
  { MSG_OFF, 0x0008},
  { MSG_ON, 0x0000},
  { _("Unknown 1-4"), 0x0010, 2 },
  { MSG_OFF, 0x0010},
  { MSG_ON, 0x0000},
  { _("Unknown 1-5"), 0x0020, 2 },
  { MSG_OFF, 0x0020},
  { MSG_ON, 0x0000},
  { _("Unknown 1-6"), 0x0040, 2 },
  { MSG_OFF, 0x0040},
  { MSG_ON, 0x0000},
  DSW_SERVICE( 0, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_wrofaero_4[] =
{
  { MSG_LIVES, 0x3, 4 },
  { "2" , 0x2},
  { "3" , 0x3},
  { "4" , 0x1},
  { "5" , 0x0},
  { _("Unknown 2-2&3"), 0xc, 4 },
  { "0" , 0x8},
  { "1" , 0xc},
  { "2" , 0x4},
  { "3" , 0x0},
  { MSG_COINAGE, 0xf0, 16 },
  { MSG_6COIN_1PLAY, 0xa0},
  { MSG_5COIN_1PLAY, 0xb0},
  { MSG_4COIN_1PLAY, 0xc0},
  { MSG_3COIN_1PLAY, 0xd0},
  { MSG_8COIN_3PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0xe0},
  { MSG_5COIN_3PLAY, 0x20},
  { MSG_3COIN_2PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0xf0},
  { MSG_2COIN_3PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x90},
  { MSG_1COIN_3PLAY, 0x80},
  { MSG_1COIN_4PLAY, 0x70},
  { MSG_1COIN_5PLAY, 0x60},
  { MSG_1COIN_6PLAY, 0x50},
  { MSG_FREE_PLAY, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_wrofaero[] =
{
  { 0x0, 0xff, dsw_data_wrofaero_3 },
  { 0x1, 0xff, dsw_data_wrofaero_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_zingzip_3[] =
{
  DSW_SCREEN( 0x0001, 0x0000),
  DSW_DEMO_SOUND( 0x0002, 0x0000),
  DSW_UNUSED( 0x0000, 0x0004),
  DSW_UNUSED( 0x0000, 0x0008),
  DSW_UNUSED( 0x0000, 0x0010),
  DSW_UNUSED( 0x0000, 0x0020),
  DSW_UNUSED( 0x0000, 0x0040),
  DSW_SERVICE( 0, 0x0080),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_zingzip_4[] =
{
  { MSG_LIVES, 0x3, 4 },
  { "2" , 0x2},
  { "3" , 0x3},
  { "4" , 0x1},
  { "5" , 0x0},
  { MSG_DIFFICULTY, 0xc, 4 },
  { _("Easy")    , 0x8},
  { _("Normal")  , 0xc},
  { _("Hard")    , 0x4},
  { _("Hardest") , 0x0},
  { MSG_COINAGE, 0xf0, 16 },
  { MSG_6COIN_1PLAY, 0xa0},
  { MSG_5COIN_1PLAY, 0xb0},
  { MSG_4COIN_1PLAY, 0xc0},
  { MSG_3COIN_1PLAY, 0xd0},
  { MSG_8COIN_3PLAY, 0x10},
  { MSG_2COIN_1PLAY, 0xe0},
  { MSG_5COIN_3PLAY, 0x20},
  { MSG_3COIN_2PLAY, 0x30},
  { MSG_1COIN_1PLAY, 0xf0},
  { MSG_2COIN_3PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x90},
  { MSG_1COIN_3PLAY, 0x80},
  { MSG_1COIN_4PLAY, 0x70},
  { MSG_1COIN_5PLAY, 0x60},
  { MSG_1COIN_6PLAY, 0x50},
  { MSG_FREE_PLAY, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_zingzip[] =
{
  { 0x0, 0xff, dsw_data_zingzip_3 },
  { 0x1, 0xff, dsw_data_zingzip_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_usclssic_3[] =
{
  { _("Credits For 9-Hole"), 0x0001, 2 },
  { "2" , 0x0001},
  { "3" , 0x0000},
  { _("Game Type"), 0x0002, 2 },
  { _("Domestic") , 0x0002},
  { _("Foreign") , 0x0000},
  { MSG_LIVES, 0x000c, 4 },
  { "1" , 0x0004},
  { "2" , 0x0008},
  { "3" , 0x000c},
  { "4" , 0x0000},
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_1PLAY, 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_usclssic_4[] =
{
  DSW_CABINET( 0x0, 0x1),
  DSW_SCREEN( 0x2, 0x0),
  DSW_SERVICE( 0, 0x4),
  { _("Flight Distance"), 0x38, 8 },
  { _("Normal") , 0x38},
  { _("-30 Yards") , 0x30},
  { _("+10 Yards") , 0x28},
  { _("+20 Yards") , 0x20},
  { _("+30 Yards") , 0x18},
  { _("+40 Yards") , 0x10},
  { _("+50 Yards") , 0x8},
  { _("+60 Yards") , 0x0},
  { _("Licensed To")    , 0xc0, 4 },
  { _("Romstar")       , 0xc0},
  { _("None (Japan)")  , 0x80},
  { _("Taito")         , 0x40},
  { _("Taito America") , 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_usclssic[] =
{
  { 0x6, 0xff, dsw_data_usclssic_3 },
  { 0x7, 0xfe, dsw_data_usclssic_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_tndrcade_3[] =
{
  { MSG_DIFFICULTY, 0x0003, 4 },
  { _("Easy")    , 0x0002},
  { _("Normal")  , 0x0003},
  { _("Hard")    , 0x0001},
  { _("Hardest") , 0x0000},
  { MSG_EXTRA_LIFE, 0x000c, 4 },
  { _("50K  Only") , 0x000c},
  { _("50K Every 150K") , 0x0004},
  { _("70K Every 200K") , 0x0000},
  { _("100k only") , 0x0008},
  { MSG_LIVES, 0x0030, 4 },
  { "1" , 0x0010},
  { "2" , 0x0000},
  { "3" , 0x0030},
  { "5" , 0x0020},
  { _("Allow Continue") , 0x0040, 2 },
  { MSG_OFF, 0x0000},
  { MSG_ON, 0x0040},
  { _("Licensed To"), 0x80, 2 },	/* + coin mode (not supported */
  { _("Taito America Corp.") , 0x0080},
  { _("Taito Corp. Japan") , 0x0000},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_tndrcade_4[] =
{
  { _("Title") , 0x1, 2 },
  { _("Thundercade") , 0x1},
  { _("Twin Formation") , 0x0},
  DSW_SCREEN( 0x2, 0x0),
  DSW_SERVICE( 0, 0x4),
  DSW_DEMO_SOUND( 0x0, 0x8),
  { MSG_COIN1, 0x30, 4 },
  { MSG_2COIN_1PLAY, 0x10},
  { MSG_1COIN_1PLAY, 0x30},
  { MSG_2COIN_3PLAY, 0x0},
  { MSG_1COIN_1PLAY, 0x20},
  { MSG_COIN2, 0xc0, 4 },
  { MSG_2COIN_1PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0xc0},
  { MSG_2COIN_3PLAY, 0x0},
  { MSG_1COIN_1PLAY, 0x80},
  { NULL, 0}
};

static struct DSW_INFO dsw_tndrcade[] =
{
  { 0x6, 0xff, dsw_data_tndrcade_3 },
  { 0x7, 0xff, dsw_data_tndrcade_4 },
  { 0, 0, NULL }
};

static UINT8 seta_dsw_r(UINT32 offset) {
  if ((offset & 6)) {
    return input_buffer[0];
  }
  return input_buffer[1];
}

static void seta_init() {
  int code_size = get_region_size(REGION_CPU1);
  limitx = current_game->video->screen_x + current_game->video->border_size;
  limity = current_game->video->screen_y + current_game->video->border_size;
  visuy = current_game->video->screen_y;
  old_bank = -1;
  latch1 = latch2 = 0xff;

  min_y = 0; // some games have a "shift" in their y coordinates (metafox, tndrcade...)

  bank_bg0 = 0x40; // normally !
  find_offsets();

  GFX_SPR = NULL;

  M6502ROM = RAM+0xa000;

  if (GFX) {
    layer_id_data[0] = add_layer_info(gettext("BG0"));
    if (load_region[REGION_GFX3]) {
      layer_id_data[1] = add_layer_info(gettext("BG1"));
      id_sprites = 2;
      layer_id_data[2] = add_layer_info(gettext("SPRITES BG"));
      layer_id_data[3] = add_layer_info(gettext("SPRITES FG"));
    } else {
      id_sprites = 1;
      layer_id_data[1] = add_layer_info(gettext("SPRITES BG"));
      layer_id_data[2] = add_layer_info(gettext("SPRITES FG"));
    }
  } else {
    id_sprites = 0;
    layer_id_data[0] = add_layer_info(gettext("SPRITES BG"));
    layer_id_data[1] = add_layer_info(gettext("SPRITES FG"));
  }

  RAM_BG0 = RAM+0x000000;
  RAM_SPR2= RAM+0x004000;
  RAM_SPR = RAM+0x008000;
  RAM_CTRL = RAM+0x09000;
  RAM_PAL = RAM+0x9010;
  RAM_BG1 = RAM+0xb810; // no known game using bg1 + 6502 + keep room for ram_pal (c0 banks)
  RAM_CTRL2 = RAM_BG1 + 0x4000;

  set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);

/*
 *  StarScream Stuff follows
 */

  ByteSwap(ROM,code_size);

  AddMemFetch(0x000000, code_size-1, ROM+0x000000-0x000000);	// 68000 ROM
  AddMemFetch(-1, -1, NULL);

  AddReadBW(0x000000, code_size-1, NULL, ROM+0x000000);			// 68000 ROM

  seta_tiles_offset = double_mapping = fixed_layers = 0;  // normal color mapping for layers
  buffered_sprites = 0;
}

static int stopped_68k;

static void stop_68k(UINT32 offset, UINT16 data) {
  s68000releaseTimeslice();
  print_debug("[Stop68000]\n");
  stopped_68k = 1;
}

static int gun_input_bit = 0, gun_input_src = 0;

/* Big congratulations to mame for decoding how this serial controler worked.
   Notice that it would be more efficient to patch the rom to directly get
   the byte instead of passing the results bit per bit... If I am bored one day
   it would be something interesting to do !!! */

static UINT8 zombraid_gun_r(UINT32 offset) /* Serial interface */
{
  int data = input_buffer[13 + gun_input_src]; /* Input Ports 13-16 */
  return (data >> gun_input_bit) & 1;
}

/* Bit 0 is clock, 1 is data, 2 is reset */
static void zombraid_gun_w(UINT32 offset, UINT8 data) {
  static int bit_count = 0, old_clock = 0;

  if(data&4) { bit_count = 0; return; } /* Reset */

  if((data&1) == old_clock) return; /* No change */

  if(old_clock == 0) /* Rising edge */
    {
      switch (bit_count)
	{
	case 0:
	case 1: /* Starting sequence 2,3,2,3. Other inputs? */
	  break;
	case 2: /* First bit of source */
	  gun_input_src = (gun_input_src&2) | (data>>1);
	  break;
	case 3: /* Second bit of source */
	  gun_input_src = (gun_input_src&1) | (data&2);
	  break;
	default:
	  gun_input_bit = bit_count - 4;
	  gun_input_bit = 8 - gun_input_bit; /* Reverse order */
	  break;
	}
      bit_count++;
    }

  old_clock = data & 1;
}

static void hack6(UINT32 adr) {
  // speed hack on 6 bytes
  WriteWord(&ROM[adr],0x4239); // clr.b $aa0000
  WriteWord(&ROM[adr+2],0xaa);
  WriteWord(&ROM[adr+4],0);
}

static void hack8(UINT32 adr) {
  // speed hack on 8 bytes
  WriteWord(&ROM[adr],0x13FC);
  WriteWord(&ROM[adr+2],0x0);
  WriteWord(&ROM[adr+4],0x00AA);
  WriteWord(&ROM[adr+6],0x00);
}

static void load_blandia() {
  // 2 bg layers, no 6502, blandia like memory mapping

  int rom_size;
  UINT8 *buf;
  UINT8 *rom;
  int rpos;

  // I prefer to avoid a speed hack for this one, the functions counts the vbl and sometimes
  // waits for more than 1

  seta_samples_bank = -1;
  RAMSize=0xa000+0x10000+0x80000; // 68k ram + 6502 ram + big 68k ram at the end
  if(!(RAM=AllocateMem(RAMSize))) return;

  seta_init();

  tile_hack = 0;

  InitPaletteMap(RAM_PAL, 0x60, 0x10, 0x8000);

  // deocde gfx regions

  if (is_current_game("blandia")) {
    buffered_sprites = 1;

  /* This is from mame. Maybe there was a way to load directly the roms with a different
     gfxlayout, but I am very bad at finding gfxlayouts (probably because I have no
     utility for that. Anyway, the easiest way is to reuse their decoding code */

    rom_size = 0x80000;
    buf = malloc(rom_size);

    if (!buf) return;

    rom = load_region[REGION_GFX2] + 0x40000;

    for (rpos = 0; rpos < rom_size/2; rpos++) {
      buf[rpos+0x40000] = rom[rpos*2];
      buf[rpos] = rom[rpos*2+1];
    }

    memcpy( rom, buf, rom_size );

    rom = load_region[REGION_GFX3] + 0x40000;

    for (rpos = 0; rpos < rom_size/2; rpos++) {
      buf[rpos+0x40000] = rom[rpos*2];
      buf[rpos] = rom[rpos*2+1];
    }

    memcpy( rom, buf, rom_size );

    free(buf);
    fixed_layers = 1;
    fixed_bg1 = 0;
  } else {

    if (is_current_game("eightfrc")) {
      // speed hack
      hack6(0x11cc);

      WriteWord(&ROM[0x11d2],0x4e71);
      WriteWord(&ROM[0x11d4],0x4e71);
      min_y = 8;
    } else if (is_current_game("gundhara") || is_current_game("zombraid")) {
      fixed_layers = 2; // banks of 64 colors
      if (is_current_game("zombraid")) {
	hack8(0xE386);
	WriteWord(&ROM[0xE38e],0x4e71);

	// Add some code to call the crosshair display function if needed
	/* No finally I won't add this code. The game is hard coded to display this
	   crosshair only at 2 specific places in the game. Calling this function directly
	   adds 1-up at the bottom of the screen behind the bullets, which is not very
	   nice. Worse : when the sprte list is reinitialized, the crosshair can
	   disappear for about 1 second, and 1 second it's very long in that game !!!

	   So we will use the standard raine crosshair instead, not that bad...

	WriteWord(&ROM[0x1f0000],0x3f3c);
	WriteWord(&ROM[0x1f0002],0x77); // move #$77,-(sp)
	WriteWord(&ROM[0x1f0004],0x3f3c);
	WriteWord(&ROM[0x1f0006],0x2); // move #2,-(sp)
	WriteWord(&ROM[0x1f0008],0x4e41); // trap #1
	WriteWord(&ROM[0x1f000a],0x588f); // addq.l #4,sp
	hack6(0x1f000c);

	*/
	// trap #1 in eab2 starts mouse polling (but not specific to the crosshair)
	// WriteWord(&ROM[0x9a0a],0x4e71);

	// parameters of trap #1, function 2 :
	// 77 : show crosshair 1 and enables it
	// 79 : show crosshair 2 and enables it
	// 73 : funny animation

	// Center the crosshair when it will be first displayed...

	input_buffer[13] = 0x80;
	input_buffer[14] = 0x80;
	input_buffer[15] = 0x80;
	input_buffer[16] = 0x80;
      }
    } else if (is_current_game("jjsquawk")) {
      fixed_layers = 2; // banks of 64 colors
      memcpy (ROM + 0x100000, ROM + 0x80000, 0x80000);

      hack6(0x990);
    } else if (is_current_game("rezon")) {
      // input_buffer[6] = 0xff; // bit 4 is for a taito logo at startup
      memset(ROM + 0x40000, 0x00, 0x100000-0x40000);
      // hack6(0x66e);
      WriteWord(&ROM[0x668],0x4ef9);
      WriteWord(&ROM[0x66a],0x13);
      WriteWord(&ROM[0x66c],0xfff0);

      WriteWord(&ROM[0x13FFf0],0x52AD);
      WriteWord(&ROM[0x13FFf2],0x18F8);

      hack6(0x13fff4);
      WriteWord(&ROM[0x13fffa],0x6100-12);
    } else if (is_current_game("zingzip")) {
      double_mapping = 1; // layer 0 = 64 colors, layer 1 = 16 colors
      hack6(0x4d0);
    } else if (is_current_game("daioh")) {
      hack6(0x47a);
    }
  }

  rom = load_region[REGION_SOUND1]; // fix banks
  if (is_current_game("gundhara")) {
    // This one has its 2 halves swapped !!!
    UINT8 *buff = AllocateMem(0x80000);
    memcpy(buff, rom, 0x80000);
    memcpy(rom, rom+0x80000,0x80000);
    memcpy(rom+0x80000,buff,0x80000);
    FreeMem(buff);
  } else if (is_current_game("zombraid")) {
    // This one has a too big 1st rom for sound, move a part of it out of the bank area
    memmove(rom+0x100000,rom + 0x80000, 0x180000);
  } else if (get_region_size(REGION_SOUND1) >= 0x140000) {
    memcpy(rom+0x100000, rom + 0xc0000, 0x40000);
  }

  memset(seta_vregs,0x0,sizeof(seta_vregs));
  memset(RAM,0,RAMSize);

  if (is_current_game("drgnunit") || is_current_game("stg")) {
    // this one has a totally different memory map...
    /* These 2 should have gone into LoadMetafox (only 1 bg layer).
       This is becoming quite messy... */
    AddRWBW(0x080000, 0x0bfFFF, NULL, RAM+0x1a000);			// 68000 RAM
    AddRWBW(0xf00000, 0xf0fFFF, NULL, RAM+0x5a000);			// 68000 RAM
    AddRWBW(0xffc000, 0xffffff, NULL, RAM+0x6a000);			// 68000 RAM

    AddReadByte(0x100000, 0x103FFF, seta_sound_word_rb, NULL);
    AddReadWord(0x100000, 0x103FFF, seta_sound_word_r, NULL);
    AddWriteByte(0x100000, 0x103FFF, seta_sound_word_wb, NULL);
    AddWriteWord(0x100000, 0x103FFF, seta_sound_word_w, NULL);

    AddRWBW(0x700000, 0x7003ff, NULL, RAM_PAL);
    AddRWBW(0x900000, 0x903fff, NULL, RAM_BG0);
    AddRWBW(0x800000, 0x80000f, NULL, RAM_CTRL);		// SCROLL RAM
    AddReadBW(0xb00000,0xb00005, NULL, &input_buffer[2]); // inputs, coins
    AddRWBW(0xd00000, 0xd00607, NULL, RAM_SPR);			// sprites y
    AddRWBW(0xe00000, 0xe03fff, NULL, RAM_SPR2);
    AddReadBW(0x600000, 0x600003, seta_dsw_r, NULL);
    AddRWBW(0xc00000, 0xc00001, NULL, RAM+0x6e000);			// 68000 RAM
    AddReadBW(0x500000, 0x500007, NULL, (UINT8*)seta_vregs);
    AddWriteBW(0x500000, 0x500005, seta_vregs_w, NULL);

    AddWriteByte(0xAA0000, 0xAA0001, stop_68k, NULL);			// Trap Idle 68000
    RAMSize = 0x6e001;
    buffered_sprites = 1;
    bank_bg0 = 0;

    if (is_current_game("drgnunit")) {
      hack6(0x65c);
    } else {
      // stg is special because it has only 2 bytes free for the speed hack !
     WriteWord(&ROM[0x478],0x4EF8);
     WriteWord(&ROM[0x47a],0x03f0);
     WriteWord(&ROM[0x3f0],0x027C); // the code I just overwrote...
     WriteWord(&ROM[0x3f2],0xE1FF);
     hack6(0x003f4);
     WriteWord(&ROM[0x003fa],0x6100-8);
    }

    finish_conf_68000(0);
    return;
  }

  AddResetHandler(&quiet_reset_handler);
  if (is_current_game("msgundam")) {
    AddRWBW(0x200000, 0x20fFFF, NULL, RAM+0x1a000);			// 68000 RAM
    AddRWBW(0x210000, 0x21fFFF, NULL, RAM+0x1a000);			// mirror
    AddRWBW(0x220000, 0x22fFFF, NULL, RAM+0x1a000);			// mirror
    AddRWBW(0x230000, 0x23fFFF, NULL, RAM+0x1a000);			// mirror
    AddRWBW(0x240000, 0x24fFFF, NULL, RAM+0x1a000);			// mirror
  } else if (is_current_game("daioh")) {
    AddRWBW(0x100000, 0x10fFFF, NULL, RAM+0x1a000);			// 68000 RAM
  } else {
    AddRWBW(0x200000, 0x21fFFF, NULL, RAM+0x1a000);			// 68000 RAM
  }
  AddRWBW(0x300000, 0x30ffff, NULL, RAM+0x1a000+0x20000);		// ???
  AddRWBW(0x700000, 0x7003ff, NULL, RAM+0x1a000+0x30000);		// ???
  AddRWBW(0x701000, 0x70ffff, NULL, RAM+0x1a000+0x30400);		// real ram ?
  AddReadBW(0x500000, 0x500005, NULL, (UINT8*)seta_vregs);
  if (is_current_game("msgundam"))
    AddWriteBW(0x500000, 0x500005, msgundam_vregs_w, NULL);
  else
    AddWriteBW(0x500000, 0x500005, seta_vregs_w, NULL);
  AddRWBW(0xb04000, 0xb0ffff, NULL, RAM+0x1a000+0x40408);		// wasted ram
  AddRWBW(0xb84000, 0xb8ffff, NULL, RAM+0x1a000+0x50048);		// wasted ram bis
  AddRWBW(0x804000, 0x80ffff, NULL, RAM+0x1a000+0x50c48);		// wasted ram bis

  AddReadBW(0x400000,0x400005, NULL, &input_buffer[2]); // inputs, coins
  if (is_current_game("daioh")) {
    AddReadBW(0x500006, 0x500007, NULL, &input_buffer[8]); // daioh specific buttons 4-6
  }

  AddReadBW(0x600000, 0x600003, seta_dsw_r, NULL);

  AddRWBW(0x700400, 0x700fFF, NULL, RAM_PAL);			// COLOUR RAM
  if (is_current_game("blandia")) {
    AddRWBW(0x800000, 0x800607, NULL, RAM_SPR);			// sprites y
    AddRWBW(0x900000, 0x903FFF, NULL, RAM_SPR2);			// OBJECT RAM
    AddRWBW(0xa00000, 0xa0000f, NULL, RAM_CTRL);		// SCROLL RAM
    AddRWBW(0xa80000, 0xa8000f, NULL, RAM_CTRL2);		// SCROLL RAM (layer 2)
    AddRWBW(0xb00000, 0xb03FFF, NULL, RAM_BG0);			// BG0 RAM
    AddRWBW(0xb80000, 0xb83FFF, NULL, RAM_BG1);			// BG0 RAM
    AddRWBW(0x880000, 0x880001, NULL, RAM+0x1a000+0x40406);		// ???
  } else if (is_current_game("msgundam")) {
    AddRWBW(0x800000, 0x800607, NULL, RAM_SPR);			// sprites y
    AddRWBW(0x900000, 0x903FFF, NULL, RAM_SPR2);			// OBJECT RAM
    AddRWBW(0xa00000, 0xa03FFF, NULL, RAM_BG0);			// BG0 RAM
    AddRWBW(0xa80000, 0xa83FFF, NULL, RAM_BG1);			// BG0 RAM
    AddRWBW(0xb00000, 0xb0000f, NULL, RAM_CTRL);		// SCROLL RAM
    AddRWBW(0xb80000, 0xb8000f, NULL, RAM_CTRL2);		// SCROLL RAM (layer 2)
    AddRWBW(0x880000, 0x880001, NULL, RAM+0x1a000+0x40406);		// ???
    buffered_sprites = 1;

  } else {
    AddRWBW(0x800000, 0x803fff, NULL, RAM_BG0);
    AddRWBW(0x880000, 0x883fff, NULL, RAM_BG1);
    AddRWBW(0x900000, 0x90000f, NULL, RAM_CTRL);		// SCROLL RAM
    AddRWBW(0x980000, 0x98000f, NULL, RAM_CTRL2);		// SCROLL RAM (layer 2)
    AddRWBW(0xa00000, 0xa00607, NULL, RAM_SPR);			// sprites y
    AddRWBW(0xb00000, 0xb03FFF, NULL, RAM_SPR2);			// OBJECT RAM
    AddRWBW(0xa80000, 0xa80001, NULL, RAM+0x1a000+0x40406);		// ???
    AddRWBW(0x884000, 0x88ffff, NULL, RAM+0x1a000+0x5cc48);		// wasted ram bis
    AddRWBW(0xb04000, 0xb13fff, NULL, RAM+0x1a000+0x68c48);		// wasted ram

  }
  AddReadByte(0xc00000, 0xc03FFF, seta_sound_word_rb, NULL);
  AddReadWord(0xc00000, 0xc03FFF, seta_sound_word_r, NULL);
  AddWriteByte(0xc00000, 0xc03FFF, seta_sound_word_wb, NULL);
  AddWriteWord(0xc00000, 0xc03FFF, seta_sound_word_w, NULL);

  if (is_current_game("zombraid")) {
    AddReadByte(0xf00002,0xf00003,zombraid_gun_r,NULL);
    AddWriteByte(0xf00000,0xf00001,zombraid_gun_w,NULL);
    GameMouse = 1;
    draw_crosshair = 1;
  }

  AddWriteByte(0xAA0000, 0xAA0001, stop_68k, NULL);			// Trap Idle 68000

  finish_conf_68000(0);

#ifdef USE_XSYSTEM
  seta_x1.RAM_A	= RAM_SPR2;
  seta_x1.RAM_B	= RAM_SPR;
  seta_x1.GFX		= GFX_SPR;
  seta_x1.MASK		= GFX_SPR_SOLID;
  seta_x1.bmp_x	= 16;
  seta_x1.bmp_y	= 16;
  seta_x1.bmp_w	= 384;
  seta_x1.bmp_h	= 240;
  seta_x1.tile_mask	= 0x3fff; // 0x1FFF;
  seta_x1.scr_x	= 0;
  seta_x1.scr_y	= 0;
#endif
}

static void calibr50_latch_w(UINT32 offset, UINT16 data) {
  data &= 0xff;
  latch2 = data;
  m6502ReleaseTimeslice();
  // In fact it's much better to exit the frame because otherwise you can
  // have a recursive loop !!!
  // cpu_execute_cycles(CPU_68K_0, 100); // 100 cycles is enough ?
}

static UINT16 usclssic_trackball_xy_r(UINT32 offset)
{
	switch (offset & 6)
	{
	case 0:	return input_buffer[0];
	case 2:	return input_buffer[1];
	case 4:	return input_buffer[2];
	case 6:	return input_buffer[3];
	}
	return 0;
}

static UINT16 dsw_usclssic_r(UINT32 offset) {
  UINT16 inp = ReadWord(&input_buffer[6]); // dsw
  switch (offset & 6)
    {
    case 0:	return (inp >>  8) & 0xf;
    case 2:	return (inp >> 12) & 0xf;
    case 4:	return (inp >>  0) & 0xf;
    case 6:	return (inp >>  4) & 0xf;
    }
  return 0;
}

static void calibr50_soundlatch_w(UINT32 offset, UINT16 data) {
  latch1 = data;
  m6502nmi();
  m6502exec(100);	// 100 cycles is enough ?
}

static void usclssic_lockout_w(UINT32 offset, UINT16 data)
{
  seta_tiles_offset = (data & 0x10) ? 0x4000: 0;

  // seta_coin_lockout_w(data);
}

static void YM2203_w(UINT32 offset,UINT8 data) {
  if (offset & 1)
    YM2203_write_port_0_w(offset,data);
  else
    YM2203_control_port_0_w(offset,data);
}

static void YM3812_w(UINT32 offset,UINT8 data) {
  if (offset & 1)
    YM3812_write_port_0_w(offset,data);
  else
    YM3812_control_port_0_w(offset,data);
}

static void sound_wiggielatch_w(UINT32 offset, UINT8 data) {
  latch1 = data;
  cpu_interrupt(CPU_Z80_0, 0x38);
}

static void load_arbalest(void)
{
  // One or zero bg layer, 1 optional 6502

  RAMSize=0xa000+0x10000+0x100000; // 68k ram + 6502 ram + big 68k ram at the end
  if(!(RAM=AllocateMem(RAMSize))) return;

  seta_init();

  if (is_current_game("twineagl")) {
    tile_hack = 1;
  } else
    tile_hack = 0;

  memset(twineagl_tilebank, 0, 4*2);

   /* ----- M6510/M6502, 65ce02 in fact ----- */

  if (is_current_game("wiggie")) {
    // decode 68k rom ? But how a bootleg can be encoded ???
    UINT8 *src;
    int len;
    UINT8 temp[16];
    int i,j;

    src = load_region[REGION_CPU1];
    len = get_region_size(REGION_CPU1);
    for (i = 0;i < len;i += 16) {
      memcpy(temp,&src[i],16);
      for (j = 0;j < 16;j++) {
	static int convtable[16] =
	  {
	    0x0, 0x1, 0x8, 0x9,
	    0x2, 0x3, 0xa, 0xb,
	    0x4, 0x5, 0xc, 0xd,
	    0x6, 0x7, 0xe, 0xf
	  };

	src[i+j] = temp[convtable[j]];
      }
    }

    /* And this one has a z80 instead of the 6502... almost all the bootlegs do have
       a z80 !!! */

    AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
    AddZ80ARead(0x0000, 0x7fff, NULL, Z80ROM);
    AddZ80ARead(0x8000, 0x87ff, NULL, M6502ROM);
    AddZ80ARead(0x9800, 0x9800, OKIM6295_status_0_r, NULL);
    AddZ80ARead(0xa000, 0xa000, NULL, &latch1);

    AddZ80AWrite(0x8000, 0x87ff, NULL, M6502ROM);
    AddZ80AWrite(0x9800, 0x9800, OKIM6295_data_0_w, NULL);

    AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
    AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);

    AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
    AddZ80AReadPort(-1, -1, NULL, NULL);

    AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,			NULL);	// Trap Idle Z80
    AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
    AddZ80AWritePort(-1, -1, NULL, NULL);
    AddZ80AInit();
  } else if (load_region[REGION_CPU2]) {
    sharedram = M6502ROM + 0x5000; // RAM+0x014000;

    if (is_current_game("metafox") || is_current_game("twineagl") || is_current_game("arbalest")) {
      memcpy(M6502ROM + 0x6000, load_region[REGION_CPU2], 0x2000);
      memcpy(M6502ROM + 0x8000, load_region[REGION_CPU2], 0x2000);
      memcpy(M6502ROM + 0xa000, load_region[REGION_CPU2], 0x2000);
      memcpy(M6502ROM + 0xc000, load_region[REGION_CPU2], 0x2000);
      memcpy(M6502ROM + 0xe000, load_region[REGION_CPU2], 0x2000);
    } else if (is_current_game("tndrcade")) {
      memcpy(M6502ROM + 0x6000, load_region[REGION_CPU2] + 0x2000, 0x6000);
      memcpy(M6502ROM + 0xc000, load_region[REGION_CPU2], 0x4000);
    } else {
      // downtown, usclssic, calibr50
      memcpy(M6502ROM + 0x7000, load_region[REGION_CPU2] + 0x3000, 0x5000);
      memcpy(M6502ROM + 0xc000, load_region[REGION_CPU2], 0x4000);
    }

    // Setup 6502 memory map
    // --------------------

    AddM6502AROMBase(M6502ROM);

    if (is_current_game("usclssic") || is_current_game("calibr50")) {
      AddM6502ARead(0x0000, 0x1fff, seta_sound_6502_r, NULL);
      AddM6502AWrite(0x0000, 0x1fff, seta_sound_6502_w, NULL);
      AddM6502ARead(0x4000,0x4000,NULL,&latch1);

      AddM6502AWrite(0x4000, 0x4000, sub_bankswitch, NULL);
      AddM6502AWrite(0xc000, 0xc000, calibr50_latch_w, NULL);

    } else {
       // AddM6502AWrite(0x5000, 0x57ff, NULL, sharedram);

       /* detailled memory map :
	  0-ff : zero page
	  100-1ff: ram
	  800 801 : sound latches (?)
	  1000-1006 : inputs
	  7000-ffff : rom (mirrored) */
       /*    AddM6502ARead(0x800,0x800, NULL, &latch1); */
       /*    AddM6502ARead(0x801,0x801, NULL, &latch2); */
       // AddM6502Read(0x8000, 0xbfff, NULL, NULL); // bank


       AddM6502AWrite(0x1000, 0x1000, sub_bankswitch, NULL);
       if (is_current_game("tndrcade")) {
	 // tndrcade uses shared ram, no sound latch
	 AddM6502ARead(0x2001,0x2001,YM2203_read_port_0_r,NULL);

	 AddM6502AWrite(0x2000, 0x2001, YM2203_w, NULL);
	 // AddM6502AWrite(0x2001, 0x2001, YM2203_write_port_0_w, NULL);

	 AddM6502AWrite(0x3000, 0x3001, YM3812_w, NULL);
	 // AddM6502AWrite(0x3001, 0x3001, YM3812_write_port_0_w, NULL);
	 M6502ROM[0x800] = 0xff;
       }
       AddM6502AWrite(0x0000, 0x57ff, NULL, M6502ROM);
     }
     AddM6502ARead(    -1,     -1, NULL,                        NULL);
     AddM6502AWriteByte(0xFFFC, 0xFFFC, StopM6502Mode2,             NULL);
     AddM6502AWriteByte(0x0000, 0xFFFF, DefBadWriteM6502,           NULL);
     AddM6502AWriteByte(    -1,     -1, NULL,                       NULL);

#ifdef RAINE_DEBUG
#endif
     AddM6502AInit();

     memset(M6502ROM+0x1000,0xff,0xa); // inputs for 6502 initialisation
     if (is_current_game("arbalest"))
       M6502ROM[0x1004] = 0; // stupid useless test for this game
   }

   /* ----------------------- */

   memset(RAM+0x00000,0x00,0xa000);

   // Speed Hack

   if (is_current_game("metafox")) {
     WriteWord(&ROM[0x00D0A],0x4EF8);
     WriteWord(&ROM[0x00D0C],0x0300);
     hack8(0x00300);
     WriteWord(&ROM[0x00308],0x6100-10);

     // Fix CP ERROR

     WriteWord(&ROM[0x8Ab1c],0x4E71);
     WriteWord(&ROM[0x8Ab1e],0x4E71);
     WriteWord(&ROM[0x8Ab20],0x4E71);
     min_y = 8;
   } else if (is_current_game("arbalest")) {
     WriteWord(&ROM[0x01088],0x4EF8);
     WriteWord(&ROM[0x0108a],0x0300);
     hack8(0x00300);
     WriteWord(&ROM[0x00308],0x6100-10);
   } else if (is_current_game("twineagl")) {
     hack8(0x04108);
     // disable rom check
     WriteWord(&ROM[0x33e],0x6000);
   } else if (is_current_game("thunderl") || is_current_game("wiggie")) {
     hack8(0x358);
   } else if (is_current_game("wits")) {
     // The whole game is in the irq, the main program just waits for the vbl !!!
     hack6(0x508);
   } else if (is_current_game("downtown")) {
     GameMouse = 1;
#if 0
     // I don't think this speed hack adds anything, and the game might accelerate at
     // places with it...
   } else if (is_current_game("tndrcade")) {
     hack6(0x10120);
     WriteWord(&ROM[0x10126],0x60f8);
     // disable rom check
     WriteWord(&ROM[0x56c],0x6000);
#endif
   } else if (is_current_game("umanclub")) {
     // The longest speed hack I ever made, a piece of courage...
     WriteWord(&ROM[0x444],0x4ef9); // No room in the normal program
     WriteWord(&ROM[0x446],0x3);
     WriteWord(&ROM[0x448],0xfff0);

     WriteWord(&ROM[0x3FFF0],0x52AD); // copy overwriten code
     WriteWord(&ROM[0x3FFF2],0x052C); // (is it usefull ???)
     WriteWord(&ROM[0x3FFF4],0x526D);
     WriteWord(&ROM[0x3FFF6],0x084E);

     hack6(0x3fff8);
     WriteWord(&ROM[0x3fffe],0x6100-16); // and loop
   } else if (is_current_game("neobattl")) {
     hack6(0x4a4);
   }

   if (is_current_game("usclssic")) {
     InitPaletteMap(RAM_PAL, 0x40, 0x10, 0x8000);
     memcpy(RAM_PAL+0x400, load_region[REGION_PROMS], 0x400);
   } else
     InitPaletteMap(RAM_PAL, 0x20, 0x10, 0x8000);

   if (is_current_game("thunderl") || is_current_game("wits") || is_current_game("wiggie")) {
     AddRWBW(0xe04000, 0xe07FFF, NULL, RAM+0x1a000);			// 68000 RAM
     AddRWBW(0xffc000, 0xfffFFF, NULL, RAM+0x1a000+0x4000);		// 68000 RAM
     AddRWBW(0xc00000, 0xc00001, NULL, RAM+0x1a000+0x8000);		// ???
     AddReadBW(0xb00000,0xb0000d, NULL, &input_buffer[2]); // inputs, dsw and protection
     if (is_current_game("wiggie"))
       AddWriteByte(0xB00008, 0xB00008, sound_wiggielatch_w, NULL);
     WriteWord(&input_buffer[0xc+2],0x00dd);
   } else if (is_current_game("umanclub") || is_current_game("neobattl")) {
     AddRWBW(0x200000, 0x20ffff, NULL, RAM+0x1a000);
     AddRWBW(0x300000, 0x3003ff, NULL, RAM_PAL);
     AddRWBW(0x300400, 0x300fff, NULL, RAM+0x1a000+0x10000);
     AddReadBW(0x400000,0x400005, NULL, &input_buffer[2]); // inputs, dsw and protection
     AddRWBW(0xa00000, 0xa00607, NULL, RAM_SPR);			// sprites y
     AddRWBW(0xb00000, 0xb03FFF, NULL, RAM_SPR2);			// OBJECT RAM

     AddReadByte(0xc00000, 0xc03FFF, seta_sound_word_rb, NULL);
     AddReadWord(0xc00000, 0xc03FFF, seta_sound_word_r, NULL);
     AddWriteByte(0xc00000, 0xc03FFF, seta_sound_word_wb, NULL);
     AddWriteWord(0xc00000, 0xc03FFF, seta_sound_word_w, NULL);

     AddRWBW(0x500000, 0x50000F, NULL, RAM_CTRL);		// SCROLL RAM

     AddReadBW(0x600000, 0x600003, seta_dsw_r, NULL);
     AddRWBW(0xa80000, 0xa80001, NULL, RAM+0x1a000+0x11000); // ?

     AddWriteByte(0xAA0000, 0xAA0001, stop_68k, NULL);			// Trap Idle 68000

     memset(input_buffer,255,0x20);
     finish_conf_68000(0);
     return;
   } else if (is_current_game("usclssic")) {
     AddRWBW(0xFf0000, 0xFffFFF, NULL, RAM+0x1a000+0x30000);			// 68000 RAM
     AddRWBW(0x800000, 0x800607, NULL, RAM_SPR);			// sprites y
     AddRWBW(0xa00000, 0xa0000F, NULL, RAM_CTRL);		// SCROLL RAM

     AddRWBW(0xb00000, 0xb003FF, NULL, RAM_PAL);			// COLOUR RAM
     AddRWBW(0xc00000, 0xc03FFF, NULL, RAM_SPR2);			// OBJECT RAM
     AddRWBW(0xd00000, 0xd03FFF, NULL, RAM_BG0);			// BG0 RAM
     AddRWBW(0xd04000, 0xd04FFF, NULL, RAM+0x1a002);			// 68000 RAM
     AddRWBW(0xe00000, 0xe00FFF, NULL, RAM+0x2a002);			// 68000 RAM

     AddReadBW(0xb40000, 0xb40007, usclssic_trackball_xy_r, NULL);
     AddWriteBW(0xb40000, 0xb40007, usclssic_lockout_w, NULL);
     AddReadBW(0xb40010, 0xb40011, NULL, &input_buffer[4]); // coins
     AddWriteBW(0xb40010, 0xb40011, calibr50_soundlatch_w, NULL);
     AddReadBW(0xb40018, 0xb4001f, dsw_usclssic_r, NULL);

     AddRWBW(0x900000, 0x900001, NULL, RAM+0x1a000);		// ?
     finish_conf_68000(0);
     GameMouse = 1;
     return;
   } else if (is_current_game("calibr50")) {
     AddRWBW(0xFf0000, 0xFffFFF, NULL, RAM+0x1a000+0x30000);			// 68000 RAM
     AddRWBW(0xd00000, 0xd00607, NULL, RAM_SPR);			// sprites y
     AddRWBW(0x800000, 0x80000F, NULL, RAM_CTRL);		// SCROLL RAM
     AddRWBW(0x200000, 0x200FFF, NULL, RAM+0x2a002);			// 68000 RAM

     AddReadBW(0xa00000,0xa00019, NULL, M6502ROM + 0x2000); // inputs
     memset(M6502ROM + 0x2000,0xff,0x20);
     AddRWBW  (0x904000,0x904fff, NULL, M6502ROM + 0x2020); // ram ?
     AddRWBW  (0xc00000,0xc00001, NULL, M6502ROM + 0x3020); // ram ?
     AddWriteBW(0xb00000, 0xb00001, calibr50_soundlatch_w, NULL);
     AddReadBW(0xb00000, 0xb00001, NULL, (UINT8*)&latch2);
     GameMouse = 1;
   } else if (is_current_game("tndrcade")) {
     AddRWBW(0xFfc000, 0xFffFFF, NULL, RAM+0x1a000);			// 68000 RAM
     AddRWBW(0xe00000, 0xe03fFF, NULL, RAM+0x1a000);			// 68000 RAM mirror
     AddRWBW(0x400000, 0x400001, NULL, RAM+0x1a000+0x4000);			// 68000 RAM mirror

     AddRWBW(0x380000, 0x3803FF, NULL, RAM_PAL);			// COLOUR RAM
     AddRWBW(0x600000, 0x600607, NULL, RAM_SPR);			// sprites y
     AddReadBW(0xa00000, 0xa00FFF, sharedram_68000_r, NULL);
     AddWriteBW(0xa00000, 0xa00FFF, sharedram_68000_w, NULL);
     AddRWBW(0xc00000, 0xc03FFF, NULL, RAM_SPR2);			// OBJECT RAM
     AddWriteBW(0x800000, 0x800007, sub_ctrl_w, NULL);
     AddWriteByte(0xAA0000, 0xAA0001, stop_68k, NULL);			// Trap Idle 68000
     finish_conf_68000(0);
     min_y = 8;
     return;
   } else {
     // metafox, twineagl and downtown, arbalest
     AddRWBW(0xF00000, 0xFffFFF, NULL, RAM+0x1a000);			// 68000 RAM
     AddReadBW(0xB00000, 0xB00FFF, sharedram_68000_r, NULL);
     AddWriteBW(0xB00000, 0xB00FFF, sharedram_68000_w, NULL);
   }

   AddRWBW(0x900000, 0x903FFF, NULL, RAM_BG0);			// BG0 RAM
   AddRWBW(0xD00000, 0xD00FFF, NULL, RAM_SPR);			// sprites y
   AddRWBW(0xE00000, 0xE03FFF, NULL, RAM_SPR2);			// OBJECT RAM

   AddRWBW(0x700000, 0x7003FF, NULL, RAM_PAL);			// COLOUR RAM
   AddRWBW(0x800000, 0x80000F, NULL, RAM_CTRL);		// SCROLL RAM
   if (is_current_game("twineagl")) {
     AddRWBW(0x200100,0x20010f, NULL, RAM_PAL + 0x400);
   }
   if (!is_current_game("calibr50")) {
     AddReadByte(0x100000, 0x103FFF, seta_sound_word_rb, NULL);
     AddReadWord(0x100000, 0x103FFF, seta_sound_word_r, NULL);
     AddWriteByte(0x100000, 0x103FFF, seta_sound_word_wb, NULL);
     AddWriteWord(0x100000, 0x103FFF, seta_sound_word_w, NULL);

     AddWriteBW(0xa00000, 0xa00007, sub_ctrl_w, NULL);

     AddReadByte(0x200000,0x2001ff, downtown_protection_rb, NULL);
     AddWriteBW(0x200000,0x2001ff, NULL, downtown_protection);

     AddRWBW(0x400000, 0x400007, NULL, (UINT8*)twineagl_tilebank);
   }

   AddReadBW(0x600000, 0x600003, seta_dsw_r, NULL);

   AddWriteByte(0xAA0000, 0xAA0001, stop_68k, NULL);			// Trap Idle 68000

   finish_conf_68000(0);
}

static void execute_arbalest(void)
{
  // As often the 68k is supposed to be a 8Mhz but the game seems to push it to its limits
  // at times, so it should be a little smoother at 12 MHz
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));
  m6502exec(CPU_FRAME_MHz(0.5,60));	// M6502 4MHz (60fps)
  m6502nmi();

  // cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(6,60));
  cpu_interrupt(CPU_68K_0, 3);

  m6502exec(CPU_FRAME_MHz(0.5,60));	// M6502 4MHz (60fps)
  print_debug("M6502_PC:%04x\n",m6502pc);
  m6502int(1);
}

static void execute_downtown(void)
{
  // char *line = NULL,prompt[80];
  // static int dump = 0;
  static int pos1, pos2;
  UINT8 *base = M6502ROM + 0x1000;
  int mx,my,dir1,dir2;
  GetMouseMickeys(&mx,&my);
  pos1 += mx;

#ifndef SDL
  if (*MouseB & 1) base[2] &= ~0x10;
  if (*MouseB & 2) base[2] &= ~0x20;
#endif

  if (!(base[7] & 1)) // rotate left
    pos1--;
  if (!(base[7] & 2)) // rotate right
    pos1++;
  if (!(base[7] & 4)) // rotate left
    pos2--;
  if (!(base[7] & 8)) // rotate right
    pos2++;
  while (pos1 < 0) pos1 += 256;
  while (pos1 > 255) pos1 -= 256;
  while (pos2 < 0) pos2 += 256;
  while (pos2 > 255) pos2 -= 256;

  // Thanks to mame for the formula to convert the absolute postion to values for the ports
  // I won't have to look for it then... (seems VERY complicated)

  dir1 = (~ (0x800 >> ((pos1 * 12)/0x100)) ) & 0xfff;
  dir2 = (~ (0x800 >> ((pos2 * 12)/0x100)) ) & 0xfff;

  base[0] = (base[0] & 0xf0) | (dir1 >> 8);
  base[1] = dir1 & 0xff;
  base[4] = dir2 >> 8;
  base[5] = dir2 & 0xff;

  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(4,60));
  cpu_interrupt(CPU_68K_0, 1);
  m6502nmi();
#if 1
  m6502exec(CPU_FRAME_MHz(0.8,60));	// M6502 4MHz (60fps)
#else
  if (cpu_frame_count < 380)
    m6502exec(CPU_FRAME_MHz(1.5,60));	// M6502 4MHz (60fps)
  else {
    int counter = 400;
  do {
    int oldpc = m6502pc, cycles = 1;
    if (--counter <= 0) break;
    if (counter == 200) {
      m6502int(1);
    }
    m6502GetContext(&M6502_context[0]);
/*     if (m6502pc >= 0x70bc && m6502pc <= 0x70c0) */
/*       dump = 1; */
    while (m6502pc == oldpc) {
      m6502exec(cycles);
      cycles++;
    }
    M6502_disp_context(0);
    sprintf(prompt,"%x ",m6502pc);
    if (dump)
      line = readline(prompt);
  } while (!line || line[0] != 'q');
  }
#endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(4,60));
   cpu_interrupt(CPU_68K_0, 2);

   // if (cpu_frame_count < 380) {
     m6502int(1);
     m6502exec(CPU_FRAME_MHz(0.8,60));	// M6502 4MHz (60fps)
     // }
     print_debug("M6502_PC:%04x %02x %02x\n",m6502pc,M6502ROM[m6502pc],M6502ROM[m6502pc+1]);
}

#define SLICES 16

static void execute_tndrcade() {
  // 68k irq 2, 6502 at 2 Mhz
  int n;
  m6502nmi();
  for (n=0; n<SLICES; n++) {
    cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60)/SLICES);

    m6502exec(CPU_FRAME_MHz(1.9,60)/SLICES);	// M6502 4MHz (60fps)
    print_debug("M6502_PC:%04x %02x %02x\n",m6502pc,M6502ROM[m6502pc],M6502ROM[m6502pc+1]);
    m6502int(1);
  }
  cpu_interrupt(CPU_68K_0, 2);
}

static void execute_thunderl(void)
{
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60)); // The test mode talks about 16Mhz?
  cpu_interrupt(CPU_68K_0, 2);
}

static void execute_wiggie(void)
{
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60)); // The test mode talks about 16Mhz?
  cpu_interrupt(CPU_68K_0, 2);
  cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));
}

static void execute_blandia(void)
{
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));
  cpu_interrupt(CPU_68K_0, 2);
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));
  cpu_interrupt(CPU_68K_0, 4);
}

static void execute_drgnunit(void)
{
  stopped_68k = 0;

  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));
  cpu_interrupt(CPU_68K_0, 1);

  if (!stopped_68k) {
    cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(32,60));
  }
  cpu_interrupt(CPU_68K_0, 2);
}

static void execute_zombraid(void)
{
  // irq 1 + 2 + the mouse
  int mx,my;

  UINT8 *pos = &input_buffer[13];
  GetMouseMickeys(&mx,&my);
  if (mx) mx = -mx;
  if (!(input_buffer[2] & 0x1))
    mx = -3;
  else if (!(input_buffer[2] & 0x2))
    mx = 3;
  if (!(input_buffer[2] & 0x4))
    my = -3;
  else if (!(input_buffer[2] & 0x8))
    my = 3;

  if (*pos + mx >= 0 && *pos + mx <= 255)
    *pos += mx;
  pos++;
  if (*pos + my >= 0 && *pos + my <= 255)
    *pos += my;
  pos++;

  mx = my = 0;
  if (!(input_buffer[4] & 0x1))
    mx = -3;
  else if (!(input_buffer[4] & 0x2))
    mx = 3;
  if (!(input_buffer[4] & 0x4))
    my = -3;
  else if (!(input_buffer[4] & 0x8))
    my = 3;

  if (*pos + mx >= 0 && *pos + mx <= 255)
    *pos += mx;
  pos++;
  if (*pos + my >= 0 && *pos + my <= 255)
    *pos += my;

#ifndef SDL
  if (*MouseB & 1) input_buffer[2] &= ~0x10;
  if (*MouseB & 2) input_buffer[2] &= ~0x20;
#endif

  stopped_68k = 0;

  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));
  cpu_interrupt(CPU_68K_0, 1);

  if (!stopped_68k) {
    cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(9,60));
    /* About the speed : the game seems to try to use more than these 17 Mhz at times
       especially during the fade outs on the screen. Well, I prefer to leave 17 Mhz
       the game is fast enough already !!!
       Even at 19 Mhz for this second execute_cycles the cpu does not enough time
       for some frames !!!
    */
  }
  cpu_interrupt(CPU_68K_0, 2);
}

static void execute_umanclub() {
  // The 64 Mhz are necessary to be sure that the whole frame is executed all the time...
  // Need a speed hack for all the games which use this frame.
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(64,60));
  cpu_interrupt(CPU_68K_0, 3);
}

static void execute_usclssic(void)
{
  int mx,my;
  GetMouseMickeys(&mx,&my);
  mx *= 2; my *= 2;
  if (!(input_buffer[8] & 0x1))
    mx = -20;
  else if (!(input_buffer[8] & 0x2))
    mx = 20;
  if (!(input_buffer[8] & 0x4))
      my = -20;
  else if (!(input_buffer[8] & 0x8))
    my = 20;
  WriteWord(&input_buffer[0],mx & 0xfff);
  WriteWord(&input_buffer[2],(ReadWord(&input_buffer[2]) & 0xf000) | (my & 0xfff));

#ifndef SDL
  if (*MouseB & 1) input_buffer[3] |= 0x20;
#endif

  for (mx=0; mx<5; mx++) {
    cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60)/5);
    if (mx < 4)
      cpu_interrupt(CPU_68K_0, 4);
    else
      cpu_interrupt(CPU_68K_0, 2);
    m6502exec(CPU_FRAME_MHz(2,60)/5);
  }
  print_debug("M6502_PC:%04x\n",m6502pc);
  m6502int(1);
}

static void execute_calibr50(void)
{
  int mx,my,n;
  static int pos1,pos2;
  UINT8 *base = RAM+0xc001;
  GetMouseMickeys(&mx,&my);
  // Same handling as downtown, almost (except the final formula)
  pos1 += mx;
  if (!(*base & 0x1))
    pos1--;
  else if (!(*base & 0x2))
    pos1++;
  if (!(*base & 0x4))
    pos2--;
  else if (!(*base & 0x8))
    pos2++;

  while (pos1 < 0) pos1 += 256;
  while (pos1 > 255) pos1 -= 256;
  while (pos2 < 0) pos2 += 256;
  while (pos2 > 255) pos2 -= 256;

  base[0xf] = pos1 & 0xff;
  base[0x11] = pos1 >> 8;
  base[0x13] = pos2 & 0xff;
  base[0x15] = pos2 >> 8;

#ifndef SDL
  if (*MouseB & 1) base[-1] &= ~0x10;
  if (*MouseB & 2) base[-1] &= ~0x20;
#endif

  // 6502 : 4 irqs, 68000 : irq 4 & 2
  // calibr50 was made for an 8 Mhz cpu, if you increase the frequency, then the game
  // accelerates !
  for (n=0; n<4; n++) {
    m6502exec(CPU_FRAME_MHz(2,60)/4);
    print_debug("M6502_PC:%04x\n",m6502pc);
    m6502int(1);

    cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60)/4); // normal frame
    if (n == 2)
      cpu_interrupt(CPU_68K_0, 4);
    else if (n == 3)
      cpu_interrupt(CPU_68K_0, 2);
  }
}
























static struct VIDEO_INFO video_arbalest =
{
   draw_metafox,
   384,
   224,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   downtown_gfxdecodeinfo,
};
static struct VIDEO_INFO video_blandia =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   blandia_gfxdecodeinfo,
};
static struct VIDEO_INFO video_drgnunit =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   downtown_gfxdecodeinfo,
};
static struct VIDEO_INFO video_eightfrc =
{
   draw_blandia,
   384,
   224,
   16,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   msgundam_gfxdecodeinfo,
};
static struct VIDEO_INFO video_gundhara =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   jjsquawk_gfxdecodeinfo,
};
static struct VIDEO_INFO video_jjsquawk =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   jjsquawk_gfxdecodeinfo,
};
static struct VIDEO_INFO video_msgundam =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   msgundam_gfxdecodeinfo,
};
static struct VIDEO_INFO video_neobattl =
{
   draw_metafox,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   downtown_gfxdecodeinfo,
};
static struct VIDEO_INFO video_stg =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   downtown_gfxdecodeinfo,
};
static struct VIDEO_INFO video_umanclub =
{
   draw_metafox,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   downtown_gfxdecodeinfo,
};
static struct VIDEO_INFO video_usclssic =
{
  draw_usclssic, // very strange color mapping !!!
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   usclssic_gfxdecodeinfo,
};
static struct VIDEO_INFO video_wiggie =
{
   draw_metafox,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   wiggie_gfxdecodeinfo
};
static struct VIDEO_INFO video_wrofaero =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   msgundam_gfxdecodeinfo,
};
static struct VIDEO_INFO video_zingzip =
{
   draw_blandia,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   zingzip_gfxdecodeinfo,
};
GMEI( arbalest, "Arbalester", SETA, 1989, GAME_SHOOT);
static struct DIR_INFO dir_blandia[] =
{
  { "blandia" },
  { NULL }
};
GAME( blandia, "Blandia", ALLUMER, 1992, GAME_BEAT,
	.input = input_blandia,
	.dsw = dsw_blandia,
	.video = &video_blandia,
	.exec = execute_blandia,
);
static struct DIR_INFO dir_calibr50[] =
{
  { "calibr50" },
  { NULL }
};
CLNE( calibr50, arbalest, "Caliber 50",  SETA, /* depends on the license / country */
       	1989, GAME_SHOOT,
	.input = input_calibr50,
	.dsw = dsw_calibr50,
	.video = &video_neobattl,
	.exec = execute_calibr50,
);
static struct DIR_INFO dir_daioh[] =
  {
    { "daioh" },
   { NULL, },
  };
CLNE( daioh, blandia, "Daioh", ATHENA, 1993, GAME_SHOOT,
	.dsw = dsw_daioh,
	.video = &video_wrofaero,
	.exec = execute_drgnunit,
);
static struct DIR_INFO dir_downtown[] =
{
  { "downtown" },
  { NULL }
};
CLNE( downtown, arbalest, "DownTown", SETA, 1989, GAME_BEAT,
	.input = input_downtown,
	.dsw = dsw_downtown,
	.video = &video_neobattl,
	.exec = execute_downtown,
	.sound = sound_downtown,
);
static struct DIR_INFO dir_drgnunit[] =
  {
    { "drgnunit", },
    { NULL, },
  };
CLNE( drgnunit, blandia, "Dragon Unit / Castle of Dragon", SETA, 1989, GAME_MISC,
	.dsw = dsw_drgnunit,
	.video = &video_drgnunit,
	.exec = execute_drgnunit,
);
static struct DIR_INFO dir_eightfrc[] =
{
  { "eightfrc" },
  { NULL }
};
CLNE( eightfrc, blandia, "Eight Forces", TECMO, 1994, GAME_BEAT,
	.dsw = dsw_eightfrc,
	.video = &video_eightfrc,
	.exec = execute_drgnunit,
);
static struct DIR_INFO dir_gundhara[] =
{
  { "gundhara" },
  { NULL }
};
CLNE( gundhara, blandia, "Gundhara", BANPREST, 1995, GAME_SHOOT,
	.dsw = dsw_gundhara,
	.video = &video_gundhara,
);
static struct DIR_INFO dir_jjsquawk[] =
{
  { "jjsquawk" },
  { NULL }
};
CLNE( jjsquawk, blandia, "J. J. Squawkers", ATHENA, 1993, GAME_PLATFORM,
	.dsw = dsw_jjsquawk,
	.video = &video_jjsquawk,
	.exec = execute_drgnunit,
);
static struct DIR_INFO dir_metafox[] =
{
   { "meta_fox", },
   { "metafox", },
   { NULL, },
};
CLNE( metafox, arbalest, "Meta Fox", SETA, 1989, GAME_SHOOT,
	.dsw = dsw_metafox,
);
static struct DIR_INFO dir_msgundam[] =
  {
    { "msgundam" },
   { NULL, },
  };
CLNE( msgundam, blandia, "Mobile Suit Gundam", BANPREST, 1993, GAME_SHOOT,
	.dsw = dsw_msgundam,
	.video = &video_msgundam,
);
static struct DIR_INFO dir_neobattl[] =
  {
    { "neobattl" },
   { NULL, },
  };
CLNE( neobattl, arbalest, "SD Gundam Neo Battling (Japan)", BANPREST, 1992, GAME_BEAT,
	.input = input_blandia,
	.dsw = dsw_neobattl,
	.video = &video_neobattl,
	.exec = execute_umanclub,
);
static struct DIR_INFO dir_rezon[] =
{
  { "rezon" },
  { NULL }
};
CLNE( rezon, blandia, "Rezon", ALLUMER, 1991, GAME_SHOOT,
	.dsw = dsw_rezon,
	.video = &video_msgundam,
	.exec = execute_umanclub,
);
static struct DIR_INFO dir_stg[] =
  {
    { "stg" },
   { NULL, },
  };
CLNE( stg, blandia, "Strike Gunner S.T.G", SETA, 1989, GAME_MISC,
	.dsw = dsw_stg,
	.video = &video_stg,
	.exec = execute_drgnunit,
);
static struct DIR_INFO dir_thunderl[] =
{
  { "thunderl" },
  { NULL }
};
CLNE( thunderl, arbalest, "Thunder & Lightning", SETA, 1989, GAME_BREAKOUT,
	.input = input_blandia,
	.dsw = dsw_thunderl,
	.video = &video_neobattl,
	.exec = execute_thunderl,
);
static struct DIR_INFO dir_tndrcade[] =
  {
    {"tndrcade",},
    {NULL,},
  };
CLNE( tndrcade, arbalest, "Thundercade / Twin Formation", SETA, 1987, GAME_SHOOT,
	.input = input_tndrcade,
	.dsw = dsw_tndrcade,
	.exec = execute_tndrcade,
	.sound = sound_tndrcade,
);
static struct DIR_INFO dir_twineagl[] =
{
   { "twin_eagle", },
   { "twineagl", },
   { NULL, },
};
CLNE( twineagl, arbalest, "Twin Eagle", SETA, 1990, GAME_SHOOT,
	.input = input_tndrcade,
	.dsw = dsw_twineagl,
	.video = &video_neobattl,
);
static struct DIR_INFO dir_umanclub[] =
  {
    { "umanclub" },
   { NULL, },
  };
CLNE( umanclub, arbalest, "Ultraman Club - Tatakae! Ultraman Kyoudai!!", BANPREST, 1992, GAME_BEAT,
	.input = input_blandia,
	.dsw = dsw_umanclub,
	.video = &video_umanclub,
	.exec = execute_umanclub,
);
static struct DIR_INFO dir_usclssic[] =
{
   { "us_classic_golf", },
   { "usclssic", },
   { NULL, },
};
CLNE( usclssic, arbalest, "US Classic Golf", SETA, 1989, GAME_SPORTS,
	.input = input_usclssic,
	.dsw = dsw_usclssic,
	.video = &video_usclssic,
	.exec = execute_usclssic,
);
static struct DIR_INFO dir_wiggie[] =
  {
    { "wiggie" },
   { NULL, },
  };
CLNE( wiggie, arbalest, "Wiggie Waggie", BOOTLEG, 1994, GAME_BREAKOUT,
	.input = input_blandia,
	.dsw = dsw_thunderl,
	.video = &video_wiggie,
	.exec = execute_wiggie,
	.sound = sound_wiggie,
);
static struct DIR_INFO dir_wits[] =
{
  { "wits" },
  { NULL }
};
CLNE( wits, arbalest, "Wit's (Japan)", VISCO, 1989, GAME_MISC,
	.input = input_blandia,
	.dsw = dsw_wits,
	.video = &video_umanclub,
	.exec = execute_thunderl,
);
static struct DIR_INFO dir_wrofaero[] =
{
  { "wrofaero" },
  { NULL }
};
CLNE( wrofaero, blandia, "War of Aero - Project MEIOU", YANG_CHENG, 1993, GAME_MISC,
	.dsw = dsw_wrofaero,
	.video = &video_wrofaero,
);
static struct DIR_INFO dir_zingzip[] =
{
   { "zing_zing_zip", },
   { "zingzip", },
   { NULL, },
};
CLNE( zingzip, blandia, "Zing Zing Zip", ALLUMER, 1992, GAME_MISC,
	.dsw = dsw_zingzip,
	.video = &video_zingzip,
	.exec = execute_umanclub,
);
static struct DIR_INFO dir_zombraid[] =
{
  { "zombraid" },
  { NULL }
};
CLNE( zombraid, blandia, "Zombie Raid (US)", SAMMY, 1995, GAME_SHOOT,
	.dsw = dsw_zombraid,
	.video = &video_jjsquawk,
	.exec = execute_zombraid,
);

