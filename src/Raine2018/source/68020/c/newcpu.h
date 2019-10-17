
#ifdef __cplusplus
extern "C" {
#endif
 /*
  * UAE - The Un*x Amiga Emulator
  *
  * MC68000 emulation
  *
  * Copyright 1995 Bernd Schmidt
  */

#include "readcpu.h"
#include "newmem.h"
#include "m68k.h"

#define SPCFLAG_STOP 2
#define SPCFLAG_COPPER 4
#define SPCFLAG_INT 8
#define SPCFLAG_BRK 16
#define SPCFLAG_EXTRA_CYCLES 32
#define SPCFLAG_TRACE 64
#define SPCFLAG_DOTRACE 128
#define SPCFLAG_DOINT 256
#define SPCFLAG_BLTNASTY 512
#define SPCFLAG_EXEC 1024
#define SPCFLAG_MODE_CHANGE 8192

extern int areg_byteinc[];
extern int imm8_table[];

extern int movem_index1[256];
extern int movem_index2[256];
extern int movem_next[256];

typedef unsigned long cpuop_func (UINT32);

struct cputbl {
    cpuop_func *handler;
    int specific;
    UINT16 opcode;
};

extern unsigned long op_illg (UINT32);

typedef char flagtype;

extern struct regstruct
{
    UINT32 regs[16];
    CPTR  usp,isp,msp;
    UINT16 sr;
    flagtype t1;
    flagtype t0;
    flagtype s;
    flagtype m;
    flagtype x;
    flagtype stopped;
    int intmask;

    UINT32 pc;
    UINT32 vbr,sfc,dfc;
} regs, lastint_regs;

#define m68k_dreg(r,num) ((r).regs[(num)])
#define m68k_areg(r,num) (((r).regs + 8)[(num)])
/*
UINT8 RR_ROM;
#define get_ibyte(o) ReadByte68k(((&RR_ROM)+regs.pc+(o)+1))
#define get_iword(o) ReadWord68k(((&RR_ROM)+regs.pc+(o)))
#define get_ilong(o) ReadLong68k(((&RR_ROM)+regs.pc+(o)))
*/
#define get_ibyte(o) ReadByte68k(&ROM[regs.pc+(o)+1])
#define get_iword(o) ReadWord68k(&ROM[regs.pc+(o)])
#define get_ilong(o) ReadLong68k(&ROM[regs.pc+(o)])

#define get_ibyte_1(o) get_ibyte(o)
#define get_iword_1(o) get_iword(o)
#define get_ilong_1(o) get_ilong(o)

#define m68k_incpc(o) (regs.pc += (o))

/* These are only used by the 68020/68881 code, and therefore don't
 * need to handle prefetch.  */
static DEF_INLINE UINT32 next_ibyte (void)
{
    UINT32 r = get_ibyte(0);
    m68k_incpc (2);
    return r;
}

static DEF_INLINE UINT32 next_iword (void)
{
    UINT32 r = get_iword(0);
    m68k_incpc(2);
    return r;
}

static DEF_INLINE UINT32 next_ilong (void)
{
    UINT32 r = get_ilong(0);
    m68k_incpc(4);
    return r;
}

static DEF_INLINE void m68k_setpc (CPTR newpc)
{
    regs.pc = newpc;
}

static DEF_INLINE CPTR m68k_getpc (void)
{
    return regs.pc;
}

#define m68k_setpc_fast m68k_setpc
#define m68k_setpc_bcc  m68k_setpc
#define m68k_setpc_rte  m68k_setpc

#define run_compiled_code() do { } while (0)
#define compiler_init() do { } while (0)
#define possible_loadseg() do { } while (0)

static DEF_INLINE void m68k_setstopped (int stop)
{
    regs.stopped = stop;
}

extern INT32 cycles;
extern UINT32 get_disp_ea_020 (UINT32 base, UINT32 dp);

typedef void (*output_func_ptr)( const char *, ... );

extern INT32 ShowEA (int reg, amodes mode, wordsizes size, char *buf, output_func_ptr debug_out);

extern void MakeSR (void);
extern void MakeFromSR (void);
extern void Exception (int, CPTR);
extern void dump_counts (void);
extern int m68k_move2c (int, UINT32 *);
extern int m68k_movec2 (int, UINT32 *);
extern void m68k_divl (UINT32, UINT32, UINT16, CPTR);
extern void m68k_mull (UINT32, UINT32, UINT16);
extern void init_m68k (void);
extern void m68k_go (int);
extern void m68k_dumpstate (CPTR *, int);
extern void m68k_disasm (CPTR, CPTR *, int, output_func_ptr debug_out);
extern void m68k_reset (void);

extern void mmu_op (UINT32, UINT16);

/* Opcode of faulting instruction */
extern UINT16 last_op_for_exception_3;
/* PC at fault time */
extern CPTR last_addr_for_exception_3;
/* Address that generated the exception */
extern CPTR last_fault_for_exception_3;

#define CPU_OP_NAME(a) op ## a

/* 68020 */
extern struct cputbl op_smalltbl_1[];

extern cpuop_func *cpufunctbl[65536];

static DEF_INLINE void m68k_do_jsr(unsigned int oldpc, unsigned int dest)
{
   m68k_areg(regs, 7) -= 4;
   cpu_writemem24_dword(m68k_areg(regs, 7), oldpc);
   m68k_setpc(dest);
}

static DEF_INLINE void m68k_do_rts(void)
{
    m68k_setpc(cpu_readmem24_dword(m68k_areg(regs, 7)));
    m68k_areg(regs, 7) += 4;
}

static DEF_INLINE void m68k_do_bsr(unsigned int oldpc, UINT32 offset)
{
    m68k_do_jsr(oldpc, m68k_getpc() + offset);
}

#ifdef __cplusplus
}
#endif
