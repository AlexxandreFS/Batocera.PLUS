#include <unistd.h> // chdir
#include "raine.h"
#include "starhelp.h" // ByteSwap
#include "sasound.h"
#include <string.h>
#include "neocd.h"
#include "blit.h" // clear_game_screen
#include "files.h"
#include "palette.h"
#include "newspr.h"
#include "cache.h"
#include "profile.h"
#include "cdrom.h"
#include "cdda.h"
#include "dsw.h"
#include "iso.h"
#include "newmem.h"
#include "games.h"
#include "config.h"
#include "display.h"
#ifndef RAINE_DOS
#include "display_sdl.h"
#else
#include <ctype.h>
#include "alleg/gui/rgui.h"
#endif
#include "ingame.h"
#include "7z.h"

// cdrom_speed : used only for the speed of the loading animations
int cdrom_speed;

#define animations_enabled RAM[0x10fddc ^ 1]

void save_cdrom_config() {
  raine_set_config_int("neocd","cdrom_speed",cdrom_speed);
}

void restore_cdrom_config() {
  cdrom_speed = raine_get_config_int("neocd","cdrom_speed",8);
}

static char *exts[] = {"prg","fix","spr","z80","pcm","pat","jue"};

#define COPY_BIT(a, b) { \
    a <<= 1; \
    a |= (b & 0x01); \
    b >>= 1; }

static int extract8(UINT8 *src, UINT8 *dst)
{
  int i;

  unsigned char bh = *src++;
  unsigned char bl = *src++;
  unsigned char ch = *src++;
  unsigned char cl = *src;
  unsigned char al, ah;

  int res = 0;
  for(i = 0; i < 4; i++)
  {
    al = ah = 0;

    COPY_BIT(al, ch)
      COPY_BIT(al, cl)
      COPY_BIT(al, bh)
      COPY_BIT(al, bl)

      COPY_BIT(ah, ch)
      COPY_BIT(ah, cl)
      COPY_BIT(ah, bh)
      COPY_BIT(ah, bl)

      if ((*dst++ = al)) res++;
      if ((*dst++ = ah)) res++;
  }
  return res;
}

void spr_conv(UINT8 *src, UINT8 *dst, int len, unsigned char *usage_ptr)
{
  register int    i;

  if (is_neocd()) {
      UINT32 offset;
      int res = 0;
      for(i=0;i<len;i+=4) {
	  if ((i % 128) == 0 && i) {
	      if (res == 0) // all transp
		  *usage_ptr++ = 0;
	      else if (res == 256)
		  *usage_ptr++ = 2; // all solid
	      else
		  *usage_ptr++ = 1; // semi
	      res = 0;
	  }
	  if((i&0x7f)<64)
	      offset=(i&0xffffff80)+((i&0x7f)<<1)+4;
	  else
	      offset=(i&0xffffff80)+((i&0x7f)<<1)-128;

	  res += extract8(src,dst+offset*2);
	  src+=4;
      }
      if (res == 0) // all transp
	  *usage_ptr++ = 0;
      else if (res == 256)
	  *usage_ptr++ = 2; // all solid
      else
	  *usage_ptr++ = 1; // semi
      return;
  }
  int tileno,nb_sprites = get_region_size(REGION_SPRITES)/128;

  for (tileno = 0;tileno < nb_sprites;tileno++)
  {
      unsigned char swap[128];
      UINT8 *gfxdata;
      int x,y;
      unsigned int pen;

      gfxdata = &load_region[REGION_SPRITES][128 * tileno];

      memcpy(swap,gfxdata,128);

      for (y = 0;y < 16;y++)
      {
	  UINT32 dw;

	  dw = 0;
	  for (x = 0;x < 8;x++)
	  {
	      pen  = ((swap[64 + 4*y + 3] >> x) & 1) << 3;
	      pen |= ((swap[64 + 4*y + 1] >> x) & 1) << 2;
	      pen |= ((swap[64 + 4*y + 2] >> x) & 1) << 1;
	      pen |=	(swap[64 + 4*y	  ] >> x) & 1;
	      dw |= pen << 4*x;
	  }
	  *(gfxdata++) = dw>>0;
	  *(gfxdata++) = dw>>8;
	  *(gfxdata++) = dw>>16;
	  *(gfxdata++) = dw>>24;

	  dw = 0;
	  for (x = 0;x < 8;x++)
	  {
	      pen  = ((swap[4*y + 3] >> x) & 1) << 3;
	      pen |= ((swap[4*y + 1] >> x) & 1) << 2;
	      pen |= ((swap[4*y + 2] >> x) & 1) << 1;
	      pen |=	(swap[4*y	 ] >> x) & 1;
	      dw |= pen << 4*x;
	  }
	  *(gfxdata++) = dw>>0;
	  *(gfxdata++) = dw>>8;
	  *(gfxdata++) = dw>>16;
	  *(gfxdata++) = dw>>24;
      }
  }
  int res = 0;
  for (i=0; i<len; i+=8) {
      if (i%(16*8) == 0 && i) {
	  if (res == 256)
	      *usage_ptr++ = 2;
	  else if (res == 0)
	      *usage_ptr++ = 0;
	  else
	      *usage_ptr++ = 1;
	  res = 0;
      }

      UINT32 mydword = src[0]|(src[1]<<8)|(src[2]<<16)|(src[3]<<24);
      if ((*dst++ = (mydword>>0)&0xf)) res++;
      if ((*dst++ = (mydword>>4)&0xf)) res++;
      if ((*dst++ = (mydword>>8)&0xf)) res++;
      if ((*dst++ = (mydword>>12)&0xf)) res++;
      if ((*dst++ = (mydword>>16)&0xf)) res++;
      if ((*dst++ = (mydword>>20)&0xf)) res++;
      if ((*dst++ = (mydword>>24)&0xf)) res++;
      if ((*dst++ = (mydword>>28)&0xf)) res++;

      mydword = src[4]|(src[5]<<8)|(src[6]<<16)|(src[7]<<24);
      if ((*dst++ = (mydword>>0)&0xf)) res++;
      if ((*dst++ = (mydword>>4)&0xf)) res++;
      if ((*dst++ = (mydword>>8)&0xf)) res++;
      if ((*dst++ = (mydword>>12)&0xf)) res++;
      if ((*dst++ = (mydword>>16)&0xf)) res++;
      if ((*dst++ = (mydword>>20)&0xf)) res++;
      if ((*dst++ = (mydword>>24)&0xf)) res++;
      if ((*dst++ = (mydword>>28)&0xf)) res++;

      src += 8;
  }
}

static int load_type;

int get_cd_load_type() { return load_type; }

int nb_tracks;
static int alloc_tracks;
static char **mp3_track;
static int *indexes,nb_indexes,alloc_indexes;
static char jue[4] = "jue"; // region selection

void get_track_index(int track, int *start, int *end) {
  track -= 2; // track 1 = data, 2 = audio, and array index starts at 0...
  if (track < 0) track = 0; // just to be safe
  if (track < nb_indexes) {
    *start = indexes[track];
    if (track < nb_indexes-1)
      *end = indexes[track+1];
    else
      *end = size_file(neocd_path)/2352;
  } else
    *start = 0;
}

void init_load_type() {
  if (alloc_tracks) {
    int n;
    for (n=0; n<nb_tracks; n++) {
      free(mp3_track[n]);
    }
    free(mp3_track);
    mp3_track = NULL;
  }
  nb_tracks = alloc_tracks = 0;
  nb_indexes = 0;
  if (!stricmp(&neocd_path[strlen(neocd_path)-3],"zip"))
    load_type = ZIP_TYPE;
  if (!stricmp(&neocd_path[strlen(neocd_path)-2],"7z"))
    load_type = P7Z_TYPE;
  else if (!stricmp(&neocd_path[strlen(neocd_path)-3],"txt"))
    load_type = IPL_TYPE;
  else if (!stricmp(&neocd_path[strlen(neocd_path)-3],"cue")) {
    FILE *f = fopen(neocd_path,"r");
    if (f) {
	char cue[FILENAME_MAX];
	strcpy(cue,neocd_path);
	int current_track = 0,last_track = 0;
      while (!feof(f)) {
	char buff[256],orig[256];
	char *s;
	fgets(buff,sizeof(buff),f);
	buff[255] = 0;
	if (!*buff)
	  continue;
	int l = strlen(buff);
	while (buff[l-1] < 32 && l > 0) {
	  buff[l-1] = 0;
	  l--;
	}
	strcpy(orig,buff);

	if (!strncmp(buff,"FILE",4)) {
	    char *start;
	    char *end = strrchr(buff,'"');
	  if (!end) {
	      end = strrchr(buff,' ');
	      if (!end) {
		  char msg[1024];
		  sprintf(msg,_("Serious cue format error on line %s"),orig);
		  MessageBox(gettext("Error"),msg,gettext("OK"));
		  break;
	      }
	      start = buff + 5;
	      while (*start == ' ') start++;
	      *end = 0;
	      end--; // so that end+2 points to binary
	      start--; // so that start+1 points to the beg of filename
	  } else {
	      *end = 0;
	      start = strchr(buff,'"');
	      if (!start) {
		  char msg[1024];
		  sprintf(msg,_("cue format error on line : %s"),orig);
		  MessageBox(gettext("Error"),msg,gettext("OK"));
		  break;
	      }
	  }
	  if (!strncmp(end+2,"BINARY",6)) {
	    char *path = strrchr(neocd_path,SLASH[0]);
	    if (!path) {
	      MessageBox(gettext("Error"),gettext("path format error"),gettext("OK"));
	      break;
	    }
	    strcpy(path+1,start+1);
	    if (!exists(neocd_path)) {
		// 1st thing to try : some lamers distribute rips where they
		// rename all the files without editing the cue file.
		// The only way to find the correct file is to use only
		// the extension and replace the base part of the filename
		// with the one of the cue file !
		// Usually the bin file has the same base filename as the cue
		// file so it's a reasonable assumption.
		char ext[4];
		strcpy(ext,&neocd_path[strlen(neocd_path)-3]);
		strcpy(neocd_path,cue);
		strcpy(&neocd_path[strlen(neocd_path)-3],ext);
	    }
	    if (!exists(neocd_path)) {
		strcat(neocd_path,".gz");
		if (!exists(neocd_path)) {
		    MessageBox(gettext("Error"),gettext("can't find iso file"),gettext("OK"));
		    path[1] = 0;
		    break;
		} else
		    init_iso_gz();
	    } else
		init_iso();
	  } else if (!strncmp(end+2,"MP3",3) || !strncmp(end+2,"WAVE",4)) {
	    if (alloc_tracks == nb_tracks) {
	      alloc_tracks += 10;
	      mp3_track = realloc(mp3_track,alloc_tracks*sizeof(char**));
	      if (!mp3_track) {
		MessageBox(gettext("Error"),gettext("alloc error"),gettext("OK"));
		break;
	      }
	    }
	    int n = nb_tracks;
	    mp3_track[nb_tracks++] = malloc(strlen(start+1)+strlen(neocd_dir)+4); // +1 for the /, +2 for flac instead of wav, +3 for the end 0.
	    sprintf(mp3_track[n],"%s" SLASH "%s",neocd_dir,start+1);
	    if (!exists(mp3_track[n])) {
		char *ext = strrchr(mp3_track[n],'.');
		if (ext) {
		    char *exts[] = { "mp3","ogg","flac", NULL };
		    int x = 0;
		    while (exts[x]) {
			strcpy(ext+1,exts[x]);
			if (exists(mp3_track[n])) break;
			x++;
		    }
		    if (!exts[x]) {
			strcpy(ext+1,"wav");
			print_debug("track %d does not exist : %s\n",n,mp3_track[n]);
		    }
		}
	    }
	    print_debug("adding mp3 track %s\n",mp3_track[n]);
	  } else {
	    char msg[160];
	    sprintf(msg,_("Track format unknown '%s'"),end+2);
	    MessageBox(gettext("Error"),msg,gettext("OK"));
	    break;
	  }
	} else if ((s = strstr(buff,"TRACK "))) {
	    current_track = atoi(s+6);
	    if (current_track == 1) {
		char *slash = strchr(buff,'/');
		if (slash) {
		    iso_sector_size = atoi(slash+1);
		    print_debug("found sector size %d\n",iso_sector_size);
		}
	    }
	} else if ((s = strstr(buff,"INDEX")) && !nb_tracks && current_track > 1) {
	  // found internal audio track
	  int n;
	  if (nb_indexes == alloc_indexes) {
	    indexes = realloc(indexes,(alloc_indexes+10)*sizeof(int));
	    if (!indexes) {
	      MessageBox(gettext("Error"),gettext("indexes alloc error"),gettext("OK"));
	      break;
	    }
	    for (n=alloc_indexes; n<alloc_indexes+10; n++)
	      indexes[n] = 0;
	    alloc_indexes += 10;
	  }
	  int nb_index = atoi(s+6);
	  int mins = atol(s+9);
	  int secs = atol(s+9+3);
	  int frames = atol(s+9+6);
	  // 44100 Hz x 16 bit x stereo -> 44100x4 bytes/s
	  // -> /2352 (sector size in audio format) = 75 sectors /s
	  // so the length translates directly to a number of sector
	  // (if the data track is in mode1/2048 the 1st index for an audio
	  // track still gives the correct sector number)
	  if (nb_index <= 1) {
	      // The rule for the indexes seems to be silence = 2s for
	      // index 0, then index 1 = real beginning.
	      // So if we have index 1 we overwrite the previous index with it
	      // but ignore any eventual other indexes !
	      if (last_track == current_track)
		  nb_indexes--;
	      indexes[nb_indexes++] = frames+75*(secs+60*mins);
	  }
	  last_track = current_track;
	  print_debug("added index %02d:%02d:%02d -> %d\n",mins,secs,frames,indexes[nb_indexes-1]);
	} else if ((s = strstr(buff,"INDEX 01 ")) && nb_tracks) {
	  // found internal audio track
	  int n;
	  if (alloc_indexes < alloc_tracks) {
	    indexes = realloc(indexes,alloc_tracks*sizeof(int));
	    if (!indexes) {
	      MessageBox(gettext("Error"),gettext("indexes alloc error"),gettext("OK"));
	      break;
	    }
	    for (n=alloc_indexes; n<alloc_tracks; n++)
	      indexes[n] = 0;
	    alloc_indexes = alloc_tracks;
	  }
	  int nb_index = atoi(s+6);
	  int mins = atol(s+9);
	  int secs = atol(s+9+3);
	  int frames = atol(s+9+6);
	  // Here we convert all this to ms only (seek in audio file)
	  if (nb_index <= 1)
	      indexes[nb_tracks-1] = (frames*1000/75+(secs+60*mins)*1000)/1000*44100*4;
	  nb_indexes = nb_tracks;
	  print_debug("added index %02d:%02d:%02d -> %d\n",mins,secs,frames,indexes[nb_indexes-1]);
	}
      } // feof
      fclose(f);
      if (!iso_sector_size) {
	MessageBox(gettext("Error"),gettext("Could not determine sector size from\nthe cue file"),gettext("OK"));
      } else {
	if (nb_tracks) { // we MUST chdir to the cue directory in this case !
	  char *path = strrchr(neocd_path,SLASH[0]);
	  // path is defined (checked before)
	  *path = 0;
	  chdir(neocd_path);
	  *path = SLASH[0];
	}
	load_type = CUE_TYPE;
      }
    } else { // if (f)
	char error[4096];
	sprintf(error,_("The file '%s' can't be loaded"),neocd_path);
	MessageBox(gettext("Error"),error,gettext("ok"));
    }
  } else if (!stricmp(&neocd_path[strlen(neocd_path)-3],"iso")) {
    load_type = ISO_TYPE;
    iso_sector_size = 2048;
    init_iso();
  } else if (!stricmp(&neocd_path[strlen(neocd_path)-6],"iso.gz")) {
    load_type = ISO_TYPE;
    iso_sector_size = 2048;
    init_iso_gz();
  }
}

char *get_mp3_track(int n) {
  n-=2;
  if (load_type == CUE_TYPE && n < nb_tracks && n >= 0) {
    if (exists(mp3_track[n]))
      return mp3_track[n];
  }
  return NULL;
}

static int    recon_filetype(char *ext, char *filename)
{
  int n;
  for (n=0; n<sizeof(exts)/sizeof(char*); n++)
    if (!strcmp(ext,exts[n]))
      return n;

  // else try to find the type in the filename !
  for (n=0; n<sizeof(exts)/sizeof(char*); n++)
    if (strstr(filename,exts[n])) {
#ifdef RAINE_DEBUG
	printf("warning: type taken from filename %s\n",filename);
#endif
      return n;
    }

  if (!strcmp(ext,"obj")) {// sprites in art of fighting !!!!
#ifdef RAINE_DEBUG
      printf("warning: aof sprites %s\n",filename);
#endif
    return SPR_TYPE;
  }

  // really nothing to do !
#ifdef RAINE_DEBUG
  /* Neo turf master for example has a se_02.a80 file in its ipl.txt
   * same size and same crc as se_02.z80. It's very probably an error, the file
   * seems to be ignored by the original hw, and the correct one (.z80) loaded
   * later */
  printf("file type not recognized : %s\n",filename);
#endif
  return    -1;
}

int get_size(char *filename) {
    int size;
    // 1st check override
    size = size_file(get_override(filename));
    if (size) {
	int type = recon_filetype(&filename[strlen(filename)-3],filename);
	if (type == SPR_TYPE)
	    size /= 2;
	return size;
    }
    switch(load_type) {
	case ZIP_TYPE: size = size_zipped(neocd_path,filename,0); break;
	case P7Z_TYPE: size = load_7z(neocd_path,filename,0,0,0,NULL,0); break;
	case IPL_TYPE:
		       if (!strchr(filename,SLASH[0])) {
			   char file[1024];
			   sprintf(file,"%s%s%s",neocd_dir,SLASH,filename);
			   size = size_file(file);
			   break;
		       }
		       size = size_file(filename);
		       break;
	default:
		       // iso, cue
		       size = iso_size(neocd_path,filename);
    }
    return size;
}

static int check_offset;

static int check_screen_data(int offset, int type) {
  UINT32 data_offset;
  int data_type;

  check_offset = offset;

  do
  {
    data_type = ReadLongSc(&RAM[check_offset]);
    check_offset += 4;

    data_offset = ReadLongSc(&RAM[check_offset]);
    check_offset += 4;

    if (data_type == type + 1)
      return -1;

    if (data_type == -1)
      return -1;

  } while (data_type != type);
  return data_offset;

}

static void install_progress_fix() {
  // Install the fix area from the bios and from logo_x.prg area
  // fix_conv(&neocd_bios[0x6beb0], neogeo_fix_memory, 0x4000, video_fix_usage );
  fix_conv(&neocd_bios[loading_animation_fix], neogeo_fix_memory, 0x4000, video_fix_usage );
  // fix_conv(&neocd_bios[0x7c000], neogeo_fix_memory, 0x4000, video_fix_usage );
  // now upload the fix parts from logo.prg, if any...
  int offset = 0x120002;
  while (offset != -1) {
    offset = check_screen_data(offset,1);
    if (offset > -1) {
      UINT16 fix_offs, size;
      fix_offs = ReadLongSc(&RAM[offset]);
      size = ReadLongSc(&RAM[offset + 4]);
      offset += 8;
      fix_conv(&RAM[offset],&neogeo_fix_memory[fix_offs>>1],size,&video_fix_usage[fix_offs>>6]);
      print_debug("fix from logo.prg %x size %x ram %x logo %x\n",fix_offs,size,offset,check_offset);
      offset = check_offset;
    }
  }
}

loading_params neocd_lp;

static struct {
  char *name;
  UINT8 *dest;
  int size,FileType;
  UINT32 offset;
  int conv_off,bytes_left;
} current;

static int load_file_off(char *name, UINT8 *dest, int offset, int size) {
  FILE *f = fopen(name,"rb");
  if (!f) {
    print_debug("couldn't load %s\n",name);
    return 0;
  }
  fseek(f,offset, SEEK_SET);
  fread(dest,1,size,f);
  fclose(f);
  return 1;
}

// Contrary to spr_conv, this one just updates the usage based on an already
// converted sprites are (on 256 bytes, not 128).
void update_spr_usage(UINT32 offset, UINT32 size) {
    UINT8 *dest = GFX + offset;
    UINT8 *usage_ptr = video_spr_usage + (offset>>8);
    print_debug("update_spr_usage %x,%x\n",offset,size);
    int i,j;
    for (i=0; i<size; i+= 256) {
	int res = 0;
	for (j=0; j<256; j++) {
	    if (dest[i+j])
		res++;
	}
	if (res == 0) // all transp
	    usage_ptr[i/256] = 0;
	else if (res == 256)
	    usage_ptr[i/256] = 2; // all solid
	else
	    usage_ptr[i/256] = 1; // semi
    }
}

static int load_neocd_file(char *name, UINT8 *dest, int size) {
  int offset = 0,ret;
  UINT8 *Ptr;
  print_debug("load_neocd_file %s\n",name);
  if (name && strstr(name,"spr")) {
    /* Quick support for override directory :
     * no loading progress for this, and any file in this directory is chosen
     * first, whatever the game */
    FILE *f = fopen(get_override(name),"rb");
    if (f) {
      fread(GFX + current.offset*2,1,size*2,f);
      fclose(f);
      print_ingame(180,gettext("used override for %s"),name);
      free(dest);
      // We must still update usage area, or we'll see nothing !
      cache_set_crc(current.offset*2,size*2,SPR_TYPE);
      update_spr_usage(current.offset*2,size*2);
      return 1;
    }
  } else if (name && strstr(name,".prg")) {
    FILE *f = fopen(get_override(name),"rb");
    if (f) {
      fread(RAM + current.offset,1,size,f);
      fclose(f);
      ByteSwap(&RAM[current.offset],size);
      print_ingame(180,gettext("used override for %s"),name);
      cache_set_crc(current.offset,size,PRG_TYPE);
      int Offset = current.offset;
      if (Offset <= 0x68 && Offset +current.size >= 0x6c) {
	// irq2 overwriten, kof96 neocd collection is the only known game to do
	// this !!!
	WriteLongSc(&RAM[0x10f6ee],ReadLongSc(&RAM[0x68]));
	print_debug("saving irq2 after load prg over it (%x)\n",ReadLongSc(&RAM[0x68]));
      }
      if (Offset <= 0x100)
	update_game_vectors();
      return 1;
    }
  }
  if (cdrom_speed && animations_enabled) {
    int possible_size = cdrom_speed*150000/60;
    if (!name) {
      name = current.name;
      dest = current.dest+neocd_lp.bytes_loaded;
      size = current.size - neocd_lp.bytes_loaded;
      offset = neocd_lp.bytes_loaded;
    } else {
      neocd_lp.bytes_loaded = 0;
      current.name = name;
      current.dest = dest;
      current.size = size;
      current.conv_off = current.bytes_left = 0;
    }
    if (size > possible_size) {
      neocd_lp.bytes_loaded += possible_size;
      size = possible_size;
    } else
      neocd_lp.bytes_loaded = 0;
  } else {
    current.size = size;
    current.dest = dest;
    current.conv_off = current.bytes_left = 0;
  }

  switch(load_type) {
    case ZIP_TYPE: // return load_zipped(neocd_path, name, size, 0, dest, 1);
      ret = load_zipped_part(neocd_path, name, offset, size, dest);
      break;
    case P7Z_TYPE:
      ret = load_7z(neocd_path, name, offset, size, 0, dest, 1);
      break;
    case IPL_TYPE:
		   if (!strchr(name,SLASH[0])) {
		     char file[1024];
		     sprintf(file,"%s%s%s",neocd_dir,SLASH,name);
		     ret = load_file_off(file,dest,offset,size);
		   } else
		     ret = load_file_off(name,dest,offset,size);
		  break;
    case CUE_TYPE:
    case ISO_TYPE: ret = load_from_iso(neocd_path, name, dest, offset, size);
	break;
    default:
		   print_debug("couldn't load %s\n",name);
		   return 0;
  }
  int Offset = current.offset;
  /* progressive conversion */
  switch (current.FileType) {
    case FIX_TYPE:
      if (cdrom_speed && animations_enabled) {
	Offset += current.conv_off;
	dest -= current.bytes_left;
	size += current.bytes_left;
	int size_conv = size/32*32;
	current.bytes_left = size-size_conv;
	current.conv_off += size_conv;
	size = size_conv;
      }
      Ptr = neogeo_fix_memory + Offset;
      fix_conv(dest, Ptr, size, video_fix_usage + (Offset>>5));

      break;
    case SPR_TYPE:
      if (cdrom_speed && animations_enabled) {
	Offset += current.conv_off;
	dest -= current.bytes_left;
	size += current.bytes_left;
	int size_conv = size/128*128;
	current.bytes_left = size-size_conv;
	current.conv_off += size_conv;
	size = size_conv;
      }
      Offset &= 0x3fffff;
      Ptr = GFX + Offset*2;
      if (Offset+size > 0x400000) {
	  /* What's loaded after the end of sprites ram appears at the start !
	   * Can be seen in kof94, how to play */
	  int size1 = 0x400000-Offset;
	  spr_conv(dest,Ptr,size1,video_spr_usage + (Offset>>7));
	  spr_conv(dest + size1,GFX,size-size1,video_spr_usage);
      } else
	  spr_conv(dest,Ptr,size,video_spr_usage + (Offset>>7));
      break;
    case PRG_TYPE:
      // How did I come with such a non-sense :
      ByteSwap(RAM+current.offset+offset,size);
      // anyway, current.offset is the offset in ram of the file
      // and offset is the offset in the file
      break;
  }
  if (!cdrom_speed || !animations_enabled || (cdrom_speed && neocd_lp.bytes_loaded == 0)) {
    // the end
    switch (current.FileType) {
      case FIX_TYPE:
	free(current.dest);

	cache_set_crc(current.offset,current.size,FIX_TYPE);
	print_debug("update fix crc\n");
	if (cdrom_speed && animations_enabled && current.offset < 0x400) {
	  print_debug("update saved fix area\n");
	  save_fix(0);
	  install_progress_fix();
	}
	break;
      case SPR_TYPE:
	free(current.dest);
	cache_set_crc(current.offset*2,current.size*2,SPR_TYPE);
	break;
      case Z80_TYPE:
      case PCM_TYPE:
	cache_set_crc(current.offset,current.size,current.FileType);
	break;
      case PAT_TYPE:
	ByteSwap(current.dest,current.size); // byteswap for z80 ???

	neogeo_cdrom_apply_patch((short*)current.dest, current.offset);
	free(current.dest);

	break;
      case PRG_TYPE:

	if (current.offset < 0x400) {
	    // try to restore the name as fast as possible to be able
	    // to restore the override dir from the current game name
	    char *name = current_game->main_name;
	    neogeo_read_gamename();
	    if (name != current_game->main_name)
		restore_override(1);
	}
	cache_set_crc(current.offset,current.size,PRG_TYPE);
	if (Offset <= 0x68 && Offset +current.size >= 0x6c) {
	  // irq2 overwriten, kof96 neocd collection is the only known game to do
	  // this !!!
	  WriteLongSc(&RAM[0x10f6ee],ReadLongSc(&RAM[0x68]));
	  print_debug("saving irq2 after load prg over it (%x)\n",ReadLongSc(&RAM[0x68]));
	}
	if (Offset <= 0x100)
	  update_game_vectors();

	break;
      }
  }
  return ret;
}

void cdrom_load_neocd() {
  load_neocd_file(NULL,NULL,0); // continue load, called when cdrom_speed > 0
}

extern UINT8 *RAM_PAL;

void fix_extension(char *FileName, char *extension) {
  char *ext = strrchr(FileName,'.');
  if (ext) {
    char old[4];
    int size;
    ext++;
    strcpy(old,ext);
    strcpy(ext,extension);
    size = get_size(FileName);
    if (!size)
      strcpy(ext,old); // keep the original
  }
}

void neogeo_cdrom_load_title(void)
{
  /* Loads a title screen based on the currently selected region */
  // all the games do not contain a title screen...
  char            file[12] = "title_x.sys";
  int size;
  UINT8 *buff;
  UINT8 *map;
  int                Readed;
  int                x, y;

#ifdef USE_VIDEO_GL
  int filter=neo4all_filter;
  neogeo_adjust_filter(1);
#endif
  //    sound_disable();

  file[6] = jue[GetLanguageSwitch()]; // adjust based on region

  size = get_size(file);
  if (!size) return;
  buff = (UINT8*)malloc(size);

  int old_cdrom = cdrom_speed;
  cdrom_speed = 0;
  current.FileType = -1;
  load_neocd_file(file,buff,size);
  cdrom_speed = old_cdrom;
  memcpy(RAM_PAL,buff,0x200);
  ByteSwap(RAM_PAL,0x200);
  print_debug("palette init from title\n");

  spr_conv(&buff[0x5a0], GFX, size-0x5a0, video_spr_usage);

  clear_game_screen(0);
  ClearPaletteMap();
  Readed = 0;
  for(y=0;y<80;y+=16)
  {
    for(x=0;x<144;x+=16)
    {
      MAP_PALETTE_MAPPED_NEW(
	  Readed,
	  16,
	  map);
      if (video_spr_usage[Readed]) {
	if (video_spr_usage[Readed] == 1)
	  Draw16x16_Trans_Mapped_Rot(&GFX[Readed<<8],(304-144)/2+ x+32,(224-80)/2+ y+32,map);
	else
	  Draw16x16_Mapped_Rot(&GFX[Readed<<8],(304-144)/2+ x+32,(224-80)/2+ y+32,map);
      }
      Readed++;
    }
  }

#ifndef RAINE_DOS
  if (sdl_screen->w != display_cfg.screen_x ||
      sdl_screen->h != display_cfg.screen_y ||
      sdl_screen->format->BitsPerPixel != display_cfg.bpp)
    ScreenChange();
#endif
  DrawNormal();
  memset(video_spr_usage,0,(size-0x5a0)/128); // Clear the sprite usage !!!
  free(buff);
}

static int loading_phase,total_size;

int    neogeo_cdrom_load_prg_file(char *FileName, unsigned int Offset)
{
  UINT8 *Ptr;
  int size;
  current.FileType = PRG_TYPE;

  fix_extension(FileName,"prg");

  size = get_size(FileName);
  if (Offset + size > 0x200000) {
    size = 0x200000-Offset;
    if (size <= 0) return 1;
  }
  Ptr = RAM + Offset;
  if (file_cache(FileName,Offset,size,PRG_TYPE)) {
    if (loading_phase == 0)
      total_size++;
    return 1; // file already present
  }
  if (loading_phase == 0) {
    total_size += (size+2047)/2048;
    return size;
  }

  current.offset = Offset;
  if (!load_neocd_file(FileName,Ptr,size)) {
    print_debug("could not load %s at %x,%x\n",FileName,Offset,size);
    return 0;
  }
  return size;
}

void    fix_inv_conv(UINT8 *Src, UINT8 *Ptr, int Taille)
{
    // Does the opposite of fix_conv : from a converted area, recreate the
    // original data
    int        i;
    UINT8 *orig_ptr = Ptr;
    for(i=Taille;i>0;i-=32) {
	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr++;

	*(Ptr+16) = *Src++;
	*(Ptr+24) = *Src++;
	*(Ptr) = *Src++;
	*(Ptr+8) = *Src++;
	Ptr+=25;
    }
    Ptr = orig_ptr;
    for (i=0; i<Taille; i++) {
	Ptr[i] = (Ptr[i]>>4) | ((Ptr[i]<<4));
    }
}

void    fix_conv(UINT8 *Src, UINT8 *Ptr, int Taille, unsigned char *usage_ptr)
{
  int        i;
  unsigned char    usage;
  UINT8 *orig_ptr = Ptr;

  for(i=Taille;i>0;i-=32) {
    usage = 0;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src++;
    *Ptr++ = *(Src+16);
    usage |= *(Src+16);
    *Ptr++ = *(Src+24);
    usage |= *(Src+24);
    *Ptr++ = *(Src);
    usage |= *(Src);
    *Ptr++ = *(Src+8);
    usage |= *(Src+8);
    Src+=25;
    *usage_ptr++ = usage;
  }
  // Raine renders inverted packed sprites by default
  // the easiest solution is to swap the bytes here
  Ptr = orig_ptr;
  for (i=0; i<Taille; i++) {
    Ptr[i] = (Ptr[i]>>4) | ((Ptr[i]<<4));
  }
}

int    neogeo_cdrom_load_fix_file(char *FileName, unsigned int Offset)
{
  UINT8    *buff;
  int size;
  current.FileType = FIX_TYPE;

  //    sound_disable();
  fix_extension(FileName,"fix");

  size = get_size(FileName);
  // size = 0 can happen in some weird disc images from fatal fury
  if (!size) return 1;

  if (Offset + size > 0x20000) {
    size = 0x20000-Offset;
    if (size <= 0) return 1;
  }
  if (file_cache(FileName,Offset,size,FIX_TYPE)) {
    if (loading_phase == 0)
      total_size++;
    return 1; // file already present
  }
  if (loading_phase == 0) {
    // total_size += size;
    total_size += (size+2047)/2048;
    return size;
  }
  if (cdrom_speed && animations_enabled && Offset < 0x400)
    restore_fix(0);

  buff = (UINT8*)malloc(size);
  current.offset = Offset;
  if (!load_neocd_file(FileName,buff,size)) return 0;
  return size;
}

int    neogeo_cdrom_load_spr_file(char *FileName, unsigned int Offset)
{
  int size;

  UINT8 *buff;
  current.FileType = SPR_TYPE;

  fix_extension(FileName,"spr");

  size = get_size(FileName);
  if (!size) {
      print_debug("load_spr: problem with %s\n",FileName);
      return 1;
  }

  // Do not try to fix the size here, sprites loop around the limit !
  if (file_cache(FileName,Offset*2,size*2,SPR_TYPE)) {
    if (loading_phase == 0)
      total_size++;
    return 1; // file already present
  }
  if (loading_phase == 0) {
    // total_size += size;
    total_size += (size+2047)/2048;
    return size;
  }

  print_debug("Loading %s offset %x size %x\n",FileName,Offset*2,size*2);
  buff = malloc(size);
  current.offset = Offset;
  if (!load_neocd_file(FileName,buff,size)) return 0;
  return size;
}

static int    neogeo_cdrom_load_z80_file(char *FileName, unsigned int Offset)
{
  int size;
  current.FileType = Z80_TYPE;

  fix_extension(FileName,"z80");
  size = get_size(FileName);
  if (!size) return 1;

  if (Offset + size > 0xffe0) {
    // The size must explicitely be fixed to ffe0 to leave the $800 last
    // bytes alone and avoid to overwrite the stack !
    size = 0xffe0-Offset;
    if (size <= 0) return 1;
  }
  if (file_cache(FileName,Offset,size,Z80_TYPE)) {
    if (loading_phase == 0)
      total_size++;
    return 1; // file already present
  }
  if (loading_phase == 0) {
    // total_size += size;
    total_size += (size+2047)/2048;
    return size;
  }

  print_debug("load %s %x,%x\n",FileName,Offset,size);
  current.offset = Offset;
  if (!load_neocd_file(FileName,&Z80ROM[Offset],size)) return 0;
  return size;
}

#define PATCH_Z80(a, b) { \
  Z80ROM[(a)] = (b)&0xFF; \
  Z80ROM[(a+1)] = ((b)>>8)&0xFF; \
}

void neogeo_cdrom_apply_patch(short *source, int master_offset)
{

  while(*source != 0)
  {
    PATCH_Z80( source[0], ((source[1] + master_offset)>>1) );
    PATCH_Z80( source[0] + 2, (((source[2] + master_offset)>>1) - 1) );

    if ((source[3])&&(source[4]))
    {
      PATCH_Z80( source[0] + 5, ((source[3] + master_offset)>>1) );
      PATCH_Z80( source[0] + 7, (((source[4] + master_offset)>>1) - 1) );
    }

    source += 5;
  }
}

static int    neogeo_cdrom_load_pat_file(char *FileName, unsigned int Offset, unsigned int Bank)
{
  int size;
  UINT8 *buff;
  current.FileType = PAT_TYPE;

  fix_extension(FileName,"pat");
  size = get_size(FileName);
  if (!size) return 1;
  if (loading_phase == 0) {
    // total_size += size;
    total_size += (size+2047)/2048;
    return size;
  }

  buff = (UINT8*)malloc(size);
  current.offset = (((Bank*0x100000) + Offset)/256)&0xFFFF;
  if (!load_neocd_file(FileName,buff,size)) return 0;
  return size;
}

int neogeo_cdrom_load_pcm_file(char *FileName, unsigned int Offset)
{
  int size;

  UINT8 *Ptr;
  current.FileType = PCM_TYPE;

  /* Some files are clearly not intended to be loaded, see the weird pcm
     file in the ipl.txt of aof for example ! */

  fix_extension(FileName,"pcm");
  size = get_size(FileName);
  if (!size) return 1;

  if (Offset + size > 0x100000) {
    print_debug("size was fixed for pcm\n");
    size = 0x100000 - Offset;
    if (size <= 0) return 1;
  }
  if (file_cache(FileName,Offset,size,PCM_TYPE)) {
    if (loading_phase == 0)
      total_size++;
    return 1; // file already present
  }
  if (loading_phase == 0) {
    // total_size += size;
    total_size += (size+2047)/2048;
    return size;
  }

  Ptr = PCMROM + Offset;
  print_debug("load %s %x,%x\n",FileName,Offset,size);
  current.offset = Offset;
  if (!load_neocd_file(FileName,Ptr,size)) return 0;
  return size;
}

static void finish_loading() {
  /* These writes are still necessary, they do what the bios would do if we
     were able to emulate every hardware address used by the cdrom. But we
     are very far from that, so it's much easier to do all the loading in
     only 1 time, and then call this function as if the bios had done it */
  write_reg_b(0xff0111,0); // spr_disable

  // This one clears copy protection (extracted from a tutorial on how to crack
  // neogeo cd games !)
  WriteByte(&RAM[0x10FE85^1], 0x01);
  /* I don't know where these writes come from since there are no comments
     at all (I love this, really !).
     Anyway, what I know is that they hide the fix layer in art of fighting
     when you have played the demo (even 1s of the demo is enough), then
     return to the main screen -> no fix layer if these writes are enabled */
  WriteLongSc(&RAM[0x10F68C], 0x00000000);
  WriteByte(&RAM[0x10F6DB^1], 0x01);
  WriteLongSc(&RAM[0x10F742], 0x00000000);
  WriteLongSc(&RAM[0x10F746], 0x00000000);

  // This is the particular write which blows fix area in aof (commented)
  // WriteByte(&RAM[0x10FDC2], 0x01);
  WriteByte(&RAM[0x10FDDC^1], 0x00); // c0DB60 (with/without loading screen)
  WriteByte(&RAM[0x10FDDD^1], 0x00); // c00712
  WriteByte(&RAM[0x10FE88^1], 0x00); // c07E88
  // WriteByte(&RAM[0x10FEC4^1], 0x01); // C0071C
  // this ec4 location prevents magician lord from testing the upload area
  // we'll have to test without it for a while...
  // At the same time, not setting this to 1 freezes mslug at start
  // there is definetely a problem with this address to be investigated...
  // Apparently this adress was linked to 10f6ea

  // this write seems to say that a game cd is loaded (it triggers the message
  // "press start button" in the cd interface).
  // 2 bits are used on this adress :
  // bit 0 : busy status for the cd -> message wait a moment in the cd interface
  // bit 7 : bootable cd loaded
  RAM[0x10f656^1] = 0x80;
  // WriteWord(&RAM[0x7db0],1);
  // This one is necessary of art of fighting 3, or you get a black screen
  // during loading. I guess it's some kind of ack... !
  WriteByte(&RAM[0x10F6D9 ^ 1], 0x01);
  animations_enabled = 0; // animations disabled, must be explicitely enabled
  // by the game...
}

int hextodec(char c) {
  switch (c) {
    case '0':	return 0;
    case '1':	return 1;
    case '2':	return 2;
    case '3':	return 3;
    case '4':	return 4;
    case '5':	return 5;
    case '6':	return 6;
    case '7':	return 7;
    case '8':	return 8;
    case '9':	return 9;
    case 'a':	return 10;
    case 'b':	return 11;
    case 'c':	return 12;
    case 'd':	return 13;
    case 'e':	return 14;
    case 'f':	return 15;
    default:	return 0;
  }
}

static void init_loading_progress() {
  neocd_lp.total_sectors = (total_size);
  print_debug("total_size %d neocd_lp.total_sectors %d\n",total_size,neocd_lp.total_sectors);
  WriteLongSc(&RAM[0x10f694],neocd_lp.total_sectors);
  WriteLongSc(&RAM[0x10f690],0);

  // save fix plane
  save_fix(1);
  // neocd_function(0x11c808);
  install_progress_fix();
  // save pal
  memcpy(&RAM[0x11be06],RAM_PAL,0x200);
  // pal = bios pal
  print_debug("pal init from bios\n");
  // memcpy(RAM_PAL,&neocd_bios[0x1701c],0x200);
  // memcpy(RAM_PAL,&neocd_bios[0x20ba2],0x200);
  memcpy(RAM_PAL,&neocd_bios[loading_animation_pal],0x200);
  int offset = 0x120002;
  while (offset != -1) {
    offset = check_screen_data(offset,2);
    if (offset > -1) {
      UINT16 bank = ReadWord(&RAM[offset]);
      print_debug("found pal bank from logo.prg %x\n",bank);
      memcpy(&RAM_PAL[bank*16*2],&RAM[offset+2],16*2);
      offset = check_offset;
    }
  }
  neocd_lp.file_to_load = 0;
  current_game->exec = &loading_progress_function;
  neocd_lp.sectors_to_load = neocd_lp.loaded_sectors = 0;
}

static int handle_file(char *FileName, int Off, int Bnk) {
  char *ext = strrchr(FileName,'.');
  if (ext) ext++;
  current.FileType = recon_filetype(ext,FileName);
  print_debug("handle_file %s %x,%x\n",FileName,Off,Bnk);
  int size;
  switch( current.FileType ) {
    case PRG_TYPE:
      size = neogeo_cdrom_load_prg_file(FileName, Off);
      break;
    case FIX_TYPE:
      size = neogeo_cdrom_load_fix_file(FileName, (Off>>1));
      break;
    case SPR_TYPE:
      size = neogeo_cdrom_load_spr_file(FileName, (Bnk*0x100000) + Off);
      break;
    case Z80_TYPE:
      size = neogeo_cdrom_load_z80_file(FileName, (Off>>1));
      break;
    case PAT_TYPE:
      size = neogeo_cdrom_load_pat_file(FileName, Off, Bnk);
      break;
    case PCM_TYPE:
      size = neogeo_cdrom_load_pcm_file(FileName, (Bnk*0x80000) + (Off>>1));
      break;
    default:
      // some files can't be recognised, see aof ipl.txt
      print_debug("didn't recognise %s (%d)\n",FileName,current.FileType);
      size = 1; // size = 0 is an error, we return 1 to avoid the error
  }
  print_debug("%s size : %d\n",FileName,size);
  neocd_lp.sectors_to_load = (size + 2047) / 2048;
  if (cdrom_speed && animations_enabled) {
    reset_ingame_timer();
  }
  return size;
}

int    neogeo_cdrom_process_ipl(loading_params *param)
{
  static char    FileName[16];
  int        Bnk;
  int        Off;
  int        i, j;
  static UINT8	*buf;
  int size;
  int start;

  sa_pause_sound();
  loading_phase = 1; // really load logo_x.prg
  animations_enabled = 1;

  // Try to load logo_x.prg if available
  if (!param) {
    int region = GetLanguageSwitch();
    size = get_size("ipl.txt")+1;
    if (size <= 0) return 0;
    if (buf) FreeMem(buf);
    if (!(buf = AllocateMem(size))) return 0;
    memset(buf,0,size);
    current.FileType = -1;
    if(!load_neocd_file("ipl.txt",buf,size-1)) {
      ErrorMsg("Could not open IPL.TXT!");
      sa_unpause_sound();
      FreeMem(buf);
      return 0;
    }

    total_size = 0;
    if (cdrom_speed && animations_enabled)
      start = 0;
    else
      start = 1;

    WriteLongSc(&RAM[0x120002],0xffffffff); // eof in case no logo file
    int old_cdrom = cdrom_speed;
    cdrom_speed = 0;
    current.FileType = PRG_TYPE;
    char            file[12] = "logo_x.prg";
    for (; region >= 0; region--) {
      file[5] = jue[region]; // adjust based on region
      if (neogeo_cdrom_load_prg_file(file,0x120000)) {
	break;
      }
    }
    cdrom_speed = old_cdrom;
  } else
    start = 1;

  neocd_lp.initial_cdrom_speed = cdrom_speed;
  for (loading_phase=start; loading_phase <= 1; loading_phase++) {
    if (loading_phase == 1 && !param && cdrom_speed && animations_enabled) {
      init_loading_progress();

      neocd_lp.function = 1;
      return 1; // to be continued...
    }

    char* bufp = (char*)buf;
    int nb_file = 0;
    while (1)
    {

      char* p = strchr(bufp,'\n');
      char    Line[32];
      if (p==NULL) break;
      p++;
      int len = p-bufp;
      memcpy(Line,bufp, len);
      Line[len] = 0;
      bufp = p;

      Bnk=0;
      Off=0;
      i=0;
      j=0;
      strlwr(Line);
      while((Line[i] != ',')&&(Line[i]!=0))
	FileName[j++] = Line[i++];
      FileName[j]=0;

      j -= 3;
      if (j>0) {
	i++;
	// Get the bank number (decimal)
	while(Line[i] != ',') {
	  Bnk*=10;
	  Bnk+=Line[i]-'0';
	  i++;
	}

	i++;
	// Get the offset (hex)
	while ((Line[i] >= '0' && Line[i]<='9') ||
	       	(Line[i]>='a' && Line[i]<='f')) {
	  Off*=16;
	  Off+=hextodec(Line[i++]);
	}

	Bnk &= 3;

	if (loading_phase > 0 && param) {
	  if (param->file_to_load > nb_file) {
	    nb_file++;
	    continue;
	  }
	  param->file_to_load++;
	}

	size = handle_file(FileName,Off,Bnk);
	if (size == 0) {
	  char msg[80];
	  sprintf(msg,"ipl.txt: error while loading %s.",FileName);
	  ErrorMsg(msg);
	  sa_unpause_sound();
	  FreeMem(buf);
	  return 0;
	}
	if (param) {
	  return 1;
	}
      }
    }
  }

  // FreeMem(buf); // don't free buff, keep it for savegames !
  sa_unpause_sound();
  reset_ingame_timer();
  if (param) {
    neocd_lp.function = 0;
    current_game->exec = &execute_neocd;
    neocd_lp.sectors_to_load = 0;
  }
  postprocess_ipl();
  if (cdrom_speed && animations_enabled) {
    memcpy(RAM_PAL,&RAM[0x11be06],0x200);
    restore_fix(1);
  }
  finish_loading();
  return 1;
}

#define swab(src,dest,len) memcpy(dest,src,len); ByteSwap(dest,len);

unsigned neogeo_cdrom_test_files(unsigned char *Ptr, loading_params *param)
{
  unsigned ret=0;
  char    Entry[32];
  static char FileName[14];
  int     i, j, Bnk, Off;
  if (param) {
    if (param->file_to_load != 0) {
      Ptr += 32*param->file_to_load;
    }
    loading_phase = 1;
  } else if (cdrom_speed && animations_enabled) {
    loading_phase = 0;
    total_size = 0;
    neocd_lp.initial_cdrom_speed = cdrom_speed;
  } else
    loading_phase = 1;

  // pspDebugScreenInit();
  do {
    if (!*Ptr)
      break;
    swab(Ptr, (UINT8 *)Entry, 32);
    i = 0;
    if (loading_phase == 1)
      Ptr[1] = 0;

    while((Entry[i]!=0)&&(Entry[i]!=';')) {
      FileName[i] = tolower(Entry[i]);
      i++;
    }

    FileName[i] = 0;

    Bnk = Entry[16]&3;

    Off = ReadLong68k((unsigned char *)&Entry[18]); // Entry is byteswapped
    if (!cdrom_speed || !animations_enabled || loading_phase < 1) {
      /* If animations are enabled we can't finish the laoding after handle_file
       * we must wait for the next call to this function to terminate */
      Ptr += 32;
    }

    j=0;
    while(FileName[j] != '.' && FileName[j] != '\0')
      j++;

    if(FileName[j]=='\0')
    {
      //console_printf("Internal Error loading file: %s",FileName);
      //SDL_Delay(1000);
      printf("internal error loading file %s\n",FileName);
      exit(1);
      // ExitCallback(1,2,NULL);
    }

    j++;

    ret++;
    // printf("Loading File: %s %02x %08x\n", FileName, Bnk, Off);
    //text_draw_loading(ret,check);

    handle_file(FileName,Off,Bnk);
  } while( *Ptr != 0 && !param);
  if (loading_phase == 0) {
    init_loading_progress();
    neocd_lp.function = 2;
    myStop68000(0,0);
  } else if (param) {
    if (*Ptr)
      param->file_to_load++;
  }
  if (loading_phase == 1 && !*Ptr) {
    // end of loading with or without loading progress...
    if (cdrom_speed && animations_enabled) {
      memcpy(RAM_PAL,&RAM[0x11be06],0x200);
      restore_fix(1);
      neocd_lp.function = 0;
      current_game->exec = &execute_neocd;
      neocd_lp.sectors_to_load = 0;
    }

    // sa_unpause_sound();
    finish_loading();
    reset_ingame_timer();
  }
  return ret;
}

void    neogeo_cdrom_load_files(UINT8 *Ptr)
{
  // sa_pause_sound();

  if (auto_stop_cdda) cdda_stop();
  //menu_raise();
  // cdda_current_track = 0;
  // now_loading();
  // neogeo_cdrom_load_title();

  neogeo_cdrom_test_files(Ptr,NULL);

  /*
     else
     ERROR !!!!!!!!!!!!!!!!!!
     */

}

