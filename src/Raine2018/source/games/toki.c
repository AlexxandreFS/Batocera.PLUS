#define DRV_DEF_SOUND sound_tokib
/******************************************************************************/
/*                                                                            */
/*                       TOKI (C) 1989 DATSU ELECTRON                         */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "3812intf.h"
#include "msm5205.h"
#include "timer.h"

#define FRAME_Z80 CPU_FRAME_MHz(4,60)

static int current_bank;


static struct ROM_INFO rom_tokib[] =
{
   {      "toki.e9", 0x00010000, 0x82ce27f6, 0, 0, 0, },
   {      "toki.e8", 0x00010000, 0x46a1b821, 0, 0, 0, },
   {      "toki.e7", 0x00008000, 0x70729106, 0, 0, 0, },
   {      "toki.e6", 0x00010000, 0x6f4b878a, 0, 0, 0, },
   {      "tokijp.003", 0x00010000, 0xa01a5b10, 0, 0, 0, },
   {     "toki.e38", 0x00020000, 0x87f4e7fb, 0, 0, 0, },
   {     "toki.e36", 0x00020000, 0x96e8db8b, 0, 0, 0, },
   {     "toki.e34", 0x00020000, 0xe5f6e19b, 0, 0, 0, },
   {     "toki.e32", 0x00020000, 0xc289d246, 0, 0, 0, },
   {     "toki.e30", 0x00020000, 0x770d2b1b, 0, 0, 0, },
   {      "toki.e3", 0x00020000, 0xae9b3da4, 0, 0, 0, },
   {     "toki.e28", 0x00020000, 0x29784948, 0, 0, 0, },
   {     "toki.e26", 0x00020000, 0xa8ba71fc, 0, 0, 0, },
   {     "toki.e25", 0x00010000, 0x63026cad, 0, 0, 0, },
   {     "toki.e24", 0x00010000, 0x5b365637, 0, 0, 0, },
   {     "toki.e23", 0x00010000, 0xfeb13d35, 0, 0, 0, },
   {     "toki.e22", 0x00008000, 0x04dcdc21, 0, 0, 0, },
   {     "toki.e21", 0x00008000, 0xbb8cacbd, 0, 0, 0, },
   {     "toki.e20", 0x00010000, 0xa7f2ce26, 0, 0, 0, },
   {      "tokijp.005", 0x00010000, 0xd6a82808, 0, 0, 0, },
   {     "toki.e19", 0x00010000, 0x6cd22b18, 0, 0, 0, },
   {     "toki.e18", 0x00010000, 0x4c2a72e1, 0, 0, 0, },
   {     "toki.e17", 0x00010000, 0xfbc3d456, 0, 0, 0, },
   {     "toki.e16", 0x00010000, 0x2a11c0f0, 0, 0, 0, },
   {     "toki.e15", 0x00010000, 0x617c32e6, 0, 0, 0, },
   {     "toki.e14", 0x00010000, 0x859e313a, 0, 0, 0, },
   {     "toki.e13", 0x00008000, 0x052ad275, 0, 0, 0, },
   {     "toki.e12", 0x00010000, 0xc2ad9342, 0, 0, 0, },
   {     "toki.e11", 0x00010000, 0x48989aa0, 0, 0, 0, },
   {     "toki.e10", 0x00010000, 0xe15c1d0f, 0, 0, 0, },
   {      "toki.e1", 0x00010000, 0x2832ef75, REGION_ROM2, 0, LOAD_NORMAL, },
   {      "toki.e1", 0x00010000, 0x2832ef75, 0, 0, 0, },
   {      "toki.e5", 0x00020000, 0x66a5a1d6, 0, 0, 0, },
   {     "toki.e40", 0x00020000, 0x96e87350, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_tokib[] =
{
   INP0( COIN1, 0x020004, 0x01 ),
   INP0( COIN2, 0x020004, 0x02 ),
   INP0( SERVICE, 0x020004, 0x04 ),

   INP0( P1_START, 0x020004, 0x08 ),
   INP0( P1_UP, 0x020002, 0x01 ),
   INP0( P1_DOWN, 0x020002, 0x02 ),
   INP0( P1_LEFT, 0x020002, 0x04 ),
   INP0( P1_RIGHT, 0x020002, 0x08 ),
   INP0( P1_B1, 0x020002, 0x10 ),
   INP0( P1_B2, 0x020002, 0x20 ),

   INP0( P2_START, 0x020004, 0x10 ),
   INP0( P2_UP, 0x020003, 0x01 ),
   INP0( P2_DOWN, 0x020003, 0x02 ),
   INP0( P2_LEFT, 0x020003, 0x04 ),
   INP0( P2_RIGHT, 0x020003, 0x08 ),
   INP0( P2_B1, 0x020003, 0x10 ),
   INP0( P2_B2, 0x020003, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_toki_0[] =
{
   { MSG_COINAGE,               0x1F, 0x14 },
   { MSG_6COIN_1PLAY,         0x15},
   { MSG_5COIN_1PLAY,         0x17},
   { MSG_4COIN_1PLAY,         0x19},
   { MSG_3COIN_1PLAY,         0x1B},
   { MSG_8COIN_3PLAY,         0x03},
   { MSG_2COIN_1PLAY,         0x1D},
   { MSG_5COIN_3PLAY,         0x05},
   { MSG_3COIN_2PLAY,         0x07},
   { MSG_1COIN_1PLAY,         0x1F},
   { MSG_2COIN_3PLAY,         0x09},
   { MSG_1COIN_2PLAY,         0x13},
   { MSG_1COIN_3PLAY,         0x11},
   { MSG_1COIN_4PLAY,         0x0F},
   { MSG_1COIN_5PLAY,         0x0D},
   { MSG_1COIN_6PLAY,         0x0B},
   { _("A 1/1 B 1/2"),           0x1E},
   { _("A 2/1 B 1/3"),           0x14},
   { _("A 3/1 B 1/5"),           0x0A},
   { _("A 5/1 B 1/6"),           0x00},
   { MSG_FREE_PLAY,             0x01},
   { _("Joysticks"),             0x20, 0x02 },
   { "1",                     0x20},
   { "2",                     0x00},
   DSW_CABINET( 0x40, 0x00),
   DSW_SCREEN( 0x80, 0x00),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_toki_1[] =
{
   { _("Lives"),                 0x03, 0x04 },
   { "3",                     0x03},
   { "2",                     0x02},
   { "5",                     0x01},
   { "3",                     0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("70k"),                   0x0C},
   { _("50k 150k"),              0x08},
   { _("100k 200k"),             0x04},
   { _("70k 14k 21k"),           0x00},
   { MSG_DIFFICULTY,          0x30, 0x04 },
   { MSG_NORMAL,              0x30},
   { MSG_EASY,                0x20},
   { MSG_HARD,                0x10},
   { MSG_HARDEST,             0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   DSW_DEMO_SOUND( 0x80, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_tokib[] =
{
   { 0x020000, 0x9F, dsw_data_toki_0 },
   { 0x020001, 0xFB, dsw_data_toki_1 },
   { 0,        0,    NULL,      },
};


static struct YM3812interface ym3812_interface =
{
   1,              // 1 chip
   3600000,        // 3.6 MHz
   { 200 },        // Volume (emu only)
   { NULL }
};

#if 0
static void toki_adpcm_int (int data)
{
    cpu_int_nmi(CPU_Z80_0);
}
#endif

static struct msm5205_adpcm_list toki_adpcm[MAX_MSM_ADPCM];

static struct MSM5205buffer_interface msm5205_interface =
{
   1,
   { 4000 },
   { 255 },
   { toki_adpcm },
   { sizeof(toki_adpcm) / sizeof(struct msm5205_adpcm_list) },
   { NULL },
   { 0 },
   { 0 },
   MSM5205_MONO,
};

static struct SOUND_INFO sound_tokib[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { SOUND_MSM5205_BUFF,  &msm5205_interface, },
   { 0,             NULL,                 },
};


static UINT8 *RAM_BG0;
static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *RAM_BG1;
static UINT8 *GFX_BG1;
static UINT8 *GFX_BG1_SOLID;

static UINT8 *RAM_SPR;
static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *RAM_FG0;
static UINT8 *GFX_FG0;
static UINT8 *GFX_FG0_SOLID;

static int sport=0;

static void SoundWrite(UINT32 offset, UINT8 data)
{
   sport = data;

#ifdef RAINE_DEBUG
   if(sport) print_debug("68000 Sends $%02x\n",sport);
#endif
   cpu_interrupt(CPU_Z80_0, 0x38);
}

static UINT8 SoundRead(UINT16 address)
{
#ifdef RAINE_DEBUG
   if(sport) print_debug("Z80 Receives $%02x\n",sport);
#endif
   return sport;
}

static void TokiDecode1(char *S,int tb, int td)
{
   int ta,tc;

   if(!load_rom(S, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      tc=RAM[ta];
      GFX[tb+0]|=((tc&0x80)>>7)<<td;
      GFX[tb+1]|=((tc&0x40)>>6)<<td;
      GFX[tb+2]|=((tc&0x20)>>5)<<td;
      GFX[tb+3]|=((tc&0x10)>>4)<<td;
      GFX[tb+4]|=((tc&0x08)>>3)<<td;
      GFX[tb+5]|=((tc&0x04)>>2)<<td;
      GFX[tb+6]|=((tc&0x02)>>1)<<td;
      GFX[tb+7]|=((tc&0x01)>>0)<<td;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
}

static void TokiDecode2(char *S,int tb, int td)
{
   int ta,tc,te,tf,tg;

   if(!load_rom(S, RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      tc=RAM[ta];
      tf=RAM[ta+0x800];
      te=RAM[ta+0x1000];
      tg=RAM[ta+0x1800];
      GFX[tb+0]|=((tc&0x80)>>7)<<td;
      GFX[tb+1]|=((tc&0x40)>>6)<<td;
      GFX[tb+2]|=((tc&0x20)>>5)<<td;
      GFX[tb+3]|=((tc&0x10)>>4)<<td;
      GFX[tb+4]|=((tc&0x08)>>3)<<td;
      GFX[tb+5]|=((tc&0x04)>>2)<<td;
      GFX[tb+6]|=((tc&0x02)>>1)<<td;
      GFX[tb+7]|=((tc&0x01)>>0)<<td;
      GFX[tb+8]|=((te&0x80)>>7)<<td;
      GFX[tb+9]|=((te&0x40)>>6)<<td;
      GFX[tb+10]|=((te&0x20)>>5)<<td;
      GFX[tb+11]|=((te&0x10)>>4)<<td;
      GFX[tb+12]|=((te&0x08)>>3)<<td;
      GFX[tb+13]|=((te&0x04)>>2)<<td;
      GFX[tb+14]|=((te&0x02)>>1)<<td;
      GFX[tb+15]|=((te&0x01)>>0)<<td;
      GFX[tb+0+128]|=((tf&0x80)>>7)<<td;
      GFX[tb+1+128]|=((tf&0x40)>>6)<<td;
      GFX[tb+2+128]|=((tf&0x20)>>5)<<td;
      GFX[tb+3+128]|=((tf&0x10)>>4)<<td;
      GFX[tb+4+128]|=((tf&0x08)>>3)<<td;
      GFX[tb+5+128]|=((tf&0x04)>>2)<<td;
      GFX[tb+6+128]|=((tf&0x02)>>1)<<td;
      GFX[tb+7+128]|=((tf&0x01)>>0)<<td;
      GFX[tb+8+128]|=((tg&0x80)>>7)<<td;
      GFX[tb+9+128]|=((tg&0x40)>>6)<<td;
      GFX[tb+10+128]|=((tg&0x20)>>5)<<td;
      GFX[tb+11+128]|=((tg&0x10)>>4)<<td;
      GFX[tb+12+128]|=((tg&0x08)>>3)<<td;
      GFX[tb+13+128]|=((tg&0x04)>>2)<<td;
      GFX[tb+14+128]|=((tg&0x02)>>1)<<td;
      GFX[tb+15+128]|=((tg&0x01)>>0)<<td;
      tb+=16;
      if((tb&0x7F)==0){tb+=0x80;}
      if((ta&0x7FF)==0x7FF){ta+=0x1800;}
   }
}

static void toki_adpcm_control_w(UINT16 adr, UINT8 data)
{
  data &= 1;
  if (data != current_bank) {
    z80a_set_bank(0,data & 1);
    current_bank = data;
  }
}

static WRITE_HANDLER( toki_adpcm_data_w )
{
  INT16 len = ReadWord(&Z80RAM[0x704]);
  UINT16 adr = ReadWord(&Z80RAM[0x702])+(current_bank*0x4000);
  if (len>0) len--;
  if (live_msm_decode(adr,len)) { // did we start a new sample ?
    WriteWord(&Z80RAM[0x702],adr+1);
    WriteWord(&Z80RAM[0x704],1); // stop the work in the nmi !
  }
}

static UINT16 sound_buff;

static UINT8 myYM3812ReadZ80(UINT32 offset) {
  UINT8 ret = YM3812ReadZ80(offset);
  if ((offset & 1) == 0)
    ret |= 0x60; // timer related, don't know why toki needs it...
  /* Probably because we don't trigger timers in toki, the speed of the music is
     controlled manually here since the 3812 does not generate any irq for the z80 */
  return ret;
}

static void load_tokib(void)
{
   int ta,tb,tc,td;

   for (ta=0; ta < MAX_MSM_ADPCM; ta++)
     toki_adpcm[ta].start = toki_adpcm[ta].end = 0;

   RAMSize=0x22000+0x800;
   setup_z80_frame(CPU_Z80_0,FRAME_Z80);

   msm5205_interface.rom[0] = load_region[REGION_ROM2];
   msm5205_interface.romsize[0] = 0x10000;

   if(!(ROM=AllocateMem(0x60000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   Z80RAM = RAM+0x22000;
   if(!(GFX=AllocateMem(0x440000))) return;

   if(!load_rom("toki.e3", RAM, 0x20000)) return;	// 68000 ROMs
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("toki.e5", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("tokijp.005", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("tokijp.003", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   memset(GFX+0x00000,0x00,0x440000);

   if(!load_rom("toki.e21", RAM+0x00000, 0x8000)) return;		// Character Tiles
   if(!load_rom("toki.e13", RAM+0x08000, 0x8000)) return;
   if(!load_rom("toki.e22", RAM+0x10000, 0x8000)) return;
   if(!load_rom("toki.e7",  RAM+0x18000, 0x8000)) return;
   tb=0;
   for(ta=0;ta<0x8000;ta++){
      for(td=0;td<4;td++){
      tc=RAM[ta+(td*0x8000)];
      GFX[tb+0]|=((tc&0x80)>>7)<<td;
      GFX[tb+1]|=((tc&0x40)>>6)<<td;
      GFX[tb+2]|=((tc&0x20)>>5)<<td;
      GFX[tb+3]|=((tc&0x10)>>4)<<td;
      GFX[tb+4]|=((tc&0x08)>>3)<<td;
      GFX[tb+5]|=((tc&0x04)>>2)<<td;
      GFX[tb+6]|=((tc&0x02)>>1)<<td;
      GFX[tb+7]|=((tc&0x01)>>0)<<td;
      }
      tb+=8;
   }

   TokiDecode1("toki.e26",0x40000,0);	// Sprites (Set A)
   TokiDecode1("toki.e30",0x40000,2);
   TokiDecode1("toki.e34",0x40000,1);
   TokiDecode1("toki.e38",0x40000,3);

   TokiDecode1("toki.e28",0x140000,0);	// Sprites (Set B)
   TokiDecode1("toki.e32",0x140000,2);
   TokiDecode1("toki.e36",0x140000,1);
   TokiDecode1("toki.e40",0x140000,3);

   TokiDecode2("toki.e23",0x240000,0);	// Decode BG1 GFX (Set A)
   TokiDecode2("toki.e17",0x240000,2);
   TokiDecode2("toki.e15",0x240000,1);
   TokiDecode2("toki.e8", 0x240000,3);

   TokiDecode2("toki.e24",0x2C0000,0);	// Decode BG1 GFX (Set B)
   TokiDecode2("toki.e18",0x2C0000,2);
   TokiDecode2("toki.e16",0x2C0000,1);
   TokiDecode2("toki.e9", 0x2C0000,3);

   TokiDecode2("toki.e25",0x340000,0);	// Decode BG2 GFX (Set A)
   TokiDecode2("toki.e19",0x340000,2);
   TokiDecode2("toki.e11",0x340000,1);
   TokiDecode2("toki.e10",0x340000,3);

   TokiDecode2("toki.e20",0x3C0000,0);	// Decode BG2 GFX (Set B)
   TokiDecode2("toki.e14",0x3C0000,2);
   TokiDecode2("toki.e12",0x3C0000,1);
   TokiDecode2("toki.e6", 0x3C0000,3);

   GFX_BG0 = GFX+0x340000;
   GFX_BG1 = GFX+0x240000;
   GFX_SPR = GFX+0x040000;
   GFX_FG0 = GFX+0x000000;

   for(ta=0;ta<0x100000;ta++){
      GFX_BG0[ta]^=15;
   }
   for(ta=0;ta<0x100000;ta++){
      GFX_BG1[ta]^=15;
   }
   for(ta=0;ta<0x040000;ta++){
      GFX_FG0[ta]^=15;
   }

   RAM_BG0 = RAM+0x0F000;
   RAM_BG1 = RAM+0x0E800;
   RAM_SPR = RAM+0x11806;
   RAM_FG0 = RAM+0x0F800;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x1000);
   GFX_BG1_SOLID = make_solid_mask_16x16(GFX_BG1, 0x1000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);
   GFX_FG0_SOLID = make_solid_mask_8x8  (GFX_FG0, 0x1000);

   // Apply Speed Patch
   // -----------------

   Z80ROM[0x0E40]=0xD3; // OUTA (AAh)
   Z80ROM[0x0E41]=0xAA; //

   SetStopZ80Mode2(0x0E42);

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
   z80_init_banks(0,REGION_ROM2,0x8000,0x4000);

   AddZ80AReadByte(0x0000, 0xbFFF, NULL,     NULL);	// Z80 ROM/BANK ROM
   AddZ80AReadByte(0xF000, 0xF7FF, NULL,     Z80RAM); // Z80 RAM
   AddZ80AReadByte(0xF800, 0xF800, SoundRead,                   NULL);		// COMM
   AddZ80AReadByte(0xEC00, 0xEC01, myYM3812ReadZ80,               NULL);
   AddZ80AReadByte(0xEC08, 0xEC09, myYM3812ReadZ80,               NULL);
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xF000, 0xF7FF, NULL,   Z80RAM); // Z80 RAM
   AddZ80AWriteByte(0xEC00, 0xEC01, YM3812WriteZ80,             NULL);
   AddZ80AWriteByte(0xEC08, 0xEC09, YM3812WriteZ80,             NULL);
   AddZ80AWriteByte(0xE000, 0xE000, toki_adpcm_control_w,             NULL);
   AddZ80AWriteByte(0xE400, 0xE400, toki_adpcm_data_w,             NULL);

   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   memset(RAM+0x00000,0x00,0x22000);
   memset(RAM+0x20000,0xFF,0x00100);

   // Speed Hack

   WriteLong68k(&ROM[0x1A1D4],0x13FC0000);
   WriteLong68k(&ROM[0x1A1D8],0x00AA0000);

   WriteWord68k(&ROM[0x1A1E2],0x4E71);
   WriteWord68k(&ROM[0x1A1EA],0x4E71);

   WriteLong68k(&ROM[0x1A342],0x13FC0000);
   WriteLong68k(&ROM[0x1A346],0x00AA0000);

   WriteLong68k(&ROM[0x1A6A2],0x13FC0000);
   WriteLong68k(&ROM[0x1A6A6],0x00AA0000);

   // Scroll Sync

   WriteLong68k(&ROM[0x00288],0x4EF80300);

   WriteWord68k(&ROM[0x00300],0x33C1);
   WriteLong68k(&ROM[0x00302],0x00075008);

   WriteLong68k(&ROM[0x00306],0x13FC0000);
   WriteLong68k(&ROM[0x0030A],0x00AA0000);

   WriteWord68k(&ROM[0x0030E],0x4E75);

   // Sound Comm

   WriteLong68k(&ROM[0x1D940],0x00BB0000);

   set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr_rev);
   InitPaletteMap(RAM+0x0E000, 0x40, 0x10, 0x1000);


/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x20300);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);	// 68000 ROM

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x060000, 0x07FFFF, NULL, RAM+0x000000);			// 68000 RAM/VRAM/PALETTE/SPRITE
   AddReadByte(0x080000, 0x0800FF, NULL, RAM+0x020200);
   sound_buff = 0xffff;
   AddReadBW(0xc0000e, 0xc0000f, NULL, (UINT8*)&sound_buff);
   AddReadByte(0x0C0000, 0x0C00FF, NULL, RAM+0x020000);			// DSW/INPUT
   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x060000, 0x07FFFF, NULL, RAM+0x000000);			// 68000 RAM/VRAM/PALETTE/SPRITE
   AddReadWord(0x080000, 0x0800FF, NULL, RAM+0x020200);
   AddReadWord(0x0C0000, 0x0C00FF, NULL, RAM+0x020000);			// DSW/INPUT
   AddWriteByte(0xBB0000, 0xBB0001, SoundWrite, NULL);			// Sound Comm
   AddWriteByte(0x060000, 0x07FFFF, NULL, RAM+0x000000);		// 68000 RAM/VRAM/PALETTE/SPRITE
   AddWriteByte(0x080000, 0x0800FF, NULL, RAM+0x020200);
   AddWriteByte(0x0A0000, 0x0A00FF, NULL, RAM+0x020100);
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteWord(0x060000, 0x07FFFF, NULL, RAM+0x000000);		// 68000 RAM/VRAM/PALETTE/SPRITE
   AddWriteWord(0x080000, 0x0800FF, NULL, RAM+0x020200);
   AddWriteWord(0x0A0000, 0x0A00FF, NULL, RAM+0x020100);
   finish_conf_68000(0);

}

#if 1
static void execute_tokib(void)
{
   static int ta;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 1);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(4,60));	// Sync

   ta++;

   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(1,60));       // Z80 4MHz (60fps) Timer on YM3812 needs fixing!!
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(1,60));       // Z80 4MHz (60fps)
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(1,60));       // Z80 4MHz (60fps)
/*    if(ta&1) */
/*       cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(1,60));    // Z80 4MHz (60fps) */
    cpu_int_nmi(CPU_Z80_0);
}
#else

extern void finish_speed_hack(INT32 diff);

static void execute_tokib(void)
{
  int frame = FRAME_Z80;
  int diff;
  int speed_hack = 0;
  cycles = 1;
  while (frame > 0) {
    if (speed_hack<1)
      diff = execute_one_z80_audio_frame(frame);
    else
      diff = frame;
    if (z80pc == 0xe42) {
      speed_hack++;
      if (speed_hack == 1 && frame > diff) {
	finish_speed_hack(frame-diff);
      }
    }
    if (cycles) // cycles = 0 if we reached the speed hack
      cpu_execute_cycles(CPU_68K_0, diff *3);	// M68020 32MHz (60fps)

    frame -= diff;
  }
  cpu_interrupt(CPU_68K_0, 1);
  cpu_int_nmi(CPU_Z80_0);

}
#endif

static void DrawToki(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta,ofs_x,col_msk;
   UINT8 *map;
   UINT8 *RAM_BG,*GFX_BG,*MSK_BG,*SCR_BG;

   ClearPaletteMap();

   if(RAM_FG0[0x710]!=0x44){
      RAM_BG = RAM_BG0;
      GFX_BG = GFX_BG0;
      MSK_BG = GFX_BG0_SOLID;
      SCR_BG = RAM+0x15008;
      ofs_x  = 0x101;
      col_msk = 0x30;
   }
   else{
      RAM_BG = RAM_BG1;
      GFX_BG = GFX_BG1;
      MSK_BG = GFX_BG1_SOLID;
      SCR_BG = RAM+0x15004;
      ofs_x  = 0x103;
      col_msk = 0x20;
   }

   // BG0
   // ---

   MAKE_SCROLL_512x512_2_16(
       ReadWord(SCR_BG+2)-ofs_x,
       ReadWord(SCR_BG)+16+1
   );

   START_SCROLL_512x512_2_16(32,32,256,224);

      MAP_PALETTE_MAPPED_NEW(
         ((ReadWord(&RAM_BG[zz])>>12)&0x0F)|col_msk,
         16,
         map
      );

      Draw16x16_Mapped_Rot(&GFX_BG[(ReadWord(&RAM_BG[zz])&0x0FFF)<<8], x, y, map);

   END_SCROLL_512x512_2_16();

   // BG1
   // ---

   if(RAM_FG0[0x710]==0x44){
      RAM_BG = RAM_BG0;
      GFX_BG = GFX_BG0;
      MSK_BG = GFX_BG0_SOLID;
      SCR_BG = RAM+0x15008;
      ofs_x  = 0x101;
      col_msk = 0x30;
   }
   else{
      RAM_BG = RAM_BG1;
      GFX_BG = GFX_BG1;
      MSK_BG = GFX_BG1_SOLID;
      SCR_BG = RAM+0x15004;
      ofs_x  = 0x103;
      col_msk = 0x20;
   }

   MAKE_SCROLL_512x512_2_16(
       ReadWord(SCR_BG+2)-ofs_x,
       ReadWord(SCR_BG)+16+1
   );

   START_SCROLL_512x512_2_16(32,32,256,224);

      ta = ReadWord(&RAM_BG[zz])&0x0FFF;
      if(MSK_BG[ta]){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ((ReadWord(&RAM_BG[zz])>>12)&0x0F)|col_msk,
            16,
            map
         );

         if(MSK_BG[ta]==1){			// Some pixels; trans
            Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }
         else{						// all pixels; solid
            Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }

      }

   END_SCROLL_512x512_2_16();

   // OBJECT
   // ------

   for(zz=0;zz<0x800;zz+=8){

      y = ReadWord(&RAM_SPR[zz+0]);

      if((y&0xF000)==0){

         y = (255 - y)&0x1FF;

         if((y>16)&&(y<224+32)){

            ta = ReadWord(&RAM_SPR[zz+2])&0x1FFF;

            if(GFX_SPR_SOLID[ta]){				// No pixels; skip

            x = (32+ReadWord(&RAM_SPR[zz+6]))&0x1FF;

            if((x>16)&&(x<256+32)){

            MAP_PALETTE_MAPPED_NEW(
               ((ReadWord(&RAM_SPR[zz+4])>>12)&0x0F)|0x00,
               16,
               map
            );

         if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
            switch(RAM_SPR[zz+3]&0xC0){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_SPR[zz+3]&0xC0){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }

            }

         }


         }

      }
      else{
         zz=0x800;
      }
   }

   // FG0
   // ---

   MAKE_SCROLL_256x256_2_8(
       0,
       16
   );

   START_SCROLL_256x256_2_8(32,32,256,224);

      ta = ReadWord(&RAM_FG0[zz])&0x0FFF;
      if(GFX_FG0_SOLID[ta]){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ((ReadWord(&RAM_FG0[zz])>>12)&0x0F)|0x10,
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

   END_SCROLL_256x256_2_8();
}

/*

Background Data (2 bytes per tile)
==================================

Byte(s)| Bit(s) | Description
-------+76543210+----------------------------
   00  |xxxx....| Tile Palette bank (0-15)
   00  |....xxxx| Tile Number (high 4 bits)
   01  |xxxxxxxx| Tile Number (low 8 bits)

Sprite Data (8 bytes per Sprite)
================================

Byte(s)| Bit(s) | Description
-------+76543210+----------------------------
   00  |.......x| Sprite Ypos (high bit)
   01  |xxxxxxxx| Sprite Ypos (low 8 bits)
   02  |.x......| Sprite Flip X-Axis
   02  |...xxxxx| Sprite Number (low 5 bits)
   03  |xxxxxxxx| Sprite Number (high 8 bits)
   04  |xxxx....| Sprite Palette Bank (0-15)
   06  |.......x| Sprite Xpos (high bit)
   07  |xxxxxxxx| Sprite Xpos (low 8 bits)

Palette Bank Info
=================

Banks 00-15: Sprites
Banks 16-31: Foreground
Banks 32-47: Backgound#1
Banks 48-63: Backgound#2

*/
static struct VIDEO_INFO video_tokib =
{
   DrawToki,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_tokib[] =
{
   { "toki", },
   { "tokib", },
   { NULL, },
};
GME( tokib, "Toki", BOOTLEG, 1989, GAME_PLATFORM,
	.long_name_jpn = "‚i‚•‚i‚•“`à",
);

