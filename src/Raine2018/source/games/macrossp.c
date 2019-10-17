/* Driver taken from mame (original work by David Haywood)
   Notes from mame :
 Whats the BIOS rom? should it be in the 68020 map, its different between
 games.

 68020 interrupts
 lev 1 : 0x64 : 0000 084c - unknown..
 lev 2 : 0x68 : 0000 0882 - unknown..
 lev 3 : 0x6c : 0000 08b0 - vblank?
 lev 4 : 0x70 : 001f 002a - x
 lev 5 : 0x74 : 001f 002a - x
 lev 6 : 0x78 : 001f 002a - x
 lev 7 : 0x7c : 001f 002a - x

Personnal notes (Emmanuel Anne) : this hardware is quite strange.
The layers and the sprites have a "depth toggle bit" which seems to
control how many colors to take to draw the sprites ??!!!

******************************************************************************/

#include "gameinc.h"
#include "f3system.h"
#include "blit.h" // clear_game_screen (necessary when the solid layer is
// disabled by the function keys).
#include "es5506.h"
#include "sasound.h"
#include "zoom/16x16.h"		// 16x8 zoomed sprite routines

static struct ES5506interface es5506_interface =
{
	1,
	{ 16000000 },
	{ REGION_SOUND1 },
	{ REGION_SOUND2 },
	{ REGION_SOUND3 },
	{ REGION_SOUND4 },
	{ YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT) },
	{ NULL /* irqhandler */ },
	/* IRQ lines 1 & 4 on the sound 68000 are definitely triggered by the ES5506,
	but I haven't noticed the ES5506 ever assert the line - maybe only used when developing the game? */
/*	cpu_set_irq_line(1,1,irq ? ASSERT_LINE : CLEAR_LINE); */
	{ 0 }
};

static struct SOUND_INFO sound_macrossp[] =
{
   { SOUND_ES5506,  &es5506_interface,  },
   { 0,             NULL,               },
};

static struct ROM_INFO rom_macrossp[] =
{
  { "bp964a-c.u1", 0x080000, 0x39da35e7 , REGION_ROM1, 0x000003, LOAD_8_32 },
  { "bp964a-c.u2", 0x080000, 0x86d0ca6a , REGION_ROM1, 0x000002, LOAD_8_32 },
  { "bp964a-c.u3", 0x080000, 0xfb895a7b , REGION_ROM1, 0x000001, LOAD_8_32 },
  { "bp964a-c.u4", 0x080000, 0x8c8b966c , REGION_ROM1, 0x000000, LOAD_8_32 },

  LOAD8_16(  REGION_ROM2,  0x000000,  0x080000,
            "bp964a.u21",  0x87bdd2fc, "bp964a.u20",  0x12960cbb ),

  /* Bios : unknown use */
  { "bp964a.u49", 0x020000, 0xad203f76 , REGION_USER1, 0x000000, LOAD_NORMAL },

  { "bp964a.u9", 0x400000, 0xbd51a70d , REGION_GFX1, 0x000003, LOAD_8_32 },
  { "bp964a.u10", 0x400000, 0xab84bba7 , REGION_GFX1, 0x000002, LOAD_8_32 },
  { "bp964a.u11", 0x400000, 0xb9ae1d0b , REGION_GFX1, 0x000001, LOAD_8_32 },
  { "bp964a.u12", 0x400000, 0x8dda1052 , REGION_GFX1, 0x000000, LOAD_8_32 },

  { "bp964a.u13", 0x400000, 0xf4d3c5bf , REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "bp964a.u14", 0x400000, 0x4f2dd1b2 , REGION_GFX2, 0x400000, LOAD_NORMAL },

  { "bp964a.u15", 0x400000, 0x5b97a870 , REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "bp964a.u16", 0x400000, 0xc8a0cd64 , REGION_GFX3, 0x400000, LOAD_NORMAL },

  { "bp964a.u17", 0x400000, 0xf2470876 , REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "bp964a.u18", 0x400000, 0x52ef21f3 , REGION_GFX4, 0x400000, LOAD_NORMAL },

  { "bp964a.u19", 0x080000, 0x19c7acd9 , REGION_GFX5, 0x000000, LOAD_NORMAL },

  { "bp964a.u24", 0x400000, 0x93f90336 , REGION_SMP1, 0x000001, LOAD_8_16 },
  // REGION_SMP2 initialised from REGION_SMP1 in the loading function
  { NULL, 0, 0, 0, 0, 0 }
};

#if 0
// unused
static struct ROM_INFO quizmoon_roms[] =
{
  { "u1.bin", 0x020000, 0xea404553 , REGION_ROM1, 0x000003, LOAD_8_32 },
  { "u2.bin", 0x020000, 0x024eedff , REGION_ROM1, 0x000002, LOAD_8_32 },
  { "u3.bin", 0x020000, 0x545b1d17 , REGION_ROM1, 0x000001, LOAD_8_32 },
  { "u4.bin", 0x020000, 0x60b3d18c , REGION_ROM1, 0x000000, LOAD_8_32 },
  { "u5.bin", 0x080000, 0x4cc65f5e , REGION_ROM1, 0x200003, LOAD_8_32 },
  { "u6.bin", 0x080000, 0xd84b7c6c , REGION_ROM1, 0x200002, LOAD_8_32 },
  { "u7.bin", 0x080000, 0x656b2125 , REGION_ROM1, 0x200001, LOAD_8_32 },

  { "u8.bin", 0x080000, 0x944df309 , REGION_ROM1, 0x200000, LOAD_8_32 },
  { "u20.bin", 0x020000, 0xd7ad1ffb , REGION_ROM2, 0x000000, LOAD_NORMAL },
  { "u21.bin", 0x020000, 0x6fc625c6 , REGION_ROM2, 0x000000, LOAD_NORMAL },

  { "u49.bin", 0x020000, 0x1590ad81 , REGION_ROM2, 0x000000, LOAD_NORMAL },
  { "u9.bin", 0x0400000, 0xaaaf2ca9 , REGION_GFX1, 0x0000003, LOAD_8_32 },
  { "u10.bin", 0x0400000, 0xf0349691 , REGION_GFX1, 0x0000002, LOAD_8_32 },
  { "u11.bin", 0x0400000, 0x893ab178 , REGION_GFX1, 0x0000001, LOAD_8_32 },

  { "u12.bin", 0x0400000, 0x39b731b8 , REGION_GFX1, 0x0000000, LOAD_8_32 },

  { "u13.bin", 0x0400000, 0x3dcbb041 , REGION_GFX2, 0x0000000, LOAD_NORMAL },

  { "u15.bin", 0x0400000, 0xb84224f0 , REGION_GFX3, 0x0000000, LOAD_NORMAL },

  { "u17.bin", 0x0200000, 0xff93c949 , REGION_GFX4, 0x0000000, LOAD_NORMAL },

  { "u24.bin", 0x0400000, 0x5b12d0b1 , REGION_SMP1, 0x0000000, LOAD_NORMAL },
  { "u25.bin", 0x0400000, 0x3b9689bc , REGION_SMP1, 0x0400000, LOAD_NORMAL },
  { "u26.bin", 0x0400000, 0x6c8f30d4 , REGION_SMP1, 0x0800000, LOAD_NORMAL },
  { "u27.bin", 0x0400000, 0xbd75d165 , REGION_SMP1, 0x0c00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

#endif

static struct DSW_DATA dsw_data_macrossp_4[] =
{
  DSW_SCREEN( 0x1, 0x0),
  { MSG_UNKNOWN, 0x2, 2 },
  { MSG_OFF, 0x2},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x4, 2 },
  { MSG_OFF, 0x4},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x8, 2 },
  { MSG_OFF, 0x8},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x0},
  DSW_SERVICE( 0, 0x80),
  { NULL, 0}
};

static struct DSW_DATA dsw_data_macrossp_5[] =
{
  { "2", 0x1, 2 },
  { MSG_OFF, 0x1},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x2, 2 },
  { MSG_OFF, 0x2},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x4, 2 },
  { MSG_OFF, 0x4},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x8, 2 },
  { MSG_OFF, 0x8},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x10, 2 },
  { MSG_OFF, 0x10},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x20, 2 },
  { MSG_OFF, 0x20},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x40, 2 },
  { MSG_OFF, 0x40},
  { MSG_ON, 0x0},
  { MSG_UNKNOWN, 0x80,2 },
  { MSG_ON, 0},
  { MSG_OFF, 0x80},
  { NULL, 0}
};

/* These are the only 2 ports listed in service mode. Except for the
   service mode bit, I could not check anything else */
static struct DSW_INFO dsw_macrossp[] =
{
  { 0x4000c, 0xff, dsw_data_macrossp_4 },
  { 0x4000d, 0xff, dsw_data_macrossp_5 },
  { 0, 0, NULL }
};

/*** GFX DECODE **************************************************************/

static gfx_layout macrossp_char16x16x4layout =
{
	16,16,
	RGN_FRAC(1,1),
	4,
	{ 0,1,2,3 },
	{ 0, 4, 8, 12, 16, 20, 24, 28, 32+0,32+4,32+8,32+12,32+16,32+20,32+24,32+28 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64,
	  8*64, 9*64, 10*64,11*64,12*64,13*64,14*64,15*64},
	16*64
};

static gfx_layout macrossp_char16x16x8layout =
{
	16,16,
	RGN_FRAC(1,1),
	8,
	{ 0,1,2,3,4,5,6,7 },
	{ 0, 8, 16, 24, 32, 40, 48, 56, 64+0,64+8,64+16,64+24,64+32,64+40,64+48,64+56 },
	{ 0*128, 1*128, 2*128, 3*128, 4*128, 5*128, 6*128, 7*128,
	  8*128, 9*128, 10*128,11*128,12*128,13*128,14*128,15*128},
	16*128
};

static struct GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &macrossp_char16x16x8layout,   },	/* 8bpp but 6bpp granularity */
	{ REGION_GFX2, &macrossp_char16x16x8layout,   },	/* 8bpp but 6bpp granularity */
	{ REGION_GFX3, &macrossp_char16x16x8layout,   },	/* 8bpp but 6bpp granularity */
	{ REGION_GFX4, &macrossp_char16x16x8layout,   },	/* 8bpp but 6bpp granularity */
	{ REGION_GFX5, &macrossp_char16x16x4layout,   },
	{ 0,           NULL,             },
};


static struct INPUT_INFO input_macrossp[] =
{
  INP0( P1_UP, 0x40001, 0x01 ),
  INP0( P1_DOWN, 0x40001, 0x02 ),
  INP0( P1_LEFT, 0x40001, 0x04 ),
  INP0( P1_RIGHT, 0x40001, 0x08 ),
  INP0( P1_B1, 0x40001, 0x10 ),
  INP0( P1_B2, 0x40001, 0x20 ),
  INP0( P1_B3, 0x40001, 0x40 ),
  INP0( P1_B4, 0x40001, 0x80 ),
  INP0( P2_UP, 0x40000, 0x01 ),
  INP0( P2_DOWN, 0x40000, 0x02 ),
  INP0( P2_LEFT, 0x40000, 0x04 ),
  INP0( P2_RIGHT, 0x40000, 0x08 ),
  INP0( P2_B1, 0x40000, 0x10 ),
  INP0( P2_B2, 0x40000, 0x20 ),
  INP0( P2_B3, 0x40000, 0x40 ),
  INP0( P2_B4, 0x40000, 0x80 ),

  INP0( P1_START, 0x40003, 0x01 ),
  INP0( P2_START, 0x40003, 0x02 ),
  INP0( COIN1, 0x40003, 0x04 ),
  INP0( COIN2, 0x40003, 0x08 ),

  INP0( SERVICE, 0x40003, 0x20 ),
   END_INPUT
};


static UINT8 *GFX_SPR;
static UINT8 *GFX_SPR_SOLID;

static UINT8 *RAM_SPR,*RAM2;
static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;
static UINT8 *RAM_BG3;

static struct layer {
  UINT8 *ram,*gfx,*solid;
  UINT32 pri,num,max;
} layer[4];

static struct layer sorted[4];

static UINT32 colours = 0x10;
static int nb_sprites;
#define MAX_SPR 0x3000/(4*3)
static UINT8 *sprites_pri[4][MAX_SPR]; // sprites ordered by priorities
static int nb_sprites_pri[4]; // And number of sprites for each priority

static int layer_id_data[5];

static char *layer_id_name[5] =
{
   "SCR-A", "SCR-B", "SCR-C", "TEXT", "SPR"
};

static int sound_latch;

static void macrossp_system(UINT8 data)
{
  if (data == 3) { // sound write
    sound_latch=m68k_dreg(regs,0);

    cpu_interrupt(CPU_68K_0,2);
    // The number of executed cycles is not realy important, thanks to the speed hack
    cpu_execute_cycles(CPU_68K_0,CPU_FRAME_MHz(16,60)); // M68000 16MHz (60fps)
    if (s68000context.pc == 0x336) {
      s68000context.pc = 0x32a;
    }
  } else if (data == 2) { // speed hack
    Stop68020();
  }
}

static void macrossp_stop_68k(UINT32 offset, UINT8 data) {
  // Stop 68k if there is no command to process
  if (ReadLong68k(&RAM2[0x6]) == ReadLong68k(&RAM2[0xa]))
    Stop68000(offset,data);
}

static void load_macrossp() {
  int ta;
  UINT8 *RAM_PAL;
  UINT8 *ROM2 = load_region[REGION_ROM2];

  RAMSize = 0x78000;

  if(!(RAM=AllocateMem(RAMSize+0x10000)))     return;
  if(!(load_region[REGION_SMP2] = AllocateMem(0x400000))) return;

  memcpy(load_region[REGION_SMP2], load_region[REGION_SMP1] + 0x400000,0x400000);

  RAM_SPR = RAM;
  RAM_BG0 = RAM + 0x10000;
  RAM_BG1 = RAM + 0x18000;
  RAM_BG2 = RAM + 0x20000;
  RAM_BG3 = RAM + 0x28000;
  RAM_PAL = RAM + 0x30000;
  RAM2 =    RAM + 0x70000;

  set_colour_mapper(&col_map_24bit_rgb);
  // the text layer has 16 colours, the other layers seem to have 256 colors...
  InitPaletteMap(RAM_PAL, 0x100, 0x100, 0x10000);
  init_16x16_zoom_64(); // Should have zoom...

  ROM = load_region[REGION_CPU1];
  // 68020 memory map... How short !
   for(ta=0;ta<0x100;ta++)
      R24[ta]=W24[ta] = RAM+0x78000;	// SCRATCH RAM

  for(ta=0;ta<=0x3f;ta++)
      R24[ta]=ROM+ta*0x10000;	// 68020 ROM
  R24[0x80] = W24[0x80] = RAM_SPR;
  R24[0x90] = W24[0x90] = RAM_BG0; // bg0 / bg1
  R24[0x91] = W24[0x91] = RAM_BG2; // bg2 / bg3
  R24[0xa0] = W24[0xa0] = RAM_PAL;
  R24[0xb0] = W24[0xb0] = RAM + 0x40000; // inputs and maybe palette fade
  memset(RAM+0x40000,0xff,32); // clear the dsw, inputs, etc...

  R24[0xf0] = W24[0xf0] = RAM + 0x50000; // RAM
  R24[0xf1] = W24[0xf1] = RAM + 0x60000; // RAM

  init_m68k();

  // speed hack
  // first disable the funny b00007 port, probably related to some
  // interrupt generated by the sprites hardware. It slows down the emulation
  // and I don't sse what to do with it...
  WriteWord68k(&ROM[0x18264],0x4e75); // rts
  WriteWord68k(&ROM[0x1866a],0x4e71); // nop
  WriteWord68k(&ROM[0x18a44],0x4e71); // nop
  WriteWord68k(&ROM[0x18c52],0x4e71); // nop
  WriteWord68k(&ROM[0x18d48],0x4e71); // nop
/*   WriteWord68k(&ROM[0x197ce],0x4e71); // nop */
/*   WriteWord68k(&ROM[0x197d0],0x4e71); // nop */

  WriteWord68k(&ROM[0x197d2],0x7f03); // sound write (raine #03)
  WriteWord68k(&ROM[0x197d4],0x4e71); // nop
  WriteWord68k(&ROM[0x197d6],0x4e71); // nop

  // Now actually install the speed hack
  WriteWord68k(&ROM[0x18110],0x7F02);		//	raine	#$02 <stop cpu>

  F3SystemEEPROMAccess = macrossp_system;

  layer[0].ram = RAM_BG0;
  layer[0].solid = NULL;
  layer[0].num = 0;

  layer[1].ram = RAM_BG1;
  layer[1].num = 1;

  layer[2].ram = RAM_BG2;
  layer[2].num = 2;

  layer[3].ram = RAM_BG3; // layer 3 is always BG3 (text layer)
  memcpy(&sorted[3],&layer[3],sizeof(struct layer));
  for (ta=0; ta<5; ta++)
    layer_id_data[ta] = add_layer_info(layer_id_name[ta]);

  // Sound 68000
  ByteSwap(ROM2,get_region_size(REGION_ROM2));

  WriteWord(&ROM2[0x330],0x4239); // clr.b $aa0000
  WriteWord(&ROM2[0x332],0xaa);
  WriteWord(&ROM2[0x334],0);

  WriteWord(&ROM2[0x336],0x4e71); // nops
  WriteWord(&ROM2[0x338],0x4e71);

  AddMemFetch(0x000000,0x0fffff,ROM2);
  AddMemFetch(-1, -1, NULL);

  AddReadBW(   0x000000, 0x0fffff, NULL, ROM2);
  AddRWBW(     0x200000, 0x207fff, NULL, RAM2);
  AddReadBW(   0x400000, 0x40007f, ES5506_data_0_word_r, NULL);
  AddWriteWord(0x400000, 0x40007f, ES5506_data_0_word_w, NULL);
  AddReadBW(   0x600000, 0x600001, NULL, (UINT8*)&sound_latch);
  AddWriteByte(0xAA0000, 0xAA0001, macrossp_stop_68k, NULL);   // Trap Idle 68000

  AddRWBW(-1, -1, NULL, NULL);
  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);      // <Bad Reads>
  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);      // <Bad Reads>
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);    // <Bad Writes>
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);    // <Bad Writes>

  AddInitMemory();   // Set Starscream mem pointers...
}

#define BORDER 16

int layer_cmp(const void *a, const void *b) {
  return ((struct layer *)a)->pri - ((struct layer *)b)->pri;
}

static void draw_solid(struct layer *layer) {
  UINT8 *ram = layer->ram,*map;
  UINT8 *gfx = layer->gfx;
  UINT16 attr = ReadWord68k(&ram[0x5002]);
  int zz,zzz,zzzz,x16,y16,x,y;

  if(! check_layer_enabled(layer_id_data[layer->num])) {
    clear_game_screen(0);
    return;
  }

  MAKE_SCROLL_n_16(1024,1024,4,attr & 0x3ff,
			     ReadWord68k(&ram[0x5000]) & 0x3ff);
  START_SCROLL_16(BORDER,BORDER,384,240);
  // these are banks of 64 colors and the palette was initialised for banks
  // of 16 colors. The banks go from 0 to 1f (I hope !).

    switch(ram[0x5002] & 0xc) {
    case 8:
      MAP_PALETTE_MAPPED_NEW(
			     ((ReadWord68k(&ram[zz]) & 0xe)<<3)|0x80,
			     colours*16,
			     map
			     );
      break;
    default:
    MAP_PALETTE_MAPPED_NEW(
			   ((ReadWord68k(&ram[zz]) & 0xfe)>>1)| 0x80,
              colours*4,
              map
            );
    }
  Draw16x16_Mapped_flip_Rot(&gfx[ReadWord68k(&ram[zz+2])<<8], x, y, map, ram[zz] & 0xc0>>6);
  END_SCROLL_n_16(1024,1024,4);
}

static void draw_normal(struct layer *layer) {
  UINT16 ta;
  UINT8 *ram = layer->ram,*map;
  UINT8 *gfx = layer->gfx;
  UINT8 *solid = layer->solid;
  UINT16 attr = ReadWord68k(&ram[0x5002]);
  int zz,zzz,zzzz,x16,y16,x,y;

  if(! check_layer_enabled(layer_id_data[layer->num]))
    return;

  MAKE_SCROLL_n_16(1024,1024,4,attr & 0x3ff,
			     ReadWord68k(&ram[0x5000]) & 0x3ff);
  START_SCROLL_16(BORDER,BORDER,384,240);

  ta = ReadWord68k(&ram[zz+2]);
  if (solid[ta]) {
    switch(ram[0x5002] & 0xc) {
    case 8:
      MAP_PALETTE_MAPPED_NEW(
			     ((ReadWord68k(&ram[zz]) & 0xe)<<3)|0x80,
			     colours*16,
			     map
			     );
      break;
    default:
      MAP_PALETTE_MAPPED_NEW(
			     ((ReadWord68k(&ram[zz]) & 0xfe)>>1)|0x80,
			     colours*16,
			     map
			     );
      break;
    }
    if (solid[ta] == 1)
      Draw16x16_Trans_Mapped_flip_Rot(&gfx[ta<<8], x, y, map, ram[zz] & 0xc0>>6);
    else
      Draw16x16_Mapped_flip_Rot(&gfx[ta<<8], x, y, map, ram[zz] & 0xc0>>6);
  }
  END_SCROLL_n_16(1024,1024,4);
}

static void draw_text_layer(struct layer *layer) {
  UINT16 ta;
  UINT8 *ram = layer->ram,*map;
  UINT8 *gfx = layer->gfx;
  UINT8 *solid = layer->solid;
  UINT16 attr = ReadWord68k(&ram[0x5002]),max = layer->max;
  int zz,zzz,zzzz,x16,y16,x,y;

  if(! check_layer_enabled(layer_id_data[layer->num]))
    return;

  MAKE_SCROLL_n_16(1024,1024,4,attr & 0x3ff,
			     ReadWord68k(&ram[0x5000]) & 0x3ff);
  START_SCROLL_16((BORDER+16),BORDER,384,240);

  ta = ReadWord68k(&ram[zz+2]);
  if (ta > max) {
    continue;
  }
  if (solid[ta]) {
    MAP_PALETTE_MAPPED_NEW(
			   ((ram[zz+1] & 0xfe)>>1) | 0x80,
			     colours,
			     map
			     );
    if (solid[ta] == 1)
      Draw16x16_Trans_Mapped_Rot(&gfx[ta<<8], x, y, map);
    else
      Draw16x16_Mapped_Rot(&gfx[ta<<8], x, y, map);
  }
  END_SCROLL_n_16(1024,1024,4);
}

static void draw_sprites(int pri) {
  UINT8 *ptr,*end,*map;
  int ta;
  UINT16 wide, high, zoomx,zoomy, nb, flipx,flipy,flip;
  INT16 x,y, startx, starty, endx, endy, incx, incy, xcnt, ycnt;

  if(! check_layer_enabled(layer_id_data[4]))
    return;

  if (pri == 0) {
    ptr = RAM_SPR;
    end = RAM_SPR + 0x3000;
    memset(nb_sprites_pri,0,sizeof(nb_sprites_pri));
    while (ptr < end) {
      int pri = (ptr[8] & 0x0c)>>2;
      sprites_pri[pri][nb_sprites_pri[pri]++] = ptr;
      ptr += 4*3;
    }
  }

  for (ta=0; ta<nb_sprites_pri[pri]; ta++) {
    ptr = sprites_pri[pri][ta];
    high = (*ptr & 0x3c)>>2;
    wide = (ptr[2] & 0x3c) >> 2;
    y    = ReadWord68k(ptr) & 0x3ff;
    x    = ReadWord68k(ptr + 2) & 0x3ff;
    zoomy= ReadWord68k(ptr + 4) & 0x3ff;
    zoomx= ReadWord68k(ptr + 6) & 0x3ff;
    zoomx= ((zoomx*16+(1<<7))>>8);
    zoomy= ((zoomy*16+(1<<7))>>8);
    nb   = ReadWord68k(ptr + 10);
    flipx= ptr[8] & 0x40;
    flipy= ptr[8] & 0x80;
    flip = 0;
    // unknown = 0;

    // the mapping here is strange. The sprites have 0x80 banks of 16 colors
    // available, and they seem to pass a bank from 0 to 1f ?
    switch (ptr[2] & 0xc0) {
    case 0x80:
      MAP_PALETTE_MAPPED_NEW(
			     (ptr[9] & 0x38)<<1,
			     colours*4,
			     map); // 64 colours, maybe 256...
      break;
    case 0x40:
      MAP_PALETTE_MAPPED_NEW(
			     (ptr[9] & 0xf8)>>1,
			     colours*4,
			     map); // 64 colours, maybe 256...
      break;
    default:
      //unknown = 1;
      MAP_PALETTE_MAPPED_NEW(
			     (ptr[9] & 0x78),
			     colours*4,
			     map); // 64 colours, maybe 256...

    }
    if (x>0x1ff) x-=0x400;
    if (y>0x1ff) y-=0x400;

    x+= 16;
    y+= 16;

    if (flipy) {
      starty = high; endy = 0-1; incy = -1;
      flip |= 1;
    } else {
      starty = 0; endy = high+1; incy = 1;
    }

    if (flipx) {
      startx = wide; endx = 0-1; incx = -1;
      flip |= 2;
    } else {
      startx = 0; endx = wide+1; incx = 1;
    }

    for (ycnt = starty; ycnt != endy; ycnt += incy) {
      for (xcnt = startx; xcnt != endx; xcnt += incx) {
	INT16 px = x + xcnt*zoomx - (zoomx-16)/2;
	INT16 py = y + ycnt*zoomy  - (zoomy-16)/2;
	if (px >= 0 && px <= 384+16 && py>= 0 && py <= 240+16) {
	  if (GFX_SPR_SOLID[nb] == 1) {
	    Draw16x16_64_Trans_Mapped_ZoomXY_flip_Rot(&GFX_SPR[nb<<8],px,py,
						      map,zoomx,zoomy,flip);
/* 	    if (unknown) { */
/* 	      sprintf(buff,"%02x",ptr[9]); */
/* 	      textout_fast(buff,py,384-px+16,get_white_pen()); */
/* 	    } */
	  } else if (GFX_SPR_SOLID[nb] == 2) {
	    Draw16x16_64_Mapped_ZoomXY_flip_Rot(&GFX_SPR[nb<<8],px,py,map,
						zoomx,zoomy,flip);
/* 	    if (unknown) { */
/* 	      sprintf(buff,"%02x",ptr[9]); */
/* 	      textout_fast(buff,py,384-px+16,get_white_pen()); */
/* 	    } */
	  } /* else */
/* 	    textout_fast("R",py-32,384-px+16,get_white_pen()); */
	}
	nb++;
      }
    }
  } // for (ta=0; ta < nb_sprites_pri...
}

static void draw_macrossp() {
  if (!layer[0].solid) {
    int n;
    for (n=0; n<4; n++) {
      layer[n].gfx = gfx[n+1];
      layer[n].solid = gfx_solid[n+1];
      layer[n].max = get_region_size(REGION_GFX2+n)/0x100;
    }
    GFX_SPR = gfx[0];
    GFX_SPR_SOLID = gfx_solid[0];
    nb_sprites = get_region_size(REGION_GFX1)/0x100;
  }
  memcpy(&sorted,&layer,sizeof(struct layer)*3);

  sorted[0].pri = RAM_BG0[0x5002] & 0xc0;
  sorted[1].pri = RAM_BG1[0x5002] & 0xc0;
  sorted[2].pri = RAM_BG2[0x5002] & 0xc0;
  qsort(&sorted,3,sizeof(struct layer),layer_cmp);

  ClearPaletteMap();
  draw_solid(&sorted[0]);
  draw_sprites(0);
  draw_normal(&sorted[1]);
  draw_sprites(1);
  draw_normal(&sorted[2]);
  draw_sprites(2);
  draw_sprites(3); // strange (priorities 2 and 3 are drawn together)
  draw_text_layer(&layer[3]);
}


static void execute_macrossp() {
  cpu_execute_cycles(CPU_M68020_0, CPU_FRAME_MHz(50,60));
  cpu_interrupt(CPU_M68020_0, 3);

  cpu_execute_cycles(CPU_68K_0,CPU_FRAME_MHz(16,60)); // M68000 16MHz (60fps)
  if (s68000context.pc == 0x336) {
    // Speed hack stops here, we loop around here
    s68000context.pc = 0x32a;
  }
  print_debug("PC1:%06x SR:%04x\n",s68000context.pc,s68000context.sr);
}

static struct VIDEO_INFO video_macrossp =
{
   draw_macrossp,
   384,
   240,
   BORDER,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   gfxdecodeinfo,
};
GMEI( macrossp, "Macross plus", BANPREST, 1996, GAME_SHOOT);

