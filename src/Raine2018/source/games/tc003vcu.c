/******************************************************************************/
/*                                                                            */
/*                tc0003vcu: TAITO VIDEO CHIP UNIT (F3-SYSTEM)                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc003vcu.h"

/*

tc0003vcu main
--------------

00000-03FFF | OBJECT A (tc0200obj)
08000-0BFFF | OBJECT B (tc0200obj)
10000-10FFF | BG0 RAM - 512 x 512
11000-11FFF | BG0 RAM - 512 x 512
12000-12FFF | BG0 RAM - 512 x 512
13000-13FFF | BG0 RAM - 512 x 512
10000-11FFF | BG0 RAM - 1024 x 512
12000-13FFF | BG0 RAM - 1024 x 512
14000-15FFF | BG0 RAM - 1024 x 512
16000-17FFF | BG0 RAM - 1024 x 512
1C000-1DFFF | FG0 RAM - 512 x 512
1E000-1FFFF | FG0 GFX

20000-201FF | LINE SET RAM (256 x 2 bytes) 1000 | ????
20200-203FF | LINE SET RAM (256 x 2 bytes) 1400 | ????
20400-205FF | LINE SET RAM (256 x 2 bytes) 1800 | ????
20600-207FF | LINE SET RAM (256 x 2 bytes) 1C00 | ????
20800-209FF | LINE SET RAM (256 x 2 bytes) 2000 | ????
20A00-20BFF | LINE SET RAM (256 x 2 bytes) 2400 | ????
20C00-20DFF | LINE SET RAM (256 x 2 bytes) 2800 | ????
20E00-20FFF | LINE SET RAM (256 x 2 bytes) 2C00 | ????

21000-21FFF | PIVOT PORT RAM
22000-2FFFF | LINE DATA RAM

24000-241FF | ? LINE SCROLL? (256 x 2 bytes)
24200-243FF | ? LINE SCROLL? (256 x 2 bytes)
24400-245FF | ? LINE SCROLL? (256 x 2 bytes)
24600-247FF | ? LINE SCROLL? (256 x 2 bytes)
24800-249FF | ? LINE SCROLL? (256 x 2 bytes)
24A00-24BFF | ? LINE SCROLL? (256 x 2 bytes)
24C00-24DFF | ? LINE SCROLL? (256 x 2 bytes)
24E00-24FFF | ? LINE SCROLL? (256 x 2 bytes)

28000-281FF | ? LINE ZOOM? (256 x 2 bytes)
28200-283FF | ? LINE ZOOM? (256 x 2 bytes)
28400-285FF | ? LINE ZOOM? (256 x 2 bytes)
28600-287FF | ? LINE ZOOM? (256 x 2 bytes)
28800-289FF | ? LINE ZOOM? (256 x 2 bytes)
28A00-28BFF | ? LINE ZOOM? (256 x 2 bytes)
28C00-28DFF | ? LINE ZOOM? (256 x 2 bytes)
28E00-28FFF | ? LINE ZOOM? (256 x 2 bytes)

30000-3FFFF | PIVOT RAM

BS: 2-3-1-0 = 100F 140F 180F 1C02 2005 240F 2806 2C06
BM: 0-1-3-2 = 100F 140F 180D 1C02 2005 240F 280E 2C07

FG0 RAM:

H: 0x02 bytes x 0x40 = 0x0080 = 512
V: 0x80 bytes x 0x40 = 0x2000 = 512

tc0003vcu scroll
----------------

-----+--------+---------------------
Byte | Bit(s) | Use
-----+76543210+---------------------
 00  |xxxxxxxx| BG0 Scroll X (high)
 01  |x+......| BG0 Scroll X (low)
 02  |xxxxxxxx| BG1 Scroll X (high)
 03  |x+......| BG1 Scroll X (low)
 04  |xxxxxxxx| BG2 Scroll X (high)
 05  |x+......| BG2 Scroll X (low)
 06  |xxxxxxxx| BG3 Scroll X (high)
 07  |x+......| BG3 Scroll X (low)
 08  |xxxxxxxx| BG0 Scroll Y (high)
 09  |x.......| BG0 Scroll Y (low)
 0A  |xxxxxxxx| BG1 Scroll Y (high)
 0B  |x.......| BG1 Scroll Y (low)
 0C  |xxxxxxxx| BG2 Scroll Y (high)
 0D  |x.......| BG2 Scroll Y (low)
 0E  |xxxxxxxx| BG3 Scroll Y (high)
 0F  |x.......| BG3 Scroll Y (low)
 10  |........| BG0 ???
 11  |.xxxxxxx| BG0 ???
 12  |........| BG1 ???
 13  |.xxxxxxx| BG1 ???
 14  |........| BG2 ???
 15  |.xxxxxxx| BG2 ???
 16  |........| BG3 ???
 17  |.xxxxxxx| BG4 ???
 18  |.......x| PX0 Scroll X (high)
 19  |xxxxxxxx| PX0 Scroll X (low)
 1A  |.......x| PX0 Scroll Y (high)
 1B  |xxxxxxxx| PX0 Scroll Y (low)
 1C  |00000000| Unused
 1D  |00000000| Unused
 1E  |........| Control?
 1F  |........| Control?
 1F  |...xxxxx| BG0-3/FG0 disable?
 1F  |..x.....| ?
 1F  |.x......| Screen Flip
 20  |........| BG0 Zoom X (high)
 21  |........| BG0 Zoom X (low)
 22  |........| BG1 Zoom X (high)
 23  |........| BG1 Zoom X (low)
 24  |........| BG2 Zoom X (high)
 25  |........| BG2 Zoom X (low)
 26  |........| BG3 Zoom X (high)
 27  |........| BG3 Zoom X (low)
 28  |........| BG0 Zoom Y (high)
 29  |........| BG0 Zoom Y (low)
 2A  |........| BG1 Zoom Y (high)
 2B  |........| BG1 Zoom Y (low)
 2C  |........| BG2 Zoom Y (high)
 2D  |........| BG2 Zoom Y (low)
 2E  |........| BG3 Zoom Y (high)
 2F  |........| BG3 Zoom Y (low)

-----+--------+---------------------

Video hardware of F3-System. tc0003vcu is just a made up name, since I don't
know the real one.

Also appears in Metal Black, Dead Connection, Football Champ [F2/F3-Hybrids].

Not implemented:

- Everything except FG0.

*/

/******************************************************************************/

void f3video_render_fg0(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0003vcu.RAM + 0x1C000;
   GFX_BG    = tc0003vcu.RAM + 0x1E000;

   bmp_x = tc0003vcu.bmp_x;
   bmp_y = tc0003vcu.bmp_y;
   bmp_w = tc0003vcu.bmp_w;
   bmp_h = tc0003vcu.bmp_h;
   scr_x = tc0003vcu.scr_x;
   scr_y = tc0003vcu.scr_y;

   tx = 128-(bmp_w>>2);

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<(bmp_h+bmp_y);y+=8,zz+=tx){
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=2){

      ta=RAM_BG[zz+1];
      if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]>>1)&0x3F,
            16,
            map
         );

         switch(RAM_BG[zz]&0x81){
         case 0x01: Draw8x8_Trans_Packed_Mapped_Rot(&GFX_BG[ta<<5],x,y,map);        break;
         case 0x00: Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x81: Draw8x8_Trans_Packed_Mapped_FlipX_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x80: Draw8x8_Trans_Packed_Mapped_FlipXY_Rot(&GFX_BG[ta<<5],x,y,map); break;
         }

      }

      }
      }
}

void f3video_render_fg0_new(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0003vcu.RAM + 0x1C000;
   GFX_BG    = tc0003vcu.RAM + 0x1E000;

   bmp_x = tc0003vcu.bmp_x;
   bmp_y = tc0003vcu.bmp_y;
   bmp_w = tc0003vcu.bmp_w;
   bmp_h = tc0003vcu.bmp_h;
   scr_x = tc0003vcu.scr_x;
   scr_y = tc0003vcu.scr_y;

   tx = 128-(bmp_w>>2);

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<(bmp_h+bmp_y);y+=8,zz+=tx){
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=2){

      ta=RAM_BG[zz+1];
      if(ta!=0){

         MAP_PALETTE_MULTI_MAPPED_NEW(
            (RAM_BG[zz]>>1)&0x3F,
            16,
            map
         );

         switch(RAM_BG[zz]&0x81){
         case 0x01: Draw8x8_Trans_Packed_Mapped_Rot(&GFX_BG[ta<<5],x,y,map);        break;
         case 0x00: Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x81: Draw8x8_Trans_Packed_Mapped_FlipX_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x80: Draw8x8_Trans_Packed_Mapped_FlipXY_Rot(&GFX_BG[ta<<5],x,y,map); break;
         }

      }

      }
      }
}

void f3video_render_fg0_r180(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0003vcu.RAM + 0x1C000;
   GFX_BG    = tc0003vcu.RAM + 0x1E000;

   bmp_x = tc0003vcu.bmp_x;
   bmp_y = tc0003vcu.bmp_y;
   bmp_w = tc0003vcu.bmp_w;
   bmp_h = tc0003vcu.bmp_h;
   scr_x = tc0003vcu.scr_x;
   scr_y = tc0003vcu.scr_y;

   tx = 128-(bmp_w>>2);

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=tx){
      for(x=(bmp_w+bmp_x-8);(UINT32)x>=bmp_x;x-=8,zz+=2){

      ta=RAM_BG[zz+1];
      if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]>>1)&0x3F,
            16,
            map
         );

         switch(RAM_BG[zz]&0x81){
         case 0x80: Draw8x8_Trans_Packed_Mapped_Rot(&GFX_BG[ta<<5],x,y,map);        break;
         case 0x81: Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x00: Draw8x8_Trans_Packed_Mapped_FlipX_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x01: Draw8x8_Trans_Packed_Mapped_FlipXY_Rot(&GFX_BG[ta<<5],x,y,map); break;
         }

      }

      }
      }
}

void f3video_render_fg0_r270(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0003vcu.RAM + 0x1C000;
   GFX_BG    = tc0003vcu.RAM + 0x1E000;

   bmp_x = tc0003vcu.bmp_x;
   bmp_y = tc0003vcu.bmp_y;
   bmp_w = tc0003vcu.bmp_w;
   bmp_h = tc0003vcu.bmp_h;
   scr_x = tc0003vcu.scr_x;
   scr_y = tc0003vcu.scr_y;

   tx = 128-(bmp_h>>2);

      MAKE_SCROLL_512x512_2_8_no16(
         scr_y,		//-(ReadWord(RAM_SCR+0)),
         scr_x		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=tx){
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=2){

      ta=RAM_BG[zz+1];
      if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]>>1)&0x3F,
            16,
            map
         );

         switch(RAM_BG[zz]&0x81){
         case 0x01: Draw8x8_Trans_Packed_Mapped_Rot(&GFX_BG[ta<<5],x,y,map);        break;
         case 0x81: Draw8x8_Trans_Packed_Mapped_FlipY_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x00: Draw8x8_Trans_Packed_Mapped_FlipX_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x80: Draw8x8_Trans_Packed_Mapped_FlipXY_Rot(&GFX_BG[ta<<5],x,y,map); break;
         }

      }

      }
      }
}

/******************************************************************************/

void f3video_render_fg0_gfx2(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0003vcu.RAM + 0x1C000;
   GFX_BG    = tc0003vcu.RAM + 0x1E000;

   bmp_x = tc0003vcu.bmp_x;
   bmp_y = tc0003vcu.bmp_y;
   bmp_w = tc0003vcu.bmp_w;
   bmp_h = tc0003vcu.bmp_h;
   scr_x = tc0003vcu.scr_x;
   scr_y = tc0003vcu.scr_y;

   tx = 128-(bmp_w>>2);

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<(bmp_h+bmp_y);y+=8,zz+=tx){
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=2){

      ta=RAM_BG[zz+1];
      if(ta!=0){

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]>>0)&0x3F,
            16,
            map
         );

         switch(RAM_BG[zz]&0xC0){
         case 0x40: Draw8x8_Trans_Packed_Mapped_SwapWord_Rot(&GFX_BG[ta<<5],x,y,map);        break;
         case 0x00: Draw8x8_Trans_Packed_Mapped_SwapWord_FlipY_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0xC0: Draw8x8_Trans_Packed_Mapped_SwapWord_FlipX_Rot(&GFX_BG[ta<<5],x,y,map);  break;
         case 0x80: Draw8x8_Trans_Packed_Mapped_SwapWord_FlipXY_Rot(&GFX_BG[ta<<5],x,y,map); break;
         }

      }

      }
      }
}
