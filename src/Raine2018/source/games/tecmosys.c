#define DRV_DEF_VIDEO &video_gaiden
#define DRV_DEF_EXEC execute_gaiden
#define DRV_DEF_SOUND sound_gaiden
/******************************************************************************/
/*                                                                            */
/*                       NINJA GAIDEN (C)1988 TECMO                           */
/*                                                                            */
/*                       TECMO KNIGHT (C)1989 TECMO                           */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "2203intf.h"
#include "sasound.h"		// sample support routines
#include "adpcm.h"
#include "timer.h"

static struct ROM_INFO rom_shadoww[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "shadowa.1",  0x8290d567, "shadowa.2",  0xf3f08921),
  { "gaiden.3", 0x10000, 0x75fd3e6a, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "gaiden.5", 0x10000, 0x8d4035f7, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "14.bin", 0x20000, 0x1ecfddaa, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "15.bin", 0x20000, 0x1291a696, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "16.bin", 0x20000, 0x140b47ca, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "17.bin", 0x20000, 0x7638cccb, REGION_GFX2, 0x060000, LOAD_NORMAL },
  { "18.bin", 0x20000, 0x3fadafd6, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "19.bin", 0x20000, 0xddae9d5b, REGION_GFX3, 0x020000, LOAD_NORMAL },
  { "20.bin", 0x20000, 0x08cf7a93, REGION_GFX3, 0x040000, LOAD_NORMAL },
  { "21.bin", 0x20000, 0x1ac892f5, REGION_GFX3, 0x060000, LOAD_NORMAL },
  { "gaiden.6", 0x20000, 0xe7ccdf9f, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "gaiden.8", 0x20000, 0x7ef7f880, REGION_GFX4, 0x020000, LOAD_NORMAL },
  { "gaiden.10", 0x20000, 0xa6451dec, REGION_GFX4, 0x040000, LOAD_NORMAL },
  { "shadoww.12a", 0x10000, 0x9bb07731, REGION_GFX4, 0x060000, LOAD_NORMAL },
  { "shadoww.12b", 0x10000, 0xa4a950a2, REGION_GFX4, 0x070000, LOAD_NORMAL },
  { "gaiden.7", 0x20000, 0x016bec95, REGION_GFX4, 0x080000, LOAD_NORMAL },
  { "gaiden.9", 0x20000, 0x6e9b7fd3, REGION_GFX4, 0x0a0000, LOAD_NORMAL },
  { "gaiden.11", 0x20000, 0x7fbfdf5e, REGION_GFX4, 0x0c0000, LOAD_NORMAL },
  { "shadoww.13a", 0x10000, 0x996d2fa5, REGION_GFX4, 0x0e0000, LOAD_NORMAL },
  { "shadoww.13b", 0x10000, 0xb8df8a34, REGION_GFX4, 0x0f0000, LOAD_NORMAL },
  { "gaiden.4", 0x20000, 0xb0e0faf9, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_shadowwa[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "shadoww.1",  0xfefba387, "shadoww.2",  0x9b9d6b18),
  { "gaiden.3", 0x10000, 0x75fd3e6a, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "gaiden.5", 0x10000, 0x8d4035f7, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "14.bin", 0x20000, 0x1ecfddaa, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "15.bin", 0x20000, 0x1291a696, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "16.bin", 0x20000, 0x140b47ca, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "17.bin", 0x20000, 0x7638cccb, REGION_GFX2, 0x060000, LOAD_NORMAL },
  { "18.bin", 0x20000, 0x3fadafd6, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "19.bin", 0x20000, 0xddae9d5b, REGION_GFX3, 0x020000, LOAD_NORMAL },
  { "20.bin", 0x20000, 0x08cf7a93, REGION_GFX3, 0x040000, LOAD_NORMAL },
  { "21.bin", 0x20000, 0x1ac892f5, REGION_GFX3, 0x060000, LOAD_NORMAL },
  { "gaiden.6", 0x20000, 0xe7ccdf9f, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "gaiden.8", 0x20000, 0x7ef7f880, REGION_GFX4, 0x020000, LOAD_NORMAL },
  { "gaiden.10", 0x20000, 0xa6451dec, REGION_GFX4, 0x040000, LOAD_NORMAL },
  { "shadoww.12a", 0x10000, 0x9bb07731, REGION_GFX4, 0x060000, LOAD_NORMAL },
  { "shadoww.12b", 0x10000, 0xa4a950a2, REGION_GFX4, 0x070000, LOAD_NORMAL },
  { "gaiden.7", 0x20000, 0x016bec95, REGION_GFX4, 0x080000, LOAD_NORMAL },
  { "gaiden.9", 0x20000, 0x6e9b7fd3, REGION_GFX4, 0x0a0000, LOAD_NORMAL },
  { "gaiden.11", 0x20000, 0x7fbfdf5e, REGION_GFX4, 0x0c0000, LOAD_NORMAL },
  { "shadoww.13a", 0x10000, 0x996d2fa5, REGION_GFX4, 0x0e0000, LOAD_NORMAL },
  { "shadoww.13b", 0x10000, 0xb8df8a34, REGION_GFX4, 0x0f0000, LOAD_NORMAL },
  { "gaiden.4", 0x20000, 0xb0e0faf9, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_gaiden[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "gaiden.1",  0xe037ff7c, "gaiden.2",  0x454f7314),
  { "gaiden.3", 0x10000, 0x75fd3e6a, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "gaiden.5", 0x10000, 0x8d4035f7, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "14.bin", 0x20000, 0x1ecfddaa, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "15.bin", 0x20000, 0x1291a696, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "16.bin", 0x20000, 0x140b47ca, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "17.bin", 0x20000, 0x7638cccb, REGION_GFX2, 0x060000, LOAD_NORMAL },
  { "18.bin", 0x20000, 0x3fadafd6, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "19.bin", 0x20000, 0xddae9d5b, REGION_GFX3, 0x020000, LOAD_NORMAL },
  { "20.bin", 0x20000, 0x08cf7a93, REGION_GFX3, 0x040000, LOAD_NORMAL },
  { "21.bin", 0x20000, 0x1ac892f5, REGION_GFX3, 0x060000, LOAD_NORMAL },
  { "gaiden.6", 0x20000, 0xe7ccdf9f, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "gaiden.8", 0x20000, 0x7ef7f880, REGION_GFX4, 0x020000, LOAD_NORMAL },
  { "gaiden.10", 0x20000, 0xa6451dec, REGION_GFX4, 0x040000, LOAD_NORMAL },
  { "gaiden.12", 0x20000, 0x90f1e13a, REGION_GFX4, 0x060000, LOAD_NORMAL },
  { "gaiden.7", 0x20000, 0x016bec95, REGION_GFX4, 0x080000, LOAD_NORMAL },
  { "gaiden.9", 0x20000, 0x6e9b7fd3, REGION_GFX4, 0x0a0000, LOAD_NORMAL },
  { "gaiden.11", 0x20000, 0x7fbfdf5e, REGION_GFX4, 0x0c0000, LOAD_NORMAL },
  { "gaiden.13", 0x20000, 0x7d9f5c5e, REGION_GFX4, 0x0e0000, LOAD_NORMAL },
  { "gaiden.4", 0x20000, 0xb0e0faf9, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ryukendn[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "ryukendn.1",  0x6203a5e2, "ryukendn.2",  0x9e99f522),
  { "ryukendn.3", 0x10000, 0x6b686b69, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "ryukendn.5", 0x10000, 0x765e7baa, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "14.bin", 0x20000, 0x1ecfddaa, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "15.bin", 0x20000, 0x1291a696, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "16.bin", 0x20000, 0x140b47ca, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "17.bin", 0x20000, 0x7638cccb, REGION_GFX2, 0x060000, LOAD_NORMAL },
  { "18.bin", 0x20000, 0x3fadafd6, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "19.bin", 0x20000, 0xddae9d5b, REGION_GFX3, 0x020000, LOAD_NORMAL },
  { "20.bin", 0x20000, 0x08cf7a93, REGION_GFX3, 0x040000, LOAD_NORMAL },
  { "21.bin", 0x20000, 0x1ac892f5, REGION_GFX3, 0x060000, LOAD_NORMAL },
  { "gaiden.6", 0x20000, 0xe7ccdf9f, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "gaiden.8", 0x20000, 0x7ef7f880, REGION_GFX4, 0x020000, LOAD_NORMAL },
  { "gaiden.10", 0x20000, 0xa6451dec, REGION_GFX4, 0x040000, LOAD_NORMAL },
  { "shadoww.12a", 0x10000, 0x9bb07731, REGION_GFX4, 0x060000, LOAD_NORMAL },
  { "ryukendn.12b", 0x10000, 0x1773628a, REGION_GFX4, 0x070000, LOAD_NORMAL },
  { "gaiden.7", 0x20000, 0x016bec95, REGION_GFX4, 0x080000, LOAD_NORMAL },
  { "ryukendn.9a", 0x10000, 0xc821e200, REGION_GFX4, 0x0a0000, LOAD_NORMAL },
  { "ryukendn.9b", 0x10000, 0x6a6233b3, REGION_GFX4, 0x0b0000, LOAD_NORMAL },
  { "gaiden.11", 0x20000, 0x7fbfdf5e, REGION_GFX4, 0x0c0000, LOAD_NORMAL },
  { "shadoww.13a", 0x10000, 0x996d2fa5, REGION_GFX4, 0x0e0000, LOAD_NORMAL },
  { "ryukendn.13b", 0x10000, 0x1f43c507, REGION_GFX4, 0x0f0000, LOAD_NORMAL },
  { "gaiden.4", 0x20000, 0xb0e0faf9, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_tknight[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "tkni1.bin",  0x9121daa8, "tkni2.bin",  0x6669cd87),
  { "tkni3.bin", 0x10000, 0x15623ec7, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "tkni5.bin", 0x10000, 0x5ed15896, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "tkni7.bin", 0x80000, 0x4b4d4286, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "tkni6.bin", 0x80000, 0xf68fafb1, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "tkni9.bin", 0x80000, 0xd22f4239, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "tkni8.bin", 0x80000, 0x4931b184, REGION_GFX4, 0x080000, LOAD_NORMAL },
  { "tkni4.bin", 0x20000, 0xa7a1dbcf, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_wildfang[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "1.3st",  0xab876c9b, "2.5st",  0x1dc74b3b),
  { "tkni3.bin", 0x10000, 0x15623ec7, REGION_ROM2, 0x0000, LOAD_NORMAL },
  { "tkni5.bin", 0x10000, 0x5ed15896, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "14.3a", 0x20000, 0x0d20c10c, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "15.3b", 0x20000, 0x3f40a6b4, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "16.1a", 0x20000, 0x0f31639e, REGION_GFX2, 0x040000, LOAD_NORMAL },
  { "17.1b", 0x20000, 0xf32c158e, REGION_GFX2, 0x060000, LOAD_NORMAL },
  { "tkni6.bin", 0x80000, 0xf68fafb1, REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "tkni9.bin", 0x80000, 0xd22f4239, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "tkni8.bin", 0x80000, 0x4931b184, REGION_GFX4, 0x080000, LOAD_NORMAL },
  { "tkni4.bin", 0x20000, 0xa7a1dbcf, REGION_SMP1, 0x0000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

#if 0

/* raiga/stratof have protection + differences for graphics. See mame source for the
   details. */

#define NO_DUMP 0

static struct ROM_INFO stratof_roms[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "1.3s",  0x060822a4, "2.4s",  0x339358fa),
  { "a-4b.3", 0x10000, 0x18655c95, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "a-6v.mcu", 0x1000, NO_DUMP , REGION_CPU3, 0x00000, LOAD_NORMAL },
  { "b-7a.5", 0x10000, 0x6d2e4bf1, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "b-1b", 0x80000, 0x781d1bd2, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "b-4b", 0x80000, 0x89468b84, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "b-2m", 0x80000, 0x5794ec32, REGION_GFX4, 0x00000, LOAD_NORMAL },
  { "b-1m", 0x80000, 0xb0de0ded, REGION_GFX4, 0x80000, LOAD_NORMAL },
  { "a-4a.4", 0x20000, 0xef9acdcf, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO raiga_roms[] =
{
  LOAD8_16(  REGION_ROM1,  0x00000,  0x20000,
            "a-3s.1",  0x303c2a6c, "a-4s.2",  0x5f31fecb),
  { "a-4b.3", 0x10000, 0x18655c95, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "a-6v.mcu", 0x1000, NO_DUMP , REGION_CPU3, 0x00000, LOAD_NORMAL },
  { "b-7a.5", 0x10000, 0x6d2e4bf1, REGION_GFX1, 0x00000, LOAD_NORMAL },
  { "b-1b", 0x80000, 0x781d1bd2, REGION_GFX2, 0x00000, LOAD_NORMAL },
  { "b-4b", 0x80000, 0x89468b84, REGION_GFX3, 0x00000, LOAD_NORMAL },
  { "b-2m", 0x80000, 0x5794ec32, REGION_GFX4, 0x00000, LOAD_NORMAL },
  { "b-1m", 0x80000, 0xb0de0ded, REGION_GFX4, 0x80000, LOAD_NORMAL },
  { "a-4a.4", 0x20000, 0xef9acdcf, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

#endif







static GfxLayout tilelayout =
{
	8,8,	/* tile size */
	RGN_FRAC(1,1),	/* number of tiles */
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },
	{ 0*4, 1*4, 2*4, 3*4, 4*4, 5*4, 6*4, 7*4 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8	/* offset to next tile */
};

static GfxLayout tile2layout =
{
	16,16,	/* tile size */
	RGN_FRAC(1,1),	/* number of tiles */
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },	/* the bitplanes are packed in one nibble */
	{ 0*4, 1*4, 2*4, 3*4, 4*4, 5*4, 6*4, 7*4,
	  32*8+0*4, 32*8+1*4, 32*8+2*4, 32*8+3*4,
	  32*8+4*4, 32*8+5*4, 32*8+6*4, 32*8+7*4,},
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32,
	  16*32, 17*32, 18*32, 19*32, 20*32, 21*32, 22*32, 23*32},
	128*8	/* offset to next tile */
};

static GfxLayout spritelayout =
{
	8,8,	/* sprites size */
	RGN_FRAC(1,2),	/* number of sprites */
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },	/* the bitplanes are packed in one nibble */
	{ 0,4,RGN_FRAC(1,2),4+RGN_FRAC(1,2),8,12,8+RGN_FRAC(1,2),12+RGN_FRAC(1,2) },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
	16*8	/* offset to next sprite */
};

static struct GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &tilelayout }, // 4096 - 256 color banks
	{ REGION_GFX2, &tile2layout }, // 4096 - 768 color banks
	{ REGION_GFX3, &tile2layout }, // 4096 - 512 color banks
	{ REGION_GFX4, &spritelayout }, // 4096 -   0 color banks

	{ 0, NULL } /* end of array */
};

static struct INPUT_INFO input_shadoww[] =
{
   INP0( COIN1, 0x01A000, 0x40 ),
   INP0( COIN2, 0x01A000, 0x80 ),

   INP0( P1_START, 0x01A000, 0x01 ),
   INP0( P1_UP, 0x01A002, 0x08 ),
   INP0( P1_DOWN, 0x01A002, 0x04 ),
   INP0( P1_LEFT, 0x01A002, 0x01 ),
   INP0( P1_RIGHT, 0x01A002, 0x02 ),
   INP0( P1_B1, 0x01A002, 0x20 ),
   INP0( P1_B2, 0x01A002, 0x40 ),
   INP0( P1_B3, 0x01A002, 0x10 ),

   INP0( P2_START, 0x01A000, 0x02 ),
   INP0( P2_UP, 0x01A003, 0x08 ),
   INP0( P2_DOWN, 0x01A003, 0x04 ),
   INP0( P2_LEFT, 0x01A003, 0x01 ),
   INP0( P2_RIGHT, 0x01A003, 0x02 ),
   INP0( P2_B1, 0x01A003, 0x20 ),
   INP0( P2_B2, 0x01A003, 0x40 ),
   INP0( P2_B3, 0x01A003, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_ninja_gaiden_0[] =
{
   DSW_DEMO_SOUND( 0x01, 0x00),
   DSW_SCREEN( 0x02, 0x00),
   { MSG_COIN2,               0x1c, 0x08 },
   { MSG_5COIN_1PLAY,         0x00},
   { MSG_4COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x08},
   { MSG_2COIN_1PLAY,         0x04},
   { MSG_1COIN_1PLAY,         0x1c},
   { MSG_1COIN_2PLAY,         0x0c},
   { MSG_1COIN_3PLAY,         0x14},
   { MSG_1COIN_4PLAY,         0x18},
   { MSG_COIN1,               0xe0, 0x08 },
   { MSG_5COIN_1PLAY,         0x00},
   { MSG_4COIN_1PLAY,         0x80},
   { MSG_3COIN_1PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_1COIN_1PLAY,         0xe0},
   { MSG_1COIN_2PLAY,         0x60},
   { MSG_1COIN_3PLAY,         0xa0},
   { MSG_1COIN_4PLAY,         0xc0},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_ninja_gaiden_1[] =
{
   { MSG_UNKNOWN,             0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_DIFFICULTY,          0x0c, 0x03 },	// enemy _("recovery") time
   { MSG_NORMAL,              0x0c},
   { MSG_HARD,                0x04},
   { MSG_HARDEST,             0x00},
   { _("Energy"),                0x30, 0x04 },
   { "2",                     0x00},
   { "3",                     0x30},
   { "4",                     0x10},
   { "5",                     0x20},
   { MSG_LIVES,               0xc0, 0x04 },
   { "1",                     0x00},
   { "2",                     0xc0},
   { "3",                     0x40},
   { "4",                     0x80},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_shadoww[] =
{
   { 0x01A005, 0xFF, dsw_data_ninja_gaiden_0 },
   { 0x01A004, 0x7F, dsw_data_ninja_gaiden_1 },
   { 0,        0,    NULL,      },
};


static struct YM2203interface ym2203_interface =
{
  2,				// 2 x YM2203
  4000000,			// Rate - Guessed
  {YM2203_VOL(160,60),YM2203_VOL(160,60)},	// Volume Control
  { 0,		0 },
  { 0,		0 },
  { 0,		0 },
  { 0,		0 },
  { z80_irq_handler }
};

static struct OKIM6295interface m6295_interface =
{
   1,					// 1 chip
   { 15700/2 },				// rate
   { REGION_SOUND1 },		// rom list
   { 100 },
};

static struct SOUND_INFO sound_gaiden[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { SOUND_M6295,   &m6295_interface,     },
   { 0,             NULL,                 },
};

static struct INPUT_INFO input_wildfang[] =
{
   INP0( COIN1, 0x01A000, 0x40 ),
   INP0( COIN2, 0x01A000, 0x80 ),

   INP0( P1_START, 0x01A000, 0x01 ),
   INP0( P1_UP, 0x01A002, 0x08 ),
   INP0( P1_DOWN, 0x01A002, 0x04 ),
   INP0( P1_LEFT, 0x01A002, 0x01 ),
   INP0( P1_RIGHT, 0x01A002, 0x02 ),
   INP0( P1_B1, 0x01A002, 0x20 ),
   INP0( P1_B2, 0x01A002, 0x10 ),
   INP0( P1_B3, 0x01A002, 0x40 ),

   INP0( P2_START, 0x01A000, 0x02 ),
   INP0( P2_UP, 0x01A003, 0x08 ),
   INP0( P2_DOWN, 0x01A003, 0x04 ),
   INP0( P2_LEFT, 0x01A003, 0x01 ),
   INP0( P2_RIGHT, 0x01A003, 0x02 ),
   INP0( P2_B1, 0x01A003, 0x20 ),
   INP0( P2_B2, 0x01A003, 0x10 ),
   INP0( P2_B3, 0x01A003, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_tecmo_knight_1[] =
{
   { MSG_UNKNOWN,             0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_DIFFICULTY,          0x0c, 0x04 },	// enemy _("recovery") time
   { MSG_EASY,                0x04},
   { MSG_NORMAL,              0x0c},
   { MSG_HARD,                0x08},
   { MSG_HARDEST,             0x00},
   { MSG_UNKNOWN,             0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_LIVES,               0xc0, 0x03 },
   { "1",                     0x80},
   { "2",                     0xc0},
   { "3",                     0x40},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_wildfang[] =
{
   { 0x01A005, 0xFF, dsw_data_ninja_gaiden_0 },
   { 0x01A004, 0x7F, dsw_data_tecmo_knight_1 },
   { 0,        0,    NULL,      },
};

static int sport=0;

static void CtrlWriteB(UINT32 offset,UINT8 data)
{

   if((offset==0x7A802)||(offset==0x7A803)){
      sport=data&0xFF;
      print_debug("68000 Sends $%02x\n",sport);
      cpu_int_nmi(CPU_Z80_0);
   }

   offset-=0x60000;
   offset&=0x1FFFF;

   RAM[offset^1]=data;
}

static UINT16 SoundReadZ80(UINT16 address)
{
   print_debug("Z80 Receives $%02x\n",sport);
   return sport;
}

static void AddTecmoSound(UINT32 p1, UINT32 p2)
{

   // Apply Speed Patch
   // -----------------

  if (p1) {
    Z80ROM[p1+0]=0xD3;	// OUTA (AAh)
    Z80ROM[p1+1]=0xAA;	//

    SetStopZ80Mode2( (UINT16) p2);
  }

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xF7FF, NULL,			Z80ROM+0x0000);	// Z80 ROM/RAM
   AddZ80AReadByte(0xF800, 0xF800, M6295_A_Read_Z80,		NULL);		// ADPCM
   //AddZ80AReadByte(0xF810, 0xF811, YM2203AReadZ80,		NULL);		// YM2203 A
   //AddZ80AReadByte(0xF820, 0xF821, YM2203BReadZ80,		NULL);		// YM2203 B
   AddZ80AReadByte(0xFC20, 0xFC20, SoundReadZ80,		NULL);		// 68000 COMM
   AddZ80AReadByte(0x0000, 0xFFFF, NULL,			Z80ROM+0x0000);	// <test>
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0xF000, 0xF7FF, NULL,			Z80ROM+0xF000);	// Z80 RAM
   AddZ80AWriteByte(0xF800, 0xF800, M6295_A_Write_Z80,		NULL);		// ADPCM CHANNEL A
   AddZ80AWriteByte(0xF810, 0xF811, YM2203AWriteZ80,		NULL);		// YM2203 A
   AddZ80AWriteByte(0xF820, 0xF821, YM2203BWriteZ80,		NULL);		// YM2203 B
   AddZ80AWriteByte(0x0000, 0xFFFF, NULL,			Z80ROM+0x0000);	// <test>
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();
}

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG1;
static UINT8 *GFX_FG0;
static UINT8 *GFX_SPR;

static UINT8 *GFX_BG0_SOLID;
static UINT8 *GFX_BG1_SOLID;
static UINT8 *GFX_FG0_SOLID;
static UINT8 *GFX_SPR_SOLID;

static void load_actual() {
  GFX_FG0 = NULL;

   RAMSize=0x24000+0x10000;
   if(!(RAM=AllocateMem(RAMSize))) return;

   memset(RAM+0x00000,0x00,0x24000);
   memset(RAM+0x1A000,0xFF,0x01000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,get_region_size(REGION_ROM1));

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x060000, 0x07FFFF, NULL, RAM+0x000000);			// *ALL* RAM
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x060000, 0x07FFFF, NULL, RAM+0x000000);			// *ALL* RAM
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x060000, 0x079FFF, NULL, RAM+0x000000);		// *ALL* RAM
   AddWriteByte(0x07A000, 0x07FFFF, CtrlWriteB, NULL);			// *ALL* RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000,  NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x060000, 0x07FFFF, NULL, RAM+0x000000);		// *ALL* RAM
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   InitPaletteMap(RAM+0x18000, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);
}

static void load_gaiden(void)
{
  load_actual();

   /*-------[SOUND SYSTEM INIT]-------*/

   AddTecmoSound(0x00BD, 0x00BD);

   /*---------------------------------*/

   // 68000 Speed hack
   // ----------------

   WriteWord(&ROM[0x1338],0x4EF9);		// jmp $000300
   WriteWord(&ROM[0x133A],0x0000);
   WriteWord(&ROM[0x133c],0x0300);

   WriteWord(&ROM[0x300],0x41F9);		// lea #$001344,a0
   WriteWord(&ROM[0x302],0x0000);
   WriteWord(&ROM[0x304],0x1344);
   WriteWord(&ROM[0x306],0x4EB9);		// jsr $0011D8
   WriteWord(&ROM[0x308],0x0000);
   WriteWord(&ROM[0x30a],0x11D8);
   WriteWord(&ROM[0x30C],0x13FC);	// move.w #$0000,$AA0000
   WriteWord(&ROM[0x30e],0x0000);
   WriteWord(&ROM[0x310],0x00AA);	//
   WriteWord(&ROM[0x312],0x0000);	//
   WriteWord(&ROM[0x314],0x60EA);		// bra <loop>

   // Fix 68000 Checksum
   // ------------------

   ROM[0x54b]=0x60;
   ROM[0x553]=0x60;
}

static void load_wildfang(void)
{
  load_actual();

   /*-------[SOUND SYSTEM INIT]-------*/

   AddTecmoSound(0x00D2, 0x00D2);

   /*---------------------------------*/

   // Protected JSR's hack
   // --------------------

   WriteWord(&ROM[0x1AA76],0x0240);	// andi.w #$001F,d0
   WriteWord(&ROM[0x1AA78],0x001F);	//
   WriteWord(&ROM[0x1AA7A],0xE348);		// lsl.w #1,d0
   WriteWord(&ROM[0x1AA7C],0x4BF8);	// lea $24d2.w,a5
   WriteWord(&ROM[0x1AA7e],0x24D2);	//
   WriteWord(&ROM[0x1AA80],0x3035);	// move.w 0(a5,d0.w),d0
   WriteWord(&ROM[0x1AA82],0x0000);	//
   WriteWord(&ROM[0x1AA84],0x4E75);		// rts

   // 68000 Speed hack
   // ----------------

   WriteWord(&ROM[0x0AAE],0x13FC);	// move.w #$0000,$AA0000
   WriteWord(&ROM[0x0Ab0],0x0000);	//
   WriteWord(&ROM[0x0AB2],0x00AA);	//
   WriteWord(&ROM[0x0AB4],0x0000);	//
}

static void load_shadoww() {
  load_actual();
  AddTecmoSound(0, 0);
}

static void execute_gaiden(void)
{
   RAM[0x1A005] = get_dsw(1);
   RAM[0x1A004] = get_dsw(0);

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(10,60));	// M68000 10MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);

   execute_z80_audio_frame();
}

int have_gfx_bg1[20][18];

static void draw_tecmo_object(int pri)
{
   static int spr_off[4 * 4 * 2] =
   {
      0,  0, 16,  0,  0, 16, 16, 16,
     32,  0, 48,  0, 32, 16, 48, 16,
      0, 32, 16, 32,  0, 48, 16, 48,
     32, 32, 48, 32, 32, 48, 48, 48,
   };

   int x, y, ta, zz, dx, dy, i, x1,y1;
   UINT8 *MAP;

   for(zz=0x16000;zz<0x16800;zz+=16){			// SPRITES (HIGH PRIORITY)
   if (RAM[zz]&0x04){						// sprite enable

   y=(ReadWord(&RAM[zz+6])+48)&0x1FF;
   x=(ReadWord(&RAM[zz+8])+64)&0x1FF;
   x1 = x/16; y1 = y/16;

   if((x>0)&&(y>0)&&(x<256+64)&&(y<224+64)){

   if( ((pri)&&((RAM[zz]&0x80)&&(have_gfx_bg1[x1][y1]))) ||
      ((!pri)&&(!((RAM[zz]&0x80)&&(have_gfx_bg1[x1][y1])))) ){

      ta=ReadWord(&RAM[zz+2]);

      MAP_PALETTE_MAPPED_NEW(
         RAM[zz+4]>>4,
         16,
         MAP
      );

      switch(RAM[zz]&3)
      {
         case 0:
            switch(RAM[zz+4]&0x03){
            case 0:			// 8x8
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[ta<<6],x,y,MAP);
            break;
            case 1:			// 16x16
               ta &= 0xFFFC;
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+0)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+1)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+2)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+3)<<6],x+8,y+8,MAP);
            break;
            case 2:			// 32x32
               dx = x;
               dy = y;
               ta &= 0xFFF0;
               for(i = 0; i < 4; i ++){
               x = dx + spr_off[(i<<1) + 0];
               y = dy + spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+0)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+1)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+2)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+3)<<6],x+8,y+8,MAP);
               ta+=4;
               }
            break;
            case 3:			// 64x64
               dx = x;
               dy = y;
               ta &= 0xFFC0;
               for(i = 0; i < 16; i ++){
               x = dx + spr_off[(i<<1) + 0];
               y = dy + spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+0)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+1)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+2)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_Rot(&GFX_SPR[(ta+3)<<6],x+8,y+8,MAP);
               ta+=4;
               }
            break;
            }
         break;
         case 1:
            switch(RAM[zz+4]&0x03){
            case 0:			// 8x8
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<6],x,y,MAP);
            break;
            case 1:			// 16x16
               ta &= 0xFFFC;
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+0)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+1)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+2)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+3)<<6],x+0,y+8,MAP);
            break;
            case 2:			// 32x32
               dx = x + 16;
               dy = y;
               ta &= 0xFFF0;
               for(i = 0; i < 4; i ++){
               x = dx - spr_off[(i<<1) + 0];
               y = dy + spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+0)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+1)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+2)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+3)<<6],x+0,y+8,MAP);
               ta+=4;
               }
            break;
            case 3:			// 64x64
               dx = x + 48;
               dy = y;
               ta &= 0xFFC0;
               for(i = 0; i < 16; i ++){
               x = dx - spr_off[(i<<1) + 0];
               y = dy + spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+0)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+1)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+2)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta+3)<<6],x+0,y+8,MAP);
               ta+=4;
               }
            break;
            }
         break;
         case 2:
            switch(RAM[zz+4]&0x03){
            case 0:			// 8x8
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<6],x,y,MAP);
            break;
            case 1:			// 16x16
               ta &= 0xFFFC;
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+0)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+1)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+2)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+3)<<6],x+8,y+0,MAP);
            break;
            case 2:			// 32x32
               dx = x;
               dy = y + 16;
               ta &= 0xFFF0;
               for(i = 0; i < 4; i ++){
               x = dx + spr_off[(i<<1) + 0];
               y = dy - spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+0)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+1)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+2)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+3)<<6],x+8,y+0,MAP);
               ta+=4;
               }
            break;
            case 3:			// 64x64
               dx = x;
               dy = y + 48;
               ta &= 0xFFC0;
               for(i = 0; i < 16; i ++){
               x = dx + spr_off[(i<<1) + 0];
               y = - spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+0)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+1)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+2)<<6],x+0,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta+3)<<6],x+8,y+0,MAP);
               ta+=4;
               }
            break;
            }
         break;
         case 3:
            switch(RAM[zz+4]&0x03){
            case 0:			// 8x8
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<6],x,y,MAP);
            break;
            case 1:			// 16x16
               ta &= 0xFFFC;
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+0)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+1)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+2)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+3)<<6],x+0,y+0,MAP);
            break;
            case 2:			// 32x32
               dx = x + 16;
               dy = y + 16;
               ta &= 0xFFF0;
               for(i = 0; i < 4; i ++){
               x = dx - spr_off[(i<<1) + 0];
               y = dy - spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+0)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+1)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+2)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+3)<<6],x+0,y+0,MAP);
               ta+=4;
               }
            break;
            case 3:			// 64x64
               dx = x + 48;
               dy = y + 48;
               ta &= 0xFFC0;
               for(i = 0; i < 16; i ++){
               x = dx - spr_off[(i<<1) + 0];
               y = dy - spr_off[(i<<1) + 1];
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+0)<<6],x+8,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+1)<<6],x+0,y+8,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+2)<<6],x+8,y+0,MAP);
               Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta+3)<<6],x+0,y+0,MAP);
               ta+=4;
               }
            break;
            }
         break;
      }

   }

   }

   }
   }
}

static void TestNearest(int x, int y)
{
  if ((x>0)&&(y>0))			// top
    have_gfx_bg1[x-1][y-1]=1;
  if (y>0)
    have_gfx_bg1[x][y-1]=1;
  if ((x<19)&&(y>0))
    have_gfx_bg1[x+1][y-1]=1;
  if (x>0)
    have_gfx_bg1[x-1][y]=1;
  have_gfx_bg1[x][y]=1;			// current position
  if (x<19)
    have_gfx_bg1[x+1][y]=1;
  if ((x>0)&&(y<17))			// bottom
    have_gfx_bg1[x-1][y+1]=1;
  if (y<17)
    have_gfx_bg1[x][y+1]=1;
  if ((x<19)&&(y<17))
    have_gfx_bg1[x+1][y+1]=1;

  if ((x>1)&&(y<17))			// for security
    have_gfx_bg1[x-2][y+1]=1;
  if (x>1)
    have_gfx_bg1[x-2][y]=1;
  if ((x>1)&&(y>0))
    have_gfx_bg1[x-2][y-1]=1;
  if ((x>1)&&(y>1))
    have_gfx_bg1[x-2][y-2]=1;
  if ((x>0)&&(y>1))
    have_gfx_bg1[x-1][y-2]=1;
  if (y>1)
    have_gfx_bg1[x][y-2]=1;
  if ((x<19)&&(y>1))
    have_gfx_bg1[x+1][y-2]=1;
}

static void DrawTecmoSys(void)
{
   int x,y,ta,zz,zzz,zzzz,x16,y16, x1,y1;
   UINT8 *MAP,bcol;
   if (!GFX_FG0) {
     GFX_FG0=gfx[0];
     GFX_BG0=gfx[1];
     GFX_BG1=gfx[2];
     GFX_SPR=gfx[3];

     GFX_BG0_SOLID = gfx_solid[1];
     GFX_BG1_SOLID = gfx_solid[2];
     GFX_FG0_SOLID = gfx_solid[0];
     GFX_SPR_SOLID = gfx_solid[3];
   }

   ClearPaletteMap();

      MAP_PALETTE_MAPPED_NEW(
         0x20,
         16,
         MAP
      );

   bcol=MAP[0];

   /*

   BG0

   */

   MAKE_SCROLL_1024x512_2_16(
      ReadWord(&RAM[0x1A30C]),
      ReadWord(&RAM[0x1A304])+16
   );

   START_SCROLL_1024x512_2_16(64,64,256,224);

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x14000+zz]>>4)|0x30,
         16,
         MAP
      );

      MAP[0]=bcol;

      Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord(&RAM[0x15000+zz])&0xFFF)<<8],x,y,MAP);

   END_SCROLL_1024x512_2_16();

   /*

   OBJECT LOW

   */

   draw_tecmo_object(0x80);

   /*

   BG1

   */

   MAKE_SCROLL_1024x512_2_16(
      ReadWord(&RAM[0x1A20C]),
      ReadWord(&RAM[0x1A204])+16
   );

   START_SCROLL_1024x512_2_16(64,64,256,224);

      ta=ReadWord(&RAM[0x13000+zz])&0xFFF;
      x1 = x/16; y1 = y/16;

      if(GFX_BG1_SOLID[ta]){				// No pixels; skip

	   TestNearest(x1,y1);

         MAP_PALETTE_MAPPED_NEW(
            (RAM[0x12000+zz]>>4)|0x20,
            16,
            MAP
         );

         if(GFX_BG1_SOLID[ta]==1)			// Some pixels; trans
            Draw16x16_Trans_Mapped_Rot(&GFX_BG1[ta<<8],x,y,MAP);
         else						// all pixels; solid
            Draw16x16_Mapped_Rot(&GFX_BG1[ta<<8],x,y,MAP);

      }
	else have_gfx_bg1[x1][y1]=0;

   END_SCROLL_1024x512_2_16();

   /*

   OBJECT HIGH

   */

   draw_tecmo_object(0x00);

   /*

   FG0

   */

   MAKE_SCROLL_256x256_2_8(
      ReadWord(&RAM[0x1A10C]),
      ReadWord(&RAM[0x1A104])+16
   );

   START_SCROLL_256x256_2_8(64,64,256,224);

      ta=ReadWord(&RAM[0x10800+zz])&0x7FF;
      if(GFX_FG0_SOLID[ta]){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM[0x10000+zz]>>4)|0x10,
            16,
            MAP
         );

         if(GFX_FG0_SOLID[ta]==1)			// Some pixels; trans
            Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,MAP);
         else						// all pixels; solid
            Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6],x,y,MAP);
      }

   END_SCROLL_256x256_2_8();

}






/* Wild fang is not working because the protection hack for Tknight needs to be adapted.
   It should be easy to do, but I am not in mood. */

/*

TECMO 68000 SYSTEM (C)1988-89 TECMO
===================================

Information compiled by [J3d!]

Main CPU......68000
Sound CPUs....Z80, YM2203, YM2203
Screen........256x224

68000 MEMORY MAP
================

-------+--------+--------------------------
Start  | End    | Description
-------+--------+--------------------------
000000 | 03FFFF | 68000 ROM
060000 | 063FFF | 68000 RAM
070000 | 0707FF | FG0 RAM A
070800 | 070FFF | FG0 RAM B
072000 | 072FFF | BG1 RAM A
073000 | 073FFF | BG1 RAM B
074000 | 074FFF | BG0 RAM A
075000 | 075FFF | BG0 RAM B
076000 | 0767FF | SPRITE RAM
078000 | 0787FF | COLOUR RAM
-------+--------+--------------------------

COLOR RAM
=========

- 64 banks of 16 colours
- Format is 12-bit bgr
- 1024 colours onscreen from palette of 4096

------+------------------------------------
Banks | Description
------+------------------------------------
00-0F | Sprites
10-1F | FG0 Plans
20-2F | BG1 Plane
30-3F | BG0 Plane
------+------------------------------------

SPRITE RAM
==========

- 16 bytes/sprite entry
- 128 entries
- Sprites are infact 8x8, but chained to form
  8x8, 16x16, 32x32 and 64x64. 32x32 is most
  common, followed by 16x16, others are rarely
  needed, but sometimes used...

-----+--------+----------------------------
Byte | Bit(s) | Description
-----+76543210+----------------------------
  0  |........| <Garbage?>
  1  |.......x| Flip Y-Axis
  1  |......x.| Flip X-Axis
  1  |.....x..| Sprite Enabled
  1  |.x......| Sprite:BG0 Priority?
  1  |x.......| Sprite:BG1 Priority (0=Sprites Infront)
  2  |xxxxxxxx| Sprite Number (high)
  3  |xxxxxxxx| Sprite Number (low)
  4  |........| <Garbage?>
  5  |......xx| Sprite Size (0=8x8; 1=16x16; 2=32x32; 3=64x64)
  5  |xxxx....| Palette Bank
  6  |xxxxxxxx| Y Pos (high)
  7  |xxxxxxxx| Y Pos (low)
  8  |xxxxxxxx| X Pos (high)
  9  |xxxxxxxx| X Pos (low)
10-15|........| <Unused>
-----+--------+----------------------------

*/
static struct VIDEO_INFO video_gaiden =
{
   DrawTecmoSys,
   256,
   224,
   64,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   gfxdecodeinfo
};
GMEI( shadoww, "Shadow Warriors (World set 1)", TECMO, 1988, GAME_BEAT,
	.input = input_shadoww,
	.dsw = dsw_shadoww,
);
CLNEI(gaiden,shadoww, "Ninja Gaiden", TECMO, 1988, GAME_BEAT,
	.load_game = load_gaiden,
	.long_name_jpn = "者龍剣伝",
);
CLNEI(ryukendn, shadoww, "Ninja Ryukenden", TECMO, 1989, GAME_BEAT);
CLNEI(shadowwa, shadoww, "Shadow Warriors (World set 2)", TECMO, 1988, GAME_BEAT);
GMEI( wildfang, "Wild Fang (Tecmo Knight)", TECMO, 1989, GAME_BEAT | GAME_NOT_WORKING,
	.long_name_jpn = "ワイルドファング",
);
CLNEI(tknight, wildfang, "Tecmo Knight", TECMO, 1989, GAME_BEAT,
	.long_name_jpn = "ワイルドファング",
);

