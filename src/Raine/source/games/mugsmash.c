#define DRV_DEF_SOUND technos_ym2151_m6295_sound
/* Mug Smashers
 (c) Electronic Devices

 this seems to borrow quite a few things from Combatribes... including the music

*/

/* I haven't checked which of these we need */
#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "2151intf.h"
#include "adpcm.h"
#include "3812intf.h"
#include "blit.h" // clear_game_screen
#include "timer.h"
#include "savegame.h"
#include "emumain.h" // set_reset_function
#include "scroll.h"
#include "tchnosnd.h"

static UINT8 *RAM_Z80;
static UINT8 *RAM_MAIN;
static UINT8 *RAM_SPRITE;
static UINT8 *RAM_TILEMAP1;
static UINT8 *RAM_TILEMAP2;
static UINT8 *RAM_PALETTE;
static UINT8 *RAM_VIDREGS;
static UINT8 *RAM_OTHERREGS;

/* Diverboy Directories and (automatic) Rom loading */



static struct ROM_INFO rom_mugsmash[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,     0x040000,
            "mugs_04.bin",  0x2498fd27, "mugs_05.bin",  0x95efb40b),

	{ "mugs_03.bin",    0x010000, 0x0101df2d, REGION_ROM2, 0x000000, LOAD_NORMAL },

	{ "mugs_02.bin",    0x020000, 0xf92a7f4a, REGION_SMP1, 0x000000, LOAD_NORMAL },
	{ "mugs_01.bin",    0x020000, 0x1a3a0b39, REGION_SMP1, 0x020000, LOAD_NORMAL },

  LOAD8_16(  REGION_GFX1,  0x000000,     0x080000,
            "mugs_11.bin",  0x1c9f5acf, "mugs_10.bin",  0x6b3c22d9),
  LOAD8_16(  REGION_GFX1,  0x100000,     0x080000,
            "mugs_09.bin",  0x4e9490f3, "mugs_08.bin",  0x716328d5),
  LOAD8_16(  REGION_GFX1,  0x200000,     0x080000,
            "mugs_07.bin",  0x9e3167fd, "mugs_06.bin",  0x8df75d29),

	{ "mugs_12.bin",    0x080000, 0xc0a6ed98, REGION_GFX2, 0x000000, LOAD_NORMAL },
	{ "mugs_13.bin",    0x080000, 0xe2be8595, REGION_GFX2, 0x080000, LOAD_NORMAL },
	{ "mugs_14.bin",    0x080000, 0x24e81068, REGION_GFX2, 0x100000, LOAD_NORMAL },
	{ "mugs_15.bin",    0x080000, 0x82e8187c, REGION_GFX2, 0x180000, LOAD_NORMAL },

	{ NULL, 0, 0, 0, 0, 0 }
};


/* Video Setup */
static UINT8* map;

static void mugsmash_draw_sprites(void)
{

	/* Each Sprite takes 16 bytes, 5 used? */

	/* ---- ----  xxxx xxxx  ---- ----  aaaa aaaa  ---- ----  NNNN NNNN  ---- ----  nnnn nnnn  ---- ----  yyyy yyyy (rest unused?) */

	/* x = xpos LSB
       y = ypos LSB
       N = tile number MSB
       n = tile number LSB
       a = attribute / extra
            f?XY cccc

        f = x-flip
        ? = unknown, probably y-flip
        X = xpos MSB
        y = ypos MSB
        c = colour

    */

	const UINT8 *source = RAM_SPRITE;
	const UINT8 *finish = source+0x4000;

	while( source<finish )
	{
		int num = source[6]|(source[4]<<8);

		int xpos = source[0];
		int ypos = source[8];
		int attr = source[2];
		int flipx = (attr & 0x0080);
		int colour = (attr & 0x000f);

		xpos += ((attr & 0x0020) >> 5) * 0x100;
		ypos += ((attr & 0x0010) >> 4) * 0x100;

//		xpos -= 28;
//		ypos -= 16;

		xpos += 2;
		ypos += 12;

		if((xpos<=16)||(xpos>=320+32)) { source+=16; continue;} // offscreen, skip
		if((ypos<=16)||(ypos>=240+32)) { source+=16; continue;} // offscreen, skip

		if(gfx1_solid[num])
		{

/*
			drawgfx(
					bitmap,
					gfx,
					num,
					colour,
					flipx,0,
					xpos,ypos,
					cliprect,
					TRANSPARENCY_PEN,0
					);
*/

			MAP_PALETTE_MAPPED_NEW(
				colour,
				16,
				map
				);

			if(gfx1_solid[num]==1) // Some pixels; trans
			{
				if(!flipx) Draw16x16_Trans_Mapped_Rot       (&gfx1[num<<8], xpos, ypos, map);
				else Draw16x16_Trans_Mapped_FlipY_Rot       (&gfx1[num<<8], xpos, ypos, map); // in raine flipy is flipx .... wtf!
			}
			else                           // all pixels; solid
			{
				if(!flipx) Draw16x16_Mapped_Rot             (&gfx1[num<<8], xpos, ypos, map);
				else Draw16x16_Mapped_FlipY_Rot             (&gfx1[num<<8], xpos, ypos, map); // in raine flipy is flipx .... wtf!
			}


		}

		source += 0x10;
	}
}

/* this could be sped up a bit by working out the ranges of x/y we need to process first.. instead of looping
  through all of them, it has no linescroll etc. afterall */
static void mugsmash_draw_16x16_layer(int scrollx,int scrolly, int palbase, int layersolid, UINT8 *TILERAM)
{
	register int x,y;
	int offset;

	offset = 0;

	for (y=0;y<512;y+=16)
	{
		for (x=0;x<512;x+=16)
		{
			int drawx,drawy;
			drawx = x;
			drawy = y;

			/* adjust for scrolling */
			drawx -= scrollx;
			drawy -= scrolly;

			/* adjust for raine's clipping area */
			drawx += 32;
			drawy += 32;

			drawx &=512-1;
			drawy &=512-1;


			if ((drawx>=16)&&(drawx<320+32+16)&&(drawy>=16)&&(drawy<240+32+16))
			{
				UINT16 tileno;
				UINT8  colour;
				UINT8  flipxy;

				tileno = TILERAM[offset+2]|(TILERAM[offset+3]<<8);
				colour = TILERAM[offset+0]&0x000f;
				flipxy = TILERAM[offset+0]&0x00c0;

				colour += palbase;
//				tileno &= 0xffff;

				if( gfx2_solid[tileno] || layersolid )
				{
					MAP_PALETTE_MAPPED_NEW(
						colour,
						16,
						map
						);

					if((gfx2_solid[tileno]==1)&&(!layersolid))
					{
						switch (flipxy)
						{
							case 0x00: Draw16x16_Trans_Mapped_Rot       (&gfx2[tileno<<8], drawx, drawy, map); break;
							case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot (&gfx2[tileno<<8], drawx, drawy, map); break;
							case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot (&gfx2[tileno<<8], drawx, drawy, map); break;
							case 0xc0: Draw16x16_Trans_Mapped_FlipXY_Rot(&gfx2[tileno<<8], drawx, drawy, map); break;
						}
					}
					else
					{
						switch (flipxy)
						{
							case 0x00: Draw16x16_Mapped_Rot       (&gfx2[tileno<<8], drawx, drawy, map); break;
							case 0x80: Draw16x16_Mapped_FlipX_Rot (&gfx2[tileno<<8], drawx, drawy, map); break;
							case 0x40: Draw16x16_Mapped_FlipY_Rot (&gfx2[tileno<<8], drawx, drawy, map); break;
							case 0xc0: Draw16x16_Mapped_FlipXY_Rot(&gfx2[tileno<<8], drawx, drawy, map); break;
						}
					}
				}
			}


			offset+=4;


		}
	}
}

static void draw_mugsmash(void)
{
	int scrollx, scrolly;

	ClearPaletteMap();

	scrollx = (RAM_VIDREGS[4]|(RAM_VIDREGS[5]<<8))+7;
	scrolly = (RAM_VIDREGS[6]|(RAM_VIDREGS[7]<<8))+12;

	mugsmash_draw_16x16_layer(scrollx,scrolly,0x20,1,RAM_TILEMAP2);


	scrollx = (RAM_VIDREGS[0]|(RAM_VIDREGS[1]<<8))+3;
	scrolly = (RAM_VIDREGS[2]|(RAM_VIDREGS[3]<<8))+12;

	mugsmash_draw_16x16_layer(scrollx,scrolly,0x10,0,RAM_TILEMAP1);

	mugsmash_draw_sprites();
}

static gfx_layout mugsmash_16x16tiles =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0,1,2,3 },
	{ 16,20,24,28,0,4,8,12,48,52,56,60,32,36,40,44 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64,
	 8*64, 9*64, 10*64, 11*64, 12*64, 13*64, 14*64, 15*64},
	16*64
};

static gfx_layout mugsmash_16x16tiles2 =
{
	16,16,
	RGN_FRAC(1,4),
	4,
	{ 	0x080000*3*8, 	0x080000*2*8, 	0x080000*1*8,	0x080000*0*8 },
	{ 0, 1, 2, 3, 4, 5, 6, 7, 16*8+0,16*8+1,16*8+2,16*8+3,16*8+4,16*8+5,16*8+6,16*8+7  },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8, 8*8, 9*8, 10*8, 11*8, 12*8, 13*8, 14*8, 15*8 },
	32*8
};

static struct GFX_LIST mugsmash_gfx[] =
{
   { REGION_GFX1, &mugsmash_16x16tiles, },
   { REGION_GFX2, &mugsmash_16x16tiles2, },
   { 0,           NULL,           },
};



#define FRAME CPU_FRAME_MHz(12,60)

static void execute_mugsmash(void)
{
	cpu_execute_cycles(CPU_68K_0, FRAME); // Main 68000
	cpu_interrupt(CPU_68K_0, 6);

	TechnosSoundOld_Frame();	// Z80; YM2151; OKI ADPCM

}

/* Inputs + Dips */

static struct INPUT_INFO input_mugsmash[] =
{
	INP0( P1_RIGHT, 0x0000, 0x01 ),
	INP0( P1_LEFT, 0x0000, 0x02 ),
	INP0( P1_UP, 0x0000, 0x04 ),
	INP0( P1_DOWN, 0x0000, 0x08 ),
	INP0( P1_B1, 0x0000, 0x10 ),
	INP0( P1_B2, 0x0000, 0x20 ),
	INP0( P1_B3, 0x0000, 0x40 ),
	INP0( P1_START, 0x0000, 0x80 ),

	INP0( P2_RIGHT, 0x0001, 0x01 ),
	INP0( P2_LEFT, 0x0001, 0x02 ),
	INP0( P2_UP, 0x0001, 0x04 ),
	INP0( P2_DOWN, 0x0001, 0x08 ),
	INP0( P2_B1, 0x0001, 0x10 ),
	INP0( P2_B2, 0x0001, 0x20 ),
	INP0( P2_B3, 0x0001, 0x40 ),
	INP0( P2_START, 0x0001, 0x80 ),

	INP0( COIN1, 0x0002, 0x01 ),
	INP0( COIN2, 0x0002, 0x02 ),
	/*                                       0x04               */
	/*                                       0x08               */
	/*                                       0x10               */
	/*                                       0x20               */
	/*                                       0x40               */
	/*                                       0x80               */

	END_INPUT
};

static struct DSW_DATA dsw_data_mugsmash_0[] =
{
   { MSG_TEST_MODE,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_COINAGE,             0x0e, 0x08 },
   { MSG_4COIN_1PLAY,         0x0c},
   { MSG_3COIN_1PLAY,         0x0a},
   { MSG_2COIN_1PLAY,         0x08},
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x02},
   { MSG_1COIN_3PLAY,         0x04},
   { MSG_1COIN_4PLAY,         0x06},
   { MSG_FREE_PLAY,           0x0e},
   { _("Allow Continue"),        0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { _("Sound Test"),            0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { _("Colour Test"),           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Draw SF."),              0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_mugsmash_1[] =
{
   { MSG_DEMO_SOUND,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { _("Lives"),                 0x06, 0x04 },
   { "1",                     0x00},
   { "2",                     0x02},
   { "3",                     0x04},
   { "4",                     0x06},
   { _("Unused 2-4"),            0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { _("Difficulty"),            0x30, 0x04 },
   { _("Very Easy"),             0x00},
   { _("Easy"),                  0x10},
   { _("Hard"),                  0x20},
   { _("Very Hard"),             0x30},
   { _("Draw Objects"),          0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Freeze"),                0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_mugsmash[] =
{
  { 0x3, 0xe1, dsw_data_mugsmash_0 },
  { 0x4, 0xe6, dsw_data_mugsmash_1 },
  { 0, 0, NULL }
};


#if 0
static ADDRESS_MAP_START( mugsmash_readmem, ADDRESS_SPACE_PROGRAM, 16 )
	AM_RANGE(0x000000, 0x07ffff) AM_READ(MRA16_ROM)
	AM_RANGE(0x080000, 0x080fff) AM_READ(MRA16_RAM)
	AM_RANGE(0x082000, 0x082fff) AM_READ(MRA16_RAM)
	AM_RANGE(0x100000, 0x1001ff) AM_READ(MRA16_RAM)
	AM_RANGE(0x100200, 0x1005ff) AM_READ(MRA16_RAM)
	AM_RANGE(0x1c0000, 0x1c3fff) AM_READ(MRA16_RAM)
	AM_RANGE(0x1c4000, 0x1cffff) AM_READ(MRA16_RAM)
	AM_RANGE(0x200000, 0x201fff) AM_READ(MRA16_RAM)
	AM_RANGE(0x202000, 0x203fff) AM_READ(MRA16_RAM)
#if USE_FAKE_INPUT_PORTS
	AM_RANGE(0x180000, 0x180007) AM_READ(mugsmash_input_ports_r)
#else
	AM_RANGE(0x180000, 0x180001) AM_READ(input_port_0_word_r)
	AM_RANGE(0x180002, 0x180003) AM_READ(input_port_1_word_r)
	AM_RANGE(0x180004, 0x180005) AM_READ(input_port_2_word_r)
	AM_RANGE(0x180006, 0x180007) AM_READ(input_port_3_word_r)
#endif
ADDRESS_MAP_END

static ADDRESS_MAP_START( mugsmash_writemem, ADDRESS_SPACE_PROGRAM, 16 )
	AM_RANGE(0x000000, 0x07ffff) AM_WRITE(MWA16_ROM)
	AM_RANGE(0x080000, 0x080fff) AM_WRITE(mugsmash_videoram1_w) AM_BASE(&mugsmash_videoram1)
	AM_RANGE(0x082000, 0x082fff) AM_WRITE(mugsmash_videoram2_w) AM_BASE(&mugsmash_videoram2)
	AM_RANGE(0x0C0000, 0x0C0007) AM_WRITE(mugsmash_reg_w) AM_BASE(&mugsmash_regs1) 	/* video registers*/
	AM_RANGE(0x100000, 0x1005ff) AM_WRITE(paletteram16_xRRRRRGGGGGBBBBB_word_w) AM_BASE(&paletteram16)
	AM_RANGE(0x140000, 0x140007) AM_WRITE(mugsmash_reg2_w) AM_BASE(&mugsmash_regs2) /* sound + ? */
	AM_RANGE(0x1c0000, 0x1c3fff) AM_WRITE(MWA16_RAM) /* main ram? */
	AM_RANGE(0x1c4000, 0x1cffff) AM_WRITE(MWA16_RAM)
	AM_RANGE(0x200000, 0x203fff) AM_WRITE(MWA16_RAM) AM_BASE(&mugs_spriteram) /* sprite ram */
ADDRESS_MAP_END
#endif




UINT8 input_mugsmash_8r (UINT32 offset)
{
	UINT16 data = 0xff;

	offset &=0x07;
	offset ^=1;

	switch (offset&0x07)
	{
		case 0:
			data = (input_buffer[0] & 0xff);
			break;
		case 1:
			data = ((input_buffer[3] & 0xc0) >> 2) | ((input_buffer[2] & 0x03));
			break;
		case 2:
			data = (input_buffer[1] & 0xff);
			break;
		case 3:
			data = ((input_buffer[3] & 0x3f));
			break;
		case 4:
			data = 0xff;
			break;
		case 5 :
			data = ((input_buffer[4] & 0x3f));
			break;
		case 6:
			data = 0xff;
			break;
		case 7 :
			data = ((input_buffer[4] & 0xc0) >> 6);
			break;
	}

	return data;
}

UINT16 input_mugsmash_16r (UINT32 offset)
{
	offset &=0x0f;

	return input_mugsmash_8r(offset+1)|(input_mugsmash_8r(offset)<<8);
}

static void WriteOutByte(UINT32 address, UINT8 data)
{
	address &= 0x0F;
	RAM_OTHERREGS[address^1]=data;

	if(address==3)
		TechnosSoundWrite68k(address,data);
}

static void WriteOutWord(UINT32 address, UINT16 data)
{
	address &= 0x0F;
	WriteWord(&RAM_OTHERREGS[address],data);

	if(address==2)
		TechnosSoundWrite68k(address, (UINT8) (data&0xFF) );
}

static void load_mugsmash(void)
{
	/* In RAINE we allocate one big block of RAM to contain all emulated RAM then set some pointers to it

		Z80:
		0x10000 bytes z80

		0x10000 bytes MAIN RAM
		0x04000 bytes SPRITE RAM
		0x01000 bytes TILERAM1
		0x01000 bytes TILERAM2
		0x00600 bytes PALETTERAM
		0x00008 bytes VIDEO REGS
		0x00008 bytes OTHER REGS

	*/

	/* Calculate how much RAM we need to allocate */
	RAMSize=0x10000 /* for Z80 */
	       +0x10000 /* MAIN RAM */
	       +0x04000 /* SPRITE RAM */
	       +0x01000 /* TILERAM1*/
	       +0x01000 /* TILERAM2 */
	       +0x00800 /* PALETTE RAM */
	       +0x00008 /* VIDEO REGS */
	       +0x00010;/* OTHER REGS */

	/* Allocate the RAM */
	if(!(RAM=AllocateMem(RAMSize))) return;

	/* Set Up the Pointers */
	RAM_Z80       = &RAM[0x00000];
	RAM_MAIN      = &RAM[0x00000+0x10000];
	RAM_SPRITE    = &RAM[0x00000+0x10000+0x10000];
	RAM_TILEMAP1  = &RAM[0x00000+0x10000+0x10000+0x04000];
	RAM_TILEMAP2  = &RAM[0x00000+0x10000+0x10000+0x04000+0x01000];
	RAM_PALETTE   = &RAM[0x00000+0x10000+0x10000+0x04000+0x01000+0x01000];
	RAM_VIDREGS   = &RAM[0x00000+0x10000+0x10000+0x04000+0x01000+0x01000+0x00800];
	RAM_OTHERREGS = &RAM[0x00000+0x10000+0x10000+0x04000+0x01000+0x01000+0x00800+0x00008];

	/* uses Combatribes sound system */
	AddTechnosSoundOld(0x00A8, 0x0083, 0x8000, load_region[REGION_SMP1], 100);


	/* Setup Starscream 68000 core */

	/* ROM is a pointer to the ROM1 region.. automatically set up? */

	/* byteswap the ROM area.. */
	ByteSwap(ROM,get_region_size(REGION_CPU1));

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


	/* For running code.. */
	AddMemFetch (0x000000, 0x07ffff,                        ROM                      );
	AddMemFetch (0x1c0000, 0x1cffff,                        RAM_MAIN-0x1c0000        ); // note: you need to subtract the address?!

	/* ROM for normal READ Operations -- we don't want to allow writing to ROM! */
	AddReadBW   (0x000000, 0x07ffff,     NULL,              ROM             );   // 68000 ROM
	/* Set Up the RAM, we allow all types of READ/WRITE operations */

	AddRWBW     (0x080000, 0x080fff,     NULL,              RAM_TILEMAP1    );   // TILEMAP1 RAM
	AddRWBW     (0x082000, 0x082fff,     NULL,              RAM_TILEMAP2    );   // TILEMAP2 RAM
	AddRWBW     (0x0c0000, 0x0c0007,     NULL,              RAM_VIDREGS     );   // VIDEO REGS
	AddRWBW     (0x100000, 0x1005ff,     NULL,              RAM_PALETTE     );   // PALETTE RAM
	AddWriteByte(0x140000, 0x14000F,     WriteOutByte,      NULL            );   //
	AddWriteWord(0x140000, 0x14000F,     WriteOutWord,      NULL            );   //
	AddReadByte (0x180000, 0x18000f,    input_mugsmash_8r, NULL            );   // Inputs
	AddReadWord (0x180000, 0x18000f,    input_mugsmash_16r,NULL            );   // Inputs

	AddRWBW     (0x1c0000, 0x1cffff,     NULL,              RAM_MAIN        );   // MAIN RAM
	AddRWBW     (0x200000, 0x203fff,     NULL,              RAM_SPRITE      );   // MAIN RAM

	/* Make sure ALL other READS and WRITES (both BYTE and WORD) fall through to the
	   appropriate Bad Read / Write functions */
	finish_conf_68000(0);

	print_debug("Starscream Memory Init Done\n");

	/* Note: In RAINE the palette is handled like this */
	InitPaletteMap(RAM_PALETTE, 0x40, 0x10, 0x8000);
	set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);  /* rrr_rrgg_gggb_bbbb !! */
}


static struct VIDEO_INFO video_mugsmash =
{
   draw_mugsmash,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   mugsmash_gfx,
};
static struct DIR_INFO dir_mugsmash[] =
{
   { "mugsmash", },
   { "mug_smashers", },
   { NULL, },
};
GME( mugsmash, "Mug Smashers", ELECTRONIC_DEVICES,  1990, GAME_MISC);

