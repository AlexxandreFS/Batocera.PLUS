#include "../gui/menu.h"

// Part in dsw.c specific to the menu integration...
//
#define MAX_DSW_SETTINGS 64

extern menu_item_t dsw_items[MAX_DSW_SETTINGS];
typedef struct {
  int def, // factory default
    value, // current value
    start, end, // start/end indexes for the masks/bitsets
    address;
} s_dsw;

extern s_dsw dipswitch[MAX_DIPSWITCHES];
extern int dsw_mask[MAX_DSW_SETTINGS], dsw_bitset[MAX_DSW_SETTINGS];

int do_dlg_dsw(int);

