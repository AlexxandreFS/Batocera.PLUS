#ifndef ANDROID
#include "SDL_syswm.h"
#endif
#include <stdlib.h>

/* We do this one separately because we need to include windows.h and its
 * very incompatible with most headers used by raine (deftypes.h for a start)
 */

extern void raine_set_config_string(const char *section, const char *name, char *val);

void update_window_pos() {
#ifndef ANDROID
   static SDL_SysWMinfo pInfo;
   SDL_VERSION(&pInfo.version);
   SDL_GetWMInfo(&pInfo);
#endif

#ifdef RAINE_WIN32
   RECT rcWind;
   GetWindowRect(pInfo.window, &rcWind);
   POINT point;
   point.x = point.y = 0;
   ClientToScreen(pInfo.window,&point);
   int diffx = point.x - rcWind.left;
   int diffy = point.y - rcWind.top;

   char buf[40];
   sprintf(buf,"%ld,%ld",rcWind.left+diffx,rcWind.top+diffy);
   if (!strcmp(buf,"0,0")) {
       char *s = getenv("SDL_VIDEO_WINDOW_POS");
       if (s) {
	   /* If not doing this, the window is moved to 0,0, title bar out of
	    * screen when returning from fullscreen, completely ignoring the
	    * position environment variable (sdl bug - sdl should handle this).
	    * The MoveWindow here doesn't work with wine, so it might not work
	    * with all windows versions, but it works at least with win7 */
	   sscanf(s,"%d,%d",&diffx,&diffy);
	   MoveWindow(pInfo.window,diffx,diffy,rcWind.right-rcWind.left,
	       rcWind.bottom-rcWind.top,1);
       }
       return; // avoid bad coordinates when leaving fs
   }
   raine_set_config_string("Display","position",buf);
   /* I would have used setenv here, but windows doesn't know setenv... !!! */
   static char buffer[100];
   snprintf(buffer,100,"SDL_VIDEO_WINDOW_POS=%s",buf);
   buffer[99] = 0;
   putenv(buffer);
#endif
   /* For linux : in linux we usually have decent window managers, so it should
    * not be of any interest to save the window position here.
    * + it would collide with wm's intelligent placement
    * + xlib api is as crazy as windows to handle this kind of thing */
}

