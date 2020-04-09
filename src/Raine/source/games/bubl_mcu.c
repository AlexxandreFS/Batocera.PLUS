/* Auto-generated from mcu.asm! Do not modify! */

#include <stdlib.h>
#include "deftypes.h"
#include "debug.h"
#include "ingame.h"

UINT8 BubbleBobble_MCU_RDMEM(int a);
void BubbleBobble_MCU_WRMEM(int a, UINT8 v);
#define MCU_RDMEM(a) BubbleBobble_MCU_RDMEM(a)
#define MCU_WRMEM(a,v) BubbleBobble_MCU_WRMEM(a,v)

#include "m68705.h"

static int unpacked;

void BubbleBobble_mcu_reset(void)
{
	m68705.pc = MCU_RDMEM(0x7ff) | (MCU_RDMEM(0x7fe) << 8);
	m68705.sp = 0x7f;
	m68705.a = m68705.x = 0x00;
	m68705.flag_i = 0;
	m68705.flag_n = m68705.flag_h = m68705.flag_z = m68705.flag_c = 0;
	unpacked = 0;
}

/*

arghh, fucking msvc, goto jumptables not supported!!! :((

*/

#if defined(RAINE_DOS) || defined(RAINE_UNIX)

#define LABEL(addr) \
L0x##addr           \

#else

#define LABEL(addr) \
case 0x##addr       \

#undef JUMP

#define JUMP(addr) \
break;             \

#undef JUMP_IMM

#define JUMP_IMM(adr) \
{ m68705.pc = adr;    \
break; }              \

#endif

void BubbleBobble_mcu(int bih_count)
{
	UINT8 temp; //, dummy;
	UINT16 addr;
	UINT8 x = m68705.x;
	UINT8 a = m68705.a;
	UINT16 sp = m68705.sp;
	UINT8 flag_c = m68705.flag_c;
	UINT8 flag_h = m68705.flag_h;
	UINT8 flag_n = m68705.flag_n;
	UINT8 flag_z = m68705.flag_z;
#if defined(RAINE_DOS) || defined(RAINE_UNIX)
	static const M68705_JumpTable jump_table[] = {
		{ 0x080, &&L0x080 },
		{ 0x086, &&L0x086 },
		{ 0x099, &&L0x099 },
		{ 0x09f, &&L0x09f },
		{ 0x0b2, &&L0x0b2 },
		{ 0x0b8, &&L0x0b8 },
		{ 0x0c9, &&L0x0c9 },
		{ 0x0cf, &&L0x0cf },
		{ 0x0e8, &&L0x0e8 },
		{ 0x0f9, &&L0x0f9 },
		{ 0x10d, &&L0x10d },
		{ 0x10e, &&L0x10e },
		{ 0x128, &&L0x128 },
		{ 0x12a, &&L0x12a },
		{ 0x131, &&L0x131 },
		{ 0x134, &&L0x134 },
		{ 0x139, &&L0x139 },
		{ 0x147, &&L0x147 },
		{ 0x14a, &&L0x14a },
		{ 0x150, &&L0x150 },
		{ 0x156, &&L0x156 },
		{ 0x15c, &&L0x15c },
		{ 0x162, &&L0x162 },
		{ 0x168, &&L0x168 },
		{ 0x16e, &&L0x16e },
		{ 0x16f, &&L0x16f },
		{ 0x175, &&L0x175 },
		{ 0x17b, &&L0x17b },
		{ 0x181, &&L0x181 },
		{ 0x187, &&L0x187 },
		{ 0x18d, &&L0x18d },
		{ 0x193, &&L0x193 },
		{ 0x199, &&L0x199 },
		{ 0x19f, &&L0x19f },
		{ 0x1a5, &&L0x1a5 },
		{ 0x1a6, &&L0x1a6 },
		{ 0x1b2, &&L0x1b2 },
		{ 0x1b8, &&L0x1b8 },
		{ 0x1be, &&L0x1be },
		{ 0x1c4, &&L0x1c4 },
		{ 0x1ca, &&L0x1ca },
		{ 0x1d0, &&L0x1d0 },
		{ 0x1d6, &&L0x1d6 },
		{ 0x1dc, &&L0x1dc },
		{ 0x1e2, &&L0x1e2 },
		{ 0x1e3, &&L0x1e3 },
		{ 0x1e9, &&L0x1e9 },
		{ 0x1ef, &&L0x1ef },
		{ 0x1f5, &&L0x1f5 },
		{ 0x1f9, &&L0x1f9 },
		{ 0x200, &&L0x200 },
		{ 0x20b, &&L0x20b },
		{ 0x22a, &&L0x22a },
		{ 0x22e, &&L0x22e },
		{ 0x236, &&L0x236 },
		{ 0x238, &&L0x238 },
		{ 0x23a, &&L0x23a },
		{ 0x243, &&L0x243 },
		{ 0x24a, &&L0x24a },
		{ 0x269, &&L0x269 },
		{ 0x26d, &&L0x26d },
		{ 0x275, &&L0x275 },
		{ 0x277, &&L0x277 },
		{ 0x279, &&L0x279 },
		{ 0x282, &&L0x282 },
		{ 0x28a, &&L0x28a },
		{ 0x28b, &&L0x28b },
		{ 0x291, &&L0x291 },
		{ 0x29b, &&L0x29b },
		{ 0x2a1, &&L0x2a1 },
		{ 0x2a5, &&L0x2a5 },
		{ 0x2ac, &&L0x2ac },
		{ 0x2b7, &&L0x2b7 },
		{ 0x2d6, &&L0x2d6 },
		{ 0x2da, &&L0x2da },
		{ 0x2e2, &&L0x2e2 },
		{ 0x2e4, &&L0x2e4 },
		{ 0x2e6, &&L0x2e6 },
		{ 0x2ef, &&L0x2ef },
		{ 0x2f6, &&L0x2f6 },
		{ 0x315, &&L0x315 },
		{ 0x319, &&L0x319 },
		{ 0x321, &&L0x321 },
		{ 0x323, &&L0x323 },
		{ 0x325, &&L0x325 },
		{ 0x32e, &&L0x32e },
		{ 0x336, &&L0x336 },
		{ 0x38a, &&L0x38a },
		{ 0x38d, &&L0x38d },
		{ 0x390, &&L0x390 },
		{ 0x393, &&L0x393 },
		{ 0x396, &&L0x396 },
		{ 0x39e, &&L0x39e },
		{ 0x3a6, &&L0x3a6 },
		{ 0, NULL }
	};

	if (!unpacked) { M68705_Unpack(&jump_table[0], &&invalid_pc); unpacked=1; }

/* code starts here */
	JUMP(m68705.pc);
#else

LOOP:
      switch(m68705.pc){

#endif

LABEL(080):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x010, x);

//LABEL(082):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(084):	/* bsr */
	PUSHWORD(0x086);
	JUMP_IMM(0x0f9);

LABEL(086):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(088):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//LABEL(08a):	/* bset3 */
	BSET(0x001, 3);

//LABEL(08c):	/* bclr4 */
	BCLR(0x001, 4);

//LABEL(08e):	/* bclr0 */
	BCLR(0x001, 0);

//LABEL(090):	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//LABEL(092):	/* bset0 */
	BSET(0x001, 0);

//LABEL(094):	/* bset4 */
	BSET(0x001, 4);

//LABEL(096):	/* ldx */
	addr = 0x010;
	x = MCU_RDMEM(0x010);
	SET_NZ(x);

//LABEL(098):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(099):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x010, x);

//LABEL(09b):	/* ldx */
	x = 0x00c;
	SET_NZ(x);

//LABEL(09d):	/* bsr */
	PUSHWORD(0x09f);
	JUMP_IMM(0x0f9);

LABEL(09f):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(0a1):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//LABEL(0a3):	/* bset3 */
	BSET(0x001, 3);

//LABEL(0a5):	/* bclr4 */
	BCLR(0x001, 4);

//LABEL(0a7):	/* bclr0 */
	BCLR(0x001, 0);

//LABEL(0a9):	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//LABEL(0ab):	/* bset0 */
	BSET(0x001, 0);

//LABEL(0ad):	/* bset4 */
	BSET(0x001, 4);

//LABEL(0af):	/* ldx */
	addr = 0x010;
	x = MCU_RDMEM(0x010);
	SET_NZ(x);

//LABEL(0b1):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(0b2):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x010, x);

//LABEL(0b4):	/* ldx */
	x = 0x00c;
	SET_NZ(x);

//LABEL(0b6):	/* bsr */
	PUSHWORD(0x0b8);
	JUMP_IMM(0x0f9);

LABEL(0b8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(0ba):	/* bclr3 */
	BCLR(0x001, 3);

//LABEL(0bc):	/* bclr4 */
	BCLR(0x001, 4);

//LABEL(0be):	/* bset4 */
	BSET(0x001, 4);

//LABEL(0c0):	/* bset3 */
	BSET(0x001, 3);

//LABEL(0c2):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(0c4):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//LABEL(0c6):	/* ldx */
	addr = 0x010;
	x = MCU_RDMEM(0x010);
	SET_NZ(x);

//LABEL(0c8):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(0c9):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x010, x);

//LABEL(0cb):	/* ldx */
	x = 0x00f;
	SET_NZ(x);

//LABEL(0cd):	/* bsr */
	PUSHWORD(0x0cf);
	JUMP_IMM(0x0f9);

LABEL(0cf):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(0d1):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//LABEL(0d3):	/* bset3 */
	BSET(0x001, 3);

//LABEL(0d5):	/* bclr4 */
	BCLR(0x001, 4);

//LABEL(0d7):	/* bclr0 */
	BCLR(0x001, 0);

//LABEL(0d9):	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//LABEL(0db):	/* bset0 */
	BSET(0x001, 0);

//LABEL(0dd):	/* bset4 */
	BSET(0x001, 4);

//LABEL(0df):	/* ldx */
	addr = 0x010;
	x = MCU_RDMEM(0x010);
	SET_NZ(x);

//LABEL(0e1):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

//LABEL(0e2):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x010, x);

//LABEL(0e4):	/* ldx */
	x = 0x00f;
	SET_NZ(x);

//LABEL(0e6):	/* bsr */
	PUSHWORD(0x0e8);
	JUMP_IMM(0x0f9);

LABEL(0e8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(0ea):	/* bclr3 */
	BCLR(0x001, 3);

//LABEL(0ec):	/* bclr4 */
	BCLR(0x001, 4);

//LABEL(0ee):	/* bset4 */
	BSET(0x001, 4);

//LABEL(0f0):	/* bset3 */
	BSET(0x001, 3);

//LABEL(0f2):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(0f4):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//LABEL(0f6):	/* ldx */
	addr = 0x010;
	x = MCU_RDMEM(0x010);
	SET_NZ(x);

//LABEL(0f8):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(0f9):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x000, x);

//LABEL(0fb):	/* ldx */
	x = 0x0ff;
	SET_NZ(x);

//LABEL(0fd):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//LABEL(0ff):	/* bclr2 */
	BCLR(0x001, 2);

//LABEL(101):	/* bset2 */
	BSET(0x001, 2);

//LABEL(103):	/* ldx */
	addr = 0x012;
	x = MCU_RDMEM(0x012);
	SET_NZ(x);

//LABEL(105):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x000, x);

//LABEL(107):	/* bclr1 */
	BCLR(0x001, 1);

//LABEL(109):	/* bset1 */
	BSET(0x001, 1);

//LABEL(10b):	/* bih */
//BIH 0x10d
	if (--bih_count == 0) {
	m68705.pc = 0x10d;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
	return;
	}

LABEL(10d):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(10e):	/* sei */
//INIT_PC
	m68705.flag_i = 1;

//LABEL(10f):	/* rsp */
	sp = 0x7f;

//LABEL(110):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(112):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//LABEL(114):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(116):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x006, a);

//LABEL(118):	/* lda */
	a = 0x0df;
	SET_NZ(a);

//LABEL(11a):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//LABEL(11c):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(11e):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x005, a);

//LABEL(120):	/* lda */
	a = 0x0df;
	SET_NZ(a);

//LABEL(122):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//LABEL(124):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(126):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

LABEL(128):	/* jsr */
	PUSHWORD(0x12a);
	JUMP_IMM(0x099);

LABEL(12a):	/* cmpa */
	SUB(temp, a, 0x02e);

//LABEL(12c):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x128);

//LABEL(12e):	/* jsr */
	PUSHWORD(0x131);
	JUMP_IMM(0x1a6);

LABEL(131):	/* jsr */
	PUSHWORD(0x134);
	JUMP_IMM(0x1a6);

LABEL(134):	/* cli */
	m68705.flag_i = 0;

//LABEL(135):	/* ldx */
	x = 0x000;
	SET_NZ(x);

//LABEL(137):	/* lda */
	a = 0x000;
	SET_NZ(a);

LABEL(139):	/* inca */
	INC(a, a);

//LABEL(13a):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x139);

//LABEL(13c):	/* incx */
	INC(x, x);

//LABEL(13d):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x139);

//LABEL(13f):	/* lda */
	a = 0x085;
	SET_NZ(a);

//LABEL(141):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(143):	/* lda */
	a = 0x037;
	SET_NZ(a);

//LABEL(145):	/* jsr */
	PUSHWORD(0x147);
	JUMP_IMM(0x0b2);

LABEL(147):	/* jmp */
	JUMP_IMM(0x38a);

LABEL(14a):	/* lda */
	a = 0x088;
	SET_NZ(a);

//LABEL(14c):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(14e):	/* jsr */
	PUSHWORD(0x150);
	JUMP_IMM(0x0c9);

LABEL(150):	/* lda */
	a = 0x08c;
	SET_NZ(a);

//LABEL(152):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(154):	/* jsr */
	PUSHWORD(0x156);
	JUMP_IMM(0x0c9);

LABEL(156):	/* lda */
	a = 0x090;
	SET_NZ(a);

//LABEL(158):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(15a):	/* jsr */
	PUSHWORD(0x15c);
	JUMP_IMM(0x0c9);

LABEL(15c):	/* lda */
	a = 0x097;
	SET_NZ(a);

//LABEL(15e):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(160):	/* jsr */
	PUSHWORD(0x162);
	JUMP_IMM(0x0c9);

LABEL(162):	/* lda */
	a = 0x096;
	SET_NZ(a);

//LABEL(164):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(166):	/* jsr */
	PUSHWORD(0x168);
	JUMP_IMM(0x0c9);

LABEL(168):	/* lda */
	a = 0x098;
	SET_NZ(a);

//LABEL(16a):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(16c):	/* jsr */
	PUSHWORD(0x16e);
	JUMP_IMM(0x0c9);

LABEL(16e):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(16f):	/* lda */
	a = 0x098;
	SET_NZ(a);

//LABEL(171):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(173):	/* jsr */
	PUSHWORD(0x175);
	JUMP_IMM(0x0c9);

LABEL(175):	/* lda */
	a = 0x01e;
	SET_NZ(a);

//LABEL(177):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(179):	/* jsr */
	PUSHWORD(0x17b);
	JUMP_IMM(0x099);

LABEL(17b):	/* lda */
	a = 0x094;
	SET_NZ(a);

//LABEL(17d):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(17f):	/* jsr */
	PUSHWORD(0x181);
	JUMP_IMM(0x0c9);

LABEL(181):	/* lda */
	a = 0x06f;
	SET_NZ(a);

//LABEL(183):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(185):	/* jsr */
	PUSHWORD(0x187);
	JUMP_IMM(0x099);

LABEL(187):	/* lda */
	a = 0x095;
	SET_NZ(a);

//LABEL(189):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(18b):	/* jsr */
	PUSHWORD(0x18d);
	JUMP_IMM(0x0c9);

LABEL(18d):	/* lda */
	a = 0x070;
	SET_NZ(a);

//LABEL(18f):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(191):	/* jsr */
	PUSHWORD(0x193);
	JUMP_IMM(0x099);

LABEL(193):	/* lda */
	a = 0x095;
	SET_NZ(a);

//LABEL(195):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(197):	/* jsr */
	PUSHWORD(0x199);
	JUMP_IMM(0x0c9);

LABEL(199):	/* lda */
	a = 0x07e;
	SET_NZ(a);

//LABEL(19b):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(19d):	/* jsr */
	PUSHWORD(0x19f);
	JUMP_IMM(0x099);

LABEL(19f):	/* lda */
	a = 0x095;
	SET_NZ(a);

//LABEL(1a1):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1a3):	/* jsr */
	PUSHWORD(0x1a5);
	JUMP_IMM(0x0c9);

LABEL(1a5):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(1a6):	/* lda */
	a = 0x01f;
	SET_NZ(a);

//LABEL(1a8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1aa):	/* lda */
	addr = 0x002;
	a = MCU_RDMEM(0x002);
	SET_NZ(a);

//LABEL(1ac):	/* anda */
	AND(a, a, 0x00f);
	SET_NZ(a);

//LABEL(1ae):	/* ora */
	OR(a, a, 0x0b0);
	SET_NZ(a);

//LABEL(1b0):	/* jsr */
	PUSHWORD(0x1b2);
	JUMP_IMM(0x0b2);

LABEL(1b2):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(1b4):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1b6):	/* jsr */
	PUSHWORD(0x1b8);
	JUMP_IMM(0x080);

LABEL(1b8):	/* ldx */
	x = 0x020;
	SET_NZ(x);

//LABEL(1ba):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x012, x);

//LABEL(1bc):	/* jsr */
	PUSHWORD(0x1be);
	JUMP_IMM(0x0b2);

LABEL(1be):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(1c0):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1c2):	/* jsr */
	PUSHWORD(0x1c4);
	JUMP_IMM(0x080);

LABEL(1c4):	/* ldx */
	x = 0x021;
	SET_NZ(x);

//LABEL(1c6):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x012, x);

//LABEL(1c8):	/* jsr */
	PUSHWORD(0x1ca);
	JUMP_IMM(0x0b2);

LABEL(1ca):	/* lda */
	a = 0x002;
	SET_NZ(a);

//LABEL(1cc):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1ce):	/* jsr */
	PUSHWORD(0x1d0);
	JUMP_IMM(0x080);

LABEL(1d0):	/* ldx */
	x = 0x022;
	SET_NZ(x);

//LABEL(1d2):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x012, x);

//LABEL(1d4):	/* jsr */
	PUSHWORD(0x1d6);
	JUMP_IMM(0x0b2);

LABEL(1d6):	/* lda */
	a = 0x003;
	SET_NZ(a);

//LABEL(1d8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1da):	/* jsr */
	PUSHWORD(0x1dc);
	JUMP_IMM(0x080);

LABEL(1dc):	/* ldx */
	x = 0x023;
	SET_NZ(x);

//LABEL(1de):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x012, x);

//LABEL(1e0):	/* jsr */
	PUSHWORD(0x1e2);
	JUMP_IMM(0x0b2);

LABEL(1e2):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(1e3):	/* lda */
	a = 0x05f;
	SET_NZ(a);

//LABEL(1e5):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1e7):	/* jsr */
	PUSHWORD(0x1e9);
	JUMP_IMM(0x099);

LABEL(1e9):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(1eb):	/* inc */
	addr = 0x012;
	INC(temp, MCU_RDMEM(0x012));
	MCU_WRMEM(addr, temp);

//LABEL(1ed):	/* jsr */
	PUSHWORD(0x1ef);
	JUMP_IMM(0x099);

LABEL(1ef):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(1f1):	/* inc */
	addr = 0x012;
	INC(temp, MCU_RDMEM(0x012));
	MCU_WRMEM(addr, temp);

//LABEL(1f3):	/* jsr */
	PUSHWORD(0x1f5);
	JUMP_IMM(0x099);

LABEL(1f5):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x016, a);

//LABEL(1f7):	/* ldx */
	x = 0x000;
	SET_NZ(x);

LABEL(1f9):	/* lda */
	addr = x + 0x337;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(1fc):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(1fe):	/* jsr */
	PUSHWORD(0x200);
	JUMP_IMM(0x099);

LABEL(200):	/* cmpa */
	SUB(temp, a, 0x080);

//LABEL(202):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x282);

//LABEL(204):	/* lda */
	addr = x + 0x33e;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(207):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(209):	/* jsr */
	PUSHWORD(0x20b);
	JUMP_IMM(0x099);

LABEL(20b):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(20d):	/* lda */
	addr = x + 0x34c;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(210):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(212):	/* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(214):	/* suba */
	addr = 0x011;
	SUB(a, a, MCU_RDMEM(0x011));

//LABEL(216):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(218):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x22a);

//LABEL(21a):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x22e);

//LABEL(21c):	/* eora */
	EOR(a, a, 0x0ff);
	SET_NZ(a);

//LABEL(21e):	/* adda */
	ADD(a, a, 0x001);

//LABEL(220):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(222):	/* cmpa */
	SUB(temp, a, 0x027);

//LABEL(224):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x236);

//LABEL(226):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(228):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x238);

LABEL(22a):	/* lda */
	a = 0x080;
	SET_NZ(a);

//LABEL(22c):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x238);

LABEL(22e):	/* cmpa */
	SUB(temp, a, 0x027);

//LABEL(230):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x236);

//LABEL(232):	/* lda */
	a = 0x002;
	SET_NZ(a);

//LABEL(234):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x238);

LABEL(236):	/* lda */
	a = 0x000;
	SET_NZ(a);

LABEL(238):	/* jsr */
	PUSHWORD(0x23a);
	JUMP_IMM(0x0b2);

LABEL(23a):	/* lda */
	addr = x + 0x353;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(23d):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(23f):	/* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(241):	/* jsr */
	PUSHWORD(0x243);
	JUMP_IMM(0x0b2);

LABEL(243):	/* lda */
	addr = x + 0x345;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(246):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(248):	/* jsr */
	PUSHWORD(0x24a);
	JUMP_IMM(0x099);

LABEL(24a):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(24c):	/* lda */
	addr = x + 0x35a;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(24f):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(251):	/* lda */
	addr = 0x016;
	a = MCU_RDMEM(0x016);
	SET_NZ(a);

//LABEL(253):	/* suba */
	addr = 0x011;
	SUB(a, a, MCU_RDMEM(0x011));

//LABEL(255):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(257):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x269);

//LABEL(259):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x26d);

//LABEL(25b):	/* eora */
	EOR(a, a, 0x0ff);
	SET_NZ(a);

//LABEL(25d):	/* adda */
	ADD(a, a, 0x001);

//LABEL(25f):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(261):	/* cmpa */
	SUB(temp, a, 0x047);

//LABEL(263):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x275);

//LABEL(265):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(267):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x277);

LABEL(269):	/* lda */
	a = 0x080;
	SET_NZ(a);

//LABEL(26b):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x277);

LABEL(26d):	/* cmpa */
	SUB(temp, a, 0x047);

//LABEL(26f):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x275);

//LABEL(271):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(273):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x277);

LABEL(275):	/* lda */
	a = 0x000;
	SET_NZ(a);

LABEL(277):	/* jsr */
	PUSHWORD(0x279);
	JUMP_IMM(0x0b2);

LABEL(279):	/* lda */
	addr = x + 0x361;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(27c):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(27e):	/* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(280):	/* jsr */
	PUSHWORD(0x282);
	JUMP_IMM(0x0b2);

LABEL(282):	/* incx */
	INC(x, x);

//LABEL(283):	/* cpx */
	SUB(temp, x, 0x007);

//LABEL(285):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x28b);

//LABEL(287):	/* jmp */
	JUMP_IMM(0x1f9);

LABEL(28a):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(28b):	/* lda */
	a = 0x067;
	SET_NZ(a);

//LABEL(28d):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(28f):	/* jsr */
	PUSHWORD(0x291);
	JUMP_IMM(0x099);

LABEL(291):	/* cmpa */
	SUB(temp, a, 0x000);

//LABEL(293):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x28a);

//LABEL(295):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x017, a);

//LABEL(297):	/* inc */
	addr = 0x012;
	INC(temp, MCU_RDMEM(0x012));
	MCU_WRMEM(addr, temp);

//LABEL(299):	/* jsr */
	PUSHWORD(0x29b);
	JUMP_IMM(0x099);

LABEL(29b):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x018, a);

//LABEL(29d):	/* inc */
	addr = 0x012;
	INC(temp, MCU_RDMEM(0x012));
	MCU_WRMEM(addr, temp);

//LABEL(29f):	/* jsr */
	PUSHWORD(0x2a1);
	JUMP_IMM(0x099);

LABEL(2a1):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x019, a);

//LABEL(2a3):	/* ldx */
	x = 0x000;
	SET_NZ(x);

LABEL(2a5):	/* lda */
	addr = x + 0x337;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2a8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(2aa):	/* jsr */
	PUSHWORD(0x2ac);
	JUMP_IMM(0x099);

LABEL(2ac):	/* cmpa */
	SUB(temp, a, 0x080);

//LABEL(2ae):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x32e);

//LABEL(2b0):	/* lda */
	addr = x + 0x33e;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2b3):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(2b5):	/* jsr */
	PUSHWORD(0x2b7);
	JUMP_IMM(0x099);

LABEL(2b7):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2b9):	/* lda */
	addr = x + 0x368;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2bc):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(2be):	/* lda */
	addr = 0x018;
	a = MCU_RDMEM(0x018);
	SET_NZ(a);

//LABEL(2c0):	/* suba */
	addr = 0x011;
	SUB(a, a, MCU_RDMEM(0x011));

//LABEL(2c2):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2c4):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x2d6);

//LABEL(2c6):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x2da);

//LABEL(2c8):	/* eora */
	EOR(a, a, 0x0ff);
	SET_NZ(a);

//LABEL(2ca):	/* adda */
	ADD(a, a, 0x001);

//LABEL(2cc):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2ce):	/* cmpa */
	SUB(temp, a, 0x027);

//LABEL(2d0):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x2e2);

//LABEL(2d2):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(2d4):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x2e4);

LABEL(2d6):	/* lda */
	a = 0x080;
	SET_NZ(a);

//LABEL(2d8):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x2e4);

LABEL(2da):	/* cmpa */
	SUB(temp, a, 0x027);

//LABEL(2dc):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x2e2);

//LABEL(2de):	/* lda */
	a = 0x002;
	SET_NZ(a);

//LABEL(2e0):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x2e4);

LABEL(2e2):	/* lda */
	a = 0x000;
	SET_NZ(a);

LABEL(2e4):	/* jsr */
	PUSHWORD(0x2e6);
	JUMP_IMM(0x0b2);

LABEL(2e6):	/* lda */
	addr = x + 0x36f;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2e9):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(2eb):	/* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(2ed):	/* jsr */
	PUSHWORD(0x2ef);
	JUMP_IMM(0x0b2);

LABEL(2ef):	/* lda */
	addr = x + 0x345;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2f2):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(2f4):	/* jsr */
	PUSHWORD(0x2f6);
	JUMP_IMM(0x099);

LABEL(2f6):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2f8):	/* lda */
	addr = x + 0x376;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2fb):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(2fd):	/* lda */
	addr = 0x019;
	a = MCU_RDMEM(0x019);
	SET_NZ(a);

//LABEL(2ff):	/* suba */
	addr = 0x011;
	SUB(a, a, MCU_RDMEM(0x011));

//LABEL(301):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(303):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x315);

//LABEL(305):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x319);

//LABEL(307):	/* eora */
	EOR(a, a, 0x0ff);
	SET_NZ(a);

//LABEL(309):	/* adda */
	ADD(a, a, 0x001);

//LABEL(30b):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(30d):	/* cmpa */
	SUB(temp, a, 0x047);

//LABEL(30f):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x321);

//LABEL(311):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(313):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x323);

LABEL(315):	/* lda */
	a = 0x080;
	SET_NZ(a);

//LABEL(317):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x323);

LABEL(319):	/* cmpa */
	SUB(temp, a, 0x047);

//LABEL(31b):	/* bls */
	IF_CC_LS()
	JUMP_IMM(0x321);

//LABEL(31d):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(31f):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x323);

LABEL(321):	/* lda */
	a = 0x000;
	SET_NZ(a);

LABEL(323):	/* jsr */
	PUSHWORD(0x325);
	JUMP_IMM(0x0b2);

LABEL(325):	/* lda */
	addr = x + 0x37d;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(328):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(32a):	/* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(32c):	/* jsr */
	PUSHWORD(0x32e);
	JUMP_IMM(0x0b2);

LABEL(32e):	/* incx */
	INC(x, x);

//LABEL(32f):	/* cpx */
	SUB(temp, x, 0x007);

//LABEL(331):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x336);

//LABEL(333):	/* jmp */
	JUMP_IMM(0x2a5);

LABEL(336):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(38a):	/* jsr */
	PUSHWORD(0x38d);
	JUMP_IMM(0x14a);

LABEL(38d):	/* jsr */
	PUSHWORD(0x390);
	JUMP_IMM(0x1a6);

LABEL(390):	/* jsr */
	PUSHWORD(0x393);
	JUMP_IMM(0x16f);

LABEL(393):	/* jsr */
	PUSHWORD(0x396);
	JUMP_IMM(0x1e3);

LABEL(396):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(398):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(39a):	/* lda */
	a = 0x02e;
	SET_NZ(a);

//LABEL(39c):	/* jsr */
	PUSHWORD(0x39e);
	JUMP_IMM(0x0b2);

LABEL(39e):	/* lda */
	a = 0x085;
	SET_NZ(a);

//LABEL(3a0):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(3a2):	/* lda */
	a = 0x037;
	SET_NZ(a);

//LABEL(3a4):	/* jsr */
	PUSHWORD(0x3a6);
	JUMP_IMM(0x0b2);

LABEL(3a6):	/* jmp */
	JUMP_IMM(0x38a);

#if defined(RAINE_DOS) || defined(RAINE_UNIX)

invalid_pc:
	#ifdef RAINE_DEBUG
		print_debug("M68705: Invalid jump address (0x%x)\n", m68705.pc);
		print_ingame(200, gettext("M68705: Invalid jump address (0x%x)\n"), m68705.pc);
	#endif
	return;
#else
        default:

	#ifdef RAINE_DEBUG
		print_debug("M68705: Invalid jump address (0x%x)\n", m68705.pc);
		print_ingame(200, gettext("M68705: Invalid jump address (0x%x)\n"), m68705.pc);
	#endif
	return;
        break;
      }

      goto LOOP;

#endif
}
