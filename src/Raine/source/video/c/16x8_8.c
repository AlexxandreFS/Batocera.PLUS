/******************************************************************************/
/*                                                                            */
/*                         RAINE 16x8 TILE DRAWING                           */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"
#include "raine.h"
#include "blit.h"

/*

Mapped
Transparent Mapped
Direct-Mapped
Transparent Direct-Mapped

*/

void init_spr16x8asm(void)
{
}

static BITMAP *mask_bitmap;
void init_spr16x8asm_mask(BITMAP *my_bitmap)
{
  mask_bitmap = my_bitmap;
}

// 16x8 mapped sprites

void Draw16x8_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++){
         *line++ = cmap[ *SPR++ ];
      }
   }
}

void Draw16x8_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++){
         *line++ = cmap[ *SPR++ ];
      }
   }
}

void Draw16x8_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x + 15;
      for(xx=0; xx<16; xx++){
         *line-- = cmap[ *SPR++ ];
      }
   }
}

void Draw16x8_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x + 15;
      for(xx=0; xx<16; xx++){
         *line-- = cmap[ *SPR++ ];
      }
   }
}

// 16x8 mapped transparent sprites

void Draw16x8_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++, SPR++){
         if(*SPR)
            line[xx] = cmap[ *SPR ];
      }
   }
}

void Draw16x8_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++, SPR++){
         if(*SPR)
            line[xx] = cmap[ *SPR ];
      }
   }
}

void Draw16x8_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x;
      for(xx=15; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = cmap[ *SPR ];
      }
   }
}

void Draw16x8_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x;
      for(xx=15; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = cmap[ *SPR ];
      }
   }
}

// 16x8 sprites

void Draw16x8_8(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++){
         *line++ = *SPR++ | cmap;
      }
   }
}

void Draw16x8_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++){
         *line++ = *SPR++ | cmap;
      }
   }
}

void Draw16x8_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x + 15;
      for(xx=0; xx<16; xx++){
         *line-- = *SPR++ | cmap;
      }
   }
}

void Draw16x8_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x + 15;
      for(xx=0; xx<16; xx++){
         *line-- = *SPR++ | cmap;
      }
   }
}

// Draw16x8_Mask : just one 16x8 opaque block of the same colour

void Draw16x8_Mask(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;
   UINT32 mask = cmap | (cmap << 8);
   mask |= (mask << 16);

   for(yy=0; yy<8; yy++){
      line = mask_bitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx+=4){
         WriteLong(&line[x],mask);
      }
   }
}

// 16x8 transparent sprites

void Draw16x8_Trans_8(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++, SPR++){
         if(*SPR)
            line[xx] = *SPR | cmap;
      }
   }
}

void Draw16x8_Trans_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++, SPR++){
         if(*SPR)
            line[xx] = *SPR | cmap;
      }
   }
}

void Draw16x8_Trans_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = GameBitmap->line[y+yy] + x;
      for(xx=15; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = *SPR | cmap;
      }
   }
}

void Draw16x8_Trans_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = GameBitmap->line[y+yy] + x;
      for(xx=15; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = *SPR | cmap;
      }
   }
}

// Draw16x8_Mask_Trans

void Draw16x8_Mask_Trans_8(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = mask_bitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++, SPR++){
         if(*SPR)
            line[xx] = cmap;
      }
   }
}

void Draw16x8_Mask_Trans_8_FlipX(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = mask_bitmap->line[y+yy] + x;
      for(xx=0; xx<16; xx++, SPR++){
         if(*SPR)
            line[xx] = cmap;
      }
   }
}

void Draw16x8_Mask_Trans_8_FlipY(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=0; yy<8; yy++){
      line = mask_bitmap->line[y+yy] + x;
      for(xx=15; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = cmap;
      }
   }
}

void Draw16x8_Mask_Trans_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap)
{
   UINT8 *line;
   int xx,yy;

   for(yy=7; yy>=0; yy--){
      line = mask_bitmap->line[y+yy] + x;
      for(xx=15; xx>=0; xx--, SPR++){
         if(*SPR)
            line[xx] = cmap;
      }
   }
}
