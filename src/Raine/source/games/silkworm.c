#define DRV_DEF_VIDEO &video_rygar
#define DRV_DEF_SOUND sound_gemini
#define DRV_DEF_EXEC execute_gemini
/***************************************************************************/
/*                                                                         */
/*                          SILKWORM (C) 1988 TECMO                        */
/*                                                                         */
/*                            RYGAR (C) 1986 TECMO                         */
/*                                                                         */
/*                         GEMINI WING (C) 1987 TECMO                      */
/*                                                                         */
/*                        Z80 + Z80 + YM3812 + MSM5205                     */
/*                                                                         */
/***************************************************************************/

/*
	Converted to Raine from Mame sourcecode.
	Original Mame driver written by: Nicola Salmoria

*/


#include "gameinc.h"
#include "taitosnd.h"
#include "msm5205.h"
#include "sasound.h"		// sample support routines
#include "3812intf.h"
#include "blit.h" // clear_game_screen
#include "timer.h"

static int sound_command;
static int nmi_trigger;
static int sample_size;

/******************
   SILKWORM SET 1
 ******************/


static struct ROM_INFO rom_silkworm[] =
{
   {   "silkworm.4", 0x10000, 0xa5277cce, REGION_CPU1, 0, LOAD_NORMAL },
   {   "silkworm.5", 0x10000, 0xa6c7bb51, REGION_CPU1, 0xc000, LOAD_NORMAL },
   {   "silkworm.3", 0x08000, 0xb589f587, REGION_CPU2, 0, LOAD_NORMAL },
   {   "silkworm.2", 0x08000, 0xe80a1cd9, 0, 0, 0, }, // char
   {   "silkworm.6", 0x10000, 0x1138d159, 0, 0, 0, }, // spr
   {   "silkworm.7", 0x10000, 0xd96214f7, 0, 0, 0, }, // spr
   {   "silkworm.8", 0x10000, 0x0494b38e, 0, 0, 0, }, // spr
   {   "silkworm.9", 0x10000, 0x8ce3cdf5, 0, 0, 0, }, // spr
   {   "silkworm.10",0x10000, 0x8c7138bb, 0, 0, 0, }, // tile1
   {   "silkworm.11",0x10000, 0x6c03c476, 0, 0, 0, }, // tile1
   {   "silkworm.12",0x10000, 0xbb0f568f, 0, 0, 0, }, // tile1
   {   "silkworm.13",0x10000, 0x773ad0a4, 0, 0, 0, }, // tile1
   {   "silkworm.14",0x10000, 0x409df64b, 0, 0, 0, }, // tile2
   {   "silkworm.15",0x10000, 0x6e4052c9, 0, 0, 0, }, // tile2
   {   "silkworm.16",0x10000, 0x9292ed63, 0, 0, 0, }, // tile2
   {   "silkworm.17",0x10000, 0x3fa4563d, 0, 0, 0, }, // tile2
   {   "silkworm.1", 0x08000, 0x5b553644, REGION_SOUND1, 0, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

#define JOY_1 \
   { KB_DEF_P1_LEFT,      MSG_P1_LEFT,             0x6000, 0x01, BIT_ACTIVE_1 },\
   { KB_DEF_P1_RIGHT,     MSG_P1_RIGHT,            0x6000, 0x02, BIT_ACTIVE_1 },\
   { KB_DEF_P1_DOWN,      MSG_P1_DOWN,             0x6000, 0x04, BIT_ACTIVE_1 },\
   { KB_DEF_P1_UP,        MSG_P1_UP,               0x6000, 0x08, BIT_ACTIVE_1 },

#define JOY_2 \
   { KB_DEF_P2_LEFT,      MSG_P2_LEFT,             0x6002, 0x01, BIT_ACTIVE_1 },\
   { KB_DEF_P2_RIGHT,     MSG_P2_RIGHT,            0x6002, 0x02, BIT_ACTIVE_1 },\
   { KB_DEF_P2_DOWN,      MSG_P2_DOWN,             0x6002, 0x04, BIT_ACTIVE_1 },\
   { KB_DEF_P2_UP,        MSG_P2_UP,               0x6002, 0x08, BIT_ACTIVE_1 },

static struct INPUT_INFO input_silkworm[] =
{
   JOY_1
   INP1( P1_B1, 0x6001, 0x02 ),
   INP1( P1_B2, 0x6001, 0x01 ),
   INP1( P1_B3, 0x6001, 0x04 ),

   JOY_2
   INP1( P2_B1, 0x6003, 0x02 ),
   INP1( P2_B2, 0x6003, 0x01 ),
   INP1( P2_B3, 0x6003, 0x04 ),

   INP1( P1_START, 0x600F, 0x01 ),
   INP1( P2_START, 0x600F, 0x02 ),
   INP1( COIN1, 0x600F, 0x04 ),
   INP1( COIN2, 0x600F, 0x08 ),
   END_INPUT
};

#define COINAGE_SILKWORM \
   { MSG_COIN1,               0x03, 0x04 },\
   { MSG_2COIN_1PLAY,         0x01, 0x00 },\
   { MSG_1COIN_1PLAY,         0x00, 0x00 },\
   { MSG_1COIN_2PLAY,         0x02, 0x00 },\
   { MSG_1COIN_3PLAY,         0x03, 0x00 },\
   { MSG_COIN2,               0x0C, 0x04 },\
   { MSG_2COIN_1PLAY,         0x04, 0x00 },\
   { MSG_1COIN_1PLAY,         0x00, 0x00 },\
   { MSG_1COIN_2PLAY,         0x08, 0x00 },\
   { MSG_1COIN_3PLAY,         0x0C, 0x00 },

/* Dipswitch B */
static struct DSW_DATA dsw_data_silkworm_B[] =
{
   { MSG_EXTRA_LIFE,          0x07, 0x08 },
   { _("50k, 200k and 500k"), 0x00 },
   { _("100k, 300k and 800k"),   0x01, 0x00 },
   { _("50k and 200k"),          0x02},
   { _("100k and 300k"),         0x03},
   { _("50k only"),              0x04},
   { _("100k only"),             0x05},
   { _("200k only"),             0x06},
   { _("None"),                  0x07},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x08},
   { MSG_DIFFICULTY,          0x70, 0x04 },
   { MSG_EASY,                0x00},
   { MSG_NORMAL,              0x30},
   { MSG_HARD,                0x10},	// same as 0x20 ?
   { MSG_HARDEST,             0x40},	// same as 0x50 ?
   /* 0x60 and 0x70 are the same as 0x00 */
   { MSG_CONTINUE_PLAY,       0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

/* Dipswitch A */
static struct DSW_DATA dsw_data_silkworm_A[] =
{
   COINAGE_SILKWORM
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x30},
   { "3",                     0x00},
   { "4",                     0x10},
   { "5",                     0x20},
   { MSG_UNKNOWN,             0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { MSG_DEMO_SOUND,          0x80, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_silkworm[] =
{
   { 0x6006, 0x80, dsw_data_silkworm_A },
   { 0x6008, 0x30, dsw_data_silkworm_B },
   { 0,        0,    NULL,      },
};


static struct YM3812interface ym3812_interface =
{
   1,              // 1 chip
   4000000,        // 4.0 MHz
   { 200 },        // Volume (emu only)
   { z80_irq_handler }
};

static int adpcm_pos,adpcm_end;

static void sw_adpcm_start(UINT32 address, UINT8 data){
	if(RaineSoundCard){
	  adpcm_pos = data << 8;
	  if (adpcm_pos > sample_size) {
	    adpcm_pos = adpcm_end;
	  }
	}
}

static void sw_adpcm_end(UINT32 address, UINT8 data){
  if(RaineSoundCard){
    //		print_ingame(120, gettext("ADPCM End: %i"), data);
    adpcm_end = (data + 1) << 8;
    if (adpcm_end > sample_size) {
      adpcm_end = adpcm_pos;
    }
  }
}

static void sw_adpcm_volume(UINT32 address, UINT8 data){
  if(RaineSoundCard){
    //		print_ingame(120, gettext("ADPCM Volume: %i"), data);
    MSM5205_set_volume(0,(data & 0x0f) * 255 / 15);
  }
}

static void tecmo_adpcm_int()
{
#if 0
	static int adpcm_data = -1;

	if (adpcm_pos >= adpcm_end ||
				adpcm_pos >= get_region_size(REGION_SOUND1))
		MSM5205_reset_w(0,1);
	else if (adpcm_data != -1)
	{
	  MSM5205_data_w(0,adpcm_data & 0x0f);
	  adpcm_data = -1;
	}
	else
	{
	  unsigned char *ROM = load_region[REGION_SOUND1];

	  adpcm_data = ROM[adpcm_pos++];
	  MSM5205_data_w(0,adpcm_data >> 4);
	}
#else
	if (adpcm_end > adpcm_pos) {
	  live_msm_decode(adpcm_pos,adpcm_end-adpcm_pos-1);
	  adpcm_pos++;
	}
#endif
}

static struct msm5205_adpcm_list silkworm_adpcm[MAX_MSM_ADPCM];

static struct MSM5205buffer_interface msm5205_interface =
  {
    1,
    { 8000 }, // 8 khz
    { 200 }, // volume
   { silkworm_adpcm },
   { sizeof(silkworm_adpcm) / sizeof(struct msm5205_adpcm_list) },
   { NULL },
   { 0 },
   { REGION_SOUND1 },
   MSM5205_MONO,
};

static struct SOUND_INFO sound_gemini[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { SOUND_MSM5205_BUFF, &msm5205_interface },
   { 0,             NULL,                 },
};


/******************
   SILKWORM SET 2
 ******************/


static struct ROM_INFO rom_silkwrm2[] =
{
   {           "r4", 0x10000, 0x6df3df22, REGION_CPU1, 0, LOAD_NORMAL, },   // cpu1
   {   "silkworm.5", 0x10000, 0xa6c7bb51, REGION_CPU1, 0xc000, LOAD_NORMAL, }, // cpu1
   {           "r3", 0x08000, 0xb79848d0, REGION_CPU2, 0, LOAD_NORMAL, }, // cpu2
   {   "silkworm.2", 0x08000, 0xe80a1cd9, 0, 0, 0, }, // char
   {   "silkworm.6", 0x10000, 0x1138d159, 0, 0, 0, }, // spr
   {   "silkworm.7", 0x10000, 0xd96214f7, 0, 0, 0, }, // spr
   {   "silkworm.8", 0x10000, 0x0494b38e, 0, 0, 0, }, // spr
   {   "silkworm.9", 0x10000, 0x8ce3cdf5, 0, 0, 0, }, // spr
   {   "silkworm.10",0x10000, 0x8c7138bb, 0, 0, 0, }, // tile1
   {   "silkworm.11",0x10000, 0x6c03c476, 0, 0, 0, }, // tile1
   {   "silkworm.12",0x10000, 0xbb0f568f, 0, 0, 0, }, // tile1
   {   "silkworm.13",0x10000, 0x773ad0a4, 0, 0, 0, }, // tile1
   {   "silkworm.14",0x10000, 0x409df64b, 0, 0, 0, }, // tile2
   {   "silkworm.15",0x10000, 0x6e4052c9, 0, 0, 0, }, // tile2
   {   "silkworm.16",0x10000, 0x9292ed63, 0, 0, 0, }, // tile2
   {   "silkworm.17",0x10000, 0x3fa4563d, 0, 0, 0, }, // tile2
   {   "silkworm.1", 0x08000, 0x5b553644, REGION_SOUND1, 0, LOAD_NORMAL, }, // adpcm
   {           NULL,          0,          0, 0, 0, 0, },
};


/******************
       RYGAR
 ******************/


static struct ROM_INFO rom_rygar[] =
{
   {         "5.5p", 0x08000, 0x062cd55d, REGION_CPU1, 0, LOAD_NORMAL },
   {   "cpu_5m.bin", 0x04000, 0x7ac5191b, REGION_CPU1, 0x8000, LOAD_NORMAL },
   {   "cpu_5j.bin", 0x08000, 0xed76d606, REGION_CPU1, 0xc000, LOAD_NORMAL },
   {   "cpu_4h.bin", 0x02000, 0xe4a2fa87, REGION_CPU2, 0, LOAD_NORMAL },
   {   "cpu_8k.bin", 0x08000, 0x4d482fb6, 0, 0, 0, }, // char
   {   "vid_6k.bin", 0x08000, 0xaba6db9e, 0, 0, 0, }, // spr
   {   "vid_6j.bin", 0x08000, 0xae1f2ed6, 0, 0, 0, }, // spr
   {   "vid_6h.bin", 0x08000, 0x46d9e7df, 0, 0, 0, }, // spr
   {   "vid_6g.bin", 0x08000, 0x45839c9a, 0, 0, 0, }, // spr
   {   "vid_6p.bin", 0x08000, 0x9eae5f8e, 0, 0, 0, }, // tile1
   {   "vid_6o.bin", 0x08000, 0x5a10a396, 0, 0, 0, }, // tile1
   {   "vid_6n.bin", 0x08000, 0x7b12cf3f, 0, 0, 0, }, // tile1
   {   "vid_6l.bin", 0x08000, 0x3cea7eaa, 0, 0, 0, }, // tile1
   {   "vid_6f.bin", 0x08000, 0x9840edd8, 0, 0, 0, }, // tile2
   {   "vid_6e.bin", 0x08000, 0xff65e074, 0, 0, 0, }, // tile2
   {   "vid_6c.bin", 0x08000, 0x89868c85, 0, 0, 0, }, // tile2
   {   "vid_6b.bin", 0x08000, 0x35389a7b, 0, 0, 0, }, // tile2
   {   "cpu_1f.bin", 0x04000, 0x3cc98c5a, REGION_SOUND1, 0, LOAD_NORMAL, }, // adpcm
   {           NULL,       0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_rygar[] =
{
   JOY_1
   INP1( P1_B1, 0x6001, 0x01 ),
   INP1( P1_B2, 0x6001, 0x02 ),
   INP1( SERVICE, 0x6001, 0x04 ),

   INP1( P2_LEFT, 0x6002, 0x02 ),
   INP1( P2_RIGHT, 0x6002, 0x01 ),
   INP1( P2_DOWN, 0x6002, 0x04 ),
   INP1( P2_UP, 0x6002, 0x08 ),

   INP1( P2_B1, 0x6003, 0x01 ),
   INP1( P2_B2, 0x6003, 0x02 ),

   INP1( P1_START, 0x6004, 0x02 ),
   INP1( P2_START, 0x6004, 0x01 ),
   INP1( COIN1, 0x6004, 0x08 ),
   INP1( COIN2, 0x6004, 0x04 ),
   END_INPUT
};

/* Dipswitch B */
static struct DSW_DATA dsw_data_rygar_B[] =
{
   { MSG_EXTRA_LIFE,          0x03, 0x04 },
   { _("50k, 200k and 500k"), 0x00 },
   { _("100k, 300k and 600k"),   0x01, 0x00 },
   { _("200k and 500k"),         0x02},
   { _("100k only"),             0x03},
   { MSG_UNKNOWN,             0x04, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x04},
   { MSG_UNKNOWN,             0x08, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x08},
   { MSG_DIFFICULTY,          0x30, 0x04 },
   { MSG_EASY,                0x00},
   { MSG_NORMAL,              0x10},
   { MSG_HARD,                0x20},
   { MSG_HARDEST,             0x30},
   { _("2P Start Anytime"),      0x40, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x40},
   { MSG_CONTINUE_PLAY,       0x80, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
   { NULL,                    0,   },
};

/* Dipswitch A */
static struct DSW_DATA dsw_data_rygar_A[] =
{
   COINAGE_SILKWORM
   { MSG_LIVES,               0x30, 0x04 },
   { "2",                     0x30},
   { "3",                     0x00},
   { "4",                     0x10},
   { "5",                     0x20},
   { MSG_CABINET,             0x40, 0x02 },
   { MSG_UPRIGHT,             0x40},
   { MSG_TABLE,               0x00},
   { MSG_UNKNOWN,             0x80, 0x02 },
   { MSG_OFF,                 0x00},
   { MSG_ON,                  0x80},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_rygar[] =
{
   { 0x6006, 0x40, dsw_data_rygar_A },
   { 0x6008, 0xD0, dsw_data_rygar_B },
   { 0,        0,    NULL,      },
};


/******************
    GEMINI WING
 ******************/


static struct ROM_INFO rom_gemini[] =
{
   {   "gw04-5s.rom",  0x10000, 0xff9de855, REGION_CPU1, 0, LOAD_NORMAL },
   {   "gw05-6s.rom",  0x10000, 0x5a6947a9, REGION_CPU1, 0xc000, LOAD_NORMAL },
   {   "gw03-5h.rom",  0x08000, 0x9bc79596, REGION_CPU2, 0, LOAD_NORMAL },
   {   "gw02-3h.rom",  0x08000, 0x7acc8d35, 0, 0, 0, }, // char
   {   "gw06-1c.rom",  0x10000, 0x4ea51631, 0, 0, 0, }, // spr
   {   "gw07-1d.rom",  0x10000, 0xda42637e, 0, 0, 0, }, // spr
   {   "gw08-1f.rom",  0x10000, 0x0b4e8d70, 0, 0, 0, }, // spr
   {   "gw09-1h.rom",  0x10000, 0xb65c5e4c, 0, 0, 0, }, // spr
   {   "gw10-1n.rom",  0x10000, 0x5e84cd4f, 0, 0, 0, }, // tile1
   {   "gw11-2na.rom", 0x10000, 0x08b458e1, 0, 0, 0, }, // tile1
   {   "gw12-2nb.rom", 0x10000, 0x229c9714, 0, 0, 0, }, // tile1
   {   "gw13-3n.rom",  0x10000, 0xc5dfaf47, 0, 0, 0, }, // tile1
   {   "gw14-1r.rom",  0x10000, 0x9c10e5b5, 0, 0, 0, }, // tile2
   {   "gw15-2ra.rom", 0x10000, 0x4cd18cfa, 0, 0, 0, }, // tile2
   {   "gw16-2rb.rom", 0x10000, 0xf911c7be, 0, 0, 0, }, // tile2
   {   "gw17-3r.rom",  0x10000, 0x79a9ce25, 0, 0, 0, }, // tile2
   {   "gw01-6a.rom",  0x08000, 0xd78afa05, REGION_SOUND1, 0, LOAD_NORMAL, }, // adpcm
   {            NULL,        0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_gemini[] =
{
   JOY_1
   INP1( P1_B1, 0x6001, 0x02 ),
   INP1( P1_B2, 0x6001, 0x01 ),

   JOY_2
   INP1( P2_B1, 0x6003, 0x02 ),
   INP1( P2_B2, 0x6003, 0x01 ),

   INP1( P1_START, 0x6005, 0x01 ),
   INP1( P2_START, 0x6005, 0x02 ),
   INP1( COIN1, 0x6005, 0x04 ),
   INP1( COIN2, 0x6005, 0x08 ),
   END_INPUT
};

/* Dipswitch B */
static struct DSW_DATA dsw_data_gemini_B[] =
{
   { MSG_LIVES,               0x03, 0x04 },
   { "2",                     0x03},
   { "3",                     0x00},
   { "4",                     0x01},
   { "5",                     0x02},
   { MSG_DIFFICULTY,          0x0c, 0x04 },
   { MSG_EASY,                0x00},
   { MSG_NORMAL,              0x04},
   { MSG_HARD,                0x08},
   { MSG_HARDEST,             0x0c},
   { MSG_EXTRA_LIFE,          0x70, 0x08 },
   { _("50k and 200k"),          0x00},
   { _("50k and 300k"),          0x10},
   { _("100k and 500k"),         0x20},
   { _("50k only"),              0x30},
   { _("100k only"),             0x40},
   { _("200k only"),             0x50},
   { _("300k only"),             0x60},
   { _("None"),                  0x70},
   { MSG_DEMO_SOUND,          0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

/* Dipswitch A */
static struct DSW_DATA dsw_data_gemini_A[] =
{
   { MSG_COIN1,               0x07, 0x08 },
   { MSG_2COIN_1PLAY,         0x06},
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_2COIN_3PLAY,         0x07},
   { MSG_1COIN_2PLAY,         0x01},
   { MSG_1COIN_3PLAY,         0x02},
   { MSG_1COIN_4PLAY,         0x03},
   { MSG_1COIN_5PLAY,         0x04},
   { MSG_1COIN_6PLAY,         0x05},
   { _("F. Round Continue"),     0x08, 0x02 },
   { _("Round 6"),               0x00},
   { _("Round 7"),               0x08},
   { MSG_COIN2,               0x70, 0x08 },
   { MSG_2COIN_1PLAY,         0x60},
   { MSG_1COIN_1PLAY,         0x00},
   { MSG_2COIN_3PLAY,         0x70},
   { MSG_1COIN_2PLAY,         0x10},
   { MSG_1COIN_3PLAY,         0x20},
   { MSG_1COIN_4PLAY,         0x30},
   { MSG_1COIN_5PLAY,         0x40},
   { MSG_1COIN_6PLAY,         0x50},
   { _("Buy in Final Round"),    0x80, 0x02 },
   { MSG_YES,                 0x80},
   { MSG_NO,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_gemini[] =
{
   { 0x6006, 0x88, dsw_data_gemini_A },
   { 0x6008, 0x04, dsw_data_gemini_B },
   { 0,        0,    NULL,      },
};



/**********************************************************************/
/**********************************************************************/


static UINT8 *TMP;
static UINT8 *RAM1;
static UINT8 *RAM2;
static UINT8 *ROM1;
static UINT8 *RAM_INPUT;

static UINT8 *RAM_BG;
static UINT8 *RAM_COLOR_BG;
static UINT8 *RAM_VIDEO_FG;
static UINT8 *RAM_COLOR_FG;
static UINT8 *RAM_VIDEO_TX;
static UINT8 *RAM_COLOR_TX;
static UINT8 *RAM_SPR;

static UINT8 *GFX_CHAR;
static UINT8 *GFX_CHAR_SOLID;
static UINT8 *GFX_TILE;
static UINT8 *GFX_TILE_SOLID;
static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static int   flip_screen;
static int   romset;

/************************************************************************/
/*	CPU1 write ports									*/
/************************************************************************/
static void sw_sound_command(UINT32 address, UINT8 data){
	(void)(data);
	sound_command = data;
	if(RaineSoundCard){
		nmi_trigger = 1;
		cpu_int_nmi(CPU_Z80_1);
		// print_ingame(120, gettext("CPU1 Writes: %i"), sound_command);
	}
}
static void sw_flip_screen(UINT32 address, UINT8 data){
//	print_ingame(120, gettext("Flip screen: %i"), data);
	flip_screen = data;
}
static void sw_bankswitch(UINT32 address, UINT8 data){
  data >>=3;
  z80a_set_bank(0,data);
}

/************************************************************************/
/*	CPU1 read ports									*/
/************************************************************************/
UINT8 sw_dsw_a_lo(UINT32 address){
	return ((RAM_INPUT[0x06] & 0x0F) + 0xF0);
}
UINT8 sw_dsw_a_hi(UINT32 address){
	return (((RAM_INPUT[0x06]& 0xF0)>>4) + 0xF0);
}
UINT8 sw_dsw_b_lo(UINT32 address){
	return ((RAM_INPUT[0x08] & 0x0F) + 0xF0);
}
UINT8 sw_dsw_b_hi(UINT32 address){
	return (((RAM_INPUT[0x08] & 0xF0)>>4) + 0xF0);
}


/************************************************************************/
/*	CPU2 write ports									*/
/************************************************************************/

static void sw_ym3812_control_port(UINT32 address, UINT8 data){
	if(RaineSoundCard){
		YM3812_control_port_0_w(address, data);
//		print_ingame(120, gettext("YM3812 control: %i"), data);
	}
}
static void sw_ym3812_write_port(UINT32 address, UINT8 data){
	if(RaineSoundCard){
		YM3812_write_port_0_w(address, data);
//		print_ingame(120, gettext("YM3812 write: %i"), data);
	}
}


/************************************************************************/
/*	CPU2 read ports									*/
/************************************************************************/

UINT8 sw_soundlatch(UINT32 address){
	int ta = 0x00;
	if(RaineSoundCard)
		ta = sound_command;
	nmi_trigger = 0;
	sound_command = 0;
//	print_ingame(120, gettext("CPU2 Reads: %i"), sound_command);
	return ta;
}



/************************************************************************/
/*	GFX LOADING										*/
/************************************************************************/

static void DecodeSilkwormGfx_8x8(char *file, float gfx_offs, int gfx_size){
	int ta,tb;

	if(!(load_rom(file, TMP, gfx_size))){
		print_ingame(120, gettext("ERROR: Unable to load gfx rom: %s"), file);
	}else{
		tb = gfx_offs * 0x20000;
		for(ta=0; ta<gfx_size; ta++){
			GFX[tb+1] = TMP[ta] & 0x0F;
			GFX[tb+0] = TMP[ta] >> 4;
			tb += 2;
		}
	}

}


static void DecodeSilkwormGfx_16x16(char *file, float gfx_offs, UINT32 gfx_size){
	int ta,tb;
	int i,j;

	if(!(load_rom(file, TMP, gfx_size))){
		print_ingame(120, gettext("ERROR: Unable to load gfx rom: %s"), file);
	}else{
		tb = gfx_offs * 0x20000;
		ta = 0;
		for(i=0; i<(gfx_size/128); i++){
			for(j=0; j<8; j++){
				GFX[tb+0]  = (TMP[ta+0] >> 4) & 0x0F;
				GFX[tb+1]  = (TMP[ta+0] >> 0) & 0x0F;
				GFX[tb+2]  = (TMP[ta+1] >> 4) & 0x0F;
				GFX[tb+3]  = (TMP[ta+1] >> 0) & 0x0F;
				GFX[tb+4]  = (TMP[ta+2] >> 4) & 0x0F;
				GFX[tb+5]  = (TMP[ta+2] >> 0) & 0x0F;
				GFX[tb+6]  = (TMP[ta+3] >> 4) & 0x0F;
				GFX[tb+7]  = (TMP[ta+3] >> 0) & 0x0F;
				GFX[tb+8]  = (TMP[ta+0+32] >> 4) & 0x0F;
				GFX[tb+9]  = (TMP[ta+0+32] >> 0) & 0x0F;
				GFX[tb+10] = (TMP[ta+1+32] >> 4) & 0x0F;
				GFX[tb+11] = (TMP[ta+1+32] >> 0) & 0x0F;
				GFX[tb+12] = (TMP[ta+2+32] >> 4) & 0x0F;
				GFX[tb+13] = (TMP[ta+2+32] >> 0) & 0x0F;
				GFX[tb+14] = (TMP[ta+3+32] >> 4) & 0x0F;
				GFX[tb+15] = (TMP[ta+3+32] >> 0) & 0x0F;
				tb += 16;
				ta += 4;
			}
			ta += 32;
			for(j=0; j<8; j++){
				GFX[tb+0]  = (TMP[ta+0] >> 4) & 0x0F;
				GFX[tb+1]  = (TMP[ta+0] >> 0) & 0x0F;
				GFX[tb+2]  = (TMP[ta+1] >> 4) & 0x0F;
				GFX[tb+3]  = (TMP[ta+1] >> 0) & 0x0F;
				GFX[tb+4]  = (TMP[ta+2] >> 4) & 0x0F;
				GFX[tb+5]  = (TMP[ta+2] >> 0) & 0x0F;
				GFX[tb+6]  = (TMP[ta+3] >> 4) & 0x0F;
				GFX[tb+7]  = (TMP[ta+3] >> 0) & 0x0F;
				GFX[tb+8]  = (TMP[ta+0+32] >> 4) & 0x0F;
				GFX[tb+9]  = (TMP[ta+0+32] >> 0) & 0x0F;
				GFX[tb+10] = (TMP[ta+1+32] >> 4) & 0x0F;
				GFX[tb+11] = (TMP[ta+1+32] >> 0) & 0x0F;
				GFX[tb+12] = (TMP[ta+2+32] >> 4) & 0x0F;
				GFX[tb+13] = (TMP[ta+2+32] >> 0) & 0x0F;
				GFX[tb+14] = (TMP[ta+3+32] >> 4) & 0x0F;
				GFX[tb+15] = (TMP[ta+3+32] >> 0) & 0x0F;
				tb += 16;
				ta += 4;
			}
			ta += 32;
		}
	}
}


/************************************************************************/
/*	MEMORY MAP										*/
/************************************************************************/

UINT8 nothing1,nothing2,nothing3;

static void MemoryMap_cpu1(void)
{
   AddZ80AROMBase(RAM1, 0x0038, 0x0066);

   z80_init_banks_area_gap(0,load_region[REGION_CPU1],
			   get_region_size(REGION_CPU1),0xc000,0xf000,0x800);
   z80a_set_bank(0,0);
   AddZ80AReadByte(0x0000, 0xBFFF, NULL,		NULL);	  // rom
   AddZ80AReadByte(0xC000, 0xEFFF, NULL,		RAM);	  // all RAM
   AddZ80AReadByte(0xF000, 0xF7FF, NULL,	NULL);	// Banked ROM

   AddZ80AReadByte(0xF800, 0xF805, NULL,		RAM_INPUT+0x00);  // inputs
   AddZ80AReadByte(0xF806, 0xF806, sw_dsw_a_lo,		NULL);		  // dsw 1_a
   AddZ80AReadByte(0xF807, 0xF807, sw_dsw_a_hi,		NULL);		  // dsw 1_b
   AddZ80AReadByte(0xF808, 0xF808, sw_dsw_b_lo,		NULL);		  // dsw 2_a
   AddZ80AReadByte(0xF809, 0xF809, sw_dsw_b_hi,		NULL);		  // dsw 2_b
   AddZ80AReadByte(0xF80F, 0xF80F, NULL,		RAM_INPUT+0x0F);  // coin (silkworm)
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,	NULL);		  // <bad reads>
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0xC000, 0xEFFF, NULL,		RAM);	  // all RAM

   AddZ80AWriteByte(0xF800, 0xF805, NULL,		RAM+0x4000);	  // bg scroll-x,y
   AddZ80AWriteByte(0xF806, 0xF806, sw_sound_command,	NULL);		  // Sound command
   AddZ80AWriteByte(0xF807, 0xF807, sw_flip_screen,	NULL);		  // Screen flip
   AddZ80AWriteByte(0xF808, 0xF808, sw_bankswitch,	NULL);		  // Bank switch
   AddZ80AWriteByte(0xF809, 0xF809, NULL,		&nothing1);		  // ???
   AddZ80AWriteByte(0xF80B, 0xF80B, NULL,		&nothing2);		  // ???
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,	NULL);		  // <bad writes>
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,		NULL);		  // <bad reads>
   AddZ80AReadPort(-1, -1, NULL, NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,		NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,		NULL);		  // <bad reads>
   AddZ80AWritePort(-1, -1, NULL, NULL);
}

static void MemoryMap_cpu2(void)
{
   AddZ80BROMBase(RAM2, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x7FFF, NULL,		      RAM2+0x0000); // ROM
   AddZ80BReadByte(0x8000, 0x87FF, NULL,		      RAM+0x5000); // RAM
   AddZ80BReadByte(0xC000, 0xC000, sw_soundlatch,	      NULL);	    // soundlatch
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,	      NULL);	    // <bad reads>

   //AddZ80BWriteByte(0x0000, 0x7FFF, NULL,		      NULL);	    // ROM
   AddZ80BWriteByte(0x2000, 0x207f, NULL,		      RAM2+0x2000);
   AddZ80BWriteByte(0x8000, 0x87FF, NULL,		      RAM+0x5000); // RAM
   AddZ80BWriteByte(0xA000, 0xA000, sw_ym3812_control_port,   NULL);	    // sound control port
   AddZ80BWriteByte(0xA001, 0xA001, sw_ym3812_write_port,     NULL);	    // sound write port
   AddZ80BWriteByte(0xC000, 0xC000, sw_adpcm_start,	      NULL);	    // sample start
   AddZ80BWriteByte(0xC400, 0xC400, sw_adpcm_end,	      NULL);	    // sample end
   AddZ80BWriteByte(0xC800, 0xC800, sw_adpcm_volume,	      NULL);	    // sample volume
   AddZ80BWriteByte(0xCC00, 0xCC00, NULL,		      &nothing3);	    // NMI ack.
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,	      NULL);	    // <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,		      NULL);	    // <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,		      NULL);
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,		      NULL);        // <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);
}

static void MemoryMap_cpu2_rygar(void)
{
   AddZ80BROMBase(RAM2, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0x3FFF, NULL,		      RAM2+0x0000); // ROM
   AddZ80BReadByte(0x4000, 0x47FF, NULL,		      RAM+0x5000); // RAM
   AddZ80BReadByte(0xC000, 0xC000, sw_soundlatch,	      NULL);	    // soundlatch
   AddZ80BReadByte(0x0000, 0xFFFF, DefBadReadZ80,	      NULL);	    // <bad reads>
   AddZ80BReadByte(-1, -1, NULL, NULL);

   //AddZ80BWriteByte(0x0000, 0x3FFF, NULL,		      NULL);	    // ROM
   AddZ80BWriteByte(0x4000, 0x47FF, NULL,		      RAM+0x5000); // RAM
   AddZ80BWriteByte(0x8000, 0x8000, sw_ym3812_control_port,   NULL);	    // sound control port
   AddZ80BWriteByte(0x8001, 0x8001, sw_ym3812_write_port,     NULL);	    // sound write port
   AddZ80BWriteByte(0xC000, 0xC000, sw_adpcm_start,	      NULL);	    // sample start
   AddZ80BWriteByte(0xD000, 0xD000, sw_adpcm_end,	      NULL);	    // sample end
   AddZ80BWriteByte(0xE000, 0xE000, sw_adpcm_volume,	      NULL);	    // sample volume
   AddZ80BWriteByte(0xF000, 0xF000, NULL,		      &nothing3);	    // NMI ack.
   AddZ80BWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,	      NULL);	    // <bad writes>
   AddZ80BWriteByte(-1, -1, NULL, NULL);

   AddZ80BReadPort(0x00, 0xFF, DefBadReadZ80,		      NULL);	    // <bad reads>
   AddZ80BReadPort(-1, -1, NULL, NULL);

   AddZ80BWritePort(0xAA, 0xAA, StopZ80BMode2,		      NULL);
   AddZ80BWritePort(0x00, 0xFF, DefBadWriteZ80,		      NULL);        // <bad reads>
   AddZ80BWritePort(-1, -1, NULL, NULL);
}


/************************************************************************/
/*	GAME LOAD										*/
/************************************************************************/

#define FRAME_Z80	CPU_FRAME_MHz(6,60)
#define FRAME_Z80_RYGAR	CPU_FRAME_MHz(4,60)

static void load_silkworm(void)
{
   romset=0;
   RAMSize=0x7000;
   sample_size = get_region_size(REGION_SOUND1);
   adpcm_pos = adpcm_end = 0;

   if(!(RAM=AllocateMem(RAMSize)))			return;
   if(!(GFX=AllocateMem(0x1A0000)))			return;
   if(!(TMP=AllocateMem(0x10000))) 			return;

   RAM_INPUT  = RAM+0x6000; // Cpu1 input
   RAM_PAL= RAM+0xE800 - 0xc000; // Fake palette ram

   memset(RAM, 0x00, RAMSize);

   flip_screen = 0;
   RAM1 = ROM;
   RAM2 = load_region[REGION_CPU2];

   /* SPEED HACK */
   RAM1[0x05da] = 0xD3;		// OUTA (AAh)
   RAM1[0x05db] = 0xAA;
   RAM1[0x05dc] = 0x00;		// NOP
   RAM1[0x05dd] = 0x00;		// NOP
   SetStopZ80Mode2(0x05dc);

   RAM_BG = RAM+0xC000 - 0xc000;
   RAM_COLOR_BG = RAM+0xC200 - 0xc000;
   RAM_VIDEO_FG = RAM+0xC400 - 0xc000;
   RAM_COLOR_FG = RAM+0xC600 - 0xc000;
   RAM_VIDEO_TX = RAM+0xC800 - 0xc000;
   RAM_COLOR_TX = RAM+0xCC00 - 0xc000;
   RAM_SPR= RAM+0xE000 - 0xc000;
   MemoryMap_cpu1();

   // CPU2

   if (is_current_game("silkworm")) {
       /* SPEED HACK */
       RAM2[0x00b4] = 0xD3;		// OUTA (AAh)
       RAM2[0x00b5] = 0xAA;
       SetStopZ80BMode2(0x00b4);
   } else {
       /* SPEED HACK */
       RAM2[0x00df] = 0xD3;		// OUTA (AAh)
       RAM2[0x00e0] = 0xAA;
       SetStopZ80BMode2(0x00df);
   }

   MemoryMap_cpu2();

   // GFX
   GFX_CHAR  = GFX + (0x20000 * 0);
   GFX_SPR   = GFX + (0x20000 * 1);
   GFX_TILE  = GFX + (0x20000 * 5);

   memset(GFX, 0x00, 0x1A0000);

   DecodeSilkwormGfx_8x8("silkworm.2", 0, 0x08000);		// characters

   DecodeSilkwormGfx_8x8("silkworm.6", 1, 0x10000);		// sprites
   DecodeSilkwormGfx_8x8("silkworm.7", 2, 0x10000);		// sprites
   DecodeSilkwormGfx_8x8("silkworm.8", 3, 0x10000);		// sprites
   DecodeSilkwormGfx_8x8("silkworm.9", 4, 0x10000);		// sprites

   DecodeSilkwormGfx_16x16("silkworm.10", 5, 0x10000);	// tiles 1
   DecodeSilkwormGfx_16x16("silkworm.11", 6, 0x10000);	// tiles 1
   DecodeSilkwormGfx_16x16("silkworm.12", 7, 0x10000);	// tiles 1
   DecodeSilkwormGfx_16x16("silkworm.13", 8, 0x10000);	// tiles 1

   DecodeSilkwormGfx_16x16("silkworm.14", 9, 0x10000);	// tiles 2
   DecodeSilkwormGfx_16x16("silkworm.15", 10, 0x10000);	// tiles 2
   DecodeSilkwormGfx_16x16("silkworm.16", 11, 0x10000);	// tiles 2
   DecodeSilkwormGfx_16x16("silkworm.17", 12, 0x10000);	// tiles 2

   // Setup palette
   InitPaletteMap(RAM_PAL, 0x40, 0x10, 0x10000);
   set_colour_mapper(&col_map_rrrr_gggg_xxxx_bbbb);

   // make solid mask
   GFX_CHAR_SOLID = make_solid_mask_8x8(   GFX_CHAR, 0x08000 / 32  );
   GFX_SPR_SOLID  = make_solid_mask_8x8(   GFX_SPR,  0x40000 / 32 );
   GFX_TILE_SOLID = make_solid_mask_16x16( GFX_TILE, 0x80000 / 128 );

   FreeMem(TMP);

   AddZ80AInit();
   AddZ80BInit();
   setup_z80_frame(CPU_Z80_1,FRAME_Z80);
}

static void load_rygar(void)
{
   romset=1;
   RAMSize=0x7000;
   sample_size = get_region_size(REGION_SOUND1);
   adpcm_pos = adpcm_end = 0;

   if(!(RAM=AllocateMem(RAMSize)))			return;
   if(!(GFX=AllocateMem(0x1A0000)))			return;
   if(!(TMP=AllocateMem(0x10000))) 			return;

   ROM1 = ROM+0x00000;	// Cpu1

   RAM1	      = ROM; // Cpu1
   RAM2       = load_region[REGION_CPU2];
   RAM_INPUT  = RAM+0x6000; // Cpu1 input
   RAM_PAL= RAM+0xE800 - 0xc000; // Fake palette ram

   memset(RAM, 0x00, RAMSize);

   flip_screen = 0;

   /* SPEED HACK */
//   RAM1[0x05da] = 0xD3;		// OUTA (AAh)
//   RAM1[0x05db] = 0xAA;
//   RAM1[0x05dc] = 0x00;		// NOP
//   RAM1[0x05dd] = 0x00;		// NOP
//   SetStopZ80Mode2(0x05dc);

   RAM_BG = RAM+0xDC00 - 0xc000;
   RAM_COLOR_BG = RAM_BG+0x0200;
   RAM_VIDEO_FG = RAM+0xD800 - 0xc000;
   RAM_COLOR_FG = RAM+0xDA00 - 0xc000;
   RAM_VIDEO_TX = RAM+0xD000 - 0xc000;
   RAM_COLOR_TX = RAM+0xD400 - 0xc000;
   RAM_SPR= RAM+0xE000 - 0xc000;

   MemoryMap_cpu1();


   /* SPEED HACK */
//   RAM2[0x00b4] = 0xD3;		// OUTA (AAh)
//   RAM2[0x00b5] = 0xAA;
//   SetStopZ80BMode2(0x00b4);

   MemoryMap_cpu2_rygar();


   // GFX
   GFX_CHAR  = GFX + (0x20000 * 0);
   GFX_SPR   = GFX + (0x20000 * 1);
   GFX_TILE  = GFX + (0x20000 * 3);

   memset(GFX, 0x00, 0x1A0000);

   DecodeSilkwormGfx_8x8("cpu_8k.bin", 0, 0x08000);		// characters

   DecodeSilkwormGfx_8x8("vid_6k.bin", 1,   0x08000);		// sprites
   DecodeSilkwormGfx_8x8("vid_6j.bin", 1.5, 0x08000);		// sprites
   DecodeSilkwormGfx_8x8("vid_6h.bin", 2,   0x08000);		// sprites
   DecodeSilkwormGfx_8x8("vid_6g.bin", 2.5, 0x08000);		// sprites

   DecodeSilkwormGfx_16x16("vid_6p.bin", 3,   0x08000);		// tiles 1
   DecodeSilkwormGfx_16x16("vid_6o.bin", 3.5, 0x08000);		// tiles 1
   DecodeSilkwormGfx_16x16("vid_6n.bin", 4,   0x08000);		// tiles 1
   DecodeSilkwormGfx_16x16("vid_6l.bin", 4.5, 0x08000);		// tiles 1

   DecodeSilkwormGfx_16x16("vid_6f.bin", 7,   0x08000);		// tiles 2
   DecodeSilkwormGfx_16x16("vid_6e.bin", 7.5, 0x08000);		// tiles 2
   DecodeSilkwormGfx_16x16("vid_6c.bin", 8,   0x08000);		// tiles 2
   DecodeSilkwormGfx_16x16("vid_6b.bin", 8.5, 0x08000);		// tiles 2

   // Setup palette
   InitPaletteMap(RAM_PAL, 0x40, 0x10, 0x10000);
   set_colour_mapper(&col_map_rrrr_gggg_xxxx_bbbb);

   // make solid mask
   GFX_CHAR_SOLID = make_solid_mask_8x8(   GFX_CHAR, 0x08000 / 32  );
   GFX_SPR_SOLID  = make_solid_mask_8x8(   GFX_SPR,  0x40000 / 32 );
   GFX_TILE_SOLID = make_solid_mask_16x16( GFX_TILE, 0x80000 / 128 );

   FreeMem(TMP);

   AddZ80AInit();
   AddZ80BInit();
   setup_z80_frame(CPU_Z80_1,FRAME_Z80_RYGAR);
}

static void load_gemini(void)
{
   romset=2;
   RAMSize=0x7000;
   sample_size = get_region_size(REGION_SOUND1);
   adpcm_pos = adpcm_end = 0;

   if(!(RAM=AllocateMem(RAMSize)))			return;
   if(!(GFX=AllocateMem(0x1A0000)))			return;
   if(!(TMP=AllocateMem(0x10000))) 			return;

   ROM1 = ROM+0x00000;	// Cpu1

   RAM1	      = ROM; // Cpu1
   RAM2       = load_region[REGION_CPU2];
   RAM_INPUT  = RAM+0x6000; // Cpu1 input
   RAM_PAL= RAM+0xE000 - 0xc000; // Fake palette ram

   memset(RAM, 0x00, RAMSize);

   flip_screen = 0;

   /* SPEED HACK */
   RAM1[0x05da] = 0xD3;		// OUTA (AAh)
   RAM1[0x05db] = 0xAA;
   RAM1[0x05dc] = 0x00;		// NOP
   RAM1[0x05dd] = 0x00;		// NOP
   SetStopZ80Mode2(0x05dc);

   RAM_BG = RAM+0xDC00 - 0xc000;
   RAM_COLOR_BG = RAM+0xDE00 - 0xc000;
   RAM_VIDEO_FG = RAM+0xD800 - 0xc000;
   RAM_COLOR_FG = RAM+0xDA00 - 0xc000;
   RAM_VIDEO_TX = RAM+0xD000 - 0xc000;
   RAM_COLOR_TX = RAM+0xD400 - 0xc000;
   RAM_SPR= RAM+0xE800 - 0xc000;

   MemoryMap_cpu1();

   /* SPEED HACK */
   RAM2[0x00b4] = 0xD3;		// OUTA (AAh)
   RAM2[0x00b5] = 0xAA;
   SetStopZ80BMode2(0x00b4);

   MemoryMap_cpu2();


   // GFX
   GFX_CHAR  = GFX + (0x20000 * 0);
   GFX_SPR   = GFX + (0x20000 * 1);
   GFX_TILE  = GFX + (0x20000 * 5);

   memset(GFX, 0x00, 0x1A0000);

   DecodeSilkwormGfx_8x8("gw02-3h.rom", 0, 0x08000);		// characters

   DecodeSilkwormGfx_8x8("gw06-1c.rom", 1, 0x10000);		// sprites
   DecodeSilkwormGfx_8x8("gw07-1d.rom", 2, 0x10000);		// sprites
   DecodeSilkwormGfx_8x8("gw08-1f.rom", 3, 0x10000);		// sprites
   DecodeSilkwormGfx_8x8("gw09-1h.rom", 4, 0x10000);		// sprites

   DecodeSilkwormGfx_16x16("gw10-1n.rom" , 5, 0x10000);		// tiles 1
   DecodeSilkwormGfx_16x16("gw11-2na.rom", 6, 0x10000);		// tiles 1
   DecodeSilkwormGfx_16x16("gw12-2nb.rom", 7, 0x10000);		// tiles 1
   DecodeSilkwormGfx_16x16("gw13-3n.rom" , 8, 0x10000);		// tiles 1

   DecodeSilkwormGfx_16x16("gw14-1r.rom" , 9, 0x10000);		// tiles 2
   DecodeSilkwormGfx_16x16("gw15-2ra.rom", 10, 0x10000);	// tiles 2
   DecodeSilkwormGfx_16x16("gw16-2rb.rom", 11, 0x10000);	// tiles 2
   DecodeSilkwormGfx_16x16("gw17-3r.rom" , 12, 0x10000);	// tiles 2

   // Setup palette
   InitPaletteMap(RAM_PAL, 0x40, 0x10, 0x10000);
   set_colour_mapper(&col_map_rrrr_gggg_xxxx_bbbb);

   // make solid mask
   GFX_CHAR_SOLID = make_solid_mask_8x8(   GFX_CHAR, 0x08000 / 32  );
   GFX_SPR_SOLID  = make_solid_mask_8x8(   GFX_SPR,  0x40000 / 32 );
   GFX_TILE_SOLID = make_solid_mask_16x16( GFX_TILE, 0x80000 / 128 );

   FreeMem(TMP);

   AddZ80AInit();
   AddZ80BInit();
   setup_z80_frame(CPU_Z80_1,FRAME_Z80);
}



/************************************************************************/
/*	GAME CLEAR										*/
/************************************************************************/
static void ClearSilkworm(void)
{
  memset(silkworm_adpcm,0,sizeof(silkworm_adpcm));
}


/************************************************************************/
/*	GAME EXECUTE									*/
/************************************************************************/
#if 0
static void execute_gemini(void)
{
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(6,60));	// Main Z80 6MHz (60fps)
   cpu_interrupt(CPU_Z80_0, 0x38);					// vbl interrupt

   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(4,60));	// Sub Z80 4MHz (60fps)
   triger_timers();
   //cpu_interrupt(CPU_Z80_1, 0x38);					// Sound interrupt

    cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(2,60));	// Sub Z80 4MHz (60fps)
    triger_timers();
   //cpu_interrupt(CPU_Z80_1, 0x38);					// Sound interrupt

/*   if (nmi_trigger != 0) */
/* 	cpu_int_nmi(CPU_Z80_1); */

}
#else

static void execute_gemini(void)
{
  int frame, diff;
  int speed_hack1 = 0,speed_hack2 = 0;
  if (romset==1)		// Rygar
    frame = FRAME_Z80_RYGAR;
  else
    frame = FRAME_Z80;
  while (frame > 0) {
    cpu_get_pc(CPU_Z80_1);
    if (!speed_hack1)
      diff = execute_one_z80_audio_frame(frame);
    else
      diff = frame;
    if (z80pc == 0xb4) {
      speed_hack1 = 1;
    }
    if (!speed_hack2) { // cycles = 0 if we reached the speed hack
      cpu_execute_cycles(CPU_Z80_0, diff*3/2);	// M68020 32MHz (60fps)
      if (z80pc == 0x5dc)
	speed_hack2 = 1;
    }

    frame -= diff;
  }
  cpu_interrupt(CPU_Z80_0, 0x38);
  tecmo_adpcm_int();
}
#endif


/************************************************************************/
/*	SPRITE DRAW										*/
/************************************************************************/
static void silkworm_draw_sprites(int _priority){
   const UINT8 layout[8][8] =
   {
	{0,1,4,5,16,17,20,21},
	{2,3,6,7,18,19,22,23},
	{8,9,12,13,24,25,28,29},
	{10,11,14,15,26,27,30,31},
	{32,33,36,37,48,49,52,53},
	{34,35,38,39,50,51,54,55},
	{40,41,44,45,56,57,60,61},
	{42,43,46,47,58,59,62,63}
   };
   UINT8 *map;
   int offs;
   int code;
   int flags;
   int x,y;
   int sx,sy,sc;
   int xpos,ypos;
   int flip,flipx,flipy;
   int priority;
   int size;
   int bank;


   for(offs=0; offs<0x800; offs+=8){
   if(RAM[0x4010+(offs>>3)]==0){

	flags		= RAM_SPR[offs+3];
	bank		= RAM_SPR[offs+0];
	priority	= flags>>6;

	if( (priority==_priority) && (bank&0x04) ){

		RAM[0x4010+(offs>>3)] = 1;

		size  = RAM_SPR[offs+2] & 0x03;
		if (romset==1)							// Rygar
		  code = RAM_SPR[offs+1] + ((bank & 0xF0) << 4);
		else
		  code = RAM_SPR[offs+1] + ((bank & 0xF8) << 5);
		code  &= ~((1 << (size<<1)) - 1);
		size  = 1 << size;

		xpos	= RAM_SPR[offs+5] - ((flags & 0x10) << 4);
		ypos 	= RAM_SPR[offs+4] - ((flags & 0x20) << 3);
		flip  = bank & 0x03;


		if(flip_screen){
			xpos 	= 256 - (size<<3) - xpos;
			ypos	= 256 - (size<<3) - ypos;
			flip = ~flip;
		}
		flipx = flip & 0x01;
		flipy = flip & 0x02;
		xpos += 32;
		ypos += 16;
		MAP_PALETTE_MAPPED_NEW(flags & 0x0F, 16, map);

		for(y=0; y<size; y++){
			for(x=0; x<size; x++){
				sx = xpos + ((flipx?(size-1-x):x)<<3);
				sy = ypos + ((flipy?(size-1-y):y)<<3);
				sc = code+layout[y][x];

			    if(GFX_SPR_SOLID[sc] && (sx>24) && (sy>14) && (sx<320) && (sy<280) ){
			        if(GFX_SPR_SOLID[sc]==1){		// Some pixels; trans
				  switch(flip & 0x03){
				    case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_SPR[sc<<6], sx, sy, map); break;
				    case 0x01: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_SPR[sc<<6], sx, sy, map);  break;
			      	    case 0x02: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_SPR[sc<<6], sx, sy, map);  break;
			            case 0x03: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_SPR[sc<<6], sx, sy, map); break;
				  }
				}else{
				  switch(flip & 0x03){			// all pixels; solid
				    case 0x00: Draw8x8_Mapped_Rot(&GFX_SPR[sc<<6], sx, sy, map); break;
				    case 0x01: Draw8x8_Mapped_FlipY_Rot(&GFX_SPR[sc<<6], sx, sy, map);  break;
			      	    case 0x02: Draw8x8_Mapped_FlipX_Rot(&GFX_SPR[sc<<6], sx, sy, map);  break;
			            case 0x03: Draw8x8_Mapped_FlipXY_Rot(&GFX_SPR[sc<<6], sx, sy, map); break;
				  }
			        }
			    }
			}
		}
	}
   }
   }
}



/************************************************************************/
/*	GAME DRAW										*/
/************************************************************************/
static void DrawSilkworm(void)
{
   UINT8 *map;
   int color;
   int code;
   SCROLL_REGS;

   ClearPaletteMap();

   MAP_PALETTE_MAPPED_NEW(
      16,
      16,
      map
   );

   // clear_game_screen because of priorities and this is the only way to
   // avoid the black sky !
   switch(display_cfg.bpp) {
   case 8:   clear_game_screen(map[0]); break;
   case 15:
   case 16: clear_game_screen(ReadWord(&map[0])); break;
   default: clear_game_screen(ReadLong(&map[0])); break;
   }

   memset(RAM+0x4010, 0x00, 0x100);

   /***************************/
   /* BACKGROUND LAYER		*/
   /***************************/
   silkworm_draw_sprites(3);

   MAKE_SCROLL_512x256_4_16(
	RAM[0x4003] + (RAM[0x4004]<<8) + 48,
	RAM[0x4005] - 240
   );

   START_SCROLL_512x256_4_16(32,16,256,240);

	color = RAM_COLOR_BG[zz>>2];
	if (romset==2)							// Gemini Wing
	  code  = RAM_BG[zz>>2] + ((color & 0x70)<<4);
	else
	  code  = RAM_BG[zz>>2] + ((color & 0x07)<<8);
	if(GFX_TILE_SOLID[2048 + code]){
		if (romset==2){							// Gemini Wing
		  MAP_PALETTE_MAPPED_NEW( 48+(color&0x0f), 16, map);
		}
		else{
		  MAP_PALETTE_MAPPED_NEW( 48+(color>>4), 16, map);
		}
		if(GFX_TILE_SOLID[2048+code]==1)
		  Draw16x16_Trans_Mapped_Rot(&GFX_TILE[0x80000+(code<<8)], x, 16+y, map);
		else
		  Draw16x16_Mapped_Rot(&GFX_TILE[0x80000+(code<<8)], x, 16+y, map);
	}

   END_SCROLL_512x256_4_16();


   /***************************/
   /* FOREGROUND LAYER		*/
   /***************************/
   silkworm_draw_sprites(2);

   MAKE_SCROLL_512x256_4_16(
	RAM[0x4000] + (RAM[0x4001]<<8) + 48,
	RAM[0x4002] - 240
   );

   START_SCROLL_512x256_4_16(32,16,256,240);

	color = RAM_COLOR_FG[zz>>2];
	if (romset==2)							// Gemini Wing
	  code  = RAM_VIDEO_FG[zz>>2] + ((color & 0x70)<<4);
	else
	  code  = RAM_VIDEO_FG[zz>>2] + ((color & 0x07)<<8);
	if(GFX_TILE_SOLID[code]){
		if (romset==2){							// Gemini Wing
		  MAP_PALETTE_MAPPED_NEW( 32+(color&0x0f), 16, map);
		}
		else{
		  MAP_PALETTE_MAPPED_NEW( 32+(color>>4), 16, map);
		}
		if(GFX_TILE_SOLID[code]==1)
		  Draw16x16_Trans_Mapped_Rot(&GFX_TILE[code<<8], x, 16+y, map);
		else
		  Draw16x16_Mapped_Rot(&GFX_TILE[code<<8], x, 16+y, map);
	}

   END_SCROLL_512x256_4_16();

   /***************************/
   /* TEXT LAYER			*/
   /***************************/
   silkworm_draw_sprites(1);

   for(x=0;x!=960;x++){
	code = RAM_VIDEO_TX[x] + ((RAM_COLOR_TX[x]&0x03)<<8);
	if(GFX_CHAR_SOLID[code]){
		MAP_PALETTE_MAPPED_NEW(16 + (RAM_COLOR_TX[x]>>4), 16, map);
		if(GFX_CHAR_SOLID[code]==1)
		  Draw8x8_Trans_Mapped_Rot(&GFX_CHAR[code<<6], 32 + ((x<<3)&0xF8), 16 + ((x>>2)&0xF8), map);
		else
		  Draw8x8_Mapped_Rot(&GFX_CHAR[code<<6], 32 + ((x<<3)&0xF8), 16 + ((x>>2)&0xF8), map);
	}
   }

   silkworm_draw_sprites(0);

}
static struct VIDEO_INFO video_gemini =
{
   DrawSilkworm,
   256,
   224,
   32,
   VIDEO_ROTATE_90 | VIDEO_ROTATABLE,
};
static struct VIDEO_INFO video_rygar =
{
   DrawSilkworm,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_gemini[] =
{
   { "gemini_wing", },
   { "gemini", },
   { NULL, },
};
GME( gemini, "Gemini Wing", TECMO, 1987, GAME_SHOOT,
	.clear = ClearSilkworm,
	.video = &video_gemini,
	.board = "6217",
);
GMEI( rygar, "Rygar - Legendary Warrior", TECMO, 1986, GAME_PLATFORM,
	.clear = ClearSilkworm,
	.board = "6217",
);
GMEI( silkworm, "Silkworm (Set 1)", TECMO, 1988, GAME_SHOOT,
	.clear = ClearSilkworm,
	.board = "6217",
);
static struct DIR_INFO dir_silkwrm2[] =
{
   { "silkworm_set2", },
   { "silkwrm2", },
   { ROMOF("silkworm"), },
   { CLONEOF("silkworm"), },
   { NULL, },
};
CLNE(silkwrm2, silkworm, "Silkworm (Set 2)", TECMO, 1988, GAME_SHOOT,
	.clear = ClearSilkworm,
	.board = "6217",
);

