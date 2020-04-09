
#ifdef __cplusplus
extern "C" {
#endif
 /*
  * UAE - The Un*x Amiga Emulator
  *
  * MC68000 emulation - machine dependent bits
  * Version WITHOUT CRLFs
  * Copyright 1996 Bernd Schmidt
  */

struct flag_struct {
	unsigned int c:1; /* first byte */
	int :5;
	unsigned int z:1;
	unsigned int n:1;
	int :3; 		  /* second, third & fourth byte */
	unsigned int v:1;
	int :20;
	unsigned int x:1; /* fifth */
	int :31;
};

#if defined( RAINE_WIN32 ) && !defined(__MINGW32__)
extern struct flag_struct regflags;
#else
extern struct flag_struct regflags __asm__ ("regflags");
#endif

//extern struct flag_struct regflags __asm__ ("regflags");

#define ZFLG (regflags.z)
#define NFLG (regflags.n)
#define CFLG (regflags.c)
#define VFLG (regflags.v)
#define XFLG (regflags.x)

static DEF_INLINE int cctrue(const int cc)
{
	switch(cc){
	 case 0: return 1;						 /* T */
	 case 1: return 0;						 /* F */
	 case 2: return !CFLG && !ZFLG; 		 /* HI */
	 case 3: return CFLG || ZFLG;			 /* LS */
	 case 4: return !CFLG;					 /* CC */
	 case 5: return CFLG;					 /* CS */
	 case 6: return !ZFLG;					 /* NE */
	 case 7: return ZFLG;					 /* EQ */
	 case 8: return !VFLG;					 /* VC */
	 case 9: return VFLG;					 /* VS */
	 case 10:return !NFLG;					 /* PL */
	 case 11:return NFLG;					 /* MI */
	 case 12:return NFLG == VFLG;			 /* GE */
	 case 13:return NFLG != VFLG;			 /* LT */
	 case 14:return !ZFLG && (NFLG == VFLG); /* GT */
	 case 15:return ZFLG || (NFLG != VFLG);  /* LE */
	}
	abort();
	return 0;
}

#define x86_flag_testl(v) \
  __asm__ __volatile__ ("testl %1,%1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n" \
			: "=r" (scratch) : "r" (v) : "cc")

#define x86_flag_testw(v) \
  __asm__ __volatile__ ("testw %w1,%w1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n" \
			: "=r" (scratch) : "r" (v) : "cc")

#define x86_flag_testb(v) \
  __asm__ __volatile__ ("testb %b1,%b1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n" \
			: "=r" (scratch) : "q" (v) : "cc")

#define x86_flag_addl(v, s, d) \
  __asm__ __volatile__ ("addl %k2,%k1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n\t" \
			"movl %0,regflags+4\n" \
			: "=r" (scratch), "=r" (v) : "rmi" (s), "1" (d) : "cc")

#define x86_flag_addw(v, s, d) \
  __asm__ __volatile__ ("addw %w2,%w1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n\t" \
			"movl %0,regflags+4\n" \
			: "=r" (scratch), "=r" (v) : "rmi" (s), "1" (d) : "cc")

#define x86_flag_addb(v, s, d) \
  __asm__ __volatile__ ("addb %b2,%b1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n\t" \
			"movl %0,regflags+4\n" \
			: "=r" (scratch), "=q" (v) : "qmi" (s), "1" (d) : "cc")

#define x86_flag_subl(v, s, d) \
  __asm__ __volatile__ ("subl %k2,%k1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n\t" \
			"movl %0,regflags+4\n" \
			: "=r" (scratch), "=r" (v) : "rmi" (s), "1" (d) : "cc")

#define x86_flag_subw(v, s, d) \
  __asm__ __volatile__ ("subw %w2,%w1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n\t" \
			"movl %0,regflags+4\n" \
			: "=r" (scratch), "=r" (v) : "rmi" (s), "1" (d) : "cc")

#define x86_flag_subb(v, s, d) \
  __asm__ __volatile__ ("subb %b2,%b1\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n\t" \
			"movl %0,regflags+4\n" \
			: "=r" (scratch), "=q" (v) : "qmi" (s), "1" (d) : "cc")

#define x86_flag_cmpl(s, d) \
  __asm__ __volatile__ ("cmpl %k1,%k2\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n" \
			: "=r" (scratch) : "rmi" (s), "r" (d) : "cc")

#define x86_flag_cmpw(s, d) \
  __asm__ __volatile__ ("cmpw %w1,%w2\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n" \
			: "=r" (scratch) : "rmi" (s), "r" (d) : "cc")

#define x86_flag_cmpb(s, d) \
  __asm__ __volatile__ ("cmpb %b1,%b2\n\t" \
			"pushfl\n\t" \
			"popl %0\n\t" \
			"movl %0,regflags\n" \
			: "=r" (scratch) : "qmi" (s), "q" (d) : "cc")


#ifdef __cplusplus
}
#endif
