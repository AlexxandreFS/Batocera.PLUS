/* Seeing mame source, it would seem the original driver used an intel chip for
   input/output (controls and sound). This makes the driver much more complex,
   and it does not seem necessary, so I have just skipped the intel chip and
   taken directly controls and sound commands.
   Also this driver has emudx support, dx sounds + ay8910 sound (for the music).
   Now also supports galaxian clones (very similar hw)
*/

#include "gameinc.h"
#include "decode.h"
#include "ay8910.h"
#include "sasound.h"
#include "froggerm.h"
#include "blit.h"
#include "emudx.h"
#include "dxsmp.h"
#include "galdxm.h"
#ifdef SDL
#include "sdl/dialogs/messagebox.h"
#endif

extern void hs_load (void);

// defined in rgui.c for allegro, but it should be generic...
extern int raine_alert(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, int c1, int c2);

static int romset,
  stars_blink_state,
  stars_colors_start,stars_scrollpos;

#define STARS_COUNT 252
struct star
{
	int x,y,color;
};
static struct star stars[STARS_COUNT];

static struct ROM_INFO rom_frogger[] =
{
  { "frogger.26", 0x1000, 0x597696d6, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "frogger.27", 0x1000, 0xb6e6fcc3, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "frsm3.7", 0x1000, 0xaca22ae0, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "frogger.608", 0x0800, 0xe8ab0256, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "frogger.609", 0x0800, 0x7380a48f, REGION_ROM2, 0x0800, LOAD_NORMAL },
  { "frogger.610", 0x0800, 0x31d7eb27, REGION_ROM2, 0x1000, LOAD_NORMAL },
  { "frogger.607", 0x0800, 0x05f7d883, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "frogger.606", 0x0800, 0xf524ee30, REGION_GFX1, 0x0800, LOAD_NORMAL },
  { "pr-91.6l", 0x0020, 0x413703bf, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_froggs[] =
{
  { "frogger.ic5", 0x1000, 0xc4224bc4, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "frogger.ic6", 0x1000, 0x5370ad00, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "frogger.ic7", 0x1000, 0xdd251066, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "frogger.ic8", 0x1000, 0xe7d0563d, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_galaxian[] =
{
  { "galmidw.u", 0x0800, 0x745e2d61, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "galmidw.v", 0x0800, 0x9c999a40, REGION_ROM1, 0x0800, LOAD_NORMAL },
  { "galmidw.w", 0x0800, 0xb5894925, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "galmidw.y", 0x0800, 0x6b3ca10b, REGION_ROM1, 0x1800, LOAD_NORMAL },
  { "7l", 0x0800, 0x1b933207, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "1h.bin", 0x0800, 0x39fb43a4, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "1k.bin", 0x0800, 0x7e3f56a2, REGION_GFX1, 0x0800, LOAD_NORMAL },
  { "6l.bpr", 0x0020, 0xc3ac9467, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_galapx[] =
{
  { "galx.u", 0x0800, 0x79e4007d, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "galx.v", 0x0800, 0xbc16064e, REGION_ROM1, 0x0800, LOAD_NORMAL },
  { "galx.w", 0x0800, 0x72d2d3ee, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "galx.y", 0x0800, 0xafe397f3, REGION_ROM1, 0x1800, LOAD_NORMAL },
  { "galx.z", 0x0800, 0x778c0d3c, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "galx.1h", 0x0800, 0xe8810654, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "galx.1k", 0x0800, 0xcbe84a76, REGION_GFX1, 0x0800, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_superg[] =
{
  { "7f.bin", 0x1000, 0x4335b1de, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "superg.w", 0x0800, 0xddeabdae, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "superg.y", 0x0800, 0x9463f753, REGION_ROM1, 0x1800, LOAD_NORMAL },
  { "superg.z", 0x0800, 0xe6312e35, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "galmidw.1j", 0x0800, 0x84decf98, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "galmidw.1k", 0x0800, 0xc31ada9e, REGION_GFX1, 0x0800, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/* If there is a difference except the sega name instead of konami in frogger1 and
   frogger2, then this difference is well hidden !!! */

static struct DSW_DATA dsw_data_frogger_1[] =
{
  { MSG_LIVES, 0x03, 4 },
  { "3", 	0x00},
  { "5", 	0x01},
  { "7", 	0x02},
  { _("256 (Cheat)"), 	0x03},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_frogger_2[] =
{
  { MSG_COINAGE, 0x06, 4 },
  { _("A 2/1 B 2/1 C 2/1"), 	0x02},
  { _("A 2/1 B 1/3 C 2/1"), 	0x04},
  { _("A 1/1 B 1/1 C 1/1"), 	0x00},
  { _("A 1/1 B 1/6 C 1/1"), 	0x06},
  DSW_CABINET( 0x00, 0x08),
  { NULL, 0}
};

static struct DSW_INFO dsw_frogger[] =
{
  { 0x2, 0x00, dsw_data_frogger_1 },
  { 0x4, 0x00, dsw_data_frogger_2 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_galaxian_0[] =
{
  DSW_CABINET( 0x00, 0x20),
  DSW_SERVICE( 0x40, 0),
  { NULL, 0}
};


static struct DSW_DATA dsw_data_galaxian_1[] =
{
  { MSG_COINAGE, 0xc0, 4 },
  { MSG_2COIN_1PLAY, 0x40},
  { MSG_1COIN_1PLAY, 0x00},
  { MSG_1COIN_2PLAY, 0x80},
  { MSG_FREE_PLAY, 0xc0},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_galaxian_2[] =
{
  { MSG_EXTRA_LIFE, 0x03, 4 },
  { "7000", 0x00},
  { "10000", 0x01},
  { "12000", 0x02},
  { "20000", 0x03},
  { MSG_LIVES, 0x04, 2 },
  { "2", 0x00},
  { "3", 0x04},
  DSW_UNUSED( 0x08, 0x00),
  { NULL, 0}
};

static struct DSW_INFO dsw_galaxian[] =
{
  { 0x0, 0x00, dsw_data_galaxian_0 },
  { 0x2, 0x00, dsw_data_galaxian_1 },
  { 0x4, 0x04, dsw_data_galaxian_2 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_superg_0[] =
{
  { MSG_EXTRA_LIFE, 0x03, 4 },
  { "4000", 0x01},
  { "5000", 0x02},
  { "7000", 0x03},
  { MSG_UNKNOWN, 0x00},
  { MSG_LIVES, 0x04, 2 },
  { "3", 0x00},
  { "5", 0x04},
  DSW_UNUSED( 0x08, 0x00),
  { NULL, 0}
};

static struct DSW_INFO dsw_superg[] =
{
  { 0x0, 0x00, dsw_data_galaxian_0 },
  { 0x2, 0x00, dsw_data_galaxian_1 },
  { 0x4, 0x01, dsw_data_superg_0 },
  { 0, 0, NULL }
};

static struct INPUT_INFO input_frogger[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( SERVICE, 0x00, 0x04 ),
  INP0( P1_RIGHT, 0x00, 0x10 ),
  INP0( P1_LEFT, 0x00, 0x20 ),
  INP0( COIN2, 0x00, 0x40 ),
  INP0( COIN1, 0x00, 0x80 ),

  INP0( P1_RIGHT, 0x02, 0x10 ),
  INP0( P1_LEFT, 0x02, 0x20 ),
  INP0( P2_START, 0x02, 0x40 ),
  INP0( P1_START, 0x02, 0x80 ),

  INP0( P1_DOWN, 0x04, 0x01 ),

  INP0( P1_UP, 0x04, 0x10 ),
  INP0( P1_DOWN, 0x04, 0x40 ),
#ifdef RAINE_DEBUG
  INP1( P1_B2, 0x08, 0x8 ),
#endif
   END_INPUT
};

static struct INPUT_INFO input_galaxian[] =
{
  INP1( COIN1, 0x00, 0x01 ),
  INP1( COIN2, 0x00, 0x02 ),
  INP1( P1_LEFT, 0x00, 0x04 ),
  INP1( P1_RIGHT, 0x00, 0x08 ),
  INP1( P1_B1, 0x00, 0x10 ),
  INP1( TEST, 0x00, 0x80 ),

  INP1( P1_START, 0x02, 0x01 ),
  INP1( P2_START, 0x02, 0x02 ),
  INP1( P2_LEFT, 0x02, 0x04 ),
  INP1( P2_RIGHT, 0x02, 0x08 ),
  INP1( P2_B1, 0x02, 0x10 ),
#ifdef RAINE_DEBUG
  INP1( P1_B2, 0x08, 0x8 ),
#endif

   END_INPUT
};

static GfxLayout galaxian_charlayout =
{
	8,8,
	RGN_FRAC(1,2),
	2,
	{ RGN_FRAC(0,2), RGN_FRAC(1,2) },
	{ 0, 1, 2, 3, 4, 5, 6, 7 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
	8*8
};
static GfxLayout galaxian_spritelayout =
{
	16,16,
	RGN_FRAC(1,2),
	2,
	{ RGN_FRAC(0,2), RGN_FRAC(1,2) },
	{ 0, 1, 2, 3, 4, 5, 6, 7,
			8*8+0, 8*8+1, 8*8+2, 8*8+3, 8*8+4, 8*8+5, 8*8+6, 8*8+7 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
			16*8, 17*8, 18*8, 19*8, 20*8, 21*8, 22*8, 23*8 },
	32*8
};

/* Don't know how mame found this frogger timer ??!!! What is sure is that without
   the timer, the ay8910 will produce no sounds at all ! Which made its emulation rather
   hard... */
static int frogger_timer[10] =
{
	0x00, 0x10, 0x08, 0x18, 0x40, 0x90, 0x88, 0x98, 0x88, 0xd0
};

static UINT8 frogger_portB_r(UINT32 offset)
{
	/* need to protect from totalcycles overflow */
	static int last_totalcycles = 0;

	/* number of Z80 clock cycles to count */
	static int clock;

	int current_totalcycles;

	current_totalcycles = mz80GetCyclesDone();
	clock = (clock + (current_totalcycles-last_totalcycles)) % 5120;

	last_totalcycles = current_totalcycles;
	return frogger_timer[clock/512];
}

struct AY8910interface frogger_ay8910_interface =
{
	1,	/* 1 chip */
	14318000/8,	/* 1.78975 MHz */
	{ 255 | (0x80<<8) },
	{ soundlatch_lo_r },
	{ frogger_portB_r },
	{ 0 },
	{ 0 }
};

static struct dxsmpinterface frogger_emudx_interface =
  {
    "froggerm.dx2",
    YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT)
  };

static struct dxsmpinterface galax_emudx_interface =
  {
    "galdxm.dx2",
    YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT)
  };

static struct SOUND_INFO sound_frogger[] =
{
   { SOUND_AY8910,  &frogger_ay8910_interface,  },
   { SOUND_DXSMP, &frogger_emudx_interface, },
   { 0,             NULL,               },
};

static struct SOUND_INFO sound_galaxian[] =
{
  { SOUND_DXSMP, &galax_emudx_interface, },
  { 0, NULL }
};

static UINT8 *gfx_ram,*attributes, *spriteram, *bulletsram, *nmi_enable,*spr,
  *flip_screen_x,*flip_screen_y,*stars_enable;

static UINT16 mypal[(8+1+16)*4];

static UINT8 *copy_sprites(UINT8 *region) {
  UINT8 *dest = AllocateMem(0x1000);
  memcpy(dest, region, 0x1000);
  return dest;
}

static int layer_id_data[2];
static UINT8 cursam=music1;

static void frogger_sound_w(UINT32 offset, UINT16 data) {
/* Sound cpu codes:
   (directly from emudx)

1 - Credit?
2 - Splash
3 - Splat
4 - Frog Jump
5 - Time running out?
6 - dead (but be carefull this command is also sent at the start of the game)
7
8
9
10 - Intro
11 - Start main tune when samples stop?
12
13 - Game over ?
14 - Next tune
15 - Main tune
16 - All frogs home?

24 - Lady Frog

8/240 - Frog home?

208 - Racing car?

255 - Theme?

Mike

*/

/* I commented the music sounds to have the ay8910 playing the music instead */

  static int dont_play_dead;

  if (!raine_nb_samples) {
    latch = data;
    cpu_interrupt(CPU_Z80_1,0x38);

    return;
  }

  if(data==1) raine_play_sample(coin,200);
  else
    if(data==2)
    {
      raine_stop_samples();
      raine_play_sample(splash,100);
    }
  else if(data==3)
    {
      raine_stop_samples();
      raine_play_sample(splat,255);
    }
  else if(data==4) raine_play_sample(jump,100);
  else if(data==5) raine_play_sample(timeout,100);
/*   else if(data==10) raine_play_sample(start,40); */

  else if(data==13)
    {
      raine_stop_samples();
      raine_play_sample(gameover,100);
    }

  else if(data==14)
    {
      raine_stop_samples();
      raine_play_sample(cursam++,100);
      if(cursam>music6) cursam=music1;
    }

  else if(data==16)
    {
      raine_stop_samples();
      raine_play_sample(allhome,250);
    }
  else if(data==24) raine_play_sample(coin,200);
  else if(data==15) {
    raine_stop_samples();
    raine_play_sample(maintune,100);
  }
  else if(data==208) raine_play_sample(car,100);

  else if(data==240 || data==8) raine_play_sample(home,250);
  else if(data==0x6) {
    if (dont_play_dead) {
      dont_play_dead = 0;
    } else {
      raine_stop_samples();
      raine_play_sample(dead,250);
    }
  } else if (data == 11) // start of game
    dont_play_dead = 1;
  else if (data != 6 && data != 12){
    // 6 seems to be a generic command : sent when the game starts, and also when you
    // loose a life...
    latch = data;
    cpu_interrupt(CPU_Z80_1,0x38);
    if (data == 13 || data == 14 || data == 16) // game over, music start, all home
      raine_stop_samples();
  }
}

static UINT16 corresp_tiles[392];

static UINT16 char_map[32*7*2];
static UINT8 *char_tab;

static void setup_frog_gfx(void)
{
  int h[]={1,28,-2,25};
  int a,x=0,chr=0;
  UINT8 *dest;
  int bpp = display_cfg.bpp / 16;

  for(a=0;a<256;a++)
    {
      corresp_tiles[a] = a+h[x]-(chr*2);
      x++;
      if(x==4)
	{
	  x=0;
	  chr++;
	  if(chr==14) chr=0;
	}
    }

  if (!(char_tab = AllocateMem(45*(256)))) return;

  /* This crazy function tries to keep the pseudo 3d mapping for the chars
     This can't be handled by the emudx module because the characters are not contiguous
     I must use the correspondance table here. And moreover they use this pseudo 3d look
     which requires more than 1 color ! */
  switch(bpp) {
  case 1: // 16 bpp
      {
	  UINT16 *src;

	  for (chr=0; chr<45; chr++) {
	      if (chr==44)
		  src = (UINT16*)&emudx_sprites[corresp_tiles[0x4e]<<9];
	      else
		  src = (UINT16*)&emudx_sprites[corresp_tiles[chr]<<9];
	      dest = char_tab + chr*16*16;
	      for (a=0; a<0x100; a++) {
		  if (src[a] != emudx_transp) {
		      int red = (src[a] & 0xf800)>>11;
		      if ((src[a] & 0x1f) > red) red = src[a] & 0x1f; // some are mapped to blue...
		      if (!red) red = 1; // avoid transparency !
		      dest[a] = red;
		  } else {
		      dest[a] = 0;
		  }
	      }
	  }
      }
      break;
  case 2: // 32 bpp
      {
	  UINT32 *src;

#ifdef SDL
	  int Rshift = color_format->Rshift;
	  int Rmask = color_format->Rmask;
	  int Bshift = color_format->Bshift;
	  int Bmask = color_format->Bmask;
#else
	  int Rshift = 16;
	  int Rmask = 0xff0000;
	  int Bshift = 0;
	  int Bmask = 0xff;
#endif

	  for (chr=0; chr<45; chr++) {
	      if (chr==44)
		  src = (UINT32*)&emudx_sprites[corresp_tiles[0x4e]<<10];
	      else
		  src = (UINT32*)&emudx_sprites[corresp_tiles[chr]<<10];
	      dest = char_tab + chr*16*16;
	      for (a=0; a<0x100; a++) {
		  if (src[a] != emudx_transp) {
		      int red = (src[a] & Rmask)>>Rshift;
		      if (((src[a] & Bmask)>>Bshift) > red)
			  red = (src[a] & Bmask)>>Bshift; // some are mapped to blue...
		      red >>=3; // convert to palette indice 0..1f
		      if (!red) red = 1; // avoid transparency !
		      dest[a] = red;
		  } else {
		      dest[a] = 0;
		  }
	      }
	  }
      }
  }
}

static void setup_gal_gfx(void)
{
  int h[]={1,28,-2,25};
  int a,x=0,chr=0;
  UINT16 *src;
  UINT8 *dest;

  for(a=0;a<392;a++)
    {
      corresp_tiles[a] = a+h[x]-(chr*2);
      x++;
      if(x==4)
	{
	  x=0;
	  chr++;
	  if(chr==14) chr=0;
	}
    }

  if (!(char_tab = AllocateMem(94*256))) return;

  /* This crazy function tries to keep the pseudo 3d mapping for the chars
     This can't be handled by the emudx module because the characters are not contiguous
     I must use the correspondance table here. And moreover they use this pseudo 3d look
     which requires more than 1 color ! */
  for (chr=0; chr<94; chr++) {
    int code = corresp_tiles[chr];
    src = (UINT16*)&emudx_sprites[code<<9];
    dest = char_tab + chr*16*16;
    for (a=0; a<0x100; a++) {
      if (src[a] != emudx_transp) {
	int red = ((src[a] & 0x1f)>>0) ;
	// the following line will prevent digits (codes from 0 to 9) to be
	// blended. They are really more readable without blending, so it's
	// probably better...
	// if (chr >= 10 && (src[a] & 0x1f) > red) red = src[a] & 0x1f;
	if (red < 12) red = 12; // avoid too dark sprites
	dest[a] = red;
      } else {
	dest[a] = 0;
      }
    }
  }
}

/* We need at least 32 for the emudx sprites (32x32) */
#define BORDER 32

static int draw_emudx_tile;
static int bpp;

#ifdef RAINE_DEBUG
static void draw_debug_layer() {
  UINT8 code, color;
  int x,y,zzzz,zz;
  UINT8 *map,*solid;
  int coul1, coul2,sx,sy;
  char str[4];
  UINT8 *gfx = load_region[REGION_GFX1];

  // background color
  MAP_PALETTE_MAPPED_NEW(
			 8,
			 4,
			 map
			 );
  /* The screen is split by 2 bands of colour. These colors are not actually drawn by
     the game, but it was verified on the original hardware (as mentioned in the mame
     driver) */
  switch(display_cfg.bpp) {
  case 8: coul1 = map[0]; coul2 = map[1]; break;
  case 15:
  case 16: coul1 = ReadWord(&map[0]); coul2 = ReadWord(&map[2]); break;
  default: coul1 = ReadLong(&map[0]); coul2 = ReadLong(&map[4]); break;
  }
  rectfill(GameBitmap,BORDER,BORDER,BORDER+224*2,BORDER+256*2/2,coul2);
  rectfill(GameBitmap,BORDER,BORDER+256*2/2,BORDER+224*2,BORDER+256*2,coul1);

  if( check_layer_enabled(layer_id_data[0])) {
    solid = gfx_solid[0];

    /* No scroll register for this layer (0,0) */
    zzzz=0;

    /* These complex looking lines are just the unrolling of START_SCROLL_8(BORDER,BORDER,256,224)
       + the line scroll handling between the fors */

    zz=zzzz;
    for(x=(BORDER);(UINT32)x<(256+BORDER);x+=8){
      int coffs = attributes[(x-BORDER)/8*2];
      int xoffs=0;

      /* In fact it's not a true line scroll it would rather be some sort of "character"
	 scroll, which means that the offset is applied to the whole character line (8
	 pixels). As such, we can just change the offset, without calling the ldraw
	 functions which become unnecessary here ! The offset is in pixels though, not in
	 characters, so we compute an intermediate xoffs...
	 It's more like changing the layer scroll offset every 8 pixels or every row */

      if (coffs) {
	if (romset == 0)
	  coffs = ((coffs << 4) | (coffs >> 4)) & 0xff; // frogger modify
	xoffs = (coffs&7);
	coffs /= 8;
      }

      for(y=(int)(8-xoffs);(int)y<(224+24-xoffs);y+=8){
	zz = ((((y+xoffs)/8)+coffs)&31)*32+(x-BORDER)/8; // direct access (ignores scrollx, scrolly)
	code = gfx_ram[zz];
	color = attributes[((zz & 0x1f) << 1) | 1];
	if (romset == 0)
	  color = ((color >> 1) & 0x03) | ((color << 2) & 0x04); // frogger modify

	if (solid[code]) {
	  MAP_PALETTE_MAPPED_NEW(
				 color,
				 4,
				 map
				 );
	  sy = (y-8)*2+BORDER-16; // convert to 16x16
	  sx = (x-BORDER)*2+BORDER;
	  if (solid[code] == 1) // transp
	    Draw8x8_Trans_Mapped_Rot(&gfx[code<<6],sx,sy,map);
	  else
	    Draw8x8_Mapped_Rot(&gfx[code<<6],sx,sy,map);
	  sprintf(str,"%02x",code);
	  textout_fast(str,448+BORDER*2-8-sy,sx+8,get_white_pen());
	  sprintf(str,"%x",color);
	  textout_fast(str,448+BORDER*2-8-sy+8,sx,get_white_pen());
	}
      }
    }
  }
}
#endif

static void setup_frogger_pal() {
  int a;
  for (a=0; a<0x20; a++) {
    int c=a<<3;
    if (display_cfg.bpp == 15) {
      GET_PEN_FOR_COLOUR_15(c,c,c,char_map[a]); // white
      GET_PEN_FOR_COLOUR_15(c,c,c,char_map[a+32]); // white (undefined in fact)
      GET_PEN_FOR_COLOUR_15(c,0,c,char_map[a+32*2]); // magenta
      GET_PEN_FOR_COLOUR_15(c,0,0,char_map[a+32*3]); // red
      GET_PEN_FOR_COLOUR_15(0,c,c,char_map[a+32*4]); // cyan
      GET_PEN_FOR_COLOUR_15(c,c,0,char_map[a+32*5]); // yellow
      GET_PEN_FOR_COLOUR_15(0,c,0,char_map[a+32*6]); // green
    } else if (display_cfg.bpp == 16) { // 16
      GET_PEN_FOR_COLOUR_16(c,c,c,char_map[a]); // white
      GET_PEN_FOR_COLOUR_16(c,c,c,char_map[a+32]); // white (undefined in fact)
      GET_PEN_FOR_COLOUR_16(c,0,c,char_map[a+32*2]); // magenta
      GET_PEN_FOR_COLOUR_16(c,0,0,char_map[a+32*3]); // red
      GET_PEN_FOR_COLOUR_16(0,c,c,char_map[a+32*4]); // cyan
      GET_PEN_FOR_COLOUR_16(c,c,0,char_map[a+32*5]); // yellow
      GET_PEN_FOR_COLOUR_16(0,c,0,char_map[a+32*6]); // green
    } else if (display_cfg.bpp == 32) {
      WriteLong(&char_map[a*2],makecol(c,c,c)); // white
      WriteLong(&char_map[(a+32)*2],makecol(c,c,c)); // white (undefined in fact)
      WriteLong(&char_map[(a+32*2)*2],makecol(c,0,c)); // magenta
      WriteLong(&char_map[(a+32*3)*2],makecol(c,0,0)); // red
      WriteLong(&char_map[(a+32*4)*2],makecol(0,c,c)); // cyan
      WriteLong(&char_map[(a+32*5)*2],makecol(c,c,0)); // yellow
      WriteLong(&char_map[(a+32*6)*2],makecol(0,c,0)); // green
    }
  }
}

static void setup_gal_pal() {
  int a;
  for (a=0; a<0x20; a++) {
    int c=a<<3;
    if (display_cfg.bpp == 15) {
      GET_PEN_FOR_COLOUR_15(c,c,c,char_map[a]); // white
      GET_PEN_FOR_COLOUR_15(c,c,c,char_map[a+32]); // white (undefined in fact)
      GET_PEN_FOR_COLOUR_15(c,0,0,char_map[a+32*2]); // red
      GET_PEN_FOR_COLOUR_15(c,0,c,char_map[a+32*3]); // magenta
      GET_PEN_FOR_COLOUR_15(c,c,0,char_map[a+32*4]); // yellow
      GET_PEN_FOR_COLOUR_15(c,0,0,char_map[a+32*5]); // red
      GET_PEN_FOR_COLOUR_15(0,c,c,char_map[a+32*6]); // cyan
    } else if (display_cfg.bpp == 16) { // 16
      GET_PEN_FOR_COLOUR_16(c,c,c,char_map[a]); // white
      GET_PEN_FOR_COLOUR_16(c,c,c,char_map[a+32]); // white (undefined in fact)
      GET_PEN_FOR_COLOUR_16(c,0,0,char_map[a+32*2]); // red
      GET_PEN_FOR_COLOUR_16(c,0,c,char_map[a+32*3]); // magenta
      GET_PEN_FOR_COLOUR_16(c,c,0,char_map[a+32*4]); // yellow
      GET_PEN_FOR_COLOUR_16(c,0,0,char_map[a+32*5]); // red
      GET_PEN_FOR_COLOUR_16(0,c,c,char_map[a+32*6]); // cyan
    } else if (display_cfg.bpp == 32) {
      WriteLong(&char_map[(a)*2],makecol(c,c,c)); // white
      WriteLong(&char_map[(a+32)*2],makecol(c,c,c)); // white (undefined in fact)
      WriteLong(&char_map[(a+32*2)*2],makecol(c,0,0)); // red
      WriteLong(&char_map[(a+32*3)*2],makecol(c,0,c)); // magenta
      WriteLong(&char_map[(a+32*4)*2],makecol(c,c,0)); // yellow
      WriteLong(&char_map[(a+32*5)*2],makecol(c,0,0)); // red
      WriteLong(&char_map[(a+32*6)*2],makecol(0,c,c)); // cyan
    }
  }
}

static int warned;

static void draw_emudx() {
  UINT8 code,color;
  int x,y,zzzz,zz;
  UINT8 *map,*solid;
  int coul1, coul2;

  if (RefreshBuffers) {
      setup_frogger_pal();
      bpp = display_cfg.bpp / 16;
      if (bpp == 1 && !warned) {
	  warned = 1;
#ifndef SDL
	  raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("Switch to at least 16bpp and reload"),NULL,raine_translate_text("&Ok"),NULL,'O',0);
#endif
      }
  }

#ifdef RAINE_DEBUG
  if (input_buffer[8] & 8) {
    draw_debug_layer();
    return;
  }
#endif

  if (draw_emudx_tile) {
    blit(emudx_tiles[0], GameBitmap, 0, 0, BORDER, BORDER, 448, 512);
    draw_emudx_tile = 0;
    // Make sure the fps counter is visible
    switch(raine_cfg.show_fps_mode) {
    case 1:
    case 2: rectfill(GameBitmap, BORDER+224*2-9*6,BORDER, BORDER+224*2, BORDER+8,0);
      break;
    case 3:
    case 4:
      rectfill(GameBitmap,BORDER+224*2-10*6,BORDER, BORDER+224*2, BORDER+8*7,0);
      break;
    }
  } else {
    /* The screen is split by 2 bands of colour. These colors are not actually drawn by
       the game, but it was verified on the original hardware (as mentioned in the mame
       driver) */
    // background color
    MAP_PALETTE_MAPPED_NEW(
			   8,
			   4,
			   map
			   );
    switch(display_cfg.bpp) {
    case 8: coul1 = map[0]; coul2 = map[1]; break;
    case 15:
    case 16: coul1 = ReadWord(&map[0]); coul2 = ReadWord(&map[2]); break;
    default: coul1 = ReadLong(&map[0]); coul2 = ReadLong(&map[4]); break;
    }
    rectfill(GameBitmap,BORDER,BORDER,BORDER+224*2,BORDER+256*2/2,coul2);
    rectfill(GameBitmap,BORDER,BORDER+256*2/2,BORDER+224*2,BORDER+256*2,coul1);
  }

  /* A note about optimization : mame and emudx thought it was nice to have a buffer
     to handle dirty areas to redraw here. The point is that during the game most of the
     screen is moving because of linescrolls effects (cars on bottom part, trees on the
     top). So in fact your dirty buffer is not really usefull, I am not even sure it does
     not make things slower than what they should be ! */

  if( check_layer_enabled(layer_id_data[0])) {
    solid = gfx_solid[0];

    /* No scroll register for this layer (0,0) */
    zzzz=0;

    /* These complex looking lines are just the unrolling of START_SCROLL_8(BORDER,BORDER,256,224)
       + the line scroll handling between the fors */

    zz=zzzz;
    for(x=(BORDER);(UINT32)x<(256*2+BORDER);x+=16){
      int coffs = attributes[(x-BORDER)/16*2];
      int xoffs=0;

      /* In fact it's not a true line scroll it would rather be some sort of "character"
	 scroll, which means that the offset is applied to the whole character line (8
	 pixels). As such, we can just change the offset, without calling the ldraw
	 functions which become unnecessary here ! The offset is in pixels though, not in
	 characters, so we compute an intermediate xoffs...
	 It's more like changing the layer scroll offset every 8 pixels or every row */

      if (coffs) { // don't touch that : these offsets are inteded for 8x8 sprites !
	if (romset == 0)
	  coffs = ((coffs << 4) | (coffs >> 4)) & 0xff; // frogger modify
	xoffs = (coffs&7);
	coffs /= 8;
      }

      for(y=(int)(0-xoffs);(int)y<(256-xoffs);y+=8){
	int sy;
	if (y<0) continue;
	zz = ((((y+xoffs)/8)+coffs)&31)*32+(x-BORDER)/16; // direct access (ignores scrollx, scrolly)
	code = gfx_ram[zz];
	color = attributes[((zz & 0x1f) << 1) | 1];
	if (romset == 0)
	  color = ((color >> 1) & 0x03) | ((color << 2) & 0x04); // frogger modify

	if (solid[code]) {
/* 	  MAP_PALETTE_MAPPED_NEW( */
/* 				 color, */
/* 				 4, */
/* 				 map */
/* 				 ); */
	  sy = (y-8)*2 +BORDER-16; // convert to 16x16
	  if (y<0) continue;
	  if (code==16 || (code>63 && code<76)) {
	    draw_emudx_tile = 1;
	    continue;
	  }
	  else if (code<=43 || (code>63 && code<80) || (code>207 && code<212)) {
	    // Normal character
	    /* Actually the real characters seem to be codes from 0 to 9 for digits
	       and then from 0x11 for A to 42 (?) and included 4e for copyright
	       The progress bar for time uses characters $c and $f at least, but it has
	       the same problems as normal chars : not the right colors (does not switch
	       to red).
	    */
	    if (code <= 43 || code == 0x4e) {
	      // special mapping for the chars to retrieve the original colors
	      if (code >= 10 && code <= 16) { // pseudo graphic (progress bar)
		// special color mapping for these
		if (color == 5) color = 6;
		else if (color == 0) color = 3;
	      } else if (code == 0x4e) code = 44; // copyright symbol

	      if (solid[code] == 1) // transp
		Draw16x16_Trans_Mapped_Rot(&char_tab[code<<8],x,sy,(UINT8*)&char_map[32*color*bpp]);
	      else
		Draw16x16_Mapped_Rot(&char_tab[code<<8],x,sy,(UINT8*)&char_map[32*color*bpp]);
	    } else {
	      if (solid[code] == 1) // transp
		Draw16x16_Trans_Rot(&emudx_sprites[corresp_tiles[code]<<(8+bpp)],x,sy,0);
	      else
		Draw16x16_Rot(&emudx_sprites[corresp_tiles[code]<<(8+bpp)],x,sy,0);
	    }
	  }
	  else if((((code+3)&3)==3)) {
	    /* We can't do the replacement of the chars by the sprites like what emudx
	       does (x-24,y-24) because it's incompatible with screen rotation.
	       So the test ((code+3)&3)==3 is here to detect the upper left corner of
	       the big tile (formed by 4 16x16 tiles) instead of the lower right corner
	       in emudx */
	    if(code>135 && code<156)
	      {
		  if (bpp == 1)
		      Draw32x32_Trans_Alpha50_16_flip_Rot(&emudx_sprites32[(code/4)<<(10+bpp)],x,sy,0,0);
		  else if (bpp == 2)
		      Draw32x32_Trans_Alpha50_32_flip_Rot(&emudx_sprites32[(code/4)<<(10+bpp)],x,sy,0,0);
		continue;
	      }
	    else
	      {
		Draw32x32_Trans_flip_Rot(&emudx_sprites32[(code/4)<<(10+bpp)],x,sy,0,0);
		continue;
	      }
	  }
	}
      }
    }
  }

  if( check_layer_enabled(layer_id_data[1])) {
    int offs;
    UINT8 color;
    solid = gfx_solid[1];

    for (offs = 0x20 - 4;offs >= 0;offs -= 4) {
      UINT8 sx,sy;
      int flipx,flipy,code;

      sx = spriteram[offs + 3] + 1; /* the existence of +1 is supported by a LOT of games */
      sy = spriteram[offs];			/* Anteater, Mariner, for example */
      flipx = spriteram[offs + 1] & 0x40;
      flipy = spriteram[offs + 1] & 0x80;
      code = spriteram[offs + 1] & 0x3f;
      color = spriteram[offs + 2] & 7;

      if (romset == 0) {
	color = ((color >> 1) & 0x03) | ((color << 2) & 0x04); // frogger modify
	sy = ((sy << 4) | (sy >> 4)); // frogger modify
      }
      /* Notice : flip_screen_x and flip_screen_y are not yet handled for the layer.
	 Not sure if it's usefull or not */
      if (*flip_screen_x & 1) {
	sx = 240 - sx;
	flipx = !flipx;
      }

      if (*flip_screen_y & 1) {
	flipy = !flipy;
      } else {
	sy = 240 - sy;
      }

      if (solid[code]) {
/* 	MAP_PALETTE_MAPPED_NEW( */
/* 			       color, */
/* 			       4, */
/* 			       map */
/* 			       ); */
	if (sy >= 8 && sy <= 8+224) {
	  x = sx*2 + BORDER;
	  y = (sy-16)*2 + BORDER;
	  if (x>=0 && y>=0) {
	    if(code>33 && code<37) {
		if (bpp == 1)
		    Draw32x32_Trans_Alpha50_16_flip_Rot(&emudx_sprites32[(code)<<(10+bpp)],x,y,0,(flipx ? 1 : 0) | (flipy?2:0));
		else if (bpp == 2)
		    Draw32x32_Trans_Alpha50_32_flip_Rot(&emudx_sprites32[(code)<<(10+bpp)],x,y,0,(flipx ? 1 : 0) | (flipy?2:0));
	    } else {
	      if (solid[code] == 1) { // transp
		if (color==2 && (code>27 && code<34)) code +=36;
		Draw32x32_Trans_flip_Rot(&emudx_sprites32[code<<(10+bpp)],x,y,0,(flipx ? 1 : 0) | (flipy?2:0));
	      } else {// solid
		if (color==2 && (code>27 && code<34)) code +=36;

		Draw32x32_flip_Rot(&emudx_sprites32[code<<(10+bpp)],x,y,0,(flipx ? 1 : 0) | (flipy?2:0));
	      }
	    }
	  }
	}
      }
    }
  }
}

static int playing_theme;

static void draw_emudx_gal() {
  UINT8 color;
  UINT16 code;
  int x,y,zzzz,zz;
  UINT8 *solid;

  if (gfx_ram[0x194] == 30) {
    if (!playing_theme) {
      playing_theme = 1;
      raine_play_sample(theme,255);
    }
  } else {
    playing_theme = 0;
  }

  if (RefreshBuffers) {
      setup_gal_pal();
      bpp = display_cfg.bpp/16;
  }

#ifdef RAINE_DEBUG
  if (input_buffer[8] & 8) {
    draw_debug_layer();
    return;
  }
#endif

  if (*stars_enable) {
    blit(emudx_tiles[0], GameBitmap, 0, 0, BORDER, BORDER, 448, 512);
    // Make sure the fps counter is visible
    switch(raine_cfg.show_fps_mode) {
    case 1:
    case 2: rectfill(GameBitmap, BORDER+224*2-9*6,BORDER, BORDER+224*2, BORDER+8,0);
      break;
    case 3:
    case 4:
      rectfill(GameBitmap,BORDER+224*2-10*6,BORDER, BORDER+224*2, BORDER+8*7,0);
      break;
    }
  } else
    clear_bitmap(GameBitmap);

  if( check_layer_enabled(layer_id_data[0])) {
    solid = gfx_solid[0];

    /* No scroll register for this layer (0,0) */
    zzzz=0;

    /* These complex looking lines are just the unrolling of START_SCROLL_8(BORDER,BORDER,256,224)
       + the line scroll handling between the fors */

    zz=zzzz;
    for(x=(BORDER);(UINT32)x<(256*2+BORDER);x+=16){
      int coffs = attributes[(x-BORDER)/16*2];
      int xoffs=0;

      if (coffs) { // don't touch that : these offsets are inteded for 8x8 sprites !
	xoffs = (coffs&7);
	coffs /= 8;
      }

      for(y=(int)(0-xoffs);(int)y<(256-xoffs);y+=8){
	int sy;
	if (y<0) continue;
	zz = ((((y+xoffs)/8)+coffs)&31)*32+(x-BORDER)/16; // direct access (ignores scrollx, scrolly)
	code = gfx_ram[zz];
	color = attributes[((zz & 0x1f) << 1) | 1];

	if (solid[code]) {
	  sy = (y-8)*2 +BORDER-16; // convert to 16x16
	  if (y<0) continue;
		if(code==49 || code==51 || code==53 || (code>54 && code<96))
		{
		  UINT16 code0 = code;
		  /* The aliens - there already available in different colors
		   * from the emudx files -> draw directly (no palette) */

			if(color==3)
				code+=224;
			if(color==4)
				code+=280;
			code = corresp_tiles[code];
			if (solid[code0] == 1) // transp
			  Draw16x16_Trans_Rot(&emudx_sprites[code<<(8+bpp)],x,sy,0);
			else
			  Draw16x16_Rot(&emudx_sprites[code<<(8+bpp)],x,sy,0);
		} else {
		  /* The other stuff, including some blended letters which look
		   * good this time ! */
		  if (solid[code] == 1) // transp
		    Draw16x16_Trans_Rot(&emudx_sprites[corresp_tiles[code]<<(8+bpp)],x,sy,0);
		  else
		    Draw16x16_Rot(&emudx_sprites[corresp_tiles[code]<<(8+bpp)],x,sy,0);
		}

		if(code==193) raine_play_sample(explode,200);
	}
      }
    }
  }

  { // bullets
    int offs;
    for (offs = 0;offs < 0x20;offs += 4)
    {
      UINT16 sx,sy,sprite;

      sy = 255 - bulletsram[offs + 1];
      sx = 255 - bulletsram[offs + 3];

      if (sy < 16 ||
	  sy > 240)
	continue;

      if (*flip_screen_y) {
	sy = 255 - sy;
      }

#define ebullet 391
#define sbullet 392

      sprite = ((offs == 7*4) ? ebullet : sbullet);
      Draw16x16_Trans_Rot(&emudx_sprites[sprite<<(8+bpp)],sx*2+BORDER-16,sy*2+BORDER-48+3,0);
    }
  }

  if( check_layer_enabled(layer_id_data[1])) {
    int offs;
    UINT8 color;
    solid = gfx_solid[1];

    for (offs = 0x20 - 4;offs >= 0;offs -= 4) {
      UINT8 sx,sy;
      int flipx,flipy,code;

      sx = spriteram[offs + 3] + 1; /* the existence of +1 is supported by a LOT of games */
      sy = spriteram[offs];			/* Anteater, Mariner, for example */
      flipx = spriteram[offs + 1] & 0x40;
      flipy = spriteram[offs + 1] & 0x80;
      code = spriteram[offs + 1] & 0x3f;
      color = spriteram[offs + 2] & 7;

      /* Notice : flip_screen_x and flip_screen_y are not yet handled for the layer.
	 Not sure if it's usefull or not */
      if (*flip_screen_x & 1) {
	sx = 240 - sx;
	flipx = !flipx;
      }

      if (*flip_screen_y & 1) {
	flipy = !flipy;
      } else {
	sy = 240 - sy;
      }

      if (solid[code]) {
	int sol = solid[code];
/* 	MAP_PALETTE_MAPPED_NEW( */
/* 			       color, */
/* 			       4, */
/* 			       map */
/* 			       ); */
	if (sy >= 8 && sy <= 8+224) {
	  x = sx*2 + BORDER;
	  y = (sy-16)*2 + BORDER;
	  if (x>=0 && y>=0) {
	    if(code>13 && code<24)
	    {
	      if(color==3) code+=56;
	      if(color==4) code+=70;
	    }

	    if (sol == 1) { // transp
	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[code<<(10+bpp)],x,y,0,(flipx ? 1 : 0) | (flipy?2:0));
	    } else {// solid
	      Draw32x32_flip_Rot(&emudx_sprites32[code<<(10+bpp)],x,y,0,(flipx ? 1 : 0) | (flipy?2:0));
	    }
	    if (code == 28)
	      raine_play_sample(hit,255);
	  }
	}
      }
    }
  }
}

static UINT8 *ram_hiscores;

static char *myget_filename() {
  static char str[1024];
  snprintf(str,1024,"%ssavedata" SLASH "%s.ram", dir_cfg.exe_path, current_game->main_name);
  return str;
}

static void clear_frogger() {
  if (is_current_game("froggs")) { // save permanent ram
    FILE *f = fopen(myget_filename(),"wb");
    if (f) {
      fwrite(ram_hiscores,0x20,1,f);
      fclose(f);
    }
  }
}

static void shot_enable_w(UINT32 offset, UINT16 data) {
  static int shot_playing;
  if (data == 1) {
    if (!shot_playing) {
      raine_play_sample(shot,255);
      shot_playing = 1;
    }
  } else
    shot_playing = 0;
}

static void load_frogger() {
  UINT8 *color_prom = load_region[REGION_PROMS],*decode1,*decode2,*ram2,*rom2 = load_region[REGION_CPU2];
  int i;
  UINT32 dest_size;

  if (!strncmp(current_game->main_name,"frogg",5)) {
    /* the first ROM of the second CPU has data lines D0 and D1 swapped. Decode it. */
    ROM = load_region[REGION_CPU2];
    for (i = 0;i < 0x0800;i++)
      ROM[i] = BITSWAP8(ROM[i],7,6,5,4,3,2,0,1);

    /* likewise, the 2nd gfx ROM has data lines D0 and D1 swapped. Decode it. */
    ROM = load_region[REGION_GFX1];
    for (i = 0x0800;i < 0x1000;i++)
      ROM[i] = BITSWAP8(ROM[i],7,6,5,4,3,2,0,1);

    ROM = load_region[REGION_CPU1];
  }
  RAMSize = 0x800 + 0x400 + 0x100 + 10 + 0x400 +
  0x21 + 2 + // hiscore enhancenments
  1; // stars enable
  if (!(RAM = AllocateMem(RAMSize))) return;

  gfx_ram = RAM+0x800;
  attributes = gfx_ram + 0x400;
  spriteram = attributes + 0x40;
  bulletsram = spriteram + 0x20;

  nmi_enable = RAM + 0x800 + 0x400 + 0x100;
  flip_screen_x = nmi_enable + 1;
  flip_screen_y = nmi_enable + 2;
  ram2 = flip_screen_y + 1;
  ram_hiscores = ram2 + 0x400;
  stars_enable = ram_hiscores + 0x23;

  AddZ80AROMBase(ROM, 0x0038, 0x0066); // ???!
  if (!strncmp(current_game->main_name,"frogg",5)) {
    romset = 0;
    AddZ80ARead(0x0000, 0x3fff, NULL, ROM);
    AddZ80ARW(0x8000, 0x87ff, NULL, RAM);
    AddZ80ARW(0xa800, 0xabff, NULL, gfx_ram);
    AddZ80ARW(0xb000, 0xb0ff, NULL, attributes);

    AddZ80AWrite(0xb808, 0xb808, NULL, nmi_enable);
    AddZ80AWrite(0xb80c, 0xb80c, NULL, flip_screen_y);
    AddZ80AWrite(0xb810, 0xb810, NULL, flip_screen_x);
    AddZ80AWrite(0xd000, 0xd000, frogger_sound_w, NULL);

    /* I test inputs using the very much simplified method of emudx instead of the
       "emulate everything" method of mame. Hope I won't need anything from mame here. */
    AddZ80ARead(0xe000, 0xe004, NULL, input_buffer);

    // sound z80
    AddZ80BROMBase(rom2, 0x0038, 0x0066); // ???!
    AddZ80BRead(0x0000, 0x1fff, NULL, rom2);
    AddZ80BRW(0x4000, 0x43ff, NULL, ram2);
    AddZ80BRead(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
    AddZ80BWrite(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);

    AddZ80BReadPort(0x40, 0x40, AY8910_read_port_0_r,	NULL);	// <bad reads>
    AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);	// <bad reads>
    AddZ80BReadPort(-1, -1, NULL, NULL);

    AddZ80BWritePort(0x40, 0x40, AY8910_write_port_0_w,	NULL);	// Trap Idle Z80
    AddZ80BWritePort(0x80, 0x80, AY8910_control_port_0_w,	NULL);	// Trap Idle Z80
    AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);	// <bad reads>
    AddZ80BWritePort(-1, -1, NULL, NULL);
    AddZ80BInit();

  } else {
    // Galaxian
    romset = 1;
    AddZ80ARead(0x0000, 0x3fff, NULL, ROM);
    AddZ80ARW(0x4000, 0x47ff, NULL, RAM);
    AddZ80ARW(0x5000, 0x53ff, NULL, gfx_ram);
    AddZ80ARW(0x5800, 0x58ff, NULL, attributes);

    AddZ80AWrite(0x7001, 0x7001, NULL, nmi_enable);
    AddZ80AWrite(0x7006, 0x7006, NULL, flip_screen_x);
    AddZ80AWrite(0x7007, 0x7007, NULL, flip_screen_y);
    AddZ80AWrite(0x7004, 0x7004, NULL, stars_enable);
    AddZ80AWrite(0xd000, 0xd000, frogger_sound_w, NULL);

    AddZ80ARead(0x6000, 0x6000, NULL, input_buffer);
    // AddZ80AWrite(0x6004, 0x6007, galaxian_lfo_freq_w, NULL);
    AddZ80ARead(0x6800, 0x6800, NULL, &input_buffer[2]);
    AddZ80AWrite(0x6805, 0x6805, shot_enable_w, NULL);
    AddZ80ARead(0x7000, 0x7000, NULL, &input_buffer[4]);
  }

  if (is_current_game("froggs")) {
    // hiscores enhancements (froggs roms)
    AddZ80ARW(0x7000, 0x7020, NULL, ram_hiscores);
    AddZ80ARead(0x7100, 0x7101, NULL, ram_hiscores+0x21);
    ram_hiscores[0x21] = 0x4a;
    ram_hiscores[0x22] = 0x52;
    FILE *f = fopen(myget_filename(),"rb");
    if (f) {
      fread(ram_hiscores,0x20,1,f);
      fclose(f);
    }
  }

  AddZ80ARead(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
  AddZ80AWrite(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadPortZ80,			NULL);	// <bad reads>
  AddZ80AReadPort(-1, -1, NULL, NULL);

  AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,			NULL);	// Trap Idle Z80
  AddZ80AWritePort(0x00, 0xFF, DefBadWritePortZ80,			NULL);	// <bad reads>
  AddZ80AWritePort(-1, -1, NULL, NULL);
  AddZ80AInit();

/***************************************************************************

  Convert the color PROMs into a more useable format.

  Galaxian has one 32 bytes palette PROM, connected to the RGB output this way:

  bit 7 -- 220 ohm resistor  -- BLUE
        -- 470 ohm resistor  -- BLUE
        -- 220 ohm resistor  -- GREEN
        -- 470 ohm resistor  -- GREEN
        -- 1  kohm resistor  -- GREEN
        -- 220 ohm resistor  -- RED
        -- 470 ohm resistor  -- RED
  bit 0 -- 1  kohm resistor  -- RED

  The output of the background star generator is connected this way:

  bit 5 -- 100 ohm resistor  -- BLUE
        -- 150 ohm resistor  -- BLUE
        -- 100 ohm resistor  -- GREEN
        -- 150 ohm resistor  -- GREEN
        -- 100 ohm resistor  -- RED
  bit 0 -- 150 ohm resistor  -- RED

  The blue background in Scramble and other games goes through a 390 ohm
  resistor.

  The bullet RGB outputs go through 100 ohm resistors.

  The RGB outputs have a 470 ohm pull-down each.

***************************************************************************/
  for (i=0; i<get_region_size(REGION_PROMS); i++) {
    int red = (color_prom[i] & 7);
    int green = (color_prom[i] & 0x38) >> 3;
    int blue = (color_prom[i] & 0xc0) >> 5;
    mypal[i] = (blue) | (green<<3) | (red<<6);
  }
  mypal[i] = 0;
  mypal[i+1] = 2; // background color for half top of the screen
  // bullets
  mypal[i+2] = 0 | (7<<3) | (7<<6); // yellow
  mypal[i+3] = 7 | (7<<3) | (7<<6); // white
  // stars
  i+=4;
  *stars_enable = 0;
  stars_blink_state = 0;
  stars_colors_start = i;

  for (i = 0;i < 64;i++)
  {
    int bits,r,g,b;
    const int map[4] = { 0x00, 0x4, 0x6, 0x7 };


    bits = (i >> 0) & 0x03;
    r = map[bits];
    bits = (i >> 2) & 0x03;
    g = map[bits];
    bits = (i >> 4) & 0x03;
    b = map[bits];
    mypal[stars_colors_start + i] = b | (g<<3) | (r<<6);
  }

  // pre-calculate stars position. I wonder how mame came with this code...
  int total_stars = 0;
  int generator = 0;
  int x,y;

  for (y = 0;y < 256;y++)
  {
    for (x = 0;x < 512;x++)
    {
      UINT32 bit0;


      bit0 = ((~generator >> 16) & 0x01) ^ ((generator >> 4) & 0x01);

      generator = (generator << 1) | bit0;

      if (((~generator >> 16) & 0x01) && (generator & 0xff) == 0xff)
      {
	int color;


	color = (~(generator >> 8)) & 0x3f;
	if (color)
	{
	  stars[total_stars].x = x;
	  stars[total_stars].y = y;
	  stars[total_stars].color = color;

	  total_stars++;
	}
      }
    }
  }

  InitPaletteMap((UINT8*)mypal, (8+1+16), 4, 0x200); // 8 banks of 4 colors each : extreme !!! + 1 for bg/bullets, +16 for stars
  set_colour_mapper(&col_map_xxxxRrrgggbbb);
  layer_id_data[0] = add_layer_info(gettext("BG"));
  layer_id_data[1] = add_layer_info(gettext("SPRITES"));

  // The wicked layouts
  load_region[REGION_GFX2] = copy_sprites(load_region[REGION_GFX1]);
  decode1 = decode_gfx(load_region[REGION_GFX1],0x1000,&galaxian_charlayout,&dest_size);
  gfx_solid[0] = make_solid_mask_8x8(decode1,dest_size/64);
  decode2 = decode_gfx(load_region[REGION_GFX2],0x1000,&galaxian_spritelayout,&dest_size);
  gfx_solid[1] = make_solid_mask_16x16(decode2,dest_size/0x100);

  FreeMem(load_region[REGION_GFX1]);
  FreeMem(load_region[REGION_GFX2]);
  load_region[REGION_GFX1] = decode1;
  spr = load_region[REGION_GFX2] = decode2;

  ay8910_amplify = 8;
  if (romset == 0) { // frogger
      if (!exists_emudx_file("froggerm.dx2")) {
#ifndef SDL
	  raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("Without froggerm.dx2 you will have no sound"),NULL,raine_translate_text("&Ok"),NULL,'O',0);
#else
	  MessageBox(gettext("EmuDX"),gettext("Without froggerm.dx2 you will have no sound"),gettext("Ok"));
#endif
      }
      if (exists_emudx_file("froggerg.dx2")) {
#ifndef SDL
      if((raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("EmuDX support?"),NULL,raine_translate_text("&Yes"),raine_translate_text("&No"),'Y','N'))==1)
#else
	if(MessageBox(gettext("EmuDX"),gettext("EmuDX support ?"),gettext("Yes|No")) == 1)
#endif
	{
	  load_emudx("froggerg.dx2",1,280,282,351,
	      0,0, // no chars here, they seem to have coloured tiles for the chars
	      448,512,makecol(0xff,0,0xff),draw_emudx);
	  setup_frog_gfx();
	  draw_emudx_tile = 0;
	}
    }
  } else { // galaxian
    if (exists_emudx_file("galdxg.dx2")) {
#ifndef SDL
      if((raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("EmuDX support?"),NULL,raine_translate_text("&Yes"),raine_translate_text("&No"),'Y','N'))==1)
#else
	if(MessageBox(gettext("EmuDX"),gettext("EmuDX support ?"),gettext("Yes|No")) == 1)
#endif
	{
	  load_emudx("galdxg.dx2",1,393,395,488,
	      0,0, // no chars here, they seem to have coloured tiles for the chars
	      448,512,makecol(0xff,0,0xff),draw_emudx_gal);
	  setup_gal_gfx();
	}
    }
  }
}

#define BULLETS_COLOR_BASE (2)

static void galaxian_draw_bullets(int offs, int x, int y,UINT8 *map)
{
  int i;

  int color;
  color = ((offs == 7*4) ? BULLETS_COLOR_BASE : BULLETS_COLOR_BASE + 1);
  /* yellow missile, white shells (this is the terminology on the schematics) */
  switch(display_cfg.bpp) {
    case 8:
      color = map[color];
      for (i = 0; i < 4; i++)
      {
	x--;
	*(GameBitmap->line[x]+y) = color;
      }
      break;
    case 15:
    case 16:
      color = ReadWord(&map[color*2]);
      for (i = 0; i < 4; i++)
      {
	x--;
	WriteWord(GameBitmap->line[x]+y*2,color);
      }
      break;
    case 32:
      color = ReadLong(&map[color*4]);
      for (i = 0; i < 4; i++)
      {
	x--;
	WriteLong(GameBitmap->line[x]+y*4,color);
      }
      break;
  }
}

static void draw_frogger() {
  /* The only difficulty here is the row/col scroll of the layer (since the screen is
     rotated you call it either col or row scroll ! */

  UINT8 code, color;
  int x,y,zzzz,zz;
  UINT8 *map,*solid;
  int coul1, coul2;
  UINT8 *gfx = load_region[REGION_GFX1];
  static UINT8 *map_bg, *map_stars;

  if (RefreshBuffers) {
    setup_frogger_pal();
    // background color
    MAP_PALETTE_MAPPED_NEW(
	8,
	4,
	map_bg
	);
    MAP_PALETTE_MULTI_MAPPED_NEW(
	9,
	64,
	map_stars
	);
  }

  if (romset == 0) {
    /* The screen is split by 2 bands of colour. These colors are not actually drawn by
       the game, but it was verified on the original hardware (as mentioned in the mame
       driver) */
    switch(display_cfg.bpp) {
      case 8: coul1 = map_bg[0]; coul2 = map_bg[1]; break;
      case 15:
      case 16: coul1 = ReadWord(&map_bg[0]); coul2 = ReadWord(&map_bg[2]); break;
      default: coul1 = ReadLong(&map_bg[0]); coul2 = ReadLong(&map_bg[4]); break;
    }
    rectfill(GameBitmap,BORDER,BORDER,BORDER+224,BORDER+256/2,coul2);
    rectfill(GameBitmap,BORDER,BORDER+256/2,BORDER+224,BORDER+256,coul1);
  } else { // galaxian
    clear_bitmap(GameBitmap);

    if (gfx_ram[0x194] == 30) {
      if (!playing_theme) {
	playing_theme = 1;
	raine_play_sample(theme,255);
      }
    } else {
      playing_theme = 0;
    }

    if (*stars_enable) {
      int offs;
      for (offs = 0;offs < STARS_COUNT;offs++)
      {
	int x,y;


	x = ((stars[offs].x +   stars_scrollpos) & 0x01ff) >> 1;
	y = ( stars[offs].y + ((stars_scrollpos + stars[offs].x) >> 9)) & 0xff;

	if ((y & 0x01) ^ ((x >> 3) & 0x01))
	{
	  if (x >= 0 && x <= 256 && y >= 0 && y <= 224) {
	    x += BORDER;
	    y += BORDER;
	    switch(display_cfg.bpp) {
	      case 8:
		*(GameBitmap->line[x]+y) = map_stars[stars[offs].color]; break;
	      case 15:
	      case 16:
		WriteWord(GameBitmap->line[x]+y*2,ReadWord(&map_stars[stars[offs].color*2])); break;
	      case 32:
		WriteLong(GameBitmap->line[x]+y*4,ReadLong(&map_stars[stars[offs].color*4])); break;
	    }
	  }
	}
      }
      stars_scrollpos++;
    }
  }

  if( check_layer_enabled(layer_id_data[0])) {
    solid = gfx_solid[0];

    /* No scroll register for this layer (0,0) */
    zzzz = 0;

    /* These complex looking lines are just the unrolling of START_SCROLL_8(BORDER,BORDER,256,224)
       + the line scroll handling between the fors */

    zz=zzzz;
    for(x=(BORDER);(UINT32)x<(256+BORDER);x+=8){
      int coffs = attributes[(x-BORDER)/8*2];
      int xoffs=0;

      /* In fact it's not a true line scroll it would rather be some sort of "character"
	 scroll, which means that the offset is applied to the whole character line (8
	 pixels). As such, we can just change the offset, without calling the ldraw
	 functions which become unnecessary here ! The offset is in pixels though, not in
	 characters, so we compute an intermediate xoffs...
	 It's more like changing the layer scroll offset every 8 pixels or every row */

      if (coffs) {
	if (romset == 0)
	  coffs = ((coffs << 4) | (coffs >> 4)) & 0xff; // frogger modify
	xoffs = (coffs&7);
	coffs /= 8;
      }

      for(y=(int)(8-xoffs);(int)y<(224+24-xoffs);y+=8){
	zz = ((((y+xoffs)/8)+coffs)&31)*32+(x-BORDER)/8; // direct access (ignores scrollx, scrolly)
	code = gfx_ram[zz];

	if (solid[code]) {
	  color = attributes[((zz & 0x1f) << 1) | 1];
	  if (romset == 0)
	    color = ((color >> 1) & 0x03) | ((color << 2) & 0x04); // frogger modify
	  MAP_PALETTE_MAPPED_NEW(
				 color,
				 4,
				 map
				 );

	  if(code==193 && romset) raine_play_sample(explode,200);
	  if (solid[code] == 1) // transp
	    Draw8x8_Trans_Mapped_Rot(&gfx[code<<6],x,y+BORDER-16,map);
	  else
	    Draw8x8_Mapped_Rot(&gfx[code<<6],x,y+BORDER-16,map);
	}
      }
    }
  }

  if (romset == 1) {
    int offs;
    for (offs = 0;offs < 0x20;offs += 4)
    {
      UINT16 sx,sy;

      sy = 255 - bulletsram[offs + 1];
      sx = 255 - bulletsram[offs + 3];

      if (sy < 16 ||
	  sy > 240)
	continue;

      if (!*flip_screen_y) {
	sy = 255 - sy;
      }

      galaxian_draw_bullets( offs, sx+BORDER, sy+BORDER-16, map_bg);
    }
  }

  if( check_layer_enabled(layer_id_data[1])) {
    solid = gfx_solid[1];
    int offs;
    for (offs = 0x20 - 4;offs >= 0;offs -= 4) {
      UINT8 sx,sy,color;
      int flipx,flipy,code;

      sx = spriteram[offs + 3] + 1; /* the existence of +1 is supported by a LOT of games */
      sy = spriteram[offs];			/* Anteater, Mariner, for example */
      flipx = spriteram[offs + 1] & 0x40;
      flipy = spriteram[offs + 1] & 0x80;
      code = spriteram[offs + 1] & 0x3f;
      if (romset == 0)
	sy = ((sy << 4) | (sy >> 4)); // frogger modify
      /* Notice : flip_screen_x and flip_screen_y are not yet handled for the layer.
	 Not sure if it's usefull or not */
      if (*flip_screen_x & 1) {
	sx = 240 - sx;
	flipx = !flipx;
      }

      if (*flip_screen_y & 1) {
	flipy = !flipy;
      } else {
	sy = 240 - sy;
      }

      if (solid[code]) {
	color = spriteram[offs + 2] & 7;

	if (romset == 0)
	  color = ((color >> 1) & 0x03) | ((color << 2) & 0x04); // frogger modify
	MAP_PALETTE_MAPPED_NEW(
			       color,
			       4,
			       map
			       );
	if (code == 28 && romset) // galaxian
	  raine_play_sample(hit,255);
	if (solid[code] == 1) // transp
	  Draw16x16_Trans_Mapped_flip_Rot(&spr[code<<8],sx+BORDER,sy+BORDER-16,map,(flipx ? 1 : 0) | (flipy?2:0));
	else // solid
	  Draw16x16_Mapped_flip_Rot(&spr[code<<8],sx+BORDER,sy+BORDER-16,map,(flipx ? 1 : 0) | (flipy?2:0));
      }
    }
  }
}

static struct VIDEO_INFO video_frogger =
{
   draw_frogger,
   256,
   224,
   BORDER,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   NULL, // no automatic region decoding
};

/* #define SLICES 48 */

static void execute_frogger() {
  cpu_execute_cycles(CPU_Z80_0,3072000/60);
  if (*nmi_enable) {
    cpu_int_nmi(CPU_Z80_0);
  }

  // Get an irq by the main cpu for each new sound command
  // so the frequency of the cpu determines music speed. This one is taken from mame
  cpu_execute_cycles(CPU_Z80_1,1789750/60);
}

static void execute_galaxian() {
  static int hs_loaded;
  cpu_execute_cycles(CPU_Z80_0,3072000/60);
  if (*nmi_enable) {
    cpu_int_nmi(CPU_Z80_0);
    if (!hs_loaded) {
      /* For some reason, the hiscore detection of hiscore.dat doesn't work :
       * it detects it can load the hiscores, then this ram location is cleared
       * again by the game ! If it works in mame, then it means it doesn't
       * execute the same number of cycles before updating the hiscores.
       * Anyway, there are 2 ways to fix this : the hard one, patching the rom
       * code to avoid to clear this twice, or the easy one here, just load the
       * hiscores when the interrupts start, and not before. */
      hs_load();
      hs_loaded = 1;
    }
  } else
    hs_loaded = 0;
}

GMEI( frogger,
     "Frogger",
     KONAMI,
     1981,
     GAME_MISC);
CLNEI( froggs, frogger, "Frogger enhanced hiscore", BOOTLEG,2001,GAME_MISC,
	.clear = clear_frogger);
#define load_galaxian load_frogger
#define video_galaxian video_frogger
GMEI( galaxian,
     "Galaxian (Namco set 1)",
     NAMCO,
     1979,
     GAME_SHOOT);
CLNEI(superg, galaxian, "Super galaxians (hack)", BOOTLEG, 1979, GAME_SHOOT,
	.dsw = dsw_superg);
CLNEI(galapx, galaxian, "Galaxian Part X", BOOTLEG, 1979, GAME_SHOOT,
	.dsw = dsw_superg);

