
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                 tc0005rot: TAITO ROTATION LAYER (F2-SYSTEM)                */
/*                                                                            */
/******************************************************************************/

typedef struct TC0005ROT			// Information about 1 chip
{
   UINT8 *RAM;					// Chip RAM address
   UINT8 *RAM_SCR;				// Scroll RAM address
   UINT8 *GFX_ROT;				// GFX BG0
} TC0005ROT;

extern struct TC0005ROT tc0005rot;

void init_tc0005rot();
void init_tc430grw();

void tc0005rot_bg0_ww(UINT32 address, UINT16 data);
void tc0005rot_set_bitmap();
void tc0005rot_unset_bitmap();

void tc0005rot_refresh_buffer(void);

void tc0005rot_draw_rot(int col_ofs, int transp);
void tc0005rot_draw_rot_r270(int col_ofs, int transp);

#ifdef __cplusplus
}
#endif
