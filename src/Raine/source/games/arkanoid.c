/*

Arkanoid driver.
Emmanuel Anne <emanne@absysteme.fr>
Thanks to Stephh for his eagle eye to find the levels pointers in the z80 roms !

Notes :
 - I used the mame driver as a base for this driver, so thanks !
 - They are rendering the bg layer with a blit when it does not change, I just use
the cache system for solid tiles because it seems faster than the blits !
 - I decided to make a driver without any MCU (68705), because this chip is just an
anti-copy chip, and it just gets in the way. That's why the parent romset (arkanoid)
does not work : its mcu is not emulated. You get :

arkatayt : bootleg patch of arkanoid to work without its mcu.
  This bootleg version had a bug in the 25th level (bad level pointer). It's fixed
  here.
arkangc : more or less the same with a level selection at the begining of the game
arkatour : Arkanoid with brand new levels ! I made this one by applying the bootleg
  patch from arkatayt to arkatour because there was no bootleg version available.
  This is where the help from Stephh was valuable ! The patch is quite big...

This is the first driver in raine which uses colour proms AFAIK. I emulate them like a
normal palette but I never call ClearPaletteMap of course. Something to notice : most
colour mappers in raine expect 16 colors/bank even if InitPaletteMap has a parameter for
the number of colours by bank. So I had to update the colour mapper to make it work with
8 colours/bank like here. Almost all the other color mappers force 16 colors / bank.

Interesting RAM address from Stephh :
0xc4ce : if it contains 1, then the door to next level is opened.

*/

#include "gameinc.h"
#include "ay8910.h"
#include "sasound.h"

// parent set.
static struct ROM_INFO rom_arkanoid[] =
{
  { "a75_01-1.rom", 0x8000, 0x5bcda3b0 , REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "a75_11.rom", 0x8000, 0xeafd7191 , REGION_ROM1, 0x8000, LOAD_NORMAL },
  { "arkanoid.uc", 0x0800, 0x515d77b6 , REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "a75_03.rom", 0x8000, 0x038b74ba , REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "a75_04.rom", 0x8000, 0x71fae199 , REGION_GFX1, 0x08000, LOAD_NORMAL },
  { "a75_05.rom", 0x8000, 0xc76374e2 , REGION_GFX1, 0x10000, LOAD_NORMAL },
  { "07.bpr", 0x0200, 0x0af8b289 , REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "08.bpr", 0x0200, 0xabb002fb , REGION_PROMS, 0x0200, LOAD_NORMAL },
  { "09.bpr", 0x0200, 0xa7c6c277 , REGION_PROMS, 0x0400, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_arkatour[] =
{
  { "t_ark1.bin", 0x8000, 0xe3b8faf5 , REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "t_ark2.bin", 0x8000, 0x326aca4d , REGION_ROM1, 0x8000, LOAD_NORMAL },
  { REGION_EMPTY, 0, 0 , REGION_ROM2, 0, LOAD_NORMAL },
  { "t_ark3.bin", 0x8000, 0x5ddea3cf , REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "t_ark4.bin", 0x8000, 0x5fcf2e85 , REGION_GFX1, 0x08000, LOAD_NORMAL },
  { "t_ark5.bin", 0x8000, 0x7b76b192 , REGION_GFX1, 0x10000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_arkatayt[] =
{
  { REGION_EMPTY, 0, 0 , REGION_ROM2, 0, LOAD_NORMAL },
  { "arkanoid.1", 0x8000, 0x6e0a2b6f , REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "arkanoid.2", 0x8000, 0x5a97dd56 , REGION_ROM1, 0x8000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_arkangc[] =
{
  { REGION_EMPTY, 0, 0 , REGION_ROM2, 0, LOAD_NORMAL },
  { "arkgc.1", 0x8000, 0xc54232e6 , REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "arkgc.2", 0x8000, 0x9f0d4754 , REGION_ROM1, 0x8000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_arkanoid_4[] =
{
  { _("Allow Continue"), 0x01, 2 },
  { MSG_NO, 0x01},
  { MSG_YES, 0x00},
  DSW_SCREEN( 0x02, 0x00),
  DSW_SERVICE( 0, 0x04),
  { MSG_DIFFICULTY, 0x08, 2 },
  { _("Easy") , 0x08},
  { _("Hard") , 0x00},
  { MSG_EXTRA_LIFE, 0x10, 2 },
  { _("20K 60K and every 60K") , 0x10},
  { _("20K only") , 0x00},
  { MSG_LIVES, 0x20, 2 },
  { "3" , 0x20},
  { "5" , 0x00},
  { MSG_COINAGE, 0xc0, 4 },
  { MSG_2COIN_1PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0xc0},
  { MSG_1COIN_1PLAY, 0x80},
  { MSG_1COIN_6PLAY, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_arkanoid[] =
{
  { 8, 0xfe, dsw_data_arkanoid_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_arknoidj_4[] =
{
  { _("Allow Continue"), 0x01, 2 },
  { MSG_NO, 0x01},
  { MSG_YES, 0x00},
  DSW_SCREEN( 0x02, 0x00),
  DSW_SERVICE( 0, 0x04),
  { MSG_DIFFICULTY, 0x08, 2 },
  { _("Easy") , 0x08},
  { _("Hard") , 0x00},
  { MSG_EXTRA_LIFE, 0x10, 2 },
  { _("20K60K and every 60K") , 0x10},
  { _("20K only") , 0x00},
  { MSG_LIVES, 0x20, 2 },
  { "3" , 0x20},
  { "5" , 0x00},
  { MSG_COINAGE, 0x40, 2 },
  { MSG_1COIN_1PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x00},
  DSW_CABINET( 0x00, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_arknoidj[] =
{
  { 8, 0x7e, dsw_data_arknoidj_4 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_arkatayt_4[] =
{
  { _("Allow Continue"), 0x01, 2 },
  { MSG_NO, 0x01},
  { MSG_YES, 0x00},
  DSW_SCREEN( 0x02, 0x00),
  DSW_SERVICE( 0, 0x04),
  { MSG_DIFFICULTY, 0x08, 2 },
  { _("Easy") , 0x08},
  { _("Hard") , 0x00},
  { MSG_EXTRA_LIFE, 0x10, 2 },
  { _("60K100K and every 60K") , 0x10},
  { _("60K only") , 0x00},
  { MSG_LIVES, 0x20, 2 },
  { "2" , 0x20},
  { "3" , 0x00},
  { MSG_COINAGE, 0x40, 2 },
  { MSG_2COIN_1PLAY, 0x00},
  { MSG_1COIN_1PLAY, 0x40},
  DSW_CABINET( 0x00, 0x80),
  { NULL, 0}
};

static struct DSW_INFO dsw_arkatayt[] =
{
  { 8, 0x5e, dsw_data_arkatayt_4 },
  { 0, 0, NULL }
};

static struct INPUT_INFO input_arkanoid[] =
{
  INP0( P1_START, 0x0000, 0x01 ),
  INP0( P2_START, 0x0000, 0x02 ),
  INP0( SERVICE, 0x0000, 0x04 ),
  INP0( TILT, 0x0000, 0x08 ),
  INP1( COIN1, 0x0000, 0x10 ),
  INP1( COIN2, 0x0000, 0x20 ),
  // The last 2 bits are from the 68705 (mcu) 0x40 and 0x80

  // These 2 are added for those who are crazy enough to play arkanoid without a mouse
  // or a trackball...
  INP1( P1_LEFT, 1, 0x01 ),
  INP1( P1_RIGHT, 1, 0x02 ),

  INP0( P1_B1, 0x0002, 0x01 ),
  INP0( P2_B1, 0x0002, 0x04 ),
  END_INPUT
};


static GFX_LAYOUT charlayout =
{
	8,8,	/* 8*8 characters */
	4096,	/* 4096 characters */
	3,	/* 3 bits per pixel */
	{ 2*4096*8*8, 4096*8*8, 0 },	/* the two bitplanes are separated */
	{ 0, 1, 2, 3, 4, 5, 6, 7 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
	8*8	/* every char takes 8 consecutive bytes */
};

static struct GFX_LIST arkanoid_gfx[] =
{
	{ REGION_GFX1, &charlayout, },
	/* sprites use the same characters above, but are 16x8 */
	{ -1 } /* end of array */
};

UINT8 input_port_4_r(UINT32 offset) {
  return get_dsw(0);
}

static struct AY8910interface ay8910_interface =
{
	1,	/* 1 chips */
	1500000,	/* 1.5 MHz ???? */
	{ 85 | (0x80<<8) },
	{ 0 },
	{ input_port_4_r },
	{ 0 },
	{ 0 }
};

static struct SOUND_INFO sound_arkanoid[] =
{
   { SOUND_AY8910,  &ay8910_interface,  },
   { 0,             NULL,               },
};

static UINT8 input_stuff(UINT32 offset) {
  switch(offset) {
  case 0xd00c: return input_buffer[0];
  case 0xd010: return input_buffer[2];
  case 0xd018: /* This one returns the paddle position, 1st or 2nd one */
    /* Since raine emulates only one paddle, we always return port 4 */
    return RAM[0x2802];
  }
  return 0xff;
}

static int gfxbank,palettebank;
#define SENSITIVE 5

static void arkanoid_d008_w(UINT32 offset, UINT8 data)
{
  //  if (offset == 0xd008) {
  /* bits 0 and 1 flip X and Y, I don't know which is which */
  // flip_screen_x_set(data & 0x01);
  // flip_screen_y_set(data & 0x02);

  /* bit 2 selects the input paddle */
  /* Used by the read at d018 */
  // arkanoid_paddle_select = data & 0x04;

  /* bit 3 is coin lockout (but not the service coin) */
  // coin_lockout_w(0, !(data & 0x08));
  // coin_lockout_w(1, !(data & 0x08));

  /* bit 4 is unknown */

  /* bits 5 and 6 control gfx bank and palette bank. They are used together */
  /* so I don't know which is which. */
    gfxbank = (data & 0x20) >> 5;
    palettebank = (data & 0x40) >> 6;

  /* bit 7 is unknown */
    //  }
}

static UINT8 *vram,*RAM_SPR,*GFX_BG0_SOLID;
static UINT8 mypal[512*2];
static UINT32 z80_frame;

// First version of the patch function :
// args address, nb, source bytes (xnb), dest bytes (xnb)
// the source bytes are passed to be sure we patch the right thing.

static void patch(UINT8 *rom, UINT32 nb, ...) {
  va_list ap;
  int i;
  int val;

  va_start(ap,nb);
  for (i=0; i<nb; i++) {
    val = va_arg(ap,int);
    if (rom[i] != val) {
      va_end(ap);
      return;
    }
  }
  for (i=0; i<nb; i++) {
    val = va_arg(ap,int);
    rom[i] = val;
  }
  va_end(ap);
}

// Same thing but directly with strings instead of separate arguments
// it allows to have a more compact syntax

static void patchstr(UINT8 *rom, char *as1, char *as2) {
  int nb=strlen(as1)/2;
  int val,i;
  char old;
  char s1[80],s2[80];
  strcpy(s1,as1);
  strcpy(s2,as2);
  for (i=0; i<nb; i++) {
    old = s1[(i+1)*2];
    s1[(i+1)*2] = 0;
    sscanf(&s1[i*2],"%x",&val);
    s1[(i+1)*2] = old;
    if (rom[i] != val) {
      return;
    }
  }
  for (i=0; i<nb; i++) {
    old = s2[(i+1)*2];
    s2[(i+1)*2] = 0;
    sscanf(&s2[i*2],"%x",&val);
    s2[(i+1)*2] = old;
    rom[i] = val;
  }
}

// same thing without the source bytes. Used to insert the levels data and the
// function to read this data.

static void puthexstr(UINT8 *rom, char *as1) {
  int nb=strlen(as1)/2;
  int val,i;
  char old;
  char s2[256];
  strcpy(s2,as1);
  for (i=0; i<nb; i++) {
    old = s2[(i+1)*2];
    s2[(i+1)*2] = 0;
    sscanf(&s2[i*2],"%x",&val);
    s2[(i+1)*2] = old;
    rom[i] = val;
  }
}

static void load_arkanoid() {
  int i;
  UINT8 *color_prom = load_region[REGION_PROMS];

  RAMSize = 0x2803;
  if (!(RAM = AllocateMem(RAMSize))) return;

  // End of the RAM :
  // 2800 : word = mouse position in mickeys. This allow to adjust sensitivity
  // 2802 : byte = mouse position reported to the driver : 0-255

  memset(RAM,0,RAMSize);
  memset(input_buffer,0x0,16);

  Z80ROM = load_region[REGION_ROM1];

  vram = RAM+0x800;
  RAM_SPR = vram + 0x800;

  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066); // ???!
  AddZ80ARead(0x0000,0xbfff, NULL, ROM);
  AddZ80ARead(0xc000,0xc7ff, NULL, RAM);
  AddZ80ARead(0xd001,0xd001, AY8910_read_port_0_r, NULL);
  AddZ80ARead(0xd00c,0xd018, input_stuff, NULL);
  /* The following includes RAM + blank area (must return 0)
     From the mame driver :

	Most if not all Arkanoid sets have a bug in their game code. It occurs on the
	final level where the player has to dodge falling objects. The bug resides in
	the collision detection routine which sometimes reads from unmapped addresses
	above $F000. For these addresses it is vital to read zero values, or else the
	player will die for no reason.
  */
  AddZ80ARead(0xe000,0xffff, NULL, vram);

  AddZ80AWrite(0xc000, 0xc7ff, NULL, RAM);
  AddZ80AWrite(0xe000,0xefff, NULL, vram);

  AddZ80AWrite(0xd000, 0xd000, AY8910_control_port_0_w, NULL);
  AddZ80AWrite(0xd001, 0xd001, AY8910_write_port_0_w,   NULL);

  AddZ80AWrite(0xd008, 0xd008, arkanoid_d008_w,   NULL);

  AddZ80ARead(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
  AddZ80AWrite(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
  AddZ80AReadPort(-1, -1, NULL, NULL);

  AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,			NULL);	// Trap Idle Z80
  AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);	// <bad reads>
  AddZ80AWritePort(-1, -1, NULL, NULL);
  AddZ80AInit();

  // Preparation of the palette...
  for (i = 0;i < 512;i++)
    {
      int r,g,b;
      /* red component */
      r = color_prom[i] & 0xf;
      /* green component */
      g  = color_prom[i + 512] & 0xf;
      /* blue component */
      b = color_prom[i + 2*512] & 0xf;

      WriteWord(&mypal[i*2],b + (g<<4) + (r<<8));
    }
  InitPaletteMap(mypal, 0x40, 8, 0x1000);
  set_colour_mapper(&col_map_xxxx_rrrr_gggg_bbbb);
  GameMouse = 1;

  z80_frame = CPU_FRAME_MHz(6,60);
  // Speed hack
  Z80ROM[0x03c9]=0xD3;  // OUTA (AAh)
  Z80ROM[0x03ca]=0xAA;  //
  SetStopZ80Mode2(0x3c5);

  /* Increasing the z80 speed does not seem usefull : it does not check if it got late */

  // z80_frame = CPU_FRAME_MHz(7,60);
  if  (is_current_game("arkatour")) {

    /* The big bootleg patch for arkatour to get rid of the mcu.
       It's based on the arkatayt bootleg patch. */

    UINT8 *rom = Z80ROM;
    // disable hardware test
    patch(&rom[0x340],9,
	       0x3a,0x0c,0xd0,0xcb,0x77,0x28,0xf9,0xaf,0x32,
	       0xcd,0x17,0x21, // call $2117
	       0xcd,0xd0,0x21, // call $21d0
	       0xc3,0xbb,0x03  // jr $3bb
	       );

    // disable mcu tests
    patch(&rom[0x3f4],2,0x28,0xf9,0,0);
    patch(&rom[0x402],2,0x28,0xf9,0,0);

    patch(&rom[0x417],2,0x20,0xf9,0,0);
    patch(&rom[0x421],2,0x20,0x13,0,0);
    patch(&rom[0x428],2,0x20,0xf9,0,0);
    patch(&rom[0x434],1,0x28,0x18);

    // These 3 are not direct mcu tests, but seem related...
    patch(&rom[0x476],2,0x20,0x07,0,0);
    patch(&rom[0x5d4],1,0x28,0x18);
    patch(&rom[0x61b],2,0x20,0x06,0,0);

    patch(&rom[0x68b],2,0x28,0xfc,0,0);
    patch(&rom[0x6ae],2,0x28,0xfc,0,0);
    patch(&rom[0x6e6],2,0x28,0xfc,0,0);
    patch(&rom[0x6ed],2,0x28,0xfc,0,0);

    patch(&rom[0x6f7],7,
	  0x20,0xf9,0x19,0xcd,0xd0,0x21,0x7e,  // ld a,(hl)
	  0x00,0x19,0xcd,0xd0,0x21,0x3e,0x06); // ld a,6

    patch(&rom[0x776],2,0x28,0xfc,0,0);
    patch(&rom[0x796],2,0x20,0xfd,0,0);
    patch(&rom[0x7ba],2,0x28,0xfc,0,0);
    patch(&rom[0x7c1],2,0x28,0xfc,0,0);
    patch(&rom[0x80c],2,0x20,0xf9,0,0);

    // This one reads something at a different place in RAM ?!! (ed83)
    patch(&rom[0x822],5,
	  0x2a,0x71,0xc4,0x7e,0xa7,
	  0x3a,0x83,0xed,0xfe,0x00);

    patch(&rom[0x15ca],2,0x28,0xfc,0,0);
    patch(&rom[0x15e8],2,0x28,0xfc,0,0);
    patch(&rom[0x15f2],2,0x28,0xfc,0,0);
    patch(&rom[0x15f6],2,0x20,0xfc,0,0);

    patch(&rom[0x1623],2,0x20,0xfc,0,0);
    patch(&rom[0x167c],2,0x20,0x07,0,0);
    patch(&rom[0x16a1],2,0x28,0xfc,0,0);

    patch(&rom[0x17db],3,0x3a,0x18,0xd0,0x3e,0x8b,0x00);
    patch(&rom[0x17eb],4,0x28,0x05,0x10,0xf7,0x18,0x05,0x00,0x00);
    patch(&rom[0x17ff],3,0x3a,0x18,0xd0,0x3e,0x8b,0x00);

    // From here there is an offset between aratayt and arkatour
    // (arkatayt is just a patch of arkanoid, arkatour is a rewrite !)

    patch(&rom[0x2a76+30],2,0x28,0xfc,0,0);
    patch(&rom[0x2b7f+30],2,0x28,0xfc,0,0);
    patch(&rom[0x2b98+30],2,0x28,0xfc,0,0);
    patch(&rom[0x2ba2+30],2,0x28,0xfc,0,0);
    patch(&rom[0x2ba6+30],2,0x20,0xfc,0,0);

    // First call to the function reading levels pointers (middle of it)
    // arkanoid 9680 -> arkatour 97a7
    // start arkanoid 965b -> arkatour 9782
    patch(&rom[0x2bba+30],3,0x3a,0x18,0xd0, // ld a,($d018)
	  0xcd,0xa7,0x97);               // -> call $97a7
    patch(&rom[0x2bc0+30],2,0x20,0xfc,0,0);
    patch(&rom[0x2bcb+30],1,0x77,0x00);

    patch(&rom[0x311a+36],2,0x28,0xfc,0,0);

    // Apparently only these 2 bytes are used in the patch (caution)
    // the offset changes again...
    patch(&rom[0x3183+37],2,0x21,0x3c,0x18,0x11);

    patch(&rom[0x3211+37],2,0x28,0xfc,0,0);
    // and again...
    patch(&rom[0x3278+42],2,0x20,0x07,0,0);

    // this one is nowhere... Data ? Does not look like data.
    // patch(&rom[0x32e1+42],1,0x28,0x18);
    // a few areas of data after this...
    // copyright at 33be (arkanoid) 3441 (arkatour)

    patchstr(&rom[0x4f09-75],"28","18");

    patch(&rom[0x5878-75],4,0xcb,0x76,0x28,0xfc,0,0,0,0);
    patch(&rom[0x5881-75],2,0x28,0xfc,0,0);
    patch(&rom[0x5885-75],10,
	  0x32,0x18,0xd0,
	  0x3a,0x0c,0xd0,
	  0xcb,0x7f,
	  0x20,0xf9,
	  // ->
	  0x2a,0x88,0xed, // ld      hl,($ed88)
	  0xcd,0x50,0x20, // call    $2050
	  0xe5,           // push    hl
	  0,0,0);
    patch(&rom[0x58a6-75],2,0x20,0xf9,0,0);
    patch(&rom[0x58b8-75],2,0x67,0xd1,0xd1,0xe1);

    patch(&rom[0x67f9-75],1,0x28,0x18);
    patch(&rom[0x76ea-75],8,0x26,0xd0,0x2e,0x0c,0xcb,0x76,0x28,0xfc,
	  0,0,0,0,0,0,0,0);
    patchstr(&rom[0x76f9-75],"e5214d7ecd50207ee13218d0","000000000000000000000000");
    patchstr(&rom[0x778c-75],"e526d02e0ccb7628fc","000000000000000000");
    patchstr(&rom[0x779c-75],"e5214d7ecd50207ee1e13218d0","00000000000000000000000000");

    // 7b82 (arkanoid) 7b37 (arkatour) : notice this game is for use in japan only
    // 7d9f (arkanoid) taYto
    // 8000 clearly data, but don't know what

    patchstr(&rom[0x91b0-131],"28","18");
    patchstr(&rom[0x920b-131],"28fc","0000");
    patchstr(&rom[0x9224-131],"28fc","0000");
    patchstr(&rom[0x9242-131],"2007","0000");
    patchstr(&rom[0x92d1-131],"28fc","0000");

    patchstr(&rom[0x9317-106],"28fc","0000");
    patchstr(&rom[0x937a-106],"28","18");
    patchstr(&rom[0x93be - 106 ],"20","60");

    patchstr(&rom[0x9430+65],"28fc","0000");
    patchstr(&rom[0x9449+65],"28fc","0000");
    patchstr(&rom[0x945a+65],"28fc","0000");
    patchstr(&rom[0x9464+65],"28fc","0000");
    patchstr(&rom[0x946e +65],"28fc","0000");

    patchstr(&rom[0x94cf +215],"28f9","0000");
    patchstr(&rom[0x94eb +215],"28f9","0000");
    patchstr(&rom[0x9503 +215],"28fc","0000");
    patchstr(&rom[0x950d +215],"28fc","0000");
    patchstr(&rom[0x9517 +215],"28fc","0000");

    patchstr(&rom[0x95eb +295],"2007","0000");

    // levels reading. Levels array inserted at 7d64

    puthexstr(&rom[0x7d64],"BF150138BE2B04CB0FE014D416BD1F4222CA299A302B34E640BF41A94DB54FF7543F5B745C765D6064AD665D67EE73B874A2758D7D637F4D86968F3690209DDE9DDF77");
    // the function itself
    puthexstr(&rom[0x9782],"3a72ed8721647dcd50207e236e67c33b98");
    // 97a7 : returns the paddle position
    puthexstr(&rom[0x97a7],"3a18d0c9");

    patchstr(&rom[0x9769 +295],"7e","00");

    patchstr(&rom[0x97d1 +349],"28","18");
    patchstr(&rom[0x97e5 +349],"28fc","0000");
    patchstr(&rom[0x982b +349],"28","18");

    patchstr(&rom[0x9916 +222],"28","18");
    patchstr(&rom[0x9925 +222],"28fc","0000");
    patchstr(&rom[0x9976 +222],"28","18");

    patchstr(&rom[0x99d7 +235],"28fc","0000");

    patchstr(&rom[0x9b61 +220],"2007","0000");
    patchstr(&rom[0x9c06 +220],"28fc","0000");
    patchstr(&rom[0x9c80 +227],"20","60");

  } else if (is_current_game("arkatayt"))
    // fixes level 25
    patchstr(&Z80ROM[0xbda5],"e5","ed");

  input_buffer[0] |= 0x40;
  GFX_BG0_SOLID = NULL;
}

static void execute_arkanoid() {
  int mx,my;
  int paddle;
  GetMouseMickeys(&mx,&my);

  if(input_buffer[1]&1) mx = -12;
  if(input_buffer[1]&2) mx = 12;

  paddle = ReadWord(&RAM[0x2800])+mx;
  if (paddle < 0)
    paddle += 255*SENSITIVE;
  else if (paddle > 255*SENSITIVE)
    paddle -= 255*SENSITIVE;
  WriteWord(&RAM[0x2800], paddle);
  RAM[0x2802] = paddle/SENSITIVE;
  if (*MouseB & 1) input_buffer[2] &= 0xfe;

  cpu_execute_cycles(CPU_Z80_0, z80_frame);
  cpu_interrupt(CPU_Z80_0, 0x38);
}

extern UINT16 nb_tile_used;

static void draw_arkanoid() {
  int ofs = 0x800 - 32*2*2 - 2; // Draw starting 2 lines from the end
  int sx,sy,bank;
  UINT8 *map;

  if (!GFX_BG0_SOLID) {
    init_tile_cache();
    GFX_BG0_SOLID = gfx_solid[0];
  }

  /* The palette is never cleared or changed since it's a prom */

  // BG Layer : solid
  clear_tile_cache();
  for (sy = 8*28-8; sy>=0; sy-=8) {
    for (sx=8*32-8; sx>=0; sx-=8) {
      UINT32 code = vram[ofs + 1] + ((vram[ofs] & 0x07) << 8) + 2048 * gfxbank;
      bank = ((vram[ofs] & 0xf8)>>3)+ 32 * palettebank;
      MAP_PALETTE_MAPPED_NEW(
			     bank,
			     8,
			     map
			     );
      if ((tile_cache[code]) && (cache_map[code] == map)) {
	Move8x8_Rot(tile_cache[code],sx,sy,NULL);
      } else {
	Draw8x8_Mapped_Rot(&GFX[code<<6],sx,sy,map);
	add_tile_cache_Rot(NULL,sx,sy,code);
	cache_map[code] = map;
      }
      ofs -= 2;
    }
  }

  /* Draw the sprites. */
  for (ofs = 0;ofs < 64;ofs += 4) {
    int sx,sy,code;


    sx = RAM_SPR[ofs];
    sy = 232 - RAM_SPR[ofs + 1];
    if (sy < 0 || sy > 224-8 || sx > 248) {
      continue;
    }

/*     if (flip_screen_x) sx = 248 - sx; */
/*     if (flip_screen_y) sy = 248 - sy; */

    code = (RAM_SPR[ofs + 3] + ((RAM_SPR[ofs + 2] & 0x03) << 8) + 1024 * gfxbank)*2;

    MAP_PALETTE_MAPPED_NEW(
			   ((RAM_SPR[ofs + 2] & 0xf8) >> 3) + 32 * palettebank,
			   8,
			   map
			   );

    if (GFX_BG0_SOLID[code]) {
      if (GFX_BG0_SOLID[code]==1) // Some pixels transp
	Draw8x8_Trans_Mapped_Rot(&GFX[code<<6],sx,sy-8,map);
      else
	Draw8x8_Mapped_Rot(&GFX[code<<6],sx,sy-8,map);
    }
    // Lower part (8x16 sprites)
    code++;
    if (GFX_BG0_SOLID[code]) {
      if (GFX_BG0_SOLID[code]==1) // Some pixels transp
	Draw8x8_Trans_Mapped_Rot(&GFX[code<<6],sx,sy,map);
      else
	Draw8x8_Mapped_Rot(&GFX[code<<6],sx,sy,map);
    }
  }
}

static struct VIDEO_INFO video_arkanoid =
{
   draw_arkanoid,
   256,
   224,
   0,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   arkanoid_gfx,
};

GMEI( arkanoid,
     "Arkanoid",
     TAITO,
     1986,
     GAME_BREAKOUT | GAME_NOT_WORKING);

CLNEI( arkatayt,
	   arkanoid,
	   "Arkanoid (Tayto bootleg, Japanese)",
	   BOOTLEG,
	   1986,
	   GAME_BREAKOUT,
	   .dsw = dsw_arkatayt);


CLNEI( arkangc,
	   arkanoid,
	   "Arkanoid (Bootleg, level selection)",
	   BOOTLEG,
	   1986,
	   GAME_BREAKOUT,
	   .dsw = dsw_arknoidj);

CLNEI( arkatour,
       arkanoid,
       "Arkanoid Tournamant",
       TAITO,
       1987,
       GAME_BREAKOUT);
