#define DRV_DEF_SOUND taito_ym2610_sound
#define DRV_DEF_INPUT b_system_inputs
#define DRV_DEF_VIDEO &b_system_video
/******************************************************************************/
/*                                                                            */
/*            RASTAN 2/NASTAR WARRIOR (C) 1988 TAITO CORPORATION              */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "timer.h"

/**********
   NASTAR
 **********/


static struct ROM_INFO rom_nastar[] =
{
   {   "b81-01.bin", 0x00080000, 0xb33f796b, 0, 0, 0, },
   {   "b81-02.bin", 0x00080000, 0x20ec3b86, 0, 0, 0, },
   {   "b81-03.bin", 0x00080000, 0x551b75e6, 0, 0, 0, },
   {   "b81-04.bin", 0x00080000, 0xcf734e12, 0, 0, 0, },
   {   "b81-13.bin", 0x00020000, 0x60d176fb, 0, 0, 0, },
   {   "b81-08.50", 0x00020000, 0xd6da9169, 0, 0, 0, },
   {   "b81-09.30", 0x00020000, 0x630d34af, 0, 0, 0, },
   {   "b81-10.49", 0x00020000, 0x53f34344, 0, 0, 0, },
   {   "b81-11.bin", 0x00010000, 0x3704bf09, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_nastar_0[] =
{
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

static struct DSW_DATA dsw_data_nastar_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { _("Extra Life"),            0x0C, 0x04 },
   { _("100k only"),             0x0C},
   { _("150k only"),             0x08},
   { _("200k only"),             0x04},
   { _("250k only"),             0x00},
   { _("Lives"),                 0x30, 0x04 },
   { "3",                     0x30},
   { "1",                     0x20},
   { "2",                     0x10},
   { "5",                     0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_nastar[] =
{
   { 0x000000, 0xFF, dsw_data_nastar_0 },
   { 0x000002, 0xFF, dsw_data_nastar_1 },
   { 0,        0,    NULL,      },
};

/*
static struct ROMSW_DATA romsw_data_nastar_0[] =
{
   { "Taito Japan (Rastan Saga 2)",    0x00 },
   { "Taito America (Nastar Warrior)", 0x01 },
   { "Taito Japan (World) (Nastar)",   0x02 },
   { NULL,                             0    },
};

static struct ROMSW_INFO nastar_romsw[] =
{
   { 0x03FFFF, 0x02, romsw_data_nastar_0 },
   { 0,        0,    NULL },
};
*/


/*****************
   RASTAN SAGA 2
 *****************/


static struct ROM_INFO rom_rastsag2[] =
{
   {   "b81-01.bin", 0x00080000, 0xb33f796b, 0, 0, 0, },
   {   "b81-02.bin", 0x00080000, 0x20ec3b86, 0, 0, 0, },
   {   "b81-03.bin", 0x00080000, 0x551b75e6, 0, 0, 0, },
   {   "b81-04.bin", 0x00080000, 0xcf734e12, 0, 0, 0, },
   {   "b81-07.bin", 0x00020000, 0x8edf17d7, 0, 0, 0, },
   {   "b81-08.50", 0x00020000, 0xd6da9169, 0, 0, 0, },
   {   "b81-09.30", 0x00020000, 0x630d34af, 0, 0, 0, },
   {   "b81-10.49", 0x00020000, 0x53f34344, 0, 0, 0, },
   {   "b81-11.bin", 0x00010000, 0x3704bf09, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_rastan_saga_2_0[] =
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

static struct DSW_INFO dsw_rastsag2[] =
{
   { 0x000000, 0xFF, dsw_data_rastan_saga_2_0 },
   { 0x000002, 0xFF, dsw_data_nastar_1 },
   { 0,        0,    NULL,      },
};


/******************
   NASTAR WARRIOR
 ******************/


static struct ROM_INFO rom_nastarw[] =
{
   {   "b81-01.bin", 0x00080000, 0xb33f796b, 0, 0, 0, },
   {   "b81-02.bin", 0x00080000, 0x20ec3b86, 0, 0, 0, },
   {   "b81-03.bin", 0x00080000, 0x551b75e6, 0, 0, 0, },
   {   "b81-04.bin", 0x00080000, 0xcf734e12, 0, 0, 0, },
   {    "b81-12.31", 0x00020000, 0xf9d82741, 0, 0, 0, },
   {   "b81-08.50", 0x00020000, 0xd6da9169, 0, 0, 0, },
   {   "b81-09.30", 0x00020000, 0x630d34af, 0, 0, 0, },
   {   "b81-10.49", 0x00020000, 0x53f34344, 0, 0, 0, },
   {   "b81-11.bin", 0x00010000, 0x3704bf09, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_nastar_warrior_0[] =
{
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

static struct DSW_INFO dsw_nastarw[] =
{
   { 0x000000, 0xFF, dsw_data_nastar_warrior_0 },
   { 0x000002, 0xFF, dsw_data_nastar_1 },
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

static void load_nastar(void)
{
   int ta,tb,tc;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(5,60));

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x200000;

   if(!load_rom_index(3, RAM, 0x80000)) return;
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
   if(!load_rom_index(2, RAM, 0x80000)) return;
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

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom_index(5, RAM+0x00000, 0x20000)) return;	// 68000 ROM
   if(!load_rom_index(7, RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(4, RAM+0x00000, 0x20000)) return;
   if(!load_rom_index(6, RAM+0x20000, 0x20000)) return;
   for(ta=0;ta<0x40000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x40000;
   if(!load_rom_index(8, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom_index(0, PCMROM+0x00000, 0x80000)) return;	// ADPCM A rom
   if(!load_rom_index(1, PCMROM+0x80000, 0x80000)) return;	// ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x02EE, 0x028D, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   RAM_INPUT  = RAM+0x1E000;
   RAM_VIDEO  = RAM+0x08000;
   RAM_COLOUR = RAM+0x1C000;
   RAM_VIDEO_2= RAM+0x1E100;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x100, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   // Fix 68000 ROM Checksum
   // ----------------------

   ROM[0x00BF6]=0x60;

   // Fix 68000 Ints
   // --------------

   WriteWord68k(&ROM[0x005DA],0x4E71);
   WriteWord68k(&ROM[0x005FA],0x4E71);

   // Fix Sound Error
   // ---------------

   ROM[0x02DFA]=0x60;
   WriteWord68k(&ROM[0x02DD4],0x4E71);		// Response Timeout
   WriteWord68k(&ROM[0x02E2E],0x4E71);		// Response Timeout

   WriteWord68k(&ROM[0x00CEE],0x4E71);
   WriteWord68k(&ROM[0x00D06],0x4E71);
   WriteWord68k(&ROM[0x00D0C],0x4E71);
   ROM[0x00D1E]=0x60;

   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x0059E],0x4EF9);
   WriteLong68k(&ROM[0x005A0],0x00000300);

   WriteLong68k(&ROM[0x00300],0x13FC0000);
   WriteLong68k(&ROM[0x00304],0x00AA0000);
   WriteWord68k(&ROM[0x00308],0x6100-10);

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

   vcu_make_col_bankmap(0x40,0xC0,0x80,0x40,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x600000, 0x607FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadByte(0xA00000, 0xA0000F, tc0220ioc_rb, NULL);			// INPUT
   AddReadByte(0x800000, 0x800003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x600000, 0x607FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddReadWord(0xA00000, 0xA0000F, tc0220ioc_rw, NULL);			// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x600000, 0x607FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteByte(0x800000, 0x800003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xA00000, 0xA0000F, tc0220ioc_wb, NULL);		// INPUT
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x600000, 0x607FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x413FFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x200000, 0x201FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x418000, 0x41801F, NULL, RAM_VIDEO_2);			// SCREEN RAM
   AddWriteWord(0xA00000, 0xA0000F, tc0220ioc_ww, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_nastar(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 4);
   cpu_interrupt(CPU_68K_0, 2);

   execute_z80_audio_frame();
}
GMEI( nastar, "Nastar", TAITO, 1989, GAME_BEAT | GAME_PLATFORM,
	.long_name_jpn = "‚Î‚X‚^‚Ù‚T¸[‚KÈQ",
	.board = "B81",
);
static struct DIR_INFO dir_nastarw[] =
{
   { "nastar_warrior", },
   { "nastarw", },
   { ROMOF("nastar"), },
   { CLONEOF("nastar"), },
   { NULL, },
};
CLNE( nastarw,nastar, "Nastar Warrior", TAITO, 1989, GAME_BEAT | GAME_PLATFORM,
	.dsw = dsw_nastarw,
	.long_name_jpn = "ÉâÉXÉ^ÉìÉTÅ[ÉKÇQ",
	.board = "B81",
);
static struct DIR_INFO dir_rastsag2[] =
{
   { "rastan_saga_2", },
   { "rastan2", },
   { "rastsag2", },
   { ROMOF("nastar"), },
   { CLONEOF("nastar"), },
   { NULL, },
};
CLNE( rastsag2,nastar, "Rastan Saga 2", TAITO, 1988, GAME_PLATFORM | GAME_BEAT,
	.dsw = dsw_rastsag2,
	.long_name_jpn = "‚Î‚X‚^‚Ù‚T¸[‚KÈQ",
	.board = "B81",
);

