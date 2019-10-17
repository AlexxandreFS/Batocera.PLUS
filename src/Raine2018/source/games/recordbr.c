#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                 RECORD BREAKER (C) 1988 TAITO CORPORATION                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc004vcu.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines


static struct ROM_INFO rom_recordb2[] =
{
   {   "b56-01.rom", 0x00020000, 0x766b7260, 0, 0, 0, },
   {   "b56-02.rom", 0x00020000, 0xc9566226, 0, 0, 0, },
   {   "b56-03.rom", 0x00020000, 0xdafb6836, 0, 0, 0, },
   {   "b56-04.rom", 0x00020000, 0xdeee08fd, 0, 0, 0, },
   {   "b56-05.rom", 0x00020000, 0xed390378, 0, 0, 0, },
   {   "b56-06.rom", 0x00020000, 0x51f70ab0, 0, 0, 0, },
   {   "b56-07.rom", 0x00020000, 0x82c2856f, 0, 0, 0, },
   {   "b56-08.rom", 0x00020000, 0x0f5383b5, 0, 0, 0, },
   {   "b56-09.bin", 0x00080000, 0x7fd9ee68, 0, 0, 0, },
   {   "b56-10.bin", 0x00080000, 0xde1bce59, 0, 0, 0, },
   {   "b56-15.rom", 0x00020000, 0xb346e282, 0, 0, 0, },
   {   "b56-16.rom", 0x00020000, 0xb447f12c, 0, 0, 0, },
   {   "b56-17.rom", 0x00020000, 0x3e0a9c35, 0, 0, 0, },
   {   "b56-19.rom", 0x00010000, 0xc68085ee, 0, 0, 0, },
   {   "b56-21.rom", 0x00020000, 0xe5f63790, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_recordbr[] =
{
   INP1( COIN1, 0x032004, 0x04 ),
   INP1( COIN2, 0x032004, 0x08 ),
   INP0( TILT, 0x032004, 0x20 ),
   INP0( SERVICE, 0x032004, 0x10 ),

   INP0( P1_START, 0x032006, 0x01 ),
   INP0( P1_UP, 0x03200E, 0x01 ),
   INP0( P1_DOWN, 0x03200E, 0x02 ),
   INP0( P1_B1, 0x03200E, 0x04 ),
   INP0( P1_B2, 0x03200E, 0x08 ),

   INP0( P2_START, 0x032006, 0x02 ),
   INP0( P2_UP, 0x03200E, 0x10 ),
   INP0( P2_DOWN, 0x03200E, 0x20 ),
   INP0( P2_B1, 0x03200E, 0x40 ),
   INP0( P2_B2, 0x03200E, 0x80 ),

   INP0( P3_START, 0x032006, 0x04 ),

   INP0( P4_START, 0x032006, 0x08 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_record_breaker_0[] =
{
   { MSG_DSWA_BIT1,           0x01, 0x02 },
   { MSG_OFF,                 0x01},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT2,           0x02, 0x02 },
   { MSG_OFF,                 0x02},
   { MSG_ON,                  0x00},
   { MSG_TEST_MODE,           0x04, 0x02 },
   { MSG_OFF,                 0x04},
   { MSG_ON,                  0x00},
   { MSG_DEMO_SOUND,          0x08, 0x02 },
   { MSG_ON,                  0x08},
   { MSG_OFF,                 0x00},
   { MSG_DSWA_BIT5,           0x10, 0x02 },
   { MSG_OFF,                 0x10},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT6,           0x20, 0x02 },
   { MSG_OFF,                 0x20},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT7,           0x40, 0x02 },
   { MSG_OFF,                 0x40},
   { MSG_ON,                  0x00},
   { MSG_DSWA_BIT8,           0x80, 0x02 },
   { MSG_OFF,                 0x80},
   { MSG_ON,                  0x00},
   { NULL,                    0,   },
};

static struct DSW_INFO dsw_recordbr[] =
{
   { 0x032000, 0xFF, dsw_data_record_breaker_0 },
   { 0x032002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_record_breaker_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_recordbr[] =
{
   { 0x07FFFF, 0x03, romsw_data_record_breaker_0 },
   { 0,        0,    NULL },
};




static struct ROM_INFO rom_recordbr[] =
{
   {   "b56-01.rom", 0x00020000, 0x766b7260, 0, 0, 0, },
   {       "b56-02", 0x00020000, 0x68c604ec, 0, 0, 0, },
   {       "b56-03", 0x00020000, 0x4045fd44, 0, 0, 0, },
   {       "b56-04", 0x00020000, 0xf7afdff0, 0, 0, 0, },
   {   "b56-05.rom", 0x00020000, 0xed390378, 0, 0, 0, },
   {       "b56-06", 0x00020000, 0x5fbcd302, 0, 0, 0, },
   {       "b56-07", 0x00020000, 0x0c76e4c8, 0, 0, 0, },
   {       "b56-08", 0x00020000, 0xc9f0d38a, 0, 0, 0, },
   {   "b56-09.bin", 0x00080000, 0x7fd9ee68, 0, 0, 0, },
   {   "b56-10.bin", 0x00080000, 0xde1bce59, 0, 0, 0, },
   {   "b56-15.rom", 0x00020000, 0xb346e282, 0, 0, 0, },
   {   "b56-16.rom", 0x00020000, 0xb447f12c, 0, 0, 0, },
   {   "b56-17.rom", 0x00020000, 0x3e0a9c35, 0, 0, 0, },
   {   "b56-19.rom", 0x00010000, 0xc68085ee, 0, 0, 0, },
   {   "b56-21.rom", 0x00020000, 0xe5f63790, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};


static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_FG0;

static void load_recordbr(void)
{
   int ta,tb,tc;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x200000))) return;

   GFX_BG0 = GFX+0x000000;

   if(!load_rom_index(3, RAM+0x00000, 0x20000)) return;	// GFX
   tb=0;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(7, RAM+0x00000, 0x20000)) return;	// GFX
   tb=2;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(2, RAM+0x00000, 0x20000)) return;	// GFX
   tb=4;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(6, RAM+0x00000, 0x20000)) return;	// GFX
   tb=6;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(1, RAM+0x00000, 0x20000)) return;	// GFX
   tb=8;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(5, RAM+0x00000, 0x20000)) return;	// GFX
   tb=10;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(0, RAM+0x00000, 0x20000)) return;	// GFX
   tb=12;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom_index(4, RAM+0x00000, 0x20000)) return;	// GFX
   tb=14;
   for(ta=0;ta<0x20000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }

   if(!load_rom_index(12, RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom_index(11, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom_index(10, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom_index(14, RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   RAMSize=0x48000+0x10000;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x48000;
   if(!load_rom_index(13, Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom_index(8,PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom_index(9,PCMROM+0x80000,0x80000)) return;	// ADPCM B rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x02EE, 0x028D, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   GFX_FG0   = RAM+0x40000;
   RAM_VIDEO = RAM+0x10000;
   RAM_COLOUR= RAM+0x31000+0x800;
   RAM_INPUT = RAM+0x32000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x8000);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // Fix 68000 Checksum
   // ------------------

   WriteWord68k(&ROM[0x3FEE],0x4E71);	// nop

   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x071E],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0722],0x00AA0000);
   WriteWord68k(&ROM[0x0726],0x6100-16);	// bra.s <loop>

   // Init tc0004vcu emulation
   // ------------------------

   tc0004vcu.RAM	= RAM_VIDEO;
   tc0004vcu.GFX_BG0	= GFX_BG0;
   tc0004vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0004vcu.GFX_FG0	= GFX_FG0;
   tc0004vcu.tile_mask	= 0x1FFF;
   tc0004vcu.bmp_x	= 64;
   tc0004vcu.bmp_y	= 64;
   tc0004vcu.bmp_w	= 320;
   tc0004vcu.bmp_h	= 240;
   tc0004vcu.scr_x	= 16-1;
   tc0004vcu.scr_y	= 32-1;

   tc0004vcu_init();

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = RAM_INPUT;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x40000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x420FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadByte(0x500000, 0x500FFF, NULL, RAM+0x031000);			// COLOR RAM
   AddReadByte(0x200000, 0x200003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByte(0x300000, 0x300003, tc0140syt_read_main_68k, NULL);	// SOUND COMM
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x420FFF, NULL, RAM+0x010000);			// SCREEN RAM
   AddReadWord(0x500000, 0x500FFF, NULL, RAM+0x031000);			// COLOR RAM
   AddReadWord(0x200000, 0x200003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x420FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteByte(0x500000, 0x500FFF, NULL, RAM+0x031000);		// COLOR RAM
   AddWriteByte(0x200000, 0x200003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByte(0x300000, 0x300003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x420FFF, NULL, RAM+0x010000);		// SCREEN RAM
   AddWriteWord(0x500000, 0x500FFF, NULL, RAM+0x031000);		// COLOR RAM
   AddWriteWord(0x200000, 0x200003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_recordbr(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);

   Taito2610_Frame();			// Z80 and YM2610
}

static void DrawRecordBr(void)
{
   ClearPaletteMap();

   // Init tc0180vcu emulation
   // ------------------------

   tc0004vcu_layer_count = 0;

   // BG0
   // ---

   tc0004vcu_render_bg0();

   // BG1
   // ---

   tc0004vcu_render_bg1();

   // OBJECT
   // ------

   tc0004vcu_render_obj();

   // FG0
   // ---

   //tc0004vcu_render_fg0();
}
static struct VIDEO_INFO video_recordbr =
{
   DrawRecordBr,
   320,
   240,
   64,
   VIDEO_ROTATE_NORMAL,
};
static struct DIR_INFO dir_recordb2[] =
{
   { "record_breaker", },
   { "recordb2", },
   { ROMOF("recordbr"), },
   { CLONEOF("recordbr"), },
   { NULL, },
};
CLNE( recordb2,recordbr, "Record Breaker (Alternate)", TAITO, 1988, GAME_SPORTS | GAME_NOT_WORKING,
	.romsw = romsw_recordbr,
	.board = "B56",
);
static struct DIR_INFO dir_recordbr[] =
{
   { "record_breaker_alternate", },
   { "record_breaker_alt", },
   { "recbralt", },
   { "recordbr", },
   { NULL, },
};
GME( recordbr, "Record Breaker", TAITO, 1988, GAME_SPORTS | GAME_NOT_WORKING,
	.romsw = romsw_recordbr,
	.board = "B56",
);

