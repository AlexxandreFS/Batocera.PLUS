
#ifdef __cplusplus
extern "C" {
#endif
/* Learn Raine how to speak the Mame language... */
#ifndef DRIVER_H
// Mame include files have the bad habit to include each other...

#define DRIVER_H

#include "memory.h"

/* driver.h */

struct MachineCPU
{
	int cpu_type;	/* see #defines below. */
	int cpu_clock;	/* in Hertz */
	const struct MemoryReadAddress *memory_read;
	const struct MemoryWriteAddress *memory_write;
	const struct IOReadPort *port_read;
	const struct IOWritePort *port_write;
	int (*vblank_interrupt)(void);
    int vblank_interrupts_per_frame;    /* usually 1 */
/* use this for interrupts which are not tied to vblank 	*/
/* usually frequency in Hz, but if you need 				*/
/* greater precision you can give the period in nanoseconds */
	int (*timed_interrupt)(void);
	int timed_interrupts_per_second;
/* pointer to a parameter to pass to the CPU cores reset function */
	void *reset_param;
};

enum
{
	CPU_DUMMY,
	CPU_Z80,
#ifdef HAS_Z80GB
	CPU_Z80GB,
#endif
#ifdef HAS_8080
	CPU_8080,
#endif
#ifdef HAS_8085A
	CPU_8085A,
#endif
#ifdef HAS_M6502
	CPU_M6502,
#endif
#ifdef HAS_M65C02
	CPU_M65C02,
#endif
#ifdef HAS_M65SC02
	CPU_M65SC02,
#endif
#ifdef HAS_M65CE02
	CPU_M65CE02,
#endif
#ifdef HAS_M6509
    CPU_M6509,
#endif
#ifdef HAS_M6510
	CPU_M6510,
#endif
#ifdef HAS_M6510T
	CPU_M6510T,
#endif
#ifdef HAS_M7501
	CPU_M7501,
#endif
#ifdef HAS_M8502
	CPU_M8502,
#endif
#ifdef HAS_N2A03
	CPU_N2A03,
#endif
#ifdef HAS_M4510
	CPU_M4510,
#endif
#ifdef HAS_H6280
	CPU_H6280,
#endif
#ifdef HAS_I86
	CPU_I86,
#endif
#ifdef HAS_I88
	CPU_I88,
#endif
#ifdef HAS_I186
	CPU_I186,
#endif
#ifdef HAS_I188
	CPU_I188,
#endif
#ifdef HAS_I286
	CPU_I286,
#endif
#ifdef HAS_V20
	CPU_V20,
#endif
#ifdef HAS_V30
	CPU_V30,
#endif
#ifdef HAS_V33
	CPU_V33,
#endif
#ifdef HAS_I8035
	CPU_I8035,		/* same as CPU_I8039 */
#endif
#ifdef HAS_I8039
	CPU_I8039,
#endif
#ifdef HAS_I8048
	CPU_I8048,		/* same as CPU_I8039 */
#endif
#ifdef HAS_N7751
	CPU_N7751,		/* same as CPU_I8039 */
#endif
#ifdef HAS_M6800
	CPU_M6800,		/* same as CPU_M6802/CPU_M6808 */
#endif
#ifdef HAS_M6801
	CPU_M6801,		/* same as CPU_M6803 */
#endif
#ifdef HAS_M6802
	CPU_M6802,		/* same as CPU_M6800/CPU_M6808 */
#endif
#ifdef HAS_M6803
	CPU_M6803,		/* same as CPU_M6801 */
#endif
#ifdef HAS_M6808
	CPU_M6808,		/* same as CPU_M6800/CPU_M6802 */
#endif
#ifdef HAS_HD63701
	CPU_HD63701,	/* 6808 with some additional opcodes */
#endif
#ifdef HAS_NSC8105
	CPU_NSC8105,	/* same(?) as CPU_M6802(?) with scrambled opcodes. There is at least one new opcode. */
#endif
#ifdef HAS_M6805
	CPU_M6805,
#endif
#ifdef HAS_M68705
	CPU_M68705, 	/* same as CPU_M6805 */
#endif
#ifdef HAS_HD63705
	CPU_HD63705,	/* M6805 family but larger address space, different stack size */
#endif
#ifdef HAS_HD6309
	CPU_HD6309,		/* same as CPU_M6809 (actually it's not 100% compatible) */
#endif
#ifdef HAS_M6809
	CPU_M6809,
#endif
#ifdef HAS_KONAMI
	CPU_KONAMI,
#endif
	CPU_M68000,
#ifdef HAS_M68010
	CPU_M68010,
#endif
	CPU_M68EC020,
	CPU_M68020,
#ifdef HAS_T11
	CPU_T11,
#endif
#ifdef HAS_S2650
	CPU_S2650,
#endif
#ifdef HAS_F8
	CPU_F8,
#endif
#ifdef HAS_TMS34010
	CPU_TMS34010,
#endif
#ifdef HAS_TMS9900
	CPU_TMS9900,
#endif
#ifdef HAS_TMS9940
	CPU_TMS9940,
#endif
#ifdef HAS_TMS9980
	CPU_TMS9980,
#endif
#ifdef HAS_TMS9985
	CPU_TMS9985,
#endif
#ifdef HAS_TMS9989
	CPU_TMS9989,
#endif
#ifdef HAS_TMS9995
	CPU_TMS9995,
#endif
#ifdef HAS_TMS99105A
	CPU_TMS99105A,
#endif
#ifdef HAS_TMS99110A
	CPU_TMS99110A,
#endif
#ifdef HAS_Z8000
	CPU_Z8000,
#endif
#ifdef HAS_TMS320C10
	CPU_TMS320C10,
#endif
#ifdef HAS_CCPU
	CPU_CCPU,
#endif
#ifdef HAS_PDP1
	CPU_PDP1,
#endif
#ifdef HAS_ADSP2100
	CPU_ADSP2100,
#endif
#ifdef HAS_ADSP2105
	CPU_ADSP2105,
#endif
#ifdef HAS_PSXCPU
	CPU_PSX,
#endif
#ifdef HAS_SC61860
	CPU_SC61860,
#endif
#ifdef HAS_ARM
	CPU_ARM,
#endif
#ifdef HAS_G65816
	CPU_G65C816,
#endif
#ifdef HAS_SPC700
	CPU_SPC700,
#endif
    CPU_COUNT
};

/* set this if the CPU is used as a slave for audio. It will not be emulated if */
/* sound is disabled, therefore speeding up a lot the emulation. */
#define CPU_AUDIO_CPU 0x8000

/* the Z80 can be wired to use 16 bit addressing for I/O ports */
#define CPU_16BIT_PORT 0x4000

#define CPU_FLAGS_MASK 0xff00


#define MAX_CPU 8	/* MAX_CPU is the maximum number of CPUs which cpuintrf.c */
					/* can run at the same time. Currently, 8 is enough. */


#define MAX_SOUND 5	/* MAX_SOUND is the maximum number of sound subsystems */
					/* which can run at the same time. Currently, 5 is enough. */


#endif

#ifdef __cplusplus
}
#endif
