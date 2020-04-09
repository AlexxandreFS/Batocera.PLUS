
#ifdef __cplusplus
extern "C" {
#endif
/**************************************************************/
/*   MSM5205 (DARIUS ADPCM chip) control                      */
/**************************************************************/
#ifndef __MSM5205_H__
#define __MSM5205_H__

#define MSM5205BF_MAX     (2)

#define MSM5205_MONO    (0)
#define MSM5205_STEREO  (1)

#define MAX_MSM_ADPCM 31

struct msm5205_adpcm_list {
  unsigned int start, end;
};

struct MSM5205buffer_interface {
  int num;
  int sample_rate[MSM5205BF_MAX];
  int volume[MSM5205BF_MAX];
  struct msm5205_adpcm_list *list[MSM5205BF_MAX];
  int listsize[MSM5205BF_MAX];
  unsigned char *rom[MSM5205BF_MAX];
  unsigned int  romsize[MSM5205BF_MAX];
  int region[MSM5205BF_MAX];
  int updatemode;
};

void decode_msm_sample(int chip, int sample);
int MSM5205buffer_sh_start( struct MSM5205buffer_interface *interface );
void MSM5205buffer_sh_stop( void );

void MSM5205buffer_UpdateOne( int num, INT16 *buffer, int length );
void MSM5205buffer_Stereo_UpdateOne( int num, INT16 **buffer, int length );


void MSM5205buffer_request( int num, int code );
void MSM5205buffer_setpan( int num, int data );
int live_msm_decode(UINT16 adr,INT16 len);
void MSM5205_set_volume(int chip, int volume);

#endif
/**************** end of file ****************/

#ifdef __cplusplus
}
#endif
