/* Bezel support, from the mame artwork.
   I just want very basic support, the idea is to use this to fill the ugly black borders
   in vertical games, I don't care about transparency or anything displayed over the
   the game screen area...
   I handle the alphafile anyway because mame uses it to hide unneeded pixels in some
   artwork files... */

/* SDL uses this file too, because it seems handy to have tested code to
 * read/write pngs in any depth, and it isn't too hard to adapt to sdl...
 */

#include "unzip.h"
#include "raine.h"
#include "games.h"
#include "loadpng.h"
#include "video/res.h"
#include "blit.h"
#include "files.h"
#ifdef SDL
#include "sdl/SDL_gfx/SDL_rotozoom.h"
#include "sdl/blit_sdl.h"
#endif

// the people taking care of libc were really crazy when they decided that you had
// to define this to get the definition of round when including math.h...
#define __USE_ISOC99 1
#include <math.h>

#if defined(RAINE_DOS) || __FreeBSD_version < 500300
// djgpp seems to have specificities for rounding...
// why on earth non one implements cleanly such basic function ???
#define round rint
#endif

#ifdef RAINE_DOS
#define bytes_per_pixel(b) bitmap_color_depth(b)/8
#endif

static BITMAP *bezel_bitmap;
static PALETTE bezel_pal;
static float x,y,w,h;
static int bezel_width, bezel_height; // Size for the unscaled game screen

#define BUFFER_SIZE 1024
static  char buffer[BUFFER_SIZE];

static char* get_next_line() {
  static  char *next_line, *next_eol;
  if (!next_line) {
    next_line = buffer;
    next_eol = buffer;
  }
  if (next_eol) {
    next_line = next_eol+1;
    next_eol = strchr(next_line,'\n');
    if (next_eol) {
      *next_eol = 0;
      if (*(next_eol-1) == '\r') // stupid windows with its cr lf...
	*(next_eol-1) = 0;
    }
    while (*next_line == ' ' || *next_line == '\t')
      next_line++;
    return next_line;
  }
  next_line = NULL;
  return NULL;
}

static char *get_arg(char *s) {
  char *d = strchr(s,'=');
  if (d) {
    d++;
    while (*d == ' ' || *d == '\t')
      d++;
  }
  return d;
}

void clear_bezel() {
  if (bezel_bitmap) {
    destroy_bitmap(bezel_bitmap);
    bezel_bitmap = NULL;
    x = y = w = h = bezel_width = bezel_height = 0;
    print_debug("bezel destroyed\n");
  }
}

int get_line_pixel(UINT8 *line,int x,int depth) {
  switch(depth) {
    case 8:
    return line[x];
    case 15:
    case 16:
    return ReadWord(line+x*2);
    case 24:
    return ReadWord(line+x*3)+(ReadByte(line+x*3+2)<<16);
    default:
    return ReadLong(line+x*4);
  }
}

void load_bezel() {
  /* zip support only */
  unzFile uf;
  int err;
  char name[256],game_name[32];
  char *s,file[30],*arg;
  char alphafile[30];
  BITMAP *alpha_bitmap;

  if (display_cfg.bpp == 8)
    return;

  alphafile[0] = 0;

  clear_bezel();
  snprintf(name,256,"%s%s.zip",dir_cfg.artwork_dir,current_game->main_name);
  strcpy(game_name,current_game->main_name);

   uf = unzOpen(get_shared(name));

   if (!uf) {
     /* Try with the parents... */
     const DIR_INFO *head = current_game->dir_list;
     char *dir;
     for (; head; head++) {
       dir = head[0].maindir;

       if( dir ){

	 if( IS_ROMOF(dir) ){

	   GAME_MAIN *game_romof;

	   game_romof = find_game(dir+1);

	   strcpy(game_name,game_romof->main_name);
	   snprintf(name,256,"%s%s.zip",dir_cfg.artwork_dir,game_name);
	   uf = unzOpen(get_shared(name));
	   if (uf) break;
	 }
       } else
	 break;
     }
   }

   if(!uf) {			// Fail: Unable to find/open zipfile
     print_debug("bezel: not found %s\n",name);
     return;
   }
   sprintf(name,"%s.art",game_name);
   err = unzLocateFile(uf,name,2);
   if(err!=UNZ_OK){
     print_debug("bezel: not found %s\n",name);
     unzClose(uf);
     return;		// Fail: File not in zip
   }

   err = unzOpenCurrentFile(uf);
   if(err!=UNZ_OK){
      print_debug("unzOpenCurrentFile(): Error #%d\n",err);
      unzCloseCurrentFile(uf);	// Is this needed when open failed?
      unzClose(uf);
      return;			// Fail: Something internal
   }

   err = unzReadCurrentFile(uf,buffer,BUFFER_SIZE);
   if(err<0){
      print_debug("unzReadCurrentFile(): Error #%d\n",err);
      unzCloseCurrentFile(uf);
      unzClose(uf);
      return;			// Fail: Something internal
   }

   do {
     s = get_next_line();
     if (!s) {
       print_debug("bezel: eof while looking for bezel:\n");
       unzCloseCurrentFile(uf);
       unzClose(uf);
       return;			// Fail: Something internal
     }
   } while (strncasecmp(s,"bezel:",6) && strncasecmp(s,"backdrop:",9));

   *file = 0;
   do {
     s = get_next_line();
     if (s) {
       arg = get_arg(s);
       if (!strncasecmp(s,"file",4))
	 strcpy(file,arg);
       else if (!strncasecmp(s,"position",8))
	 sscanf(arg,"%f,%f,%f,%f",&x,&y,&w,&h);
       else if (!strncasecmp(s,"alphafile",9))
	 strcpy(alphafile,arg);
     }
   } while (s);

   unzCloseCurrentFile(uf);

   if (*file == 0) {
     print_debug("bezel: didn't find file argument\n");
     unzClose(uf);
     return;			// Fail: Something internal
   }

   err = unzLocateFile(uf,file,2);
   if(err!=UNZ_OK){
     print_debug("bezel: not found %s.\n",file);
     unzClose(uf);
     return;		// Fail: File not in zip
   }

   err = unzOpenCurrentFile(uf);
   if(err!=UNZ_OK){
      print_debug("unzOpenCurrentFile(): Error #%d\n",err);
      unzCloseCurrentFile(uf);	// Is this needed when open failed?
      unzClose(uf);
      return;			// Fail: Something internal
   }

   bezel_bitmap = load_png_from_zip(uf,bezel_pal);

   if (alphafile[0]) {
     err = unzLocateFile(uf,alphafile,2);
     if(err!=UNZ_OK){
       print_debug("bezel: not found %s.\n",alphafile);
       unzClose(uf);
       return;		// Fail: Alphafile not in zip
     }

     err = unzOpenCurrentFile(uf);
     if(err!=UNZ_OK){
       print_debug("unzOpenCurrentFile(): Error #%d\n",err);
       unzCloseCurrentFile(uf);	// Is this needed when open failed?
       unzClose(uf);
       return;			// Fail: Something internal
     }

     alpha_bitmap = load_png_from_zip(uf,bezel_pal);
     if (alpha_bitmap) {
       if (alpha_bitmap->w != bezel_bitmap->w || alpha_bitmap->h != bezel_bitmap->h) {
	 print_debug("bezel: alphafile dimensions != bezel dimensions, ignoring alphafile\n");
       } else {
	 /* I would have prefered to simply ignore the alphafile parameter since we can't
	    render the alpha channel in an efficient way without a 3d rendering driver,
	    and raine has no 3d rendering for now.
	    But some bezels do not have very precise coordinates for the game areas, and
	    hide the "bad pixels" with an alpha channel at 100%, so I must do something
	    for these broken artworks (which happen to be official ones sometimes !).
	    Solution for now : paint every pixel in the bezel in black if it's transparent*/
	 int x,y;
	 int depth = bytes_per_pixel(alpha_bitmap)*8;
	 int depthb = bytes_per_pixel(bezel_bitmap)*8;
	 printf("depth alpha %d bezel %d\n",depth,bytes_per_pixel(bezel_bitmap)*8);
	 if (depthb == 24 || depthb == 32) {
	   UINT8 *pixel;
	   for (y=0; y<bezel_bitmap->h; y++) {
	     pixel = alpha_bitmap->line[y];
	     for (x=0; x<bezel_bitmap->w; x++) {
	       if (!get_line_pixel(pixel,x,depth)) { // black pixel -> transp
		 if (depthb == 32) {
		   WriteLong(((UINT32*)bezel_bitmap->line[y])+x,0);
		 } else if (depthb==24) {
		   WriteWord((bezel_bitmap->line[y])+x*3,0);
		   WriteByte((bezel_bitmap->line[y])+x*3+2,0);
		 }
	       }
	     }
	   }
	 } else { // bpp 15 or 16
	   UINT8 *pixel;
	   for (y=0; y<bezel_bitmap->h; y++) {
	     pixel = alpha_bitmap->line[y];
	     for (x=0; x<bezel_bitmap->w; x++) {
	       if (!get_line_pixel(pixel,x,depth)) { // black pixel -> transp
		 WriteWord(((UINT16*)bezel_bitmap->line[y])+x,0);
	       }
	     }
	   }
	 }
       }
       destroy_bitmap(alpha_bitmap);
     } // if (alpha_bitmap...
   } // if (alphafile[0]...
   unzClose(uf);

   if (!bezel_bitmap) {
     print_debug("could not load png %s\n",file);
   }

   print_debug("bezel loaded %s\n",file);

   return;
}

int bezel_fix_screen_size(int *myw,int *myh) {
  /* Tell raine that we need a biger screen to fit the bezel */
  if (!current_game) return 0;
  int rotate_screen = (current_game->video->flags ^ display_cfg.user_rotate) & 3;
  if (rotate_screen == 1 || rotate_screen == 3) {
    int *dupe = myw;
    myw = myh;
    myh = dupe;
  }
  if (bezel_bitmap) {
    print_debug("bezel_fix_screen_size before : %d,%d factors %g,%g\n",*myw,*myh,w-x,h-y);

    *myw = round(*myw*(w-x));
    *myh = round(*myh*(h-y));
#ifndef RAINE_DOS
    if (sdl_overlay) {
      /* If we have an overlay then we can adjust this to any size
       * (otherwise the game screen has priority over the bezel) */
      if ((rotate_screen & 1) && (*myw > display_cfg.screen_y ||
	    *myh > display_cfg.screen_x)) {
	double ratio = *myw*1.0/ *myh;
	printf("bezel: overflow %d x %d of screen %d %d\n",*myw,*myh,display_cfg.screen_x,display_cfg.screen_y);
	if (*myw > *myh) {
	  *myw = display_cfg.screen_y;
	  *myh = *myw/ratio;
	} else {
	  if (ratio * display_cfg.screen_x < display_cfg.screen_y) {
	    *myh = display_cfg.screen_x;
	    *myw = ratio* *myh;
	  } else {
	    *myw = display_cfg.screen_y;
	    *myh = *myw/ratio;
	  }
	}
	if ((rotate_screen & 1) && (*myw > display_cfg.screen_y ||
	      *myh > display_cfg.screen_x)) {
	  printf("still overflow after %d %d\n",*myw,*myh);
	  printf("forcing size of screen...\n");
	  if (*myw > display_cfg.screen_y)
	    *myw = display_cfg.screen_y;
	  if (*myh > display_cfg.screen_x)
	    *myh = display_cfg.screen_x;
	}
	printf("bezel: fixed screen overflow, new size : %d x %d\n",*myw,*myh);
      } else if (((rotate_screen & 1) == 0) && (*myw > display_cfg.screen_x ||
	    *myh > display_cfg.screen_y)) {
	double ratio = *myw*1.0/ *myh;
	printf("bezel: horiz overflow %d x %d of screen %d %d\n",*myw,*myh,display_cfg.screen_x,display_cfg.screen_y);
	if (*myw > *myh) {
	  *myw = display_cfg.screen_x;
	  *myh = *myw/ratio;
	} else {
	  if (ratio * display_cfg.screen_y < display_cfg.screen_x) {
	    *myh = display_cfg.screen_y;
	    *myw = ratio* *myh;
	  } else {
	    *myw = display_cfg.screen_x;
	    *myh = *myw/ratio;
	  }
	}
	if ((*myw > display_cfg.screen_x ||
	      *myh > display_cfg.screen_y)) {
	  printf("still overflow after %d %d\n",*myw,*myh);
	  printf("forcing size of screen...\n");
	  if (*myw > display_cfg.screen_x)
	    *myw = display_cfg.screen_x;
	  if (*myh > display_cfg.screen_y)
	    *myh = display_cfg.screen_y;
	}
	printf("bezel: fixed screen overflow, new size : %d x %d\n",*myw,*myh);
      }
    }
#endif

    bezel_width = *myw;
    bezel_height = *myh;
    if (use_scale2x == 1) {
      /* This thing is becoming *REALLY* messy now... I should probably try
       * to rewrite the whole thing more cleanly one day... ! */
      bezel_width /= 2;
      bezel_height /= 2;
    } else if (use_scale2x == 2) {
      bezel_width /= 3;
      bezel_height /= 3;
    }
    *myw = round(*myw/(w-x));
    *myh = round(*myh/(h-y));
    print_debug("bezel_fix_screen_size after : %d,%d\n",*myw,*myh);
    return 1;
  }
  return 0;
}

void bezel_fix_screen_coordinates(int *destx,int *desty,int viewx,int viewy, int screenx, int screeny) {
  /* This thing is wicked, it can also move the game screen from the center of the
     display... We must recalculate from screenx and screeny to avoid the rounding errors */
  int rotate_screen = (current_game->video->flags ^ display_cfg.user_rotate) & 3;

  if (bezel_bitmap) {
    print_debug("bezel: before coords fix %d,%d view %d,%d rotate %d\n",*destx,*desty,viewx,viewy,rotate_screen);
    if (rotate_screen == 3 || rotate_screen == 1) { // 270
      *desty = round((screeny-viewy*(w+x))/2);
      *destx = round((screenx-viewx*(h+y))/2);
    } else {
      *destx = round((screenx-viewx*(w+x))/2);
      *desty = round((screeny-viewy*(h+y))/2);
    }
    print_debug("bezel: after coords fix %d,%d\n",*destx,*desty);
  }
}

#ifdef SDL
void fit_screen(SDL_Rect *area) {
  if (area->x < 0) { area->w += area->x; area->x = 0; }
  if (area->y < 0) { area->h += area->y; area->y = 0; }
  if (area->x+area->w > screen->w) area->w = screen->w-area->x;
  if (area->y+area->h > screen->h) area->h = screen->h-area->y;
}
#endif

void display_bezel() {
  /* A note about bezels and overlays :
   * it seems that some bezels are intended to work with a distorted aspect
   * ratio. For example, gunbird has -0.384,+1.384 for the position, which maps
   * to a bezel of 140 pixels on each side for a total length of 640.
   * So it means that their game screen has the dimensions 640-140*2 = 360x480
   * which makes an aspect ratio of 0.75, when gunbird should have a screen of
   * 224x320 with an aspect of 0.7... !
   *
   * Well 0.75 is the aspect ratio of our modern monitors, it's the aspect of
   * 320x240, 640x480, etc... so I guess I should add an option to fix these
   * aspect ratios when using acceleretad overlays.
   * In practice, it means that if the overlay resizes the gunbird game screen
   * to fit in 800x600 while keeping the original aspect ratio of 0.7, it's then
   * impossible to map the bezel on this surface without having black borders.
   * */

    if (!GameBitmap) return;
  if (bezel_bitmap && display_cfg.bpp > 8) {
    int rotate_screen = (current_game->video->flags ^ display_cfg.user_rotate) & 3;
    int bw = bezel_width, bh = bezel_height;
    int multw =1, multh = 1;
    int xoff2,yoff2,destx,desty,xxx,yyy;
    BITMAP *scaled_bezel;

    if (!bw || !bh) {
	    // if wants_switch_res = 0, then the bezel is not initalised when arriving here...
	    int x,y;
	    x = current_game->video->screen_x;
	    y = current_game->video->screen_y;
	    bezel_fix_screen_size(&x,&y);
	    bw = bezel_width;
	    bh = bezel_height;
	    printf("coordinates fix %d %d %d %d\n",x,y,bw,bh);
    }
    get_screen_coordinates(&xoff2,&yoff2,&destx,&desty,&xxx,&yyy);
#ifdef SDL
    if (sdl_overlay || sdl_screen->flags & SDL_OPENGL) {
      get_overlay_area(&destx,&desty,&xxx,&yyy);
      printf("get_overlay_area: destx %d desty %d w %d h %d\n",destx,desty,xxx,yyy);
    }
#endif
    if (display_cfg.scanlines & 2) {// halfheight...
      multh*=2;
    }
    if (display_cfg.scanlines == 3)
      multw*=2;
    if (
#ifndef SDL
      display_cfg.pixel_double==1 || display_cfg.eagle_fx ||
#endif
      use_scale2x==1) {
      multh*=2; multw*=2;
    } else if (use_scale2x == 2) {
      multh*=3; multw*=3;
#ifndef SDL
    } else if (display_cfg.pixel_double==2) {// double width
      multw*=2;
#endif
    }

    bw *= multw; bh *= multh;
#ifdef SDL
    if (sdl_overlay || sdl_screen->flags & SDL_OPENGL) {
      /* Here is the difficulty : here the bezel must be entierly independant
       * from the game screen and based only on what we know about overlay_area
       * which is the area to which the game screen is scaled when displayed.
       * More precisely :
       * the bezel must be scaled to (w-x)*overlay_width
       * and (h-y)*overlay_height where x,y,w,h are the values of the bezel
       * position parameter */
      if (rotate_screen == 1 || rotate_screen == 3) {
	bw = (w-x)*yyy;
	bh = (h-y)*xxx;
      } else {
	bw = (w-x)*xxx;
	bh = (h-y)*yyy;
      }
    }
    printf("bezel: create bitmap %dx%d zoom %g %g\n",bw,bh,bw*1.0/bezel_bitmap->w, bh*1.0/bezel_bitmap->h);
    SDL_Surface *scaled = rotozoomSurfaceXY(get_surface_from_bmp(bezel_bitmap),
      0.0, bw*1.0/bezel_bitmap->w, bh*1.0/bezel_bitmap->h, 1);
    scaled_bezel = surface_to_bmp(scaled);
#else
    scaled_bezel = create_bitmap_ex(bitmap_color_depth(bezel_bitmap),bw,bh);
    stretch_blit(bezel_bitmap,scaled_bezel,0,0,bezel_bitmap->w-1,bezel_bitmap->h-1,0,0,bw,bh);
#endif

    if (rotate_screen == 3 || rotate_screen == 1) { // 270
      desty += yyy*x*multh;
      destx += xxx*y*multw;
      printf("destx adjusted by %d x %g x %d = %g -> %d rotate_screen %d\n",xxx,y,multw,xxx*y*multw,destx,rotate_screen);
      printf("desty adjusted by %d x %g x %d = %g -> %d\n",yyy,x,multh,yyy*x*multh,desty);
#ifdef SDL
	int res = 0;
	SDL_Rect area;
	SDL_Surface *rotated;
	if (rotate_screen == 3)
	  rotated = rotozoomSurfaceXY(get_surface_from_bmp(scaled_bezel), 90.0, 1, 1, 0);
	else
	  rotated = rotozoomSurfaceXY(get_surface_from_bmp(scaled_bezel), -90.0, 1, 1, 0);
	printf("bliting bezel %d %d to %d %d from scaled %d %d dest %d %d mult %d %d\n",rotated->w,rotated->h,sdl_screen->w,sdl_screen->h,scaled_bezel->w,scaled_bezel->h,destx,desty,multw,multh);
	area.x = destx;
	area.y = desty;
	area.w = rotated->w;
	area.h = rotated->h;
	fit_screen(&area);
	if (sdl_screen->pixels)
	    res = SDL_BlitSurface(rotated, NULL, sdl_screen,&area);
	if (res)
	  printf("blit returned %d\n",res);
	SDL_FreeSurface(rotated);
	SDL_UpdateRects(sdl_screen,1,&area);
#else
	pivot_sprite(screen,scaled_bezel,destx,desty,scaled_bezel->w-1,0,itofix(-64));
#endif
    } else  {
      desty += yyy*y*multh;
      destx += xxx*x*multw;
#ifdef SDL
      if (sdl_screen->pixels) {
	  SDL_Rect area;
	  area.x = destx;
	  area.y = desty;
	  area.w = scaled_bezel->w;
	  area.h = scaled_bezel->h;
	  fit_screen(&area);
	  SDL_BlitSurface(get_surface_from_bmp(scaled_bezel),NULL,sdl_screen,NULL);
	  SDL_UpdateRects(sdl_screen,1,&area);
      }
#else
      blit(scaled_bezel,screen,0,0,destx,desty,scaled_bezel->w,scaled_bezel->h);
#endif
    }
    destroy_bitmap(scaled_bezel);
  }
}

double get_bezel_ratio() {
  if (bezel_bitmap && bezel_width) {
    return bezel_width*1.0/bezel_height;
  }
  return -1;
}

