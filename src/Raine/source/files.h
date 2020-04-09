
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                        RAINE FILE ACCESS/ZIP SUPPORT                       */
/*                                                                            */
/******************************************************************************/

#ifndef mkdir_rwx

#include "deftypes.h"
#include "unzip.h"

extern UINT8 *remaining_b;
extern int remaining_size;
extern char pwd[FILENAME_MAX];

void mkdir_rwx(const char *name);
  // returns the correct filename (looks first in the personnal dir, then in the shared
  // system dir).
char *get_shared(char *);
int load_file(char *filename, UINT8 *dest, UINT32 size);
int save_file(char *filename, UINT8 *source, UINT32 size);

// zip files
int unz_locate_file_crc32(unzFile file, UINT32 crc32);
int unz_locate_file_name(unzFile file, char *name);
int size_file(char *filename);
int is_dir(char *name);

#ifdef RAINE_DEBUG

void save_debug(char *name, UINT8 *src, UINT32 size, UINT32 mode);
#else
#define save_debug(name, src, size, mode)
#endif
#endif

int mgetl(gzFile file);
void mputl(int nb, gzFile file);
int igetl(gzFile file);
int igetw(gzFile file);
void iputl(int nb, gzFile file);
void iputw(int nb, gzFile file);
int load_zipped(char *zipfile, char *name, unsigned int size, int crc32, UINT8 *dest, int actual_load);
int size_zipped(char *zipfile, char *name, int crc32);
void backslash(char *s);

int load_zipped_part(char *zipfile, char *name, unsigned int offset, unsigned int size, UINT8 *dest);

#include <stdio.h>
// fgets + strips trailing cr and returns length of string
int myfgets(char *buff, int size, FILE *f);

#ifdef __cplusplus
}
#endif
