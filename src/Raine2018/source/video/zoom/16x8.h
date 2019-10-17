
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                          RAINE 16x8 TILE ZOOMING                           */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

// These ones can zoom from x/y = [0..16] (ie. max size is normal: 16x8)

void init_16x8_zoom(void);
UINT8 *make_16x8_zoom_ofs_type1(void);
UINT8 *make_16x8_zoom_ofs_type1z(void);
UINT8 *make_16x8_zoom_ofs_type1zz(void);

void Draw16x8_Trans_Mapped_ZoomXY_8       (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_8_FlipY (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_8_FlipX (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);

void Draw16x8_Mapped_ZoomXY_8       (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_8_FlipY (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_8_FlipX (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_8_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);

// 16 bpp
void Draw16x8_Trans_Mapped_ZoomXY_16       (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_16_FlipY (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_16_FlipX (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);

void Draw16x8_Mapped_ZoomXY_16       (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_16_FlipY (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_16_FlipX (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_16_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);

// 32 bpp
void Draw16x8_Trans_Mapped_ZoomXY_32       (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_32_FlipY (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_32_FlipX (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Trans_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);

void Draw16x8_Mapped_ZoomXY_32       (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_32_FlipY (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_32_FlipX (UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);
void Draw16x8_Mapped_ZoomXY_32_FlipXY(UINT8 *SPR, int x, int y, UINT8 *cmap, int zoom_x, int zoom_y);


#ifdef __cplusplus
}
#endif
