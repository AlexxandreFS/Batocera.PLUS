
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                    tc0110pcr: TAITO COLOUR RAM PORT                        */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

void tc0110pcr_init(UINT8 *src, UINT8 colmode);
void tc0110pcr_init_typeb(UINT8 *src, UINT8 colmode, UINT16 add ); /* hiro-shi!! */
void tc0110pcr_ww(UINT32 address, UINT16 data);
UINT16 tc0110pcr_rw(UINT32 address);

void tc0110pcr_init_2(UINT8 *src, UINT8 colmode);
void tc0110pcr_init_typeb_2(UINT8 *src, UINT8 colmode, UINT16 add ); /* hiro-shi!! */
void tc0110pcr_ww_2(UINT32 address, UINT16 data);
UINT16 tc0110pcr_rw_2(UINT32 address);

void tc0110pcr_init_3(UINT8 *src, UINT8 colmode);
void tc0110pcr_init_typeb_3(UINT8 *src, UINT8 colmode, UINT16 add ); /* hiro-shi!! */
void tc0110pcr_ww_3(UINT32 address, UINT16 data);
UINT16 tc0110pcr_rw_3(UINT32 address);

#ifdef __cplusplus
}
#endif
