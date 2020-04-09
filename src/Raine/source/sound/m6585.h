
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                  M6585 - ANOTHER ADPCM PLAYBACK CHIP :)                    */
/*                                                                            */
/******************************************************************************/

#ifndef __M6585_H__
#define __M6585_H__

#define M6585BF_MAX     (1)
#define M6585BF_CHANNEL (1)
#define M6585BF_NUMBUF  (1)

typedef struct M6585_ROM
{
   UINT8 *data;					// pointer to rom
   UINT32 size;					// size of rom
} M6585_ROM;

struct M6585_interface
{
   UINT32 num;					// number of chips
   UINT32 sample_rate[M6585BF_MAX];		// rate for each chip
   M6585_ROM *rom[M6585BF_MAX];			// list of roms
};

typedef struct M6585_SAMPLE
{
   UINT32 len;                  			// length (in samples?)
   UINT8 *data;                        		// sample data (16 bit?)
} M6585_SAMPLE;

typedef struct M6585rec
{
   UINT32 rate;					// rate
   UINT32 offset, req_len;
   UINT8 *req_buf;
   UINT8 command[8];
   UINT32 add;
   UINT32 banks;					// sample bank count
   UINT32 current_bank;				// current sample bank
   M6585_SAMPLE *sample_decode;			// decoded info
} M6585Rec;

int  M6585buffer_sh_start(struct M6585_interface *interface);
void M6585buffer_sh_stop(void);
void M6585buffer_bank_write(int num, int bank);
void M6585buffer_request(int num, int offset, int data);
int  M6585buffer_status(int num);
void M6585buffer_UpdateOne( int num, INT16 *buffer, int length );

#endif

/******************************************************************************/

#ifdef __cplusplus
}
#endif
