/* loadpng, Allegro wrapper routines for libpng
 * by Peter Wang (tjaden@users.sf.net).
 *
 * This file is hereby placed in the public domain.
 */


#include <png.h>
#include "raine.h"
#include "loadpng.h"
#include "sasound.h"
#include "cpumain.h"
#include "profile.h"



/* write_data:
 *  Custom write function to use Allegro packfile routines,
 *  rather than C streams.
 */
static void write_data(png_structp png_ptr, png_bytep data, png_uint_32 length)
{
    FILE *f = png_get_io_ptr(png_ptr);
    if ((png_uint_32)fwrite(data, 1, length, f) != length)
	png_error(png_ptr, "write error (loadpng calling fwrite)");
}

/* Don't think Allegro has any problem with buffering
 * (rather, Allegro provides no way to flush packfiles).
 */
static void flush_data(png_structp png_ptr) { (void)png_ptr; }



/* save_indexed:
 *  Core save routine for 8 bpp images.
 * */
static int save_indexed(png_structp png_ptr, BITMAP *bmp)
{
    ASSERT(bitmap_color_depth(bmp) == 8);

	int y;

	for (y=0; y<bmp->h; y++) {
	    png_write_row(png_ptr, bmp->line[y]);
	}

	return 1;
}

#ifdef SDL
static inline int getpixel( int depth, unsigned char *pix, int x) {
  switch(depth) {
    case 15:
    case 16:
      return ((Uint16 *)pix)[x];
  }
  return ((Uint32 *)pix)[x];
}

#endif

/* save_rgb:
 *  Core save routine for 15/16/24 bpp images (original by Martijn Versteegh).
 */
static int save_rgb(png_structp png_ptr, BITMAP *bmp)
{
    const int depth = bitmap_color_depth(bmp);
    unsigned char *rowdata;
    int y, x;
    ASSERT(depth == 15 || depth == 16 || depth == 24);

    rowdata = malloc(bmp->w * 3);
    if (!rowdata)
	return 0;

    for (y=0; y<bmp->h; y++) {
	unsigned char *p = rowdata;

#ifdef SDL
	unsigned char *pix = bmp->line[y];

	for (x = 0; x < bmp->w; x++) {
	  Uint8 r,g,b;
	  int c = getpixel(depth,pix,x);
	  SDL_GetRGB(c,color_format,&r,&g,&b);

	  *p++ = r;
	  *p++ = g;
	  *p++ = b;
	}
#else
	if (depth == 15) {
	    for (x = 0; x < bmp->w; x++) {
		int c = getpixel(bmp, x, y);
		*p++ = getr15(c);
		*p++ = getg15(c);
		*p++ = getb15(c);
	    }
	}
	else if (depth == 16) {
	    for (x = 0; x < bmp->w; x++) {
		int c = getpixel(bmp, x, y);
		*p++ = getr16(c);
		*p++ = getg16(c);
		*p++ = getb16(c);
	    }
	}
	else { /* depth == 24 */
	    for (x = 0; x < bmp->w; x++) {
		int c = getpixel(bmp, x, y);
		*p++ = getr24(c);
		*p++ = getg24(c);
		*p++ = getb24(c);
	    }
	}
#endif
	png_write_row(png_ptr, rowdata);
    }

    free(rowdata);

    return 1;
}



/* save_rgba:
 *  Core save routine for 32 bpp images.
 */
static int save_rgba(png_structp png_ptr, BITMAP *bmp)
{
    unsigned char *rowdata;
    int x, y;

    ASSERT(bitmap_color_depth(bmp) == 32);

    rowdata = malloc(bmp->w * 4);
    if (!rowdata)
	return 0;

    for (y=0; y<bmp->h; y++) {
	unsigned char *p = rowdata;

#ifdef SDL
	unsigned char *pix = bmp->line[y];
	SDL_PixelFormat *fmt = get_surface_from_bmp(bmp)->format;

	for (x = 0; x < bmp->w; x++) {
	  Uint8 r,g,b;
	  int c = getpixel(32,pix,x);
	  SDL_GetRGB(c,fmt,&r,&g,&b);
	  *p++ = r;
	  *p++ = g;
	  *p++ = b;
	  *p++ = 255;
	}
#else
        for (x=0; x<bmp->w; x++) {
            int c = getpixel(bmp, x, y);
	    *p++ = getr32(c);
	    *p++ = getg32(c);
	    *p++ = getb32(c);
	    *p++ = geta32(c);
        }
#endif
        png_write_row(png_ptr, rowdata);
    }

    free(rowdata);

    return 1;
}



/* save_png:
 *  Writes a non-interlaced, no-frills PNG, taking the usual save_xyz
 *  parameters.  Returns non-zero on error.
 */
static int really_save_png(FILE *fp, BITMAP *bmp, const RGB *pal)
{
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    int depth;
    int colour_type;

    depth = bitmap_color_depth(bmp);
    if (depth == 8 && !pal)
	return -1;

    /* Create and initialize the png_struct with the
     * desired error handler functions.
     */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
				      (void *)NULL, NULL, NULL);
    if (!png_ptr)
	goto Error;

    /* Allocate/initialize the image information data. */
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
	goto Error;

    /* Set error handling. */
    if (setjmp(png_jmpbuf(png_ptr))) {
	/* If we get here, we had a problem reading the file. */
	goto Error;
    }

    /* Use packfile routines. */
    png_set_write_fn(png_ptr, fp, (png_rw_ptr)write_data, flush_data);

    /* Set the image information here.  Width and height are up to 2^31,
     * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
     * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
     * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
     * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
     * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
     * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE.
     */
    if (depth == 8)
	colour_type = PNG_COLOR_TYPE_PALETTE;
    else if (depth == 32)
	colour_type = PNG_COLOR_TYPE_RGB_ALPHA;
    else
	colour_type = PNG_COLOR_TYPE_RGB;

    /* Set compression level. */
    png_set_compression_level(png_ptr, _png_compression_level);

    png_set_IHDR(png_ptr, info_ptr, bmp->w, bmp->h, 8, colour_type,
		 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
		 PNG_FILTER_TYPE_BASE);

    /* Set the palette if there is one.  Required for indexed-color images. */
    if (colour_type == PNG_COLOR_TYPE_PALETTE) {
	png_color palette[256];
	int i;

	for (i = 0; i < 256; i++) {
#ifdef SDL
	    palette[i].red   = (pal[i].r);
	    palette[i].green = (pal[i].g);
	    palette[i].blue  = (pal[i].b);
#else
	    palette[i].red   = _rgb_scale_6[pal[i].r];   /* 64 -> 256 */
	    palette[i].green = _rgb_scale_6[pal[i].g];
	    palette[i].blue  = _rgb_scale_6[pal[i].b];
#endif
	}

	/* Set palette colors. */
	png_set_PLTE(png_ptr, info_ptr, palette, 256);
    }

    /* Optionally write comments into the image ... Nah. */

    /* Write the file header information. */
    png_write_info(png_ptr, info_ptr);

    /* Once we write out the header, the compression type on the text
     * chunks gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
     * PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
     * at the end.
     */

    /* Save the data. */
    switch (depth) {
	case 8:
	    if (!save_indexed(png_ptr, bmp))
		goto Error;
	    break;
	case 15:
	case 16:
	case 24:
	    if (!save_rgb(png_ptr, bmp))
		goto Error;
	    break;
	case 32:
	    if (!save_rgba(png_ptr, bmp))
		goto Error;
	    break;
	default:
	    ASSERT(FALSE);
	    goto Error;
    }

    png_write_end(png_ptr, info_ptr);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;

  Error:

    if (png_ptr) {
	if (info_ptr)
	    png_destroy_write_struct(&png_ptr, &info_ptr);
	else
	    png_destroy_write_struct(&png_ptr, NULL);
    }

    return -1;
}


int save_png(const char *filename, BITMAP *bmp, const RGB *pal)
{
    FILE *fp;
    int result;

    ASSERT(filename);
    ASSERT(bmp);

    if (!raine_cfg.req_pause_game) {
      sa_pause_sound();
      stop_cpu_main();
    }
    fp = fopen(filename, "wb");
    if (!fp)
	return -1;

#ifndef SDL
    acquire_bitmap(bmp);
#endif
    result = really_save_png(fp, bmp, pal);
#ifndef SDL
    release_bitmap(bmp);
#endif

    fclose(fp);

    if (!raine_cfg.req_pause_game) {
      start_cpu_main();
      sa_unpause_sound();
      reset_ingame_timer();
    }
    return result;
}
