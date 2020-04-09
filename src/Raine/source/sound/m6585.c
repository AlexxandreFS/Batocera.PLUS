/******************************************************************************/
/*                                                                            */
/*                  M6585 - ANOTHER ADPCM PLAYBACK CHIP :)                    */
/*                                                                            */
/******************************************************************************/

#include "raine.h"
#include "sasound.h"
#include "m6585.h"
#include "smp16bit.h"
#include "debug.h"
#include "ingame.h"
#include "streams.h"

static DEF_INLINE int aLimit( int val, int max, int min )
{
  if ( val > max )
    val = max;
  else if ( val < min )
    val = min;
  return val;
}

M6585Rec M6585_entry[M6585BF_MAX], *M6585;

static int chip_max;
static int sample_len;
static int emu_rate;
static int stream[M6585BF_MAX];

#define UPDATE_SHIFT (8)

/**************************************************/
/*    sh start                                    */
/**************************************************/

int M6585buffer_sh_start( struct M6585_interface *intf )
{
  char buf[40];
  int ta, i;
  int rate;
  M6585_ROM *rom;
  M6585_SAMPLE *sample_decode;

  rate       = audio_sample_rate;
  chip_max   = intf->num;
  sample_len = rate / 60;
  emu_rate   = sample_len * 60;

  for( i = 0; i < chip_max; i++ ){

    M6585_entry[i].rate    = intf->sample_rate[i];
    M6585_entry[i].add     = (UINT32) (((float)intf->sample_rate[i] / (float)emu_rate)*(1<<UPDATE_SHIFT));
    M6585_entry[i].offset  = (UINT32) -1;
    M6585_entry[i].req_len = 0;
    M6585_entry[i].req_buf = NULL;
    M6585_entry[i].current_bank = 0;

    // rom bank base pointers

    rom = intf->rom[i];

    // Calculate sample bank count

    ta=0;
    while(rom[ta].data){
       ta++;
    }
    M6585_entry[i].banks = ta;

    // Make decode rom data

    sample_decode = (M6585_SAMPLE *) malloc(M6585_entry[i].banks * sizeof(M6585_SAMPLE));

    M6585_entry[i].sample_decode = sample_decode;

    // malloc error

    if(!sample_decode)
       M6585_entry[i].banks = 0;

    // Decode them

    for(ta = 0; (UINT32)ta < M6585_entry[i].banks; ta++){

       sample_decode[ta].len  = (UINT32)   (rom[ta].size);
       sample_decode[ta].data = (UINT8 *) (rom[ta].data);

    }

    // Stream setup

    sprintf( buf, "M6585 #%d", i );
    stream[i] = stream_init( buf, emu_rate, 16, i, M6585buffer_UpdateOne );
  }

  return 0;
}

/**************************************************/
/*    sh end                                      */
/**************************************************/

void M6585buffer_sh_stop( void )
{
  int i;
  M6585_SAMPLE *sample_decode;

  for(i = 0; i < chip_max; i++){

    sample_decode = M6585_entry[i].sample_decode;

    if (sample_decode)
      free(sample_decode);

  }

  chip_max = 0;
}

static int ad_sample;
static int ad_index;

/**************************************************/
/*    rom bank                                    */
/**************************************************/

void M6585buffer_bank_write(int num, int bank)
{
   if( num >= chip_max ) return;

   M6585 = &M6585_entry[num];

   if((UINT32)bank >= M6585->banks){
#ifdef RAINE_DEBUG
      print_ingame(1200,"M6585(%d) Bank out of range:%02x", num, bank );
#endif
      return;
   }

   M6585->current_bank = bank;
}

/**************************************************/
/*    request                                     */
/**************************************************/

void M6585buffer_request(int num, int offset, int data)
{
   int ta,tb;

   M6585_SAMPLE *sample_decode;

   if( num >= chip_max ) return;

   M6585 = &M6585_entry[num];

   offset &= 7;

   M6585->command[offset] = data;

   if(offset==6){	// Trigger

   sample_decode = M6585->sample_decode;

   M6585->req_buf = NULL;

   ta=0;
   tb=0;

   if(sample_decode){
      ad_sample = 0;
      ad_index = 0;
      ta = ((M6585->command[2]<<16) | (M6585->command[1]<<8) | (M6585->command[0]<<0)) & 0x0FFFFF;
      tb = ((M6585->command[5]<<16) | (M6585->command[4]<<8) | (M6585->command[3]<<0)) & 0x0FFFFF;

      if( (tb > ta) &&
      ((UINT32)ta < sample_decode[M6585->current_bank].len) &&
      ((UINT32)tb < sample_decode[M6585->current_bank].len) ){

      M6585->req_buf = ((UINT8 *) (sample_decode[M6585->current_bank].data)) + ta;

      M6585->offset  = 0;

      M6585->req_len = tb - ta;

      M6585->req_len <<= 1;

      M6585->req_len <<= UPDATE_SHIFT;

      }

   }

   if(!(M6585->req_buf)){
      M6585->offset = (UINT32) -1;
      #ifdef RAINE_DEBUG
      print_ingame(1200,"M6585(%d) out of range: %06x %06x", num, ta, tb );
      #endif
   }
   else{
      /*#ifdef RAINE_DEBUG
      print_ingame(1200,"M6585(%d) %06x %06x", num, ta, tb );
      #endif*/
   }

   }
}

/**************************************************/
/*    read status                                 */
/**************************************************/

// 0 = not playing
// 1 = playing

int M6585buffer_status( int num )
{
  int ret;

  if( num >= chip_max ) return 0;

  ret = 0;

  M6585 = &M6585_entry[num];

  if( M6585->offset != (UINT32) -1 ) ret |= 1;

  return ret;
}

/**************************************************/
/*    update                                      */
/**************************************************/

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

void M6585buffer_UpdateOne( int num, INT16 *buffer, int length )
{
   int data,ta;
   INT16 *sp;

   if(!length) return;

   sp = (INT16 *) buffer;

   M6585 = &M6585_entry[num];

   do{
      data = 0;
      if(M6585->offset != (UINT32) -1){

         if( (M6585->offset + M6585->add) >= M6585->req_len ){
            M6585->offset = (UINT32) -1;
         }
         else{

         for(ta = (M6585->offset >> UPDATE_SHIFT); (UINT32)ta<((M6585->offset + M6585->add) >> UPDATE_SHIFT); ta++){

         if((ta&1)==0)
            ad_decode((M6585->req_buf[ta>>1]>>4)&0x0F);
         else
            ad_decode((M6585->req_buf[ta>>1]>>0)&0x0F);

         }

         M6585->offset += M6585->add;

         data += (((ad_sample * 16) * 80) / 16);

         }

      }
      *sp++ = aLimit( data, 0x7FFF, -0x8000 );
   }while(--length);
}

/**************** end of file ****************/
