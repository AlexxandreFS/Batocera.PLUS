#define DRV_DEF_SOUND taito_ym2151_sound
/******************************************************************************/
/*                                                                            */
/*            TOP SPEED / FULL THROTTLE (C) 1986 TAITO CORPORATION            */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines
#include "zoom/16x8.h"		// 16x8 zoomed sprite routines


static struct ROM_INFO rom_fullthrl[] =
{
   {       "b14-02", 0x00080000, 0x6889186b, 0, 0, 0, },
   {       "b14-01", 0x00080000, 0x84a56f37, 0, 0, 0, },
   {       "b14-03", 0x00080000, 0xd1ed9e71, 0, 0, 0, },
   {       "b14-04", 0x00080000, 0xb63f0519, 0, 0, 0, },
   {       "b14-05", 0x00080000, 0x6557e9d8, 0, 0, 0, },
   {       "b14-06.52", 0x00020000, 0xb4e2536e, 0, 0, 0, },
   {       "b14-07.54", 0x00020000, 0xc6025fff, 0, 0, 0, },
   {       "b14-25.67", 0x00010000, 0x9eab28ef, 0, 0, 0, },
   {       "b14-28.103", 0x00010000, 0xdf11d0ae, 0, 0, 0, },
   {       "b14-29.109", 0x00010000, 0x7ad983e7, 0, 0, 0, },
   {       "b14-30.88", 0x00010000, 0xdccb0c7f, 0, 0, 0, },
   {       "b14-31.90", 0x00002000, 0x5c6b013d, 0, 0, 0, },
   {       "b14-67", 0x00010000, 0x284c943f, 0, 0, 0, },
   {       "b14-68", 0x00010000, 0x54cf6196, 0, 0, 0, },
   {       "b14-69.80", 0x00010000, 0xd652e300, 0, 0, 0, },
   {       "b14-71", 0x00010000, 0xf7081727, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_topspeed[] =
{
   INP1( COIN1, 0x055004, 0x08 ),
   INP1( COIN2, 0x055004, 0x04 ),
   INP0( SERVICE, 0x055004, 0x10 ),
   INP0( TILT, 0x055006, 0x02 ),

   INP0( P1_START, 0x055006, 0x08 ),

// Fake wheel addresses, used for keyboard support
   INP1( P1_LEFT, 0x05501C, 0xFF ),
   INP1( P1_RIGHT, 0x05501D, 0xFF ),

// Fake pedal addresses, used for keyboard support - Unsure if adresses are really unused
   { KB_DEF_P1_B1,        "Accelerator",           0x05501E, 0xFF, BIT_ACTIVE_1 },
   { KB_DEF_P1_B3,        "Brake",                 0x05501B, 0xFF, BIT_ACTIVE_1 },

   { KB_DEF_P1_B2,        "Low Gear",              0x055006, 0x10, BIT_ACTIVE_1 },
   { KB_DEF_P1_B4,        "Nitro",                 0x055006, 0x01, BIT_ACTIVE_0 },

   END_INPUT
};

/*

Note: Spinner control setting should not be used, because it's not compatible with PC controllers. Spinner is only usefull for MAME cabinet freaks that have built a custom controller, which behaves like a primitive steering wheel from the 1970's. Only the Analog dipswitch settings will work on PC hardware (keyboards and joysticks).

Top Speed Controls Description by Warlock

Cabinet type is selectable via dipswitches A1 and A2


A2A1 - 00 (Sit-Down with good wheel)

Motor: No
Pedals Type: Analog
Wheel Type: Normal

A2A1 - 01 (Sit-Down with bad wheel)

Motor: No
Pedals Type: Analog
Wheel Type: Spinner

A2A1 - 10 (Upright)

Motor: No
Pedals Type: Digital
Wheel Type: Spinner

A2A1 - 11 - (Deluxe Motorized Sit-Down)

Motor: Yes
Pedals Type: Analog
Wheel Type: Normal


Analog Pedals Behaviour (same for Accelerator and Brake)

Accelerator - Address 0x055006; bits 0xE0
Brake       - Address 0x055004; bits 0xE0

(Address - Speed Setting)

000 - 0
001 - 1
010 - 3
011 - 2
100 - 7
101 - 6
110 - 4
111 - 5

or

000 - 0
001 - 1
011 - 2
010 - 3
110 - 4
111 - 5
101 - 6
100 - 7

As you can see from the table above, the non-linear behaviour of the pedal is pretty stupid, it's not "standard" :(

In order to support PC analog pedals, the following method could be used:

For the accelerator, divide joy_y by 16, and for each of the 8 possible states, feed the result in the machine RAM, using the above conversion table.

For the brake replace "joy_y" with "-joy_y".

For the steering wheel, the following would work:

  RAM[0x05501A] = (joy_x)>>8;
  RAM[0x055018] = (joy_x);

I won't bother doing this because the graphics are not emulated properly, also the game is running too fast (200% speed maybe)


*/

static struct DSW_DATA dsw_data_full_throttle_0[] =
{

// Spinner wheel behaviour is not supported, user is not allowed to change the cabinet.

//   { _("Cabinet"),               0x03, 0x04 },
//   { _("Wheel"),                 0x03},
//   { _("Spinner"),               0x02},
//   { _("Spinner + Digital"),     0x01},
//   { _("Wheel + Motor"),         0x00},

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

static struct DSW_DATA dsw_data_full_throttle_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Start Time"),            0x0C, 0x04 },
   { "60",                    0x0C},
   { "70",                    0x08},
   { "50",                    0x04},
   { "40",                    0x00},
   { _("Nitros per Stage"),      0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "4",                     0x10},
   { "5",                     0x00},
   DSW_CONTINUE_PLAY( 0x00, 0x40),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_topspeed[] =
{
   { 0x055000, 0xFF, dsw_data_full_throttle_0 },
   { 0x055002, 0xFF, dsw_data_full_throttle_1 },
   { 0,        0,    NULL,      },
};

/*
static struct ROMSW_DATA romsw_data_full_throttle_0[] =
{
   { "Taito 0",               0x00 },
   { "Taito 1",               0x01 },
   { "Taito 2",               0x02 },
   { "Taito 3",               0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO full_throttle_romsw[] =
{
   { 0x0BFFFF, 0xFF, romsw_data_full_throttle_0 },	// Bad Data?!
   { 0,        0,    NULL },
};
*/



static struct ROM_INFO rom_topspeed[] =
{
   {       "b14-47.3", 0x00020000, 0xb3a1f75b, 0, 0, 0, },
   {       "b14-07.54", 0x00020000, 0xc6025fff, 0, 0, 0, },
   {       "b14-25.67", 0x00010000, 0x9eab28ef, 0, 0, 0, },
   {       "b14-28.103", 0x00010000, 0xdf11d0ae, 0, 0, 0, },
   {       "b14-29.109", 0x00010000, 0x7ad983e7, 0, 0, 0, },
   {       "b14-30.88", 0x00010000, 0xdccb0c7f, 0, 0, 0, },
   {       "b14-31.90", 0x00002000, 0x5c6b013d, 0, 0, 0, },
   {       "b14-36.13", 0x00020000, 0x20a7c1b8, 0, 0, 0, },
   {       "b14-37.9", 0x00020000, 0x801b703b, 0, 0, 0, },
   {       "b14-38.5", 0x00020000, 0xde0c213e, 0, 0, 0, },
   {       "b14-39.1", 0x00020000, 0x798c28c5, 0, 0, 0, },
   {       "b14-40.14", 0x00020000, 0xfa2a3cb3, 0, 0, 0, },
   {       "b14-41.10", 0x00020000, 0x09455a14, 0, 0, 0, },
   {       "b14-42.6", 0x00020000, 0xab51f53c, 0, 0, 0, },
   {       "b14-43.2", 0x00020000, 0x1e6d2b38, 0, 0, 0, },
   {       "b14-44.15", 0x00020000, 0x9f6c030e, 0, 0, 0, },
   {       "b14-45.11", 0x00020000, 0x63e4ce03, 0, 0, 0, },
   {       "b14-46.7", 0x00020000, 0xd489adf2, 0, 0, 0, },
   {       "b14-06.52", 0x00020000, 0xb4e2536e, 0, 0, 0, },
   {       "b14-48.16", 0x00020000, 0x30c7f265, 0, 0, 0, },
   {       "b14-49.12", 0x00020000, 0x32ba4265, 0, 0, 0, },
   {       "b14-50.8", 0x00020000, 0xec1ef311, 0, 0, 0, },
   {       "b14-51.4", 0x00020000, 0x35041c5f, 0, 0, 0, },
   {       "b14-52.26", 0x00020000, 0xe1b5b2a1, 0, 0, 0, },
   {       "b14-53.25", 0x00020000, 0x04a04f5f, 0, 0, 0, },
   {       "b14-54.24", 0x00020000, 0x172924d5, 0, 0, 0, },
   {       "b14-55.23", 0x00020000, 0xa1f15499, 0, 0, 0, },
   {     "b14-67-1.11", 0x00010000, 0x23f17616, 0, 0, 0, },
   {     "b14-68-1.9", 0x00010000, 0x835659d9, 0, 0, 0, },
   {       "b14-69.80", 0x00010000, 0xd652e300, 0, 0, 0, },
   {       "b14-70.81", 0x00010000, 0xb720592b, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static int romset;

#define OBJ_A_COUNT	(0x8000)

// OBJECT TILE MAPS

static UINT8 *OBJECT_MAP;

// 16x16 OBJECT TILES BANK A

static UINT8 *GFX_OBJ_A;
static UINT8 *GFX_OBJ_A_SOLID;

static UINT8 *zoom16_ofs;
static UINT8 *zoom8_ofs;

static UINT8 *RAM_VIDEO;
static UINT8 *RAM_VIDEO_2;
static UINT8 *RAM_SCROLL;
static UINT8 *RAM_SCROLL_2;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0_SOLID;

static int tcpu=0;

static int BadReadByte(UINT32 address)
{
      print_debug("Rb%01d(%06x) [%06x]\n",tcpu,address,s68000context.pc);
   return(0x55);
}

static int BadReadWord(UINT32 address)
{
       print_debug("Rw%01d(%06x) [%06x]\n",tcpu,address,s68000context.pc);
   return(0x5555);
}

static void load_topspeed(void)
{
   int ta,tb,tc;
   UINT8 *TMP;
   if (is_current_game("fullthrl"))
       romset = 0;
   else if (is_current_game("topspeed"))
       romset = 1;

   if(!(GFX=AllocateMem(0x80000))) return;

   if(!(GFX_OBJ_A=AllocateMem(OBJ_A_COUNT*0x80))) return;

   if(!(TMP=AllocateMem(0x80000))) return;

   if(romset==0){
   if(!load_rom("b14-04", TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] =((tc&0x8000)>>(15));
      GFX_OBJ_A[tb+1] =((tc&0x4000)>>(14));
      GFX_OBJ_A[tb+2] =((tc&0x2000)>>(13));
      GFX_OBJ_A[tb+3] =((tc&0x1000)>>(12));
      GFX_OBJ_A[tb+4] =((tc&0x0800)>>(11));
      GFX_OBJ_A[tb+5] =((tc&0x0400)>>(10));
      GFX_OBJ_A[tb+6] =((tc&0x0200)>>( 9));
      GFX_OBJ_A[tb+7] =((tc&0x0100)>>( 8));
      GFX_OBJ_A[tb+8] =((tc&0x0080)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x0040)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x0020)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x0010)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x0008)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x0004)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x0002)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x0001)>>( 0));
      tb+=16;
   }
   }
   else{
   if(!load_rom("b14-50.8", TMP+0x00000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-51.4", TMP+0x20000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-48.16", TMP+0x40000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-49.12", TMP+0x60000, 0x20000)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<0x40000;ta++){
      tc=TMP[ta];
      GFX_OBJ_A[tb+0] =((tc&0x80)>>( 7));
      GFX_OBJ_A[tb+1] =((tc&0x40)>>( 6));
      GFX_OBJ_A[tb+2] =((tc&0x20)>>( 5));
      GFX_OBJ_A[tb+3] =((tc&0x10)>>( 4));
      GFX_OBJ_A[tb+4] =((tc&0x08)>>( 3));
      GFX_OBJ_A[tb+5] =((tc&0x04)>>( 2));
      GFX_OBJ_A[tb+6] =((tc&0x02)>>( 1));
      GFX_OBJ_A[tb+7] =((tc&0x01)>>( 0));
      tc=TMP[ta+0x40000];
      GFX_OBJ_A[tb+8] =((tc&0x80)>>( 7));
      GFX_OBJ_A[tb+9] =((tc&0x40)>>( 6));
      GFX_OBJ_A[tb+10]=((tc&0x20)>>( 5));
      GFX_OBJ_A[tb+11]=((tc&0x10)>>( 4));
      GFX_OBJ_A[tb+12]=((tc&0x08)>>( 3));
      GFX_OBJ_A[tb+13]=((tc&0x04)>>( 2));
      GFX_OBJ_A[tb+14]=((tc&0x02)>>( 1));
      GFX_OBJ_A[tb+15]=((tc&0x01)>>( 0));
      tb+=16;
   }
   }
   if(romset==0){
   if(!load_rom("b14-03", TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(14));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(13));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(12));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(11));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>(10));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 9));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 8));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 7));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 1));
      tb+=16;
   }
   }
   else{
   if(!load_rom("b14-46.7", TMP+0x00000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-47.3", TMP+0x20000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-44.15", TMP+0x40000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-45.11", TMP+0x60000, 0x20000)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<0x40000;ta++){
      tc=TMP[ta];
      GFX_OBJ_A[tb+0] |=((tc&0x80)>>( 6));
      GFX_OBJ_A[tb+1] |=((tc&0x40)>>( 5));
      GFX_OBJ_A[tb+2] |=((tc&0x20)>>( 4));
      GFX_OBJ_A[tb+3] |=((tc&0x10)>>( 3));
      GFX_OBJ_A[tb+4] |=((tc&0x08)>>( 2));
      GFX_OBJ_A[tb+5] |=((tc&0x04)>>( 1));
      GFX_OBJ_A[tb+6] |=((tc&0x02)>>( 0));
      GFX_OBJ_A[tb+7] |=((tc&0x01)<<( 1));
      tc=TMP[ta+0x40000];
      GFX_OBJ_A[tb+8] |=((tc&0x80)>>( 6));
      GFX_OBJ_A[tb+9] |=((tc&0x40)>>( 5));
      GFX_OBJ_A[tb+10]|=((tc&0x20)>>( 4));
      GFX_OBJ_A[tb+11]|=((tc&0x10)>>( 3));
      GFX_OBJ_A[tb+12]|=((tc&0x08)>>( 2));
      GFX_OBJ_A[tb+13]|=((tc&0x04)>>( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x02)>>( 0));
      GFX_OBJ_A[tb+15]|=((tc&0x01)<<( 1));
      tb+=16;
   }
   }
   if(romset==0){
   if(!load_rom("b14-02", TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(13));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(12));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(11));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>(10));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 9));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 8));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 7));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 6));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 2));
      tb+=16;
   }
   }
   else{
   if(!load_rom("b14-42.6", TMP+0x00000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-43.2", TMP+0x20000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-40.14", TMP+0x40000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-41.10", TMP+0x60000, 0x20000)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<0x40000;ta++){
      tc=TMP[ta];
      GFX_OBJ_A[tb+0] |=((tc&0x80)>>( 5));
      GFX_OBJ_A[tb+1] |=((tc&0x40)>>( 4));
      GFX_OBJ_A[tb+2] |=((tc&0x20)>>( 3));
      GFX_OBJ_A[tb+3] |=((tc&0x10)>>( 2));
      GFX_OBJ_A[tb+4] |=((tc&0x08)>>( 1));
      GFX_OBJ_A[tb+5] |=((tc&0x04)>>( 0));
      GFX_OBJ_A[tb+6] |=((tc&0x02)<<( 1));
      GFX_OBJ_A[tb+7] |=((tc&0x01)<<( 2));
      tc=TMP[ta+0x40000];
      GFX_OBJ_A[tb+8] |=((tc&0x80)>>( 5));
      GFX_OBJ_A[tb+9] |=((tc&0x40)>>( 4));
      GFX_OBJ_A[tb+10]|=((tc&0x20)>>( 3));
      GFX_OBJ_A[tb+11]|=((tc&0x10)>>( 2));
      GFX_OBJ_A[tb+12]|=((tc&0x08)>>( 1));
      GFX_OBJ_A[tb+13]|=((tc&0x04)>>( 0));
      GFX_OBJ_A[tb+14]|=((tc&0x02)<<( 1));
      GFX_OBJ_A[tb+15]|=((tc&0x01)<<( 2));
      tb+=16;
   }
   }
   if(romset==0){
   if(!load_rom("b14-01", TMP, OBJ_A_COUNT*0x10)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<OBJ_A_COUNT*0x10;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_OBJ_A[tb+0] |=((tc&0x8000)>>(12));
      GFX_OBJ_A[tb+1] |=((tc&0x4000)>>(11));
      GFX_OBJ_A[tb+2] |=((tc&0x2000)>>(10));
      GFX_OBJ_A[tb+3] |=((tc&0x1000)>>( 9));
      GFX_OBJ_A[tb+4] |=((tc&0x0800)>>( 8));
      GFX_OBJ_A[tb+5] |=((tc&0x0400)>>( 7));
      GFX_OBJ_A[tb+6] |=((tc&0x0200)>>( 6));
      GFX_OBJ_A[tb+7] |=((tc&0x0100)>>( 5));
      GFX_OBJ_A[tb+8] |=((tc&0x0080)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x0040)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x0020)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x0010)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x0008)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x0004)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x0002)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x0001)<<( 3));
      tb+=16;
   }
   }
   else{
   if(!load_rom("b14-38.5", TMP+0x00000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-39.1", TMP+0x20000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-36.13", TMP+0x40000, 0x20000)) return;	// 16x16 OBJ A
   if(!load_rom("b14-37.9", TMP+0x60000, 0x20000)) return;	// 16x16 OBJ A
   tb=0;
   for(ta=0;ta<0x40000;ta++){
      tc=TMP[ta];
      GFX_OBJ_A[tb+0] |=((tc&0x80)>>( 4));
      GFX_OBJ_A[tb+1] |=((tc&0x40)>>( 3));
      GFX_OBJ_A[tb+2] |=((tc&0x20)>>( 2));
      GFX_OBJ_A[tb+3] |=((tc&0x10)>>( 1));
      GFX_OBJ_A[tb+4] |=((tc&0x08)>>( 0));
      GFX_OBJ_A[tb+5] |=((tc&0x04)<<( 1));
      GFX_OBJ_A[tb+6] |=((tc&0x02)<<( 2));
      GFX_OBJ_A[tb+7] |=((tc&0x01)<<( 3));
      tc=TMP[ta+0x40000];
      GFX_OBJ_A[tb+8] |=((tc&0x80)>>( 4));
      GFX_OBJ_A[tb+9] |=((tc&0x40)>>( 3));
      GFX_OBJ_A[tb+10]|=((tc&0x20)>>( 2));
      GFX_OBJ_A[tb+11]|=((tc&0x10)>>( 1));
      GFX_OBJ_A[tb+12]|=((tc&0x08)>>( 0));
      GFX_OBJ_A[tb+13]|=((tc&0x04)<<( 1));
      GFX_OBJ_A[tb+14]|=((tc&0x02)<<( 2));
      GFX_OBJ_A[tb+15]|=((tc&0x01)<<( 3));
      tb+=16;
   }
   }

   if(!load_rom("b14-07.54", TMP+0x00000, 0x20000)) return;	// 8x8 TILES
   if(!load_rom("b14-06.52", TMP+0x20000, 0x20000)) return;	// 8x8 TILES
   tb=0;
   for(ta=0;ta<0x20000;ta++){
      GFX[tb+3]=TMP[ta+0x00000]&15;
      GFX[tb+2]=TMP[ta+0x00000]>>4;
      GFX[tb+1]=TMP[ta+0x20000]&15;
      GFX[tb+0]=TMP[ta+0x20000]>>4;
      tb+=4;
   }

   FreeMem(TMP);

   RAMSize=0x80000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0xC0000))) return;

   if(romset==0){
   if(!load_rom("b14-67", RAM, 0x10000)) return;	// 68000 MAIN ROM
   }
   else{
   if(!load_rom("b14-67-1.11", RAM, 0x10000)) return; // 68000 MAIN ROM
   }
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(romset==0){
   if(!load_rom("b14-68", RAM, 0x10000)) return;
   }
   else{
   if(!load_rom("b14-68-1.9", RAM, 0x10000)) return;
   }
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   if(romset==0){
   if(!load_rom("b14-05", ROM+0x20000, 0x80000)) return;
   ByteSwap(ROM+0x20000,0x80000);
   }
   else{
   if(!load_rom("b14-54.24", RAM+0x00000, 0x20000)) return;
   if(!load_rom("b14-55.23", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+0x20000]=RAM[ta];
   }
   if(!load_rom("b14-52.26", RAM+0x00000, 0x20000)) return;
   if(!load_rom("b14-53.25", RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+0x20001]=RAM[ta];
   }
   }

   if(!load_rom("b14-69.80", RAM, 0x10000)) return;	// 68000 SUB ROM
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xA0000]=RAM[ta];
   }
   if(romset==0){
   if(!load_rom("b14-71", RAM, 0x10000)) return;
   }
   else{
   if(!load_rom("b14-70.81", RAM, 0x10000)) return;
   }
   for(ta=0;ta<0x10000;ta++){
      ROM[ta+ta+0xA0001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x64000;
   if(!load_rom("b14-25.67", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   AddTaitoYM2151(0x0348, 0x0294, 0x10000, NULL, NULL);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x64000);
   memset(RAM+0x55000,0xFF,0x00100);

   RAM_VIDEO    = RAM+0x10000;
   RAM_VIDEO_2  = RAM+0x20000;
   RAM_SCROLL   = RAM+0x1F000;
   RAM_SCROLL_2 = RAM+0x2F000;
   RAM_INPUT    = RAM+0x55000;
   OBJECT_MAP   = RAM+0x34000;

   GFX_OBJ_A_SOLID = make_solid_mask_16x8(GFX_OBJ_A, OBJ_A_COUNT);
   GFX_BG0_SOLID   = make_solid_mask_8x8(GFX, 0x2000);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);
   InitPaletteMap(RAM+0x30000, 0x100, 0x10, 0x8000);


   // Main 68000 Speed Hack
   // ---------------------

   WriteLong68k(&ROM[0x0063A],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0x0063E],0x00AA0000);	//

   // Sub 68000 Speed Hack
   // ---------------------

   WriteLong68k(&ROM[0xB3CA8],0x4EF80100);	// [B3CAE]

   WriteLong68k(&ROM[0xB413A],0x4EF80100);	// [B4140]

   WriteWord68k(&ROM[0xA0100],0x4EB9);		//
   WriteLong68k(&ROM[0xA0102],0x00014B9E);	//

   WriteLong68k(&ROM[0xA0106],0x13FC0000);	//	move.b	#$00,$AA0000
   WriteLong68k(&ROM[0xA010A],0x00AA0000);	//
   WriteWord68k(&ROM[0xA010E],0x6100-16);	//

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();
   memset(RAM_INPUT,0xFF,0x00020);

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn[0].layer[0].RAM	=RAM_VIDEO+0x0000;
   tc0100scn[0].layer[0].GFX	=GFX;
   tc0100scn[0].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[0].SCR	=RAM_SCROLL+0;
   tc0100scn[0].layer[0].type	=0;
   tc0100scn[0].layer[0].bmp_x	=32;
   tc0100scn[0].layer[0].bmp_y	=32;
   tc0100scn[0].layer[0].bmp_w	=320;
   tc0100scn[0].layer[0].bmp_h	=240;
   tc0100scn[0].layer[0].tile_mask=0x1FFF;
   tc0100scn[0].layer[0].scr_x	=16;
   tc0100scn[0].layer[0].scr_y	=8;

   tc0100scn[0].layer[1].RAM	=RAM_VIDEO+0x8000;
   tc0100scn[0].layer[1].GFX	=GFX;
   tc0100scn[0].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[0].layer[1].SCR	=RAM_SCROLL+2;
   tc0100scn[0].layer[1].type	=0;
   tc0100scn[0].layer[1].bmp_x	=32;
   tc0100scn[0].layer[1].bmp_y	=32;
   tc0100scn[0].layer[1].bmp_w	=320;
   tc0100scn[0].layer[1].bmp_h	=240;
   tc0100scn[0].layer[1].tile_mask=0x1FFF;
   tc0100scn[0].layer[1].scr_x	=16;
   tc0100scn[0].layer[1].scr_y	=8;

   tc0100scn[1].layer[0].RAM	=RAM_VIDEO_2+0x0000;
   tc0100scn[1].layer[0].GFX	=GFX;
   tc0100scn[1].layer[0].MASK	=GFX_BG0_SOLID;
   tc0100scn[1].layer[0].SCR	=RAM_SCROLL_2+0;
   tc0100scn[1].layer[0].type	=0;
   tc0100scn[1].layer[0].bmp_x	=32;
   tc0100scn[1].layer[0].bmp_y	=32;
   tc0100scn[1].layer[0].bmp_w	=320;
   tc0100scn[1].layer[0].bmp_h	=240;
   tc0100scn[1].layer[0].tile_mask=0x1FFF;
   tc0100scn[1].layer[0].scr_x	=16;
   tc0100scn[1].layer[0].scr_y	=8;

   tc0100scn[1].layer[1].RAM	=RAM_VIDEO_2+0x8000;
   tc0100scn[1].layer[1].GFX	=GFX;
   tc0100scn[1].layer[1].MASK	=GFX_BG0_SOLID;
   tc0100scn[1].layer[1].SCR	=RAM_SCROLL_2+2;
   tc0100scn[1].layer[1].type	=0;
   tc0100scn[1].layer[1].bmp_x	=32;
   tc0100scn[1].layer[1].bmp_y	=32;
   tc0100scn[1].layer[1].bmp_w	=320;
   tc0100scn[1].layer[1].bmp_h	=240;
   tc0100scn[1].layer[1].tile_mask=0x1FFF;
   tc0100scn[1].layer[1].scr_x	=16;
   tc0100scn[1].layer[1].scr_y	=8;

   tc0100scn[0].RAM     = RAM_VIDEO;
   tc0100scn[0].GFX_FG0 = NULL;

   tc0100scn[1].RAM     = RAM_VIDEO_2;
   tc0100scn[1].GFX_FG0 = NULL;

   init_tc0100scn(0);
   init_tc0100scn(1);

   init_16x8_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1z();
   zoom8_ofs  = make_16x8_zoom_ofs_type1z();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0xC0000);
   ByteSwap(RAM,0x64000);

   AddMemFetch(0x000000, 0x01FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x01FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x080000, 0x0FFFFF, NULL, ROM+0x020000);                 // DATA ROM
   AddReadByte(0x400000, 0x40FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0xB00000, 0xB0FFFF, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadByte(0x7E0000, 0x7E0003, tc0140syt_read_main_68k, NULL); 	// SOUND
   AddReadByte(0x000000, 0xFFFFFF, BadReadByte, NULL);			// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x01FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x080000, 0x0FFFFF, NULL, ROM+0x020000);                 // DATA ROM
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0xB00000, 0xB0FFFF, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadWord(0x500000, 0x503FFF, NULL, RAM+0x030000);                 // COLOUR RAM
   AddReadWord(0xE00000, 0xE0FFFF, NULL, OBJECT_MAP);                   // OBJECT CHAIN
   AddReadWord(0xD00000, 0xD00FFF, NULL, RAM+0x044000);                 // OBJECT RAM
   AddReadWord(0x000000, 0xFFFFFF, BadReadWord, NULL);			// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x400000, 0x40FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0xB00000, 0xB0FFFF, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteByte(0xA20000, 0xA20003, NULL, RAM_SCROLL+6);                // SCROLL Y
   AddWriteByte(0xA40000, 0xA40003, NULL, RAM_SCROLL+0);                // SCROLL X
   AddWriteByte(0xA50000, 0xA50001, NULL, RAM_SCROLL+14);               // CTRL
   AddWriteByte(0xB20000, 0xB20003, NULL, RAM_SCROLL_2+6);              // SCROLL Y
   AddWriteByte(0xB40000, 0xB40003, NULL, RAM_SCROLL_2+0);              // SCROLL X
   AddWriteByte(0xB50000, 0xB50001, NULL, RAM_SCROLL_2+14);             // CTRL
   AddWriteByte(0x7E0000, 0x7E0003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x400000, 0x40FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0xA00000, 0xA0FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0xB00000, 0xB0FFFF, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteWord(0xD00000, 0xD00FFF, NULL, RAM+0x044000);                // OBJECT RAM
   AddWriteWord(0x500000, 0x503FFF, NULL, RAM+0x030000);                // COLOUR RAM
   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM+0x045000);                // ?
   AddWriteWord(0xE00000, 0xE0FFFF, NULL, OBJECT_MAP);                  // OBJECT CHAIN
   AddWriteWord(0xA20000, 0xA20003, NULL, RAM_SCROLL+6);                // SCROLL Y
   AddWriteWord(0xA40000, 0xA40003, NULL, RAM_SCROLL+0);                // SCROLL X
   AddWriteWord(0xA50000, 0xA50001, NULL, RAM_SCROLL+14);               // CTRL
   AddWriteWord(0xB20000, 0xB20003, NULL, RAM_SCROLL_2+6);              // SCROLL Y
   AddWriteWord(0xB40000, 0xB40003, NULL, RAM_SCROLL_2+0);              // SCROLL X
   AddWriteWord(0xB50000, 0xB50001, NULL, RAM_SCROLL_2+14);             // CTRL
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   AddMemFetchMC68000B(0x000000, 0x01FFFF, ROM+0x0A0000-0x000000);	// 68000 ROM
   AddMemFetchMC68000B(-1, -1, NULL);

   AddReadByteMC68000B(0x000000, 0x01FFFF, NULL, ROM+0x0A0000);		// 68000 ROM
   AddReadByteMC68000B(0x400000, 0x40FFFF, NULL, RAM+0x000000);		// COMMON RAM
   AddReadByteMC68000B(0x880000, 0x880003, tc0220ioc_rb_port, NULL);	// INPUT
   AddReadByteMC68000B(0x000000, 0xFFFFFF, BadReadByte, NULL);		// <Bad Reads>
   AddReadByteMC68000B(-1, -1, NULL, NULL);

   AddReadWordMC68000B(0x000000, 0x01FFFF, NULL, ROM+0x0A0000);		// 68000 ROM
   AddReadWordMC68000B(0x400000, 0x40FFFF, NULL, RAM+0x000000);		// COMMON RAM
   AddReadWordMC68000B(0x880000, 0x880003, tc0220ioc_rw_port, NULL);	// INPUT
   AddReadWordMC68000B(0x000000, 0xFFFFFF, BadReadWord, NULL);		// <Bad Reads>
   AddReadWordMC68000B(-1, -1, NULL, NULL);

   AddWriteByteMC68000B(0x400000, 0x40FFFF, NULL, RAM+0x000000);	// COMMON RAM
   AddWriteByteMC68000B(0x880000, 0x880003, tc0220ioc_wb_port, NULL);	// INPUT
   AddWriteByteMC68000B(0xAA0000, 0xAA0001, Stop68000, NULL);		// Trap Idle 68000
   AddWriteByteMC68000B(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);	// <Bad Writes>
   AddWriteByteMC68000B(-1, -1, NULL, NULL);

   AddWriteWordMC68000B(0x400000, 0x40FFFF, NULL, RAM+0x000000);	// COMMON RAM
   AddWriteWordMC68000B(0x880000, 0x880003, tc0220ioc_ww_port, NULL);	// INPUT
   AddWriteWordMC68000B(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);	// <Bad Writes>
   AddWriteWordMC68000B(-1, -1, NULL, NULL);

   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
}

static void execute_topspeed(void)
{

/*----[Start of Keyboard Support]-----*/

// Wheel Hack

 RAM[0x05501A] = 0x00;
 RAM[0x055018] = 0x00;

//Player presses left on keyboard
 if (RAM[0x05501C]) {
  RAM[0x05501A] = 0xFF;
  RAM[0x055018] = 0x80;
  }

//Player presses right on keyboard
 if (RAM[0x05501D]) {
  RAM[0x05501A] = 0x00;
  RAM[0x055018] = 0x7F;
  }

// Pedals Hack

  RAM[0x055006] &= ~0x80;
  RAM[0x055006] &= ~0x40;
  RAM[0x055006] &= ~0x20;


//Player presses accelerator on keyboard
 if (RAM[0x05501E]) {
  RAM[0x055006] |=  0x80;
  RAM[0x055006] &= ~0x40;
  RAM[0x055006] &= ~0x20;
}


  RAM[0x055004] &= ~0x80;
  RAM[0x055004] &= ~0x40;
  RAM[0x055004] &= ~0x20;


//Player presses brake on keyboard
 if (RAM[0x05501B]) {
  RAM[0x055004] |=  0x80;
  RAM[0x055004] &= ~0x40;
  RAM[0x055004] &= ~0x20;
}

/*----[End of Keyboard Support]-----*/



   tcpu=0;
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));		// M68000 12MHz (60fps)
      print_debug("PC0:%06x SR0:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_0, 6);

   tcpu=1;
   cpu_execute_cycles(CPU_68K_1, CPU_FRAME_MHz(12,60));		// M68000 12MHz (60fps)
      print_debug("PC1:%06x SR1:%04x\n",s68000context.pc,s68000context.sr);
   cpu_interrupt(CPU_68K_1, 5);

   Taito2151_Frame();				// Z80 and YM2151
}

static void render_z_system_sprites(int pri)
{
   int x,y,ta,tb,zz;
   int zx,zy,rx,ry,xx,zzx,zzy;
   UINT8 *map,*SPR_MAP;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
/*
   if(pri!=0)
      pri=0x00;
   else
      pri=0x80;
*/

/*

01: FE00 ZOOM
01: 01FF Y
23: 007F ZOOM
45: 8000 PRIORITY?
45: 4000 FLIP Y
45: 01FF X
67: FF00 COLOUR
67: 00FF TILE

*/

   // OBJECT Z-SYSTEM
   // ---------------

   for(zz=0x447F8;zz>=0x44000;zz-=8){

      //if((RAM[zz+2]&0x80)==pri){

      zx=(RAM[zz+2]>>0)&0x7F;
      zy=(RAM[zz+1]>>1)&0x7F;
      if((zx!=0)&&(zy!=0)){

         ta = ReadWord(&RAM[zz+6])&0x0FF;
         if(ta!=0){

            x=(32+ReadWord(&RAM[zz+4]))&0x1FF;

            //y=(32+ReadWord(&RAM[zz+0])+(0x3F-(zy>>1)))&0x1FF;

            y=(((128-16)+32+7)+(ReadWord(&RAM[zz+0])-zy))&0x1FF;

            MAP_PALETTE_MAPPED_NEW(
               (ReadWord(&RAM[zz+6])>>8)&0xFF,
               16,
               map
            );

            zoom_dat_x = zoom16_ofs+(zx<<3);
            zoom_dat_y = zoom8_ofs+(zy<<4);

            SPR_MAP = OBJECT_MAP + (ta<<8);

            switch(RAM[zz+5]&0x40){
            case 0x00:

            xx=x;

            for(ry=0;ry<16;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            x = (x+zzx)&0x1FF;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            case 0x40:

            x+=(zx+1);
            xx=x;

            for(ry=0;ry<16;ry++){
            zzy = zoom_dat_y[ry];
            if((y>16)&&(y<240+32)){
            ta=0;
            for(rx=0;rx<8;rx++){
            zzx = zoom_dat_x[rx];
            x = (x-zzx)&0x1FF;

            if((x>16)&&(x<320+32)){
               tb=ReadWord(&SPR_MAP[ta])&0x7FFF;
               if(GFX_OBJ_A_SOLID[tb]!=0){			// No pixels; skip
                  if(GFX_OBJ_A_SOLID[tb]==1)			// Some pixels; trans
                     Draw16x8_Trans_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
                  else						// all pixels; solid
                     Draw16x8_Mapped_ZoomXY_FlipY_Rot(&GFX_OBJ_A[tb<<7],x,y,map,zzx,zzy);
               }
            }
            ta+=2;
            }
            }
            y = (y+zzy)&0x1FF;
            SPR_MAP+=16;
            x=xx;
            }

            break;
            }

         }
      }
   //}
   }
}

static void DrawFullThrottle(void)
{
   ClearPaletteMap();

   // Init tc0100scn emulation
   // ------------------------

   tc0100scn_layer_count = 0;
   tc0100scn[0].ctrl = ReadWord(RAM_SCROLL+12);
   tc0100scn[1].ctrl = ReadWord(RAM_SCROLL_2+12);

   // BG0
   // ---

   render_tc0100scn_layer_mapped(1,1,0);

   // BG1
   // ---

   render_tc0100scn_layer_mapped(1,0,1);

   // BG2
   // ---

   render_tc0100scn_layer_mapped(0,1,1);

   // Z-SYSTEM OBJECT
   // ---------------

   //if(check_layer_enabled(obj_id))
      render_z_system_sprites(1);

   // BG3
   // ---

   render_tc0100scn_layer_mapped(0,0,1);
}

/*

FULL THROTTLE - JROM
--------------------

fullthr

-------+------------------------------------
B14-01 | GFX Type A (even planes?)
B14-02 | GFX Type A (odd planes?)
B14-03 | GFX Type B (even planes?)
B14-04 | GFX Type B (odd planes?)
B14-05 |*Main 68k Data Rom
B14-06 |*GFX BG0 (odd)
B14-07 |*GFX BG0 (even)
B14-25 |*SOUND Z80
B14-28 | M5205 ROM
B14-29 | M5205 ROM
B14-30 | GFX ROADSCROLL
B14-31 | ??? with Z80 code ???
B14-67 |*MAIN MC68000 (even)
B14-68 |*MAIN MC68000 (odd)
B14-69 |*SUB MC68000 (even)
B14-71 |*SUB MC68000 (odd)
-------+------------------------------------

TOP SPEED - JH
--------------

topspalt

-----------+------------------------------------
B14-06.ROM | GFX BG0 (odd)
B14-07.ROM | GFX BG0 (even)
B14-23.ROM
B14-24.ROM
B14-25.ROM
B14-26.ROM
B14-28.ROM | M5205 ROM
B14-29.ROM | M5205 ROM
B14-30.ROM | GFX ROADSCROLL
B14-56.ROM
B14-57.ROM
B14-58.ROM
B14-59.ROM
B14-60.ROM
B14-61.ROM
B14-62.ROM
B14-63.ROM
B14-64.ROM
-----------+------------------------------------

TOP SPEED - MALCOR
------------------

topspeed

---------+------------------------------------
B14-06   | GFX BG0 (odd)               [Equal]
B14-07   | GFX BG0 (even)              [Equal]
B14-25   | Sound Z80                   [Equal]
B14-28   | M5205 ROM                   [Equal]
B14-29   | M5205 ROM                   [Equal]
B14-30   | GFX ROADSCROLL              [Equal]
B14-31   | ??? with Z80 code ???       [Equal but size diff]
B14-36   | Gfx#3 (even#0)
B14-37   | Gfx#3 (even#1)
B14-38   | Gfx#3 (odd#0)
B14-39   | Gfx#3 (odd#1)
B14-40   | Gfx#2 (even#0)
B14-41   | Gfx#2 (even#1)
B14-42   | Gfx#2 (odd#0)
B14-43   | Gfx#2 (odd#1)
B14-44   | Gfx#1 (even#0)
B14-45   | Gfx#1 (even#1)
B14-46   | Gfx#1 (odd#0)
B14-47   | Gfx#1 (odd#1)
B14-48   | Gfx#0 (even#0)
B14-49   | Gfx#0 (even#1)
B14-50   | Gfx#0 (odd#0)
B14-51   | Gfx#0 (odd#1)
B14-52   | Main 68k Data Rom (even#0)
B14-53   | Main 68k Data Rom (even#1)
B14-54   | Main 68k Data Rom (odd#0)
B14-55   | Main 68k Data Rom (odd#1)
B14-67-1 | MAIN MC68000 (even)         [Diff]
B14-68-1 | MAIN MC68000 (odd)          [Diff]
B14-69   | SUB MC68000 (even)          [Equal]
B14-70   | SUB MC68000 (odd)           [Small Diff: Rom Switch]
---------+------------------------------------

*/

static struct VIDEO_INFO video_topspeed =
{
   DrawFullThrottle,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL| VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_fullthrl[] =
{
   { "full_throttle", },
   { "fullthr", },
   { "fullthrl", },
   { ROMOF("topspeed"), },
   { CLONEOF("topspeed"), },
   { NULL, },
};
CLNE(fullthrl, topspeed, "Full Throttle", TAITO, 1987, GAME_RACE | GAME_NOT_WORKING,
	.board = "B14",
);
static struct DIR_INFO dir_topspeed[] =
{
   { "top_speed", },
   { "topspeed", },
   { NULL, },
};
GME( topspeed, "Top Speed", TAITO, 1987, GAME_RACE | GAME_NOT_WORKING,
	.board = "B14",
);

