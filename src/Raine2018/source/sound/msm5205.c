/**************************************************************/
/*   MSM5205 (DARIUS ADPCM chip) control                      */
/**************************************************************/
/* Warning : don't EVER mix live_msm_decode with a static list *
 * of samples. live_msm_decode uses realloc on decode_area,    *
 * which would make the list of static samples invalid.        *
 * also, msm_live_decode is intended to be used with a single  *
 * msm chip, since it works on only the global variable        *
 * decode_area.                                                *
 **************************************************************/

#include "raine.h"
#include "sasound.h"
#include "msm5205.h"
#include "debug.h"
#include "ingame.h"
#include "streams.h"
#include "loadroms.h"

static struct MSM5205buffer_interface *intf;

// adr and length for the live_decode function
static UINT16 last_adr;
static INT16 last_len;

static int used_adpcm;

typedef struct M5205_SAMPLE
{
   UINT32 len;                  	// length (in samples?)
   INT16 *data;                  // sample data (16 bit?)
   int in_decode_area; // offset in decode_area when used
} M5205_SAMPLE;

struct msm5205buffer_chip
{
  int    sample_rate;
  int    now_reqcode;
  struct M5205_SAMPLE *samp;
  int    stream;
  int    req_len;
  INT16  *req_buf;
  int    req_vol;
  int    offset, add;
  INT16  *decode_area;
};

struct msm5205buffer_chip *MSM5205buffer_chip = NULL;
static int chip_num = 0;
static int emu_rate, buf_len;
static int sample_len;


#define UPDATE_SHIFT (8)


static INLINE int aLimit( int val, int max, int min ){
  if ( val > max )
    val = max;
  else if ( val < min )
    val = min;
  return val;
}

/**************************************************/
/*    decode control                              */
/**************************************************/
static int ad_sample;
static int ad_index;
static int ad_index_table[8] = {
  -1, -1, -1, -1, 2, 4, 6, 8
};
static int ad_offset_table[49]= {
  0x0010, 0x0011, 0x0013, 0x0015, 0x0017, 0x0019, 0x001c, 0x001f,
  0x0022, 0x0025, 0x0029, 0x002d, 0x0032, 0x0037, 0x003c, 0x0042,
  0x0049, 0x0050, 0x0058, 0x0061, 0x006b, 0x0076, 0x0082, 0x008f,
  0x009d, 0x00ad, 0x00be, 0x00d1, 0x00e6, 0x00fd, 0x0117, 0x0133,
  0x0151, 0x0173, 0x0198, 0x01c1, 0x01ee, 0x0220, 0x0256, 0x0292,
  0x02d4, 0x031c, 0x036c, 0x03c3, 0x0424, 0x048e, 0x0502, 0x0583,
  0x0610
};
static void ad_decode(int ad_code){
  int ad_base;
  int ad_offset;

  ad_base   = ad_offset_table[ad_index];
  ad_offset = ad_base/8;

  if( ad_code&0x01 )  ad_offset += ad_base>>2;
  if( ad_code&0x02 )  ad_offset += ad_base>>1;
  if( ad_code&0x04 )  ad_offset += ad_base;
  if( ad_code&0x08 )  ad_offset  = 0 - ad_offset;

  ad_sample = aLimit( ad_sample + ad_offset, 2047, -2048 );
  ad_index = aLimit( ad_index + ad_index_table[ad_code&7], 48, 0 );
}

/**************************************************/
/*    rom decode                                  */
/**************************************************/
static unsigned int err_table;
static int   decode_table_count;
static unsigned int *decode_table;
static int   decode_area_size;
static INT16 *decode_area;

void MSM5205_decode( int i, struct M5205_SAMPLE *samp, UINT8 *rom, UINT32 romsize, UINT32 start, UINT32 stop ){
  INT16 *ad_data;

  /**** table initial ****/
  samp->len        = 0;
  samp->data       = NULL;
  samp->in_decode_area = -1;
  /*************************************************/
  if( stop >= romsize )  stop = romsize;

#ifdef RAINE_DEBUG
  print_debug( "Now decode No.%d %08x-%08x\n", i, start, stop );
#endif
  if((start<romsize) && (stop<romsize)){	// Add Antiriad (Kick Off needs it)

    if( (start < stop) &&
	!(start == 0x00808080 || start == 0x00080808 ||
	  stop == 0x00808080 || stop == 0x00080808) ){
      /**** low limit address check ****/
      if( start < err_table )  err_table = start;
      samp->len = (stop - start)*2; /* get length (1byte = 2 data) */
      /**** new decode routine ****/
      {
	int  count, j;
	count = decode_table_count;
	for( j = 0; j < count; j++ ){
#if 0
	  if( start == *(decode_table + j*3) && stop <= *(decode_table + j*3 + 1) ){
#ifdef RAINE_DEBUG
	    print_debug( "Get decode table (%08x - %08x) [%08x-%08x]\n", start, stop, *(decode_table + j*3),  *(decode_table + j*3 + 1) );
#endif
	    samp->data = (void *)(*(decode_table + j*3 + 2)|0x80000000);
	    return;
	  }
#else
	  if( start >= *(decode_table + j*3) && stop <= *(decode_table + j*3 + 1) ){
#ifdef RAINE_DEBUG
	    print_debug( "Get decode table (%08x - %08x) [%08x-%08x]\n", start, stop, *(decode_table + j*3),  *(decode_table + j*3 + 1) );
#endif
	    samp->in_decode_area = ((*(decode_table + j*3 + 2) + (start - *(decode_table + j*3))*2));
	    return;
	  }
#endif
	}
	/**** decode start ****/
	*(decode_table + count*3)     = start;
	*(decode_table + count*3 + 1) = stop;
	*(decode_table + count*3 + 2) = decode_area_size;
	decode_table_count++;
#ifdef RAINE_DEBUG
	print_debug( "New decode Address (%02x:%08x - %08x)\n", count, *(decode_table + count*3), *(decode_table + count*3 + 1) );
#endif
	decode_area = realloc( decode_area, (decode_area_size + samp->len) * sizeof(INT16) );
	ad_data = (INT16 *)(decode_area + decode_area_size);
	samp->in_decode_area = (decode_area_size); /* rom offset */
	decode_area_size += samp->len;

	rom += start;
	ad_sample = 0;		/* work init */
	ad_index = 0;		/* work init */
	for( start = 0; start < samp->len/2; start++ ){
	  ad_decode( (*rom)>>4 );
	  *ad_data++ = (INT16)(ad_sample<<4);
	  ad_decode( (*rom)&0x0f );
	  *ad_data++ = (INT16)(ad_sample<<4);
	  rom++;
	}
      }
    }
  }
}

void decode_msm_sample(int chip, int sample) {
  struct msm5205buffer_chip *mp = MSM5205buffer_chip + chip;

  MSM5205_decode( sample, mp->samp + sample, intf->rom[chip], intf->romsize[chip], (intf->list[chip] + sample)->start, (intf->list[chip] + sample)->end );

}

/**************************************************/
/*    sh start                                    */
/**************************************************/
int MSM5205buffer_sh_start( struct MSM5205buffer_interface *interface ){
  int  num;
  int  i;
  char buf[2][40];
  const char *name[2];
  struct msm5205buffer_chip *mp;

  int rate = audio_sample_rate;

  last_adr = last_len = 0;
  used_adpcm = 0;

  intf = interface;
  chip_num = intf->num;
  sample_len  = rate / 60;
  emu_rate = sample_len * 60;

  if( chip_num > MSM5205BF_MAX )  return 1;
  if( (MSM5205buffer_chip = (struct msm5205buffer_chip *)malloc( sizeof(struct msm5205buffer_chip) * chip_num )) == NULL )
    return 1;

  for( num = 0; num < chip_num; num++ ){
    mp = MSM5205buffer_chip + num;
    mp->now_reqcode = -1;
    mp->sample_rate = intf->sample_rate[num];
    mp->req_len = 0;
    mp->req_vol = 0xff;
    mp->add = (int)(((float)mp->sample_rate / (float)rate)*(1<<UPDATE_SHIFT));

    if( intf->updatemode == MSM5205_MONO ){
      sprintf( buf[0], "MSM5205 Monaural" );
      mp->stream = stream_init( buf[0], emu_rate, 16, num, MSM5205buffer_UpdateOne );			// Antiriad: fix param num
      stream_set_pan( mp->stream, 0x80 );
      stream_set_volume( mp->stream, intf->volume[num] );
    }
    else{
      name[0] = buf[0];
      name[1] = buf[1];
      sprintf( buf[0], "MSM5205 Stereo Left" );
      sprintf( buf[1], "MSM5205 Stereo Right" );
      mp->stream = stream_init_multi( 2, name, emu_rate, 16, num, MSM5205buffer_Stereo_UpdateOne );	// Antiriad: fix param num
      stream_set_pan( mp->stream, 0x00 );
      stream_set_pan( mp->stream+1, 0xff );
      stream_set_volume( mp->stream, intf->volume[num] );
      stream_set_volume( mp->stream+1, intf->volume[num] );
    }
    mp->samp = (M5205_SAMPLE *)malloc( sizeof(M5205_SAMPLE) * intf->listsize[num] );
    decode_table = malloc( (sizeof(unsigned int) * intf->listsize[num] * 3) );
    if (intf->region[num]) {
	intf->rom[num] = load_region[intf->region[num]];
	intf->romsize[num] = get_region_size(intf->region[num]);
    }
    if( mp->samp != NULL && decode_table != NULL ){
      decode_table_count = 0;
      decode_area  = NULL;
      decode_area_size = 0;
      for( i = 0; i < intf->listsize[num]; i++ ){
	*(decode_table + i*3)     = 0xffffffff;
	*(decode_table + i*3 + 1) = 0xffffffff;
	*(decode_table + i*3 + 2) = 0x00000000;
      }
      for( i = 0; i < intf->listsize[num]; i++ )
	MSM5205_decode( i, mp->samp + i, intf->rom[num], intf->romsize[num], (intf->list[num] + i)->start, (intf->list[num] + i)->end );
      if( decode_area != NULL ){
	mp->decode_area  = decode_area;	/* stock work */
	for( i = 0; i < intf->listsize[num]; i++ ){
	  if( (mp->samp + i)->in_decode_area >= 0) {
	    (mp->samp + i)->data = decode_area + (mp->samp + i)->in_decode_area;
	  }
	  /**** 0x8xxxxxxx is use flag ****/
	}
      }
      else{
	mp->decode_area = NULL;
      }
      /**** end of decode ****/
    }
  }
  return 0;
}

/**************************************************/
/**************************************************/
void MSM5205buffer_sh_stop( void )
{
   int i;
   struct msm5205buffer_chip *mp;
   if( MSM5205buffer_chip == NULL )  return;
   for( i = 0; i < chip_num; i++ ){
      mp = MSM5205buffer_chip + i;
      if(mp->samp != NULL) free(mp->samp);			// Antiriad 06-04-99
      if(mp->decode_area != NULL) free(mp->decode_area);
      else if (chip_num == 0 && decode_area) {// dynamic allocation
	free(decode_area);
	decode_area = NULL;
      }
   }
   if(MSM5205buffer_chip != NULL) free(MSM5205buffer_chip);	// Antiriad 06-04-99
   MSM5205buffer_chip = NULL;
   if (decode_table) {
      free( decode_table );
      decode_table = NULL;
   }
   chip_num = 0;
}

/**************************************************/
/*    sh update                                   */
/**************************************************/
void MSM5205buffer_UpdateOne( int num, INT16 *buffer, int length )
{
  int  i, addr, bf_len;
  INT16 *sp =NULL, *dsp = NULL;
  struct msm5205buffer_chip *mp;

  if( num >= chip_num )  return;			// Antiriad: replace > with >=
  mp = MSM5205buffer_chip + num;


  sp = (INT16 *)buffer;
  dsp = mp->req_buf;
  buf_len = length * 2;
  bf_len = length;

  if( mp->now_reqcode == -1 ){
    memset( buffer, 0, buf_len );
  } else{
    for( i = 0; i < bf_len; i++ ){
      addr = mp->offset>>UPDATE_SHIFT;
      if( addr >= mp->req_len ){
	memset( sp, 0, (bf_len - i)*2 );
	mp->now_reqcode = -1;		/* end ADPCM */
	break;
      }
      *sp++ = *(dsp + addr);
      mp->offset += mp->add;
    }
  }
}

/**************************************************/
/*    sh update                                   */
/**************************************************/
void MSM5205buffer_Stereo_UpdateOne( int num, INT16 **buffer, int length ){
  int  i, addr, bf_len;
  INT16 *sp = NULL, *sp2 = NULL, *dsp = NULL;
  int lv, rv;
  struct msm5205buffer_chip *mp;

  if( num >= chip_num )  return;			// Antiriad: replace > with >=
  mp = MSM5205buffer_chip + num;

  lv = mp->req_vol&0xf0;
  rv = (mp->req_vol&0x0f)<<4;
  buf_len = length * 2;

  sp  = (INT16 *)buffer[0];
  sp2 = (INT16 *)buffer[1];
  dsp = mp->req_buf;
  bf_len = buf_len / 2;

  if( mp->now_reqcode == -1 ){
    memset( sp, 0, bf_len*sizeof(short) );
    memset( sp2, 0, bf_len*sizeof(short) );
  } else{
    for( i = 0; i < bf_len; i++ ){
      addr = mp->offset>>UPDATE_SHIFT;
      if( addr >= mp->req_len ){
	memset(  sp, 0, (bf_len - i)*2 );
	memset( sp2, 0, (bf_len - i)*2 );
	mp->now_reqcode = -1;		/* end ADPCM */
	break;
      }
      *sp++  = (((int)*(dsp + addr)) * lv)>>8;
      *sp2++ = (((int)*(dsp + addr)) * rv)>>8;
      mp->offset += mp->add;
    }
  }
}

/**************************************************/
/*    ADPCM request                               */
/**************************************************/
void MSM5205buffer_request( int num, int code )
{
  struct msm5205buffer_chip *mp;

  if( num >= chip_num )  return;			// Antiriad: replace > with >=
  mp = MSM5205buffer_chip + num;

  if(! mp->samp )  return;					// Antiriad ??-??-99

  mp->now_reqcode = code;
  if (mp->samp[code].in_decode_area >= 0) {
    mp->req_buf = decode_area + mp->samp[code].in_decode_area;
  } else
    mp->req_buf = mp->samp[code].data;
  mp->req_len = mp->samp[code].len;
  mp->offset = 0;
}

/**************************************************/
/*    ADPCM pan request                           */
/**************************************************/
void MSM5205buffer_setpan( int num, int data )
{
  struct msm5205buffer_chip *mp;

  if( num >= chip_num )  return;			// Antiriad: replace > with >=
  mp = MSM5205buffer_chip + num;
  mp->req_vol = data;
}

/* This function tries to decode an adpcm sample in live. It should
 * be called from the function which sends the data byte to the msm5205
 * with in parameter where this data byte comes from (address and length)
 * If the sample has already been decoded then it's played directly.
 * If not then the decoding function is called appropriately.
 * It works only for the first msm5205 chip (for now).
 *
 * Usually, the data sent to the msm5205 is called from an nmi. The
 * primary goal of this function is to avoid to do all the work in 4000
 * nmis / second !
 */

extern UINT8 *Z80RAM; // mz80help

int live_msm_decode(UINT16 adr,INT16 len) {
  // returns 1 if the sample was actually started, 0 otherwise.
  if (len > 0) {
    if (adr <= last_adr || adr >= last_adr + last_len) {
      // the sample has changed...
      int i;
      struct msm5205_adpcm_list *list = intf->list[0];

      last_adr = adr;
      last_len = len;

      // did we already decode it ?
      for (i=0; i< used_adpcm; i++)
	if (list[i].start == adr)
	  break;
      if (i>= used_adpcm) {
	// it's a new sample !
	i = used_adpcm++;
	if (used_adpcm >= MAX_MSM_ADPCM) {
	  print_ingame(300,"ADPCM overflow. Please set a higher MAX_MSM_ADPCM\n");
	  i = --used_adpcm;
	} else {
	  list[i].start = adr;
	  list[i].end = adr+len;

	  decode_msm_sample(0,i);
	}
      }

      MSM5205buffer_request( 0, i );
      return 1;
    }
  }
  return 0;
}

void MSM5205_set_volume(int chip, int volume) {
  struct msm5205buffer_chip *mp = MSM5205buffer_chip + chip;
  stream_set_volume(mp->stream,volume);
}

/**************** end of file ****************/
