/* Savegame converter, from the allegro format to the 0.50 format */
/* Requires allegro and zlib */

#include <allegro.h>
#include <zlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <utime.h>

/* Basic file i/o functions */

#if BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN
#error endianess problem (PDP_ENDIAN ?)
#endif

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
  
#define SIZE 150000
#define ASCII_ID(a,b,c,d)	  ((a<<24) | (b<<16) | (c<<8) | (d<<0))
#define SAVE_END              ASCII_ID('E','N','D',0x00)
#define SAVE_FILE_TYPE_0      ASCII_ID('J','3','d','!')
#define SAVE_FILE_TYPE_1      ASCII_ID('R','N','E','!')
// TYPE_2 : starting with 0.35 : new mz80 3.4
#define SAVE_FILE_TYPE_2      ASCII_ID('R','N','E','1')

static void convert(char *name) {
  PACKFILE *fin;
  gzFile *fout;

  if(!(fin=pack_fopen(name,F_READ))){
    return;
  }
  
  fout = gzopen("temp.gz","wb9");
  if (!fout) {
    printf("can't create temp.gz !\n");
    exit(1);
  }

  int savegame_version = pack_mgetl(fin);
  if (savegame_version == SAVE_FILE_TYPE_0) {
    printf("%s: too ancient, format not supported anymore !!!\n",name);
    pack_fclose(fin);
    gzclose(fout);
    return;
  } else if (savegame_version != SAVE_FILE_TYPE_1 &&
    savegame_version != SAVE_FILE_TYPE_2) {
      pack_fclose(fin);
      if(!(fin=pack_fopen(name,F_READ_PACKED))){
	gzclose(fout);
	return;
      }
      savegame_version = pack_mgetl(fin);
      if (savegame_version == SAVE_FILE_TYPE_0) {
	printf("%s: too ancient, format not supported anymore !!!\n",name);
	pack_fclose(fin);
	gzclose(fout);
	return;
      } else if (savegame_version != SAVE_FILE_TYPE_1 &&
	  savegame_version != SAVE_FILE_TYPE_2) {

	printf("%s: Format not recognized : %x\n",name,savegame_version);
	pack_fclose(fin);
	gzclose(fout);
	return;
      }
  }
  mputl(savegame_version,fout);

  int t_size = pack_igetl(fin);
  iputl(t_size,fout);

  char *buffer = malloc(SIZE);
  if (!buffer) {
    printf("can't allocate %d bytes\n",SIZE);
    exit(1);
  }

   while (1){

     // read header

     int t_id   = pack_mgetl(fin);
     int t_size = pack_igetl(fin);
     mputl(t_id,fout);
     iputl(t_size,fout);

     if (t_id == SAVE_END) {
       printf("conversion %s ok\n",name);
       break;
     }
     while (t_size > 0) {
       int s = t_size;
       if (s > SIZE)
	 s = SIZE;
       t_size -= s;
       pack_fread(buffer,s,fin);
       gzwrite(fout,buffer,s);
     }
   }
   free(buffer);

   struct stat buf;
   struct utimbuf buf2;

   pack_fclose(fin);
   gzclose(fout);
   stat(name,&buf);
   buf2.actime = buf.st_atime;
   buf2.modtime = buf.st_mtime;
   unlink(name);
   rename("temp.gz",name);
   utime(name,&buf2);
}

int main(int argc, char **argv) {
  int n;
  
  for (n=1; n<argc; n++) {
    convert(argv[n]);
  }
  return 0;
}
