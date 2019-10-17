/******************************************************************************/
/*                                                                            */
/*                 ASHURA BLASTER (C) 1990 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

/*  Ashura Japan & US don't have same dipswitch values cionage is different.
    Corrected some dipswitch settings.  Added the US rom set and coded rom
    names used by Mame 7/22/00   -BaT */

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"
#include "timer.h"

/************************
   ASHURA BLASTER JAPAN
 ************************/


static struct ROM_INFO rom_ashura[] =
{
   {       "c43-03", 0x00080000, 0x426606ba, 0, 0, 0, },
   {       "c43-02", 0x00080000, 0x105722ae, 0, 0, 0, },
   {       "c43-01", 0x00080000, 0xdb953f37, 0, 0, 0, },
   {       "c43-16", 0x00010000, 0xcb26fce1, 0, 0, 0, },
   {   "c4307-1.50", 0x00020000, 0xd5ceb20f, 0, 0, 0, },
   {   "c4305-1.31", 0x00020000, 0xa6f3bb37, 0, 0, 0, },
   {   "c4306-1.49", 0x00020000, 0x0f331802, 0, 0, 0, },
   {   "c4304-1.30", 0x00020000, 0xe06a2414, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_ashura_blaster_0[] =
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

static struct DSW_DATA dsw_data_ashura_blaster_1[] =
{
   { MSG_DIFFICULTY,          0x03, 0x04 },
   { MSG_NORMAL,              0x03},
   { MSG_EASY,                0x02},
   { MSG_HARD,                0x01},
   { MSG_HARDEST,             0x00},
   { MSG_EXTRA_LIFE,          0x0c, 0x04 },
   { _("Every 150k"),            0x0C},
   { _("Every 100k"),            0x08},
   { _("Every 200k"),            0x04},
   { _("Every 250k"),            0x00},
   { MSG_LIVES,               0x30, 0x04 },
   { "3",                     0x30},
   { "4",                     0x20},
   { "2",                     0x10},
   { "1",                     0x00},
   DSW_CONTINUE_PLAY( 0x40, 0x00),
   { MSG_DSWB_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};


static struct DSW_INFO dsw_ashura[] =
{
   { 0x000000, 0xFF, dsw_data_ashura_blaster_0 },
   { 0x000002, 0xFF, dsw_data_ashura_blaster_1 },
   { 0,        0,    NULL,      },
};



/*********************
   ASHURA BLASTER US
 *********************/


static struct ROM_INFO rom_ashurau[] =
{
   {       "c43-03", 0x00080000, 0x426606ba, 0, 0, 0, },
   {       "c43-02", 0x00080000, 0x105722ae, 0, 0, 0, },
   {       "c43-01", 0x00080000, 0xdb953f37, 0, 0, 0, },
   {       "c43-16", 0x00010000, 0xcb26fce1, 0, 0, 0, },
   {       "c43-11", 0x00020000, 0xd5aefc9b, 0, 0, 0, },
   {       "c43-09", 0x00020000, 0xe91d0ab1, 0, 0, 0, },
   {       "c43-10", 0x00020000, 0xc218e7ea, 0, 0, 0, },
   {       "c43-08", 0x00020000, 0x5ef4f19f, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_ashura_blaster_us_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
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

static struct DSW_INFO dsw_ashurau[] =
{
   { 0x000000, 0xFF, dsw_data_ashura_blaster_us_0 },
   { 0x000002, 0xFF, dsw_data_ashura_blaster_1 },
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

static void load_ashura(void)
{
   int ta,tb,tc;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(5,60));

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x200000;

   if(!load_rom_index(0, RAM, 0x80000)) return;
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
   if(!load_rom_index(1, RAM, 0x80000)) return;
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

   Rotate16x16(GFX,0x2000);
   Flip16x16_X(GFX,0x2000);
   Rotate8x8(GFX+0x200000,0x1000);
   Flip8x8_X(GFX+0x200000,0x1000);

   RAMSize=0x40000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(ROM=AllocateMem(0x80000))) return;

   if(!load_rom_index(4, RAM, 0x20000)) return;	// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(5, RAM, 0x20000)) return;	// fixed
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom_index(6, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom_index(7, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/	// Z80 + YM2610 + YM3016 DAC

   Z80ROM=RAM+0x40000;
   if(!load_rom_index(3, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x80000))) return;
   if(!load_rom_index(2,PCMROM,0x80000)) return;		// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x80000, 0x80000);

   AddTaitoYM2610(0x023A, 0x01BA, 0x10000);

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

   // 68000 Speed Hack
   // ----------------

   WriteWord68k(&ROM[0x00502],0x4EF9);
   WriteLong68k(&ROM[0x00504],0x00000300);

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
   tc0180vcu.bmp_w	= 224;
   tc0180vcu.bmp_h	= 320;
   tc0180vcu.scr_x	= 16;
   tc0180vcu.scr_y	= 0;

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
   AddReadByte(0x800000, 0x800003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0xA00000, 0xA0000F, tc0220ioc_rb, NULL);			// INPUT
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

static void execute_ashura(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);
   cpu_interrupt(CPU_68K_0, 4);

   execute_z80_audio_frame();
}

static void DrawAshuraBlaster(void)
{
   ClearPaletteMap();

   // Init tc0180vcu emulation

   tc0180vcu_layer_count = 0;

   // BG0

   vcu_render_bg0_r270();

   // OBJ

   vcu_render_obj_r270(0);

   // BG1

   vcu_render_bg1_r270();

   // OBJ

   vcu_render_obj_r270(1);

   // BG2

   vcu_render_bg2_r270();
}
static struct VIDEO_INFO video_ashurau =
{
   DrawAshuraBlaster,
   224,
   320,
   32,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_ashura[] =
{
   { "ashura_blaster", },
   { "ashura", },
   { NULL, },
};
GAME( ashura, "Ashura Blaster (Japan)", TAITO, 1990, GAME_SHOOT,
	.input = b_system_inputs,
	.dsw = dsw_ashura,
	.video = &video_ashurau,
	.exec = execute_ashura,
	.long_name_jpn = "�寶C羅ブラスター",
	.board = "C43",
	.sound = taito_ym2610_sound,
);
static struct DIR_INFO dir_ashurau[] =
{
   { "ashura_blaster_us", },
   { "ashurau", },
   { ROMOF("ashura"), },
   { CLONEOF("ashura"), },
   { NULL, },
};
#define load_ashurau load_ashura
GAME( ashurau, "Ashura Blaster (US)", TAITO, 1990, GAME_SHOOT,
	.input = b_system_inputs,
	.dsw = dsw_ashurau,
	.video = &video_ashurau,
	.exec = execute_ashura,
	.long_name_jpn = "�寶C羅ブラスター",
	.board = "C43",
	.sound = taito_ym2610_sound,
);

