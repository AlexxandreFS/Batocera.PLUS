#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sound/assoc.h"
#include "confile.h"
#include "neocd/cdda.h"
#include "sasound.h"
#ifdef SDL
#include "sdl/compat.h" // exists
#endif
#include "raine.h" // Z80ROM
#include "games.h" // current_game
#include "ingame.h" // print_ingame
#include "savegame.h"

#define VERBOSE 0

#ifdef RAINE_DOS
static void start_music_fadeout(double time) {
    // Does nothing in dos
}
#endif

// active : same role as cdda.playing, except that neocd and neogeo share the
// same code, so if we use cdda.playing, neocd tracks are stopped very very
// quickly !!!
static int type,adr,active,end_sound_codes;
static char *track[256],loop[256];
int disable_assoc,last_song;
enum {
    MUSIC=0,
    SOUND,
    ONE_SOUND,
    FADEOUT,
    EAT_TWO
};
static int mode;
// use_music : do we use external music ? It's the case if a real association
// is made or if playing neocd tracks. In this case sfx_volume and music_volume
// apply, otherwise everything is played at maximum volume.
int use_music;

static int search(int len, UINT8 *needle, int n) {
    int index = 0;
    while (index < len && n < 0x1000) {
	if (Z80ROM[n] == needle[index])
	    index++;
	else
	    index = 0;
	n++;
    }
    return n;
}

void init_assoc(int kind) {
    if (kind == 1) { // neogeo
	/* Some roms have a version + an author in them, but apparently
	 * there are some variants, so they must be recognized on something
	 * else. So I just check the instruction, it must be ld (ld),adr
	 * ($21) */
	char *err = "";
	end_sound_codes = 0x1e; // normal last code for the sounds for type 1
	if (!strncmp((char*)&Z80ROM[0x3e],"Ver 3.0 by MAKOTO",17)) {
	    // Search 7e: ld a,(hl)
	    // 32: ld (adr),a
	    // and 2 bytes further : 21: ld hl,adr2
	    // and adr2 is the target
	    // This new patern matches wakuwaku7 and probably some others
	    // since it's not dependant anymore on any address... !
	    // This includes galaxyfg, 3countb fatfury2, fatfury3...
	    UINT8 needle[3] = { 0x7e,0x32 };
	    int n;
	    n = 0x65;
	    do {
	       n = search(2,needle,n+1);
	    } while (n < 0x1000 && Z80ROM[n+2] != 0x21);
	    if (n < 0x1000) n += 3;

	    if (n >= 0x1000) {
		needle[0] = 0x3f; // search for fe3f then (2nd form !)
		needle[1] = 0xfe;
		// This 2nd form is for fightfev
		n = search(2,needle,0x66);
		if (n >= 0x1000) {
		    needle[0] = 0x25; // magdrop3
		    n = search(2,needle,0x66);
		}
		if (n < 0x1000) {
		    printf("found fe%x at %x\n",needle[0],n);
		    n -= 7;
		    if (Z80ROM[n-1] != 0x21) {
			printf("but not 21 !\n");
			type = 0;
			return;
		    }
		}
	    }
	    if (n < 0x1000) {
		type = 2;
		printf("found type 2 at adr = %x\n",n);
		adr = ReadWord(&Z80ROM[n]);
	    } else {
		type = 0;
		printf("not found type 2\n");
	    }
	} else if (!strncmp((char*)&Z80ROM[0x101],"SYSTEM",6)) {
	    type = 3; // sonicwi2/3
#if VERBOSE
	    printf("assoc: sonicwi2/3 detected\n");
#endif
	} else if (!strncmp((char*)&Z80ROM[0x3e],"Ver 2.0",7) ||
		!strncmp((char*)&Z80ROM[0x3e],"Ver 1.5",7) ||
		!strncmp((char*)&Z80ROM[0x3e],"Ver 8.3",7)) {
	    // Search for fe3b, a ld ld,adr is 6 bytes before
	    // This includes mutnat, alpham2, blazstar, gpilots, kotm...
	    // fe25 is for lans2004
	    UINT8 needle[2] = { 0x3b,0xfe };
	    if (!strncmp((char*)&Z80ROM[0x3e],"Ver 8.3",7))
		needle[0] = 0x25;
	    int n = 0x65;
	    type = 0;
	    while ((n = search(2,needle,n+1)) < 0x1000) {
		printf("found fe%x at %x\n",needle[0],n);
		if (Z80ROM[n-8] == 0x21) {
		    type = 2;
		    adr = ReadWord(&Z80ROM[n-7]);
		    printf("found type 2 at adr = %x -> %x\n",n-7,adr);
		    break;
		}
	    }
	} else if (!strncmp((char*)&Z80ROM[0x3e],"Sound Driver Ver 0.1 ",21) ||
		!strncmp((char*)&Z80ROM[0x3e],"Sound Driver Ver 0.0 ",21)) {
	    adr = 0x14f;
	    err = "kof96";
	    type = 1;
	} else if (!strncmp((char*)&Z80ROM[0x3e],"Sound Driver Ver 1.1 ",21)) {
	    adr = 0x17d;
	    err = "kof97";
	    type = 1;
	} else if (!strncmp((char*)&Z80ROM[0x3e],"Sound Driver(ROM)Ver 1.9 00/03/22",33)) {
	    adr = 0x184;
	    err = "kof2k";
	    type = 1;
	    end_sound_codes = 0x1f;
	} else if (!strncmp((char*)&Z80ROM[0x3E],"Sound Driver(ROM)Ver 1.7",24) ||
		!strncmp((char*)&Z80ROM[0x3E],"Sound Driver(ROM)Ver 1.8",24)) {
	    adr = 0x184;
	    err = "kof98/garou";
	    type = 1;
	} else if (!strncmp(current_game->main_name,"mslug",5))
	    type = 4; // mslug, except mslug4/5 (lowest priority)
	if (type == 1) {
	    // The type 1 are all garou variants, but with a sound table at
	    // different adresses. The funny thing is that even with the rom
	    // signature, we have to double check that we really get what we
	    // expect...
	    if (Z80ROM[adr-1] != 0x21) {
		type = 0;
		printf("%s variant not recognized\n",err);
		return;
	    }
	    adr = ReadWord(&Z80ROM[adr]);
	}
    } else if (kind == 2)
	type = 10; // gunbird
    else if (kind == 3) // bublbobl
	type = 11;
    if (type == 1) mode = MUSIC;
    if (type) {
	prepare_cdda_save(ASCII_ID('T','R','C','K'));
	AddSaveData(ASCII_ID('T','R','C','A'),(UINT8*)&active,sizeof(active));
    }
}

int get_asso_loop(int cmd) {
    return loop[cmd];
}

void set_asso_loop(int cmd, int lp) {
    loop[cmd] = lp;
}

int get_assoc_adr() {
    return adr;
}

int get_assoc_type() {
    return type;
}

char* get_assoc(int cmd) {
    return track[cmd];
}

void assoc(int cmd, char *t) {
    if (!track[cmd])
	if (!(track[cmd] = malloc(FILENAME_MAX+1))) return;
    strncpy(track[cmd],t,FILENAME_MAX);
    track[cmd][FILENAME_MAX] = 0;
    use_music = 1;
}

void del_assoc(int cmd) {
    if (track[cmd]) {
	free(track[cmd]);
	track[cmd] = NULL;
	loop[cmd] = 0;
    }
}

void save_assoc(char *section) {
    int cmd;
    raine_clear_config_section(section);
    for (cmd=1; cmd<256; cmd++)
	if (track[cmd]) {
	    char key[5];
	    sprintf(key,"%d",cmd);
	    raine_set_config_string(section,key,track[cmd]);
	    if (get_asso_loop(cmd)) {
		char name[20];
		sprintf(name,"loop%d",cmd);
		raine_set_config_int(section,name,get_asso_loop(cmd));
	    }
	}
}

void clear_assoc() {
    type = 0;
    int cmd;
    for (cmd=1; cmd<256; cmd++)
	if (track[cmd]) {
	    del_assoc(cmd);
	}
}

void load_assoc(char *section) {
    int cmd;
    for (cmd=1; cmd<256; cmd++) {
	char key[5];
	sprintf(key,"%d",cmd);
	char *s = raine_get_config_string(section,key,NULL);
	if (s) {
	    assoc(cmd,s);
	    char name[20];
	    sprintf(name,"loop%d",cmd);
	    int loop = raine_get_config_int(section,name,0);
	    set_asso_loop(cmd,loop);
	}
    }
}

static void mute_song() {
    // It's quite a hassle to change the 2 variables together, but on neocd
    // active != cdda.playing since they are started by the game itself !
#if VERBOSE
    printf("mute song mode %d\n",mode);
#endif
    active = 0;
    cdda.playing = CDDA_STOP;
}

int handle_sound_cmd(int cmd) {
#if VERBOSE
    printf("cmd %x mode %d\n",cmd,mode);
#endif
    if (disable_assoc || !type) return 0;
    switch (type) {
    case 4:
	// all the mslug games support sound modes. The default is MUSIC after
	// a reset or command 0. Command 3 sets MUSIC mode. Command $11 sets
	// sounds mode, and there are some other unknown commands < 0x20
	// This could get extremely messy if each games had its own mode
	// numbers, but apparently it's not the case for most of them at least.
	if (cmd == 0 || cmd == 3) {
	    mode = MUSIC;
	} else if (cmd < 0x20 && cmd != 2) {
	    mode = SOUND;
	}
	if (mode == SOUND) return 0;
	if (active && (cmd == 1 || cmd == 3 || cmd == 2 || cmd >= 0x20))
	    mute_song();
	break;
    case 3: // sonicwi2 / sonicwi3
	if (active && (cmd == 3 || (cmd >= 0x20 && cmd < Z80ROM[0x30d])))
	    mute_song();
	if (cmd < 0x20 || cmd >= Z80ROM[0x30d])
	    return 0; // less verbose in debug mode !
	break;
    case 2: // galaxyfg
	if (cmd == 3) { // immediate reset
	    if (active)
		mute_song();
	    mode = SOUND;
	    return 0;
	}
	if (mode == EAT_TWO) {
	    mode = ONE_SOUND;
	    return 0;
	} else if (mode == ONE_SOUND) {
	    mode = MUSIC;
	    return 0;
	}


	if (mode == FADEOUT) {
	    // 0x10 stops it
	    // 0x11 takes about 8s
	    // 4 takes about 28s !
	    // 0x30 takes about 3.5s
	    double time;
	    if (cmd == 0x10)
		mute_song();
	    else {
		if (cmd >= 0x11)
		    time = 8.0*0x11/cmd;
		else if (cmd >= 4 && cmd <= 0x10)
		    time = 8.0*0x10/cmd;
		if (is_current_game("wakuwak7")) {
		    /* Well to adapt to the saturn audio tracks we need about
		     * 3s more. Then these tracks have a recorded fadeout so the
		     * 2 effects add. There is not much difference between
		     * 3.0 and 4.0 here, I'll leave 4 to have more margin */
		    time = 4.0;
		}
		if (active)
		    start_music_fadeout(time);
	    }
	    mode = MUSIC;
	    return 0;
	}
	int no_return = 0;
	if (cmd == 4 || cmd == 5 || cmd == 0x10) {
	    // if music is playing then 4 stops it immediately
	    // 5 is fading on the currently playing note !slow)
	    mode = SOUND; // all commands after this are eaten, maybe for sound?
	    if (active)
		mute_song();
	} else if (cmd == 7 || cmd == 8) mode = MUSIC;
	else if (cmd == 0xa)
	    mode = FADEOUT;
	// b, c, d are ignored
	// e slows down music until the next part where it takes back its
	// normal speed -> impossible to emulate !
	else if (cmd == 0x14 && is_current_game("wakuwak7"))
	    mode = EAT_TWO;
	else if (Z80ROM[adr + cmd] == 1)
	    // Note : 1a and 1c and 1e are those which really output sound the
	    // others just eat the following byte (for wakuwak7)
	    // I assume the 1 means they eat 1 byte here, but I am not certain
	    mode = ONE_SOUND;
	else // all the others are ignored
	    no_return = 1;
	if (!no_return)
	    return 0;
	if (active && Z80ROM[adr + cmd] == 2)
	    mute_song();
	else if (Z80ROM[adr + cmd] != 2)
	    return 0; // return if it's not a song
	break;
    case 1: // garou
	// Garou has modes + interruptable songs !
	if (mode == ONE_SOUND) {
	    // Eats the next byte as sound, then switch to music
	    mode = MUSIC;
	    return 0;
	} else if (mode == FADEOUT) {
	    // argument is probably the speed of the fadeout, but no idea
	    // how it works exactly...
	    mode = MUSIC;
	    if (cmd) {
#if 1
		/* This is extremely approximated, but I can't get the precise
		 * calculation here, so I took a timer and tried to manually
		 * measure the time taken for the fadeout. With 10, it's a
		 * little more than 13s. With 32, it's a little more than 4s,
		 * But now apparently all the parts of the music don't decrease
		 * at the same time, so it's just an approximation, but it seems
		 * ok for now... */
		// 13s ssems to be only for kof97, kof98 and 99 are more around
		// 6.5 or 7s... !
		double time;
	       if (strstr(current_game->main_name,"kof97"))
		   time = 13.0*10/cmd;
	       else
		   time = 6.5*10/cmd;
	       if (active)
		   start_music_fadeout(time);
#else
		mute_song();
#endif
	    }
	    return 0;
	}
	if (cmd >= 6 && cmd <= 9) mode = MUSIC;
	else if ((cmd >= 0x15 && cmd <= end_sound_codes) &&
	       mode != ONE_SOUND) {
	    mode = ONE_SOUND;
	    return 0;
	} else if (cmd == 0xa) {
	    mode = FADEOUT;
	    return 0;
	} else if ((cmd >= 0x8 && cmd <= 0xc) || (cmd >= 0xf && cmd < 0x14)) {
	    // cmd 0xa is one_sound, handled just before
	    return 0; // these commands don't seem to do anything !
	} else if (cmd < 0x20 && cmd != 2 && cmd != 3 && cmd != 1)
	    mode = SOUND;
	if (mode == SOUND) return 0;
	if (active && (cmd == 4 || cmd == 3 || cmd == 1 ||
		    (cmd >= 0x20 && Z80ROM[adr + cmd - 0x20] == 2))) {
	    mute_song();
	}
	break;
    case 10:
	if (active && cmd < 0x40)  // gunbird
	    mute_song();
	else
	    return 0;
	break;
    }
    /* At this point all the sound commands have already returned, we are
     * left with something which is a song number in cmd */
    last_song = cmd;
#ifdef RAINE_DEBUG
    print_ingame(180,"playing %x track %s\n",cmd,track[cmd]);
#endif
    if (cmd > 1 && track[cmd]) {
	// An association to an empty track allows to just forbid playing this
	// MUSIC
#if VERBOSE
	printf("playing song %x track %s\n",cmd,track[cmd]);
#endif
	if (*track[cmd] && exists(track[cmd])) {
	    cdda.track = cmd; // for restoration
	    cdda.skip_silence = 1;
	    load_sample(track[cmd]);
	    cdda.loop = loop[cmd];
	    active = 1;
	} else if (*track[cmd])
	    printf("does not exist %s\n",track[cmd]);
	else
	    printf("no assoc for %x\n",cmd);
	return 1;
    }
    return 0;
}

