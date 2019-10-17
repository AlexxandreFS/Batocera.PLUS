#include <zlib.h>
#include "raine.h"
#ifdef RAINE_DOS
#include "alleg/gui/rgui.h"
#else
#include "sdl/dialogs/messagebox.h"
#endif

/* Extremely simplified iso image handling, can handle only files in the
 * root directory (I don't need anything else !) */

static struct {
    void* (*open)(char *name,char *mode);
    int (*seek)(void *f,long offset, int whence);
    size_t (*read)(void *ptr, size_t size, size_t nmemb, void *stream);
    int (*close)(void *f);
} isof;

int iso_sector_size;

int gzread_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    return gzread(stream,ptr,size*nmemb); // return value never tested anyway
}

static FILE *last_file;

void init_iso() {
    if (last_file) {
	isof.close(last_file);
	last_file = NULL;
    }
    isof.open = (void*)&fopen;
    isof.seek = (void*)&fseek;
    isof.read = (void*)&fread;
    isof.close = (void*)&fclose;
}

void init_iso_gz() {
    if (last_file) {
	isof.close(last_file);
	last_file = NULL;
    }
    isof.open = (void*)&gzopen;
    isof.seek = (void*)&gzseek;
    isof.read = (void*)&gzread_callback;
    isof.close = (void*)gzclose;
}

static void myfseek(FILE *f, int pos, int where) {
  isof.seek(f,pos,where);
  if (iso_sector_size == 2352) {
    isof.seek(f,0x10,SEEK_CUR);
  }
}

static char last_name[FILENAME_MAX];
// gz reads are extremely slow if we seek all the time because the buffer
// becomes useless. So we must at least make a dir cache to avoid to read
// the root dir all the time
typedef struct {
    char name[20];
    int location,size;
} tcache;
static tcache *dir;
static int nb_alloc, nb;

static FILE *myopen(char *iso,char *mode) {
    FILE *f;
    if (!strcmp(last_name,iso) && last_file)
	f = last_file;
    else {
	if (last_file) isof.close(last_file);
	if (dir) free(dir);
	dir = NULL;
	nb_alloc = nb = 0;
	f = isof.open(iso,"rb");
	strcpy(last_name,iso);
	last_file = f;
    }
    return f;
}

static int find_file(char *iso, char *filename, int *size, int *start) {
  FILE *f = myopen(iso,"rb");
  if (!f) {
    char msg[256];
    sprintf(msg,_("Couldn't open iso file:|%s"),iso);
    MessageBox(gettext("Error"),msg,gettext("Ok"));
    return 0;
  }
  if (!dir) {
      myfseek(f,iso_sector_size*0x10 + 0x9e,SEEK_SET);
      int root_dir = 0;
      isof.read(&root_dir,1,4,f);
      myfseek(f,root_dir * iso_sector_size, SEEK_SET);
      unsigned char buff[2048];
      isof.read(buff,2048,1,f);
      unsigned char *ptr = buff;
      int len_record;
      int len_dir = 0;
      do {
	  len_record = *ptr;
	  if (len_record == 0 && len_dir > 0) {
	      if (iso_sector_size > 2048)
		  isof.seek(f,iso_sector_size - 2048, SEEK_CUR);
	      isof.read(buff,2048,1,f);
	      len_dir -= 2048;
	      if (len_dir) {
		  ptr = buff;
		  len_record = *ptr;
	      }
	  }
	  if (len_record) {
	      // int len_ext = ptr[1];
	      int location = *((int *)&ptr[2]);
	      int len_file = *((int *)&ptr[10]);
	      int file_type = ptr[25];
	      int len_name = ptr[32];
	      char name[40];
	      memcpy(name,&ptr[33],len_name);
	      name[len_name] = 0;
	      char *s = strchr(name,';'); // extension iso : ; + number
	      if (s)
		  *s = 0;
	      // printf("%s len %d location %x\n",name,len_file,location);
	      if (!name[0] && len_file && !len_dir) {
		  len_dir = len_file;
		  // printf("init len_dir %d\n",len_dir);
	      } else if (file_type != 2) {
		  if (nb >= nb_alloc) {
		      nb_alloc += 10;
		      dir = realloc(dir,sizeof(tcache)*nb_alloc);
		      if (!dir) {
			  printf("find_file: allocation error\n");
			  return 0;
		      }
		  }
		  dir[nb].size = len_file;
		  dir[nb].location = location;
		  strncpy(dir[nb].name,name,20);
		  dir[nb].name[19] = 0;
		  nb++;
	      }
	  }
	  ptr += len_record;
      } while (len_record);
  }
  int n;
  int found = 0;
  for (n=0; n<nb; n++)
      if (!stricmp(dir[n].name,filename)) {
	  *size = dir[n].size;
	  *start = dir[n].location;
	  found = 1;
	  break;
      }
  if (!found) {
    print_debug("could not find %s in iso\n",filename);
  }
  return found;
}

int iso_size(char *iso, char *name) {
  int len, location;
  if (find_file(iso,name,&len,&location))
    return len;
  return 0;
}

int load_from_iso(char *iso, char *name, unsigned char *dest, int offset, int size) {
  int chunk = 0;
  if (iso_sector_size > 2048 && offset) {
    // add the number of crc areas crossed
    chunk = offset % 2048;
    offset += (offset/2048)*(iso_sector_size-2048);
  }
  int len, location;
  if (find_file(iso, name, &len, &location)) {
    FILE *f = myopen(iso,"rb");
    myfseek(f,location * iso_sector_size + offset, SEEK_SET);
    if (iso_sector_size > 2048) {
      while (size > 0) {
	if (offset) {
	  /* We must stop at 2048 boundaries, after it's just crc code... */
	  offset = 0;
	  chunk = (size > 2048-chunk ? 2048-chunk : size);
	} else
	  chunk = (size > 2048 ? 2048 : size);
	isof.read(dest,1,chunk,f);
	size -= chunk;
	isof.seek(f,iso_sector_size - 2048 , SEEK_CUR);
	dest += chunk;
      }
    } else
      isof.read(dest,1,size,f);
    return 1;
  }
  return 0;
}

