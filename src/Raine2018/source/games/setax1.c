/******************************************************************************/
/*                                                                            */
/*        SETA X1-001A/002A/006/004/003: SETA & TAITO VIDEO HARDWARE          */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "setax1.h"
#include "blit.h" // clear_game_screen

/*

CHIP DATA
---------

BALLOON BROS:

SETA X1-001A
SETA X1-002A
SETA X1-004

KAGEKI:

SETA X1-002A
SETA X1-003
SETA X1-004
SETA X1-006

DAISENPU:

SETA X1-001A
SETA X1-002A
SETA X1-004
SETA X1-006
SETA X1-007

ARKANOID 2:

SETA X1-001
SETA X1-002
SETA X1-003
SETA X1-004

M68000 MAPPING
--------------

VIDEO RAM - SECTION A

 - there is no bank switching for double buffer

--------------+---------------------+------------------
Address Range |     Used Bit(s)     | Information
--------------+-FEDC-BA98-7654-3210-+------------------
D00000-D003FF | .... ...x xxxx xxxx | Sprite Y
D00400-D005FF | .... .... xxxx xxxx | BG0 Strip X and Y
D00600-D007FF | .... .... .... .... | Control Data
--------------+---------------------+------------------

VIDEO RAM - SECTION B

- there is bank switching for double buffer

--------------+---------------------+------+------------------
Address Range |     Used Bit(s)     | Bank |Information
--------------+-FEDC-BA98-7654-3210-+------+------------------
E00000-E003FF | ..xx xxxx xxxx xxxx |   A  | Tile Number
''''''-'''''' | .x.. .... .... .... |   A  | Flip X Axis
''''''-'''''' | x... .... .... .... |   A  | Flip Y Axis
E00400-E007FF | .... ...x xxxx xxxx |   A  | Sprite X
''''''-'''''' | xxxx x... .... .... |   A  | Colour Bank
E00800-E00BFF | ..xx xxxx xxxx xxxx |   A  | BG0 Strip Tile Number
''''''-'''''' | .x.. .... .... .... |   A  | BG0 Strip Flip X Axis
''''''-'''''' | x... .... .... .... |   A  | BG0 Strip Flip Y Axis
E00C00-E00FFF | xxxx x... .... .... |   A  | BG0 Strip Colour Bank
E02000-E023FF | ..xx xxxx xxxx xxxx |   B  | Tile Number
''''''-'''''' | .x.. .... .... .... |   B  | Flip X Axis
''''''-'''''' | x... .... .... .... |   B  | Flip Y Axis
E02400-E027FF | .... ...x xxxx xxxx |   B  | Sprite X
''''''-'''''' | xxxx x... .... .... |   B  | Colour Bank
E02800-E02BFF | ..xx xxxx xxxx xxxx |   B  | BG0 Strip Tile Number
''''''-'''''' | .x.. .... .... .... |   B  | BG0 Strip Flip X Axis
''''''-'''''' | x... .... .... .... |   B  | BG0 Strip Flip Y Axis
E02C00-E02FFF | xxxx x... .... .... |   B  | BG0 Strip Colour Bank
--------------+---------------------+------+------------------

CONTROL DATA

-----+--------+-------------------------
Byte | Bit(s) | Information
-----+76543210+-------------------------
  1  |.x......| Screen Invert
  3  |....xxxx| BG0 Strip Count
  3  |.x......| Double Buffer Bank
  5  |xxxxxxxx| BG0 Strip Y high (0-7)
  7  |xxxxxxxx| BG0 Strip Y high (8-15)
-----+--------+-------------------------

Z80
---

0000-01FF | Tile (low)
0200-03FF | X (low)
0400-05FF | BG0 Tile (low)
0600-07FF | BG0 Colour (low)
1000-11FF | Tile (high)
1200-13FF | X (high)
1400-15FF | BG0 Tile (high)
1600-17FF | BG0 Colour (low)

3000-31FF | Sprite Y
3200-32FF | BG0 X/Y
3300-33FF | Control Data

- Line enable is number of lines to draw:
    0  = draw no lines
    1  = draw all 16 lines
  2-15 = draw 2-15 lines

Todo:

 - test mode hatch is not showing in extermination, enable problem?
 - screen invert (added it to z80 version, because chuka taisen seems
   to require it)

*/

#define MASK_X	(0x1FF)
#define MASK_Y	(0x0FF)

void render_seta_x1_68000(void)
{
   int zz,zzz,z,x16,y16,x,y,ta,rx,ry;
   int st,tb;
   UINT32 tile_mask;
   UINT8 *map;
   UINT8 *RAM_BGA;
   UINT8 *RAM_BGB;

   UINT8 *RAM_A;
   UINT8 *RAM_B;

   UINT8 *GFX_SPR;
   UINT8 *GFX_SPR_SOLID;

   UINT32 bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_A     = seta_x1.RAM_A;
   RAM_B     = seta_x1.RAM_B;

   bmp_w     = seta_x1.bmp_w;
   bmp_h     = seta_x1.bmp_h;
   scr_x     = seta_x1.scr_x;
   scr_y     = seta_x1.scr_y;

   GFX_SPR       = seta_x1.GFX;
   GFX_SPR_SOLID = seta_x1.MASK;

   tile_mask     = seta_x1.tile_mask;

   // BASE SCREEN COLOUR

   MAP_PALETTE_MAPPED_NEW(
      0x1F,
      16,
      map
   );

   clear_game_screen(map[0]);

   // BACK

   if( (ReadWord(&RAM_B[0x0602])&0x40) == 0){

   RAM_BGA = RAM_A + 0x0800;
   RAM_BGB = RAM_A + 0x0C00;

   }
   else{

   RAM_BGA = RAM_A + 0x2800;
   RAM_BGB = RAM_A + 0x2C00;

   }

   st = ReadWord(&RAM_B[0x0602])&0x0F;

   if(is_current_game("gigandes")){
     if((st==0) && (ReadWord(&RAM_B[2])==0xfa)){
       RAM_BGA = RAM_A + 0x0800;
       RAM_BGB = RAM_A + 0x0C00;
       st = 0xd;
     }
   }

   if(st!=0){

   if(st==1) st=16;

   tb = ( ((ReadWord(&RAM_B[0x0604])&0xFF)<<8) | ((ReadWord(&RAM_B[0x0606])&0xFF)<<16) );

   for(zzz=0;zzz<st;zzz++){

   z = zzz<<5;

   x16 = ((16+ (ReadWord(&RAM_B[0x0408+z]) | (tb&0x100))) + scr_x) & MASK_X;
   y16 = ((((249+16) - ReadWord(&RAM_B[0x0400+z]))) + scr_y) & MASK_Y;

   tb >>= 1;

   z <<= 1;

      y = y16;

      for(ry=0;ry<0x10;ry++){

      x = x16;

      for(rx=0;rx<0x02;rx++){

      if((x>16)&&(y>0)&&((UINT32)x<bmp_w+32)&&((UINT32)y<bmp_h+16)){

         ta = ReadWord(&RAM_BGA[z])&tile_mask;

         if(GFX_SPR_SOLID[ta]){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord(&RAM_BGB[z])>>11,
            16,
            map
         );

         if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
            switch(ReadWord(&RAM_BGA[z])&0xC000){
            case 0x0000: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y+16, map);        break;
            case 0x4000: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0x8000: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0xC000: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y+16, map); break;
            }
         }
         else{						// all pixels; solid
            switch(ReadWord(&RAM_BGA[z])&0xC000){
            case 0x0000: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8], x, y+16, map);        break;
            case 0x4000: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0x8000: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0xC000: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y+16, map); break;
            }
         }

         }

      }

      x = (x+16)&MASK_X;
      z += 2;

      }

      y = (y+16)&0x0FF;

      }

   }

   }

   // OBJECT

   if( (ReadWord(&RAM_B[0x0602])&0x40) == 0){

   RAM_BGA = RAM_A + 0x0000;
   RAM_BGB = RAM_A + 0x0400;

   }
   else{

   RAM_BGA = RAM_A + 0x2000;
   RAM_BGB = RAM_A + 0x2400;

   }

   for(zz=0x3FE;zz>=0;zz-=2){

      x = ((16+ReadWord(&RAM_BGB[zz])) + scr_x) & MASK_X;
      y = (((250+0)-ReadWord(&RAM_B[zz])) + scr_y) & MASK_Y;

      if((x>16)&&(y>0)&&((UINT32)x<bmp_w+32)&&((UINT32)y<bmp_h+16)){

         ta = ReadWord(&RAM_BGA[zz])&tile_mask;

         if(GFX_SPR_SOLID[ta]){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ReadWord(&RAM_BGB[zz])>>11,
            16,
            map
         );

         if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
            switch(ReadWord(&RAM_BGA[zz])&0xC000){
            case 0x0000: Draw16x16_Trans_Mapped_Rot(&GFX_SPR[ta<<8], x, y+16, map);        break;
            case 0x4000: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0x8000: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0xC000: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y+16, map); break;
            }
         }
         else{						// all pixels; solid
            switch(ReadWord(&RAM_BGA[zz])&0xC000){
            case 0x0000: Draw16x16_Mapped_Rot(&GFX_SPR[ta<<8], x, y+16, map);        break;
            case 0x4000: Draw16x16_Mapped_FlipX_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0x8000: Draw16x16_Mapped_FlipY_Rot(&GFX_SPR[ta<<8], x, y+16, map);  break;
            case 0xC000: Draw16x16_Mapped_FlipXY_Rot(&GFX_SPR[ta<<8], x, y+16, map); break;
            }
         }

         }

      }
   }
}

void render_seta_x1_z80(void)
{
   int zz,zzz,z,x16,y16,x,y,ta;
#if 0
   int rx,ry;
#endif
   int st,tb;
   UINT8 *map;
   UINT8 *RAM_BGA;
   UINT8 *RAM_BGB;

   UINT8 *RAM_A;
   UINT8 *RAM_B;

   UINT8 *GFX_SPR_SOLID;

   RAM_A     = seta_x1.RAM_A;
   RAM_B     = seta_x1.RAM_B;

   GFX_SPR_SOLID = seta_x1.MASK;


   // BASE SCREEN COLOUR

   MAP_PALETTE_MAPPED_NEW(
      0x1F,
      16,
      map
   );

   clear_game_screen(map[0]);


   if( ((RAM_B[0x0300])&0x40) == 0){ // flip screen

#if 0

   // BACK

   if( ((RAM_B[0x0301])&0x40) == 0){

   RAM_BGA = RAM_A + 0x00400;
   RAM_BGB = RAM_A + 0x00600;

   }
   else{

   RAM_BGA = RAM_A + 0x00C00;
   RAM_BGB = RAM_A + 0x00E00;

   }

   st = (RAM_B[0x0301])&0x0F;

   if(st!=0){

   if(st==1) st=16;

   tb = ( (((RAM_B[0x0302])&0xFF)<<8) | ((RAM_B[0x0303])&0xFF)<<16);

   for(zzz=0;zzz<st;zzz++){

   z = (zzz<<4)^0x80;

   x16 = ((16+ ((RAM_B[0x0204+z]) | (tb&0x100))) + scr_x) & MASK_X;
   y16 = ((((249+16) - (RAM_B[0x0200+z]))) + scr_y) & MASK_Y;

   tb >>= 1;

   z <<= 1;

      y = y16;

      for(ry=0;ry<0x10;ry++){

      x = x16;

      for(rx=0;rx<0x02;rx++){

      if((x>16)&&(y>0)&&(x<bmp_w+32)&&(y<bmp_h+16)){

   		ta = ((RAM_BGA[z+0x1000]<<8)|(RAM_BGA[z])) & 0x1FFF;

         if(GFX_SPR_SOLID[ta]){				// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BGB[z+0x1000]>>3,
            16,
            map
         );

         if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
            switch(RAM_BGA[z+0x1000]&0xC0){
            case 0x0000: Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8], x, y+16, map);        break;
            case 0x4000: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[ta<<8], x, y+16, map);  break;
            case 0x8000: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[ta<<8], x, y+16, map);  break;
            case 0xC000: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[ta<<8], x, y+16, map); break;
            }
         }
         else{						// all pixels; solid
            switch(RAM_BGA[z+0x1000]&0xC0){
            case 0x0000: Draw16x16_Mapped_Rot(&GFX[ta<<8], x, y+16, map);        break;
            case 0x4000: Draw16x16_Mapped_FlipX_Rot(&GFX[ta<<8], x, y+16, map);  break;
            case 0x8000: Draw16x16_Mapped_FlipY_Rot(&GFX[ta<<8], x, y+16, map);  break;
            case 0xC000: Draw16x16_Mapped_FlipXY_Rot(&GFX[ta<<8], x, y+16, map); break;
            }
         }

         }

      }

      x = (x+16)&MASK_X;
      z += 1;

      }

      y = (y+16)&0x0FF;

      }

   }

   }

#else

   // BACK

   if( ((RAM_B[0x0301])&0x40) == 0){

   RAM_BGA = RAM_A + 0x00400;
   RAM_BGB = RAM_A + 0x00600;

   }
   else{

   RAM_BGA = RAM_A + 0x00C00;
   RAM_BGB = RAM_A + 0x00E00;

   }

   st = RAM_B[0x0301]&0x0F;

   if(st!=0){

   if(st==1) st=16;

   tb = ReadWord(&RAM_B[0x0302])<<8;
   tb |= ReadWord(&RAM_B[0x0382])<<8;

   for(zzz=0;zzz<st;zzz++){

   z=(zzz<<5)^0x100;

   x16 = (RAM_B[0x0204+((z>>1)^0x80)] | (tb&0x100)) + 32;
   y16 = ((256+16) - RAM_B[0x0200+((z>>1)^0x80)]) + 1;

   tb >>= 1;

   for(zz=z;zz<(z+0x20);zz++){

   ta = ((RAM_BGA[zz+0x1000]<<8)|(RAM_BGA[zz])) & 0x1FFF;

   if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

   x=(x16+((zz&0x01)<<4))&MASK_X;
   y=(y16+((zz&0x1E)<<3))&MASK_Y;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){

      MAP_PALETTE_MAPPED_NEW(
         RAM_BGB[zz+0x1000]>>3,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[ta<<8],x,y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[ta<<8],x,y,map); break;
         }
      }

   }
   }

   }
   }

   }

#endif

   // OBJECT

   if( ((RAM_B[0x0301])&0x40) == 0){

   RAM_BGA = RAM_A + 0x00000;
   RAM_BGB = RAM_A + 0x00200;

   }
   else{

   RAM_BGA = RAM_A + 0x00800;
   RAM_BGB = RAM_A + 0x00A00;

   }

   for(zz=0x1FF;zz>=0;zz--){

      x = (32+((RAM_BGB[zz+0x1000]<<8)|(RAM_BGB[zz]))) & MASK_X;
      if((x>16)&&(x<256+32)){

      y = ((224+32+2)-(RAM_B[zz])) & MASK_Y;
      if((y>16)&&(y<224+32)){

      ta = ((RAM_BGA[zz+0x1000]<<8)|(RAM_BGA[zz])) & 0x1FFF;

      if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM_BGB[zz+0x1000]>>3,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0x00: Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[ta<<8],x,y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0x00: Draw16x16_Mapped_Rot(&GFX[ta<<8],x,y,map);        break;
         case 0x40: Draw16x16_Mapped_FlipX_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0x80: Draw16x16_Mapped_FlipY_Rot(&GFX[ta<<8],x,y,map);  break;
         case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&GFX[ta<<8],x,y,map); break;
         }
      }

      }

      }
      }
   }


   }
   else{


   // BACK

   if( ((RAM_B[0x0301])&0x40) == 0){

   RAM_BGA = RAM_A + 0x00400;
   RAM_BGB = RAM_A + 0x00600;

   }
   else{

   RAM_BGA = RAM_A + 0x00C00;
   RAM_BGB = RAM_A + 0x00E00;

   }

   st = RAM_B[0x0301]&0x0F;

   if(st!=0){

   if(st==1) st=16;

   tb = ReadWord(&RAM_B[0x0302])<<8;

   for(zzz=0;zzz<st;zzz++){

   z=(zzz<<5)^0x100;

   x16 = (RAM_B[0x0204+((z>>1)^0x80)] | (tb&0x100)) + 32;
   y16 = ((256+16) - RAM_B[0x0200+((z>>1)^0x80)]) + 1 - 2;

   tb >>= 1;

   for(zz=z;zz<(z+0x20);zz++){

   ta = ((RAM_BGA[zz+0x1000]<<8)|(RAM_BGA[zz])) & 0x1FFF;

   if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

   x=(x16+((zz&0x01)<<4))&MASK_X;
   y=(y16+((zz&0x1E)<<3))&MASK_Y;

   if((x>16)&&(y>16)&&(x<256+32)&&(y<224+32)){

      MAP_PALETTE_MAPPED_NEW(
         RAM_BGB[zz+0x1000]>>3,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0xC0: Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8],x,224+48-y,map);        break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x00: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[ta<<8],x,224+48-y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0xC0: Draw16x16_Mapped_Rot(&GFX[ta<<8],x,224+48-y,map);        break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x00: Draw16x16_Mapped_FlipXY_Rot(&GFX[ta<<8],x,224+48-y,map); break;
         }
      }

   }
   }

   }
   }

   }

   // OBJECT

   if( ((RAM_B[0x0301])&0x40) == 0){

   RAM_BGA = RAM_A + 0x00000;
   RAM_BGB = RAM_A + 0x00200;

   }
   else{

   RAM_BGA = RAM_A + 0x00800;
   RAM_BGB = RAM_A + 0x00A00;

   }

   for(zz=0x1FF;zz>=0;zz--){

      x = (32+((RAM_BGB[zz+0x1000]<<8)|(RAM_BGB[zz]))) & MASK_X;
      if((x>16)&&(x<256+32)){

      y = ((224+32+2-4)-(RAM_B[zz])) & MASK_Y;
      if((y>16)&&(y<224+32)){

      ta = ((RAM_BGA[zz+0x1000]<<8)|(RAM_BGA[zz])) & 0x1FFF;

      if(GFX_SPR_SOLID[ta]!=0){			// No pixels; skip

      MAP_PALETTE_MAPPED_NEW(
         RAM_BGB[zz+0x1000]>>3,
         16,
         map
      );

      if(GFX_SPR_SOLID[ta]==1){			// Some pixels; trans
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0xC0: Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8],x,224+48-y,map);        break;
         case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x00: Draw16x16_Trans_Mapped_FlipXY_Rot(&GFX[ta<<8],x,224+48-y,map); break;
         }
      }
      else{					// all pixels; solid
         switch(RAM_BGA[zz+0x1000]&0xC0){
         case 0xC0: Draw16x16_Mapped_Rot(&GFX[ta<<8],x,224+48-y,map);        break;
         case 0x80: Draw16x16_Mapped_FlipX_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x40: Draw16x16_Mapped_FlipY_Rot(&GFX[ta<<8],x,224+48-y,map);  break;
         case 0x00: Draw16x16_Mapped_FlipXY_Rot(&GFX[ta<<8],x,224+48-y,map); break;
         }
      }

      }

      }
      }
   }


   }
}
