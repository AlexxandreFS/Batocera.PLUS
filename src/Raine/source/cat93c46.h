
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                    CATALYST 93C46 1K-BIT SERIAL EEPROM                     */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

extern UINT16 *eeprom_data;

UINT8 eeprom_93c46_rb(void);
UINT8 eeprom_93c46_rb_cave(void);
void eeprom_93c46_wb(UINT8 data);

#ifdef __cplusplus
}
#endif
