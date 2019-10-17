#define DRV_DEF_DSW NULL
#define DRV_DEF_SOUND sound_esprade
#define DRV_DEF_EXEC execute_esprade
#define DRV_DEF_INPUT input_esprade
/******************************************************************************/
/*                                                                            */
/*                        CAVE / ATLUS GAMES (C) 1998                         */
/*                                                                            */
/******************************************************************************/
// The sailor moon and the mazinger drivers are from Luca Elia in Mame...
// I really wonder how he found such bankswitch functions for the oki...
// And the decrypion of sprites too... Thanks Luca anyway...
/*
  Notes : the video hardware of cave games seems to be able to switch from 16x16
  sprites to 8x8. For now it's not fully emulated because it will create problems in raine
  sprites are rotated when building solid masks in raine normally, these functions are
  heavily dependant on a fixed sprite size. The best way to avoid this is to have one
  copy of the sprites / size, but it's unthinkable for the huge games like guwange.
  So for now this feature is not really emulated. It's just done when needed (agallet uses
  this in one place for its background).

  8/2003 : we upgrade to the mame romsets once again. The patch is not from me, I just
  adapted it a little...

  2/2004 : it seems finally after all this time that contrary to what I always believed
  and contrary to what mame writes in its source comments, sprites have no relative
  priorities. As for magical cat adventure, their priority only counts when compared to
  layers, but not between sprites. Which means that we should use the priority bitmap
  of magical cat adventure, adding a big overhead.
  The only place where I could see a relative priorities problem between sprites is in
  dfeveron, just before the title screen appears (there should be some very big white
  sprites appearing and we can't see anything).

  11/2004 (!) : finally fixed the sprites problem in mazinger in late stages.
  It was only because the sprites area needed a fixed size of 0x800000 bytes... !!!
   - Fixed a 1 pixel layer alignement issue in another stage of mazinger
   - Finally rewrote the code to handle video priorities.
*/

#include "gameinc.h"
#include "cat93c46.h"
#include "mame/handlers.h"
#include "mame/eeprom.h"
#include "sasound.h"		// sample support routines
#include "ymz280b.h"
#include "adpcm.h"
#include "2203intf.h"
#include "2151intf.h"
#include "savegame.h"
#include "lspr16.h" // experimental line scroll (not finished)
#include "decode.h" // BITSWAP24 for mazinger
#include "emumain.h" // reset_game_hardware
#include "blit.h" // clear_game_screen
#include "taitosnd.h" // z80_irq_handler
#include "timer.h"
#include "video/priorities.h"
#include "pdraw.h"
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines
#include "speed_hack.h"
#include "profile.h" // fps

static int limitx, gamex;

static int layer_size[3]; // Sizes of the sprites in the layer
static UINT8 layer_base[3]; // palette base for the layers
static BITMAP *layer_bitmap[3], *layer_pbitmap[3];

static short vblank_irq,sound_irq,romset,unknown_irq;
// romset uses bits :
// 1 for ddonpach (sprites attributes differ and no zoom)
// 2 : palette share between OBJ and bg layers
// 4 ; sprite placement for hotdogst (and others)
// 8 : special bg2 for sailor moon. I doubt any other driver will use this...

static unsigned long sprite_size; // To prevent overflows...
static int sprites_bg0, sprites_bg1, sprites_bg2;

// Nb of sprites / rows for a tile
#define DIM_NX 0x20
// _ / col
#define DIM_NY 0x20

static UINT8 *GFX_BG0;
static UINT8 *GFX_BG1;
static UINT8 *GFX_BG2;

static UINT8 *GFX_OBJ_A;
static UINT8 *GFX_OBJ_B;
static UINT8 *GFX_OBJ_SIZE;

static UINT8 *GFX_BG0_SOLID;
static UINT8 *GFX_BG1_SOLID;
static UINT8 *GFX_BG2_SOLID;

static UINT8 *GFX_OBJ_SOLID;

static int layer_id_data[4];

static char *layer_id_name[4] =
{
   "BG0", "BG1", "BG2", "OBJECT",
};

static UINT8 *RAM_BG0;
static UINT8 *RAM_BG1;
static UINT8 *RAM_BG2;

static UINT8 *RAM_BG0_CTRL;
static UINT8 *RAM_BG1_CTRL;
static UINT8 *RAM_BG2_CTRL;

#define FRAME_68K 32
static UINT32 xcorrection; // x correction for layers alignement

int get_layer_size(int n) {
  const VIDEO_INFO *video_info = current_game->video;
  const GFX_LIST *gfx_list = video_info->gfx_list;

  while (n--) gfx_list++;
  if (!gfx_list->layout)
    return 16; // default (esprade)
  else
    return gfx_list->layout->width;
}

static void setup_nolayouts() {
  int n;
  for (n=0; n<=2; n++)
    gfx_solid[n] = make_solid_region_16x16(REGION_GFX1+n);
}

static void setup_cave_sprites(GFX_LAYOUT *layout) {
  // we must keep a layer of sprites not rotated, so they are handled this way...
  UINT8 *tmp;
  UINT32 dest_size;
  if (layout) {
    tmp = decode_gfx(load_region[REGION_GFX4], get_region_size(REGION_GFX4), layout, &dest_size);
    FreeMem(load_region[REGION_GFX4]);
    load_region[REGION_GFX4] = tmp;
  } else {
    dest_size = get_region_size(REGION_GFX4);
  }
  sprite_size = dest_size/0x100;
  GFX_OBJ_A = load_region[REGION_GFX4];
  if(!(GFX_OBJ_SIZE=AllocateMem(sprite_size))) return;
  memset(GFX_OBJ_SIZE,0x01,sprite_size);
  if(!(GFX_OBJ_B   =AllocateMem(sprite_size<<8))) return;
  memcpy(GFX_OBJ_B,GFX_OBJ_A,sprite_size<<8);
  GFX_OBJ_SOLID = make_solid_mask_16x16(GFX_OBJ_B, sprite_size);
  // This is the default for most cave games. Only sailormoon uses a different
  // base for each layer...
  layer_base[0] = layer_base[1] = layer_base[2] = 0x40;
  xcorrection = 0x12;
  GFX_BG0 = NULL;
}

static void setup_cave_tiles()
{
  int s0,s1,s2;
  s0 = get_layer_size(0);
  s1 = get_layer_size(1);
  s2 = get_layer_size(2);

  GFX_BG0   = load_region[REGION_GFX1];
  GFX_BG1   = load_region[REGION_GFX2];
  GFX_BG2   = load_region[REGION_GFX3];

  if (GFX_BG0) {
    sprites_bg0 = get_region_size(REGION_GFX1)/s0/s0;
    GFX_BG0_SOLID = gfx_solid[0];
    layer_id_data[0] = add_layer_info(layer_id_name[0]);
  }
  if (GFX_BG1) {
    sprites_bg1 = get_region_size(REGION_GFX2)/s1/s1;
    GFX_BG1_SOLID = gfx_solid[1];
    layer_id_data[1] = add_layer_info(layer_id_name[1]);
  }
  if (GFX_BG2) {
    sprites_bg2 = get_region_size(REGION_GFX3)/s2/s2;
    GFX_BG2_SOLID = gfx_solid[2];

    layer_id_data[2] = add_layer_info(layer_id_name[2]);
  }
  if (s1 == 8 || s2 == 8 || s0 == 8)
    init_tile_cache();

  layer_id_data[3] = add_layer_info(layer_id_name[3]);
  layer_size[0] = s0;
  layer_size[1] = s1;
  layer_size[2] = s2;
}

/*	We need a FIFO buffer for sailormn, where the inter-CPUs
	communication is *really* tight */
#define SOUND_BUFLEN 64
struct
{
  int len;
  data8_t data[SOUND_BUFLEN];
} soundbuf;

static UINT32 cave_region_pos;
static UINT32 cave_region_byte;

static void install_region() {
  if (cave_region_pos) {
    // Region hack from the eeprom !
    EEPROM_get_data_pointer(0)[cave_region_pos] =  cave_region_byte;
  }
}

static void setup_cave_game() {
  int i;
  init_pbitmap();
  // memset(input_buffer, 0xff, 16);

  for (i=0; i<3; i++) {
    layer_bitmap[i] = layer_pbitmap[i] = NULL;
  }
  limitx = current_game->video->screen_x + current_game->video->border_size+16;
  // +16 because compared to zoomed sprites which have a size of 16 by default
  gamex = current_game->video->screen_x;
  memset(RAM+0x00000,0x00,0x80000);

  finish_conf_68000(0);
  vblank_irq = sound_irq = unknown_irq = 0;
  soundbuf.len = 0;
  AddSaveData(SAVE_USER_1, (UINT8 *)&soundbuf, sizeof(soundbuf));

  EEPROM_init(&eeprom_interface_93C46);
  load_eeprom();

  set_reset_function(install_region);
}

static void sail_soundcmd_w(UINT32 offset,UINT16 data)
{
  latch = data;
  cpu_int_nmi(CPU_Z80_0);
}

static void sail_soundcmd_wb(UINT32 offset, UINT8 data)
{
  if (offset & 1)
    latch = (latch & 0xff) | (data << 8);
  else
    latch = (latch & 0xff00) | data;
  cpu_int_nmi(CPU_Z80_0);
  // mz80 now supports nested nmi !
}

static void update_irq_state(void)
{
  // static int irq_counter;
  if ((vblank_irq || unknown_irq || sound_irq)) { // && irq_counter++<32) {
    // s68000interrupt(1, -1);
/*     if (s68000context.interrupts[0] & 2) {
     } */
     cpu_interrupt(CPU_68K_0, 1);
  } else {
#ifdef RAINE_DEBUG
/*     if (s68000context.interrupts[0] & 2) */
#endif
    s68000context.interrupts[0] &= ~2;
    // irq_counter = 0;
  }
}

/* Called by the YMZ280B to set the IRQ state */
static void sound_irq_gen(int state)
{
	sound_irq = (state != 0);
        update_irq_state();
}

static struct YMZ280Binterface ymz280b_intf =
{
   1,
   { 16934400 },
   { REGION_SMP1 },
   { YM3012_VOL(255,MIXER_PAN_LEFT,255,MIXER_PAN_RIGHT) },
   { sound_irq_gen }
};

static struct OKIM6295interface donpachi_okim6295_interface =
{
	2,
	{ 8330, 16000 },
	{ REGION_SMP1, REGION_SMP2 },
	{ 225, 225 }
};

static struct YM2203interface hotdogst_ym2203_interface =
{
	1,			/* 1 chip */
	3367000,	/* 3 MHz ??? */
	{ YM2203_VOL(204,51) },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ z80_irq_handler }
};

static struct OKIM6295interface hotdogst_okim6295_interface =
{
	1,                  /* 1 chip */
	{ 8000 },           /* 8000Hz frequency? */
	{ REGION_SMP1 },	/* memory region */
	{ 255 }
};

// The cave driver has become a real mess : you have almost every possible
// sound chip now here...
static struct YM2151interface ym2151_intf_4MHz =
{
	1,
	4000000,		/* ? */
	{ YM3012_VOL(76,MIXER_PAN_LEFT,76,MIXER_PAN_RIGHT) },
	{ z80_irq_handler, /* sound_irq_gen */ },	/* irq handler */
	{ 0 }			/* port_write */
};

static struct OKIM6295interface okim6295_intf_16kHz_16kHz =
{
  2,
  { 16000, 16000 },
  { REGION_SMP1, REGION_SMP2 },
  { 250, 250 }
};

static struct SOUND_INFO sound_donpachi[] =
{
   { SOUND_M6295,  &donpachi_okim6295_interface,  },
   { 0,             NULL,               },
};

static struct SOUND_INFO sound_agallet[] =
{
  { SOUND_YM2151J,	&ym2151_intf_4MHz },
  { SOUND_M6295,	&okim6295_intf_16kHz_16kHz },
   { 0,             NULL,               },
};

static struct SOUND_INFO sound_esprade[] =
{
   { SOUND_YMZ280B,  &ymz280b_intf,  },
   { 0,             NULL,               },
};

static struct SOUND_INFO sound_hotdogst[] =
{
   { SOUND_YM2203,  &hotdogst_ym2203_interface,  },
   { SOUND_M6295, &hotdogst_okim6295_interface,},
   { 0,             NULL,               },
};


















static struct ROM_INFO rom_esprade[] =
{
  LOAD8_16( REGION_ROM1, 0,  0x00080000,
                 "u42_i.bin",  0x3b510a73,      "u41_i.bin",  0x97c1b649),

   {      "u54.bin", 0x00400000, 0xe7ca6936,REGION_GFX1,0x000000,LOAD8X8_16X16 },
   {      "u55.bin", 0x00400000, 0xf53bd94f,REGION_GFX1,0x400000,LOAD8X8_16X16 },

   {      "u52.bin", 0x00400000, 0xe7abe7b4,REGION_GFX2,0x000000,LOAD8X8_16X16 },
   {      "u53.bin", 0x00400000, 0x51a0f391,REGION_GFX2,0x400000,LOAD8X8_16X16 },

   {      "u51.bin", 0x00400000, 0x0b9b875c,REGION_GFX3,0x000000,LOAD8X8_16X16 },

  LOAD8_16S( REGION_GFX4, 0x000000,  0x00400000,
                 "u63.bin",  0x2f2fe92c,      "u64.bin",  0x491a3da4),
  LOAD8_16S( REGION_GFX4, 0x800000,  0x00400000,
                 "u65.bin",  0x06563efe,      "u66.bin",  0x7bbe4cfc),

   {      "u19.bin", 0x00400000, 0xf54b1cab,REGION_SMP1,0,LOAD_NORMAL },
   {           NULL,          0,          0, },
};

static struct ROM_INFO rom_espradeo[] =
{
  LOAD8_16( REGION_ROM1, 0,  0x00080000,
                 "u42.bin",  0x0718c7e5,      "u41.bin",  0xdef30539),





   {           NULL,          0,          0, },
};

static struct ROM_INFO rom_espradej[] =
{
  LOAD8_16( REGION_ROM1, 0,  0x00080000,
                 "u42_ver2.bin",  0x75d03c42,      "u41_ver2.bin",  0x734b3ef0),





   {           NULL,          0,          0, },
};

static struct ROM_INFO rom_donpachi[] =
{
   {      "prgu.u29", 0x00080000, 0x89c36802,REGION_ROM1,0,LOAD_SWAP_16 },

   {      "atdp.u54", 0x100000, 0x6bda6b66,REGION_GFX1,0x000000, LOAD_NORMAL },

   {      "atdp.u57", 0x100000, 0x0a0e72b9,REGION_GFX2,0x000000,LOAD_NORMAL },

   {      "text.u58", 0x00040000, 0x5dba06e7,REGION_GFX3,0x000000,LOAD_NORMAL },

   {      "atdp.u44",0x00200000, 0x7189e953,REGION_GFX4,0x000000,LOAD_SWAP_16 },
   {      "atdp.u45",0x00200000, 0x6984173f,REGION_GFX4,0x200000,LOAD_SWAP_16 },

   {      "atdp.u33", 0x00200000, 0xd749de00,REGION_SMP1,0x40000,LOAD_NORMAL },

   {      "atdp.u32", 0x00100000, 0x0d89fcca,REGION_SMP2,0x40000,LOAD_NORMAL },
   {      "atdp.u33", 0x00200000, 0xd749de00,REGION_SMP2,0x140000,LOAD_NORMAL },
   {           NULL,          0,          0, },
};


static struct ROM_INFO rom_donpachj[] =
{
   {      "prg.u29", 0x00080000, 0x6be14af6,REGION_ROM1,0,LOAD_SWAP_16 },
   {      "u58.bin", 0x00040000, 0x285379ff,REGION_GFX3,0x000000,LOAD_NORMAL },
   {           NULL,          0,          0, },
};

static struct ROM_INFO rom_donpachk[] =
{
   {      "prgk.u26", 0x00080000, 0xbbaf4c8b,REGION_ROM1,0,LOAD_SWAP_16 },
   {      "u58.bin", 0x00040000, 0x285379ff,REGION_GFX3,0x000000,LOAD_NORMAL },
   {           NULL,          0,          0, },
};

static struct ROM_INFO rom_guwange[] =
{
  LOAD8_16(  REGION_ROM1,  0x0000000,  0x00080000,
            "gu-u0127.bin",  0xf86b5293, "gu-u0129.bin",  0x6c0e3b93),

  {     "u101.bin", 0x00800000, 0x0369491f, REGION_GFX1, 0x0000000, LOAD8X8_16X16, },

  {   "u10102.bin", 0x00400000, 0xe28d6855, REGION_GFX2, 0x0000000, LOAD8X8_16X16, },
   {   "u10103.bin", 0x00400000, 0x0fe91b8e, REGION_GFX3, 0x0000000, LOAD8X8_16X16, },

  LOAD8_16S(  REGION_GFX4,  0x0000000,  0x00800000,
                "u083.bin",  0xadc4b9c4,     "u082.bin",  0x3d75876c),
  LOAD8_16S(  REGION_GFX4,  0x1000000,  0x00400000,
                "u086.bin",  0x188e4f81,     "u085.bin",  0xa7d5659e),
  LOAD8_16S(  REGION_GFX4, 0x1800000,  0x400000,
             "u086.bin",  0x188e4f81,  "u085.bin",  0xa7d5659e),
   {    "u0462.bin", 0x00400000, 0xb3d75691, REGION_SMP1, 0, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_guwanges[] = // clone of guwange
{
  LOAD8_16(  REGION_CPU1, 0x000000,  0x080000,
             "gu-u0127b.bin",  0x64667d2e,  "gu-u0129b.bin",  0xa99C6b6c),
  LOAD8_16S(  REGION_GFX4, 0x0000000,  0x800000,
             "u083.bin",  0xadc4b9c4,  "u082.bin",  0x3d75876c),
  LOAD8_16S(  REGION_GFX4, 0x1000000,  0x400000,
             "u086.bin",  0x188e4f81,  "u085.bin",  0xa7d5659e),
//  sprite bug fix?
//  ROM_FILL(                    0x1800000, 0x800000, 0xff )
  LOAD8_16S(  REGION_GFX4, 0x1800000,  0x400000,
             "u086.bin",  0x188e4f81,  "u085.bin",  0xa7d5659e),
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_ddonpach[] =
{
  LOAD8_16(  REGION_ROM1,  0x0000000,  0x00080000,
                 "b1.u27",  0xb5cdc8d3,      "b2.u26",  0x6bbb063a),

   {      "u60.bin", 0x00200000, 0x903096a7, REGION_GFX1, 0x0000000, LOAD_NORMAL,  },

   {      "u61.bin", 0x00200000, 0xd89b7631, REGION_GFX2, 0x0000000, LOAD_NORMAL,  },

   {      "u62.bin", 0x00200000, 0x292bfb6b, REGION_GFX3, 0x0000000, LOAD_NORMAL,  },

   {      "u50.bin", 0x00200000, 0x14b260ec, REGION_GFX4, 0x0000000, LOAD_SWAP_16, },
   {      "u51.bin", 0x00200000, 0xe7ba8cce, REGION_GFX4, 0x0200000, LOAD_SWAP_16, },
   {      "u52.bin", 0x00200000, 0x02492ee0, REGION_GFX4, 0x0400000, LOAD_SWAP_16, },
   {      "u53.bin", 0x00200000, 0xcb4c10f0, REGION_GFX4, 0x0600000, LOAD_SWAP_16, },
   {       "u6.bin", 0x00200000, 0x9dfdafaf, REGION_SMP1, 0x0000000, LOAD_NORMAL, },
   {       "u7.bin", 0x00200000, 0x795b17d5, REGION_SMP1, 0x0200000, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_ddonpchj[] =
{
  LOAD8_16(  REGION_ROM1,  0x0000000,  0x00080000,
                 "u27.bin",  0x2432ff9b,      "u26.bin",  0x4f3a914a),




   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_hotdogst[] =
{
  LOAD8_16( REGION_ROM1, 0,  0x00080000,
                  "mp3u29",  0x1f4e5479,       "mp4u28",  0x6f1c3c4b),

   {       "mp2u19", 0x00040000, 0xff979ebe,REGION_ROM2,0x000,LOAD_NORMAL },

   {       "mp7u56", 0x080000, 0x87c21c50,REGION_GFX1,0x000000, LOAD_NORMAL },

   {       "mp6u61", 0x080000, 0x4dafb288,REGION_GFX2,0x000000,LOAD_NORMAL },

   {       "mp5u64",0x0080000, 0x9b26458c,REGION_GFX3,0x000000,LOAD_NORMAL },

   {      "mp9u55",0x00200000, 0x258d49ec,REGION_GFX4,0x000000, LOAD_NORMAL },
   {      "mp8u54",0x00200000, 0xbdb4d7b8,REGION_GFX4,0x200000, LOAD_NORMAL },

   {      "mp1u65", 0x00080000, 0x4868be1b,REGION_SMP1,0x40000,LOAD_NORMAL },

   {           NULL,          0,          0, },
};

static struct ROM_INFO rom_mazinger[] =
{
  { "mzp-0.u24", 0x80000, 0x43a4279f , REGION_ROM1, 0x00000, LOAD_SWAP_16 },
  { "mzs.u21", 0x20000, 0xc5b4f7ed , REGION_ROM2, 0x000, LOAD_NORMAL },
  // ROM3 : 68000 bank...
  { "mzp-1.924", 0x80000, 0xdb40acba,  REGION_ROM3, 0x00000, LOAD_SWAP_16 },
  { "bp943a-1.u60", 0x200000, 0x46327415 , REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bp943a-0.u63", 0x200000, 0xc1fed98a , REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "bp943a-2.u56", 0x200000, 0x97e13959 , REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "bp943a-3.u55", 0x080000, 0x9c4957dd , REGION_GFX4, 0x200000, LOAD_NORMAL },
  { "bp943a-3.u55", 0x080000, 0x9c4957dd , REGION_GFX4, 0x780000, LOAD_NORMAL },
  { "bp943a-4.u64", 0x080000, 0x3fc7f29a , REGION_SMP1, 0x040000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sailormn[] =
{
  { "bpsm945a.u45", 0x080000, 0x898c9515 , REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "bpsm.u46", 0x200000, 0x32084e80 , REGION_ROM1, 0x200000, LOAD_SWAP_16 },

  { "bpsm945a.u9", 0x80000, 0x438de548 , REGION_ROM2, 0x4000, LOAD_NORMAL },

  { "bpsm.u53", 0x200000, 0xb9b15f83 , REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bpsm.u54", 0x200000, 0x8f00679d , REGION_GFX2, 0x000000, LOAD_NORMAL },

  { "bpsm.u57", 0x200000, 0x86be7b63 , REGION_GFX3, 0x000000, LOAD_NORMAL },
  { "bpsm.u58", 0x200000, 0xe0bba83b , REGION_GFX3, 0x200000, LOAD_NORMAL },
  { "bpsm.u62", 0x200000, 0xa1e3bfac , REGION_GFX3, 0x400000, LOAD_NORMAL },
  { "bpsm.u61", 0x200000, 0x6a014b52 , REGION_GFX3, 0x600000, LOAD_NORMAL },
  { "bpsm.u60", 0x200000, 0x992468c0 , REGION_GFX3, 0x800000, LOAD_NORMAL },
  // 2bits part
  { "bpsm.u65", 0x200000, 0xf60fb7b5 , REGION_GFX3, 0xa00000, LOAD_NORMAL },
  { "bpsm.u64", 0x200000, 0x6559d31c , REGION_GFX3, 0xc00000, LOAD_NORMAL },
  { "bpsm.u63", 0x200000, 0xd57a56b4 , REGION_GFX3, 0xe00000, LOAD_NORMAL },
  // Duplicate the 2 bit part to have twice the same size
  { "bpsm.u65", 0x200000, 0xf60fb7b5 , REGION_GFX3, 0x1000000, LOAD_NORMAL },
  { "bpsm.u64", 0x200000, 0x6559d31c , REGION_GFX3, 0x1200000, LOAD_NORMAL },

  { "bpsm.u76", 0x200000, 0xa243a5ba , REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "bpsm.u77", 0x200000, 0x5179a4ac , REGION_GFX4, 0x200000, LOAD_NORMAL },

  { "bpsm.u48", 0x200000, 0x498e4ed1 , REGION_SMP1, 0x040000, LOAD_NORMAL },
  { "bpsm.u47", 0x080000, 0x0f2901b9 , REGION_SMP2, 0x040000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_sailormo[] =
{
  { "smprg.u45", 0x080000, 0x234f1152 , REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "bpsm.u46", 0x200000, 0x32084e80 , REGION_ROM1, 0x200000, LOAD_SWAP_16 },



  // 2bits part
  // Duplicate the 2 bit part to have twice the same size


  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_agallet[] =
{
  { "bp962a.u45", 0x080000, 0x24815046 , REGION_ROM1, 0x000000, LOAD_SWAP_16 },
  { "bp962a.u9", 0x80000, 0x06caddbe, REGION_ROM2, 0x4000, LOAD_NORMAL },

  { "bp962a.u53", 0x200000, 0xfcd9a107, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bp962a.u54", 0x200000, 0x0cfa3409, REGION_GFX2, 0x000000, LOAD_NORMAL },

  { "bp962a.u57", 0x200000, 0x6d608957, REGION_GFX3, 0x000000, LOAD_NORMAL },
  // 2bits part
  { "bp962a.u65", 0x200000, 0x135fcf9a, REGION_GFX3, 0x200000, LOAD_NORMAL },

  { "bp962a.u76", 0x200000, 0x858da439, REGION_GFX4, 0x000000, LOAD_NORMAL },
  { "bp962a.u77", 0x200000, 0xea2ba35e, REGION_GFX4, 0x200000, LOAD_NORMAL },

  { "bp962a.u48", 0x200000, 0xae00a1ce, REGION_SMP1, 0x040000, LOAD_NORMAL },
  { "bp962a.u47", 0x200000, 0x6d4e9737, REGION_SMP2, 0x040000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_uopoko[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00080000,
                "u26j.bin",  0xe7eec050,     "u25j.bin",  0x68cb6211),
   {      "u49.bin", 0x00400000, 0x12fb11bb, REGION_GFX1, 0x000000, LOAD_NORMAL, },
   {      "u33.bin", 0x00400000, 0x5d142ad2, REGION_GFX4, 0x000000, LOAD_NORMAL, },
   {       "u4.bin", 0x00200000, 0xa2d0d755, REGION_SMP1, 0x000000, LOAD_NORMAL, },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct ROM_INFO rom_dfeveron[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00080000,
                 "cv01-u34.bin",  0xbe87f19d,      "cv01-u33.bin",  0xe53a7db3),

   {      "cv01-u50.bin", 0x00200000, 0x7a344417, REGION_GFX1, 0x000000, LOAD_NORMAL, },

   {      "cv01-u49.bin", 0x00200000, 0xd21cdda7, REGION_GFX2, 0x000000, LOAD_NORMAL, },

   {      "cv01-u25.bin", 0x00400000, 0xa6f6a95d, REGION_GFX4, 0x000000, LOAD_NORMAL, },
   {      "cv01-u26.bin", 0x00400000, 0x32edb62a, REGION_GFX4, 0x400000, LOAD_NORMAL, },
   {      "cv01-u19.bin", 0x00400000, 0x5f5514da, REGION_SMP1,        0, LOAD_NORMAL, },
   {           NULL,          0,          0,           0,        0,           0, },
};

static struct ROM_INFO rom_feversos[] =
{
  LOAD8_16(  REGION_ROM1,  0x000000,  0x00080000,
                 "rom2.bin",  0x24ef3ce6,      "rom1.bin",  0x64ff73fd),



   {           NULL,          0,          0,           0,        0,           0, },
};

static const struct INPUT_INFO input_esprade[] =
{
   INP0( COIN1, 0x000000, 0x01 ),
   INP0( COIN2, 0x000002, 0x01 ),
   INP0( TEST, 0x000000, 0x02 ),
   INP0( SERVICE, 0x000002, 0x02 ),
   INP0( UNKNOWN, 0, 4), // exit service mode
   INP0( UNKNOWN, 0, 8), // enter & exit service mode

   INP0( P1_START, 0x000001, 0x80 ),
   INP0( P1_UP, 0x000001, 0x01 ),
   INP0( P1_DOWN, 0x000001, 0x02 ),
   INP0( P1_LEFT, 0x000001, 0x04 ),
   INP0( P1_RIGHT, 0x000001, 0x08 ),
   INP0( P1_B1, 0x000001, 0x10 ),
   INP0( P1_B2, 0x000001, 0x20 ),
   INP0( P1_B3, 0x000001, 0x40 ),

   INP0( P2_START, 0x000003, 0x80 ),
   INP0( P2_UP, 0x000003, 0x01 ),
   INP0( P2_DOWN, 0x000003, 0x02 ),
   INP0( P2_LEFT, 0x000003, 0x04 ),
   INP0( P2_RIGHT, 0x000003, 0x08 ),
   INP0( P2_B1, 0x000003, 0x10 ),
   INP0( P2_B2, 0x000003, 0x20 ),
   INP0( P2_B3, 0x000003, 0x40 ),

   END_INPUT
};

static struct INPUT_INFO input_guwange[] =
{
   INP0( COIN1, 0x000003, 0x01 ),
   INP0( COIN2, 0x000003, 0x02 ),
   INP0( TEST, 0x000003, 0x04 ),
   INP0( SERVICE, 0x000003, 0x08 ),

   INP0( P1_START, 0x000001, 0x01 ),
   INP0( P1_UP, 0x000001, 0x02 ),
   INP0( P1_DOWN, 0x000001, 0x04 ),
   INP0( P1_LEFT, 0x000001, 0x08 ),
   INP0( P1_RIGHT, 0x000001, 0x10 ),
   INP0( P1_B1, 0x000001, 0x20 ),
   INP0( P1_B2, 0x000001, 0x40 ),
   INP0( P1_B3, 0x000001, 0x80 ),

   INP0( P2_START, 0x000000, 0x01 ),
   INP0( P2_UP, 0x000000, 0x02 ),
   INP0( P2_DOWN, 0x000000, 0x04 ),
   INP0( P2_LEFT, 0x000000, 0x08 ),
   INP0( P2_RIGHT, 0x000000, 0x10 ),
   INP0( P2_B1, 0x000000, 0x20 ),
   INP0( P2_B2, 0x000000, 0x40 ),
   INP0( P2_B3, 0x000000, 0x80 ),

   END_INPUT
};

/* 8x8x4 tiles */
static gfx_layout layout_8x8x4 =
{
   8,8,
   RGN_FRAC(1,1),
   4,
   {0,1,2,3},
   {STEP8(0,4)},
   {STEP8(0,8*4)},
   8*8*4
};

/* 8x8x8 tiles */
static gfx_layout layout_8x8x8 =
{
   8,8,
   RGN_FRAC(1,1),
   8,
   {8,9,10,11, 0,1,2,3},
   {0*4,1*4,4*4,5*4,8*4,9*4,12*4,13*4},
   {0*64,1*64,2*64,3*64,4*64,5*64,6*64,7*64},
   8*8*8
};


/* 16x16x4 tiles */
static gfx_layout layout_16x16x4 =
{
   16,16,
   RGN_FRAC(1,1),
   4,
   {0,1,2,3},
   {0*4,1*4,2*4,3*4,4*4,5*4,6*4,7*4,
    64*4,65*4,66*4,67*4,68*4,69*4,70*4,71*4},
   {0*32,1*32,2*32,3*32,4*32,5*32,6*32,7*32,
    16*32,17*32,18*32,19*32,20*32,21*32,22*32,23*32},
   16*16*4
};

/* 16x16x8 tiles */
static gfx_layout layout_16x16x8 =
{
   16,16,
   RGN_FRAC(1,1),
   8,
   {8,9,10,11, 0,1,2,3},
   {0*4,1*4,4*4,5*4,8*4,9*4,12*4,13*4,
    128*4,129*4,132*4,133*4,136*4,137*4,140*4,141*4},
   {0*64,1*64,2*64,3*64,4*64,5*64,6*64,7*64,
    16*64,17*64,18*64,19*64,20*64,21*64,22*64,23*64},
   16*16*8
};

/* 16x16x4 objects */
static gfx_layout cave_gfx_object =
{
   16,16,
   RGN_FRAC(1,1),
   4,
   {0,1,2,3},
   {  1*4,  0*4,  3*4,  2*4,  5*4,  4*4,  7*4,  6*4,
      9*4,  8*4, 11*4, 10*4, 13*4, 12*4, 15*4, 14*4 },
   {STEP16(0,16*4)},
   16*16*4
};

static gfx_layout layout_8x8x6 =
{
	8,8,
	RGN_FRAC(1,1),
	6,
	{8,9, 0,1,2,3},
	{0*4,1*4,4*4,5*4,8*4,9*4,12*4,13*4},
	{0*64,1*64,2*64,3*64,4*64,5*64,6*64,7*64},
	8*8*8
};

/* 8x8x6 tiles (4 bits in one rom, 2 bits in the other,
   unpacked in 2 pages of 4 bits) */
static gfx_layout layout_8x8x6_2 =
{
	8,8,
	RGN_FRAC(1,2),
	6,
	{RGN_FRAC(1,2)+2,RGN_FRAC(1,2)+3, STEP4(0,1)},
	{STEP8(0,4)},
	{STEP8(0,4*8)},
	8*8*4
};

/* 16x16x4 objects */
static gfx_layout ddonpach_gfx_object =
{
   16,16,
   RGN_FRAC(1,1),
   4,
   {0,1,2,3},
   {STEP16(0,4)},
   {STEP16(0,16*4)},
   16*16*4
};

static struct GFX_LIST cave_gfx[] =
{
   { REGION_GFX1, &layout_16x16x4,  },
   { REGION_GFX2, &layout_16x16x4,  },
   { REGION_GFX3, &layout_16x16x4,  },
   // { REGION_GFX4, &cave_gfx_object, },
   { 0,           NULL,             },
};

static struct GFX_LIST donpachi_gfx[] =
{
   { REGION_GFX1, &layout_16x16x4,  },
   { REGION_GFX2, &layout_16x16x4,  },
   { REGION_GFX3, &layout_8x8x4,  },
   // { REGION_GFX4, &ddonpach_gfx_object, },
   { 0,           NULL,             },
};

static struct GFX_LIST esprade_gfx[] =
{
   { REGION_GFX1, NULL,  },
   { REGION_GFX2, NULL,  },
   { REGION_GFX3, NULL,  },
   { REGION_GFX4, NULL, },
   { 0,           NULL,             },
};

static struct GFX_LIST ddonpach_gfx[] =
{
   { REGION_GFX1, &layout_16x16x4,      },
   { REGION_GFX2, &layout_16x16x4,      },
   { REGION_GFX3, &layout_8x8x8,        },
   // { REGION_GFX4, &ddonpach_gfx_object, },
   { 0,           NULL,                 },
};

static struct GFX_LIST uopoko_gfx[] =
{
   { REGION_GFX1, &layout_16x16x8,  },
   { REGION_GFX2, &layout_16x16x8,  },
   { REGION_GFX3, &layout_16x16x8,  },
   // { REGION_GFX4, &cave_gfx_object, },
   { 0,           NULL,             },
};

static struct GFX_LIST mazinger_gfx[] =
{
  /*	Sprites are 4 bit deep.
	Layer 0 is 4 bit deep.
	Layer 1 uses 64 color palettes, but the game only fills the
	first 16 colors of each palette, Indeed, the gfx data in ROM
	is empty in the top 4 bits. Additionally even if there are
	$40 color codes, only $400 colors are addressable.
	A vh_init_palette is thus needed for sprites and layer 0.	*/

  // We can't use cave_gfx_object layout because sprites are encrypted
  { REGION_GFX1, &layout_8x8x4,	}, /* [0] Layer 0 */
  { REGION_GFX2, &layout_8x8x6,	}, /* [1] Layer 1 */
  { REGION_GFX4, NULL, }, // Sprites */
	{ -1 }
};

static struct GFX_LIST sailormn_gfx[] =
{
  // We can't use cave_gfx_object layout because sprites are encrypted
  { REGION_GFX1, &layout_16x16x4,	}, /* [0] Layer 0 */
  { REGION_GFX2, &layout_16x16x4,	}, /* [1] Layer 1 */
  { REGION_GFX3, &layout_8x8x6_2 },
  { REGION_GFX4, NULL, }, // Sprites */
	{ -1 }
};










static void clear_cave_68k(void)
{
  int i;
  for (i=0; i<3; i++) {
    if (layer_bitmap[i]) {
      destroy_bitmap(layer_bitmap[i]);
      destroy_bitmap(layer_pbitmap[i]);
    }
  }
  // pbitmap = NULL;
  save_eeprom();
}

static void clear_mazinger(void)
{
   save_eeprom();
}

static UINT8 *RAM_CTRL;

static UINT32 gfx_colours;

//WRITE_HANDLER( cave_eeprom_w )
static void cave_eeprom_w(UINT32 offset, UINT16 data)
{
	(void)(offset);
   if ( (data & 0xFF000000) == 0 )  /* even address */
   {
      /* latch the bit */
     EEPROM_write_bit(data & 0x0800);

     /* reset line asserted: reset. */
     EEPROM_set_cs_line((data & 0x0200) ? CLEAR_LINE : ASSERT_LINE );

     /* clock line asserted: write latch or select next bit to read */
     EEPROM_set_clock_line((data & 0x0400) ? ASSERT_LINE : CLEAR_LINE );

   }
}

/*	Sailormn: the lower 2 Megabytes are banked, plus line scroll
	data is to be fetched outside of the $4000 bytes of tile RAM.	*/

static int sailormn_tile_bank = 0;

static void sailormn_tilebank_w( int bank )
{
	if (sailormn_tile_bank != bank)
	{
		sailormn_tile_bank = bank;
	}
}

WRITE16_HANDLER( sailormn_eeprom_msb_w )
{
	sailormn_tilebank_w    ( data &  0x0100 );
	cave_eeprom_w(offset,data & ~0x0100);
}

//WRITE16_HANDLER( guwange_eeprom_w )
static void guwange_eeprom_w(UINT32 offset, UINT16 data)
{
	(void)(offset);
  if ( (data & 0x00FF0000) == 0 )  /* odd address */
   {
     // latch the bit

     EEPROM_write_bit(data & 0x80);

      // reset line asserted: reset.
     EEPROM_set_cs_line((data & 0x20) ? CLEAR_LINE : ASSERT_LINE );

     // clock line asserted: write latch or select next bit to read
     EEPROM_set_clock_line((data & 0x40) ? ASSERT_LINE : CLEAR_LINE );
   }
}

/* Handles writes to the YMZ280B */
static WRITE16_HANDLER( sound_esprade_w )
{
  if (offset & 2)
    YMZ280B_data_0_w(offset, data & 0xff);
  else
    YMZ280B_register_0_w(offset, data & 0xff);
  //   }
}

static UINT8 esp_input_rb(UINT32 offset)
{
  short val;
  offset &= 3;
  switch(offset){
  case 0x00:
    val = input_buffer[0];
    break;
  case 0x01:
    val = input_buffer[1];
    break;
  case 0x02:
    val = (input_buffer[2] & 0x03) | 0xF4 |
      ( (EEPROM_read_bit() & 0x01) << 3 );
    break;
  case 0x03:
    val = input_buffer[3];
    break;
  default:
    val = 0;
    break;
  }
  return val;
}

//AD16_HANDLER( input_guwange_r )
static UINT8 guwange_input_rb(UINT32 offset)
{
  short val;
  offset &= 3;
  switch(offset){
  case 0x00:
    val = input_buffer[0];
    break;
  case 0x01:
    val = input_buffer[1];
    break;
  case 0x02:
    val = input_buffer[2];
    //     (eeprom_93c46_rb_cave() << 3);
    //   val = input_buffer[2] | ((eeprom_93c46_rb_cave() & 0x1) << 3);
    break;
      case 0x03:
   val = (input_buffer[3] & 0x7f) | ( (EEPROM_read_bit() & 0x01) << 7 );
   break;
  default:
    val = 0;
    break;
  }
  return val;
}

static UINT16 esp_input_rw(UINT32 offset)
{
   UINT16 val= (esp_input_rb(offset+0) << 8) |
          (esp_input_rb(offset+1) << 0);
   return val;
}

static UINT16 guwange_input_rw(UINT32 offset)
{
   UINT16 val= (guwange_input_rb(offset+0) << 8) |
          (guwange_input_rb(offset+1) << 0);
   return val;
}

static int stopped_68k;

static void mystop68k(UINT32 offset, UINT16 data) {
  Stop68000(0,0);
  stopped_68k = 1;
}

static int agallet_vblank_irq;

static UINT16 cave_irq_cause_r(UINT32 offset)
{

    int result = 0x0003;
    offset &= 0xf;
    offset >>=1;

    if (vblank_irq)      result ^= 0x01;
    if (unknown_irq)	result ^= 0x02;
    // if (sound_irq) result ^= 0x04;

    if (offset == 4/2)   vblank_irq = 0;
    else if (offset == 6/2)   unknown_irq = 0;
    else if (offset == 0) {
      // vblank_irq = 0;
      // if (romset != 8 && irq_status) result |= 4;
      result &= ~4;
      result |= (agallet_vblank_irq?0:4);
    }

    update_irq_state();
    return result;

}

static UINT16 soundflags_ack_r(UINT32 offset)
{
  /* bit 0 is low: can write command */
  /* bit 1 is low: can read answer */
  /*	return	((sound_flag1 | sound_flag2) ? 1 : 0) | */
  /*			((soundbuf.len>0        ) ? 0 : 2) ; */

  if (soundbuf.len == 0) {
    /* When the 68k reads this place, it waits for z80 to acknoledge a cmd. */
    /* In fact, it waits so much that it enters an infinite loop until */
    /* the z80 answers. So, we try to make the answer to arrive faster ! */
    cpu_execute_cycles(CPU_Z80_0, 1000);        // Sound Z80
  }
  return		((soundbuf.len>0        ) ? 0 : 2) ;
}

static UINT8 cave_default_eeprom_type1[16] =	{0x00,0x0C,0x11,0x0D,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x11,0x11,0xFF,0xFF,0xFF,0xFF};  /* DFeveron, Guwange */
static UINT8 cave_default_eeprom_type2[16] =	{0x00,0x0C,0xFF,0xFB,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};  /* Esprade, DonPachi, DDonPachi */
static UINT8 cave_default_eeprom_type3[16] =	{0x00,0x03,0x08,0x00,0xFF,0xFF,0xFF,0xFF,0x08,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};  /* UoPoko */
static UINT8 cave_default_eeprom_type5[16] =	{0xED,0xFF,0x00,0x00,0x12,0x31,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  /* Mazinger Z (6th byte is country code) */
static UINT8 cave_default_eeprom_type6[18] =	{0xa5,0x00,0xa5,0x00,0xa5,0x00,0xa5,0x00,0xa5,0x01,0xa5,0x01,0xa5,0x04,0xa5,0x01,0xa5,0x02};	/* Sailor Moon (last byte is country code) */
/* Air Gallet. Byte 1f is the country code (0==JAPAN,U.S.A,EUROPE,HONGKONG,TAIWAN,KOREA) */
static UINT8 cave_default_eeprom_type7[48] =
  {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
   0xff,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x02,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,
   0xff,0xff,0xff};

static void load_ddonpach(void)
{
   romset = 1;

   default_eeprom = cave_default_eeprom_type2;
   default_eeprom_size = sizeof(cave_default_eeprom_type2);

   setup_cave_sprites(&ddonpach_gfx_object);

   xcorrection = 0x11;
   gfx_colours = 256;

   RAMSize=0x80000;
   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM_BG0 = RAM + 0x020000;
   RAM_BG1 = RAM + 0x028000;
   RAM_BG2 = RAM + 0x030000;

   RAM_BG0_CTRL = RAM + 0x040000;
   RAM_BG1_CTRL = RAM + 0x040006;
   RAM_BG2_CTRL = RAM + 0x04000c;

   RAM_CTRL = RAM + 0x50100;

/*
   WriteWord68k(&ROM[0x02D4A],0x4E71);
*/
   InitPaletteMap(RAM+0x40012, 0x80, 0x100, 0x8000);

   set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(RAM,0x050012);

   Add68000Code(0,0,REGION_CPU1);
   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);   // 68000 RAM

   AddReadWord(0x300002,0x300003,YMZ280B_status_0_r,NULL);
   AddWriteWord(0x300000, 0x300003, sound_esprade_w,NULL);

   AddRWBW(0x400000, 0x40FFFF, NULL, RAM+0x010000);   // OBJECT RAM
   AddRWBW(0x500000, 0x507FFF, NULL, RAM+0x020000);   // BG0 RAM
   AddRWBW(0x600000, 0x607FFF, NULL, RAM+0x028000);   // BG1 RAM
   AddRWBW(0x700000, 0x703FFF, NULL, RAM+0x030000);   // BG2 RAM
   AddRWBW(0x704000, 0x707FFF, NULL, RAM+0x030000);   // BG2 RAM [mirror]
   AddRWBW(0x708000, 0x70BFFF, NULL, RAM+0x030000);   // BG2 RAM [mirror]
   AddRWBW(0x70C000, 0x70FFFF, NULL, RAM+0x030000);   // BG2 RAM [mirror]

   AddReadWord(0x800000, 0x800007, cave_irq_cause_r, NULL);// ?
   //AddWriteByte(0x800000, 0x80007F, esp_800000_wb, NULL);// ?
   //AddWriteWord(0x800000, 0x80007F, esp_800000_ww, NULL);// ?
   AddWriteBW(0x800000, 0x80007F, NULL, RAM_CTRL+0);

   AddRWBW(0x900000, 0x900005, NULL, RAM+0x40000);      // bg0 ctrl
   AddRWBW(0xa00000, 0xa00005, NULL, RAM+0x40006);      // bg1 ctrl

   AddRWBW(0xb00000, 0xb00005, NULL, RAM+0x4000c);      // bg2 ctrl
   AddRWBW(0xC00000, 0xC0FFFF, NULL, RAM+0x40012);   // COLOR RAM

   AddReadByte(0xD00000, 0xD00003, esp_input_rb, NULL);   // INPUT
   AddReadWord(0xD00000, 0xD00003, esp_input_rw, NULL);   // INPUT

   AddReadBW(0xe00000, 0xe00001, NULL, RAM+0x50012);   // INPUT
   AddWriteWord(0xE00000, 0xE00001, cave_eeprom_w, NULL);// EEPROM
   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);   // Trap Idle 68000

   // speed hack

   if (!strcmp(current_game->main_name,"ddonpchj")) {
     apply_hack(0x56dfa,1);

     // Disable rom check

     pWriteWord(&ROM[0x53f6],0x4e71);
     pWriteWord(&ROM[0x5400],0x6008);

     // remove pause between letters on copyright screen
     pWriteWord(&ROM[0x56dc2],0x4e75);
   } else { // international version (new set)
     apply_hack(0x571b2,1);

     // Disable rom check

     pWriteWord(&ROM[0x53ea],0x4e71);
     pWriteWord(&ROM[0x53f4],0x6008);

     // remove pause between letters on copyright screen
     pWriteWord(&ROM[0x5717a],0x4e75);
   }

   // WriteWord(&ROM[0x56e00],0x4e71);

   setup_cave_game();
}

static WRITE16_HANDLER( nmk_oki6295_bankswitch_w )
{
  /* The OKI6295 ROM space is divided in four banks, each one indepentently
     controlled. The sample table at the beginning of the addressing space is
     divided in four pages as well, banked together with the sample data. */

#define TABLESIZE 0x100
#define BANKSIZE 0x10000

  int chip,banknum,size,bankaddr;
  unsigned char *rom;
  offset -= 0xb00020;
  offset >>=1;

  chip	=	offset / 4;
  banknum	=offset % 4;

  rom = load_region[REGION_SMP1 + chip];
  size	= get_region_size(REGION_SMP1 + chip) - 0x40000;

  bankaddr =	(data * BANKSIZE) % size;	// % used: size is not a power of 2

  /* copy the samples */
  memcpy(rom + banknum * BANKSIZE,rom + 0x40000 + bankaddr,BANKSIZE);

  /* and also copy the samples address table (only for chip #1) */
  if (chip==1)
    {
      rom += banknum * TABLESIZE;
      memcpy(rom,rom + 0x40000 + bankaddr,TABLESIZE);
    }
}

static void load_donpachi(void)
{
  romset =1; // like ddonpach
  default_eeprom = cave_default_eeprom_type2;
  default_eeprom_size = sizeof(cave_default_eeprom_type2);

  setup_cave_sprites(&ddonpach_gfx_object);
  xcorrection = 0x13;

  gfx_colours = 16;

  RAMSize=0x80000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  RAM_BG0 = RAM + 0x028000;
  RAM_BG1 = RAM + 0x020000;
  RAM_BG2 = RAM + 0x030000;

  RAM_BG1_CTRL = RAM + 0x038000;
  RAM_BG0_CTRL = RAM + 0x038006;
  RAM_BG2_CTRL = RAM + 0x03800c;

  RAM_CTRL = RAM + 0x38020;

/*
   WriteWord68k(&ROM[0x02D4A],0x4E71);
*/
   InitPaletteMap(RAM+0x38100, 0x80, 0x10, 0x8000);

   set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

/*
 *  StarScream Stuff follows
 */

   // 68000 speed hack

   ByteSwap(ROM,0x80000);
   ByteSwap(RAM,0x050012);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x07FFFF, NULL, ROM+0x000000);   // 68000 ROM
   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);   // 68000 RAM
   AddRWBW(0x200000, 0x207FFF, NULL, RAM+0x020000);   // BG1
   AddRWBW(0x300000, 0x307FFF, NULL, RAM+0x028000);   // BG0
   AddRWBW(0x400000, 0x403FFF, NULL, RAM+0x030000);   // BG2
   AddRWBW(0x404000, 0x407FFF, NULL, RAM+0x030000);   // BG2 (mirror)
   AddRWBW(0x500000, 0x50fFFF, NULL, RAM+0x010000);   // Sprites

   AddRWBW(0x600000, 0x600005, NULL, RAM+0x38000);      // bg1 ctrl
   AddRWBW(0x700000, 0x700005, NULL, RAM+0x38006);      // bg0 ctrl
   AddRWBW(0x800000, 0x800005, NULL, RAM+0x3800c);      // bg2 ctrl
   AddRWBW(0x900000, 0x90007f, NULL, RAM+0x38020);      // sprites ctrl

   AddRWBW(0xa08000, 0xa08FFF, NULL, RAM+0x38100);   // COLOR RAM

   AddReadWord(0xb00000, 0xb00001, OKIM6295_status_0_r, NULL);
   AddReadWord(0xb00010, 0xb00011, OKIM6295_status_1_r, NULL);
   AddWriteWord(0xb00000, 0xb00001, OKIM6295_data_0_w, NULL);
   AddWriteWord(0xb00010, 0xb00011, OKIM6295_data_1_w, NULL);
   AddWriteWord(0xb00020, 0xb0002f, nmk_oki6295_bankswitch_w, NULL);

   AddReadByte(0xc00000, 0xc00003, esp_input_rb, NULL);   // INPUT
   AddReadWord(0xc00000, 0xc00003, esp_input_rw, NULL);   // INPUT

   AddWriteWord(0xd00000, 0xd00001, cave_eeprom_w, NULL);// EEPROM

   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);   // Trap Idle 68000

   // speed hack

   apply_hack(0x2edc,1);

   // Disable rom check

   if (!strcmp(current_game->main_name,"donpachj")) { // normal
     pWriteWord(&ROM[0x3428a],0x6008);
   } else if (!strcmp(current_game->main_name,"donpachk")) { // Korean version
     pWriteWord(&ROM[0x348ce],0x6008);
   } else if (!strcmp(current_game->main_name,"donpachi")) { // usa
     pWriteWord(&ROM[0x3437c],0x6008);
   }

   setup_cave_game();
}

/* Main CPU: read the latch written by the sound CPU (acknowledge) */
static READ16_HANDLER( soundlatch_ack_r )
{
  if (soundbuf.len>0) {
    UINT8 data = soundbuf.data[0];
    memmove(soundbuf.data,soundbuf.data+1,(SOUND_BUFLEN-1)*sizeof(soundbuf.data[0]));
    soundbuf.len--;
    return data;
  }
  return 0xff;
}

/* Sound CPU: write latch for the main CPU (acknowledge) */
static WRITE_HANDLER( soundlatch_ack_w )
{
  soundbuf.data[soundbuf.len] = data;
  if (soundbuf.len<SOUND_BUFLEN-1)
    soundbuf.len++;
}

// This is a ugly bankswitch for sound, with lots of memcpy.
// But for now I am more interested to know wether it works or not.
WRITE_HANDLER( hotdogst_okibank_w )
{
  data8_t *RAM = load_region[REGION_SMP1];
  int bank1 = (data >> 0) & 0x3;
  int bank2 = (data >> 4) & 0x3;
  if (audio_sample_rate == 0)	return;
  memcpy(RAM + 0x20000 * 0, RAM + 0x40000 + 0x20000 * bank1, 0x20000);
  memcpy(RAM + 0x20000 * 1, RAM + 0x40000 + 0x20000 * bank2, 0x20000);
}

static void mazinger_rombank_w(UINT32 offset, UINT8 data)
{
  int bank = (data) & 0x07;
  if (bank > 0) bank--;
  z80a_set_bank(0,bank);
}

static void hotdogst_rombank_w(UINT32 offset, UINT8 data)
{
  int bank = (data) & 0x0f;
  if (bank > 0) bank--;
  z80a_set_bank(0,bank);
}

static void sailormn_rombank_w(UINT32 offset, UINT8 data)
{
  int bank = data & 0x1f;
  //if (bank > 0) bank--;
  z80a_set_bank(0,bank);
}

static struct ROMSW_DATA romsw_data_mazinger[] =
{
   { "Japan",           0x30 },
   { "World",           0x31 },
   { NULL,                    0    },
};

static struct ROMSW_DATA romsw_data_sailormn[] =
{
   { "Japan",           0x00 },
   { "USA",             0x01 },
   { "Europe",          0x02 },
   { "Hong Kong",       0x03 },
   { "Taiwan",          0x04 },
   { "Korea",           0x05 },
   { NULL,                    0    },
};

static struct ROMSW_INFO romsw_mazinger[] =
{
  { 0xaa0001, 0x31, romsw_data_mazinger },
  { 0,        0,    NULL },
};

static struct ROMSW_INFO romsw_agallet[] =
{
  { 0xaa0001, 0x02, romsw_data_sailormn },
  { 0,        0,    NULL },
};

static void load_mazinger()
{
  UINT8 *Z80RAM;
  unsigned char *buffer;
  int len = get_region_size(REGION_GFX4);
  data8_t *src = load_region[REGION_GFX4]; // AllocateMem(len);
  // memcpy(src,load_region[REGION_GFX4],get_region_size(REGION_GFX4));

  /* decrypt sprites */

  if ((buffer = malloc(len))){
    int i;
    for (i = 0;i < len; i++)
      buffer[i ^ 0xdf88] = src[BITSWAP24(i,23,22,21,20,19,9,7,3,15,4,17,14,18,2,16,5,11,8,6,13,1,10,12,0)];
    memcpy(src,buffer,len);
    free(buffer);
  }

  romset =6; // palette + sprite placement

  gfx_colours = 16;
  unpack_region_lsb(REGION_GFX4);
  setup_cave_sprites(NULL);

  RAMSize=0x80000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  RAM_BG0 = RAM + 0x028000;
  RAM_BG1 = RAM + 0x020000;

  RAM_BG1_CTRL = RAM + 0x038000;
  RAM_BG0_CTRL = RAM + 0x038006;

  RAM_CTRL = RAM + 0x38020;

/*
   WriteWord68k(&ROM[0x02D4A],0x4E71);
*/
   InitPaletteMap(RAM+0x38100, 0x80, gfx_colours, 0x8000);
   init_16x16_zoom_64(); // Should have zoom...

   set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

   default_eeprom = cave_default_eeprom_type5;
   default_eeprom_size = sizeof(cave_default_eeprom_type5);

   Z80ROM=load_region[REGION_ROM2];
   Z80RAM=RAM+0x50000; // Too much ram for sure !
   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066); // ???!
   z80_init_banks(0,REGION_ROM2,0x4000,0x4000);
   z80a_set_bank(0,0);

   AddZ80AReadByte(0x0000, 0x7fFF, NULL,  NULL); // Z80 ROM + bank
   AddZ80AReadByte(0xc000, 0xc7FF, NULL,  Z80RAM+0x0000); // RAM
   AddZ80AReadByte(0xf800, 0xffFF, NULL,  Z80RAM+0x0800); // RAM

   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,       NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                NULL);

   AddZ80AWriteByte(0xc000, 0xc7FF, NULL,  Z80RAM+0X0000); // RAM
   AddZ80AWriteByte(0xf800, 0xffFF, NULL,  Z80RAM+0X0800); // RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,     NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,               NULL);

   AddZ80AReadPort(0x30, 0x30, soundlatch_lo_r,  NULL);
   AddZ80AReadPort(0x52, 0x52, YM2203_status_port_0_r, NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadPortZ80,       NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0x0, 0x0, mazinger_rombank_w, NULL);
   AddZ80AWritePort(0x10, 0x10, soundlatch_ack_w, NULL);
   AddZ80AWritePort(0x50, 0x50, YM2203_control_port_0_w, NULL);
   AddZ80AWritePort(0x51, 0x51, YM2203_write_port_0_w, NULL);
   AddZ80AWritePort(0x70, 0x70, OKIM6295_data_0_w, NULL);
   AddZ80AWritePort(0x74, 0x74, hotdogst_okibank_w, NULL);
   AddZ80AWritePort(0x00, 0xFF, DefBadWritePortZ80, NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

/*
 *  StarScream Stuff follows
 */

   // ByteSwap(RAM,0x040000);
   // WriteWord(&ROM[0x1d92],0x4e71); // Stupid useless loop...
   AddResetHandler(&quiet_reset_handler);

   Add68000Code(0,0, REGION_ROM1);
   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);   // 68000 RAM
   AddRWBW(0x200000, 0x20fFFF, NULL, RAM+0x010000);   // Sprites
   AddReadBW(0x300000, 0x300007, cave_irq_cause_r, NULL);

   // This watchdog is quite unefficient. I prefer to do without (too slow
   // to react).
   // AddWriteWord(0x300068, 0x300069, watchdog_reset_w, NULL);
   AddReadWord(0x30006e, 0x30006f, soundlatch_ack_r, NULL);
   AddWriteByte(0x30006e, 0x30006f, sail_soundcmd_wb, NULL);
   AddWriteWord(0x30006e, 0x30006f, sail_soundcmd_w, NULL);
   AddWriteBW( 0x300000, 0x30007f, NULL, RAM_CTRL+0); // video regs

   AddRWBW(0x404000, 0x407FFF, NULL, RAM_BG1);   // BG1
   AddRWBW(0x504000, 0x507FFF, NULL, RAM_BG0);   // BG0
   AddRWBW(0x600000, 0x600005, NULL, RAM_BG1_CTRL);      // bg1 ctrl
   AddRWBW(0x700000, 0x700005, NULL, RAM_BG0_CTRL);      // bg0 ctrl

   AddReadByte(0x800000, 0x800003, esp_input_rb, NULL);   // INPUT
   AddReadWord(0x800000, 0x800003, esp_input_rw, NULL);   // INPUT

   AddWriteWord(0x900000, 0x900001, cave_eeprom_w, NULL);// EEPROM

   AddRWBW(0xc08000, 0xc0fFFF, NULL, RAM+0x38100);   // COLOR RAM

   Add68000Code(0, 0xd00000, REGION_ROM3);      // 68000 ROM

   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);   // Trap Idle 68000
   cave_region_pos = 0x05;
   AddWriteByte(0xAA0001, 0xAA0001, NULL, ((UINT8*)&cave_region_byte)+1);   // Trap Idle 68000

   // Speed hack

   WriteWord(&ROM[0x64fc],0x4239); // clr.b $aa0000
   WriteWord(&ROM[0x64fe],0xaa);
   WriteWord(&ROM[0x6500],0);
   WriteWord(&ROM[0x6502],0x4e71);

   WriteWord(&ROM[0x2014],0x4e71); // disable rom check (nop)
   WriteWord(&ROM[0x2016],0x4e71);
   setup_cave_game();

   adpcm_amplify = 3;
}

WRITE_HANDLER( sailormn_okibank0_w )
{
  UINT8 *RAM = load_region[REGION_SMP1];
  int bank1 = (data >> 0) & 0xf;
  int bank2 = (data >> 4) & 0xf;
  if (audio_sample_rate == 0)	return;
  memcpy(RAM + 0x20000 * 0, RAM + 0x40000 + 0x20000 * bank1, 0x20000);
  memcpy(RAM + 0x20000 * 1, RAM + 0x40000 + 0x20000 * bank2, 0x20000);
}

WRITE_HANDLER( sailormn_okibank1_w )
{
  UINT8 *RAM = load_region[REGION_SMP2];
  int bank1 = (data >> 0) & 0xf;
  int bank2 = (data >> 4) & 0xf;
  if (audio_sample_rate == 0)	return;
  memcpy(RAM + 0x20000 * 0, RAM + 0x40000 + 0x20000 * bank1, 0x20000);
  memcpy(RAM + 0x20000 * 1, RAM + 0x40000 + 0x20000 * bank2, 0x20000);
}

static UINT8 soundflags_r(UINT32 offset) {
  return 0;
}

/* Tiles are 6 bit, 4 bits stored in one rom, 2 bits in the other.
   Expand the 2 bit part into a 4 bit layout, so we can decode it */
static void sailormn_unpack_tiles( const int region )
{
  unsigned char *src = load_region[region] + (get_region_size(region)/4)*3 - 1;
  unsigned char *dst = load_region[region] + (get_region_size(region)/4)*4 - 2;

  while(src <= dst)
    {
      unsigned char data = src[0];

      dst[0] = ((data & 0x03) << 4) + ((data & 0x0c) >> 2);
      dst[1] = ((data & 0x30) >> 0) + ((data & 0xc0) >> 6);

      src -= 1;
      dst -= 2;
    }
}

static int supplement;

static void init_sailormn_hardware(int type)
{
  // Type : 0 = sailormoon, 1 = agallet
  UINT8 *Z80RAM;
  unsigned char *buffer;
  data8_t *src = load_region[REGION_GFX4];
  int len = get_region_size(REGION_GFX4);
  setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(8,60));
  set_pulse_time(3); // for coin key...

  load_message(_("Decrypting sprites"));
  /* decrypt sprites */

  if (type == 0) {
    if ((buffer = malloc(len))){
      int i;
      for (i = 0;i < len; i++)
	buffer[i ^ 0x950c4] = src[BITSWAP24(i,23,22,21,20,15,10,12,6,11,1,13,3,16,17,2,5,14,7,18,8,4,19,9,0)];
      memcpy(src,buffer,len);
      free(buffer);
    }
  }

  sailormn_unpack_tiles(REGION_GFX3);

  unpack_region_lsb(REGION_GFX4);
  setup_cave_sprites(NULL);

  gfx_colours = 16;
  layer_base[1] = 0x80;
  layer_base[2] = 0xc0;
  if (type == 0) {
    romset =12; // sprite placement + custom bg2
  } else if (type == 1) {
    romset = 8; // Just a specific bg2, à la sailor moon...
  }

  load_message(_("Preparing ROMS (patches...)"));
  RAMSize=0x80000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  RAM_BG0 = RAM + 0x020000;
  RAM_BG1 = RAM + 0x028000;
  RAM_BG2 = RAM + 0x030000;

  RAM_BG0_CTRL = RAM + 0x048080;
  RAM_BG1_CTRL = RAM + 0x048088;
  RAM_BG2_CTRL = RAM + 0x048090;

  RAM_CTRL = RAM + 0x48100;

  InitPaletteMap(RAM+0x38100, 0x200, gfx_colours, 0x8000);
  init_16x16_zoom_64(); // Should have zoom...

  set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

  Z80ROM=load_region[REGION_ROM2];
  memcpy(Z80ROM,Z80ROM+0x4000,0x4000); // Bank0 = ROM

  Z80RAM=RAM+0x50000; // Too much ram for sure !
  AddZ80AROMBase(Z80ROM, 0x0038, 0x0066); // ???!
  z80_init_banks(0,REGION_ROM2,0x4000,0x4000);
  z80a_set_bank(0,0);

  AddZ80AReadByte(0x0000, 0x7fFF, NULL,  NULL); // Z80 ROM + bank
  AddZ80AReadByte(0xc000, 0xdfff, NULL,  Z80RAM+0x0000); // RAM
  AddZ80AReadByte(0xe000, 0xffff, NULL,  Z80RAM+0X0000); // RAM (mirror)

  AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,       NULL);
  AddZ80AReadByte(    -1,     -1, NULL,                NULL);

  AddZ80AWriteByte(0xc000, 0xdfff, NULL,  Z80RAM+0X0000); // RAM
  AddZ80AWriteByte(0xe000, 0xffff, NULL,  Z80RAM+0X0000); // RAM (mirror)
  AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,     NULL);
  AddZ80AWriteByte(    -1,     -1, NULL,               NULL);

  AddZ80AReadPort(0x20, 0x20, soundflags_r, NULL);
  AddZ80AReadPort(0x30, 0x30, soundlatch_lo_r, NULL);
  AddZ80AReadPort(0x40, 0x40, soundlatch_hi_r, NULL);
  AddZ80AReadPort(0x51, 0x51, YM2151_status_port_0_r, NULL);
  AddZ80AReadPort(0x60, 0x60, OKIM6295_status_0_r, NULL);
  AddZ80AReadPort(0x80, 0x80, OKIM6295_status_1_r, NULL);

  AddZ80AReadPort(0x00, 0xFF, DefBadReadPortZ80,       NULL);
  AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

  AddZ80AWritePort(0x0, 0x0, sailormn_rombank_w, NULL);
  AddZ80AWritePort(0x10, 0x10, soundlatch_ack_w, NULL);
  AddZ80AWritePort(0x50, 0x50, YM2151_register_port_0_w, NULL);
  AddZ80AWritePort(0x51, 0x51, YM2151_data_port_0_w, NULL);
  AddZ80AWritePort(0x60, 0x60, OKIM6295_data_0_w, NULL);
  AddZ80AWritePort(0x70, 0x70, sailormn_okibank0_w, NULL);
  AddZ80AWritePort(0x80, 0x80, OKIM6295_data_1_w, NULL);
  AddZ80AWritePort(0xc0, 0xc0, sailormn_okibank1_w, NULL);
  AddZ80AWritePort(0x00, 0xFF, DefBadWritePortZ80, NULL);
  AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

  AddZ80AInit();

/*
 *  StarScream Stuff follows
 */

  ByteSwap(ROM,get_region_size(REGION_ROM1));
  ByteSwap(RAM,0x040000);
  // WriteWord(&ROM[0x1d92],0x4e71); // Stupid useless loop...
  AddResetHandler(&quiet_reset_handler);

  //AddReadBW(0xaa0002, 0xaa0005, my_testw, NULL);
  AddMemFetch(0x000000, 0x07FFFF, ROM+0x000000-0x000000);      // 68000 ROM
  if (type == 0)
    AddMemFetch(0x200000, 0x3fffff, ROM-0x200000); // 2nd part...
  // romcheck in 4cc (for sailormoon)
  AddReadBW(0x000000, 0x07FFFF, NULL, ROM+0x000000);   // 68000 ROM
  AddRWBW(  0x100000, 0x10FFFF, NULL, RAM+0x000000);   // 68000 RAM
  // These are for agallet, to pass the ram checks
  AddRWBW(  0x110000, 0x110003, NULL, (UINT8*)&supplement);
  AddRWBW(  0x410000, 0x410003, NULL, (UINT8*)&supplement);
  AddRWBW(  0x908000, 0x908003, NULL, (UINT8*)&supplement);
  AddRWBW(  0x510000, 0x510003, NULL, (UINT8*)&supplement);

  if (type == 0) {
    AddReadBW(0x200000, 0x3ffFFF, NULL, ROM+0x200000);   // 2nd ROM
    AddRWBW(0x408000, 0x40bfff, NULL, RAM+0x38100); // palette
  } else if (type == 1) {
    AddRWBW(0x400000, 0x407fff, NULL, RAM+0x38100); // palette ??
    AddRWBW(0x408000, 0x40ffff, NULL, RAM+0x38100); // palette
    // AddRWBW(0x40a000, 0x40ffff, NULL, RAM+0x60000); // palette (dummy)
  }
  AddRWBW(0x500000, 0x50fFFF, NULL, RAM+0x010000);   // Sprites

  AddReadByte(0x600000, 0x600003, esp_input_rb, NULL);   // INPUT
  AddReadWord(0x600000, 0x600003, esp_input_rw, NULL);   // INPUT

  AddWriteWord(0x700000, 0x700001, sailormn_eeprom_msb_w, NULL);

  AddRWBW(0x800000, 0x807FFF, NULL, RAM_BG0);   // BG0
  AddRWBW(0x880000, 0x887FFF, NULL, RAM_BG1);   // BG1
  AddRWBW(0x900000, 0x907FFF, NULL, RAM_BG2);   // BG2

  AddRWBW(0xa00000, 0xa00005, NULL, RAM_BG0_CTRL);      // bg0 ctrl
  AddRWBW(0xa80000, 0xa80005, NULL, RAM_BG1_CTRL);      // bg1 ctrl
  AddRWBW(0xb00000, 0xb00005, NULL, RAM_BG2_CTRL);      // bg2 ctrl

  AddReadBW(0xb80000, 0xb80007, cave_irq_cause_r, NULL);

  AddReadWord(0xb8006c, 0xb8006d, soundflags_ack_r, NULL);
  AddReadWord(0xb8006e, 0xb8006f, soundlatch_ack_r, NULL);

  AddWriteByte(0xb8006e, 0xb8006f, sail_soundcmd_wb, NULL);
  AddWriteWord(0xb8006e, 0xb8006f, sail_soundcmd_w, NULL);
  AddRWBW( 0xb80000, 0xb8007f, NULL, RAM_CTRL+0); // video regs

  AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);   // Trap Idle 68000
  cave_region_pos = 0x11;
  AddWriteByte(0xAA0001, 0xAA0001, NULL, ((UINT8*)&cave_region_byte)+1);   // Trap Idle 68000

  if (type == 1) {
    // Air Gallet
    /*    // Disable romcheck */
    WriteLong(&ROM[0x104d8],0x4e714e71);

    // Disable RAM check
    //WriteLong(&ROM[0x104aa],0x4e714e71);

    // Speed hack
     apply_hack(0xcdb8,4);
     pWriteWord(&ROM[0xcdbe],0x600c);

/*      HACK(0xe460); */
/*      WriteWord(&ROM[0xe466],0x6002); */

     // This stupid game is testing its video hardware to wait for a vbl
     // instead of using a hardware interrupt like the others.
     // The problem is that the vbl emulation is rather unprecise (we would
     // need something like the sound timers, and well, it seems quite useless)
     // So this code is just removing all the tests for the vbl, relying
     // on the speed hack just before...
     // Notice : these hacks make the game to run better, but you can do
     // without them. For this just add something like :
     // execute_one_z80_audio_frame(frame-1000);
     // sound_irq = 1;
     // execute_one_z80_audio_frame(1000);
     // sound_irq = 0;
     // But it's a rough approximation, and patching the rom is better !

     pWriteWord(&ROM[0x2ce],0x4e71);
     pWriteWord(&ROM[0x33c],0x4e71);
     pWriteWord(&ROM[0xc884],0x4e71);
     pWriteWord(&ROM[0xcdca],0x4e71);
     pWriteWord(&ROM[0xd3c4],0x4e71);
     pWriteWord(&ROM[0xd3da],0x4e71);
     pWriteWord(&ROM[0xd404],0x4e71);
     pWriteWord(&ROM[0xd41a],0x4e71);
     pWriteWord(&ROM[0xd89e],0x4e71);
     pWriteWord(&ROM[0xd932],0x4e71);
     pWriteWord(&ROM[0xd958],0x4e71);
     pWriteWord(&ROM[0xd988],0x4e71);
     pWriteWord(&ROM[0xe468],0x4e71);

     pWriteWord(&ROM[0xd14c],0x4e71);
     pWriteWord(&ROM[0xd162],0x4e71);
     pWriteWord(&ROM[0xd178],0x4e71);
     pWriteWord(&ROM[0xd0e8],0x4e71);
     pWriteWord(&ROM[0xd2f2],0x4e71);
     pWriteWord(&ROM[0xb4ae],0x4e71);
     pWriteWord(&ROM[0xb4be],0x4e71);
     pWriteWord(&ROM[0xb4ce],0x4e71);
     pWriteWord(&ROM[0xb4de],0x4e71);
     pWriteWord(&ROM[0xcede],0x4e71);
  } else if (type == 0) {
    apply_hack(0x738,1); // clr.b $aa0000
    // disable rom check (tricky...)
    // d0 contains a bit mask of the cmp results.
    // 3fc -> bad ram, 7fc -> everything good...
    // The 2 writes below force everything correct...
    // WriteWord(&ROM[0x504],0x203c);
    // WriteLong(&ROM[0x506],0x7fc0000);

    // The or below forces at least the rom correct.
    // Notice the game seems to work correctly even when it detects the rom
    // is bad, but I prefer to avoid bad surprises later...
    pWriteWord(&ROM[0x504],0); // or
    pWriteWord(&ROM[0x506],0x14);
    pWriteWord(&ROM[0x508],0x4e71);
  }

  setup_cave_game();
}

static void load_sailormn() {
  default_eeprom = cave_default_eeprom_type6;
  default_eeprom_size = sizeof(cave_default_eeprom_type6);
  init_sailormn_hardware(0);
}

static void load_agallet() {
  default_eeprom = cave_default_eeprom_type7;
  default_eeprom_size = sizeof(cave_default_eeprom_type7);
  init_sailormn_hardware(1);
  cave_region_pos = 0x1f;
  // xcorrection = 0x12;
}

static void load_hotdogst(void)
{
  UINT8 *Z80RAM;

  romset =6; // palette shared + sprite placement different...

  gfx_colours = 16;
  setup_cave_sprites(&cave_gfx_object);

  RAMSize=0x80000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  RAM_BG0 = RAM + 0x028000;
  RAM_BG1 = RAM + 0x020000;
  RAM_BG2 = RAM + 0x030000;

  RAM_BG1_CTRL = RAM + 0x038000;
  RAM_BG0_CTRL = RAM + 0x038006;
  RAM_BG2_CTRL = RAM + 0x03800c;

  RAM_CTRL = RAM + 0x38020;

/*
   WriteWord68k(&ROM[0x02D4A],0x4E71);
*/
   InitPaletteMap(RAM+0x38100, 0x80, 0x10, 0x8000);
   init_16x16_zoom_64(); // Should have zoom...

   set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

   Z80ROM=load_region[REGION_ROM2];
   Z80RAM=RAM+0x50000; // Too much ram for sure !
   AddZ80AROMBase(Z80ROM, 0x0038, 0x0066); // ???!

   z80_init_banks(0,REGION_ROM2,0x4000,0x4000);
   z80a_set_bank(0,0);

   AddZ80AReadByte(0x0000, 0x7fFF, NULL,  NULL); // Z80 ROM + Bank
   AddZ80AReadByte(0xe000, 0xFFFF, NULL,  Z80RAM+0X0000); // RAM
   AddZ80AReadByte(0x0000, 0xFFFF, DefBadReadZ80,       NULL);
   AddZ80AReadByte(    -1,     -1, NULL,                NULL);

   AddZ80AWriteByte(0xe000, 0xffFF, NULL, Z80RAM+0x0000); // Z80 RAM
   AddZ80AWriteByte(0x0000, 0xFFFF, DefBadWriteZ80,     NULL);
   AddZ80AWriteByte(    -1,     -1, NULL,               NULL);

   AddZ80AReadPort(0x30, 0x30, soundlatch_lo_r,  NULL);
   AddZ80AReadPort(0x40, 0x40, soundlatch_hi_r,  NULL);
   AddZ80AReadPort(0x50, 0x50, YM2203_status_port_0_r, NULL);
   AddZ80AReadPort(0x51, 0x51, YM2203_read_port_0_r, NULL);
   AddZ80AReadPort(0x60, 0x60, OKIM6295_status_0_r, NULL);
   AddZ80AReadPort(0x00, 0xFF, DefBadReadZ80,           NULL);
   AddZ80AReadPort(  -1,   -1, NULL,                    NULL);

   AddZ80AWritePort(0x0, 0x0, hotdogst_rombank_w, NULL);
   AddZ80AWritePort(0x50, 0x50, YM2203_control_port_0_w, NULL);
   AddZ80AWritePort(0x51, 0x51, YM2203_write_port_0_w, NULL);
   AddZ80AWritePort(0x60, 0x60, OKIM6295_data_0_w, NULL);
   AddZ80AWritePort(0x70, 0x70, hotdogst_okibank_w, NULL);
   AddZ80AWritePort(0x01, 0xFF, DefBadWriteZ80,         NULL);
   AddZ80AWritePort(  -1,   -1, NULL,                   NULL);

   AddZ80AInit();

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x040000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x0fFFFF, NULL, ROM+0x000000);   // 68000 ROM
   AddRWBW(0x300000, 0x30FFFF, NULL, RAM+0x000000);   // 68000 RAM
   AddRWBW(0x880000, 0x887FFF, NULL, RAM_BG0);   // BG0
   AddRWBW(0x900000, 0x907FFF, NULL, RAM_BG1);   // BG1
   AddRWBW(0x980000, 0x987FFF, NULL, RAM_BG2);   // BG2

   AddWriteWord(0xa8006e, 0xa8006f, soundcmd_w, NULL);
   AddWriteByte(0xa8006e, 0xa8006f, soundcmd_wb, NULL);

   AddReadWord(0xa80000, 0xa80007, cave_irq_cause_r, NULL);
   AddWriteBW( 0xa80000, 0xa8007f, NULL, RAM_CTRL+0);
   AddRWBW(0xf00000, 0xf0fFFF, NULL, RAM+0x010000);   // Sprites

   AddRWBW(0xb00000, 0xb00005, NULL, RAM_BG0_CTRL);      // bg0 ctrl
   AddRWBW(0xb80000, 0xb80005, NULL, RAM_BG1_CTRL);      // bg1 ctrl
   AddRWBW(0xc00000, 0xc00005, NULL, RAM_BG2_CTRL);      // bg2 ctrl

   AddRWBW(0x408000, 0x408FFF, NULL, RAM+0x38100);   // COLOR RAM

   AddReadByte(0xc80000, 0xc80003, esp_input_rb, NULL);   // INPUT
   AddReadWord(0xc80000, 0xc80003, esp_input_rw, NULL);   // INPUT

   AddWriteWord(0xd00000, 0xd00001, cave_eeprom_w, NULL);// EEPROM
   AddWriteWord(0xd00002, 0xd00003, NULL, RAM+0x380a0); // ???

   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);   // Trap Idle 68000

   // Speed hack

   apply_hack(0x634,1); // clr.b $aa0000

   setup_cave_game();
   adpcm_amplify = 2;
}

static void load_esprade(void)
{
  UINT32 hack_adr;
  romset = 0;

  setup_nolayouts();
  setup_cave_sprites(NULL);
  default_eeprom = cave_default_eeprom_type2;
  default_eeprom_size = sizeof(cave_default_eeprom_type2);

  gfx_colours = 256;

  RAMSize=0x80000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  RAM_BG0 = RAM + 0x020000;
  RAM_BG1 = RAM + 0x028000;
  RAM_BG2 = RAM + 0x030000;

  RAM_BG0_CTRL = RAM + 0x048080;
  RAM_BG1_CTRL = RAM + 0x048088;
  RAM_BG2_CTRL = RAM + 0x048090;

  RAM_CTRL = RAM + 0x48100;

  // 68000 speed hack

   if (!strcmp(current_game->main_name,"espradeo")) // normal
     hack_adr = 0x4f156;
   else if (!strcmp(current_game->main_name,"espradej")) // japan
     hack_adr = 0x4f158;
   else if (!strcmp(current_game->main_name,"esprade")) // new set
     hack_adr = 0x4f382;

  InitPaletteMap(RAM+0x38000, 0x80, 0x100, 0x8000);
  init_16x16_zoom_64();

  set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x048000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);         // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);         // 68000 RAM
   AddReadWord(0x300002,0x300003,YMZ280B_status_0_r,NULL);
   AddWriteWord(0x300000, 0x300003, sound_esprade_w,NULL);

   AddReadByte(0x400000, 0x40FFFF, NULL, RAM+0x010000);         // OBJECT RAM
   AddReadByte(0x500000, 0x507FFF, NULL, RAM+0x020000);         // BG0 RAM
   AddReadByte(0x600000, 0x607FFF, NULL, RAM+0x028000);         // BG1 RAM
   AddReadByte(0x700000, 0x707FFF, NULL, RAM+0x030000);         // BG2 RAM
   AddReadBW(0x800000, 0x800007, cave_irq_cause_r, NULL);      // ?
   AddReadByte(0xC00000, 0xC0FFFF, NULL, RAM+0x038000);         // COLOR RAM
   AddReadByte(0xD00000, 0xD00003, esp_input_rb, NULL);         // INPUT

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);         // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);         // 68000 RAM
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM+0x010000);         // OBJECT RAM
   AddReadWord(0x500000, 0x507FFF, NULL, RAM+0x020000);         // BG0 RAM
   AddReadWord(0x600000, 0x607FFF, NULL, RAM+0x028000);         // BG1 RAM
   AddReadWord(0x700000, 0x707FFF, NULL, RAM+0x030000);         // BG2 RAM
   AddReadWord(0x900000, 0x900007, NULL, RAM+0x048080);      // BG0 CTRL RAM
   AddReadWord(0xA00000, 0xA00007, NULL, RAM+0x048088);      // BG1 CTRL RAM
   AddReadWord(0xB00000, 0xB00007, NULL, RAM+0x048090);      // BG2 CTRL RAM
   AddReadWord(0xC00000, 0xC0FFFF, NULL, RAM+0x038000);         // COLOR RAM
   AddReadWord(0xD00000, 0xD00003, esp_input_rw, NULL);         // INPUT

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);      // 68000 RAM
   AddWriteByte(0x400000, 0x40FFFF, NULL, RAM+0x010000);      // OBJECT RAM
   AddWriteByte(0x500000, 0x507FFF, NULL, RAM+0x020000);      // BG0 RAM
   AddWriteByte(0x600000, 0x607FFF, NULL, RAM+0x028000);      // BG1 RAM
   AddWriteByte(0x700000, 0x707FFF, NULL, RAM+0x030000);      // BG2 RAM
   //AddWriteByte(0x800000, 0x80007F, esp_800000_wb, NULL);      // ?
   AddWriteByte(0xC00000, 0xC0FFFF, NULL, RAM+0x038000);      // COLOR RAM
   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);         // Trap Idle 68000
   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);      // 68000 RAM
   AddWriteWord(0x400000, 0x40FFFF, NULL, RAM+0x010000);      // OBJECT RAM
   AddWriteWord(0x500000, 0x507FFF, NULL, RAM+0x020000);      // BG0 RAM
   AddWriteWord(0x600000, 0x607FFF, NULL, RAM+0x028000);      // BG1 RAM
   AddWriteWord(0x700000, 0x707FFF, NULL, RAM+0x030000);      // BG2 RAM
   AddWriteWord(0xC00000, 0xC0FFFF, NULL, RAM+0x038000);      // COLOR RAM
   AddWriteWord(0xE00000, 0xE00001, cave_eeprom_w, NULL);      // EEPROM
   //AddWriteWord(0x800000, 0x80007F, esp_800000_ww, NULL);      // ?
   AddWriteBW(0x800000, 0x80007F, NULL, RAM_CTRL+0);
   AddWriteWord(0x900000, 0x900007, NULL, RAM+0x048080);      // BG0 CTRL RAM
   AddWriteWord(0xA00000, 0xA00007, NULL, RAM+0x048088);      // BG1 CTRL RAM
   AddWriteWord(0xB00000, 0xB00007, NULL, RAM+0x048090);      // BG2 CTRL RAM
   setup_cave_game();
   apply_hack(hack_adr,1);
}

static void load_guwange(void)
{
   // Guwange has exactly the same gfx handling as esprade...
   romset = 0;

   default_eeprom = cave_default_eeprom_type1;
   default_eeprom_size = sizeof(cave_default_eeprom_type1);

   setup_nolayouts();
  setup_cave_sprites(NULL);
  gfx_colours = 256;

  RAMSize=0x80000;
  if(!(RAM=AllocateMem(RAMSize))) return;

  RAM_BG0 = RAM + 0x020000;
  RAM_BG1 = RAM + 0x028000;
  RAM_BG2 = RAM + 0x030000;

  RAM_BG0_CTRL = RAM + 0x048080;
  RAM_BG1_CTRL = RAM + 0x048088;
  RAM_BG2_CTRL = RAM + 0x048090;

  RAM_CTRL = RAM + 0x48100;

  InitPaletteMap(RAM+0x38000, 0x80, gfx_colours, 0x8000);
  init_16x16_zoom_64();

  set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x048500);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x0FFFFF, NULL, ROM+0x000000);         // 68000 ROM
   AddRWBW(0x200000, 0x20FFFF, NULL, RAM+0x000000);         // 68000 RAM
   AddReadBW(0x300000,0x300007,cave_irq_cause_r,NULL);

   //AddWriteByte(0x300000, 0x30007f, esp_800000_wb,NULL);
   //AddWriteWord(0x300000, 0x30007f, esp_800000_ww,NULL);
   AddWriteBW(0x300000, 0x30007F, NULL, RAM_CTRL+0);

   AddRWBW(0x400000, 0x40FFFF, NULL, RAM+0x010000);         // OBJECT RAM
   AddRWBW(0x500000, 0x507FFF, NULL, RAM+0x020000);         // BG0 RAM
   AddRWBW(0x600000, 0x607FFF, NULL, RAM+0x028000);         // BG1 RAM
   AddRWBW(0x700000, 0x707FFF, NULL, RAM+0x030000);         // BG2 RAM
   AddReadBW(0x800002, 0x800003, YMZ280B_status_0_r, NULL);      // ?
   AddWriteWord(0x800000, 0x800003, sound_esprade_w,NULL);
   AddWriteByte(0x800000, 0x800003, sound_esprade_w, NULL);      // ?
   AddRWBW(0x900000, 0x900007, NULL, RAM+0x048080);      // BG0 CTRL RAM
   AddRWBW(0xA00000, 0xA00007, NULL, RAM+0x048088);      // BG1 CTRL RAM

   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);         // Trap Idle 68000
   AddRWBW(0xB00000, 0xB00007, NULL, RAM+0x048090);      // BG2 CTRL RAM
   AddWriteWord(0xB00000, 0xB00007, NULL, RAM+0x048090);      // BG2 CTRL RAM
   AddRWBW(0xC00000, 0xC0FFFF, NULL, RAM+0x038000);         // COLOR RAM
   AddReadByte(0xD00010, 0xD00013, guwange_input_rb, NULL);         // INPUT
   AddReadWord(0xD00010, 0xD00013, guwange_input_rw, NULL);         // INPUT
   AddWriteWord(0xD00010, 0xD00011, guwange_eeprom_w, NULL);         // INPUT

   // Speed hack

   if (is_current_game("guwange")) {
       apply_hack(0x6d6de,4);
       pWriteWord(&ROM[0x6d6e4],0x6010);
   } else if (is_current_game("guwanges")) {
       apply_hack(0x6ec44,4);
       pWriteWord(&ROM[0x6ec4a],0x6010);
   }

   pWriteWord(&ROM[0x6d76],0x4e71); // disable rom check : nop
   pWriteWord(&ROM[0x6d80],0x6008); // bra

   setup_cave_game();
}

static void load_dfeveron(void)
{
   romset = 0;

   default_eeprom = cave_default_eeprom_type1;
   default_eeprom_size = sizeof(cave_default_eeprom_type1);

   setup_cave_sprites(&cave_gfx_object);

   gfx_colours = 16;

   RAMSize=0x80000;
   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM_BG0 = RAM + 0x020000;
   RAM_BG1 = RAM + 0x028000;
   RAM_BG2 = NULL;

   RAM_BG0_CTRL = RAM + 0x048080;
   RAM_BG1_CTRL = RAM + 0x048088;
   RAM_BG2_CTRL = NULL;

   RAM_CTRL = RAM + 0x48100;

/*
   WriteWord68k(&ROM[0x02D4A],0x4E71);
*/

   InitPaletteMap(RAM+0x38000, 0x80, gfx_colours, 0x8000);
   init_16x16_zoom_64();

   set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x048000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadBW(0x000000, 0x0FFFFF, NULL, ROM+0x000000);         // 68000 ROM
   AddRWBW(0x100000, 0x10FFFF, NULL, RAM+0x000000);         // 68000 RAM
   AddReadBW(0x300002,0x300003,YMZ280B_status_0_r,NULL);
   AddWriteBW(0x300000, 0x300003, sound_esprade_w,NULL);

   AddRWBW(0x400000, 0x40FFFF, NULL, RAM+0x010000);         // OBJECT RAM
   AddRWBW(0x500000, 0x507FFF, NULL, RAM+0x020000);         // BG0 RAM
   AddRWBW(0x600000, 0x607FFF, NULL, RAM+0x028000);         // BG1 RAM
   AddRWBW(0x708000, 0x708FFF, NULL, RAM+0x038000);         // COLOR RAM
   //AddReadBW(0x708000, 0x708FFF, NULL, RAM+0x038000);         // COLOR RAM
   //AddWriteByte(0x708000, 0x708FFF, feveron_pal_wb, NULL);         // COLOR RAM
   //AddWriteWord(0x708000, 0x708FFF, feveron_pal_ww, NULL);         // COLOR RAM

   AddRWBW(0x710000, 0x710FFF, NULL, RAM+0x038000);         // COLOR RAM [MIRROR]

   AddReadWord(0x800000, 0x800007, cave_irq_cause_r, NULL);      // ?
   //AddWriteByte(0x800000, 0x80007f, esp_800000_wb, NULL);      // ?
   //AddWriteWord(0x800000, 0x80007f, esp_800000_ww, NULL);      // ?
   AddWriteBW(0x800000, 0x80007F, NULL, RAM_CTRL+0);

   AddWriteWord(0x900000, 0x900007, NULL, RAM+0x048080);      // BG0 CTRL RAM

   AddWriteWord(0xA00000, 0xA00007, NULL, RAM+0x048088);      // BG1 CTRL RAM

   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);         // Trap Idle 68000

   AddReadWord(0xB00000, 0xB00003, esp_input_rw, NULL);         // INPUT
   AddReadByte(0xB00000, 0xB00003, esp_input_rb, NULL);         // INPUT

   AddWriteWord(0xC00000, 0xC00001, cave_eeprom_w, NULL);      // EEPROM

   if (is_current_game("dfeveron")) {
     // Speed hack
     apply_hack(0x772f2,4); // clr.b $aa0000
     pWriteWord(&ROM[0x772f8],0x6012);

     pWriteWord(&ROM[0x8dba],0x4e71); // disable rom check : nop
     pWriteWord(&ROM[0x8dc4],0x600a); // bra
   } else {
     // fever sos
     // Speed hack
     apply_hack(0x7766c,4); // clr.b $aa0000
     pWriteWord(&ROM[0x77672],0x6012);

     pWriteWord(&ROM[0x8ddc],0x4e71); // disable rom check : nop
     pWriteWord(&ROM[0x8de6],0x600a); // bra

     pWriteWord(&ROM[0x8f46],0x4e71); // disable eeprom test (nop)
     pWriteWord(&ROM[0x8f48],0x4e71); // if it does not find this value in the eeprom
     // then it just resets
  }
   setup_cave_game();
}

static void load_uopoko(void)
{
   romset = 0;

   default_eeprom = cave_default_eeprom_type3;
   default_eeprom_size = sizeof(cave_default_eeprom_type3);

   setup_cave_sprites(&cave_gfx_object);
   gfx_colours = 256;

   RAMSize=0x80000;
   if(!(RAM=AllocateMem(RAMSize))) return;

   RAM_BG0 = RAM + 0x020000;
   RAM_BG1 = NULL;
   RAM_BG2 = NULL;

   RAM_BG0_CTRL = RAM + 0x048080;
   RAM_BG1_CTRL = NULL;
   RAM_BG2_CTRL = NULL;

   RAM_CTRL = RAM + 0x48100;

/*
   WriteWord68k(&ROM[0x02D4A],0x4E71);
*/
   InitPaletteMap(RAM+0x38000, 0x80, gfx_colours, 0x8000);
   init_16x16_zoom_64();

   set_colour_mapper(&col_map_xggg_ggrr_rrrb_bbbb);

/*
 *  StarScream Stuff follows
 */

   ByteSwap(ROM,0x100000);
   ByteSwap(RAM,0x048000);

   AddMemFetch(0x000000, 0x0FFFFF, ROM+0x000000-0x000000);      // 68000 ROM

   AddReadByte(0x000000, 0x0FFFFF, NULL, ROM+0x000000);         // 68000 ROM
   AddReadByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);         // 68000 RAM
   AddReadBW(0x300002,0x300003,YMZ280B_status_0_r,NULL);
   AddWriteBW(0x300000, 0x300003, sound_esprade_w,NULL);

   AddReadByte(0x400000, 0x40FFFF, NULL, RAM+0x010000);         // OBJECT RAM
   AddReadByte(0x500000, 0x507FFF, NULL, RAM+0x020000);         // BG0 RAM
   AddReadWord(0x600000, 0x60007F, cave_irq_cause_r, NULL);      // ?
   AddReadByte(0x800000, 0x80FFFF, NULL, RAM+0x038000);         // COLOR RAM
   AddReadByte(0x900000, 0x900003, esp_input_rb, NULL);         // INPUT

   AddReadWord(0x000000, 0x0FFFFF, NULL, ROM+0x000000);         // 68000 ROM
   AddReadWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);         // 68000 RAM
   AddReadWord(0x400000, 0x40FFFF, NULL, RAM+0x010000);         // OBJECT RAM
   AddReadWord(0x500000, 0x507FFF, NULL, RAM+0x020000);         // BG0 RAM
   AddReadWord(0x800000, 0x80FFFF, NULL, RAM+0x038000);         // COLOR RAM
   AddReadWord(0x900000, 0x900003, esp_input_rw, NULL);         // INPUT

   AddWriteByte(0x100000, 0x10FFFF, NULL, RAM+0x000000);      // 68000 RAM
   AddWriteByte(0x400000, 0x40FFFF, NULL, RAM+0x010000);      // OBJECT RAM
   AddWriteByte(0x500000, 0x507FFF, NULL, RAM+0x020000);      // BG0 RAM
   //AddWriteByte(0x600000, 0x60007F, esp_800000_wb, NULL);      // ?
   AddWriteByte(0x800000, 0x80FFFF, NULL, RAM+0x038000);      // COLOR RAM
   AddWriteByte(0xAA0000, 0xAA0000, mystop68k, NULL);         // Trap Idle 68000
   AddWriteWord(0x100000, 0x10FFFF, NULL, RAM+0x000000);      // 68000 RAM
   AddWriteWord(0x400000, 0x40FFFF, NULL, RAM+0x010000);      // OBJECT RAM
   AddWriteWord(0x500000, 0x507FFF, NULL, RAM+0x020000);      // BG0 RAM
   //AddWriteWord(0x600000, 0x60007F, esp_800000_ww, NULL);      // ?
   AddWriteBW(0x600000, 0x60007F, NULL, RAM_CTRL+0);

   AddWriteWord(0x800000, 0x80FFFF, NULL, RAM+0x038000);      // COLOR RAM
   AddWriteWord(0xA00000, 0xA00001, cave_eeprom_w, NULL);      // EEPROM
   AddWriteWord(0x700000, 0x700007, NULL, RAM+0x048080);      // BG0 CTRL RAM

   // Speed hack

   apply_hack(0xc36,1);

   pWriteWord(&ROM[0x6bc],0x600a); // disable rom check : bra

   setup_cave_game();
}

static void execute_mazinger(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(FRAME_68K,60));   // M68000 28MHz (60fps)

   execute_z80_audio_frame();

   unknown_irq  = 1;
   update_irq_state();

   if (s68000context.pc == 0x1d92)
     reset_game_hardware();
}

static UINT8 *RAM_OBJ;

static void execute_esprade(void)
{
   stopped_68k = 0;
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(32,60));
   /* This thing is extremely sensible here.
    * The idea :
    * at the end of each frame, before the vbl, the main program resets a
    * counter. Then inside the vbl irq (irq 1), this counter is checked 1st.
    * If it is not 0 then it's assumed we didn't have enough cycles to
    * execute the frame, and the sprite buffer is not flipped (RAM_CTRL[8] & 1)
    * and at the end of the irq, this flag is incremented normaly.
    *
    * Failing to set the correct minimum number of cycles before the irq
    * produces display bugs. Try 15 Mhz here in sailor moon, and even the
    * copyright screen doesn't display correctly. Mame chose to find precisely
    * the number of cycles needed to avoid the display bugs, I prefer to use
    * a speed hack, allow much more cycles than needed (32 here instead of 16)
    * then triger the irq, this way you are sure to never have any display bug.
    * Then after this you still have a small subtelity :
    * the vbl sets a bit (emulated by agallet_vblank_irq = 1) for only 1/8
    * of the normal frame, and then this bit is cleared. Some games test this
    * bit and expect it to be set sometimes, so we must allow a minimum number
    * of cycles to be executed with this bit set. I allow the whole irq to be
    * executed by explicitely seting the pc on the speed hack and then
    * executing a lot of cycles (it will end on the speed hack).
    * Seems to work everywhere. */

   if (MZ80Engine)
     execute_z80_audio_frame();

   vblank_irq = 1;
   agallet_vblank_irq = 1;
   if (stopped_68k) {
     // return to the speed hack
     s68000context.pc = get_speed_hack_adr(0)-ROM;
     stopped_68k = 0;
   }
   update_irq_state();
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(1.8,60));
   if (!stopped_68k) {
     // bonus frame, not needed in normal frames, I guess I could do without
     // completely. Gives a little boost on the hardware test phase.
     cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(16,60));
   }
   agallet_vblank_irq = 0;
}

static void blit_cave_layer(int num) {
  UINT8 *RAM_BG,*pbline,*pline;
  BITMAP *plbitmap = layer_pbitmap[num];
  BITMAP *lbitmap = layer_bitmap[num];
  int x,y;

  switch(num) {
  case 0:
    RAM_BG = RAM_BG0;
    break;
  case 1:
    RAM_BG = RAM_BG1;
    break;
  case 2:
    RAM_BG = RAM_BG2;
    break;
  }
  RAM_BG += 0x1002; // Start of row fetch data

  switch ((current_game->video->flags ^ display_cfg.user_rotate) & 1) {
  case 0:
    // no screen rotation

    switch(display_cfg.bpp) {
    case 8:
      for (y=0; y<240; y++) {
	UINT8 *line,*layer;
	UINT32 py = ReadWord(RAM_BG+y*4);
	if (py >= 240) py %= 240;
	py += 32;
	pbline = plbitmap->line[py]+32;
	pline = pbitmap->line[y+32]+32;
	line = GameBitmap->line[y+32]+32;
	layer = lbitmap->line[py]+32;
	for (x=0; x<320; x++) {
	  if (pbline[x] && pline[x] < pbline[x]) {
	    line[x] = layer[x];
	  }
	}
      }
      break;
    case 15:
    case 16:
      for (y=0; y<240; y++) {
	UINT16 *line,*layer;
	UINT32 py = ReadWord(RAM_BG+y*4);
	if (py >= 240) py %= 240;
	py += 32;
	pbline = plbitmap->line[py]+32;
	pline = pbitmap->line[y+32]+32;
	line = ((UINT16 *)GameBitmap->line[y+32])+32;
	layer = ((UINT16 *)lbitmap->line[py])+32;

	for (x=0; x<320; x++) {
	  if (pbline[x] && pline[x] < pbline[x])
	    line[x] = layer[x];
	}
      }
      break;
    case 32:
      for (y=0; y<240; y++) {
	UINT32 *line,*layer;
	UINT32 py = ReadWord(RAM_BG+y*4);
	if (py >= 240) py %= 240;
	py += 32;
	pbline = plbitmap->line[py]+32;
	pline = pbitmap->line[y+32]+32;
	line = ((UINT32 *)GameBitmap->line[y+32])+32;
	layer = ((UINT32 *)lbitmap->line[py])+32;

	for (x=0; x<320; x++) {
	  if (pbline[x] && pline[x] < pbline[x])
	    line[x] = layer[x];
	}
      }
      break;
    }
    break;
  default:
    // Vertical screen
    switch(display_cfg.bpp) {
    case 8:
      {
	int w = GameBitmap->w;
	for (y=0; y<240; y++) {
	  UINT16 py = ReadWord(RAM_BG+y*4) & 255;
	  UINT8 *game_bitmap, *l_bitmap;
	  UINT8 *p_bitmap,*p_lbitmap;
	  int dy;
	  if (py >= 240) py %= 240;
	  dy = y+32;
	  py += 32;
	  game_bitmap = ((UINT8 *)GameBitmap->line[32]) + dy;
	  l_bitmap = ((UINT8 *)lbitmap->line[32]) + py;
	  p_lbitmap = plbitmap->line[32]+py;
	  p_bitmap = pbitmap->line[32]+dy;
	  for (x=0+32; x<320+32; x++) {
	    if (*p_lbitmap && *p_bitmap < *p_lbitmap) {
	      *game_bitmap = *l_bitmap;
	    }
	    game_bitmap += w;
	    l_bitmap += w;
	    p_lbitmap += w;
	    p_bitmap += w;
	  }
	}
      }
      break;
    case 15:
    case 16:
      {
	int w = GameBitmap->w;
	for (y=0; y<240; y++) {
	  UINT16 py = ReadWord(RAM_BG+y*4) & 255;
	  UINT16 *game_bitmap, *l_bitmap;
	  UINT8 *p_bitmap,*p_lbitmap;
	  int dy;
	  if (py >= 240) py %= 240;
	  dy = y+32;
	  py += 32;
	  game_bitmap = ((UINT16 *)GameBitmap->line[32]) + dy;
	  l_bitmap = ((UINT16 *)lbitmap->line[32]) + py;
	  p_lbitmap = plbitmap->line[32]+py;
	  p_bitmap = pbitmap->line[32]+dy;
	  for (x=0+32; x<320+32; x++) {
	    if (*p_lbitmap && *p_bitmap < *p_lbitmap) {
	      *game_bitmap = *l_bitmap;
	    }
	    game_bitmap += w;
	    l_bitmap += w;
	    p_lbitmap += w;
	    p_bitmap += w;
	  }
	}
      }
      break;
    case 32:
      {
	int w = GameBitmap->w;
	for (y=0; y<240; y++) {
	  UINT16 py = ReadWord(RAM_BG+y*4) & 255;
	  UINT32 *game_bitmap, *l_bitmap;
	  UINT8 *p_bitmap,*p_lbitmap;
	  int dy;
	  if (py >= 240) py %= 240;
	  dy = y+32;
	  py += 32;
	  game_bitmap = ((UINT32 *)GameBitmap->line[32]) + dy;
	  l_bitmap = ((UINT32 *)lbitmap->line[32]) + py;
	  p_lbitmap = plbitmap->line[32]+py;
	  p_bitmap = pbitmap->line[32]+dy;
	  for (x=0+32; x<320+32; x++) {
	    if (*p_lbitmap && *p_bitmap < *p_lbitmap) {
	      *game_bitmap = *l_bitmap;
	    }
	    game_bitmap += w;
	    l_bitmap += w;
	    p_lbitmap += w;
	    p_bitmap += w;
	  }
	}
      }
      break;
    }
  }
}

extern UINT8 *RAM_PAL;

static void reset_spr16() {
  switch (display_cfg.bpp) {
  case 8:
    init_spr16x16asm_8();
    break;
  case 15:
  case 16:
    init_spr16x16asm_16();
    break;
  case 32:
    init_spr16x16asm_32();
  }
}

static BITMAP *old_bitmap,*old_pbitmap;

static void create_cave_layer(int i, UINT16 *scrolly) {
  old_bitmap = GameBitmap;
  old_pbitmap = pbitmap;
  if (!layer_bitmap[i]) {
    layer_bitmap[i] = create_bitmap_ex(bitmap_color_depth(GameBitmap),
				       GameBitmap->w,GameBitmap->h);
  }
  if (!layer_pbitmap[i]) {
    layer_pbitmap[i] = create_bitmap_ex(8,GameBitmap->w,GameBitmap->h);
  }

  if (!layer_bitmap[i] || !layer_pbitmap[i]) {
    print_ingame(10,gettext("Not enough memory for layer bitmap %d"),i);
    *scrolly &= ~0x4000;
    return;
  }
  clear_bitmap(layer_pbitmap[i]);

  GameBitmap = layer_bitmap[i];
  reset_spr16();
  init_spr16x16asm_mask(layer_pbitmap[i]);
  pbitmap = layer_pbitmap[i];
}

static INT16 offsets_bg0[256],offsets_bg1[256],offsets_bg2[256];

static void draw_cave_layer(int num)
{
  int x,y,dx;
  UINT32 ta;
  int zz;
  int layer_pris = 0;
  int x16,y16,zzz,zzzz;
  UINT8 *map;
  UINT16 scrollx, scrolly,tile_dim,row_scroll,flipx,flipy;

  UINT8 *RAM_BG;
  UINT8 *SCR_BG;
  UINT8 *MSK_BG;
  UINT8 *GFX_BG;
  INT16 *offsets;
  UINT16 layer_status;

  if(! check_layer_enabled(layer_id_data[num])) {
    return;
  }

  switch(num) {
  case 0:
    RAM_BG = RAM_BG0;
    SCR_BG = RAM_BG0_CTRL;
    MSK_BG = GFX_BG0_SOLID;
    GFX_BG = GFX_BG0;
    offsets = offsets_bg0;
    break;
  case 1:
    RAM_BG = RAM_BG1;
    SCR_BG = RAM_BG1_CTRL;
    MSK_BG = GFX_BG1_SOLID;
    GFX_BG = GFX_BG1;
    offsets = offsets_bg1;
    break;
  case 2:
    RAM_BG = RAM_BG2;
    SCR_BG = RAM_BG2_CTRL;
    MSK_BG = GFX_BG2_SOLID;
    GFX_BG = GFX_BG2;
    offsets = offsets_bg2;
    break;
  default:
    return;
    break;
  }

  if (!SCR_BG) return;
  layer_status = ReadWord(SCR_BG+4);
  if (((layer_status & 0x10))){ // Layer active ?
#ifdef RAINE_DEBUG
    print_ingame(1,gettext("layer %d disabled"),num);
#endif
    return;
  }


/***************************************************************************
 From the mame driver. They found this 16x16/8x8 toggle bit...
								Screen Drawing


				Layers Control Registers (cave_vctrl_0..2)


		Offset:		Bits:					Value:

		0.w			f--- ---- ---- ----		0 = Layer Flip X
					-e-- ---- ---- ----		Activate Row Scroll
					--d- ---- ---- ----
					---c ba9- ---- ----
					---- ---8 7654 3210		Scroll X

		2.w			f--- ---- ---- ----		0 = Layer Flip Y
					-e-- ---- ---- ----		Activate "Column" Scroll
					--d- ---- ---- ----		0 = 8x8 tiles, 1 = 16x16 tiles
					---c ba9- ---- ----
					---- ---8 7654 3210		Scroll Y

		4.w			fedc ba98 765- ----
					---- ---- ---4 ----		Layer Disable
					---- ---- ---- 32--
					---- ---- ---- --10		Layer Priority (decides the order
											of the layers for tiles with the
											same tile priority)


		Row / "Column" Scroll data is fetched from tile RAM + $1000.

		"Column" Scroll:	a tilemap line is specified for each scan line.
		Row Scroll:			a different scroll value is specified for each scan line.


					Sprites Registers (cave_videoregs)


	Offset:		Bits:					Value:

		0.w		f--- ---- ---- ----		Sprites Flip X
				-edc ba98 7654 3210		Sprites Offset X

		2.w		f--- ---- ---- ----		Sprites Flip Y
				-edc ba98 7654 3210		Sprites Offset Y

		..

		8.w		fedc ba98 7654 321-
				---- ---- ---- ---0		Sprite RAM Bank

		There are more!

***************************************************************************/
#if 0
  // This code is more or less what mame uses
  // but it does not seem to work well with flipx, flipy...
  // Both ways are working ?!!!
  scrollx = ReadWord(SCR_BG+0) - ReadWord(RAM_CTRL + 0);
  scrolly = ReadWord(SCR_BG+2) - ReadWord(RAM_CTRL + 2);
  flipx = ~scrollx & 0x8000;
  flipy = ~scrolly & 0x8000;

  tile_dim = scrolly & 0x2000;
  row_scroll = scrollx & 0x4000;

  dx = 0x13 - (tile_dim ? num+1 : 9+num);
  scrollx += (flipx ? 0x2 + dx : - dx);
  // scrollx += 2 + dx; // problem in hotdogst : it changes flipx in the middle of the scrolling !
  // scrolly += (flipy ? - 0x10 : 0x12) + 35;
  scrolly += -0x12 + 34;
  // scrollx += (flipx ? dx :  - dx);
#else
  // this is our old code.
  // I prefer this version because hotdogstorm title screen looks much better with it !

  scrollx = ReadWord(SCR_BG+0);
  scrolly = ReadWord(SCR_BG+2);
  flipx = ~scrollx & 0x8000;
  flipy = ~scrolly & 0x8000;

  tile_dim = scrolly & 0x2000;
  row_scroll = scrollx & 0x4000;

  dx = xcorrection - (tile_dim ? num : 8+num);
  scrollx += (flipx ? 0x5 + dx : 0x7c - dx);
  // scrollx += (flipx ? dx :  - dx);

  if (flipy) {
    scrolly = 0x100 + scrolly;
  } else
    scrolly = 0x11 + scrolly;
#endif
  // fprintf(stderr,"layer %d flipx %d flipy %d tile_dim %d scx %d scy %d\n",num,flipx,flipy,tile_dim,scrollx,scrolly);

  if (scrolly & 0x4000) {
    // row fetch effect
    if (romset == 8) {
      // Air Gallet wastes cpu time by enabling the row select bit without actually using
      // it (all the rows point to the usual rows).
#ifdef RAINE_DEBUG
      print_ingame(1,gettext("disabling row select (agallet)"));
#endif
      scrolly &= ~0x4000;
    } else {
      create_cave_layer(num,&scrolly);
    // UINT8 *dy = RAM_BG+0x1002+0*4;
#ifdef RAINE_DEBUG
      print_ingame(1,gettext("row select layer %d size %d"),num,layer_size[num]);
#endif
    }
/*     if (row_scroll) */
  }

  if(layer_size[num]<16) {
#ifdef RAINE_DEBUG
    if (row_scroll)
      print_ingame(1,gettext("row scroll on 8x8 layer unemulated"));
#endif
    if (romset & 2) { // Share colors between sprites & layers
      MAKE_SCROLL_512x512_4_8(scrollx, scrolly);

      START_SCROLL_512x512_4_8(32,32,gamex,240);

      ta = ReadWord(&RAM_BG[zz+2]);
      if(MSK_BG[ta]) {
	UINT8 pri,bank;
	bank = RAM_BG[zz+1];
	pri = (bank >> 6);

	if (num == 1)
	  // WARNING : this code converts the 64 colors banks from mazinger.
	  // Any other game coming here would probably have problems...
	  bank = ((bank * 4 ) & 0x3f)+64;
	else
	  bank &= 0x3f;

	MAP_PALETTE_MAPPED_NEW(
			       bank,
			       gfx_colours,
			       map
			       );

	// Since we are now using the priority bitmap, it would be rather hard
	// to use at the same time the tile cache. Just forget about it !!!
	if(MSK_BG[ta]==1)                     // Some pixels; trans
	  pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<6], x, y, map,pri);
	else {                                        // all pixels; solid
	  pdraw8x8_Mask_Mapped_Rot(&GFX_BG[ta<<6], x, y, map,pri);
	}
      }
      END_SCROLL_512x512_4_8();
    } else { // Separate colors for layers (8x8)
      if (romset & 8) { // Very special case for sailor moon...
	if (tile_dim) { // 16x16 layer ! (this only happens for air gallet normally)
	  /* In fact every 16x16 layer in cave games is made with 8x8 sprites. */
	  /* For speed reasons these layers are converted to real 16x16 layers */
	  /* We could have 2 copies of the layers in ram (8x8 and 16x16), but  */
	  /* it would eat really too much memory. That's why we have size=9    */
	  UINT8 bank,pri;
	  layer_size[2] = 9; // Special handling : 16x16 drawn with 8x8 sprites
	  MAKE_SCROLL_512x512_4_16(scrollx, scrolly);

	  START_SCROLL_512x512_4_16(32,32,gamex,240);

	  ta = ReadWord(&RAM_BG[zz+2]) | (RAM_BG[zz]<<16);
	  if(ta < sprites_bg2/4) {
	    // The bank is converted to a bank for 64 colors : x4
	    bank = RAM_BG[zz+1];
	    pri = (bank >> 6);

	    bank = (bank*4) & 0x3f;
	    MAP_PALETTE_MULTI_MAPPED_NEW(
					 bank | 0xc0,
					 64,
					 map
					 );

	    if(MSK_BG[ta*4]) {
	      if(MSK_BG[ta*4]==1)                      // Some pixels; trans
		pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	      else                                         // all pixels; solid
		pdraw8x8_Mask_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	    }

	    if(MSK_BG[ta*4+1]) {
	      if(MSK_BG[ta*4+1]==1)                      // Some pixels; trans
		pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[(ta<<8)+0x40], x+8, y, map,pri);
	      else                                         // all pixels; solid
		pdraw8x8_Mask_Mapped_Rot(&GFX_BG[(ta<<8)+0x40], x+8, y, map,pri);
	    }

	    if(MSK_BG[ta*4+2]) {
	      if(MSK_BG[ta*4+2]==1)                      // Some pixels; trans
		pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[(ta<<8)+0x80], x, y+8, map,pri);
	      else                                         // all pixels; solid
		pdraw8x8_Mask_Mapped_Rot(&GFX_BG[(ta<<8)+0x80], x, y+8, map,pri);
	    }

	    if(MSK_BG[ta*4+3]) {
	      if(MSK_BG[ta*4+3]==1)                      // Some pixels; trans
		pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[(ta<<8)+0xc0], x+8, y+8, map,pri);
	      else                                         // all pixels; solid
		pdraw8x8_Mask_Mapped_Rot(&GFX_BG[(ta<<8)+0xc0], x+8, y+8, map,pri);
	    }
	  }
	  END_SCROLL_512x512_4_16();
	} else { // 8x8 layer... (with the sailor moon color mapping)
	  UINT8 bank,pri;
	  RAM_BG += 0x4000;
	  layer_size[2] = 8;
	  MAKE_SCROLL_512x512_4_8(scrollx, scrolly);

	  START_SCROLL_512x512_4_8(32,32,gamex,240);

	  ta = (ReadWord(&RAM_BG[zz+2]) | (RAM_BG[zz])<<16);
	  if ((ta < 0x10000) && (sailormn_tile_bank))	ta += 0x40000;
	  if(ta < sprites_bg2 && MSK_BG[ta]) {
	    bank = RAM_BG[zz+1];
	    pri = (bank >> 6);
	    bank = ((bank*4) & 0x3f) + 0xc0;
	    // The bank is converted to a bank for 64 colors : x4
	    MAP_PALETTE_MULTI_MAPPED_NEW(
					 // ((RAM_BG[zz+1]&0x3f)<<2) | 0xc0,
					 bank,
					 64,
					 map
					 );

	    if(MSK_BG[ta]==1)                     // Some pixels; trans
	      pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<6], x, y, map,pri);
	    else {                                        // all pixels; solid
	      pdraw8x8_Mask_Mapped_Rot(&GFX_BG[ta<<6], x, y, map,pri);
	    }
	  }
	  END_SCROLL_512x512_4_8();
	}
      } else {
	// 8x8 layer, normal color mapping
	UINT8 base = layer_base[num];
	MAKE_SCROLL_512x512_4_8(scrollx, scrolly);

	START_SCROLL_512x512_4_8(32,32,gamex,240);

	ta = ReadWord(&RAM_BG[zz+2]);

	if(MSK_BG[ta]) {
	  UINT8 bank = RAM_BG[zz+1],pri;
	  pri = (bank >> 6);
	  MAP_PALETTE_MAPPED_NEW(
				 (bank & 0x3F) | base,
				 gfx_colours,
				 map
				 );

	  if(MSK_BG[ta]==1)                     // Some pixels; trans
	    pdraw8x8_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<6], x, y, map,pri);
	  else {                                        // all pixels; solid
	    pdraw8x8_Mask_Mapped_Rot(&GFX_BG[ta<<6], x, y, map,pri);
	  }
	}
	END_SCROLL_512x512_4_8();
      }
    }
  } else { // "normal" 16x16 layer

    MAKE_SCROLL_512x512_4_16(scrollx, scrolly);
    if (row_scroll) {
      UINT8 *dy;
      INT16 *dy2;
      UINT8 base = layer_base[num];
      //START_SCROLL_512x512_4_16(32,32,gamex,240);
      // I am obliged to modify all the scroll primitives... (for speed)
      // zzzz+=16;
      zz=zzzz;
      // This code is very dirty. It was a quick hack to see if it is
      // possible. Now that I know it is, it would be nice to rewrite it
      // a better way : it should scan the whole 512x512 window normally...
#define WIDTH 512
#define HEIGHT 512
#define N 4
#ifdef RAINE_DEBUG
      print_ingame(1,gettext("line scroll %d"),num);
#endif
      for(y=(32-y16);(UINT32)y<(240+32);y+=16){
	INT16 min = 999, max = -999;
	int n,startn;
	if (y<16) {
	  zz = zzzz = (zzzz+(WIDTH*N/16))&(WIDTH*HEIGHT*N/(16*16)-1);
	  continue;
	}

	dy = RAM_BG+0x1000+(y-32)*4;
	if (y < 32) {
	    dy2 = &offsets[0];
	    startn = 32-y;
	} else {
	    dy2 = &offsets[y-32];
	    startn =  0;
	}

	for (n=startn; n<16; n++) {
	  INT16 ta = -ReadWord(dy+n*4);
	  dy2[n]=ta;
	  if (min > ta)
	    min = ta;
	  if (max < ta)
	    max = ta;
	}
	if (min) {
	  if (min & 15) /* min is not on the limit of a sprite */
	    min = (min > 0) ? min/16 : min/16 - 1;
	  else
	    min /= 16;
	}
	if (max) {
	  if (max & 15)
	    max = max/16 +1;
	  else
	    max /= 16;
	}

	if (max || min) { /* some line scroll for this line */
	  zz=(zz&(WIDTH*HEIGHT*N/(16*16)-WIDTH*N/16))|((zz-max*N)&(WIDTH*N/16-1));
	  for(x=(32-x16-max*16);x<(gamex+32-min*16);x+=16){
	    ta = ReadWord(&RAM_BG[zz+2]);

	    if(MSK_BG[ta]) {
	      UINT8 bank = RAM_BG[zz+1];
	      UINT8 pri;
	      if (romset & 2) { // sharing palette between sprites and layers
		MAP_PALETTE_MAPPED_NEW(
				       (bank & 0x7F),
				       gfx_colours,
				       map
				       );
	      } else {
		MAP_PALETTE_MAPPED_NEW(
				       (bank & 0x3F) | base,
				       gfx_colours,
				       map
				       );
	      }

	      pri = (bank >> 6);
	      if (scrolly & 0x4000) { // row fetch -> direct rendering
		layer_pris = 1; // |= (1 <<  pri);
		pri++; // to make the difference between not drawn and priority 0
	      }

	      if(MSK_BG[ta]==1) {                     // Some pixels; trans
		pldraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,dy2,pri);
	      } else {                                        // all pixels; solid
		pldraw16x16_Mask_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,dy2,pri);
	      }
	    }
	    zz=(zz&(WIDTH*HEIGHT*N/(16*16)-WIDTH*N/16))|((zz+N)&(WIDTH*N/16-1));
	  }
	} else { // no line scroll for this line
	  for(x=(32-x16);x<(gamex+32);x+=16){
	    ta = ReadWord(&RAM_BG[zz+2]);

	    if(MSK_BG[ta]) {
	      UINT8 bank = RAM_BG[zz+1];
	      UINT8 pri;

	      if (romset & 2) { // sharing palette between sprites and layers
		MAP_PALETTE_MAPPED_NEW(
				       (bank & 0x7F),
				       gfx_colours,
				       map
				       );
	      } else {
		MAP_PALETTE_MAPPED_NEW(
				     (bank & 0x3F) | base,
				     gfx_colours,
				     map
				     );
	      }
	      pri = (bank >> 6);
	      if (scrolly & 0x4000) { // row fetch -> direct rendering
		layer_pris = 1; // (1 <<  pri);
		pri++; // to make the difference between not drawn and priority 0
	      }

	      if(MSK_BG[ta] == 1) {                     // Some pixels; trans
		pdraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	      } else {                                        // all pixels; solid
		pdraw16x16_Mask_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	      }
	    }
	    zz=(zz&(WIDTH*HEIGHT*N/(16*16)-WIDTH*N/16))|((zz+N)&(WIDTH*N/16-1));
	  }
	}
	zz = zzzz = (zzzz+(WIDTH*N/16))&(WIDTH*HEIGHT*N/(16*16)-1);
      } // for y

      if (scrolly & 0x4000) { // row fetch -> direct rendering
	GameBitmap = old_bitmap;
	pbitmap = old_pbitmap;
	init_spr16x16asm_mask(pbitmap);
	reset_spr16();
	if (layer_pris)
	  blit_cave_layer(num);
      }
      return;
    } // raster effect

#ifdef RAINE_DEBUG
    print_ingame(1,gettext("no line scroll %d"),num);
#endif

    if (romset & 2) {
      // hotdog storm shares its palette between sprites & layers...
      START_SCROLL_512x512_4_16(32,32,gamex,240);

      ta = ReadWord(&RAM_BG[zz+2])&0x7FFF;
      if(MSK_BG[ta]) {
	UINT8 bank = RAM_BG[zz+1];
	UINT8 pri;
	MAP_PALETTE_MAPPED_NEW(
			       bank & 0x7f, // | 0x40) & 0x7F,
			       gfx_colours,
			       map
			       );
	pri = (bank >> 6);
	if (scrolly & 0x4000) { // row fetch -> direct rendering
	  layer_pris = 1; // (1 <<  pri);
	  pri++; // to make the difference between not drawn and priority 0
	}
	if(MSK_BG[ta]==1) {                     // Some pixels; trans
	  pdraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	} else {                                        // all pixels; solid
	  pdraw16x16_Mask_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	}
      }

      END_SCROLL_512x512_4_16();
    } else {
      UINT8 base = layer_base[num];
      START_SCROLL_512x512_4_16(32,32,gamex,240);

      ta = ReadWord(&RAM_BG[zz+2])&0x7FFF;
      if(MSK_BG[ta]) {
	UINT8 bank = RAM_BG[zz+1];
	UINT8 pri;
	MAP_PALETTE_MAPPED_NEW(
	        (bank & 0x3f) | base,
		gfx_colours,
		map
		);
	pri = (bank >> 6);
	if (scrolly & 0x4000) { // row fetch -> direct rendering
	  layer_pris = 1; // (1 <<  pri);
	  pri++; // to make the difference between not drawn and priority 0
	}
	if(MSK_BG[ta]==1) {                     // Some pixels; trans
	  pdraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	} else {                                        // all pixels; solid
	  pdraw16x16_Mask_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
	}
      }

      END_SCROLL_512x512_4_16();
    }
  }
  if (scrolly & 0x4000) { // row fetch -> direct rendering
    GameBitmap = old_bitmap;
    pbitmap = old_pbitmap;
    init_spr16x16asm_mask(pbitmap);
    reset_spr16();
    if (layer_pris)
      blit_cave_layer(num);
  }
}

static UINT8 flip_map[4] =
{
   0, 2, 1, 3
};

static void draw_cave_68k(void)
{
   int x,y,ta,size,code,priority,zoomx,zoomy;
   int ww,hh,flip,attr;
   UINT8 *map;

   if (!GFX_BG0) {
     setup_cave_tiles();
   }

   ClearPaletteMap();

   // Sadly we are obliged to explicitly clear the screen because
   // with priorities mixed we can't know what is drawn first in one place
   // and wether there is something at all (it must be black if nothing)
   clear_game_screen(0);
   clear_bitmap(pbitmap);

   if (RefreshBuffers) {
     int i;
     for (i=0; i<3; i++) {
       if (layer_bitmap[i]) {
	 destroy_bitmap(layer_bitmap[i]);
	 layer_bitmap[i] = NULL;
       }
     }
   }
   if(! (ReadWord(RAM_CTRL+8) & 1)) {
     RAM_OBJ = RAM + 0x10000;
   } else {
     RAM_OBJ = RAM + 0x14000;
   }


   /*

   OBJECT

   */
   if(check_layer_enabled(layer_id_data[3])) { // sprites enabled
     int xx,w;
     for(ta=0; ta < 0x4000; ta+=16){
       if (romset & 1) {
	 attr = ReadWord(&RAM_OBJ[0+ta]);
	 size = ReadWord(&RAM_OBJ[8+ta]);
	 zoomx=16*16;
	 zoomy=16*16;
       } else {
	 attr = ReadWord(&RAM_OBJ[4+ta]);
	 zoomx= ReadWord(&RAM_OBJ[8+ta]);
	 zoomy= ReadWord(&RAM_OBJ[10+ta]);
	 size = ReadWord(&RAM_OBJ[12+ta]);
	 if (!zoomx || !zoomy) continue;
	 if (zoomx>63*16) {
	   zoomx=63*16;
	 }
	 if (zoomy>63*16)
	   zoomy=63*16;
       }

       priority = ((attr & 0x0030) >> 4);// | 3;

       ww = (size >> 8) & 0x1F;
       hh = (size >> 0) & 0x1F;

       if((ww) && (hh)){
	 if (romset & 1) { // donpachi / ddonpach
	   code = ReadWord(&RAM_OBJ[2+ta]);
	   x = ReadWord(&RAM_OBJ[4+ta])<<6;
	   y = ReadWord(&RAM_OBJ[6+ta])<<6;
	 } else {
	   code = ReadWord(&RAM_OBJ[6+ta]);
	   x = ReadWord(&RAM_OBJ[0+ta]);
	   y = ReadWord(&RAM_OBJ[2+ta]);
	 }

	 if (romset & 4) { // Hotdogst
	   x &= 0x3ff;
	   y &= 0x3ff;
	 } else {
	   x = ((x >> 6));
	   y = ((y >> 6));
	 }
	 if (x > 0x1FF)	{
	   x -= 0x400;
	 }
	 if (y > 0x1FF)	y -= 0x400;
	 int total_width = zoomx*ww/16;
	 int total_height = zoomy*hh/16;
	 // I am not sure if centering is 100% correct, it looks ok though
	 // This centering is not for the whole block (total_width), but only
	 // about centering the 1st sprite around its starting position related
	 // to the normal 16 zoom ! So the difference is small, and you can
	 // rarely see it...
	 x -= (zoomx/16-16)/2;
	 y -= (zoomy/16-16)/2;

	 code |= (attr & 3) << 16;
	 if (code > sprite_size) code %= sprite_size;


	 flip = flip_map[(attr >>2) & 0x03];

	 MAP_PALETTE_MAPPED_NEW(
				(attr>>8) & 0x3F,
				gfx_colours,
				map
				);
	 x += 32;
	 y += 32;

	 // QueueTileZoom(code, x+32, y+32, map, flip, priority,ww,hh, zoomx, zoomy);

	 int dx , dy = 0;
	switch(flip){
	case 0:
	  do{
	    if(GFX_OBJ_SIZE[code] != ww) {
	      make_tile_new(code, ww,GFX_OBJ_A,GFX_OBJ_B,GFX_OBJ_SOLID,GFX_OBJ_SIZE);
	    }
	    xx = x;
	    w = ww;
	    // the idea is to really draw total_height pixels instead of the
	    // approximation we used previously (zoomy/16 for each sprite).
	    // It creates much smoother animations !!!
	    int zy = (total_height-dy)/(hh); dy += zy;
	    dx = 0;
	    /* Notice : with a zoom max = 64, I should normaly have borders of 64 pixels here.
	     * I think at the begining it was 64, a very long time ago, and it was set to 32
	     * to get a slightly faster clear_game_bitmap (!)
	     * Anyway with a border of only 32, if a sprite with a zoom of 64 was slowly scrolling in
	     * the screen, the 32 1st pixel would appear in 1 time.
	     * But actually it never happens. Cave games really use very little the zoom effect.
	     * Guwange is the one which probably uses it the most, and it should probably be changed
	     * to draw something similar to mame (zoom by enlarging the space, but not doubling the
	     * pixels). Anyway in 0.51.0, this border of 32 suddenly made a buffer overflow in the
	     * intro of guwange which uses a zoom of 64 for its sprites.
	     * So now instead of 32-zy, I use 0 as the 1st allowed value.
	     * A better fix would be to put borders to 64, but it would be messy considering the
	     * number of changes it would imply + it's useless since sprites that big never scroll
	     * into the screen except in this weird title screen of guwange.
	     * The weird thing is that this buffer overflow has been here since this part of the code was
	     * redone to have smoother animations, and it was a very very very long time ago, but it never
	     * crashed anything until version 0.51.0 !!! */
	    if ((y >= 0) && (y < 240+32-zy+16) && y>= 0) {
	      do{
		int zx = (total_width-dx)/w; dx += zx;
		if(GFX_OBJ_SOLID[code]){
		  if((xx >= 0) && (xx < limitx-zx)){

		    if(GFX_OBJ_SOLID[code]==1)      // Some pixels; trans
		      pdraw16x16_64_Trans_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 0, priority);
		    else                         // all pixels; solid
		      pdraw16x16_64_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 0, priority);
		  }
		}
		xx = (xx + zx) & 0x3ff;
		code = (code + 1);
		if (code > sprite_size) {
		  code %= sprite_size;
		}

	      }while(--w);
	    } else {
	      code = (code + ww);
	      if (code > sprite_size) {
		code %= sprite_size;
	      }
	    }

	    y = (y + zy) & 0x3FF;

	  }while(--hh);
	  break;
	case 1:
	  x = (x + ((ww - 1) * 16)) & 0x3FF;
	  do{

	    if(GFX_OBJ_SIZE[code] != ww) {
	      make_tile_new(code, ww,GFX_OBJ_A,GFX_OBJ_B,GFX_OBJ_SOLID,GFX_OBJ_SIZE);
	    }
	    xx = x;
	    w = ww;

	    int zy = (total_height-dy)/(hh); dy += zy;
	    dx = 0;
	    if ((y >= 0) && (y < 240+32-zy+16) && y >= 0) {
	      do{
		int zx = (total_width-dx)/w; dx += zx;
		if(GFX_OBJ_SOLID[code]){
		  if((xx >= 0) && (xx < limitx-zx)){

		    if(GFX_OBJ_SOLID[code]==1)      // Some pixels; trans
		      pdraw16x16_64_Trans_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 1, priority);
		    else                         // all pixels; solid
		      pdraw16x16_64_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 1,priority);
		  }
		}

		xx = (xx - zx) & 0x3FF;
		code++;
		if (code > sprite_size) {
		  code %= sprite_size;
		}
	      }while(--w);
	    } else {
	      code = (code + ww);
	      if (code > sprite_size) {
		code %= sprite_size;
	      }
	    }
	    y = (y + zy) & 0x3FF;

	  }while(--hh);
	  break;
	case 2:
	  y = (y + ((hh - 1) * 16)) & 0x3FF;
	  do{

	    if(GFX_OBJ_SIZE[code] != ww) {
	      make_tile_new(code, ww,GFX_OBJ_A,GFX_OBJ_B,GFX_OBJ_SOLID,GFX_OBJ_SIZE);
	    }
	    xx = x;
	    w = ww;

	    int zy = (total_height-dy)/(hh); dy += zy;
	    dx = 0;
	    if ((y > 0) && (y < 240+32-zy+16) && y >= 0) {
	      do{
		int zx = (total_width-dx)/w; dx += zx;
		if(GFX_OBJ_SOLID[code]){
		  if((xx >= 0) && (xx < limitx-zx) && xx >= 0){
		    if(GFX_OBJ_SOLID[code]==1)      // Some pixels; trans
		      pdraw16x16_64_Trans_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 2, priority);
		    else                         // all pixels; solid
		      pdraw16x16_64_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 2, priority);
		  }
		}

		xx = (xx + zx) & 0x3FF;
		code++;
		if (code > sprite_size) {
		  code %= sprite_size;
		}
	      }while(--w);
	    } else {
	      code = (code + ww);
	      if (code > sprite_size) {
		code %= sprite_size;
	      }
	    }
	    y = (y - zy) & 0x3FF;

	  }while(--hh);
	  break;
	case 3:
	  x = (x + ((ww - 1) * 16)) & 0x3FF;
	  y = (y + ((hh - 1) * 16)) & 0x3FF;
	  do{

	    if(GFX_OBJ_SIZE[code] != ww) {
	      make_tile_new(code, ww,GFX_OBJ_A,GFX_OBJ_B,GFX_OBJ_SOLID,GFX_OBJ_SIZE);
	    }
	    xx = x;
	    w = ww;

	    int zy = (total_height-dy)/(hh); dy += zy;
	    dx = 0;
	    if ((y > 0) && (y < 240+32-zy+16) && y >= 0) {
	      do{
		int zx = (total_width-dx)/w; dx += zx;
		if((xx >= 0) && (xx < limitx-zx) && xx >= 0){

		  if(GFX_OBJ_SOLID[code]){
		    if(GFX_OBJ_SOLID[code]==1)      // Some pixels; trans
		      pdraw16x16_64_Trans_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 3, priority);
		    else                         // all pixels; solid
		      pdraw16x16_64_Mapped_back_ZoomXY_flip_Rot(&GFX_OBJ_B[code<<8], xx, y, map, zx, zy, 3, priority);
		  }
		}
		xx = (xx - zx) & 0x3FF;
		code++;
		if (code > sprite_size) {
		  code %= sprite_size;
		}

	      }while(--w);
	    } else {
	      code = (code + ww);
	      if (code > sprite_size) {
		code %= sprite_size;
	      }
	    }
	    y = (y - zy) & 0x3FF;

	  }while(--hh);
	  break;
	}
       }
     }
   } // if sprites enabled

   /*

     BG0

   */

   draw_cave_layer(0);

   /*

     BG1

   */

   draw_cave_layer(1);

   /*

     BG2

   */

   draw_cave_layer(2);

}


/*

bg ram 0x0000-0x0FFF:

byte |     bit(s)     | use
-----+FEDCBA9876543210+-----------
 0-1 |..xxxxxx........| colour
 2-3 |.xxxxxxxxxxxxxxx| tile

bg ram 0x1000-0x1FFF:

byte |     bit(s)     | use
-----+FEDCBA9876543210+-----------
 0-1 |..........xxxxxx| ?
 2-3 |................|

bg ctrl ram:

byte |     bit(s)     | use
-----+FEDCBA9876543210+-----------
 0-1 |xxx.............| x offset
 0-1 |.......xxxxxxxxx| x pos
 2-3 |xxx.............| y offset
 2-3 |......x.........| priority ?
 2-3 |.......xxxxxxxxx| y pos

object ram:

byte |     bit(s)     | use
-----+FEDCBA9876543210+-----------
 0-1 |xxxxxxxxxx......| x pos
 2-3 |xxxxxxxxxx......| y pos
 4-5 |..xxxxxx........| colour
 4-5 |............x...| flip x axis
 4-5 |.............x..| flip y axis
 6-7 |xxxxxxxxxxxxxxxx| tile
 8-9 |................|
 A-B |................|
 C-D |....xxxx........| x chain
 C-D |............xxxx| y chain
 E-F |................|

ctrl ram:

byte |     bit(s)     | use
-----+FEDCBA9876543210+-----------
08-09|...............x| object double buffer

*/

static struct VIDEO_INFO video_agallet =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   sailormn_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_ddonpach =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   ddonpach_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_dfeveron =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   cave_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_donpachi =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   donpachi_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_esprade =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   esprade_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_hotdogst =
{
   draw_cave_68k,
   384,
   240,
   32,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   cave_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_mazinger =
{
   draw_cave_68k,
   384,
   240,
   32,
   VIDEO_ROTATE_90 |
   VIDEO_ROTATABLE,
   mazinger_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_sailormn =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   sailormn_gfx,
   15625/271.5
};
static struct VIDEO_INFO video_uopoko =
{
   draw_cave_68k,
   320,
   240,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE | VIDEO_NEEDS_16BPP,
   uopoko_gfx,
   15625/271.5
};
static struct DIR_INFO dir_agallet[] =
{
  { "agallet", },
  { "air_gallet" },
  { NULL, },
};
GAME( agallet, "Air Gallet", BANPREST, 1995, GAME_SHOOT,
	.romsw = romsw_agallet,
	.clear = clear_cave_68k,
	.video = &video_agallet,
	.board = "BP962A",
	.sound = sound_agallet,
);
GMEI( ddonpach, "Dodonpachi (International)", CAVE, 1997, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C03D2",
);
CLNEI( ddonpchj, ddonpach,"Dodonpachi (Japan)", CAVE, 1997, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C03D2",
);
GMEI( donpachi, "DonPachi (USA) v1.12", CAVE, 1995, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C01DP-2",
	.sound = sound_donpachi
);
CLNEI( donpachj, donpachi, "DonPachi (Japan) v1.01", CAVE, 1995, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C01DP-2",
	.sound = sound_donpachi
);
static struct DIR_INFO dir_donpachk[] =
{
   { "donpachk", },
   { "DonPachK", },
   { ROMOF( "donpachi" ), },
   { CLONEOF( "donpachi" ) },
   { NULL, },
};
CLNE( donpachk, donpachi, "DonPachi (Korean) v1.12", CAVE, 1995, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C01DP-2",
	.sound = sound_donpachi
);
static struct DIR_INFO dir_esprade[] =
{
   { "esprade", },
   { "espradea", },
   { NULL, },
};
GME( esprade, "ESP Ra.De. (International - 4/22 98)", CAVE, 1998, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C04",
);
static struct DIR_INFO dir_espradej[] =
{
   { "espradej", },
   { ROMOF("esprade") },
   { CLONEOF("esprade") },
   { NULL, },
};
CLNE( espradej,esprade, "ESP Ra.De. (Japan - 4/21 1998)", CAVE, 1998, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C04",
);
static struct DIR_INFO dir_espradeo[] =
{
   { "espradeo", },
   { ROMOF("esprade") },
   { CLONEOF("esprade") },
   { NULL, },
};
CLNE( espradeo,esprade, "ESP Ra.De. (Japan - 4/14 1998)", CAVE, 1998, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "AT-C04",
);
static struct DIR_INFO dir_dfeveron[] =
{
   { "feveron", },
   { "dfeveron", },
   { "dangun_feveron", },
   { NULL, },
};
GAME( dfeveron, "Dangun Feveron", CAVE, 1998, GAME_SHOOT,
	.clear = clear_cave_68k,
	.video = &video_dfeveron,
	.board = "CV-01",
);
CLNEI( feversos, dfeveron, "Fever SOS", CAVE, 1998, GAME_SHOOT,
	.clear = clear_cave_68k,
	.board = "CV-01",
);
#define video_guwange video_esprade
GMEI( guwange, "Guwange", CAVE, 1999, GAME_SHOOT,
	.input = input_guwange,
	.clear = clear_cave_68k,
	.board = "AT-C05",
);
static struct DIR_INFO dir_hotdogst[] =
{
   { "hotdogst", },
   { "HotDogStorm" },
   { NULL, },
};
GAME( hotdogst, "Hotdog Storm", MARBLE, 1996, GAME_SHOOT,
	.clear = clear_cave_68k,
	.video = &video_hotdogst,
	.sound = sound_hotdogst,
);
static struct DIR_INFO dir_mazinger[] =
{
   { "mazinger", },
   { "MazingerZ" },
   { NULL, },
};
GAME( mazinger, "Mazinger Z", BANPREST, 1994, GAME_SHOOT,
	.romsw = romsw_mazinger,
	.clear = clear_mazinger,
	.video = &video_mazinger,
	.exec = execute_mazinger,
	.sound = sound_hotdogst,
);
static struct DIR_INFO dir_sailormn[] =
{
  { "sailormn", },
  { "SailorMoon", },
  { NULL, },
};
GAME( sailormn, "Pretty Soldier Sailor Moon Ver B", BANPREST, 1995, GAME_SHOOT,
	.romsw = romsw_agallet,
	.clear = clear_cave_68k,
	.video = &video_sailormn,
	.board = "BP945A",
	.sound = sound_agallet,
);
CLNEI( sailormo, sailormn, "Pretty Soldier Sailor Moon", BANPREST, 1995, GAME_SHOOT,
	.romsw = romsw_agallet,
	.clear = clear_cave_68k,
	.video = &video_sailormn,
	.board = "BP945A",
	.sound = sound_agallet,
);
static struct DIR_INFO dir_uopoko[] =
{
   { "uo_poko", },
   { "uopoko", },
   { "uopokoj", },
   { NULL, },
};
GAME( uopoko, "Uo Poko", CAVE, 1998, GAME_PUZZLE,
	.clear = clear_cave_68k,
	.video = &video_uopoko,
	.board = "CV-02",
);

CLNEI( guwanges, guwange, "Guwange (Japan, Special Ver. 00/01/01)", CAVE,
		2000, GAME_SHOOT,
	.input = input_guwange,
	.video = &video_esprade);
