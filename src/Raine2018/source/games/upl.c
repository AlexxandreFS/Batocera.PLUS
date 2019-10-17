#define DRV_DEF_SOUND sound_arkarea
/******************************************************************************/
/*                                                                            */
/*                    UPL Z80B+Z80B+YM2203+YM2203 GAMES                       */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "sasound.h"		// sample support routines
#include "savegame.h"

/****************
   MUTANT NIGHT
 ****************/


static struct ROM_INFO rom_mnight[] =
{
   { "mn13-b23.bin", 0x00010000, 0x65714070, 0, 0, 0, },
   { "mn11-b20.bin", 0x00010000, 0x4d37e0f4, 0, 0, 0, },
   { "mn12-b22.bin", 0x00010000, 0xb22cbbd3, 0, 0, 0, },
   { "mn10-b10.bin", 0x00008000, 0x37b8221f, 0, 0, 0, },
   {   "mn1-j7.bin", 0x00010000, 0xa0782a31, 0, 0, 0, },
   {  "mn2-j12.bin", 0x00008000, 0x9c391d1b, 0, 0, 0, },
   {  "mn3-j14.bin", 0x00008000, 0xdf6a4f7a, 0, 0, 0, },
   {  "mn4-j16.bin", 0x00008000, 0xc5e42bb4, 0, 0, 0, },
   {  "mn5-j17.bin", 0x00008000, 0x2a73f88e, 0, 0, 0, },
   {  "mn6-j19.bin", 0x00008000, 0x56678d14, 0, 0, 0, },
   {  "mn7-e11.bin", 0x00010000, 0x4883059c, 0, 0, 0, },
   {  "mn8-e12.bin", 0x00010000, 0x02b91445, 0, 0, 0, },
   {  "mn9-e14.bin", 0x00010000, 0x9f08d160, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_arkarea[] =
{
   INP0( COIN1, 0x00F800, 0x40 ),
   INP0( COIN2, 0x00F800, 0x80 ),
   INP0( SERVICE, 0x00F800, 0x10 ),

   INP0( P1_START, 0x00F800, 0x01 ),
   INP0( P1_UP, 0x00F801, 0x08 ),
   INP0( P1_DOWN, 0x00F801, 0x04 ),
   INP0( P1_LEFT, 0x00F801, 0x02 ),
   INP0( P1_RIGHT, 0x00F801, 0x01 ),
   INP0( P1_B1, 0x00F801, 0x10 ),
   INP0( P1_B2, 0x00F801, 0x20 ),

   INP0( P2_START, 0x00F800, 0x02 ),
   INP0( P2_UP, 0x00F802, 0x08 ),
   INP0( P2_DOWN, 0x00F802, 0x04 ),
   INP0( P2_LEFT, 0x00F802, 0x02 ),
   INP0( P2_RIGHT, 0x00F802, 0x01 ),
   INP0( P2_B1, 0x00F802, 0x10 ),
   INP0( P2_B2, 0x00F802, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_mutant_night_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_EXTRA_LIFE,          0x02, 0x02 },
   { _("30k and every 50k"),     0x02},
   { _("50k and every 80k"),     0x00},
   { MSG_DIFFICULTY,          0x04},
   { MSG_NORMAL,              0x04},
   { MSG_HARD,                0x00},
   { MSG_FREE_PLAY,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   DSW_CABINET( 0x00, 0x10),
   DSW_DEMO_SOUND( 0x00, 0x20),
   { MSG_LIVES,               0xC0, 0x04 },
   { "3",                     0xC0},
   { "2",                     0x80},
   { "4",                     0x40},
   { "5",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_mutant_night_1[] =
{
   DSW_TEST_MODE( 0x00, 0x01),
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
   { MSG_COINAGE,             0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0xE0},
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0xA0},
   { MSG_1COIN_4PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x60},
   { MSG_3COIN_1PLAY,         0x40},
   { MSG_4COIN_1PLAY,         0x40},
   { MSG_5COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_mnight[] =
{
   { 0x00F803, 0xFF, dsw_data_mutant_night_0 },
   { 0x00F804, 0xFF, dsw_data_mutant_night_1 },
   { 0,        0,    NULL,      },
};



static struct YM2203interface ym2203_interface =
{
   2,				// 2 Chips
   4000000,			// 2.5MHz?
   { YM2203_VOL(88,88), YM2203_VOL(88,88) },
//   { 0x00ff20c0, 0x00ff20c0 },
   { 0, 0 },
   { 0, 0 },
   { 0, 0 },
   { 0, 0 },
   { NULL, NULL }
};

static struct SOUND_INFO sound_arkarea[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { 0,             NULL,                 },
};


/************
   ARK AREA
 ************/


static struct ROM_INFO rom_arkarea[] =
{
   {  "arkarea.001", 0x00010000, 0x09d11ab7, 0, 0, 0, },
   {  "arkarea.002", 0x00010000, 0x051d3482, 0, 0, 0, },
   {  "arkarea.003", 0x00010000, 0x6f45a308, 0, 0, 0, },
   {  "arkarea.004", 0x00008000, 0x69e36af2, 0, 0, 0, },
   {  "arkarea.005", 0x00010000, 0x9886004d, 0, 0, 0, },
   {  "arkarea.006", 0x00010000, 0x2c0567d6, 0, 0, 0, },
   {  "arkarea.007", 0x00010000, 0xd5684a27, 0, 0, 0, },
   {  "arkarea.008", 0x00008000, 0x1ce1b5b9, 0, 0, 0, },
   {  "arkarea.009", 0x00008000, 0xdb1c81d1, 0, 0, 0, },
   {  "arkarea.010", 0x00008000, 0x5a460dae, 0, 0, 0, },
   {  "arkarea.011", 0x00008000, 0x63f022c9, 0, 0, 0, },
   {  "arkarea.012", 0x00008000, 0x3c4c65d5, 0, 0, 0, },
   {  "arkarea.013", 0x00008000, 0x2d409d58, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_ark_area_0[] =
{
   { MSG_COINAGE,             0x03, 0x04 },
   { MSG_1COIN_1PLAY,         0x03},
   { MSG_1COIN_2PLAY,         0x02},
   { MSG_2COIN_1PLAY,         0x01},
   { MSG_3COIN_1PLAY,         0x00},
   { MSG_DSWA_BIT3,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT4,           0x08, 0x02 },
   { MSG_OFF,                 0x08},
   { MSG_ON,                  0x00},
   DSW_DEMO_SOUND( 0x00, 0x10),
   { MSG_DSWA_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_EXTRA_LIFE,          0x40, 0x02 },
   { _("Every 50k"),             0x40},
   { _("Every 100k"),            0x00},
   { MSG_LIVES,               0x80, 0x02 },
   { "3",                     0x80},
   { "4",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_ark_area_1[] =
{
   DSW_TEST_MODE( 0x00, 0x01),
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
   { MSG_DSWB_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_arkarea[] =
{
   { 0x00F803, 0xFF, dsw_data_ark_area_0 },
   { 0x00F804, 0xFF, dsw_data_ark_area_1 },
   { 0,        0,    NULL,      },
};


/***************
   NINJA KID 2
 ***************/


static struct ROM_INFO rom_ninjakd2[] =
{
   {   "nk2_01.rom", 0x00008000, 0x3cdbb906, 0, 0, 0, },
   {   "nk2_02.rom", 0x00008000, 0xb5ce9a1a, 0, 0, 0, },
   {   "nk2_03.rom", 0x00008000, 0xad275654, 0, 0, 0, },
   {   "nk2_04.rom", 0x00008000, 0xe7692a77, 0, 0, 0, },
   {   "nk2_05.rom", 0x00008000, 0x5dac9426, 0, 0, 0, },
   {   "nk2_06.rom", 0x00010000, 0xd3a18a79, 0, 0, 0, },
   {   "nk2_07.rom", 0x00010000, 0x0be5cd13, 0, 0, 0, },
   {   "nk2_08.rom", 0x00010000, 0x1b79c50a, 0, 0, 0, },
   {   "nk2_09.rom", 0x00010000, 0xc1d2d170, 0, 0, 0, },
   {   "nk2_10.rom", 0x00010000, 0xc913c4ab, 0, 0, 0, },
   {   "nk2_11.rom", 0x00010000, 0x41a714b3, 0, 0, 0, },
   {   "nk2_12.rom", 0x00008000, 0xdb5657a9, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_ninjakd2[] =
{
   INP0( COIN1, 0x00C000, 0x40 ),
   INP0( COIN2, 0x00C000, 0x80 ),
   INP0( SERVICE, 0x00C000, 0x10 ),

   INP0( P1_START, 0x00C000, 0x01 ),
   INP0( P1_UP, 0x00C001, 0x08 ),
   INP0( P1_DOWN, 0x00C001, 0x04 ),
   INP0( P1_LEFT, 0x00C001, 0x02 ),
   INP0( P1_RIGHT, 0x00C001, 0x01 ),
   INP0( P1_B1, 0x00C001, 0x10 ),
   INP0( P1_B2, 0x00C001, 0x20 ),

   INP0( P2_START, 0x00C000, 0x02 ),
   INP0( P2_UP, 0x00C002, 0x08 ),
   INP0( P2_DOWN, 0x00C002, 0x04 ),
   INP0( P2_LEFT, 0x00C002, 0x02 ),
   INP0( P2_RIGHT, 0x00C002, 0x01 ),
   INP0( P2_B1, 0x00C002, 0x10 ),
   INP0( P2_B2, 0x00C002, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_ninja_kid_2_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_EXTRA_LIFE,          0x06, 0x04 },
   { _("30k and 50k"),           0x06},
   { _("20k and 50k"),           0x04},
   { _("50k and 100k"),          0x02},
   { _("None"),                  0x00},
   DSW_CONTINUE_PLAY( 0x08, 0x00),
   DSW_DEMO_SOUND( 0x00, 0x10),
   { MSG_DIFFICULTY,          0x20},
   { MSG_NORMAL,              0x20},
   { MSG_HARD,                0x00},
   { MSG_LIVES,               0x40, 0x02 },
   { "3",                     0x40},
   { "4",                     0x00},
   { _("Language"),              0x80, 0x02 },
   { _("Japanese"),              0x80},
   { _("English"),               0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_ninja_kid_2_1[] =
{
   DSW_TEST_MODE( 0x00, 0x01),
   DSW_CABINET( 0x00, 0x02),
   { _("Credit Service"),        0x04, 0x02 },
   { MSG_ON,                  0x04},
   { MSG_OFF,                 0x00},
   { MSG_COIN2,               0x18, 0x04 },
   { MSG_1COIN_1PLAY,         0x18},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_1COIN_3PLAY,         0x08},
   { MSG_2COIN_1PLAY,         0x00},
   { MSG_COIN1,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0xE0},
   { MSG_1COIN_2PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0xA0},
   { MSG_1COIN_4PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x60},
   { MSG_3COIN_1PLAY,         0x40},
   { MSG_4COIN_1PLAY,         0x40},
   { MSG_5COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_ninjakd2[] =
{
   { 0x00C003, 0xFF, dsw_data_ninja_kid_2_0 },
   { 0x00C004, 0xFF, dsw_data_ninja_kid_2_1 },
   { 0,        0,    NULL,      },
};


/*************************
   OMEGA FIGHTER SPECIAL
 *************************/


static struct ROM_INFO rom_omegafs[] =
{
   {   "1back2.15b", 0x00080000, 0x6210ddcc, 0, 0, 0, },
   {   "2back1.27b", 0x00080000, 0x21f8a32e, 0, 0, 0, },
   {    "3back3.5f", 0x00080000, 0xc31cae56, 0, 0, 0, },
   {        "4.18h", 0x00008000, 0x9e2d8152, 0, 0, 0, },
   {         "5.3l", 0x00020000, 0x503a3e63, 0, 0, 0, },
   {         "6.4l", 0x00020000, 0x6277735c, 0, 0, 0, },
   {         "7.7m", 0x00010000, 0xd40fc8d5, 0, 0, 0, },
   {        "8.23m", 0x00020000, 0x0bd2a5d1, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_omegaf[] =
{
   INP0( COIN1, 0x00C000, 0x40 ),
   INP0( COIN2, 0x00C000, 0x80 ),
   INP0( SERVICE, 0x00C000, 0x10 ),

   INP0( P1_START, 0x00C000, 0x01 ),
   INP0( P1_UP, 0x00C001, 0x08 ),
   INP0( P1_DOWN, 0x00C001, 0x04 ),
   INP0( P1_LEFT, 0x00C001, 0x02 ),
   INP0( P1_RIGHT, 0x00C001, 0x01 ),
   INP0( P1_B1, 0x00C001, 0x10 ),
   INP0( P1_B2, 0x00C001, 0x20 ),

   INP0( P2_START, 0x00C000, 0x02 ),
   INP0( P2_UP, 0x00C002, 0x08 ),
   INP0( P2_DOWN, 0x00C002, 0x04 ),
   INP0( P2_LEFT, 0x00C002, 0x02 ),
   INP0( P2_RIGHT, 0x00C002, 0x01 ),
   INP0( P2_B1, 0x00C002, 0x10 ),
   INP0( P2_B2, 0x00C002, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_omega_fighter_0[] =
{
   DSW_SCREEN( 0x01, 0x00),
   { MSG_DIFFICULTY,          0x06, 0x04 },
   { MSG_NORMAL,              0x06},
   { MSG_HARDEST,             0x04},
   { MSG_HARD,                0x02},
   { MSG_EASY,                0x00},
   DSW_TEST_MODE( 0x00, 0x08),
   DSW_CABINET( 0x00, 0x10),
   DSW_DEMO_SOUND( 0x20, 0x00),
   { MSG_LIVES,               0xC0, 0x04 },
   { "3",                     0xC0},
   { "5",                     0x80},
   { "4",                     0x40},
   { "2",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_omega_fighter_1[] =
{
   { MSG_EXTRA_LIFE,          0x03, 0x04 },
   { _("30k"),                   0x03},
   { _("100k"),                  0x02},
   { _("50k"),                   0x01},
   { _("20k"),                   0x00},
   { MSG_COIN1,               0xE0, 0x08 },
   { MSG_1COIN_1PLAY,         0xE0},
   { MSG_2COIN_1PLAY,         0xC0},
   { MSG_1COIN_3PLAY,         0xA0},
   { MSG_4COIN_1PLAY,         0x80},
   { MSG_1COIN_2PLAY,         0x60},
   { MSG_3COIN_1PLAY,         0x40},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_5COIN_1PLAY,         0x00},
   { MSG_COIN2,               0x1C, 0x08 },
   { MSG_1COIN_1PLAY,         0x1C},
   { MSG_1COIN_2PLAY,         0x0C},
   { MSG_2COIN_1PLAY,         0x18},
   { MSG_1COIN_3PLAY,         0x14},
   { MSG_4COIN_1PLAY,         0x10},
   { MSG_3COIN_1PLAY,         0x08},
   { MSG_1COIN_4PLAY,         0x04},
   { MSG_5COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_omegaf[] =
{
   { 0x00C003, 0xF9, dsw_data_omega_fighter_0 },
   { 0x00C004, 0xFC, dsw_data_omega_fighter_1 },
   { 0,        0,    NULL,      },
};


/*****************
   OMEGA FIGHTER
 *****************/


static struct ROM_INFO rom_omegaf[] =
{
   {   "1back2.15b", 0x00080000, 0x6210ddcc, 0, 0, 0, },
   {   "2back1.27b", 0x00080000, 0x21f8a32e, 0, 0, 0, },
   {    "3back3.5f", 0x00080000, 0xc31cae56, 0, 0, 0, },
   {        "4.18h", 0x00008000, 0x9e2d8152, 0, 0, 0, },
   {          "1.5", 0x00020000, 0x57a7fd96, 0, 0, 0, },
   {         "6.4l", 0x00020000, 0x6277735c, 0, 0, 0, },
   {         "7.7m", 0x00010000, 0xd40fc8d5, 0, 0, 0, },
   {        "8.23m", 0x00020000, 0x0bd2a5d1, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


/**************
   RAD ACTION
 **************/


static struct ROM_INFO rom_rdaction[] =
{
   {         "1.3u", 0x00008000, 0x5c475611, 0, 0, 0, },
   {   "nk2_10.rom", 0x00010000, 0xc913c4ab, 0, 0, 0, },
   {   "nk2_11.rom", 0x00010000, 0x41a714b3, 0, 0, 0, },
   {        "12.5n", 0x00008000, 0x0936b365, 0, 0, 0, },
   {         "2.3s", 0x00008000, 0xa1e23bd2, 0, 0, 0, },
   {   "nk2_03.rom", 0x00008000, 0xad275654, 0, 0, 0, },
   {   "nk2_04.rom", 0x00008000, 0xe7692a77, 0, 0, 0, },
   {         "nk2_05.bin", 0x00008000, 0x960725fb, 0, 0, 0, },
   {   "nk2_06.bin", 0x00010000, 0x7bfe6c9e, 0, 0, 0, },
   {   "nk2_07.rom", 0x00010000, 0x0be5cd13, 0, 0, 0, },
   {   "nk2_08.rom", 0x00010000, 0x1b79c50a, 0, 0, 0, },
   {   "nk2_09.rom", 0x00010000, 0xc1d2d170, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static int romset;

static UINT8 *RAM2;
static UINT8 *ROM2;
static UINT8 *RAM_VIDEO;

static UINT8 *RAM_FG0;
static UINT8 mask_fg0;

static UINT8 *RAM_SPR;
static UINT8 mask_spr;

static UINT8 *GFX_FG0;
static UINT8 *FG0_Mask;

static UINT8 *GFX_SPR;
static UINT8 *SPR_Mask;

static UINT8 *GFX_BG1;
static UINT8 *BG1_Mask;

static UINT8 *GFX_BG0;
static UINT8 *BG0_Mask;

static UINT8 *GFX_BG2;
static UINT8 *BG2_Mask;

#define BG_FLIP_NONE	0x00
#define BG_FLIP_Y	0x01
#define BG_FLIP_X	0x02
#define BG_FLIP_XY	0x03

typedef struct UPL_BG_LAYER			// Information about 1 layer
{
   UINT8 *RAM;					// Layer RAM address
   UINT8 *SCR;					// Layer SCROLL RAM address
   UINT8 *GFX;					// Layer GFX address
   UINT8 *MASK;					// Layer GFX SOLID MASK address
   UINT32 type;					// Type of layer
   UINT8 col_bank;				// Colour Bank Offset
} UPL_BG_LAYER;

static struct UPL_BG_LAYER bg_layers[3];

/*

UPL Z80 GAMES
-------------

Supported romsets:

0 - Ninja Kid 2
1 - Rad Action
2 - Mutant Night
3 - Omega Fighter
4 - Ark Area

? - XX Mission

Mutant Night:

0000-7FFF BASE ROM
8000-BFFF BANK ROM
C000-D9FF RAM
DA00-DFFF OBJECT
E000-E7FF BG0
E800-EFFF FG0
F000-F7FF COLOUR
F800-F805 INPUT
FA02-FA02 BANK SWITCH

Omega Fighter:

0000-7FFF BASE ROM
8000-BFFF BANK ROM
C002-C002 BANK SWITCH
D000-D7FF FG0
D800-DFFF COLOUR
E000-F9FF RAM
FA00-FFFF OBJECT

*/

/******************************************************************************/
/* ROBO KID Z80 ROM BANKING                                                   */
/******************************************************************************/

static void UPLBankWrite(UINT16 offset, UINT8 data)
{
  z80_set_bank(1,data);
}

static void init_bank_rom(UINT8 *src, UINT8 *dst)
{
  z80_init_banks_area_ofs(1,src,0x40000,0x8000,0x4000,2);
}

/******************************************************************************/
/* ROBO KID VIDEO RAM BANKING                                                 */
/******************************************************************************/

static UINT8 *BG_BANK[4];

static void OmegaBG0BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[1] = RAM_VIDEO+(1*0x2000)+((data&7)<<10);
}

static void OmegaBG1BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[2] = RAM_VIDEO+(2*0x2000)+((data&7)<<10);
}

static void OmegaBG2BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[3] = RAM_VIDEO+(3*0x2000)+((data&7)<<10);
}

static void OmegaBG012Write(UINT16 offset, UINT8 data)
{
   BG_BANK[(offset>>10)&3][offset&0x3FF] = data;
}

static UINT8 OmegaBG012Read(UINT16 offset)
{
   return BG_BANK[(offset>>10)&3][offset&0x3FF];
}

static void OmegaBG012Init(void)
{
   BG_BANK[0] = RAM_VIDEO+(0*0x2000);
   BG_BANK[1] = RAM_VIDEO+(1*0x2000);
   BG_BANK[2] = RAM_VIDEO+(2*0x2000);
   BG_BANK[3] = RAM_VIDEO+(3*0x2000);
}

/******************************************************************************/
/* ROBO KID SOUND COMMUNICATION                                               */
/******************************************************************************/

static UINT8 sound_byte;

static void UPLSoundWrite(UINT16 offset, UINT8 data)
{
   sound_byte = data;
}

static UINT8 UPLSoundRead(UINT16 offset)
{
   UINT8 ta;
   ta = sound_byte;
   sound_byte = 0xFF;
   return ta;
}

/******************************************************************************/
/* ROBO KID VIDEO RAM BANKING                                                 */
/******************************************************************************/

#if 0

static UINT8 *BG_BANK[4];

static void UPLBG0BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[2] = RAM_VIDEO+(2<<11)+((data&1)<<10);
}

static void UPLBG1BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[1] = RAM_VIDEO+(1<<11)+((data&1)<<10);
}

static void UPLBG2BankWrite(UINT16 offset, UINT8 data)
{
   BG_BANK[0] = RAM_VIDEO+(0<<11)+((data&1)<<10);
}

static void UPLBG012Write(UINT16 offset, UINT8 data)
{
   BG_BANK[(offset>>10)&3][offset&0x3FF] = data;
}

static UINT8 UPLBG012Read(UINT16 offset)
{
   return BG_BANK[(offset>>10)&3][offset&0x3FF];
}

static void UPLBG012Init(void)
{
   BG_BANK[0] = RAM_VIDEO+(0<<11);
   BG_BANK[1] = RAM_VIDEO+(1<<11);
   BG_BANK[2] = RAM_VIDEO+(2<<11);
   BG_BANK[3] = RAM_VIDEO+(3<<11);
}
#endif

/******************************************************************************/
/* GFX DECODES (from MS-1)                                                    */
/******************************************************************************/

static int MS1DecodeFG0(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_FG0=AllocateMem(0x10000))) return(0);
   memset(GFX_FG0,0x00,0x10000);

   tb=0;
   for(ta=0;ta<size;ta++,tb+=2){
      GFX_FG0[tb+0]=(src[ta]>>4)^15;
      GFX_FG0[tb+1]=(src[ta]&15)^15;
   }

   FG0_Mask = make_solid_mask_8x8(GFX_FG0, 0x400);

   return 1;
}

static int MS1DecodeSPR(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_SPR=AllocateMem(0x100000))) return(0);
   memset(GFX_SPR,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_SPR[tb+0]=(src[ta+0]>>4)^15;
      GFX_SPR[tb+1]=(src[ta+0]&15)^15;
      GFX_SPR[tb+2]=(src[ta+1]>>4)^15;
      GFX_SPR[tb+3]=(src[ta+1]&15)^15;
      GFX_SPR[tb+4]=(src[ta+2]>>4)^15;
      GFX_SPR[tb+5]=(src[ta+2]&15)^15;
      GFX_SPR[tb+6]=(src[ta+3]>>4)^15;
      GFX_SPR[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   SPR_Mask = make_solid_mask_16x16(GFX_SPR, 0x1000);

   return 1;
}

static int MS1DecodeSPR_TypeB(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_SPR=AllocateMem(0x100000))) return(0);
   memset(GFX_SPR,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_SPR[tb+0]=(src[ta+0]>>4)^15;
      GFX_SPR[tb+1]=(src[ta+0]&15)^15;
      GFX_SPR[tb+2]=(src[ta+1]>>4)^15;
      GFX_SPR[tb+3]=(src[ta+1]&15)^15;
      GFX_SPR[tb+4]=(src[ta+2]>>4)^15;
      GFX_SPR[tb+5]=(src[ta+2]&15)^15;
      GFX_SPR[tb+6]=(src[ta+3]>>4)^15;
      GFX_SPR[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   SPR_Mask = make_solid_mask_16x16(GFX_SPR, 0x1000);

   return 1;
}

static int MS1DecodeBG0(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG0=AllocateMem(0x100000))) return(0);
   memset(GFX_BG0,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG0[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG0[tb+1]=(src[ta+0]&15)^15;
      GFX_BG0[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG0[tb+3]=(src[ta+1]&15)^15;
      GFX_BG0[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG0[tb+5]=(src[ta+2]&15)^15;
      GFX_BG0[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG0[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   BG0_Mask = make_solid_mask_16x16(GFX_BG0, 0x1000);

   return 1;
}

static int MS1DecodeBG2_TypeB(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG2=AllocateMem(0x100000))) return(0);
   memset(GFX_BG2,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG2[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG2[tb+1]=(src[ta+0]&15)^15;
      GFX_BG2[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG2[tb+3]=(src[ta+1]&15)^15;
      GFX_BG2[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG2[tb+5]=(src[ta+2]&15)^15;
      GFX_BG2[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG2[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG2_Mask = make_solid_mask_16x16(GFX_BG2, 0x1000);

   return 1;
}

static int MS1DecodeBG1_TypeB(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG1=AllocateMem(0x100000))) return(0);
   memset(GFX_BG1,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG1[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG1[tb+1]=(src[ta+0]&15)^15;
      GFX_BG1[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG1[tb+3]=(src[ta+1]&15)^15;
      GFX_BG1[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG1[tb+5]=(src[ta+2]&15)^15;
      GFX_BG1[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG1[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG1_Mask = make_solid_mask_16x16(GFX_BG1, 0x1000);

   return 1;
}

static int MS1DecodeBG0_TypeB(UINT8 *src, UINT32 size)
{
   UINT32 ta,tb;

   if(!(GFX_BG0=AllocateMem(0x100000))) return(0);
   memset(GFX_BG0,0x00,0x100000);

   tb=0;
   for(ta=0;ta<size;ta+=4){
      GFX_BG0[tb+0]=(src[ta+0]>>4)^15;
      GFX_BG0[tb+1]=(src[ta+0]&15)^15;
      GFX_BG0[tb+2]=(src[ta+1]>>4)^15;
      GFX_BG0[tb+3]=(src[ta+1]&15)^15;
      GFX_BG0[tb+4]=(src[ta+2]>>4)^15;
      GFX_BG0[tb+5]=(src[ta+2]&15)^15;
      GFX_BG0[tb+6]=(src[ta+3]>>4)^15;
      GFX_BG0[tb+7]=(src[ta+3]&15)^15;
      tb+=16;
      if((tb&0xFF)==0){tb-=0xF8;}
      else{if((tb&0xFF)==8){tb-=8;}}
   }

   BG0_Mask = make_solid_mask_16x16(GFX_BG0, 0x1000);

   return 1;
}


/******************************************************************************/

static void load_ninjakd2(void)
{
   UINT8 *TMP;
   int ta;

   romset=0;

   if(!(ROM2=AllocateMem(0x10000))) return;

   RAMSize    = 0x10000+0x10000+0x2000+0x10;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_VIDEO  = RAM+0x10000+0x10000;

   if(!(TMP =AllocateMem(0x28000))) return;

   if(!load_rom("nk2_01.rom",TMP+0x00000,0x08000)) return;	// Z80 MAIN ROM *
   if(!load_rom("nk2_02.rom",TMP+0x08000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("nk2_03.rom",TMP+0x10000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("nk2_04.rom",TMP+0x18000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("nk2_05.rom",TMP+0x20000,0x08000)) return;	// Z80 MAIN ROM

   // Fix ROM Checksum
   // ----------------

   TMP[0x2984]=0x18;  // JR xx

   // Decustomize Interrupt
   // ---------------------

   TMP[0x0039]=0x10;

   // Skip Idle Z80
   // -------------

   TMP[0x02C2]=0xD3;  // OUTA (AAh)
   TMP[0x02C3]=0xAA;  //

   SetStopZ80BMode2(0x02C4);

   z80_init_banks_area(1,TMP,0x28000,0x8000,0x4000);

   memset(RAM+0x00000, 0x00, 0x10000);
   memset(RAM+0x0C000, 0xFF, 0x00010);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0010, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC800, 0xFFFF, NULL,			RAM+0xC800);	// COLOR/FG0/BG0/RAM/OBJECT
   AddZ80BReadByte(0xC000, 0xC00F, NULL,			RAM+0xC000);	// INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC800, 0xFFFF, NULL,			RAM+0xC800);	// COLOR/FG0/BG0/RAM/OBJECT
   AddZ80BWriteByte(0xC202, 0xC202, UPLBankWrite,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xC200, 0xC200, UPLSoundWrite,		NULL);		// SOUND
   AddZ80BWriteByte(0xC100, 0xC7FF, NULL,			RAM+0xC100);	// MISC CTRL
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   //if(!load_rom("robokid.k7",ROM2+0x00000,0x10000)) return;	// Z80 SUB ROM
   if(!load_rom("nk2_06.rom",ROM2+0x00000,0x10000)) return;	// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x00B2]=0xD3;  // OUTA (AAh)
   ROM2[0x00B3]=0xAA;  //

   SetStopZ80CMode2(0x00B2);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xC7FF, NULL,			RAM2+0x0000);	// Z80 ROM/BANK ROM/RAM
   AddZ80CReadByte(0xE000, 0xE000, UPLSoundRead,		NULL);		// SOUND
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xC7FF, NULL,			RAM2+0xC000);	// RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0x01, YM2203AReadZ80,			NULL);		// YM2203#1
   AddZ80CReadPort(0x80, 0x81, YM2203BReadZ80,			NULL);		// YM2203#2
   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0x00, 0x01, YM2203AWriteZ80,		NULL);		// YM2203#1
   AddZ80CWritePort(0x80, 0x81, YM2203BWriteZ80,		NULL);		// YM2203#2
   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(TMP=AllocateMem(0x040000))) return;

   if(!load_rom("nk2_12.rom", TMP+0x8000, 0x8000)) return;    // 8x8 FG0 TILES *
   for(ta=0;ta<0x2000;ta++){
      TMP[ta+ta+0x0000]=TMP[ta+0x08000];	// Interleave
      TMP[ta+ta+0x0001]=TMP[ta+0x0A000];
      TMP[ta+ta+0x4000]=TMP[ta+0x0C000];	// Interleave
      TMP[ta+ta+0x4001]=TMP[ta+0x0E000];
   }
   if(!MS1DecodeFG0(TMP,0x08000))return;

   if(!load_rom("nk2_08.rom", TMP+0x20000, 0x10000)) return;  // 16x16 SPRITES *
   if(!load_rom("nk2_07.rom", TMP+0x30000, 0x10000)) return;  // 16x16 SPRITES *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x20000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x24000];
      TMP[ta+ta+0x08000]=TMP[ta+0x28000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x2C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x30000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x34000];
      TMP[ta+ta+0x18000]=TMP[ta+0x38000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x3C000];
   }
   if(!MS1DecodeSPR(TMP,0x20000))return;

   if(!load_rom("nk2_11.rom", TMP+0x20000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("nk2_10.rom", TMP+0x30000, 0x10000)) return;  // 16x16 BG0 *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x20000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x24000];
      TMP[ta+ta+0x08000]=TMP[ta+0x28000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x2C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x30000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x34000];
      TMP[ta+ta+0x18000]=TMP[ta+0x38000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x3C000];
   }
   if(!MS1DecodeBG0(TMP,0x20000))return;

   FreeMem(TMP);

   InitPaletteMap(RAM+0xC800, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k);

   AddSaveData(SAVE_USER_1, (UINT8 *) &sound_byte,          sizeof(sound_byte));

   // Init Video Hardware
   // -------------------

   bg_layers[0].RAM      = RAM+0xD800;
   bg_layers[0].SCR      = RAM+0xC208;
   bg_layers[0].GFX      = GFX_BG0;
   bg_layers[0].MASK     = BG0_Mask;
   bg_layers[0].col_bank = 0x00;
   bg_layers[0].type     = BG_FLIP_XY;

   bg_layers[1].RAM      = NULL;

   bg_layers[2].RAM      = NULL;

   RAM_FG0 = RAM+0xD000;
   mask_fg0 = 0x20;

   RAM_SPR = RAM+0xFA00;
   mask_spr = 0x10;
}

static void load_rdaction(void)
{
   UINT8 *TMP;
   int ta;

   romset=1;

   if(!(ROM2=AllocateMem(0x10000))) return;

   RAMSize    = 0x10000+0x10000+0x2000+0x10;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_VIDEO  = RAM+0x10000+0x10000;

   if(!(TMP =AllocateMem(0x28000))) return;

   if(!load_rom("1.3u",TMP+0x00000,0x08000)) return;	// Z80 MAIN ROM *
   if(!load_rom("2.3s",TMP+0x08000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("nk2_03.rom",TMP+0x10000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("nk2_04.rom",TMP+0x18000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("nk2_05.bin",TMP+0x20000,0x08000)) return;	// Z80 MAIN ROM

   // Fix ROM Checksum
   // ----------------

   TMP[0x29B0]=0x18;  // JR xx

   // Decustomize Interrupt
   // ---------------------

   TMP[0x0039]=0x10;

   // Skip Idle Z80
   // -------------

   TMP[0x02C2]=0xD3;  // OUTA (AAh)
   TMP[0x02C3]=0xAA;  //

   SetStopZ80BMode2(0x02C4);

   z80_init_banks_area(1,TMP,0x28000,0x8000,0x4000);

   memset(RAM+0x00000, 0x00, 0x10000);
   memset(RAM+0x0C000, 0xFF, 0x00010);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0010, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC800, 0xFFFF, NULL,			RAM+0xC800);	// COLOR/FG0/BG0/RAM/OBJECT
   AddZ80BReadByte(0xC000, 0xC00F, NULL,			RAM+0xC000);	// INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC800, 0xFFFF, NULL,			RAM+0xC800);	// COLOR/FG0/BG0/RAM/OBJECT
   AddZ80BWriteByte(0xC202, 0xC202, UPLBankWrite,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xC200, 0xC200, UPLSoundWrite,		NULL);		// SOUND
   AddZ80BWriteByte(0xC100, 0xC7FF, NULL,			RAM+0xC100);	// MISC CTRL
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("nk2_06.bin",ROM2+0x00000,0x10000)) return;	// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x00B2]=0xD3;  // OUTA (AAh)
   ROM2[0x00B3]=0xAA;  //

   SetStopZ80CMode2(0x00B2);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xC7FF, NULL,			RAM2+0x0000);	// Z80 ROM/BANK ROM/RAM
   AddZ80CReadByte(0xE000, 0xE000, UPLSoundRead,		NULL);		// SOUND
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xC7FF, NULL,			RAM2+0xC000);	// RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0x01, YM2203AReadZ80,			NULL);		// YM2203#1
   AddZ80CReadPort(0x80, 0x81, YM2203BReadZ80,			NULL);		// YM2203#2
   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0x00, 0x01, YM2203AWriteZ80,		NULL);		// YM2203#1
   AddZ80CWritePort(0x80, 0x81, YM2203BWriteZ80,		NULL);		// YM2203#2
   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(TMP=AllocateMem(0x040000))) return;

   if(!load_rom("12.5n", TMP+0x8000, 0x8000)) return;    // 8x8 FG0 TILES *
   for(ta=0;ta<0x2000;ta++){
      TMP[ta+ta+0x0000]=TMP[ta+0x08000];	// Interleave
      TMP[ta+ta+0x0001]=TMP[ta+0x0A000];
      TMP[ta+ta+0x4000]=TMP[ta+0x0C000];	// Interleave
      TMP[ta+ta+0x4001]=TMP[ta+0x0E000];
   }
   if(!MS1DecodeFG0(TMP,0x08000))return;

   if(!load_rom("nk2_08.rom", TMP+0x20000, 0x10000)) return;  // 16x16 SPRITES *
   if(!load_rom("nk2_07.rom", TMP+0x30000, 0x10000)) return;  // 16x16 SPRITES *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x20000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x24000];
      TMP[ta+ta+0x08000]=TMP[ta+0x28000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x2C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x30000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x34000];
      TMP[ta+ta+0x18000]=TMP[ta+0x38000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x3C000];
   }
   if(!MS1DecodeSPR(TMP,0x20000))return;

   if(!load_rom("nk2_11.rom", TMP+0x20000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("nk2_10.rom", TMP+0x30000, 0x10000)) return;  // 16x16 BG0 *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x20000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x24000];
      TMP[ta+ta+0x08000]=TMP[ta+0x28000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x2C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x30000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x34000];
      TMP[ta+ta+0x18000]=TMP[ta+0x38000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x3C000];
   }
   if(!MS1DecodeBG0(TMP,0x20000))return;

   FreeMem(TMP);

   InitPaletteMap(RAM+0xC800, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k);

   AddSaveData(SAVE_USER_1, (UINT8 *) &sound_byte,          sizeof(sound_byte));

   // Init Video Hardware
   // -------------------

   bg_layers[0].RAM      = RAM+0xD800;
   bg_layers[0].SCR      = RAM+0xC208;
   bg_layers[0].GFX      = GFX_BG0;
   bg_layers[0].MASK     = BG0_Mask;
   bg_layers[0].col_bank = 0x00;
   bg_layers[0].type     = BG_FLIP_XY;

   bg_layers[1].RAM      = NULL;

   bg_layers[2].RAM      = NULL;

   RAM_FG0 = RAM+0xD000;
   mask_fg0 = 0x20;

   RAM_SPR = RAM+0xFA00;
   mask_spr = 0x10;
}

static void load_mnight(void)
{
   UINT8 *TMP;
   int ta;

   romset=2;

   if(!(ROM2=AllocateMem(0x10000))) return;

   RAMSize    = 0x10000+0x10000+0x2000+0x10;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_VIDEO  = RAM+0x10000+0x10000;

   if(!(TMP =AllocateMem(0x28000))) return;

   if(!load_rom("mn6-j19.bin",TMP+0x00000,0x08000)) return;	// Z80 MAIN ROM *
   if(!load_rom("mn5-j17.bin",TMP+0x08000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("mn4-j16.bin",TMP+0x10000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("mn3-j14.bin",TMP+0x18000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("mn2-j12.bin",TMP+0x20000,0x08000)) return;	// Z80 MAIN ROM

#if 1
   // This hack produces garbage on the screen at begining of level 1 !!!
   // Fix ROM Checksum

   TMP[0x388e]=0x18;  // JR xx

   // Skip Idle Z80

   TMP[0x0307]=0xD3;  // OUTA (AAh)
   TMP[0x0308]=0xAA;  //

   SetStopZ80BMode2(0x0309);
#endif

   z80_init_banks_area(1,TMP,0x28000,0x8000,0x4000);

   memset(RAM+0x00000, 0x00, 0x10000);
   memset(RAM+0x0F800, 0xFF, 0x00010);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0010, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC000, 0xF7FF, NULL,			RAM+0xC000);	// RAM/OBJECT/BG0/FG0/COL
   AddZ80BReadByte(0xF800, 0xF80F, NULL,			RAM+0xF800);	// INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC000, 0xF7FF, NULL,			RAM+0xC000);	// RAM/OBJECT/BG0/FG0/COL
   AddZ80BWriteByte(0xFA02, 0xFA02, UPLBankWrite,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xFA00, 0xFA00, UPLSoundWrite,		NULL);		// SOUND
   AddZ80BWriteByte(0xF900, 0xFFFF, NULL,			RAM+0xF900);	// MISC CTRL
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("mn1-j7.bin",ROM2+0x00000,0x10000)) return;	// Z80 SUB ROM

   // Skip Idle Z80

   ROM2[0x00B2]=0xD3;  // OUTA (AAh)
   ROM2[0x00B3]=0xAA;  //

   SetStopZ80CMode2(0x00B2);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xC7FF, NULL,			RAM2+0x0000);	// Z80 ROM/BANK ROM/RAM
   AddZ80CReadByte(0xE000, 0xE000, UPLSoundRead,		NULL);		// SOUND
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xC7FF, NULL,			RAM2+0xC000);	// RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0x01, YM2203AReadZ80,			NULL);		// YM2203#1
   AddZ80CReadPort(0x80, 0x81, YM2203BReadZ80,			NULL);		// YM2203#2
   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0x00, 0x01, YM2203AWriteZ80,		NULL);		// YM2203#1
   AddZ80CWritePort(0x80, 0x81, YM2203BWriteZ80,		NULL);		// YM2203#2
   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(TMP=AllocateMem(0x080000))) return;

   if(!load_rom("mn10-b10.bin", TMP+0x8000, 0x8000)) return;    // 8x8 FG0 TILES *
   for(ta=0;ta<0x2000;ta++){
      TMP[ta+ta+0x0000]=TMP[ta+0x08000];	// Interleave
      TMP[ta+ta+0x0001]=TMP[ta+0x0A000];
      TMP[ta+ta+0x4000]=TMP[ta+0x0C000];	// Interleave
      TMP[ta+ta+0x4001]=TMP[ta+0x0E000];
   }
   if(!MS1DecodeFG0(TMP,0x08000))return;

   if(!load_rom("mn7-e11.bin", TMP+0x30000, 0x10000)) return;  // 16x16 SPR *
   if(!load_rom("mn8-e12.bin", TMP+0x40000, 0x10000)) return;  // 16x16 SPR *
   if(!load_rom("mn9-e14.bin", TMP+0x50000, 0x10000)) return;  // 16x16 SPR *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x30000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x34000];
      TMP[ta+ta+0x08000]=TMP[ta+0x38000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x3C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x40000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x44000];
      TMP[ta+ta+0x18000]=TMP[ta+0x48000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x4C000];
      TMP[ta+ta+0x20000]=TMP[ta+0x50000];	// Interleave
      TMP[ta+ta+0x20001]=TMP[ta+0x54000];
      TMP[ta+ta+0x28000]=TMP[ta+0x58000];	// Interleave
      TMP[ta+ta+0x28001]=TMP[ta+0x5C000];
   }
   if(!MS1DecodeSPR(TMP,0x30000))return;

   if(!load_rom("mn11-b20.bin", TMP+0x30000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("mn12-b22.bin", TMP+0x40000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("mn13-b23.bin", TMP+0x50000, 0x10000)) return;  // 16x16 BG0 *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x30000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x34000];
      TMP[ta+ta+0x08000]=TMP[ta+0x38000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x3C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x40000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x44000];
      TMP[ta+ta+0x18000]=TMP[ta+0x48000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x4C000];
      TMP[ta+ta+0x20000]=TMP[ta+0x50000];	// Interleave
      TMP[ta+ta+0x20001]=TMP[ta+0x54000];
      TMP[ta+ta+0x28000]=TMP[ta+0x58000];	// Interleave
      TMP[ta+ta+0x28001]=TMP[ta+0x5C000];
   }
   if(!MS1DecodeBG0(TMP,0x30000))return;

   FreeMem(TMP);

   InitPaletteMap(RAM+0xF000, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k);

   AddSaveData(SAVE_USER_1, (UINT8 *) &sound_byte,          sizeof(sound_byte));

   // Init Video Hardware
   // -------------------

   bg_layers[0].RAM      = RAM+0xE000;
   bg_layers[0].SCR      = RAM+0xFA08;
   bg_layers[0].GFX      = GFX_BG0;
   bg_layers[0].MASK     = BG0_Mask;
   bg_layers[0].col_bank = 0x00;
   bg_layers[0].type     = BG_FLIP_X;

   bg_layers[1].RAM      = NULL;

   bg_layers[2].RAM      = NULL;

   RAM_FG0 = RAM+0xE800;
   mask_fg0 = 0x20;

   RAM_SPR = RAM+0xDA00;
   mask_spr = 0x10;
}

static void load_arkarea(void)
{
   UINT8 *TMP;
   int ta;

   romset=4;

   if(!(ROM2=AllocateMem(0x10000))) return;

   RAMSize    = 0x10000+0x10000+0x2000+0x10;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_VIDEO  = RAM+0x10000+0x10000;

   if(!(TMP =AllocateMem(0x28000))) return;

   if(!load_rom("arkarea.008",TMP+0x00000,0x08000)) return;	// Z80 MAIN ROM *
   if(!load_rom("arkarea.009",TMP+0x08000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("arkarea.010",TMP+0x10000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("arkarea.011",TMP+0x18000,0x08000)) return;	// Z80 MAIN ROM
   if(!load_rom("arkarea.012",TMP+0x20000,0x08000)) return;	// Z80 MAIN ROM

   // Skip Idle Z80

   TMP[0x043A]=0xD3;  // OUTA (AAh)
   TMP[0x043B]=0xAA;  //

   SetStopZ80BMode2(0x043C);

   z80_init_banks_area(1,TMP,0x28000,0x8000,0x4000);

   memset(RAM+0x00000, 0x00, 0x10000);
   memset(RAM+0x0F800, 0xFF, 0x00010);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0010, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM/BANK ROM
   AddZ80BReadByte(0xC000, 0xF7FF, NULL,			RAM+0xC000);	// RAM/OBJECT/BG0/FG0/COL
   AddZ80BReadByte(0xF800, 0xF80F, NULL,			RAM+0xF800);	// INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xC000, 0xF7FF, NULL,			RAM+0xC000);	// RAM/OBJECT/BG0/FG0/COL
   AddZ80BWriteByte(0xFA02, 0xFA02, UPLBankWrite,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xFA00, 0xFA00, UPLSoundWrite,		NULL);		// SOUND
   AddZ80BWriteByte(0xF900, 0xFFFF, NULL,			RAM+0xF900);	// MISC CTRL
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("arkarea.013",ROM2+0x00000,0x8000)) return;	// Z80 SUB ROM

   // Skip Idle Z80

   ROM2[0x00B2]=0xD3;  // OUTA (AAh)
   ROM2[0x00B3]=0xAA;  //

   SetStopZ80CMode2(0x00B2);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xC7FF, NULL,			RAM2+0x0000);	// Z80 ROM/BANK ROM/RAM
   AddZ80CReadByte(0xE000, 0xE000, UPLSoundRead,		NULL);		// SOUND
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xC7FF, NULL,			RAM2+0xC000);	// RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0x01, YM2203AReadZ80,			NULL);		// YM2203#1
   AddZ80CReadPort(0x80, 0x81, YM2203BReadZ80,			NULL);		// YM2203#2
   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0x00, 0x01, YM2203AWriteZ80,		NULL);		// YM2203#1
   AddZ80CWritePort(0x80, 0x81, YM2203BWriteZ80,		NULL);		// YM2203#2
   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(TMP=AllocateMem(0x080000))) return;

   if(!load_rom("arkarea.004", TMP+0x8000, 0x8000)) return;    // 8x8 FG0 TILES *
   for(ta=0;ta<0x2000;ta++){
      TMP[ta+ta+0x0000]=TMP[ta+0x08000];	// Interleave
      TMP[ta+ta+0x0001]=TMP[ta+0x0A000];
      TMP[ta+ta+0x4000]=TMP[ta+0x0C000];	// Interleave
      TMP[ta+ta+0x4001]=TMP[ta+0x0E000];
   }
   if(!MS1DecodeFG0(TMP,0x08000))return;

   if(!load_rom("arkarea.007", TMP+0x40000, 0x10000)) return;  // 16x16 SPR *
   if(!load_rom("arkarea.006", TMP+0x50000, 0x10000)) return;  // 16x16 SPR *
   if(!load_rom("arkarea.005", TMP+0x60000, 0x10000)) return;  // 16x16 BG0 *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x40000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x44000];
      TMP[ta+ta+0x08000]=TMP[ta+0x48000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x4C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x50000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x54000];
      TMP[ta+ta+0x18000]=TMP[ta+0x58000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x5C000];
      TMP[ta+ta+0x20000]=TMP[ta+0x60000];	// Interleave
      TMP[ta+ta+0x20001]=TMP[ta+0x64000];
      TMP[ta+ta+0x28000]=TMP[ta+0x68000];	// Interleave
      TMP[ta+ta+0x28001]=TMP[ta+0x6C000];
   }
   if(!MS1DecodeSPR(TMP,0x30000))return;

   if(!load_rom("arkarea.003", TMP+0x40000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("arkarea.002", TMP+0x50000, 0x10000)) return;  // 16x16 BG0 *
   if(!load_rom("arkarea.001", TMP+0x60000, 0x10000)) return;  // 16x16 BG0 *
   for(ta=0;ta<0x4000;ta++){
      TMP[ta+ta+0x00000]=TMP[ta+0x40000];	// Interleave
      TMP[ta+ta+0x00001]=TMP[ta+0x44000];
      TMP[ta+ta+0x08000]=TMP[ta+0x48000];	// Interleave
      TMP[ta+ta+0x08001]=TMP[ta+0x4C000];
      TMP[ta+ta+0x10000]=TMP[ta+0x50000];	// Interleave
      TMP[ta+ta+0x10001]=TMP[ta+0x54000];
      TMP[ta+ta+0x18000]=TMP[ta+0x58000];	// Interleave
      TMP[ta+ta+0x18001]=TMP[ta+0x5C000];
      TMP[ta+ta+0x20000]=TMP[ta+0x60000];	// Interleave
      TMP[ta+ta+0x20001]=TMP[ta+0x64000];
      TMP[ta+ta+0x28000]=TMP[ta+0x68000];	// Interleave
      TMP[ta+ta+0x28001]=TMP[ta+0x6C000];
   }
   if(!MS1DecodeBG0(TMP,0x30000))return;

   FreeMem(TMP);

   InitPaletteMap(RAM+0xF000, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k);

   AddSaveData(SAVE_USER_1, (UINT8 *) &sound_byte,          sizeof(sound_byte));

   // Init Video Hardware
   // -------------------

   bg_layers[0].RAM      = RAM+0xE000;
   bg_layers[0].SCR      = RAM+0xFA08;
   bg_layers[0].GFX      = GFX_BG0;
   bg_layers[0].MASK     = BG0_Mask;
   bg_layers[0].col_bank = 0x00;
   bg_layers[0].type     = BG_FLIP_X;

   bg_layers[1].RAM      = NULL;

   bg_layers[2].RAM      = NULL;

   RAM_FG0 = RAM+0xE800;
   mask_fg0 = 0x20;

   RAM_SPR = RAM+0xDA00;
   mask_spr = 0x10;
}

static void load_omegaf(void)
{
   UINT8 *TMP;

   romset=3;

   if(!(ROM2=AllocateMem(0x10000))) return;

   RAMSize    = 0x10000+0x10000+(0x2000*4)+0x10;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM_VIDEO  = RAM+0x10000+0x10000;

   if(!(TMP =AllocateMem(0x40000))) return;

   if(!load_rom_index(4,TMP+0x00000,0x20000)) return;	// Z80 MAIN ROM *
   if(!load_rom_index(5,TMP+0x20000,0x20000)) return;	// Z80 MAIN ROM

   // Fix Input Protection

   TMP[0x029a]=0x00;
   TMP[0x029b]=0x00;

   TMP[0x02a6]=0x00;
   TMP[0x02a7]=0x00;

   TMP[0x02b2]=0xC9;

   TMP[0x02b5]=0xC9;

   TMP[0x02c9]=0xC9;

   TMP[0x02f6]=0xC9;

   TMP[0x05f0]=0x00;

   TMP[0x054c]=0x04;

   TMP[0x0557]=0x03;

   // Fix ROM Checksum

   TMP[0x0b8d]=0x00;
   TMP[0x0b8e]=0x00;
   TMP[0x0b8f]=0x00;

   if(is_current_game("omegaf")){

   // Skip Idle Z80

   TMP[0x1cd1]=0xd9;
   TMP[0x1cd2]=0x05;

   TMP[0x05d9]=0xD3;  // OUTA (AAh)
   TMP[0x05da]=0xAA;  //

   TMP[0x05db]=0xc3;
   TMP[0x05dc]=0xcc;
   TMP[0x05dd]=0x1c;

   TMP[0x06d8]=0xD3;  // OUTA (AAh)
   TMP[0x06d9]=0xAA;  //
   TMP[0x06da]=0x00;  //

   }
   else{

   // Skip Idle Z80

   TMP[0x1cae]=0xd9;
   TMP[0x1caf]=0x05;

   TMP[0x05d9]=0xD3;  // OUTA (AAh)
   TMP[0x05da]=0xAA;  //

   TMP[0x05db]=0xc3;
   TMP[0x05dc]=0xa9;
   TMP[0x05dd]=0x1c;

   TMP[0x06d8]=0xD3;  // OUTA (AAh)
   TMP[0x06d9]=0xAA;  //
   TMP[0x06da]=0x00;  //

   }
   init_bank_rom(TMP,ROM);

   memset(RAM+0x00000, 0x00, 0x10000);
   //memset(RAM+0x0C000, 0xFF, 0x00010);
   memcpy(RAM, TMP, 0x8000+0x4000);

   AddZ80BROMBase(RAM, 0x0010, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM/BANK ROM
   AddZ80BReadByte(0xD000, 0xFFFF, NULL,			RAM+0xD000);	// COLOR/FG0/BG0/RAM/OBJECT
   AddZ80BReadByte(0xC400, 0xCFFF, OmegaBG012Read,		NULL);		// BG0-2 RAM
   AddZ80BReadByte(0xC000, 0xC00F, NULL,			RAM+0xC000);	// INPUT
   AddZ80BReadByte(0xC100, 0xC3FF, NULL,			RAM+0xC100);	// INPUT
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   AddZ80BWriteByte(0xD000, 0xFFFF, NULL,			RAM+0xD000);	// COLOR/FG0/BG0/RAM/OBJECT
   AddZ80BWriteByte(0xC400, 0xCFFF, OmegaBG012Write,		NULL);		// BG0-2 RAM
   AddZ80BWriteByte(0xC002, 0xC002, UPLBankWrite,		NULL);		// ROM BANK
   AddZ80BWriteByte(0xC000, 0xC000, UPLSoundWrite,		NULL);		// SOUND
   AddZ80BWriteByte(0xC105, 0xC105, OmegaBG0BankWrite,		NULL);		// BG0 BANK
   AddZ80BWriteByte(0xC205, 0xC205, OmegaBG1BankWrite,		NULL);		// BG1 BANK
   AddZ80BWriteByte(0xC305, 0xC305, OmegaBG2BankWrite,		NULL);		// BG2 BANK
   AddZ80BWriteByte(0xC100, 0xC3FF, NULL,			RAM+0xC100);	// MISC CTRL
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80BWritePort(-1, -1, NULL, NULL);

   AddZ80BInit();

   if(!load_rom("7.7m",ROM2+0x00000,0x10000)) return;	// Z80 SUB ROM

   // Skip Idle Z80
   // -------------

   ROM2[0x00B2]=0xD3;  // OUTA (AAh)
   ROM2[0x00B3]=0xAA;  //

   SetStopZ80CMode2(0x00B2);

   memset(RAM2+0x00000, 0x00, 0x10000);
   memcpy(RAM2, ROM2, 0x8000+0x4000);

   AddZ80CROMBase(RAM2, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xC7FF, NULL,			RAM2+0x0000);	// Z80 ROM/BANK ROM/RAM
   AddZ80CReadByte(0xE000, 0xE000, UPLSoundRead,		NULL);		// SOUND
   AddZ80CReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);		// <bad reads>
   AddZ80CReadByte(-1, -1, NULL, NULL);

   AddZ80CWriteByte(0xC000, 0xC7FF, NULL,			RAM2+0xC000);	// RAM
   AddZ80CWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);		// <bad writes>
   AddZ80CWriteByte(-1, -1, NULL, NULL);

   AddZ80CReadPort(0x00, 0x01, YM2203AReadZ80,			NULL);		// YM2203#1
   AddZ80CReadPort(0x80, 0x81, YM2203BReadZ80,			NULL);		// YM2203#2
   AddZ80CReadPort(0x00, 0xFF, DefBadReadZ80,			NULL);		// <bad reads>
   AddZ80CReadPort(-1, -1, NULL, NULL);

   AddZ80CWritePort(0x00, 0x01, YM2203AWriteZ80,		NULL);		// YM2203#1
   AddZ80CWritePort(0x80, 0x81, YM2203BWriteZ80,		NULL);		// YM2203#2
   AddZ80CWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, DefBadWriteZ80,			NULL);		// <bad writes>
   AddZ80CWritePort(-1, -1, NULL, NULL);

   AddZ80CInit();

   FreeMem(TMP);

   /*-----------------------*/

   if(!(TMP=AllocateMem(0x80000))) return;

   if(!load_rom("4.18h", TMP+0x00000, 0x08000)) return;    // 8x8 FG0 TILES *
   if(!MS1DecodeFG0(TMP,0x08000))return;

   if(!load_rom("8.23m", TMP+0x00000, 0x20000)) return;  // 16x16 SPR *
   if(!MS1DecodeSPR_TypeB(TMP,0x20000))return;

   if(!load_rom("1back2.15b", TMP+0x00000, 0x80000)) return;  // 16x16 BG0 *
   if(!MS1DecodeBG1_TypeB(TMP,0x80000))return;

   if(!load_rom("2back1.27b", TMP+0x00000, 0x80000)) return;  // 16x16 BG0 *
   if(!MS1DecodeBG0_TypeB(TMP,0x80000))return;

   if(!load_rom("3back3.5f", TMP+0x00000, 0x80000)) return;  // 16x16 BG0 *
   if(!MS1DecodeBG2_TypeB(TMP,0x80000))return;

   FreeMem(TMP);

   OmegaBG012Init();

   InitPaletteMap(RAM+0xD800, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx_68k);

   AddSaveData(SAVE_USER_1, (UINT8 *) &sound_byte,          sizeof(sound_byte));

   // Init Video Hardware
   // -------------------

   bg_layers[0].RAM      = RAM_VIDEO+0x2000;
   bg_layers[0].SCR      = RAM+0xC100;
   bg_layers[0].GFX      = GFX_BG0;
   bg_layers[0].MASK     = BG0_Mask;
   bg_layers[0].col_bank = 0x00;
   bg_layers[0].type     = BG_FLIP_NONE;

   bg_layers[1].RAM      = RAM_VIDEO+0x4000;
   bg_layers[1].SCR      = RAM+0xC200;
   bg_layers[1].GFX      = GFX_BG1;
   bg_layers[1].MASK     = BG1_Mask;
   bg_layers[1].col_bank = 0x00;
   bg_layers[1].type     = BG_FLIP_NONE;

   bg_layers[2].RAM      = RAM_VIDEO+0x6000;
   bg_layers[2].SCR      = RAM+0xC300;
   bg_layers[2].GFX      = GFX_BG2;
   bg_layers[2].MASK     = BG2_Mask;
   bg_layers[2].col_bank = 0x00;
   bg_layers[2].type     = BG_FLIP_NONE;

   RAM_FG0 = RAM+0xD000;
   mask_fg0 = 0x30;

   RAM_SPR = RAM+0xFA00;
   mask_spr = 0x20;
}

#define FRAME1 CPU_FRAME_MHz(3,60)
#define FRAME2 CPU_FRAME_MHz(2,60)

static void execute_arkarea(void)
{
  cpu_execute_cycles(CPU_Z80_1, FRAME1);	// Main Z80 12MHz (60fps)
   cpu_execute_cycles(CPU_Z80_2, FRAME2);	// Sub Z80 6MHz (60fps)
      print_debug("Z80PC_SUB:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_2, 0x38);

   cpu_execute_cycles(CPU_Z80_1, FRAME1);	// Main Z80 12MHz (60fps)
   print_debug("Z80PC_MAIN:%04x [%04x]\n",z80pc,ReadWord(&RAM[0xE000]));

   cpu_execute_cycles(CPU_Z80_2, FRAME2);	// Sub Z80 6MHz (60fps)
   print_debug("Z80PC_SUB:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_2, 0x38);

   cpu_interrupt(CPU_Z80_1,0x10);
}

static UINT16 bg_map[0x10] =
{
  0x0000+0x0000+0x0000+0x0000,	// 0x00
  0x0800+0x0000+0x0000+0x0000,	// 0x10
  0x0000+0x0400+0x0000+0x0000,	// 0x20
  0x0800+0x0400+0x0000+0x0000,	// 0x30
  0x0000+0x0000+0x0100+0x0000,	// 0x40
  0x0800+0x0000+0x0100+0x0000,	// 0x50
  0x0000+0x0400+0x0100+0x0000,	// 0x60
  0x0800+0x0400+0x0100+0x0000,	// 0x70
  0x0000+0x0000+0x0000+0x0200,	// 0x80
  0x0800+0x0000+0x0000+0x0200,	// 0x90
  0x0000+0x0400+0x0000+0x0200,	// 0xA0
  0x0800+0x0400+0x0000+0x0200,	// 0xB0
  0x0000+0x0000+0x0100+0x0200,	// 0xC0
  0x0800+0x0000+0x0100+0x0200,	// 0xD0
  0x0000+0x0400+0x0100+0x0200,	// 0xE0
  0x0800+0x0400+0x0100+0x0200,	// 0xF0
};

static UINT16 bg_map_b[0x10] =
{
  0x0000+0x0000+0x0000+0x0000,	// 0x00
  0x0000+0x0000+0x0000+0x0000,	// 0x10
  0x0000+0x0400+0x0000+0x0000,	// 0x20
  0x0000+0x0400+0x0000+0x0000,	// 0x30
  0x0000+0x0000+0x0100+0x0000,	// 0x40
  0x0000+0x0000+0x0100+0x0000,	// 0x50
  0x0000+0x0400+0x0100+0x0000,	// 0x60
  0x0000+0x0400+0x0100+0x0000,	// 0x70
  0x0000+0x0000+0x0000+0x0200,	// 0x80
  0x0000+0x0000+0x0000+0x0200,	// 0x90
  0x0000+0x0400+0x0000+0x0200,	// 0xA0
  0x0000+0x0400+0x0000+0x0200,	// 0xB0
  0x0000+0x0000+0x0100+0x0200,	// 0xC0
  0x0000+0x0000+0x0100+0x0200,	// 0xD0
  0x0000+0x0400+0x0100+0x0200,	// 0xE0
  0x0000+0x0400+0x0100+0x0200,	// 0xF0
};

static UINT16 bg_map_c[0x10] =
{
  0x0000+0x0000+0x0000+0x0000,	// 0x00
  0x0400+0x0000+0x0000+0x0000,	// 0x10
  0x0000+0x0000+0x0000+0x0000,	// 0x20
  0x0400+0x0000+0x0000+0x0000,	// 0x30
  0x0000+0x0000+0x0100+0x0000,	// 0x40
  0x0400+0x0000+0x0100+0x0000,	// 0x50
  0x0000+0x0000+0x0100+0x0000,	// 0x60
  0x0400+0x0000+0x0100+0x0000,	// 0x70
  0x0000+0x0000+0x0000+0x0200,	// 0x80
  0x0400+0x0000+0x0000+0x0200,	// 0x90
  0x0000+0x0000+0x0000+0x0200,	// 0xA0
  0x0400+0x0000+0x0000+0x0200,	// 0xB0
  0x0000+0x0000+0x0100+0x0200,	// 0xC0
  0x0400+0x0000+0x0100+0x0200,	// 0xD0
  0x0000+0x0000+0x0100+0x0200,	// 0xE0
  0x0400+0x0000+0x0100+0x0200,	// 0xF0
};

int bg_layer_count;

static void DrawUPLLayer(int num)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *SCR_BG;
   UINT8 *GFX_BG;
   UINT8 *MSK_BG;
   UINT8 col_bank;

   if(bg_layers[num].RAM != NULL){

   RAM_BG   = bg_layers[num].RAM;
   SCR_BG   = bg_layers[num].SCR;
   GFX_BG   = bg_layers[num].GFX;
   MSK_BG   = bg_layers[num].MASK;
   col_bank = bg_layers[num].col_bank;

   switch(bg_layers[num].type){
   case BG_FLIP_NONE:

   if(bg_layer_count==0){	// ----------------------- [No flip bits, and solid]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | bg_map[RAM_BG[zz+1]>>4];

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);

   END_SCROLL_512x512_2_16();

   }
   else{	// --------------------------------- [No flip bits, and transparent]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | bg_map[RAM_BG[zz+1]>>4];
      if(MSK_BG[ta]!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         if(MSK_BG[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }
         else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }

      }

   END_SCROLL_512x512_2_16();

   }
   break;
   case BG_FLIP_Y:

   if(bg_layer_count==0){	// ------------------------- [flip y bit, and solid]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | bg_map_b[RAM_BG[zz+1]>>4];

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         switch(RAM_BG[zz+1]&0x10){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_BG[ta<<8], x, y, map);  break;
         }

   END_SCROLL_512x512_2_16();

   }
   else{	// ----------------------------------- [flip y bit, and transparent]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | bg_map_b[RAM_BG[zz+1]>>4];
      if(MSK_BG[ta]!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         if(MSK_BG[ta]==1){				// Some pixels; trans
            switch(RAM_BG[zz+1]&0x10){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_BG[zz+1]&0x10){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            }
         }

      }

   END_SCROLL_512x512_2_16();

   }
   break;
   case BG_FLIP_X:

   if(bg_layer_count==0){	// ------------------------- [flip x bit, and solid]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | bg_map_c[RAM_BG[zz+1]>>4];

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         switch(RAM_BG[zz+1]&0x20){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_BG[ta<<8], x, y, map);  break;
         }

   END_SCROLL_512x512_2_16();

   }
   else{	// ----------------------------------- [flip x bit, and transparent]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | bg_map_c[RAM_BG[zz+1]>>4];
      if(MSK_BG[ta]!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         if(MSK_BG[ta]==1){				// Some pixels; trans
            switch(RAM_BG[zz+1]&0x20){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x20: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_BG[zz+1]&0x10){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            }
         }

      }

   END_SCROLL_512x512_2_16();

   }
   break;
   case BG_FLIP_XY:

   if(bg_layer_count==0){	// --------------------- [both flip bits, and solid]

      MAKE_SCROLL_512x512_2_16(
         ReadWord(&SCR_BG[0]),
         ReadWord(&SCR_BG[2])+32
      );

      START_SCROLL_512x512_2_16(32,32,256,192);

         ta = RAM_BG[zz+0] | ((RAM_BG[zz+1]<<2)&0x0300);

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         switch(RAM_BG[zz+1]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG[ta<<8], x, y, map); break;
         }

      END_SCROLL_512x512_2_16();

   }
   else{	// ------------------------------- [both flip bits, and transparent]

   MAKE_SCROLL_512x512_2_16(
      ReadWord(&SCR_BG[0]),
      ReadWord(&SCR_BG[2])+32
   );

   START_SCROLL_512x512_2_16(32,32,256,192);

      ta = RAM_BG[zz+0] | ((RAM_BG[zz+1]<<2)&0x0300);
      if(MSK_BG[ta]!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         if(MSK_BG[ta]==1){				// Some pixels; trans
            switch(RAM_BG[zz+1]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_BG[ta<<8], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_BG[zz+1]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_BG[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_BG[ta<<8], x, y, map); break;
            }
         }

      }

   END_SCROLL_512x512_2_16();

   }
   break;
   }

   bg_layer_count++;

   }

}

static void draw_upl_fg0(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   UINT8 *map;

   MAKE_SCROLL_256x256_2_8(
       0,
       32
   );

   START_SCROLL_256x256_2_8(32,32,256,192);

      ta = RAM_FG0[0+zz] | ((RAM_FG0[1+zz]<<2)&0x0300);
      if(FG0_Mask[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_FG0[1+zz]&0x0F)|mask_fg0,
            16,
            map
         );

         if(FG0_Mask[ta]==1){				// Some pixels; trans
            switch(RAM_FG0[1+zz]&0x30){
            case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);        break;
            case 0x10: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x20: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x30: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_FG0[ta<<6], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_FG0[1+zz]&0x30){
            case 0x00: Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6], x, y, map);        break;
            case 0x10: Draw8x8_Mapped_FlipY_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x20: Draw8x8_Mapped_FlipX_Rot(&GFX_FG0[ta<<6], x, y, map);  break;
            case 0x30: Draw8x8_Mapped_FlipXY_Rot(&GFX_FG0[ta<<6], x, y, map); break;
            }
         }
      }

   END_SCROLL_256x256_2_8();
}

static void DrawUPL(void)
{
   int zz,x,y,ta,rr,xx,yy;
   UINT8 *map;

   ClearPaletteMap();

   bg_layer_count=0;

   DrawUPLLayer(0);

   DrawUPLLayer(1);

   DrawUPLLayer(2);

   // OBJECT
   // ------

   for(zz=0x0000;zz<0x0600;zz+=16){

      if((RAM_SPR[zz+0x0D]&2)){

      x = (32 + RAM_SPR[zz+0x0C] + ((RAM_SPR[zz+0x0D]<<8)&0x0100))&0x1FF;
      y = ( 0 + RAM_SPR[zz+0x0B])&0x0FF;

      ta  = RAM_SPR[zz+0x0E] | ((RAM_SPR[zz+0x0D]<<2)&0x0300) | ((RAM_SPR[zz+0x0D]<<7)&0x0400);

      MAP_PALETTE_MAPPED_NEW(
         (RAM_SPR[zz+0x0F]&0x0F)|mask_spr,
         16,
         map
      );

      if((RAM_SPR[zz+0x0D]&4)!=0){
         switch(RAM_SPR[zz+0x0D]&0x30){
         case 0x00:

         yy=2;
         rr=x;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         x=(x+16)&0x1FF;
         }while(--xx);

         y=(y+16)&0xFF;
         x=rr;
         }while(--yy);

         break;
         case 0x20:

         y+=16;

         yy=2;
         rr=x;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipX_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         x=(x+16)&0x1FF;
         }while(--xx);

         y=(y-16)&0xFF;
         x=rr;
         }while(--yy);

         break;
         case 0x10:

         x+=16;

         yy=2;
         rr=x;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipY_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         x=(x-16)&0x1FF;
         }while(--xx);

         y=(y+16)&0xFF;
         x=rr;
         }while(--yy);

         break;
         case 0x30:

         x+=16;
         y+=16;

         yy=2;
         rr=x;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipXY_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         x=(x-16)&0x1FF;
         }while(--xx);

         y=(y-16)&0xFF;
         x=rr;
         }while(--yy);

         break;
         }

      }
      else{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1){				// Some pixels; trans
            switch(RAM_SPR[zz+0x0D]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_SPR[zz+0x0D]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x10: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x20: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }

         }
         }

      }

      // kludge to clear shots (based on mame source)
	if (((RAM_SPR[zz+0x0D]==2) || (RAM_SPR[zz+0x0D]==0x12)) &&
         (((ta>=0xd0) && (ta<=0xd5)) || ((ta>=0x20) && (ta<=0x25))))
	  RAM_SPR[zz+0x0D]=0;

      }

   }

   draw_upl_fg0();
}

static void draw_omega_fighter(void)
{
   int zz,zzz,zzzz,x16,y16,x,y,ta;
   int xx,yy,rr;
   UINT8 *map;
   UINT8 *RAM_BG;
   UINT8 *SCR_BG;
   UINT8 *GFX_BG;
   UINT8 *MSK_BG;
   UINT8 col_bank;

   ClearPaletteMap();

   bg_layer_count=0;

   // BG0
   // ---
   RAM_BG   = bg_layers[0].RAM;
   SCR_BG   = bg_layers[0].SCR;
   GFX_BG   = bg_layers[0].GFX;
   MSK_BG   = bg_layers[0].MASK;
   col_bank = bg_layers[0].col_bank;

   if(RAM_BG!=NULL){

   zzz=(ReadWord(&SCR_BG[0]));
   zzzz =((zzz&0x00F0)>>4)<<1;                  // X Offset (16-255)
   zzzz+=((zzz&0x0700)>>4)<<6;                  // X Offset (256-511)
   x16=zzz&15;                                  // X Offset (0-15)
   zzz=(ReadWord(&SCR_BG[2])+32);
   zzzz+=((zzz&0x01F0)>>4)<<5;                  // Y Offset (16-511)
   y16=zzz&15;                                  // Y Offset (0-15)

   zzzz=zzzz&0x1FFF;
   zz=zzzz;
   for(y=(32-y16);y<(192+32);y+=16){
   for(x=(32-x16);x<(256+32);x+=16){

      ta = RAM_BG[zz+0] | bg_map[RAM_BG[zz+1]>>4];

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);

   zz+=2;
   if((zz&0x1F)==0){zz+=0x3E0;zz&=0x1FFF;}
   }
   zzzz+=0x20;
   if((zzzz&0x3E0)==0){zzzz-=0x400;}
   zzzz&=0x1FFF;
   zz=zzzz;
   }

   }

   // BG1
   // ---
   RAM_BG   = bg_layers[1].RAM;
   SCR_BG   = bg_layers[1].SCR;
   GFX_BG   = bg_layers[1].GFX;
   MSK_BG   = bg_layers[1].MASK;
   col_bank = bg_layers[1].col_bank;

   if(RAM_BG!=NULL){

   zzz=(ReadWord(&SCR_BG[0]));
   zzzz =((zzz&0x00F0)>>4)<<1;                  // X Offset (16-255)
   zzzz+=((zzz&0x0700)>>4)<<6;                  // X Offset (256-511)
   x16=zzz&15;                                  // X Offset (0-15)
   zzz=(ReadWord(&SCR_BG[2])+32);
   zzzz+=((zzz&0x01F0)>>4)<<5;                  // Y Offset (16-511)
   y16=zzz&15;                                  // Y Offset (0-15)

   zzzz=zzzz&0x1FFF;
   zz=zzzz;
   for(y=(32-y16);y<(192+32);y+=16){
   for(x=(32-x16);x<(256+32);x+=16){

      ta = RAM_BG[zz+0] | bg_map[RAM_BG[zz+1]>>4];
      if(MSK_BG[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         if(MSK_BG[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }
         else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }

      }

   zz+=2;
   if((zz&0x1F)==0){zz+=0x3E0;zz&=0x1FFF;}
   }
   zzzz+=0x20;
   if((zzzz&0x3E0)==0){zzzz-=0x400;}
   zzzz&=0x1FFF;
   zz=zzzz;
   }

   }

   // BG2
   // ---
   RAM_BG   = bg_layers[2].RAM;
   SCR_BG   = bg_layers[2].SCR;
   GFX_BG   = bg_layers[2].GFX;
   MSK_BG   = bg_layers[2].MASK;
   col_bank = bg_layers[2].col_bank;

   if(RAM_BG!=NULL){

   zzz=(ReadWord(&SCR_BG[0]));
   zzzz =((zzz&0x00F0)>>4)<<1;                  // X Offset (16-255)
   zzzz+=((zzz&0x0700)>>4)<<6;                  // X Offset (256-511)
   x16=zzz&15;                                  // X Offset (0-15)
   zzz=(ReadWord(&SCR_BG[2])+32);
   zzzz+=((zzz&0x01F0)>>4)<<5;                  // Y Offset (16-511)
   y16=zzz&15;                                  // Y Offset (0-15)

   zzzz=zzzz&0x1FFF;
   zz=zzzz;
   for(y=(32-y16);y<(192+32);y+=16){
   for(x=(32-x16);x<(256+32);x+=16){

      ta = RAM_BG[zz+0] | bg_map[RAM_BG[zz+1]>>4];
      if(MSK_BG[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz+1]&0x0F)|col_bank,
            16,
            map
         );

         if(MSK_BG[ta]==1){				// Some pixels; trans
         Draw16x16_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }
         else{						// all pixels; solid
         Draw16x16_Mapped_Rot(&GFX_BG[ta<<8], x, y, map);
         }

      }

   zz+=2;
   if((zz&0x1F)==0){zz+=0x3E0;zz&=0x1FFF;}
   }
   zzzz+=0x20;
   if((zzzz&0x3E0)==0){zzzz-=0x400;}
   zzzz&=0x1FFF;
   zz=zzzz;
   }

   }

   // OBJECT
   // ------

   for(zz=0x0000;zz<0x0600;zz+=16){

      if((RAM_SPR[zz+0x0D]&2)!=0){

      x = (32 + RAM_SPR[zz+0x0C] + ((RAM_SPR[zz+0x0D]<<8)&0x0100))&0x1FF;
      y = ( 0 + RAM_SPR[zz+0x0B])&0x0FF;

      ta = RAM_SPR[zz+0x0E] | ((RAM_SPR[zz+0x0D]<<2)&0x0300) | ((RAM_SPR[zz+0x0D]<<7)&0x0400);

      MAP_PALETTE_MAPPED_NEW(
         (RAM_SPR[zz+0x0F]&0x0F)|mask_spr,
         16,
         map
      );

      if((RAM_SPR[zz+0x0D]&4)!=0){
         ta &= ~3;
         switch(RAM_SPR[zz+0x0D]&0x30){
         case 0x00:

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y+16)&0xFF;
         }while(--xx);

         x=(x+16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         case 0x20:

         x+=16;

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipY_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y+16)&0xFF;
         }while(--xx);

         x=(x-16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         case 0x10:

         y+=16;

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipX_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y-16)&0xFF;
         }while(--xx);

         x=(x+16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         case 0x30:

         x+=16;
         y+=16;

         yy=2;
         rr=y;
         do{
         xx=2;
         do{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1) Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map);
         else                Draw16x16_Mapped_FlipXY_Rot(      &GFX_SPR[ta<<8], x, y, map);

         }
         }

         ta++;
         y=(y-16)&0xFF;
         }while(--xx);

         x=(x-16)&0x1FF;
         y=rr;
         }while(--yy);

         break;
         }

      }
      else{

         if((x>16)&&(y>16)&&(x<256+32)&&(y<192+32)){

         if(SPR_Mask[ta]!=0){			// No pixels; skip

         if(SPR_Mask[ta]==1){				// Some pixels; trans
            switch(RAM_SPR[zz+0x0D]&0x30){
            case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x20: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x10: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_SPR[zz+0x0D]&0x30){
            case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8], x, y, map);        break;
            case 0x20: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x10: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map);  break;
            case 0x30: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map); break;
            }
         }

         }
         }

      }

      }

   }

   draw_upl_fg0();

}

static struct VIDEO_INFO video_arkarea =
{
   DrawUPL,
   256,
   192,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct VIDEO_INFO video_omegaf =
{
   draw_omega_fighter,
   256,
   192,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_arkarea[] =
{
   { "ark_area", },
   { "arkarea", },
   { NULL, },
};
GME( arkarea, "Ark Area", UPL, 1987, GAME_SHOOT);
static struct DIR_INFO dir_mnight[] =
{
   { "mutant_night", },
   { "mnight", },
   { NULL, },
};
GAME( mnight, "Mutant Night", UPL, 1987, GAME_SHOOT|GAME_PARTIALLY_WORKING,
	.input = input_arkarea,
	.dsw = dsw_mnight,
	.video = &video_arkarea,
	.exec = execute_arkarea,
	.long_name_jpn = "ミュータントナイト",
);
static struct DIR_INFO dir_ninjakd2[] =
{
   { "ninja_kid_2", },
   { "ninjakd2", },
   { "ninjak2a", },
   { NULL, },
};
GAME( ninjakd2, "Ninja Kid 2", UPL, 1987, GAME_PLATFORM,
	.input = input_ninjakd2,
	.dsw = dsw_ninjakd2,
	.video = &video_arkarea,
	.exec = execute_arkarea,
);
static struct DIR_INFO dir_omegafs[] =
{
   { "omega_fighter_special", },
   { "omegafs", },
   { "omgfigts", },
   { ROMOF("omegaf"), },
   { CLONEOF("omegaf"), },
   { NULL, },
};
CLONE(omegafs, omegaf, "Omega Fighter Special", UPL, 1989, GAME_SHOOT,
	.input = input_omegaf,
	.dsw = dsw_omegaf,
	.video = &video_omegaf,
	.exec = execute_arkarea,
	.long_name_jpn = "オメガファイター Special",
	.board = "UPL-89016",
);
static struct DIR_INFO dir_omegaf[] =
{
   { "omega_fighter", },
   { "omegaf", },
   { "omgfight", },
   { NULL, },
};
GAME( omegaf, "Omega Fighter", UPL, 1989, GAME_SHOOT,
	.input = input_omegaf,
	.dsw = dsw_omegaf,
	.video = &video_omegaf,
	.exec = execute_arkarea,
	.long_name_jpn = "オメガファイター",
	.board = "UPL-89016",
);
static struct DIR_INFO dir_rdaction[] =
{
   { "rad_action", },
   { "radactn", },
   { "rdaction", },
   { ROMOF("ninjakd2"), },
   { CLONEOF("ninjakd2"), },
   { NULL, },
};
GAME(rdaction, "Rad Action", UPL, 1987, GAME_PLATFORM,
	.input = input_ninjakd2,
	.dsw = dsw_ninjakd2,
	.video = &video_arkarea,
	.exec = execute_arkarea,
);

