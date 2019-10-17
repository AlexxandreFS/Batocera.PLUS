#include "tlift.h"
#include <SDL.h>
#include "../SDL_gfx/SDL_gfxPrimitives.h"
#include "menu.h"
#include "sdl/display_sdl.h"

/* Deluxe lift, with auto-repeat arrow keys, and the thumb is moveable with
 * the mouse, either directly or page by page */

extern int repeat_interval, repeat_delay; // in gui.cpp

TLift::TLift(int myx,int myy,int myh,int *mytop, int *mydispitems,int *myrows,
  int *myupdate_count,
  SDL_Surface *surf, int myfgcol, int mybgcol,int mythumbcol)
{
  x = myx; y = myy; h = myh; w = 20;
  top = mytop; nb_disp_items = mydispitems; rows = myrows;
  s = surf;
  fgcol = myfgcol;
  bgcol = mybgcol;
  thumbcol = mythumbcol;
  update_count = myupdate_count;
  thumb_pos = phase_repeat = pressed = 0; // No button pressed
}

void TLift::press(int pressed) {
  if (pressed == 1) {
    if (*top > 0) {
      (*top)--;
    }
  } else if (pressed == 2) {
    if (*top + *rows < *nb_disp_items) {
      (*top)++;
    } 
  }
}

void TLift::prev_page() {
  *top -= *rows;
  if (*top < 0)
    *top = 0;
}

void TLift::next_page() {
  *top += *rows;
  if (*top >= *nb_disp_items)
    *top = *nb_disp_items - *rows;
}

int TLift::handle_mouse(SDL_Event *event) {
  // This one is called only when the mouse is in the lift area
  int mx,my;
  switch(event->type) {
    case SDL_MOUSEBUTTONDOWN:
      if (h > w) { // vertical
	my = event->button.y;
	if (my > y && my < y+12) { // button up
	  pressed = 1;
	  press(pressed);
	  timer = *update_count;
	} else if (my > y+h-12 && my < y+h) { // button down
	  pressed = 2;
	  press(pressed);
	  timer = *update_count;
	} else if (my > y+12 && my < y+h-12) {
	  if (my < ylift) {
	    prev_page();
	  } else if (my > ylift + size) {
	    next_page();
	  } else { // clicked in the thumb
	    thumb_pos = my;
	    orig_top = *top;
	  }
	} else
	  return 0;
	return 1;
      } else { // horizontal
	mx = event->button.x;
	if (mx > x && mx < x+12) { // button up
	  pressed = 1;
	  press(pressed);
	  timer = *update_count;
	} else if (mx > x+w-12 && mx < x+w) { // button down
	  pressed = 2;
	  press(pressed);
	  timer = *update_count;
	} else if (mx > x+12 && mx < x+w-12) {
	  if (mx < ylift) {
	    prev_page();
	  } else if (mx > ylift + size) {
	    next_page();
	  } else { // clicked in the thumb
	    thumb_pos = mx;
	    orig_top = *top;
	  }
	} else
	  return 0;
	return 1;
      }
    case SDL_MOUSEBUTTONUP:
      if (phase_repeat || pressed || thumb_pos) {
	phase_repeat = pressed = thumb_pos = 0;
	return 1;
      }
      return 0;
    case SDL_MOUSEMOTION:
      if (h > w) { // vertical version
	if (thumb_pos && event->motion.y < 4000) {
	  my = event->motion.y-thumb_pos;
	  *top = (my ) * (*nb_disp_items- *rows)/ ymax + orig_top;
	  if (*top > *nb_disp_items-*rows)
	    *top = *nb_disp_items-*rows;
	  else if (*top < 0)
	    *top = 0;
	  return 1;
	}
	return 0;
      } else {
	if (thumb_pos && event->motion.x < 4000) {
	  mx = event->motion.x-thumb_pos;
	  *top = (mx ) * (*nb_disp_items- *rows)/ ymax + orig_top;
	  if (*top > *nb_disp_items-*rows)
	    *top = *nb_disp_items-*rows;
	  else if (*top < 0)
	    *top = 0;
	  return 1;
	}
      }
  }
  return 0;
}

int TLift::produce_joystick_event(int axis_x, int axis_y) {
  // this event handler is only for embeded lifts (in menu_item_t).
  // for the main lifts this is handled automatically by the container
  if (w > h) { // horizontal
    if (axis_x == -1) {
      prev_page();
    } else if (axis_x == 1) {
      next_page();
    } else
      return 0;
    return 1;
  } else { // vertical
    if (axis_y == -1) {
      prev_page();
    } else if (axis_y == 1) {
      next_page();
    } else return 0;
  }
  return 1;
}

void TLift::update() {
  // Automatic repeat of the arrow keys !
  if (pressed) {
    int delay = (*update_count - timer)*33; // delay in ms
    if (!phase_repeat) { // didn't start repeat yet
      if (delay >= repeat_delay) {
	phase_repeat = 1; // start to repeat
	press(pressed);
	timer = *update_count;
      }
    } else {
      if (delay >= repeat_interval) {
	press(pressed);
	timer = *update_count;
      }
    }
  }
}

void TLift::draw() {
  int locked = lock_surface(s);
  if (locked < 0) return;
  rectangleColor(s,x,y,x+w-1,y+h-1,fgcol);
  boxColor(s,x+1,y+1,x+w-2,y+h-2,bgcol);

  // Now draw 2 arrows on top and bottom
  if (h > w) { // vertical version
    filledTrigonColor(s,x+3,y+10,x+w/2,y+2,x+w-4,y+10,fgcol);
    lineColor(s,x+1,y+12,x+w-1,y+12,fgcol);

    filledTrigonColor(s,x+3,y+h-11,x+w/2,y+h-3,x+w-4,y+h-11,fgcol);
    lineColor(s,x+1,y+h-13,x+w-1,y+h-13,fgcol);

    // Now compute the size & location of the "thumb"
    int height_lift = h-24;
    size = *rows * height_lift / *nb_disp_items;
    if (size < 10)
      size = 10;
    ymax = height_lift - size - 1; // (relatively to the lift coords)
    // top varies from 0 to nb_disp_items-rows...
    ylift = *top*ymax/ (*nb_disp_items-*rows) + y+12;

    rectangleColor(s,x+1,ylift,x+w-2,ylift+size,fgcol);
    boxColor(s,x+1,ylift+1,x+w-2,ylift+size-1,thumbcol);
  } else { // horizontal
    filledTrigonColor(s,x+2,y+h/2,x+10,y+3,x+10,y+h-4,fgcol);
    lineColor(s,x+12,y+1,x+12,y+h-1,fgcol);

    filledTrigonColor(s,x+w-3,y+h/2,x+w-11,y+3,x+w-11,y+h-4,fgcol);
    lineColor(s,x+w-13,y+1,x+w-13,y+h-1,fgcol);

    // Now compute the size & location of the "thumb"
    int width_lift = w-24;
    size = *rows * width_lift / *nb_disp_items;
    if (size < 10)
      size = 10;
    ymax = width_lift - size - 1; // (relatively to the lift coords)
    // top varies from 0 to nb_disp_items-rows...
    ylift = *top*ymax/ (*nb_disp_items-*rows) + x+12;

    rectangleColor(s,ylift,y+1,ylift+size,y+h-2,fgcol);
    boxColor(s,ylift+1,y+1,ylift+size-1,y+h-2,thumbcol);
  }
  if (locked)
    SDL_UnlockSurface(s);
}

void TLift::draw(SDL_Surface *mys, int ax, int ay, int aw, int ah)
{
  s = mys;
  x = ax; y = ay; w = aw; h = ah;
  draw();
}

int TLift::handle_key(SDL_Event *event) {
  switch (event->type) {
    case SDL_KEYDOWN:
      int sym = event->key.keysym.sym;
      switch(sym) {
	case SDLK_HOME:
          *top = 0;
	  return 1;
	case SDLK_END:
	  *top = *nb_disp_items - *rows;
	  return 1;
        case SDLK_LEFT:
	  if (w > h && *top > 0) {
	    *top = *top - 1;
	    return 1;
	  }
	  break;
	case SDLK_UP:
	  if (h > w && *top > 0) {
	    *top = *top - 1;
	    return 1;
	  }
	  break;
	case SDLK_RIGHT:
	  if (w > h && *top < *nb_disp_items-*rows) {
	    *top = *top + 1;
	    return 1;
	  }
	  break;
	case SDLK_DOWN:
	  if (h > w && *top < *nb_disp_items-*rows) {
	    *top = *top + 1;
	    return 1;
	  }
	  break;
	case SDLK_PAGEUP:
	  prev_page();
	  return 1;
	case SDLK_PAGEDOWN:
	  next_page();
	  return 1;
      }
  }
  return 0;
}
