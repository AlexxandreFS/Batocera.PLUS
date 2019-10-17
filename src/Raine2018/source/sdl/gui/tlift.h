#ifndef __TLIFT
#define __TLIFT

#include <SDL.h>

class TLift {
  protected:
    int x,y,w,h;
    int *top,*nb_disp_items,*rows,*update_count;
    SDL_Surface *s;
    int fgcol, bgcol,thumbcol;
    int pressed,phase_repeat,timer,size,ylift,thumb_pos,ymax,orig_top;
  public:
    TLift(int x,int y,int h,int *mytop, int *mydispitems,int *myrows,
      int *myupdate_count,
      SDL_Surface *suft, int myfgcol, int mybgcol, int mythumbcol);
    virtual ~TLift() {}
    int get_width() { return w; }
    void draw();
    void draw(SDL_Surface *mys, int ax, int ay, int aw, int ah);
    void press(int pressed);
    void update();
    int handle_mouse(SDL_Event *event);
    // Since fg_layer does not exist when we setup the lift, we need this :
    void set_surface(SDL_Surface *mysurf) { s = mysurf; }
    virtual int produce_joystick_event(int axis_x, int axis_y);
    virtual void next_page();
    virtual void prev_page();
    virtual int handle_key(SDL_Event *event);
};

#endif

