#include "newmem.h"
#include "raine.h"
#include "sasound.h"

// wav conversion based on sdl code
// Actually their code is surprisingly simple and surprisingly fast and
// efficient, I guess the fft is not always the best solution for this problem.
// The idea is just to remove/copy samples when rate is doubled/halved

void convert_wav(unsigned char *buf, int len, char **dest, int *ldest)
{
  int chans = ReadWord(&buf[22]);
  int bits = ReadWord(&buf[34]);
  int rate = ReadLong(&buf[24]);
  len -= 44; // striping the header of 44 bytes, samples remaining
  float mult = 2.0/chans*16/bits*audio_sample_rate/rate;
  *ldest = len*mult;
  *dest = AllocateMem(*ldest);
  if (!*dest) {
      *ldest = 0;
      return;
  }
  if (chans == 2 && bits == 16 && rate == audio_sample_rate) {
      // no conversion needed, just copy
      memcpy(*dest,&buf[44],len);
      return;
  }
  int n = 0;
  buf += 44;
  UINT32 sample;
  if (bits == 8 && chans == 1) { // mono/8bit -> stereo/16 bit
      if (rate == audio_sample_rate/4) {
	  while (n < len) {
	      sample = (sample & 0xffff) | ((sample & 0xffff) << 16);
	      WriteLong(*dest+n*16,sample);
	      WriteLong(*dest+n*16+4,sample);
	      WriteLong(*dest+n*16+8,sample);
	      WriteLong(*dest+n*16+12,sample);
	      n++;
	  }
      } else if (rate == audio_sample_rate/2) {
	  while (n < len) {
	      sample = (buf[n]-0x80) << 8;
	      sample = (sample & 0xffff) | ((sample & 0xffff) << 16);
	      WriteLong(*dest+n*8,sample);
	      WriteLong(*dest+n*8+4,sample);
	      n++;
	  }
      } else if (rate == audio_sample_rate) {
	  while (n < len) {
	      sample = (buf[n]-0x80) << 8;
	      sample = (sample & 0xffff) | ((sample & 0xffff) << 16);
	      WriteLong(*dest+n*4,sample);
	      n++;
	  }
      } else if (rate == audio_sample_rate*2) {
	  len /= 2;
	  while (n < len) {
	      sample = (buf[n*2]-0x80) << 8;
	      sample = (sample & 0xffff) | ((sample & 0xffff) << 16);
	      WriteLong(*dest+n*4,sample);
	      n++;
	  }
      } else {
	  printf("conversion unknown !\n");
	  exit(1);
      }
  } else { // stereo 16 bits already
      if (rate == audio_sample_rate*2) {
	  len /= 8;
	  while (n < len) {
	      sample = ReadLong(buf+n*8);
	      WriteLong(*dest+n*4,sample);
	      n++;
	  }
      } else if (rate == audio_sample_rate*4) {
	  len /= 16;
	  while (n < len) {
	      sample = ReadLong(buf+n*16);
	      WriteLong(*dest+n*4,sample);
	      n++;
	  }
      } else {
	  printf("conversion unknown !\n");
	  exit(1);
      }
  }
}


