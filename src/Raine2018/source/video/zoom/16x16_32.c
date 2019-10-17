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

/******************************************************************************/

void Draw16x16_32_Trans_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Trans_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Trans_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Trans_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_32_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_32_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1632r_dat+(zoom_x<<5);
      ZZY=zoom_1632r_dat+(zoom_y<<5);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_64_Trans_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Trans_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Trans_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Trans_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Trans_Mapped_32_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void Draw16x16_64_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32_FlipY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32_FlipX(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

void Draw16x16_64_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y)
{
   UINT8 *SSS,*ZZX,*ZZY; UINT32 *BIT;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      Draw16x16_Mapped_32_FlipXY(SPR,x,y,cmap);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

// pdraw version

void pdraw16x16_Trans_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline;
   UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_32(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Trans_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline;
   UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_32_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Trans_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline; UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_32_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Trans_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline; UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Trans_Mapped_32_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0 && pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void pdraw16x16_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline; UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_32(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline; UINT32 *BIT;
   int xx,yy;


   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_32_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline; UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_32_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y,  int pri)
{
   UINT8 *SSS,*ZZX,*ZZY, *pline; UINT32 *BIT;
   int xx,yy;

   if((zoom_x+zoom_y)==32){
      pdraw16x16_Mapped_32_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1616r_dat+(zoom_x<<4);
      ZZY=zoom_1616r_dat+(zoom_y<<4);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if (pline[xx] < pri) BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

// _64

void pdraw16x16_64_Trans_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_32(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_32_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_32_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_32_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri && SSS[ZZX[xx]]!=0) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void pdraw16x16_64_Mapped_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_32(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_32_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_32_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_32_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(pline[xx] <= pri) { pline[xx] = 0; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

// back version

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_32(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_32_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_32_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Trans_Mapped_back_32_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            if(SSS[ZZX[xx]]!=0) { pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]]; }
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

/******************************************************************************/

void pdraw16x16_64_Mapped_back_ZoomXY_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_32(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_back_ZoomXY_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_32_FlipY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_back_ZoomXY_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_32_FlipX(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
            pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}

void pdraw16x16_64_Mapped_back_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y, int pri)
{
   UINT32 *BIT; UINT8 *SSS,*ZZX,*ZZY,*pline;
   int xx,yy;

   if((zoom_x==16)&&(zoom_y==16)){
      pdraw16x16_Mapped_back_32_FlipXY(SPR,x,y,cmap,pri);
      return;
   }

   if((zoom_x!=0)&&(zoom_y!=0)){

      ZZX=zoom_1664r_dat+(zoom_x<<6);
      ZZY=zoom_1664r_dat+(zoom_y<<6);

      BIT=((UINT32*)GameBitmap->line[y])+x;
      pline = pbitmap->line[y]+x;

      yy=0;
      do{
         SSS=SPR+(ZZY[yy]<<4);
         xx=0;
         do{
	   pline[xx] = pri; BIT[xx]=((UINT32*)cmap)[SSS[ZZX[xx]]];
         }while((++xx)<zoom_x);
         BIT+=GameBitmap->w;
	 pline += pbitmap->w;
      }while((++yy)<zoom_y);

   }
}
