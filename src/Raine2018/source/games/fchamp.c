/*

 ******************************************************************************
 *                                                                            *
 *          FOOTBALL CHAMP/HAT TRICK HERO (C) 1990 TAITO CORPORATION          *
 *                 EURO CHAMP '92 (C) 1992 TAITO CORPORATION                  *
 *                                                                            *
 ******************************************************************************

  Aug 2, 2000:
  - Dipswitches defined for all 3 games.
      Hat Trick Hero read dips in reverse oder.
  - ROM names changed to match those used by Mame

  TO DO:
  - Hat Trick Hero uses slightly different SCRN offset for one screen layer.
      See displaced "white" box around announcer during the DEMO and other
      minor graphic gliches/errors.

*/

#define DRV_DEF_SOUND taito_ym2610_sound
#include "gameinc.h"
#include "tc006vcu.h"
#include "tc200obj.h"
#include "f3system.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"

static struct INPUT_INFO input_footchmp[] =
{
   INP0( COIN1, 0x032004, 0x01 ),
   INP0( COIN2, 0x032004, 0x02 ),
   INP0( TILT, 0x032004, 0x80 ),
   INP0( SERVICE, 0x032004, 0x10 ),

   INP0( P1_START, 0x03200A, 0x80 ),
   INP0( P1_UP, 0x03200A, 0x01 ),
   INP0( P1_DOWN, 0x03200A, 0x02 ),
   INP0( P1_LEFT, 0x03200A, 0x04 ),
   INP0( P1_RIGHT, 0x03200A, 0x08 ),
   INP0( P1_B1, 0x03200A, 0x10 ),
   INP0( P1_B2, 0x03200A, 0x20 ),

   INP0( P2_START, 0x03200C, 0x80 ),
   INP0( P2_UP, 0x03200C, 0x01 ),
   INP0( P2_DOWN, 0x03200C, 0x02 ),
   INP0( P2_LEFT, 0x03200C, 0x04 ),
   INP0( P2_RIGHT, 0x03200C, 0x08 ),
   INP0( P2_B1, 0x03200C, 0x10 ),
   INP0( P2_B2, 0x03200C, 0x20 ),

   INP0( P3_START, 0x03200E, 0x80 ),
   INP0( P3_UP, 0x03200E, 0x01 ),
   INP0( P3_DOWN, 0x03200E, 0x02 ),
   INP0( P3_LEFT, 0x03200E, 0x04 ),
   INP0( P3_RIGHT, 0x03200E, 0x08 ),
   INP0( P3_B1, 0x03200E, 0x10 ),
   INP0( P3_B2, 0x03200E, 0x20 ),

   INP0( P4_START, 0x032010, 0x80 ),
   INP0( P4_UP, 0x032010, 0x01 ),
   INP0( P4_DOWN, 0x032010, 0x02 ),
   INP0( P4_LEFT, 0x032010, 0x04 ),
   INP0( P4_RIGHT, 0x032010, 0x08 ),
   INP0( P4_B1, 0x032010, 0x10 ),
   INP0( P4_B2, 0x032010, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_football_champ_0[] =
{
   { _("Game Over For"),         0x01, 0x02 },
   { _("Both Teams"),            0x01},
   { _("Loser Team Only"),       0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0x80},
   { MSG_1COIN_4PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_football_champ_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Game Time"),             0x0C, 0x04 },
   { _(" 2  Minutes"),           0x0C},
   { _(" 3  Minutes"),           0x08},
   { _("2.5 Minutes"),           0x04},
   { _("1.5 Minutes"),           0x00},
   { _("Game Type"),             0x30, 0x04 },
   { _("2 Players"),             0x30},
   { _("4 Player/4 Coin Slot"),  0x20},
   { _("4 Player/2 Cabinets"),   0x10},
   { _("4 Player/2 Coin Slot"),  0x00},
   { _("Continue"),              0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { _("Euro Version"),          0x80, 0x02 },
   { MSG_ON,                  0x80},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_euro_champ_92_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Game Time"),             0x0C, 0x04 },
   { _(" 2  Minutes"),           0x0C},
   { _(" 3  Minutes"),           0x08},
   { _("2.5 Minutes"),           0x04},
   { _("1.5 Minutes"),           0x00},
   { _("Game Type"),             0x30, 0x04 },
   { _("2 Players"),             0x30},
   { _("4 Player/4 Coin Slot"),  0x20},
   { _("4 Player/2 Cabinets"),   0x10},
   { _("4 Player/2 Coin Slot"),  0x00},
   { _("Continue"),              0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_hat_trick_hero_0[] =
{
   { _("Game Over For"),         0x80, 0x02 }, // Bits read in reverse order, so...
   { _("Both Teams"),            0x80}, //  let's reverse the byte order but
   { _("Loser Team Only"),       0x00}, //  keep the visual look the same as
   DSW_SCREEN( 0x40, 0x00),
   DSW_TEST_MODE( 0x00, 0x20),
   DSW_DEMO_SOUND( 0x10, 0x00),
   { MSG_COIN1,               0x0c, 0x04 },
   { MSG_1COIN_1PLAY,         0x0c},
   { MSG_1COIN_2PLAY,         0x04},
   { MSG_2COIN_1PLAY,         0x08},
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_COIN2,               0x03, 0x04 },
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_1COIN_2PLAY,         0x01},
   { MSG_2COIN_1PLAY,         0x02},
   { MSG_3COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_hat_trick_hero_1[] =
{
   { MSG_DIFFICULTY,          0xc0, 0x04 },
   { MSG_NORMAL,              0xc0},
   { MSG_EASY,                0x40},
   { MSG_HARD,                0x80},
   { MSG_HARDEST,             0x00},
   { _("Game Time"),             0x30, 0x04 },
   { _(" 2  Minutes"),           0x30},
   { _(" 3  Minutes"),           0x10},
   { _("2.5 Minutes"),           0x20},
   { _("1.5 Minutes"),           0x00},
   { _("Game Type"),             0x0c, 0x04 },
   { _("2 Players"),             0x0c},
   { _("4 Player/4 Coin Slot"),  0x04},
   { _("4 Player/2 Cabinets"),   0x08},
   { _("4 Player/2 Coin Slot"),  0x00},
   { _("Continue"),              0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { NULL,                    0,   }, // Bit1 is unused, was bit8 for the _("Euro") in Footchamp
};


static struct DSW_INFO dsw_euroch92[] =
{
   { 0x032000, 0xFF, dsw_data_football_champ_0 },	// Needs cionage from Footbal Champ
   { 0x032002, 0xFF, dsw_data_euro_champ_92_1 },	// but DSW1 bit8 is unused
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_euroch92[] =
{
   {  "ec92_19.rom", 0x00100000, 0x219141a5, 0, 0, 0, },
   {       "c80-02.10", 0x00100000, 0x060a8b61, 0, 0, 0, },
   {       "c80-03.57", 0x00100000, 0x609938d5, 0, 0, 0, },
   {  "ec92_21.rom", 0x00080000, 0x5759ed37, 0, 0, 0, },
   {  "ec92_22.rom", 0x00080000, 0xd9a0d38e, 0, 0, 0, },
   {  "ec92_23.rom", 0x00020000, 0xae5e75e9, 0, 0, 0, },
   {  "ec92_25.rom", 0x00020000, 0x98482202, 0, 0, 0, },
   {  "ec92_26.rom", 0x00020000, 0xb986ccb2, 0, 0, 0, },
   {  "ec92_24.rom", 0x00020000, 0xb31d94ac, 0, 0, 0, },
   {  "ec92_27.rom", 0x00010000, 0x2db48e65, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};



static struct ROM_INFO rom_footchmp[] =
{
   {       "c80-01.9", 0x00100000, 0xf43782e6, 0, 0, 0, },
   {       "c80-02.10", 0x00100000, 0x060a8b61, 0, 0, 0, },
   {       "c80-03.57", 0x00100000, 0x609938d5, 0, 0, 0, },
   {       "c80-04.1", 0x00080000, 0x9a17fe8c, 0, 0, 0, },
   {       "c80-05.2", 0x00080000, 0xacde7071, 0, 0, 0, },
   {       "c80-10.4", 0x00020000, 0x32c109cb, 0, 0, 0, },
   {       "c80-11.6", 0x00020000, 0xf78630fb, 0, 0, 0, },
   {       "c80-12.7", 0x00020000, 0x80d46fef, 0, 0, 0, },
   {       "c80-14.5", 0x00020000, 0x40ac4828, 0, 0, 0, },
   {       "c80-15.70", 0x00010000, 0x05aa7fd7, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_INFO dsw_footchmp[] =
{
   { 0x032000, 0xFF, dsw_data_football_champ_0 },
   { 0x032002, 0xFF, dsw_data_football_champ_1 },
   { 0,        0,    NULL,      },
};




static struct ROM_INFO rom_hthero[] =
{
   {       "c80-01.9", 0x00100000, 0xf43782e6, 0, 0, 0, },
   {       "c80-02.10", 0x00100000, 0x060a8b61, 0, 0, 0, },
   {       "c80-03.57", 0x00100000, 0x609938d5, 0, 0, 0, },
   {       "c80-04.1", 0x00080000, 0x9a17fe8c, 0, 0, 0, },
   {       "c80-05.2", 0x00080000, 0xacde7071, 0, 0, 0, },
   {       "c80-17.4", 0x00020000, 0x42c0a838, 0, 0, 0, },
   {       "c80-16.6", 0x00020000, 0x4e795b52, 0, 0, 0, },
   {       "c80-12.7", 0x00020000, 0x80d46fef, 0, 0, 0, },
   {       "c80-18.5", 0x00020000, 0xaea22904, 0, 0, 0, },
   {       "c80-15.70", 0x00010000, 0x05aa7fd7, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_INFO dsw_hthero[] =
{
   { 0x032000, 0xFF, dsw_data_hat_trick_hero_0 },
   { 0x032002, 0xFF, dsw_data_hat_trick_hero_1 },
   { 0,        0,    NULL,      },
};


static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;
//static UINT8 *RAM_BG4;

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;
static UINT8 *RAM_SCR4;

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;
static UINT32 SCR4_XOFS;

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;
static UINT32 SCR4_YOFS;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static int romset;

static void BadWriteWord(UINT32 address, UINT16 data)
{
#ifdef RAINE_DEBUG
      if((address!=0x500002)&&(address!=0x800000))print_debug("Ww(%06x,%04x) [%06x]\n",address,data,s68000context.pc);
#endif
}

static void load_footchmp(void)
{
   int ta,tb;
   UINT8 *TMP;

   if (is_current_game("euroch92"))
       romset = 0;
   else if (is_current_game("footchmp"))
       romset = 1;
   else if (is_current_game("hthero"))
       romset = 2;

   if(!(GFX=AllocateMem(0x600000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;			// TEMP BUFFER

   GFX_BG0=GFX+0x000000;
   GFX_SPR=GFX+0x200000;

   tb=0;
   if(!load_rom_index(0, TMP, 0x100000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   if(!load_rom_index(1, TMP, 0x100000)) return;
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   tb=0;
   if(!load_rom_index(3, TMP, 0x80000)) return;	// 16x16 TILES ($2000)
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      GFX_BG0[tb+0]=TMP[ta]&15;
      GFX_BG0[tb+1]=TMP[ta]>>4;
      GFX_BG0[tb+2]=TMP[ta+1]&15;
      GFX_BG0[tb+3]=TMP[ta+1]>>4;
   }

   tb=4;
   if(!load_rom_index(4, TMP, 0x80000)) return;		// 16x16 TILES
   for(ta=0;ta<0x80000;ta+=2,tb+=8){
      GFX_BG0[tb+0]=TMP[ta]&15;
      GFX_BG0[tb+1]=TMP[ta]>>4;
      GFX_BG0[tb+2]=TMP[ta+1]&15;
      GFX_BG0[tb+3]=TMP[ta+1]>>4;
   }

   FreeMem(TMP);

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom_index(6, RAM+0x00000, 0x20000)) return;
   if(!load_rom_index(7, RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(5, RAM+0x00000, 0x20000)) return;
   if(!load_rom_index(8, RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   switch(romset){
      case 0:
         WriteWord68k(&ROM[0x173A],0x4E75);

         // speed hack

         WriteLong68k(&ROM[0x0670],0x13FC0001);	// move.b #$01,$AA0000
         WriteLong68k(&ROM[0x0674],0x00AA0000);
         WriteWord68k(&ROM[0x0678],0x60EC);

         WriteLong68k(&ROM[0x07AA],0x13FC0001);
         WriteLong68k(&ROM[0x07AE],0x00AA0000);

      break;
      case 1:
         WriteWord68k(&ROM[0x1728],0x4E75);

         // speed hack

         WriteLong68k(&ROM[0x0670],0x13FC0001);	// move.b #$01,$AA0000
         WriteLong68k(&ROM[0x0674],0x00AA0000);
         WriteWord68k(&ROM[0x0678],0x60EC);

         WriteLong68k(&ROM[0x07AA],0x13FC0001);
         WriteLong68k(&ROM[0x07AE],0x00AA0000);

      break;
      case 2:
         WriteWord68k(&ROM[0x1794],0x4E75);

         // speed hack

         WriteLong68k(&ROM[0x0670 + 0x56],0x13FC0001);	// move.b #$01,$AA0000
         WriteLong68k(&ROM[0x0674 + 0x56],0x00AA0000);
         WriteWord68k(&ROM[0x0678 + 0x56],0x60EC);

         WriteLong68k(&ROM[0x07AA + 0x54],0x13FC0001);
         WriteLong68k(&ROM[0x07AE + 0x54],0x00AA0000);

      break;
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;

   if(!(PCMROM=AllocateMem(0x100000))) return;

   if(!load_rom_index(9,Z80ROM,0x010000)) return;	// Z80 SOUND ROM
   if(!load_rom_index(2,PCMROM,0x100000)) return;	// ADPCM A rom

   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x01A4, 0x0150, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);
   memset(RAM+0x32000,0xFF,0x00020);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   RAM_BG0=RAM+0x20000;
   RAM_BG1=RAM+0x21000;
   RAM_BG2=RAM+0x22000;
   RAM_BG3=RAM+0x23000;

   RAM_SCR0=RAM+0x34000;
   RAM_SCR1=RAM+0x34002;
   RAM_SCR2=RAM+0x34004;
   RAM_SCR3=RAM+0x34006;
   RAM_SCR4=RAM+0x34018;

   SCR0_XOFS=0x0020;
   SCR1_XOFS=0x001C;
   SCR2_XOFS=0x0018;
   SCR3_XOFS=0x0014;
   SCR4_XOFS=0x0022;

   SCR0_YOFS=0x0008;
   SCR1_YOFS=0x0008;
   SCR2_YOFS=0x0008;
   SCR3_YOFS=0x0008;
   SCR4_YOFS=0x0008;

   // Init tc0006vcu emulation
   // ------------------------

   if(!(tc0006vcu.GFX_FG = AllocateMem(0x4000))) return;

   tc0006vcu.RAM	= RAM+0x20000;
   tc0006vcu.RAM_SCR	= RAM+0x34000;
   tc0006vcu.GFX_BG	= GFX_BG0;
   tc0006vcu.GFX_BG_MASK= GFX_BG0_SOLID;
   tc0006vcu.tile_mask  = 0x1FFF;
// Mapper disabled
   tc0006vcu.pal_ofs	= 0;
   tc0006vcu.bmp_x	= 48;
   tc0006vcu.bmp_y	= 48;
   tc0006vcu.bmp_w	= 320;
   tc0006vcu.bmp_h	= 224;
   tc0006vcu.scr_x[0]	= SCR0_XOFS;
   tc0006vcu.scr_x[1]	= SCR1_XOFS;
   tc0006vcu.scr_x[2]	= SCR2_XOFS;
   tc0006vcu.scr_x[3]	= SCR3_XOFS;
   tc0006vcu.scr_x[4]	= SCR4_XOFS;
   tc0006vcu.scr_y[0]	= SCR0_YOFS;
   tc0006vcu.scr_y[1]	= SCR1_YOFS;
   tc0006vcu.scr_y[2]	= SCR2_YOFS;
   tc0006vcu.scr_y[3]	= SCR3_YOFS;
   tc0006vcu.scr_y[4]	= SCR4_YOFS;

   init_tc0006vcu();

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x10000;
   tc0200obj.RAM_B	= RAM+0x18000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 48;
   tc0200obj.bmp_y	= 48;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
// Mapper disabled
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;
   tc0200obj.cols	= 16;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x40FFFF, NULL, RAM+0x020000);			// SCREEN RAM
   AddReadByte(0x600000, 0x601FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadByte(0x200000, 0x20FFFF, NULL, RAM+0x010000);			// OBJECT RAM
   AddReadByte(0xA00000, 0xA00003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <bad reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM+0x020000);			// SCREEN RAM
   AddReadWord(0x600000, 0x601FFF, NULL, RAM+0x030000);			// COLOR RAM
   AddReadWord(0x200000, 0x20FFFF, NULL, RAM+0x010000);			// OBJECT RAM
   AddReadWord(0x700000, 0x70001F, NULL, RAM+0x032000);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <bad reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM+0x010000);		// OBJECT RAM
   AddWriteByte(0x400000, 0x40DFFF, NULL, RAM+0x020000);		// SCREEN RAM
   AddWriteByte(0x40E000, 0x40FFFF, tc0006vcu_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x600000, 0x601FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteByte(0xA00000, 0xA00003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <bad writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM+0x010000);		// OBJECT RAM
   AddWriteWord(0x400000, 0x40DFFF, NULL, RAM+0x020000);		// SCREEN RAM
   AddWriteWord(0x40E000, 0x40FFFF, tc0006vcu_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x600000, 0x601FFF, NULL, RAM+0x030000);		// COLOR RAM
   AddWriteWord(0x430000, 0x43001F, NULL, RAM+0x034000);		// SCROLL
   AddWriteWord(0x300000, 0x30000F, NULL, RAM+0x034100);		// OBJECT BANK
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <bad writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_footchmp(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   //cpu_interrupt(CPU_68K_0, 6);

   Taito2610_Frame();			// Z80 and YM2610

   IntF3System();

   debug_tc0006vcu();
}


static void draw_football_champ(void)
{
   ClearPaletteMap();

   make_object_bank(RAM+0x034100);

   tc0006vcu_layer_count = 0;

   tc0006vcu_render_layer(0);

   render_tc0200obj_mapped_fchamp(0x00);

   tc0006vcu_render_layer(1);

   render_tc0200obj_mapped_fchamp(0xC0);

   tc0006vcu_render_layer(2);

   render_tc0200obj_mapped_fchamp(0x80);

   tc0006vcu_render_layer(3);

   render_tc0200obj_mapped_fchamp(0x40);

   tc0006vcu_render_fg0();
}
static struct VIDEO_INFO video_footchmp =
{
   draw_football_champ,
   320,
   224,
   48,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_euroch92[] =
{
   { "euro_champ_92", },
   { "euroch92", },
   { "footchmp", },
   { ROMOF("footchmp"), },
   { CLONEOF("footchmp"), },
   { NULL, },
};
CLNE( euroch92, footchmp, "Euro Champ 92", TAITO, 1992, GAME_SPORTS,
	.dsw = dsw_euroch92,
	.long_name_jpn = "ハットトリックヒーロー９３",
	.board = "C80",
);
static struct DIR_INFO dir_hthero[] =
{
   { "hat_trick_hero", },
   { "hthero", },
   { "fchamp", },
   { ROMOF("footchmp"), },
   { CLONEOF("footchmp"), },
   { NULL, },
};
CLNE( hthero, footchmp, "Hat Trick Hero", TAITO, 1990, GAME_SPORTS,
	.dsw = dsw_hthero,
	.board = "C80",
);
static struct DIR_INFO dir_footchmp[] =
{
   { "football_champ", },
   { "fchamp", },
   { "footchmp", },
   { NULL, },
};
GME( footchmp, "Football Champ", TAITO, 1990, GAME_SPORTS,
	.long_name_jpn = "ハットトリックヒーロー",
	.board = "C80",
);

