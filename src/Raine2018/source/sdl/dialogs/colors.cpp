#include "sdl/gui/menu.h"
#include "sdl/compat.h"
#include "sdl/gui/tfont.h"
#include "sdl/dialogs/colors.h"

static int r,g,b,a,cindex;

class TColorDlg : public TDialog
{
  private:
    int counter;
  public:
  TColorDlg(char *my_title, menu_item_t *mymenu) :
    TDialog(my_title, mymenu)
  {
    counter=0;
  }
  void set_fgcolor(int col) {
    fg = col;
  }
  void set_bgcolor(int col) {
    bg = col;
  }
  void update_fg_layer(int nb_to_update) {
    TDialog::update_fg_layer(nb_to_update);
    if (nb_to_update >= 0) {
      if (counter++ == 16) {
	draw();
	counter = 0;
      }
    }
  }
};

static TColorDlg *dlg;

static int set_gui_color(int sel);

static menu_item_t colors_dlg[] =
{
    { _("color"), NULL, NULL, },
{  _("red"), &set_gui_color, &r, ITEM_SLIDER, {255, 16, 300, 0, 0, 0} },
{  _("green"), &set_gui_color, &g, ITEM_SLIDER, {255, 16, 300, 0, 0, 0} },
{  _("blue"), &set_gui_color, &b, ITEM_SLIDER, {255, 16, 300, 0, 0, 0} },
{  _("alpha"), &set_gui_color, &a, ITEM_SLIDER, {255, 16, 300, 0, 0, 0} },
{ NULL, NULL, NULL }
};

static char color_label[25];

static int set_gui_color(int sel) {
  int color = a | (b<<8) | (g<<16) | (r<<24);
  sprintf(color_label,"color #%02x%02x%02x alpha %02x",r,g,b,a);
  switch (cindex) {
    case 0: fg_color = color;
      dlg->set_fgcolor(color);
      break;
    case 1: bg_color = color;
      dlg->set_bgcolor(color);
      break;
    case 2: fgframe_color = color;
      break; // a dialog has no frame, I can't redraw it here...
    case 3: bgframe_color = color;
      break;
    case 4: bg_dialog_bar = color;
      break;
  }
  return 0;
}
  
static int get_color_from_index() {
  switch(cindex) {
    case 0: return fg_color;
    case 1: return bg_color;
    case 2: return fgframe_color;
    case 3: return bgframe_color;
    case 4: return bg_dialog_bar;
  }
  return 0;
}

static int theme;

static int set_theme(int sel) {
  switch(theme) {
    case 0: // blue
      bg_color =  makecol_alpha(0x11,0x07,0x78,128);
      bgframe_color = mymakecol(0,0,128);
      break;
    case 1: // green
      bg_color =  makecol_alpha(0x28,0x78,0x28,128);
      bgframe_color = mymakecol(0,128,0);
      break;
  }
  fg_color = mymakecol(255,255,255);
  fgframe_color = mymakecol(255,255,255);
  cslider_border = mymakecol(0,0,0);
  cslider_bar = mymakecol(0xc0,0xc0,0xc0);
  cslider_lift = mymakecol(0xff,0xff,0xff);
  bg_dialog_bar = mymakecol(0,0,0);
  return 0;
}

static int change_color(int sel);

static menu_item_t colors_menu[] =
{
{  _("fg color"), &change_color, },
{  _("bg color"), &change_color, },
{  _("fg frame color"), &change_color, },
{  _("bg frame color"), &change_color, },
{  _("bg dialog bar color"), &change_color, },
{ _("Revert to..."), &set_theme, &theme, 2, { 0, 1 }, { _("Blue"), _("Green") } },
{ NULL, NULL, NULL }
};

static int change_color(int sel) {
  cindex = sel;
  int color = get_color_from_index();
  a = color & 0xff;
  b = (color >> 8) & 0xff;
  g = (color >> 16) & 0xff;
  r = (color >> 24) & 0xff;
  for (int n=0; n<=3; n++) {
    colors_dlg[n+1].values_list[3] = cslider_border;
    colors_dlg[n+1].values_list[5] = cslider_lift;
  }
  colors_dlg[1].values_list[4] = mymakecol(255,0,0);
  colors_dlg[2].values_list[4] = mymakecol(0,255,0);
  colors_dlg[3].values_list[4] = mymakecol(0,0,255);
  colors_dlg[4].values_list[4] = cslider_bar;
  sprintf(color_label,"color #%02x%02x%02x alpha %02x",r,g,b,a);
  colors_dlg[0].label = color_label;

  dlg = new TColorDlg((char*)colors_menu[cindex].label, colors_dlg);
  dlg->execute();
  delete dlg;
  return 1;
}


int do_colors(int sel) {
  TMenu *tmenu = new TMenu(_("Colors"),colors_menu);
  tmenu->execute();
  delete tmenu;
  return 0;
}

