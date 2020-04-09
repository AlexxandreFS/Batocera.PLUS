/******************************************************************************/
/*                                                                            */
/*                               PSIKYO DRIVER                                */
/*                                                                            */
/******************************************************************************/
// Driver by Luca Elia (l.elia@tin.it) for mame
// This version is only a port to raine with a few hacks...
// I forgot who did the original port, but I've been doing all the work
// on it for 1 year at least - Emmanuel Anne (emanne@absysteme.fr).
// this driver first appeared in raine just after 0.28g.
//
// Note about speed hacks : they are necessary for all the games, because I
// run the 68020 at 48 Mhz !!! So you don't want it to run that fast all the
// time, but rather just when the screen is full of bullets !

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "2610intf.h"
#include "ymf278b.h"
#include "memory.h"
#include "blit.h" // clear_game_screen
#include "timer.h"
#include "f3system.h"
#include "lspr16.h"
#include "video/priorities.h"
#include "zoom/16x16.h"		// 16x8 zoomed sprite routines
#include "sound/assoc.h"
#include "video/pdraw.h"

void load_gunbird(void);
void execute_gunbird(void);
void DrawGunbird();
void draw_tengai();
void load_btlkroad(void);
void load_samuraia(void);

#define execute_btlkroad execute_gunbird
#define execute_samuraia execute_gunbird
#define execute_s1945 execute_gunbird
#define execute_tengai execute_gunbird

static int  oldmem13;
static UINT8 *z80_8200; /* Fast bankswitch for z80 */


/* In realtà c'è una funzione Z80ASetbank */
WRITE_HANDLER(gunbird_sound_bankswitch_w)
{
  int bank = ((data>>4)&3);
	/* The banked rom is seen at 8200-ffff, so the last 0x200 bytes
	   of the rom not reachable. */

  z80_8200 = Z80ROM+0x10200+bank*0x8000;
}

UINT16 z80_read8200b(UINT16 offset) {
  offset -= 0x8200;
  return z80_8200[offset];
}

WRITE_HANDLER(sngkace_sound_bankswitch_w)
{
  int bank = (data&3);
  z80_8200 = Z80ROM+0x10000+bank*0x8000;
}

UINT16 z80_read8000b(UINT16 offset) {
  offset -= 0x8000;
  return z80_8200[offset];
}

static struct ROMSW_DATA romswd_btlkroad[] =
{
  { "Psikyo (Japan)", 0xf},
  { "Psikyo (Honk Kong)",0xa},
  { "Psikyo (Korea)", 0xc},
  { "Psikyo (Taiwan)",0x6},
  { "Jaleco+Psikyo (USA & Canada)",0xe},
  { "Psikyo",0x0},
  { NULL,                    0    },
};

static struct ROMSW_INFO romsw_btlkroad[] =
{
   { 0xc00007, 0x0e, romswd_btlkroad },
   { 0,        0,    NULL },
};

static struct ROMSW_DATA romswd_gunbird[] =
{
  { "World", 0xf},
  { "USA",0xe},
  { "Korea", 0xd},
  { "Hong Kong",0xb},
  { "Taiwan",0x7},
  { "Psikyo",0x0},
  { NULL,  0    },
};

static struct ROMSW_DATA romswd_sngkace[] =
{
  { "Korea (english text)", 0xd},
  { "Japan (default)",0xf},
  { NULL,                    0    },
};

static struct ROMSW_INFO romsw_gunbird[] =
{
   { 0xc00007, 0x0f, romswd_gunbird },
   { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_sngkace[] =
{
   { 0xc00007, 0x0f, romswd_sngkace },
   { 0,        0,    NULL },
};

static struct ROM_INFO rom_gunbirdj[] =
{
  { "1-u46.bin", 0x040000, 0x474abd69 , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "2-u39.bin", 0x040000, 0x3e3e661f , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
   {      "u14.bin",   0x200000, 0x7d7e8a00, 0, 0, 0, },
   {      "u24.bin",   0x200000, 0x5e3ffc9d, 0, 0, 0, },
   {      "u15.bin",   0x200000, 0xa827bfb5, 0, 0, 0, },
   {      "u25.bin",   0x100000, 0xef652e0c, 0, 0, 0, },
   {      "u33.bin",   0x200000, 0x54494e6b, 0, 0, 0, },
   {       "u3.bin",   0x040000, 0x0905aeb2, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_gunbird[] =
{
  { "4-u46.bin", 0x040000, 0xb78ec99d, REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "5-u39.bin", 0x040000, 0x925f095d, REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "3-u71.bin", 0x20000, 0x2168e4ba , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3-u71.bin", 0x20000, 0x2168e4ba , REGION_ROM2, 0x10000, LOAD_NORMAL },
   {      "u14.bin",   0x200000, 0x7d7e8a00, 0, 0, 0, },
   {      "u24.bin",   0x200000, 0x5e3ffc9d, 0, 0, 0, },
   {      "u15.bin",   0x200000, 0xa827bfb5, 0, 0, 0, },
   {      "u25.bin",   0x100000, 0xef652e0c, 0, 0, 0, },
   {      "u33.bin",   0x200000, 0x54494e6b, 0, 0, 0, },
  { "u64.bin", 0x080000, 0xe187ed4f , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "u56.bin", 0x100000, 0x9e07104d , REGION_SMP2, 0x000000, LOAD_NORMAL },
   {       "u3.bin",   0x040000, 0x0905aeb2, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_gunbirdk[] =
{
  { "1k-u46.bin", 0x080000, 0x745cee52 , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "2k-u39.bin", 0x080000, 0x669632fb , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "k3-u71.bin", 0x20000, 0x11994055 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "k3-u71.bin", 0x20000, 0x11994055 , REGION_ROM2, 0x10000, LOAD_NORMAL },
   {      "u14.bin",   0x200000, 0x7d7e8a00, 0, 0, 0, },
   {      "u24.bin",   0x200000, 0x5e3ffc9d, 0, 0, 0, },
   {      "u15.bin",   0x200000, 0xa827bfb5, 0, 0, 0, },
   {      "u25.bin",   0x100000, 0xef652e0c, 0, 0, 0, },
   {      "u33.bin",   0x200000, 0x54494e6b, 0, 0, 0, },
   {       "u3.bin",   0x040000, 0x0905aeb2, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_btlkroad[] =
{
  { "4-u46.bin", 0x040000, 0x8a7a28b4 , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "5-u39.bin", 0x040000, 0x933561fa , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "3-u71.bin", 0x20000, 0x22411fab , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3-u71.bin", 0x20000, 0x22411fab , REGION_ROM2, 0x10000, LOAD_NORMAL },
  { "u64.bin", 0x080000, 0x0f33049f , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "u56.bin", 0x100000, 0x51d73682 , REGION_SMP2, 0x000000, LOAD_NORMAL },
   {      "u14.bin",   0x200000, 0x282d89c3, 0, 0, 0, },
   {      "u24.bin",   0x200000, 0xbbe9d3d1, 0, 0, 0, },
   {      "u15.bin",   0x200000, 0xd4d1b07c, 0, 0, 0, },
   //   {      "u25.bin",       0x100000,   0xef652e0c  }, Not present
   {      "u33.bin",   0x200000, 0x4c8577f1, 0, 0, 0, },
   {       "u3.bin",   0x040000, 0x30d541ed, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static struct INPUT_INFO input_gunbird[] =
{
   INP0( COIN1, 0x30003, 0x01 ),
   INP1( COIN2, 0x30003, 0x04 ),
   INP0( SERVICE, 0x30003, 0x10 ),
   INP0( TEST, 0x30003, 0x20 ),
   INP0( TILT, 0x30003, 0x40 ),
   // 0x80 from sound CPU

   INP0( P1_START, 0x30000, 0x01 ),
   INP0( P1_UP, 0x30000, 0x80 ),
   INP0( P1_DOWN, 0x30000, 0x40 ),
   INP0( P1_LEFT, 0x30000, 0x10 ),
   INP0( P1_RIGHT, 0x30000, 0x20 ),
   INP0( P1_B1, 0x30000, 0x08 ),
   INP0( P1_B2, 0x30000, 0x04 ),
   INP0( P1_B3, 0x30000, 0x02 ),

   INP0( P2_START, 0x30001, 0x01 ),
   INP0( P2_UP, 0x30001, 0x80 ),
   INP0( P2_DOWN, 0x30001, 0x40 ),
   INP0( P2_LEFT, 0x30001, 0x10 ),
   INP0( P2_RIGHT, 0x30001, 0x20 ),
   INP0( P2_B1, 0x30001, 0x08 ),
   INP0( P2_B2, 0x30001, 0x04 ),
   INP0( P2_B3, 0x30001, 0x02 ),

   END_INPUT
};

#define input_s1945 input_gunbird
#define input_tengai input_gunbird

static struct INPUT_INFO input_btlkroad[] =
{
   INP0( COIN1, 0x30003, 0x01 ),
   INP0( COIN2, 0x30003, 0x02 ),
   INP0( SERVICE, 0x30003, 0x10 ),
   INP0( TEST, 0x30003, 0x20 ),
   INP0( TILT, 0x30003, 0x40 ),
   // 0x80 from sound CPU

   INP0( P1_START, 0x30000, 0x01 ),
   INP0( P1_UP, 0x30000, 0x80 ),
   INP0( P1_DOWN, 0x30000, 0x40 ),
   INP0( P1_LEFT, 0x30000, 0x10 ),
   INP0( P1_RIGHT, 0x30000, 0x20 ),
   INP0( P1_B1, 0x30000, 0x08 ),
   INP0( P1_B2, 0x30000, 0x04 ),
   INP0( P1_B3, 0x30000, 0x02 ),
   INP0( P1_B4, 0x30002, 0x80 ),
   INP0( P1_B5, 0x30002, 0x40 ),
   INP0( P1_B6, 0x30002, 0x20 ),

   INP0( P2_START, 0x30001, 0x01 ),
   INP0( P2_UP, 0x30001, 0x80 ),
   INP0( P2_DOWN, 0x30001, 0x40 ),
   INP0( P2_LEFT, 0x30001, 0x10 ),
   INP0( P2_RIGHT, 0x30001, 0x20 ),
   INP0( P2_B1, 0x30001, 0x08 ),
   INP0( P2_B2, 0x30001, 0x04 ),
   INP0( P2_B3, 0x30001, 0x02 ),
   INP0( P2_B4, 0x30002, 0x08 ),
   INP0( P2_B5, 0x30002, 0x04 ),
   INP0( P2_B6, 0x30002, 0x02 ),

   END_INPUT
};


static struct DSW_DATA dsw_data_gunbird_0[] =
{
   { _("Flip screen") ,	      0x01, 0x02 },
   { MSG_OFF,		      0x01},
   { MSG_ON,		      0x00},
   { MSG_DEMO_SOUND,          0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_DIFFICULTY,          0x0C, 0x04 },  // Is it really the difficulty level ?
   { MSG_EASY,                0x08},
   { MSG_NORMAL,              0x0C},
   { MSG_HARD,                0x04},
   { MSG_HARDEST,             0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "1",                     0x20},
   { "2",                     0x10},
   { "3",                     0x30},
   { "4",                     0x00},
   { _("Bonus life"),            0x40, 0x02 },
   { _("400k"),                  0x40},
   { _("600k"),                  0x00},
   { MSG_SERVICE,             0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};


static struct DSW_DATA dsw_data_gunbird_1[] =
{
   { _("Credits/Coinage"),       0x01, 0x02 },
   { _("A+B/A,B"),               0x01, 0x00 },
   { _("A,B/A"), 0x00 },
   { _("Coinage A"),             0x0E, 0x08 },
   { MSG_3COIN_1PLAY,         0x0A},
   { MSG_2COIN_1PLAY,         0x0C},
   { MSG_1COIN_1PLAY,         0x0E},
   { MSG_1COIN_2PLAY,         0x08},
   { MSG_1COIN_3PLAY,         0x06},
   { MSG_1COIN_4PLAY,         0x04},
   { MSG_1COIN_5PLAY,         0x02},
   { MSG_1COIN_6PLAY,         0x00},
   { _("Coinage B"),             0x70, 0x08 },
   { MSG_3COIN_1PLAY,         0x50},
   { MSG_2COIN_1PLAY,         0x60},
   { MSG_1COIN_1PLAY,         0x70},
   { MSG_1COIN_2PLAY,         0x40},
   { MSG_1COIN_3PLAY,         0x30},
   { MSG_1COIN_4PLAY,         0x20},
   { MSG_1COIN_5PLAY,         0x10},
   { MSG_1COIN_6PLAY,         0x00},
   { _("2 Coins/1 Credit"),      0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};


static struct DSW_INFO dsw_gunbird[] =
{
   { 0x30004, 0xFF, dsw_data_gunbird_1 },
   { 0x30005, 0xFD, dsw_data_gunbird_0 },
   { 0,        0,    NULL,      },
};

#define dsw_btlkroad dsw_gunbird
#define dsw_samuraia dsw_gunbird
#define dsw_s1945 dsw_gunbird
#define dsw_tengai dsw_gunbird

static struct VIDEO_INFO video_gunbird =
{
   DrawGunbird,
   320,
   224,
   32,
   VIDEO_ROTATE_270 | VIDEO_ROTATABLE
};

#define video_samuraia video_gunbird
#define video_s1945 video_gunbird

static struct VIDEO_INFO video_btlkroad =
{
   DrawGunbird,
   320,
   224,
   32,
   //   VIDEO_ROTATE_270 | VIDEO_ROTATABLE
   VIDEO_ROTATE_NORMAL | VIDEO_ROTATABLE
};

#define video_tengai video_btlkroad

#define clear_gunbird NULL
#define clear_btlkroad clear_gunbird
#define clear_samuraia clear_gunbird
#define clear_s1945 clear_gunbird
#define clear_tengai clear_gunbird

static struct YM2610interface ym2610_interface =
{
  1,
  8000000,
  { (180 | (OSD_PAN_CENTER<<8) ) },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { z80_irq_handler },	/* irq */
  { REGION_SMP1 },	/* delta_t */
  { REGION_SMP2 },	/* adpcm */
  { YM3012_VOL(255,OSD_PAN_LEFT,255,OSD_PAN_RIGHT) },
};

static struct YM2610interface sngkace_ym2610_interface =
{
  1,
  8000000,
  { (180 | (OSD_PAN_CENTER<<8) ) },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { z80_irq_handler },	/* irq */
  { REGION_SMP1 },	/* delta_t */
  { REGION_SMP1 },	/* adpcm */
  { YM3012_VOL(255,OSD_PAN_LEFT,255,OSD_PAN_RIGHT) },
};

static struct YMF278B_interface ymf278b_interface =
{
	1,
	{ YMF278B_STD_CLOCK },       /* 33.8688 MHz */
	{ REGION_SMP1 },
	{ YM3012_VOL(255, MIXER_PAN_CENTER, 255, MIXER_PAN_CENTER) },
	{ z80_irq_handler }
};

struct SOUND_INFO sound_gunbird[] =
{
   { SOUND_YM2610,  &ym2610_interface,  },
   { 0,             NULL,               },
};

#define sound_btlkroad sound_gunbird
#define sound_samuraia sound_sngkace

struct SOUND_INFO sound_sngkace[] =
{
   { SOUND_YM2610,  &sngkace_ym2610_interface,  },
   { 0,             NULL,               },
};

struct SOUND_INFO sound_s1945[] =
{
   { SOUND_YMF278B,  &ymf278b_interface,  },
   { 0,             NULL,               },
};

#define sound_tengai sound_s1945

GMEI( gunbird,
   "Gunbird",
   PSIKYO,
   1994,
   GAME_SHOOT,
   .romsw = romsw_gunbird);

CLNEI( gunbirdj,
       gunbird,
   "Gunbird (Japan)",
   PSIKYO,
   1994,
   GAME_SHOOT);

CLNEI( gunbirdk,
       gunbird,
   "Gunbird (Korean version)",
   PSIKYO,
   1994,
   GAME_SHOOT,
   .romsw = romsw_gunbird);

GMEI( btlkroad,
   "Battle K-Road (Japan)",
   PSIKYO,
   1994,
   GAME_BEAT,
   .romsw = romsw_btlkroad);

static struct ROM_INFO rom_sngkace[] =
{
  { "1-u127.bin", 0x040000, 0x6c45b2f8 , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "2-u126.bin", 0x040000, 0x845a6760 , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
   {      "u14.bin",   0x200000, 0x00a546cb, 0, 0, 0, },
   {      "u34.bin",   0x100000, 0xe6a75bd8, 0, 0, 0, },
   {      "u35.bin",   0x100000, 0xc4ca0164, 0, 0, 0, },
   {      "u11.bin",   0x040000, 0x11a04d91, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_samuraia[] =
{
  { "4-u127.bin", 0x040000, 0x8c9911ca , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "5-u126.bin", 0x040000, 0xd20c3ef0 , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "3-u58.bin", 0x20000, 0x310f5c76 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3-u58.bin", 0x20000, 0x310f5c76 , REGION_ROM2, 0x10000, LOAD_NORMAL },
   {      "u14.bin",   0x200000, 0x00a546cb, 0, 0, 0, },
   {      "u34.bin",   0x100000, 0xe6a75bd8, 0, 0, 0, },
   {      "u35.bin",   0x100000, 0xc4ca0164, 0, 0, 0, },
  { "u68.bin", 0x100000, 0x9a7f6c34 , REGION_SMP1, 0x000000, LOAD_NORMAL },
   {      "u11.bin",   0x040000, 0x11a04d91, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_s1945j[] =
{
  { "1-u40.bin", 0x040000, 0xc00eb012 , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "2-u41.bin", 0x040000, 0x3f5a134b , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "3-u63.bin", 0x20000, 0x42d40ae1 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3-u63.bin", 0x20000, 0x42d40ae1 , REGION_ROM2, 0x10000, LOAD_NORMAL },
  // { "4-u59.bin", 0x00100, 0x00000000 , REGION_CPU3, 0x00000, LOAD_NORMAL },
  { "u20.bin", 0x200000, 0x28a27fee , REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "u22.bin", 0x200000, 0xca152a32 , REGION_GFX1, 0x200000, LOAD_NORMAL },
  { "u21.bin", 0x200000, 0xc5d60ea9 , REGION_GFX1, 0x400000, LOAD_NORMAL },
  { "u23.bin", 0x200000, 0x48710332 , REGION_GFX1, 0x600000, LOAD_NORMAL },
  { "u34.bin", 0x200000, 0xaaf83e23 , REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "u61.bin", 0x200000, 0xa839cf47 , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "u1.bin", 0x040000, 0xdee22654 , REGION_USER1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_s1945[] =
{
  { "2s.u40", 0x040000, 0x9b10062a , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "3s.u41", 0x040000, 0xf87e871a , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "3-u63.bin", 0x20000, 0x42d40ae1 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "3-u63.bin", 0x20000, 0x42d40ae1 , REGION_ROM2, 0x10000, LOAD_NORMAL },
  // { "4-u59.bin", 0x00100, 0x00000000 , REGION_CPU3, 0x00000, LOAD_NORMAL },
  { "u20.bin", 0x200000, 0x28a27fee , REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "u22.bin", 0x200000, 0xca152a32 , REGION_GFX1, 0x200000, LOAD_NORMAL },
  { "u21.bin", 0x200000, 0xc5d60ea9 , REGION_GFX1, 0x400000, LOAD_NORMAL },
  { "u23.bin", 0x200000, 0x48710332 , REGION_GFX1, 0x600000, LOAD_NORMAL },
  { "u34.bin", 0x200000, 0xaaf83e23 , REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "u61.bin", 0x200000, 0xa839cf47 , REGION_SMP1, 0x000000, LOAD_NORMAL },
  { "u1.bin", 0x040000, 0xdee22654 , REGION_USER1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_tengai[] =
{
  { "2-u40.bin", 0x080000, 0xab6fe58a , REGION_ROM1, 0x000000, LOAD32_SWAP_16 },
  { "3-u41.bin", 0x080000, 0x02e42e39 , REGION_ROM1, 0x000002, LOAD32_SWAP_16 },
  { "1-u63.bin", 0x20000, 0x2025e387 , REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "1-u63.bin", 0x20000, 0x2025e387 , REGION_ROM2, 0x10000, LOAD_NORMAL },
  //{ "4-u59.bin", 0x00100, 0x00000000 , REGION_CPU3, 0x00000, LOAD_NORMAL },
  // GFX1
  { "u20.bin", 0x200000, 0xed42ef73 , REGION_GFX1, 0x000000, LOAD_SWAP_16 },
  { "u22.bin", 0x200000, 0x8d21caee , REGION_GFX1, 0x200000, LOAD_SWAP_16 },
  { "u21.bin", 0x200000, 0xefe34eed , REGION_GFX1, 0x400000, LOAD_SWAP_16 },
  { "u34.bin", 0x400000, 0x2a2e2eeb , REGION_GFX2, 0x000000, LOAD_SWAP_16 },
/* Ignored : ROM_COPY */
  { "u61.bin", 0x200000, 0xa63633c5, REGION_SMP1, 0, LOAD_NORMAL },	// 8 bit signed pcm (16KHz,
  { "u62.bin", 0x200000, 0x3ad0c357 , REGION_SMP1, 0x200000, LOAD_NORMAL },
  { "u1.bin", 0x040000, 0x681d7d55 , REGION_USER1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_samuraia[] =
{
   INP0( COIN1, 0x30009, 0x01 ),
   INP0( COIN2, 0x30009, 0x02 ),
   INP0( SERVICE, 0x30009, 0x10 ),
   INP0( TEST, 0x30009, 0x20 ),
   INP0( TILT, 0x30009, 0x40 ),
   // 0x80 from sound CPU

   INP0( P1_START, 0x30000, 0x01 ),
   INP0( P1_UP, 0x30000, 0x80 ),
   INP0( P1_DOWN, 0x30000, 0x40 ),
   INP0( P1_LEFT, 0x30000, 0x10 ),
   INP0( P1_RIGHT, 0x30000, 0x20 ),
   INP0( P1_B1, 0x30000, 0x08 ),
   INP0( P1_B2, 0x30000, 0x04 ),
   INP0( P1_B3, 0x30000, 0x02 ),

   INP0( P2_START, 0x30001, 0x01 ),
   INP0( P2_UP, 0x30001, 0x80 ),
   INP0( P2_DOWN, 0x30001, 0x40 ),
   INP0( P2_LEFT, 0x30001, 0x10 ),
   INP0( P2_RIGHT, 0x30001, 0x20 ),
   INP0( P2_B1, 0x30001, 0x08 ),
   INP0( P2_B2, 0x30001, 0x04 ),
   INP0( P2_B3, 0x30001, 0x02 ),

   END_INPUT
};

GMEI( samuraia,
   "Samurai Aces",
   PSIKYO,
   1993,
   GAME_SHOOT,
   .romsw = romsw_sngkace);

CLNEI( sngkace,
   samuraia,
   "Sengoku Ace",
   PSIKYO,
   1993,
   GAME_SHOOT,
   .romsw = romsw_sngkace);

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG1;
static UINT8 *GFX_BG1_SOLID;

static UINT8 *RAM_SPR_LST;
static UINT8 *RAM_SPR;
static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *LUT;
static UINT8 *TMP;

static UINT32 num_sprites;

static UINT8* actual_decode(UINT8 *TMP,int tb,int size,UINT8 *GFX) {
  int ta;
  for(ta=0;ta<size;ta+=8){
    GFX[tb++]=TMP[ta+1]>>4;
    GFX[tb++]=TMP[ta+1]&15;
    GFX[tb++]=TMP[ta+0]>>4;
    GFX[tb++]=TMP[ta+0]&15;
    GFX[tb++]=TMP[ta+3]>>4;
    GFX[tb++]=TMP[ta+3]&15;
    GFX[tb++]=TMP[ta+2]>>4;
    GFX[tb++]=TMP[ta+2]&15;
    GFX[tb++]=TMP[ta+5]>>4;
    GFX[tb++]=TMP[ta+5]&15;
    GFX[tb++]=TMP[ta+4]>>4;
    GFX[tb++]=TMP[ta+4]&15;
    GFX[tb++]=TMP[ta+7]>>4;
    GFX[tb++]=TMP[ta+7]&15;
    GFX[tb++]=TMP[ta+6]>>4;
    GFX[tb++]=TMP[ta+6]&15;
  }
  return &GFX[tb];
}

static void GunbirdDecode(char *S,int tb,int size)
{
   if(!load_rom(S, TMP, size)) return;
   actual_decode(TMP,tb,size,GFX);
}

static UINT8* my_decode_region(int region,UINT8 *GFX) {
  return actual_decode(load_region[region],0,get_region_size(region),GFX);
}

void finish_z80() {
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,		NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                NULL);

   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,		NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,               NULL);

   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,               NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                        NULL);

   AddZ80AWritePort(0x00, 0xFF, DefBadWriteZ80,              NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                        NULL);
   AddZ80AInit();
}

#define FRAME_Z80 CPU_FRAME_MHz(4,60)

static void setup_z80_mem_gunbird() {
  setup_z80_frame(CPU_Z80_0,FRAME_Z80);
  AddZ80AReadByte(0x0000,0x7fff,NULL,Z80ROM);
  AddZ80AReadByte(0x8000,0x81ff,NULL,Z80RAM+0x8000);
  AddZ80AReadByte(0x8200,0xffff,z80_read8200b,NULL);

  AddZ80AWriteByte(0x0000,0x7fff,DefBadWriteZ80,     NULL);
  AddZ80AWriteByte(0x8000,0x81ff,NULL,Z80RAM+0x8000);
  AddZ80AWriteByte(0x8200,0xffff,DefBadWriteZ80,     NULL);
}

static void psikyo_ack_latch_w(UINT32 offset, UINT8 data)
{
  RAM[0x30009] &= 0x7f;
}

static void setup_z80_gunbird() {
    init_assoc( 2);
  setup_z80_mem_gunbird();

  // Ports

  AddZ80AReadPort(0x4, 0x4,YM2610_status_port_0_A_r ,    NULL);
  AddZ80AReadPort(0x6, 0x6,YM2610_status_port_0_B_r ,    NULL);
  AddZ80AReadPort(0x8, 0x8,soundlatch_lo_r, NULL);

  AddZ80AWritePort(0x0, 0x0, gunbird_sound_bankswitch_w,    NULL);
  AddZ80AWritePort(0x4, 0x4, YM2610_control_port_0_A_w,    NULL);
  AddZ80AWritePort(0x5, 0x5, YM2610_data_port_0_A_w,    NULL);
  AddZ80AWritePort(0x6, 0x6, YM2610_control_port_0_B_w,    NULL);
  AddZ80AWritePort(0x7, 0x7, YM2610_data_port_0_B_w,    NULL);
  AddZ80AWritePort(0xc, 0xc, psikyo_ack_latch_w,    NULL);

  finish_z80();
  z80_8200 = Z80ROM+0x10200;
}

void setup_z80_s1945() {
    init_assoc( 2);
  setup_z80_mem_gunbird();

   // Ports

   AddZ80AReadPort(0x8, 0x8,YMF278B_status_port_0_r ,    NULL);
   AddZ80AReadPort(0x10, 0x10,soundlatch_lo_r, NULL);

   AddZ80AWritePort(0x0, 0x0, gunbird_sound_bankswitch_w,    NULL);
   // ports 2,3 ignored
   AddZ80AWritePort(0x8, 0x8, YMF278B_control_port_0_A_w,    NULL);
   AddZ80AWritePort(0x9, 0x9, YMF278B_data_port_0_A_w,    NULL);

   AddZ80AWritePort(0xa, 0xa, YMF278B_control_port_0_B_w,    NULL);
   AddZ80AWritePort(0xb, 0xb, YMF278B_data_port_0_B_w,    NULL);

   AddZ80AWritePort(0xc, 0xc, YMF278B_control_port_0_C_w,    NULL);
   AddZ80AWritePort(0xd, 0xd, YMF278B_data_port_0_C_w,    NULL);

   AddZ80AWritePort(0x18, 0x18, psikyo_ack_latch_w,    NULL);

   finish_z80();
   z80_8200 = Z80ROM+0x10200;
}

void setup_z80_sngkace() {
   init_assoc( 2);
   AddZ80AReadByte(0x0000,0x77ff,NULL,Z80ROM);
   AddZ80AReadByte(0x7800,0x7fff,NULL,Z80RAM+0x7800);
   AddZ80AReadByte(0x8000,0xffff,z80_read8000b,NULL);

   AddZ80AWriteByte(0x0000,0x77ff,DefBadWriteZ80,     NULL);
   AddZ80AWriteByte(0x7800,0x7fff,NULL,Z80RAM+0x7800);
   AddZ80AWriteByte(0x8000,0xffff,DefBadWriteZ80,     NULL);

   // ports

   AddZ80AReadPort(0x0, 0x0,YM2610_status_port_0_A_r ,    NULL);
   AddZ80AReadPort(0x2, 0x2,YM2610_status_port_0_B_r ,    NULL);
   AddZ80AReadPort(0x8, 0x8,soundlatch_lo_r, NULL);

   AddZ80AWritePort(0x0, 0x0, YM2610_control_port_0_A_w,    NULL);
   AddZ80AWritePort(0x1, 0x1, YM2610_data_port_0_A_w,    NULL);
   AddZ80AWritePort(0x2, 0x2, YM2610_control_port_0_B_w,    NULL);
   AddZ80AWritePort(0x3, 0x3, YM2610_data_port_0_B_w,    NULL);
   AddZ80AWritePort(0x4, 0x4, sngkace_sound_bankswitch_w,    NULL);
   AddZ80AWritePort(0xc, 0xc, psikyo_ack_latch_w,    NULL);

   finish_z80();
   z80_8200 = Z80ROM+0x10000;
}

static UINT8 *mcu_table;

static UINT8 s1945_table[256] = {
	0x00, 0x00, 0x64, 0xae, 0x00, 0x00, 0x26, 0x2c, 0x00, 0x00, 0x2c, 0xda, 0x00, 0x00, 0x2c, 0xbc,
	0x00, 0x00, 0x2c, 0x9e, 0x00, 0x00, 0x2f, 0x0e, 0x00, 0x00, 0x31, 0x10, 0x00, 0x00, 0xc5, 0x1e,
	0x00, 0x00, 0x32, 0x90, 0x00, 0x00, 0xac, 0x5c, 0x00, 0x00, 0x2b, 0xc0
};

static UINT8 s1945j_table[256] = {
	0x00, 0x00, 0x64, 0xb6, 0x00, 0x00, 0x26, 0x2c, 0x00, 0x00, 0x2c, 0xda, 0x00, 0x00, 0x2c, 0xbc,
	0x00, 0x00, 0x2c, 0x9e, 0x00, 0x00, 0x2f, 0x0e, 0x00, 0x00, 0x31, 0x10, 0x00, 0x00, 0xc5, 0x92,
	0x00, 0x00, 0x32, 0x90, 0x00, 0x00, 0xac, 0x64, 0x00, 0x00, 0x2b, 0xc0
};

static UINT8 *sound_mem,*buf1_spr,*buf2_spr;

static void gunbird_sound(int command) {
    command &= 0xff; // 68020 uses move.l a0,adr here, 3 bytes wasted !
    if (!handle_sound_cmd(command)) {
	latch = oldmem13 = command;
	RAM[0x30009] |= 0x80;
	cpu_int_nmi(CPU_Z80_0);
	/* Tsss... all this mess with the sound was because I finally noticed
	 * that you don't hear the character shouting when dying in gunbird...
	 * So to get this famous missing sound I had to patch the rom to return
	 * immediately after sending the sound command, and then the z80 needs
	 * to execute a few cycles here to be sure to have this command ! */
	cpu_execute_cycles(CPU_Z80_0,700);
    }
}

static void s1945_mcu_r(UINT8 data)
{
  if (data == 3) { // mcu read
    // used only in s1945
    UINT32 ta;
    ta=m68k_dreg(regs,0);
    m68k_dreg(regs,0)=mcu_table[ta & 0xff];
  } else if (data == 2) { // speed hack
    Stop68020();
  } else if (data == 4)  // gunbird sound command ! (using a0)
      gunbird_sound(m68k_areg(regs,0));
  else if (data == 5) // s1945/tengai sound (using d0)
      gunbird_sound(m68k_dreg(regs,0));

#if 0
  // All this is debuging stuff. It's useless now, but I leave it here
  // commented because it might be usefull another time.
  // You find here how to read the return address on the stack, and so on...
  else if (data == 4) {
    if (m68k_areg(regs,0) == 0)
      exit(1);
    else {
      m68k_areg(regs,7) -= 4; // sp = sp -4
      WriteLong68k(&RAM[0x50000]+(m68k_areg(regs,7) & 0xffff),0x10e5c); // rts
      regs.pc = m68k_areg(regs,0); // pc = a0
      my_frame = 10;
      my_int = 0;
    }
  } else {
/*     my_int = 1; */
/*     my_frame = 2500; */
  }
#endif
}

static int layer_id_data[3];

static char *layer_id_name[3] =
{
   "BG0", "BG1", "OBJECT",
};

static void finish_psikyo_conf() {
  int code_size = get_region_size(REGION_ROM1) >> 16, ta;

  init_pbitmap();

  // default latch address (gunbird, sngkace, btlkroad)
  sound_mem = &RAM[0x30013];

  RAM_SPR = RAM + 0x00000;
  RAM_BG0 = RAM + 0x20000;
  RAM_BG1 = RAM + 0x22000;

  InitPaletteMap(RAM+0x10000, 0x100, 0x10, 0x8000);  // not all used
  if (!strcmp(current_game->main_name,"tengai"))
    set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb_68k);
  else {
    set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb_rev_68k);
  }

  init_16x16_zoom();
  layer_id_data[0] = add_layer_info(layer_id_name[0]);
  layer_id_data[1] = add_layer_info(layer_id_name[1]);
  layer_id_data[2] = add_layer_info(layer_id_name[2]);

   F3SystemEEPROMAccess=&s1945_mcu_r;

   // A convinient point in the psikyo driver : all the games have exactly
   // the same memory map !

   for(ta=0;ta<0x100;ta++)
      R24[ta]=RAM+0x60000;	// SCRATCH RAM

   R24[0x40] = RAM+0x00000;     // Sprites data & Sprites list ($400000-$401FFF)
   R24[0x60] = RAM+0x10000;     // Palette ($600000-$601FFF)
   R24[0x80] = RAM+0x20000;     // Layer 0 and Layer 1 ($800000-$803FFF)
                                // RAM and Vregs ($804000-$807FFF)
   R24[0xC0] = RAM+0x30000;     // Input ports ($C00000-$C0000B) and Sound related
   R24[0xFE] = RAM+0x40000;     // RAM
   R24[0xFF] = RAM+0x50000;

   for(ta=0;ta<0x100;ta++)
      W24[ta]=R24[ta];		// copy READ -> WRITE

   for(ta=0;ta<code_size;ta++)
      R24[ta]=ROM+ta*0x10000;	// 68020 ROM

   init_m68k();

   buf1_spr = AllocateMem(0x2000);
   buf2_spr = AllocateMem(0x2000);
   memset(buf1_spr,0,0x2000);
   memset(buf2_spr,0,0x2000);
   RAM_SPR_LST = buf2_spr + 0x01800;
}

void load_gunbird(void)
{
   int ta;

   RAMSize = 0x70000;

   if(!(RAM=AllocateMem(RAMSize)))     return;
   if(!(GFX=AllocateMem(0x1200000)))   return;
   if(!(LUT=AllocateMem(0x40000)))     return;  // sprites lookup table
   if(!(TMP=AllocateMem(0x200000)))    return;
   Z80RAM = Z80ROM;

   GunbirdDecode("u14.bin", 0x0000000, 0x200000);  // sprites (0xE000 tiles)
   GunbirdDecode("u24.bin", 0x0400000, 0x200000);
   GunbirdDecode("u15.bin", 0x0800000, 0x200000);
   GunbirdDecode("u25.bin", 0x0C00000, 0x100000);
   GunbirdDecode("u33.bin", 0x0E00000, 0x200000);  // layer 0 & 1 (0x4000 tiles)

   if(!load_rom("u3.bin", LUT, 0x40000)) return;   // sprites LUT

   for(ta=0;ta<0x1200000;ta++)
      GFX[ta]^=15;

   GFX_SPR = GFX;
   GFX_BG0 = GFX + 0x0E00000;
   GFX_BG1 = GFX + 0x1000000;

   num_sprites = 0xE000-1;
   GFX_SPR_SOLID = make_solid_mask_16x16( GFX_SPR, num_sprites+1  );
   GFX_BG0_SOLID = make_solid_mask_16x16( GFX_BG0, 0x2000  );
   GFX_BG1_SOLID = make_solid_mask_16x16( GFX_BG1, 0x2000  );

   finish_psikyo_conf();

   memset(RAM+0x00000,0x00,RAMSize);
   memset(RAM+0x30000,0xFF,0x10);

   RAM[0x30003] = 0x7f;  // bit 8 is sound related and must be 0 if no sound is used, otherwise
                         // the game hangs after the startup screen
   RAM[0x30007] = 0x0;  // bit 8 is vblank: if 0 the games hangs at startup


   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);


   setup_z80_gunbird();

   /* ----------- */

  // Main CPU: 68EC020
   // Speed hack
   if (!strcmp(current_game->main_name,"gunbirdk")) { // original (japan)
     WriteWord68k(&ROM[0x15e7e],0x7F02);		//	raine	#$02 <stop cpu>
     WriteWord68k(&ROM[0x15e70],0x4e71);		//	nop
     WriteWord68k(&ROM[0xc8e],0x6006); // Enable region code
     WriteWord68k(&ROM[0x14f26],0x7f04); // sound command
     WriteWord68k(&ROM[0x14f28],0x4e71);		//	nop
     WriteWord68k(&ROM[0x14f2a],0x4e71); 		//	nop
   } else if (!strcmp(current_game->main_name,"gunbirdj")){
     WriteWord68k(&ROM[0x15eb4],0x7F02);		//	raine	#$02 <stop cpu>
     WriteWord68k(&ROM[0x15ea6],0x4e71);		//	nop
     WriteWord68k(&ROM[0x14f5c],0x7f04); // sound command
     WriteWord68k(&ROM[0x14f5e],0x4e71);		//	nop
     WriteWord68k(&ROM[0x14f60],0x4e71); 		//	nop
   } else { // gunbird world
     WriteWord68k(&ROM[0x15e76],0x7F02);		//	raine	#$02 <stop cpu>
     WriteWord68k(&ROM[0x15e68],0x4e71);		//	nop
     WriteWord68k(&ROM[0x14f1e],0x7f04); // sound command
     WriteWord68k(&ROM[0x14f20],0x4e71);		//	nop
     WriteWord68k(&ROM[0x14f22],0x4e71);		//	nop
   }

   FreeMem(TMP);
}

void load_btlkroad(void)
{
   int ta;

   RAMSize = 0x70000;

   if(!(RAM=AllocateMem(RAMSize)))     return;
   if(!(GFX=AllocateMem(0x1200000)))   return;
   if(!(LUT=AllocateMem(0x40000)))     return;  // sprites lookup table
   if(!(TMP=AllocateMem(0x200000)))    return;
   Z80RAM = Z80ROM;

   GunbirdDecode("u14.bin", 0x0000000, 0x200000);  // sprites (0xE000 tiles)
   GunbirdDecode("u24.bin", 0x0400000, 0x200000);
   GunbirdDecode("u15.bin", 0x0800000, 0x200000);
   //   GunbirdDecode("u25.bin", 0x0c00000, 0x100000);  // Not present (try gunbird)
   GunbirdDecode("u33.bin", 0x0e00000, 0x200000);  // layer 0 & 1 (0x4000 tiles)

   if(!load_rom("u3.bin", LUT, 0x40000)) return;   // sprites LUT

   for(ta=0;ta<0x1200000;ta++)
      GFX[ta]^=15;

   GFX_SPR = GFX;
   GFX_BG0 = GFX + 0x0E00000;
   GFX_BG1 = GFX + 0x1000000;

   num_sprites = 0xE000-1;
   GFX_SPR_SOLID = make_solid_mask_16x16( GFX_SPR, num_sprites+1  );
   GFX_BG0_SOLID = make_solid_mask_16x16( GFX_BG0, 0x2000  );
   GFX_BG1_SOLID = make_solid_mask_16x16( GFX_BG1, 0x2000  );

   finish_psikyo_conf();

   memset(RAM+0x00000,0x00,RAMSize);
   memset(RAM+0x30000,0xFF,0x10);

   RAM[0x30003] = 0x7f;  // bit 8 is sound related and must be 0 if no sound is used, otherwise
                         // the game hangs after the startup screen
   RAM[0x30007] = 0x00;  // bit 8 is vblank: if 0 the games hangs at startup


   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   setup_z80_gunbird();

   /* ----------- */

  // Main CPU: 68EC020
   // Speed hack
   WriteWord68k(&ROM[0x462],0x7F02);		//	raine	#$02 <stop cpu>
   WriteWord68k(&ROM[0x53418],0x7f04); // sound command
   WriteWord68k(&ROM[0x5341a],0x4e71);		//	nop
   WriteWord68k(&ROM[0x5341c],0x4e71); 		//	nop

   FreeMem(TMP);
}

void load_samuraia(void)
{
   int ta;
   int i,len = get_region_size(REGION_SMP1);
   //FILE *f;
   RAMSize = 0x70000;

   if(!(RAM=AllocateMem(RAMSize)))     return;
   if(!(GFX=AllocateMem(0x800000)))    return;
   if(!(LUT=AllocateMem(0x40000)))     return;  // sprites lookup table
   if(!(TMP=AllocateMem(0x200000)))    return;
   Z80RAM=Z80ROM;

   PCMROM = load_region[REGION_SMP1];
   /* Bit 6&7 of the samples are swapped. Naughty, naughty... */
   for (i=0;i<len;i++)
     {
       int x = PCMROM[i];
       PCMROM[i] = ((x & 0x40) << 1) | ((x & 0x80) >> 1) | (x & 0x3f);
     }

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   setup_z80_sngkace();

   GunbirdDecode("u14.bin", 0x000000, 0x200000);  // sprites (0x4000 tiles)
   GunbirdDecode("u34.bin", 0x400000, 0x100000);  // layer 0 & 1
   GunbirdDecode("u35.bin", 0x600000, 0x100000);

   if(!load_rom("u11.bin", LUT, 0x40000)) return;   // sprites LUT

   for(ta=0;ta<0x800000;ta++)
      GFX[ta]^=15;

   GFX_SPR = GFX;
   GFX_BG0 = GFX + 0x400000;
   GFX_BG1 = GFX + 0x600000;

   num_sprites = 0x4000-1;
   GFX_SPR_SOLID = make_solid_mask_16x16( GFX_SPR, num_sprites+1  );
   GFX_BG0_SOLID = make_solid_mask_16x16( GFX_BG0, 0x2000  );
   GFX_BG1_SOLID = make_solid_mask_16x16( GFX_BG1, 0x2000  );

   finish_psikyo_conf();

   memset(RAM+0x00000,0x00,RAMSize);
   memset(RAM+0x30000,0x00,0x10);

   // RAM[0x30009] = 0x7f;  // bit 8 is sound related and must be 0 if no sound is used, otherwise
                         // the game hangs after the startup screen
   RAM[0x3000B] = 0xfe;  // bit 1 is vblank: if 0 the games hangs at startup

  // Main CPU: 68EC020
   // Speed hack
   WriteWord68k(&ROM[0x46e],0x7F02);		//	raine	#$02 <stop cpu>

   // Samuraia handles its region code in the 4 higher bits of c00007
   // The problem is that these bits normally contain the tile banks.
   // So we will just fix it so that it looks at the 4 lowest bits instead
   // Sengoku ace was just ignoring these bits (and #0,d1)
   WriteWord68k(&ROM[0x994],0xe989); // lsl.l #4,d1
   WriteWord68k(&ROM[0x996],0x4e71); // nop

   if (is_current_game("samuraia")) {
       WriteWord68k(&ROM[0x71096],0x7f04); // sound command
       WriteWord68k(&ROM[0x71098],0x4e71);		//	nop
       WriteWord68k(&ROM[0x7109a],0x4e71); 		//	nop
   } else if (is_current_game("sngkace")) {
       WriteWord68k(&ROM[0x71020],0x7f04); // sound command
       WriteWord68k(&ROM[0x71022],0x4e71);		//	nop
       WriteWord68k(&ROM[0x71024],0x4e71); 		//	nop
   }
   FreeMem(TMP);
}

static int my_frame = CPU_FRAME_MHz(48,60);

void load_actual_s1945(void)
{
   int ta,num_bg0;

   RAMSize = 0x70000;

   if(!(RAM=AllocateMem(RAMSize)))     return;
   if(!(GFX=AllocateMem(0x1400000)))    return;
   LUT = load_region[REGION_USER1];
   if(!(TMP=AllocateMem(0x400000)))    return;
   Z80RAM=Z80ROM;

   PCMROM = load_region[REGION_SMP1];

   // Setup Z80 memory map
   // --------------------

   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);

   setup_z80_s1945();

   GFX_BG0 = my_decode_region(REGION_GFX1,GFX);
   num_sprites = (GFX_BG0 - GFX) / 0x100 - 1;
   GFX_BG1 = my_decode_region(REGION_GFX2,GFX_BG0);
   num_bg0 = (GFX_BG1 - GFX_BG0) / 0x100;

   if (strcmp(current_game->main_name,"tengai")) {
     for(ta=0;ta<0x1400000;ta++)
       GFX[ta]^=15;
#if 0
   } else {
     // Tengai changes its transparant color on the fly : 0 or 15.
     // For now the only reasonable solution seems to be to prepare 1 sprite
     // bank for each color...
     if(!(GFX_XOR=AllocateMem(0x1400000)))    return;
     memcpy(GFX_XOR,GFX,0x1400000);
/*    } else { */
/*      // only bg0 and bg1 have color 15 transparent... */
/*      while (GFX_BG1 > GFX_BG0) */
/*        *(--GFX_BG1) ^= 15; */
#endif
   }

   GFX_SPR = GFX;
   GFX_BG1 = GFX_BG0;

   GFX_SPR_SOLID = make_solid_mask_16x16( GFX_SPR, num_sprites+1  );
   GFX_BG0_SOLID = make_solid_mask_16x16( GFX_BG0, num_bg0  );
   GFX_BG1_SOLID = GFX_BG0_SOLID;

   finish_psikyo_conf();

   sound_mem = &RAM[0x30011];

   memset(RAM+0x00000,0,RAMSize);

   // RAM[0x30009] = 0x7f;  // bit 8 is sound related and must be 0 if no sound is used, otherwise
                         // the game hangs after the startup screen
   RAM[0x3000B] = 0xfe;  // bit 1 is vblank: if 0 the games hangs at startup

  // Main CPU: 68EC020
   // Protection
   if (!strcmp(current_game->main_name,"s1945j")) { // original (japan)
     WriteLong68k(&ROM[0xc4d8],0x302f0004); // move 4(sp),d0
     WriteWord68k(&ROM[0xc4dc],0xd079);
     WriteLong68k(&ROM[0xc4de],0xfffe2bb2); // add ext,d0
     WriteWord68k(&ROM[0xc4e2],0x7F03);	// raine #$03 -> read mcu table
     WriteWord68k(&ROM[0xc4e4],0x4e75); // rts

     WriteWord68k(&ROM[0x19540],0x4e71); // disable* mcu test

     WriteWord68k(&ROM[0x199ce],0x7F02); // raine #$02 <stop cpu / speed hack>
     WriteWord68k(&ROM[0x1867c],0x7f05); // sound command
     WriteWord68k(&ROM[0x1867e],0x4e71);		//	nop
     WriteWord68k(&ROM[0x18680],0x4e71); 		//	nop
   } else if (!strcmp(current_game->main_name,"s1945")) {
     WriteLong68k(&ROM[0xc464],0x302f0004); // move 4(sp),d0
     WriteWord68k(&ROM[0xc468],0xd079);
     WriteLong68k(&ROM[0xc46a],0xfffe2bb2); // add ext,d0
     WriteWord68k(&ROM[0xc46e],0x7F03);	// raine #$03 -> read mcu table
     WriteWord68k(&ROM[0xc470],0x4e75); // rts

     WriteWord68k(&ROM[0x194dc],0x4e71); // disable* mcu test

     WriteWord68k(&ROM[0x1996a],0x7F02); // raine #$02 <stop cpu / speed hack>
     WriteWord68k(&ROM[0x18618],0x7f05); // sound command
     WriteWord68k(&ROM[0x1861a],0x4e71);		//	nop
     WriteWord68k(&ROM[0x1861c],0x4e71); 		//	nop
   } else if (!strcmp(current_game->main_name,"tengai")) {
     WriteWord68k(&ROM[0x190de],0x7000); // moveq #0,d0
     WriteWord68k(&ROM[0x190e0],0x4e75); // rts

     WriteWord68k(&ROM[0x19318],0x203c); // move.l ...
     WriteLong68k(&ROM[0x1931a],0x55);   // #85,d0
     WriteWord68k(&ROM[0x1931e],0x4e75); // rts (second mcu test)

     // speed hack
     WriteWord68k(&ROM[0xa0a],0x7F02); // raine #$02 <stop cpu / speed hack>

     // remove sound test
     WriteWord68k(&ROM[0x128e],0x4e71); // raine #$02 <stop cpu / speed hack>

     // WriteWord68k(&ROM[0x1a384],0x7f05); // debug
     WriteWord68k(&ROM[0x1a026],0x7f05); // sound command
     WriteWord68k(&ROM[0x1a028],0x4e71);		//	nop
     WriteWord68k(&ROM[0x1a02a],0x4e71); 		//	nop

   }

   FreeMem(TMP);
}

void load_s1945(void)
{
  mcu_table = s1945_table;
  load_actual_s1945();
}

void load_s1945j(void)
{
  mcu_table = s1945j_table;
  load_actual_s1945();
}

#define load_tengai load_s1945

// This frame lets the z80 slice the frame for the 2 cpu.
// It's supposed to eat less cpu power. In fact, there is no noticeable
// difference, except that some sounds get lost (because the 68020 has
// still no write handlers !). For now the other ExecuteFrame below is better

// 19/5/2002 : it seems the new z80 core does not loose sounds anymore with
// this one. I'll keep it for now.

// 2/9/2002 : actually sengoku ace misses some sounds, but it's not related
// to the cpu frame. It's just because the 68020 writes too quickly the sound
// command, and since we don't have any handlers, we miss it.
// 2 solutions : patch the rom to use a raine instruction for the sound...
// but it does not look easy since the location where the sound command is
// written is not easy to find.
// or just change the 68020 core to have handlers. No comment.

void execute_gunbird(void)
{
  // fprintf(stderr,"30009 : %x\n",RAM[0x30009]);
  if (RaineSoundCard) {
    int frame = FRAME_Z80;
    int diff;
    cycles = 1;
    while (frame > 0) {
      diff = execute_one_z80_audio_frame(frame);
      if (cycles) {// cycles = 0 if we reached the speed hack
	cpu_execute_cycles(CPU_M68020_0, diff *8);	// M68020 32MHz (60fps)
      }
      frame -= diff;
    }
    cpu_interrupt(CPU_M68020_0, 1);
  } else { // no sound version (no use for a z80)
    cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(32,60));	// M68020 32MHz (60fps)
    cpu_interrupt(CPU_M68020_0, 1);
  }
}

void ExecuteFrame_nosound() {
  // For Strikers 1945, which does not have any sound.
  cpu_execute_cycles(CPU_M68020_0, my_frame);	// M68020 32MHz (60fps)
  cpu_interrupt(CPU_M68020_0, 1);
}

GMEI( s1945,
   "Strikers 1945 (World)",
   PSIKYO,
   1995,
   GAME_SHOOT,
   .romsw = romsw_gunbird);

CLNEI(s1945j, s1945, "Strikers 1945 (Japan)", PSIKYO, 1995, GAME_SHOOT,
	.load_game = &load_s1945j);

GMEI( tengai,
       "Tengai/Sengoku Blade:Sengoku Ace II",
       PSIKYO,
       1996,
       GAME_SHOOT,
       .romsw = romsw_sngkace);

static void DrawSpritesP()
{

   int zz,zzz,zzzz,x16,y16,x,y,ta,zoomx,zoomy,prio,nx,ny;
   UINT8 *map;
   int attr, xstart, xend, ystart, yend, dx, dy, yinc, xinc;


   //if(!(RAM_SPR_LST[0x7Fe]&1)){
   if(!(buf2_spr[0x1FFF]&1)){

     for(zz=0;zz<0x7FE;zz+=2) {

         zzz = ReadWord68k(&RAM_SPR_LST[zz]);
         if( zzz==0xFFFF ) break;
         zzzz = (zzz%0x300) << 3;

         attr = ReadWord68k(&buf2_spr[zzzz+4]);
	 // prio = (attr & 0xc0) >> 6;
	 if ((attr&0xC0) <= 1) {
	   prio = 2; // always visible
	 } else {
	   prio = 0; // under layer (bg1 at least)
	 }
	 // notice : there are 4 possible priorities for only 2 bg layers !!!

	 y = ReadWord68k(&buf2_spr[zzzz]);
	 x = ReadWord68k(&buf2_spr[zzzz+2]);
	 zzz = ReadWord68k(&buf2_spr[zzzz+6])|((attr&1)<<16);


	 /* 180-1ff are negative coordinates. Note that $80 pixels is
	    the maximum extent of a sprite, which can therefore be moved
	    out of screen without problems */
	 //	    if (x>=0x180) x-=0x200;

	 y16 = (y&0xFF)-(y&0x100) + 32;
	 x16 = (x&0x1FF);
	 x16+= (x16>=0x180) ? (32-0x200) : 32;

	 /* 	    x16 = x+32; */
/* 	    y16 = y+32; */

	 zoomx	=	((x & 0xf000) >> 12);
	 zoomy	=	((y & 0xf000) >> 12);

	 nx = ((x>>9)&7)+1;
	 ny = ((y>>9)&7)+1;


	 // the zoom here is 0..15, 0 for final zoom 16 (default),
	 // 15 for 8 (min)
	 // The game has a weird way to compute alignement for zoomed
	 // sprites with zoom < 14. It shows on the explosion of the
	 // weapon of the 1st plane in s1945.
	 //x16 += (nx*zoomx+2)/4;
	 //y16 += (ny*zoomy+2)/4;

	 /*  	    if (zoomx || zoomy) { */

	 // You loose less precision with this one (integer maths)
	 x16 += (nx*zoomx+2)/4;
	 y16 += (ny*zoomy+2)/4;
	 zoomx = (32-zoomx);
	 zoomy = (32-zoomy);
	 //x16 &= 0xfffe;
	 //y16 &= 0xfffe;
/* 	    } else { */
/* 	      zoomx = 16; */
/* 	      zoomy = 16; */
/* 	    } */

	 if(attr&0x4000){  // flipX
	   xstart = nx-1;
	   xend=-1;
	   xinc=-1;
	 } else {
	   xstart = 0;
	   xend=nx;
	   xinc=1;
	 }

	 if(attr&0x8000){  // flipY
	   ystart = ny-1;
	   yend=-1;
	   yinc=-1;
	 } else {
	   ystart = 0;
	   yend=ny;
	   yinc=1;
	 }

	 //if ((nx > 1 || ny > 1) && zoom_orig)
	 //fprintf(stderr,"draw %d,%d zoom %d,%d n %d,%d zoom_orig %d (+%d)\n",x16,y16,zoomx,zoomy,nx,ny,zoom_orig,(ny*(zoom_orig)+2)/4);

	 zoomx>>=1;
	 zoomy>>=1;
	 for(dy=ystart; dy!=yend; dy+=yinc) {
	   for(dx=xstart; dx!=xend; dx+=xinc) {

	     y = y16 + dy*zoomy;

	     if( (y>=16) && (y<=224+32) ) {

	       x = x16 + dx*zoomx;

	       if( (x>=16) && (x<=320+32) ) {

		 ta = ReadWord(&LUT[(zzz<<1)&0x3ffff]);
		 if(GFX_SPR_SOLID[ta]) {

		   MAP_PALETTE_MAPPED_NEW(
					  (attr>>8)&0x1F,
					  16,
					  map
					  );

		   if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
		     switch((attr>>8)&0xC0){
		     case 0x00: pdraw16x16_Trans_Mapped_ZoomXY_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio);        break;
		     case 0x40: pdraw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio);  break;
		     case 0x80: pdraw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio);  break;
		     case 0xC0: pdraw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio); break;
		     }
		   } else{						// all pixels; solid
		     switch((attr>>8)&0xC0){
		     case 0x00: pdraw16x16_Mapped_ZoomXY_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio);        break;
		     case 0x40: pdraw16x16_Mapped_ZoomXY_FlipY_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio);  break;
		     case 0x80: pdraw16x16_Mapped_ZoomXY_FlipX_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy,  prio);  break;
		     case 0xC0: pdraw16x16_Mapped_ZoomXY_FlipXY_Rot(&GFX_SPR[ta<<8], x, y, map, zoomx, zoomy, prio); break;
		     }
		   }
		 }
	       }
	     }
	     zzz++;
	   } // for dx
	 } // for dy
	 //fprintf(stderr,"\n");
     }
   }
#if 0
   else
     print_ingame(1,gettext("sprites disabled"));
#endif

}

// There are lots of little functions, but they are not complex :
// we have BG0 (solid) and then BG1 (normal)
// both have line scroll and normal versions, for every tile size.

static UINT16 tile_bank0, tile_bank1;
static INT16 offsets[256];
static UINT16 layer0_ctrl, layer1_ctrl;

static void scroll_bg0(int width, int height) {
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;
  if (!(layer0_ctrl & 2)) // not opaque
      clear_game_screen(0);
  MAKE_SCROLL_n_16(width,height,2,
			    ReadWord68k(&RAM[0x24406]),
			    ReadWord68k(&RAM[0x24402])
			    );

  START_SCROLL_16(32,32,320,224);

  ta = (ReadWord68k( &RAM_BG0[zz] ) & 0x1FFF)+tile_bank0;

  MAP_PALETTE_MAPPED_NEW(
	  (RAM_BG0[zz] >> 5)|0x80,
	  16,
	  map
	  );

  // Layer 0 doesn't change anything to pbitmap
  if (layer0_ctrl & 2 || GFX_BG0_SOLID[ta] == 2)
      Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);
  else if (GFX_BG0_SOLID[ta]) {
      Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);
  }

  END_SCROLL_n_16(width,height,2);
}

// geometry of layers for line scroll
// Please use the Backslashify macro from emacs to edit this code (C-C C-\)
// This function is quite generic, but I don't see any easy way to make it completely
// generic (usable directly in another driver...)

static void scroll_bg0_lscroll(int width, int height) {
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;
  INT16 scrollx = ReadWord68k(&RAM[0x24406]), scrolly = ReadWord68k(&RAM[0x24402]);
  MAKE_SCROLL_n_16(width,height,2,
			    scrollx,
			    scrolly
			    );

  zz=zzzz;
  for(y=(32-y16);(UINT32)y<(224+32);y+=16){
    int min = 999, max = -999;
    int n;
    INT16 *offs = &offsets[y-32];

    if (y<32) {
      zz = zzzz = (zzzz+(width*2/16))&(width*height*2/(16*16)-1);
      continue;
    }


    for (n=0; n<16; n++) {
      ta = offs[n];
      if (min > ta)
	min = ta;
      if (max < ta)
	max = ta;
    }
    if (min) {
      if (min & 15) /* min is not on the limit of a sprite */
	min = (min > 0) ? min/16 + 1 : min/16 - 1;
      else
	min /= 16;
    }
    if (max) {
      if (max & 15)
	max = max/16 +1;
      else
	max /= 16;
    }
    if (max || min) { /* some line scroll for this line */

      /* Start earlier, finish later... */
      zz=(zz&(width*height*2/(16*16)-width*2/16))|((zz-max*2)&(width*2/16-1));
      for(x=(32-x16-max*16);x<(320+32-min*16);x+=16){

	ta = (ReadWord68k( &RAM_BG0[zz] ) & 0x1FFF)+tile_bank0;

	MAP_PALETTE_MAPPED_NEW(
			   (RAM_BG0[zz] >> 5)|0x80,
              16,
              map
            );

	if (layer0_ctrl & 2 || GFX_BG0_SOLID[ta] == 2)
	    ldraw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map,offs);
	else if (GFX_BG0_SOLID[ta] == 1)
	    ldraw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map,offs);

	zz=(zz&(width*height*2/(16*16)-width*2/16))|((zz+2)&(width*2/16-1));
      }
    } else { /* no line scroll for this line... */
      for(x=(32-x16);x<(320+32);x+=16){

	ta = (ReadWord68k( &RAM_BG0[zz] ) & 0x1FFF)+tile_bank0;

	MAP_PALETTE_MAPPED_NEW(
  	      (RAM_BG0[zz] >> 5)|0x80,
              16,
              map
            );

	if (layer0_ctrl & 2 || GFX_BG0_SOLID[ta] == 2)
	    Draw16x16_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);
	else if (GFX_BG0_SOLID[ta]) {
	    Draw16x16_Trans_Mapped_Rot(&GFX_BG0[ta<<8], x, y, map);
	}
	zz=(zz&(width*height*2/(16*16)-width*2/16))|((zz+2)&(width*2/16-1));
      }
    }
    /* end of scrol */
    zz = zzzz = (zzzz+(width*2/16))&(width*height*2/(16*16)-1);
  } /* for(y... */
}

static void scroll_bg1(int width, int height) {
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;
  MAKE_SCROLL_n_16(width,height,2,
			    ReadWord68k(&RAM[0x2440E]),
			    ReadWord68k(&RAM[0x2440A])
			    );


  START_SCROLL_16(32,32,320,224);

  ta = (ReadWord68k( &RAM_BG1[zz] ) & 0x1FFF) + tile_bank1;

  if( GFX_BG1_SOLID[ta] || (layer1_ctrl & 2)){

    MAP_PALETTE_MAPPED_NEW(
			   (RAM_BG1[zz] >> 5)|0xC0,
              16,
              map
            );

    if(GFX_BG1_SOLID[ta]==2 || (layer1_ctrl & 2))
      pdraw16x16_Mask_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map, 1); // opaque
    else
      pdraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map, 1);
  }

  END_SCROLL_n_16(width,height,2);
}

// Same as def_bg0_lscroll, with transparency this time...

static void scroll_bg1_lscroll(int width,int height) {
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;
  MAKE_SCROLL_n_16(width,height,2,
			    ReadWord68k(&RAM[0x2440e]),
			    ReadWord68k(&RAM[0x2440a])
			    );

  zz=zzzz;
  for(y=(32-y16);(UINT32)y<(224+32);y+=16){
    int min = 999, max = -999;
    int n;
    INT16 *offs = &offsets[y-32];

    if (y<32) {
      /* Next line */
      zz = zzzz = (zzzz+(width*2/16))&(width*height*2/(16*16)-1);
      continue;
    }

    for (n=0; n<16; n++) {
      ta = offs[n];
      if (min > ta)
	min = ta;
      if (max < ta)
	max = ta;
    }
    if (min) {
      if (min & 15) /* min is not on the limit of a sprite */
	min = min/16 - 1;
      else
	min /= 16;
    }
    if (max) {
      if (max & 15)
	max = max/16 +1;
      else
	max /= 16;
    }
    if (max || min) { /* some line scroll for this line */

      /* Start earlier, finish later... */
      zz=(zz&(width*height*2/(16*16)-width*2/16))|((zz-max*2)&(width*2/16-1));
      for(x=(32-x16-max*16);x<(320+32-min*16);x+=16){

	ta = (ReadWord68k( &RAM_BG1[zz] ) & 0x1FFF)+tile_bank1;

	if( GFX_BG1_SOLID[ta] || (layer1_ctrl & 2)){

	  MAP_PALETTE_MAPPED_NEW(
	      (RAM_BG1[zz] >> 5)|0xc0,
              16,
              map
            );

	  if(GFX_BG1_SOLID[ta]==2 || (layer1_ctrl & 2)) {
	    pldraw16x16_Mask_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map,offs,1);
	  } else {
	    pldraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map,offs,1);
	  }
	}

	zz=(zz&(width*height*2/(16*16)-width*2/16))|((zz+2)&(width*2/16-1));
      }
    } else { /* no line scroll for this line... */
      for(x=(32-x16);x<(320+32);x+=16){

	ta = (ReadWord68k( &RAM_BG1[zz] ) & 0x1FFF)+tile_bank1;

	if( GFX_BG1_SOLID[ta] || (layer1_ctrl & 2)){
	  MAP_PALETTE_MAPPED_NEW(
  	      (RAM_BG1[zz] >> 5)|0xc0,
              16,
              map
            );

	  if(GFX_BG1_SOLID[ta]==2 || (layer1_ctrl & 2))
	      pdraw16x16_Mask_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map, 1); // opaque
	  else
	      pdraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG1[ta<<8], x, y, map, 1);
	}
	zz=(zz&(width*height*2/(16*16)-width*2/16))|((zz+2)&(width*2/16-1));
      }
    }
    /* end of scrol */
    zz = zzzz = (zzzz+(width*2/16))&(width*height*2/(16*16)-1);
  } /* for(y... */
}

#define LINE_SCROLL_BG0 1
#define LINE_SCROLL_BG1 1

void DrawGunbird(void)
{
  ClearPaletteMap();
  tile_bank0 = ((RAM[0x30007] >> 4) & 3) * 0x2000;
  tile_bank1 = ((RAM[0x30007] >> 6) & 3) * 0x2000;
  clear_bitmap(pbitmap);

   //    BG0
   // ----------

  if( check_layer_enabled(layer_id_data[0])) {
    layer0_ctrl = ReadWord68k(&RAM[0x24412]);
    if(!(layer0_ctrl&1)) {
      int min=0,max=0;
      // linescroll effect is troublesome on bg0
      // bg0 is used normally as a solid layer to clear the screen.
      // we can't do it if a part of the layer goes off screen.
      // Moreover this one requires to modify start_scroll
      // to be able to start further on the left if the linescroll is on the
      // right. For now, it's not a big problem to just comment it out.
#if LINE_SCROLL_BG0
      if (RAM[0x24412] & 1) {
	INT16 i,ta;
	min = 999; max = -999;
	for (i=0; i<256; i++) {
	  ta = -ReadWord68k(&RAM[0x24000+(i<<1)]);
	  offsets[i] = ta;
	  if (min > ta)
	    min = ta;
	  if (max < ta)
	    max = ta;
	}
      }
      if (min || max) { // line scroll effect
#ifdef RAINE_DEBUG
	print_ingame(1,gettext("line scroll bg0 %d %d size %d"),min,max,(layer0_ctrl & 0xc0) >> 6);
#endif
	switch((layer0_ctrl & 0xc0) >> 6) {
	case 0: scroll_bg0_lscroll(1024,1024); break;
	case 1: scroll_bg0_lscroll(2048,512);  break;
	case 2: scroll_bg0_lscroll(4096,256);  break;
	default:scroll_bg0_lscroll(512,2048); break;
	}
      } else {
#endif
	switch((layer0_ctrl & 0xc0) >> 6) {
	case 0: scroll_bg0(1024,1024); break;
	case 1: scroll_bg0(2048,512);  break;
	case 2: scroll_bg0(4096,256);  break;
	default:scroll_bg0(512,2048); break;
	}
#if LINE_SCROLL_BG0
      }
#endif
    }
    else {
      clear_game_screen(0);
      // print_ingame(1,gettext("BG0 disabled"));
    }
  }
  else {
    clear_game_screen(0);
  }

  layer1_ctrl = RAM[0x24417];


   //    BG1
   // ----------

  if( check_layer_enabled(layer_id_data[1]) && !(layer1_ctrl & 1)) {
    INT16 min = 0, max = 0;
#if LINE_SCROLL_BG1
    if (RAM[0x24416] & 1) { // line scroll ?
      INT16 i,ta;
      for (i=0; i<256; i++) {
	ta = -ReadWord68k(&RAM[0x24200+(i<<1)]);
	offsets[i] = ta;
	if (min > ta)
	  min = ta;
	if (max < ta)
	  max = ta;
      }
      // print_ingame(1,gettext("line scroll bg1 %d %d size %d"),min,max,(layer1_ctrl & 0xc0) >> 6);
    }
    if (max || min) { // some line scroll...
#ifdef RAINE_DEBUG
      print_ingame(1,gettext("line scroll bg1 %d %d size %d"),min,max,(layer1_ctrl & 0xc0) >> 6);
#endif
      switch((layer1_ctrl & 0xc0) >> 6) {
      case 0: scroll_bg1_lscroll(1024,1024); break;
      case 1: scroll_bg1_lscroll(2048,512);  break;
      case 2: scroll_bg1_lscroll(4096,256);  break;
      default:scroll_bg1_lscroll(512,2048); break;
      }
    } else { // no line scroll...
#endif
      switch((layer1_ctrl & 0xc0) >> 6) {
      case 0: scroll_bg1(1024,1024); break;
      case 1: scroll_bg1(2048,512);  break;
      case 2: scroll_bg1(4096,256);  break;
      default:scroll_bg1(512,2048); break;
      }
#if LINE_SCROLL_BG1
    }
#endif
  } else
    print_ingame(1,gettext("layer 1 disabled"));

  if( check_layer_enabled(layer_id_data[2]))
    DrawSpritesP();

  // the sprites are buffered. It shows during the demo of s1945
  // (a pink shadow appears under the big plane pictures while they are
  // scrolling to the right).
  /* After some tests, this slows down the emulation by 1.80s on my duron600
     after 60 000 frames !!!! So it's about 1/1000 slow down. Usefull to know
  */
  memcpy(buf2_spr,buf1_spr,0x2000);
  memcpy(buf1_spr,RAM_SPR,0x2000);
}
