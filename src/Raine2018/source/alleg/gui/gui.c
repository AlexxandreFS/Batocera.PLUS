/******************************************************************************/
/*									      */
/*		    RAINE GUI: Based on allegro GUI routines		      */
/*									      */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "raine.h"
#include "emumain.h"
#include "gui.h"
#include "gui2.h"
#include "default.h"
#include "dsw.h"
#include "ingame.h"
#include "arpro.h"
#include "control.h"
#include "sasound.h"
#include "config.h"
#include "games.h"
#include "tilemod.h"
#include "palette.h"
#include "hiscore.h"
#include "loadroms.h"
#include "newmem.h"
#include "sound.h"
#include "debug.h"
#include "savegame.h"
#include "blit.h" // ReclipScreen
#ifdef RAINE_DEBUG
#include "dbg_gui.h"
#endif
#include "dejap.h" // default palettes, mouse sprites in raine.dat
#include "display.h"
#include "alleg/jpg/jpgalleg.h"
#include "loadpng.h"
#include "files.h"
#include "bld.h"
#include "profile.h" // fps
#if HAS_NEO
#include "neocd/cdrom.h"
#include "neocd/neocd.h"
#endif

extern void update_stretch(); // stretch.c
struct RGUI_CFG rgui_cfg;

PALETTE gui_pal;

static	 BITMAP *snapshot=NULL;
static int snapshot_cols;


#if defined( RAINE_WIN32 )

#define strcasecmp stricmp

#endif

extern int bestw, besth,bestbpp; // rgui.c to switch mode
int screen_valid;	// 1 if screen contains a valid image

int wants_switch_res = 0;
static int WantScreen;
static int WantQuit;
static int WantPlay;

gamestr game_select_string1;
gamestr game_company,game_year,game_sound,game_strtype;
gamestr pad_buf;

int allocate_pens(int pens);
void free_pens(int pens);
void free_all_pens(void);

void free_game_avail_list(void);

void read_gui_config() {
   rgui_cfg.gui_col_text_1	= raine_get_config_hex( "GUI",          "gui_col_text_1",               0xFFFFFF);
   rgui_cfg.gui_col_text_2	= raine_get_config_hex( "GUI",          "gui_col_text_2",               0x6FEFEF);
   rgui_cfg.gui_col_black	= raine_get_config_hex( "GUI",          "gui_col_black",                0x000000);
   rgui_cfg.gui_col_select	= raine_get_config_hex( "GUI",          "gui_col_select",               0x787878);
   rgui_cfg.gui_box_col_high_2	= raine_get_config_hex( "GUI",          "gui_box_col_high_2",           0x5858A8);
   rgui_cfg.gui_box_col_high_1	= raine_get_config_hex( "GUI",          "gui_box_col_high_1",           0x383888);
   rgui_cfg.gui_box_col_middle	= raine_get_config_hex( "GUI",          "gui_box_col_middle",           0x282878);
   rgui_cfg.gui_box_col_low_1	= raine_get_config_hex( "GUI",          "gui_box_col_low_1",            0x181868);
   rgui_cfg.gui_box_col_low_2	= raine_get_config_hex( "GUI",          "gui_box_col_low_2",            0x080848);

   rgui_cfg.game_list_mode	= raine_get_config_int( "GUI",          "game_list_mode",       1);
   strcpy(rgui_cfg.bg_image,	 raine_get_config_string( "GUI",        "bg_image",             ""));

   strcpy(rgui_cfg.font_datafile,     raine_get_config_string( "GUI",   "font_datafile",                ""));
#if HAS_NEO
   restore_cdrom_config();
   restore_neocd_config();
#endif
}

void write_gui_config() {
   raine_set_config_hex(	"GUI",          "gui_col_text_1",       rgui_cfg.gui_col_text_1);
   raine_set_config_hex(	"GUI",          "gui_col_text_2",       rgui_cfg.gui_col_text_2);
   raine_set_config_hex(	"GUI",          "gui_col_black",        rgui_cfg.gui_col_black);
   raine_set_config_hex(	"GUI",          "gui_col_select",       rgui_cfg.gui_col_select);
   raine_set_config_hex(	"GUI",          "gui_box_col_high_2",   rgui_cfg.gui_box_col_high_2);
   raine_set_config_hex(	"GUI",          "gui_box_col_high_1",   rgui_cfg.gui_box_col_high_1);
   raine_set_config_hex(	"GUI",          "gui_box_col_middle",   rgui_cfg.gui_box_col_middle);
   raine_set_config_hex(	"GUI",          "gui_box_col_low_1",    rgui_cfg.gui_box_col_low_1);
   raine_set_config_hex(	"GUI",          "gui_box_col_low_2",    rgui_cfg.gui_box_col_low_2);

   raine_set_config_int(	"GUI",          "game_list_mode",       rgui_cfg.game_list_mode);

   if(rgui_cfg.bg_image[0])
   raine_set_config_string(	"GUI",          "bg_image",             rgui_cfg.bg_image);

   if(rgui_cfg.font_datafile[0])
   raine_set_config_string(	"GUI",          "font_datafile",        rgui_cfg.font_datafile);
#if HAS_NEO
  save_cdrom_config();
  save_neocd_config();
#endif
}

/*

raine_centre_dialog(): centre a dialog onscreen

*/

static int scale = 8;

void raine_centre_dialog(DIALOG *dialog)
{
   int min_x, min_y;
   int max_x, max_y;
   int dx, dy;
   int i, new_scale;

   /*

   place window at (0,0)

   */

   dx = dialog[0].x;
   dy = dialog[0].y;

   for(i=0; dialog[i].proc; i++){

      dialog[i].x -= dx;
      dialog[i].y -= dy;

   }

   /*

   scale window

   */

   new_scale = text_height(gui_main_font);

   for(i=0; dialog[i].proc; i++){

      dialog[i].x = (dialog[i].x * new_scale) / scale;
      dialog[i].y = (dialog[i].y * new_scale) / scale;
      dialog[i].w = (dialog[i].w * new_scale) / scale;
      dialog[i].h = (dialog[i].h * new_scale) / scale;

   }

   /*

   centre window

   */

   min_x = dialog[0].x;
   min_y = dialog[0].y;
   max_x = dialog[0].x + dialog[0].w;
   max_y = dialog[0].y + dialog[0].h;

   dx = (SCREEN_W - (max_x - min_x)) / 2 - min_x;
   dy = (SCREEN_H - (max_y - min_y)) / 2 - min_y;

   for(i=0; dialog[i].proc; i++){

      dialog[i].x += dx;
      dialog[i].y += dy;

   }
}

static DATAFILE *font_data;

void setup_font()
{
  if (ingame_font) {
    return;
  }
  if(rgui_cfg.font_datafile[0])
     font_data = load_datafile(rgui_cfg.font_datafile);
   if (display_cfg.screen_x >= 640 && display_cfg.screen_y >= 480)
     font_data = load_datafile("bigfont.dat");
   else if(!rgui_cfg.font_datafile[0]) {
     unload_datafile(font_data);
     font_data = NULL;
   }

   if(font_data){
     gui_main_font     = font_data[2].dat;
     gui_fixed_font    = font_data[1].dat;
     ingame_font       = font_data[0].dat;
     font	       = gui_main_font;
   } else if (RaineData) {
     gui_main_font     = RaineData[font_gui_main].dat;
     gui_fixed_font    = RaineData[font_gui_fixed].dat;
     ingame_font       = RaineData[font_8x8_ingame].dat;
     font	       = gui_main_font;
   }
}

/*

centre_all_dialogs(): centre all raine dialogs

*/

void centre_all_dialogs(void)
{
   UINT32 i;

   if (!RaineData)
     return;

   setup_font(); // Usefull even without gui for the messages on screen

   if(!raine_cfg.no_gui) {	// GUI MODE
     i = 0;
     while(raine_dialog_list[i])
       raine_centre_dialog( raine_dialog_list[i++] );
     scale = text_height(gui_main_font);

     MakeGUIBack();
   }
}

// Unselect_Button():
// Force a Button object to redraw itself unselected+unfocused
// Otherwise, they don't get redrawn till after the button's action
// (which looks ugly...).

void Unselect_Button(DIALOG *d)
{
   d->flags &= ~(D_SELECTED|D_GOTFOCUS);
     scare_mouse();
   x_raine_button_proc(MSG_DRAW,d,0);
     unscare_mouse();
   //dialog_oxygen();
}


UINT32 darken(UINT32 src)
{
   UINT32 r,g,b;

   r = (src >> 16) & 0xFF;
   g = (src >>	8) & 0xFF;
   b = (src >>	0) & 0xFF;

   r = (r * 0x100) / 0x148;
   g = (g * 0x100) / 0x148;
   b = (b * 0x100) / 0x148;

   return (r<<16) | (g<<8) | (b<<0);
}

int CGUI_COL_TEXT_1,CGUI_COL_TEXT_2,CGUI_COL_BLACK,
  CGUI_BOX_COL_HIGH_2,CGUI_BOX_COL_HIGH_1,CGUI_BOX_COL_MIDDLE,
  CGUI_BOX_COL_LOW_1,CGUI_BOX_COL_LOW_2,CGUI_COL_SELECT;

void set_gui_palette(void)
{
   gui_pal[GUI_COL_TEXT_1].r=(rgui_cfg.gui_col_text_1>>18)&0x3F;
   gui_pal[GUI_COL_TEXT_1].g=(rgui_cfg.gui_col_text_1>>10)&0x3F;
   gui_pal[GUI_COL_TEXT_1].b=(rgui_cfg.gui_col_text_1>>2)&0x3F;
   SET_PAL(GUI_COL_TEXT_1);

   gui_pal[GUI_COL_TEXT_2].r=(rgui_cfg.gui_col_text_2>>18)&0x3F;
   gui_pal[GUI_COL_TEXT_2].g=(rgui_cfg.gui_col_text_2>>10)&0x3F;
   gui_pal[GUI_COL_TEXT_2].b=(rgui_cfg.gui_col_text_2>>2)&0x3F;
   SET_PAL(GUI_COL_TEXT_2);

   gui_pal[GUI_COL_BLACK].r=(rgui_cfg.gui_col_black>>18)&0x3F;
   gui_pal[GUI_COL_BLACK].g=(rgui_cfg.gui_col_black>>10)&0x3F;
   gui_pal[GUI_COL_BLACK].b=(rgui_cfg.gui_col_black>>2)&0x3F;
   SET_PAL(GUI_COL_BLACK);

   gui_pal[GUI_COL_SELECT].r=(rgui_cfg.gui_col_select>>18)&0x3F;
   gui_pal[GUI_COL_SELECT].g=(rgui_cfg.gui_col_select>>10)&0x3F;
   gui_pal[GUI_COL_SELECT].b=(rgui_cfg.gui_col_select>>2)&0x3F;
   SET_PAL(GUI_COL_SELECT);

   gui_pal[GUI_BOX_COL_HIGH_2].r=(rgui_cfg.gui_box_col_high_2>>18)&0x3F;
   gui_pal[GUI_BOX_COL_HIGH_2].g=(rgui_cfg.gui_box_col_high_2>>10)&0x3F;
   gui_pal[GUI_BOX_COL_HIGH_2].b=(rgui_cfg.gui_box_col_high_2>>2)&0x3F;
   SET_PAL(GUI_BOX_COL_HIGH_2);

   gui_pal[GUI_BOX_COL_HIGH_1].r=(rgui_cfg.gui_box_col_high_1>>18)&0x3F;
   gui_pal[GUI_BOX_COL_HIGH_1].g=(rgui_cfg.gui_box_col_high_1>>10)&0x3F;
   gui_pal[GUI_BOX_COL_HIGH_1].b=(rgui_cfg.gui_box_col_high_1>>2)&0x3F;
   SET_PAL(GUI_BOX_COL_HIGH_1);

   gui_pal[GUI_BOX_COL_MIDDLE].r=(rgui_cfg.gui_box_col_middle>>18)&0x3F;
   gui_pal[GUI_BOX_COL_MIDDLE].g=(rgui_cfg.gui_box_col_middle>>10)&0x3F;
   gui_pal[GUI_BOX_COL_MIDDLE].b=(rgui_cfg.gui_box_col_middle>>2)&0x3F;
   SET_PAL(GUI_BOX_COL_MIDDLE);

   gui_pal[GUI_BOX_COL_LOW_1].r=(rgui_cfg.gui_box_col_low_1>>18)&0x3F;
   gui_pal[GUI_BOX_COL_LOW_1].g=(rgui_cfg.gui_box_col_low_1>>10)&0x3F;
   gui_pal[GUI_BOX_COL_LOW_1].b=(rgui_cfg.gui_box_col_low_1>>2)&0x3F;
   SET_PAL(GUI_BOX_COL_LOW_1);

   gui_pal[GUI_BOX_COL_LOW_2].r=(rgui_cfg.gui_box_col_low_2>>18)&0x3F;
   gui_pal[GUI_BOX_COL_LOW_2].g=(rgui_cfg.gui_box_col_low_2>>10)&0x3F;
   gui_pal[GUI_BOX_COL_LOW_2].b=(rgui_cfg.gui_box_col_low_2>>2)&0x3F;
   SET_PAL(GUI_BOX_COL_LOW_2);

   gui_pal[DGUI_COL_TEXT_1].r=(darken(rgui_cfg.gui_col_text_1)>>18)&0x3F;
   gui_pal[DGUI_COL_TEXT_1].g=(darken(rgui_cfg.gui_col_text_1)>>10)&0x3F;
   gui_pal[DGUI_COL_TEXT_1].b=(darken(rgui_cfg.gui_col_text_1)>>2)&0x3F;

   gui_pal[DGUI_COL_TEXT_2].r=(darken(rgui_cfg.gui_col_text_2)>>18)&0x3F;
   gui_pal[DGUI_COL_TEXT_2].g=(darken(rgui_cfg.gui_col_text_2)>>10)&0x3F;
   gui_pal[DGUI_COL_TEXT_2].b=(darken(rgui_cfg.gui_col_text_2)>>2)&0x3F;

   gui_pal[DGUI_BOX_COL_HIGH_2].r=(darken(rgui_cfg.gui_box_col_high_2)>>18)&0x3F;
   gui_pal[DGUI_BOX_COL_HIGH_2].g=(darken(rgui_cfg.gui_box_col_high_2)>>10)&0x3F;
   gui_pal[DGUI_BOX_COL_HIGH_2].b=(darken(rgui_cfg.gui_box_col_high_2)>>2)&0x3F;

   gui_pal[DGUI_BOX_COL_HIGH_1].r=(darken(rgui_cfg.gui_box_col_high_1)>>18)&0x3F;
   gui_pal[DGUI_BOX_COL_HIGH_1].g=(darken(rgui_cfg.gui_box_col_high_1)>>10)&0x3F;
   gui_pal[DGUI_BOX_COL_HIGH_1].b=(darken(rgui_cfg.gui_box_col_high_1)>>2)&0x3F;

   gui_pal[DGUI_BOX_COL_MIDDLE].r=(darken(rgui_cfg.gui_box_col_middle)>>18)&0x3F;
   gui_pal[DGUI_BOX_COL_MIDDLE].g=(darken(rgui_cfg.gui_box_col_middle)>>10)&0x3F;
   gui_pal[DGUI_BOX_COL_MIDDLE].b=(darken(rgui_cfg.gui_box_col_middle)>>2)&0x3F;

   gui_pal[DGUI_BOX_COL_LOW_1].r=(darken(rgui_cfg.gui_box_col_low_1)>>18)&0x3F;
   gui_pal[DGUI_BOX_COL_LOW_1].g=(darken(rgui_cfg.gui_box_col_low_1)>>10)&0x3F;
   gui_pal[DGUI_BOX_COL_LOW_1].b=(darken(rgui_cfg.gui_box_col_low_1)>>2)&0x3F;

   gui_pal[DGUI_BOX_COL_LOW_2].r=(darken(rgui_cfg.gui_box_col_low_2)>>18)&0x3F;
   gui_pal[DGUI_BOX_COL_LOW_2].g=(darken(rgui_cfg.gui_box_col_low_2)>>10)&0x3F;
   gui_pal[DGUI_BOX_COL_LOW_2].b=(darken(rgui_cfg.gui_box_col_low_2)>>2)&0x3F;
}

// FadeGUI():
// Remaps screen image of gui to darker colours. Used to 'fade out'
// Inactive gui areas

void FadeGUI(void)
{
   BITMAP *fade_backdrop;
   UINT8 *BIT;
   UINT32 ta,tb;
   UINT8 convert[256];

   if (display_cfg.bpp == 8) {

     for(ta=0;ta<256;ta++){
       convert[ta]=ta;
     }
     convert[GUI_COL_TEXT_1]	  = DGUI_COL_TEXT_1;
     convert[GUI_COL_TEXT_2]	  = DGUI_COL_TEXT_2;
     convert[GUI_COL_BLACK]	  = GUI_COL_BLACK;
     convert[GUI_COL_SELECT]	  = DGUI_BOX_COL_MIDDLE;
     convert[GUI_BOX_COL_HIGH_2]  = DGUI_BOX_COL_HIGH_2;
     convert[GUI_BOX_COL_HIGH_1]  = DGUI_BOX_COL_HIGH_1;
     convert[GUI_BOX_COL_MIDDLE]  = DGUI_BOX_COL_MIDDLE;
     convert[GUI_BOX_COL_LOW_1]   = DGUI_BOX_COL_LOW_1;
     convert[GUI_BOX_COL_LOW_2]   = DGUI_BOX_COL_LOW_2;

     // This bitmap must be created in 8bpp because of the palette effects
     fade_backdrop = create_bitmap_ex(8, display_cfg.screen_x,display_cfg.screen_y);

       scare_mouse();
     blit(screen,fade_backdrop,0,0,0,0,display_cfg.screen_x,display_cfg.screen_y);

     for(tb=0;tb<(UINT32)display_cfg.screen_y;tb++){
       BIT=fade_backdrop->line[tb];
       for(ta=0;ta<(UINT32)display_cfg.screen_x;ta++){
	 BIT[ta]=convert[BIT[ta]];
       }
     }

     blit(fade_backdrop,screen,0,0,0,0,display_cfg.screen_x,display_cfg.screen_y);
       unscare_mouse();

       destroy_bitmap(fade_backdrop);
   }

   //dialog_oxygen();
}

// for any mapped bitmap including mouse and logos in the dialogs...
BITMAP *make_mapped_bitmap(BITMAP *src, int *start, PALETTE *src_pal, UINT32 cols)
{
   BITMAP *dest;
   UINT8 *line,*line_2;
   int ta,x,y;

     dest = create_bitmap_ex(8, src->w, src->h);
     ta = allocate_pens(cols);
     if (ta <= 0 && display_cfg.bpp != 8) ta = 1;

     if(ta>0){

       for(y = 0; y < src->h; y++){
	 line   = src->line[y];
	 line_2 = dest->line[y];
	 for(x = 0; x < src->w; x++){
	   if(line[x])
	     line_2[x] = line[x] + ta;
	   else
	     line_2[x] = GUI_BOX_COL_MIDDLE;
	 }
       }

       memcpy(&gui_pal[ta], src_pal, cols*4);
       set_palette_range(gui_pal, ta, ta+cols-1, 0);

     }
     else{
       ta = 0;
     }

     *start = ta;

   return dest;
}

BITMAP *make_mapped_bitmap_2(BITMAP *src, int *start, PALETTE *src_pal, UINT32 cols)
{
   BITMAP *dest;
   UINT8 *line,*line_2;
   int ta,x,y;

   dest = create_bitmap_ex(8, src->w, src->h);
   ta = allocate_pens(cols);
   if (ta <= 0 && display_cfg.bpp != 8) ta = 1;

   if(ta>0){

     for(y=0;y<src->h;y++){
       line   = src->line[y];
       line_2 = dest->line[y];
       for(x=0;x<src->w;x++){
	 if(line[x]==0)
	   line_2[x] = 0;
	 else
	   line_2[x] = line[x]+ta;
       }
     }
     memcpy(&gui_pal[ta], src_pal, cols*4);
     set_palette_range(gui_pal, ta, ta+cols-1, 0);

   }
   else{
     ta = 0;
   }

   *start = ta;

   return dest;
   // Without breaking the palette in 16bpp. But I don't need this now !
}

void destroy_mapped_bitmap(BITMAP *dest, UINT32 cols)
{
  //if (display_cfg.bpp == 8) {
    free_pens(cols);
    //}
  destroy_bitmap(dest);
}

// screen_select_proc():
// Display then process Screen Select dialog

int screen_select_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      memcpy(&prev_display_cfg, &display_cfg, sizeof(DISPLAY_CFG));

      ret = raine_gfx_mode_select();

      if(ret){
	 WantScreen=1;
	 return D_EXIT;
      }
      else{
	 memcpy(&display_cfg, &prev_display_cfg, sizeof(DISPLAY_CFG));
	 return D_REDRAW;
      }
   }
   return ret;
}

// Data for game list and available/missing games

static int *GameAvail = NULL;
static UINT32 GameAvailCount = 0;
static int *GameMissing = NULL;
static UINT32 GameMissingCount = 0;

static int gtype = 0,gcompany=0; // Default values
static int my_game_count;
static struct GAME_MAIN **my_game_list;


static UINT8 ssound, syear, sstatus;

void build_game_avail_list(); // further...
static void update_game_list();

int sound_radio_proc(int msg, DIALOG *d, int c)
{
	int i;
	int ret=x_raine_radio_proc(msg, d, c);

	if((msg==MSG_KEY)||(msg==MSG_CLICK)){

		// Get selected List Mode
		// ----------------------
		// I hate these constants, but see no easy way to do it better for now

		if((game_select_opts[2].flags)&D_SELECTED) i = 0;
		else if((game_select_opts[3].flags)&D_SELECTED) i = 1;
		else if((game_select_opts[4].flags)&D_SELECTED) i = 2;
		else i = 0;

		if (i != ssound) {
			ssound = i;
			update_game_list();
		}
	}
	return ret;
}

int status_radio_proc(int msg, DIALOG *d, int c)
{
	int i;
	int ret=x_raine_radio_proc(msg, d, c);

	if((msg==MSG_KEY)||(msg==MSG_CLICK)){

		if((game_select_opts[6].flags)&D_SELECTED) i = 0;
		else if((game_select_opts[7].flags)&D_SELECTED) i = 1;
		else if((game_select_opts[8].flags)&D_SELECTED) i = 2;
		else i = 0;

		if (i != sstatus) {
			sstatus = i;
			update_game_list();
		}
	}
   return ret;
}

int year_radio_proc(int msg, DIALOG *d, int c)
{
	int i;
	int ret=x_raine_radio_proc(msg, d, c);

	if((msg==MSG_KEY)||(msg==MSG_CLICK)){

		if((game_select_opts[10].flags)&D_SELECTED) i = 0;
		else if((game_select_opts[11].flags)&D_SELECTED) i = 1;
		else if((game_select_opts[12].flags)&D_SELECTED) i = 2;
		else i = 0;

		if (i != syear) {
			syear = i;
			update_game_list();
		}
	}
	return ret;
}

static char driver_type[30];

static void raine_update_menu(int id) {
  menu[0].text = drivers_menu[id].text;
  update_game_list();
}

static int all_drivers() {
  strcpy(driver_type,"");
  raine_update_menu(0);
  return D_REDRAW;
}

static int cave_driver() {
  strcpy(driver_type,"cave.c");
  raine_update_menu(1);
  return D_REDRAW;
}

static int cps1_driver() {
  strcpy(driver_type,"cps1drv.c");
  raine_update_menu(2);
  return D_REDRAW;
}

static int cps2_driver() {
  strcpy(driver_type,"cps2drv.c");
  raine_update_menu(3);
  return D_REDRAW;
}

static int megasys1_driver() {
  strcpy(driver_type,"megasys1.c");
  raine_update_menu(4);
  return D_REDRAW;
}

static int nmk_driver() {
  strcpy(driver_type,"nmk.c");
  raine_update_menu(5);
  return D_REDRAW;
}

static int pacman_driver() {
  strcpy(driver_type,"pengo.c");
  raine_update_menu(6);
  return D_REDRAW;
}

static int psikyo_driver() {
  strcpy(driver_type,"gunbird.c");
  raine_update_menu(7);
  return D_REDRAW;
}

static int seta_driver() {
  strcpy(driver_type,"seta.c");
  raine_update_menu(8);
  return D_REDRAW;
}

static int taito_f2_driver() {
  strcpy(driver_type,"taito_f2.c");
  raine_update_menu(9);
  return D_REDRAW;
}

static int lsystem_driver() {
  strcpy(driver_type,"lsystem.c");
  raine_update_menu(10);
  return D_REDRAW;
}

static int xsystem2_driver() {
  strcpy(driver_type,"xsystem2.c");
  raine_update_menu(11);
  return D_REDRAW;
}

static int toaplan1_driver() {
  strcpy(driver_type,"toaplan1.c");
  raine_update_menu(12);
  return D_REDRAW;
}

static int toaplan2_driver() {
  strcpy(driver_type,"toaplan2.c");
  raine_update_menu(13);
  return D_REDRAW;
}

static void build_game_list()
{
  int n;
  struct GAME_MAIN *game;

  if (my_game_list) free(my_game_list);
  my_game_count = 0;

  my_game_list = malloc(game_count * sizeof(GAME_MAIN*));
  for (n=0; n<game_count; n++) {
    game = game_list[n];
    if (
	(((!sstatus) && !(game->flags & (GAME_NOT_WORKING | GAME_PARTIALLY_WORKING))) ||
	(sstatus==1 && (game->flags & GAME_PARTIALLY_WORKING)) ||
	(sstatus==2 && (game->flags & GAME_NOT_WORKING)))) {

      if (!ssound || (ssound==1 && game->sound) || // sound
	  (ssound==2 && !game->sound)) { // no sound

	if (!syear || (syear==1 && (game->year >= 1990)) ||
	    (syear==2 && (game->year < 1990))) {

	  if (!gtype || (game->flags & (1<<(gtype-1)))) {
	    if (!gcompany || game->company_id==gcompany)

	      if (!*driver_type || strstr(game->source_file,driver_type))
		my_game_list[my_game_count++] = game_list[n];
	  }
	}
      }
    }
  }
}

void set_game_list_mode(int i);

static int listbox_active = 0; // to know if we can redraw or not...

static void update_game_list()
{
  build_game_avail_list();
  set_game_list_mode(rgui_cfg.game_list_mode);
  listbox_active = 0;
  listbox_getter(-4,&game_select[GAME_LIST].d1);
  listbox_active = 1;
}

char *game_type_getter(int index, int *list_size)
{
  if (index == -1){ // Nb of indexes
    *list_size = sizeof(game_type)/sizeof(char*);
  } else if (index == -4) { // clic !
    gtype = *list_size;
    update_game_list();
  } else if (index >= 0 && index < sizeof(game_type)/sizeof(char*)) {
    return game_type[index];
  }
  return NULL;
}

char *game_company_getter(int index, int *list_size)
{
  if (index == -1){ // Nb of indexes
    *list_size = nb_companies;
  } else if (index == -4) { // clic !
    gcompany = *list_size;
    update_game_list();
  } else if (index > 0 && index < nb_companies) {
    return game_company_name(index);
  } else if (index == 0)
    return "Any";
  return NULL;
}

// build_game_avail_list():
// Updates available and missing game lists, called
// before doing game select dialog.


void set_game_list_mode(int i)
{
   int ta, tb;

   switch(rgui_cfg.game_list_mode){
      case 0x00:
	 tb = game_select[GAME_LIST].d1;
      break;
      case 0x01:
	 tb = GameAvail[game_select[GAME_LIST].d1];
      break;
      case 0x02:
	 tb = GameMissing[game_select[GAME_LIST].d1];
      break;
      // When none of the options above match (which should be never)
	  // Default to option 0;
	  default:
	 tb = game_select[GAME_LIST].d1;
      break;
   }

   rgui_cfg.game_list_mode = i;

   switch(rgui_cfg.game_list_mode){
      case 0x00:
	if (my_game_count<10)
	  sprintf(game_select[9].dp,"%d/%d Games Listed      ", my_game_count, my_game_count);
	else
	  sprintf(game_select[9].dp,"%d/%d Games Listed     ", my_game_count, my_game_count);
	 game_select[GAME_LIST].d1 = tb;
      break;
      case 0x01:
	if (my_game_count<10)
	  sprintf(game_select[9].dp,"%d/%d Games Listed      ", GameAvailCount, my_game_count);
	else
	  sprintf(game_select[9].dp,"%d/%d Games Listed     ", GameAvailCount, my_game_count);
	 game_select[GAME_LIST].d1 = 0;
	 for(ta = 0; (UINT32)ta < GameAvailCount; ta++)
	    if(GameAvail[ta] == tb)
	       game_select[GAME_LIST].d1 = ta;
      break;
      case 0x02:
	if (my_game_count<10)
	  sprintf(game_select[9].dp,"%d/%d Games Listed      ", GameMissingCount, my_game_count);
	else
	  sprintf(game_select[9].dp,"%d/%d Games Listed     ", GameMissingCount, my_game_count);
	game_select[GAME_LIST].d1 = 0;
	for(ta = 0; (UINT32)ta < GameMissingCount; ta++)
	    if(GameMissing[ta] == tb)
	       game_select[GAME_LIST].d1 = ta;
      break;
   }
}

void build_game_avail_list(void)
{
   int ta,oldcount;

   build_game_list();
   if(GameAvail) free_game_avail_list();
   oldcount = my_game_count;
   if (!my_game_count) my_game_count = 1; // To avoid the segfault with efence
   // when there are no games at all !!!

   GameAvail   = (int *) malloc(sizeof(int) * my_game_count);
   GameMissing = (int *) malloc(sizeof(int) * my_game_count);
   my_game_count=oldcount;

   GameAvailCount = 0;
   GameMissingCount = 0;

   for(ta=0; ta<my_game_count; ta++){

      if( game_exists(my_game_list,ta) )

	 GameAvail[GameAvailCount++] = ta;

      else

	 GameMissing[GameMissingCount++] = ta;

   }

   ta = rgui_cfg.game_list_mode;
   rgui_cfg.game_list_mode = 0;
   game_select[GAME_LIST].d1 = raine_cfg.req_game_index;

   set_game_list_mode(ta);
}

void free_game_avail_list(void)
{
   if(GameAvail) free(GameAvail);
   GameAvail = NULL;

   if(GameMissing) free(GameMissing);
   GameMissing = NULL;
}

// listbox_getter():
// Get game names for game select list, three
// different listing modes.

static const char *get_long_name(GAME_MAIN *game)
{
  return game->long_name;
}

static int get_normal_index(int index)
{
  return index;
}

static int get_avail_index(int index)
{
  return GameAvail[index];
}

static int get_missing_index(int index)
{
  return GameMissing[index];
}

static char* pad(char* s,int len)
{
  int len0=strlen(s);
  strcpy(pad_buf,s);
  if (len>len0)
    memset(&pad_buf[len0],0x20,len-len0);
  pad_buf[len] = 0;
  return pad_buf;
}

static char* ipad(int n, int len)
{
  char buff[10];
  sprintf(buff,"%d",n);
  return pad(buff,len);
}

static char* game_type_name(int type,int len)
{
  char buff[50];
  int ta;
  buff[0]=0;
  for (ta=0; ta<=10; ta++)
    if (type & (1 << ta)){
      sprintf(buff+strlen(buff),"%s ",game_type[ta+1]);
      break;
    }
  return pad(buff,len);
}

static void setup_game_bitmap()
{
  int new_scale,hx,hy,vx,vy;
  game_select[GAME_BITMAP].dp	= snapshot;
  new_scale = text_height(gui_main_font);
  hx = 130 * new_scale / 8;
  hy = 76 * new_scale / 8;
  vx = 70 * new_scale / 8;
  vy = 120 * new_scale / 8;
  if (snapshot->w > snapshot->h) { // horizontal
    game_select[GAME_BITMAP].x = game_select[0].x+(150*new_scale)/8;
    game_select[GAME_BITMAP].y = game_select[0].y+(145*new_scale)/8+5;
    game_select[GAME_BITMAP].w	  = (snapshot->w < hx ? snapshot->w : hx);
    game_select[GAME_BITMAP].h	  = (snapshot->h < hy ? snapshot->h : hy);
  } else { // vertical
    game_select[GAME_BITMAP].x = game_select[0].x + (235*new_scale)/8;
    game_select[GAME_BITMAP].y = game_select[0].y + (100*new_scale)/8+5;
    game_select[GAME_BITMAP].w	  = (snapshot->w < vx ? snapshot->w : vx);
    game_select[GAME_BITMAP].h	  = (snapshot->h < vy ? snapshot->h : vy);
  }
}

void destroy_snapshot(int redraw)
{
  if ((redraw) && (listbox_active)) // stupid allegro...
    rectfill(screen, game_select[GAME_BITMAP].x, game_select[GAME_BITMAP].y, game_select[GAME_BITMAP].x+game_select[GAME_BITMAP].w-1, game_select[GAME_BITMAP].y+game_select[GAME_BITMAP].h-1, CGUI_BOX_COL_MIDDLE);
  destroy_mapped_bitmap(snapshot,snapshot_cols);
  snapshot = NULL;
}

static BITMAP* load_snapshot(const char *name)
{
  char str[256];
  BITMAP *snapshot;
  PALETTE my_palette;

  if (text_height(gui_main_font) > 8)
    sprintf(str,"snapshot" SLASH "big" SLASH "%s.pcx", name);
  else
    sprintf(str,"snapshot" SLASH "%s.pcx", name);

  snapshot = load_pcx(get_shared(str),my_palette);

  if (!snapshot && text_height(gui_main_font) > 8) {
    sprintf(str,"snapshot" SLASH "%s.pcx", name);
    snapshot = load_pcx(get_shared(str),my_palette);
  }
  if (snapshot)
    set_palette_range(my_palette,0,239,1);
  return snapshot;
}

const char *listbox_getter(int index, int *list_size)
{
   int ta=0,list_length=0;
   int (*get_index)(int)=get_normal_index;
   const DIR_INFO *head;
   char *dir;

   switch(rgui_cfg.game_list_mode){
   case 0x00:			// Mode 0: List all games
     list_length = my_game_count;
     get_index = get_normal_index;
     break;
   case 0x01:			// Mode 1: List available games
     list_length = GameAvailCount;
     get_index = get_avail_index;
     break;
   case 2:
     list_length = GameMissingCount;
     get_index = get_missing_index;
   }

   switch(index){
   case -1:			// Return List Size
     *list_size = list_length;
     return NULL;
     break;
   case -2:			// Act upon List Object Selection
     break;
   case -4:

     if (snapshot)
       destroy_snapshot(1);
     if ((rgui_cfg.game_list_mode==0 && my_game_count>0) ||
	 (rgui_cfg.game_list_mode==1 && GameAvailCount>0) ||
	 (rgui_cfg.game_list_mode==2 && GameMissingCount>0)) {
       if (*list_size > list_length)
	 *list_size = list_length-1;
       ta = get_index(*list_size);
       sprintf(game_select[GAME_DATA].dp,
	       pad(game_company_name(my_game_list[ta]->company_id),20));
       sprintf(game_select[GAME_DATA+1].dp,
	       ipad(my_game_list[ta]->year,20));
       if (my_game_list[ta]->sound)
	 sprintf(game_select[GAME_DATA+2].dp,"Yes  ");
       else
	 sprintf(game_select[GAME_DATA+2].dp,"No   ");
       sprintf(game_select[GAME_DATA+3].dp,
	       game_type_name(my_game_list[ta]->flags & 0x7ff,14));

       snapshot = load_snapshot(my_game_list[ta]->main_name);

       snapshot_cols = 240;

       if (!snapshot) {
	 head = my_game_list[ta]->dir_list;
	 for (; head; head++) {
	   dir = head[0].maindir;

	   if( dir ){

	     if( IS_ROMOF(dir) ){

	       GAME_MAIN *game_romof;

	       game_romof = find_game(dir+1);

	       snapshot = load_snapshot(game_romof->main_name);

	       if (snapshot) break;
	     }
	   } else
	     break;
	 }
       }
     } else {
       sprintf(game_select[GAME_DATA].dp,
	       pad("---",20));
       sprintf(game_select[GAME_DATA+1].dp,
	       pad("---",20));
       if (my_game_list[ta]->sound)
	 sprintf(game_select[GAME_DATA+2].dp,"--- ");
       else
	 sprintf(game_select[GAME_DATA+2].dp,"--- ");
       sprintf(game_select[GAME_DATA+3].dp,
	       pad("---",14));
       snapshot = NULL;
     }

     if (!snapshot) {
       snapshot_cols = 7;
       snapshot = make_mapped_bitmap(RaineData[RaineLogo].dat, &ta, RaineData[GUIPalette].dat, snapshot_cols);
     }

     setup_game_bitmap();

     if (listbox_active) {
       // Redraw data fields
       for (ta = 0; ta < 4; ta++)
	 SEND_MESSAGE(&game_select[GAME_DATA+ta], MSG_DRAW, 0);

     // Redraw titles
       for (ta = -4; ta < 0; ta++)
	 SEND_MESSAGE(&game_select[GAME_DATA+ta], MSG_DRAW, 0);
       SEND_MESSAGE(&game_select[GAME_BITMAP],MSG_DRAW,0);
     }
     return NULL;
/*    case -3:			// Act Keyboard Input */
/*      return d_text_list_proc(index,list_size); */
   default:
     if((index >= 0)&&(index<list_length))
       return get_long_name(my_game_list[get_index(index)]);
     else
       return NULL;
     break;
   }
   return NULL;
}

// game_radio_proc():
// Radio buttons for game list mode, need to be custom
// to incorporate automatic update on button selection.

int game_radio_proc(int msg, DIALOG *d, int c)
{
   int i;

   int ret=x_raine_radio_proc(msg, d, c);

   if((msg==MSG_KEY)||(msg==MSG_CLICK)){

      // Get selected List Mode
      // ----------------------

      if((game_select[5+0].flags)&D_SELECTED) i = 0;
      else if((game_select[5+1].flags)&D_SELECTED) i = 1;
      else if((game_select[5+2].flags)&D_SELECTED) i = 2;
	  else i = 0;

      set_game_list_mode(i);

      // Refresh the Game List
      // ---------------------

      SEND_MESSAGE(&game_select[GAME_LIST], MSG_END, 0);
      SEND_MESSAGE(&game_select[GAME_LIST], MSG_START, 0);

	scare_mouse();
      broadcast_dialog_message(MSG_DRAW, 0);

	unscare_mouse();

      // Wait for release
      // ----------------

	while(gui_mouse_b()){
	  dialog_oxygen();
	}
	listbox_getter(-4,&game_select[GAME_LIST].d1);
   }
   return ret;
}

static UINT32 current_game_rom_count;
static UINT32 current_game_rom_load_count;

int load_game_proc(int msg, DIALOG *d, int c)
{
  (void)(d);
  (void)(c);
  switch(msg){
  case MSG_IDLE:

    mouse_on_real_screen();
    dialog_on_real_screen();

    LoadDefault();

    load_error = 0;
    load_debug = malloc(0x10000);

    sprintf(load_debug,"Load Game\n---------\n\n");

    if (my_game_list) // normal loading
      current_game = my_game_list[raine_cfg.req_game_index];
    else // uses -g switch
      current_game = game_list[raine_cfg.req_game_index];

    fps = current_game->video->fps;
    if (fps < 0.1)
	fps = 60.0; // 60 fps (default)

    // I have to change the depth BEFORE loading.
    // Probably because of the set_color_mapper in the loading function

    if(wants_switch_res) // && switch_res(current_game->video))){
      switch_res(current_game->video);
    else {
      print_debug("no resolution switching wanted\n");
      update_stretch();
    }

    /*

    count roms

    */

    if(!raine_cfg.no_gui) {	// GUI MODE
      const ROM_INFO *rom_list;

      current_game_rom_count = 0;
      current_game_rom_load_count = 0;
      rom_list = current_game->rom_list;

      while(rom_list->name)
	{
	  current_game_rom_count ++;
	  rom_list ++;
	}

      if(!current_game_rom_count)
	current_game_rom_count ++;

      loading_dialog[2].d1 = current_game_rom_load_count;
      loading_dialog[2].d2 = current_game_rom_count;
      scare_mouse();
      SEND_MESSAGE(&loading_dialog[2], MSG_DRAW,	0);
      unscare_mouse();
    }

    load_game_rom_info();

    if (!(load_error & LOAD_FATAL_ERROR)) {

      if(wants_switch_res) // && switch_res(current_game->video))){
	switch_res(current_game->video); // this time for the bezel...

      init_inputs();
      init_dsw();
      init_romsw();
      init_sound();
      read_bld();
    }

    if(!raine_cfg.no_gui) {	// GUI MODE
      dialog_on_buffer_screen();
      mouse_on_buffer_screen();
      loading_dialog[2].d1 = current_game_rom_count;
      loading_dialog[2].d2 = current_game_rom_count;
      scare_mouse();
      SEND_MESSAGE(&loading_dialog[2], MSG_DRAW,  0);
      unscare_mouse();
      dialog_oxygen();
    }
    return D_EXIT;
    break;
  default:
    return D_O_K;
    break;
  }
}

void load_game_gui() {
   BITMAP *load_mouse;
   int ta;
     load_mouse = make_mapped_bitmap_2(RaineData[mouse_busy].dat, &ta, RaineData[mouse_busy_pal].dat, 16);
     set_mouse_sprite(load_mouse);

     loading_dialog[2].d1 = 0;
     loading_dialog[2].d2 = 1;
     loading_dialog[1].dp = "Loading Game Files...";

     FadeGUI();

     raine_do_dialog(loading_dialog,-1);

      set_mouse_sprite(RaineData[Mouse].dat);
      destroy_mapped_bitmap(load_mouse, 16);
}

void do_load_game(void)
{
   int size;
#ifdef RAINE_DEBUG
	  int idx=18;
#else
	  int idx = 17;
#endif

   /*

   satisfy the request

   */

   raine_cfg.req_load_game = 0;


   /*

   close down the current game (if there is one)

   */

   if(current_game){

      ClearDefault();

   }


   if(!raine_cfg.no_gui) {	// GUI MODE
      // Do the load (via a loading window)

      load_game_gui();

   } else
     load_game_proc(MSG_IDLE,NULL,0); // load without gui

      // Check if the load was successful, if ok, load game config, if bad clear the mess

   switch(load_error&3){
   case LOAD_WARNING:			// WARNING - IT MIGHT RUN OK

     FadeGUI();
     strcat(load_debug,"\n\nThe game might not run correctly.");
     load_problem[2].dp = load_debug;
     raine_do_dialog(load_problem,-1);

   case 0x00:				// SUCCESS
     size = GetMemoryPoolSize()/1024; // Minimum Kb
     if (wants_switch_res) {
       memcpy(&prev_display_cfg, &display_cfg, sizeof(DISPLAY_CFG));

       if (bestbpp > 0 && bestbpp <=32) {
         WantScreen = 1;
         display_cfg.bpp = bestbpp;
         bestbpp = 0;
       }

       if (bestw && besth) {
         //display_cfg.screen_type = bestmode;
         display_cfg.screen_x = bestw;
         display_cfg.screen_y = besth;
         WantScreen = 1;
         bestw = besth = 0;
       }
     }

     load_game_config();

     reset_game_hardware();

#ifdef HAS_CONSOLE
     init_scripts(); // must be called AFTER reset_game_hardware
#endif

     {
       char name[40];

       strncpy(name,current_game->long_name,39);
       name[39] = 0;

       sprintf(gamename, "%s %s ", raine_translate_text("Game:"), name);
       if (size>=1024)
	 sprintf(&gamename[strlen(gamename)],"(%dMb)",size/1024);
       else
	 sprintf(&gamename[strlen(gamename)],"(%dKb)",size);
     }
     if (current_game_has_hiscores())
       sprintf(hiscores,"Hiscores");
     else
       *hiscores=0;
     if (CheatCount) {
       main_dialog[idx-3].proc = actionreplay_proc;
       sprintf(cheats,"C&heats");
     } else {
       main_dialog[idx-3].proc = x_text_proc;
       *cheats = 0;
     }

     if (current_game->romsw) {
       main_dialog[idx].proc = language_proc;
       strcpy(rom_region,"&Region");
     } else {
       main_dialog[idx].proc = x_text_proc;
       strcpy(rom_region,"");
     }

     if (current_game->dsw) {
       main_dialog[idx+1].proc = dsw_select_proc;
       strcpy(dips,"&Dips");
     } else {
       main_dialog[idx+1].proc = x_text_proc;
       strcpy(dips,"");
     }

     if (raine_cfg.save_game_screen_settings)
       WantScreen=1;
     break;
   case LOAD_FATAL_ERROR:			// FATAL ERROR - REMOVE GAME
   case LOAD_FATAL_ERROR|LOAD_WARNING:

     FadeGUI();
     load_problem[2].dp = load_debug;
     raine_do_dialog(load_problem,-1);

     if (current_game->clear)
       current_game->clear();

     ClearDefault();

     current_game = NULL;

     sprintf(gamename,"%s %s", raine_translate_text("Game:"), raine_translate_text("<No Game Loaded>"));
     break;
   }

   free(load_debug);
}

void load_progress(char *msg, int progress)
{
   if(current_game_rom_load_count < current_game_rom_count)
      current_game_rom_load_count ++;

   loading_dialog[4].dp = msg;
   loading_dialog[2].d1 = progress;
   loading_dialog[2].d2 = 100;

   scare_mouse();
   SEND_MESSAGE(&loading_dialog[0], MSG_DRAW,  0);
   SEND_MESSAGE(&loading_dialog[1], MSG_DRAW,  0);
   SEND_MESSAGE(&loading_dialog[2], MSG_DRAW,  0);
   SEND_MESSAGE(&loading_dialog[4], MSG_DRAW,  0);
   unscare_mouse();
}

void load_explicit_progress(int current, int max)
{
  loading_dialog[2].d1 = current;
  loading_dialog[2].d2 = max;

  scare_mouse();
  SEND_MESSAGE(&loading_dialog[2], MSG_DRAW,  0);
  unscare_mouse();
}

void load_message(char *msg) {
  if(!raine_cfg.no_gui) {	// GUI MODE
    loading_dialog[1].dp = msg;
    scare_mouse();
    // 3 redraw because the text is centered with a transparent background...
    SEND_MESSAGE(&loading_dialog[0], MSG_DRAW,  0);
    SEND_MESSAGE(&loading_dialog[1], MSG_DRAW,  0);
    SEND_MESSAGE(&loading_dialog[2], MSG_DRAW,  0);
    unscare_mouse();
  }
}

// game_select_proc():
// Display then process Game Select dialog

int game_select_opts_proc(int msg, DIALOG *d, int c)
{
  int ret=x_raine_button_proc(msg, d, c);

  if(ret==D_CLOSE){
    Unselect_Button(d);
    FadeGUI();

    // sound
    game_select_opts[2].flags=
      game_select_opts[3].flags=
      game_select_opts[4].flags=

      // status
      game_select_opts[6].flags = game_select_opts[7].flags =
      game_select_opts[8].flags =

      // year
      game_select_opts[10].flags = game_select_opts[11].flags =
      game_select_opts[12].flags =0;

    if (ssound==0) game_select_opts[2].flags = D_SELECTED;
    else
      game_select_opts[2+ssound].flags=D_SELECTED;
    game_select_opts[6+sstatus].flags = D_SELECTED;
    game_select_opts[10+syear].flags = D_SELECTED;

    raine_centre_dialog(game_select_opts);
    raine_do_dialog(game_select_opts,-1);
     SEND_MESSAGE(&game_select[GAME_LIST], MSG_END, 0);
     SEND_MESSAGE(&game_select[GAME_LIST], MSG_START, 0);
     SEND_MESSAGE(&game_select[GAME_LIST], MSG_DRAW, 0);
     SEND_MESSAGE(&game_select[9], MSG_DRAW, 0);
     // Update infos
     listbox_getter(-4,&game_select[GAME_LIST].d1);

     return D_REDRAW;
  }
  return ret;

}

int game_select_proc(int msg, DIALOG *d, int c)
{
  int ta;
  int ret=x_raine_button_proc(msg, d, c);

  if(ret==D_CLOSE){

    Unselect_Button(d);
    FadeGUI();

    /*

    set radio buttons

    */
    // I want these outside the main dlg, but they can be initialized here...

#ifdef RAINE_WIN32
    if (display_cfg.screen_type == GFX_DIRECTX_WIN ||
	display_cfg.screen_type == GFX_GDI)
      wants_switch_res = 1;
#endif

    if (!*driver_type)
      menu[0].text = drivers_menu[0].text;
    if(rgui_cfg.game_list_mode>2) rgui_cfg.game_list_mode = 2;
    if(ssound>2) ssound = 2;
    if (sstatus>2) sstatus = 2;
    if (wants_switch_res>1) wants_switch_res = 1;
    if (syear >2) syear = 2;

    game_select[5+0].flags=
      game_select[5+1].flags=
      game_select[5+2].flags=

    // switch res
    game_select[GAME_SWITCH_RES+1].flags =
      game_select[GAME_SWITCH_RES+2].flags = 0;

    game_select[GAME_SWITCH_RES+2-wants_switch_res].flags = D_SELECTED;

    game_select[5+rgui_cfg.game_list_mode].flags = D_SELECTED;

    build_game_avail_list();

    // Do the Dialog
    // -------------

    listbox_active = 0;
    listbox_getter(-4,&game_select[GAME_LIST].d1);
    listbox_active = 1;

    ret=raine_do_dialog(game_select,-1);

    listbox_active = 0;

    destroy_snapshot(0);
    set_palette(gui_pal);


    // Load game (if user didn't click cancel)
    // ---------------------------------------
    if((ret!=3)&&(ret!=-1)){

      /*

	 don't reload if the game is already in memory

      */
      ta = game_select[GAME_LIST].d1;
      if(my_game_list && current_game != my_game_list[ta])

      switch(rgui_cfg.game_list_mode){
      case 0x00:
	if((ta >= 0)&&(ta < my_game_count)){
	  raine_cfg.req_game_index = ta;
	  do_load_game();
	}
	break;
      case 0x01:
	printf("%d < %d\n",ta,GameAvailCount);
	if((ta >= 0)&&((UINT32)ta < GameAvailCount)){
	  raine_cfg.req_game_index = GameAvail[ta];
	  do_load_game();
	}
	break;
      case 0x02:
	if((ta >= 0)&&((UINT32)ta < GameMissingCount)){
	  raine_cfg.req_game_index = GameMissing[ta];
	  do_load_game();
	}
	break;
      }

    }

    free_game_avail_list();

    if(WantScreen)

      return D_EXIT;

    else

      return D_REDRAW;

  }
  return ret;
}

int romdir_edit_proc(int msg, DIALOG *d, int c)
{
   int i;
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      sprintf(romedit[0],"%s",dir_cfg.rom_dir[0]);
      sprintf(romedit[1],"%s",dir_cfg.rom_dir[1]);
      sprintf(romedit[2],"%s",dir_cfg.rom_dir[2]);
      sprintf(romedit[3],"%s",dir_cfg.rom_dir[3]);

      ret=raine_do_dialog(romdir_edit_dialog,-1);
      if(ret==1){

      sprintf(dir_cfg.rom_dir[0],"%s",romedit[0]);
      sprintf(dir_cfg.rom_dir[1],"%s",romedit[1]);
      sprintf(dir_cfg.rom_dir[2],"%s",romedit[2]);
      sprintf(dir_cfg.rom_dir[3],"%s",romedit[3]);

      for(i = 0; i < 4; i ++){
	 if(dir_cfg.rom_dir[i][0]){
	    put_backslash(dir_cfg.rom_dir[i]);
	    strlwr(dir_cfg.rom_dir[i]);
	 }
      }

      build_game_avail_list();

      scare_mouse();
      SEND_MESSAGE(&game_select[GAME_LIST],  MSG_START, 0);
      SEND_MESSAGE(&game_select[GAME_LIST],  MSG_DRAW,	0);
      SEND_MESSAGE(&game_select[9], MSG_DRAW,  0);
      unscare_mouse();
      dialog_oxygen();

      }
      return D_REDRAW;
   }
   return ret;
}

int dir_edit_proc(int msg, DIALOG *d, int c)
{
   char dir_path[256];
   char *ta;
   int ret;

   ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      sprintf(dir_path,"%s",romedit[d->d1]);

      if(raine_file_select("Select directory", dir_path, NULL)){

      // Cut any filename

      ta = get_filename(dir_path);
      if(ta) ta[0] = 0;

      sprintf(romedit[d->d1],"%s",dir_path);

      }

      return D_REDRAW;
   }
   return ret;
}

/******************************************************************************/

int auto_edit_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   /* Auto-fire : increate auto-fire rate for a key */

   if(ret==D_CLOSE){
      Unselect_Button(d);
      raine_increase_auto_rate(auto_select[1].d1);
      ret = D_REDRAW;
   }
   return ret;
}

char *autolist_getter(int index, int *list_size)
{
   static char S[128];

   if(raine_get_input_count()){

   switch(index){
   case -1:			// Return List Size
      *list_size=raine_get_input_count();
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
     raine_increase_auto_rate(auto_select[1].d1);
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < raine_get_input_count())){
	 sprintf(S,"%-21s %s",raine_input_name(index), raine_auto_name(index));
	 return S;
      }
      else
	 return NULL;
   break;
   }

   }
   else{

   if(index==-1){
      *list_size=1;
      return NULL;
   }
   else{
      if(index==0){
	 return(raine_translate_text("<No Inputs Mapped>"));
      }
      else{
	 return NULL;
      }
   }

   }
}

int auto_select_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      ret=0;
      while((ret!=2)&&(ret!=-1)){
	 ret=raine_do_dialog(auto_select,-1);
	 if((ret!=2)&&(ret!=-1)){
	   raine_increase_auto_rate(auto_select[1].d1);
	 }
      }

      ret = D_REDRAW;
   }
   return ret;
}

/******************************************************************************/

typedef struct GUI_JOY
{
   char *name;		// Mode name/string
   UINT32 id;		// ID_ Value for this mode
} GUI_JOY;

static GUI_JOY joystick_data[] =
{
   { "Autodetect",              JOY_TYPE_AUTODETECT,      },
   { "None",                    JOY_TYPE_NONE,            },
#ifdef JOYSTICK_DRIVER_STANDARD
   { "Joystick (2 buttons)",    JOY_TYPE_STANDARD,        }, // Standard
   { "Joystick (4 buttons)",    JOY_TYPE_4BUTTON,         },
   { "Joystick (6 buttons)",    JOY_TYPE_6BUTTON,         },
   { "Joystick (8 buttons)",    JOY_TYPE_8BUTTON,         },
   { "Joystick (2 pads)",       JOY_TYPE_2PADS,           },
   { "Flightstick Pro",         JOY_TYPE_FSPRO,           },
   { "Wingman Extreme",         JOY_TYPE_WINGEX,          },
#endif
#ifdef JOYSTICK_DRIVER_WINGWARRIOR
   { "Wingman Warrior",         JOY_TYPE_WINGWARRIOR,     }, // Wingman Warrior
#endif
#ifdef JOYSTICK_DRIVER_GAMEPAD_PRO
   { "Gamepad Pro",             JOY_TYPE_GAMEPAD_PRO,     }, // Game Pad Pro
#endif
#ifdef JOYSTICK_DRIVER_GRIP
   { "Grip",                    JOY_TYPE_GRIP,            }, // Grip
   { "Grip 4 way",              JOY_TYPE_GRIP4,           },
#endif
#ifdef JOYSTICK_DRIVER_SIDEWINDER
   { "Sidewinder",              JOY_TYPE_SIDEWINDER,      }, // Sidewinder
#endif
#ifdef JOY_TYPE_SIDEWINDER_AG
   { "Sidewinder Aggressive",   JOY_TYPE_SIDEWINDER_AG,   }, // Sidewinder Aggressive
#endif
#ifdef JOYSTICK_DRIVER_SNESPAD
   { "SNES (port 1)",           JOY_TYPE_SNESPAD_LPT1,    }, // SNES
   { "SNES (port 2)",           JOY_TYPE_SNESPAD_LPT2,    },
   { "SNES (port 3)",           JOY_TYPE_SNESPAD_LPT3,    },
#endif
#ifdef JOYSTICK_DRIVER_PSXPAD
   { "PSX (port 1)",            JOY_TYPE_PSXPAD_LPT1,     }, // PSX
   { "PSX (port 2)",            JOY_TYPE_PSXPAD_LPT2,     },
   { "PSX (port 3)",            JOY_TYPE_PSXPAD_LPT3,     },
#endif
#ifdef JOYSTICK_DRIVER_N64PAD
   { "N64 (port 1)",            JOY_TYPE_N64PAD_LPT1,     }, // N64
   { "N64 (port 2)",            JOY_TYPE_N64PAD_LPT2,     },
   { "N64 (port 3)",            JOY_TYPE_N64PAD_LPT3,     },
#endif
#ifdef JOYSTICK_DRIVER_DB9
   { "DB9 (port 1)",            JOY_TYPE_DB9_LPT1,        }, // DB9
   { "DB9 (port 2)",            JOY_TYPE_DB9_LPT2,        },
   { "DB9 (port 3)",            JOY_TYPE_DB9_LPT3,        },
#endif
#ifdef JOYSTICK_DRIVER_TURBOGRAFX
   { "Turbografx (port 1)",     JOY_TYPE_TURBOGRAFX_LPT1, }, // TURBOGFX
   { "Turbografx (port 2)",     JOY_TYPE_TURBOGRAFX_LPT2, },
   { "Turbografx (port 3)",     JOY_TYPE_TURBOGRAFX_LPT3, },
#endif
#ifdef JOYSTICK_DRIVER_IFSEGA_ISA
   { "SEGA (isa)",              JOY_TYPE_IFSEGA_ISA,      }, // SEGA ISA
#endif
#ifdef JOYSTICK_DRIVER_IFSEGA_PCI
   { "SEGA (pci)",              JOY_TYPE_IFSEGA_PCI,      }, // SEGA PCI
#endif
#ifdef JOYSTICK_DRIVER_IFSEGA_PCI_FAST
   { "SEGA (pci fast)",         JOY_TYPE_IFSEGA_PCI_FAST, }, // SEGA PCI FAST
#endif
#ifdef JOYSTICK_DRIVER_WIN32
   { "Win32 Joystick Driver",   JOY_TYPE_WIN32,           }, // Win32/DirectX
#endif
};

char *joylist_getter(int index, int *list_size)
{
   switch(index){
   case -1:			// Return List Size
      if(list_size){
	 *list_size = (sizeof(joystick_data) / sizeof(GUI_JOY));
      }
      return NULL;
   break;
   case -2:
      FadeGUI();
      DoJoyEdit();
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < (sizeof(joystick_data) / sizeof(GUI_JOY))))
	 return joystick_data[index].name;
      else
	 return NULL;
   break;
   }
}

// joy_name():
// Get card name for card ID

char *joy_name(int index)
{
   int ta,tb;

   tb = (sizeof(joystick_data) / sizeof(GUI_JOY));

   for(ta=0;ta<tb;ta++){
      if(joystick_data[ta].id == (UINT32)index)
	 return joystick_data[ta].name;
   }

   return joystick_data[1].name;	// None
}

int joystick_number(int index)
{
   int ta,tb;

   tb = (sizeof(joystick_data) / sizeof(GUI_JOY));

   for(ta=0;ta<tb;ta++){
      if(joystick_data[ta].id == (UINT32)index)
	 return ta;
   }

   return 1;				// None
}

// joystick_id():
// Get joy ID for joy number

int joystick_id(int index)
{
   int tb;

   tb = (sizeof(joystick_data) / sizeof(GUI_JOY));

   if((index>=0)&&(index<tb)){
      return joystick_data[index].id;
   }

   return joystick_data[1].id;		// None
}

void DoJoyEdit(void)
{
   int ta,tb;
   char *msg;

   ta = joystick_id(joy_select[1].d1);

   remove_joystick();

   JoystickType = JOY_TYPE_NONE;

   switch(ta){
   case JOY_TYPE_NONE:
      JoystickType=JOY_TYPE_NONE;
      return;
   break;
   default:		// Allegro

     show_mouse(NULL);
   if(install_joystick(ta)){
       show_mouse(screen);
      raine_alert(raine_translate_text("Control Error"),raine_translate_text("Unable to initialise Joystick"),allegro_error,NULL,raine_translate_text("&Okay"),NULL,'O',0);
      JoystickType=JOY_TYPE_NONE;
      return;
   }

   if(!(num_joysticks)){
       // show_mouse(screen);
      // raine_alert(raine_translate_text("Control Error"),raine_translate_text("No Joysticks of type"),joy_name(ta),raine_translate_text("could be detected"),raine_translate_text("&Okay"),NULL,'O',0);
      JoystickType=JOY_TYPE_NONE;
      return;
   }

   for(tb=0; tb<num_joysticks; tb++){

     while(joy[tb].flags & JOYFLAG_CALIBRATE){
       msg=((char*)calibrate_joystick_name(tb));
       show_mouse(screen);
       raine_alert(raine_translate_text("Control Setup"),raine_translate_text("Joystick Calibration:"),msg,raine_translate_text("and press space..."),raine_translate_text("Space"),NULL,' ',0);
       show_mouse(NULL);
       if(calibrate_joystick(tb)){
	 show_mouse(screen);
	 raine_alert(raine_translate_text("Control Error"),NULL,raine_translate_text("Joystick Calibration error"),NULL,raine_translate_text("&Okay"),NULL,'O',0);
	 JoystickType=JOY_TYPE_NONE;
	 return;
       }
     }

     printf("joy %d num sticks %d buttons %d\n",tb,joy[tb].num_sticks,
       joy[tb].num_buttons);
     if (joy[tb].num_sticks > 1)
       joy_axis_proc(tb);

     if (joy[tb].num_buttons > 24) {
       char msg[80];
       strcpy(msg,raine_translate_text("Your joystick has more than 24 buttons"));
       sprintf(&msg[strlen(msg)]," (%d)",joy[tb].num_buttons);
       raine_alert(raine_translate_text("Control Error"),NULL,msg,raine_translate_text("Please report the number of buttons to the forum in rainemu.com"),raine_translate_text("&Okay"),NULL,'O',0);
     }
   }

   show_mouse(screen);
   JoystickType=ta;
   return;
   break;
   }
}

int joy_edit_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      DoJoyEdit();
      ret = D_REDRAW;
   }
   return ret;
}

int joy_calib_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      ret=0;
      while((ret!=2)&&(ret!=-1)){
	 joy_select[1].d1 = joystick_number(JoystickType);
	 ret=raine_do_dialog(joy_select,-1);
	 if((ret!=2)&&(ret!=-1)){
	    FadeGUI();
	    DoJoyEdit();
	 }
      }
      ret = D_REDRAW;
   }
   return ret;
}

int game_reset_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      reset_game_hardware();
      ret = D_REDRAW;
   }
   return ret;
}

void DoLangEdit(void)
{
   int ta;
   ta=language_dialog[1].d1;
   if(ta<LanguageSw.Count){
      SetLanguageSwitch(ta);
      reset_game_hardware();
      sprintf(langname,"%s",LanguageSw.Mode[ta]);
   }
}

// language_getter():
// Get mode names for langauge/version select list

char *language_getter(int index, int *list_size)
{
   switch(index){
   case -1:
      *list_size=LanguageSw.Count;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      DoLangEdit();
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index<LanguageSw.Count))
	 return LanguageSw.Mode[index];
      else
	 return NULL;
   break;
   }
}

int language_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      ret=GetLanguageSwitch();
      if(LanguageSw.Count){
	 sprintf(langname,"%s",LanguageSw.Mode[ret]);
	 language_dialog[1].d1=ret;
      }
      else{
	 sprintf(langname,raine_translate_text("<No language switches>"));
      }
      ret=0;
      while((ret!=2)&&(ret!=-1)){
	 ret = raine_do_dialog(language_dialog,-1);
	 if((ret!=2)&&(ret!=-1)){
	    DoLangEdit();
	 }
      }
      return D_REDRAW;
   }
   return ret;
}

int language_sel_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      DoLangEdit();
      return D_REDRAW;
   }
   return ret;
}

// game_setup_proc():
// Does game setup options dialog

int game_setup_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      ret=0;
      game_setup_dialog[5].flags=(disable_irq1 ? 0 : D_SELECTED);
      game_setup_dialog[6].flags=(allowed_speed_hacks ? D_SELECTED : 0);
      while((ret!=2)&&(ret!=-1)){
	 ret = raine_do_dialog(game_setup_dialog,-1);
      }
      disable_irq1 = !(game_setup_dialog[5].flags & D_SELECTED);
      allowed_speed_hacks = game_setup_dialog[6].flags & D_SELECTED;
      return D_REDRAW;
   }
   return ret;
}

// control_setup_proc():
// Does game setup options dialog

int control_setup_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      ret=0;
      while((ret!=2)&&(ret!=-1)){
	 ret=raine_do_dialog(control_setup_dialog,-1);
      }
      return D_REDRAW;
   }
   return ret;
}

// raine_quit_proc():
// Process a click on 'quit raine' button

int raine_quit_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      if((raine_alert(raine_translate_text("Warning"),NULL,raine_translate_text("Quit Raine?"),NULL,raine_translate_text("&Yes"),raine_translate_text("&No"),'Y','N'))!=1){
	 return D_REDRAW;
      }
      else{
	 WantQuit=1;
	 return D_EXIT;
      }
   }
   return ret;
}

// game_play_proc():
// Process a click on 'play game' button

int game_play_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      if(!current_game){
	 raine_alert(raine_translate_text("Error"),raine_translate_text("No Game Loaded"),raine_translate_text("Click on Change Game"),raine_translate_text("to Select a Game."),raine_translate_text("&Okay"),NULL,'O',0);
	 ret = D_REDRAW;
      }
      else{
	 WantPlay = 1;
	 ret = D_EXIT;
      }
   }
   return ret;
}

// real primitive pen allocation

static int used_pens;

int allocate_pens(int pens)
{
   int ret;

   if((used_pens+pens)<=256){
      ret = used_pens;
      used_pens += pens;
   }
   else{
      ret = -1;
   }
   return ret;
}

void free_pens(int pens)
{
   if((used_pens-pens)>=0){
      used_pens -= pens;
   }
}

void free_all_pens(void)
{
   used_pens = 0;
}

// MakeGUIBack():
// Make a faded copy of the game screen to go behind the gui.

static BITMAP *backdrop = NULL;
static PALETTE backdrop_pal;

void MakeGUIBack(void)
{
   BITMAP *gui_backdrop = NULL;

   PALETTE new_pal;
   UINT8 *BIT;
   UINT8 mapcol[256];
   int ccnt,ta,tb,tc,td,te,tcr,tcg,tcb;

   if(screen_valid){

     if (display_cfg.bpp == 8) {
       gui_backdrop = create_bitmap_ex(display_cfg.bpp, display_cfg.screen_x, display_cfg.screen_y);

       free_all_pens();

       memset(new_pal,0x00, 256*4);
       memset(mapcol, 0xFF, 256);

       ccnt=1;	// Black=Colour0

       blit(screen,gui_backdrop,0,0,0,0,display_cfg.screen_x, display_cfg.screen_y);

       for(tb=0;tb<display_cfg.screen_y;tb++){
	 BIT=gui_backdrop->line[tb];
	 for(ta=0;ta<display_cfg.screen_x;ta++){
	   tc=BIT[ta];
	   if((te=mapcol[tc])==255){
	     tcr=pal[tc].r;
	     tcg=pal[tc].g;
	     tcb=pal[tc].b;
	     tcr = (tcr * 64) / 96;
	     if(tcr<0) tcr=0;
	     if(tcr>63) tcr=63;
	     tcg = (tcg * 64) / 80;
	     if(tcg<0) tcg=0;
	     if(tcg>63) tcg=63;
	     tcb = (tcb * 64) / 64;
	     if(tcb<0) tcb=0;
	     if(tcb>63) tcb=63;
	     te=255;
	     for(td=0;td<ccnt;td++){
	       if((tcr==new_pal[td].r)&&(tcg==new_pal[td].g)&&(tcb==new_pal[td].b)){
		 te=td;
		 td=ccnt;
		 mapcol[tc]=te;
	       }
	     }
	     if(te==255){
	       if(ccnt<216){
		 new_pal[ccnt].r=tcr;
		 new_pal[ccnt].g=tcg;
		 new_pal[ccnt].b=tcb;
		 te=ccnt;
		 ccnt++;
	       }
	       else{			// No room! Find a close match... (allegro: slow)
		 te=bestfit_color(new_pal,tcr,tcg,tcb);
	       }
	     }
	   }
	   BIT[ta]=te;
	 }

       }

       memcpy(&gui_pal, &new_pal, ccnt*4);
       allocate_pens(ccnt);
     }

   }
   else{

     // The backdrop image has historically always been 8bpp...
     // For now it's better to keep it this way...
     gui_backdrop = create_bitmap_ex(8, display_cfg.screen_x, display_cfg.screen_y);

     free_all_pens();

     memset(new_pal,0x00, 256*4);
     memset(mapcol, 0xFF, 256);

     ccnt=1;	// Black=Colour0

     if(!backdrop){

       double scalex, scaley,scale;
       int sx,sy;
       BITMAP *bmp = NULL;
       int loaded = 1;

       if(rgui_cfg.bg_image[0]) {
	 int len = strlen(rgui_cfg.bg_image);
	 if (!stricmp(rgui_cfg.bg_image+len-3,"jpg") ||
	     !stricmp(rgui_cfg.bg_image+len-4,"jpeg")) {
	   bmp = load_jpg(rgui_cfg.bg_image, backdrop_pal);
	 }
	 else if (!stricmp(rgui_cfg.bg_image+len-3,"png"))
	   bmp = load_png(rgui_cfg.bg_image, backdrop_pal);
	 else
	   bmp = load_pcx(rgui_cfg.bg_image, backdrop_pal);
       }

       if(!bmp){
	 if (RaineData[Backdrop].type == DAT_BITMAP) {
	   bmp = ((BITMAP *)RaineData[Backdrop].dat);
	   loaded = 0;
	   memcpy(&backdrop_pal, RaineData[Backdrop_pal].dat, 256*4);
	 } else {
	   /* Apparently the jpeg pictures are sometimes truncated at the end for our
	      decoder. Since I am not a jpeg expert, I can't fix the decoder, but I can
	      avoid the segfault by enlarging the buffer */
	   int size = (RaineData[Backdrop].size + 0x30); //  & ~0xff;
	   UINT8 *tmp = malloc(size);
	   memcpy(tmp,RaineData[Backdrop].dat,RaineData[Backdrop].size);
	   bmp = load_memory_jpg(tmp,backdrop_pal);
	   free(tmp);
	 }
       }
       scalex = display_cfg.screen_x * 1.0 / bmp->w;
       scaley = display_cfg.screen_y * 1.0 / bmp->h;
       scale = MIN(scalex,scaley);

       sx = bmp->w * scale;
       sy = bmp->h * scale;

       backdrop = create_bitmap_ex(bitmap_color_depth(bmp),sx,sy);
       stretch_blit(bmp, backdrop, 0,0, bmp->w-1, bmp->h-1, 0,0, sx, sy);
       if (loaded) {
	 destroy_bitmap(bmp);
       }
     }

     clear_to_color(gui_backdrop,getpixel(backdrop,0,0));

     if (bitmap_color_depth(backdrop) == 8) {
       blit(backdrop,gui_backdrop,0,0,(display_cfg.screen_x - backdrop->w)/2,(display_cfg.screen_y - backdrop->h)/2,backdrop->w,backdrop->h);
       for(tb=0;tb<display_cfg.screen_y;tb++){
	 BIT=gui_backdrop->line[tb];
	 for(ta=0;ta<display_cfg.screen_x;ta++){
	   tc=BIT[ta];
	   if((te=mapcol[tc])==255){
	     tcr=backdrop_pal[tc].r;
	     tcg=backdrop_pal[tc].g;
	     tcb=backdrop_pal[tc].b;
	     te=255;
	     for(td=0;td<ccnt;td++){
	       if((tcr==new_pal[td].r)&&(tcg==new_pal[td].g)&&(tcb==new_pal[td].b)){
		 te=td;
		 td=ccnt;
		 mapcol[tc]=te;
	       }
	     }
	     if(te==255){
	       if(ccnt<216){
		 new_pal[ccnt].r=tcr;
		 new_pal[ccnt].g=tcg;
		 new_pal[ccnt].b=tcb;
		 te=ccnt;
		 ccnt++;
	       }
	       else{			// No room! Find a close match... (allegro: slow)
		 te=bestfit_color(new_pal,tcr,tcg,tcb);
	       }
	     }
	   }
	   BIT[ta]=te;
	 }
       }
       memcpy(&gui_pal, &new_pal, ccnt*4);
       allocate_pens(ccnt);
     } else { // bmp color depth != 8
       destroy_bitmap(gui_backdrop);
       gui_backdrop = NULL;
       blit(backdrop,screen,0,0,(display_cfg.screen_x - backdrop->w)/2,(display_cfg.screen_y - backdrop->h)/2,screen->w,screen->h);
     }
   }

   set_palette_range(gui_pal,0,255,1);
   if (gui_backdrop) {
     blit(gui_backdrop,screen,0,0,0,0,display_cfg.screen_x,display_cfg.screen_y);
     destroy_bitmap(gui_backdrop);
     gui_backdrop = NULL;
   }

   if(raine_cfg.hide)
   {
      clear_bitmap(screen);
   }

}

#include "shiftjis.c"

// Setup gui : prepare a dialog to be displayed in the middle of a game
// (outside the main gui loop).

void setup_gui()
{
  if(!raine_cfg.no_gui) {	// GUI MODE
    screen_valid = 1;
    if (!GameMouse)
      install_mouse();
    set_mouse_sprite(RaineData[Mouse].dat); // This is really messy !!!
    MakeGUIBack();
  }
}

// release gui : the opposite function (see above)

void release_gui()
{
  if(!raine_cfg.no_gui) {	// GUI MODE
    reset_palette_map();
    show_mouse(NULL);
  }
  // if (!GameMouse)
  //  remove_mouse();
}

static void setup_screen_name() {
  int rate = get_refresh_rate();
   sprintf(screenname,	raine_translate_text("%s %dx%d %dbpp"), raine_translate_text("Screen:"), display_cfg.screen_x, display_cfg.screen_y, display_cfg.bpp);
   if (rate) sprintf(screenname+strlen(screenname)," %dHz",rate);
   sprintf(screenname+strlen(screenname),"; %s", gfx_card_name(display_cfg.screen_type));
}

// StartGUI():
// Actually does the gui/game loop, called from raine.c
// Caters for command line load and no gui options


int StartGUI(void)
{
   char str[256];

#ifdef RAINE_DEBUG
   print_debug("StartGUI(): START\n");
#endif
   /*----[Joystick Initialisation]----------------*/
   init_joys();

   sprintf(str, "config/language/%s", dir_cfg.language_file);
   raine_push_config_state();
   raine_set_config_file(get_shared(str));

   init_display();

   centre_all_dialogs();

   sprintf(gamename, "%s %s", raine_translate_text("Game:"), raine_translate_text("<No Game Loaded>"));
   setup_screen_name();

   memset(&gui_pal, 0x00, 256*4);

   WantScreen=0;
   WantQuit=0;
   WantPlay=0;

#ifdef RAINE_DEBUG
   print_debug("StartGUI(): prepare international\n");
#endif

   // These 2 functions are in allegro, to install japenese text.
   // Actually it creates problems with accents...
   // register_uformat(U_SJIS, sjis_getc, sjis_getx, sjis_setc, sjis_width, sjis_cwidth, sjis_isok, 2);
   // set_uformat(U_SJIS);
   while(!WantQuit){		// ----- Main Loop ------

     set_sound_variables(0);
     set_gui_palette();
     gui_fg_color = CGUI_COL_TEXT_1;
     gui_bg_color = CGUI_BOX_COL_MIDDLE;

     /* Be carefull here. Windows seems to have very unstable threads. You */
     /* MUST init these in this order, and avoid the mouse in full-screen... */
     install_timer();
     install_keyboard();
     install_mouse();

     if(!raine_cfg.no_gui) {	// GUI MODE
       MakeGUIBack();

       set_mouse_sprite(RaineData[Mouse].dat);
       show_mouse(screen);
     }

   /*

   check for load game request (from the command line)

   */

   if(raine_cfg.req_load_game)

      do_load_game();

   if(!raine_cfg.no_gui)	// GUI MODE
   {

#ifdef RAINE_DEBUG
   print_debug("StartGUI(): raine_do_dialog loop\n");
#endif
      if(!WantScreen)
      {
	if (!is_linear_bitmap(screen) &&
	    (display_cfg.eagle_fx || display_cfg.pixel_double)) {
	  raine_alert(raine_translate_text("Warning"),raine_translate_text("Your screen is not LINEAR"),raine_translate_text("Eagle/Pixel double won't work."),raine_translate_text("Select another graphics driver in Screen Setup."),raine_translate_text("&Okay"),NULL,'O',0);
	}
#ifdef RAINE_DEBUG
	if (goto_debuger)
	  debuger_proc(0,NULL,0);
#endif
	while(raine_do_dialog(main_dialog, -1) == -1)
	  {
	  }
      }

   }
   else 			// NO GUI MODE
   {

   WantQuit=1;

   if(current_game)

      WantPlay = 1;

   else

      WantPlay = 0;

   }

   if(WantScreen){		// Are we here for a screenchange?
      WantScreen=0;
      ScreenChange();
      if (backdrop) {
	destroy_bitmap(backdrop);
	backdrop = NULL;
      }
      set_palette_range(gui_pal,0,255,0);
      setup_screen_name();
  }

   // allegro is so stupid that removing these and then installing them again crashes in linux console
   // remove_mouse();
   clear_keybuf();
   remove_keyboard();
   // remove_timer();

   print_debug("everything removed\n");
   clear_raine_screen();

   print_debug("in text mode\n");
   if(WantPlay){		// Are we able to and wanting to play?
      WantPlay = 0;
      if(run_game_emulation()){ // In no gui mode, tab will reactivate the gui (req. by bubbles)
	 raine_cfg.no_gui = 0;
	 WantQuit = 0;
      }
      screen_valid=1;
   }

   }				// ----- Main Loop -----

   /*

   close down the current game (if there is one)

   */

   if(current_game){

      ClearDefault();

      current_game = NULL;
   }

   print_debug("pop config\n");
   raine_pop_config_state();
   print_debug("returning from StartGUI\n");

   return 0;
}

void init_joys() {
  int i;
  remove_joystick();
   if(JoystickType != JOY_TYPE_NONE){
      if(install_joystick(JoystickType)){
	allegro_message("Error initialising joystick:\n  %s\n\n",allegro_error);
	JoystickType=JOY_TYPE_NONE;
      }
      if(!(num_joysticks)){
	 // allegro_message("No Joysticks Detected\n");
	 JoystickType=JOY_TYPE_NONE;
      }
      else{
	 for(i = 0; i < num_joysticks; i++){
	    if(joy[i].flags & JOYFLAG_CALIBRATE){
	       allegro_message("Joystick %d needs calibrating in the gui\n", i);
	       //JoystickType=0;
	    }
	 }
      }
   }
}
