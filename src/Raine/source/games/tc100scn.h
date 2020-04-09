
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*             tc0100scn: TAITO SCREEN LAYER CHIP (BG0/BG1/FG0)               */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

#define MAX_CHIP		2		// F1-System has 2 chips

#define SCN_BG0			0		// Layer type values
#define SCN_BG1			0
#define SCN_FG0			1
#define SCN_FG0_SCROLL		2
#define SCN_FG0_SCROLL_2	3

int tc0100scn_layer_count;			// Init this to 0 each screen update.

typedef struct TC0100SCN_LAYER			// Information about 1 layer
{
   UINT8 *RAM;					// Layer RAM address
   UINT8 *GFX;					// Layer GFX address
   UINT8 *SCR;					// Layer SCROLL RAM address
   UINT8 *MASK;					// Layer GFX SOLID MASK address
   UINT32 type;					// Type of layer (BG0/BG1/FG0)
   UINT32 bmp_x,bmp_y;				// Game screen offset (32,32)
   UINT32 bmp_w,bmp_h;				// Game screen size (320,224)
   UINT32 tile_mask;				// mask for tile number
   UINT32 scr_x,scr_y;				// Scroll offset add (16,8)
} TC0100SCN_LAYER;

typedef struct TC0100SCN			// Information about 1 chip
{
   TC0100SCN_LAYER layer[3];			// BG0/BG1/FG0 layer data
   UINT16 ctrl;					// Layer control data
   UINT8 *RAM;
   UINT8 *GFX_FG0;
} TC0100SCN;

struct TC0100SCN tc0100scn[MAX_CHIP];

void render_tc0100scn_layer_mapped(int chip, int layer, int transp);

void render_tc0100scn_layer_mapped_r270(int chip, int layer);

void render_tc0100scn_layer_mapped_flipy(int chip, int layer);

/******************************************************************************/

UINT8 *GFX_FG0;
UINT8 *GFX_FG1;

void init_tc0100scn(int chip);

void tc0100scn_0_gfx_fg0_wb  (UINT32 addr, UINT8 data);
void tc0100scn_0_gfx_fg0_ww  (UINT32 addr, UINT16 data);
void tc0100scn_0_copy_gfx_fg0(UINT8 *src, UINT32 size);

void tc0100scn_1_gfx_fg0_wb  (UINT32 addr, UINT8 data);
void tc0100scn_1_gfx_fg0_ww  (UINT32 addr, UINT16 data);
void tc0100scn_1_copy_gfx_fg0(UINT8 *src, UINT32 size);

void tc0100scn_0_gfx_fg0_wb_r270  (UINT32 addr, UINT8 data);
void tc0100scn_0_gfx_fg0_ww_r270  (UINT32 addr, UINT16 data);
void tc0100scn_0_copy_gfx_fg0_r270(UINT8 *src, UINT32 size);
void tc0100scn_update_gfx_fg0(int chip);

/******************************************************************************/

#ifdef __cplusplus
}
#endif
