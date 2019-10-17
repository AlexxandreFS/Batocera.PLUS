#define DRV_DEF_SOUND technos_ym2151_m6295_sound
/******************************************************************************/
/*                                                                            */
/*                    WRESTLEFEST (C) 1991 TECHNOS JAPAN                      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "tchnosnd.h"
#include "adpcm.h"
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_wwfwfsta[] =
{
   {   "wf_73a.rom", 0x00080000, 0x6c522edb, 0, 0, 0, },
   {    "31a11-2.42", 0x00010000, 0x5ddebfea, 0, 0, 0, },
   {    "wf_33.rom", 0x00020000, 0x06f22615, 0, 0, 0, },
   {    "wf_19.rom", 0x00040000, 0xbd02e3c4, 0, 0, 0, },
   {    "wf_18.rom", 0x00040000, 0x933ea1a0, 0, 0, 0, },
   {    "wf_15.rom", 0x00100000, 0xdd387289, 0, 0, 0, },
   {    "wf_14.rom", 0x00100000, 0x44abe127, 0, 0, 0, },
   {    "wf_13.rom", 0x00100000, 0x74d774c3, 0, 0, 0, },
   {    "wf_12.rom", 0x00100000, 0x79956cf8, 0, 0, 0, },
   {    "wf_11.rom", 0x00100000, 0x2ce545e8, 0, 0, 0, },
   {    "wf_10.rom", 0x00100000, 0x00edb66a, 0, 0, 0, },
   {    "wf_09.rom", 0x00100000, 0xe395cf1d, 0, 0, 0, },
   {    "wf_08.rom", 0x00100000, 0xb5a97465, 0, 0, 0, },
   {    "wf_02.rom", 0x00040000, 0x82ed7155, 0, 0, 0, },
   {    "wf_01.rom", 0x00040000, 0x8a12b450, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_wwfwfsta[] =
{
   INP0( COIN1, 0x01C021, 0x01 ),
   INP0( COIN2, 0x01C021, 0x02 ),

   INP0( P1_START, 0x01C020, 0x80 ),
   INP0( P1_UP, 0x01C020, 0x04 ),
   INP0( P1_DOWN, 0x01C020, 0x08 ),
   INP0( P1_LEFT, 0x01C020, 0x02 ),
   INP0( P1_RIGHT, 0x01C020, 0x01 ),
   INP0( P1_B1, 0x01C020, 0x10 ),
   INP0( P1_B2, 0x01C020, 0x20 ),

   INP0( P2_START, 0x01C022, 0x80 ),
   INP0( P2_UP, 0x01C022, 0x04 ),
   INP0( P2_DOWN, 0x01C022, 0x08 ),
   INP0( P2_LEFT, 0x01C022, 0x02 ),
   INP0( P2_RIGHT, 0x01C022, 0x01 ),
   INP0( P2_B1, 0x01C022, 0x10 ),
   INP0( P2_B2, 0x01C022, 0x20 ),

   INP0( P3_START, 0x01C024, 0x80 ),
   INP0( P3_UP, 0x01C024, 0x04 ),
   INP0( P3_DOWN, 0x01C024, 0x08 ),
   INP0( P3_LEFT, 0x01C024, 0x02 ),
   INP0( P3_RIGHT, 0x01C024, 0x01 ),
   INP0( P3_B1, 0x01C024, 0x10 ),
   INP0( P3_B2, 0x01C024, 0x20 ),

   INP0( P4_START, 0x01C026, 0x80 ),
   INP0( P4_UP, 0x01C026, 0x04 ),
   INP0( P4_DOWN, 0x01C026, 0x08 ),
   INP0( P4_LEFT, 0x01C026, 0x02 ),
   INP0( P4_RIGHT, 0x01C026, 0x01 ),
   INP0( P4_B1, 0x01C026, 0x10 ),
   INP0( P4_B2, 0x01C026, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_wrestle_fest_0[] =
{
   { MSG_COINAGE,             0x03, 0x04 },
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_1COIN_2PLAY,         0x02},
   { _("Buy In Price"),          0x04, 0x02 },
   { _("1 Coin"),                0x04},
   { _("As Start Price"),        0x00},
   { _("Regain Power Price"),    0x08, 0x02 },
   { _("1 Coin"),                0x08},
   { _("As Start Price"),        0x00},
   { _("Continue Price"),        0x10, 0x02 },
   { _("1 Coin"),                0x10},
   { _("As Start Price"),        0x00},
   DSW_DEMO_SOUND( 0x20, 0x00),
   DSW_SCREEN( 0x40, 0x00),
   { _("FBI Logo"),              0x80, 0x02 },
   { MSG_YES,                 0x80},
   { MSG_NO,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_wrestle_fest_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_UNKNOWN,             0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_CABINET, 0x08, 2 },
   { _("4 Players"), 0x08 },
   { _("2 Players"), 0x00 },
   DSW_UNUSED( 0x00, 0x10),
   { _("Health For Winning"),    0x60, 0x04 },
   { "0",                     0x00},
   { "12",                    0x20},
   { "24",                    0x60},
   { "32",                    0x40},
   { _("Championship Games"),    0x80, 0x02 },
   { "5",                     0x80},
   { "4",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_wwfwfsta[] =
{
   { 0x01C07E, 0xFF, dsw_data_wrestle_fest_0 },
   { 0x01C07F, 0xFF, dsw_data_wrestle_fest_1 },
   { 0,        0,    NULL,      },
};



static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_SPR;
static UINT8 *RAM_FG0;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *GFX_FG0;
static UINT8 *GFX_FG0_SOLID;

static int layer_id_data[4];

static char *layer_id_name[4] =
{
   "BG0", "BG1", "FG0", "OBJECT",
};

static void wf_colour_ram_wb(UINT32 address, UINT8 data)
{
   WriteByte(RAM + 0x0C000 + ((address & 0xFF80) >> 2) + ((address & 0x1F) ^ 1), data);
}

static void wf_colour_ram_ww(UINT32 address, UINT16 data)
{
   WriteWord(RAM + 0x0C000 + ((address & 0xFF80) >> 2) + (address & 0x1F), data);
}

static UINT8 wf_colour_ram_rb(UINT32 address)
{
   return ReadByte(RAM + 0x0C000 + ((address & 0xFF80) >> 2) + ((address & 0x1F) ^ 1));
}

static UINT16 wf_colour_ram_rw(UINT32 address)
{
   return ReadWord(RAM + 0x0C000 + ((address & 0xFF80) >> 2) + (address & 0x1F));
}

static void WFSoundWrite(UINT32 address, UINT16 data)
{
   WriteWord(&RAM[address-0x140000+0x1C000],data);

   if(address==0x14000C) TechnosSoundWrite68k(address,data);
}

static void WrestleFSpeedPatch(void)
{
   int address;

   for(address=0;address<0x80000-8;address+=2){
   if(ROM[address+0]==0x08){
   if(ROM[address+1]==0x39){
   if(ROM[address+2]==0x00){
   if(ROM[address+3]==0x01){
   if(ROM[address+4]==0x00){
   if(ROM[address+5]==0x1C){
   if(ROM[address+6]==0x00){
   if(ROM[address+7]==0x6F){

   ROM[address+0]=0x13;	//	move.b	#$00,$AA0000
   ROM[address+1]=0xFC;
   ROM[address+2]=0x00;
   ROM[address+3]=0x00;
   ROM[address+4]=0x00;
   ROM[address+5]=0xAA;
   ROM[address+6]=0x00;
   ROM[address+7]=0x00;

   ROM[address+8]=0x4E;	//	nop
   ROM[address+9]=0x71;

   }}}}}}}}
   }
}

static void load_wwfwfsta(void)
{
   UINT8 *TMP;
   int ta,tb,tc,td,te;

   if(!(GFX_SPR=AllocateMem(0x1000000))) return;
   if(!(TMP    =AllocateMem(0x0100000))) return;

   if(!load_rom("wf_15.rom", TMP, 0x100000)) return;	// SPRITE BANK A
   tb=0;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]=(((tc&0x80)>>7)<<0);
      GFX_SPR[tb+1]=(((tc&0x40)>>6)<<0);
      GFX_SPR[tb+2]=(((tc&0x20)>>5)<<0);
      GFX_SPR[tb+3]=(((tc&0x10)>>4)<<0);
      GFX_SPR[tb+4]=(((tc&0x08)>>3)<<0);
      GFX_SPR[tb+5]=(((tc&0x04)>>2)<<0);
      GFX_SPR[tb+6]=(((tc&0x02)>>1)<<0);
      GFX_SPR[tb+7]=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_12.rom", TMP, 0x100000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]|=(((tc&0x80)>>7)<<1);
      GFX_SPR[tb+1]|=(((tc&0x40)>>6)<<1);
      GFX_SPR[tb+2]|=(((tc&0x20)>>5)<<1);
      GFX_SPR[tb+3]|=(((tc&0x10)>>4)<<1);
      GFX_SPR[tb+4]|=(((tc&0x08)>>3)<<1);
      GFX_SPR[tb+5]|=(((tc&0x04)>>2)<<1);
      GFX_SPR[tb+6]|=(((tc&0x02)>>1)<<1);
      GFX_SPR[tb+7]|=(((tc&0x01)>>0)<<1);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_11.rom", TMP, 0x100000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]|=(((tc&0x80)>>7)<<2);
      GFX_SPR[tb+1]|=(((tc&0x40)>>6)<<2);
      GFX_SPR[tb+2]|=(((tc&0x20)>>5)<<2);
      GFX_SPR[tb+3]|=(((tc&0x10)>>4)<<2);
      GFX_SPR[tb+4]|=(((tc&0x08)>>3)<<2);
      GFX_SPR[tb+5]|=(((tc&0x04)>>2)<<2);
      GFX_SPR[tb+6]|=(((tc&0x02)>>1)<<2);
      GFX_SPR[tb+7]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_09.rom", TMP, 0x100000)) return;
   tb=0;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]|=(((tc&0x80)>>7)<<3);
      GFX_SPR[tb+1]|=(((tc&0x40)>>6)<<3);
      GFX_SPR[tb+2]|=(((tc&0x20)>>5)<<3);
      GFX_SPR[tb+3]|=(((tc&0x10)>>4)<<3);
      GFX_SPR[tb+4]|=(((tc&0x08)>>3)<<3);
      GFX_SPR[tb+5]|=(((tc&0x04)>>2)<<3);
      GFX_SPR[tb+6]|=(((tc&0x02)>>1)<<3);
      GFX_SPR[tb+7]|=(((tc&0x01)>>0)<<3);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_14.rom", TMP, 0x100000)) return;	// SPRITE BANK B
   tb=0x800000;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]=(((tc&0x80)>>7)<<0);
      GFX_SPR[tb+1]=(((tc&0x40)>>6)<<0);
      GFX_SPR[tb+2]=(((tc&0x20)>>5)<<0);
      GFX_SPR[tb+3]=(((tc&0x10)>>4)<<0);
      GFX_SPR[tb+4]=(((tc&0x08)>>3)<<0);
      GFX_SPR[tb+5]=(((tc&0x04)>>2)<<0);
      GFX_SPR[tb+6]=(((tc&0x02)>>1)<<0);
      GFX_SPR[tb+7]=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_13.rom", TMP, 0x100000)) return;
   tb=0x800000;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]|=(((tc&0x80)>>7)<<1);
      GFX_SPR[tb+1]|=(((tc&0x40)>>6)<<1);
      GFX_SPR[tb+2]|=(((tc&0x20)>>5)<<1);
      GFX_SPR[tb+3]|=(((tc&0x10)>>4)<<1);
      GFX_SPR[tb+4]|=(((tc&0x08)>>3)<<1);
      GFX_SPR[tb+5]|=(((tc&0x04)>>2)<<1);
      GFX_SPR[tb+6]|=(((tc&0x02)>>1)<<1);
      GFX_SPR[tb+7]|=(((tc&0x01)>>0)<<1);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_10.rom", TMP, 0x100000)) return;
   tb=0x800000;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]|=(((tc&0x80)>>7)<<2);
      GFX_SPR[tb+1]|=(((tc&0x40)>>6)<<2);
      GFX_SPR[tb+2]|=(((tc&0x20)>>5)<<2);
      GFX_SPR[tb+3]|=(((tc&0x10)>>4)<<2);
      GFX_SPR[tb+4]|=(((tc&0x08)>>3)<<2);
      GFX_SPR[tb+5]|=(((tc&0x04)>>2)<<2);
      GFX_SPR[tb+6]|=(((tc&0x02)>>1)<<2);
      GFX_SPR[tb+7]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("wf_08.rom", TMP, 0x100000)) return;
   tb=0x800000;
   for(ta=0;ta<0x100000;ta++){
      tc=TMP[ta];
      GFX_SPR[tb+0]|=(((tc&0x80)>>7)<<3);
      GFX_SPR[tb+1]|=(((tc&0x40)>>6)<<3);
      GFX_SPR[tb+2]|=(((tc&0x20)>>5)<<3);
      GFX_SPR[tb+3]|=(((tc&0x10)>>4)<<3);
      GFX_SPR[tb+4]|=(((tc&0x08)>>3)<<3);
      GFX_SPR[tb+5]|=(((tc&0x04)>>2)<<3);
      GFX_SPR[tb+6]|=(((tc&0x02)>>1)<<3);
      GFX_SPR[tb+7]|=(((tc&0x01)>>0)<<3);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   FreeMem(TMP);

   if(!(GFX=AllocateMem(0x0140000))) return;

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("31a11-2.42", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   Z80ROM[0x03E5]=0x00;		// Timers Bodge
   Z80ROM[0x03E9]=0x18;

   if(!(PCMROM = AllocateMem(0x80000))) return;
   if(!load_rom("wf_73a.rom", PCMROM, 0x80000)) return;	// ADPCM ROM <2 banks>

   AddTechnosSound(0x0040, 0x003A, 0x10000, PCMROM, PCMROM+0x40000, 63);

   /*---------------------------------*/

   if(!load_rom("wf_18.rom", RAM, 0x40000)) return;	// 68000 ROM (EVEN BYTES)
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("wf_19.rom", RAM, 0x40000)) return;	// 68000 ROM (ODD BYTES)
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("wf_33.rom", RAM, 0x20000)) return;	// FG TILES (8x8)
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

   if(!load_rom("wf_01.rom", RAM, 0x40000)) return;	// BG TILES (16x16)
   tb=0x40000;
   for(ta=0;ta<0x40000;ta+=2){
      tc=RAM[ta+0];
      td=RAM[ta+1];
      GFX[tb+0]=(((tc&0x80)>>7)<<0);
      GFX[tb+1]=(((tc&0x40)>>6)<<0);
      GFX[tb+2]=(((tc&0x20)>>5)<<0);
      GFX[tb+3]=(((tc&0x10)>>4)<<0);
      GFX[tb+4]=(((tc&0x08)>>3)<<0);
      GFX[tb+5]=(((tc&0x04)>>2)<<0);
      GFX[tb+6]=(((tc&0x02)>>1)<<0);
      GFX[tb+7]=(((tc&0x01)>>0)<<0);
      GFX[tb+0]|=(((td&0x80)>>7)<<1);
      GFX[tb+1]|=(((td&0x40)>>6)<<1);
      GFX[tb+2]|=(((td&0x20)>>5)<<1);
      GFX[tb+3]|=(((td&0x10)>>4)<<1);
      GFX[tb+4]|=(((td&0x08)>>3)<<1);
      GFX[tb+5]|=(((td&0x04)>>2)<<1);
      GFX[tb+6]|=(((td&0x02)>>1)<<1);
      GFX[tb+7]|=(((td&0x01)>>0)<<1);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   if(!load_rom("wf_02.rom", RAM, 0x40000)) return;
   tb=0x40000;
   for(ta=0;ta<0x40000;ta+=2){
      tc=RAM[ta+0];
      td=RAM[ta+1];
      GFX[tb+0]|=(((tc&0x80)>>7)<<2);
      GFX[tb+1]|=(((tc&0x40)>>6)<<2);
      GFX[tb+2]|=(((tc&0x20)>>5)<<2);
      GFX[tb+3]|=(((tc&0x10)>>4)<<2);
      GFX[tb+4]|=(((tc&0x08)>>3)<<2);
      GFX[tb+5]|=(((tc&0x04)>>2)<<2);
      GFX[tb+6]|=(((tc&0x02)>>1)<<2);
      GFX[tb+7]|=(((tc&0x01)>>0)<<2);
      GFX[tb+0]|=(((td&0x80)>>7)<<3);
      GFX[tb+1]|=(((td&0x40)>>6)<<3);
      GFX[tb+2]|=(((td&0x20)>>5)<<3);
      GFX[tb+3]|=(((td&0x10)>>4)<<3);
      GFX[tb+4]|=(((td&0x08)>>3)<<3);
      GFX[tb+5]|=(((td&0x04)>>2)<<3);
      GFX[tb+6]|=(((td&0x02)>>1)<<3);
      GFX[tb+7]|=(((td&0x01)>>0)<<3);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x1C000,0xFF,0x01000);

   RAM_BG0 = RAM+0xA000;
   RAM_BG1 = RAM+0x8000;
   RAM_SPR = RAM+0x6000;
   RAM_FG0 = RAM+0x4000;

   GFX_BG0 = GFX+0x040000;
   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x1000);

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x10000);

   GFX_FG0 = GFX+0x000000;
   GFX_FG0_SOLID = make_solid_mask_8x8(GFX_FG0, 0x1000);

   ROM[0xD2D1]=0x42;		// Fix dodgy 24-bit addressing...
   ROM[0xD3B5]=0x42;		// Fix dodgy 24-bit addressing...
   ROM[0xD827]=0x42;		// Fix dodgy 24-bit addressing...
   ROM[0xD9AF]=0x42;		// Fix dodgy 24-bit addressing...

   InitPaletteMap(RAM+0x0C000, 0x200, 0x10, 0x1000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);

/*
 *  Catch 68000 Interrupt wait
 */

   WrestleFSpeedPatch();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);		// 68000 ROM
   AddReadByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddReadByte(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);		// SCREEN RAM
   AddReadByte(0x080000, 0x083FFF, NULL, RAM+0x008000);		// OBJECT RAM
   AddReadByte(0x180000, 0x18FFFF, wf_colour_ram_rb, NULL);	// PALETTE RAM
   AddReadByte(0x100000, 0x1000FF, NULL, RAM+0x02C000);		// SCROLL
   AddReadByte(0x140000, 0x140FFF, NULL, RAM+0x01C000);		// INPUT
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);		// 68000 ROM
   AddReadWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddReadWord(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);		// SCREEN RAM
   AddReadWord(0x080000, 0x083FFF, NULL, RAM+0x008000);		// OBJECT RAM
   AddReadWord(0x180000, 0x18FFFF, wf_colour_ram_rw, NULL);	// PALETTE RAM
   AddReadWord(0x100000, 0x1000FF, NULL, RAM+0x02C000);		// SCROLL
   AddReadWord(0x140000, 0x140FFF, NULL, RAM+0x01C000);		// INPUT
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);	// 68000 RAM
   AddWriteByte(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);	// SCREEN RAM
   AddWriteByte(0x080000, 0x083FFF, NULL, RAM+0x008000);	// OBJECT RAM
   AddWriteByte(0x180000, 0x18FFFF, wf_colour_ram_wb, NULL);	// PALETTE RAM
   AddWriteByte(0x140000, 0x140FFF, NULL, RAM+0x01C000);	// INPUT
   AddWriteByte(0x100000, 0x1000FF, NULL, RAM+0x02C000);	// SCROLL
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);	// 68000 RAM
   AddWriteWord(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);	// SCREEN RAM
   AddWriteWord(0x080000, 0x083FFF, NULL, RAM+0x008000);	// OBJECT RAM
   AddWriteWord(0x180000, 0x18FFFF, wf_colour_ram_ww, NULL);	// PALETTE RAM
   AddWriteWord(0x140000, 0x140FFF, WFSoundWrite, NULL);	// INPUT
   AddWriteWord(0x100000, 0x1000FF, NULL, RAM+0x02C000);	// SCROLL
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
   adpcm_amplify = 2;
   for (ta=0; ta<4; ta++)
       layer_id_data[ta] = add_layer_info(layer_id_name[ta]);
}

static void execute_wwfwfsta(void)
{
   int ta;

   // DSW are mapped between several bytes, this quick
   // hack splits them and maps them in RAM[]

   ta=get_dsw(1);
   RAM[0x1C021]&=0xCF;
   RAM[0x1C021]|=(ta>>2)&0x30;
   RAM[0x1C023]&=0xC0;
   RAM[0x1C023]|=ta&0x3F;
   ta=get_dsw(0);
   RAM[0x1C025]&=0xC0;
   RAM[0x1C025]|=ta&0x3F;
   RAM[0x1C027]&=0xFC;
   RAM[0x1C027]|=(ta>>6)&0x03;
   RAM[0x1C027]^=4;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);
   cpu_interrupt(CPU_68K_0, 3);

//   TechnosSound_Frame();		// Z80; YM2151; OKI ADPCM
   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Sound Z80 xMhz
}


static void RenderObject(void)
{
   int zz,x,y,ta,nn;
   UINT8 *map;

   if(! check_layer_enabled(layer_id_data[3]))
       return;
   for(zz=0x0000;zz<0x1000;zz+=16){

      if((RAM_SPR[zz+2]&0x01)!=0){

         x = (32 + (RAM_SPR[zz+10] | ((RAM_SPR[zz+2]&4)<<6) ))&0x1FF;
         y = ((240+24) - (RAM_SPR[zz+0] | ((RAM_SPR[zz+2]&2)<<7) ))&0x1FF;

         MAP_PALETTE_MAPPED_NEW(
            (RAM_SPR[zz+8]&0x0F)|0x40,
            16,
            map
         );

         ta = ((RAM_SPR[zz+4]) | (RAM_SPR[zz+6]<<8));

         nn = ((RAM_SPR[zz+2]>>5)&0x07)+1;

         switch(RAM_SPR[zz+2]&0x18){
         case 0x00:
            do{

               if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){

               if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

               if(GFX_SPR_SOLID[ta]==1) Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);
               else                     Draw16x16_Mapped_Rot(      &GFX_SPR[ta<<8], x, y, map);

               }
               }

               ta++;
               y-=16;

            }while(--nn);
         break;
         case 0x10:
            do{

               if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){

               if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

               if(GFX_SPR_SOLID[ta]==1) Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);
               else                     Draw16x16_Mapped_FlipY_Rot(      &GFX_SPR[ta<<8], x, y, map);

               }
               }

               ta++;
               y-=16;

            }while(--nn);
         break;
         case 0x08:

            y-=((nn-1)*16);

            do{

               if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){

               if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

               if(GFX_SPR_SOLID[ta]==1) Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);
               else                     Draw16x16_Mapped_FlipX_Rot(      &GFX_SPR[ta<<8], x, y, map);

               }
               }

               ta++;
               y+=16;

            }while(--nn);
         break;
         case 0x18:

            y-=((nn-1)*16);

            do{

               if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){

               if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

               if(GFX_SPR_SOLID[ta]==1) Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map);
               else                     Draw16x16_Mapped_FlipXY_Rot(      &GFX_SPR[ta<<8], x, y, map);

               }
               }

               ta++;
               y+=16;

            }while(--nn);
         break;
         }

      }
   }
}

static void DrawWrestleF(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta,bg_pri;
   UINT8 *map;

   ClearPaletteMap();

   bg_pri=0;
   ta=ReadWord(&RAM[0xA180]);
   if(ta==0x02BB){bg_pri=1;}	// Normal Match
   if(ta==0x0614){bg_pri=1;}	// Cage Match
   if(ta==0x04B7){bg_pri=2;}	// Select Screen (Normal)
   if(ta==0xF8C7){bg_pri=2;}	// Select Screen (Royal Rumble)
   ta=ReadWord(&RAM[0xA380]);
   if(ta==0x07AF){bg_pri=1;}	// Out of Ring

   if((bg_pri==0)||(bg_pri==1)){

   // BG1
   // ---

   if(check_layer_enabled(layer_id_data[1])) {
       MAKE_SCROLL_512x512_4_16(
	       ReadWord(&RAM[0x2C000]),
	       ReadWord(&RAM[0x2C002])+8
	       );

       START_SCROLL_512x512_4_16(32,32,320,240);

       ta = ReadWord(&RAM_BG1[zz+2])&0x1FFF;

       MAP_PALETTE_MAPPED_NEW(
	       (RAM_BG1[zz]&0x0F)|0x100,
	       16,
	       map
	       );

       switch(RAM_BG1[zz]&0xC0){
       case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);        break;
       case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8], x, y, map);  break;
       case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8], x, y, map);  break;
       case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8], x, y, map); break;
       }

       END_SCROLL_512x512_4_16();
   } else
       clear_game_screen(0);

   if(bg_pri==1) RenderObject();

   // BG0
   // ---

   if(check_layer_enabled(layer_id_data[0])) {
       MAKE_SCROLL_512x512_2_16(
	       ReadWord(&RAM[0x2C004]),
	       ReadWord(&RAM[0x2C006])+8
	       );

       START_SCROLL_512x512_2_16(32,32,320,240);

       ta = ReadWord(&RAM_BG0[zz])&0x0FFF;
       if(GFX_BG0_SOLID[ta]!=0){				// No pixels; skip

	   MAP_PALETTE_MAPPED_NEW(
		   ((ReadWord(&RAM_BG0[zz])>>12)&0x0F)|0xC0,
		   16,
		   map
		   );


	   if(GFX_BG0_SOLID[ta]==1){			// Some pixels; trans
	       Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);
	   }
	   else{						// all pixels; solid
	       Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);
	   }
       }

       END_SCROLL_512x512_2_16();
   }

   if(bg_pri==0) RenderObject();

   }
   else{

   // BG0
   // ---

   if(check_layer_enabled(layer_id_data[0])) {
       MAKE_SCROLL_512x512_2_16(
	       ReadWord(&RAM[0x2C004]),
	       ReadWord(&RAM[0x2C006])+8
	       );

       START_SCROLL_512x512_2_16(32,32,320,240);

       MAP_PALETTE_MAPPED_NEW(
	       ((ReadWord(&RAM_BG0[zz])>>12)&0x0F)|0xC0,
	       16,
	       map
	       );

       Draw16x16_Mapped_Rot(&GFX_BG0[(ReadWord(&RAM_BG0[zz])&0x0FFF)<<8], x, y, map);

       END_SCROLL_512x512_2_16();
   } else
       clear_game_screen(0);

   // BG1
   // ---


   if(check_layer_enabled(layer_id_data[1])) {
       MAKE_SCROLL_512x512_4_16(
	       ReadWord(&RAM[0x2C000]),
	       ReadWord(&RAM[0x2C002])+8
	       );

       START_SCROLL_512x512_4_16(32,32,320,240);

       ta = ReadWord(&RAM_BG1[zz+2])&0x1FFF;
       if(GFX_BG0_SOLID[ta]!=0){				// No pixels; skip

	   MAP_PALETTE_MAPPED_NEW(
		   (RAM_BG1[zz]&0x0F)|0x100,
		   16,
		   map
		   );

	   if(GFX_BG0_SOLID[ta]==1){			// Some pixels; trans
	       switch(RAM_BG1[zz]&0xC0){
	       case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);        break;
	       case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<8], x, y, map);  break;
	       case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<8], x, y, map);  break;
	       case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8], x, y, map); break;
	       }
	   }
	   else{						// all pixels; solid
	       switch(RAM_BG1[zz]&0xC0){
	       case 0x00: Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);        break;
	       case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_BG0[ta<<8], x, y, map);  break;
	       case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[ta<<8], x, y, map);  break;
	       case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG0[ta<<8], x, y, map); break;
	       }
	   }

       }

       END_SCROLL_512x512_4_16();
   }

   RenderObject();

   }

   // FG0
   // ---

   if(check_layer_enabled(layer_id_data[2])) {
       MAKE_SCROLL_512x512_4_8(
	       0,
	       8
	       );

       START_SCROLL_512x512_4_8(32,32,320,240);

       ta = ((RAM_FG0[zz]) | (RAM_FG0[zz+2]<<8))&0xFFF;

       if(GFX_FG0_SOLID[ta]!=0){				// No pixels; skip

	   MAP_PALETTE_MAPPED_NEW(
		   RAM_FG0[zz+2]>>4,
		   16,
		   map
		   );

	   if(GFX_FG0_SOLID[ta]==1){			// Some pixels; trans
	       Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);
	   }
	   else{						// all pixels; solid
	       Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);
	   }
       }

       END_SCROLL_512x512_4_8();
   }

}


/*

BG1 Data (4 bytes per Tile)
===========================

Byte(s)| Bit(s) | Description
-------+76543210+----------------------------
   00  |........| Unused
   01  |.x......| Tile Flip X-Axis
   01  |x.......| Tile Flip Y-Axis
   01  |....xxxx| Palette Bank (0-15)
   02  |....xxxx| Tile Number (high 4 bits)
   03  |xxxxxxxx| Tile Number (low 8 bits)

BG1 Data (2 bytes per Tile)
===========================

Byte(s)| Bit(s) | Description
-------+76543210+----------------------------
   00  |xxxx....| Palette Bank (0-15)
   00  |....xxxx| Tile Number (high 4 bits)
   01  |xxxxxxxx| Tile Number (low 8 bits)

Sprite Data (16 bytes per Sprite)
=================================

Byte(s)| Bit(s) | Description
-------+76543210+----------------------------
   00  |.......x| Sprite Ypos (high bit)
   01  |xxxxxxxx| Sprite Ypos (low 8 bits)
   03  |xxx.....| Number of chained Sprites
   03  |...x....| Sprite Flip X-Axis
   03  |....x...| Sprite Flip Y-Axis
   05  |xxxxxxxx| Sprite Number (low 8 bits)
   07  |xxxxxxxx| Sprite Number (high 8 bits)
   0A  |.......x| Sprite Xpos (high bit)
   0B  |xxxxxxxx| Sprite Xpos (low 8 bits)
 0C-0F |........| Unused

*/
static struct VIDEO_INFO video_wwfwfsta =
{
   DrawWrestleF,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_wwfwfsta[] =
{
   { "wrestle_fest", },
   { "wrestlef", },
   { "wwfwfsta", },
   { "wwfwfest", },
   { NULL, },
};
GME( wwfwfsta, "WWF Wrestlefest", TECHNOS, 1991, GAME_BEAT,
	.long_name_jpn = "‚v‚v‚eƒŒƒbƒXƒ‹ƒtƒFƒ‹ƒg",
	.board = "TA-0031",
);

