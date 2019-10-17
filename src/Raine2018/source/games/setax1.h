
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*        SETA X1-001A/002A/006/004/003: SETA & TAITO VIDEO HARDWARE          */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

typedef struct SETA_X1				// Information about 1 chip
{
   UINT8 *RAM_A;				// VIDEO RAM A
   UINT8 *RAM_B;				// VIDEO RAM B
   UINT8 *GFX;					// GFX TILES
   UINT8 *MASK;					// GFX MASK DATA
   UINT32 tile_mask;				// Last tile number
   UINT32 bmp_x,bmp_y;				// Game screen offset (32,32)
   UINT32 bmp_w,bmp_h;				// Game screen size (356,240)
   UINT32 scr_x,scr_y;				// Scroll offset add (0,0)
} SETA_X1;

struct SETA_X1 seta_x1;

void render_seta_x1_68000(void);

void render_seta_x1_z80(void);

#ifdef __cplusplus
}
#endif
