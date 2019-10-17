/******************************************************************************/
/*                                                                            */
/*                               LOAD/SAVE GAME                               */
/*                                                                            */
/******************************************************************************/
// format zlib only, sdl compatible

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cpumain.h"
#include "files.h"
#include "sasound.h"
#include "control.h" // trackball
#include <sys/stat.h> // mkdir ! (linux)
#include <zlib.h> // now uses zlib all the time for the savegames
#include <time.h>

#include "profile.h" // reset_ingame_timer()

#ifndef SDL
#include "gui.h" // setup/release_gui
#include "rgui.h" // raine file selector...
#else
// #include "compat.h"
// #include "sdl/SDL_gfx/SDL_rotozoom.h"
// #include "sdl/blit_sdl.h"
#include "dialogs/fsel.h"
#endif

#include "timer.h" // update_timers
#include "dejap.h" // default eeproms in raine.dat
#include "hiscore.h"
#include "newmem.h"
#include "neocd/cdda.h"

// #include "blit.h"
// #include "palette.h"
// #include "loadpng.h"

/*

Todo:

- Change ram area, so there is a savedata entry in each game driver (then it is
  not a special case in here).
- Add savedata and any callbacks needed for sound chip emulators and U68020. (done ?)
- Think of something useful to save in the global header, currently it is empty.
- Remove old load support, after the next release or two.

*/

#include "raine.h"
#include "savegame.h"
#include "conf-sound.h"

#include "starhelp.h"
#include "mz80help.h"
#include "68020.h"
#include "m68k.h"
#include "newcpu.h"

#include "config.h"
#include "memory.h"

#include "games.h"		// Games List

#include "ingame.h"

int RAMSize,RefreshBuffers;
UINT8 *RAM;

// ---- Saved Data Types -------------------------------

#define SAVE_RAM              ASCII_ID('R','A','M',0x00)
#define SAVE_MOUSE            ASCII_ID('M','O','U','S')
// SAVE_MOUSE is especially usefull for the demos...
#define SAVE_END              ASCII_ID('E','N','D',0x00)
#define SAVE_PICT              ASCII_ID('P','I','C','T')
#define SAVE_EXT		0

// -----------------------------------------------------

#define EXT_NAME 50

typedef struct SAVE_DATA
{
   UINT32 id;			// Unique ASCII_ID for this data
   char name[EXT_NAME+1];		// in case of extended id
   UINT8 *source;		// Pointer to the data in memory
   UINT32 size;			// Size of the data in bytes
} SAVE_DATA;

static int alloc_save_list;
static struct SAVE_DATA *save_data_list;

int SaveDataCount;
int SaveSlot;
int savegame_version;

void reset_savegames() {
    alloc_save_list = SaveDataCount = 0;
    if (save_data_list) {
	free(save_data_list);
	save_data_list = NULL;
    }
}

void AddSaveData(UINT32 id, UINT8 *src, UINT32 size)
{
  int n;
  if (SaveDataCount == alloc_save_list) {
      alloc_save_list += 10;
      save_data_list = realloc(save_data_list,sizeof(struct SAVE_DATA)*alloc_save_list);
  }
  for (n=0; n<SaveDataCount; n++) {
    if (save_data_list[n].id == id && save_data_list[n].source != src) {
	print_debug("AddSaveData: collision for id %x\n",id);
      save_data_list[n].source = src;
      save_data_list[n].size   = size;
      return;
    }
  }
  save_data_list[SaveDataCount].id     = id;
  save_data_list[SaveDataCount].source = src;
  save_data_list[SaveDataCount].size   = size;
  SaveDataCount++;
}

void AddSaveData_ext(char *name, UINT8 *src, UINT32 size)
{
  int n;
  if (SaveDataCount == alloc_save_list) {
      alloc_save_list += 10;
      save_data_list = realloc(save_data_list,sizeof(struct SAVE_DATA)*alloc_save_list);
  }
  if (strlen(name) > EXT_NAME) {
      printf("AddSaveData_ext: name overflow: %zd: %s\n",strlen(name),name);
      exit(1);
  }

  for (n=0; n<SaveDataCount; n++) {
    if (save_data_list[n].id == SAVE_EXT &&
	    !strcmp(save_data_list[n].name,name) &&
	    save_data_list[n].source != src) {
	print_debug("AddSaveData: collision for extended name %s\n",name);
      save_data_list[n].source = src;
      save_data_list[n].size   = size;
      return;
    }
  }
  strcpy(save_data_list[SaveDataCount].name,name);
  save_data_list[SaveDataCount].id     = SAVE_EXT;
  save_data_list[SaveDataCount].source = src;
  save_data_list[SaveDataCount].size   = size;
  SaveDataCount++;
}

void state_save_register_UINT8(const char *base,int num, char *part, void *src, int size) {
    char buff[80];
#ifdef RAINE_DOS
    sprintf(buff,"%s.%d.%s",base,num,part);
#else
    snprintf(buff,80,"%s.%d.%s",base,num,part);
#endif
    AddSaveData_ext(buff,src,size);
}

// -----------------------------------------------------

#define CALLBACK_LOAD      (0x00000001)
#define CALLBACK_SAVE      (0x00000002)
#define CALLBACK_CORE      (0x00000004)

typedef struct SAVE_CALLBACK
{
   UINT32 flags;			// Unique ASCII_ID for this data
   void (*proc)();		// Callback routine ptr
} SAVE_CALLBACK;

struct ptr_callback {
    void (*proc)(void *);
    void *arg;
};

#define SIZE_CALLB 0x40
static struct SAVE_CALLBACK save_callback_list[SIZE_CALLB];
static struct ptr_callback save_callback_ptr[SIZE_CALLB];

UINT32 SaveCallbackCount,savecbptr_count;

static int find_callback(int flags, void *callback) {
    if (SaveCallbackCount == SIZE_CALLB) {
	printf("callbacks overflow, sorry !\n");
	exit(1);
    }
    int n;
    for (n=0; n<SaveCallbackCount; n++)
	if (save_callback_list[n].flags == flags &&
	       	save_callback_list[n].proc == callback)
	    return n;
    return -1;
}

void AddLoadCallback_ptr(void *callback,void *arg) {
    if (savecbptr_count == SIZE_CALLB) {
	printf("callbackptr overflow\n");
	exit(1);
    }
    int n;
    for (n=0; n<savecbptr_count; n++) {
	if (save_callback_ptr[n].proc == callback &&
		save_callback_ptr[n].arg == arg) {
	    print_debug("AddLoadCallback_ptr: callback already added!\n");
	    return;
	}
    }
    save_callback_ptr[savecbptr_count].proc = callback;
    save_callback_ptr[savecbptr_count++].arg = arg;
}

void AddLoadCallback(void (*callback)())
{
    if (find_callback(CALLBACK_LOAD,callback)>0) {
	print_debug("AddLoadCallback: callback already inserted\n");
	return;
    }
   save_callback_list[SaveCallbackCount].flags     = CALLBACK_LOAD;
   save_callback_list[SaveCallbackCount].proc      = callback;
   SaveCallbackCount++;
}
void AddSaveCallback(void (*callback)())
{
    if (find_callback(CALLBACK_SAVE,callback)>0) {
	print_debug("AddSaveCallback: callback already inserted\n");
	return;
    }
   save_callback_list[SaveCallbackCount].flags     = CALLBACK_SAVE;
   save_callback_list[SaveCallbackCount].proc      = callback;
   SaveCallbackCount++;
}

void AddLoadCallback_Internal(void *callback)
{
    if (find_callback(CALLBACK_LOAD|CALLBACK_CORE,callback)>0) {
	print_debug("AddLoadCallback_internal: callback already inserted\n");
	return;
    }
   save_callback_list[SaveCallbackCount].flags     = CALLBACK_LOAD|CALLBACK_CORE;
   save_callback_list[SaveCallbackCount].proc      = callback;
   SaveCallbackCount++;
}

void AddSaveCallback_Internal(void *callback)
{
    if (find_callback(CALLBACK_SAVE|CALLBACK_CORE,callback)>0) {
	print_debug("AddSaveCallback_Internal: callback already inserted\n");
	return;
    }
   save_callback_list[SaveCallbackCount].flags     = CALLBACK_SAVE|CALLBACK_CORE;
   save_callback_list[SaveCallbackCount].proc      = callback;
   SaveCallbackCount++;
}

void ProcessCallbackList(UINT32 flags)
{
   UINT32 ta;

   for(ta=0; ta<SaveCallbackCount; ta++){
      if(save_callback_list[ta].flags == flags){
         if(save_callback_list[ta].proc)
            save_callback_list[ta].proc();
      }
   }
   if (flags == CALLBACK_LOAD) {
       int n;
       for (n=0; n<savecbptr_count; n++) {
	   save_callback_ptr[n].proc(save_callback_ptr[n].arg);
       }
   }
}

#define MAX_DYN 10
static struct {
  void (*load)(UINT8 *buff, int len);
  void (*save)(UINT8 **buff, int *len);
} dyn_callbacks[MAX_DYN];

void AddSaveDynCallbacks(int id,void (*load)(UINT8 *buff, int len),
  void (*save)(UINT8 **buf, int *len)) {
  if (id < MAX_DYN) {
    dyn_callbacks[id].load = load;
    dyn_callbacks[id].save = save;
  } else {
    print_debug("bad dyn save id %d\n",id);
  }
}

void reset_dyn_callbacks() {
  memset(&dyn_callbacks,0,sizeof(dyn_callbacks));
}

// -----------------------------------------------------

void NewSave(gzFile fout)
{
   int ta;

   ProcessCallbackList(CALLBACK_SAVE);
   ProcessCallbackList(CALLBACK_SAVE|CALLBACK_CORE);

   // global header

   mputl(SAVE_FILE_TYPE_2, fout);
   iputl(0x00000000, fout);

   // ram header

   mputl(SAVE_RAM, fout);
   iputl(RAMSize, fout);
   gzwrite( fout,RAM, RAMSize);

   // user data header

   for(ta=0;ta<SaveDataCount;ta++){
      mputl(save_data_list[ta].id, fout);
      if (save_data_list[ta].id == SAVE_EXT) {
	  gzputc(fout,strlen(save_data_list[ta].name));
	  gzwrite(fout,save_data_list[ta].name, strlen(save_data_list[ta].name));
      }
      iputl(save_data_list[ta].size, fout);
      gzwrite( fout,save_data_list[ta].source, save_data_list[ta].size);
   }

   if (GameMouse) {
     mputl(SAVE_MOUSE,fout);
     iputw(p1_trackball_x,fout);
     iputw(p1_trackball_y,fout);
   }

   for (ta=0; ta < MAX_DYN; ta++) {
     if (dyn_callbacks[ta].save) {
       UINT8 *buff;
       int len;
       dyn_callbacks[ta].save(&buff,&len);
       if (len) {
	 mputl(ASCII_ID('D','Y','N',ta),fout);
	 print_debug("storing %d bytes for dynamic callback %d\n",len,ta);
	 iputl(len,fout);
	 gzwrite(fout,buff,len);
	 FreeMem(buff);
       }
     }
   }

   mputl(SAVE_END, fout);
   // File not closed here because of demos which continue to write after this
}

void do_save_state(char *name) {
   gzFile fout;
   char str[256],*disp_str;

   if(RAMSize){
     if (strstr(name,SLASH)) // The name is already a path
       strcpy(str,name);
     else
       snprintf(str,256,"%ssavegame" SLASH "%s",dir_cfg.exe_path,name);
     disp_str = strstr(str,"savegame");
     if (!disp_str) disp_str = str;
     if (!(fout=gzopen(str,"wb9"))){
      print_ingame(120,"Unable to save: %s",disp_str);
      return;
     }

     sa_pause_sound();
     stop_cpu_main();

     NewSave(fout);

     gzclose(fout);

     print_ingame(120,"Saved to: %s",disp_str);
     if (!raine_cfg.req_pause_game) {
       start_cpu_main();
       sa_unpause_sound();
       reset_ingame_timer();
     }

   }
   else{
      print_ingame(120,"Game does not support Saving.");
   }

   print_debug("END: GameSave()\n");
}

static void get_save_name(char *str) {
   if (is_neocd())
       sprintf(str,"%ssavegame" SLASH "ncd_%s.sv%d",dir_cfg.exe_path,current_game->main_name,SaveSlot);
   else
       sprintf(str,"%ssavegame" SLASH "%s.sv%d",dir_cfg.exe_path,current_game->main_name,SaveSlot);
}

void GameSave(void)
{
   char str[FILENAME_MAX];

   print_debug("BEGIN: GameSave()\n");
   get_save_name(str);

   do_save_state(str);
}

void GameSaveName(void)
{
  char str[FILENAME_MAX];

   print_debug("BEGIN: GameSaveName()\n");

   sprintf(str,"savegame" SLASH "%s" SLASH,current_game->main_name);
   mkdir_rwx(str);
   sa_pause_sound();
   stop_cpu_main();
#ifndef SDL
   setup_gui();
   if (raine_file_select("Save game",str,NULL))
     do_save_state(str);
   release_gui();
#else
    char *exts[] = { ".sav", NULL };
    char res[FILENAME_MAX];
    *res = 0;
    fsel(str,exts,res,"Save game");
    if (*res)
	do_save_state(str);
#endif
}

/******************************************************************************/

void read_safe_data(UINT8 *dest, UINT32 dest_size, UINT32 data_size, gzFile fin)
{

   if(dest_size==data_size){
      gzread(fin,dest,data_size);
      return;
   }
   if(dest_size>data_size){
      print_debug("Actual size is bigger than load data!\n");
      if(data_size>0) gzread(fin,dest,data_size);
      return;
   }
   if(dest_size<data_size){
      print_debug("Actual size is smaller than load data!\n");
      if(dest_size>0) gzread(fin,dest,dest_size);
			gzseek(fin,data_size - dest_size,SEEK_CUR);
			print_debug("read_safe_data: skiping %d bytes\n",data_size - dest_size);
      return;
   }
}

#define ASC(x) ((x)<32?(x)+0x30:(x))

void NewLoad(gzFile fin)
{
   int ta,tb,load_done;
   char name[EXT_NAME+1];
   UINT32 t_size,t_id;
	 int endianess_bug = 0;

   // global header

   t_size = igetl(fin);

   load_done=0;

   do{

   // read header

   t_id   = mgetl(fin);
   if (t_id == SAVE_EXT) {
       t_size = gzgetc(fin);
       gzread(fin,name,t_size);
       name[t_size] = 0;
       if (endianess_bug)
	   t_size = mgetl(fin);
       else
	   t_size = igetl(fin);
       for(ta=0;ta<SaveDataCount;ta++){
	   if(save_data_list[ta].id == SAVE_EXT &&
		   !strcmp(save_data_list[ta].name,name)){
	       print_debug("NewLoad: extended section %s\n",name);
	       read_safe_data(save_data_list[ta].source,save_data_list[ta].size,t_size,fin);
	       break;
	   }
       }
       if (ta == SaveDataCount) {
	   print_debug("NewLoad: extended section %s not found\n",name);
	   read_safe_data(NULL,0,t_size,fin);
       }
       continue;
   }
   if (endianess_bug)
       t_size = mgetl(fin);
   else
       t_size = igetl(fin);

   switch(t_id){
      case SAVE_RAM:
	 if (abs(t_size-RAMSize) > 0x10000) {
		 print_debug("endianess bug detected, ramsize = %x instead of %x\n",t_size,RAMSize);
		 gzseek(fin,-4,SEEK_CUR);
		 t_size = mgetl(fin);
		 endianess_bug = 1;
	 }
	 print_debug("NewLoad: SAVE_RAM section\n");
         read_safe_data(RAM,RAMSize,t_size,fin);
      break;
      case SAVE_PICT:
        print_debug("NewLoad: SAVE_PICT section\n");
        gzseek(fin,t_size,SEEK_CUR);
	break;

      case SAVE_END:
         print_debug("Load Completed Successfully\n");
         load_done=1;
      break;
      case EOF:
         print_debug("Load Completed, but 'END.' marker was not found\n");
         load_done=1;
      break;
      case SAVE_MOUSE: // Only saved when GameMouse is true
	print_debug("NewLoad: SAVE_MOUSE section\n");
      	p1_trackball_x = t_size & 0xffff;
	p1_trackball_y = t_size >> 16;
	break;
      default:
         for (ta=0; ta<MAX_DYN; ta++) {
	   if (t_id == ASCII_ID('D','Y','N',ta)) {
	     print_debug("NewLoad: SAVE_DYN%d section\n",ta);
	     if (dyn_callbacks[ta].load) {
	       UINT8 *buff = AllocateMem(t_size);
	       if (buff) {
		 gzread(fin,buff,t_size);
		 dyn_callbacks[ta].load(buff,t_size);
		 FreeMem(buff);
		 break;
	       } else {
		 print_debug("could not allocate %d bytes for dyn callback\n",t_size);
		 gzseek(fin,t_size,SEEK_CUR);
	       }
	     } else {
	       print_debug("found dyn callback %d but I have no loading function\n",ta);
	     }
	   }
	 }
	 if (t_id == ASCII_ID('D','Y','N',ta))
	   break;

         tb=0;
         for(ta=0;ta<SaveDataCount && tb==0;ta++){
            if(save_data_list[ta].id == t_id){
	      print_debug("NewLoad: section %c%c%c%c\n",ASC((t_id>>24)),ASC((t_id>>16)&0xff),ASC((t_id>>8)&0xff),ASC(t_id & 0xff));
               read_safe_data(save_data_list[ta].source,save_data_list[ta].size,t_size,fin);
               tb=1;
            }
         }
         if(tb==0){
            print_debug("Unexpected ID in savefile: %08x/%08x\n",t_id,t_size);
            read_safe_data(NULL,0,t_size,fin);
	    if (t_size <= 0) {
	      print_debug("early exit for savefile\n");
	      load_done = 1;
	    }

         }
      break;
   }

   }while(!load_done);
   ProcessCallbackList(CALLBACK_LOAD|CALLBACK_CORE);
   ProcessCallbackList(CALLBACK_LOAD);
}

void do_load_state(char *name) {
  gzFile fin;
  char str[256],*disp_str;

   if(RAMSize){
     if (strstr(name,SLASH)) // The name is already a path
       strcpy(str,name);
     else
       snprintf(str,256,"%ssavegame" SLASH "%s",dir_cfg.exe_path,name);
   disp_str = strstr(str,"savegame");
   if (!disp_str) disp_str = str;
   if(!(fin=gzopen(str,"rb"))){
        print_ingame(120,"Unable to load: %s", disp_str);
        return;
   }

   savegame_version = mgetl(fin);

   sa_pause_sound();
   stop_cpu_main();

   switch(savegame_version){
      case SAVE_FILE_TYPE_0:
	print_ingame(120,"savegame" SLASH "%s.sv%d is too ancient!", current_game->main_name, SaveSlot);
         gzclose(fin);
         return;
      break;
      case SAVE_FILE_TYPE_1:
      case SAVE_FILE_TYPE_2:
         hs_close();
	 hs_open();
#if HAS_NEO
	 cdda_stop();
#endif
         NewLoad(fin);
	 // In fact, this hs_load is a problem : normally the hiscores are
	 // loaded once the memory has been init by the driver. But there is no
	 // way to guess if a savegame is after the memory has been initialised
	 // or not. Well since normally this initialization happens very quickly
	 // it seems better to force the loading of the hiscores (if we don't
	 // force it, then it can't detect if the memory was initialized and
	 // they are never loaded).
	 if (is_neocd()) {
	     // neocd : avoid to load the hiscores if the ram has been
	     // overwritten by the bios (cd interface for example)
	     // in this case the pointer to the game name points into the bios!
	     int region_code = GetLanguageSwitch();
	     UINT32 Ptr = ReadLongSc(&RAM[0x116]+4*region_code);
	     if (Ptr < 0x200000) hs_load();
	 } else
	     hs_load();
	 print_ingame(120,"Loaded from: %s", disp_str);
	 update_timers();
      break;
      default:
	print_ingame(120,"savegame" SLASH "%s.sv%d is not recognised", current_game->main_name, SaveSlot);
         // gzclose(fin);
         // return;
      break;
   }

   gzclose(fin);


   RefreshBuffers=1;

   if (!raine_cfg.req_pause_game) {
     start_cpu_main();
     sa_unpause_sound();
     reset_ingame_timer();
   }

   }
   else{
      print_ingame(120,"Game does not support Loading.");
   }

   reset_ingame_timer();

   print_debug("END: GameLoad()\n");
}

void GameLoad(void)
{
   char str[FILENAME_MAX];

   print_debug("BEGIN: GameLoad()\n");

   get_save_name(str);
   do_load_state(str);
}

void GameLoadName(void)
{
  char str[256];

   print_debug("BEGIN: GameLoadName()\n");

   sprintf(str,"savegame" SLASH "%s" SLASH,current_game->main_name);
   sa_pause_sound();
   stop_cpu_main();
#ifndef SDL
   setup_gui();
   if (raine_file_select("Load game",str,NULL))
     do_load_state(str);
   release_gui();
#else
    char *exts[] = { ".sav", NULL };
    char res[FILENAME_MAX];
    *res = 0;
    fsel(str,exts,res,"Load game");
    if (*res)
	do_load_state(str);
#endif
}

/******************************************************************************/

#define MAX_EPROM	(4)

typedef struct EPR_DATA
{
   UINT8 *source;		// Pointer to the data in memory
   UINT32 size;			// Size of the data in bytes
   UINT8 flags;			// Flags
} EPR_DATA;

static struct EPR_DATA eeprom_list[MAX_EPROM];

static int eeprom_count;
UINT8 *default_eeprom;
UINT16 default_eeprom_size;

void clear_eeprom_list(void)
{
   eeprom_count=0;
   default_eeprom = NULL;
   default_eeprom_size = 0;
}

void add_eeprom(UINT8 *source, UINT32 size, UINT8 flags)
{
   int ta;

   ta = eeprom_count;

   eeprom_list[ta].source = source;
   eeprom_list[ta].size   = size;
   eeprom_list[ta].flags  = flags;

   memset(eeprom_list[ta].source,0xff,eeprom_list[ta].size);

   eeprom_count++;
}

static char *epr_ext[MAX_EPROM]=
{
   ".epr",
   ".ep0",
   ".ep1",
   ".ep2",
};

int load_eeprom(void)
{
   char str[256];
   int ta,ret=0;

   for(ta=0;ta<eeprom_count;ta++){

   snprintf(str,256,"%ssavedata" SLASH "%s%s", dir_cfg.exe_path, current_game->main_name, epr_ext[ta]);
   ret = load_file(str, eeprom_list[ta].source, eeprom_list[ta].size);
   if(!ret){
     memset(eeprom_list[ta].source,0xff,eeprom_list[ta].size);
     if (default_eeprom && default_eeprom_size) {
       memcpy(eeprom_list[ta].source,default_eeprom,default_eeprom_size);
       continue;
     }
   }

   }
   return ret;
}

void save_eeprom(void)
{
   char str[256];
   int ta;

   for(ta=0;ta<eeprom_count;ta++){
      snprintf(str,256,"%ssavedata" SLASH "%s%s", dir_cfg.exe_path, current_game->main_name, epr_ext[ta]);
      save_file(str, eeprom_list[ta].source, eeprom_list[ta].size);
   }
}

void next_save_slot(void)
{
  struct stat buf;
  char str[FILENAME_MAX],date[30];
   SaveSlot++;

   if(SaveSlot>9)
      SaveSlot=0;

   get_save_name(str);
   if (stat(str,&buf) < 0)
     sprintf(date,"free");
   else
     strftime(date,sizeof(date),"%x %X",localtime(&buf.st_mtime));

   print_ingame(120,"Save Slot %01d (%s)",SaveSlot,date);
}

#if 0
// previews in savegames disabled for now because I need a new kind of gui
// widget to display them...
int get_saved_picture(gzFile fin,char **s) {
  // return the picture if one was saved it the savegame
  // fin points in the savegame just after the version number
  UINT32 t_size,t_id;
  t_size = igetl(fin);
  do{

    // read header

    t_id   = mgetl(fin);
    t_size = igetl(fin);
    switch(t_id) {
      case SAVE_MOUSE:
        igetl(fin);
	break;
      case SAVE_PICT:
        *s = (char*)malloc(t_size);
	gzread(fin,*s,t_size);
	return t_size;
      default:
        gzseek(fin,t_size,SEEK_CUR);
	break;
    }
  } while (t_id != SAVE_END);
  *s = NULL;
  return 0;
}

void store_picture(gzFile fout) {
#ifdef SDL
#define SBUF 1024
   char buff[SBUF];
   FILE *f;
   int taille;
   mputl(SAVE_PICT, fout);
   sprintf(buff, "%stemp.png", dir_cfg.screen_dir);
   SDL_PixelFormat *fmt = sdl_game_bitmap->format;
   SDL_Surface *view = SDL_CreateRGBSurface(SDL_SWSURFACE,
     GameViewBitmap->w,GameViewBitmap->h,32,
     0xff0000,0xff00,0xff,0);
   SDL_Rect r;
   r.x = current_game->video->border_size;
   r.y = r.x;
   r.w = GameViewBitmap->w;
   r.h = GameViewBitmap->h;
   int ret = SDL_BlitSurface(sdl_game_bitmap,&r,view,NULL);
   printf("blit : %d\n",ret);

    SDL_Surface *scaled = rotozoomSurfaceXY(view,
      0.0, 0.25, 0.25, 0);
    BITMAP *scaled_bmp = surface_to_bmp(scaled);
   save_png(buff,scaled_bmp,pal);
   destroy_bitmap(scaled_bmp);
   SDL_FreeSurface(view);
   f = fopen(buff,"rb");
   if (f) {
     fseek(f,0L,SEEK_END);
     taille = ftell(f);
     fseek(f,0L,SEEK_SET);
     iputl(taille,fout);

     while (taille > 0) {
       if (taille > SBUF) {
	 fread(buff,SBUF,1,f);
	 gzwrite( fout,buff, SBUF);
	 taille -= SBUF;
       } else {
	 fread(buff,taille,1,f);
	 gzwrite( fout, buff, taille);
	 taille = 0;
       }
     }
     fclose(f);
   }
#endif
}
#endif
