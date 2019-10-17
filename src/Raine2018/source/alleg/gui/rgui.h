
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                              R-GUI: RAINE GUI                              */
/*                                                                            */
/******************************************************************************/

#ifndef __rguidefs__
#define __rguidefs__

#include "raine.h"
#include "games.h"

int fbcon_enabled;
// If true, then palette switching must be slow, and fbcon must be the only
// driver available...

void setup_gui_screen();
#ifdef GFX_FBCON
void setup_fb_modes();
#endif
#ifdef GFX_XWINDOWS_FULLSCREEN
void setup_xfs_modes();
#endif

void done_gui_screen();

int raine_gfx_mode_select(void);

int raine_alert(char *title, char *s1, char *s2, char *s3, char *b1, char *b2, int c1, int c2);
#define MessageBox(title,msg,button) raine_alert(title,msg,"","",button,"",0,0)
#define ErrorMsg(msg) MessageBox("Error",msg,"OK")
int raine_edit_int(char *title, char *s1, char *b1, char *b2, int c1, int c2, int inf, int supp, int def);

char *gfx_card_name(UINT32 index);

void dialog_oxygen(void);

int raine_do_dialog(DIALOG *dialog, int focus_obj);

void mouse_on_real_screen(void);
void mouse_on_buffer_screen(void);
void dialog_on_real_screen(void);
void dialog_on_buffer_screen(void);

int gfx_card_number(UINT32 index);

// this one in rfsel.c

int raine_file_select(char *message, char *path, char *ext);
void fsel(char *path, char **exts,char *res, char *msg);
#define SDL_WM_SetCaption(s1,s2)
#define SDL_Color RGB

#define rgui_mouse_x	gui_mouse_x
#define rgui_mouse_y	gui_mouse_y
#define rgui_mouse_b	gui_mouse_b

#define raine_window_dialog	raine_do_dialog
void build_mode_list();

#endif

#ifdef __cplusplus
}
#endif
