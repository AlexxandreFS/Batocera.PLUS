
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                 tc0002obj: TAITO OBJECT LAYER CHIP (OBJ)                   */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

typedef struct TC0002OBJ			// Information about 1 chip
{
   UINT8 *RAM;					// Layer RAM address
   UINT8 *GFX;					// Layer GFX address
   UINT8 *MASK;					// Layer GFX SOLID MASK address
   UINT32 tile_mask;				// mask for tile number
   int bmp_x,bmp_y;				// Game screen offset (32,32)
   int bmp_w,bmp_h;				// Game screen size (320,224)
   int ofs_x,ofs_y;				// Scroll offset add (0,-8)
   UINT16 ctrl;					// color/pri control
} TC0002OBJ;

struct TC0002OBJ tc0002obj;

void render_tc0002obj_mapped(void);

void render_tc0002obj_mapped_r270(void);

#define TC0002OBJ_CONV_CTRL(src)                   \
   ( ((src & 0x01) << 13) | ((src & 0xE0) >> 3) ); \


#ifdef __cplusplus
}
#endif
