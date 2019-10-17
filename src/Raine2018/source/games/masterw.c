/******************************************************************************/
/*                                                                            */
/*                 MASTER OF WEAPONS (C) 1989 TAITO CORPORATION               */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "tc220ioc.h"
#include "taitosnd.h"


static struct ROM_INFO rom_masterw[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00020000,
              "b72-06.rom",  0xae848eff,   "b72-12.rom",  0x7176ce70),
  LOAD8_16(  REGION_ROM1,  0x040000,  0x00020000,
              "b72-04.rom",  0x141e964c,   "b72-03.rom",  0xf4523496),
   {   "b72-07.rom", 0x00010000, 0x2b1a946f, 0, 0, 0, },
   {  "mow-m01.rom", 0x00080000, 0xa24ac26e, 0, 0, 0, },
   {  "mow-m02.rom", 0x00080000, 0xc519f65a, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct DSW_DATA dsw_data_master_of_weapons_0[] =
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

static struct DSW_INFO dsw_masterw[] =
{
   { 0x000000, 0xFF, dsw_data_master_of_weapons_0 },
   { 0x000002, 0xFF, dsw_data_default_1 },
   { 0,        0,    NULL,      },
};

static struct ROMSW_DATA romsw_data_master_of_weapons_0[] =
{
   { "Taito Japan (Notice)",  0x01 },
   { "Taito America",         0x02 },
   { "Taito Japan",           0x03 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_masterw[] =
{
   { 0x03FFFF, 0x03, romsw_data_master_of_weapons_0 },
   { 0,        0,    NULL },
};



static UINT8 *RAM_INPUT;
static UINT8 *RAM_VIDEO;
static UINT8 *RAM_COLOUR;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_BG2;
static UINT8 *GFX_BG2_SOLID;

static void load_masterw(void)
{
   int ta,tb,tc;

   RAMSize=0x38000;

   if(!(RAM=AllocateMem(0x80000))) return;
   if(!(GFX=AllocateMem(0x240000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_BG2 = GFX+0x200000;

   if(!load_rom("mow-m01.rom", RAM, 0x80000)) return;
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

   if(!load_rom("mow-m02.rom", RAM, 0x80000)) return;
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

   Rotate16x16(GFX_BG0,0x2000);
   Flip16x16_X(GFX_BG0,0x2000);
   Rotate8x8  (GFX_BG2,0x1000);
   Flip8x8_X  (GFX_BG2,0x1000);

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x28000;
   if(!load_rom("b72-07.rom", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   AddTaitoYM2203(0x02CB, 0x025C, 0x10000, NULL, 0x00000);

   /*-----------------------*/

   memset(RAM+0x00000,0x00,0x28000);

   RAM_INPUT  = RAM+0x25100;
   RAM_VIDEO  = RAM+0x04000;
   RAM_COLOUR = RAM+0x24000;

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x2000);
   GFX_BG2_SOLID = make_solid_mask_8x8  (GFX_BG2, 0x1000);

   InitPaletteMap(RAM_COLOUR, 0x40, 0x10, 0x1000);

   set_colour_mapper(&col_map_rrrr_gggg_bbbb_xxxx);

   WriteLong68k(&ROM[0x0742],0x13FC0000);	// move.b #$00,$AA0000
   WriteLong68k(&ROM[0x0746],0x00AA0000);
   WriteWord68k(&ROM[0x074A],0x4E71);		// nop

   // Init tc0220ioc emulation
   // ------------------------

   tc0220ioc.RAM  = input_buffer;
   tc0220ioc.ctrl = 0;		//TC0220_STOPCPU;
   reset_tc0220ioc();

   // Init tc0180vcu emulation
   // ------------------------

   tc0180vcu.RAM	= RAM_VIDEO;
   tc0180vcu.RAM_2	= RAM_VIDEO+0x18000;
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

   vcu_make_col_bankmap(0x10,0x30,0x20,0x10,0x00);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x25000);

   AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);	// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadByte(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadByte(0x200000, 0x203FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadByte(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadByte(0x600000, 0x600FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadByte(0x800000, 0x800003, tc0220ioc_rb_port, NULL);		// INPUT
   AddReadByte(0xA00000, 0xA00003, tc0140syt_read_main_68k, NULL);	// SOUND
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x000000, 0x07FFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddReadWord(0x200000, 0x203FFF, NULL, RAM+0x000000);			// 68000 RAM
   AddReadWord(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddReadWord(0x600000, 0x600FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddReadWord(0x800000, 0x800003, tc0220ioc_rw_port, NULL);		// INPUT
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x200000, 0x203FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteByte(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteByte(0x600000, 0x600FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteByte(0x800000, 0x800003, tc0220ioc_wb_port, NULL);		// INPUT
   AddWriteByte(0xA00000, 0xA00003, tc0140syt_write_main_68k, NULL);	// SOUND
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x200000, 0x203FFF, NULL, RAM+0x000000);		// 68000 RAM
   AddWriteWord(0x400000, 0x41FFFF, NULL, RAM_VIDEO);			// SCREEN RAM
   AddWriteWord(0x600000, 0x600FFF, NULL, RAM_COLOUR);			// COLOR RAM
   AddWriteWord(0x800000, 0x800003, tc0220ioc_ww_port, NULL);		// INPUT
   AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void ClearMasterW(void)
{
   RemoveTaitoYM2203();
}

static void execute_masterw(void)
{
   #ifdef RAINE_DEBUG
   vcu_debug_info();
   #endif

   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(12,60));	// M68000 12MHz (60fps)
   cpu_interrupt(CPU_68K_0, 5);
   cpu_interrupt(CPU_68K_0, 4);

   Taito2203_Frame();
}

static void DrawMasterW(void)
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



static struct VIDEO_INFO video_masterw =
{
   DrawMasterW,
   224,
   320,
   32,
   VIDEO_ROTATE_NORMAL | VIDEO_NEEDS_8BPP,
};
static struct DIR_INFO dir_masterw[] =
{
   { "master_of_weapons", },
   { "masterw", },
   { NULL, },
};
GAME( masterw, "Master of Weapons", TAITO, 1989, GAME_SHOOT,
	.input = b_system_inputs,
	.dsw = dsw_masterw,
	.romsw = romsw_masterw,
	.clear = ClearMasterW,
	.video = &video_masterw,
	.exec = execute_masterw,
	.long_name_jpn = "マスターオブウェポン",
	.board = "B72",
	.sound = taito_ym2203_sound,
);

