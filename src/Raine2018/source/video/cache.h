#ifndef video_cache_h
#define video_cache_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  UINT8 **tile_cache;
  UINT8 **cache_map;
  UINT32 *tile_used;
  UINT16 nb_tile_used;
} cache_data;

extern UINT8 **tile_cache,**cache_map;

void clear_tile_cache();
void init_tile_cache();
void init_tile_cachex4();

void new_tile_cache(cache_data *old);
void new_tile_cachex4(cache_data *old);
void switch_cache(cache_data *old, cache_data *);

void add_tile_cache_8(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_8_FlipX(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_8_FlipY(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_8_FlipXY(UINT8 *dummy,int x, int y, int ta);

void add_tile_cache_16(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_16_FlipX(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_16_FlipY(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_16_FlipXY(UINT8 *dummy,int x, int y, int ta);

void add_tile_cache_32(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_32_FlipX(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_32_FlipY(UINT8 *dummy,int x, int y, int ta);
void add_tile_cache_32_FlipXY(UINT8 *dummy,int x, int y, int ta);


#ifdef __cplusplus
}
#endif
#endif

