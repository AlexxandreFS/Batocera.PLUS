#include "widget.h"

/* TBitmap : a bitmap drawn dynamically
 * parameters :
 * value_list 0 & 1 : width and height
 * menu_func becomes a function which is called to draw to GameBitmap
 * */

class TBitmap : public TStatic {
  protected:
    int bpp,width,height,border,flags;
  public:
    TBitmap(menu_item_t *my_menu);
    virtual ~TBitmap();
    int get_width(TFont *font = NULL) { return menu->values_list[0]; }
    int get_height(TFont *font = NULL) { return menu->values_list[1]; }
    int can_draw_selection() { return 1; }
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h, 
  int fg, int bg, int xoptions);
};

    
