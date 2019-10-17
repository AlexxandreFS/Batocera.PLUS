#define DRV_DEF_SOUND taito_ym2610_sound
/******************************************************************************/
/*                                                                            */
/*                    SYVALION (C) 1988 TAITO CORPORATION                     */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc004vcu.h"
#include "tc220ioc.h"
#include "sasound.h"		// sample support routines
#include "taitosnd.h"
#include "timer.h"


static struct ROM_INFO rom_syvalion[] =
{
   {   "b51-01.bin", 0x00020000, 0x8dab004a, 0, 0, 0, },
   {   "b51-02.bin", 0x00020000, 0x906ba440, 0, 0, 0, },
   {   "b51-03.bin", 0x00020000, 0x8fd9b299, 0, 0, 0, },
   {   "b51-04.bin", 0x00020000, 0x03aea658, 0, 0, 0, },
   {   "b51-05.bin", 0x00020000, 0x47976ae9, 0, 0, 0, },
   {   "b51-06.bin", 0x00020000, 0x81bef4f0, 0, 0, 0, },
   {   "b51-07.bin", 0x00020000, 0x764d4dc8, 0, 0, 0, },
   {   "b51-08.bin", 0x00020000, 0x9f6a535c, 0, 0, 0, },
   {   "b51-09.bin", 0x00020000, 0xcbb4f33d, 0, 0, 0, },
   {   "b51-10.bin", 0x00020000, 0x6aa97fbc, 0, 0, 0, },
   {   "b51-11.bin", 0x00020000, 0xae9a9ac5, 0, 0, 0, },
   {   "b51-12.bin", 0x00020000, 0x6b36d358, 0, 0, 0, },
   {   "b51-13.bin", 0x00020000, 0xdab28958, 0, 0, 0, },
   {   "b51-14.bin", 0x00020000, 0xdea7216e, 0, 0, 0, },
   {   "b51-15.bin", 0x00020000, 0x30b2ee02, 0, 0, 0, },
   {   "b51-16.bin", 0x00020000, 0xc0fcf7a5, 0, 0, 0, },
   {   "b51-17.bin", 0x00080000, 0xd85096aa, 0, 0, 0, },
   {   "b51-18.bin", 0x00080000, 0x8b23ac83, 0, 0, 0, },
   {   "b51-19.bin", 0x00020000, 0x2abd762c, 0, 0, 0, },
   {   "b51-20.bin", 0x00020000, 0x440b6418, 0, 0, 0, },
   {   "b51-21.bin", 0x00020000, 0xaa111f30, 0, 0, 0, },
   {   "b51-22.bin", 0x00020000, 0xe6c61079, 0, 0, 0, },
   {   "b51-23.bin", 0x00010000, 0x734662de, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_syvalion[] =
{
   INP1( COIN1, 0x032004, 0x04 ),
   INP1( COIN2, 0x032004, 0x08 ),
   INP0( TILT, 0x032004, 0x20 ),
   INP0( SERVICE, 0x032004, 0x10 ),

   INP0( P1_START, 0x032004, 0x40 ),
   INP1( P1_UP, 0x032080, 0xFF ),
   INP1( P1_DOWN, 0x032081, 0xFF ),
   INP1( P1_LEFT, 0x032082, 0xFF ),
   INP1( P1_RIGHT, 0x032083, 0xFF ),
   INP0( P1_B1, 0x032006, 0x10 ),

   INP0( P2_START, 0x032004, 0x80 ),
   INP1( P2_UP, 0x032084, 0xFF ),
   INP1( P2_DOWN, 0x032085, 0xFF ),
   INP1( P2_LEFT, 0x032086, 0xFF ),
   INP1( P2_RIGHT, 0x032087, 0xFF ),
   INP0( P2_B1, 0x032006, 0x01 ),

   END_INPUT
};

static struct DSW_DATA dsw_data_syvalion_0[] =
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

static struct DSW_INFO dsw_syvalion[] =
{
   { 0x032000, 0xFF, dsw_data_syvalion_0 },
   { 0x032002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_syvalion_0[] =
{
   { "Taito",                 0x00 },
   { "Taito Japan",           0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_syvalion[] =
{
   { 0x07FFFF, 0x00, romsw_data_syvalion_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;
static UINT8 *RAM_INPUT;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_FG0;

static void load_syvalion(void)
{
   int ta,tb,tc;

   setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(5,60));

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(ROM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x400000))) return;

   GFX_BG0 = GFX+0x000000;

   if(!load_rom("b51-16.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-15.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=0;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-14.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-13.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=8;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-12.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-11.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=2;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-10.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-09.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=10;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-08.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-07.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=4;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-06.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-05.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=12;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-04.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-03.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=6;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }
   if(!load_rom("b51-02.bin", RAM+0x00000, 0x20000)) return;	// GFX
   if(!load_rom("b51-01.bin", RAM+0x20000, 0x20000)) return;	// GFX
   tb=14;
   for(ta=0;ta<0x40000;ta+=16){
      for(tc=0;tc<16;tc++){
         GFX[tb+(tc<<4)]=RAM[ta+tc]&15;
         GFX[tb+(tc<<4)+1]=RAM[ta+tc]>>4;
      }
      tb+=256;
   }

   if(!load_rom("b51-20.bin", RAM, 0x20000)) return;		// 68000 ROM
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("b51-22.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("b51-19.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40000]=RAM[ta];
   }
   if(!load_rom("b51-21.bin", RAM, 0x20000)) return;
   for(ta=0;ta<0x20000;ta++){
      ROM[ta+ta+0x40001]=RAM[ta];
   }

   RAMSize=0x48000+0x10000;

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x48000;
   if(!load_rom("b51-23.bin", Z80ROM, 0x10000)) return;		// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x100000))) return;
   if(!load_rom("b51-18.bin",PCMROM+0x00000,0x80000)) return;	// ADPCM A rom
   if(!load_rom("b51-17.bin",PCMROM+0x80000,0x80000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM+0x80000, 0x80000, 0x80000);

   AddTaitoYM2610(0x02EE, 0x028D, 0x10000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x40000);

   GFX_FG0   = RAM+0x40000;
   RAM_VIDEO = RAM+0x10000;
   RAM_COLOUR= RAM+0x31000+0x800;
   RAM_INPUT = RAM+0x32000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x4000);

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x8000);

   set_colour_mapper(&col_map_xbbb_bbgg_gggr_rrrr);

   // 68000 Speed Hack
   // ----------------

   WriteLong68k(&ROM[0x072A],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x072E],0x00AA0000);
   WriteWord68k(&ROM[0x0732],0x6100-16);	// bra.s <loop>

   // Init tc0004vcu emulation
   // ------------------------

   tc0004vcu.RAM	= RAM_VIDEO;
   tc0004vcu.GFX_BG0	= GFX_BG0;
   tc0004vcu.GFX_BG0_MSK= GFX_BG0_SOLID;
   tc0004vcu.GFX_FG0	= GFX_FG0;
   tc0004vcu.tile_mask	= 0x3FFF;
   tc0004vcu.bmp_x	= 64;
   tc0004vcu.bmp_y	= 64;
   tc0004vcu.bmp_w	= 512;
   tc0004vcu.bmp_h	= 416;
   tc0004vcu.scr_x	= 0;
   tc0004vcu.scr_y	= 0;

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
   AddReadWord(0x110000, 0x11FFFF, NULL, RAM+0x000000);			// 68000 RAM [MIRROR]
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1, NULL, NULL);

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x410000, 0x410FFF, tc0004vcu_gfx_fg0_b_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x401000, 0x420FFF, NULL, RAM+0x011000);		// SCREEN RAM
   AddWriteByte(0x500000, 0x500FFF, NULL, RAM+0x031000);		// COLOR RAM
   AddWriteByte(0x400000, 0x400FFF, tc0004vcu_gfx_fg0_a_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x200000, 0x200003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByte(0x300000, 0x300003, tc0140syt_write_main_68k, NULL);	// SOUND COMM
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x410000, 0x410FFF, tc0004vcu_gfx_fg0_b_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x401000, 0x420FFF, NULL, RAM+0x011000);		// SCREEN RAM
   AddWriteWord(0x500000, 0x500FFF, NULL, RAM+0x031000);		// COLOR RAM
   AddWriteWord(0x400000, 0x400FFF, tc0004vcu_gfx_fg0_a_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x200000, 0x200003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...

   GameMouse=1;
}

static void execute_syvalion(void)
{
   static int p1x,p1y;

   p1x=0;
   p1y=0;

   /*------[Mouse Hack]-------*/

   //set_mouse_range(0,0,319,239);

   GetMouseMickeys(&p1x,&p1y);

   p1y=0-p1y;

   //p1x=0-(160-mouse_x);
   //p1y=(120-mouse_y);

   //mouse_x=160;
   //mouse_y=120;

   if(*MouseB&1) RAM[0x32006]&=0x10^255;

   if((RAM[0x32080]!=0)&&(p1y<  0x200)) p1y+=0x20;
   if((RAM[0x32081]!=0)&&(p1y> -0x200)) p1y-=0x20;
   if((RAM[0x32082]!=0)&&(p1x> -0x200)) p1x-=0x20;
   if((RAM[0x32083]!=0)&&(p1x<  0x200)) p1x+=0x20;

   RAM[0x3201C] = (p1x>>8)&0xFF;
   RAM[0x3201E] = (p1x>>0)&0xFF;
   RAM[0x32018] = (p1y>>8)&0xFF;
   RAM[0x3201A] = (p1y>>0)&0xFF;

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 2);

   execute_z80_audio_frame();
}

static void DrawSyvalion(void)
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

   tc0004vcu_render_fg0();
}

static struct VIDEO_INFO video_syvalion =
{
   DrawSyvalion,
   512,
   416,
   64,
   VIDEO_ROTATE_NORMAL|VIDEO_NEEDS_8BPP,
};
GMEI( syvalion, "Syvalion", TAITO, 1988, GAME_PLATFORM,
	.romsw = romsw_syvalion,
	.long_name_jpn = "サイバリオン",
	.board = "B51",
);

