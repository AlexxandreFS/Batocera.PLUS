/***************************************************************************/
/*   sendevent.c - send KeyEvents to window having focus V0.01B            */
/***************************************************************************/
/* Copyright (C) 2002 Erich Kitzmüller  erich.kitzmueller@itek.at          */
/***************************************************************************/
/* This program is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by    */
/* the Free Software Foundation; either version 2 of the License, or       */
/* (at your option) any later version.                                     */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU General Public License for more details.                            */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with tis program; if not, write to the Free Software              */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston MA  02111-1307 USA */
/***************************************************************************/
#include <X11/Xlib.h>
#include <sys/timeb.h>

Display *mydisp;

int sendevent(int typ, int keycode)
{
	XEvent event;
	Window win;
	int    revert_to;
    struct timeb t;

    ftime(&t);
  
	XGetInputFocus(mydisp, &win, &revert_to);

	event.xkey.type        = typ;
	event.xkey.serial      = 0;
	event.xkey.send_event  = True;
	event.xkey.display     = mydisp;
	event.xkey.window      = win;
	event.xkey.root        = XDefaultRootWindow(mydisp);
	event.xkey.subwindow   = None;
	event.xkey.time        = t.time * 1000 + t.millitm;
	event.xkey.x           = 0;
	event.xkey.y           = 0;
	event.xkey.x_root      = 0;
	event.xkey.state       = 0;
	event.xkey.keycode     = keycode;
	event.xkey.same_screen = True;

	XSendEvent(mydisp, InputFocus, True, 3, &event);
    XFlush(mydisp);

	return 0;
}

