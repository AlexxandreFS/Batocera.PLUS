
#ifdef __cplusplus
extern "C" {
#endif
 /*
  * UAE - The Un*x Amiga Emulator
  *
  * MC68000 emulation
  *
  * Copyright 1995 Bernd Schmidt
  *
  * Optimized MC68020 version
  * by Anitiriad, for Raine
  * with Taito F3-System.
  */

extern int areg_byteinc[];
extern int imm8_table[];

extern int movem_index1[256];
extern int movem_index2[256];
extern int movem_next[256];
#if (defined(RAINE_DOS) || defined(RAINE_UNIX)) && !defined(NO_ASM)
typedef void cpuop_func(uae_u32) __attribute__ ((regparm (1)));
#else
typedef void cpuop_func(uae_u32);
#endif
struct cputbl
{
   cpuop_func *handler;
   int specific;
   uae_u16 opcode;
};

extern void op_illg(uae_u32);

typedef char flagtype;

extern struct regstruct
{
    uae_u32 regs[16];
    uaecptr  usp,isp,msp;
    uae_u16 sr;
    flagtype t1;
    flagtype t0;
    flagtype s;
    flagtype m;
    flagtype x;
    flagtype stopped;
    int intmask;
    uae_u32 pc;
    uae_u32 vbr,sfc,dfc;

} regs;

#define m68k_dreg(r,num) ((r).regs[(num)])
#define m68k_areg(r,num) ((r).regs[(num)+8])
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

static DEF_INLINE uae_u32 nextibyte(void)
{
    uae_u32 r = get_ibyte(0);
    m68k_incpc(2);
    return r;
}

static DEF_INLINE uae_u32 nextiword(void)
{
    uae_u32 r = get_iword(0);
    m68k_incpc(2);
    return r;
}

static DEF_INLINE uae_u32 nextilong(void)
{
    uae_u32 r = get_ilong(0);
    m68k_incpc(4);
    return r;
}

static DEF_INLINE void m68k_setpc(uaecptr newpc)
{
    regs.pc = newpc;
}

static DEF_INLINE uaecptr m68k_getpc(void)
{
    return regs.pc;
}


#define m68k_setpc_fast m68k_setpc
#define m68k_setpc_bcc  m68k_setpc
#define m68k_setpc_rte  m68k_setpc

#define run_compiled_code() do { } while (0)
#define compiler_init() do { } while (0)
#define possible_loadseg() do { } while (0)

static DEF_INLINE void m68k_setstopped(int stop)
{
    regs.stopped = stop;
}

extern UINT32 cycles;

extern void MakeSR(void);
extern void MakeFromSR(void);

extern void Exception(int, uaecptr);
extern void dump_counts(void);
extern void m68k_move2c(int, uae_u32 *);
extern void m68k_movec2(int, uae_u32 *);
extern void m68k_divl(uae_u32, uae_u32, uae_u16, uaecptr);
extern void m68k_mull(uae_u32, uae_u32, uae_u16);
extern void init_m68k(void);
extern void m68k_go(int);
extern void m68k_dumpstate(uaecptr *);
extern void m68k_disasm(uaecptr,uaecptr *,int);
extern void m68k_reset(void);

#define CPU_OP_NAME(a) op ## a

extern struct cputbl op_smalltbl[];
extern struct cputbl op_direct_smalltbl[];
#if defined(RAINE_DOS) || defined(RAINE_UNIX)
#define ASM_SYM_FOR_FUNC(a) __asm__(a)

extern cpuop_func *cpufunctbl[0x10000];
#else
extern cpuop_func *cpufunctbl[0x10000];
#endif

#ifdef __cplusplus
}
#endif
