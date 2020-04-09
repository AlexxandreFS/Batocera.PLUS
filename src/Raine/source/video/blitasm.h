
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                   SOME CUSTOM ASM VIDEO SUPPORT ROUTINES                   */
/*                                                                            */
/******************************************************************************/

#include "raine.h"

extern UINT32 SourceSeg,
DestSeg,
SourceStart,
DestStart,
BlitWidth,
BlitHeight,
SourceAdd,
DestAdd;

void fast_blit_movsl(void);
void fast_blit_movl(void);
void fast_blit_movq(void);

// Update only changed palette entries, and vsync if enabled
// even if it wasn't needed

void fast_palette_update(PALETTE p, PALETTE p2, int vsync);
void fast_palette_update_8(PALETTE p, PALETTE p2, int vsync); // in 8bpp

// Update only changed palette entries, and only vsync if
// a changed entry exists

void fast_palette_update_vsync_check(PALETTE p, PALETTE p2);

#ifdef __cplusplus
}
#endif
