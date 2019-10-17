#define DRV_DEF_SOUND taito_ym2610_sound
#define DRV_DEF_EXEC execute_yuyugogo
/******************************************************************************/
/*                                                                            */
/*              QUIZ TORIMONOCHOU (C) 1990 TAITO CORPORATION                  */
/*                                                                            */
/*                   QUIZ HQ (C) 1990 TAITO CORPORATION                       */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc110pcr.h"
#include "tc200obj.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "blit.h" // clear_game_screen

/*********************
   QUIZ TORIMONOCHOU
 *********************/


static struct ROM_INFO rom_qtorimon[] =
{
   {   "c41-01.bin", 0x00020000, 0x39ff043c, 0, 0, 0, },
   {   "c41-02.bin", 0x00020000, 0x05dcd36d, 0, 0, 0, },
   {   "c41-03.bin", 0x00020000, 0xb2c18e89, 0, 0, 0, },
   {   "c41-04.bin", 0x00020000, 0x0fbf5223, 0, 0, 0, },
   {   "c41-05.bin", 0x00020000, 0x174bd5db, 0, 0, 0, },
   {   "c41-06.bin", 0x00010000, 0x753a98d8, 0, 0, 0, },
   {  "mask-51.bin", 0x00020000, 0x12e14aca, 0, 0, 0, },
   {  "mask-52.bin", 0x00020000, 0xb3ef66f3, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_qtorimon[] =
{
   INP0( COIN1, 0x03C00E, 0x04 ),
   INP0( COIN2, 0x03C00E, 0x08 ),
   INP0( TILT, 0x03C00E, 0x01 ),
   INP0( SERVICE, 0x03C00E, 0x02 ),

   INP0( P1_START, 0x03C004, 0x10 ),
   INP0( P1_B1, 0x03C004, 0x01 ),
   INP0( P1_B2, 0x03C004, 0x02 ),
   INP0( P1_B3, 0x03C004, 0x08 ),
   INP0( P1_B4, 0x03C004, 0x04 ),

   INP0( P2_START, 0x03C006, 0x10 ),
   INP0( P2_B1, 0x03C006, 0x01 ),
   INP0( P2_B2, 0x03C006, 0x02 ),
   INP0( P2_B3, 0x03C006, 0x08 ),
   INP0( P2_B4, 0x03C006, 0x04 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_quiz_torimonochou_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_quiz_torimonochou_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "1",                     0x10},
   { "4",                     0x00},
   { _("Show Correct Answer"),   0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_qtorimon[] =
{
   { 0x03C000, 0xFF, dsw_data_quiz_torimonochou_0 },
   { 0x03C002, 0xFF, dsw_data_quiz_torimonochou_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_quiz_torimonochou_0[] =
{
   { "Taito Japan",                   0x01 },
   { "Taito Japan (Romstar license)", 0x04 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_qtorimon[] =
{
   { 0x03FFFF, 0x01, romsw_data_quiz_torimonochou_0 },
   { 0,        0,    NULL },
};

/***********
   QUIZ HQ
 ***********/

static struct ROM_INFO rom_quizhq[] =
{
   {   "c53-01.bin", 0x00020000, 0xbf44c93e, 0, 0, 0, },
   {   "c53-02.bin", 0x00020000, 0xd704c6f4, 0, 0, 0, },
   {   "c53-03.bin", 0x00020000, 0x47596e70, 0, 0, 0, },
   {   "c53-04.bin", 0x00020000, 0x99890ad4, 0, 0, 0, },
   {   "c53-05.bin", 0x00020000, 0xc798fc20, 0, 0, 0, },
   {   "c53-06.bin", 0x00020000, 0xf77f63fc, 0, 0, 0, },
   {   "c53-07.bin", 0x00020000, 0x4f9fa82f, 0, 0, 0, },
   {   "c53-08.bin", 0x00010000, 0x25187e81, 0, 0, 0, },
   {  "c53-52.bin", 0x00020000, 0x12e14aca, 0, 0, 0, },
   {  "c53-51.bin", 0x00020000, 0xb3ef66f3, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_quizhq[] =
{
   INP0( COIN1, 0x03C00E, 0x04 ),
   INP0( COIN2, 0x03C00E, 0x08 ),
   INP0( TILT, 0x03C00E, 0x01 ),
   INP0( SERVICE, 0x03C00E, 0x02 ),

   INP0( P1_START, 0x03C004, 0x80 ),
   INP0( P1_B1, 0x03C004, 0x01 ),
   INP0( P1_B2, 0x03C004, 0x02 ),
   INP0( P1_B3, 0x03C004, 0x08 ),
   INP0( P1_B4, 0x03C004, 0x04 ),
   INP0( P1_B5, 0x03C004, 0x10 ),

   INP0( P2_START, 0x03C006, 0x80 ),
   INP0( P2_B1, 0x03C006, 0x01 ),
   INP0( P2_B2, 0x03C006, 0x02 ),
   INP0( P2_B3, 0x03C006, 0x08 ),
   INP0( P2_B4, 0x03C006, 0x04 ),
   INP0( P2_B5, 0x03C006, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_quiz_hq_0[] =
{
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_1PLAY,         0x10},
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_quiz_hq_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Time"),                  0x0c, 0x04 },
   { _("5 seconds"),             0x0C},
   { _("10 seconds"),            0x08},
   { _("15 seconds"),            0x04},
   { _("20 seconds"),            0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x30},
   { "1",                     0x20},
   { "3",                     0x10},
   { "4",                     0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { _("Upright Controls"),      0x80, 0x02 },
   { _("Dual"),                  0x80},
   { _("Single"),                0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_quizhq[] =
{
   { 0x03C000, 0xFF, dsw_data_quiz_hq_0 },
   { 0x03C002, 0xFF, dsw_data_quiz_hq_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_quiz_hq_0[] =
{
   { "Taito Japan (notice)",  0x00 },
   { "Taito Japan",           0x01 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_quizhq[] =
{
   { 0x03FFFF, 0x00, romsw_data_quiz_hq_0 },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_yuyugogo[] =
{
   {   "c83-01.12", 0x00100000, 0x8bf0d416, 0, 0, 0, },
   {   "c83-02.11", 0x00100000, 0x20bb1c15, 0, 0, 0, },
   {   "c83-03.10", 0x00100000, 0xeed9acc2, 0, 0, 0, },
   {   "c83-04.5", 0x00100000, 0x2600093a, 0, 0, 0, },
   {   "c83-05.21", 0x00020000, 0xeca57fb1, 0, 0, 0, },
   {   "c83_09.2", 0x00020000, 0xf9892792, 0, 0, 0, },
   {   "c83_10.3", 0x00020000, 0x4d185d03, 0, 0, 0, },
   {   "c83_11.1", 0x00010000, 0x461e702a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_yuyugogo[] =
{
   INP0( COIN1, 0x03C00E, 0x04 ),
   INP0( COIN2, 0x03C00E, 0x08 ),
   INP0( TILT, 0x03C00E, 0x01 ),
   INP0( SERVICE, 0x03C00E, 0x02 ),

   INP0( P1_START, 0x03C004, 0x80 ),
   INP0( P1_B1, 0x03C004, 0x01 ),
   INP0( P1_B2, 0x03C004, 0x02 ),
   INP0( P1_B3, 0x03C004, 0x08 ),
   INP0( P1_B4, 0x03C004, 0x04 ),
   INP0( P1_B5, 0x03C004, 0x10 ),

   INP0( P2_START, 0x03C006, 0x80 ),
   INP0( P2_B1, 0x03C006, 0x01 ),
   INP0( P2_B2, 0x03C006, 0x02 ),
   INP0( P2_B3, 0x03C006, 0x08 ),
   INP0( P2_B4, 0x03C006, 0x04 ),
   INP0( P2_B5, 0x03C006, 0x10 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_yuyu_no_quiz_de_gogo_0[] =
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
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_yuyugogo[] =
{
   { 0x03C000, 0xFF, dsw_data_yuyu_no_quiz_de_gogo_0 },
   { 0x03C002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_yuyu_no_quiz_de_gogo_0[] =
{
   { "Taito Japan (notice)",  0x00 },
   { "Taito Japan",           0x01 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_yuyugogo[] =
{
   { 0x03FFFF, 0x00, romsw_data_yuyu_no_quiz_de_gogo_0 },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_qcrayon[] =
{
   {       "d55-01", 0x00100000, 0xa8309af4, 0, 0, 0, },
   {       "d55-02", 0x00100000, 0xf3db2f1c, 0, 0, 0, },
   {       "d55-03", 0x00100000, 0x4d161e76, 0, 0, 0, },
   {       "d55-04", 0x00100000, 0x412975ce, 0, 0, 0, },
   {       "d55-05", 0x00100000, 0xf0e59902, 0, 0, 0, },
   {       "d55-13", 0x00040000, 0x16afbfc7, 0, 0, 0, },
   {       "d55-14", 0x00040000, 0x2fb3057f, 0, 0, 0, },
   {       "d55-15", 0x00010000, 0xba782eff, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_qcrayon[] =
{
   INP0( COIN1, 0x03C00E, 0x04 ),
   INP0( COIN2, 0x03C00E, 0x08 ),
   INP0( TILT, 0x03C00E, 0x01 ),
   INP0( SERVICE, 0x03C00E, 0x02 ),

   INP0( P1_START, 0x03C004, 0x80 ),
   INP0( P1_B1, 0x03C004, 0x01 ),
   INP0( P1_B2, 0x03C004, 0x02 ),
   INP0( P1_B3, 0x03C004, 0x08 ),
   INP0( P1_B4, 0x03C004, 0x04 ),

   INP0( P2_START, 0x03C006, 0x80 ),
   INP0( P2_B1, 0x03C006, 0x01 ),
   INP0( P2_B2, 0x03C006, 0x02 ),
   INP0( P2_B3, 0x03C006, 0x08 ),
   INP0( P2_B4, 0x03C006, 0x04 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_quiz_crayon_shinchan_0[] =
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
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_qcrayon[] =
{
   { 0x03C000, 0xFF, dsw_data_quiz_crayon_shinchan_0 },
   { 0x03C002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_qcrayon2[] =
{
   {       "d63-01", 0x00080000, 0x872e38b4, 0, 0, 0, },
   {       "d63-02", 0x00100000, 0x162ae165, 0, 0, 0, },
   {       "d63-03", 0x00100000, 0xd24843af, 0, 0, 0, },
   {       "d63-06", 0x00200000, 0x58b1e4a8, 0, 0, 0, },
   {       "d63-11", 0x00010000, 0x2c7ac9e5, 0, 0, 0, },
   {       "d63-12", 0x00040000, 0x0f445a38, 0, 0, 0, },
   {       "d63-13", 0x00040000, 0x74455752, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_quiz_crayon_shinchan_2_0[] =
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
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_qcrayon2[] =
{
   { 0x03C000, 0xFF, dsw_data_quiz_crayon_shinchan_2_0 },
   { 0x03C002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_qjinsei[] =
{
   {       "d48-01", 0x00100000, 0x72a94b73, 0, 0, 0, },
   {       "d48-02", 0x00100000, 0xa7b68e63, 0, 0, 0, },
   {       "d48-03", 0x00100000, 0xfb5ea8dc, 0, 0, 0, },
   {       "d48-04", 0x00100000, 0x61e4b078, 0, 0, 0, },
   {       "d48-05", 0x00080000, 0x3fefd058, 0, 0, 0, },
   {       "d48-09", 0x00040000, 0xa573b68d, 0, 0, 0, },
   {       "d48-10", 0x00040000, 0x37143a5b, 0, 0, 0, },
   {       "d48-11", 0x00010000, 0x656c5b54, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_quiz_jinsei_gekijoh_0[] =
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
   { MSG_2COIN_3PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_1PLAY,         0x40},
   { MSG_2COIN_3PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_qjinsei[] =
{
   { 0x03C000, 0xFF, dsw_data_quiz_jinsei_gekijoh_0 },
   { 0x03C002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROM_INFO rom_qzchikyu[] =
{
   {   "d19-01.21", 0x00100000, 0x6c4342d0, 0, 0, 0, },
   {   "d19-02.10", 0x00100000, 0xf2dce2f2, 0, 0, 0, },
   {   "d19-03.6", 0x00080000, 0x5c1b92c0, 0, 0, 0, },
   {   "d19-04.9", 0x00080000, 0xd3c44905, 0, 0, 0, },
   {   "d19_05.7", 0x00020000, 0xc6d099d0, 0, 0, 0, },
   {   "d19_06.8", 0x00020000, 0xde8c8e55, 0, 0, 0, },
   {   "d19_07.5", 0x00010000, 0xa8935f84, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_quiz_chikyu_bouei_gun_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_qzchikyu[] =
{
   { 0x03C000, 0xFF, dsw_data_quiz_chikyu_bouei_gun_0 },
   { 0x03C002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_quiz_chikyu_bouei_gun_0[] =
{
   { "Taito Japan (notice)",  0x00 },
   { "Taito Japan",           0x01 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_qzchikyu[] =
{
   { 0x03FFFF, 0x00, romsw_data_quiz_chikyu_bouei_gun_0 },
   { 0,        0,    NULL },
};

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_OBJECT;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT32 romset;

static void load_qtorimon(void)
{
   int ta,tb;

   romset = 0;

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x80000))) return;

   GFX_SPR	= GFX+0x00000;

   tb=0;
   if(!load_rom("c41-02.bin", RAM, 0x20000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x20000;ta++,tb+=4){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }
   tb=2;
   if(!load_rom("c41-01.bin", RAM, 0x20000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x20000;ta++,tb+=4){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }

   if(!load_rom("c41-04.bin",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   if(!load_rom("mask-51.bin", RAM+0x20000, 0x20000)) return;	// DATA ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c41-05.bin",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   if(!load_rom("mask-52.bin", RAM+0x20000, 0x20000)) return;	// DATA ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("c41-06.bin", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x20000))) return;
   if(!load_rom("c41-03.bin",PCMROM,0x20000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x020000, 0x020000);

   AddTaitoYM2610(0x01E5, 0x0191, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x10000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x0023C],0x4EF800C0);

   WriteLong68k(&ROM[0x000C0],0x46FC2000);

   WriteLong68k(&ROM[0x000C4],0x13FC0000);
   WriteLong68k(&ROM[0x000C8],0x00AA0000);
   WriteWord68k(&ROM[0x000CC],0x6100-10);

   // Sprite Sync

   WriteLong68k(&ROM[0x00308],0x4EF800D0);

   WriteLong68k(&ROM[0x000D0],0x4EB80326);

   WriteLong68k(&ROM[0x000D4],0x13FC0000);
   WriteLong68k(&ROM[0x000D8],0x00AA0000);

   WriteLong68k(&ROM[0x000DC],0x4EF8030C);

   tc0110pcr_init_typeb(RAM+0x3A000, 0, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);


   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x0800);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=NULL;
   tc0100scn[0].layer[0].MASK	=NULL;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=NULL;
   tc0100scn[0].layer[1].MASK	=NULL;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_15bit_xBGR;
   tc0200obj.tile_mask	= 0x07FF;
   tc0200obj.ofs_x	= 0-0x60;
   tc0200obj.ofs_y	= 0-0x10;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0x500000, 0x50001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x600000, 0x600003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0x200000, 0x200007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x500000, 0x50001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0x600000, 0x600003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x500000, 0x50001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0x200000, 0x200007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x820000, 0x82001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x500000, 0x50001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

// inputs are scrambled!

static UINT32 remap_a_ioc[4] =
{
   0x02, 0x04, 0x08, 0x12,
};

static UINT8 quiz_hq_ioc_a_rb(UINT32 offset)
{
   return tc0220ioc_rb( remap_a_ioc[(offset>>1)&3]|1 );
}

static UINT16 quiz_hq_ioc_a_rw(UINT32 offset)
{
   return tc0220ioc_rw( remap_a_ioc[(offset>>1)&3] );
}

static void quiz_hq_ioc_a_wb(UINT32 offset, UINT8 data)
{
   tc0220ioc_wb( remap_a_ioc[(offset>>1)&3]|1 , data);
}

static void quiz_hq_ioc_a_ww(UINT32 offset, UINT16 data)
{
   tc0220ioc_ww( remap_a_ioc[(offset>>1)&3] , data);
}

static UINT32 remap_b_ioc[4] =
{
   0x00, 0x06, 0x0E, 0x10,
};

static UINT8 quiz_hq_ioc_b_rb(UINT32 offset)
{
   return tc0220ioc_rb( remap_b_ioc[(offset>>1)&3]|1 );
}

static UINT16 quiz_hq_ioc_b_rw(UINT32 offset)
{
   return tc0220ioc_rw( remap_b_ioc[(offset>>1)&3] );
}

static void quiz_hq_ioc_b_wb(UINT32 offset, UINT8 data)
{
   tc0220ioc_wb( remap_b_ioc[(offset>>1)&3]|1 , data);
}

static void quiz_hq_ioc_b_ww(UINT32 offset, UINT16 data)
{
   tc0220ioc_ww( remap_b_ioc[(offset>>1)&3] , data);
}

static void load_quizhq(void)
{
   int ta,tb;

   romset = 1;

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0xC0000))) return;
   if(!(GFX=AllocateMem(0x100000))) return;

   GFX_SPR	= GFX+0x00000;

   tb=0;
   if(!load_rom("c53-03.bin", RAM+0x00000, 0x20000)) return;	// 16x16 SPRITES
   if(!load_rom("c53-02.bin", RAM+0x20000, 0x20000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x40000;ta++,tb+=4){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }
   tb=2;
   if(!load_rom("c53-07.bin", RAM+0x00000, 0x20000)) return;	// 16x16 SPRITES
   if(!load_rom("c53-06.bin", RAM+0x20000, 0x20000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x40000;ta++,tb+=4){
      GFX_SPR[tb+0]=RAM[ta]&15;
      GFX_SPR[tb+1]=RAM[ta]>>4;
   }

   memset(ROM+0x40000,0x00,0x40000);

   if(!load_rom("c53-05.bin",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c53-52.bin", RAM+0x00000, 0x20000)) return;	// DATA ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80000]=RAM[ta];
   }
   if(!load_rom("c53-01.bin",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("c53-51.bin", RAM+0x00000, 0x20000)) return;	// DATA ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x80001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("c53-08.bin", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x20000))) return;
   if(!load_rom("c53-04.bin",PCMROM,0x20000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x020000, 0x020000);

   AddTaitoYM2610(0x0217, 0x018F, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x10000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x031C4],0x13FC0000);
   WriteLong68k(&ROM[0x031C8],0x00AA0000);
   WriteWord68k(&ROM[0x031CC],0x4E75);

   // Sprite Sync

   WriteLong68k(&ROM[0x030CE],0x4EF800D0);

   WriteLong68k(&ROM[0x000D0],0x4EB8485C);

   WriteLong68k(&ROM[0x000D4],0x13FC0000);
   WriteLong68k(&ROM[0x000D8],0x00AA0000);

   WriteLong68k(&ROM[0x000DC],0x4EF830D4);

   tc0110pcr_init_typeb(RAM+0x3A000, 0, 0);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);

   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x1000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=NULL;
   tc0100scn[0].layer[0].MASK	=NULL;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=NULL;
   tc0100scn[0].layer[1].MASK	=NULL;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	=16;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_15bit_xBGR;
   tc0200obj.tile_mask	= 0x0FFF;
   tc0200obj.ofs_x	= 0-0x60;
   tc0200obj.ofs_y	= 0-0x10;

   init_tc0200obj();

   //memset(RAM_INPUT,0xFF,0x20);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xC0000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x0BFFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0x500000, 0x500007, quiz_hq_ioc_a_rb, NULL);		// INPUT
   AddReadByte(0x580000, 0x580007, quiz_hq_ioc_b_rb, NULL);		// INPUT
   AddReadByte(0x600000, 0x600003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x0BFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0x200000, 0x200007, tc0110pcr_rw, NULL);			// COLOR RAM
   AddReadWord(0x500000, 0x500007, quiz_hq_ioc_a_rw, NULL);		// INPUT
   AddReadWord(0x580000, 0x580007, quiz_hq_ioc_b_rw, NULL);		// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0x600000, 0x600003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x500000, 0x500007, quiz_hq_ioc_a_wb, NULL);		// INPUT
   AddWriteByte(0x580000, 0x580007, quiz_hq_ioc_b_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0x200000, 0x200007, tc0110pcr_ww, NULL);		// COLOR RAM
   AddWriteWord(0x820000, 0x82001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x500000, 0x500007, quiz_hq_ioc_a_ww, NULL);		// INPUT
   AddWriteWord(0x580000, 0x580007, quiz_hq_ioc_b_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_yuyugogo(void)
{
   int ta,tb,tc;
   UINT8 *TMP;

   romset = 2;

   RAMSize=0x60000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x40000+0x100000))) return;
   if(!(GFX=AllocateMem(0x400000+0x100000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   GFX_SPR	= GFX+0x000000;
   GFX_BG0	= GFX+0x400000;

   tb=0;
   if(!load_rom("c83-05.21", TMP, 0x020000)) return;		// 16x16 BG0
   for(ta=0;ta<0x020000;ta++,tb+=8){
      tc=TMP[ta];
      GFX_BG0[tb+0]=((tc&0x80)>>7)<<0;
      GFX_BG0[tb+1]=((tc&0x40)>>6)<<0;
      GFX_BG0[tb+2]=((tc&0x20)>>5)<<0;
      GFX_BG0[tb+3]=((tc&0x10)>>4)<<0;
      GFX_BG0[tb+4]=((tc&0x08)>>3)<<0;
      GFX_BG0[tb+5]=((tc&0x04)>>2)<<0;
      GFX_BG0[tb+6]=((tc&0x02)>>1)<<0;
      GFX_BG0[tb+7]=((tc&0x01)>>0)<<0;
   }

   tb=0;
   if(!load_rom("c83-01.12", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }
   tb=2;
   if(!load_rom("c83-02.11", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   FreeMem(TMP);

   if(!load_rom("c83_10.3",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("c83_09.2",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("c83-03.10",  ROM+0x40000, 0x100000)) return;	// 1MB DATA ROM

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   if(!load_rom("c83_11.1", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("c83-04.5",PCMROM,0x100000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x019E, 0x0152, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x60000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x10000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   WriteWord68k(&ROM[0x14910],0x7000);

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x03E3C],0x13FC0000);
   WriteLong68k(&ROM[0x03E40],0x00AA0000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x4000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX_BG0;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0x3FFF;
   tc0100scn[0].layer[0].scr_x	=  0 + 12;
   tc0100scn[0].layer[0].scr_y	=  8 -  1;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX_BG0;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0x3FFF;
   tc0100scn[0].layer[1].scr_x	=  0 + 12;
   tc0100scn[0].layer[1].scr_y	=  8 -  1;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	=  0 + 12;
   tc0100scn[0].layer[2].scr_y	=  8 -  0;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_12bit_RGBx;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0 - (0x53 + 0x10);
   tc0200obj.ofs_y	= 0 - (0x00 + 0x10);

   tc0200obj.cols	= 16;

   tc0200obj.RAM_TILE	= RAM+0x40000;
   tc0200obj.RAM_TILE_B	= RAM+0x40800;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x40000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0xB00000, 0xB0FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0x200000, 0x20001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x400000, 0x400003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0xD00000, 0xDFFFFF, NULL, ROM+0x040000);			// 1MB DATA ROM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0xB00000, 0xB0FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0xA00000, 0xA01FFF, NULL, RAM+0x03A000);			// COLOR RAM
   AddReadWord(0x200000, 0x20001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0xD00000, 0xDFFFFF, NULL, ROM+0x040000);			// 1MB DATA ROM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xB00000, 0xB0FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0x400000, 0x400003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x200000, 0x20001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xB00000, 0xB0FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x900000, 0x907FFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0xA00000, 0xA01FFF, NULL, RAM+0x03A000);		// COLOR RAM
   AddWriteWord(0x820000, 0x82001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x200000, 0x20001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0xC00000, 0xC01FFF, NULL, RAM+0x040000);		// OBJECT BANK RAM ?
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_qcrayon(void)
{
   int ta,tb;
   UINT8 *TMP;

   romset = 3;

   RAMSize=0x60000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000+0x100000))) return;
   if(!(GFX=AllocateMem(0x400000+0x200000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   GFX_SPR	= GFX+0x000000;
   GFX_BG0	= GFX+0x400000;

   tb=0;
   if(!load_rom("d55-02", TMP, 0x100000)) return;		// 16x16 BG0
   for(ta=0;ta<0x100000;ta+=2,tb+=4){
      GFX_BG0[tb+0]=TMP[ta+1]>>4;
      GFX_BG0[tb+1]=TMP[ta+1]&15;
      GFX_BG0[tb+2]=TMP[ta+0]>>4;
      GFX_BG0[tb+3]=TMP[ta+0]&15;
   }
   tb=0;
   if(!load_rom("d55-05", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }
   tb=2;
   if(!load_rom("d55-04", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   FreeMem(TMP);

   if(!load_rom("d55-13",  RAM+0x00000, 0x40000)) return;	// 68000 ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d55-14",  RAM+0x00000, 0x40000)) return;	// 68000 ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("d55-03",  ROM+0x80000, 0x100000)) return;	// 1MB DATA ROM

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   if(!load_rom("d55-15", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("d55-01",PCMROM,0x100000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x0211, 0x017A, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x60000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x50000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x1A794],0x13FC0000);
   WriteLong68k(&ROM[0x1A798],0x00AA0000);
   WriteWord68k(&ROM[0x1A79C],0x6100-18);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX_BG0;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0x7FFF;
   tc0100scn[0].layer[0].scr_x	= 16 + 3;
   tc0100scn[0].layer[0].scr_y	=  8 + 0;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX_BG0;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0x7FFF;
   tc0100scn[0].layer[1].scr_x	= 16 + 3;
   tc0100scn[0].layer[1].scr_y	=  8 + 0;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	= 16 + 3;
   tc0100scn[0].layer[2].scr_y	=  8 + 0;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_12bit_RGBx;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;

   tc0200obj.cols	= 16;

   tc0200obj.RAM_TILE	= RAM+0x40000;
   tc0200obj.RAM_TILE_B	= RAM+0x40800;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0xA00000, 0xA0001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x500000, 0x500003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x300000, 0x3FFFFF, NULL, ROM+0x080000);			// 1MB DATA ROM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0x700000, 0x701FFF, NULL, RAM+0x03A000);			// COLOR RAM
   AddReadWord(0xA00000, 0xA0001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x300000, 0x3FFFFF, NULL, ROM+0x080000);			// 1MB DATA ROM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x906000, 0x906FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0x500000, 0x500003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xA00000, 0xA0001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x906000, 0x906FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x900000, 0x90FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0x700000, 0x701FFF, NULL, RAM+0x03A000);		// COLOR RAM
   AddWriteWord(0x920000, 0x92001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xA00000, 0xA0001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x600000, 0x601FFF, NULL, RAM+0x040000);		// OBJECT BANK RAM
   AddWriteWord(0xB00000, 0xB0001F, NULL, RAM_SCROLL+0x20);		// PIXEL SCROLL ?
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_qcrayon2(void)
{
   int ta,tb;
   UINT8 *TMP;

   romset = 5;

   RAMSize=0x60000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000+0x80000))) return;
   if(!(GFX=AllocateMem(0x400000+0x200000))) return;
   if(!(TMP=AllocateMem(0x200000))) return;

   GFX_SPR	= GFX+0x000000;
   GFX_BG0	= GFX+0x400000;

   tb=0;
   if(!load_rom("d63-03", TMP, 0x100000)) return;		// 8x8 BG0
   for(ta=0;ta<0x100000;ta+=2,tb+=4){
      GFX_BG0[tb+0]=TMP[ta+1]>>4;
      GFX_BG0[tb+1]=TMP[ta+1]&15;
      GFX_BG0[tb+2]=TMP[ta+0]>>4;
      GFX_BG0[tb+3]=TMP[ta+0]&15;
   }
   tb=0;
   if(!load_rom("d63-06", TMP, 0x200000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta+=2,tb+=4){
      GFX_SPR[tb+0]=TMP[ta+0]&15;
      GFX_SPR[tb+1]=TMP[ta+0]>>4;
      GFX_SPR[tb+2]=TMP[ta+1]&15;
      GFX_SPR[tb+3]=TMP[ta+1]>>4;
   }

   FreeMem(TMP);

   if(!load_rom("d63-12",  RAM+0x00000, 0x40000)) return;	// 68000 ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d63-13",  RAM+0x00000, 0x40000)) return;	// 68000 ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("d63-01",  ROM+0x80000, 0x80000)) return;	// 512KB DATA ROM

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   if(!load_rom("d63-11", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("d63-02",PCMROM,0x100000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x100000, 0x100000);

   AddTaitoYM2610(0x0211, 0x017A, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x60000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x50000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x011A0],0x13FC0000);
   WriteLong68k(&ROM[0x011A4],0x00AA0000);
   WriteWord68k(&ROM[0x011A8],0x6100-16);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
  InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX_BG0;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0x7FFF;
   tc0100scn[0].layer[0].scr_x	= 16 + 3;
   tc0100scn[0].layer[0].scr_y	=  8 + 0;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX_BG0;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0x7FFF;
   tc0100scn[0].layer[1].scr_x	= 16 + 3;
   tc0100scn[0].layer[1].scr_y	=  8 + 0;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	= 16 + 3;
   tc0100scn[0].layer[2].scr_y	=  8 + 0;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_12bit_RGBx;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;

   tc0200obj.cols	= 16;

   tc0200obj.RAM_TILE	= RAM+0x40000;
   tc0200obj.RAM_TILE_B	= RAM+0x40800;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x200000, 0x20FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x500000, 0x50FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0x700000, 0x70001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0xA00000, 0xA00003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x600000, 0x67FFFF, NULL, ROM+0x080000);			// 512KB DATA ROM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x200000, 0x20FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x500000, 0x50FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0x300000, 0x301FFF, NULL, RAM+0x03A000);			// COLOR RAM
   AddReadWord(0x700000, 0x70001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x600000, 0x67FFFF, NULL, ROM+0x080000);			// 512KB DATA ROM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x200000, 0x20FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x506000, 0x506FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x500000, 0x50FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0xA00000, 0xA00003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x700000, 0x70001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x20FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x506000, 0x506FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x500000, 0x50FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x400000, 0x40FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0x300000, 0x301FFF, NULL, RAM+0x03A000);		// COLOR RAM
   AddWriteWord(0x520000, 0x52001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x700000, 0x70001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0xB00000, 0xB01FFF, NULL, RAM+0x040000);		// OBJECT BANK RAM
   AddWriteWord(0x900000, 0x90001F, NULL, RAM_SCROLL+0x20);		// PIXEL SCROLL ?
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_qjinsei(void)
{
   int ta,tb;
   UINT8 *TMP;

   romset = 4;

   RAMSize=0x60000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000+0x100000))) return;
   if(!(GFX=AllocateMem(0x400000+0x200000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   GFX_SPR	= GFX+0x000000;
   GFX_BG0	= GFX+0x400000;

   tb=0;
   if(!load_rom("d48-04", TMP, 0x100000)) return;		// 16x16 BG0
   for(ta=0;ta<0x100000;ta+=2,tb+=4){
      GFX_BG0[tb+0]=TMP[ta+1]>>4;
      GFX_BG0[tb+1]=TMP[ta+1]&15;
      GFX_BG0[tb+2]=TMP[ta+0]>>4;
      GFX_BG0[tb+3]=TMP[ta+0]&15;
   }
   tb=0;
   if(!load_rom("d48-02", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }
   tb=2;
   if(!load_rom("d48-01", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=4){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   FreeMem(TMP);

   if(!load_rom("d48-09",  RAM+0x00000, 0x40000)) return;	// 68000 ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d48-10",  RAM+0x00000, 0x40000)) return;	// 68000 ROM
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("d48-03",  ROM+0x80000, 0x100000)) return;	// 1MB DATA ROM

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   if(!load_rom("d48-11", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("d48-05",PCMROM,0x80000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x0211, 0x017A, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x60000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x50000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x03E14],0x13FC0000);
   WriteLong68k(&ROM[0x03E18],0x00AA0000);
   WriteWord68k(&ROM[0x03E1C],0x6100-18);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);
   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x4000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX_BG0;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0x7FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX_BG0;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0x7FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	=16+3;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_12bit_RGBx;
   tc0200obj.tile_mask	= 0x3FFF;
   tc0200obj.ofs_x	= 0;
   tc0200obj.ofs_y	= 0;

   tc0200obj.cols	= 16;

   tc0200obj.RAM_TILE	= RAM+0x40000;
   tc0200obj.RAM_TILE_B	= RAM+0x40800;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x300000, 0x30FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0xB00000, 0xB0001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x200000, 0x200003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x100000, 0x1FFFFF, NULL, ROM+0x080000);			// 1MB DATA ROM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x300000, 0x30FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0x700000, 0x701FFF, NULL, RAM+0x03A000);			// COLOR RAM
   AddReadWord(0xB00000, 0xB0001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x100000, 0x1FFFFF, NULL, ROM+0x080000);			// 1MB DATA ROM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x300000, 0x30FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0x200000, 0x200003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xB00000, 0xB0001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x300000, 0x30FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x806000, 0x806FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x900000, 0x90FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0x700000, 0x701FFF, NULL, RAM+0x03A000);		// COLOR RAM
   AddWriteWord(0x820000, 0x82001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0xB00000, 0xB0001F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x600000, 0x601FFF, NULL, RAM+0x040000);		// OBJECT BANK RAM ?
   AddWriteWord(0xA00000, 0xA0001F, NULL, RAM_SCROLL+0x20);		// PIXEL SCROLL ?
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void load_qzchikyu(void)
{
   int ta,tb;
   UINT8 *TMP;

   romset = 6;

   RAMSize=0x60000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000+0x100000))) return;
   if(!(GFX=AllocateMem(0x200000+0x200000))) return;
   if(!(TMP=AllocateMem(0x100000))) return;

   GFX_SPR	= GFX+0x000000;
   GFX_BG0	= GFX+0x200000;

   tb=0;
   if(!load_rom("d19-02.10", TMP, 0x100000)) return;		// 16x16 BG0
   for(ta=0;ta<0x100000;ta+=2,tb+=4){
      GFX_BG0[tb+0]=TMP[ta+1]>>4;
      GFX_BG0[tb+1]=TMP[ta+1]&15;
      GFX_BG0[tb+2]=TMP[ta+0]>>4;
      GFX_BG0[tb+3]=TMP[ta+0]&15;
   }
   tb=0;
   if(!load_rom("d19-01.21", TMP, 0x100000)) return;		// 16x16 SPRITES
   for(ta=0;ta<0x100000;ta++,tb+=2){
      GFX_SPR[tb+0]=TMP[ta]&15;
      GFX_SPR[tb+1]=TMP[ta]>>4;
   }

   FreeMem(TMP);

   if(!load_rom("d19_06.8",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("d19_05.7",  RAM+0x00000, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom("d19-03.6",  ROM+0x80000, 0x80000)) return;	// DATA ROM

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x60000;
   if(!load_rom("d19_07.5", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("d19-04.9",PCMROM,0x80000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x01AE, 0x015A, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x60000);

   RAM_VIDEO  = RAM+0x18000;
   RAM_SCROLL = RAM+0x3C100;
   RAM_OBJECT = RAM+0x50000;
   RAM_INPUT  = RAM+0x3C000;
   GFX_FG0    = RAM+0x28000;

   // 68000 Speed Hack

   WriteLong68k(&ROM[0x00E2E],0x13FC0000);
   WriteLong68k(&ROM[0x00E32],0x00AA0000);

   set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
   InitPaletteMap(RAM+0x3A000, 0x100, 0x10, 0x8000);

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x2000);

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;	//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX_BG0;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=224;
   tc0100scn[0].layer[0].tile_mask=0x7FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX_BG0;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=224;
   tc0100scn[0].layer[1].tile_mask=0x7FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[0].layer[2].RAM	=RAM_VIDEO+0x4000;
   tc0100scn[0].layer[2].GFX	=GFX_FG0;
   tc0100scn[0].layer[2].SCR	=RAM_SCROLL+4;
   tc0100scn[0].layer[2].type	=3;
   tc0100scn[0].layer[2].bmp_x	=32;
   tc0100scn[0].layer[2].bmp_y	=32;
   tc0100scn[0].layer[2].bmp_w	=320;
   tc0100scn[0].layer[2].bmp_h	=224;
   tc0100scn[0].layer[2].scr_x	=16+3;
   tc0100scn[0].layer[2].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = GFX_FG0;

   init_tc0100scn(0);

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM_OBJECT;
   tc0200obj.RAM_B	= RAM_OBJECT+0x8000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 32;
   tc0200obj.bmp_y	= 32;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
   tc0200obj.mapper	= &Map_15bit_xRGB;
   tc0200obj.tile_mask	= 0x1FFF;
   tc0200obj.ofs_x	= -96;
   tc0200obj.ofs_y	= -16;

   tc0200obj.cols	= 16;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x03FFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x500000, 0x50FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x700000, 0x70FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x600000, 0x60FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadByte(0x200000, 0x20001F, NULL, RAM_INPUT);			// INPUT
   AddReadByte(0x300000, 0x300003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x100000, 0x17FFFF, NULL, ROM+0x080000);			// DATA ROM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x03FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x500000, 0x50FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x700000, 0x70FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x600000, 0x60FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddReadWord(0x400000, 0x401FFF, NULL, RAM+0x03A000);			// COLOR RAM
   AddReadWord(0x200000, 0x20001F, NULL, RAM_INPUT);			// INPUT
   AddReadWord(0x100000, 0x17FFFF, NULL, ROM+0x080000);			// DATA ROM
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x500000, 0x50FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x706000, 0x706FFF, tc0100scn_0_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x700000, 0x70FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x600000, 0x60FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteByte(0x300000, 0x300003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x200000, 0x20001F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x500000, 0x50FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x706000, 0x706FFF, tc0100scn_0_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x700000, 0x70FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x600000, 0x60FFFF, NULL, RAM_OBJECT);			// SPRITE RAM
   AddWriteWord(0x400000, 0x401FFF, NULL, RAM+0x03A000);		// COLOR RAM
   AddWriteWord(0x720000, 0x72001F, NULL, RAM_SCROLL);			// SCROLL RAM
   AddWriteWord(0x200000, 0x20001F, tc0220ioc_ww, NULL);		// INPUT
   //AddWriteWord(0x600000, 0x601FFF, NULL, RAM+0x040000);		// OBJECT BANK RAM ?
   //AddWriteWord(0xA00000, 0xA0001F, NULL, RAM_SCROLL+0x20);		// PIXEL SCROLL ?
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_yuyugogo(void)
{
#ifdef RAINE_DEBUG
   print_ingame(10000,"---- ---- ---- ----");
   print_ingame(10000,"%04x.%04x.%04x.%04x",ReadWord(RAM+0x3C120),ReadWord(RAM+0x3C122),ReadWord(RAM+0x3C124),ReadWord(RAM+0x3C126));
   print_ingame(10000,"%04x.%04x.%04x.%04x",ReadWord(RAM+0x3C128),ReadWord(RAM+0x3C12A),ReadWord(RAM+0x3C12C),ReadWord(RAM+0x3C12E));
   print_ingame(10000,"%04x.%04x.%04x.%04x",ReadWord(RAM+0x3C130),ReadWord(RAM+0x3C132),ReadWord(RAM+0x3C134),ReadWord(RAM+0x3C136));
   print_ingame(10000,"%04x.%04x.%04x.%04x",ReadWord(RAM+0x3C138),ReadWord(RAM+0x3C13A),ReadWord(RAM+0x3C13C),ReadWord(RAM+0x3C13E));
#endif
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)

   switch(romset){
   case 0:
      if(s68000context.pc == 0x00CC){
      cpu_interrupt(CPU_68K_0, 5);
      cpu_interrupt(CPU_68K_0, 6);
      }
   break;
   case 1:
      if(s68000context.pc == 0x31CC){
      cpu_interrupt(CPU_68K_0, 6);
      cpu_interrupt(CPU_68K_0, 5);
      }
   break;
   default:
      cpu_interrupt(CPU_68K_0, 6);
      cpu_interrupt(CPU_68K_0, 5);
   break;
   }

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// Sync the sprites

   Taito2610_Frame();					// Z80 and YM2610
}

/*

this one has no bg0 gfx

*/

static void draw_quiz_torimonochou(void)
{
   ClearPaletteMap();

   clear_game_screen(0);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 1;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // OBJECT
   // ------

   render_tc0200obj_mapped_b();

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);
}

/*

this one has bg0, and object tile banking

*/

static void draw_yuyu_no_quiz_de_gogo(void)
{
   ClearPaletteMap();

   clear_game_screen(0);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 1;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // OBJECT
   // ------

   render_tc0200obj_mapped_yuyugogo();

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);
}

/*

this one has bg0, and an alternate object tile banking

*/

static void draw_quiz_crayon_shinchan(void)
{
   ClearPaletteMap();

   if((ReadWord(RAM+0x3C12E)&0x0002)==0){

   clear_game_screen(0);

   tc0100scn_layer_count = 1;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   render_tc0200obj_mapped_yuyugogo2(0);
   render_tc0100scn_layer_mapped(0,0,0);
   render_tc0100scn_layer_mapped(0,1,1);
   render_tc0200obj_mapped_yuyugogo2(1);
   render_tc0100scn_layer_mapped(0,2,1);

   }
   else{
/*
   if((ReadWord(RAM+0x3C12A)&0x0040)==0){

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   render_tc0100scn_layer_mapped(0,0);
   render_tc0100scn_layer_mapped(0,1);
   render_tc0200obj_mapped_yuyugogo2();
   render_tc0100scn_layer_mapped(0,2);

   }
   else{
*/
   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   render_tc0100scn_layer_mapped(0,0,0);
   render_tc0200obj_mapped_yuyugogo2(0);
   render_tc0100scn_layer_mapped(0,1,1);
   render_tc0200obj_mapped_yuyugogo2(1);
   render_tc0100scn_layer_mapped(0,2,1);
/*
   }
*/
   }
}

/*

this one has bg0, and object

*/

static void draw_quiz_chikyu_bouei_gun(void)
{
   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped(0,0,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // OBJECT
   // ------

   render_tc0200obj_mapped_b();

   // FG0
   // ---

   render_tc0100scn_layer_mapped(0,2,1);
}
static struct VIDEO_INFO video_qcrayon =
{
   draw_quiz_crayon_shinchan,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct VIDEO_INFO video_qtorimon =
{
   draw_quiz_torimonochou,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct VIDEO_INFO video_qzchikyu =
{
   draw_quiz_chikyu_bouei_gun,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct VIDEO_INFO video_yuyugogo =
{
   draw_yuyu_no_quiz_de_gogo,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_qzchikyu[] =
{
   { "quiz_chikyu_bouei_gun", },
   { "qzchikyu", },
   { NULL, },
};
GAME( qzchikyu, "Quiz Chikyu Bouei Gun", TAITO, 1991, GAME_QUIZZ,
	.input = input_qtorimon,
	.dsw = dsw_qzchikyu,
	.romsw = romsw_qzchikyu,
	.video = &video_qzchikyu,
	.long_name_jpn = "ÉNÉCÉYínãÖñhâqåR",
	.board = "D19",
);
static struct DIR_INFO dir_qcrayon[] =
{
   { "quiz_crayon_shinchan", },
   { "qcrayon", },
   { NULL, },
};
GME( qcrayon, "Quiz Crayon Shinchan", TAITO, 1993, GAME_QUIZZ | GAME_PUZZLE,
	.board = "D55",
);
static struct DIR_INFO dir_qcrayon2[] =
{
   { "quiz_crayon_shinchan_2", },
   { "qcrayon2", },
   { NULL, },
};
GAME( qcrayon2, "Quiz Crayon Shinchan 2", TAITO, 1993, GAME_QUIZZ,
	.input = input_qcrayon,
	.dsw = dsw_qcrayon2,
	.video = &video_qcrayon,
	.board = "D63",
);
static struct DIR_INFO dir_quizhq[] =
{
   { "quiz_hq", },
   { "quizhq", },
   { NULL, },
};
GAME( quizhq, "Quiz HQ", TAITO, 1990, GAME_QUIZZ,
	.input = input_quizhq,
	.dsw = dsw_quizhq,
	.romsw = romsw_quizhq,
	.video = &video_qtorimon,
	.long_name_jpn = "ÉNÉCÉYÇgÇp",
	.board = "C53",
);
static struct DIR_INFO dir_qjinsei[] =
{
   { "quiz_jinsei_gekijoh", },
   { "qjinsei", },
   { NULL, },
};
GAME( qjinsei, "Quiz Jinsei Gekijoh", TAITO, 1992, GAME_QUIZZ,
	.input = input_qcrayon,
	.dsw = dsw_qjinsei,
	.video = &video_qcrayon,
	.long_name_jpn = "ÉNÉCÉYêlê∂åÄèÍ",
	.board = "D48",
);
static struct DIR_INFO dir_qtorimon[] =
{
   { "quiz_torimonochou", },
   { "qtorimon", },
   { NULL, },
};
GME( qtorimon, "Quiz Torimonochou", TAITO, 1990, GAME_QUIZZ,
	.long_name_jpn = "ãÍà›ìºïˇï®í∑",
	.romsw = romsw_qtorimon,
	.board = "C41",
);
static struct DIR_INFO dir_yuyugogo[] =
{
   { "yuyu_no_quiz_de_gogo", },
   { "yuyugogo", },
   { NULL, },
};
GME( yuyugogo, "Yuuyu no Quiz de Go!Go!", TAITO, 1990, GAME_QUIZZ,
	.romsw = romsw_yuyugogo,
	.long_name_jpn = "Ç‰Ç±Ç‰ÇÃÉNÉCÉYÇ≈ÇfÇnÅIÅ@ÇfÇnÅI",
	.board = "C83",
);

