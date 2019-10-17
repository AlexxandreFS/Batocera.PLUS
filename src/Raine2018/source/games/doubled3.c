/******************************************************************************/
/*                                                                            */
/*                  DOUBLE DRAGON 3 (C) 1990 TECHNOS JAPAN                    */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "tchnosnd.h"


static struct ROM_INFO rom_ddragon3[] =
{
   {        "30a14", 0x00040000, 0xf42fe016, 0, 0, 0, },
   {        "30a15", 0x00020000, 0xad50e92c, 0, 0, 0, },
   {       "dd3.j8", 0x00040000, 0xc28b53cd, 0, 0, 0, },
   {       "dd3.3e", 0x00020000, 0x726c49b7, 0, 0, 0, },
   {       "dd3.3d", 0x00020000, 0x37a1c335, 0, 0, 0, },
   {       "dd3.3c", 0x00020000, 0x2bcfe63c, 0, 0, 0, },
   {       "dd3.3b", 0x00020000, 0xb864cf17, 0, 0, 0, },
   {       "dd3.2e", 0x00020000, 0x8c71eb06, 0, 0, 0, },
   {       "dd3.2d", 0x00020000, 0x3e134be9, 0, 0, 0, },
   {       "dd3.2c", 0x00020000, 0xb4115ef0, 0, 0, 0, },
   {       "dd3.2b", 0x00020000, 0x4639333d, 0, 0, 0, },
   {       "dd3.1e", 0x00020000, 0x04420cc8, 0, 0, 0, },
   {       "dd3.1d", 0x00020000, 0x33f97b2f, 0, 0, 0, },
   {       "dd3.1c", 0x00020000, 0x0f9a8f2a, 0, 0, 0, },
   {       "dd3.1b", 0x00020000, 0x15c91772, 0, 0, 0, },
   {       "dd3.0e", 0x00020000, 0x894734b3, 0, 0, 0, },
   {       "dd3.0d", 0x00020000, 0xcd504584, 0, 0, 0, },
   {       "dd3.0c", 0x00020000, 0x38e8a9ad, 0, 0, 0, },
   {       "dd3.0b", 0x00020000, 0x80c1cb74, 0, 0, 0, },
   {        "dd3.e", 0x00040000, 0x9bf1538e, 0, 0, 0, },
   {        "dd3.f", 0x00040000, 0x89d58d32, 0, 0, 0, },
   {        "dd3.a", 0x00040000, 0x0f74ea1c, 0, 0, 0, },
   {        "dd3.b", 0x00040000, 0x8f671a62, 0, 0, 0, },
   {       "dd3.0a", 0x00010000, 0x5a47e7a4, 0, 0, 0, },
   {       "dd3.1a", 0x00010000, 0x15e43d12, 0, 0, 0, },
   {       "dd3.2a", 0x00010000, 0x785d71b0, 0, 0, 0, },
   {       "dd3.3a", 0x00010000, 0x20d64bea, 0, 0, 0, },
   {       "dd3.06", 0x00010000, 0x1e974d9b, 0, 0, 0, },
   {       "dd3.j7", 0x00040000, 0x3af21dbe, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ddragon3[] =
{
   INP0( COIN1, 0x00C002, 0x01 ),
   INP0( COIN2, 0x00C002, 0x02 ),

   INP0( P1_START, 0x00C000, 0x80 ),
   INP0( P1_UP, 0x00C000, 0x04 ),
   INP0( P1_DOWN, 0x00C000, 0x08 ),
   INP0( P1_LEFT, 0x00C000, 0x02 ),
   INP0( P1_RIGHT, 0x00C000, 0x01 ),
   INP0( P1_B1, 0x00C000, 0x10 ),
   INP0( P1_B2, 0x00C000, 0x20 ),
   INP0( P1_B3, 0x00C000, 0x40 ),

   INP0( P2_START, 0x00C001, 0x80 ),
   INP0( P2_UP, 0x00C001, 0x04 ),
   INP0( P2_DOWN, 0x00C001, 0x08 ),
   INP0( P2_LEFT, 0x00C001, 0x02 ),
   INP0( P2_RIGHT, 0x00C001, 0x01 ),
   INP0( P2_B1, 0x00C001, 0x10 ),
   INP0( P2_B2, 0x00C001, 0x20 ),
   INP0( P2_B3, 0x00C001, 0x40 ),

   INP0( P3_START, 0x00C006, 0x80 ),
   INP0( P3_UP, 0x00C006, 0x04 ),
   INP0( P3_DOWN, 0x00C006, 0x08 ),
   INP0( P3_LEFT, 0x00C006, 0x02 ),
   INP0( P3_RIGHT, 0x00C006, 0x01 ),
   INP0( P3_B1, 0x00C006, 0x10 ),
   INP0( P3_B2, 0x00C006, 0x20 ),
   INP0( P3_B3, 0x00C006, 0x40 ),
   END_INPUT
};

static struct DSW_DATA dsw_data_double_dragon_3_0[] =
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

static struct DSW_DATA dsw_data_double_dragon_3_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Player Hurt Player"),    0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { _("Coin Statistics"),       0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { _("Stage Clear Life"),      0x20, 0x02 },
   { "50",                    0x20},
   { "0",                     0x00},
   { _("Starting Life"),         0x40, 0x02 },
   { "230",                   0x40},
   { "200",                   0x00},
   { MSG_CABINET, 0x80, 2 },
   { _("3 Players"), 0x00 },
   { _("2 Players"), 0x80 },
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ddragon3[] =
{
   { 0x00C004, 0xFF, dsw_data_double_dragon_3_0 },
   { 0x00C005, 0x7F, dsw_data_double_dragon_3_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_ddrago3b[] =
{
   {       "dd3.01", 0x00020000, 0x68321d8b, 0, 0, 0, },
   {       "dd3.02", 0x00020000, 0x38d9ae75, 0, 0, 0, },
   {       "dd3.03", 0x00020000, 0xbc05763b, 0, 0, 0, },
   {       "dd3.j8", 0x00040000, 0xc28b53cd, 0, 0, 0, },
   {       "dd3.3e", 0x00020000, 0x726c49b7, 0, 0, 0, },
   {       "dd3.3d", 0x00020000, 0x37a1c335, 0, 0, 0, },
   {       "dd3.3c", 0x00020000, 0x2bcfe63c, 0, 0, 0, },
   {       "dd3.3b", 0x00020000, 0xb864cf17, 0, 0, 0, },
   {       "dd3.2e", 0x00020000, 0x8c71eb06, 0, 0, 0, },
   {       "dd3.2d", 0x00020000, 0x3e134be9, 0, 0, 0, },
   {       "dd3.2c", 0x00020000, 0xb4115ef0, 0, 0, 0, },
   {       "dd3.2b", 0x00020000, 0x4639333d, 0, 0, 0, },
   {       "dd3.1e", 0x00020000, 0x04420cc8, 0, 0, 0, },
   {       "dd3.1d", 0x00020000, 0x33f97b2f, 0, 0, 0, },
   {       "dd3.1c", 0x00020000, 0x0f9a8f2a, 0, 0, 0, },
   {       "dd3.1b", 0x00020000, 0x15c91772, 0, 0, 0, },
   {       "dd3.0e", 0x00020000, 0x894734b3, 0, 0, 0, },
   {       "dd3.0d", 0x00020000, 0xcd504584, 0, 0, 0, },
   {       "dd3.0c", 0x00020000, 0x38e8a9ad, 0, 0, 0, },
   {       "dd3.0b", 0x00020000, 0x80c1cb74, 0, 0, 0, },
   {        "dd3.e", 0x00040000, 0x9bf1538e, 0, 0, 0, },
   {        "dd3.f", 0x00040000, 0x89d58d32, 0, 0, 0, },
   {        "dd3.a", 0x00040000, 0x0f74ea1c, 0, 0, 0, },
   {        "dd3.b", 0x00040000, 0x8f671a62, 0, 0, 0, },
   {       "dd3.0a", 0x00010000, 0x5a47e7a4, 0, 0, 0, },
   {       "dd3.1a", 0x00010000, 0x15e43d12, 0, 0, 0, },
   {       "dd3.2a", 0x00010000, 0x785d71b0, 0, 0, 0, },
   {       "dd3.3a", 0x00010000, 0x20d64bea, 0, 0, 0, },
   {       "dd3.06", 0x00010000, 0x1e974d9b, 0, 0, 0, },
   {       "dd3.j7", 0x00040000, 0x3af21dbe, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ddrago3b[] =
{
   INP0( COIN1, 0x00C001, 0x01 ),
   INP0( COIN2, 0x00C001, 0x02 ),
   INP0( TILT, 0x00C005, 0x10 ),

   INP0( P1_START, 0x00C000, 0x80 ),
   INP0( P1_UP, 0x00C000, 0x04 ),
   INP0( P1_DOWN, 0x00C000, 0x08 ),
   INP0( P1_LEFT, 0x00C000, 0x02 ),
   INP0( P1_RIGHT, 0x00C000, 0x01 ),
   INP0( P1_B1, 0x00C000, 0x10 ),
   INP0( P1_B2, 0x00C000, 0x20 ),
   INP0( P1_B3, 0x00C000, 0x40 ),

   INP0( P2_START, 0x00C002, 0x80 ),
   INP0( P2_UP, 0x00C002, 0x04 ),
   INP0( P2_DOWN, 0x00C002, 0x08 ),
   INP0( P2_LEFT, 0x00C002, 0x02 ),
   INP0( P2_RIGHT, 0x00C002, 0x01 ),
   INP0( P2_B1, 0x00C002, 0x10 ),
   INP0( P2_B2, 0x00C002, 0x20 ),
   INP0( P2_B3, 0x00C002, 0x40 ),

   INP0( P3_START, 0x00C004, 0x80 ),
   INP0( P3_UP, 0x00C004, 0x04 ),
   INP0( P3_DOWN, 0x00C004, 0x08 ),
   INP0( P3_LEFT, 0x00C004, 0x02 ),
   INP0( P3_RIGHT, 0x00C004, 0x01 ),
   INP0( P3_B1, 0x00C004, 0x10 ),
   INP0( P3_B2, 0x00C004, 0x20 ),
   INP0( P3_B3, 0x00C004, 0x40 ),
   END_INPUT
};

static struct DSW_INFO dsw_ddrago3b[] =
{
   { 0x00C010, 0xFF, dsw_data_double_dragon_3_0 },
   { 0x00C011, 0x7F, dsw_data_double_dragon_3_1 },
   { 0,        0,    NULL,      },
};


static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_SPR;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void DD3SoundWrite(UINT32 address, UINT8 data)
{
   RAM[(address-0x100000+0x1C000)^1]=data;

   if(address==0x100003) TechnosSoundWrite68k(address,data);
}

static void DD3bSoundWrite(UINT32 address, UINT8 data)
{
   RAM[(address-0x140000+0x1C000)^1]=data;

   if(address==0x140003) TechnosSoundWrite68k(address,data);
}

static void DD3MemoryMap(void)
{
   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x080000, 0x080FFF, NULL, RAM+0x008000);			// BG1 RAM
   AddReadByte(0x180000, 0x180FFF, NULL, RAM+0x009000);			// SPRITE RAM
   AddReadByte(0x082000, 0x0827FF, NULL, RAM+0x00A000);			// BG0 RAM
   AddReadByte(0x0C0000, 0x0C000F, NULL, RAM+0x004000);			// SCROLL RAM
   AddReadByte(0x140000, 0x1405FF, NULL, RAM+0x02C000);			// COLOR RAM
   AddReadByte(0x100000, 0x100007, NULL, RAM+0x00C000);			// INPUT
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x080000, 0x080FFF, NULL, RAM+0x008000);			// BG1 RAM
   AddReadWord(0x180000, 0x180FFF, NULL, RAM+0x009000);			// SPRITE RAM
   AddReadWord(0x082000, 0x0827FF, NULL, RAM+0x00A000);			// BG0 RAM
   AddReadWord(0x0C0000, 0x0C000F, NULL, RAM+0x004000);			// SCROLL RAM
   AddReadWord(0x140000, 0x1405FF, NULL, RAM+0x02C000);			// COLOR RAM
   AddReadWord(0x100000, 0x100007, NULL, RAM+0x00C000);			// INPUT
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x080000, 0x080FFF, NULL, RAM+0x008000);		// BG1 RAM
   AddWriteByte(0x180000, 0x180FFF, NULL, RAM+0x009000);		// SPRITE RAM
   AddWriteByte(0x082000, 0x0827FF, NULL, RAM+0x00A000);		// BG0 RAM
   AddWriteByte(0x140000, 0x1405FF, NULL, RAM+0x02C000);		// COLOR RAM
   AddWriteByte(0x0C0000, 0x0C000F, NULL, RAM+0x004000);		// SCROLL RAM
   AddWriteByte(0x100000, 0x10000F, DD3SoundWrite, NULL);		// SOUND
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x080000, 0x080FFF, NULL, RAM+0x008000);		// BG1 RAM
   AddWriteWord(0x180000, 0x180FFF, NULL, RAM+0x009000);		// SPRITE RAM
   AddWriteWord(0x082000, 0x0827FF, NULL, RAM+0x00A000);		// BG0 RAM
   AddWriteWord(0x140000, 0x1405FF, NULL, RAM+0x02C000);		// COLOR RAM
   AddWriteWord(0x0C0000, 0x0C000F, NULL, RAM+0x004000);		// SCROLL RAM
   AddWriteWord(0x100000, 0x10000F, NULL, RAM+0x01C000);		// PRIORITY
   AddWriteWord(-1, -1, NULL, NULL);
}

static void DD3bMemoryMap(void)
{
   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x080000, 0x083FFF, NULL, RAM+0x008000);			// OBJECT RAM
   AddReadByte(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);			// SCROLL RAM
   AddReadByte(0x100000, 0x100FFF, NULL, RAM+0x02C000);			// COLOR RAM
   AddReadByte(0x180000, 0x18000F, NULL, RAM+0x00C000);			// INPUT
   AddReadByte(0x140000, 0x14000F, NULL, RAM+0x01C000);			// ?
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x080000, 0x083FFF, NULL, RAM+0x008000);			// OBJECT RAM
   AddReadWord(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);			// SCROLL RAM
   AddReadWord(0x100000, 0x100FFF, NULL, RAM+0x02C000);			// COLOR RAM
   AddReadWord(0x180000, 0x18000F, NULL, RAM+0x00C000);			// INPUT
   AddReadWord(0x140000, 0x14000F, NULL, RAM+0x01C000);			// ?
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x080000, 0x083FFF, NULL, RAM+0x008000);		// OBJECT RAM
   AddWriteByte(0x100000, 0x100FFF, NULL, RAM+0x02C000);		// COLOR RAM
   AddWriteByte(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);		// SCROLL RAM
   AddWriteByte(0x180000, 0x18000F, NULL, RAM+0x00C000);		// INPUT
   AddWriteByte(0x140000, 0x14000F, DD3bSoundWrite, NULL);		// SOUND
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x1C0000, 0x1C3FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x080000, 0x083FFF, NULL, RAM+0x008000);		// OBJECT RAM
   AddWriteWord(0x100000, 0x100FFF, NULL, RAM+0x02C000);		// COLOR RAM
   AddWriteWord(0x0C0000, 0x0C3FFF, NULL, RAM+0x004000);		// SCROLL RAM
   AddWriteWord(0x180000, 0x18000F, NULL, RAM+0x00C000);		// INPUT
   AddWriteWord(0x140000, 0x14000F, NULL, RAM+0x01C000);		// ?
   AddWriteWord(-1, -1, NULL, NULL);
}

static void load_ddragon3(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   if(!(GFX=AllocateMem(0x680000))) return;
   if(!(TMP=AllocateMem(0x0D0000))) return;

   if(!load_rom("dd3.0e", TMP+0x00000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.0d", TMP+0x20000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.0c", TMP+0x40000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.0b", TMP+0x60000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.0a", TMP+0x80000, 0x10000)) return;	// GFX SPR
   if(!load_rom("dd3.a",  TMP+0x90000, 0x40000)) return;	// GFX BG0/BG1
   tb=0;
   for(ta=0;ta<0xD0000;ta++){
      tc=TMP[ta+0];
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
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("dd3.1e", TMP+0x00000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.1d", TMP+0x20000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.1c", TMP+0x40000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.1b", TMP+0x60000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.1a", TMP+0x80000, 0x10000)) return;	// GFX SPR
   if(!load_rom("dd3.b",  TMP+0x90000, 0x40000)) return;	// GFX BG0/BG1
   tb=0;
   for(ta=0;ta<0xD0000;ta++){
      tc=TMP[ta+0];
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
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("dd3.2e", TMP+0x00000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.2d", TMP+0x20000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.2c", TMP+0x40000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.2b", TMP+0x60000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.2a", TMP+0x80000, 0x10000)) return;	// GFX SPR
   if(!load_rom("dd3.e",  TMP+0x90000, 0x40000)) return;	// GFX BG0/BG1
   tb=0;
   for(ta=0;ta<0xD0000;ta++){
      tc=TMP[ta+0];
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
      else{if((tb&0xFF)==8){tb-=8;}}
   }
   if(!load_rom("dd3.3e", TMP+0x00000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.3d", TMP+0x20000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.3c", TMP+0x40000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.3b", TMP+0x60000, 0x20000)) return;	// GFX SPR
   if(!load_rom("dd3.3a", TMP+0x80000, 0x10000)) return;	// GFX SPR
   if(!load_rom("dd3.f",  TMP+0x90000, 0x40000)) return;	// GFX BG0/BG1
   tb=0;
   for(ta=0;ta<0xD0000;ta++){
      tc=TMP[ta+0];
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
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   FreeMem(TMP);

   RAMSize=0x40000+0x10000;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   /*-------[SOUND SYSTEM INIT]-------*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("dd3.06", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   Z80ROM[0x026E]=0x00;

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("dd3.j7",PCMROM,0x40000)) return;		// ADPCM ROM Bank 0
   if(!load_rom("dd3.j8",PCMROM + 0x40000,0x40000)) return;	// ADPCM ROM Bank 1

   AddTechnosSound(0x0041, 0x003B, 0x10000, PCMROM, PCMROM+0x40000, 63);

   /*---------------------------------*/

   if (is_current_game("ddragon3")) {
     if(!load_rom("30a15", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta]=RAM[ta];
     }
     if(!load_rom("30a14", RAM, 0x40000)) return;
     for(ta=0;ta<0x40000;ta++){
        ROM[ta+ta+1]=RAM[ta];
     }
   }
   else {
     if(!load_rom("dd3.03", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta]=RAM[ta];
     }
     if(!load_rom("dd3.01", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta+1]=RAM[ta];
     }
     if(!load_rom("dd3.02", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta+0x40000]=RAM[ta];
        ROM[ta+ta+0x40001]=RAM[ta];
     }
   }

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x0C000,0xFF,0x00010);

   RAM_BG0 = RAM+0xA000;
   RAM_BG1 = RAM+0x8000;
   RAM_SPR = RAM+0x9000;

   GFX_BG0 = GFX+0x480000;
   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);

   GFX_SPR = GFX+0x000000;
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4800);

   // Coin fix

   WriteLong68k(&ROM[0x20C8],0x60000024);

   // Speed hack

   WriteLong68k(&ROM[0x0916],0x13FC0000); // move.b #$00,$AA0000
   WriteLong68k(&ROM[0x091A],0x00AA0000); // (Speed Hack)
   WriteLong68k(&ROM[0x091E],0x4E714E71);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x2C000, 0x40, 0x10, 0x8000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   if (is_current_game("ddragon3"))
     DD3MemoryMap();
   else DD3bMemoryMap();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_ddragon3(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 6);

   TechnosSound_Frame();		// Z80; YM2151; OKI ADPCM
}

static void execute_ddrago3b(void)
{
   int ta;

   // DSW mapper (weird split byte format!)

   ta = get_dsw(0);
   RAM[0xC001]&=0xCF;
   RAM[0xC001]|=(ta>>2)&0x30;
   RAM[0xC003]&=0xC0;
   RAM[0xC003]|=ta&0x3F;
   ta = get_dsw(1);
   RAM[0xC005]&=0xC0;
   RAM[0xC005]|=ta&0x3F;
   RAM[0xC007]&=0xFC;
   RAM[0xC007]|=(ta>>6)&0x03;
   RAM[0xC007]^=4;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 6);

   TechnosSound_Frame();		// Z80; YM2151; OKI ADPCM
}

static void draw_bg0() {
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   UINT8 *map;
   UINT8 *GFX_BG;

   // BG0
   // ---

   if((RAM[0x400C]&1)==0){		// Tile Bank
      GFX_BG = GFX_BG0;
   }
   else{
      GFX_BG = GFX_BG0 + (0x1000<<8);
   }

   MAKE_SCROLL_512x512_2_16(
       ReadWord(&RAM[0x4004]),
       ReadWord(&RAM[0x4006])+8
   );

   START_SCROLL_512x512_2_16(32,32,320,240);

      ta = ReadWord(&RAM_BG0[zz])|0x0FFF;

      MAP_PALETTE_MAPPED_NEW(
         ((ReadWord(&RAM_BG0[zz])>>12)&0x0F)|0x20,
         16,
         map
      );

      if ((RAM[0x01C000] & 0x20) && (GFX_BG0_SOLID[ta]!=1) && (ta!=0xdfff))
        Draw16x16_Trans_Mapped_Rot(&GFX_BG[(ReadWord(&RAM_BG0[zz])&0x0FFF)<<8], x, y, map);
      else
        Draw16x16_Mapped_Rot(&GFX_BG[(ReadWord(&RAM_BG0[zz])&0x0FFF)<<8], x, y, map);

   END_SCROLL_512x512_2_16();
}

static void draw_bg1() {
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   UINT8 *map;

   // BG1
   // ---


   MAKE_SCROLL_512x512_4_16(
       ReadWord(&RAM[0x4000]),
       ReadWord(&RAM[0x4002])+8
   );

   START_SCROLL_512x512_4_16(32,32,320,240);

      ta = ReadWord(&RAM_BG1[zz+2])&0x1FFF;
      if(GFX_BG0_SOLID[ta]!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG1[zz]&0x0F)|0x10,
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

static void draw_sprites() {
   int zz,x,y,ta,nn;
   UINT8 *map;

   // OBJECT
   // ------

   for(zz=0x0000;zz<0x1000;zz+=16){

     if((RAM_SPR[zz+2]&0x01)!=0){ // sprites enable

       x = ( (RAM_SPR[zz+10] | ((RAM_SPR[zz+2]&4)<<6) ));
       y = ((240+24) - (RAM_SPR[zz+0] | ((RAM_SPR[zz+2]&2)<<7) ))&0x1FF;
       if (x>0x17f) x=0-(0x200-x);
       x += 32;

         MAP_PALETTE_MAPPED_NEW(
            RAM_SPR[zz+8]&0x0F,
            16,
            map
         );

         ta = ((RAM_SPR[zz+4]) | (RAM_SPR[zz+6]<<8))&0x7FFF;

         nn = ((RAM_SPR[zz+2]>>5)&0x07)+1;

         switch(RAM_SPR[zz+2]&0x18){
         case 0x00:
	   do{

	     if((x>16)&&(y>16)&&(x<320+32)&&(y<240+32)){

               if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

		 if(GFX_SPR_SOLID[ta]==1)
		   Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);
		 else
		   Draw16x16_Mapped_Rot(      &GFX_SPR[ta<<8], x, y, map);

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

		 if(GFX_SPR_SOLID[ta]==1)
		   Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);
		 else
		   Draw16x16_Mapped_FlipY_Rot(      &GFX_SPR[ta<<8], x, y, map);

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

		 if(GFX_SPR_SOLID[ta]==1)
		   Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);
		 else
		   Draw16x16_Mapped_FlipX_Rot(      &GFX_SPR[ta<<8], x, y, map);

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

		  if(GFX_SPR_SOLID[ta]==1)
		    Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map);
		  else
                    Draw16x16_Mapped_FlipXY_Rot(      &GFX_SPR[ta<<8], x, y, map);

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

static void DrawDoubleD3(void)
{
   ClearPaletteMap();

   if (RAM[0x01C000] & 0x20) {
     draw_bg1();
     draw_bg0();
     draw_sprites();
   } else if (RAM[0x01C000] & 0x40) {
     draw_bg0();
     draw_bg1();
     draw_sprites();
   } else {
     draw_bg0();
     draw_sprites();
     draw_bg1();
   }
}

/*

BG0
---

- 512x512

Byte | Bit(s) | Use
-----+76543210+---------------
  0  |xxxx....| Colour Bank
  0  |....xxxx| Tile (high)
  1  |xxxxxxxx| Tile (low)


BG1
---

- 512x512

Byte | Bit(s) | Use
-----+76543210+---------------
  1  |x.......| Flip X Axis
  1  |.x......| Flip Y Axis
  1  |....xxxx| Colour Bank
  2  |...xxxxx| Tile (high)
  3  |xxxxxxxx| Tile (low)

OBJECT
------

- Only Odd Bytes used

Byte | Bit(s) | Use
-----+76543210+---------------
  1  |xxxxxxxx| Y (low)
  3  |xxx.....| Y Chain Size
  3  |...x....| Flip X Axis
  3  |....x...| Flip Y Axis
  3  |.....x..| X (high)
  3  |......x.| Y (high)
  3  |.......x| Sprite Enable
  5  |xxxxxxxx| Tile (low)
  7  |.xxxxxxx| Tile (high)
  9  |....xxxx| Colour Bank
 11  |xxxxxxxx| X (low)

*/
static struct VIDEO_INFO video_ddragon3 =
{
   DrawDoubleD3,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ddragon3[] =
{
   { "double_dragon_3", },
   { "doubled3", },
   { "ddragon3", },
   { NULL, },
};
#define DRV_DEF_SOUND technos_ym2151_m6295_sound
#include "game_def.h"

GME( ddragon3, "Double Dragon 3", TECHNOS, 1990, GAME_BEAT,
	.long_name_jpn = "ƒ_ƒuƒ‹ƒhƒ‰ƒSƒ“‚R",
	.board = "TA-0030",
);

CLNEI( ddrago3b, ddragon3, "Double Dragon 3 (bootleg)", TECHNOS, 1990, GAME_BEAT,
	.input = input_ddrago3b,
	.dsw = dsw_ddrago3b,
	.exec = execute_ddrago3b,
	.long_name_jpn = "ƒ_ƒuƒ‹ƒhƒ‰ƒSƒ“‚R",
	.board = "TA-0030",
);
