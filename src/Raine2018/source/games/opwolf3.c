#define DRV_DEF_SOUND taito_ym2610_sound
#define DRV_DEF_DSW NULL
/******************************************************************************/
/*                                                                            */
/*                 OPERATION WOLF 3 (C) 1994 TAITO CORPORATION                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "taitosnd.h"
#include "f3system.h"
#include "tc006vcu.h"
#include "tc200obj.h"
#include "sasound.h"		// sample support routines
#ifdef SDL
#include "sdl/control_internal.h"
#endif


static struct ROM_INFO rom_opwolf3[] =
{
   {  "opw3_01.rom", 0x00200000, 0x115313e0, 0, 0, 0, },
   {  "opw3_02.rom", 0x00200000, 0xaab86332, 0, 0, 0, },
   {  "opw3_03.rom", 0x00200000, 0x3f398916, 0, 0, 0, },
   {  "opw3_04.rom", 0x00200000, 0x2f385638, 0, 0, 0, },
   {  "opw3_05.rom", 0x00200000, 0x85ea64cc, 0, 0, 0, },
   {  "opw3_06.rom", 0x00200000, 0x2fa1e08d, 0, 0, 0, },
   {  "opw3_16.rom", 0x00080000, 0x198ff1f6, 0, 0, 0, },
   {  "opw3_17.rom", 0x00080000, 0xac35a672, 0, 0, 0, },
   {  "opw3_18.rom", 0x00080000, 0xbd5d7cdb, 0, 0, 0, },
   {  "opw3_21.rom", 0x00080000, 0xc61c558b, 0, 0, 0, },
   {  "opw3_22.rom", 0x00010000, 0x118374a6, 0, 0, 0, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct INPUT_INFO input_opwolf3[] =
{
   INP0( COIN1, 0x069003, 0x10 ),
   INP0( COIN2, 0x069003, 0x20 ),
   INP0( COIN3, 0x069003, 0x40 ),
   INP0( COIN4, 0x069003, 0x80 ),
   INP0( TILT, 0x069003, 0x02 ),
   INP0( SERVICE, 0x069003, 0x0E ),
   INP0( TEST, 0x069007, 0xFF ),

   INP0( P1_START, 0x069005, 0x04 ),
   INP1( P1_UP, 0x069027, 0x01 ),
   INP1( P1_DOWN, 0x069027, 0x02 ),
   INP1( P1_LEFT, 0x069027, 0x04 ),
   INP1( P1_RIGHT, 0x069027, 0x08 ),
   INP0( P1_B1, 0x069005, 0x01 ),
   INP0( P1_B2, 0x069005, 0x02 ),
   INP0( P1_B3, 0x069005, 0x04 ),

   INP0( P2_START, 0x069005, 0x40 ),
   INP1( P2_UP, 0x069025, 0x01 ),
   INP1( P2_DOWN, 0x069025, 0x02 ),
   INP1( P2_LEFT, 0x069025, 0x04 ),
   INP1( P2_RIGHT, 0x069025, 0x08 ),
   INP0( P2_B1, 0x069005, 0x10 ),
   INP0( P2_B2, 0x069005, 0x20 ),
   INP0( P2_B3, 0x069005, 0x40 ),

   END_INPUT
};

static struct ROMSW_DATA romsw_data_operation_wolf_3_0[] =
{
   { "Taito World?",          0x00 },
   { "Taito America",         0x01 },
   { "Taito Japan",           0x02 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_opwolf3[] =
{
   { 0x000063, 0x02, romsw_data_operation_wolf_3_0 },
   { 0,        0,    NULL },
};



static void BadWriteByte(UINT32 address, UINT8 data)
{
#ifdef RAINE_DEBUG
      if(address!=0xB00000) print_debug("Wb(%06x,%02x) [%06x]\n",address,data,s68000context.pc);
#endif
}

static void BadWriteWord(UINT32 address, UINT16 data)
{
#ifdef RAINE_DEBUG
      if(address!=0xC00000) print_debug("Ww(%06x,%04x) [%06x]\n",address,data,s68000context.pc);
#endif
}

static void opwolf3_colour_ram_wb(UINT32 address, UINT8 data)
{
   WriteByte((RAM + 0x60000 + (address & 0x7FFF)), data);
}

static void opwolf3_colour_ram_ww(UINT32 address, UINT16 data)
{
   WriteWord68k((RAM + 0x60000 + (address & 0x7FFE)), data);
}

static UINT8 opwolf3_colour_ram_rb(UINT32 address)
{
   return ReadByte((RAM + 0x60000 + (address & 0x7FFF)));
}

static UINT16 opwolf3_colour_ram_rw(UINT32 address)
{
   return ReadWord68k((RAM + 0x60000 + (address & 0x7FFE)));
}

static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;

static UINT8 *RAM_SCR0;
static UINT8 *RAM_SCR1;
static UINT8 *RAM_SCR2;
static UINT8 *RAM_SCR3;
static UINT8 *RAM_SCR4;

static UINT32 SCR0_XOFS;
static UINT32 SCR1_XOFS;
static UINT32 SCR2_XOFS;
static UINT32 SCR3_XOFS;
static UINT32 SCR4_XOFS;

static UINT32 SCR0_YOFS;
static UINT32 SCR1_YOFS;
static UINT32 SCR2_YOFS;
static UINT32 SCR3_YOFS;
static UINT32 SCR4_YOFS;

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG0_SOLID;

static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 opwolf3_adc_r(UINT32 offset) {
  // if (analog_num < 0) return 0xff;

  switch (offset & 0xf) {
    case 0:
    // return (analog_normx>>7)+127;
    return 255-mouse_x; // this one is inverted !!!
    case 2:
    // return (analog_normy>>7)+127;
    return mouse_y;
    // default:
    // printf("%x ???\n",offset);
  }
  return 5;
}

static void opwolf3_adc_req_w(UINT32 offset) {
  // the game selects the analog port to read from by writing here, which
  // tiggers an irq 4 times/frame
   cpu_interrupt(CPU_68K_0, 3);
}

static void load_opwolf3(void)
{
   int ta,tb,tc;
   GameMouse = 1;
   set_mouse_range(0,0,255,255);

   RAMSize=0x80000+0x10000;

   if(!(ROM=AllocateMem(0x200000))) return;
   if(!(RAM=AllocateMem(RAMSize))) return;
   if(!(GFX=AllocateMem(0x800000+0x800000))) return;

   GFX_BG0 = GFX+0x000000;
   GFX_SPR = GFX+0x800000;

   tb=0;
   if(!load_rom("opw3_02.rom", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=2;
   if(!load_rom("opw3_03.rom", ROM, 0x200000)) return;	// 16x16 SPRITES
   for(ta=0;ta<0x200000;ta++){
      GFX_SPR[tb++]=ROM[ta]&15;
      GFX_SPR[tb++]=ROM[ta]>>4;
      tb+=2;
   }
   tb=0;
   if(!load_rom("opw3_04.rom", ROM, 0x200000)) return;	// 16x16 SPRITES (MASK)
   for(ta=0;ta<0x200000;ta++){
      tc=ROM[ta];
      GFX_SPR[tb+3]|=((tc&0xC0)>>6)<<4;
      GFX_SPR[tb+2]|=((tc&0x30)>>4)<<4;
      GFX_SPR[tb+1]|=((tc&0x0C)>>2)<<4;
      GFX_SPR[tb+0]|=((tc&0x03)>>0)<<4;
      tb+=4;
   }

   tb=0;
   if(!load_rom("opw3_05.rom", ROM, 0x200000)) return;	// 16x16 TILES
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }
   tb=4;
   if(!load_rom("opw3_06.rom", ROM, 0x200000)) return;	// 16x16 TILES
   for(ta=0;ta<0x200000;ta+=2){
      GFX_BG0[tb++]=ROM[ta]&15;
      GFX_BG0[tb++]=ROM[ta]>>4;
      GFX_BG0[tb++]=ROM[ta+1]&15;
      GFX_BG0[tb++]=ROM[ta+1]>>4;
      tb+=4;
   }

   GFX_BG0_SOLID = make_solid_mask_16x16(GFX_BG0, 0x8000);
   GFX_SPR_SOLID = make_solid_mask_16x16(GFX_SPR, 0x8000);

   if(!load_rom("opw3_16.rom", RAM, 0x80000)) return;	// MAIN 68000
   for(ta=0;ta<0x80000;ta++){
      ROM[ta+ta]=RAM[ta];
   }
   if(!load_rom("opw3_21.rom", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[ta+ta+1]=RAM[ta];
   }
   if(!load_rom("opw3_18.rom", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[ta+ta+0x100000]=RAM[ta];
   }
   if(!load_rom("opw3_17.rom", RAM, 0x80000)) return;
   for(ta=0;ta<0x80000;ta++){
      ROM[ta+ta+0x100001]=RAM[ta];
   }

   /*-----[Sound Setup]-----*/

   Z80ROM=RAM+0x80000;
   if(!load_rom("opw3_22.rom", Z80ROM, 0x10000)) return;	// Z80 SOUND ROM

   if(!(PCMROM=AllocateMem(0x200000))) return;
   if(!load_rom("opw3_01.rom",PCMROM,0x200000)) return;	// ADPCM A rom
   YM2610SetBuffers(PCMROM, PCMROM, 0x200000, 0x200000);

   AddTaitoYM2610(0x02E1, 0x00C5, 0x10000);

   /*-----------------------*/

   RAM_BG0=RAM+0x30000;
   RAM_BG1=RAM+0x32000;
   RAM_BG2=RAM+0x34000;
   RAM_BG3=RAM+0x36000;

   RAM_SCR0=RAM+0x6A000;
   RAM_SCR1=RAM+0x6A002;
   RAM_SCR2=RAM+0x6A004;
   RAM_SCR3=RAM+0x6A006;
   RAM_SCR4=RAM+0x6A018;

   SCR0_XOFS=0x0021;
   SCR1_XOFS=0x001D;
   SCR2_XOFS=0x0019;
   SCR3_XOFS=0x0015;
   SCR4_XOFS=0x0023;

   SCR0_YOFS=0x0008;
   SCR1_YOFS=0x0008;
   SCR2_YOFS=0x0008;
   SCR3_YOFS=0x0008;
   SCR4_YOFS=0x0008;

   memset(RAM+0x00000,0x00,0x80000);
   memset(RAM+0x69000,0xFF,0x00100);

   //WriteWord68k(&ROM[0x00060],0x0000);

   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);
   InitPaletteMap(RAM+0x60000, 0x200, 0x10, 0x8000);

   set_colour_mapper(&col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb);

   // Init tc0006vcu emulation
   // ------------------------

   if(!(tc0006vcu.GFX_FG = AllocateMem(0x4000))) return;

   tc0006vcu.RAM	= RAM+0x30000;
   tc0006vcu.RAM_SCR	= RAM+0x6A000;
   tc0006vcu.GFX_BG	= GFX_BG0;
   tc0006vcu.GFX_BG_MASK= GFX_BG0_SOLID;
   tc0006vcu.tile_mask  = 0x7FFF;
// Mapper disabled
   tc0006vcu.pal_ofs	= 0x100;
   tc0006vcu.bmp_x	= 48;
   tc0006vcu.bmp_y	= 48;
   tc0006vcu.bmp_w	= 320;
   tc0006vcu.bmp_h	= 224;
   tc0006vcu.scr_x[0]	= SCR0_XOFS;
   tc0006vcu.scr_x[1]	= SCR1_XOFS;
   tc0006vcu.scr_x[2]	= SCR2_XOFS;
   tc0006vcu.scr_x[3]	= SCR3_XOFS;
   tc0006vcu.scr_x[4]	= SCR4_XOFS;
   tc0006vcu.scr_y[0]	= SCR0_YOFS;
   tc0006vcu.scr_y[1]	= SCR1_YOFS;
   tc0006vcu.scr_y[2]	= SCR2_YOFS;
   tc0006vcu.scr_y[3]	= SCR3_YOFS;
   tc0006vcu.scr_y[4]	= SCR4_YOFS;

   init_tc0006vcu();

   // Init tc0200obj emulation
   // ------------------------

   tc0200obj.RAM	= RAM+0x20000;
   tc0200obj.RAM_B	= RAM+0x28000;
   tc0200obj.GFX	= GFX_SPR;
   tc0200obj.MASK	= GFX_SPR_SOLID;
   tc0200obj.bmp_x	= 48;
   tc0200obj.bmp_y	= 48;
   tc0200obj.bmp_w	= 320;
   tc0200obj.bmp_h	= 224;
// Mapper disabled
   tc0200obj.tile_mask	= 0x7FFF;
   tc0200obj.ofs_x	= 0;	//0-0x2E;
   tc0200obj.ofs_y	= 0;	//0-0x1F;

   tc0200obj.cols	= 64;

   tc0200obj.RAM_TILE	= RAM+0x40000;
   tc0200obj.RAM_TILE_B	= RAM+0x40800;

   init_tc0200obj();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x200000);
   ByteSwap(RAM,0x80000);

   AddMemFetch(0x000000, 0x1FFFFF, ROM+0x000000-0x000000);		// 68000 ROM
   AddMemFetch(-1, -1, NULL);

   AddReadBW(0x000000, 0x1FFFFF, NULL, ROM+0x000000);			// 68000 ROM
   AddRWBW(0x500000, 0x50FFFF, NULL, RAM+0x000000);			// MAIN RAM
   AddRWBW(0x600000, 0x60FFFF, NULL, RAM+0x020000);			// OBJECT RAM
   AddReadByte(0x900000, 0x907FFF, opwolf3_colour_ram_rb, NULL);	// COLOR RAM
   AddReadByte(0xA00000, 0xA03FFF, NULL, RAM+0x042000);			// EEPROM?
   AddReadByte(0xC00000, 0xC0000F, NULL, RAM+0x069000);			// ioc
   AddReadByte(0xC00020, 0xC0002F, NULL, RAM+0x069000);			// ioc
   AddReadByte(0xE00000, 0xE00006, opwolf3_adc_r, NULL);
   AddWriteByte(0xE00000, 0xE00007, opwolf3_adc_req_w, NULL);
   AddReadByte(0xD00000, 0xD00003, tc0140syt_read_main_68k, NULL);	// tc0140syt
   AddReadByte(0x700000, 0x701FFF, NULL, RAM+0x040000);			// OBJECT TILE MAP
   AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
   AddReadByte(-1, -1, NULL, NULL);

   AddReadWord(0x900000, 0x907FFF, opwolf3_colour_ram_rw, NULL);	// COLOR RAM
   AddReadWord(0x700000, 0x701FFF, NULL, RAM+0x040000);			// OBJECT TILE MAP
   AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
   AddReadWord(-1, -1,NULL, NULL);

   AddWriteByte(0x800000, 0x80DFFF, NULL, RAM+0x030000);		// SCREEN RAM
   AddWriteByte(0x80E000, 0x80FFFF, tc0006vcu_gfx_fg0_wb, NULL);	// FG0 GFX RAM
   AddWriteByte(0x700000, 0x701FFF, NULL, RAM+0x040000);		// OBJECT TILE MAP
   AddWriteByte(0x900000, 0x907FFF, opwolf3_colour_ram_wb, NULL);	// COLOR RAM
   AddWriteByte(0xA00000, 0xA03FFF, NULL, RAM+0x042000);		// EEPROM?
   AddWriteByte(0xD00000, 0xD00003, tc0140syt_write_main_68k, NULL);	// tc0140syt
   AddWriteByte(0xAA0000, 0xAA0001, Stop68000, NULL);			// Trap Idle 68000
   AddWriteByte(0x000000, 0xFFFFFF, BadWriteByte, NULL);		// <Bad Writes>
   AddWriteByte(-1, -1, NULL, NULL);

   AddWriteWord(0x800000, 0x80DFFF, NULL, RAM+0x030000);		// SCREEN RAM
   AddWriteWord(0x80E000, 0x80FFFF, tc0006vcu_gfx_fg0_ww, NULL);	// FG0 GFX RAM
   AddWriteWord(0x700000, 0x701FFF, NULL, RAM+0x040000);		// OBJECT TILE MAP
   AddWriteWord(0x900000, 0x907FFF, opwolf3_colour_ram_ww, NULL);	// COLOR RAM
   AddWriteWord(0x830000, 0x8300FF, NULL, RAM+0x06A000);		// SCROLL
   AddWriteWord(0x000000, 0xFFFFFF, BadWriteWord, NULL);		// <Bad Writes>
   AddWriteWord(-1, -1, NULL, NULL);

   AddInitMemory();	// Set Starscream mem pointers...
}

static void execute_opwolf3(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 16MHz (60fps)

   cpu_interrupt(CPU_68K_0, 6);
   cpu_interrupt(CPU_68K_0, 5);

   Taito2610_Frame();			// Z80 and YM2610

   debug_tc0006vcu();
}

static void DrawOperationWolf3(void)
{
   ClearPaletteMap();

   tc0006vcu_layer_count = 0;

   tc0006vcu_render_layer_1024(0);

   tc0006vcu_render_layer_1024(1);

   tc0006vcu_render_layer_1024(2);

   tc0006vcu_render_layer_1024(3);

   render_tc0200obj_mapped_opwolf3();

   tc0006vcu_render_fg0();
}
static struct VIDEO_INFO video_opwolf3 =
{
   DrawOperationWolf3,
   320,
   224,
   48,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};
static struct DIR_INFO dir_opwolf3[] =
{
   { "operation_wolf_3", },
   { "opwolf3", },
   { NULL, },
};
GME( opwolf3, "Operation Wolf 3", TAITO, 1994, GAME_SHOOT | GAME_NOT_WORKING,
	.romsw = romsw_opwolf3,
);

