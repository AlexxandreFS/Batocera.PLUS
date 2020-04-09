/******************************************************************************/
/*                                                                            */
/*                          RAINE 16x16 TILE ZOOMING                          */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "zoom/16x16.h"
#include "debug.h"
#include "priorities.h"
#include "pdraw.h"
#include "blit.h"
#include "alpha.h"
/*

Not implemented:

- Could merge some stuff.
- x86 versions.
- There are 16 different ways to draw a 15x15 sprite, but the chained
  zooming code can only select 1. This probably causes a slight reduction
  in zooming image quality. Same applies to 1x1-14x14 data.

*/

#ifdef RAINE_DEBUG
// #define DEBUG_TABLES
#endif

/******************************************************************************/

UINT8 zoom_1616_dat[(16+1)*16];	// [32+1][16] array
UINT8 zoom_1616r_dat[(16+1)*16];	// [32+1][16] array

void init_16x16_zoom(void)
{
	UINT8 *ZZZ;
	int xx,yy;

	// Make data table for normal orientation

	for(yy=0;yy<=16;yy++){
		ZZZ=zoom_1616_dat+(yy<<4);
		for(xx=0;xx<yy;xx++){
			ZZZ[xx]=((xx<<4)/yy);
#ifdef DEBUG_TABLES
			print_debug("%02x ",ZZZ[xx]);
#endif
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",yy);
#endif
	}

	// Make data table for flipped orientation

	for(yy=0;yy<=16;yy++){
		ZZZ=zoom_1616r_dat+(yy<<4);
		for(xx=0;xx<yy;xx++){
			ZZZ[xx]=((((yy-1)-xx)<<4)/yy);
#ifdef DEBUG_TABLES
			print_debug("%02x ",ZZZ[xx]);
#endif
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",yy);
#endif
	}
}

// Make chain offset data for hardware with 16x16
// chained zoomed sprites [TAITO F2/F3/B-System]

UINT8 *make_16x16_zoom_ofs_type1(void)
{
	UINT8 *zoom16_ofs;
	int ta,tb,tc,td;

	zoom16_ofs = AllocateMem(256*32);

	for(ta=0;ta<256;ta++){
		td=0;
		for(tb=0;tb<32;tb++){
			tc = ((((tb+1)*16)*(ta+1))/256) - (((tb*16)*(ta+1))/256);
			zoom16_ofs[((255-ta)*32)+(31-tb)] = tc;
#ifdef DEBUG_TABLES
			print_debug("%02x ",tc);
#endif
			td += tc;
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",td);
#endif
	}

	return zoom16_ofs;
}

// Make chain offset data for hardware with 16x16
// chained zoomed sprites [TAITO Z-System]

UINT8 *make_16x16_zoom_ofs_type1z(void)
{
	UINT8 *zoom16_ofs;
	int ta,tb,tc,td;

	zoom16_ofs = AllocateMem(128*8);

	for(ta=0;ta<128;ta++){
		td=0;
		for(tb=0;tb<8;tb++){
			tc = ((((tb+1)*16)*(ta+1))/128) - (((tb*16)*(ta+1))/128);
			zoom16_ofs[(ta*8)+(7-tb)] = tc;
#ifdef DEBUG_TABLES
			print_debug("%02x ",tc);
#endif
			td += tc;
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",td);
#endif
	}

	return zoom16_ofs;
}

UINT8 *make_16x16_zoom_ofs_type1zz(void)
{
	UINT8 *zoom16_ofs;
	int ta,tb,tc,td;

	zoom16_ofs = AllocateMem(64*4);

	for(ta=0;ta<64;ta++){
		td=0;
		for(tb=0;tb<4;tb++){
			tc = ((((tb+1)*16)*(ta+1))/64) - (((tb*16)*(ta+1))/64);
			zoom16_ofs[(ta*4)+(3-tb)] = tc;
#ifdef DEBUG_TABLES
			print_debug("%02x ",tc);
#endif
			td += tc;
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",td);
#endif
	}

	return zoom16_ofs;
}

/******************************************************************************/

UINT8 zoom_1632_dat[33*32];	// [32+1][32] array
UINT8 zoom_1632r_dat[33*32];	// [32+1][32] array

void init_16x16_zoom_32(void)
{
	UINT8 *ZZZ;
	int xx,yy;

	// Make data table for normal orientation

	for(yy=0;yy<=32;yy++){
		ZZZ=zoom_1632_dat+(yy*32);
		for(xx=0;xx<yy;xx++){
			ZZZ[xx]=((xx<<4)/yy);
#ifdef DEBUG_TABLES
			print_debug("%02x ",ZZZ[xx]);
#endif
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",yy);
#endif
	}

	// Make data table for flipped orientation

	for(yy=0;yy<=32;yy++){
		ZZZ=zoom_1632r_dat+(yy*32);
		for(xx=0;xx<yy;xx++){
			ZZZ[xx]=((((yy-1)-xx)<<4)/yy);
#ifdef DEBUG_TABLES
			print_debug("%02x ",ZZZ[xx]);
#endif
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",yy);
#endif
	}
}

// Make chain offset data for hardware with 16x16
// chained zoomed sprites [TAITO H/AIR-System]

UINT8 *make_16x16_zoom_ofs_type2(void)
{
	UINT8 *zoom16_ofs;
	int ta,tb,tc,td;

	zoom16_ofs = AllocateMem(128*4);

	for(ta=0;ta<128;ta++){
		td=0;
		for(tb=0;tb<4;tb++){
			tc = ((((tb+1)*16)*(ta+1))/64) - (((tb*16)*(ta+1))/64);
			zoom16_ofs[((ta)*4)+(3-tb)] = tc;
#ifdef DEBUG_TABLES
			print_debug("%02x ",tc);
#endif
			td += tc;
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",td);
#endif
	}

	return zoom16_ofs;
}

/******************************************************************************/

UINT8 zoom_1664_dat[65*64];	// [64+1][64] array
UINT8 zoom_1664r_dat[65*64];	// [64+1][64] array

void init_16x16_zoom_64(void)
{
	UINT8 *ZZZ;
	int xx,yy;

	// Make data table for normal orientation

	for(yy=0;yy<=64;yy++){
		ZZZ=zoom_1664_dat+(yy*64);
		for(xx=0;xx<yy;xx++){
			ZZZ[xx]=((xx<<4)/yy);
#ifdef DEBUG_TABLES
			print_debug("%02x ",ZZZ[xx]);
#endif
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",yy);
#endif
	}

	// Make data table for flipped orientation

	for(yy=0;yy<=64;yy++){
		ZZZ=zoom_1664r_dat+(yy*64);
		for(xx=0;xx<yy;xx++){
			ZZZ[xx]=((((yy-1)-xx)<<4)/yy);
#ifdef DEBUG_TABLES
			print_debug("%02x ",ZZZ[xx]);
#endif
		}
#ifdef DEBUG_TABLES
		print_debug("[%02x]\n",yy);
#endif
	}
}

/******************************************************************************/

#undef ARG_ZOOM
#define ARG_ZOOM UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y
#undef render
#define render(SIZE,BPP)                                                  \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_##BPP(ARG_ZOOM)            \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Trans_Mapped_##BPP(SPR,x,y,cmap);             \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                      \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                      \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            if(SSS[ZZX[xx]]!=0) bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_##BPP##_FlipY(ARG_ZOOM)    \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Trans_Mapped_##BPP##_FlipY(SPR,x,y,cmap);     \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                     \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                      \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            if(SSS[ZZX[xx]]!=0) bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_##BPP##_FlipX(ARG_ZOOM)    \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Trans_Mapped_##BPP##_FlipX(SPR,x,y,cmap);     \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                      \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                     \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            if(SSS[ZZX[xx]]!=0) bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_##BPP##_FlipXY(ARG_ZOOM)   \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Trans_Mapped_##BPP##_FlipXY(SPR,x,y,cmap);    \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                     \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                     \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            if(SSS[ZZX[xx]]!=0) bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_##BPP(ARG_ZOOM)                  \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Mapped_##BPP(SPR,x,y,cmap);                   \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                      \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                      \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]];                     \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_##BPP##_FlipY(ARG_ZOOM)          \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Mapped_##BPP##_FlipY(SPR,x,y,cmap);           \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                     \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                      \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]];                     \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_##BPP##_FlipX(ARG_ZOOM)          \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Mapped_##BPP##_FlipX(SPR,x,y,cmap);           \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                      \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                     \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]];                     \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}                                                                         \
                                                                          \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_##BPP##_FlipXY(ARG_ZOOM)         \
{                                                                         \
   UINT8 *SSS,*ZZX,*ZZY;                                                  \
   UINT##BPP *bit;                                                        \
   int xx,yy;                                                             \
                                                                          \
   if((zoom_x+zoom_y)==32){                                               \
      Draw##SIZE##x##SIZE##_Mapped_##BPP##_FlipXY(SPR,x,y,cmap);          \
      return;                                                             \
   }                                                                      \
                                                                          \
   if((zoom_x!=0)&&(zoom_y!=0)){                                          \
                                                                          \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                     \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                     \
                                                                          \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                            \
                                                                          \
      yy=0;                                                               \
      do{                                                                 \
         SSS=SPR+(ZZY[yy]<<4);                                            \
         xx=0;                                                            \
         do{                                                              \
            bit[xx]=((UINT##BPP*)cmap)[SSS[ZZX[xx]]];                     \
         }while((++xx)<zoom_x);                                           \
         bit+=GameBitmap->w;                                              \
      }while((++yy)<zoom_y);                                              \
   }                                                                      \
}
render(16,8);
render(16,16);
render(16,32);

// And now, the Alpha version...
#undef render
#define render(SIZE,BPP)                                                      \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_Alpha_##BPP(ARG_ZOOM)          \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP(SPR,x,y,cmap);           \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                          \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                          \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            if(SSS[ZZX[xx]]!=0)                                               \
                blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);       \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_Alpha_##BPP##_FlipY(ARG_ZOOM)  \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP##_FlipY(SPR,x,y,cmap);   \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                         \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                          \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            if(SSS[ZZX[xx]]!=0)                                               \
                blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);       \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_Alpha_##BPP##_FlipX(ARG_ZOOM)  \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP##_FlipX(SPR,x,y,cmap);   \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                          \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                         \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            if(SSS[ZZX[xx]]!=0)                                               \
                blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);       \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Trans_Mapped_ZoomXY_Alpha_##BPP##_FlipXY(ARG_ZOOM) \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Trans_Mapped_Alpha_##BPP##_FlipXY(SPR,x,y,cmap);  \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                         \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                         \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            if(SSS[ZZX[xx]]!=0)                                               \
                blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);       \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_Alpha_##BPP(ARG_ZOOM)                \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP(SPR,x,y,cmap);                 \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                          \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                          \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);           \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_Alpha_##BPP##_FlipY(ARG_ZOOM)        \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP##_FlipY(SPR,x,y,cmap);         \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                         \
      ZZY=zoom_1616_dat+(zoom_y<<4);                                          \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);           \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_Alpha_##BPP##_FlipX(ARG_ZOOM)        \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP##_FlipX(SPR,x,y,cmap);         \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616_dat+(zoom_x<<4);                                          \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                         \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);           \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}                                                                             \
                                                                              \
void Draw##SIZE##x##SIZE##_Mapped_ZoomXY_Alpha_##BPP##_FlipXY(ARG_ZOOM)       \
{                                                                             \
   UINT8 *SSS,*ZZX,*ZZY;                                                      \
   UINT##BPP *bit;                                                            \
   int xx,yy;                                                                 \
                                                                              \
   if((zoom_x+zoom_y)==32){                                                   \
      Draw##SIZE##x##SIZE##_Mapped_Alpha_##BPP##_FlipXY(SPR,x,y,cmap);        \
      return;                                                                 \
   }                                                                          \
                                                                              \
   if((zoom_x!=0)&&(zoom_y!=0)){                                              \
                                                                              \
      ZZX=zoom_1616r_dat+(zoom_x<<4);                                         \
      ZZY=zoom_1616r_dat+(zoom_y<<4);                                         \
                                                                              \
      bit=((UINT##BPP*)GameBitmap->line[y])+x;                                \
                                                                              \
      yy=0;                                                                   \
      do{                                                                     \
         SSS=SPR+(ZZY[yy]<<4);                                                \
         xx=0;                                                                \
         do{                                                                  \
            blend_##BPP(&bit[xx],((UINT##BPP*)cmap)[SSS[ZZX[xx]]]);           \
         }while((++xx)<zoom_x);                                               \
         bit+=GameBitmap->w;                                                  \
      }while((++yy)<zoom_y);                                                  \
   }                                                                          \
}
render(16,8);
render(16,16);
render(16,32);

/******************************************************************************/

#if 0
// These functions are probably totally useless (direct mapping + zooming ?!!!)

void Draw16x16_Trans_ZoomXY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16_Trans(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_Trans_ZoomXY_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16_Trans_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_Trans_ZoomXY_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16_Trans_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_Trans_ZoomXY_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16_Trans_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_ZoomXY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_ZoomXY_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;


   if((zoom_x+zoom_y)==32){
      Draw16x16_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_ZoomXY_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_ZoomXY_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      Draw16x16_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx] = SSS[ZZX[xx]] | cmap;
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}
#endif

/******************************************************************************/

void Draw16x16_32_Trans_Mapped_ZoomXY_8(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Trans_Mapped_ZoomXY_8_FlipY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Trans_Mapped_ZoomXY_8_FlipX(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_32_Mapped_ZoomXY_8(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Mapped_ZoomXY_8_FlipY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Mapped_ZoomXY_8_FlipX(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_64_Trans_Mapped_ZoomXY_8(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Trans_Mapped_ZoomXY_8_FlipY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Trans_Mapped_ZoomXY_8_FlipX(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_8_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_64_Mapped_ZoomXY_8(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Mapped_ZoomXY_8_FlipY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Mapped_ZoomXY_8_FlipX(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_8_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

// pdraw version (priority)

void pdraw16x16_Trans_Mapped_ZoomXY_8(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_8(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Trans_Mapped_ZoomXY_8_FlipY(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_8_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Trans_Mapped_ZoomXY_8_FlipX(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_8_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_8_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void pdraw16x16_Mapped_ZoomXY_8(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_8(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Mapped_ZoomXY_8_FlipY(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;


   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_8_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Mapped_ZoomXY_8_FlipX(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_8_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM,  int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_8_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] <= pri) BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

// _64

void pdraw16x16_64_Trans_Mapped_ZoomXY_8(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_8(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_ZoomXY_8_FlipY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_8_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_ZoomXY_8_FlipX(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_8_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_8_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void pdraw16x16_64_Mapped_ZoomXY_8(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_8(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_ZoomXY_8_FlipY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_8_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_ZoomXY_8_FlipX(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_8_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_8_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

// back version

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_8(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8_FlipY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_8_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8_FlipX(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_8_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8_FlipXY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_8_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void pdraw16x16_64_Mapped_back_ZoomXY_8(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_8(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_back_ZoomXY_8_FlipY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_8_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_back_ZoomXY_8_FlipX(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_8_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_back_ZoomXY_8_FlipXY(ARG_ZOOM, int pri)
{
   UINT8 *BIT,*SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_8_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=GameBitmap->line[y]+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=cmap[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}
