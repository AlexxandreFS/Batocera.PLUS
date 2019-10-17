/******************************************************************************/
/*                                                                            */
/*                 tc0002obj: TAITO OBJECT LAYER CHIP (OBJ)                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc002obj.h"

/*

NOTE:

Correct name of this chip is unknown, so I'll call it tc0002obj for now

OBJECT RAM
----------

- 8 bytes/sprite
- 256 sprites (0x800 bytes)
- First sprite has *highest* priority

-----+--------+-------------------------
Byte | Bit(s) | Use
-----+76543210+-------------------------
  0  |.x......| Flip Y Axis
  0  |x.......| Flip X Axis
  1  |....xxxx| Colour Bank
  2  |.......x| Sprite Y
  3  |xxxxxxxx| Sprite Y
  4  |...xxxxx| Sprite Tile
  5  |xxxxxxxx| Sprite Tile
  6  |.......x| Sprite X
  7  |xxxxxxxx| Sprite X
-----+--------+-------------------------

SPRITE CONTROL
--------------

- Maze of Flott [603D MASK] 201C 200B 200F
- Earth Joker 001C
- Cadash 0011 0013 0010 0000

-----+--------+-------------------------
Byte | Bit(s) | Use
-----+76543210+-------------------------
  0  |.......x| ?
  0  |......x.| Write Acknowledge?
  0  |..xxxx..| Colour Bank Offset
  0  |xx......| Unused
  1  |...xxxxx| Unused
  1  |..x.....| BG1:Sprite Priority
  1  |.x......| Priority?
  1  |x.......| Unused
-----+--------+-------------------------

OLD SPRITE CONTROL (RASTAN TYPE)
--------------------------------

-----+--------+-------------------------
Byte | Bit(s) | Use
-----+76543210+-------------------------
  1  |.......x| BG1:Sprite Priority?
  1  |......x.| Write Acknowledge?
  1  |xxx.....| Colour Bank Offset
-----+--------+-------------------------

UINT16 tc0002obj_conv_ctrl(UINT16 src)
{
   UOWRD ta;

   ta  = (src & 0x01) << 13;		// BG1:Sprite Priority
   ta |= (src & 0xE0) >> 3;		// Colour Bank Offset

   return ta;
}

Direct Mapped Games:

Bonze Adventure/Jigoku  - OK
Cadash/Cadash Italian   - OK
Operation Wolf          - OK
Rastan                  - ?
Rainbow Islands         - ?

Mapped Rotate 270 Games:

Maze of Flott           - OK
Earth Joker             - OK
Asuka & Asuka           - OK
Volfied                 - ?

*/

/******************************************************************************/

void render_tc0002obj_mapped(void)
{
   int zz,x,y,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;
   UINT32 spr_col;

   RAM_BG    = tc0002obj.RAM;
   RAM_GFX   = tc0002obj.GFX;
   RAM_MSK   = tc0002obj.MASK;
   tile_mask = tc0002obj.tile_mask;
   sx_1      = tc0002obj.bmp_x - 16;
   sy_1      = tc0002obj.bmp_y - 16;
   sx_2      = tc0002obj.bmp_x + tc0002obj.bmp_w;
   sy_2      = tc0002obj.bmp_y + tc0002obj.bmp_h;
   ofs_x     = tc0002obj.bmp_x + tc0002obj.ofs_x;
   ofs_y     = tc0002obj.bmp_y + tc0002obj.ofs_y;
   spr_col   = ( tc0002obj.ctrl << 2) & 0xF0;
   // int flip_screen = tc0002obj.ctrl & 1;
   int flip;

   zz=0x7F8;
   do{

   x=(ReadWord(&RAM_BG[zz+6]))&0x1FF;
   y=(ReadWord(&RAM_BG[zz+2]))&0x1FF;
   // Tread coords as signed
   if (x > 0x140) x -= 0x200;
   if (y > 0x140) y -= 0x200;
#if 0
   if (flip_screen) {
       x = 320 - x - 16;
       y = 256 - y - 16;
       flip = (RAM_BG[1+zz]&0xC0)^0xc0;
   } else
#endif
       flip = RAM_BG[1+zz]&0xC0;
   x += ofs_x;
   y += ofs_y;


   if((x > sx_1) && (x < sx_2)){


   if((y > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_BG[zz+4])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]&0x0F)|spr_col,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(flip){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{                                        // all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
      }
   }

   }

   }while((zz-=8)>=0);
}

/******************************************************************************/

void render_tc0002obj_mapped_r270(void)
{
   int zz,x,y,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;
   UINT32 spr_col;

   RAM_BG    = tc0002obj.RAM;
   RAM_GFX   = tc0002obj.GFX;
   RAM_MSK   = tc0002obj.MASK;
   tile_mask = tc0002obj.tile_mask;
   sx_1      = tc0002obj.bmp_x - 16;
   sy_1      = tc0002obj.bmp_y - 16;
   sx_2      = tc0002obj.bmp_x + tc0002obj.bmp_w;
   sy_2      = tc0002obj.bmp_y + tc0002obj.bmp_h;
   ofs_x     = tc0002obj.bmp_x + tc0002obj.ofs_x;
   ofs_y     = (tc0002obj.bmp_y + tc0002obj.bmp_h - 16) - tc0002obj.ofs_y;
   spr_col   = ( tc0002obj.ctrl << 2) & 0xF0;

   zz=0x7F8;
   do{

   x=(ofs_x+ReadWord(&RAM_BG[zz+2]))&0x1FF;

   if((x > sx_1) && (x < sx_2)){

   y=(ofs_y-ReadWord(&RAM_BG[zz+6]))&0x1FF;

   if((y > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_BG[zz+4])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]&0x0F)|spr_col,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{                                        // all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
      }
   }

   }

   }while((zz-=8)>=0);
}

/******************************************************************************/
