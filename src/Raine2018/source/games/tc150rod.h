
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                 tc0150rod: TAITO ROAD SCROLL EFFECT CHIP                   */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

typedef struct TC0150ROD			// Information about 1 chip
{
   UINT8 *RAM;					// RAM address
   UINT8 *GFX;					// GFX address
   UINT8 *PAL;					// PAL address (map rom)
   UINT32 bmp_x,bmp_y;				// Game screen offset (64,64)
   UINT32 bmp_w,bmp_h;				// Game screen size (320,224)
   UINT32 scr_x,scr_y;				// Scroll offset add (0,0)
} TC0150ROD;

struct TC0150ROD tc0150rod;

void tc0150rod_init_palette(void);

void tc0150rod_show_palette(void);

void tc0150rod_render(UINT32 start, UINT32 end);

void tc0150rod_render_flipy(UINT32 start, UINT32 end);

#ifdef __cplusplus
}
#endif
