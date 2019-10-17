/******************************************************************************/
/*                                                                            */
/*                 tc0150rod: TAITO ROAD SCROLL EFFECT CHIP                   */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc150rod.h"
#include "blit.h"

/*

tc0150rod info
--------------

- Road Scroll Chip

0000-07FF : BANK#0 [A] - 256 Lines
0800-0FFF : BANK#0 [B] - 256 Lines
1000-17FF : BANK#1 [A] - 256 Lines
1800-1FFF : BANK#1 [B] - 256 Lines

ctrl data at 1FFE:

0000/0500 = Single
0900/0C00 = Double

-----+--------+--------------------------------
Byte | Bit(s) | Info
-----+76543210+--------------------------------
  0  |....x...| Enable Bank#1
  0  |.....x..| Select A/B Buffer Bank#1
  0  |......x.| Enable Bank#0 (error chase hq?)
  0  |.......x| Select A/B Buffer Bank#0
-----+--------+--------------------------------

8 bytes per line:

-----+--------+--------------------------------
Byte | Bit(s) | Info
-----+76543210+--------------------------------
  0  |x.......| Solid from Screen Start to Line
  0  |.......x| Line Start (high) [See Road Split]
  1  |xxxxxxxx| Line Start (low)
  2  |x.......| Solid from Line to Screen End
  2  |.......x| Line End (high) [See Road Split]
  3  |xxxxxxxx| Line End (low)
  4  |x.......| ?
  4  |....x...| ?
  4  |.....xxx| X Offset (high)
  5  |xxxxxxxx| X Offset (low)
  6  |xxxx....| Colour Bank
  6  |.....xxx| Gfx Line (high)
  7  |xxxxxxxx| Gfx Line (low)
-----+--------+--------------------------------

0/1 = related to road steepness
4/5 = related to road straightness
6/7 = related to road steepness

Not implemented:

- Colour problems, control bits seem not 100%, some rendering problems.

Games:

Aqua Jack          -
Battle Shark       -
Chase HQ           -
Chase HQ Japanese  -
Chase HQ 2: SCi    -
Continental Circus -
Night Striker      -

*/

/******************************************************************************/

static UINT32 r_map[0x100];
static UINT32 map_base[0x200];

void tc0150rod_init_palette(void)
{
  UINT32 y,*map32; //,x
   UINT8 *map;
   UINT16 *map16;

   for(y=0;y<0x40;y++){

      MAP_PALETTE_MAPPED_NEW(
         (y)|(0xC0),
         8,
         map
      );

      switch(display_cfg.bpp) {
	case 8:
      map_base[(y*8) + 0] = map[0];
      map_base[(y*8) + 1] = map[1];
      map_base[(y*8) + 2] = map[2];
      map_base[(y*8) + 3] = map[3];
      map_base[(y*8) + 4] = map[4];
      map_base[(y*8) + 5] = map[5];
      map_base[(y*8) + 6] = map[6];
      map_base[(y*8) + 7] = map[7];
      break;
      case 15:
      case 16:
      map16 = (UINT16*)map;
      map_base[(y*8) + 0] = map16[0];
      map_base[(y*8) + 1] = map16[1];
      map_base[(y*8) + 2] = map16[2];
      map_base[(y*8) + 3] = map16[3];
      map_base[(y*8) + 4] = map16[4];
      map_base[(y*8) + 5] = map16[5];
      map_base[(y*8) + 6] = map16[6];
      map_base[(y*8) + 7] = map16[7];
      break;
      case 32:
      map32 = (UINT32*)map;
      map_base[(y*8) + 0] = map32[0];
      map_base[(y*8) + 1] = map32[1];
      map_base[(y*8) + 2] = map32[2];
      map_base[(y*8) + 3] = map32[3];
      map_base[(y*8) + 4] = map32[4];
      map_base[(y*8) + 5] = map32[5];
      map_base[(y*8) + 6] = map32[6];
      map_base[(y*8) + 7] = map32[7];
      break;
      }

   }

   if(tc0150rod.PAL){

      for(y=0; y<0x100; y++){
         r_map[ y ] = map_base[ ((y & 0xF0) << 1) + (tc0150rod.PAL[y] & 0x1F) ];
      }

   }
   else{

      for(y=0; y<0x100; y++){
         r_map[y] = map_base[y];
      }

   }
}

void tc0150rod_show_palette(void)
{
#ifndef SDL
   #ifdef RAINE_DEBUG

   UINT32 i,x,y;

   for(i = 0; i < 0x200; i ++){

      x = i & 0x1F;
      y = i >> 5;

      _putpixel(GameViewBitmap, (x<<1)+0 , (y<<1)+0 , map_base[i]);
      _putpixel(GameViewBitmap, (x<<1)+0 , (y<<1)+1 , map_base[i]);
      _putpixel(GameViewBitmap, (x<<1)+1 , (y<<1)+0 , map_base[i]);
      _putpixel(GameViewBitmap, (x<<1)+1 , (y<<1)+1 , map_base[i]);

   }

   for(i = 0; i < 0x100; i ++){

      x = i & 0x0F;
      y = i >> 4;

      _putpixel(GameViewBitmap, (x<<1)+0 , (y<<1)+128 , r_map[i]);
      _putpixel(GameViewBitmap, (x<<1)+0 , (y<<1)+129 , r_map[i]);
      _putpixel(GameViewBitmap, (x<<1)+1 , (y<<1)+128 , r_map[i]);
      _putpixel(GameViewBitmap, (x<<1)+1 , (y<<1)+129 , r_map[i]);

   }

   #endif
#endif
}

void tc0150rod_render(UINT32 start, UINT32 end)
{
  int y,ta,zz; // ,x,aa,bb;
   int rx; // pal;
   UINT8 *dest,*src_0,*src_1;
   UINT32 *map;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_y,bmp_h;
   UINT32 scr_y;

   UINT32 line_0,line_1;
    INT32 x_0,   x_1;
    INT32 aa_0,  aa_1;
    INT32 bb_0,  bb_1;
   UINT32 pal_0, pal_1;

   UINT32 ctrl;

   RAM_BG    = tc0150rod.RAM;
   GFX_BG    = tc0150rod.GFX;

   bmp_y = tc0150rod.bmp_y;
   bmp_h = tc0150rod.bmp_h;
   scr_y = tc0150rod.scr_y;

   ctrl = ReadWord(&RAM_BG[0x1FFE]);

   if((ReadWord(&RAM_BG[0x1FFE])&0x0100)==0)
      zz=0x0000;
   else
      zz=0x0800;

   y = bmp_y + scr_y + (start>>3);
   for(ta=zz+start;ta<(int)(zz+end);ta+=8){

      if(((UINT32)y >= bmp_y)&&((UINT32)y< (bmp_y+bmp_h))){

      dest = GameBitmap->line[y];

      line_0 = ReadWord(&RAM_BG[ta+0x1006])&0x3FF;
      line_1 = ReadWord(&RAM_BG[ta+0x0006])&0x3FF;

      x_0    = (16+512-6) - (ReadWord(&RAM_BG[ta+0x1004])&0x7FF);
      x_1    = (16+512-6) - (ReadWord(&RAM_BG[ta+0x0004])&0x7FF);

      src_0  = GFX_BG + (((line_0 <<11)+0x400)&0x1FFFFF);
      src_1  = GFX_BG + (((line_1 <<11)+0x400)&0x1FFFFF);

      aa_0   = 0x200 - (ReadWord(&RAM_BG[ta+0x1000])&0x1FF);
      aa_1   = 0x200 - (ReadWord(&RAM_BG[ta+0x0000])&0x1FF);

      bb_0   = 0x200 + (ReadWord(&RAM_BG[ta+0x1002])&0x1FF);
      bb_1   = 0x200 + (ReadWord(&RAM_BG[ta+0x0002])&0x1FF);

      pal_0  = (ReadWord(&RAM_BG[ta+0x1006])>>12)&0x0F;
      pal_1  = (ReadWord(&RAM_BG[ta+0x0006])>>12)&0x0F;

      /*

      left edge (eg. grass)

      */

      if( ctrl & 0x0800){
      if( ReadWord(&RAM_BG[ta+0x1000]) & 0x8000 ){

         map = &r_map[(pal_0<<4) + 8];

         for( rx = 32; rx < x_0 + aa_0; rx ++)

            // dest[rx] = map[0];
	    raine_put_pixel(dest,rx,map,0);

      }
      }

      if( ReadWord(&RAM_BG[ta+0x0000]) & 0x8000 ){

         map = &r_map[(pal_1<<4) + 8];

         for( rx = 32; rx < x_1 + aa_1; rx ++)

            // dest[rx] = map[0];
	    raine_put_pixel(dest,rx,map,0);

      }

      /*

      right edge (eg. grass)

      */

      if( ctrl & 0x0800){
      if( ReadWord(&RAM_BG[ta+0x1002]) & 0x8000 ){

         map = &r_map[(pal_0<<4) + 12];

         for( rx = x_0 + bb_0; rx < 320 + 32; rx ++)

            // dest[rx] = map[0];
	    raine_put_pixel(dest,rx,map,0);

      }
      }

      if( ReadWord(&RAM_BG[ta+0x0002]) & 0x8000 ){

         map = &r_map[(pal_1<<4) + 12];

         for( rx = x_1 + bb_1; rx < 320 + 32; rx ++)

            // dest[rx] = map[0];
	    raine_put_pixel(dest,rx,map,0);

      }

      /*

      left track edge (eg. white line)

      */

      if( ctrl & 0x0800){
      if( line_0 ){

         map = &r_map[(pal_0<<4) + 4];

         for( rx = aa_0 - 32; rx < aa_0; rx ++){

            if(((x_0 + rx)>=32)&&((x_0 + rx)<320+32)){

               if(src_0[(rx - aa_0)-512])

                  // dest[x_0 + rx] = map[ src_0[(rx - aa_0)-512] ];
		 raine_put_pixel(dest,x_0 + rx,map,src_0[(rx - aa_0)-512]);
            }
         }

      }
      }

      if( line_1 ){

         map = &r_map[(pal_1<<4) + 4];

         for( rx = aa_1 - 32; rx < aa_1; rx ++){

            if(((x_1 + rx)>=32)&&((x_1 + rx)<320+32)){

               if(src_1[(rx - aa_1)-512])

                  // dest[x_1 + rx] = map[ src_1[(rx - aa_1)-512] ];
		 raine_put_pixel(dest,x_1 + rx,map,src_1[(rx - aa_1)-512]);
            }
         }

      }

      /*

      right track edge (eg. white line)

      */

      if( ctrl & 0x0800){
      if( line_0 ){

         map = &r_map[(pal_0<<4) + 4];

         for( rx = bb_0; rx < bb_0 + 32; rx ++){

            if(((x_0 + rx)>=32)&&((x_0 + rx)<320+32)){

               if(src_0[(rx - bb_0)-512])

                  // dest[x_0 + rx] = map[ src_0[(rx - bb_0)-512] ];
		  raine_put_pixel(dest,x_0 + rx,map,src_0[(rx - bb_0)-512]);
            }
         }

      }
      }

      if( line_1 ){

         map = &r_map[(pal_1<<4) + 4];

         for( rx = bb_1; rx < bb_1 + 32; rx ++){

            if(((x_1 + rx)>=32)&&((x_1 + rx)<320+32)){

               if(src_1[(rx - bb_1)-512])

                  // dest[x_1 + rx] = map[ src_1[(rx - bb_1)-512] ];
		  raine_put_pixel(dest,x_1 + rx,map,src_1[(rx - bb_1)-512]);
            }
         }

      }

      /*

      middle track (eg. road)

      */

      if( ctrl & 0x0800){
      if( line_0 ){

         map = &r_map[(pal_0<<4) + 0];

         for( rx = aa_0; rx < bb_0; rx ++){

            if( ((x_0 + rx) >= 32) && ((x_0 + rx) < 320 + 32) )

               // dest[x_0 + rx] = map[ src_0[rx] ];
	      raine_put_pixel(dest,x_0 + rx,map,src_0[rx ]);

         }

      }
      }

      if( line_1 ){

         map = &r_map[(pal_1<<4) + 0];

         for( rx = aa_1; rx < bb_1; rx ++){

            if( ((x_1 + rx) >= 32) && ((x_1 + rx) < 320 + 32) )

               // dest[x_1 + rx] = map[ src_1[rx] ];
	      raine_put_pixel(dest,x_1 + rx,map,src_1[rx ]);

         }

      }

      }

      y++;
   }

#if 0

   if((ReadWord(&RAM_BG[0x1FFE])&0x0800)!=0){

   if((ReadWord(&RAM_BG[0x1FFE])&0x0400)==0)
      zz=0x1000;
   else
      zz=0x1800;

   y = bmp_y + scr_y + (start>>3);
   for(ta=zz+start;ta<zz+end;ta+=8){

      if((ReadWord(&RAM_BG[ta+6])&0x3FF)!=0){
      x=((16+512-6)-((ReadWord(&RAM_BG[ta+4])&0x7FF)>>0));

      if((y >= bmp_y)&&(y< (bmp_y+bmp_h))){

      BIT2= GFX_BG + ((((ReadWord(&RAM_BG[ta+6])&0x3FF)<<11)+0x400)&0x1FFFFF);

      BIT = GameBitmap->line[y];

      aa = 0x200 - (ReadWord(&RAM_BG[ta+0])&0x1FF);
      bb = 0x200 + (ReadWord(&RAM_BG[ta+2])&0x1FF);

      pal = (RAM_BG[ta+7]>>4)&0x0F;

      /*

      left edge (eg. grass)

      */

      map = &r_map[(pal<<4) + 8];

      if((ReadWord(&RAM_BG[ta+0])&0x8000)!=0){
         for(rx=32;rx<x+aa;rx++){
            BIT[rx] = map[0];
         }
      }

      /*

      right edge (eg. grass)

      */

      map = &r_map[(pal<<4) + 12];

      if((ReadWord(&RAM_BG[ta+2])&0x8000)!=0){
         for(rx=x+bb;rx<320+32;rx++){
            BIT[rx] = map[0];
         }
      }

      /*

      middle track (eg. road)

      */

      map = &r_map[(pal<<4) + 0];

      for(rx=aa;rx<bb;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            BIT[x+rx] = map[BIT2[rx]];
         }
      }

      BIT2 -= 0x400;

      /*

      left track edge (eg. white line)

      */

      map = &r_map[(pal<<4) + 4];

      for(rx=aa-32;rx<aa;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            if(BIT2[512+rx-aa]) BIT[x+rx] = map[BIT2[512+rx-aa]];
         }
      }

      /*

      right track edge (eg. white line)

      */

      map = &r_map[(pal<<4) + 4];

      for(rx=bb;rx<bb+32;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            if(BIT2[512+rx-bb]) BIT[x+rx] = map[BIT2[512+rx-bb]];
         }
      }

      }

      }

      y++;
   }

   }
#endif
}

void tc0150rod_render_flipy(UINT32 start, UINT32 end)
{
   int x,y,ta,zz,aa,bb;
   int rx,pal;
   UINT32 *map;
   UINT8 *BIT,*BIT2;

   UINT8 *RAM_BG;
   UINT8 *GFX_BG;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_y;

   RAM_BG    = tc0150rod.RAM;
   GFX_BG    = tc0150rod.GFX;

   bmp_x = tc0150rod.bmp_x;
   bmp_y = tc0150rod.bmp_y;
   bmp_w = tc0150rod.bmp_w;
   bmp_h = tc0150rod.bmp_h;
   scr_y = tc0150rod.scr_y;


   if((ReadWord(&RAM_BG[0x1FFE])&0x0100)==0)
      zz=0x0000;
   else
      zz=0x0800;

   y = bmp_y + scr_y + (start>>3);
   for(ta=zz+start;ta<(int)(zz+end);ta+=8){

      if((ReadWord(&RAM_BG[ta+6])&0x3FF)!=0){
      x=((16+512-6)-(ReadWord(&RAM_BG[ta+4])&0x7FF));

      if(((UINT32)y >= bmp_y)&&((UINT32)y< (bmp_y+bmp_h))){

      BIT2= GFX_BG + ((((ReadWord(&RAM_BG[ta+6])&0x3FF)<<11)+0x400)&0x1FFFFF);

      BIT = GameBitmap->line[y];

      aa = 0x200 - (ReadWord(&RAM_BG[ta+0])&0x1FF);
      bb = 0x200 + (ReadWord(&RAM_BG[ta+2])&0x1FF);

      pal = (RAM_BG[ta+7]>>4)&0x0F;

      map = &r_map[(pal<<4) + 0];

      if((ReadWord(&RAM_BG[ta+0])&0x8000)!=0){
         for(rx=32;rx<x+aa;rx++){
            BIT[(bmp_x+bmp_w-1)-(rx)] = map[0];
         }
      }

      if((ReadWord(&RAM_BG[ta+2])&0x8000)!=0){
         for(rx=x+bb;rx<320+32;rx++){
            BIT[(bmp_x+bmp_w-1)-(rx)] = map[0];
         }
      }

      map = &r_map[(pal<<4) + 12];

      for(rx=aa;rx<bb;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            BIT[(bmp_x+bmp_w-1)-(x+rx)] = map[BIT2[rx]];
         }
      }

      BIT2 -= 0x400;

      map = &r_map[(pal<<4) + 0];

      for(rx=aa-32;rx<aa;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            if(BIT2[512+rx-aa]) BIT[(bmp_x+bmp_w-1)-(x+rx)] = map[BIT2[512+rx-aa]];
         }
      }

      for(rx=bb;rx<bb+32;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            if(BIT2[512+rx-bb]) BIT[(bmp_x+bmp_w-1)-(x+rx)] = map[BIT2[512+rx-bb]];
         }
      }

      }

      }

      y++;
   }

   if((ReadWord(&RAM_BG[0x1FFE])&0x0800)!=0){

   if((ReadWord(&RAM_BG[0x1FFE])&0x0400)==0)
      zz=0x1000;
   else
      zz=0x1800;

   y = bmp_y + scr_y + (start>>3);
   for(ta=zz+start;ta<(int)(zz+end);ta+=8){

      if((ReadWord(&RAM_BG[ta+6])&0x3FF)!=0){
      x=((16+512-6)-((ReadWord(&RAM_BG[ta+4])&0x7FF)>>0));

      if(((UINT32)y >= bmp_y)&&((UINT32)y< (bmp_y+bmp_h))){

      BIT2= GFX_BG + ((((ReadWord(&RAM_BG[ta+6])&0x3FF)<<11)+0x400)&0x1FFFFF);

      BIT = GameBitmap->line[y];

      aa = 0x200 - (ReadWord(&RAM_BG[ta+0])&0x1FF);
      bb = 0x200 + (ReadWord(&RAM_BG[ta+2])&0x1FF);

      pal = (RAM_BG[ta+7]>>4)&0x0F;

      map = &r_map[(pal<<4) + 0];

      if((ReadWord(&RAM_BG[ta+0])&0x8000)!=0){
         for(rx=32;rx<x+aa;rx++){
            BIT[(bmp_x+bmp_w-1)-(rx)] = map[0];
         }
      }

      if((ReadWord(&RAM_BG[ta+2])&0x8000)!=0){
         for(rx=x+bb;rx<320+32;rx++){
            BIT[(bmp_x+bmp_w-1)-(rx)] = map[0];
         }
      }

      map = &r_map[(pal<<4) + 12];

      for(rx=aa;rx<bb;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            BIT[(bmp_x+bmp_w-1)-(x+rx)] = map[BIT2[rx]];
         }
      }

      BIT2 -= 0x400;

      map = &r_map[(pal<<4) + 0];

      for(rx=aa-32;rx<aa;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            if(BIT2[512+rx-aa]) BIT[(bmp_x+bmp_w-1)-(x+rx)] = map[BIT2[512+rx-aa]];
         }
      }

      for(rx=bb;rx<bb+32;rx++){
         if(((x+rx)>=32)&&((x+rx)<320+32)){
            if(BIT2[512+rx-bb]) BIT[(bmp_x+bmp_w-1)-(x+rx)] = map[BIT2[512+rx-bb]];
         }
      }

      }

      }

      y++;
   }

   }
}
