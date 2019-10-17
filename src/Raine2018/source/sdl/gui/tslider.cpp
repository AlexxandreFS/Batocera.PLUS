#include "menu.h"
#include "tslider.h"

TSlider::TSlider(menu_item_t *my_menu) : TStatic(my_menu)
{
  rows = menu->values_list[1];
  nb_disp_items = menu->values_list[0]+rows;
  update_count = 0;
  width = menu->values_list[2];
  int cslider_border = menu->values_list[3];
  int cslider_bar    = menu->values_list[4];
  int cslider_lift   = menu->values_list[5];

  lift = new TLift(0,0,0,menu->value_int,&nb_disp_items,&rows,&update_count,NULL,cslider_border,cslider_bar,cslider_lift);
}

int TSlider::get_width(TFont *font) {
  int w = TStatic::get_width(font);
  if (w > width)
    return w;
  return width;
}

int TSlider::get_height(TFont *font) {
  return TStatic::get_height(font)+20;
}

void TSlider::disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions) {
  int wl,hl;
  font->dimensions(menu->label,&wl,&hl);
  font->surf_string(s,(x+w-wl)/2,y,menu->label,fg,bg,w);

  y += hl;
  lift->draw(s,x,y,w,20);
}

int TSlider::handle_mouse(SDL_Event *event)
{
  return lift->handle_mouse(event);
}

int TSlider::produce_joystick_event(int axis_x, int axis_y) {
  return lift->produce_joystick_event(axis_x,axis_y);
}

int TSlider::handle_key(SDL_Event *event) {
  return lift->handle_key(event);
}
