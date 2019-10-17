/* Some very crazy games, but the graphics and the music are nice ! */
/* And the hardware is very easy to emulate ! */

#include "gameinc.h"
#include "sasound.h"		// sample support routines
#include "adpcm.h"
#include "3812intf.h"
#include "blit.h" // clear_game_screen
#include "timer.h"
#include "eeprom.h"
#include "savegame.h" // load_eeprom

static struct ROM_INFO rom_multchmp[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "multchmp.u02",  0x7da8c0df, "multchmp.u03",  0x5dc62799),
  { "multchmp.u06", 0x20000, 0x7c178bd7, REGION_ROM2, 0, LOAD_NORMAL },
  { "multchmp.u06", 0x20000, 0x7c178bd7, REGION_ROM2, 0x8000, LOAD_NORMAL },
  { "multchmp.u36", 0x040000, 0xd8f06fa8, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "multchmp.u37", 0x040000, 0xb1ae7f08, REGION_GFX1, 0x040000, LOAD_NORMAL },
  { "multchmp.u38", 0x040000, 0x88e252e8, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "multchmp.u39", 0x040000, 0x51f01067, REGION_GFX1, 0x0c0000, LOAD_NORMAL },
  { "multchmp.u35", 0x040000, 0x9d1590a6, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "multchmp.u27", 0x080000, 0xdc42704e, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "multchmp.u28", 0x080000, 0x449991fa, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "multchmp.u33", 0x080000, 0xe4c0ec96, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "multchmp.u34", 0x080000, 0xbffaaccc, REGION_GFX2, 0x180000, LOAD_NORMAL },
  { "multchmp.u29", 0x080000, 0x01bd1399, REGION_GFX2, 0x200000, LOAD_NORMAL },
  { "multchmp.u30", 0x080000, 0xc6b4cc18, REGION_GFX2, 0x280000, LOAD_NORMAL },
  { "multchmp.u31", 0x080000, 0xb1e4e9e3, REGION_GFX2, 0x300000, LOAD_NORMAL },
  { "multchmp.u32", 0x080000, 0xf05cb5b4, REGION_GFX2, 0x380000, LOAD_NORMAL },
  { "multchmp.u10", 0x20000, 0x6e741fcd, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_mchampdx[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "esd2.cu02",  0x4cca802c, "esd1.cu03",  0x0af1cd0a),
  { "esd3.su06", 0x80000, 0x2c0c8813, REGION_ROM2, 0, LOAD_NORMAL },
  { "esd3.su06", 0x80000, 0x2c0c8813, REGION_ROM2, 0x8000, LOAD_NORMAL },
  { "rom.ju02", 0x200000, 0x7e87e332, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "rom.ju01", 0x200000, 0x1a749fc2, REGION_GFX1, 0x200000, LOAD_NORMAL },
  { "esd5.ju07",0x080000, 0x6cc871cc, REGION_GFX1, 0x400000, LOAD_8_16 },
  // To emulate the rom_fill :
  { "esd5.ju07", 0x080000, 0x6cc871cc, REGION_GFX1, 0x500001, LOAD_8_16 },
  LOAD8_16(  REGION_GFX2,  0x000000,  0x200000,
            "rom.fu35",  0xba46f3dc, "rom.fu34",  0x2895cf09),
  { "esd4.su10", 0x80000, 0x14c4a30d, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_hedpanic[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x040000,
            "esd2",  0x8cccc691, "esd1",  0xd8574925),
  { "esd3", 0x80000, 0xc668d443, REGION_ROM2, 0, LOAD_NORMAL },
  { "esd3", 0x80000, 0xc668d443, REGION_ROM2, 0x8000, LOAD_NORMAL },
  { "esd6", 0x200000, 0x5858372c, REGION_GFX1, 0x200000, LOAD_NORMAL },
	/* expand this to take up 0x200000 bytes too so we can decode it */
  { "esd7", 0x200000, 0x055d525f, REGION_GFX1, 0x000000, LOAD_NORMAL },
/* Ignored : 	ROM_FILL( 0x500000, 0x100000, 0 ) */
  { "esd5", 0x080000, 0xbd785921, REGION_GFX1, 0x400000, LOAD_8_16 },
  { "esd5", 0x080000, 0xbd785921, REGION_GFX1, 0x500001, LOAD_8_16 },
  LOAD8_16(  REGION_GFX2,  0x000000,  0x200000,
            "esd8",  0x23aceb4f, "esd9",  0x76b46cd2),
  { "esd4", 0x080000, 0x5692fe92, REGION_SMP1, 0x000000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct DSW_DATA dsw_data_multchmp_2[] =
{
  DSW_SERVICE( 0, 0x0001),
  { _("Coinage Type"), 0x0002, 1 },
  { "1", 0x0002},
  DSW_DEMO_SOUND( 0x0000, 0x0004),
  DSW_SCREEN( 0x0008, 0x0000),
  { MSG_COIN1, 0x0030, 4 },
  { MSG_2COIN_1PLAY, 0x0010},
  { MSG_1COIN_1PLAY, 0x0030},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_2PLAY, 0x0020},
  { MSG_COIN2, 0x00c0, 4 },
  { MSG_2COIN_1PLAY, 0x0040},
  { MSG_1COIN_1PLAY, 0x00c0},
  { MSG_2COIN_3PLAY, 0x0000},
  { MSG_1COIN_2PLAY, 0x0080},
  { NULL, 0}
};

static struct DSW_DATA dsw_data_multchmp_3[] =
{
  { MSG_DIFFICULTY, 0x3, 4 },
  { MSG_EASY, 0x2},
  { MSG_NORMAL, 0x3},
  { MSG_HARD, 0x1},
  { MSG_HARDEST, 0x0},
  { MSG_LIVES, 0xc, 4 },
  { "2", 0x0},
  { "3", 0xc},
  { "4", 0x8},
  { "5", 0x4},
  { _("Selectable Games"), 0x10, 2 },
  { "3", 0x10},
  { "4", 0x0},
  { MSG_FREE_PLAY, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x0},
  { _("Unknown 2-6"), 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x0},
  { _("Unknown 2-7"), 0x80, 2 },
  { MSG_OFF, 0x80},
  { MSG_ON, 0x0},
  { NULL, 0}
};

static struct DSW_INFO dsw_multchmp[] =
{
  { 0x4, 0xfb, dsw_data_multchmp_2 },
  { 0x6, 0xff, dsw_data_multchmp_3 },
  { 0, 0, NULL }
};

static struct INPUT_INFO input_multchmp[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( P1_DOWN, 0x00, 0x02 ),
  INP0( P1_LEFT, 0x00, 0x04 ),
  INP0( P1_RIGHT, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),

  INP0( P2_UP, 0x01, 0x01 ),
  INP0( P2_DOWN, 0x01, 0x02 ),
  INP0( P2_LEFT, 0x01, 0x04 ),
  INP0( P2_RIGHT, 0x01, 0x08 ),
  INP0( P2_B1, 0x01, 0x10 ),
  INP0( P2_B2, 0x01, 0x20 ),

  INP0( COIN1, 0x02, 0x01 ),
  INP0( COIN2, 0x02, 0x02 ),
  INP0( P1_START, 0x02, 0x04 ),
  INP0( P2_START, 0x02, 0x08 ),
   END_INPUT
};

static struct INPUT_INFO input_mchampdx[] =
{
  INP0( P1_UP, 0x00, 0x01 ),
  INP0( P1_DOWN, 0x00, 0x02 ),
  INP0( P1_LEFT, 0x00, 0x04 ),
  INP0( P1_RIGHT, 0x00, 0x08 ),
  INP0( P1_B1, 0x00, 0x10 ),
  INP0( P1_B2, 0x00, 0x20 ),

  INP0( P2_UP, 0x01, 0x01 ),
  INP0( P2_DOWN, 0x01, 0x02 ),
  INP0( P2_LEFT, 0x01, 0x04 ),
  INP0( P2_RIGHT, 0x01, 0x08 ),
  INP0( P2_B1, 0x01, 0x10 ),
  INP0( P2_B2, 0x01, 0x20 ),

  INP0( COIN1, 0x02, 0x01 ),
  INP0( COIN2, 0x02, 0x02 ),
  INP0( P1_START, 0x02, 0x04 ),
  INP0( P2_START, 0x02, 0x08 ),
  INP0( P1_B1, 0x02, 0x10 ),
  INP0( TEST, 0x02, 0x40 ),

   END_INPUT
};

static GfxLayout layout_16x16x5 =
{
	16,16,
	RGN_FRAC(1,5),
	5,
	{ RGN_FRAC(4,5),RGN_FRAC(3,5),RGN_FRAC(2,5),RGN_FRAC(1,5), RGN_FRAC(0,5) },
	{ STEP8(0+7,-1), STEP8(8*16+7,-1) },
	{ STEP16(0,8) },
	16*16
};

static GfxLayout layout_8x8x8 =
{
	8,8,
	RGN_FRAC(1,4),
	8,
	{ STEP8(0,1) },
	{ RGN_FRAC(3,4)+0*8,RGN_FRAC(2,4)+0*8,RGN_FRAC(1,4)+0*8,RGN_FRAC(0,4)+0*8,
	  RGN_FRAC(3,4)+1*8,RGN_FRAC(2,4)+1*8,RGN_FRAC(1,4)+1*8,RGN_FRAC(0,4)+1*8 },
	{ STEP8(0,2*8) },
	8*8*2,
};

static struct GFX_LIST esd16_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &layout_16x16x5 }, // 8 color banks
	{ REGION_GFX2, &layout_8x8x8 }, // 2 color banks
	{ REGION_GFX1, &layout_16x16x5 }, // 8 color banks
	{ 0, NULL }
};

static GfxLayout hedpanic_layout_8x8x8 =
{
	8,8,
	RGN_FRAC(1,1),
	8,
	{ 0,1,2,3,4,5,6,7 },
	{ 0*8,2*8,1*8,3*8,4*8,6*8,5*8,7*8 },
	{ 0*64,1*64,2*64,3*64,4*64,5*64,6*64,7*64 },
	64*8,
};

static GfxLayout hedpanic_layout_16x16x8 =
{
	16,16,
	RGN_FRAC(1,1),
	8,
	{ 0,1,2,3,4,5,6,7 },
	{ 0*8,2*8,1*8,3*8,4*8,6*8,5*8,7*8,
	  64*8+0*8,64*8+2*8,64*8+1*8,64*8+3*8,64*8+4*8,64*8+6*8,64*8+5*8,64*8+7*8 },
	{ 0*64,1*64,2*64,3*64,4*64,5*64,6*64,7*64,
	  128*8+0*64,128*8+1*64,128*8+2*64,128*8+3*64,128*8+4*64,128*8+5*64,128*8+6*64,128*8+7*64
	},
	256*8,
};

static GfxLayout hedpanic_sprite_16x16x5 =
{
	16,16,
	RGN_FRAC(1,3),
	5,
	{   RGN_FRAC(2,3), RGN_FRAC(0,3), RGN_FRAC(0,3)+8, RGN_FRAC(1,3),RGN_FRAC(1,3)+8 },
	{ 7,6,5,4,3,2,1,0, 256+7,256+6,256+5,256+4,256+3,256+2,256+1,256+0 },
	{ 0*16,1*16,2*16,3*16,4*16,5*16,6*16,7*16,8*16,9*16,10*16,11*16,12*16,13*16,14*16,15*16 },
	16*32,
};

static struct GFX_LIST hedpanic_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &hedpanic_sprite_16x16x5 }, // 8 color banks
	{ REGION_GFX2, &hedpanic_layout_8x8x8 }, // 2 color banks
	{ REGION_GFX2, &hedpanic_layout_16x16x8 }, // 2 color banks
	{ 0, NULL }
};

static UINT8 *ram_spr,
  *ram_vram0,
  *ram_vram1,
  *ram_scroll,
  *ram_z80;

static UINT16 *spriteram16;

static void esd16_sound_w(UINT32 offset, UINT16 data) {
  latch = data;
  cpu_interrupt(CPU_Z80_0,0x38);
  ExitOnEI = 1;
  cpu_execute_cycles(CPU_Z80_0,6000);
  ExitOnEI = 0;
}

static UINT16 esd16_sound_command_r(UINT32 offset) {
  return latch;
}

static int layer_id_data[3];

static void esd16_eeprom_w(UINT32 offset, UINT16 data)
{
  // data line
  EEPROM_write_bit((data & 0x04) << 2);

  // clock line asserted.
  EEPROM_set_clock_line((data & 0x02) ? ASSERT_LINE : CLEAR_LINE );

  // reset line asserted: reset.
  EEPROM_set_cs_line((data & 0x01) ? CLEAR_LINE : ASSERT_LINE );
  //  logerror("(0x%06x) Unk EEPROM write: %04x %04x\n", activecpu_get_pc(), data, mem_mask);
}

static void hedpanic_platform_w(UINT32 offset, UINT16 data) {
  int offsets = ReadWord(&ram_scroll[8])+0x40* ReadWord(&ram_scroll[10]);

  WriteWord(&ram_vram1[offsets*2],data);
}

static UINT16 esd_eeprom_r(UINT32 offset) {
  return ((EEPROM_read_bit() & 0x01) << 7);
}

extern struct EEPROM_interface eeprom_interface_93C46; // cave.c

static void esd16_draw_sprites()
{
	int offs;

	UINT8 *map;

	for ( offs = 0; offs < 0x800/2; offs += 8/2 )
	{
	  int y, starty, endy, incy;

	  int	sy		=	spriteram16[ offs + 0 ];
	  int	code	=	spriteram16[ offs + 1 ];
	  int	sx		=	spriteram16[ offs + 2 ];
	  // int	attr	=	spriteram16[ offs + 3 ];

	  int dimy	=	1 << ((sy >> 9) & 3);

	  int color	=	(sx >> 9) & 0xf;

	  sx	=	sx & 0x1ff;
	  if (sx >= 0x180)	sx -= 0x200;

	  sy	 =	0x100 - ((sy & 0xff)  - (sy & 0x100));
	  sy	-=	dimy*16;

	  sx += 16;
	  sy += 16-8;

/* 	  if (flipy)	{ */
/* 	    starty = sy+(dimy-1)*16;	endy = sy-16;		incy = -16; */
/* 	  } else { */
	    starty = sy;  endy = sy+dimy*16;	incy = +16;
/* 	  } */

	  MAP_PALETTE_MAPPED_NEW(
				 16+color,
				 32, // ???
				 map);

	  if (sx>0 && sx<320+16) {
	    for (y = starty ; y != endy ; y += incy)
	      {
		if (y > 0 && y < 240+16) {
		  if (gfx1_solid[code]) {
		    if (gfx1_solid[code] == 1)
		      Draw16x16_Trans_Mapped_Rot(&gfx1[code<<8],sx,y,map);
		    else
		      Draw16x16_Mapped_Rot(&gfx1[code<<8],sx,y,map);
		  }
		}
		code++;
	      }
	  }
	}
}

static void hedpanic_draw_sprites()
{
	int offs;

	UINT8 *map;

	for ( offs = 0; offs < 0x800/2; offs += 8/2 )
	{
	  int y, starty, endy, incy;

	  int	sy		=	spriteram16[ offs + 0 ];
	  int	code	=	spriteram16[ offs + 1 ];
	  int	sx		=	spriteram16[ offs + 2 ];
	  // int	attr	=	spriteram16[ offs + 3 ];

	  int dimy	=	1 << ((sy >> 9) & 3);
	  int	flipx	=	(spriteram16[ offs + 0 ] & 0x2000 ? 1 : 0);

	  int color	=	(sx >> 9) & 0xf;

	  sx	=	sx & 0x1ff;
	  if (sx >= 0x180)	sx -= 0x200;

	  sy = 0x1ff-(sy & 0x1ff);

	  sx += 16-24;
	  sy += 16-8;

/* 	  if (flipy)	{ */
/* 	    starty = sy+(dimy-1)*16;	endy = sy-16;		incy = -16; */
/* 	  } else { */
	  starty = sy-dimy*16; endy = sy;	incy = +16;
/* 	  } */

	  MAP_PALETTE_MAPPED_NEW(
				 16+color,
				 32, // ???
				 map);

	  if (sx>0 && sx<320+16) {
	    for (y = starty ; y != endy ; y += incy)
	      {
		if (y > 0 && y < 240+16) {
		  if (gfx1_solid[code]) {
		    if (gfx1_solid[code] == 1)
		      Draw16x16_Trans_Mapped_flip_Rot(&gfx1[code<<8],sx,y,map,flipx);
		    else
		      Draw16x16_Mapped_flip_Rot(&gfx1[code<<8],sx,y,map,flipx);
		  }
		}
		code++;
	      }
	  }
	}
}

static void (*draw_sprites)();

static void load_multchmp() {
  RAMSize = 0x10000 + 0x1000 + 0x800 + 0x4000*2 + 16 + 0x800;
  if(!(RAM=AllocateMem(RAMSize))) return;

  ram_spr = RAM + 0x11000;
  ram_vram0 = ram_spr + 0x800;
  ram_vram1 = ram_vram0 + 0x4000;
  ram_scroll = ram_vram1 + 0x4000;
  ram_z80 = ram_scroll + 16;

  spriteram16 = (UINT16*)ram_spr;

  // sprites use 16 banks of 32 colors
  // + 2 (?) tilemaps (maybe shared) of 256 colors
  InitPaletteMap(RAM+0x10000, 64, 32,0x8000);
  set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);

  AddMemFetch(0x000000,0x07ffff,ROM);
  AddMemFetch(-1, -1, NULL);

  memset(input_buffer,0xff,8);

  AddReadBW(0x000000, 0x07ffff, NULL, ROM);
  if (!is_current_game("multchmp")) {
    EEPROM_init(&eeprom_interface_93C46);
    load_eeprom();
    memset(load_region[REGION_GFX1] + 0x500000, 0, 0x100000);
  }

  if (is_current_game("mchampdx")) {
    AddRWBW(0x200000, 0x20ffff, NULL, RAM);
    AddRWBW(0x300000, 0x303fff, NULL, ram_vram0);
    AddRWBW(0x320000, 0x323fff, NULL, ram_vram1);
    AddRWBW(0x324000, 0x327fff, NULL, ram_vram1); // mirror ?
    AddRWBW(0x400000, 0x400fff, NULL, RAM+0x10000);
    AddReadBW(0x500002, 0x500005, NULL, input_buffer);
    AddReadByte(0x500006, 0x500006, esd_eeprom_r, NULL);
    AddWriteWord(0x50000c, 0x50000d, esd16_sound_w, NULL);
    AddWriteByte(0x50000e, 0x50000e, esd16_eeprom_w, NULL);
    AddRWBW(0x600000, 0x6007ff, NULL, ram_spr);
    AddRWBW(0x600800, 0x600807, NULL, ram_spr);
    AddRWBW(0x700000, 0x70000f, NULL, ram_scroll);
    AddWriteWord(0xd00008, 0xd00009, hedpanic_platform_w, NULL); // ???

  } else {
    AddRWBW(0x100000, 0x10ffff, NULL, RAM);
    if (is_current_game("hedpanic")) {
      AddRWBW(0x800000, 0x800fff, NULL, RAM+0x10000);
      AddRWBW(0x900000, 0x9007ff, NULL, ram_spr);
      AddRWBW(0x900800, 0x900807, NULL, ram_spr); // a mirror of only 8 bytes ??!!!!!
      AddRWBW(0xa00000, 0xa03fff, NULL, ram_vram0);
      AddRWBW(0xa20000, 0xa23fff, NULL, ram_vram1);
      AddRWBW(0xa24000, 0xa27fff, NULL, ram_vram1);
      AddRWBW(0xb00000, 0xb0000f, NULL, ram_scroll);
      AddReadBW(0xc00002, 0xc00005, NULL, input_buffer);
      AddWriteWord(0xc0000c, 0xc0000d, esd16_sound_w, NULL);
      AddReadByte(0xc00006, 0xc00006, esd_eeprom_r, NULL);
      AddWriteByte(0xc0000e, 0xc0000e, esd16_eeprom_w, NULL);
      AddWriteWord(0xd00008, 0xd00009, hedpanic_platform_w, NULL);
    } else {
      AddRWBW(0x200000, 0x2005ff, NULL, RAM+0x10000);
      AddRWBW(0x300000, 0x3007ff, NULL, ram_spr);
      AddRWBW(0x300800, 0x300807, NULL, ram_spr); // a mirror of only 8 bytes ??!!!!!
      AddRWBW(0x400000, 0x403fff, NULL, ram_vram0);
      AddRWBW(0x420000, 0x423fff, NULL, ram_vram1);
      AddRWBW(0x500000, 0x50000f, NULL, ram_scroll);

      AddReadBW(0x600002, 0x600007, NULL, input_buffer);

      AddWriteWord(0x60000c, 0x60000d, esd16_sound_w, NULL);
    }
  }

  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066);
  z80_init_banks(0, REGION_ROM2, 0x8000, 0x4000);
  AddZ80ARead(0x0000, 0xbfff, NULL, NULL); // rom + bank
  AddZ80ARW(0xf800, 0xffff, NULL, ram_z80);

  AddZ80AReadPort(2, 2, OKIM6295_status_0_r, NULL);
  AddZ80AReadPort(3, 3, esd16_sound_command_r, NULL);
  AddZ80AWritePort(0, 0, YM3812_control_port_0_w, NULL);
  AddZ80AWritePort(1, 1, YM3812_write_port_0_w, NULL);
  AddZ80AWritePort(2, 2, OKIM6295_data_0_w, NULL);
  AddZ80AWritePort(5, 5, z80a_set_bank, NULL);

  finish_conf_68000(0);
  AddZ80AReadByte (0x0000, 0xFFFF, DefBadReadZ80,            NULL);
  AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,           NULL);
  AddZ80AReadPort(-1, -1, NULL, NULL);
  AddZ80AWritePort(-1, -1, NULL, NULL);

  AddZ80AInit();
  AddInitMemory();   // Set Starscream mem pointers...
  ByteSwap(ROM,get_region_size(REGION_CPU1));

  layer_id_data[0] = add_layer_info(gettext("sprites"));
  layer_id_data[1] = add_layer_info(gettext("tilemap0"));
  layer_id_data[2] = add_layer_info(gettext("tilemap1"));
  if (is_current_game("multchmp"))
    draw_sprites = &esd16_draw_sprites;
  else
    draw_sprites = &hedpanic_draw_sprites; // including mchampdx
}

static struct YM3812interface ym3812_interface =
{
   1,              // 1 chip
   4000000,	/**/
   { 150 },        // Volume (emu only)
   { NULL }
};

static struct OKIM6295interface esd16_okim6295_interface =
{
	1,			/* 1 chip */
	{ 8000 },
	{ REGION_SOUND1 },
	{ 170 }
};

static struct SOUND_INFO sound_multchmp[] =
{
   { SOUND_YM3812,  &ym3812_interface,    },
   { SOUND_M6295,    &esd16_okim6295_interface   },
   { 0,              NULL,                 },
};

static void execute_multchmp() {
  cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));	// M68000 12MHz (60fps)
  cpu_interrupt(CPU_68K_0, 6);

  execute_z80_audio_frame_with_nmi(32);
}

static void draw_multchmp() {
  int x16,y16,zzz,zzzz;
  int zz;
  int x,y;
  UINT16 code;
  UINT8 *map;

  ClearPaletteMap();

  // 1 layer is opaque 1024x512, 8x8 sprites
  if (check_layer_enabled(layer_id_data[1])) {
    MAKE_SCROLL_1024x512_2_8(ReadWord(ram_scroll)-0x3a0,ReadWord(&ram_scroll[2])+8);
    MAP_PALETTE_MULTI_MAPPED_NEW(
				 1*8,
				 256,
				 map
				 );
    START_SCROLL_1024x512_2_8(16,16,320,240);
    {
      code = ReadWord(&ram_vram0[zz]);
      Draw8x8_Mapped_Rot(&gfx2[code<<6],x,y,map);
    }
    END_SCROLL_1024x512_2_8();
  } else
      clear_game_screen(0);

  // then same thing transparent (very easy !)
  if (check_layer_enabled(layer_id_data[2])) {
    if (ram_scroll[14] & 2) { // size of layer ?
      MAKE_SCROLL_1024x1024_2_16(ReadWord(&ram_scroll[4])-0x3a0,ReadWord(&ram_scroll[6])+8);
      MAP_PALETTE_MULTI_MAPPED_NEW(
				   0,
				   256,
				   map
				   );
      START_SCROLL_1024x1024_2_16(16,16,320,240);
      {
	code = ReadWord(&ram_vram1[zz]);
	if (gfx3_solid[code]) {
	  if (gfx3_solid[code] == 1)
	    Draw16x16_Trans_Mapped_Rot(&gfx3[code<<8],x,y,map);
	  else
	    Draw16x16_Mapped_Rot(&gfx3[code<<8],x,y,map);
	}
      }
      END_SCROLL_1024x1024_2_16();
    } else {
      MAKE_SCROLL_1024x512_2_8(ReadWord(&ram_scroll[4])-0x3a0,ReadWord(&ram_scroll[6])+8);
      MAP_PALETTE_MULTI_MAPPED_NEW(
				   0,
				   256,
				   map
				   );
      START_SCROLL_1024x512_2_8(16,16,320,240);
      {
	code = ReadWord(&ram_vram1[zz]);
	if (gfx2_solid[code]) {
	  if (gfx2_solid[code] == 1)
	    Draw8x8_Trans_Mapped_Rot(&gfx2[code<<6],x,y,map);
	  else
	    Draw8x8_Mapped_Rot(&gfx2[code<<6],x,y,map);
	}
      }
      END_SCROLL_1024x512_2_8();
    }
  }

  // and the sprites...
  if (check_layer_enabled(layer_id_data[0]))
    draw_sprites();
}

static struct VIDEO_INFO video_multchmp =
{
   draw_multchmp,
   320,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   esd16_gfxdecodeinfo,
};

GMEI( multchmp,
     "Multi Champ (Korea)",
     ESD,
     1998,
     GAME_MISC);

static struct VIDEO_INFO video_mchampdx =
{
   draw_multchmp,
   320,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   hedpanic_gfxdecodeinfo,
};
static struct DIR_INFO dir_hedpanic[] =
{
   { "hedpanic", },
   { NULL, },
};

CLNE( hedpanic, multchmp, "Head Panic (Korea?)", ESD, 2000, GAME_MISC,
	.input = input_mchampdx,
	.video = &video_mchampdx,
);

static struct DIR_INFO dir_mchampdx[] =
{
   { "mchampdx", },
   { NULL, },
};
CLNE( mchampdx, multchmp,"Multi Champ Deluxe", ESD, 1999, GAME_MISC,
	.input = input_mchampdx,
	.video = &video_mchampdx,
);

