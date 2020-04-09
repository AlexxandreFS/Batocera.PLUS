#define DRV_DEF_SOUND taito_ym2151_sound
/******************************************************************************/
/*                                                                            */
/*              RAINBOW ISLANDS/EXTRA (C) 1988 TAITO CORPORATION              */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc002obj.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "2203intf.h"
#include "dejap.h" // jumping hack in raine.dat


static struct ROM_INFO rom_jumping[] =
{
   {   "ri_m03.rom", 0x00020000, 0x3ebb0fb8, 0, 0, 0, },
   {   "ri_m04.rom", 0x00020000, 0x91625e7f, 0, 0, 0, },
   {     "jb1_cd67", 0x00010000, 0x8527c00e, 0, 0, 0, },
   {      "jb1_f89", 0x00010000, 0x0810d327, 0, 0, 0, },
   {       "jb1_h4", 0x00010000, 0x3fab6b31, 0, 0, 0, },
   {       "jb1_h8", 0x00010000, 0x8c878827, 0, 0, 0, },
   {       "jb1_i4", 0x00010000, 0x443492cf, 0, 0, 0, },
   {       "jb1_i8", 0x00010000, 0xed33bae1, 0, 0, 0, },
   {     "jb2_ic14", 0x00010000, 0x9fdc6c8e, 0, 0, 0, },
   {     "jb2_ic13", 0x00010000, 0x06226492, 0, 0, 0, },
   {     "jb2_ic12", 0x00010000, 0x312700ca, 0, 0, 0, },
   {     "jb2_ic11", 0x00010000, 0xde3b0b88, 0, 0, 0, },
   {     "jb2_ic10", 0x00010000, 0xe61933fb, 0, 0, 0, },
   {      "jb2_ic9", 0x00010000, 0xed031eb2, 0, 0, 0, },
   {      "jb2_ic8", 0x00010000, 0x65b76309, 0, 0, 0, },
   {      "jb2_ic7", 0x00010000, 0x43a94283, 0, 0, 0, },
   {     "jb2_ic78", 0x00010000, 0x925865e1, 0, 0, 0, },
   {     "jb2_ic77", 0x00010000, 0xb09695d1, 0, 0, 0, },
   {     "jb2_ic76", 0x00008000, 0x41937743, 0, 0, 0, },
   {     "jb2_i119", 0x00008000, 0x7e1d58d8, 0, 0, 0, },
   {     "jb2_i120", 0x00010000, 0x7c4e893b, 0, 0, 0, },
   {     "jb2_i121", 0x00010000, 0x93df1e4d, 0, 0, 0, },
   {     "jb2_ic62", 0x00010000, 0x8548db6c, 0, 0, 0, },
   {     "jb2_ic61", 0x00010000, 0x37c5923b, 0, 0, 0, },
   {     "jb2_ic93", 0x00010000, 0xf644eeab, 0, 0, 0, },
   {     "jb2_ic92", 0x00010000, 0x3fbccd33, 0, 0, 0, },
   {     "jb2_ic91", 0x00008000, 0xd886c014, 0, 0, 0, },
   {     "jb2_ic60", 0x00008000, 0x662a2f1e, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_jumping[] =
{
   INP0( COIN1, 0x01B104, 0x01 ),
   INP0( COIN2, 0x01B104, 0x02 ),

   INP0( P1_START, 0x01B104, 0x10 ),
   INP0( P1_LEFT, 0x01B106, 0x80 ),
   INP0( P1_RIGHT, 0x01B106, 0x40 ),
   INP0( P1_B1, 0x01B106, 0x02 ),
   INP0( P1_B2, 0x01B106, 0x04 ),

   INP0( P2_START, 0x01B104, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_jumping_islands_0[] =
{
   { _("Game Style"),            0x01, 0x02 },
   { _("Cocktail"),              0x01},
   { _("Upright"),               0x00},
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

static struct DSW_DATA dsw_data_jumping_islands_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { _("B"),                     0x03},
   { _("C"),                     0x02},
   { _("D"),                     0x01},
   { _("A"),                     0x00},
   { _("Bonus"),                 0x04, 0x02 },
   { _("100k/1000k"),            0x04},
   { _("None"),                  0x00},
   { _("Complete Bonus"),        0x08, 0x02 },
   { _("1Up"),                   0x08},
   { _("None"),                  0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "1",                     0x20},
   { "4",                     0x10},
   { "2",                     0x00},
   { _("Language"),              0x40, 0x02 },
   { _("Japanese"),              0x40},
   { _("English"),               0x00},
   { _("Coin Type"),             0x80, 0x02 },
   { _("Type 1"),                0x80},
   { _("Type 2"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_jumping[] =
{
   { 0x01B100, 0xFF, dsw_data_jumping_islands_0 },
   { 0x01B102, 0xBF, dsw_data_jumping_islands_1 },
   { 0,        0,    NULL,      },
};


static struct YM2203interface ym2203_interface =
{
  2,
  4000000,
  { 0x00ff2040, 0x00ff2040 },
  { 0 },
  { 0 },
  { NULL, NULL },
  { NULL, NULL },
  { NULL, NULL }
};

static struct SOUND_INFO sound_jumping[] =
{
   { SOUND_YM2203,  &ym2203_interface,  },
   { 0,             NULL,               },
};



static struct ROM_INFO rom_rainbow[] =
{
   {   "ri_m01.rom", 0x00080000, 0xb76c9168, 0, 0, 0, },
   {   "ri_m02.rom", 0x00080000, 0x1b87ecf0, 0, 0, 0, },
   {   "ri_m03.rom", 0x00020000, 0x3ebb0fb8, 0, 0, 0, },
   {   "ri_m04.rom", 0x00020000, 0x91625e7f, 0, 0, 0, },
   {       "b22-08", 0x00010000, 0x962fb845, 0, 0, 0, },
   {       "b22-09", 0x00010000, 0xf43efa27, 0, 0, 0, },
   {       "b22-10", 0x00010000, 0x3b013495, 0, 0, 0, },
   {       "b22-11", 0x00010000, 0x80041a3d, 0, 0, 0, },
   {       "b22-12", 0x00010000, 0x67a76dc6, 0, 0, 0, },
   {       "b22-13", 0x00010000, 0x2fda099f, 0, 0, 0, },
   {       "b22-14", 0x00010000, 0x113c1a5b, 0, 0, 0, },
   {      "jb1_f89", 0x00010000, 0x0810d327, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_rainbow[] =
{
   INP1( COIN1, 0x020009, 0x01 ),
   INP1( COIN2, 0x020009, 0x02 ),
   INP0( TILT, 0x02000B, 0x01 ),
   INP0( SERVICE, 0x020007, 0x80 ),

   INP0( P1_START, 0x020007, 0x40 ),
   INP0( P1_LEFT, 0x02000B, 0x10 ),
   INP0( P1_RIGHT, 0x02000B, 0x20 ),
   INP0( P1_B1, 0x02000B, 0x40 ),
   INP0( P1_B2, 0x02000B, 0x80 ),

   INP0( P2_START, 0x020007, 0x20 ),
   INP0( P2_LEFT, 0x02000D, 0x08 ),
   INP0( P2_RIGHT, 0x02000D, 0x10 ),
   INP0( P2_B1, 0x02000D, 0x20 ),
   INP0( P2_B2, 0x02000D, 0x40 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_rainbow_islands_0[] =
{
   { _("Game Style"),            0x01, 0x02 },
   { _("Cocktail"),              0x01},
   { _("Upright"),               0x00},
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

static struct DSW_DATA dsw_data_rainbow_islands_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { _("B"),                     0x03},
   { _("C"),                     0x02},
   { _("D"),                     0x01},
   { _("A"),                     0x00},
   { _("Bonus"),                 0x04, 0x02 },
   { _("100k/1000k"),            0x04},
   { _("None"),                  0x00},
   { _("Complete Bonus"),        0x08, 0x02 },
   { _("1Up"),                   0x08},
   { _("None"),                  0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "1",                     0x20},
   { "4",                     0x10},
   { "2",                     0x00},
   { _("Language"),              0x40, 0x02 },
   { _("Japanese"),              0x40},
   { _("English"),               0x00},
   { _("Coin Type"),             0x80, 0x02 },
   { _("Type 1"),                0x80},
   { _("Type 2"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_rainbow[] =
{
   { 0x01B012, 0xFF, dsw_data_rainbow_islands_0 },
   { 0x01B014, 0xBF, dsw_data_rainbow_islands_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_rainbow_islands_0[] =
{
   { "Taito America",             0x01 },
   { "Taito Japan",               0x02 },
   { "Taito America (Romstar)",   0x03 },
   { "Taito Worldwide (Phoenix)", 0x04 },
   { "Taito Worldwide",           0x05 },
   { NULL,                        0    },
};

static struct ROMSW_INFO romsw_rainbow[] =
{
   { 0x02FFFF, 0x00, romsw_data_rainbow_islands_0 },
   { 0,        0,    NULL },
};



static struct ROM_INFO rom_rainbowa[] =
{
   {   "ri_m01.rom", 0x00080000, 0xb76c9168, 0, 0, 0, },
   {   "ri_m02.rom", 0x00080000, 0x1b87ecf0, 0, 0, 0, },
   {   "ri_m03.rom", 0x00020000, 0x3ebb0fb8, 0, 0, 0, },
   {   "ri_m04.rom", 0x00020000, 0x91625e7f, 0, 0, 0, },
   {     "b22_08-1", 0x00010000, 0x15d6e17a, 0, 0, 0, },
   {     "b22_09-1", 0x00010000, 0x454e66bc, 0, 0, 0, },
   {     "b22_10-1", 0x00010000, 0xe34a50ca, 0, 0, 0, },
   {     "b22_11-1", 0x00010000, 0x6a31a093, 0, 0, 0, },
   {       "b22-12", 0x00010000, 0x67a76dc6, 0, 0, 0, },
   {       "b22-13", 0x00010000, 0x2fda099f, 0, 0, 0, },
   {       "b22-14", 0x00010000, 0x113c1a5b, 0, 0, 0, },
   {      "jb1_f89", 0x00010000, 0x0810d327, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};



static struct ROM_INFO rom_rainbowe[] =
{
   {   "ri_m01.rom", 0x00080000, 0xb76c9168, 0, 0, 0, },
   {   "ri_m02.rom", 0x00080000, 0x1b87ecf0, 0, 0, 0, },
   {   "ri_m03.rom", 0x00020000, 0x3ebb0fb8, 0, 0, 0, },
   {   "ri_m04.rom", 0x00020000, 0x91625e7f, 0, 0, 0, },
   {       "b22-14", 0x00010000, 0x113c1a5b, 0, 0, 0, },
   {       "b22-13", 0x00010000, 0x2fda099f, 0, 0, 0, },
   {       "b22-12", 0x00010000, 0x67a76dc6, 0, 0, 0, },
   {    "ri_04.rom", 0x00010000, 0x4caa53bd, 0, 0, 0, },
   {    "ri_03.rom", 0x00010000, 0x4a4cb785, 0, 0, 0, },
   {    "ri_02.rom", 0x00010000, 0x4dead71f, 0, 0, 0, },
   {    "ri_01.rom", 0x00010000, 0x50690880, 0, 0, 0, },
   {      "jb1_f89", 0x00010000, 0x0810d327, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


#if 0
static mapper_direct *col_mapper[3] =
{
   &Map_15bit_xBGR,		// Original
   &Map_15bit_xBGR,		// Extra
   //&Map_12bit_xBGR_Rev,		// Bootleg
};
#endif

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_OBJECT;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static int romset;      // 0=ORIGINAL; 1=EXTRA; 2=JUMPING
static int subset;

static UINT16 JumpingRead_b800(UINT16 offset);

static void Jumpingsound_w(UINT32 offset,UINT8 data);

static UINT8 *CBANK[8];
static int CChip_Bank=0;

static int CChip_ID=0x01;

static int CChipReadB(UINT32 address)
{
   int i;

   i=address&0x0FFF;

   switch(i){
      case 0x803:
         return(CChip_ID);
      break;
      case 0xC01:
         return(CChip_Bank);
      break;
      default:
#ifdef RAINE_DEBUG
	if(i>0x20){
	  print_debug("CCRB[%02x][%03x](%02x)\n",CChip_Bank,i,CBANK[CChip_Bank][i]);
	  print_ingame(60,"CCRB[%02x][%03x](%02x)",CChip_Bank,i,CBANK[CChip_Bank][i]);
	}
#endif
         return(CBANK[CChip_Bank][i]);
      break;
   }
}

static int CChipReadW(UINT32 address)
{
   return(CChipReadB(address+1));
}

static void CChipWriteB(UINT32 address, int data)
{
   int i;

   i=address&0x0FFF;

   switch(i){
      case 0x11:                                // cchip[0][0x011]: COIN LEDS
         CBANK[CChip_Bank][i]=data;
         switch_led(0,(data>>4)&1);             // Coin A [Coin Inserted]
         switch_led(1,(data>>5)&1);             // Coin B [Coin Inserted]
         switch_led(2,((data>>6)&1)^1);         // Coin A [Ready for coins]
         //switch_led(3,((data>>7)&1)^1);       // Coin B [Ready for coins]
      break;
      case 0x803:
      break;
      case 0xC01:
         CChip_Bank=data&7;
      break;
      case 0x283:
         CBANK[0][i]=data;
      break;
      case 0x201:
      switch(CBANK[0][0x283]){
         case 0x00: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x00; CBANK[1][0x28b]=0x00; break;
         case 0x01: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x03; CBANK[1][0x28b]=0x60; break;
         case 0x02: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x07; CBANK[1][0x28b]=0x98; break;
         case 0x03: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x0C; CBANK[1][0x28b]=0xA8; break;

         case 0x04: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x11; CBANK[1][0x28b]=0xB8; break;
         case 0x05: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x15; CBANK[1][0x28b]=0xF0; break;
         case 0x06: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x1B; CBANK[1][0x28b]=0x00; break;
         case 0x07: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x21; CBANK[1][0x28b]=0xC0; break;

         case 0x08: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x25; CBANK[1][0x28b]=0xB8; break;
         case 0x09: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x28; CBANK[1][0x28b]=0xF0; break;
         case 0x0A: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x2C; CBANK[1][0x28b]=0x00; break;
         case 0x0B: CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x30; CBANK[1][0x28b]=0xC0; break;

         default:   CBANK[1][0x285]=0x00; CBANK[1][0x287]=0x03; CBANK[1][0x289]=0x40; CBANK[1][0x28b]=0x00; break;
      }
      switch(CBANK[0][0x283]){
         case 0x00: CBANK[1][0x005]=0x02; CBANK[1][0x003]=0xDC; break;
         case 0x01: CBANK[1][0x005]=0x03; CBANK[1][0x003]=0xB4; break;
         case 0x02: CBANK[1][0x005]=0x04; CBANK[1][0x003]=0x44; break;
         case 0x03: CBANK[1][0x005]=0x04; CBANK[1][0x003]=0xFC; break;

         case 0x04: CBANK[1][0x005]=0x03; CBANK[1][0x003]=0x7C; break;
         case 0x05: CBANK[1][0x005]=0x04; CBANK[1][0x003]=0x8C; break;
         case 0x06: CBANK[1][0x005]=0x06; CBANK[1][0x003]=0x3C; break;
         case 0x07: CBANK[1][0x005]=0x03; CBANK[1][0x003]=0x74; break;

         default:   CBANK[1][0x005]=0x02; CBANK[1][0x003]=0xDC; break;
      }
      CBANK[1][0x201]=0xFF;
      break;
      default:
      break;
   }
}

static void CChipWriteW(UINT32 address, int data)
{
   CChipWriteB(address+1,data&0xFF);
}

/*

0 - Insect
1 - Combat
2 - Monster
3 - Toy
4 - Doh
5 - Robot
6 - Dragon
7 - Magical
8 - Darius
9 - Bubble

*/

static UINT8 rmap[40] =
{
   (8*4)+0,(8*4)+1,(8*4)+2,(8*4)+3,
   (7*4)+0,(7*4)+1,(7*4)+2,(7*4)+3,
   (6*4)+0,(6*4)+1,(6*4)+2,(6*4)+3,
   (5*4)+0,(5*4)+1,(5*4)+2,(5*4)+3,
   (4*4)+0,(4*4)+1,(4*4)+2,(4*4)+3,
   (3*4)+0,(3*4)+1,(3*4)+2,(3*4)+3,
   (2*4)+0,(2*4)+1,(2*4)+2,(2*4)+3,
   (1*4)+0,(1*4)+1,(1*4)+2,(1*4)+3,
   (0*4)+0,(0*4)+1,(0*4)+2,(0*4)+3,
   (9*4)+0,(9*4)+1,(9*4)+2,(9*4)+3,
};

static UINT8 rmap_mask[16] =
{
   0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0
};

static void load_rainbow(void)
{
   int ta,tb,tc;
   UINT8 *TMP;
   if (is_current_game("rainbow")) {
       romset=0;
       subset=0;
   } else if (is_current_game("rainbowa")) {
       romset=0;
       subset=1;
   } else if (is_current_game("rainbowe"))
       romset=1;
   else if (is_current_game("jumping"))
       romset = 2;

// 464 bytes, extracted with hexcat
UINT8 jumping_hack[] =
{
  0x23,0xfc,0x00,0x08,0x00,0x00,0x00,0xc0,0xff,0xf0,0x4e,0x75,0x48,0xe7,
  0x08,0x18,0x47,0xf9,0x00,0x80,0x02,0x91,0x61,0x00,0x01,0xa4,0x4a,0x04,
  0x4c,0xdf,0x18,0x10,0x4e,0x75,0x48,0xe7,0x08,0x18,0x47,0xf9,0x00,0x80,
  0x02,0x85,0x61,0x00,0x01,0x8e,0x10,0x04,0x4c,0xdf,0x18,0x10,0x4e,0x75,
  0x48,0xe7,0x08,0x18,0x47,0xf9,0x00,0x80,0x02,0x87,0x61,0x00,0x01,0x78,
  0x12,0x04,0x4c,0xdf,0x18,0x10,0x4e,0x75,0x48,0xe7,0x08,0x18,0x47,0xf9,
  0x00,0x80,0x02,0x89,0x60,0xe8,0x48,0xe7,0x08,0x18,0x47,0xf9,0x00,0x80,
  0x02,0x8b,0x61,0x00,0x01,0x56,0x14,0x04,0x4c,0xdf,0x18,0x10,0x4e,0x75,
  0x48,0xe7,0x08,0x18,0x47,0xf9,0x00,0x80,0x02,0x91,0x60,0x9a,0x48,0xe7,
  0x08,0x18,0x47,0xf9,0x00,0x80,0x00,0x03,0x60,0xa4,0x48,0xe7,0x08,0x18,
  0x47,0xf9,0x00,0x80,0x00,0x05,0x60,0xae,0x48,0xe7,0x08,0x18,0x47,0xf9,
  0x00,0x80,0x00,0x03,0x60,0x8c,0x48,0xe7,0x08,0x18,0x47,0xf9,0x00,0x80,
  0x00,0x05,0x60,0x96,0x23,0xfc,0x00,0x08,0x92,0xa0,0x00,0xc0,0xff,0xf0,
  0x4e,0x75,0x42,0x40,0x48,0xe7,0x08,0x18,0x47,0xf0,0x10,0x00,0x60,0x00,
  0xff,0x68,0x42,0x42,0x48,0xe7,0x08,0x18,0x47,0xf1,0x10,0x00,0x60,0x92,
  0x42,0x41,0x48,0xe7,0x08,0x18,0x47,0xf0,0x00,0x00,0x60,0x00,0xff,0x64,
  0x42,0x41,0x48,0xe7,0x08,0x18,0x47,0xf0,0x00,0x02,0x60,0x00,0xff,0x56,
  0x48,0xe7,0x08,0x18,0x47,0xd1,0x61,0x00,0x00,0xc6,0x10,0x04,0x4c,0xdf,
  0x18,0x10,0x43,0xe9,0x00,0x01,0x06,0x40,0x11,0x83,0x4e,0x75,0x48,0xe7,
  0x08,0x18,0x47,0xe8,0x00,0x01,0x61,0x00,0x00,0xaa,0x10,0x04,0x4c,0xdf,
  0x18,0x10,0x41,0xe8,0x00,0x02,0x12,0x00,0x02,0x00,0x00,0x0f,0x4e,0x75,
  0xe5,0x08,0x48,0xe7,0x08,0x18,0x47,0xf2,0x00,0x01,0x60,0x00,0xfe,0xfa,
  0xe5,0x48,0x48,0xe7,0x08,0x18,0x47,0xf0,0x00,0x01,0x60,0x00,0xfe,0xec,
  0x48,0xe7,0x08,0x18,0x47,0xe9,0x00,0x01,0x61,0x00,0x00,0x70,0x14,0x04,
  0x4c,0xdf,0x18,0x10,0x02,0x02,0x00,0x03,0x4e,0x75,0x48,0xe7,0x08,0x18,
  0x47,0xe9,0x00,0x03,0x61,0x00,0x00,0x58,0x14,0x04,0xe1,0x4a,0x47,0xe9,
  0x00,0x01,0x61,0x00,0x00,0x4c,0x14,0x04,0x48,0x42,0x47,0xe9,0x00,0x07,
  0x61,0x00,0x00,0x40,0x16,0x04,0xe1,0x4b,0x47,0xe9,0x00,0x05,0x16,0x04,
  0x60,0x00,0xfe,0xe0,0x48,0xe7,0x08,0x18,0x47,0xe9,0x00,0x03,0x61,0x00,
  0x00,0x26,0x10,0x04,0xe1,0x48,0x47,0xe9,0x00,0x01,0x60,0x00,0xfe,0x8a,
  0x48,0xe7,0x08,0x18,0x47,0xe8,0x00,0x03,0x61,0x00,0x00,0x0e,0x10,0x04,
  0xe1,0x48,0x47,0xe8,0x00,0x01,0x60,0x00,0xfe,0x88,0x4e,0xf9,0x00,0x07,
  0xff,0x10,0x5b,0x4a,0x33,0x64,0x21,0x5d,0x2f,0x52,0x61,0x69,0x6e,0x65,
  0x21,0x00 };

// 94 bytes extracted with hexcat
UINT8 jump1630_hack[] =
{
  0x2f,0x00,0x28,0x79,0x00,0xc0,0xff,0xf0,0x42,0x84,0x18,0x39,0x00,0x10,
  0xd0,0x32,0xe5,0x4c,0x49,0xf4,0x48,0x00,0x42,0x84,0x38,0x2d,0x10,0x48,
  0x4a,0x2d,0x11,0xc4,0x67,0x04,0x38,0x2d,0x11,0xc6,0xeb,0x4c,0x49,0xf4,
  0x48,0x00,0x42,0x84,0x42,0x80,0x09,0x0c,0x00,0x05,0x01,0x0c,0x00,0x01,
  0x98,0x40,0x67,0x1e,0xe3,0x4c,0xb8,0x4b,0x65,0x18,0x67,0x16,0x42,0x84,
  0x38,0x0b,0xe3,0x88,0xd8,0x80,0x49,0xf9,0x00,0x08,0x00,0x00,0x18,0x34,
  0x48,0x00,0x20,0x1f,0x4e,0x75,0x42,0x44,0x60,
  0xf8 };

   RAMSize=0x34000;

   if(!(ROM=AllocateMem(0xA0000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;      // $1B004
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_SPR      = GFX+0x000000;
   GFX_BG0      = GFX+0x140000;

   CBANK[0]=RAM+0x20000;
   CBANK[1]=RAM+0x20800;
   CBANK[2]=RAM+0x21000;
   CBANK[3]=RAM+0x21800;
   CBANK[4]=RAM+0x22000;
   CBANK[5]=RAM+0x22800;
   CBANK[6]=RAM+0x23000;
   CBANK[7]=RAM+0x23800;

   if(romset==2){       // Bootleg

      Z80ROM=RAM+0x24000;
      if(!load_rom("jb1_cd67", Z80ROM, 0x10000)) return;               // Z80 SOUND ROM

      Z80ROM[0x186]=0xC3;       // JP 0068h
      Z80ROM[0x187]=0x68;       //
      Z80ROM[0x188]=0x00;       //

      Z80ROM[0x068]=0xF3;       // DI
      Z80ROM[0x069]=0xCD;       // CALL 02B6h
      Z80ROM[0x06A]=0xB6;       //
      Z80ROM[0x06B]=0x02;       //
      Z80ROM[0x06C]=0xFB;       // EI
      Z80ROM[0x06D]=0xCD;       // CALL 1C8Fh
      Z80ROM[0x06E]=0x8F;       //
      Z80ROM[0x06F]=0x1C;       //
      Z80ROM[0x070]=0xCD;       // CALL 04DCh
      Z80ROM[0x071]=0xDC;       //
      Z80ROM[0x072]=0x04;       //
      Z80ROM[0x073]=0xD3;       // OUTA (AAh)
      Z80ROM[0x074]=0xAA;       //
      Z80ROM[0x075]=0xCD;       // CALL 1C8Fh
      Z80ROM[0x076]=0x8F;       //
      Z80ROM[0x077]=0x1C;       //
      Z80ROM[0x078]=0xCD;       // CALL 04DCh
      Z80ROM[0x079]=0xDC;       //
      Z80ROM[0x07A]=0x04;       //
      Z80ROM[0x07B]=0xD3;       // OUTA (AAh)
      Z80ROM[0x07C]=0xAA;       //
      Z80ROM[0x07D]=0xCD;       // CALL 1C8Fh
      Z80ROM[0x07E]=0x8F;       //
      Z80ROM[0x07F]=0x1C;       //
      Z80ROM[0x080]=0xCD;       // CALL 04DCh
      Z80ROM[0x081]=0xDC;       //
      Z80ROM[0x082]=0x04;       //
      Z80ROM[0x083]=0xD3;       // OUTA (AAh)
      Z80ROM[0x084]=0xAA;       //
      Z80ROM[0x085]=0xC3;       // JP 0068h
      Z80ROM[0x086]=0x68;       //
      Z80ROM[0x087]=0x00;       //

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0xB000, 0xB001, YM2203AReadZ80,              NULL);
   AddZ80AReadByte(0xB400, 0xB401, YM2203BReadZ80,              NULL);
   AddZ80AReadByte(0xB800, 0xB800, JumpingRead_b800,            NULL);
   AddZ80AReadByte(0x0000, 0xFFFF, NULL,                        Z80ROM+0x0000); // Z80 ROM/RAM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,               NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                        NULL);

   AddZ80AWriteByte(0xB000, 0xB001, YM2203AWriteZ80,            NULL);
   AddZ80AWriteByte(0xB400, 0xB401, YM2203BWriteZ80,            NULL);
   AddZ80AWriteByte(0x0000, 0xFFFF, NULL,                       Z80ROM+0x0000); // Z80 RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,             NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,                       NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80,                NULL);  // Trap Idle Z80
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   }
   else{                // Original/Extra

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x24000;

   if(!load_rom("b22-14", Z80ROM, 0x10000)) return;         // Z80 SOUND ROM
/*
   Z80ROM[0x0268]=0x00;         // Fix timers causing sound drops
   Z80ROM[0x0269]=0x00;

   Z80ROM[0x026C]=0x00;
   Z80ROM[0x026D]=0x00;

   Z80ROM[0x0076]=0x00;
   Z80ROM[0x0077]=0x00;
*/
   AddTaitoYM2151(0x0259, 0x01E8, 0x10000, NULL, NULL);

   /*-----------------------*/

   }

   if(romset==1){
   if(!load_rom("ri_m01.rom", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+0]>>4;
      GFX_BG0[tb++]=ROM[ta+0]&15;
   }
   if(!load_rom("ri_m02.rom", ROM, 0x80000)) return;
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      GFX_SPR[tb++]=ROM[ta+1]>>4;
      GFX_SPR[tb++]=ROM[ta+1]&15;
      GFX_SPR[tb++]=ROM[ta+0]>>4;
      GFX_SPR[tb++]=ROM[ta+0]&15;
   }
   if(!load_rom("b22-12",ROM+0x00000,0x10000)) return;
   if(!load_rom("b22-13",ROM+0x10000,0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      GFX_SPR[tb++]=ROM[ta+0x10000]>>4;
      GFX_SPR[tb++]=ROM[ta+0x10000]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      GFX_SPR[tb++]=ROM[ta]&15;
   }

   if(!load_rom("ri_01.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("ri_02.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("ri_03.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("ri_04.rom", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("ri_m03.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("ri_m04.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }
   if(!load_rom("jb1_f89", RAM, 0x10000)) return;             // BOOTLEG C-CHIP
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80000]=0;
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   for(tc=0;tc<40;tc++){
   for(ta=0;ta<0x10;ta++){
      if(rmap_mask[ta]!=0){
         tb=ta+0x4950;
         ROM[tb+tb+0x80000+(tc<<5)]=0;
         ROM[tb+tb+0x80001+(tc<<5)]=RAM[tb+(rmap[tc]<<4)];
      }
   }
   }

   }

   if(romset==0){
   if(!load_rom("ri_m01.rom", ROM, 0x80000)) return;   // Came From Extra
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+0]>>4;
      GFX_BG0[tb++]=ROM[ta+0]&15;
   }
   if(!load_rom("ri_m02.rom", ROM, 0x80000)) return;   // Came From Extra
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      GFX_SPR[tb++]=ROM[ta+1]>>4;
      GFX_SPR[tb++]=ROM[ta+1]&15;
      GFX_SPR[tb++]=ROM[ta+0]>>4;
      GFX_SPR[tb++]=ROM[ta+0]&15;
   }
   if(!load_rom("b22-12", ROM+0x00000, 0x10000)) return;
   if(!load_rom("b22-13", ROM+0x10000, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      GFX_SPR[tb++]=ROM[ta+0x10000]>>4;
      GFX_SPR[tb++]=ROM[ta+0x10000]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      GFX_SPR[tb++]=ROM[ta]&15;
   }

   if (subset==0)
   {
      if(!load_rom("b22-10", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta]=RAM[ta];
      }
      if(!load_rom("b22-11", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta+1]=RAM[ta];
      }
      if(!load_rom("b22-08", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta+0x20000]=RAM[ta];
      }
      if(!load_rom("b22-09", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta+0x20001]=RAM[ta];
      }
   }
   else
   {
      if(!load_rom("b22_10-1", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta]=RAM[ta];
      }
      if(!load_rom("b22_11-1", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta+1]=RAM[ta];
      }
      if(!load_rom("b22_08-1", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta+0x20000]=RAM[ta];
      }
      if(!load_rom("b22_09-1", RAM, 0x10000)) return;
      for(ta=0;ta<0x10000;ta++){
         ROM[ta+ta+0x20001]=RAM[ta];
      }
   }

   if(!load_rom("ri_m03.rom", RAM, 0x20000)) return;   // Came From Extra
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("ri_m04.rom", RAM, 0x20000)) return;   // Came From Extra
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   if(!load_rom("jb1_f89", RAM, 0x10000)) return;              // BOOTLEG C-CHIP
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80000]=0;
      ROM[ta+ta+0x80001]=RAM[ta];
   }
   }

   if(romset==2){

   if(!load_rom("jb2_ic8",&ROM[0x00000],0x10000)) return;      // 8x8 TILES
   if(!load_rom("jb2_ic7",&ROM[0x10000],0x10000)) return;
   tb=0;
   for(ta=0;ta<0x20000;ta++,tb+=8){
      tc=ROM[ta]^255;
      GFX_BG0[tb+0]=((tc&0x80)>>7)<<3;
      GFX_BG0[tb+1]=((tc&0x40)>>6)<<3;
      GFX_BG0[tb+2]=((tc&0x20)>>5)<<3;
      GFX_BG0[tb+3]=((tc&0x10)>>4)<<3;
      GFX_BG0[tb+4]=((tc&0x08)>>3)<<3;
      GFX_BG0[tb+5]=((tc&0x04)>>2)<<3;
      GFX_BG0[tb+6]=((tc&0x02)>>1)<<3;
      GFX_BG0[tb+7]=((tc&0x01)>>0)<<3;
   }
   if(!load_rom("jb2_ic10",&ROM[0x00000],0x10000)) return;
   if(!load_rom("jb2_ic9",&ROM[0x10000],0x10000)) return;
   tb=0;
   for(ta=0;ta<0x20000;ta++,tb+=8){
      tc=ROM[ta]^255;
      GFX_BG0[tb+0]|=((tc&0x80)>>7)<<2;
      GFX_BG0[tb+1]|=((tc&0x40)>>6)<<2;
      GFX_BG0[tb+2]|=((tc&0x20)>>5)<<2;
      GFX_BG0[tb+3]|=((tc&0x10)>>4)<<2;
      GFX_BG0[tb+4]|=((tc&0x08)>>3)<<2;
      GFX_BG0[tb+5]|=((tc&0x04)>>2)<<2;
      GFX_BG0[tb+6]|=((tc&0x02)>>1)<<2;
      GFX_BG0[tb+7]|=((tc&0x01)>>0)<<2;
   }
   if(!load_rom("jb2_ic12",&ROM[0x00000],0x10000)) return;
   if(!load_rom("jb2_ic11",&ROM[0x10000],0x10000)) return;
   tb=0;
   for(ta=0;ta<0x20000;ta++,tb+=8){
      tc=ROM[ta]^255;
      GFX_BG0[tb+0]|=((tc&0x80)>>7)<<1;
      GFX_BG0[tb+1]|=((tc&0x40)>>6)<<1;
      GFX_BG0[tb+2]|=((tc&0x20)>>5)<<1;
      GFX_BG0[tb+3]|=((tc&0x10)>>4)<<1;
      GFX_BG0[tb+4]|=((tc&0x08)>>3)<<1;
      GFX_BG0[tb+5]|=((tc&0x04)>>2)<<1;
      GFX_BG0[tb+6]|=((tc&0x02)>>1)<<1;
      GFX_BG0[tb+7]|=((tc&0x01)>>0)<<1;
   }
   if(!load_rom("jb2_ic14",&ROM[0x00000],0x10000)) return;
   if(!load_rom("jb2_ic13",&ROM[0x10000],0x10000)) return;
   tb=0;
   for(ta=0;ta<0x20000;ta++,tb+=8){
      tc=ROM[ta]^255;
      GFX_BG0[tb+0]|=((tc&0x80)>>7)<<0;
      GFX_BG0[tb+1]|=((tc&0x40)>>6)<<0;
      GFX_BG0[tb+2]|=((tc&0x20)>>5)<<0;
      GFX_BG0[tb+3]|=((tc&0x10)>>4)<<0;
      GFX_BG0[tb+4]|=((tc&0x08)>>3)<<0;
      GFX_BG0[tb+5]|=((tc&0x04)>>2)<<0;
      GFX_BG0[tb+6]|=((tc&0x02)>>1)<<0;
      GFX_BG0[tb+7]|=((tc&0x01)>>0)<<0;
   }

   if(!load_rom("jb2_ic62",&ROM[0x00000],0x10000)) return;     // 16x16 SPRITES
   if(!load_rom("jb2_ic61",&ROM[0x10000],0x10000)) return;
   if(!load_rom("jb2_ic60",&ROM[0x20000],0x8000)) return;
   tb=0;
   for(ta=0;ta<0x28000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+0]=((tc&0x80)>>7)<<0;
      GFX_SPR[tb+1]=((tc&0x40)>>6)<<0;
      GFX_SPR[tb+2]=((tc&0x20)>>5)<<0;
      GFX_SPR[tb+3]=((tc&0x10)>>4)<<0;
      GFX_SPR[tb+4]=((tc&0x08)>>3)<<0;
      GFX_SPR[tb+5]=((tc&0x04)>>2)<<0;
      GFX_SPR[tb+6]=((tc&0x02)>>1)<<0;
      GFX_SPR[tb+7]=((tc&0x01)>>0)<<0;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
   if(!load_rom("jb2_ic78",&ROM[0x00000],0x10000)) return;     // 16x16 SPRITES
   if(!load_rom("jb2_ic77",&ROM[0x10000],0x10000)) return;
   if(!load_rom("jb2_ic76",&ROM[0x20000],0x8000)) return;
   tb=0;
   for(ta=0;ta<0x28000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+0]|=((tc&0x80)>>7)<<1;
      GFX_SPR[tb+1]|=((tc&0x40)>>6)<<1;
      GFX_SPR[tb+2]|=((tc&0x20)>>5)<<1;
      GFX_SPR[tb+3]|=((tc&0x10)>>4)<<1;
      GFX_SPR[tb+4]|=((tc&0x08)>>3)<<1;
      GFX_SPR[tb+5]|=((tc&0x04)>>2)<<1;
      GFX_SPR[tb+6]|=((tc&0x02)>>1)<<1;
      GFX_SPR[tb+7]|=((tc&0x01)>>0)<<1;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
   if(!load_rom("jb2_ic93",&ROM[0x00000],0x10000)) return;     // 16x16 SPRITES
   if(!load_rom("jb2_ic92",&ROM[0x10000],0x10000)) return;
   if(!load_rom("jb2_ic91",&ROM[0x20000],0x8000)) return;
   tb=0;
   for(ta=0;ta<0x28000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+0]|=((tc&0x80)>>7)<<2;
      GFX_SPR[tb+1]|=((tc&0x40)>>6)<<2;
      GFX_SPR[tb+2]|=((tc&0x20)>>5)<<2;
      GFX_SPR[tb+3]|=((tc&0x10)>>4)<<2;
      GFX_SPR[tb+4]|=((tc&0x08)>>3)<<2;
      GFX_SPR[tb+5]|=((tc&0x04)>>2)<<2;
      GFX_SPR[tb+6]|=((tc&0x02)>>1)<<2;
      GFX_SPR[tb+7]|=((tc&0x01)>>0)<<2;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }
   if(!load_rom("jb2_I121",&ROM[0x00000],0x10000)) return;     // 16x16 SPRITES
   if(!load_rom("jb2_I120",&ROM[0x10000],0x10000)) return;
   if(!load_rom("jb2_I119",&ROM[0x20000],0x8000)) return;
   tb=0;
   for(ta=0;ta<0x28000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+0]|=((tc&0x80)>>7)<<3;
      GFX_SPR[tb+1]|=((tc&0x40)>>6)<<3;
      GFX_SPR[tb+2]|=((tc&0x20)>>5)<<3;
      GFX_SPR[tb+3]|=((tc&0x10)>>4)<<3;
      GFX_SPR[tb+4]|=((tc&0x08)>>3)<<3;
      GFX_SPR[tb+5]|=((tc&0x04)>>2)<<3;
      GFX_SPR[tb+6]|=((tc&0x02)>>1)<<3;
      GFX_SPR[tb+7]|=((tc&0x01)>>0)<<3;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=0x8;}}
   }

   if(!load_rom("jb1_h4", RAM, 0x10000)) return;               // 68000 ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("jb1_h8", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("jb1_i4", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("jb1_i8", RAM, 0x10000)) return;
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   if(!load_rom("ri_m03.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("ri_m04.rom", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }
   if(!load_rom("jb1_f89", RAM, 0x10000)) return;              // BOOTLEG C-CHIP
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0x80000]=0;
      ROM[ta+ta+0x80001]=RAM[ta];
   }
   }

   memset(RAM+0x00000,0x00,0x20000);
   memset(RAM+0x1A000,0xFF,0x01000);

   WriteWord(&RAM[0x1B108],0x0000);

   for(ta=0x20000;ta<0x24000;ta++){
      RAM[ta]=(ta>>1)+8;
   }

   for(ta=0x001;ta<0x800;ta+=2){
      CBANK[4][ta]=0xFF;
   }

   for(ta=0x001;ta<0x800;ta+=2){
      CBANK[5][ta]=0xFF;
   }

   CBANK[5][0x001]=0xFF;

   CBANK[2][0x051]=0x30;        /* Dying rainbow graphics */
   CBANK[2][0x053]=0x31;
   CBANK[2][0x055]=0x32;
   CBANK[2][0x057]=0x33;
   CBANK[2][0x059]=0x34;
   CBANK[2][0x05b]=0x35;
   CBANK[2][0x05d]=0x36;
   CBANK[2][0x05f]=0x37;

   CBANK[2][0x061]=0x38;
   CBANK[2][0x063]=0x39;
   CBANK[2][0x065]=0x3a;
   CBANK[2][0x067]=0x3b;
   CBANK[2][0x069]=0x3c;
   CBANK[2][0x06b]=0x3d;
   CBANK[2][0x06d]=0x3e;
   CBANK[2][0x06f]=0x3f;

   CBANK[2][0x071]=0x40;
   CBANK[2][0x073]=0x41;
   CBANK[2][0x075]=0x42;
   CBANK[2][0x077]=0x43;
   CBANK[2][0x079]=0x44;
   CBANK[2][0x07b]=0x45;
   CBANK[2][0x07d]=0x46;
   CBANK[2][0x07f]=0x47;

   CBANK[1][0x20b]=0x00;        // Rainbow Climb
   CBANK[1][0x223]=0x00;        // Rainbow Climb
   CBANK[1][0x277]=0x7F;        // Rainbow Climb
   CBANK[1][0x279]=0x7F;        // Rainbow Climb

   CBANK[1][0x291]=0x00;        // End of Island Boss
   CBANK[1][0x293]=0x00;        // Unknown
   CBANK[1][0x295]=0x00;        // G Below
   CBANK[1][0x297]=0x00;        // G Right
   CBANK[1][0x299]=0x20;        // O below
   CBANK[1][0x29b]=0x10;        // O Right
   CBANK[1][0x29d]=0x40;        // A Below
   CBANK[1][0x29f]=0x20;        // A Right
   CBANK[1][0x2a1]=0x60;        // L Below
   CBANK[1][0x2a3]=0x38;        // L Right
   CBANK[1][0x2a5]=0x80;        // I Below
   CBANK[1][0x2a7]=0x58;        // I Right
   CBANK[1][0x2a9]=0xa0;        // N Below
   CBANK[1][0x2ab]=0x68;        // N Right

   RAMSize=0x34000;             // *****

   RAM_VIDEO  = RAM+0x08000;
   RAM_SCROLL = RAM+0x1B080;
   RAM_OBJECT = RAM+0x18000;

   if(romset!=2)
      InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x8000);
   else
      InitPaletteMap(RAM+0x4000, 0x100, 0x10, 0x1000);


   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x4000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x1400);

/*
 *  Catch 68000 Interrupt wait
 */

   if(romset==0){

   ROM[0x0116E]=0x4E;           // Fix ROM CHECKSUM
   ROM[0x0116F]=0x71;

   ROM[0x070C]=0x4E;            // jmp $7FF00
   ROM[0x070D]=0xF9;
   ROM[0x070E]=0x00;
   ROM[0x070F]=0x07;
   ROM[0x0710]=0xFF;
   ROM[0x0711]=0x00;

   ROM[0x7FF06]=0x13;           // move.b #$00,$AA0000 (speed hack)
   ROM[0x7FF07]=0xFC;
   ROM[0x7FF08]=0x00;
   ROM[0x7FF09]=0x00;
   ROM[0x7FF0A]=0x00;
   ROM[0x7FF0B]=0xAA;
   ROM[0x7FF0C]=0x00;
   ROM[0x7FF0D]=0x00;

   ROM[0x7FF0E]=0x60;           // bra <loop>
   ROM[0x7FF0F]=0x100-16;

   if(subset==0){

   ROM[0x7FF00]=0x4E;           //  jsr $11D78 (random gen)
   ROM[0x7FF01]=0xB9;
   ROM[0x7FF02]=0x00;
   ROM[0x7FF03]=0x01;
   ROM[0x7FF04]=0x1D;
   ROM[0x7FF05]=0x78;

   TMP=jumping_hack;                     // COPY C-CHIP HACK CODE
   for(ta=0;ta<0x1D0;ta++){
      ROM[ta+0xC0]=TMP[ta];
   }

   TMP=jump1630_hack;                    // COPY C-CHIP HACK CODE#2
   for(ta=0;ta<0x5E;ta++){
      ROM[ta+0x7FF10]=TMP[ta];
   }

   WriteLong68k(&ROM[0x40AE],0x4EB90000);               // C-CHIP HACK#1
   WriteLong68k(&ROM[0x40B2],0x00C04E71);

   WriteLong68k(&ROM[0x51FA],0x4EB90000);               // C-CHIP HACK#2
   WriteWord68k(&ROM[0x51FE],0x00CC);

   WriteLong68k(&ROM[0x59A2],0x4EB90000);               // C-CHIP HACK#3
   WriteWord68k(&ROM[0x59A6],0x00E2);

   WriteLong68k(&ROM[0x59AA],0x4EB90000);               // C-CHIP HACK#4
   WriteWord68k(&ROM[0x59AE],0x00F8);

   WriteLong68k(&ROM[0x59B6],0x4EB90000);               // C-CHIP HACK#5
   WriteWord68k(&ROM[0x59BA],0x010E);

   WriteLong68k(&ROM[0x59BE],0x4EB90000);               // C-CHIP HACK#6
   WriteWord68k(&ROM[0x59C2],0x011A);

   WriteLong68k(&ROM[0x5E9A],0x4EB90000);               // C-CHIP HACK#7A
   WriteWord68k(&ROM[0x5E9E],0x0130);

   WriteLong68k(&ROM[0x5F5E],0x4EB90000);               // C-CHIP HACK#7B
   WriteWord68k(&ROM[0x5F62],0x0130);

   WriteLong68k(&ROM[0xB654],0x4EB90000);               // C-CHIP HACK#7C
   WriteWord68k(&ROM[0xB658],0x0130);

   WriteLong68k(&ROM[0xB832],0x4EB90000);               // C-CHIP HACK#7D
   WriteWord68k(&ROM[0xB836],0x0130);

   WriteLong68k(&ROM[0xCF04],0x4EB90000);               // C-CHIP HACK#7E
   WriteWord68k(&ROM[0xCF08],0x0130);

   WriteLong68k(&ROM[0x5F14],0x4EB90000);               // C-CHIP HACK#8
   WriteWord68k(&ROM[0x5F18],0x013C);

   WriteLong68k(&ROM[0x5F1A],0x4EB90000);               // C-CHIP HACK#9
   WriteWord68k(&ROM[0x5F1E],0x0148);

   WriteLong68k(&ROM[0xA07E],0x4EB90000);               // C-CHIP HACK#10A
   WriteWord68k(&ROM[0xA082],0x0154);

   WriteLong68k(&ROM[0xB61E],0x4EB90000);               // C-CHIP HACK#10B
   WriteWord68k(&ROM[0xB622],0x0154);

   WriteLong68k(&ROM[0xB800],0x4EB90000);               // C-CHIP HACK#10C
   WriteWord68k(&ROM[0xB804],0x0154);

   WriteLong68k(&ROM[0xA084],0x4EB90000);               // C-CHIP HACK#11A
   WriteWord68k(&ROM[0xA088],0x0160);

   WriteLong68k(&ROM[0xB624],0x4EB90000);               // C-CHIP HACK#11B
   WriteWord68k(&ROM[0xB628],0x0160);

   WriteLong68k(&ROM[0xB806],0x4EB90000);               // C-CHIP HACK#11C
   WriteWord68k(&ROM[0xB80A],0x0160);

   WriteLong68k(&ROM[0x12C42],0x4EB90000);              // C-CHIP HACK#12
   WriteLong68k(&ROM[0x12C46],0x016C4E71);

   WriteLong68k(&ROM[0x65BA],0x4EB90000);               // C-CHIP HACK#13A
   WriteWord68k(&ROM[0x65BE],0x0178);

   WriteLong68k(&ROM[0x65E8],0x4EB90000);               // C-CHIP HACK#13B
   WriteWord68k(&ROM[0x65EC],0x0178);

   WriteLong68k(&ROM[0x7104],0x4EB90000);               // C-CHIP HACK#14A
   WriteWord68k(&ROM[0x7108],0x0186);

   WriteLong68k(&ROM[0x719E],0x4EB90000);               // C-CHIP HACK#14B
   WriteWord68k(&ROM[0x71A2],0x0186);

   WriteLong68k(&ROM[0xD13E],0x4EB90000);               // C-CHIP HACK#15
   WriteWord68k(&ROM[0xD142],0x01AE);

   WriteLong68k(&ROM[0x13EB8],0x4EB90000);              // C-CHIP HACK#16
   WriteLong68k(&ROM[0x13EBC],0x01C84E71);

   WriteLong68k(&ROM[0x14134],0x4EB90000);              // C-CHIP HACK#17
   WriteWord68k(&ROM[0x14138],0x01E6);

   WriteLong68k(&ROM[0x13FA2],0x4EB90000);              // C-CHIP HACK#18
   WriteWord68k(&ROM[0x13FA6],0x01F4);

   WriteLong68k(&ROM[0x13FDE],0x4EB90000);              // C-CHIP HACK#19
   WriteLong68k(&ROM[0x13FE2],0x02024E71);

   WriteLong68k(&ROM[0x13FEE],0x4EB90000);              // C-CHIP HACK#20
   WriteLong68k(&ROM[0x13FF2],0x021A4EF9);
   WriteLong68k(&ROM[0x13FF6],0x00014004);

   WriteLong68k(&ROM[0x14074],0x4EB90000);              // C-CHIP HACK#21A
   WriteLong68k(&ROM[0x14078],0x024C4E71);
   WriteWord68k(&ROM[0x1407C],0x4E71);

   WriteLong68k(&ROM[0x1409E],0x4EB90000);              // C-CHIP HACK#21B
   WriteLong68k(&ROM[0x140A2],0x024C4E71);
   WriteWord68k(&ROM[0x140A6],0x4E71);

   WriteLong68k(&ROM[0x140C6],0x4EB90000);              // C-CHIP HACK#21C
   WriteLong68k(&ROM[0x140CA],0x024C4E71);
   WriteWord68k(&ROM[0x140CE],0x4E71);

   WriteLong68k(&ROM[0x140E0],0x4EB90000);              // C-CHIP HACK#21D
   WriteLong68k(&ROM[0x140E4],0x024C4E71);
   WriteWord68k(&ROM[0x140E8],0x4E71);

   WriteLong68k(&ROM[0x140FA],0x4EB90000);              // C-CHIP HACK#21E
   WriteLong68k(&ROM[0x140FE],0x024C4E71);
   WriteWord68k(&ROM[0x14102],0x4E71);

   WriteLong68k(&ROM[0x139A6],0x4EB90000);              // C-CHIP HACK#22A
   WriteLong68k(&ROM[0x139AA],0x02644E71);
   WriteWord68k(&ROM[0x139AE],0x4E71);

   WriteLong68k(&ROM[0x1BB8E],0x4EB90000);              // C-CHIP HACK#22B
   WriteLong68k(&ROM[0x1BB92],0x02644E71);
   WriteWord68k(&ROM[0x1BB96],0x4E71);

   WriteLong68k(&ROM[0x597A],0x4EF8599C);               // C-CHIP INLINE HACK#1

   //WriteWord68k(&ROM[0x164E],0xD1C7);                 // SECERT ROOMS?

   }
   else{

   ROM[0x7FF00]=0x4E;           //  jsr $11D78 (random gen)
   ROM[0x7FF01]=0xB9;
   ROM[0x7FF02]=0x00;
   ROM[0x7FF03]=0x01;
   ROM[0x7FF04]=0x1D;
   ROM[0x7FF05]=0x78 + 0x2E + 0x08;

   TMP=jumping_hack;                     // COPY C-CHIP HACK CODE
   for(ta=0;ta<0x1D0;ta++){
      ROM[ta+0xC0]=TMP[ta];
   }

   TMP=jump1630_hack;                    // COPY C-CHIP HACK CODE#2
   for(ta=0;ta<0x5E;ta++){
      ROM[ta+0x7FF10]=TMP[ta];
   }

   WriteLong68k(&ROM[0x40AE],0x4EB90000);               // C-CHIP HACK#1
   WriteLong68k(&ROM[0x40B2],0x00C04E71);

   WriteLong68k(&ROM[0x51FA],0x4EB90000);               // C-CHIP HACK#2
   WriteWord68k(&ROM[0x51FE],0x00CC);

   WriteLong68k(&ROM[0x59A2 + 0x2E],0x4EB90000);               // C-CHIP HACK#3
   WriteWord68k(&ROM[0x59A6 + 0x2E],0x00E2);

   WriteLong68k(&ROM[0x59AA + 0x2E],0x4EB90000);               // C-CHIP HACK#4
   WriteWord68k(&ROM[0x59AE + 0x2E],0x00F8);

   WriteLong68k(&ROM[0x59B6 + 0x2E],0x4EB90000);               // C-CHIP HACK#5
   WriteWord68k(&ROM[0x59BA + 0x2E],0x010E);

   WriteLong68k(&ROM[0x59BE + 0x2E],0x4EB90000);               // C-CHIP HACK#6
   WriteWord68k(&ROM[0x59C2 + 0x2E],0x011A);

   WriteLong68k(&ROM[0x5E9A + 0x2E],0x4EB90000);               // C-CHIP HACK#7A *
   WriteWord68k(&ROM[0x5E9E + 0x2E],0x0130);

   WriteLong68k(&ROM[0x5F5E + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#7B *
   WriteWord68k(&ROM[0x5F62 + 0x2E + 0x08],0x0130);

   WriteLong68k(&ROM[0xB654 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#7C
   WriteWord68k(&ROM[0xB658 + 0x2E + 0x08],0x0130);

   WriteLong68k(&ROM[0xB832 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#7D
   WriteWord68k(&ROM[0xB836 + 0x2E + 0x08],0x0130);

   WriteLong68k(&ROM[0xCF04 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#7E
   WriteWord68k(&ROM[0xCF08 + 0x2E + 0x08],0x0130);

   WriteLong68k(&ROM[0x5F14 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#8 *
   WriteWord68k(&ROM[0x5F18 + 0x2E + 0x08],0x013C);

   WriteLong68k(&ROM[0x5F1A + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#9
   WriteWord68k(&ROM[0x5F1E + 0x2E + 0x08],0x0148);

   WriteLong68k(&ROM[0xA07E + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#10A
   WriteWord68k(&ROM[0xA082 + 0x2E + 0x08],0x0154);

   WriteLong68k(&ROM[0xB61E + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#10B
   WriteWord68k(&ROM[0xB622 + 0x2E + 0x08],0x0154);

   WriteLong68k(&ROM[0xB800 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#10C
   WriteWord68k(&ROM[0xB804 + 0x2E + 0x08],0x0154);

   WriteLong68k(&ROM[0xA084 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#11A
   WriteWord68k(&ROM[0xA088 + 0x2E + 0x08],0x0160);

   WriteLong68k(&ROM[0xB624 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#11B
   WriteWord68k(&ROM[0xB628 + 0x2E + 0x08],0x0160);

   WriteLong68k(&ROM[0xB806 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#11C
   WriteWord68k(&ROM[0xB80A + 0x2E + 0x08],0x0160);

   WriteLong68k(&ROM[0x12C42 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#12
   WriteLong68k(&ROM[0x12C46 + 0x2E + 0x08],0x016C4E71);

   WriteLong68k(&ROM[0x65BA + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#13A
   WriteWord68k(&ROM[0x65BE + 0x2E + 0x08],0x0178);

   WriteLong68k(&ROM[0x65E8 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#13B
   WriteWord68k(&ROM[0x65EC + 0x2E + 0x08],0x0178);

   WriteLong68k(&ROM[0x7104 + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#14A
   WriteWord68k(&ROM[0x7108 + 0x2E + 0x08],0x0186);

   WriteLong68k(&ROM[0x719E + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#14B
   WriteWord68k(&ROM[0x71A2 + 0x2E + 0x08],0x0186);

   WriteLong68k(&ROM[0xD13E + 0x2E + 0x08],0x4EB90000);               // C-CHIP HACK#15
   WriteWord68k(&ROM[0xD142 + 0x2E + 0x08],0x01AE);

   WriteLong68k(&ROM[0x13EB8 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#16
   WriteLong68k(&ROM[0x13EBC + 0x2E + 0x08],0x01C84E71);

   WriteLong68k(&ROM[0x14134 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#17
   WriteWord68k(&ROM[0x14138 + 0x2E + 0x08],0x01E6);

   WriteLong68k(&ROM[0x13FA2 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#18
   WriteWord68k(&ROM[0x13FA6 + 0x2E + 0x08],0x01F4);

   WriteLong68k(&ROM[0x13FDE + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#19
   WriteLong68k(&ROM[0x13FE2 + 0x2E + 0x08],0x02024E71);

   WriteLong68k(&ROM[0x13FEE + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#20
   WriteLong68k(&ROM[0x13FF2 + 0x2E + 0x08],0x021A4EF9);
   WriteLong68k(&ROM[0x13FF6 + 0x2E + 0x08],0x00014004 + 0x2E + 0x08);

   WriteLong68k(&ROM[0x14074 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#21A
   WriteLong68k(&ROM[0x14078 + 0x2E + 0x08],0x024C4E71);
   WriteWord68k(&ROM[0x1407C + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x1409E + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#21B
   WriteLong68k(&ROM[0x140A2 + 0x2E + 0x08],0x024C4E71);
   WriteWord68k(&ROM[0x140A6 + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x140C6 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#21C
   WriteLong68k(&ROM[0x140CA + 0x2E + 0x08],0x024C4E71);
   WriteWord68k(&ROM[0x140CE + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x140E0 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#21D
   WriteLong68k(&ROM[0x140E4 + 0x2E + 0x08],0x024C4E71);
   WriteWord68k(&ROM[0x140E8 + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x140FA + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#21E
   WriteLong68k(&ROM[0x140FE + 0x2E + 0x08],0x024C4E71);
   WriteWord68k(&ROM[0x14102 + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x139A6 + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#22A
   WriteLong68k(&ROM[0x139AA + 0x2E + 0x08],0x02644E71);
   WriteWord68k(&ROM[0x139AE + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x1BB8E + 0x2E + 0x08],0x4EB90000);              // C-CHIP HACK#22B
   WriteLong68k(&ROM[0x1BB92 + 0x2E + 0x08],0x02644E71);
   WriteWord68k(&ROM[0x1BB96 + 0x2E + 0x08],0x4E71);

   WriteLong68k(&ROM[0x597A + 0x2E],0x4EF8599C + 0x2E);        // C-CHIP INLINE HACK#1

   //WriteWord68k(&ROM[0x164E],0xD1C7);                 // SECERT ROOMS?

   }

   }

   if(romset==1){
   ROM[0x01180]=0x4E;           // Fix ROM CHECKSUM
   ROM[0x01181]=0x71;

   ROM[0x070C]=0x4E;            // jmp $7FF00
   ROM[0x070D]=0xF9;
   ROM[0x070E]=0x00;
   ROM[0x070F]=0x07;
   ROM[0x0710]=0xFF;
   ROM[0x0711]=0x00;

   ROM[0x7FF00]=0x4E;           //  jsr $129BC (random gen)
   ROM[0x7FF01]=0xB9;
   ROM[0x7FF02]=0x00;
   ROM[0x7FF03]=0x01;
   ROM[0x7FF04]=0x29;
   ROM[0x7FF05]=0xBC;

   ROM[0x7FF06]=0x13;           // move.b #$00,$AA0000 (speed hack)
   ROM[0x7FF07]=0xFC;
   ROM[0x7FF08]=0x00;
   ROM[0x7FF09]=0x00;
   ROM[0x7FF0A]=0x00;
   ROM[0x7FF0B]=0xAA;
   ROM[0x7FF0C]=0x00;
   ROM[0x7FF0D]=0x00;

   ROM[0x7FF0E]=0x60;           // bra <loop>
   ROM[0x7FF0F]=0x100-16;

   TMP=jumping_hack;                     // COPY C-CHIP HACK CODE
   for(ta=0;ta<0x1D0;ta++){
      ROM[ta+0xC0]=TMP[ta];
   }

   TMP=jump1630_hack;                    // COPY C-CHIP HACK CODE#2
   for(ta=0;ta<0x5E;ta++){
      ROM[ta+0x7FF10]=TMP[ta];
   }

   WriteWord68k(&ROM[0x7FF2A],0x104A);
   WriteWord68k(&ROM[0x7FF2E],0x11CC);
   WriteWord68k(&ROM[0x7FF34],0x11CE);

   WriteLong68k(&ROM[0x44BE],0x4EB90000);               // C-CHIP HACK#1
   WriteLong68k(&ROM[0x44C2],0x00C04E71);

   WriteLong68k(&ROM[0x5670],0x4EB90000);               // C-CHIP HACK#2
   WriteWord68k(&ROM[0x5674],0x00CC);

   WriteLong68k(&ROM[0x615E],0x4EB90000);               // C-CHIP HACK#3
   WriteWord68k(&ROM[0x6162],0x00E2);

   WriteLong68k(&ROM[0x6166],0x4EB90000);               // C-CHIP HACK#4
   WriteWord68k(&ROM[0x616A],0x00F8);

   WriteLong68k(&ROM[0x6172],0x4EB90000);               // C-CHIP HACK#5
   WriteWord68k(&ROM[0x6176],0x010E);

   WriteLong68k(&ROM[0x617A],0x4EB90000);               // C-CHIP HACK#6
   WriteWord68k(&ROM[0x617E],0x011A);

   WriteLong68k(&ROM[0x664C],0x4EB90000);               // C-CHIP HACK#7A
   WriteWord68k(&ROM[0x6650],0x0130);

   WriteLong68k(&ROM[0x674C],0x4EB90000);               // C-CHIP HACK#7B
   WriteWord68k(&ROM[0x6750],0x0130);

   WriteLong68k(&ROM[0xBEC6],0x4EB90000);               // C-CHIP HACK#7C
   WriteWord68k(&ROM[0xBECA],0x0130);

   WriteLong68k(&ROM[0xC0CE],0x4EB90000);               // C-CHIP HACK#7D
   WriteWord68k(&ROM[0xC0D2],0x0130);

   WriteLong68k(&ROM[0xD7C4],0x4EB90000);               // C-CHIP HACK#7E
   WriteWord68k(&ROM[0xD7C8],0x0130);

   WriteLong68k(&ROM[0x66CE],0x4EB90000);               // C-CHIP HACK#8
   WriteWord68k(&ROM[0x66D2],0x013C);

   WriteLong68k(&ROM[0x66D4],0x4EB90000);               // C-CHIP HACK#9
   WriteWord68k(&ROM[0x66D8],0x0148);

   WriteLong68k(&ROM[0xA8AA],0x4EB90000);               // C-CHIP HACK#10A
   WriteWord68k(&ROM[0xA8AE],0x0154);

   WriteLong68k(&ROM[0xBE90],0x4EB90000);               // C-CHIP HACK#10B
   WriteWord68k(&ROM[0xBE94],0x0154);

   WriteLong68k(&ROM[0xC09C],0x4EB90000);               // C-CHIP HACK#10C
   WriteWord68k(&ROM[0xC0A0],0x0154);

   WriteLong68k(&ROM[0xA8B0],0x4EB90000);               // C-CHIP HACK#11A
   WriteWord68k(&ROM[0xA8B4],0x0160);

   WriteLong68k(&ROM[0xBE96],0x4EB90000);               // C-CHIP HACK#11B
   WriteWord68k(&ROM[0xBE9A],0x0160);

   WriteLong68k(&ROM[0xC0A2],0x4EB90000);               // C-CHIP HACK#11C
   WriteWord68k(&ROM[0xC0A6],0x0160);

   WriteLong68k(&ROM[0x13886],0x4EB90000);              // C-CHIP HACK#12
   WriteLong68k(&ROM[0x1388A],0x016C4E71);

   WriteLong68k(&ROM[0x6DB4],0x4EB90000);               // C-CHIP HACK#13A
   WriteWord68k(&ROM[0x6DB8],0x0178);

   WriteLong68k(&ROM[0x6DE2],0x4EB90000);               // C-CHIP HACK#13B
   WriteWord68k(&ROM[0x6DE6],0x0178);

   WriteLong68k(&ROM[0x78FA],0x4EB90000);               // C-CHIP HACK#14A
   WriteWord68k(&ROM[0x78FE],0x0186);

   WriteLong68k(&ROM[0x7994],0x4EB90000);               // C-CHIP HACK#14B
   WriteWord68k(&ROM[0x7998],0x0186);

   WriteLong68k(&ROM[0xD9FE],0x4EB90000);               // C-CHIP HACK#15
   WriteWord68k(&ROM[0xDA02],0x01AE);

   WriteLong68k(&ROM[0x14AF4],0x4EB90000);              // C-CHIP HACK#16
   WriteLong68k(&ROM[0x14AF8],0x01C84E71);

   WriteLong68k(&ROM[0x14D70],0x4EB90000);              // C-CHIP HACK#17
   WriteWord68k(&ROM[0x14D74],0x01E6);

   WriteLong68k(&ROM[0x14BDE],0x4EB90000);              // C-CHIP HACK#18
   WriteWord68k(&ROM[0x14BE2],0x01F4);

   WriteLong68k(&ROM[0x14C1A],0x4EB90000);              // C-CHIP HACK#19
   WriteLong68k(&ROM[0x14C1E],0x02024E71);

   WriteLong68k(&ROM[0x14C2A],0x4EB90000);              // C-CHIP HACK#20
   WriteLong68k(&ROM[0x14C2E],0x021A4EF9);
   WriteLong68k(&ROM[0x14C32],0x00014C40);

   WriteLong68k(&ROM[0x14CB0],0x4EB90000);              // C-CHIP HACK#21A
   WriteLong68k(&ROM[0x14CB4],0x024C4E71);
   WriteWord68k(&ROM[0x14CB8],0x4E71);

   WriteLong68k(&ROM[0x14CDA],0x4EB90000);              // C-CHIP HACK#21B
   WriteLong68k(&ROM[0x14CDE],0x024C4E71);
   WriteWord68k(&ROM[0x14CE2],0x4E71);

   WriteLong68k(&ROM[0x14D02],0x4EB90000);              // C-CHIP HACK#21C
   WriteLong68k(&ROM[0x14D06],0x024C4E71);
   WriteWord68k(&ROM[0x14D0A],0x4E71);

   WriteLong68k(&ROM[0x14D1C],0x4EB90000);              // C-CHIP HACK#21D
   WriteLong68k(&ROM[0x14D20],0x024C4E71);
   WriteWord68k(&ROM[0x14D24],0x4E71);

   WriteLong68k(&ROM[0x14D36],0x4EB90000);              // C-CHIP HACK#21E
   WriteLong68k(&ROM[0x14D3A],0x024C4E71);
   WriteWord68k(&ROM[0x14D3E],0x4E71);

   WriteLong68k(&ROM[0x145D6],0x4EB90000);              // C-CHIP HACK#22A
   WriteLong68k(&ROM[0x145DA],0x02644E71);
   WriteWord68k(&ROM[0x145DE],0x4E71);

   WriteLong68k(&ROM[0x1C758],0x4EB90000);              // C-CHIP HACK#22B
   WriteLong68k(&ROM[0x1C75C],0x02644E71);
   WriteWord68k(&ROM[0x1C760],0x4E71);

   WriteLong68k(&ROM[0x6136],0x4EF86158);               // C-CHIP INLINE HACK#1

   }

   if(romset==2){
   ROM[0x0116E]=0x4E;           // Fix ROM CHECKSUM
   ROM[0x0116F]=0x71;

   ROM[0x070C]=0x4E;            // jmp $7FF00
   ROM[0x070D]=0xF9;
   ROM[0x070E]=0x00;
   ROM[0x070F]=0x07;
   ROM[0x0710]=0xFF;
   ROM[0x0711]=0x00;

   ROM[0x7FF00]=0x4E;           //  jsr $11D78 (random gen)
   ROM[0x7FF01]=0xB9;
   ROM[0x7FF02]=0x00;
   ROM[0x7FF03]=0x01;
   ROM[0x7FF04]=0x1D;
   ROM[0x7FF05]=0x78;

   ROM[0x7FF06]=0x13;           // move.b #$00,$AA0000 (speed hack)
   ROM[0x7FF07]=0xFC;
   ROM[0x7FF08]=0x00;
   ROM[0x7FF09]=0x00;
   ROM[0x7FF0A]=0x00;
   ROM[0x7FF0B]=0xAA;
   ROM[0x7FF0C]=0x00;
   ROM[0x7FF0D]=0x00;

   ROM[0x7FF0E]=0x60;           // bra <loop>
   ROM[0x7FF0F]=0x100-16;

   WriteLong68k(&ROM[0x788],0x303C00ED);                // UNDO BOOTLEG SPRITE HACK
   WriteLong68k(&ROM[0x78C],0x41ED084A);

   WriteLong68k(&ROM[0x820],0x33ED1042);                // UNDO BOOTLEG SCROLL HACK
   WriteLong68k(&ROM[0x824],0x00C20000);

   //WriteLong68k(&ROM[0xA6C],0xD1C23019);              // UNDO BOOTLEG COLOR HACK
   //WriteLong68k(&ROM[0xA70],0x30C051C9);              // <NOT 100%>

   }

   ROM[0x7FF30]=0x60;

   // Init tc0100scn emulation
   // ------------------------

   if (romset < 2) {
     set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   } else {
     set_colour_mapper(&col_map_xxxx_bbbb_gggg_rrrr_rev);
   }

   tc0100scn[0].layer[0].RAM    =RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX    =GFX_BG0;
   tc0100scn[0].layer[0].MASK   =GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR    =RAM_SCROLL+0;
   tc0100scn[0].layer[0].type   =0;
   tc0100scn[0].layer[0].bmp_x  =32;
   tc0100scn[0].layer[0].bmp_y  =32;
   tc0100scn[0].layer[0].bmp_w  =320;
   tc0100scn[0].layer[0].bmp_h  =224;
   //tc0100scn[0].layer[0].mapper = col_mapper[romset];
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x  =16;
   tc0100scn[0].layer[0].scr_y  =16;

   tc0100scn[0].layer[1].RAM    =RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX    =GFX_BG0;
   tc0100scn[0].layer[1].MASK   =GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR    =RAM_SCROLL+2;
   tc0100scn[0].layer[1].type   =0;
   tc0100scn[0].layer[1].bmp_x  =32;
   tc0100scn[0].layer[1].bmp_y  =32;
   tc0100scn[0].layer[1].bmp_w  =320;
   tc0100scn[0].layer[1].bmp_h  =224;
   //tc0100scn[0].layer[1].mapper = col_mapper[romset];
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x  =16;
   tc0100scn[0].layer[1].scr_y  =16;

   tc0100scn[0].RAM     = RAM_VIDEO;
   init_tc0100scn(0);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.RAM        = RAM_OBJECT;
   tc0002obj.GFX        = GFX_SPR;
   tc0002obj.MASK       = GFX_SPR_SOLID;
   tc0002obj.bmp_x      = 32;
   tc0002obj.bmp_y      = 32;
   tc0002obj.bmp_w      = 320;
   tc0002obj.bmp_h      = 224;
   //tc0002obj.mapper     = col_mapper[romset];
   tc0002obj.tile_mask  = 0x1FFF;
   tc0002obj.ofs_x      = 0;
   tc0002obj.ofs_y      = -16;

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xA0000);
   ByteSwap(RAM,0x20000);

   AddMemFetch(0x000000, 0x09FFFF, ROM+0x000000-0x000000);      // 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x09FFFF, NULL, ROM+0x000000);
   AddReadByte(0x10C000, 0x10FFFF, NULL, RAM+0x000000);
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM+0x008000);
   AddReadByte(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddReadByte(0x200000, 0x203FFF, NULL, RAM+0x004000);                 // COLOR RAM
   AddReadByte(0xC20000, 0xC20003, NULL, RAM+0x01B000);
   AddReadByte(0xC40000, 0xC40003, NULL, RAM+0x01B004);
   AddReadByte(0xC50000, 0xC50001, NULL, RAM+0x01B008);
   AddReadByte(0x390000, 0x390001, NULL, RAM+0x01B012);                 // DSWA
   AddReadByte(0x3A0000, 0x3A0001, NULL, RAM+0x01B00A);
   AddReadByte(0x3B0000, 0x3B0001, NULL, RAM+0x01B014);                 // DSWB
   AddReadByte(0x3C0000, 0x3C0001, NULL, RAM+0x01B00C);
   AddReadByte(0x3E0000, 0x3E0003, tc0140syt_read_main_68k, NULL);      // SOUND
   AddReadByte(0x800000, 0x800FFF, CChipReadB, NULL);                   // C-CHIP
   if(romset==2){
   AddReadByte(0x400000, 0x400003, NULL, RAM+0x01B100);                 // JUMPING: DSW
   AddReadByte(0x401000, 0x401003, NULL, RAM+0x01B104);                 // JUMPING: INPUT
   AddReadByte(0x420000, 0x420000, NULL, RAM+0x01B108);                 // JUMPING: ???
   }
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);               // <bad reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x09FFFF, NULL, ROM+0x000000);
   AddReadWord(0x10C000, 0x10FFFF, NULL, RAM+0x000000);
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM+0x008000);
   AddReadWord(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddReadWord(0x200000, 0x203FFF, NULL, RAM+0x004000);                 // COLOR RAM
   AddReadWord(0xC20000, 0xC20003, NULL, RAM+0x01B000);
   AddReadWord(0xC40000, 0xC40003, NULL, RAM+0x01B004);
   AddReadWord(0xC50000, 0xC50001, NULL, RAM+0x01B008);
   AddReadWord(0x390000, 0x390001, NULL, RAM+0x01B012);                 // DSWA
   AddReadWord(0x3A0000, 0x3A0001, NULL, RAM+0x01B00A);
   AddReadWord(0x3B0000, 0x3B0001, NULL, RAM+0x01B014);                 // DSWB
   AddReadWord(0x3C0000, 0x3C0001, NULL, RAM+0x01B00C);
   AddReadWord(0x3E0000, 0x3E0003, NULL, RAM+0x01B00E);                 // SOUND
   AddReadWord(0x800000, 0x800FFF, CChipReadW, NULL);                   // C-CHIP
   if(romset==2){
   AddReadWord(0x400000, 0x400003, NULL, RAM+0x01B100);                 // JUMPING: DSW
   AddReadWord(0x401000, 0x401003, NULL, RAM+0x01B104);                 // JUMPING: INPUT
   }
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);               // <bad reads>
   AddReadWord(-1, -1, NULL, NULL);


   AddWriteByte(0x10C000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM+0x008000);                // SCREEN RAM
   AddWriteByte(0xD00000, 0xD01FFF, NULL, RAM+0x018000);                // OBJECT RAM
   AddWriteByte(0x200000, 0x203FFF, NULL, RAM+0x004000);                // COLOR RAM

   AddWriteByte(0xC20000, 0xC20003, NULL, RAM_SCROLL+6);                // SCROLL Y
   AddWriteByte(0xC40000, 0xC40003, NULL, RAM_SCROLL+0);                // SCROLL X
   AddWriteByte(0xC50000, 0xC50001, NULL, RAM_SCROLL+14);               // CTRL

   AddWriteByte(0x390000, 0x390001, NULL, RAM+0x01B012);                // DSWA
   AddWriteByte(0x3A0000, 0x3A0001, NULL, RAM+0x01B00A);
   AddWriteByte(0x3B0000, 0x3B0001, NULL, RAM+0x01B014);                // DSWB
   AddWriteByte(0x3C0000, 0x3C0001, NULL, RAM+0x01B00C);
   AddWriteByte(0x3E0000, 0x3E0003, tc0140syt_write_main_68k, NULL);    // SOUND
   AddWriteByte(0x800000, 0x800FFF, CChipWriteB, NULL);                 // C-CHIP
   if(romset==2){
   AddWriteByte(0x400007, 0x400007, Jumpingsound_w, NULL);              // JUMPING: SOUND
   }
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);                   // Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);             // <bad writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x10C000, 0x10FFFF, NULL, RAM+0x000000);                // 68000 RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM+0x008000);
   AddWriteWord(0xD00000, 0xD01FFF, NULL, RAM+0x018000);
   AddWriteWord(0x200000, 0x203FFF, NULL, RAM+0x004000);                // COLOR RAM
   if(romset==2){
   AddWriteWord(0x440000, 0x4407FF, NULL, RAM+0x01B200);                // JUMPING: SPRITE?
   AddWriteWord(0x430000, 0x430003, NULL, RAM+0x01B110);                // JUMPING: SCROLL
   }
   AddWriteWord(0xC20000, 0xC20003, NULL, RAM_SCROLL+6);                // SCROLL Y
   AddWriteWord(0xC40000, 0xC40003, NULL, RAM_SCROLL+0);                // SCROLL X
   AddWriteWord(0xC50000, 0xC50001, NULL, RAM_SCROLL+14);               // CTRL

   AddWriteWord(0x390000, 0x390001, NULL, RAM+0x01B012);                // DSWA
   AddWriteWord(0x3A0000, 0x3A0001, NULL, RAM+0x01B00A);
   AddWriteWord(0x3B0000, 0x3B0001, NULL, RAM+0x01B014);                // DSWB
   AddWriteWord(0x3C0000, 0x3C0001, NULL, RAM+0x01B00C);
   AddWriteWord(0x3E0000, 0x3E0003, NULL, RAM+0x01B00E);                // SOUND
   AddWriteWord(0x800000, 0x800FFF, CChipWriteW, NULL);                 // C-CHIP
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);             // <bad writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();     // Set Starscream mem pointers...
}

static void execute_rainbow(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));    // M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 4);

   if(romset==2){
      cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));    // Sound Z80
      cpu_interrupt(CPU_Z80_0, 0x38);
   }
   else{
      Taito2151_FrameRI();              // Antiriad
   }
}

static void DrawRainbow(void)
{
   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // Init tc0002obj emulation
   // ------------------------

   tc0002obj.ctrl = TC0002OBJ_CONV_CTRL(ReadWord(&RAM[0x1B00A]));

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

}

// Jumping Islands Sound Comm
// --------------------------

static int JSoundPort=0;

static void Jumpingsound_w(UINT32 offset,UINT8 data)
{
    JSoundPort=data;
}

static UINT16 JumpingRead_b800(UINT16 offset)
{
   int ta;

   ta=JSoundPort;
   JSoundPort=0xFF;

   return(ta);
}

/*

Jumping Islands
---------------

Name     | Description
---------+---------------------------------
JB1_CD67 | Z80 ROM
JB1_F89  | C-Chip Data
JB1_H23  | 68000 ROM (block#3) (even)
JB1_H4   | 68000 ROM (block#1) (even)
JB1_H7   | 68000 ROM (block#3) (odd)
JB1_H8   | 68000 ROM (block#1) (odd)
JB1_I23  | 68000 ROM (block#4) (even)
JB1_I4   | 68000 ROM (block#2) (even)
JB1_I7   | 68000 ROM (block#4) (odd)
JB1_I8   | 68000 ROM (block#2) (odd)
JB2_I119 | 16x16 Sprites (block#3) (plane1)
JB2_I120 | 16x16 Sprites (block#2) (plane1)
JB2_I121 | 16x16 Sprites (block#1) (plane1)
JB2_IC10 | 8x8 Tiles (block#1) (plane2)
JB2_IC11 | 8x8 Tiles (block#2) (plane3)
JB2_IC12 | 8x8 Tiles (block#1) (plane3)
JB2_IC13 | 8x8 Tiles (block#2) (plane4)
JB2_IC14 | 8x8 Tiles (block#1) (plane4)
JB2_IC60 | 16x16 Sprites (block#3) (plane2)
JB2_IC61 | 16x16 Sprites (block#2) (plane2)
JB2_IC62 | 16x16 Sprites (block#1) (plane2)
JB2_IC7  | 8x8 Tiles (block#2) (plane1)
JB2_IC76 | 16x16 Sprites (block#3) (plane3)
JB2_IC77 | 16x16 Sprites (block#2) (plane3)
JB2_IC78 | 16x16 Sprites (block#1) (plane3)
JB2_IC8  | 8x8 Tiles (block#1) (plane1)
JB2_IC9  | 8x8 Tiles (block#2) (plane2)
JB2_IC91 | 16x16 Sprites (block#3) (plane3)
JB2_IC92 | 16x16 Sprites (block#2) (plane3)
JB2_IC93 | 16x16 Sprites (block#1) (plane3)

Rainbow Original
----------------

- Has bad/missing roms, so stuff added from
  rainbow extra!!

Name       | Description
-----------+---------------------------------
B22-03     | 68000 ROM (block#2, even) (too short dump)
B22-04     | 68000 ROM (block#2, odd) (too short dump)
B22-08     | 68000 ROM (block#0, even) *
B22-09     | 68000 ROM (block#0, odd) *
B22-10     | 68000 ROM (block#1, even) *
B22-11     | 68000 ROM (block#1, odd) *
B22-12     | 16x16 SPR Tiles#2 (odd)
B22-13     | 16x16 SPR Tiles#2 (even)
B22-14     | Z80 ROM *
JB1_F89    | C-Chip data (from jumping islands)
RI_M01.ROM | 8x8 BG0 Tiles (from extra romset)
RI_M02.ROM | 16x16 SPR Tiles (from extra romset)
RI_M03.ROM | 68000 ROM (block#2, even) (from extra romset)
RI_M04.ROM | 68000 ROM (block#2, odd) (from extra romset)


Rainbow Extra
-------------

Name       | Description
-----------+-----------------------------------
JB1_F89    | C-Chip data (from jumping islands)
RI_01.ROM  | 68000 ROM (block#0, even) *
RI_02.ROM  | 68000 ROM (block#0, odd) *
RI_03.ROM  | 68000 ROM (block#1, even) *
RI_04.ROM  | 68000 ROM (block#1, odd) *
RI_12.ROM  | 16x16 SPR Tiles#2 (odd)
RI_13.ROM  | 16x16 SPR Tiles#2 (even)
RI_14.ROM  | Z80 ROM *
RI_M01.ROM | 8x8 BG0 Tiles
RI_M02.ROM | 16x16 SPR Tiles
RI_M03.ROM | 68000 ROM (block#2, even)
RI_M04.ROM | 68000 ROM (block#2, odd)

*/

static struct VIDEO_INFO video_rainbow =
{
   DrawRainbow,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_jumping[] =
{
   { "jumping_islands", },
   { "jumping", },
   { ROMOF("rainbow"), },
   { CLONEOF("rainbow"), },
   { NULL, },
};
CLNE( jumping, rainbow, "Jumping Islands", BOOTLEG, 1989, GAME_PLATFORM,
	.input = input_jumping,
	.dsw = dsw_jumping,
	.long_name_jpn = "ジャンピングアイランド",
	.sound = sound_jumping,
);
static struct DIR_INFO dir_rainbow[] =
{
   { "rainbow_islands", },
   { "rainbow", },
   { "rainbowo", },
   { "jumping", },
   { NULL, },
};
GME( rainbow, "Rainbow Islands", TAITO, 1987, GAME_PLATFORM,
	.romsw = romsw_rainbow,
	.long_name_jpn = "レインボーアイランド",
	.board = "B22",
);
static struct DIR_INFO dir_rainbowa[] =
{
   { "rainbow_islands_alt", },
   { "rainbowa", },
   { ROMOF("rainbow"), },
   { CLONEOF("rainbow"), },
   { NULL, },
};
CLNE( rainbowa, rainbow,"Rainbow Islands (alternate)", TAITO, 1987, GAME_PLATFORM,
	.romsw = romsw_rainbow,
	.long_name_jpn = "レインボーアイランド",
	.board = "B22",
);
static struct DIR_INFO dir_rainbowe[] =
{
   { "rainbow_islands_extra", },
   { "rainbowe", },
   { ROMOF("rainbow"), },
   { CLONEOF("rainbow"), },
   { NULL, },
};
CLNE( rainbowe,rainbow, "Rainbow Islands (extra)", TAITO, 1988, GAME_PLATFORM,
	.romsw = romsw_rainbow,
	.long_name_jpn = "レインボーアイランドエキストラ",
	.board = "B22",
);

