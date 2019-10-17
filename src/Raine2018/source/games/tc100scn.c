/******************************************************************************/
/*                                                                            */
/*             tc0100scn: TAITO SCREEN LAYER CHIP (BG0/BG1/FG0)               */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc100scn.h"
#include "lspr8.h"

extern int layer_id_data[MAX_CHIP][3];

/*

SCREEN RAM
----------
(standard)

----------+-----------------------------
 Range    | Use
----------+-----------------------------
0000-3FFF | BG0 Layer [512x512x8: 4 bytes]
4000-5FFF | FG0 Layer [512x512x8: 2 bytes]
6000-7FFF | FG0 GFX
8000-BFFF | BG1 Layer [512x512x8: 4 bytes]
C000-C7FF | Line-Line Scroll? (AquaJack)

From mame:
c000-c3ff BG0 rowscroll (second half unused*)
c400-c7ff BG1 rowscroll (second half unused*)
e000-e0ff BG0 colscroll [see info below]

E000-E0FF | ? (AquaJack)
----------+-----------------------------

Double width tilemaps memory layout (two 128x64 tilemaps, one 128x32 tilemap)

00000-07fff BG0 (128x64)
08000-0ffff BG1 (128x64)
10000-103ff BG0 rowscroll (second half unused*)
10400-107ff BG1 rowscroll (second half unused*)
10800-108ff BG0 colscroll [evidenced by Warriorb inits from $1634]
10900-10fff unused (probably)
11000-11fff gfx data for FG0
12000-13fff FG0 (128x32)

* Perhaps Taito wanted potential for double height tilemaps on the
  TC0100SCN. The inits state the whole area is "linescroll".


SCROLL RAM
----------

-----+--------+-------------------------
Byte | Bit(s) | Use
-----+76543210+-------------------------
  0  |.......x| BG0 Scroll X
  1  |xxxxxxxx| BG0 Scroll X
  2  |.......x| BG1 Scroll X
  3  |xxxxxxxx| BG1 Scroll X
  4  |.......x| FG0 Scroll X
  5  |xxxxxxxx| FG0 Scroll X
  6  |.......x| BG0 Scroll Y
  7  |xxxxxxxx| BG0 Scroll Y
  8  |.......x| BG1 Scroll Y
  9  |xxxxxxxx| BG1 Scroll Y
  A  |.......x| FG0 Scroll Y
  B  |xxxxxxxx| FG0 Scroll Y
  D  |.......x| BG0 Disable
  D  |......x.| BG1 Disable
  D  |.....x..| FG0 Disable
  D  |....x...| Swap BG0:BG1
  D  |...x....| double width tilemaps + different memory map (mame)
                 (cameltru and all the multi-screen games)
  F  |.......x| Screen Flip
  F  |..x.....| Priority for 2 chips?
-----+--------+-------------------------

Not implemented:

- FG0 seems to be offset differently in some games.
- The variable stuff is slower, unless it can use self
  modifying code, so need to convert to asm.
- Need to add support for different screen orientations
  (screen flip Y-Axis, screen rotate 90 degrees).
- Line-line scroll is used occasionally (Chase HQ).
- FG0 gfx mask is missing (might be faster, might not make
  much difference).

Direct Mapped Games:

Bonze Adventure/Jigoku	- OK
Cadash/Cadash Italian	- OK (title screen might use line-line scroll)
Mega Blast		- OK
Camel Try		- OK (only need FG0)
Growl			- OK (fg0 is different offset in test mode)
Ninja Kids		- OK
Thunder Fox		- OK (priorities between dual tc0100scn and sprites wrong)
Operation Wolf		- OK (Old/Split scroll ram)
Rastan			- ? (Old/Split scroll ram)
Rainbow Islands		- ? (Old/Split scroll ram)

Mapped Games:

Final Blow		- OK
Chase HQ		- OK (uses line-line scroll)
Pulirula		- OK
AquaJack		- OK
Dino Rex		- OK
Night Striker		- OK (uses line-line scroll)
Chase HQ 2		- ?
Continental Circus	- ?

Mapped rotate 270° games:

Maze of Flott		- OK
Earth Joker		- OK
Asuka & Asuka		- OK (don't need FG0)
Gun Frontier		- OK

Direct Mapped rotate 180° games:

Liquid Kids		- OK
Don Doko Don		- OK

Mapped Flip-Y Axis games:

Space Gun		- OK (hiscores use line-line scroll?)
Operation Thunderbolt   - OK
Battle Shark		- OK

*/

/******************************************************************************/

static INT16 *bgscroll_ram;

#define WIDTH 512
#define HEIGHT 512
#define N 4

static void scroll_512_bg0_lscroll(TC0100SCN_LAYER *tc_layer, int trans) {
  int zz,zzz,zzzz,x16,y16,x,y,ta;
  UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 tile_mask;
   UINT32 bmp_y,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_y = tc_layer->bmp_y;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x -(ReadWord(RAM_SCR+0));
   scr_y = tc_layer->scr_y -(ReadWord(RAM_SCR+6));
   RAM_MSK = tc_layer->MASK;
   if ((ReadWord(tc0100scn[0].layer[0].SCR + 14) & 1)) {// flip layer ?
     scr_y += 16;
   }

  MAKE_SCROLL_512x512_4_8(
			    scr_x,
			    scr_y
			    );

  zz=zzzz;
  for(y=(bmp_y-y16);(UINT32)y<(bmp_h+bmp_y);y+=8){
    int min = 999, max = -999;
    int n;
    INT16 *offs = &bgscroll_ram[y+8-bmp_y];

    if (y<32) {
      zz = zzzz = (zzzz+(WIDTH*N/8))&(WIDTH*HEIGHT*N/(8*8)-1);
      continue;
    }


    for (n=0; n<8; n++) {
      ta = offs[n];
      if (min > ta)
	min = ta;
      if (max < ta)
	max = ta;
    }
    if (min) {
      if (min & 7) /* min is not on the limit of a sprite */
	min = (min > 0) ? min/8 : min/8 - 1;
      else
	min /= 8;
    }
    if (max) {
      if (max & 7)
	max = max/8 +1;
      else
	max /= 8;
    }
    if (max || min) { /* some line scroll for this line */

      /* Start earlier, finish later... */
/*       if (32-x16-max*8 < 0 || min < 0) { */
/* 	zz = zzzz = (zzzz+(WIDTH*N/8))&(WIDTH*HEIGHT*N/(8*8)-1); */
/* 	continue; */
/*       } */

      zz=(zz&(WIDTH*HEIGHT*N/(8*8)-WIDTH*N/8))|((zz-max*N)&(WIDTH*N/8-1));
      if (trans) {
	for(x=(32-x16-max*8);x<(320+32-min*8);x+=8){

	  ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
	  if(RAM_MSK[ta]!=0){			// No pixels; skip

	    MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
              16,
              map
            );

	    if(RAM_MSK[ta]==1){			// Some pixels; trans
	      switch(RAM_BG[1+zz]&0xC0){
	      case 0x00: ldraw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map,offs);        break;
	      case 0x40: ldraw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map,offs);  break;
	      case 0x80: ldraw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map,offs);  break;
	      case 0xC0: ldraw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map,offs); break;
	      }
	    }else{					// all pixels; solid
	      switch(RAM_BG[1+zz]&0xC0){
	      case 0x00: ldraw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map,offs);        break;
	      case 0x40: ldraw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map,offs);  break;
	      case 0x80: ldraw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map,offs);  break;
	      case 0xC0: ldraw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map,offs); break;
	      }
	    }
	  }
	  zz=(zz&(WIDTH*HEIGHT*N/(8*8)-WIDTH*N/8))|((zz+N)&(WIDTH*N/8-1));
	} // loop
      } else { // no transparency...
	for(x=(32-x16-max*8);x<(320+32-min*8);x+=8){

	  ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
	  MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
              16,
              map
            );

	  switch(RAM_BG[1+zz]&0xC0){
	  case 0x00: ldraw8x8_Mapped_Rot(&RAM_GFX[(ta)<<6],x,y,map,offs);        break;
	  case 0x40: ldraw8x8_Mapped_FlipY_Rot(&RAM_GFX[(ta)<<6],x,y,map,offs);  break;
	  case 0x80: ldraw8x8_Mapped_FlipX_Rot(&RAM_GFX[(ta)<<6],x,y,map,offs);  break;
	  case 0xC0: ldraw8x8_Mapped_FlipXY_Rot(&RAM_GFX[(ta)<<6],x,y,map,offs); break;
	  }
	  zz=(zz&(WIDTH*HEIGHT*N/(8*8)-WIDTH*N/8))|((zz+N)&(WIDTH*N/8-1));
	} // loop
      } // transparency test
    } else { /* no line scroll for this line... */
      if (trans) {
	for(x=(32-x16);x<(320+32);x+=8){
	  ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
	  if(RAM_MSK[ta]!=0){			// No pixels; skip

	    MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
	    );

	    if(RAM_MSK[ta]==1){			// Some pixels; trans
	      switch(RAM_BG[1+zz]&0xC0){
	      case 0x00: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
	      case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
	      case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
	      case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
	      }
	    } else { // all solid
	      switch(RAM_BG[1+zz]&0xC0){
	      case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
	      case 0x40: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
	      case 0x80: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
	      case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
	      }
	    }
	  }
	  zz=(zz&(WIDTH*HEIGHT*N/(8*8)-WIDTH*N/8))|((zz+N)&(WIDTH*N/8-1));
	} // loop
      } else{					// all pixels; solid
	for(x=(32-x16);x<(320+32);x+=8){
	  ta=ReadWord(&RAM_BG[2+zz])&tile_mask;

	    MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
	    );

	    switch(RAM_BG[1+zz]&0xC0){
	    case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
	    case 0x40: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
	    case 0x80: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
	    case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
	    }
	    zz=(zz&(WIDTH*HEIGHT*N/(8*8)-WIDTH*N/8))|((zz+N)&(WIDTH*N/8-1));
	}
      }
    }
    zz = zzzz = (zzzz+(WIDTH*N/8))&(WIDTH*HEIGHT*N/(8*8)-1);
  } // for y
}

static void render_bg0_mapped(TC0100SCN_LAYER *tc_layer, int trans)
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

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x -(ReadWord(RAM_SCR+0));
   scr_y = tc_layer->scr_y -(ReadWord(RAM_SCR+6));
   if ((ReadWord(tc0100scn[0].layer[0].SCR + 14) & 1)) { // flip layer ?
     // flipping is not emulated in raine, because I don't see why it would be interesting
     // we need to compensate the y coordinate though to make it look exactly like a normal
     // screen
     scr_y += 16;
   }

   // fprintf(stderr,"bg %d,%d -> %d,%d flipped %d\n",ReadWord(RAM_SCR+0),ReadWord(RAM_SCR+6),scr_x,scr_y,ReadWord(tc0100scn[0].layer[0].SCR + 14) & 1);

   MAKE_SCROLL_512x512_4_8(
         scr_x,
         scr_y
	 );

   if (trans) {
     RAM_MSK = tc_layer->MASK;
     START_SCROLL_512x512_4_8(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x40: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_4_8();
   } else {

      START_SCROLL_512x512_4_8(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[(ta)<<6],x,y,map);        break;
         case 0x40: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[(ta)<<6],x,y,map);  break;
         case 0x80: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[(ta)<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[(ta)<<6],x,y,map); break;
         }

      END_SCROLL_512x512_4_8();
   }
}

void render_fg0scr_transparent_mapped_2(TC0100SCN_LAYER *tc_layer)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   //UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   RAM_MSK = tc_layer->MASK;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   //tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;
  if ((ReadWord(tc0100scn[0].layer[0].SCR + 14) & 1)) { // flip layer ?
    // flipping is not emulated in raine, because I don't see why it would be interesting
    // we need to compensate the y coordinate though to make it look exactly like a normal
    // screen
    // it can be checked in liquid kids when player 2 starts to play, the screen is flipped
    scr_y += 16;
  }

      MAKE_SCROLL_512x512_2_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_2_8(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=RAM_BG[zz];

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x40: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x40: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_2_8();
}

void render_tc0100scn_layer_mapped(int chip, int layer, int transp)
{
   TC0100SCN *tchip;
   int ta,lscroll=0;
   UINT16 *bgcol_ram = NULL;;

   if(!check_layer_enabled(layer_id_data[chip][layer]))
       return;

   tchip = &tc0100scn[chip];

   // Check Layer Disable bits
   // ------------------------
   if((tchip->ctrl & (1<<layer))!=0) return;
   if (!tchip->RAM) return;

   // Check BG0/BG1 flip
   // ------------------

   if(((tchip->ctrl & 0x08)!=0)&&(layer<2)) layer^=1;

   if (layer < 2) {
     if (layer)
       bgscroll_ram =  (INT16*)(tchip->RAM + 0xc400);
     else {
       bgscroll_ram =  (INT16*)(tchip->RAM + 0xc000);
#ifdef RAINE_DEBUG
       // In test, I am not really convinced it's worth being emulated.
       // I am almost sure it's not worth it in fact !
       bgcol_ram =  (UINT16*)(tchip->RAM + 0xe000);
       for (ta=0; ta<128; ta++)
	 if (bgcol_ram[ta]) {
	   print_ingame(1,"cscroll");
	   break;
	 }
#endif
     }


     for (ta=0; ta<240; ta++)
       if (bgscroll_ram[ta]) {
	 lscroll = 1;
	 break;
	 // bgscroll_ram[ta] = -bgscroll_ram[ta];
       }
   }

#ifdef RAINE_DEBUG
   if (lscroll) {
     print_ingame(1,"lscroll chip %d layer %d trans %d",chip,layer,transp);
   }
#endif

   switch(tchip->layer[layer].type){
      case SCN_BG0:				// [BG0/BG1: 512x512; 8x8 TILE ROM]
	if (lscroll)
	  scroll_512_bg0_lscroll(&tchip->layer[layer],transp);
	else
	  render_bg0_mapped(&tchip->layer[layer],transp);
	break;
      case SCN_FG0:				// [FG0: 512x512; 8x8 TILE RAM]
      case SCN_FG0_SCROLL:			// [FG0: 512x512; 8x8 TILE RAM + SCROLLING]
	//render_fg0scr_transparent_mapped(&tchip->layer[layer],transp);
	//break;
      case SCN_FG0_SCROLL_2:		// [FG0: 512x512; 8x8 TILE RAM + SCROLLING]
      tc0100scn_update_gfx_fg0(chip);
      render_fg0scr_transparent_mapped_2(&tchip->layer[layer]);
      break;
   }
}

/******************************************************************************/

void render_bg0_solid_mapped_r270(TC0100SCN_LAYER *tc_layer)
{
   int x,y,x16,y16,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_4_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_4_8_R270(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);        break;
         case 0x80: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);  break;
         case 0x40: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map); break;
         }

      END_SCROLL_512x512_4_8();
}


void render_bg0_transparent_mapped_r270(TC0100SCN_LAYER *tc_layer)
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

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   RAM_MSK = tc_layer->MASK;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_4_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_4_8_R270(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x80: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x40: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x80: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x40: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_4_8();
}


void render_fg0_solid_mapped_r270(TC0100SCN_LAYER *tc_layer)
{
   int x,y,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   // RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=48){
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=2){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x00: Draw8x8_Mapped_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);        break;
         case 0x80: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);  break;
         case 0x40: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map); break;
         }
      }
      }
}


void render_fg0_transparent_mapped_r270(TC0100SCN_LAYER *tc_layer)
{
   int x,y,zzzz,zzz,zz,z;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   // RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(x=bmp_x;(UINT32)x<(bmp_w+bmp_x);x+=8,zz+=48){
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=2){
         if((z=RAM_BG[zz])!=0){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x00: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[z<<6],x,y,map);        break;
         case 0x80: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[z<<6],x,y,map);  break;
         case 0x40: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[z<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[z<<6],x,y,map); break;
         }

         }
      }
      }
}


void render_fg0scr_transparent_mapped_r270(TC0100SCN_LAYER *tc_layer)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   //UINT8 *RAM_MSK;
   //UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   //RAM_MSK = tc_layer->MASK;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   //tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_2_8_R270(bmp_x,bmp_y,bmp_w,bmp_h);

         if((ta=RAM_BG[zz])!=0){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x00: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
         case 0x80: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
         case 0x40: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
         }

         }

      END_SCROLL_512x512_2_8();
}


void render_tc0100scn_layer_mapped_r270(int chip, int layer)
{
   TC0100SCN *tchip;

   if(!check_layer_enabled(layer_id_data[chip][layer]))
       return;

   tchip = &tc0100scn[chip];

   // Check BG0/BG1 flip
   // ------------------

   if(((tchip->ctrl & 0x08)!=0)&&(layer<2)) layer^=1;

   if (layer < 2) {
     int ta;
     if (layer)
       bgscroll_ram =  (INT16*)(tchip->layer[0].RAM + 0xc400);
     else
       bgscroll_ram =  (INT16*)(tchip->layer[0].RAM + 0xc000);

     for (ta=0; ta<240; ta++)
       if (bgscroll_ram[ta]) {
#ifdef RAINE_DEBUG
	 print_ingame(1,"lscroll");
#endif
	 // bgscroll_ram[ta] = -bgscroll_ram[ta];
       }
   }

   // Check Layer Disable bits
   // ------------------------

   if((tchip->ctrl & (1<<layer))!=0) return;

   if(tc0100scn_layer_count==0){		// [SOLID]

   switch(tchip->layer[layer].type){
      case SCN_BG0:				// [BG0/BG1: 512x512; 8x8 TILE ROM]
      render_bg0_solid_mapped_r270(&tchip->layer[layer]);
      break;
      case SCN_FG0:				// [FG0: 512x512; 8x8 TILE RAM]
      render_fg0_solid_mapped_r270(&tchip->layer[layer]);
      break;
   }

   }
   else{					// [TRANSPARENT]

   switch(tchip->layer[layer].type){
      case SCN_BG0:				// [BG0/BG1: 512x512; 8x8 TILE ROM]
      render_bg0_transparent_mapped_r270(&tchip->layer[layer]);
      break;
      case SCN_FG0:				// [FG0: 512x512; 8x8 TILE RAM]
      render_fg0_transparent_mapped_r270(&tchip->layer[layer]);
      break;
      case SCN_FG0_SCROLL:			// [FG0: 512x512; 8x8 TILE RAM + SCROLLING]
      render_fg0scr_transparent_mapped_r270(&tchip->layer[layer]);
      break;
   }

   }

   tc0100scn_layer_count++;
}

/******************************************************************************/

void render_bg0_solid_mapped_flipy(TC0100SCN_LAYER *tc_layer)
{
   int x,y,x16,y16,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_4_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_4_8_FLIPY(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x40: Draw8x8_Mapped_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);        break;
         case 0x00: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);  break;
         case 0x80: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map); break;
         }

      END_SCROLL_512x512_4_8();
}

void render_bg0_transparent_mapped_flipy(TC0100SCN_LAYER *tc_layer)
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

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   RAM_MSK = tc_layer->MASK;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_4_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_4_8_FLIPY(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0x40: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x00: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x40: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x00: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_4_8();
}


void render_fg0_solid_mapped_flipy(TC0100SCN_LAYER *tc_layer)
{
   int x,y,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   // RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<(bmp_h+bmp_y);y+=8,zz+=48){
      for(x=(bmp_w+bmp_x-8);(UINT32)x>=bmp_x;x-=8,zz+=2){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x40: Draw8x8_Mapped_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);        break;
         case 0x00: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);  break;
         case 0x80: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map); break;
         }
      }
      }
}

void render_fg0_transparent_mapped_flipy(TC0100SCN_LAYER *tc_layer)
{
   int x,y,zzzz,zzz,zz,z;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   // RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=bmp_y;(UINT32)y<(bmp_h+bmp_y);y+=8,zz+=48){
      for(x=(bmp_w+bmp_x-8);(UINT32)x>=bmp_x;x-=8,zz+=2){
         if((z=RAM_BG[zz])!=0){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0x40: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[z<<6],x,y,map);        break;
         case 0x00: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[z<<6],x,y,map);  break;
         case 0xC0: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[z<<6],x,y,map);  break;
         case 0x80: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[z<<6],x,y,map); break;
         }

         }
      }
      }
}

void render_fg0scr_transparent_mapped_flipy_2(TC0100SCN_LAYER *tc_layer)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   //UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   RAM_MSK = tc_layer->MASK;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   //tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_2_8_FLIPY(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=RAM_BG[zz];

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0x40: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x00: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0x40: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x00: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0xC0: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x80: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_2_8();
}

void render_tc0100scn_layer_mapped_flipy(int chip, int layer)
{
   TC0100SCN *tchip;

   if(!check_layer_enabled(layer_id_data[chip][layer]))
       return;

   tchip = &tc0100scn[chip];

   // Check BG0/BG1 flip
   // ------------------

   if(((tchip->ctrl & 0x08)!=0)&&(layer<2)) layer^=1;

   // Check Layer Disable bits
   // ------------------------

   if((tchip->ctrl & (1<<layer))!=0) return;

   if(tc0100scn_layer_count==0){		// [SOLID]

   switch(tchip->layer[layer].type){
      case SCN_BG0:				// [BG0/BG1: 512x512; 8x8 TILE ROM]
      render_bg0_solid_mapped_flipy(&tchip->layer[layer]);
      break;
      case SCN_FG0:				// [FG0: 512x512; 8x8 TILE RAM]
      render_fg0_solid_mapped_flipy(&tchip->layer[layer]);
      break;
   }

   }
   else{					// [TRANSPARENT]

   switch(tchip->layer[layer].type){
      case SCN_BG0:				// [BG0/BG1: 512x512; 8x8 TILE ROM]
      render_bg0_transparent_mapped_flipy(&tchip->layer[layer]);
      break;
      case SCN_FG0_SCROLL_2:			// [FG0: 512x512; 8x8 TILE RAM + SCROLLING]
      tc0100scn_update_gfx_fg0(chip);
      render_fg0scr_transparent_mapped_flipy_2(&tchip->layer[layer]);
      break;
   }

   }

   tc0100scn_layer_count++;
}

/******************************************************************************/

void render_bg0_solid_r180_mapped(TC0100SCN_LAYER *tc_layer)
{
   int x,y,x16,y16,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 tile_mask;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_4_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_4_8_R180(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0xC0: Draw8x8_Mapped_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);        break;
         case 0x80: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);  break;
         case 0x40: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map);  break;
         case 0x00: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[(ReadWord(&RAM_BG[2+zz])&tile_mask)<<6],x,y,map); break;
         }

      END_SCROLL_512x512_4_8();
}


void render_bg0_transparent_r180_mapped(TC0100SCN_LAYER *tc_layer)
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

   RAM_BG  = tc_layer->RAM;
   RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   RAM_MSK = tc_layer->MASK;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   tile_mask = tc_layer->tile_mask;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_4_8(
         scr_x-(ReadWord(RAM_SCR+0)),
         scr_y-(ReadWord(RAM_SCR+6))
      );

      START_SCROLL_512x512_4_8_R180(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=ReadWord(&RAM_BG[2+zz])&tile_mask;
      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz],
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[1+zz]&0xC0){
               case 0xC0: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x80: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x40: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x00: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[1+zz]&0xC0){
               case 0xC0: Draw8x8_Mapped_Rot(&RAM_GFX[ta<<6],x,y,map);        break;
               case 0x80: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x40: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[ta<<6],x,y,map);  break;
               case 0x00: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[ta<<6],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_4_8();
}


void render_fg0_solid_r180_mapped(TC0100SCN_LAYER *tc_layer)
{
   int x,y,zzzz,zzz,zz;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   // RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=48){
      for(x=(bmp_w+bmp_x-8);(UINT32)x>=bmp_x;x-=8,zz+=2){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0xC0: Draw8x8_Mapped_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);        break;
         case 0x80: Draw8x8_Mapped_FlipY_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);  break;
         case 0x40: Draw8x8_Mapped_FlipX_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map);  break;
         case 0x00: Draw8x8_Mapped_FlipXY_Rot(&RAM_GFX[RAM_BG[zz]<<6],x,y,map); break;
         }
      }
      }
}


void render_fg0_transparent_r180_mapped(TC0100SCN_LAYER *tc_layer)
{
   int x,y,zzzz,zzz,zz,z;
   UINT8 *map;

   UINT8 *RAM_BG;
   // UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y;

   RAM_BG  = tc_layer->RAM;
   // RAM_SCR = tc_layer->SCR;
   RAM_GFX = tc_layer->GFX;
   bmp_x = tc_layer->bmp_x;
   bmp_y = tc_layer->bmp_y;
   bmp_w = tc_layer->bmp_w;
   bmp_h = tc_layer->bmp_h;
   scr_x = tc_layer->scr_x;
   scr_y = tc_layer->scr_y;

      MAKE_SCROLL_512x512_2_8_no16(
         scr_x,		//-(ReadWord(RAM_SCR+0)),
         scr_y		//-(ReadWord(RAM_SCR+6))
      );

      zz=zzzz;
      for(y=(bmp_h+bmp_y-8);(UINT32)y>=bmp_y;y-=8,zz+=48){
      for(x=(bmp_w+bmp_x-8);(UINT32)x>=bmp_x;x-=8,zz+=2){
         if((z=RAM_BG[zz])!=0){

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[1+zz]&0x3F,
            4,				// 4 Colours
            map
         );

         switch(RAM_BG[1+zz]&0xC0){
         case 0xC0: Draw8x8_Trans_Mapped_Rot(&RAM_GFX[z<<6],x,y,map);        break;
         case 0x80: Draw8x8_Trans_Mapped_FlipY_Rot(&RAM_GFX[z<<6],x,y,map);  break;
         case 0x40: Draw8x8_Trans_Mapped_FlipX_Rot(&RAM_GFX[z<<6],x,y,map);  break;
         case 0x00: Draw8x8_Trans_Mapped_FlipXY_Rot(&RAM_GFX[z<<6],x,y,map); break;
         }

         }
      }
      }
}

/******************************************************************************/
