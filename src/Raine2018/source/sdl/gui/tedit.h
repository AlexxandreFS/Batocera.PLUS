#ifndef TEDIT_H
#define TEDIT_H

#include "widget.h"

#define MAX_HISTORY 30

class TEdit : public TStatic
{
  protected:
    char *field;
    unsigned int maxl,pos,cursor_on,update_count,old_pos,pos_cursor;
    int curx,cury,curh,maxw;
    SDL_Surface *mys;
    TFont *font;
    char *history[MAX_HISTORY];
    int used_hist,current_hist,use_hist;
    char prefix_hist[80];
  public:
    TEdit(menu_item_t *my_menu);
    ~TEdit();
    void free_history();
    void load_history(char *name);
    void save_history(char *name);
    void update_cursor();
    virtual void disp(SDL_Surface *mys, TFont *myfont, int x, int y, int w, int h,
  int fg, int bg, int xoptions);
    virtual int get_height(TFont *font);
    virtual int get_len();
    virtual int get_len_max_options();
    virtual int get_width(TFont *font);
    virtual int get_width_max_options(TFont *font);
    // virtual int handle_mouse(SDL_Event *event);
    virtual int handle_key(SDL_Event *event);
    virtual void update();
    virtual void add_history();
    virtual void insert(char *s);
    virtual int can_be_selected() { return 1; }
    virtual int valid_chars(int sym, int unicode);
};

extern void EditDlg(char *label, char *dest,int max_len);

class TFloatEdit : public TEdit {
  protected:
      float *the_float, min, max;
  public:
    TFloatEdit(menu_item_t *my_menu);
    ~TFloatEdit();
    virtual int valid_chars(int sym, int unicode);
    virtual int can_exit();
    int get_len_max_options() { return 10; } // minimum field size !
};

class THexEdit : public TEdit {
  protected:
      UINT32 *the_hex, min, max;
  public:
    THexEdit(menu_item_t *my_menu);
    ~THexEdit();
    virtual int valid_chars(int sym, int unicode);
    virtual int can_exit();
    virtual int handle_key(SDL_Event *event);
    int get_len_max_options() { return 10; } // minimum field size !
};

class TIntEdit : public TEdit {
  public:
    TIntEdit(menu_item_t *my_menu);
    ~TIntEdit();
    virtual int valid_chars(int sym, int unicode);
    virtual int can_exit();
    virtual int handle_key(SDL_Event *event);
    int get_len_max_options() { return 30; } // minimum field size !
};

#endif
