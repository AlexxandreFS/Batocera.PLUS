#include "raine.h"

/* Super simple handling of inifinite rom_dirs.
 * The idea is to remain compatible with the old array, so we want a not-so-
 * dynamic array. The thing which makes it dynamic is the call to alloc_romdir
 * Except this to read we do now
 * for (n=0; dir_cfg.rom_dir[n]; n++)
 * instead of
 * for (n=0; n<4; n++)
 */

static int nb_alloc;

void init_rom_dir() {
  nb_alloc = 5;
  dir_cfg.rom_dir = calloc(nb_alloc,sizeof(char*));
}

// make sure the nth index is already allocated
void alloc_romdir(int n) {
  while (n >= nb_alloc-1) {
    int x;
    nb_alloc += 5;
    dir_cfg.rom_dir = realloc(dir_cfg.rom_dir,nb_alloc*sizeof(char*));
    for (x=nb_alloc-5; x<nb_alloc; dir_cfg.rom_dir[x++] = NULL);
  }
}

void add_rom_dir(char *s) {
  int nb_used;
  for (nb_used=0; dir_cfg.rom_dir[nb_used]; nb_used++);
  alloc_romdir(nb_used);
  dir_cfg.rom_dir[nb_used] = strdup(s);
}

void remove_rom_dir(int sel) {
  if (sel < nb_alloc) {
    if (dir_cfg.rom_dir[sel]) {
      int n;
      free(dir_cfg.rom_dir[sel]);
      for (n=sel+1; n<nb_alloc; n++)
	dir_cfg.rom_dir[n-1] = dir_cfg.rom_dir[n];
      dir_cfg.rom_dir[nb_alloc-1] = NULL;
    }
  }
}

