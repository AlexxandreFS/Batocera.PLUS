/* Auto-generated from kiki.asm! Do not modify! */
/* [spindizzy] - hacked, see L0x162 */

#include <stdlib.h>
#include "deftypes.h"
#ifndef SDL
#include "ingame.h"
#endif

extern UINT8 KSystem_MCU_RDMEM(int a);
extern void KSystem_MCU_WRMEM(int a, UINT8 v);
#define MCU_RDMEM(a) KSystem_MCU_RDMEM(a)
#define MCU_WRMEM(a,v) KSystem_MCU_WRMEM(a,v)

#include "m68705.h"
#ifndef SDL
#include "debug.h"
#endif

static int unpacked;

void KikiKaiKai_mcu_reset(void)
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

void KikiKaiKai_mcu(int bih_count)
{
	UINT8 temp;
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
		{ 0x09f, &&L0x09f },
		{ 0x0b4, &&L0x0b4 },
		{ 0x0e2, &&L0x0e2 },
		{ 0x0e4, &&L0x0e4 },
		{ 0x0f0, &&L0x0f0 },
		{ 0x0f6, &&L0x0f6 },
		{ 0x0f8, &&L0x0f8 },
		{ 0x0fe, &&L0x0fe },
		{ 0x100, &&L0x100 },
		{ 0x10c, &&L0x10c },
		{ 0x110, &&L0x110 },
		{ 0x118, &&L0x118 },
		{ 0x11c, &&L0x11c },
		{ 0x122, &&L0x122 },
		{ 0x12a, &&L0x12a },
		{ 0x132, &&L0x132 },
		{ 0x138, &&L0x138 },
		{ 0x13e, &&L0x13e },
		{ 0x144, &&L0x144 },
		{ 0x14a, &&L0x14a },
		{ 0x14c, &&L0x14c },
		{ 0x14f, &&L0x14f },
		{ 0x152, &&L0x152 },
		{ 0x153, &&L0x153 },
		{ 0x164, &&L0x164 },
		{ 0x17c, &&L0x17c },
		{ 0x17e, &&L0x17e },
		{ 0x182, &&L0x182 },
		{ 0x188, &&L0x188 },
		{ 0x18e, &&L0x18e },
		{ 0x19a, &&L0x19a },
		{ 0x1ac, &&L0x1ac },
		{ 0x1b4, &&L0x1b4 },
		{ 0x1c6, &&L0x1c6 },
		{ 0x1d0, &&L0x1d0 },
		{ 0x1d8, &&L0x1d8 },
		{ 0x1db, &&L0x1db },
		{ 0x1e3, &&L0x1e3 },
		{ 0x1f8, &&L0x1f8 },
		{ 0x1fd, &&L0x1fd },
		{ 0x213, &&L0x213 },
		{ 0x223, &&L0x223 },
		{ 0x227, &&L0x227 },
		{ 0x22f, &&L0x22f },
		{ 0x233, &&L0x233 },
		{ 0x24c, &&L0x24c },
		{ 0x254, &&L0x254 },
		{ 0x25a, &&L0x25a },
		{ 0x263, &&L0x263 },
		{ 0x265, &&L0x265 },
		{ 0x267, &&L0x267 },
		{ 0x27c, &&L0x27c },
		{ 0x27e, &&L0x27e },
		{ 0x281, &&L0x281 },
		{ 0x292, &&L0x292 },
		{ 0x2a1, &&L0x2a1 },
		{ 0x2aa, &&L0x2aa },
		{ 0x2b2, &&L0x2b2 },
		{ 0x2bb, &&L0x2bb },
		{ 0x2ca, &&L0x2ca },
		{ 0x2cf, &&L0x2cf },
		{ 0x2e0, &&L0x2e0 },
		{ 0x2e9, &&L0x2e9 },
		{ 0x2f9, &&L0x2f9 },
		{ 0x2ff, &&L0x2ff },
		{ 0x305, &&L0x305 },
		{ 0x309, &&L0x309 },
		{ 0x30f, &&L0x30f },
		{ 0x311, &&L0x311 },
		{ 0x31c, &&L0x31c },
		{ 0x31e, &&L0x31e },
		{ 0, NULL }
	};

	if (!unpacked) { M68705_Unpack(&jump_table[0], &&invalid_pc); unpacked=1; }

/* code starts here */
	JUMP(m68705.pc);

#else

LOOP:
      switch(m68705.pc){

#endif

LABEL(080):	/* lda */
	addr = 0x010;
	a = MCU_RDMEM(0x010);
	SET_NZ(a);

//LABEL(082):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(084):	/* bclr1 */
	BCLR(0x001, 1);

//LABEL(086):	/* bset1 */
	BSET(0x001, 1);

//LABEL(088):	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(08a):	/* bset4 */
	BSET(0x001, 4);

//LABEL(08c):	/* bclr3 */
	BCLR(0x001, 3);

//LABEL(08e):	/* bclr0 */
	BCLR(0x001, 0);

//LABEL(090):	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//LABEL(092):	/* bset3 */
	BSET(0x001, 3);

//LABEL(094):	/* bset0 */
	BSET(0x001, 0);

//LABEL(096):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(098):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(09a):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//LABEL(09c):	/* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(09e):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(09f):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(0a1):	/* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(0a3):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(0a5):	/* bclr1 */
	BCLR(0x001, 1);

//LABEL(0a7):	/* bset1 */
	BSET(0x001, 1);

//LABEL(0a9):	/* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(0ab):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(0ad):	/* bclr4 */
	BCLR(0x001, 4);

//LABEL(0af):	/* bclr3 */
	BCLR(0x001, 3);

//LABEL(0b1):	/* bset3 */
	BSET(0x001, 3);

//LABEL(0b3):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(0b4):	/* sei */
//INIT_PC
	m68705.flag_i = 1;

//LABEL(0b5):	/* rsp */
	sp = 0x7f;

//LABEL(0b6):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(0b8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//LABEL(0ba):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(0bc):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x006, a);

//LABEL(0be):	/* lda */
	a = 0x0df;
	SET_NZ(a);

//LABEL(0c0):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//LABEL(0c2):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(0c4):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x005, a);

//LABEL(0c6):	/* lda */
	a = 0x0df;
	SET_NZ(a);

//LABEL(0c8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//LABEL(0ca):	/* clr */
	addr = 0x01a;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(0cc):	/* clr */
	addr = 0x01b;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(0ce):	/* clr */
	addr = 0x01c;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(0d0):	/* clr */
	addr = 0x01d;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(0d2):	/* lda */
	addr = 0x002;
	a = MCU_RDMEM(0x002);
	SET_NZ(a);

//LABEL(0d4):	/* anda */
	AND(a, a, 0x03f);
	SET_NZ(a);

//LABEL(0d6):	/* eora */
	EOR(a, a, 0x003);
	SET_NZ(a);

//LABEL(0d8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(0da):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(0dc):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(0de):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(0e0):	/* bset2 */
	BSET(0x001, 2);

LABEL(0e2):	/* jsr */
	PUSHWORD(0x0e4);
	JUMP_IMM(0x080);

LABEL(0e4):	/* cmpa */
	SUB(temp, a, 0x000);

//LABEL(0e6):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x0e2);

//LABEL(0e8):	/* lda */
	a = 0x004;
	SET_NZ(a);

//LABEL(0ea):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(0ec):	/* lda */
	a = 0x0fc;
	SET_NZ(a);

//LABEL(0ee):	/* jsr */
	PUSHWORD(0x0f0);
	JUMP_IMM(0x09f);

LABEL(0f0):	/* lda */
	a = 0x00b;
	SET_NZ(a);

//LABEL(0f2):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(0f4):	/* jsr */
	PUSHWORD(0x0f6);
	JUMP_IMM(0x080);

LABEL(0f6):	/* jsr */
	PUSHWORD(0x0f8);
	JUMP_IMM(0x080);

LABEL(0f8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01f, a);

//LABEL(0fa):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(0fc):	/* jsr */
	PUSHWORD(0x0fe);
	JUMP_IMM(0x080);

LABEL(0fe):	/* jsr */
	PUSHWORD(0x100);
	JUMP_IMM(0x080);

LABEL(100):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x020, a);

//LABEL(102):	/* clr */
	addr = 0x010;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(104):	/* lda */
	a = 0x002;
	SET_NZ(a);

//LABEL(106):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(108):	/* bclr2 */
	BCLR(0x001, 2);

//LABEL(10a):	/* jsr */
	PUSHWORD(0x10c);
	JUMP_IMM(0x080);

LABEL(10c):	/* bset2 */
	BSET(0x001, 2);

//LABEL(10e):	/* jsr */
	PUSHWORD(0x110);
	JUMP_IMM(0x09f);

LABEL(110):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(112):	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(114):	/* bclr2 */
	BCLR(0x001, 2);

//LABEL(116):	/* jsr */
	PUSHWORD(0x118);
	JUMP_IMM(0x080);

LABEL(118):	/* bset2 */
	BSET(0x001, 2);

//LABEL(11a):	/* jsr */
	PUSHWORD(0x11c);
	JUMP_IMM(0x09f);

LABEL(11c):	/* lda */
	a = 0x019;
	SET_NZ(a);

//LABEL(11e):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(120):	/* jsr */
	PUSHWORD(0x122);
	JUMP_IMM(0x080);

LABEL(122):	/* lda */
	a = 0x01b;
	SET_NZ(a);

//LABEL(124):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(126):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(128):	/* jsr */
	PUSHWORD(0x12a);
	JUMP_IMM(0x09f);

LABEL(12a):	/* lda */
	a = 0x007;
	SET_NZ(a);

//LABEL(12c):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(12e):	/* lda */
	a = 0x003;
	SET_NZ(a);

//LABEL(130):	/* jsr */
	PUSHWORD(0x132);
	JUMP_IMM(0x09f);

LABEL(132):	/* dec */
	addr = 0x011;
	DEC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(134):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(136):	/* jsr */
	PUSHWORD(0x138);
	JUMP_IMM(0x09f);

LABEL(138):	/* clr */
	addr = 0x011;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(13a):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(13c):	/* jsr */
	PUSHWORD(0x13e);
	JUMP_IMM(0x09f);

LABEL(13e):	/* clr */
	addr = 0x011;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(140):	/* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(142):	/* jsr */
	PUSHWORD(0x144);
	JUMP_IMM(0x09f);

LABEL(144):	/* lda */
	a = 0x00d;
	SET_NZ(a);

//LABEL(146):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(148):	/* jsr */
	PUSHWORD(0x14a);
	JUMP_IMM(0x080);

LABEL(14a):	/* jsr */
	PUSHWORD(0x14c);
	JUMP_IMM(0x080);

LABEL(14c):	/* jsr */
	PUSHWORD(0x14f);
	JUMP_IMM(0x164);

LABEL(14f):	/* jsr */
	PUSHWORD(0x152);
	JUMP_IMM(0x24c);

LABEL(152):	/* cli */
	m68705.flag_i = 0;

LABEL(153):	/* lda */
	addr = 0x01f;
	a = MCU_RDMEM(0x01f);
	SET_NZ(a);

//LABEL(155):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(156):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(157):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(158):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(159):	/* tax */
	x = a;

//LABEL(15a):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(15c):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x016, a);

//LABEL(15e):	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//LABEL(15f):	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//LABEL(160):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x017, x);

//LABEL(162):	/* bra */
   //JUMP_IMM(0x153);
   /* Hack to make it (a) only do the main loop once then return,
    * and (b) call the interrupt code from the main loop instead.
    */
   m68705.pc = 0x14c;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
   return;

LABEL(164):	/* lda */
	a = 0x004;
	SET_NZ(a);

//LABEL(166):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(168):	/* lda */
	addr = 0x002;
	a = MCU_RDMEM(0x002);
	SET_NZ(a);

//LABEL(16a):	/* anda */
	AND(a, a, 0x03f);
	SET_NZ(a);

//LABEL(16c):	/* eora */
	EOR(a, a, 0x003);
	SET_NZ(a);

//LABEL(16e):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(170):	/* lda */
	addr = 0x01a;
	a = MCU_RDMEM(0x01a);
	SET_NZ(a);

//LABEL(172):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x17c);

//LABEL(174):	/* dec */
	addr = 0x01a;
	DEC(temp, MCU_RDMEM(0x01a));
	MCU_WRMEM(addr, temp);

//LABEL(176):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x17c);

//LABEL(178):	/* lda */
	addr = 0x01e;
	a = MCU_RDMEM(0x01e);
	SET_NZ(a);

//LABEL(17a):	/* bra */
	JUMP_IMM(0x17e);

LABEL(17c):	/* lda */
	addr = 0x012;
	a = MCU_RDMEM(0x012);
	SET_NZ(a);

LABEL(17e):	/* bset2 */
	BSET(0x001, 2);

//LABEL(180):	/* jsr */
	PUSHWORD(0x182);
	JUMP_IMM(0x09f);

LABEL(182):	/* lda */
	a = 0x00b;
	SET_NZ(a);

//LABEL(184):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(186):	/* jsr */
	PUSHWORD(0x188);
	JUMP_IMM(0x080);

LABEL(188):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01f, a);

//LABEL(18a):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(18c):	/* jsr */
	PUSHWORD(0x18e);
	JUMP_IMM(0x080);

LABEL(18e):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x020, a);

//LABEL(190):	/* clr */
	addr = 0x010;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(192):	/* lda */
	a = 0x002;
	SET_NZ(a);

//LABEL(194):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(196):	/* bclr2 */
	BCLR(0x001, 2);

//LABEL(198):	/* jsr */
	PUSHWORD(0x19a);
	JUMP_IMM(0x080);

LABEL(19a):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(19b):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(19c):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(19e):	/* tax */
	x = a;

//LABEL(19f):	/* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1a1):	/* anda */
	AND(a, a, 0x0f3);
	SET_NZ(a);

//LABEL(1a3):	/* ora */
	addr = x + 0x248;
	OR(a, a, MCU_RDMEM(addr));
	SET_NZ(a);

//LABEL(1a6):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x018, a);

//LABEL(1a8):	/* bset2 */
	BSET(0x001, 2);

//LABEL(1aa):	/* jsr */
	PUSHWORD(0x1ac);
	JUMP_IMM(0x09f);

LABEL(1ac):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(1ae):	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(1b0):	/* bclr2 */
	BCLR(0x001, 2);

//LABEL(1b2):	/* jsr */
	PUSHWORD(0x1b4);
	JUMP_IMM(0x080);

LABEL(1b4):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(1b5):	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//LABEL(1b6):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(1b8):	/* tax */
	x = a;

//LABEL(1b9):	/* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1bb):	/* anda */
	AND(a, a, 0x0f3);
	SET_NZ(a);

//LABEL(1bd):	/* ora */
	addr = x + 0x248;
	OR(a, a, MCU_RDMEM(addr));
	SET_NZ(a);

//LABEL(1c0):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x019, a);

//LABEL(1c2):	/* bset2 */
	BSET(0x001, 2);

//LABEL(1c4):	/* jsr */
	PUSHWORD(0x1c6);
	JUMP_IMM(0x09f);

LABEL(1c6):	/* lda */
	a = 0x019;
	SET_NZ(a);

//LABEL(1c8):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(1ca):	/* lda */
	a = 0x01b;
	SET_NZ(a);

//LABEL(1cc):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(1ce):	/* jsr */
	PUSHWORD(0x1d0);
	JUMP_IMM(0x080);

LABEL(1d0):	/* ldx */
	addr = 0x019;
	x = MCU_RDMEM(0x019);
	SET_NZ(x);

//LABEL(1d2):	/* cmpa */
	SUB(temp, a, 0x0aa);

//LABEL(1d4):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x1d8);

//LABEL(1d6):	/* ldx */
	addr = 0x018;
	x = MCU_RDMEM(0x018);
	SET_NZ(x);

LABEL(1d8):	/* txa */
	a = x;

//LABEL(1d9):	/* jsr */
	PUSHWORD(0x1db);
	JUMP_IMM(0x09f);

LABEL(1db):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(1dd):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(1df):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(1e1):	/* jsr */
	PUSHWORD(0x1e3);
	JUMP_IMM(0x080);

LABEL(1e3):	/* lda */
	addr = 0x012;
	a = MCU_RDMEM(0x012);
	SET_NZ(a);

//LABEL(1e5):	/* eora */
	addr = 0x014;
	EOR(a, a, MCU_RDMEM(0x014));
	SET_NZ(a);

//LABEL(1e7):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(1e9):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x233);

//LABEL(1eb):	/* anda */
	addr = 0x014;
	AND(a, a, MCU_RDMEM(0x014));
	SET_NZ(a);

//LABEL(1ed):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x233);

//LABEL(1ef):	/* ldx */
	x = 0x00c;
	SET_NZ(x);

//LABEL(1f1):	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x01e, x);

//LABEL(1f3):	/* brclr0 */
	BRCLR(0x014, 0)
	JUMP_IMM(0x1f8);

//LABEL(1f6):	/* inc */
	addr = 0x01c;
	INC(temp, MCU_RDMEM(0x01c));
	MCU_WRMEM(addr, temp);

LABEL(1f8):	/* brclr1 */
	BRCLR(0x014, 1)
	JUMP_IMM(0x1fd);

//LABEL(1fb):	/* inc */
	addr = 0x01d;
	INC(temp, MCU_RDMEM(0x01d));
	MCU_WRMEM(addr, temp);

LABEL(1fd):	/* lda */
	addr = 0x01a;
	a = MCU_RDMEM(0x01a);
	SET_NZ(a);

//LABEL(1ff):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x233);

//LABEL(201):	/* ldx */
	addr = 0x016;
	x = MCU_RDMEM(0x016);
	SET_NZ(x);

//LABEL(203):	/* lda */
	addr = 0x01c;
	a = MCU_RDMEM(0x01c);
	SET_NZ(a);

//LABEL(205):	/* suba */
	addr = x + 0x238;
	SUB(a, a, MCU_RDMEM(addr));

//LABEL(208):	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x213);

//LABEL(20a):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01c, a);

//LABEL(20c):	/* bset5 */
	BSET(0x01e, 5);

//LABEL(20e):	/* lda */
	addr = x + 0x23c;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(211):	/* bra */
	JUMP_IMM(0x223);

LABEL(213):	/* ldx */
	addr = 0x017;
	x = MCU_RDMEM(0x017);
	SET_NZ(x);

//LABEL(215):	/* lda */
	addr = 0x01d;
	a = MCU_RDMEM(0x01d);
	SET_NZ(a);

//LABEL(217):	/* suba */
	addr = x + 0x240;
	SUB(a, a, MCU_RDMEM(addr));

//LABEL(21a):	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x233);

//LABEL(21c):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01d, a);

//LABEL(21e):	/* bset4 */
	BSET(0x01e, 4);

//LABEL(220):	/* lda */
	addr = x + 0x244;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

LABEL(223):	/* adda */
	addr = 0x015;
	ADD(a, a, MCU_RDMEM(0x015));

//LABEL(225):	/* jsr */
	PUSHWORD(0x227);
	JUMP_IMM(0x09f);

LABEL(227):	/* lda */
	a = 0x00a;
	SET_NZ(a);

//LABEL(229):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(22b):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(22d):	/* jsr */
	PUSHWORD(0x22f);
	JUMP_IMM(0x09f);

LABEL(22f):	/* lda */
	a = 0x003;
	SET_NZ(a);

//LABEL(231):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01a, a);

LABEL(233):	/* lda */
	addr = 0x012;
	a = MCU_RDMEM(0x012);
	SET_NZ(a);

//LABEL(235):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(237):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(24c):	/* bset4 */
	BSET(0x001, 4);

//LABEL(24e):	/* lda */
	a = 0x001;
	SET_NZ(a);

//LABEL(250):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(252):	/* jsr */
	PUSHWORD(0x254);
	JUMP_IMM(0x080);

LABEL(254):	/* lda */
	a = 0x008;
	SET_NZ(a);

//LABEL(256):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(258):	/* jsr */
	PUSHWORD(0x25a);
	JUMP_IMM(0x080);

LABEL(25a):	/* lda */
	a = 0x0b0;
	SET_NZ(a);

//LABEL(25c):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(25e):	/* inca */
	INC(a, a);

//LABEL(25f):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(261):	/* ldx */
	x = 0x008;
	SET_NZ(x);

LABEL(263):	/* jsr */
	PUSHWORD(0x265);
	JUMP_IMM(0x080);

LABEL(265):	/* jsr */
	PUSHWORD(0x267);
	JUMP_IMM(0x09f);

LABEL(267):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(269):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(26b):	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(26d):	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(26f):	/* decx */
	DEC(x, x);

//LABEL(270):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x263);

//LABEL(272):	/* lda */
	a = 0x090;
	SET_NZ(a);

//LABEL(274):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(276):	/* lda */
	a = 0x0c0;
	SET_NZ(a);

//LABEL(278):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(27a):	/* ldx */
	x = 0x00a;
	SET_NZ(x);

LABEL(27c):	/* jsr */
	PUSHWORD(0x27e);
	JUMP_IMM(0x080);

LABEL(27e):	/* inca */
	INC(a, a);

//LABEL(27f):	/* jsr */
	PUSHWORD(0x281);
	JUMP_IMM(0x09f);

LABEL(281):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(283):	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(285):	/* decx */
	DEC(x, x);

//LABEL(286):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x27c);

//LABEL(288):	/* lda */
	a = 0x0d0;
	SET_NZ(a);

//LABEL(28a):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(28c):	/* lda */
	a = 0x0d2;
	SET_NZ(a);

//LABEL(28e):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(290):	/* jsr */
	PUSHWORD(0x292);
	JUMP_IMM(0x080);

LABEL(292):	/* cmpa */
	SUB(temp, a, 0x000);

//LABEL(294):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x2b2);

//LABEL(296):	/* cmpa */
	SUB(temp, a, 0x004);

//LABEL(298):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x2b2);

//LABEL(29a):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(29c):	/* tax */
	x = a;

//LABEL(29d):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(29f):	/* jsr */
	PUSHWORD(0x2a1);
	JUMP_IMM(0x080);

LABEL(2a1):	/* cmpa */
	SUB(temp, a, 0x0ff);

//LABEL(2a3):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x2b2);

//LABEL(2a5):	/* lda */
	addr = x + 0x31f;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2a8):	/* jsr */
	PUSHWORD(0x2aa);
	JUMP_IMM(0x09f);

LABEL(2aa):	/* lda */
	a = 0x0d0;
	SET_NZ(a);

//LABEL(2ac):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2ae):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(2b0):	/* jsr */
	PUSHWORD(0x2b2);
	JUMP_IMM(0x09f);

LABEL(2b2):	/* lda */
	a = 0x0e0;
	SET_NZ(a);

//LABEL(2b4):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(2b6):	/* inca */
	INC(a, a);

//LABEL(2b7):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2b9):	/* jsr */
	PUSHWORD(0x2bb);
	JUMP_IMM(0x080);

LABEL(2bb):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x2e0);

//LABEL(2bd):	/* cmpa */
	SUB(temp, a, 0x004);

//LABEL(2bf):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x2e0);

//LABEL(2c1):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(2c3):	/* deca */
	DEC(a, a);

//LABEL(2c4):	/* asla */
	ASL(a, a);
	SET_NZ(a);

//LABEL(2c5):	/* asla */
	ASL(a, a);
	SET_NZ(a);

//LABEL(2c6):	/* asla */
	ASL(a, a);
	SET_NZ(a);

//LABEL(2c7):	/* asla */
	ASL(a, a);
	SET_NZ(a);

//LABEL(2c8):	/* tax */
	x = a;

//LABEL(2c9):	/* incx */
	INC(x, x);

LABEL(2ca):	/* lda */
	addr = x + 0x323;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2cd):	/* jsr */
	PUSHWORD(0x2cf);
	JUMP_IMM(0x09f);

LABEL(2cf):	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(2d1):	/* incx */
	INC(x, x);

//LABEL(2d2):	/* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(2d4):	/* cmpa */
	SUB(temp, a, 0x0f0);

//LABEL(2d6):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x2ca);

//LABEL(2d8):	/* lda */
	a = 0x0e0;
	SET_NZ(a);

//LABEL(2da):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2dc):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(2de):	/* jsr */
	PUSHWORD(0x2e0);
	JUMP_IMM(0x09f);

LABEL(2e0):	/* lda */
	a = 0x0f0;
	SET_NZ(a);

//LABEL(2e2):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(2e4):	/* inca */
	INC(a, a);

//LABEL(2e5):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(2e7):	/* jsr */
	PUSHWORD(0x2e9);
	JUMP_IMM(0x080);

LABEL(2e9):	/* cmpa */
	SUB(temp, a, 0x000);

//LABEL(2eb):	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x2ff);

//LABEL(2ed):	/* cmpa */
	SUB(temp, a, 0x004);

//LABEL(2ef):	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x2ff);

//LABEL(2f1):	/* anda */
	AND(a, a, 0x003);
	SET_NZ(a);

//LABEL(2f3):	/* tax */
	x = a;

//LABEL(2f4):	/* lda */
	addr = x + 0x353;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//LABEL(2f7):	/* jsr */
	PUSHWORD(0x2f9);
	JUMP_IMM(0x09f);

LABEL(2f9):	/* dec */
	addr = 0x011;
	DEC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(2fb):	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(2fd):	/* jsr */
	PUSHWORD(0x2ff);
	JUMP_IMM(0x09f);

LABEL(2ff):	/* lda */
	a = 0x0a0;
	SET_NZ(a);

//LABEL(301):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(303):	/* jsr */
	PUSHWORD(0x305);
	JUMP_IMM(0x080);

LABEL(305):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(307):	/* jsr */
	PUSHWORD(0x309);
	JUMP_IMM(0x080);

LABEL(309):	/* lda */
	a = 0x020;
	SET_NZ(a);

//LABEL(30b):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(30d):	/* ldx */
	x = 0x038;
	SET_NZ(x);

LABEL(30f):	/* jsr */
	PUSHWORD(0x311);
	JUMP_IMM(0x080);

LABEL(311):	/* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(313):	/* decx */
	DEC(x, x);

//LABEL(314):	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x30f);

//LABEL(316):	/* lda */
	a = 0x0a3;
	SET_NZ(a);

//LABEL(318):	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(31a):	/* jsr */
	PUSHWORD(0x31c);
	JUMP_IMM(0x080);

LABEL(31c):	/* jsr */
	PUSHWORD(0x31e);
	JUMP_IMM(0x080);

LABEL(31e):	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

#if defined(RAINE_DOS) || defined(RAINE_UNIX)

invalid_pc:
#ifndef SDL
		print_debug("M68705: Invalid jump address (0x%x)\n", m68705.pc);
		print_ingame(200, gettext("M68705: Invalid jump address (0x%x)\n"), m68705.pc);
#endif
	return;
#else
        default:

	#ifndef SDL
		print_debug("M68705: Invalid jump address (0x%x)\n", m68705.pc);
		print_ingame(200, gettext("M68705: Invalid jump address (0x%x)\n"), m68705.pc);
	#endif
	return;
        break;
      }

      goto LOOP;

#endif
}
