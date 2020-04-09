
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                  tc0180vcu: TAITO VIDEO CHIP (B-SYSTEM)                    */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

int tc0180vcu_layer_count;			// Init this to 0 each screen update.

typedef struct TC0180VCU			// Information about 1 chip
{
   UINT8 *RAM;					// Layer RAM address
   UINT8 *GFX_BG0;				// GFX BG0 and BG1
   UINT8 *GFX_BG0_MSK;				// GFX MASK BG0 and BG1
   UINT8 *GFX_BG2;				// GFX BG2
   UINT8 *GFX_BG2_MSK;				// GFX MASK BG2
   UINT32 tile_mask;				// Mask for tile number
   UINT32 bmp_x,bmp_y;				// Game screen offset (32,32)
   UINT32 bmp_w,bmp_h;				// Game screen size (320,224)
   UINT32 scr_x,scr_y;				// Scroll offset add (0,16)
   UINT8 col_mask;				//
   UINT8 col_bank[4];				//
   UINT8 *RAM_2;				// Further RAM address
} TC0180VCU;

struct TC0180VCU tc0180vcu;

void vcu_make_col_bankmap(UINT8 mask, UINT8 ofs_0, UINT8 ofs_1, UINT8 ofs_2, UINT8 ofs_3);

void vcu_debug_info(void);

void vcu_render_bg0(void);
void vcu_render_bg1(void);
void vcu_render_bg2(void);
void vcu_render_obj(UINT32 num);

void vcu_render_bg0_r270(void);
void vcu_render_bg1_r270(void);
void vcu_render_bg2_r270(void);
void vcu_render_obj_r270(int pri);
void vcu_render_ryujin_bg(int bg, int pri);

/*

video interface

*/

extern struct VIDEO_INFO b_system_video;
extern struct VIDEO_INFO b_system_r180_video;

void draw_b_system(void);

#ifdef __cplusplus
}
#endif
