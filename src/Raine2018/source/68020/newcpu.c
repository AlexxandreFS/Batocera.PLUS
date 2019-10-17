//
// UAE 68020 - RAINE VERSION
//

/* Speed hacks explained for the 68020 :
   the illegal instruction handler is calling op_illg in this file, passing
   the illegal instruction. Every instruction on 2 bytes with the 1st being
   7f is passed to the f3 eeprom handler.
   If you put :
   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;
   Then puting opcodes 7f02 in the rom (raine #$02 !!!) will stop the cpu,
   producing a speed hack. */

#include "68020.h"
//#include "config.h"
#include "m68k.h"

#include "newcpu.h"
#include "newmem.h"
#include "readcpu.h"

#include "raine.h"
#include "savegame.h"

#if defined( RAINE_WIN32 ) && !defined(__MINGW32__)
struct flag_struct regflags;
#else
struct flag_struct regflags __asm__ ("regflags");
#endif

void (*F3SystemEEPROMAccess)(UINT8 data);
int areg_byteinc[8] = { 1,1,1,1,1,1,1,2 };
int imm8_table[8] = { 8,1,2,3,4,5,6,7 };
int movem_index1[0x100];
int movem_index2[0x100];
int movem_next[0x100];
struct regstruct regs;

#define FAST020
extern void DoCycles(void);

cpuop_func *cpufunctbl[0x10000];

extern cpuop_func CPU_OP_NAME(_illegal_jedi);

UINT32 cycles;
/* static */ UINT8 *cyclepos;

extern void Init020_00(void);
extern void Init020_01(void);
extern void Init020_02(void);
extern void Init020_03(void);
extern void Init020_04(void);
extern void Init020_05(void);
extern void Init020_06(void);
extern void Init020_07(void);
extern void Init020_08(void);
extern void Init020_09(void);
extern void Init020_0a(void);
extern void Init020_0b(void);
extern void Init020_0c(void);
extern void Init020_0d(void);
extern void Init020_0e(void);
extern void Init020_0f(void);

void InitJedi(void)
{
   Init020_00();
   Init020_01();
   Init020_02();
   Init020_03();
   Init020_04();
   Init020_05();
   Init020_06();
   Init020_07();
   Init020_08();
   Init020_09();
   Init020_0a();
   Init020_0b();
   Init020_0c();
   Init020_0d();
   Init020_0e();
   Init020_0f();
}

static DEF_INLINE UINT16 table020(UINT16 ta)
{
   return(((ta&0xFF)<<8)|((ta>>8)&0xFF));
}

#ifdef FAST020
/*#if !defined( RAINE_WIN32 )
#warning FAST020
#endif*/

//static unsigned long smc;

#ifdef RAINE_DOS
// Now defined in asm02x.s - but i didn't fix that yet!!! :p [Antiriad 20001107]

void DoCycles(void)
{
   asm(
"	subl	$8,%%esp\n"

"	movl	_ROM,%%eax\n"
"	movl	%%eax,SMC1-4\n"

"	movl	%%esp,_cyclepos\n"

"	movl	_cycles,%%eax\n"
"	movl	%%eax,(%%esp)\n"

"	movl	$SMC2,%%eax\n"
"	movl	%%eax,4(%%esp)\n"

"	movl	_regs+88,%%ebx\n"
"	xorl	%%eax,%%eax\n"
"	movw	0x2164334A(%%ebx),%%ax\n"
"SMC1:\n"
"	movl	_cpufunctbl(,%%eax,4),%%ebx\n"
"	rolw	$8,%%ax\n"
"	jmp	*%%ebx\n"
"SMC2:\n"
	:
	:
	: "%eax","%ebx","%ecx","%edx","%esi","%edi"
   );
}
#endif

#else
#if 0
void DoCycles(void)
{
   UINT32 opcode;
   do{
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
   }
   while((cycles-=4)>0);
}
#endif

#endif

void Execute68020(int c)
{
   cycles=(c>>4);
#if defined(RAINE_DOS) || defined(RAINE_UNIX) || defined(__MINGW32__)
   // This one is the way to go in for everyone. Carefull here, it's a
   // non standard way to call a function. If you enter in that the wrong
   // way, you crash raine efficiently !
   __asm__ __volatile__ ("pushl %%ebp\n\tcall *%0\n\tpopl %%ebp" : : "r" (DoCycles) : "%eax", "%edx", "%ecx", "memory", "cc");
#else
   {
   UINT32 opcode;
   do{
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
      opcode=get_iword(0);
      (*cpufunctbl[opcode])(opcode);
   }
   while((cycles-=4)>0);
   }
#endif
}

void U_68020_A_load_update(void)
{
   // I haven't found anything that needs refreshing in here...
}

int MC68020 = 0;

void init_m68k(void)
{
    long int opcode;
    int i,j;

    print_debug("Adding U68020...\n");

    MC68020 = 1;
    for (i = 0 ; i < 256 ; i++) {
	for (j = 0 ; j < 8 ; j++) {
		if (i & (1 << j)) break;
	}
	movem_index1[i] = j;
	movem_index2[i] = 7-j;
	movem_next[i] = i & (~(1 << j));
    }

    table68k = (struct instr *) AllocateMem (65536 * sizeof (struct instr));

    read_table68k();
    do_merges();

    print_debug("%d CPU functions\n", nr_cpuop_funcs);

    for(opcode=0;opcode<65536;opcode++){
	cpufunctbl[opcode] = CPU_OP_NAME(_illegal_jedi);
    }

    for (i = 0; op_smalltbl[i].handler != NULL; i++) {
	if (!op_smalltbl[i].specific)
	    cpufunctbl[table020(op_smalltbl[i].opcode)] = op_smalltbl[i].handler;
    }
    for (opcode = 0; opcode < 65536; opcode++) {
	cpuop_func *f;

	if (table68k[opcode].mnemo == i_ILLG)
	    continue;

	if (table68k[opcode].handler != -1) {
	    f = cpufunctbl[table020(table68k[opcode].handler)];
	    if (f == CPU_OP_NAME(_illegal_jedi))
		abort();
	    cpufunctbl[table020(opcode)] = f;
	}
    }
    for (i = 0; op_smalltbl[i].handler != NULL; i++) {
	if (op_smalltbl[i].specific)
	    cpufunctbl[table020(op_smalltbl[i].opcode)] = op_smalltbl[i].handler;
    }

   FreeMem((UINT8 *)table68k);

   InitJedi();

   AddLoadCallback(U_68020_A_load_update);
   AddSaveData(SAVE_M68020_0, (UINT8 *) &regs, sizeof(regs));
}

void m68k_do_jsr(uaecptr oldpc, uaecptr dest)
{
   m68k_areg(regs, 7) -= 4;
   put_long(m68k_areg(regs, 7), oldpc);
   m68k_setpc(dest);
}

// MakeSR():
// Generate the 68020 SR register from flags

void MakeSR(void)
{
   regs.sr = (
      (regs.t1      << 15) |
      (regs.t0      << 14) |
      (regs.s       << 13) |
      (regs.m       << 12) |
      (regs.intmask <<  8) |
      (XFLG         <<  4) |
      (NFLG         <<  3) |
      (ZFLG         <<  2) |
      (VFLG         <<  1) |
      (CFLG         <<  0)
   );
}

// MakeFromSR():
// Generate flags from the 68020 SR register

void MakeFromSR(void)
{
   int olds = regs.s;
   int oldm = regs.m;

   regs.t1      = (regs.sr >> 15) & 1;
   regs.t0      = (regs.sr >> 14) & 1;
   regs.s       = (regs.sr >> 13) & 1;
   regs.m       = (regs.sr >> 12) & 1;
   regs.intmask = (regs.sr >>  8) & 7;
   XFLG         = (regs.sr >>  4) & 1;
   NFLG         = (regs.sr >>  3) & 1;
   ZFLG         = (regs.sr >>  2) & 1;
   VFLG         = (regs.sr >>  1) & 1;
   CFLG         = (regs.sr >>  0) & 1;

   if(olds != regs.s){
      if(olds){
         if(oldm)
            regs.msp = m68k_areg(regs, 7);
         else
            regs.isp = m68k_areg(regs, 7);
         m68k_areg(regs, 7) = regs.usp;
      }
      else{
         regs.usp = m68k_areg(regs, 7);
         m68k_areg(regs, 7) = regs.m ? regs.msp : regs.isp;
      }
   }
   else{
      if(olds && oldm != regs.m){
         if(oldm){
            regs.msp = m68k_areg(regs, 7);
            m68k_areg(regs, 7) = regs.isp;
         }
         else{
            regs.isp = m68k_areg(regs, 7);
            m68k_areg(regs, 7) = regs.msp;
         }
      }
   }
}

void Exception(int nr, uaecptr oldpc)
{
    MakeSR();
    if (!regs.s) {
        regs.usp = m68k_areg(regs, 7);
        m68k_areg(regs, 7) = regs.m ? regs.msp : regs.isp;
	regs.s = 1;
    }

	if (nr == 2 || nr == 3) {
	    int i;
	    // @@@ this is probably wrong (?)
	    for (i = 0 ; i < 12 ; i++) {
		m68k_areg(regs, 7) -= 2;
		put_word (m68k_areg(regs, 7), 0);
	    }
	    m68k_areg(regs, 7) -= 2;
	    put_word (m68k_areg(regs, 7), 0xa000 + nr * 4);
	} else if (nr ==5 || nr == 6 || nr == 7 || nr == 9) {
	    m68k_areg(regs, 7) -= 4;
	    put_long (m68k_areg(regs, 7), oldpc);
	    m68k_areg(regs, 7) -= 2;
	    put_word (m68k_areg(regs, 7), 0x2000 + nr * 4);
	} else if (regs.m && nr >= 24 && nr < 32) {
	    m68k_areg(regs, 7) -= 2;
	    put_word (m68k_areg(regs, 7), nr * 4);
	    m68k_areg(regs, 7) -= 4;
	    put_long (m68k_areg(regs, 7), m68k_getpc ());
	    m68k_areg(regs, 7) -= 2;
	    put_word (m68k_areg(regs, 7), regs.sr);
	    regs.sr |= (1 << 13);
	    regs.msp = m68k_areg(regs, 7);
	    m68k_areg(regs, 7) = regs.isp;
	    m68k_areg(regs, 7) -= 2;
	    put_word (m68k_areg(regs, 7), 0x1000 + nr * 4);
	} else {
	    m68k_areg(regs, 7) -= 2;
	    put_word (m68k_areg(regs, 7), nr * 4);
	}

    m68k_areg(regs, 7) -= 4;
    put_long (m68k_areg(regs, 7), m68k_getpc ());
    m68k_areg(regs, 7) -= 2;
    put_word (m68k_areg(regs, 7), regs.sr);
    m68k_setpc(get_long(regs.vbr + 4*nr));
    regs.t1 = regs.t0 = regs.m = 0;
}

void Interrupt020(int nr)
{
    if((nr<8) && (nr>=0)){
    Exception(nr+24,0);

    regs.intmask = nr;
    }
}

void Interrupt68020(int level)
{
   MakeSR();
   if(level>=((regs.sr&0xf00)>>8)) Exception(level+24,regs.pc);
}

static int caar, cacr;

void m68k_move2c(int regno, uae_u32 *regp)
{
   switch (regno) {
	 case 0: regs.sfc = *regp & 7; break;
	 case 1: regs.dfc = *regp & 7; break;
	 case 2: cacr = *regp & 0x3; break;	// ignore C and CE
	 case 0x800: regs.usp = *regp; break;
	 case 0x801: regs.vbr = *regp; break;
	 case 0x802: caar = *regp &0xfc; break;
	 case 0x803: regs.msp = *regp; if (regs.m == 1) m68k_areg(regs, 7) = regs.msp; break;
	 case 0x804: regs.isp = *regp; if (regs.m == 0) m68k_areg(regs, 7) = regs.isp; break;
      default:
         op_illg(0x4E7B);
      break;
   }
}

void m68k_movec2(int regno, uae_u32 *regp)
{
	switch (regno) {
	 case 0: *regp = regs.sfc; break;
	 case 1: *regp = regs.dfc; break;
	 case 2: *regp = cacr; break;
	 case 0x800: *regp = regs.usp; break;
	 case 0x801: *regp = regs.vbr; break;
	 case 0x802: *regp = caar; break;
	 case 0x803: *regp = regs.m == 1 ? m68k_areg(regs, 7) : regs.msp; break;
	 case 0x804: *regp = regs.m == 0 ? m68k_areg(regs, 7) : regs.isp; break;
	 default:
	    op_illg (0x4E7A);
	    break;
	}
}

static DEF_INLINE int
div_unsigned(uae_u32 src_hi, uae_u32 src_lo, uae_u32 div, uae_u32 *quot, uae_u32 *rem)
{
	uae_u32 q = 0, cbit = 0;
	int i;

	if (div <= src_hi) {
	    return(1);
	}
	for (i = 0 ; i < 32 ; i++) {
		cbit = src_hi & 0x80000000ul;
		src_hi <<= 1;
		if (src_lo & 0x80000000ul) src_hi++;
		src_lo <<= 1;
		q = q << 1;
		if (cbit || div <= src_hi) {
			q |= 1;
			src_hi -= div;
		}
	}
	*quot = q;
	*rem = src_hi;
	return(0);
}

void m68k_divl(uae_u32 opcode, uae_u32 src, uae_u16 extra, uaecptr oldpc)
{
	(void)(opcode);
#if defined(uae_s64)
    if (src == 0) {
	Exception(5,oldpc);
	return;
    }
    if (extra & 0x800) {
	// signed variant
	uae_s64 a = (uae_s64)(uae_s32)m68k_dreg(regs, (extra >> 12) & 7);
	uae_s64 quot, rem;

	if (extra & 0x400) {
	    a &= 0xffffffffu;
	    a |= (uae_s64)m68k_dreg(regs, extra & 7) << 32;
	}
	rem = a % (uae_s64)(uae_s32)src;
	quot = a / (uae_s64)(uae_s32)src;
	if ((quot & UVAL64(0xffffffff80000000)) != 0
	    && (quot & UVAL64(0xffffffff80000000)) != UVAL64(0xffffffff80000000))
	{
	    VFLG = NFLG = 1;
	    CFLG = 0;
	}
	else {
	    if (((uae_s32)rem < 0) != ((uae_s64)a < 0)) rem = -rem;
	    VFLG = CFLG = 0;
	    ZFLG = ((uae_s32)quot) == 0;
	    NFLG = ((uae_s32)quot) < 0;
	    m68k_dreg(regs, extra & 7) = rem;
	    m68k_dreg(regs, (extra >> 12) & 7) = quot;
	}
    } else {
	// unsigned
	uae_u64 a = (uae_u64)(uae_u32)m68k_dreg(regs, (extra >> 12) & 7);
	uae_u64 quot, rem;

	if (extra & 0x400) {
	    a &= 0xffffffffu;
	    a |= (uae_u64)m68k_dreg(regs, extra & 7) << 32;
	}
	rem = a % (uae_u64)src;
	quot = a / (uae_u64)src;
	if (quot > 0xffffffffu) {
	    VFLG = NFLG = 1;
	    CFLG = 0;
	}
	else {
	    VFLG = CFLG = 0;
	    ZFLG = ((uae_s32)quot) == 0;
	    NFLG = ((uae_s32)quot) < 0;
	    m68k_dreg(regs, extra & 7) = rem;
	    m68k_dreg(regs, (extra >> 12) & 7) = quot;
	}
    }
#else
    if (src == 0) {
	Exception(5,oldpc);
	return;
    }
    if (extra & 0x800) {
	// signed variant
	uae_s32 lo = (uae_s32)m68k_dreg(regs, (extra >> 12) & 7);
	uae_s32 hi = lo < 0 ? -1 : 0;
	uae_s32 save_high;
	uae_u32 quot = 0, rem = 0;
	uae_u32 sign;

	if (extra & 0x400) {
	    hi = (uae_s32)m68k_dreg(regs, extra & 7);
	}
	save_high = hi;
	sign = (hi ^ src);
	if (hi < 0) {
		hi = ~hi;
		lo = -lo;
		if (lo == 0) hi++;
	}
	if ((uae_s32)src < 0) src = -src;
	if (div_unsigned(hi, lo, src, &quot, &rem) ||
	    (sign & 0x80000000) ? quot > 0x80000000 : quot > 0x7fffffff) {
	    VFLG = NFLG = 1;
	    CFLG = 0;
	}
	else {
	    if (sign & 0x80000000) quot = -quot;
	    if (((uae_s32)rem < 0) != (save_high < 0)) rem = -rem;
	    VFLG = CFLG = 0;
	    ZFLG = ((uae_s32)quot) == 0;
	    NFLG = ((uae_s32)quot) < 0;
	    m68k_dreg(regs, extra & 7) = rem;
	    m68k_dreg(regs, (extra >> 12) & 7) = quot;
	}
    } else {
	// unsigned
	uae_u32 lo = (uae_u32)m68k_dreg(regs, (extra >> 12) & 7);
	uae_u32 hi = 0;
	uae_u32 quot = 0, rem = 0;

	if (extra & 0x400) {
	    hi = (uae_u32)m68k_dreg(regs, extra & 7);
	}
	if (div_unsigned(hi, lo, src, &quot, &rem)) {
	    VFLG = NFLG = 1;
	    CFLG = 0;
	}
	else {
	    VFLG = CFLG = 0;
	    ZFLG = ((uae_s32)quot) == 0;
	    NFLG = ((uae_s32)quot) < 0;
	    m68k_dreg(regs, extra & 7) = rem;
	    m68k_dreg(regs, (extra >> 12) & 7) = quot;
	}
    }
#endif
}

static DEF_INLINE void
mul_unsigned(uae_u32 src1, uae_u32 src2, uae_u32 *dst_hi, uae_u32 *dst_lo)
{
	uae_u32 r0 = (src1 & 0xffff) * (src2 & 0xffff);
	uae_u32 r1 = ((src1 >> 16) & 0xffff) * (src2 & 0xffff);
	uae_u32 r2 = (src1 & 0xffff) * ((src2 >> 16) & 0xffff);
	uae_u32 r3 = ((src1 >> 16) & 0xffff) * ((src2 >> 16) & 0xffff);
	uae_u32 lo;

	lo = r0 + ((r1 << 16) & 0xffff0000ul);
	if (lo < r0) r3++;
	r0 = lo;
	lo = r0 + ((r2 << 16) & 0xffff0000ul);
	if (lo < r0) r3++;
	r3 += ((r1 >> 16) & 0xffff) + ((r2 >> 16) & 0xffff);
	*dst_lo = lo;
	*dst_hi = r3;
}

void m68k_mull(uae_u32 opcode, uae_u32 src, uae_u16 extra)
{
	(void)(opcode);
#if defined(uae_s64)
    if (extra & 0x800) {
	// signed variant
	uae_s64 a = (uae_s64)(uae_s32)m68k_dreg(regs, (extra >> 12) & 7);

	a *= (uae_s64)(uae_s32)src;
	VFLG = CFLG = 0;
	ZFLG = a == 0;
	NFLG = a < 0;
	if (extra & 0x400)
	    m68k_dreg(regs, extra & 7) = a >> 32;
	else if ((a & UVAL64(0xffffffff80000000)) != 0
		 && (a & UVAL64(0xffffffff80000000)) != UVAL64(0xffffffff80000000))
	{
	    VFLG = 1;
	}
	m68k_dreg(regs, (extra >> 12) & 7) = (uae_u32)a;
    } else {
	// unsigned
	uae_u64 a = (uae_u64)(uae_u32)m68k_dreg(regs, (extra >> 12) & 7);

	a *= (uae_u64)src;
	VFLG = CFLG = 0;
	ZFLG = a == 0;
	NFLG = ((uae_s64)a) < 0;
	if (extra & 0x400)
	    m68k_dreg(regs, extra & 7) = a >> 32;
	else if ((a & UVAL64(0xffffffff00000000)) != 0) {
	    VFLG = 1;
	}
	m68k_dreg(regs, (extra >> 12) & 7) = (uae_u32)a;
    }
#else
    if (extra & 0x800) {
	// signed variant
	uae_s32 src1,src2;
	uae_u32 dst_lo,dst_hi;
	uae_u32 sign;

	src1 = (uae_s32)src;
	src2 = (uae_s32)m68k_dreg(regs, (extra >> 12) & 7);
	sign = (src1 ^ src2);
	if (src1 < 0) src1 = -src1;
	if (src2 < 0) src2 = -src2;
	mul_unsigned((uae_u32)src1,(uae_u32)src2,&dst_hi,&dst_lo);
	if (sign & 0x80000000) {
		dst_hi = ~dst_hi;
		dst_lo = -dst_lo;
		if (dst_lo == 0) dst_hi++;
	}
	VFLG = CFLG = 0;
	ZFLG = dst_hi == 0 && dst_lo == 0;
	NFLG = ((uae_s32)dst_hi) < 0;
	if (extra & 0x400)
	    m68k_dreg(regs, extra & 7) = dst_hi;
	else if ((dst_hi != 0 || (dst_lo & 0x80000000) != 0)
		 && ((dst_hi & 0xffffffff) != 0xffffffff
		     || (dst_lo & 0x80000000) != 0x80000000))
	{
	    VFLG = 1;
	}
	m68k_dreg(regs, (extra >> 12) & 7) = dst_lo;
    } else {
	// unsigned
	uae_u32 dst_lo,dst_hi;

	mul_unsigned(src,(uae_u32)m68k_dreg(regs, (extra >> 12) & 7),&dst_hi,&dst_lo);

	VFLG = CFLG = 0;
	ZFLG = dst_hi == 0 && dst_lo == 0;
	NFLG = ((uae_s32)dst_hi) < 0;
	if (extra & 0x400)
	    m68k_dreg(regs, extra & 7) = dst_hi;
	else if (dst_hi != 0) {
	    VFLG = 1;
	}
	m68k_dreg(regs, (extra >> 12) & 7) = dst_lo;
    }
#endif
}


void customreset(void)
{
   //Reset68020();
}

void Reset68020(void)
{
    m68k_areg(regs,7)=get_long(0);
    m68k_setpc(get_long(4));
    regs.s=1;
    regs.m=0;
    regs.stopped=0;
    regs.t1=0;
    regs.t0=0;
    ZFLG=CFLG=NFLG=VFLG=0;
    regs.intmask=7;
    regs.vbr=regs.sfc=regs.dfc=0;
    regs.sr=0x2700;
    MakeFromSR();
}

void op_illg(uae_u32 opcode)
{
    // RAINE #$xx

    if((opcode&0xFF00)==0x7F00){
       F3SystemEEPROMAccess(opcode&0xFF);
       m68k_incpc(2);
       return;
    }

    // LINEF #$xxx

    if((opcode&0xF000)==0xF000){
	Exception(0xB,0);
	return;
    }

    // LINEA #$xxx

    if((opcode&0xF000)==0xA000){
	Exception(0xA,0);
	return;
    }

       print_debug("[Illegal 68020 Instruction $%08x:%04x]\n",regs.pc,opcode);
    Exception(4,0);
}

void Stop68020(void)
{
   cycles=0;

#ifdef FAST020
   WriteLong(&cyclepos[0],cycles);
#endif

      print_debug("[68020 Stopped by User]\n");
}

