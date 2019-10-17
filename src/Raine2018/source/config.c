/******************************************************************************/
/*                                                                            */
/*                            RAINE COMMAND LINE                              */
/*                                                                            */
/******************************************************************************/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>
#include <dirent.h>
#ifdef DARWIN
#include <unistd.h>
#endif

#include "raine.h"		// General defines and stuff
#include "gui.h"		// Interface stuff

#include "savegame.h"		// Save/Load game stuff
#include "sasound.h"		// Sound Sample stuff
#include "dsw.h"		// Dipswitch stuff
#include "ingame.h"		// screen handling routines
#include "arpro.h"		// Action Replay stuff
#include "control.h"		// Control/Input related stuff
#include "games.h"		// Games List
#include "loadroms.h"		//
#include "config.h"		// config and command parsing routines
#include "version.h"
#include "display.h" // load/save_screen_settings
#include "files.h"
#ifdef HAS_CONSOLE
#include "sdl/console/scripts.h"
#endif
#include "sound/assoc.h"
#ifdef SDL
#include "display_sdl.h"
#endif

static int ArgCount;		// Number of arguments in the command line
static int ArgPosition;		// Current position in the argument list
static char *ArgList[256];	// Pointers to each argument string

static int verbose;		// show extra information for some options

/*

process the -help/-?/--help/-h option

*/

void CLI_region() {
    if ((ArgPosition+1) < ArgCount) {
	ArgPosition++;
	override_region = atoi(ArgList[ArgPosition]);
    } else {
	printf("-region requires a parameter\n");
	exit(1);
    }
}

static void CLI_Help(void)
{
   allegro_message(
	"USE: Raine <commands> <options> [gamename]\n"
	"\n"
	"Commands:\n"
	"\n"
	"-game/-g [gamename]            : Select a game to load (see game list)\n"
	"-gamelist/-gl                  : Quick list of all games\n"
	"-gameinfo/-listinfo|-li <gamename> : List info for a game, or all games\n"
	"-romcheck/-rc <gamename>       : Check roms are valid for a game, or all games\n"
	"-romcheck-full/-rcf <gamename> : like romcheck, but load all the games, very slow now\n"
	"-help/-h/-?/--help             : Show command line options and list games\n"
	"-joystick/-j [type]            : Select joystick type (see list in raine.cfg)\n"
	"-limitspeed/-l                 : Limit emulation speed to 60fps\n"
	"-nogui/-n                      : Disable GUI (useful for frontends)\n"
#ifdef RAINE_DOS
	"-leds                          : Enable keyboard LED usage\n"
	"-noleds                        : Disable keyboard LED usage\n"
#endif
	"-cont                          : Enable continuous playing\n"
	"-nocont                        : Disable continuous playing\n"
	"-autoload                      : Enable auto savegame loading\n"
	"-noautoload                    : Disable auto savegame loading\n"
	"-screenx/-sx [width]           : Select screen width\n"
	"-screeny/-sy [height]          : Select screen height\n"
	"-geometry [width][xheight][+posx][+posy] : window placement\n"
#ifndef SDL
	"-screenmode/sm [type]          : Select screen type (allegro)\n"
#endif
	"-fullscreen/fs [0/1]           : Set fullscreen mode on/off\n"
	"-bpp/-depth [number]           : Select screen colour depth\n"
	"-rotate/-r [angle]             : Rotate screen 0,90,180 or 270 degrees\n"
	"-ror                           : Rotate screen 90 degrees\n"
	"-rol                           : Rotate screen 270 degrees\n"
	"-norotate/-nor                 : Ignore default rotation in game drivers\n"
	"-flip/-f [0-3]                 : Flip screen on none, x, y or x+y axis\n"
	"-flipx/-fx                     : Flip screen on x axis\n"
	"-flipy/-fy                     : Flip screen on y axis\n"
	"-noflip/-nof                   : Ignore default flipping in game drivers\n"
#ifndef SDL
	"-hide                          : Hide the gui (play at work)\n"
#endif
	"-listdsw <gamename>            : List dipswitches for a game, or all games\n"
	"-region n			: set region to number n. Pass -1 for values\n"
        "-source_file/-lsf <gamename>   : list source file\n"
	"\n"
	"Options:\n"
	"\n"
	"-verbose                       : Show extra information for romcheck mainly\n"
	"\n"
#ifdef SDL
	"SDL video options :\n"
	"\n"
	"-video/-vm n                   : Video mode : 0 = opengl, 1 = yuv overlays\n"
	"				  2 = normal blits\n"
	"OpenGL options :\n"
	"-render [0|1]                  : Renderer : 0 = DrawPixels, 1 = Texture\n"
	"-dbuf [0|1]                    : Double buffer : 0 = off, 1 = on\n"
	"-shader file                   : use file as shader\n"
	"-filter [0|1]                   : opengl filtering, 0 = GL_NEAREST, 1 = GL_LINEAR\n"
#endif
	"\n"
	"Other options are available only from the GUI/config file for now.\n"
	"\n"

	"Version: " VERSION "\n"
	"Games:   %d\n"
	"\n", game_count
   );

   exit(1);
}

/*

process the -limitspeed/-l option

*/

static void CLI_LimitSpeed(void)
{
   display_cfg.limit_speed = 1;
}

/*

process the -nogui/-n option

*/

static void CLI_NoGUI(void)
{
   raine_cfg.no_gui = 1;
}

/*

process the -game/-g option

*/

static void CLI_game_load_alt(void)
{
   int i,found = 0;

   for(i=0; i<game_count; i++){

      if((stricmp(ArgList[ArgPosition], game_list[i]->main_name))){
	const DIR_INFO *dir = game_list[i]->dir_list;
	while (dir->maindir && stricmp(ArgList[ArgPosition],dir->maindir))
	  dir++;
	if (dir->maindir)
	  found = 1;
      } else
        found = 1;

      if (found) {
          raine_cfg.req_load_game = 1;
          raine_cfg.req_game_index = i;

          return;
      }

   }

   allegro_message(
      "Unsupported game\n"
      "Type 'Raine -gamelist' for a list of available games.\n"
#ifdef RAINE_WIN32
      "Well, actually don't do that : -gamelist is broken in win32... !\n"
#endif
      "\n"
   );
   exit(1);

}

static void CLI_game_load(void)
{
   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;
      CLI_game_load_alt();

   }
   else{

   allegro_message(
      "Unsupported game\n"
      "Type 'Raine -gamelist' for a list of available games.\n"
      "\n"
   );
   exit(1);

   }

}
#if HAS_NEO
#include "neocd/neocd.h"
#endif
#include "blit.h"
#include "newspr.h"
#include "default.h"
#include "emumain.h"

#if HAS_NEO
int actual_load_neo_game(void)
{
  // Here neocd_dir and neocd_path are already initialized...
  DIR *dir = opendir(neocd_dir);
  if (dir) { // this dir exists !
    closedir(dir);
    if (current_game)
      ClearDefault();
    current_game = (GAME_MAIN *)&game_neocd;
    if (!screen) {
#ifndef RAINE_DOS
	sdl_init();
#endif
      init_display();
      setup_font(); // Usefull even without gui for the messages on screen
    }
    SetupScreenBitmap();

    print_debug("Init Video Core...\n");
    init_video_core();

    LoadDefault();
    current_game->load_game();
    if (!(load_error & LOAD_FATAL_ERROR)) {
      init_inputs();
      init_dsw();
      init_romsw();
      init_sound();
      reset_game_hardware();
    }
    return 1;
  }
  return 0;
}

int load_neo_from_name(char *res) {
  if (res[strlen(res)-1] == SLASH[0]) { // don't load anything with only a path
    return 0;
  }
  strcpy(neocd_path,res);
  strcpy(neocd_dir,res);
  char *s = strrchr(neocd_dir,SLASH[0]);
  if (!s) {
      getcwd(neocd_dir,FILENAME_MAX);
      sprintf(neocd_path,"%s%s%s",neocd_dir,SLASH,res);
  } else
      *s = 0; // neocd_dir without ending slash
  print_debug("load_neo_from_name: file %s neocd_dir %s\n",neocd_path,neocd_dir);
  return actual_load_neo_game();
}
#endif
// CLI_DisableLeds():
// Disable LED usage

static void CLI_DisableLeds(void)
{
   use_leds = 0;
}

// CLI_EnableLeds():
// Disable LED usage

static void CLI_EnableLeds(void)
{
   use_leds = 1;
}

// CLI_screen_x():
// Process the -screenx/-sx option

static void CLI_screen_x(void)
{
   ArgPosition++;
   sscanf(ArgList[ArgPosition], "%d", &display_cfg.screen_x);
}

// autosave

static void CLI_EnableCont(void)
{
   raine_cfg.auto_save |=  (FLAG_AUTO_SAVE | FLAG_AUTO_LOAD);
}

static void CLI_DisableCont(void)
{
   raine_cfg.auto_save &= ~(FLAG_AUTO_SAVE | FLAG_AUTO_LOAD);
}

// autoload

static void CLI_EnableAutoLoad(void)
{
   raine_cfg.auto_save |=  (FLAG_AUTO_LOAD);
}

static void CLI_DisableAutoLoad(void)
{
   raine_cfg.auto_save &= ~(FLAG_AUTO_LOAD);
}

// CLI_screen_y():
// Process the -screeny/-sy option

static void CLI_screen_y(void)
{
   ArgPosition++;
   sscanf(ArgList[ArgPosition], "%d", &display_cfg.screen_y);
}

static void CLI_geometry(void) {
    int nb = 0, size = 0, pos = -1,x = -1,y = -1;
    char *s = ArgList[++ArgPosition];

    while (*s) {
	if (*s >= '0' && *s <= '9') {
	    nb = 10*nb+(*s-'0');
	} else if (*s == 'x') {
	    size++;
	    if (size == 1)
		display_cfg.screen_x = nb;
	    else
		printf("geometry: bad syntax : %s\n",ArgList[ArgPosition-1]);
	    nb = 0;
	} else if (*s == '+') {
	    if (size == 1 && pos < 0)
		display_cfg.screen_y = nb;
	    pos++;
	    if (pos == 1)
		x = nb;
	    nb = 0;
	}
	s++;
    }
    if (s[-1] >= '0' && s[-1] <= '9') {
	if (pos < 0) {
	    if (size == 0)
		display_cfg.screen_x = nb;
	    else
		display_cfg.screen_y = nb;
	} else if (pos == 0)
	    x = nb;
	else if (pos == 1)
	    y = nb;
    }
    if (x >= 0 || y >= 0) {
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	char buf[80];
	sprintf(buf,"%d,%d",x,y);
	raine_set_config_string("Display","position",buf);
#ifndef RAINE_DOS
	display_cfg.fullscreen = 0;
	display_cfg.noborder = 1;
#endif
	// I would have used setenv here, but windows doesn't know setenv... !!!
	static char buffer[100];
	snprintf(buffer,100,"SDL_VIDEO_WINDOW_POS=%s",buf);
	buffer[99] = 0;
	putenv(buffer);
    }
}

#ifndef SDL
// CLI_screen_mode():
// Process the -screenmode/-sm option

typedef struct CLI_VIDEO
{
   char *name;		// Mode name/string
   UINT32 id;		// ID_ Value for this mode
} CLI_VIDEO;

static CLI_VIDEO video_options[] =
{
   { "0",		GFX_AUTODETECT			},
   { "Autodetect",	GFX_AUTODETECT			},
#ifdef GFX_VGA
   { "VGA",		GFX_VGA				},
#endif
#ifdef GFX_MODEX
   { "MODX",		GFX_MODEX			},
   { "ModeX",		GFX_MODEX			},
   { "ARCM",		GFX_ARCMON			},
#ifndef RAINE_UNIX
   { "arcade_monitor",	GFX_ARCMON			},
#endif
#endif
#ifdef GFX_SVGA
	 { "Svgalib",		GFX_SVGALIB		},
#endif
#ifdef GFX_DRIVER_VESA1
   { "VBE1",		GFX_VESA1			},
   { "Vesa1",		GFX_VESA1			},
#endif
#ifdef GFX_DRIVER_VESA2B
   { "VB2B",		GFX_VESA2B			},
   { "Vesa2b",		GFX_VESA2B			},
#endif
#ifdef GFX_DRIVER_VESA2L
   { "VB2L",		GFX_VESA2L			},
   { "Vesa2l",		GFX_VESA2L			},
#endif
#ifdef GFX_DRIVER_VESA3
   { "VBE3",		GFX_VESA3			},
   { "Vesa3",		GFX_VESA3			},
#endif
#ifdef GFX_DRIVER_VBEAF
   { "VBAF",		GFX_VBEAF			},
   { "Vbeaf",		GFX_VBEAF			},
#endif
#ifdef GFX_DRIVER_XTENDED
   { "XTND",		GFX_XTENDED			},
   { "extended",	GFX_XTENDED			},
#endif
#ifdef GFX_DRIVER_DIRECTX
   { "DXAC",		GFX_DIRECTX_ACCEL		},
   { "dx_accel",	GFX_DIRECTX_ACCEL		},
   { "DXSA",		GFX_DIRECTX_SAFE		},
   { "dx_safe",		GFX_DIRECTX_SAFE		},
   { "DXSO",		GFX_DIRECTX_SOFT		},
   { "dx_soft",		GFX_DIRECTX_SOFT		},
#endif
   { NULL,		0        			}
};

static void CLI_screen_mode(void)
{
   int ta;

   ArgPosition++;

   ta = 0;
   while( video_options[ta].name ){

      if(!( stricmp( video_options[ta].name, ArgList[ArgPosition] ))){

         display_cfg.screen_type = video_options[ta].id;
         return;

      }

      ta++;

   }

   allegro_message(
      "Unsupported video mode\n"
      "See raine.cfg for a list of modes\n"
      "eg. raine -screenmode vbaf (for vbe/af)\n"
      "\n"
   );
   exit(1);

}
#else

/*

process the -fullscreen/-fs option

*/

static void CLI_fullscreen_mode(void)
{
  int i;

  if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') )
    i = atoi(ArgList[ArgPosition+1]);
  else
    i = 1; // default : fullscreen = 1

  display_cfg.fullscreen = i;
}
#endif


/*

process -rotate n

*/

static void CLI_screen_rotate(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;
      sscanf(ArgList[ArgPosition], "%d", &i);

   }
   else{

      i = 0;

   }

   switch(i){
      case 90:
      case 1:
         display_cfg.user_rotate = 1;
      break;
      case 180:
      case 2:
         display_cfg.user_rotate = 2;
      break;
      case 270:
      case 3:
         display_cfg.user_rotate = 3;
      break;
      default:
         display_cfg.user_rotate = 0;
      break;
   }
}

/*

process -ror

*/

static void CLI_screen_rotate_right(void)
{
   display_cfg.user_rotate = 1;
}

/*

process -rol

*/

static void CLI_screen_rotate_left(void)
{
   display_cfg.user_rotate = 3;
}

/*

process -norotate

*/

static void CLI_screen_no_rotate(void)
{
   display_cfg.no_rotate = 1;
}

/*

process -flip n

*/

static void CLI_screen_flip(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;
      sscanf(ArgList[ArgPosition], "%d", &i);

   }
   else{

      i = 0;

   }

   switch(i){
      case 1:
         display_cfg.user_flip = 1;
      break;
      case 2:
         display_cfg.user_flip = 2;
      break;
      case 3:
         display_cfg.user_flip = 3;
      break;
      default:
         display_cfg.user_flip = 0;
      break;
   }
}

/*

process -flipx

*/

static void CLI_screen_flip_x(void)
{
   display_cfg.user_flip |= 1;
}

/*

process -flipy

*/

static void CLI_screen_flip_y(void)
{
   display_cfg.user_flip |= 2;
}

/*

process -noflip

*/

static void CLI_screen_no_flip(void)
{
   display_cfg.no_flip = 1;
}

/*

process -bpp

*/

int forced_bpp;

static void CLI_screen_bpp(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;
      sscanf(ArgList[ArgPosition], "%d", &i);

   }
   else{

      i = 0;

   }

   switch(i){
      case 8:
      case 15:
      case 16:
      case 24:
      case 32:
         display_cfg.bpp = i;
      break;
      default:
         display_cfg.bpp = 8;
      break;
   }
   forced_bpp = display_cfg.bpp;
}

#ifndef SDL
/*

process -hide

*/

static void CLI_hide(void)
{
   raine_cfg.hide = 1;
}
#endif

#ifdef RAINE_DOS
// CLI_Joystick():
// Process the -joystick/-j option

typedef struct CLI_JOY
{
   char *name;		// Mode name/string
   UINT32 id;		// ID_ Value for this mode
} CLI_JOY;

static CLI_JOY joy_options[] =
{
   { "-1",		JOY_TYPE_AUTODETECT	},
   { "Autodetect",	JOY_TYPE_AUTODETECT	},
   { "0",		JOY_TYPE_NONE		},
   { "None",		JOY_TYPE_NONE		},
#ifdef JOYSTICK_DRIVER_STANDARD
   { "STD",		JOY_TYPE_STANDARD	},
   { "standard",	JOY_TYPE_STANDARD	},
   { "4BUT",		JOY_TYPE_4BUTTON	},
   { "4buttons",	JOY_TYPE_4BUTTON	},
   { "6BUT",		JOY_TYPE_6BUTTON	},
   { "6buttons",	JOY_TYPE_6BUTTON	},
   { "8BUT",		JOY_TYPE_8BUTTON	},
   { "8buttons",	JOY_TYPE_8BUTTON	},
   { "2PAD",		JOY_TYPE_2PADS		},
   { "2pads",		JOY_TYPE_2PADS		},
   { "FPRO",		JOY_TYPE_FSPRO		},
   { "flightstickpro",	JOY_TYPE_FSPRO		},
   { "WING",		JOY_TYPE_WINGEX		},
   { "wingman",		JOY_TYPE_WINGEX		},
   { "wingmanextreme",	JOY_TYPE_WINGEX		},
#endif
#ifdef JOYSTICK_DRIVER_WINGWARRIOR
   { "WWAR",		JOY_TYPE_WINGWARRIOR	},
   { "wingwarrior",	JOY_TYPE_WINGWARRIOR	},
#endif
#ifdef JOYSTICK_DRIVER_SIDEWINDER
   { "SW",		JOY_TYPE_SIDEWINDER	},
   { "sidewinder",	JOY_TYPE_SIDEWINDER	},
#endif
#ifdef JOY_TYPE_SIDEWINDER_AG
   { "SWAG",		JOY_TYPE_SIDEWINDER_AG	},
   { "sidewinderag",	JOY_TYPE_SIDEWINDER_AG	},
#endif
#ifdef JOYSTICK_DRIVER_GAMEPAD_PRO
   { "GPRO",		JOY_TYPE_GAMEPAD_PRO	},
   { "gamepadpro",	JOY_TYPE_GAMEPAD_PRO	},
#endif
#ifdef JOYSTICK_DRIVER_GRIP
   { "GRIP",		JOY_TYPE_GRIP		},
   { "grip",		JOY_TYPE_GRIP		},
   { "GRI4",		JOY_TYPE_GRIP4		},
   { "grip4",		JOY_TYPE_GRIP4		},
#endif
#ifdef JOYSTICK_DRIVER_SNESPAD
   { "SNE1",		JOY_TYPE_SNESPAD_LPT1	},
   { "snespad1",	JOY_TYPE_SNESPAD_LPT1	},
   { "SNE2",		JOY_TYPE_SNESPAD_LPT2	},
   { "snespad2",	JOY_TYPE_SNESPAD_LPT2	},
   { "SNE3",		JOY_TYPE_SNESPAD_LPT3	},
   { "snespad3",	JOY_TYPE_SNESPAD_LPT3	},
#endif
#ifdef JOYSTICK_DRIVER_PSXPAD
   { "PSX1",		JOY_TYPE_PSXPAD_LPT1	},
   { "psxpad1",		JOY_TYPE_PSXPAD_LPT1	},
   { "PSX2",		JOY_TYPE_PSXPAD_LPT2	},
   { "psxpad2",		JOY_TYPE_PSXPAD_LPT2	},
   { "PSX3",		JOY_TYPE_PSXPAD_LPT3	},
   { "psxpad3",		JOY_TYPE_PSXPAD_LPT3	},
#endif
#ifdef JOYSTICK_DRIVER_N64PAD
   { "N641",		JOY_TYPE_N64PAD_LPT1	},
   { "n64pad1",		JOY_TYPE_N64PAD_LPT1	},
   { "N642",		JOY_TYPE_N64PAD_LPT2	},
   { "n64pad2",		JOY_TYPE_N64PAD_LPT2	},
   { "N643",		JOY_TYPE_N64PAD_LPT3	},
   { "n64pad3",		JOY_TYPE_N64PAD_LPT3	},
#endif
#ifdef JOYSTICK_DRIVER_DB9
   { "DB91",            JOY_TYPE_DB9_LPT1,      },
   { "db9pad1",         JOY_TYPE_DB9_LPT1,      },
   { "DB92",            JOY_TYPE_DB9_LPT2,      },
   { "db9pad2",         JOY_TYPE_DB9_LPT2,      },
   { "DB93",            JOY_TYPE_DB9_LPT3,      },
   { "db9pad3",         JOY_TYPE_DB9_LPT3,      },
#endif
#ifdef JOYSTICK_DRIVER_TURBOGRAFX
   { "TGX1",            JOY_TYPE_TURBOGRAFX_LPT1, },
   { "turbografx1",     JOY_TYPE_TURBOGRAFX_LPT1, },
   { "TGX2",            JOY_TYPE_TURBOGRAFX_LPT2, },
   { "turbografx2",     JOY_TYPE_TURBOGRAFX_LPT2, },
   { "TGX3",            JOY_TYPE_TURBOGRAFX_LPT3, },
   { "turbografx3",     JOY_TYPE_TURBOGRAFX_LPT3, },
#endif
#ifdef JOYSTICK_DRIVER_IFSEGA_ISA
   { "SEGI",		JOY_TYPE_IFSEGA_ISA	},
   { "segaisa",		JOY_TYPE_IFSEGA_ISA	},
#endif
#ifdef JOYSTICK_DRIVER_IFSEGA_PCI
   { "SEGP",		JOY_TYPE_IFSEGA_PCI	},
   { "segapci",		JOY_TYPE_IFSEGA_PCI	},
#endif
#ifdef JOYSTICK_DRIVER_IFSEGA_PCI_FAST
   { "SGPF",		JOY_TYPE_IFSEGA_PCI_FAST },
   { "segapcifast",	JOY_TYPE_IFSEGA_PCI_FAST },
#endif
#ifdef JOYSTICK_DRIVER_WIN32
   { "W32",		JOY_TYPE_WIN32		},
   { "win32",		JOY_TYPE_WIN32		},
#endif
   { NULL,		0        		}
};

static void CLI_Joystick(void)
{
   int ta;

   ArgPosition++;

   ta = 0;
   while( joy_options[ta].name ){

      if(!( stricmp( joy_options[ta].name, ArgList[ArgPosition] ))){

         JoystickType = joy_options[ta].id;
         return;

      }

      ta++;

   }

   allegro_message(
      "Unsupported joystick type\n"
      "See raine.cfg for a list of types\n"
      "eg. raine -joystick sidewinder\n"
      "\n"
   );
   exit(1);

}
#endif

// CLI_game_list():
// Output list of all games

static void CLI_game_list(void)
{
   int ta;

   for(ta=0; ta<game_count; ta++)

         printf("%-8s : %-30s\n", game_list[ta]->main_name, game_list[ta]->long_name);

   printf("\n");
   printf("%d Games Supported\n\n", game_count);

   exit(0);
}

// CLI_Verbose():
// Output extra info for some options

static void CLI_Verbose(void)
{
   verbose = 1;
}

static int get_rom_size(const ROM_INFO** rom_list) {
    int check_size = (*rom_list)->size;
    while ((*rom_list)[1].flags == LOAD_CONTINUE ||
	    (*rom_list)[1].flags == LOAD_IGNORE) {
	check_size += (*rom_list)[1].size;
	(*rom_list)++;
    }
    return check_size;
}

static void CheckGame(GAME_MAIN *game_info, int full_check)
{
   const DIR_INFO *dir_list;
   const ROM_INFO *rom_list;
   UINT8    *ram;
   char    *outbuf;
   UINT32     crc_32bit, len, bad_set;

   outbuf = malloc(0x4000);
   outbuf[0] = 0;

   printf("%-8s | %-30s", game_info->main_name, game_info->long_name);

   rom_list = game_info->rom_list;
   dir_list = game_info->dir_list;

   bad_set = 0;
   load_error = 0;
   load_debug = outbuf;

   while(rom_list->name){

       if (rom_list->flags == LOAD_FILL) {
	   rom_list++;
	   continue;
       }
      sprintf(outbuf+strlen(outbuf), "rom:%-12s size:0x%08x crc32:0x%08x -- ",rom_list->name,rom_list->size,rom_list->crc32);

      ram = malloc(rom_list->size);

      if(load_rom_dir(dir_list, rom_list->name, ram, rom_list->size, rom_list->crc32,full_check)){

         len = rom_size_dir(dir_list, rom_list->name, rom_list->size, rom_list->crc32);

         if(len != get_rom_size(&rom_list)){

            sprintf(outbuf+strlen(outbuf), "bad size: 0x%08x\n",len);
            bad_set = 1;

         }
         else{

	 if (full_check)
	   crc_32bit = crc32(0, ram, rom_list->size);

         if(full_check && crc_32bit != rom_list->crc32 && ~crc_32bit != rom_list->crc32){

            sprintf(outbuf+strlen(outbuf), "bad crc32: 0x%08x\n", crc_32bit);
            bad_set = 1;

         }
         else if (load_error){
	   sprintf(outbuf+strlen(outbuf),"\n");
	 } else {
            sprintf(outbuf+strlen(outbuf), "ok\n");
         }

         }

      }
      else{

         sprintf(outbuf+strlen(outbuf), "rom not found\n");
         bad_set = 1;

      }

      free(ram);

      rom_list++;

   }

   if (load_error)
     bad_set = 1;

   if(bad_set)

      printf(" | BAD\n");

   else

      printf(" | OK\n");


   if((verbose)||(bad_set))

      printf("%s",outbuf);


   free(outbuf);

}

// CLI_game_check():
// Check roms for a single or all games (todo - wildstar support)

static void CLI_game_check(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;

      for(i=0; i<game_count; i++){
         if(
             !(stricmp(ArgList[ArgPosition], game_list[i]->main_name))){
                CheckGame(game_list[i],0);
                exit(0);
         }
      }

      allegro_message(
	 "Unsupported game\n"
	 "Type 'Raine -gamelist' for a list of available games.\n"
	 "\n"
      );
      exit(1);

   }
   else{

      for(i=0; i<game_count; i++)
            CheckGame(game_list[i],0);

   }

   exit(0);
}

static void CLI_game_check_full(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;

      for(i=0; i<game_count; i++){
         if(
             !(stricmp(ArgList[ArgPosition], game_list[i]->main_name))){
                CheckGame(game_list[i],1);
                exit(0);
         }
      }

      allegro_message(
	 "Unsupported game\n"
	 "Type 'Raine -gamelist' for a list of available games.\n"
	 "\n"
      );
      exit(1);

   }
   else{

      for(i=0; i<game_count; i++)
            CheckGame(game_list[i],1);

   }

   exit(0);
}

#define QUOTE	"\""
#define INDENT	"\t"

static void GameInfo_Begin(void)
{
   printf("emulator (\n");
   printf(INDENT "name " QUOTE EMUNAME QUOTE "\n");
   printf(INDENT "version " QUOTE VERSION QUOTE "\n");
   printf(INDENT "games %d\n", game_count);
   printf(")\n\n");

}

static void GameInfo_End(void)
{
}

char *romof_list[MAX_ROMOF];

void find_romof(const struct DIR_INFO *dir_list, int *romof) {
  while(dir_list->maindir){

    if(IS_ROMOF(dir_list->maindir)){
      GAME_MAIN *game_romof;
      romof_list[(*romof)++] = (dir_list->maindir) + 1;
      if (*romof >= 4) {
	fprintf(stderr,"romof too big (%d), shouldn't happen.\n",*romof);
	exit(1);
      }
      // ... and if parent is a clone too...
      game_romof = find_game(dir_list->maindir+1);
      find_romof(game_romof->dir_list,romof);
    }

    dir_list ++;
  }
}

static void GameInfo(GAME_MAIN *game_info)
{
   int tb,tc,td,romof,cloneof,dup;
   const DIR_INFO *dir_list;
   const ROM_INFO *rom_list, *rom_list_tmp;
   const DSW_INFO *dsw;
   const VIDEO_INFO *vid_info;
   const SOUND_INFO *sound;
   GAME_MAIN *game_romof;
   printf("game (\n");

   /*

   'id' name (8 char, lower case)

   */

   printf(INDENT "name %s\n", game_info->main_name);

   /*

   full name (description)

   */

   printf(INDENT "description " QUOTE "%s" QUOTE, game_info->long_name);

   if(game_info->long_name_jpn)

      printf(" japanese " QUOTE "%s" QUOTE, game_info->long_name_jpn);

   printf("\n");

   /*

   manufacturer

   */

   printf(INDENT "manufacturer " QUOTE "%s" QUOTE "\n", game_company_name(game_info->company_id));

   /*

   year

   */

   if(game_info->year)

      printf(INDENT "year %4d\n", game_info->year);

   /*

   board number [optional]

   */

   if(game_info->board)

      printf(INDENT "board " QUOTE "%s" QUOTE "\n", game_info->board);

   /*

   romof %s [optional]

   */

   romof = 0;

   find_romof(game_info->dir_list, &romof);
   if (romof)
     printf(INDENT "romof %s\n", romof_list[0] );

   /*

   cloneof %s [optional]

   */

   cloneof = 0;

   dir_list = game_info->dir_list;

   while(dir_list->maindir){

      if(dir_list->maindir[0] == '$'){

            printf(INDENT "cloneof %s\n", (dir_list->maindir) + 1 );

            cloneof ++;

      }

      dir_list ++;

   }

   /*

   rom ( name %s merge %s size %d crc32 %08x region %s )

   */

   memset(load_region,0,sizeof(load_region));

   rom_list = game_info->rom_list;
   while(rom_list->name){

       if (!*rom_list->name) {
	   rom_list++;
	   continue;
       }
      rom_list_tmp=game_info->rom_list;
      dup=0;

      while(rom_list_tmp<rom_list)
      {
         if (!strcmp(rom_list->name, rom_list_tmp->name))
            dup++;
         rom_list_tmp++;
      }

      if (!dup && strcmp(rom_list->name,REGION_EMPTY)) {
	  printf(INDENT "rom ( name %s", rom_list->name);

	  if(romof){

	      tc = find_alternative_file_names(rom_list, game_info->dir_list);

	      for(td=0; td<tc; td++) {
		  printf(" merge %s", alt_names[td]);
	      }

	  }

	  printf(" size %d crc32 %08x", get_rom_size(&rom_list), rom_list->crc32);
	  if (rom_list->region) {
	      load_region[rom_list->region] = (UINT8*)rom_list->name;
	      printf(" regiona %s",get_region_name(rom_list->region));
	  }
	  printf(" )\n");
      } else if (!dup && rom_list->region)
	  load_region[rom_list->region] = (UINT8*)rom_list->name;

      rom_list++;

   }

   if (romof) { // we have clones !
     int region,i;
     for (region=1; region < REGION_MAX; region++) {
       // Not found -> go to the parent !
       for (i=0; i<romof; i++) {
	 if (!load_region[region]) {
	   game_romof = find_game(romof_list[i]);
	   rom_list = game_romof->rom_list;
	   while(rom_list->name){
	     if (rom_list->region == region) {
	       rom_list_tmp=game_romof->rom_list;
	       dup=0;

	       while(rom_list_tmp<rom_list)
		 {
		   if (!strcmp(rom_list->name, rom_list_tmp->name))
		     dup++;
		   rom_list_tmp++;
		 }

	       if (!dup && strcmp(rom_list->name,REGION_EMPTY) && *rom_list->name) {
		   /* The merge thing is inherited from the old days. Its only
		      purpose is to show at a glance that a rom is inherited from
		      the parent. Here the repeating of the name is stupid, but it's
		      for compatibility... */
		   printf(INDENT "rom ( name %s merge %s", rom_list->name,rom_list->name);
		   printf(" size %d crc32 %08x", get_rom_size(&rom_list), rom_list->crc32);
		   if (rom_list->region)
		       printf(" regionb %s",get_region_name(rom_list->region));
		   printf(" )\n");
		   load_region[rom_list->region] = (UINT8*)rom_list->name; // to avoid duplication
	       }
	     }
	     rom_list++;
	   }
	 }
       }
     }
   }

   /*

   archive ( name %s ... )

   */

   dir_list = game_info->dir_list;

   printf(INDENT "archive ( ");

   while(dir_list->maindir){

      if((dir_list->maindir[0] != '#') && (dir_list->maindir[0] != '$'))

         printf("name " QUOTE "%s" QUOTE " ", dir_list->maindir);

      dir_list++;

   }

   printf(")\n");

   /*

   chip ( type audio name %s ) [optional]

   */

   sound = game_info->sound;

   if(sound){

      while(sound->interface){

         printf(INDENT "chip ( type audio name \"%s\" )\n", get_sound_chip_name(sound->type));

         sound++;

      }

   }

   /*

   input ( dipswitches %d ) [optional]

   */

   dsw = game_info->dsw;

   tb = 0;
   if(dsw){

      while(dsw->data){

         tb++;

         dsw++;

      }

   }

   if(tb){

      printf(INDENT "input ( ");
      printf("dipswitches %d ", tb);
      printf(")\n");

   }

   /*

   video ( screen raster x %d y %d colors %d freq %d )

   */

   vid_info = game_info->video;

   printf(INDENT "video ( screen raster ");

   if(vid_info->flags & VIDEO_ROTATABLE){

   switch(VIDEO_ROTATE( vid_info->flags )){
      case VIDEO_ROTATE_NORMAL:
         printf("orientation horizontal ");
      break;
      case VIDEO_ROTATE_90:
         printf("orientation vertical ");
      break;
      case VIDEO_ROTATE_180:
         printf("orientation horizontal ");
      break;
      case VIDEO_ROTATE_270:
         printf("orientation vertical ");
      break;
   }

   }
   else{
      printf("orientation undefined ");
   }

   printf("x %d y %d ", vid_info->screen_x, vid_info->screen_y);
   printf("freq %g )\n",(vid_info->fps < 0.1 ? 60.0 : vid_info->fps));

   /*

   driver ( status good|imperfect|preliminary color good colordeep 8|16 credits %s )

   */

   printf(INDENT "driver ( status %s color good colordeep %d credits " QUOTE "%s" QUOTE " )\n",
      (game_info->flags & GAME_NOT_WORKING) ? "preliminary" :
      ((game_info->flags & GAME_PARTIALLY_WORKING) ? "imperfect" : "good"),
	  ((vid_info->flags & VIDEO_NEEDS_16BPP) ? 16 : 8),
	  "Antiriad & Raine Team"
	  );

   printf(")\n\n");
}

// CLI_game_info():
// List game info for a combination of games (todo - wildstar support)

static void CLI_game_info(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;

      for(i=0; i<game_count; i++){
         if(
            !(stricmp(ArgList[ArgPosition], game_list[i]->main_name))){

            GameInfo_Begin();
            GameInfo(game_list[i]);
            GameInfo_End();

            exit(0);
         }
      }

      printf(
	 "Unsupported game\n"
	 "Type 'Raine -gamelist' for a list of available games.\n"
	 "\n"
      );
      exit(1);

   }
   else{

      GameInfo_Begin();

      for(i=0;i<game_count;i++)

            GameInfo(game_list[i]);

      GameInfo_End();

   }

   exit(0);

}

static void dsw_info_Begin(void)
{
   printf("emulator (\n");
   printf(INDENT "name " QUOTE EMUNAME QUOTE "\n");
   printf(INDENT "version " QUOTE VERSION QUOTE "\n");
   printf(INDENT "games %d\n", game_count);
   printf(")\n\n");
}

static void dsw_info_End(void)
{
}

static void list_game_info(GAME_MAIN *game_info) {
   printf("game (\n");

   /*

   'id' name (8 char, lower case)

   */

   printf(INDENT "name %s\n", game_info->main_name);

   /*

   full name (description)

   */

   printf(INDENT "description " QUOTE "%s" QUOTE "\n", game_info->long_name);

   /*

   manufacturer

   */

   printf(INDENT "manufacturer " QUOTE "%s" QUOTE "\n", game_company_name(game_info->company_id));
}

static void dsw_info(GAME_MAIN *game_info)
{
   const DSW_INFO *dsw;
   DSW_DATA *dsw_data;
   UINT32 i;

   list_game_info(game_info);

   /*

   dsw ( type audio name %s ) [optional]

   */

   dsw = game_info->dsw;

   i = 0;

   if(dsw){

      while(dsw->data){

         dsw_data = dsw->data;

         printf(INDENT "dipswitch ( number %d factory 0x%02x )\n", i, dsw->factory_setting);

         while(dsw_data->name){

				if(dsw_data->count)

          	  printf(INDENT "dipdata ( type head bitmask 0x%02x name " QUOTE "%s" QUOTE " )\n", dsw_data->bit_mask, dsw_data->name);

				else

          	  printf(INDENT "dipdata ( type body bitmask 0x%02x name " QUOTE "%s" QUOTE " )\n", dsw_data->bit_mask, dsw_data->name);

            dsw_data++;

         }

         dsw++;
         i++;

      }

   }

   printf(")\n\n");
}

// CLI_dsw_info():
// List game info for a combination of games (todo - wildstar support)

static void CLI_dsw_info(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;

      for(i=0; i<game_count; i++){
         if(
            !(stricmp(ArgList[ArgPosition], game_list[i]->main_name))){

            dsw_info_Begin();
            dsw_info(game_list[i]);
            dsw_info_End();

            exit(0);
         }
      }

      printf(
	 "Unsupported game\n"
	 "Type 'Raine -gamelist' for a list of available games.\n"
	 "\n"
      );
      exit(1);

   }
   else{

      dsw_info_Begin();

      for(i=0;i<game_count;i++)

            dsw_info(game_list[i]);

      dsw_info_End();

   }

   exit(0);

}

static void CLI_lsf(void)
{
   int i;

   if( ((ArgPosition+1) < ArgCount) && (ArgList[ArgPosition+1][0] != '-') ){

      ArgPosition++;

      for(i=0; i<game_count; i++){
         if(
            !(stricmp(ArgList[ArgPosition], game_list[i]->main_name))){

	   list_game_info(game_list[i]);
	   printf( INDENT "source file : %s\n",game_list[i]->source_file);
	   printf(")\n\n");

            exit(0);
         }
      }

      printf(
	 "Unsupported game\n"
	 "Type 'Raine -gamelist' for a list of available games.\n"
	 "\n"
      );
      exit(1);

   }
   else{

      for(i=0;i<game_count;i++) {

	   list_game_info(game_list[i]);
	   printf( INDENT "source file : %s\n",game_list[i]->source_file);
	   printf(")\n\n");
      }
   }

   exit(0);

}

// CLI_OPTION:
// Type for command line process list

typedef struct CLI_OPTION
{
   char *Name;			// Option name/string
   void (*Process)();		// Pointer to option process function
} CLI_OPTION;

#ifdef SDL
static int intArg(int min, int max, char *errNoArg, char *errOutofLimits) {
    // Process integer positive arguments, 2 possible error messages
    int mode = -1;
    if ((ArgPosition+1) < ArgCount) {
	ArgPosition++;
	mode = atoi(ArgList[ArgPosition]);
    }
    else {
	printf("%s\n",errNoArg);
	exit(1);
    }
    if (mode < min || mode > max) {
	printf("%s\n",errOutofLimits);
	exit(1);
    }
    return mode;
}

static void CLI_video_mode(void) {
    display_cfg.video_mode = intArg(0,2,"video mode number missing !","video_mode must be between 0 & 2 (0 = opengl, 1 = yuv overlays, 2 = normal blits");
}

static void CLI_render() {
    ogl.render = intArg(0,1,"missing renderer argument","renderer must be 0 = DrawPixels, or 1 = Texture");
}

static void CLI_dbuf() {
    ogl.dbuf = intArg(0,1,"Missing dbuf argument","dbuf must be 0 = off, or 1 = on");
}

static void CLI_shader() {
    if ((ArgPosition+1) < ArgCount) strcpy(ogl.shader,ArgList[ArgPosition+1]);
}

static void CLI_filter() {
    int filter = intArg(0,1,"Missing filter argument", "filter must be 0 = GL_NEAREST, 1 = GL_LINEAR");
    // use a function to avoid to include opengl.h in windows which makes
    // collisions with the old allegro api
    set_opengl_filter(filter);
}
#endif

// Command_Options:
// List of command line options and their handlers

static CLI_OPTION cli_commands[] =
{
   { "-gamelist",	CLI_game_list		},
   { "-gl",		CLI_game_list		},
   { "-gameinfo",	CLI_game_info		},
   { "-listinfo",	CLI_game_info		},
   { "-li",		CLI_game_info		},
   { "-romcheck",	CLI_game_check		},
   { "-rc",		CLI_game_check		},
   { "-romcheck-full",	CLI_game_check_full	},
   { "-rcf",		CLI_game_check_full	},
   { "-verifyroms",	CLI_game_check		},
   { "-game",		CLI_game_load		},
   { "-g",		CLI_game_load		},
   { "-listdsw",	CLI_dsw_info		},
   { "-lsf",            CLI_lsf },
   { "-source_file",    CLI_lsf },
   { "-help",		CLI_Help		},
   { "-?",		CLI_Help		},
   { "--help",          CLI_Help                },
   { "-h",              CLI_Help                },
#ifdef RAINE_DOS
   { "-joystick",	CLI_Joystick		},
   { "-j",		CLI_Joystick		},
#endif
   { "-limitspeed",	CLI_LimitSpeed		},
   { "-l",		CLI_LimitSpeed		},
   { "-nogui",		CLI_NoGUI		},
   { "-n",		CLI_NoGUI		},
   { "-leds",		CLI_EnableLeds		},
   { "-noleds",		CLI_DisableLeds         },
   { "-cont",		   CLI_EnableCont          },
   { "-nocont",		CLI_DisableCont         },
   { "-autoload",		CLI_EnableAutoLoad      },
   { "-noautoload",	CLI_DisableAutoLoad     },
   { "-screenx",	CLI_screen_x		},
   { "-sx",		CLI_screen_x		},
   { "-screeny",	CLI_screen_y		},
   { "-sy",		CLI_screen_y		},
   { "-geometry",	CLI_geometry },
#ifndef SDL
   { "-screenmode",	CLI_screen_mode		},
   { "-sm",		CLI_screen_mode		},
#else
   { "-fullscreen",	CLI_fullscreen_mode		},
   { "-fs",		CLI_fullscreen_mode		},
#endif
   { "-rotate",		CLI_screen_rotate	},
   { "-r",		CLI_screen_rotate	},
   { "-ror",		CLI_screen_rotate_right	},
   { "-rol",		CLI_screen_rotate_left	},
   { "-norotate",	CLI_screen_no_rotate	},
   { "-nor",		CLI_screen_no_rotate	},
   { "-flip",		CLI_screen_flip		},
   { "-f",		CLI_screen_flip		},
   { "-flipx",		CLI_screen_flip_x	},
   { "-fx",		CLI_screen_flip_x	},
   { "-flipy",		CLI_screen_flip_y	},
   { "-fy",		CLI_screen_flip_y	},
   { "-noflip",		CLI_screen_no_flip	},
   { "-nof",		CLI_screen_no_flip	},
#ifndef SDL
   { "-hide",           CLI_hide                },
#endif
   { "-bpp",            CLI_screen_bpp          },
   { "-depth",          CLI_screen_bpp          },
   { "-region",		CLI_region },
#ifdef SDL
   { "-video",		CLI_video_mode		},
   { "-vm",		CLI_video_mode		},
   { "-render",		CLI_render		},
   { "-dbuf",		CLI_dbuf		},
   { "-shader",		CLI_shader		},
   { "-filter",		CLI_filter		},
#endif
   { NULL,		NULL        		}
};

static CLI_OPTION cli_options[] =
{
   { "-verbose",	CLI_Verbose		},
   { "-v",		CLI_Verbose		},
   { NULL,		NULL        		}
};

/*

parse_command_line(): process command line options.

*/

void parse_command_line(int argc, char *argv[])
{
   UINT32 ta;

   if(argc){

   verbose = 0;

   ArgCount = argc;

   for(ta=0; ta<(UINT32)ArgCount; ta++)
      ArgList[ta] = argv[ta];

   // check for options first

   for(ArgPosition=1; ArgPosition<ArgCount; ArgPosition++){

       if(*ArgList[ArgPosition] == '-'){

       ta=0;
       while((cli_options[ta].Process) && (ta!=255)){
          if(!(stricmp(cli_options[ta].Name, ArgList[ArgPosition]))){
             ArgList[ArgPosition] = NULL;
             cli_options[ta].Process();
             ta=255;
          }
          else{
             ta++;
          }
       }

       }

   }

   // now check for commands

   for(ArgPosition=1; ArgPosition<ArgCount; ArgPosition++){

       if(ArgList[ArgPosition]){

       // command line options start with '-'

       if(*ArgList[ArgPosition] == '-'){

       ta=0;
       while((cli_commands[ta].Process) && (ta!=255)){
          if(!(stricmp(cli_commands[ta].Name, ArgList[ArgPosition]))){
             cli_commands[ta].Process();
             ta=255;
          }
          else{
             ta++;
          }
       }
       if(ta!=255){
          printf(
		"Unsupported command line option: %s\n"
		"Type 'Raine -help' for a list of available options.\n"
		"\n",
		ArgList[ArgPosition]
          );
          exit(1);
       }

       }
       else if (ArgPosition == ArgCount-1) {

          // allow raine <gamename> (preferred use is raine -game <gamename>)
#if HAS_NEO
	  char *s = ArgList[ArgPosition];

	   if (is_dir(ArgList[ArgPosition]) ||
		   !stricmp(&s[strlen(s)-4],".iso") ||
		   !stricmp(&s[strlen(s)-7],".iso.gz") ||
		   !stricmp(&s[strlen(s)-4],".zip") ||
		   !stricmp(&s[strlen(s)-3],".7z") ||
		   !stricmp(&s[strlen(s)-4],".cue") ||
		   !stricmp(&s[strlen(s)-7],"ipl.txt")
		   ) {
	       // iso or directory, assuming neocd image
#ifdef RAINE_SDL
	       sdl_init();
#endif
	       backslash(ArgList[ArgPosition]);
	       load_neo_from_name(ArgList[ArgPosition]);
	   } else
#endif
	       CLI_game_load_alt();

       }

       }

   }

   }
}

#ifdef RAINE_DOS
// CLI_WaitKeyPress():
// wait for a key routine.

void CLI_WaitKeyPress(void)
{
   install_keyboard();

   clear_keybuf();
   do{
   }while(!keypressed());
   if((readkey()&0xFF)==27){
      exit(0);
   }

   remove_keyboard();
}
#endif

/*

load_main_config(void): load main raine settings

*/

void load_main_config(void)
{
   char str[256];

   // config/raine.cfg -------------------------------------

   snprintf(str,256,"%sconfig/%s", dir_cfg.exe_path, dir_cfg.config_file);
   raine_set_config_file(str);
}

/*

save_main_config(void): load main raine settings

*/

void save_main_config(void)
{
   char str[256];

   // config/raine.cfg -------------------------------------

   raine_push_config_state();

   snprintf(str,256,"%sconfig/%s", dir_cfg.exe_path, dir_cfg.config_file);
   raine_set_config_file(str);


   raine_pop_config_state();

}

/*

load_game_config(int game): load game specific settings for a certain game.

*/

static void load_cheats(char *name) {
    char buff[80];
  load_arpro_cheats(name);
  if (CheatCount == 0 && !is_neocd()) {
      sprintf(buff,"%s:!neocd",name);
      load_arpro_cheats(buff);
  }
}

void load_game_config(void)
{
   char str[256];
   print_debug("load_game_config: %s\n",current_game->main_name);

   // config/games.cfg -------------------------------------

   raine_push_config_state();

   snprintf(str,256,"%sconfig/games.cfg", dir_cfg.exe_path);
   raine_set_config_file(str);

   // Load Key Settings

   sprintf(str,"%s:keyconfig", current_game->main_name);
   load_game_keys(str);

#ifndef SDL
   // Load Joy Settings

   sprintf(str,"%s:joyconfig", current_game->main_name);
   load_game_joys(str);
#endif

   // Load Screen Settings

   sprintf(str,"%s:display", current_game->main_name);
   load_screen_settings(str);

   if (!is_neocd()) {
       // Load DSW Settings

       sprintf(str,"%s:dipswitch", current_game->main_name);
       load_dipswitches(str);
   }

   // Load ROM Version Settings

   sprintf(str,"%s:romversion", current_game->main_name);
   load_romswitches(str);

#if HAS_NEO
   sprintf(str,"%s:assoc", current_game->main_name);
   load_assoc(str);

   // config/cheats.cfg ------------------------------------

   if (is_neocd() || current_game->load_game == &load_neocd)
       sprintf(str,"%s",get_shared("neocheats.cfg"));
   else
#endif
       sprintf(str,"%s",get_shared("cheats.cfg"));
   raine_set_config_file(str);

   // Load Cheat Settings

   load_cheats(current_game->main_name);
   if (!is_neocd()) {
       if (CheatCount == 0) {
	   char *parent = (char*)parent_name();
	   if (parent != current_game->main_name)
	       load_cheats(parent); // default : if no cheats, try the parent !
       }
   }

   raine_pop_config_state();
}

/*

save_game_config(int game): save game specific settings for a certain game.

*/

void save_game_config(void)
{
   char str[256];
   print_debug("save_game_config: %s\n",current_game->main_name);

   // config/games.cfg -------------------------------------

   raine_push_config_state();

   snprintf(str,256,"%sconfig/games.cfg", dir_cfg.exe_path);
   raine_set_config_file(str);

   // Save Key Settings

   sprintf(str,"%s:keyconfig", current_game->main_name);
   save_game_keys(str);

#ifndef SDL
   // Save Joy Settings

   sprintf(str,"%s:joyconfig", current_game->main_name);
   save_game_joys(str);
#endif

   // Save screeen settings

   sprintf(str,"%s:display", current_game->main_name);
   save_screen_settings(str);

   if (!is_neocd()) {
       // Save DSW Settings

       sprintf(str,"%s:dipswitch", current_game->main_name);
       save_dipswitches(str);
   }

   // Save ROM Version Settings

   sprintf(str,"%s:romversion", current_game->main_name);
   save_romswitches(str);

#if HAS_NEO
   sprintf(str,"%s:assoc", current_game->main_name);
   save_assoc(str);
#endif

   raine_pop_config_state();
#ifndef SDL
   // there is no reason to save this in the sdl version since the cheats
   // can't be edited for now from the gui...
   // config/cheats.cfg ------------------------------------

   raine_push_config_state();

   // Must always be saved here.
   sprintf(str,"%sconfig/cheats.cfg", dir_cfg.exe_path);
   raine_set_config_file(str);

   // Save Cheat Settings

   save_arpro_cheats(current_game->main_name);

   raine_pop_config_state();
#endif

}

