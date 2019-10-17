#define DRV_DEF_SOUND sound_puckman
// Pengo driver, taken from mame. Here are the comments in the mame driver :
// Warning : it's adviced to use 44Khz for sound for this one.
/* Raine notes : This driver is really full of tricks.
   There is the rom encryption, which looks like kabuki (qsound), but in worse
   because it also executes code in ram (!), then there is the lookup table for
   colors which allows the game to change the transparency color on the fly
   (!), only partially emulated but I didn't find a place where it's a problem,
   and there is also 2 layouts / region, applied manually */

/* Added pacman games to this driver too, they are much easier to emulate than
 * pengo */
/* About the million of clones supported by mame : I have included those I
 * found to
   be the most interesting ones : puckman because it's the parent of pacman
   (required), pacplus because it's much harder than pacman, mspacman because
   it's the parent of mspacmab, and that's all. Really I prefer to let mame
   emulate the others, they are either uninteresting (some are only the same
   game with the speed cheat enabled in the dipswitches) or completely
   different games which really look and sound horrible nowdays. Interestingly
   pacman still looks and sounds interesting 20 years after its creation. I
   guess that's where you recognize a master piece.

   Added multi15 finally, which includes 24 clones/hacks of pacman.
   I added it very cleanly : if you reset the game, it returns to the menu so that
   you can choose another game, and when you choose a game, hiscores and history
   are reseted to adapt to the selected game. And of course you can also use
   savegames. It was an interesting exercice ! And I added this one because I was
   impressed by such a hack, 24 z80 games in only 1 rom, wow ! */

/***************************************************************************

	Sega Pengo

    driver by Nicola Salmoria

    Games supported:
		* Pengo

	Known issues:
		* none

****************************************************************************

	Pengo memory map (preliminary)

	driver by Nicola Salmoria

	0000-7fff ROM
	8000-83ff Video RAM
	8400-87ff Color RAM
	8800-8fff RAM

	memory mapped ports:

	read:
	9000      DSW1
	9040      DSW0
	9080      IN1
	90c0      IN0

	write:
	8ff2-8ffd 6 pairs of two bytes:
	          the first byte contains the sprite image number (bits 2-7), Y flip (bit 0),
			  X flip (bit 1); the second byte the color
	9005      sound voice 1 waveform (nibble)
	9011-9013 sound voice 1 frequency (nibble)
	9015      sound voice 1 volume (nibble)
	900a      sound voice 2 waveform (nibble)
	9016-9018 sound voice 2 frequency (nibble)
	901a      sound voice 2 volume (nibble)
	900f      sound voice 3 waveform (nibble)
	901b-901d sound voice 3 frequency (nibble)
	901f      sound voice 3 volume (nibble)
	9022-902d Sprite coordinates, x/y pairs for 6 sprites
	9040      interrupt enable
	9041      sound enable
	9042      palette bank selector
	9043      flip screen
	9044-9045 coin counters
	9046      color lookup table bank selector
	9047      character/sprite bank selector
	9070      watchdog reset

	Main clock: XTAL = 18.432 MHz
	Z80 Clock: XTAL/6 = 3.072 MHz
	Horizontal video frequency: HSYNC = XTAL/3/192/2 = 16 kHz
	Video frequency: VSYNC = HSYNC/132/2 = 60.606060 Hz
	VBlank duration: 1/VSYNC * (20/132) = 2500 us

***************************************************************************
There seems to be something weird with the colors : if you start a new game
some time before the first ghost appears, the colors of the level are different.
It happens at least is mspacmab and pacman25, maybe in others as well. And it
lasts only during the 1st life... Bug or feature ?
Issue confirmed, it happens also in the original hardware.

*/

#include "gameinc.h"
#include "sasound.h"
#include "namco.h"
#include "blit.h" // clear_game_screen
#include "decode.h"
#include "emudx.h"
#include "alpha.h"
#include "cpuid.h"
#include "emumain.h" // set_reset_function
#include "savegame.h"
#include "history.h"
#include "hiscore.h"
#ifdef SDL
#include "sdl/dialogs/messagebox.h"
#endif


static struct DSW_DATA dsw_data_pengo_2[] =
{
  { MSG_EXTRA_LIFE, 0x01, 2 },
  { "30000" , 0x00},
  { "50000" , 0x01},
  { MSG_DEMO_SOUND, 0x02, 2 },
  { MSG_OFF, 0x02},
  { MSG_ON, 0x00},
  { MSG_CABINET, 0x04, 2 },
  { MSG_UPRIGHT, 0x00},
  { MSG_TABLE, 0x04},
  { MSG_LIVES, 0x18, 4 },
  { "2" , 0x18},
  { "3" , 0x10},
  { "4" , 0x08},
  { "5" , 0x00},
  { _("Rack Test"),    0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x00},
  { MSG_DIFFICULTY, 0xc0, 4 },
  { _("Easy") , 0xc0},
  { _("Medium") , 0x80},
  { _("Hard") , 0x40},
  { _("Hardest") , 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_pengo_3[] =
{
  { MSG_COIN1, 0x0f, 16 },
  { MSG_4COIN_1PLAY, 0x00},
  { MSG_3COIN_1PLAY, 0x08},
  { MSG_2COIN_1PLAY, 0x04},
  { _("2 Coins/1 Credit 5/3") , 0x09},
  { _("2 Coins/1 Credit 4/3") , 0x05},
  { MSG_1COIN_1PLAY, 0x0c},
  { _("1 Coin/1 Credit 5/6") , 0x0d},
  { _("1 Coin/1 Credit 4/5") , 0x03},
  { _("1 Coin/1 Credit 2/3") , 0x0b},
  { MSG_1COIN_1PLAY, 0x02},
  { _("1 Coin/2 Credits 5/11") , 0x07},
  { _("1 Coin/2 Credits 4/9") , 0x0f},
  { MSG_1COIN_3PLAY, 0x0a},
  { MSG_1COIN_4PLAY, 0x06},
  { MSG_1COIN_5PLAY, 0x0e},
  { MSG_1COIN_6PLAY, 0x01},
  { MSG_COIN2, 0xf0, 16 },
  { MSG_4COIN_1PLAY, 0x00},
  { MSG_3COIN_1PLAY, 0x80},
  { MSG_2COIN_1PLAY, 0x40},
  { _("2 Coins/1 Credit 5/3") , 0x90},
  { _("2 Coins/1 Credit 4/3") , 0x50},
  { MSG_1COIN_1PLAY, 0xc0},
  { _("1 Coin/1 Credit 5/6") , 0xd0},
  { _("1 Coin/1 Credit 4/5") , 0x30},
  { _("1 Coin/1 Credit 2/3") , 0xb0},
  { MSG_1COIN_1PLAY, 0x20},
  { _("1 Coin/2 Credits 5/11") , 0x70},
  { _("1 Coin/2 Credits 4/9") , 0xf0},
  { MSG_1COIN_3PLAY, 0xa0},
  { MSG_1COIN_4PLAY, 0x60},
  { MSG_1COIN_5PLAY, 0xe0},
  { MSG_1COIN_6PLAY, 0x10},
  { NULL, 0}
};

static struct DSW_INFO dsw_pengo[] =
{
  { 4, 0xb0, dsw_data_pengo_2 },
  { 6, 0xcc, dsw_data_pengo_3 },
  { 0, 0, NULL }
};

static struct INPUT_INFO input_pengo[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( P1_DOWN, 0x00, 0x02 ),
  INP0( P1_LEFT, 0x00, 0x04 ),
  INP0( P1_RIGHT, 0x00, 0x08 ),

  INP0( COIN1, 0x00, 0x10 ),
  INP0( COIN2, 0x00, 0x20 ),
  INP0( COIN3, 0x00, 0x40 ),

  INP0( P1_B1, 0x00, 0x80 ),

  INP0( P2_UP, 0x02, 0x01 ),
  INP0( P2_DOWN, 0x02, 0x02 ),
  INP0( P2_LEFT, 0x02, 0x04 ),
  INP0( P2_RIGHT, 0x02, 0x08 ),

  INP0( TEST, 0x02, 0x10 ),
  INP0( P1_START, 0x02, 0x20 ),
  INP0( P2_START, 0x02, 0x40 ),
  INP0( P2_B1, 0x02, 0x80 ),
  END_INPUT
};

static struct ROM_INFO rom_pengo[] =
{
  { "ic8", 0x1000, 0xf37066a8 , REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "ic7", 0x1000, 0xbaf48143 , REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "ic15", 0x1000, 0xadf0eba0 , REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "ic14", 0x1000, 0xa086d60f , REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "ic21", 0x1000, 0xb72084ec , REGION_ROM1, 0x4000, LOAD_NORMAL },
  { "ic20", 0x1000, 0x94194a89 , REGION_ROM1, 0x5000, LOAD_NORMAL },
  { "ic32", 0x1000, 0xaf7b12c4 , REGION_ROM1, 0x6000, LOAD_NORMAL },
  { "ic31", 0x1000, 0x933950fe , REGION_ROM1, 0x7000, LOAD_NORMAL },

  { "ic92", 0x2000, 0xd7eec6cd , REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "ic105", 0x2000, 0x5bfd26e9 , REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "pr1633.078", 0x0020, 0x3a5844ec , REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "pr1634.088", 0x0400, 0x766b139b , REGION_PROMS, 0x0020, LOAD_NORMAL },
  { "pr1635.051", 0x0100, 0xc29dea27 , REGION_SMP1, 0x0000, LOAD_NORMAL },
  { "pr1636.070", 0x0100, 0x77245b66 , REGION_SMP1, 0x0100, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

// not encrypted
static struct ROM_INFO rom_pengo2u[] =
{
  { "pengo.u8", 0x1000, 0x3dfeb20e, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "pengo.u7", 0x1000, 0x1db341bd, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pengo.u15", 0x1000, 0x7c2842d5, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "pengo.u14", 0x1000, 0x6e3c1f2f, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "pengo.u21", 0x1000, 0x95f354ff, REGION_ROM1, 0x4000, LOAD_NORMAL },
  { "pengo.u20", 0x1000, 0x0fdb04b8, REGION_ROM1, 0x5000, LOAD_NORMAL },
  { "pengo.u32", 0x1000, 0xe5920728, REGION_ROM1, 0x6000, LOAD_NORMAL },
  { "pengo.u31", 0x1000, 0x13de47ed, REGION_ROM1, 0x7000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/******************************************************************************

  Sega encryption emulation                                 by Nicola Salmoria


  Several Sega Z80 games have program ROMs encrypted using a common algorithm
  (but with a different key).
  The hardware used to implement this encryption is either a custom CPU, or an
  epoxy block which probably contains a standard Z80 + PALs.

  You can think of the decryption algorithm as a black box which takes as
  input D3, D5, D7, M1, A0, A4, A8 and A12, and returns the decrypted D3, D5
  and D7. [Dn are the data lines, An the address lines, M1 is the Z80 pin which
  tells whether the CPU is accessing data or opcodes]. D0, D1, D3, D4 and D6
  are always unaffected.

  We can summarize that using a XOR mask laid out like this:

    0 1 2 3 4 5 6 7 8 9 a b c d e f
  0 A A A A A A A A B B B B B B B B
  1 A A A A A A A A B B B B B B B B
  2 C C C C C C C C D D D D D D D D
  3 C C C C C C C C D D D D D D D D
  4 A A A A A A A A B B B B B B B B
  5 A A A A A A A A B B B B B B B B
  6 C C C C C C C C D D D D D D D D
  7 C C C C C C C C D D D D D D D D
  8 D D D D D D D D C C C C C C C C
  9 D D D D D D D D C C C C C C C C
  a B B B B B B B B A A A A A A A A
  b B B B B B B B B A A A A A A A A
  c D D D D D D D D C C C C C C C C
  d D D D D D D D D C C C C C C C C
  e B B B B B B B B A A A A A A A A
  f B B B B B B B B A A A A A A A A

  on the left edge you have the most significant nibble of the data, on the top
  edge the least significant nibble. For example, if the input data is 0xc0, it
  will be XORed with D. As you can see, the table is symmetrical, so the 8
  possible combinations of D3, D5 and D7 only require 4 different XOR values.
  Since only D3, D5 and D7 are affected, A, B, C and D can have only these
  values: 0x00, 0x08, 0x20, 0x28, 0x80, 0x88, 0xa0, 0xa8.
  Another important thing to note is that A XOR B XOR C XOR D must always be 0;
  that is, it must cause a permutation. If that weren't the case, there would
  be values impossible to obtain.

  We need 32 of these tables, one for every possible combination of M1, A0, A4,
  A8 and A12. However, all the games currently known are full of repetitions
  and only use 6 different tables, the only exceptions being Pengo, Yamato and
  Spatter which have 7 (but one of them is { 0x00, 0x00, 0x00, 0x00 } ). This
  is most likely a limitation of the hardware.
  Some of the early games are even weaker: of the 6 different tables, they use
  3 for opcodes and 3 for data, and always coupled in the same way.

  In all games currently known, only bytes in the memory range 0x0000-0x7fff
  (A15 = 0) are encrypted. My guess is that this was done to allow games to
  copy code to RAM (in the memory range 0x8000-0xffff) and execute it from
  there without the CPU trying to decrypt it and messing everything up.
  However Zaxxon has RAM at 0x6000, and the CPU doesn't seem to interfere with
  it; but it doesn't execute code from there, so it's possible that the CPU is
  encrypting the data while writing it and decrypting it while reading (that
  would seem kind of strange though). Video and sprite RAM and memory mapped
  ports are all placed above 0x8000.

  Given its strict limitations, this encryption is reasonably easy to break,
  and very vulnerable to known plaintext attacks.

******************************************************************************/

static UINT8 *decoded;

static void sega_decode(const unsigned char xortable[32][4], UINT8 *dest)
{
  int A;
  unsigned char *rom = load_region[REGION_CPU1];

  for (A = 0x0000;A < 0x8000;A++)
    {
      int row,col;
      unsigned char src;


      src = rom[A];

      /* pick the translation table from bits 0, 4, 8 and 12 of the address */
      row = (A & 1) + (((A >> 4) & 1) << 1) + (((A >> 8) & 1) << 2) + (((A >> 12) & 1) << 3);

      /* pick the offset in the table from bits 3 and 5 of the source data */
      col = ((src >> 3) & 1) + (((src >> 5) & 1) << 1);
      /* the bottom half of the translation table is the mirror image of the top */
      if (src & 0x80) col = 3 - col;

      /* decode the opcodes */
      dest[A] = src ^ xortable[2*row][col];

      /* decode the data */
      rom[A] = src ^ xortable[2*row+1][col];

      if (xortable[2*row][col] == 0xff)	/* table incomplete! (for development) */
	dest[A] = 0x00;
      if (xortable[2*row+1][col] == 0xff)	/* table incomplete! (for development) */
	rom[A] = 0xee;
    }
  z80_offdata = rom - dest;
}

static void pengo_decode(void)
{
  static const unsigned char xortable[32][4] =
    {
      /*       opcode                   data                     address      */
      /*  A    B    C    D         A    B    C    D                           */
      { 0xa0,0x88,0x88,0xa0 }, { 0x28,0xa0,0x28,0xa0 },	/* ...0...0...0...0 */
      { 0x28,0xa0,0x28,0xa0 }, { 0xa0,0x88,0x88,0xa0 },	/* ...0...0...0...1 */
      { 0xa0,0x88,0x00,0x28 }, { 0xa0,0x88,0x00,0x28 },	/* ...0...0...1...0 */
      { 0x08,0x20,0xa8,0x80 }, { 0xa0,0x88,0x88,0xa0 },	/* ...0...0...1...1 */
      { 0x08,0x08,0xa8,0xa8 }, { 0x28,0xa0,0x28,0xa0 },	/* ...0...1...0...0 */
      { 0xa0,0x88,0x00,0x28 }, { 0x08,0x08,0xa8,0xa8 },	/* ...0...1...0...1 */
      { 0xa0,0x88,0x00,0x28 }, { 0xa0,0x88,0x00,0x28 },	/* ...0...1...1...0 */
      { 0xa0,0x88,0x00,0x28 }, { 0x00,0x00,0x00,0x00 },	/* ...0...1...1...1 */
      { 0x88,0x88,0x28,0x28 }, { 0xa0,0x88,0x00,0x28 },	/* ...1...0...0...0 */
      { 0x88,0x88,0x28,0x28 }, { 0x00,0x00,0x00,0x00 },	/* ...1...0...0...1 */
      { 0x08,0x20,0xa8,0x80 }, { 0x08,0x20,0xa8,0x80 },	/* ...1...0...1...0 */
      { 0xa0,0x88,0x88,0xa0 }, { 0xa0,0x88,0x00,0x28 },	/* ...1...0...1...1 */
      { 0x08,0x08,0xa8,0xa8 }, { 0x88,0x88,0x28,0x28 },	/* ...1...1...0...0 */
      { 0x00,0x00,0x00,0x00 }, { 0x88,0x88,0x28,0x28 },	/* ...1...1...0...1 */
      { 0x08,0x20,0xa8,0x80 }, { 0x08,0x20,0xa8,0x80 },	/* ...1...1...1...0 */
      { 0x08,0x08,0xa8,0xa8 }, { 0xa0,0x88,0x00,0x28 }	/* ...1...1...1...1 */
    };

  sega_decode(xortable,decoded);
}

static UINT8 input_port_3_r(UINT16 offset) {
  UINT8 res = input_buffer[6];
  return res;
}

static UINT8 input_port_2_r(UINT16 offset) {
  UINT8 res = input_buffer[4];
  return res;
}

static UINT8 input_port_1_r(UINT16 offset) {
  UINT8 res = input_buffer[2];
  return res;
}

static UINT8 input_port_0_r(UINT16 offset) {
  UINT8 res = input_buffer[0];
  return res;
}

static struct namco_interface namco_interface =
{
	3072000/32,
	3,			/* number of voices */
	255,		/* playback volume */
	REGION_SOUND1,	/* memory region */
};

static struct SOUND_INFO sound_puckman[] =
  {
   { SOUND_NAMCO, &namco_interface },
   { 0,             NULL,                 },
  };

static UINT8 *interrupt_enable,*gfx_bank,multipac_mode;

static gfx_layout tilelayout =
{
	8,8,	/* 8*8 characters */
    RGN_FRAC(1,2),    /* 256 characters */
    2,  /* 2 bits per pixel */
    { 0, 4 },   /* the two bitplanes for 4 pixels are packed into one byte */
    { 8*8+0, 8*8+1, 8*8+2, 8*8+3, 0, 1, 2, 3 }, /* bits are packed in groups of four */
    { 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
    16*8    /* every char takes 16 bytes */
};


static gfx_layout spritelayout =
{
	16,16,	/* 16*16 sprites */
	RGN_FRAC(1,2),	/* 64 sprites */
	2,	/* 2 bits per pixel */
	{ 0, 4 },	/* the two bitplanes for 4 pixels are packed into one byte */
	{ 8*8, 8*8+1, 8*8+2, 8*8+3, 16*8+0, 16*8+1, 16*8+2, 16*8+3,
			24*8+0, 24*8+1, 24*8+2, 24*8+3, 0, 1, 2, 3 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
			32*8, 33*8, 34*8, 35*8, 36*8, 37*8, 38*8, 39*8 },
	64*8	/* every sprite takes 64 bytes */
};

static UINT8 *colorram,*videoram,*spriteram,*spriteram_2,mypal[0x100*4];

static int layer_id_data[2];

static void dup_writes(UINT32 offset, UINT8 data) {
  ROM[offset] = data;
  RAM[offset] = data;
}

static UINT8 *copy_sprites(UINT8 *region) {
  // the sprites are starting at 0x1000, but after this they are continuing at the
  // begining of the region...
  UINT8 *dest = AllocateMem(0x2000);
  memcpy(dest, region + 0x1000, 0x1000);
  memcpy(dest + 0x1000, region, 0x1000);
  return dest;
}

static int tile_cache_init;

static void load_pengo() {
  UINT8 *color_prom = load_region[REGION_PROMS];
  UINT8 palette[32*2];
  int i;
  multipac_mode = 0;

  RAMSize = 0x1032+0x8000;

  if(!(RAM=AllocateMem(RAMSize))) return;

  if (!strcmp(current_game->main_name,"pengo")) {// normal
    if (!(decoded = AllocateMem(0x8000))) return;

    pengo_decode();
  } else {
    decoded = ROM;
  }
  memcpy(RAM,decoded,0x8000); // There is some code executed in ram
  // so rom and ram must be contiguous for this to work...
  if (z80_offdata) { // encrypted !
    // in this case, the data of the rom is fetched at a different place
    // so we must make sure opcodes and operands are updated together in ram
    // for this we will allocate a 2nd buffer for the ram and duplicate the writes
    // to the code region (ramrom)
    UINT8 *tmp = AllocateMem(0x9000);
    memcpy(tmp,ROM,0x8000);
    z80_offdata = tmp - RAM;
    FreeMem(ROM);
    ROM = tmp;
  }

  memset(RAM+0x8000,0x0,0x1031);

  gfx_bank = &RAM[0x8000+0x1030];
  interrupt_enable = RAM + 0x8000 + 0x1031;

  // 1st : the 2 gfx regions become 4 regions
  load_region[REGION_GFX3] = load_region[REGION_GFX2];
  load_region[REGION_GFX2] = copy_sprites(load_region[REGION_GFX1]);
  load_region[REGION_GFX4] = copy_sprites(load_region[REGION_GFX3]);

  // Z80 init, finally

  AddZ80AROMBase(RAM, 0x0038, 0x0066);
  AddZ80AReadByte(0x0000, 0x7fff, NULL, ROM);
  if (decoded != ROM) {
    AddZ80AWriteByte(0x8800, 0x8fef, dup_writes, NULL);
  }

  RAM += 0x8000; // points to the real RAM (the 0x8000 first bytes are a copy of the rom

  AddZ80AReadByte(0x8000, 0x8fff, NULL, RAM);

  videoram = RAM;
  colorram = RAM + 0x400;
  spriteram = RAM + 0xff0;

  set_pulse_time(2); // for the coin input

  AddZ80AReadByte(0x9000, 0x903f, input_port_3_r, NULL);
  AddZ80AReadByte(0x9040, 0x907f, input_port_2_r, NULL);
  AddZ80AReadByte(0x9080, 0x90bf, input_port_1_r, NULL);
  AddZ80AReadByte(0x90c0, 0x90ff, input_port_0_r, NULL);

  AddZ80AWriteByte(0x8000, 0x8fff, NULL, RAM);
  pengo_soundregs = RAM+0x1000;
  /* Very bad idea : pengo_sound_w write to pengo_soundregs and expects the game driver
     to allocate this memory. I leave it like this to preserve mame compatibility... */
  AddZ80AWriteByte(0x9000, 0x901f, pengo_sound_w, NULL); // namco.c (sound)
  spriteram_2 = RAM+0x1020;
  AddZ80AWriteByte(0x9020, 0x902f, NULL, spriteram_2); // sprite ram 2


  AddZ80AWriteByte(0x9040, 0x9040, NULL, interrupt_enable); // sprite ram 2
  AddZ80AWriteByte(0x9041, 0x9041, pengo_sound_enable_w, NULL); // namco.c
  // flip screen is at 9043, how usefull...
  AddZ80AWriteByte(0x9047, 0x9047, NULL, gfx_bank); // gfx bank

  // finish conf z80

   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();
   *interrupt_enable = 0;
   RAM -= 0x8000; // points to the ROM part again for dup_writes

   /* The palette from the color proms : argh ! */
   /* Apparently there are only 32 different colors at start !!! */

   for (i = 0;i < 32;i++) {
     int bit0,bit1,bit2,r,g,b;

     /* red component */
     bit0 = (*color_prom >> 0) & 0x01;
     bit1 = (*color_prom >> 1) & 0x01;
     bit2 = (*color_prom >> 2) & 0x01;
     // r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
     r = (bit2 << 2) | (bit1 << 1) | bit0;
     /* green component */
     bit0 = (*color_prom >> 3) & 0x01;
     bit1 = (*color_prom >> 4) & 0x01;
     bit2 = (*color_prom >> 5) & 0x01;
     // g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
     g = (bit2 << 2) | (bit1 << 1) | bit0;

     /* blue component */
     bit0 = 0;
     bit1 = (*color_prom >> 6) & 0x01;
     bit2 = (*color_prom >> 7) & 0x01;
     // b = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
     b = (bit2 << 2) | (bit1 << 1) | bit0;

     WriteWord(&palette[i*2],b + (g<<3) + (r<<6));
     color_prom++;
   }

   /* After this, it seems to be a list of colors (from 0 to f). */
   /* color_prom now points to the beginning of the lookup table */

   /* character lookup table */
   /* sprites use the same color lookup table as characters */
   for (i = 0;i < 0x80;i++)
     WriteWord(&mypal[i*2], ReadWord(&palette[(*(color_prom++) & 0x0f)*2]));

   color_prom += 0x80;

   /* second bank character lookup table */
   /* sprites use the same color lookup table as characters */
   for (i = 0;i < 0x80;i++)
     {
       if (*color_prom)
	 WriteWord(&mypal[0x80*2+i*2], ReadWord(&palette[((*(color_prom) & 0x0f)+0x10)*2]));
       // COLOR(2,i) = (*color_prom & 0x0f) + 0x10;	/* second palette bank */
       else
	 WriteWord(&mypal[0x80*2+i*2], 0);
       // COLOR(2,i) = 0;	/* preserve transparency */

       color_prom++;
     }

  InitPaletteMap(mypal, 0x40, 4, 0x200);
  set_colour_mapper(&col_map_xxxxRrrgggbbb);
  layer_id_data[0] = add_layer_info(gettext("BG"));
  layer_id_data[1] = add_layer_info(gettext("SPRITES"));
  tile_cache_init = 0;
}

extern UINT32 cpu_frame_count;
static int multipac_bank;

#ifdef RAINE_DEBUG
// Trigered by p1b2 in debug builds and in emudx mode
static void draw_debug_tile() {
  int offs;
  UINT8 *solid,*gfx;
  int bank,col_base;

  if (display_cfg.bpp > 16 || display_cfg.bpp < 15) {
    print_ingame(1,gettext("switch to 16bpp color depth and reload"));
    return;
  }

  if (!multipac_mode) {
    *gfx_bank &= 1;
    if (*gfx_bank) {
      col_base = 0x20;
    } else
      col_base = 0;
    bank = *gfx_bank * 2;
    gfx = load_region[REGION_GFX1 + bank];
  } else {
    col_base = 0;
    gfx = load_region[REGION_GFX1]+0x8000*(*gfx_bank);
  }

  if( check_layer_enabled(layer_id_data[0])) {
    // Tiles
    solid = gfx_solid[0+bank];
    clear_game_screen(0); // Here it's because of the debug info on the screen which
    // needs to be cleared between each frame

    for (offs=0x3ff; offs>0; offs--) {
      int mx,my,sx,sy;
      UINT8 code,*map;
      mx = offs & 0x1f;
      my = offs / 32;

      if (my < 2) {
	if (mx < 2 || mx >= 30) continue; /* not visible */
	sx = my + 34;
	sy = mx - 2;
      } else if (my >= 30) {
	if (mx < 2 || mx >= 30) continue; /* not visible */
	sx = my - 30;
	sy = mx - 2;
      } else {
	sx = mx + 2;
	sy = my - 2;
      }

      MAP_PALETTE_MAPPED_NEW(
			     col_base + (colorram[offs] & 0x1f),
			     4,
			     map
			     );

      sx=sx*16+16; sy=sy*16+16;
      code = videoram[offs];

/*       if ((input_buffer[8] & 1) && code != 0x40) */
      /* Tile approximation : starting at code d0 ? */
/*       if (code >= 0xd0 || code == 0x31) code = 0x40; */
      if (solid[code]) {
	char str[4];
	if (solid[code] == 1) // some transp
	  Draw8x8_Trans_Mapped_Rot(&gfx[code<<6],sx,sy,map); // 1 tile, transp
	else
	  Draw8x8_Mapped_Rot(&gfx[code<<6],sx,sy,map); // 1 tile, no transp
	sprintf(str,"%02x",code);
	textout_fast(str,448+24-sy,sx+8,get_white_pen());
	sprintf(str,"%x",(colorram[offs] & 0x1f) >> 1);
	textout_fast(str,448+24-sy+8,sx,get_white_pen());
      }
    }
  } else
   clear_game_screen(0);
}
#endif

static void draw_pengo() {
  int offs;
  UINT8 *map,*gfx,*solid,*gfx_spr;
  int bank,col_base;
  if (!tile_cache_init) {
    init_tile_cache();
    tile_cache_init = 1;
  }

  if (!multipac_mode) {
    *gfx_bank &= 1;
    if (*gfx_bank) {
      col_base = 0x20;
    } else
      col_base = 0;
    bank = *gfx_bank * 2;
    gfx = load_region[REGION_GFX1 + bank];
    gfx_spr = load_region[REGION_GFX2 + bank];
    solid = gfx_solid[1 + bank];
  } else {
    if (*gfx_bank == 3) // super pacman
      col_base = 0x20;
    else if (*gfx_bank == 13) // crush roller
      col_base = 0x40;
    else if (*gfx_bank == 14) // liz wiz
      col_base = 0x60;
    else
      col_base = 0;
    if (0x8000 * (*gfx_bank) >= get_region_size(REGION_GFX1)) {
      gfx = load_region[REGION_GFX1];
      gfx_spr = load_region[REGION_GFX2]+0x4000;
      solid = gfx_solid[1]+0x4000/0x100;
    } else {
      gfx = load_region[REGION_GFX1]+0x8000*(*gfx_bank);
      gfx_spr = load_region[REGION_GFX2]+0x8000*(*gfx_bank)+0x4000;
      solid = gfx_solid[1] + 0x8000/0x100*(*gfx_bank)+0x4000/0x100;
    }
  }

  if( check_layer_enabled(layer_id_data[0])) {
    // Tiles
    clear_tile_cache();

    for (offs=0x3ff; offs>0; offs--) {
      int mx,my,sx,sy;
      UINT8 code;
      mx = offs & 0x1f;
      my = offs / 32;

      if (my < 2) {
	if (mx < 2 || mx >= 30) continue; /* not visible */
	sx = my + 34;
	sy = mx - 2;
      } else if (my >= 30) {
	if (mx < 2 || mx >= 30) continue; /* not visible */
	sx = my - 30;
	sy = mx - 2;
      } else {
	sx = mx + 2;
	sy = my - 2;
      }

      MAP_PALETTE_MAPPED_NEW(
			     col_base + (colorram[offs] & 0x1f),
			     4,
			     map
			     );

      sx=sx*8+16; sy=sy*8+16;
      code = videoram[offs];

      /* Tile approximation : starting at code d0 ? */
      if ((tile_cache[code]) && (cache_map[code] == map)) {
	Move8x8_Rot(tile_cache[code],sx,sy,NULL);
      } else {
	Draw8x8_Mapped_Rot(&gfx[code<<6],sx,sy,map); // 1 tile, no transp
	add_tile_cache_Rot(NULL,sx,sy,code);
	cache_map[code] = map;
      }
    }
  } else
   clear_game_screen(0);

  if( check_layer_enabled(layer_id_data[1])) {
    /* Draw the sprites. Note that it is important to draw them exactly in this */
    /* order, to have the correct priorities. */

  /* There is a problem with the sprites transparency : the colors are taken from a
     lookup table and not directly and color 0 in the lookup table is transparent.
     In raine, I emulate this by writing bank palettes which use the lookup table to
     map the colors. The problem is that we can't handle transparency like this.
     Transparency seems used only to write 1 sprite over 1 over.
     Example of this is sprite 2b (when pengoo is caught) : the game assigns bank 0 to
     the sprite of the bee, making it this way completely transparant.
     We can't emulate this transparency, so I just do not draw sprites with bank 0 */

    for (offs = 16 - 2;offs > 2*2;offs -= 2) {
      int sx,sy;

      sx = 272 - spriteram_2[offs + 1]+16;
      sy = spriteram_2[offs] - 31+16;
      if (sx >= 0 && sy >= 0 && sx <= 288 && sy <= 224) {
	UINT8 ta = spriteram[offs] >> 2;
	UINT8 coul = (spriteram[offs+1] & 0x1f);
	if (!coul) continue; // bank 0 is "all the colors transparent"

	MAP_PALETTE_MAPPED_NEW(
			       col_base + (spriteram[offs+1] & 0x1f),
			       4,
			       map
			       );
	ta &= 0x3f;
	/* Emudx emulation sprite tile = code + $c2 (to confirm) */
	if (solid[ta]) {
	  if (solid[ta] == 1) // some transp
	    Draw16x16_Trans_Mapped_flip_Rot(&gfx_spr[ta<<8],sx,sy,map,spriteram[offs] & 3);
	  else
	    // All solid, must be rather rare, I think...
	    Draw16x16_Mapped_flip_Rot(&gfx_spr[ta<<8],sx,sy,map,spriteram[offs] & 3);
	}
      }
    }

    for (offs = 2*2;offs >= 0;offs -= 2) {
      int sx,sy;


      sx = 272 - spriteram_2[offs + 1]+16;
      sy = spriteram_2[offs] - 31+16;
      if (sx >= 0 && sy >= 0 && sx <= 288 && sy <= 224) {
	UINT8 ta = spriteram[offs] >> 2;
	UINT8 coul = (spriteram[offs+1] & 0x1f);
	if (!coul) continue; // bank 0 is "all the colors transparent"

	MAP_PALETTE_MAPPED_NEW(
			       col_base + coul,
			       4,
			       map
			       );
	ta &= 0x3f;
	if (solid[ta]) {
	  if (solid[ta] == 1) // some transp
	    Draw16x16_Trans_Mapped_flip_Rot(&gfx_spr[ta<<8],sx,sy,map,spriteram[offs] & 3);
	  else
	    // All solid, must be rather rare, I think...
	    Draw16x16_Mapped_flip_Rot(&gfx_spr[ta<<8],sx,sy,map,spriteram[offs] & 3);
	}
      }
    }
  }
}

static int draw_emudx_tile;

/* static void disp_sprite(int sx, int sy, int ta,int coul) { */
/* } */

/* ta >= 8 is not sure, it's to display the fruit bonuses */
/* I am not even sure anymore the sprites between 8 and f are affected by colours */
/* ta between 1c and 1d is for the flashing ghosts from blue to white */
/* 1e..28 is mainly for the ghosts with their normal 4 colors. there are 4 unknown
   sprites here since there are 14 sprites / bank in the dx files and I have only 10
   here. */
#define conv_sprite(ta, coul)				\
  if ((coul) && ta >= 8) {				\
  if (ta>=0x1e && ta<0x28) ta += 24 + (coul)*14;	\
  else if (ta <= 0xf || (ta>=0x1c && ta<=0x1d)) {	\
     ta += 22+(coul)*14;					\
  }							\
}

static int mspacman,use_alpha,inc_alpha;

#define draw_ghost(sx,sy,sprite,flip)                               \
  if (bpp == 1) {                                                   \
      if ((input_buffer[8] & 0x10)) {                               \
          /* mmx alpha blending ? */                                \
          Draw32x32_Trans_Alpha_16_flip_Rot(sprite,sx,sy,0,flip);   \
      } else if (bpp == 1 && (input_buffer[8] & 0x20)) {            \
          /* 50% alpha blending ? */                                \
          Draw32x32_Trans_Alpha50_16_flip_Rot(sprite,sx,sy,0,flip); \
      } else {                                                      \
          Draw32x32_Trans_flip_Rot(sprite,sx,sy,0,flip);            \
      }                                                             \
  } else if (bpp == 2) {                                            \
      if ((input_buffer[8] & 0x10)) {                               \
          /* mmx alpha blending ? */                                \
          Draw32x32_Trans_Alpha_32_flip_Rot(sprite,sx,sy,0,flip);   \
      } else if (bpp == 1 && (input_buffer[8] & 0x20)) {            \
          /* 50% alpha blending ? */                                \
          Draw32x32_Trans_Alpha50_32_flip_Rot(sprite,sx,sy,0,flip); \
      } else {                                                      \
          Draw32x32_Trans_flip_Rot(sprite,sx,sy,0,flip);            \
      }                                                             \
  }

static void draw_emudx() {
  int offs;
  UINT8 *solid;
  int bank,col_base;
  static int bpp;

  if (RefreshBuffers) {
      bpp = display_cfg.bpp / 16;
  }

#ifdef RAINE_DEBUG
  if (input_buffer[8] & 8) {
    draw_debug_tile();
    return;
  }
#endif

  *gfx_bank &= 1;
  if (*gfx_bank) {
    col_base = 0x20;
  } else
    col_base = 0;
  bank = *gfx_bank * 2;

  if( check_layer_enabled(layer_id_data[0])) {
    // Tiles
    solid = gfx_solid[0+bank];
    if (draw_emudx_tile) {
      if (mspacman) {
	int level = RAM[0xe13];
	if (level <= 1) { // 1st 2 levels
	  blit(emudx_tiles[0], GameBitmap, 0, 0, 16, 16, 448, 576);
	} else if (level <= 4) {
	  blit(emudx_tiles[1], GameBitmap, 0, 0, 16, 16, 448, 576); // 3 times
	} else {
	  level = ((level - 5) / 4) & 1;
	  blit(emudx_tiles[2+level], GameBitmap, 0, 0, 16, 16, 448, 576);
	}
      } else
	blit(emudx_tiles[(RAM[0xe13]%10)], GameBitmap, 0, 0, 16, 16, 448, 576);

      draw_emudx_tile = 0;
    } else {
      clear_game_screen(0); // we NEED to do this because most layers have been
      // prepared with the transparent color (too bad !).
    }

    for (offs=0x3ff; offs>0; offs--) {
      int mx,my,sx,sy;
      UINT8 code;
      mx = offs & 0x1f;
      my = offs / 32;

      if (my < 2) {
	if (mx < 2 || mx >= 30) continue; /* not visible */
	sx = my + 34;
	sy = mx - 2;
      } else if (my >= 30) {
	if (mx < 2 || mx >= 30) continue; /* not visible */
	sx = my - 30;
	sy = mx - 2;
      } else {
	sx = mx + 2;
	sy = my - 2;
      }

      sx=sx*16+16; sy=sy*16+16;
      code = videoram[offs];

/*       if ((input_buffer[8] & 1) && code != 0x40) */
      /* Tile approximation : starting at code d0 ? */
/*       if (code >= 0xd0 || code == 0x31) code = 0x40; */
      if (solid[code]) {
	if (code >= 144 && code <= 192) { // Big tile...
	  /* These big tiles are fruits (appear on the bottom of the screen) */
	  int i=code-144;
	  if(i<32)
	    {
	      if((i%4)==0) {
		Draw32x32_Trans_flip_Rot(&emudx_sprites32[(i/4)<<(10+bpp)],sx,sy,0,0);
	      }
	      continue;
	    }
	}
	if (code >= 0xc0) { // maze tile
	  if (code < 0xfc)
	    draw_emudx_tile = 1;
	  // We skip a screen frame here anyway it should be unnoticeable
	} else {
	  /* Apparently we have not enough sprites : title screen, we have only 1 color
	     for the ghosts */
	  if (mspacman) { // A few adjustements to pacman tiles
	    if (code == 0x20) { // Pacman lives, for the details
	      // sprites might look a little better here too
	      UINT8 coul = (colorram[offs] & 0x1f)>>1;
	      code = 0x35;
	      conv_sprite(code,coul);
	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[code<<(10+bpp)],sx,sy,0,2);
	      continue;
	    } else if (code >= 0x21 && code <= 0x23) // end of pacman lives
	      continue;
	  } else {
	    if (code == 0xb2) { // A ghost
	      /* Ghosts are best displayed by real sprites, especially for the color which
		 is not rendered with normal tiles (only 1 color for tiles */
	      UINT8 coul = (colorram[offs] & 0x1f)>>1;
	      code = 0x20;
	      conv_sprite(code,coul);
	      draw_ghost(sx,sy,&emudx_sprites32[code<<(10+bpp)],0);
	      continue;
	    } else if (code >= 0xb0 && code <= 0xb5)
	      continue; // end of the ghost
	    else if (code == 0x20) { // Pacman lives, for the details
	      // sprites might look a little better here too
	      UINT8 coul = (colorram[offs] & 0x1f)>>1;
	      code = 0x2e;
	      conv_sprite(code,coul);
	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[code<<(10+bpp)],sx,sy,0,2);
	      continue;
	    } else if (code >= 0x21 && code <= 0x23) // end of pacman lives
	      continue;
	  }
	  if (code < 0x30 || code >= 0x80) { // not a character
	    if (code == 0x14) { // power pill
	      UINT8 coul = (colorram[offs] & 0x1f);
	      if (coul) {
		code--;
	      } else
		continue;
	    }
	    if (solid[code] == 1) { // some transp
	      Draw16x16_Trans_Rot(&emudx_sprites[code<<(8+bpp)],sx,sy,0);
	    } else {
	      Draw16x16_Rot(&emudx_sprites[code<<(8+bpp)],sx,sy,0);
	    }
	  } else { // special case for characters
	    UINT8 *map;
	    MAP_PALETTE_MAPPED_NEW(
			     col_base + (colorram[offs] & 0x1f),
			     4,
			     map
			     );
	    map += 2*bpp*2; // skip 2 first colors...
	    code -= 0x30;
	    Draw16x16_Trans_Mapped_Rot(&emudx_chars[code<<8],sx,sy,map);
	  }
	}
      }
    }
  } else
   clear_game_screen(0);

  if( check_layer_enabled(layer_id_data[1])) {
    /* Draw the sprites. Note that it is important to draw them exactly in this */
    /* order, to have the correct priorities. */

    solid = gfx_solid[1 + bank];
    for (offs = 16 - 2;offs > 2*2;offs -= 2) {
      int sx,sy;

      sx = (272 - spriteram_2[offs + 1])*2+16;
      sy = (spriteram_2[offs] - 31)*2+16;
      if (sx >= 0 && sy >= 0 && sx <= 576 && sy <= 448) {
	UINT16 ta = spriteram[offs] >> 2;
	UINT8 coul = (spriteram[offs+1] & 0xf);
	if (!coul) continue; // bank 0 is "all the colors transparent"
	coul = (coul >> 1);

	ta &= 0x3f;
	// disp_sprite(sx,sy,ta,coul);
	if (solid[ta]) {
	  if (solid[ta] == 1) {// some transp
	    if (ta >= 0x20 && ta <= 0x27) { // A ghost
	      // Draw it with 50% alpha blending !!!
	      conv_sprite(ta,coul);
	      draw_ghost(sx,sy,&emudx_sprites32[ta<<(10+bpp)],spriteram[offs] & 3);
	    } else {
	      conv_sprite(ta,coul);
	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[ta<<(10+bpp)],sx,sy,0,spriteram[offs] & 3);
	    }
	  } else {
	    conv_sprite(ta,coul);
	    // All solid, must be rather rare, I think...
	    Draw32x32_flip_Rot(&emudx_sprites32[ta<<(10+bpp)],sx,sy,0,spriteram[offs] & 3);
	  }
	}
      }
    }

    for (offs = 2*2;offs >= 0;offs -= 2) {
      int sx,sy;


      sx = (272 - spriteram_2[offs + 1])*2+16;
      sy = (spriteram_2[offs] - 31)*2+16;
      if (sx >= 0 && sy >= 0 && sx <= 576 && sy <= 448) {
	UINT16 ta = spriteram[offs] >> 2;
	UINT8 coul = (spriteram[offs+1] & 0xf);
	if (!coul) continue; // bank 0 is "all the colors transparent"
	coul = (coul >> 1);

	ta &= 0x3f;
	// disp_sprite(sx,sy,ta,coul);
	if (solid[ta]) {
	  if (solid[ta] == 1) { // some transp
	    if (ta >= 0x20 && ta <= 0x27) { // A ghost
	      // Draw it with 50% alpha blending !!!
	      conv_sprite(ta,coul);
	      draw_ghost(sx,sy,&emudx_sprites32[ta<<(10+bpp)],spriteram[offs] & 3);
	    } else {
	      conv_sprite(ta,coul);
	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[ta<<(10+bpp)],sx,sy,0,spriteram[offs] & 3);
	    }
	  } else {
	    conv_sprite(ta,coul);
	    // All solid, must be rather rare, I think...
	    Draw32x32_flip_Rot(&emudx_sprites32[ta<<(10+bpp)],sx,sy,0,spriteram[offs] & 3);
	  }
	}
      }
    }
  }
  if (use_alpha) {
    if ((input_buffer[8] & 0x30) == 0x10) { // variable alpha blending wanted
      use_alpha += inc_alpha;
      if (use_alpha < 110) {
	use_alpha = 111;
	inc_alpha = 2;
      } else if (use_alpha > 220) {
	use_alpha = 219;
	inc_alpha = -2;
      }
      init_alpha(use_alpha);
    } else if ((input_buffer[8] & 0x30) == 0x30) { // 30% alpha blending wanted !
      if (use_alpha != 180) {
	use_alpha = 180;
	init_alpha(use_alpha);
      }
    }
  }
}

// static int trace = 0;

static void execute_pengo() {
  /* The correct speed is 3.072 MHz, but 3.020 gives a more */
  /* accurate emulation speed (time for two attract mode */
  /* cycles after power up, until the high score list appears */
  /* for the second time: 3'39") */
    cpu_execute_cycles(CPU_Z80_0, 3020000/60);
  if (*interrupt_enable)
      cpu_interrupt(CPU_Z80_0, 0x38);
}

// The pacman driver is very similar. Both pengo and pacman share the same drawing function

static struct ROM_INFO rom_puckman[] =
{
  { "namcopac.6e", 0x1000, 0xfee263b3, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "namcopac.6f", 0x1000, 0x39d1fc83, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "namcopac.6h", 0x1000, 0x02083b03, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "namcopac.6j", 0x1000, 0x7a36fe55, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "pacman.5e", 0x1000, 0x0c944964, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "pacman.5f", 0x1000, 0x958fedf9, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "82s123.7f", 0x0020, 0x2fc650bd, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "82s126.4a", 0x0100, 0x3eb3a8e4, REGION_PROMS, 0x0020, LOAD_NORMAL },
  { "82s126.1m", 0x0100, 0xa9cc86bf, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { "82s126.3m", 0x0100, 0x77245b66, REGION_SMP1, 0x0100, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pacman[] =
{
  { "pacman.6e", 0x1000, 0xc1e6ab10, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "pacman.6f", 0x1000, 0x1a6fb2d4, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pacman.6h", 0x1000, 0xbcdd1beb, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "pacman.6j", 0x1000, 0x817d94e3, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_multi15[] =
{
  { "mpexe15.bin", 0x80000, 0xeb181a29, REGION_ROM1, 0x10000, LOAD_NORMAL },
  // I load the same rom in gfx1 and gfx2, it's because there are lots of
  // layouts are different offsets in it, and it's simpler to have 2 separate
  // copies to handle them...
  { "mpgfx15.bin", 0x20000, 0x012fb9ec, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "mpgfx15.bin", 0x20000, 0x012fb9ec, REGION_GFX2, 0x0000, LOAD_NORMAL },

  { "pal_7f.bin",  0x100, 0x40a5c3d9, REGION_PROMS, 0x1000, LOAD_NORMAL },
  { "clut_4a.bin", 0x400, 0x562a66de, REGION_PROMS, 0x40, LOAD_NORMAL },

  { NULL, 0, 0, 0, 0, 0 }
};

// mspacman is protected, I'll take care of this later...

static struct ROM_INFO rom_mspacman[] =
{
  { "pacman.6e", 0x1000, 0xc1e6ab10, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "pacman.6f", 0x1000, 0x1a6fb2d4, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pacman.6h", 0x1000, 0xbcdd1beb, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "pacman.6j", 0x1000, 0x817d94e3, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "u5", 0x0800, 0xf45fbbcd, REGION_ROM1, 0x8000, LOAD_NORMAL },
  { "u6", 0x1000, 0xa90e7000, REGION_ROM1, 0x9000, LOAD_NORMAL },
  { "u7", 0x1000, 0xc82cd714, REGION_ROM1, 0xb000, LOAD_NORMAL },
  { "5e", 0x1000, 0x5c281d01, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "5f", 0x1000, 0x615af909, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mspacmab[] =
{
  { "boot1", 0x1000, 0xd16b31b7, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "boot2", 0x1000, 0x0d32de5e, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "boot3", 0x1000, 0x1821ee0b, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "boot4", 0x1000, 0x165a9dd8, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "boot5", 0x1000, 0x8c3e6de6, REGION_ROM1, 0x8000, LOAD_NORMAL },
  { "boot6", 0x1000, 0x368cb165, REGION_ROM1, 0x9000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mspac6m[] =
{
  { "1.cpu", 0x1000, 0xd16b31b7, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "2.cpu", 0x1000, 0x0d32de5e, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "3.cpu", 0x1000, 0x513f4d5c, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "4.cpu", 0x1000, 0xe21c81ff, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "52.cpu", 0x1000, 0x48453707, REGION_ROM1, 0x8000, LOAD_NORMAL },
  { "62.cpu", 0x1000, 0x2e961bc4, REGION_ROM1, 0x9000, LOAD_NORMAL },

  { "7.cpu", 0x0800, 0x2850148a, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "9.cpu", 0x0800, 0x6c3c6ebb, REGION_GFX1, 0x0800, LOAD_NORMAL },

  { "8.cpu", 0x0800, 0x5596b345, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "10.cpu", 0x0800, 0x50c7477d, REGION_GFX2, 0x0800, LOAD_NORMAL },

  // the proms are taken from pacplus (as mentioned in the text file)

  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mspacpls[] =
{
  { "boot1", 0x1000, 0xd16b31b7, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "mspacatk.2", 0x1000, 0x0af09d31, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "boot3", 0x1000, 0x1821ee0b, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "boot4", 0x1000, 0x165a9dd8, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "mspacatk.5", 0x1000, 0xe6e06954, REGION_ROM1, 0x8000, LOAD_NORMAL },
  { "mspacatk.6", 0x1000, 0x3b5db308, REGION_ROM1, 0x9000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pacplus[] =
{
  { "pacplus.6e", 0x1000, 0xd611ef68, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "pacplus.6f", 0x1000, 0xc7207556, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pacplus.6h", 0x1000, 0xae379430, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "pacplus.6j", 0x1000, 0x5a6dff7b, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "pacplus.5e", 0x1000, 0x022c35da, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "pacplus.5f", 0x1000, 0x4de65cdd, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "pacplus.7f", 0x0020, 0x063dd53a, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "pacplus.4a", 0x0100, 0xe271a166, REGION_PROMS, 0x0020, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_puckman[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( P1_LEFT, 0x00, 0x02 ),
  INP0( P1_RIGHT, 0x00, 0x04 ),
  INP0( P1_DOWN, 0x00, 0x08 ),
  // cheat (must be validated by the dsw !)
#ifdef RAINE_DEBUG
  INP1( P1_B2, 0x08, 0x8 ),
#endif

  INP0( COIN1, 0x00, 0x20 ),
  INP0( COIN2, 0x00, 0x40 ),
  INP0( SERVICE, 0x00, 0x80 ),

  INP0( P2_UP, 0x02, 0x01 ),
  INP0( P2_LEFT, 0x02, 0x02 ),
  INP0( P2_RIGHT, 0x02, 0x04 ),
  INP0( P2_DOWN, 0x02, 0x08 ),

  INP0( P1_START, 0x02, 0x20 ),
  INP0( P1_B1, 0x02, 0x20 ),
  // (to simplfy gameplay with some games)
  INP0( P2_START, 0x02, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_pacman_0[] =
{
  { _("Rack Test (Cheat)") , 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_pacman_1[] =
{
  { MSG_SERVICE, 0x10,2 },
  { MSG_ON, 0},
  { MSG_OFF, 0x10},
  { MSG_CABINET, 0x80, 2 },
  { MSG_UPRIGHT, 0x80},
  { MSG_TABLE, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_pacman_2[] =
{
  { MSG_COINAGE, 0x03, 4 },
  { MSG_2COIN_1PLAY, 0x03},
  { MSG_1COIN_1PLAY, 0x01},
  { MSG_1COIN_1PLAY, 0x02},
  { MSG_FREE_PLAY, 0x00},
  { MSG_LIVES, 0x0c, 4 },
  { "1" , 0x00},
  { "2" , 0x04},
  { "3" , 0x08},
  { "5" , 0x0c},
  { MSG_EXTRA_LIFE, 0x30, 4 },
  { "10000" , 0x00},
  { "15000" , 0x10},
  { "20000" , 0x20},
  { MSG_UNKNOWN, 0x30},
  { MSG_DIFFICULTY, 0x40, 2 },
  { MSG_NORMAL, 0x40},
  { MSG_HARD, 0x00},
  { _("Ghost Names") , 0x80, 2 },
  { MSG_NORMAL, 0x80},
  { MSG_ALT, 0x00},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_pacman_4[] =
{
  { _("2x Speed Cheat") , 0x06, 3 },
  { _("Disabled") , 0x00},
  { _("Enabled Always") , 0x02},
  { _("Enabled with Button") , 0x04},
  { _("DX alpha blending"), 0x30, 4 },
  { _("Variable (MMX)") , 0x10},
  { "50%" , 0x20},
  { _("30% (MMX)") , 0x30},
  { _("None"), 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_puckman[] =
{
  { 0x0, 0x10, dsw_data_pacman_0 },
  { 0x2, 0x90, dsw_data_pacman_1 },
  { 0x4, 0xc9, dsw_data_pacman_2 },
  { 0x8, 0x10, dsw_data_pacman_4 },
  { 0, 0, NULL }
};

// No speed cheat !
static struct DSW_INFO dsw_namcosil[] =
{
  { 0x0, 0x10, dsw_data_pacman_0 },
  { 0x2, 0x90, dsw_data_pacman_1 },
  { 0x4, 0xc9, dsw_data_pacman_2 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_mspacman_2[] =
{
  { MSG_COINAGE, 0x03, 4 },
  { MSG_2COIN_1PLAY, 0x03},
  { MSG_1COIN_1PLAY, 0x01},
  { MSG_1COIN_1PLAY, 0x02},
  { MSG_FREE_PLAY, 0x00},
  { MSG_LIVES, 0x0c, 4 },
  { "1" , 0x00},
  { "2" , 0x04},
  { "3" , 0x08},
  { "5" , 0x0c},
  { MSG_EXTRA_LIFE, 0x30, 4 },
  { "10000" , 0x00},
  { "15000" , 0x10},
  { "20000" , 0x20},
  { MSG_UNKNOWN, 0x30},
  { MSG_DIFFICULTY, 0x40, 2 },
  { MSG_NORMAL, 0x40},
  { MSG_HARD, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_mspacman[] =
{
  { 0x0, 0x10, dsw_data_pacman_0 },
  { 0x2, 0x90, dsw_data_pacman_1 },
  { 0x4, 0x49, dsw_data_mspacman_2 },
  { 0x8, 0x10, dsw_data_pacman_4 },
  { 0, 0, NULL }
};

// No speed cheat for this one ;-(
static struct DSW_INFO dsw_mspacpls[] =
{
  { 0x0, 0x10, dsw_data_pacman_0 },
  { 0x2, 0x90, dsw_data_pacman_1 },
  { 0x4, 0x49, dsw_data_mspacman_2 },
  { 0, 0, NULL }
};

static GfxLayout tilelayout2 =
{
	8,8,	/* 8*8 characters */
	RGN_FRAC(1,1),
    2,  /* 2 bits per pixel */
    { 0, 4 },   /* the two bitplanes for 4 pixels are packed into one byte */
    { 8*8+0, 8*8+1, 8*8+2, 8*8+3, 0, 1, 2, 3 }, /* bits are packed in groups of four */
    { 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
    16*8    /* every char takes 16 bytes */
};

static GfxLayout spritelayout2 =
{
	16,16,	/* 16*16 sprites */
	RGN_FRAC(1,1),
	2,	/* 2 bits per pixel */
	{ 0, 4 },	/* the two bitplanes for 4 pixels are packed into one byte */
	{ 8*8, 8*8+1, 8*8+2, 8*8+3, 16*8+0, 16*8+1, 16*8+2, 16*8+3,
			24*8+0, 24*8+1, 24*8+2, 24*8+3, 0, 1, 2, 3 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
			32*8, 33*8, 34*8, 35*8, 36*8, 37*8, 38*8, 39*8 },
	64*8	/* every sprite takes 64 bytes */
};

static struct GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &tilelayout2 }, // 32 color banks
	{ REGION_GFX2, &spritelayout2 }, // 32 color banks
	{ 0, NULL } /* end of array */
};

static struct GFX_LIST pengo_gfx[] =
{
	{ REGION_GFX1, &tilelayout }, // 32 color banks
	{ REGION_GFX2, &spritelayout }, // 32 color banks
	// The 2 following are generated by the loading function
	{ REGION_GFX3, &tilelayout }, // 32 color banks
	{ REGION_GFX4, &spritelayout }, // 32 color banks
	{ 0, NULL } /* end of array */
};




static UINT8 *vector;

static void irq_vector_w(UINT32 offset, UINT16 data)
{
  // fprintf(stderr,"setting vector %x\n",data);
  // pacman use interrupt mode 2 of the z80
  // it gets its vector through port 0
  // then this vector is the low address of the interrupt vector
  // the high adress is register i when the interrupt is called

  *vector = data;
}

// This one is taken from mame. Amazing to imagine all the time spent searching
// for this...
static unsigned char decrypt_pacplus(int addr, unsigned char e)
{
	static const unsigned char swap_xor_table[6][9] =
	{
		{ 7,6,5,4,3,2,1,0, 0x00 },
		{ 7,6,5,4,3,2,1,0, 0x28 },
		{ 6,1,3,2,5,7,0,4, 0x96 },
		{ 6,1,5,2,3,7,0,4, 0xbe },
		{ 0,3,7,6,4,2,1,5, 0xd5 },
		{ 0,3,4,6,7,2,1,5, 0xdd }
	};
	static const int picktable[32] =
	{
		0,2,4,2,4,0,4,2,2,0,2,2,4,0,4,2,
		2,2,4,0,4,2,4,0,0,4,0,4,4,2,4,2
	};
	unsigned int method = 0;
	const unsigned char *tbl;


	/* pick method from bits 0 2 5 7 9 of the address */
	method = picktable[
		(addr & 0x001) |
		((addr & 0x004) >> 1) |
		((addr & 0x020) >> 3) |
		((addr & 0x080) >> 4) |
		((addr & 0x200) >> 5)];

	/* switch method if bit 11 of the address is set */
	if ((addr & 0x800) == 0x800)
		method ^= 1;

	tbl = swap_xor_table[method];
	return BITSWAP8(e,tbl[0],tbl[1],tbl[2],tbl[3],tbl[4],tbl[5],tbl[6],tbl[7]) ^ tbl[8];
}

static UINT32 speedcheat, speedadr1, speedadr2;
static UINT8 speed1,speed2,nospeed1,nospeed2;

// defined in rgui.c for allegro, but it should be generic...
extern int raine_alert(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, int c1, int c2);

// the game structs can't be modified because they are declared as const.
// So I must make a temporary copy first and then modify it...
static struct GAME_MAIN temp_game;

static char *multipac_games[] =
{
  "mutli15",
  "pacman",
  "fastpac",
  "pacplus",
  "fastplus",
  "puckman",
  "hangly",
  "pacmod",
  "pmad",
  "sil",
  "pacmini2",
  "pengman",
  "pacman3d",
  "piranha",
  "eyes",
  "crush",
  "mspacmab",
  "fastmspa",
  "mspacpls",
  "fastplus",
  "mspacmat",
  "mspacrip",
  "msyakman",
  "msindy",
  "lizwiz",
};

static void speedcheat_test() {
  if ((ROM[0x180b] == 0xbe && ROM[0x1ffd] == 0x00) ||
      (ROM[0x180b] == 0x01 && ROM[0x1ffd] == 0xbd)) {
    /* works for pacman, puckman, mspacman, mspacmab */
    speedcheat = 1;
    speedadr1 = 0x180b; speed1 = 1;    nospeed1 = 0xbe;
    speedadr2 = 0x1ffd; speed2 = 0xbd; nospeed2 = 0;
  } else if ((ROM[0x182d] == 0xbe && ROM[0x1ffd] == 0xff) ||
	     (ROM[0x182d] == 0x01 && ROM[0x1ffd] == 0xbc)) {
    // pacplus
    speedcheat = 1;
    speedadr1 = 0x182d; speed1 = 1;    nospeed1 = 0xbe;
    speedadr2 = 0x1ffd; speed2 = 0xbc; nospeed2 = 0xff;
  } else {
    speedcheat = 0;
  }
}

static void multipac_a000_w(UINT32 offset, UINT8 data) {
  int adr;
  if (data != multipac_bank) {
    print_debug("bank %x\n",data);
    if (data < 0x20) {
      data = ((data & 0x10) / 0x10 + (data & 0x0f) *2);
      adr = 0x10000 + data * 0x4000;
    } else {
      data = 0;
      adr = 0x10000;
    }
    memcpy(&ROM[0],&ROM[adr],0x4000);
    multipac_bank = data;
    memcpy(&ROM[0x8000],&ROM[adr+0x4000],0x4000);
    hs_close();
    if (current_game != &temp_game) {
      memcpy(&temp_game,current_game,sizeof(GAME_MAIN));
      current_game = &temp_game;
    }
    if (data == 28)
      data = 23;
    else if (data == 30)
      data = 24;
    else if (data > 16)
      data -= (data - 16)/2;
    if (data <= 24)
      current_game->main_name = multipac_games[data];
    if (!current_game->main_name)
      exit(1);
    *interrupt_enable = 0;
    cpu_reset(CPU_Z80_0); // the reset seems mandatory for wizliz (last game)
    hs_open();
    hs_init();

    hist_open("history.dat",current_game->main_name);
    speedcheat_test();
  }
}

static void multipac_color_w(UINT32 offset, UINT8 data) {
   // The colours are currently handled by the graphics banking, but here
   // is an exception
   if (data==2) {
      RAM[0x1050]=0; // maps to f000, don't know what it does !!!
   }
}

static void multipac_reset() {
  multipac_a000_w(0,0); // set bank = 0
  memset(RAM,0,RAMSize);
}

static void multipac_load() {
  int old_bank = multipac_bank;
  multipac_bank = 0;
  multipac_a000_w(0,old_bank); // restore the bank
}

static void load_puckman()
{
  // quite different from pengo for the init : no encoding, different memory map,
  // different palette...
  UINT8 *color_prom = load_region[REGION_PROMS];
  UINT8 palette[64*2];
  int i;
  RAMSize = 0x2050;
  memset(input_buffer,0xff,0x20);

  if (!strcmp(current_game->main_name,"pacplus")) {
    for (i = 0; i < 0x4000; i++)
      {
	ROM[i] = decrypt_pacplus(i,ROM[i]);
      }
  }

  speedcheat_test();
  if(!(RAM=AllocateMem(RAMSize))) return;

  memset(RAM,0x0,RAMSize);

  gfx_bank = &RAM[0x1030];
  interrupt_enable = gfx_bank + 1;
  vector = interrupt_enable + 1;

  // Z80 init, finally

  AddZ80AROMBase(ROM, 0x0038, 0x0066);

  AddZ80AReadByte(0x0000, 0x3fff, NULL, ROM);
  // apprently we must allow the read after the end of the bank for
  // ms pacman plus in multipac (otherwise it hangs when you insert a coin !)
  AddZ80AReadByte(0x8000, 0xefff, NULL, ROM+0x8000); // mspacman/pacman25

  AddZ80AReadByte(0x4000, 0x4fff, NULL, RAM);

  videoram = RAM;
  colorram = RAM + 0x400;
  spriteram = RAM + 0xff0;

  set_pulse_time(2); // for the coin input

  AddZ80AReadByte(0x5000, 0x503f, input_port_0_r, NULL);
  AddZ80AReadByte(0x5040, 0x507f, input_port_1_r, NULL);
  AddZ80AReadByte(0x5080, 0x50bf, input_port_2_r, NULL);
  AddZ80AReadByte(0x50c0, 0x50ff, input_port_3_r, NULL);

  AddZ80AWriteByte(0x4000, 0x4fff, NULL, RAM);
  pengo_soundregs = RAM+0x1000;
  /* Very bad idea : pengo_sound_w write to pengo_soundregs and expects the game driver
     to allocate this memory. I leave it like this to preserve mame compatibility... */
  AddZ80AWriteByte(0x5001, 0x5001, pengo_sound_enable_w, NULL); // namco.c
  AddZ80AWriteByte(0x5040, 0x505f, pengo_sound_w, NULL); // namco.c (sound)
  spriteram_2 = RAM+0x1020;
  AddZ80AWriteByte(0x5060, 0x506f, NULL, spriteram_2); // sprite ram 2

  AddZ80AWriteByte(0x5000, 0x5000, NULL, interrupt_enable); // sprite ram 2
  AddZ80AWrite(0xc000, 0xc7ff, NULL, RAM); // mirror (in write only ??? semms so...)
  // AddZ80AWrite(0x5006, 0x5006, mspac_banksw_w, NULL);


  // flip screen is at 5003, how usefull...

  // finish conf z80

  if (is_current_game("multi15")) {
    AddZ80AWrite(0xa000, 0xa000, multipac_a000_w, NULL);
    AddZ80AWrite(0xa001, 0xa001, NULL, gfx_bank);
    AddZ80AWrite(0xa002, 0xa002, multipac_color_w, NULL);
    AddZ80AWrite(0xa003, 0xa00f,NULL, &RAM[0x1040]);
    AddZ80ARW(0xf000, 0xffff, NULL, RAM+0x1050);
    multipac_bank = 0;
    memcpy(&ROM[0],&ROM[0x10000],0x4000);
    multipac_mode = 1;
    set_reset_function(&multipac_reset);
    AddSaveData(SAVE_USER_1, (UINT8 *)&multipac_bank, sizeof(multipac_bank));
    AddLoadCallback(multipac_load);
  } else {
    multipac_mode = 0;
    AddZ80AWrite(0xfffc, 0xffff, NULL, RAM + 0x1035); // ???
    AddZ80ARead(0xfffc, 0xffff, NULL, RAM + 0x1035); // ???
  }
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadPort,		NULL);
   AddZ80AReadPort(  -1,   -1, NULL,			NULL);
  AddZ80AWritePort(0x00, 0x00, irq_vector_w,			NULL);
   AddZ80AWritePort(0x01, 0xFF, DefBadWritePort, 	NULL);
   AddZ80AWritePort(  -1,   -1, NULL,			NULL);

   AddZ80AInit();
   *interrupt_enable = 0;

   /* The palette from the color proms : argh ! */
   /* Apparently there are only 32 different colors at start !!! */

   if (multipac_mode) {
     UINT8 *prom = load_region[REGION_PROMS];
     memcpy(prom,&prom[0x1000], 0x10);
     memcpy(&prom[0x10],&prom[0x1020], 0x10);
     memcpy(&prom[0x20],&prom[0x1020], 0x10);
     memcpy(&prom[0x30],&prom[0x1020], 0x10);

     for (i = 0;i < 64;i++) {
       int bit0,bit1,bit2,r,g,b;

       /* red component */
       bit0 = (*color_prom >> 0) & 0x01;
       bit1 = (*color_prom >> 1) & 0x01;
       bit2 = (*color_prom >> 2) & 0x01;
       // r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
       r = (bit2 << 2) | (bit1 << 1) | bit0;
       /* green component */
       bit0 = (*color_prom >> 3) & 0x01;
       bit1 = (*color_prom >> 4) & 0x01;
       bit2 = (*color_prom >> 5) & 0x01;
       // g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
       g = (bit2 << 2) | (bit1 << 1) | bit0;

       /* blue component */
       bit0 = 0;
       bit1 = (*color_prom >> 6) & 0x01;
       bit2 = (*color_prom >> 7) & 0x01;
       // b = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
       b = (bit2 << 2) | (bit1 << 1) | bit0;

       WriteWord(&palette[i*2],b + (g<<3) + (r<<6));
       color_prom++;
     }

     /* After this, it seems to be a list of colors (from 0 to f). */
     /* color_prom now points to the beginning of the lookup table */

     /* character lookup table */
     /* sprites use the same color lookup table as characters */
     for (i = 0;i < 0x80;i++) {
       WriteWord(&mypal[i*2], ReadWord(&palette[(*(color_prom++) & 0x0f)*2]));
     }

     color_prom += 0x80;

     // 2nd bank (pac man plus) -> 0x20
     for (i = 0;i < 0x80;i++)
     {
       if (*color_prom)
	 WriteWord(&mypal[i*2+0x100],ReadWord(&palette[((*color_prom & 0x0f) + 0x10) * 2]));      /* third palette bank */
       else     /* preserve transparency */
	 WriteWord(&mypal[0x80*2+i*2], 0);

       color_prom++;
     }
     color_prom += 0x80;

     // 3rd bank (Crush Roller) -> 0x40
     for (i = 0;i < 0x80;i++)
     {
       if (*color_prom)
	 WriteWord(&mypal[i*2+0x200],ReadWord(&palette[((*color_prom & 0x0f) + 0x00) * 2]));      /* third palette bank */
       else     /* preserve transparency */
	 WriteWord(&mypal[0x200+i*2], 0);

       color_prom++;
     }
     color_prom += 0x80;

    // 4th bank (Liz Wiz) -> 0x60
     for (i = 0;i < 0x80;i++)
     {
       if (*color_prom)
	 WriteWord(&mypal[i*2+0x300],ReadWord(&palette[((*color_prom & 0x0f) + 0x30) * 2]));      /* third palette bank */
       else     /* preserve transparency */
	 WriteWord(&mypal[0x300+i*2], 0);

       color_prom++;
     }
   } else {
     for (i = 0;i < 16;i++) {
       int bit0,bit1,bit2,r,g,b;

       /* red component */
       bit0 = (*color_prom >> 0) & 0x01;
       bit1 = (*color_prom >> 1) & 0x01;
       bit2 = (*color_prom >> 2) & 0x01;
       // r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
       r = (bit2 << 2) | (bit1 << 1) | bit0;
       /* green component */
       bit0 = (*color_prom >> 3) & 0x01;
       bit1 = (*color_prom >> 4) & 0x01;
       bit2 = (*color_prom >> 5) & 0x01;
       // g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
       g = (bit2 << 2) | (bit1 << 1) | bit0;

       /* blue component */
       bit0 = 0;
       bit1 = (*color_prom >> 6) & 0x01;
       bit2 = (*color_prom >> 7) & 0x01;
       // b = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
       b = (bit2 << 2) | (bit1 << 1) | bit0;

       WriteWord(&palette[i*2],b + (g<<3) + (r<<6));
       color_prom++;
     }

     color_prom += 0x10;
     /* After this, it seems to be a list of colors (from 0 to f). */
     /* color_prom now points to the beginning of the lookup table */

     /* character lookup table */
     /* sprites use the same color lookup table as characters */
     for (i = 0;i < 0x80;i++) {
       WriteWord(&mypal[i*2], ReadWord(&palette[(*(color_prom++) & 0x0f)*2]));
     }
   }

  InitPaletteMap(mypal, 0x80, 4, 0x200);
  set_colour_mapper(&col_map_xxxxRrrgggbbb);
  layer_id_data[0] = add_layer_info(gettext("BG"));
  layer_id_data[1] = add_layer_info(gettext("SPRITES"));
  init_tile_cache();

  if (is_current_game("pacman") || is_current_game("puckman") || is_current_game("mspacmab")) {
    char *db_filename;
    if (is_current_game("mspacmab")) {
      mspacman = 1;
      db_filename = "mspacmang.dx2";
    } else {
      db_filename = "pacmang.dx2";
      mspacman = 0;
    }
    if (exists_emudx_file(db_filename)) {
#ifndef SDL
      if((raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("EmuDX support?"),NULL,raine_translate_text("&Yes"),raine_translate_text("&No"),'Y','N'))==1)
#else
      if(MessageBox(gettext("EmuDX"),gettext("EmuDX support ?"),gettext("Yes|No")) == 1)
#endif
	{
	if (mspacman)
	  load_emudx(db_filename,4,204,193+13,312+13,0x30+5,0x7f+5,448,576,makecol(0xff,0,0xff),draw_emudx);
	else
	  load_emudx(db_filename,11,0xd0,193,312,0x30+12,0x7f+12,448,576, makecol(0xff,0,0xff),draw_emudx);
	if (raine_cpu_capabilities & CPU_MMX) {
	  use_alpha = 180;
	  init_alpha(use_alpha);
	  inc_alpha = -1;
	} else
	  use_alpha = 0;
      }
      draw_emudx_tile = 0;
    }
  }
}

static void execute_puckman() {
    cpu_execute_cycles(CPU_Z80_0, 3072000/60);
  if (speedcheat) {
    if ((((input_buffer[8] & 4) == 4) && (input_buffer[2] & 0x20)==0) || (input_buffer[8] & 6) == 2) {
      ROM[speedadr1] = speed1;
      ROM[speedadr2] = speed2;
    } else {
      ROM[speedadr1] = nospeed1;
      ROM[speedadr2] = nospeed2;
    }
  }
  if (*interrupt_enable) {
    cpu_interrupt(CPU_Z80_0, *vector);
  }
}

static struct ROM_INFO rom_pacman3d[] =
{
  { "pacman.6e", 0x1000, 0xc1e6ab10, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "pacman3d.6f", 0x1000, 0x96364259, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pacman.6h", 0x1000, 0xbcdd1beb, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "pacman3d.6j", 0x1000, 0x959e930e, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "pacman3d.5e", 0x1000, 0xaa203d45, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "pacman3d.5f", 0x1000, 0xd1830540, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_namcosil[] =
{
  { "namcopac.6e", 0x1000, 0xfee263b3, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "namcosil.6f", 0x1000, 0xc5ec2352, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "namcopac.6h", 0x1000, 0x02083b03, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "namcosil.6j", 0x1000, 0x57a07f6e, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_xenrev[] =
{
  { "pacman.6e", 0x1000, 0xc1e6ab10, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "pacman.6f", 0x1000, 0x1a6fb2d4, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pacman.6h", 0x1000, 0xbcdd1beb, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "xenrev.6j", 0x1000, 0x64a10b6c, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "xenrev.5e", 0x1000, 0x40e3522d, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/* Tested hacks from http://www.cis.rit.edu/~jerry/Software/gamehacks/ :
   pengman : pengo is flashing when walking. Too bad. And the map is too weird to play,
   turning is difficult at places. Too bad...
   Brakman : didn't even tried it. Looks interesting, but if it's too hard, it misses
   the playability, very important in this kind of game...
*/

static struct ROM_INFO rom_pacman25[] =
{
  { "namcopac.6e", 0x1000, 0xfee263b3, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "namcosil.6f", 0x1000, 0xc5ec2352, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "pacman25.6h", 0x1000, 0x92cd89b9, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "pacman25.6j", 0x1000, 0xf7193845, REGION_ROM1, 0x3000, LOAD_NORMAL },

  // maps 1-6
  { "maps1.rom", 0x1000, 0x19a22304, REGION_ROM1, 0x8000, LOAD_NORMAL },
  // maps 7-12
  { "maps2.rom", 0x1000, 0x7cdbd912, REGION_ROM1, 0x9000, LOAD_NORMAL },
  // maps 13-18
  { "maps3.rom", 0x1000, 0xc626ea9c, REGION_ROM1, 0xa000, LOAD_NORMAL },
  // maps 18-25
  { "maps4.rom", 0x1000, 0xf5ba954d, REGION_ROM1, 0xb000, LOAD_NORMAL },

  { "pacman25.5e", 0x1000, 0x11d47ae1, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct VIDEO_INFO video_pengo =
{
   draw_pengo,
   288,
   224,
   16,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   pengo_gfx
};
static struct VIDEO_INFO video_puckman =
{
   draw_pengo,
   288,
   224,
   16,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   gfxdecodeinfo,
};
GMEI( pengo, "Pengo", SEGA, 1982, GAME_MAZE);
CLNEI( pengo2u, pengo, "Pengo set 2", BOOTLEG, 1982, GAME_MAZE);

GMEI( puckman, "PuckMan (Japan set 1)", NAMCO, 1980, GAME_MAZE);
// 2004 ? This is the date in the zip file, at least...
// The asm source is available at the url given above.
/* Yeah the year is indeed 2004, for the 25th anniversary, but there still is a bug
   with palette selection... anyway it does not make the game unplayable, so I'll keep
   it. */
CLNEI( pacman25, puckman, "25 MAP PAC", BOOTLEG, 2004, GAME_MAZE);
// See http://www.xensei.com/users/jeffm/www/pacman/xens-revenge/ for this one !
CLNEI( xenrev, puckman, "Xen's Revenge (hack - hard!)", BOOTLEG, 1998, GAME_MAZE);
CLNEI( pacman, puckman, "Pac-Man (Midway)", MIDWAY, 1980, GAME_MAZE);
// pacman3d from http://home.kabelfoon.nl/~msilvius/sillyarcade.htm
CLNEI( pacman3d, puckman, "Pacman 3D", BOOTLEG,1998, GAME_MAZE);

// namcosil : vertical tunnels ! (same url)
CLNEI( namcosil, puckman, "Namco Pacman - Vertical tunnel edition!", BOOTLEG,1998, GAME_MAZE,
	.dsw = dsw_namcosil);

// This one is really for mame compatibility only, if we didn't add it then most people
// would miss some roms since this is the parent set of all mspacman games in mame !
CLNEI(mspacman, puckman, "Ms. Pac-Man", MIDWAY, 1981, GAME_MAZE | GAME_PARTIALLY_WORKING);

#define input_mspacman input_puckman
#define load_mspacman load_puckman
#define video_mspacman video_puckman
#define execute_mspacman execute_puckman
CLNEI( mspacmab, mspacman, "Ms. Pac-Man (bootleg)", BOOTLEG, 1981, GAME_MAZE);
CLNEI( mspacpls, mspacman, "Ms. Pac-Man + (hack)", BOOTLEG, 1981, GAME_MAZE,
	.dsw = dsw_mspacpls);
#define input_pacplus input_puckman
#define dsw_pacplus dsw_puckman
#define load_pacplus load_puckman
#define video_pacplus video_puckman
#define execute_pacplus execute_puckman
CLNEI( mspac6m, pacplus, "Ms. Pac-Man 6 maps (hack)", BOOTLEG, 1981, GAME_MAZE);

CLNEI( pacplus, puckman, "Pac-Man Plus", NAMCO, 1982, GAME_MAZE);
CLNEI( multi15, puckman, "MultiPac 1.5", BOOTLEG, 1998, GAME_MAZE);

