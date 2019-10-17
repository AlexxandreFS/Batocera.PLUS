/******************************************************************************/
/*									      */
/*	   RAINE (680x0 arcade emulation) v0.35 (c) 1998-2015 Raine Team      */
/*									      */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "conf-cpu.h"
#include "conf-sound.h"
#ifndef SDL
#include "rgui.h" // setup mode lists...
#include "alleg/gui/gui.h"                // Interface stuff
#include "alleg/gui/about.h"
#include "loadpng.h"
#else
#include "sdl/gui.h"
#endif

#ifdef RAINE_DOS
#include <conio.h>
#elif defined(RAINE_UNIX)
#include <unistd.h> // isatty
#elif defined(RAINE_WIN32)
#include <io.h> // getcwd, chdir...
#endif

#include "raine.h"              // General defines and stuff
#include "romdir.h"
#include "savegame.h"           // Save/Load game stuff
#include "sasound.h"            // Sound Sample stuff
#include "dsw.h"                // Dipswitch stuff
#include "ingame.h"             // screen handling routines
#include "arpro.h"              // Action Replay stuff
#include "control.h"            // Control/Input related stuff
#include "config.h"             // Command Line + Config file routines

#include "starhelp.h"           // M68000 Support Interface
#include "mz80help.h"           // MZ80 Support Interface
#ifdef HAVE_6502
#include "m6502hlp.h"           // M6502 Support Interface
#endif
#include "68020.h"              // M68020 Engine + Support Interface
#include "neocd/neocd.h"
#include "neocd/cdda.h"
#include "games.h"              // Game list
#include "files.h"
#include "profile.h" // rdtsc
#include "version.h"
#include "dejap.h" // default config files in raine.dat
#include "display.h" // setup_gfx_modes
#include "blit.h"
#include "cpuid.h"

struct RAINE_CFG raine_cfg;
UINT8 *ingame_font; 	// Raw data for ingame font
struct DIR_CFG dir_cfg;


#ifdef OLD_ALLEG
// Cutback Allegro
// ---------------
#ifdef RAINE_DOS
DECLARE_COLOR_DEPTH_LIST(
   COLOR_DEPTH_8
)
#endif
#endif

/**************************************************************/

#ifdef RAINE_UNIX
int x_display = 0;
#endif

// main():
// Start here, end here.

#ifdef SDL
// just in case we compile with allegro...
#undef GFX_XWINDOWS_FULLSCREEN
#undef GFX_FBCON
char raine_cpu_model[80]; // declared in gui/about.c, not available with sdl...
#endif

char language[3];

void init_lang() {
    if (!language[0]) {
	char *olang = getenv("LANGUAGE");
	if (!olang) olang = getenv("LANG");
	language[0] = 0;
	if (olang) {
	    strncpy(language,olang,2);
	    language[2] = 0;
	}
#ifdef RAINE_WIN32
	else
	    strcpy(language,get_win_lang());
#endif
	if (!language[0])
	    strcpy(language,"C");
    }

#ifndef RAINE_DOS
    static char buf[20];
    snprintf(buf,20,"LANGUAGE=%s",language);
#ifdef RAINE_WIN32
    /* I had SDL_putenv not working in native windows but maybe it was related
     * to an old dll. Anyway using putenv + an updated dll works so I'll leave
     * it like this for now ! */
    putenv(buf);
#else
    SDL_putenv(buf);
#endif
    setlocale(LC_ALL & ~LC_NUMERIC,"");
#endif
}

static void mystrcpy(char *dst,char *src) {
    // osx *CRASHES* if you pass src == dst here, even if src[0]=0 !!!
    // See http://postgresql.nabble.com/OSX-doesn-t-accept-identical-source-target-for-strcpy-anymore-td5776101.html
    if (src != dst)
	strcpy(dst,src);
}

int main(int argc,char *argv[])
{
   int i;
   unsigned int version_id;
#ifndef SDL
   int ta;
#endif
   char str[256],*s;
   const char *dirs[] = {
		 "config",
		 "savegame",
		 "savedata",
		 "roms",
		 "demos",
		 "artwork",
#ifdef HAS_CONSOLE
		 "debug",
#endif
		 NULL
		 };
   const char **dirp = dirs;
#ifdef GFX_FBCON
   FILE *f;
#endif

  /* This just helps some window managers to grab some info from the
   * .desktop file if it exists */
  putenv((char*)"SDL_VIDEO_X11_WMCLASS=raine");
#if 0
  /* Don't force directx anymore, creating too many problems especially in
   * fullscreen. There is a reason why windib is now the default windows video
   * driver in sdl... */
#ifdef RAINE_WIN32
  /* This one is because directx doesn't seem to be the default driver
   * in windows, and it's the only one with hardware acceleration... */
  putenv("SDL_VIDEODRIVER=directx");
#endif
#endif

   /*

   show emulator version on the command line

   */

   // Use ansi color codes in linux. Windows still does not support ansi codes natively !
   // windows is really a paradox !
#ifdef RAINE_UNIX
   if (isatty(fileno(stdout))) {
     /* Is there a way to do this in windoze ??? Probably not, windows is lame when it
	comes to redirections (and in many other areas too by the way) */
       printf(pretty_emu_name);
   } else {
     printf(" RAINE");
   }
#elif defined(RAINE_DOS)
    textcolor(7);  cprintf(" ");
    textcolor(12); cprintf("R");
    textcolor(14); cprintf("A");
    textcolor(10); cprintf("I");
    textcolor(9);  cprintf("N");
    textcolor(13); cprintf("E");
    textcolor(15);
#else
    // Anyway we should disable the console in windows, it's uggly and broken.
     printf(" RAINE");
#endif
    printf(" (680x0 Arcade Emulation) " VERSION " (c)1998-2015(!) " HANDLE);

   printf("\n\n");

#ifdef RAINE_DEBUG

#ifdef RAINE_DOS
   textcolor(5);
#elif defined(RAINE_UNIX)
   if (isatty(fileno(stdout)))
     printf("\E[35m"); // magenta
#endif

 printf("[PRIVATE BETA VERSION]");
 printf("\n\n");

#endif // ifdef RAINE_DEBUG

#ifdef RAINE_DOS
   printf("\E[0m"); // normal text
#elif defined(RAINE_UNIX)
   if (isatty(fileno(stdout)))
       printf("\E[0m"); // normal text
#endif

 // The cpu detection is not just to print the name of the cpu, it's also to
 // initialize raine_cpu_capabilities so that we can use mmx if available.
 get_cpu_name(raine_cpu_model);
 printf("CPU: %s\n",raine_cpu_model);

   /*

   get executable path

     If Unix, use ~/.raine as a base directory, screenshots, saves, personnal
     roms are stored in this directory.. If not Unix it's stored in the current
     directory.
   */

#ifdef RAINE_UNIX
   sprintf(dir_cfg.share_path, "/usr/share/games/raine/");
   sprintf(dir_cfg.exe_path, "%s/.raine/", getenv("HOME"));
#else
#if !defined(RAINE_WIN32) || defined(__MINGW32__)
   strcpy(dir_cfg.exe_path, argv[0]);
#else
   strcpy(dir_cfg.exe_path, __argv[0]);
#endif

   strcpy(get_filename(dir_cfg.exe_path),"");
   if (!dir_cfg.exe_path[0]) { // No path
	   getcwd(dir_cfg.exe_path,255);
	   chdir(dir_cfg.exe_path);
	   strcat(dir_cfg.exe_path,"/");
   }
   backslash(dir_cfg.exe_path);

   strcpy(dir_cfg.share_path,dir_cfg.exe_path); // avoid useless ifdefs...
#endif
#ifdef DARWIN
   if ((s = strstr(argv[0],"MacOS/"))) {
       // If lauched from a bundle the share path becomes the Ressources dir
       strncpy(dir_cfg.share_path,argv[0],256);
       strcpy(dir_cfg.share_path+(s - argv[0]),"Resources/");
       strncpy(dir_cfg.m68kdis,argv[0],256);
       strncpy(dir_cfg.dz80,argv[0],256);
       strcpy(dir_cfg.m68kdis+(s - argv[0]+6),"m68kdis");
       strcpy(dir_cfg.dz80+(s - argv[0]+6),"dz80");
       if (!exists(dir_cfg.m68kdis))
	   strcpy(dir_cfg.m68kdis,"m68kdis");
       if (!exists(dir_cfg.dz80))
	   strcpy(dir_cfg.dz80,"dz80");
   }
#endif

   // set config filename

#ifdef RAINE_DOS
   strcpy(dir_cfg.config_file, "raine.cfg");
#else
#ifdef RAINE_WIN32
#ifdef SDL
   strcpy(dir_cfg.config_file, "raine32_sdl.cfg");
#else
   strcpy(dir_cfg.config_file, "raine32.cfg");
#endif
#else
#ifdef SDL
   strcpy(dir_cfg.config_file, "rainex_sdl.cfg");
#else
   strcpy(dir_cfg.config_file, "rainex.cfg");
#endif
#endif
#endif

   // i18n : path for catalog file
#ifndef RAINE_DOS
   bindtextdomain("raine",get_shared("locale"));
   textdomain("raine");
#endif

   // set default screen settings
   setup_gfx_modes();

   // it would be usefull to avoid allegro_init to be able to run -gamelist
   // without starting an X connection, but there is a bug until allegro 4.0.2
   // which prevents from loading raine.dat if it is linked to the exe and
   // we didn't call allegro_init.

   // The raine.dat file must be loaded AFTER initialising the video mode to be able
   // to load true color bitmaps
#ifndef SDL
   allegro_init();
   RaineData = load_datafile("#");

   if(!RaineData){
      RaineData = load_datafile(get_shared("raine.dat"));
      if(!RaineData){
	RaineData = load_datafile("raine.dat"); // try current directory
	if(!RaineData){
	  allegro_message("Unable to find raine.dat (must be in raine dir, or attached to raine.exe)\n");
	  exit(1);
	}
      }
   }
#endif

   raine_cfg.no_gui = 0;
   raine_cfg.hide = 0;
   raine_cfg.req_load_game = 0;
   raine_cfg.req_game_index = 0;

   mkdir_rwx(dir_cfg.exe_path);
   while (*dirp) {
     mkdir_rwx(*dirp);
     dirp++;
   }

   sprintf(dir_cfg.screen_dir,"%sscreens" SLASH, dir_cfg.exe_path);
   sprintf(dir_cfg.emudx_dir,"%semudx" SLASH, dir_cfg.share_path);
   sprintf(dir_cfg.artwork_dir,"%sartwork" SLASH, dir_cfg.share_path);
   init_rom_dir();
   snprintf(str,256,"%sroms" SLASH, dir_cfg.exe_path);
   add_rom_dir(str);
#ifdef RAINE_UNIX
   snprintf(str,256,"%sroms" SLASH, dir_cfg.share_path);
   add_rom_dir(str);
#endif

   load_main_config();

   // RAINE GUI (Allegro...)
   strncpy(language,	 raine_get_config_string( "General", "language", ""), 2);
   language[2] = 0;
   init_lang();

   read_gui_config();

#ifndef SDL
   _png_compression_level = raine_get_config_int( "Display",      "png_compression",         6);
#endif

   getcwd(pwd,FILENAME_MAX);
#ifdef RAINE_DEBUG
   debug_mode			= raine_get_config_int( "General",      "debug_mode",           1);
   open_debug();
   print_debug("exe_path %s share_path %s pwd %s argv0 %s\n",dir_cfg.exe_path,
	   dir_cfg.share_path,pwd,argv[0]);
#endif

   raine_cfg.wibble		= raine_get_config_int( "General",      "wibble",               0);

   raine_cfg.extra_games = 0;

   raine_cfg.run_count		= raine_get_config_int( "General",      "run_count",                            0);
   raine_cfg.version_no 	= raine_get_config_int( "General",      "version",                              0);

   s = strchr(VERSION,'.');
   if (s) {
     int major = atoi(VERSION);
     int minor = atoi(s+1);
     int patchlevel = 0;
     s = strchr(s+1,'.');
     if (s)
       patchlevel = atoi(s+1);
     version_id = patchlevel | (minor << 8) | (major << 16);
   } else {
     fprintf(stderr,"Bad version number. Should be major.minor[.patchlevel]\n");
     exit(1);
   }
   if (raine_cfg.version_no != version_id) {
     raine_cfg.version_no = version_id;
     raine_cfg.run_count = 0;
   }
   display_cfg.limit_speed	= raine_get_config_int( "General",      "LimitSpeed",                           1);
   display_cfg.frame_skip	= raine_get_config_int( "General",      "frame_skip",                           0);
   raine_cfg.show_fps_mode	= raine_get_config_int( "General",      "ShowFPS",                              0);
   use_rdtsc			= raine_get_config_int( "General",      "UseRdtsc",                             1);
   if (!(raine_cpu_capabilities & CPU_TSC) && use_rdtsc) {
     use_rdtsc = 0;
     fprintf(stderr,"Can't use RDTSC, the cpu does not support it !\n");
   }

   use_leds			= raine_get_config_int( "General",      "UseLEDS",                              1);

   raine_cfg.save_game_screen_settings	  = raine_get_config_int(	"General",      "save_game_screen_settings",            0);

   raine_cfg.auto_save	= raine_get_config_int( "General", "auto_save", 0);

   if((use_rdtsc==0)&&(raine_cfg.show_fps_mode>2)) raine_cfg.show_fps_mode=0;

   // DISPLAY
   display_read_config();

   // DIRECTORIES

#ifndef RAINE_DOS
   dir_cfg.long_file_names = 1;
#else
   dir_cfg.long_file_names	= raine_get_config_int( "Directories",  "long_file_names",      1);
#endif

   mystrcpy(dir_cfg.screen_dir,	 raine_get_config_string( "Directories", "screenshots",   dir_cfg.screen_dir));
   mystrcpy(dir_cfg.emudx_dir,	 raine_get_config_string( "Directories", "emudx",   dir_cfg.emudx_dir));
   if (!*dir_cfg.m68kdis)
       strcpy(dir_cfg.m68kdis, raine_get_config_string( "Directories", "m68kdis", "m68kdis"));
   if (!*dir_cfg.dz80)
       strcpy(dir_cfg.dz80, raine_get_config_string( "Directories", "dz80", "dz80"));
   mystrcpy(dir_cfg.artwork_dir,	 raine_get_config_string( "Directories", "artwork",   dir_cfg.artwork_dir));
   i=0;
   do {
     alloc_romdir(i);
     sprintf(str,"rom_dir_%d",i);
     char *s = raine_get_config_string( "Directories", str, dir_cfg.rom_dir[i]);
     if (s == dir_cfg.rom_dir[i])
       break;
     dir_cfg.rom_dir[i++] = strdup(s);
   } while(1);
#ifndef SDL
   strcpy(dir_cfg.language_file, raine_get_config_string( "Directories", "language_file", "english.cfg"));
#endif
#if HAS_NEO
   strcpy(neocd_dir,    raine_get_config_string("neocd", "neocd_dir", dir_cfg.exe_path));
   strcpy(neocd_bios_file, raine_get_config_string("neocd", "neocd_bios", ""));
   music_volume = raine_get_config_int("neocd","music_volume",DEFAULT_MUSIC_VOLUME);
   sfx_volume = raine_get_config_int("neocd","sfx_volume",DEFAULT_SFX_VOLUME);
#ifndef RAINE_DOS
   neocd_cdda_format = raine_get_config_int("neocd","cdda_format",AUDIO_S16LSB);
#endif
   auto_stop_cdda = raine_get_config_int("neocd","auto_stop_cdda",1);
   mute_sfx = raine_get_config_int("neocd","mute_sfx",0);
   mute_music = raine_get_config_int("neocd","mute_music",0);
   allowed_speed_hacks = raine_get_config_int("neocd","allowed_speed_hacks",1);
#endif

   for(i = 0; dir_cfg.rom_dir[i]; i ++){
     put_backslash(dir_cfg.rom_dir[i]);
   }


   /*

   make sure any "output" directories are created

   */

   mkdir_rwx(dir_cfg.screen_dir);

   sound_load_cfg();

   if (audio_sample_rate < 15000)
      audio_sample_rate = 11025;
   else if (audio_sample_rate < 30000)
	 audio_sample_rate = 22050;
      else
	 audio_sample_rate = 44100;

   // KEYBOARD DEFAULT

   load_default_keys("default_game_key_config");

   // JOYSTICK DEFAULT

#ifndef SDL
#ifdef RAINE_DOS
   JoystickType 	= raine_get_config_id(	"Control",      "JoystickType",         JOY_TYPE_NONE);
#else
   JoystickType = JOY_TYPE_AUTODETECT;
#endif
   load_joystick_data(str);
   for (ta=0; ta<4; ta++){
     sprintf(str,"DirectionStick%d",ta);
     direction_stick[ta] = raine_get_config_id(	"Control",      str,         0);
   }

   load_default_joys("default_game_joy_config");
#endif

   // KEYBOARD EMULATOR

   load_emulator_keys("emulator_key_config");

   // JOYSTICK EMULATOR

   load_emulator_joys("emulator_joy_config");

   raine_pop_config_state();

   // JOYSTICK ALLEGRO

   snprintf(str,256,"%sconfig" SLASH "%s",dir_cfg.exe_path, dir_cfg.config_file);

   init_game_list();

   parse_command_line(argc,argv);
#ifdef SDL
   sdl_init();
#endif

#ifdef GFX_FBCON
   // With Frame buffer, I have to avoid the standard modex, or raine freezes!

   if (!x_display) {
     f = fopen("/dev/fb0","rb");
     if (f) {
       fclose(f);
       setup_fb_modes();

       if (display_cfg.screen_x < 640 || display_cfg.screen_y < 480) {
	 display_cfg.screen_x = 640;
	 display_cfg.screen_y = 480;
       }
       display_cfg.screen_type = GFX_FBCON;
     }
   }
#endif
#ifdef GFX_XWINDOWS_FULLSCREEN
   setup_xfs_modes();
#endif
#ifndef RAINE_DEBUG
   /*----[New Users Message (no config file)]--------------*/

   if(!(raine_cfg.run_count)){
      allegro_message(
	"This seems to be the first time you have run " EMUNAME " " VERSION ".\n"
	"Please read the docs before running... also read raine.cfg.\n"
	"If you have any problems, please visit\n"
	"http://rainemu.swishparty.co.uk/\n"
	"\n"
#ifndef SDL
	"ISSUES:\n"
	"\n"
#ifdef RAINE_WIN32
	"If you have bad colors in 8bpp fullscreen modes, try setting\n"
	"fast_set_pal = 2 in your raine32.cfg...\n"
        "If your colours flicker in 8bpp modes then you should switch to\n"
	"16bpp, and wait for the SDL version to be ready.\n"
#endif
#ifdef RAINE_UNIX
	"liballegro4.2 is broken, it produces the message\n"
	"'Xlib: unexpected async reply' randomly\n"
	"when you start raine, and then you are obliged to kill it.\n"
	"This bug is related to allegro threads and seems to happen less often\n"
	"when you compile your own allegro version instead of using the\n"
	"debian one...\n"
	"\n"
#endif
#endif
      );
#ifdef RAINE_DOS
	// Win32 waits for a click with allegro_message...
	printf( "[Press a key to continue] [Press ESC to exit]\n"
		"\n");
	CLI_WaitKeyPress();
#endif
   }
   raine_cfg.run_count++;

   /*----[New Release Message (config version is old)]--------*/
/* Removed by katharsis as Raine ain't dead =)
   if(raine_cfg.version_no != 28){
      raine_cfg.version_no = 28;
      printf(
	"(This will only appear once only)\n"
	"\n"
	"Thanks for trying " EMUNAME " " VERSION ".\n"
	"\n"
	"ISSUES:\n"
	"\n"
	"þ This is an alpha release - I expect there are bugs and the\n"
	"  docs are a bit out of date. This is due to lack of time, a\n"
	"  problem that will effect raine for these last few days of\n"
	"  it's life.\n"
	"\n"
	"[Press a key to continue] [Press ESC to exit]\n"
	"\n"
      );
      CLI_WaitKeyPress();
   }
*/
#endif

#ifndef SDL
   build_mode_list(); // After the REAL allegro init...
   RaineSoundCardTotal=8;
#endif

   /*------------------------------------------*/

#if HAVE_68000
   s68000init();
#endif

   StartGUI();
   if (recording)
       end_recording();

   snprintf(str,256,"%sconfig" SLASH "%s", dir_cfg.exe_path, dir_cfg.config_file);
#ifndef SDL
#ifdef RAINE_UNIX
   save_file(str, RaineData[ConfigUnix].dat, RaineData[ConfigUnix].size);
#else
#ifdef RAINE_WIN32
   save_file(str, RaineData[ConfigWin].dat, RaineData[ConfigWin].size);
#else
   save_file(str, RaineData[ConfigDos].dat, RaineData[ConfigDos].size);
#endif
#endif
#endif
   print_debug("calling save_main_config\n");
   save_main_config();
   print_debug("save_main_config done\n");

   raine_push_config_state();

   snprintf(str,256,"%sconfig" SLASH "%s", dir_cfg.exe_path, dir_cfg.config_file);
   raine_set_config_file(str);

#ifdef RAINE_DEBUG
   if(debug_mode) raine_set_config_int("General","debug_mode",debug_mode);
   close_debug();
#endif

   if(raine_cfg.wibble)
   raine_set_config_int(	"General",      "wibble",               raine_cfg.wibble);

   raine_set_config_int(	"General",      "run_count",            raine_cfg.run_count);
   raine_set_config_int(	"General",      "version",              raine_cfg.version_no);
   raine_set_config_int(	"General",      "LimitSpeed",           display_cfg.limit_speed);
   raine_set_config_int(	"General",      "frame_skip",           display_cfg.frame_skip);
   raine_set_config_int(	"General",      "ShowFPS",              raine_cfg.show_fps_mode);
   raine_set_config_int(	"General",      "UseRdtsc",             use_rdtsc);
   raine_set_config_int(	"General",      "UseLEDS",              use_leds);

   raine_set_config_int(	"General",      "save_game_screen_settings", raine_cfg.save_game_screen_settings);
   raine_set_config_int(   "General",      "auto_save",                 raine_cfg.auto_save);

   // DISPLAY

   display_write_config();

   // DIRECTORIES

#ifdef RAINE_DOS
   raine_set_config_int(	"Directories",  "long_file_names",      dir_cfg.long_file_names);
#endif
   raine_set_config_string(	"Directories",  "ScreenShots",          dir_cfg.screen_dir);
   raine_set_config_string(     "Directories", "m68kdis", dir_cfg.m68kdis);
   raine_set_config_string(     "Directories", "dz80", dir_cfg.dz80);
#if HAS_NEO
   raine_set_config_string("neocd", "neocd_dir", neocd_dir);
   raine_set_config_string("neocd", "neocd_bios", neocd_bios_file);
   raine_set_config_int("neocd","music_volume",music_volume);
   raine_set_config_int("neocd","sfx_volume",sfx_volume);
   raine_set_config_int("neocd","cdda_format",neocd_cdda_format);
   raine_set_config_int("neocd","auto_stop_cdda",auto_stop_cdda);
   raine_set_config_int("neocd","mute_sfx",mute_sfx);
   raine_set_config_int("neocd","mute_music",mute_music);
   raine_set_config_int("neocd","allowed_speed_hacks",allowed_speed_hacks);
#endif
   raine_set_config_string(	"Directories",  "emudx",          dir_cfg.emudx_dir);
   raine_set_config_string(	"Directories",  "artwork",          dir_cfg.artwork_dir);
   for(i = 0; dir_cfg.rom_dir[i]; i ++){
     sprintf(str,"rom_dir_%d",i);
     raine_set_config_string("Directories",str,dir_cfg.rom_dir[i]);
     free(dir_cfg.rom_dir[i]);
   }
   // remove the directories which have been deleted in the gui...
   do {
     sprintf(str,"rom_dir_%d",i++);
     s = raine_get_config_string( "Directories", str, NULL);
     if (s)
       raine_set_config_string("Directories",str,"");
   } while (s);
   free(dir_cfg.rom_dir);
#ifndef SDL
   raine_set_config_string(	"Directories",  "language_file",        dir_cfg.language_file);
#endif

   // CONTROL

#ifndef SDL
   raine_set_config_id( 	"Control",      "JoystickType",         JoystickType);
   for (ta=0; ta<num_joysticks; ta++){
     sprintf(str,"DirectionStick%d",ta);
     raine_set_config_id(	"Control",      str,                    direction_stick[ta]);
   }
#endif

   // KEYBOARD DEFAULT

   save_default_keys("default_game_key_config");

#ifndef SDL
   // JOYSTICK DEFAULT

   save_default_joys("default_game_joy_config");
#endif

   // KEYBOARD EMULATOR

   save_emulator_keys("emulator_key_config");

   // JOYSTICK EMULATOR

   save_emulator_joys("emulator_joy_config");

   snprintf(str,256,"%sconfig" SLASH "%s",dir_cfg.exe_path, dir_cfg.config_file);

   // RAINE GUI

    write_gui_config();

#ifndef SDL
   raine_set_config_int(	"Display",      "png_compression",         _png_compression_level);
#endif

   sound_save_cfg();

   // JOYSTICK ALLEGRO

#ifndef SDL
   save_joystick_data(str);
#endif
   raine_set_config_string("General","language",language);

   raine_pop_config_state();
   raine_config_cleanup();
#ifndef SDL
   unload_datafile(RaineData);
#endif

   return 0;
}

#ifndef SDL
END_OF_MAIN();
#endif

