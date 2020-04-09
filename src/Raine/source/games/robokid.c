/******************************************************************************/
/*                                                                            */
/*                        ATOMIC ROBOKID (C) 1988 UPL                         */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "savegame.h"


static struct ROM_INFO rom_robokid[] =
{
   {  "robokid.12a", 0x00010000, 0xe64d1c10, 0, 0, 0, },
   {  "robokid.12c", 0x00010000, 0x0ab45f94, 0, 0, 0, },
   {  "robokid.14a", 0x00010000, 0x8f9371e4, 0, 0, 0, },
   {  "robokid.14c", 0x00010000, 0x029bbd4a, 0, 0, 0, },
   {  "robokid.15a", 0x00010000, 0x469204e7, 0, 0, 0, },
   {  "robokid.15c", 0x00010000, 0x7de67ebb, 0, 0, 0, },
   {  "robokid.15d", 0x00010000, 0xcd632a4d, 0, 0, 0, },
   {  "robokid.15f", 0x00010000, 0xba61f5ab, 0, 0, 0, },
   {  "robokid.16a", 0x00010000, 0x4e340815, 0, 0, 0, },
   {  "robokid.16c", 0x00010000, 0x53c0e582, 0, 0, 0, },
   {  "robokid.16d", 0x00010000, 0x18d92b2b, 0, 0, 0, },
   {  "robokid.16f", 0x00010000, 0xd9b399ce, 0, 0, 0, },
   {  "robokid.17a", 0x00010000, 0xf0863106, 0, 0, 0, },
   {  "robokid.17c", 0x00010000, 0x0cae5a1e, 0, 0, 0, },
   {  "robokid.17d", 0x00010000, 0x2fa29b99, 0, 0, 0, },
   {  "robokid.17f", 0x00010000, 0xafe432b9, 0, 0, 0, },
   {  "robokid.18a", 0x00010000, 0xfdff7441, 0, 0, 0, },
   {  "robokid.18c", 0x00010000, 0x56ac7c8a, 0, 0, 0, },
   {  "robokid.18d", 0x00010000, 0xae15ce02, 0, 0, 0, },
   {  "robokid.18f", 0x00010000, 0xa0aa2a84, 0, 0, 0, },
   {  "robokid.19c", 0x00010000, 0x02220421, 0, 0, 0, },
   {  "robokid.19d", 0x00010000, 0x784b089e, 0, 0, 0, },
   {  "robokid.19f", 0x00010000, 0x0f9071c6, 0, 0, 0, },
   {  "robokid.20c", 0x00010000, 0x02d59bc2, 0, 0, 0, },
   {  "robokid.20d", 0x00010000, 0xb0b395ed, 0, 0, 0, },
   {   "robokid.b9", 0x00008000, 0xfac59c3f, 0, 0, 0, },
   {   "robokid.k7", 0x00010000, 0xf490a2e9, 0, 0, 0, },
   { "robokid1.18j", 0x00010000, 0x378c21fc, 0, 0, 0, },
   { "robokid2.18k", 0x00010000, 0xddef8c5a, 0, 0, 0, },
   { "robokid3.15k", 0x00010000, 0x05295ec3, 0, 0, 0, },
   { "robokid4.12k", 0x00010000, 0x3bc3977f, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_robokid[] =
{
   INP0( COIN1, 0x00DC00, 0x20 ),
   INP0( COIN2, 0x00DC00, 0x40 ),
   INP0( TILT, 0x00DC00, 0x04 ),
   INP0( SERVICE, 0x00DC00, 0x08 ),

   INP0( P1_START, 0x00DC00, 0x01 ),
   INP0( P1_UP, 0x00DC01, 0x08 ),
   INP0( P1_DOWN, 0x00DC01, 0x04 ),
   INP0( P1_LEFT, 0x00DC01, 0x02 ),
   INP0( P1_RIGHT, 0x00DC01, 0x01 ),
   INP0( P1_B1, 0x00DC01, 0x10 ),
   INP0( P1_B2, 0x00DC01, 0x20 ),

   INP0( P2_START, 0x00DC00, 0x02 ),
   INP0( P2_UP, 0x00DC02, 0x08 ),
   INP0( P2_DOWN, 0x00DC02, 0x04 ),
   INP0( P2_LEFT, 0x00DC02, 0x02 ),
   INP0( P2_RIGHT, 0x00DC02, 0x01 ),
   INP0( P2_B1, 0x00DC02, 0x10 ),
   INP0( P2_B2, 0x00DC02, 0x20 ),

   END_INPUT
};

static struct DSW_INFO dsw_robokid[] =
{
   { 0x00DC03, 0xFF, dsw_data_default_0 },
   { 0x00DC04, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};


static struct YM2203interface ym2203_interface =
{
     2,				// 2 Chips
     5000000,			// 1.25 * 4 ?
   { 0x00ff20c0, 0x00ff20c0 },
   { 0,          0          },
   { 0,          0          },
   { 0,          0          },
   { 0,          0          },
   { NULL,       NULL       }
};

static struct SOUND_INFO sound_robokid[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { 0,             NULL,                 },
};



static struct ROM_INFO rom_robokidj[] =
{
   {  "robokid.12a", 0x00010000, 0xe64d1c10, 0, 0, 0, },
   {  "robokid.12c", 0x00010000, 0x0ab45f94, 0, 0, 0, },
   {  "robokid.14a", 0x00010000, 0x8f9371e4, 0, 0, 0, },
   {  "robokid.14c", 0x00010000, 0x029bbd4a, 0, 0, 0, },
   {  "robokid.15a", 0x00010000, 0x469204e7, 0, 0, 0, },
   {  "robokid.15c", 0x00010000, 0x7de67ebb, 0, 0, 0, },
   {  "robokid.15d", 0x00010000, 0xcd632a4d, 0, 0, 0, },
   {  "robokid.15f", 0x00010000, 0xba61f5ab, 0, 0, 0, },
   {  "robokid.16a", 0x00010000, 0x4e340815, 0, 0, 0, },
   {  "robokid.16c", 0x00010000, 0x53c0e582, 0, 0, 0, },
   {  "robokid.16d", 0x00010000, 0x18d92b2b, 0, 0, 0, },
   {  "robokid.16f", 0x00010000, 0xd9b399ce, 0, 0, 0, },
   {  "robokid.17a", 0x00010000, 0xf0863106, 0, 0, 0, },
   {  "robokid.17c", 0x00010000, 0x0cae5a1e, 0, 0, 0, },
   {  "robokid.17d", 0x00010000, 0x2fa29b99, 0, 0, 0, },
   {  "robokid.17f", 0x00010000, 0xafe432b9, 0, 0, 0, },
   {  "robokid.18a", 0x00010000, 0xfdff7441, 0, 0, 0, },
   {  "robokid.18c", 0x00010000, 0x56ac7c8a, 0, 0, 0, },
   {  "robokid.18d", 0x00010000, 0xae15ce02, 0, 0, 0, },
   {  "robokid.18f", 0x00010000, 0xa0aa2a84, 0, 0, 0, },
   {  "robokid.19c", 0x00010000, 0x02220421, 0, 0, 0, },
   {  "robokid.19d", 0x00010000, 0x784b089e, 0, 0, 0, },
   {  "robokid.19f", 0x00010000, 0x0f9071c6, 0, 0, 0, },
   {  "robokid.20c", 0x00010000, 0x02d59bc2, 0, 0, 0, },
   {  "robokid.20d", 0x00010000, 0xb0b395ed, 0, 0, 0, },
   {   "robokid.b9", 0x00008000, 0xfac59c3f, 0, 0, 0, },
   {   "robokid.k7", 0x00010000, 0xf490a2e9, 0, 0, 0, },
   {         "1.29", 0x00010000, 0x59a1e2ec, 0, 0, 0, },
   {         "2.30", 0x00010000, 0xe3f73476, 0, 0, 0, },
   { "robokid3.15k", 0x00010000, 0x05295ec3, 0, 0, 0, },
   { "robokid4.12k", 0x00010000, 0x3bc3977f, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static int romset;

static UINT8 *RAM2;
static UINT8 *ROM2;
static UINT8 *RAM_VIDEO;

static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_FG0;
static UINT8 *RAM_SPR;

static UINT8 *SCR_BG0;
static UINT8 *SCR_BG1;
static UINT8 *SCR_BG2;

static UINT8 mask_bg0;
static UINT8 mask_bg1;
static UINT8 mask_bg2;
static UINT8 mask_fg0;
static UINT8 mask_spr;

static UINT8 *GFX_FG0;
static UINT8 *FG0_Mask;

static UINT8 *GFX_SPR;
static UINT8 *SPR_Mask;

static UINT8 *GFX_BG1;
static UINT8 *BG1_Mask;

static UINT8 *GFX_BG0;
static UINT8 *BG0_Mask;

static UINT8 *GFX_BG2;
static UINT8 *BG2_Mask;

/*

UPL GAMES
---------

Supported romsets:

0 - Atomic Robokid

Ninja Kid 2 was seperated, due to several hardware differences.

*/

/******************************************************************************/
/* ROBO KID Z80 ROM BANKING                                                   */
/******************************************************************************/

static void RoboKidBankWrite(UINT16 offset, UINT8 data)
{
  z80_set_bank(1,data);
}

static void init_bank_rom(UINT8 *src, UINT8 *dst, UINT8 bank_skip)
{
  z80_init_banks_area_ofs(1,src,0x40000,0x8000,0x4000,2);
}

/******************************************************************************/
/* ROBO KID SOUND COMMUNICATION                                               */
/******************************************************************************/

static UINT8 sound_byte;

static void RoboKidSoundWrite(UINT16 offset, UINT8 data)
{
   sound_byte = data;
}

static UINT8 RoboKidSoundRead(UINT16 offset)
{
   UINT8 ta;
   ta = sound_byte;
   sound_byte = 0xFF;
   return ta;
}

/******************************************************************************/
/* ROBO KID VIDEO RAM BANKING                                                 */
/******************************************************************************/

static UINT8 *BG_BANK[4];

static void RoboKidBG0BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[2] = RAM_VIDEO+(2<<11)+((data&1)<<10);
}

static void RoboKidBG1BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[1] = RAM_VIDEO+(1<<11)+((data&1)<<10);
}

static void RoboKidBG2BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[0] = RAM_VIDEO+(0<<11)+((data&1)<<10);
}

static void RoboKidBG012Write(UINT16 offset, UINT8 data)
{
   BG_BANK[(offset>>10)&3][offset&0x3FF] = data;
}

static UINT8 RoboKidBG012Read(UINT16 offset)
{
   return BG_BANK[(offset>>10)&3][offset&0x3FF];
}

static void RoboKidBG012Init(void)
{
   BG_BANK[0] = RAM_VIDEO+(0<<11);
   BG_BANK[1] = RAM_VIDEO+(1<<11);
   BG_BANK[2] = RAM_VIDEO+(2<<11);
   BG_BANK[3] = RAM_VIDEO+(3<<11);
}

/******************************************************************************/
/* GFX DECODES (from MS-1)                                                    */
/******************************************************************************/

static int MS1DecodeFG0(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_FG0=AllocateMem(0x10000))) return(0);
   memset(GFX_FG0,0x00,0x10000);

   tb=0;
   for(ta=0;ta<size;ta++,tb+=2){
      GFX_FG0[tb+0]=(src[ta]>>4)^15;
      GFX_FG0[tb+1]=(src[ta]&15)^15;
   }

   FG0_Mask = make_solid_mask_8x8(GFX_FG0, 0x400);

   return 1;
}

static int MS1DecodeSPR(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_SPR=AllocateMem(0x100000))) return(0);
   memset(GFX_SPR,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_SPR[tb+0]=(src[ta+0]>>4)^15;
      GFX_SPR[tb+1]=(src[ta+0]&15)^15;
      GFX_SPR[tb+2]=(src[ta+1]>>4)^15;
      GFX_SPR[tb+3]=(src[ta+1]&15)^15;
      GFX_SPR[tb+4]=(src[ta+2]>>4)^15;
      GFX_SPR[tb+5]=(src[ta+2]&15)^15;
      GFX_SPR[tb+6]=(src[ta+3]>>4)^15;
      GFX_SPR[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   SPR_Mask = make_solid_mask_16x16(GFX_SPR, 0x1000);

   return 1;
}

static int MS1DecodeBG2(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG2=AllocateMem(0x100000))) return(0);
   memset(GFX_BG2,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG2[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG2[tb+1]=(src[ta+0]&15)^15;
      GFX_BG2[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG2[tb+3]=(src[ta+1]&15)^15;
      GFX_BG2[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG2[tb+5]=(src[ta+2]&15)^15;
      GFX_BG2[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG2[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG2_Mask = make_solid_mask_16x16(GFX_BG2, 0x1000);

   return 1;
}

static int MS1DecodeBG1(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG1=AllocateMem(0x100000))) return(0);
   memset(GFX_BG1,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG1[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG1[tb+1]=(src[ta+0]&15)^15;
      GFX_BG1[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG1[tb+3]=(src[ta+1]&15)^15;
      GFX_BG1[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG1[tb+5]=(src[ta+2]&15)^15;
      GFX_BG1[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG1[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG1_Mask = make_solid_mask_16x16(GFX_BG1, 0x1000);

   return 1;
}

static int MS1DecodeBG0(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG0=AllocateMem(0x100000))) return(0);
   memset(GFX_BG0,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG0[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG0[tb+1]=(src[ta+0]&15)^15;
      GFX_BG0[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG0[tb+3]=(src[ta+1]&15)^15;
      GFX_BG0[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG0[tb+5]=(src[ta+2]&15)^15;
      GFX_BG0[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG0[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG0_Mask = make_solid_mask_16x16(GFX_BG0, 0x1000);

   return 1;
}

/******************************************************************************/

static void RoboKidLoadUpdate(void)
{
   print_debug("Robokid Load Callback()\n");

   // BG RAM Bank Refresh

   if(romset==0){
      RoboKidBG0BankWrite(0xDD05,RAM[0xDD05]);
      RoboKidBG1BankWrite(0xDE05,RAM[0xDE05]);
      RoboKidBG2BankWrite(0xDF05,RAM[0xDF05]);
   }
}

static void load_robokid(void)
{
   UINT8 *TMP;

   romset=0;

   if(!(ROM=AllocateMem(0x40000))) return;
   if(!(ROM2=AllocateMem(0x10000))) return;

   RAMSize    = 0x10000+0x10000+0x2000+0x10;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_VIDEO  = RAM+0x10000+0x10000;

   if(!(TMP =AllocateMem(0x40000))) return;

   if(is_current_game("robokid")){

   if(!load_rom("robokid1.18j",TMP+0x00000,0x10000)) return;	// Z80 MAIN ROM *
   if(!load_rom("robokid2.18k",TMP+0x10000,0x10000)) return;	// Z80 MAIN ROM

   // Fix ROM Checksum

   TMP[0x33e2]=0x18;  // JR xx

   }
   else{

   if(!load_rom("1.29",TMP+0x00000,0x10000)) return;	// Z80 MAIN ROM *
   if(!load_rom("2.30",TMP+0x10000,0x10000)) return;	// Z80 MAIN ROM

   // Fix ROM Checksum

   TMP[0x3401]=0x18;  // JR xx

   }

   if(!load_rom("robokid3.15k",TMP+0x20000,0x10000)) return;	// Z80 MAIN ROM
   if(!load_rom("robokid4.12k",TMP+0x30000,0x10000)) return;	// Z80 MAIN ROM

   // Decustomize Interrupt

   TMP[0x0039]=0x10;

   // Skip Idle Z80

   TMP[0x0108]=0xD3;  // OUTA (AAh)
   TMP[0x0109]=0xAA;  //

   SetStopZ80BMode2(0x010A);

   init_bank_rom(TMP,ROM,0);

   memset(RAM+0x00000, 0x00, 0x10000);
   memset(RAM+0x0DC00, 0xFF, 0x00010);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0010, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM/BANK ROM
   AddZ80BReadByte(0xE000, 0xFFFF, NULL,			RAM+0xE000);	// RAM/OBJECT RAM
   AddZ80BReadByte(0xC000, 0xCFFF, NULL,			RAM+0xC000);	// COLOR/FG0 RAM
   AddZ80BReadByte(0xD000, 0xDBFF, RoboKidBG012Read,		NULL);		// BG0-2 RAM
   AddZ80BReadByte(0xDC00, 0xDC0F, NULL,			RAM+0xDC00);	// INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xE000, 0xFFFF, NULL,			RAM+0xE000);	// RAM/OBJECT RAM
   AddZ80BWriteByte(0xC000, 0xCFFF, NULL,			RAM+0xC000);	// COLOR/FG0 RAM
   AddZ80BWriteByte(0xD000, 0xDBFF, RoboKidBG012Write,		NULL);		// BG0-2 RAM
   AddZ80BWriteByte(0xDC00, 0xDC00, RoboKidSoundWrite,		NULL);		// SOUND
   AddZ80BWriteByte(0xDC02, 0xDC02, RoboKidBankWrite,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xDD05, 0xDD05, RoboKidBG0BankWrite,	NULL);		// BG0 BANK
   AddZ80BWriteByte(0xDE05, 0xDE05, RoboKidBG1BankWrite,	NULL);		// BG1 BANK
   AddZ80BWriteByte(0xDF05, 0xDF05, RoboKidBG2BankWrite,	NULL);		// BG2 BANK
   AddZ80BWriteByte(0xDD00, 0xDFFF, NULL,			RAM+0xDD00);	// SCROLL
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("robokid.k7",ROM2+0x00000,0x10000)) return;	// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x00B2]=0xD3;  // OUTA (AAh)
   ROM2[0x00B3]=0xAA;  //

   SetStopZ80CMode2(0x00B2);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xC7FF, NULL,			RAM2+0x0000);	// Z80 ROM/BANK ROM/RAM
   AddZ80CReadByte(0xE000, 0xE000, RoboKidSoundRead,		NULL);		// SOUND
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xC7FF, NULL,			RAM2+0xC000);	// RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0x01, YM2203AReadZ80,			NULL);		// YM2203#1
   AddZ80CReadPort(0x80, 0x81, YM2203BReadZ80,			NULL);		// YM2203#2
   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0x00, 0x01, YM2203AWriteZ80,		NULL);		// YM2203#1
   AddZ80CWritePort(0x80, 0x81, YM2203BWriteZ80,		NULL);		// YM2203#2
   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(TMP=AllocateMem(0x080000))) return;

   if(!load_rom("robokid.b9", TMP, 0x8000)) return;           // 8x8 FG0 TILES *
   if(!MS1DecodeFG0(TMP,0x08000))return;

   if(!load_rom("robokid.15f", TMP+0x00000, 0x10000)) return;  // 16x16 SPRITES *
   if(!load_rom("robokid.16f", TMP+0x10000, 0x10000)) return;  // 16x16 SPRITES *
   if(!load_rom("robokid.17f", TMP+0x20000, 0x10000)) return;  // 16x16 SPRITES *
   if(!load_rom("robokid.18f", TMP+0x30000, 0x10000)) return;  // 16x16 SPRITES *
   if(!MS1DecodeSPR(TMP,0x40000))return;

   memset(TMP,0xFF,0x80000);
   if(!load_rom("robokid.19c", TMP+0x00000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("robokid.20c", TMP+0x10000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("robokid.17d", TMP+0x20000, 0x10000)) return;  // 16x16 BG0 ?
   if(!load_rom("robokid.18d", TMP+0x30000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("robokid.19d", TMP+0x40000, 0x10000)) return;  // 16x16 BG0 ?
   if(!load_rom("robokid.20d", TMP+0x50000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("robokid.19f", TMP+0x60000, 0x10000)) return;  // 16x16 BG0 *
   if(!MS1DecodeBG0(TMP,0x80000))return;

   memset(TMP,0xFF,0x80000);
   if(!load_rom("robokid.12c", TMP+0x00000, 0x10000)) return;  // 16x16 BG1
   if(!load_rom("robokid.14c", TMP+0x10000, 0x10000)) return;  // 16x16 BG1 *
   if(!load_rom("robokid.15c", TMP+0x20000, 0x10000)) return;  // 16x16 BG1 *
   if(!load_rom("robokid.16c", TMP+0x30000, 0x10000)) return;  // 16x16 BG1 * (why 16a?)
   if(!load_rom("robokid.17c", TMP+0x40000, 0x10000)) return;  // 16x16 BG1 *
   if(!load_rom("robokid.18c", TMP+0x50000, 0x10000)) return;  // 16x16 BG1 *
   if(!load_rom("robokid.15d", TMP+0x60000, 0x10000)) return;  // 16x16 BG1 *
   if(!load_rom("robokid.16d", TMP+0x70000, 0x10000)) return;  // 16x16 BG1 *
   if(!MS1DecodeBG1(TMP,0x80000))return;

   memset(TMP,0xFF,0x80000);
   if(!load_rom("robokid.12a", TMP+0x00000, 0x10000)) return;  // 16x16 BG2
   if(!load_rom("robokid.14a", TMP+0x10000, 0x10000)) return;  // 16x16 BG2 *
   if(!load_rom("robokid.15a", TMP+0x20000, 0x10000)) return;  // 16x16 BG2
   if(!load_rom("robokid.16a", TMP+0x30000, 0x10000)) return;  // 16x16 BG2 * (why 16c?)
   if(!load_rom("robokid.17a", TMP+0x40000, 0x10000)) return;  // 16x16 BG2 *
   if(!load_rom("robokid.18a", TMP+0x50000, 0x10000)) return;  // 16x16 BG2 *
   if(!MS1DecodeBG2(TMP,0x80000))return;

   FreeMem(TMP);

   RoboKidBG012Init();

   RAM_BG0 = RAM_VIDEO+0x1000;
   RAM_BG1 = RAM_VIDEO+0x0800;
   RAM_BG2 = RAM_VIDEO+0x0000;
   RAM_FG0 = RAM+0xC800;
   RAM_SPR = RAM+0xFA00;
   SCR_BG0 = RAM+0xDD00;
   SCR_BG1 = RAM+0xDE00;
   SCR_BG2 = RAM+0xDF00;

   mask_bg0 = 0x00;
   mask_bg1 = 0x00;
   mask_bg2 = 0x00;
   mask_fg0 = 0x30;
   mask_spr = 0x20;

   InitPaletteMap(RAM+0xC000, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k);

   AddLoadCallback(RoboKidLoadUpdate);

   AddSaveData(SAVE_USER_1, (UINT8 *) &sound_byte,          sizeof(sound_byte));
}

static void execute_robokid(void)
{
   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(8,60));	// Main Z80 8MHz (60fps)
   /*#ifdef RAINE_DEBUG
      print_debug("Z80PC_MAIN:%04x [%04x]\n",z80pc,ReadWord(&RAM[0xE000]));
#endif*/
   cpu_interrupt(CPU_Z80_1, 0x10);

   cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(6,60));	// Sub Z80 6MHz (60fps)
   /*#ifdef RAINE_DEBUG
      print_debug("Z80PC_SUB:%04x\n",z80pc);
#endif*/
   cpu_interrupt(CPU_Z80_2, 0x38);
   cpu_interrupt(CPU_Z80_2, 0x38);
}

static UINT16 bg_map[0x10] =
{
  0x0000+0x0000+0x0000+0x0000,	// 0x00
  0x0800+0x0000+0x0000+0x0000,	// 0x10
  0x0000+0x0400+0x0000+0x0000,	// 0x20
  0x0800+0x0400+0x0000+0x0000,	// 0x30
  0x0000+0x0000+0x0100+0x0000,	// 0x40
  0x0800+0x0000+0x0100+0x0000,	// 0x50
  0x0000+0x0400+0x0100+0x0000,	// 0x60
  0x0800+0x0400+0x0100+0x0000,	// 0x70
  0x0000+0x0000+0x0000+0x0200,	// 0x80
  0x0800+0x0000+0x0000+0x0200,	// 0x90
  0x0000+0x0400+0x0000+0x0200,	// 0xA0
  0x0800+0x0400+0x0000+0x0200,	// 0xB0
  0x0000+0x0000+0x0100+0x0200,	// 0xC0
  0x0800+0x0000+0x0100+0x0200,	// 0xD0
  0x0000+0x0400+0x0100+0x0200,	// 0xE0
  0x0800+0x0400+0x0100+0x0200,	// 0xF0
};

static void DrawRoboKid(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   int xx,yy,rr;
   UINT8 *map;

   ClearPaletteMap();

   // BG0
   // ---
   if(RAM_BG0!=NULL){

   zzz=(ReadWord(&SCR_BG0[0]));
   zzzz =((zzz&0x00F0)>>4)<<1;                  // X Offset (16-255)
   zzzz+=((zzz&0x0100)>>4)<<6;                  // X Offset (256-511)
   x16=zzz&15;                                  // X Offset (0-15)
   zzz=(ReadWord(&SCR_BG0[2])+32);
   zzzz+=((zzz&0x01F0)>>4)<<5;                  // Y Offset (16-511)
   y16=zzz&15;                                  // Y Offset (0-15)

   zzzz=zzzz&0x7FF;
   zz=zzzz;
   for(y=(32-y16);y<(192+32);y+=16){
   for(x=(32-x16);x<(256+32);x+=16){

      ta = RAM_BG0[zz+0] | bg_map[RAM_BG0[zz+1]>>4];

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG0[zz+1]&0x0F)|mask_bg0,
            16,
            map
         );

         Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);

   zz+=2;
   if((zz&0x1F)==0){zz+=0x3E0;zz&=0x7FF;}
   }
   zzzz+=0x20;
   if((zzzz&0x3E0)==0){zzzz-=0x400;}
   zzzz&=0x7FF;
   zz=zzzz;
   }

   }

   // BG1
   // ---

   if(RAM_BG1!=NULL){

   zzz=(ReadWord(&SCR_BG1[0]));
   zzzz =((zzz&0x00F0)>>4)<<1;                  // X Offset (16-255)
   zzzz+=((zzz&0x0100)>>4)<<6;                  // X Offset (256-511)
   x16=zzz&15;                                  // X Offset (0-15)
   zzz=(ReadWord(&SCR_BG1[2])+32);
   zzzz+=((zzz&0x01F0)>>4)<<5;                  // Y Offset (16-511)
   y16=zzz&15;                                  // Y Offset (0-15)

   zzzz=zzzz&0x7FF;
   zz=zzzz;
   for(y=(32-y16);y<(192+32);y+=16){
   for(x=(32-x16);x<(256+32);x+=16){

      ta = RAM_BG1[zz+0] | bg_map[RAM_BG1[zz+1]>>4];
      if(BG1_Mask[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG1[zz+1]&0x0F)|mask_bg1,
            16,
            map
         );

         if(BG1_Mask[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map);
         }
         else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map);
         }

      }

   zz+=2;
   if((zz&0x1F)==0){zz+=0x3E0;zz&=0x7FF;}
   }
   zzzz+=0x20;
   if((zzzz&0x3E0)==0){zzzz-=0x400;}
   zzzz&=0x7FF;
   zz=zzzz;
   }

   }

   // BG2
   // ---

   if(RAM_BG2!=NULL){

   zzz=(ReadWord(&SCR_BG2[0]));
   zzzz =((zzz&0x00F0)>>4)<<1;                  // X Offset (16-255)
   zzzz+=((zzz&0x0100)>>4)<<6;                  // X Offset (256-511)
   x16=zzz&15;                                  // X Offset (0-15)
   zzz=(ReadWord(&SCR_BG2[2])+32);
   zzzz+=((zzz&0x01F0)>>4)<<5;                  // Y Offset (16-511)
   y16=zzz&15;                                  // Y Offset (0-15)

   zzzz=zzzz&0x7FF;
   zz=zzzz;
   for(y=(32-y16);y<(192+32);y+=16){
   for(x=(32-x16);x<(256+32);x+=16){

      ta = RAM_BG2[zz+0] | bg_map[RAM_BG2[zz+1]>>4];
      if(BG2_Mask[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG2[zz+1]&0x0F)|mask_bg2,
            16,
            map
         );

         if(BG2_Mask[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG2[ta<<8], x, y, map);
         }
         else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG2[ta<<8], x, y, map);
         }

      }

   zz+=2;
   if((zz&0x1F)==0){zz+=0x3E0;zz&=0x7FF;}
   }
   zzzz+=0x20;
   if((zzzz&0x3E0)==0){zzzz-=0x400;}
   zzzz&=0x7FF;
   zz=zzzz;
   }

   }

   // OBJECT
   // ------

   for(zz=0x0000;zz<0x0600;zz+=16){

      if((RAM_SPR[zz+0x0D]&2)!=0){

      x = (32 + RAM_SPR[zz+0x0C] + ((RAM_SPR[zz+0x0D]<<8)&0x0100))&0x1FF;
      y = ( 0 + RAM_SPR[zz+0x0B])&0x0FF;

      ta = RAM_SPR[zz+0x0E] | ((RAM_SPR[zz+0x0D]<<2)&0x0300) | ((RAM_SPR[zz+0x0D]<<7)&0x0400);

      MAP_PALETTE_MAPPED_NEW(
         (RAM_SPR[zz+0x0F]&0x0F)|mask_spr,
         16,
         map
      );

      if((RAM_SPR[zz+0x0D]&4)!=0){
         switch(RAM_SPR[zz+0x0D]&0x30){
         case 0x00:

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y+16)&0xFF;
         }while(--xx);

         x=(x+16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         case 0x10:

         x+=16;

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipY_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y+16)&0xFF;
         }while(--xx);

         x=(x-16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         case 0x20:

         y+=16;

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipX_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y-16)&0xFF;
         }while(--xx);

         x=(x+16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         case 0x30:

         x+=16;
         y+=16;

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipXY_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y-16)&0xFF;
         }while(--xx);

         x=(x-16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         }

      }
      else{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1){				// Some pixels; trans
            switch(RAM_SPR[zz+0x0D]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_SPR[zz+0x0D]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }

         }
         }

      }

      }

   }

   // FG0
   // ---

   MAKE_SCROLL_256x256_2_8(
       0,
       32
   );

   START_SCROLL_256x256_2_8(32,32,256,192);

      ta = RAM_FG0[0+zz] | ((RAM_FG0[1+zz]<<2)&0x0300);
      if(FG0_Mask[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_FG0[1+zz]&0x0F)|mask_fg0,
            16,
            map
         );

         if(FG0_Mask[ta]==1){				// Some pixels; trans
            switch(RAM_FG0[1+zz]&0x30){
            case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);        break;
            case 0x10: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x20: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x30: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_FG0[ta<<6], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_FG0[1+zz]&0x30){
            case 0x00: Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);        break;
            case 0x10: Draw8x8_Mapped_FlipY_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x20: Draw8x8_Mapped_FlipX_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x30: Draw8x8_Mapped_FlipXY_Rot(&GFX_FG0[ta<<6], x, y, map); break;
            }
         }
      }

   END_SCROLL_256x256_2_8();
}

/*

nnhv.????.nnnn.nnnn

*/
static struct VIDEO_INFO video_robokid =
{
   DrawRoboKid,
   256,
   192,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_robokid[] =
{
   { "atomic_robo_kid", },
   { "robokid", },
   { NULL, },
};
GME( robokid, "Atomic Robo Kid", UPL, 1988, GAME_SHOOT,
	.long_name_jpn = "アトミックロボキッド",
	.board = "UPL-88013",
);
static struct DIR_INFO dir_robokidj[] =
{
   { "atomic_robo_kid_japanese", },
   { "robokidj", },
   { ROMOF("robokid"), },
   { CLONEOF("robokid"), },
   { NULL, },
};
CLNE( robokidj,robokid, "Atomic Robo Kid Japanese", UPL, 1988, GAME_SHOOT,
	.long_name_jpn = "アトミックロボキッド",
	.board = "UPL-88013",
);

