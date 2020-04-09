#define DRV_DEF_INPUT b_system_inputs
#define DRV_DEF_SOUND taito_ym2610_sound
#define DRV_DEF_VIDEO &b_system_video
/******************************************************************************/
/*                                                                            */
/*                  CRIME CITY (C) 1990 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"

/**************
   CRIME CITY
 **************/


static struct ROM_INFO rom_crimec[] =
{
   {   "b99_01.19", 0x00080000, 0xa19e373a, 0, 0, 0, },
   {   "b99_02.18", 0x00080000, 0x2a5d4a26, 0, 0, 0, },
   {   "b99_03.37", 0x00080000, 0xdda10df7, 0, 0, 0, },
   {       "b99_05.29", 0x00020000, 0xff7f9a9d, 0, 0, 0, },
   {       "b99_06.39", 0x00020000, 0x1f26aa92, 0, 0, 0, },
   {       "b99_07.40", 0x00020000, 0x26e886e6, 0, 0, 0, },
   {       "b99_08.45", 0x00010000, 0x26135451, 0, 0, 0, },
   {       "b99_14.28", 0x00020000, 0x71c8b4d7, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_crime_city_0[] =
{
   { _("Hiscores"),              0x01, 0x02 },
   { _("Scribble"),              0x01},
   { _("3 characters"),          0x00},
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

static struct DSW_DATA dsw_data_crime_city_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_EASY,                0x03},
   { MSG_NORMAL,              0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "2",                     0x20},
   { "1",                     0x10},
   { "5",                     0x00},
   { MSG_CONTINUE_PLAY,       0xC0, 0x04 },
   { MSG_ON,                  0xC0},
   { _("8 Times"),               0x80},
   { _("5 Times"),               0x40},
   { MSG_OFF,                 0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_crimec[] =
{
   { 0x000000, 0xFF, dsw_data_crime_city_0 },
   { 0x000002, 0xFF, dsw_data_crime_city_1 },
   { 0,        0,    NULL,      },
};

/*
static struct ROMSW_DATA romsw_data_crime_city_0[] =
{
   { "Taito Japan",           0x01 },
   { "Taito America",         0x02 },
   { "Taito (World)",         0x03 },
   { NULL,                    0    },
};
*/

/*
static struct ROMSW_INFO crime_city_romsw[] =
{
   { 0x07FFFF, 0x03, romsw_data_crime_city_0 },
   { 0,        0,    NULL },
};
*/


/*****************
   CRIME CITY US
 *****************/


static struct ROM_INFO rom_crimecu[] =
{
   {   "b99_01.19", 0x00080000, 0xa19e373a, 0, 0, 0, },
   {   "b99_02.18", 0x00080000, 0x2a5d4a26, 0, 0, 0, },
   {   "b99_03.37", 0x00080000, 0xdda10df7, 0, 0, 0, },
   {       "b99_05.29", 0x00020000, 0xff7f9a9d, 0, 0, 0, },
   {       "b99_06.39", 0x00020000, 0x1f26aa92, 0, 0, 0, },
   {       "b99_07.40", 0x00020000, 0x26e886e6, 0, 0, 0, },
   {       "b99_08.45", 0x00010000, 0x26135451, 0, 0, 0, },
   {     "b99_13.28", 0x00020000, 0x06cf8441, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_crime_city_US_0[] =
{
   { _("Hiscores"),              0x01, 0x02 },
   { _("Scribble"),              0x01},
   { _("3 characters"),          0x00},
   DSW_SCREEN( 0x02, 0x00),
   DSW_TEST_MODE( 0x00, 0x04),
   DSW_DEMO_SOUND( 0x08, 0x00),
   { MSG_COIN_SLOTS,          0x30, 0x04 },
   { MSG_1COIN_1PLAY,         0x30},
   { MSG_2COIN_1PLAY,         0x20},
   { MSG_3COIN_1PLAY,         0x10},
   { MSG_4COIN_1PLAY,         0x00},
   { _("Continue cost"),         0xC0, 0x04 },
   { _("Same as play"),          0xC0},
   { _("1 extra coin"),          0x80},
   { _("2 extra coins"),         0x40},
   { _("3 extra coins"),         0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_crimecu[] =
{
   { 0x000000, 0xFF, dsw_data_crime_city_US_0 },
   { 0x000002, 0xFF, dsw_data_crime_city_1 },
   { 0,        0,    NULL,      },
};

/*
static struct ROMSW_INFO crime_city_US_romsw[] =
{
   { 0x07FFFF, 0x02, romsw_data_crime_city_0 },
   { 0,        0,    NULL },
};
*/


/********************
   CRIME CITY JAPAN
 ********************/


static struct ROM_INFO rom_crimecj[] =
{
   {   "b99_01.19", 0x00080000, 0xa19e373a, 0, 0, 0, },
   {   "b99_02.18", 0x00080000, 0x2a5d4a26, 0, 0, 0, },
   {   "b99_03.37", 0x00080000, 0xdda10df7, 0, 0, 0, },
   {       "b99_05.29", 0x00020000, 0xff7f9a9d, 0, 0, 0, },
   {       "b99_06.39", 0x00020000, 0x1f26aa92, 0, 0, 0, },
   {       "b99_07.40", 0x00020000, 0x26e886e6, 0, 0, 0, },
   {       "b99_08.45", 0x00010000, 0x26135451, 0, 0, 0, },
   {           "b99_15.28", 0x00020000, 0xe8c1e56d, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_crime_city_jp_0[] =
{
   { _("Hiscores"),              0x01, 0x02 },
   { _("Scribble"),              0x01},
   { _("3 characters"),          0x00},
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

static struct DSW_INFO dsw_crimecj[] =
{
   { 0x000000, 0xFF, dsw_data_crime_city_jp_0 },
   { 0x000002, 0xFF, dsw_data_crime_city_1 },
   { 0,        0,    NULL,      },
};


static UINT8 *RAM_INPUT;
static UINT8 *RAM_VIDEO;
static UINT8 *RAM_VIDEO_2;
static UINT8 *RAM_COLOUR;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG2;
static UINT8 *GFX_BG2_SOLID;

static void load_crimec(void)
{
   int ta,tb,tc;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x200000;

   if(!load_rom("b99_01.19", RAM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x10000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]=((tc&0x80)>>7)<<0;
      GFX[tb+1]=((tc&0x40)>>6)<<0;
      GFX[tb+2]=((tc&0x20)>>5)<<0;
      GFX[tb+3]=((tc&0x10)>>4)<<0;
      GFX[tb+4]=((tc&0x08)>>3)<<0;
      GFX[tb+5]=((tc&0x04)>>2)<<0;
      GFX[tb+6]=((tc&0x02)>>1)<<0;
      GFX[tb+7]=((tc&0x01)>>0)<<0;
      tc=RAM[ta];
      GFX[tb+0]|=((tc&0x80)>>7)<<1;
      GFX[tb+1]|=((tc&0x40)>>6)<<1;
      GFX[tb+2]|=((tc&0x20)>>5)<<1;
      GFX[tb+3]|=((tc&0x10)>>4)<<1;
      GFX[tb+4]|=((tc&0x08)>>3)<<1;
      GFX[tb+5]|=((tc&0x04)>>2)<<1;
      GFX[tb+6]|=((tc&0x02)>>1)<<1;
      GFX[tb+7]|=((tc&0x01)>>0)<<1;
      tb+=8;
   }
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]=((tc&0x80)>>7)<<0;
      GFX[tb+1]=((tc&0x40)>>6)<<0;
      GFX[tb+2]=((tc&0x20)>>5)<<0;
      GFX[tb+3]=((tc&0x10)>>4)<<0;
      GFX[tb+4]=((tc&0x08)>>3)<<0;
      GFX[tb+5]=((tc&0x04)>>2)<<0;
      GFX[tb+6]=((tc&0x02)>>1)<<0;
      GFX[tb+7]=((tc&0x01)>>0)<<0;
      tc=RAM[ta];
      GFX[tb+0]|=((tc&0x80)>>7)<<1;
      GFX[tb+1]|=((tc&0x40)>>6)<<1;
      GFX[tb+2]|=((tc&0x20)>>5)<<1;
      GFX[tb+3]|=((tc&0x10)>>4)<<1;
      GFX[tb+4]|=((tc&0x08)>>3)<<1;
      GFX[tb+5]|=((tc&0x04)>>2)<<1;
      GFX[tb+6]|=((tc&0x02)>>1)<<1;
      GFX[tb+7]|=((tc&0x01)>>0)<<1;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }
   if(!load_rom("b99_02.18", RAM, 0x80000)) return;
   tb=0x200000;
   for(ta=0;ta<0x10000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]|=((tc&0x80)>>7)<<2;
      GFX[tb+1]|=((tc&0x40)>>6)<<2;
      GFX[tb+2]|=((tc&0x20)>>5)<<2;
      GFX[tb+3]|=((tc&0x10)>>4)<<2;
      GFX[tb+4]|=((tc&0x08)>>3)<<2;
      GFX[tb+5]|=((tc&0x04)>>2)<<2;
      GFX[tb+6]|=((tc&0x02)>>1)<<2;
      GFX[tb+7]|=((tc&0x01)>>0)<<2;
      tc=RAM[ta];
      GFX[tb+0]|=((tc&0x80)>>7)<<3;
      GFX[tb+1]|=((tc&0x40)>>6)<<3;
      GFX[tb+2]|=((tc&0x20)>>5)<<3;
      GFX[tb+3]|=((tc&0x10)>>4)<<3;
      GFX[tb+4]|=((tc&0x08)>>3)<<3;
      GFX[tb+5]|=((tc&0x04)>>2)<<3;
      GFX[tb+6]|=((tc&0x02)>>1)<<3;
      GFX[tb+7]|=((tc&0x01)>>0)<<3;
      tb+=8;
   }
   tb=0;
   for(ta=0;ta<0x80000;ta+=2){
      tc=RAM[ta+1];
      GFX[tb+0]|=((tc&0x80)>>7)<<2;
      GFX[tb+1]|=((tc&0x40)>>6)<<2;
      GFX[tb+2]|=((tc&0x20)>>5)<<2;
      GFX[tb+3]|=((tc&0x10)>>4)<<2;
      GFX[tb+4]|=((tc&0x08)>>3)<<2;
      GFX[tb+5]|=((tc&0x04)>>2)<<2;
      GFX[tb+6]|=((tc&0x02)>>1)<<2;
      GFX[tb+7]|=((tc&0x01)>>0)<<2;
      tc=RAM[ta];
      GFX[tb+0]|=((tc&0x80)>>7)<<3;
      GFX[tb+1]|=((tc&0x40)>>6)<<3;
      GFX[tb+2]|=((tc&0x20)>>5)<<3;
      GFX[tb+3]|=((tc&0x10)>>4)<<3;
      GFX[tb+4]|=((tc&0x08)>>3)<<3;
      GFX[tb+5]|=((tc&0x04)>>2)<<3;
      GFX[tb+6]|=((tc&0x02)>>1)<<3;
      GFX[tb+7]|=((tc&0x01)>>0)<<3;
      tb+=16;
      if((tb&0x7F)==0){tb-=0x78;}
      else{if((tb&0x7F)==8){tb-=0x08;}}
   }

   FreeMem(RAM);

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom("b99_07.40", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("b99_05.29", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("b99_06.39", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom_index(7, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom("b99_08.45", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom("b99_03.37",PCMROM,0x80000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x080000, 0x080000);

   AddTaitoYM2610(0x01E6, 0x0185, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_INPUT  = RAM+0x26000;
   RAM_VIDEO  = RAM+0x10000;
   RAM_COLOUR = RAM+0x24000;
   RAM_VIDEO_2= RAM+0x26100;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   ROM[0x48BA]=0x4E;		// 68000 ROM CHECKSUM
   ROM[0x48BB]=0x71;

   ROM[0x063A]=0x4E;		// jsr $300
   ROM[0x063B]=0xB9;
   ROM[0x063C]=0x00;
   ROM[0x063D]=0x00;
   ROM[0x063E]=0x03;
   ROM[0x063F]=0x00;

   ROM[0x0300]=0x13;		// move.b #$00,$AA0000
   ROM[0x0301]=0xFC;		// (Speed Hack)
   ROM[0x0302]=0x00;
   ROM[0x0303]=0x00;
   ROM[0x0304]=0x00;
   ROM[0x0305]=0xAA;
   ROM[0x0306]=0x00;
   ROM[0x0307]=0x00;

   ROM[0x0308]=0x4E;
   ROM[0x0309]=0x75;

   ROM[0x075C]=0x13;		// move.b #$00,$AA0000
   ROM[0x075D]=0xFC;		// (Speed Hack)
   ROM[0x075E]=0x00;
   ROM[0x075F]=0x00;
   ROM[0x0760]=0x00;
   ROM[0x0761]=0xAA;
   ROM[0x0762]=0x00;
   ROM[0x0763]=0x00;

   ROM[0x0764]=0x60;		// Loop
   ROM[0x0765]=0x100-24;

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO_2;
   tc0180vcu.GFX_BG0	= GFX_BG0;
   tc0180vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0180vcu.GFX_BG2	= GFX_BG2;
   tc0180vcu.GFX_BG2_MSK= GFX_BG2_SOLID;
   tc0180vcu.tile_mask	= 0x1FFF;
   tc0180vcu.bmp_x	= 32;
   tc0180vcu.bmp_y	= 32;
   tc0180vcu.bmp_w	= 320;
   tc0180vcu.bmp_h	= 224;
   tc0180vcu.scr_x	= 0;
   tc0180vcu.scr_y	= 16;

   vcu_make_col_bankmap(0x40,0x00,0x40,0x80,0xC0);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x2C000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0xA00000, 0xA0FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x200000, 0x20000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x800000, 0x801FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadByte(0x600000, 0x600003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0xA00000, 0xA0FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x800000, 0x801FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadWord(0x200000, 0x20000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0xA00000, 0xA0FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x800000, 0x801FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x600000, 0x600003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0x200000, 0x20000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0xA00000, 0xA0FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x800000, 0x801FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteWord(0x200000, 0x20000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_crimec(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)

   Taito2610_Frame();			// Z80 and YM2610
}
static struct DIR_INFO dir_crimec[] =
{
   { "crime_city", },
   { "crimec", },
   { NULL, },
};
GAME( crimec, "Crime City", TAITO, 1989, GAME_SHOOT,
	.dsw = dsw_crimec,
	.exec = execute_crimec,
	.long_name_jpn = "‚N‚Î‚C‚«‚V‚e‚B",
	.board = "B99",
);
static struct DIR_INFO dir_crimecu[] =
{
   { "crime_city_US",   },
   { "crimecu",         },
   { ROMOF("crimec"),   },
   { CLONEOF("crimec"), },
   { NULL, },
};
CLNE( crimecu,crimec, "Crime City (US)", TAITO, 1989, GAME_SHOOT,
	.dsw = dsw_crimecu,
	.long_name_jpn = "‚N‚Î‚C‚«‚V‚e‚B (US)",
	.board = "B99",
);
static struct DIR_INFO dir_crimecj[] =
{
   { "crime_city_jp",   },
   { "crimecj",         },
   { ROMOF("crimec"),   },
   { CLONEOF("crimec"), },
   { NULL, },
};
CLNE( crimecj, crimec, "Crime City (Japan)", TAITO, 1989, GAME_SHOOT,
	.dsw = dsw_crimecj,
	.long_name_jpn = "‚N‚Î‚C‚«‚V‚e‚B (Japan)",
	.board = "B99",
);

