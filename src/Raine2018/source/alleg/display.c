#include "raine.h"
#include "palette.h"
#ifndef RAINE_WIN32
#include "arcmon.h"
#endif
#include "rgui.h"
#include "blit.h" // reclipscreen
#include "gui.h" // wants_switch_res
#include "video/res.h"
#include "display.h"

void display_read_config() {
   if(display_cfg.scanlines == 2) display_cfg.screen_y <<= 1;

   display_cfg.screen_type	= raine_get_config_id(	"Display",      "screen_type",          display_cfg.screen_type);
   display_cfg.screen_x 	= raine_get_config_int( "Display",      "screen_x",             display_cfg.screen_x);
   display_cfg.screen_y 	= raine_get_config_int( "Display",      "screen_y",             display_cfg.screen_y);
   display_cfg.bpp		= raine_get_config_int( "Display",      "bpp",                  16);
   display_cfg.scanlines	= raine_get_config_int( "Display",      "scanlines",            0);
   display_cfg.vsync		= raine_get_config_int( "Display",      "vsync",                0);
   display_cfg.triple_buffer	= raine_get_config_int( "Display",      "triple_buffer",        0);
   display_cfg.eagle_fx 	= raine_get_config_int( "Display",      "eagle_fx",             0);
   display_cfg.stretch	= raine_get_config_int( "Display",      "stretch",             0);
   display_cfg.pixel_double	= raine_get_config_int( "Display",      "pixel_double",         0);
   use_scale2x	= raine_get_config_int( "Display",      "scale2x",         0);
   display_cfg.fast_set_pal	= raine_get_config_int( "Display",      "fast_set_pal",         1);
   display_cfg.screenshot_png = raine_get_config_int( "Display",      "screenshot_png",         1);
   video_fps = raine_get_config_int( "Display",      "video_fps",         15);

#ifdef RAINE_UNIX
   if (geteuid()>0) { // non root user can NOT write to the palette
	   display_cfg.fast_set_pal = 0;
   }
#endif
   display_cfg.user_rotate	= raine_get_config_int( "Display",      "rotate",               0);
   display_cfg.user_flip	= raine_get_config_int( "Display",      "flip",                 0);
   display_cfg.no_rotate	= raine_get_config_int( "Display",      "no_rotate",            0);
   display_cfg.no_flip		= raine_get_config_int( "Display",      "no_flip",              0);
   display_cfg.auto_mode_change      = raine_get_config_int( "Display",      "auto_mode_change",  1);
#ifdef RAINE_DOS
   display_cfg.arcade_h_timing	= raine_get_config_int( "Display",      "arcade_h_timing",      105);
   display_cfg.arcade_v_timing	= raine_get_config_int( "Display",      "arcade_v_timing",      9);
   display_cfg.arcade_center_x	= raine_get_config_int( "Display",      "arcade_center_x",      8);
   display_cfg.arcade_center_y	= raine_get_config_int( "Display",      "arcade_center_y",      4);
#endif

   if(display_cfg.scanlines == 2) display_cfg.screen_y >>= 1;

   if(display_cfg.vsync > 1) display_cfg.vsync = 0;
}

void display_write_config() {
   if(display_cfg.scanlines == 2) display_cfg.screen_y <<= 1;

   raine_set_config_id (	"Display",      "screen_type",          display_cfg.screen_type);
   raine_set_config_int(	"Display",      "screen_x",             display_cfg.screen_x);
   raine_set_config_int(	"Display",      "screen_y",             display_cfg.screen_y);
   raine_set_config_int(	"Display",      "scanlines",            display_cfg.scanlines);
   raine_set_config_int(	"Display",      "vsync",                display_cfg.vsync);
   raine_set_config_int(	"Display",      "triple_buffer",        display_cfg.triple_buffer);
   raine_set_config_int(	"Display",      "eagle_fx",             display_cfg.eagle_fx);
   raine_set_config_int(	"Display",      "scale2x",             use_scale2x);
   raine_set_config_int(	"Display",      "stretch",              display_cfg.stretch);
   raine_set_config_int(	"Display",      "pixel_double",         display_cfg.pixel_double);
   raine_set_config_int(	"Display",      "fast_set_pal",         display_cfg.fast_set_pal);
   raine_set_config_int(	"Display",      "screenshot_png",         display_cfg.screenshot_png);
   raine_set_config_int(	"Display",      "video_fps",         video_fps);

   raine_set_config_int(	"Display",      "rotate",               display_cfg.user_rotate);
   raine_set_config_int(	"Display",      "flip",                 display_cfg.user_flip);
   raine_set_config_int(	"Display",      "no_rotate",            display_cfg.no_rotate);
   raine_set_config_int(	"Display",      "no_flip",              display_cfg.no_flip);
   raine_set_config_int(	"Display",      "bpp",                  display_cfg.bpp);
   raine_set_config_int(	"Display",      "auto_mode_change",       display_cfg.auto_mode_change);

   if(display_cfg.scanlines == 2) display_cfg.screen_y >>= 1;

#ifdef RAINE_DOS
   raine_set_config_int(	"Display",      "arcade_h_timing",      display_cfg.arcade_h_timing);
   raine_set_config_int(	"Display",      "arcade_v_timing",      display_cfg.arcade_v_timing);
   raine_set_config_int(	"Display",      "arcade_center_x",      display_cfg.arcade_center_x);
   raine_set_config_int(	"Display",      "arcade_center_y",      display_cfg.arcade_center_y);
#endif
}

// Same thing, but saved as specific game parameters...
void load_screen_settings(char *section)
{
   if(raine_cfg.save_game_screen_settings){

   // DISPLAY

   if(display_cfg.scanlines == 2) display_cfg.screen_y <<= 1;

   display_cfg.screen_type	= raine_get_config_id(	section,	"screen_type",		display_cfg.screen_type);
   display_cfg.frame_skip	= raine_get_config_int( section,        "frame_skip", 0);
   display_cfg.bpp		= raine_get_config_int( section,        "bpp",                  display_cfg.bpp);
   display_cfg.stretch	        = raine_get_config_int( section,        "stretch",              display_cfg.stretch);
   display_cfg.screen_x		= raine_get_config_int(	section,	"screen_x",		display_cfg.screen_x);
   display_cfg.screen_y		= raine_get_config_int(	section,	"screen_y",		display_cfg.screen_y);
   display_cfg.scanlines	= raine_get_config_int(	section,	"scanlines",		display_cfg.scanlines);
   display_cfg.vsync		= raine_get_config_int(	section,	"vsync",		display_cfg.vsync);
   display_cfg.triple_buffer	= raine_get_config_int(	section,	"triple_buffer",	display_cfg.triple_buffer);
   display_cfg.eagle_fx		= raine_get_config_int(	section,	"eagle_fx",		display_cfg.eagle_fx);
   display_cfg.pixel_double	= raine_get_config_int(	section,	"pixel_double",		display_cfg.pixel_double);

   if(display_cfg.scanlines == 2) display_cfg.screen_y >>= 1;

   if(display_cfg.vsync > 1) display_cfg.vsync = 0;

   }
}

void save_screen_settings(char *section)
{
   // remove all old settings

   raine_clear_config_section(section);

   if(raine_cfg.save_game_screen_settings){

   // DISPLAY

   if(display_cfg.scanlines == 2) display_cfg.screen_y <<= 1;

   raine_set_config_int(	section,      "frame_skip", display_cfg.frame_skip);
   raine_set_config_id (	section,	"screen_type",		display_cfg.screen_type);
   raine_set_config_int(	section,        "bpp",                  display_cfg.bpp);
   raine_set_config_int(	section,	"screen_x",		display_cfg.screen_x);
   raine_set_config_int(	section,        "stretch",              display_cfg.stretch);
   raine_set_config_int(	section,	"screen_y",		display_cfg.screen_y);
   raine_set_config_int(	section,	"scanlines",		display_cfg.scanlines);
   raine_set_config_int(	section,	"vsync",		display_cfg.vsync);
   raine_set_config_int(	section,	"triple_buffer",	display_cfg.triple_buffer);
   raine_set_config_int(	section,	"eagle_fx",		display_cfg.eagle_fx);
   raine_set_config_int(	section,	"pixel_double",		display_cfg.pixel_double);

   if(display_cfg.scanlines == 2) display_cfg.screen_y >>= 1;

   }
}

/* As you could guess, this file includes all the functions to setup video
   modes. Entry points :
void init_display();
void ScreenChange(void); -> called when the resolution must be changed
void set_default_video_mode() -> restore default values in display_cfg
 */

extern int screen_valid; // gui.c
extern void centre_all_dialogs(void); // gui.c
extern int fbcon_enabled; // rgui.c
extern void update_stretch(); // stretch.c

// All the first functions are here to setup special video modes.
// These modes were interesting in the old dos days, when you had to actually
// setup the mode you wanted on the screen. Nowdays, you usually choose
// hardware scaling instead - it makes things MUCH easier.

#ifdef RAINE_UNIX
#ifndef ALLEGRO_LINUX
// These are not defined by freebsd, but they could...
static inline unsigned char inportb(unsigned short port)
{
   unsigned char value;
   __asm__ volatile ("inb %1, %0" : "=a" (value) : "d" (port));
   return value;
}

static inline void outportb(unsigned short port, unsigned char value)
{
   __asm__ volatile ("outb %0, %1" : : "a" (value), "d" (port));
}

static inline void outportw(unsigned short port, unsigned short value)
{
   __asm__ volatile ("outw %0, %1" : : "a" (value), "d" (port));
}

#endif

#define outp(a,b)	outportb(a,b)
#define inp(a)		inportb(a)

/* #define strcasecmp	_stricmp */

#endif

#define enable()	asm(" sti")
#define disable()	asm(" cli")

BITMAP *tpage[3];

void clear_raine_screen() {
  if(display_cfg.triple_buffer){
    int ta;
    for (ta=0; ta<3; ta++)
      clear_bitmap(tpage[ta]);
  } else {
    clear_bitmap(screen);
  }
}

static int set_triple_buffer_mode(int type, int width, int height) {
  int ret;
  if ((ret = set_gfx_mode(type,width,height,0,height*3))) {
    if ((ret = set_gfx_mode(type,width,height,0,0)))
      return ret;
  }

  /* if triple buffering isn't available, try to enable it */
  if (!(gfx_capabilities & GFX_CAN_TRIPLE_BUFFER))
    enable_triple_buffer();

  /* if that didn't work, give up */
  if (!(gfx_capabilities & GFX_CAN_TRIPLE_BUFFER))
    return 1;

  print_debug("set_triple_buffer_mode successfull !\n");
  for (ret = 0; ret<3; ret++) {
    tpage[ret] = create_video_bitmap(width,height);
    if (!tpage[ret]) {
	    print_debug("Impossible to create video bitmap %d\n",ret);
	    return 1;
    }
    clear_bitmap(tpage[ret]);
  }

  // it worked !
  return 0;
}

#ifndef RAINE_WIN32

static DEF_INLINE void WaitVBlank(void)
{
  while(inportb(0x3DA)&0x08);
  while(!(inportb(0x3DA)&0x08));
}

static int Stretch256x240(int SType)
{
   static UINT8 fwnesdata[] = {
   0x4F,0x3F,0x40,0x92,0x46,0x10,0x0D,0x3E,
   0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x00,
   0xEA,0xAC,0xDF,0x20,0x00,0xE7,0x06,0xE3
   };

   int ta,ret;

   if(display_cfg.triple_buffer)
      ret = set_triple_buffer_mode(SType,256,240);
   else
      ret = set_gfx_mode(SType,256,240,256,240);

   if(!ret){

   disable();
   WaitVBlank();

   //outportw(0x3C4,0x100);
   outportb(0x3C2,0xE3);
   //outportw(0x3C4,0x300);

   outportw(0x3D4,((fwnesdata[0x11]&0x7F)<<8)+0x11);
   for(ta=0;ta<24;ta++){
      outportw(0x3D4,(fwnesdata[ta]<<8)+ta);
   }
   //inportb(0x3DA);
   //outportb(0x3c0,0x31);
   //outportb(0x3c0,0x3f);
   inportb(0x3DA);
   //outportb(0x3C0,0x11  | 0x20);
   //outportb(0x3C0,0x40);
   enable();

   }
   return ret;
}

// SetDarkForceMode():
// Set a normal vesa mode (via allegro), then divide
// the number of screen lines...

static int SetDarkForceMode(int SType, int SX, int SY, int NewSY)
{
   int ret,lines;
   UINT8 scanline;

   if(display_cfg.triple_buffer)
      ret = set_triple_buffer_mode(SType,SX,SY);
   else
      ret = set_gfx_mode(SType,SX,SY,SX,SY);

   if(!ret){
      lines=SY/NewSY;
      if(lines<1)lines=1;
      if(lines>4)lines=4;
      outp(0x3D4,0x09); 	// CRTC Register index 9
      scanline=inp(0x3D5);	// get scanline height
      scanline&=0x60;		// clear any existing bits
      scanline|=(lines-1);	// set multiply bits
      outp(0x3D5,scanline);	// set new line height
   }

   return ret;
}

// Set320x256():
// Set a normal mode-x mode (via allegro), then twiddle
// the vga registers and the vtable

static int Set320x256(int SType)
{
   int n,ret;
   UINT16 port;
   UINT8 *q,reg,data;
   static unsigned char gfx_320x256_data[] = {
      194,3,0,227,212,3,0,95,212,3,1,79,212,3,2,80,212,3,3,130,212,3,4,84,212,3,5,154,212,3,6,35,212,
      3,7,178,212,3,8,0,212,3,9,97,212,3,16,10,212,3,17,172,212,3,18,255,212,3,19,40,212,3,20,0,212,3,
      21,7,212,3,22,26,212,3,23,227,196,3,1,1,196,3,4,6,206,3,5,64,206,3,6,5,192,3,16,65,192,3,19,
      0,};

   if(display_cfg.triple_buffer)
      ret = set_triple_buffer_mode(SType,320,480);
   else
      ret = set_gfx_mode(SType,320,480,320,256);

   if(ret)
      return ret;

   disable();
   WaitVBlank();

   /* ready the vga registers */
   outp(0x3d4,0x11);
   data = inp(0x3d5) & 0x7f;
   outp(0x3d4,0x11);
   outp(0x3d5,data);

   n = 25;
   q = &gfx_320x256_data[0];
   do {
      port = *q++;
      port |= ((*q++) << 8);
      reg = *q++;
      data = *q++;
      switch(port)
      {
      case 0x3c0:
	 inp(0x3da);	     /* reset read/write flip-flop */
	 outp(0x3c0, reg | 0x20);
				 /* ensure VGA output is enabled */
	 outp(0x3c0, data);
	 break;

      case 0x3c2:
      case 0x3c3:
	 outp(port, data);   /* directly to the port */
			break;

      case 0x3c4:
      case 0x3ce:
      case 0x3d4:
      default:			 /* This is the default method: */
	 outp(port, reg);    /* index to port		    */
	 outp(port+1, data); /* value to port+1 	    */
			break;
      }
   } while(--n);

   enable();
   screen->h = 256;
   return ret;
}

static int set_arcade_mode(int SType, int SX, int SY)
{
   int ret=1;
#ifdef GFX_MODEX
// Actually GFX_MODEX is defined in dos and in linux.
// Apparently it is not defined in freebsd...

   // Currently only accept 320x240

   if((SX!=320)||(SY!=240))
      return -1;

   // Set Mode X as the base mode

   if(display_cfg.triple_buffer)
      ret = set_triple_buffer_mode(GFX_MODEX,SX,SY);
   else
      ret = set_gfx_mode(GFX_MODEX,SX,SY,SX,SY);

   // Apply hacks for arcade monitor rates

   if(!ret){
      arcade_monitor_mode(
	 display_cfg.arcade_h_timing,
	 display_cfg.arcade_v_timing,
	 display_cfg.arcade_center_x,
	 display_cfg.arcade_center_y
      );
   }

#endif
   return ret;

}
#endif // #ifndef RAINE_WIN32

static int raine_set_gfx_mode(int SType,int SX,int SY)
{
  int ret;
#ifdef RAINE_DEBUG
   print_debug("raine_gfx_mode bpp %d type %x x %d y %d display_cfg:%dx%d\n",display_cfg.bpp,SType,SX,SY,display_cfg.screen_x,display_cfg.screen_y);
#endif
   set_color_depth(display_cfg.bpp);
#ifndef RAINE_WIN32
#ifdef RAINE_UNIX
   if (!x_display) {
#endif
     if((SX==256)&&(SY==240)) return Stretch256x240(SType);
     if((SX==320)&&(SY==256)) return Set320x256(SType);

     if((SX==400)&&(SY==150)) return SetDarkForceMode(SType,SX,300,SY);
     if((SX==640)&&(SY==100)) return SetDarkForceMode(SType,SX,400,SY);
     if((SX==640)&&(SY==150)) return SetDarkForceMode(SType,SX,400,SY);
     if((SX==640)&&(SY==200)) return SetDarkForceMode(SType,SX,400,SY);
     if((SX==640)&&(SY==120)) return SetDarkForceMode(SType,SX,480,SY);
     if((SX==640)&&(SY==160)) return SetDarkForceMode(SType,SX,480,SY);
     if((SX==640)&&(SY==240)) return SetDarkForceMode(SType,SX,480,SY);
     if((SX==800)&&(SY==150)) return SetDarkForceMode(SType,SX,600,SY);
     if((SX==800)&&(SY==200)) return SetDarkForceMode(SType,SX,600,SY);
     if((SX==800)&&(SY==300)) return SetDarkForceMode(SType,SX,600,SY);
     if((SX==1024)&&(SY==192)) return SetDarkForceMode(SType,SX,768,SY);
     if((SX==1024)&&(SY==256)) return SetDarkForceMode(SType,SX,768,SY);
     if((SX==1024)&&(SY==384)) return SetDarkForceMode(SType,SX,768,SY);

#ifdef GFX_DRIVER_MODEX
     if(SType==GFX_ARCMON) return set_arcade_mode(SType,SX,SY);
#endif
#ifdef RAINE_UNIX
   }
#endif
#endif

   if(display_cfg.triple_buffer)
      ret= set_triple_buffer_mode(SType,SX,SY);
   else
      ret= set_gfx_mode(SType,SX,SY,SX,SY);
#ifdef RAINE_DEBUG
   print_debug("raine_gfx_mode result %d bpp %d\n",ret,get_color_depth());
#endif
   if (ret < 0)
     allegro_message(allegro_error);

   return ret;
}

static int new_set_gfx_mode(int SType,int SX,int SY,int SLines)
{
  int ta;

  screen_valid=0;

  if(SLines==0){				// Set a Normal Mode
    ta=raine_set_gfx_mode(SType,SX,SY);
    if(!ta){
      screen->w=SX;
      screen->h=SY;
      screen->cr=screen->w;
      screen->cb=screen->h;
      gfx_driver->w=screen->w;
      gfx_driver->h=screen->h;
      centre_all_dialogs();
      update_stretch();
    }
    return ta;
  }
  else
    {
      // Set a Mode with Scanlines Hack
      ta=raine_set_gfx_mode(SType,SX,SY);
      if(!ta){
	screen->w=SX;
	screen->h=SY;
	screen->cr=screen->w;
	screen->cb=screen->h;
	gfx_driver->w=screen->w;
	gfx_driver->h=screen->h;
	centre_all_dialogs();
      }
      return ta;
    }
  return -1; // Error : can't set mode
}

void set_default_video_mode() {
  // Called at raine startup for the default values and when setting
  // a configured video mode fails.
  VIDEO_INFO vid;
  set_color_depth(8);

  set_color_conversion(COLORCONV_TOTAL);
  wants_switch_res = 1;
#ifdef RAINE_WIN32
  /* For windows, some setups are so weird that it's better to choose
   * a windowed default video mode ! */
  display_cfg.screen_type	= GFX_DIRECTX_WIN;
   display_cfg.bpp = 16;
#elif defined(RAINE_UNIX)
   if (x_display) {
     display_cfg.screen_type = GFX_XWINDOWS;
     display_cfg.bpp = 16;
   } else
#ifdef GFX_SVGA
     display_cfg.screen_type	= GFX_SVGALIB;
#elif defined(GFX_MODEX)
   display_cfg.screen_type	= GFX_MODEX;
#else
   display_cfg.screen_type	= GFX_AUTODETECT;
#endif
#else
  // dos
   display_cfg.screen_type = GFX_AUTODETECT;
#endif

   /* Chosses the 1st video mode >= 320x240 */
   vid.screen_x = 320;
   vid.screen_y = 240;
   vid.flags = 0;
   switch_res(&vid);
   display_cfg.screen_x = bestw;
   display_cfg.screen_y = besth;
   if (bestbpp) display_cfg.bpp = bestbpp;

   print_debug("set_default_video_mode: type %x %dx%d auto_mode_change %d\n",display_cfg.screen_type,display_cfg.screen_x,display_cfg.screen_y,display_cfg.auto_mode_change);
}

void init_display() {
  if(new_set_gfx_mode(display_cfg.screen_type,display_cfg.screen_x,display_cfg.screen_y,display_cfg.scanlines)!=0){
    if (display_cfg.bpp != 8) {
      display_cfg.bpp = 8;
    }

    set_default_video_mode();

    if(new_set_gfx_mode(display_cfg.screen_type,display_cfg.screen_x,display_cfg.screen_y,0)){
	printf("%s\n",raine_translate_text("Unable to detect any screenmode."));
#ifdef RAINE_UNIX
	printf("%s\n",raine_translate_text("On the console, you need to be root to use svgalib (or modex) !"));
#else
	printf("%s\n",raine_translate_text("Get Display Doctor from www.scitechsoft.com to fix this."));
#endif
	printf("%s\n\n",raine_translate_text("Mail about this problem is not appreciated!"));
	exit(1);
      }
  }
  display_cfg.screen_type = gfx_driver->id; // get rid of autodetect effect
  build_mode_list();
}

void ScreenChange(void)
{
    show_mouse(NULL);

   if(new_set_gfx_mode(display_cfg.screen_type,display_cfg.screen_x,display_cfg.screen_y,display_cfg.scanlines)){	// Didn't work:
      memcpy(&display_cfg, &prev_display_cfg, sizeof(DISPLAY_CFG));
      new_set_gfx_mode(display_cfg.screen_type,display_cfg.screen_x,display_cfg.screen_y,display_cfg.scanlines);	// Revert to old mode
   }
   else{
     ReClipScreen();
      if (prev_display_cfg.bpp != display_cfg.bpp) {
	if (current_colour_mapper){
	  set_colour_mapper(current_colour_mapper);
	  ResetPalette();
	}
      }
   }

   show_mouse(screen);
}

