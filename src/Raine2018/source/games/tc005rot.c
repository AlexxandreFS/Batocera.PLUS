/******************************************************************************/
/*                                                                            */
/*                 tc0005rot: TAITO ROTATION LAYER (F2-SYSTEM)                */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tc005rot.h"
#include "blit.h"

// Supported any color depth
// not supported : rotations 90 and 180

/*

'tc0005rot' is a made up name, until someone can give me the more board info.
Or this layer could be another part of tc0100scn (but I guess it isn't).

Manu: from the mame source, we learn it's a combination of 2 chips... How do they
learn all that ? They probably have access to lots of technical data...
Anyway, here is their description of the chips :

TC0280GRD
TC0430GRW
---------
These generate a zooming/rotating tilemap. The TC0280GRD has to be used in
pairs, while the TC0430GRW is a newer, single-chip solution.
Regardless of the hardware differences, the two are functionally identical
except for incxx and incxy, which need to be multiplied by 2 in the TC0280GRD
to bring them to the same scale of the other parameters (maybe the chip has
half-pixel resolution?).

control registers:
000-003 start x
004-005 incxx
006-007 incyx
008-00b start y
00c-00d incxy
00e-00f incyy

Anyway, the implementation from Antiriad is very efficient, even if it lacks some
comments ! So I am going to try to keep most of it. The goal is to make this compatible
to any color depth and to be sure that games which use this chip really have it.

The way it works in Antiriad implementation :

The chipset has some RAM to create its bitmap to be zoomed/rotated. So an allegro bitmap
is created, and everytime the cpu writes to the RAM of this chipset, the allegro bitmap
is updated accordingly.

I am going to create an 8bpp bitmap, and do the color mapping at the last minute, when
transfering the bitmap to the screen, instead of doing it while the bitmap is created.

The bank is kept with the color number when creating the 8bpp bitmap, so that we
can update correctly the mapping at the end.
We get the bank number when we update the bitmap but no bank base. Since the bank base
can change later, we must keep the bank in the 8bpp bitmap as we do now.

Notice : I should try to find some fast asm functions maybe there are some mmx/3dnow
         functions to help in this kind of stuff. Or at least adapt the old asm code
         from Antiriad, it's clearly faster than the C version.

TC0005ROT RAM
-------------

--------------+---------------
00000 - 01FFF | BG ROT RAM
02000 - 0200F | SCROLL RAM
--------------+---------------

BG ROT RAM
----------

-----+--------+---------------------
Byte | Bit(s) | Info
-----+76543210+---------------------
  0  |xx......| Colour Bank
  0  |..xxxxxx| Tile Number (high)
  1  |xxxxxxxx| Tile Number (low)
-----+--------+---------------------

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

0000.0000.000X.XXXX
XXXX.xxxx.xxxx.xxxx
SXXX.xxxx.xxxx.xxxx
SXXX.xxxx.xxxx.xxxx
0000.0000.000Y.YYYY
YYYY.yyyy.yyyy.yyyy
SYYY.yyyy.yyyy.yyyy
SYYY.yyyy.yyyy.yyyy

Not implemented:

- Various things.
- Priority with sprites.

Normal Games:

- Camel Try      - OK

R180 Games:

- Don Doko Don   - OK

R270 Games:

- Drift Out      - OK

*/

struct TC0005ROT tc0005rot;
static UINT8 *RAM_BG;
static UINT8 *RAM_SCR;
static UINT8 *GFX_BG;

UINT8 rot_pens;
// static UINT8 rot_map[64];

static BITMAP *pixel_bitmap;

typedef void tc005rot_drawing_func(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp);

static BITMAP *bitmap_store;

void tc0005rot_set_bitmap(void)
{
   bitmap_store = GameBitmap;
   GameBitmap = pixel_bitmap;
   init_spr8x8asm_8();
}

void tc0005rot_unset_bitmap(void)
{
   GameBitmap = bitmap_store;
   init_spr8x8asm_8();
}

extern int disp_x_8, disp_y_8;

void tc0005rot_bg0_ww(UINT32 address, UINT16 data)
{
   if(ReadWord(&RAM_BG[address&0x1FFF])!=data){

     // Update RAM
     // ----------

     WriteWord(&RAM_BG[address&0x1FFF],data);

     // Update BG0 Buffer
     // -----------------

     if(RefreshBuffers==0){
       // update the bitmap of the chipset (not the screen)
       // we keep the bank with the pixel data (it's the role of Draw8x8)
/*        int oldx = disp_x_8, oldy = disp_y_8; */
/*        disp_x_8 = 512 - 8; disp_y_8 = 512 - 8; */
       Draw8x8_8(&GFX_BG[(data&0x3FFF)<<6],(address&0x7E)<<2,((address&0x1F80)>>4),(data>>10)&0x30);
/*        disp_x_8 = oldx; disp_y_8 = oldy; */

     }
   }
}

// static UINT32 tmp_f1x,tmp_f1y,tmp_f1xd,tmp_f1yd,tmp_f2xd,tmp_f2yd;
// static UINT32 tmp_src,tmp_bit;

static void RotateF2SystemBG0_8(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp)
{
  //#if !defined(RAINE_DOS) && !defined(RAINE_UNIX)
  long f2x,f2y;
  int dx,dy;
  UINT8 ta;
  //#endif
  UINT8 *BIT;
  UINT8 *SRC;

   // Init Stuff
   // ----------

   f1x+=(16*f2xd);
   f1y+=(16*f2yd);

   f1x+=(16*f1xd);
   f1y+=(16*f1yd);

   BIT=GameViewBitmap->line[0];
   SRC=pixel_bitmap->line[0];

   // Draw the rotated data
   // ---------------------

#if 1
   // !defined(RAINE_DOS) && !defined(RAINE_UNIX)

   dy=224;
   do{
      dx=320;
      f2x=f1x;
      f2y=f1y;
      do{
         ta=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         if ((ta & 0xf) || !transp) {
	   *BIT=map[ta]; // transp
	 }
         f2x+=f2xd;
         f2y+=f2yd;
         BIT++;
      }while(--dx);
      BIT+=(64);
      f1x+=f1xd;
      f1y+=f1yd;
   }while(--dy);

#else

   tmp_f1x=f1x;
   tmp_f1y=f1y;
   tmp_f1xd=f1xd;
   tmp_f1yd=f1yd;
   tmp_f2xd=f2xd;
   tmp_f2yd=f2yd;
   tmp_src=(UINT32) &SRC[0];
   tmp_bit=(UINT32) &BIT[0];

   if(((tmp_f1yd>>5)==0x0800)&&((tmp_f1xd>>4)==0x0000)&&((tmp_f2yd>>5)==0x0000)&&((tmp_f2xd>>4)==0x1000)){

     tmp_f1x=(tmp_f1x>>16)&0x1FF;
     tmp_f1y=((tmp_f1y>>16)&0x1FF)<<9;


   if((tmp_f1x&3)==0){

     /* Big thanks to Emacs for the stings conversions (all the "...\n").
	Emacs is very big, but its macros can be VERY usefull at times !!! */

#ifdef RAINE_DOS
     asm(
"	pushl	%%ebp\n"
"	movl	_tmp_f1x,%%eax\n"
"	movl	_tmp_src,%%ebx\n"
"	movl	%%eax,SMC4-4\n"
"	movl	%%ebx,SMC5-4\n"

"	movl	_tmp_f1y,%%ebx\n"
"	movl	_tmp_bit,%%edi\n"
"	movb	$255,%%ch\n"

"	movl	$224,%%edx\n"
"1:\n"
"	movl	$320/4,%%ebp\n"
"	movl	$0x2164334A,%%eax\n"
"SMC4:\n"
"	movl	%%ebx,%%esi\n"
"	addl	$0x2164334A,%%esi\n"
"SMC5:\n"
"2:\n"
"	movl	(%%esi,%%eax),%%ecx\n"
"	testl	%%ecx,%%ecx		\n// Skip Blank Lines\n"
"	jz	5f\n"

"        testb	$0x80,%%cl\n"
"	jnz	8f\n"
"	movb	%%cl,(%%edi)\n"
"8:\n"
"        testb	$0x80,%%ch\n"
"	jnz	8f\n"
"	movb	%%ch,1(%%edi)\n"
"8:\n"
"	roll	$16,%%ecx\n"

"        testb	$0x80,%%cl\n"
"	jnz	8f\n"
"	movb	%%cl,2(%%edi)\n"
"8:\n"
"        testb	$0x80,%%ch\n"
"	jnz	8f\n"
"	movb	%%ch,3(%%edi)\n"
"8:\n"
"5:\n"
"	addl	$4,%%eax\n"
"	addl	$4,%%edi\n"
"	andl	$0x001FF,%%eax\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	addl	$0x00200,%%ebx\n"
"	addl	$(64),%%edi\n"
"	andl	$0x3FE00,%%ebx\n"

"	decl	%%edx\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi" , "%ebp"
   );
#else // RAINE_UNIX
     asm(
"	pushl	%%ebp\n"
"	movl	tmp_f1y,%%ebx\n"
"	movl	tmp_bit,%%edi\n"
"	movb	$255,%%ch\n"

"	movl	$224,%%edx\n"
"1:\n"
"	movl	$320/4,%%ebp\n"
"        movl    (tmp_f1x),%%eax\n"
"	movl	%%ebx,%%esi\n"
"        addl    tmp_src,%%esi\n"
"2:\n"
"	movl	(%%esi,%%eax),%%ecx\n"
"	testl	%%ecx,%%ecx		\n// Skip Blank Lines\n"
"	jz	5f\n"

"        testb	$0x80,%%cl\n"
"	jnz	8f\n"
"	movb	%%cl,(%%edi)\n"
"8:\n"
"        testb	$0x80,%%ch\n"
"	jnz	8f\n"
"	movb	%%ch,1(%%edi)\n"
"8:\n"
"	roll	$16,%%ecx\n"

"        testb	$0x80,%%cl\n"
"	jnz	8f\n"
"	movb	%%cl,2(%%edi)\n"
"8:\n"
"        testb	$0x80,%%ch\n"
"	jnz	8f\n"
"	movb	%%ch,3(%%edi)\n"
"8:\n"
"5:\n"
"	addl	$4,%%eax\n"
"	addl	$4,%%edi\n"
"	andl	$0x001FF,%%eax\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	addl	$0x00200,%%ebx\n"
"	addl	$(64),%%edi\n"
"	andl	$0x3FE00,%%ebx\n"

"	decl	%%edx\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi" , "%ebp"
   );
#endif
     return;
   }
   else{

#ifdef RAINE_DOS
   asm(
"	pushl	%%ebp\n"
"	movl	_tmp_f1x,%%eax\n"
"	movl	_tmp_src,%%ebx\n"
"	movl	%%eax,SMC1-4\n"
"	movl	%%ebx,SMC2-4\n"

"	movl	_tmp_f1y,%%ebx\n"
"	movl	_tmp_bit,%%edi\n"
"					// Mask colour is 255 (skip them)\n"
"	movb	$255,%%ch\n"
"					// Screen is 224 high\n"
"	movl	$224,%%edx\n"
"1:\n"
"	movl	$320,%%ebp		\n// Screen is 320 wide\n"
"	movl	$0x2164334A,%%eax\n"
"SMC1:\n"
"	movl	%%ebx,%%esi\n"
"	addl	$0x2164334A,%%esi\n"
"SMC2:\n"
"2:\n"
"	movb	(%%esi,%%eax,1),%%cl\n"
"	incl	%%eax\n"
"        cmpb	%%ch,%%cl\n"
"	jz	8f\n"
"	movb	%%cl,(%%edi)\n"
"8:\n"
"	incl	%%edi\n"
"	andl	$0x001FF,%%eax\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	addl	$0x00200,%%ebx\n"
"	addl	$(64),%%edi\n"
"	andl	$0x3FE00,%%ebx\n"

"	decl	%%edx\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi" , "%ebp"
   );
#else // RAINE_UNIX
   asm(
"	pushl	%%ebp\n"
"	movl	tmp_f1y,%%ebx\n"
"	movl	tmp_bit,%%edi\n"
"					// Mask colour is 255 (skip them)\n"
"	movb	$255,%%ch\n"
"					// Screen is 224 high\n"
"	movl	$224,%%edx\n"
"1:\n"
"	movl	$320,%%ebp		\n// Screen is 320 wide\n"
"	movl	(tmp_f1x),%%eax\n"
"	movl	%%ebx,%%esi\n"
"	addl	tmp_src,%%esi\n"
"2:\n"
"	movb	(%%esi,%%eax,1),%%cl\n"
"	incl	%%eax\n"
"        cmpb	%%ch,%%cl\n"
"	jz	8f\n"
"	movb	%%cl,(%%edi)\n"
"8:\n"
"	incl	%%edi\n"
"	andl	$0x001FF,%%eax\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	addl	$0x00200,%%ebx\n"
"	addl	$(64),%%edi\n"
"	andl	$0x3FE00,%%ebx\n"

"	decl	%%edx\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi" , "%ebp"
   );
#endif
   return;
   }

   }
   else{

#ifdef RAINE_DOS
     asm(
"	pushl	%%ebp\n"
"	movl	_tmp_f2xd,%%eax		\n// Poke in the data for the main loops\n"
"	movl	_tmp_f2yd,%%ebx		\n// <self modifying code>\n"
"	movl	%%eax,Hack1+1\n"
"	movl	%%ebx,Hack2+2\n"
"	movl	_tmp_f1xd,%%eax\n"
"	movl	_tmp_f1yd,%%ebx\n"
"	movl	%%eax,Hack3+1\n"
"	movl	%%ebx,Hack4+2\n"

"	movl	_tmp_src,%%eax		\n// source buffer (512 x 512 x 1byte/pixel)\n"
"	movl	%%eax,Hack5+2\n"

"	movl	$224,%%ebp		\n// dest size y\n"
"	movl	_tmp_f1x,%%eax\n"
"	movl	_tmp_f1y,%%ebx\n"
"	movl	_tmp_bit,%%edi		\n// destination buffer\n"
"1:\n"
"	pushl	%%ebp\n"
"	pushl	%%eax\n"
"	pushl	%%ebx\n"

"	movl	$320,%%ebp		\n// dest size x\n"
"	movl	%%eax,%%ecx\n"
"	movl	%%ebx,%%edx\n"
"2:\n"
"	shrl	$16,%%ecx\n"
"	shrl	$7,%%edx\n"
"	andl	$0x001FF,%%ecx		\n// wrap around source x\n"
"	andl	$0x3FE00,%%edx		\n// wrap around source y\n"

"Hack1:	addl	$0x2164334A,%%eax\n"
"	orl	%%edx,%%ecx\n"

"Hack2:	addl	$0x2164334A,%%ebx\n"
"Hack5:	movb	0x2164334A(%%ecx),%%dl\n"

"	movl	%%eax,%%ecx\n"

"        testb	$0x80,%%dl		\n// bit 7 used for transparent mask\n"
"	jnz	8f\n"
"	movb	%%dl,(%%edi)\n"
"8:\n"
"	movl	%%ebx,%%edx\n"

"	incl	%%edi\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	popl	%%ebx\n"
"	popl	%%eax\n"
"	popl	%%ebp\n"

"	addl	$(64),%%edi\n"
"Hack3:\n"
"	addl	$0x2164334A,%%eax\n"
"Hack4:\n"
"	addl	$0x2164334A,%%ebx\n"

"	decl	%%ebp\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%ebp"
   );
#else
     asm(
"	pushl	%%ebp\n"
"	movl	$224,%%ebp		\n// dest size y\n"
"	movl	tmp_f1x,%%eax\n"
"	movl	tmp_f1y,%%ebx\n"
"	movl	tmp_bit,%%edi		\n// destination buffer\n"
"        movl    tmp_src,%%esi\n"
"1:\n"
"	pushl	%%ebp\n"
"	pushl	%%eax\n"
"	pushl	%%ebx\n"

"	movl	$320,%%ebp		\n// dest size x\n"
"	movl	%%eax,%%ecx\n"
"	movl	%%ebx,%%edx\n"
"2:\n"
"	shrl	$16,%%ecx\n"
"	shrl	$7,%%edx\n"
"	andl	$0x001FF,%%ecx		\n// wrap around source x\n"
"	andl	$0x3FE00,%%edx		\n// wrap around source y\n"

"	addl	(tmp_f2xd),%%eax\n"
"	orl	%%edx,%%ecx\n"

"	addl	(tmp_f2yd),%%ebx\n"
"	movb	(%%esi,%%ecx),%%dl\n"

"	movl	%%eax,%%ecx\n"

"        testb	$0x80,%%dl		\n// bit 7 used for transparent mask\n"
"	jnz	8f\n"
"	movb	%%dl,(%%edi)\n"
"8:\n"
"	movl	%%ebx,%%edx\n"

"	incl	%%edi\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	popl	%%ebx\n"
"	popl	%%eax\n"
"	popl	%%ebp\n"

"	addl	$(64),%%edi\n"
"	addl	(tmp_f1xd),%%eax\n"
"	addl	(tmp_f1yd),%%ebx\n"

"	decl	%%ebp\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%ebp"
   );
#endif
   }

#endif
}

static void RotateF2SystemBG0_16(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp)
{
  //#if !defined(RAINE_DOS) && !defined(RAINE_UNIX)
  long f2x,f2y;
  int dx,dy;
  UINT8 ta;
  //#endif
  UINT16 *BIT;
  UINT8 *SRC;

   // Init Stuff
   // ----------

   f1x+=(16*f2xd);
   f1y+=(16*f2yd);

   f1x+=(16*f1xd);
   f1y+=(16*f1yd);

   BIT=(UINT16*)GameViewBitmap->line[0];
   SRC=pixel_bitmap->line[0];

   // Draw the rotated data
   // ---------------------

   // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   dy=224;
   do{
      dx=320;
      f2x=f1x;
      f2y=f1y;
      do{
         ta=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         if ((ta & 0xf) || !transp) {
	   *BIT=ReadWord(&map[ta*2]); // transp
	 }
         f2x+=f2xd;
         f2y+=f2yd;
         BIT++;
      }while(--dx);
      BIT+=(64);
      f1x+=f1xd;
      f1y+=f1yd;
   }while(--dy);
}

static void RotateF2SystemBG0_32(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp)
{
  //#if !defined(RAINE_DOS) && !defined(RAINE_UNIX)
  long f2x,f2y;
  int dx,dy;
  UINT8 ta;
  //#endif
  UINT32 *BIT;
  UINT8 *SRC;

   // Init Stuff
   // ----------

   f1x+=(16*f2xd);
   f1y+=(16*f2yd);

   f1x+=(16*f1xd);
   f1y+=(16*f1yd);

   BIT=(UINT32*)GameViewBitmap->line[0];
   SRC=pixel_bitmap->line[0];

   // Draw the rotated data
   // ---------------------

   // !defined(RAINE_DOS) && !defined(RAINE_UNIX)

   dy=224;
   do{
      dx=320;
      f2x=f1x;
      f2y=f1y;
      do{
         ta=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         if ((ta & 0xf) || !transp) *BIT=ReadLong(&map[ta*4]); // transp
         f2x+=f2xd;
         f2y+=f2yd;
         BIT++;
      }while(--dx);
      BIT+=(64);
      f1x+=f1xd;
      f1y+=f1yd;
   }while(--dy);
}

static void RotateF2SystemBG0_r270_8(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp)
{
#if 1 // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   long f2x,f2y;
   int dx,dy;
#endif
   UINT8 *BIT,ta;
   UINT8 *SRC;

   // Init Stuff
   // ----------

   f1x+=(319*f2xd);
   f1y+=(319*f2yd);

   BIT=GameViewBitmap->line[0];
   SRC=pixel_bitmap->line[0];

   // Draw the rotated data
   // ---------------------
#if 1
   // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   for(dy=0;dy<320;dy++){
      f2x=f1x;
      f2y=f1y;
      for(dx=0;dx<224;dx++){
         ta=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         if ((ta & 0xf) || !transp) {
	   *BIT=map[ta]; // transp
	 }
         // BIT[0]=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         f2x+=f1xd;
         f2y+=f1yd;
         BIT++;
      }
      BIT+=(64);
      f1x-=f2xd;
      f1y-=f2yd;
   }
#else
   tmp_src=(UINT32) &SRC[0];
   tmp_bit=(UINT32) &BIT[0];
   tmp_f1xd=f1xd;
   tmp_f1yd=f1yd;
   tmp_f2xd=f2xd;
   tmp_f2yd=f2yd;
   tmp_f1x=f1x;
   tmp_f1y=f1y;

#ifdef RAINE_DOS
   asm(
"	pushl	%%ebp\n"
"	movl	_tmp_f1xd,%%eax		\n// Poke in the data for the main loops\n"
"	movl	_tmp_f1yd,%%ebx		\n// <self modifying code>\n"
"	movl	%%eax,Hck1+1\n"
"	movl	%%ebx,Hck2+2\n"

"	movl	_tmp_f2xd,%%eax\n"
"	movl	_tmp_f2yd,%%ebx\n"
"	movl	%%eax,Hck3+1\n"
"	movl	%%ebx,Hck4+2\n"

"	movl	_tmp_src,%%eax\n"
"	movl	%%eax,Hck5+2\n"

"	movl	$320,%%ebp\n"
"	movl	_tmp_f1x,%%eax\n"
"	movl	_tmp_f1y,%%ebx\n"
"	movl	_tmp_bit,%%edi\n"
"1:\n"
"	pushl	%%ebp\n"
"	pushl	%%eax\n"
"	pushl	%%ebx\n"

"	movl	$224,%%ebp\n"
"2:\n"
"	movl	%%eax,%%ecx\n"
"	movl	%%ebx,%%edx\n"
"	shrl	$16,%%ecx\n"
"	shrl	$7,%%edx\n"
"	andl	$0x001FF,%%ecx\n"
"	andl	$0x3FE00,%%edx\n"
"	orl	%%ecx,%%edx\n"
"Hck5:	movb	0x2164334A(%%edx),%%cl\n"

"Hck1:	addl	$0x2164334A,%%eax\n"
"	movb	%%cl,(%%edi)\n"
"Hck2:	addl	$0x2164334A,%%ebx\n"
"	incl	%%edi\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	popl	%%ebx\n"
"	popl	%%eax\n"
"	popl	%%ebp\n"

"	addl	$(64),%%edi\n"
"Hck3:\n"
"	subl	$0x2164334A,%%eax\n"
"Hck4:\n"
"	subl	$0x2164334A,%%ebx\n"

"	decl	%%ebp\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%ebp"
   );
#else // RAINE_UNIX
   asm(
"	pushl	%%ebp\n"
"	movl	$320,%%ebp\n"
"	movl	tmp_f1x,%%eax\n"
"	movl	tmp_f1y,%%ebx\n"
"	movl	tmp_bit,%%edi\n"
"        movl    tmp_src,%%esi\n"
"1:\n"
"	pushl	%%ebp\n"
"	pushl	%%eax\n"
"	pushl	%%ebx\n"

"	movl	$224,%%ebp\n"
"2:\n"
"	movl	%%eax,%%ecx\n"
"	movl	%%ebx,%%edx\n"
"	shrl	$16,%%ecx\n"
"	shrl	$7,%%edx\n"
"	andl	$0x001FF,%%ecx\n"
"	andl	$0x3FE00,%%edx\n"
"	orl	%%ecx,%%edx\n"
"	movb	(%%esi,%%edx),%%cl\n"
"	addl	(tmp_f1xd),%%eax\n"
"	movb	%%cl,(%%edi)\n"
"	addl	(tmp_f1yd),%%ebx\n"
"	incl	%%edi\n"

"	decl	%%ebp\n"
"	jnz	2b\n"

"	popl	%%ebx\n"
"	popl	%%eax\n"
"	popl	%%ebp\n"

"	addl	$(64),%%edi\n"
"	subl	(tmp_f2xd),%%eax\n"
"	subl	(tmp_f2yd),%%ebx\n"

"	decl	%%ebp\n"
"	jnz	1b\n"
"	popl	%%ebp\n"
	:
	:
	: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "%ebp"
   );
#endif

#endif
}

static void RotateF2SystemBG0_r270_16(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp)
{
   long f2x,f2y;
   int dx,dy;
   UINT16 *BIT;
   UINT8 *SRC,ta;

   // Init Stuff
   // ----------

   f1x+=(319*f2xd);
   f1y+=(319*f2yd);

   BIT=(UINT16*)GameViewBitmap->line[0];
   SRC=pixel_bitmap->line[0];

   // Draw the rotated data
   // ---------------------
   // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   for(dy=0;dy<320;dy++){
      f2x=f1x;
      f2y=f1y;
      for(dx=0;dx<224;dx++){
         ta=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         if ((ta & 0xf) || !transp) {
	   *BIT=ReadWord(&map[ta*2]); // transp
	 }
         // BIT[0]=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         f2x+=f1xd;
         f2y+=f1yd;
         BIT++;
      }
      BIT+=(64);
      f1x-=f2xd;
      f1y-=f2yd;
   }
}

static void RotateF2SystemBG0_r270_32(long f1x, long f1y, long f1xd,long f1yd,long f2xd,long f2yd,UINT8 *map, int transp)
{
   long f2x,f2y;
   int dx,dy;
   UINT32 *BIT;
   UINT8 *SRC,ta;

   // Init Stuff
   // ----------

   f1x+=(319*f2xd);
   f1y+=(319*f2yd);

   BIT=(UINT32*)GameViewBitmap->line[0];
   SRC=pixel_bitmap->line[0];

   // Draw the rotated data
   // ---------------------
   // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   for(dy=0;dy<320;dy++){
      f2x=f1x;
      f2y=f1y;
      for(dx=0;dx<224;dx++){
         ta=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         if ((ta & 0xf) || !transp) {
	   *BIT=ReadLong(&map[ta*4]); // transp
	 }
         // BIT[0]=SRC[((f2x>>16)&0x1FF)|((f2y>>7)&0x3FE00)];
         f2x+=f1xd;
         f2y+=f1yd;
         BIT++;
      }
      BIT+=(64);
      f1x-=f2xd;
      f1y-=f2yd;
   }
}

static tc005rot_drawing_func *RotateF2SystemBG0,*RotateF2SystemBG0_r270;

static void select_drawing_func() {
  switch (display_cfg.bpp) {
  case  8: RotateF2SystemBG0 = RotateF2SystemBG0_8;
    RotateF2SystemBG0_r270 = RotateF2SystemBG0_r270_8;
    break;
  case 15:
  case 16: RotateF2SystemBG0 = RotateF2SystemBG0_16;
    RotateF2SystemBG0_r270 = RotateF2SystemBG0_r270_16;
    break;
  case 32: RotateF2SystemBG0 = RotateF2SystemBG0_32;
    RotateF2SystemBG0_r270 = RotateF2SystemBG0_r270_32;
    break;
  }
}

static int xmultiply;

void tc0005rot_draw_rot_r270(int col_ofs,int transp)
{
  //int x,y,zz;
  long px,py,ang1,ang2,ang3,ang4;
  UINT8 *map;
   /*if(RefreshBuffers){

   zz=0;
   for(y=512;y<1024;y+=8){
      for(x=0;x<512;x+=8){
         Draw8x8_Mapped(&GFX_BG[(ReadWord(&RAM_BG[zz])&0x3FFF)<<6],x,y,&rot_map[(ReadWord(&RAM_BG[zz])>>10)&0x30]);
         zz+=2;
      }
   }

   }*/

   // Set_Pens_15bit_xRGB(rot_pens, col_ofs<<4, 64);

   // Copy and Rotate BG0
   // -------------------

   px=((ReadWord(&RAM_SCR[0x00])<<20)|(ReadWord(&RAM_SCR[0x02])<<4));

   py=((ReadWord(&RAM_SCR[0x08])<<20)|(ReadWord(&RAM_SCR[0x0A])<<4));

   ang2=ReadWord(&RAM_SCR[0x04]);	// -8000 to 7FF0 (?)

   if((ang2&0x8000)!=0){ang2=0-(((ang2^0xFFFF)+1)<<xmultiply);}
   else{ang2=ang2<<xmultiply;}

   ang1=ReadWord(&RAM_SCR[0x06]);

   if((ang1&0x8000)!=0){ang1=0-(((ang1^0xFFFF)+1)<<4);}
   else{ang1=ang1<<4;}

   ang4=ReadWord(&RAM_SCR[0x0C]);

   if((ang4&0x8000)!=0){ang4=0-(((ang4^0xFFFF)+1)<<xmultiply);}
   else{ang4=ang4<<xmultiply;}

   ang3=ReadWord(&RAM_SCR[0x0E]);

   if((ang3&0x8000)!=0){ang3=0-(((ang3^0xFFFF)+1)<<4);}
   else{ang3=ang3<<4;}

   MAP_PALETTE_MULTI_MAPPED_NEW(
			  col_ofs,
			  16*4,
			  map);

   RotateF2SystemBG0_r270(px,py,ang1,ang2,ang3,ang4,map, transp);

/*    RotateF2SystemBG0(px,py,ang1<<4,ang2<<5,ang3<<4,ang4<<5,map); */
}

void tc0005rot_draw_rot(int col_ofs, int transp)
{
  //int x,y,zz;
   long px,py,ang1,ang2,ang3,ang4;
   UINT8 *map;

   /*if(RefreshBuffers){

   zz=0;
   for(y=512;y<1024;y+=8){
      for(x=0;x<512;x+=8){
         Draw8x8_Mapped(&GFX_BG[(ReadWord(&RAM_BG[zz])&0x3FFF)<<6],x,y,&rot_map[(ReadWord(&RAM_BG[zz])>>10)&0x30]);
         zz+=2;
      }
   }

   }*/

   // Copy and Rotate BG0
   // -------------------

   px=((ReadWord(&RAM_SCR[0x00])<<20)|(ReadWord(&RAM_SCR[0x02])<<4));

   py=((ReadWord(&RAM_SCR[0x08])<<20)|(ReadWord(&RAM_SCR[0x0A])<<4));

   ang2=ReadWord(&RAM_SCR[0x04]);	// -8000 to 7FF0 (?)

   if((ang2&0x8000)!=0){ang2=0-(((ang2^0xFFFF)+1));}

   ang1=ReadWord(&RAM_SCR[0x06]);

   if((ang1&0x8000)!=0){ang1=0-(((ang1^0xFFFF)+1));}

   ang4=ReadWord(&RAM_SCR[0x0C]);

   if((ang4&0x8000)!=0){ang4=0-(((ang4^0xFFFF)+1));}

   ang3=ReadWord(&RAM_SCR[0x0E]);

   if((ang3&0x8000)!=0){ang3=0-(((ang3^0xFFFF)+1));}

   MAP_PALETTE_MULTI_MAPPED_NEW(
			  col_ofs,
			  16*4,
			  map);

   RotateF2SystemBG0(px,py,ang1<<4,ang2<<xmultiply,ang3<<4,ang4<<xmultiply,map, transp);
}

void init_tc0005rot()
{
  // int ta;

   RAM_BG = tc0005rot.RAM;
   RAM_SCR= tc0005rot.RAM_SCR;
   GFX_BG = tc0005rot.GFX_ROT;

/*    rot_pens = Reserve_Pens(64); */

/*    for(ta=0;ta<64;ta++){ */
/*       rot_map[ta] = rot_pens+ta; */
/*    } */

/*    if(mode){ */
/*       rot_map[0] = 255; */
/*       rot_map[16] = 255; */
/*       rot_map[32] = 255; */
/*       rot_map[48] = 255; */
/*    } */

   if(pixel_bitmap) destroy_bitmap(pixel_bitmap);

   pixel_bitmap = create_bitmap_ex(8,512,512);

   clear_bitmap(pixel_bitmap);
   select_drawing_func();
   xmultiply = 5; // TC280GRD
}

void init_tc430grw() {
  init_tc0005rot();
  xmultiply = 4;
  // The 430GRW is a more modern version of the TC280GRD
  // the only difference is that the 2 x angles must be multiplied by 2 on
  // the 280GRD
}

void tc0005rot_refresh_buffer(void)
{
   UINT32 address;
   UINT16 data;
/*    int oldx = disp_x_8, oldy = disp_y_8; */
/*    disp_x_8 = 512 - 8; disp_y_8 = 512 - 8; */

   tc0005rot_set_bitmap();

   for(address=0;address<0x2000;address+=2){

      data = ReadWord(&RAM_BG[address]);

      Draw8x8_8(&GFX_BG[(data&0x3FFF)<<6],(address&0x7E)<<2,((address&0x1F80)>>4),(data>>10)&0x30);

   }

/*    disp_x_8 = oldx; disp_y_8 = oldy; */
   tc0005rot_unset_bitmap();
   select_drawing_func();
}

