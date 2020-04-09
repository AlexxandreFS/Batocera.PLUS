/******************************************************************************/
/*                                                                            */
/*                               TILE MODIFIERS                               */
/*                                                                            */
/******************************************************************************/

#include "gameinc.h"
#include "tilemod.h"
#ifdef RAINE_DEBUG
#include "debug.h"
#endif

UINT8 *GFX_BG0;
UINT8 *GFX_BG1;
UINT8 *GFX_BG2;
UINT8 *GFX_OBJ;

UINT8 *GFX_BG0_SOLID;
UINT8 *GFX_BG1_SOLID;
UINT8 *GFX_BG2_SOLID;

UINT8 tile_8x8_map[8 * 8];
int max_tile_sprites; // used only in make_solid_mask_8x8 for now...

static struct TILE_INFO tile_8x8_template =
{
   1,
   TILE_TYPE_8x8,
   8,
   8,
   tile_8x8_map,
   NULL,
   0,
   0,
};

UINT8 tile_16x16_map[16 * 16];
UINT8 tile_32x32_map[32 * 32];

static struct TILE_INFO tile_16x16_template =
{
   1,
   TILE_TYPE_16x16,
   16,
   16,
   tile_16x16_map,
   NULL,
   0,
   0,
};

static struct TILE_INFO tile_32x32_template =
{
   1,
   TILE_TYPE_32x32,
   32,
   32,
   tile_32x32_map,
   NULL,
   0,
   0,
};

static void do_rotate(TILE_INFO *tile, UINT32 rotate)
{
   UINT32 count,size,x,y,ta,tb,tc;
   UINT8 *src,*buffer;

   if(!rotate) return;

   x     = tile->width;
   y     = tile->height;
   count = tile->count;
   size  = x * y;
   src   = tile->data;

   if(!(buffer=AllocateMem(size))) return;

   for(tc=0;tc<count;tc++){

   memcpy(buffer, src, size);

   switch(rotate){
   case 1:
      for(tb=0; tb<y; tb++){

         for(ta=0; ta<x; ta++){

            src[ ta + (tb*x) ] = buffer[ (((x-1)-ta)*y) + tb ];

         }

      }
   break;
   case 2:
      for(tb=0; tb<y; tb++){

         for(ta=0; ta<x; ta++){

            src[ ta + (tb*x) ] = buffer[ ((x-1)-ta) + (((y-1)-tb)*x) ];

         }

      }
   break;
   case 3:
      for(tb=0; tb<y; tb++){

         for(ta=0; ta<x; ta++){

            src[ ta + (tb*x) ] = buffer[ (ta*y) + ((y-1)-tb) ];

         }

      }
   break;
   }

   src += size;

   }

   FreeMem(buffer);
}

static void do_flip(TILE_INFO *tile, UINT32 flip)
{
   UINT32 count,size,x,y,ta,tb,tc;
   UINT8 *src,*buffer;

   if(!flip) return;

   x     = tile->width;
   y     = tile->height;
   count = tile->count;
   size  = x * y;
   src   = tile->data;

   if(!(buffer=AllocateMem(size))) return;

   for(tc=0;tc<count;tc++){

   memcpy(buffer, src, size);

   switch(flip){
   case 1:
      for(tb=0; tb<y; tb++){

         for(ta=0; ta<x; ta++){

            src[ ta + (tb*x) ] = buffer[ ((x-1)-ta) + (tb*x) ];

         }

      }
   break;
   case 2:
      for(tb=0; tb<y; tb++){

         for(ta=0; ta<x; ta++){

            src[ ta + (tb*x) ] = buffer[ ta + (((y-1)-tb)*x) ];

         }

      }
   break;
   case 3:
      for(tb=0; tb<y; tb++){

         for(ta=0; ta<x; ta++){

            src[ ta + (tb*x) ] = buffer[ ((x-1)-ta) + (((y-1)-tb)*x) ];

         }

      }
   break;
   }

   src += size;

   }

   FreeMem(buffer);
}

void Rotate8x8(UINT8 *source, UINT32 count)
{
   UINT8 *TMP,*SRC;
   UINT32 ta,tb,tc;

   if(!(TMP=AllocateMem(0x40))) return;

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x40;tb++){
      TMP[tb]=SRC[tb];
   }

   for(tb=0;tb<8;tb++){
   for(ta=0;ta<8;ta++){
      SRC[ta+(tb<<3)]=TMP[(ta<<3)+tb];
   }
   }

   SRC+=0x40;

   }

   FreeMem(TMP);
}

void Rotate8x8_4bpp(UINT8 *source, UINT32 count)
{
   UINT8 TMP[0x40],TMP2[0x40],*SRC;
   UINT32 ta,tb,tc;

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x40;tb+=2){
      TMP[tb+0]=(SRC[tb>>1]>>4)&15;
      TMP[tb+1]=(SRC[tb>>1]>>0)&15;
   }

   for(tb=0;tb<8;tb++){
   for(ta=0;ta<8;ta++){
      TMP2[ta+(tb<<3)]=TMP[(ta<<3)+tb];
   }
   }

   for(tb=0;tb<0x40;tb+=2){
      SRC[tb>>1]=(TMP2[tb+0]&15)<<4;
      SRC[tb>>1]|=(TMP2[tb+1]&15)<<0;
   }

   SRC+=0x20;

   }

}


void Rotate16x16(UINT8 *source, UINT32 count)
{
   UINT8 *TMP,*SRC;
   UINT32 ta,tb,tc;

   if(!(TMP=AllocateMem(0x100))){return;}

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x100;tb++){
      TMP[tb]=SRC[tb];
   }

   for(tb=0;tb<16;tb++){
   for(ta=0;ta<16;ta++){
      SRC[ta+(tb<<4)]=TMP[(ta<<4)+tb];
   }
   }

   SRC+=0x100;

   }

   FreeMem(TMP);
}


void Flip8x8_X(UINT8 *source, UINT32 count)
{
   UINT8 *TMP,*SRC;
   UINT32 ta,tb,tc;

   if(!(TMP=AllocateMem(0x40))){return;}

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x40;tb++){
      TMP[tb]=SRC[tb];
   }

   for(tb=0;tb<8;tb++){
   for(ta=0;ta<8;ta++){
      SRC[ta+(tb<<3)]=TMP[(ta)+((7-tb)<<3)];
   }
   }

   SRC+=0x40;

   }

   FreeMem(TMP);
}

void Flip8x8_4bpp_X(UINT8 *source, UINT32 count)
{
   UINT8 TMP[0x40],TMP2[0x40],*SRC;
   UINT32 ta,tb,tc;

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x40;tb+=2){
      TMP[tb+0]=(SRC[tb>>1]>>4)&15;
      TMP[tb+1]=(SRC[tb>>1]>>0)&15;
   }

   for(tb=0;tb<8;tb++){
   for(ta=0;ta<8;ta++){
      TMP2[ta+(tb<<3)]=TMP[(ta)+((7-tb)<<3)];
   }
   }

   for(tb=0;tb<0x40;tb+=2){
      SRC[tb>>1]=(TMP2[tb+0]&15)<<4;
      SRC[tb>>1]|=(TMP2[tb+1]&15)<<0;
   }

   SRC+=0x20;

   }

}


void Flip16x16_X(UINT8 *source, UINT32 count)
{
   UINT8 *TMP,*SRC;
   UINT32 ta,tb,tc;

   if(!(TMP=AllocateMem(0x100))){return;}

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x100;tb++){
      TMP[tb]=SRC[tb];
   }

   for(tb=0;tb<16;tb++){
   for(ta=0;ta<16;ta++){
      SRC[ta+(tb<<4)]=TMP[(ta)+((15-tb)<<4)];
   }
   }

   SRC+=0x100;

   }

   FreeMem(TMP);
}

void Flip8x8_Y(UINT8 *source, UINT32 count)
{
   UINT8 *TMP,*SRC;
   UINT32 ta,tb,tc;

   if(!(TMP=AllocateMem(0x40))){return;}

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x40;tb++){
      TMP[tb]=SRC[tb];
   }

   for(tb=0;tb<8;tb++){
   for(ta=0;ta<8;ta++){
      SRC[ta+(tb<<3)]=TMP[(7-ta)+((tb)<<3)];
   }
   }

   SRC+=0x40;

   }

   FreeMem(TMP);
}

void Flip16x16_Y(UINT8 *source, UINT32 count)
{
   UINT8 *TMP,*SRC;
   UINT32 ta,tb,tc;

   if(!(TMP=AllocateMem(0x100))){return;}

   SRC=source;

   for(tc=0;tc<count;tc++){

   for(tb=0;tb<0x100;tb++){
      TMP[tb]=SRC[tb];
   }

   for(tb=0;tb<16;tb++){
   for(ta=0;ta<16;ta++){
      SRC[ta+(tb<<4)]=TMP[(15-ta)+((tb)<<4)];
   }
   }

   SRC+=0x100;

   }

   FreeMem(TMP);
}

void CountColours(UINT8 *source, UINT32 count)
{
   UINT32 ta,tb;

   tb=0;
   for(ta=0;ta<count;ta++){
      if((source[ta]&0x20)!=0)tb++;
   }
#ifdef RAINE_DEBUG
   print_debug("64 Colour Bytes: $%08x\n",tb);
#endif
}


UINT8 check_tile_solid(UINT8 *src, UINT32 size)
{
   UINT32 i, a, b;

   for(i = 0, a = 0, b = 0; i < size; i++){
      if(src[i])
         a = 1;
      else
         b = 1;
   }

   if((!a) &&  (b)) return 0; // Draw Nothing
   if( (a) &&  (b)) return 1; // Draw Transparent
   if( (a) && (!b)) return 2; // Draw Solid

   return 0;
}

UINT32 tile_list_count;

UINT8 *MakeSolidTileMap(UINT8 *source, UINT32 count, UINT32 size)
{
   UINT32 ta,tb,tc;
   UINT8 *map;

   if(!(map=AllocateMem(count)))return(NULL);

   // Apparently tiles are 16x16 per default... (hope so !)
   tile_list[tile_list_count].count  = count;
   tile_list[tile_list_count].type   = TILE_TYPE_16x16;
   tile_list[tile_list_count].width  = 16;
   tile_list[tile_list_count].height = 16;
   tile_list[tile_list_count].data   = source;
   tile_list[tile_list_count].mask   = map;
   tile_list[tile_list_count].rotate = 0;
   tile_list[tile_list_count].flip   = 0;

   tile_list_count++;

   tb=0;
   for(ta=0;ta<count;ta++){
      map[ta]=1;         // This tile is solid!
      for(tc=0;tc<size;tc++,tb++){
         if(source[tb]==0)map[ta]=0;   // This tile is not solid!
      }
   }

   return(map);
}

char *tile_type[TILE_TYPE_MAX] =
{
   " X x  Y (Nbpp)",
   " 8 x  8 (8bpp)",
   "16 x 16 (8bpp)",
   "32 x 32 (8bpp)",
};

void check_tile_rotation(void)
{
   UINT32 i,j,k;

   /*

   rotate and flip all tile_list tiles

   */

   for( i = 0; i < tile_list_count; i ++){

      j  = display_cfg.rotate;
      j -= tile_list[i].rotate;
      j &= 3;

      k  = display_cfg.flip;
      k -= tile_list[i].flip;
      k &= 3;

      if(j || k){

         do_flip(&tile_list[i], tile_list[i].flip);

         do_rotate(&tile_list[i], j);

         do_flip(&tile_list[i], display_cfg.flip);

         tile_list[i].rotate = display_cfg.rotate;
         tile_list[i].flip   = display_cfg.flip;

      }

   }

   /*

   rotate and flip the template tiles (used for building correctly
   rotated GFX RAM tiles)

   */

   for(i = 0; i < (8 * 8); i++)

       tile_8x8_map[i] = i;

   tile_8x8_template.rotate = 0;
   tile_8x8_template.flip = 0;

   do_rotate(&tile_8x8_template, (0 - display_cfg.rotate) & 3);
   do_flip(&tile_8x8_template, display_cfg.flip);

   tile_8x8_template.rotate = display_cfg.rotate;
   tile_8x8_template.flip = display_cfg.flip;


   for(i = 0; i < (16 * 16); i++)

       tile_16x16_map[i] = i;

   tile_16x16_template.rotate = 0;
   tile_16x16_template.flip = 0;

   do_rotate(&tile_16x16_template, (0 - display_cfg.rotate) & 3);
   do_flip(&tile_16x16_template, display_cfg.flip);

   tile_16x16_template.rotate = display_cfg.rotate;
   tile_16x16_template.flip = display_cfg.flip;

   for(i = 0; i < (32 * 32); i++)

       tile_32x32_map[i] = i;

   tile_32x32_template.rotate = 0;
   tile_32x32_template.flip = 0;

   do_rotate(&tile_32x32_template, (0 - display_cfg.rotate) & 3);
   do_flip(&tile_32x32_template, display_cfg.flip);

   tile_32x32_template.rotate = display_cfg.rotate;
   tile_32x32_template.flip = display_cfg.flip;

}

UINT8 *MakeSolidTileMap16x16(UINT8 *source, UINT32 count)
{
   return MakeSolidTileMap(source,count,16*16);
}

UINT8 *MakeSolidTileMap32x32(UINT8 *source, UINT32 count)
{
   return MakeSolidTileMap(source,count,32*32);
}

UINT8 *MakeSolidTileMap64x64(UINT8 *source, UINT32 count)
{
   return MakeSolidTileMap(source,count,64*64);
}


UINT32 get_pad_size(UINT32 count)
{
   UINT32 pad_size;

   pad_size = 0x010000;
   if(count>0x10000) pad_size = 0x020000;
   if(count>0x20000) pad_size = 0x040000;
   if(count>0x40000) pad_size = 0x080000;
   if(count>0x80000) pad_size = 0x100000;

   return pad_size;
}

UINT8 *make_solid_mask(UINT8 *source, UINT32 count, UINT32 size, UINT32 pad_size)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *map;
   int nb;
   for (nb=0; nb<MAX_GFX; nb++) {
     if (source == gfx[nb]) {
       if (gfx_solid[nb]) {
#ifdef RAINE_DEBUG
	 printf("make_solid_mask called again for region_gfx %d\n",nb+1);
#endif
	 return gfx_solid[nb];
       }
       break;
     }
   }

   if(pad_size<count)
      pad_size = get_pad_size(count);

   if(!(map=AllocateMem(pad_size))) return NULL;

   memset(map,0x00,pad_size);

   tb=0;
   for(ta=0;ta<count;ta++){
      td=0;
      te=0;
      for(tc=0;tc<size;tc++,tb++){
         if(source[tb])
            td=1;
         else
            te=1;
      }
      if((td==0)&&(te==1)) map[ta]=0;      // All pixels are 0: Don't Draw
      if((td==1)&&(te==1)) map[ta]=1;      // Mixed: Draw Trans
      if((td==1)&&(te==0)) map[ta]=2;      // All pixels are !0: Draw Solid
   }

   if (nb < MAX_GFX && source == gfx[nb]) {
     gfx_solid[nb] = map;
   }
   return map;
}

UINT8 *make_solid_region_8x8(UINT32 region) {
  if (load_region[region])
    return make_solid_mask_8x8(load_region[region],get_region_size(region)/(8*8));
  return NULL;
}

UINT8 *make_solid_region_16x16(UINT32 region) {
  return make_solid_mask_16x16(load_region[region],get_region_size(region)/(16*16));
}

UINT8 *make_solid_region_16x8(UINT32 region) {
  return make_solid_mask_16x8(load_region[region],get_region_size(region)/(16*8));
}

UINT8 *make_solid_mask_8x8(UINT8 *source, UINT32 count)
{
   UINT8 *map;

   if (count > max_tile_sprites)
     max_tile_sprites = count;

   map = make_solid_mask(source, count, 8*8, 0);

   tile_list[tile_list_count].count  = count;
   tile_list[tile_list_count].type   = TILE_TYPE_8x8;
   tile_list[tile_list_count].width  = 8;
   tile_list[tile_list_count].height = 8;
   tile_list[tile_list_count].data   = source;
   tile_list[tile_list_count].mask   = map;
   tile_list[tile_list_count].rotate = 0;
   tile_list[tile_list_count].flip   = 0;

   tile_list_count++;

   return map;
}

UINT8 *make_solid_mask_16x8(UINT8 *source, UINT32 count)
{
   return make_solid_mask(source, count, 16*8, 0);
}

UINT8 *make_solid_mask_16x16(UINT8 *source, UINT32 count)
{
   UINT8 *map;

   map = make_solid_mask(source, count, 16*16, 0);

   tile_list[tile_list_count].count  = count;
   tile_list[tile_list_count].type   = TILE_TYPE_16x16;
   tile_list[tile_list_count].width  = 16;
   tile_list[tile_list_count].height = 16;
   tile_list[tile_list_count].data   = source;
   tile_list[tile_list_count].mask   = map;
   tile_list[tile_list_count].rotate = 0;
   tile_list[tile_list_count].flip   = 0;

   tile_list_count++;

   return map;
}

UINT8 *make_solid_mask_32x32(UINT8 *source, UINT32 count)
{
   UINT8 *map;

   map = make_solid_mask(source, count, 32*32, 0);

   tile_list[tile_list_count].count  = count;
   tile_list[tile_list_count].type   = TILE_TYPE_32x32;
   tile_list[tile_list_count].width  = 32;
   tile_list[tile_list_count].height = 32;
   tile_list[tile_list_count].data   = source;
   tile_list[tile_list_count].mask   = map;
   tile_list[tile_list_count].rotate = 0;
   tile_list[tile_list_count].flip   = 0;

   tile_list_count++;

   return map;
}

UINT8 *make_solid_mask_64x64(UINT8 *source, UINT32 count)
{
   return make_solid_mask(source, count, 64*64, 0);
}

UINT8 *make_solid_mask_pad_8x8(UINT8 *source, UINT32 count, UINT32 pad_size)
{
   UINT8 *map;

   map = make_solid_mask(source, count, 8*8, pad_size);

   tile_list[tile_list_count].count  = count;
   tile_list[tile_list_count].type   = TILE_TYPE_8x8;
   tile_list[tile_list_count].width  = 8;
   tile_list[tile_list_count].height = 8;
   tile_list[tile_list_count].data   = source;
   tile_list[tile_list_count].mask   = map;
   tile_list[tile_list_count].rotate = 0;
   tile_list[tile_list_count].flip   = 0;

   tile_list_count++;

   return map;
}

UINT8 *make_solid_mask_pad_16x16(UINT8 *source, UINT32 count, UINT32 pad_size)
{
   UINT8 *map;

   map = make_solid_mask(source, count, 16*16, pad_size);

   tile_list[tile_list_count].count  = count;
   tile_list[tile_list_count].type   = TILE_TYPE_16x16;
   tile_list[tile_list_count].width  = 16;
   tile_list[tile_list_count].height = 16;
   tile_list[tile_list_count].data   = source;
   tile_list[tile_list_count].mask   = map;
   tile_list[tile_list_count].rotate = 0;
   tile_list[tile_list_count].flip   = 0;

   tile_list_count++;

   return map;
}

UINT8 *make_solid_mask_4bpp(UINT8 *source, UINT32 count, UINT32 size)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *map;

   ta = get_pad_size(count);

   if(!(map=AllocateMem(ta))) return NULL;

   memset(map,0x00,ta);

   tb=0;
   for(ta=0;ta<count;ta++){
      td=0;
      te=0;
      for(tc=0;tc<size;tc+=2,tb++){
         if((source[tb]&0xF0)!=0) td=1;
         else te=1;
         if((source[tb]&0x0F)!=0) td=1;
         else te=1;
      }
      if((td==0)&&(te==1)) map[ta]=0;      // All pixels are 0: Don't Draw
      if((td==1)&&(te==1)) map[ta]=1;      // Mixed: Draw Trans
      if((td==1)&&(te==0)) map[ta]=2;      // All pixels are !0: Draw Solid
   }

   return(map);
}

UINT8 *make_solid_mask_8x8_4bpp(UINT8 *source, UINT32 count)
{
   return make_solid_mask_4bpp(source,count,8*8);
}

UINT8 *make_solid_mask_16x16_4bpp(UINT8 *source, UINT32 count)
{
   return make_solid_mask_4bpp(source,count,16*16);
}

UINT8 *make_solid_mask_64x64_4bpp(UINT8 *source, UINT32 count)
{
   return make_solid_mask_4bpp(source,count,64*64);
}


UINT8 *make_colour_count(UINT8 *source, UINT32 count, UINT32 size)
{
   UINT32 ta,tb,tc,td,te;
   UINT8 *map;

   ta = get_pad_size(count);

   if(!(map=AllocateMem(ta))) return NULL;

   memset(map,0x00,ta);

   tb=0;
   for(ta=0;ta<count;ta++){
      td = 0;
      for(tc=0;tc<size;tc++,tb++){
         if(source[tb] > td) td = source[tb];
      }
      te = 0;
      if(td>0x00) te=0x01;
      if(td>0x01) te=0x02;
      if(td>0x02) te=0x04;
      if(td>0x04) te=0x08;
      if(td>0x08) te=0x10;
      if(td>0x10) te=0x20;
      if(td>0x20) te=0x40;
      if(td>0x40) te=0x80;
      if(td>0x80) te=0xFF;

      map[ta] = te;
   }

   return map;
}

UINT8 *make_colour_count_16x16(UINT8 *source, UINT32 count)
{
   return make_colour_count(source,count,16*16);
}

/*

GFX ROM decoding (mame style)

*/

/* #define readbit(src, bitnum)                       \ */
/*    (src[(bitnum) >> 3] & (0x80 >> ((bitnum) & 7))) \ */

static inline int readbit(const UINT8 *src,int bitnum)
{
	return src[bitnum / 8] & (0x80 >> (bitnum % 8));
}

typedef struct GFX_ELEMENT
{
   int width, height;
   unsigned char *gfxdata; /* pixel data */
   int line_modulo;        /* amount to add to get to the next line (usually = width) */
   int char_modulo;        /* = line_modulo * height */
} GFX_ELEMENT;


static void decodechar(GFX_ELEMENT *gfx, int num, const UINT8 *src, const GFX_LAYOUT *gl)
{
   int plane,x,y;
   UINT8 *dp;
   int baseoffs;
   const UINT32 *xoffset,*yoffset;

   xoffset = gl->xoffset;
   yoffset = gl->yoffset;

   dp = gfx->gfxdata + num * gfx->char_modulo;
   memset(dp,0,gfx->height * gfx->line_modulo);

   baseoffs = num * gl->charincrement;

   for (plane = 0;plane < gl->planes;plane++)
   {
      int shiftedbit = 1 << (gl->planes-1-plane);
      int offs = baseoffs + gl->planeoffset[plane];

      dp = gfx->gfxdata + num * gfx->char_modulo + (gfx->height-1) * gfx->line_modulo;

      y = gfx->height;
      while (--y >= 0)
      {
         int offs2 = offs + yoffset[y];

         x = gfx->width;
         while (--x >= 0)
         {
            if (readbit(src,offs2 + xoffset[x]))
               dp[x] |= shiftedbit;
         }
         dp -= gfx->line_modulo;
      }

   }
}

UINT8 *decode_gfx(const UINT8 *src, const UINT32 src_size, const GFX_LAYOUT *layout,UINT32 *dest_size)
{
   GFX_ELEMENT gfx;
   gfx_layout gl;
   UINT8 *gfx_data;
   UINT32 c, j, reglen;

   /*

   some weirdness

   */

   reglen = 8 * src_size;

   memcpy(&gl, layout, sizeof(gl));

   if (IS_FRAC(gl.total))
      gl.total = reglen / gl.charincrement * FRAC_NUM(gl.total) / FRAC_DEN(gl.total);

   for (j = 0;j < MAX_GFX_PLANES;j++)
   {
      if (IS_FRAC(gl.planeoffset[j]))
      {
         gl.planeoffset[j] = FRAC_OFFSET(gl.planeoffset[j]) +
               reglen * FRAC_NUM(gl.planeoffset[j]) / FRAC_DEN(gl.planeoffset[j]);
      }
   }

   for (j = 0;j < MAX_GFX_SIZE;j++)
   {
      if (IS_FRAC(gl.xoffset[j]))
      {
         gl.xoffset[j] = FRAC_OFFSET(gl.xoffset[j]) +
               reglen * FRAC_NUM(gl.xoffset[j]) / FRAC_DEN(gl.xoffset[j]);
      }
      if (IS_FRAC(gl.yoffset[j]))
      {
         gl.yoffset[j] = FRAC_OFFSET(gl.yoffset[j]) +
               reglen * FRAC_NUM(gl.yoffset[j]) / FRAC_DEN(gl.yoffset[j]);
      }
   }

   /*

   some setup then decode

   */

   memset(&gfx, 0, sizeof(gfx));

   gfx.width = gl.width;
   gfx.height = gl.height;

   gfx.line_modulo = gfx.width;
   gfx.char_modulo = gfx.line_modulo * gfx.height;

   reglen = gl.total * gfx.char_modulo * sizeof(UINT8);
   gfx_data = AllocateMem(reglen);
   if (dest_size)
     *dest_size = reglen; // for get_region_size

   if(!gfx_data)
   {
      return 0;
   }

   gfx.gfxdata = gfx_data;
   for (c = 0;c < gl.total;c++)
      decodechar(&gfx, c, src, &gl);

   return gfx_data;
}

/*

convert real bpp -> internal bpp

 8 ->  8
15 -> 16
16 -> 16
24 -> 32
32 -> 32

*/

UINT32 internal_bpp(UINT32 source)
{
   static const UINT32 dest[4] =
   {
      8, 16, 32, 32,
   };

   return dest[((source - 1) >> 3) & 3];
}

int get_mask(int v) {
    // Get the mask closest to the value passed
    int m = 1;
    if (v) v--;
    while (v >>= 1)
	m = (m<<1)|1;
    return m;
}

