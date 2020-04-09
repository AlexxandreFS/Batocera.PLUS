#define DRV_DEF_SOUND technos_ym2151_m6295_sound
/******************************************************************************/
/*                                                                            */
/*              COMBA TRIBES - BOOTLEG (C) 1990 TECHNOS JAPAN                 */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "tchnosnd.h"


static struct ROM_INFO rom_ctribe[] =
{
   {        "ic-26", 0x00020000, 0xc46b2e63, 0, 0, 0, },
   {   "ct_ep2.rom", 0x00010000, 0x8c2c6dbd, 0, 0, 0, },
   {        "ic-25", 0x00020000, 0x3221c755, 0, 0, 0, },
   {   "ct_ep4.rom", 0x00008000, 0x4346de13, 0, 0, 0, },
   {   "ct_ep5.rom", 0x00010000, 0x972faddb, 0, 0, 0, },
   {   "ct_ep6.rom", 0x00010000, 0xeb3ab374, 0, 0, 0, },
   {   "ct_ep7.rom", 0x00010000, 0xc602ac97, 0, 0, 0, },
   {   "ct_ep8.rom", 0x00010000, 0x4da1d8e5, 0, 0, 0, },
   {   "ct_mr0.rom", 0x00080000, 0xba73c49e, 0, 0, 0, },
   {   "ct_mr1.rom", 0x00080000, 0x1c9badbd, 0, 0, 0, },
   {   "ct_mr2.rom", 0x00080000, 0x8c796707, 0, 0, 0, },
   {   "ct_mr3.rom", 0x00080000, 0x1ac2a461, 0, 0, 0, },
   {   "ct_mr4.rom", 0x00040000, 0xb84fda09, 0, 0, 0, },
   {   "ct_mr5.rom", 0x00040000, 0xcef0a821, 0, 0, 0, },
   {   "ct_mr6.rom", 0x00040000, 0x617530fc, 0, 0, 0, },
   {   "ct_mr7.rom", 0x00040000, 0xa8b773f1, 0, 0, 0, },
   {   "ct_mr8.rom", 0x00040000, 0x9963a6be, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ctribe[] =
{
   INP0( COIN1, 0x014001, 0x01 ),
   INP0( COIN2, 0x014001, 0x02 ),
   INP0( SERVICE, 0x014001, 0x04 ),

   INP0( P1_START, 0x014000, 0x80 ),
   INP0( P1_UP, 0x014000, 0x04 ),
   INP0( P1_DOWN, 0x014000, 0x08 ),
   INP0( P1_LEFT, 0x014000, 0x02 ),
   INP0( P1_RIGHT, 0x014000, 0x01 ),
   INP0( P1_B1, 0x014000, 0x10 ),
   INP0( P1_B2, 0x014000, 0x20 ),
   INP0( P1_B3, 0x014000, 0x40 ),

   INP0( P2_START, 0x014002, 0x80 ),
   INP0( P2_UP, 0x014002, 0x04 ),
   INP0( P2_DOWN, 0x014002, 0x08 ),
   INP0( P2_LEFT, 0x014002, 0x02 ),
   INP0( P2_RIGHT, 0x014002, 0x01 ),
   INP0( P2_B1, 0x014002, 0x10 ),
   INP0( P2_B2, 0x014002, 0x20 ),
   INP0( P2_B3, 0x014002, 0x40 ),

   INP0( P3_START, 0x014004, 0x80 ),
   INP0( P3_UP, 0x014004, 0x04 ),
   INP0( P3_DOWN, 0x014004, 0x08 ),
   INP0( P3_LEFT, 0x014004, 0x02 ),
   INP0( P3_RIGHT, 0x014004, 0x01 ),
   INP0( P3_B1, 0x014004, 0x10 ),
   INP0( P3_B2, 0x014004, 0x20 ),
   INP0( P3_B3, 0x014004, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_combatribes_0[] =
{
   { MSG_COINAGE,             0x03, 0x04 },
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_1COIN_2PLAY,         0x02},
   DSW_UNUSED( 0x00, 0x04),
   DSW_UNUSED( 0x00, 0x08),
   { _("1 Coin to Continue"),    0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   DSW_DEMO_SOUND( 0x20, 0x00),
   DSW_SCREEN( 0x40, 0x00),
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_combatribes_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Timer Speed"),           0x04, 0x02 },
   { MSG_NORMAL,              0x04},
   { _("Fast"),                  0x00},
   { _("FBI Logo"),              0x08, 0x02 },
   { MSG_YES,                 0x08},
   { MSG_NO,                  0x00},
   DSW_TEST_MODE( 0x00, 0x10),
   { _("Stage Clear Life"),      0x60, 0x04 },
   { "0",                     0x60},
   { "50",                    0x40},
   { "100",                   0x20},
   { "150",                   0x00},
   { MSG_CABINET, 0x80, 2 },
   { _("3 Players"), 0x00 },
   { _("2 Players"), 0x80 },
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ctribe[] =
{
   { 0x014011, 0xFF, dsw_data_combatribes_0 },
   { 0x014013, 0xBF, dsw_data_combatribes_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_ctribeb[] =
{
   {   "ct_ep1.rom", 0x00020000, 0x9cfa997f, 0, 0, 0, },
   {   "ct_ep2.rom", 0x00010000, 0x8c2c6dbd, 0, 0, 0, },
   {   "ct_ep3.rom", 0x00020000, 0x2ece8681, 0, 0, 0, },
   {   "ct_ep4.rom", 0x00008000, 0x4346de13, 0, 0, 0, },
   {   "ct_ep5.rom", 0x00010000, 0x972faddb, 0, 0, 0, },
   {   "ct_ep6.rom", 0x00010000, 0xeb3ab374, 0, 0, 0, },
   {   "ct_ep7.rom", 0x00010000, 0xc602ac97, 0, 0, 0, },
   {   "ct_ep8.rom", 0x00010000, 0x4da1d8e5, 0, 0, 0, },
   {   "ct_mr0.rom", 0x00080000, 0xba73c49e, 0, 0, 0, },
   {   "ct_mr1.rom", 0x00080000, 0x1c9badbd, 0, 0, 0, },
   {   "ct_mr2.rom", 0x00080000, 0x8c796707, 0, 0, 0, },
   {   "ct_mr3.rom", 0x00080000, 0x1ac2a461, 0, 0, 0, },
   {   "ct_mr4.rom", 0x00040000, 0xb84fda09, 0, 0, 0, },
   {   "ct_mr5.rom", 0x00040000, 0xcef0a821, 0, 0, 0, },
   {   "ct_mr6.rom", 0x00040000, 0x617530fc, 0, 0, 0, },
   {   "ct_mr7.rom", 0x00040000, 0xa8b773f1, 0, 0, 0, },
   {   "ct_mr8.rom", 0x00040000, 0x9963a6be, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static UINT8 *GFX_BG0_SOLID;
static UINT8 *GFX_SPR_SOLID;

static void WriteOutByte(UINT32 address, UINT8 data)
{
	address &= 0x0F;
	RAM[(0x13000+address)^1]=data;

	if(address==3)
		TechnosSoundWrite68k(address,data);
}

static void WriteOutWord(UINT32 address, UINT16 data)
{
	address &= 0x0F;
	WriteWord(&RAM[0x13000+address],data);

	if(address==2)
		TechnosSoundWrite68k(address, (UINT8) (data&0xFF) );
}

static void CombaTribesSpeedPatch(void)
{
   int address;

   for(address=0;address<0x40000-8;address+=2){
   if(ReadLong68k(&ROM[address+0])==0x08390003){
   if(ReadLong68k(&ROM[address+4])==0x00180000){

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

   }}
   }
}

static void load_ctribe(void)
{
   int ta,tb,tc;

   RAMSize=0x40000+0x10000;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x680000))) return;

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("ct_ep4.rom", Z80ROM, 0x8000)) return;	// Z80 SOUND ROM

   Z80ROM[0x0098]=0x0F;
   Z80ROM[0x009F]=0xA8;
   Z80ROM[0x00E0]=0xC9;

   if(!(PCMROM = AllocateMem(0x40000))) return;
   if(!load_rom("ct_mr8.rom", PCMROM, 0x40000)) return;	// ADPCM ROM

   for(ta=0;ta<0x20000;ta++){	// OKI ROM is out of sequence!!
      tb=PCMROM[ta];
      PCMROM[ta]=PCMROM[ta+0x20000];
      PCMROM[ta+0x20000]=tb;
   }

   AddTechnosSoundOld(0x00A8, 0x0083, 0x8000, PCMROM, 159);

   /*---------------------------------*/

   tb=0;
   if(!load_rom("ct_mr4.rom", ROM, 0x40000)) return;		// BG0
   for(ta=0;ta<0x40000;ta++){
      tc=ROM[ta];
      GFX[tb+0]=(((tc&0x80)>>7)<<0);
      GFX[tb+1]=(((tc&0x40)>>6)<<0);
      GFX[tb+2]=(((tc&0x20)>>5)<<0);
      GFX[tb+3]=(((tc&0x10)>>4)<<0);
      GFX[tb+4]=(((tc&0x08)>>3)<<0);
      GFX[tb+5]=(((tc&0x04)>>2)<<0);
      GFX[tb+6]=(((tc&0x02)>>1)<<0);
      GFX[tb+7]=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
   tb=0;
   if(!load_rom("ct_mr5.rom", ROM, 0x40000)) return;		// BG0
   for(ta=0;ta<0x40000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<1);
      GFX[tb+1]|=(((tc&0x40)>>6)<<1);
      GFX[tb+2]|=(((tc&0x20)>>5)<<1);
      GFX[tb+3]|=(((tc&0x10)>>4)<<1);
      GFX[tb+4]|=(((tc&0x08)>>3)<<1);
      GFX[tb+5]|=(((tc&0x04)>>2)<<1);
      GFX[tb+6]|=(((tc&0x02)>>1)<<1);
      GFX[tb+7]|=(((tc&0x01)>>0)<<1);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
   tb=0;
   if(!load_rom("ct_mr6.rom", ROM, 0x40000)) return;		// BG0
   for(ta=0;ta<0x40000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<2);
      GFX[tb+1]|=(((tc&0x40)>>6)<<2);
      GFX[tb+2]|=(((tc&0x20)>>5)<<2);
      GFX[tb+3]|=(((tc&0x10)>>4)<<2);
      GFX[tb+4]|=(((tc&0x08)>>3)<<2);
      GFX[tb+5]|=(((tc&0x04)>>2)<<2);
      GFX[tb+6]|=(((tc&0x02)>>1)<<2);
      GFX[tb+7]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
   tb=0;
   if(!load_rom("ct_mr7.rom", ROM, 0x40000)) return;		// BG0
   for(ta=0;ta<0x40000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<3);
      GFX[tb+1]|=(((tc&0x40)>>6)<<3);
      GFX[tb+2]|=(((tc&0x20)>>5)<<3);
      GFX[tb+3]|=(((tc&0x10)>>4)<<3);
      GFX[tb+4]|=(((tc&0x08)>>3)<<3);
      GFX[tb+5]|=(((tc&0x04)>>2)<<3);
      GFX[tb+6]|=(((tc&0x02)>>1)<<3);
      GFX[tb+7]|=(((tc&0x01)>>0)<<3);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x200000;
   if(!load_rom("ct_mr0.rom", ROM, 0x80000)) return;		// SPR
   for(ta=0;ta<0x80000;ta++){
      tc=ROM[ta];
      GFX[tb+0]=(((tc&0x80)>>7)<<0);
      GFX[tb+1]=(((tc&0x40)>>6)<<0);
      GFX[tb+2]=(((tc&0x20)>>5)<<0);
      GFX[tb+3]=(((tc&0x10)>>4)<<0);
      GFX[tb+4]=(((tc&0x08)>>3)<<0);
      GFX[tb+5]=(((tc&0x04)>>2)<<0);
      GFX[tb+6]=(((tc&0x02)>>1)<<0);
      GFX[tb+7]=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x200000;
   if(!load_rom("ct_mr1.rom", ROM, 0x80000)) return;		// SPR
   for(ta=0;ta<0x80000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<1);
      GFX[tb+1]|=(((tc&0x40)>>6)<<1);
      GFX[tb+2]|=(((tc&0x20)>>5)<<1);
      GFX[tb+3]|=(((tc&0x10)>>4)<<1);
      GFX[tb+4]|=(((tc&0x08)>>3)<<1);
      GFX[tb+5]|=(((tc&0x04)>>2)<<1);
      GFX[tb+6]|=(((tc&0x02)>>1)<<1);
      GFX[tb+7]|=(((tc&0x01)>>0)<<1);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x200000;
   if(!load_rom("ct_mr2.rom", ROM, 0x80000)) return;		// SPR
   for(ta=0;ta<0x80000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<2);
      GFX[tb+1]|=(((tc&0x40)>>6)<<2);
      GFX[tb+2]|=(((tc&0x20)>>5)<<2);
      GFX[tb+3]|=(((tc&0x10)>>4)<<2);
      GFX[tb+4]|=(((tc&0x08)>>3)<<2);
      GFX[tb+5]|=(((tc&0x04)>>2)<<2);
      GFX[tb+6]|=(((tc&0x02)>>1)<<2);
      GFX[tb+7]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x200000;
   if(!load_rom("ct_mr3.rom", ROM, 0x80000)) return;		// SPR
   for(ta=0;ta<0x80000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<3);
      GFX[tb+1]|=(((tc&0x40)>>6)<<3);
      GFX[tb+2]|=(((tc&0x20)>>5)<<3);
      GFX[tb+3]|=(((tc&0x10)>>4)<<3);
      GFX[tb+4]|=(((tc&0x08)>>3)<<3);
      GFX[tb+5]|=(((tc&0x04)>>2)<<3);
      GFX[tb+6]|=(((tc&0x02)>>1)<<3);
      GFX[tb+7]|=(((tc&0x01)>>0)<<3);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x600000;
   if(!load_rom("ct_ep8.rom", ROM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      tc=ROM[ta];
      GFX[tb+0]=(((tc&0x80)>>7)<<0);
      GFX[tb+1]=(((tc&0x40)>>6)<<0);
      GFX[tb+2]=(((tc&0x20)>>5)<<0);
      GFX[tb+3]=(((tc&0x10)>>4)<<0);
      GFX[tb+4]=(((tc&0x08)>>3)<<0);
      GFX[tb+5]=(((tc&0x04)>>2)<<0);
      GFX[tb+6]=(((tc&0x02)>>1)<<0);
      GFX[tb+7]=(((tc&0x01)>>0)<<0);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x600000;
   if(!load_rom("ct_ep7.rom", ROM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<1);
      GFX[tb+1]|=(((tc&0x40)>>6)<<1);
      GFX[tb+2]|=(((tc&0x20)>>5)<<1);
      GFX[tb+3]|=(((tc&0x10)>>4)<<1);
      GFX[tb+4]|=(((tc&0x08)>>3)<<1);
      GFX[tb+5]|=(((tc&0x04)>>2)<<1);
      GFX[tb+6]|=(((tc&0x02)>>1)<<1);
      GFX[tb+7]|=(((tc&0x01)>>0)<<1);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x600000;
   if(!load_rom("ct_ep6.rom", ROM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<2);
      GFX[tb+1]|=(((tc&0x40)>>6)<<2);
      GFX[tb+2]|=(((tc&0x20)>>5)<<2);
      GFX[tb+3]|=(((tc&0x10)>>4)<<2);
      GFX[tb+4]|=(((tc&0x08)>>3)<<2);
      GFX[tb+5]|=(((tc&0x04)>>2)<<2);
      GFX[tb+6]|=(((tc&0x02)>>1)<<2);
      GFX[tb+7]|=(((tc&0x01)>>0)<<2);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   tb=0x600000;
   if(!load_rom("ct_ep5.rom", ROM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      tc=ROM[ta];
      GFX[tb+0]|=(((tc&0x80)>>7)<<3);
      GFX[tb+1]|=(((tc&0x40)>>6)<<3);
      GFX[tb+2]|=(((tc&0x20)>>5)<<3);
      GFX[tb+3]|=(((tc&0x10)>>4)<<3);
      GFX[tb+4]|=(((tc&0x08)>>3)<<3);
      GFX[tb+5]|=(((tc&0x04)>>2)<<3);
      GFX[tb+6]|=(((tc&0x02)>>1)<<3);
      GFX[tb+7]|=(((tc&0x01)>>0)<<3);
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   if(!load_rom_index(2, RAM, 0x20000)) return;            // MAIN 68000
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(0, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("ct_ep2.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("ct_ep2.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX + 0x000000, 0x2000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX + 0x200000, 0x4800);

   memset(RAM+0x00000,0x00,0x40000);

   InitPaletteMap(RAM+0x12000, 0x30, 0x10, 0x1000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr);

   CombaTribesSpeedPatch();
/*
   WriteLong68k(&ROM[0x00A54],0x13FC0000);
   WriteLong68k(&ROM[0x00A58],0x00AA0000);
   WriteWord68k(&ROM[0x00A5C],0x4E71);

   WriteLong68k(&ROM[0x00402],0x13FC0000);
   WriteLong68k(&ROM[0x00406],0x00AA0000);
   WriteWord68k(&ROM[0x0040A],0x4E71);

   WriteLong68k(&ROM[0x09EA2],0x13FC0000);
   WriteLong68k(&ROM[0x09EA6],0x00AA0000);
   WriteWord68k(&ROM[0x09EAA],0x4E71);

   WriteLong68k(&ROM[0x0B29A],0x13FC0000);
   WriteLong68k(&ROM[0x0B29E],0x00AA0000);
   WriteWord68k(&ROM[0x0B2A2],0x4E71);
*/
/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x080000, 0x083FFF, NULL, RAM+0x004000);			// VIDEO RAM
   AddReadByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);			// SCROLL RAM
   AddReadByte(0x100000, 0x100FFF, NULL, RAM+0x012000);			// COLOR RAM
   AddReadByte(0x140000, 0x14000F, NULL, RAM+0x013000);			// COMM RAM
   AddReadByte(0x180000, 0x18000F, NULL, RAM+0x014000);			// INPUTS
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x080000, 0x083FFF, NULL, RAM+0x004000);			// VIDEO RAM
   AddReadWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);			// SCROLL RAM
   AddReadWord(0x100000, 0x100FFF, NULL, RAM+0x012000);			// COLOR RAM
   AddReadWord(0x140000, 0x14000F, NULL, RAM+0x013000);			// COMM RAM
   AddReadWord(0x180000, 0x18000F, NULL, RAM+0x014000);			// INPUTS
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x080000, 0x083FFF, NULL, RAM+0x004000);		// VIDEO RAM
   AddWriteByte(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);		// SCROLL RAM
   AddWriteByte(0x100000, 0x100FFF, NULL, RAM+0x012000);		// COLOR RAM
   AddWriteByte(0x140000, 0x14000F, WriteOutByte, NULL);		//
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x080000, 0x083FFF, NULL, RAM+0x004000);		// VIDEO RAM
   AddWriteWord(0x0C0000, 0x0C0FFF, NULL, RAM+0x011000);		// SCROLL RAM
   AddWriteWord(0x100000, 0x100FFF, NULL, RAM+0x012000);		// COLOR RAM
   AddWriteWord(0x140000, 0x14000F, WriteOutWord, NULL);		//
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_ctribe(void)
{
   int ta;

   // DSW are mapped between several bytes, this quick
   // hack splits them and maps them in RAM[]

   ta=get_dsw(0);
   RAM[0x14001]&=0xCF;
   RAM[0x14001]|=(ta>>2)&0x30;
   RAM[0x14003]&=0xC0;
   RAM[0x14003]|=ta&0x3F;
   ta=get_dsw(1);
   RAM[0x14005]&=0xC0;
   RAM[0x14005]|=ta&0x3F;
   RAM[0x14007]&=0xFC;
   RAM[0x14007]|=(ta>>6)&0x03;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(6,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5); // inputs
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(6,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 6); // vblank

   TechnosSoundOld_Frame();	// Z80; YM2151; OKI ADPCM
}

static void DrawCombaTribes(void)
{
   UINT8 *MAP;
   int x,y,ta,tb;
   int zz,zzz,zzzz,x16,y16;
   int td;

   ClearPaletteMap();   // (0x30,0x1000);

   zzz=ReadWord(&RAM[0x11004]);
   zzzz=((zzz&0x1F0)>>4)<<1;			// X Offset (16-511)
   x16=zzz&15;					// X Offset (0-15)
   zzz=ReadWord(&RAM[0x11006]);
   zzzz|=((zzz&0x1F0)>>4)<<6;			// Y Offset (16-511)
   y16=zzz&15;					// Y Offset (0-15)

   zzzz&=0x7FF;
   zz=zzzz;

   for(y=24-y16;y<256+24;y+=16){
   for(x=32-x16;x<320+32;x+=16){

      MAP_PALETTE_MAPPED_NEW(
         ((ReadWord(&RAM[zz+0x6000]))>>12)|0x20,
         16,
         MAP
      );

      Draw16x16_Mapped_Rot(&GFX[((ReadWord(&RAM[zz+0x6000])&0xFFF)|0x1000)<<8],x,y,MAP);

      zz=(zz&0x7C0)|((zz+2)&0x3F);
   }
   zzzz=(zzzz+0x40)&0x7FF;
   zz=zzzz;
   }


   zzz=ReadWord(&RAM[0x11000]);
   zzzz=((zzz&0x1F0)>>4)<<2;			// X Offset (16-511)
   x16=zzz&15;					// X Offset (0-15)
   zzz=ReadWord(&RAM[0x11002]);
   zzzz|=((zzz&0x1F0)>>4)<<7;			// Y Offset (16-511)
   y16=zzz&15;					// Y Offset (0-15)

   zzzz&=0xFFF;
   zz=zzzz;

   for(y=24-y16;y<256+24;y+=16){
   for(x=32-x16;x<320+32;x+=16){

      ta=ReadWord(&RAM[zz+0x4002])&0x1FFF;
      if( GFX_BG0_SOLID[ta] && ta){

         MAP_PALETTE_MAPPED_NEW(
            (RAM[zz+0x4000]&15)|0x10,
            16,
            MAP
         );

         if(GFX_BG0_SOLID[ta]==1){
            if((RAM[zz+0x4000]&0x40)==0){Draw16x16_Trans_Mapped_Rot(&GFX[(ta<<8)],x,y,MAP);}
            else{                        Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[(ta<<8)],x,y,MAP);}
         }
         else{
            if((RAM[zz+0x4000]&0x40)==0){Draw16x16_Mapped_Rot(&GFX[(ta<<8)],x,y,MAP);}
            else{                        Draw16x16_Mapped_FlipY_Rot(&GFX[(ta<<8)],x,y,MAP);}
         }

      }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zzzz=(zzzz+0x80)&0xFFF;
   zz=zzzz;
   }

   for(zz=0x5000;zz<0x5800;zz+=16){

      if(((td=RAM[zz+2])&1)!=0){

      x=(RAM[zz+10]+((td&4)<<6))+32;

      if(x>(320+32)){
         x-=512;
      }

      if((x>16)&&(x<320+32)){

         y=(RAM[zz]+((td&2)<<7));

         y=(256+8-y)&0x1FF;

         ta=((RAM[zz+6]<<8)|(RAM[zz+4]))&0x7FFF;

         MAP_PALETTE_MAPPED_NEW(
            (RAM[zz+8])&15,
            16,
            MAP
         );

         tb=(td>>5);

         switch(td&0x18){
            case 0x00:
               for(td=0;td<=tb;td++){
               if((y>16)&&(y<256+32)){
               Draw16x16_Trans_Mapped_Rot(&GFX[0x200000+(ta<<8)],x,y,MAP);
               }
               ta++;
               y-=16;
               }
            break;
            case 0x10:
               for(td=0;td<=tb;td++){
               if((y>16)&&(y<256+32)){
               Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[0x200000+(ta<<8)],x,y,MAP);
               }
               ta++;
               y-=16;
               }
            break;
            case 0x08:
               y-=(tb<<4);
               for(td=0;td<=tb;td++){
               if((y>16)&&(y<256+32)){
               Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[0x200000+(ta<<8)],x,y,MAP);
               }
               ta++;
               y+=16;
               }
            break;
            case 0x18:
               y-=(tb<<4);
               for(td=0;td<=tb;td++){
               if((y>16)&&(y<256+32)){
               Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[0x200000+(ta<<8)],x,y,MAP);
               }
               ta++;
               y+=16;
               }
            break;
         }

      }

      }
   }
}

/*

SPRITE RAM
----------

- 16 bytes/sprite (only odd bytes used)

Byte | Bit(s) | Usage
-----+76543210+-------------------
  1  |xxxxxxxx| Sprite Y (low)
  3  |.......x| Sprite Enable
  3  |......x.| Sprite Y (high)
  3  |.....x..| Sprite X (high)
  3  |....x...| Sprite Flip Y
  3  |...x....| Sprite Flip X
  3  |xxx.....| Sprite Chain
  5  |xxxxxxxx| Sprite Number (low)
  7  |..xxxxxx| Sprite Number (high)
  9  |....xxxx| Sprite Palette
  B  |xxxxxxxx| Sprite X (low)
  D  |........| Unused
  F  |........| Unused

*/
static struct VIDEO_INFO video_ctribe =
{
   DrawCombaTribes,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ctribe[] =
{
   { "combatribes", },
   { "ctribe", },
   { NULL, },
};
GME( ctribe, "Combatribes", TECHNOS, 1990, GAME_BEAT,
	.long_name_jpn = "ザ・コンバットライブス",
	.board = "TA-0028",
);
static struct DIR_INFO dir_ctribeb[] =
{
   { "combatribes_bootleg", },
   { "ctribebl", },
   { "ctribeb", },
   { ROMOF("ctribe"), },
   { CLONEOF("ctribe"), },
   { NULL, },
};
CLNE( ctribeb, ctribe, "Combatribes (bootleg)", BOOTLEG, 1990, GAME_BEAT,
	.long_name_jpn = "ザ・コンバットライブス (bootleg)",
	.board = "TA-0028",
);

