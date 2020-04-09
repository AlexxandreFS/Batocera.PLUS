#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "gui.h"
#include "cheat.h"

#include "arpro.h"

typedef char editf[256];
static editf cheateditname,cheateditaddress,cheateditdata,cheateditinfo,
  cheateditmask;

static char *cheat_size_getter(int index, int *list_size)
{
   static char *list_data[] =
   {
      "1 byte",
      "2 bytes",
      "3 bytes",
      "4 bytes",
   };

   if(index == -1){
      if(list_size)
	 *list_size = sizeof(list_data) / sizeof(char *);
      return NULL;
   }

   if(index >= 0)
      return raine_translate_text(list_data[index]);
   else
      return NULL;
}

#define CHEAT_SIZE 15
#define CHEAT_TYPE 17
#define CHEAT_TYPE_EVERY_5S 20
#define CHEAT_EDIT_FLAGS 22

#define CHEAT_DATA 9
#define CHEAT_MASK 13

void update_editable_status() {
  if (cheatdata_edit_dialog[CHEAT_TYPE+2].flags & D_SELECTED) {
    cheatdata_edit_dialog[CHEAT_DATA-1].dp = "Max:  ";
    cheatdata_edit_dialog[CHEAT_MASK-1].dp = "Min:  ";
    cheatdata_edit_dialog[CHEAT_TYPE_EVERY_5S].flags &= ~D_SELECTED;
  } else {
    cheatdata_edit_dialog[CHEAT_DATA-1].dp = "Data:";
    cheatdata_edit_dialog[CHEAT_MASK-1].dp = "Mask:";
  }
}

int d_watchpoint_proc(int msg, DIALOG *d, int c) {
  int status = cheatdata_edit_dialog[CHEAT_TYPE+1].flags & D_SELECTED;
  int ret = d_raine_check_proc(msg,d,c);
  if ((cheatdata_edit_dialog[CHEAT_TYPE+1].flags & D_SELECTED) && !status)
    // watchpoint selected -> deselect editable
    if (cheatdata_edit_dialog[CHEAT_TYPE+2].flags) {
      cheatdata_edit_dialog[CHEAT_TYPE+2].flags = 0;
      update_editable_status();
      SEND_MESSAGE(&cheatdata_edit_dialog[CHEAT_TYPE+2], MSG_DRAW, 0);
      SEND_MESSAGE(&cheatdata_edit_dialog[CHEAT_DATA-1], MSG_DRAW, 0);
      SEND_MESSAGE(&cheatdata_edit_dialog[CHEAT_MASK-1], MSG_DRAW, 0);
    }
  return ret;
}

int d_editable_proc(int msg, DIALOG *d, int c) {
  int status = cheatdata_edit_dialog[CHEAT_TYPE+2].flags & D_SELECTED;
  int ret = d_raine_check_proc(msg,d,c);
  if ((cheatdata_edit_dialog[CHEAT_TYPE+2].flags & D_SELECTED) != status) {
    // editable selected -> clear watchpoint
    if (cheatdata_edit_dialog[CHEAT_TYPE+1].flags && !status)
      cheatdata_edit_dialog[CHEAT_TYPE+1].flags = 0;
    update_editable_status();
    SEND_MESSAGE(&cheatdata_edit_dialog[CHEAT_TYPE+1], MSG_DRAW, 0);
    SEND_MESSAGE(&cheatdata_edit_dialog[CHEAT_DATA-1], MSG_DRAW, 0);
    SEND_MESSAGE(&cheatdata_edit_dialog[CHEAT_MASK-1], MSG_DRAW, 0);
  }
  return ret;
}

DIALOG cheatdata_edit_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   320,  112,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Cheat Data"},
   { x_raine_button_proc,48,   98,   48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { x_raine_button_proc,104,  98,   48,   16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Cancel"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Cheat Data:"},
   { x_text_proc,        48,   38,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Name:"},
   { x_edit_proc,        80,   38,   6*12, 8,    GUI_COL_TEXT_1,  253,  0,    0,       255,  0,    cheateditname},
   { x_text_proc,        48,   48,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Addr:"},
   { x_edit_proc,        80,   48,   6*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    cheateditaddress},
   { x_text_proc,        48,   58,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Data:"},
   { x_edit_proc,        80,   58,   6*9,  8,    GUI_COL_TEXT_1,  253,  0,    0,       8,    0,    cheateditdata},
   { x_text_proc,        48,   68,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Info:"},
   { x_edit_proc,        80,   68,   6*12, 8,    GUI_COL_TEXT_1,  253,  0,    0,       255,  0,    cheateditinfo},
   { x_text_proc,        48,   78,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Mask:"},
   { x_edit_proc,        80,   78,   6*12, 8,    GUI_COL_TEXT_1,  253,  0,    0,       255,  0,    cheateditmask},

   { x_text_proc, 170,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Size:"},
   { d_raine_list_proc,       170,  36,   64, 30,   255,  GUI_BOX_COL_MIDDLE,    0,    0,       0,    0,    cheat_size_getter, NULL, NULL},
   { x_text_proc, 260,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Type:"},
   { d_raine_check_proc, 260,    46,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "Permanent", NULL, NULL},
   { d_watchpoint_proc, 260,    56,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "Watchpoint", NULL, NULL},
   { d_editable_proc, 260,    66,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "Editable", NULL, NULL},
   { d_raine_check_proc, 260,    76,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "Every 5s", NULL, NULL},

   { x_text_proc, 170,   76,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Editable options:"},
   { d_raine_check_proc, 170,    86,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "+1", NULL, NULL},
   { d_raine_check_proc, 170,    96,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "BCD", NULL, NULL},
   { d_raine_check_proc, 170,   106,64,   9,    255,  GUI_BOX_COL_MIDDLE,    0,    0,       5,    1,    "On change", NULL, NULL},

   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG actionreplay_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   240,  178+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Cheat Control"},
   { d_raine_list_proc,  48,   26+12,224,  112,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    cheatlist_getter},
   { x_raine_button_proc,48,   164+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { cheat_edit_proc,    48,   144+12,56,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'T',  D_EXIT,  0,    0,    "&Toggle"},
   { cheatdata_edit_proc,112,  144+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Edit"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Action Replay cheats:"},
   { x_raine_button_proc,216,  164+12,56,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "&Search>>"},
   { cheat_new_proc,     168,  144+12,32,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'N',  D_EXIT,  0,    0,    "&New"},
   { cheat_del_proc,     208,  144+12,56,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    "Delete"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

int cheat_search_new_proc(int msg, DIALOG *d, int c);
int cheat_search_cont_proc(int msg, DIALOG *d, int c);

DIALOG search_main_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   240,  178+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Cheat Search"},
   { x_raine_button_proc,48,   164+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { cheat_search_new_proc,48, 144+12,64,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'S',  D_EXIT,  0,    0,    "New &Search"},
   { cheat_search_cont_proc,120,144+12,64, 16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'C',  D_EXIT,  0,    0,    "&Continue"},
   { d_raine_list_proc,  48,   26+12,224,  112,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    search_list_getter},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Action Replay results:"},
   { x_raine_button_proc,216,  164+12,56,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Edit>>"},
   { cheat_add_proc,     192,  144+12,64,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'A',  D_EXIT,  0,    0,    "&Add Result"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

char *search_mode_getter(int index, int *list_size);

DIALOG search_mode_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   180,  80+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,   0,    0,       0,    0,    "New Search"},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Choose Search Mode:"},
   { d_raine_list_proc,  48,   26+12,164,  32+4, GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    search_mode_getter},
   { x_raine_button_proc,48,   68+12, 48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

char byte_hex_data[8];
char byte_dec_data[8];
char byte_sgn_data[8];
char byte_asc_data[8];

DIALOG *byte_hex_dialog;
DIALOG *byte_dec_dialog;
DIALOG *byte_sgn_dialog;
DIALOG *byte_asc_dialog;

int byte_hex_edit_proc(int msg, DIALOG *d, int c);
int byte_dec_edit_proc(int msg, DIALOG *d, int c);
int byte_sgn_edit_proc(int msg, DIALOG *d, int c);
int byte_asc_edit_proc(int msg, DIALOG *d, int c);

DIALOG search_type_0a_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   180,  80+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,   0,    0,       0,    0,    "New Search"},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Enter Search Byte:"},
   { x_text_proc,        48,   26+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Hex:"},
   { byte_hex_edit_proc, 48+(6*8),26+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  2,    0,    byte_hex_data},
   { x_text_proc,        48,   36+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Dec:"},
   { byte_dec_edit_proc, 48+(6*8),36+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  3,    0,    byte_dec_data},
   { x_text_proc,        48,   46+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Signed:"},
   { byte_sgn_edit_proc, 48+(6*8),46+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  4,    0,    byte_sgn_data},
   { x_text_proc,        48,   56+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Ascii:"},
   { byte_asc_edit_proc, 48+(6*8),56+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  1,    0,    byte_asc_data},
   { x_raine_button_proc,48,   68+12, 48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

DIALOG search_type_0b_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   180,  80+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,   0,    0,       0,    0,    "Continue Search"},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Enter Search Byte:"},
   { x_text_proc,        48,   26+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Hex:"},
   { byte_hex_edit_proc, 48+(6*8),26+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  2,    0,    byte_hex_data},
   { x_text_proc,        48,   36+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Dec:"},
   { byte_dec_edit_proc, 48+(6*8),36+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  3,    0,    byte_dec_data},
   { x_text_proc,        48,   46+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Signed:"},
   { byte_sgn_edit_proc, 48+(6*8),46+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  4,    0,    byte_sgn_data},
   { x_text_proc,        48,   56+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Ascii:"},
   { byte_asc_edit_proc, 48+(6*8),56+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  1,    0,    byte_asc_data},
   { x_raine_button_proc,48,   68+12, 48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

DIALOG search_type_1a_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   160,  68,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "New Search"},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Search initialized, use"},
   { x_text_proc,        48,   36,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "continue search when the"},
   { x_text_proc,        48,   46,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "search value has changed."},
   { x_raine_button_proc,48,   56,    48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

DIALOG search_type_1b_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   200,  80+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,   0,    0,       0,    0,    "Continue Search"},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Enter difference from last byte:"},
   { x_text_proc,        48,   26+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Hex:"},
   { byte_hex_edit_proc, 48+(6*8),26+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  2,    0,    byte_hex_data},
   { x_text_proc,        48,   36+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Dec:"},
   { byte_dec_edit_proc, 48+(6*8),36+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  3,    0,    byte_dec_data},
   { x_text_proc,        48,   46+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Signed:"},
   { byte_sgn_edit_proc, 48+(6*8),46+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  4,    0,    byte_sgn_data},
   { x_text_proc,        48,   56+12,  0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Ascii:"},
   { byte_asc_edit_proc, 48+(6*8),56+12,6*6,8,   GUI_COL_TEXT_1,  253,  0,    D_EXIT,  1,    0,    byte_asc_data},
   { x_raine_button_proc,48,   68+12, 48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

#define search_type_2a_dialog search_type_1a_dialog

char *search_type_2b_getter(int index, int *list_size);

DIALOG search_type_2b_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   180,  80+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,   0,    0,       0,    0,    "Continue Search"},
   { x_text_proc,        48,   26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Bit status since last search:"},
   { d_raine_list_proc,  48,   26+12,164,  32+4, GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    search_type_2b_getter},
   { x_raine_button_proc,48,   68+12, 48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,      0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

#define search_type_3a_dialog search_type_1a_dialog

char *search_type_3b_getter(int index, int *list_size);

DIALOG search_type_3b_dialog[] =
{
   /* (dialog proc)     (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    0,    180, 80+12,GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,   0,    0,       0,    0,    "Continue Search"},
   { x_text_proc,        8,    16,   0,   8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Byte status since last search:"},
   { d_raine_list_proc,  8,    28,   164, 32+4, GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    search_type_3b_getter},
   { x_raine_button_proc,8,    70,   48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { NULL,               0,    0,    0,   0,     0,    0,   0,   0,       0,    0,    NULL}
};

char *hex_view_getter(int index, int *list_size);

DIALOG hex_view_dialog[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,    10,   284,  200+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "View Memory"},
   { x_raine_button_proc,8,    186+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { d_raine_list_proc,  8,    26+12,268,  156,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    hex_view_getter},
   { x_text_proc,        8,    26,     0,   8,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Memory Dump:"},
   { NULL,               0,    0,      0,   0,     0,    0,  0,    0,       0,    0,    NULL}
};


static UINT32 hex_start;
static UINT32 hex_end;
static UINT32 hex_lines;

char *hex_view_getter(int index, int *list_size)
{
   int ta;
   UINT8 data[8];
   UINT8 state[8+1];

   static char S[128];

   switch(index){
   case -1:			// Return List Size
      *list_size = hex_lines;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&((UINT32)index<hex_lines)){
         sprintf(S,"%06X:",hex_start+(index<<3));
         state[0] = 0;
         for(ta=0;ta<8;ta++){
            data[ta] = gen_cpu_read_byte(hex_start+(index<<3)+ta);
            state[ta+1] = get_address_status(hex_start+(index<<3)+ta);
         }
         for(ta=0;ta<8;ta++){
            if((state[ta])||(state[ta+1]))
               sprintf(S+strlen(S),"*");
            else
               sprintf(S+strlen(S)," ");
            sprintf(S+strlen(S),"%02X",data[ta]);
         }
         if(state[8])
            sprintf(S+strlen(S),"*");
         else
            sprintf(S+strlen(S)," ");
         for(ta=0;ta<8;ta++){
            if((data[ta]>=0x20)&&(data[ta]<=0x7F))
               sprintf(S+strlen(S),"%c",data[ta]);
            else
               sprintf(S+strlen(S),".");
         }
         return S;
      }
      else
         return NULL;
   break;
   }
}

void do_hex_view(UINT32 offset)
{
   hex_start = get_search_range_start(offset);
   hex_end   = get_search_range_end  (offset);
   hex_lines = (hex_end + 1) - (hex_start);
   hex_lines = hex_lines >> 3;

   hex_view_dialog[2].d1 = (offset - hex_start) >> 3;

   if(hex_view_dialog[2].d1 >= 9)
      hex_view_dialog[2].d2 = hex_view_dialog[2].d1 - 9;

   raine_do_dialog(hex_view_dialog,-1);
}

static UINT32 *s_list;

char *search_list_getter(int index, int *list_size)
{
   int ta;
   static char S[128];

   if(match_all_count>0){

   switch(index){
   case -1:			// Return List Size
      if(match_all_count>512){
         *list_size=512;
      }
      else{
         *list_size=match_all_count;
      }
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      ta = search_main_dialog[4].d1;
      if(ta<match_all_count){
         do_hex_view(s_list[ta]);
      }
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index<511)){
         sprintf(S,"%06x: %02x",s_list[index],gen_cpu_read_byte(s_list[index]));
         return(S);
      }
      if(index==511){
         return("......  ..");
      }
      return NULL;
   break;
   }
   }
   else{

   switch(index){
   case -1:			// Return List Size
      *list_size=1;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if(index == 0)
         return raine_translate_text("<No Search Results>");
      else
         return NULL;
   break;
   }

   }
}

static int search_data;
static int ar_window = 0;

char *search_type_2b_getter(int index, int *list_size)
{
   static char *str_list[2] =
   {
      "The bit is unchanged",
      "The bit has flipped",
   };

   switch(index){
   case -1:			// Return List Size
      *list_size = 2;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < 2))
         return raine_translate_text(str_list[index]);
      else
         return NULL;
   break;
   }
}

char *search_type_3b_getter(int index, int *list_size)
{
   static char *str_list[6] =
   {
      "New Byte == Last Byte",
      "New Byte != Last Byte",
      "New Byte <  Last Byte",
      "New Byte <= Last Byte",
      "New Byte >  Last Byte",
      "New Byte >= Last Byte",
   };

   switch(index){
   case -1:			// Return List Size
      *list_size = 6;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < 6))
         return raine_translate_text(str_list[index]);
      else
         return NULL;
   break;
   }
}

char *search_mode_getter(int index, int *list_size)
{
   switch(index){
   case -1:			// Return List Size
      *list_size = SEARCH_MODE_COUNT;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      *list_size = D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index < SEARCH_MODE_COUNT))
         return raine_translate_text(get_search_mode_name(index));
      else
         return NULL;
   break;
   }
}

int byte_hex_edit_proc(int msg, DIALOG *d, int c)
{
   int ta,ret;

   if(msg == MSG_START)
      byte_hex_dialog = d;

   ret = x_edit_proc(msg, d, c);

   if(ret!=D_O_K){

      // Grab byte value

      if(byte_hex_data[0]){
         sscanf(byte_hex_data,"%x",&ta);
         ta &= 0xFF;
      }
      else{
         ta = 0;
      }

      // Fill in alternate byte strings

      sprintf(byte_dec_data,"%d",ta);
      sprintf(byte_sgn_data,"%d",(INT8) ta);
      sprintf(byte_asc_data,"%c",ta);

      // Draw them

      scare_mouse();
      SEND_MESSAGE(byte_dec_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_sgn_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_asc_dialog, MSG_DRAW, 0);
      unscare_mouse();
      dialog_oxygen();

   }
   if(ret==D_CLOSE) ret = D_O_K;

   return ret;
}

int byte_dec_edit_proc(int msg, DIALOG *d, int c)
{
   int ta,ret;

   if(msg == MSG_START)
      byte_dec_dialog = d;

   ret = x_edit_proc(msg, d, c);

   if(ret!=D_O_K){

      // Grab byte value

      if(byte_dec_data[0]){
         sscanf(byte_dec_data,"%d",&ta);
         ta &= 0xFF;
      }
      else{
         ta = 0;
      }

      // Fill in alternate byte strings

      sprintf(byte_hex_data,"%02x", (UINT8) ta);
      sprintf(byte_sgn_data,"%d",   (INT8)  ta);
      sprintf(byte_asc_data,"%c",   (UINT8) ta);

      // Draw them

      scare_mouse();
      SEND_MESSAGE(byte_hex_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_sgn_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_asc_dialog, MSG_DRAW, 0);
      unscare_mouse();
      dialog_oxygen();

   }
   if(ret==D_CLOSE) ret = D_O_K;

   return ret;
}

int byte_sgn_edit_proc(int msg, DIALOG *d, int c)
{
   int ta,ret;

   if(msg == MSG_START)
      byte_sgn_dialog = d;

   ret = x_edit_proc(msg, d, c);

   if(ret!=D_O_K){

      // Grab byte value

      if(byte_sgn_data[0]){
         sscanf(byte_sgn_data,"%d",&ta);
         ta &= 0xFF;
      }
      else{
         ta = 0;
      }

      // Fill in alternate byte strings

      sprintf(byte_hex_data,"%02x", (UINT8) ta);
      sprintf(byte_dec_data,"%d",   (UINT8) ta);
      sprintf(byte_asc_data,"%c",   (UINT8) ta);

      // Draw them

      scare_mouse();
      SEND_MESSAGE(byte_hex_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_dec_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_asc_dialog, MSG_DRAW, 0);
      unscare_mouse();
      dialog_oxygen();

   }
   if(ret==D_CLOSE) ret = D_O_K;

   return ret;
}

int byte_asc_edit_proc(int msg, DIALOG *d, int c)
{
   int ta,ret;

   if(msg == MSG_START)
      byte_asc_dialog = d;

   ret = x_edit_proc(msg, d, c);

   if(ret!=D_O_K){

      // Grab byte value

      ta = byte_asc_data[0];

      // Fill in alternate byte strings

      sprintf(byte_hex_data,"%02x",(UINT8) ta);
      sprintf(byte_dec_data,"%d",  (UINT8) ta);
      sprintf(byte_sgn_data,"%d",  (INT8)  ta);

      // Draw them

      scare_mouse();
      SEND_MESSAGE(byte_hex_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_dec_dialog, MSG_DRAW, 0);
      SEND_MESSAGE(byte_sgn_dialog, MSG_DRAW, 0);
      unscare_mouse();
      dialog_oxygen();

   }
   if(ret==D_CLOSE) ret = D_O_K;

   return ret;
}

int cheat_search_new_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      ret = raine_do_dialog(search_mode_dialog,-1);

      search_mode = search_mode_dialog[2].d1;

      switch(search_mode){
      case SEARCH_MODE_ABSOLUTE:
      ret = raine_do_dialog(search_type_0a_dialog,-1);

      sscanf(byte_hex_data,"%x",&search_data);
      search_data &= 0xFF;

      start_arpro_search( (UINT8) search_data);
      break;
      case SEARCH_MODE_RELATIVE:
      ret = raine_do_dialog(search_type_1a_dialog,-1);

      start_arpro_search(0x00);
      break;
      case SEARCH_MODE_SINGLE_BIT:
      ret = raine_do_dialog(search_type_2a_dialog,-1);

      start_arpro_search(0x00);
      break;
      case SEARCH_MODE_SLOW:
      ret = raine_do_dialog(search_type_3a_dialog,-1);

      start_arpro_search(0x00);
      break;
      default:
      break;
      }

      if(match_all_count>0){
         if(match_all_count>512){
            s_list = get_arpro_results(512);
         }
         else{
            s_list = get_arpro_results(match_all_count);
         }
      }
      SEND_MESSAGE(&search_main_dialog[4], MSG_START, 0);

      return D_REDRAW;
   }
   return ret;
}

int cheat_search_cont_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      switch(search_mode){
      case SEARCH_MODE_ABSOLUTE:
      ret = raine_do_dialog(search_type_0b_dialog,-1);

      sscanf(byte_hex_data,"%x",&search_data);
      search_data &= 0xFF;

      continue_arpro_search( (UINT8) search_data);
      break;
      case SEARCH_MODE_RELATIVE:
      ret = raine_do_dialog(search_type_1b_dialog,-1);

      sscanf(byte_hex_data,"%x",&search_data);
      search_data &= 0xFF;

      continue_arpro_search( (UINT8) search_data);
      break;
      case SEARCH_MODE_SINGLE_BIT:
      ret = raine_do_dialog(search_type_2b_dialog,-1);

      search_data = search_type_2b_dialog[2].d1;
      if(search_data>1) search_data=0;
      if(search_data<0) search_data=0;

      continue_arpro_search( (UINT8) search_data);
      break;
      case SEARCH_MODE_SLOW:
      ret = raine_do_dialog(search_type_3b_dialog,-1);

      search_data = search_type_3b_dialog[2].d1;
      if(search_data>5) search_data=0;
      if(search_data<0) search_data=0;

      continue_arpro_search( (UINT8) search_data);
      break;
      default:
      break;
      }

      if(match_all_count>0){
         if(match_all_count>512){
            s_list = get_arpro_results(512);
         }
         else{
            s_list = get_arpro_results(match_all_count);
         }
      }
      SEND_MESSAGE(&search_main_dialog[4], MSG_START, 0);

      return D_REDRAW;
   }
   return ret;
}

int cheat_main_proc(void)
{
   int ret;

   ret=0;

   while(ret>=0){

      ret = raine_do_dialog(actionreplay_dialog,-1);

      switch(ret){
      case 0x02:	// [Done]
         return -1;
      break;
      case 0x01:	// List Click
         DoCheatEdit();
      break;
      case 0x06:	// [Search>>]
         ar_window = 1;
         ret = -1;
      break;
      }

   }
   return 0;
}

int cheat_search_proc(void)
{
   int ret;

   ret=0;

   while(ret>=0){

      sprintf(cheateditdata,"%02x",search_data);

      if(match_all_count>0){
         if(match_all_count>512){
            s_list = get_arpro_results(512);
         }
         else{
            s_list = get_arpro_results(match_all_count);
         }
      }

      ret = raine_do_dialog(search_main_dialog,-1);

      sscanf(cheateditdata,"%x",&search_data);
      search_data&=0xFF;

      switch(ret){
      case 0x01:	// [Done]
         return -1;
      break;
      case 0x06:	// [Edit>>]
         ar_window = 0;
         ret = -1;
      break;
      }

   }
   return 0;
}

int do_cheat_data_edit(int ta)
{
   int ret;

      if(ta<CheatCount){
         sprintf(cheateditname,"%s",CheatList[ta].name);
         sprintf(cheateditaddress,"%08x",CheatList[ta].address);
         sprintf(cheateditdata,"%02x",CheatList[ta].data);
         sprintf(cheateditmask,"%02x",CheatList[ta].mask);
         sprintf(cheateditinfo,"%s",CheatList[ta].info);
	 cheatdata_edit_dialog[CHEAT_SIZE].d1 = CheatList[ta].type & 3;
	 cheatdata_edit_dialog[CHEAT_TYPE].flags =
	   cheatdata_edit_dialog[CHEAT_TYPE+1].flags =
	   cheatdata_edit_dialog[CHEAT_TYPE+2].flags =
	   cheatdata_edit_dialog[CHEAT_TYPE_EVERY_5S].flags = 0;

	 cheatdata_edit_dialog[CHEAT_EDIT_FLAGS].flags =
	   (CheatList[ta].type & CHEAT_EDIT_BASE ? D_SELECTED : 0);

	 cheatdata_edit_dialog[CHEAT_EDIT_FLAGS+1].flags =
	   (CheatList[ta].type & CHEAT_EDIT_BCD ? D_SELECTED : 0);

	 cheatdata_edit_dialog[CHEAT_EDIT_FLAGS+2].flags =
	   (CheatList[ta].type & CHEAT_EDIT_ONCHANGE ? D_SELECTED : 0);

	 if (CheatList[ta].type & CHEAT_WATCH) // watchpoint
	   cheatdata_edit_dialog[CHEAT_TYPE+1].flags = D_SELECTED;
	 else {
	   if (CheatList[ta].type & CHEAT_EDITABLE) {
	     cheatdata_edit_dialog[CHEAT_TYPE+2].flags = D_SELECTED;
	   }
	   update_editable_status();
	 }

	 if (!(CheatList[ta].type & CHEAT_1_TIME))
	   cheatdata_edit_dialog[CHEAT_TYPE].flags = D_SELECTED;
	 if ((CheatList[ta].type & CHEAT_EVERY_5S))
	   cheatdata_edit_dialog[CHEAT_TYPE_EVERY_5S].flags = D_SELECTED;

         ret = raine_do_dialog(cheatdata_edit_dialog,-1);

         if(ret==1){

            sprintf(CheatList[ta].name,"%s",cheateditname);
            sscanf(cheateditaddress,"%x",&CheatList[ta].address);
            sscanf(cheateditdata,"%x",&CheatList[ta].data);
            sscanf(cheateditmask,"%x",&CheatList[ta].mask);
            sprintf(CheatList[ta].info,"%s",cheateditinfo);
	    CheatList[ta].type = cheatdata_edit_dialog[CHEAT_SIZE].d1 & 3;
	    if (CheatList[ta].mask) CheatList[ta].type |= 4;

	    if (!(cheatdata_edit_dialog[CHEAT_TYPE].flags)) {
	      CheatList[ta].type |= CHEAT_1_TIME; // Temporary
	    }
	    if ((cheatdata_edit_dialog[CHEAT_TYPE_EVERY_5S].flags & D_SELECTED)) {
	      CheatList[ta].type |= CHEAT_EVERY_5S;
	    }

	    if (cheatdata_edit_dialog[CHEAT_TYPE+1].flags)
	      CheatList[ta].type |= CHEAT_WATCH; // Watchpoint
	    else if (cheatdata_edit_dialog[CHEAT_TYPE+2].flags) {
	      CheatList[ta].type |= CHEAT_EDITABLE;

	      // This type takes some flags...

	      if (cheatdata_edit_dialog[CHEAT_EDIT_FLAGS].flags)
		CheatList[ta].type |= CHEAT_EDIT_BASE;
	      if (cheatdata_edit_dialog[CHEAT_EDIT_FLAGS+1].flags)
		CheatList[ta].type |= CHEAT_EDIT_BCD;
	      if (cheatdata_edit_dialog[CHEAT_EDIT_FLAGS+2].flags)
		CheatList[ta].type |= CHEAT_EDIT_ONCHANGE;
	    }

            return 1;
         }
         else{
            return 0;
         }
      }
      else{
         return 0;
      }
}

int cheatdata_edit_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      ret = do_cheat_data_edit(actionreplay_dialog[1].d1);

      return D_REDRAW;
   }
   return ret;
}

char *cheatlist_getter(int index, int *list_size)
{
   static char S[128];

   if(CheatCount){

   switch(index){
   case -1:			// Return List Size
      *list_size=CheatCount;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      DoCheatEdit();
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index<CheatCount)){

         sprintf(S,"%-29s", CheatList[index].name);
         S[29] = 0;

         if(CheatList[index].active) {
            sprintf(S+strlen(S)," %s", raine_translate_text("On"));
	 }
         else
            sprintf(S+strlen(S)," %s", raine_translate_text("Off"));

         return S;
      }
      else
         return NULL;
   break;
   }
   }
   else{

   switch(index){
   case -1:			// Return List Size
      *list_size=1;
      return NULL;
   break;
   case -2:			// Act upon List Object Selection
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if(index == 0)
         return raine_translate_text("<No Cheats Mapped>");
      else
         return NULL;
   break;
   }

   }
}

void DoCheatEdit(void)
{
   int ta;

   ta=actionreplay_dialog[1].d1;

   if(ta<CheatCount){
      CheatList[ta].active^=1;
      if (CheatList[ta].active) {
	// Cheat editable -> we must ask the value...
	if (CheatList[ta].type & CHEAT_EDITABLE) {
	  char text[10];
	  int val;
	  get_cheat_hex_value(ta,text);
	  sscanf(text,"%x",&val);
	  CheatList[ta].old_value = val;
	  if (CheatList[ta].type & CHEAT_EDIT_BCD)
	    val = ((val >> 4)*10)+(val & 0xf);
	  if (CheatList[ta].type & CHEAT_EDIT_BASE)
	    val++;
	  val = raine_edit_int("Cheat value", CheatList[ta].name,
			       "&Ok","&Canel",'O','C',
			       CheatList[ta].mask, // inf
			       CheatList[ta].data, // supp
			       val); // default
	  if (CheatList[ta].type & CHEAT_EDIT_BASE)
	    val--;
	  if (CheatList[ta].type & CHEAT_EDIT_BCD)
	    val = ((val/10)<<4) + (val%10);
	  CheatList[ta].edit_value = val;
	}
      }
   }
}

int cheat_edit_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      DoCheatEdit();
      return D_REDRAW;
   }
   return ret;
}

void do_cheat_add(UINT32 addr, UINT8 data)
{
   int ta, ret;

      if(CheatCount<CHEAT_MAX){
         ta = CheatCount;
         CheatCount++;

         sprintf(CheatList[ta].name,"New Cheat %d",ta);
         CheatList[ta].address = addr;
         CheatList[ta].data    = data;
         CheatList[ta].mask    = 0xFF;
         CheatList[ta].type    = 0x00;
         CheatList[ta].info[0] = 0;
         CheatList[ta].active  = 0;

         ret = do_cheat_data_edit(ta);

         if( ret != 1) CheatCount--;
      }
}

int cheat_add_proc(int msg, DIALOG *d, int c)
{
   int ta;
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      ta = search_main_dialog[4].d1;

      if(ta<match_all_count){

      do_cheat_add(s_list[ta], gen_cpu_read_byte(s_list[ta]));

      }

      return D_REDRAW;
   }
   return ret;
}

int cheat_new_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      do_cheat_add(0,0);

      return D_REDRAW;
   }
   return ret;
}

void DoCheatDelete(void)
{
   int ta,tb;

   ta=actionreplay_dialog[1].d1;

   if(ta<CheatCount){
      if((raine_alert(raine_translate_text("Warning"),raine_translate_text("Really delete this cheat"),raine_translate_text("permanently?"),NULL,raine_translate_text("&Yes"),raine_translate_text("&No"),'Y','N'))==1){
         for(tb=ta; tb<(CheatCount-1); tb++){
            memcpy(&CheatList[tb], &CheatList[tb+1], sizeof(CHEAT));
         }
         CheatCount--;
      }
   }
}

int cheat_del_proc(int msg, DIALOG *d, int c)
{
   int ret=x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      DoCheatDelete();
      return D_REDRAW;
   }
   return ret;
}

int actionreplay_proc(int msg, DIALOG *d, int c)
{
   int ta;

   int ret=x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();

      ta=0;
      while(ta==0){

      switch(ar_window){
         case 0x00:
            ta = cheat_main_proc();
         break;
         case 0x01:
            ta = cheat_search_proc();
         break;
      }

      }
      return D_REDRAW;
   }
   return ret;
}
