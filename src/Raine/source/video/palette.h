
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                           RAINE COLOUR MAPPING                             */
/*                                                                            */
/******************************************************************************/

#ifndef _palette_h_
#define _palette_h_

#include "deftypes.h"

  /* Colors are now supposed to be on 8 bits in raine (work in progress) */

#ifdef SDL

#include "sdl/compat.h"

#define GET_PEN_FOR_COLOUR_15(red, green, blue, result, ...) \
      result = SDL_MapRGB(color_format, red, green, blue)

#define makecol15(r,g,b) SDL_MapRGB(color_format, r, g, b)
#define makecol16(r,g,b) SDL_MapRGB(color_format, r, g, b)
#define makecol32(r,g,b) SDL_MapRGB(color_format, r, g, b)
#define makecol(r,g,b) SDL_MapRGB(color_format, r, g, b)

  // sdl does not make any distinction after this (everything is in pixelformat)
#define GET_PEN_FOR_COLOUR_16 GET_PEN_FOR_COLOUR_15
#define GET_PEN_FOR_COLOUR_24 GET_PEN_FOR_COLOUR_15
#define GET_PEN_FOR_COLOUR_32 GET_PEN_FOR_COLOUR_15

#else

  // Allegro version

#define GET_PEN_FOR_COLOUR_15(red, green, blue, result, ...)  \
      result = makecol15((red), (green), (blue));
// (((red) << 9) | ((green) << 4) | ((blue) >> 1)) & 0x7FFF;

#define GET_PEN_FOR_COLOUR_16(red, green, blue, result, ...) \
      result = makecol16((red), (green), (blue));
//(((red) << 10) | ((green) << 5) | ((blue) >> 1)) & 0xFFFF;

// 24 bits colors are not used anymore
#define GET_PEN_FOR_COLOUR_24(red, green, blue, result, ...)  \
      result = (((blue) << 18) | ((green) << 10) | ((red) << 2)) & 0xFFFFFF;

// the 32 bit version didn't care about rgb order, makecol does.
#define GET_PEN_FOR_COLOUR_32(red, green, blue, result, ... ) \
      result = makecol32((red),(green),(blue));

#endif

extern PALETTE pal;			// 256 Colour palette for the game
extern UINT8 *RAM_PAL;

typedef void CMAP_FUNC(UINT32 bank, UINT32 cols);

typedef struct COLOUR_MAPPER
{
   char     *name;
   CMAP_FUNC *mapper_8bpp;
   CMAP_FUNC *mapper_15bpp;
   CMAP_FUNC *mapper_16bpp;
   CMAP_FUNC *mapper_24bpp;
   CMAP_FUNC *mapper_32bpp;
} COLOUR_MAPPER;

extern CMAP_FUNC *current_cmap_func;
extern COLOUR_MAPPER *current_colour_mapper;

/*

16 bit source

*/

extern struct COLOUR_MAPPER col_map_xxxxRrrgggbbb;
extern struct COLOUR_MAPPER col_map_xxxx_rrrr_gggg_bbbb;
extern struct COLOUR_MAPPER col_map_nnnn_rrrr_gggg_bbbb_cps1;
extern struct COLOUR_MAPPER col_map_nnnn_rrrr_gggg_bbbb_cps2;
extern struct COLOUR_MAPPER col_map_xxxx_bbbb_gggg_rrrr;
extern struct COLOUR_MAPPER col_map_xxxx_bbbb_gggg_rrrr_rev;
extern struct COLOUR_MAPPER col_map_xrrr_rrgg_gggb_bbbb;
extern struct COLOUR_MAPPER col_map_rrrr_gggg_bbbb_xxxx;
extern struct COLOUR_MAPPER col_map_xggg_ggrr_rrrb_bbbb;
extern struct COLOUR_MAPPER col_map_xbbb_bbgg_gggr_rrrr;
extern struct COLOUR_MAPPER col_map_xxbb_bbxg_gggx_rrrr;
extern struct COLOUR_MAPPER col_map_rrrr_gggg_bbbb_rgbx_rev;
extern struct COLOUR_MAPPER col_map_rrrr_rggg_ggbb_bbbx_rev;
extern struct COLOUR_MAPPER col_map_xrrr_rrgg_gggb_bbbb_rev_68k;
extern struct COLOUR_MAPPER col_map_xrrr_rrgg_gggb_bbbb_68k;
extern struct COLOUR_MAPPER col_map_12bit_rgbxxxx; // arabianm...
extern struct COLOUR_MAPPER col_map_21bit_xRGB;
extern struct COLOUR_MAPPER col_Map_15bit_RRRRGGGGBBBBRGBx;
extern struct COLOUR_MAPPER col_Map_15bit_xRGBRRRRGGGGBBBB;
extern struct COLOUR_MAPPER col_map_15bit_grbx;
extern struct COLOUR_MAPPER col_map_rrrr_gggg_xxxx_bbbb;
extern struct COLOUR_MAPPER col_map_12bit_xxxxRRRRGGGGBBBB_Rev;
extern struct COLOUR_MAPPER col_map_rrrr_gggg_bbbb_xxxx_68k;

/*

32 bit source

*/

extern struct COLOUR_MAPPER col_map_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx;
extern struct COLOUR_MAPPER col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb;
extern struct COLOUR_MAPPER col_map_24bit_rgb;

void set_colour_mapper(COLOUR_MAPPER *colour_mapper);

#define MAX_COLBANKS	0x200

/*-----[Init Section]-----*/

// Call this to setup colour mapping (eg. during load game)

void InitPaletteMap(UINT8 *src, int banks, int bankcols, int mapsize);
void ResetPalette(); // Reinit palette when changing color mapper

/*

In the rare case that colour 255 is used and cannot be white
(eg. direct mapped, american horseshoes - the man on a bike)

*/

void set_white_pen(int pen);

/*

Used by the ingame gui, to get the white pen (nearly always 255)

*/

UINT32 get_white_pen(void);

// Call this to remove resources (eg. in clear default)

void destroy_palette_map(void);

// Call this at the start of each screen redraw

void ClearPaletteMap(void);

// Call this to clear caches (eg. when coming back into game from gui)

void reset_palette_map(void);

// Call this to permanently allocate some pens

int Reserve_Pens(int num);

void silly_wgp_colour_ram(UINT8 *src);

// Call these to change permanently allocated pen colours

void Set_Pens_15bit_xRGB(int talc, int start, int cols);

/*-----[Macro Section]-----*/

extern UINT16 bank_status[MAX_COLBANKS];
extern UINT8 *coltab[MAX_COLBANKS];

// MAP_PALETTE_MAPPED(mapper, bank, cols, dst)

#define MAP_PALETTE_MAPPED(mapper,bank,cols,dst) \
   dst=coltab[bank];                             \
   if(bank_status[bank] == 0)                    \
      mapper(bank, cols);                        \

// MAP_PALETTE_MAPPED_NEW(mapper, bank, cols, dst)

#define MAP_PALETTE_MAPPED_NEW(bank,cols,dst) \
   dst = coltab[bank];                        \
   if(bank_status[bank] == 0)                 \
      current_cmap_func(bank, cols);          \

#define MAP_PAL MAP_PALETTE_MAPPED_NEW

// MAP_PALETTE_MULTI_MAPPED(mapper, bank, cols, dst)

#define MAP_PALETTE_MULTI_MAPPED(mapper,bank,cols,dst) \
   dst=coltab[bank];                                   \
   if(bank_status[bank] < cols)                        \
      mapper(bank, cols);                              \

// MAP_PALETTE_MULTI_MAPPED_NEW(mapper, bank, cols, dst)

#define MAP_PALETTE_MULTI_MAPPED_NEW(bank,cols,dst) \
   dst = coltab[bank];                              \
   if(bank_status[bank] < cols)                     \
      current_cmap_func(bank, cols);                \

// MAP_PALETTE(mapper, bank, cols)

#define MAP_PALETTE(mapper,bank,cols) \
   coltab[bank];                      \
   if(bank_status[bank] == 0)         \
      mapper(bank, cols);             \

// MAP_PALETTE_2BPP(mapper, bank, cols)

#define MAP_PALETTE_2BPP(mapper,bank,cols)        \
   coltab[bank>>2]+((bank&3)<<2);                 \
   if((bank_status[bank>>2]&(1<<(bank&3))) == 0)  \
      mapper(bank, cols);                         \

/*-----[Macro Mappers]-----*/

void Map_12bit_RGBx(int bank, int cols);
void Map_12bit_RGBx_68k(int bank, int cols);

void Map_12bit_xRGB(int bank, int cols);

void Map_12bit_xBGR_Rev_2BPP(int bank, int cols);

void Map_15bit_xRGB(int bank, int cols);
void Map_15bit_xBGR(int bank, int cols);

// F3-System

void Map_12bit_RGBxxxxx(int bank, int cols);

void Map_24bit_xRGB(int bank, int cols);

#endif // _palette_h_

#ifdef __cplusplus
}
#endif
