
#ifdef __cplusplus
extern "C" {
#endif
/*
 *  Stuff for the raine gui, mostly dialog data
 */

#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#ifdef RAINE_DEBUG
#include "dbg_gui.h"
#endif

char gamename[96];
char screenname[96];
char soundname[96];
static char hiscores[10],cheats[9],rom_region[8],dips[6];
char langname[80];

int dir_edit_proc(int msg, DIALOG *d, int c);

int screen_select_proc(int msg, DIALOG *d, int c);

int raine_quit_proc(int msg, DIALOG *d, int c);

int game_play_proc(int msg, DIALOG *d, int c);

int sound_radio_proc(int msg, DIALOG *d, int c);
int status_radio_proc(int msg, DIALOG *d, int c);
int year_radio_proc(int msg, DIALOG *d, int c);
int game_radio_proc(int msg, DIALOG *d, int c);
int res_radio_proc(int msg, DIALOG *d, int c);

int game_select_proc(int msg, DIALOG *d, int c);
const char *listbox_getter(int index, int *list_size);
char *game_company_getter(int index, int *list_size);

char *game_type_getter(int index, int *list_size);
char *status_getter(int index, int *list_size);

int joy_calib_proc(int msg, DIALOG *d, int c);
char *joylist_getter(int index, int *list_size);
int joy_edit_proc(int msg, DIALOG *d, int c);
void DoJoyEdit(void);

int game_reset_proc(int msg, DIALOG *d, int c);

int game_setup_proc(int msg, DIALOG *d, int c);

int control_setup_proc(int msg, DIALOG *d, int c);

int romdir_edit_proc(int msg, DIALOG *d, int c);

char romedit[4][256];

char *language_getter(int index, int *list_size);
int language_proc(int msg, DIALOG *d, int c);

int language_sel_proc(int msg, DIALOG *d, int c);

int load_game_proc(int msg, DIALOG *d, int c);

int auto_select_proc(int msg, DIALOG *d, int c);
char *autolist_getter(int index, int *list_size);
int auto_edit_proc(int msg, DIALOG *d, int c);
int game_select_opts_proc(int msg, DIALOG *d, int c);


#include "about.h"
#include "sound.h"
#include "keys.h"
#include "joystick.h"
#include "cheat.h"
#include "dlg_dsw.h"

typedef char gamestr[256];

extern gamestr game_select_string1;
extern gamestr game_company,game_year,game_sound,game_strtype;

// Main game listbox index
#define GAME_LIST 1
#define GAME_SWITCH_RES 10
#define GAME_DATA 14 // index of data info fields (start)
#define GAME_BITMAP 19

DIALOG game_select_opts[] =
  {
   // Type of the game, status
   { d_raine_window_proc,25,   00,   260,  145,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Selection options"},

   // Sound
   { x_text_proc,             33,    20,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Sound:"},
   { sound_radio_proc,    33,  30,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  1,    1,    "Any"},
   { sound_radio_proc,    33,  40,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  1,    1,    "With"},
   { sound_radio_proc,    33,  50,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  1,    1,    "Without"},

   // Working
   { x_text_proc,             98,    20,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Working:"},
   { status_radio_proc,    98,  30,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  2,    1,    "Yes"},
   { status_radio_proc,    98,  40,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  2,    1,    "Partial"},
   { status_radio_proc,    98,  50,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  2,    1,    "No"},

   // year
   { x_text_proc,         166,    20,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,    0,  0,       0,    0,    "Year"},
   { year_radio_proc,    166,  30,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  3,    1,    "Any"},
   { year_radio_proc,    166,  40,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  3,    1,    ">=1990"},
   { year_radio_proc,    166,  50,64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  3,    1,    "<1990"},

   { x_raine_button_proc,232,   35,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'L',  D_EXIT,  0,    0,    "&Ok"},

   { x_text_proc,             33,  70,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Type:"},
   { d_raine_list_proc,       33,   80,  90,   50,   255,  GUI_BOX_COL_MIDDLE,    0,    D_EXIT,       0,    0,    game_type_getter},

   { x_text_proc,             150,  70,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    "Company:"},
   { d_raine_list_proc,       150,   80,  130,   50,   255,  GUI_BOX_COL_MIDDLE,    0,    D_EXIT,       0,    0,    game_company_getter},

   //{ x_raine_button_proc,  8, 128,  32,  16, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Okay"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}

  };

static int all_drivers();
static int cave_driver();
static int cps1_driver();
static int cps2_driver();
static int megasys1_driver();
static int nmk_driver();
static int pacman_driver();
static int psikyo_driver();
static int seta_driver();
static int taito_f2_driver();
static int lsystem_driver();
static int xsystem2_driver();
static int toaplan1_driver();
static int toaplan2_driver();

static MENU drivers_menu[32] =
{
   { "All drivers",  all_drivers,           NULL,       0, NULL  },
   { "Cave",  cave_driver,           NULL,       0, NULL  },
   { "Capcom CPS1",  cps1_driver,           NULL,       0, NULL  },
   { "Capcom CPS2",  cps2_driver,           NULL,       0, NULL  },
   { "Jaleco Megasystem-1",  megasys1_driver,           NULL,       0, NULL  },
   { "NMK",  nmk_driver,           NULL,       0, NULL  },
   { "Pac-man/Pengo",  pacman_driver,           NULL,       0, NULL  },
   { "Psikyo", psikyo_driver, NULL, 0, NULL },
   { "Seta", seta_driver, NULL, 0, NULL },
   { "Taito F2", taito_f2_driver, NULL, 0, NULL },
   { "Taito L-System",  lsystem_driver,           NULL,       0, NULL  },
   { "Taito X-System 2",  xsystem2_driver,           NULL,       0, NULL  },
   { "Toaplan 1",  toaplan1_driver,           NULL,       0, NULL  },
   { "Toaplan 2",  toaplan2_driver,           NULL,       0, NULL  },
  { NULL,                          NULL,             NULL,       0, NULL  }
};

static MENU menu[32] =
{
   { "",                       NULL,             drivers_menu,  0, NULL  },
   { NULL,                          NULL,             NULL,       0, NULL  }
};

// Size of the game list box
#define GLIST_SIZE 11

DIALOG game_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,5,   00,   312,  230,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Change/Load ROM"},

   { d_raine_list_proc,  13,   35,   224,  GLIST_SIZE*8, GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  GUI_COL_TEXT_1,  0,    listbox_getter},
   { x_raine_button_proc,13,   189,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'L',  D_EXIT,  0,    0,    "&Load"},
   { x_raine_button_proc,13+56,189,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Cancel"},
   { x_text_proc,        250,  20,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Game List:"},
   { game_radio_proc,    250,  30,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    1,    "Full"},
   { game_radio_proc,    250,  40,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    1,    "Available"},
   { game_radio_proc,    250,  50,  64,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    1,    "Missing"},
   { romdir_edit_proc,   13+56,169,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Dirs"},
   { x_text_proc,        13,   155,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    game_select_string1},

   // Info about selection
   { x_text_proc,        13,  130,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Company:"},
   { x_text_proc,        155,  140,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Year:"},
   { x_text_proc,        155,  130,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Sound:"},
   { x_text_proc,        13,  140,  1,    1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Type:"},

   // Data fields for info
   { x_text_proc,        60,  130,  1,    1,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    game_company},
   { x_text_proc,        200,  140,  1,    1,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    game_year},
   { x_text_proc,        200,  130,  1,    1,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    game_sound},
   { x_text_proc,        60,  140,  1,    1,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    game_strtype},

   // I put the selection button at the end to avoid to change all the
   // indexes...
   { game_select_opts_proc,   13,169,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "&Selection"},
   { d_bitmap_proc,      155,   150, 130,   76,    0,               0,                   0,    0,       0,    0,    NULL},

   { d_menu_proc,       13,    20,    0,    0,    0,    0,    0,       0,          0,             0,       menu,             NULL, NULL  },


   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG romdir_edit_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   208,  96,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Directories"},
   { x_raine_button_proc,48,   82,   48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { x_raine_button_proc,104,  82,   48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Cancel"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Rom Directories:"},
   { x_edit_proc,        48,   38,   6*30, 8,    GUI_COL_TEXT_1,  253,  0,    0,       240,  0,    romedit[0]},
   { x_edit_proc,        48,   48,   6*30, 8,    GUI_COL_TEXT_1,  253,  0,    0,       240,  0,    romedit[1]},
   { x_edit_proc,        48,   58,   6*30, 8,    GUI_COL_TEXT_1,  253,  0,    0,       240,  0,    romedit[2]},
   { x_edit_proc,        48,   68,   6*30, 8,    GUI_COL_TEXT_1,  253,  0,    0,       240,  0,    romedit[3]},
   { dir_edit_proc,      232,  38,   8,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    " "},
   { dir_edit_proc,      232,  48,   8,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  1,    0,    " "},
   { dir_edit_proc,      232,  58,   8,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  2,    0,    " "},
   { dir_edit_proc,      232,  68,   8,    8,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  3,    0,    " "},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG joy_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   240,  178+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Joystick Selection"},
   { d_raine_list_proc,  48,   26+12,224,  132,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    joylist_getter},
   { x_raine_button_proc,48,   164+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { joy_edit_proc,      104,  164+12,72,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Calibrate"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Choose Joystick:"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG auto_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   240,  158+16,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Autofire Setup"},
   { d_raine_list_proc,  48,   26+12,224,  112,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    autolist_getter},
   { x_raine_button_proc,48,   144+16,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { auto_edit_proc,     104,  144+16,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Edit"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Autofire Speeds:"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG language_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   240,  178+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "ROM Switches"},
   { d_raine_list_proc,  48,   26+12,224,  100,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    language_getter},
   { x_raine_button_proc,48,   164+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { language_sel_proc,  102,  164+12,56,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "&Select"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Change ROM Version:"},
   { x_text_proc,        48,   150,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Current:"},
   { x_text_proc,        48,   160,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    langname},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG loading_dialog[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)             (bg)                 (key) (flags)  (d1)  (d2)  (dp1)   (dp2) (dp3)  */
   { d_raine_window_proc,0,    0,    160,  50,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Load Game", NULL, NULL},
   { x_ctext_proc,       80,   18,   0,    0,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "", NULL, NULL},
   { d_progress_proc,    16,   32,   128,  8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL, NULL, NULL},
   { load_game_proc,     0,    0,    0,    0,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL, NULL, NULL},
   { x_ctext_proc,       80,   32,   0,    0,    GUI_COL_TEXT_2,  -1,  0,    0,       0,    0,    "", NULL, NULL},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL, NULL, NULL}
};

DIALOG game_setup_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    0,    110,  140,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Game Setup"},
   { x_text_proc,        8,    16,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Select:"},
   { x_raine_button_proc,8,    96+20,48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'B',  D_EXIT,  0,    0,    "&Back"},
   { game_reset_proc,    8,    16+12,84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',  D_EXIT,  0,    0,    "&Reset Game"},
   { actionreplay_proc,  8,    56+12,84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'A',  D_EXIT,  0,    0,    "&Action Replay"},
   { d_raine_check_proc, 8,    56+28+7,  84,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Neogeo Rasters"},
   { d_raine_check_proc, 8,    56+37+7,  84,   9,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       1,    1,    "Speed hacks"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};


DIALOG control_setup_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    0,    110,  140,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Controls"},
   { x_text_proc,        8,    16,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Select:"},
   { x_raine_button_proc,8,    116,  48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'B',  D_EXIT,  0,    0,    "&Back"},
   { input_select_proc,  8,    16+12,94,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'K',  D_EXIT,  0,    0,    "&Keyboard Setup"},
   { joy_select_proc,    8,    36+12,94,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'J',  D_EXIT,  0,    0,    "&Joystick Setup"},
   { auto_select_proc,   8,    56+12,94,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'A',  D_EXIT,  0,    0,    "&Autofire Setup"},
   { joy_calib_proc,     8,    76+12,94,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "Joystick &Select"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

#ifndef NEW_DLG
DIALOG main_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp1) (dp2) (dp3) */
   { d_yield_proc,      16,    0,    280,    220,    0,    0,    0,    0,       0,    0,    NULL},
#if 0
   { d_raine_window_proc, 16,  160,    256,  60,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Raine " VERSION " (c)1998-2001 " HANDLE },
   { x_ctext_proc,       128,  180,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    gamename, NULL, NULL},
   { x_ctext_proc,       128,  190,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    screenname, NULL, NULL},
   { x_ctext_proc,       128,  200,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    soundname, NULL, NULL},
   { game_play_proc,     16,   16,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'P',  D_EXIT,  0,    0,    "&Play Game", NULL, NULL},
   { game_select_proc,   16,   36,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'G',  D_EXIT,  0,    0,    "Change &Game", NULL, NULL},
   { control_setup_proc, 16,   56,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Control Setup", NULL, NULL},
   { game_setup_proc,    16,   76,  84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'M',  D_EXIT,  0,    0,    "Ga&me Setup", NULL, NULL},
   { screen_select_proc, 156,  16,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "&Screen Setup", NULL, NULL},
   { sound_setup_proc,   156,  36,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "S&ound Setup", NULL, NULL},
   { about_proc,         156,  56,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'A',  D_EXIT,  0,    0,    "&About Raine", NULL, NULL},
   { raine_quit_proc,    156,  76,  84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'Q',  D_EXIT,  0,    0,    "&Quit Raine", NULL, NULL},
#ifdef RAINE_DEBUG
   { debuger_proc,    156,   76,  84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Debuger", NULL, NULL},
#endif
   { NULL,              0,    0,    0,    0,    0,    0,    0,    0,       0,                      0,    NULL,             NULL, NULL  }
#else
   { d_raine_box_proc,   16,   160,  320-32,64,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { game_play_proc,     16,   16,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'P',  D_EXIT,  0,    0,    "&Play Game"},
   { game_select_proc,   16,   46,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'G',  D_EXIT,  0,    0,    "Change &Game"},
   { control_setup_proc, 16,   76,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Control Setup"},
   { raine_quit_proc,    16,   106,  84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'Q',  D_EXIT,  0,    0,    "&Quit Raine"},
   { screen_select_proc, 220,  16,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "&Screen Setup"},
   { sound_setup_proc,   220,   46,   84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "S&ound Setup"},
   { game_setup_proc,    220,   76,  84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'M',  D_EXIT,  0,    0,    "Ga&me Setup"},
#ifdef RAINE_DEBUG
   { debuger_proc,    220, 106,  84,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Debuger", NULL, NULL},
#endif
   { x_text_proc,        24,   196,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    ""},
   { x_text_proc,        24,   166,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    gamename},
   { x_text_proc,        24,   176,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    screenname},
   { x_text_proc,        24,   186,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    soundname},
   { x_text_proc,       50,   202,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    hiscores},
   { x_text_proc,       115,   198,  50,    16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'H',    D_EXIT,       0,    0,    cheats},
   { d_raine_oxygen_proc,16,   160,  8,    8,    0,    0,    0,    0,       0,    0,    NULL},
   { about_proc,         24,   202,  18,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  '?',  D_EXIT,  0,    0,    "?!"},
   { x_text_proc,       175,   198,  50,    16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'R',    D_EXIT,       0,    0,    rom_region},
   { x_text_proc,       235,   198,  30,    16,    GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',    D_EXIT,       0,    0,    dips},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
#endif
};
#else // OLD_DLG

static MENU game_menu[] =
{
  { "Change &Game",		game_select_proc,	NULL,	0, NULL },
  { "&Play Game",		game_play_proc,		NULL,	0, NULL },
  { "",				NULL,			NULL,	0, NULL },
  { "Quick Load",		GameLoad,		NULL,	0, NULL },
  { "Load from...",		GameLoadName,		NULL,	0, NULL },
  { "Load Demo",		GameLoadDemo,		NULL,	0, NULL },
  { "",				NULL,			NULL,	0, NULL },
  { "Change Game Slot",		next_save_slot,		NULL,	0, NULL },
  { "",				NULL,			NULL,   0, NULL },
  { "Quick save",		GameSave,		NULL,   0, NULL },
  { "Save as...",		GameSaveName,		NULL,	0, NULL },
  { "Save Demo",		GameSaveDemo,		NULL,	0, NULL },
  { "Quit",			raine_quit_proc,	NULL,	0, NULL },
  { NULL,			NULL,			NULL,	0, NULL },
};

static MENU settings_menu[] =
{
  { "Game",			game_setup_proc,	NULL,	0, NULL },
  { "Controls",			control_setup_proc,	NULL,	0, NULL },
  { "Screen",			screen_setup_proc,	NULL,	0, NULL },
  { "Sound",			sound_setup_proc,	NULL,	0, NULL },
  { NULL,			NULL,			NULL, 	0, NULL },
};

static MENU about_menu[] =
{
  { "Raine",			about_proc,	NULL,		0, NULL },
  { "Game",			game_about_proc,NULL,		0, NULL },
  { NULL,			NULL,		NULL,		0, NULL },
};

static MENU menu[] =
{
  { "&Game",			NULL,		game_menu,	0, NULL },
  { "&Settings",		NULL,		settings_menu,	0, NULL },
  {" &About",			NULL,		about_menu,	0, NULL },
};

DIALOG main_dialog[] =
{
   { d_raine_box_proc,   16,   160,  320-32,64,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { d_menu_proc,       0,    0,    0,    0,    0,    0,    0,       0,
     0,             0,       menu,             NULL, NULL  },
   { x_text_proc,        24,   196,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    ""},
   { x_text_proc,        24,   166,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    gamename},
   { x_text_proc,        24,   176,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    screenname},
   { x_text_proc,        24,   186,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    soundname},
   { x_text_proc,       50,   202,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    hiscores},
   { x_text_proc,       120,   202,  0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    cheats},
   { d_raine_oxygen_proc,16,   160,  8,    8,    0,    0,    0,    0,       0,    0,    NULL},
   { about_proc,         24,   202,  18,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  '?',  D_EXIT,  0,    0,    "?!"},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};
#endif

DIALOG load_problem[] =
{
   /* (dialog proc)      (x)  (y)  (w)  (h) (fg) (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,  0,   0, 316, 152, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Error Report"},
   { x_raine_button_proc,  8, 128,  32,  16, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Okay"},
   { d_raine_textbox_proc, 8,  20, 300, 102, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { NULL,               0,    0,    0,    0,    0,               0,                   0,    0,       0,    0,    NULL}
};

extern DIALOG file_selector[];
extern DIALOG about_cpus[];
extern DIALOG gfx_mode_dialog[];
#ifdef RAINE_DEBUG
extern DIALOG debuger_gui[],regs_gui[];
extern DIALOG break_gui[];
#endif

DIALOG *raine_dialog_list[] =
{
   about_raine,
   about_game,
   game_select,
   game_select_opts,
   romdir_edit_dialog,
   input_select,
   joy_input_select,
   joy_axis_select,
   joy_select,
   auto_select,
   cheatdata_edit_dialog,
   actionreplay_dialog,
   search_main_dialog,
   search_mode_dialog,
   search_type_0a_dialog,
   search_type_0b_dialog,
   search_type_1a_dialog,
   search_type_1b_dialog,
   search_type_2b_dialog,
   search_type_3b_dialog,
   dsw_select,
   language_dialog,
   key_editing,
   joy_key_editing,
   loading_dialog,
   game_setup_dialog,
   sound_setup_dialog,
   control_setup_dialog,
   main_dialog,
   load_problem,
   hex_view_dialog,
   file_selector,
   gfx_mode_dialog,
#ifdef RAINE_DEBUG
   regs_gui,
   debuger_gui,
   break_gui,
#endif
   about_cpus,
   NULL,
};


#ifdef __cplusplus
}
#endif
