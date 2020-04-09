#ifndef _Z80_H_
#define _Z80_H_

// #include "cpuintrf.h"
#include "deftypes.h"

enum {
	Z80_PC=1, Z80_SP,
	Z80_A, Z80_B, Z80_C, Z80_D, Z80_E, Z80_H, Z80_L,
	Z80_AF, Z80_BC, Z80_DE, Z80_HL,
	Z80_IX, Z80_IY,	Z80_AF2, Z80_BC2, Z80_DE2, Z80_HL2,
	Z80_R, Z80_I, Z80_IM, Z80_IFF1, Z80_IFF2, Z80_HALT,
	Z80_DC0, Z80_DC1, Z80_DC2, Z80_DC3
};

enum {
	Z80_TABLE_op,
	Z80_TABLE_cb,
	Z80_TABLE_ed,
	Z80_TABLE_xy,
	Z80_TABLE_xycb,
	Z80_TABLE_ex	/* cycles counts for taken jr/jp/call and interrupt latency (rst opcodes) */
};

enum
{
	CPUINFO_PTR_Z80_CYCLE_TABLE = 0, // CPUINFO_PTR_CPU_SPECIFIC,
	CPUINFO_PTR_Z80_CYCLE_TABLE_LAST = CPUINFO_PTR_Z80_CYCLE_TABLE + Z80_TABLE_ex
};

#include "mame/pair.h"

/****************************************************************************/
/* The Z80 registers. HALT is set to 1 when the CPU is halted, the refresh  */
/* register is calculated as follows: refresh=(Z80.r&127)|(Z80.r2&128)      */
/****************************************************************************/
typedef struct
{
	PAIR	prvpc,pc,sp,af,bc,de,hl,ix,iy;
	PAIR	af2,bc2,de2,hl2;
	UINT8	r,r2,iff1,iff2,halt,im,i;
	UINT8	nmi_state;			/* nmi line state */
	UINT8	nmi_pending;		/* nmi pending */
	UINT8	irq_state;			/* irq line state */
	UINT8	after_ei;			/* are we in the EI shadow? */
	int irq_vector;
	UINT32 dwElapsedTicks;
	// z80Base will make debuger functions much easier
	UINT8 *z80Base;
#ifdef DAISY
	const struct z80_irq_daisy_chain *daisy;
#endif
}	Z80_Regs;

extern Z80_Regs Z80;
extern int z80_ICount;

// extern void z80_get_info(UINT32 state, cpuinfo *info);

void z80_init(const void *config);
void z80_reset(void);
void z80_exit(void);
int z80_execute(int cycles);
void z80_release_time_slice();
void z80_get_context (void *dst);
void z80_set_context (void *src);
void z80_set_irq_line(int irq_vector, int irqline, int state);
#ifdef ENABLE_DEBUGGER
extern unsigned z80_dasm(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram);
#endif


#endif

