#include "driver.h"
#include <math.h>
#include "dac.h"
#include "sasound.h"
#include "streams.h"
#include <stdlib.h> // exit
#include <string.h>

static int channel[MAX_DAC];
static int output[MAX_DAC];
static int UnsignedVolTable[256];
static int SignedVolTable[256];

#define MY_BUFF_LEN 512
static INT16 my_buff[MY_BUFF_LEN];
static int my_output_len;

static void DAC_update(int num,INT16 *buffer,int length)
{
	INT16 out = output[num];
	/* The problem : with the new sound code relying entirely on sdl for
	 * the updates, the sound is not updated in sync with the cpus anymore
	 * with the consequence that sometimes the dac received 90 commands
	 * for one update, and next time 0, and then 90 again.
	 * So we need to keep a few dac commands for next time so that the
	 * sound is not too distorted... */
	if (my_output_len) {
	  int n,n2;
	  INT16 *buffend = buffer + length,next;
	  INT16 *bufstart = buffer;
	  int max = my_output_len/2;
	  if (max < 40) max = 40;
	  if (max > my_output_len-1) max = my_output_len-1;
	  for (n=0; n<max; n++) {
	      int len = (n+1)*length/(max)-(buffer-bufstart);
	    n2 = len;
	    out = my_buff[n];
	    next = my_buff[n+1];
	    while (n2) {
	      INT16 myout = out+(next-out)*(len-n2)/len;
	      *(buffer++) = myout;
	      n2--;
	    }
	  }
	  out = my_buff[my_output_len-1];
	  while (buffer < buffend) *(buffer++) = out; // normally useless now
	  if (my_output_len-1 > max) {
	      memcpy(&my_buff[0],&my_buff[max],(my_output_len-max)*sizeof(INT16));
	      my_output_len -= max;
	  } else {
	      my_output_len = 0;
	  }
	} else
	  while (length--) *(buffer++) = out;
}


void DAC_data_w(int num,int data)
{
	int out = UnsignedVolTable[data];

	if (output[num] != out)
	{
		/* update the output buffer before changing the registers */
		// stream_update(channel[num],0);
		output[num] = out;
		my_buff[my_output_len++] = out;
		if (my_output_len >= MY_BUFF_LEN) {
		  fprintf(stderr,"DAC overflow\n");
		  exit(1);
		}
	}
}


void DAC_signed_data_w(int num,int data)
{
	int out = SignedVolTable[data];

	if (output[num] != out)
	{
		/* update the output buffer before changing the registers */
		// stream_update(channel[num],0);
		output[num] = out;
		my_buff[my_output_len++] = out;
		if (my_output_len >= MY_BUFF_LEN) {
		  fprintf(stderr,"DAC overflow\n");
		  exit(1);
		}
	}
}


void DAC_data_16_w(int num,int data)
{
	int out = data >> 1;		/* range      0..32767 */

	if (output[num] != out)
	{
		/* update the output buffer before changing the registers */
		stream_update(channel[num],0);
		output[num] = out;
	}
}


void DAC_signed_data_16_w(int num,int data)
{
	int out = data - 0x8000;	/* range -32768..32767 */

	if (output[num] != out)
	{
		/* update the output buffer before changing the registers */
		stream_update(channel[num],0);
		output[num] = out;
	}
}


static void DAC_build_voltable(void)
{
	int i;


	/* build volume table (linear) */
	for (i = 0;i < 256;i++)
	{
		UnsignedVolTable[i] = i * 0x101 / 2;	/* range      0..32767 */
		SignedVolTable[i] = i * 0x101 - 0x8000;	/* range -32768..32767 */
	}
}


int DAC_sh_start(const struct DACinterface *intf)
{
	int i;


	DAC_build_voltable();

	for (i = 0;i < intf->num;i++)
	{
		char name[40];


		sprintf(name,"DAC #%d",i);
		channel[i] = stream_initm(name,intf->mixing_level[i],audio_sample_rate,
				i,DAC_update);

		if (channel[i] == -1)
			return 1;

		output[i] = 0;
	}

	return 0;
}


WRITE_HANDLER( DAC_0_data_w )
{
	DAC_data_w(0,data);
}

WRITE_HANDLER( DAC_1_data_w )
{
	DAC_data_w(1,data);
}

WRITE_HANDLER( DAC_0_signed_data_w )
{
	DAC_signed_data_w(0,data);
}

WRITE_HANDLER( DAC_1_signed_data_w )
{
	DAC_signed_data_w(1,data);
}
