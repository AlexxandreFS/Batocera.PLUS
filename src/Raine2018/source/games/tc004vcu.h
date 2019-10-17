
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*           tc0004vcu: TAITO VIDEO CHIP UNIT (H-SYSTEM/AIR-SYSTEM)           */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

int tc0004vcu_layer_count;			// Init this to 0 each screen update.

typedef struct TC0004VCU			// Information about 1 chip
{
   UINT8 *RAM;					// Chip RAM address
   UINT8 *GFX_BG0;				// GFX BG0 and BG1
   UINT8 *GFX_BG0_MSK;				// GFX MASK BG0 and BG1
   UINT8 *GFX_FG0;				// GFX FG0
   UINT32 tile_mask;				// Mask for tile number
   mapper_direct *mapper;			// Colour mapper
   UINT32 bmp_x,bmp_y;				// Game screen offset (64,64)
   UINT32 bmp_w,bmp_h;				// Game screen size (512,416)
   UINT32 scr_x,scr_y;				// Scroll offset add (0,0)
} TC0004VCU;

struct TC0004VCU tc0004vcu;

void tc0004vcu_init(void);

void tc0004vcu_gfx_fg0_a_wb(UINT32 addr, UINT8 data);
void tc0004vcu_gfx_fg0_a_ww(UINT32 addr, UINT16 data);
void tc0004vcu_gfx_fg0_b_wb(UINT32 addr, UINT8 data);
void tc0004vcu_gfx_fg0_b_ww(UINT32 addr, UINT16 data);

void tc0004vcu_render_bg0(void);
void tc0004vcu_render_bg1(void);
void tc0004vcu_render_fg0(void);
void tc0004vcu_render_obj(void);
//void tc0004vcu_render_obj_low(void);
//void tc0004vcu_render_obj_high(void);

#ifdef __cplusplus
}
#endif
