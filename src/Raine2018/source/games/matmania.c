/* This driver is to test 2 6502 working together. Works quite good.
   Thanks to mame for the description of the hardware
   The "specialities" : the 2 cpus have a speed hack, and I am obliged to use
   the switch_cpu function in the sh_command_w handler to trigger an interrupt
   on the 2nd cpu while the first continues to execute its cycles... */
/***************************************************************************

Mat Mania
Memetron, 1985
(copyright Taito, licensed by Technos, distributed by Memetron)

driver by Brad Oliver

MAIN BOARD:

0000-0fff RAM
1000-13ff Video RAM
1400-17ff Attribute RAM
1800-1fff ?? Only used in self-test ??
2000-21ff Background video RAM #1
2200-23ff Background attribute RAM #1
2400-25ff Background video RAM #2
2600-27ff Background attribute RAM #2
4000-ffff ROM

***************************************************************************/

#include "gameinc.h"
#include "blit.h" // clear_game_screen
#include "sasound.h"
#include "ay8910.h"
#include "m6502hlp.h"
#include "dac.h"

static struct ROM_INFO rom_matmania[] =
    {
      { "k0-03", 0x4000, 0x314ab8a4, REGION_ROM1, 0x0000, LOAD_NORMAL },
      { "k1-03", 0x4000, 0x3b3c3f08, REGION_ROM1, 0x4000, LOAD_NORMAL },
      { "k2-03", 0x4000, 0x286c0917, REGION_ROM1, 0x8000, LOAD_NORMAL },
      { "k4-0", 0x4000, 0x86dab489, REGION_ROM2, 0x0000, LOAD_NORMAL },
      { "k5-0", 0x4000, 0x4c41cdba, REGION_ROM2, 0x4000, LOAD_NORMAL },
      { "ku-02", 0x2000, 0x613c8698, REGION_GFX1, 0x00000, LOAD_NORMAL },
      { "kv-02", 0x2000, 0x274ce14b, REGION_GFX1, 0x02000, LOAD_NORMAL },
      { "kw-02", 0x2000, 0x7588a9c4, REGION_GFX1, 0x04000, LOAD_NORMAL },
      { "kt-02", 0x4000, 0x5d817c70, REGION_GFX2, 0x00000, LOAD_NORMAL },
      { "ks-02", 0x4000, 0x2e9f3ba0, REGION_GFX2, 0x04000, LOAD_NORMAL },
      { "kr-02", 0x4000, 0xb057d3e3, REGION_GFX2, 0x08000, LOAD_NORMAL },
      { "k6-00", 0x4000, 0x294d0878, REGION_GFX3, 0x00000, LOAD_NORMAL },
      { "k7-00", 0x4000, 0x0908c2f5, REGION_GFX3, 0x04000, LOAD_NORMAL },
      { "k8-00", 0x4000, 0xae8341e1, REGION_GFX3, 0x08000, LOAD_NORMAL },
      { "k9-00", 0x4000, 0x752ac2c6, REGION_GFX3, 0x0c000, LOAD_NORMAL },
      { "ka-00", 0x4000, 0x46a9cb16, REGION_GFX3, 0x10000, LOAD_NORMAL },
      { "kb-00", 0x4000, 0xbf016772, REGION_GFX3, 0x14000, LOAD_NORMAL },
      { "kc-00", 0x4000, 0x8d08bce7, REGION_GFX3, 0x18000, LOAD_NORMAL },
      { "kd-00", 0x4000, 0xaf1d6a60, REGION_GFX3, 0x1c000, LOAD_NORMAL },
      { "ke-00", 0x4000, 0x614f19b0, REGION_GFX3, 0x20000, LOAD_NORMAL },
      { "kf-00", 0x4000, 0xbdf58c18, REGION_GFX3, 0x24000, LOAD_NORMAL },
      { "kg-00", 0x4000, 0x2189f5cf, REGION_GFX3, 0x28000, LOAD_NORMAL },
      { "kh-00", 0x4000, 0x6b11ed1f, REGION_GFX3, 0x2c000, LOAD_NORMAL },
      { "ki-00", 0x4000, 0xd7ac4ec5, REGION_GFX3, 0x30000, LOAD_NORMAL },
      { "kj-00", 0x4000, 0x2caee05d, REGION_GFX3, 0x34000, LOAD_NORMAL },
      { "kk-00", 0x4000, 0xeb54f010, REGION_GFX3, 0x38000, LOAD_NORMAL },
      { "kl-00", 0x4000, 0xfa4c7e0c, REGION_GFX3, 0x3c000, LOAD_NORMAL },
      { "km-00", 0x4000, 0x6d2369b6, REGION_GFX3, 0x40000, LOAD_NORMAL },
      { "kn-00", 0x4000, 0xc55733e2, REGION_GFX3, 0x44000, LOAD_NORMAL },
      { "ko-00", 0x4000, 0xed3c3476, REGION_GFX3, 0x48000, LOAD_NORMAL },
      { "kp-00", 0x4000, 0x9c84a969, REGION_GFX3, 0x4c000, LOAD_NORMAL },
      { "kq-00", 0x4000, 0xfa2f0003, REGION_GFX3, 0x50000, LOAD_NORMAL },
      { "matmania.1", 0x0020, 0x1b58f01f, REGION_PROMS, 0x0000, LOAD_NORMAL },
      { "matmania.5", 0x0020, 0x2029f85f, REGION_PROMS, 0x0020, LOAD_NORMAL },
      { "matmania.2", 0x0020, 0xb6ac1fd5, REGION_PROMS, 0x0040, LOAD_NORMAL },
      { "matmania.16", 0x0020, 0x09325dc2, REGION_PROMS, 0x0060, LOAD_NORMAL },
      { NULL, 0, 0, 0, 0, 0 }
    };

static struct ROM_INFO rom_excthour[] =
  {
    { "e29", 0x4000, 0xc453e855, REGION_ROM1, 0x00000, LOAD_NORMAL },
    { "e28", 0x4000, 0x17b63708, REGION_ROM1, 0x04000, LOAD_NORMAL },
    { "e27", 0x4000, 0x269ab3bc, REGION_ROM1, 0x08000, LOAD_NORMAL },
    { "k4-0", 0x4000, 0x86dab489, REGION_ROM2, 0x0000, LOAD_NORMAL },
    { "k5-0", 0x4000, 0x4c41cdba, REGION_ROM2, 0x4000, LOAD_NORMAL },
    { "e30", 0x2000, 0xb2875329, REGION_GFX1, 0x00000, LOAD_NORMAL },
    { "e31", 0x2000, 0xc9506de8, REGION_GFX1, 0x02000, LOAD_NORMAL },
    { "e32", 0x2000, 0x00d1635f, REGION_GFX1, 0x04000, LOAD_NORMAL },
    { "e5", 0x4000, 0x0604dc55, REGION_GFX2, 0x00000, LOAD_NORMAL },
    { "ks-02", 0x4000, 0x2e9f3ba0, REGION_GFX2, 0x04000, LOAD_NORMAL },
    { "e3", 0x4000, 0xebd273c6, REGION_GFX2, 0x08000, LOAD_NORMAL },
    { "k6-00", 0x4000, 0x294d0878, REGION_GFX3, 0x00000, LOAD_NORMAL },
    { "k7-00", 0x4000, 0x0908c2f5, REGION_GFX3, 0x04000, LOAD_NORMAL },
    { "k8-00", 0x4000, 0xae8341e1, REGION_GFX3, 0x08000, LOAD_NORMAL },
    { "k9-00", 0x4000, 0x752ac2c6, REGION_GFX3, 0x0c000, LOAD_NORMAL },
    { "ka-00", 0x4000, 0x46a9cb16, REGION_GFX3, 0x10000, LOAD_NORMAL },
    { "kb-00", 0x4000, 0xbf016772, REGION_GFX3, 0x14000, LOAD_NORMAL },
    { "kc-00", 0x4000, 0x8d08bce7, REGION_GFX3, 0x18000, LOAD_NORMAL },
    { "kd-00", 0x4000, 0xaf1d6a60, REGION_GFX3, 0x1c000, LOAD_NORMAL },
    { "ke-00", 0x4000, 0x614f19b0, REGION_GFX3, 0x20000, LOAD_NORMAL },
    { "kf-00", 0x4000, 0xbdf58c18, REGION_GFX3, 0x24000, LOAD_NORMAL },
    { "kg-00", 0x4000, 0x2189f5cf, REGION_GFX3, 0x28000, LOAD_NORMAL },
    { "kh-00", 0x4000, 0x6b11ed1f, REGION_GFX3, 0x2c000, LOAD_NORMAL },
    { "ki-00", 0x4000, 0xd7ac4ec5, REGION_GFX3, 0x30000, LOAD_NORMAL },
    { "kj-00", 0x4000, 0x2caee05d, REGION_GFX3, 0x34000, LOAD_NORMAL },
    { "kk-00", 0x4000, 0xeb54f010, REGION_GFX3, 0x38000, LOAD_NORMAL },
    { "kl-00", 0x4000, 0xfa4c7e0c, REGION_GFX3, 0x3c000, LOAD_NORMAL },
    { "km-00", 0x4000, 0x6d2369b6, REGION_GFX3, 0x40000, LOAD_NORMAL },
    { "kn-00", 0x4000, 0xc55733e2, REGION_GFX3, 0x44000, LOAD_NORMAL },
    { "ko-00", 0x4000, 0xed3c3476, REGION_GFX3, 0x48000, LOAD_NORMAL },
    { "kp-00", 0x4000, 0x9c84a969, REGION_GFX3, 0x4c000, LOAD_NORMAL },
    { "kq-00", 0x4000, 0xfa2f0003, REGION_GFX3, 0x50000, LOAD_NORMAL },
    { "matmania.1", 0x0020, 0x1b58f01f, REGION_PROMS, 0x0000, LOAD_NORMAL },
    { "matmania.5", 0x0020, 0x2029f85f, REGION_PROMS, 0x0020, LOAD_NORMAL },
    { "matmania.2", 0x0020, 0xb6ac1fd5, REGION_PROMS, 0x0040, LOAD_NORMAL },
    { "matmania.16", 0x0020, 0x09325dc2, REGION_PROMS, 0x0060, LOAD_NORMAL },
    { NULL, 0, 0, 0, 0, 0 }
  };

static struct INPUT_INFO input_matmania[] =
  {
    INP0( P1_RIGHT, 0x00, 0x01 ),
    INP0( P1_LEFT, 0x00, 0x02 ),
    INP0( P1_UP, 0x00, 0x04 ),
    INP0( P1_DOWN, 0x00, 0x08 ),
    INP0( P1_B1, 0x00, 0x10 ),
    INP0( P1_B2, 0x00, 0x20 ),
    INP0( COIN2, 0x00, 0x40 ),
    INP0( COIN1, 0x00, 0x80 ),

    INP0( P2_RIGHT, 0x10, 0x01 ),
    INP0( P2_LEFT, 0x10, 0x02 ),
    INP0( P2_UP, 0x10, 0x04 ),
    INP0( P2_DOWN, 0x10, 0x08 ),
    INP0( P2_B1, 0x10, 0x10 ),
    INP0( P2_B2, 0x10, 0x20 ),
    INP0( P1_START, 0x10, 0x40 ),
    INP0( P2_START, 0x10, 0x80 ),

    END_INPUT
  };

static GfxLayout charlayout =
  {
    8,8,	/* 8*8 characters */
    1024,	/* 1024 characters */
    3,	/* 3 bits per pixel */
    { 2*1024*8*8, 1024*8*8, 0 },	/* the bitplanes are separated */
    { 0, 1, 2, 3, 4, 5, 6, 7 },
    { 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },
    8*8	/* every char takes 8 consecutive bytes */
  };

static GfxLayout tilelayout =
  {
    16,16,  /* 16*16 tiles */
    512,    /* 512 tiles */
    3,	/* 3 bits per pixel */
    { 2*512*16*16, 512*16*16, 0 },	/* the bitplanes are separated */
    { 16*8+0, 16*8+1, 16*8+2, 16*8+3, 16*8+4, 16*8+5, 16*8+6, 16*8+7,
      0, 1, 2, 3, 4, 5, 6, 7 },
    { 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
      8*8, 9*8, 10*8, 11*8, 12*8, 13*8, 14*8, 15*8 },
    32*8	/* every tile takes 16 consecutive bytes */
  };

static GfxLayout matmania_spritelayout =
  {
    16,16,  /* 16*16 sprites */
    3584,    /* 3584 sprites */
    3,	/* 3 bits per pixel */
    { 2*3584*16*16, 3584*16*16, 0 },	/* the bitplanes are separated */
    { 16*8+0, 16*8+1, 16*8+2, 16*8+3, 16*8+4, 16*8+5, 16*8+6, 16*8+7,
      0, 1, 2, 3, 4, 5, 6, 7 },
    { 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
      8*8, 9*8, 10*8, 11*8, 12*8, 13*8, 14*8, 15*8 },
    32*8	/* every sprite takes 16 consecutive bytes */
  };

static struct GFX_LIST matmania_gfxdecodeinfo[] =
  {
    { REGION_GFX1, &charlayout }, // 4 color banks
    { REGION_GFX2, &tilelayout }, // 4 color banks
    { REGION_GFX3, &matmania_spritelayout }, // 2 color banks
    { 0, NULL } /* end of array */
  };

static struct DSW_DATA dsw_data_matmania_2[] =
  {
    { MSG_DIFFICULTY, 0x03, 4 },
    { _("Easy") , 0x03},
    { _("Medium") , 0x02},
    { _("Hard") , 0x01},
    { _("Hardest") , 0x00},
    { MSG_UNKNOWN, 0x04, 2 },
    { MSG_OFF, 0x04},
    { MSG_ON, 0x00},
    { MSG_UNKNOWN, 0x08, 2 },
    { MSG_OFF, 0x08},
    { MSG_ON, 0x00},
    { MSG_UNKNOWN, 0x10, 2 },
    { MSG_OFF, 0x10},
    { MSG_ON, 0x00},
    { MSG_UNKNOWN, 0x20, 2 },
    { MSG_OFF, 0x20},
    { MSG_ON, 0x00},
    { MSG_UNKNOWN, 0x40, 2 },
    { MSG_OFF, 0x40},
    { MSG_ON, 0x00},
    { MSG_UNKNOWN, 0x80, 2 },
    { MSG_OFF, 0x80},
    { MSG_ON, 0x00},
    { NULL, 0}
  };

static struct DSW_DATA dsw_data_matmania_3[] =
  {
    { MSG_COIN1, 0x03, 4 },
    { MSG_2COIN_1PLAY, 0x00},
    { MSG_1COIN_1PLAY, 0x03},
    { MSG_1COIN_1PLAY, 0x02},
    { MSG_1COIN_3PLAY, 0x01},
    { MSG_COIN2, 0x0c, 4 },
    { MSG_2COIN_1PLAY, 0x00},
    { MSG_1COIN_1PLAY, 0x0c},
    { MSG_1COIN_1PLAY, 0x08},
    { MSG_1COIN_3PLAY, 0x04},
    { MSG_DEMO_SOUND, 0x10, 2 },
    { MSG_OFF, 0x00},
    { MSG_ON, 0x10},
    { MSG_CABINET, 0x20, 2 },
    { MSG_UPRIGHT, 0x00},
    { MSG_TABLE, 0x20},
    { MSG_SERVICE, 0x40,2 },
    { MSG_ON, 0},
    { MSG_OFF, 0x40},
    { NULL, 0}
  };

static struct DSW_INFO dsw_matmania[] =
  {
    { 0x20, 0xff, dsw_data_matmania_2 },
    { 0x30, 0x5f, dsw_data_matmania_3 },
    { 0, 0, NULL }
  };

static UINT8 *RAM_SPR,*RAM_BG0,*RAM_BG1,*RAM_BG2,*RAM_COL,*RAM_COL2,*RAM_COL3;
static UINT8 *page_select,*RAM_SCR,*PAL;
static UINT8 *GFX_BG0, *GFX_BG1, *GFX_SPR;
static UINT8 *GFX_BG0_SOLID, *GFX_BG1_SOLID, *GFX_SPR_SOLID,*RAM2;

static void matmania_sh_command_w(UINT32 offset, UINT16 data)
{
  data &= 0xff;
  RAM2[0x2007] = data;
  cpu_interrupt(CPU_M6502_1,1);
  switch_cpu(CPU_M6502_0);
}

static void matmania_dac_w(UINT32 offset, UINT16 data)
{
  DAC_signed_data_w(0,data & 0xff);
}

static UINT16 private_pal[10*8],palette_updated;

static void matmania_paletteram_w(UINT32 offset, UINT16 data) {
  int val;
  int r,g,b;
  int offs2;


  if (RAM[offset] != data) {
    palette_updated = 1;
    RAM[offset] = data;
    offs2 = offset & 0x0f;

    val = PAL[offs2];
    r = val & 0xf;

    val = PAL[offs2 | 0x10];
    g = val & 0xf;

    val = PAL[offs2 | 0x20];
    b = val & 0xf;

    private_pal[offs2 + 64] = (r<<8) | (g<<4) | b;
  }
}

static void hack1(UINT32 adr) {
  RAM[adr]=0x8D;	// STA $FFFC
  RAM[adr+1]=0xFC;
  RAM[adr+2]=0xFF;

  RAM[adr+3]=0xea; // nop
  RAM[adr+4]=0xea; // nop
}

static void nops(UINT32 adr) {
  RAM[adr]=0xea; // nop
  RAM[adr+1]=0xea; // nop
  RAM[adr+2]=0xea; // nop
  RAM[adr+3]=0xea; // nop
  RAM[adr+4]=0xea; // nop
}

static int stopped_6502;

static void stop_6502(UINT32 offset, UINT16 data) {
  stopped_6502 = 1;
  StopM6502(offset,data);
}

static int layer_id_data[3];

static void load_matmania() {
  RAMSize = 0x20000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  layer_id_data[0] = add_layer_info(gettext("BG"));
  layer_id_data[1] = add_layer_info(gettext("SPRITES"));
  layer_id_data[2] = add_layer_info(gettext("TEXT"));

  memset(RAM,0,RAMSize);
  RAM2 = RAM + 0x10000;

  RAM_SPR = RAM + 0x780;
  RAM_BG1 = RAM + 0x1000;
  RAM_BG0 = RAM + 0x2000;
  RAM_BG2 = RAM + 0x2400;

  RAM_COL2 = RAM + 0x1400;
  RAM_COL = RAM + 0x2200;
  RAM_COL3 = RAM + 0x2600;

  RAM_SCR = RAM + 0x3020;
  PAL = RAM + 0x3050;

  GFX_BG0_SOLID = NULL;

  page_select = RAM + 0x3000;
  AddM6502AROMBase(RAM);

  AddM6502ARead(0x3000, 0x3030, NULL, input_buffer);

  AddM6502AWrite(0x3010, 0x3010, matmania_sh_command_w, NULL);
  AddM6502AWrite(0,0x302f,NULL,RAM);
  AddM6502AWrite(0x3050, 0x307f, matmania_paletteram_w, NULL);

  memcpy(RAM + 0x4000, load_region[REGION_ROM1], 0xc000);

  // These speed hacks stop the cpu everytime it tries to test the vbl bit in $3030
  if (is_current_game("matmania")) {
    // speed hack
    hack1(0xab56);
    nops(0xab64);

    hack1(0xab75);
    nops(0xab7d);

    hack1(0xab99);
    nops(0xaba1);

    hack1(0xabbe);
    nops(0xabc3);

    hack1(0xae3c);
    nops(0xae41);

    hack1(0xf899);
    nops(0xf89e);

    hack1(0xf9cd);
    nops(0xf9d2);
  } else { // exciting hour
    hack1(0xab4d);
    nops(0xab5b);

    hack1(0xab6c);
    nops(0xab74);

    hack1(0xab90);
    nops(0xab98);

    hack1(0xabb5);
    nops(0xabba);

    hack1(0xae33);
    nops(0xae38);

    hack1(0xf88b);
    nops(0xf890);

    hack1(0xf9bf);
    nops(0xf9c4);
  }

  AddM6502ARead(    -1,     -1, NULL,                        NULL);
  AddM6502AWriteByte(0xFFFC, 0xFFFC, stop_6502,             NULL);
  AddM6502AWriteByte(0x0000, 0xFFFF, DefBadWriteM6502,           NULL);
  AddM6502AWriteByte(    -1,     -1, NULL,                       NULL);

  // 2nd cpu !
  AddM6502BROMBase(RAM2);
  memcpy(RAM2 + 0x8000, load_region[REGION_ROM2], 0x8000);

  // speed hack
  SetStopM6502BMode2(0x8057);
  RAM2[0x8058]=0x8D;	// STA $FFFC
  RAM2[0x8059]=0xFC;
  RAM2[0x805a]=0xFF;

  AddM6502BWrite(0, 0x1ff, NULL, RAM2);
  AddM6502BWrite(0x2000, 0x2000, AY8910_write_port_0_w, NULL);
  AddM6502BWrite(0x2001, 0x2001, AY8910_control_port_0_w, NULL);
  AddM6502BWrite(0x2002, 0x2002, AY8910_write_port_1_w, NULL);
  AddM6502BWrite(0x2003, 0x2003, AY8910_control_port_1_w, NULL);
  AddM6502BWrite(0x2004, 0x2004, matmania_dac_w, NULL);
  AddM6502BRead(    -1,     -1, NULL,                        NULL);
  AddM6502BWriteByte(0xFFFC, 0xFFFC, StopM6502BMode2,            NULL);
  AddM6502BWriteByte(0x0000, 0xFFFF, DefBadWriteM6502,           NULL);
  AddM6502BWriteByte(    -1,     -1, NULL,                       NULL);
  AddM6502AInit();
  AddM6502BInit();

  /* init the palette (the begining)
     From mame :

     Mat Mania is unusual in that it has both PROMs and RAM to control the
     palette. PROMs are used for characters and background tiles, RAM for
     sprites.
     I don't know for sure how the PROMs are connected to the RGB output,
     but it's probably the usual:

     bit 7 -- 220 ohm resistor  -- GREEN
     -- 470 ohm resistor  -- GREEN
     -- 1  kohm resistor  -- GREEN
     -- 2.2kohm resistor  -- GREEN
     -- 220 ohm resistor  -- RED
     -- 470 ohm resistor  -- RED
     -- 1  kohm resistor  -- RED
     bit 0 -- 2.2kohm resistor  -- RED

     bit 3 -- 220 ohm resistor  -- BLUE
     -- 470 ohm resistor  -- BLUE
     -- 1  kohm resistor  -- BLUE
     bit 0 -- 2.2kohm resistor  -- BLUE */
  {
    UINT8 *color_prom = load_region[REGION_PROMS];
    int i;
    for (i = 0;i < 64;i++)
      {
	int r,g,b;

	r = color_prom[0] & 0xf;
	g = color_prom[0]>>4;
	b= color_prom[64] & 0xf;

	private_pal[i] = (r<<8) | (g<<4) | b;
	color_prom++;
      }
  }

  /* Now declare the palette */
  InitPaletteMap((UINT8 *)private_pal,10,8,0x1000);
  set_colour_mapper(&col_map_xxxx_rrrr_gggg_bbbb);
}

static struct AY8910interface ay8910_interface =
  {
    2,	/* 2 chips */
    1500000,	/* 1.5 MHz?????? */
    { MIXER(66,OSD_PAN_CENTER), // music
       MIXER(66,OSD_PAN_CENTER) }, // sound effects
    { 0 },
    { 0 },
    { 0 },
    { 0 }
  };

static struct DACinterface dac_interface =
{
	1,
	{ 102 | (0x80<<8) }
};

static struct SOUND_INFO sound_matmania[] =
  {
    { SOUND_AY8910, &ay8910_interface },
    { SOUND_DAC, &dac_interface },
    { 0,             NULL,                 },
  };

static void draw_matmania() {
  UINT8 *RAM_BG, *COL,*map;
  int offs,scrolly;

  if (palette_updated || RefreshBuffers) {
    ClearPaletteMap();
  }

  if (!GFX_BG0_SOLID) {
    GFX_BG0 = load_region[REGION_GFX2];
    GFX_BG1 = load_region[REGION_GFX1];
    GFX_SPR = load_region[REGION_GFX3];

    GFX_BG1_SOLID = gfx_solid[0]; // chars
    GFX_BG0_SOLID = gfx_solid[1]; // tiles
    GFX_SPR_SOLID = gfx_solid[2]; // sprites
  }

  if( check_layer_enabled(layer_id_data[0])) {
    if (*page_select) {
      RAM_BG = RAM_BG2;
      COL = RAM_COL3;
    } else {
      RAM_BG = RAM_BG0;
      COL = RAM_COL;
    }

    scrolly = *RAM_SCR;
    for (offs = 0x200 - 1;offs >= 0;offs--)
      {
	int sx,sy;
	UINT8 color;
	int offs_orig = offs % 32;

	sy = (offs_orig)*16-scrolly;
	if (sy < -15 || sy >= 240)
	  continue;
	sx = 15 - offs / 32;
	color = COL[offs];

	MAP_PALETTE_MAPPED_NEW(((color & 0x30) >> 4)|4,8,map);

	if (offs_orig >= 16)
	  Draw16x16_Mapped_FlipX_Rot(&GFX_BG0[(RAM_BG[offs] + ((color & 0x08) << 5))<<8], 16*sx+16, sy+16, map);
	else
	  Draw16x16_Mapped_Rot(&GFX_BG0[(RAM_BG[offs] + ((color & 0x08) << 5))<<8], 16*sx+16, sy+16, map);

      }
  } else
    clear_game_screen(0);


  // sprites
  if( check_layer_enabled(layer_id_data[1])) {
    for (offs = 0;offs < 0x60;offs += 4)
      {
	if (RAM_SPR[offs] & 0x01)
	  {
	    UINT16 ta = RAM_SPR[offs+1] + ((RAM_SPR[offs] & 0xf0) << 4);
	    MAP_PALETTE_MAPPED_NEW(((RAM_SPR[offs] & 0x08) >> 3)|8,8,map);
	    if (GFX_SPR_SOLID[ta] != 0) {
	      int sx = 239 - RAM_SPR[offs+3] + 16;
	      int sy = ((240 - RAM_SPR[offs+2]) & 0xff)+16;
	      if (sx < 256+16 && sy < 240+16) {
		if (GFX_SPR_SOLID[ta] == 1) { // transp
		  switch(RAM_SPR[offs] & 0x06){
		  case 0: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[(ta<<8)], sx, sy, map);        break;
		  case 4: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[(ta<<8)], sx, sy, map);  break;
		  case 2: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[(ta<<8)], sx, sy, map);  break;
		  case 6: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[(ta<<8)], sx, sy, map); break;
		  }
		} else {
		  switch(RAM_SPR[offs] & 0x06){
		  case 0: Draw16x16_Mapped_Rot(&GFX_SPR[(ta<<8)], sx, sy, map);        break;
		  case 4: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[(ta<<8)], sx, sy, map);  break;
		  case 2: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[(ta<<8)], sx, sy, map);  break;
		  case 6: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[(ta<<8)], sx, sy, map); break;
		  }
		}
	      }
	    }
	  }
      }
  }

  // chars
  if( check_layer_enabled(layer_id_data[2])) {
    for (offs = 0x400 - 1;offs >= 0;offs--)
      {
	int sx,sy;
	UINT16 ta = RAM_BG1[offs] + 256 * (RAM_COL2[offs] & 0x07);

	if (GFX_BG1_SOLID[ta]) {
	  sx = 31 - offs / 32;
	  sy = offs % 32;

	  MAP_PALETTE_MAPPED_NEW((RAM_COL2[offs] & 0x30) >> 4,8,map);

	  if (GFX_BG1_SOLID[ta] == 1) // transp
	    Draw8x8_Trans_Mapped_Rot(&GFX_BG1[(ta<<6)], 8*sx+16, 8*sy+16, map);
	  else {
	    Draw8x8_Mapped_Rot(&GFX_BG1[(ta<<6)], 8*sx+16, 8*sy+16, map);
	  }
	}
      }
  }
}

#define SLICES 15 // speed of the music, 15 is a guess, but it sounds good

static void execute_matmania() {
  int slice;
  stopped_6502 = 0;
  for (slice=0; slice<SLICES; slice++) {
    if (!stopped_6502) {
      cpu_execute_cycles(CPU_M6502_0, CPU_FRAME_MHz(1.8,60)/SLICES); // a little more than 1.5 Mhz
      print_debug("M6502_PC:%04x\n",m6502pc);
    }
    cpu_execute_cycles(CPU_M6502_1, CPU_FRAME_MHz(1.4,60)/SLICES); // a little more than 1.5 Mhz
    print_debug("M6502_PC2:%04x\n",m6502pc);
    cpu_int_nmi(CPU_M6502_1);
  }
  cpu_interrupt(CPU_M6502_0,1);
  input_buffer[0x30] ^= 0x80;
}

static struct VIDEO_INFO video_matmania =
{
  &draw_matmania,
  256,
  240,
  16,
  VIDEO_ROTATE_270 |
  VIDEO_ROTATABLE,
  matmania_gfxdecodeinfo,
};
GMEI( matmania, "Mat Mania", TECHNOS, 1985, GAME_SPORTS);
CLNEI( excthour, matmania, "Exciting Hour", TECHNOS, 1985, GAME_SPORTS);

