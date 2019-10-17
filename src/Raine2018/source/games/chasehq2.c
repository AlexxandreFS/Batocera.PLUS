#define DRV_DEF_SOUND taito_ym2610b_sound
/******************************************************************************/
/*                                                                            */
/*   CHASE HQ 2: SPECIAL CRIMINAL INVESTIGATION (C) 1989 TAITO CORPORATION    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc150rod.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "zoom/16x8.h"		// 16x8 zoomed sprite routines
#include "zoom/16x16.h"		// 16x8 zoomed sprite routines


static struct ROM_INFO rom_sci[] =
{
   {   "c09-01.rom", 0x00080000, 0x64bfea10, 0, 0, 0, },
   {   "c09-02.rom", 0x00080000, 0xa83a0389, 0, 0, 0, },
   {   "c09-03.rom", 0x00080000, 0xa31d0e80, 0, 0, 0, },
   {   "c09-04.rom", 0x00080000, 0x2cbb3c9b, 0, 0, 0, },
   {   "c09-05.rom", 0x00080000, 0x890b38f0, 0, 0, 0, },
   {   "c09-06.rom", 0x00080000, 0x12df6d7b, 0, 0, 0, },
   {   "c09-07.rom", 0x00080000, 0x963bc82b, 0, 0, 0, },
   {   "c09-12.rom", 0x00080000, 0x56c99fa5, 0, 0, 0, },
   {   "c09-13.rom", 0x00080000, 0xd57c41d3, 0, 0, 0, },
   {   "c09-14.rom", 0x00080000, 0xad78bf46, 0, 0, 0, },
   {   "c09-15.rom", 0x00080000, 0xe63b9095, 0, 0, 0, },
   {   "c09-16.rom", 0x00010000, 0x7245a6f6, 0, 0, 0, },
   {   "c09-32.rom", 0x00010000, 0xa4713719, 0, 0, 0, },
   {   "c09-33.rom", 0x00010000, 0xcf4e6c5b, 0, 0, 0, },
   {   "c09-34.rom", 0x00020000, 0xa21b3151, 0, 0, 0, },
   {   "c09-37.rom", 0x00020000, 0x0fecea17, 0, 0, 0, },
   {   "c09-38.rom", 0x00020000, 0xf4404f87, 0, 0, 0, },
   {   "c09-40.rom", 0x00020000, 0xe46ebd9b, 0, 0, 0, },
   {   "c09-41.rom", 0x00020000, 0xde87bcb9, 0, 0, 0, },
   {   "c09-23.rom", 0x00000100, 0xfbf81f30, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_sci[] =
{
   INP0( COIN1, 0x022804, 0x04 ),
   INP0( COIN2, 0x022804, 0x08 ),
   INP0( TILT, 0x022806, 0x02 ),
   INP0( SERVICE, 0x022804, 0x10 ),

   INP0( P1_START, 0x022806, 0x08 ),
   INP1( P1_LEFT, 0x02281C, 0xFF ),
   INP1( P1_RIGHT, 0x02281D, 0xFF ),
   { KB_DEF_P1_B4,        "Turbo",                 0x022806, 0x01, BIT_ACTIVE_0 },
   { KB_DEF_P1_B3,        "Fire",                  0x022804, 0x02, BIT_ACTIVE_0 },
   { KB_DEF_P1_B2,        "Low Gear",              0x022806, 0x10, BIT_ACTIVE_1 },
   { KB_DEF_P1_B1,        "Accelerate",            0x022806, 0x20, BIT_ACTIVE_0 },
   { KB_DEF_P1_B5,        "Brake",                 0x022804, 0x20, BIT_ACTIVE_0 },
   { KB_DEF_P1_B6,        "Centre",                0x022806, 0x04, BIT_ACTIVE_0 },

   END_INPUT
};


static struct DSW_DATA dsw_data_chase_hq_2_sci_0[] =
{
   { _("Cabinet Type"),          0x01, 0x02 },
   { _("Cockpit"),               0x01},
   { _("Upright"),               0x00},
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_chase_hq_2_sci_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Start Time"),            0x0C, 0x04 },
   { "60",                    0x0C},
   { "70",                    0x08},
   { "65",                    0x04},
   { "55",                    0x00},
   { _("Start Turbos"),          0x10, 0x02 },
   { "3",                     0x10},
   { "5",                     0x00},
   { _("Responds to Controls"),  0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { _("Clear Damage on Cont."), 0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Volume of Siren"),       0x80, 0x02 },
   { MSG_NORMAL,              0x80},
   { _("Low"),                   0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_sci[] =
{
   { 0x022800, 0xFF, dsw_data_chase_hq_2_sci_0 },
   { 0x022802, 0xFF, dsw_data_chase_hq_2_sci_1 },
   { 0,        0,    NULL,      },
};


static struct ROMSW_DATA romsw_data_chase_hq_2_sci_0[] =
{
   { "Taito Japan (Japanese)",0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_sci[] =
{
   { 0x07FFFE, 0x03, romsw_data_chase_hq_2_sci_0 }, // normally, this would be 0x7FFFF
   { 0,        0,    NULL },
};




static struct ROM_INFO rom_sciu[] =
{
   {   "c09-01.rom", 0x00080000, 0x64bfea10, 0, 0, 0, },
   {   "c09-02.rom", 0x00080000, 0xa83a0389, 0, 0, 0, },
   {   "c09-03.rom", 0x00080000, 0xa31d0e80, 0, 0, 0, },
   {   "c09-04.rom", 0x00080000, 0x2cbb3c9b, 0, 0, 0, },
   {   "c09-05.rom", 0x00080000, 0x890b38f0, 0, 0, 0, },
   {   "c09-06.rom", 0x00080000, 0x12df6d7b, 0, 0, 0, },
   {   "c09-07.rom", 0x00080000, 0x963bc82b, 0, 0, 0, },
   {   "c09-12.rom", 0x00080000, 0x56c99fa5, 0, 0, 0, },
   {   "c09-13.rom", 0x00080000, 0xd57c41d3, 0, 0, 0, },
   {   "c09-14.rom", 0x00080000, 0xad78bf46, 0, 0, 0, },
   {   "c09-15.rom", 0x00080000, 0xe63b9095, 0, 0, 0, },
   {   "c09-16.rom", 0x00010000, 0x7245a6f6, 0, 0, 0, },
   {   "c09-32.rom", 0x00010000, 0xa4713719, 0, 0, 0, },
   {   "c09-33.rom", 0x00010000, 0xcf4e6c5b, 0, 0, 0, },
   {   "c09-34.rom", 0x00020000, 0xa21b3151, 0, 0, 0, },
   {    "c09-43.37", 0x00020000, 0x20a9343e, 0, 0, 0, },
   {    "c09-41.38", 0x00020000, 0x83477f11, 0, 0, 0, },
   {    "c09-44.40", 0x00020000, 0x7524338a, 0, 0, 0, },
   {   "c09-41.rom", 0x00020000, 0xde87bcb9, 0, 0, 0, },
   {   "c09-23.rom", 0x00000100, 0xfbf81f30, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROMSW_INFO romsw_sciu[] =
{
   { 0x07FFFE, 0x02, romsw_data_chase_hq_2_sci_0 }, // normally, this would be 0x7FFFF
   { 0,        0,    NULL },
};


#define OBJ_A_COUNT	(0x748F)

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
static UINT8 *GFX_OBJ_A_SOLID;

static UINT8 *zoom16_ofs;
static UINT8 *zoom8_ofs;

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_LINES;

/* road - line - left - right */

static UINT8 PAL_MAP[0x100] =
{
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
   0x1C, 0x1D, 0x1E, 0x1F, 0xC, 0xD, 0xE, 0xF, 0x4, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
};

static void load_sci()
{
   int ta,tb,tc;
   UINT8 *TMP;

   if(!(GFX=AllocateMem(0x100000))) return;

   if(!(GFX_LINES=AllocateMem(0x200000))) return;

   if(!(GFX_OBJ_A=AllocateMem(OBJ_A_COUNT*0x80))) return;

   if(!(OBJECT_MAP=AllocateMem(0x80000))) return;

   if(!(TMP=AllocateMem(0x80000))) return;

   if(!load_rom_index(6, TMP, 0x80000)) return;	// 1024x1 ROAD LINES
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_LINES[tb+0] =((tc&0x8000)>>(14));
      GFX_LINES[tb+1] =((tc&0x4000)>>(13));
      GFX_LINES[tb+2] =((tc&0x2000)>>(12));
      GFX_LINES[tb+3] =((tc&0x1000)>>(11));
      GFX_LINES[tb+4] =((tc&0x0800)>>(10));
      GFX_LINES[tb+5] =((tc&0x0400)>>( 9));
      GFX_LINES[tb+6] =((tc&0x0200)>>( 8));
      GFX_LINES[tb+7] =((tc&0x0100)>>( 7));
      GFX_LINES[tb+0]|=((tc&0x0080)>>( 7));
      GFX_LINES[tb+1]|=((tc&0x0040)>>( 6));
      GFX_LINES[tb+2]|=((tc&0x0020)>>( 5));
      GFX_LINES[tb+3]|=((tc&0x0010)>>( 4));
      GFX_LINES[tb+4]|=((tc&0x0008)>>( 3));
      GFX_LINES[tb+5]|=((tc&0x0004)>>( 2));
      GFX_LINES[tb+6]|=((tc&0x0002)>>( 1));
      GFX_LINES[tb+7]|=((tc&0x0001)>>( 0));
      tb+=8;
   }

   if(!load_rom_index(0, TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_A[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_A[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_A[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_A[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_A[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_A[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_A[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_A[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   if(!load_rom_index(2, TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   if(!load_rom_index(1, TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   if(!load_rom_index(3, TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }

   if(!load_rom_index(5, OBJECT_MAP, 0x80000)) return; // TILE MAPPING

   if(!load_rom_index(4, TMP, 0x80000)) return;	// 8x8 BG0 TILES
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX[tb+0] = ((tc&0xF000)>>12);
      GFX[tb+1] = ((tc&0x0F00)>> 8);
      GFX[tb+2] = ((tc&0x00F0)>> 4);
      GFX[tb+3] = ((tc&0x000F)>> 0);
      tb+=4;
   }

   FreeMem(TMP);

   GFX_OBJ_A_SOLID = make_solid_mask_16x8(GFX_OBJ_A, OBJ_A_COUNT);
   GFX_BG0_SOLID   = make_solid_mask_8x8 (GFX,       0x4000);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0xA0000))) return;

   if(!load_rom_index(15, RAM+0x00000, 0x20000)) return;	// 68000 MAIN ROM
   if(!load_rom_index(16, RAM+0x20000, 0x20000)) return;	// 68000 MAIN ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(17, RAM+0x00000, 0x20000)) return;
   if(!load_rom_index(18, RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom_index(13, RAM, 0x10000)) return;	// 68000 SUB ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom_index(12, RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x50000;
   if(!load_rom_index(14, Z80ROM, 0x20000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x200000))) return;
   if(!load_rom_index(10,PCMROM+0x000000,0x80000)) return;	// Delta-T
   if(!load_rom_index( 9,PCMROM+0x080000,0x80000)) return;	// Main
   if(!load_rom_index( 8,PCMROM+0x100000,0x80000)) return;	// Main
   if(!load_rom_index( 7,PCMROM+0x180000,0x80000)) return;	// Main
   YM2610SetBuffers(PCMROM+0x00000, PCMROM+0x80000, 0x80000, 0x180000);

   AddTaitoYM2610B(0x0234, 0x01B4, 0x20000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x22800,0xFF,0x00800);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x29000;
   RAM_INPUT  = RAM+0x22800;

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x20000, 0x100, 0x10, 0x8000);


   GFX_FG0    = RAM+0x3C000;

   // Motor wait

   WriteWord68k(&ROM[0x009B4],0x4E71);		//	nop

   // Main 68000 Speed Hack

   WriteLong68k(&ROM[0x00FFE],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x01002],0x00AA0000);	//
   WriteWord68k(&ROM[0x01006],0x4E71);		//	nop

   // Sub 68000 Speed Hack

   WriteLong68k(&ROM[0x804D6],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x804DA],0x00AA0000);	//

   // 300 = ? 301 = debug msgs   302 = ? 303 = ?
   // 304 = ? 305 = motor enable 306 = ? 307 = ?
/*
   WriteLong68k(&ROM[0x00300],0x01000101);
   WriteLong68k(&ROM[0x00304],0x00000101);
*/
   //WriteWord68k(&ROM[0x08158],0x6040);

   //WriteLong68k(&ROM[0x0819E],0x13FC0000);
   //WriteLong68k(&ROM[0x081A2],0x00BB0000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0150rod emulation
   // ------------------------

   tc0150rod.RAM  	= RAM + 0x38000;
   tc0150rod.GFX  	= GFX_LINES;
   tc0150rod.PAL  	= PAL_MAP;
   // tc0150rod.mapper	= &Map_15bit_xBGR;
   tc0150rod.bmp_x	= 32;
   tc0150rod.bmp_y	= 32;
   tc0150rod.bmp_w	= 320;
   tc0150rod.bmp_h	= 240;
   tc0150rod.scr_x	= 0;
   tc0150rod.scr_y	= -15;

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   // tc0100scn[0].layer[0].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   // tc0100scn[0].layer[1].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=240;
   // tc0100scn[0].layer[2].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   init_16x8_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1zz();
   zoom8_ofs  = make_16x8_zoom_ofs_type1zz();
/*
   init_16x8_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1z();
   zoom8_ofs  = make_16x8_zoom_ofs_type1z();
*/
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xA0000);
   ByteSwap(RAM,0x50000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x200000, 0x20001F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x420000, 0x420003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xC00000, 0xC01FFF, NULL, RAM+0x040000);			// OBJECT RAM
   AddReadWord(0x800000, 0x801FFF, NULL, RAM+0x020000);			// COLOR RAM
   AddReadWord(0x200000, 0x20001F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xA06000, 0xA06FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x200000, 0x20001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0x420000, 0x420003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xA06000, 0xA06FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xC00000, 0xC01FFF, NULL, RAM+0x040000);		// OBJECT RAM
   AddWriteWord(0xA20000, 0xA2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x800000, 0x801FFF, NULL, RAM+0x020000);		// COLOR RAM
   AddWriteWord(0x200000, 0x20001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x01FFFF, ROM+0x080000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x01FFFF, NULL, ROM+0x080000);		// 68000 ROM
   AddReadByteMC68000B(0x200000, 0x203FFF, NULL, RAM+0x030000);		// MAIN RAM
   AddReadByteMC68000B(0x208000, 0x20BFFF, NULL, RAM+0x008000);		// COMMON RAM
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);	// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x01FFFF, NULL, ROM+0x080000);		// 68000 ROM
   AddReadWordMC68000B(0x200000, 0x203FFF, NULL, RAM+0x030000);		// MAIN RAM
   AddReadWordMC68000B(0x208000, 0x20BFFF, NULL, RAM+0x008000);		// COMMON RAM
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);	// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x200000, 0x203FFF, NULL, RAM+0x030000);	// MAIN RAM
   AddWriteByteMC68000B(0x208000, 0x20BFFF, NULL, RAM+0x008000);	// COMMON RAM
   AddWriteByteMC68000B(0xA00000, 0xA01FFF, NULL, RAM+0x038000);	// ROADSCROLL RAM
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);	// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x200000, 0x203FFF, NULL, RAM+0x030000);	// MAIN RAM
   AddWriteWordMC68000B(0x208000, 0x20BFFF, NULL, RAM+0x008000);	// COMMON RAM
   AddWriteWordMC68000B(0xA00000, 0xA01FFF, NULL, RAM+0x038000);	// ROADSCROLL RAM
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);	// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void execute_sci(void)
{
   static int int6_frame;
   int wheel;

   wheel = 0;

   if(RAM[0x02281C])

      wheel = -128;

   if(RAM[0x02281D])

      wheel = 127;

   RAM[0x022818] = wheel;

   RAM[0x02281A] = wheel>>8;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
      print_debug("PC0:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);

   if(cpu_get_pc(CPU_68K_0) == 0x1006){

      cpu_interrupt(CPU_68K_0, 4);

      int6_frame ^=1;

      if(int6_frame & 1)

      cpu_interrupt(CPU_68K_0, 6);

   }

   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
      print_debug("PC1:%06x SR1:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 4);

   Taito2610_Frame();			// Z80 and YM2610
}

static void render_z_system_sprites(int pri)
{
   int x,y,ta,tb,zz;
   int zx,zy,rx,ry,xx,zzx,zzy;
   UINT8 *map,*SPR_MAP;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;

/*
   if(pri!=0)
      pri=0x00;
   else
      pri=0x80;
*/
   // OBJECT Z-SYSTEM
   // ---------------

   for(zz=0x40000;zz<0x41000;zz+=8){

      //if((RAM[zz+2]&0x80)==pri){

      zx=(RAM[zz+2]>>0)&0x3F;
      zy=(RAM[zz+1]>>1)&0x3F;
      if((zx!=0)&&(zy!=0)){

         ta = ReadWord(&RAM[zz+6])&0xFFF;
         if(ta!=0){

            x=(32+(ReadWord(&RAM[zz+4])))&0x1FF;

            y=( (64+32-10) + ReadWord(&RAM[zz+0]) - (zy) )&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+2])>>7)&0xFF,
               16,
               map
            );

            zoom_dat_x = zoom16_ofs+(zx<<2);
            zoom_dat_y = zoom8_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + (ta<<6);

            switch(RAM[zz+5]&0xC0){
            case 0x00:

            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0x80:

            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipX_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            SPR_MAP+=8;
            x=xx;
            }

            break;
            case 0xC0:

            x+=(zx+1);
            y+=zy;
            xx=x;

            for(ry=0;ry<8;ry++){
            zzy = zoom_dat_y[ry];
            y = (y-zzy)&0x1FF;
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<4;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            SPR_MAP+=8;
            x=xx;
            }

            break;
            }

         }
      }
   //}
   }
}

static void DrawChaseHQ2(void)
{
   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // 3D-ROAD Z-SYSTEM
   // ----------------

   tc0150rod_init_palette();
   tc0150rod_render(0x000,0x800);

   // Z-SYSTEM OBJECT
   // ---------------

   render_z_system_sprites(1);

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);

   tc0150rod_show_palette();
}

/*

Sprite List Format (8 bytes/sprite)
===================================

Byte | Bit(s) | Description
-----+76543210+--------------------
  0  |.xxxxxx.| Zoom (0-63)
  0  |.......x| Y Position (High)
  1  |xxxxxxxx| Y Position (Low)
  2  |.xxxxxxx| Color Bank (High)
  3  |x.......| Color Bank (Low)
  3  |..xxxxxx| Zoom (0-63)
  4  |.x......| Flip Y Axis
  4  |x.......| Flip X Axis
  4  |.......x| X Position (High)
  5  |xxxxxxxx| X Position (Low)
  6  |....xxxx| Sprite Number (High)
  7  |xxxxxxxx| Sprite Number (Low)

*/

static struct VIDEO_INFO video_sci =
{
   DrawChaseHQ2,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_sci[] =
{
   { "chase_hq_2_sci", },
   { "chasehq2", },
   { "chase_hq_2", },
   { "sci", },
   { NULL, },
};
GME( sci, "Special Criminal Investigation", TAITO, 1989, GAME_RACE | GAME_PARTIALLY_WORKING,
	.romsw = romsw_sci,
	.board = "C09",
);
static struct DIR_INFO dir_sciu[] =
{
   { "chase_hq_2_sci_alt", },
   { "chashq2a", },
   { "sciu", },
   { "chasehq2", },
   { "chase_hq_2_alt", },
   { ROMOF("sci"), },
   { CLONEOF("sci"), },
   { NULL, },
};
CLNE( sciu, sci, "Special Criminal Investigation (alternate)", TAITO, 1989, GAME_RACE | GAME_PARTIALLY_WORKING,
	.romsw = romsw_sciu,
	.board = "C09",
);

