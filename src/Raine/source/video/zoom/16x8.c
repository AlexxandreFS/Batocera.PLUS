/******************************************************************************/
/*                                                                            */
/*                          RAINE 16x8 TILE ZOOMING                           */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "zoom/16x8.h"
#include "debug.h"
#include "blit.h"

/*

Not implemented:

- Could merge some stuff.
- x86 versions.
- There are 16 different ways to draw a 15x15 sprite, but the chained
  zooming code can only select 1. This probably causes a slight reduction
  in zooming image quality. Same applies to 1x1-14x14 data.

*/

#ifdef RAINE_DEBUG
#define DEBUG_TABLES
#endif

/******************************************************************************/

static UINT8 zoom_1616_dat[(16+1)*16];	// [16+1][16] array
static UINT8 zoom_1616r_dat[(16+1)*16];	// [16+1][16] array

static UINT8 zoom_88_dat[(8+1)*8];	// [8+1][8] array
static UINT8 zoom_88r_dat[(8+1)*8];	// [8+1][8] array

void init_16x8_zoom(void)
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

   // Make data table for normal orientation

   for(yy=0;yy<=8;yy++){
      ZZZ=zoom_88_dat+(yy<<3);
      for(xx=0;xx<yy;xx++){
         ZZZ[xx]=((xx<<3)/yy);
         #ifdef DEBUG_TABLES
         print_debug("%02x ",ZZZ[xx]);
         #endif
      }
      #ifdef DEBUG_TABLES
      print_debug("[%02x]\n",yy);
      #endif
   }

   // Make data table for flipped orientation

   for(yy=0;yy<=8;yy++){
      ZZZ=zoom_88r_dat+(yy<<3);
      for(xx=0;xx<yy;xx++){
         ZZZ[xx]=((((yy-1)-xx)<<3)/yy);
         #ifdef DEBUG_TABLES
         print_debug("%02x ",ZZZ[xx]);
         #endif
      }
      #ifdef DEBUG_TABLES
      print_debug("[%02x]\n",yy);
      #endif
   }
}

// Make chain offset data for hardware with 16x8
// chained zoomed sprites [TAITO Z-System]

UINT8 *make_16x8_zoom_ofs_type1z(void)
{
   UINT8 *zoom16_ofs;
   int ta,tb,tc,td;

   zoom16_ofs = AllocateMem(128*16);

   for(ta=0;ta<128;ta++){
      td=0;
      for(tb=0;tb<16;tb++){
         tc = ((((tb+1)*8)*(ta+1))/128) - (((tb*8)*(ta+1))/128);
         zoom16_ofs[(ta*16)+(15-tb)] = tc;
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

UINT8 *make_16x8_zoom_ofs_type1zz(void)
{
   UINT8 *zoom16_ofs;
   int ta,tb,tc,td;

   zoom16_ofs = AllocateMem(64*8);

   for(ta=0;ta<64;ta++){
      td=0;
      for(tb=0;tb<8;tb++){
         tc = ((((tb+1)*8)*(ta+1))/64) - (((tb*8)*(ta+1))/64);
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

/******************************************************************************/

#define render_pal(SIZE,EXT) \
void Draw16x8_Trans_Mapped_ZoomXY##EXT(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Trans_Mapped##EXT(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616_dat+(zoom_x<<4); \
      ZZY=zoom_88_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
void Draw16x8_Trans_Mapped_ZoomXY##EXT##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Trans_Mapped##EXT##_FlipY(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616r_dat+(zoom_x<<4); \
      ZZY=zoom_88_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
void Draw16x8_Trans_Mapped_ZoomXY##EXT##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Trans_Mapped##EXT##_FlipX(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616_dat+(zoom_x<<4); \
      ZZY=zoom_88r_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
void Draw16x8_Trans_Mapped_ZoomXY##EXT##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Trans_Mapped##EXT##_FlipXY(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616r_dat+(zoom_x<<4); \
      ZZY=zoom_88r_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
/******************************************************************************/ \
 \
void Draw16x8_Mapped_ZoomXY##EXT(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Mapped##EXT(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616_dat+(zoom_x<<4); \
      ZZY=zoom_88_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
void Draw16x8_Mapped_ZoomXY##EXT##_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Mapped##EXT##_FlipY(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616r_dat+(zoom_x<<4); \
      ZZY=zoom_88_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
void Draw16x8_Mapped_ZoomXY##EXT##_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Mapped##EXT##_FlipX(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616_dat+(zoom_x<<4); \
      ZZY=zoom_88r_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
} \
 \
void Draw16x8_Mapped_ZoomXY##EXT##_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y) \
{ \
   UINT8 *SSS,*ZZX,*ZZY; \
   UINT##SIZE *BIT; \
   int xx,yy; \
 \
   if((zoom_x+zoom_y)==24){ \
      Draw16x8_Mapped##EXT##_FlipXY(SPR,x,y,cmap); \
      return; \
   } \
 \
   if((zoom_x!=0)&&(zoom_y!=0)){ \
 \
      ZZX=zoom_1616r_dat+(zoom_x<<4); \
      ZZY=zoom_88r_dat+(zoom_y<<3); \
 \
      BIT=((UINT##SIZE *)GameBitmap->line[y])+x; \
 \
      yy=0; \
      do{ \
         SSS=SPR+(ZZY[yy]<<4); \
         xx=0; \
         do{ \
            BIT[xx]=((UINT##SIZE *)cmap)[SSS[ZZX[xx]]]; \
         }while((++xx)<zoom_x); \
         BIT+=GameBitmap->w; \
      }while((++yy)<zoom_y); \
 \
   } \
}

render_pal(8,_8);
render_pal(16,_16)
render_pal(32,_32)

/******************************************************************************/

