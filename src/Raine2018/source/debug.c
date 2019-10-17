/******************************************************************************/
/*                                                                            */
/*                              DEBUG FILE SUPPORT                            */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include "version.h"

#include "raine.h"
#include "files.h"

#ifdef RAINE_DEBUG

int debug_mode;

static FILE *file_debug;

/*

write a string to the debug file. supports printf() sytle formatting.

*/

#ifdef RAINE_WIN32
static char debug_name[256];
#endif

void print_debug(const char *format, ...)
{
  if(debug_mode){

      char debug_str[256];
      va_list ap;
      va_start(ap,format);
      vsprintf(debug_str,format,ap);
      va_end(ap);

      /* RAINE_WIN32 has some restrictions : when the computer freezes, */
      /* which is rather common in win98, the debug file stays stupidly */
      /* at 0 byte. These defines are an attempt to avoid this... */
#ifdef RAINE_WIN32
      if (debug_mode < 2) {
	file_debug = fopen(debug_name,"a+");
	fseek(file_debug,0,2);
      } // else file_debug is stderr
#else
      if (!file_debug) return;
#endif
      fprintf(file_debug, "%s",debug_str);
      //#ifndef RAINE_DOS
      fflush(file_debug);
      // Why does this simple flush not work in win32 ???
      //#endif
#ifdef RAINE_WIN32
      fclose(file_debug);
#endif
  }
}

void open_debug(void)
{
   if(debug_mode){

      char str[256];

      snprintf(str,256,"%sdebug",dir_cfg.exe_path);
      mkdir_rwx(str);
      snprintf(str,256,"%sdebug/debug.txt",dir_cfg.exe_path);

      if (debug_mode < 2) {
	if(!(file_debug=fopen(str,"w"))){
	  printf("Unable to write to %s\n",str);
	  exit(1);
	}
#ifdef RAINE_WIN32
	fclose(file_debug);
	strcpy(debug_name,str);
#endif
      } else
	file_debug = stderr;

      print_debug( EMUNAME " " VERSION " Debug File (Illegal Mem accesses etc...)\n");
      print_debug("--------------------------------------------------------\n\n");


#ifdef MEMORY_DEBUG
      InitPurify();
#endif

   }
}

void close_debug(void)
{
   if(debug_mode){

#ifdef MEMORY_DEBUG
      DonePurify();
#endif
#ifndef RAINE_WIN32
      fclose(file_debug);
      file_debug = NULL;
#endif

   }
}

#endif
