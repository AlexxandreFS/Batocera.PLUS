
#include "raine.h"
#include "newspr.h"
#include "blit.h"

static UINT8 *ZOOM64;
static UINT8 *ZOOM64R;

/********************************************************************/
// Init64x64_Table():
// Setup zoom table data for 64x64 sprites.
// TPOS Points to $2000 bytes of memory.

void Init64x64_Table(UINT8 *TPOS)
{
   UINT8 *ZZZ;
   int xx,yy;

   ZOOM64=TPOS;

   for(yy=1;yy<65;yy++){	// NORMAL
      ZZZ=ZOOM64+((yy-1)<<6);
      for(xx=0;xx<yy;xx++){
         ZZZ[xx]=((xx<<6)/yy);
      }
   }

   ZOOM64R=TPOS+0x1000;

   for(yy=1;yy<65;yy++){	// FLIP
      ZZZ=ZOOM64R+((yy-1)<<6);
      for(xx=0;xx<yy;xx++){
         ZZZ[xx]=((((yy-1)-xx)<<6)/yy);
      }
   }
}

/* Here are the basic definitions of Draw64x64_Trans_Mapped_16 functions, taken
 * directly from video/c/16x16_16.c */

static void Draw64x64_Trans_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT16 *line;
   int xx,yy;

   for(yy=0; yy<64; yy++){
      line = ((UINT16 *)(GameBitmap->line[y+yy])) + x;
      for(xx=0; xx<64; xx++, SPR++){
         if(*SPR)
            line[xx] = ((UINT16 *)cmap)[ *SPR ];
      }
   }
}

static void Draw64x64_Trans_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT16 *line;
   int xx,yy;

   for(yy=63; yy>=0; yy--){
      line = ((UINT16 *)(GameBitmap->line[y+yy])) + x;
      for(xx=0; xx<64; xx++, SPR++){
         if(*SPR)
            line[xx] = ((UINT16 *)cmap)[ *SPR ];
      }
   }
}

static void Draw64x64_Trans_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT16 *line;
   int xx,yy;

   for(yy=0; yy<64; yy++){
      line = ((UINT16 *)(GameBitmap->line[y+yy])) + x;
      for(xx=63; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = ((UINT16 *)cmap)[ *SPR ];
      }
   }
}

static void Draw64x64_Trans_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT16 *line;
   int xx,yy;

   for(yy=63; yy>=0; yy--){
      line = ((UINT16 *)(GameBitmap->line[y+yy])) + x;
      for(xx=63; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = ((UINT16 *)cmap)[ *SPR ];
      }
   }
}

// And the ones from 16x16_32...

static void Draw64x64_Trans_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT32 *line;
   int xx,yy;

   for(yy=0; yy<64; yy++){
      line = ((UINT32 *)(GameBitmap->line[y+yy])) + x;
      for(xx=0; xx<64; xx++, SPR++){
         if(*SPR)
            line[xx] = ((UINT32 *)cmap)[ *SPR ];
      }
   }
}

static void Draw64x64_Trans_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT32 *line;
   int xx,yy;

   for(yy=63; yy>=0; yy--){
      line = ((UINT32 *)(GameBitmap->line[y+yy])) + x;
      for(xx=0; xx<64; xx++, SPR++){
         if(*SPR)
            line[xx] = ((UINT32 *)cmap)[ *SPR ];
      }
   }
}

static void Draw64x64_Trans_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT32 *line;
   int xx,yy;

   for(yy=0; yy<64; yy++){
      line = ((UINT32 *)(GameBitmap->line[y+yy])) + x;
      for(xx=63; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = ((UINT32 *)cmap)[ *SPR ];
      }
   }
}

static void Draw64x64_Trans_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT32 *line;
   int xx,yy;

   for(yy=63; yy>=0; yy--){
      line = ((UINT32 *)(GameBitmap->line[y+yy])) + x;
      for(xx=63; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = ((UINT32 *)cmap)[ *SPR ];
      }
   }
}

/********************************************************************/
// Draw64x64_Trans_Mapped_Zoom():
// Draw64x64_Trans_Mapped_Zoom_FlipY():
// Draw64x64_Trans_Mapped_Zoom_FlipX():
// Draw64x64_Trans_Mapped_Zoom_FlipXY():
// Zoomed 64x64 sprites, using colour mapping.
// From Looking at the compiled asm, I'm not sure it's worth trying
// to rewrite these in asm...

#define GEN_FUNCS(EXT, TYPE)                                                                                  \
void Draw64x64_Trans_Mapped_Zoom##EXT(UINT8 *SPR, int x, int y, TYPE *cmap, int zoom)                         \
{                                                                                                             \
   TYPE *BIT;                                                                                                 \
   UINT8 *SSS,*ZZXY;                                                                                          \
   int xx,yy;                                                                                                 \
                                                                                                              \
   if(zoom>=63){                                                                                              \
      Draw64x64_Trans_Mapped##EXT(SPR,x,y,(UINT8*)cmap);                                                      \
   }                                                                                                          \
   else{                                                                                                      \
                                                                                                              \
   ZZXY=ZOOM64+(zoom<<6);                                                                                     \
                                                                                                              \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                        \
                                                                                                              \
   for(yy=0;yy<=zoom;yy++){                                                                                   \
      SSS=SPR+(ZZXY[yy]<<6);                                                                                  \
      for(xx=0;xx<=zoom;xx++){                                                                                \
         if(SSS[ZZXY[xx]]!=0)BIT[xx]=cmap[SSS[ZZXY[xx]]];                                                     \
      }                                                                                                       \
      BIT+=GameBitmap->w;                                                                                     \
   }                                                                                                          \
                                                                                                              \
   }                                                                                                          \
}                                                                                                             \
                                                                                                              \
void Draw64x64_Trans_Mapped_Zoom##EXT##_FlipY(UINT8 *SPR, int x, int y, TYPE *cmap, int zoom)                 \
{                                                                                                             \
   TYPE *BIT;                                                                                                 \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                      \
   int xx,yy;                                                                                                 \
                                                                                                              \
                                                                                                              \
   if(zoom>=63){                                                                                              \
      Draw64x64_Trans_Mapped##EXT##_FlipY(SPR,x,y,(UINT8*)cmap);                                              \
   }                                                                                                          \
   else{                                                                                                      \
                                                                                                              \
   ZZX=ZOOM64R+(zoom<<6);                                                                                     \
   ZZY=ZOOM64+(zoom<<6);                                                                                      \
                                                                                                              \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                        \
                                                                                                              \
   for(yy=0;yy<=zoom;yy++){                                                                                   \
      SSS=SPR+(ZZY[yy]<<6);                                                                                   \
      for(xx=0;xx<=zoom;xx++){                                                                                \
         if(SSS[ZZX[xx]]!=0)BIT[xx]=cmap[SSS[ZZX[xx]]];                                                       \
      }                                                                                                       \
      BIT+=GameBitmap->w;                                                                                     \
   }                                                                                                          \
                                                                                                              \
   }                                                                                                          \
}                                                                                                             \
                                                                                                              \
void Draw64x64_Trans_Mapped_Zoom##EXT##_FlipX(UINT8 *SPR, int x, int y, TYPE *cmap, int zoom)                 \
{                                                                                                             \
   TYPE *BIT;                                                                                                 \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                      \
   int xx,yy;                                                                                                 \
                                                                                                              \
   if(zoom>=63){                                                                                              \
      Draw64x64_Trans_Mapped##EXT##_FlipX(SPR,x,y,(UINT8*)cmap);                                              \
   }                                                                                                          \
   else{                                                                                                      \
                                                                                                              \
   ZZX=ZOOM64+(zoom<<6);                                                                                      \
   ZZY=ZOOM64R+(zoom<<6);                                                                                     \
                                                                                                              \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                        \
                                                                                                              \
   for(yy=0;yy<=zoom;yy++){                                                                                   \
      SSS=SPR+(ZZY[yy]<<6);                                                                                   \
      for(xx=0;xx<=zoom;xx++){                                                                                \
         if(SSS[ZZX[xx]]!=0)BIT[xx]=cmap[SSS[ZZX[xx]]];                                                       \
      }                                                                                                       \
      BIT+=GameBitmap->w;                                                                                     \
   }                                                                                                          \
                                                                                                              \
   }                                                                                                          \
}                                                                                                             \
                                                                                                              \
void Draw64x64_Trans_Mapped_Zoom##EXT##_FlipXY(UINT8 *SPR, int x, int y, TYPE *cmap, int zoom)                \
{                                                                                                             \
   TYPE *BIT;                                                                                                 \
   UINT8 *SSS,*ZZXY;                                                                                          \
   int xx,yy;                                                                                                 \
                                                                                                              \
   if(zoom>=63){                                                                                              \
      Draw64x64_Trans_Mapped##EXT##_FlipXY(SPR,x,y,(UINT8*)cmap);                                             \
   }                                                                                                          \
   else{                                                                                                      \
                                                                                                              \
   ZZXY=ZOOM64R+(zoom<<6);                                                                                    \
                                                                                                              \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                        \
                                                                                                              \
   for(yy=0;yy<=zoom;yy++){                                                                                   \
      SSS=SPR+(ZZXY[yy]<<6);                                                                                  \
      for(xx=0;xx<=zoom;xx++){                                                                                \
         if(SSS[ZZXY[xx]]!=0)BIT[xx]=cmap[SSS[ZZXY[xx]]];                                                     \
      }                                                                                                       \
      BIT+=GameBitmap->w;                                                                                     \
   }                                                                                                          \
                                                                                                              \
   }                                                                                                          \
}

GEN_FUNCS(_8,UINT8);
GEN_FUNCS(_16,UINT16);
GEN_FUNCS(_32,UINT32);

/********************************************************************/

#undef GEN_FUNCS
#define GEN_FUNCS(EXT,TYPE)                                                                                      \
void Draw64x64_Trans_Mapped_Zoom2##EXT(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)               \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Trans_Mapped##EXT(SPR,x,y,(UINT8*)cmap);                                                  \
                                                                                                                 \
   ZZX=ZOOM64+(zoomx<<6);                                                                                        \
   ZZY=ZOOM64+(zoomy<<6);                                                                                        \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         if(SSS[ZZX[xx]]!=0)                                                                                     \
         BIT[xx]=cmap[SSS[ZZX[xx]]];                                                                             \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
void Draw64x64_Trans_Mapped_Zoom2##EXT##_FlipY(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)       \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Trans_Mapped##EXT##_FlipY(SPR,x,y,(UINT8*)cmap);                                          \
                                                                                                                 \
   ZZX=ZOOM64R+(zoomx<<6);                                                                                       \
   ZZY=ZOOM64+(zoomy<<6);                                                                                        \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         if(SSS[ZZX[xx]]!=0)BIT[xx]=cmap[SSS[ZZX[xx]]];                                                          \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
void Draw64x64_Trans_Mapped_Zoom2##EXT##_FlipX(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)       \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Trans_Mapped##EXT##_FlipX(SPR,x,y,(UINT8*)cmap);                                          \
                                                                                                                 \
   ZZX=ZOOM64+(zoomx<<6);                                                                                        \
   ZZY=ZOOM64R+(zoomy<<6);                                                                                       \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         if(SSS[ZZX[xx]]!=0)BIT[xx]=cmap[SSS[ZZX[xx]]];                                                          \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
void Draw64x64_Trans_Mapped_Zoom2##EXT##_FlipXY(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)      \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Trans_Mapped##EXT##_FlipXY(SPR,x,y,(UINT8*)cmap);                                         \
                                                                                                                 \
   ZZX=ZOOM64R+(zoomx<<6);                                                                                       \
   ZZY=ZOOM64R+(zoomy<<6);                                                                                       \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         if(SSS[ZZX[xx]]!=0)BIT[xx]=cmap[SSS[ZZX[xx]]];                                                          \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
/********************************************************************/                                           \
                                                                                                                 \
void Draw64x64_Mapped_Zoom2##EXT(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)                     \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Mapped##EXT(SPR,x,y,(UINT8*)cmap);                                                        \
                                                                                                                 \
   ZZX=ZOOM64+(zoomx<<6);                                                                                        \
   ZZY=ZOOM64+(zoomy<<6);                                                                                        \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         BIT[xx]=cmap[SSS[ZZX[xx]]];                                                                             \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
void Draw64x64_Mapped_Zoom2##EXT##_FlipY(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)             \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Mapped##EXT##_FlipY(SPR,x,y,(UINT8*)cmap);                                                \
                                                                                                                 \
   ZZX=ZOOM64R+(zoomx<<6);                                                                                       \
   ZZY=ZOOM64+(zoomy<<6);                                                                                        \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         BIT[xx]=cmap[SSS[ZZX[xx]]];                                                                             \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
void Draw64x64_Mapped_Zoom2##EXT##_FlipX(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)             \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Mapped##EXT##_FlipX(SPR,x,y,(UINT8*)cmap);                                                \
                                                                                                                 \
   ZZX=ZOOM64+(zoomx<<6);                                                                                        \
   ZZY=ZOOM64R+(zoomy<<6);                                                                                       \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         BIT[xx]=cmap[SSS[ZZX[xx]]];                                                                             \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}                                                                                                                \
                                                                                                                 \
void Draw64x64_Mapped_Zoom2##EXT##_FlipXY(UINT8 *SPR, int x, int y, TYPE *cmap, int zoomx, int zoomy)            \
{                                                                                                                \
   TYPE *BIT;                                                                                                    \
   UINT8 *SSS,*ZZX,*ZZY;                                                                                         \
   int xx,yy;                                                                                                    \
                                                                                                                 \
   if((zoomx>=63)&&(zoomy>=63))                                                                                  \
      return Draw64x64_Mapped##EXT##_FlipXY(SPR,x,y,(UINT8*)cmap);                                               \
                                                                                                                 \
   ZZX=ZOOM64R+(zoomx<<6);                                                                                       \
   ZZY=ZOOM64R+(zoomy<<6);                                                                                       \
                                                                                                                 \
   BIT=((TYPE*)GameBitmap->line[y])+x;                                                                           \
                                                                                                                 \
   for(yy=0;yy<=zoomy;yy++){                                                                                     \
      SSS=SPR+(ZZY[yy]<<6);                                                                                      \
      for(xx=0;xx<=zoomx;xx++){                                                                                  \
         BIT[xx]=cmap[SSS[ZZX[xx]]];                                                                             \
      }                                                                                                          \
      BIT+=GameBitmap->w;                                                                                        \
   }                                                                                                             \
}

GEN_FUNCS(_8,UINT8);
GEN_FUNCS(_16,UINT16);
GEN_FUNCS(_32,UINT32);

/********************************************************************/
