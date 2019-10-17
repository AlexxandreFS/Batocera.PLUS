/******************************************************************************/
/*                                                                            */
/*                      CABAL (C) 1988 TAD CORPORATION                        */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "2151intf.h"
#include "smp16bit.h"
#include "sasound.h"		// sample support routines
#include "savegame.h"


static struct ROM_INFO rom_cabalbl[] =
{
/*
   { "cabal_01.bin", 0x00010000, 0x55c44764, 0, 0, 0, },
   { "cabal_02.bin", 0x00010000, 0x0e1ec30e, 0, 0, 0, },
   { "cabal_03.bin", 0x00010000, 0x7065e840, 0, 0, 0, },
   { "cabal_04.bin", 0x00010000, 0x34d3cac8, 0, 0, 0, },
   { "cabal_05.bin", 0x00010000, 0x4e49c28e, 0, 0, 0, },
   { "cabal_08.bin", 0x00010000, 0x702735c9, 0, 0, 0, },
   { "cabal_07.bin", 0x00010000, 0x581a50c1, 0, 0, 0, },
   { "cabal_06.bin", 0x00010000, 0x6a0e739d, 0, 0, 0, },
*/
   { "tad-1.5e", 0x00080000, 0x8324a7fe, 0, 0, 0, },
   { "cabal_09.bin", 0x00010000, 0x4ffa7fe3, 0, 0, 0, },
   { "cabal_10.bin", 0x00010000, 0x958789b6, 0, 0, 0, },
   { "cabal_11.bin", 0x00010000, 0xd308a543, 0, 0, 0, },
/*
   { "cabal_12.bin", 0x00010000, 0x543fcb37, 0, 0, 0, },
   { "cabal_13.bin", 0x00010000, 0xd28d921e, 0, 0, 0, },
   { "cabal_14.bin", 0x00010000, 0x420b0801, 0, 0, 0, },
   { "cabal_15.bin", 0x00010000, 0x1023319b, 0, 0, 0, },
   { "cabal_16.bin", 0x00010000, 0x77bc7a60, 0, 0, 0, },
   { "cabal_17.bin", 0x00010000, 0x3b6d2b09, 0, 0, 0, },
   { "cabal_18.bin", 0x00010000, 0x0bc50075, 0, 0, 0, },
   { "cabal_19.bin", 0x00010000, 0x67e4fe47, 0, 0, 0, },
*/
   { "tad-2.7s", 0x00080000, 0x13ca7ae1, 0, 0, 0, },
   { "cabal_21.bin", 0x00010000, 0x96d5e8af, 0, 0, 0, },
   { "cabal_22.bin", 0x00010000, 0x78c4af27, 0, 0, 0, },
   { "cabal_23.bin", 0x00010000, 0xd763a47c, 0, 0, 0, },
   { "cabal_24.bin", 0x00010000, 0x00abbe0c, 0, 0, 0, },
   {         "5-6s", 0x00004000, 0x6a76955a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_cabalbl[] =
{
   INP0( COIN1, 0x005404, 0x06 ),

   INP0( P1_START, 0x005421, 0x80 ),
   INP0( P1_UP, 0x005419, 0x01 ),
   INP0( P1_DOWN, 0x005419, 0x02 ),
   INP0( P1_LEFT, 0x005419, 0x04 ),
   INP0( P1_RIGHT, 0x005419, 0x08 ),
   INP0( P1_B1, 0x005420, 0x01 ),
   INP0( P1_B2, 0x005420, 0x02 ),
   INP0( P1_B3, 0x005421, 0x20 ),

   INP0( P2_START, 0x005421, 0x40 ),
   INP0( P2_UP, 0x005419, 0x10 ),
   INP0( P2_DOWN, 0x005419, 0x20 ),
   INP0( P2_LEFT, 0x005419, 0x40 ),
   INP0( P2_RIGHT, 0x005419, 0x80 ),
   INP0( P2_B1, 0x005420, 0x04 ),
   INP0( P2_B2, 0x005420, 0x08 ),
   INP0( P2_B3, 0x005421, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_cabal_0[] =
{
   { MSG_COIN_SLOTS,          0x0F, 0x07 },
   { MSG_1COIN_1PLAY,         0x0F},
   { MSG_2COIN_1PLAY,         0x0E},
   { MSG_3COIN_1PLAY,         0x0D},
   { MSG_4COIN_1PLAY,         0x0C},
   { MSG_5COIN_1PLAY,         0x0B},
   { MSG_6COIN_1PLAY,         0x0A},
   { MSG_1COIN_2PLAY,         0x09},
   { MSG_FREE_PLAY,              0x00},
   { _("Coin Mode"),             0x10, 0x02 },
   { _("Type 1"),                0x10},
   { _("Type 2"),                0x00},
   { _("Buttons"),               0x20, 0x02 },
   { MSG_NORMAL,              0x20},
   { MSG_INVERT,              0x00},
   { _("Trackball"),             0x80, 0x02 },
   { _("Small"),                 0x80},
   { _("Large"),                 0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_cabal_1[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "3",                     0x03},
   { "2",                     0x02},
   { "5",                     0x01},
   { _("Infinite"),              0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("20k and 50k"),           0x0C},
   { _("30k and 100k"),          0x08},
   { _("50k and 150k"),          0x04},
   { _("70k"),                   0x00},
   { MSG_DIFFICULTY,          0x30, 0x04 },
   { MSG_EASY,                0x30},
   { MSG_NORMAL,              0x20},
   { MSG_HARD,                0x10},
   { MSG_HARDEST,             0x00},
   { MSG_DEMO_SOUND,          0x80, 0x02 },
   { MSG_ON,                  0x80},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_cabalbl[] =
{
   { 0x005410, 0xFF, dsw_data_cabal_0 },
   { 0x005411, 0xFF, dsw_data_cabal_1 },
   { 0,        0,    NULL,      },
};


static struct SMP16_ROM smp16_romlist_chip_a[16];	// Fill in later

static struct SMP16_ROM smp16_romlist_chip_b[16];	// Fill in later

static struct SMP16buffer_interface smp16_interface =
{
   2,					// 2 chips
   { 22000,
     22000 },				// rate
   { smp16_romlist_chip_a,
     smp16_romlist_chip_b },		// rom list
};

static struct YM2151interface ym2151_interface =
{
   1,			// 1 chip
   3579580, // 4000000,		// 4 MHz
   { YM3012_VOL(255,OSD_PAN_LEFT,255,OSD_PAN_RIGHT) },
   { NULL } //z80_irq_handler }
};

static struct SOUND_INFO sound_cabalbl[] =
{
   { SOUND_YM2151J, &ym2151_interface,    },
   { SOUND_SMP16,   &smp16_interface,     },
   { 0,             NULL,                 },
};


static int sp_status=0xFF;

static void CabalSoundWrite68k(UINT32 offset, UINT8 data)
{
   switch(offset&15){
      case 0x01:
         latch=data;
         sp_status=1;
            print_debug("68000 Sends:%02x\n",latch);
      break;
   }
}

static UINT8 CabalSoundRead68k(UINT32 offset)
{
   int ret;

   switch(offset&15){
      case 0x05:
         ret = RAM[0x5404];
      break;
      default:
         ret = 0xFF;
      break;
   }

   return ret;
}


UINT8 CabalSoundReadZ80(UINT16 offset)
{
   UINT8 ta;

   switch(offset&15){
      case 0x08:
         ta=sp_status;
      break;
      case 0x0A:
         sp_status=0xFF;
         ta=latch;
            print_debug("Z80 Receives:%02x\n",latch);
      break;
      default:
         ta=0xFF;
      break;
   }

   print_debug("Z80Read:%04x,%02x [%04x]\n",offset,ta,z80pc);
   return(ta);
}

static void CabalSoundWriteZ80(UINT16 offset, UINT8 data)
{
   switch(offset&15){
      case 0x00:
         data&=0x7F;
         if((data>0)&&(data<16)) SMP16buffer_request(0,data-1);
      break;
      case 0x02:
         data&=0x7F;
         if((data>0)&&(data<16)) SMP16buffer_request(1,data-1);
      break;
      default:
         print_debug("Z80Write:%04x,%02x [%04x]\n",offset,data,z80pc);
      break;
   }
}

static void load_cabalbl(void)
{
   int ta,tb,tc;

   if(!(ROM=AllocateMem(0x40000))) return;
   if(!(RAM=AllocateMem(0x100000))) return;
   if(!(GFX=AllocateMem(0x210000))) return;

   if(!load_rom("5-6s", RAM, 0x4000)) return;		// FG0 GFX (2 bitplanes)
   tb=0;
   for(ta=0;ta<0x4000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      GFX[tb+3]|=0x0C;
      GFX[tb+2]|=0x0C;
      GFX[tb+1]|=0x0C;
      GFX[tb+0]|=0x0C;
      tb+=4;
   }
/*
   if(!load_rom("cabal_01.bin",&RAM[0x30000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_02.bin",&RAM[0x20000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_03.bin",&RAM[0x10000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_04.bin",&RAM[0x00000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_08.bin",&RAM[0x70000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_07.bin",&RAM[0x60000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_06.bin",&RAM[0x50000],0x10000)) return;	// SPR GFX
   if(!load_rom("cabal_05.bin",&RAM[0x40000],0x10000)) return;	// SPR GFX
*/
   if(!load_rom("tad-1.5e",&RAM[0x80000],0x80000)) return;	// SPR GFX
   for(ta=0;ta<0x10000;ta++){
      RAM[0x30000+ta]=RAM[0xe0000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x20000+ta]=RAM[0xc0000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x10000+ta]=RAM[0xa0000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x00000+ta]=RAM[0x80000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x40000+ta]=RAM[0x80000+ta+ta+1];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x50000+ta]=RAM[0xa0000+ta+ta+1];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x60000+ta]=RAM[0xc0000+ta+ta+1];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x70000+ta]=RAM[0xe0000+ta+ta+1];
   }

   tb=0x10000;
   for(ta=0;ta<0x40000;ta++){
      tc=RAM[ta];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+0x40000];
      GFX[tb+3]|=((tc&0x80)>>7)<<3;
      GFX[tb+2]|=((tc&0x40)>>6)<<3;
      GFX[tb+1]|=((tc&0x20)>>5)<<3;
      GFX[tb+0]|=((tc&0x10)>>4)<<3;
      GFX[tb+3]|=((tc&0x08)>>3)<<2;
      GFX[tb+2]|=((tc&0x04)>>2)<<2;
      GFX[tb+1]|=((tc&0x02)>>1)<<2;
      GFX[tb+0]|=((tc&0x01)>>0)<<2;
      tb+=4;
   }
/*
   if(!load_rom("cabal_12.bin",&RAM[0x20000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_13.bin",&RAM[0x30000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_14.bin",&RAM[0x10000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_15.bin",&RAM[0x00000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_18.bin",&RAM[0x60000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_19.bin",&RAM[0x70000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_16.bin",&RAM[0x50000],0x10000)) return;	// BG0 GFX
   if(!load_rom("cabal_17.bin",&RAM[0x40000],0x10000)) return;	// BG0 GFX
*/
   if(!load_rom("tad-2.7s",&RAM[0x80000],0x80000)) return;	// SPR GFX
   for(ta=0;ta<0x10000;ta++){
      RAM[0x30000+ta]=RAM[0xe0000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x20000+ta]=RAM[0xc0000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x10000+ta]=RAM[0xa0000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x00000+ta]=RAM[0x80000+ta+ta];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x50000+ta]=RAM[0xa0000+ta+ta+1];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x40000+ta]=RAM[0x80000+ta+ta+1];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x60000+ta]=RAM[0xc0000+ta+ta+1];
   }
   for(ta=0;ta<0x10000;ta++){
      RAM[0x70000+ta]=RAM[0xe0000+ta+ta+1];
   }

   tb=0x110000;
   for(ta=0;ta<0x40000;ta+=2){
      tc=RAM[ta];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+0x40000];
      GFX[tb+3]|=((tc&0x80)>>7)<<3;
      GFX[tb+2]|=((tc&0x40)>>6)<<3;
      GFX[tb+1]|=((tc&0x20)>>5)<<3;
      GFX[tb+0]|=((tc&0x10)>>4)<<3;
      GFX[tb+3]|=((tc&0x08)>>3)<<2;
      GFX[tb+2]|=((tc&0x04)>>2)<<2;
      GFX[tb+1]|=((tc&0x02)>>1)<<2;
      GFX[tb+0]|=((tc&0x01)>>0)<<2;
      tb+=4;
      tc=RAM[ta+1];
      GFX[tb+3]=((tc&0x80)>>7)<<1;
      GFX[tb+2]=((tc&0x40)>>6)<<1;
      GFX[tb+1]=((tc&0x20)>>5)<<1;
      GFX[tb+0]=((tc&0x10)>>4)<<1;
      GFX[tb+3]|=((tc&0x08)>>3)<<0;
      GFX[tb+2]|=((tc&0x04)>>2)<<0;
      GFX[tb+1]|=((tc&0x02)>>1)<<0;
      GFX[tb+0]|=((tc&0x01)>>0)<<0;
      tc=RAM[ta+0x40001];
      GFX[tb+3]|=((tc&0x80)>>7)<<3;
      GFX[tb+2]|=((tc&0x40)>>6)<<3;
      GFX[tb+1]|=((tc&0x20)>>5)<<3;
      GFX[tb+0]|=((tc&0x10)>>4)<<3;
      GFX[tb+3]|=((tc&0x08)>>3)<<2;
      GFX[tb+2]|=((tc&0x04)>>2)<<2;
      GFX[tb+1]|=((tc&0x02)>>1)<<2;
      GFX[tb+0]|=((tc&0x01)>>0)<<2;
      tb+=12;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   for(ta=0;ta<0x210000;ta++){
      GFX[ta]^=15;
   }

   if(!load_rom("cabal_24.bin", RAM, 0x10000)) return;	// MAIN 68000
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("cabal_22.bin", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("cabal_23.bin", RAM, 0x10000)) return;	// MAIN 68000
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("cabal_21.bin", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x20000;
   if(!load_rom("cabal_11.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x0120]=0xD3;	// OUTA (AAh)
   Z80ROM[0x0121]=0xAA;	//

   SetStopZ80Mode2(0x0110);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x27FF, NULL,                  	Z80ROM+0x0000);	// Z80 ROM/RAM
   AddZ80AReadByte(0x400E, 0x400F, YM2151ReadZ80,         	NULL);		// YM2151 I/O
   AddZ80AReadByte(0x4000, 0x400D, CabalSoundReadZ80,     	NULL);		// 68000 + OTHER I/O
   AddZ80AReadByte(0x8000, 0xFFFF, NULL,			Z80ROM+0x8000);	// MORE ROM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x2000, 0x27FF, NULL,                   	Z80ROM+0x2000);	// Z80 RAM
   AddZ80AWriteByte(0x400E, 0x400F, YM2151WriteZ80,         	NULL);		// YM2151 I/O
   AddZ80AWriteByte(0x4000, 0x400D, CabalSoundWriteZ80,     	NULL);		// 68000 + OTHER I/O
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   if(!(PCMROM = AllocateMem(0x20000))) return;
   if(!load_rom("cabal_09.bin", PCMROM+0x00000, 0x10000)) return;
   if(!load_rom("cabal_10.bin", PCMROM+0x10000, 0x10000)) return;

     tc = 0x102;
     for(ta=0;ta<5;ta++,tc+=2){
        tb = ReadWord(&PCMROM[tc+0x00000]);
        smp16_romlist_chip_a[ta].data = PCMROM+0x00000+(tb+2);
        smp16_romlist_chip_a[ta].size = ReadWord68k(&PCMROM[tb+0x00000]);
        smp16_romlist_chip_a[ta].type = 0;
     }

     tc = 0x102;
     for(ta=0;ta<7;ta++,tc+=2){
        tb = ReadWord(&PCMROM[tc+0x10000]);
        smp16_romlist_chip_b[ta].data = PCMROM+0x10000+(tb+2);
        smp16_romlist_chip_b[ta].size = ReadWord68k(&PCMROM[tb+0x10000]);
        smp16_romlist_chip_b[ta].type = 0;
     }

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x20000);
   memset(RAM+0x05400,0xFF,0x00100);

   RAMSize=0x30000;

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr_rev);
   InitPaletteMap(RAM+0x4C00, 0x40, 0x10, 0x1000);


   // 68000 Speed hack
   // ----------------

   WriteWord68k(&ROM[0x04FE],0x4EF9);
   WriteLong68k(&ROM[0x0500],0x00000300);

   WriteWord68k(&ROM[0x0300],0x5279);
   WriteLong68k(&ROM[0x0302],0x0004003E);

   WriteLong68k(&ROM[0x0306],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x030A],0x00AA0000);	//

   WriteWord68k(&ROM[0x030E],0x6100-16);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x040000, 0x043FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x060000, 0x0607FF, NULL, RAM+0x004000);			// FG0 RAM
   AddReadByte(0x0E8000, 0x0E800F, CabalSoundRead68k, NULL);		// COIN RAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x040000, 0x043FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x060000, 0x0607FF, NULL, RAM+0x004000);			// FG0 RAM
   AddReadWord(0x0A0000, 0x0A001F, NULL, RAM+0x005410);			// INPUT RAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x040000, 0x043FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x060000, 0x0607FF, NULL, RAM+0x004000);		// FG0 RAM
   AddWriteByte(0x0E8000, 0x0E800F, CabalSoundWrite68k, NULL);		// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x040000, 0x043FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x060000, 0x0607FF, NULL, RAM+0x004000);		// FG0 RAM
   AddWriteWord(0x080000, 0x0803FF, NULL, RAM+0x004800);		// BG0 RAM
   AddWriteWord(0x0E0000, 0x0E07FF, NULL, RAM+0x004C00);		// COLOR RAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_cabalbl(void)
{
   static int coin_toggle;

   if((RAM[0x5404]&0x07)!=7){
      if(coin_toggle==0){
         coin_toggle=1;
      }
      else{
         RAM[0x5404]|=0x07;
      }
   }
   else{
      coin_toggle=0;
   }

   // Main 68000 (8MHz)
   // -----------------

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);

   // Sound Z80 (4MHz)
   // ----------------

   cpu_execute_cycles(CPU_Z80_0, 4000000/60);		// Sound Z80
   /*#ifdef RAINE_DEBUG
      print_debug("Z80PC0:%04x\n",z80pc);
#endif*/
   cpu_interrupt(CPU_Z80_0, 0x38);
   cpu_int_nmi(CPU_Z80_0);
}

static void DrawCabal(void)
{
   int x,y,x16,y16;
   int zz,zzzz,ta;
   UINT8 *MAP;

   ClearPaletteMap();

   x16=16;
   y16=16;
   zzzz=0x20;

   zzzz=zzzz&0x3FF;

   for(y=(16+y16);y<(224+32);y+=16){
   zz=zzzz;
   for(x=(16+x16);x<(256+32);x+=16){

      MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[0x4800+zz])>>12)|0x20,  // 0x20 o 0x30 è lo stesso perchè i colori sono uguali
               16,        MAP
            );

      Draw16x16_Mapped_Rot(&GFX[((ReadWord(&RAM[0x4800+zz])&0xFFF)<<8)+0x110000],x,y,MAP);

      zz+=2;
      if((zz&0x1F)==0){zz-=0x20;}
   }
   zzzz+=0x20;
   zzzz=zzzz&0x3FF;
   }

   for(zz=0x3FF8;zz>=0x3800;zz-=8){

   if((RAM[zz+1]&0x01)==1){

   y=16+RAM[zz+0];
   x=(32+ReadWord(&RAM[zz+4]))&0x1FF;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){
   ta=ReadWord(&RAM[zz+2])&0xFFF;
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
               (RAM[zz+5]>>3)+0x10,
               16,        MAP
            );

      switch(RAM[zz+5]&0x04){
      case 0x00: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[(ta<<8)+0x10000],x,y,MAP);  break;
      case 0x04: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[(ta<<8)+0x10000],x,y,MAP); break;
      }

   }

   }

   }

   }

   zz=0x80;
   for(y=32;y<224+32;y+=8){
   for(x=32;x<256+32;x+=8,zz+=2){

   if((ta=ReadWord(&RAM[0x4000+zz])&0x03FF)!=0){

      MAP = MAP_PALETTE_2BPP(
               Map_12bit_xBGR_Rev_2BPP,
               (ReadWord(&RAM[0x4000+zz])>>10),
               4
            );

      Draw8x8_Trans_Mapped_Rot(&GFX[ta<<6],x,y,MAP);
   }

   }
   }
}


/*

1 |xxxxxxxx| Y Pos
5 |xxxxxxxx| X Pos

*/
static struct VIDEO_INFO video_cabalbl =
{
   DrawCabal,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_cabalbl[] =
{
   { "cabal", },
   { "cabalbl", },
   { NULL, },
};
GME( cabalbl, "Cabal (bootleg)", TAD, 1988, GAME_SHOOT,
	.long_name_jpn = "ƒJƒo[ƒ‹",
);

