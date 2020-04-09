#define DRV_DEF_DSW NULL
#define DRV_DEF_LOAD load_pang
#define DRV_DEF_EXEC execute_pang
#define DRV_DEF_SOUND sound_pang
/* Capcom mitchell hardware : z80 games !!!
   This driver is quite a nightmare, congratulations to mame to have emulated it first.
   Kabuki encryption, rom banks, ram banks, code executed in ram, eeprom, and tweaks for
   the inputs... !!!
   This driver could maybe be improved to be faster, but since it's a z80 with only
   1 bg layer, it's already quite fast ! */

#include "gameinc.h"
#include "decode.h"
#include "sound/adpcm.h"
#include "sound/2413intf.h"
#include "sasound.h"
#include "cps1.h" // eeprom
#include "blit.h"
#include "savegame.h"

static struct ROM_INFO rom_pkladies[] =
{
  { "pko-prg1.14f", 0x08000, 0x86585a94, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "pko-prg2.15f", 0x10000, 0x86cbe82d, REGION_ROM1, 0x10000, LOAD_NORMAL },
  LOAD8_16(  REGION_GFX1,  0x000000,  0x80000,
            "pko-001.8h",  0x1ead5d9b, "pko-003.8j",  0x339ab4e6),
  LOAD8_16(  REGION_GFX1,  0x100000,  0x80000,
            "pko-002.9h",  0x1cf02586, "pko-004.9j",  0x09ccb442),
  { "pko-chr1.2j", 0x20000, 0x31ce33cd, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "pko-chr2.3j", 0x20000, 0xad7e055f, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "pko-voi1.2d", 0x20000, 0x07e0f531, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { "pko-voi2.3d", 0x20000, 0x18398bf6, REGION_SMP1, 0x20000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_pang[] =
{
  { "pang6.bin", 0x08000, 0x68be52cd, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "pang7.bin", 0x20000, 0x4a2e70f6, REGION_ROM1, 0x10000, LOAD_NORMAL },

  { "pang_09.bin", 0x20000, 0x3a5883f5, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bb3.bin", 0x20000, 0x79a8ed08, REGION_GFX1, 0x020000, LOAD_NORMAL },
	/* 40000-7ffff empty */
  { "pang_11.bin", 0x20000, 0x166a16ae, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "bb5.bin", 0x20000, 0x2fb3db6c, REGION_GFX1, 0x0a0000, LOAD_NORMAL },
  { "bb5.bin", 0x20000, 0x2fb3db6c, REGION_GFX1, 0x0e0000, LOAD_NORMAL },
	/* c0000-fffff empty */
  { "bb10.bin", 0x20000, 0xfdba4f6e, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "bb9.bin", 0x20000, 0x39f47a63, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "bb1.bin", 0x20000, 0xc52e5b8e, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_spang[] =
{
  { "spe_06.rom", 0x08000, 0x1af106fb, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "spe_07.rom", 0x20000, 0x208b5f54, REGION_ROM1, 0x10000, LOAD_NORMAL },
  { "spe_08.rom", 0x20000, 0x2bc03ade, REGION_ROM1, 0x30000, LOAD_NORMAL },
  { "spe_02.rom", 0x20000, 0x63c9dfd2, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "03.f2", 0x20000, 0x3ae28bc1, REGION_GFX1, 0x020000, LOAD_NORMAL },
	/* 40000-7ffff empty */
  { "spe_04.rom", 0x20000, 0x9d7b225b, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "05.g2", 0x20000, 0x4a060884, REGION_GFX1, 0x0a0000, LOAD_NORMAL },
	/* c0000-fffff empty */
  { "05.g2", 0x20000, 0x4a060884, REGION_GFX1, 0x0e0000, LOAD_NORMAL },
  { "spj10_2k.bin", 0x20000, 0xeedd0ade, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "spj09_1k.bin", 0x20000, 0x04b41b75, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "spe_01.rom", 0x20000, 0x2d19c133, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_block[] =
{
  { "ble_05.rom", 0x08000, 0xc12e7f4c, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "ble_06.rom", 0x20000, 0xcdb13d55, REGION_ROM1, 0x10000, LOAD_NORMAL },
  { "ble_07.rom", 0x20000, 0x1d114f13, REGION_ROM1, 0x30000, LOAD_NORMAL },
  { "bl_08.rom", 0x20000, 0xaa0f4ff1, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "bl_08.rom", 0x20000, 0xaa0f4ff1, REGION_GFX1, 0x040000, LOAD_NORMAL },
  { "bl_09.rom", 0x20000, 0x6fa8c186, REGION_GFX1, 0x020000, LOAD_NORMAL },
  { "bl_09.rom", 0x20000, 0x6fa8c186, REGION_GFX1, 0x060000, LOAD_NORMAL },
  { "bl_18.rom", 0x20000, 0xc0acafaf, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "bl_18.rom", 0x20000, 0xc0acafaf, REGION_GFX1, 0x0c0000, LOAD_NORMAL },
  { "bl_19.rom", 0x20000, 0x1ae942f5, REGION_GFX1, 0x0a0000, LOAD_NORMAL },
  { "bl_19.rom", 0x20000, 0x1ae942f5, REGION_GFX1, 0x0e0000, LOAD_NORMAL },
  { "bl_16.rom", 0x20000, 0xfadcaff7, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "bl_17.rom", 0x20000, 0x5f8cab42, REGION_GFX2, 0x020000, LOAD_NORMAL },
  { "bl_01.rom", 0x20000, 0xc2ec2abb, REGION_SMP1, 0x00000, LOAD_NORMAL },
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_blockj[] =
{
  { "blj_05.rom", 0x08000, 0x3b55969a, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "ble_06.rom", 0x20000, 0xcdb13d55, REGION_ROM1, 0x10000, LOAD_NORMAL },
  { "blj_07.rom", 0x20000, 0x1723883c, REGION_ROM1, 0x30000, LOAD_NORMAL },
  /* Clone of block all the other regions are the same */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct ROM_INFO rom_blockjoy[] =
{
  { "ble_05.bin", 0x08000, 0xfa2a4536, REGION_ROM1, 0x00000, LOAD_NORMAL },
  { "blf_06.bin", 0x20000, 0xe114ebde, REGION_ROM1, 0x10000, LOAD_NORMAL },
  { "ble_07.rom", 0x20000, 0x1d114f13, REGION_ROM1, 0x30000, LOAD_NORMAL },
  /* Clone of block all the other regions are the same */
  { NULL, 0, 0, 0, 0, 0 }
};

static struct INPUT_INFO input_pkladies[] =
{
  INP0( TEST, 0x00, 0x02 ),

  INP0( SERVICE, 0x01, 0x01 ),
  INP0( COIN1, 0x01, 0x80 ),

  INP0( P1_KAN, 0x02, 0x20 ),
  INP0( P1_E, 0x02, 0x40 ),
  INP0( P1_A, 0x02, 0x80 ),

  INP0( P1_PON, 0x03, 0x20 ),
  INP0( P1_B, 0x03, 0x80 ),

  INP0( P1_CHI, 0x04, 0x20 ),
  INP0( P1_C, 0x04, 0x80 ),

  INP0( P1_D, 0x05, 0x80 ),


/* P2 Control */
  INP0( P1_KAN, 0x07, 0x20 ),
/* P2 Control */
  INP0( P1_E, 0x07, 0x40 ),
/* P2 Control */
  INP0( P1_A, 0x07, 0x80 ),

/* P2 Control */
  INP0( P1_PON, 0x8, 0x20 ),
/* P2 Control */
  INP0( P1_B, 0x8, 0x80 ),

/* P2 Control */
  INP0( P1_CHI, 0x9, 0x20 ),
/* P2 Control */
  INP0( P1_C, 0x9, 0x80 ),

/* P2 Control */
  INP0( P1_D, 0xa, 0x80 ),

   END_INPUT
};

static struct INPUT_INFO input_pang[] =
{
  INP0( TEST, 0x00, 0x02 ),

  INP0( P2_START, 0x01, 0x02 ),
  INP0( P1_START, 0x01, 0x08 ),
  INP0( COIN2, 0x01, 0x40 ),
  INP0( COIN1, 0x01, 0x80 ),

  INP0( P1_B2, 0x02, 0x04 ),
  INP0( P1_B1, 0x02, 0x08 ),
  INP0( P1_RIGHT, 0x02, 0x10 ),
  INP0( P1_LEFT, 0x02, 0x20 ),
  INP0( P1_DOWN, 0x02, 0x40 ),
  INP0( P1_UP, 0x02, 0x80 ),

  INP0( P2_B2, 0x03, 0x04 ),
  INP0( P2_B1, 0x03, 0x08 ),
  INP0( P2_RIGHT, 0x03, 0x10 ),
  INP0( P2_LEFT, 0x03, 0x20 ),
  INP0( P2_DOWN, 0x03, 0x40 ),
  INP0( P2_UP, 0x03, 0x80 ),
   END_INPUT
};

static struct INPUT_INFO input_block[] =
{
  INP0( TEST, 0x00, 0x02 ),
  INP0( P2_START, 0x01, 0x02 ),
  INP0( P1_START, 0x01, 0x08 ),
  INP0( COIN2, 0x01, 0x40 ),
  INP0( COIN1, 0x01, 0x80 ),

  INP0( P1_RIGHT, 0x02, 0x10 ),
  INP0( P1_LEFT, 0x02, 0x20 ),
  INP0( P1_B1, 0x02, 0x80 ),

  INP0( P2_RIGHT, 0x03, 0x10 ),
  INP0( P2_LEFT, 0x03, 0x20 ),
  INP0( P2_B1, 0x03, 0x80 ),
  // port 4 is dial 0, port 5 is dial 1

   END_INPUT
};

static GfxLayout charlayout =
{
	8,8,	/* 8*8 characters */
	32768,	/* 32768 characters */
	4,		/* 4 bits per pixel */
	{ 32768*16*8+4, 32768*16*8+0,4, 0 },
	{ 0, 1, 2, 3, 8+0, 8+1, 8+2, 8+3 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16 },
	16*8    /* every char takes 16 consecutive bytes */
};

static GfxLayout spritelayout =
{
	16,16,  /* 16*16 sprites */
	2048,   /* 2048 sprites */
	4,      /* 4 bits per pixel */
	{ 2048*64*8+4, 2048*64*8+0, 4, 0 },
	{ 0, 1, 2, 3, 8+0, 8+1, 8+2, 8+3,
			32*8+0, 32*8+1, 32*8+2, 32*8+3, 33*8+0, 33*8+1, 33*8+2, 33*8+3 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16,
			8*16, 9*16, 10*16, 11*16, 12*16, 13*16, 14*16, 15*16 },
	64*8    /* every sprite takes 64 consecutive bytes */
};

static struct GFX_LIST gfxdecodeinfo[] =
{
	{ REGION_GFX1, &charlayout }, // 128 color banks
	{ REGION_GFX2, &spritelayout }, //  16 color banks
	{ 0, NULL } /* end of array */
};

static GfxLayout marukin_charlayout =
{
	8,8,	/* 8*8 characters */
	65536,	/* 65536 characters */
	4,		/* 4 bits per pixel */
	{ 3*4, 2*4, 1*4, 0*4 },
	{ 0, 1, 2, 3, 16+0, 16+1, 16+2, 16+3 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8    /* every char takes 32 consecutive bytes */
};

static struct GFX_LIST marukin_gfxdecodeinfo[] =
{
	{ REGION_GFX1, &marukin_charlayout }, // 128 color banks
	{ REGION_GFX2, &spritelayout }, //  16 color banks
	{ 0, NULL } /* end of array */
};

static UINT8 *decoded;

static void mitchell_decode(int swap_key1,int swap_key2,int addr_key,int xor_key)
{
  int i;
  unsigned char *rom = load_region[REGION_CPU1];
  int diff = get_region_size(REGION_CPU1);
  decoded = AllocateMem(diff);

  kabuki_decode(rom,decoded,rom,0x0000,0x8000, swap_key1,swap_key2,addr_key,xor_key);
  for (i = 0x10000;i < diff;i += 0x4000)
    kabuki_decode(rom+i,decoded+i,rom+i,0x8000,0x4000, swap_key1,swap_key2,addr_key,xor_key);
  z80_offdata = rom - decoded;
}

static void block_decode(void)    { mitchell_decode(0x02461357,0x64207531,0x0002,0x01); }
static void spang_decode(void)    { mitchell_decode(0x45670123,0x45670123,0x5852,0x43); }
// static void cworld_decode(void)   { mitchell_decode(0x04152637,0x40516273,0x5751,0x43); }
static void pang_decode(void)     { mitchell_decode(0x01234567,0x76543210,0x6548,0x24); }
static void mgakuen2_decode(void) { mitchell_decode(0x76543210,0x01234567,0xaa55,0xa5); }

UINT8 *palram,*objram;

struct {
  // there are 2 ram banks in these games (not linear ram)
  // handling it this way seems to be the easiest solution for now
  UINT8 cpu_bank,
    video_bank,palbank,flipscreen; // 4 UINT8 -> no alignement issue
  UINT16 keymatrix;
} cfg;

static void pang_gfxctrl_w(UINT32 offset, UINT8 data)
{
  /* bit 0 is unknown (used, maybe back color enable?) */

  /* bit 1 is coin counter */
  // coin_counter_w(0,data & 2);

  /* bit 2 is flip screen */
  cfg.flipscreen = data & 0x04;

  /* bit 3 is unknown (used, e.g. marukin pulses it on the title screen) */

  /* bit 4 selects OKI M6295 bank */
  OKIM6295_set_bank_base(0, ALL_VOICES, (data & 0x10) ? 0x40000 : 0x00000);

  /* bit 5 is palette RAM bank selector (doesn't apply to mgakuen) */
  if (data & 0x20) {
    cfg.palbank = 1;
  } else {
    cfg.palbank = 0;
  }

  /* bits 6 and 7 are unknown, used in several places. At first I thought */
  /* they were bg and sprites enable, but this screws up spang (screen flickers */
  /* every time you pop a bubble). However, not using them as enable bits screws */
  /* up marukin - you can see partially built up screens during attract mode. */
}

static int clear_pal;

static void pang_paletteram_w(UINT32 offset, UINT8 data) {
  clear_pal = 1;
  palram[0x800*cfg.palbank+(offset & 0x7ff)] = data;
}

static UINT8 pang_paletteram_r(UINT32 offset) {
  return palram[0x800*cfg.palbank+(offset & 0x7ff)];
}

/* The inputs are a real mess here... */

static int dial[2],dial_selected;
static int init_eeprom_count;

static UINT8  block_input_r (UINT32 offset) {
  static int dir[2];

  if (dial_selected)
    {
      int delta;

      delta = (input_buffer[4 + offset] - dial[offset]) & 0xff;
      if (delta & 0x80)
	{
	  delta = (-delta) & 0xff;
	  if (dir[offset])
	    {
	      /* don't report movement on a direction change, otherwise it will stutter */
	      dir[offset] = 0;
	      delta = 0;
	    }
	}
      else if (delta > 0)
	{
	  if (dir[offset] == 0)
	    {
	      /* don't report movement on a direction change, otherwise it will stutter */
	      dir[offset] = 1;
	      delta = 0;
	    }
	}
      if (delta > 0x3f) delta = 0x3f;
/*       if (offset == 0) */
      return delta << 2;
    }
  else
    {
      int res;

      res = input_buffer[2 + offset] & 0xf7;
      if (dir[offset]) res |= 0x08;

      return res;
    }
}

static void  block_dial_control_w (UINT32 offset, UINT8 data) {
  if (data == 0x08)
    {
      /* reset the dial counters */
      dial[0] = input_buffer[4];
      dial[1] = input_buffer[5];
    }
  else if (data == 0x80)
    dial_selected = 0;
  else
    dial_selected = 1;
}

static UINT8  mahjong_input_r (UINT32 offset) {
  int i;

  for (i = 0;i < 5;i++)
    if (cfg.keymatrix & (0x80 >> i)) return input_buffer[2 + 5 * offset + i];

  return 0xff;
}

static void  mahjong_input_select_w (UINT32 offset, UINT8 data) {
  cfg.keymatrix = data;
}

static int input_type;

static UINT8  input_r(UINT32 offset) {
  switch (input_type)
    {
    case 0:
    default:
      return input_buffer[1 + offset];
      break;
    case 1:	/* Mahjong games */
      if (offset) return mahjong_input_r(offset-1);
      else return input_buffer[1];
      break;
    case 2:	/* Block Block - dial control */
      if (offset) return block_input_r(offset-1);
      else return input_buffer[1];
      break;
    case 3:	/* Super Pang - simulate START 1 press to initialize EEPROM */
      if (offset || init_eeprom_count == 0) return input_buffer[1 + offset];
      else
	{
	  init_eeprom_count--;
	  return input_buffer[1] & ~0x08;
	}
      break;
    }
}

static void  input_w (UINT32 offset, UINT8 data) {
  switch (input_type)
    {
    case 0:
    default:
      // logerror("PC %04x: write %02x to port 01\n",activecpu_get_pc(),data);
      break;
    case 1:
      mahjong_input_select_w(offset,data);
      break;
    case 2:
      block_dial_control_w(offset,data);
      break;
    }
}

static void pang_bankswitch_w(UINT32 offset, UINT8 data)
{
  int bankaddress;

  data &= 0xf;
  if (cfg.cpu_bank != data) {
    cfg.cpu_bank = data;
    bankaddress = 0x10000 + data * 0x4000;

    memcpy(ROM+0x8000,ROM+bankaddress,0x4000);
    memcpy(decoded+0x8000,decoded+bankaddress,0x4000);
  }
}

static void restore_bank() {
  // savegame callback to restore the cpu bank
  int old = cfg.cpu_bank;
  cfg.cpu_bank = 0xff;
  pang_bankswitch_w(0,old);
  clear_pal = 1;
}

static UINT8  pang_port5_r (UINT32 offset) {
  int bit;
  UINT8 res;

  bit = EEPROM_read_bit() << 7;
  // 2 bits are togled in the cpu frame, 1 for the vblank, the other unknown

/* if (Machine->gamedrv == &driver_mgakuen2)	/\* hack... music doesn't work otherwise *\/ */
/* 	bit ^= 0x08; */

  res = (input_buffer[0] & 0x7f) | bit;
  return res;
}

static UINT8 *videoram;

void  pang_videoram_w (UINT32 offset, UINT8 data) {
  offset &= 0xfff;
  if (cfg.video_bank)
    objram[offset] = data;
  else
    videoram[offset] = data;
}

UINT8  pang_videoram_r (UINT32 offset) {
  offset &= 0xfff;
  if (cfg.video_bank)
    return objram[offset];
  else
    return videoram[offset];
}

static void  eeprom_cs_w (UINT32 offset, UINT8 data) {
	EEPROM_set_cs_line(data ? CLEAR_LINE : ASSERT_LINE);
}

static void  eeprom_clock_w (UINT32 offset, UINT8 data) {
	EEPROM_set_clock_line(data ? CLEAR_LINE : ASSERT_LINE);
}

static void  eeprom_serial_w (UINT32 offset, UINT8 data) {
	EEPROM_write_bit(data);
}

static UINT8 *BG_SOLID, *SPR, *SPR_SOLID;
static int nb_sprites,nb_tiles;

/* static UINT8 port12_r(UINT32 offset) { */
/*   return input_buffer[12+(offset & 1)]; */
/* } */

static void videobank_w(UINT32 offset, UINT8 data) {
  cfg.video_bank = data;
}

static int layer_id_data[2];
static char *layer_id_name[4] =
{
   "BG", "SPR",
};

static void dup_writes(UINT32 offset, UINT8 data) {
  ROM[offset] = decoded[offset] = data;
}

static void load_pang() {
  input_type = 0;
  clear_pal = 1;
  if (is_current_game("pang"))
    pang_decode();
  else if (is_current_game("spang")) {
    spang_decode();
    EEPROM_init(&pang3_eeprom_interface);
    load_eeprom();
    input_type = 3;
    init_eeprom_count = 1000;
  } else if (is_current_game("pkladies")) {
    mgakuen2_decode();
    input_type = 1;
    EEPROM_init(&pang3_eeprom_interface);
    load_eeprom();
  } else if (is_current_game("block") || is_current_game("blockj") || is_current_game("blockjoy")) {
    input_type = 2;
    block_decode();
    EEPROM_init(&pang3_eeprom_interface);
    load_eeprom();
    if (!is_current_game("blockjoy")) {
      // the mouse port is ignored in block block (World 911106 Joystick) ... there might be a way to force it,
      // but it's not obvious
      GameMouse = 1;
    }
  }

  RAMSize = 0x4000 - 0x800;
  cfg.cpu_bank = 0xff;

  /* How this hardware works :
      - rom + banks kabuki encrypted !
      - some zone of the ram takes code to be executed (ramrom) !
      This means that it's even more complicated than cps1/cps2 banks since here
      the banks contain code to be executed !
     So this is rather extreme. In this case using the classical raine bankswitch code
     with pointers instead of memcpys would make things insanely complicated.
     To keep things understandable, I'll have to use a memcpy for the bank here */
  RAM = decoded + 0xc800;
  videoram = decoded + 0xd000;
  /* Allocate the ram banks */
  if(!(palram=AllocateMem(0x1000))) return;
  if(!(objram=AllocateMem(0x1000))) return;
  // It's confirmed : this z80 really executes code in its banks !!!
  // With a data bank, it crashes even before the message "RAM OK"
  // z80_init_data_banks(0,REGION_ROM1,0x10000,0x4000);

  AddZ80AROMBase(decoded,0x38,0x66);
  AddZ80AReadByte(0x0000, 0xbfff, NULL, ROM); // ROM (data decoded) + bank
  // AddZ80AReadByte(0x0000, 0x7fff, NULL, ROM); // ROM (data decoded) + bank
  // AddZ80AReadByte(0x8000, 0xbfFF, NULL, NULL); // Z80 bank (data)
  if (is_current_game("spang")) {
    // spang actually executes code in ram, so the writes must be duplicated in
    // the rom area and in the decoded area
    AddZ80AWrite(0xe000,0xffff, dup_writes, NULL);
  } else if (is_current_game("pkladies")) {
    AddZ80AWrite(0xe000,0xefff, dup_writes, NULL);
  }

  /* The palette is banked. I guess I could use a data bank for that, but it would not
     be much faster than these little functions which make the code easier for me for
     now */
  if (1) { // (!is_current_game("pkladies")) { // pkladies has no ram banks !
    AddZ80ARead(0xc000,0xc7ff, pang_paletteram_r, NULL);
    AddZ80AWrite(0xc000,0xc7ff, pang_paletteram_w, NULL);

    AddZ80ARead(0xd000,0xdfff, pang_videoram_r, NULL);
    AddZ80AWrite(0xd000,0xdfff, pang_videoram_w, NULL);
  } else {
    // AddZ80ARW(0xc000, 0xc7ff, NULL, palram);
    AddZ80ARead(0xc000,0xc7ff, pang_paletteram_r, NULL);
    AddZ80AWrite(0xc000,0xc7ff, pang_paletteram_w, NULL);

    AddZ80ARW(0xf000, 0xffff, NULL, objram);
  }
  AddZ80ARW(0xc800, 0xffff, NULL, RAM);

  AddZ80AWriteByte(0x0000, 0xffff, DefBadWriteZ80, NULL);

  AddZ80AReadPort(0, 2, input_r, NULL);
  /*   AddZ80AReadPort(3, 4, port12_r, NULL); // cards games mgakuen only */
  AddZ80AReadPort(5, 5, pang_port5_r, NULL);
  AddZ80AReadPort(0, 0xff, DefBadReadPortZ80, NULL);

  AddZ80AWritePort(0, 0, pang_gfxctrl_w, NULL);
  AddZ80AWritePort(1, 1, input_w, NULL);
  AddZ80AWritePort(2, 2, pang_bankswitch_w, NULL);

  AddZ80AWritePort(3, 3, YM2413_data_port_0_w, NULL);
  AddZ80AWritePort(4, 4, YM2413_register_port_0_w, NULL);
  AddZ80AWritePort(5, 5, OKIM6295_data_0_w, NULL);

  AddZ80AWritePort(7, 7, videobank_w, NULL);
  AddZ80AWritePort(8, 8, eeprom_cs_w, NULL);
  AddZ80AWritePort(0x10, 0x10, eeprom_clock_w, NULL);
  AddZ80AWritePort(0x18, 0x18, eeprom_serial_w, NULL);
  AddZ80AWritePort(0, 0xff, DefBadWritePortZ80, NULL);
  AddZ80AInit();

  /* Color 15 is transparent, so we must take a reversed color mapper... */
  set_colour_mapper(&col_map_12bit_xxxxRRRRGGGGBBBB_Rev);
  InitPaletteMap(palram, 0x80, 0x10, 0x1000);
  /* And now invert the colors of all the sprites */
  // The xor is now applied before the regions are decoded with the layouts
  // -> xor ff instead of just 0f
  {
    UINT32 *spr = (UINT32*)load_region[REGION_GFX1];
    int size;
    for (size = get_region_size(REGION_GFX1)/4-4; size >= 0; size--) {
      spr[size] ^= 0xffffffff;
    }
    spr = (UINT32*)load_region[REGION_GFX2];
    for (size = get_region_size(REGION_GFX2)/4-4; size >= 0; size--) {
      spr[size] ^= 0xffffffff;
    }
  }

  nb_tiles = 0;
  memset(input_buffer,0xff,0x10);

  layer_id_data[0] = add_layer_info(layer_id_name[0]);
  layer_id_data[1] = add_layer_info(layer_id_name[1]);
  AddSaveData(SAVE_USER_1, (UINT8 *)&cfg, sizeof(cfg));
  AddSaveData(SAVE_USER_2, palram, 0x1000);
  AddSaveData(SAVE_USER_3, objram, 0x1000);
  AddLoadCallback(restore_bank);
}

static void execute_pang() {
  /* bits 0 and (sometimes) 3 are checked in the interrupt handler. */
  /* Maybe they are vblank related, but I'm not sure. */
  /* bit 3 is checked before updating the palette so it really seems to be vblank. */
  /* Many games require two interrupts per frame and for these bits to toggle, */
  /* otherwise music doesn't work. */

  if (GameMouse) {
    int mx,my;
    GetMouseMickeys(&mx,&my);

    if(!(input_buffer[2]&0x10)) mx = +15;
    if(!(input_buffer[2]&0x20)) mx = -15;

    input_buffer[4] += mx;
    if (*MouseB)
      input_buffer[2] &= 0x7f;
  }

  cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));
  cpu_interrupt(CPU_Z80_0, 0x38);
  input_buffer[0] = (input_buffer[0] & 0xf6) | 1;
  // One interrupt for vbl, the other for music as it seems...
  cpu_execute_cycles(CPU_Z80_0, CPU_FRAME_MHz(4,60));
  cpu_interrupt(CPU_Z80_0, 0x38);
  input_buffer[0] = (input_buffer[0] & 0xf6) | 8;


}

static void draw() {
  int x16,y16,zzz,zzzz;
  int zz;
  int x,y;
  UINT16 code;
  UINT8 attr,*map;

  if (clear_pal) {
    ClearPaletteMap();
  }

  if (!nb_tiles) {
    BG_SOLID = gfx_solid[0];
    SPR = load_region[REGION_GFX2];
    SPR_SOLID = gfx_solid[1];
    nb_sprites = get_region_size(REGION_GFX2)/0x100;
    nb_tiles = get_region_size(REGION_GFX1)/0x40;
  }

  // the bg layer must be drawn with transparency or we get bad things on screen
  MAP_PALETTE_MAPPED_NEW(
			 0,
			 16,
			 map
			 );
  if (display_cfg.bpp == 8)
    clear_game_screen(map[15]);
  else if (display_cfg.bpp < 32)
    clear_game_screen(ReadWord(&map[15*2]));
  else
    clear_game_screen(ReadLong(&map[15*4]));

  if(check_layer_enabled(layer_id_data[0])) {
    MAKE_SCROLL_512x256_2_8(64, 8);
    START_SCROLL_512x256_2_8(16,16,384,240);
    {
      code = ReadWord(&videoram[zz]);
      attr = RAM[zz/2]; // colorram
      if (code < nb_tiles) {
	if (BG_SOLID[code]) {
	  MAP_PALETTE_MAPPED_NEW(
				 attr & 0x7f,
				 16,
				 map
				 );

	  if (BG_SOLID[code] == 1) { // some trans
	    if (attr & 0x80)
	      Draw8x8_Trans_Mapped_FlipY_Rot(&GFX[code<<6],x,y,map);
	    else
	      Draw8x8_Trans_Mapped_Rot(&GFX[code<<6],x,y,map);
	  } else { // all solid
	    if (attr & 0x80)
	      Draw8x8_Mapped_FlipY_Rot(&GFX[code<<6],x,y,map);
	    else
	      Draw8x8_Mapped_Rot(&GFX[code<<6],x,y,map);
	  }
	}
      }
    }
    END_SCROLL_512x256_2_8();
  }

  if(check_layer_enabled(layer_id_data[1]))
  {
    int offs,sx,sy;

    /* the last entry is not a sprite, we skip it otherwise spang shows a bubble */
    /* moving diagonally across the screen */
    for (offs = 0x1000-0x40;offs >= 0;offs -= 0x20)
      {
	UINT16 code = objram[offs];
	UINT8 attr = objram[offs+1];
	UINT8 color = attr & 0x0f;
	sx = objram[offs+3] + ((attr & 0x10) << 4)-64+16;
	sy = ((objram[offs+2] + 8) & 0xff);
	code += (attr & 0xe0) << 3;
	if (cfg.flipscreen)
	  {
	    sx = 496-64 - sx;
	    sy = 240 - sy;
	  }
	if (code > nb_sprites) {
	  continue;
	}
	if (SPR_SOLID[code] && sx < 384+16 && sy < 240+16 && sx > 0 && sy > 0) {
	  MAP_PALETTE_MAPPED_NEW(
				 color,
				 16,
				 map
				 );

	  if (SPR_SOLID[code]==1) { // some transp
	    if (cfg.flipscreen)
	      Draw16x16_Trans_Mapped_FlipXY_Rot(&SPR[code<<8],sx,sy,map);
	    else
	      Draw16x16_Trans_Mapped_Rot(&SPR[code<<8],sx,sy,map);
	  } else { // everything solid
	    if (cfg.flipscreen)
	      Draw16x16_Mapped_FlipXY_Rot(&SPR[code<<8],sx,sy,map);
	    else
	      Draw16x16_Mapped_Rot(&SPR[code<<8],sx,sy,map);
	  }
	}
      }
  }
}

static struct VIDEO_INFO video_pang =
{
   draw,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   gfxdecodeinfo,
};

static struct VIDEO_INFO video_pkladies =
{
   draw,
   384,
   240,
   16,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   marukin_gfxdecodeinfo,
};

static struct VIDEO_INFO video_block =
{
   draw,
   384,
   240,
   16,
   VIDEO_ROTATE_270 |
   VIDEO_ROTATABLE,
   gfxdecodeinfo,
};

static struct YM2413interface ym2413_interface =
{
        1,      /* 1 chip */
        3579545,        /* ??? */
        { YM2413_VOL(255,MIXER_PAN_CENTER,255,MIXER_PAN_CENTER) },      /* Volum
e */
};

static struct OKIM6295interface oki_interface =
{
	1,                  /* 1 chip */
	{ 8000 },           /* 8000Hz frequency? */
	{ REGION_SMP1 },	/* memory region */
	{ 120 }
};

struct SOUND_INFO sound_pang[] =
{
  { SOUND_YM2413,  &ym2413_interface },
   { SOUND_M6295,  &oki_interface,  },
   { 0,             NULL,               },
};

GMEI( pang,
     "Pang (World)",
     MITCHELL,
     1989,
     GAME_MISC);
CLNEI(spang, pang, "Super Pang (World 900914)",MITCHELL,1990,GAME_MISC);

GMEI( pkladies, "Poker Ladies", MITCHELL, 1989, GAME_MISC);

GMEI( block, "Block Block (World 910910)", CAPCOM, 1991, GAME_BREAKOUT);
CLNEI( blockj, block, "Block Block (Japan 910910)", CAPCOM, 1991, GAME_BREAKOUT);
CLNEI( blockjoy, block, "Block Block (World 911106 Joystick only)", CAPCOM, 1991, GAME_BREAKOUT);

