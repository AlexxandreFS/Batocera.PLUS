#include "../gui/menu.h"
#include "dsw.h"
#include "dlg_dsw.h"

class Tdlg_dsw : public TMenu
{
  public:
    Tdlg_dsw(char *name, menu_item_t *menu) :
      TMenu(name,menu)
    {}
    void validate_dsw();
    // The ackward explicit call to validate dsw in the 2 following functions
    // is because next_list_item never calls exec_menu_item or there would
    // be an infinite loop (because exec_menu_item calls next_list_item !)
    // So this seems to be the easiest workaround...
    void next_list_item() {
      TMenu::next_list_item();
      validate_dsw();
    }
    void prev_list_item() {
      TMenu::prev_list_item();
      validate_dsw();
    }
};

void Tdlg_dsw::validate_dsw() {
  int index;
  // 1st : find the dsw index corresponding to the current sel
  for (index = 0; index < MAX_DIPSWITCHES; index++) {
    if (sel >= dipswitch[index].start && sel <= dipswitch[index].end)
      break;
  }

  dipswitch[index].value = (dipswitch[index].value & (~dsw_mask[sel])) |
    dsw_bitset[sel];
  write_dsw(index);
  draw(); // In case the dsw tests itself (see galmedes)
}

int do_dlg_dsw(int sel) {
  Tdlg_dsw *dlg = new Tdlg_dsw(_("Dipswitches"),dsw_items);
  dlg->execute();
  delete dlg;
  return 0;
}


