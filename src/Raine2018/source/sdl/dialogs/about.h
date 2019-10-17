// A special TStatic class to be able to display these special sequences for
// commands...
class TMoveStatic : public TStatic
{
    public:
    TMoveStatic(menu_item_t *my_menu) : TStatic(my_menu) {}
    virtual void disp(SDL_Surface *s, TFont *font, int x, int y, int w, int h,
  int fg, int bg, int xoptions);
    virtual int get_width(TFont *font);
};

int do_about(int);
int show_moves(int sel);

