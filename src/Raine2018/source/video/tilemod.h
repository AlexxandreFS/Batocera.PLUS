
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                               TILE MODIFIERS                               */
/*                                                                            */
/******************************************************************************/

#ifndef _tilemod_h_
#define _tilemod_h_

#include "deftypes.h"
#include "games.h"

/* So far, this type is only used in the about dialog !!! */
enum tile_type_num
{
   TILE_TYPE_UNKNOWN = 0,
   TILE_TYPE_8x8,
   TILE_TYPE_16x16,
   TILE_TYPE_32x32,
   TILE_TYPE_MAX,
};

extern char *tile_type[TILE_TYPE_MAX];
extern int max_tile_sprites;

typedef struct TILE_INFO
{
   UINT32 count;
   UINT32 type;
   UINT32 width;
   UINT32 height;
   UINT8 *data;
   UINT8 *mask;
   UINT32 rotate;
   UINT32 flip;
} TILE_INFO;

struct TILE_INFO tile_list[0x10];

extern UINT32 tile_list_count;

extern UINT8 tile_8x8_map[8 * 8];
extern UINT8 tile_16x16_map[16 * 16];

/*

Rotation by 90 degrees

*/

void Rotate8x8(UINT8 *source, UINT32 count);
void Rotate8x8_4bpp(UINT8 *source, UINT32 count);
void Rotate16x16(UINT8 *source, UINT32 count);

/*

Flip on X Axis

*/

void Flip8x8_X(UINT8 *source, UINT32 count);
void Flip8x8_4bpp_X(UINT8 *source, UINT32 count);
void Flip16x16_X(UINT8 *source, UINT32 count);

/*

Flip on Y Axis

*/

void Flip8x8_Y(UINT8 *source, UINT32 count);
void Flip16x16_Y(UINT8 *source, UINT32 count);

/*

Count Colour bits (for F3-System 64 colour tile check)

*/

void CountColours(UINT8 *source, UINT32 count);

/*

Make Tile Solid/Transparent map

*/

UINT8 *MakeSolidTileMap16x16(UINT8 *source, UINT32 count);
UINT8 *MakeSolidTileMap64x64(UINT8 *source, UINT32 count);
UINT8 *MakeSolidTileMap32x32(UINT8 *source, UINT32 count);

UINT8 *make_solid_mask_8x8(UINT8 *source, UINT32 count);
UINT8 *make_solid_mask_16x8(UINT8 *source, UINT32 count);
UINT8 *make_solid_mask_16x16(UINT8 *source, UINT32 count);
UINT8 *make_solid_mask_32x32(UINT8 *source, UINT32 count);
UINT8 *make_solid_mask_64x64(UINT8 *source, UINT32 count);

UINT8 *make_solid_mask_8x8_4bpp(UINT8 *source, UINT32 count);
UINT8 *make_solid_mask_16x16_4bpp(UINT8 *source, UINT32 count);
UINT8 *make_solid_mask_64x64_4bpp(UINT8 *source, UINT32 count);

UINT8 *make_solid_mask_pad_8x8(UINT8 *source, UINT32 count, UINT32 pad_size);
UINT8 *make_solid_mask_pad_16x16(UINT8 *source, UINT32 count, UINT32 pad_size);

UINT8 *make_solid_region_8x8(UINT32 region);
UINT8 *make_solid_region_16x16(UINT32 region);
UINT8 *make_solid_region_16x8(UINT32 region);

/*

generate used colour count map

*/

UINT8 *make_colour_count_16x16(UINT8 *source, UINT32 count);

UINT8 check_tile_solid(UINT8 *src, UINT32 size);
void check_tile_rotation(void);

UINT8 *decode_gfx(const UINT8 *src, const UINT32 src_size, const GFX_LAYOUT *gfx_layout,UINT32 *dest_size);

int get_mask(int v);

/*

convert real bpp -> internal bpp

 8 ->  8
15 -> 16
16 -> 16
24 -> 32
32 -> 32

*/

UINT32 internal_bpp(UINT32 source);

/* This function is to prepare a sprite of a new size in a different buffer */
/* Instead of a wx16 x hx16 sprite it produces wxh 16x16 sprites (working only on the
   width part in fact) */
static DEF_INLINE void make_tile_new(UINT32 num, UINT32 width,UINT8 *GFX_OBJ_A,UINT8 *GFX_OBJ_B,UINT8 *GFX_OBJ_SOLID,UINT8 *GFX_OBJ_SIZE)
{
   UINT32 x,y;
   UINT8 *src,*dst;

   src = GFX_OBJ_A + (num << 8);
   dst = GFX_OBJ_B + (num << 8);

   for(y = 0; y < (0x010 * 0x010); y += 0x010){
   for(x = 0; x < (width * 0x100); x += 0x100){

      dst[x + tile_16x16_map[y +  0]] = src[ 0];
      dst[x + tile_16x16_map[y +  1]] = src[ 1];
      dst[x + tile_16x16_map[y +  2]] = src[ 2];
      dst[x + tile_16x16_map[y +  3]] = src[ 3];
      dst[x + tile_16x16_map[y +  4]] = src[ 4];
      dst[x + tile_16x16_map[y +  5]] = src[ 5];
      dst[x + tile_16x16_map[y +  6]] = src[ 6];
      dst[x + tile_16x16_map[y +  7]] = src[ 7];
      dst[x + tile_16x16_map[y +  8]] = src[ 8];
      dst[x + tile_16x16_map[y +  9]] = src[ 9];
      dst[x + tile_16x16_map[y + 10]] = src[10];
      dst[x + tile_16x16_map[y + 11]] = src[11];
      dst[x + tile_16x16_map[y + 12]] = src[12];
      dst[x + tile_16x16_map[y + 13]] = src[13];
      dst[x + tile_16x16_map[y + 14]] = src[14];
      dst[x + tile_16x16_map[y + 15]] = src[15];

      src += 16;

   }
   }

   for(x = 0; x < width; x ++){
      GFX_OBJ_SIZE[num + x] = width;
      GFX_OBJ_SOLID[num + x] = check_tile_solid(GFX_OBJ_B + ((num + x) << 8), 0x100);
   }

}

#endif //_tilemod_h_

#ifdef __cplusplus
}
#endif
