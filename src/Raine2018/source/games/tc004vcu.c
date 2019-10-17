/******************************************************************************/
/*                                                                            */
/*           tc0004vcu: TAITO VIDEO CHIP UNIT (H-SYSTEM/AIR-SYSTEM)           */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc004vcu.h"
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines

/*

'tc0004vcu' is a made up name, until someone can give me more board info.

TC0004VCU RAM
-------------

--------------+---------------
00000 - 00FFF | FG0 GFX   [A]
01000 - 01FFF | FG0 RAM   [A]
02000 - 0BFFF | CHAIN RAM [A]
0C000 - 0DFFF | BG0 RAM   [A]
0E000 - 0FFFF | BG1 RAM   [A]
10000 - 10FFF | FG0 GFX   [B]
11000 - 11FFF | FG0 RAM   [B]
12000 - 1BFFF | CHAIN RAM [B]
1C000 - 1DFFF | BG0 RAM   [B]
1E000 - 1FFFF | BG1 RAM   [B]
20400 - 207F7 | OBJECT RAM
20800 - 2080F | SCROLL RAM
--------------+---------------

FG0 RAM
-------

-----+--------+---------------------
Byte | Bit(s) | Info
-----+76543210+---------------------
 A:0 |xxxxxxxx| Tile Number
-----+--------+---------------------

BG0/BG1/CHAIN RAM
-----------------

-----+--------+---------------------
Byte | Bit(s) | Info
-----+76543210+---------------------
 A:0 |.xxxxxxx| Tile Number (high)
 A:1 |xxxxxxxx| Tile Number (low)
 B:1 |x.......| Flip X Axis
 B:1 |.x......| Flip Y Axis
 B:1 |..xxxxxx| Colour Bank
-----+--------+---------------------

OBJECT RAM
----------

- 8 bytes/sprite definition

-----+--------+---------------------
Byte | Bit(s) | Info
-----+76543210+---------------------
  0  |...x....| Sprite:BG1 Priority?
  0  |....xx..| Chain Size Y (1/x/4/x)
  0  |......xx| Sprite X (high)
  1  |xxxxxxxx| Sprite X (low)
  2  |......xx| Sprite Y (high)
  3  |xxxxxxxx| Sprite Y (low)
  4  |++xxxxxx| Zoom X Axis
  5  |++xxxxxx| Zoom Y Axis
  6  |...xxxxx| Sprite Chain (high)
  7  |xxxxxxxx| Sprite Chain (low)
-----+--------+---------------------

Chain Size:

X Size is always 4 tiles (64 pixels)
Y Size is 1/x/4/x tiles

Zoom:

0x20 = x0: Min Size
0x3F = x1: Normal Size
0x7F = x2: Max Size

[Non-linear mapping, I think the hardware has perspective correction maybe]

SCROLL RAM
----------

-----+--------+---------------------
Byte | Bit(s) | Info
-----+76543210+---------------------
  0  |.......x| ?
  0  |......x.| ?
  2  |......xx| BG0 Scroll X (high)
  3  |xxxxxxxx| BG0 Scroll X (low)
  4  |......xx| BG1 Scroll X (high)
  5  |xxxxxxxx| BG1 Scroll X (low)
  6  |......xx| BG0 Scroll Y (high)
  7  |xxxxxxxx| BG0 Scroll Y (low)
  8  |......xx| BG1 Scroll Y (high)
  9  |xxxxxxxx| BG1 Scroll Y (low)
-----+--------+---------------------

Not implemented:

- FG0 Scroll (if it exists).
- Any priority and enable bits that could exist.

Mapped Games:

- Dynamite League [Sprite-BG1 Pri wrong/TV report screen wrong]
- Record Breaker  [Sprite Zoom Y bit wrong]

*/

#define OBJ_X_MASK	0x3FF
#define OBJ_Y_MASK	0x3FF

static UINT8 *GFX_HG0;
static UINT8 *RAM_GFX_HG0A;
static UINT8 *RAM_GFX_HG0B;

static UINT8 *zoom16_ofs;

static UINT8 zoom_conv_x[0x80];
static UINT8 zoom_conv_y[0x80];

static UINT8 zoom_table[0x80+1]=
{
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x03,0x04,0x08,0x0B,0x0E,0x11,0x14,0x17,0x1A,0x1C,0x1E,0x21,0x23,0x25,0x27,
   0x29,0x2B,0x2C,0x2E,0x30,0x31,0x33,0x34,0x35,0x37,0x38,0x39,0x3B,0x3C,0x3D,0x3E,
   0x3F,0x40,0x41,0x43,0x45,0x47,0x49,0x4A,0x4C,0x4E,0x4F,0x51,0x52,0x54,0x55,0x56,
   0x58,0x59,0x5A,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,
   0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6E,0x6F,0x70,0x71,0x71,0x72,0x73,0x74,0x74,0x75,
   0x76,0x76,0x77,0x78,0x78,0x79,0x79,0x7A,0x7B,0x7B,0x7C,0x7D,0x7D,0x7E,0x7E,0x7F,0x80
};

void tc0004vcu_init(void)
{
   int ta,tb=0x00;

   // H-System has non-linear zooming

   for(ta=0x00;ta<0x40;ta++){
      zoom_conv_x[ta]=(ta/2)+0x20;
   }
   for(ta=0x40;ta<0x80;ta++){
      zoom_conv_x[ta]=ta;
   }

   for(ta=0x00;ta<0x80;ta++){
      zoom_conv_y[ta]=0;
   }
   for(ta=0x01;ta<0x80;ta++){
      for(;tb<zoom_table[ta+1];tb++){
         zoom_conv_y[tb]=ta-1;
      }
   }

   GFX_HG0      = tc0004vcu.GFX_FG0;
   RAM_GFX_HG0A = tc0004vcu.RAM + 0x00000;
   RAM_GFX_HG0B = tc0004vcu.RAM + 0x10000;

   memset(GFX_HG0,     0x00,0x4000);
   memset(RAM_GFX_HG0A,0x00,0x1000);
   memset(RAM_GFX_HG0B,0x00,0x1000);

   init_16x16_zoom_32();
   zoom16_ofs = make_16x16_zoom_ofs_type2();
}

void tc0004vcu_gfx_fg0_a_wb(UINT32 addr, UINT8 data)
{
   int tb;

   addr &= 0x0FFF;

   if((RAM_GFX_HG0A[addr^1])!=data){

   // Write to RAM
   // ------------

   RAM_GFX_HG0A[addr^1]=data;

   // Write to 8x8 GFX
   // ----------------

   tb=(addr&0xFFE)<<2;

   if((addr&1)!=0){
      GFX_HG0[tb+0]=(GFX_HG0[tb+0]&0x0E)|(((data&0x80)>>7)<<0);
      GFX_HG0[tb+1]=(GFX_HG0[tb+1]&0x0E)|(((data&0x40)>>6)<<0);
      GFX_HG0[tb+2]=(GFX_HG0[tb+2]&0x0E)|(((data&0x20)>>5)<<0);
      GFX_HG0[tb+3]=(GFX_HG0[tb+3]&0x0E)|(((data&0x10)>>4)<<0);
      GFX_HG0[tb+4]=(GFX_HG0[tb+4]&0x0E)|(((data&0x08)>>3)<<0);
      GFX_HG0[tb+5]=(GFX_HG0[tb+5]&0x0E)|(((data&0x04)>>2)<<0);
      GFX_HG0[tb+6]=(GFX_HG0[tb+6]&0x0E)|(((data&0x02)>>1)<<0);
      GFX_HG0[tb+7]=(GFX_HG0[tb+7]&0x0E)|(((data&0x01)>>0)<<0);
   }
   else{
      GFX_HG0[tb+0]=(GFX_HG0[tb+0]&0x0D)|(((data&0x80)>>7)<<1);
      GFX_HG0[tb+1]=(GFX_HG0[tb+1]&0x0D)|(((data&0x40)>>6)<<1);
      GFX_HG0[tb+2]=(GFX_HG0[tb+2]&0x0D)|(((data&0x20)>>5)<<1);
      GFX_HG0[tb+3]=(GFX_HG0[tb+3]&0x0D)|(((data&0x10)>>4)<<1);
      GFX_HG0[tb+4]=(GFX_HG0[tb+4]&0x0D)|(((data&0x08)>>3)<<1);
      GFX_HG0[tb+5]=(GFX_HG0[tb+5]&0x0D)|(((data&0x04)>>2)<<1);
      GFX_HG0[tb+6]=(GFX_HG0[tb+6]&0x0D)|(((data&0x02)>>1)<<1);
      GFX_HG0[tb+7]=(GFX_HG0[tb+7]&0x0D)|(((data&0x01)>>0)<<1);
   }

   }
}

void tc0004vcu_gfx_fg0_a_ww(UINT32 addr, UINT16 data)
{
   addr&=0xFFE;

   if(ReadWord(&RAM_GFX_HG0A[addr])!=data){

   // Write to RAM
   // ------------

   WriteWord(&RAM_GFX_HG0A[addr],data);

   // Write to 8x8 GFX
   // ----------------

   addr=addr<<2;

   GFX_HG0[addr+0]=(GFX_HG0[addr+0]&0x0C)|(((data&0x8000)>>15)<<1)|(((data&0x0080)>>7)<<0);
   GFX_HG0[addr+1]=(GFX_HG0[addr+1]&0x0C)|(((data&0x4000)>>14)<<1)|(((data&0x0040)>>6)<<0);
   GFX_HG0[addr+2]=(GFX_HG0[addr+2]&0x0C)|(((data&0x2000)>>13)<<1)|(((data&0x0020)>>5)<<0);
   GFX_HG0[addr+3]=(GFX_HG0[addr+3]&0x0C)|(((data&0x1000)>>12)<<1)|(((data&0x0010)>>4)<<0);
   GFX_HG0[addr+4]=(GFX_HG0[addr+4]&0x0C)|(((data&0x0800)>>11)<<1)|(((data&0x0008)>>3)<<0);
   GFX_HG0[addr+5]=(GFX_HG0[addr+5]&0x0C)|(((data&0x0400)>>10)<<1)|(((data&0x0004)>>2)<<0);
   GFX_HG0[addr+6]=(GFX_HG0[addr+6]&0x0C)|(((data&0x0200)>>9)<<1)|(((data&0x0002)>>1)<<0);
   GFX_HG0[addr+7]=(GFX_HG0[addr+7]&0x0C)|(((data&0x0100)>>8)<<1)|(((data&0x0001)>>0)<<0);

   }
}

void tc0004vcu_gfx_fg0_b_wb(UINT32 addr, UINT8 data)
{
   int tb;

   addr&=0xFFF;

   if((RAM_GFX_HG0B[addr^1])!=data){

   // Write to RAM
   // ------------

   RAM_GFX_HG0B[addr^1]=data;

   // Write to 8x8 GFX
   // ----------------

   tb=(addr&0xFFE)<<2;

   if((addr&1)!=0){
      GFX_HG0[tb+0]=(GFX_HG0[tb+0]&0x0B)|(((data&0x80)>>7)<<2);
      GFX_HG0[tb+1]=(GFX_HG0[tb+1]&0x0B)|(((data&0x40)>>6)<<2);
      GFX_HG0[tb+2]=(GFX_HG0[tb+2]&0x0B)|(((data&0x20)>>5)<<2);
      GFX_HG0[tb+3]=(GFX_HG0[tb+3]&0x0B)|(((data&0x10)>>4)<<2);
      GFX_HG0[tb+4]=(GFX_HG0[tb+4]&0x0B)|(((data&0x08)>>3)<<2);
      GFX_HG0[tb+5]=(GFX_HG0[tb+5]&0x0B)|(((data&0x04)>>2)<<2);
      GFX_HG0[tb+6]=(GFX_HG0[tb+6]&0x0B)|(((data&0x02)>>1)<<2);
      GFX_HG0[tb+7]=(GFX_HG0[tb+7]&0x0B)|(((data&0x01)>>0)<<2);
   }
   else{
      GFX_HG0[tb+0]=(GFX_HG0[tb+0]&0x07)|(((data&0x80)>>7)<<3);
      GFX_HG0[tb+1]=(GFX_HG0[tb+1]&0x07)|(((data&0x40)>>6)<<3);
      GFX_HG0[tb+2]=(GFX_HG0[tb+2]&0x07)|(((data&0x20)>>5)<<3);
      GFX_HG0[tb+3]=(GFX_HG0[tb+3]&0x07)|(((data&0x10)>>4)<<3);
      GFX_HG0[tb+4]=(GFX_HG0[tb+4]&0x07)|(((data&0x08)>>3)<<3);
      GFX_HG0[tb+5]=(GFX_HG0[tb+5]&0x07)|(((data&0x04)>>2)<<3);
      GFX_HG0[tb+6]=(GFX_HG0[tb+6]&0x07)|(((data&0x02)>>1)<<3);
      GFX_HG0[tb+7]=(GFX_HG0[tb+7]&0x07)|(((data&0x01)>>0)<<3);
   }

   }
}

void tc0004vcu_gfx_fg0_b_ww(UINT32 addr, UINT16 data)
{
   addr&=0xFFE;

   if(ReadWord(&RAM_GFX_HG0B[addr])!=data){

   // Write to RAM
   // ------------

   WriteWord(&RAM_GFX_HG0B[addr],data);

   // Write to 8x8 GFX
   // ----------------

   addr=addr<<2;

   GFX_HG0[addr+0]=(GFX_HG0[addr+0]&0x03)|(((data&0x8000)>>15)<<3)|(((data&0x0080)>>7)<<2);
   GFX_HG0[addr+1]=(GFX_HG0[addr+1]&0x03)|(((data&0x4000)>>14)<<3)|(((data&0x0040)>>6)<<2);
   GFX_HG0[addr+2]=(GFX_HG0[addr+2]&0x03)|(((data&0x2000)>>13)<<3)|(((data&0x0020)>>5)<<2);
   GFX_HG0[addr+3]=(GFX_HG0[addr+3]&0x03)|(((data&0x1000)>>12)<<3)|(((data&0x0010)>>4)<<2);
   GFX_HG0[addr+4]=(GFX_HG0[addr+4]&0x03)|(((data&0x0800)>>11)<<3)|(((data&0x0008)>>3)<<2);
   GFX_HG0[addr+5]=(GFX_HG0[addr+5]&0x03)|(((data&0x0400)>>10)<<3)|(((data&0x0004)>>2)<<2);
   GFX_HG0[addr+6]=(GFX_HG0[addr+6]&0x03)|(((data&0x0200)>>9)<<3)|(((data&0x0002)>>1)<<2);
   GFX_HG0[addr+7]=(GFX_HG0[addr+7]&0x03)|(((data&0x0100)>>8)<<3)|(((data&0x0001)>>0)<<2);

   }
}

/******************************************************************************/

void tc0004vcu_render_bg0(void)
{
   int x,y,x16,y16,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_BG_B;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0004vcu.RAM + 0x0C000;
   RAM_BG_B  = tc0004vcu.RAM + 0x1C000;
   RAM_SCR   = tc0004vcu.RAM + 0x20802;
   RAM_GFX   = tc0004vcu.GFX_BG0;
   tile_mask = tc0004vcu.tile_mask;

   bmp_x = tc0004vcu.bmp_x;
   bmp_y = tc0004vcu.bmp_y;
   bmp_w = tc0004vcu.bmp_w;
   bmp_h = tc0004vcu.bmp_h;
   scr_x = tc0004vcu.scr_x;
   scr_y = tc0004vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y+(ReadWord(RAM_SCR+4))
      );

      START_SCROLL_1024x1024_2_16(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG_B[zz]&0x3F,
            16,
            map
         );

      switch(RAM_BG_B[zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map); break;
      }

      END_SCROLL_1024x1024_2_16();
}

void tc0004vcu_render_bg1(void)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_BG_B;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0004vcu.RAM + 0x0E000;
   RAM_BG_B  = tc0004vcu.RAM + 0x1E000;
   RAM_SCR   = tc0004vcu.RAM + 0x20804;
   RAM_GFX   = tc0004vcu.GFX_BG0;
   RAM_MSK   = tc0004vcu.GFX_BG0_MSK;
   tile_mask = tc0004vcu.tile_mask;

   bmp_x = tc0004vcu.bmp_x;
   bmp_y = tc0004vcu.bmp_y;
   bmp_w = tc0004vcu.bmp_w;
   bmp_h = tc0004vcu.bmp_h;
   scr_x = tc0004vcu.scr_x;
   scr_y = tc0004vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y+(ReadWord(RAM_SCR+4))
      );

      START_SCROLL_1024x1024_2_16(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG_B[zz]&0x3F,
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG_B[zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG_B[zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }

      }

      END_SCROLL_1024x1024_2_16();
}

void tc0004vcu_render_fg0(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0004vcu.RAM + 0x01000;
   GFX_BG    = tc0004vcu.GFX_FG0;

   bmp_x = tc0004vcu.bmp_x;
   bmp_y = tc0004vcu.bmp_y;
   bmp_w = tc0004vcu.bmp_w;
   bmp_h = tc0004vcu.bmp_h;
   scr_x = tc0004vcu.scr_x;
   scr_y = tc0004vcu.scr_y;

   tx = 64-(bmp_w>>3);

      MAKE_SCROLL_512x512_1_8_no16(
         scr_x, //-(ReadWord(RAM_SCR+0)),
         scr_y  //+(ReadWord(RAM_SCR+4))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<(bmp_h+bmp_y);y+=8,zz+=tx){
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz++){

      ta=RAM_BG[zz^1];
      if(ta!=0){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            32,
            16,
            map
         );

         Draw8x8_Trans_Mapped_Rot(&GFX_BG[ta<<6],x,y,map);

      }

      }
      }
}

static UINT32 chain_y_size[4] =
{
   1,	// 64x16: OK
   2,	// 64x32: ?
   4,	// 64x64: OK
   4,	// 64x64: ?
};

void tc0004vcu_render_obj(void)
{
   int x,y,zz,ta,td;
   int rx,ry,x_store,zx,zy;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *zdx_store;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT8 *RAM_CH;
   UINT8 *RAM_CH_B;
   UINT32 tile_mask;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;

   RAM_BG    = tc0004vcu.RAM + 0x20400;
   RAM_GFX   = tc0004vcu.GFX_BG0;
   RAM_MSK   = tc0004vcu.GFX_BG0_MSK;
   RAM_CH    = tc0004vcu.RAM + 0x00000;
   RAM_CH_B  = tc0004vcu.RAM + 0x10000;
   tile_mask = tc0004vcu.tile_mask;

   sx_1      = tc0004vcu.bmp_x;
   sy_1      = tc0004vcu.bmp_y;
   sx_2      = tc0004vcu.bmp_x + tc0004vcu.bmp_w;
   sy_2      = tc0004vcu.bmp_y + tc0004vcu.bmp_h;
   ofs_x     = tc0004vcu.bmp_x - tc0004vcu.scr_x;
   ofs_y     = tc0004vcu.bmp_y - tc0004vcu.scr_y;

   zz = 0x03F0;
   do{

      if(ReadWord(&RAM_BG[zz+4])!=0x0000){

   x_store    = (ofs_x+ReadWord(&RAM_BG[zz+2]))&OBJ_X_MASK;
   y          = (ofs_y+ReadWord(&RAM_BG[zz+0]))&OBJ_Y_MASK;

   td         = ((ReadWord(&RAM_BG[zz+6])&0x1FFF)<<3);

   zdx_store  = zoom16_ofs+(zoom_conv_x[(RAM_BG[zz+5]&0x7F)]<<2);
   //zoom_dat_y = zoom16_ofs+(zoom_conv_y[(RAM_BG[zz+4]&0x7F)]<<2);
   zoom_dat_y = zoom16_ofs+(zoom_conv_x[(RAM_BG[zz+5]&0x7F)]<<2);

   ry         = chain_y_size[(ReadWord(&RAM_BG[zz])>>10)&0x03];

   do{
   x          = x_store;
   rx         = 4;
   zoom_dat_x = zdx_store;
   zy         = *zoom_dat_y++;
   do{
      zx = *zoom_dat_x++;
      if(((x+zx) > sx_1) && (x < sx_2)){
      if(((y+zy) > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_CH[td])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM_CH_B[td]&0x3F,
         16,
         map
      );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_CH_B[td]&0xC0){
               case 0x00: Draw16x16_32_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x40: Draw16x16_32_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x80: Draw16x16_32_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_32_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_CH_B[td]&0xC0){
               case 0x00: Draw16x16_32_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x40: Draw16x16_32_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x80: Draw16x16_32_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_32_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }
      }
      }
      x = (x+zx)&OBJ_X_MASK;
      td += 2;
   }while(--rx);
   y = (y+zy)&OBJ_Y_MASK;
   }while(--ry);

   }

   }while((zz-=8)>=0);

}

/******************************************************************************/
