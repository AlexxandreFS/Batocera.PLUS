#define DRV_DEF_SOUND technos_ym2151_m6295_sound
/******************************************************************************/
/*                                                                            */
/*                  WWF SUPER STARS (C) 1989 TECHNOS JAPAN                    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tchnosnd.h"
#include "sasound.h"		// sample support routines


static struct ROM_INFO rom_wwfsstar[] =
{
   {   "wwfs43.bin", 0x00010000, 0xaafc4a38, 0, 0, 0, },
   {   "24ac-04.34", 0x00020000, 0xee9b850e, 0, 0, 0, },
   {   "24ad-04.35", 0x00020000, 0x057c2eef, 0, 0, 0, },
   {      "24a9.46", 0x00020000, 0x703ff08f, 0, 0, 0, },
   {    "24a4-0.58", 0x00020000, 0xcb12ba40, 0, 0, 0, },
   {   "wwfs03.bin", 0x00010000, 0x8a35a20e, 0, 0, 0, },
   {   "wwfs05.bin", 0x00010000, 0x6df08962, 0, 0, 0, },
   {   "wwfs12.bin", 0x00010000, 0x242caff5, 0, 0, 0, },
   {   "wwfs13.bin", 0x00010000, 0x970b6e76, 0, 0, 0, },
   {   "wwfs14.bin", 0x00010000, 0x67eb7bea, 0, 0, 0, },
   {   "wwfs15.bin", 0x00010000, 0xaac5a928, 0, 0, 0, },
   {   "wwfs16.bin", 0x00010000, 0x08343e7f, 0, 0, 0, },
   {   "wwfs17.bin", 0x00010000, 0xef12069f, 0, 0, 0, },
   {   "wwfs18.bin", 0x00010000, 0xaf11ad2a, 0, 0, 0, },
   {   "wwfs19.bin", 0x00010000, 0x7426d444, 0, 0, 0, },
   {   "wwfs20.bin", 0x00010000, 0xb2a8050e, 0, 0, 0, },
   {   "wwfs21.bin", 0x00010000, 0xc52eee5e, 0, 0, 0, },
   {   "wwfs22.bin", 0x00010000, 0x81fe1bf7, 0, 0, 0, },
   {   "wwfs23.bin", 0x00010000, 0x681f5b5e, 0, 0, 0, },
   {   "wwfs24.bin", 0x00010000, 0x76b08bcd, 0, 0, 0, },
   {   "wwfs25.bin", 0x00010000, 0xbbf69c6a, 0, 0, 0, },
   {   "wwfs26.bin", 0x00010000, 0x2ca91eaf, 0, 0, 0, },
   {   "wwfs27.bin", 0x00010000, 0xf3eb8ab9, 0, 0, 0, },
   {   "wwfs28.bin", 0x00010000, 0x70fda626, 0, 0, 0, },
   {   "wwfs29.bin", 0x00010000, 0x7b5b9d83, 0, 0, 0, },
   {   "wwfs30.bin", 0x00010000, 0x94094518, 0, 0, 0, },
   {   "wwfs31.bin", 0x00010000, 0xf94c74d5, 0, 0, 0, },
   {   "wwfs32.bin", 0x00010000, 0x9becd621, 0, 0, 0, },
   {   "wwfs33.bin", 0x00010000, 0xf6923db6, 0, 0, 0, },
   {   "wwfs34.bin", 0x00010000, 0x742a79db, 0, 0, 0, },
   {   "wwfs35.bin", 0x00010000, 0x9d648d82, 0, 0, 0, },
   {   "wwfs36.bin", 0x00010000, 0x9005e942, 0, 0, 0, },
   {   "wwfs37.bin", 0x00010000, 0x5e8d7407, 0, 0, 0, },
   {   "wwfs38.bin", 0x00010000, 0xd8ea94d3, 0, 0, 0, },
   {   "wwfs39.bin", 0x00010000, 0xd807b09a, 0, 0, 0, },
   {   "wwfs40.bin", 0x00010000, 0x4d75fd89, 0, 0, 0, },
   {   "wwfs41.bin", 0x00010000, 0xed7f69d5, 0, 0, 0, },
   {   "wwfs42.bin", 0x00010000, 0xe48b88fb, 0, 0, 0, },
   {         "b.12", 0x00008000, 0x1e44f8aa, 0, 0, 0, },
   {   "wwfs44.bin", 0x00010000, 0x4f965fa9, 0, 0, 0, },
   {   "wwfs45.bin", 0x00010000, 0xb2fad792, 0, 0, 0, },
   {   "wwfs46.bin", 0x00010000, 0x985e5180, 0, 0, 0, },
   {   "wwfs47.bin", 0x00010000, 0x6fd7b6ea, 0, 0, 0, },
   {   "wwfs48.bin", 0x00010000, 0x251372fd, 0, 0, 0, },
   {   "wwfs49.bin", 0x00010000, 0xa14076b0, 0, 0, 0, },
   {   "wwfs50.bin", 0x00010000, 0x7fc79df5, 0, 0, 0, },
   {   "wwfs51.bin", 0x00010000, 0x51157385, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_wwfsstar[] =
{
   INP0( COIN1, 0x014008, 0x02 ),
   INP0( COIN2, 0x014008, 0x04 ),
   INP0( SERVICE, 0x014008, 0x08 ),

   { KB_DEF_P1_START,     "1P VS CPU - Power Up",  0x014004, 0x80, BIT_ACTIVE_0 },
   { KB_DEF_P2_START,     "1P VS 2P - Buy-in",     0x014006, 0x80, BIT_ACTIVE_0 },
   { KB_DEF_P3_START,     "1P/2P VS CPU",          0x014006, 0x40, BIT_ACTIVE_0 },

   INP0( P1_UP, 0x014004, 0x04 ),
   INP0( P1_DOWN, 0x014004, 0x08 ),
   INP0( P1_LEFT, 0x014004, 0x02 ),
   INP0( P1_RIGHT, 0x014004, 0x01 ),
   INP0( P1_B1, 0x014004, 0x10 ),
   INP0( P1_B2, 0x014004, 0x20 ),

   INP0( P2_UP, 0x014006, 0x04 ),
   INP0( P2_DOWN, 0x014006, 0x08 ),
   INP0( P2_LEFT, 0x014006, 0x02 ),
   INP0( P2_RIGHT, 0x014006, 0x01 ),
   INP0( P2_B1, 0x014006, 0x10 ),
   INP0( P2_B2, 0x014006, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_wwf_super_stars_0[] =
{
   { MSG_COIN1,               0x07, 0x08 },
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_3COIN_1PLAY,         0x01},
   { MSG_2COIN_1PLAY,         0x02},
   { MSG_1COIN_1PLAY,         0x07},
   { MSG_1COIN_2PLAY,         0x06},
   { MSG_1COIN_3PLAY,         0x05},
   { MSG_1COIN_4PLAY,         0x04},
   { MSG_1COIN_5PLAY,         0x03},
   { MSG_COIN2,               0x38, 0x08 },
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_3COIN_1PLAY,         0x08},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_1COIN_1PLAY,         0x38},
   { MSG_1COIN_2PLAY,         0x30},
   { MSG_1COIN_3PLAY,         0x28},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_1COIN_5PLAY,         0x18},
   DSW_UNUSED( 0x00, 0x40),
   DSW_SCREEN( 0x80, 0x00),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_wwf_super_stars_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x01},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x02},
   { MSG_HARDEST,             0x00},
   DSW_DEMO_SOUND( 0x04, 0x00),
   { _("Super Techniques"),      0x08, 0x02 },
   { MSG_NORMAL,              0x08},
   { MSG_HARD,                0x00},
   { _("Game Time"),             0x30, 0x04 },
   { "+2:30",                 0x20},
   { _("Default"),               0x30},
   { "-2:30",                 0x10},
   { "-5:00",                 0x00},
   DSW_UNUSED( 0x00, 0x40),
   { _("Health For Winning"),    0x80, 0x02 },
   { MSG_NO,                  0x80},
   { MSG_YES,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_wwfsstar[] =
{
   { 0x014000, 0xFF, dsw_data_wwf_super_stars_0 },
   { 0x014002, 0x7F, dsw_data_wwf_super_stars_1 },
   { 0,        0,    NULL,      },
};



static UINT8 *GFX_BG0_SOLID;
static UINT8 *GFX_SPR_SOLID;
static UINT8 *GFX_FG0_SOLID;

static void WriteOutByte(UINT32 address, UINT8 data)
{
   address&=0x0F;
   RAM[(0x14010+address)^1]=data;

   if(address==9) TechnosSoundWrite68k(address,data);
}

static void WriteOutWord(UINT32 address, UINT16 data)
{
   address&=0x0F;
   WriteWord(&RAM[0x14010+address],data);

   if(address==8) TechnosSoundWrite68k(address, (UINT8) (data&0xFF));
}

static void WWFSuperStarsSpeedPatch(void)
{
   int address;

   for(address=0;address<0x40000-8;address+=2){
   if(ROM[address+0]==0x08){
   if(ROM[address+1]==0x39){
   if(ROM[address+2]==0x00){
   if(ROM[address+3]==0x00){
   if(ROM[address+4]==0x00){
   if(ROM[address+5]==0x18){
   if(ROM[address+6]==0x00){
   if(ROM[address+7]==0x09){

   if(ROM[address+8]==0x66){

   WriteLong68k(&ROM[address+0],0x13FC0000);
   WriteLong68k(&ROM[address+4],0x00AA0000);
   WriteWord68k(&ROM[address+8],0x4E71);

   }
   else{

   WriteLong68k(&ROM[address+0],0x4E714E71);
   WriteLong68k(&ROM[address+4],0x4E714E71);
   WriteWord68k(&ROM[address+8],0x4E71);

   }

   }}}}}}}}
   }

   WriteLong68k(&ROM[0x0F6A+0],0x4E714E71);
   WriteLong68k(&ROM[0x0F6A+4],0x4E714E71);
   WriteWord68k(&ROM[0x0F6A+8],0x4E71);
}

static void load_wwfsstar(void)
{
   int ta,tb,tc,td,te;

   RAMSize=0x40000+0x10000;

   if(!(ROM=AllocateMem(0x40000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x540000))) return;

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("b.12", Z80ROM, 0x8000)) return;	// Z80 SOUND ROM

   Z80ROM[0x0122]=0x01;
   Z80ROM[0x0121]=0x2A;

   Z80ROM[0x0163]=0xC9;

   if(!(PCMROM = AllocateMem(0x40000))) return;
   if(!load_rom(   "24a9.46",PCMROM+0x00000,0x20000)) return;	// ADPCM ROM <temp>
   if(!load_rom("wwfs03.bin",PCMROM+0x20000,0x10000)) return;	// ADPCM ROM <temp>
   if(!load_rom("wwfs05.bin",PCMROM+0x30000,0x10000)) return;	// ADPCM ROM <temp>

   AddTechnosSoundOld(0x012A, 0x0100, 0x8000, PCMROM, 160);

   /*---------------------------------*/

   if(!load_rom("24a4-0.58", RAM+0x00000, 0x20000)) return;		// 8x8 FG0 TILES
   tb=0;
   for(ta=0;ta<0x20000;ta+=32){
      for(td=0;td<8;td+=2){
      for(te=0;te<8;te++){
      tc=RAM[ta+(td<<2)+te];
      GFX[tb+1+td+(te<<3)]=(((tc&0x80)>>7)<<3);
      GFX[tb+0+td+(te<<3)]=(((tc&0x40)>>6)<<3);
      GFX[tb+1+td+(te<<3)]|=(((tc&0x20)>>5)<<2);
      GFX[tb+0+td+(te<<3)]|=(((tc&0x10)>>4)<<2);
      GFX[tb+1+td+(te<<3)]|=(((tc&0x08)>>3)<<1);
      GFX[tb+0+td+(te<<3)]|=(((tc&0x04)>>2)<<1);
      GFX[tb+1+td+(te<<3)]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0+td+(te<<3)]|=(((tc&0x01)>>0)<<0);
      }
      }
      tb+=64;
   }

   tb=0x40000;
   if(!load_rom("wwfs27.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs26.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs25.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs24.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=(((tc&0x80)>>7)<<3);
      GFX[tb+2]=(((tc&0x40)>>6)<<3);
      GFX[tb+1]=(((tc&0x20)>>5)<<3);
      GFX[tb+0]=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x40000;
   if(!load_rom("wwfs39.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs38.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs37.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs36.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]|=(((tc&0x80)>>7)<<1);
      GFX[tb+2]|=(((tc&0x40)>>6)<<1);
      GFX[tb+1]|=(((tc&0x20)>>5)<<1);
      GFX[tb+0]|=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x140000;
   if(!load_rom("wwfs23.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs22.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs21.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs20.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=(((tc&0x80)>>7)<<3);
      GFX[tb+2]=(((tc&0x40)>>6)<<3);
      GFX[tb+1]=(((tc&0x20)>>5)<<3);
      GFX[tb+0]=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x140000;
   if(!load_rom("wwfs43.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs42.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs41.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs40.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]|=(((tc&0x80)>>7)<<1);
      GFX[tb+2]|=(((tc&0x40)>>6)<<1);
      GFX[tb+1]|=(((tc&0x20)>>5)<<1);
      GFX[tb+0]|=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x240000;
   if(!load_rom("wwfs35.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs34.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs33.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs32.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=(((tc&0x80)>>7)<<3);
      GFX[tb+2]=(((tc&0x40)>>6)<<3);
      GFX[tb+1]=(((tc&0x20)>>5)<<3);
      GFX[tb+0]=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x240000;
   if(!load_rom("wwfs19.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs18.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs17.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs16.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]|=(((tc&0x80)>>7)<<1);
      GFX[tb+2]|=(((tc&0x40)>>6)<<1);
      GFX[tb+1]|=(((tc&0x20)>>5)<<1);
      GFX[tb+0]|=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x340000;
   if(!load_rom("wwfs31.bin", RAM+0x00000, 0x10000)) return;		// *
   if(!load_rom("wwfs30.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs29.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs28.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=(((tc&0x80)>>7)<<3);
      GFX[tb+2]=(((tc&0x40)>>6)<<3);
      GFX[tb+1]=(((tc&0x20)>>5)<<3);
      GFX[tb+0]=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x340000;
   if(!load_rom("wwfs15.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs14.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs13.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs12.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]|=(((tc&0x80)>>7)<<1);
      GFX[tb+2]|=(((tc&0x40)>>6)<<1);
      GFX[tb+1]|=(((tc&0x20)>>5)<<1);
      GFX[tb+0]|=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x440000;
   if(!load_rom("wwfs47.bin", RAM+0x00000, 0x10000)) return;		// 16x16 BG0 TILES
   if(!load_rom("wwfs46.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs45.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs44.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=(((tc&0x80)>>7)<<3);
      GFX[tb+2]=(((tc&0x40)>>6)<<3);
      GFX[tb+1]=(((tc&0x20)>>5)<<3);
      GFX[tb+0]=(((tc&0x10)>>4)<<3);
      GFX[tb+3]|=(((tc&0x08)>>3)<<2);
      GFX[tb+2]|=(((tc&0x04)>>2)<<2);
      GFX[tb+1]|=(((tc&0x02)>>1)<<2);
      GFX[tb+0]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   tb=0x440000;
   if(!load_rom("wwfs51.bin", RAM+0x00000, 0x10000)) return;
   if(!load_rom("wwfs50.bin", RAM+0x10000, 0x10000)) return;
   if(!load_rom("wwfs49.bin", RAM+0x20000, 0x10000)) return;
   if(!load_rom("wwfs48.bin", RAM+0x30000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]|=(((tc&0x80)>>7)<<1);
      GFX[tb+2]|=(((tc&0x40)>>6)<<1);
      GFX[tb+1]|=(((tc&0x20)>>5)<<1);
      GFX[tb+0]|=(((tc&0x10)>>4)<<1);
      GFX[tb+3]|=(((tc&0x08)>>3)<<0);
      GFX[tb+2]|=(((tc&0x04)>>2)<<0);
      GFX[tb+1]|=(((tc&0x02)>>1)<<0);
      GFX[tb+0]|=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xFC;}
      else{if((tb&0xFF)==4){tb-=0xFC;}
      else{if((tb&0xFF)==8){tb-=0xFC;}
      else{if((tb&0xFF)==12){tb-=12;}}}}
   }

   GFX_FG0_SOLID = make_solid_mask_8x8  (GFX + 0x000000, 0x1000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX + 0x040000, 0x4000);
   GFX_BG0_SOLID = make_solid_mask_16x16(GFX + 0x440000, 0x1000);

   if(!load_rom("24ac-04.34", RAM, 0x20000)) return;		// MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("24ad-04.35", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   memset(RAM+0x00000,0xFF,0x40000);

   InitPaletteMap(RAM+0x13000, 0x18, 0x10, 0x1000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);

   WWFSuperStarsSpeedPatch();
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x1C0000, 0x1CFFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x080000, 0x080FFF, NULL, RAM+0x010000);			// FG0 RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);			// BG0 RAM
   AddReadByte(0x100000, 0x100FFF, NULL, RAM+0x012000);			// OBJECT RAM
   AddReadByte(0x140000, 0x140FFF, NULL, RAM+0x013000);			// COLOR RAM
   AddReadByte(0x180000, 0x18000F, NULL, RAM+0x014000);			// INPUTS
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x1C0000, 0x1CFFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x080000, 0x080FFF, NULL, RAM+0x010000);			// FG0 RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);			// BG0 RAM
   AddReadWord(0x100000, 0x100FFF, NULL, RAM+0x012000);			// OBJECT RAM
   AddReadWord(0x140000, 0x140FFF, NULL, RAM+0x013000);			// COLOR RAM
   AddReadWord(0x180000, 0x18000F, NULL, RAM+0x014000);			// INPUTS
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x1C0000, 0x1CFFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x080000, 0x080FFF, NULL, RAM+0x010000);		// FG0 RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);		// BG0 RAM
   AddWriteByte(0x100000, 0x100FFF, NULL, RAM+0x012000);		// OBJECT RAM
   AddWriteByte(0x140000, 0x140FFF, NULL, RAM+0x013000);		// COLOR RAM
   AddWriteByte(0x180000, 0x18000F, WriteOutByte, NULL);		// OUTPUTS
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x1C0000, 0x1CFFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x080000, 0x080FFF, NULL, RAM+0x010000);		// FG0 RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);		// BG0 RAM
   AddWriteWord(0x100000, 0x100FFF, NULL, RAM+0x012000);		// OBJECT RAM
   AddWriteWord(0x140000, 0x140FFF, NULL, RAM+0x013000);		// COLOR RAM
   AddWriteWord(0x180000, 0x18000F, WriteOutWord, NULL);		// OUTPUTS
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_wwfsstar(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 6);

   TechnosSoundOld_Frame();		// Z80; YM2151; OKI ADPCM
}

static void DrawWWFSuperStars(void)
{
   int x,y,ta;
   int zz,zzz,zzzz,x16,y16;
   int td,zx,zy,zxx;
   UINT8 *map;

   ClearPaletteMap();

   zzz=ReadWord(&RAM[0x14014]);
   zzzz=((zzz&0x1F0)>>4)<<2;			// X Offset (16-511)
   x16=zzz&15;					// X Offset (0-15)
   zx=zzzz&0x007F;

   zzz=ReadWord(&RAM[0x14016]);
   zzzz=((zzz&0x1F0)>>4)<<6;			// Y Offset (16-511)
   y16=zzz&15;					// Y Offset (0-15)
   zy=zzzz&0x07FF;

   for(y=32-y16;y<256+32;y+=16){
   zxx=zx;
      for(x=32-x16;x<256+32;x+=16){
         zz=0x11000+((zy&0x3FF)|(zxx&0x3F));			// Build offset
         zz+=(zxx&0x0040)<<4;
         zz+=(zy&0x0400)<<1;

         MAP_PALETTE_MAPPED_NEW(
            ((RAM[zz]>>4)&7)|0x10,
            16,
            map
         );

         if((RAM[zz]&0x80)==0){
            Draw16x16_Mapped_Rot(&GFX[0x440000+((((RAM[zz]<<8)|(RAM[zz+2]))&0xFFF)<<8)],x,y,map);
         }
         else{
            Draw16x16_Mapped_FlipY_Rot(&GFX[0x440000+((((RAM[zz]<<8)|(RAM[zz+2]))&0xFFF)<<8)],x,y,map);
         }
         zxx+=4;
         zxx&=0x7F;
      }
   zy+=0x40;
   zy&=0x7FF;
   }

   for(zz=0x12000;zz<0x12400;zz+=10){

      td=RAM[zz+2];

      if((td&0x01)!=0){

      x=((td&0x08)<<5)|(RAM[zz+8]);
      x=((256+16)-x)&0x1FF;

      y=((td&0x04)<<6)|(RAM[zz+0]);
      y=((256+16)-y)&0x1FF;

      if((x>16)&&(x<256+32)){

         ta=((RAM[zz+4]<<8)|(RAM[zz+6]))&0x3FFF;

         MAP_PALETTE_MAPPED_NEW(
            (td>>4)+8,
            16,
            map
         );

         if((td&0x02)==0){

         if((y>16)&&(y<256+32)){

         switch(RAM[zz+4]&0xC0){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map);        break;
            case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map);  break;
            case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map);  break;
            case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map); break;
         }

         }

         }
         else{

         ta &= 0x3FFE;

         if((y>16)&&(y<256+32)){

         switch(RAM[zz+4]&0xC0){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[0x40000+((ta+1)<<8)],x,y,map);        break;
            case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[0x40000+((ta+1)<<8)],x,y,map);  break;
            case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map);  break;
            case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map); break;
         }

         }

         y=(y-16)&0x1FF;

         if((y>16)&&(y<256+32)){

         switch(RAM[zz+4]&0xC0){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map);        break;
            case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[0x40000+((ta+0)<<8)],x,y,map);  break;
            case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[0x40000+((ta+1)<<8)],x,y,map);  break;
            case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[0x40000+((ta+1)<<8)],x,y,map); break;
         }

         }

         }

      }

      }
   }

   zz=0x10000;
   for(y=32;y<256+32;y+=8){
   for(x=32;x<256+32;x+=8){

      ta=((RAM[zz]<<8)|(RAM[zz+2]))&0xFFF;
      if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            RAM[zz]>>4,
            16,
            map
         );

         Draw8x8_Trans_Mapped_Rot(&GFX[ta<<6],x,y,map);
      }
      zz+=4;
   }
   }
}

/*

WWF SUPERSTARS (C) 1989 TECHNOS
-------------------------------

Main CPU....68000
Sound CPUs..Z80; YM2151; M6295

Sprite RAM
----------

- 10 bytes/sprite entry.
- Even bytes unused, so just 5 bytes/sprite
  entry.
- Sprites are 16x16.
- Chain Y bit allows drawing of 2 sprites
  per entry (ie. to give a 16x32).

Byte | Bit(s) | Description
-----+76543210+----------------------
  0  |........| <Unused>
  1  |xxxxxxxx| Sprite Y (low)
  2  |........| <Unused>
  3  |.......x| Sprite Enable
  3  |......x.| Chain Y (16x32)
  3  |.....x..| Sprite Y (high)
  3  |....x...| Sprite X (high)
  3  |xxxx....| Colour Bank
  4  |........| <Unused>
  5  |.x......| Flip X Axis
  5  |x.......| Flip Y Axis
  5  |..xxxxxx| Sprite Number (high)
  6  |........| <Unused>
  7  |xxxxxxxx| Sprite Number (low)
  8  |........| <Unused>
  9  |xxxxxxxx| Sprite X (low)


Colour RAM
----------

- 24 banks of 16 colours.

Banks | Usage
------+--------------------
 0-15 | FG0 Layer
 8-23 | Sprites
16-23 | BG0 Layer


FileName   | Description
-----------+---------------------------------
WWFS01.BIN | Z80 ROM
WWFS02.BIN | ADPCM Sampledata (block#1)
WWFS03.BIN | ADPCM Sampledata (block#3)
WWFS04.BIN | ADPCM Sampledata (block#2)
WWFS05.BIN | ADPCM Sampledata (block#4)
WWFS06.BIN | 8x8 FG0 GFX (block#1)
WWFS07.BIN | 68000 ROM (block#1) (odd)
WWFS08.BIN | 68000 ROM (block#1) (even)
WWFS09.BIN | 68000 ROM (block#2) (odd)
WWFS10.BIN | 68000 ROM (block#2) (even)
WWFS11.BIN | 8x8 FG0 GFX (block#2)
WWFS12.BIN | 16x16 SPRITES (block#1a)
WWFS13.BIN | 16x16 SPRITES (block#2a)
WWFS14.BIN | 16x16 SPRITES (block#3a)
WWFS15.BIN | 16x16 SPRITES (block#4a)
WWFS16.BIN | 16x16 SPRITES (block#5a)
WWFS17.BIN | 16x16 SPRITES (block#6a)
WWFS18.BIN | 16x16 SPRITES (block#7a)
WWFS19.BIN | 16x16 SPRITES (block#8a)
WWFS20.BIN | 16x16 SPRITES (block#9a)
WWFS21.BIN | 16x16 SPRITES (block#10a)
WWFS22.BIN | 16x16 SPRITES (block#11a)
WWFS23.BIN | 16x16 SPRITES (block#12a)
WWFS24.BIN | 16x16 SPRITES (block#13a)
WWFS25.BIN | 16x16 SPRITES (block#14a)
WWFS26.BIN | 16x16 SPRITES (block#15a)
WWFS27.BIN | 16x16 SPRITES (block#16a)
WWFS28.BIN | 16x16 SPRITES (block#1b)
WWFS29.BIN | 16x16 SPRITES (block#2b)
WWFS30.BIN | 16x16 SPRITES (block#3b)
WWFS31.BIN | 16x16 SPRITES (block#4b)
WWFS32.BIN | 16x16 SPRITES (block#9b)
WWFS33.BIN | 16x16 SPRITES (block#10b)
WWFS34.BIN | 16x16 SPRITES (block#11b)
WWFS35.BIN | 16x16 SPRITES (block#12b)
WWFS36.BIN | 16x16 SPRITES (block#5b)
WWFS37.BIN | 16x16 SPRITES (block#6b)
WWFS38.BIN | 16x16 SPRITES (block#7b)
WWFS39.BIN | 16x16 SPRITES (block#8b)
WWFS40.BIN | 16x16 SPRITES (block#13b)
WWFS41.BIN | 16x16 SPRITES (block#14b)
WWFS42.BIN | 16x16 SPRITES (block#15b)
WWFS43.BIN | 16x16 SPRITES (block#16b)
WWFS44.BIN | 16x16 BG0 TILES (block#4a)
WWFS45.BIN | 16x16 BG0 TILES (block#3a)
WWFS46.BIN | 16x16 BG0 TILES (block#2a)
WWFS47.BIN | 16x16 BG0 TILES (block#1a)
WWFS48.BIN | 16x16 BG0 TILES (block#4b)
WWFS49.BIN | 16x16 BG0 TILES (block#3b)
WWFS50.BIN | 16x16 BG0 TILES (block#2b)
WWFS51.BIN | 16x16 BG0 TILES (block#1b)

*/
static struct VIDEO_INFO video_wwfsstar =
{
   DrawWWFSuperStars,
   256,
   256,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_wwfsstar[] =
{
   { "wwf_super_stars", },
   { "wwfsstar", },
   { "wwfsstau", },
   { NULL, },
};
GME( wwfsstar, "WWF Superstars", TECHNOS, 1989, GAME_BEAT,
	.long_name_jpn = "ＷＷＦスーパースターズ",
	.board = "TA-0024",
);

