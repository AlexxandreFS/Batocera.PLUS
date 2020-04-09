
#ifdef __cplusplus
extern "C" {
#endif
#include "deftypes.h"

// 64x64 Transparent Mapped Zoomed Sprites

void Init64x64_Table(UINT8 *TPOS);

void Draw64x64_Trans_Mapped_Zoom_8(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);

void Draw64x64_Trans_Mapped_Zoom_16(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);

void Draw64x64_Trans_Mapped_Zoom_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
void Draw64x64_Trans_Mapped_Zoom_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);

void Draw64x64_Mapped_Zoom2_8(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);

void Draw64x64_Trans_Mapped_Zoom2_8(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_8_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_8_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);

void Draw64x64_Mapped_Zoom2_16(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);

void Draw64x64_Trans_Mapped_Zoom2_16(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_16_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_16_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);

void Draw64x64_Mapped_Zoom2_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Mapped_Zoom2_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);

void Draw64x64_Trans_Mapped_Zoom2_32(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_32_FlipX(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_32_FlipY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);
void Draw64x64_Trans_Mapped_Zoom2_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoomx, int zoomy);

/***************************************/

typedef void draw_mapped_zoom_func(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom);
extern draw_mapped_zoom_func *Draw64x64_Trans_Mapped_Zoom_Flip_Rot[4];

#define Draw64x64_Trans_Mapped_Zoom_flip_Rot(a, b, c, d, e, g) (*Draw64x64_Trans_Mapped_Zoom_Flip_Rot[g])(a, b, c, d, e)
#define Draw64x64_Trans_Mapped_Zoom_Rot(a, b, c, d, e)        (*Draw64x64_Trans_Mapped_Zoom_Flip_Rot[0])(a, b, c, d, e)
#define Draw64x64_Trans_Mapped_Zoom_FlipY_Rot(a, b, c, d, e)  (*Draw64x64_Trans_Mapped_Zoom_Flip_Rot[1])(a, b, c, d, e)
#define Draw64x64_Trans_Mapped_Zoom_FlipX_Rot(a, b, c, d, e)  (*Draw64x64_Trans_Mapped_Zoom_Flip_Rot[2])(a, b, c, d, e)
#define Draw64x64_Trans_Mapped_Zoom_FlipXY_Rot(a, b, c, d, e) (*Draw64x64_Trans_Mapped_Zoom_Flip_Rot[3])(a, b, c, d, e)

extern draw_mapped_zoom_xy_func *Draw64x64_Trans_Mapped_Zoom2_Flip_Rot[4];

#define Draw64x64_Trans_Mapped_Zoom2_flip_Rot(a, b, c, d, e, f, g) (*Draw64x64_Trans_Mapped_Zoom2_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw64x64_Trans_Mapped_Zoom2_Rot(a, b, c, d, e, f)        (*Draw64x64_Trans_Mapped_Zoom2_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw64x64_Trans_Mapped_Zoom2_FlipY_Rot(a, b, c, d, e, f)  (*Draw64x64_Trans_Mapped_Zoom2_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw64x64_Trans_Mapped_Zoom2_FlipX_Rot(a, b, c, d, e, f)  (*Draw64x64_Trans_Mapped_Zoom2_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw64x64_Trans_Mapped_Zoom2_FlipXY_Rot(a, b, c, d, e, f) (*Draw64x64_Trans_Mapped_Zoom2_Flip_Rot[3])(a, b, c, d, e, f)

extern draw_mapped_zoom_xy_func *Draw64x64_Mapped_Zoom2_Flip_Rot[4];

#define Draw64x64_Mapped_Zoom2_flip_Rot(a, b, c, d, e, f, g) (*Draw64x64_Mapped_Zoom2_Flip_Rot[g])(a, b, c, d, e, f)

#define Draw64x64_Mapped_Zoom2_Rot(a, b, c, d, e, f)        (*Draw64x64_Mapped_Zoom2_Flip_Rot[0])(a, b, c, d, e, f)
#define Draw64x64_Mapped_Zoom2_FlipY_Rot(a, b, c, d, e, f)  (*Draw64x64_Mapped_Zoom2_Flip_Rot[1])(a, b, c, d, e, f)
#define Draw64x64_Mapped_Zoom2_FlipX_Rot(a, b, c, d, e, f)  (*Draw64x64_Mapped_Zoom2_Flip_Rot[2])(a, b, c, d, e, f)
#define Draw64x64_Mapped_Zoom2_FlipXY_Rot(a, b, c, d, e, f) (*Draw64x64_Mapped_Zoom2_Flip_Rot[3])(a, b, c, d, e, f)

#ifdef __cplusplus
}
#endif
