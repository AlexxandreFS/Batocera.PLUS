/******************************************************************************/
/*									      */
/*			    SAMPLE SUPPORT FOR RAINE			      */
/*									      */
/*			  modified by Hiromitsu Shioya			      */
/* Allegro support : Emmanuel Anne.					      */
/*									      */
/******************************************************************************/
// define USE_COMPENS in streams.h if you want an audio buffer of the exact
// length of what it should be (does not seem to make much good).
//
// code totally broken also because get_voice_position returns
// values impossible to use (they jump too much).
// Maybe it will work with another allegro version (tested with 4.1.13).

#include <time.h>
#include "raine.h"
#include "sasound.h"
#include "games.h"
#include "debug.h"
#include "timer.h"
#include "profile.h" // fps

#define UINT unsigned int
#define DWORD int

int GameSound;
static UINT8 counter[MAX_STREAM_CHANNELS];

int RaineSoundCardTotal,
  RaineSoundCard;

/* Avoid to uncomment USE_8BITS unless you finish 8bit support... which is
    pretty useless nowdays ! */

//#define USE_8BITS 1

/*

dump channels (debug)

*/

//#define DUMP_CHANNELS

#ifdef DUMP_CHANNELS
FILE *stream_out[NUMVOICES];
#endif

SoundRec      *SndMachine = NULL, snd_entry;

/* audio related stuff */

static SAMPLE *lpWave[NUMVOICES];
static int hVoice[NUMVOICES];

// The "normal" version of PlayStream does not use samples nor voicexs.
// It just uses "streams" ! What a mess !

static int	   playing[NUMVOICES];
static UINT16	   *vout[NUMVOICES],*vend[NUMVOICES];

int	    audio_sample_rate;

static int reserved_channel = 0;

static int stream_buffer_max;

static int pause_sound;

void saCheckPlayStream( void );

void saSetVolume( int channel, int data )
{
    voice_set_volume(hVoice[channel],data);
}

void saSetPan( int channel, int data )
{
    voice_set_pan(hVoice[channel],data);
}

#include "streams.c"

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
     //int i;
     // This part is called for each frame, which *should* be 60
  // times/sec, but it can be less (if the game slows down)
      streams_sh_update();
   }

}

int enh_stereo = 0;

extern int max_mixer_volume;

/******************************************/
/*    setup sound			  */
/******************************************/
BOOL saInitSoundCard( int soundcard, int sample_rate )
{

   int i,id;
   /* install a digital sound driver */
     // Normally, soundcard =0 means no sound in raine.
     // I will try not to break this to keep compatibility with the other
     // sources...
   id = sound_card_id(soundcard);

   if (max_mixer_volume)
     set_volume_per_voice(0);

   reserve_voices(16,0); // found by nlx_doom
   if (install_sound(id, MIDI_NONE, NULL) != 0) {
     //set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error initialising sound system\n%s\n", allegro_error);
      RaineSoundCard = 0;
      return 0;
   }

   // a super mega bug in allegro, at least in my installation.
   /* Maybe it's a compilation bug (gcc bug) but I don't want to test a
      lib without the optimizations, so I'll leave this as is. I must
      initialise the sound driver twice or reserve_voices is simply ignored
      and I loose voices */
   remove_sound();

   if (max_mixer_volume)
     set_volume_per_voice(0);
   else
     set_volume_per_voice(-1);

   if (install_sound(id, MIDI_NONE, NULL) != 0) {
     //set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
      allegro_message("Error initialising sound system\n%s\n", allegro_error);
      RaineSoundCard = 0;
      return 0;
   }

   set_volume(255,-1);

   for( i = 0; i < NUMVOICES; i++ ){

      lpWave[i]  = 0;
      playing[i] = 0;

#ifdef DUMP_CHANNELS
      sprintf(s,"stream%02d.raw",i);
      stream_out[i] = fopen(s,"wb");
#endif
   }

   stream_buffer_max = STREAM_BUFFER_MAXB;

   //reserved_channel = 0;

   pause_sound = 0;		/* pause flag off */
   if(!init_sound_emulators()) {
     return FALSE;  // Everything fine
   }

   return TRUE;
}

/******************************************/
/*    setup sound			  */
/******************************************/

void init_sound(void)
{
  const SOUND_INFO *sound_src; // games/games.h
  int ta;

  sound_src = current_game->sound;

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
    voice_stop(hVoice[chan]);
    destroy_sample( lpWave[chan] );
    lpWave[chan] = 0;
    playing[chan] = 0;
    deallocate_voice(hVoice[chan]);
  }
}

void saDestroySound( int remove_all_resources )
{
   int i;

#ifdef RAINE_DEBUG
   print_debug("saDestroySound: Removing SEAL\n");
#endif

   //pause_raine_ym3812();

   if(remove_all_resources){
     saStopSoundEmulators();
   }
   for( i = 0; i < NUMVOICES; i++ ){
      saDestroyChannel(i);

#ifdef DUMP_CHANNELS
      fclose(stream_out[i]);
#endif

   }
   remove_sound();
#ifdef USE_COMPENS
   reset_streams();
#endif

#ifdef RAINE_DEBUG
   print_debug("saDestroySound: OK\n");
#endif
}

void sa_pause_sound(void)
{
   int i;

   pause_sound	    = 1;

   //pause_raine_ym3812();
   for( i = 0; i < NUMVOICES; i++ ){
     if (playing[i])
       voice_stop( hVoice[i] );
   }
}

void sa_unpause_sound(void)
{
  int i;
  pause_sound	   = 0;
   for( i = 0; i < NUMVOICES; i++ ){
     if (playing[i])
       voice_start( hVoice[i] );
   }
}

/*******************************************************************************************/
/*******************************************************************************************/
/******************************************/
/*    play samples			  */
/******************************************/

static int pos_counter[NUMVOICES];
unsigned short *reference;

void saPlayBufferedStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan ){
  /* This version works at low level, creating a sample, and following its
     advancement directly in the voice_position... */
  int i;
  unsigned short *dout,*dfin;
  signed short *din;
  //fprintf(stderr,"saPlayBuffer %d freq %d bits %d pan %d len %d\n",channel,freq,bits,pan,len);
  if( audio_sample_rate == 0 || channel >= NUMVOICES )	return;
  if( SndMachine == NULL )  return;
  if( !playing[channel] ){
#ifdef USE_COMPENS
    int fin = stream_buffer_max * freq * 2 / fps;
#else
    int fin = stream_buffer_max * len;
#endif
    if( lpWave[channel] ){
      destroy_sample( lpWave[channel] );
      lpWave[channel] = 0;
    }

    if (!(lpWave[channel] = create_sample(16,0,freq,fin/2))){
      lpWave[channel] = 0;
      return;
    }

    //	  memset( lpWave[channel]->data, 0, fin );
    dout=lpWave[channel]->data;
    dfin=(short*) (((char*)lpWave[channel]->data)+fin);
    // Fill the buffer with 0 (signed) in case the soundcards reads what
    // is after the sample...
    while (dout < dfin)
      *(dout++) = 0x8000;
    vend[channel] = dfin;
    counter[channel] = 0;

    hVoice[channel] = allocate_voice( lpWave[channel] );
    if (hVoice[channel]<0) {
      allegro_message("allocate_voice failed !\n");
      exit(1);
    }

    voice_set_playmode(hVoice[channel],PLAYMODE_LOOP);

    playing[channel] = 1;	/* use front surface */

    init_mixing_buff(len);

    /**** make sound temp. buffer ****/
    if (enh_stereo && SamplePan[channel] == PAN_LEFT)
      dout=(short*) (((char*)lpWave[channel]->data)+len*(MODEB_UPDATE_COUNT+1)); //+len*MODEB_UPDATE_COUNT);
    else
      dout=(short*) (((char*)lpWave[channel]->data)+len*MODEB_UPDATE_COUNT); //+len*MODEB_UPDATE_COUNT);
    din = ((signed short*)data);
    //	      memcpy( dout, din, len );
    for (i=0; i<len; i+=2){
      *(dout++) = *(din++)^0x8000;
    }

    update_recording(channel,data);

    if (dout ==dfin){
      dout=(short*) (((char*)lpWave[channel]->data));
    }
#ifdef DUMP_CHANNELS
    fwrite( lpWave[channel]->data+len*MODEB_UPDATE_COUNT, 1, len, stream_out[channel]);
#endif

    vout[channel] = dout;
    saSetVolume(channel,SampleVol[channel]);
    saSetPan(channel,SamplePan[channel]);
    voice_set_position(hVoice[channel],0);
    voice_start(hVoice[channel]);
    pos_counter[channel] = 0;
    reference = NULL;
  } else{
    int pos = voice_get_position(hVoice[channel]);
    static int last_pos;
    int th_pos;
    int count = (enh_stereo && SamplePan[channel] == PAN_LEFT ?
		 MODEB_UPDATE_COUNT + 1 : MODEB_UPDATE_COUNT);

    // this difference between the theorical position and the actual
    // position is because clearly the reported position is directly
    // dependant of when the sound driver updated the voice for the
    // last time. Luckily the difference is big only when the voice
    // starts. After starting it gets more or less updated when it
    // should, depending on external factors too like the cpu load.

    dout=vout[channel];
    th_pos = (dout - ((UINT16 *)lpWave[channel]->data)-
	      count*len/2);
    if (th_pos < 0) th_pos += stream_buffer_max * len/2;

    if (channel == 0) {
      static int nb1,nb2,moy1,moy2;
      if (!reference) {
	reference = vout[0];
	last_pos = pos;
	nb1 = nb2 = moy1 = moy2 = 0;
      }
      if (reference == vout[0] && pos != last_pos) { // constant, since base_len (streams.c) is constant
	printf("pos %d th %d diff %d\n",pos,th_pos,th_pos-pos);
	if (pos > th_pos) { // bad start, try again...
	  printf("try again\n");
	  for( i = 0; i < NUMVOICES; i++ ){
	    if (enh_stereo && SamplePan[i] == PAN_LEFT)
	      pos = th_pos - len/2*(MODEB_UPDATE_COUNT+1); //+len*MODEB_UPDATE_COUNT);
	    else
	      pos = th_pos - len/2*(MODEB_UPDATE_COUNT); //+len*MODEB_UPDATE_COUNT);
	    if (pos < 0) {
	      printf("pos forced at 0\n");
	      pos = 0;
	    }
	    voice_set_position(hVoice[i],0);
	    reference = NULL;
	  }
	}
	if (nb1 < 2) {
	  moy1 += pos - th_pos;
	  nb1++;
	} else if (nb2 < 2) {
	  moy2 += pos - th_pos;
	  nb2++;
	} else {
	  moy1 /= 2;
	  moy2 /= 2;
	  printf("variation %d moy1 %d moy2 %d\n",abs(moy1-moy2),moy1,moy2);
	  if (abs(moy1-moy2) > 50 && abs(moy1-moy2)<2000) {
	    if (moy2 > moy1) { // soundcard slower than streams
	      more_stream = 1; // one more time
	    } else {
	      more_stream = -1; // drop next frame
	    }
	  }
	  nb1 = 0;
	  nb2 = 0;
	}
      }
    }

    din = ((signed short*)data);
    dfin = vend[channel];
    //	  memcpy(dout,din,len);

    for (i=0; i<len; i+=2){
      *(dout++) = *(din++)^0x8000;
    }
    update_recording(channel,data);
    if (dout >=dfin){
      dout=(short*) (((char*)lpWave[channel]->data));

    }

#ifdef DUMP_CHANNELS

    fwrite( lpWave[channel]->data+len*s_pos, 1, len, stream_out[channel]);
#endif
    vout[channel] = dout;

  }
}

#ifdef USE_8BITS
/******************************************/
/*    play samples			  */
/******************************************/
void saPlayStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan ){
  // This one should leave most of the sync work to allegro
  int pos;
	void *buff; // position in the stream
  unsigned short *dout;
  signed short *din;
  int i;
  if (bits == 8) {
    fprintf(stderr,"error: Can't play 8 bits\n");
    // Just because I don't want to bother with this now.
    return;
  }
  if( audio_sample_rate == 0 || channel >= NUMVOICES )	return;
  if( SndMachine == NULL )  return;
  if( !playing[channel] ){
    if( stream[channel] ){
      stop_audio_stream(stream[channel]);
      free_audio_stream_buffer(stream[channel]);
      stream[channel] = NULL;
    }

    printf("playing %d at freq %d\n",channel,freq);
    if (!(stream[channel] = play_audio_stream(len,bits,0,freq,volume,pan))){
      return;
    }
    playing[channel] = 1;	/* use front surface */

    // Wait for the buffer to be ready...
    while (!(buff = get_audio_stream_buffer(stream[channel])));
    //print_debug("first stream entry. [%d:%d:%d:%d]\n", channel, len, freq, volume );

  }

  if (!(buff = get_audio_stream_buffer(stream[channel]))) {
    fprintf(stderr,"init stream impossible : buffer NULL\n");
    return;
  }
  //	fprintf(stderr,"len memcpy : %d\n",len);
  dout=buff;
  din = ((signed short*)data);
  for (i=0; i<len; i+=2)
    *(dout++) = *(din++)^0x8000;

  //fprintf(stderr,"set chanel vol = %d\n",volume);
}
#endif

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

/******************************************************************************/
/*									      */
/*			    SOUND CARD INFORMATION			      */
/*									      */
/******************************************************************************/

static char *sound_name_list[10];
char *sound_card_name( int num )
{
  _DRIVER_INFO *digi;
   int i;
   int id = sound_card_id(RaineSoundCard);

   sound_name_list[0] = "Silence";
   install_sound(id, MIDI_NONE, NULL);
   if (system_driver->digi_drivers)
      digi = system_driver->digi_drivers();
   else
      digi = _digi_driver_list;

   for (i=0; digi[i].driver; i++)
     {
       sound_name_list[i+1] = ((char*)((DIGI_DRIVER *)digi[i].driver)->name);
     }
   // Normally with allegro, the last driver is "No sound", at least until
   // 3.9.37 in linux. In raine, no sound is 0 which makes a little more
   // sense...
   // But allegro being allegro, they changed this lately, so we need to
   // make sure the last entry is really "No sound"
   if (strcmp(sound_name_list[i],"No sound"))
     i++; // In this case we want the last driver too...
   RaineSoundCardTotal = i;

   if (num<i) {
     return sound_name_list[num];
   } else return "???";


}

int sound_card_id( int i )
{
  _DRIVER_INFO *digi;

  if (!i)
    return 0;
  if (system_driver->digi_drivers)
    digi = system_driver->digi_drivers();
  else
    digi = _digi_driver_list;


  if (i<RaineSoundCardTotal) {
    DIGI_DRIVER *driver = digi[i-1].driver;
    if (driver) {
      return driver->id;
    }
  }
  return 0;
}

/******************************* END OF FILE **********************************/
