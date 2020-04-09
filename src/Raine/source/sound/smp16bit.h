
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*     16-BIT SAMPLE PLAYBACK (odd samples - nichibutsu dac, cabal adpcm)     */
/*                                                                            */
/******************************************************************************/

#ifndef __SMP16_H__
#define __SMP16_H__

void decode_sample_adpcm(UINT8 *src, UINT32 size, INT16 *dest, int volume);
void decode_sample_8bit(UINT8 *src, UINT32 size, INT16 *dest, int volume);

#define SMP16BF_MAX     (2)
#define SMP16BF_CHANNEL (1)
#define SMP16BF_NUMBUF  (1)

typedef struct SMP16_ROM
{
   UINT8 *data;					// pointer to rom
   UINT32 size;					// size of rom
   UINT32 type;					// 0 - adpcm
} SMP16_ROM;

struct SMP16buffer_interface
{
   int num;					// number of chips
   int sample_rate[SMP16BF_MAX];		// rate for each chip
   SMP16_ROM *rom[SMP16BF_MAX];			// list of roms
};

typedef struct SMP16_SAMPLE
{
   UINT32 len;                  			// length (in samples?)
   INT16 *data;                        		// sample data (16 bit?)
} SMP16_SAMPLE;

typedef struct SMP16rec
{
  int rate;					// rate
  int command;
  unsigned int offset, req_len;
  signed short *req_buf;
  unsigned int add;
  UINT32 samples;				// sample count
  SMP16_SAMPLE *sample_decode;			// decoded info
} SMP16Rec;

int SMP16buffer_sh_start( struct SMP16buffer_interface *interface );
void SMP16buffer_sh_stop( void );
void SMP16buffer_request( int num, int code );
int  SMP16buffer_status( int num );
void SMP16buffer_UpdateOne( int num, INT16 *sp, int length );

#endif

/******************************************************************************/

#ifdef __cplusplus
}
#endif
