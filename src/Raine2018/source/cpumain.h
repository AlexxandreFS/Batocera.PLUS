
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                        GENERIC CPU CALLING ROUTINES                        */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"
#include "conf-cpu.h"

/*

cpu identifiers - the low nibble is for cpu number, the
high nibble is for cpu type

*/

#define CPU_NONE             (0x00)

#define CPU_68K_0            (0x10)
#define CPU_68K_1            (0x11)
#define CPU_68K_2            (0x12)

#define CPU_Z80_0            (0x20)
#define CPU_Z80_1            (0x21)
#define CPU_Z80_2            (0x22)
#define CPU_Z80_3            (0x23)

#define CPU_M68020_0         (0x30)

#define CPU_M6502_0          (0x40)
#define CPU_M6502_1          (0x41)
#define CPU_M6502_2          (0x42)

/*

initialize - call before using anything else in this file

*/

void switch_cpu(UINT32 cpu_id); // usefull for the debuger

void start_cpu_main(void);

/*

uninitialize - call this before changing contexts (ie. load/save/exit to gui)

*/

void stop_cpu_main(void);

/*

request an interrupt on a cpu

*/

void cpu_interrupt(UINT32 cpu_id, UINT32 vector);

/*

request an nmi on a cpu

*/

void cpu_int_nmi(UINT32 cpu_id);

/*

execute a cpu for some cycles

*/

void cpu_execute_cycles(UINT32 cpu_id, UINT32 cycles);

/*

reset a cpu

*/

void cpu_reset(UINT32 cpu_id);

/*

get the pc of a cpu

*/

UINT32 cpu_get_pc(UINT32 cpu_id);
void cpu_get_ram(UINT32 cpu, UINT32 *range, UINT32 *count);
UINT8 *get_code_range(UINT32 cpu, UINT32 adr, UINT32 *start, UINT32 *end);
UINT8 *get_userdata(UINT32 cpu, UINT32 adr);
int bcd(int value);

#ifdef RAINE_DEBUG
extern UINT32 current_cpu_num[0x10];
#endif

#ifdef __cplusplus
}
#endif
