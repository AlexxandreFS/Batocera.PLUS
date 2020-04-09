/******************************************************************************/
/*                                                                            */
/*           tc0006vcu: TAITO VIDEO CHIP UNIT (F2/F3-SYSTEM HYBRID)           */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc006vcu.h"
#include "savegame.h"
#include "zoom/16x16.h"		// 16x16 zoomed sprite routines

/*

In fact, this chip is actually the TC0480SCP (from mame). Here is the info they have:

Tilemap generator, has four zoomable tilemaps with 16x16 tiles.
It also has a front tilemap with 8x8 tiles which fetches gfx data
from RAM.

BG2 and 3 are "special" layers which have row zoom and source
columnscroll. The selectable layer priority order is a function
of the need to have the "special" layers in particular priority
positions.

Standard memory layout (four 32x32 bg tilemaps, one 64x64 fg tilemap)

0000-0fff BG0
1000-1fff BG1
2000-2fff BG2
3000-3fff BG3
4000-43ff BG0 rowscroll
4400-47ff BG1 rowscroll
4800-4bff BG2 rowscroll
4c00-4fff BG3 rowscroll
5000-53ff BG0 rowscroll low order bytes (see info below)
5400-57ff BG1 rowscroll low order bytes
5800-5bff BG2 rowscroll low order bytes
5c00-5fff BG3 rowscroll low order bytes
6000-63ff BG2 row zoom
6400-67ff BG3 row zoom
6800-6bff BG2 source colscroll
6c00-6fff BG3 source colscroll
7000-bfff unknown/unused?
c000-dfff FG0
e000-ffff gfx data for FG0 (4bpp)

Double width tilemaps memory layout (four 64x32 bg tilemaps, one 64x64 fg tilemap)

0000-1fff BG0
2000-3fff BG1
4000-5fff BG2
6000-7fff BG3
8000-83ff BG0 rowscroll
8400-87ff BG1 rowscroll
8800-8bff BG2 rowscroll
8c00-8fff BG3 rowscroll
9000-93ff BG0 rowscroll low order bytes (used for accuracy with row zoom or layer zoom)
9400-97ff BG1 rowscroll low order bytes [*]
9800-9bff BG2 rowscroll low order bytes
9c00-9fff BG3 rowscroll low order bytes
a000-a3ff BG2 row zoom [+]
a400-a7ff BG3 row zoom
a800-abff BG2 source colscroll
ac00-afff BG3 source colscroll
b000-bfff unknown (Slapshot and Superchs poke in TBA OVER error message in FG0 format)
c000-dfff FG0
e000-ffff gfx data for FG0 (4bpp)

[* Gunbustr suggests that high bytes are irrelevant: it leaves them
all zeroed. Superchs is the only game which uses high bytes that
aren't the low byte of the main rowscroll (Footchmp/Undrfire have
this verified in the code).]

[+ Usual row zoom values are 0 - 0x7f. Gunbustr also uses 0x80-d0
approx. Undrfire keeps to the 0-0x7f range but oddly also uses
the high byte with a mask of 0x3f. Meaning of this high byte is
unknown.]

Bg layers tile word layout

+0x00   %yx..bbbb cccccccc      b=control bits(?) c=color .=unused(?)
+0x02   tilenum
[y=yflip x=xflip b=unknown seen in Metalb]

Control registers

000-001 BG0 x scroll    (layer priority order is definable)
002-003 BG1 x scroll
004-005 BG2 x scroll
006-007 BG3 x scroll
008-009 BG0 y scroll
00a-00b BG1 y scroll
00c-00d BG2 y scroll
00e-00f BG3 y scroll
010-011 BG0 zoom        (high byte = X zoom, low byte = Y zoom,
012-013 BG1 zoom         compression is allowed on Y axis only)
014-015 BG2 zoom
016-017 BG3 zoom
018-019 Text layer x scroll
01a-01b Text layer y scroll
01c-01d Unused (not written)
01e-01f Layer Control register
		x-------	Double width tilemaps (4 bg tilemaps become 64x32, and the
		            memory layout changes). Slapshot changes this on the fly.
		-x------	Flip screen
		--x-----	unknown

				Set in Metalb init by whether a byte in prg ROM $7fffe is zero.
				Subsequently Metalb changes it for some screen layer layouts.
				Footchmp clears it, Hthero sets it [then both leave it alone].
				Deadconx code at $10e2 is interesting, with possible values of:
				0x0, 0x20, 0x40, 0x60 poked in (via ram buffer) to control reg,
				dependent on byte in prg ROM $7fffd and whether screen is flipped.

		---xxx--	BG layer priority order

		...000..	0  1  2  3
		...001..	1  2  3  0  (no evidence of this)
		...010..	2  3  0  1  (no evidence of this)
		...011..	3  0  1  2
		...100..	3  2  1  0
		...101..	2  1  0  3  [Gunbustr attract and Metalb (c) screen]
		...110..	1  0  3  2  (no evidence of this)
		...111..	0  3  2  1

		------x-	BG3 row zoom enable
		-------x	BG2 row zoom enable

020-021 BG0 dx	(provides extra precision to x-scroll, only changed with xscroll)
022-023 BG1 dx
024-025 BG2 dx
026-027 BG3 dx
028-029 BG0 dy	(provides extra precision to y-scroll, only changed with yscroll)
02a-02b BG1 dy
02c-02d BG2 dy
02e-02f BG3 dy

[see code at $1b4a in Slapshot and $xxxxx in Undrfire for evidence of row areas]

Previous Antiriad notes (very short) :

Dead Connection
Football Champ / Euro Champ 92
Metal Black
Operation Wolf 3

tc0006vcu main
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

tc0006vcu scroll
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
 1E  |00000000| Unused?
 1F  |...xxxxx| Priorities?
 1F  |..x.....| ?
 1F  |.x......| Screen flip
 1F  |x.......| 1024x512 bg size
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

0x80 00000 = 0123   [Operation Wolf 3]
0x00 00000 = 0123   [Dead Connection]
0x00 00000 = 0123   [Football Champ]
0x20 00000 = 0123   [Metal Black]
0x23 00011 = 0    ? [Metal Black]
0x2C 01100 = 0312 ? [Metal Black]
0x2F 01111 = 3012   [Metal Black]
0x30 10000 = 3012   [Metal Black]
0x32 10010 =      ? [Metal Black]
0x33 10011 = 3210   [Metal Black]
0x34 10100 = 23   ? [Metal Black]
0x37 10111 = 23   ? [Metal Black]
0x3C 11100 = 0    ? [Metal Black]
0x3E 11110 = 0321   [Metal Black]
0x3F 11111 = 0321 ? [Metal Black]

*/

#define GFX_FG0_COUNT	0x100

static UINT8 *RAM_FG;
static UINT8 *GFX_FG;

static UINT32 gfx_fg0_dirty_count;
static UINT32 GFX_FG0_DIRTY[GFX_FG0_COUNT];
static UINT8 GFX_FG0_SOLID[GFX_FG0_COUNT];

static int layer_id_data[5];

static char *layer_id_name[5] =
{
   "BG0",   "BG1",   "BG2",   "BG3",    "FG0",
};

void tc0006vcu_load_update(void);

static UINT8 *z_step;

/*

0x7F = Normal Size
0xBF = 2x Size?
0xFF = 3x Size??

*/

static UINT8 *make_16x16_zoom_ofs_type3b(void)
{
   UINT8 *zoom16_ofs;
   int ta,tb,tc,td;

   zoom16_ofs = AllocateMem(128*32);

   for(ta=0;ta<128;ta++){
      td=0;
      for(tb=0;tb<32;tb++){
         tc = ((((tb+1)*16)*(ta+1))/64) - (((tb*16)*(ta+1))/64) + 16;
         zoom16_ofs[((ta)*32)+(31-tb)] = tc;
         #ifdef DEBUG_TABLES
         print_debug("%02x ",tc);
         #endif
         td += tc;
      }
      #ifdef DEBUG_TABLES
      print_debug("[%02x]\n",td);
      #endif
   }

   return zoom16_ofs;
}

void init_tc0006vcu(void)
{
   GFX_FG = tc0006vcu.GFX_FG;
   RAM_FG = tc0006vcu.RAM + 0xE000;

   tc0006vcu.GFX_FG_MASK = GFX_FG0_SOLID;

   gfx_fg0_dirty_count = 0;
   memset(GFX_FG0_DIRTY, 0x00, GFX_FG0_COUNT*4);
   memset(GFX_FG0_SOLID, 0x00, GFX_FG0_COUNT);

   layer_id_data[0] = add_layer_info(layer_id_name[0]);
   layer_id_data[1] = add_layer_info(layer_id_name[1]);
   layer_id_data[2] = add_layer_info(layer_id_name[2]);
   layer_id_data[3] = add_layer_info(layer_id_name[3]);
   layer_id_data[4] = add_layer_info(layer_id_name[4]);

   if(GFX_FG){
      memset(GFX_FG,0x00, 0x4000);
      memset(RAM_FG,0x00, 0x2000);
   }

   init_16x16_zoom_64();
   z_step = make_16x16_zoom_ofs_type3b();

   AddLoadCallback(tc0006vcu_load_update);
}

void debug_tc0006vcu(void)
{
   #if 0

   UINT8 *src;

   src = tc0006vcu.RAM_SCR;

   clear_ingame_message_list();

   print_ingame(60,"BG0: (%04x,%04x) Z: (%04x,%04x) ?: %04x",ReadWord(&src[0x00]),ReadWord(&src[0x08]),ReadWord(&src[0x20]),ReadWord(&src[0x28]),ReadWord(&src[0x10]));
   print_ingame(60,"BG1: (%04x,%04x) Z: (%04x,%04x) ?: %04x",ReadWord(&src[0x02]),ReadWord(&src[0x08]),ReadWord(&src[0x22]),ReadWord(&src[0x2A]),ReadWord(&src[0x12]));
   print_ingame(60,"BG2: (%04x,%04x) Z: (%04x,%04x) ?: %04x",ReadWord(&src[0x04]),ReadWord(&src[0x08]),ReadWord(&src[0x24]),ReadWord(&src[0x2C]),ReadWord(&src[0x14]));
   print_ingame(60,"BG3: (%04x,%04x) Z: (%04x,%04x) ?: %04x",ReadWord(&src[0x06]),ReadWord(&src[0x08]),ReadWord(&src[0x26]),ReadWord(&src[0x2E]),ReadWord(&src[0x16]));
   print_ingame(60,"FG0: (%04x,%04x) 0: %04x     Ctrl: %04x",ReadWord(&src[0x18]),ReadWord(&src[0x1A]),ReadWord(&src[0x1C]),ReadWord(&src[0x1E]));

   #endif
}

/******************************************************************************/

#undef  RAM_PTR
#undef  GFX_PTR
#define RAM_PTR		RAM_FG
#define GFX_PTR		GFX_FG

void tc0006vcu_load_update(void)
{
   UINT32 i,j;

   gfx_fg0_dirty_count = 0;

   for(i = 0; i < 0x2000; i += 2){
      j = ReadWord(&RAM_PTR[i]);
      WriteWord(&RAM_PTR[i], ~j);
      tc0006vcu_gfx_fg0_ww(i, j);
   }
}

void tc0006vcu_update_gfx_fg0(void)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *source;

   for(ta = 0; ta < gfx_fg0_dirty_count; ta++){

      tb = GFX_FG0_DIRTY[ta];
      source = GFX_PTR + (tb << 6);

      td=0;
      te=0;
      for(tc=0;tc<0x40;tc++){
         if(source[tc])
            td=1;
         else
            te=1;
      }
      if((td==0)&&(te==1)) GFX_FG0_SOLID[tb]=0;	// All pixels are 0: Don't Draw
      if((td==1)&&(te==1)) GFX_FG0_SOLID[tb]=1;	// Mixed: Draw Trans
      if((td==1)&&(te==0)) GFX_FG0_SOLID[tb]=2;	// All pixels are !0: Draw Solid

   }

   gfx_fg0_dirty_count = 0;
}

void tc0006vcu_gfx_fg0_wb(UINT32 addr, UINT8 data)
{
   addr ^= 1;
   addr &= 0x1FFF;

   if((RAM_PTR[addr])!=data){

   // Write to RAM

   RAM_PTR[addr]=data;

   // Write to 8x8 GFX

   addr  ^= 1;
   addr <<= 1;

   GFX_PTR[addr+0] = (data >> 0) & 0x0F;
   GFX_PTR[addr+1] = (data >> 4) & 0x0F;

   // request mask update

   addr >>= 6;

   if(GFX_FG0_SOLID[addr] != 3){
      GFX_FG0_SOLID[addr] = 3;
      GFX_FG0_DIRTY[gfx_fg0_dirty_count++] = addr;
   }

   }
}

void tc0006vcu_gfx_fg0_ww(UINT32 addr, UINT16 data)
{
   addr &= 0x1FFE;

   if(ReadWord(&RAM_PTR[addr])!=data){

   // Write to RAM

   WriteWord(&RAM_PTR[addr],data);

   // Write to 8x8 GFX

   addr <<= 1;

   GFX_PTR[addr+0] = (data >>  0) & 0x0F;
   GFX_PTR[addr+1] = (data >>  4) & 0x0F;
   GFX_PTR[addr+2] = (data >>  8) & 0x0F;
   GFX_PTR[addr+3] = (data >> 12) & 0x0F;

   // request mask update

   addr >>= 6;

   if(GFX_FG0_SOLID[addr] != 3){
      GFX_FG0_SOLID[addr] = 3;
      GFX_FG0_DIRTY[gfx_fg0_dirty_count++] = addr;
   }

   }
}

/******************************************************************************/

void tc0006vcu_render_layer(int layer)
{
   int zoom,tx,ty,txx,tyy;
   UINT8 *z_data_x,*z_data_y;

   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x, scr_y, pal_ofs, tile_mask;

   if(!check_layer_enabled(layer_id_data[layer]))
       return;

   RAM_BG    = tc0006vcu.RAM     + (layer * 0x1000);
   RAM_SCR   = tc0006vcu.RAM_SCR + (layer * 0x0002);
   RAM_GFX   = tc0006vcu.GFX_BG;
   RAM_MSK   = tc0006vcu.GFX_BG_MASK;
   pal_ofs   = tc0006vcu.pal_ofs;
   tile_mask = tc0006vcu.tile_mask;

   bmp_x = tc0006vcu.bmp_x;
   bmp_y = tc0006vcu.bmp_y;
   bmp_w = tc0006vcu.bmp_w;
   bmp_h = tc0006vcu.bmp_h;
   scr_x = tc0006vcu.scr_x[layer];
   scr_y = tc0006vcu.scr_y[layer];


   if(tc0006vcu_layer_count == 0){

   zoom   = RAM_SCR[0x10];

   if((zoom<=0x7F)){

      MAKE_SCROLL_512x512_4_16(
         scr_x - (ReadWord(&RAM_SCR[0])),
         scr_y + (ReadWord(&RAM_SCR[8]))
      );

      START_SCROLL_512x512_4_16(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );

         ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

         switch(RAM_BG[zz+1]&0xC0){
            case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
            case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
            case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
            case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
         }

      END_SCROLL_512x512_4_16();

   }
   else{

   z_data_x = &z_step[(zoom-0x80)<<5];
   z_data_y = &z_step[(zoom-0x80)<<5];
   tx=0;
   ty=0;

   zzz = scr_x - (ReadWord(&RAM_SCR[0]));

   zzzz=(zzz&0x1F0)>>2;
   x16=zzz&15;

   zzz = scr_y + (ReadWord(&RAM_SCR[8]));

   zzzz|=(zzz&0x1F0)<<3;
   y16=zzz&15;

   x16 = (x16 * z_data_x[tx])/16;
   y16 = (y16 * z_data_y[ty])/16;

   zz=zzzz;
   for(y=(48-y16);y<(224+48);y+=tyy){

   tyy = z_data_y[ty];
   ty  = (ty+1)&3;

   for(x=(48-x16);x<(320+48);x+=txx){

      txx = z_data_x[tx];
      tx  = (tx+1)&3;

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );

         ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;
         switch(RAM_BG[zz+1]&0xC0){
            case 0x00: Draw16x16_64_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);        break;
            case 0x40: Draw16x16_64_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
            case 0x80: Draw16x16_64_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
            case 0xC0: Draw16x16_64_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy); break;
         }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zz = zzzz = (zzzz+0x80)&0xFFF;
   }

   }

   }
   else{

   zoom   = RAM_SCR[0x10];

   if((zoom<=0x7F)){

      MAKE_SCROLL_512x512_4_16(
         scr_x - (ReadWord(&RAM_SCR[0])),
         scr_y + (ReadWord(&RAM_SCR[8]))
      );

      START_SCROLL_512x512_4_16(bmp_x,bmp_y,bmp_w,bmp_h);

      ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }

      }

      END_SCROLL_512x512_4_16();

   }
   else{

   z_data_x = &z_step[(zoom-0x80)<<5];
   z_data_y = &z_step[(zoom-0x80)<<5];
   tx=0;
   ty=0;

   zzz = scr_x - (ReadWord(&RAM_SCR[0]));

   zzzz=(zzz&0x1F0)>>2;
   x16=zzz&15;

   zzz = scr_y + (ReadWord(&RAM_SCR[8]));

   zzzz|=(zzz&0x1F0)<<3;
   y16=zzz&15;

   //x16 = (x16 * z_data_x[tx])/16;
   //y16 = (y16 * z_data_y[ty])/16;

   x16 = (x16 * (zoom-0x40))/0x40;
   y16 = (y16 * (zoom-0x40))/0x40;

   zz=zzzz;
   for(y=(48-y16);y<(224+48);y+=tyy){

   tyy = z_data_y[ty];
   ty  = (ty+1)&3;

   for(x=(48-x16);x<(320+48);x+=txx){

      txx = z_data_x[tx];
      tx  = (tx+1)&3;

      ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );
         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_64_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);        break;
               case 0x40: Draw16x16_64_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0x80: Draw16x16_64_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0xC0: Draw16x16_64_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_64_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);        break;
               case 0x40: Draw16x16_64_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0x80: Draw16x16_64_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0xC0: Draw16x16_64_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy); break;
            }
         }

      }

      zz=(zz&0xF80)|((zz+4)&0x7F);
   }
   zz = zzzz = (zzzz+0x80)&0xFFF;
   }

   }

   }

   tc0006vcu_layer_count ++;
}

void tc0006vcu_render_layer_1024(int layer)
{
   int zoom,tx,ty,txx,tyy;
   UINT8 *z_data_x,*z_data_y;

   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x, scr_y, pal_ofs, tile_mask;

   if(!check_layer_enabled(layer_id_data[layer]))
       return;

   RAM_BG    = tc0006vcu.RAM     + (layer * 0x2000);
   RAM_SCR   = tc0006vcu.RAM_SCR + (layer * 0x0002);
   RAM_GFX   = tc0006vcu.GFX_BG;
   RAM_MSK   = tc0006vcu.GFX_BG_MASK;
   pal_ofs   = tc0006vcu.pal_ofs;
   tile_mask = tc0006vcu.tile_mask;

   bmp_x = tc0006vcu.bmp_x;
   bmp_y = tc0006vcu.bmp_y;
   bmp_w = tc0006vcu.bmp_w;
   bmp_h = tc0006vcu.bmp_h;
   scr_x = tc0006vcu.scr_x[layer];
   scr_y = tc0006vcu.scr_y[layer];


   if(tc0006vcu_layer_count == 0){

   zoom   = RAM_SCR[0x10];

   if((zoom<=0x7F)){

      MAKE_SCROLL_1024x512_4_16(
         scr_x - (ReadWord(&RAM_SCR[0])),
         scr_y + (ReadWord(&RAM_SCR[8]))
      );

      START_SCROLL_1024x512_4_16(bmp_x,bmp_y,bmp_w,bmp_h);

         MAP_PALETTE_MAPPED_NEW(
            (RAM_BG[zz]|pal_ofs),
            16,
            map
         );

         ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

         switch(RAM_BG[zz+1]&0xC0){
            case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
            case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
            case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
            case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
         }

      END_SCROLL_1024x512_4_16();

   }
   else{

   z_data_x = &z_step[(zoom-0x80)<<5];
   z_data_y = &z_step[(zoom-0x80)<<5];
   tx=0;
   ty=0;

   zzz = scr_x - (ReadWord(&RAM_SCR[0]));

   zzzz=(zzz&0x3F0)>>2;
   x16=zzz&15;

   zzz = scr_y + (ReadWord(&RAM_SCR[8]));

   zzzz|=(zzz&0x1F0)<<4;
   y16=zzz&15;

   x16 = (x16 * z_data_x[tx])/16;
   y16 = (y16 * z_data_y[ty])/16;

   zz=zzzz;
   for(y=(48-y16);y<(224+48);y+=tyy){

   tyy = z_data_y[ty];
   ty  = (ty+1)&3;

   for(x=(48-x16);x<(320+48);x+=txx){

      txx = z_data_x[tx];
      tx  = (tx+1)&3;

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );

         ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

         switch(RAM_BG[zz+1]&0xC0){
            case 0x00: Draw16x16_64_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);        break;
            case 0x40: Draw16x16_64_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
            case 0x80: Draw16x16_64_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
            case 0xC0: Draw16x16_64_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy); break;
         }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zz = zzzz = (zzzz+0x100)&0x1FFF;
   }

   }

   }
   else{

   zoom   = RAM_SCR[0x10];

   if((zoom<=0x7F)){

      MAKE_SCROLL_1024x512_4_16(
         scr_x - (ReadWord(&RAM_SCR[0])),
         scr_y + (ReadWord(&RAM_SCR[8]))
      );

      START_SCROLL_1024x512_4_16(bmp_x,bmp_y,bmp_w,bmp_h);

      ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_Trans_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Trans_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Trans_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Trans_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_Mapped_Rot(&RAM_GFX[ta<<8],x,y,map);        break;
               case 0x40: Draw16x16_Mapped_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0x80: Draw16x16_Mapped_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map);  break;
               case 0xC0: Draw16x16_Mapped_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map); break;
            }
         }

      }

      END_SCROLL_1024x512_4_16();

   }
   else{

   z_data_x = &z_step[(zoom-0x80)<<5];
   z_data_y = &z_step[(zoom-0x80)<<5];
   tx=0;
   ty=0;

   zzz = scr_x - (ReadWord(&RAM_SCR[0]));

   zzzz=(zzz&0x3F0)>>2;
   x16=zzz&15;

   zzz = scr_y + (ReadWord(&RAM_SCR[8]));

   zzzz|=(zzz&0x1F0)<<4;
   y16=zzz&15;

   //x16 = (x16 * z_data_x[tx])/16;
   //y16 = (y16 * z_data_y[ty])/16;

   x16 = (x16 * (zoom-0x40))/0x40;
   y16 = (y16 * (zoom-0x40))/0x40;

   zz=zzzz;
   for(y=(48-y16);y<(224+48);y+=tyy){

   tyy = z_data_y[ty];
   ty  = (ty+1)&3;

   for(x=(48-x16);x<(320+48);x+=txx){

      txx = z_data_x[tx];
      tx  = (tx+1)&3;

      ta = ReadWord(&RAM_BG[zz+2]) & tile_mask;

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            RAM_BG[zz]|pal_ofs,
            16,
            map
         );

         if(RAM_MSK[ta]==1){			// Some pixels; trans
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_64_Trans_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);        break;
               case 0x40: Draw16x16_64_Trans_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0x80: Draw16x16_64_Trans_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0xC0: Draw16x16_64_Trans_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy); break;
            }
         }
         else{					// all pixels; solid
            switch(RAM_BG[zz+1]&0xC0){
               case 0x00: Draw16x16_64_Mapped_ZoomXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);        break;
               case 0x40: Draw16x16_64_Mapped_ZoomXY_FlipY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0x80: Draw16x16_64_Mapped_ZoomXY_FlipX_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy);  break;
               case 0xC0: Draw16x16_64_Mapped_ZoomXY_FlipXY_Rot(&RAM_GFX[ta<<8],x,y,map,txx,tyy); break;
            }
         }

      }

      zz=(zz&0x1F00)|((zz+4)&0xFF);
   }
   zz = zzzz = (zzzz+0x100)&0x1FFF;
   }

   }

   }

   tc0006vcu_layer_count ++;
}

void tc0006vcu_render_fg0(void)
{
   int x,y,x16,y16,zzzz,zzz,zz,ta;
   UINT8 *map;

   UINT8 *RAM_BG;
   UINT8 *RAM_SCR;
   UINT8 *RAM_GFX;
   UINT8 *RAM_MSK;
   UINT32 bmp_x,bmp_y,bmp_w,bmp_h;
   UINT32 scr_x,scr_y, pal_ofs;

   if(!check_layer_enabled(layer_id_data[4]))
       return;

   tc0006vcu_update_gfx_fg0();

   RAM_BG    = tc0006vcu.RAM + 0x0C000;
   RAM_SCR   = tc0006vcu.RAM_SCR + 0x00018;
   RAM_GFX   = tc0006vcu.GFX_FG;
   RAM_MSK   = tc0006vcu.GFX_FG_MASK;
   pal_ofs   = tc0006vcu.pal_ofs;

   bmp_x = tc0006vcu.bmp_x;
   bmp_y = tc0006vcu.bmp_y;
   bmp_w = tc0006vcu.bmp_w;
   bmp_h = tc0006vcu.bmp_h;
   scr_x = tc0006vcu.scr_x[4];
   scr_y = tc0006vcu.scr_y[4];

      MAKE_SCROLL_512x512_2_8(
         scr_x - (ReadWord(&RAM_SCR[0])),
         scr_y - (ReadWord(&RAM_SCR[2]))
      );

      START_SCROLL_512x512_2_8(bmp_x,bmp_y,bmp_w,bmp_h);

      ta=RAM_BG[zz];

      if(RAM_MSK[ta]!=0){			// No pixels; skip

         MAP_PALETTE_MAPPED_NEW(
            ((RAM_BG[1+zz]&0x3F)|pal_ofs),
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

      END_SCROLL_512x512_2_8();

   tc0006vcu_layer_count ++;
}
