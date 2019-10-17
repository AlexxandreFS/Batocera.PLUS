
#ifdef __cplusplus
extern "C" {
#endif
#ifndef TILE_PRIORITIES
#define TILE_PRIORITIES

/*
  These functions are intended to handle games with a "priority mess" : games where
  each sprites on a given tile can have a different priority.
  Drivers using this for now : cave, toaplan2, mcatadv

  The principle is not so hard : an array of priorities (first_tile) containing the list
  of sprites to draw for this priority. Then you just draw the priorities in order.
  This file does not contain the drawing function itself, because it's dependant on the
  driver : 8x8, 16x16, optional zoom and so on : driver specific.

  The idea here is to use a pre-allocated array of TILE_Q instead of allocating each
  element by new (c++) or malloc, which would be way too slow for what we want.
  The size of this array is given by MAX_TILES below.
*/

#define MAX_PRI         32              // 32 levels of priority

#define MAX_TILES       0x8000          // 0x4000*0x14=0xA0000 (640kb)

struct TILE_Q
{
   UINT32 tile;                          // Tile number
   INT16 x,y;                           // X,Y position
   UINT8 *map;                          // Colour map data
   UINT32 flip;                          // Flip X/Y Axis
  // These 4 are optional : size and zoom when needed
   UINT16 ww,hh;
   UINT16 zoomx,zoomy;
   struct TILE_Q *next;                 // Next item with equal priority
};

struct TILE_Q *last_tile;               // last tile in use
struct TILE_Q *next_tile[MAX_PRI];      // next tile for each priority
struct TILE_Q *first_tile[MAX_PRI];     // first tile for each priority

UINT32 tile_start;

static DEF_INLINE void QueueTile(int tile, int x, int y, UINT8 *map, UINT8 flip, int pri)
{
   struct TILE_Q *curr_tile;

   curr_tile = next_tile[pri];

   curr_tile->tile = tile+tile_start;
   curr_tile->x    = x;
   curr_tile->y    = y;
   curr_tile->map  = map;
   curr_tile->flip = flip;
   curr_tile->next = last_tile;

   next_tile[pri]  = last_tile;
   last_tile       = last_tile+1;
}

/* Same thing, but with the the added sizes parameters */
static DEF_INLINE void QueueTileSize(UINT32 tile, int x, int y, UINT8 *map, UINT8 flip, UINT32 pri,UINT16 ww,UINT16 hh)
{
   struct TILE_Q *curr_tile;
   curr_tile = next_tile[pri];

   curr_tile->tile = tile;
   curr_tile->x    = x;
   curr_tile->y    = y;
   curr_tile->map  = map;
   curr_tile->flip = flip;
   curr_tile->next = last_tile;
   curr_tile->ww   = ww;
   curr_tile->hh   = hh;

   next_tile[pri]  = last_tile;
   last_tile       = last_tile+1;
}

/* And with the zoom parameters */
static DEF_INLINE void QueueTileZoom(UINT32 tile, int x, int y, UINT8 *map, UINT8 flip, UINT32 pri,UINT16 ww,UINT16 hh,UINT16 zoomx, UINT16 zoomy)
{
   struct TILE_Q *curr_tile;
   curr_tile = next_tile[pri];

   curr_tile->tile = tile;
   curr_tile->x    = x;
   curr_tile->y    = y;
   curr_tile->map  = map;
   curr_tile->flip = flip;
   curr_tile->next = last_tile;
   curr_tile->ww   = ww;
   curr_tile->hh   = hh;
   curr_tile->zoomx= zoomx;
   curr_tile->zoomy= zoomy;

   next_tile[pri]  = last_tile;
   last_tile       = last_tile+1;
}

void ClearTileQueue(void);
void TerminateTileQueue(void);
int init_tilequeue();

extern BITMAP *pbitmap;

void init_pbitmap();

#endif

#ifdef __cplusplus
}
#endif
