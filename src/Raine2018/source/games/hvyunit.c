/******************************************************************************/
/*                                                                            */
/*                HEAVY UNIT (C) 1988 KANEKO (TAITO LICENSE)                  */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc220ioc.h"
#include "taitosnd.h"
#include "2203intf.h"
#include "decode.h"
#include "sasound.h"		// sample support routines
#include "savegame.h"
#include "blit.h" // clear_game_screen

/*

b73-12.bin - sound cpu
----------------------

nmi is triggered when sound command is written?
int is triggered by ym2203 timers or 60fps?

memory:

0000-7FFF = base rom
8000-BFFF = bank rom

port:

00-00 = bank switch
02-03 = ym2203
04-04 = sound command?

*/

static struct ROM_INFO rom_hvyunit[] =
{
  { "b73_10.5c", 0x20000, 0xca52210f, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "b73_11.5p", 0x10000, 0xcb451695, REGION_CPU2, 0x00000, LOAD_NORMAL },
  { "b73_12.7e", 0x010000, 0xd1d24fab, REGION_ROM3, 0x000000, LOAD_NORMAL },
//  { "mermaid.bin", 0x0e00, 0x88c5dd27, REGION_MERMAID, 0x0000, LOAD_NORMAL },
  { "b73_08.2f", 0x080000, 0xf83dd808, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "b73_07.2c", 0x010000, 0x5cffa42c, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "b73_06.2b", 0x010000, 0xa98e4aea, REGION_GFX1, 0x120000, LOAD_NORMAL },
  { "b73_01.1b", 0x010000, 0x3a8a4489, REGION_GFX1, 0x140000, LOAD_NORMAL },
  { "b73_02.1c", 0x010000, 0x025c536c, REGION_GFX1, 0x160000, LOAD_NORMAL },
  { "b73_03.1d", 0x010000, 0xec6020cf, REGION_GFX1, 0x180000, LOAD_NORMAL },
	/*                      0x190000, 0x010000  no data */
  { "b73_04.1f", 0x010000, 0xf7badbb2, REGION_GFX1, 0x1a0000, LOAD_NORMAL },
	/*                      0x1b0000, 0x010000  no data */
  { "b73_05.1h", 0x010000, 0xb8e829d2, REGION_GFX1, 0x1c0000, LOAD_NORMAL },
  { "b73_09.2p", 0x080000, 0x537c647f, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hvyunitj[] = // clone of hvyunit
{
  { "b73_30.5c", 0x20000, 0x600af545, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "b73_14.5p", 0x10000, 0x0dfb51d4, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hvyunitjo[] = // clone of hvyunit
{
  { "b73_13.5c", 0x20000, 0xe2874601, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "b73_14.5p", 0x10000, 0x0dfb51d4, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hvyunitu[] = // clone of hvyunit
{
  { "b73_34.5c", 0x20000, 0x05c30a90, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "b73_35.6p", 0x10000, 0xaed1669d, REGION_ROM2, 0x00000, LOAD_NORMAL },
  { "b73_08.2f", 0x080000, 0xf83dd808, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "b73_28.2c", 0x020000, 0xa02e08d6, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "b73_27.2b", 0x020000, 0x8708f97c, REGION_GFX1, 0x120000, LOAD_NORMAL },
  { "b73_25.0b", 0x020000, 0x2f13f81e, REGION_GFX1, 0x140000, LOAD_NORMAL }, /* the data in first half of this actually differs slightly to the other sets, a 0x22 fill is replaced by 0xff on empty tiles */
  { "b73_26.0c", 0x010000, 0xb8e829d2, REGION_GFX1, 0x160000, LOAD_NORMAL }, /* == b73_05.1h, despite the different label */
  { NULL, 0, 0, 0, 0, 0 }
};

// inputs / dsw are handled by an mcu, so adresses < 255 and to handle later...
static struct INPUT_INFO input_hvyunit[] =
{
  INP0( P1_START, 0x00, 0x01),
  INP0( P2_START, 0x00, 0x02),
  INP0( COIN1, 0x00, 0x04),
  INP0( COIN2, 0x00, 0x08),
  INP0( UNKNOWN, 0x00, 0x10),
  INP0( UNKNOWN, 0x00, 0x20),
  INP0( SERVICE, 0x00, 0x40),
  INP0( UNKNOWN, 0x00, 0x80),

  INP0( P1_UP, 0x01, 0x01),
  INP0( P1_DOWN, 0x01, 0x02),
  INP0( P1_LEFT, 0x01, 0x04),
  INP0( P1_RIGHT, 0x01, 0x08),
  INP0( P1_B1, 0x01, 0x10),
  INP0( P1_B2, 0x01, 0x20),
  INP0( UNKNOWN, 0x01, 0x40),
  INP0( UNKNOWN, 0x01, 0x80),

  INP0( P2_UP, 0x02, 0x01),
  INP0( P2_DOWN, 0x02, 0x02),
  INP0( P2_LEFT, 0x02, 0x04),
  INP0( P2_RIGHT, 0x02, 0x08),
  INP0( P2_B1, 0x02, 0x10),
  INP0( P2_B2, 0x02, 0x20),
  INP0( UNKNOWN, 0x02, 0x40),
  INP0( UNKNOWN, 0x02, 0x80),
  END_INPUT
};

static struct DSW_DATA dsw_data_hvyunit_3[] =
{
  // "DSW1:1"
  { MSG_CABINET, 0x01, 2 },
  { MSG_UPRIGHT, 0x00, 0x00 },
  { MSG_TABLE, 0x01, 0x00 },
  // "DSW1:2"
  { MSG_SCREEN, 0x02, 2 },
  { MSG_OFF, 0x02, 0x00 },
  { MSG_ON, 0x00, 0x00 },
  // "DSW1:3"
  DSW_SERVICE( 0x00, 0x04 ),
  // "DSW1:4"
  { ("Coin Mode"), 0x08, 2 },
  { ("Mode 1"), 0x08, 0x00 },
  { ("Mode 2"), 0x00, 0x00 },
  // "DSW1:5,6"
  { MSG_COIN1, 0x30, 8 },
  { MSG_2COIN_1PLAY, 0x20, 0x00 },
  { MSG_1COIN_1PLAY, 0x30, 0x00 },
  { MSG_1COIN_2PLAY, 0x10, 0x00 },
  { MSG_1COIN_6PLAY, 0x00, 0x00 },
  { MSG_2COIN_1PLAY, 0x20, 0x00 },
  { MSG_1COIN_1PLAY, 0x30, 0x00 },
  { MSG_1COIN_3PLAY, 0x10, 0x00 },
  { MSG_1COIN_4PLAY, 0x00, 0x00 },
  // "DSW1:7,8"
  { MSG_COIN2, 0xc0, 8 },
  { MSG_2COIN_1PLAY, 0x80, 0x00 },
  { MSG_1COIN_1PLAY, 0xc0, 0x00 },
  { MSG_1COIN_2PLAY, 0x40, 0x00 },
  { MSG_1COIN_6PLAY, 0x00, 0x00 },
  { MSG_2COIN_1PLAY, 0x80, 0x00 },
  { MSG_1COIN_1PLAY, 0xc0, 0x00 },
  { MSG_1COIN_3PLAY, 0x40, 0x00 },
  { MSG_1COIN_4PLAY, 0x00, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_DATA dsw_data_hvyunit_4[] =
{
  // "DSW2:1,2"
  { MSG_DIFFICULTY, 0x03, 4 },
  { MSG_EASY, 0x02, 0x00 },
  { MSG_NORMAL, 0x03, 0x00 },
  { MSG_HARD, 0x01, 0x00 },
  { MSG_HARDEST, 0x00, 0x00 },
  // "DSW2:3"
  { MSG_CONTINUE_PLAY, 0x04, 2 },
  { MSG_OFF, 0x00, 0x00 },
  { MSG_ON, 0x04, 0x00 },
  // "DSW2:4"
  { "Bonus", 0x08, 2 },
  { MSG_OFF, 0x08, 0x00 },
  { MSG_ON, 0x00, 0x00 },
  // "DSW2:5,6"
  { MSG_LIVES, 0x30, 4 },
  { "3", 0x30, 0x00 },
  { "4", 0x20, 0x00 },
  { "5", 0x10, 0x00 },
  { "7", 0x00, 0x00 },
  // "DSW2:7"
  { MSG_DEMO_SOUND, 0x40, 2 },
  { MSG_OFF, 0x00, 0x00 },
  { MSG_ON, 0x40, 0x00 },
  { NULL, 0, 0}
};

static struct DSW_INFO dsw_hvyunit[] =
{
  { 0x3, 0xfe, dsw_data_hvyunit_3 },
  { 0x4, 0x77, dsw_data_hvyunit_4 },
  { 0, 0, NULL }
};

#if 0
static struct ROMSW_DATA romsw_data_heavy_unit_0[] =
{
   { "Taito Japan (notice)",     0x01 },
   { "Taito America",            0x02 },
   { "Taito Japan",              0x03 },
   { "Tad Corporation",          0x04 },
   { NULL,                       0    },
};
#endif

static struct YM2203interface ym2203_interface =
{
  1,			// 1 chip
  3000000,		// rate
  { 85 | (0x80<<8) },   // volume
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { NULL }
};

static struct SOUND_INFO sound_hvyunit[] =
{
   { SOUND_YM2203,  &ym2203_interface,  },
   { 0,             NULL,               },
};

#if 0
static struct ROMSW_INFO romsw_heavy_unit[] =
{
   { 0x007FFF, 0x01, romsw_data_heavy_unit_0 },
   { 0,        0,    NULL },
};
#endif

static UINT8 *RAM2;
static UINT8 *RAM3;
static UINT8 *RAM_COLOUR;

static UINT8 mcu_latch,mcu_pos,scrollx,scrolly,slave_latch;

/******************************************************************************/
/* MAIN Z80 ROM BANKING                                                       */
/******************************************************************************/

static void init_bank_rom()
{
  z80_init_banks_area_ofs(0,ROM,0x20000,0x8000,0x4000,2);
}

/******************************************************************************/
/* SUB Z80 ROM BANKING                                                        */
/******************************************************************************/

static void init_bank_rom_1()
{
  z80_init_banks_area_ofs(1,Z80ROM,0x10000,0x8000,0x4000,2);
}

/******************************************************************************/
/* SUB Z80 ROM BANKING                                                        */
/******************************************************************************/

static void init_bank_rom_2(UINT8 *src, UINT8 *dst)
{
  z80_init_banks_area_ofs(2,src,0x10000,0x8000,0x4000,2);
}

/******************************************************************************/
/* INPUT + DSW                                                                */
/******************************************************************************/

static UINT32 sound_command;
static UINT32 sound_nmi;

static void heavy_unit_main_port_wb(UINT16 offset, UINT8 data)
{
   offset &= 0xFF;

   switch(offset){
      case 0x01:
	z80_set_bank(0,data & 7);
      break;
      default:
         print_debug("main_port_wb(%02x,%02x) [%04x]\n", offset, data, z80pc);
      break;
   }
}


static UINT8 heavy_unit_sub_port_rb(UINT16 offset)
{
   offset &= 0xFF;

   switch(offset){
       // slave_latch comes from the mcu, will need to handle this specifically...
   case 4: return slave_latch;
   case 12: return 0; // mcu status : 0 means data available on latch
   }
   return 0xff;
}

static void heavy_unit_sub_port_wb(UINT16 offset, UINT8 data)
{
   offset &= 0xFF;

   switch(offset){
      case 0x00:
	z80_set_bank(1,data & 3);
	break;
      case 0x02:
         sound_command = data;
         sound_nmi = 1;
	 break;
      case 4:
	 mcu_latch = data;
	 mcu_pos = 0;
	 break;
      case 6:
	 scrolly = data;
	 break;
      case 8:
	 scrollx = data;
	 break;
	 // 14 : coin_count_w
      default:
         print_debug("sub_port_wb(%02x,%02x) [%04x]\n", offset, data, z80pc);
      break;
   }
}

static UINT8 hvyunit_sound_port_rb(UINT16 offset)
{
   UINT8 ret;

   offset &= 0xFF;

   switch(offset){
      case 0x02:
      case 0x03:
         ret = YM2203AReadZ80(offset & 1);
      break;
      case 0x04:
         ret = sound_command;
      break;
      default:
         print_debug("sound_port_rb(%02x) [%04x]\n", offset, z80pc);
         ret = 0xFF;
      break;
   }

   return ret;
}

static void hvyunit_sound_port_wb(UINT16 offset, UINT8 data)
{
   offset &= 0xFF;

   switch(offset){
      case 0x00:
	z80_set_bank(2,data & 3);
      break;
      case 0x02:
      case 0x03:
         YM2203AWriteZ80(offset & 1, data);
      break;
      default:
         print_debug("sound_port_wb(%02x,%02x) [%04x]\n", offset, data, z80pc);
      break;
   }
}

/******************************************************************************/
/* LOAD SAVE DATA                                                             */
/******************************************************************************/

static void load_hvyunit(void)
{
   UINT8 *TMP;

   RAMSize=0x10000+0x10000+0x10000;

   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM2       = RAM+0x10000;
   RAM3       = RAM+0x10000+0x10000;
   RAM_COLOUR = RAM + 0x400;

   // Skip Idle Z80

   ROM[0x1B2C]=0xD3;  // OUTA (AAh)
   ROM[0x1B2D]=0xAA;  //

   SetStopZ80Mode2(0x1B22);

   init_bank_rom();

   AddZ80AROMBase(ROM, 0x0038, 0x0066);

   AddZ80AReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM + BANK
   AddZ80ARW(0xC000, 0xDFFF, NULL,			RAM +0xC000);	// RAM
   AddZ80ARW(0xE000, 0xFFFF, NULL,			RAM2+0xE000);	// COMMON RAM

   AddZ80AWritePort(0xAA, 0xAA, StopZ80BMode2,			NULL);		// Trap Idle Z80
   AddZ80AWritePort(0x00, 0xFF, heavy_unit_main_port_wb,	NULL);		// PORT
   finish_conf_z80(0);

/*
   // Skip Idle Z80

   TMP[0x0089]=0xD3;  // OUTA (AAh)
   TMP[0x008A]=0xAA;  //

   SetStopZ80CMode2(0x0083);
*/
   init_bank_rom_1();

   memset(RAM2, 0x00, 0x10000);

   AddZ80BROMBase(Z80ROM, 0x0038, 0x0066);

   AddZ80BReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM + BANK
   AddZ80BRW(0xC000, 0xc7ff, NULL, RAM);	// video + palette
   AddZ80BRW(0xd000, 0xdfff, NULL, RAM2+0xd000);	// palette_ext + palette + ram
   AddZ80BRW(0xE000, 0xFFFF, NULL, RAM2+0xE000);	// COMMON RAM

   AddZ80BReadPort(0x00, 0xFF, heavy_unit_sub_port_rb,		NULL);		// PORT

   AddZ80BWritePort(0xAA, 0xAA, StopZ80CMode2,			NULL);		// Trap Idle Z80
   AddZ80BWritePort(0x00, 0xFF, heavy_unit_sub_port_wb,		NULL);		// PORT
   finish_conf_z80(1);

   TMP = load_region[REGION_ROM3];

   // Skip Idle Z80

/*   TMP[0x00CB]=0xD3;  // OUTA (AAh)
   TMP[0x00CC]=0xAA;  //

   SetStopZ80DMode2(0x00CB); */

   init_bank_rom_2(TMP,NULL);

   AddZ80CROMBase(TMP, 0x0038, 0x0066);

   AddZ80CReadByte(0x0000, 0xBFFF, NULL,			NULL);		// Z80 ROM + BANK
   AddZ80CRW(0xC000, 0xc7FF, NULL,			RAM3+0xC000);	// RAM

   AddZ80CReadPort(0x00, 0xFF, hvyunit_sound_port_rb,	NULL);		// PORT

   AddZ80CWritePort(0xAA, 0xAA, StopZ80DMode2,			NULL);		// Trap Idle Z80
   AddZ80CWritePort(0x00, 0xFF, hvyunit_sound_port_wb,	NULL);		// PORT
   finish_conf_z80(2);

   InitPaletteMap(RAM_COLOUR, 0x20, 0x10, 0x1000);
   set_colour_mapper(&col_map_xxxx_rrrr_gggg_bbbb);
}

static void execute_hvyunit(void)
{
   cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(8,60));	// MAIN Z80 8MHz (60fps)
      print_debug("Z80PC_MAIN:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_0, 0x38);

   cpu_execute_cycles(CPU_Z80_1, CPU_FRAME_MHz(8,60));	// SUB Z80 8MHz (60fps)
      print_debug("Z80PC_SUB:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_1, 0x38);

   if(sound_nmi){
      sound_nmi = 0;
      cpu_int_nmi(CPU_Z80_2);
   }

   cpu_execute_cycles(CPU_Z80_2, CPU_FRAME_MHz(8,60));	// SUB Z80 8MHz (60fps)
      print_debug("Z80PC_SOUND:%04x\n",z80pc);
   cpu_interrupt(CPU_Z80_2, 0x38);
}

static void draw_heavy_unit(void)
{
  int x,y,ta;
  int sx,sy,offs,goffs,gfx_offs,gfx_num,gfx_attr,height,xc,yc;
  UINT8 *map,*RAM_BG;
   ClearPaletteMap();

   clear_game_screen(0);
   // TC0010VCU 0

   RAM_BG = RAM+0xC000;

   sx = 0;
   for (offs=0;offs<0x600;offs+=4)
   {
      if (*(UINT32 *)(&RAM_BG[offs + 0]) == 0) continue;

      gfx_num = RAM_BG[offs + 1];
      gfx_attr = RAM_BG[offs + 3];

      if ((gfx_num & 0x80) == 0){     /* 16x16 sprites */

         gfx_offs = gfx_num & 0x7F;
         gfx_offs <<= 3;
         gfx_offs += 0x0600;
         height = 2;

         sx  = RAM_BG[offs + 2];
         sx |= (gfx_attr & 0x40) << 2;

      }
      else{                           /* 16x256 columns */

         gfx_offs = gfx_num & 0x3F;
         gfx_offs <<= 7;
         gfx_offs += 0x0A00;
         height = 32;

         if(gfx_num & 0x40)
            sx += 16;
         else {
            sx  = RAM_BG[offs + 2];
            sx |= (gfx_attr & 0x40) << 2;
	 }
      }

      sy = 256 - height*8 - (RAM_BG[offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++,goffs+=2)
         {
            ta = ReadWord(&RAM_BG[goffs]);
            if(gfx_solid[0][ta&0x3FFF]){

            MAP_PALETTE_MAPPED(
               Map_12bit_xRGB,
               (gfx_attr & 0x0F) | ((ta & 0xC000) >> 14),
               16,
               map
            );

            ta &= 0x3FFF;

            x = (sx + (xc << 3)) & 0xff;
            y = ((sy + (yc << 3)) & 0xff) -16;

            if ((x > -8) && (y > -8) && (x < 256) && (y < 224))
            {
               if(gfx_solid[0][ta] == 1)
                  Draw8x8_Trans_Mapped_8(&gfx[0][ta<<6], x+32, y+32, map);
               else
                  Draw8x8_Mapped_8(&gfx[0][ta<<6], x+32, y+32, map);
            }
            }
         }

         gfx_offs += height<<1;
      }
   }

   // TC0010VCU 1

   RAM_BG = RAM3+0x8000;

   sx = 0;
   for (offs=0;offs<0x600;offs+=4)
   {
      if (*(UINT32 *)(&RAM_BG[offs + 0]) == 0) continue;

      gfx_num = RAM_BG[offs + 1];
      gfx_attr = RAM_BG[offs + 3];

      if ((gfx_num & 0x80) == 0){     /* 16x16 sprites */

         gfx_offs = gfx_num & 0x7F;
         gfx_offs <<= 3;
         gfx_offs += 0x0600;
         height = 2;

         sx  = RAM_BG[offs + 2];
         sx |= (gfx_attr & 0x40) << 2;

      }
      else{                           /* 16x256 columns */

         gfx_offs = gfx_num & 0x3F;
         gfx_offs <<= 7;
         gfx_offs += 0x0A00;
         height = 32;

         if(gfx_num & 0x40)
            sx += 16;
         else {
            sx  = RAM_BG[offs + 2];
            sx |= (gfx_attr & 0x40) << 2;
	 }
      }

      sy = 256 - height*8 - (RAM_BG[offs + 0]);

      for (xc=0;xc<2;xc++)
      {
         goffs = gfx_offs;

         for (yc=0;yc<height;yc++,goffs+=2)
         {
            ta = ReadWord(&RAM_BG[goffs]);
            if(gfx_solid[1][ta&0x3FFF]){

            MAP_PALETTE_MAPPED(
               Map_12bit_xRGB,
               (gfx_attr & 0x0F) | ((ta & 0xC000) >> 14) | 0x10,
               16,
               map
            );

            ta &= 0x3FFF;

            x = (sx + (xc << 3)) & 0xff;
            y = ((sy + (yc << 3)) & 0xff) -16;

            if ((x > -8) && (y > -8) && (x < 256) && (y < 224))
            {
               if(gfx_solid[1][ta] == 1)
                  Draw8x8_Trans_Mapped_8(&gfx[1][ta<<6], x+32, y+32, map);
               else
                  Draw8x8_Mapped_8(&gfx[1][ta<<6], x+32, y+32, map);
            }
            }
         }

         gfx_offs += height<<1;
      }
   }
}

/*

CTRL RAM (OBJECT RAM)

0x0600 bytes

 0 |xxxxxxxx| Sprite Y (low)
 1 |x.......| 16x16 sprite / 16x256 column select
 1 |.x......| X Chain (16x256 column)
 1 |..xxxxxx| Sprite num (16x256 column)
 1 |.xxxxxxx| Sprite num (16x16 sprite)
 2 |xxxxxxxx| Sprite X (low)
 3 |.x......| Sprite X (high)
 3 |....xx..| Colour Bank (high)
 3 |......xx| Colour Bank (low mirror)

DATA RAM (SCREEN RAM)

0x0400 bytes (16x16 sprite)
0x1600 bytes (16x256 column)

 0 |xx......| Colour Bank (low)
 0 |..xxxxxx| Tile (high)
 1 |xxxxxxxx| Tile (low)

*/

static gfx_layout tile_layout =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0, 1, 2, 3 },
	{
		0*4,1*4,2*4,3*4,4*4,5*4,6*4,7*4,
		8*32+0*4,8*32+1*4,8*32+2*4,8*32+3*4,8*32+4*4,8*32+5*4,8*32+6*4,8*32+7*4
	},
	{
		0*32,1*32,2*32,3*32,4*32,5*32,6*32,7*32,
		16*32+0*32,16*32+1*32,16*32+2*32,16*32+3*32,16*32+4*32,16*32+5*32,16*32+6*32,16*32+7*32
	},
	4*8*32
};

static struct GFX_LIST hvyunit_gfx[] =
{
    { REGION_GFX1, &tile_layout }, /* sprite bank */
    { REGION_GFX2, &tile_layout }, /* sprite bank */
    { 0,           NULL,             },
};

static struct VIDEO_INFO video_hvyunit =
{
   draw_heavy_unit,
   256,
   224,
   32,
   VIDEO_ROTATE_NORMAL,
   hvyunit_gfx,
   56
};

GMEI( hvyunit,"Heavy Unit (World)",KANEKO,1988, GAME_SHOOT );
CLNEI( hvyunitj,hvyunit,"Heavy Unit (Japan,Newer)",KANEKO,1988, GAME_SHOOT );
CLNEI( hvyunitjo,hvyunit,"Heavy Unit (Japan,Older)",KANEKO,1988, GAME_SHOOT );
CLNEI( hvyunitu,hvyunit,"Heavy Unit -U.S.A. Version- (US)",KANEKO,1988, GAME_SHOOT );
