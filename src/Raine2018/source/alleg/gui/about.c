#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"

#include "gui.h"

#include "about.h"

#include "games.h"
#include "tilemod.h"
#include "palette.h"
#include "sasound.h"
#include "ingame.h"
#include "profile.h" // palette animation (ingame_timer...)
#include "version.h" // Little funny gcc version (!)
#include "dejap.h" // companies logos in raine.dat
#include "history.h"
#include "cpuid.h"
#include "config.h"

char about0[64];
char about1[64];
char about2[64];
char about3[64];
char about4[64];
char about5[64];
char about6[64];
char about7[64];
char about8[64];
char about9[64];

#define WIDTH 300
#define MAX_LEN 32000

static int len;

static void add_text(char *buff,const char *format, ...)
{
  char tbuff[512];
  int tlen;
   va_list ap;
   va_start(ap,format);
   vsprintf(tbuff,format,ap);
   va_end(ap);
   tlen = strlen(tbuff);
   if (len+tlen < MAX_LEN) {
     strcpy(&buff[len],tbuff);
     len += tlen;
   }
}

DIALOG about_cpus[] =
{
   /* (dialog proc)      (x)  (y)  (w)  (h) (fg) (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,  0,   0, WIDTH, 120, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Cpu Emulators"},
   { x_raine_button_proc,  8, 100,  32,  16, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Okay"},
   { d_raine_textbox_proc, 8, 20, 284, 70, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { NULL,                 0,   0,   0,   0,   0,   0,  0,    0,       0,    0,    NULL}
};

static int about_cpu_emulators_proc(int msg, DIALOG *d, int c)
{
  int ret;

  ret = x_raine_button_proc(msg, d, c);

  if(ret==D_CLOSE){
    char *text_data;

    Unselect_Button(d);
    FadeGUI();

      text_data = malloc(MAX_LEN);
      len = 0;

      add_text(text_data, "Starscream 0.26r2 by Neill Corlett\n");
      add_text(text_data, "MZ80 3.4raine by Neill Bradley\n");
      add_text(text_data, "M6502 1.6raine2 by Neill Bradley\n");
      add_text(text_data, "UAE 68020 Emulator : old hacked asm version\n");
      add_text(text_data, "\nMCU 68705: statically recompiled code by Richard Mitton\n");

      about_cpus[2].d1 = 0;
      about_cpus[2].d2 = 0;
      about_cpus[2].dp = text_data;

      ret = raine_do_dialog(about_cpus,-1);

      free(text_data);
      ret = D_REDRAW;
  }
  return ret;
}

DIALOG about_raine[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,0,   0,   240, 210,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "About Raine"},
   { d_bitmap_proc,      0,   0,   0,   0,    0,               0,                   0,    0,       0,    0,    NULL},
   { x_raine_button_proc,8,   180, 32,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Okay"},
   { x_ctext_proc,       120, 54,  1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about0},
   { x_ctext_proc,       120, 64,  1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about1},
   { x_ctext_proc,       120, 84,  1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about2},
   { x_ctext_proc,       120, 94,  1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about3},
   { x_ctext_proc,       120, 104, 1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about4},
   { x_ctext_proc,       120, 114, 1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about5},
   { x_ctext_proc,       120, 134, 1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about6},
   { x_ctext_proc,       120, 144, 1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about7},
   { x_ctext_proc,       120, 154, 1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about8},
   { x_ctext_proc,       120, 164, 1,   1,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    about9},
   { cycle_proc,         70,  18,  93,  23,   GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { about_game_proc,    44,  180, 64,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'G',  D_EXIT,  0,    0,    "&Game Info"},
   { about_cpu_emulators_proc,    112,  180, 74,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'G',  D_EXIT,  0,    0,    "&Cpu Emulators"},
   { NULL,               0,   0,   0,   0,    0,    0,    0,    0,       0,    0,    NULL}
};

DIALOG about_game[] =
{
   /* (dialog proc)      (x)  (y)  (w)  (h) (fg) (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,  0,   0, WIDTH, 186, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Game Information"},
   { d_bitmap_proc,        0,   0,   0,   0,   0,   0,  0,    0,       0,    0,    NULL},
   { x_raine_button_proc,  8, 162,  32,  16, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  'O',  D_EXIT,  0,    0,    "&Okay"},
   { d_raine_textbox_proc, 8,  54, 284, 102, GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL},
   { NULL,                 0,   0,   0,   0,   0,   0,  0,    0,       0,    0,    NULL}
};

// about_proc():
// Setup and display the about dialog

static int cycle_logo_pal;

static char *OSName(void)
{
   switch(os_type){
   case OSTYPE_UNKNOWN   : return "unknown, or regular MSDOS";
   case OSTYPE_WIN3      : return "Windows 3.1 or earlier";
   case OSTYPE_WIN95     : return "Windows 95";
   case OSTYPE_WIN98     : return "Windows 98";
   case OSTYPE_WINME     : return "Windows ME";
   case OSTYPE_WINNT     : return "Windows NT";
   case OSTYPE_WIN2000   : return "Windows 2000";
   case OSTYPE_WINXP     : return "Windows XP";
   case OSTYPE_OS2       : return "OS/2";
   case OSTYPE_WARP      : return "OS/2 Warp 3";
   case OSTYPE_DOSEMU    : return "Linux DOSEMU";
   case OSTYPE_OPENDOS   : return "Caldera OpenDOS";
   case OSTYPE_LINUX     : return "Linux";
   case OSTYPE_SUNOS     : return "SunOS/Solaris";
   case OSTYPE_FREEBSD   : return "FreeBSD";
   case OSTYPE_NETBSD    : return "NetBSD";
   case OSTYPE_IRIX      : return "IRIX";
#ifdef OSTYPE_DARWIN
   case OSTYPE_DARWIN    : return "Darwin";
#endif
   case OSTYPE_QNX       : return "QNX";
   case OSTYPE_UNIX      : return "Unknown Unix variant";
   case OSTYPE_BEOS      : return "BeOS";
   case OSTYPE_MACOS     : return "MacOS";
   }
   return "???";
}

char raine_cpu_model[80];

int about_proc(int msg, DIALOG *d, int c)
{
  BITMAP *logo;
  int ret = x_raine_button_proc(msg, d, c);

  if(ret==D_CLOSE){

    Unselect_Button(d);
    FadeGUI();
    check_cpu();
    sprintf(about0, EMUNAME " " VERSION " (c)1998-2015 " HANDLE);
    sprintf(about1, "Compiled on " __DATE__ " (" __TIME__ ")");
#ifdef __GNUC__
    {
      int major = __GNUC__;
      int minor = __GNUC_MINOR__;
#ifdef __GNUC_PATCHLEVEL__
      int patchlevel = __GNUC_PATCHLEVEL__;
#else
      int patchlevel = 0;
#endif

      sprintf(about2,"GCC %d.%d.%d",major,minor,patchlevel);
    }
#else
    sprintf(about2,"GCC ???");
#endif
      sprintf(about3, "Allegro " ALLEGRO_VERSION_STR " by Shawn Hargreaves");
#ifdef RAINE_WIN32
      // MMX status is unknown in win32 because allegro includes a header file from its
      // object directory for that !!! So the capabilities are not saved for programs
      // using allegro, just for allegro itself (contrary to the unix version)
      strcpy(about4,"");
#else
      sprintf(about4, "Allegro compiled ");
#ifdef ALLEGRO_MMX
      strcat(about4,"WITH");
#else
      strcat(about4,"WITHOUT");
#endif
      strcat(about4," MMX optimizations");
#endif

      if (raine_cpu_capabilities & CPU_MMX)
	sprintf(about5,"Raine uses MMX for Scale2X effect");
      else
	sprintf(about5, " ");

      sprintf(about6, "Host System: %s", OSName());
      sprintf(about7, "CPU: %s", raine_cpu_model);
#ifdef RDTSC_PROFILE
      if (cycles_per_second) sprintf(about7+strlen(about7)," at %d MHz",cycles_per_second/1000000);
#endif
      sprintf(about8, " ");
      sprintf(about9, "http://raine.1emulation.com/");

      logo = make_mapped_bitmap(RaineData[RaineLogo].dat, &cycle_logo_pal, RaineData[GUIPalette].dat, 7);

      about_raine[1].proc = &d_bitmap_proc;
      about_raine[1].dp   = logo;
      about_raine[1].x    = about_raine[0].x + ((120 * text_height(gui_main_font)) / 8) - (logo->w / 2);
      about_raine[1].y    = about_raine[0].y + (( 32 * text_height(gui_main_font)) / 8) - (logo->h / 2);
      about_raine[1].w    = logo->w;
      about_raine[1].h    = logo->h;

      ret = raine_do_dialog(about_raine, -1);

      destroy_mapped_bitmap(logo, 7);

      return D_REDRAW;
   }

   return ret;
}

// cycle_proc():
// Colour Cycling for the 'About Raine' logo

int cycle_proc(int msg, DIALOG *d, int c)
{
   static int tt;
   static UINT32 ts;
   static UINT8 *CYC;
   static PALETTE cyc_pal;
   static int dirty_palette;
   static UINT32 timer;

   UINT32 ta;

   switch(msg){
      case MSG_START:	// Startup
         CYC = malloc(4*192*2);

         for(ta=0;ta<64;ta++){
            CYC[(  0<<2)+(ta<<2)+0] = 63 - ta;
            CYC[(  0<<2)+(ta<<2)+1] = 63;
            CYC[(  0<<2)+(ta<<2)+2] = ta;

            CYC[( 64<<2)+(ta<<2)+0] = ta;
            CYC[( 64<<2)+(ta<<2)+1] = 63 - ta;
            CYC[( 64<<2)+(ta<<2)+2] = 63;

            CYC[(128<<2)+(ta<<2)+0] = 63;
            CYC[(128<<2)+(ta<<2)+1] = ta;
            CYC[(128<<2)+(ta<<2)+2] = 63 - ta;
         }

         for(ta=0;ta<192;ta++){
            CYC[((ta+192)<<2)+0] = CYC[(ta<<2)+0];
            CYC[((ta+192)<<2)+1] = CYC[(ta<<2)+1];
            CYC[((ta+192)<<2)+2] = CYC[(ta<<2)+2];
         }

         memcpy(&cyc_pal, &gui_pal, 256*4);

         tt=0;
         ts=0;
         start_ingame_timer();
	 timer = read_ingame_timer();
         dirty_palette=1;
      break;
      case MSG_END:	// Shutdown
         gui_pal[cycle_logo_pal+1].r=cyc_pal[cycle_logo_pal+1].r;
         gui_pal[cycle_logo_pal+1].g=cyc_pal[cycle_logo_pal+1].g;
         gui_pal[cycle_logo_pal+1].b=cyc_pal[cycle_logo_pal+1].b;
         gui_pal[cycle_logo_pal+2].r=cyc_pal[cycle_logo_pal+2].r;
         gui_pal[cycle_logo_pal+2].g=cyc_pal[cycle_logo_pal+2].g;
         gui_pal[cycle_logo_pal+2].b=cyc_pal[cycle_logo_pal+2].b;
         gui_pal[cycle_logo_pal+3].r=cyc_pal[cycle_logo_pal+3].r;
         gui_pal[cycle_logo_pal+3].g=cyc_pal[cycle_logo_pal+3].g;
         gui_pal[cycle_logo_pal+3].b=cyc_pal[cycle_logo_pal+3].b;
         gui_pal[cycle_logo_pal+4].r=cyc_pal[cycle_logo_pal+4].r;
         gui_pal[cycle_logo_pal+4].g=cyc_pal[cycle_logo_pal+4].g;
         gui_pal[cycle_logo_pal+4].b=cyc_pal[cycle_logo_pal+4].b;
         gui_pal[cycle_logo_pal+5].r=cyc_pal[cycle_logo_pal+5].r;
         gui_pal[cycle_logo_pal+5].g=cyc_pal[cycle_logo_pal+5].g;
         gui_pal[cycle_logo_pal+5].b=cyc_pal[cycle_logo_pal+5].b;
         set_palette_range(gui_pal,cycle_logo_pal+1,cycle_logo_pal+5,0);
         stop_ingame_timer();
         free(CYC);
	 restore_ingame_timer(timer);
      break;
      case MSG_IDLE:	// Update
         if( read_ingame_timer() != ts){
         ts = read_ingame_timer();
         gui_pal[cycle_logo_pal+1].r=CYC[((tt+0)<<2)];
         gui_pal[cycle_logo_pal+1].g=CYC[((tt+0)<<2)+1];
         gui_pal[cycle_logo_pal+1].b=CYC[((tt+0)<<2)+2];
         gui_pal[cycle_logo_pal+2].r=CYC[((tt+32)<<2)];
         gui_pal[cycle_logo_pal+2].g=CYC[((tt+32)<<2)+1];
         gui_pal[cycle_logo_pal+2].b=CYC[((tt+32)<<2)+2];
         gui_pal[cycle_logo_pal+3].r=CYC[((tt+64)<<2)];
         gui_pal[cycle_logo_pal+3].g=CYC[((tt+64)<<2)+1];
         gui_pal[cycle_logo_pal+3].b=CYC[((tt+64)<<2)+2];
         gui_pal[cycle_logo_pal+4].r=CYC[((tt+96)<<2)];
         gui_pal[cycle_logo_pal+4].g=CYC[((tt+96)<<2)+1];
         gui_pal[cycle_logo_pal+4].b=CYC[((tt+96)<<2)+2];
         gui_pal[cycle_logo_pal+5].r=CYC[((tt+128)<<2)];
         gui_pal[cycle_logo_pal+5].g=CYC[((tt+128)<<2)+1];
         gui_pal[cycle_logo_pal+5].b=CYC[((tt+128)<<2)+2];
         tt++;
         if(tt>=192) tt=0;
         dirty_palette=1;
         SEND_MESSAGE(d,MSG_DRAW,0);
         }
      break;
      case MSG_DRAW:	// Draw
         if(dirty_palette){
            dirty_palette=0;
            set_palette_range(gui_pal,cycle_logo_pal+1,cycle_logo_pal+5,0);
         }
         //textout(screen,font,gamename,64,tt,255);
      break;
      case MSG_CLICK:	// Draw
         rgui_cfg.gui_col_text_1     = ((rgui_cfg.gui_col_text_1>>8)&0xFFFF)     | ((rgui_cfg.gui_col_text_1<<16)&0xFF0000);
         rgui_cfg.gui_col_text_2     = ((rgui_cfg.gui_col_text_2>>8)&0xFFFF)     | ((rgui_cfg.gui_col_text_2<<16)&0xFF0000);
         rgui_cfg.gui_col_black      = ((rgui_cfg.gui_col_black>>8)&0xFFFF)      | ((rgui_cfg.gui_col_black<<16)&0xFF0000);
         rgui_cfg.gui_col_select     = ((rgui_cfg.gui_col_select>>8)&0xFFFF)     | ((rgui_cfg.gui_col_select<<16)&0xFF0000);
         rgui_cfg.gui_box_col_high_2 = ((rgui_cfg.gui_box_col_high_2>>8)&0xFFFF) | ((rgui_cfg.gui_box_col_high_2<<16)&0xFF0000);
         rgui_cfg.gui_box_col_high_1 = ((rgui_cfg.gui_box_col_high_1>>8)&0xFFFF) | ((rgui_cfg.gui_box_col_high_1<<16)&0xFF0000);
         rgui_cfg.gui_box_col_middle = ((rgui_cfg.gui_box_col_middle>>8)&0xFFFF) | ((rgui_cfg.gui_box_col_middle<<16)&0xFF0000);
         rgui_cfg.gui_box_col_low_1  = ((rgui_cfg.gui_box_col_low_1>>8)&0xFFFF)  | ((rgui_cfg.gui_box_col_low_1<<16)&0xFF0000);
         rgui_cfg.gui_box_col_low_2  = ((rgui_cfg.gui_box_col_low_2>>8)&0xFFFF)  | ((rgui_cfg.gui_box_col_low_2<<16)&0xFF0000);

         set_gui_palette();

         set_palette_range(gui_pal,0,255,0);
      break;
      default:
      break;
   }

   return D_O_K;
}

// about_game_proc():
// Setup and display the about game dialog
extern struct SOUND_CHIP sound_chip_list[]; // declared in sasound / alsound

int about_game_proc(int msg, DIALOG *d, int c)
{
   char *text_data;
   BITMAP *logo,*logo_2=0;
   PALETTE *logo_pal;
   DATAFILE *company_logo;
   const DIR_INFO *dir_list;
   const ROM_INFO *rom_list;
   const VIDEO_INFO *vid_info;
   int ret,romof,cloneof,j;
   UINT32 i;
   GAME_MAIN *game_info;

   ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){

   if(current_game){

      Unselect_Button(d);
      FadeGUI();

      text_data = malloc(MAX_LEN);

      game_info = current_game;

      if (history) {
	strncpy(text_data,history,MAX_LEN);
	text_data[MAX_LEN-1] = 0;
      } else
	text_data[0] = 0;
      len = strlen(text_data);

      add_text(text_data,"Game:\n   %s\n\n", game_info->long_name);

      add_text(text_data,"Company:\n   %s\n\n", game_company_name(game_info->company_id));

      add_text(text_data,"Year:\n   %4d\n\n", game_info->year);

      /*

      cpu %s %d

      */

      add_text(text_data,"CPU:\n");
      if (StarScreamEngine)
	add_text(text_data,"   M68000 x %d\n",StarScreamEngine);
      if (MZ80Engine)
	add_text(text_data,"   Z80 x %d\n",MZ80Engine);
#ifdef HAVE_6502
      if (M6502Engine)
	add_text(text_data,"   M6502 x %d\n",M6502Engine);
#endif
#ifndef NO020
      if(MC68020)
	add_text(text_data,"   M68020 x 1\n");
#endif
      add_text(text_data,"\n");

      /*

      audio %s

      */

      if (game_info->sound) {
         add_text(text_data,"Audio:\n");
	 for( j = 0; j < SndMachine->control_max; j++ )
	    add_text(text_data,"   %s\n",sound_chip_list[ SndMachine->init[j] ]);
         add_text(text_data,"\n");
      }

      /*

      board number [optional]

      */

      if(game_info->board)

         add_text(text_data,"Board:\n   %s\n\n", game_info->board);

      /*

      video %d x %d

      */

      vid_info = game_info->video;

      add_text(text_data,"Video:\n   %d x %d (8bpp)", vid_info->screen_x, vid_info->screen_y);

      if(vid_info->flags & VIDEO_ROTATABLE){

      switch(VIDEO_ROTATE( vid_info->flags )){
         case VIDEO_ROTATE_NORMAL:
            add_text(text_data," horizontal");
         break;
         case VIDEO_ROTATE_90:
            add_text(text_data," vertical");
         break;
         case VIDEO_ROTATE_180:
            add_text(text_data," horizontal");
         break;
         case VIDEO_ROTATE_270:
            add_text(text_data," vertical");
         break;
      }

      }

      add_text(text_data,"\n\n");

      /*

      palette %s

      */

      if(current_colour_mapper)

         add_text(text_data,"Palette:\n   %s\n\n", current_colour_mapper->name);

      /*

      tiles %s

      */

      if(tile_list_count){

         add_text(text_data,"Tiles:\n");

         for( i = 0; i < tile_list_count; i ++){

            add_text(text_data,"   %-14s", tile_type[tile_list[i].type]);
            add_text(text_data," %6d tiles\n", tile_list[i].count);

         }

         add_text(text_data,"\n");

      }

      /*

      archive %s

      */

      add_text(text_data,"Archive:\n");

      dir_list = game_info->dir_list;

      while(dir_list->maindir){

         if((!IS_ROMOF(dir_list->maindir)) && (!IS_CLONEOF(dir_list->maindir)))

            add_text(text_data,"   %s\n", dir_list->maindir);

         dir_list++;

      }

      add_text(text_data,"\n");

      /*

      romof %s [optional]

      */

      romof = 0;

      find_romof(game_info->dir_list, &romof);

      if (romof) { // Shows only the 1st romof...
	add_text(text_data,"Romof:\n");
	add_text(text_data,"   %s\n", romof_list[0] );
	add_text(text_data,"\n");
      }

      /*

      cloneof %s [optional]

      */

      cloneof = 0;

      dir_list = game_info->dir_list;

      while(dir_list->maindir){

         if(IS_CLONEOF(dir_list->maindir)){

               if(!cloneof)

                  add_text(text_data,"Cloneof:\n");

               add_text(text_data,"   %s\n", (dir_list->maindir) + 1 );

               cloneof ++;

         }

         dir_list ++;

      }

      if(cloneof)

         add_text(text_data,"\n");

      add_text(text_data,"Roms:\n");

      rom_list = game_info->rom_list;

      while(rom_list->name){
	if (strcmp(rom_list->name,REGION_EMPTY)) {
	  add_text(text_data,"   %-12s %7d bytes\n", rom_list->name, rom_list->size);
	}
	rom_list++;
      }

      if (load_region[REGION_CPU1]) { // Check the parent if we have defined regions
	int region;
	for (region=1; region < REGION_MAX; region++) {
	  if (load_region[region]) {
	    int found = 0;
	    rom_list = game_info->rom_list;

	    while(rom_list->name && !found){
	      if (rom_list->region == region) {
		found = 1;
	      }
	      rom_list++;
	    }

	    for (i=0; i<romof; i++) {
	      if (!found) {
		GAME_MAIN *game_romof = find_game(romof_list[i]);
		rom_list = game_romof->rom_list;
		while(rom_list->name){
		  if (rom_list->region == region) {
		    add_text(text_data,"   %-12s %7d bytes\n", rom_list->name, rom_list->size);
		    found = 1;
		  }
		  rom_list++;
		}
	      }
	    }
	  }
	}
      }

      add_text(text_data,"\n");
      add_text(text_data,"Driver: %s\n",game_info->source_file);

      about_game[3].d1 = 0;
      about_game[3].d2 = 0;
      about_game[3].dp = text_data;

      company_logo = (DATAFILE *) RaineData[company].dat;

      switch(game_info->company_id){
	 case COMPANY_ID_CAPCOM:
	    logo     = company_logo[company_capcom].dat;
	    logo_pal = company_logo[company_capcom_pal].dat;
         break;
         case COMPANY_ID_EX_SYSTEM:
            logo     = company_logo[company_ex_system].dat;
            logo_pal = company_logo[company_ex_system_pal].dat;
         break;
         case COMPANY_ID_JALECO:
            logo     = company_logo[company_jaleco].dat;
            logo_pal = company_logo[company_jaleco_pal].dat;
         break;
         case COMPANY_ID_NICHIBUTSU:
            logo     = company_logo[company_nichibutsu].dat;
            logo_pal = company_logo[company_nichibutsu_pal].dat;
         break;
         case COMPANY_ID_NMK:
            logo     = company_logo[company_nmk].dat;
            logo_pal = company_logo[company_nmk_pal].dat;
         break;
         case COMPANY_ID_RAIZING:
            logo     = company_logo[company_raizing].dat;
            logo_pal = company_logo[company_raizing_pal].dat;
         break;
         case COMPANY_ID_SETA:
            logo     = company_logo[company_seta].dat;
            logo_pal = company_logo[company_seta_pal].dat;
         break;
         case COMPANY_ID_TAD:
            logo     = company_logo[company_tad].dat;
            logo_pal = company_logo[company_tad_pal].dat;
         break;
         case COMPANY_ID_TAITO:
            logo     = company_logo[company_taito].dat;
            logo_pal = company_logo[company_taito_pal].dat;
         break;
         case COMPANY_ID_TECHNOS:
            logo     = company_logo[company_technos].dat;
            logo_pal = company_logo[company_technos_pal].dat;
         break;
         case COMPANY_ID_TECMO:
            logo     = company_logo[company_tecmo].dat;
            logo_pal = company_logo[company_tecmo_pal].dat;
         break;
         case COMPANY_ID_TOAPLAN:
            logo     = company_logo[company_toaplan].dat;
            logo_pal = company_logo[company_toaplan_pal].dat;
         break;
         case COMPANY_ID_UPL:
            logo     = company_logo[company_upl].dat;
            logo_pal = company_logo[company_upl_pal].dat;
         break;
         case COMPANY_ID_VISCO:
            logo     = company_logo[company_visco].dat;
            logo_pal = company_logo[company_visco_pal].dat;
         break;
         default:
            logo     = NULL;
            logo_pal = NULL;
         break;
      }

      if(logo){
         logo_2 = make_mapped_bitmap(logo, (INT32*)&i, logo_pal, 16);

         about_game[1].proc = &d_bitmap_proc;
         about_game[1].dp   = logo_2;
         about_game[1].x    = about_game[0].x + ((WIDTH/2 * text_height(gui_main_font)) / 8) - (logo_2->w / 2);
         about_game[1].y    = about_game[0].y + (( 32 * text_height(gui_main_font)) / 8) - (logo_2->h / 2);
         about_game[1].w    = logo_2->w;
         about_game[1].h    = logo_2->h;
      }
      else{
         about_game[1].proc = &d_null_proc;
         about_game[1].dp   = NULL;
         about_game[1].x    = about_game[0].x;
         about_game[1].y    = about_game[0].y;
         about_game[1].w    = 0;
         about_game[1].h    = 0;
      }

      ret = raine_do_dialog(about_game,-1);

      if(logo_2)
         destroy_mapped_bitmap(logo_2, 16);

      free(text_data);
   }
   ret = D_REDRAW;
   }
   return ret;
}
