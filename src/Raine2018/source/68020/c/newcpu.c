/*
 * UAE - The Un*x Amiga Emulator
 *
 * MC68000 emulation
 *
 * (c) 1995 Bernd Schmidt
 */

/* Speed hacks explained for the 68020 :
   the illegal instruction handler is calling op_illg in this file, passing
   the illegal instruction. Every instruction on 2 bytes with the 1st being
   7f is passed to the f3 eeprom handler.
   If you put :
   F3SystemEEPROMAccess=&F3SysEEPROMAccessMode2;
   Then puting opcodes 7f02 in the rom (raine #$02 !!!) will stop the cpu,
   producing a speed hack. */

#include "raine.h"
#include "newmem.h"
#include "readcpu.h"
#include "68020.h"
#include "newcpu.h"

void (*F3SystemEEPROMAccess)(UINT8 data);
struct flag_struct regflags;

/* Normally uae uses cpu_readmem24 and cpu_writemem24 functions to access memory.
 * Raine converted this to R24 / W24 arrays pointing to regions of 65536 bytes
 * allocated by the game drivers. Here we just need to declare the arrays */
UINT8 *R24[0x100], *W24[0x100];

/* Opcode of faulting instruction */
UINT16 last_op_for_exception_3;
/* PC at fault time */
CPTR last_addr_for_exception_3;
/* Address that generated the exception */
CPTR last_fault_for_exception_3;

int areg_byteinc[] = { 1,1,1,1,1,1,1,2 };
int imm8_table[] = { 8,1,2,3,4,5,6,7 };

int movem_index1[256];
int movem_index2[256];
int movem_next[256];

cpuop_func *cpufunctbl[65536];

INT32 cycles;

static unsigned long op_illg_1 (UINT32 opcode)
{
    op_illg (opcode);
    return 4;
}

static void build_cpufunctbl (void)
{
    int i;
    unsigned long opcode;
    struct cputbl *tbl = op_smalltbl_1;

    for (opcode = 0; opcode < 65536; opcode++)
		cpufunctbl[opcode] = op_illg_1;
    for (i = 0; tbl[i].handler != NULL; i++) {
		if (! tbl[i].specific)
			cpufunctbl[tbl[i].opcode] = tbl[i].handler;
    }
    for (opcode = 0; opcode < 65536; opcode++) {
		cpuop_func *f;

		if (table68k[opcode].mnemo == i_ILLG || table68k[opcode].clev > 2)
			continue;

		if (table68k[opcode].handler != -1) {
			f = cpufunctbl[table68k[opcode].handler];
			if (f == op_illg_1)
				abort();
			cpufunctbl[opcode] = f;
		}
    }
    for (i = 0; tbl[i].handler != NULL; i++) {
		if (tbl[i].specific)
			cpufunctbl[tbl[i].opcode] = tbl[i].handler;
    }
}

int MC68020 = 0;

void init_m68k (void)
{
    int i;

    MC68020 = 1;
    for (i = 0 ; i < 256 ; i++) {
		int j;
		for (j = 0 ; j < 8 ; j++) {
			if (i & (1 << j)) break;
		}
		movem_index1[i] = j;
		movem_index2[i] = 7-j;
		movem_next[i] = i & (~(1 << j));
    }

    read_table68k ();
    do_merges ();

    build_cpufunctbl ();
}

void m68k_cleanup (void)
{
    free (table68k);
}

struct regstruct regs, lastint_regs;
static long int m68kpc_offset;
int lastint_no;

INT32 ShowEA (int reg, amodes mode, wordsizes size, char *buf, output_func_ptr debug_out )
{
    UINT16 dp;
    INT8 disp8;
    INT16 disp16;
    int r;
    UINT32 dispreg;
    CPTR addr;
    INT32 offset = 0;
    char buffer[80];

    switch (mode){
	case Dreg:
		sprintf (buffer,"D%d", reg);
		break;
	case Areg:
		sprintf (buffer,"A%d", reg);
		break;
	case Aind:
		sprintf (buffer,"(A%d)", reg);
		break;
	case Aipi:
		sprintf (buffer,"(A%d)+", reg);
		break;
	case Apdi:
		sprintf (buffer,"-(A%d)", reg);
		break;
	case Ad16:
		disp16 = get_iword_1 (m68kpc_offset); m68kpc_offset += 2;
		addr = m68k_areg(regs,reg) + (INT16)disp16;
		sprintf (buffer,"(A%d,$%04x) == $%08lx", reg, disp16 & 0xffff,
			(unsigned long)addr);
		break;
	case Ad8r:
		dp = get_iword_1 (m68kpc_offset); m68kpc_offset += 2;
		disp8 = dp & 0xFF;
		r = (dp & 0x7000) >> 12;
		dispreg = dp & 0x8000 ? m68k_areg(regs,r) : m68k_dreg(regs,r);
		if (!(dp & 0x800)) dispreg = (INT32)(INT16)(dispreg);
		dispreg <<= (dp >> 9) & 3;

		if (dp & 0x100) {
			INT32 outer = 0, disp = 0;
			INT32 base = m68k_areg(regs,reg);
			char name[10];
			sprintf (name,"A%d, ",reg);
			if (dp & 0x80) { base = 0; name[0] = 0; }
			if (dp & 0x40) dispreg = 0;
			if ((dp & 0x30) == 0x20) { disp = (INT32)(INT16)get_iword_1 (m68kpc_offset); m68kpc_offset += 2; }
			if ((dp & 0x30) == 0x30) { disp = get_ilong_1 (m68kpc_offset); m68kpc_offset += 4; }
			base += disp;

			if ((dp & 0x3) == 0x2) { outer = (INT32)(INT16)get_iword_1 (m68kpc_offset); m68kpc_offset += 2; }
			if ((dp & 0x3) == 0x3) { outer = get_ilong_1 (m68kpc_offset); m68kpc_offset += 4; }

			if (!(dp & 4)) base += dispreg;
			if (dp & 3) base = cpu_readmem24_dword(base);
			if (dp & 4) base += dispreg;

			addr = base + outer;
			sprintf (buffer,"(%s%c%d.%c*%d+%d)+%d == $%08lx", name,
				dp & 0x8000 ? 'A' : 'D', (int)r, dp & 0x800 ? 'L' : 'W',
				1 << ((dp >> 9) & 3),
				disp,outer,
				(unsigned long)addr);
		} else {
			addr = m68k_areg(regs,reg) + (INT32)((INT8)disp8) + dispreg;
			sprintf (buffer,"(A%d, %c%d.%c*%d, $%02x) == $%08lx", reg,
				dp & 0x8000 ? 'A' : 'D', (int)r, dp & 0x800 ? 'L' : 'W',
				1 << ((dp >> 9) & 3), disp8,
				(unsigned long)addr);
		}
		break;
	case PC16:
		addr = m68k_getpc () + m68kpc_offset;
		disp16 = get_iword_1 (m68kpc_offset); m68kpc_offset += 2;
		addr += (INT16)disp16;
		sprintf (buffer,"(PC,$%04x) == $%08lx", disp16 & 0xffff,(unsigned long)addr);
		break;
	case PC8r:
		addr = m68k_getpc () + m68kpc_offset;
		dp = get_iword_1 (m68kpc_offset); m68kpc_offset += 2;
		disp8 = dp & 0xFF;
		r = (dp & 0x7000) >> 12;
		dispreg = dp & 0x8000 ? m68k_areg(regs,r) : m68k_dreg(regs,r);
		if (!(dp & 0x800)) dispreg = (INT32)(INT16)(dispreg);
		dispreg <<= (dp >> 9) & 3;

		if (dp & 0x100) {
			INT32 outer = 0,disp = 0;
			INT32 base = addr;
			char name[10];
			sprintf (name,"PC, ");
			if (dp & 0x80) { base = 0; name[0] = 0; }
			if (dp & 0x40) dispreg = 0;
			if ((dp & 0x30) == 0x20) { disp = (INT32)(INT16)get_iword_1 (m68kpc_offset); m68kpc_offset += 2; }
			if ((dp & 0x30) == 0x30) { disp = get_ilong_1 (m68kpc_offset); m68kpc_offset += 4; }
			base += disp;

			if ((dp & 0x3) == 0x2) { outer = (INT32)(INT16)get_iword_1 (m68kpc_offset); m68kpc_offset += 2; }
			if ((dp & 0x3) == 0x3) { outer = get_ilong_1 (m68kpc_offset); m68kpc_offset += 4; }

			if (!(dp & 4)) base += dispreg;
			if (dp & 3) base = cpu_readmem24_dword (base);
			if (dp & 4) base += dispreg;

			addr = base + outer;
			sprintf (buffer,"(%s%c%d.%c*%d+%d)+%d == $%08lx", name,
				dp & 0x8000 ? 'A' : 'D', (int)r, dp & 0x800 ? 'L' : 'W',
				1 << ((dp >> 9) & 3),
				disp,outer,
				(unsigned long)addr);
		} else {
			addr += (INT32)((INT8)disp8) + dispreg;
			sprintf (buffer,"(PC, %c%d.%c*%d, $%02x) == $%08lx", dp & 0x8000 ? 'A' : 'D',
				(int)r, dp & 0x800 ? 'L' : 'W',  1 << ((dp >> 9) & 3),
				disp8, (unsigned long)addr);
		}
		break;
	case absw:
		sprintf (buffer,"$%08lx", (unsigned long)(INT32)(INT16)get_iword_1 (m68kpc_offset));
		m68kpc_offset += 2;
		break;
	case absl:
		sprintf (buffer,"$%08lx", (unsigned long)get_ilong_1 (m68kpc_offset));
		m68kpc_offset += 4;
		break;
	case imm:
		switch (size){
		case sz_byte:
			sprintf (buffer,"#$%02x", (unsigned int)(get_iword_1 (m68kpc_offset) & 0xff));
			m68kpc_offset += 2;
			break;
		case sz_word:
			sprintf (buffer,"#$%04x", (unsigned int)(get_iword_1 (m68kpc_offset) & 0xffff));
			m68kpc_offset += 2;
			break;
		case sz_long:
			sprintf (buffer,"#$%08lx", (unsigned long)(get_ilong_1 (m68kpc_offset)));
			m68kpc_offset += 4;
			break;
		default:
			break;
		}
		break;
		case imm0:
			offset = (INT32)(INT8)get_iword_1 (m68kpc_offset);
			m68kpc_offset += 2;
			sprintf (buffer,"#$%02x", (unsigned int)(offset & 0xff));
			break;
		case imm1:
			offset = (INT32)(INT16)get_iword_1 (m68kpc_offset);
			m68kpc_offset += 2;
			sprintf (buffer,"#$%04x", (unsigned int)(offset & 0xffff));
			break;
		case imm2:
			offset = (INT32)get_ilong_1 (m68kpc_offset);
			m68kpc_offset += 4;
			sprintf (buffer,"#$%08lx", (unsigned long)offset);
			break;
		case immi:
			offset = (INT32)(INT8)(reg & 0xff);
			sprintf (buffer,"#$%08lx", (unsigned long)offset);
			break;
		default:
			break;
    }
    if (buf == 0)
		(*debug_out) ("%s", buffer);
    else
		strcat (buf, buffer);
    return offset;
}


UINT32 get_disp_ea_020 (UINT32 base, UINT32 dp)
{
    int reg = (dp >> 12) & 15;
    INT32 regd = regs.regs[reg];
    if ((dp & 0x800) == 0)
		regd = (INT32)(INT16)regd;
    regd <<= (dp >> 9) & 3;
    if (dp & 0x100) {
		INT32 outer = 0;
		if (dp & 0x80) base = 0;
		if (dp & 0x40) regd = 0;

		if ((dp & 0x30) == 0x20) base += (INT32)(INT16)next_iword();
		if ((dp & 0x30) == 0x30) base += next_ilong();

		if ((dp & 0x3) == 0x2) outer = (INT32)(INT16)next_iword();
		if ((dp & 0x3) == 0x3) outer = next_ilong();

		if ((dp & 0x4) == 0) base += regd;
		if (dp & 0x3) base = cpu_readmem24_dword (base);
		if (dp & 0x4) base += regd;

		return base + outer;
    } else {
		return base + (INT32)((INT8)dp) + regd;
    }
}

void MakeSR (void)
{
    regs.sr = ((regs.t1 << 15) | (regs.t0 << 14)
	       | (regs.s << 13) | (regs.m << 12) | (regs.intmask << 8)
		   | (GET_XFLG << 4) | (GET_NFLG << 3) | (GET_ZFLG << 2) | (GET_VFLG << 1)
		   | GET_CFLG);
}

void MakeFromSR (void)
{
    int oldm = regs.m;
    int olds = regs.s;

    regs.t1 = (regs.sr >> 15) & 1;
    regs.t0 = (regs.sr >> 14) & 1;
    regs.s = (regs.sr >> 13) & 1;
    regs.m = (regs.sr >> 12) & 1;
    regs.intmask = (regs.sr >> 8) & 7;
    SET_XFLG ((regs.sr >> 4) & 1);
    SET_NFLG ((regs.sr >> 3) & 1);
    SET_ZFLG ((regs.sr >> 2) & 1);
    SET_VFLG ((regs.sr >> 1) & 1);
    SET_CFLG (regs.sr & 1);
	if (olds != regs.s) {
		if (olds) {
			if (oldm)
				regs.msp = m68k_areg(regs, 7);
			else
				regs.isp = m68k_areg(regs, 7);
			m68k_areg(regs, 7) = regs.usp;
		} else {
			regs.usp = m68k_areg(regs, 7);
			m68k_areg(regs, 7) = regs.m ? regs.msp : regs.isp;
		}
	} else if (olds && oldm != regs.m) {
		if (oldm) {
			regs.msp = m68k_areg(regs, 7);
			m68k_areg(regs, 7) = regs.isp;
		} else {
			regs.isp = m68k_areg(regs, 7);
			m68k_areg(regs, 7) = regs.msp;
		}
	}
}

void Exception(int nr, CPTR oldpc)
{
    MakeSR();
    if (!regs.s) {
		regs.usp = m68k_areg(regs, 7);
		m68k_areg(regs, 7) = regs.m ? regs.msp : regs.isp;
		regs.s = 1;
    }
    if (nr == 2 || nr == 3) {
		int i;
		/* @@@ this is probably wrong (?) */
		for (i = 0 ; i < 12 ; i++) {
			m68k_areg(regs, 7) -= 2;
			cpu_writemem24_word (m68k_areg(regs, 7), 0);
		}
		m68k_areg(regs, 7) -= 2;
		cpu_writemem24_word(m68k_areg(regs, 7), 0xa000 + nr * 4);
	} else if (nr ==5 || nr == 6 || nr == 7 || nr == 9) {
		m68k_areg(regs, 7) -= 4;
		cpu_writemem24_dword (m68k_areg(regs, 7), oldpc);
		m68k_areg(regs, 7) -= 2;
		cpu_writemem24_word (m68k_areg(regs, 7), 0x2000 + nr * 4);
	} else if (regs.m && nr >= 24 && nr < 32) {
		m68k_areg(regs, 7) -= 2;
		cpu_writemem24_word (m68k_areg(regs, 7), nr * 4);
		m68k_areg(regs, 7) -= 4;
		cpu_writemem24_dword (m68k_areg(regs, 7), m68k_getpc ());
		m68k_areg(regs, 7) -= 2;
		cpu_writemem24_word (m68k_areg(regs, 7), regs.sr);
		regs.sr |= (1 << 13);
		regs.msp = m68k_areg(regs, 7);
		m68k_areg(regs, 7) = regs.isp;
		m68k_areg(regs, 7) -= 2;
		cpu_writemem24_word (m68k_areg(regs, 7), 0x1000 + nr * 4);
	} else {
		m68k_areg(regs, 7) -= 2;
		cpu_writemem24_word (m68k_areg(regs, 7), nr * 4);
	}
    m68k_areg(regs, 7) -= 4;
    cpu_writemem24_dword (m68k_areg(regs, 7), m68k_getpc ());
	//kludge_me_do:
    m68k_areg(regs, 7) -= 2;
    cpu_writemem24_word (m68k_areg(regs, 7), regs.sr);
    m68k_setpc (cpu_readmem24_dword (regs.vbr + 4*nr));
    regs.t1 = regs.t0 = regs.m = 0;
}


static int caar, cacr;

int m68k_move2c (int regno, UINT32 *regp)
{
	switch (regno) {
	case 0: regs.sfc = *regp & 7; break;
	case 1: regs.dfc = *regp & 7; break;
	case 2: cacr = *regp & 0x3; break;	/* ignore C and CE */
	case 0x800: regs.usp = *regp; break;
	case 0x801: regs.vbr = *regp; break;
	case 0x802: caar = *regp &0xfc; break;
	case 0x803: regs.msp = *regp; if (regs.m == 1) m68k_areg(regs, 7) = regs.msp; break;
	case 0x804: regs.isp = *regp; if (regs.m == 0) m68k_areg(regs, 7) = regs.isp; break;
	default:
		op_illg (0x4E7B);
		return 0;
	}
    return 1;
}

int m68k_movec2 (int regno, UINT32 *regp)
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
		return 0;
	}
    return 1;
}

static DEF_INLINE int
div_unsigned(UINT32 src_hi, UINT32 src_lo, UINT32 div, UINT32 *quot, UINT32 *rem)
{
	UINT32 q = 0, cbit = 0;
	int i;

	if (div <= src_hi) {
		return 1;
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
	return 0;
}

void m68k_divl (UINT32 opcode, UINT32 src, UINT16 extra, CPTR oldpc)
{
	(void)(opcode);
    if (src == 0) {
		Exception (5, oldpc);
		return;
    }
    if (extra & 0x800) {
		/* signed variant */
		INT64 a = (INT64)(INT32)m68k_dreg(regs, (extra >> 12) & 7);
		INT64 quot, rem;

		if (extra & 0x400) {
			a &= 0xffffffffu;
			a |= (INT64)m68k_dreg(regs, extra & 7) << 32;
		}
		rem = a % (INT64)(INT32)src;
		quot = a / (INT64)(INT32)src;
		if ((quot & (UINT64)(0xffffffff80000000)) != 0
			&& (quot & (UINT64)(0xffffffff80000000)) != (UINT64)(0xffffffff80000000))
		{
			SET_VFLG (1);
			SET_NFLG (1);
			SET_CFLG (0);
		} else {
			if (((INT32)rem < 0) != ((INT64)a < 0)) rem = -rem;
			SET_VFLG (0);
			SET_CFLG (0);
			SET_ZFLG (((INT32)quot) == 0);
			SET_NFLG (((INT32)quot) < 0);
			m68k_dreg(regs, extra & 7) = rem;
			m68k_dreg(regs, (extra >> 12) & 7) = quot;
		}
    } else {
		/* unsigned */
		UINT64 a = (UINT64)(INT32)m68k_dreg(regs, (extra >> 12) & 7);
		UINT64 quot, rem;

		if (extra & 0x400) {
			a &= 0xffffffffu;
			a |= (UINT64)m68k_dreg(regs, extra & 7) << 32;
		}
		rem = a % (UINT64)src;
		quot = a / (UINT64)src;
		if (quot > 0xffffffffu) {
			SET_VFLG (1);
			SET_NFLG (1);
			SET_CFLG (0);
		} else {
			SET_VFLG (0);
			SET_CFLG (0);
			SET_ZFLG (((INT32)quot) == 0);
			SET_NFLG (((INT32)quot) < 0);
			m68k_dreg(regs, extra & 7) = rem;
			m68k_dreg(regs, (extra >> 12) & 7) = quot;
		}
    }
}

static DEF_INLINE void
mul_unsigned(UINT32 src1, UINT32 src2, UINT32 *dst_hi, UINT32 *dst_lo)
{
	UINT32 r0 = (src1 & 0xffff) * (src2 & 0xffff);
	UINT32 r1 = ((src1 >> 16) & 0xffff) * (src2 & 0xffff);
	UINT32 r2 = (src1 & 0xffff) * ((src2 >> 16) & 0xffff);
	UINT32 r3 = ((src1 >> 16) & 0xffff) * ((src2 >> 16) & 0xffff);
	UINT32 lo;

	lo = r0 + ((r1 << 16) & 0xffff0000ul);
	if (lo < r0) r3++;
	r0 = lo;
	lo = r0 + ((r2 << 16) & 0xffff0000ul);
	if (lo < r0) r3++;
	r3 += ((r1 >> 16) & 0xffff) + ((r2 >> 16) & 0xffff);
	*dst_lo = lo;
	*dst_hi = r3;
}

void m68k_mull (UINT32 opcode, UINT32 src, UINT16 extra)
{
	(void)(opcode);
    if (extra & 0x800) {
		/* signed variant */
		UINT64 a = (INT64)(INT32)m68k_dreg(regs, (extra >> 12) & 7);

		a *= (INT64)(INT32)src;
		SET_VFLG (0);
		SET_CFLG (0);
		SET_ZFLG (a == 0);
		SET_NFLG (a < 0);
		if (extra & 0x400)
			m68k_dreg(regs, extra & 7) = a >> 32;
		else if ((a & (UINT64)(0xffffffff80000000)) != 0
			&& (a & (UINT64)(0xffffffff80000000)) != (UINT64)(0xffffffff80000000))
		{
			SET_VFLG (1);
		}
		m68k_dreg(regs, (extra >> 12) & 7) = (UINT32)a;
    } else {
		/* unsigned */
		UINT64 a = (UINT64)(UINT32)m68k_dreg(regs, (extra >> 12) & 7);

		a *= (UINT64)src;
		SET_VFLG (0);
		SET_CFLG (0);
		SET_ZFLG (a == 0);
		SET_NFLG (((UINT64)a) < 0);
		if (extra & 0x400)
			m68k_dreg(regs, extra & 7) = a >> 32;
		else if ((a & (UINT64)(0xffffffff00000000)) != 0) {
			SET_VFLG (1);
		}
		m68k_dreg(regs, (extra >> 12) & 7) = (UINT32)a;
    }
}
static char* ccnames[] =
{ "T ","F ","HI","LS","CC","CS","NE","EQ",
"VC","VS","PL","MI","GE","LT","GT","LE" };

void Reset68020 (void)
{
    m68k_areg (regs, 7) = cpu_readmem24_dword(0);
    m68k_setpc (cpu_readmem24_dword(4));
    regs.s = 1;
    regs.m = 0;
    regs.stopped = 0;
    regs.t1 = 0;
    regs.t0 = 0;
    SET_ZFLG (0);
    SET_XFLG (0);
    SET_CFLG (0);
    SET_VFLG (0);
    SET_NFLG (0);
    regs.intmask = 7;
    regs.vbr = regs.sfc = regs.dfc = 0;
	regs.sr=0x2700;
	MakeFromSR();
}

unsigned long op_illg (UINT32 opcode)
{
    // RAINE #$xx

    if((opcode&0xFF00)==0x7F00){
       F3SystemEEPROMAccess(opcode&0xFF);
       m68k_incpc(2);
       return 4;
    }

    // LINEF #$xxx

    if((opcode&0xF000)==0xF000){
	Exception(0xB,0);
	return 4;
    }

    // LINEA #$xxx

    if((opcode&0xF000)==0xA000){
	Exception(0xA,0);
	return 4;
    }

    print_debug("[Illegal 68020 Instruction $%08x:%04x]\n",regs.pc,opcode);

    Exception (4,0);
    return 4;
}

void m68k_disasm (CPTR addr, CPTR *nextpc, int cnt, output_func_ptr debug_out)
{
    CPTR newpc = 0;
    m68kpc_offset = addr - m68k_getpc ();
    while (cnt-- > 0) {
		char instrname[20],*ccpt;
		int opwords;
		UINT32 opcode;
		struct mnemolookup *lookup;
		struct instr *dp;
		(*debug_out) ("%08lx: ", m68k_getpc () + m68kpc_offset);
		for (opwords = 0; opwords < 5; opwords++){
			(*debug_out) ("%04x ", get_iword_1 (m68kpc_offset + opwords*2));
		}
		opcode = get_iword_1 (m68kpc_offset);
		m68kpc_offset += 2;
		if (cpufunctbl[opcode] == op_illg_1) {
			opcode = 0x4AFC;
		}
		dp = table68k + opcode;
		for (lookup = lookuptab;lookup->mnemo != dp->mnemo; lookup++)
			;

		strcpy (instrname, lookup->name);
		ccpt = strstr (instrname, "cc");
		if (ccpt != 0) {
			strncpy (ccpt, ccnames[dp->cc], 2);
		}
		(*debug_out) ("%s", instrname);
		switch (dp->size){
		case sz_byte: (*debug_out) (".B "); break;
		case sz_word: (*debug_out) (".W "); break;
		case sz_long: (*debug_out) (".L "); break;
		default: (*debug_out) ("   "); break;
		}

		if (dp->suse) {
			newpc = m68k_getpc () + m68kpc_offset;
			newpc += ShowEA (dp->sreg, dp->smode, dp->size, 0, debug_out);
		}
		if (dp->suse && dp->duse)
			(*debug_out) (",");
		if (dp->duse) {
			newpc = m68k_getpc () + m68kpc_offset;
			newpc += ShowEA (dp->dreg, dp->dmode, dp->size, 0, debug_out);
		}
		if (ccpt != 0) {
			if (cctrue(dp->cc))
				(*debug_out) (" == %08lx (TRUE)", newpc);
			else
				(*debug_out) (" == %08lx (FALSE)", newpc);
		} else if ((opcode & 0xff00) == 0x6100) /* BSR */
			(*debug_out) (" == %08lx", newpc);
		(*debug_out) ("\n");
    }
    if (nextpc)
		*nextpc = m68k_getpc () + m68kpc_offset;
}

static int stopped_68020;

void Execute68020(int c)
{
	UINT32 opcode;

	cycles = c;
        stopped_68020 = 0;

    while ( cycles > 0 && !stopped_68020 )
	{
		opcode = get_iword (0);
		cycles -= (*cpufunctbl[opcode])(opcode);
		opcode = get_iword (0);
		cycles -= (*cpufunctbl[opcode])(opcode);
		opcode = get_iword (0);
		cycles -= (*cpufunctbl[opcode])(opcode);
		opcode = get_iword (0);
		cycles -= (*cpufunctbl[opcode])(opcode);
	}
    if (stopped_68020)
        cycles = 0;
}

void Interrupt68020(int level)
{
	MakeSR();
	if(level>=((regs.sr&0xf00)>>8)) Exception(level+24,regs.pc);
}

void Stop68020(void)
{
    stopped_68020 = 1;
    /* We can't just set the cycles to 0 in the C version because
     * the cycles are updated at the end of the instruction so a direct
     * initialization is lost ! */
}
