
#ifdef __cplusplus
extern "C" {
#endif
#ifndef STREAMS_H
#define STREAMS_H

#define MODEB_UPDATE_COUNT (3)
#define STREAM_BUFFER_MAXB (20)

#define MAX_STREAM_CHANNELS 16

void set_RC_filter(int channel,int R1,int R2,int R3,int C);

int streams_sh_start(void);
void streams_sh_stop(void);
void streams_sh_update(void);

int stream_init(const char *name,int sample_rate,int sample_bits,
		int param,void (*callback)(int param,INT16 *buffer,int length));
int stream_init_multi(int channels,const char **name,int sample_rate,int sample_bits,
		int param,void (*callback)(int param,INT16 **buffer,int length));
/* These are the mame stream_init functions. By having both prototypes, I can
   avoid converting all the drivers using the old raine functions... */
int stream_initm(const char *name,int mixing_level,int sample_rate,
		int param,void (*callback)(int param,INT16 *buffer,int length));
int stream_init_multim(int channels,const char **name,int *mixing_level,int sample_rate,
		int param,void (*callback)(int param,INT16 **buffer,int length));
void stream_update(int channel,int min_interval);	/* min_interval is in usec */
void stream_set_volume(int channel,int volume);
int stream_get_volume(int channel);
void stream_set_pan(int channel,int pan);
int stream_get_pan(int channel);
const char *stream_get_name(int channel);
void streams_init_timers();
void saSetPanMulti( int num, int data );

#endif

#ifdef __cplusplus
}
#endif
