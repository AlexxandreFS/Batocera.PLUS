#include "conf-sound.h"

#ifdef HAS_NEO
#ifndef	CDDA_H
#define CDDA_H
#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_SFX_VOLUME 60
#define DEFAULT_MUSIC_VOLUME 60

enum {
    CDDA_STOP = 0,
    CDDA_PLAY,
    CDDA_LOAD,
    CDDA_PAUSE
}; // possible values for cdda.playing

typedef struct {
  int playing,track,loop,pos,skip_silence;
} cdda_t;
extern cdda_t cdda;

extern int start_index, end_index;
extern int neocd_cdda_format;
extern int auto_stop_cdda,mute_sfx,mute_music;

void do_cdda( int command, int track_number_bcd);
void init_cdda();
void cdda_stop();
void prepare_cdda_save(UINT32 id);

#ifdef __cplusplus
}
#endif
#endif
#endif // HAS_NEO
