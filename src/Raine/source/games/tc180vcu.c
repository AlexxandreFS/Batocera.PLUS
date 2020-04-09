/******************************************************************************/
/*                                                                            */
/*                tc0180vcu: TAITO VIDEO CHIP UNIT (B-SYSTEM)                 */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc180vcu.h"
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines
#include "blit.h"

struct VIDEO_INFO b_system_video =
{
   draw_b_system,
   320,
   224,
   32,
   VIDEO_ROTATE_NORMAL |
   VIDEO_ROTATABLE,
};

struct VIDEO_INFO b_system_r180_video =
{
   draw_b_system,
   320,
   224,
   32,
   VIDEO_ROTATE_180 |
   VIDEO_ROTATABLE,
};

void draw_b_system(void)
{
   ClearPaletteMap();

   tc0180vcu_layer_count = 0;

   vcu_render_bg0();

   vcu_render_bg1();

   vcu_render_obj(0x200);

   vcu_render_bg2();
}

/*

tc0180vcu info
--------------

Screen: 320x224
Colour: 12-bit RGBx

------------+--------------------------
Address     | Use
------------+--------------------------
00000-01FFF | BG0 RAM (tile)
02000-03FFF | BG0 RAM (colour and flip)
04000-05FFF | BG1 RAM (tile)
06000-07FFF | BG1 RAM (colour and flip)
08000-08FFF | FG0 RAM (bank 0)
09000-09FFF | FG0 RAM (bank 1)
0A000-0AFFF | FG0 RAM (bank 2)
0B000-0BFFF | FG0 RAM (bank 3)
0C000-0DFFF | BG? RAM (tile)
0E000-0FFFF | BG? RAM (colour and flip)
10000-11FFF | OBJECT RAM
13800-13803 | BG0 SCROLL
13C00-13C03 | BG1 SCROLL
18000-1801F | PIXEL SCROLL/CTRL
40000-5FFFF | PIXEL RAM (bank 0)
60000-7FFFF | PIXEL RAM (bank 1)
------------+--------------------------

BG0-BG1 RAM
-----------

-----+--------+----------------------
Byte | Bit(s) | Use
-----+76543210+----------------------
0000 |...xxxxx| Tile (high)
0001 |xxxxxxxx| Tile (low)
2000 |x.......| Flip X Axis
2000 |.x......| Flip Y Axis
2001 |++xxxxxx| Colour Bank
-----+--------+----------------------

BG2 RAM [FG0]
-------------

-----+--------+----------------------
Byte | Bit(s) | Use
-----+76543210+----------------------
  0  |xxxx....| Colour Bank
  0  |....xxxx| Tile (high)
  1  |xxxxxxxx| Tile (low)
-----+--------+----------------------

OBJECT RAM [SPRITES]
--------------------

-----+--------+----------------------
Byte | Bit(s) | Use
-----+76543210+----------------------
  0  |...xxxxx| Sprite Number (High)
  1  |xxxxxxxx| Sprite Number (Low)
  2  |.x......| Flip Y Axis
  2  |x.......| Flip X Axis
  3  |..++xxxx| Colour Bank
  4  |++++++xx| XPos (High)
  5  |xxxxxxxx| XPos (Low)
  6  |++++++xx| YPos (High)
  7  |xxxxxxxx| YPos (Low)
  8  |xxxxxxx+| Zoom X
  9  |xxxxxxx+| Zoom Y
  A  |...xxxxx| Chain X
  B  |...xxxxx| Chain Y
-----+--------+----------------------

. = unused bit
x = used bit
+ = sometimes used bit

Zoom:

00 = Full size sprites
FF = Min size sprites

Priority Based on Colour Bank:

Colour & 0x01 = Sprite:BG1 Priority

Problem Case:

Ashura Blaster Level 1 Start

PIXEL SCROLL RAM
----------------

-----+--------+----------------------
Byte | Bit(s) | Use
-----+76543210+----------------------
  C  |....xxxx| BG2 Bank (0x00-0x0F)
  E  |.......x| Sprites Stay Onscreen
  E  |.x......| Pixel Bank (0x00-0x01)
-----+--------+----------------------

PIXEL A/B RAM
-------------

- 512x256

Not implemented:

- Sprite-BG1 priority.
- Sprite zooming is not in asm.
- BG2 (FG0) is probably scrollable (Hit the Ice test hatch).
- BG2 (FG0) tiles are probably bank switchable (Silent Dragon).

Normal:

Crime City		- OK
Rastan 2		- OK
Silent Dragon		- OK <trash on attract mode>
Space Invaders DX	- OK <pixel>
Taito Tetris		- ?? <pixel only>

180:

Hit the Ice             - OK
Rambo 3                 - OK
Violence Fight		- OK

270:

Ashura Blaster		- OK
Master of Weapons	- OK <title screen problems>

*/

#define OBJ_X_MASK	0x3FF
#define OBJ_Y_MASK	0x3FF

static UINT8 col_remap[4][0x40];

static UINT8 *zoom16_ofs;

static BITMAP *pixel_bitmap;
static BITMAP *bitmap_store;
static int pixel_blit;
static UINT8 map_data[256];
static UINT8 mapped[256];
static UINT8 mapping[16];
static UINT8 map_bored[256];
static int map_count;

void vcu_make_col_bankmap(UINT8 mask, UINT8 ofs_0, UINT8 ofs_1, UINT8 ofs_2, UINT8 ofs_3)
{
   int ta;

   mask -= 1;

   ofs_0 &= ~mask;
   ofs_1 &= ~mask;
   ofs_2 &= ~mask;
   ofs_3 &= ~mask;

   for(ta=0; ta<0x40; ta++){
      col_remap[0][ta] = (ta & mask) | ofs_0;
      col_remap[1][ta] = (ta & mask) | ofs_1;
      col_remap[2][ta] = (ta & mask) | ofs_2;
      col_remap[3][ta] = (ta & mask) | ofs_3;
   }

   init_16x16_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1();

   if(pixel_bitmap) destroy_bitmap(pixel_bitmap);

   pixel_bitmap = create_bitmap(tc0180vcu.bmp_w+64,tc0180vcu.bmp_h+64);

   clear_bitmap(pixel_bitmap);

   pixel_blit=0;

   map_count=0;

   for(ta=0;ta<256;ta++){
      map_data[ta]=ta;
      if(!(ta&15)) map_data[ta]=0;
   }

   memset(mapped,255,256);
}

void vcu_debug_info(void)
{
/*
   #ifdef RAINE_DEBUG
   UINT8 *src;

   src = tc0180vcu.RAM_2;

   if(src){

   print_ingame(120,"[Scroll/Ctrl]");
   print_ingame(120,"00:%04x %04x %04x %04x",ReadWord(&src[0x00]),ReadWord(&src[0x02]),ReadWord(&src[0x04]),ReadWord(&src[0x06]));
   print_ingame(120,"08:%04x %04x %04x %04x",ReadWord(&src[0x08]),ReadWord(&src[0x0A]),ReadWord(&src[0x0C]),ReadWord(&src[0x0E]));
   print_ingame(120,"10:%04x %04x %04x %04x",ReadWord(&src[0x10]),ReadWord(&src[0x12]),ReadWord(&src[0x14]),ReadWord(&src[0x16]));
   print_ingame(120,"18:%04x %04x %04x %04x",ReadWord(&src[0x18]),ReadWord(&src[0x1A]),ReadWord(&src[0x1C]),ReadWord(&src[0x1E]));

   }
   #endif
*/
}

/******************************************************************************/

void vcu_render_bg0(void)
{
   int x,y,x16,y16,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0180vcu.RAM + 0x04000;
   RAM_SCR   = tc0180vcu.RAM + 0x13C00;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   tile_mask = tc0180vcu.tile_mask;

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+2))
      );

      START_SCROLL_1024x1024_2_16(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            col_remap[0][RAM_BG[0x2000+zz]&0x3F],
            16,
            map
         );

      switch(RAM_BG[0x2000+zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map); break;
      }

      END_SCROLL_1024x1024_2_16();
}

void vcu_render_bg1(void)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0180vcu.RAM + 0x00000;
   RAM_SCR   = tc0180vcu.RAM + 0x13800;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   RAM_MSK   = tc0180vcu.GFX_BG0_MSK;
   tile_mask = tc0180vcu.tile_mask;

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+2))
      );

      START_SCROLL_1024x1024_2_16(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            col_remap[1][RAM_BG[0x2000+zz]&0x3F],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[0x2000+zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[0x2000+zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }

      }

      END_SCROLL_1024x1024_2_16();
}

void vcu_render_bg2(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *GFX_BG;
   UINT8 *RAM_MSK;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0180vcu.RAM + 0x08000;
   // RAM_SCR   = NULL;
   GFX_BG    = tc0180vcu.GFX_BG2;
   RAM_MSK   = tc0180vcu.GFX_BG2_MSK;

   if(tc0180vcu.RAM_2){
      RAM_BG = tc0180vcu.RAM + ((ReadWord(&tc0180vcu.RAM_2[0x0C])&0x0F00)<<4);
   }

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

   tx = 128-(bmp_w>>2);

      MAKE_SCROLL_512x256_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+2))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<bmp_h+bmp_y;y+=8,zz+=tx){
      for(x=bmp_x;(UINT32)x<bmp_w+bmp_x;x+=8,zz+=2){

      ta=ReadWord(&RAM_BG[zz])&0xFFF;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            col_remap[3][RAM_BG[1+zz]>>4],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            Draw8x8_Trans_Mapped_Rot(&GFX_BG[ta<<6],x,y,map);
         }
         else{					// all pixels; solid
            Draw8x8_Mapped_Rot(&GFX_BG[ta<<6],x,y,map);
         }

      }

      }
      }
}

#define silentd_spr_test \
((RAM_BG[zz+3]&0x3f) || (ta==0x4000) || (ta==0x4040) || (ta==0xb0b) || (ta==0x7f7f))

void vcu_render_obj(UINT32 num)
{
   int x,y,zz,ta,tx,ty;
   int rx,ry,y_store,ry_store;
   int zx,zy,tc;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;

   RAM_BG    = tc0180vcu.RAM + 0x10000;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   RAM_MSK   = tc0180vcu.GFX_BG0_MSK;
   tile_mask = tc0180vcu.tile_mask;

   sx_1      = tc0180vcu.bmp_x - 16;
   sy_1      = tc0180vcu.bmp_y - 16;
   sx_2      = tc0180vcu.bmp_x + tc0180vcu.bmp_w;
   sy_2      = tc0180vcu.bmp_y + tc0180vcu.bmp_h;
   ofs_x     = tc0180vcu.bmp_x - tc0180vcu.scr_x;
   ofs_y     = tc0180vcu.bmp_y - tc0180vcu.scr_y;

   if(tc0180vcu.RAM_2){
       if(ReadWord(&tc0180vcu.RAM_2[0x0E])&0x0100){
	   if (!is_current_game("silentd"))
	       pixel_blit=1;
       }
       else{
	   if(pixel_blit) clear_bitmap(pixel_bitmap);
	   map_count=0;
	   pixel_blit=0;
	   memset(mapped,255,256);
       }
   }
   else{
      pixel_blit=0;
   }

   if(pixel_blit){
      bitmap_store = GameBitmap;
      GameBitmap = pixel_bitmap;
      init_spr16x16asm_8();

   zz = (0x1980-16);
   do{

   x        = (ofs_x+ReadWord(&RAM_BG[zz+4]))&OBJ_X_MASK;
   y_store  = (ofs_y+ReadWord(&RAM_BG[zz+6]))&OBJ_Y_MASK;

   rx       = RAM_BG[zz+11]&0x1F;
   ry_store = RAM_BG[zz+10]&0x1F;

   zoom_dat_x = zoom16_ofs+(RAM_BG[zz+9]<<5);
   zoom_dat_y = zoom16_ofs+(RAM_BG[zz+8]<<5);

   tx=0;
   do{
   y  = y_store;
   ry = ry_store;
   ty = 0;
   zx = zoom_dat_x[tx++];
   do{
      zy = zoom_dat_y[ty++];

      if((x > sx_1) && (x < sx_2)){
      if((y > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

      tc = col_remap[2][RAM_BG[2+zz]&0x3F];

      if(mapped[tc] == 255 ){
         mapped[tc] = map_count;
         mapping[map_count>>4] = tc;
         map_count += 16;
         map_count &= 255;
      }

      map = &map_data[mapped[tc]];

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x40: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x80: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x40: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x80: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }
      }
      }
      y = (y+zy)&OBJ_Y_MASK;
      zz -= 16;
   }while(ry--);
   x = (x+zx)&OBJ_X_MASK;
   }while(rx--);

   }while(zz>=0);

   for(ta=0;ta<map_count;ta+=16){
      MAP_PALETTE_MAPPED_NEW(
         mapping[ta>>4],
         16,
         map
      );
      for(tc=0;tc<16;tc++)
         map_bored[tc+ta]=map[tc];
   }

      GameBitmap = bitmap_store;
      init_spr16x16asm_8();

   for(ty=32;(UINT32)ty<32+tc0180vcu.bmp_h;ty++){
   for(tx=32;(UINT32)tx<32+tc0180vcu.bmp_w;tx++){
      GameBitmap->line[ty][tx] = map_bored[pixel_bitmap->line[ty][tx]];
   }
   }
      //blit(pixel_bitmap,GameBitmap,32,32,32,32,tc0180vcu.bmp_w,tc0180vcu.bmp_h);

   }
   else{

   zz = (num-1)<<4;
   do{

   x        = (ofs_x+ReadWord(&RAM_BG[zz+4]))&OBJ_X_MASK;
   y_store  = (ofs_y+ReadWord(&RAM_BG[zz+6]))&OBJ_Y_MASK;

   rx       = RAM_BG[zz+11]&0x1F;
   ry_store = RAM_BG[zz+10]&0x1F;

   zoom_dat_x = zoom16_ofs+(RAM_BG[zz+9]<<5);
   zoom_dat_y = zoom16_ofs+(RAM_BG[zz+8]<<5);

   tx=0;
   do{
   y  = y_store;
   ry = ry_store;
   ty = 0;
   zx = zoom_dat_x[tx++];
   do{
      zy = zoom_dat_y[ty++];

      if((x > sx_1) && (x < sx_2)){
      if((y > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if((RAM_MSK[ta]!=0) && !(is_current_game("silentd") && silentd_spr_test)){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         col_remap[2][RAM_BG[2+zz]&0x3F],
         16,
         map
      );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x40: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x80: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x40: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x80: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }
      }
      }
      y = (y+zy)&OBJ_Y_MASK;
      zz -= 16;
   }while(ry--);
   x = (x+zx)&OBJ_X_MASK;
   }while(rx--);

   }while(zz>=0);

   }
}

/******************************************************************************/

void vcu_render_bg0_r270(void)
{
   int x,y,x16,y16,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0180vcu.RAM + 0x04000;
   RAM_SCR   = tc0180vcu.RAM + 0x13C00;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   tile_mask = tc0180vcu.tile_mask;

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_y-(ReadWord(RAM_SCR+0)),
         scr_x-(ReadWord(RAM_SCR+2))
      );

      START_SCROLL_1024x1024_2_16_R270(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            col_remap[0][RAM_BG[0x2000+zz]&0x3F],
            16,
            map
         );

      switch(RAM_BG[0x2000+zz]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);        break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);  break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[zz])&tile_mask)<<8],x,y,map); break;
      }

      END_SCROLL_1024x1024_2_16();
}

void vcu_render_bg1_r270(void)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0180vcu.RAM + 0x00000;
   RAM_SCR   = tc0180vcu.RAM + 0x13800;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   RAM_MSK   = tc0180vcu.GFX_BG0_MSK;
   tile_mask = tc0180vcu.tile_mask;

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_y-(ReadWord(RAM_SCR+0)),
         scr_x-(ReadWord(RAM_SCR+2))
      );

      START_SCROLL_1024x1024_2_16_R270(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            col_remap[1][RAM_BG[0x2000+zz]&0x3F],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[0x2000+zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[0x2000+zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x80: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x40: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }

      }

      END_SCROLL_1024x1024_2_16();
}

void vcu_render_bg2_r270(void)
{
   int x,y,zzzz,zzz,zz,ta,tx;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *GFX_BG;
   UINT8 *RAM_MSK;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG    = tc0180vcu.RAM + 0x08000;
   // RAM_SCR   = NULL;
   GFX_BG    = tc0180vcu.GFX_BG2;
   RAM_MSK   = tc0180vcu.GFX_BG2_MSK;

   if(tc0180vcu.RAM_2){
      RAM_BG = tc0180vcu.RAM + ((ReadWord(&tc0180vcu.RAM_2[0x0C])&0x0F00)<<4);
   }

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

   tx = 128-(bmp_h>>2);

      MAKE_SCROLL_512x256_2_8_no16(
         scr_y,		//-(ReadWord(RAM_SCR+0)),
         scr_x		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=tx){
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=2){

      ta=ReadWord(&RAM_BG[zz])&0xFFF;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            col_remap[3][RAM_BG[1+zz]>>4],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            Draw8x8_Trans_Mapped_Rot(&GFX_BG[ta<<6],x,y,map);
         }
         else{					// all pixels; solid
            Draw8x8_Mapped_Rot(&GFX_BG[ta<<6],x,y,map);
         }

      }

      }
      }
}

void vcu_render_obj_r270(int pri)
{
   int x,y,zz,ta,tx,ty;
   int rx,ry,x_store,rx_store;
   int zx,zy,tc,tp;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;

   tp=1;
   if(pri!=0) tp=0;

   RAM_BG    = tc0180vcu.RAM + 0x10000;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   RAM_MSK   = tc0180vcu.GFX_BG0_MSK;
   tile_mask = tc0180vcu.tile_mask;

   sx_1      = tc0180vcu.bmp_x - 16;
   sy_1      = tc0180vcu.bmp_y - 16;
   sx_2      = tc0180vcu.bmp_x + tc0180vcu.bmp_w;
   sy_2      = tc0180vcu.bmp_y + tc0180vcu.bmp_h;
   ofs_x     = tc0180vcu.bmp_x - tc0180vcu.scr_x;
   ofs_y     = (tc0180vcu.bmp_y + tc0180vcu.bmp_h) + tc0180vcu.scr_y;

   if(tc0180vcu.RAM_2){
   if(ReadWord(&tc0180vcu.RAM_2[0x0E])&0x0100){
      pixel_blit=1;
   }
   else{
      if(pixel_blit) clear_bitmap(pixel_bitmap);
      map_count=0;
      pixel_blit=0;
      memset(mapped,255,256);
   }
   }
   else{
      pixel_blit=0;
   }

   if(pixel_blit){

   if(tp==0){

      bitmap_store = GameBitmap;
      GameBitmap = pixel_bitmap;
      init_spr16x16asm_8();

   zz = 0x1FF0;
   do{

   y        = (ofs_y-ReadWord(&RAM_BG[zz+4]))&OBJ_X_MASK;
   x_store  = (ofs_x+ReadWord(&RAM_BG[zz+6]))&OBJ_Y_MASK;

   ry       = RAM_BG[zz+11]&0x1F;
   rx_store = RAM_BG[zz+10]&0x1F;

   zoom_dat_x = zoom16_ofs+(RAM_BG[zz+8]<<5);
   zoom_dat_y = zoom16_ofs+(RAM_BG[zz+9]<<5);

   ty = ry;
   do{
   x  = x_store;
   rx = rx_store;
   tx = 0;
   zy = zoom_dat_y[ty--];
   y  = (y-zy)&OBJ_X_MASK;
   do{
      zx = zoom_dat_x[tx++];

      if((x > sx_1) && (x < sx_2)){
      if((y > sy_1) && (y < sy_2)){

      tc = RAM_BG[2+zz]&0x3F;

      //if((tc&0x01)==tp){

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

      tc = col_remap[2][tc];

      if(mapped[tc] == 255 ){
         mapped[tc] = map_count;
         mapping[map_count>>4] = tc;
         map_count += 16;
         map_count &= 255;
      }

      map = &map_data[mapped[tc]];

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x80: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x40: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x80: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x40: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }//}
      }
      }
      x = (x+zx)&OBJ_Y_MASK;
      zz -= 16;
   }while(rx--);
   }while(ry--);

   }while(zz>=0);

   for(ta=0;ta<map_count;ta+=16){
      MAP_PALETTE_MAPPED_NEW(
         mapping[ta>>4],
         16,
         map
      );
      for(tc=0;tc<16;tc++)
         map_bored[tc+ta]=map[tc];
   }

      GameBitmap = bitmap_store;
      init_spr16x16asm_8();

   for(ty=32;(UINT32)ty<32+tc0180vcu.bmp_h;ty++){
   for(tx=32;(UINT32)tx<32+tc0180vcu.bmp_w;tx++){
      GameBitmap->line[ty][tx] = map_bored[pixel_bitmap->line[ty][tx]];
   }
   }

   }

   }
   else{

   zz = 0x1FF0;
   do{

   y        = (ofs_y-ReadWord(&RAM_BG[zz+4]))&OBJ_X_MASK;
   x_store  = (ofs_x+ReadWord(&RAM_BG[zz+6]))&OBJ_Y_MASK;

   ry       = RAM_BG[zz+11]&0x1F;
   rx_store = RAM_BG[zz+10]&0x1F;

   zoom_dat_x = zoom16_ofs+(RAM_BG[zz+8]<<5);
   zoom_dat_y = zoom16_ofs+(RAM_BG[zz+9]<<5);

   ty = ry;
   do{
   x  = x_store;
   rx = rx_store;
   tx = 0;
   zy = zoom_dat_y[ty--];
   y  = (y-zy)&OBJ_X_MASK;
   do{
      zx = zoom_dat_x[tx++];

      if((x > sx_1) && (x < sx_2)){
      if((y > sy_1) && (y < sy_2)){

      tc = RAM_BG[2+zz]&0x3F;

      if((tc&0x01)==tp){

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         col_remap[2][tc],
         16,
         map
      );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x80: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x40: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+3]&0xC0){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x80: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x40: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0xC0: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }}
      }
      }
      x = (x+zx)&OBJ_Y_MASK;
      zz -= 16;
   }while(rx--);
   }while(ry--);

   }while(zz>=0);

   }
}

/******************************************************************************/

#define bg_test	(bg==1) || ((bg==0)&&(pri==0x3200))

void vcu_render_ryujin_bg(int bg, int pri)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta,p;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   if (bg==0)
     RAM_BG  = tc0180vcu.RAM + 0x04000;
   else
     RAM_BG  = tc0180vcu.RAM + 0x00000;
   if (((bg==0)&&(pri==0x3200)) || ((bg==1)&&(pri!=0x3200)))
     RAM_SCR = tc0180vcu.RAM + 0x13800;
   else
     RAM_SCR = tc0180vcu.RAM + 0x13C00;
   RAM_GFX   = tc0180vcu.GFX_BG0;
   RAM_MSK   = tc0180vcu.GFX_BG0_MSK;
   tile_mask = tc0180vcu.tile_mask;

   bmp_x = tc0180vcu.bmp_x;
   bmp_y = tc0180vcu.bmp_y;
   bmp_w = tc0180vcu.bmp_w;
   bmp_h = tc0180vcu.bmp_h;
   scr_x = tc0180vcu.scr_x;
   scr_y = tc0180vcu.scr_y;

      MAKE_SCROLL_1024x1024_2_16(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+2))
      );

      START_SCROLL_1024x1024_2_16(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(!((RAM_MSK[ta]==0) && (bg_test))){			// No pixels; skip

	 if (((bg==0)&&(pri==0x3200)) || ((bg==1)&&(pri!=0x3200)))
	   p = 1;
	 else p = 0;

         MAP_PALETTE_MAPPED_NEW(
            col_remap[p][RAM_BG[0x2000+zz]&0x3F],
            16,
            map
         );

         if((RAM_MSK[ta]==1) && (bg_test)){			// Some pixels; trans
            switch(RAM_BG[0x2000+zz]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{							// all pixels; solid
            switch(RAM_BG[0x2000+zz]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }

      }

      END_SCROLL_1024x1024_2_16();
}
