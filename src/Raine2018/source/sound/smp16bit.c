/******************************************************************************/
/*                                                                            */
/*     16-BIT SAMPLE PLAYBACK (odd samples - nichibutsu dac, cabal adpcm)     */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "sasound.h"
#include "smp16bit.h"
#include "debug.h"
#include "ingame.h"
#include "streams.h"

/*

todo:

- different sample rate for each sample, maybe also volume and panning?

*/

static DEF_INLINE int aLimit( int val, int max, int min )
{
  if ( val > max )
    val = max;
  else if ( val < min )
    val = min;
  return val;
}

static int ad_sample;
static int ad_index;

static int ad_index_table[8] =
{
  -1, -1, -1, -1, 2, 4, 6, 8
};

static int ad_offset_table[49] =
{
  0x0010, 0x0011, 0x0013, 0x0015, 0x0017, 0x0019, 0x001c, 0x001f,
  0x0022, 0x0025, 0x0029, 0x002d, 0x0032, 0x0037, 0x003c, 0x0042,
  0x0049, 0x0050, 0x0058, 0x0061, 0x006b, 0x0076, 0x0082, 0x008f,
  0x009d, 0x00ad, 0x00be, 0x00d1, 0x00e6, 0x00fd, 0x0117, 0x0133,
  0x0151, 0x0173, 0x0198, 0x01c1, 0x01ee, 0x0220, 0x0256, 0x0292,
  0x02d4, 0x031c, 0x036c, 0x03c3, 0x0424, 0x048e, 0x0502, 0x0583,
  0x0610
};

static void ad_decode(int ad_code)
{
  int ad_base;
  int ad_offset;

  ad_base   = ad_offset_table[ad_index];
  ad_offset = ad_base/8;

  if( ad_code&0x01 ) ad_offset += ad_base>>2;
  if( ad_code&0x02 ) ad_offset += ad_base>>1;
  if( ad_code&0x04 ) ad_offset += ad_base;
  if( ad_code&0x08 ) ad_offset  = 0 - ad_offset;

  ad_sample = aLimit( ad_sample + ad_offset , 0x7FF, -0x800 );
  ad_index = aLimit( ad_index + ad_index_table[ad_code&7], 48, 0 );
}

// Type 0 - adpcm (cabal)

void decode_sample_adpcm(UINT8 *src, UINT32 size, INT16 *dest, int volume)
{
   UINT32 ta;

   ad_sample = 0;
   ad_index = 0;

   for(ta=0;ta<size;ta++){
      ad_decode((src[ta]>>4)&0x0F);
      *dest++ = (INT16) aLimit((((ad_sample * 16) * volume)/16), 0x7FFF, -0x8000);
      ad_decode((src[ta]>>0)&0x0F);
      *dest++ = (INT16) aLimit((((ad_sample * 16) * volume)/16), 0x7FFF, -0x8000);
   }
}

// Type 1 - 8bit dac (nichibutsu)

void decode_sample_8bit(UINT8 *src, UINT32 size, INT16 *dest, int volume)
{
   UINT32 ta;

   ad_sample = 0;
   ad_index = 0;

   for(ta=0;ta<size;ta++){
      *dest++ = (INT16) aLimit(((((src[ta]-0x80) * 256) * volume)/16), 0x7FFF, -0x8000);
   }
}

SMP16Rec SMP16_entry[SMP16BF_MAX], *SMP16;

static int chip_max;
static int sample_len;
static int emu_rate;
static int stream[SMP16BF_MAX];

#define UPDATE_SHIFT (8)

/**************************************************/
/*    sh start                                    */
/**************************************************/

int SMP16buffer_sh_start( struct SMP16buffer_interface *intf )
{
  char buf[40];
  int ta, i;
  int rate;
  SMP16_ROM *rom;
  SMP16_SAMPLE *sample_decode;

  rate       = audio_sample_rate;
  chip_max   = intf->num;
  sample_len = rate / 60;
  emu_rate   = sample_len * 60;

  for( i = 0; i < chip_max; i++ ){

    SMP16_entry[i].rate    = intf->sample_rate[i];
    SMP16_entry[i].command = -1;
    SMP16_entry[i].add     = (UINT32) (((float)intf->sample_rate[i] / (float)emu_rate)*(1<<UPDATE_SHIFT));

    SMP16_entry[i].offset  = (UINT32) -1;
    SMP16_entry[i].req_len = 0;
    SMP16_entry[i].req_buf = NULL;

    // rom bank base pointers

    rom = intf->rom[i];

    // Calculate sample count

    ta=0;
    while(rom[ta].data){
       ta++;
    }
    SMP16_entry[i].samples = ta;

    // Make decode rom data

    sample_decode = (SMP16_SAMPLE *) malloc(SMP16_entry[i].samples * sizeof(SMP16_SAMPLE));

    SMP16_entry[i].sample_decode = sample_decode;

    // malloc error

    if(!sample_decode)
       SMP16_entry[i].samples = 0;

    // Decode them

    for(ta = 0; (UINT32)ta < SMP16_entry[i].samples; ta++){

       switch(rom[ta].type){
       case 0x00:

       sample_decode[ta].len  = (UINT32)  (rom[ta].size * 2);
       sample_decode[ta].data = (INT16 *) malloc(sample_decode[ta].len * 2);

       decode_sample_adpcm(rom[ta].data, rom[ta].size, sample_decode[ta].data, 24);

       break;
       case 0x01:

       sample_decode[ta].len  = (UINT32)  (rom[ta].size * 1);
       sample_decode[ta].data = (INT16 *) malloc(sample_decode[ta].len * 2);
       fprintf(stderr,"decode sample 8bit %d len %d\n",ta,sample_decode[ta].len);
       decode_sample_8bit(rom[ta].data, rom[ta].size, sample_decode[ta].data, 24);

       break;
       }

    }

    // Stream setup

    sprintf( buf, "SMP16 #%d", i );
    stream[i] = stream_init( buf, emu_rate, 16, i, SMP16buffer_UpdateOne );
  }

  return 0;
}

/**************************************************/
/*    sh end                                      */
/**************************************************/

void SMP16buffer_sh_stop( void )
{
  int ta,i;
  SMP16_SAMPLE *sample_decode;

  for(i = 0; i < chip_max; i++){

    sample_decode = SMP16_entry[i].sample_decode;

    for(ta = 0; (UINT32)ta < SMP16_entry[i].samples; ta++){

       if(sample_decode[ta].data) free(sample_decode[ta].data);

    }
    free(sample_decode);

  }

  chip_max = 0;
}

/**************************************************/
/*    request                                     */
/**************************************************/
void SMP16buffer_request( int num, int code )
{
   SMP16_SAMPLE *sample_decode;

   if( num >= chip_max ) return;

   SMP16 = &SMP16_entry[num];

   sample_decode = SMP16->sample_decode;

   if((sample_decode) && ((UINT32)code < SMP16->samples)){
      SMP16->req_buf = (INT16 *) (sample_decode[code].data);
      SMP16->req_len = (sample_decode[code].len) << UPDATE_SHIFT;
      SMP16->offset  = 0;
   }
   else{
      SMP16->req_buf = NULL;
   }

   if(!(SMP16->req_buf)){
      SMP16->offset = (UINT32) -1;
#ifdef RAINE_DEBUG
      print_ingame(120,"Now SMP16(%d) not samp[%02x]", num, code );
#endif
   }

}

/**************************************************/
/*    read status                                 */
/**************************************************/

// 0 = not playing
// 1 = playing

int SMP16buffer_status( int num )
{
  int ret;

  if( num >= chip_max ) return 0;

  ret = 0;

  SMP16 = &SMP16_entry[num];

  if( SMP16->offset != (UINT32) -1 ) ret |= 1;

  return ret;
}

/**************************************************/
/*    update                                      */
/**************************************************/

void SMP16buffer_UpdateOne( int num, INT16 *sp, int length )
{
   int data;

   if(!length) return;

   SMP16 = &SMP16_entry[num];

   do{
      data = 0;
      if(SMP16->offset != (UINT32) -1){
         data += *( SMP16->req_buf + (SMP16->offset >> UPDATE_SHIFT) );
         if( (SMP16->offset += SMP16->add) >= SMP16->req_len )
            SMP16->offset = (UINT32) -1;
      }
      *sp++ = aLimit( data, 32767, -32768 );
   }while(--length);
}

/**************** end of file ****************/
