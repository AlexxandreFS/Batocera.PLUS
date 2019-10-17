/*
  DiverBoy
 - (c)Electronic Devices (Italy)

*/

/* Diverboy Directories and (automatic) Rom loading */

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

static UINT8 *RAM_Z80;
static UINT8 *RAM_MAIN;
static UINT8 *RAM_SPRITE;
static UINT8 *RAM_PALETTE;
static UINT8 *RAM_UNKNOWN1;
static UINT8 *RAM_UNKNOWN2;


static struct ROM_INFO rom_diverboy[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,     0x020000,
            "db_01.bin",  0x6aa11366, "db_02.bin",  0x45f8a673),
	{ "db_05.bin",    0x010000, 0xffeb49ec, REGION_ROM2, 0x000000, LOAD_NORMAL },
	{ "db_03.bin",    0x080000, 0x50457505, REGION_SMP1, 0x000000, LOAD_NORMAL }, // note, load at 0x040000, banks get memcpy'd to 0
	{ "db_04.bin",    0x020000, 0x01b81da0, REGION_SMP1, 0x0a0000, LOAD_NORMAL },
	{ "db_04.bin",    0x020000, 0x01b81da0, REGION_SMP1, 0x0e0000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,     0x080000,
            "db_08.bin",  0x7bb96220, "db_09.bin",  0x12b15476),
  LOAD8_16(  REGION_GFX2,  0x000000,     0x020000,
            "db_07.bin",  0x18485741, "db_10.bin",  0xc381d1cc),
  LOAD8_16(  REGION_GFX2,  0x040000,     0x020000,
            "db_06.bin",  0x21b4e352, "db_11.bin",  0x41d29c81),
	{ NULL, 0, 0, 0, 0, 0 }
};



/* Inputs and Dipswitches */

/* if the address (3rd param) here is <0x100 the input is stored in input_buffer..*/

static struct INPUT_INFO input_diverboy[] =
{
	INP0( P1_UP, 0x0001, 0x01 ),
	INP0( P1_DOWN, 0x0001, 0x02 ),
	INP0( P1_LEFT, 0x0001, 0x04 ),
	INP0( P1_RIGHT, 0x0001, 0x08 ),
	INP0( P1_B1, 0x0001, 0x10 ),
	INP0( P1_B2, 0x0001, 0x20 ),
	INP0( P1_B3, 0x0001, 0x40 ),
	INP0( P1_START, 0x0001, 0x80 ),

	INP0( P2_UP, 0x0000, 0x01 ),
	INP0( P2_DOWN, 0x0000, 0x02 ),
	INP0( P2_LEFT, 0x0000, 0x04 ),
	INP0( P2_RIGHT, 0x0000, 0x08 ),
	INP0( P2_B1, 0x0000, 0x10 ),
	INP0( P2_B2, 0x0000, 0x20 ),
	INP0( P2_B3, 0x0000, 0x40 ),
	INP0( P2_START, 0x0000, 0x80 ),

	INP0( COIN1, 0x0008, 0x01 ),
	INP0( COIN2, 0x0008, 0x02 ),
	INP0( COIN3, 0x0008, 0x04 ),
/*                                            0x08, VBLANK          */
	END_INPUT
};

static struct DSW_DATA dsw_data_diverboy_1[] =
{
  { MSG_COINAGE, 0x07, 8 },
  { MSG_4COIN_1PLAY, 0x07},
  { MSG_3COIN_1PLAY, 0x06},
  { MSG_2COIN_1PLAY, 0x05},
  { MSG_1COIN_1PLAY, 0x00},
  { MSG_1COIN_2PLAY, 0x01},
  { MSG_1COIN_3PLAY, 0x02},
  { MSG_1COIN_4PLAY, 0x03},
  { MSG_1COIN_6PLAY, 0x04},
  { MSG_LIVES, 0x08, 2 },
  { "2", 0x00},
  { "3", 0x08},
  { _("Display Copyright"), 0x10, 2 },
  { MSG_NO, 0x00},
  { MSG_YES, 0x10},
  { MSG_DIFFICULTY, 0x60, 4 },
  { MSG_EASY, 0x00},
  { MSG_NORMAL, 0x20},
  { MSG_HARD, 0x40},
  { MSG_HARDEST, 0x60},
  { MSG_FREE_PLAY, 0x80, 2 },
  { MSG_NO, 0x80},
  { MSG_YES, 0x00},
  { NULL, 0}
};

static struct DSW_INFO dsw_diverboy[] =
{
  { 0x2, 0xb8, dsw_data_diverboy_1 },
  { 0, 0, NULL }
};

/* Sound Hardware */

static struct OKIM6295interface okim6295_interface =
{
	1,			/* 1 chip */
	{ 10000 },		/* 7575Hz playback? */
	{ REGION_SMP1 },
	{ 240 }
};

static struct SOUND_INFO sound_diverboy[] =
{
   { SOUND_M6295,    &okim6295_interface   },
   { 0,              NULL,                 },
};

/* Drawing */

static void draw_diverboy(void)
{
	static int framecounter = 0;
	UINT8* map;
	UINT8 *source;
	UINT8 *finish;

	framecounter++;

	ClearPaletteMap();

	/* this might not be needed, most of the time a solid set of sprites is drawn.. */
	MAP_PALETTE_MAPPED_NEW(0x0,16,map);
	clear_game_screen(ReadLong(&map[0]));

	source = RAM_SPRITE;
	finish = source + 0x4000;

	while (source < finish)
	{
		INT16 xpos,ypos,number,colr,bank,flash,solid;

		ypos = source[8]|(source[9]<<8);
		xpos = source[0]|(source[1]<<8);
		colr = (source[2]& 0xf0) >> 4;
		number = source[6]|(source[7]<<8);
		flash = source[3] & 0x10;
		solid = source[2] & 0x08;
		colr |= ((source[2] & 0x0c) << 2);

		ypos = 0x100 - ypos;
		xpos = 0x100 - xpos;

		/* fine-tune sprite pos */
		xpos +=64-13;
		ypos -=16;

		/* adjust for raine clipping area */
		xpos+=32;
		ypos+=32;


		bank = (source[2]&0x02) >> 1;

		if((xpos<=16)||(xpos>=320+32)) { source+=16; continue;}
		if((ypos<=16)||(ypos>=240+32)) { source+=16; continue;}

		if (!flash || (framecounter & 1))
		{
			if (!bank)
			{
				if(gfx1_solid[number])   // No pixels; skip
				{

					MAP_PALETTE_MAPPED_NEW(
						colr,
						16,
						map
					);

					if( (gfx1_solid[number]==1) && (!solid) ) // Some pixels; trans
						Draw16x16_Trans_Mapped_Rot       (&gfx1[number<<8], xpos, ypos, map);
					else                           // all pixels; solid
						Draw16x16_Mapped_Rot             (&gfx1[number<<8], xpos, ypos, map);
				}
			}
			else
			{
				if(gfx2_solid[number])   // No pixels; skip
				{

					MAP_PALETTE_MAPPED_NEW(
						colr,
						16,
						map
					);

					if( (gfx2_solid[number]==1) && (!solid) ) // Some pixels; trans
						Draw16x16_Trans_Mapped_Rot       (&gfx2[number<<8], xpos, ypos, map);
					else                           // all pixels; solid
						Draw16x16_Mapped_Rot             (&gfx2[number<<8], xpos, ypos, map);
				}



			}
		}



		source+=16;
	}


}

/* Video Setup */

static gfx_layout diverboy_16x16tiles =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0,1,2,3 },
//	{  4, 0,  12, 8,  20, 16, 28, 24,
//	  36, 32, 44, 40, 52, 48, 60, 56 },
	{  56, 60,  48, 52,  40, 44, 32, 36,
	  24, 28, 16, 20, 8, 12, 0, 4 },
	{ 0*64, 1*64, 2*64,  3*64,  4*64,  5*64,  6*64,  7*64,
	  8*64, 9*64, 10*64, 11*64, 12*64, 13*64, 14*64, 15*64 },
	16*64
};


static struct GFX_LIST diverboy_gfx[] =
{
   { REGION_GFX1, &diverboy_16x16tiles, },
   { REGION_GFX2, &diverboy_16x16tiles, },
   { 0,           NULL,           },
};



/* System (execute) */

/* instead of a MACHINE_DRIVER (as in MAME) the CPU speeds etc. are handled
   here by calling the execute functions for each CPU core, likewise the
   interrupts */

#define FRAME CPU_FRAME_MHz(16,60)

static void execute_diverboy(void)
{
	input_buffer[8] &= 0xf7;
	cpu_execute_cycles(CPU_68K_0, FRAME); // Main 68000
	input_buffer[8] |= 0x08;
	cpu_interrupt(CPU_68K_0, 6);


	if (RaineSoundCard)
		execute_z80_audio_frame();

	cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(1,60)); // run a bit of code with vbl set
}
/* Load Roms / Set Memory Map */



static void sound_diverboy_w(UINT32 address, UINT32 data)
{
 	latch = data;
// 	printf("diversound %02x\n",data);
 	cpu_interrupt(CPU_Z80_0, 0x38);
//	ExitOnEI=1; // ??
	cpu_execute_cycles(CPU_Z80_0, 1000);

}

static void diverboy_sample_bank_w ( UINT32 address, UINT32 data)
{
	data &=0x03;
	/* saves memory, but not as fast as if we expanded on startup */
	// memcpy(load_region[REGION_SMP1],load_region[REGION_SMP1]+0x40000+(0x20000*data),0x20000);
	OKIM6295_set_bank_base(0,ALL_VOICES, (data & 3) * 0x40000);
}


static void load_diverboy(void)
{
	/* In RAINE we allocate one big block of RAM to contain all emulated RAM then set some pointers to it

		Z80:
		0x10000 bytes z80

		68000:
	    0x10000 bytes MAIN ram
	    0x04000 bytes SPRITE ram
	    0x00800 bytes PALETTE ram
	    0x00800 bytes UNKNOWN1 ram
	    0x00800 bytes UNKNOWN2 ram
	*/

	/* Calculate how much RAM we need to allocate */
	RAMSize=0x10000 /* for Z80 */
	       +0x10000 /* MAIN RAM */
	       +0x04000 /* SPRITE RAM */
	       +0x00800 /* PALETTE RAM*/
	       +0x00800 /* UNKNOWN1 RAM */
	       +0x00800;/* UNKONWN2 RAM */

	/* Allocate the RAM */
	if(!(RAM=AllocateMem(RAMSize))) return;

	/* Set Up the Pointers */
	RAM_Z80       = &RAM[0x00000];
	RAM_MAIN      = &RAM[0x00000+0x10000];
	RAM_SPRITE    = &RAM[0x00000+0x10000+0x10000];
	RAM_PALETTE   = &RAM[0x00000+0x10000+0x10000+0x04000];
	RAM_UNKNOWN1  = &RAM[0x00000+0x10000+0x10000+0x04000+0x00800];
	RAM_UNKNOWN2  = &RAM[0x00000+0x10000+0x10000+0x04000+0x00800+0x00800];

	/* Shuffle the Z80 Rom and Samples around a little.. */
	/* 2nd half of the z80 rom contains the code.. first half is blank for some reason */
	memcpy(load_region[REGION_ROM2],load_region[REGION_ROM2]+0x8000,0x8000);
	/* lower 0x20000 bytes of samples are banked.. upper 0x20000 bytes are fixed, set a default bank */
	/* REGION SOUND1 is totally messy. Here is the setup:
	ROM_LOAD( "db_03.bin", 0x00000, 0x20000, CRC(50457505) SHA1(faf1c055ec56d2ed7f5e6993cc04d3317bf1c3cc) )
	ROM_CONTINUE(          0x40000, 0x20000 )
	ROM_CONTINUE(          0x80000, 0x20000 )
	ROM_CONTINUE(          0xc0000, 0x20000 )
	ROM_LOAD( "db_04.bin", 0x20000, 0x20000, CRC(01b81da0) SHA1(914802f3206dc59a720af9d57eb2285bc8ba822b) )
	ROM_RELOAD(            0x60000, 0x20000 )
	ROM_RELOAD(            0xa0000, 0x20000 )
	ROM_RELOAD(            0xe0000, 0x20000 )
	In raine I load this in 2 blocks of course :
	{ "db_03.bin",    0x080000, 0x50457505, REGION_SMP1, 0x000000, LOAD_NORMAL }, // note, load at 0x040000, banks get memcpy'd to 0
	{ "db_04.bin",    0x020000, 0x01b81da0, REGION_SMP1, 0x0a0000, LOAD_NORMAL },
	{ "db_04.bin",    0x020000, 0x01b81da0, REGION_SMP1, 0x0e0000, LOAD_NORMAL },
	*/

	memcpy(load_region[REGION_SMP1]+0xc0000, load_region[REGION_SMP1]+0x60000,0x20000);
	memcpy(load_region[REGION_SMP1]+0x80000, load_region[REGION_SMP1]+0x40000,0x20000);
	memcpy(load_region[REGION_SMP1]+0x40000, load_region[REGION_SMP1]+0x20000,0x20000);

	memcpy(load_region[REGION_SMP1]+0x60000,load_region[REGION_SMP1]+0xa0000,0x20000);
	memcpy(load_region[REGION_SMP1]+0x20000,load_region[REGION_SMP1]+0xa0000,0x20000);

	/* Set up the Z80 Memory Map (Sound CPU) */
	AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

	AddZ80AReadByte (0x0000, 0x7fff, NULL,                     load_region[REGION_ROM2] ); // Z80 ROM
	AddZ80AReadByte (0x8000, 0x87ff, NULL,                     RAM_Z80                  );
	AddZ80AReadByte (0x9800, 0x9800, OKIM6295_status_0_r,      NULL                     );
	AddZ80AReadByte (0xa000, 0xa000, NULL,                     (UINT8*)&latch           );

	AddZ80AWriteByte(0x8000, 0x87ff, NULL,                     RAM_Z80                  ); // Z80 RAM
	AddZ80AWriteByte(0x9000, 0x9000, diverboy_sample_bank_w,   NULL                     );
	AddZ80AWriteByte(0x9800, 0x9800, OKIM6295_data_0_w,        NULL                     );

	/* all unmapped reads go here */
	AddZ80AReadByte (0x0000, 0xFFFF, DefBadReadZ80,            NULL                     );
	AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,           NULL                     );
	AddZ80AReadPort (  0x00,   0xFF, DefBadReadZ80,            NULL                     );
	AddZ80AWritePort(  0x00,   0xFF, DefBadWriteZ80,           NULL                     );

	/* terminate lists */
	AddZ80AReadByte (    -1,     -1, NULL,                     NULL                     );
	AddZ80AWriteByte(    -1,     -1, NULL,                     NULL                     );
	AddZ80AReadPort (    -1,     -1, NULL,                     NULL                     );
	AddZ80AWritePort(    -1,     -1, NULL,                     NULL                     );

	AddZ80AInit();

	setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(7,60)); // for the Z80 we need to set up the speed here..

	print_debug("z80 Init Done\n");



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
	AddMemFetch (0x000000, 0x03ffff,                        ROM                      );
	AddMemFetch (0x040000, 0x04ffff,                        RAM_MAIN-0x040000        ); // note: you need to subtract the address?!

	/* ROM for normal READ Operations -- we don't want to allow writing to ROM! */
	AddReadBW   (0x000000, 0x03ffff,     NULL,              ROM             );   // 68000 ROM
	/* Set Up the RAM, we allow all types of READ/WRITE operations */
	AddRWBW     (0x040000, 0x04ffff,     NULL,              RAM_MAIN        );   // MAIN RAM
	AddRWBW     (0x080000, 0x083fff,     NULL,              RAM_SPRITE      );   // SPRITE RAM
	AddWriteWord(0x100000, 0x100001,    sound_diverboy_w,   NULL            );   // sound
	AddRWBW     (0x140000, 0x1407ff,     NULL,              RAM_PALETTE     );   // PALETTE RAM
	AddReadByte (0x180000, 0x18000f,    NULL, input_buffer            );   // Inputs
	AddReadWord (0x180000, 0x18000f,    NULL, input_buffer            );   // Inputs
	AddRWBW     (0x320000, 0x3207ff,     NULL,              RAM_UNKNOWN1    );   // UNKNOWN1 RAM
	AddRWBW     (0x322000, 0x3227ff,     NULL,              RAM_UNKNOWN2    );   // UNKNOWN2 RAM


	/* Handler for the Inputs */

	finish_conf_68000(0);

	/* Note: In RAINE the palette is handled like this */
	InitPaletteMap(RAM_PALETTE, 0x40, 0x10, 0x8000);
	set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);

	print_debug("GFX are Set Up\n");

}


static struct VIDEO_INFO video_diverboy =
{
   draw_diverboy,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   diverboy_gfx,
};
static struct DIR_INFO dir_diverboy[] =
{
   { "diverboy", },
   { "diver_boy", },
   { NULL, },
};
GME( diverboy, "Diverboy", ELECTRONIC_DEVICES, 1995, GAME_MISC);

