#define DRV_DEF_SOUND sound_zerozone
/******************************************************************************/
/*                                                                            */
/*                         ZERO ZONE (C) 1993 COMAD                           */
/* disabled oki sound for now                                                 */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "adpcm.h"


static struct ROM_INFO rom_zerozone[] =
{
   {     "zz-2.rom", 0x00020000, 0xc7551e81, 0, 0, 0, },
   {     "zz-1.rom", 0x00008000, 0x223ccce5, 0, 0, 0, },
   {     "zz-3.rom", 0x00020000, 0xe348ff5e, 0, 0, 0, },
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00010000,
                "zz-4.rom",  0x83718b9b,     "zz-5.rom",  0x18557f41),
   {     "zz-6.rom", 0x00080000, 0xc8b906b9, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_zerozone[] =
{
   INP0( COIN1, 0x010000, 0x01 ),
   INP0( COIN2, 0x010000, 0x02 ),

   INP0( P1_START, 0x010000, 0x08 ),
   INP0( P1_UP, 0x010002, 0x08 ),
   INP0( P1_DOWN, 0x010002, 0x04 ),
   INP0( P1_LEFT, 0x010002, 0x02 ),
   INP0( P1_RIGHT, 0x010002, 0x01 ),
   INP0( P1_B1, 0x010002, 0x10 ),

   INP0( P2_START, 0x010000, 0x10 ),
   INP0( P2_UP, 0x010003, 0x08 ),
   INP0( P2_DOWN, 0x010003, 0x04 ),
   INP0( P2_LEFT, 0x010003, 0x02 ),
   INP0( P2_RIGHT, 0x010003, 0x01 ),
   INP0( P2_B1, 0x010003, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_zero_zone_1[] =
{
   { MSG_DSWB_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_zerozone[] =
{
   { 0x01000A, 0xFF, dsw_data_default_0 },
   { 0x010009, 0xFF, dsw_data_zero_zone_1 },
   { 0,        0,    NULL,      },
};


static struct OKIM6295interface m6295_interface =
{
   1,               // 1 chip
   { 7000 },            // rate
   { 0 },      // rom list
   { 220 }, // volume - still unused
};

static struct SOUND_INFO sound_zerozone[] =
{
   { SOUND_M6295,   &m6295_interface,     },
   { 0,             NULL,                 },
};


static gfx_layout zero_zone_bg0 =
{
   8,8,   /* 8*8 characters */
   0x4000,   /* 0x4000 characters */
   4,   /* 4 bits per pixel */
   { 0, 1, 2, 3 },
   { 0, 4, 8+0, 8+4, 16+0, 16+4, 24+0, 24+4 },
   { 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
   32*8   /* every sprite takes 32 consecutive bytes */
};

static UINT8 *GFX_BG0_SOLID;

static UINT8 sport;
static UINT8 want_int;

static void ZeroZoneSoundWrite68k(UINT32 address, UINT16 data)
{
   sport=data;
   want_int=1;
}

static UINT8 ZeroZoneSoundReadZ80(UINT16 offset)
{
   print_debug("Z80 Receives:%02x\n",sport);
   return sport;
}

static void load_zerozone(void)
{
   RAMSize=0x50000;

   if(!(RAM=AllocateMem(0x80000))) return;

   if(!load_rom("zz-6.rom", RAM, 0x80000)) return;            // GFX BG0
   if(!(GFX = decode_gfx(RAM, 0x80000, &zero_zone_bg0,NULL))) return;

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX, 0x4000);

   /*----------------------*/

   Z80ROM=RAM+0x40000;
   if(!load_rom( "zz-1.rom", Z80ROM, 0x8000)) return;         // Z80 SOUND ROM

   memset(Z80ROM+0x8000,0x00,0x8000);

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x009A]=0xD3; // OUTA (AAh)
   Z80ROM[0x009B]=0xAA; //

   SetStopZ80Mode2(0x008A);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x87FF, NULL,                        Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80AReadByte(0x9800, 0x9800, M6295_A_Read_Z80,            NULL);          // M6295
   AddZ80AReadByte(0xA000, 0xA000, ZeroZoneSoundReadZ80,        NULL);          // 68000
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0x8000, 0x87FF, NULL,                       Z80ROM+0x8000); // Z80 RAM
   AddZ80AWriteByte(0x9800, 0x9800, M6295_A_Write_Z80,          NULL);          // M6295
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   if(!(PCMROM = AllocateMem(0x40000))) return;
   if(!load_rom( "zz-2.rom", PCMROM+0x00000, 0x20000)) return;
   if(!load_rom( "zz-3.rom", PCMROM+0x20000, 0x20000)) return;
   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),PCMROM,0x40000);

   /*----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x10000,0xFF,0x00010);

   set_white_pen(15);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x20000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x01FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x01FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadByte(0x0C0000, 0x0C7FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadByte(0x080000, 0x09FFFF, NULL, RAM+0x010000);                 // VRAM/PALETTE
   AddReadByte(0x0B4000, 0x0BFFFF, NULL, RAM+0x030000);                 // ???
   AddReadByte(0x0F0000, 0x0FBFFF, NULL, RAM+0x034000);                 // ???
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x01FFFF, NULL, ROM+0x000000);                 // 68000 ROM
   AddReadWord(0x0C0000, 0x0C7FFF, NULL, RAM+0x000000);                 // 68000 RAM
   AddReadWord(0x080000, 0x09FFFF, NULL, RAM+0x010000);                 // VRAM/PALETTE
   AddReadWord(0x0B4000, 0x0BFFFF, NULL, RAM+0x030000);                 // ???
   AddReadWord(0x0F0000, 0x0FBFFF, NULL, RAM+0x034000);                 // ???
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x0C0000, 0x0C7FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0x084000, 0x084000, ZeroZoneSoundWrite68k, NULL);       // SOUND COMM
   AddWriteByte(0x080000, 0x09FFFF, NULL, RAM+0x010000);                // VRAM/PALETTE
   AddWriteByte(0x0B4000, 0x0BFFFF, NULL, RAM+0x030000);                // ???
   AddWriteByte(0x0F0000, 0x0FBFFF, NULL, RAM+0x034000);                // ???
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x0C0000, 0x0C7FFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0x080000, 0x09FFFF, NULL, RAM+0x010000);                // VRAM/PALETTE
   AddWriteWord(0x0B4000, 0x0BFFFF, NULL, RAM+0x030000);                // ???
   AddWriteWord(0x0F0000, 0x0FBFFF, NULL, RAM+0x034000);                // ???
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void ClearZeroZone(void)
{
}

static void execute_zerozone(void)
{
   cpu_execute_cycles(CPU_68K_0, 100000);
   cpu_interrupt(CPU_68K_0, 1);
   //cpu_execute_cycles(CPU_68K_0, 20000);
   //cpu_interrupt(CPU_68K_0, 1);

   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(1,60));
   if(want_int){
      want_int=0;
      cpu_interrupt(CPU_Z80_0, 0x38);
   }
}

static void DrawZeroZone(void)
{
   int ta,yy,tx,ty,zz;

   // Palette (256 colours)

   for(ta=0;ta<256;ta++){
      yy=ReadWord(&RAM[0x18000+(ta<<1)]);
#ifdef SDL
      pal[ta].b=(yy&0xF000)>>8|((yy&0x08));
      pal[ta].g=(yy&0x0F00)>>4|((yy&0x04)<<1);
      pal[ta].r=(yy&0x00F0)|((yy&0x02)<<2);
#else
      pal[ta].b=(yy&0xF000)>>10|((yy&0x08)>>2);
      pal[ta].g=(yy&0x0F00)>>6|((yy&0x04)>>1);
      pal[ta].r=(yy&0x00F0)>>2|((yy&0x02)>>0);
#endif
   }

   // BG0

   zz=0x2CE00+4+64;
   for(tx=0;tx<368;tx+=8,zz+=8){
      for(ty=0;ty<224;ty+=8,zz+=2){
         ta = ReadWord(&RAM[zz]);
         Draw8x8_8_Rot(&GFX[(ta&0x0FFF)<<6], tx, ty, (UINT8) ((ta>>8)&0xF0) );
      }
   }
}
static struct VIDEO_INFO video_zerozone =
{
   DrawZeroZone,
   368,
   224,
   0,
   VIDEO_ROTATE_NORMAL | VIDEO_NEEDS_8BPP |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_zerozone[] =
{
   { "zero_zone", },
   { "zerozone", },
   { NULL, },
};
GME( zerozone, "Zero Zone", COMAD, 1993, GAME_PUZZLE | GAME_ADULT,
	.clear = ClearZeroZone,
	.long_name_jpn = "É[ÉçÉ]Å[Éì",
);

