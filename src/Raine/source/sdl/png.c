#include "raine.h"
#include "loadpng.h"
#include <SDL_image.h>
#include <png.h>

int _png_compression_level = Z_BEST_COMPRESSION;

BITMAP *load_png(const char *filename, RGB *pal) {
  SDL_Surface *s = IMG_Load(filename);
  return surface_to_bmp(s);
}

BITMAP *load_png_from_zip(unzFile uf, RGB *pal) {
  unz_file_info file_info;
  UINT8 *buffer;
  SDL_RWops *rw;

  unzGetCurrentFileInfo(uf,&file_info,NULL,0,NULL,0,NULL,0);
  buffer = malloc(file_info.uncompressed_size);
  unzReadCurrentFile(uf,buffer,file_info.uncompressed_size);
  rw = SDL_RWFromMem(buffer, file_info.uncompressed_size);

  SDL_Surface *s = IMG_Load_RW(rw,1);
  free(buffer);
  return surface_to_bmp(s);
}

