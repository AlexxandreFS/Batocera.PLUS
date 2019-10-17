/******************************************************************************/
/*                                                                            */
/*              tc0200obj: TAITO OBJECT LAYER CHIP (F2-SYSTEM)                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc200obj.h"
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines

/*

This chip mainly exists in F2-System games.
It seems to behave slightly differently in most games (banking methods,
disable methods, offset methods). Horrible.

OBJECT RAM
----------

- 16 bytes/sprite
- 1024 sprites (0x4000 bytes)

-----+--------+-----------------------------------------------------------------
Byte | Bit(s) | Use
-----+76543210+-----------------------------------------------------------------
  0  |xxxxxxxx| Sprite Tile (high)
  1  |xxxxxxxx| Sprite Tile (low)
  2  |xxxxxxxx| Zoom Y
  3  |xxxxxxxx| Zoom X
  4  |.x......| Add Relative X and Y offsets [Final Blow]
  4  |.x......| Reset Relative X and Y offsets to 0 [Liquid Kids/Don Doko Don]
  4  |....xxxx| Sprite X (high)
  5  |xxxxxxxx| Sprite X (low)
  6  |x.......| Disable/Enable Sprites [Gun Frontier/Metal Black/Football Champ/Dead Connection]
  6  |....xxxx| Sprite Y (high)
  7  |xxxxxxxx| Sprite Y (low)
  8  |.....x..| Update Colour Bank and Zoom X/Y registers
  8  |......x.| Flip X Axis
  8  |.......x| Flip Y Axis
  9  |xxxxxxxx| Colour Bank
  A  |x.......| Jump to sprite Flag [Darius Gaiden]
  A  |....x...| Jump to sprite Bank A/B [Darius Gaiden]
  A  |......xx| Jump to sprite Number (high) [Darius Gaiden]
  B  |xxxxxxxx| Jump to sprite Number (low) [Darius Gaiden]
  B  |.......x| Last Sprite Marker
  D  |.......x| Last Sprite Marker (alt)
-----+--------+-----------------------------------------------------------------

Zoom:

00 = Full Size (16 sprites would span 256 pixels)
FF = Min Size  (16 sprites would span 1 pixel)

Direct Mapped Games:

Mega Blast              - OK
Thunder Fox             - OK
Camel Try               - OK [Colour Based Priorities]

Mapped 64 Colour Games:

Final Blow              - OK

Direct Mapped Rotate 180° Games:

Liquid Kids             - OK [Control bits work differently]
Don Doko Don            - OK [Control bits work differently]

Mapped Rotate 270° Games:

Gun Frontier            - OK

render_tc0200obj_mapped_f3system_b:

Arkanoid Returns        - ?
Puzzle Bobble 2         - OK
Puzzle Bobble 3         - OK
Puzzle Bobble 4         - OK
Pop'n Pop               - OK
Puchi Carat             - OK

render_tc0200obj_mapped_fchamp:

Dead Connection         - OK [bank 0x0A]
Football Champ          - OK [bank ????]
Euro Champ 92           - OK [bank ????]

*/

/* Yeah quite horrible indeed. Anyway mame has done an incredible work about this chip too
   I almost converted "as is" their draw_sprite function for the taito f2 driver.
   Here is their information :

		Sprite format:
		0000: ---xxxxxxxxxxxxx tile code (0x0000 - 0x1fff)
		0002: xxxxxxxx-------- sprite y-zoom level
		      --------xxxxxxxx sprite x-zoom level

			  0x00 - non scaled = 100%
			  0x80 - scaled to 50%
			  0xc0 - scaled to 25%
			  0xe0 - scaled to 12.5%
			  0xff - scaled to zero pixels size (off)

		[this zoom scale may not be 100% correct, see Gunfront flame screen]

		0004: ----xxxxxxxxxxxx x-coordinate (-0x800 to 0x07ff)
		      ---x------------ latch extra scroll
		      --x------------- latch master scroll
		      -x-------------- don't use extra scroll compensation
		      x--------------- absolute screen coordinates (ignore all sprite scrolls)
		      xxxx------------ the typical use of the above is therefore
		                       1010 = set master scroll
		                       0101 = set extra scroll
		0006: ----xxxxxxxxxxxx y-coordinate (-0x800 to 0x07ff)
		      x--------------- marks special control commands (used in conjunction with 00a)
		                       If the special command flag is set:
		      ---------------x related to sprite ram bank
		      ---x------------ unknown (deadconx, maybe others)
		      --x------------- unknown, some games (growl, gunfront) set it to 1 when
		                       screen is flipped
		0008: --------xxxxxxxx color (0x00 - 0xff)
		      -------x-------- flipx
		      ------x--------- flipy
		      -----x---------- if set, use latched color, else use & latch specified one
		      ----x----------- if set, next sprite entry is part of sequence
		      ---x------------ if clear, use latched y coordinate, else use current y
		      --x------------- if set, y += 16
		      -x-------------- if clear, use latched x coordinate, else use current x
		      x--------------- if set, x += 16
		000a: only valid when the special command bit in 006 is set
		      ---------------x related to sprite ram bank. I think this is the one causing
		                       the bank switch, implementing it this way all games seem
		                       to properly bank switch except for footchmp which uses the
		                       bit in byte 006 instead.
		      ------------x--- unknown; some games toggle it before updating sprite ram.
		      ------xx-------- unknown (finalb)
		      -----x---------- unknown (mjnquest)
		      ---x------------ disable the following sprites until another marker with
			                   this bit clear is found
		      --x------------- flip screen

		000b - 000f : unused

		See the render_tc0200obj_mapped function for the implementation.
		The goal is to remove as many functions (exceptions) from this file
		as possible (because 1 function is MUCH easier to maintain).
*/

#define OBJ_XY_MASK	0xFFF

static UINT8 *zoom16_ofs;

static int object_id,f2_sprite_type,f2_x_offset/* ,sprites_flipscreen */;

static int master_scrollx,master_scrolly,disabled,sx_1,sy_1,sx_2,sy_2;

static UINT8 *RAM_BG,*RAM_GFX,*RAM_MSK;

static UINT32 tile_mask;
UINT16 *f2_sprite_extension = NULL;
static UINT16 bank_data[8];
UINT16 f2_sprites_colors;

void init_tc0200obj(void)
{
  int i;
  for (i=0; i<8; i++)
    bank_data[i] = 0x400 * i;

   init_16x16_zoom();
   zoom16_ofs = make_16x16_zoom_ofs_type1();

   object_id = add_layer_info("Object");
   disabled = 1;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   f2_x_offset = tc0200obj.ofs_x;
   f2_sprite_type = tc0200obj.ofs_y;
   //object_id = add_layer_info("TC0200OBJ:OBJECT");
}

void make_object_bank(UINT8 *src)
{
   bank_data[0] = ((ReadWord(src+0x04)<<11)&0x3800)+0x0000;
   bank_data[1] = ((ReadWord(src+0x04)<<11)&0x3800)+0x0400;
   bank_data[2] = ((ReadWord(src+0x06)<<11)&0x3800)+0x0000;
   bank_data[3] = ((ReadWord(src+0x06)<<11)&0x3800)+0x0400;
   bank_data[4] = ((ReadWord(src+0x08)<<10)&0x3C00)+0x0000;
   bank_data[5] = ((ReadWord(src+0x0A)<<10)&0x3C00)+0x0000;
   bank_data[6] = ((ReadWord(src+0x0C)<<10)&0x3C00)+0x0000;
   bank_data[7] = ((ReadWord(src+0x0E)<<10)&0x3C00)+0x0000;
}

void make_object_bank_koshien(UINT8 *src)
{
   UINT32 data;
   static UINT32 my_data;

   data = ReadWord(src);

/*     if(key[KEY_LEFT]) my_data -= 0x0400; */
/*     if(key[KEY_RIGHT]) my_data += 0x0400; */

   my_data &= 0x3C00;

   #ifdef RAINE_DEBUG
   clear_ingame_message_list();
   print_ingame(60,"K_BANK[%04x] %04x",data, my_data);
   #endif

   //0101/0210/0543/0550/0554/0643

   switch(data){
   case 0x0101:
   bank_data[0]= 0x0000;
   bank_data[1]= 0x0400;
   bank_data[2]= 0x0800;
   bank_data[3]= 0x0C00;
   bank_data[4]= 0x0000;
   bank_data[5]= 0x0400;
   bank_data[6]= 0x0800;
   bank_data[7]= 0x0C00;
   break;
   case 0x0210:
   bank_data[0]= 0x0000;	// *
   bank_data[1]= 0x0400;	// *
   bank_data[2]= 0x0800;	// *
   bank_data[3]= 0x0C00;
   bank_data[4]= 0x1000;	// *
   bank_data[5]= 0x1400;
   bank_data[6]= 0x1800;	// *
   bank_data[7]= 0x1C00;
   break;
   case 0x0543:
   bank_data[0]= 0x0000;
   bank_data[1]= 0x0400;
   bank_data[2]= 0xFFFF;
   bank_data[3]= 0xFFFF;
   bank_data[4]= 0x2800;
   bank_data[5]= 0x2C00;
   bank_data[6]= 0x3000;
   bank_data[7]= 0x3400;
   break;
   case 0x0550:
   bank_data[0]= 0x0000;	// *
   bank_data[1]= 0x0400;	// *
   bank_data[2]= 0xFFFF;
   bank_data[3]= 0xFFFF;
   bank_data[4]= 0x2800;
   bank_data[5]= 0x2C00;
   bank_data[6]= 0x3000;	// *
   bank_data[7]= 0x3400;	// *
   break;
   case 0x0554:
   bank_data[0]= 0x0000;
   bank_data[1]= 0x0400;
   bank_data[2]= 0xFFFF;
   bank_data[3]= 0xFFFF;
   bank_data[4]= 0x2800;
   bank_data[5]= 0x2C00;
   bank_data[6]= 0x3000;
   bank_data[7]= 0x3400;
   break;
   case 0x0643:
   bank_data[0]= 0x0000;	// *
   bank_data[1]= 0x0400;	// *
   bank_data[2]= 0x2000;
   bank_data[3]= 0x2400;
   bank_data[4]= 0x2800;
   bank_data[5]= 0x2C00;	// *
   bank_data[6]= 0x3800;	// *
   bank_data[7]= 0x3C00;	// *
   break;
   default:
   bank_data[0]= 0xFFFF;
   bank_data[1]= 0xFFFF;
   bank_data[2]= 0xFFFF;
   bank_data[3]= 0xFFFF;
   bank_data[4]= 0xFFFF;
   bank_data[5]= 0xFFFF;
   bank_data[6]= 0xFFFF;
   bank_data[7]= 0xFFFF;
   break;
   }
}

void render_tc0200obj_mapped_b(void)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   x=0;
   y=0;
   xn=0;
   yn=0;

   rel_x=ReadWord(&RAM_BG[0x14]);
   rel_y=ReadWord(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x20;zz<0x4000;zz+=16){

      if(RAM_BG[zz+13]!=0) return;

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+4]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y + ReadWord(&RAM_BG[zz+6]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}

void render_tc0200obj_mapped_yuyugogo(void)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_TILE;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   RAM_TILE  = tc0200obj.RAM_TILE;

   x=0;
   y=0;
   xn=0;
   yn=0;

   rel_x=ReadWord(&RAM_BG[0x14]);
   rel_y=ReadWord(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   RAM_TILE+=4;
   for(zz=0x20;zz<0x4000;zz+=16,RAM_TILE+=2){

      if(RAM_BG[zz+13]!=0) return;

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+4]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y + ReadWord(&RAM_BG[zz+6]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta  = ReadWord(&RAM_BG[zz])&0x03FF;
      ta |= (ReadWord(&RAM_TILE[0])<<10)&0xFC00;
      ta &= tile_mask;

      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}

void render_tc0200obj_mapped_yuyugogo2(int pri)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_TILE;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   RAM_TILE  = tc0200obj.RAM_TILE;

   if(pri) pri = 0x80;

   x=0;
   y=0;
   xn=0;
   yn=0;

   if(((ReadWord(&RAM_BG[0x0A])&0x0001)==0) && (tc0200obj.RAM_B)){
      RAM_BG    = tc0200obj.RAM_B;
      RAM_TILE  = tc0200obj.RAM_TILE_B;
   }

   rel_x=ReadWord(&RAM_BG[0x14]);
   rel_y=ReadWord(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   RAM_TILE+=6;
   for(zz=0x30;zz<0x4000;zz+=16,RAM_TILE+=2){

      if(RAM_BG[zz+13]!=0) return;

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((tb&0x80)==pri){

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+4]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y + ReadWord(&RAM_BG[zz+6]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta  = ReadWord(&RAM_BG[zz])&0x00FF;
      ta |= (ReadWord(&RAM_TILE[0])<<8)&0xFF00;
      ta &= tile_mask;

      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }
      }
      }

   }

}

/*

Gun Frontier

*/

void render_tc0200obj_mapped_r270(void)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y,spr_on;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     =(tc0200obj.bmp_y + tc0200obj.bmp_h) - tc0200obj.ofs_y;

   x=0;
   y=0;
   xn=0;
   yn=0;
   spr_on=0;

   if(((ReadWord(&RAM_BG[0x0A])&0x0001)==0) && (tc0200obj.RAM_B)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_y=ReadWord(&RAM_BG[0x14]);
   rel_x=ReadWord(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x30;zz<0x4000;zz+=16){

      //if(RAM_BG[zz+13]!=0) return;
      if(RAM_BG[zz+11]!=0) return;

      if((ReadWord(&RAM_BG[zz+6])&0x8000)!=0) spr_on^=1;

      if(spr_on!=0){

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+6]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x20)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            y = ofs_y - ReadWord(&RAM_BG[zz+4]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y -= rel_y;		// Minus?
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
         y  = (y-zy)&OBJ_XY_MASK;
      }
      else{
         if((td&0x80)!=0){
            zy = zoom_dat_y[ty++];
            y  = (y-zy)&OBJ_XY_MASK;
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=ReadWord(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

      }
   }

}

void render_tc0200obj_mapped(int pri_mask)
{
   int color,offs,big_sprite=0,zoomxlatch=0,zoomylatch=0,xcurrent,ycurrent;
   int spritecont,zx,zy,x_no=0,y_no=0,last_continuation_tile=0;
   int scroll1x=0,scroll1y=0,/* sprites_flip_screen, */ scrollx=0,scrolly=0,xlatch=0,ylatch=0;
   int curx,cury;
   UINT8 *map;
   UINT8 *NEW_RAM = RAM_BG;
   UINT16 code,i,x,y,*curr_extension;
   if (RAM_BG ==  tc0200obj.RAM_B)
     // If using bank b, then the extended area takes a bank too...
     curr_extension = f2_sprite_extension + (0x4000>>4);
   else
     curr_extension = f2_sprite_extension;

   if(!check_layer_enabled(object_id))
       return;

   x=0;
   y=0;
   color=0;

/*    if(((ReadWord(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){ */
/*       RAM_BG = tc0200obj.RAM_B; */
/*    } */

   color = 0;

   for(offs=0;offs<0x4000;offs+=16){

     if (RAM_BG[offs+7] & 0x80) { // special commands
       disabled = RAM_BG[offs+11] & 0x10;
       // sprites_flip_screen = RAM_BG[offs+11] & 0x20;
       if ((RAM_BG[offs+10] & 1) && tc0200obj.RAM_B) {
	 NEW_RAM = tc0200obj.RAM_B;
       } else
	 NEW_RAM = tc0200obj.RAM;
#ifdef VERBOSE
#endif
       continue;
     }

      if ((RAM_BG[offs+5] & 0xf0) == 0xa0) {
	master_scrollx = ReadWord(&RAM_BG[offs+4]) & 0xfff;
	if (master_scrollx >= 0x800) master_scrollx -= 0x1000;   /* signed value */
	master_scrolly = ReadWord(&RAM_BG[offs+6]) & 0xfff;
	if (master_scrolly >= 0x800) master_scrolly -= 0x1000;   /* signed value */
      }

      if ((RAM_BG[offs+5] & 0xf0) == 0x50) {
	scroll1x = ReadWord(&RAM_BG[offs+4]) & 0xfff;
	if (scroll1x >= 0x800) scroll1x -= 0x1000;   /* signed value */
	scroll1y = ReadWord(&RAM_BG[offs+6]) & 0xfff;
	if (scroll1y >= 0x800) scroll1y -= 0x1000;   /* signed value */
      }

     if (disabled)
       continue;

      spritecont=RAM_BG[offs+9];

      if((spritecont&0x04)==0){
         color = RAM_BG[offs+8];
      }
      if (!( (1<<((color & 0xc0)>>6)) & pri_mask)) {
#ifdef VERBOSE
#endif
	continue;
      }

      if (f2_sprite_type == 0) {
	code = ReadWord(&RAM_BG[offs]) & 0x1fff;
	i = (code & 0x1c00) >> 10;
	code = bank_data[i] + (code & 0x3ff);
      } else if (f2_sprite_type == 1) {   /* Yuyugogo */
	code = ReadWord(&RAM_BG[offs]) & 0x3ff;
	i = (curr_extension[offs >> 4] & 0x3f ) << 10;
	code = (i | code);
      } else if (f2_sprite_type == 2) {  /* Pulirula */
	code = RAM_BG[offs];
	i = (curr_extension[offs >> 4] & 0xff00 );
	code = (i | code);
      } else if (f2_sprite_type == 3) {   /* Dinorex and a few quizzes */
	code = RAM_BG[offs];
	i = (curr_extension[offs >> 4] & 0xff ) << 8;
	code = (i | code);
      }

      // check for extra scroll offset

      if ((spritecont & 0x08) != 0) {   /* sprite continuation flag set */
	if (big_sprite == 0) {   /* are we starting a big sprite ? */
	  xlatch = ReadWord(&RAM_BG[offs+4]) & 0xfff;
	  ylatch = ReadWord(&RAM_BG[offs+6]) & 0xfff;
	  x_no = 0;
	  y_no = 0;
	  zoomylatch = RAM_BG[offs+3];
	  zoomxlatch = RAM_BG[offs+2];
	  big_sprite = 1;   /* we have started a new big sprite */
	}
      } else if (big_sprite) {
	last_continuation_tile = 1;   /* don't clear big_sprite until last tile done */
      }

/* The bigsprite == 0 check fixes "tied-up" little sprites in Thunderfox */
/* which (mostly?) have spritecont = 0x20 when they are not continuations */
/* of anything. */
      if (big_sprite == 0 || (spritecont & 0xf0) == 0) {
	x = ReadWord(&RAM_BG[offs+4]);

/* Some absolute x values deduced here are 1 too high (scenes when you get */
/* home run in Koshien, and may also relate to BG layer woods and stuff as you */
/* journey in MjnQuest). You will see they are 1 pixel too far to the right. */
/* Where is this extra pixel offset coming from?? */

	if (x & 0x8000) {  /* absolute (koshien) */
	  // fprintf(stderr,"absolute\n");
	  scrollx = - f2_x_offset - 0x60;
	  scrolly = 0; // +16;
	} else if (x & 0x4000) {  /* ignore extra scroll */
	  // fprintf(stderr,"ignore extra scroll\n");
	  scrollx = master_scrollx - f2_x_offset - 0x60;
	  scrolly = master_scrolly;

	} else { /* all scrolls applied */
	  scrollx = scroll1x + master_scrollx - f2_x_offset - 0x60;
	  scrolly = scroll1y + master_scrolly;
	  // fprintf(stderr,"normal %d,%d\n",scrollx,scrolly);
	}
	x &= 0xfff;
	y = ReadWord(&RAM_BG[offs+6]) & 0xfff;

	xcurrent = x;
	ycurrent = y;
      } else {
	if ((spritecont & 0x10) == 0) // use latched y
	  y = ycurrent;
	else if ((spritecont & 0x20) != 0) { // y+=16... weird !!!
	  y += 16;
	  y_no++;   /* keep track of y tile for zooms */
	}
	if ((spritecont & 0x40) == 0) // use latched x
	  x = xcurrent;
	else if ((spritecont & 0x80) != 0) { // x+=16...
	  x += 16;
	  y_no=0;
	  x_no++;   /* keep track of x tile for zooms */
	}
      }

      if (big_sprite) {
	int zoomx = zoomxlatch;
	int zoomy = zoomylatch;
	zx = 0x10;	/* default, no zoom: 16 pixels across */
	zy = 0x10;	/* default, no zoom: 16 pixels vertical */

	if (zoomx || zoomy) {
	  /* "Zoom" zx&y is pixel size horizontally and vertically
	     of our sprite chunk. So it is difference in x and y
	     coords of our chunk and diagonally adjoining one. */

	  /* These calcs caused black lines between flames in Gunfront attract... */
/*				x = xlatch + x_no * (0x100 - zoomx) / 16; */
/*				y = ylatch + y_no * (0x100 - zoomy) / 16; */
/*				zx = xlatch + (x_no+1) * (0x100 - zoomx) / 16 - x; */
/*				zy = ylatch + (y_no+1) * (0x100 - zoomy) / 16 - y; */

	  // raine notice : I wonder how our code could work since we didn't test big_sprite
	  // that is (RAM_BG[9] & 8). Note : keep some sample of the old code to analyse
	  // this one day eventually.
	  x = xlatch + (x_no * (0x100 - zoomx)+12) / 16;    /*ks */
	  y = ylatch + (y_no * (0x100 - zoomy)+12) / 16;    /*ks */
	  zx = xlatch + ((x_no+1) * (0x100 - zoomx)+12) / 16 - x;  /*ks */
	  zy = ylatch + ((y_no+1) * (0x100 - zoomy)+12) / 16 - y;  /*ks */
	}
      } else {
	int zoomy = RAM_BG[offs+3];
	int zoomx = RAM_BG[offs+2];
	// zx = zoom16_ofs[(zoomx<<5)];
	zx = (0x100 - zoomx) / 16;
	// zy = zoom16_ofs[(zoomy<<5)];
	zy = (0x100 - zoomy) / 16;
      }

      if (last_continuation_tile) {
	big_sprite=0;
	last_continuation_tile=0;
      }

      if(RAM_MSK[code]==0) {
#ifdef VERBOSE
	if (code)
#endif
	continue;                      // No pixels; skip
      }

      curx = (x + scrollx + 38) & 0xfff;
      if (curx >= 0x800)	curx -= 0x1000;   /* treat it as signed */

      cury = (y + scrolly + 16) & 0xfff;
      if (cury >= 0x800)	cury -= 0x1000;   /* treat it as signed */

/*       if (sprites_flipscreen) { */
/* 	/\* -zx/y is there to fix zoomed sprite coords in screenflip. */
/* 	   drawgfxzoom does not know to draw from flip-side of sprites when */
/* 	   screen is flipped; so we must correct the coords ourselves. *\/ */

/* 	curx = 320 - curx - zx; */
/* 	cury = 256 - cury - zy; */
/* 	spritecont ^= 3; // invert flipx, flipy */
/*       } */

      if((curx > sx_1) && (curx < sx_2) && (cury > sy_1) && (cury < sy_2)){

	if (f2_sprites_colors == 64) {
	  MAP_PALETTE_MULTI_MAPPED_NEW(
            color,
            64,
            map
	    );
	} else {
	  MAP_PALETTE_MAPPED_NEW(
			       color,
			       16,
			       map
			       );
	}

	if(RAM_MSK[code]==1){                        // Some pixels; trans
	  switch(spritecont&0x03){
	  case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy);        break;
	  case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy);  break;
	  case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy);  break;
	  case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy); break;
	  }
	}  else {                                        // all pixels; solid
	  switch(spritecont&0x03){
	  case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy);        break;
	  case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy);  break;
	  case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy);  break;
	  case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[code<<8],curx,cury,map,zx,zy); break;
	  }
	}
      }
   } // for
   RAM_BG = NEW_RAM;
}

/*

diff:

- start at 0x20
- spr_on start = 1
- bank switch at 0x33EA

*/

void render_tc0200obj_mapped_soliltary_fighter(void)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y,spr_on;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;
   spr_on=1;

   // solitary fighter

   if(((ReadWord(&RAM_BG[0x33EA])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   // growl (wrong?)

   if(((ReadWord(&RAM_BG[0x321A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_y = ReadWord(&RAM_BG[0x14]);
   rel_x = ReadWord(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x20;zz<0x4000;zz+=16){

      if(RAM_BG[zz+13]!=0) return;

      if((ReadWord(&RAM_BG[zz+6])&0x8000)!=0) spr_on^=1;

      if(spr_on!=0){

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y + ReadWord(&RAM_BG[zz+6]);

            //if((ReadWord(&RAM_BG[zz+4])&0x8000)!=0) rel_y = ReadWord(&RAM_BG[zz+6]);
            //else y += rel_y;

            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;

            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+4]);

            //if((ReadWord(&RAM_BG[zz+4])&0x8000)!=0) rel_x = ReadWord(&RAM_BG[zz+4]);
            //else x += rel_x;

            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;

            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta  = ReadWord(&RAM_BG[zz]);
      ta  = (ta&0x3FF) | bank_data[(ta>>10)&7];
      ta &= tile_mask;

      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

      }

   }

}

void render_tc0200obj_mapped_fchamp(int pri)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y,spr_on;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;
   spr_on=0;

   if((ReadWord(&RAM_BG[0x0A])&0x0001) && (tc0200obj.RAM_B)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_y=ReadWord(&RAM_BG[0x14]);
   rel_x=ReadWord(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   if((ReadWord(&RAM_BG[0x06])&0x8000)!=0){
      if((ReadWord(&RAM_BG[0x0A])&0x1000)!=0) spr_on=0;
      else spr_on=1;
   }

   for(zz=0x30;zz<0x4000;zz+=16){

      if(RAM_BG[zz+13]!=0) return;

      if((ReadWord(&RAM_BG[zz+0x06])&0x8000)!=0){
         if((ReadWord(&RAM_BG[zz+0x0A])&0x1000)!=0) spr_on=0;
         else spr_on=1;
      }

      if(spr_on!=0){

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((td&0x10)==0){
         if((td&0x80)==0){
            y = ofs_y + ReadWord(&RAM_BG[zz+6]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+4]);
            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      if((tb&0xC0) == pri){

      ta  = ReadWord(&RAM_BG[zz]);
      ta  = (ta&0x3FF) | bank_data[(ta>>10)&7];
      ta &= tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            16,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

      }

      }

   }

}

void render_tc0200obj_mapped_opwolf3(void)
{
   int x,y,ta,tb,zz,cols;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_TILE;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   RAM_TILE  = tc0200obj.RAM_TILE;

   cols      = tc0200obj.cols;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;

   //if(((ReadWord(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
   if(((ReadWord(&RAM_BG[0x3216])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
      RAM_TILE = tc0200obj.RAM_TILE_B;
   }

   rel_y=ReadWord(&RAM_BG[0x24]);
   rel_x=ReadWord(&RAM_BG[0x26]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   RAM_TILE+=6;
   for(zz=0x30;zz<0x4000;zz+=16,RAM_TILE+=2){

      if(RAM_BG[zz+13]!=0) return;

      td=RAM_BG[zz+9];

      if((td&0x04)==0){
         tb = RAM_BG[zz+8];
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y + ReadWord(&RAM_BG[zz+6]);

            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) rel_y = ReadWord(&RAM_BG[zz+6]);
            else y += rel_y;

            //if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;

            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord(&RAM_BG[zz+4]);

            if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) rel_x = ReadWord(&RAM_BG[zz+4]);
            else x += rel_x;

            //if((ReadWord(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;

            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta  = ReadWord(&RAM_BG[zz])&0x00FF;
      ta |= ReadWord(&RAM_TILE[0])&0xFF00;
      ta &= tile_mask;

      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb,
            cols,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}

void render_tc0200obj_mapped_f3system(void)
{
   int x,y,ta,tb,zz,cols;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   cols      = tc0200obj.cols;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;

   if(((ReadWord68k(&RAM_BG[0x0A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }
   if(((ReadWord68k(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_x=ReadWord68k(&RAM_BG[0x14]);
   rel_y=ReadWord68k(&RAM_BG[0x16]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x30;zz<0x4000;zz+=16){

      if(RAM_BG[zz+12]!=0) return;

      td=RAM_BG[zz+8];

      if((td&0x04)==0){
         tb = RAM_BG[zz+9];
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord68k(&RAM_BG[zz+4]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y + ReadWord68k(&RAM_BG[zz+6]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=ReadWord68k(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb|0x100,
            cols,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}

void render_tc0200obj_mapped_f3system_b(void)
{
   int x,y,ta,tb,zz,cols;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   int rel_x2,rel_y2;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   cols      = tc0200obj.cols;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;


   if(((ReadWord68k(&RAM_BG[0x0A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }
   if(((ReadWord68k(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_x=ReadWord68k(&RAM_BG[0x14]);
   rel_y=ReadWord68k(&RAM_BG[0x16]);

   rel_x2=ReadWord68k(&RAM_BG[0x24]);
   rel_y2=ReadWord68k(&RAM_BG[0x26]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x30;zz<0x4000;zz+=16){

      if(RAM_BG[zz+12]!=0) return;

      td=RAM_BG[zz+8];

      if((td&0x04)==0){
         tb = RAM_BG[zz+9];
      }

      if((td&0x40)==0){
         if((td&0x80)==0){
            x = ofs_x + ReadWord68k(&RAM_BG[zz+4]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            else x += (rel_x2+rel_x);
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x10)==0){
         if((td&0x80)==0){
            y = ofs_y + ReadWord68k(&RAM_BG[zz+6]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            else y += (rel_y2+rel_y);
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=ReadWord68k(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MULTI_MAPPED_NEW(
            tb|0x100,
            cols,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}

void render_tc0200obj_mapped_f3system_b_multi(UINT8 *colour_mask)
{
   int x,y,ta,tb,zz;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   int rel_x2,rel_y2;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT8 *COL_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   COL_MSK   = colour_mask;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     = tc0200obj.bmp_y + tc0200obj.ofs_y;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;


   if(((ReadWord68k(&RAM_BG[0x0A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }
   if(((ReadWord68k(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_x=ReadWord68k(&RAM_BG[0x14]);
   rel_y=ReadWord68k(&RAM_BG[0x16]);

   rel_x2=ReadWord68k(&RAM_BG[0x24]);
   rel_y2=ReadWord68k(&RAM_BG[0x26]);

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x30;zz<0x4000;zz+=16){

      if(RAM_BG[zz+12]!=0) return;

      td=RAM_BG[zz+8];

      if((td&0x04)==0){
         tb = RAM_BG[zz+9];
      }

      if((td&0x40)==0){
         if((td&0x80)==0){
            x = ofs_x + ReadWord68k(&RAM_BG[zz+4]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            else x += (rel_x2+rel_x);
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x80)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x10)==0){
         if((td&0x80)==0){
            y = ofs_y + ReadWord68k(&RAM_BG[zz+6]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) y += rel_y;
            else y += (rel_y2+rel_y);
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
      }
      else{
         if((td&0x20)!=0){
            y  = (y+zy)&OBJ_XY_MASK;
            zy = zoom_dat_y[ty++];
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=ReadWord68k(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MULTI_MAPPED_NEW(
            tb|0x100,
            COL_MSK[ta],
            map
         );

         if(RAM_MSK[ta]==1)
            Draw16x16_Trans_Mapped_ZoomXY_flip_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy,td&3);
         else
            Draw16x16_Mapped_ZoomXY_flip_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy,td&3);

      }

      }

   }

}

void render_tc0200obj_mapped_f3system_r180(void)
{
   int x,y,ta,tb,zz,cols;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   int rel_x2,rel_y2;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     =(tc0200obj.bmp_x + tc0200obj.bmp_w) - tc0200obj.ofs_x;
   ofs_y     =(tc0200obj.bmp_y + tc0200obj.bmp_h) - tc0200obj.ofs_y;

   cols      = tc0200obj.cols;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;

   rel_x=ReadWord68k(&RAM_BG[0x14]);
   rel_y=ReadWord68k(&RAM_BG[0x16]);

   rel_x2=ReadWord68k(&RAM_BG[0x24]);
   rel_y2=ReadWord68k(&RAM_BG[0x26]);

   if(((ReadWord68k(&RAM_BG[0x0A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }
   if(((ReadWord68k(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   tb = 0;
   zoom_dat_x = zoom16_ofs+(0<<5);
   zoom_dat_y = zoom16_ofs+(0<<5);
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x30;zz<0x4000;zz+=16){

      if(RAM_BG[zz+12]!=0) return;

      td=RAM_BG[zz+8];

      if((td&0x04)==0){
         tb = RAM_BG[zz+9];
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            x = ofs_x - ReadWord68k(&RAM_BG[zz+4]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) x -= rel_x;
            else x -= (rel_x2+rel_x);
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
         x  = (x-zx)&OBJ_XY_MASK;
      }
      else{
         if((td&0x80)!=0){
            zx = zoom_dat_x[tx++];
            x  = (x-zx)&OBJ_XY_MASK;
         }
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            y = ofs_y - ReadWord68k(&RAM_BG[zz+6]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) y -= rel_y;
            else y -= (rel_y2+rel_y);
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
         y  = (y-zy)&OBJ_XY_MASK;
      }
      else{
         if((td&0x20)!=0){
            zy = zoom_dat_y[ty++];
            y  = (y-zy)&OBJ_XY_MASK;
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=( ReadWord68k(&RAM_BG[zz]) | ((RAM_BG[zz+11]&1)<<16) ) & tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb|0x100,
            cols,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x03: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x00: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}

void render_tc0200obj_mapped_f3system_r270_b(void)
{
   int x,y,ta,tb,zz,cols;
   int xn,yn,td,zx,zy,tx,ty;
   int rel_x,rel_y;
   int rel_x2,rel_y2;
   UINT8 *zoom_dat_x;
   UINT8 *zoom_dat_y;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   int sx_1,sy_1,sx_2,sy_2;
   int ofs_x,ofs_y;
   UINT32 tile_mask;

   if(!check_layer_enabled(object_id))
       return;

   RAM_BG    = tc0200obj.RAM;
   RAM_GFX   = tc0200obj.GFX;
   RAM_MSK   = tc0200obj.MASK;
   tile_mask = tc0200obj.tile_mask;
   sx_1      = tc0200obj.bmp_x - 16;
   sy_1      = tc0200obj.bmp_y - 16;
   sx_2      = tc0200obj.bmp_x + tc0200obj.bmp_w;
   sy_2      = tc0200obj.bmp_y + tc0200obj.bmp_h;
   ofs_x     = tc0200obj.bmp_x + tc0200obj.ofs_x;
   ofs_y     =(tc0200obj.bmp_y + tc0200obj.bmp_h) - tc0200obj.ofs_y;

   cols      = tc0200obj.cols;

   x=0;
   y=0;
   xn=0;
   yn=0;
   tb=0;


   if(((ReadWord68k(&RAM_BG[0x0A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }
   if(((ReadWord68k(&RAM_BG[0x2A])&0x0001)!=0) && (tc0200obj.RAM_B != NULL)){
      RAM_BG = tc0200obj.RAM_B;
   }

   rel_x=ReadWord68k(&RAM_BG[0x16]);
   rel_y=ReadWord68k(&RAM_BG[0x14]);

   rel_x2=ReadWord68k(&RAM_BG[0x26]);
   rel_y2=ReadWord68k(&RAM_BG[0x24]);

   tb = 0;
   zoom_dat_x = zoom16_ofs;
   zoom_dat_y = zoom16_ofs;
   tx = 0;
   ty = 0;
   zx = zoom_dat_x[0];
   zy = zoom_dat_y[0];

   for(zz=0x30;zz<0x4000;zz+=16){

      if(RAM_BG[zz+12]!=0) return;

      td=RAM_BG[zz+8];

      if((td&0x04)==0){
         tb = RAM_BG[zz+9];
      }

      if((td&0x10)==0){
         if((td&0x04)==0){
            x = ofs_x + ReadWord68k(&RAM_BG[zz+6]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) x += rel_x;
            else x += rel_x2;
            x &= OBJ_XY_MASK;
            xn = x;

            zoom_dat_x = zoom16_ofs+(RAM_BG[zz+2]<<5);
         }
         else{
            x = xn;
         }
         tx = 0;
         zx = zoom_dat_x[tx++];
      }
      else{
         if((td&0x20)!=0){
            x  = (x+zx)&OBJ_XY_MASK;
            zx = zoom_dat_x[tx++];
         }
      }

      if((td&0x40)==0){
         if((td&0x04)==0){
            y = ofs_y - ReadWord68k(&RAM_BG[zz+4]);
            if((ReadWord68k(&RAM_BG[zz+4])&0x4000)!=0) y -= rel_y;
            else y -= rel_y2;
            y &= OBJ_XY_MASK;
            yn = y;

            zoom_dat_y = zoom16_ofs+(RAM_BG[zz+3]<<5);
         }
         else{
            y = yn;
         }
         ty = 0;
         zy = zoom_dat_y[ty++];
         y  = (y-zy)&OBJ_XY_MASK;
      }
      else{
         if((td&0x80)!=0){
            zy = zoom_dat_y[ty++];
            y  = (y-zy)&OBJ_XY_MASK;
         }
      }

      if((x > sx_1) && (x < sx_2) && (y > sy_1) && (y < sy_2)){

      ta=ReadWord68k(&RAM_BG[zz])&tile_mask;
      if(RAM_MSK[ta]!=0){                        // No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            tb|0x100,
            cols,
            map
         );

         if(RAM_MSK[ta]==1){                        // Some pixels; trans
            switch(td&0x03){
               case 0x00: Draw16x16_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x02: Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x01: Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }
         else{                                        // all pixels; solid
            switch(td&0x03){
               case 0x00: Draw16x16_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);        break;
               case 0x02: Draw16x16_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x01: Draw16x16_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy);  break;
               case 0x03: Draw16x16_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,zx,zy); break;
            }
         }

      }

      }

   }

}
