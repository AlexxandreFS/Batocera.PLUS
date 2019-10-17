#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raine.h"
#include "neocd.h"
#include "cache.h"
#include "cdrom.h"
#include "sasound.h"
#include "savegame.h"
#include "newmem.h"
#include "files.h"
#include "starhelp.h"
#include "ingame.h"
#include "games.h"

#ifdef PSP
#define printf	pspDebugScreenPrintf
#endif

typedef struct {
  char name[15];
  unsigned int offset, len, crc;
} file_entry;

static file_entry *cache[7];
static int used[7];
static int max[7];

void get_cache_origin(int type, int offset, char **name, int *nb) {
  if (cache[type]) {
    file_entry *list = cache[type];
    int n = 0;
    while (n < used[type] && list[n].offset+list[n].len < offset)
      n++;
    if (list[n].offset < offset && list[n].offset+list[n].len > offset) {
      *name = list[n].name;
      *nb = offset-list[n].offset;
    }
  }
}

static UINT8 *get_src(int type, int offset) {
  switch(type) {
    case PRG_TYPE: return RAM + offset; break;
    case Z80_TYPE: return Z80ROM + offset; break;
    case FIX_TYPE: return neogeo_fix_memory + offset; break;
    case SPR_TYPE: return GFX + offset; break;
    case PCM_TYPE: return PCMROM + offset; break;
  }
  return NULL;
}

void put_override(int type, char *name, UINT32 size_msg) {
  if (cache[type]) {
    file_entry *list = cache[type];
    int n = 0;
    while (n < used[type] && strcasecmp(list[n].name,name))
      n++;
    if (n< used[type]) { // found
      char *filename = get_override(name);
      sprintf(filename,"%soverride", dir_cfg.exe_path);
      mkdir_rwx(filename);
      sprintf(&filename[strlen(filename)],SLASH "%s", current_game->main_name);
      mkdir_rwx(filename);
      sprintf(&filename[strlen(filename)],SLASH "%s", name);
      UINT8 *src = get_src(type,list[n].offset);
      if (type == PRG_TYPE)
        ByteSwap(src,list[n].len);
      print_debug("write %s len %d\n",list[n].name,list[n].len);
      if (!strncmp(list[n].name,"msg",3) && size_msg) {
	  printf("size changed from %d to %d for %s\n",list[n].len,size_msg,
		  filename);
	  list[n].len = size_msg;
      }
      FILE *f = fopen(filename,"wb");
      fwrite(src,1,list[n].len,f);
      fclose(f);
      if (type == PRG_TYPE)
        ByteSwap(src,list[n].len);
    }
  }
}

// find a prg loaded whose name starts by spec, usefull for ssrpg
// if the name passed is != "" then the search starts at that name
// returns 1 if found something, with name, offset and len initialized
int find_spec(char *spec, char *name, UINT32 *offset, UINT32 *size) {
    file_entry *list = cache[PRG_TYPE];
    int n=0;
    if (*name) {
	for (;n < used[PRG_TYPE] && strcmp(list[n].name,name); n++);
	n++;
    }
    int len_spec = strlen(spec);
    while (n < used[PRG_TYPE]) {
	if (!strncmp(list[n].name,spec,len_spec)) {
	    strcpy(name,list[n].name);
	    *offset = list[n].offset;
	    *size = list[n].len;
	    return 1;
	}
	n++;
    }
    return 0;
}

char *get_override(char *name) {
    static char filename[1024];
    snprintf(filename,1024,"%s/override/%s/%s",dir_cfg.exe_path,
	    current_game->main_name,name);
    return filename;
}

void restore_override(int all) {
    file_entry *list = cache[PRG_TYPE];
    int n;
    for (n=0;n < used[PRG_TYPE]; n++) {
	char *fn = get_override(list[n].name);
	int size = size_file(fn);
	if (!size) continue;
	if (size != list[n].len && strncmp(list[n].name,"msg",3)) {
	    printf("list: %s %x size_file %x\n",list[n].name,list[n].len,size);
	    exit(1);
	}
	FILE *f = fopen(fn,"rb");
	if (!f) continue;
	fread(RAM + list[n].offset,1,size,f);
	fclose(f);
	ByteSwap(&RAM[list[n].offset],size);
	print_debug("restore_override: %s,%x, size %d\n",fn,list[n].offset,size);
	cache_set_crc(list[n].offset,size,PRG_TYPE);
	int Offset = list[n].offset;
	if (Offset <= 0x68 && Offset +size >= 0x6c) {
	    // irq2 overwriten, kof96 neocd collection is the only known game to do
	    // this !!!
	    WriteLongSc(&RAM[0x10f6ee],ReadLongSc(&RAM[0x68]));
	    print_debug("saving irq2 after load prg over it (%x)\n",ReadLongSc(&RAM[0x68]));
	}
    }
    if (!all) return;
    list = cache[SPR_TYPE];
    for (n=0;n < used[SPR_TYPE]; n++) {
	char *fn = get_override(list[n].name);
	int size = size_file(fn);
	if (!size) continue;
	if (size != list[n].len) {
	    printf("list: %s %x size_file %x\n",list[n].name,list[n].len,size);
	    exit(1);
	}
	FILE *f = fopen(fn,"rb");
	if (!f) continue;
	fread(GFX + list[n].offset,1,size,f);
	fclose(f);
	print_debug("restore_override: %s,%x, size %d\n",fn,list[n].offset,size);
	cache_set_crc(list[n].offset,size,SPR_TYPE);
	update_spr_usage(list[n].offset,size);
    }
}

int file_cache(char *filename, int offset, int size,int type) {
    int use;
    char *s = strrchr(filename,'/');
    if (s)
	filename = s+1; // no path here !

#ifdef DEBUG_CACHE
    if (type == 2)
	printf("looking for %s offset %x size %x\n",filename,offset,size);
#endif

    if (cache[type]) {
	file_entry *list = cache[type];
	int n = 0;
	while (n < used[type] && list[n].offset < offset)
	    n++;
	if (n>0 && list[n-1].offset + list[n-1].len == offset &&
		!strcmp(list[n-1].name,filename)) { // concat
	    // works well with upload of course !
	    list[n-1].len += size;
	    return 0;
	}

	if (n == used[type]) { // reached the end of list
	    use = used[type]++;
	    if (used[type] >= max[type]) {
		// I use >= on purpose because I want more room for an eventual insertion
		// see memmove further
		max[type]+=32;
		cache[type] = realloc(cache[type],sizeof(file_entry)*max[type]);
	    }
	} else { // found an offset >= this one
	    int end;
	    if (n < used[type] && list[n].offset == offset && list[n].len == size &&
		    !strcmp(list[n].name,filename)) {
		// already have it !
		int old_crc = list[n].crc;
		// printf("!!! already have it !!!\n");
		/* Since this one is going to be reloaded, we remove the ones
		 * overwriten just after it */
		n++;
		end = offset+size;
		while (n < used[type] && list[n].offset >= offset && list[n].offset < end) {
		    /* We don't test the end here. The idea is that a new file overwrites
		     * the start of an old one. In this case we consider the whole old
		     * file to be bad... */
#ifdef DEBUG_CACHE
		    if (type == 2) {
			printf("remove %s %x %x\n",list[n].name,list[n].offset,list[n].len);
		    }
#endif
		    memmove(&list[n],&list[n+1],sizeof(file_entry)*(used[type]-(n+1)));
		    used[type]--;
		}

		n--;
		cache_set_crc(offset,size,type);
		if (list[n].crc != old_crc) {
		    print_debug("cache: %s: crc differ (%x & %x)\n",filename,old_crc,list[n].crc);
		    return 0;
		}
		print_debug("cache: %s: same crc %x\n",filename,old_crc);
		/* Carefull here, there were tons of bugs in the cache,
		 * returning 1 here can be dangerous these bugs are often
		 * hard to find !
		 * Returning 0 obliges to reload the same data, but since
		 * returning 1 doesn't give any speed boost at least on pc,
		 * I'll return 0 for now. */
		return 0;
	    }
	    end = offset+size;

	    // remove those which are overwriten (if there are some)
	    // We also remove the ones partially overwritten, because I don't think
	    // the neocd would keep accessing some data partially overwritten
	    // and it will make the cache handling much easier
	    while (n < used[type] && list[n].offset >= offset && list[n].offset < end) {
#ifdef DEBUG_CACHE
		if (type == 2) {
		    printf("remove %s %x %x\n",list[n].name,list[n].offset,list[n].len);
		}
#endif
		memmove(&list[n],&list[n+1],sizeof(file_entry)*(used[type]-(n+1)));
		used[type]--;
	    }
	    // otherwise insertion needed at this place
	    if (n < used[type]) {
#ifdef DEBUG_CACHE
		if (type == 2)
		    printf("insertion before %s %x %x\n",list[n].name,list[n].offset,list[n].len);
#endif
		memmove(&list[n+1],&list[n],(used[type]-n)*sizeof(file_entry));
	    }
	    use = n;
	    used[type]++;
	    if (used[type] >= max[type]) {
		max[type]+=32;
		cache[type] = realloc(cache[type],sizeof(file_entry)*max[type]);
	    }
	}
    } else { // first allocation
	if (!max[type])
	    max[type] = 32;
	cache[type] = malloc(sizeof(file_entry)*max[type]);
	used[type] = 1;
	use = 0;
    }
    strcpy(cache[type][use].name,filename);
    cache[type][use].offset = offset;
    cache[type][use].len = size;
    return 0; // not already cached, new file
}

  int get_used(int type) {
    if (type < 7)
      return used[type];
    return -1;
  }

void cache_set_crc(int offset,int size,int type) {
    return; // disabled for now
  /* The problem of neocd is that everything is loaded in ram, which means that it can
     be changed dynamically after it's loaded. Most of the time this is only changed
     by accessing the upload area so we could probably only test the upload area.
     But the 68k and z80 prg memory, can be changed directly or with some patches
     for the z80. So the best way is to add a crc */
  if (cache[type]) {
    file_entry *list = cache[type];
    int n = 0;
    UINT8 *src=NULL,*end;
    unsigned int crc;

    while (n < used[type] && (list[n].offset != offset))
      n++;

    /* Normally this function is called AFTER file_cache, which means that this loop
       will always find the correct file in the cache, we just need to compute the crc
       here */
    if (list[n].len != size) {
	printf("cache_set_crc: size change from %x to %x\n",list[n].len,size);
	list[n].len = size;
    }

    switch(type) {
      case PRG_TYPE: src= RAM + offset; end = RAM+0x200000; break;
      case Z80_TYPE: src= Z80ROM + offset; end = Z80ROM+0x10000; break;
      case FIX_TYPE: src= neogeo_fix_memory + offset;
		     end = neogeo_fix_memory+0x20000; break;
      case SPR_TYPE: src= GFX + offset; end = GFX+0x800000; break;
      case PCM_TYPE: src= PCMROM + offset; end = PCMROM+0x100000; break;
    }

    crc = 0;
    /* If the size is not a multiple of 4, then we loose precision, a few bytes are
       ignored at the end of the file. Oh well it should be enough just to check
       if an area has changed anyway... ! */
    do {
      crc += *((int *)src); // an xor here loops on 0 if the rom is filled
      // with the same value... a simple add should be safer (avoid complexity)
      size -= 4;
      src += 4;
      if (src >= end) {
	  switch(type) {
	  case PRG_TYPE: src= RAM ; break;
	  case Z80_TYPE: src= Z80ROM;  break;
	  case FIX_TYPE: src= neogeo_fix_memory; break;
	  case SPR_TYPE: src= GFX; break;
	  case PCM_TYPE: src= PCMROM; break;
	  }
      }
    } while (size>=4);
    list[n].crc = crc;
  }
}

static int nb_upload, used_upload = 0,*upload_offset,*upload_size;

void clear_file_cache() {
  int n;
  for (n=0; n<7; n++) {
    if (cache[n]) {
      free(cache[n]);
      cache[n] = NULL;
      used[n] = 0;
      max[n] = 32;
    }
  }
  if (upload_offset) {
	  free(upload_offset);
	  upload_offset = NULL;
  }
  if (upload_size) {
	  free(upload_size);
	  upload_size = NULL;
  }
  used_upload = 0;
}

static UINT8 *fill_upload(UINT8 *buff, int *len, int type)
{
	int old_cd = cdrom_speed;
	nb_upload = 0;
	file_entry *tcache = (file_entry *)buff;
	cdrom_speed = 0;
	while (*len > 0) {
		if (!strcmp(tcache->name,"upload")) {
			if (nb_upload == used_upload) {
				used_upload += 20;
				upload_offset = realloc(upload_offset,sizeof(int)*used_upload);
				upload_size = realloc(upload_size,sizeof(int)*used_upload);
			}
			if (upload_offset && upload_size) {
				upload_offset[nb_upload] = tcache->offset;
				upload_size[nb_upload++] = tcache->len;
			}
			*len -= tcache->len;
		} else {
			switch(type) {
			case SPR_TYPE:
				neogeo_cdrom_load_spr_file(tcache->name, tcache->offset/2);
				break;
			case FIX_TYPE:
				neogeo_cdrom_load_fix_file(tcache->name, tcache->offset); break;
			case PCM_TYPE:
				neogeo_cdrom_load_pcm_file(tcache->name, tcache->offset); break;
			default:
				printf("unknown type passed to fill_upload\n");
				exit(1);
			}
		}
		tcache++;
		*len -= sizeof(file_entry);
	}
	cdrom_speed = old_cd;
	return (UINT8*)tcache;
}

static void cache_load_spr(UINT8 *buff, int len) {
  /* Actually the cache isn't directly loaded from the savegame, we use
   * the filenames and uploads areas from the savegame and feed them directly
   * to the existing cache which existed before the load */
  buff = fill_upload(buff,&len,SPR_TYPE);
  int n;
  for (n = 0; n<nb_upload; n++) {
	  print_debug("restoring spr upload %x,%x\n",upload_offset[n],
			  upload_size[n]);
	  memcpy(GFX+upload_offset[n],buff,upload_size[n]);
	  UINT8 *usage_ptr = video_spr_usage + (upload_offset[n]>>8);
	  int i;
	  for (i=0; i<upload_size[n]; i+= 256) {
		  int res = 0;
		  int j;
		  for (j=0; j<256; j++) {
			  if (buff[i+j])
				  res++;
		  }
		  if (res == 0) // all transp
			  usage_ptr[i/256] = 0;
		  else if (res == 256)
			  usage_ptr[i/256] = 2; // all solid
		  else
			  usage_ptr[i/256] = 1; // semi
	  }
	  buff += upload_size[n];
  }
}

static void cache_save_spr(UINT8 **buff, int *len) {
  int upload_size = 0;
  int n;
  for (n=0; n<used[SPR_TYPE]; n++) {
    if (!strcmp(cache[SPR_TYPE][n].name,"upload")) {
      upload_size += cache[SPR_TYPE][n].len;
    }
  }
  *len = used[SPR_TYPE]*sizeof(file_entry);
  *buff = AllocateMem(*len + upload_size);
  memcpy(*buff,cache[SPR_TYPE],*len);
  if (upload_size) {
    UINT8 *tmp = *buff + *len;
    for (n=0; n<used[SPR_TYPE]; n++) {
      if (!strcmp(cache[SPR_TYPE][n].name,"upload")) {
	memcpy(tmp,GFX + cache[SPR_TYPE][n].offset,cache[SPR_TYPE][n].len);
	tmp += cache[SPR_TYPE][n].len;
      }
    }
  }
  *len += upload_size;
}

static void cache_load_fix(UINT8 *buff, int len) {
  buff = fill_upload(buff,&len,FIX_TYPE);
  int n;
  for (n = 0; n<nb_upload; n++) {
	  print_debug("restoring fix upload %x,%x\n",upload_offset[n],
			  upload_size[n]);
	  memcpy(neogeo_fix_memory+upload_offset[n],buff,upload_size[n]);
	  UINT8 *usage_ptr = video_fix_usage + (upload_offset[n]>>5);
	  int i;
	  for (i=0; i<upload_size[n]; i+= 64) {
		  int res = 0;
		  int j;
		  for (j=0; j<64; j++) {
			  if (buff[i+j])
				  res++;
		  }
		  if (res == 0) // all transp
			  usage_ptr[i/64] = 0;
		  else if (res == 64)
			  usage_ptr[i/64] = 2; // all solid
		  else
			  usage_ptr[i/64] = 1; // semi
	  }
	  buff += upload_size[n];
  }
}

static void cache_save_fix(UINT8 **buff, int *len) {
  int upload_size = 0;
  int n;
  for (n=0; n<used[FIX_TYPE]; n++) {
    if (!strcmp(cache[FIX_TYPE][n].name,"upload")) {
      upload_size += cache[FIX_TYPE][n].len;
    }
  }
  *len = used[FIX_TYPE]*sizeof(file_entry);
  *buff = AllocateMem(*len + upload_size);
  memcpy(*buff,cache[FIX_TYPE],*len);
  if (upload_size) {
    UINT8 *tmp = *buff + *len;
    for (n=0; n<used[FIX_TYPE]; n++) {
      if (!strcmp(cache[FIX_TYPE][n].name,"upload")) {
	memcpy(tmp,neogeo_fix_memory + cache[FIX_TYPE][n].offset,cache[FIX_TYPE][n].len);
	tmp += cache[FIX_TYPE][n].len;
      }
    }
  }
  *len += upload_size;
}

static void cache_load_pcm(UINT8 *buff, int len) {
  buff = fill_upload(buff,&len,PCM_TYPE);
  int n;
  for (n = 0; n<nb_upload; n++) {
	  print_debug("restoring pcm upload %x,%x\n",upload_offset[n],
			  upload_size[n]);
	  memcpy(PCMROM+upload_offset[n],buff,upload_size[n]);
	  buff += upload_size[n];
  }
}

void cache_save_pcm(UINT8 **buff, int *len) {
  int n;
  int upload_size = 0;
  for (n=0; n<used[PCM_TYPE]; n++) {
    if (!strcmp(cache[PCM_TYPE][n].name,"upload")) {
      upload_size += cache[PCM_TYPE][n].len;
    }
  }
  *len = used[PCM_TYPE]*sizeof(file_entry);
  *buff = AllocateMem(*len + upload_size);
  memcpy(*buff,cache[PCM_TYPE],*len);
  if (upload_size) {
    UINT8 *tmp = *buff + *len;
    for (n=0; n<used[PCM_TYPE]; n++) {
      if (!strcmp(cache[PCM_TYPE][n].name,"upload")) {
	memcpy(tmp,PCMROM + cache[PCM_TYPE][n].offset,cache[PCM_TYPE][n].len);
	tmp += cache[PCM_TYPE][n].len;
      }
    }
  }
  *len += upload_size;
}

// the prg handling is the easiest one because I don't handle uploads there
// I need it only for the translator, so that I am able to find where some
// piece of data comes from
// (it would be cool to be able to save only the ram which isn't directly loaded
// from cd, but it would require not to save directly RAM, which would be messy)
/* Actually it wasn't so easy because of the crcs :
 * when we save the cache, we save the crcs
 * if we restore this area like the others we call file_cache, but never
 * cache_set_crc because we don't know if the file has been overwriten or not.
 * The consequence is that the status of the crc is unknown ! if the same
 * file is loaded after this by the game it will believe the correct crc is
 * the one file_cache has put here : 0 most of the time !!!
 * So the correct way is to import everything into the cache, crcs included,
 * without changing anything to the ram area. */
// #define LOAD
static void cache_load_prg(UINT8 *buff, int len) {
  file_entry *tcache = (file_entry *)buff;
  int old_cd = cdrom_speed;
  cdrom_speed = 0;
  used[PRG_TYPE] = 0;
#ifdef LOAD
  int size = tcache->len;
  UINT8 *tmp = malloc(size);
#endif
  while (len > 0) {
#ifdef LOAD
      if (tcache->len > size) {
	  free(tmp);
	  size = tcache->len;
	  tmp = malloc(size);
      }
      memcpy(tmp,&RAM[tcache->offset],tcache->len);
      printf("on recalcule la taille pour %s,%x\n",tcache->name,tcache->len);
      neogeo_cdrom_load_prg_file(tcache->name, tcache->offset);
      memcpy(&RAM[tcache->offset],tmp,tcache->len);
#else
      // Normally a file_cache call is enough, no need to reload the thing
      /* But the size is obviously wrong in some savegames, so I should fix
       * it first */
      char *fn = get_override(tcache->name);
      tcache->len = size_file(fn);
      file_cache(tcache->name,tcache->offset,tcache->len,PRG_TYPE);
#endif
      tcache++;
      len -= sizeof(file_entry);
  }
#ifdef LOAD
  free(tmp);
#endif
  cdrom_speed = old_cd;
}

void cache_save_prg(UINT8 **buff, int *len) {
  *len = used[PRG_TYPE]*sizeof(file_entry);
  *buff = AllocateMem(*len);
  memcpy(*buff,cache[PRG_TYPE],*len);
}

void prepare_cache_save() {
  AddSaveDynCallbacks(0,cache_load_spr,cache_save_spr);
  AddSaveDynCallbacks(1,cache_load_fix,cache_save_fix);
  AddSaveDynCallbacks(2,cache_load_pcm,cache_save_pcm);
  // Actually it doesn't work for prg, the ram can be changed directly
  // and some programs seem to store their data in the middle of the code
  // so if you save it here, all the data is erased when you restore a
  // savegame !!!
  AddSaveDynCallbacks(3,cache_load_prg,cache_save_prg);
}

