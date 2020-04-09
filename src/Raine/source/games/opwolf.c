/******************************************************************************/
/*                                                                            */
/*                  OPERATION WOLF (C) 1987 TAITO CORPORATION                 */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc002obj.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "msm5205.h"
#include "2151intf.h"
#include "gun.h"
#include "emumain.h"


static struct ROM_INFO rom_opwolf[] =
{
   {     "opwlf.13", 0x00080000, 0xf6acdab1, 0, 0, 0, },
   {     "opwlf.29", 0x00010000, 0xb71bc44c, 0, 0, 0, },
   {     "opwlf.30", 0x00010000, 0xfdabd8a5, 0, 0, 0, },
   {     "opwlf.39", 0x00010000, 0x216b4838, 0, 0, 0, },
   {     "opwlf.40", 0x00010000, 0x3ffbfe3a, 0, 0, 0, },
   {     "opwlf.72", 0x00080000, 0x89f889e5, 0, 0, 0, },
   {   "opwlf_s.10", 0x00010000, 0x45c7ace3, 0, 0, 0, },
   {   "opwlf_s.21", 0x00080000, 0xf3e19c64, 0, 0, 0, },
   {  "opwlfb.09", 0x00008000, 0xab27a3dd, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_opwolf[] =
{
   INP1( COIN1, 0x05C580, 0x04 ),
   INP1( COIN2, 0x05C581, 0x04 ),
   INP0( TILT, 0x02B10A, 0x08 ),
   INP0( SERVICE, 0x02B10A, 0x04 ),

   INP0( P1_START, 0x02B10A, 0x10 ),
   INP1( P1_UP, 0x02B408, 0x01 ),
   INP1( P1_DOWN, 0x02B408, 0x02 ),
   INP1( P1_LEFT, 0x02B408, 0x04 ),
   INP1( P1_RIGHT, 0x02B408, 0x08 ),
   INP0( P1_B1, 0x02B10A, 0x01 ),
   INP0( P1_B2, 0x02B10A, 0x02 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_operation_wolf_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_CONTINUE_PLAY( 0x00, 0x02),
   DSW_TEST_MODE( 0x00, 0x04),
   { _("Attract Mode"),          0x08, 0x02 },
   { _("Sound"),                 0x08},
   { _("Silence"),               0x00},
   { _("Coin Slot A"),           0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { _("Coin Slot B"),           0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_operation_wolf_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Start Ammo"),            0x0C, 0x04 },
   { _("6 Clips"),               0x0C},
   { _("7 Clips"),               0x08},
   { _("5 Clips"),               0x04},
   { _("4 Clips"),               0x00},
   { MSG_DSWB_BIT6,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT7,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { _("Cont Discount"),         0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Language"),              0x80, 0x02 },
   { _("Japanese"),              0x80},
   { _("English"),               0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_opwolf[] =
{
   { 0x02B000, 0xBF, dsw_data_operation_wolf_0 },
   { 0x02B002, 0xFF, dsw_data_operation_wolf_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_operation_wolf_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_opwolf[] =
{
   { 0x03FFFF, 0x02, romsw_data_operation_wolf_0 },
   { 0,        0,    NULL },
};


static struct YM2151interface ym2151_interface =
{
  1,			// 1 chip
  4000000,		// 4 MHz
  { YM3012_VOL(160,OSD_PAN_LEFT,160,OSD_PAN_RIGHT) },
  { NULL },
  { NULL }
};

static struct msm5205_adpcm_list opwolf_adpcm[] =
{
   { 0x000000,0x001B20-1 },	// 0xA0
   { 0x001B20,0x003520-1 },	// 0xB0
   { 0x003520,0x005520-1 },	// 0xB4
   { 0x005520,0x007F40-1 },	// 0xB0
   { 0x007F40,0x009F10-1 },	// 0xB0
   { 0x009F10,0x00E5D0-1 },	// 0xB0
   { 0x00E5D0,0x0135B0-1 },	// 0xB0
   { 0x0135B0,0x014BC0-1 },	// 0xB0
   { 0x014BC0,0x015FC0-1 },	// 0xB8
   { 0x015FC0,0x019450-1 },	// 0xB0
   { 0x019450,0x01A8E0-1 },	// 0xA4
   { 0x01A8E0,0x01D6F0-1 },	// 0xAC
   { 0x01D6F0,0x024500-1 },	// 0xAC
   { 0x024500,0x029FA0-1 },	// 0xAC
   { 0x029FA0,0x02D8C0-1 },	// 0xAC
   { 0x02D8C0,0x032BB0-1 },	// 0xA8
   { 0x032BB0,0x037FB0-1 },	// 0xA8
   { 0x037FB0,0x03CAA0-1 },	// 0xB0
   { 0x03CAA0,0x03D020-1 },	// 0xAC
   { 0x03D020,0x03DAF0-1 },	// 0xA8
   { 0x03DAF0,0x03E220-1 },	// 0xA4
   { 0x03E220,0x03EC30-1 },	// 0x80
   { 0x03EC30,0x03F380-1 },	// 0xA8
   { 0x040AD0,0x0415E0-1 },	// 0xAC
   { 0x0415E0,0x042380-1 },	// 0xAC
   { 0x042380,0x043880-1 },	// 0x88
   { 0x043880,0x044B70-1 },	// 0x88
   { 0x044B70,0x045F50-1 },	// 0x84
   { 0x045F50,0x046660-1 },	// 0xB8
   { 0x046660,0x046C00-1 },	// 0xB4
   { 0x046C00,0x0475F0-1 },	// 0xA0
   { 0x0475F0,0x0483F0-1 },	// 0xB0
   { 0x0483F0,0x04CE30-1 },	// 0xA4
   { 0x04CE30,0x04F9E0-1 },	// 0xA4
   { 0x04F9E0,0x0516E0-1 },	// 0xC0
   { 0x0516E0,0x0537B0-1 },	// 0xC0
   { 0x0537B0,0x054010-1 },	// 0xD0
   { 0x054010,0x058750-1 },	// 0xFC
   { 0x058750,0x059AB0-1 },	// 0xA8
   { 0x059AB0,0x05D990-1 },	// 0xC8
   { 0x05D990,0x061300-1 },	// 0xB0
   { 0x061300,0x068E40-1 },	// 0xE8
   { 0x068E40,0x069E30-1 },	// 0xEC
   { 0x069E30,0x06B960-1 },	// 0xB4
   { 0x06B960,0x06CBE0-1 },	// 0xB4
   { 0x06CBE0,0x06DC90-1 },	// 0xCC
   { 0x06F0A0,0x06FE10-1 },	// 0xFC
   { 0x06FE10,0x070E60-1 },	// 0xC8
   { 0x070E60,0x072010-1 },	// 0xC0
   { 0x072C10,0x074F50-1 },	// 0xB4
   { 0x074F50,0x0777C0-1 },	// 0xE4

   { 0x03F380,0x03FF80-1 },	// 0xAC
   { 0x03FF80,0x040AD0-1 },	// 0xA2
   { 0x06DC90,0x06F0A0-1 },	// 0xD4
   { 0x058750,0x059AB0-1 },	// 0x84
   { 0x058750,0x059AB0-1 },	// 0x98
   { 0x045F50,0x046660-1 },	// 0xF8
   { 0x045F50,0x046660-1 },	// 0x90
   { 0x072C10,0x074F50-1 },	// 0xE8
   { 0x045F50,0x046660-1 },	// 0xB0
};

static struct MSM5205buffer_interface msm5205_interface =
{
   2,
   { 8000, 8000 },
   { 223,  223  },
   { opwolf_adpcm, opwolf_adpcm},
   { sizeof(opwolf_adpcm) / sizeof(struct msm5205_adpcm_list), sizeof(opwolf_adpcm) / sizeof(struct msm5205_adpcm_list)},
   { NULL, NULL },
   { 0,    0    },
   { 0, 0 },
   MSM5205_MONO,
};

static struct SOUND_INFO sound_opwolf[] =
{
   { SOUND_YM2151J, &ym2151_interface,  },
   { SOUND_MSM5205_BUFF, &msm5205_interface, },
   { 0,             NULL,               },
};



static struct ROM_INFO rom_opwolfb[] =
{
   {  "opwlfb.01", 0x00010000, 0x0a65f256, 0, 0, 0, },
   {  "opwlfb.02", 0x00010000, 0x6231fdd0, 0, 0, 0, },
   {  "opwlfb.03", 0x00010000, 0xccf8ba80, 0, 0, 0, },
   {  "opwlfb.04", 0x00010000, 0xde0ca98d, 0, 0, 0, },
   {  "opwlfb.05", 0x00010000, 0xfd9e72c8, 0, 0, 0, },
   {  "opwlfb.06", 0x00010000, 0x317d0e66, 0, 0, 0, },
   {  "opwlfb.07", 0x00010000, 0xe1c4095e, 0, 0, 0, },
   {  "opwlfb.08", 0x00010000, 0x134d294e, 0, 0, 0, },
   {  "opwlfb.09", 0x00008000, 0xab27a3dd, 0, 0, 0, },
   {  "opwlfb.10", 0x00010000, 0x9ab6f75c, 0, 0, 0, },
   {  "opwlfb.11", 0x00010000, 0x342e318d, 0, 0, 0, },
   {  "opwlfb.12", 0x00010000, 0xd87e4405, 0, 0, 0, },
   {  "opwlfb.13", 0x00010000, 0x61230c6e, 0, 0, 0, },
   {  "opwlfb.14", 0x00010000, 0x663786eb, 0, 0, 0, },
   {  "opwlfb.15", 0x00010000, 0x315b8aa9, 0, 0, 0, },
   {  "opwlfb.16", 0x00010000, 0xe01099e3, 0, 0, 0, },
   {  "opwlfb.17", 0x00010000, 0x56fbe61d, 0, 0, 0, },
   {  "opwlfb.18", 0x00010000, 0xde9ab08e, 0, 0, 0, },
   {  "opwlfb.19", 0x00010000, 0x645cf85e, 0, 0, 0, },
   {  "opwlfb.20", 0x00010000, 0xd80b9cc6, 0, 0, 0, },
   {  "opwlfb.21", 0x00010000, 0x97d25157, 0, 0, 0, },
   {  "opwlfb.22", 0x00010000, 0x9228481f, 0, 0, 0, },
   {  "opwlfb.23", 0x00010000, 0xa874c703, 0, 0, 0, },
   {  "opwlfb.24", 0x00010000, 0x8efc5d4d, 0, 0, 0, },
   {  "opwlfb.25", 0x00010000, 0x85b87f58, 0, 0, 0, },
   {  "opwlfb.26", 0x00010000, 0x86d1d42d, 0, 0, 0, },
   {  "opwlfb.27", 0x00010000, 0x441211a6, 0, 0, 0, },
   {  "opwlfb.28", 0x00010000, 0x281b2175, 0, 0, 0, },
   {  "opwlfb.29", 0x00010000, 0x05a9eac0, 0, 0, 0, },
   {  "opwlfb.30", 0x00008000, 0x0669b94c, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *RAM_OBJECT;
static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *Z80ROM2;

static void OpWolfWriteADPCMA(UINT16 offset, UINT8 data);
static void OpWolfWriteADPCMB(UINT16 offset, UINT8 data);

static int romset;	// 0=ORIGINAL; 1=BOOTLEG

static int x1,myy1,x11,myy11;

static int CChipReadB(UINT32 address)
{
   int i;

   i=address&0x0FFE;

   return(Z80ROM2[0xC000+(i>>1)]);
}

static int CChipReadW(UINT32 address)
{
   return(CChipReadB(address+1));
}

static void CChipWriteB(UINT32 address, int data)
{
   int i;

   i=address&0x0FFE;

   Z80ROM2[0xC000+(i>>1)]=data;
}

static void CChipWriteW(UINT32 address, int data)
{
   CChipWriteB(address+1,data&0xFF);
}


static int BadReadByte(UINT32 address)
{
   return(0);
}

static int BadReadWord(UINT32 address)
{
   return(0);
}

static void BadWriteByte(UINT32 address, UINT8 data)
{
}

static void BadWriteWord(UINT32 address, UINT16 data)
{
}

static void clear_ram() {
  // Clears the z80 c-chip ram, or reseting the game will hang
  memset(Z80ROM2+0x8000,0,0x8000);
}

static void load_opwolf(void)
{
   UINT8 *TMP;
   int ta,tb;
   if (is_current_game("opwolf"))
       romset = 0;
   else if (is_current_game("opwolfb"))
       romset = 1;

   RAMSize=0x60000;

   set_reset_function(clear_ram);

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x40000))) return;
   if(!(GFX=AllocateMem(0x200000))) return;

   GFX_SPR	= GFX+0x100000;

   Z80ROM2=RAM+0x50000;			// C-CHIP ROM/RAM

   if(romset==1){			// BOOTLEG

   tb=0;
   if(!load_rom("opwlfb.08", RAM+0x00000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.06", RAM+0x10000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.07", RAM+0x20000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.05", RAM+0x30000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.04", RAM+0x40000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.02", RAM+0x50000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.03", RAM+0x60000, 0x10000)) return;	// 8x8 TILES
   if(!load_rom("opwlfb.01", RAM+0x70000, 0x10000)) return;	// 8x8 TILES
   for(ta=0;ta<0x40000;ta++,tb+=4){
      GFX[tb+0]=RAM[ta+0x00000]>>4;
      GFX[tb+1]=RAM[ta+0x00000]&15;
      GFX[tb+2]=RAM[ta+0x40000]>>4;
      GFX[tb+3]=RAM[ta+0x40000]&15;
   }
   if(!load_rom("opwlfb.14", RAM+0x00000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.15", RAM+0x10000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.16", RAM+0x20000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.17", RAM+0x30000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.18", RAM+0x40000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.19", RAM+0x50000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.20", RAM+0x60000, 0x10000)) return;	// 16x16 TILES
   if(!load_rom("opwlfb.21", RAM+0x70000, 0x10000)) return;	// 16x16 TILES
   for(ta=0;ta<0x40000;ta++,tb+=4){
      GFX[tb+0]=RAM[ta+0x00000]>>4;
      GFX[tb+1]=RAM[ta+0x00000]&15;
      GFX[tb+2]=RAM[ta+0x40000]>>4;
      GFX[tb+3]=RAM[ta+0x40000]&15;
   }

   if(!load_rom("opwlfb.12", RAM, 0x10000)) return;		// 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("opwlfb.10", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("opwlfb.13", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("opwlfb.11", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("opwlfb.09", Z80ROM2, 0x8000)) return;	// Z80 C-CHIP ROM

   }
   else{	// ORIGINAL

   tb=0;
   if(!load_rom("opwlf.13", RAM, 0x80000)) return;		// 8x8 TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb++]=RAM[ta+1]>>4;
      GFX[tb++]=RAM[ta+1]&15;
      GFX[tb++]=RAM[ta+0]>>4;
      GFX[tb++]=RAM[ta+0]&15;
   }
   if(!load_rom("opwlf.72", RAM, 0x80000)) return;		// 16x16 TILES
   for(ta=0;ta<0x80000;ta+=2){
      GFX[tb++]=RAM[ta+1]>>4;
      GFX[tb++]=RAM[ta+1]&15;
      GFX[tb++]=RAM[ta+0]>>4;
      GFX[tb++]=RAM[ta+0]&15;
   }

   if(!load_rom("opwlf.40", RAM, 0x10000)) return;		// 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("opwlf.30", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("opwlf.39", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("opwlf.29", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("opwlfb.09", Z80ROM2, 0x8000)) return;	// Z80 C-CHIP ROM

   }

   /*--------[C-Chip Z80]---------*/

   Z80ROM2[0x19B]=0xC3;
   Z80ROM2[0x19C]=0x80;
   Z80ROM2[0x19D]=0x00;

   Z80ROM2[0x080]=0x21;
   Z80ROM2[0x081]=0x1B;
   Z80ROM2[0x082]=0xC0;

   Z80ROM2[0x083]=0xD3;  // OUTA (AAh)
   Z80ROM2[0x084]=0xAA;  //

   Z80ROM2[0x0570]=0x18;
   Z80ROM2[0x059E]=0x18;

   SetStopZ80BMode2(0x019E);

   memset(Z80ROM2+0x8000,0x00,0x8000);

   AddZ80BROMBase(Z80ROM2, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0xFFFF, NULL,                        Z80ROM2+0x0000); // Z80 ROM/RAM
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80BReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80BWriteByte(0x0000, 0xFFFF, NULL,                       Z80ROM2+0x0000); // Z80 RAM
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80BWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80BReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,          NULL);
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80BWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80BInit();

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;

   if(romset==0){
   if(!load_rom("opwlf_s.10", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM
   }
   else{
   if(!load_rom("opwlfb.30", Z80ROM, 0x8000)) return;	// Z80 SOUND ROM
   }

   tb=16;			// First Sample=1
   for(ta=0;ta<(0x3C*7);ta+=7){
      Z80ROM[ta+0x2F00]=tb>>16;
      Z80ROM[ta+0x2F02]=tb>>8;
      Z80ROM[ta+0x2F01]=tb;
      tb+=16;			// Next Sample
   }

   AddTaitoYM2151(0x028A, 0x0219, 0x10000, (void *) OpWolfWriteADPCMA, (void *) OpWolfWriteADPCMB);

   /*------[Sample Setup]--------*/

   if(!(PCMROM=AllocateMem(0x80000))) return;

   if(romset==0){
   if(!load_rom("opwlf_s.21", PCMROM, 0x80000)) return;
   }
   else{
   if(!(TMP=AllocateMem(0x80000))) return;

   if(!load_rom("opwlfb.29", TMP+0x00000, 0x10000)) return;
   if(!load_rom("opwlfb.28", TMP+0x10000, 0x10000)) return;
   if(!load_rom("opwlfb.27", TMP+0x20000, 0x10000)) return;
   if(!load_rom("opwlfb.26", TMP+0x30000, 0x10000)) return;
   if(!load_rom("opwlfb.25", TMP+0x40000, 0x10000)) return;
   if(!load_rom("opwlfb.24", TMP+0x50000, 0x10000)) return;
   if(!load_rom("opwlfb.23", TMP+0x60000, 0x10000)) return;
   if(!load_rom("opwlfb.22", TMP+0x70000, 0x10000)) return;
   for(ta=0;ta<0x40000;ta++){
      PCMROM[ta+ta+0]=TMP[ta+0x00000];
      PCMROM[ta+ta+1]=TMP[ta+0x40000];
   }

   FreeMem(TMP);
   }

   msm5205_interface.rom[0] = PCMROM;
   msm5205_interface.romsize[0] = 0x80000;
   msm5205_interface.rom[1] = PCMROM;
   msm5205_interface.romsize[1] = 0x80000;
   msm5205_interface.updatemode = MSM5205_MONO;

   ROM[0x0988]=0x60;	// FIX C-CHIP USER ERROR

   //ROM[0x0C32]=0x60;	// COIN ERROR

   WriteWord68k(&ROM[0xBB72],0x4E71);		// nop

   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x04F4],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x04F8],0x00AA0000);
   WriteWord68k(&ROM[0x04FC],0x6100-16);	// <loop>

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x2B200;
   RAM_OBJECT = RAM+0x28000;

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX,     0x4000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x1000);

   set_colour_mapper(&col_map_xxxx_rrrr_gggg_bbbb);
   InitPaletteMap(RAM+0x2A000, 0x100, 0x10, 0x1000);


/*
 *  StarScream Main 68000 Setup
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x107FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0xC00000, 0xC1FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0xD00000, 0xD01FFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddReadByte(0x0FF000, 0x0FFFFF, CChipReadB, NULL);			// C-CHIP
   AddReadByte(0x380000, 0x38000F, NULL, RAM+0x02B000);			// I/O RAM
   AddReadByte(0x0F0000, 0x0F000F, NULL, RAM+0x02B100);			// I/O RAM
   AddReadByte(0x3E0000, 0x3E0003, tc0140syt_read_main_68k, NULL);	// SOUND
   AddReadByte(0x000000, 0xFFFFFF, BadReadByte, NULL);			// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x107FFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0x200000, 0x2007FF, NULL, RAM+0x02A000);			// COLOR RAM
   AddReadWord(0xC00000, 0xC1FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x0FF000, 0x0FFFFF, CChipReadW, NULL);			// C-CHIP
   AddReadWord(0x380000, 0x38000F, NULL, RAM+0x02B000);			// I/O RAM
   AddReadWord(0x3A0000, 0x3A000F, NULL, RAM+0x02B400);			// GUN
   AddReadWord(0x0F0000, 0x0F000F, NULL, RAM+0x02B100);			// I/O RAM
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x107FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0xC00000, 0xC1FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xD00000, 0xD01FFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteByte(0x0FF000, 0x0FFFFF, CChipWriteB, NULL);			// C-CHIP
   AddWriteByte(0x3E0000, 0x3E0003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, BadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x107FFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0xC00000, 0xC1FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xD00000, 0xD01FFF, NULL, RAM_OBJECT);			// OBJECT RAM
   AddWriteWord(0x200000, 0x2007FF, NULL, RAM+0x02A000);		// COLOR RAM
   AddWriteWord(0xC20000, 0xC20003, NULL, RAM_SCROLL+6);		// SCROLL Y
   AddWriteWord(0xC40000, 0xC40003, NULL, RAM_SCROLL+0);		// SCROLL X
   AddWriteWord(0xC50000, 0xC50001, NULL, RAM_SCROLL+14);		// CTRL
   AddWriteWord(0x0FF000, 0x0FFFFF, CChipWriteW, NULL);			// C-CHIP
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   GameMouse=1;
}

static void execute_opwolf(void)
{
   /*------[Mouse Hack]-------*/

   set_mouse_range(0,0,319,239);

   x11=mouse_x;
   myy11=mouse_y;

   x1=x11+16;
   if(romset==1){
      myy1=myy11-8;
   }
   else{
      myy1=myy11-24;
   }

   if(x1<0)   x1=0;
   if(x1>319) x1=319;
   if(myy1<0)   myy1=0;
   if(myy1>239) myy1=239;

   if(mouse_b&1) RAM[0x2B10A]&= ~0x01;
   if(mouse_b&2) RAM[0x2B10A]&= ~0x02;

   /*-----[Keyboard Hack]-----*/

   if(((RAM[0x2B408]&0x01)!=0)&&(myy1>0))   myy1--;
   if(((RAM[0x2B408]&0x02)!=0)&&(myy1<239)) myy1++;
   if(((RAM[0x2B408]&0x04)!=0)&&(x1>0))   x1--;
   if(((RAM[0x2B408]&0x08)!=0)&&(x1<319)) x1++;

   /*----[Write Positions]----*/

   RAM[0x2B400]=x1;
   RAM[0x2B402]=myy1;

   cpu_execute_cycles(CPU_Z80_1, 400000);		// C-CHIP Z80 4Mhz?
   cpu_interrupt(CPU_Z80_1, 0x38);

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)		// MAIN 68000 12Mhz?
   cpu_interrupt(CPU_68K_0, 5);

   Taito2151_FrameFast();	// Z80 and YM2151
}


static void DrawOperationWolf(void)
{
   int x,y;

   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   if(RefreshBuffers){

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = NULL;
   init_tc0100scn(0);

   }

   // Init tc0002obj emulation
   // ------------------------

   //tc0002obj.ctrl	= ReadWord(&RAM[0x1B010]);
   tc0002obj.ctrl	= 0x2000;

   if(RefreshBuffers){

   tc0002obj.RAM	= RAM_OBJECT;
   tc0002obj.GFX	= GFX_SPR;
   tc0002obj.MASK	= GFX_SPR_SOLID;
   tc0002obj.bmp_x	= 32;
   tc0002obj.bmp_y	= 32;
   tc0002obj.bmp_w	= 320;
   tc0002obj.bmp_h	= 240;
   tc0002obj.tile_mask	= 0x0FFF;
   tc0002obj.ofs_x	= 0;
   tc0002obj.ofs_y	= -8;

   }

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1+OBJECT
   // ----------

   if((tc0002obj.ctrl & 0x2000)==0){
      render_tc0100scn_layer_mapped(0,1,1);
      render_tc0002obj_mapped();
   }
   else{
      render_tc0002obj_mapped();
      render_tc0100scn_layer_mapped(0,1,1);
   }

   // CURSOR
   // ------

   x=(32+x11)-7;
   y=(32+myy11)-7;
   if((x>16)&&(y>16)&&(x<320+32)&&(y<224+32)){
     disp_gun(0,x,y);
   }
}

/*-------[ADPCM PORT]-------*/

static int ad[8];

static void OpWolfWriteADPCMA(UINT16 offset, UINT8 data)
{
   int ta=0;

   offset&=7;

   ad[offset]=data;

   if(offset==6){

      print_debug("OpWolfADPCM(%02X%02X:%02X%02X:%02X%02X)\n",ad[1],ad[0],ad[3],ad[2],ad[4],ad[5]);

   ta=ad[0];

   if((ta>0)&&(ta<=0x3C)){
      MSM5205buffer_request( 0, ta-1 );
   }

   }
}

/*------[ADPCM PORT 2]------*/

static int ad2[8];

static void OpWolfWriteADPCMB(UINT16 offset, UINT8 data)
{
   int ta=0;

   offset&=7;

   ad2[offset]=data;

   if(offset==6){

      print_debug("OpWolfADPCM#2(%02X%02X:%02X%02X:%02X%02X)\n",ad2[1],ad2[0],ad2[3],ad2[2],ad2[4],ad2[5]);

   ta=ad2[0];

   if((ta>0)&&(ta<=0x3C)){
      MSM5205buffer_request( 1, ta-1 );
   }

   }
}
static struct VIDEO_INFO video_opwolf =
{
   DrawOperationWolf,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_opwolf[] =
{
   { "operation_wolf", },
   { "opwolf", },
   { "opwolfb", },
   { "opwolfu", },
   { NULL, },
};
GME( opwolf, "Operation Wolf", TAITO, 1987, GAME_SHOOT,
	.romsw = romsw_opwolf,
	.long_name_jpn = "オペレーションウルフ",
	.board = "B20",
);
static struct DIR_INFO dir_opwolfb[] =
{
   { "operation_wolf_bootleg", },
   { "opwolfbl", },
   { "opwolfb", },
   { ROMOF("opwolf"), },
   { CLONEOF("opwolf"), },
   { NULL, },
};
CLNE( opwolfb, opwolf, "Operation Bear", BOOTLEG, 1987, GAME_SHOOT,
	.long_name_jpn = "オペレーションウルフ (bootleg)",
);

