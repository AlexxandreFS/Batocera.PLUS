
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                  tc0003vcu: TAITO VIDEO CHIP (F3-SYSTEM)                   */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

int tc0003vcu_layer_count;			// Init this to 0 each screen update.

typedef struct TC0003VCU			// Information about 1 chip
{
   UINT8 *RAM;					// Layer RAM address
   mapper_direct *mapper;			// Colour mapper
   UINT32 bmp_x,bmp_y;				// Game screen offset (64,64)
   UINT32 bmp_w,bmp_h;				// Game screen size (320,224)
   UINT32 scr_x,scr_y;				// Scroll offset add (0,0)
} TC0003VCU;

struct TC0003VCU tc0003vcu;

void f3video_render_fg0(void);
void f3video_render_fg0_r180(void);
void f3video_render_fg0_r270(void);

void f3video_render_fg0_new(void);

// gfx are written byteswapped

void f3video_render_fg0_gfx2(void);

#ifdef __cplusplus
}
#endif
