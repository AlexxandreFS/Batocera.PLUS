/******************************************************************************/
/*                                                                            */
/*                           NICHIBUTSU SOUND SYSTEMS                         */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "3812intf.h"
#include "sasound.h"		// sample support routines

#define USE_DAC // DAC is slower, but *MUCH* easier to use than smp16
// and smp16 support was never finished (it does not work !!!)

#ifdef USE_DAC
#include "dac.h"

static struct DACinterface dac_interface =
{
	2,	/* 2 channels */
	{ 200 | (0x80<<8),250 | (0x80<<8) },
};

#else
#include "smp16bit.h"

static struct SMP16_ROM smp16_romlist_chip_a[16];	// Fill in later
static struct SMP16_ROM smp16_romlist_chip_b[16];	// Fill in later

static struct SMP16buffer_interface smp16_interface =
{
   2,					// 2 chips
   { 8000, 8000, },			// rate
   { smp16_romlist_chip_a,
     smp16_romlist_chip_b, },		// rom list
};
#endif

static int nichi_sample_count;

void AddNichiSample(UINT16 start, UINT16 end, int rate)
{
#ifndef USE_DAC
   smp16_romlist_chip_a[nichi_sample_count].data = Z80ROM+start;
   smp16_romlist_chip_a[nichi_sample_count].size = (end-start)+1;
   smp16_romlist_chip_a[nichi_sample_count].type = 1;

   smp16_romlist_chip_b[nichi_sample_count].data = Z80ROM+start;
   smp16_romlist_chip_b[nichi_sample_count].size = (end-start)+1;
   smp16_romlist_chip_b[nichi_sample_count].type = 1;

   nichi_sample_count++;
#endif
   //SampleList[SampleCount-1].freq=(SampleList[SampleCount-1].freq / rate);
}

void NichiSoundDAC(UINT16 address, UINT8 ta)
{
#ifdef USE_DAC
/*   if (ta != 0x80) */
  if (address & 1)
    DAC_1_signed_data_w(address,ta);
  else
    DAC_0_signed_data_w(address,ta);
#else
  if(ta<nichi_sample_count) {
    SMP16buffer_request(address&1, ta);
  }// else
  // fprintf(stderr,"rejecting sample %x (%x)\n",ta,nichi_sample_count);
#endif
}

// Sound Communication Port
// ------------------------

static UINT32 sport;

static UINT16 NichiSoundCommClearZ80(UINT16 address)
{
   sport = 0;
   return 0;
}

static UINT16 NichiSoundCommReadZ80(UINT16 address)
{
   return sport;
}

void NichiSoundCommWrite68k(UINT32 offset,UINT8 data)
{
   sport=((data&0x7F)<<1)|1;
}

UINT16 NichiSoundCommRead68k(UINT32 offset)
{
   return 3;
}

#define INT_SLICE	20

// Nichibutsu3526_SlowFrame():
// Half as many int's/frame (Terra Cresta)

#define INT_RATE_3526_SLOW      140             // interrupts per frame (change for music speed)

void Nichibutsu3526_SlowFrame(void)
{
   int ta,tb;

   for(ta=0;ta<INT_RATE_3526_SLOW/INT_SLICE;ta++){
     cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60*INT_RATE_3526_SLOW/INT_SLICE));    // Z80 4MHz
     for(tb=0;tb<INT_SLICE;tb++) cpu_interrupt(CPU_Z80_0, 0x38);
   }
}

// Nichibutsu3526_Frame():
// For Terra Force and Armed Formation

#define INT_RATE_3526   180             // interrupts per frame (change for music speed)

void Nichibutsu3526_Frame(void)
{
#if 0
  int ta,tb;
   for(ta=0;ta<INT_RATE_3526_SLOW/INT_SLICE;ta++){
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60*INT_RATE_3526_SLOW/INT_SLICE));         // Z80 4MHz
   //for(tb=0;tb<INT_SLICE*2;tb++)
     cpu_interrupt(CPU_Z80_0, 0x38);
   }
#else
   int ta;

   for(ta=0;ta<128;ta++){
     cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,(60*128)));
     //for(tb=0;tb<INT_SLICE;tb++)
     cpu_interrupt(CPU_Z80_0, 0x38);
   }

#endif
}

static struct YM3812interface ym3812_interface =
{
        1,              // 1 chip
        4000000,        // 4 MHz  (emu and real OPL2/3 chips)
        { 150 },        // Volume (emu only)
        { NULL }
};

struct SOUND_INFO nichi_ym3812_sound[] =
{
   { SOUND_YM3812,  &ym3812_interface,  },
#ifdef USE_DAC
   { SOUND_DAC,   &dac_interface,   },
#else
   { SOUND_SMP16,   &smp16_interface,   },
#endif
   { 0,             NULL,               },
};

/*-------[SOUND SYSTEM INIT]-------*/

void AddNichibutsuYM3526(UINT32 p1, UINT32 p2)
{
#ifndef USE_DAC
  int ta;
#endif

   // Apply Speed Patch

   if (p1) {
     Z80ROM[p1+0]=0xD3;   // OUTA (AAh)
     Z80ROM[p1+1]=0xAA;   //

     SetStopZ80Mode2( (UINT16) p2);
   }

   // Setup Z80 memory map

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xFFFF, NULL,                Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80AReadByte(    -1,     -1, NULL,                NULL);

   AddZ80AWriteByte(0x0000, 0xFFFF, NULL,               Z80ROM+0x0000); // Z80 RAM
   // AddZ80AWriteByte(0x0000, 0xF7FF, DefBadWriteZ80,     NULL);
   // AddZ80AWriteByte(0xf800, 0xffff, NULL,   Z80ROM + 0xf800);
   AddZ80AWriteByte(    -1,     -1, NULL,               NULL);

   // AddZ80AReadPort(0x00, 0x01, YM3526ReadZ80,           NULL);
   AddZ80AReadPort(0x04, 0x04, NichiSoundCommClearZ80,  NULL);
   AddZ80AReadPort(0x06, 0x06, NichiSoundCommReadZ80,   NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(-1, -1, NULL, NULL);

   AddZ80AWritePort(0x00, 0x01, YM3526WriteZ80,         NULL);
   AddZ80AWritePort(0x02, 0x03, NichiSoundDAC,          NULL);
   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(-1, -1, NULL, NULL);

   AddZ80AInit();

   nichi_sample_count=0;

#ifndef USE_DAC
   for(ta=0;ta<16;ta++){
     smp16_romlist_chip_a[ta].data = NULL;
     smp16_romlist_chip_b[ta].data = NULL;
   }
#endif
}

void RemoveNichibutsuYM3526(void)
{
}

