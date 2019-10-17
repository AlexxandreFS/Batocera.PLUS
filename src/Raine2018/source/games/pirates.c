#define DRV_DEF_DSW NULL
/**
 Pirates (c)1994 NIX
 Genix (c)1994 NIX

 -- todo --

 the eeprom does not work (neither in mame)
 there seem to be a few gfx glitches when buildings are destroyed (off by 1 pixel somewhere?)

 speedup

**/

#include "gameinc.h"
#include "taitosnd.h"
#include "sasound.h"		// sample support routines
#include "adpcm.h"
#include "blit.h" // clear_game_screen
#include "mame/eeprom.h"
#include "savegame.h" // load_eeprom
#include "decode.h"


static struct ROM_INFO rom_pirates[] =
{
	/* 68000 Code (encrypted) */
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "r_449b.bin",  0x224aeeda, "l_5c1e.bin",  0x46740204),
   /* GFX (encrypted) */
  { "p4_4d48.bin", 0x080000, 0x89fda216, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "p2_5d74.bin", 0x080000, 0x40e069b4, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "p1_7b30.bin", 0x080000, 0x26d78518, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "p8_9f4f.bin", 0x080000, 0xf31696ea, REGION_GFX1, 0x180000, LOAD_NORMAL },
	/* GFX (encrypted) */
  { "s1_6e89.bin", 0x080000, 0xc78a276f, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "s2_6df3.bin", 0x080000, 0x9f0bad96, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "s4_fdcc.bin", 0x080000, 0x8916ddb5, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "s8_4b7c.bin", 0x080000, 0x1c41bd2c, REGION_GFX2, 0x180000, LOAD_NORMAL },
	/* OKI samples (encrypted) */
   { "s89_49d4.bin", 0x080000, 0x63a739ec, REGION_SMP1, 0x000000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};



static struct ROM_INFO rom_genix[] =
{
	/* 68000 Code (encrypted) */
  LOAD8_16(  REGION_ROM1,  0x00000,  0x80000,
            "1.15",  0xd26abfb0, "2.16",  0xa14a25b4),
   /* GFX (encrypted) */
  { "7.34", 0x040000, 0x58da8aac, REGION_GFX1, 0x000000, LOAD_NORMAL },
  { "9.35", 0x040000, 0x96bad9a8, REGION_GFX1, 0x080000, LOAD_NORMAL },
  { "8.48", 0x040000, 0x0ddc58b6, REGION_GFX1, 0x100000, LOAD_NORMAL },
  { "10.49", 0x040000, 0x2be308c5, REGION_GFX1, 0x180000, LOAD_NORMAL },
  { "10.49", 0x040000, 0x2be308c5, REGION_GFX1, 0x1c0000, LOAD_NORMAL },
	/* GFX (encrypted) */
  { "6.69", 0x040000, 0xb8422af7, REGION_GFX2, 0x000000, LOAD_NORMAL },
  { "5.70", 0x040000, 0xe46125c5, REGION_GFX2, 0x080000, LOAD_NORMAL },
  { "4.71", 0x040000, 0x7a8ed21b, REGION_GFX2, 0x100000, LOAD_NORMAL },
  { "3.72", 0x040000, 0xf78bd6ca, REGION_GFX2, 0x180000, LOAD_NORMAL },
  { "3.72", 0x040000, 0xf78bd6ca, REGION_GFX2, 0x1c0000, LOAD_NORMAL },
	/* OKI samples (encrypted) */
  { "0.31", 0x080000, 0x80d087bc, REGION_SMP1, 0x000000, LOAD_NORMAL },
   {           NULL,          0,          0, 0, 0, 0, },
};

static struct EEPROM_interface eeprom_interface =
{
	6,				/* address bits */
	16,				/* data bits */
	"*110",			/*  read command */
	"*101",			/* write command */
	0,				/* erase command */
	"*10000xxxx",	/* lock command */
	"*10011xxxx"	/* unlock command */
};

static  void pirates_out_w(UINT32 offset, UINT8 data)
{
  /* bits 0-2 control EEPROM */
  EEPROM_write_bit(data & 0x04);
  EEPROM_set_cs_line((data & 0x01) ? CLEAR_LINE : ASSERT_LINE);
  EEPROM_set_clock_line((data & 0x02) ? ASSERT_LINE : CLEAR_LINE);

  /* bit 6 selects oki bank */
  OKIM6295_set_bank_base(0, ALL_VOICES, (data & 0x40) ? 0x40000 : 0x00000);
  /* bit 7 used (function unknown) */
}

static struct INPUT_INFO input_genix[] =
{
   INP0( P1_UP, 0x000000, 0x01 ),
   INP0( P1_DOWN, 0x000000, 0x02 ),
   INP0( P1_LEFT, 0x000000, 0x04 ),
   INP0( P1_RIGHT, 0x000000, 0x08 ),
   INP0( P1_B1, 0x000000, 0x10 ),
   INP0( P1_B2, 0x000000, 0x20 ),
   INP0( P1_B3, 0x000000, 0x40 ),
   INP0( P1_START, 0x000000, 0x80 ),

   INP0( P2_UP, 0x000001, 0x01 ),
   INP0( P2_DOWN, 0x000001, 0x02 ),
   INP0( P2_LEFT, 0x000001, 0x04 ),
   INP0( P2_RIGHT, 0x000001, 0x08 ),
   INP0( P2_B1, 0x000001, 0x10 ),
   INP0( P2_B2, 0x000001, 0x20 ),
   INP0( P2_B3, 0x000001, 0x40 ),
   INP0( P2_START, 0x000001, 0x80 ),

   INP0( COIN1, 0x000002, 0x01 ),
   INP0( COIN2, 0x000002, 0x02 ),
   INP0( SERVICE, 0x000002, 0x04 ),
   INP0( TEST, 0x000002, 0x08 ),

   END_INPUT
};

static struct OKIM6295interface m6295_interface =
{
   1,               // 1 chip
   { 1333333/165  },            // rate
   { REGION_SOUND1 },// { OKISND },      // rom list
   { 220 }, // volume - still unused
};

static struct SOUND_INFO sound_genix[] =
{
   { SOUND_M6295,   &m6295_interface,     },
   { 0,             NULL,                 },
};

static GfxLayout charlayout =
{
	8,8,
	RGN_FRAC(1,4),
	4,
	{ RGN_FRAC(3,4), RGN_FRAC(2,4), RGN_FRAC(1,4), RGN_FRAC(0,4) },
	{ 7, 6, 5, 4, 3, 2, 1, 0 },
	{ 8*0, 8*1, 8*2, 8*3, 8*4, 8*5, 8*6, 8*7 },
	8*8
};

static GfxLayout spritelayout =
{
	16,16,
	RGN_FRAC(1,4),
	4,
	{ RGN_FRAC(3,4), RGN_FRAC(2,4), RGN_FRAC(1,4), RGN_FRAC(0,4) },
	{ 7, 6, 5, 4, 3, 2, 1, 0,
	 15,14,13,12,11,10, 9, 8 },
	{ 0*16, 1*16, 2*16, 3*16, 4*16, 5*16, 6*16, 7*16,
	  8*16, 9*16,10*16,11*16,12*16,13*16,14*16,15*16 },
	16*16
};

static struct GFX_LIST pirates_gfx[] =
{
  { REGION_GFX1, &charlayout },
  { REGION_GFX2, &spritelayout },
  { 0,           NULL,           },
};

static void pirates_decrypt_68k(void)
{
    int rom_size;
    UINT8 *buf, *rom;
    int i;

    load_message(_("Decrypting 68K (Code)"));

    rom_size = get_region_size(REGION_CPU1);

    buf = malloc(rom_size);

    if (!buf) return;

    rom = load_region[REGION_CPU1];
    memcpy (buf, rom, rom_size);

    for (i=0; i<rom_size/2; i++)
    {
        int adrl, adrr;
        unsigned char vl, vr;

        adrl = BITSWAP24(i,23,22,21,20,19,18,4,8,3,14,2,15,17,0,9,13,10,5,16,7,12,6,1,11);
        vl = BITSWAP8(buf[adrl*2+1],    4,2,7,1,6,5,0,3);

        adrr = BITSWAP24(i,23,22,21,20,19,18,4,10,1,11,12,5,9,17,14,0,13,6,15,8,3,16,7,2);
        vr = BITSWAP8(buf[adrr*2], 1,4,7,0,3,5,6,2);

        rom[i*2] = vr;
        rom[i*2+1] = vl;
    }
    free (buf);
}

static void pirates_decrypt_p(void)
{
    int rom_size;
    UINT8 *buf, *rom;
    int i;

	load_message(_("Decrypting GFX1 (Tilemaps)"));

	rom_size = get_region_size(REGION_GFX1);

    buf = malloc(rom_size);

    if (!buf) return;

    rom = load_region[REGION_GFX1];
    memcpy (buf, rom, rom_size);

    for (i=0; i<rom_size/4; i++)
    {
		int adr = BITSWAP24(i,23,22,21,20,19,18,10,2,5,9,7,13,16,14,11,4,1,6,12,17,3,0,15,8);
		rom[adr+0*(rom_size/4)] = BITSWAP8(buf[i+0*(rom_size/4)], 2,3,4,0,7,5,1,6);
		rom[adr+1*(rom_size/4)] = BITSWAP8(buf[i+1*(rom_size/4)], 4,2,7,1,6,5,0,3);
		rom[adr+2*(rom_size/4)] = BITSWAP8(buf[i+2*(rom_size/4)], 1,4,7,0,3,5,6,2);
		rom[adr+3*(rom_size/4)] = BITSWAP8(buf[i+3*(rom_size/4)], 2,3,4,0,7,5,1,6);
    }
    free (buf);
}

static void pirates_decrypt_s(void)
{
    int rom_size;
    UINT8 *buf, *rom;
    int i;

	load_message(_("Decrypting GFX2 (Sprites)"));

    rom_size = get_region_size(REGION_GFX2);

    buf = malloc(rom_size);

    if (!buf) return;

    rom = load_region[REGION_GFX2];
    memcpy (buf, rom, rom_size);

    for (i=0; i<rom_size/4; i++)
    {
		int adr = BITSWAP24(i,23,22,21,20,19,18,17,5,12,14,8,3,0,7,9,16,4,2,6,11,13,1,10,15);
		rom[adr+0*(rom_size/4)] = BITSWAP8(buf[i+0*(rom_size/4)], 4,2,7,1,6,5,0,3);
		rom[adr+1*(rom_size/4)] = BITSWAP8(buf[i+1*(rom_size/4)], 1,4,7,0,3,5,6,2);
		rom[adr+2*(rom_size/4)] = BITSWAP8(buf[i+2*(rom_size/4)], 2,3,4,0,7,5,1,6);
		rom[adr+3*(rom_size/4)] = BITSWAP8(buf[i+3*(rom_size/4)], 4,2,7,1,6,5,0,3);
    }
    free (buf);
}

static void pirates_decrypt_oki(void)
{
    int rom_size;
    UINT8 *buf, *rom;
    int i;

    load_message(_("Decrypting OKI (Sound)"));

    rom_size = get_region_size(REGION_SOUND1);

    buf = malloc(rom_size);

    if (!buf) return;

    rom = load_region[REGION_SOUND1];
    memcpy (buf, rom, rom_size);

    for (i=0; i<rom_size; i++)
    {
		int adr = BITSWAP24(i,23,22,21,20,19,10,16,13,8,4,7,11,14,17,12,6,2,0,5,18,15,3,1,9);
		rom[adr] = BITSWAP8(buf[i], 2,3,4,0,7,5,1,6);
    }
    free (buf);
}



static UINT8* pirates_main_ram;
static UINT8* pirates_sprite_ram;
static UINT8* pirates_palette_ram;
static UINT8* pirates_tilemap_ram;
static UINT8  pirates_scroll[2];

static UINT8 pirates_system_readbyte(UINT32 offset)
{
  return (input_buffer[2]&0x0f)|0xe0|(EEPROM_read_bit() << 4); // also testswitch etc.
}

static UINT16 pirates_system_readword(UINT32 offset)
{
   return (pirates_system_readbyte(offset+0) << 8) |
          (pirates_system_readbyte(offset+1) << 0);
}

static void loadpirates_common(void)
{
  InitPaletteMap(pirates_palette_ram, 0x200, 0x10, 0x8000);
  set_colour_mapper(&col_map_xrrr_rrgg_gggb_bbbb);
  memset(input_buffer,0xff,3);

  ByteSwap(ROM,0x100000);

  AddMemFetch(0x000000, 0x0FFFFF, ROM);      // 68000 ROM
  AddMemFetch(-1, -1, NULL);
  AddReadByte(0x000000, 0x0FFFFF, NULL, ROM );                          	// 68000 ROM
  AddReadByte(0x100000, 0x10FFFF, NULL, pirates_main_ram);                // 68000 RAM
  AddReadBW(0x300000, 0x300001, NULL, input_buffer );        // inputs
  AddReadByte(0x400000, 0x400001, pirates_system_readbyte, NULL );        // test switch, eeprom, protection
  AddReadByte(0x500000, 0x5007FF, NULL, pirates_sprite_ram);              // Sprite RAM
  AddReadByte(0x800000, 0x803FFF, NULL, pirates_palette_ram);             // Palette RAM
  AddReadByte(0x900000, 0x907FFF, NULL, pirates_tilemap_ram);             // Tilemap RAM
  AddReadBW(0xa00000, 0xa00001, OKIM6295_status_0_r, NULL);             // Tilemap RAM
  AddWriteBW(0xa00000, 0xa00001, OKIM6295_data_0_w, NULL);             // Tilemap RAM

  AddReadByte(0x000000, 0xFFFFFF, DefBadReadByte, NULL);		// <Bad Reads>
  AddReadByte(-1, -1, NULL, NULL);

  AddReadWord(0x000000, 0x0FFFFF, NULL, ROM);                 			// 68000 ROM
  AddReadWord(0x100000, 0x10FFFF, NULL, pirates_main_ram);                // 68000 RAM

  // AddReadWord(0x300000, 0x300001, input_genix_readword, NULL );        // inputs
  AddReadWord(0x400000, 0x400001, pirates_system_readword, NULL );        // system

  AddReadWord(0x500000, 0x5007FF, NULL, pirates_sprite_ram);                 // 68000 RAM
  AddReadWord(0x800000, 0x803FFF, NULL, pirates_palette_ram);                 // 68000 RAM
  AddReadWord(0x900000, 0x907FFF, NULL, pirates_tilemap_ram);                 // 68000 RAM

  AddReadWord(0x000000, 0xFFFFFF, DefBadReadWord, NULL);		// <Bad Reads>
  AddReadWord(-1, -1,NULL, NULL);

  AddWriteByte(0x100000, 0x10FFFF, NULL, pirates_main_ram);                // 68000 RAM
  AddWriteByte(0x500000, 0x5007FF, NULL, pirates_sprite_ram);                // 68000 RAM
  AddWriteByte(0x700000, 0x700001, NULL, pirates_scroll);             // scroll
  AddWriteByte(0x800000, 0x803FFF, NULL, pirates_palette_ram);                // 68000 RAM
  AddWriteByte(0x900000, 0x907FFF, NULL, pirates_tilemap_ram);                // 68000 RAM
  AddWriteByte(0x000000, 0xFFFFFF, DefBadWriteByte, NULL);		// <Bad Writes>
  AddWriteByte(-1, -1, NULL, NULL);

  AddWriteWord(0x100000, 0x10FFFF, NULL, pirates_main_ram);                // 68000 RAM
  AddWriteWord(0x500000, 0x5007FF, NULL, pirates_sprite_ram);                // 68000 RAM
  AddWriteWord(0x700000, 0x700001, NULL, pirates_scroll);             // scroll
  AddWriteWord(0x800000, 0x803FFF, NULL, pirates_palette_ram);                // 68000 RAM
  AddWriteWord(0x900000, 0x907FFF, NULL, pirates_tilemap_ram);                // 68000 RAM
  AddWriteWord(0x600000, 0x600001, pirates_out_w, NULL); // eeprom, sound bank
  AddWriteWord(0x000000, 0xFFFFFF, DefBadWriteWord, NULL);		// <Bad Writes>

  AddWriteWord(-1, -1, NULL, NULL);

  AddInitMemory();     // Set Starscream mem pointers...
}

static UINT8 genix_prot_byte_r(UINT32 offset)
{
	switch (offset&3) // offset = complete address unlike MAME?
	{
	  //case 0: return 0x00;
		case 1: return 0x04;
		  //case 2: return 0x00;
		  //case 3: return 0x00;
	}
	return 0;
}

static UINT16 genix_prot_word_r(UINT32 offset)
{
   return (genix_prot_byte_r(offset+0) << 8) |
          (genix_prot_byte_r(offset+1) << 0);
}

static int layer_bg, layer_sprites,layer_text;

static void load_genix(void)
{
  RAMSize = 0x10000 + 0x800 + 0x4000 + 0x8000;
  layer_bg = add_layer_info(gettext("bg"));
  layer_sprites = add_layer_info(gettext("sprites"));
  layer_text = add_layer_info(gettext("text"));
  if(!(RAM=AllocateMem(RAMSize))) return;

  pirates_main_ram=RAM;
  pirates_sprite_ram=RAM + 0x10000;
  pirates_palette_ram=RAM + 0x10000 + 0x800;
  pirates_tilemap_ram=RAM + 0x10000 + 0x800 + 0x4000;

   /* decrypt 68k code */
  pirates_decrypt_68k();

  pirates_decrypt_p();

  /* load GFX2 into RAM */
  pirates_decrypt_s();

  pirates_decrypt_oki();

  // game specific crap

  /* patch out protection check (pirates) */
  if (!strcmp(current_game->main_name,"pirates")) {
    ROM[0x62c0] = 0x60; ROM[0x62c1] = 0x06;
  } else {
    // Genix
    AddReadByte(0x109e98, 0x109e9b, genix_prot_byte_r, NULL);
    AddReadWord(0x109e98, 0x109e9b, genix_prot_word_r, NULL);
  }

  loadpirates_common();

  EEPROM_init(&eeprom_interface);
  load_eeprom();

  init_tile_cache();
}

static void execute_genix(void)
{
   cpu_execute_cycles(CPU_68K_0, CPU_FRAME_MHz(17,60));  // should be 16mhz...
   cpu_interrupt(CPU_68K_0, 1);
}

static UINT16 other[65536];
static void Drawpirates(void)
{

  //	const struct GfxElement *gfx = Machine->gfx[1];
  data8_t *source = pirates_sprite_ram + 8;
  data8_t *finish = source + 0x800-8;
  UINT8 *map,*map1;
  int zz,zzz,x,y,scroll;
  UINT16 ta,ta2;

  ClearPaletteMap();
  // clear_game_screen(0);
  clear_tile_cache();


  /* there are the back tilemaps, these can actually be scrolled, genix uses scrolling, they appear to scroll together */

  scroll=-3+(pirates_scroll[0]>>3);

  if( check_layer_enabled(layer_bg)) {
      for(x=0;x<40;x++){
	  for(y=0;y<32;y++){
	      // int added = 0;
	      int sx,sy;
	      zz=0x2a80+(((x+scroll)*32)+y)*4;
	      zzz=0x1380+(((x+scroll)*32)+y)*4;

	      ta=ReadWord(&pirates_tilemap_ram[zz]);
	      ta2=ReadWord(&pirates_tilemap_ram[zzz]);
	      // if (gfx1_solid[ta]) {

	      MAP_PALETTE_MAPPED_NEW(
		      ((pirates_tilemap_ram[zz+2])&0x7f)+0x100,
		      16,
		      map1
		      );

	      sx = x*8+8-(pirates_scroll[0]&7); sy = y*8+16;
	      if ((tile_cache[ta]) && (cache_map[ta] == map1 && other[ta] == ta2)) {
		  Move8x8_Rot(tile_cache[ta],sx,sy,NULL);
		  continue;
	      } else {
		  Draw8x8_Mapped_Rot(&gfx1[ta<<6],sx,sy,map1);
	      }

	      if (gfx1_solid[ta2]) {
		  // if (added) fprintf(stderr,"%x %x\n",ta,ta2);
		  // if (added) tile_cache[ta] = NULL;
		  MAP_PALETTE_MAPPED_NEW(
			  ((pirates_tilemap_ram[zzz+2])&0x7f)+0x80,
			  16,
			  map
			  );

		  if (gfx1_solid[ta2] == 1) // some transp
		      Draw8x8_Trans_Mapped_Rot(&gfx1[ta2<<6],x*8+8-(pirates_scroll[0]&7),y*8+16,map);
		  else {
		      Draw8x8_Mapped_Rot(&gfx1[ta2<<6],x*8+8-(pirates_scroll[0]&7),y*8+16,map);
		      add_tile_cache_Rot(NULL,sx,sy,ta);
		      cache_map[ta] = map1;
		  }
		  other[ta] = ta2;
	      }
	      // }
	  }
      }
  } else
      clear_game_screen(0);

  /* sprites */

  if (check_layer_enabled(layer_sprites))
      while( source<finish )
      {
	  int xpos, ypos, flipxy, code, color;

	  xpos = ((source[3]<<8) | source[2]) - 32;
	  ypos = (source[-1]<<8)| source[-2];	// indeed...

	  if (ypos & 0x8000) break;	/* end-of-list marker */

	  code = ((source[5] <<8) | (source[4])) >> 2;
	  color =source[0] & 0x7f;
	  flipxy =source[4] & 3;

	  ypos = 0xf2 - ypos;

	  xpos += 32;ypos += 16;

	  // add if gfx solid code

	  if ((ypos>=0) && (ypos<224+64) && (xpos>=0) && (xpos<288+64))
	  {
	      if (gfx2_solid[code]) {
		  MAP_PALETTE_MAPPED_NEW(
			  color+0x180,
			  16,
			  map
			  );

		  switch (flipxy)
		  {

		  case 0: Draw16x16_Trans_Mapped_Rot(&gfx2[code<<8], xpos, ypos, map); break;
		  case 2: Draw16x16_Trans_Mapped_FlipY_Rot(&gfx2[code<<8], xpos, ypos, map); break;
		  case 1: Draw16x16_Trans_Mapped_FlipX_Rot(&gfx2[code<<8], xpos, ypos, map); break;
		  case 3: Draw16x16_Trans_Mapped_FlipXY_Rot(&gfx2[code<<8], xpos, ypos, map); break;
		  }
	      }
	  }

	  source+=8;
      }

/* this is the text tilemap */


  if (check_layer_enabled(layer_text))
      for(x=0;x<36;x++){
	  for(y=0;y<32;y++){

	      zz=0x180+(((x*32)+y)*4);

	      ta=ReadWord(&pirates_tilemap_ram[zz]);

	      if (gfx1_solid[ta]) {
		  MAP_PALETTE_MAPPED_NEW(
			  ((pirates_tilemap_ram[zz+3]<<8)|pirates_tilemap_ram[zz+2])&0x7f,
			  16,
			  map
			  );
		  if (gfx1_solid[ta] == 1) // some transp
		      Draw8x8_Trans_Mapped_Rot(&gfx1[ta<<6],x*8+32,y*8+16,map);
		  else
		      Draw8x8_Mapped_Rot(&gfx1[ta<<6],x*8+32,y*8+16,map);
	      }
	      // zz+=4;
	  }
      }
}



static struct VIDEO_INFO video_genix =
{
   Drawpirates,
   288,
   224,
   32, // this gets added to the edges, clip area
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
   pirates_gfx
};
static struct DIR_INFO dir_genix[] =
{
   { "genix", },
   { "genix_family", },
   { NULL, },
};
GME( genix, "Genix Family", NIX, 1994, GAME_SHOOT,
	.long_name_jpn = "ƒ[ƒƒ][ƒ“",
);
static struct DIR_INFO dir_pirates[] =
{
   { "pirates", },
   { "nix_pirates", },
   { NULL, },
};
CLNE( pirates, genix, "Pirates", NIX, 1994, GAME_SHOOT,
	.long_name_jpn = "ƒ[ƒƒ][ƒ“",
);

