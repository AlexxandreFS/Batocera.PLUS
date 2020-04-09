#include "raine.h"
#include "sasound.h"
/* Because we are not ready yet to release this password... */
#include "savegame.h" // to be able to save sample status
#include "emudx.h"
#include "newmem.h"
#include <string.h>
#include "dxsmp.h"
#include "streams.h"
#include "zlib.h"
#include "wav.h"
#include "gui.h"
#include "files.h"

/* DX Samples : my first idea was to add these in sasound.c and to mix them
 * after
   the normal streams have been processed. Advantage : code very easy.
   Disadvantages : 1 version/sound driver, and not precise enough where you
   must have a big buffer for sdl (buggy sound driver in windows).  So here is
   the "generic" implementation. But it's not so generic : allegro is missing
   sample conversion functions (in fact it probably has them internally). So I
   can't convert the samples with allegro as easily, unless I copy the
   conversion code from the sdl source... For now allegro is used only in dos,
   so it does not seem very important.

   For now the old packfile format is still supported if SDL isn't defined,
   but there doesn't seem to be any reason to keep it... */

struct wave_spec {
  // to be saved
  int      pos;		/* Current play position */
  int volume,playing,loop;
};

struct private_data {
  int len;
  UINT8 *data;
};

static struct wave_spec* emudx_samples;
static struct private_data* sample_data;

// to be able to save them easily

int raine_nb_samples = 0;

static char dx_file[256];

void read_dx_file() {
  int i,err;
  char buff[80];
  unzFile dat;
  UINT8 *buffer;
  unz_file_info file_info;
/*   int start,end; */
/*   short *src; */

  if (!dx_file[0])
    return;
  if (raine_nb_samples && emudx_samples && sample_data) {
    return;
  }

  dat = unzOpen(dx_file);
  if (!dat) return;
  for (raine_nb_samples=1; raine_nb_samples<32; raine_nb_samples++) {
    sprintf(buff,"%d.wav",raine_nb_samples);
    err = unzLocateFile(dat,buff,2);
    if (err != UNZ_OK)
      break;
  }
  raine_nb_samples--;

  emudx_samples = (struct wave_spec*)AllocateMem((raine_nb_samples+1) * sizeof(struct wave_spec));
  AddSaveData(ASCII_ID('S','A','M','P'),
	      (UINT8*)emudx_samples,
	      (raine_nb_samples+1) * sizeof(struct wave_spec));

  sample_data = (struct private_data*)AllocateMem((raine_nb_samples+1)*sizeof(struct private_data));
  for (i=1; i<=raine_nb_samples; i++) {
    sprintf(buff,"%d.wav",i);
    unzLocateFile(dat,buff,2);

    err = unzOpenCurrentFile(dat);
    unzGetCurrentFileInfo(dat,&file_info,NULL,0,NULL,0,NULL,0);
    buffer = malloc(file_info.uncompressed_size);
    unzReadCurrentFile(dat,buffer,file_info.uncompressed_size);
    emudx_samples[i].pos = emudx_samples[i].playing = 0;
#ifdef SDL
  SDL_RWops *rw;
  unsigned int len_in_bytes;
  SDL_AudioCVT  wav_cvt;
  SDL_AudioSpec wave;
  UINT8 *wav_buffer;
    extern SDL_AudioSpec gotspec;
    if (!gotspec.freq) {
	/* Now read_dx_file is called before the soundcard init, so we
	 * must put sensible default values here... */
	gotspec.freq = audio_sample_rate;
	gotspec.channels = 2;
	gotspec.format = AUDIO_S16;
    }
    rw = SDL_RWFromMem(buffer, file_info.uncompressed_size);
    if (!SDL_LoadWAV_RW(rw,1,&wave,&wav_buffer,&len_in_bytes)) {
      printf("couldn't load sample %d: %s\n",i,SDL_GetError());
      exit(1);
    }
    unzCloseCurrentFile(dat);	// Is this needed when open failed?

    if (SDL_BuildAudioCVT(&wav_cvt,
			  wave.format, wave.channels, wave.freq,
			  gotspec.format, gotspec.channels,gotspec.freq) == -1) {
      printf("can't build converter\n");
      exit(1);
    }

    wav_cvt.buf = sample_data[i].data = AllocateMem(len_in_bytes*wav_cvt.len_mult);
    sample_data[i].len =len_in_bytes*wav_cvt.len_ratio;
    wav_cvt.len = len_in_bytes;
    memcpy(sample_data[i].data, wav_buffer, len_in_bytes);
    SDL_FreeWAV(wav_buffer);

    SDL_ConvertAudio(&wav_cvt);
#else
    convert_wav((char*)buffer,file_info.uncompressed_size,
	    (char**)&sample_data[i].data,&sample_data[i].len);
#endif
    free(buffer);
  }
  unzClose(dat);
}

static void dxsmp_update(int num, INT16 **buffer, int length)
{
  int nb;

  memset(buffer[0],0,length*2);
  memset(buffer[1],0,length*2);

  for (nb=1; nb<=raine_nb_samples; nb++) { // samples playing ?
    if (emudx_samples[nb].playing) {
      int i,len2 = length*4; // len = length in bytes
      signed short *din = (signed short *)&sample_data[nb].data[emudx_samples[nb].pos];
      int volume = emudx_samples[nb].volume;
      // printf("playing sample %d pos %d\n",nb,emudx_samples[nb].pos);
      if (emudx_samples[nb].pos + len2 > sample_data[nb].len) {
	len2 = sample_data[nb].len-emudx_samples[nb].pos;
	emudx_samples[nb].playing = 0;
      }
      emudx_samples[nb].pos += len2;
      if (!emudx_samples[nb].playing && emudx_samples[nb].loop) {
	emudx_samples[nb].playing = 1;
	emudx_samples[nb].pos = 0;
      }
      len2 /= 4;
      for (i=0; i<len2; i++) {
	INT16 left = *(din++)*volume/255;
	INT16 right = *(din++)*volume/255;
#ifdef RAINE_DEBUG
	INT32 sample = buffer[0][i]+left;
	if (sample > 0x7fff) {
	  printf("overflow left %x\n",sample);
	  sample = 0x7fff;
	} else if (sample < -0x8000) {
	  printf("underflow left %x\n",sample);
	  sample = -0x8000;
	}
	buffer[0][i] += sample;
	sample = buffer[1][i] + right;
	if (sample > 0x7fff) {
	  printf("overflow right %x\n",sample);
	  sample = 0x7fff;
	} else if (sample < -0x8000) {
	  printf("underflow right %x\n",sample);
	  sample = -0x8000;
	}
	buffer[1][i] += sample;
#else
	buffer[0][i] += left;
	buffer[1][i] += right;
#endif
      }
    }
  }
}


void raine_stop_sample(int sample) {
  if (sample > 0 && sample <= raine_nb_samples) {
    emudx_samples[sample].playing = 0;
  }
}

void raine_stop_samples() {
  int i;
  for (i=1; i<= raine_nb_samples; i++)
    emudx_samples[i].playing = 0;
}

void raine_play_sample(int sample, int volume) {
  if (sample > 0 && sample <= raine_nb_samples) {
    emudx_samples[sample].pos = 0;
    emudx_samples[sample].volume = volume;
    emudx_samples[sample].playing = 1;
    emudx_samples[sample].loop = 0;
  }
}

void raine_loop_sample(int sample, int volume) {
  if (sample > 0 && sample <= raine_nb_samples) {
    emudx_samples[sample].pos = 0;
    emudx_samples[sample].volume = volume;
    emudx_samples[sample].playing = 1;
    emudx_samples[sample].loop = 1;
  }
}

int dxsmp_sh_start(const struct dxsmpinterface *intf) {
  char *str;
  const char *stream_names[2] = { "DX Sample L", "DX Sample R"};

  if ((str = exists_emudx_file(intf->dx_name))) {
    unzFile dat;
    int vol[2];
    vol[0] = intf->mixing_level & 0xffff;
    vol[1] = intf->mixing_level >> 16;

    dat = unzOpen(str);
    if (!dat) {
      raine_nb_samples = 0;
      return 1;
    }
    unzClose(dat);
    strcpy(dx_file,str);
    read_dx_file();
    if (stream_init_multim(2, stream_names, vol, audio_sample_rate, 0, dxsmp_update) == -1)
      return 1;

    return 0;
  }
  return 1; // failure
}

void dxsmp_sh_stop() {
  int i;
  if (raine_nb_samples && emudx_samples) {
    for (i=1; i<=raine_nb_samples; i++) {
      FreeMem(sample_data[i].data);
    }
    FreeMem((UINT8*)emudx_samples);
    FreeMem((UINT8*)sample_data);
    sample_data = NULL;
    emudx_samples = NULL;
    raine_nb_samples = 0;
  }
  dx_file[0] = 0;
}

int is_dxsmp_playing(int sample) {
  return emudx_samples[sample].playing;
}
