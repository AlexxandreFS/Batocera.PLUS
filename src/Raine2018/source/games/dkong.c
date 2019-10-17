#include "gameinc.h"
#include "decode.h"
#include "dkongm.h"
#include "sasound.h"
#include "emudx.h"
#include "blit.h"
#include "cpuid.h"
#include "profile.h"
#include "emumain.h" // set_reset_function
#include "dxsmp.h"
#include "savegame.h"
#ifdef SDL
#include "sdl/dialogs/messagebox.h"
// disable draw_trans_sprite for now
#define draw_trans_sprite(dst,src,x,y)
#endif

#define MASKRED 0xF800
#define MASKGREEN 0x07E0
#define MASKBLUE 0x1F

extern int disp_y_32;

#if 0
// Attempt to emulate the draw_trans_sprite combined with set_screen_blender effect.
// Still not perfect. Using allegro for now...
static void my_draw_alpha(UINT16 *src, int x, int y) {
  UINT32 sred,sgreen,sblue, dred,dgreen,dblue,dx,dy;
  UINT16 *dest;
  dx = disp_y_32 - y;
  y = x;
  x = dx;
  for (dy=0; dy<32; dy++) {
    dest = ((UINT16*)GameBitmap->line[dy+y])+x;
    for (dx=0; dx<32; dx++) {
      UINT32 val = *src++;
      if (val != emudx_transp) {
	// val = *dest;
	sred = (val & MASKRED)>> 8;
	sgreen = (val & MASKGREEN)>>3;
	sblue = (val & MASKBLUE)<<3;
	dred = (*dest & MASKRED)>>8;
	dgreen = (*dest & MASKGREEN)>>3;
	dblue = (*dest & MASKBLUE)<<3;
	sred = 255 - ((255 - sred) * (255 - dred))/256;
	sgreen = 255 - ((255 - sgreen) * (255 - dgreen))/256;
	sblue = 255 - ((255 - sblue) * (255 - dblue))/256;
	*dest++ = ((sred>>3)<<11) | ((sgreen>>2)<<5) | ((sblue>>3));
      } else
	dest++;
    }
  }
}
#endif

struct dxsmpinterface dkong_emudx_interface =
  {
    "dkongm.dx2",
    YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT)
  };

static struct SOUND_INFO sound_dkong[] =
{
  { SOUND_DXSMP, &dkong_emudx_interface, },
  { 0, NULL },
};

// defined in rgui.c for allegro, but it should be generic...
extern int raine_alert(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, int c1, int c2);

static struct ROM_INFO rom_dkong[] =
{
  { "c_5et_g.bin", 0x1000, 0xba70b88b, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "c_5ct_g.bin", 0x1000, 0x5ec461ec, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "c_5bt_g.bin", 0x1000, 0x1c97d324, REGION_ROM1, 0x2000, LOAD_NORMAL },
	/* space for diagnostic ROM */
  { "c_5at_g.bin", 0x1000, 0xb9005ac0, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "s_3i_b.bin", 0x0800, 0x45a4ed06, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "s_3j_b.bin", 0x0800, 0x4743fe92, REGION_ROM2, 0x0800, LOAD_NORMAL },
  { "v_5h_b.bin", 0x0800, 0x12c8c95d, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "v_3pt.bin", 0x0800, 0x15e9c5e9, REGION_GFX1, 0x0800, LOAD_NORMAL },
  { "l_4m_b.bin", 0x0800, 0x59f8054d, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "l_4n_b.bin", 0x0800, 0x672e4714, REGION_GFX2, 0x0800, LOAD_NORMAL },
  { "l_4r_b.bin", 0x0800, 0xfeaa59ee, REGION_GFX2, 0x1000, LOAD_NORMAL },
  { "l_4s_b.bin", 0x0800, 0x20f2ef7e, REGION_GFX2, 0x1800, LOAD_NORMAL },
  { "c-2k.bpr", 0x0100, 0xe273ede5, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "c-2j.bpr", 0x0100, 0xd6412358, REGION_PROMS, 0x0100, LOAD_NORMAL },
  { "v-5e.bpr", 0x0100, 0xb869b8f5, REGION_PROMS, 0x0200, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dkongex[] =
{
  { "cx_5et_g.bin", 0x1000, 0x00b7efaf, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "cx_5ct_g.bin", 0x1000, 0x88af9b69, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "cx_5bt_g.bin", 0x1000, 0xde74ad91, REGION_ROM1, 0x2000, LOAD_NORMAL },
	/* space for diagnostic ROM */
  { "cx_5at_g.bin", 0x1000, 0x9fa3e5b7, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dkongjp[] =
{
  { "c_5f_b.bin", 0x1000, 0x424f2b11, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "5g.cpu", 0x1000, 0xd326599b, REGION_ROM1, 0x1000, LOAD_NORMAL },
  { "5h.cpu", 0x1000, 0xff31ac89, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "c_5k_b.bin", 0x1000, 0x394d6007, REGION_ROM1, 0x3000, LOAD_NORMAL },
  { "v_5h_b.bin", 0x0800, 0x12c8c95d, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "v_5k_b.bin", 0x0800, 0x3684f914, REGION_GFX1, 0x0800, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

/*
static struct ROM_INFO rom_dkongjr[] =
{
  { "dkj.5b", 0x2000, 0xdea28158, REGION_ROM1, 0, LOAD_NORMAL },
  { "dkj.5c", 0x2000, 0x6fb5faf6, REGION_ROM1, 0, LOAD_NORMAL },
  { "dkj.5e", 0x2000, 0xd042b6a8, REGION_ROM1, 0, LOAD_NORMAL },
  { "c_3h.bin", 0x1000, 0x715da5f8, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "dkj.3n", 0x1000, 0x8d51aca9, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "dkj.3p", 0x1000, 0x4ef64ba5, REGION_GFX1, 0x1000, LOAD_NORMAL },
  { "v_7c.bin", 0x0800, 0xdc7f4164, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "v_7d.bin", 0x0800, 0x0ce7dcf6, REGION_GFX2, 0x0800, LOAD_NORMAL },
  { "v_7e.bin", 0x0800, 0x24d1ff17, REGION_GFX2, 0x1000, LOAD_NORMAL },
  { "v_7f.bin", 0x0800, 0x0f8c083f, REGION_GFX2, 0x1800, LOAD_NORMAL },
  { "c-2e.bpr", 0x0100, 0x463dc7ad, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "c-2f.bpr", 0x0100, 0x47ba0042, REGION_PROMS, 0x0100, LOAD_NORMAL },
  { "v-2n.bpr", 0x0100, 0xdbf185bf, REGION_PROMS, 0x0200, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_dkong3[] =
{
  { "dk3c.7b", 0x2000, 0x38d5f38e, REGION_ROM1, 0x0000, LOAD_NORMAL },
  { "dk3c.7c", 0x2000, 0xc9134379, REGION_ROM1, 0x2000, LOAD_NORMAL },
  { "dk3c.7d", 0x2000, 0xd22e2921, REGION_ROM1, 0x4000, LOAD_NORMAL },
  { "dk3c.7e", 0x2000, 0x615f14b7, REGION_ROM1, 0x8000, LOAD_NORMAL },
  { "dk3c.5l", 0x2000, 0x7ff88885, REGION_ROM2, 0xe000, LOAD_NORMAL },
  { "dk3c.6h", 0x2000, 0x36d7200c, REGION_CPU3, 0xe000, LOAD_NORMAL },
  { "dk3v.3n", 0x1000, 0x415a99c7, REGION_GFX1, 0x0000, LOAD_NORMAL },
  { "dk3v.3p", 0x1000, 0x25744ea0, REGION_GFX1, 0x1000, LOAD_NORMAL },
  { "dk3v.7c", 0x1000, 0x8ffa1737, REGION_GFX2, 0x0000, LOAD_NORMAL },
  { "dk3v.7d", 0x1000, 0x9ac84686, REGION_GFX2, 0x1000, LOAD_NORMAL },
  { "dk3v.7e", 0x1000, 0x0c0af3fb, REGION_GFX2, 0x2000, LOAD_NORMAL },
  { "dk3v.7f", 0x1000, 0x55c58662, REGION_GFX2, 0x3000, LOAD_NORMAL },
  { "dkc1-c.1d", 0x0200, 0xdf54befc, REGION_PROMS, 0x0000, LOAD_NORMAL },
  { "dkc1-c.1c", 0x0200, 0x66a77f40, REGION_PROMS, 0x0100, LOAD_NORMAL },
  { "dkc1-v.2n", 0x0100, 0x50e33434, REGION_PROMS, 0x0200, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};
*/

static struct DSW_DATA dsw_data_dkong_3[] =
{
  { MSG_LIVES, 0x03, 4 },
  { "3", 0x00},
  { "4", 0x01},
  { "5", 0x02},
  { "6", 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { "7000", 0x00},
  { "10000", 0x04},
  { "15000", 0x08},
  { "20000", 0x0c},
  { MSG_COINAGE, 0x70, 8 },
  { MSG_5COIN_1PLAY, 0x70},
  { MSG_4COIN_1PLAY, 0x50},
  { MSG_3COIN_1PLAY, 0x30},
  { MSG_2COIN_1PLAY, 0x10},
  { MSG_1COIN_1PLAY, 0x00},
  { MSG_1COIN_1PLAY, 0x20},
  { MSG_1COIN_3PLAY, 0x40},
  { MSG_1COIN_4PLAY, 0x60},
  { MSG_CABINET, 0x80, 2 },
  { MSG_UPRIGHT, 0x80},
  { MSG_TABLE, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_dkong[] =
{
  { 0x6, 0x80, dsw_data_dkong_3 },
  { 0, 0, NULL }
};

/* static struct DSW_DATA dsw_data_dkong3_2[] =
{
  { MSG_COINAGE, 0x07, 8 },
  { MSG_3COIN_1PLAY, 0x02},
  { MSG_2COIN_1PLAY, 0x04},
  { MSG_1COIN_1PLAY, 0x00},
  { MSG_1COIN_1PLAY, 0x06},
  { MSG_1COIN_3PLAY, 0x01},
  { MSG_1COIN_4PLAY, 0x03},
  { MSG_1COIN_5PLAY, 0x05},
  { MSG_1COIN_6PLAY, 0x07},
  { MSG_UNKNOWN, 0x08, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x08},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x10},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x00},
  { MSG_ON, 0x20},
  { MSG_CABINET, 0x80, 2 },
  { MSG_UPRIGHT, 0x00},
  { MSG_TABLE, 0x80},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_dkong3_3[] =
{
  { MSG_LIVES, 0x03, 4 },
  { "3", 0x00},
  { "4", 0x01},
  { "5", 0x02},
  { "6", 0x03},
  { MSG_EXTRA_LIFE, 0x0c, 4 },
  { "30000", 0x00},
  { "40000", 0x04},
  { "50000", 0x08},
  { MSG_UNKNOWN, 0x0c},
  { _("Additional Bonus"), 0x30, 4 },
  { "30000", 0x00},
  { "40000", 0x10},
  { "50000", 0x20},
  { MSG_UNKNOWN, 0x30},
  { MSG_DIFFICULTY, 0xc0, 4 },
  { MSG_EASY, 0x00},
  { MSG_MEDIUM, 0x40},
  { MSG_HARD, 0x80},
  { MSG_HARDEST, 0xc0},
  { NULL, 0}
};

static struct DSW_INFO dsw_dkong3[] =
{
  { 0x4, 0x00, dsw_data_dkong3_2 },
  { 0x6, 0x00, dsw_data_dkong3_3 },
  { 0, 0, NULL }
};
*/

static struct INPUT_INFO input_dkong[] =
{
  INP1( P1_RIGHT, 0x00, 0x01 ),
  INP1( P1_LEFT, 0x00, 0x02 ),
  INP1( P1_UP, 0x00, 0x04 ),
  INP1( P1_DOWN, 0x00, 0x08 ),
  INP1( P1_B1, 0x00, 0x10 ),
#ifdef RAINE_DEBUG
  INP1( P1_B2, 0x08, 0x8 ),
#endif

  INP1( P2_RIGHT, 0x02, 0x01 ),
  INP1( P2_LEFT, 0x02, 0x02 ),
  INP1( P2_UP, 0x02, 0x04 ),
  INP1( P2_DOWN, 0x02, 0x08 ),
  INP1( P2_B1, 0x02, 0x10 ),

  INP1( SERVICE, 1, 0x04 ),
  INP1( P1_START, 0x04, 0x04 ),
  INP1( P2_START, 0x04, 0x08 ),
  INP1( COIN1, 0x04, 0x80 ),
   END_INPUT
};

/* static struct INPUT_INFO input_dkong3[] =
{
  INP1( P1_RIGHT, 0x00, 0x01 ),
  INP1( P1_LEFT, 0x00, 0x02 ),
  INP1( P1_UP, 0x00, 0x04 ),
  INP1( P1_DOWN, 0x00, 0x08 ),
  INP1( P1_B1, 0x00, 0x10 ),
  INP1( P1_START, 0x00, 0x20 ),
  INP1( P2_START, 0x00, 0x40 ),
  INP1( COIN3, 0x00, 0x80 ),

  INP1( P2_RIGHT, 0x02, 0x01 ),
  INP1( P2_LEFT, 0x02, 0x02 ),
  INP1( P2_UP, 0x02, 0x04 ),
  INP1( P2_DOWN, 0x02, 0x08 ),
  INP1( P2_B1, 0x02, 0x10 ),
  INP1( COIN1, 0x02, 0x20 ),
  INP1( COIN2, 0x02, 0x40 ),
   END_INPUT
};
*/

static GfxLayout charlayout =
{
	8,8,	/* 8*8 characters */
	RGN_FRAC(1,2),
	2,	/* 2 bits per pixel */
	{ RGN_FRAC(1,2), RGN_FRAC(0,2) },	/* the two bitplanes are separated */
	{ 0, 1, 2, 3, 4, 5, 6, 7 },	/* pretty straightforward layout */
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
	8*8	/* every char takes 8 consecutive bytes */
};

static GfxLayout spritelayout =
{
	16,16,	/* 16*16 sprites */
	RGN_FRAC(1,4),	/* 128 sprites */
	2,	/* 2 bits per pixel */
	{ RGN_FRAC(1,2), RGN_FRAC(0,2) },	/* the two bitplanes are separated */
	{ 0, 1, 2, 3, 4, 5, 6, 7,	/* the two halves of the sprite are separated */
			RGN_FRAC(1,4)+0, RGN_FRAC(1,4)+1, RGN_FRAC(1,4)+2, RGN_FRAC(1,4)+3, RGN_FRAC(1,4)+4, RGN_FRAC(1,4)+5, RGN_FRAC(1,4)+6, RGN_FRAC(1,4)+7 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
			8*8, 9*8, 10*8, 11*8, 12*8, 13*8, 14*8, 15*8 },
	16*8	/* every sprite takes 16 consecutive bytes */
};

static struct GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &charlayout, },
	{ REGION_GFX2, &spritelayout, },
	{ -1 } /* end of array */
};

static UINT8 *gfx_ram,*spriteram,*interrupt_enable,*palette_bank,*color_codes,*gfx_bg_solid,*gfx_spr_solid,*gfx_bank,*gfx_bg,*gfx_spr;
static UINT16 mypal[256];

static int sp,mask_bank,spriteram_size,shift_bits,hammer_playing;
static int roar_counter,repeat_roar;
extern UINT32 cpu_frame_count;
static UINT8 last_level;

void dkongSoundWrite(UINT32 dwAddr, UINT8 bVal)
{

/*
7c00      Background sound/music select:
          00 - nothing
		  01 - Intro tune
		  02 - How High? (intermisson) tune
		  03 - Out of time
		  04 - Hammer
		  05 - Rivet level 2 completed (end tune)
		  06 - Hammer hit
		  07 - Standard level end + gorilla roar
		  08 - Background 1	(first screen)
		  09 - ???
		  0A - Background 3	(springs)
		  0B - Background 2 (rivet)
		  0C - Rivet level 1 completed (end tune)
		  0D - Rivet removed
		  0E - Rivet level completed
		  0F - Gorilla roar

7d00      digital sound trigger - walk
7d01      digital sound trigger - jump
7d02      digital sound trigger - boom (gorilla stomps foot)
7d03      digital sound trigger - coin input/spring
7d04      digital sound trigger	- gorilla fall
7d05      digital sound trigger - barrel jump/prize
7d06      ?
7d07      ?
7d80      digital sound trigger - dead

*/
  // if (bVal && bVal != 1 && bVal != 8) printf("%x,%d\n",dwAddr,bVal);
  if(dwAddr==0x7c00)
    {
      switch(bVal)
	{
	case 1:
	  raine_play_sample(start,200);
	  break;

	case 2:
	  raine_stop_samples();
	  // dkong us changes its level at this place in ram, but it must be read
	  // only between levels or otherwise you can see the next level before having
	  // the how high screen...
	  last_level = RAM[0x227];
	  raine_play_sample(howhigh,100);
	  sp=0;
	  break;

	case 6:
	  raine_play_sample(hammer_hit,200);
	  break;

	case 4:
	  if (!hammer_playing) {
	    /* I wanted to pause/unpause the level music at first, but it creates some
	       problems :
	        - allegro does not support this
		- since pause would be another sample variable, it breaks compatibility
		  with old savegames
		and finally restarting the music after the hammer is gone seems to sound
		better, and it's easier to do !
		Now the hammer is very primitive : the game sends the command to play
		this music once / frame, except when hitting something with the hammer.
		I found the solution of only stopping the music instead of all the samples
		when starting playing the hammer's music, it seems to be the best solution*/
	    raine_stop_sample(level1);
	    raine_stop_sample(level1+2);
	    raine_stop_sample(level1+3);
	    sp=0; // the game will restart the normal level music when needed
	    raine_loop_sample(dkhammer,150);
	    hammer_playing = 3;
	  } else {
	    hammer_playing = 3;
	  }
	  break;

	case 7:
	  raine_stop_samples();
	  raine_play_sample(levelend,150);
	  roar_counter = 2*fps; // roar in 3.1s !
	  repeat_roar = 1;
	  break;

	case 8:
	case 9:
	case 10:
	case 11:
	  if(!sp)
	    {
	      if (bVal == 9) bVal = 10;
	      raine_loop_sample(level1+bVal-8,80);
	      sp = 1;
	    }
	  break;

	case 0x0d:
	  raine_play_sample(jump_over,160);
	  break;

	case 0x0f:
	  raine_play_sample(roar,200);
	  break;
	}

      if(bVal==5 || bVal==12)
	{
	  raine_stop_samples();
	  raine_play_sample(winner,200);

	}
    }
  if(dwAddr==0x7d80 && bVal) {
    raine_stop_samples();
    raine_play_sample(dead,200);
  }

  if(dwAddr==0x7d00 && bVal) {
    raine_play_sample(walk,180);
  }

  if(dwAddr==0x7d01 && bVal)
    raine_play_sample(jump,160);

  if(dwAddr==0x7d02 && bVal)
    raine_play_sample(stomp,200);

  if(dwAddr==0x7d03 && bVal)
    raine_play_sample(coin,60);

  if(dwAddr==0x7d04 && bVal)
    raine_play_sample(fall,100);

  if(dwAddr==0x7d05 && bVal)
    raine_play_sample(jump_over,160);

}

static int layer_id_data[2];
static int draw_emudx_tile;
static BITMAP *flame_red, *flame_blue;

#define tile_index zz
#define BORDER 16

#ifdef RAINE_DEBUG
static void draw_debug_tile() {
  UINT8 code, color;
  SCROLL_REGS;
  UINT8 *map,*gfx;
  char str[4];
  if (!gfx_bg) {
    gfx_bg_solid = gfx_solid[0];
    gfx_spr_solid = gfx_solid[1];
    gfx_bg = load_region[REGION_GFX1];
    gfx_spr = load_region[REGION_GFX2];
  }

  if (*gfx_bank) {
    gfx = gfx_ram + 0x100;
  } else
    gfx = gfx_ram;

  MAKE_SCROLL_n_16(512,512,1,0, 0);
  START_SCROLL_16(BORDER,BORDER,512,512);

  int sy = y-16*2;
  if (sy < 0 || sy > 224*2+BORDER)
    continue;
  code = gfx[tile_index];
  color = (color_codes[(tile_index & 31) + 32 * (tile_index >> 7)] & 0x0f) + 0x10 * *palette_bank;

  // Draw8x8_Mapped_Rot(&gfx_bg[code<<6],x,sy,map);

  if (gfx_bg_solid[code]) {
    MAP_PALETTE_MAPPED_NEW(
			   color,
			   4,
			   map
			   );
    if (gfx_bg_solid[code] == 1) // transp
      Draw8x8_Trans_Mapped_Rot(&gfx_bg[code<<6],x,sy,map);
    else
      Draw8x8_Mapped_Rot(&gfx_bg[code<<6],x,sy,map);
    sprintf(str,"%02x",code);
    textout_fast(str,448+BORDER*2-8-sy,x+8,get_white_pen());
    sprintf(str,"%x",color);
    textout_fast(str,448+BORDER*2-8-sy+8,x,get_white_pen());
  }
    // }
  END_SCROLL_n_16(512,512,1);
}
#endif

static int dkong_us; // order of the levels different...
static int warned;

static void draw_emudx() {
  UINT8 code, color;
  SCROLL_REGS
  UINT8 *map,*gfx;
  int offs;
  int curlev = 0;
  static int bpp;

  if (RefreshBuffers) {
      bpp = display_cfg.bpp / 8;
      if (bpp == 1 && !warned) {
	  warned = 1;
#ifndef SDL
	  raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("Switch to at least 16bpp and reload"),NULL,raine_translate_text("&Ok"),NULL,'O',0);
#endif
      }
  }

  if (RAM[0x40]) { // number of lifes > 0 (6228 and 6040 seem to be the same !)
    if (RAM[0x22e]) { // seems to stay at 0 in attract mode...
      curlev = (RAM[0x22e]-1) & 3;
      if (dkong_us) {
	// int displev = RAM[0x229]; // level displayed on top right corner
	// printf("displev %d curlev %d\n",displev,curlev);
	curlev = last_level;
      } else
	if (curlev) curlev++;
    }
  }

  if (draw_emudx_tile) {
    if (!curlev) curlev = 1; // attract mode, draw 1st level...
    blit(emudx_tiles[curlev-1], GameBitmap, 0, 0, BORDER, BORDER, 448, 512);
    draw_emudx_tile = 0;
  } else {
    clear_game_screen(0);
  }

#ifdef RAINE_DEBUG
  if (input_buffer[8] & 8) {
    draw_debug_tile();
    return;
  }
#endif

  if (*gfx_bank) {
    gfx = gfx_ram + 0x100;
  } else
    gfx = gfx_ram;

  if( check_layer_enabled(layer_id_data[0])) {
    MAKE_SCROLL_n_16(512,512,1,0, 0)
    START_SCROLL_16(BORDER,BORDER,512,512)

    int sy = y-16*2;
    if (sy < 0 || sy > 224*2+BORDER)
      continue;
    code = gfx[tile_index];
    color = (color_codes[(tile_index & 31) + 32 * (tile_index >> 7)] & 0x0f) + 0x10 * *palette_bank;

    // Draw8x8_Mapped_Rot(&gfx_bg[code<<6],x,sy,map);

    if ((code >= 0xf0 && code < 0xfb)) {
      draw_emudx_tile = 1;
    } else {
      // level 4 is something really special we have to combine sprites and bg layer for it
      if (code == 0xb7 && curlev == 4) draw_emudx_tile = 1;

      if (code <= 165-5 && (code < 0x50 || code > 0x67)) { // character
	// between 0x50 and 0x67 it's the big sprite of the gorilla on the how high screen
	// when starting a level
	MAP_PALETTE_MAPPED_NEW(
			       color,
			       4,
			       map
			       );
	map += 2*bpp; // skip 2 first colors...
	// code -= 5;
	Draw16x16_Trans_Mapped_Rot(&emudx_chars[code<<8],x,sy,map);
      } else {
	if (code != 0xc0 || curlev == 4)
	  // only draw the ladders (c0) in level 4.
	  // The other dx levels have the ladders already drawn.
	  Draw16x16_Trans_Rot(&emudx_sprites[code<<(8+bpp/2)],x,sy,0);
      }
    }
    END_SCROLL_n_16(512,512,1);
  }

  /* Draw the sprites. */
  if( check_layer_enabled(layer_id_data[1])) {
    for (offs = 0;offs < spriteram_size;offs += 4){
      if (spriteram[offs]){
	/* spriteram[offs + 2] & 0x40 is used by Donkey Kong 3 only */
	/* spriteram[offs + 2] & 0x30 don't seem to be used (they are */
	/* probably not part of the color code, since Mario Bros, which */
	/* has similar hardware, uses a memory mapped port to change */
	/* palette bank, so it's limited to 16 color codes) */

	int x,y;

	x = spriteram[offs + 3] - 8;
	y = 240 - spriteram[offs] + 7;
	color = (spriteram[offs + 2] & 0x0f) + 16 * *palette_bank;
	code = (spriteram[offs + 1] & 0x7f) + ((spriteram[offs + 2] & mask_bank) << shift_bits);
	x=x*2+BORDER; y= y*2+BORDER-16*2;
	if (x<256*2+BORDER && y < 224*2+BORDER) {
	  int subcol = color & 0xf;
	  if ((code == 30 || code == 31) && subcol == 0x1) {
	    // hammer ready to run out...
	    code += 98;
	  } else if (code == 68 && subcol == 3) {
	    // improved platform on level 3.... is it really necessary to test the
	    // color ???
	    code++;
	  }
	  if((code>60 && code<63) || code==77 || code==78)
	    {
	      // flame effects
	      // int col = ((color >> 1) & 0x03) | ((color << 2) & 0x04);
	      BITMAP *flame = flame_red;
	      (void)flame; // used only by allegro, no warning this way
	      if(subcol==0 && (code==61 || code==62)) {
		code+=28; // Fire that fears (1st level)
		flame = flame_blue;
	      }
	      if(subcol==0 && (code==77 || code==78)) {
		code+=14; // Fire bugs that fear (rivets level)
		flame = flame_blue;
	      }

	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[code<<(10+bpp/2)],x,y,0,
					  ((spriteram[offs + 2] & 0x80)>>7) | ((spriteram[offs + 1] & 0x80)>>6));
	      draw_trans_sprite(GameBitmap,flame,disp_y_32 - y - 12, x - 8);

	      // my_draw_alpha(&flame->line[0],x-8,y+12);

	    } else {
/* 	      if (code==21 || code==25) */
	      /* Barrels are supposed to rotate, but it would be messy to do and almost
		 unnoticable considering the size of the details of the barrel... */
	      // rotate_sprite(prime_display,sprites[V], x, y-3,itofix(x*2+y*2)); //Our beautiful barrel rolls

	      Draw32x32_Trans_flip_Rot(&emudx_sprites32[code<<(10+bpp/2)],x,y,0,
					  ((spriteram[offs + 2] & 0x80)>>7) | ((spriteram[offs + 1] & 0x80)>>6));
	    }
	  /* consider doing it for x+256,y (warp around probably not necessary here) */
	}
      }
    }
  }
}

static void dkong_palette_bank_w(UINT32 offset, UINT8 data) {
  offset &= 1;

  if (data & 1)
    *palette_bank |= 1 << offset;
  else
    *palette_bank &= ~(1 << offset);
}

static void reset_roar() {
  roar_counter = 1;
  repeat_roar = 1;
  memset(RAM,0,RAMSize);
  // There is a bit somewhere in these input ports which absolutely needs to be
  // cleared before the game starts, but I didn't try to find which one.
  memset(input_buffer,0,5);
}

static void reset_level() {
  last_level = RAM[0x227]; // for dkong us
}

static void load_dkong() {
  UINT8 *color_prom = load_region[REGION_PROMS];
  int i;
  // RAMSize = 0x1000 + 0x400 + 4;
  RAMSize = 0x1800 + 4;

  dkong_us = is_current_game("dkong");

  if (!(RAM = AllocateMem(0xffff))) return;
  memcpy(RAM,ROM,get_region_size(REGION_CPU1));
  ROM = RAM;
  RAM = RAM + 0x6000;
  gfx_ram = RAM + 0x1400;

  // sprite parameters
  spriteram = RAM +0x900;
  spriteram_size = 0x17f;
  mask_bank = 64;
  shift_bits = 1;

  interrupt_enable = RAM + 0x1800;
  palette_bank = interrupt_enable + 1;
  gfx_bank = palette_bank+1;
  *palette_bank = *gfx_bank = 0;

  AddZ80AROMBase(ROM, 0x0038, 0x0066);
  AddZ80ARead(0x0000, get_region_size(REGION_ROM1)-1, NULL, ROM);
  AddZ80ARW(0x6000, 0x6fff, NULL, RAM);
  AddZ80ARW(0x7400, 0x77ff, NULL, gfx_ram);
  AddZ80ARead(0x7c00, 0x7c00, NULL, &input_buffer[0]);
  AddZ80ARead(0x7c80, 0x7c80, NULL, &input_buffer[2]);
  AddZ80ARead(0x7d00, 0x7d00, NULL, &input_buffer[4]);
  AddZ80ARead(0x7d80, 0x7d80, NULL, &input_buffer[6]);

  AddZ80ARead(0x8000,0xdfff, NULL, ROM + 0x8000);

  AddZ80AWrite(0x7c00, 0x7d80, dkongSoundWrite, NULL);
  AddZ80AWrite(0x7d84, 0x7d84, NULL, interrupt_enable);
  AddZ80AWrite(0x7d86, 0x7d87, dkong_palette_bank_w, NULL);

  AddZ80ARead(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
  AddZ80AWrite(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);	// <bad reads>
  AddZ80AReadPort(-1, -1, NULL, NULL);

  AddZ80AWritePort(0x00, 0xFF, DefBadWritePortZ80,			NULL);	// <bad reads>
  AddZ80AWritePort(-1, -1, NULL, NULL);
  AddZ80ARW(-1,-1,NULL,NULL);
  AddZ80AInit();

/***************************************************************************

  Convert the color PROMs into a more useable format.

  Donkey Kong has two 256x4 palette PROMs and one 256x4 PROM which contains
  the color codes to use for characters on a per row/column basis (groups of
  of 4 characters in the same column - actually row, since the display is
  rotated)
  The palette PROMs are connected to the RGB output this way:

  bit 3 -- 220 ohm resistor -- inverter  -- RED
        -- 470 ohm resistor -- inverter  -- RED
        -- 1  kohm resistor -- inverter  -- RED
  bit 0 -- 220 ohm resistor -- inverter  -- GREEN
  bit 3 -- 470 ohm resistor -- inverter  -- GREEN
        -- 1  kohm resistor -- inverter  -- GREEN
        -- 220 ohm resistor -- inverter  -- BLUE
  bit 0 -- 470 ohm resistor -- inverter  -- BLUE

***************************************************************************/
  /* As always for the color prom, great thanks go to mame for their decoding work */
  for (i=0; i<256; i++) {
    UINT8 bit0, bit1, bit2;
    int r,g,b;
    /* red component */
    bit0 = (color_prom[256] >> 1) & 1;
    bit1 = (color_prom[256] >> 2) & 1;
    bit2 = (color_prom[256] >> 3) & 1;
    r = 7 - (bit0 | (bit1<<1) | (bit2 << 2));
    /* green component */
    bit0 = (color_prom[0] >> 2) & 1;
    bit1 = (color_prom[0] >> 3) & 1;
    bit2 = (color_prom[256] >> 0) & 1;
    g = 7 - (bit0 | (bit1<<1) | (bit2 << 2));
    /* blue component */
    bit0 = (color_prom[0] >> 0) & 1;
    bit1 = (color_prom[0] >> 1) & 1;
    b = 7 - ((bit0<<1) | (bit1 << 2));
    mypal[i] = (b) | (g<<3) | (r<<6);
    color_prom++;
  }
  color_prom += 256;
  /* color_prom now points to the beginning of the character color codes */
  color_codes = color_prom;	/* we'll need it later */

  InitPaletteMap((UINT8*)mypal, 64, 4, 0x200); // 64 banks of 4 colors
  set_colour_mapper(&col_map_xxxxRrrgggbbb);

  gfx_bg = NULL;

  sp = 0; // no sample playing
  hammer_playing = 0;

  layer_id_data[0] = add_layer_info(gettext("BG"));
  layer_id_data[1] = add_layer_info(gettext("SPRITES"));

  if (!exists_emudx_file("dkongm.dx2") && (is_current_game("dkongjp") || is_current_game("dkong"))) {
#ifndef SDL
    raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("Without dkongm.dx2 you will have no sound"),NULL,raine_translate_text("&Ok"),NULL,'O',0);
#else
    MessageBox(gettext("EmuDX"),gettext("Without dkongm.dx2 you will have no sound"),gettext("Ok"));
#endif
  }
  if (exists_emudx_file("dkongg.dx2") && (is_current_game("dkongjp") || is_current_game("dkong"))) {
#ifndef SDL
    if((raine_alert(raine_translate_text("EmuDX"),NULL,raine_translate_text("EmuDX support?"),NULL,raine_translate_text("&Yes"),raine_translate_text("&No"),'Y','N'))==1)
#else
      if(MessageBox(gettext("EmuDX"),gettext("EmuDX support ?"),gettext("Yes|No")) == 1)
#endif
      {
	load_emudx("dkongg.dx2",4,262-5,262,419,
		   5,164,
		   448,512,makecol(0xff,0,0xff),draw_emudx);
	draw_emudx_tile = 0;

	/* There is a special effect for flames in dkong : the flames are drawn as normal
	   solid sprites, and then a flame "halo" is applied with alpha blending on top
	   of them. The size of the halo is of course different from the size of a normal
	   sprite, so I must load it directly here, it can't be handled in the emudx
	   module... */
#ifndef SDL
	set_screen_blender(140, 140, 140, 140);
#endif
	if (!flame_red) {
	  emudx_file dat = open_emudx_file("dkongg.dx2");
	  BITMAP *bmp;
	  flame_red = create_bitmap_ex(16,56,49);
	  flame_blue = create_bitmap_ex(16,56,49);
	  bmp = emudx_bitmap(dat,418);
	  stretch_blit(bmp,flame_red,0,0,84,74,0,0,56,49);
	  destroy_bitmap(bmp);
	  bmp = emudx_bitmap(dat,419);
	  stretch_blit(bmp,flame_blue,0,0,84,74,0,0,56,49);
	  destroy_bitmap(bmp);
	  close_emudx(dat);
	}
      }
  }
  set_reset_function(reset_roar);
  AddLoadCallback(reset_level);
}

static void execute_dkong() {
  if (roar_counter) {
    roar_counter--;
    if (!roar_counter) {
      raine_play_sample(roar,200);
      if (repeat_roar) {
	repeat_roar--;
	roar_counter = fps;
      }
    }
  }
  if (hammer_playing) {
    hammer_playing--;
    if (!hammer_playing) {
      raine_stop_sample(dkhammer);
    }
  }
  cpu_execute_cycles(CPU_Z80_0,CPU_FRAME_MHz(61.44/20,60)); // 3072000/60);
  if (*interrupt_enable) {
    cpu_int_nmi(CPU_Z80_0);
  }
}

static void draw_dkong() {
  UINT8 code, color;
  SCROLL_REGS
  UINT8 *map,*gfx;
  int offs,sy;

  if (!gfx_bg) {
    gfx_bg_solid = gfx_solid[0];
    gfx_spr_solid = gfx_solid[1];
    gfx_bg = load_region[REGION_GFX1];
    gfx_spr = load_region[REGION_GFX2];
  }

  if (*gfx_bank) {
    gfx = gfx_ram + 0x100;
  } else
    gfx = gfx_ram;

  if( check_layer_enabled(layer_id_data[0])) {
    MAKE_SCROLL_n_8(256,256,1,0, 0);
    START_SCROLL_8(BORDER,BORDER,256,256);

    sy = y-16;
    if (sy < 0 || sy > 224+BORDER)
      continue;
    code = gfx[tile_index];
    color = (color_codes[(tile_index & 31) + 32 * (tile_index >> 7)] & 0x0f) + 0x10 * *palette_bank;
    MAP_PALETTE_MAPPED_NEW(
			   color,
			   4,
			   map
			   );

    Draw8x8_Mapped_Rot(&gfx_bg[code<<6],x,sy,map);
    END_SCROLL_n_8(256,256,1);
  } else
    clear_game_screen(0);

  /* Draw the sprites. */
  if( check_layer_enabled(layer_id_data[1])) {
    for (offs = 0;offs < spriteram_size;offs += 4){
      if (spriteram[offs]){
	/* spriteram[offs + 2] & 0x40 is used by Donkey Kong 3 only */
	/* spriteram[offs + 2] & 0x30 don't seem to be used (they are */
	/* probably not part of the color code, since Mario Bros, which */
	/* has similar hardware, uses a memory mapped port to change */
	/* palette bank, so it's limited to 16 color codes) */

	int x,y;

	x = spriteram[offs + 3] - 8;
	y = 240 - spriteram[offs] + 7;
	color = (spriteram[offs + 2] & 0x0f) + 16 * *palette_bank;
	code = (spriteram[offs + 1] & 0x7f) + ((spriteram[offs + 2] & mask_bank) << shift_bits);
	x+=BORDER; y+=BORDER-16;
	if (x<256+BORDER && y < 224+BORDER && gfx_spr_solid[code]) {
	  MAP_PALETTE_MAPPED_NEW(
				 color,
				 4,
				 map
				 );
	  if (gfx_spr_solid[code] == 1)
	    Draw16x16_Trans_Mapped_flip_Rot(&gfx_spr[code<<8],x,y,map,
					    ((spriteram[offs + 2] & 0x80)>>7) | ((spriteram[offs + 1] & 0x80)>>6));
	  else
	    Draw16x16_Mapped_flip_Rot(&gfx_spr[code<<8],x,y,map,
				      ((spriteram[offs + 2] & 0x80)>>7) | ((spriteram[offs + 1] & 0x80)>>6));
	  /* consider doing it for x+256,y (warp around probably not necessary here) */
	}
      }
    }
  }
}

static struct VIDEO_INFO video_dkong =
{
   draw_dkong,
   256,
   224,
   BORDER,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   gfxdecodeinfo
};

GMEI( dkong,
     "Donkey Kong",
     NINTENDO,
     1981,
     GAME_PLATFORM);

CLNEI( dkongjp, dkong, "Donkey Kong (Japan)", NINTENDO, 1981, GAME_PLATFORM);
CLNEI( dkongex, dkong, "Donkey Kong (Foundry)", BOOTLEG, 2001, GAME_PLATFORM);
