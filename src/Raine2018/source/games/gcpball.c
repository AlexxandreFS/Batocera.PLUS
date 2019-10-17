/******************************************************************************/
/*                                                                            */
/*               GRAND CROSS PINBALL (C) 1994 EXCELLENT SYSTEM                */
/*                                                                            */
/******************************************************************************/
/* Stephh's notes (based on the game M68000 code and some tests) :
 *
 *   - Reset the game while pressing START1 to enter the "test mode"
 */

#include "gameinc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "m6585.h"
#include "adpcm.h"
#include "savegame.h"

/*

Todo:

- M6295 should have a bankswitch
- Some gfx I wonder about (the shadow thing when launching a ball)

*/


static struct ROM_INFO rom_gcpinbal[] =
{
   {           "u1", 0x00100000, 0xafa459bb, 0, 0, 0, },
   {        "u10.1", 0x00020000, 0x79321550, 0, 0, 0, },
   {          "u13", 0x00200000, 0x62f3952f, 0, 0, 0, },
   {        "u43.2", 0x00080000, 0xd174bd7f, 0, 0, 0, },
   {        "u45.3", 0x00080000, 0x0511ad56, 0, 0, 0, },
   {        "u46.4", 0x00080000, 0xe0f3a1b4, 0, 0, 0, },
   {          "u55", 0x00080000, 0xb3063351, 0, 0, 0, },
   {          "u56", 0x00200000, 0x092b2c0f, 0, 0, 0, },
   {           "u6", 0x00100000, 0xc3f024e5, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_gcpinbal[] =
{
   INP0( COIN1, 0x016087, 0x01 ),
   INP0( COIN2, 0x016087, 0x02 ),

   INP0( SERVICE, 0x016087, 0x08 ),

   INP0( P1_START, 0x016085, 0x80 ),
   INP0( P2_START, 0x016084, 0x80 ),

   INP0( FLIPPER_1_L, 0x016085, 0x10 ),
   INP0( FLIPPER_1_R, 0x016084, 0x10 ),

   INP0( FLIPPER_2_L, 0x016085, 0x20 ),
   INP0( FLIPPER_2_R, 0x016084, 0x20 ),

   INP0( TILT_L, 0x016085, 0x40 ),
   INP0( TILT_R, 0x016084, 0x40 ),

   INP0( B1_L, 0x016085, 0x08 ),
   INP0( B1_R, 0x016084, 0x08 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_grand_cross_pinball_0[] =
{
   { MSG_COIN1,               0x07, 0x07 },
   { MSG_4COIN_1PLAY,         0x02},
   { MSG_3COIN_1PLAY,         0x03},
   { MSG_2COIN_1PLAY,         0x04},
   { _("2 Coins/1 Credit 3/2 4/3 6/5"), 0x01},
   { MSG_1COIN_1PLAY,         0x07},
   { _("1 Coin/1 Credit 2/3"),   0x05},
   { _("1 Coin/1 Credit 5/6"),   0x00},
   { MSG_1COIN_2PLAY,         0x06},
   { MSG_COIN2,               0x38, 0x07 },
   { MSG_4COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x18},
   { MSG_2COIN_1PLAY,         0x20},
   { _("2 Coins/1 Credit 3/2 4/3 6/5"), 0x08},
   { MSG_1COIN_1PLAY,         0x38},
   { _("1 Coin/1 Credit 2/3"),   0x28},
   { _("1 Coin/1 Credit 5/6"),   0x00},
   { MSG_1COIN_2PLAY,         0x30},
   { _("Lives"),                 0xC0, 0x04 },
   { "2",                     0x00},
   { "3",                     0xC0},
   { "4",                     0x80},
   { "5",                     0x40},
};

static struct DSW_DATA dsw_data_grand_cross_pinball_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("300K"),                  0x04},
   { _("500K"),                  0x08},
   { _("1000K"),                 0x0C},
   { _("none"),                  0x00},
   DSW_SCREEN( 0x10, 0x00),
   DSW_UNUSED( 0x00, 0x20),
   DSW_DEMO_SOUND( 0x40, 0x00),
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_gcpinbal[] =
{
   { 0x016080, 0xFF, dsw_data_grand_cross_pinball_0 },
   { 0x016081, 0xFF, dsw_data_grand_cross_pinball_1 },
   { 0,        0,    NULL,      },
};


static struct OKIM6295interface m6295_interface =
{
	1,                  /* 1 chip */
	{ 8000 },			/* 8000 KHz? */
	{ 0 },  /* memory region (not yet !) */
	{ 30 }				/* volume */
};

static struct M6585_ROM m6585_romlist_chip_a[] =
{
   { NULL, 0x100000, },		// Bank 0
   { NULL, 0x100000, },		// Bank 1
   { NULL,        0, },		// Terminator
};

static struct M6585_interface m6585_interface =
{
   1,					// 1 chip
   { 8000 },				// rate
   { m6585_romlist_chip_a },		// rom list
};

static struct SOUND_INFO sound_gcpinbal[] =
{
   { SOUND_M6295,   &m6295_interface,     },
   { SOUND_M6585,   &m6585_interface,     },
   { 0,             NULL,                 },
};


static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_FG0;
static UINT8 *GFX_FG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

/******************************************************************************/
/*  I/O CONTROLLER                                                            */
/******************************************************************************/

static void grand_cross_pinball_ioc_wb(UINT32 offset, UINT8 data)
{
   offset &= 0x00FF;
   switch(offset){
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1A:
      case 0x1B:
      case 0x1C:
      case 0x1D:
      case 0x1E:
      case 0x1F:
      case 0x20:
      case 0x21:
         RAM[0x16000+(offset^1)] = data;	// Scroll
      break;
      case 0x60:
      case 0x61:
      case 0x62:
      case 0x63:
      case 0x64:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x76:
      case 0x77:
         RAM[0x16000+(offset^1)] = data;	// ?
      break;
      case 0x88:
         RAM[0x16000+(offset^1)] = data;

         switch_led(2, (data>>0)&1 );		// Coin A [Ready for coins]
         //switch_led(3, (data>>1)&1 );		// Coin B [Ready for coins]

         M6585buffer_bank_write(0, (data>>4)&1 );
      break;
      case 0xA0:
      case 0xA1:
      case 0xA2:
      case 0xA3:
	OKIM6295_data_0_w(0,data&0xFF); // M6295buffer_request
      break;
      case 0xC0:
      case 0xC1:
      case 0xC2:
      case 0xC3:
      case 0xC4:
      case 0xC5:
      case 0xC6:
      case 0xC7:
      case 0xC8:
      case 0xC9:
      case 0xCA:
      case 0xCB:
      case 0xCC:
      case 0xCD:
         M6585buffer_request(0, (offset>>1)&7, data&0xFF);
      break;
      default:
         print_debug("IOC: %02x %02x\n",offset,data);
      break;
   }
}

static void grand_cross_pinball_ioc_ww(UINT32 offset, UINT16 data)
{
   grand_cross_pinball_ioc_wb(offset+0, (UINT8) ((data>>8)&0xFF) );
   grand_cross_pinball_ioc_wb(offset+1, (UINT8) ((data>>0)&0xFF) );
}

static UINT8 grand_cross_pinball_ioc_rb(UINT32 offset)
{
   offset &= 0x00FF;
   switch(offset){
      case 0xA0:
      case 0xA1:
      case 0xA2:
      case 0xA3:
         return OKIM6295_status_0_r(0);                  ;
         //return 0;
      break;
      default:
         return RAM[0x16000+(offset^1)];
      break;
   }
}

static UINT16 grand_cross_pinball_ioc_rw(UINT32 offset)
{
   UINT16 ret;

   ret  = grand_cross_pinball_ioc_rb(offset+0)<<8;
   ret |= grand_cross_pinball_ioc_rb(offset+1)<<0;

   return ret;
}

#define RAMSize 0x16200

static void load_gcpinbal(void)
{
   int ta,tb,tc;

   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x840000))) return;

   GFX_BG0 = GFX+0x000000;

   if(!load_rom("u1", ROM+0x000000, 0x100000)) return;		// GFX BG0
   if(!load_rom("u6", ROM+0x100000, 0x100000)) return;		// GFX BG0
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[ta+ta+0]=ROM[ta+1]>>4;
      GFX_BG0[ta+ta+1]=ROM[ta+1]&15;
      GFX_BG0[ta+ta+2]=ROM[ta+0]>>4;
      GFX_BG0[ta+ta+3]=ROM[ta+0]&15;
   }

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);

   GFX_FG0 = GFX+0x800000;

   if(!load_rom("u10.1", ROM+0x00000, 0x20000)) return;		// GFX FG0
   for(ta=0;ta<0x20000;ta+=2){
      GFX_FG0[ta+ta+0]=ROM[ta+1]>>4;
      GFX_FG0[ta+ta+1]=ROM[ta+1]&15;
      GFX_FG0[ta+ta+2]=ROM[ta+0]>>4;
      GFX_FG0[ta+ta+3]=ROM[ta+0]&15;
   }

   GFX_FG0_SOLID = make_solid_mask_8x8(GFX_FG0, 0x1000);

   GFX_SPR = GFX+0x400000;

   if(!load_rom("u13", ROM+0x000000, 0x200000)) return;		// GFX SPR
   tb=0;
   for(ta=0;ta<0x200000;ta+=8){
      tc=ReadWord(&ROM[ta+0]);
      GFX_SPR[tb+0] =((tc&0x8000)>>15)<<0;
      GFX_SPR[tb+1] =((tc&0x4000)>>14)<<0;
      GFX_SPR[tb+2] =((tc&0x2000)>>13)<<0;
      GFX_SPR[tb+3] =((tc&0x1000)>>12)<<0;
      GFX_SPR[tb+4] =((tc&0x0800)>>11)<<0;
      GFX_SPR[tb+5] =((tc&0x0400)>>10)<<0;
      GFX_SPR[tb+6] =((tc&0x0200)>> 9)<<0;
      GFX_SPR[tb+7] =((tc&0x0100)>> 8)<<0;
      GFX_SPR[tb+8] =((tc&0x0080)>> 7)<<0;
      GFX_SPR[tb+9] =((tc&0x0040)>> 6)<<0;
      GFX_SPR[tb+10]=((tc&0x0020)>> 5)<<0;
      GFX_SPR[tb+11]=((tc&0x0010)>> 4)<<0;
      GFX_SPR[tb+12]=((tc&0x0008)>> 3)<<0;
      GFX_SPR[tb+13]=((tc&0x0004)>> 2)<<0;
      GFX_SPR[tb+14]=((tc&0x0002)>> 1)<<0;
      GFX_SPR[tb+15]=((tc&0x0001)>> 0)<<0;
      tc=ReadWord(&ROM[ta+4]);
      GFX_SPR[tb+0] |=((tc&0x8000)>>15)<<1;
      GFX_SPR[tb+1] |=((tc&0x4000)>>14)<<1;
      GFX_SPR[tb+2] |=((tc&0x2000)>>13)<<1;
      GFX_SPR[tb+3] |=((tc&0x1000)>>12)<<1;
      GFX_SPR[tb+4] |=((tc&0x0800)>>11)<<1;
      GFX_SPR[tb+5] |=((tc&0x0400)>>10)<<1;
      GFX_SPR[tb+6] |=((tc&0x0200)>> 9)<<1;
      GFX_SPR[tb+7] |=((tc&0x0100)>> 8)<<1;
      GFX_SPR[tb+8] |=((tc&0x0080)>> 7)<<1;
      GFX_SPR[tb+9] |=((tc&0x0040)>> 6)<<1;
      GFX_SPR[tb+10]|=((tc&0x0020)>> 5)<<1;
      GFX_SPR[tb+11]|=((tc&0x0010)>> 4)<<1;
      GFX_SPR[tb+12]|=((tc&0x0008)>> 3)<<1;
      GFX_SPR[tb+13]|=((tc&0x0004)>> 2)<<1;
      GFX_SPR[tb+14]|=((tc&0x0002)>> 1)<<1;
      GFX_SPR[tb+15]|=((tc&0x0001)>> 0)<<1;
      tc=ReadWord(&ROM[ta+2]);
      GFX_SPR[tb+0] |=((tc&0x8000)>>15)<<2;
      GFX_SPR[tb+1] |=((tc&0x4000)>>14)<<2;
      GFX_SPR[tb+2] |=((tc&0x2000)>>13)<<2;
      GFX_SPR[tb+3] |=((tc&0x1000)>>12)<<2;
      GFX_SPR[tb+4] |=((tc&0x0800)>>11)<<2;
      GFX_SPR[tb+5] |=((tc&0x0400)>>10)<<2;
      GFX_SPR[tb+6] |=((tc&0x0200)>> 9)<<2;
      GFX_SPR[tb+7] |=((tc&0x0100)>> 8)<<2;
      GFX_SPR[tb+8] |=((tc&0x0080)>> 7)<<2;
      GFX_SPR[tb+9] |=((tc&0x0040)>> 6)<<2;
      GFX_SPR[tb+10]|=((tc&0x0020)>> 5)<<2;
      GFX_SPR[tb+11]|=((tc&0x0010)>> 4)<<2;
      GFX_SPR[tb+12]|=((tc&0x0008)>> 3)<<2;
      GFX_SPR[tb+13]|=((tc&0x0004)>> 2)<<2;
      GFX_SPR[tb+14]|=((tc&0x0002)>> 1)<<2;
      GFX_SPR[tb+15]|=((tc&0x0001)>> 0)<<2;
      tc=ReadWord(&ROM[ta+6]);
      GFX_SPR[tb+0] |=((tc&0x8000)>>15)<<3;
      GFX_SPR[tb+1] |=((tc&0x4000)>>14)<<3;
      GFX_SPR[tb+2] |=((tc&0x2000)>>13)<<3;
      GFX_SPR[tb+3] |=((tc&0x1000)>>12)<<3;
      GFX_SPR[tb+4] |=((tc&0x0800)>>11)<<3;
      GFX_SPR[tb+5] |=((tc&0x0400)>>10)<<3;
      GFX_SPR[tb+6] |=((tc&0x0200)>> 9)<<3;
      GFX_SPR[tb+7] |=((tc&0x0100)>> 8)<<3;
      GFX_SPR[tb+8] |=((tc&0x0080)>> 7)<<3;
      GFX_SPR[tb+9] |=((tc&0x0040)>> 6)<<3;
      GFX_SPR[tb+10]|=((tc&0x0020)>> 5)<<3;
      GFX_SPR[tb+11]|=((tc&0x0010)>> 4)<<3;
      GFX_SPR[tb+12]|=((tc&0x0008)>> 3)<<3;
      GFX_SPR[tb+13]|=((tc&0x0004)>> 2)<<3;
      GFX_SPR[tb+14]|=((tc&0x0002)>> 1)<<3;
      GFX_SPR[tb+15]|=((tc&0x0001)>> 0)<<3;
      tb+=16;
   }

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   if(!(PCMROM=AllocateMem(0x280000))) return;
   if(!load_rom("u55", PCMROM+0x000000, 0x080000)) return;		// M6295
   if(!load_rom("u56", PCMROM+0x080000, 0x200000)) return;		// M6585
   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),PCMROM,0x40000);


   m6585_romlist_chip_a[0].data = PCMROM+0x080000;
   m6585_romlist_chip_a[1].data = PCMROM+0x180000;

   if(!load_rom("u43.2", ROM+0x000000, 0x80000)) return;	// BASE ROM
   memset(ROM+0x080000,0x00,0x080000);				// EMPTY ROM
   if(!load_rom("u45.3", ROM+0x100000, 0x80000)) return;	// DATA ROM
   if(!load_rom("u46.4", ROM+0x180000, 0x80000)) return;	// DATA ROM

   ByteSwap(ROM,0x200000);

   memset(RAM+0x00000,0x00,RAMSize);
   memset(RAM+0x16000,0xFF,0x00200);

   // eeprom save

   WriteLong68k(&ROM[0x31DD6],0x00BB0000);
   WriteLong68k(&ROM[0x31DDA],0x701F22D8);
   WriteLong68k(&ROM[0x31DDE],0x51C8FFFC);
   WriteWord68k(&ROM[0x31DE2],0x4E75);

   // eeprom load

   WriteLong68k(&ROM[0x31E2E],0x00BB0000);
   WriteLong68k(&ROM[0x31E32],0x701F20D9);
   WriteLong68k(&ROM[0x31E36],0x51C8FFFC);
   WriteWord68k(&ROM[0x31E3A],0x4E75);

   // speed hack

   WriteLong68k(&ROM[0x02A00],0x4EF80100);

   WriteLong68k(&ROM[0x00100],0x1200C239);
   WriteLong68k(&ROM[0x00104],0x00FF22EC);
   WriteLong68k(&ROM[0x00108],0xB101C200);

   WriteWord68k(&ROM[0x0010C],0x6606);

   WriteLong68k(&ROM[0x0010E],0x4CDF0003);
   WriteWord68k(&ROM[0x00112],0x4E75);

   WriteLong68k(&ROM[0x00114],0x13FC0000);
   WriteLong68k(&ROM[0x00118],0x00AA0000);

   WriteLong68k(&ROM[0x0011C],0x4EF80100);

   // scroll sync

   WriteLong68k(&ROM[0x00A9E],0x00000180);

   WriteLong68k(&ROM[0x00180],0x13FC0000);
   WriteLong68k(&ROM[0x00184],0x00AA0000);

   WriteLong68k(&ROM[0x00188],0x4EF824AA);

   // skip cpu idling on sound writes

   WriteWord68k(&ROM[0x0BF7C],0x4E75);

   set_colour_mapper(&col_Map_15bit_RRRRGGGGBBBBRGBx);
   InitPaletteMap(RAM+0x15000, 0x80, 0x10, 0x8000);


   EEPROM=RAM+0x16100;

   add_eeprom(EEPROM, 0x80, EPR_INVALIDATE_ON_ROM_CHANGE);
   ta = load_eeprom();
   if(!ta) memset(EEPROM, 0x55, 0x80);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x200000);
   ByteSwap(RAM,RAMSize);

   AddMemFetch(0x000000, 0x1FFFFF, ROM+0x000000-0x000000);              // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x1FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0xFF0000, 0xFFFFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0xC00000, 0xC03FFF, NULL, RAM+0x010000);                 // BG0/BG1/FG0 RAM
   AddReadByte(0xC80000, 0xC80FFF, NULL, RAM+0x014000);                 // ? RAM
   AddReadByte(0xD00000, 0xD00FFF, NULL, RAM+0x015000);                 // COLOR RAM
   AddReadByte(0xD80000, 0xD800FF, grand_cross_pinball_ioc_rb, NULL);   // I/O
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x1FFFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0xFF0000, 0xFFFFFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0xC00000, 0xC03FFF, NULL, RAM+0x010000);                 // BG0/BG1/FG0 RAM
   AddReadWord(0xC80000, 0xC80FFF, NULL, RAM+0x014000);                 // ? RAM
   AddReadWord(0xD00000, 0xD00FFF, NULL, RAM+0x015000);                 // COLOR RAM
   AddReadWord(0xD80000, 0xD800FF, grand_cross_pinball_ioc_rw, NULL);   // I/O
   AddReadWord(0xBB0000, 0xBB007F, NULL, EEPROM);                       // EEPROM FAKE
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xFF0000, 0xFFFFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0xC00000, 0xC03FFF, NULL, RAM+0x010000);                // BG0/BG1/FG0 RAM
   AddWriteByte(0xC80000, 0xC80FFF, NULL, RAM+0x014000);                // ? RAM
   AddWriteByte(0xD00000, 0xD00FFF, NULL, RAM+0x015000);                // COLOR RAM
   AddWriteByte(0xD80000, 0xD800FF, grand_cross_pinball_ioc_wb, NULL);	// I/O
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xFF0000, 0xFFFFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0xC00000, 0xC03FFF, NULL, RAM+0x010000);                // BG0/BG1/FG0 RAM
   AddWriteWord(0xC80000, 0xC80FFF, NULL, RAM+0x014000);                // ? RAM
   AddWriteWord(0xD00000, 0xD00FFF, NULL, RAM+0x015000);                // COLOR RAM
   AddWriteWord(0xD80000, 0xD800FF, grand_cross_pinball_ioc_ww, NULL);	// I/O
   AddWriteWord(0xBB0000, 0xBB007F, NULL, EEPROM);                      // EEPROM FAKE
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void clear_grand_cross_pinball(void)
{
   save_eeprom();

#ifdef RAINE_DEBUG
   //save_debug("RAM.bin",RAM,RAMSize,1);
#endif
}

static void execute_gcpinbal(void)
{
   if(!M6585buffer_status(0))
      cpu_interrupt(CPU_68K_0, 3);

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(1,60));	// Scroll Sync
   cpu_interrupt(CPU_68K_0, 4);
}

static void draw_grand_cross_pinball_object(void)
{
   int rx;
   int x,y,zz;
   int ta;
   UINT8 *map;
   UINT8 *RAM_BG;

   // OBJECT

      RAM_BG = RAM + 0x14000;

      for(zz=0;zz<0x1000;zz+=0x10){

         if(!(RAM_BG[zz+14]&0x80)){

         x = (16 + ((RAM_BG[zz+6]<<8) | (RAM_BG[zz+4]<<0)))&0x7FFF;
         y = ((320 + 16) - ((RAM_BG[zz+2]<<8) | (RAM_BG[zz+0]<<0)))&0x7FFF;

            ta = ((RAM_BG[zz+12]<<8) | (RAM_BG[zz+10]<<0))&0x3FFF;

            MAP_PALETTE_MAPPED_NEW(
               (RAM_BG[zz+14]&0x0F) | 0x60,
               16,
               map
            );

            rx = (RAM_BG[zz+8]&0x07)+1;

            switch(RAM_BG[zz+8]&0x18){
            case 0x08:
               do{
                  if((x>16)&&(y>16)&&(x<224+32)&&(y<320+32)){
                  if(GFX_SPR_SOLID[ta]!=0){
                  if(GFX_SPR_SOLID[ta]==1)
                     Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  else
                     Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  }
                  }
                  ta++;
                  x = (x+16)&0x7FFF;
               }while(--rx);
            break;
            case 0x18:
               x += ((rx-1)<<4);
               x &= 0x7FFF;
               do{
                  if((x>16)&&(y>16)&&(x<224+32)&&(y<320+32)){
                  if(GFX_SPR_SOLID[ta]!=0){
                  if(GFX_SPR_SOLID[ta]==1)
                     Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  else
                     Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  }
                  }
                  ta++;
                  x = (x-16)&0x7FFF;
               }while(--rx);
            break;
            case 0x00:
               //y -= ((rx-1)<<4);
               //y &= 0x7FFF;
               do{
                  if((x>16)&&(y>16)&&(x<224+32)&&(y<320+32)){
                  if(GFX_SPR_SOLID[ta]!=0){
                  if(GFX_SPR_SOLID[ta]==1)
                     Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  else
                     Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  }
                  }
                  ta++;
                  y = (y-16)&0x7FFF;
               }while(--rx);
            break;
            case 0x10:
               do{
                  if((x>16)&&(y>16)&&(x<224+32)&&(y<320+32)){
                  if(GFX_SPR_SOLID[ta]!=0){
                  if(GFX_SPR_SOLID[ta]==1)
                     Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  else
                     Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],320+48-y,x,map);
                  }
                  }
                  ta++;
                  y = (y-16)&0x7FFF;
               }while(--rx);
            break;
            }

         }
      }
}

static void draw_grand_cross_pinball(void)
{
   int x16,y16;
   int x,y,zz,zzz,zzzz;
   int ta;
   UINT8 *map;
   UINT8 *GFX_BG;
   UINT8 *MSK_BG;
   UINT8 *RAM_BG;

   ClearPaletteMap();

   // BG0

   //if(bg0){

      RAM_BG = RAM + 0x10000;

      if(!(ReadWord(&RAM[0x16088])&0x0400)){
         GFX_BG = GFX_BG0+0x000000;
         MSK_BG = GFX_BG0_SOLID+0x0000;
      }
      else{
         GFX_BG = GFX_BG0+0x100000;
         MSK_BG = GFX_BG0_SOLID+0x1000;
      }

      MAKE_SCROLL_512x512_4_16(
         ReadWord(&RAM[0x16014]),
         ReadWord(&RAM[0x16016])+0x10
      );

      START_SCROLL_512x512_4_16(32,32,320,224);

      ta=ReadWord(&RAM_BG[zz+0])&0x0FFF;

      MAP_PALETTE_MAPPED_NEW(
         (ReadWord(&RAM_BG[zz+2])&0x1F)+0x00,
         16,
         map
      );

      switch(ReadWord(&RAM_BG[zz+2])&0x0300){
      case 0x0000: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8],x,y,map); break;
      case 0x0100: Draw16x16_Mapped_FlipY_Rot(&GFX_BG[ta<<8],x,y,map); break;
      case 0x0200: Draw16x16_Mapped_FlipX_Rot(&GFX_BG[ta<<8],x,y,map); break;
      case 0x0300: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG[ta<<8],x,y,map); break;
      }

      END_SCROLL_512x512_4_16();
   //}

   if(!(ReadWord(&RAM[0x16068])&0x8800))
      draw_grand_cross_pinball_object();

   // BG1

   //if(bg1){

      RAM_BG = RAM + 0x11000;

      if(!(ReadWord(&RAM[0x16088])&0x0800)){
         GFX_BG = GFX_BG0+0x200000;
         MSK_BG = GFX_BG0_SOLID+0x2000;
      }
      else{
         GFX_BG = GFX_BG0+0x300000;
         MSK_BG = GFX_BG0_SOLID+0x3000;
      }

      MAKE_SCROLL_512x512_4_16(
         ReadWord(&RAM[0x16018]),
         ReadWord(&RAM[0x1601A])+0x10
      );

      START_SCROLL_512x512_4_16(32,32,320,224);

      ta=ReadWord(&RAM_BG[zz+0])&0x0FFF;
      if(MSK_BG[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (ReadWord(&RAM_BG[zz+2])&0x1F)+0x30,
            16,
            map
         );

         if(MSK_BG[ta]==1){			// Some pixels; trans
            switch(ReadWord(&RAM_BG[zz+2])&0x0300){
            case 0x0000: Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8],x,y,map); break;
            case 0x0100: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG[ta<<8],x,y,map); break;
            case 0x0200: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG[ta<<8],x,y,map); break;
            case 0x0300: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(ReadWord(&RAM_BG[zz+2])&0x0300){
            case 0x0000: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8],x,y,map); break;
            case 0x0100: Draw16x16_Mapped_FlipY_Rot(&GFX_BG[ta<<8],x,y,map); break;
            case 0x0200: Draw16x16_Mapped_FlipX_Rot(&GFX_BG[ta<<8],x,y,map); break;
            case 0x0300: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG[ta<<8],x,y,map); break;
            }
         }
      }

      END_SCROLL_512x512_4_16();
   //}

   if((ReadWord(&RAM[0x16068])&0x8800))
      draw_grand_cross_pinball_object();

   // FG0

   //if(bg2){

      RAM_BG = RAM + 0x12000;

      MAKE_SCROLL_512x512_2_8(
         ReadWord(&RAM[0x1601C]),
         ReadWord(&RAM[0x1601E])+0x10
      );

      START_SCROLL_512x512_2_8(32,32,320,224);

      ta=ReadWord(&RAM_BG[zz])&0x0FFF;
      if(GFX_FG0_SOLID[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (ReadWord(&RAM_BG[zz])>>12) | 0x70,
            16,
            map
         );

         if(GFX_FG0_SOLID[ta]==1)		// Some pixels; trans
            Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
         else					// all pixels; solid
            Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);

      }

      END_SCROLL_512x512_2_8();
   //}

}

/*

EXCELLENT SYSTEM - OBJECT RAM
-----------------------------

Byte | Bit(s) | Use
-----+76543210+-----------------
  0  |xxxxxxxx| X (low)
  2  |xxxxxxxx| X (high)
  4  |xxxxxxxx| Y (low)
  6  |xxxxxxxx| Y (high)
  E  |...x....| Flip X
  E  |....x...| Flip Y
  E  |.....xxx| Chain
  A  |xxxxxxxx| Tile (low)
  C  |xxxxxxxx| Tile (high)
  E  |x.......| Disable
  E  |....xxxx| Colour Bank

*/
static struct VIDEO_INFO video_gcpinbal =
{
   draw_grand_cross_pinball,
   320,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_gcpinbal[] =
{
   { "grand_cross_pinball", },
   { "gcpball", },
   { "gcpinbal", },
   { NULL, },
};
GME( gcpinbal, "Grand Cross Pinball", EX_SYSTEM, 1994, GAME_MISC,
	.clear = clear_grand_cross_pinball,
	.long_name_jpn = "グランドクロスピンボール",
);

