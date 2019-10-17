/******************************************************************************/
/*                                                                            */
/*                      DARIUS (C) 1986 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "2203intf.h"
#include "msm5205.h"
#include "streams.h"

static WRITE_HANDLER( DariusVol );



static struct ROM_INFO rom_dariusj[] =
{
   { "a96_28-1.152", 0x00010000, 0xfb34d400, 0, 0, 0, },
   { "a96_29-1.185", 0x00010000, 0x75486f62, 0, 0, 0, },
   {   "a96_30.154", 0x00010000, 0x9eb5e127, 0, 0, 0, },
   {   "a96_31.187", 0x00010000, 0xe9bb5d89, 0, 0, 0, },
   { "a96_32-1.157", 0x00010000, 0xd9719de8, 0, 0, 0, },
   { "a96_33-1.190", 0x00010000, 0xff186048, 0, 0, 0, },
   { "a96_34-1.158", 0x00010000, 0xca3b2573, 0, 0, 0, },
   { "a96_35-1.191", 0x00010000, 0xb3280193, 0, 0, 0, },
   {   "a96_36.175", 0x00010000, 0xaf598141, 0, 0, 0, },
   {   "a96_37.196", 0x00010000, 0xb48137c8, 0, 0, 0, },
   {   "a96_38.176", 0x00010000, 0xe4f3e3a7, 0, 0, 0, },
   {   "a96_39.197", 0x00010000, 0xea30920f, 0, 0, 0, },
   {   "a96_40.177", 0x00010000, 0xb699a51e, 0, 0, 0, },
   {   "a96_41.198", 0x00010000, 0x97128a3a, 0, 0, 0, },
   {   "a96_42.178", 0x00010000, 0x7f55ee0f, 0, 0, 0, },
   {   "a96_43.199", 0x00010000, 0xc7cad469, 0, 0, 0, },
   {   "a96_44.179", 0x00010000, 0xbbc18878, 0, 0, 0, },
   {   "a96_45.200", 0x00010000, 0x616cdd8b, 0, 0, 0, },
   {   "a96_46.180", 0x00010000, 0xfec35418, 0, 0, 0, },
   {   "a96_47.201", 0x00010000, 0x8df9286a, 0, 0, 0, },
   {    "a96_48.24", 0x00010000, 0x39c9b3aa, 0, 0, 0, },
   {    "a96_49.25", 0x00010000, 0x37a7d88a, 0, 0, 0, },
   {    "a96_50.26", 0x00010000, 0x75d738e4, 0, 0, 0, },
   {    "a96_51.47", 0x00010000, 0x1bf8f0d3, 0, 0, 0, },
   {    "a96_52.48", 0x00010000, 0x2d9b2128, 0, 0, 0, },
   {    "a96_53.49", 0x00010000, 0x0173484c, 0, 0, 0, },
   {   "a96_54.143", 0x00004000, 0x51c02ae2, 0, 0, 0, },
   {   "a96_55.144", 0x00004000, 0x771e4d98, 0, 0, 0, },
   {    "a96_56.18", 0x00010000, 0x292ef55c, 0, 0, 0, },
   {    "a96_57.33", 0x00010000, 0x33ceb730, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_dariuso[] =
{
   {   "a96-28.152", 0x00010000, 0x4721d667, 0, 0, 0, },
   {   "a96-29.185", 0x00010000, 0xf775162b, 0, 0, 0, },
   {   "a96_30.154", 0x00010000, 0x9eb5e127, 0, 0, 0, },
   {   "a96_31.187", 0x00010000, 0xe9bb5d89, 0, 0, 0, },
   {   "a96-32.157", 0x00010000, 0x044c9848, 0, 0, 0, },
   {   "a96-33.190", 0x00010000, 0xd2f340d2, 0, 0, 0, },
   {   "a96-34.158", 0x00010000, 0x7556a660, 0, 0, 0, },
   {   "a96-35.191", 0x00010000, 0xb8ed718b, 0, 0, 0, },
   {   "a96_36.175", 0x00010000, 0xaf598141, 0, 0, 0, },
   {   "a96_37.196", 0x00010000, 0xb48137c8, 0, 0, 0, },
   {   "a96_38.176", 0x00010000, 0xe4f3e3a7, 0, 0, 0, },
   {   "a96_39.197", 0x00010000, 0xea30920f, 0, 0, 0, },
   {   "a96_40.177", 0x00010000, 0xb699a51e, 0, 0, 0, },
   {   "a96_41.198", 0x00010000, 0x97128a3a, 0, 0, 0, },
   {   "a96_42.178", 0x00010000, 0x7f55ee0f, 0, 0, 0, },
   {   "a96_43.199", 0x00010000, 0xc7cad469, 0, 0, 0, },
   {   "a96_44.179", 0x00010000, 0xbbc18878, 0, 0, 0, },
   {   "a96_45.200", 0x00010000, 0x616cdd8b, 0, 0, 0, },
   {   "a96_46.180", 0x00010000, 0xfec35418, 0, 0, 0, },
   {   "a96_47.201", 0x00010000, 0x8df9286a, 0, 0, 0, },
   {    "a96_48.24", 0x00010000, 0x39c9b3aa, 0, 0, 0, },
   {    "a96_49.25", 0x00010000, 0x37a7d88a, 0, 0, 0, },
   {    "a96_50.26", 0x00010000, 0x75d738e4, 0, 0, 0, },
   {    "a96_51.47", 0x00010000, 0x1bf8f0d3, 0, 0, 0, },
   {    "a96_52.48", 0x00010000, 0x2d9b2128, 0, 0, 0, },
   {    "a96_53.49", 0x00010000, 0x0173484c, 0, 0, 0, },
   {   "a96_54.143", 0x00004000, 0x51c02ae2, 0, 0, 0, },
   {   "a96_55.144", 0x00004000, 0x771e4d98, 0, 0, 0, },
   {    "a96_56.18", 0x00010000, 0x292ef55c, 0, 0, 0, },
   {    "a96_57.33", 0x00010000, 0x33ceb730, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

extern int YM2203_get_stream_num(int); // 2203intf.c

static struct INPUT_INFO input_darius[] =
{
   INP1( COIN1, 0x04200C, 0x01 ),
   INP1( COIN2, 0x04200C, 0x02 ),
   INP0( TILT, 0x04200C, 0x20 ),
   INP0( SERVICE, 0x04200C, 0x10 ),

   INP0( P1_START, 0x04200C, 0x04 ),
   INP0( P1_UP, 0x042008, 0x01 ),
   INP0( P1_DOWN, 0x042008, 0x02 ),
   INP0( P1_LEFT, 0x042008, 0x08 ),
   INP0( P1_RIGHT, 0x042008, 0x04 ),
   INP0( P1_B1, 0x042008, 0x10 ),
   INP0( P1_B2, 0x042008, 0x20 ),

   INP0( P2_START, 0x04200C, 0x08 ),
   INP0( P2_UP, 0x04200A, 0x01 ),
   INP0( P2_DOWN, 0x04200A, 0x02 ),
   INP0( P2_LEFT, 0x04200A, 0x08 ),
   INP0( P2_RIGHT, 0x04200A, 0x04 ),
   INP0( P2_B1, 0x04200A, 0x10 ),
   INP0( P2_B2, 0x04200A, 0x20 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_darius_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { _("Auto Turbo Fire"),       0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { MSG_COIN1,               0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_1COIN_2PLAY,         0x20},
   { MSG_2COIN_3PLAY,         0x10},
   { MSG_2COIN_1PLAY,         0x00},
   { MSG_COIN2,               0xC0, 0x04 },
   { MSG_1COIN_1PLAY,         0xC0},
   { MSG_1COIN_2PLAY,         0x80},
   { MSG_2COIN_3PLAY,         0x40},
   { MSG_2COIN_1PLAY,         0x00},
   { NULL,                    0,   },
};

static struct DSW_DATA dsw_data_darius_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Ship"),            0x0C, 0x04 },
   { _("30k 100k"),              0x0C},
   { _("20k 80k"),               0x08},
   { _("40k 200k"),              0x04},
   { _("50k 250k"),              0x00},
   { _("Ships"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "5",                     0x20},
   { "1",                     0x10},
   { "2",                     0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_darius[] =
{
   { 0x042010, 0xFF, dsw_data_darius_0 },
   { 0x042011, 0xFF, dsw_data_darius_1 },
   { 0,        0,    NULL,      },
};


static struct YM2203interface ym2203_interface =
{
  2,
  4000000,
  { YM2203_VOL(120,50), YM2203_VOL(120,50) }, // 0x2028
  //{ 0x00ff2040, 0x00ff2040 },
  { 0 },
  { 0 },
  { DariusVol, NULL },
  { NULL, NULL },
  { NULL, NULL }
};

static struct msm5205_adpcm_list darius_adpcm[] =
{
  { 0x00000,0x00000 },		/* dummy code */
  { 0x0aa97,0x0eaf7 },
  { 0x00500,0x01260 },
  { 0x01261,0x019d1 },
  { 0x019d2,0x02409 },
  { 0x0240a,0x02b4a },
  { 0x02b4b,0x036fb },
  { 0x036fc,0x040d4 },
  { 0x040d5,0x04be5 },
  { 0x04be6,0x055de },
  { 0x055df,0x05e1f },
  { 0x05e40,0x06440 },
  { 0x06481,0x06a81 },
  { 0x06ac2,0x070c2 },
  { 0x070e3,0x07603 },
  { 0x07604,0x07a82 },
  { 0x07a83,0x07dc3 },
  { 0x07dc4,0x08284 },
  { 0x08285,0x087c5 },
  { 0x087c6,0x09006 },
  { 0x09007,0x0975b },
  { 0x0975c,0x09e94 },
  { 0x09e85,0x0a8d5 },
  { 0x0a8d6,0x0aa96 },
  { 0x08285,0x087c5 },
  { 0x00500,0x01260 },
  { 0x00500,0x01260 },
  { 0x00500,0x01260 },
  { 0x00500,0x01260 },
  { 0x00500,0x01260 },
};

static struct MSM5205buffer_interface msm5205_interface =
{
   1,
   { 8000 },
   { 120 },
   { darius_adpcm },
   { sizeof(darius_adpcm) / sizeof(struct msm5205_adpcm_list) },
   { NULL },
   { 0 },
   { 0 },
   MSM5205_MONO,
};

static struct SOUND_INFO sound_darius[] =
{
   { SOUND_YM2203,  &ym2203_interface,    },
   { SOUND_MSM5205_BUFF, &msm5205_interface,   },
   { 0,             NULL,                 },
};

static struct ROM_INFO rom_dariuse[] =
{
   { "dae-67.bin", 0x00010000, 0xb99aea8c, 0, 0, 0, },
   { "dae-68.bin", 0x00010000, 0xed721127, 0, 0, 0, },
   {   "a96_30.154", 0x00010000, 0x9eb5e127, 0, 0, 0, },
   { "dae-70.bin", 0x00010000, 0x54590b31, 0, 0, 0, },
   { "dae-71.bin", 0x00010000, 0x65dd0403, 0, 0, 0, },
   { "dae-72.bin", 0x00010000, 0x248ca2cc, 0, 0, 0, },
   { "dae-73.bin", 0x00010000, 0x27036a4d, 0, 0, 0, },
   { "dae-74.bin", 0x00010000, 0x0ea31f60, 0, 0, 0, },
   {   "a96_36.175", 0x00010000, 0xaf598141, 0, 0, 0, },
   {   "a96_37.196", 0x00010000, 0xb48137c8, 0, 0, 0, },
   {   "a96_38.176", 0x00010000, 0xe4f3e3a7, 0, 0, 0, },
   {   "a96_39.197", 0x00010000, 0xea30920f, 0, 0, 0, },
   {   "a96_40.177", 0x00010000, 0xb699a51e, 0, 0, 0, },
   {   "a96_41.198", 0x00010000, 0x97128a3a, 0, 0, 0, },
   {   "a96_42.178", 0x00010000, 0x7f55ee0f, 0, 0, 0, },
   {   "a96_43.199", 0x00010000, 0xc7cad469, 0, 0, 0, },
   {   "a96_44.179", 0x00010000, 0xbbc18878, 0, 0, 0, },
   {   "a96_45.200", 0x00010000, 0x616cdd8b, 0, 0, 0, },
   {   "a96_46.180", 0x00010000, 0xfec35418, 0, 0, 0, },
   {   "a96_47.201", 0x00010000, 0x8df9286a, 0, 0, 0, },
   {    "a96_48.24", 0x00010000, 0x39c9b3aa, 0, 0, 0, },
   {    "a96_49.25", 0x00010000, 0x37a7d88a, 0, 0, 0, },
   {    "a96_50.26", 0x00010000, 0x75d738e4, 0, 0, 0, },
   {    "a96_51.47", 0x00010000, 0x1bf8f0d3, 0, 0, 0, },
   {    "a96_52.48", 0x00010000, 0x2d9b2128, 0, 0, 0, },
   {    "a96_53.49", 0x00010000, 0x0173484c, 0, 0, 0, },
   {   "a96_54.143", 0x00004000, 0x51c02ae2, 0, 0, 0, },
   {   "a96_55.144", 0x00004000, 0x771e4d98, 0, 0, 0, },
   {    "a96_56.18", 0x00010000, 0x292ef55c, 0, 0, 0, },
   {    "a96_57.33", 0x00010000, 0x33ceb730, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_darius[] =
{
   {    "da-58.bin", 0x00010000, 0x5f71e697, 0, 0, 0, },
   {    "da-59.bin", 0x00010000, 0x11aab4eb, 0, 0, 0, },
   {   "a96_30.154", 0x00010000, 0x9eb5e127, 0, 0, 0, },
   {   "a96_31.187", 0x00010000, 0xe9bb5d89, 0, 0, 0, },
   { "a96_32-1.157", 0x00010000, 0xd9719de8, 0, 0, 0, },
   { "a96_33-1.190", 0x00010000, 0xff186048, 0, 0, 0, },
   { "a96_34-1.158", 0x00010000, 0xca3b2573, 0, 0, 0, },
   { "a96_35-1.191", 0x00010000, 0xb3280193, 0, 0, 0, },
   {    "da-62.bin", 0x00010000, 0x9179862c, 0, 0, 0, },
   {    "da-63.bin", 0x00010000, 0xfa19cfff, 0, 0, 0, },
   {    "da-64.bin", 0x00010000, 0x814c676f, 0, 0, 0, },
   {    "da-65.bin", 0x00010000, 0x14eee326, 0, 0, 0, },
   {   "a96_40.177", 0x00010000, 0xb699a51e, 0, 0, 0, },
   {   "a96_41.198", 0x00010000, 0x97128a3a, 0, 0, 0, },
   {   "a96_42.178", 0x00010000, 0x7f55ee0f, 0, 0, 0, },
   {   "a96_43.199", 0x00010000, 0xc7cad469, 0, 0, 0, },
   {   "a96_44.179", 0x00010000, 0xbbc18878, 0, 0, 0, },
   {   "a96_45.200", 0x00010000, 0x616cdd8b, 0, 0, 0, },
   {   "a96_46.180", 0x00010000, 0xfec35418, 0, 0, 0, },
   {   "a96_47.201", 0x00010000, 0x8df9286a, 0, 0, 0, },
   {    "a96_48.24", 0x00010000, 0x39c9b3aa, 0, 0, 0, },
   {    "a96_49.25", 0x00010000, 0x37a7d88a, 0, 0, 0, },
   {    "a96_50.26", 0x00010000, 0x75d738e4, 0, 0, 0, },
   {    "a96_51.47", 0x00010000, 0x1bf8f0d3, 0, 0, 0, },
   {    "a96_52.48", 0x00010000, 0x2d9b2128, 0, 0, 0, },
   {    "a96_53.49", 0x00010000, 0x0173484c, 0, 0, 0, },
   {   "a96_54.143", 0x00004000, 0x51c02ae2, 0, 0, 0, },
   {   "a96_55.144", 0x00004000, 0x771e4d98, 0, 0, 0, },
   {    "a96_56.18", 0x00010000, 0x292ef55c, 0, 0, 0, },
   {    "a96_57.33", 0x00010000, 0x33ceb730, 0, 0, 0, },
   {    "da-61.bin", 0x00010000, 0x4736aa9b, 0, 0, 0, },
   {    "da-66.bin", 0x00010000, 0x4ede5f56, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static void DariusYM2203SetFMPan( UINT16 offset, UINT8 data );
static void DariusYM2203SetAYPan( UINT16 offset, UINT8 data );
static void DariusMSM5205SetPan( UINT16 offset, UINT8 data );

static void DariusWrite_ADPCM(UINT16 offset, UINT8 data);

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_FG0;
static UINT8 *GFX_FG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static int tcpu;

static UINT16 BadReadWord(UINT32 address)
{
#ifdef RAINE_DEBUG
       if(address!=0x0B0000)print_debug("Rw%01d(%06x) [%06x]\n",tcpu,address,s68000context.pc);
#endif
   return(0xFFFF);
}

static void BadWriteWord(UINT32 address, UINT16 data)
{
#ifdef RAINE_DEBUG
      if(address!=0x0B0000)print_debug("Ww%01d(%06x,%04x) [%06x]\n",tcpu,address,data,s68000context.pc);
#endif
}

static UINT8 darius_ioc_rb(UINT32 address)
{
   address&=0xFF;

   switch(address){
      case 0x01:
      case 0x03:
         return tc0140syt_read_main_68k(address);
      break;
      default:
         return RAM[0x42000+(address^1)];
      break;
   }
}

static UINT16 darius_ioc_rw(UINT32 address)
{
   UINT16 ret;

   ret  = darius_ioc_rb(address+0)<<8;
   ret |= darius_ioc_rb(address+1)<<0;

   return ret;
}

static void darius_ioc_wb(UINT32 address, UINT8 data)
{
   address&=0xFF;

   switch(address){
      case 0x01:
      case 0x03:
         tc0140syt_write_main_68k(address, data);
      break;
      case 0x61:
         RAM[0x42000+(address^1)] = data;
         switch_led(0,((data>>3)&1)|((data>>4)&1));	// Coin A [Coin Inserted] + Player Start Game
         switch_led(1,((data>>6)&1)|((data>>4)&1));	// Coin B [Coin Inserted] + Player Start Game
       //switch_led(0,((data>>3)&1));			// Coin A [Coin Inserted]
       //switch_led(1,((data>>6)&1));			// Coin B [Coin Inserted]
         switch_led(2,((data>>1)&1));			// Coin A [Ready for coins]
       //switch_led(3,((data>>2)&1));			// Coin B [Ready for coins]
       //switch_led(4,((data>>4)&1));			// Player Start Game
      break;
      default:
         RAM[0x42000+(address^1)] = data;
      break;
   }
}

static void darius_ioc_ww(UINT32 address, UINT16 data)
{
   darius_ioc_wb(address+0, (UINT8) ((data>>8)&0xFF));
   darius_ioc_wb(address+1, (UINT8) ((data>>0)&0xFF));
}

static void load_darius()
{
   int ta,tb,tc,romset;
   if (is_current_game("dariusj"))
       romset = 0;
   else if (is_current_game("dariuse"))
       romset = 1;
   else if (is_current_game("darius"))
       romset = 2;
   else if (is_current_game("dariuso"))
       romset = 3;

   RAMSize=0x80000;

   if(!(ROM=AllocateMem(0xA0000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0xC0000+0x20000+0x180000))) return;

   GFX_BG0=GFX+0x000000;
   GFX_FG0=GFX+0x0C0000;
   GFX_SPR=GFX+0x0E0000;

   if(!load_rom_index(16, RAM+0x00000, 0x10000)) return;		// 16x16 Sprites
   if(!load_rom_index(12, RAM+0x10000, 0x10000)) return;
   if(!load_rom_index( 8, RAM+0x20000, 0x10000)) return;
   tb=0;
   for(ta=0;ta<0x30000;ta++){
      tc=RAM[ta];
      GFX_SPR[tb+0]=((tc&0x80)>>7)<<0;
      GFX_SPR[tb+1]=((tc&0x40)>>6)<<0;
      GFX_SPR[tb+2]=((tc&0x20)>>5)<<0;
      GFX_SPR[tb+3]=((tc&0x10)>>4)<<0;
      GFX_SPR[tb+4]=((tc&0x08)>>3)<<0;
      GFX_SPR[tb+5]=((tc&0x04)>>2)<<0;
      GFX_SPR[tb+6]=((tc&0x02)>>1)<<0;
      GFX_SPR[tb+7]=((tc&0x01)>>0)<<0;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom_index(17, RAM+0x00000, 0x10000)) return;		// 16x16 Sprites
   if(!load_rom_index(13, RAM+0x10000, 0x10000)) return;
   if(!load_rom_index( 9, RAM+0x20000, 0x10000)) return;
   tb=0;
   for(ta=0;ta<0x30000;ta++){
      tc=RAM[ta];
      GFX_SPR[tb+0]|=((tc&0x80)>>7)<<1;
      GFX_SPR[tb+1]|=((tc&0x40)>>6)<<1;
      GFX_SPR[tb+2]|=((tc&0x20)>>5)<<1;
      GFX_SPR[tb+3]|=((tc&0x10)>>4)<<1;
      GFX_SPR[tb+4]|=((tc&0x08)>>3)<<1;
      GFX_SPR[tb+5]|=((tc&0x04)>>2)<<1;
      GFX_SPR[tb+6]|=((tc&0x02)>>1)<<1;
      GFX_SPR[tb+7]|=((tc&0x01)>>0)<<1;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom_index(18, RAM+0x00000, 0x10000)) return;		// 16x16 Sprites
   if(!load_rom_index(14, RAM+0x10000, 0x10000)) return;
   if(!load_rom_index(10, RAM+0x20000, 0x10000)) return;
   tb=0;
   for(ta=0;ta<0x30000;ta++){
      tc=RAM[ta];
      GFX_SPR[tb+0]|=((tc&0x80)>>7)<<2;
      GFX_SPR[tb+1]|=((tc&0x40)>>6)<<2;
      GFX_SPR[tb+2]|=((tc&0x20)>>5)<<2;
      GFX_SPR[tb+3]|=((tc&0x10)>>4)<<2;
      GFX_SPR[tb+4]|=((tc&0x08)>>3)<<2;
      GFX_SPR[tb+5]|=((tc&0x04)>>2)<<2;
      GFX_SPR[tb+6]|=((tc&0x02)>>1)<<2;
      GFX_SPR[tb+7]|=((tc&0x01)>>0)<<2;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }
   if(!load_rom_index(19, RAM+0x00000, 0x10000)) return;		// 16x16 Sprites
   if(!load_rom_index(15, RAM+0x10000, 0x10000)) return;
   if(!load_rom_index(11, RAM+0x20000, 0x10000)) return;
   tb=0;
   for(ta=0;ta<0x30000;ta++){
      tc=RAM[ta];
      GFX_SPR[tb+0]|=((tc&0x80)>>7)<<3;
      GFX_SPR[tb+1]|=((tc&0x40)>>6)<<3;
      GFX_SPR[tb+2]|=((tc&0x20)>>5)<<3;
      GFX_SPR[tb+3]|=((tc&0x10)>>4)<<3;
      GFX_SPR[tb+4]|=((tc&0x08)>>3)<<3;
      GFX_SPR[tb+5]|=((tc&0x04)>>2)<<3;
      GFX_SPR[tb+6]|=((tc&0x02)>>1)<<3;
      GFX_SPR[tb+7]|=((tc&0x01)>>0)<<3;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=8;}}
   }

   if(!load_rom_index(20, RAM+0x00000, 0x10000)) return;	// 8x8 BG0
   if(!load_rom_index(21, RAM+0x10000, 0x10000)) return;
   if(!load_rom_index(22, RAM+0x20000, 0x10000)) return;
   tb=0;
   for(ta=0;ta<0x30000;ta++,tb+=4){
      GFX_BG0[tb+0]=RAM[ta]>>4;
      GFX_BG0[tb+1]=RAM[ta]&15;
   }
   if(!load_rom_index(23, RAM+0x00000, 0x10000)) return;
   if(!load_rom_index(24, RAM+0x10000, 0x10000)) return;
   if(!load_rom_index(25, RAM+0x20000, 0x10000)) return;
   tb=0;
   for(ta=0;ta<0x30000;ta++,tb+=4){
      GFX_BG0[tb+2]=RAM[ta]>>4;
      GFX_BG0[tb+3]=RAM[ta]&15;
   }
   if(!load_rom_index(27, RAM+0x00000, 0x4000)) return;		// 8x8 FG0
   tb=0;
   for(ta=0;ta<0x4000;ta++){
      tc=RAM[ta];
      GFX_FG0[tb+0]=((tc&0x80)>>7)<<0;
      GFX_FG0[tb+1]=((tc&0x40)>>6)<<0;
      GFX_FG0[tb+2]=((tc&0x20)>>5)<<0;
      GFX_FG0[tb+3]=((tc&0x10)>>4)<<0;
      GFX_FG0[tb+4]=((tc&0x08)>>3)<<0;
      GFX_FG0[tb+5]=((tc&0x04)>>2)<<0;
      GFX_FG0[tb+6]=((tc&0x02)>>1)<<0;
      GFX_FG0[tb+7]=((tc&0x01)>>0)<<0;
      tb+=8;
   }
   if(!load_rom_index(26, RAM+0x00000, 0x4000)) return;
   tb=0;
   for(ta=0;ta<0x4000;ta++){
      tc=RAM[ta];
      GFX_FG0[tb+0]|=((tc&0x80)>>7)<<1;
      GFX_FG0[tb+1]|=((tc&0x40)>>6)<<1;
      GFX_FG0[tb+2]|=((tc&0x20)>>5)<<1;
      GFX_FG0[tb+3]|=((tc&0x10)>>4)<<1;
      GFX_FG0[tb+4]|=((tc&0x08)>>3)<<1;
      GFX_FG0[tb+5]|=((tc&0x04)>>2)<<1;
      GFX_FG0[tb+6]|=((tc&0x02)>>1)<<1;
      GFX_FG0[tb+7]|=((tc&0x01)>>0)<<1;
      tb+=8;
   }

   GFX_BG0_SOLID = make_solid_mask_8x8  (GFX_BG0, 0x3000);
   GFX_FG0_SOLID = make_solid_mask_8x8  (GFX_FG0, 0x0800);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x1800);

   memset(RAM,0xFF,0x30000);
   if(!load_rom_index(1, RAM+0x00000, 0x10000)) return;		// 68000 MAIN
   if(romset==2){
   if(!load_rom_index(30,RAM+0x10000, 0x10000)) return;
   }
   if(!load_rom_index(3, RAM+0x20000, 0x10000)) return;

   for(ta=0;ta<0x30000;ta++){
      ROM[ta+ta]=RAM[ta];
   }

   memset(RAM,0xFF,0x30000);
   if(!load_rom_index(0, RAM+0x00000, 0x10000)) return;		// 68000 MAIN
   if(romset==2){
   if(!load_rom_index(31,RAM+0x10000, 0x10000)) return;
   }
   if(!load_rom_index(2, RAM+0x20000, 0x10000)) return;

   for(ta=0;ta<0x30000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(!load_rom_index(5, RAM+0x00000, 0x10000)) return;		// 68000 SUB
   if(!load_rom_index(7, RAM+0x10000, 0x10000)) return;

   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x60000]=RAM[ta];
   }

   if(!load_rom_index(4, RAM+0x00000, 0x10000)) return;		// 68000 SUB
   if(!load_rom_index(6, RAM+0x10000, 0x10000)) return;

   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x60001]=RAM[ta];
   }

   /*----------------------*/

   if(!(PCMROM=AllocateMem(0x10000))) return;
   if(!load_rom_index(28, PCMROM, 0x10000)) return;

   Z80ROM=RAM+0x44000;
   if(!load_rom_index(29, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM
   // if(!load_rom("a96_56.18", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   Z80ROM[0x0270]=0xD3;	// OUTA (AAh)
   Z80ROM[0x0271]=0xAA;	//

   SetStopZ80Mode2(0x0263);

   // Setup rom banking
   // -----------------

   AddTaitoSoundBanking(Z80ROM, 0x10000);

   // Setup Z80 memory interface
   // --------------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0x7FFF, NULL,		   NULL);		// BANK ROM
   AddZ80AReadByte(0x8000, 0x8FFF, NULL,		   Z80ROM+0x008000);	// Z80 RAM
   AddZ80AReadByte(0x9000, 0x9001, YM2203AReadZ80,         NULL);		// YM2203 A
   AddZ80AReadByte(0xA000, 0xA001, YM2203BReadZ80,         NULL);		// YM2203 B
   AddZ80AReadByte(0xB000, 0xB001, tc0140syt_read_sub_z80, NULL);		// 68000 COMM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,          NULL);
   AddZ80AReadByte(-1, -1, NULL, NULL);

   AddZ80AWriteByte(0x8000, 0x8FFF, NULL,		    Z80ROM+0x008000);	// Z80 RAM
   AddZ80AWriteByte(0x9000, 0x9001, YM2203AWriteZ80,        NULL);		// YM2203 A
   AddZ80AWriteByte(0xA000, 0xA001, YM2203BWriteZ80,        NULL);		// YM2203 B
   AddZ80AWriteByte(0xB000, 0xB001, tc0140syt_write_sub_z80,NULL);		// 68000 COMM
   AddZ80AWriteByte(0xD400, 0xD400, DariusWrite_ADPCM,      NULL);		// ADPCM COMM
   AddZ80AWriteByte(0xDC00, 0xDC00, TaitoSoundSetBank,      NULL);		// BANK SELECT
     AddZ80AWriteByte(0xC000, 0xC000, DariusYM2203SetFMPan,   NULL); /* YM2203 FM #0 pan */
     AddZ80AWriteByte(0xC400, 0xC400, DariusYM2203SetFMPan,   NULL); /* YM2203 FM #1 pan */
     AddZ80AWriteByte(0xC800, 0xC800, DariusYM2203SetAYPan,   NULL); /* YM2203 PSG #0 pan */
     AddZ80AWriteByte(0xCC00, 0xCC00, DariusYM2203SetAYPan,   NULL); /* YM2203 PSG #1 pan */
     AddZ80AWriteByte(0xD000, 0xD000, DariusMSM5205SetPan,    NULL); /* ADPCM pan */
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,         NULL);
   AddZ80AWriteByte(-1, -1, NULL, NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0xAA, 0xAA, StopZ80Mode2,           NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

   TaitoSoundSetBank(0,1);

   tc0140syt_reset();			// Add [J3d!]

   msm5205_interface.rom[0] = PCMROM;
   msm5205_interface.romsize[0] = 0x10000;
   msm5205_interface.updatemode = MSM5205_STEREO;

   /************************************/


   if(romset==0){		// Original

   // Main 68000 Speed Hack

   WriteLong68k(&ROM[0x0070C],0x13FC0000);
   WriteLong68k(&ROM[0x00710],0x00AA0000);
   WriteWord68k(&ROM[0x00714],0x6100-20);

   WriteLong68k(&ROM[0x00938],0x13FC0000);
   WriteLong68k(&ROM[0x0093C],0x00AA0000);

   // Sub 68000 Speed Hack

   WriteLong68k(&ROM[0x606FA],0x13FC0000);
   WriteLong68k(&ROM[0x606FE],0x00AA0000);
   WriteWord68k(&ROM[0x60702],0x6100-16);

   WriteLong68k(&ROM[0x6F074],0x13FC0000);
   WriteLong68k(&ROM[0x6F078],0x00AA0000);

   // Fix Main 68000 Checksum

   WriteLong68k(&ROM[0x013A8],0x4E714E71);
   WriteLong68k(&ROM[0x013BE],0x4E714E71);

   // Fix Communication

   WriteWord68k(&ROM[0x013EA],0x4E71);

   // Fix Sub 68000 Checksum

   WriteLong68k(&ROM[0x60A0A],0x4E714E71);

   }

   if(romset==1){		// Extra

   // Main 68000 Speed Hack

   WriteLong68k(&ROM[0x00716],0x13FC0000);
   WriteLong68k(&ROM[0x0071A],0x00AA0000);
   WriteWord68k(&ROM[0x0071E],0x6100-20);

   WriteLong68k(&ROM[0x0093E],0x13FC0000);
   WriteLong68k(&ROM[0x00942],0x00AA0000);

   // Sub 68000 Speed Hack

   WriteLong68k(&ROM[0x606FA],0x13FC0000);
   WriteLong68k(&ROM[0x606FE],0x00AA0000);
   WriteWord68k(&ROM[0x60702],0x6100-16);

   WriteLong68k(&ROM[0x6F074],0x13FC0000);
   WriteLong68k(&ROM[0x6F078],0x00AA0000);

   // Fix Main 68000 Checksum

   WriteLong68k(&ROM[0x013D6],0x4E714E71);
   WriteLong68k(&ROM[0x013EC],0x4E714E71);

   // Fix Communication

   WriteWord68k(&ROM[0x01418],0x4E71);

   // Fix Sub 68000 Checksum

   WriteLong68k(&ROM[0x60A0A],0x4E714E71);

   }

   if(romset==2){		// Alternate

   // Main 68000 Speed Hack

   WriteLong68k(&ROM[0x0070C],0x13FC0000);
   WriteLong68k(&ROM[0x00710],0x00AA0000);
   WriteWord68k(&ROM[0x00714],0x6100-20);

   WriteLong68k(&ROM[0x00938],0x13FC0000);
   WriteLong68k(&ROM[0x0093C],0x00AA0000);

   // Sub 68000 Speed Hack

   WriteLong68k(&ROM[0x606FA],0x13FC0000);
   WriteLong68k(&ROM[0x606FE],0x00AA0000);
   WriteWord68k(&ROM[0x60702],0x6100-16);

   WriteLong68k(&ROM[0x6F074],0x13FC0000);
   WriteLong68k(&ROM[0x6F078],0x00AA0000);

   // Fix Main 68000 Checksum

   WriteLong68k(&ROM[0x013FA],0x4E714E71);
   WriteLong68k(&ROM[0x01410],0x4E714E71);

   // Fix Communication

   WriteWord68k(&ROM[0x0143C],0x4E71);

   // Fix Sub 68000 Checksum

   WriteLong68k(&ROM[0x60A0A],0x4E714E71);

   }

   if (romset == 3) {
   // Main 68000 Speed Hack

   WriteLong68k(&ROM[0x00700],0x13FC0000);
   WriteLong68k(&ROM[0x00704],0x00AA0000);
   WriteWord68k(&ROM[0x00708],0x6100-20);

   WriteLong68k(&ROM[0x0092c],0x13FC0000);
   WriteLong68k(&ROM[0x00930],0x00AA0000);

   // Sub 68000 Speed Hack

   WriteLong68k(&ROM[0x606FA],0x13FC0000);
   WriteLong68k(&ROM[0x606FE],0x00AA0000);
   WriteWord68k(&ROM[0x60702],0x6100-16);

   WriteLong68k(&ROM[0x6F076],0x13FC0000);
   WriteLong68k(&ROM[0x6F07a],0x00AA0000);

   // Fix Main 68000 Checksum

   WriteLong68k(&ROM[0x01398],0x4E714E71);
   //WriteLong68k(&ROM[0x013BE],0x4E714E71);

   // Fix Communication

   WriteWord68k(&ROM[0x013c4],0x4E71);

   // Fix Sub 68000 Checksum

   WriteLong68k(&ROM[0x60A0A],0x4E714E71);
   }

   memset(RAM+0x00000,0x00,0x44000);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x31000, 0x80, 0x10, 0x8000);


   // Main 68000 Memory Map
   // ---------------------

   ByteSwap(ROM,0xA0000);
   ByteSwap(RAM,0x44000);

   AddMemFetch(0x000000, 0x05FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadByte(0xD00000, 0xD0FFFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByte(0xE00000, 0xE10FFF, NULL, RAM+0x020000);			// COMMON RAM
   AddReadByte(0xC00000, 0xC000FF, darius_ioc_rb, NULL);		// I/O
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x05FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddReadWord(0xD00000, 0xD0FFFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWord(0xD80000, 0xD80FFF, NULL, RAM+0x031000);			// COLOUR RAM
   AddReadWord(0xE00000, 0xE10FFF, NULL, RAM+0x020000);			// COMMON RAM
   AddReadWord(0xC00000, 0xC000FF, darius_ioc_rw, NULL);		// I/O
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteByte(0xD00000, 0xD0FFFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0xE00000, 0xE10FFF, NULL, RAM+0x020000);		// COMMON RAM
   AddWriteByte(0xC00000, 0xC000FF, darius_ioc_wb, NULL);		// I/O
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x080000, 0x08FFFF, NULL, RAM+0x000000);		// MAIN RAM
   AddWriteWord(0xD00000, 0xD0FFFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0xD80000, 0xD80FFF, NULL, RAM+0x031000);		// COLOUR RAM
   AddWriteWord(0xE00000, 0xE10FFF, NULL, RAM+0x020000);		// COMMON RAM
   AddWriteWord(0xD20000, 0xD20003, NULL, RAM+0x042100);		// YSCROLL RAM
   AddWriteWord(0xD40000, 0xD40003, NULL, RAM+0x042200);		// XSCROLL RAM
   AddWriteWord(0xC00000, 0xC000FF, darius_ioc_ww, NULL);		// I/O
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   // Sub 68000 Memory Map
   // --------------------

   AddMemFetchMC68000B(0x000000, 0x03FFFF, ROM+0x060000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x060000);		// 68000 ROM
   AddReadByteMC68000B(0x040000, 0x04FFFF, NULL, RAM+0x032000);		// SUB LOCAL RAM
   AddReadByteMC68000B(0xE00000, 0xE10FFF, NULL, RAM+0x020000);		// COMMON RAM
   AddReadByteMC68000B(0x000000, 0xFFFFFF, DefBadReadByte, NULL);	// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x03FFFF, NULL, ROM+0x060000);		// 68000 ROM
   AddReadWordMC68000B(0x040000, 0x04FFFF, NULL, RAM+0x032000);		// SUB LOCAL RAM
   AddReadWordMC68000B(0xD80000, 0xD80FFF, NULL, RAM+0x031000);		// COLOUR RAM
   AddReadWordMC68000B(0xE00000, 0xE10FFF, NULL, RAM+0x020000);		// COMMON RAM
   AddReadWordMC68000B(0x000000, 0xFFFFFF, BadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x040000, 0x04FFFF, NULL, RAM+0x032000);	// SUB LOCAL RAM
   AddWriteByteMC68000B(0xE00000, 0xE10FFF, NULL, RAM+0x020000);	// COMMON RAM
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);	// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x040000, 0x04FFFF, NULL, RAM+0x032000);	// SUB LOCAL RAM
   AddWriteWordMC68000B(0xD80000, 0xD80FFF, NULL, RAM+0x031000);	// COLOUR RAM
   AddWriteWordMC68000B(0xE00000, 0xE10FFF, NULL, RAM+0x020000);	// COMMON RAM
   AddWriteWordMC68000B(0xC00000, 0xC000FF, NULL, RAM+0x042000);	// I/O RAM
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, BadWriteWord, NULL);	// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void execute_darius(void)
{
   tcpu=0;
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)

   tcpu=1;
   cpu_execute_cycles(CPU_68K_1, 90000*2);

   tcpu=0;
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
      print_debug("PC0:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 4);

   tcpu=1;
   cpu_execute_cycles(CPU_68K_1, 90000*2);
      print_debug("PC1:%06x SR1:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 4);

   if(tc0140syt_want_nmi()!=0) cpu_int_nmi(CPU_Z80_0);

   //cpu_execute_cycles(CPU_Z80_0, 4000000/60*2);			// Sound Main Z80
   cpu_execute_cycles(CPU_Z80_0, 5000000/60);			// Sound Main Z80
   /*#ifdef RAINE_DEBUG
      print_debug("Z80PC0:%04x\n",z80pc);
#endif*/
   cpu_interrupt(CPU_Z80_0, 0x38);

}

static void DrawDarius(void)
{
   int x,y,ta,zz,zzz,zzzz;
   int x16,y16;
   UINT8 *map;

   ClearPaletteMap();

   // BG0
   // ---

   MAKE_SCROLL_1024x512_2_8(
      0-(ReadWord(&RAM[0x42200])),
      0-(ReadWord(&RAM[0x42100]))
   );

   START_SCROLL_1024x512_2_8(32,32,864,224);

      ta = ReadWord(&RAM[0x14000+zz])&0x3FFF;

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x10000+zz]&0x3F,
         16,
         map
      );

      switch(RAM[0x10001+zz]&0xC0){
         case 0x00: Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
         case 0x40: Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
         case 0x80: Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
      }

   END_SCROLL_1024x512_2_8();

   // OBJECT
   // ------

   for(zz=0x20FF8;zz>=0x20100;zz-=8){
   x=(32+ReadWord(&RAM[zz+2]))&0x3FF;
   y=((240+32)-ReadWord(&RAM[zz]))&0x1FF;

   if((x>16)&&(y>16)&&(x<864+32)&&(y<224+32)){
   ta=ReadWord(&RAM[zz+4])&0x1FFF;
   if(GFX_SPR_SOLID[ta]){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[zz+6]&0x7F,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM[zz+5]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM[zz+5]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8],x,y,map); break;
         }
      }


   }

   }

   }

   // BG1
   // ---

   MAKE_SCROLL_1024x512_2_8(
      0-(ReadWord(&RAM[0x42202])),
      0-(ReadWord(&RAM[0x42102]))
   );

   START_SCROLL_1024x512_2_8(32,32,864,224);

   ta=ReadWord(&RAM[0x1C000+zz])&0x3FFF;
   if(GFX_BG0_SOLID[ta]){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x18000+zz]&0x3F,
         16,
         map
      );

      if(GFX_BG0_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM[0x18001+zz]&0xC0){
            case 0x00: Draw8x8_Trans_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
            case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM[0x18001+zz]&0xC0){
            case 0x00: Draw8x8_Mapped_Rot(&GFX_BG0[ta<<6],x,y,map);        break;
            case 0x40: Draw8x8_Mapped_FlipY_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0x80: Draw8x8_Mapped_FlipX_Rot(&GFX_BG0[ta<<6],x,y,map);  break;
            case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&GFX_BG0[ta<<6],x,y,map); break;
         }
      }

   }

   END_SCROLL_1024x512_2_8();

   // FG0
   // ---

   zz=0;
   for(y=32;y<224+32;y+=8){
   for(x=32;x<864+32;x+=8){

   ta=ReadWord(&RAM[0x2C000+zz])&0x7FF;
   if(GFX_FG0_SOLID[ta]){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM[0x28000+zz]&0x0F,
         4,			// 4 Colours
         map
      );

      if(GFX_FG0_SOLID[ta]==1)			// Some pixels; trans
         Draw8x8_Trans_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);
      else					// all pixels; solid
         Draw8x8_Mapped_Rot(&GFX_FG0[ta<<6],x,y,map);

   }

   zz+=2;
   }
   zz+=(256-216);
   }
}

/*-------[ADPCM PORT]-------*/

static void DariusWrite_ADPCM(UINT16 offset, UINT8 data)
{
   /*#ifdef RAINE_DEBUG
      print_debug("DariusADPCM(%02x)\n",data);
#endif*/
   data&=0x7F;

   if((data>0)&&(data<=0x1D)){
     MSM5205buffer_request( 0, data );
   }
}

static int DariusVolTable[] = {
  0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38,
  0x40, 0x50, 0x60, 0x80, 0xa0, 0xc0, 0xe0, 0xf0,
};
static int darius_volFM[2];
static int darius_volAY[2];
static int darius_panFM[2];
static int darius_panAY[2];

static void DariusYM2203SetFMPan( UINT16 offset, UINT8 data ){
  int cen;
  if( !(offset&0x0400) ){
    /**** make FM0 ****/
    darius_panFM[0] = (~data)&0xff;
    stream_set_pan( YM2203_get_stream_num(0), darius_panFM[0] );
    cen = darius_panFM[0] < 0x80 ? 0x80 - darius_panFM[0] : -(0x80 - darius_panFM[0]);
    data = darius_volFM[0] - ((darius_volFM[0] * cen)>>8);
    //stream_set_volume( YM2203_get_stream_num(0), data );
    //print_ingame(120,gettext("Pan[0]:%02x %s"), darius_panFM[0], stream_get_name(YM2203_get_stream_num(0)) );
  } else{
    darius_panFM[1] = (~data)&0xff;
    stream_set_pan( YM2203_get_stream_num(1), darius_panFM[1] );
    cen = darius_panFM[1] < 0x80 ? 0x80 - darius_panFM[1] : -(0x80 - darius_panFM[1]);
    data = darius_volFM[1] - ((darius_volFM[1] * cen)>>8);
    //stream_set_volume( YM2203_get_stream_num(1), data );
    //print_ingame(120,gettext("Pan[1]:%02x %s"), darius_panFM[1], stream_get_name(YM2203_get_stream_num(1)) );
  }
}
static void DariusYM2203SetAYPan( UINT16 offset, UINT8 data ){
  int cen;
  if( !(offset&0x0400) ){
    darius_panAY[0] = (~data)&0xff;
    darius_volAY[0] = 0xff;
    saSetPanMulti( AY8910_get_stream_num(0), darius_panAY[0] );
    cen = darius_panAY[0] < 0x80 ? 0x80 - darius_panAY[0] : -(0x80 - darius_panAY[0]);
    data = darius_volAY[0] - ((darius_volAY[0] * cen)>>8);
    //stream_set_volume( AY8910_get_stream_num(0), data );
  } else{
    darius_panAY[1] = (~data)&0xff;
    darius_volAY[1] = 0xff;
    saSetPanMulti( AY8910_get_stream_num(1), darius_panAY[1] );
    cen = darius_panAY[1] < 0x80 ? 0x80 - darius_panAY[1] : -(0x80 - darius_panAY[1]);
    data = darius_volAY[1] - ((darius_volAY[1] * cen)>>8);
    //stream_set_volume( AY8910_get_stream_num(1), data );
  }
}

static WRITE_HANDLER( DariusVol ){
  int cen;
  if( (data&0xf0) == 0xf0 ){
    //print_ingame(120,gettext("Vol:%02x %s %s"), data, stream_get_name(3*2), stream_get_name(3*2+1) );
    darius_volFM[0] = DariusVolTable[data&0x0f];
    darius_volFM[1] = darius_volFM[0];
    /**** make FM0 ****/
    cen = darius_panFM[0] < 0x80 ? 0x80 - darius_panFM[0] : -(0x80 - darius_panFM[0]);
    data = darius_volFM[0] - ((darius_volFM[0] * cen)>>8);
    //stream_set_volume( YM2203_get_stream_num(0), data );
    /**** make FM1 ****/
    cen = darius_panFM[1] < 0x80 ? 0x80 - darius_panFM[1] : -(0x80 - darius_panFM[1]);
    data = darius_volFM[1] - ((darius_volFM[1] * cen)>>8);
    //stream_set_volume( YM2203_get_stream_num(1), data );
  }
}

static void DariusMSM5205SetPan( UINT16 offset, UINT8 data ){
  MSM5205buffer_setpan( 0, data );
}

/**************** end of file ****************/

static struct VIDEO_INFO video_darius =
{
   DrawDarius,
   864,
   224,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE,
};
CLNEI( dariusj,darius, "Darius Japanese", TAITO, 1986, GAME_SHOOT,
	.input = input_darius,
	.dsw = dsw_darius,
	.video = &video_darius,
	.exec = execute_darius,
	.long_name_jpn = "ダライアス",
	.board = "A96",
	.sound = sound_darius,
);
static struct DIR_INFO dir_darius[] =
{
   { "darius_alt", },
   { "darius", },
   { "dariusb", },
   { NULL, },
};
GME( darius, "Darius", TAITO, 1986, GAME_SHOOT,
	.long_name_jpn = "ダライアス",
	.board = "A96",
);
static struct DIR_INFO dir_dariuse[] =
{
   { "darius_extra", },
   { "dariusex", },
   { "dariuse", },
   { ROMOF("darius"), },
   { CLONEOF("darius"), },
   { NULL, },
};
CLNE( dariuse,darius, "Darius (extra)", TAITO, 1986, GAME_SHOOT,
	.long_name_jpn = "ダライアス　エキストラバージョン",
	.board = "A96",
);
CLNEI( dariuso,darius, "Darius (Old, JPN Ver.)", TAITO, 1986, GAME_SHOOT,
	.long_name_jpn = "ダライアス",
	.board = "A96",
);

