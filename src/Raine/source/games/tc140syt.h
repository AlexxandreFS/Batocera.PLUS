
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*   tc0140syt: TAITO MAIN TO SOUND CPU COMMUNICATION (68000-Z80; Z80-Z80)    */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

void tc0140syt_reset(void);

UINT8 tc0140syt_get_port01(void);
UINT8 tc0140syt_get_port23(void);

UINT8 tc0140syt_want_nmi(void);

// 68000 Main
// ----------

UINT8 tc0140syt_read_main_68k(UINT32 offset);
void tc0140syt_write_main_68k(UINT32 offset, UINT8 data);

// Z80 Main
// --------

UINT8 tc0140syt_read_main_z80(UINT16 offset);
void tc0140syt_write_main_z80(UINT16 offset, UINT8 data);

// Z80 Sub
// -------

UINT8 tc0140syt_read_sub_z80(UINT16 offset);
void tc0140syt_write_sub_z80(UINT16 offset, UINT8 data);


#ifdef __cplusplus
}
#endif
