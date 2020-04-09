/******************************************************************************/
/*                                                                            */
/*                              R-GUI: RAINE GUI                              */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "gui.h" // color conversion for the gui
#include "palette.h" // GET_PEN...

/* Stupid deprecated stuff from allegro... was it really useful ?!!! */
#if (ALLEGRO_VERSION == 4 && ALLEGRO_SUB_VERSION == 0) || ALLEGRO_VERSION < 4
#define gui_textout_ex(bmp,s,x,y,color,bg,centre)	\
  text_mode(bg);					\
  gui_textout(bmp,s,x,y,color,centre);
#define textout_ex(bmp,f,str,x,y,color,bg)		\
  text_mode(bg);					\
  textout(bmp,f,str,x,y,color);
#endif

/*

Todo:

- Anything/everything/something... some day maybe... boring...

*/

#define SLOW_DRAG			// Don't buffer window when moving it, slow

// typedef for the listbox callback functions

typedef char *(*getfuncptr)(int, int *);
typedef void (*getfuncptr2)(int, int *,int *);

static int translate_color(int x)
{
  int Cx=0; // Translated color
  SET_PAL(x);
  return Cx;
}

static DEF_INLINE void trans_3d_box(int x1, int y1, int x2, int y2)
{
   putpixel(screen, x2, y1, CGUI_BOX_COL_MIDDLE);
   putpixel(screen, x1, y2, CGUI_BOX_COL_MIDDLE);

   hline(screen, x1,   y1,   x2-1, CGUI_BOX_COL_HIGH_2);
   hline(screen, x1+1, y2,   x2,   CGUI_BOX_COL_LOW_2 );
   vline(screen, x1,   y1,   y2-1, CGUI_BOX_COL_HIGH_2);
   vline(screen, x2,   y1+1, y2,   CGUI_BOX_COL_LOW_2 );
}

static DEF_INLINE void trans_3d_box_invert(int x1, int y1, int x2, int y2)
{
   putpixel(screen, x2, y1, CGUI_BOX_COL_MIDDLE);
   putpixel(screen, x1, y2, CGUI_BOX_COL_MIDDLE);

   hline(screen, x1,   y1,   x2-1, CGUI_BOX_COL_LOW_2 );
   hline(screen, x1+1, y2,   x2,   CGUI_BOX_COL_HIGH_2);
   vline(screen, x1,   y1,   y2-1, CGUI_BOX_COL_LOW_2 );
   vline(screen, x2,   y1+1, y2,   CGUI_BOX_COL_HIGH_2);
}

static DEF_INLINE void solid_3d_box(int x1, int y1, int x2, int y2)
{
   rectfill(screen, x1, y1, x2-1, y2-1, CGUI_BOX_COL_MIDDLE);

   hline(screen, x1+0, y1+0, x2-2, CGUI_BOX_COL_HIGH_2);
   hline(screen, x1+1, y2-1, x2-1, CGUI_BOX_COL_LOW_2 );
   vline(screen, x1+0, y1+0, y2-2, CGUI_BOX_COL_HIGH_2);
   vline(screen, x2-1, y1+1, y2-1, CGUI_BOX_COL_LOW_2 );

   hline(screen, x1+1, y1+1, x2-3, CGUI_BOX_COL_HIGH_1);
   hline(screen, x1+2, y2-2, x2-2, CGUI_BOX_COL_LOW_1 );
   vline(screen, x1+1, y1+1, y2-3, CGUI_BOX_COL_HIGH_1);
   vline(screen, x2-2, y1+2, y2-2, CGUI_BOX_COL_LOW_1 );
}

static DEF_INLINE void solid_3d_box_invert(int x1, int y1, int x2, int y2)
{
   rectfill(screen, x1, y1, x2-1, y2-1, CGUI_BOX_COL_MIDDLE);

   hline(screen, x1+0, y1+0, x2-2, CGUI_BOX_COL_LOW_2 );
   hline(screen, x1+1, y2-1, x2-1, CGUI_BOX_COL_HIGH_2);
   vline(screen, x1+0, y1+0, y2-2, CGUI_BOX_COL_LOW_2 );
   vline(screen, x2-1, y1+1, y2-1, CGUI_BOX_COL_HIGH_2);

   hline(screen, x1+1, y1+1, x2-3, CGUI_BOX_COL_LOW_1 );
   hline(screen, x1+2, y2-2, x2-2, CGUI_BOX_COL_HIGH_1);
   vline(screen, x1+1, y1+1, y2-3, CGUI_BOX_COL_LOW_1 );
   vline(screen, x2-2, y1+2, y2-2, CGUI_BOX_COL_HIGH_1);
}

static DEF_INLINE void dotted_rect(int x1, int y1, int x2, int y2)
{
   rect(screen, x1, y1, x2, y2, CGUI_COL_SELECT);
}

// d_raine_box_proc:
// Simple dialog procedure: just draws a 3D box.

int d_raine_box_proc(int msg, DIALOG *d, int c)
{
  if(msg==MSG_DRAW){
    scare_mouse();
    solid_3d_box(d->x, d->y, d->x+d->w, d->y+d->h);
    unscare_mouse();
  }

   return D_O_K;
}

typedef struct WINDOW_DATA
{
   BITMAP *back_cache;
   BITMAP *window;
   UINT32  back_x;
   UINT32  back_y;
   UINT32  back_w;
   UINT32  back_h;
} WINDOW_DATA;

void _handle_drag_window(DIALOG *dialog)
{
   int x_ofs, y_ofs;
   int xx   , yy;
   int gx   , gy;
   int count;
#ifndef SLOW_DRAG
   WINDOW_DATA *wdat;
   wdat = (WINDOW_DATA *) dialog[0].dp2;
#endif


   // Init

   gx = rgui_mouse_x();
   gy = rgui_mouse_y();

   x_ofs = gx - dialog[0].x;
   y_ofs = gy - dialog[0].y;

   while (gui_mouse_b()) {

      // Check if mouse has moved

      gx = rgui_mouse_x();
      gy = rgui_mouse_y();

      xx = dialog[0].x - (gx - x_ofs);
      yy = dialog[0].y - (gy - y_ofs);

      // Update dialog if it moved

      if((xx != 0)||(yy != 0)){

         for (count=0; dialog[count].proc; count++) {
            dialog[count].x -= xx;
            dialog[count].y -= yy;
         }

         x_ofs = gx - dialog[0].x;
         y_ofs = gy - dialog[0].y;

#ifdef SLOW_DRAG
         broadcast_dialog_message(MSG_DRAW, 0);
#else
         scare_mouse();

         if(wdat){
         if(wdat->window){	// Copy Window
            blit(screen, wdat->window, wdat->back_x, wdat->back_y, 0, 0, dialog[0].w+1, dialog[0].h+1);
         }
         if(wdat->back_cache){	// Restore Back
            blit(wdat->back_cache, screen, 0, 0, wdat->back_x, wdat->back_y, dialog[0].w+1, dialog[0].h+1);
         }
         }

         if(wdat){
         if(wdat->back_cache){	// Store Back
            wdat->back_x = dialog[0].x;
            wdat->back_y = dialog[0].y;
            blit(screen, wdat->back_cache, wdat->back_x, wdat->back_y, 0, 0, dialog[0].w+1, dialog[0].h+1);
         }
         if(wdat->window){	// Paste Window
            blit(wdat->window, screen, 0, 0, wdat->back_x, wdat->back_y, dialog[0].w+1, dialog[0].h+1);
         }
         }

         unscare_mouse();
#endif

      }

      // Don't suffocate the rest of the dialog

      broadcast_dialog_message(MSG_IDLE, 0);
   }


}

int d_raine_window_proc(int msg, DIALOG *dialog, int c)
{
   WINDOW_DATA *wdat;

   switch(msg){
      case MSG_START:

         wdat = (WINDOW_DATA *) malloc(sizeof(WINDOW_DATA));

         if(wdat){

         wdat->back_x      = dialog->x;
         wdat->back_y      = dialog->y;
         wdat->back_w      = dialog->w;
         wdat->back_h      = dialog->h;
         wdat->back_cache  = create_bitmap( wdat->back_w, wdat->back_h);
         wdat->window      = create_bitmap( wdat->back_w, wdat->back_h);

         if(wdat->back_cache){
            scare_mouse();
            blit(screen, wdat->back_cache, wdat->back_x, wdat->back_y, 0, 0, wdat->back_w, wdat->back_h);
            unscare_mouse();
         }

         }

         dialog->dp2 = (void *) wdat;

         return D_O_K;
      break;
      case MSG_END:
         wdat = (WINDOW_DATA *) dialog->dp2;

         if(wdat){

         if(wdat->back_cache){
            scare_mouse();
            blit(wdat->back_cache, screen, 0, 0, wdat->back_x, wdat->back_y, wdat->back_w, wdat->back_h);
            unscare_mouse();
            destroy_bitmap(wdat->back_cache);
         }

         free(wdat);

         }

         return D_O_K;
      break;
      case MSG_DRAW:
	scare_mouse();
         wdat = (WINDOW_DATA *) dialog->dp2;

         if(wdat){

         if(wdat->back_cache){
            blit(wdat->back_cache, screen, 0, 0, wdat->back_x, wdat->back_y, wdat->back_w, wdat->back_h);
            wdat->back_x = dialog->x;
            wdat->back_y = dialog->y;
            blit(screen, wdat->back_cache, wdat->back_x, wdat->back_y, 0, 0, wdat->back_w, wdat->back_h);
         }

         }

         solid_3d_box(dialog->x, dialog->y, dialog->x+dialog->w, dialog->y+dialog->h);

         rectfill(screen, dialog->x+3, dialog->y+3+1, dialog->x+dialog->w-4, dialog->y+3+text_height(gui_main_font), CGUI_BOX_COL_LOW_2 );

         hline(screen, dialog->x+3, dialog->y+3,                            dialog->x+dialog->w-4, CGUI_BOX_COL_LOW_1 );
         hline(screen, dialog->x+3, dialog->y+4+text_height(gui_main_font), dialog->x+dialog->w-4, CGUI_BOX_COL_LOW_1 );

         // text_mode(-1);
	 if (dialog->dp)
	   textout_ex(screen, gui_main_font, raine_translate_text(dialog->dp), dialog->x+4+6, dialog->y+4, CGUI_COL_TEXT_1, -1 );

	 unscare_mouse();
         return D_O_K;
      break;
      case MSG_CLICK:

         {
            int gx = rgui_mouse_x();
            int gy = rgui_mouse_y();

            if((gx >= dialog->x+3)&&(gy >= dialog->y+3)&&(gx <= dialog->x+dialog->w-4)&&(gy <= dialog->y+4+text_height(gui_main_font)))
	       _handle_drag_window( dialog );
            else
               broadcast_dialog_message(MSG_IDLE, 0);
         };

         return D_O_K;
      break;
      case MSG_IDLE:
         dialog_oxygen();
         return D_O_K;
      break;
      default:
         return D_O_K;
      break;
   }

}


int d_null_proc(int msg, DIALOG *d, int c)
{
   return D_O_K;
}

int d_raine_oxygen_proc(int msg, DIALOG *d, int c)
{
   if(msg==MSG_IDLE)
      dialog_oxygen();
   return D_O_K;
}

int raine_slider_proc(int msg, DIALOG *d, int c)
{
   BITMAP *slhan = NULL;
   int sfg;                /* slider foreground color */
   int vert = TRUE;        /* flag: is slider vertical? */
   int hh = 7;             /* handle height (width for horizontal sliders) */
   int slp;                /* slider position */
   int irange;
   int slx, sly, slh, slw;
   int retval = D_O_K;
   fixed slratio, slmax, slpos;
   int dbg;

   /* check for slider direction */
   if (d->h < d->w)
      vert = FALSE;

   /* set up the metrics for the control */
   if (d->dp != NULL) {
      slhan = (BITMAP *)d->dp;
      if (vert)
	 hh = slhan->h;
      else
	 hh = slhan->w;
   }

   irange = (vert) ? d->h : d->w;
   slmax = itofix(irange-hh);
   slratio = slmax / (d->d1);
   slpos = slratio * d->d2;
   slp = fixtoi(slpos);

   switch (msg) {

      case MSG_DRAW:
	scare_mouse();
	 sfg = (d->flags & D_DISABLED) ? gui_mg_color : d->fg;
	 sfg = translate_color(sfg);

	 dbg = translate_color(d->bg);

	 if (vert) {
	    rectfill(screen, d->x, d->y, d->x+d->w/2-2, d->y+d->h-1, dbg);
	    rectfill(screen, d->x+d->w/2-1, d->y, d->x+d->w/2+1, d->y+d->h-1, sfg);
	    rectfill(screen, d->x+d->w/2+2, d->y, d->x+d->w-1, d->y+d->h-1, dbg);
	 }
	 else {
	    rectfill(screen, d->x, d->y, d->x+d->w-1, d->y+d->h/2-2, dbg);
	    rectfill(screen, d->x, d->y+d->h/2-1, d->x+d->w-1, d->y+d->h/2+1, sfg);
	    rectfill(screen, d->x, d->y+d->h/2+2, d->x+d->w-1, d->y+d->h-1, dbg);
	 }

	 /* okay, background and slot are drawn, now draw the handle */
	 if (slhan) {
	    if (vert) {
	       slx = d->x+(d->w/2)-(slhan->w/2);
	       sly = d->y+(d->h-1)-(hh+slp);
	    }
	    else {
	       slx = d->x+slp;
	       sly = d->y+(d->h/2)-(slhan->h/2);
	    }
	    draw_sprite(screen, slhan, slx, sly);
	 }
	 else {
	    /* draw default handle */
	    if (vert) {
	       slx = d->x;
	       sly = d->y+(d->h)-(hh+slp);
	       slw = d->w-1;
	       slh = hh-1;
	    } else {
	       slx = d->x+slp;
	       sly = d->y;
	       slw = hh-1;
	       slh = d->h-1;
	    }

	    /* draw body */
	    rectfill(screen, slx+2, sly, slx+(slw-2), sly+slh, sfg);
	    vline(screen, slx+1, sly+1, sly+slh-1, sfg);
	    vline(screen, slx+slw-1, sly+1, sly+slh-1, sfg);
	    vline(screen, slx, sly+2, sly+slh-2, sfg);
	    vline(screen, slx+slw, sly+2, sly+slh-2, sfg);
	    vline(screen, slx+1, sly+2, sly+slh-2, dbg);
	    hline(screen, slx+2, sly+1, slx+slw-2, dbg);
	    putpixel(screen, slx+2, sly+2, d->bg);
	 }

	 if (d->flags & D_GOTFOCUS)
	    dotted_rect(d->x, d->y, d->x+d->w-1, d->y+d->h-1);
	 unscare_mouse();
	 break;
   default:
     return d_slider_proc(msg,d,c);
   }
   return retval;
}

// d_raine_button_proc():
// A button object (the dp field points to the text string). This object
// can be selected by clicking on it with the mouse or by pressing its
// keyboard shortcut. If the D_EXIT flag is set, selecting it will close
// the dialog, otherwise it will toggle on and off.
//
// Only MSG_DRAW is changed, all others fall back on the original d_button_proc

int d_raine_button_proc(int msg, DIALOG *d, int c)
{
   int state1, state2;
   int swap;
   int g;

   switch (msg) {

      case MSG_DRAW:

	scare_mouse();
	if(d->flags & D_SELECTED){

	  solid_3d_box_invert(d->x, d->y, d->x + d->w, d->y + d->h);

	  //line(screen, d->x+1, d->y+1, d->x+1,      d->y+d->h-1, CGUI_BOX_COL_LOW_1);
	  //line(screen, d->x+1, d->y+1, d->x+d->w-1, d->y+1,      CGUI_BOX_COL_LOW_1);

	  g = 1;
	  state1 = (d->flags & D_DISABLED) ? gui_mg_color : translate_color(d->fg);
	  state2 = translate_color(d->bg);

      }
      else{

      solid_3d_box(d->x, d->y, d->x + d->w, d->y + d->h);

      //line(screen, d->x+1,      d->y+d->h-1, d->x+d->w-1, d->y+d->h-1, CGUI_BOX_COL_LOW_1);
      //line(screen, d->x+d->w-1, d->y+1,      d->x+d->w-1, d->y+d->h-1, CGUI_BOX_COL_LOW_1);

      g = 0;
      state1 = (d->flags & D_DISABLED) ? gui_mg_color : translate_color(d->fg);
      state2 = translate_color(d->bg);

      }

	// text_mode(-1);
      gui_textout_ex(screen, raine_translate_text(d->dp), d->x+d->w/2+g, d->y+d->h/2-text_height(font)/2+g, state1, -1, TRUE);

      if((d->flags & D_GOTFOCUS) && (!(d->flags & D_SELECTED) || !(d->flags & D_EXIT))){
	    dotted_rect(d->x+1+g, d->y+1+g, d->x+d->w-2+g, d->y+d->h-2+g);
      }

      unscare_mouse();
	 break;

      case MSG_WANTFOCUS:
	 return D_WANTFOCUS;

      case MSG_KEY:
	 /* close dialog? */
	 if (d->flags & D_EXIT) {
	    return D_CLOSE;
	 }

	 /* or just toggle */
	 d->flags ^= D_SELECTED;
	 scare_mouse();
	 SEND_MESSAGE(d, MSG_DRAW, 0);
	 unscare_mouse();
	 break;

      case MSG_CLICK:
	 /* what state was the button originally in? */
	 state1 = d->flags & D_SELECTED;
	 if (d->flags & D_EXIT)
	    swap = FALSE;
	 else
	    swap = state1;

	 /* track the mouse until it is released */
	 while (gui_mouse_b()) {
	    state2 = ((rgui_mouse_x() >= d->x) && (rgui_mouse_y() >= d->y) &&
		      (rgui_mouse_x() < d->x + d->w) && (rgui_mouse_y() < d->y + d->h));
	    if (swap)
	       state2 = !state2;

	    /* redraw? */
	    if (((state1) && (!state2)) || ((state2) && (!state1))) {
	       d->flags ^= D_SELECTED;
	       state1 = d->flags & D_SELECTED;
	       scare_mouse();
	       SEND_MESSAGE(d, MSG_DRAW, 0);
	       unscare_mouse();
	    }

	    /* let other objects continue to animate */
	    broadcast_dialog_message(MSG_IDLE, 0);
	 }

	 /* should we close the dialog? */
	 if ((d->flags & D_SELECTED) && (d->flags & D_EXIT)) {
	    d->flags ^= D_SELECTED;
	    return D_CLOSE;
	 }
	 break;
   }

   return D_O_K;
}

int x_raine_button_proc(int msg, DIALOG *d, int c)
{
   return d_raine_button_proc(msg,d,c);
}

/* x_edit_proc */
int x_edit_proc(int msg, DIALOG *d, int c)
{
   int f, l, p, w, x, fg, b, scroll;
   char buf[16];
   char *s;

   if (msg == MSG_DRAW) {
     scare_mouse();
     s = d->dp;
     l = ustrlen(s);
     if (d->d2 > l)
       d->d2 = l;

     /* calculate maximal number of displayable characters */
     if (d->d2 == l)  {
       usetc(buf+usetc(buf, ' '), 0);
       x = text_length(font, buf);
     }
     else
       x = 0;

     b = 0;

     for (p=d->d2; p>=0; p--) {
       usetc(buf+usetc(buf, ugetat(s, p)), 0);
       x += text_length(font, buf);
       b++;
       if (x > d->w)
	 break;
     }

     if (x <= d->w) {
       b = l;
       scroll = FALSE;
     }
     else {
       b--;
       scroll = TRUE;
     }

     // Real drawing
     fg = (d->flags & D_DISABLED) ? gui_mg_color : translate_color(d->fg);
     x = 0;

     if (scroll) {
       p = d->d2-b+1;
       b = d->d2;
     }
     else
       p = 0;

     for (; p<=b; p++) {
       f = ugetat(s, p);
       usetc(buf+usetc(buf, (f) ? f : ' '), 0);
       w = text_length(font, buf);
       if (x+w > d->w)
	 break;
       f = ((p == d->d2) && (d->flags & D_GOTFOCUS));
       // rtm = text_mode((f) ? fg : translate_color(d->bg));
       textout_ex(screen, font, buf, d->x+x, d->y, (f) ? translate_color(d->bg) : fg,(f) ? fg : translate_color(d->bg));
       // text_mode(rtm);
       x += w;
     }
     if (x < d->w)
       rectfill(screen, d->x+x, d->y, d->x+d->w-1, d->y+text_height(font)-1, translate_color(d->bg));
     unscare_mouse();
   } else { // MSG_DRAW
     return d_edit_proc(msg,d,c);
   }

   return D_O_K;

}

/* d_raine_check_proc:
 *  Who needs C++ after all? This is derived from d_button_proc,
 *  but overrides the drawing routine to provide a check box.
 */
int d_raine_check_proc(int msg, DIALOG *d, int c)
{
   if (msg==MSG_DRAW) {
     return d_raine_radio_proc(msg,d,0);
   }

   return d_raine_button_proc(msg, d, 0);
}

// d_raine_radio_proc():
// GUI procedure for radio buttons.
// Parameters: d1-button group number; d2-button style (0=circle,1=square);
// dp-text to appear as label to the right of the button.
//
// Only MSG_DRAW is changed, all others fall back on the original d_radio_proc

int d_raine_radio_proc(int msg, DIALOG *d, int c)
{
   int x, center, r, fg;

   if(msg==MSG_DRAW){
     scare_mouse();
	 fg = (d->flags & D_DISABLED) ? CGUI_BOX_COL_MIDDLE : translate_color(d->fg);
	 // text_mode(CGUI_BOX_COL_MIDDLE);
	 gui_textout_ex(screen, d->dp, d->x+d->h+text_height(font), d->y+(d->h-(text_height(font)-gui_font_baseline))/2, fg, CGUI_BOX_COL_MIDDLE, FALSE);

	 x = d->x;
	 r = d->h/2;
	 center = x+r;
	 rectfill(screen, x+1, d->y+1, x+d->h-1, d->y+d->h-1, CGUI_BOX_COL_MIDDLE);

	 switch (d->d2) {

	    case 1:
	       trans_3d_box(x, d->y, x+d->h, d->y+d->h);
	       if (d->flags & D_SELECTED)
		  rectfill(screen, x+r/2, d->y+r/2, x+d->h-r/2, d->y+d->h-r/2, CGUI_BOX_COL_HIGH_2);
	       break;

	    default:
	       circle(screen, center, d->y+r, r, fg);
	       if (d->flags & D_SELECTED)
		  circlefill(screen, center, d->y+r, r/2, CGUI_BOX_COL_HIGH_2);
	       break;
	 }

	 if(d->flags & D_GOTFOCUS){
	    dotted_rect(x+1, d->y+1, x+d->h-1, d->y+d->h-1);
         }

	 unscare_mouse();
      return D_O_K;
   }
   else{
      return d_radio_proc(msg,d,c);
   }
}

static void swap( int *a, int *b) {
  int old = *a;
  *a = *b;
  *b = old;
}

int d_raine_radio_button_proc(int msg, DIALOG *d, int c)
{
   int ret;

   switch (msg) {
   case MSG_DRAW:

     scare_mouse();
     if(d->flags & D_SELECTED){
       int old = CGUI_BOX_COL_MIDDLE;
       CGUI_BOX_COL_MIDDLE = translate_color(d->fg);
       swap(&d->fg,&d->bg);
       ret = d_raine_button_proc(msg,d,c);
       swap(&d->fg,&d->bg);
       CGUI_BOX_COL_MIDDLE = old;
     } else
       ret = d_raine_button_proc(msg,d,c);
     unscare_mouse();
     return ret;
   }

   return d_raine_radio_proc(msg,d,c);
}

int x_raine_radio_proc(int msg, DIALOG *d, int c)
{
   int x, center, r, fg;

   if(msg==MSG_DRAW){
     scare_mouse();
	 fg = (d->flags & D_DISABLED) ? CGUI_BOX_COL_MIDDLE : translate_color(d->fg);
	 // text_mode(CGUI_BOX_COL_MIDDLE);
	 gui_textout_ex(screen, raine_translate_text(d->dp), d->x+d->h+text_height(font), d->y+(d->h-(text_height(font)-gui_font_baseline))/2, fg, CGUI_BOX_COL_MIDDLE, FALSE);

	 x = d->x;
	 r = d->h/2;
	 center = x+r;
	 rectfill(screen, x+1, d->y+1, x+d->h-1, d->y+d->h-1, CGUI_BOX_COL_MIDDLE);

	 switch (d->d2) {

	    case 1:
	       trans_3d_box(x, d->y, x+d->h, d->y+d->h);
	       if (d->flags & D_SELECTED)
		  rectfill(screen, x+r/2, d->y+r/2, x+d->h-r/2, d->y+d->h-r/2, CGUI_BOX_COL_HIGH_2);
	       break;

	    default:
	       circle(screen, center, d->y+r, r, fg);
	       if (d->flags & D_SELECTED)
		  circlefill(screen, center, d->y+r, r/2, CGUI_BOX_COL_HIGH_2);
	       break;
	 }

	 if(d->flags & D_GOTFOCUS){
	    dotted_rect(x+1, d->y+1, x+d->h-1, d->y+d->h-1);
         }

	 unscare_mouse();
      return D_O_K;
   }
   else{
      return d_radio_proc(msg,d,c);
   }
}

/* _draw_raine_scrollable_frame:
 *  Helper function to draw a frame for all objects with vertical scrollbars.
 */
void _draw_raine_scrollable_frame(DIALOG *d, int listsize, int offset, int height, int fg_color)
{
   int i, len;
   int xx, yy;

   // possibly draw scrollbar
   if (listsize > height) {
      trans_3d_box(d->x, d->y, d->x+d->w-(8+5), d->y+d->h);
      trans_3d_box(d->x+d->w-(8+4), d->y, d->x+d->w, d->y+d->h);

      // scrollbar with focus
      if (d->flags & D_GOTFOCUS) {
	 dotted_rect(d->x+1, d->y+1, d->x+d->w-(8+6), d->y+d->h-1);
	 dotted_rect(d->x+d->w-(8+3), d->y+1, d->x+d->w-1, d->y+d->h-1);
      }
      else {
	 rect(screen, d->x+1, d->y+1, d->x+d->w-(8+6), d->y+d->h-1, CGUI_BOX_COL_MIDDLE);
	 rect(screen, d->x+d->w-(8+3), d->y+1, d->x+d->w-1, d->y+d->h-1, CGUI_BOX_COL_MIDDLE);
      }

      // create and draw the scrollbar
      i = ((d->h-4) * height + listsize/2) / listsize;
      xx = d->x+d->w-(8+2);
      yy = d->y+2;

      if (offset > 0) {
	 len = (((d->h-4) * offset) + listsize/2) / listsize;
	 rectfill(screen, xx, yy, xx+8, yy+len-1, CGUI_BOX_COL_MIDDLE);
	 yy += len;
      }
      if (yy+i+1 < d->y+d->h-2) {
         solid_3d_box(xx, yy, xx+8+1, yy+i+1);
	 yy += i+1;
	 rectfill(screen, xx, yy, xx+8, d->y+d->h-2, CGUI_BOX_COL_MIDDLE);
      }
      else {
         solid_3d_box(xx, yy, xx+8+1, d->y+d->h-1);
      }
   }
   else {
      trans_3d_box(d->x, d->y, d->x+d->w, d->y+d->h);

      // no scrollbar necessary
      if (d->flags & D_GOTFOCUS)
	 dotted_rect(d->x+1, d->y+1, d->x+d->w-1, d->y+d->h-1);
      else
	 rect(screen, d->x+1, d->y+1, d->x+d->w-1, d->y+d->h-1, CGUI_BOX_COL_MIDDLE);
   }
}


/* _draw_raine_listbox:
 *  Helper function to draw a listbox object.
 */
// Extension : dp3 is now a pointer to the color of the index :
// void func(int index, int &fg, int &bg)
// if the function does not change the colors, then defaults are used.
void _draw_raine_listbox(DIALOG *d)
{
   int height, listsize, i, len, bar, x, y, w;
   int fg_color, fg, bg;
   char *sel = d->dp2;
   char s[1024];

   (*(getfuncptr)d->dp)(-1, &listsize);
   height = (d->h-3) / text_height(gui_fixed_font);
   bar = (listsize > height);
   w = (bar ? d->w-14 : d->w-2);
   fg_color = (d->flags & D_DISABLED) ? gui_mg_color : CGUI_BOX_COL_HIGH_2;

   /* draw box contents */
   for (i=0; i<height; i++) {
      if (d->d2+i < listsize) {
	if (d->d2+i == d->d1) { // selected
	  fg = CGUI_COL_TEXT_1;
	  bg = CGUI_BOX_COL_HIGH_2;
	}
	else if ((sel) && (sel[d->d2+i])) {
	    fg = CGUI_COL_TEXT_1;
	    bg = CGUI_BOX_COL_MIDDLE;
	 }
	 else {
	    fg = CGUI_COL_TEXT_1;
	    bg = CGUI_BOX_COL_MIDDLE;
	 }
	if (d->dp3 && ((int)d->dp3)>1000 && d->d2+i != d->d1) // not selected -> custom colors allowed
	  (*(getfuncptr2)d->dp3)(i,&fg,&bg);

	usetc(s, 0);
	 ustrncat(s, (*(getfuncptr)d->dp)(i+d->d2, NULL), sizeof(s)-ucwidth(0));
	 x = d->x + 2;
	 y = d->y + 2 + i*text_height(gui_fixed_font);
	 // text_mode(bg);
	 rectfill(screen, x, y, x+7, y+text_height(gui_fixed_font)-1, bg);
	 x += 8;
	 len = ustrlen(s);
	 while (text_length(gui_fixed_font, s) >= MAX(d->w - (bar ? 22 : 10), 1)) {
	    len--;
	    usetat(s, len, 0);
	 }
	 textout_ex(screen, gui_fixed_font, s, x, y, fg, bg);
	 x += text_length(gui_fixed_font, s);
	 if (x <= d->x+w)
	    rectfill(screen, x, y, d->x+w, y+text_height(gui_fixed_font)-1, bg);
      }
      else {
	 rectfill(screen, d->x+2,  d->y+2+i*text_height(gui_fixed_font),
		  d->x+w, d->y+1+(i+1)*text_height(gui_fixed_font), CGUI_BOX_COL_MIDDLE);
      }
   }

   if (d->y+2+i*text_height(gui_fixed_font) <= d->y+d->h-2)
      rectfill(screen, d->x+2, d->y+2+i*text_height(gui_fixed_font),
				       d->x+w, d->y+d->h-2, CGUI_BOX_COL_MIDDLE);

   /* draw frame, maybe with scrollbar */
   _draw_raine_scrollable_frame(d, listsize, d->d2, height, fg_color);

}

// d_raine_list_proc():
// A list box object. The dp field points to a function which it will call
// to obtain information about the list. This should follow the form:
//    char *<list_func_name> (int index, int *list_size);
// If index is zero or positive, the function should return a pointer to
// the string which is to be displayed at position index in the list. If
// index is  negative, it should return null and list_size should be set
// to the number of items in the list. The list box object will allow the
// user to scroll through the list and to select items list by clicking
// on them, and if it has the input focus also by using the arrow keys. If
// the D_EXIT flag is set, double clicking on a list item will cause it to
// close the dialog. The index of the selected item is held in the d1
// field, and d2 is used to store how far it has scrolled through the list.
//
// + MSG_DRAW is changed
// + MSG_KEY/MSG_DCLICK are changed, so the list function is able to act upon
//   the selection
// + MSG_CHAR is changed, so the list function can use key shortcuts for
//   selecting position

int d_raine_list_proc(int msg, DIALOG *d, int c)
{
  int last_d1,ret; //ta
  DIALOG_PROC callback;
   last_d1 = d->d1;

   ret = D_O_K;

   if (((int)d->dp3) > 1000) // dp3 points to a color function
     callback = d_list_proc;
   else
     callback = d_text_list_proc;

   switch(msg){
      case MSG_DRAW:
	scare_mouse();
         _draw_raine_listbox(d);
	 unscare_mouse();
      break;
      case MSG_DCLICK:
      case MSG_KEY:
         ret = (*callback)(msg,d,c);
	 (*(getfuncptr)d->dp)(-2, &ret);
      break;
      case MSG_XCHAR:
      case MSG_CHAR:
         ret = (*callback)(msg,d,c);

	 if ((!(c & 0xff)) || ret != D_USED_CHAR) { // extended code or unused
	   if (ret == D_USED_CHAR)
	     (*(getfuncptr)d->dp)(-3, &c); // Give a chance to the user func
	   else {
	     ret = c; // user func alone
	     (*(getfuncptr)d->dp)(-3, &ret);
	   }
	 }

	 if(ret == D_USED_CHAR){
	   scare_mouse();
	   SEND_MESSAGE(d, MSG_DRAW, 0);
	   unscare_mouse();
	   ret = D_USED_CHAR;
	 }
	 else{
	   ret = D_O_K;
	 }

	 break;
      default:
         ret = (*callback)(msg,d,c);
      break;
   }

   // Act on change of d1

   if(last_d1 != d->d1){
      last_d1 = d->d1;
      (*(getfuncptr)d->dp)(-4, &last_d1);
   }

   return ret;
}


/* _draw_textbox:
 *  Helper function to draw a textbox object.
 */
void _draw_raine_textbox(char *thetext, int *listsize, int draw, int offset,
		   int wword, int tabsize, int x, int y, int w, int h,
		   int disabled, int fore, int deselect, int disable)
{
   int fg = fore;
   int y1 = y+4;
   int x1;
   int len;
   int ww = w-4;
   char s[16];
   char text[16];
   char space[16];
   char *printed = text;
   char *scanned = text;
   char *oldscan = text;
   char *ignore = NULL;
   char *tmp, *ptmp;
   int width;
   int line = 0;
   int i = 0;

   usetc(s+usetc(s, '.'), 0);
   usetc(text+usetc(text, ' '), 0);
   usetc(space+usetc(space, ' '), 0);

   /* find the correct text */
   if (thetext != NULL) {
      printed = thetext;
      scanned = thetext;
   }

   /* do some drawing setup */
   if (draw) {
      /* initial start blanking at the top */
      rectfill(screen, x+2, y+2, x+w-1, y1-1, deselect);
   }

   /* choose the text color */
   if (disabled)
      fg = disable;

   // text_mode(deselect);

   /* loop over the entire string */
   while (1) {
      width = 0;

      /* find the next break */
      while (ugetc(scanned)) {
	 /* check for a forced break */
	 if (ugetc(scanned) == '\n') {
	    scanned += uwidth(scanned);

	    /* we are done parsing the line end */
	    break;
	 }

	 /* the next character length */
	 usetc(s+usetc(s, ugetc(scanned)), 0);
	 len = text_length(gui_fixed_font, s);

	 /* modify length if its a tab */
	 if (ugetc(s) == '\t')
	    len = tabsize * text_length(gui_fixed_font, space);

	 /* check for the end of a line by excess width of next char */
	 if (width+len >= ww) {
	    /* we have reached end of line do we go back to find start */
	    if (wword) {
	       /* remember where we were */
	       oldscan = scanned;

	       /* go backwards looking for start of word */
	       while (!uisspace(ugetc(scanned))) {
		  /* don't wrap too far */
		  if (scanned == printed) {
		     /* the whole line is filled, so stop here */
		     scanned = oldscan;
		     break;
		  }
		  /* look further backwards to wrap */
		  tmp = ptmp = printed;
		  while (tmp < scanned) {
		     ptmp = tmp;
		     tmp += uwidth(tmp);
		  }
		  scanned = ptmp;
	       }
	       /* put the space at the end of the line */
	       ignore = scanned;
	       scanned += uwidth(scanned);

	       /* check for endline at the convenient place */
	       if (ugetc(scanned) == '\n')
		  scanned += uwidth(scanned);
	    }
	    /* we are done parsing the line end */
	    break;
	 }

	 /* the character can be added */
	 scanned += uwidth(scanned);
	 width += len;
      }

      /* check if we are to print it */
      if ((draw) && (line >= offset) && (y1+text_height(gui_fixed_font) < (y+h-1))) {
	 x1 = x+4;

	 /* the initial blank bit */
	 rectfill(screen, x+2, y1, x1-1, y1+text_height(gui_fixed_font), deselect);

	 /* print up to the marked character */
	 while (printed != scanned) {
	    /* do special stuff for each charater */
	    switch (ugetc(printed)) {

	       case '\r':
	       case '\n':
		  /* don't print endlines in the text */
		  break;

	       /* possibly expand the tabs */
	       case '\t':
		  for (i=0; i<tabsize; i++) {
		     usetc(s+usetc(s, ' '), 0);
		     textout_ex(screen, gui_fixed_font, s, x1, y1, fg, deselect);
		     x1 += text_length(gui_fixed_font, s);
		  }
		  break;

	       /* print a normal charater */
	       default:
		  if (printed != ignore) {
		     usetc(s+usetc(s, ugetc(printed)), 0);
		     textout_ex(screen, gui_fixed_font, s, x1, y1, fg,deselect);
		     x1 += text_length(gui_fixed_font, s);
		  }
	    }

	    /* goto the next character */
	    printed += uwidth(printed);
	 }
	 /* the last blank bit */
	 if (x1 < x+w-1)
	    rectfill(screen, x1, y1, x+w-1, y1+text_height(gui_fixed_font)-1, deselect);

	 /* print the line end */
	 y1 += text_height(gui_fixed_font);
      }
      printed = scanned;

      /* we have done a line */
      line++;

      /* check if we are at the end of the string */
      if (!ugetc(printed)) {
	 /* the under blank bit */
	 if (draw)
	    rectfill(screen, x+1, y1, x+w-1, y+h-1, deselect);

	 /* tell how many lines we found */
	 *listsize = line;
	 return;
      }
   }
}

int d_raine_textbox_proc(int msg, DIALOG *d, int c)
{
   int height, bar, ret = D_O_K;
   //int start, top, bottom,l;
   //int used;
   int fg_color = (d->flags & D_DISABLED) ? CGUI_BOX_COL_MIDDLE : translate_color(d->fg);

   /* calculate the actual height */
   height = (d->h-4) / text_height(gui_fixed_font);

   switch (msg) {

      case MSG_START:
	 /* measure how many lines of text we contain */
	 _draw_raine_textbox(d->dp, &d->d1,
		       0, /* DONT DRAW anything */
		       d->d2, !(d->flags & D_SELECTED), 8,
		       d->x, d->y, d->w, d->h,
		       (d->flags & D_DISABLED),
		       0, 0, 0);
      break;

      case MSG_DRAW:
	scare_mouse();
	 /* tell the object to sort of draw, but only calculate the listsize */
	 _draw_raine_textbox(d->dp, &d->d1,
		       0, /* DONT DRAW anything */
		       d->d2, !(d->flags & D_SELECTED), 8,
		       d->x, d->y, d->w, d->h,
		       (d->flags & D_DISABLED),
		       0, 0, 0);

	 if (d->d1 > height) {
	    bar = 12;
	 }
	 else {
	    bar = 0;
	    d->d2 = 0;
	 }

	 /* now do the actual drawing */
	 _draw_raine_textbox(d->dp, &d->d1, 1, d->d2,
		       !(d->flags & D_SELECTED), 8,
		       d->x, d->y, d->w-bar-1, d->h,
		       (d->flags & D_DISABLED),
		       fg_color, translate_color(d->bg), gui_mg_color);

	 /* draw the frame around */
	 _draw_raine_scrollable_frame(d, d->d1, d->d2, height, fg_color);
	 unscare_mouse();
      break;
      default:
         ret = d_textbox_proc(msg,d,c);
      break;
   }

   return ret;
}


/* x_text_proc:
 *  Text proc, but with translation file support.
 */
int x_text_proc(int msg, DIALOG *d, int c)
{
   if (msg==MSG_DRAW) {
      int fg = (d->flags & D_DISABLED) ? CGUI_BOX_COL_MIDDLE : translate_color(d->fg);
      FONT *oldfont = font;
      scare_mouse();

      if (d->dp2)
	 font = d->dp2;

      // text_mode(CGUI_BOX_COL_MIDDLE);
      gui_textout_ex(screen, raine_translate_text(d->dp), d->x, d->y, fg, CGUI_BOX_COL_MIDDLE, FALSE);

      font = oldfont;
      unscare_mouse();
   }

   return D_O_K;
}

/* x_ctext_proc:
 *  Simple dialog procedure: draws the text string which is pointed to by dp,
 *  centering it around the object's x coordinate.
 * Add translation of text and color for raine
 */
int x_ctext_proc(int msg, DIALOG *d, int c)
{
   if (msg==MSG_DRAW) {
      int fg = (d->flags & D_DISABLED) ? gui_mg_color : translate_color(d->fg);
      FONT *oldfont = font;
     scare_mouse();

      if (d->dp2)
	 font = d->dp2;

      // rtm = text_mode(translate_color(d->bg));
      gui_textout_ex(screen, raine_translate_text(d->dp), d->x, d->y, fg, d->bg, TRUE);
      // text_mode(rtm);

      font = oldfont;
      unscare_mouse();
   }

   return D_O_K;
}

int d_progress_proc(int msg, DIALOG *d, int c)
{
   if (msg==MSG_DRAW)
   {
      int i, bg, fg;
     scare_mouse();

      bg = CGUI_BOX_COL_LOW_2;
      fg = CGUI_BOX_COL_HIGH_2;

      if(!d->d2)
         d->d2 = 100;

      if(d->d1 > d->d2)
         d->d1 = d->d2;

      i = ((d->d1 * d->w) / d->d2);
      if(i < d->w)
         rectfill(screen, d->x + i, d->y, d->x + d->w - 1, d->y + d->h, bg );

      if(i > 0)
         rectfill(screen, d->x, d->y, d->x + i, d->y + d->h, fg );
     unscare_mouse();
   }

   return D_O_K;
}

