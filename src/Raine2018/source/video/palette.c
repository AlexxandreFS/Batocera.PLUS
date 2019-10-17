/******************************************************************************/
/*                                                                            */
/*                          RAINE COLOUR MAPPING                              */
/*                                                                            */
/******************************************************************************/
/*
Warning : the yy variable in the color mappers is used for 8bpp conversion.
So when you see yy = something & 0x7fff, leave the '& 0x7fff" where it is
even if it seems useless in 16bp (it allows to map directly color numbers
from rgb values of the color).
*/

#include <limits.h>
#include "raine.h"
#include "gameinc.h"
#include "palette.h"
#include "blitasm.h"
#include "profile.h"

PALETTE pal;			// 256 Colour palette for the game
CMAP_FUNC *current_cmap_func;
COLOUR_MAPPER *current_colour_mapper;
UINT16 bank_status[MAX_COLBANKS];
UINT8 *coltab[MAX_COLBANKS];

/*

Closest Colour finder (when there are no free pens)

*/

static void closest_colour_init(void);
static UINT8 closest_colour(int r, int g, int b);

/*

Data

*/

enum map_type
{
   PMAP_NONE = 0,
   PMAP_MAPPED,
   PMAP_DIRECT,
};

static UINT8 map_mode = PMAP_NONE;

UINT8 *RAM_PAL;		// points to source colour ram

static UINT8 *colour_ram_src[MAX_COLBANKS];

static UINT8 *bankmap;
static UINT8 *cloc;

static UINT32 res_pens;		// number of pens reserved in the palette (0-255)
static UINT32 talc;		// next free pen in the palette (0-255)

static UINT8 *cloc_2;		// cloc data from last frame
static UINT8 *pmap;		// list of which pens are allocated (0=free 1=used)
static UINT8 *pmap_2;		// pmap data from last frame
static UINT16 pal_banks;		// number of colour banks the hardware supports
static UINT32 map_size;
static UINT32 bank_cols;

#ifdef TRIPLE_BUFFER
static UINT8 *cloc_2a;		// extra buffer
static UINT8 *pmap_2a;		// extra buffer
#else
#define cloc_2a	cloc_2
#define pmap_2a	pmap_2
#endif

PALETTE pal_screen;

static UINT8 white_pen;

// mapsize is the size of the buffer taken to make conversions to 8bits colors
void InitPaletteMap(UINT8 *src, int banks, int bankcols, int mapsize)
{
   int ta;
   int bmsize;
   map_mode = PMAP_MAPPED;

   RAM_PAL = src;

   pal_banks = banks;
   bank_cols = bankcols;
   map_size  = mapsize;

   bmsize = pal_banks * bankcols * (internal_bpp(display_cfg.bpp) / 8);
   if (!(bankmap = AllocateMem(bmsize ))) return;
   memset(bankmap,0,bmsize); // For MAP_PALETTE_MULTI...

   if (!(cloc    = AllocateMem(map_size))) return;
   if (!(cloc_2  = AllocateMem(map_size))) return;
#ifdef TRIPLE_BUFFER
   if (!(cloc_2a = AllocateMem(map_size))) return;
#endif
   if (!(pmap    = AllocateMem(256))) return;
   if (!(pmap_2  = AllocateMem(256))) return;
   memset(pmap,0,256);
   memset(pmap_2,0,256);

#ifdef TRIPLE_BUFFER
   if (!(pmap_2a = AllocateMem(256))) return;
#endif
   memset(pmap_2a,0,256);
   for(ta=0; ta<pal_banks; ta++){
      coltab[ta] = bankmap + (ta * bankcols * (internal_bpp(display_cfg.bpp) / 8));
      colour_ram_src[ta] = src + (ta * bankcols * 2);
   }

   res_pens = 1;	// 1 reserved (pen 0 == black)

   white_pen = 255;

   closest_colour_init();

   reset_palette_map();
}

void ResetPalette() {
   if (cloc) FreeMem(cloc);
   if (cloc_2) FreeMem(cloc_2);
   if (bankmap) FreeMem(bankmap);
#ifdef TRIPLE_BUFFER
   if (cloc_2a) FreeMem(cloc_2a);
#endif
   if (pmap)   FreeMem(pmap);
   if (pmap_2) FreeMem(pmap_2);
#ifdef TRIPLE_BUFFER
   if (pmap_2a) FreeMem(pmap_2a);
#endif
   InitPaletteMap(RAM_PAL,pal_banks,bank_cols,map_size);
}

void set_colour_mapper(COLOUR_MAPPER *colour_mapper)
{
   current_colour_mapper = colour_mapper;

   switch(display_cfg.bpp){
      case 8:
         current_cmap_func = current_colour_mapper->mapper_8bpp;
      break;
      case 15:
         current_cmap_func = current_colour_mapper->mapper_15bpp;
      break;
      case 16:
         current_cmap_func = current_colour_mapper->mapper_16bpp;
      break;
      case 24:
         current_cmap_func = current_colour_mapper->mapper_24bpp;
      break;
      case 32:
         current_cmap_func = current_colour_mapper->mapper_32bpp;
      break;
      default:
         current_cmap_func = current_colour_mapper->mapper_8bpp;
      break;
   }
}

void set_white_pen(int pen)
{
   white_pen = pen;
}

UINT32 get_white_pen(void)
{
    if (display_cfg.bpp > 8)
	return makecol(255,255,255);

    pal[white_pen].r = 255;
    pal[white_pen].g = 255;
    pal[white_pen].b = 255;

    return white_pen;
}

int Reserve_Pens(int num)
{
   int ret;

   ret = res_pens;
   res_pens += num;

   return ret;
}

void Set_Pens_15bit_xRGB(int talc, int start, int cols)
{
   UINT16 yy;
   UINT16 *ta;

   ta = (UINT16 *) (RAM_PAL+(start<<1));
   do{
      yy = (*ta++) & 0x7FFF;
      pal[talc].r = (yy&0x7C00)>>7;
      pal[talc].g = (yy&0x03E0)>>4;
      pal[talc].b = (yy&0x001F)<<1;
      talc++;
   }while(--cols);
}

void ClearPaletteMap(void)
{
   UINT8 *ta;

   switch(map_mode){
   case PMAP_MAPPED:

#ifdef TRIPLE_BUFFER

   ta      = cloc_2;
   cloc_2  = cloc_2a;		// cloc_2  = <last-last frame map>
   cloc_2a = cloc;		// cloc_2a = <last frame map>
   cloc    = ta;		// cloc    = <new frame map>

   ta      = pmap_2;
   pmap_2  = pmap_2a;		// pmap_2  = <last-last frame map>
   pmap_2a = pmap;		// pmap_2a = <last frame map>
   pmap    = ta;		// pmap    = <new frame map>

#else
   ta     = cloc_2;
   cloc_2 = cloc;		// cloc_2 = <last frame map>
   cloc   = ta;			// cloc   = <new frame map>

   ta     = pmap_2;
   pmap_2 = pmap;		// pmap_2 = <last frame map>
   pmap   = ta;			// pmap   = <new frame map>
#endif

   memset(bank_status, 0, pal_banks * 2);
   memset(cloc, 0xFF, map_size);
   memset(pmap, 0x00, 256);

   // pen 0 is always black

   cloc[0] = 0;
   pal[0].r = 0;
   pal[0].g = 0;
   pal[0].b = 0;

   // Find first free pen

   talc = res_pens;

#ifdef TRIPLE_BUFFER
   while((pmap_2[talc])||(pmap_2a[talc])){ talc++; }
#else
   talc --;
   while(pmap_2[++talc]);
#endif
   break;
   case PMAP_DIRECT:
   break;
   default:

   break;
   }
}

void reset_palette_map(void)
{
   switch(map_mode){
   case PMAP_MAPPED:
      ClearPaletteMap();		// Make sure no colours are cached
      ClearPaletteMap();
#ifdef TRIPLE_BUFFER
      ClearPaletteMap();
#endif
   break;
   case PMAP_DIRECT:
   break;
   default:

   break;
   }

   memset(pal       , 0x00, sizeof(PALETTE));
   memset(pal_screen, 0xFF, sizeof(PALETTE));
}

void destroy_palette_map(void)
{
   map_mode = PMAP_NONE;
}

void silly_wgp_colour_ram(UINT8 *src)
{
   RAM_PAL = src;
}

// Allegro never found weird to use 0-63 colors values for 8bpp and 0-255 for other depths!
#ifdef SDL
// We could use sdl_maprgb here, but it would force us to really maintain the sdl_palette
// (clear it for each frame), and at the same time the conversion in raine works rather well
// wo why bother ?
#define GET_PEN_FOR_COLOUR_8(red, green, blue, result)                       \
      if(cloc_2a[yy] == 255){                                                \
         if(talc < 255){                                                     \
            result = cloc_2a[yy] = cloc[yy] = talc;                          \
            pal[talc].r = red;                                               \
            pal[talc].g = green;                                             \
            pal[talc].b = blue;                                              \
            talc++;                                                          \
            while((pmap_2[talc])||(pmap_2a[talc])){ talc++; }                \
         }                                                                   \
         else{				                                     \
            result = closest_colour(red, green, blue);                       \
         }                                                                   \
      }                                                                      \
      else{                                                                  \
         result = cloc[yy] = cloc_2a[yy];                                    \
      }                                                                      \
      pmap[result] = 1;

#else
#define GET_PEN_FOR_COLOUR_8(red, green, blue, result)			\
      if(cloc_2a[yy] == 255){						\
         if(talc < 255){						\
            result = cloc_2a[yy] = cloc[yy] = talc;			\
            pal[talc].r = (red)>>2;					\
            pal[talc].g = (green)>>2;					\
            pal[talc].b = (blue)>>2;					\
            talc++;							\
            while((pmap_2[talc])||(pmap_2a[talc])){ talc++; }		\
         }								\
         else{								\
            result = closest_colour((red)>>2, (green)>>2, (blue)>>2);	\
         }								\
      }									\
      else{								\
         result = cloc[yy] = cloc_2a[yy];				\
      }									\
      pmap[result] = 1;
#endif

/******************************************************************************/
/* 12-bit xBGR (12-bit mapping)                                               */
/******************************************************************************/

void Map_12bit_xRGB(int bank, int cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x0FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_xxxx_rrrr_gggg_bbbb_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x0FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_xxxx_rrrr_gggg_bbbb_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x0FFF;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_xxxx_rrrr_gggg_bbbb_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x0FFF;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_xxxx_rrrr_gggg_bbbb_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x0FFF;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_xxxx_rrrr_gggg_bbbb_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x0FFF;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_xxxx_rrrr_gggg_bbbb =
{
   "12bit xxxx rrrr gggg bbbb",
   map_12bit_xxxx_rrrr_gggg_bbbb_8,
   map_12bit_xxxx_rrrr_gggg_bbbb_15,
   map_12bit_xxxx_rrrr_gggg_bbbb_16,
   map_12bit_xxxx_rrrr_gggg_bbbb_24,
   map_12bit_xxxx_rrrr_gggg_bbbb_32,
};

#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT16 yy, bright;				\
   UINT16 *ta;					\
   TYPE *ct,res;				\
   UINT8 red,green,blue;			\
						\
   bank_status[bank] = cols;			\
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);	\
   ct = (TYPE *)coltab[bank];			\
   do{						\
      yy = (*ta--);				\
      bright = (yy >> 12);			\
      if (bright) bright += 2;			\
						\
      red = (((yy&0x0F00)>>8) * bright);	\
      green = (((yy&0x00F0)>>4) * bright);	\
      blue = (((yy&0x000F)<<0) * bright);	\
						\
      PEN_FUNC(					\
			   red,green,blue,	\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
   }while(--cols);				\
}

BUILD_MAPPER(map_12bit_nnnn_rrrr_gggg_bbbb_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(map_12bit_nnnn_rrrr_gggg_bbbb_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(map_12bit_nnnn_rrrr_gggg_bbbb_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(map_12bit_nnnn_rrrr_gggg_bbbb_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(map_12bit_nnnn_rrrr_gggg_bbbb_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_nnnn_rrrr_gggg_bbbb_cps1 =
{
   "12bit nnnn rrrr gggg bbbb_cps1",
   map_12bit_nnnn_rrrr_gggg_bbbb_8,
   map_12bit_nnnn_rrrr_gggg_bbbb_15,
   map_12bit_nnnn_rrrr_gggg_bbbb_16,
   map_12bit_nnnn_rrrr_gggg_bbbb_24,
   map_12bit_nnnn_rrrr_gggg_bbbb_32,
};

// cps2 : the only difference is in the bright coefficient...

#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)			\
void NAME(UINT32 bank, UINT32 cols)				\
{								\
   UINT16 yy, bright;						\
   UINT16 *ta;							\
   TYPE *ct,res;						\
   UINT8 red,green,blue;					\
								\
   bank_status[bank] = cols;					\
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);			\
   ct = (TYPE *)coltab[bank];					\
   do{								\
      yy = (*ta--);						\
      bright = (yy >> 12)+16;					\
								\
      red = (((yy&0x0F00)>>8) * bright * 0x11 / 0x1f);		\
      green = (((yy&0x00F0)>>4) * bright * 0x11 / 0x1f);	\
      blue = (((yy&0x000F)<<0) * bright * 0x11 / 0x1f);		\
								\
      PEN_FUNC(							\
			   red,green,blue,			\
         res							\
      );							\
								\
      *ct++ = res;						\
								\
   }while(--cols);						\
}

BUILD_MAPPER(map_12bit_nnnn_cps2_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(map_12bit_nnnn_cps2_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(map_12bit_nnnn_cps2_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(map_12bit_nnnn_cps2_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(map_12bit_nnnn_cps2_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_nnnn_rrrr_gggg_bbbb_cps2 =
{
   "12bit nnnn cps2",
   map_12bit_nnnn_cps2_8,
   map_12bit_nnnn_cps2_15,
   map_12bit_nnnn_cps2_16,
   map_12bit_nnnn_cps2_24,
   map_12bit_nnnn_cps2_32,
};

// Map_12bit_xxxxRRRRGGGGBBBB_Rev

#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT16 yy;					\
   UINT16 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);	\
   ct = (TYPE*)coltab[bank];			\
   do{						\
      yy = (*ta--) & 0x0FFF;			\
						\
      PEN_FUNC(					\
         (yy&0x0F00)>>4,			\
         (yy&0x00F0),			\
         (yy&0x000F)<<4,			\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
   }while(--cols);				\
}

BUILD_MAPPER(Map_12bit_xxxxRRRRGGGGBBBB_Rev_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(Map_12bit_xxxxRRRRGGGGBBBB_Rev_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(Map_12bit_xxxxRRRRGGGGBBBB_Rev_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(Map_12bit_xxxxRRRRGGGGBBBB_Rev_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(Map_12bit_xxxxRRRRGGGGBBBB_Rev_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_12bit_xxxxRRRRGGGGBBBB_Rev =
{
   "12bit xxxx rrrr gggg bbbb [Rev]",
   Map_12bit_xxxxRRRRGGGGBBBB_Rev_8,
   Map_12bit_xxxxRRRRGGGGBBBB_Rev_15,
   Map_12bit_xxxxRRRRGGGGBBBB_Rev_16,
   Map_12bit_xxxxRRRRGGGGBBBB_Rev_24,
   Map_12bit_xxxxRRRRGGGGBBBB_Rev_32,
};

// map rrr_ggg_bbb (9 bits -> 512 couleurs) (pengo)
#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)		\
void NAME(UINT32 bank, UINT32 cols)			\
{							\
   UINT16 yy;						\
   UINT16 *ta;						\
   TYPE *ct,res;					\
							\
   bank_status[bank] = cols;				\
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));	\
   ct = (TYPE*)coltab[bank];				\
   do{							\
      yy = (*ta++) & 0x01FF;				\
							\
      PEN_FUNC(						\
         (yy&0x01c0)>>1,				\
         (yy&0x0038)<<2,					\
         (yy&0x0007)<<5,				\
         res						\
      );						\
							\
      *ct++ = res;					\
							\
   }while(--cols);					\
}

BUILD_MAPPER(Map_xxxxRrrgggbbb_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(Map_xxxxRrrgggbbb_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(Map_xxxxRrrgggbbb_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(Map_xxxxRrrgggbbb_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(Map_xxxxRrrgggbbb_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_xxxxRrrgggbbb =
{
   "8bit xxxx rrr ggg bbb",
   Map_xxxxRrrgggbbb_8,
   Map_xxxxRrrgggbbb_15,
   Map_xxxxRrrgggbbb_16,
   Map_xxxxRrrgggbbb_24,
   Map_xxxxRrrgggbbb_32,
};

/******************************************************************************/
/* 12-bit xBGR (12-bit mapping)                                               */
/******************************************************************************/

// Map_12bit_xBGR
#define BUILD_MAPPER3(NAME, TYPE, PEN_FUNC) \
void NAME(UINT32 bank, UINT32 cols)	\
{					\
   UINT16 yy;				\
   UINT16 *ta;				\
   TYPE *ct,res;			\
					\
   bank_status[bank] = cols;		\
   ta = (UINT16 *) (RAM_PAL+(bank<<5));	\
   ct = (TYPE *)coltab[bank];		\
   do{					\
      yy = (*ta++) & 0x0FFF;		\
					\
      PEN_FUNC(				\
         (yy&0x000F)<<4,		\
         (yy&0x00F0),		\
         (yy&0x0F00)>>4,		\
         res				\
      );				\
					\
      *ct++ = res;			\
					\
   }while(--cols);			\
}

BUILD_MAPPER3(Map_12bit_xBGR_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER3(Map_12bit_xBGR_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER3(Map_12bit_xBGR_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER3(Map_12bit_xBGR_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER3(Map_12bit_xBGR_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_xxxx_bbbb_gggg_rrrr =
{
   "12bit xxxx bbbb gggg rrrr",
   Map_12bit_xBGR_8,
   Map_12bit_xBGR_15,
   Map_12bit_xBGR_16,
   Map_12bit_xBGR_24,
   Map_12bit_xBGR_32,
};

/******************************************************************************/
/* 12-bit RGBx (12-bit mapping)                                               */
/******************************************************************************/

void Map_12bit_RGBx(int bank, int cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = coltab[bank];
   do{
      yy = (*ta++) >> 4;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = coltab[bank];
   do{
      yy = (*ta++) >> 4;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) >> 4;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) >> 4;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) >> 4;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) >> 4;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_rrrr_gggg_bbbb_xxxx =
{
   "12bit rrrr gggg bbbb xxxx",
   map_12bit_rrrr_gggg_bbbb_xxxx_8,
   map_12bit_rrrr_gggg_bbbb_xxxx_15,
   map_12bit_rrrr_gggg_bbbb_xxxx_16,
   map_12bit_rrrr_gggg_bbbb_xxxx_24,
   map_12bit_rrrr_gggg_bbbb_xxxx_32,
};

/******************************************************************************/
/* 15-bit RRRRGGGGBBBBRGBx Reverse Colour Order (Jaleco MS-1)                 */
/******************************************************************************/

void map_15bit_rrrr_gggg_bbbb_rgbx_rev_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_8(
         ((yy&0x7800)>>7) | ((yy&0x0004)<<1),
         ((yy&0x0780)>>3) | ((yy&0x0002)<<2),
         ((yy&0x0078)<<1) | ((yy&0x0001)<<3),
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_gggg_bbbb_rgbx_rev_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_15(
         ((yy&0x7800)>>7) | ((yy&0x0004)<<1),
         ((yy&0x0780)>>3) | ((yy&0x0002)<<2),
         ((yy&0x0078)<<1) | ((yy&0x0001)<<3),
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_gggg_bbbb_rgbx_rev_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_16(
         ((yy&0x7800)>>7) | ((yy&0x0004)<<1),
         ((yy&0x0780)>>3) | ((yy&0x0002)<<2),
         ((yy&0x0078)<<1) | ((yy&0x0001)<<3),
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_gggg_bbbb_rgbx_rev_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_24(
         ((yy&0x7800)>>7) | ((yy&0x0004)<<1),
         ((yy&0x0780)>>3) | ((yy&0x0002)<<2),
         ((yy&0x0078)<<1) | ((yy&0x0001)<<3),
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_gggg_bbbb_rgbx_rev_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_32(
         ((yy&0x7800)>>7) | ((yy&0x0004)<<1),
         ((yy&0x0780)>>3) | ((yy&0x0002)<<2),
         ((yy&0x0078)<<1) | ((yy&0x0001)<<3),
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_rrrr_gggg_bbbb_rgbx_rev =
{
   "15bit rrrr gggg bbbb rgbx [reverse]",
   map_15bit_rrrr_gggg_bbbb_rgbx_rev_8,
   map_15bit_rrrr_gggg_bbbb_rgbx_rev_15,
   map_15bit_rrrr_gggg_bbbb_rgbx_rev_16,
   map_15bit_rrrr_gggg_bbbb_rgbx_rev_24,
   map_15bit_rrrr_gggg_bbbb_rgbx_rev_32,
};

// Map_15bit_RRRRGGGGBBBBRGBx
#define BUILD_MAPPER5(NAME, TYPE, PEN_FUNC)		\
void NAME(UINT32 bank, UINT32 cols)	\
{							\
   UINT16 yy;						\
   UINT16 *ta;						\
   TYPE *ct,res;					\
                                                        \
   bank_status[bank] = cols;                            \
   ta = (UINT16 *) (RAM_PAL+(bank<<5));                 \
   ct = (TYPE*)coltab[bank];                            \
   do{                                                  \
      yy = (*ta++) >> 1;                                \
                                                        \
      PEN_FUNC(                             \
         ((yy&0x7800)>>7) | ((yy&0x0004)<<1),           \
         ((yy&0x0780)>>3) | ((yy&0x0002)<<2),           \
         ((yy&0x0078)<<1) | ((yy&0x0001)<<3),           \
         res                                            \
      );                                                \
                                                        \
      *ct++ = res;                                      \
                                                        \
   }while(--cols);                                      \
}

BUILD_MAPPER5(Map_15bit_RRRRGGGGBBBBRGBx_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER5(Map_15bit_RRRRGGGGBBBBRGBx_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER5(Map_15bit_RRRRGGGGBBBBRGBx_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER5(Map_15bit_RRRRGGGGBBBBRGBx_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER5(Map_15bit_RRRRGGGGBBBBRGBx_32,UINT32,GET_PEN_FOR_COLOUR_32)

// Map_15bit_xRGBRRRRGGGGBBBB
#undef BUILD_MAPPER5
#define BUILD_MAPPER5(NAME, TYPE, PEN_FUNC)		\
void NAME(UINT32 bank, UINT32 cols)	\
{							\
   UINT16 yy;						\
   UINT16 *ta;						\
   TYPE *ct,res;					\
                                                        \
   bank_status[bank] = cols;                            \
   ta = (UINT16 *) (RAM_PAL+(bank<<5));                 \
   ct = (TYPE*)coltab[bank];                            \
   do{                                                  \
      yy = (*ta++);                                     \
                                                        \
      PEN_FUNC(                             \
         ((yy&0x0F00)>>4) | ((yy&0x4000)>>11),           \
         ((yy&0x00F0)>>0) | ((yy&0x2000)>>10),           \
         ((yy&0x000F)<<4) | ((yy&0x1000)>>9),           \
         res                                            \
      );                                                \
                                                        \
      *ct++ = res;                                      \
                                                        \
   }while(--cols);                                      \
}

int get_pen(int red, int green, int blue, int yy) {
  int result;
      if(cloc_2a[yy] == 255){                                                \
         if(talc < 255){                                                     \
            result = cloc_2a[yy] = cloc[yy] = talc;                          \
            pal[talc].r = red;                                               \
            pal[talc].g = green;                                             \
            pal[talc].b = blue;                                              \
            talc++;                                                          \
            while((pmap_2[talc])||(pmap_2a[talc])){ talc++; }                \
         }                                                                   \
         else{				                                     \
            result = closest_colour(red, green, blue);                       \
         }                                                                   \
      }                                                                      \
      else{                                                                  \
         result = cloc[yy] = cloc_2a[yy];                                    \
      }                                                                      \
      pmap[result] = 1;
      return result;
}

BUILD_MAPPER5(Map_15bit_xRGBRRRRGGGGBBBB_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER5(Map_15bit_xRGBRRRRGGGGBBBB_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER5(Map_15bit_xRGBRRRRGGGGBBBB_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER5(Map_15bit_xRGBRRRRGGGGBBBB_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER5(Map_15bit_xRGBRRRRGGGGBBBB_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_Map_15bit_RRRRGGGGBBBBRGBx =
{
   "15bit_RRRRGGGGBBBBRGBx",
   Map_15bit_xRGBRRRRGGGGBBBB_8,
   Map_15bit_xRGBRRRRGGGGBBBB_15,
   Map_15bit_xRGBRRRRGGGGBBBB_16,
   Map_15bit_xRGBRRRRGGGGBBBB_24,
   Map_15bit_xRGBRRRRGGGGBBBB_32,
};

struct COLOUR_MAPPER col_Map_15bit_xRGBRRRRGGGGBBBB =
{
   "15bit_xRGBRRRRGGGGBBBB",
   Map_15bit_xRGBRRRRGGGGBBBB_8,
   Map_15bit_xRGBRRRRGGGGBBBB_15,
   Map_15bit_xRGBRRRRGGGGBBBB_16,
   Map_15bit_xRGBRRRRGGGGBBBB_24,
   Map_15bit_xRGBRRRRGGGGBBBB_32,
};

void map_15bit_rrrr_rggg_ggbb_bbbx_rev_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_rggg_ggbb_bbbx_rev_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_rggg_ggbb_bbbx_rev_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_rggg_ggbb_bbbx_rev_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_rrrr_rggg_ggbb_bbbx_rev_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta--) >> 1;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_rrrr_rggg_ggbb_bbbx_rev =
{
   "15bit rrrr rggg ggbb bbbx [reverse]",
   map_15bit_rrrr_rggg_ggbb_bbbx_rev_8,
   map_15bit_rrrr_rggg_ggbb_bbbx_rev_15,
   map_15bit_rrrr_rggg_ggbb_bbbx_rev_16,
   map_15bit_rrrr_rggg_ggbb_bbbx_rev_24,
   map_15bit_rrrr_rggg_ggbb_bbbx_rev_32,
};

/******************************************************************************/
/* 12-bit xBGR (12-bit mapping) Reverse Colour Order (WestStory)              */
/******************************************************************************/
// Map_12bit_xBGR_Rev
#define BUILD_MAPPER4(NAME, TYPE, PEN_FUNC)		\
void NAME(UINT32 bank, UINT32 cols)	\
{							\
   UINT16 yy;						\
   UINT16 *ta;						\
   TYPE *ct,res;					\
							\
   bank_status[bank] = cols;				\
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);		\
   ct = (TYPE *)coltab[bank];				\
   do{							\
      yy = (*ta--) & 0x0FFF;				\
							\
      PEN_FUNC(						\
         (yy&0x000F)<<4,				\
         (yy&0x00F0),				\
         (yy&0x0F00)>>4,				\
         res						\
      );						\
							\
      *ct++ = res;					\
							\
   }while(--cols);					\
}

BUILD_MAPPER4(Map_12bit_xBGR_Rev_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER4(Map_12bit_xBGR_Rev_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER4(Map_12bit_xBGR_Rev_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER4(Map_12bit_xBGR_Rev_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER4(Map_12bit_xBGR_Rev_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_xxxx_bbbb_gggg_rrrr_rev =
{
   "12bit xxxx bbbb gggg rrrr_rev",
   Map_12bit_xBGR_Rev_8,
   Map_12bit_xBGR_Rev_15,
   Map_12bit_xBGR_Rev_16,
   Map_12bit_xBGR_Rev_24,
   Map_12bit_xBGR_Rev_32,
};

/******************************************************************************/
/* 12-bit xBGR (12-bit mapping) Reverse Colour Order 2BPP (Cabal FG0)         */
/*                                                                            */
/* Each bank in RAM has 4 colors (2 bitplanes per pixel). Each coltab[bank]   */
/* has 16 colors and thus can store 4 RAM banks                               */
/*                                                                            */
/******************************************************************************/

void Map_12bit_xBGR_Rev_2BPP(int bank, int cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank>>2]|= 1<<(bank&3);
   ta = (UINT16 *) (RAM_PAL+(bank<<3)+6);
   ct = coltab[bank>>2]+((bank&3)<<2);
   do{
      yy = (*ta--) & 0x0FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x000F)<<2,
         (yy&0x00F0)>>2,
         (yy&0x0F00)>>6,
         res
      );

      *ct++ = res;

   }while(--cols);
}

/******************************************************************************/
/* 12-bit RGBx (12-bit mapping)                                               */
/******************************************************************************/

void map_12bit_rrrr_gggg_bbbb_xxxx_rev_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = coltab[bank];
   do{
      yy = ReadWord68k(ta--) >> 4;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_rev_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT16 *) coltab[bank];
   do{
      yy = ReadWord68k(ta--) >> 4;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_rev_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT16 *) coltab[bank];
   do{
      yy = ReadWord68k(ta--) >> 4;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_rev_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT32 *) coltab[bank];
   do{
      yy = ReadWord68k(ta--) >> 4;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_12bit_rrrr_gggg_bbbb_xxxx_rev_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);
   ct = (UINT32 *) coltab[bank];
   do{
      yy = ReadWord68k(ta--) >> 4;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x0F00)>>4,
         (yy&0x00F0),
         (yy&0x000F)<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_rrrr_gggg_bbbb_xxxx_68k =
{
   "12bit rrrr gggg bbbb xxxx [M68000]",
   map_12bit_rrrr_gggg_bbbb_xxxx_rev_8,
   map_12bit_rrrr_gggg_bbbb_xxxx_rev_15,
   map_12bit_rrrr_gggg_bbbb_xxxx_rev_16,
   map_12bit_rrrr_gggg_bbbb_xxxx_rev_24,
   map_12bit_rrrr_gggg_bbbb_xxxx_rev_32,
};

/******************************************************************************/
/* 15-bit xRGB (15-bit mapping)                                               */
/******************************************************************************/

void Map_15bit_xRGB(int bank, int cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank<<5));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}



/******************************************************************************/
/* 15-bit xRGB (15-bit mapping) Reverse Colour Order 680X0 format (Gunbird)   */
/******************************************************************************/
#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT16 yy;					\
   UINT16 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (UINT16 *) (RAM_PAL+(bank<<5)+30);	\
   ct = (TYPE *)coltab[bank];			\
   do{						\
      yy = ReadWord68k(ta--) & 0x7fff;		\
						\
      PEN_FUNC(					\
         (yy&0x7C00)>>7,			\
         (yy&0x03E0)>>2,			\
         (yy&0x001F)<<3,			\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
   }while(--cols);				\
}


BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_xrrr_rrgg_gggb_bbbb_rev_68k =
{
   "15bit xrrr rrgg gggb bbbb [reverse] [68000]",
   map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_8,
   map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_15,
   map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_16,
   map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_24,
   map_15bit_xrrr_rrgg_gggb_bbbb_rev_68k_32,
};

/******************************************************************************/
/* 15-bit xRGB (15-bit mapping) - 68k version                                 */
/******************************************************************************/

#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT16 yy;					\
   UINT16 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (UINT16 *) (RAM_PAL+(bank<<5));		\
   ct = (TYPE *)coltab[bank];			\
   do{						\
      yy = ReadWord68k(ta++) & 0x7fff;		\
						\
      PEN_FUNC(					\
         (yy&0x7C00)>>7,			\
         (yy&0x03E0)>>2,			\
         (yy&0x001F)<<3,			\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
   }while(--cols);				\
}

BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_68k_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_68k_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_68k_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_68k_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(map_15bit_xrrr_rrgg_gggb_bbbb_68k_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_xrrr_rrgg_gggb_bbbb_68k =
{
   "15bit xrrr rrgg gggb bbbb [68000]",
   map_15bit_xrrr_rrgg_gggb_bbbb_68k_8,
   map_15bit_xrrr_rrgg_gggb_bbbb_68k_15,
   map_15bit_xrrr_rrgg_gggb_bbbb_68k_16,
   map_15bit_xrrr_rrgg_gggb_bbbb_68k_24,
   map_15bit_xrrr_rrgg_gggb_bbbb_68k_32,
};

// GRBx (galpanic) 15 bit

#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT16 yy;					\
   UINT16 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (UINT16 *) (RAM_PAL+(bank<<5));		\
   ct = (TYPE *)coltab[bank];			\
   do{						\
      yy = ReadWord(ta++)>>1;			\
						\
      PEN_FUNC(					\
         (yy&0x3e0)>>2,				\
         (yy&0x7c00)>>7,			\
         (yy&0x001f)<<3,			\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
   }while(--cols);				\
}

BUILD_MAPPER(map_15bit_grbx_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(map_15bit_grbx_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(map_15bit_grbx_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(map_15bit_grbx_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(map_15bit_grbx_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_15bit_grbx =
{
   "15bit GRBx",
   map_15bit_grbx_8,
   map_15bit_grbx_15,
   map_15bit_grbx_16,
   map_15bit_grbx_24,
   map_15bit_grbx_32,
};

/******************************************************************************/
/* 15-bit xRGB (15-bit mapping)                                               */
/******************************************************************************/

void map_15bit_xrrr_rrgg_gggb_bbbb_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xrrr_rrgg_gggb_bbbb_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xrrr_rrgg_gggb_bbbb_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xrrr_rrgg_gggb_bbbb_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xrrr_rrgg_gggb_bbbb_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x7C00)>>7,
         (yy&0x03E0)>>2,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_xrrr_rrgg_gggb_bbbb =
{
   "15bit xrrr rrgg gggb bbbb",
   map_15bit_xrrr_rrgg_gggb_bbbb_8,
   map_15bit_xrrr_rrgg_gggb_bbbb_15,
   map_15bit_xrrr_rrgg_gggb_bbbb_16,
   map_15bit_xrrr_rrgg_gggb_bbbb_24,
   map_15bit_xrrr_rrgg_gggb_bbbb_32,
};

/******************************************************************************/
/* 15-bit xBGR (15-bit mapping)                                               */
/******************************************************************************/

void Map_15bit_xBGR(int bank, int cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xbbb_bbgg_gggr_rrrr_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xbbb_bbgg_gggr_rrrr_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xbbb_bbgg_gggr_rrrr_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xbbb_bbgg_gggr_rrrr_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xbbb_bbgg_gggr_rrrr_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_xbbb_bbgg_gggr_rrrr =
{
   "15bit xbbb bbgg gggr rrrr",
   map_15bit_xbbb_bbgg_gggr_rrrr_8,
   map_15bit_xbbb_bbgg_gggr_rrrr_15,
   map_15bit_xbbb_bbgg_gggr_rrrr_16,
   map_15bit_xbbb_bbgg_gggr_rrrr_24,
   map_15bit_xbbb_bbgg_gggr_rrrr_32,
};

/******************************************************************************/
/* 15-bit xBGR (15-bit mapping) [4bits used; AIR-SYSTEM; change to 12-bit?]   */
/******************************************************************************/

void map_15bit_xxbb_bbxg_gggx_rrrr_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x000F)<<4,
         (yy&0x01E0)>>1,
         (yy&0x3C00)>>6,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xxbb_bbxg_gggx_rrrr_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x000F)<<4,
         (yy&0x01E0)>>1,
         (yy&0x3C00)>>6,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xxbb_bbxg_gggx_rrrr_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x000F)<<4,
         (yy&0x01E0)>>1,
         (yy&0x3C00)>>6,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xxbb_bbxg_gggx_rrrr_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x000F)<<4,
         (yy&0x01E0)>>1,
         (yy&0x3C00)>>6,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xxbb_bbxg_gggx_rrrr_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x000F)<<4,
         (yy&0x01E0)>>1,
         (yy&0x3C00)>>6,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_xxbb_bbxg_gggx_rrrr =
{
   "15bit xxbb bbxg gggx rrrr",
   map_15bit_xxbb_bbxg_gggx_rrrr_8,
   map_15bit_xxbb_bbxg_gggx_rrrr_15,
   map_15bit_xxbb_bbxg_gggx_rrrr_16,
   map_15bit_xxbb_bbxg_gggx_rrrr_24,
   map_15bit_xxbb_bbxg_gggx_rrrr_32,
};

/******************************************************************************/
/* 24-bit xRGB (12-bit mapping) 680x0 format                                  */
/******************************************************************************/

void Map_24bit_xRGB(int bank, int cols)
{
   UINT8 yr,yg,yb;
   UINT16 yy;
   UINT8 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (RAM_PAL+(bank<<6));
   ct = coltab[bank];
   do{
      yr = (*(ta+1)) >>4;
      yg = (*(ta+2)) >>4;
      yb = (*(ta+3)) >>4;
      ta += 4;
      yy=((yr<<8)|(yg<<4)|(yb));

      GET_PEN_FOR_COLOUR_8(
         yr<<4,
         yg<<4,
         yb<<4,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_8(UINT32 bank, UINT32 cols)
{
   UINT8 yr,yg,yb;
   UINT32 yy;
   UINT32 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<6));
   ct = coltab[bank];
   do{
      yy = (*ta++) >> 8;

      yr = (yy&0x0000F8)>>0;
      yg = (yy&0x00F800)>>8;
      yb = (yy&0xF80000)>>16;

      yy = (yr<<7) | (yg<<2) | (yb>>3);

      GET_PEN_FOR_COLOUR_8(
         yr << 0,
         yg << 0,
         yb << 0,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_15(UINT32 bank, UINT32 cols)
{
   UINT8 yr,yg,yb;
   UINT32 yy;
   UINT32 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<6));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) >> 8;

      yr = (yy&0x0000Ff)>>0;
      yg = (yy&0x00Ff00)>>8;
      yb = (yy&0xFf0000)>>16;

      GET_PEN_FOR_COLOUR_15(
         yr,
         yg,
         yb,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_16(UINT32 bank, UINT32 cols)
{
   UINT8 yr,yg,yb;
   UINT32 yy;
   UINT32 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<6));
   ct = (UINT16 *) coltab[bank];
   do{
     yy = (*ta++) >> 8;

      yr = (yy&0x0000Ff)>>0;
      yg = (yy&0x00Ff00)>>8;
      yb = (yy&0xFf0000)>>16;

      GET_PEN_FOR_COLOUR_16(
         yr,
         yg,
         yb,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_24(UINT32 bank, UINT32 cols)
{
   UINT8 yr,yg,yb;
   UINT32 yy;
   UINT32 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<6));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) >> 8;

      yr = (yy&0x0000Ff)>>0;
      yg = (yy&0x00Ff00)>>8;
      yb = (yy&0xFf0000)>>16;

      GET_PEN_FOR_COLOUR_24(
         yr,
         yg,
         yb,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_32(UINT32 bank, UINT32 cols)
{
   UINT8 yr,yg,yb;
   UINT32 yy;
   UINT32 *ta;
   UINT32 *ct;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<6));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) >> 8;

      yr = (yy&0x0000Ff);
      yg = (yy&0x00Ff00)>>8;
      yb = (yy&0xFf0000)>>16;

      *ct++ = makecol32(
         yr,
         yg,
         yb
      );

   }while(--cols);
}

struct COLOUR_MAPPER col_map_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb =
{
   "24bit xxxx xxxx rrrr rrrr gggg gggg bbbb bbbb [M68020]",
   map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_8,
   map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_15,
   map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_16,
   map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_24,
   map_24bit_xxxx_xxxx_rrrr_rrrr_gggg_gggg_bbbb_bbbb_32,
};


#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)				\
void NAME(UINT32 bank, UINT32 cols)					\
{									\
  UINT32 yy,*ta;							\
  TYPE *ct,res;								\
									\
    bank_status[bank] = cols--;						\
    ct = (TYPE *) coltab[bank]+1;					\
    ta = (UINT32 *) (RAM_PAL+(bank<<6)+4);				\
   do{									\
      yy = *ta++;							\
									\
      PEN_FUNC(								\
	       (yy&0xFf)>>0,						\
	       (yy&0x00Ff00)>>8,					\
	       (yy&0xFf0000)>>16,					\
	       res							\
	       );							\
									\
      *ct++ = res;							\
									\
   }while(--cols);							\
}

void Map_24bit_RGB_8(UINT32 bank, UINT32 cols)
{
  UINT32 yy,*ta;
  UINT8 *ct,res;
  UINT8 yr,yg,yb;

    bank_status[bank] = cols--;
    ct = (UINT8 *) coltab[bank]+1;
    ta = (UINT32 *) (RAM_PAL+(bank<<6)+4);
   do{
      yy = *ta++;
      yr = (yy&0xF8)>>3; // 5 bits
      yg = (yy&0x00Fc00)>>10; // 6 bits
      yb = (yy&0xF80000)>>19; // 5 bits

      yy = yr | (yg<<5) | (yb<<11);

      GET_PEN_FOR_COLOUR_8(
			   yr<<3,
			   yg<<2,
			   yb<<3,
	       res
	       );

      *ct++ = res;

   }while(--cols);
}

BUILD_MAPPER(Map_24bit_RGB_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(Map_24bit_RGB_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(Map_24bit_RGB_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(Map_24bit_RGB_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_24bit_rgb =
{
   "12bit xxxx bbbb gggg rrrr",
   Map_24bit_RGB_8,
   Map_24bit_RGB_15,
   Map_24bit_RGB_16,
   Map_24bit_RGB_24,
   Map_24bit_RGB_32,
};

/******************************************************************************/
/* 21-bit xRGB (12-bit mapping) 680x0 format (Cleopatra's Fortune)            */
/******************************************************************************/
// Map_21bit_xRGB
// this one is for cleofort, it uses 2 color mappers.
#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT8 yr,yg,yb;				\
   UINT16 yy;					\
   UINT8 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (RAM_PAL+(bank<<6));			\
   ct = (TYPE *)coltab[bank];			\
   do{						\
      yr = ((*(ta+1))&0x7f)<<1;			\
      yg = ((*(ta+2))&0x7f)<<1;			\
      yb = ((*(ta+3))&0x7f)<<1;			\
      ta += 4;					\
						\
      yy=(((yr>>4)<<8)|((yg>>4)<<4)|(yb>>4));		\
      PEN_FUNC(					\
         yr,					\
         yg,					\
         yb,					\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
						\
   }while(--cols);				\
}

// version without 8bpp conversion...
#define BUILD_MAPPER2(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT8 yr,yg,yb;				\
   UINT8 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (RAM_PAL+(bank<<6));			\
   ct = (TYPE *)coltab[bank];			\
   do{						\
      yr = ((*(ta+1))&0x7f)<<1;			\
      yg = ((*(ta+2))&0x7f)<<1;			\
      yb = ((*(ta+3))&0x7f)<<1;			\
      ta += 4;					\
						\
      PEN_FUNC(					\
         yr,					\
         yg,					\
         yb,					\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
						\
   }while(--cols);				\
}


BUILD_MAPPER(Map_21bit_xRGB_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER2(Map_21bit_xRGB_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER2(Map_21bit_xRGB_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER2(Map_21bit_xRGB_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER2(Map_21bit_xRGB_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_21bit_xRGB =
{
   "21bit_xRGB",
   Map_21bit_xRGB_8,
   Map_21bit_xRGB_15,
   Map_21bit_xRGB_16,
   Map_21bit_xRGB_24,
   Map_21bit_xRGB_32,
};

/******************************************************************************/
/* 12-bit xxxxRGBx (12-bit mapping) 680x0 format (Arabian Magic)              */
/******************************************************************************/
//Map_12bit_RGBxxxxx
#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC) \
void NAME(UINT32 bank, UINT32 cols)        \
{                                    \
   UINT16 yy;                        \
   UINT8 *ta;                        \
   TYPE *ct,res;                    \
                                     \
   bank_status[bank] = cols;         \
   ta = (RAM_PAL+(bank<<6)+2);       \
   ct = (TYPE *)coltab[bank];                \
   do{                               \
      yy = ReadWord68k(ta)>>4;       \
      ta += 4;                       \
                                     \
      PEN_FUNC(          \
         (yy&0x0F00)>>4,             \
         (yy&0x00F0)>>0,             \
         (yy&0x000F)<<4,             \
         res                         \
      );                             \
                                     \
      *ct++ = res;                   \
                                     \
   }while(--cols);                   \
}

BUILD_MAPPER(Map_12bit_RGBxxxxx_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(Map_12bit_RGBxxxxx_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(Map_12bit_RGBxxxxx_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(Map_12bit_RGBxxxxx_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(Map_12bit_RGBxxxxx_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_12bit_rgbxxxx =
{
   "12bit rgbxxx",
   Map_12bit_RGBxxxxx_8,
   Map_12bit_RGBxxxxx_15,
   Map_12bit_RGBxxxxx_16,
   Map_12bit_RGBxxxxx_24,
   Map_12bit_RGBxxxxx_32,
};

#undef BUILD_MAPPER
#define BUILD_MAPPER(NAME, TYPE, PEN_FUNC)	\
void NAME(UINT32 bank, UINT32 cols)		\
{						\
   UINT16 yy;					\
   UINT16 *ta;					\
   TYPE *ct,res;				\
						\
   bank_status[bank] = cols;			\
   ta = (UINT16 *) (RAM_PAL+(bank*bank_cols*2));		\
   ct = (TYPE*)coltab[bank];			\
   do{						\
      yy = (*ta++);				\
						\
      PEN_FUNC(					\
         (yy&0x0F000)>>8,			\
         (yy&0x00F00)>>4,			\
         (yy&0x000F)<<4,			\
         res					\
      );					\
						\
      *ct++ = res;				\
						\
   }while(--cols);				\
}

BUILD_MAPPER(map_12bit_rrrr_gggg_xxxx_bbbb_8,UINT8,GET_PEN_FOR_COLOUR_8)
BUILD_MAPPER(map_12bit_rrrr_gggg_xxxx_bbbb_15,UINT16,GET_PEN_FOR_COLOUR_15)
BUILD_MAPPER(map_12bit_rrrr_gggg_xxxx_bbbb_16,UINT16,GET_PEN_FOR_COLOUR_16)
BUILD_MAPPER(map_12bit_rrrr_gggg_xxxx_bbbb_24,UINT32,GET_PEN_FOR_COLOUR_24)
BUILD_MAPPER(map_12bit_rrrr_gggg_xxxx_bbbb_32,UINT32,GET_PEN_FOR_COLOUR_32)

struct COLOUR_MAPPER col_map_rrrr_gggg_xxxx_bbbb =
{
   "12bit rrrr gggg xxxx bbbb ",
   map_12bit_rrrr_gggg_xxxx_bbbb_8,
   map_12bit_rrrr_gggg_xxxx_bbbb_15,
   map_12bit_rrrr_gggg_xxxx_bbbb_16,
   map_12bit_rrrr_gggg_xxxx_bbbb_24,
   map_12bit_rrrr_gggg_xxxx_bbbb_32,
};

/******************************************************************************/
/* 15bit rrrr rggg ggbb bbbx xxxx xxxx xxxx xxxx                              */
/******************************************************************************/

void map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT32 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<10));
   ct = coltab[bank];
   do{
      yy = (*ta++) >> 1;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT32 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<10));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) >> 1;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT32 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<10));
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) >> 1;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT32 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<10));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) >> 1;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT32 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT32 *) (RAM_PAL+(bank<<10));
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) >> 1;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x001F)<<3,
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx =
{
   "15bit bbbb bggg ggrr rrrx xxxx xxxx xxxx xxxx",
   map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_8,
   map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_15,
   map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_16,
   map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_24,
   map_15bit_bbbb_bggg_ggrr_rrrx_xxxx_xxxx_xxxx_xxxx_32,
};

/******************************************************************************/
/* 15bit xggg ggrr rrrb bbbb                                                  */
/******************************************************************************/

void map_15bit_xggg_ggrr_rrrb_bbbb_8(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT8 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) colour_ram_src[bank];
   ct = coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_8(
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xggg_ggrr_rrrb_bbbb_15(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) colour_ram_src[bank];
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_15(
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xggg_ggrr_rrrb_bbbb_16(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT16 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) colour_ram_src[bank];
   ct = (UINT16 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_16(
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xggg_ggrr_rrrb_bbbb_24(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) colour_ram_src[bank];
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_24(
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

void map_15bit_xggg_ggrr_rrrb_bbbb_32(UINT32 bank, UINT32 cols)
{
   UINT16 yy;
   UINT16 *ta;
   UINT32 *ct,res;

   bank_status[bank] = cols;
   ta = (UINT16 *) colour_ram_src[bank];
   ct = (UINT32 *) coltab[bank];
   do{
      yy = (*ta++) & 0x7FFF;

      GET_PEN_FOR_COLOUR_32(
         (yy&0x03E0)>>2,
         (yy&0x7C00)>>7,
         (yy&0x001F)<<3,
         res
      );

      *ct++ = res;

   }while(--cols);
}

struct COLOUR_MAPPER col_map_xggg_ggrr_rrrb_bbbb =
{
   "15bit xggg ggrr rrrb bbbb",
   map_15bit_xggg_ggrr_rrrb_bbbb_8,
   map_15bit_xggg_ggrr_rrrb_bbbb_15,
   map_15bit_xggg_ggrr_rrrb_bbbb_16,
   map_15bit_xggg_ggrr_rrrb_bbbb_24,
   map_15bit_xggg_ggrr_rrrb_bbbb_32,
};

/******************************************************************************/
/*                                                                            */
/*                     CLOSEST MATCHING COLOUR ROUTINE                        */
/*                                                                            */
/******************************************************************************/

static UINT32 col_diff[128*3];

static void closest_colour_init(void)
{
   int i;

   for(i=1; i<64; i++){
      int k = i * i;
      col_diff[0  +i] = col_diff[0  +128-i] = k * (59 * 59);
      col_diff[128+i] = col_diff[128+128-i] = k * (30 * 30);
      col_diff[256+i] = col_diff[256+128-i] = k * (11 * 11);
   }
}

/*

Find the best fitting colour in the range res_pens - 254

*/

static UINT8 closest_colour(int r, int g, int b)
{
   int i, coldiff, lowest, bestfit;
   RGB *rgb;

   bestfit = 0;
   lowest = INT_MAX;

   i = res_pens;

   rgb = &pal[i];

   do{
      coldiff = (col_diff + 0) [ (rgb->g - g) & 0x7F ];
      if (coldiff < lowest) {
	 coldiff += (col_diff + 128) [ (rgb->r - r) & 0x7F ];
	 if (coldiff < lowest) {
	    coldiff += (col_diff + 256) [ (rgb->b - b) & 0x7F ];
	    if (coldiff < lowest) {
	       bestfit = i;
	       if (coldiff == 0)
		  return bestfit;
	       lowest = coldiff;
	    }
	 }
      }
      i++;
      rgb++;
   }while(i<255);

   return bestfit;
}

