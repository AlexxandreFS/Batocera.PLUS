#include "widget.h"
#include "tlift.h"

class TSlider : public TStatic
{
  private:
    TLift *lift;
    int rows, update_count, nb_disp_items,width;
  public:
    TSlider(menu_item_t *my_menu);
    ~TSlider()
    {
      delete lift;
    }
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h, 
  int fg, int bg, int xoptions);
    virtual int get_width(TFont *font);
    virtual int get_height(TFont *font);
    virtual int handle_mouse(SDL_Event *event);
    virtual int handle_key(SDL_Event *event);
    virtual int produce_joystick_event(int axis_x, int axis_y);
};


