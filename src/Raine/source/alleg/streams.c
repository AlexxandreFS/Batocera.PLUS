/* This file now contains all the general stream functions. It's one */
/* level higher than the low level driver functions which are called */
/* from here. */

#include <math.h>
#include "newmem.h"
#include "ingame.h"
#include "streams.h"
#include "palette.h"
#ifdef SDL
#include "sdl/SDL_gfx/SDL_gfxPrimitives.h"
#include "sdl/dialogs/messagebox.h"
#endif
#ifdef RAINE_DOS
#include "alleg/gui/rgui.h"
#endif
#include "blit.h" // GameBitmap
#include <unistd.h>

int recording =0,monitoring = 1;
static int mixing_buff_len;
static FILE *f_record = NULL;
static short *mixing_buff;

int SampleVol[MAX_STREAM_CHANNELS];
static int SamplePan[MAX_STREAM_CHANNELS];

static int stream_joined_channels[MAX_STREAM_CHANNELS],more_stream;
static char stream_name[MAX_STREAM_CHANNELS][40];
static void *stream_buffer[MAX_STREAM_CHANNELS];
static int stream_buffer_len[MAX_STREAM_CHANNELS];
static int base_len,base_len0; // base length of sample for 1 frame
static int remaining_samples[MAX_STREAM_CHANNELS]; // remaining samples to be played at the end
static int stream_sample_rate[MAX_STREAM_CHANNELS];
static int stream_sample_bits[MAX_STREAM_CHANNELS];
static int stream_buffer_pos[MAX_STREAM_CHANNELS];
static int stream_sample_length[MAX_STREAM_CHANNELS];	/* in usec */
static int stream_param[MAX_STREAM_CHANNELS];
static void (*stream_callback[MAX_STREAM_CHANNELS])(int param,INT16 *buffer,int length);
static void (*stream_callback_multi[MAX_STREAM_CHANNELS])(int param,INT16 **buffer,int length);

static int memory[MAX_STREAM_CHANNELS];
static int r1[MAX_STREAM_CHANNELS];
static int r2[MAX_STREAM_CHANNELS];
static int r3[MAX_STREAM_CHANNELS];
static int c[MAX_STREAM_CHANNELS];

#ifdef USE_COMPENS
// This compensation tries to remove the lack of precision on the length
// of the buffer for the samples when audio_sample_rate / fps is not an
// integer. It was not required when we forced resynchronisation everytime
// a voice was looping, but now that we know that calling voice_set_position
// produces clicks when it's called too often, we need this solution.
static int compensation, nb_frames, tmp_frames, tmp_compens;
#endif

#ifdef USE_8BITS
void osd_play_streamed_sample(int channel,signed char *data,int len,int freq,int volume, int pan){
#if USE_MODE
  if( !sound_stream_mode )  saPlayStreamedSampleBase( channel, (signed char *)data, len, freq, volume, 8, pan );
  else
#endif
    saPlayBufferedStreamedSampleBase( channel, (signed char *)data, len, freq, volume, 8, pan );
}
#endif

void osd_play_streamed_sample_16(int channel,signed short *data,int len,int freq,int volume, int pan){

#if USE_MODE
  if( !sound_stream_mode )  saPlayStreamedSampleBase( channel, (signed char *)data, len, freq, volume, 16, pan );
  else
#endif
    saPlayBufferedStreamedSampleBase( channel, (signed char *)data, len, freq, volume, 16, pan );
}

/*
signal >--R1--+--R2--+
              |      |
              C      R3---> amp
              |      |
             GND    GND
*/

/* R1, R2, R3 in Ohm; C in pF */
/* set C = 0 to disable the filter */
void set_RC_filter(int channel,int R1,int R2,int R3,int C)
{
	r1[channel] = R1;
	r2[channel] = R2;
	r3[channel] = R3;
	c[channel] = C;
}

void apply_RC_filter_8(int channel,signed char *buf,int len,int sample_rate)
{
	float R1,R2,R3,C;
	float Req;
	int K;
	int i;


	if (c[channel] == 0) return;	/* filter disabled */

	R1 = r1[channel];
	R2 = r2[channel];
	R3 = r3[channel];
	C = (float)c[channel] * 1E-12;	/* convert pF to F */

	/* Cut Frequency = 1/(2*Pi*Req*C) */

	Req = (R1*(R2+R3))/(R1+R2+R3);

	K = 0x10000 * exp(-1 / (Req * C) / sample_rate);

	buf[0] = buf[0] + (memory[channel] - buf[0]) * K / 0x10000;

	for (i = 1;i < len;i++)
		buf[i] = buf[i] + (buf[i-1] - buf[i]) * K / 0x10000;

	memory[channel] = buf[len-1];
}

void apply_RC_filter_16(int channel,signed short *buf,int len,int sample_rate)
{
	float R1,R2,R3,C;
	float Req;
	int K;
	int i;


	if (c[channel] == 0) {
	  // printf("filter disabled\n");
	  return;	/* filter disabled */
	}
	R1 = r1[channel];
	R2 = r2[channel];
	R3 = r3[channel];
	C = (float)c[channel] * 1E-12;	/* convert pF to F */

	/* Cut Frequency = 1/(2*Pi*Req*C) */

	Req = (R1*(R2+R3))/(R1+R2+R3);

	K = 0x10000 * exp(-1 / (Req * C) / sample_rate);

	buf[0] = buf[0] + (memory[channel] - buf[0]) * K / 0x10000;

	for (i = 1;i < len;i++)
		buf[i] = buf[i] + (buf[i-1] - buf[i]) * K / 0x10000;

	memory[channel] = buf[len-1];
}



void apply_volume_16( INT16 *buf, UINT32 len, int vol )
{
  // Normally, now that we have the same values as osd functions,
  // we should be abble to simply make a voice_set_volume here...
  // I keep this for the end !
  if(vol != VOLUME_MAX){	// Add [J3d!]: Small speedup

      if( vol != VOLUME_MIN){	// Add [J3d!]: Another speedup

      if(len){

      do{
         *buf = (INT16)((((INT32)*buf) * vol)>>8);
         buf++;
      }while(--len);

      }

      }
      else{
         memset(buf,0x00,len<<1);
      }

   }
}

void apply_volume_8( INT8 *buf, UINT32 len, int vol )
{
   if(vol != VOLUME_MAX){	// Add [J3d!]: Small speedup

      if( vol != VOLUME_MIN){	// Add [J3d!]: Another speedup

      if(len){

      do{
         *buf = (INT8)((((INT32)*buf) * vol)>>8);
         buf++;
      }while(--len);

      }

      }
      else{
         memset(buf,0x00,len);
      }

   }
}

int streams_sh_start(void)
{
	int i;


	for (i = 0;i < MAX_STREAM_CHANNELS;i++)
	{
		stream_joined_channels[i] = 1;
		stream_buffer[i] = 0;
	}

	return 0;
}

void end_recording() {
  int i;
  if (f_record) {
    // Write lengths for the wav file... Soooooo stupid !
    i = ftell(f_record); // position = length
    i-=8;
    fseek(f_record,4L,SEEK_SET);
    fwrite(&i,1,4,f_record);

    i-=36;
    fseek(f_record,40L,SEEK_SET);
    fwrite(&i,1,4,f_record);

    fclose(f_record);
    f_record = NULL;
  }
  recording = 0;
}

void streams_sh_stop(void)
{
  int i;

  for (i = 0;i < MAX_STREAM_CHANNELS;i++)
    {
      if(stream_buffer[i]) FreeMem(stream_buffer[i]);
      stream_buffer[i] = 0;
      remaining_samples[i] = 0;
    }
}

static void stream_update_channel(int channel, int samples) {
  if (stream_joined_channels[channel] > 1){
    INT16 *buf[MAX_STREAM_CHANNELS];
    int i;
    if (samples > 0){
#ifdef USE_8BITS
      if (stream_sample_bits[channel] == 16){
#endif
	for (i = 0;i < stream_joined_channels[channel];i++)
	  buf[i] = &((short *)stream_buffer[channel+i])[stream_buffer_pos[channel+i]];
#ifdef USE_8BITS
      } else {
	for (i = 0;i < stream_joined_channels[channel];i++)
	  buf[i] = &((char *)stream_buffer[channel+i])[stream_buffer_pos[channel+i]];
      }
#endif
      (*stream_callback_multi[channel])(stream_param[channel],buf,samples);
    }

#if SOFT_VOL
    // In hardware mode, no mixing is necessary :
    // volume & pan are set at the begining and that's all !
    if (stream_sample_bits[channel] == 16){
      for (i = 0;i < stream_joined_channels[channel];i++)
#ifndef __RAINE__
	apply_RC_filter_16(channel+i,stream_buffer[channel+i],stream_buffer_len[channel+i],stream_sample_rate[channel+i]);
#else
      apply_volume_16( stream_buffer[channel+i], stream_buffer_len[channel+i], SampleVol[channel+i] );
#endif
    } else {
      for (i = 0;i < stream_joined_channels[channel];i++)
#ifndef __RAINE__
	apply_RC_filter_8(channel+i,stream_buffer[channel+i],stream_buffer_len[channel+i],stream_sample_rate[channel+i]);
#else
      apply_volume_8( stream_buffer[channel+i], stream_buffer_len[channel+i], SampleVol[channel+i] );
#endif
    }
#endif // SOFT_VOL
  } else { // stream_joinded_channels
    if (samples > 0){
      void *buf;

      if (stream_sample_bits[channel] == 16)
	buf = &((short *)stream_buffer[channel])[stream_buffer_pos[channel]];
      else
	buf = &((char *)stream_buffer[channel])[stream_buffer_pos[channel]];
      (*stream_callback[channel])(stream_param[channel],buf,samples);
    }

#if SOFT_VOL
    if (stream_sample_bits[channel] == 16)
#ifndef __RAINE__
      apply_RC_filter_16(channel,stream_buffer[channel],stream_buffer_len[channel],stream_sample_rate[channel]);
#else

    apply_volume_16( stream_buffer[channel], stream_buffer_len[channel], SampleVol[channel] );
#endif
    else
#ifndef __RAINE__
      apply_RC_filter_8(channel,stream_buffer[channel],stream_buffer_len[channel],stream_sample_rate[channel]);
#else
    apply_volume_8( stream_buffer[channel], stream_buffer_len[channel], SampleVol[channel] );
#endif
#endif
  } // else if joined...
}

void streams_sh_update(void)
{
  int channel,i;
  int buflen;

#ifdef USE_COMPENS
  if (tmp_compens) {
    buflen++;
    tmp_compens--;
  }
  tmp_frames--;
  if (!tmp_frames) {
    tmp_compens = compensation;
    tmp_frames = nb_frames;
  }
#endif

  if (more_stream <= 0) {
    more_stream = 1;
    return;
  }
  while (more_stream>0) {
    more_stream--; // normally only 1 time
  /* update all the output buffers */
  for (channel = 0;channel < MAX_STREAM_CHANNELS;channel += stream_joined_channels[channel]){
    buflen = remaining_samples[channel];

    remaining_samples[channel] = base_len;

    if (stream_buffer[channel]) {
      if (buflen)
	stream_update_channel(channel, buflen);

      for (i = 0;i < stream_joined_channels[channel];i++)
	stream_buffer_pos[channel+i] = 0;

      // Now actually play these channels on the soundcard
#ifdef USE_8BITS
      if (stream_sample_bits[channel] == 16){
#endif
	for (i = 0;i < stream_joined_channels[channel];i++)
	  osd_play_streamed_sample_16(channel+i,stream_buffer[channel+i],
				      2*base_len,
				      stream_sample_rate[channel+i],
				      255, 128  );
#ifdef USE_8BITS
      } else {
	for (i = 0;i < stream_joined_channels[channel];i++)
	  osd_play_streamed_sample(channel+i,stream_buffer[channel+i],
				   base_len,
				   stream_sample_rate[channel+i],
				   255, 128  );
      }
#endif
    } // if (stream_buffer_channel)
  } // for...

  } // while (more_stream)
  if (!more_stream)
    more_stream = 1;
}

#ifdef USE_COMPENS
static void reset_streams() {
  // to be called just before starting playing a sound.
  tmp_compens = compensation - MODEB_UPDATE_COUNT;
  tmp_frames = nb_frames;
}
#endif

int stream_init(const char *name,int sample_rate,int sample_bits,
		int param,void (*callback)(int param,INT16 *buffer,int length))
{
  int channel;

  channel = saGetPlayChannels(1);

  stream_joined_channels[channel] = 1;

  strcpy(stream_name[channel],name);

#ifndef __RAINE__
  stream_buffer_len[channel] = sample_rate / Machine->drv->frames_per_second;
  /* adjust sample rate to make it a multiple of buffer_len */
  sample_rate = stream_buffer_len[channel] * Machine->drv->frames_per_second;
#else
  base_len = sample_rate / CPU_FPS;
  more_stream = 1;
  stream_buffer_len[channel] = base_len;
  remaining_samples[channel] = base_len;

#ifdef USE_COMPENS
  compensation = STREAM_BUFFER_MAXB * sample_rate / CPU_FPS -
    STREAM_BUFFER_MAXB * base_len;
  nb_frames = STREAM_BUFFER_MAXB;
  reset_streams();
#endif

  // Needs +1 to adjust more precisely to what the result should be !!!
  /* adjust sample rate to make it a multiple of buffer_len */
#ifdef ALLEGRO_SOUND
  /* This sample rate is used again in the allegro sound driver at leat.
     it allows voices to play at a different sample rate from the main sound card mixer
     I don't think the conversion is made in hardware but it seems very fast anyway */
  sample_rate = stream_buffer_len[channel] * CPU_FPS;
  /* If not in allegro, adjusting this is useless and wastes cpu time */
#endif

#endif

  if ((stream_buffer[channel] = AllocateMem((sample_bits/8)*(stream_buffer_len[channel]+4))) == 0)
		return -1;
	stream_sample_rate[channel] = sample_rate;
	stream_sample_bits[channel] = sample_bits;
	stream_buffer_pos[channel] = 0;
	if (sample_rate)
		stream_sample_length[channel] = 1000000 / sample_rate;
	else
		stream_sample_length[channel] = 0;
	stream_param[channel] = param;
	stream_callback[channel] = callback;
	return channel;
}


int stream_init_multi(int channels,const char **name,int sample_rate,int sample_bits,
		int param,void (*callback)(int param,INT16 **buffer,int length))
{
  int channel,i;


  channel = saGetPlayChannels(channels);

  stream_joined_channels[channel] = channels;

  for (i = 0;i < channels;i++)
    {
      strcpy(stream_name[channel+i],name[i]);
#ifndef  __RAINE__
      stream_buffer_len[channel+i] = sample_rate / Machine->drv->frames_per_second;
      /* adjust sample rate to make it a multiple of buffer_len */
      sample_rate = stream_buffer_len[channel+i] * Machine->drv->frames_per_second;
#else
  base_len = sample_rate / CPU_FPS;
  more_stream = 1;
  base_len0 = base_len;
  stream_buffer_len[channel+i] = base_len;

#ifdef USE_COMPENS
  compensation = STREAM_BUFFER_MAXB * audio_sample_rate / CPU_FPS -
    STREAM_BUFFER_MAXB * base_len;
  nb_frames = STREAM_BUFFER_MAXB;
  reset_streams();
#endif

#ifdef ALLEGRO_SOUND
  /* adjust sample rate to make it a multiple of buffer_len */
  sample_rate = stream_buffer_len[channel+i] * CPU_FPS;
#endif
#endif

      if ((stream_buffer[channel+i] = AllocateMem((sample_bits/8)*stream_buffer_len[channel+i]+4)) == 0)
	return -1;
      memset(stream_buffer[channel+i],0,(sample_bits/8)*stream_buffer_len[channel+i]);
      stream_sample_rate[channel+i] = sample_rate;
      stream_sample_bits[channel+i] = sample_bits;
      stream_buffer_pos[channel+i] = 0;
      if (sample_rate)
	stream_sample_length[channel+i] = 1000000 / sample_rate;
      else
	stream_sample_length[channel+i] = 0;
    }

  stream_param[channel] = param;
  stream_callback_multi[channel] = callback;

  return channel;
}

int stream_initm(const char *name,int mixing_level,int sample_rate,
		int param,void (*callback)(int param,INT16 *buffer,int length))
{
  int stream = stream_init(name,sample_rate,16,param,callback);
  stream_set_volume(stream,mixing_level & 0xff);
  stream_set_pan(stream,mixing_level >> 8);
  return stream;
}

int stream_init_multim(int channels,const char **name,int *mixing_level,int sample_rate,
		       int param,void (*callback)(int param,INT16 **buffer,int length))
{
  int i,stream = stream_init_multi(channels,name,sample_rate,16,param,callback);
  for (i=0; i<channels; i++){
    stream_set_volume(stream+i,mixing_level[i] & 0xff);
    stream_set_pan(stream+i,mixing_level[i] >> 8);
  }
  return stream;
}

void stream_update(int channel,int min_interval)	/* min_interval is in usec */
{
#if 0
  double frac = pos_in_frame();
  UINT32 samples = frac * base_len;
  int i;
  // printf("samples bruts %d/%d\n",samples,remaining_samples[channel]);
  if (remaining_samples[channel] < base_len) // already came here...
    samples -= (base_len - remaining_samples[channel]);
  if (!samples || !remaining_samples[channel]) return;
  if (samples > remaining_samples[channel])
    samples = remaining_samples[channel];
  remaining_samples[channel] -= samples;

  stream_update_channel(channel, samples);
  for (i = 0;i < stream_joined_channels[channel];i++)
    stream_buffer_pos[channel+i] += samples;
#endif

  // printf("playing %d samples, remaining %d/%d pos %g\n",samples, remaining_samples[channel], base_len,frac);

  // Does nothing
}

void stream_set_volume(int channel,int volume)
{
  /* My goal is now to have the same volume/pan values for streams and for
     osd low level functions... */
  SampleVol[channel] = volume;
  saSetVolume(channel,volume);
}


int stream_get_volume(int channel)
{
	return SampleVol[channel];
}


void stream_set_pan(int channel,int pan)
{
  SamplePan[channel] = pan & 0xff;
  saSetPan(channel,pan & 0xff);
}


int stream_get_pan(int channel)
{
	return SamplePan[channel];
}


const char *stream_get_name(int channel)
{
	if (stream_buffer[channel])
		return stream_name[channel];
	else return 0;	/* unused channel */
}

int get_stream_sample_rate(int channel)
{
  return stream_sample_rate[channel];
}

static int updated_recording;

void update_monitoring() {
    if ((recording && updated_recording)) {
	int i;
	int w = current_game->video->screen_x;
	int h = current_game->video->screen_y - 50;
	int pen = makecol(255,255,255);
	int border=current_game->video->border_size;
	if (monitoring) {
	    int h2 = h;
	    h -= 100;
	    for (i=0; i<mixing_buff_len; i+=2) {
		int x = i*w/mixing_buff_len;
		int y = mixing_buff[i]*50/32767;
		int y2 = mixing_buff[i+1]*50/32767;
		line(GameBitmap,x+border,h+border,x+border,h+y+border,pen);
		line(GameBitmap,x+border,h2+border,x+border,h2+y2+border,pen);
	    }
	} else
	    print_ingame(1,"Recording to wav...");
	if (!f_record) {
	    char path[1024];
	    sprintf(path,"%sraine_sound",dir_cfg.exe_path);
	    int l = strlen(path);
	    strcat(path,".wav");
	    int num = 0;
	    while (exists(path)) {
		sprintf(&path[l],"_%03d.wav",num);
		num++;
	    }
	    f_record = fopen(path,"wb");
	    if (f_record) {
		fwrite("RIFF",1,4,f_record);
		fwrite(&i,1,4,f_record); // length of the file -8 -> at the end
		fwrite("WAVE",1,4,f_record);

		fwrite("fmt ",1,4,f_record);
		i=16; fwrite(&i,1,4,f_record); //length of chunk (waste of space !)
		i=1;  fwrite(&i,1,2,f_record); // codec : pcm
		// if (mixing_stereo)
		i=2;
		fwrite(&i,1,2,f_record); // number of channels

		fwrite(&audio_sample_rate,1,4,f_record);
		// if (mixing_stereo)
		i = audio_sample_rate * 4;
		/* 	else */
		/* 	  i = audio_sample_rate * 2; */
		fwrite(&i,1,4,f_record); // bytes / second

		i=4; fwrite(&i,1,2,f_record); // block alignement ??!!!!
		i=16; fwrite(&i,1,2,f_record); // bits / sample

		fwrite("data",1,4,f_record);
		fwrite(&i,1,4,f_record); // size 2 (offset 40) = filesize - 44 ???
	    } else {
		char dir[1024];
		sprintf(dir,"Can't create %s",path);
		MessageBox("Error",dir,"OK");
		recording = 0;
	    }
	}

	updated_recording = 0;
#ifdef ALLEGRO_SOUND
	// update directly in the callback for sdl, it's sometimes called more
	// often than the video !
	if (f_record)
	    fwrite(mixing_buff,2,mixing_buff_len,f_record);
	/* This is useless in sdl since eveything is done in the sound handler */
	memset(mixing_buff,0,mixing_buff_len*2);
#endif
    }
}

void init_mixing_buff(int len) {
#if !defined(SDL) && !defined(SDL_SOUND)
  if (mixing_buff_len != len && mixing_buff) {
    free(mixing_buff);
    mixing_buff = NULL;
  }
  if (!mixing_buff) {
    // if (mixing_stereo) {
    mixing_buff = (short*)malloc(len*4); // keep some room at the end to be able to
    // copy directly the buffer updated by sdl
    mixing_buff_len = len;
    memset(mixing_buff,0,mixing_buff_len*2);
/*   } else { */
/*       mixing_buff = (short*)malloc(len); */
/*       mixing_buff_len = len/2; */
/*       memset(mixing_buff,0,mixing_buff_len*2); */
/*   } */
  }
#endif
}

void update_recording(int channel, signed char *data) {
  if (recording) {
    int volume = SampleVol[channel];
    signed short *din=((signed short*)data);
    int i;
/*     if (mixing_stereo) { */
      int vol_l = (SamplePan[channel]-255)*volume/255;
      int vol_r = (SamplePan[channel])*volume/255;
      // vol_l>>=1;
      // vol_r>>=1;
      for (i=0; i<mixing_buff_len; i+=2) {
	mixing_buff[i] += *(din)*vol_l/255;
	mixing_buff[i+1] += *(din++)*vol_r/255;
      }
/*     } else { */
/*       for (i=0; i<mixing_buff_len; i++) */
/* 	mixing_buff[i] += *(din++)*volume/255; */
/*     } */
  }
  updated_recording = 1;
}

/******************************************************************************/
/*									      */
/*			  VOLUME / PANNING CONTROL			      */
/*									      */
/******************************************************************************/

void saInitVolPan( void )
{
   int i;
   for( i = 0; i < MAX_STREAM_CHANNELS; i++ ){
      SampleVol[i] = VOLUME_MAX;
      SamplePan[i] = PAN_CENTRE;
   }
}

void saSetPanMulti( int num, int data )
{
   int	i;

   for( i = 0; i < stream_joined_channels[num]; i++ )
      stream_set_pan(num + i, data);
}
