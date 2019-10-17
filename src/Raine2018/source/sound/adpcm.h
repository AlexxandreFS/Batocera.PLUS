
#ifdef __cplusplus
extern "C" {
#endif
#ifndef ADPCM_H
#define ADPCM_H

#include "mame/handlers.h"

#define MAX_ADPCM 8


/* a generic ADPCM interface, for unknown chips */

struct ADPCMinterface
{
	int num;			       /* total number of ADPCM decoders in the machine */
	int frequency;             /* playback frequency */
	int region;                /* memory region where the samples come from */
	int mixing_level[MAX_ADPCM];     /* master volume */
};

void ADPCMSetBuffers(const struct ADPCMinterface *msound,UINT8 *region,int banksize);
void ADPCMSetBuffersOne(const struct ADPCMinterface *msound,UINT8 *region,int banksize); // Init 1 chip only, 2 banks (wrestlef...)
int ADPCM_sh_start(const struct ADPCMinterface *msound);
void ADPCM_sh_stop(void);
void ADPCM_sh_update(void);

void ADPCM_play(int num, int offset, int length);
void ADPCM_setvol(int num, int vol);
void ADPCM_stop(int num);
int ADPCM_playing(int num);


/* an interface for the OKIM6295 and similar chips */

#define MAX_OKIM6295 			2
#define MAX_OKIM6295_VOICES		4
#define ALL_VOICES				-1

struct OKIM6295interface
{
	int num;                  		/* total number of chips */
	int frequency[MAX_OKIM6295];	/* playback frequency */
	int region[MAX_OKIM6295];		/* memory region where the sample ROM lives */
	int mixing_level[MAX_OKIM6295];	/* master volume */
};

int OKIM6295_sh_start(const struct OKIM6295interface *msound);
void OKIM6295_bankswitch(int which, int data);
void OKIM6295_sh_stop(void);
void OKIM6295_sh_update(void);
void OKIM6295_set_bank_base(int which, int voice, int base);	/* set voice to ALL_VOICES to set all banks at once */
// I can't define the macro and the function so just remember to pass ALL_VOICES for
// compatibility with mame...
// #define OKIM6295_set_bank_base(which, base) OKIM6295_set_bank_base(which, ALL_VOICES, base)
void OKIM6295_set_frequency(int which, int voice, int frequency);	/* set voice to ALL_VOICES to set all banks at once */

READ_HANDLER( OKIM6295_status_0_r );
READ_HANDLER( OKIM6295_status_1_r );
WRITE_HANDLER( OKIM6295_data_0_w );
WRITE_HANDLER( OKIM6295_data_1_w );

extern UINT32 adpcm_amplify;

#endif

#ifdef __cplusplus
}
#endif
