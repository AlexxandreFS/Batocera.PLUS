#ifndef WIDGET_H
#define WIDGET_H

#include "tfont.h"
#include "menuitem.h"

extern int test_utf(const char *s);

class TStatic {
  protected:
    menu_item_t *menu;
    int is_utf;
  public:
    TStatic(menu_item_t *my_menu);
    virtual ~TStatic() {} // virtual destructor required so that objects
    // which overload this one can have one !
    virtual int get_len();
    virtual int can_be_selected();
    virtual int can_draw_selection();
    virtual int get_len_max_options();
    virtual int get_width(TFont *font);
    virtual int get_width_max_options(TFont *font);
    virtual int get_list_index();
    virtual int get_height(TFont *font);
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions);
    virtual void next_list_item();
    virtual void prev_list_item();
    virtual int handle_mouse(SDL_Event *event) {
      return 0;
    }
    virtual int handle_key(SDL_Event *event) {
      // Returns :
      // 0 : key not handled, find another handler
      // > 0 : key handled, call the handler
      // < 0 : key handled, don't call anything
      return 0;
    }
    virtual int handle_key_buff(char *buff) {
      return 0;
    }
    virtual int produce_joystick_event(int axis_x, int axis_y) {
      return 0;
    }
    virtual void update() {
      // called to update the widget when nothing better to do...
    }
    virtual int can_exit() {
	return 1;
    }
};

class TProgressBar : public TStatic
{
  public:
    TProgressBar(menu_item_t *my_menu) : TStatic(my_menu)
    {}
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions);
    virtual int get_width(TFont *font);
    virtual int get_height(TFont *font);
};

class TOptions : public TStatic
{
  public:
    TOptions(menu_item_t *my_menu) : TStatic(my_menu)
    {}
    int can_be_selected() {
      // TOptions is created only if value_list_size > 0 -> returns 1 always
      return 1;
    }
    virtual int get_list_index();
    virtual int get_len_max_options();
    virtual int get_width_max_options(TFont *font);
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions);
    virtual void next_list_item();
    virtual void prev_list_item();
    virtual int handle_key_buff(char *buff);
};

#endif
