
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                  tc0006vcu: TAITO VIDEO CHIP (F3-SYSTEM)                   */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

int tc0006vcu_layer_count;

typedef struct TC0006VCU			// Information about 1 chip
{
   UINT8 *RAM;					// video ram
   UINT8 *RAM_SCR;				// ctrl ram
   UINT8 *GFX_FG;				//
   UINT8 *GFX_FG_MASK;				//
   UINT8 *GFX_BG;				//
   UINT8 *GFX_BG_MASK;				//
   UINT32 tile_mask;                             //
   mapper_direct *mapper;			// Colour mapper
   UINT32 bmp_x,bmp_y;				// Game screen offset (64,64)
   UINT32 bmp_w,bmp_h;				// Game screen size (320,224)
   UINT32 scr_x[5];				//
   UINT32 scr_y[5];				//
   UINT32 pal_ofs;				//
} TC0006VCU;

struct TC0006VCU tc0006vcu;

void init_tc0006vcu(void);

void debug_tc0006vcu(void);

void tc0006vcu_gfx_fg0_wb(UINT32 addr, UINT8 data);
void tc0006vcu_gfx_fg0_ww(UINT32 addr, UINT16 data);

void tc0006vcu_render_layer(int layer);
void tc0006vcu_render_layer_1024(int layer);
void tc0006vcu_render_fg0(void);

#ifdef __cplusplus
}
#endif
