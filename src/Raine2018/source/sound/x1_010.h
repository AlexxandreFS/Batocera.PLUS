
#ifdef __cplusplus
extern "C" {
#endif
#include "mame/handlers.h"

struct x1_010_interface
{
	int clock;	/* clock */
	int volume;	/* volume */
	int adr;	/* address */
};


READ_HANDLER ( seta_sound_r );
WRITE_HANDLER( seta_sound_w );
READ_HANDLER ( seta_sound_6502_r );
WRITE_HANDLER( seta_sound_6502_w );

READ16_HANDLER ( seta_sound_word_r );
WRITE16_HANDLER ( seta_sound_word_w );
void seta_sound_word_wb(UINT32 offset,UINT16 data);
UINT16 seta_sound_word_rb(UINT32 offset);

void seta_sound_enable_w(int);

int seta_sh_start( const struct x1_010_interface *msound );
void seta_sh_stop( void );

#ifdef __cplusplus
}
#endif
