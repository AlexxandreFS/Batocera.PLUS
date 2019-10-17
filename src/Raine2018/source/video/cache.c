// Basic tilemap cache for solid sprites.
/* The idea is to use the sprite drawn on screen instead of the classic */
/* drawing function for solid sprites. This avoids the indirection of the */
/* palette and allows to draw faster. */
/* This was done for mazinger, which had a serious slow down for its */
/* drawing functions. It is currently in toaplan2 too, but I don't know */
/* if it's usefull in toaplan2. */
/* For now it works only for 8x8 sprites, but in any depth. */
/* Just call init_tile_cache AFTER your make_solid_mask_8x8 calls, and */
/* then see cave.c for how to handle solid 8x8 sprites. */

#include "raine.h"
#include "newmem.h"
#include "newspr.h"
#include <string.h> // memcpy
#include "tilemod.h" // max_tile_sprites
#include "blit.h"

UINT8 **tile_cache;
UINT8 **cache_map;

#define MAX_TILES_CACHE 1024

static UINT32 *tile_used;;
static UINT16 nb_tile_used;

int call_init_tile_cache;

void init_tile_cache() {
  if (!max_tile_sprites) {
    call_init_tile_cache = 1; // called from the loading function...
    return;
  }
  tile_cache = (UINT8**)AllocateMem(max_tile_sprites*sizeof(UINT8*));
  /* cache_map is an optional array to hold the color map pointer for cases */
  /* where the same tile is displayed with 2 different banks in the same */
  /* layer. This is extremely rare (only whoopee known to do it for now. */
  /* So only the allocation is handled here. This array is not filled nor */
  /* tested automatically. See toaplan2.c for how to use it. */
  cache_map = (UINT8**)AllocateMem(max_tile_sprites*sizeof(UINT8*));
  memset(tile_cache,0,max_tile_sprites*sizeof(UINT8*));
  nb_tile_used = 0;
  tile_used = (UINT32*)AllocateMem(sizeof(UINT32)*MAX_TILES_CACHE);
}

// Same thing, but 4 times the size for flipping.
void init_tile_cachex4() {
  if (!max_tile_sprites) {
    allegro_message("init_tile_cache called before make_solid_mask_8x8");
    exit(1);
  }
  tile_cache = (UINT8**)AllocateMem(max_tile_sprites*sizeof(UINT8*)*4);
  cache_map = (UINT8**)AllocateMem(max_tile_sprites*4*sizeof(UINT8*));
  memset(tile_cache,0,max_tile_sprites*sizeof(UINT8*)*4);
  nb_tile_used = 0;
  tile_used = (UINT32*)AllocateMem(sizeof(UINT32)*MAX_TILES_CACHE);
}

static void store_cache(cache_data *data) {
  data->tile_cache = tile_cache;
  data->cache_map = cache_map;
  data->tile_used = tile_used;
  data->nb_tile_used = nb_tile_used;
}

void new_tile_cache(cache_data *data) {
  store_cache(data);
  init_tile_cache();
}

void new_tile_cachex4(cache_data *data) {
  store_cache(data);
  init_tile_cachex4();
}

void switch_cache(cache_data *old, cache_data *new) {
  store_cache(old);
  tile_cache = new->tile_cache;
  cache_map = new->cache_map;
  tile_used = new->tile_used;
  nb_tile_used = new->nb_tile_used;
}

void clear_tile_cache() {
  int n,ta;
  if (nb_tile_used) {
    for (n=0; n<nb_tile_used; n++) {
      ta = tile_used[n];
      tile_cache[ta] = NULL;
    }
    nb_tile_used = 0;
  }
}

#define map_8bpp( FUNC ) \
void FUNC(UINT8 *dummy,int x, int y, int ta) { \
  if (nb_tile_used < MAX_TILES_CACHE) { \
    UINT8 *addr = GameBitmap->line[y]+x; \
    tile_used[nb_tile_used++] = ta; \
    tile_cache[ta] = addr; \
  }  \
}

map_8bpp(add_tile_cache_8)
map_8bpp(add_tile_cache_8_FlipX)
map_8bpp(add_tile_cache_8_FlipY)
map_8bpp(add_tile_cache_8_FlipXY)

#define map_16bpp( FUNC ) \
void FUNC(UINT8 *dummy,int x, int y, int ta) { \
  if (nb_tile_used < MAX_TILES_CACHE) { \
    UINT8 *addr = GameBitmap->line[y]+x*2; \
    tile_used[nb_tile_used++] = ta; \
    tile_cache[ta] = addr; \
  } \
}

map_16bpp(add_tile_cache_16)
map_16bpp(add_tile_cache_16_FlipX)
map_16bpp(add_tile_cache_16_FlipY)
map_16bpp(add_tile_cache_16_FlipXY)

#define map_32bpp( FUNC ) \
void FUNC(UINT8 *dummy,int x, int y, int ta) { \
  if (nb_tile_used < MAX_TILES_CACHE) { \
    UINT8 *addr = GameBitmap->line[y]+x*4; \
    tile_used[nb_tile_used++] = ta; \
    tile_cache[ta] = addr; \
  } \
}

map_32bpp(add_tile_cache_32)
map_32bpp(add_tile_cache_32_FlipX)
map_32bpp(add_tile_cache_32_FlipY)
map_32bpp(add_tile_cache_32_FlipXY)
