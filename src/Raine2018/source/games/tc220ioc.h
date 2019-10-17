
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*            tc0220ioc: TAITO INPUT/OUTPUT CONTROL CHIP (F2 SYSTEM)          */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

#define TC0220_STOPCPU	(0x0001)		// Use tc0220ioc for frame sync
#define TC0220_QUIET	(0x0002)		// Don't report any errors

typedef struct TC0220IOC			// Information about 1 chip
{
   UINT8 *RAM;					// RAM address
   UINT32 ctrl;					// Control Information
} TC0220IOC;

struct TC0220IOC tc0220ioc;

extern struct INPUT_INFO b_system_inputs[];
extern struct INPUT_INFO b_system_inputs_3_button[];

void reset_tc0220ioc(void);

// 'Normal' 68000 Interface

UINT8 tc0220ioc_rb(UINT32 address);
UINT16 tc0220ioc_rw(UINT32 address);
void  tc0220ioc_wb(UINT32 address, UINT8 data);
void  tc0220ioc_ww(UINT32 address, UINT16 data);

// 'Byteswapped' 68000 Interface (Gun Frontier)

UINT8 tc0220ioc_rb_bswap(UINT32 address);
UINT16 tc0220ioc_rw_bswap(UINT32 address);
void  tc0220ioc_wb_bswap(UINT32 address, UINT8 data);
void  tc0220ioc_ww_bswap(UINT32 address, UINT16 data);

// 'Port access' 68000 Interface (Master of Weapons)

UINT8 tc0220ioc_rb_port(UINT32 address);
UINT16 tc0220ioc_rw_port(UINT32 address);
void  tc0220ioc_wb_port(UINT32 address, UINT8 data);
void  tc0220ioc_ww_port(UINT32 address, UINT16 data);

// 'Normal' Z80 Interface (L-System)

UINT8 tc0220ioc_rb_z80(UINT16 address);
void  tc0220ioc_wb_z80(UINT16 address, UINT8 data);

// 'Port access' Z80 Interface (L-System)

UINT8 tc0220ioc_rb_z80_port(UINT16 address);
void  tc0220ioc_wb_z80_port(UINT16 address, UINT8 data);


#ifdef __cplusplus
}
#endif
