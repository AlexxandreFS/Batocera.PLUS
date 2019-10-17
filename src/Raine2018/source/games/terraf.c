#define DRV_DEF_SOUND nichi_ym3812_sound
/******************************************************************************/
/*                                                                            */
/*                      TERRA FORCE (C) 1987 NICHBUTSU                        */
/*                                                                            */
/*                        LEGION (C) 1987 NICHBUTSU                           */
/*                                                                            */
/*                     KODURE OOKAMI (C) 1987 NICHBUTSU                       */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "nichisnd.h"
#include "blit.h" // clear_game_screen
#include "profile.h" // fps


static struct ROM_INFO rom_terraf[] =
{
   { "terrafor.010", 0x00010000, 0x58b5f43b, 0, 0, 0, },
   { "terrafor.002", 0x00010000, 0x148aa0c5, 0, 0, 0, },
   { "terrafor.003", 0x00010000, 0xd74085a1, 0, 0, 0, },
   { "terrafor.004", 0x00010000, 0x2144d8e0, 0, 0, 0, },
   { "terrafor.005", 0x00010000, 0x744f5c9e, 0, 0, 0, },
   { "terrafor.006", 0x00010000, 0x25d23dfd, 0, 0, 0, },
   { "terrafor.007", 0x00010000, 0xb9b0fe27, 0, 0, 0, },
   { "terrafor.008", 0x00008000, 0xbc6f7cbc, 0, 0, 0, },
   { "terrafor.009", 0x00008000, 0xd1014280, 0, 0, 0, },
   { "terrafor.001", 0x00010000, 0xeb6b4138, 0, 0, 0, },
   { "terrafor.011", 0x00010000, 0x5320162a, 0, 0, 0, },
   { "terrafor.012", 0x00008000, 0x4f0e1d76, 0, 0, 0, },
   { "terrafor.013", 0x00010000, 0xa86951e0, 0, 0, 0, },
   { "terrafor.014", 0x00010000, 0x8e5f557f, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_legion[] =
{
   INP0( COIN1, 0x018001, 0x04 ),
   INP0( COIN2, 0x018001, 0x08 ),
   INP0( SERVICE, 0x018003, 0x01 ),
   INP0( TEST, 0x018003, 0x02 ),
   INP0( TILT, 0x018003, 0x04 ),

   INP0( P1_START, 0x018001, 0x01 ),
   INP0( P1_UP, 0x018000, 0x01 ),
   INP0( P1_DOWN, 0x018000, 0x02 ),
   INP0( P1_LEFT, 0x018000, 0x04 ),
   INP0( P1_RIGHT, 0x018000, 0x08 ),
   INP0( P1_B1, 0x018000, 0x10 ),
   INP0( P1_B2, 0x018000, 0x20 ),

   INP0( P2_START, 0x018001, 0x02 ),
   INP0( P2_UP, 0x018002, 0x01 ),
   INP0( P2_DOWN, 0x018002, 0x02 ),
   INP0( P2_LEFT, 0x018002, 0x04 ),
   INP0( P2_RIGHT, 0x018002, 0x08 ),
   INP0( P2_B1, 0x018002, 0x10 ),
   INP0( P2_B2, 0x018002, 0x20 ),

   END_INPUT
};

#define COINAGE_TERRAFORCE \
   { MSG_COIN1,               0x03, 0x04 },\
   { MSG_2COIN_1PLAY,         0x01, 0x00 },\
   { MSG_1COIN_1PLAY,         0x03, 0x00 },\
   { MSG_1COIN_2PLAY,         0x02, 0x00 },\
   { MSG_FREE_PLAY,           0x00, 0x00 },\
   { MSG_COIN2,               0x0C, 0x04 },\
   { MSG_2COIN_1PLAY,         0x04, 0x00 },\
   { MSG_1COIN_1PLAY,         0x0C, 0x00 },\
   { MSG_2COIN_3PLAY,         0x00, 0x00 },\
   { MSG_1COIN_2PLAY,         0x08, 0x00 },

static struct DSW_DATA dsw_data_terra_force_0[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "3",                     0x03},
   { "4",                     0x02},
   { "5",                     0x01},
   { "6",                     0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("20000, every 60000"),    0x0C, 0x00 },
   { _("20000, every 90000"),    0x04, 0x00 },
   { _("50000, every 60000"),    0x08, 0x00 },
   { _("50000, every 90000")},
   DSW_DEMO_SOUND( 0x00, 0x10),
   DSW_CABINET( 0x00, 0x20),
   { MSG_DIFFICULTY,          0xC0, 0x04 },
   { MSG_EASY,                0xC0},
   { MSG_NORMAL,              0x80},
   { MSG_HARD,                0x40},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_terra_force_1[] =
{
   COINAGE_TERRAFORCE
   DSW_UNUSED( 0x00, 0x10),
   DSW_SCREEN( 0x20, 0x00),
   { MSG_CONTINUE_PLAY,       0xC0, 0x04 },
   { MSG_NO,                  0xC0},
   { _("3 Times"),               0x80},
   { _("5 Times"),               0x40},
   { MSG_YES,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_terraf[] =
{
   { 0x018004, 0xAF, dsw_data_terra_force_0 },
   { 0x018006, 0x3F, dsw_data_terra_force_1 },
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_legion[] =
{
   { "lg1.bin"   , 0x00010000, 0xc4aeb724, 0, 0, 0, },		// main 68000
   { "lg3.bin"   , 0x00010000, 0x777e4935, 0, 0, 0, },
   { "legion.1b" , 0x00010000, 0xc306660a, 0, 0, 0, },
   { "legion.1d" , 0x00010000, 0xc2e45e1e, 0, 0, 0, },
   { "legion.1h" , 0x00004000, 0x2ca4f7f0, 0, 0, 0, },		// sound z80
   { "lg8.bin"   , 0x00008000, 0xe0596570, 0, 0, 0, },		// text
   { "legion.1e" , 0x00010000, 0xa9d70faf, 0, 0, 0, },		// foreground
   { "legion.1i" , 0x00008000, 0x79f4a827, 0, 0, 0, },
   { "legion.1f" , 0x00008000, 0xf018313b, 0, 0, 0, },
   { "legion.1l" , 0x00010000, 0x29b8adaa, 0, 0, 0, },		// background
   { "legion.1k" , 0x00010000, 0xff5a0db9, 0, 0, 0, },		// sprites
   { "legion.1j" , 0x00010000, 0xbae220c8, 0, 0, 0, },
   {         NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_legion_0[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "3",                     0x03},
   { "4",                     0x02},
   { "5",                     0x01},
   { "6",                     0x00},
   { MSG_EXTRA_LIFE,          0x04, 0x02 },
   { _("30000, every 100000"),   0x04, 0x00 },
   { _("50000 only"),            0x00},
   DSW_DEMO_SOUND( 0x00, 0x08),
   DSW_SCREEN( 0x10, 0x00),
   { MSG_UNKNOWN,             0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   DSW_UNUSED( 0x00, 0x40),
   { _("Invulnerability"),       0x80, 0x02 },
   { MSG_NO,                  0x80},
   { MSG_YES,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_legion_1[] =
{
   COINAGE_TERRAFORCE
   { _("Coin Slots"),            0x10, 0x02 },
   { _("Common"),                0x10},
   { _("Individual"),            0x00},
   { MSG_DIFFICULTY,          0x20, 0x02 },
   { MSG_NORMAL,              0x20},
   { MSG_HARD,                0x00},
   { _("P1 Invulnerability"),    0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("P2 Invulnerability"),    0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_legion[] =
{
   { 0x018004, 0xF7, dsw_data_legion_0 },
   { 0x018006, 0xFF, dsw_data_legion_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_kodure[] =
{
   { "kodure8.6e"  , 0x00010000, 0x6bbfb1e6, 0, 0, 0, },	// main 68000
   { "kodure3.6h"  , 0x00010000, 0xf9178ec8, 0, 0, 0, },
   { "kodure7.5e"  , 0x00010000, 0xa7ee09bb, 0, 0, 0, },
   { "kodure2.5h"  , 0x00010000, 0x236d820f, 0, 0, 0, },
   { "kodure6.3e"  , 0x00010000, 0x9120e728, 0, 0, 0, },
   { "kodure1.3h"  , 0x00010000, 0x345fe7a5, 0, 0, 0, },
   { "kodure11.17k", 0x00010000, 0xdba51e2d, 0, 0, 0, },	// sound z80
   { "kodure9.11e" , 0x00008000, 0xe041356e, 0, 0, 0, },	// text
   { "kodure5.15h" , 0x00020000, 0x0b510258, 0, 0, 0, },	// foreground
   { "kodure4.14h" , 0x00010000, 0xfb8e13e6, 0, 0, 0, },
   { "kodure14.8a" , 0x00010000, 0x94a9c3d0, 0, 0, 0, },	// background
   { "kodure12.8d" , 0x00020000, 0x15f4021d, 0, 0, 0, },	// sprites
   { "kodure13.9d" , 0x00020000, 0xb3b6c753, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_kodure_0[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "3",                     0x03},
   { "4",                     0x02},
   { "5",                     0x01},
   { "6",                     0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("50000, every 60000"),    0x08, 0x00 },
   { _("50000, every 90000")},
   { _("Every 60000"),           0x0C},
   { _("Every 90000"),           0x04},
   DSW_DEMO_SOUND( 0x00, 0x10),
   DSW_CABINET( 0x00, 0x20),
   { MSG_DIFFICULTY,          0x40, 0x02 },
   { MSG_NORMAL,              0x40},
   { MSG_HARD,                0x00},
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_kodure_1[] =
{
   { MSG_COIN1,               0x03, 0x04 },
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_1COIN_2PLAY,         0x02},
   { MSG_FREE_PLAY,           0x00},
   { MSG_COIN2,               0x0C, 0x04 },
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_2COIN_3PLAY,         0x04},
   { MSG_1COIN_3PLAY,         0x0C},
   { MSG_1COIN_6PLAY,         0x08},
   DSW_UNUSED( 0x00, 0x10),
   DSW_SCREEN( 0x20, 0x00),
   { MSG_CONTINUE_PLAY, 0x40, 2 },
   { MSG_YES, 0x40 },
   { MSG_NO, 0x00 },
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_kodure[] =
{
   { 0x018004, 0xEF, dsw_data_kodure_0 },
   { 0x018006, 0xFF, dsw_data_kodure_1 },
   { 0,        0,    NULL,      },
};


static UINT8 *GFX_BG0;
static UINT8 *GFX_BG1;
static UINT8 *GFX_SPR;
static UINT8 *GFX_FG0;

static UINT8 *MSK_BG1;
static UINT8 *MSK_SPR;
static UINT8 *MSK_FG0;

static UINT8 *RAM_SCR;

int romset, x_res, x_off, fg_off;
UINT16 VReg;

static void terraf_clear_intro(int ram_off, int st1, int st2)
{
  int i,j;

  if (st1 != -1)
    for (j = st1; j <= st1+0x300; j+=0x40)
      for (i = 0; i < 0x20; i++){
        RAM[ram_off+i+j] = 0;
        RAM[ram_off+0x0800+i+j] = 0;
      }
  if (st2 != -1)
    for (j = st2; j <= st2+0x300; j+=0x20)
      for (i = 0; i < 0x10; i++){
        RAM[ram_off+0x1000+i+j] = 0;
        RAM[ram_off+0x1800+i+j] = 0;
      }
}

static void terraf_vreg(UINT32 offset, UINT16 data)
{
  VReg = data;

  // little hack for game intro...
  if ((RAM[0x8420]==0x80) && (RAM[0x8C20]==0xD9))	// parte 1
    terraf_clear_intro(0x8400, 0, 0x10);
  if ((RAM[0x80E0]==0x30) && (RAM[0x88E0]==0xBB))	// parte 2
    terraf_clear_intro(0x8400, 0x20, 0);
  if ((RAM[0x80C0]==0xF3) && (RAM[0x88C0]==0xC9))	// parte 4
    terraf_clear_intro(0x80C0, 0x20, 0);
  if (VReg == 0x8E10)					// parte 3
    terraf_clear_intro(0x80C0,-1, 0x10);
}

static void load_terraf(void)
{
   int ta,tb;

   romset = 0;
   x_res = 320; x_off = 0; fg_off = 0x38;

   RAMSize=0x20100+0x10000;

   if(!(ROM=AllocateMem(0x50000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0xD0000))) return;

   if(!load_rom("terrafor.014",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("terrafor.011",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("terrafor.013",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("terrafor.010",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("terrafor.012",&RAM[0x0000],0x8000)) return;
   for(ta=0;ta<0x8000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("terrafor.009",&RAM[0x0000],0x8000)) return;
   for(ta=0;ta<0x8000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x20100;
   if(!load_rom("terrafor.001", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   AddNichibutsuYM3526(0x0085, 0x007A);

   AddNichiSample(0x0173, 0x0175, 1);
   AddNichiSample(0x0176, 0x0178, 1);

   AddNichiSample(0x5040, 0x53F0, 1);
   AddNichiSample(0x53F1, 0x5511, 1);
   AddNichiSample(0x5512, 0x5AD2, 1);
   AddNichiSample(0x5AD3, 0x70D3, 3);

   AddNichiSample(0x8040, 0x88DB, 2);
   AddNichiSample(0x88DC, 0x9687, 2);
   AddNichiSample(0x9688, 0xA9C4, 3);
   AddNichiSample(0xA9C5, 0xAFF5, 3);
   AddNichiSample(0xAFF6, 0xCA26, 3);
   AddNichiSample(0xCA27, 0xDC27, 3);
   AddNichiSample(0xDC28, 0xDD48, 1);
   AddNichiSample(0xDD49, 0xE3B6, 2);
   AddNichiSample(0xE3B7, 0xF0B7, 1);

   /*-----------------------*/

   GFX_BG0 = GFX+0x000000;
   GFX_BG1 = GFX+0x040000;
   GFX_SPR = GFX+0x080000;
   GFX_FG0 = GFX+0x0C0000;

   tb=0;
   if(!load_rom("terrafor.004", RAM+0x00000, 0x10000)) return;	// GFX BG0
   if(!load_rom("terrafor.005", RAM+0x10000, 0x10000)) return;
   for(ta=0;ta<0x20000;ta++,tb+=2){
      GFX_BG0[tb+0]=(RAM[ta]&15)^15;
      GFX_BG0[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("terrafor.006", RAM+0x00000, 0x10000)) return;	// GFX BG1
   if(!load_rom("terrafor.007", RAM+0x10000, 0x10000)) return;
   for(ta=0;ta<0x20000;ta++,tb+=2){
      GFX_BG1[tb+0]=(RAM[ta]&15)^15;
      GFX_BG1[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("terrafor.003", RAM+0x00000, 0x10000)) return;	// GFX SPR
   if(!load_rom("terrafor.002", RAM+0x10000, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++,tb+=4){
      GFX_SPR[tb+0]=(RAM[ta+0x00000]&15)^15;
      GFX_SPR[tb+1]=(RAM[ta+0x00000]>>4)^15;
      GFX_SPR[tb+2]=(RAM[ta+0x10000]&15)^15;
      GFX_SPR[tb+3]=(RAM[ta+0x10000]>>4)^15;
   }

   tb=0;
   if(!load_rom("terrafor.008", RAM+0x00000, 0x08000)) return;	// GFX FG0
   for(ta=0;ta<0x8000;ta++,tb+=2){
      GFX_FG0[tb+0]=(RAM[ta]&15)^15;
      GFX_FG0[tb+1]=(RAM[ta]>>4)^15;
   }

   MSK_BG1 = make_solid_mask_16x16(GFX_BG1, 0x0400);
   MSK_SPR = make_solid_mask_16x16(GFX_SPR, 0x0400);
   MSK_FG0 = make_solid_mask_8x8  (GFX_FG0, 0x0400);

   RAM_SCR = RAM+0x1C000;

   memset(RAM+0x00000,0x00,0x20100);
   memset(RAM+0x18000,0xFF,0x00100);

   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x00132],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x00136],0x00AA0000);	//	(Speed Hack)

   // Change Sound Comm Address (for speed)
   // -------------------------------------

   WriteLong68k(&ROM[0x0784A],0x00BB0000);

   // Scroll Write Fix
   // ----------------

   WriteLong68k(&ROM[0x1F724],0x0007D000);


   set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
   InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x1000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x50000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x04FFFF, ROM+0x000000-0x000000);
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x04FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x060000, 0x07FFFF, NULL, RAM+0x000000);			// ALL RAM
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x04FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x060000, 0x07FFFF, NULL, RAM+0x000000);			// ALL RAM
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x060000, 0x07FFFF, NULL, RAM+0x000000);		// ALL RAM
   AddWriteByte(0x0C0000, 0x0C000F, NULL, RAM+0x020000);		// ???
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x07C000, 0x07C001, terraf_vreg, NULL);			// Video registers
   AddWriteWord(0x060000, 0x07FFFF, NULL, RAM+0x000000);		// ALL RAM
   AddWriteWord(0xBB0000, 0xBB0001, NichiSoundCommWrite68k, NULL);	// SOUND COMM
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void legion_vreg(UINT32 offset, UINT16 data)
{
  VReg = data;

  if (!(VReg & 0x0080)){			// Clear Text Layer
    int i;
    for (i = 0; i < 0xF80; i++)
      RAM[0x8000+128+i] = 0;
  }
}

static void load_legion(void)
{
   int ta,tb;

   romset = 2;
   x_res = 288; x_off = 16; fg_off = 0x700;

   RAMSize=0x20000+0x10000;

   if(!(ROM=AllocateMem(0x40000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0xB0000))) return;

   if(!load_rom("lg3.bin",&RAM[0x0000],0x10000)) return;	// 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("lg1.bin",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("legion.1d",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("legion.1b",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x20000;
   if(!load_rom("legion.1h", Z80ROM, 0x04000)) return;		// Z80 SOUND ROM

   AddNichibutsuYM3526(0x00, 0x00);

   /*-----------------------*/

   GFX_BG0 = GFX+0x000000;
   GFX_BG1 = GFX+0x020000;
   GFX_SPR = GFX+0x060000;
   GFX_FG0 = GFX+0x0A0000;

   tb=0;
   if(!load_rom("legion.1l", RAM+0x00000, 0x10000)) return;	// GFX BG0
   for(ta=0;ta<0x10000;ta++,tb+=2){
      GFX_BG0[tb+0]=(RAM[ta]&15)^15;
      GFX_BG0[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("legion.1e", RAM+0x00000, 0x10000)) return;	// GFX BG1
   if(!load_rom("legion.1i", RAM+0x10000, 0x08000)) return;
   if(!load_rom("legion.1f", RAM+0x18000, 0x08000)) return;
   for(ta=0;ta<0x20000;ta++,tb+=2){
      GFX_BG1[tb+0]=(RAM[ta]&15)^15;
      GFX_BG1[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("legion.1k", RAM+0x00000, 0x10000)) return;	// GFX SPR
   if(!load_rom("legion.1j", RAM+0x10000, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++,tb+=4){
      GFX_SPR[tb+0]=(RAM[ta+0x00000]&15)^15;
      GFX_SPR[tb+1]=(RAM[ta+0x00000]>>4)^15;
      GFX_SPR[tb+2]=(RAM[ta+0x10000]&15)^15;
      GFX_SPR[tb+3]=(RAM[ta+0x10000]>>4)^15;
   }

   tb=0;
   if(!load_rom("lg8.bin", RAM+0x00000, 0x08000)) return;	// GFX FG0
   for(ta=0;ta<0x8000;ta++,tb+=2){
      GFX_FG0[tb+0]=(RAM[ta]&15)^15;
      GFX_FG0[tb+1]=(RAM[ta]>>4)^15;
   }

   Rotate16x16(GFX_BG0,0x200);
   Flip16x16_X(GFX_BG0,0x200);
   Rotate8x8(GFX_FG0+0x4000,0x300);
   Flip8x8_X(GFX_FG0+0x4000,0x300);

   MSK_BG1 = make_solid_mask_16x16(GFX_BG1, 0x0400);
   MSK_SPR = make_solid_mask_16x16(GFX_SPR, 0x0400);
   MSK_FG0 = make_solid_mask_8x8  (GFX_FG0, 0x0100);

   RAM_SCR = RAM+0x1C000;

   memset(RAM+0x00000,0x00,0x20000);
   memset(RAM+0x18000,0xFF,0x00100);

   // 68000 Speed Hack
   // ----------------

   // ...

   // Enable Invulnerability dipswitch (see Stephh's notes in mame)

   WriteLong68k(&ROM[0x0D9B2],0);

   // 68000 Checksum Fix
   // ------------------

   WriteLong68k(&ROM[0x00486],0x4E714E71);	// 	nop

   set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
   InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x1000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x10000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x060000, 0x07C005, NULL, RAM+0x000000);			// ALL RAM
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x060000, 0x07C005, NULL, RAM+0x000000);			// ALL RAM
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x060000, 0x07C005, NULL, RAM+0x000000);		// ALL RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x07C000, 0x07C001, legion_vreg, NULL);			// Video registers
   AddWriteWord(0x060000, 0x07C005, NULL, RAM+0x000000);		// ALL RAM
   AddWriteWord(0x07C00A, 0x07C00B, NichiSoundCommWrite68k, NULL);	// SOUND COMM
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_kodure(void)
{
   int ta,tb;

   romset = 1;
   x_res = 320; x_off = 0; fg_off = 0x38;

   RAMSize=0x40100+0x10000;

   if(!(ROM=AllocateMem(0x60000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x110000))) return;

   if(!load_rom("kodure8.6e",&RAM[0x0000],0x10000)) return;	// 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("kodure3.6h",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("kodure7.5e",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("kodure2.5h",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("kodure6.3e",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("kodure1.3h",&RAM[0x0000],0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40100;
   if(!load_rom("kodure11.17k", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   AddNichibutsuYM3526(0x008c, 0x0081);

   /*-----------------------*/

   GFX_BG0 = GFX+0x000000;
   GFX_BG1 = GFX+0x020000;
   GFX_SPR = GFX+0x080000;
   GFX_FG0 = GFX+0x100000;

   tb=0;
   if(!load_rom("kodure14.8a", RAM+0x00000, 0x10000)) return;	// GFX BG0
   for(ta=0;ta<0x10000;ta++,tb+=2){
      GFX_BG0[tb+0]=(RAM[ta]&15)^15;
      GFX_BG0[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("kodure5.15h", RAM+0x00000, 0x20000)) return;	// GFX BG1
   if(!load_rom("kodure4.14h", RAM+0x20000, 0x10000)) return;
   for(ta=0;ta<0x30000;ta++,tb+=2){
      GFX_BG1[tb+0]=(RAM[ta]&15)^15;
      GFX_BG1[tb+1]=(RAM[ta]>>4)^15;
   }

   tb=0;
   if(!load_rom("kodure12.8d", RAM+0x00000, 0x20000)) return;	// GFX SPR
   if(!load_rom("kodure13.9d", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++,tb+=4){
      GFX_SPR[tb+0]=(RAM[ta+0x00000]&15)^15;
      GFX_SPR[tb+1]=(RAM[ta+0x00000]>>4)^15;
      GFX_SPR[tb+2]=(RAM[ta+0x20000]&15)^15;
      GFX_SPR[tb+3]=(RAM[ta+0x20000]>>4)^15;
   }

   tb=0;
   if(!load_rom("kodure9.11e", RAM+0x00000, 0x08000)) return;	// GFX FG0
   for(ta=0;ta<0x8000;ta++,tb+=2){
      GFX_FG0[tb+0]=(RAM[ta]&15)^15;
      GFX_FG0[tb+1]=(RAM[ta]>>4)^15;
   }

   MSK_BG1 = make_solid_mask_16x16(GFX_BG1, 0x0600);
   MSK_SPR = make_solid_mask_16x16(GFX_SPR, 0x0800);
   MSK_FG0 = make_solid_mask_8x8  (GFX_FG0, 0x0100);

   RAM_SCR = RAM+0x1C000;

   memset(RAM+0x00000,0x00,0x40100);
   memset(RAM+0x18000,0xFF,0x00100);

   // 68000 Speed Hack
   // ----------------

   // ...
   WriteWord68k(&ROM[0x4ab6],0x4239); // clr.b $aa0000
   WriteWord68k(&ROM[0x4ab8],0xaa);
   WriteWord68k(&ROM[0x4aba],0);

   WriteLong68k(&ROM[0x4fb2], 0x303800fe); // move EXT_0002.W,D0
   WriteWord68k(&ROM[0x4fb6],0x6004); // bra.s +4 (disable rom check)

   set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
   InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x1000);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x60000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x060000, 0x07C005, NULL, RAM+0x000000);			// ALL RAM
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x060000, 0x07C005, NULL, RAM+0x000000);			// ALL RAM
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x060000, 0x07C005, NULL, RAM+0x000000);		// ALL RAM
   AddWriteByte(0x0C0000, 0x0C000F, NULL, RAM+0x040000);		// ???
   AddWriteByte(0xFFD000, 0xFFD00F, NULL, RAM+0x040010);		// ???
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x07C000, 0x07C001, legion_vreg, NULL);			// Video registers
   AddWriteWord(0x060000, 0x07C005, NULL, RAM+0x000000);		// ALL RAM
   AddWriteWord(0x07C00A, 0x07C00B, NichiSoundCommWrite68k, NULL);	// SOUND COMM
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_terraf(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)

   cpu_interrupt(CPU_68K_0, 1);

   Nichibutsu3526_Frame();		// Z80 and YM3526
}

static void execute_kodure(void)
{
  // Kodure needs its own cpu frame for the speed hack
  // If the hack happens in an interrupt then the pc must not move (infinite loop).

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   if (s68000context.pc == 0x4abc)
     s68000context.pc = 0x4ab6;

   cpu_interrupt(CPU_68K_0, 1);

   Nichibutsu3526_Frame();		// Z80 and YM3526
}

static void execute_legion(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(8,60));	// M68000 8MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);

   Nichibutsu3526_Frame();		// Z80 and YM3526
}

static void DrawSprites(int priority)
{
   UINT8 *map;
   int x,y,ta,zz,zzz;

   if(((zzz=VReg)&0x0200)!=0){

   for(zz=0;zz<0x600;zz+=8){

      if(((ReadWord(&RAM[zz])&0x3000)>>12)==priority){

      ta=ReadWord(&RAM[zz+2])&0x7FF;
      if(MSK_SPR[ta]!=0){				// No pixels; skip

      if (romset==2)	// Legion
        y=((x_res+32-64) - ReadWord(&RAM[zz+0]))&0x1FF;
      else y=((x_res+32+32) - ReadWord(&RAM[zz+0]))&0x1FF;

      x=(ReadWord(&RAM[zz+6]) - (32+32+x_off))&0x1FF;

      if((x>16)&&(y>16)&&(x<x_res+32)&&(y<224+32)){

         MAP_PALETTE_MAPPED_NEW(
            (RAM[zz+5]&0x1F)|0x20,
            16,
            map
         );

         if(MSK_SPR[ta]==1){				// Some pixels; trans
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM[zz+3]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
            case 0x10: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x20: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
            }
         }


      }
      }
      }
   }
   }
}

static void DrawTerraF(void)
{
   UINT8 *map;
   int x,y,ta,zz,zzz,zzzz,x16,y16;
   int xmin,xmax,ymin,ymax;

   ClearPaletteMap();

   // BG0
   // ---

   clear_game_screen(0);			// Game has no solid BG0
   if(((zzz=VReg)&0x0800)!=0){

   zzz=15+(ReadWord(&RAM[0x1C004]));
   zzzz=((zzz&0x1F0)>>4)<<1;			// X Offset (16-511)
   x16=15-(zzz&15);				// X Offset (0-15)
   zzz=95+(ReadWord(&RAM[0x1C002]));
   zzzz+=((zzz&0x3F0)>>4)<<6;			// Y Offset (16-511)
   y16=15-(zzz&15)-x_off;			// Y Offset (0-15)

   zzzz&=0xFFF;

   for(x=(16+y16);x<(x_res+32);x+=16){
   zz=zzzz;
   for(y=(16+x16);y<(224+32);y+=16){

      ta=(ReadWord(&RAM[0x14000+zz])&0x3FF)<<8;
      if (ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x14001+zz]>>3)|0x60,
         16,
         map
      );

      Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta],x,y,map);
      }

   zz+=2;
   if((zz&0x3F)==0){zz-=0x40;}
   }
   zzzz+=0x40;
   zzzz&=0xFFF;
   }

   }

   DrawSprites(2);

   // BG1
   // ---

   if(((zzz=VReg)&0x0400)!=0){

   if (romset==0)	// Terra Force
     zzz=15+((RAM[0x1C007])|(((RAM[0x1D001]>>0)&3)<<8));
   else	zzz=15+(RAM[0x8000+11*2] | (RAM[0x8000+12*2]<<8));
   zzzz=((zzz&0x1F0)>>4)<<1;			// X Offset (16-511)
   x16=15-(zzz&15);				// X Offset (0-15)

   if (romset==0)	// Terra Force
     zzz=95+((RAM[0x1C009])|(((RAM[0x1D001]>>4)&3)<<8));
   else zzz=95+(RAM[0x8000+13*2] | (RAM[0x8000+14*2]<<8));
   zzzz+=((zzz&0x3F0)>>4)<<6;			// Y Offset (16-511)
   y16=15-(zzz&15)-x_off;			// Y Offset (0-15)

   zzzz&=0xFFF;

   for(x=(16+y16);x<(x_res+32);x+=16){
   zz=zzzz;
   for(y=(16+x16);y<(224+32);y+=16){

      ta=ReadWord(&RAM[0x10000+zz])&0x7FF;
      if(MSK_BG1[ta]!=0){				// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x10001+zz]>>3)|0x40,
         16,
         map
      );

      if(MSK_BG1[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG1[ta<<8],x,y,map);
      }
      else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG1[ta<<8],x,y,map);
      }

      }

   zz+=2;
   if((zz&0x3F)==0){zz-=0x40;}
   }
   zzzz+=0x40;
   zzzz&=0xFFF;
   }

   }

   DrawSprites(1);

   // FG0
   // ---

   if(((zzz=VReg)&0x0100)!=0){

   zz=64*2;
   for(y=224+24+x_off;y>=32;y-=8){
   for(x=32+32;x<256+32+32;x+=8){

   ta=(((RAM[0x8800+zz]&3)<<14)|((RAM[0x8000+zz])<<6));
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x8800+zz]>>4),
         16,
         map
      );

      if (romset==2){	// Legion
        if (y==152 && ta>=0xD000)	// hack - 2 players glitch
          ta=0;
        Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta],x-48,y+16,map);
      }
      else Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta],x,y,map);
   }

   zz+=2;
   }
   }

   if (romset==2){
     zz=0; ymax=24; ymin=0;
     xmin=32+32; xmax=256+32+32;
   }
   else{
     zz=64*2; ymax=224+24; ymin=32;
     xmin=0+32; xmax=32+32;
   }
   for(y=ymax;y>=ymin;y-=8){
   for(x=xmin;x<xmax;x+=8){

   ta=(((RAM[0x9800+zz+fg_off]&3)<<14)|((RAM[0x9000+zz+fg_off])<<6));
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x9800+zz+fg_off]>>4),
         16,
         map
      );

      if (romset==2)	// Legion
        Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta],x-48,y+256+32+16,map);
      else Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta],x,y,map);
   }

   ta=(((RAM[0x9800+zz]&3)<<14)|((RAM[0x9000+zz])<<6));
   if(ta!=0){

      MAP_PALETTE_MAPPED_NEW(
         (RAM[0x9800+zz]>>4),
         16,
         map
      );

      if (romset==2)	// Legion
        Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta],x-48,y+16,map);
      else Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta],x+256+32,y,map);
   }

   zz+=2;
   }
   if (romset!=2)
     zz+=56;
   }

   }

   DrawSprites(0);
}



/*

-----+--------+--------------------
Byte | Bit(s) | Info
-----+76543210+--------------------
  0  |....xxxx| Sprite Y (high)
  1  |xxxxxxxx| Sprite Y (low)
  2  |...x....| Sprite Flip X Axis
  2  |..x.....| Sprite Flip Y Axis
  2  |......xx| Sprite Number (high)
  3  |xxxxxxxx| Sprite Number (low)
  4  |...xxxxx| Colour Bank
  6  |xxxxxxxx| Sprite X (high)
  7  |xxxxxxxx| Sprite X (low)
-----+--------+--------------------

*/
static struct VIDEO_INFO video_legion =
{
   DrawTerraF,
   288,
   224,
   32,
   VIDEO_ROTATE_270 | VIDEO_ROTATABLE,
};
static struct VIDEO_INFO video_terraf =
{
   DrawTerraF,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
   NULL,
   57
};
static struct DIR_INFO dir_kodure[] =
{
   { "kodure", },
   { NULL, },
};
GAME( kodure, "Kodure Ookami (Japan)", NICHIBUTSU, 1987, GAME_BEAT,
	.input = input_legion,
	.dsw = dsw_kodure,
	.video = &video_terraf,
	.exec = execute_kodure,
);
GMEI( legion, "Legion", NICHIBUTSU, 1987, GAME_SHOOT|GAME_PARTIALLY_WORKING,
);
static struct DIR_INFO dir_terraf[] =
{
   { "terra_force", },
   { "terraf", },
   { NULL, },
};
GAME( terraf, "Terra Force", NICHIBUTSU, 1987, GAME_SHOOT,
	.input = input_legion,
	.dsw = dsw_terraf,
	.video = &video_terraf,
	.exec = execute_terraf,
	.long_name_jpn = "テラフォース",
);

