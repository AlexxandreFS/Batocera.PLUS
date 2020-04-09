#define DRV_DEF_SOUND taito_ym2610_sound
#define DRV_DEF_INPUT input_gigandes
#define DRV_DEF_EXEC execute_gigandes
/******************************************************************************/
/*                                                                            */
/*                   BALLOON BROS (C) 1992 EAST TECHNOLOGY                    */
/*                                                                            */
/*                     GIGANDES (C) 1989 EAST TECHNOLOGY                      */
/*                                                                            */
/*                    SUPERMAN (C) 1988 TAITO CORPORATION                     */
/*                                                                            */
/*              TWIN HAWK / DAISENPU (C) 1989 TAITO CORPORATION               */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "setax1.h"
#include "sasound.h"		// sample support routines
#include "timer.h"


static struct ROM_INFO rom_ballbros[] =
{
   {            "0", 0x00020000, 0x1cc584e5, 0, 0, 0, },
   {            "1", 0x00020000, 0x8196d624, 0, 0, 0, },
   {            "2", 0x00020000, 0xbb441717, 0, 0, 0, },
   {            "3", 0x00020000, 0xec3e0537, 0, 0, 0, },
   {          "10a", 0x00020000, 0x4af0e858, 0, 0, 0, },
   {           "5a", 0x00020000, 0x0b983a69, 0, 0, 0, },
   {           "8d", 0x00010000, 0xd1c515af, 0, 0, 0, },
   {      "east-10", 0x00080000, 0xca0ac419, 0, 0, 0, },
   {      "east-11", 0x00080000, 0x92111f96, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_gigandes[] =
{
   INP0( COIN1, 0x020005, 0x01 ),
   INP0( COIN2, 0x020005, 0x02 ),
   INP0( TILT, 0x020005, 0x08 ),
   INP0( SERVICE, 0x020005, 0x04 ),

   INP0( P1_START, 0x020001, 0x80 ),
   INP0( P1_UP, 0x020001, 0x01 ),
   INP0( P1_DOWN, 0x020001, 0x02 ),
   INP0( P1_LEFT, 0x020001, 0x04 ),
   INP0( P1_RIGHT, 0x020001, 0x08 ),
   INP0( P1_B1, 0x020001, 0x10 ),
   INP0( P1_B2, 0x020001, 0x20 ),
   INP0( P1_B3, 0x020001, 0x40 ),

   INP0( P2_START, 0x020003, 0x80 ),
   INP0( P2_UP, 0x020003, 0x01 ),
   INP0( P2_DOWN, 0x020003, 0x02 ),
   INP0( P2_LEFT, 0x020003, 0x04 ),
   INP0( P2_RIGHT, 0x020003, 0x08 ),
   INP0( P2_B1, 0x020003, 0x10 ),
   INP0( P2_B2, 0x020003, 0x20 ),
   INP0( P2_B3, 0x020003, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_balloon_bros_0[] =
{
   { MSG_COIN1,               0x03, 0x04 },
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x02},
   { MSG_COIN2,               0x04, 0x02 },
   { MSG_1COIN_1PLAY,         0x04},
   { MSG_1COIN_2PLAY,         0x00},
   DSW_UNUSED( 0x00, 0x08),
   DSW_UNUSED( 0x00, 0x10),
   { MSG_DIFFICULTY,          0x60, 0x04 },
   { MSG_EASY,                0x60},
   { MSG_NORMAL,              0x40},
   { MSG_HARD,                0x20},
   { MSG_HARDEST,             0x00},
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_balloon_bros_1[] =
{
   DSW_DEMO_SOUND( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_CONTINUE_PLAY( 0x04, 0x00),
   DSW_UNUSED( 0x00, 0x08),
   DSW_UNUSED( 0x00, 0x10),
   { _("Language"),              0x20, 0x02 },
   { _("English"),               0x00},
   { _("Japanese"),              0x20},
   DSW_UNUSED( 0x00, 0x40),
   DSW_SERVICE( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ballbros[] =
{
   { 0x020100, 0xDF, dsw_data_balloon_bros_0 },
   { 0x020102, 0xDE, dsw_data_balloon_bros_1 },
   { 0,        0,    NULL,      },
};





static struct ROM_INFO rom_gigandes[] =
{
   {            "1", 0x00020000, 0x290c50e0, 0, 0, 0, },
   {            "3", 0x00020000, 0x9cef82af, 0, 0, 0, },
   {            "2", 0x00020000, 0xdd94b4d0, 0, 0, 0, },
   {            "4", 0x00020000, 0xa647310a, 0, 0, 0, },
   {            "5", 0x00010000, 0xb24ab5f4, 0, 0, 0, },
   {            "6", 0x00080000, 0x75eece28, 0, 0, 0, },
   {            "7", 0x00080000, 0xb179a76a, 0, 0, 0, },
   {            "9", 0x00080000, 0x5c5e6898, 0, 0, 0, },
   {            "8", 0x00080000, 0x52db30e9, 0, 0, 0, },
   {           "11", 0x00080000, 0x92111f96, 0, 0, 0, },
   {           "10", 0x00080000, 0xca0ac419, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_gigandes_0[] =
{
   { MSG_COIN1,               0x03, 0x04 },
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x02},
   { MSG_COIN2,               0x0c, 0x04 },
   { MSG_2COIN_1PLAY,         0x04},
   { MSG_1COIN_1PLAY,         0x0c},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x08},
   { _("Demo Game"),             0x10, 0x02 },
   { MSG_YES,                 0x10},
   { MSG_NO,                  0x00},
   { MSG_DIFFICULTY,          0x60, 0x04 },
   { MSG_EASY,                0x60},
   { MSG_NORMAL,              0x40},
   { MSG_HARD,                0x20},
   { MSG_HARDEST,             0x00},
   { _("Invincibility"),         0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_gigandes_1[] =
{
   DSW_DEMO_SOUND( 0x00, 0x01),
   DSW_SCREEN( 0x00, 0x02),
   DSW_CONTINUE_PLAY( 0x00, 0x04),
   { MSG_LIVES,               0x18, 0x04 },
   { "3",                     0x18},
   { "4",                     0x10},
   { "5",                     0x08},
   { "6",                     0x00},
   DSW_CABINET( 0x00, 0x20),
   { _("Language"),              0x40, 0x02 },
   { _("English"),               0x00},
   { _("Japanese"),              0x40},
   DSW_SERVICE( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_gigandes[] =
{
   { 0x020100, 0xDF, dsw_data_gigandes_0 },
   { 0x020102, 0x98, dsw_data_gigandes_1 },
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_superman[] =
{
   {   "a10_09.bin", 0x00020000, 0x640f1d58, 0, 0, 0, },
   {   "a08_08.bin", 0x00020000, 0x79fc028e, 0, 0, 0, },
   {   "a05_07.bin", 0x00020000, 0xfddb9953, 0, 0, 0, },
   {   "a03_13.bin", 0x00020000, 0x9f446a44, 0, 0, 0, },
   {   "d18_10.bin", 0x00010000, 0x6efe79e8, 0, 0, 0, },
   {   "e18_01.bin", 0x00080000, 0x3cf99786, 0, 0, 0, },
   {   "f01_14.bin", 0x00080000, 0x89368c3e, 0, 0, 0, },
   {   "h01_15.bin", 0x00080000, 0x910cc4f9, 0, 0, 0, },
   {   "j01_16.bin", 0x00080000, 0x3622ed2f, 0, 0, 0, },
   {   "k01_17.bin", 0x00080000, 0xc34f27e0, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

#define COINAGE_SUPERMAN \
   { MSG_COIN1,               0x30, 0x04 },\
   { MSG_4COIN_1PLAY,         0x00, 0x00 },\
   { MSG_3COIN_1PLAY,         0x10, 0x00 },\
   { MSG_2COIN_1PLAY,         0x20, 0x00 },\
   { MSG_1COIN_1PLAY,         0x30, 0x00 },\
   { MSG_COIN2,               0xC0, 0x04 },\
   { MSG_1COIN_2PLAY,         0xC0, 0x00 },\
   { MSG_1COIN_3PLAY,         0x80, 0x00 },\
   { MSG_1COIN_4PLAY,         0x40, 0x00 },\
   { MSG_1COIN_6PLAY,         0x00, 0x00 },

static struct DSW_DATA dsw_data_superman_0[] =
{
   DSW_UNUSED( 0x00, 0x01),
   DSW_SCREEN( 0x02, 0x00),
   DSW_SERVICE( 0x00, 0x04),
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   COINAGE_SUPERMAN
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_superman_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_UNKNOWN,             0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x20},
   { "3",                     0x30},
   { "4",                     0x10},
   { "5",                     0x00},
   DSW_UNUSED( 0x00, 0x40),
   DSW_UNUSED( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_superman[] =
{
   { 0x040100, 0xFF, dsw_data_superman_0 },
   { 0x040102, 0xFF, dsw_data_superman_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_superman_0[] =
{
   { "Taito Worldwide",       0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_superman[] =
{
   { 0x07FFFF, 0x02, romsw_data_superman_0 },
   { 0,        0,    NULL },
};



static struct ROM_INFO rom_twinhawk[] =
{
   {   "b87-11.bin", 0x00020000, 0xfc84a399, 0, 0, 0, },
   {   "b87-10.bin", 0x00020000, 0x17181706, 0, 0, 0, },
   {       "b87-07", 0x00008000, 0xe2e0efa0, 0, 0, 0, },
   {       "b87-02", 0x00080000, 0x89ad43a0, 0, 0, 0, },
   {       "b87-01", 0x00080000, 0x81e82ae1, 0, 0, 0, },
   {       "b87-04", 0x00080000, 0x958434b6, 0, 0, 0, },
   {       "b87-03", 0x00080000, 0xce155ae0, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

#define DSW_A_TWINHAWK \
   { MSG_CABINET,             0x01, 0x02 },\
   { MSG_UPRIGHT,             0x00, 0x00 },\
   { MSG_TABLE,               0x01, 0x00 },\
   { MSG_SCREEN,              0x02, 0x02 },\
   { MSG_NORMAL,              0x02, 0x00 },\
   { MSG_INVERT,              0x00, 0x00 },\
   { MSG_SERVICE,             0x04, 0x02 },\
   { MSG_OFF,                 0x04, 0x00 },\
   { MSG_ON,                  0x00, 0x00 },\
   { MSG_DEMO_SOUND,          0x08, 0x02 },\
   { MSG_OFF,                 0x00, 0x00 },\
   { MSG_ON,                  0x08, 0x00 },

static struct DSW_DATA dsw_data_twin_hawk_0[] =
{
   DSW_A_TWINHAWK
   COINAGE_SUPERMAN
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_twin_hawk_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x02},
   { MSG_NORMAL,              0x03},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0C, 0x04 },
   { _("50k and every 150k"),    0x0C},
   { _("70k and every 200k"),    0x08},
   { _("100k only"),             0x04},
   { _("None"),                  0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x00},
   { "3",                     0x30},
   { "4",                     0x10},
   { "5",                     0x20},
   DSW_UNUSED( 0x00, 0x40),
   DSW_CONTINUE_PLAY( 0x00, 0x80),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_twinhawk[] =
{
   { 0x040100, 0xFE, dsw_data_twin_hawk_0 },
   { 0x040102, 0x7F, dsw_data_twin_hawk_1 },
   { 0,        0,    NULL,      },
};



static struct ROM_INFO rom_daisenpu[] =
{
   {       "b87-01", 0x00080000, 0x81e82ae1, 0, 0, 0, },
   {       "b87-02", 0x00080000, 0x89ad43a0, 0, 0, 0, },
   {       "b87-03", 0x00080000, 0xce155ae0, 0, 0, 0, },
   {       "b87-04", 0x00080000, 0x958434b6, 0, 0, 0, },
   {       "b87-05", 0x00020000, 0x7f15edc7, 0, 0, 0, },
   {       "b87-06", 0x00020000, 0xcf236100, 0, 0, 0, },
   {       "b87-07", 0x00008000, 0xe2e0efa0, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_daisenpu_0[] =
{
   DSW_A_TWINHAWK
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_1COIN_2PLAY,         0x80},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_daisenpu[] =
{
   { 0x040100, 0xFE, dsw_data_daisenpu_0 },
   { 0x040102, 0x7F, dsw_data_twin_hawk_1 },
   { 0,        0,    NULL,      },
};


static UINT32 romset;
static UINT32 tile_mask;

static UINT8 cchip_bank;

static UINT8 balloonb_cchip_rb(UINT32 address)
{
   switch(address & 0xFFF){
      case 0x803:
         return 0x01;
      break;
      case 0xC01:
         return cchip_bank;
      break;
      default:
         return RAM[0x20000+(address&0x7FF)];
      break;
   }
}

static UINT16 balloonb_cchip_rw(UINT32 address)
{
   return balloonb_cchip_rb( address+1 );
}

static void balloonb_cchip_wb(UINT32 address, UINT8 data)
{
   switch(address & 0xFFF){
      case 0x007:				// cchip[0][0x007]: COIN LEDS - SUPERMAN
         RAM[0x20000+(address&0x7FF)] = data;
         switch_led(0,((data>>0)&1)^1);		// Coin A [Coin Inserted]
         switch_led(1,((data>>1)&1)^1);		// Coin B [Coin Inserted]
         switch_led(2,((data>>2)&1)^1);		// Coin A [Ready for coins]
       //switch_led(3,((data>>3)&1)^1);		// Coin B [Ready for coins]
      break;
      case 0x009:				// cchip[0][0x009]: COIN LEDS - BALLOON BROS
         RAM[0x20000+(address&0x7FF)] = data;
         switch_led(0,(data>>0)&1);		// Coin A [Coin Inserted]
         switch_led(1,(data>>1)&1);		// Coin B [Coin Inserted]
         switch_led(2,(data>>2)&1);		// Coin A [Ready for coins]
       //switch_led(3,(data>>3)&1);		// Coin B [Ready for coins]
      break;
      case 0x803:
      break;
      case 0xC01:
         cchip_bank = data & 7;
      break;
      default:
      break;
   }
}

static void balloonb_cchip_ww(UINT32 address, UINT16 data)
{
   balloonb_cchip_wb( address+1, (UINT8) (data&0xFF) );
}

static UINT8 split_dsw_rb(UINT32 address)
{
   switch( (address >> 1) & 3 ){

      case 0:
         return (get_dsw(0) >> 0) & 0x0F;

      case 1:
         return (get_dsw(0) >> 4) & 0x0F;

      case 2:
         return (get_dsw(1) >> 0) & 0x0F;

      case 3:
         return (get_dsw(1) >> 4) & 0x0F;

      default:
         return 0;

   }
}

static UINT16 split_dsw_rw(UINT32 address)
{
   return (UINT16) split_dsw_rb(address);
}

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static void DecodeXSystemGfx(int tb, int tc, int n)
{
  if (n==0) {
    GFX_SPR[tb+0] = (((tc&0x80)>>7)<<n);
    GFX_SPR[tb+1] = (((tc&0x40)>>6)<<n);
    GFX_SPR[tb+2] = (((tc&0x20)>>5)<<n);
    GFX_SPR[tb+3] = (((tc&0x10)>>4)<<n);
    GFX_SPR[tb+4] = (((tc&0x08)>>3)<<n);
    GFX_SPR[tb+5] = (((tc&0x04)>>2)<<n);
    GFX_SPR[tb+6] = (((tc&0x02)>>1)<<n);
    GFX_SPR[tb+7] = (((tc&0x01)>>0)<<n);
  }
  else {
    GFX_SPR[tb+0] |= (((tc&0x80)>>7)<<n);
    GFX_SPR[tb+1] |= (((tc&0x40)>>6)<<n);
    GFX_SPR[tb+2] |= (((tc&0x20)>>5)<<n);
    GFX_SPR[tb+3] |= (((tc&0x10)>>4)<<n);
    GFX_SPR[tb+4] |= (((tc&0x08)>>3)<<n);
    GFX_SPR[tb+5] |= (((tc&0x04)>>2)<<n);
    GFX_SPR[tb+6] |= (((tc&0x02)>>1)<<n);
    GFX_SPR[tb+7] |= (((tc&0x01)>>0)<<n);
  }
}

static void MemoryMap_68000(void)
{
   if ((romset==0) || (romset==2))	// Balloon Bros, Twin Hawk / Daisenpu
     AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);		// 68000 ROM
   else					// Superman, Gigandes
     AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);		// 68000 ROM
   AddReadByte(0xF00000, 0xF03FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xE00000, 0xE03FFF, NULL, RAM+0x00C000);			// VIDEO RAM
   AddReadByte(0xD00000, 0xD00FFF, NULL, RAM+0x016000);			// VIDEO RAM2
   AddReadByte(0xB00000, 0xB003FF, NULL, RAM+0x015000);			// COLOUR RAM
   AddReadByte(0x800000, 0x800003, tc0140syt_read_main_68k, NULL);	// tc0140syt
   AddReadByte(0x900000, 0x900FFF, balloonb_cchip_rb, NULL);		// c-chip
   AddReadByte(0x500000, 0x50000F, split_dsw_rb, NULL);			// DSW
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   if ((romset==0) || (romset==2))	// Balloon Bros, Twin Hawk / Daisenpu
     AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);		// 68000 ROM
   else					// Superman, Gigandes
     AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);		// 68000 ROM
   AddReadWord(0xF00000, 0xF03FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xE00000, 0xE03FFF, NULL, RAM+0x00C000);			// VIDEO RAM
   AddReadWord(0xD00000, 0xD00FFF, NULL, RAM+0x016000);			// VIDEO RAM2
   AddReadWord(0xB00000, 0xB003FF, NULL, RAM+0x015000);			// COLOUR RAM
   AddReadWord(0x900000, 0x900FFF, balloonb_cchip_rw, NULL);		// c-chip
   AddReadWord(0x500000, 0x50000F, split_dsw_rw, NULL);			// DSW
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xF00000, 0xF03FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xE00000, 0xE03FFF, NULL, RAM+0x00C000);		// VIDEO RAM
   AddWriteByte(0xD00000, 0xD00FFF, NULL, RAM+0x016000);		// VIDEO RAM2
   AddWriteByte(0xB00000, 0xB003FF, NULL, RAM+0x015000);		// COLOUR RAM
   AddWriteByte(0x800000, 0x800003, tc0140syt_write_main_68k, NULL);	// tc0140syt
   AddWriteByte(0x900000, 0x900FFF, balloonb_cchip_wb, NULL);		// c-chip
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xF00000, 0xF03FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xE00000, 0xE03FFF, NULL, RAM+0x00C000);		// VIDEO RAM
   AddWriteWord(0xD00000, 0xD00FFF, NULL, RAM+0x016000);		// VIDEO RAM2
   AddWriteWord(0xB00000, 0xB003FF, NULL, RAM+0x015000);		// COLOUR RAM
   AddWriteWord(0x900000, 0x900FFF, balloonb_cchip_ww, NULL);		// c-chip
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);
}

static void load_ballbros(void)
{
   int ta,tb,tc;

   romset = 0;

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x40000))) return;
   if(!(GFX_SPR=AllocateMem(0x100000))) return;

   if(!load_rom("3", RAM, 0x20000)) return;		// 16x16 SPRITES
   tb=0;
   for(ta=0;ta<0x20000;ta++){
      tc=RAM[ta];
      DecodeXSystemGfx(tb,tc,0);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("2", RAM, 0x20000)) return;		// 16x16 SPRITES
   tb=0;
   for(ta=0;ta<0x20000;ta++){
      tc=RAM[ta];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("1", RAM, 0x20000)) return;		// 16x16 SPRITES
   tb=0;
   for(ta=0;ta<0x20000;ta++){
      tc=RAM[ta];
      DecodeXSystemGfx(tb,tc,2);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("0", RAM, 0x20000)) return;		// 16x16 SPRITES
   tb=0;
   for(ta=0;ta<0x20000;ta++){
      tc=RAM[ta];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x1000);

   tile_mask = 0x0FFF;

   if(!load_rom("10a", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("5a", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("8d", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("east-11",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("east-10",PCMROM+0x80000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM+0x00000, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x006E, 0x0068, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   // Speed Hack

   WriteLong68k(&ROM[0x004A6],0x13FC0000);
   WriteLong68k(&ROM[0x004AA],0x00AA0000);

   // Starscream problem

   // Mistery here : there is a 41b9 opcode at this address.
   // It does not seem to correspond to any valid instruction...
   // It seems to be fixed in Starscream 0.26d !

   // WriteLong68k(&ROM[0x00E9C],0x4E714E71);

   InitPaletteMap(RAM+0x15000, 0x20, 0x10, 0x8000);

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);

   // Init seta_x1 emulation
   // ----------------------

   seta_x1.RAM_A	= RAM+0x0C000;
   seta_x1.RAM_B	= RAM+0x16000;
   seta_x1.GFX		= GFX_SPR;
   seta_x1.MASK		= GFX_SPR_SOLID;
   seta_x1.bmp_x	= 32;
   seta_x1.bmp_y	= 32;
   seta_x1.bmp_w	= 384;
   seta_x1.bmp_h	= 240;
   seta_x1.tile_mask	= 0x0FFF;
   seta_x1.scr_x	= 16;
   seta_x1.scr_y	= 0;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   MemoryMap_68000();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void clear_balloon_bros(void)
{
   RemoveTaitoYM2610();
}

static void load_gigandes(void)
{
   int ta,tb,tc;

   romset = 3;

   RAMSize=0x44000+0x10000;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX_SPR=AllocateMem(0x400000))) return;

   if(!load_rom("6", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,0);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("9", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,2);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("7", ROM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,0);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("8", ROM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,2);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   tile_mask = 0x3FFF;

   if(!load_rom("1", RAM+0x00000, 0x20000)) return;
   if(!load_rom("2", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("3", RAM+0x00000, 0x20000)) return;
   if(!load_rom("4", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("5", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("11",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("10",PCMROM+0x80000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM+0x00000, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x006E, 0x0068, 0x10000);		// 100% not sure

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   // Speed Hack

   // ...

   InitPaletteMap(RAM+0x15000, 0x20, 0x10, 0x8000);

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);

   // Init seta_x1 emulation
   // ----------------------

   seta_x1.RAM_A	= RAM+0x0C000;
   seta_x1.RAM_B	= RAM+0x16000;
   seta_x1.GFX		= GFX_SPR;
   seta_x1.MASK		= GFX_SPR_SOLID;
   seta_x1.bmp_x	= 32;
   seta_x1.bmp_y	= 32;
   seta_x1.bmp_w	= 384;
   seta_x1.bmp_h	= 240;
   seta_x1.tile_mask	= 0x3FFF;
   seta_x1.scr_x	= 16;
   seta_x1.scr_y	= 0;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   MemoryMap_68000();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_superman(void)
{
   int ta,tb,tc;

   romset = 1;

   RAMSize=0x44000+0x10000;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX_SPR=AllocateMem(0x400000))) return;

   if(!load_rom("f01_14.bin", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,0);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("j01_16.bin", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,2);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("h01_15.bin", ROM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,0);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("k01_17.bin", ROM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,2);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   tile_mask = 0x3FFF;

   if(!load_rom("a10_09.bin", RAM+0x00000, 0x20000)) return;
   if(!load_rom("a08_08.bin", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("a05_07.bin", RAM+0x00000, 0x20000)) return;
   if(!load_rom("a03_13.bin", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("d18_10.bin", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("e18_01.bin",PCMROM,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x02EE, 0x028D, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   // c-chip hacks

   WriteWord68k(&ROM[0x2C1E],0x4E71);		//	nop
   WriteWord68k(&ROM[0x2C28],0x4E71);		//	nop
   WriteWord68k(&ROM[0x2C32],0x4E71);		//	nop

   WriteLong68k(&ROM[0x4268],0x4E714E71);	// 	nop

   // c-chip hack (sound comm)

   WriteLong68k(&ROM[0x2D8A],0x4EF80300);	// 	jmp	$300.w

   WriteLong68k(&ROM[0x0300],0x48E7C000);	// 	movem.l	d0-d1,-(a7)
   WriteWord68k(&ROM[0x0304],0x7000);		//	moveq	#0,d0
   WriteLong68k(&ROM[0x0306],0x322F000C);	//	move.w	12(a7),d1
   WriteLong68k(&ROM[0x030A],0x4EB82DF0);	// 	jsr	$2DF0.w
   WriteLong68k(&ROM[0x030E],0x4CDF0003);	// 	movem.l	(a7)+,d0-d1
   WriteWord68k(&ROM[0x0312],0x4E75);		//	rts

   // Speed Hack

   WriteLong68k(&ROM[0x818],0x13FC0000);	// 	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x81C],0x00AA0000);	// 	(Speed Hack)
   WriteWord68k(&ROM[0x820],0x6100-10);		// 	<Loop>

   InitPaletteMap(RAM+0x15000, 0x20, 0x10, 0x8000);

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);

   // Init seta_x1 emulation
   // ----------------------

   seta_x1.RAM_A	= RAM+0x0C000;
   seta_x1.RAM_B	= RAM+0x16000;
   seta_x1.GFX		= GFX_SPR;
   seta_x1.MASK		= GFX_SPR_SOLID;
   seta_x1.bmp_x	= 32;
   seta_x1.bmp_y	= 32;
   seta_x1.bmp_w	= 384;
   seta_x1.bmp_h	= 240;
   seta_x1.tile_mask	= 0x3FFF;
   seta_x1.scr_x	= 16;
   seta_x1.scr_y	= 0;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   MemoryMap_68000();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_twinhawk(void)
{
   int ta,tb,tc;

   romset = 2;

   RAMSize=0x44000+0x10000;

   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX_SPR=AllocateMem(0x400000))) return;

   if(!load_rom("b87-02", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,0);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("b87-04", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,2);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("b87-01", ROM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,0);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,1);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom("b87-03", ROM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x80000;ta+=2){
      tc=ROM[ta+0];
      DecodeXSystemGfx(tb,tc,2);
      tc=ROM[ta+1];
      DecodeXSystemGfx(tb,tc,3);
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   tile_mask = 0x3FFF;

   if (is_current_game("twinhawk")) {
     if(!load_rom("b87-11.bin", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta]=RAM[ta];
     }
     if(!load_rom("b87-10.bin", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta+1]=RAM[ta];
     }
   }
   else {
     if(!load_rom("b87-06", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta]=RAM[ta];
     }
     if(!load_rom("b87-05", RAM, 0x20000)) return;
     for(ta=0;ta<0x20000;ta++){
        ROM[ta+ta+1]=RAM[ta];
     }
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("b87-07", Z80ROM, 0x8000)) return;	// Z80 SOUND ROM
   memset(Z80ROM+0x8000,0x00,0x8000);

   // fix rom checksum

   Z80ROM[0x007F] = 0x00;
   Z80ROM[0x0080] = 0x00;

   AddTaitoYM2151_xsystem(0x00B3, 0x00B2, 0x8000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   if (is_current_game("twinhawk")) {
     // Speed Hack

     // ...
   }
   else {		// daisenpu
     // fix rom checksum

     WriteWord68k(&ROM[0xC5F8],0x4E71);
     WriteWord68k(&ROM[0xC606],0x4E71);

     // Speed Hack

     WriteLong68k(&ROM[0x8254],0x027CF8FF);
     WriteLong68k(&ROM[0x8258],0x13FC0000);
     WriteLong68k(&ROM[0x825C],0x00AA0000);
     WriteLong68k(&ROM[0x8260],0x4E714E71);

     WriteLong68k(&ROM[0x8276],0x51C8FFE0);
   }

   InitPaletteMap(RAM+0x15000, 0x20, 0x10, 0x8000);

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);

   // Init seta_x1 emulation
   // ----------------------

   seta_x1.RAM_A	= RAM+0x0C000;
   seta_x1.RAM_B	= RAM+0x16000;
   seta_x1.GFX		= GFX_SPR;
   seta_x1.MASK		= GFX_SPR_SOLID;
   seta_x1.bmp_x	= 32;
   seta_x1.bmp_y	= 32;
   seta_x1.bmp_w	= 384;
   seta_x1.bmp_h	= 224;
   seta_x1.tile_mask	= 0x3FFF;
   seta_x1.scr_x	= 0 + 16;
   seta_x1.scr_y	= 0 - 8;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   MemoryMap_68000();

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_gigandes(void)
{
   if(romset==3)
     cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   else
     cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)

   if(romset==1)
      cpu_interrupt(CPU_68K_0, 6);
   else
      cpu_interrupt(CPU_68K_0, 2);

   if(tc0140syt_want_nmi()!=0) {
     cpu_int_nmi(CPU_Z80_0);
   }
   execute_z80_audio_frame();
}

static void draw_x_system(void)
{
   ClearPaletteMap();

   render_seta_x1_68000();
}
static struct VIDEO_INFO video_gigandes =
{
   draw_x_system,
   384,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct VIDEO_INFO video_twinhawk =
{
   draw_x_system,
   384,
   224,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_ballbros[] =
{
   { "balloon_brothers", },
   { "balloon_bros", },
   { "ballbros", },
   { "balloonb", },
   { NULL, },
};
GAME( ballbros, "Balloon Brothers", EAST_TECHNOLOGY, 1992, GAME_PUZZLE,
	.dsw = dsw_ballbros,
	.clear = clear_balloon_bros,
	.video = &video_gigandes,
	.long_name_jpn = "ƒoƒ‹[ƒ“ƒuƒ‰ƒU[ƒY",
);
static struct DIR_INFO dir_daisenpu[] =
{
   { "daisenpu", },
   { ROMOF("twinhawk"), },
   { CLONEOF("twinhawk"), },
   { NULL, },
};
CLONE(daisenpu, twinhawk, "Daisenpu", TAITO, 1989, GAME_SHOOT,
	.dsw = dsw_daisenpu,
	.video = &video_twinhawk,
	.long_name_jpn = "µåù•—",
	.board = "B87",
	.sound = taito_ym2151_sound,
);
GMEI( gigandes, "Gigandes", EAST_TECHNOLOGY, 1989, GAME_SHOOT);
static struct DIR_INFO dir_superman[] =
{
   { "superman", },
   { NULL, },
};
GAME( superman, "Superman", TAITO, 1988, GAME_BEAT | GAME_SHOOT,
	.dsw = dsw_superman,
	.romsw = romsw_superman,
	.video = &video_gigandes,
	.long_name_jpn = "ƒX[ƒp[ƒ}ƒ“",
	.board = "B61",
);
static struct DIR_INFO dir_twinhawk[] =
{
   { "twinhawk", },
   { NULL, },
};
GAME( twinhawk, "Twin Hawk", TAITO, 1989, GAME_SHOOT,
	.dsw = dsw_twinhawk,
	.video = &video_twinhawk,
	.long_name_jpn = "µåù•—",
	.board = "B87",
	.sound = taito_ym2151_sound,
);

