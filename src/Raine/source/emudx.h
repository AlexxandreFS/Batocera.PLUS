#ifndef __EMUDX_H
#define __EMUDX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "unzip.h"

typedef unzFile emudx_file;
char *exists_emudx_file(const char *db_filename);
emudx_file open_emudx_file(const char *name);

void close_emudx(emudx_file dat);
BITMAP *emudx_bitmap(emudx_file dat, int nb);

void load_emudx(const char *name, int tiles, int sprites,
		int start_sprites32, int sprites32, int first_char, int last_char,
		int width, int height,
		int transp,void (*draw_emudx)());
void free_emudx();

extern BITMAP **emudx_tiles;
extern UINT8 *emudx_sprites,*emudx_sprites32,*emudx_chars;
extern UINT32 emudx_nb_tiles,emudx_transp;

#define set_emudx_password() packfile_password("pacsass")


#ifdef __cplusplus
}
#endif

#endif
