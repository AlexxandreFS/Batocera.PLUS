/******************************************************************************/
/*                                                                            */
/*                        RAINE FILE ACCESS/ZIP SUPPORT                       */
/*                                                                            */
/******************************************************************************/

#ifdef RAINE_WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h> // mkdir
#include <unistd.h> // mkdir for mingw !
#include "raine.h"
#include "unzip.h"
#include "files.h"
#include "conf-cpu.h"
#ifdef HAVE_68000
#include "starhelp.h"
#endif
#include "version.h" // To recompile when the makefile changes (RAINE_DEBUG)
#include "loadroms.h"
#ifndef BYTE_ORDER
#ifdef RAINE_DOS
#include <machine/endian.h>
#else
// for mingw32...
#include <sys/param.h>
#endif
#endif
#include "newmem.h"

#ifndef BYTE_ORDER
#error no byte order info sorry
#endif

#ifdef __MINGW32__
/* Strange that mingw does not define the standard posix mkdir... windows even has
   file permissons now, even if it's messy */
#define my_mkdir(name) mkdir(name)
#else
#define my_mkdir(name) mkdir(name, 0700)
#endif

#ifndef STANDALONE
static char shared[FILENAME_MAX];
char pwd[FILENAME_MAX]; // current working dir, init in main / raine.c

char *get_shared(char *name) {
  struct stat buf;
  int ret;
  strcpy(shared,name); // use current path 1st
  ret = stat(shared,&buf);
  if (!ret) {
#ifdef RAINE_WIN32
      char *end;
      GetFullPathName(name,FILENAME_MAX,shared,&end);
#else
      realpath(name,shared);
#endif
      print_debug("get_shared: using direct name access %s\n",shared);
      return shared;
  }
#ifdef RAINE_UNIX
  /* Start by looking in the personnal dir (exe_path) */
  snprintf(shared,FILENAME_MAX, "%s%s", dir_cfg.exe_path,name);
  ret = stat(shared,&buf);
  if (!ret) {
    print_debug("get_shared: using personnal %s\n",shared);
    return shared;
  }
  snprintf(shared,FILENAME_MAX,"%sconfig/%s",dir_cfg.exe_path,name);
  ret = stat(shared,&buf);
  if (!ret) {
    print_debug("get_shared: using personnal %s\n",shared);
    return shared;
  }
#endif
  sprintf(shared, "%s%s", dir_cfg.share_path,name);
  ret = stat(shared,&buf);
  if (!ret) {
    print_debug("get_shared: using shared %s\n",shared);
    return shared;
  }
  snprintf(shared,FILENAME_MAX,"%sconfig/%s",dir_cfg.share_path,name);
  ret = stat(shared,&buf);
  if (!ret) {
    print_debug("get_shared: using shared %s\n",shared);
    return shared;
  }
  // Extreme case : when loading a neocd game we chdir to the game's directory
  // so current directory is lost, so we test the initial working directory
  // here... !
  sprintf(shared, "%s" SLASH "%s", pwd,name);
  return shared;
}
#endif

int is_dir(char *name) {
  struct stat buf;
  int ret;
  ret = stat(name,&buf);
  if (!ret)
      return S_ISDIR(buf.st_mode);
  return 0;
}

void mkdir_rwx(const char *name) {
  char str[256];
  // If path is not absolute (relative then)
#ifndef STANDALONE
  if
#ifndef RAINE_UNIX
  (name[1] != ':' && name[0] != *SLASH)
#else
  (name[0] != *SLASH)
#endif
  {
    snprintf(str,256,"%s%s",dir_cfg.exe_path,name);
    my_mkdir(str);
  } else // absolute path, just do it
#endif
    my_mkdir(name);
}

int load_file(char *filename, UINT8 *dest, UINT32 size)
{
   FILE *file_ptr;

   file_ptr = fopen(filename,"rb");

   if(file_ptr){
      fread(dest, 1, size, file_ptr);
      fclose(file_ptr);
      return 1;		// Success
   }
   else{
      return 0;		// Failure
   }
}

int save_file(char *filename, UINT8 *source, UINT32 size)
{
   FILE *file_ptr;

   file_ptr = fopen(filename,"wb");

   if(file_ptr){
      fwrite(source, 1, size, file_ptr);
      fclose(file_ptr);
      return 1;		// Success
   }
   else{
      return 0;		// Failure
   }
}
int size_file(char *filename)
{
    struct stat buff;
    if (stat(filename,&buff)<0)
	buff.st_size = 0;
    return buff.st_size;
}

#ifdef RAINE_DEBUG

void save_debug(char *name, UINT8 *src, UINT32 size, UINT32 mode)
{
   if(debug_mode){
      char str[256];

      if(src){

#if HAVE_68000
         if(mode)
            ByteSwap(src,size);
#endif

         snprintf(str,256,"%sdebug/%s", dir_cfg.exe_path, name);
         save_file(str, src, size);

         print_debug("Debug Save: '%s' saved.\n", name);

      }
      else{

         print_debug("Debug Save: '%s' is NULL.\n", name);

      }

   }

}

#endif

/* Basic file i/o functions */

#if BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN
#error endianess problem (PDP_ENDIAN ?)
#endif

#ifndef NO_GZIP
/*

find a file by filename

*/

int unz_locate_file_name(unzFile file, char *name)
{
	int err;

    	if(!name)
		return UNZ_PARAMERROR;

	err = unzGoToFirstFile(file);

	while (err == UNZ_OK)
	{
		char current[256+1];

		unzGetCurrentFileInfo(file,NULL,current,256,NULL,0,NULL,0);

		if(!unzStringFileNameCompare(current,name,2))
			return UNZ_OK;
		char *base = strrchr(current,'/');
		if (base) {
		    base++;
		    if(!unzStringFileNameCompare(base,name,2))
			return UNZ_OK;
		}

		err = unzGoToNextFile(file);
	}

	return err;
}

/*

find a file by crc32

*/

int unz_locate_file_crc32(unzFile file, UINT32 crc32)
{
	int err;

	if (!crc32)
		return UNZ_PARAMERROR;

	err = unzGoToFirstFile(file);

	while (err == UNZ_OK)
	{
		unz_file_info file_info;

		unzGetCurrentFileInfo(file,&file_info,NULL,0,NULL,0,NULL,0);

		if (file_info.crc == crc32 || file_info.crc == ~crc32)
			return UNZ_OK;

		err = unzGoToNextFile(file);
	}

	return err;
}

int mgetl(gzFile file) {
  char nb[8], dest[4];
  gzread(file,nb,4);
#if BYTE_ORDER == LITTLE_ENDIAN
  dest[0] = nb[3];
  dest[1] = nb[2];
  dest[2] = nb[1];
  dest[3] = nb[0];
  return *((int *)dest);
#else
  return *((int *)nb);
#endif
}

void mputl(int nb, gzFile file) {
  // this time no trick, we have to convert the number...
#if BYTE_ORDER == LITTLE_ENDIAN
  // We are on an intel cpu, we have to swap everything !
  char dest[4];
  char *snb = (char*)&nb;
  dest[0] = snb[3];
  dest[1] = snb[2];
  dest[2] = snb[1];
  dest[3] = snb[0];
  gzwrite(file,dest,4);
#else
  gzwrite(file,&nb,4);
#endif
}

int igetl(gzFile file) {
  int nb = 0;
  gzread(file,&nb,4);
#if BYTE_ORDER == BIG_ENDIAN
  char dest[4];
  char *snb = (char*)&nb;
  dest[0] = snb[3];
  dest[1] = snb[2];
  dest[2] = snb[1];
  dest[3] = snb[0];
  return *((int *)dest);
#endif
  return nb;
}

int igetw(gzFile file) {
  int nb = 0;
  gzread(file,&nb,2);
#if BYTE_ORDER == BIG_ENDIAN
  char dest[4];
  char *snb = (char*)&nb;
  dest[0] = snb[1];
  dest[1] = snb[0];
  dest[2] = dest[3] = 0;
  return *((int *)dest);
#endif
  return nb;
}

void iputl(int nb, gzFile file) {
  // The opposite of mputl -> swap if BIG ENDIAN
#if BYTE_ORDER == BIG_ENDIAN
  // We are on an intel cpu, we have to swap everything !
  char dest[4];
  char *snb = (char*)&nb;
  dest[0] = snb[3];
  dest[1] = snb[2];
  dest[2] = snb[1];
  dest[3] = snb[0];
  gzwrite(file,dest,4);
#else
  gzwrite(file,&nb,4);
#endif
}

void iputw(int nb, gzFile file) {
  // The opposite of mputl -> swap if BIG ENDIAN
  // on 2 bytes this time
#if BYTE_ORDER == BIG_ENDIAN
  // We are on an intel cpu, we have to swap everything !
  char dest[4];
  char *snb = (char*)&nb;
  dest[0] = snb[1];
  dest[1] = snb[0];
  gzwrite(file,dest,2);
#else
  gzwrite(file,&nb,2);
#endif
}

UINT8 *remaining_b;
int remaining_size;

int load_zipped(char *zipfile, char *name, unsigned int size, int crc32, UINT8 *dest, int actual_load)
{
   unzFile uf;
   int err;

   uf = unzOpen(zipfile);

   if(!uf)			// Fail: Unable to find/open zipfile
      return 0;

   err = unz_locate_file_crc32(uf,crc32);
   if(err!=UNZ_OK){
      print_debug("unz_locate_file_crc32(): Error #%d\nNow trying with file name...\n",err);
      // unzClose(uf);

      // uf = unzOpen(zipfile);

      if(!uf)			// Fail: Unable to find/open zipfile
         return 0;

      err = unz_locate_file_name(uf,name);
      if(err!=UNZ_OK){
         print_debug("unz_locate_file_name(): Error #%d\nNow giving up...\n",err);
         unzClose(uf);
         return 0;		// Fail: File not in zip
      } else if (crc32) { // found by name, but not by crc...
	// if given crc is 0, then we don't know about crc !
	load_error |= LOAD_WARNING;

	if (load_debug)
	  sprintf(load_debug+strlen(load_debug),
		  _("Bad CRC for ROM %s (%x)\n"),name,crc32);
      }
   }

   unz_file_info info;
   unzGetCurrentFileInfo(uf,&info,NULL,0,NULL,0,NULL,0);
   if (!actual_load) {
     if (info.uncompressed_size < size) {
       load_error |= LOAD_WARNING;

       if (load_debug)
	 sprintf(load_debug+strlen(load_debug),
	     _("Bad rom size for %s: tried to read %xh bytes, got %lxh\n"),name,size,info.uncompressed_size);
     }
     unzClose(uf);
     return -1;
   }

   err = unzOpenCurrentFile(uf);
   if(err!=UNZ_OK){
      print_debug("unzOpenCurrentFile(): Error #%d\n",err);
      unzCloseCurrentFile(uf);	// Is this needed when open failed?
      unzClose(uf);
      return 0;			// Fail: Something internal
   }

   err = unzReadCurrentFile(uf,dest,size);
   if(err<0){
      print_debug("unzReadCurrentFile(): Error #%d\n",err);
      unzCloseCurrentFile(uf);
      unzClose(uf);
      return 0;			// Fail: Something internal
   }

   if (err < (signed int)size) {
     load_error |= LOAD_WARNING;

     if (load_debug)
       sprintf(load_debug+strlen(load_debug),
	       _("Bad rom size for %s: tried to read %xh bytes, got %xh\n"),name,size,err);
   }

   if (size < info.uncompressed_size && err == size) {
       if (remaining_b) {
	   FreeMem(remaining_b);
	   remaining_b = NULL;
       }
       remaining_size = info.uncompressed_size - size;
       remaining_b = AllocateMem(remaining_size);
       err = unzReadCurrentFile(uf,remaining_b,remaining_size);
   } else if (remaining_b) {
       FreeMem(remaining_b);
       remaining_size = 0;
       remaining_b = NULL;
   }

   err = unzCloseCurrentFile(uf);
   if(err!=UNZ_OK){
      print_debug("unzCloseCurrentFile(): Error #%d\n",err);
      unzClose(uf);
      load_error |= LOAD_WARNING;

      if (load_debug)
	sprintf(load_debug+strlen(load_debug),
		_("ZIP file damaged for ROM %s\n"),name);
      return -1;		// Clean up Failed: Something internal
   }

   unzClose(uf);
   return -1;
}

int load_zipped_part(char *zipfile, char *name, unsigned int offset, unsigned int size, UINT8 *dest)
{
  static unzFile uf;
  int err;

  if (!offset) {
    uf = unzOpen(zipfile);

    if(!uf)			// Fail: Unable to find/open zipfile
      return 0;

    err = unz_locate_file_name(uf,name);
    if(err!=UNZ_OK){
      print_debug("unz_locate_file_name(): Error #%d\nNow giving up...\n",err);
      unzClose(uf);
      return 0;		// Fail: File not in zip
    }

    if (!uf) return 0;

    err = unzOpenCurrentFile(uf);
    if(err!=UNZ_OK){
      print_debug("unzOpenCurrentFile(): Error #%d\n",err);
      unzCloseCurrentFile(uf);	// Is this needed when open failed?
      unzClose(uf);
      uf = NULL;
      return 0;			// Fail: Something internal
    }
  }

  /* Notice : I couldn't find a function to read from a file in a zip starting
   * at a given offset, so I have changed my mind, offset is just used to
   * read incrementaly, ignoring the exact value of offset... */

  err = unzReadCurrentFile(uf,dest,size);
  if(err<0){
    print_debug("unzReadCurrentFile(): Error #%d\n",err);
    unzCloseCurrentFile(uf);
    unzClose(uf);
    uf = NULL;
    return 0;			// Fail: Something internal
  }

  if (unzeof(uf)) {
    print_debug("load_zipped_part: eof on %s\n",name);
    err = unzCloseCurrentFile(uf);
    if(err!=UNZ_OK){
      print_debug("unzCloseCurrentFile(): Error #%d\n",err);
      unzClose(uf);
      load_error |= LOAD_WARNING;

      if (load_debug)
	sprintf(load_debug+strlen(load_debug),
	    _("ZIP file damaged for ROM %s\n"),name);
      return -1;		// Clean up Failed: Something internal
    }

    unzClose(uf);
    return 1;
  }
  return -1;
}

int size_zipped(char *zipfile, char *name, int crc32)
{
   unzFile uf;
   unz_file_info file_info;
   int err;

   uf = unzOpen(zipfile);

   if(!uf)			// Fail: Unable to find/open zipfile
      return size_file(name);

   if (crc32)
     err = unz_locate_file_crc32(uf,crc32);
   else
     err = -1;
   if(err!=UNZ_OK){
      print_debug("unz_locate_file_crc32(): Error #%d\nNow trying with file name...\n",err);
      if (crc32) {
	unzClose(uf);

	uf = unzOpen(zipfile);
      }

      if(!uf)			// Fail: Unable to find/open zipfile
         return 0;

      err = unz_locate_file_name(uf,name);
      if(err!=UNZ_OK){
         print_debug("unz_locate_file_name(): Error #%d\nNow giving up...\n",err);
         unzClose(uf);
         return 0;		// Fail: File not in zip
      }
   }

   err = unzGetCurrentFileInfo(uf,&file_info,NULL,0,NULL,0,NULL,0);
   if(err!=UNZ_OK){
      print_debug("unzGetCurrentFileInfo(): Error #%d\n",err);
      unzClose(uf);
      return 0;			// Fail: Something internal
   }

   unzClose(uf);

   if( file_info.uncompressed_size > 0 )
      return file_info.uncompressed_size;
   else
      return 0;
}
#endif

int myfgets(char *buff, int size, FILE *f) {
  fgets(buff,size,f);
  int len = strlen(buff);
  while (len > 0 && buff[len-1] < 32 && buff[len-1] > 0)
    buff[--len] = 0;
  return len;
}

void backslash(char *s)
{
#ifndef RAINE_UNIX
  while(*s){

      if(*s == '/')

	 *s = '\\';

      s ++;
   }
#endif
}



