
#ifdef __cplusplus
extern "C" {
#endif
/*
 *  SAMPLE (ADPCM) SUPPORT FOR RAINE
 *  modified by Hiromitsu Shioya
 *  change SEAL library 09/20/98
 */

#ifndef _SASOUND_H
#define _SASOUND_H

#include <stdio.h>
#include "deftypes.h"

extern int GameSound;

#undef INLINE
#define INLINE DEF_INLINE

/*
 *  Volume Section
 */

#define VOLUME_MIN	(0)			// Minimum volume
#define VOLUME_MAX	(255)			// Maximum volume

#define _STATE_H // mame state.h compatibility !

/*
 *  Panning Section
 */

#define PAN_LEFT	(0)			// Left panning
#define PAN_CENTRE	(128)			// Central panning
#define PAN_RIGHT	(255)			// Right panning

/*
 *  Sample Control Section
 */

#define CPU_FPS 	(fps)			// Frames per second of emulated hardware


/* audio related stuff */
#define MAX_STREAM_CHANNELS 16
#define    NUMVOICES    (MAX_STREAM_CHANNELS)

// Config allegro only

extern int ventry[NUMVOICES];
extern int sound_stream_mode,enh_stereo;

enum {
  SOUND_STREAM_NORMAL = 0,
  SOUND_STREAM_WAIT
};

#ifndef SDL
extern int RaineSoundCardTotal;
#endif
extern int RaineSoundCard;

/**** add hiro-shi 10/30/98 ****/

extern int change_sample_rate;

extern int audio_sample_rate;
extern int recording,monitoring;

#define   SND_CONTROL_MAX   (3)

typedef struct soundrec
{
   int  first;					// 0 = Sound emulator not init; 1 = Sound emulators init
   int  init[SND_CONTROL_MAX];			// Emulator type (see inittype)
   void *intf[SND_CONTROL_MAX];			// Emulator specific interface
   int  control_max;				// Number of emulators in list
} SoundRec;

/**** pcm support ****/
#ifdef __RAINE__
extern UINT8 *PCMROM;			/* hiro-shi */
#endif

/************************************************/
/*    include some headers                      */
/************************************************/

#define HAS_YM2608  0
#include "conf-sound.h"

/*

do not modify this order without updating sound_chip_list[] in sasound.c as well

*/

enum inittype
{
#if HAS_YM2203
  SOUND_YM2203 = 0,
#endif
#if HAS_YM2151
  SOUND_YM2151S,
#endif
#if HAS_YM2151_ALT
  SOUND_YM2151J,
#endif
#if HAS_YM2610
  SOUND_YM2610,
#endif
#if HAS_YM2610B
  SOUND_YM2610B,
#endif
#if HAS_MSM5205_BUFF
  SOUND_MSM5205_BUFF,
#endif
#if HAS_MSM5232
  SOUND_MSM5232,
#endif
#if HAS_ADPCM
  SOUND_M6295,
#endif
#if HAS_AY8910
  SOUND_AY8910,
#endif
#if HAS_YM3812
  SOUND_YM3812,
#endif
  SOUND_SN76496,
#if HAS_YM2413
  SOUND_YM2413,
#endif
#if HAS_SMP16
  SOUND_SMP16,
#endif
#if HAS_M6585
  SOUND_M6585,
#endif
#if HAS_YMZ280B
  SOUND_YMZ280B,
#endif
#if HAS_ES5505
  SOUND_ES5505,
  SOUND_ES5506,
#endif
#if HAS_QSOUND
  SOUND_QSOUND,
#endif
#if HAS_YMF278B
  SOUND_YMF278B,
#endif
#if HAS_NAMCO
  SOUND_NAMCO,
#endif
#if HAS_X1_010
  SOUND_X1_010,
#endif
#if HAS_DAC
  SOUND_DAC,
#endif
#if HAS_DXSMP
  SOUND_DXSMP,
#endif
  SOUND_NONE,
};

/* volume level for YM2203 */
#define YM2203_VOL(FM_VOLUME,SSG_VOLUME) (((FM_VOLUME)<<16)+(SSG_VOLUME))

/* YM2151interface->volume optionaly macro */
/* #define YM3014_VOL(Vol,Pan) VOL_YM3012((Vol)/2,Pan,(Vol)/2,Pan) */
#define MIXER(level,pan) ((level & 0xff) | ((pan) << 8))
#define YM3012_VOL(LVol,LPan,RVol,RPan) (MIXER(LVol,LPan)|(MIXER(RVol,RPan) << 16))

typedef struct SOUND_CHIP
{
   char *name;			// name

   void (*shutdown)(void);	// //stop
} SOUND_CHIP;

extern struct SOUND_CHIP sound_chip_list[];

extern SoundRec      *SndMachine, snd_entry;

/**** prottype ****/
void saUpdateSound( int nowclock );
BOOL saInitSoundCard( int soundcard, int sample_rate );

char *get_sound_chip_name(UINT32 id);

void init_sound(void);

void saDestroySound( int remove_all_resources );
void saStopSoundEmulators(void);
int init_sound_emulators(void);

void saPlayBufferedStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan );

void saPlayStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan );

int saGetPlayChannels( int request );
void saResetPlayChannels( void );

void sa_pause_sound(void);
void sa_unpause_sound(void);

#ifndef RAINE_DOS
void load_sample(char *filename);
void init_samples();
void set_sample_pos(int pos);
void start_music_fadeout(double time);
#endif

void end_recording();

/******************************************************************************/
/*                                                                            */
/*                          'MAME' STREAMS INTERFACE                          */
/*                                                                            */
/******************************************************************************/
/* Notice : panning is not (yet) enabled... */
#define OSD_PAN_CENTER 0x80
#define OSD_PAN_LEFT   0x00
#define OSD_PAN_RIGHT  0xff

#define MIXER_PAN_CENTER OSD_PAN_CENTER
#define MIXER_PAN_LEFT OSD_PAN_LEFT
#define MIXER_PAN_RIGHT OSD_PAN_RIGHT

/*
 #define OSD_PAN_CENTER 0
 #define OSD_PAN_LEFT   1
 #define OSD_PAN_RIGHT  2
*/

/******************************************************************************/
/*                                                                            */
/*                       HIROSHI VOLUME-PANNING CONTROL                       */
/*                                                                            */
/******************************************************************************/

extern int SampleVol[MAX_STREAM_CHANNELS]; // used by the mixer in the gui

void sound_load_cfg();
void sound_save_cfg();

void saInitVolPan( void );

/******************************************************************************/
/*                                                                            */
/*                          SOUND CARD INFORMATION                            */
/*                                                                            */
/******************************************************************************/

char *sound_card_name(int num);
int sound_card_id( int i );

/******************************* END OF FILE **********************************/

#endif // _SASOUND_H

#ifdef __cplusplus
}
#endif
