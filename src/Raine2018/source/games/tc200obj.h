
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                 tc0200obj: TAITO OBJECT LAYER CHIP (F2/F3 SYSTEM)          */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

typedef struct TC0200OBJ			// Information about 1 chip
{
   UINT8 *RAM;					// Layer RAM address
   UINT8 *RAM_B;				// Layer RAM address (double buffer)
   UINT8 *GFX;					// Layer GFX address
   UINT8 *MASK;					// Layer GFX SOLID MASK address
   UINT32 tile_mask;				// mask for tile number
   int bmp_x,bmp_y;				// Game screen offset (32,32)
   int bmp_w,bmp_h;				// Game screen size (320,224)
   int ofs_x,ofs_y;				// Scroll offset add (0,-8)
   mapper_direct *mapper;			// Colour mapper
   UINT16 ctrl;					// color/pri control
   UINT8 *RAM_TILE;				// Extra Tile mapping
   UINT8 *RAM_TILE_B;				// Extra Tile mapping (double buffer)
   UINT8 cols;					// Colours per sprite
} TC0200OBJ;

struct TC0200OBJ tc0200obj;

extern UINT16 *f2_sprite_extension,f2_sprites_colors;

void init_tc0200obj(void);

void make_object_bank(UINT8 *src);

void render_tc0200obj_mapped_b(void);

void render_tc0200obj_mapped_yuyugogo(void);
void render_tc0200obj_mapped_yuyugogo2(int pri);

void render_tc0200obj_mapped(int pri);

void render_tc0200obj_mapped_soliltary_fighter(void);

void render_tc0200obj_mapped_64(void);

void render_tc0200obj_mapped_r270(void);

void render_tc0200obj_mapped_r270_b(void); // old
void render_tc0200obj_mapped_r270_b_rot(void); // new

void render_tc0200obj_mapped_opwolf3(void);

void render_tc0200obj_mapped_f3system(void);
void render_tc0200obj_mapped_f3system_b(void);
void render_tc0200obj_mapped_f3system_b_multi(UINT8 *colour_mask);

void render_tc0200obj_mapped_f3system_r180(void);
void render_tc0200obj_mapped_f3system_r270_b(void);

void render_tc0200obj_mapped_fchamp(int pri);
void make_object_bank_koshien(UINT8 *src);

#ifdef __cplusplus
}
#endif
