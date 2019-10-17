// Store Tiles in priority lists (good idea from Shark!).

#include "raine.h"
#include "newmem.h"
#include "priorities.h"
#include "games.h"
#include "spr16x16.h"

/*
  The priority bitmap :

  it's the way to address issues where we need priorities at the pixel level. 2 cases
  known until now : when the sprites'priority counts for the tiles priorities but not
  between sprites (gunbird, mcatadv), in this case we can't compare the sprites'priority
  with the tiles...
  And the complex video effects where you render a tile with priorities and then
  swap or zoom the lines of the tiles (in this case the priorities move with the lines
  and you need a priority bitmap to find them when rendering to screen - not used yet, but
  I will probably use this in the cave driver soon).

  The usage is simple : when rendering a tile with priority > 0, just call a _Mask_ function
  after the normal Draw function like this :
     Draw16x16_Trans_Mapped_Rot(&GFX[ta<<8],tile_ptr->x,tile_ptr->y,tile_ptr->map);
     Draw16x16_Mask_Trans_Rot(&GFX[ta<<8],tile_ptr->x,tile_ptr->y,my_pri);
   or even better, call combined pdraw_Mask function like this :
     pdraw16x16_Mask_Trans_Mapped_Rot(&GFX_BG[ta<<8], x, y, map,pri);
   Notice that the combined function tests the priority bitmap before drawing a pixel,
   so the pixel is drawn only if it has a priority >= what was there before.

  Then, render the sprites as if they had no priorities at all, but instead of using
  the normal Draw functions, use the pdraw functions which will test the priority bitmap
  before rendering the sprite : a pixel of the sprite is rendered only if the sprite's
  priority is >= the priority of this same pixel in the priority bitmap. So the pdraw
  function is called like this :
      pdraw16x16_Trans_Mapped_flip_Rot(&gfx_obj_b[tileno<<8], xx, y, map, 0, pri);
  The sprites are a little particular : the hardware for mcatadv and cave does not test
  the priority field of sprites between them, it counts only when comparing a sprite with
  a tile. So the pdraw function clears the corresponding pixel on the priority bitmap
  if the sprite can be drawn.
  This way if you draw a tile of priority 1
  then a sprite of priority 1 on top of it
  and finally a last sprite of priority 0 on top of everything, the sprite of priority 0
  will show because the sprite just before it cleared the priority bitmap.

  The priority bitmap must be created in the loading function of the driver by calling
  init_pbitmap. The destuction of the bitmap is automatic when the driver is unloaded.
  Don't forget to call clear_bitmap(pbitmap) for every drawn frame !

  Notice about rotation : we are OBLIGED to create _Rot functions for the mask functions
  and for the pdraw functions because the sprite memory is rotated before the game starts
  in raine to match the orientation of the screen...
  So we must handle the priority bitmap exactly like the screen, and it must be rotated too.

  This allows not to rotate sprites while drawing them on screen but here it makes our code
  much more complex than it should be. It would be nice to have something which makes a blit
  with rotation without loosing cpu power, but I guess that even if it exists it can't work
  everywhere, so we will be obliged to maintain these _Rot functions anyway.

*/

static struct TILE_Q *TileQueue;               // full list
BITMAP *pbitmap = NULL; // global, because used by the pdraw functions

void init_pbitmap() {
  // Prepare the mask functions to draw to the priority bitmap
  const VIDEO_INFO *vid = current_game->video;
  int x = vid->screen_x + vid->border_size*2, y = vid->screen_y+vid->border_size*2;
  int rotate = vid->flags ^ display_cfg.user_rotate;

  if (pbitmap)
    destroy_bitmap(pbitmap);
  if (rotate & 1) { // rotate 90, 270
    if (!(pbitmap = create_bitmap_ex(8,y,x))) return;
  } else {
    if (!(pbitmap = create_bitmap_ex(8,x,y))) return;
  }
  init_spr16x16asm_mask(pbitmap);
}

int init_tilequeue() {
  if(!(TileQueue = (struct TILE_Q *) AllocateMem(sizeof(struct TILE_Q)*MAX_TILES)))return 0;
  return 1;
}

void TerminateTileQueue(void)
{
   int ta;
   struct TILE_Q *curr_tile;

   for(ta=0; ta<MAX_PRI; ta++){

      curr_tile = next_tile[ta];

      curr_tile->next = NULL;

   }
}

void ClearTileQueue(void)
{
   int ta;

   last_tile = TileQueue;

   for(ta=0; ta<MAX_PRI; ta++){
      first_tile[ta] = last_tile;
      next_tile[ta]  = last_tile;
      last_tile      = last_tile+1;
   }
}
