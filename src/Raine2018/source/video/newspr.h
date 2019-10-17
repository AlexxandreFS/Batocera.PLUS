
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                            RAINE TILE DRAWING                              */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

#include "spr8x8.h"
#include "spr16x8.h"
#include "spr16x16.h"
#include "spr32x32.h"

#include "move.h"
#include "cache.h"

#include "spp8x8.h"

#include "str6x8.h"
#include "mapped_alpha.h"

typedef void text_func(char *STR, int x, int y, UINT32 cmap);
extern text_func *textout_fast;

typedef void draw_mapped_zoom_xy_func(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
typedef void draw_mapped_func(UINT8 *SPR, int x, int y, UINT8 *cmap);

typedef void draw_pixel_func(UINT8 *line, int xoff, UINT32 *pal, int color);

extern draw_pixel_func *raine_put_pixel;


// 8xh functions
typedef void add_move_func(UINT8 *dummy, int x, int y, int ta);
typedef void drawh_mapped_func(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
typedef void draw_func(UINT8 *SPR, int x, int y, UINT8 cmap);

/***************************************/
/* These Flip functions tables are built automatically by MAKE_ROT_JUMP_16 *
 * You DON'T have to declare anything in newspr.c except this. *
 * But you have to call make_rot_jump or make_rot_jump_16 and init_jump_table ! */

extern draw_func *Draw8x8_8_Flip_Rot[4];

#define Draw8x8_8_flip_Rot(a, b, c, d, e) (*Draw8x8_8_Flip_Rot[e])(a, b, c, d)

#define Draw8x8_8_Rot(a, b, c, d)        (*Draw8x8_8_Flip_Rot[0])(a, b, c, d)
#define Draw8x8_8_FlipY_Rot(a, b, c, d)  (*Draw8x8_8_Flip_Rot[1])(a, b, c, d)
#define Draw8x8_8_FlipX_Rot(a, b, c, d)  (*Draw8x8_8_Flip_Rot[2])(a, b, c, d)
#define Draw8x8_8_FlipXY_Rot(a, b, c, d) (*Draw8x8_8_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw8x8_Trans_8_Flip_Rot[4];

#define Draw8x8_Trans_8_flip_Rot(a, b, c, d, e) (*Draw8x8_Trans_8_Flip_Rot[e])(a, b, c, d)

#define Draw8x8_Trans_8_Rot(a, b, c, d)        (*Draw8x8_Trans_8_Flip_Rot[0])(a, b, c, d)
#define Draw8x8_Trans_8_FlipY_Rot(a, b, c, d)  (*Draw8x8_Trans_8_Flip_Rot[1])(a, b, c, d)
#define Draw8x8_Trans_8_FlipX_Rot(a, b, c, d)  (*Draw8x8_Trans_8_Flip_Rot[2])(a, b, c, d)
#define Draw8x8_Trans_8_FlipXY_Rot(a, b, c, d) (*Draw8x8_Trans_8_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw16x16_Flip_Rot[4];

#define Draw16x16_flip_Rot(a, b, c, d, e) (*Draw16x16_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Rot(a, b, c, d)        (*Draw16x16_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_FlipY_Rot(a, b, c, d)  (*Draw16x16_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_FlipX_Rot(a, b, c, d)  (*Draw16x16_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_FlipXY_Rot(a, b, c, d) (*Draw16x16_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw16x16_Trans_Flip_Rot[4];

#define Draw16x16_Trans_flip_Rot(a, b, c, d, e) (*Draw16x16_Trans_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Trans_Rot(a, b, c, d)        (*Draw16x16_Trans_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Trans_FlipY_Rot(a, b, c, d)  (*Draw16x16_Trans_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Trans_FlipX_Rot(a, b, c, d)  (*Draw16x16_Trans_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Trans_FlipXY_Rot(a, b, c, d) (*Draw16x16_Trans_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw32x32_Flip_Rot[4];

#define Draw32x32_flip_Rot(a, b, c, d, e) (*Draw32x32_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Rot(a, b, c, d)        (*Draw32x32_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_FlipY_Rot(a, b, c, d)  (*Draw32x32_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_FlipX_Rot(a, b, c, d)  (*Draw32x32_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_FlipXY_Rot(a, b, c, d) (*Draw32x32_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw32x32_Trans_Flip_Rot[4];

#define Draw32x32_Trans_flip_Rot(a, b, c, d, e) (*Draw32x32_Trans_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Trans_Rot(a, b, c, d)        (*Draw32x32_Trans_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Trans_FlipY_Rot(a, b, c, d)  (*Draw32x32_Trans_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Trans_FlipX_Rot(a, b, c, d)  (*Draw32x32_Trans_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Trans_FlipXY_Rot(a, b, c, d) (*Draw32x32_Trans_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw32x32_Trans_Alpha50_16_Flip_Rot[4];

#define Draw32x32_Trans_Alpha50_16_flip_Rot(a, b, c, d, e) (*Draw32x32_Trans_Alpha50_16_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Trans_Alpha50_16_Rot(a, b, c, d)        (*Draw32x32_Trans_Alpha50_16_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Trans_Alpha50_16_FlipY_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha50_16_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Trans_Alpha50_16_FlipX_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha50_16_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Trans_Alpha50_16_FlipXY_Rot(a, b, c, d) (*Draw32x32_Trans_Alpha50_16_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw32x32_Trans_Alpha50_32_Flip_Rot[4];

#define Draw32x32_Trans_Alpha50_32_flip_Rot(a, b, c, d, e) (*Draw32x32_Trans_Alpha50_32_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Trans_Alpha50_32_Rot(a, b, c, d)        (*Draw32x32_Trans_Alpha50_32_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Trans_Alpha50_32_FlipY_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha50_32_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Trans_Alpha50_32_FlipX_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha50_32_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Trans_Alpha50_32_FlipXY_Rot(a, b, c, d) (*Draw32x32_Trans_Alpha50_32_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw32x32_Trans_Alpha_16_Flip_Rot[4];

#define Draw32x32_Trans_Alpha_16_flip_Rot(a, b, c, d, e) (*Draw32x32_Trans_Alpha_16_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Trans_Alpha_16_Rot(a, b, c, d)        (*Draw32x32_Trans_Alpha_16_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Trans_Alpha_16_FlipY_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha_16_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Trans_Alpha_16_FlipX_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha_16_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Trans_Alpha_16_FlipXY_Rot(a, b, c, d) (*Draw32x32_Trans_Alpha_16_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw32x32_Trans_Alpha_32_Flip_Rot[4];

#define Draw32x32_Trans_Alpha_32_flip_Rot(a, b, c, d, e) (*Draw32x32_Trans_Alpha_32_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Trans_Alpha_32_Rot(a, b, c, d)        (*Draw32x32_Trans_Alpha_32_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Trans_Alpha_32_FlipY_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha_32_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Trans_Alpha_32_FlipX_Rot(a, b, c, d)  (*Draw32x32_Trans_Alpha_32_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Trans_Alpha_32_FlipXY_Rot(a, b, c, d) (*Draw32x32_Trans_Alpha_32_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw16x16_Mask_Trans_Flip_Rot[4];

#define Draw16x16_Mask_Trans_flip_Rot(a, b, c, d, e) (*Draw16x16_Mask_Trans_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Mask_Trans_Rot(a, b, c, d)        (*Draw16x16_Mask_Trans_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Mask_Trans_FlipY_Rot(a, b, c, d)  (*Draw16x16_Mask_Trans_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Mask_Trans_FlipX_Rot(a, b, c, d)  (*Draw16x16_Mask_Trans_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Mask_Trans_FlipXY_Rot(a, b, c, d) (*Draw16x16_Mask_Trans_Flip_Rot[3])(a, b, c, d)

extern draw_func *Draw16x16_Mask_Flip_Rot[4];

#define Draw16x16_Mask_flip_Rot(a, b, c, d, e) (*Draw16x16_Mask_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Mask_Rot(a, b, c, d)        (*Draw16x16_Mask_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Mask_FlipY_Rot(a, b, c, d)  (*Draw16x16_Mask_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Mask_FlipX_Rot(a, b, c, d)  (*Draw16x16_Mask_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Mask_FlipXY_Rot(a, b, c, d) (*Draw16x16_Mask_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw8x8_Mapped_Flip_Rot[4];

#define Draw8x8_Mapped_flip_Rot(a, b, c, d, e) (*Draw8x8_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw8x8_Mapped_Rot(a, b, c, d)        (*Draw8x8_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw8x8_Mapped_FlipY_Rot(a, b, c, d)  (*Draw8x8_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw8x8_Mapped_FlipX_Rot(a, b, c, d)  (*Draw8x8_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw8x8_Mapped_FlipXY_Rot(a, b, c, d) (*Draw8x8_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw8x8_Trans_Mapped_Flip_Rot[4];

#define Draw8x8_Trans_Mapped_flip_Rot(a, b, c, d, e) (*Draw8x8_Trans_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw8x8_Trans_Mapped_Rot(a, b, c, d)        (*Draw8x8_Trans_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw8x8_Trans_Mapped_FlipY_Rot(a, b, c, d)  (*Draw8x8_Trans_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw8x8_Trans_Mapped_FlipX_Rot(a, b, c, d)  (*Draw8x8_Trans_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw8x8_Trans_Mapped_FlipXY_Rot(a, b, c, d) (*Draw8x8_Trans_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw8x8_Trans_Packed_Mapped_Flip_Rot[4];

#define Draw8x8_Trans_Packed_Mapped_flip_Rot(a, b, c, d, e) (*Draw8x8_Trans_Packed_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw8x8_Trans_Packed_Mapped_Rot(a, b, c, d)        (*Draw8x8_Trans_Packed_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw8x8_Trans_Packed_Mapped_FlipY_Rot(a, b, c, d)  (*Draw8x8_Trans_Packed_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw8x8_Trans_Packed_Mapped_FlipX_Rot(a, b, c, d)  (*Draw8x8_Trans_Packed_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw8x8_Trans_Packed_Mapped_FlipXY_Rot(a, b, c, d) (*Draw8x8_Trans_Packed_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw8x8_Trans_Packed_Mapped_SwapWord_Flip_Rot[4];

#define Draw8x8_Trans_Packed_Mapped_SwapWord_flip_Rot(a, b, c, d, e) (*Draw8x8_Trans_Packed_Mapped_SwapWord_Flip_Rot[e])(a, b, c, d)

#define Draw8x8_Trans_Packed_Mapped_SwapWord_Rot(a, b, c, d)        (*Draw8x8_Trans_Packed_Mapped_SwapWord_Flip_Rot[0])(a, b, c, d)
#define Draw8x8_Trans_Packed_Mapped_SwapWord_FlipY_Rot(a, b, c, d)  (*Draw8x8_Trans_Packed_Mapped_SwapWord_Flip_Rot[1])(a, b, c, d)
#define Draw8x8_Trans_Packed_Mapped_SwapWord_FlipX_Rot(a, b, c, d)  (*Draw8x8_Trans_Packed_Mapped_SwapWord_Flip_Rot[2])(a, b, c, d)
#define Draw8x8_Trans_Packed_Mapped_SwapWord_FlipXY_Rot(a, b, c, d) (*Draw8x8_Trans_Packed_Mapped_SwapWord_Flip_Rot[3])(a, b, c, d)


extern draw_mapped_func *Draw16x16_Mapped_Flip_Rot[4];

#define Draw16x16_Mapped_flip_Rot(a, b, c, d, e) (*Draw16x16_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Mapped_Rot(a, b, c, d)        (*Draw16x16_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Mapped_FlipY_Rot(a, b, c, d)  (*Draw16x16_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Mapped_FlipX_Rot(a, b, c, d)  (*Draw16x16_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Mapped_FlipXY_Rot(a, b, c, d) (*Draw16x16_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw16x16_Trans_Mapped_Flip_Rot[4];

#define Draw16x16_Trans_Mapped_flip_Rot(a, b, c, d, e) (*Draw16x16_Trans_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Trans_Mapped_Rot(a, b, c, d)        (*Draw16x16_Trans_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Trans_Mapped_FlipY_Rot(a, b, c, d)  (*Draw16x16_Trans_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Trans_Mapped_FlipX_Rot(a, b, c, d)  (*Draw16x16_Trans_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Trans_Mapped_FlipXY_Rot(a, b, c, d) (*Draw16x16_Trans_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw16x16_Trans_Mapped_Alpha_Flip_Rot[4];

#define Draw16x16_Trans_Mapped_Alpha_flip_Rot(a, b, c, d, e) (*Draw16x16_Trans_Mapped_Alpha_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Trans_Mapped_Alpha_Rot(a, b, c, d)        (*Draw16x16_Trans_Mapped_Alpha_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Trans_Mapped_Alpha_FlipY_Rot(a, b, c, d)  (*Draw16x16_Trans_Mapped_Alpha_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Trans_Mapped_Alpha_FlipX_Rot(a, b, c, d)  (*Draw16x16_Trans_Mapped_Alpha_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Trans_Mapped_Alpha_FlipXY_Rot(a, b, c, d) (*Draw16x16_Trans_Mapped_Alpha_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw16x16_Mapped_Alpha_Flip_Rot[4];

#define Draw16x16_Mapped_Alpha_flip_Rot(a, b, c, d, e) (*Draw16x16_Mapped_Alpha_Flip_Rot[e])(a, b, c, d)

#define Draw16x16_Mapped_Alpha_Rot(a, b, c, d)        (*Draw16x16_Mapped_Alpha_Flip_Rot[0])(a, b, c, d)
#define Draw16x16_Mapped_Alpha_FlipY_Rot(a, b, c, d)  (*Draw16x16_Mapped_Alpha_Flip_Rot[1])(a, b, c, d)
#define Draw16x16_Mapped_Alpha_FlipX_Rot(a, b, c, d)  (*Draw16x16_Mapped_Alpha_Flip_Rot[2])(a, b, c, d)
#define Draw16x16_Mapped_Alpha_FlipXY_Rot(a, b, c, d) (*Draw16x16_Mapped_Alpha_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw16x8_Mapped_Flip_Rot[4];

#define Draw16x8_Mapped_flip_Rot(a, b, c, d, e) (*Draw16x8_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw16x8_Mapped_Rot(a, b, c, d)        (*Draw16x8_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw16x8_Mapped_FlipY_Rot(a, b, c, d)  (*Draw16x8_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw16x8_Mapped_FlipX_Rot(a, b, c, d)  (*Draw16x8_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw16x8_Mapped_FlipXY_Rot(a, b, c, d) (*Draw16x8_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw16x8_Trans_Mapped_Flip_Rot[4];

#define Draw16x8_Trans_Mapped_flip_Rot(a, b, c, d, e) (*Draw16x8_Trans_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw16x8_Trans_Mapped_Rot(a, b, c, d)        (*Draw16x8_Trans_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw16x8_Trans_Mapped_FlipY_Rot(a, b, c, d)  (*Draw16x8_Trans_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw16x8_Trans_Mapped_FlipX_Rot(a, b, c, d)  (*Draw16x8_Trans_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw16x8_Trans_Mapped_FlipXY_Rot(a, b, c, d) (*Draw16x8_Trans_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw32x32_Mapped_Flip_Rot[4];

#define Draw32x32_Mapped_flip_Rot(a, b, c, d, e) (*Draw32x32_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Mapped_Rot(a, b, c, d)        (*Draw32x32_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Mapped_FlipY_Rot(a, b, c, d)  (*Draw32x32_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Mapped_FlipX_Rot(a, b, c, d)  (*Draw32x32_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Mapped_FlipXY_Rot(a, b, c, d) (*Draw32x32_Mapped_Flip_Rot[3])(a, b, c, d)

extern draw_mapped_func *Draw32x32_Trans_Mapped_Flip_Rot[4];

#define Draw32x32_Trans_Mapped_flip_Rot(a, b, c, d, e) (*Draw32x32_Trans_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw32x32_Trans_Mapped_Rot(a, b, c, d)        (*Draw32x32_Trans_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw32x32_Trans_Mapped_FlipY_Rot(a, b, c, d)  (*Draw32x32_Trans_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw32x32_Trans_Mapped_FlipX_Rot(a, b, c, d)  (*Draw32x32_Trans_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw32x32_Trans_Mapped_FlipXY_Rot(a, b, c, d) (*Draw32x32_Trans_Mapped_Flip_Rot[3])(a, b, c, d)

// move functions

extern draw_mapped_func *Move8x8_Flip_Rot[4];

#define Move8x8_Rot(a, b, c, d)        (*Move8x8_Flip_Rot[0])(a, b, c, d)

extern add_move_func *add_tile_cache_Flip_Rot[4];

#define add_tile_cache_Rot(a,b,c,d) (*add_tile_cache_Flip_Rot[0])(a,b,c,d)

extern draw_mapped_zoom_xy_func *Draw16x16_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x8_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x8_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x8_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x8_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x8_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x8_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x8_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x8_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x8_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x8_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x8_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x8_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x8_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x8_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x8_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x8_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x8_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x8_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x8_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x8_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x8_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x8_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)


// 64x64 Mapped Sprites

void Draw64x64_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);
//16 bpp version
void Draw64x64_Mapped_16(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);
//32 bpp version
void Draw64x64_Mapped_32(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);

// Rot definition

extern draw_mapped_func *Draw64x64_Mapped_Flip_Rot[4];

#define Draw64x64_Mapped_flip_Rot(a, b, c, d, e) (*Draw64x64_Mapped_Flip_Rot[e])(a, b, c, d)

#define Draw64x64_Mapped_Rot(a, b, c, d)        (*Draw64x64_Mapped_Flip_Rot[0])(a, b, c, d)
#define Draw64x64_Mapped_FlipY_Rot(a, b, c, d)  (*Draw64x64_Mapped_Flip_Rot[1])(a, b, c, d)
#define Draw64x64_Mapped_FlipX_Rot(a, b, c, d)  (*Draw64x64_Mapped_Flip_Rot[2])(a, b, c, d)
#define Draw64x64_Mapped_FlipXY_Rot(a, b, c, d) (*Draw64x64_Mapped_Flip_Rot[3])(a, b, c, d)

// 64x64 Transparent Mapped Sprites

void Draw64x64_Trans_Mapped_8(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Trans_Mapped_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Trans_Mapped_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap);
void Draw64x64_Trans_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap);
// no 16bpp version (yet)
// no 32bpp version (yet)

// Specially for F3 System (pixel layer)

void Draw8xH_Trans_Packed_Mapped_8(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_8_FlipY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_8_FlipX(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_8_FlipXY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
//16 bpp version
void Draw8xH_Trans_Packed_Mapped_16(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_16_FlipY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_16_FlipX(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_16_FlipXY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
//32 bpp version
void Draw8xH_Trans_Packed_Mapped_32(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_32_FlipY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_32_FlipX(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);
void Draw8xH_Trans_Packed_Mapped_32_FlipXY(UINT8 *SPR, int x, int y, int height, UINT8 *cmap);

// Rot definition

extern drawh_mapped_func *Draw8xH_Trans_Packed_Mapped_Flip_Rot[4];

#define Draw8xH_Trans_Packed_Mapped_flip_Rot(a, b, c, d, e,f) (*Draw8xH_Trans_Packed_Mapped_Flip_Rot[f])(a, b, c, d,e)

#define Draw8xH_Trans_Packed_Mapped_Rot(a, b, c, d, e)        (*Draw8xH_Trans_Packed_Mapped_Flip_Rot[0])(a, b, c, d, e)
#define Draw8xH_Trans_Packed_Mapped_FlipY_Rot(a, b, c, d, e)  (*Draw8xH_Trans_Packed_Mapped_Flip_Rot[1])(a, b, c, d, e)
#define Draw8xH_Trans_Packed_Mapped_FlipX_Rot(a, b, c, d, e)  (*Draw8xH_Trans_Packed_Mapped_Flip_Rot[2])(a, b, c, d, e)
#define Draw8xH_Trans_Packed_Mapped_FlipXY_Rot(a, b, c, d, e) (*Draw8xH_Trans_Packed_Mapped_Flip_Rot[3])(a, b, c, d, e)

void init_newspr2asm();
void init_newspr2asm_16();
void init_newspr2asm_32();

void init_video_core(void);

/* A macro to draw an 8x8 sprite, testing solid, mapping palette, and even
 * checking clipping, this should have been done a few eons ago !
 * Used by buble boble driver only for now... */
#define drawspr_8x8_flip(layer,x,y,ta,color,flip)                 \
    if (gfx_solid[layer][ta]) /* No pixels; skip */               \
    {                                                             \
        MAP_PALETTE_MAPPED_NEW(                                   \
                color,                                            \
                16,                                               \
                map                                               \
                );                                                \
                                                                  \
                                                                  \
        if((x>current_game->video->border_size-8) &&              \
                (y>current_game->video->border_size-8) &&         \
                (x<current_game->video->border_size +             \
                 current_game->video->screen_x) &&                \
                (y<current_game->video->border_size +             \
                 current_game->video->screen_y))                  \
        {                                                         \
            if(gfx_solid[layer][ta]==1)                           \
            {        /* Some pixels; trans */                     \
                Draw8x8_Trans_Mapped_flip_Rot(&gfx[layer][ta<<6], \
                        x, y, map, flip);                         \
            } else {    /* all pixels; solid */                   \
                Draw8x8_Mapped_flip_Rot(&gfx[layer][ta<<6],       \
                               x, y, map, flip);                  \
                                                                  \
            }                                                     \
        }                                                         \
    }

#ifdef __cplusplus
}
#endif
