/******************************************************************************/
/*                                                                            */
/*                       BIOMECHANICAL TOY (C) 1995 ZEUS                      */
/*                                                                            */
/*                        MANIAC SQUARE (C) 1996 GAELCO                       */
/*                                                                            */
/******************************************************************************/
/* The maniac square story :
 *
 * It's a test driver due to the fact that the game was only a
 * prototype, and the person who dumped/released it would be obvious
 * to the powers-that-be, and would be subject to backlash.
 *
 * This was confirmed from mame's team by this email :
 *
 * From: "Manuel Abadia" <manu@mame.net>
 * To: <neohaze@haywood2.force9.co.uk>
 * Sent: Sunday, September 24, 2000 9:08 AM
 * Subject: New Raine - IMPORTANT -
 *
 *
 * > Hello Haze.
 * >
 * > I emulated biomechanical toy and maniac square for MAME. Maniac
 * > Square was disabled because of a VERY IMPORTANT reason.
 * > Please DO NOT ENABLE THAT GAME in your compiles.
 *
 * So well... Maniac square SHOULD stay as it is : GAME_PRIVATE, which
 * means it can be enabled only if PRIVATE is defined, and PRIVATE
 * should NEVER be defined in any public release.
 */

// Maniac Square became public again in January 2003.

#include "gameinc.h"
#include "sasound.h"
#include "adpcm.h"
#include "taitosnd.h"
#include "blit.h" // clear_game_screen


static struct ROM_INFO rom_biomtoy[] =
{
   {          "d18",   0x080000, 0x4569ce64, 0, 0, 0, },
   {          "d16",   0x080000, 0x739449bd, 0, 0, 0, },
   {           "h6",   0x080000, 0x9416a729, 0, 0, 0, },
   {           "j6",   0x080000, 0xe923728b, 0, 0, 0, },
   {           "h7",   0x080000, 0x9c984d7b, 0, 0, 0, },
   {           "j7",   0x080000, 0x0e18fac2, 0, 0, 0, },
   {           "h9",   0x080000, 0x8c1f6718, 0, 0, 0, },
   {           "j9",   0x080000, 0x1c93f050, 0, 0, 0, },
   {          "h10",   0x080000, 0xaca1702b, 0, 0, 0, },
   {          "j10",   0x080000, 0x8e3e96cc, 0, 0, 0, },
   {           "c1",   0x080000, 0x0f02de7e, 0, 0, 0, },
   {           "c3",   0x080000, 0x914e4bbc, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_maniacsq[] =
{
   INP0( COIN1, 0x030004, 0x40 ),
   INP0( COIN2, 0x030004, 0x80 ),

   INP0( P1_START, 0x030006, 0x40 ),
   INP0( P1_UP, 0x030004, 0x01 ),
   INP0( P1_DOWN, 0x030004, 0x02 ),
   INP0( P1_LEFT, 0x030004, 0x08 ),
   INP0( P1_RIGHT, 0x030004, 0x04 ),
   INP0( P1_B1, 0x030004, 0x20 ),
   INP0( P1_B2, 0x030004, 0x10 ),

   INP0( P2_START, 0x030006, 0x80 ),
   INP0( P2_UP, 0x030006, 0x01 ),
   INP0( P2_DOWN, 0x030006, 0x02 ),
   INP0( P2_LEFT, 0x030006, 0x08 ),
   INP0( P2_RIGHT, 0x030006, 0x04 ),
   INP0( P2_B1, 0x030006, 0x20 ),
   INP0( P2_B2, 0x030006, 0x10 ),

   END_INPUT
};

/* Dipswitch 2 */
static struct DSW_DATA dsw_data_BiomToy_0[] =
{
   DSW_SERVICE( 0x00, 0x01),
   DSW_UNUSED( 0x00, 0x02),
   DSW_UNUSED( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_LIVES,               0x30, 0x04 },
   { "1",                     0x20},
   { "2",                     0x10},
   { "3",                     0x30},
   { "4",                     0x00},
   { MSG_DIFFICULTY,          0xC0, 0x04 },
   { MSG_EASY,                0x40},
   { MSG_NORMAL,              0xC0},
   { MSG_HARD,                0x80},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};

/* Dipswitch 1 */
static struct DSW_DATA dsw_data_BiomToy_1[] =
{
   { MSG_COIN2,               0x0F, 0x0C },
   { MSG_4COIN_1PLAY,         0x0E},
   { MSG_3COIN_1PLAY,         0x01},
   { MSG_2COIN_1PLAY,         0x09},
   { MSG_3COIN_2PLAY,         0x0A},
   { MSG_1COIN_1PLAY,         0x0F},
   { MSG_2COIN_3PLAY,         0x06},
   { MSG_1COIN_2PLAY,         0x07},
   { MSG_1COIN_3PLAY,         0x0B},
   { MSG_1COIN_4PLAY,         0x03},
   { MSG_1COIN_5PLAY,         0x0D},
   { MSG_1COIN_6PLAY,         0x05},
   { MSG_FREE_PLAY,           0x00},
   { MSG_COIN1,               0xF0, 0x0C },
   { MSG_4COIN_1PLAY,         0xE0},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x90},
   { MSG_3COIN_2PLAY,         0xA0},
   { MSG_1COIN_1PLAY,         0xF0},
   { MSG_2COIN_3PLAY,         0x60},
   { MSG_1COIN_2PLAY,         0x70},
   { MSG_1COIN_3PLAY,         0xB0},
   { MSG_1COIN_4PLAY,         0x30},
   { MSG_1COIN_5PLAY,         0xD0},
   { MSG_1COIN_6PLAY,         0x50},
   { MSG_FREE_PLAY,           0x00},
   { NULL,                    0,   },
};


static struct DSW_INFO dsw_biomtoy[] =
{
   { 0x030002, 0xFF, dsw_data_BiomToy_1 },
   { 0x030000, 0xFF, dsw_data_BiomToy_0 },
   { 0,        0,    NULL,      },
};

static struct OKIM6295interface m6295_interface =
{
	1,                  /* 1 chip */
	{ 8000 },			/* 8000 KHz? */
	{ 0 },  /* memory region (not yet !) */
	{ 255 }				/* volume */
};

static struct SOUND_INFO sound_maniacsq[] =
{
   { SOUND_M6295,   &m6295_interface,     },
   { 0,             NULL,                 },
};

static UINT8 *GFX_CHAR16;
static UINT8 *GFX_CHAR16_SOLID;

static UINT8 *GFX_TILE16;
static UINT8 *GFX_TILE16_SOLID;

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SPR;
static UINT8 *ADPCM;





static struct ROM_INFO rom_maniacsq[] =
{
   {          "d18",    0x20000, 0x740ecab2, 0, 0, 0, },
   {          "d16",    0x20000, 0xc6c42729, 0, 0, 0, },
   {           "f3",    0x40000, 0xe7f6582b, 0, 0, 0, },
   {           "f2",    0x40000, 0xca43a5ae, 0, 0, 0, },
   {           "f1",    0x40000, 0xfca112e8, 0, 0, 0, },
   {           "f0",    0x40000, 0x6e829ee8, 0, 0, 0, },
   {           "c1",    0x80000, 0x2557f2d6, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


/* Dipswitch 2 */
static struct DSW_DATA dsw_data_Maniacsq_0[] =
{
   DSW_SERVICE( 0x00, 0x01),
   { MSG_UNKNOWN,	      0x02, 0x02 },
   { MSG_OFF,		      0x02},
   { MSG_ON,		      0x00},
   DSW_DEMO_SOUND( 0x04, 0x00),
   { _("Sound type"),            0x08, 0x02 },
   { _("Mono"),                  0x08},
   { _("Stereo"),                0x00},
   { MSG_UNKNOWN,	      0x10, 0x02 },
   { MSG_OFF,		      0x10},
   { MSG_ON,		      0x00},
   { MSG_UNKNOWN,	      0x20, 0x02 },
   { MSG_OFF,		      0x20},
   { MSG_ON,		      0x00},
   { MSG_DIFFICULTY,          0xC0, 0x04 },
   { MSG_EASY,                0x40},
   { MSG_NORMAL,              0xC0},
   { MSG_HARD,                0x80},
   { MSG_HARDEST,             0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_maniacsq[] =
{
   { 0x030002, 0xFF, dsw_data_BiomToy_1 },
   { 0x030000, 0xF7, dsw_data_Maniacsq_0 },
   { 0,        0,    NULL,      },
};



static void BiomToyDecode(char *S,int tb, int td)
{
   int ta,tc,tb2;

   if(!load_rom(S, RAM, 0x80000)) return;

   tb2 = tb;

   for(ta=0x00000;ta<0x40000;ta++){
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

   tb = tb2+0x400000;
   for(ta=0x40000;ta<0x80000;ta++){
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


static void load_biomtoy(void)
{
   int ta;

   RAMSize = 0x80000;

   if(!(ROM=AllocateMem(0x100000)))   return;
   if(!(RAM=AllocateMem(RAMSize)))    return;
   if(!(GFX=AllocateMem(0x800000)))   return;
   if(!(ADPCM=AllocateMem(0x140000))) return;


   /* 68000 ROMs */
   if(!load_rom("d18", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d16", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   memset(GFX+0x00000,0x00,0x800000);

   BiomToyDecode("j6", 0x000000,3);
   BiomToyDecode("j7", 0x000000,2);
   BiomToyDecode("j9", 0x000000,1);
   BiomToyDecode("j10",0x000000,0);

   BiomToyDecode("h6", 0x200000,3);
   BiomToyDecode("h7", 0x200000,2);
   BiomToyDecode("h9", 0x200000,1);
   BiomToyDecode("h10",0x200000,0);

   GFX_CHAR16 = GFX + 0x000000;
   GFX_TILE16 = GFX + 0x400000;

   RAM_VIDEO = RAM + 0x00000;
   RAM_SPR   = RAM + 0x20000;

   GFX_CHAR16_SOLID = make_solid_mask_16x16( GFX_CHAR16, 0x04000  ); // 0x04000 = num_tiles
   GFX_TILE16_SOLID = make_solid_mask_16x16( GFX_TILE16, 0x04000  );

   InitPaletteMap(RAM+0x010000, 0x40, 0x10, 0x8000);
   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // ADPCM banks

   if(!load_rom("c1", RAM, 0x80000))   return;
   //   for(ta=0;ta<16;ta++)
   memcpy(ADPCM,RAM,0x40000);
   memcpy(ADPCM+0x40000,RAM,0x80000);
   //for(ta=0;ta<8;ta++)
   //memcpy(ADPCM+0x30000+ta*0x40000,RAM+ta*0x10000,0x10000);
   if(!load_rom("c3",ADPCM+0xc0000,0x80000))   return;
/*    for(ta=0;ta<8;ta++) */
/*       memcpy(ADPCM+0x230000+ta*0x40000,RAM+ta*0x10000,0x10000); */

   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),ADPCM,0x40000);

   memset(RAM+0x000000,0x00,0x50000);
   memset(RAM+0x030000,0xFF,0x10);


/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x50000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM);				// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x101FFF, NULL, RAM+0x000000);			// VIDEORAM
   AddReadByte(0x200000, 0x2007FF, NULL, RAM+0x010000);			// PALETTERAM
   AddReadByte(0x440000, 0x440FFF, NULL, RAM+0x020000);			// SPRITERAM
   AddReadByte(0x700000, 0x700007, NULL, RAM+0x030000);                 // DSW/INPUT
   AddReadByte(0x70000F, 0x70000F, OKIM6295_status_0_r, NULL);  	                // ADPCM CHANNEL A
   AddReadByte(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);			// WORKRAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x101FFF, NULL, RAM+0x000000);			// VIDEORAM
   AddReadWord(0x200000, 0x2007FF, NULL, RAM+0x010000);			// PALETTERAM
   AddReadWord(0x440000, 0x440FFF, NULL, RAM+0x020000);			// SPRITERAM
   AddReadWord(0x700000, 0x700007, NULL, RAM+0x030000);			// DSW/INPUT
   AddReadWord(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);			// WORKRAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);


   AddWriteByte(0x100000, 0x101FFF, NULL, RAM+0x000000);		// VIDEORAM
   AddWriteByte(0x108000, 0x108007, NULL, RAM+0x008000);		// Video registers
   AddWriteByte(0x200000, 0x2007FF, NULL, RAM+0x010000);		// PALETTERAM
   AddWriteByte(0x440000, 0x440FFF, NULL, RAM+0x020000);		// SPRITERAM
   AddWriteByte(0x70000D, 0x70000D, M6295_A_WriteBank_68k, NULL);             // ADPCM BANKSWITCH
   AddWriteByte(0x70000F, 0x70000F, OKIM6295_data_0_w, NULL);                 // ADPCM CHANNEL A
   AddWriteByte(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);		// WORKRAM
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x101FFF, NULL, RAM+0x000000);		// VIDEORAM
   AddWriteWord(0x108000, 0x108007, NULL, RAM+0x008000);		// Video registers
   AddWriteWord(0x200000, 0x2007FF, NULL, RAM+0x010000);		// PALETTERAM
   AddWriteWord(0x440000, 0x440FFF, NULL, RAM+0x020000);		// SPRITERAM
   AddWriteWord(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);		// WORKRAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);


   AddInitMemory();	// Set Starscream mem pointers...
}


static void ManiacsqDecode(char *S, int td)
{
   int ta,tc,tb=0;

   if(!load_rom(S, RAM, 0x40000)) return;

   for(ta=0x00000;ta<0x40000;ta++){
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


static void load_maniacsq(void)
{
   int ta;

   RAMSize = 0x80000;

   if(!(ROM=AllocateMem(0x40000)))    return;
   if(!(RAM=AllocateMem(RAMSize)))    return;
   if(!(GFX=AllocateMem(0x200000)))   return;
   if(!(ADPCM=AllocateMem(0x140000))) return;

   /* 68000 ROMs */
   if(!load_rom("d18", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d16", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   memset(GFX+0x00000,0x00,0x200000);

   ManiacsqDecode("f3", 3);
   ManiacsqDecode("f2", 2);
   ManiacsqDecode("f1", 1);
   ManiacsqDecode("f0", 0);

   GFX_CHAR16 = GFX;
   GFX_TILE16 = GFX_CHAR16;

   RAM_VIDEO = RAM + 0x00000;
   RAM_SPR   = RAM + 0x20000;

   GFX_CHAR16_SOLID = make_solid_mask_16x16( GFX_CHAR16, 0x2000  );
   GFX_TILE16_SOLID = GFX_CHAR16_SOLID;

   InitPaletteMap(RAM+0x010000, 0x40, 0x10, 0x8000);
   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);


   // ADPCM banks

   if(!load_rom("c1", RAM, 0x80000))   return;
   memcpy(ADPCM,RAM,0x40000);
   memcpy(ADPCM+0x40000,RAM,0x80000);
   memcpy(ADPCM+0xc0000,RAM,0x80000); // Twice the same rom... !

   ADPCMSetBuffers(((struct ADPCMinterface*)&m6295_interface),ADPCM,0x40000);

   memset(RAM+0x000000,0x00,0x50000);
   memset(RAM+0x030000,0xFF,0x10);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x50000);

   AddMemFetch(0x000000, 0x03FFFF, ROM);				// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x101FFF, NULL, RAM+0x000000);			// VIDEORAM
   AddReadByte(0x200000, 0x2007FF, NULL, RAM+0x010000);			// PALETTERAM
   AddReadByte(0x440000, 0x440FFF, NULL, RAM+0x020000);			// SPRITERAM
   AddReadByte(0x700000, 0x700007, NULL, RAM+0x030000);                 // DSW/INPUT
   AddReadByte(0x70000F, 0x70000F, OKIM6295_status_0_r, NULL);  	                // ADPCM CHANNEL A
   AddReadByte(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);			// WORKRAM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x101FFF, NULL, RAM+0x000000);			// VIDEORAM
   AddReadWord(0x200000, 0x2007FF, NULL, RAM+0x010000);			// PALETTERAM
   AddReadWord(0x440000, 0x440FFF, NULL, RAM+0x020000);			// SPRITERAM
   AddReadWord(0x700000, 0x700007, NULL, RAM+0x030000);			// DSW/INPUT
   AddReadWord(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);			// WORKRAM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);


   AddWriteByte(0x100000, 0x101FFF, NULL, RAM+0x000000);		// VIDEORAM
   AddWriteByte(0x108000, 0x108007, NULL, RAM+0x008000);		// Video registers
   AddWriteByte(0x200000, 0x2007FF, NULL, RAM+0x010000);		// PALETTERAM
   AddWriteByte(0x440000, 0x440FFF, NULL, RAM+0x020000);		// SPRITERAM
   AddWriteByte(0x70000D, 0x70000D, M6295_A_WriteBank_68k, NULL);             // ADPCM BANKSWITCH
   AddWriteByte(0x70000F, 0x70000F, OKIM6295_data_0_w, NULL);                 // ADPCM CHANNEL A
   AddWriteByte(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);		// WORKRAM
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x101FFF, NULL, RAM+0x000000);		// VIDEORAM
   AddWriteWord(0x108000, 0x108007, NULL, RAM+0x008000);		// Video registers
   AddWriteWord(0x200000, 0x2007FF, NULL, RAM+0x010000);		// PALETTERAM
   AddWriteWord(0x440000, 0x440FFF, NULL, RAM+0x020000);		// SPRITERAM
   AddWriteWord(0xFF0000, 0xFFFFFF, NULL, RAM+0x040000);		// WORKRAM
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);


   AddInitMemory();	// Set Starscream mem pointers...
   adpcm_amplify = 2;
}


static void execute_biomtoy(void)
{

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 12MHz (60fps) but it's smoother with 16MHZ
   cpu_interrupt(CPU_68K_0, 6);
}


static void execute_maniacsq(void)
{

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));
   cpu_interrupt(CPU_68K_0, 6);
}


static void DrawBiomToy(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   UINT8 *map;

   ClearPaletteMap();

   clear_game_screen(0);  // needed to see the service screen properly



   //  SCREEN 1
   // ----------


   MAKE_SCROLL_512x512_4_16(
       ReadWord(&RAM[0x8006]),
       ReadWord(&RAM[0x8004])+16
   );


   START_SCROLL_512x512_4_16(32,32,320,240);

      ta = (ReadWord( &RAM_VIDEO[zz+0x1000] ) >> 2);

      if( GFX_TILE16_SOLID[ta] ){

         MAP_PALETTE_MAPPED_NEW(
           RAM_VIDEO[zz+0x1000+2] & 0x3F ,   // bank
           16,
	   map
         );

         if(GFX_TILE16_SOLID[ta]==1){			// Some pixels; trans
            switch( RAM_VIDEO[zz+0x1000] & 0x03){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }else{
	    switch( RAM_VIDEO[zz+0x1000] & 0x03){	// all pixels; solid
               case 0x00: Draw16x16_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }
      }


   END_SCROLL_512x512_4_16();



   //  SCREEN 0
   // ----------

   MAKE_SCROLL_512x512_4_16(
       ReadWord(&RAM[0x8002])+4,	// offset
       ReadWord(&RAM[0x8000])+16
   );

   START_SCROLL_512x512_4_16(32,32,320,240);

      ta = (ReadWord( &RAM_VIDEO[zz] ) >> 2);

      if( GFX_TILE16_SOLID[ta] ){

         MAP_PALETTE_MAPPED_NEW(
           RAM_VIDEO[zz+2] & 0x3F ,
           16,
           map
         );

         if(GFX_TILE16_SOLID[ta]==1){			// Some pixels; trans
            switch(RAM_VIDEO[zz] & 0x03){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }else{
	    switch(RAM_VIDEO[zz] & 0x03){		// all pixels; solid
               case 0x00: Draw16x16_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }
      }

   END_SCROLL_512x512_4_16();



   //  SPRITES
   // ---------

   for(zz=6;zz<0x1000-6;zz+=8){

      y = 240 - RAM_SPR[zz];
      y += (y< 0) ? 0x110 : 0x10;

      if( (y>16) && (y<240+32) ){

         ta = (ReadWord(&RAM_SPR[zz+6]) >> 2);

         if(GFX_CHAR16_SOLID[ta]){				// No pixels; skip

            x = 32 + (ReadWord(&RAM_SPR[zz+4])&0x1FF) - 15;

            if((x>16)&&(x<320+32)){

               MAP_PALETTE_MAPPED_NEW(
                  (RAM_SPR[zz+5] & 0x7E) >> 1,
                  16,
                  map
               );

               if(GFX_CHAR16_SOLID[ta]==1){			// Some pixels; trans
                  switch(RAM_SPR[zz+1]&0xC0){
                     case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_CHAR16[ta<<8], x, y, map);        break;
                     case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_CHAR16[ta<<8], x, y, map); break;
                  }
               } else{						// all pixels; solid
                  switch(RAM_SPR[zz+1]&0xC0){
                     case 0x00: Draw16x16_Mapped_Rot(&GFX_CHAR16[ta<<8], x, y, map);        break;
                     case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_CHAR16[ta<<8], x, y, map); break;
                  }
               }
            }
         }
      }
   }


}


static void DrawManiacsq(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   UINT8 *map;

   ClearPaletteMap();

   // We do not clear the screen because otherwise text doesn't work properly

   //  SCREEN 0
   // ----------

   MAKE_SCROLL_512x512_4_16(
       ReadWord(&RAM[0x8002])+4,	// offset
       ReadWord(&RAM[0x8000])+16
   );

   START_SCROLL_512x512_4_16(32,32,320,240);

      ta = (ReadWord( &RAM_VIDEO[zz] ) >> 2)&0x1FFF;

      if( GFX_TILE16_SOLID[ta] ){

         MAP_PALETTE_MAPPED_NEW(
           RAM_VIDEO[zz+2] & 0x3F ,
           16,
           map
         );


         if(GFX_TILE16_SOLID[ta]==1){			// Some pixels; trans
            switch(RAM_VIDEO[zz] & 0x03){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }else{
	    switch(RAM_VIDEO[zz] & 0x03){		// all pixels; solid
               case 0x00: Draw16x16_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }
      }

   END_SCROLL_512x512_4_16();


   //  SCREEN 1
   // ----------


   MAKE_SCROLL_512x512_4_16(
       ReadWord(&RAM[0x8006]),
       ReadWord(&RAM[0x8004])+16
   );


   START_SCROLL_512x512_4_16(32,32,320,240);

      ta = (ReadWord( &RAM_VIDEO[zz+0x1000] ) >> 2)&0x1FFF;

      if( GFX_TILE16_SOLID[ta] ){

         MAP_PALETTE_MAPPED_NEW(
           RAM_VIDEO[zz+0x1000+2] & 0x3F ,   // bank
           16,
           map
         );


         if(GFX_TILE16_SOLID[ta]==1){			// Some pixels; trans
            switch( RAM_VIDEO[zz+0x1000] & 0x03){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }else{
	    switch( RAM_VIDEO[zz+0x1000] & 0x03){	// all pixels; solid
               case 0x00: Draw16x16_Mapped_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
               case 0x01: Draw16x16_Mapped_FlipY_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x02: Draw16x16_Mapped_FlipX_Rot(&GFX_TILE16[ta<<8], x, y, map);  break;
               case 0x03: Draw16x16_Mapped_FlipXY_Rot(&GFX_TILE16[ta<<8], x, y, map); break;
            }
         }
      }


   END_SCROLL_512x512_4_16();


   //  SPRITES
   // ---------

   for(zz=6;zz<0x1000-6;zz+=8){

      y = 240 - RAM_SPR[zz];
      y += (y< 0) ? 0x110 : 0x10;

      if( (y>16) && (y<240+32) ){

         ta = (ReadWord(&RAM_SPR[zz+6]) >> 2)&0x1FFF;

         if(GFX_CHAR16_SOLID[ta]){				// No pixels; skip

            x = 32 + (ReadWord(&RAM_SPR[zz+4])&0x1FF) - 15;

            if((x>16)&&(x<320+32)){

               MAP_PALETTE_MAPPED_NEW(
                  (RAM_SPR[zz+5] & 0x7E) >> 1,
                  16,
                  map
               );

               if(GFX_CHAR16_SOLID[ta]==1){			// Some pixels; trans
                  switch(RAM_SPR[zz+1]&0xC0){
                     case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_CHAR16[ta<<8], x, y, map);        break;
                     case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_CHAR16[ta<<8], x, y, map); break;
                  }
               } else{						// all pixels; solid
                  switch(RAM_SPR[zz+1]&0xC0){
                     case 0x00: Draw16x16_Mapped_Rot(&GFX_CHAR16[ta<<8], x, y, map);        break;
                     case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_CHAR16[ta<<8], x, y, map);  break;
                     case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_CHAR16[ta<<8], x, y, map); break;
                  }
               }
            }
         }
      }
   }

}


/***********************************************************************************************

From MAME source:

        Tile format
	-----------

	Screen 0 & 1: (32*32, 16x16 tiles)

	Byte | Bit(s)		 | Description
	-----+-FEDCBA98-76543210-+--------------------------
	  0  | -------- -------x | flip x
	  0  | -------- ------x- | flip y
	  0  | -------- xxxxxx-- | code (low 6 bits)
	  0  | xxxxxxxx -------- | code (high 8 bits)
	  2  | -------- --xxxxxx | color
	  2  | -------- xx------ | priority
	  2  | xxxxxxxx -------- | not used


        Sprite Format
	-------------

	Byte | Bit(s)		 | Description
	-----+-FEDCBA98-76543210-+--------------------------
	  0  | -------- xxxxxxxx | y position
	  0  | -----xxx -------- | not used
	  0  | ----x--- -------- | sprite size
	  0  | --xx---- -------- | sprite priority
	  0  | -x------ -------- | flipx
	  0  | x------- -------- | flipy
	  2  | xxxxxxxx xxxxxxxx | not used
	  4  | -------x xxxxxxxx | x position
	  4  | -xxxxxx- -------- | sprite color
	  6  | -------- ------xx | sprite code (8x8 cuadrant)
	  6  | xxxxxxxx xxxxxx-- | sprite code

Notes
-  sprite size: if bit is on the sprite is 8x8, oteherwise it's 16x16
   In biomtoy and maniacsq this bit is always off and it's not used in the driver
-  priority
   In biomtoy it's always 0. In maniacsq the priority changes but there's no need to draw the
   same plane with different priorities because swapping layers works good

************************************************************************************************/
static struct VIDEO_INFO video_biomtoy =
{
   DrawBiomToy,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct VIDEO_INFO video_maniacsq =
{
   DrawManiacsq,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_biomtoy[] =
{
   { "biomechanical_toy", },
   { "Biomechanical_Toy", },
   { "biomtoy", },
   { "BiomToy", },
   { NULL, },
};
GAME( biomtoy, "Biomechanical Toy", ZEUS, 1995, GAME_PLATFORM,
	.input = input_maniacsq,
	.dsw = dsw_biomtoy,
	.video = &video_biomtoy,
	.exec = execute_biomtoy,
	.long_name_jpn = "Biomechanical Toy",
	.sound = sound_maniacsq,
);
static struct DIR_INFO dir_maniacsq[] =
{
   { "Maniac_Square", },
   { "maniacsq", },
   { "maniacsp", },
   { NULL, },
};
GME( maniacsq, "Maniac Square", GAELCO, 1996, GAME_PUZZLE);

