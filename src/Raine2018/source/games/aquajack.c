#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************
 *                                                                            *
 *                    AQUA JACK (C) 1989 TAITO CORPORATION                    *
 *                                                                            *
 ******************************************************************************

	Aqua Jack Alt set removed.  Only difference was the "Taito Region"
	byte which is used to determine the game version: Japan, US or World

*/


#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc150rod.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "zoom/16x8.h"		// 16x8 zoomed sprite routines
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines


static struct ROM_INFO rom_aquajckj[] =
{
   {   "b77-01.rom", 0x00080000, 0xcdab000d, 0, 0, 0, },
   {   "b77-02.rom", 0x00080000, 0xdaea0d2e, 0, 0, 0, },
   {   "b77-03.rom", 0x00080000, 0x9a3030a7, 0, 0, 0, },
   {   "b77-04.rom", 0x00080000, 0xbed0be6c, 0, 0, 0, },
   {   "b77-05.rom", 0x00080000, 0x7238f0ff, 0, 0, 0, },
   {   "b77-06.rom", 0x00080000, 0xce2aed00, 0, 0, 0, },
   {   "b77-07.rom", 0x00080000, 0x7db1fc5e, 0, 0, 0, },
   {   "b77-08.rom", 0x00080000, 0x119b9485, 0, 0, 0, },
   {   "b77-09.rom", 0x00080000, 0x948e5ad9, 0, 0, 0, },
   {   "b77-20.rom", 0x00010000, 0x84ba54b7, 0, 0, 0, },
   {   "b77-21.rom", 0x00020000, 0x23436845, 0, 0, 0, },
   {   "b77-22.rom", 0x00020000, 0x67400dde, 0, 0, 0, },
   {   "b77-23.rom", 0x00020000, 0x395a7d1c, 0, 0, 0, },
   {   "b77-24.rom", 0x00020000, 0x95e643ed, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_aquajckj[] =
{
   INP0( COIN1, 0x01F104, 0x04 ),
   INP0( COIN2, 0x01F104, 0x08 ),
   INP0( TILT, 0x01F104, 0x20 ),
   INP0( SERVICE, 0x01F104, 0x10 ),

   INP0( P1_UP, 0x01F106, 0x08 ),
   INP0( P1_DOWN, 0x01F106, 0x01 ),
   INP0( P1_LEFT, 0x01F106, 0x02 ),
   INP0( P1_RIGHT, 0x01F106, 0x04 ),
   { KB_DEF_P1_B1,        "Missile",               0x01F106, 0x10, BIT_ACTIVE_0 },
   { KB_DEF_P1_B2,        "Jump",                  0x01F106, 0x20, BIT_ACTIVE_0 },
   { KB_DEF_P1_B3,        "Vulcan",                0x01F106, 0x40, BIT_ACTIVE_0 },
   { KB_DEF_P1_B4,        "Accelerate?",           0x01F10E, 0xFF, BIT_ACTIVE_0 },

   END_INPUT
};

static struct DSW_DATA dsw_data_aqua_jack_0[] =
{
   { _("Cabinet Moves"),         0x01, 0x02 },
   { MSG_YES,                   0x01},
   { MSG_NO,                    0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_1PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_3COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_aqua_jack_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Bonus Life"),            0x0C, 0x04 },
   { _("50k"),                   0x0C},
   { _("80k"),                   0x08},
   { _("100k"),                  0x04},
   { _("30k"),                   0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "1",                     0x10},
   { "5",                     0x00}, // Bits 7 & 8 are unused according to manual
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_aquajckj[] =
{
   { 0x01F100, 0xFF, dsw_data_aqua_jack_0 },
   { 0x01F102, 0xFF, dsw_data_aqua_jack_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_aqua_jack_0[] =
{
   { "Taito Japan (notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan (World)",   0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_aquajckj[] =
{
   { 0x03FFFF, 0x01, romsw_data_aqua_jack_0 },
   { 0,        0,    NULL },
};




#define OBJ_A_COUNT	(0x7FBF)

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

static void load_aquajckj(void)
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
   if(!load_rom_index(1, TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
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
   if(!load_rom_index(2, TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
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

   RAMSize=0x44000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom_index(11, RAM, 0x20000)) return;		// 68000 MAIN
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(10, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom_index(13, RAM, 0x20000)) return;		// 68000 SUB
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom_index(12, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x44000;
   if(!load_rom_index(9, Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   Z80ROM[0x00DC] = 0xC3;
   Z80ROM[0x00DD] = 0x20;
   Z80ROM[0x00DE] = 0x00;

   Z80ROM[0x0020] = 0x3E;
   Z80ROM[0x0021] = 0x07;

   Z80ROM[0x0022] = 0x32;
   Z80ROM[0x0023] = 0x2C;
   Z80ROM[0x0024] = 0xCF;

   Z80ROM[0x0025] = 0xC3;
   Z80ROM[0x0026] = 0xDF;
   Z80ROM[0x0027] = 0x00;

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom_index(8,PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom_index(7,PCMROM+0x80000,0x80000)) return;	// ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x023A, 0x01BA, 0x10000);

   /*-----------------------*/

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1F000;
   GFX_FG0    = RAM+0x40000;
   RAM_INPUT  = RAM+0x1F100;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x4000);

   memset(RAM+0x00000,0x00,0x40000);

   // Main 68000 Speed Hack
   // ---------------------

   WriteLong68k(&ROM[0x0C88C],0x4EF800C0);	//	jmp	$C0.w
   WriteLong68k(&ROM[0x000C0],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x000C4],0x00AA0000);	//
   WriteWord68k(&ROM[0x000C8],0x6100-10);	//	bra.s	<loop>

   // Main 68000 Speed Hack (test mode)
   // ---------------------------------

   WriteLong68k(&ROM[0x0C8CC],0x4EB800D0);	//	jsr	$C0.w
   WriteLong68k(&ROM[0x000D0],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x000D4],0x00AA0000);	//
   WriteWord68k(&ROM[0x000D8],0x4E75);		//	rts

   // Sub 68000 Speed Hack
   // --------------------

   WriteLong68k(&ROM[0x41062],0x4EF80300);	//	jmp	$300.w
   WriteLong68k(&ROM[0x40300],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x40304],0x00AA0000);	//
   WriteWord68k(&ROM[0x40308],0x3B6D);		//	move	16384(a5),16386(a5)
   WriteLong68k(&ROM[0x4030A],0x40004002);	//
   //WriteLong68k(&ROM[0x4030E],0x13FC0000);	//	move.b	#$00,$AA0000
   //WriteLong68k(&ROM[0x40312],0x00AA0000);	//
   WriteLong68k(&ROM[0x4030E],0x4A6D4002);	//	tst	16386(a5)
   WriteWord68k(&ROM[0x40312],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x40314],0x4E75);		//	rts
   WriteLong68k(&ROM[0x40316],0x4EF81070);	//	jmp	$1070.w

   // Fix 68000 Communication (bitch!)
   // --------------------------------
/*
   WriteWord68k(&ROM[0x00100],0x0C6D);		//	cmpi.w	#$0000,16386(a5)
   WriteLong68k(&ROM[0x00102],0x00004002);	//
   WriteWord68k(&ROM[0x00106],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x00108],0x4E75);		//	rts
   WriteLong68k(&ROM[0x0010A],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0010E],0x00AA0000);	//
   WriteWord68k(&ROM[0x00112],0x6100-20);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x00120],0x0C6D);		//	cmpi.w	#$0001,16386(a5)
   WriteLong68k(&ROM[0x00122],0x00014002);	//
   WriteWord68k(&ROM[0x00126],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x00128],0x4E75);		//	rts
   WriteLong68k(&ROM[0x0012A],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0012E],0x00AA0000);	//
   WriteWord68k(&ROM[0x00132],0x6100-20);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x00140],0x0C6D);		//	cmpi.w	#$0002,16386(a5)
   WriteLong68k(&ROM[0x00142],0x00024002);	//
   WriteWord68k(&ROM[0x00146],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x00148],0x4E75);		//	rts
   WriteLong68k(&ROM[0x0014A],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0014E],0x00AA0000);	//
   WriteWord68k(&ROM[0x00152],0x6100-20);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x00160],0x0C6D);		//	cmpi.w	#$0003,16386(a5)
   WriteLong68k(&ROM[0x00162],0x00034002);	//
   WriteWord68k(&ROM[0x00166],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x00168],0x4E75);		//	rts
   WriteLong68k(&ROM[0x0016A],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0016E],0x00AA0000);	//
   WriteWord68k(&ROM[0x00172],0x6100-20);	//	bra.s	<loop>

   WriteLong68k(&ROM[0xC79E],0x4EB80120);	//	[cmpi	#$0001,16386(a5)]
   WriteLong68k(&ROM[0xC7A2],0x4E714E71);	//

   WriteLong68k(&ROM[0xC7A6],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0xC7AA],0x4E71);		//

   WriteLong68k(&ROM[0xC7B2],0x4EB80140);	//	[cmpi	#$0002,16386(a5)]
   WriteLong68k(&ROM[0xC7B6],0x4E714E71);	//

   WriteLong68k(&ROM[0xC7BA],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0xC7BE],0x4E71);		//

   WriteLong68k(&ROM[0x1F194],0x4EB80100);	//	[tst	16386(a5)] ****
   WriteWord68k(&ROM[0x1F198],0x4E71);		//

   WriteLong68k(&ROM[0x1F1B8],0x4EB80140);	//	[cmpi	#$0002,16386(a5)]
   WriteLong68k(&ROM[0x1F1BC],0x4E714E71);	//

   WriteLong68k(&ROM[0x1F1C4],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x1F1C8],0x4E71);		//

   WriteLong68k(&ROM[0x1F28E],0x4EB80160);	//	[cmpi	#$0003,16386(a5)]
   WriteLong68k(&ROM[0x1F292],0x4E714E71);	//

   WriteLong68k(&ROM[0x1F296],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x1F29A],0x4E71);		//

   WriteLong68k(&ROM[0x23D40],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x23D44],0x4E71);		//

   WriteLong68k(&ROM[0x23D58],0x4EB80120);	//	[cmpi	#$0001,16386(a5)]
   WriteLong68k(&ROM[0x23D5C],0x4E714E71);	//

   WriteLong68k(&ROM[0x23D64],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x23D68],0x4E71);		//

   WriteLong68k(&ROM[0x23D70],0x4EB80140);	//	[cmpi	#$0002,16386(a5)]
   WriteLong68k(&ROM[0x23D74],0x4E714E71);	//

   WriteLong68k(&ROM[0x23D7C],0x4EB80100);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x23D80],0x4E71);		//

   WriteWord68k(&ROM[0x00180],0x0C6D);		//	cmpi.w	#$0000,16386(a5)
   WriteLong68k(&ROM[0x00182],0x00006002);	//
   WriteWord68k(&ROM[0x00186],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x00188],0x4E75);		//	rts
   WriteLong68k(&ROM[0x0018A],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0018E],0x00AA0000);	//
   WriteWord68k(&ROM[0x00192],0x6100-20);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x001A0],0x0C6D);		//	cmpi.w	#$0001,16386(a5)
   WriteLong68k(&ROM[0x001A2],0x00016002);	//
   WriteWord68k(&ROM[0x001A6],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x001A8],0x4E75);		//	rts
   WriteLong68k(&ROM[0x001AA],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x001AE],0x00AA0000);	//
   WriteWord68k(&ROM[0x001B2],0x6100-20);	//	bra.s	<loop>

   WriteWord68k(&ROM[0x001C0],0x0C6D);		//	cmpi.w	#$0002,16386(a5)
   WriteLong68k(&ROM[0x001C2],0x00026002);	//
   WriteWord68k(&ROM[0x001C6],0x6602);		//	bne.s	+2
   WriteWord68k(&ROM[0x001C8],0x4E75);		//	rts
   WriteLong68k(&ROM[0x001CA],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x001CE],0x00AA0000);	//
   WriteWord68k(&ROM[0x001D2],0x6100-20);	//	bra.s	<loop>

   WriteLong68k(&ROM[0x1FDC0],0x4EB801A0);	//	[cmpi	#$0001,24578(a5)]
   WriteLong68k(&ROM[0x1FDC4],0x4E714E71);	//

   WriteLong68k(&ROM[0x1FDC8],0x4EB80180);	//	[tst	24578(a5)]
   WriteWord68k(&ROM[0x1FDCC],0x4E71);		//

   WriteLong68k(&ROM[0x1FDFA],0x4EB801C0);	//	[cmpi	#$0002,24578(a5)]
   WriteLong68k(&ROM[0x1FDFE],0x4E714E71);	//

   WriteLong68k(&ROM[0x1FE02],0x4EB80180);	//	[tst	24578(a5)]
   WriteWord68k(&ROM[0x1FE06],0x4E71);		//
*/
   WriteLong68k(&ROM[0x00200],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x00204],0x00AA0000);	//
   WriteWord68k(&ROM[0x00208],0x4E75);		//	rts

   WriteLong68k(&ROM[0x8882],0x4EB80200);	//	[cmpi	#$0004,18688(a5)]
   WriteLong68k(&ROM[0x8886],0x4E714E71);	//

   WriteLong68k(&ROM[0xC79E],0x4EB80200);	//	[cmpi	#$0001,16386(a5)]
   WriteLong68k(&ROM[0xC7A2],0x4E714E71);	//

   WriteLong68k(&ROM[0xC7A6],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0xC7AA],0x4E71);		//

   WriteLong68k(&ROM[0xC7B2],0x4EB80200);	//	[cmpi	#$0002,16386(a5)]
   WriteLong68k(&ROM[0xC7B6],0x4E714E71);	//

   WriteLong68k(&ROM[0xC7BA],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0xC7BE],0x4E71);		//

   WriteLong68k(&ROM[0x1F194],0x4E714E71);	//	[tst	16386(a5)] ****
   WriteWord68k(&ROM[0x1F198],0x4E71);		//

   WriteLong68k(&ROM[0x1F1B8],0x4EB80200);	//	[cmpi	#$0002,16386(a5)]
   WriteLong68k(&ROM[0x1F1BC],0x4E714E71);	//

   WriteLong68k(&ROM[0x1F1C4],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x1F1C8],0x4E71);		//

   WriteLong68k(&ROM[0x1F28E],0x4EB80200);	//	[cmpi	#$0003,16386(a5)]
   WriteLong68k(&ROM[0x1F292],0x4E714E71);	//

   WriteLong68k(&ROM[0x1F296],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x1F29A],0x4E71);		//

   WriteLong68k(&ROM[0x23D40],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x23D44],0x4E71);		//

   WriteLong68k(&ROM[0x23D58],0x4EB80200);	//	[cmpi	#$0001,16386(a5)]
   WriteLong68k(&ROM[0x23D5C],0x4E714E71);	//

   WriteLong68k(&ROM[0x23D64],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x23D68],0x4E71);		//

   WriteLong68k(&ROM[0x23D70],0x4EB80200);	//	[cmpi	#$0002,16386(a5)]
   WriteLong68k(&ROM[0x23D74],0x4E714E71);	//

   WriteLong68k(&ROM[0x23D7C],0x4E714E71);	//	[tst	16386(a5)]
   WriteWord68k(&ROM[0x23D80],0x4E71);		//

   WriteLong68k(&ROM[0x1FDC0],0x4EB80200);	//	[cmpi	#$0001,24578(a5)]
   WriteLong68k(&ROM[0x1FDC4],0x4E714E71);	//

   WriteLong68k(&ROM[0x1FDC8],0x4E714E71);	//	[tst	24578(a5)]
   WriteWord68k(&ROM[0x1FDCC],0x4E71);		//

   WriteLong68k(&ROM[0x1FDFA],0x4EB80200);	//	[cmpi	#$0002,24578(a5)]
   WriteLong68k(&ROM[0x1FDFE],0x4E714E71);	//

   WriteLong68k(&ROM[0x1FE02],0x4E714E71);	//	[tst	24578(a5)]
   WriteWord68k(&ROM[0x1FE06],0x4E71);		//

   WriteLong68k(&ROM[0x20112],0x4EB80200);	//
   WriteLong68k(&ROM[0x20116],0x4E714E71);	//
   WriteLong68k(&ROM[0x2011A],0x4E714E71);	//

   tc0110pcr_init_typeb(RAM+0x1C000, 1, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x1C000, 0x100, 0x10, 0x8000);


   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0150rod emulation
   // ------------------------

   tc0150rod.RAM  	= RAM + 0x20000;
   tc0150rod.GFX  	= GFX_LINES;
   tc0150rod.PAL  	= NULL;
   // tc0150rod.mapper	= &Map_15bit_xBGR;
   tc0150rod.bmp_x	= 32;
   tc0150rod.bmp_y	= 32;
   tc0150rod.bmp_w	= 320;
   tc0150rod.bmp_h	= 224;
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
   tc0100scn[0].layer[0].bmp_h	=224;
   // tc0100scn[0].layer[0].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=16;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   // tc0100scn[0].layer[1].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=16;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=1;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   // tc0100scn[0].layer[2].mapper	=&Map_15bit_xBGR;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=16;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);
   tc0100scn_0_copy_gfx_fg0(ROM+0x2016C, 0x1000);

   init_16x8_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1zz();
   zoom8_ofs  = make_16x8_zoom_ofs_type1zz();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x107FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x107FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x800000, 0x801FFF, NULL, RAM+0x020000);			// ROAD RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x107FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x107FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xC40000, 0xC403FF, NULL, RAM+0x01E000);		// OBJECT RAM
   AddWriteWord(0x300000, 0x300007, tc0110pcr_ww, NULL);		// COLOUR RAM
   AddWriteWord(0xA20000, 0xA2000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x800000, 0x801FFF, NULL, RAM+0x020000);		// ROAD RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM+0x040000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x040000);			// 68000 ROM
   AddReadByteMC68000B(0x100000, 0x103FFF, NULL, RAM+0x018000);			// SUB LOCAL RAM
   AddReadByteMC68000B(0x104000, 0x107FFF, NULL, RAM+0x004000);			// COMMON RAM
   AddReadByteMC68000B(0x300000, 0x300003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByteMC68000B(0x200000, 0x20000F, NULL, RAM_INPUT);			// INPUT
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x040000);			// 68000 ROM
   AddReadWordMC68000B(0x100000, 0x103FFF, NULL, RAM+0x018000);			// SUB LOCAL RAM
   AddReadWordMC68000B(0x104000, 0x107FFF, NULL, RAM+0x004000);			// COMMON RAM
   AddReadWordMC68000B(0x300000, 0x300003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadWordMC68000B(0x200000, 0x20000F, NULL, RAM_INPUT);			// INPUT
   AddReadWordMC68000B(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x100000, 0x103FFF, NULL, RAM+0x018000);		// SUB LOCAL RAM
   AddWriteByteMC68000B(0x104000, 0x107FFF, NULL, RAM+0x004000);		// COMMON RAM
   AddWriteByteMC68000B(0x200000, 0x20000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x100000, 0x103FFF, NULL, RAM+0x018000);		// SUB LOCAL RAM
   AddWriteWordMC68000B(0x104000, 0x107FFF, NULL, RAM+0x004000);		// COMMON RAM
   AddWriteWordMC68000B(0x300000, 0x300003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWordMC68000B(0x200000, 0x20000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void execute_aquajckj(void)
{
#if 0
   int ta;

   for(ta=0;ta<16;ta++){
   cpu_execute_cycles(CPU_68K_0, 1800000/16);
   cpu_execute_cycles(CPU_68K_1, 1800000/16);
   }

   cpu_interrupt(CPU_68K_0, 4);

#else
   int ta;

   ta=0;

CPULoop:
   cpu_execute_cycles(CPU_68K_0, 1800000);

   if((s68000context.pc)>=0x100){
   if((s68000context.pc)!=0x208){
      print_debug("PC0-WAIT:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
   }

   cpu_execute_cycles(CPU_68K_1, 1800000);
   ta++;
   if(ta<16){
   goto CPULoop;
   }

   }

   cpu_execute_cycles(CPU_68K_1, 1800000);

      print_debug("PC0:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 4);
#endif

   Taito2610_Frame();				// Z80 and YM2610
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

   for(zz=0x1E3F8;zz>=0x1E000;zz-=8){

      //if((RAM[zz+2]&0x80)==pri){

      zx=(RAM[zz+4]>>0)&0x3F;
      zy=(RAM[zz+1]>>1)&0x3F;
      if((zx!=0)&&(zy!=0)){

         ta = ReadWord(&RAM[zz+6])&0xFFF;
         if(ta!=0){

            x=(32+(ReadWord(&RAM[zz+2])))&0x1FF;

            //y=(32+ReadWord(&RAM[zz+0])+(0x3F-(zy)))&0x1FF;

            y=(32+(ReadWord(&RAM[zz+0])))&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+4])>>8)&0xFF,
               16,
               map
            );

            zoom_dat_x = zoom16_ofs+(zx<<2);
            zoom_dat_y = zoom8_ofs+(zy<<3);

            SPR_MAP = OBJECT_MAP + (ta<<6);

            if((RAM[zz+7]&0x80)==0){
            switch(RAM[zz+3]&0x40){
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
            }

            }
            else{

            switch(RAM[zz+3]&0x40){
            case 0x00:

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
            case 0x40:

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
      }
   //}
   }
}

static void draw_aqua_jack(void)
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

   // OBJECT
   // ------

   render_z_system_sprites(1);

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);
}

/*

Sprite List Format (8 bytes/sprite)
===================================

Byte | Bit(s) | Description
-----+76543210+--------------------
  0  |.xxxxxx.| ZoomY (0-63)
  0  |.......x| Y Position (High)
  1  |xxxxxxxx| Y Position (Low)
  2  |.x......| Flip Y Axis
  2  |x.......| Sprite:BG1 Priority
  2  |.......x| X Position (High)
  3  |xxxxxxxx| X Position (Low)
  4  |xxxxxxxx| Palette Bank
  5  |..xxxxxx| ZoomX (0-63)
  6  |x.......| Flip X Axis?
  6  |.....xxx| Sprite Number (High)
  7  |xxxxxxxx| Sprite Number (Low)

*/
static struct VIDEO_INFO video_aquajckj =
{
   draw_aqua_jack,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_aquajckj[] =
{
   { "aqua_jack", },
   { "aquajack", },
   { "aquajckj", },
   { NULL, },
};
GME( aquajckj, "Aqua Jack", TAITO, 1990, GAME_SHOOT | GAME_PARTIALLY_WORKING,
	.romsw = romsw_aquajckj,
	.board = "B77",
);

