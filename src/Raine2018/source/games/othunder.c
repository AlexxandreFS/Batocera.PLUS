#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*              OPERATION THUNDERBOLT (C) 1988 TAITO CORPORATION              */
/*                                                                            */
/******************************************************************************/
/* Todo : convert to any color depth */

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "savegame.h"
#include "gun.h"


static struct ROM_INFO rom_othunder[] =
{
   {       "b67-02", 0x00080000, 0xc20cd2fb, 0, 0, 0, },
   {       "b67-03", 0x00080000, 0xbc9019ed, 0, 0, 0, },
   {       "b67-04", 0x00080000, 0x2af4c8af, 0, 0, 0, },
   {       "b67-05", 0x00080000, 0x9593e42b, 0, 0, 0, },
   {       "b67-06", 0x00080000, 0xb9a38d64, 0, 0, 0, },
   {       "b67-07", 0x00080000, 0x4f834357, 0, 0, 0, },
   {       "b67-08", 0x00080000, 0x458f41fb, 0, 0, 0, },
   {       "b67-01", 0x00080000, 0x81ad9acb, 0, 0, 0, },
   {       "b67-13.40", 0x00010000, 0x2936b4b1, 0, 0, 0, },
   {       "b67-14.61", 0x00020000, 0x7f3dd724, 0, 0, 0, },
   {       "b67-15.62", 0x00020000, 0xe84f62d0, 0, 0, 0, },
   {       "b67-20", 0x00020000, 0x21439ea2, 0, 0, 0, },
   {       "b67-23", 0x00020000, 0x789e9daa, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_othunder[] =
{
   INP0( COIN1, 0x028004, 0x08 ),
   INP0( COIN2, 0x028004, 0x04 ),
   INP0( TILT, 0x028004, 0x20 ),
   INP0( SERVICE, 0x028004, 0x10 ),

   INP0( P1_START, 0x028004, 0x40 ),
   INP1( P1_UP, 0x028010, 0x01 ),
   INP1( P1_DOWN, 0x028010, 0x02 ),
   INP1( P1_LEFT, 0x028010, 0x04 ),
   INP1( P1_RIGHT, 0x028010, 0x08 ),
   INP0( P1_B1, 0x02800E, 0x01 ),
   INP0( P1_B2, 0x02800E, 0x04 ),

   INP0( P2_START, 0x028004, 0x80 ),
   INP1( P2_UP, 0x028020, 0x01 ),
   INP1( P2_DOWN, 0x028020, 0x02 ),
   INP1( P2_LEFT, 0x028020, 0x04 ),
   INP1( P2_RIGHT, 0x028020, 0x08 ),
   INP0( P2_B1, 0x02800E, 0x02 ),
   INP0( P2_B2, 0x02800E, 0x08 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_operation_thunderbolt_0[] =
{
   { _("Continue Mode"),         0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
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

static struct DSW_DATA dsw_data_operation_thunderbolt_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Bullet Mags / Rockets"), 0x0c, 0x04 },
   { "5 / 3",                 0x0c},
   { "6 / 4",                 0x08},
   { "7 / 5",                 0x04},
   { "8 / 6",                 0x00},
   { _("Bullets per Magazine"),  0x30, 0x04 },
   { "40",                    0x30},
   { "50",                    0x20},
   { "35",                    0x10},
   { "30",                    0x00},
   { _("Half Price Continue"),   0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Game Title Language"),   0x80, 0x02 },
   { _("Japanese"),              0x80},
   { _("English"),               0x00},
   { NULL,                    0,   },
};
static struct DSW_INFO dsw_othunder[] =
{
   { 0x028000, 0xFF, dsw_data_operation_thunderbolt_0 },
   { 0x028002, 0x7F, dsw_data_operation_thunderbolt_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_operation_thunderbolt_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_othunder[] =
{
   { 0x03FFFF, 0x03, romsw_data_operation_thunderbolt_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static int x1,myy1,x11,myy11,x2,y2;

static void load_othunder(void)
{
   int ta,tb,tc,td,te,tf;
   UINT8 *TMP;

   if(!(TMP=AllocateMem(0x2CBA00))) return;
   if(!(GFX=AllocateMem(0x100000+0x459000+0x2000+0x4000))) return;

   tb=0x80000;
   if(!load_rom("b67-04", TMP, 0x49740)) return;		// 16x8 SPRITES
   for(ta=0;ta<0x49740;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]=((tc&0x8000)>>(15-0));
      TMP[tb+1]=((tc&0x4000)>>(14-0));
      TMP[tb+2]=((tc&0x2000)>>(13-0));
      TMP[tb+3]=((tc&0x1000)>>(12-0));
      TMP[tb+4]=((tc&0x0800)>>(11-0));
      TMP[tb+5]=((tc&0x0400)>>(10-0));
      TMP[tb+6]=((tc&0x0200)>>(9-0));
      TMP[tb+7]=((tc&0x0100)>>(8-0));
      TMP[tb+8]=((tc&0x0080)>>(7-0));
      TMP[tb+9]=((tc&0x0040)>>(6-0));
      TMP[tb+10]=((tc&0x0020)>>(5-0));
      TMP[tb+11]=((tc&0x0010)>>(4-0));
      TMP[tb+12]=((tc&0x0008)>>(3-0));
      TMP[tb+13]=((tc&0x0004)>>(2-0));
      TMP[tb+14]=((tc&0x0002)>>(1-0));
      TMP[tb+15]=((tc&0x0001)>>(0-0));
      tb+=16;
   }
   tb=0x80000;
   if(!load_rom("b67-03", TMP, 0x49740)) return;		// 16x8 SPRITES
   for(ta=0;ta<0x49740;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]|=((tc&0x8000)>>(15-1));
      TMP[tb+1]|=((tc&0x4000)>>(14-1));
      TMP[tb+2]|=((tc&0x2000)>>(13-1));
      TMP[tb+3]|=((tc&0x1000)>>(12-1));
      TMP[tb+4]|=((tc&0x0800)>>(11-1));
      TMP[tb+5]|=((tc&0x0400)>>(10-1));
      TMP[tb+6]|=((tc&0x0200)>>(9-1));
      TMP[tb+7]|=((tc&0x0100)>>(8-1));
      TMP[tb+8]|=((tc&0x0080)>>(7-1));
      TMP[tb+9]|=((tc&0x0040)>>(6-1));
      TMP[tb+10]|=((tc&0x0020)>>(5-1));
      TMP[tb+11]|=((tc&0x0010)>>(4-1));
      TMP[tb+12]|=((tc&0x0008)>>(3-1));
      TMP[tb+13]|=((tc&0x0004)>>(2-1));
      TMP[tb+14]|=((tc&0x0002)>>(0));
      TMP[tb+15]|=((tc&0x0001)<<(1));
      tb+=16;
   }
   tb=0x80000;
   if(!load_rom("b67-02", TMP, 0x49740)) return;		// 16x8 SPRITES
   for(ta=0;ta<0x49740;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]|=((tc&0x8000)>>(15-2));
      TMP[tb+1]|=((tc&0x4000)>>(14-2));
      TMP[tb+2]|=((tc&0x2000)>>(13-2));
      TMP[tb+3]|=((tc&0x1000)>>(12-2));
      TMP[tb+4]|=((tc&0x0800)>>(11-2));
      TMP[tb+5]|=((tc&0x0400)>>(10-2));
      TMP[tb+6]|=((tc&0x0200)>>(9-2));
      TMP[tb+7]|=((tc&0x0100)>>(8-2));
      TMP[tb+8]|=((tc&0x0080)>>(7-2));
      TMP[tb+9]|=((tc&0x0040)>>(6-2));
      TMP[tb+10]|=((tc&0x0020)>>(5-2));
      TMP[tb+11]|=((tc&0x0010)>>(4-2));
      TMP[tb+12]|=((tc&0x0008)>>(3-2));
      TMP[tb+13]|=((tc&0x0004)>>(0));
      TMP[tb+14]|=((tc&0x0002)<<(1));
      TMP[tb+15]|=((tc&0x0001)<<(2));
      tb+=16;
   }
   tb=0x80000;
   if(!load_rom("b67-01", TMP, 0x49740)) return;		// 16x8 SPRITES
   for(ta=0;ta<0x49740;ta+=2){
      tc=ReadWord(&TMP[ta]);
      TMP[tb+0]|=((tc&0x8000)>>(15-3));
      TMP[tb+1]|=((tc&0x4000)>>(14-3));
      TMP[tb+2]|=((tc&0x2000)>>(13-3));
      TMP[tb+3]|=((tc&0x1000)>>(12-3));
      TMP[tb+4]|=((tc&0x0800)>>(11-3));
      TMP[tb+5]|=((tc&0x0400)>>(10-3));
      TMP[tb+6]|=((tc&0x0200)>>(9-3));
      TMP[tb+7]|=((tc&0x0100)>>(8-3));
      TMP[tb+8]|=((tc&0x0080)>>(7-3));
      TMP[tb+9]|=((tc&0x0040)>>(6-3));
      TMP[tb+10]|=((tc&0x0020)>>(5-3));
      TMP[tb+11]|=((tc&0x0010)>>(4-3));
      TMP[tb+12]|=((tc&0x0008)>>(0));
      TMP[tb+13]|=((tc&0x0004)<<(1));
      TMP[tb+14]|=((tc&0x0002)<<(2));
      TMP[tb+15]|=((tc&0x0001)<<(3));
      tb+=16;
   }

   te=0;
   if(!load_rom("b67-05", TMP, 0x11640)) return;		// 64x64 SPRITES
   for(ta=0x100000;ta<0x559000;ta+=0x1000){
      for(tb=0;tb<8;tb++){
      for(tc=0;tc<4;tc++){
         td=((TMP[te+1]<<8)|(TMP[te+0]));
         td=td<<7;
         td+=0x80000;
         te+=2;
         for(tf=0;tf<8;tf++){
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+0],ReadLong(&TMP[td+0]));
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+4],ReadLong(&TMP[td+4]));
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+8],ReadLong(&TMP[td+8]));
            WriteLong(&GFX[(tb<<9)+(tc<<4)+(tf<<6)+ta+12],ReadLong(&TMP[td+12]));
            td+=16;
         }
      }
      }
   }


   tb=0;
   if(!load_rom("b67-06", TMP, 0x80000)) return;		// 8x8 BG TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb+3]=TMP[ta+0]&15;
      GFX[tb+2]=TMP[ta+0]>>4;
      GFX[tb+1]=TMP[ta+1]&15;
      GFX[tb+0]=TMP[ta+1]>>4;
      tb+=4;
   }

   GFX_BG0=GFX+0x000000;
   GFX_SPR=GFX+0x100000;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x4000);
   GFX_SPR_SOLID = MakeSolidTileMap64x64(GFX_SPR, 0x459);

   Init64x64_Table(&GFX[0x559000]);	// $2000 bytes

   RAMSize=0x48000+0x10000+0x80;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom("b67-20", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("b67-23", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("b67-14.61", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("b67-15.62", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x48000;
   if(!load_rom("b67-13.40", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("b67-07",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("b67-08",PCMROM+0x80000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x0338, 0x02A5, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x10000;
   RAM_SCROLL = RAM+0x28100;
   RAM_INPUT  = RAM+0x28000;

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
   InitPaletteMap(RAM+0x38000, 0x100, 0x10, 0x8000);

   GFX_FG0 = RAM+0x3C000;

   tc0110pcr_init(RAM+0x38000, 1);

   EEPROM=RAM+0x48000+0x10000;

   add_eeprom(EEPROM, 0x80, EPR_INVALIDATE_ON_ROM_CHANGE);
   load_eeprom();

   WriteLong68k(&ROM[0x072C],0x4E714E71);	// FIX INTERRUPT

   WriteLong68k(&ROM[0x1A2E],0x4E714E71);	// FIX MAIN CHECKSUM ERROR
   WriteLong68k(&ROM[0x1A32],0x4E714E71);

   ROM[0xCDBE]=0x60;	// FIX SOUND? ERROR

   ROM[0x185C]=0x4E;	// FIX MAIN RAM CHECK
   ROM[0x185D]=0x71;
   ROM[0x185E]=0x4E;
   ROM[0x185F]=0x71;

   ROM[0x187A]=0x4E;	// FIX MAIN RAM CHECK
   ROM[0x187B]=0x71;
   ROM[0x187C]=0x4E;
   ROM[0x187D]=0x71;

   ROM[0x1898]=0x4E;	// FIX MAIN RAM CHECK
   ROM[0x1899]=0x71;
   ROM[0x189A]=0x4E;
   ROM[0x189B]=0x71;

   ROM[0x18B6]=0x4E;	// FIX MAIN RAM CHECK
   ROM[0x18B7]=0x71;
   ROM[0x18B8]=0x4E;
   ROM[0x18B9]=0x71;

   ROM[0x007A]=0xCD;
   ROM[0x007B]=0x3E;

   ROM[0xCD3E]=0x48;		// IMPROVE INT#6
   ROM[0xCD3F]=0xE7;
   ROM[0xCD40]=0xC0;
   ROM[0xCD41]=0xC0;

   ROM[0x0868]=0x4E;		// SKIP OLD CODE (NO ROOM FOR HACK)
   ROM[0x0867]=0xF9;		// (JMP $7FF00)
   ROM[0x0868]=0x00;
   ROM[0x0869]=0x07;
   ROM[0x086A]=0xFF;
   ROM[0x086B]=0x00;

   ROM[0x7FF00]=0x4E;		// (JSR $000400)
   ROM[0x7FF01]=0xB9;
   ROM[0x7FF02]=0x00;
   ROM[0x7FF03]=0x00;
   ROM[0x7FF04]=0x04;
   ROM[0x7FF05]=0x00;

   ROM[0x7FF06]=0x13;		// move.b #$00,$AA0000
   ROM[0x7FF07]=0xFC;		// (Speed Hack)
   ROM[0x7FF08]=0x00;
   ROM[0x7FF09]=0x00;
   ROM[0x7FF0A]=0x00;
   ROM[0x7FF0B]=0xAA;
   ROM[0x7FF0C]=0x00;
   ROM[0x7FF0D]=0x00;

   ROM[0x7FF0E]=0x60;		// Loop
   ROM[0x7FF0F]=0x100-0x0A;

   // EEPROM Read Hack
   // ----------------

   WriteLong68k(&ROM[0xCD68],0x4E560000);	//	link	a6,#0
   WriteLong68k(&ROM[0xCD6C],0x48E7C0C0);	//	movem.l	D0-D1/a0-a1,-(a7)
   WriteLong68k(&ROM[0xCD70],0x206E0008);	//	movea.l	8(a6),a0
   WriteLong68k(&ROM[0xCD74],0x322E000C);	//	move	12(a6),D1
   WriteLong68k(&ROM[0xCD78],0x02810000);	//	andi.l	#$0000003F,D1
   WriteWord68k(&ROM[0xCD7C],0x003F);		//
   WriteWord68k(&ROM[0xCD7E],0x43F9);		//	lea	EXT_0000,a1
   WriteLong68k(&ROM[0xCD80],0x00BB0000);	//
   WriteWord68k(&ROM[0xCD84],0xE349);		//	lsL	#1,D1
   WriteWord68k(&ROM[0xCD86],0xD2C1);		//	adda	D1,a1
   WriteWord68k(&ROM[0xCD88],0x3091);		//	move	(a1),(a0)
   WriteLong68k(&ROM[0xCD8A],0x4CDF0303);	//	movem.l	(a7)+,D0-D1/a0-a1
   WriteWord68k(&ROM[0xCD8E],0x4E5E);		//	unlk	a6
   WriteWord68k(&ROM[0xCD90],0x4E75);		//	rts

   // EEPROM Write Hack
   // -----------------

   WriteLong68k(&ROM[0xCE32],0x4E560000);	//	link	a6,#0
   WriteLong68k(&ROM[0xCE36],0x48E7C0C0);	//	movem.l	D0-D1/a0-a1,-(a7)
   WriteLong68k(&ROM[0xCE3A],0x206E0008);	//	movea.l	8(a6),a0
   WriteLong68k(&ROM[0xCE3E],0x322E000C);	//	move	12(a6),D1
   WriteLong68k(&ROM[0xCE42],0x02810000);	//	andi.l	#$0000003F,D1
   WriteWord68k(&ROM[0xCE46],0x003F);		//
   WriteWord68k(&ROM[0xCE48],0x43F9);		//	lea	EXT_0000,a1
   WriteLong68k(&ROM[0xCE4A],0x00BB0000);	//
   WriteWord68k(&ROM[0xCE4E],0xE349);		//	lsL	#1,D1
   WriteWord68k(&ROM[0xCE50],0xD2C1);		//	adda	D1,a1
   WriteWord68k(&ROM[0xCE52],0x3290);		//	move	(a0),(a1)
   WriteLong68k(&ROM[0xCE54],0x4CDF0303);	//	movem.l	(a7)+,D0-D1/a0-a1
   WriteWord68k(&ROM[0xCE58],0x4E5E);		//	unlk	a6
   WriteWord68k(&ROM[0xCE5A],0x4E75);		//	rts

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=64;
   tc0100scn[0].layer[0].bmp_y	=64;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=20;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=64;
   tc0100scn[0].layer[1].bmp_y	=64;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=20;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=64;
   tc0100scn[0].layer[2].bmp_y	=64;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=240;
   tc0100scn[0].layer[2].scr_x	=20;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x3C000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x090000, 0x09000F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x500000, 0x50000F, NULL, RAM+0x028200);			// GUN PORTS
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x400000, 0x4005FF, NULL, RAM+0x020000);			// SPRITE RAM
   AddReadWord(0x090000, 0x09000F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x100000, 0x100007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x300000, 0x300003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadWord(0xBB0000, 0xBB007F, NULL, EEPROM+0x000000);		// EEPROM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0x206000, 0x206FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x500000, 0x50000F, NULL, RAM+0x028200);		// GUN PORTS
   AddWriteByte(0x090000, 0x09000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x206000, 0x206FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x400000, 0x4005FF, NULL, RAM+0x020000);		// SPRITE RAM
   AddWriteWord(0x100000, 0x100007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x220000, 0x22000F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x500000, 0x50000F, NULL, RAM+0x028200);		// GUN PORTS
   AddWriteWord(0x300000, 0x300003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteWord(0x600000, 0x60000F, NULL, RAM+0x028400);		// ??? RAM
   AddWriteWord(0x090000, 0x09000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0xBB0000, 0xBB007F, NULL, EEPROM+0x000000);		// EEPROM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   x1=64;
   myy1=64;

   x2=64;
   y2=64;

   GameMouse=1;
}

static void execute_othunder(void)
{
   /*------[Mouse Hack]-------*/

   set_mouse_range(0,0,319,239);

   x11=319-mouse_x;
   myy11=mouse_y;

   x1=(x11<<7)/320;
   myy1=(myy11<<7)/240;

   if(x1<0){x1=0;}
   if(x1>127){x1=127;}
   if(myy1<0){myy1=0;}
   if(myy1>127){myy1=127;}

   if(mouse_b&1) RAM[0x2800E] &= ~0x01;
   if(mouse_b&2) RAM[0x2800E] &= ~0x04;

   /*-----[Keyboard Hack]-----*/

   if(((RAM[0x28010]&0x01)!=0)&&(myy1>  0)) myy1--;
   if(((RAM[0x28010]&0x02)!=0)&&(myy1<127)) myy1++;
   if(((RAM[0x28010]&0x08)!=0)&&(x1>  0)) x1--;
   if(((RAM[0x28010]&0x04)!=0)&&(x1<127)) x1++;

   if(((RAM[0x28020]&0x01)!=0)&&(y2>  0)) y2--;
   if(((RAM[0x28020]&0x02)!=0)&&(y2<127)) y2++;
   if(((RAM[0x28020]&0x08)!=0)&&(x2>  0)) x2--;
   if(((RAM[0x28020]&0x04)!=0)&&(x2<127)) x2++;

   /*----[Write Positions]----*/

   RAM[0x2854]=x1+128-64;
   RAM[0x2856]=myy1+128-64;
   RAM[0x2858]=x2+128-64;
   RAM[0x285A]=y2+128-64;

   /*------[EE-ROM Hack]------*/

   WriteLong(&RAM[0xA026+0x00], 0x00C00040);
   WriteLong(&RAM[0xA026+0x04], 0x80000002);
   WriteLong(&RAM[0xA026+0x08], 0x00C00040);
   WriteLong(&RAM[0xA026+0x0C], 0xE0000001);

   WriteLong(&RAM[0xA026+0x10], 0x00C00040);
   WriteLong(&RAM[0xA026+0x14], 0x80000002);
   WriteLong(&RAM[0xA026+0x18], 0x00C00040);
   WriteLong(&RAM[0xA026+0x1C], 0xE0000001);

   WriteLong(&RAM[0xA026+0x20], 0x00800080);
   WriteLong(&RAM[0xA026+0x24], 0x00800080);
   WriteLong(&RAM[0xA026+0x28], 0x80000002);
   WriteLong(&RAM[0xA026+0x2C], 0xE0000001);

   WriteLong(&RAM[0xA026+0x30], 0x80000002);
   WriteLong(&RAM[0xA026+0x34], 0xE0000001);

   WriteLong(&RAM[0xA026+0x38], 0x80000002);
   WriteLong(&RAM[0xA026+0x3C], 0xE0000001);

   WriteLong(&RAM[0xA026+0x40], 0x80000002);
   WriteLong(&RAM[0xA026+0x44], 0xE0000001);

   WriteLong(&RAM[0xA026+0x24], 0x00800080);

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610
}

static void DrawOpThunderbolt(void)
{
   int x,y,z,ta,zz;
   UINT8 *MAP;

   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped_flipy(0,0);

   // OBJECT LOW
   // ----------

   for(zz=0x20600-8;zz>=0x20000;zz-=8){

      if((RAM[zz+3]&0x80)==0) continue;

      z=(RAM[zz+1]>>1)&63;
      if(z==0) continue;
      y=RAM[zz];
      if((RAM[zz+1]&1)!=0) y=0-((y^255)+1);
      y=32+19+y;
      x=ReadWord(&RAM[zz+2])&0x1FF;
      if(x>400) x=0-((x^511)+1);
      x=(320+(63-z))-x;

      if((x>0)&&(y>0)&&(x<320+64)&&(y<240+64)){
	  ta=ReadWord(&RAM[zz+6])&0x7FF;

	  if((ta==0)||(ta>=0x559)) continue;

	  MAP_PALETTE_MAPPED_NEW(
		  RAM[zz+5],
		  16,        MAP
		  );

	  if((RAM[zz+7]&0x80)==0){
	      if((RAM[zz+3]&0x40)!=0)
		  Draw64x64_Trans_Mapped_Zoom_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);
	      else
		  Draw64x64_Trans_Mapped_Zoom_FlipY_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);
	  }
	  else{
	      if((RAM[zz+3]&0x40)!=0){	Draw64x64_Trans_Mapped_Zoom_FlipX_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);}
	      else{				Draw64x64_Trans_Mapped_Zoom_FlipXY_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);}
	  }

      }
   }

   // BG1
   // ---

   render_tc0100scn_layer_mapped_flipy(0,1);

   // OBJECT HIGH
   // -----------

   for(zz=0x20600-8;zz>=0x20000;zz-=8){

      if((RAM[zz+3]&0x80)==0){

      z=(RAM[zz+1]>>1)&63;
      if(z!=0){
         y=RAM[zz];
         if((RAM[zz+1]&1)!=0){y=0-((y^255)+1);}
         y=32+19+y;
         x=ReadWord(&RAM[zz+2])&0x1FF;
         if(x>400){x=0-((x^511)+1);}
         x=(320+(63-z))-x;

         if((x>0)&&(y>0)&&(x<320+64)&&(y<240+64)){
            ta=ReadWord(&RAM[zz+6])&0x7FF;

            if((ta!=0)&&(ta<0x559)){

      MAP_PALETTE_MAPPED_NEW(
               RAM[zz+5],
               16,        MAP
            );

               //(*Zoom64x64_Trans_Mapped_JumpList[z])(&GFX_SPR[ta<<12],x,y,MAP);

               if((RAM[zz+7]&0x80)==0){
                  if((RAM[zz+3]&0x40)!=0){	Draw64x64_Trans_Mapped_Zoom_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);}
                  else{				Draw64x64_Trans_Mapped_Zoom_FlipY_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);}
               }
               else{
                  if((RAM[zz+3]&0x40)!=0){	Draw64x64_Trans_Mapped_Zoom_FlipX_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);}
                  else{				Draw64x64_Trans_Mapped_Zoom_FlipXY_Rot(&GFX_SPR[ta<<12],x,y,MAP,z);}
               }


            }
         }
      }
      }
   }

   // FG0
   // ---

   render_tc0100scn_layer_mapped_flipy(0,2);

   // GUNS
   // ----

   x=(64+(((127-x2)*320)>>7))-7;		// Player 2
   y=(64+((y2*240)>>7))-(7+16);
   if((x>48)&&(y>48)&&(x<320+64)&&(y<240+64)){
     disp_gun(1,x,y);
   }

   x=(64+(319-x11))-7;				// Player 1
   y=(64+myy11)-(7+16);
   if((x>48)&&(y>48)&&(x<320+64)&&(y<240+64)){
     disp_gun(0,x,y);
   }

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
  2  |..?????x| X Position (High)
  3  |xxxxxxxx| X Position (Low)
  4  |xxxxxxxx| Palette Bank
  5  |..xxxxxx| ZoomX (0-63)
  6  |x.......| Flip X Axis?
  6  |.....xxx| Sprite Number (High)
  7  |xxxxxxxx| Sprite Number (Low)

*/
static struct VIDEO_INFO video_othunder =
{
   DrawOpThunderbolt,
   320,
   240,
   64,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_othunder[] =
{
   { "operation_thunderbolt", },
   { "othunder", },
   { NULL, },
};
GME( othunder, "Operation Thunderbolt", TAITO, 1989, GAME_SHOOT,
	.romsw = romsw_othunder,
	.long_name_jpn = "オペレーションサンダーボルト",
	.board = "B67",
);

