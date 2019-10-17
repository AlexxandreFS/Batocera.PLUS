
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                          RAINE 16x16 TILE ZOOMING                          */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

// These ones can zoom from x/y = [0..16] (ie. max size is normal: 16x16)

extern UINT8 zoom_1616_dat[(16+1)*16];	// [32+1][16] array
extern UINT8 zoom_1616r_dat[(16+1)*16];	// [32+1][16] array
extern UINT8 zoom_1632_dat[33*32];	// [32+1][32] array
extern UINT8 zoom_1632r_dat[33*32];	// [32+1][32] array
extern UINT8 zoom_1664_dat[65*64];	// [64+1][64] array
extern UINT8 zoom_1664r_dat[65*64];	// [64+1][64] array

void init_16x16_zoom(void);
UINT8 *make_16x16_zoom_ofs_type1(void);
UINT8 *make_16x16_zoom_ofs_type1z(void);
UINT8 *make_16x16_zoom_ofs_type1zz(void);

#undef ARG_ZOOM
#define ARG_ZOOM UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y
void Draw16x16_Trans_Mapped_ZoomXY_8       (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_8_FlipY (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_8_FlipX (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM);

void Draw16x16_Mapped_ZoomXY_8       (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_8_FlipY (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_8_FlipX (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM);

void Draw16x16_Trans_Mapped_ZoomXY_Alpha_8       (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_8_FlipY (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_8_FlipX (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_8_FlipXY(ARG_ZOOM);

void Draw16x16_Mapped_ZoomXY_Alpha_8       (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_8_FlipY (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_8_FlipX (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_8_FlipXY(ARG_ZOOM);

#if 0
// The useless direct mapping + zoom functions
void Draw16x16_Trans_ZoomXY       (UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
void Draw16x16_Trans_ZoomXY_FlipY (UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
void Draw16x16_Trans_ZoomXY_FlipX (UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
void Draw16x16_Trans_ZoomXY_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);

void Draw16x16_ZoomXY       (UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
void Draw16x16_ZoomXY_FlipY (UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
void Draw16x16_ZoomXY_FlipX (UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
void Draw16x16_ZoomXY_FlipXY(UINT8 *SPR, int x, int y, UINT8 cmap, int zoom_x, int zoom_y);
#endif

// These ones can zoom from x/y = [0..32] (ie. max size is double: 32x32)

void init_16x16_zoom_32(void);
UINT8 *make_16x16_zoom_ofs_type2(void);

void Draw16x16_32_Trans_Mapped_ZoomXY_8     (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_8_FlipY (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_8_FlipX (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM);

void Draw16x16_32_Mapped_ZoomXY_8       (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_8_FlipY (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_8_FlipX (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM);

// These ones can zoom from x/y = [0..32] (ie. max size is quaruple: 64x64)

void init_16x16_zoom_64(void);
UINT8 *make_16x16_zoom_ofs_type3(void);

void Draw16x16_64_Trans_Mapped_ZoomXY_8       (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_8_FlipY (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_8_FlipX (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM);

void Draw16x16_64_Mapped_ZoomXY_8       (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_8_FlipY (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_8_FlipX (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM);

// 16bpp

void Draw16x16_Trans_Mapped_ZoomXY_16       (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_16_FlipY (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_16_FlipX (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM);

void Draw16x16_Mapped_ZoomXY_16       (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_16_FlipY (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_16_FlipX (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM);

void Draw16x16_Trans_Mapped_ZoomXY_Alpha_16       (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_16_FlipY (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_16_FlipX (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_16_FlipXY(ARG_ZOOM);

void Draw16x16_Mapped_ZoomXY_Alpha_16       (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_16_FlipY (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_16_FlipX (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_16_FlipXY(ARG_ZOOM);

void Draw16x16_32_Trans_Mapped_ZoomXY_16       (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_16_FlipY (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_16_FlipX (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM);

void Draw16x16_32_Mapped_ZoomXY_16       (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_16_FlipY (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_16_FlipX (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM);

// These ones can zoom from x/y = [0..32] (ie. max size is quaruple: 32x32)

void Draw16x16_64_Trans_Mapped_ZoomXY_16       (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_16_FlipY (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_16_FlipX (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM);

void Draw16x16_64_Mapped_ZoomXY_16       (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_16_FlipY (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_16_FlipX (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM);

// 32 bpp

void Draw16x16_Trans_Mapped_ZoomXY_32       (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_32_FlipY (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_32_FlipX (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM);

void Draw16x16_Mapped_ZoomXY_32       (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_32_FlipY (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_32_FlipX (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM);

void Draw16x16_Trans_Mapped_ZoomXY_Alpha_32       (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_32_FlipY (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_32_FlipX (ARG_ZOOM);
void Draw16x16_Trans_Mapped_ZoomXY_Alpha_32_FlipXY(ARG_ZOOM);

void Draw16x16_Mapped_ZoomXY_Alpha_32       (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_32_FlipY (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_32_FlipX (ARG_ZOOM);
void Draw16x16_Mapped_ZoomXY_Alpha_32_FlipXY(ARG_ZOOM);

void Draw16x16_32_Trans_Mapped_ZoomXY_32       (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_32_FlipY (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_32_FlipX (ARG_ZOOM);
void Draw16x16_32_Trans_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM);

void Draw16x16_32_Mapped_ZoomXY_32       (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_32_FlipY (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_32_FlipX (ARG_ZOOM);
void Draw16x16_32_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM);

// These ones can zoom from x/y = [0..32] (ie. max size is quaruple: 32x32)

void Draw16x16_64_Trans_Mapped_ZoomXY_32       (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_32_FlipY (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_32_FlipX (ARG_ZOOM);
void Draw16x16_64_Trans_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM);

void Draw16x16_64_Mapped_ZoomXY_32       (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_32_FlipY (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_32_FlipX (ARG_ZOOM);
void Draw16x16_64_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM);

// Rot of the above...

extern draw_mapped_zoom_xy_func *Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

// Alpha

extern draw_mapped_zoom_xy_func *Draw16x16_Trans_Mapped_ZoomXY_Alpha_Flip_Rot[4];

#define Draw16x16_Trans_Mapped_ZoomXY_Alpha_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_Trans_Mapped_ZoomXY_Alpha_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_Trans_Mapped_ZoomXY_Alpha_Rot(a, b, c, d, e, f)        (*Draw16x16_Trans_Mapped_ZoomXY_Alpha_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_Alpha_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_Trans_Mapped_ZoomXY_Alpha_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_Alpha_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_Trans_Mapped_ZoomXY_Alpha_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_Trans_Mapped_ZoomXY_Alpha_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_Trans_Mapped_ZoomXY_Alpha_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_Mapped_ZoomXY_Alpha_Flip_Rot[4];

#define Draw16x16_Mapped_ZoomXY_Alpha_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_Mapped_ZoomXY_Alpha_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_Mapped_ZoomXY_Alpha_Rot(a, b, c, d, e, f)        (*Draw16x16_Mapped_ZoomXY_Alpha_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_Alpha_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_Mapped_ZoomXY_Alpha_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_Alpha_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_Mapped_ZoomXY_Alpha_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_Mapped_ZoomXY_Alpha_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_Mapped_ZoomXY_Alpha_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_32_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_32_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_32_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_32_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_32_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_32_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_32_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_32_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_32_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_32_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_32_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_32_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_32_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_32_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_32_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_32_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_32_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_32_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_32_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_32_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_32_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_32_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_64_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_64_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_64_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_64_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_64_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_64_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_64_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_64_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_64_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_64_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_64_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define Draw16x16_64_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g) (*Draw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw16x16_64_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f)        (*Draw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw16x16_64_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f)  (*Draw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw16x16_64_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f)  (*Draw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw16x16_64_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f) (*Draw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f)

// pdraw

void pdraw16x16_Trans_Mapped_ZoomXY_8       (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_8_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_8_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_Mapped_ZoomXY_8       (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_8_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_8_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM, int pri);

// 16bpp

void pdraw16x16_Trans_Mapped_ZoomXY_16       (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_16_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_16_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_Mapped_ZoomXY_16       (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_16_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_16_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM, int pri);

// 32bpp

void pdraw16x16_Trans_Mapped_ZoomXY_32       (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_32_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_32_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_Trans_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_Mapped_ZoomXY_32       (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_32_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_32_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM, int pri);

  // pdraw 64

void pdraw16x16_64_Trans_Mapped_ZoomXY_8       (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_8_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_8_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_64_Mapped_ZoomXY_8       (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_8_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_8_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_8_FlipXY(ARG_ZOOM, int pri);

// 16bpp

void pdraw16x16_64_Trans_Mapped_ZoomXY_16       (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_16_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_16_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_64_Mapped_ZoomXY_16       (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_16_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_16_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_16_FlipXY(ARG_ZOOM, int pri);

// 32bpp

void pdraw16x16_64_Trans_Mapped_ZoomXY_32       (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_32_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_32_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_64_Mapped_ZoomXY_32       (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_32_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_32_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_ZoomXY_32_FlipXY(ARG_ZOOM, int pri);

  // and finally, the _back version

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8       (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_8_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_64_Mapped_back_ZoomXY_8       (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_8_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_8_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_8_FlipXY(ARG_ZOOM, int pri);

// 16bpp

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_16       (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_16_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_16_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_16_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_64_Mapped_back_ZoomXY_16       (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_16_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_16_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_16_FlipXY(ARG_ZOOM, int pri);

// 32bpp

void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32       (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Trans_Mapped_back_ZoomXY_32_FlipXY(ARG_ZOOM, int pri);

void pdraw16x16_64_Mapped_back_ZoomXY_32       (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_32_FlipY (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_32_FlipX (ARG_ZOOM, int pri);
void pdraw16x16_64_Mapped_back_ZoomXY_32_FlipXY(ARG_ZOOM, int pri);

  // Rot definitions
// pdraw zoom 16

typedef void draw_mapped_zoom_xy_func_pri(ARG_ZOOM, int pri);

extern draw_mapped_zoom_xy_func_pri *pdraw16x16_Mapped_ZoomXY_Flip_Rot[4];

#define pdraw16x16_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g, h) (*pdraw16x16_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f, h)

#define pdraw16x16_Mapped_ZoomXY_Rot(a, b, c, d, e, f, h)        (*pdraw16x16_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f, h)
#define pdraw16x16_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f, h)
#define pdraw16x16_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f, h)
#define pdraw16x16_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f, h) (*pdraw16x16_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f, h)

extern draw_mapped_zoom_xy_func_pri *pdraw16x16_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define pdraw16x16_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g, h) (*pdraw16x16_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f, h)

#define pdraw16x16_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f, h)        (*pdraw16x16_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f, h)
#define pdraw16x16_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f, h)
#define pdraw16x16_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f, h)
#define pdraw16x16_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f, h) (*pdraw16x16_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f, h)

  // pdraw, zoom 64

extern draw_mapped_zoom_xy_func_pri *pdraw16x16_64_Mapped_ZoomXY_Flip_Rot[4];

#define pdraw16x16_64_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g, h) (*pdraw16x16_64_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f, h)

#define pdraw16x16_64_Mapped_ZoomXY_Rot(a, b, c, d, e, f, h)        (*pdraw16x16_64_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f, h) (*pdraw16x16_64_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f, h)

extern draw_mapped_zoom_xy_func_pri *pdraw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[4];

#define pdraw16x16_64_Trans_Mapped_ZoomXY_flip_Rot(a, b, c, d, e, f, g, h) (*pdraw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f, h)

#define pdraw16x16_64_Trans_Mapped_ZoomXY_Rot(a, b, c, d, e, f, h)        (*pdraw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Trans_Mapped_ZoomXY_FlipY_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Trans_Mapped_ZoomXY_FlipX_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Trans_Mapped_ZoomXY_FlipXY_Rot(a, b, c, d, e, f, h) (*pdraw16x16_64_Trans_Mapped_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f, h)

  // back version

extern draw_mapped_zoom_xy_func_pri *pdraw16x16_64_Mapped_back_ZoomXY_Flip_Rot[4];

#define pdraw16x16_64_Mapped_back_ZoomXY_flip_Rot(a, b, c, d, e, f, g, h) (*pdraw16x16_64_Mapped_back_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f, h)

#define pdraw16x16_64_Mapped_back_ZoomXY_Rot(a, b, c, d, e, f, h)        (*pdraw16x16_64_Mapped_back_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Mapped_back_ZoomXY_FlipY_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Mapped_back_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Mapped_back_ZoomXY_FlipX_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Mapped_back_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Mapped_back_ZoomXY_FlipXY_Rot(a, b, c, d, e, f, h) (*pdraw16x16_64_Mapped_back_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f, h)

extern draw_mapped_zoom_xy_func_pri *pdraw16x16_64_Trans_Mapped_back_ZoomXY_Flip_Rot[4];

#define pdraw16x16_64_Trans_Mapped_back_ZoomXY_flip_Rot(a, b, c, d, e, f, g, h) (*pdraw16x16_64_Trans_Mapped_back_ZoomXY_Flip_Rot[g])(a, b, c, d, e, f, h)

#define pdraw16x16_64_Trans_Mapped_back_ZoomXY_Rot(a, b, c, d, e, f, h)        (*pdraw16x16_64_Trans_Mapped_back_ZoomXY_Flip_Rot[0])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Trans_Mapped_back_ZoomXY_FlipY_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Trans_Mapped_back_ZoomXY_Flip_Rot[1])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Trans_Mapped_back_ZoomXY_FlipX_Rot(a, b, c, d, e, f, h)  (*pdraw16x16_64_Trans_Mapped_back_ZoomXY_Flip_Rot[2])(a, b, c, d, e, f, h)
#define pdraw16x16_64_Trans_Mapped_back_ZoomXY_FlipXY_Rot(a, b, c, d, e, f, h) (*pdraw16x16_64_Trans_Mapped_back_ZoomXY_Flip_Rot[3])(a, b, c, d, e, f, h)

#ifdef __cplusplus
}
#endif
