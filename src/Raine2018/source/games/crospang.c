#define DRV_DEF_SOUND sound_crospang
#define DRV_DEF_EXEC execute_crospang
#define DRV_DEF_INPUT input_crospang
#define DRV_DEF_LOAD load_crospang
#define DRV_DEF_VIDEO &video_crospang
/* Cross Pang

  - Similar hardware to the Cookie Bibi (sprite system, tilemaps)

*/

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
static UINT8 *RAM_SPRITE;
static UINT8 *RAM_PF1;
static UINT8 *RAM_PF2;
static UINT8 *RAM_PALETTE;
static UINT8 *RAM_PFCTRL;


static struct ROM_INFO rom_crospang[] =
{
    { "p1.bin", 0x20000, 0x0bcbbaad, REGION_CPU1, 0x00001, LOAD_8_16 },
    { "p2.bin", 0x20000, 0x0947d204, REGION_CPU1, 0x00000, LOAD_8_16 },
{ "s1.bin",      0x010000, 0xd61a224c, REGION_ROM2, 0x000000, LOAD_NORMAL },
{ "s2.bin",      0x020000, 0x9f9ecd22, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "rom1.bin", 0x40000, 0x905042bb, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "rom2.bin", 0x40000, 0xbc4381e9, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "rom3.bin", 0x80000, 0xcc6e1fce, REGION_GFX2, 0x000000, LOAD_8_16 },
  { "rom4.bin", 0x80000, 0x9a91d494, REGION_GFX2, 0x000001, LOAD_8_16 },
  { "rom5.bin", 0x80000, 0x53a34dc5, REGION_GFX2, 0x100000, LOAD_8_16 },
  { "rom6.bin", 0x80000, 0x9c633082, REGION_GFX2, 0x100001, LOAD_8_16 },
{ NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_heuksun[] =
{
  { "ua02.j3", 0x80000, 0xdb2b9c8e, REGION_CPU1, 0x00001, LOAD_8_16 },
  { "ua03.j5", 0x80000, 0xde9f01e8, REGION_CPU1, 0x00000, LOAD_8_16 },
  { "us02.r4", 0x10000, 0xc7cc05fa, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "us08.u7", 0x40000, 0xae177589, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "uc08.r11", 0x20000, 0x242cee69, REGION_GFX1, 0x00001, LOAD_8_16 },
  { "uc08.r11", 0x20000, 0x242cee69, REGION_GFX1, 0x100001, LOAD_CONTINUE },
  { "uc08.r11", 0x20000, 0x242cee69, REGION_GFX1, 0x040001, LOAD_CONTINUE },
  { "uc08.r11", 0x20000, 0x242cee69, REGION_GFX1, 0x140001, LOAD_CONTINUE },
  { "uc07.t11", 0x20000, 0x4d1ed885, REGION_GFX1, 0x00000, LOAD_8_16 },
  { "uc07.t11", 0x20000, 0x4d1ed885, REGION_GFX1, 0x100000, LOAD_CONTINUE },
  { "uc07.t11", 0x20000, 0x4d1ed885, REGION_GFX1, 0x040000, LOAD_CONTINUE },
  { "uc07.t11", 0x20000, 0x4d1ed885, REGION_GFX1, 0x140000, LOAD_CONTINUE },
  { "ud14.p11", 0x40000, 0x4fc2b574, REGION_GFX2, 0x00000, LOAD_8_16 },
  { "ud15.m11", 0x40000, 0x1d6187a6, REGION_GFX2, 0x00001, LOAD_8_16 },
  { "ud16.l11", 0x40000, 0xeabec43e, REGION_GFX2, 0x80000, LOAD_8_16 },
  { "ud17.j11", 0x40000, 0xc6b04171, REGION_GFX2, 0x80001, LOAD_8_16 },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_crospang[] =
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

	INP0( COIN1, 0x0003, 0x01 ),
	INP0( COIN2, 0x0003, 0x02 ),
INP0( COIN3, 0x0003, 0x04 ),
	END_INPUT
};

static struct DSW_DATA dsw_data_crospang_0[] =
{
  { MSG_COINAGE, 0x0003, 4 },
  { MSG_3COIN_1PLAY, 0x0000, 0x00 },
  { MSG_2COIN_1PLAY, 0x0001, 0x00 },
  { MSG_1COIN_1PLAY, 0x0002, 0x00 },
  { MSG_1COIN_2PLAY, 0x0003, 0x00 },
// _("SW1:5")
  { MSG_DIFFICULTY, 0x000c, 4 },
  { MSG_EASY, 0x0008, 0x00 },
  { MSG_MEDIUM, 0x000c, 0x00 },
  { MSG_HARD, 0x0000, 0x00 },
  { MSG_HARDEST, 0x0004, 0x00 },
// _("SW1:6")
  { _("Bonus Power (Points)"), 0x0010, 2 },
  { _("5k 20k 15k+"), 0x0010, 0x00 },
  { _("8k 23k 15k+"), 0x0000, 0x00 },
// _("SW1:7,8")
  { _("Number of Powers"), 0x0020, 2 },
  { "1", 0x0000, 0x00 },
  { "2", 0x0020, 0x00 },
// _("SW2:1,2")
  { _("Extra Balls per Move"), 0x00c0, 4 },
  { "1", 0x00c0, 0x00 },
  { "2", 0x0080, 0x00 },
  { "3", 0x0040, 0x00 },
  { "4", 0x0000, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_DATA dsw_data_crospang_1[] =
{
  { MSG_UNKNOWN, 0x3, 4 },
  { "6/7", 0x3, 0x00 },
  { "7/8", 0x2, 0x00 },
  { "8/9", 0x1, 0x00 },
  { "9/10", 0x0, 0x00 },
// _("SW2:4,5")
  { _("Bonus Power (Bomb)"), 0x4, 2 },
  { _("3 Chain Reactions"), 0x4, 0x00 },
  { _("4 Chain Reactions"), 0x0, 0x00 },
  { _("Minimum Balls per Row"), 0x18, 4 },
  { "3", 0x18, 0x00 },
  { "4", 0x10, 0x00 },
  { "5", 0x8, 0x00 },
  { "6", 0x0, 0x00 },
  DSW_SERVICE(0,0x40),
  { NULL, 0, 0}
};

static struct DSW_INFO dsw_crospang[] =
{
  { 0x4, 0x7e, dsw_data_crospang_0 },
  { 0x5, 0xf7, dsw_data_crospang_1 },
  { 0, 0, NULL }
};

static struct DSW_DATA dsw_data_heuksun_2[] =
{
// _("SW1:1,2")
// _("SW1:3,4")
  { MSG_COINAGE, 0x0003, 4 },
  { MSG_3COIN_1PLAY, 0x0000, 0x00 },
  { MSG_2COIN_1PLAY, 0x0001, 0x00 },
  { MSG_1COIN_1PLAY, 0x0002, 0x00 },
  { MSG_1COIN_2PLAY, 0x0003, 0x00 },
// _("SW1:5")
  { MSG_DIFFICULTY, 0x000c, 4 },
  { MSG_EASY, 0x000c, 0x00 },
  { MSG_MEDIUM, 0x0008, 0x00 },
  { MSG_HARD, 0x0004, 0x00 },
  { MSG_HARDEST, 0x0000, 0x00 },
  { _("Help Penalty (Heuk Sun)"), 0x0010, 2 },
  { _("Constant"), 0x0010, 0x00 },
  { _("Variable"), 0x0000, 0x00 },
  DSW_SERVICE( 0, 0x0080 ),
// _("SW2:1,2,3,4,5,6,7,8")
  { NULL, 0, 0}
};

static struct DSW_DATA dsw_data_heuksun_3[] =
{
  { MSG_UNKNOWN, 0xff, 9 },
  { "0", 0xff, 0x00 },
  { "1", 0xfe, 0x00 },
  { "2", 0xfd, 0x00 },
  { "3", 0xfb, 0x00 },
  { "4", 0xf7, 0x00 },
  { "5", 0xef, 0x00 },
  { "6", 0xdf, 0x00 },
  { "7", 0xbf, 0x00 },
  { "8", 0x7f, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_INFO dsw_heuksun[] =
{
  { 0x4, 0x9e, dsw_data_heuksun_2 },
  { 0x5, 0xff, dsw_data_heuksun_3 },
  { 0, 0, NULL }
};

static struct YM3812interface ym3812_interface =
{
   1,              // 1 chip
   14318180/4,	/**/
   { 255 },        // Volume (emu only)
   { z80_irq_handler }
};

static struct OKIM6295interface okim6295_interface =
{
	1,			/* 1 chip */
	{ 8000 },		/* 7575Hz playback? */
	{ REGION_SOUND1 },
	{ 240 }
};

static struct SOUND_INFO sound_crospang[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { SOUND_M6295,    &okim6295_interface   },
   { 0,              NULL,                 },
};

static gfx_layout tlayout =
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

static struct GFX_LIST crospang_gfx[] =
{
   { REGION_GFX1, &tlayout, },
   { REGION_GFX2, &tlayout, },
   { 0,           NULL,           },
};

/* this doesn't take into account priority, but afaik these games don't really care */
static int spr_xoffset = -4;
static int spr_yoffset = 0;

static UINT8 *map;

#define BORDER 16

static void draw_solid_layer(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	UINT8  colour;
	int x16,y16,zzz,zzzz;
	int zz;


	MAKE_SCROLL_512x512_2_16(scrollx,scrolly);
	START_SCROLL_512x512_2_16(BORDER,BORDER,320,240);
	{

	  tileno = ReadWord(&PFRAM[zz]);
	  colour = (tileno>>12) + palbase;
	  tileno &= 0x0fff;

	  MAP_PALETTE_MAPPED_NEW(
				 colour,
				 16,
				 map
				 );

	  Draw16x16_Mapped_Rot(&gfx1[tileno<<8], x, y, map);
	}
	END_SCROLL_512x512_2_16();
}

static void crospang_draw_16x16_layer(int scrollx,int scrolly, int palbase, UINT8 *PFRAM)
{
	int x,y;
	UINT16 tileno;
	UINT8  colour;
	int x16,y16,zzz,zzzz;
	int zz;


	MAKE_SCROLL_512x512_2_16(scrollx,scrolly);
	START_SCROLL_512x512_2_16(BORDER,BORDER,320,240);
	{

	  tileno = ReadWord(&PFRAM[zz]);
	  colour = (tileno>>12) + palbase;
	  tileno &= 0x0fff;

	  if( gfx1_solid[tileno] )
	    {
	      MAP_PALETTE_MAPPED_NEW(
				     colour,
				     16,
				     map
				     );

	      if((gfx1_solid[tileno]==1))
		{
		  Draw16x16_Trans_Mapped_Rot(&gfx1[tileno<<8], x, y, map);
		}
	      else
		{
		  Draw16x16_Mapped_Rot(&gfx1[tileno<<8], x, y, map);
		}
	    }
	}
	END_SCROLL_512x512_2_16();
}

static void crospang_drawsprites(void)
{
	int offs;
	static int frame=0;

	frame++;

	for (offs = 0;offs<0x800;offs+=8)
	{
		int x,y,sprite,colour,multi,/* fx, */ fy,inc,flash,mult,flipyx,xdraw;

//		print_debug("sprite %04x\n",offs);

		sprite = (RAM_SPRITE[offs+2]|(RAM_SPRITE[offs+3]<<8));

		if (!sprite) continue; // careful.. not all games have sprite 0 as blank, these AFAIK do however

		y =      ReadWord(&RAM_SPRITE[offs]);

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
		x = 304 - x;

		xdraw = x+BORDER+spr_xoffset; // x-1 for bcstory .. realign other layers?

		if((xdraw<=BORDER-16)||(xdraw>=320+BORDER)) continue;

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
			int ydraw = (y+mult*multi)+BORDER-7+spr_yoffset;
			int spriteno = sprite - multi * inc;
/*
			drawgfx(bitmap,Machine->gfx[3],
					spriteno,
					colour,
					fx,fy,
					xdraw,ydraw,
					cliprect,TRANSPARENCY_PEN,0);
*/


			if ((ydraw>BORDER-16)&&(ydraw<240+BORDER))
			{
//				print_debug("sprite draw %04x %04x %04x\n",xdraw,ydraw,spriteno);

				if(gfx2_solid[spriteno])
				{            // No pixels; skip

					MAP_PALETTE_MAPPED_NEW(
						colour,
						16,
						map
					);

					if(gfx2_solid[spriteno]==1)
					{         // Some pixels; trans
						switch(flipyx)
						{
							case 0x00: Draw16x16_Trans_Mapped_Rot       (&gfx2[spriteno<<8], xdraw, ydraw, map); break;
							case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot (&gfx2[spriteno<<8], xdraw, ydraw, map); break;
							case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot (&gfx2[spriteno<<8], xdraw, ydraw, map); break;
							case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&gfx2[spriteno<<8], xdraw, ydraw, map); break;
						}
					}
					else
					{                  // all pixels; solid
						switch(flipyx)
						{
							case 0x00: Draw16x16_Mapped_Rot       (&gfx2[spriteno<<8], xdraw, ydraw, map); break;
							case 0x01: Draw16x16_Mapped_FlipY_Rot (&gfx2[spriteno<<8], xdraw, ydraw, map); break;
							case 0x02: Draw16x16_Mapped_FlipX_Rot (&gfx2[spriteno<<8], xdraw, ydraw, map); break;
							case 0x03: Draw16x16_Mapped_FlipXY_Rot(&gfx2[spriteno<<8], xdraw, ydraw, map); break;
						}
					}
				}
			}

			multi--;
		}

	}
}


static void draw_crospang(void)
{
	int scrollx,scrolly;

	ClearPaletteMap();

	scrollx = ReadWord(&RAM_PFCTRL[8]);
	scrolly = ReadWord(&RAM_PFCTRL[6]);
	scrolly += 8;
	draw_solid_layer(scrollx,scrolly,0x20,RAM_PF2);

	scrollx = ReadWord(&RAM_PFCTRL[4]);
	scrolly = ReadWord(&RAM_PFCTRL[2]);
	scrollx += 4;
	scrolly += 8;
	crospang_draw_16x16_layer  (scrollx,scrolly,0x10,RAM_PF1);

	crospang_drawsprites();
}

#define FRAME_Z80 CPU_FRAME_MHz(4,60)

static void execute_crospang(void)
{
  int frame = FRAME_Z80,diff;
  while (frame > 0) {
    diff = execute_one_z80_audio_frame(frame);
    cpu_execute_cycles(CPU_68K_0, diff*2); // Main 68000
    frame -= diff;
  }
  cpu_interrupt(CPU_68K_0, 6);
}

UINT8 crosspang_soundlatch_r (UINT32 offset)
{
	return latch;
}


static void sound_crospang16_w ( UINT32 offset, UINT16 data )
{
	latch = data;

	// cpu_execute_cycles(CPU_Z80_0, 6000);
//	printf("sound16_w data %04x\n",data);

}

static UINT16 my_speed_hack(UINT32 offset) {
  /* I am not 100% certain that this is the place tested for the vbl, because this
     rom executes an insane amount of code while waiting for the vbl, but this is
     the 1st thing tested, and it seems to work */
  UINT16 ret = ReadWord(&RAM_MAIN[0x53fe]);
  if (ret == 0) {
    Stop68000(0,0);
  }
  return ret;
}

static void load_crospang(void)
{
	UINT8 *rom = load_region[REGION_GFX1];
	int len = get_region_size(REGION_GFX1);
	int i;

	/* gfx data is in the wrong order */
	for (i = 0; i < len; i++)
	{
		if ((i & 0x20) == 0)
		{
			int t = rom[i]; rom[i] = rom[i + 0x20]; rom[i + 0x20] = t;
		}
	}
	/* low/high half are also swapped */
	for (i = 0; i < len / 2; i++)
	{
		int t = rom[i]; rom[i] = rom[i + len / 2]; rom[i + len / 2] = t;
	}
	/* In RAINE we allocate one big block of RAM to contain all emulated RAM then set some pointers to it

		Z80:
		0x10000 bytes z80

		68000:
		0x10000 bytes - MAIN RAM
		0x00800 bytes - SPRITERAM
		0x00800 bytes - FG TILEMAP
		0x00800 bytes - BG TILEMAP
		0x00800 bytes - PALETTE (actually 0x600)
		0x00010 bytes - VIDEO REGS
	*/

	/* Calculate how much RAM we need to allocate */
	RAMSize=0x10000
	       +0x10000
	       +0x00800
	       +0x00800
	       +0x00800
	       +0x00800
	       +0x00010;

	/* Allocate the RAM */
	if(!(RAM=AllocateMem(RAMSize))) return;
	// Without the memset here we can even get a crash at startup !
	memset(RAM,0,RAMSize);

	/* Set Up the Pointers */
	RAM_Z80       = &RAM[0x00000];
	RAM_MAIN      = &RAM[0x00000+0x10000];
	RAM_SPRITE    = &RAM[0x00000+0x10000+0x10000];
	RAM_PF1       = &RAM[0x00000+0x10000+0x10000+0x00800];
	RAM_PF2       = &RAM[0x00000+0x10000+0x10000+0x00800+0x00800];
	RAM_PALETTE   = &RAM[0x00000+0x10000+0x10000+0x00800+0x00800+0x00800];
	RAM_PFCTRL    = &RAM[0x00000+0x10000+0x10000+0x00800+0x00800+0x00800+0x00800];


   // Setup Z80 memory map
   // --------------------

	AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

	AddZ80AReadByte (0x0000, 0xbfff, NULL,                     load_region[REGION_ROM2] ); // Z80 ROM
	AddZ80AReadByte (0xc000, 0xc7ff, NULL,                     RAM_Z80                  );

	AddZ80AWriteByte(0xc000, 0xc7ff, NULL,                     RAM_Z80                  ); // Z80 RAM

	AddZ80AReadPort (0x00, 0x00, YM3812ReadZ80,                  NULL);
	AddZ80AReadPort (0x02, 0x02, OKIM6295_status_0_r,            NULL);
	AddZ80AReadPort (0x06, 0x06, crosspang_soundlatch_r,         NULL);

	AddZ80AWritePort(0x00, 0x01, YM3812WriteZ80,                 NULL);
	AddZ80AWritePort(0x02, 0x02, OKIM6295_data_0_w,              NULL);


	AddZ80AReadByte (0x0000, 0xFFFF, DefBadReadZ80,              NULL);
	AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
	AddZ80AReadPort (0x00,   0xFF,   DefBadReadZ80,              NULL);
	AddZ80AWritePort(0x00,   0xFF,   DefBadWriteZ80,             NULL);
	AddZ80AReadByte (  -1,   -1,     NULL,                       NULL);
	AddZ80AWriteByte(  -1,   -1,     NULL,                       NULL);
	AddZ80AReadPort (  -1,   -1,     NULL,                       NULL);
	AddZ80AWritePort(  -1,   -1,     NULL,                       NULL);

	AddZ80AInit();

	setup_z80_frame(CPU_Z80_0,FRAME_Z80); // for the Z80 we need to set up the speed here..


	/* Setup Starscream 68000 core */

	/* ROM is a pointer to the ROM1 region.. automatically set up? */


	Add68000Code(0,0, REGION_CPU1);
	AddMemFetch (0x320000, 0x32ffff,                        RAM_MAIN-0x320000        ); // note: you need to subtract the address?!

	/* Set Up the RAM, we allow all types of READ/WRITE operations */
	AddRWBW     (0x100000, 0x10000f,     NULL,              RAM_PFCTRL      );   // scroll regs etc.

	AddRWBW     (0x120000, 0x120fff,     NULL,              RAM_PF1         );   // PLAYFIELD 1 DATA
	AddRWBW     (0x122000, 0x122fff,     NULL,              RAM_PF2         );   // PLAYFIELD 2 DATA
	AddRWBW     (0x200000, 0x2007ff,     NULL,              RAM_PALETTE     );   // PALETTE RAM
	AddRWBW     (0x210000, 0x2107ff,     NULL,              RAM_SPRITE      );   // SPRITE RAM

	AddWriteWord(0x270000, 0x270001,     sound_crospang16_w,NULL            );   // sound

	AddReadBW (0x280000, 0x28000f,     NULL, input_buffer);   // Inputs
	if (is_current_game("crospang"))
	    AddReadWord(0x3253fe,0x3253ff,my_speed_hack, NULL);
	AddRWBW     (0x320000, 0x32ffff,     NULL,              RAM_MAIN        );   // MAIN RAM



	/* Handler for the Inputs */
	finish_conf_68000(0);


	/* Note: In RAINE the palette is handled like this */
	InitPaletteMap(RAM_PALETTE, 0x60, 0x10, 0x8000);
	set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);  /* rrr_rrgg_gggb_bbbb !! */


}

static struct VIDEO_INFO video_crospang =
{
   draw_crospang,
   320,
   240,
   BORDER,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   crospang_gfx,
};
static struct DIR_INFO dir_crospang[] =
{
   { "cross_pang", },
   { "crospang", },
   { NULL, },
};
GME( crospang, "Cross Pang", F2, 1998, GAME_PUZZLE);
GMEI( heuksun, "Heuk Sun Baek Sa (Korea)", F2, 1998, GAME_PUZZLE);

