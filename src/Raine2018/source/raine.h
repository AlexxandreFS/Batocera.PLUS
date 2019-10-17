
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*																			  */
/*		  RAINE (680x0 arcade emulation) v0.28 (C) 1998/99 Raine Team		  */
/*																			  */
/******************************************************************************/

#ifndef __rainedefs__
#define __rainedefs__

#include <stdio.h>
#include <stdlib.h> // Would you believe that this is included by allegro.h
#include <stdarg.h> // this one too by the way (needed by arkanoid.c at least)

#include <string.h>
#include "translate.h"

#ifndef SDL
#include <allegro.h>
#ifdef RAINE_UNIX
// Well sorry : these are defined only in allegro dos...
#define GFX_DRIVER_VGA
#define GFX_DRIVER_MODEX
#endif // RAINE_UNIX
#ifdef GFX_DRIVER_MODEX
#define GFX_ARCMON				 AL_ID('A','R','C','M')
#endif
#else
#include "sdl/compat.h"
#endif

#ifdef MEMORY_DEBUG
#include "newmem.h"     // This must be placed before other includes
#endif

#include "deftypes.h"       // Raine data types
#include "confile.h"
#include "debug.h" // if needed

// Compilation Options

#define FASTF3MEM		// Use Faster (no bad address checking) memory access in F3-System
#define F3SINGLE		// Directly use F3-System memory access in 68020 engine

#define BGAMES			// Beta/Unreleased games included

#if !defined(NO_ASM) || defined(__MMX__)
#define RDTSC_PROFILE		// Rdtsc profiling included
#endif

#ifndef SDL
#define TRIPLE_BUFFER		// Triple buffer support included
#endif

// Useful String Constants

#define HANDLE	"Raine Team"    // Credit string
#ifdef RAINE_WIN32
#define EMUNAME "Raine32"       // Win32/DirectX Name
#else
#define EMUNAME "Raine"    // Dos/Linux Name
#endif

#ifdef RAINE_UNIX
   #define SLASH "/"
#else
   #define SLASH "\\"
#endif

extern UINT8 *R24[0x100],		// Memory Addresses for UAE020 Read
*W24[0x100],		// Memory Addresses for UAE020 Read
*ROM, 		// Pointer for ROM memory
*RAM, 		// Pointer for RAM memory
*GFX, 		// Pointer for Graphics memory
*SMP, 		// Pointer for Sample memory
*EEPROM,			// Pointer for EEPROM memory
*Z80ROM;			// Pointer for Z80ROM memory
extern int MC68020;  // 68020 running ???
#ifdef RAINE_UNIX
extern int x_display;			// Running in XFree ???
#endif

#define pretty_emu_name      \
     "\E[1m " /* bold */     \
     "\E[31mR" /* red */     \
     "\E[33mA" /* yellow */  \
     "\E[32mI" /* green */   \
     "\E[34mN" /* blue */    \
     "\E[35mE" /* magenta */ \
     "\E[0m" /* reset */

/*

x86 memory access

*/

#define ReadByte(a) (*(UINT8  *)(a))
#define ReadWord(a) (*(UINT16 *)(a))
#define ReadLong(a) (*(UINT32 *)(a))

#define WriteByte(a,d)	(*(UINT8  *)(a) = (d))
#define WriteWord(a,d)	(*(UINT16 *)(a) = (d))
#define WriteLong(a,d)	(*(UINT32 *)(a) = (d))

/*

680x0 memory access

*/

static DEF_INLINE UINT32 m680x0_get_word(UINT16 *a)
{
#ifdef NO_ASM
   return (((UINT8 *) a)[0] << 8) | (((UINT8 *) a)[1] << 0);
#else
   UINT32 retval;
   asm("xorl %k0,%k0\n\tmovw %w1,%w0\n\trolw $8,%w0" : "=&r" (retval) : "m" (*a) : "cc");
	return retval;
#endif
}

static DEF_INLINE UINT32 m680x0_get_long(UINT32 *a)
{
#ifdef NO_ASM // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   return (((UINT8 *) a)[0] << 24) | (((UINT8 *) a)[1] << 16) | (((UINT8 *) a)[2] << 8) | (((UINT8 *) a)[3] << 0);
#else
   UINT32 retval;
   asm("bswapl %0" : "=r" (retval) : "0" (*a) : "cc");
   return retval;
#endif
}

#define ReadByte68k(a)	(*(UINT8 *)(a))
#define ReadWord68k(a)	m680x0_get_word((UINT16 *)(a))
#define ReadLong68k(a)	m680x0_get_long((UINT32 *)(a))

static DEF_INLINE void m680x0_put_word(UINT16 *a, UINT32 v)
{
#ifdef NO_ASM // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   ((UINT8 *) a)[0] = (v >> 8) & 0xFF;
   ((UINT8 *) a)[1] = (v >> 0) & 0xFF;
#else
   asm("rolw $8,%w0" : "=r" (v) : "0" (v) : "cc");
   *a = v;
#endif
}
static DEF_INLINE void m680x0_put_long(UINT32 *a, UINT32 v)
{
#ifdef NO_ASM // !defined(RAINE_DOS) && !defined(RAINE_UNIX)
   ((UINT8 *) a)[0] = (v >>24) & 0xFF;
   ((UINT8 *) a)[1] = (v >>16) & 0xFF;
   ((UINT8 *) a)[2] = (v >> 8) & 0xFF;
   ((UINT8 *) a)[3] = (v >> 0) & 0xFF;
#else
   asm("bswapl %0" : "=r" (v) : "0" (v) : "cc");
   *a = v;
#endif
}

#define WriteByte68k(a,d)	(*(UINT8 *)(a) = (d))
#define WriteWord68k(a,d)	m680x0_put_word((UINT16 *)(a), (d))
#define WriteLong68k(a,d)	m680x0_put_long((UINT32 *)(a), (d))

// UAE 68020 Read Pointers
// -----------------------

extern UINT8  (*ByteRead)(UINT32 address);
extern UINT16 (*WordRead)(UINT32 address);
extern UINT32 (*LongRead)(UINT32 address);

// UAE 68020 Write Pointers
// ------------------------

extern void (*ByteWrite)(UINT32 address, UINT8  data);
extern void (*WordWrite)(UINT32 address, UINT16 data);
extern void (*LongWrite)(UINT32 address, UINT32 data);

extern void (*F3SystemEEPROMAccess)(UINT8 data);

#ifdef F3SINGLE

static DEF_INLINE UINT8 ReadF3SystemByte(UINT32 i)
{
   return(R24[(i>>16)&0xFF][i&0xFFFF]);
}

static DEF_INLINE UINT16 ReadF3SystemWord(UINT32 i)
{
   return(ReadWord68k(&R24[(i>>16)&0xFF][i&0xFFFF]));
}

static DEF_INLINE UINT32 ReadF3SystemLong(UINT32 i)
{
   return(ReadLong68k(&R24[(i>>16)&0xFF][i&0xFFFF]));
}

static DEF_INLINE void WriteF3SystemByte(UINT32 i, UINT8 data)
{
   W24[(i>>16)&0xFF][i&0xFFFF]=data;
}

static DEF_INLINE void WriteF3SystemWord(UINT32 i, UINT16 data)
{
   WriteWord68k(&W24[(i>>16)&0xFF][i&0xFFFF],data);
}

static DEF_INLINE void WriteF3SystemLong(UINT32 i, UINT32 data)
{
   WriteLong68k(&W24[(i>>16)&0xFF][i&0xFFFF],data);
}

// Define UAE 680x0 Read routines
// ------------------------------

#define cpu_readmem24(address)			ReadF3SystemByte(address)
#define cpu_readmem24_word(address) 	ReadF3SystemWord(address)
#define cpu_readmem24_dword(address)		ReadF3SystemLong(address)

// Define UAE 680x0 Write routines
// -------------------------------

#define cpu_writemem24(address,data)		WriteF3SystemByte(address,data)
#define cpu_writemem24_word(address,data)	WriteF3SystemWord(address,data)
#define cpu_writemem24_dword(address,data)	WriteF3SystemLong(address,data)

#else

// Define UAE 680x0 Read routines
// ------------------------------

#define cpu_readmem24(address)			ByteRead(address)
#define cpu_readmem24_word(address) 	WordRead(address)
#define cpu_readmem24_dword(address)		LongRead(address)

// Define UAE 680x0 Write routines
// -------------------------------

#define cpu_writemem24(address,data)		ByteWrite(address,data)
#define cpu_writemem24_word(address,data)	WordWrite(address,data)
#define cpu_writemem24_dword(address,data)	LongWrite(address,data)

#endif

#define CPU_FRAME_MHz(speed,slice) ((speed*1000000)/slice)


#ifndef SDL
DATAFILE *RaineData;		// Resource datafile
#endif

extern int StarScreamEngine,		// Number of M68000's in use
MZ80Engine; 		// Number of Z80's in use

extern int RAMSize;			// Size of RAM[] block

extern UINT8 *ingame_font; 	// Raw data for ingame font


extern int RefreshBuffers;

/*

general configuration

*/

typedef struct RAINE_CFG
{
   UINT32 show_fps_mode;			// type of fps output
   UINT32 no_gui;			// gui is disabled
   UINT32 req_load_game;			// request to load game (from the command line)
   UINT32 req_game_index;		// game number for req_load_game
   UINT32 version_no;			// what version of raine is running
   UINT32 run_count;			// how many times raine has run
   UINT32 wibble;			// wibble the screen
   UINT32 extra_games;			// extra games enable (currently unused)
   UINT32 save_game_screen_settings;	// save display config for each game
   UINT32 hide;
   UINT32 req_pause_game;
   UINT32 req_save_screen;
   UINT32 req_pause_scroll;
   UINT32 auto_save; // Auto-save/load current game
} RAINE_CFG;

extern struct RAINE_CFG raine_cfg;

// flags for auto_save

#define FLAG_AUTO_SAVE 1
#define FLAG_AUTO_LOAD 2

/*

display configuration

*/

typedef struct DISPLAY_CFG
{
#ifndef SDL
   UINT32 screen_type;			// pc screen display type {..MODX,VB2L,VBAF..}
#else
   UINT32 video_mode,video_driver;
   // 0 : auto-detect (hw YUV overlay, then classic blits)
   // 1 : force YUV overlays
   // 2 : force classic blits
   UINT32 winx,winy; // size of window (used when toggling fullscreen)
#endif
   INT32 screen_x; 		// pc screen display width
   INT32 screen_y; 		// pc screen display height
   UINT32 scanlines;			// scanlines mode {0,1,2}
#ifndef SDL
   UINT32 vsync;			// vsync mode {0,1}
   UINT32 triple_buffer;		// triple buffer mode {0,1}
   UINT32 eagle_fx; 		// use eagle effect {0,1}
#endif
   UINT16 stretch; // see sdl/dialogs/video_options.cpp for meaning

#ifndef SDL
   UINT32 fast_set_pal; 		// fast or slow(compatable) set pal {0,1}
   UINT32 screenshot_png;
   UINT32 pixel_double; 		// double pixels effect {0,1,2}
#endif
   UINT32 limit_speed;			// don't exceed 60 fps {0,1}
   UINT32 frame_skip;			// skip frames number {0..9} (0=auto frame skip)
#ifndef SDL
#if defined(RAINE_DOS) || defined(RAINE_UNIX)
   UINT32 arcade_h_timing;		// arcade monitor mode
   UINT32 arcade_v_timing;
   UINT32 arcade_center_x;
   UINT32 arcade_center_y;
#endif
#endif
   UINT32 rotate;			// real rotation setting {0,1,2,3}
   UINT32 flip; 			// real flipping setting {0,1,2,3}
   UINT32 user_rotate;			// user preferred rotation {0,1,2,3}
   UINT32 user_flip;			// user preferred flipping {0,1,2,3}
   UINT32 no_rotate;			// ignore default rotation in game drivers
   UINT32 no_flip;			// ignore default rotation in game drivers
  UINT32 auto_mode_change; // Mode change allowed when loading a game ?
   UINT32 bpp;							// colour depth {8,15,16,24,32}
#ifdef SDL
   UINT32 fix_aspect_ratio; // fix aspect for YUV overlays
   int fullscreen,double_buffer,noborder,keep_ratio;
#endif
} DISPLAY_CFG;

extern struct DISPLAY_CFG display_cfg, game_display_cfg, prev_display_cfg;

extern int use_custom_screen;

/*

file & directory configuration

*/

typedef struct DIR_CFG
{
   char exe_path[FILENAME_MAX]; 		// current path of raine.exe
   char share_path[FILENAME_MAX];		// location of data files
#ifndef SDL
   char language_file[FILENAME_MAX];		// language translation file (no path)
#endif
   char screen_dir[FILENAME_MAX];		// screenshot path
   char emudx_dir[FILENAME_MAX];		// screenshot path
   char artwork_dir[FILENAME_MAX];		// screenshot path
   char **rom_dir;		// rom paths
   char config_file[FILENAME_MAX];		// config file (no path)
   char m68kdis[FILENAME_MAX],dz80[FILENAME_MAX];
   UINT32 long_file_names;		// enable long file name support
   UINT32 last_screenshot_num;		// counter for last screenshot
} DIR_CFG;

extern struct DIR_CFG dir_cfg;

extern char raine_cpu_model[80];
#endif

#ifdef __cplusplus
}
#endif
