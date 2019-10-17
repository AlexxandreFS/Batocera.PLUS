#ifndef _GUI_H
#define _GUI_H

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                                  RAINE GUI                                 */
/*                                                                            */
/******************************************************************************/

#include <allegro.h>
#include "deftypes.h"

extern PALETTE gui_pal;

typedef struct RGUI_CFG
{
   UINT32 gui_col_text_1;
   UINT32 gui_col_text_2;
   UINT32 gui_col_black;
   UINT32 gui_col_select;
   UINT32 gui_box_col_high_2;
   UINT32 gui_box_col_high_1;
   UINT32 gui_box_col_middle;
   UINT32 gui_box_col_low_1;
   UINT32 gui_box_col_low_2;
   UINT32 game_list_mode;		// Show full, available or missing games
   char bg_image[256];			// bg image
   char font_datafile[256];	// font file
} RGUI_CFG;

extern struct RGUI_CFG rgui_cfg;

#define SET_PAL( COL ) switch (display_cfg.bpp){\
  case 8: C##COL = COL; break; \
  case 15: C##COL = makecol15(gui_pal[COL].r<<2,gui_pal[COL].g<<2,gui_pal[COL].b<<2); break; \
  case 16: C##COL = makecol16(gui_pal[COL].r<<2,gui_pal[COL].g<<2,gui_pal[COL].b<<2); break; \
  case 24: C##COL = makecol24(gui_pal[COL].r<<2,gui_pal[COL].g<<2,gui_pal[COL].b<<2); break; \
  case 32: C##COL = makecol32(gui_pal[COL].r<<2,gui_pal[COL].g<<2,gui_pal[COL].b<<2); break; \
}

// StartGUI():
// Does the whole gui loop, currently always returns 0.

int StartGUI(void);
void setup_gui();
void release_gui();

void Unselect_Button(DIALOG *d);
void FadeGUI(void);
BITMAP *make_mapped_bitmap(BITMAP *src, int *start, PALETTE *src_pal, UINT32 cols);
void destroy_mapped_bitmap(BITMAP *dest, UINT32 cols);
void set_gui_palette(void);
void MakeGUIBack(void);
void raine_centre_dialog(DIALOG *dialog);
void load_progress(char *msg, int progress);
void load_explicit_progress(int current, int max);
void init_joys();
void read_gui_config();
void write_gui_config();
void setup_font();
void load_message(char *msg);

#ifdef __cplusplus
}
#endif
#endif
