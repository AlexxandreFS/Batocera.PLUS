#include <dirent.h>
#include <unistd.h>
#include "raine.h"
#include "neocd.h"
#include "sasound.h"
#include "profile.h"
#include "savegame.h"
#include "cdrom.h"
#include "ingame.h"
#include "sound/assoc.h"
#include "games/games.h"
#include "mz80help.h"
#include "cpumain.h"
#include "timer.h"
#include "cdda.h"

int auto_stop_cdda = 0,mute_sfx = 0, mute_music = 0;

cdda_t cdda;

int sfx_volume,music_volume,neocd_cdda_format;
int start_index,end_index;

#ifdef RAINE_DOS
void cdda_stop() {}
void do_cdda( int command, int track_number_bcd) {}
void init_cdda() {}
void prepare_cdda_save(UINT32 id) {}
#else

static SDL_CD *cdrom;

static char *find_file(char *pattern,char *path){
  static char name[256];
  char buff[1024];
  char number[25];
  char ext[10];
  char *s = strchr(pattern,'.');
  if (s) {
    strcpy(ext,s);
    strcpy(number,pattern);
    number[s-pattern] = 0;
  } else {
    number[0] = ext[0] = 0;
  }

  name[0] = 0;

  DIR *dir = opendir(path);
  if (!dir) return NULL;
  struct dirent *dent;
  while ((dent = readdir(dir))) {
    // windows does not support strcasestr, use strlwr before...
    strcpy(buff,dent->d_name);
    strlwr(buff);
    if (strstr(buff,pattern)) {
      strcpy(name,dent->d_name);
      break;
    } else if (*number) {
      // if (strcasestr(dent->d_name,ext))
	int len = strlen(number);
	s = dent->d_name-1;
	do {
	  s = strstr(s+1,number);
	  // search for the track number alone in the filename (ie followed
	  // by a non digit, and either at the start of the name, or following
	  // a non digit !
	} while (s && ((s[len] <= '9' && s[len] >= '0') ||
	  (s > dent->d_name && (s[-1] >= '0' && s[-1] <= '9'))));
	if (s) {
	  strcpy(name,dent->d_name);
	  break;
	}
    }
  }
  closedir(dir);
  if (name[0]) return name;
  return NULL;
}

void cdda_stop() {
  // usefull before loading a game...
  cdda.playing = CDDA_STOP;
  if (cdrom)
    SDL_CDStop(cdrom);
}

static void cdda_resume() {
  if (cdda.playing==CDDA_PAUSE) {//was in pause, so resume & let stop/play again
    cdda.playing = CDDA_PLAY;
    if (cdrom)
      SDL_CDResume(cdrom);
  }
}

static int cdda_play(int track,int loop)
{
  char str[FILENAME_MAX];char str2[FILENAME_MAX];char *str3;
  print_debug("cdda_play %d loop %d\n",track,loop);

  if (!RaineSoundCard) return 1;

  cdda_stop();
  cdda.track = track;

  str3 = get_mp3_track(track);
  if (!str3) {
    get_track_index(track,&start_index, &end_index);
    if (start_index) {
      if (loop)
	cdda.loop = -1;
      else
	cdda.loop = 0;
      cdda.playing = CDDA_PLAY;
      return 1;
    }
  }
  if (!str3) {
      if (get_cd_load_type() != IPL_TYPE) {
	  // Guess the file, but not when reading directly the files !!!
	  sprintf(str,"%s%sneocd.mp3",neocd_dir,SLASH);
	  strcpy(str2,"xx.mp3");
	  str2[0]=(((track)/10)%10)+48;
	  str2[1]=((track)%10)+48;

	  str3=find_file(str2,str);
	  if (!str3) { // try in the same dir
	      strcpy(str,neocd_dir);
	      str3=find_file(str2,str);
	  }
      }
  } else if (!strchr(str3,SLASH[0])) // no path in track
    strcpy(str,neocd_dir);
  else
      str[0] = 0;

  if (!str3) {
    // defaults to direct cdda reading...
    if (!cdrom) {
      int ndrives = SDL_CDNumDrives();
      int n;
      print_debug("found %d cd drives\n",ndrives);
      for (n=0; n<ndrives; n++) {
	cdrom = SDL_CDOpen(n);
	if (!CD_INDRIVE(SDL_CDStatus(cdrom)) || cdrom->numtracks <= 1) {
	  print_debug("cd drive %d isn't good\n",n);
	  SDL_CDClose(cdrom);
	  cdrom = NULL;
	} else
	  break;
      }
    }
    if (cdrom) {
      print_debug("starting direct cdda play track %d\n",track);
      SDL_CDPlayTracks(cdrom,track-1,0,1,0);
      if (loop)
	cdda.loop = -1;
      else
	cdda.loop = 0;
      cdda.playing = CDDA_PLAY;
      return 1;
    }
  }

  if (str3) {
    print_debug("cdda play - mp3 found str:%s.\n",str);
    if (str[0] && str[strlen(str)-1] != SLASH[0])
      strcat(str,SLASH);
    strcat(str,str3);
    load_sample(str);
    if (loop)
      cdda.loop = -1;
    else
      cdda.loop = 0;
    get_track_index(track,&start_index, &end_index);
    if (start_index) {
      set_sample_pos(start_index);
      start_index = end_index = 0;
    }
    print_debug("playing %s\n",str);
    reset_ingame_timer(); // loading the song can be long, esp from a cd !
  } else {
      print_ingame(180,gettext("Could not find audio track %d"),track);
      print_debug("Could not find audio track %d",track);
  }

  return 1;
}

static void	cdda_pause(void)
{
  print_debug("cdda pause\n");
  if (cdda.playing)
    cdda.playing = CDDA_PAUSE;
  if (cdrom)
      // Notice : pause and resume are totally unreliable with sdl !
      // All this should be replace by something to access the data on the
      // tracks directly, but I am not sure it exists a cross platform solution
    SDL_CDPause(cdrom);
}

void do_cdda( int command, int track_number_bcd)
{
	int		track_number;

  print_debug("do_cdda(%d,%d)\n",command,track_number_bcd);
	if ((command == 0)&&(track_number_bcd == 0))
		return;

	switch( command )
	{
	  case	0:
	  case	1:
	  case	5:
	  case	4:
	    track_number = ((track_number_bcd>>4)*10) + (track_number_bcd&0x0F);
	    if ((track_number == 0)&&(!cdda.playing))
	    {
	      cdda.playing = CDDA_PLAY;
	    }
	    else if ((track_number>1)&&(track_number<99))
	    {
	      cdda_play(track_number,!(command&1));
	    }
	    break;
	  case	6:
	  case	2:
	    if (cdda.playing)
	    {
	      //sound_mute();
	      cdda_pause();
	    }
	    break;
	  case	3:
	  case	7:
	    cdda_resume();
	    break;
	}
}

void init_cdda() {
  cdda.playing = cdda.track = cdda.pos = start_index = 0;
  if (cdrom) {
    SDL_CDStop(cdrom);
    SDL_CDClose(cdrom);
    cdrom = NULL;
  }
}

static void restore_cdda() {
    if (!is_neocd() && disable_assoc) {
	cdda.playing = CDDA_STOP;
	return;
    }
  if (cdda.playing) { // play, pause or load, any activity
    int track = cdda.track;
    int pos = cdda.pos;
    if (is_neocd()) {
	cdda.track = -1;
	cdda_play(track,cdda.loop);
    } else {
	last_song = track;
	char *t = get_assoc(track);
	if (t) {
	    load_sample(t);
	}
    }
    set_sample_pos(pos);
  } else if (cdda.playing == CDDA_PAUSE)
    cdda.playing = CDDA_PLAY;
  print_debug("cdda restored\n");
}

void prepare_cdda_save(UINT32 id) {
  AddSaveData(id,(UINT8*)&cdda,sizeof(cdda));
  AddLoadCallback(restore_cdda);
}
#endif

