/******************************************************************************/
/*									      */
/*			    SAMPLE SUPPORT FOR RAINE			      */
/*									      */
/*			  modified by Hiromitsu Shioya			      */
/*			  change SEAL library 09/20/98			      */
/*									      */
/******************************************************************************/
// Avoid to use this thing in linux. I can be wrong, but apparently there is
// no way to decide wether to use signed or unsigned samples.
// And seal seems to be obliged to convert the samples in linux to match its
// default format. Too bad, it works really badly with looping voices...

#include <time.h>
#include "audio.h"
#include "raine.h"
#include "sasound.h"
#include "profile.h" // fps
#include "games.h"

#include <sys/time.h>

int GameSound;
static UINT8 counter[MAX_STREAM_CHANNELS];

int RaineSoundCardTotal,
  RaineSoundCard,enh_stereo;

// USE_8BITS is something from the old days of seal. Don't know if it works
//#define USE_8BITS 1

/*

dump channels (debug)

*/

//#define DUMP_CHANNELS

#ifdef DUMP_CHANNELS
FILE *stream_out[NUMVOICES];
#endif

/*

mame seal interface. syncs works better, but it is much slower, blame
seal or your pc for this. the sample rate seal streams play at is nearly
always different from the one it *should* be running at.

*/

SoundRec      *SndMachine = NULL, snd_entry;

/* audio related stuff */

HAC	    hVoice[NUMVOICES];
LPAUDIOWAVE lpWave[NUMVOICES];
int	    playing[NUMVOICES];
static UINT16	   *vout[NUMVOICES],*vend[NUMVOICES];

int	    SampleRate;
int	    audio_sample_rate;
int	    sound_emu_count;

static int reserved_channel = 0;

int sound_stream_mode = SOUND_STREAM_WAIT;

static int stream_buffer_max;

static int pause_sound;

void saSetVolume( int channel, int data )
{
  ASetVoiceVolume( hVoice[channel], data>>2 ); // 64 = 256/4
}

void saSetPan( int channel, int data )
{
  ASetVoicePanning( hVoice[channel], data );
}

/*******************************************************************************************/
/*  streams v35x									   */
/*******************************************************************************************/

#include "alleg/streams.c"

/*******************************************************************************************/
/*  sa???Sound										   */
/*******************************************************************************************/
/******************************************/
/*    update sound			  */
/******************************************/
void saUpdateSound( int nowclock )
{
   if( ! GameSound ) return;
   if( ! RaineSoundCard ) return;
   if( ! audio_sample_rate ) return;
   if( ! SndMachine ) return;

   if( nowclock ){

      streams_sh_update();
      AUpdateAudio();

   }
}

/******************************************************************************/
/*									      */
/*			    SOUND CARD INFORMATION			      */
/*									      */
/******************************************************************************/

static char *sound_name_list[16][60];
static int sound_id_list[16];

char *sound_card_name( int num )
{
   AUDIOINFO audio_info;
   AUDIOCAPS audio_caps;
   if (sound_name_list[1][0] == 0) { // init list
     int n;
     int id=0;
     AInitialize();
     for (n=0; n<0x200; n++) {
       audio_info.nDeviceId = n;
       audio_info.wFormat = AUDIO_FORMAT_16BITS | AUDIO_FORMAT_STEREO;
       audio_info.nSampleRate = audio_sample_rate;
       if (!AGetAudioDevCaps( audio_info.nDeviceId, &audio_caps )) {
	 sound_id_list[id] = n;
	 strncpy((char*)sound_name_list[id++],audio_caps.szProductName,60);
       }
     }
     RaineSoundCardTotal = id;
   }

   if (num>= 0 && num < RaineSoundCardTotal) {
     return (char*)sound_name_list[num];
   } else return "???";
}

int sound_card_id( int i )
{
  if (i >= 0 && i < RaineSoundCardTotal)
    return sound_id_list[i];
  return 0;
}

/******************************************/
/*    setup sound			  */
/******************************************/

static int modeb_count;
static int init_done = 0;

void set_mastervolume(int _attenuation)
{
	float volume;


	if (_attenuation > 0) _attenuation = 0;
	if (_attenuation < -32) _attenuation = -32;

	volume = 256.0;	/* range is 0-256 */
	while (_attenuation++ < 0)
		volume /= 1.122018454;	/* = (10 ^ (1/20)) = 1dB */

	ASetAudioMixerValue(AUDIO_MIXER_MASTER_VOLUME,volume);
}

BOOL saInitSoundCard( int soundcard, int sample_rate )
{
   AUDIOINFO audio_info;
   AUDIOCAPS audio_caps;
   if (init_done) return FALSE;

   int i;

   soundcard = sound_card_id(soundcard);

   if( AInitialize() != AUDIO_ERROR_NONE ){
      print_debug("saInitSoundCard(): Seal failed to initialize\n");
      audio_sample_rate = 0;
      RaineSoundCard = 0;
      return FALSE;
   }

   if( soundcard <= 0 ){		// no soundcard (not going to autodetect)
      print_debug("saInitSoundCard(): OK [No Card]\n");
      audio_sample_rate = 0;
      RaineSoundCard = 0;
      return TRUE;
   }

   modeb_count = MODEB_UPDATE_COUNT;

   // Set card id

   audio_info.nDeviceId = soundcard;

   // 16 bit only

   audio_info.wFormat = AUDIO_FORMAT_16BITS | AUDIO_FORMAT_STEREO;

   // Seal is crap, it clicks, it's slow, it's bugged (why are we ever using it?)

/*   if(audio_sample_rate>44098)
       // Don't know if it's still relevant with a patched seal
       // it seems faster with this, so I'll keep it.
       audio_sample_rate = 44098; */
   // Sample Rate

   audio_info.nSampleRate = audio_sample_rate;

   // Open audio

   int rc;
   if( (rc = AOpenAudio(&audio_info)) != AUDIO_ERROR_NONE ){
       char szText[1024];
       AGetErrorText(rc, szText, sizeof(szText) - 1);
      print_debug("saInitSoundCard(): Audio Initialization Failed: %s\n",szText);
      audio_sample_rate = 0;
      RaineSoundCard = 0;
      return FALSE;
   } else
       print_debug("AOpenAudio ok !\n");

   // Find out what seal chose for us

   AGetAudioDevCaps( audio_info.nDeviceId, &audio_caps );
   print_debug(
      "Sound - '%s' %d-bit %s %u Hz\n",
      audio_caps.szProductName,
      audio_info.wFormat & AUDIO_FORMAT_16BITS ? 16 : 8,
      audio_info.wFormat & AUDIO_FORMAT_STEREO ? "stereo" : "mono",
      audio_info.nSampleRate
   );

   // Update sample rate (incase seal chose a different one)
/*
   if(audio_info.nSampleRate != audio_sample_rate)
      audio_sample_rate = audio_info.nSampleRate;
*/
   // Open and allocate voices, allocate waveforms

   if( AOpenVoices(NUMVOICES) != AUDIO_ERROR_NONE ){
      print_debug("saInitSoundCard(): Voice Initialization Failed\n");
      audio_sample_rate = 0;
      return FALSE;
   }

   for( i = 0; i < NUMVOICES; i++ ){
      if( ACreateAudioVoice(&hVoice[i]) != AUDIO_ERROR_NONE ){
	  print_debug("saInitSoundCard(): Voice %d Creation Failed\n",i);
	  audio_sample_rate = 0;
	  return FALSE;
      }
      ASetVoicePanning( hVoice[i], PAN_CENTRE );
      lpWave[i]  = 0;
      playing[i] = 0;

#ifdef DUMP_CHANNELS
      sprintf(s,"stream%02d.raw",i);
      stream_out[i] = fopen(s,"wb");
#endif
   }

#ifdef RAINE_DOS
   AUpdateAudio();
#endif

   print_debug("saInitSoundCard(): SEAL initialize OK\n");

   /**** stream buffer mode ****/
   stream_buffer_max = STREAM_BUFFER_MAXB;

   //reserved_channel = 0;

   set_mastervolume(0);

   if(!init_sound_emulators()) {
       init_done = 1;
      return FALSE;
   }

   return TRUE;
}

/******************************************/
/*    setup sound			  */
/******************************************/

void init_sound(void)
{
   SOUND_INFO *sound_src;
   int ta;

   sound_src = (SOUND_INFO*)current_game->sound;

   if(sound_src){

   saStopSoundEmulators();

   for( ta = 0; ta < SND_CONTROL_MAX; ta++ ){
      SndMachine->init[ta] = SOUND_NONE;
      SndMachine->intf[ta] = NULL;
   }

   SndMachine->first = 0;
   SndMachine->control_max = 0;

   ta = 0;

   while(sound_src[ta].interface){

   SndMachine->init[ta] = sound_src[ta].type;
   SndMachine->intf[ta] = sound_src[ta].interface;

   ta++;

   }

   SndMachine->control_max = ta;

   GameSound = 1;

   }
}

/******************************************/
/*    destroy sound			  */
/******************************************/

void saDestroyChannel( int chan )
{
   if( lpWave[chan] ){
      AStopVoice( hVoice[chan] );
      ADestroyAudioData( lpWave[chan] );
      free( lpWave[chan] );
      lpWave[chan] = 0;
      playing[chan] = 0;
      ADestroyAudioVoice( hVoice[chan] );
   }
}

void saDestroySound( int remove_all_resources )
{
   int i;

   print_debug("saDestroySound: Removing SEAL\n");

   // pause_raine_ym3812();

   if(remove_all_resources) saStopSoundEmulators();

   for( i = 0; i < NUMVOICES; i++ ){
      saDestroyChannel( i );

      #ifdef DUMP_CHANNELS
      fclose(stream_out[i]);
      #endif

   }
   ACloseVoices();
   ACloseAudio();
   init_done = 0;
#ifdef USE_COMPENS
   reset_streams();
#endif
   print_debug("saDestroySound: OK\n");
}

void sa_pause_sound(void)
{
   pause_sound	    = 1;

   // pause_raine_ym3812();
#if 1
   // There is a remarquable bug in the win32 version of seal : voices can't
   // be stopped !!!
   saDestroySound(0);
#else
   for( i = 0; i < NUMVOICES; i++ ){
     if (playing[i])
       AStopVoice( hVoice[i] );
   }
#endif
}

void sa_unpause_sound(void)
{
  pause_sound	    = 0;
#if 1
  saInitSoundCard(RaineSoundCard,audio_sample_rate);
#else
  for( i = 0; i < NUMVOICES; i++ ){
    if (playing[i])
      AStartVoice(hVoice[i]);
  }
#endif
}

/*******************************************************************************************/
/*******************************************************************************************/
/******************************************/
/*    play samples			  */
/******************************************/

static int pos_counter[NUMVOICES];

void saPlayBufferedStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan ){
  // int i;
  unsigned short *dout,*dfin;
  signed short *din;
  if( audio_sample_rate == 0 || channel >= NUMVOICES )	return;
  if( SndMachine == NULL )  return;
  if( !playing[channel] ){
#ifdef USE_COMPENS
    int fin = stream_buffer_max * freq * 2 / fps;
#else
    int fin = stream_buffer_max * len;
#endif
    if( lpWave[channel] ){
      AStopVoice( hVoice[channel] );
      ADestroyAudioData( lpWave[channel] );
      free( lpWave[channel] );
      lpWave[channel] = 0;
    }
    if( (lpWave[channel] = (LPAUDIOWAVE)malloc(sizeof(AUDIOWAVE))) == 0 )  return;
    lpWave[channel]->wFormat	 = (bits == 8 ? AUDIO_FORMAT_8BITS :
    AUDIO_FORMAT_16BITS) | AUDIO_FORMAT_MONO | AUDIO_FORMAT_LOOP;
    lpWave[channel]->nSampleRate = freq;
    lpWave[channel]->dwLength	 = fin;
    lpWave[channel]->dwLoopStart = 0;
    lpWave[channel]->dwLoopEnd	 = fin-1;
    if( ACreateAudioData(lpWave[channel]) != AUDIO_ERROR_NONE ){
      free( lpWave[channel] );
      lpWave[channel] = 0;
      return;
    }
    dout=(unsigned short *)lpWave[channel]->lpData;
    dfin=(unsigned short*) (((char*)lpWave[channel]->lpData)+fin);
#if 1
    memset( dout, 0, fin );
    dout += fin/2;
#else
    // This code which should work in linux does not, because seal insists on
    // converting the sample format !
    while (dout < dfin)
      *(dout++) = 0x8000;
#endif
    vend[channel] = dfin;
    counter[channel] = 0;

    ASetVoicePosition(hVoice[channel],0);
    /**** make sound temp. buffer ****/

    init_mixing_buff(len);

    if (enh_stereo && SamplePan[channel] == PAN_LEFT)
      dout=(unsigned short*) (((char*)lpWave[channel]->lpData)+len*(MODEB_UPDATE_COUNT+1)); //+len*MODEB_UPDATE_COUNT);
    else
      dout=(unsigned short*) (((char*)lpWave[channel]->lpData)+len*MODEB_UPDATE_COUNT); //+len*MODEB_UPDATE_COUNT);
    din = ((signed short*)data);
#if 1
    memcpy( dout, din, len );
    dout += len/2;
#else
    //	      memcpy( dout, din, len );
    for (i=0; i<len; i+=2){
      *(dout++) = *(din++)^0x8000;
    }
#endif
    if (dout ==dfin){
      dout=(unsigned short*) (((char*)lpWave[channel]->lpData));
    }

    update_recording(channel,data);
    pos_counter[channel] = 0;
    playing[channel] = 1;	/* use front surface */
    vout[channel] = dout;
    // ASetVoiceFrequency( hVoice[channel], audio_sample_rate );
    saSetVolume( channel, SampleVol[channel]>>2 );
    saSetPan(channel,SamplePan[channel]);
    APlayVoice( hVoice[channel], lpWave[channel] );
  } else{
    long pos = 0;
    int th_pos;
    int count = (enh_stereo && SamplePan[channel] == PAN_LEFT ?
		 modeb_count + 1 : modeb_count);
    AGetVoicePosition(hVoice[channel],&pos);

    dout=vout[channel];
    th_pos = (dout - ((UINT16 *)lpWave[channel]->lpData)-
	      count*len/2);
    if (th_pos < 0) th_pos += stream_buffer_max * len/2;

    // if there is more than count frames between pos and th_pos, then
    // wait for the voice.
    if (pos < th_pos) {
      if (th_pos - pos < count * len/2) {
	more_stream = 0;
	return;
      }
    }
    din = ((signed short*)data);
    dfin = vend[channel];
#if 1
    memcpy( dout, din, len );
    dout += len/2;
#else
    for (i=0; i<len; i+=2){
      *(dout++) = *(din++)^0x8000;
    }
#endif
    update_recording(channel,data);
    if (dout >=dfin){
      dout=(unsigned short*) (((char*)lpWave[channel]->lpData));
    }
#ifdef DUMP_CHANNELS
    fwrite( lpWave[channel]->data+len*s_pos, 1, len, stream_out[channel]);
#endif
    vout[channel] = dout;

    // more than count frames of advance : more stream !
    pos -= count*len/2;
    if (pos > th_pos && pos > 0) {
      more_stream = 1;
    } else
      more_stream = 0;
/*     if (channel == 0) */
/*       fprintf(stderr,"end of frame %d more_stream %d\n",cpu_frame_count,more_stream); */
  }
}

/******************************************************************************/
/*									      */
/*			  SOUND CHANNEL ALLOCATION			      */
/*									      */
/******************************************************************************/

int saGetPlayChannels( int request )
{
   int ret_value = reserved_channel;
   reserved_channel += request;
   return ret_value;
}

void saResetPlayChannels( void )
{
   reserved_channel = 0;
}


/******************************* END OF FILE **********************************/

