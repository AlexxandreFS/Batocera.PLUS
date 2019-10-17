
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                    R-GUI: RAINE GUI - SUPPORT PROCEDURES                   */
/*                                                                            */
/******************************************************************************/

#ifndef __rguiprocdefs__
#define __rguiprocdefs__

#include "raine.h"

// active gui colours

#define GUI_COL_TEXT_1		(0xFF)
#define GUI_COL_TEXT_2		(0xFE)
#define GUI_COL_BLACK		(0xFD)

#define GUI_BOX_COL_HIGH_2	(0xFC)
#define GUI_BOX_COL_HIGH_1	(0xFB)
#define GUI_BOX_COL_MIDDLE	(0xFA)
#define GUI_BOX_COL_LOW_1	(0xF9)
#define GUI_BOX_COL_LOW_2	(0xF8)

#define GUI_COL_SELECT		(0xF5)

extern int CGUI_COL_TEXT_1,CGUI_COL_TEXT_2,CGUI_COL_BLACK,
  CGUI_BOX_COL_HIGH_2,CGUI_BOX_COL_HIGH_1,CGUI_BOX_COL_MIDDLE,
  CGUI_BOX_COL_LOW_1,CGUI_BOX_COL_LOW_2,CGUI_COL_SELECT;

// disabled gui colours

#define DGUI_COL_TEXT_1		(0xF7)
#define DGUI_COL_TEXT_2		(0xF6)

#define DGUI_BOX_COL_HIGH_2	(0xF4)
#define DGUI_BOX_COL_HIGH_1	(0xF3)
#define DGUI_BOX_COL_MIDDLE	(0xF2)
#define DGUI_BOX_COL_LOW_1	(0xF1)
#define DGUI_BOX_COL_LOW_2	(0xF0)

// gui fonts

FONT *gui_main_font;
FONT *gui_fixed_font;

// gui dialog routines

int x_edit_proc(int msg, DIALOG *d, int c);

int d_raine_window_proc(int msg, DIALOG *d, int c);

int d_raine_oxygen_proc(int msg, DIALOG *d, int c);

int d_raine_box_proc(int msg, DIALOG *d, int c);

int d_null_proc(int msg, DIALOG *d, int c);

int d_progress_proc(int msg, DIALOG *d, int c);

int d_raine_button_proc(int msg, DIALOG *d, int c);
int d_raine_check_proc(int msg, DIALOG *d, int c);
int x_raine_button_proc(int msg, DIALOG *d, int c);

int d_raine_list_proc(int msg, DIALOG *d, int c);

int d_raine_radio_proc(int msg, DIALOG *d, int c);
int x_raine_radio_proc(int msg, DIALOG *d, int c);
int d_raine_radio_button_proc(int msg, DIALOG *d, int c);

int d_raine_textbox_proc(int msg, DIALOG *d, int c);

int x_text_proc(int msg, DIALOG *d, int c);
int x_ctext_proc(int msg, DIALOG *d, int c);
int raine_slider_proc(int msg, DIALOG *d, int c);

#endif

#ifdef __cplusplus
}
#endif
