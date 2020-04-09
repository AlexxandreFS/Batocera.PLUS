#include "raine.h"
#include "newmem.h"
#include "loadroms.h"

static  GFX_LAYOUT charlayout =
{
	8,8,	/* 8*8 characters */
	RGN_FRAC(1,1),
	4,	/* 4 bits per pixel */
	{ 0, 1, 2, 3 },
	{ 2*4, 3*4, 0*4, 1*4, 6*4, 7*4, 4*4, 5*4 },
	{ 0*32, 1*32, 2*32, 3*32, 4*32, 5*32, 6*32, 7*32 },
	32*8	/* every sprite takes 32 consecutive bytes */
};

// why this layout doesn't work ?!!!
static  GFX_LAYOUT tile16x8_layout =
{
	16,8,	/* 16*8 sprites */
	RGN_FRAC(1,1),
	4,	/* 4 bits per pixel */
	{ 0, 8, 16, 24 },
	{ 32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7 },
	{ 0*64, 1*64, 2*64, 3*64, 4*64, 5*64, 6*64, 7*64 },
	64*8	/* every sprite takes 64 consecutive bytes */
};

GFX_LIST taitoz_gfxdecodeinfo[] =
{
	{ REGION_GFX2, &tile16x8_layout, },	/* sprite parts */
	{ REGION_GFX1, &charlayout, },		/* sprites & playfield */
	{ 0, NULL } /* end of array */
};

UINT8* process_lines(int region) {
   UINT8 *TMP,*GFX_LINES;
   int ta,tb, size = get_region_size(region);
   UINT16 tc;

   TMP = load_region[region];
   if(!(GFX_LINES=AllocateMem(size*4))) return NULL;

   tb=0;
   for(ta=0;ta<size;ta+=2){
      tc=ReadWord(&TMP[ta]);
      GFX_LINES[tb+0] =((tc&0x8000)>>(14));
      GFX_LINES[tb+1] =((tc&0x4000)>>(13));
      GFX_LINES[tb+2] =((tc&0x2000)>>(12));
      GFX_LINES[tb+3] =((tc&0x1000)>>(11));
      GFX_LINES[tb+4] =((tc&0x0800)>>(10));
      GFX_LINES[tb+5] =((tc&0x0400)>>( 9));
      GFX_LINES[tb+6] =((tc&0x0200)>>( 8));
      GFX_LINES[tb+7] =((tc&0x0100)>>( 7));
      GFX_LINES[tb+0]|=((tc&0x0080)>>( 7));
      GFX_LINES[tb+1]|=((tc&0x0040)>>( 6));
      GFX_LINES[tb+2]|=((tc&0x0020)>>( 5));
      GFX_LINES[tb+3]|=((tc&0x0010)>>( 4));
      GFX_LINES[tb+4]|=((tc&0x0008)>>( 3));
      GFX_LINES[tb+5]|=((tc&0x0004)>>( 2));
      GFX_LINES[tb+6]|=((tc&0x0002)>>( 1));
      GFX_LINES[tb+7]|=((tc&0x0001)>>( 0));
      tb+=8;
   }
   FreeMem(TMP);
   load_region[region] = NULL;
   return GFX_LINES;
}
