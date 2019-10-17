
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                            LOAD ROMS FROM ROM_INFO                         */
/*                                                                            */
/******************************************************************************/

#ifndef __loadroms_h_
#define __loadroms_h_

#include "deftypes.h"

/*

GFX LAYOUT

*/

#define REGION_EMPTY "REGION EMPTY"

#define MAX_GFX_PLANES   (8)
#define MAX_GFX_SIZE     (64)

#define RGN_FRAC(num,den)   (0x80000000 | (((num) & 0x0f) << 27) | (((den) & 0x0f) << 23))
#define IS_FRAC(offset)     ((offset) & 0x80000000)
#define FRAC_NUM(offset)    (((offset) >> 27) & 0x0f)
#define FRAC_DEN(offset)    (((offset) >> 23) & 0x0f)
#define FRAC_OFFSET(offset) ((offset) & 0x007fffff)

#define STEP4(START,STEP)   (START), (START)+1*(STEP), (START)+2*(STEP), (START)+3*(STEP)
#define STEP8(START,STEP)   STEP4(START,STEP), STEP4((START)+4*(STEP), STEP)
#define STEP16(START,STEP)  STEP8(START,STEP), STEP8((START)+8*(STEP), STEP)

// Load Error Report

#define LOAD_FATAL_ERROR (0x0001)
#define LOAD_WARNING	 (0x0002)

typedef struct GFX_LAYOUT
{
   UINT16 width,height;                // width and height (in pixels) of chars/sprites
   UINT32 total;                       // total numer of chars/sprites in the rom
   UINT16 planes;                      // number of bitplanes
   UINT32 planeoffset[MAX_GFX_PLANES]; // start of every bitplane (in bits)
   UINT32 xoffset[MAX_GFX_SIZE];       // position of the bit corresponding to the pixel
   UINT32 yoffset[MAX_GFX_SIZE];       // of the given coordinates
   UINT16 charincrement;               // distance between two consecutive characters/sprites (in bits)
} gfx_layout;

#define GFX_LAYOUT gfx_layout

// mame compatibility
#define GfxLayout GFX_LAYOUT

typedef struct GFX_LIST
{
   UINT32       region;
   gfx_layout *layout;
} GFX_LIST;

enum region_type
{
   REGION_NONE = 0,
   REGION_ROM1,
   REGION_ROM2,
   REGION_ROM3,
   REGION_ROM4,
   REGION_GFX1,
   REGION_GFX2,
   REGION_GFX3,
   REGION_GFX4,
   REGION_GFX5,
   REGION_SMP1,
   REGION_SMP2,
   REGION_SMP3,
   REGION_SMP4,
   REGION_PROMS,
   REGION_USER1,
   REGION_USER2,
   REGION_FIXED,
   REGION_FIXEDBIOS,
   REGION_ZOOMY,
   REGION_YMSND_DELTAT,
   REGION_SPRITES,
   REGION_MAINBIOS,
   REGION_AUDIOCRYPT,
   REGION_MAX,
};

// mame compatibility
#define REGION_CPU1 REGION_ROM1
#define REGION_CPU2 REGION_ROM2
#define REGION_CPU3 REGION_ROM3
#define REGION_CPU4 REGION_ROM4

#define REGION_SOUND1 REGION_SMP1
#define REGION_SOUND2 REGION_SMP2
#define REGION_SOUND3 REGION_SMP3
#define REGION_SOUND4 REGION_SMP4

#define REG(x) load_region[REGION_##x]

enum region_flags
{
   LOAD_NORMAL = 0,

   // Rom loading
   LOAD_8_16,
   LOAD_8_32,
   LOAD_8_64,
   LOAD_16_32,
   LOAD_16_64,
   LOAD_BE,
   LOAD32_SWAP_16,

   // sprites
   LOAD_SWAP_16,
   LOAD8X8_16X16,
   LOAD_8_16S, // 8_16 for sprites (without GfxLayout)

   LOAD_CONTINUE,
   LOAD_IGNORE,
   LOAD_FILL,
};

#define LOAD8_16(region, offset, size, rom1, crc1, rom2, crc2) \
{ rom1, size, crc1, region, offset, LOAD_8_16 }, \
{ rom2, size, crc2, region, offset+1, LOAD_8_16 }

#define LOAD8_16S(region, offset, size, rom1, crc1, rom2, crc2) \
{ rom1, size, crc1, region, offset, LOAD_8_16S }, \
{ rom2, size, crc2, region, offset+1, LOAD_8_16S }

#define LOAD16_64(region, offset, size, rom1, crc1, rom2, crc2, \
		rom3, crc3, rom4, crc4) \
{ rom1, size, crc1, region, offset, LOAD_16_64 }, \
{ rom2, size, crc2, region, offset+2, LOAD_16_64 }, \
{ rom3, size, crc3, region, offset+4, LOAD_16_64 }, \
{ rom4, size, crc4, region, offset+6, LOAD_16_64 } \

#define FILL(offset, size, content, region) \
{ "", size, content, REGION_##region, offset, LOAD_FILL }

typedef struct ROM_INFO
{
   char *name;                 // file name
   UINT32  size;                 // file size
   UINT32  crc32;                // file crc32
   UINT16  region;               // rom region (optional)
   UINT32  offset;               // offset within rom region (optional)
   UINT16  flags;                // loading flags (optional)
} ROM_INFO;

typedef struct DIR_INFO
{
   char *maindir;              // directory name
} DIR_INFO;

extern UINT8 *load_region[REGION_MAX];
#define MAX_GFX 16 // more than enough !
extern UINT8 *gfx[MAX_GFX], *gfx_solid[MAX_GFX];
extern UINT8 *gfx1, *gfx2, *gfx3;
extern UINT8 *gfx1_solid, *gfx2_solid, *gfx3_solid;
extern int max_sprites[MAX_GFX];
extern int load_error;
extern char *load_debug;

/*

search for any alternative file names that a rom could have. this uses the
romlist data for any 'romof' games, if a rom matches on crc32 and size, we
assume it is a match.

*/

extern char *alt_names[8]; // used by config.c too... !!!
UINT32 find_alternative_file_names(const ROM_INFO *rom_info, const DIR_INFO *dir_list);

UINT32 get_region_size(UINT32 region);
char *get_region_name(int reg);

void load_game_rom_info(void);
// used to decode a region after manipulating it in the loading function
void decode_region(UINT32 region, const GFX_LAYOUT *gfx_layout);

int load_rom(char *rom, UINT8 *dest, UINT32 size);

int load_be(char *name, UINT8 *ROM, int size);
int load_rom_8_16(char *rom, UINT8 *dest, UINT32 size);
int load_rom_8_32(char *rom, UINT8 *dest, UINT32 size);
int load_rom_8_64(char *rom, UINT8 *dest, UINT32 size);
int load_rom_16_32(char *rom, UINT8 *dest, UINT32 size);
int load_rom_16_64(char *rom, UINT8 *dest, UINT32 size);
int load32_swap_16(char *rom, UINT8 *dest, UINT32 size);

int load_rom_swap_16(char *rom, UINT8 *dest, UINT32 size);
void convert_8x8_16x16(UINT8* src, UINT8* dst, UINT32 len);
int load_rom_8x8_16x16(char *rom, UINT8 *dst, UINT32 len);


int load_rom_index(UINT32 num, UINT8 *dest, UINT32 size);

int load_rom_dir(const DIR_INFO *dir_list, char *rom, UINT8 *dest, UINT32 size, UINT32 crc32,int actual_load);

int rom_size_dir(const DIR_INFO *dir_list, char *rom, UINT32 size, UINT32 crc32);
void load_message(char *);

// unpacking sprites (2 x 4 bits -> 1 byte)
void unpack_region_lsb(UINT32 region);
void set_region_size(UINT32 region, UINT32 size);
void clear_regions();

#endif // __loadroms_h_

#ifdef __cplusplus
}
#endif
