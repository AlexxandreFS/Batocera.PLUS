/******************************************************************************/
/*                                                                            */
/*                    EXZISUS (C) 1987 TAITO CORPORATION                      */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "savegame.h"
#include "blit.h" // clear_game_screen

/*

Z80 x 3

TC0140SYT

Z80 + YM2151

TC0010VCU x 2

B12 = Exzisus (2 screens)     = original game
B23 = Exzisus (single screen) = romswap update

*/


static struct ROM_INFO rom_exzisus[] =
{
   {   "b12-12.bin", 0x00010000, 0xa662be67, 0, 0, 0, },
   {   "b12-13.bin", 0x00010000, 0x04a29633, 0, 0, 0, },
   {   "b12-15.bin", 0x00010000, 0xd81107c8, 0, 0, 0, },
   {   "b12-16.bin", 0x00010000, 0x6fec6acb, 0, 0, 0, },
   {   "b12-17.bin", 0x00010000, 0xdb1d5a6c, 0, 0, 0, },
   {   "b12-18.bin", 0x00010000, 0x64e358aa, 0, 0, 0, },
   {   "b12-19.bin", 0x00010000, 0x772b2641, 0, 0, 0, },
   {   "b12-20.bin", 0x00010000, 0x87f52e89, 0, 0, 0, },
   {   "b23-03.bin", 0x00000400, 0x9458fd45, 0, 0, 0, },
   {   "b23-04.bin", 0x00000400, 0x5042cffa, 0, 0, 0, },
   {   "b23-05.bin", 0x00000400, 0x87f0f69a, 0, 0, 0, },
   {   "b23-06.bin", 0x00010000, 0x44f8f661, 0, 0, 0, },
   {   "b23-07.bin", 0x00010000, 0xd7f6ec89, 0, 0, 0, },
   {   "b23-08.bin", 0x00010000, 0x1ce498c1, 0, 0, 0, },
   {   "b23-09.bin", 0x00010000, 0x6651617f, 0, 0, 0, },
   {   "b23-10.bin", 0x00010000, 0xc80216fc, 0, 0, 0, },
   {   "b23-11.bin", 0x00010000, 0xd6a79cef, 0, 0, 0, },
   {   "b23-12.bin", 0x00010000, 0x13637f54, 0, 0, 0, },
   {   "b23-13.bin", 0x00008000, 0x51110aa1, 0, 0, 0, },
   {   "b23-14.bin", 0x00008000, 0xf7ca7df2, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_exzisus[] =
{
   INP1( COIN1, 0x020002, 0x10 ),
   INP1( COIN2, 0x020002, 0x20 ),
   INP0( TILT, 0x020002, 0x02 ),
   INP0( SERVICE, 0x020002, 0x01 ),

   INP0( P1_START, 0x020002, 0x04 ),
   INP0( P1_UP, 0x020000, 0x01 ),
   INP0( P1_DOWN, 0x020000, 0x02 ),
   INP0( P1_LEFT, 0x020000, 0x08 ),
   INP0( P1_RIGHT, 0x020000, 0x04 ),
   INP0( P1_B1, 0x020000, 0x10 ),
   INP0( P1_B2, 0x020000, 0x20 ),

   INP0( P2_START, 0x020002, 0x08 ),
   INP0( P2_UP, 0x020001, 0x01 ),
   INP0( P2_DOWN, 0x020001, 0x02 ),
   INP0( P2_LEFT, 0x020001, 0x08 ),
   INP0( P2_RIGHT, 0x020001, 0x04 ),
   INP0( P2_B1, 0x020001, 0x10 ),
   INP0( P2_B2, 0x020001, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_exzisus_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_3COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_exzisus_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("150k and every 200k"),   0x0C},
   { _("100k and every 150k"),   0x08},
   { _("150k"),                  0x04},
   { _("200k"),                  0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "5",                     0x10},
   { "2",                     0x00},
   { MSG_DSWB_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWB_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_exzisus[] =
{
   { 0x020004, 0xFF, dsw_data_exzisus_0 },
   { 0x020005, 0xFF, dsw_data_exzisus_1 },
   { 0,        0,    NULL,      },
};


static struct ROMSW_DATA romsw_data_exzisus_0[] =
{
   { "Taito Japan (notice)",     0x01 },
   { "Taito America",            0x02 },
   { "Taito Japan",              0x03 },
   { "Tad Corporation",          0x04 },
   { NULL,                       0    },
};

static struct ROMSW_INFO romsw_exzisus[] =
{
   { 0x2007FFF, 0x01, romsw_data_exzisus_0 },
   { 0,        0,    NULL },
};


static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;
static UINT8 *GFX_BG1;
static UINT8 *GFX_BG1_SOLID;

static UINT8 *RAM2;
static UINT8 *RAM3;
static UINT8 *ROM2;
static UINT8 *RAM_INPUT;
static UINT8 *RAM_COLOUR;

/******************************************************************************/
/* MAIN Z80 ROM BANKING                                                       */
/******************************************************************************/

static void exzisus_bank_w(UINT16 offset, UINT8 data)
{
   offset &= 15;

   if(offset==0){
     z80_set_bank(1,data & 0xf);
   }
}

static void init_bank_rom(UINT8 *src, UINT8 *dst)
{
  z80_init_banks_area_ofs(1,src,0x20000,0x8000,0x4000,2);
/*    int ta; */

/*    for(ta=0; ta<0x10; ta++){ */
/*       ROM_BANK[ta] = dst+(ta*0xC000); */
/*       memcpy(ROM_BANK[ta]+0x0000,src+0x0000,0x8000); */
/*       memcpy(ROM_BANK[ta]+0x8000,src+(ta*0x4000),0x4000); */
/*    } */
}

/******************************************************************************/
/* SUB Z80 ROM BANKING                                                        */
/******************************************************************************/

static void exzisus_sub_bank_w(UINT16 offset, UINT8 data)
{
   offset &= 15;

   switch(offset){
   case 0x00:

     z80_set_bank(2,data & 0xf);
/*       z80_bank_1 = data & 0x0F; */
/*       Z80CSetBank( ROM_BANK_1[z80_bank_1] ); */
      /*#ifdef RAINE_DEBUG
      print_debug("SUB Bank: %02x [%04x]\n", data, z80pc);
#endif*/
/*    } */

   break;
   case 0x02:

      switch_led(0,(data>>2)&1);		// Coin A [Coin Inserted]
      switch_led(1,(data>>3)&1);		// Coin B [Coin Inserted]
      switch_led(2,(data>>0)&1);		// Coin A [Ready for coins]
    //switch_led(3,(data>>1)&1);		// Coin B [Ready for coins]

   break;
   }
}

static void init_bank_rom_1(UINT8 *src, UINT8 *dst)
{
  z80_init_banks_area_ofs(2,src,0x30000,0x8000,0x4000,2);
/*    int ta; */

/*    for(ta=0; ta<0x10; ta++){ */
/*       ROM_BANK_1[ta] = dst+(ta*0xC000); */
/*       memcpy(ROM_BANK_1[ta]+0x0000,src+0x0000,0x8000); */
/*       memcpy(ROM_BANK_1[ta]+0x8000,src+(ta*0x4000),0x4000); */
/*    } */
}

/******************************************************************************/
/* INPUT + DSW                                                                */
/******************************************************************************/

static UINT8 exzisus_ioc_rb(UINT16 offset)
{
   return RAM_INPUT[offset & 0x0F];
}

/******************************************************************************/
/* LOAD SAVE DATA                                                             */
/******************************************************************************/

static void DrawNibble0(UINT8 *out, UINT32 plane, UINT8 c)
{
   int count, t;

   count = 4;
      do {
         t = c & 1;
         *out = t << plane;
         out++;
         c >>= 1;
      } while(--count);
}

static void DrawNibble(UINT8 *out, UINT32 plane, UINT8 c)
{
   int count, t;

   count = 4;
      do {
         t = c & 1;
         *out |= t << plane;
         out++;
         c >>= 1;
      } while(--count);
}

static void load_exzisus(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   RAMSize=0x10000+0x10000+0x10+0x10000+0x10000+0x400;

   if(!(ROM2=AllocateMem(0xC000*0x10))) return;

   if(!(RAM=AllocateMem(RAMSize))) return;

   if(!(TMP=AllocateMem(0x080000))) return;

   RAM2       = RAM+0x10000;
   RAM_INPUT  = RAM+0x10000+0x10000;
   Z80ROM     = RAM+0x10000+0x10000+0x10;
   RAM3       = RAM+0x10000+0x10000+0x10+0x10000;
   RAM_COLOUR = RAM+0x10000+0x10000+0x10+0x10000+0x10000;

   /*-----[Sound Setup]-----*/

   if(!load_rom("b23-14.bin", Z80ROM, 0x8000)) return;	// Z80 SOUND ROM
   memset(Z80ROM+0x8000,0x00,0x8000);

   AddTaitoYM2151(0x01C7, 0x01A0, 0x10000, NULL, NULL);

   /*-----------------------*/

   if(!load_rom("b23-10.bin",TMP+0x00000,0x10000)) return;	// Z80 MAIN ROM
   if(!load_rom("b23-12.bin",TMP+0x10000,0x10000)) return;	// Z80 MAIN ROM
   memset(TMP+0x20000,0x00,0x10000);
   memset(TMP+0x30000,0x00,0x10000);

   // fix rom 1 error

   TMP[0x6829]=0x18;

   // fix work ram error

   TMP[0x67fd]=0x18;

   // Skip Idle Z80

   TMP[0x0084]=0xD3;  // OUTA (AAh)
   TMP[0x0085]=0xAA;  //

   SetStopZ80BMode2(0x007E);

   init_bank_rom(TMP,ROM);

   memset(RAM, 0x00, 0x10000);
   memcpy(RAM, TMP,  0x0C000);

   AddZ80BROMBase(RAM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM + BANK
   AddZ80BReadByte(0xE000, 0xEFFF, NULL,			RAM +0xE000);	// RAM
   AddZ80BReadByte(0xC000, 0xDFFF, NULL,			RAM3+0x8000);	// VIDEO
   AddZ80BReadByte(0xF800, 0xFFFF, NULL,			RAM +0xF800);	// COMMON RAM
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xE000, 0xEFFF, NULL,			RAM +0xE000);	// RAM
   AddZ80BWriteByte(0xC000, 0xDFFF, NULL,			RAM3+0x8000);	// VIDEO
   AddZ80BWriteByte(0xF400, 0xF40F, exzisus_bank_w,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xF800, 0xFFFF, NULL,			RAM +0xF800);	// COMMON RAM
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("b23-11.bin",TMP+0x00000,0x10000)) return;	// Z80 SUB ROM
   if(!load_rom("b12-12.bin",TMP+0x10000,0x10000)) return;	// Z80 SUB ROM
   if(!load_rom("b12-13.bin",TMP+0x20000,0x10000)) return;	// Z80 SUB ROM
   memset(TMP+0x30000,0x00,0x10000);

   // Skip Idle Z80

   TMP[0x0089]=0xD3;  // OUTA (AAh)
   TMP[0x008A]=0xAA;  //

   SetStopZ80CMode2(0x0083);

   init_bank_rom_1(TMP,ROM2);

   memset(RAM2, 0x00, 0x10000);
   memcpy(RAM2, TMP, 0x0C000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM + BANK
   AddZ80CReadByte(0xE000, 0xEFFF, NULL,			RAM2+0xE000);	// RAM
   AddZ80CReadByte(0xC000, 0xDFFF, NULL,			RAM +0xC000);	// VIDEO RAM [COMMON]
   AddZ80CReadByte(0xF000, 0xF001, tc0140syt_read_main_z80,     NULL);		// SOUND COMM
   AddZ80CReadByte(0xF800, 0xFFFF, NULL,			RAM +0xF800);	// COMMON?
   AddZ80CReadByte(0xF400, 0xF40F, exzisus_ioc_rb,		NULL);		// IOC
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xE000, 0xEFFF, NULL,			RAM2+0xE000);	// RAM
   AddZ80CWriteByte(0xC000, 0xDFFF, NULL,			RAM +0xC000);	// VIDEO RAM [COMMON]
   AddZ80CWriteByte(0xF400, 0xF40F, exzisus_sub_bank_w,		NULL);		// ROM BANK
   AddZ80CWriteByte(0xF000, 0xF001, tc0140syt_write_main_z80,   NULL);		// SOUND COMM
   AddZ80CWriteByte(0xF800, 0xFFFF, NULL,			RAM +0xF800);	// COMMON?
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();
   exzisus_sub_bank_w(0,0); // pre-init bank !!!
   if(!load_rom("b23-13.bin",RAM3,0x08000)) return;	// Z80 SUB^SUB ROM
   memset(RAM3+0x8000, 0x00, 0x8000);

   // Skip Idle Z80

   RAM3[0x010F]=0xD3;  // OUTA (AAh)
   RAM3[0x0110]=0xAA;  //

   SetStopZ80DMode2(0x0109);

   AddZ80DROMBase(RAM3, 0x0038, 0x0066);

   AddZ80DReadByte(0x0000, 0x7FFF, NULL,			RAM3+0x0000);	// Z80 ROM
   AddZ80DReadByte(0xB000, 0xBFFF, NULL,			RAM3+0xB000);	// RAM
   AddZ80DReadByte(0x8000, 0x9FFF, NULL,			RAM3+0x8000);	// VIDEO RAM [COMMON]
   AddZ80DReadByte(0xA000, 0xAFFF, NULL,			RAM +0xE000);	// COMMON
   AddZ80DReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80DReadByte(-1, -1, NULL, NULL);

   AddZ80DWriteByte(0xB000, 0xBFFF, NULL,			RAM3+0xB000);	// RAM
   AddZ80DWriteByte(0x8000, 0x9FFF, NULL,			RAM3+0x8000);	// VIDEO RAM [COMMON]
   AddZ80DWriteByte(0xA000, 0xAFFF, NULL,			RAM +0xE000);	// COMMON
   AddZ80DWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80DWriteByte(-1, -1, NULL, NULL);

   AddZ80DReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80DReadPort(-1, -1, NULL, NULL);

   AddZ80DWritePort(0xAA, 0xAA, StopZ80DMode2,			NULL);		// Trap Idle Z80
   AddZ80DWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad reads>
   AddZ80DWritePort(-1, -1, NULL, NULL);

   AddZ80DInit();

   if(!(GFX=AllocateMem(0x100000+0x100000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG1 = GFX+0x100000;

   tb=0;
   if(!load_rom("b23-06.bin", TMP+0x00000, 0x10000)) return;
   if(!load_rom("b23-08.bin", TMP+0x10000, 0x10000)) return;
   memset(TMP+0x20000,0x00,0x10000);
   memset(TMP+0x30000,0x00,0x10000);
   if(!load_rom("b23-07.bin", TMP+0x40000, 0x10000)) return;
   if(!load_rom("b23-09.bin", TMP+0x50000, 0x10000)) return;
   memset(TMP+0x60000,0x00,0x10000);
   memset(TMP+0x70000,0x00,0x10000);
   for(ta=0;ta<0x40000;ta+=2,tb+=8){
      DrawNibble0(GFX_BG1+tb+0, 0, (UINT8) (TMP[ta+0x00000]&15) );
      DrawNibble (GFX_BG1+tb+0, 1, (UINT8) (TMP[ta+0x00000]>>4) );
      DrawNibble (GFX_BG1+tb+0, 2, (UINT8) (TMP[ta+0x40000]&15) );
      DrawNibble (GFX_BG1+tb+0, 3, (UINT8) (TMP[ta+0x40000]>>4) );
      DrawNibble0(GFX_BG1+tb+4, 0, (UINT8) (TMP[ta+0x00001]&15) );
      DrawNibble (GFX_BG1+tb+4, 1, (UINT8) (TMP[ta+0x00001]>>4) );
      DrawNibble (GFX_BG1+tb+4, 2, (UINT8) (TMP[ta+0x40001]&15) );
      DrawNibble (GFX_BG1+tb+4, 3, (UINT8) (TMP[ta+0x40001]>>4) );
   }

   tb=0;
   if(!load_rom("b12-16.bin", TMP+0x00000, 0x10000)) return;
   if(!load_rom("b12-18.bin", TMP+0x10000, 0x10000)) return;
   if(!load_rom("b12-20.bin", TMP+0x20000, 0x10000)) return;
   memset(TMP+0x30000,0x00,0x10000);
   if(!load_rom("b12-15.bin", TMP+0x40000, 0x10000)) return;
   if(!load_rom("b12-17.bin", TMP+0x50000, 0x10000)) return;
   if(!load_rom("b12-19.bin", TMP+0x60000, 0x10000)) return;
   memset(TMP+0x70000,0x00,0x10000);
   for(ta=0;ta<0x40000;ta+=2,tb+=8){
      DrawNibble0(GFX_BG0+tb+0, 0, (UINT8) (TMP[ta+0x00000]&15) );
      DrawNibble (GFX_BG0+tb+0, 1, (UINT8) (TMP[ta+0x00000]>>4) );
      DrawNibble (GFX_BG0+tb+0, 2, (UINT8) (TMP[ta+0x40000]&15) );
      DrawNibble (GFX_BG0+tb+0, 3, (UINT8) (TMP[ta+0x40000]>>4) );
      DrawNibble0(GFX_BG0+tb+4, 0, (UINT8) (TMP[ta+0x00001]&15) );
      DrawNibble (GFX_BG0+tb+4, 1, (UINT8) (TMP[ta+0x00001]>>4) );
      DrawNibble (GFX_BG0+tb+4, 2, (UINT8) (TMP[ta+0x40001]&15) );
      DrawNibble (GFX_BG0+tb+4, 3, (UINT8) (TMP[ta+0x40001]>>4) );
   }

   if(!load_rom("b23-04.bin", TMP+0x00000, 0x400)) return;
   if(!load_rom("b23-03.bin", TMP+0x00400, 0x400)) return;
   if(!load_rom("b23-05.bin", TMP+0x00800, 0x400)) return;

   for(ta=0;ta<0x200;ta++){

      tb  = ta & 0x1F0;
      tb |= 15 - (ta & 15);

      tc  = (TMP[tb+0x000]&15)<<8;
      tc |= (TMP[tb+0x400]&15)<<4;
      tc |= (TMP[tb+0x800]&15)<<0;

      WriteWord(&RAM_COLOUR[ta<<1], tc);

   }

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_8x8(GFX_BG0, 0x4000);
   GFX_BG1_SOLID = make_solid_mask_8x8(GFX_BG1, 0x4000);

   InitPaletteMap(RAM_COLOUR, 0x20, 0x10, 0x1000);

   set_colour_mapper(&col_map_xxxx_rrrr_gggg_bbbb);
}

static void clear_exzisus(void)
{
   RemoveTaitoYM2151();
}

static void execute_exzisus(void)
{
   cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));	// Main Z80 8MHz (60fps)
      print_debug("Z80PC_MAIN:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_2, 0x38);

   cpu_execute_cycles(CPU_Z80_3, CPU_FRAME_MHz(8,60));	// Sub-2 Z80 8MHz (60fps)
      print_debug("Z80PC_SUB2:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_3, 0x38);

   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(8,60));	// Sub-1 Z80 8MHz (60fps)
      print_debug("Z80PC_SUB1:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_1, 0x38);

   Taito2151_Frame();
}

static void draw_exzisus(void)
{
   int x,y,ta;
   int sx,sy,offs,goffs,gfx_offs,gfx_num,gfx_attr,height,xc,yc;
   UINT8 *map,*RAM_BG;

   ClearPaletteMap();

   clear_game_screen(0);

   // TC0010VCU 0

   RAM_BG = RAM+0xC000;

   sx = 0;
   for (offs=0;offs<0x600;offs+=4)
   {
      if (*(UINT32 *)(&RAM_BG[offs + 0]) == 0) continue;

      gfx_num = RAM_BG[offs + 1];
      gfx_attr = RAM_BG[offs + 3];

      if ((gfx_num & 0x80) == 0){     /* 16x16 sprites */

         gfx_offs = gfx_num & 0x7F;
         gfx_offs <<= 3;
         gfx_offs += 0x0600;
         height = 2;

         sx  = RAM_BG[offs + 2];
         sx |= (gfx_attr & 0x40) << 2;

      }
      else{                           /* 16x256 columns */

         gfx_offs = gfx_num & 0x3F;
         gfx_offs <<= 7;
         gfx_offs += 0x0A00;
         height = 32;

         if(gfx_num & 0x40)
            sx += 16;
         else {
            sx  = RAM_BG[offs + 2];
            sx |= (gfx_attr & 0x40) << 2;
	 }
      }

      sy = 256 - height*8 - (RAM_BG[offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++,goffs+=2)
         {
            ta = ReadWord(&RAM_BG[goffs]);
            if(GFX_BG0_SOLID[ta&0x3FFF]){

            MAP_PALETTE_MAPPED_NEW(
               (gfx_attr & 0x0F) | ((ta & 0xC000) >> 14),
               16,
               map
            );

            ta &= 0x3FFF;

            x = (sx + (xc << 3)) & 0xff;
            y = ((sy + (yc << 3)) & 0xff) -16;

            if ((x > -8) && (y > -8) && (x < 256) && (y < 224))
            {
               if(GFX_BG0_SOLID[ta] == 1)
                  Draw8x8_Trans_Mapped_Rot(&GFX_BG0[ta<<6], x+32, y+32, map);
               else
                  Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6], x+32, y+32, map);
            }
            }
         }

         gfx_offs += height<<1;
      }
   }

   // TC0010VCU 1

   RAM_BG = RAM3+0x8000;

   sx = 0;
   for (offs=0;offs<0x600;offs+=4)
   {
      if (*(UINT32 *)(&RAM_BG[offs + 0]) == 0) continue;

      gfx_num = RAM_BG[offs + 1];
      gfx_attr = RAM_BG[offs + 3];

      if ((gfx_num & 0x80) == 0){     /* 16x16 sprites */

         gfx_offs = gfx_num & 0x7F;
         gfx_offs <<= 3;
         gfx_offs += 0x0600;
         height = 2;

         sx  = RAM_BG[offs + 2];
         sx |= (gfx_attr & 0x40) << 2;

      }
      else{                           /* 16x256 columns */

         gfx_offs = gfx_num & 0x3F;
         gfx_offs <<= 7;
         gfx_offs += 0x0A00;
         height = 32;

         if(gfx_num & 0x40)
            sx += 16;
         else {
            sx  = RAM_BG[offs + 2];
            sx |= (gfx_attr & 0x40) << 2;
	 }
      }

      sy = 256 - height*8 - (RAM_BG[offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++,goffs+=2)
         {
            ta = ReadWord(&RAM_BG[goffs]);
            if(GFX_BG1_SOLID[ta&0x3FFF]){

            MAP_PALETTE_MAPPED_NEW(
               (gfx_attr & 0x0F) | ((ta & 0xC000) >> 14) | 0x10,
               16,
               map
            );

            ta &= 0x3FFF;

            x = (sx + (xc << 3)) & 0xff;
            y = ((sy + (yc << 3)) & 0xff) -16;

            if ((x > -8) && (y > -8) && (x < 256) && (y < 224))
            {
               if(GFX_BG1_SOLID[ta] == 1)
                  Draw8x8_Trans_Mapped_Rot(&GFX_BG1[ta<<6], x+32, y+32, map);
               else
                  Draw8x8_Mapped_Rot(&GFX_BG1[ta<<6], x+32, y+32, map);
            }
            }
         }

         gfx_offs += height<<1;
      }
   }
}

/*

CTRL RAM (OBJECT RAM)

0x0600 bytes

 0 |xxxxxxxx| Sprite Y (low)
 1 |x.......| 16x16 sprite / 16x256 column select
 1 |.x......| X Chain (16x256 column)
 1 |..xxxxxx| Sprite num (16x256 column)
 1 |.xxxxxxx| Sprite num (16x16 sprite)
 2 |xxxxxxxx| Sprite X (low)
 3 |.x......| Sprite X (high)
 3 |....xx..| Colour Bank (high)
 3 |......xx| Colour Bank (low mirror)

DATA RAM (SCREEN RAM)

0x0400 bytes (16x16 sprite)
0x1600 bytes (16x256 column)

 0 |xx......| Colour Bank (low)
 0 |..xxxxxx| Tile (high)
 1 |xxxxxxxx| Tile (low)

*/
static struct VIDEO_INFO video_exzisus =
{
   draw_exzisus,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_exzisus[] =
{
   { "exzisus", },
   { NULL, },
};
GAME( exzisus, "Exzisus", TAITO, 1987, GAME_SHOOT,
	.input = input_exzisus,
	.dsw = dsw_exzisus,
	.romsw = romsw_exzisus,
	.clear = clear_exzisus,
	.video = &video_exzisus,
	.exec = execute_exzisus,
	.long_name_jpn = "イグジーザス",
	.board = "B23",
	.sound = taito_ym2151_sound,
);

