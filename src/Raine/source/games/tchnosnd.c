/******************************************************************************/
/*                                                                            */
/*             TECHNOS SOUND SYSTEMS (C) 1990-1992 TECHNOS JAPAN              */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tchnosnd.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "adpcm.h"
#include "2151intf.h"

static UINT8 SoundByte[32];
static int SoundW;
static int SoundR;

UINT8 TechnosSoundReadZ80(UINT16 offset)
{
   int ta;

   if( SoundW != SoundR ){
      ta = SoundByte[SoundR];
      SoundR = (SoundR+1) & 31;
   }
   else{
      ta = 0x00;
   }
   print_debug("Z80 Receives:%02x\n",ta);
   return ta;
}

void TechnosSoundWrite68k(UINT32 address, UINT16 data)
{
   data&=0xFF;

   SoundByte[SoundW]=data;
   SoundW = (SoundW+1) & 31;

   cpu_int_nmi(CPU_Z80_0);
   print_debug("68000 Sends:%02x\n",data);
}

static struct OKIM6295interface m6295_interface =
{
   1,					// 1 chip
   { 8000 },				// rate
   { 0 },		// rom list
   { 127 },
};

static struct YM2151interface ym2151_interface =
{
  1,                    // 1 chip
  3500000,              // 3.5 MHz
  { YM3012_VOL(250,MIXER_PAN_LEFT,250,MIXER_PAN_RIGHT) },
  { NULL, },
};

struct SOUND_INFO technos_ym2151_m6295_sound[] =
{
   { SOUND_YM2151J, &ym2151_interface,    },
   { SOUND_M6295,   &m6295_interface,     },
   { 0,             NULL,                 },
};

static void YM2151_Init(int volume)
{
    ym2151_interface.volume[0] = YM3012_VOL(volume,MIXER_PAN_LEFT,volume,MIXER_PAN_RIGHT);
}

void TechnosSound_Frame(void)
{
   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Sound Z80 xMhz
   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Sound Z80 xMhz
}

static void my_bankswitch(UINT16 offset,UINT8 data)
{
	OKIM6295_set_bank_base(0,ALL_VOICES,(data & 1) * 0x40000);
}

void AddTechnosSound(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, UINT8 *adpcmB, int volume)
{
  int bank_size = adpcmB - adpcmA;

  // Apply Speed Patch
   // -----------------
   Z80ROM[p1+0]=0xD3;   // OUTA (AAh)
   Z80ROM[p1+1]=0xAA;   //

   SetStopZ80Mode2( (UINT16) p2);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0xC000, 0xC7FF, NULL,                        Z80ROM+0xC000); // Z80 RAM
   AddZ80AReadByte(0xC800, 0xC801, YM2151ReadZ80,               NULL);          // YM2151
   AddZ80AReadByte(0xD800, 0xD800, M6295_A_Read_Z80,            NULL);          // OKI M6295
   AddZ80AReadByte(0xE000, 0xE000, TechnosSoundReadZ80,         NULL);          // 68000 COMM
   AddZ80AReadByte(0x0000, 0xFFFF, NULL,                        Z80ROM+0x0000); // <test>
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);          // <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0xC000, 0xC7FF, NULL,                       Z80ROM+0xC000); // Z80 RAM
   AddZ80AWriteByte(0xC800, 0xC801, YM2151WriteZ80,             NULL);          // YM2151
   AddZ80AWriteByte(0xD800, 0xD800, M6295_A_Write_Z80,          NULL);          // OKI M6295
   AddZ80AWriteByte(0xE800, 0xE800, my_bankswitch,      NULL);          // OKI BANKING
   //AddZ80AWriteByte(0xE800, 0xE800, M6295_A_WriteBank_Z80,      NULL);          // OKI BANKING
   AddZ80AWriteByte(0x0000, 0xFFFF, NULL,                       Z80ROM+0x0000); // <test>
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);          // <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   // Setup YM2151
   // ------------

   YM2151_Init(volume);

   // Setup M6295
   // -----------

   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),adpcmA,bank_size);
   // ExecuteSoundFrame=&TechnosSound_Frame;

   SoundW = 0;
   SoundR = 0;
}

void TechnosSoundOld_Frame(void)
{
   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Sound Z80 xMhz
   cpu_interrupt(CPU_Z80_0, 0x38);
   cpu_execute_cycles(CPU_Z80_0, 4000000/60);        // Sound Z80 xMhz
   cpu_interrupt(CPU_Z80_0, 0x38);
}

// AddTechnosSoundOld():
//
// Older version seen in WWF SuperStars and Comba Tribes. Memory map is $4000
// bytes earlier, single adpcm bank and int#38 is used.

void AddTechnosSoundOld(UINT32 p1, UINT32 p2, UINT32 romsize, UINT8 *adpcmA, int volume)
{
   int ta;

   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),adpcmA,0x40000);
   for(ta=0;ta<0x8000;ta++){
      Z80ROM[ta+0x8000]=0;
   }

   // Apply Speed Patch
   // -----------------

   Z80ROM[p1+0]=0xD3;   // OUTA (AAh)
   Z80ROM[p1+1]=0xAA;   //

   SetStopZ80Mode2( (UINT16) p2);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x8000, 0x87FF, NULL,                        Z80ROM+0x8000); // Z80 RAM
   AddZ80AReadByte(0x8800, 0x8801, YM2151ReadZ80,               NULL);          // YM2151
   AddZ80AReadByte(0x9800, 0x9800, M6295_A_Read_Z80,            NULL);          // OKI ADPCM
   AddZ80AReadByte(0xA000, 0xA000, TechnosSoundReadZ80,         NULL);          // 68000 COMM
   AddZ80AReadByte(0x0000, 0xFFFF, NULL,                        Z80ROM+0x0000); // <test>
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);          // <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x87FF, NULL,                       Z80ROM+0x8000); // Z80 RAM
   AddZ80AWriteByte(0x8800, 0x8801, YM2151WriteZ80,             NULL);          // YM2151
   AddZ80AWriteByte(0x9800, 0x9800, M6295_A_Write_Z80,          NULL);          // OKI ADPCM
   AddZ80AWriteByte(0x0000, 0xFFFF, NULL,                       Z80ROM+0x0000); // <test>
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);          // <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   // Setup YM2151
   // ------------

   YM2151_Init(volume);

   // Setup M6295
   // -----------

   // ExecuteSoundFrame=&TechnosSoundOld_Frame;

   SoundW = 0;
   SoundR = 0;
}
