/* Auto-generated from kickrun.asm! Do not modify! */
/* [kayamon] - had to hack this again, see L0x0e8 and L0x236.
 * also see L0x0e0.
 */

#include <stdlib.h>
#include "deftypes.h"
#include "debug.h"
#ifndef SDL
#include "ingame.h"
#endif

UINT8 KSystem_MCU_RDMEM(int a);
void KSystem_MCU_WRMEM(int a, UINT8 v);
#define MCU_RDMEM(a) KSystem_MCU_RDMEM(a)
#define MCU_WRMEM(a,v) KSystem_MCU_WRMEM(a,v)

#include "m68705.h"

static int unpacked;

void KickRun_mcu_reset(void)
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

void KickRun_mcu(int bih_count)
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
		{ 0x0d6, &&L0x0d6 },
		{ 0x0dc, &&L0x0dc },
		{ 0x0e0, &&L0x0e0 },
		{ 0x0e2, &&L0x0e2 },
      { 0x0e7, &&L0x0e7 },
		{ 0x0e8, &&L0x0e8 },
      { 0x0ea, &&L0x0ea },
		{ 0x100, &&L0x100 },
		{ 0x10a, &&L0x10a },
		{ 0x113, &&L0x113 },
		{ 0x115, &&L0x115 },
		{ 0x11d, &&L0x11d },
		{ 0x126, &&L0x126 },
		{ 0x128, &&L0x128 },
		{ 0x12e, &&L0x12e },
		{ 0x136, &&L0x136 },
		{ 0x13c, &&L0x13c },
		{ 0x148, &&L0x148 },
		{ 0x14e, &&L0x14e },
		{ 0x15c, &&L0x15c },
		{ 0x162, &&L0x162 },
		{ 0x16e, &&L0x16e },
		{ 0x175, &&L0x175 },
		{ 0x17c, &&L0x17c },
		{ 0x183, &&L0x183 },
		{ 0x186, &&L0x186 },
		{ 0x194, &&L0x194 },
		{ 0x19c, &&L0x19c },
		{ 0x1ac, &&L0x1ac },
		{ 0x1ae, &&L0x1ae },
		{ 0x1b8, &&L0x1b8 },
		{ 0x1c4, &&L0x1c4 },
		{ 0x1c8, &&L0x1c8 },
		{ 0x1ca, &&L0x1ca },
		{ 0x1d4, &&L0x1d4 },
		{ 0x1e2, &&L0x1e2 },
		{ 0x1e6, &&L0x1e6 },
		{ 0x1f8, &&L0x1f8 },
		{ 0x1fc, &&L0x1fc },
		{ 0x1fe, &&L0x1fe },
		{ 0x206, &&L0x206 },
		{ 0x20e, &&L0x20e },
		{ 0x216, &&L0x216 },
		{ 0x21e, &&L0x21e },
		{ 0x226, &&L0x226 },
		{ 0x22e, &&L0x22e },
		{ 0x236, &&L0x236 },
		{ 0x237, &&L0x237 },
		{ 0x242, &&L0x242 },
		{ 0x247, &&L0x247 },
		{ 0x24c, &&L0x24c },
		{ 0x251, &&L0x251 },
		{ 0x254, &&L0x254 },
		{ 0x25a, &&L0x25a },
		{ 0x264, &&L0x264 },
		{ 0x26e, &&L0x26e },
		{ 0x278, &&L0x278 },
		{ 0x27c, &&L0x27c },
		{ 0, NULL }
	};

	if (!unpacked) { M68705_Unpack(&jump_table[0], &&invalid_pc); unpacked=1; }

/* code starts here */
	JUMP(m68705.pc);
#else

LOOP:
      switch(m68705.pc){

#endif


LABEL(080):  /* lda */
	addr = 0x010;
	a = MCU_RDMEM(0x010);
	SET_NZ(a);

//LABEL(082):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(084):   /* bclr1 */
	BCLR(0x001, 1);

//LABEL(086):   /* bset1 */
	BSET(0x001, 1);

//LABEL(088):   /* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(08a):   /* bset4 */
	BSET(0x001, 4);

//LABEL(08c):   /* bclr3 */
	BCLR(0x001, 3);

//LABEL(08e):   /* bclr0 */
	BCLR(0x001, 0);

//LABEL(090):   /* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//LABEL(092):   /* bset3 */
	BSET(0x001, 3);

//LABEL(094):   /* bset0 */
	BSET(0x001, 0);

//LABEL(096):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(098):   /* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(09a):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//LABEL(09c):   /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(09e):   /* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(09f):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(0a1):   /* lda */
	addr = 0x011;
	a = MCU_RDMEM(0x011);
	SET_NZ(a);

//LABEL(0a3):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(0a5):   /* bclr1 */
	BCLR(0x001, 1);

//LABEL(0a7):   /* bset1 */
	BSET(0x001, 1);

//LABEL(0a9):   /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(0ab):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//LABEL(0ad):   /* bclr4 */
	BCLR(0x001, 4);

//LABEL(0af):   /* bclr3 */
	BCLR(0x001, 3);

//LABEL(0b1):   /* bset3 */
	BSET(0x001, 3);

//LABEL(0b3):   /* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(0b4):  /* sei */
//INIT_PC
	m68705.flag_i = 1;

//LABEL(0b5):   /* rsp */
	sp = 0x7f;

//LABEL(0b6):   /* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(0b8):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//LABEL(0ba):   /* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(0bc):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x006, a);

//LABEL(0be):   /* lda */
	a = 0x0df;
	SET_NZ(a);

//LABEL(0c0):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//LABEL(0c2):   /* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(0c4):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x005, a);

//LABEL(0c6):   /* lda */
	a = 0x0df;
	SET_NZ(a);

//LABEL(0c8):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//LABEL(0ca):   /* clr */
	addr = 0x014;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(0cc):   /* bset2 */
	BSET(0x001, 2);

//LABEL(0ce):   /* lda */
	a = 0x00d;
	SET_NZ(a);

//LABEL(0d0):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(0d2):   /* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(0d4):   /* jsr */
	PUSHWORD(0x0d6);
	JUMP_IMM(0x09f);

LABEL(0d6):  /* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(0d8):   /* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(0da):   /* jsr */
	PUSHWORD(0x0dc);
	JUMP_IMM(0x09f);

LABEL(0dc):  /* lda */
	a = 0x07f;
	SET_NZ(a);

//LABEL(0de):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

LABEL(0e0):  /* jsr */
	PUSHWORD(0x0e2);
	JUMP_IMM(0x080);

LABEL(0e2):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x018, a);

//LABEL(0e4):   /* brclr7 */
   //BRCLR(0x018, 7)
   //JUMP_IMM(0x0e0);
   /* [kayamon] - hacked here to yield itself, otherwise it'd never pass
    the startup handshake */
   BRSET(0x018, 7)
   JUMP_IMM(0x0e7); /* switch to jump on inverse case */
   m68705.pc = 0x0e0;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
   return;

LABEL(0e7):   /* cli */
	m68705.flag_i = 0;

LABEL(0e8):  /* jmp */
   // [kayamon] - fall-through here to interrupt code
   //JUMP_IMM(0x0e8);

LABEL(0ea):   /* bset5 */
	BSET(0x001, 5);

//LABEL(0ec):   /* bclr5 */
	BCLR(0x001, 5);

//LABEL(0ee):   /* lda */
	a = 0x047;
	SET_NZ(a);

//LABEL(0f0):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(0f2):   /* lda */
	addr = 0x002;
	a = MCU_RDMEM(0x002);
	SET_NZ(a);

//LABEL(0f4):   /* anda */
	AND(a, a, 0x03f);
	SET_NZ(a);

//LABEL(0f6):   /* eora */
	EOR(a, a, 0x003);
	SET_NZ(a);

//LABEL(0f8):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(0fa):   /* bset2 */
	BSET(0x001, 2);

//LABEL(0fc):   /* lda */
	addr = 0x012;
	a = MCU_RDMEM(0x012);
	SET_NZ(a);

//LABEL(0fe):   /* jsr */
	PUSHWORD(0x100);
	JUMP_IMM(0x09f);

LABEL(100):  /* clr */
	addr = 0x010;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(102):   /* lda */
	a = 0x00d;
	SET_NZ(a);

//LABEL(104):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(106):   /* bclr2 */
	BCLR(0x001, 2);

//LABEL(108):   /* jsr */
	PUSHWORD(0x10a);
	JUMP_IMM(0x080);

LABEL(10a):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(10c):   /* bset2 */
	BSET(0x001, 2);

//LABEL(10e):   /* lda */
	addr = 0x012;
	a = MCU_RDMEM(0x012);
	SET_NZ(a);

//LABEL(110):   /* jsr */
	PUSHWORD(0x113);
	JUMP_IMM(0x237);

LABEL(113):  /* jsr */
	PUSHWORD(0x115);
	JUMP_IMM(0x09f);

LABEL(115):  /* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(117):   /* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(119):   /* bclr2 */
	BCLR(0x001, 2);

//LABEL(11b):   /* jsr */
	PUSHWORD(0x11d);
	JUMP_IMM(0x080);

LABEL(11d):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x012, a);

//LABEL(11f):   /* bset2 */
	BSET(0x001, 2);

//LABEL(121):   /* lda */
	addr = 0x012;
	a = MCU_RDMEM(0x012);
	SET_NZ(a);

//LABEL(123):   /* jsr */
	PUSHWORD(0x126);
	JUMP_IMM(0x237);

LABEL(126):  /* jsr */
	PUSHWORD(0x128);
	JUMP_IMM(0x09f);

LABEL(128):  /* lda */
	a = 0x06b;
	SET_NZ(a);

//LABEL(12a):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(12c):   /* jsr */
	PUSHWORD(0x12e);
	JUMP_IMM(0x080);

LABEL(12e):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x017, a);

//LABEL(130):   /* lda */
	a = 0x06c;
	SET_NZ(a);

//LABEL(132):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(134):   /* jsr */
	PUSHWORD(0x136);
	JUMP_IMM(0x080);

LABEL(136):  /* eora */
	EOR(a, a, 0x020);
	SET_NZ(a);

//LABEL(138):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x13c);

//LABEL(13a):   /* clr */
	addr = 0x017;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

LABEL(13c):  /* lda */
	addr = 0x017;
	a = MCU_RDMEM(0x017);
	SET_NZ(a);

//LABEL(13e):   /* eora */
	EOR(a, a, 0x0ff);
	SET_NZ(a);

//LABEL(140):   /* beq */
	IF_CC_Z()
	JUMP_IMM(0x148);

//LABEL(142):   /* lda */
	addr = 0x014;
	a = MCU_RDMEM(0x014);
	SET_NZ(a);

//LABEL(144):   /* beq */
	IF_CC_Z()
	JUMP_IMM(0x148);

//LABEL(146):   /* dec */
	addr = 0x014;
	DEC(temp, MCU_RDMEM(0x014));
	MCU_WRMEM(addr, temp);

LABEL(148):  /* lda */
	a = 0x06d;
	SET_NZ(a);

//LABEL(14a):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(14c):   /* jsr */
	PUSHWORD(0x14e);
	JUMP_IMM(0x080);

LABEL(14e):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x013, a);

//LABEL(150):   /* brset6 */
	BRSET(0x013, 6)
	JUMP_IMM(0x15c);

//LABEL(153):   /* brclr7 */
	BRCLR(0x013, 7)
	JUMP_IMM(0x15c);

//LABEL(156):   /* lda */
	addr = 0x014;
	a = MCU_RDMEM(0x014);
	SET_NZ(a);

//LABEL(158):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x15c);

//LABEL(15a):   /* bra */
	JUMP_IMM(0x186);

LABEL(15c):  /* lda */
	a = 0x068;
	SET_NZ(a);

//LABEL(15e):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x00a, a);

//LABEL(160):   /* jsr */
	PUSHWORD(0x162);
	JUMP_IMM(0x080);

LABEL(162):  /* eora */
	EOR(a, a, 0x019);
	SET_NZ(a);

//LABEL(164):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x183);

//LABEL(166):   /* lda */
	a = 0x079;
	SET_NZ(a);

//LABEL(168):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(16a):   /* lda */
	a = 0x060;
	SET_NZ(a);

//LABEL(16c):   /* jsr */
	PUSHWORD(0x16e);
	JUMP_IMM(0x09f);

LABEL(16e):  /* lda */
	a = 0x068;
	SET_NZ(a);

//LABEL(170):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(172):   /* clra */
	a = 0;
	SET_NZ(a);

//LABEL(173):   /* jsr */
	PUSHWORD(0x175);
	JUMP_IMM(0x09f);

LABEL(175):  /* lda */
	a = 0x06b;
	SET_NZ(a);

//LABEL(177):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(179):   /* clra */
	a = 0;
	SET_NZ(a);

//LABEL(17a):   /* jsr */
	PUSHWORD(0x17c);
	JUMP_IMM(0x09f);

LABEL(17c):  /* lda */
	a = 0x076;
	SET_NZ(a);

//LABEL(17e):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(180):   /* clra */
	a = 0;
	SET_NZ(a);

//LABEL(181):   /* jsr */
	PUSHWORD(0x183);
	JUMP_IMM(0x09f);

LABEL(183):  /* jmp */
	JUMP_IMM(0x206);

LABEL(186):  /* lda */
	a = 0x0ff;
	SET_NZ(a);

//LABEL(188):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x016, a);

//LABEL(18a):   /* lda */
	a = 0x00b;
	SET_NZ(a);

//LABEL(18c):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(18e):   /* brset5 */
	BRSET(0x013, 5)
	JUMP_IMM(0x194);

//LABEL(191):   /* jsr */
	PUSHWORD(0x194);
	JUMP_IMM(0x254);

LABEL(194):  /* lda */
	a = 0x043;
	SET_NZ(a);

//LABEL(196):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(198):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(19a):   /* jsr */
	PUSHWORD(0x19c);
	JUMP_IMM(0x080);

LABEL(19c):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(19e):   /* cmpa */
	SUB(temp, a, 0x001);

//LABEL(1a0):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x1ae);

//LABEL(1a2):   /* lda */
	a = 0x005;
	SET_NZ(a);

//LABEL(1a4):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(1a6):   /* dec */
	addr = 0x011;
	DEC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(1a8):   /* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(1aa):   /* jsr */
	PUSHWORD(0x1ac);
	JUMP_IMM(0x09f);

LABEL(1ac):  /* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

LABEL(1ae):  /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1b0):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x1b8);

//LABEL(1b2):   /* lda */
	a = 0x060;
	SET_NZ(a);

//LABEL(1b4):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(1b6):   /* clr */
	addr = 0x016;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

LABEL(1b8):  /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1ba):   /* anda */
	AND(a, a, 0x00f);
	SET_NZ(a);

//LABEL(1bc):   /* beq */
	IF_CC_Z()
	JUMP_IMM(0x1c4);

//LABEL(1be):   /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1c0):   /* suba */
	SUB(a, a, 0x005);

//LABEL(1c2):   /* bra */
	JUMP_IMM(0x1c8);

LABEL(1c4):  /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1c6):   /* suba */
	SUB(a, a, 0x00b);

LABEL(1c8):  /* jsr */
	PUSHWORD(0x1ca);
	JUMP_IMM(0x09f);

LABEL(1ca):  /* lda */
	addr = 0x016;
	a = MCU_RDMEM(0x016);
	SET_NZ(a);

//LABEL(1cc):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x1fc);

//LABEL(1ce):   /* dec */
	addr = 0x010;
	DEC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(1d0):   /* dec */
	addr = 0x011;
	DEC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

//LABEL(1d2):   /* jsr */
	PUSHWORD(0x1d4);
	JUMP_IMM(0x080);

LABEL(1d4):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(1d6):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x1e6);

//LABEL(1d8):   /* clr */
	addr = 0x014;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//LABEL(1da):   /* lda */
	a = 0x043;
	SET_NZ(a);

//LABEL(1dc):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(1de):   /* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(1e0):   /* jsr */
	PUSHWORD(0x1e2);
	JUMP_IMM(0x09f);

LABEL(1e2):  /* bset6 */
	BSET(0x013, 6);

//LABEL(1e4):   /* bra */
	JUMP_IMM(0x1fe);

LABEL(1e6):  /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1e8):   /* suba */
	SUB(a, a, 0x001);

//LABEL(1ea):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

//LABEL(1ec):   /* anda */
	AND(a, a, 0x00f);
	SET_NZ(a);

//LABEL(1ee):   /* adda */
	ADD(a, a, 0x0f6);

//LABEL(1f0):   /* bcc */
	IF_CC_NC()
	JUMP_IMM(0x1f8);

//LABEL(1f2):   /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1f4):   /* suba */
	SUB(a, a, 0x006);

//LABEL(1f6):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x015, a);

LABEL(1f8):  /* lda */
	addr = 0x015;
	a = MCU_RDMEM(0x015);
	SET_NZ(a);

//LABEL(1fa):   /* jsr */
	PUSHWORD(0x1fc);
	JUMP_IMM(0x09f);

LABEL(1fc):  /* bclr7 */
	BCLR(0x013, 7);

LABEL(1fe):  /* lda */
	a = 0x06d;
	SET_NZ(a);

//LABEL(200):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(202):   /* lda */
	addr = 0x013;
	a = MCU_RDMEM(0x013);
	SET_NZ(a);

//LABEL(204):   /* jsr */
	PUSHWORD(0x206);
	JUMP_IMM(0x09f);

LABEL(206):  /* lda */
	a = 0x06b;
	SET_NZ(a);

//LABEL(208):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(20a):   /* lda */
	addr = 0x017;
	a = MCU_RDMEM(0x017);
	SET_NZ(a);

//LABEL(20c):   /* jsr */
	PUSHWORD(0x20e);
	JUMP_IMM(0x09f);

LABEL(20e):  /* lda */
	a = 0x056;
	SET_NZ(a);

//LABEL(210):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(212):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x011, a);

//LABEL(214):   /* jsr */
	PUSHWORD(0x216);
	JUMP_IMM(0x080);

LABEL(216):  /* eora */
	EOR(a, a, 0x0a7);
	SET_NZ(a);

//LABEL(218):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x236);

//LABEL(21a):   /* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(21c):   /* jsr */
	PUSHWORD(0x21e);
	JUMP_IMM(0x080);

LABEL(21e):  /* eora */
	EOR(a, a, 0x000);
	SET_NZ(a);

//LABEL(220):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x236);

//LABEL(222):   /* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(224):   /* jsr */
	PUSHWORD(0x226);
	JUMP_IMM(0x080);

LABEL(226):  /* eora */
	EOR(a, a, 0x083);
	SET_NZ(a);

//LABEL(228):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x236);

//LABEL(22a):   /* inc */
	addr = 0x010;
	INC(temp, MCU_RDMEM(0x010));
	MCU_WRMEM(addr, temp);

//LABEL(22c):   /* jsr */
	PUSHWORD(0x22e);
	JUMP_IMM(0x080);

LABEL(22e):  /* eora */
	EOR(a, a, 0x057);
	SET_NZ(a);

//LABEL(230):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x236);

//LABEL(232):   /* lda */
	a = 0x000;
	SET_NZ(a);

//LABEL(234):   /* jsr */
	PUSHWORD(0x236);
	JUMP_IMM(0x09f);

LABEL(236):  /* rti */
//invalid instruction!
   //goto invalid_pc;
   /* [kayamon] - hacked here to quit and return to the main loop */
   m68705.pc = 0x0ea;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
   return;

LABEL(237):  /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x018, a);

//LABEL(239):   /* ora */
	OR(a, a, 0x00f);
	SET_NZ(a);

//LABEL(23b):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x019, a);

//LABEL(23d):   /* brset0 */
	BRSET(0x018, 0)
	JUMP_IMM(0x242);

//LABEL(240):   /* bclr2 */
	BCLR(0x019, 2);

LABEL(242):  /* brset1 */
	BRSET(0x018, 1)
	JUMP_IMM(0x247);

//LABEL(245):   /* bclr3 */
	BCLR(0x019, 3);

LABEL(247):  /* brset2 */
	BRSET(0x018, 2)
	JUMP_IMM(0x24c);

//LABEL(24a):   /* bclr1 */
	BCLR(0x019, 1);

LABEL(24c):  /* brset3 */
	BRSET(0x018, 3)
	JUMP_IMM(0x251);

//LABEL(24f):   /* bclr0 */
	BCLR(0x019, 0);

LABEL(251):  /* lda */
	addr = 0x019;
	a = MCU_RDMEM(0x019);
	SET_NZ(a);

//LABEL(253):   /* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

LABEL(254):  /* lda */
	a = 0x007;
	SET_NZ(a);

//LABEL(256):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//LABEL(258):   /* jsr */
	PUSHWORD(0x25a);
	JUMP_IMM(0x080);

LABEL(25a):  /* anda */
	AND(a, a, 0x00c);
	SET_NZ(a);

//LABEL(25c):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x264);

//LABEL(25e):   /* lda */
	a = 0x009;
	SET_NZ(a);

//LABEL(260):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(262):   /* bra */
	JUMP_IMM(0x27c);

LABEL(264):  /* cmpa */
	SUB(temp, a, 0x00c);

//LABEL(266):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x26e);

//LABEL(268):   /* lda */
	a = 0x006;
	SET_NZ(a);

//LABEL(26a):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(26c):   /* bra */
	JUMP_IMM(0x27c);

LABEL(26e):  /* cmpa */
	SUB(temp, a, 0x008);

//LABEL(270):   /* bne */
	IF_CC_NZ()
	JUMP_IMM(0x278);

//LABEL(272):   /* lda */
	a = 0x00f;
	SET_NZ(a);

//LABEL(274):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

//LABEL(276):   /* bra */
	JUMP_IMM(0x27c);

LABEL(278):  /* lda */
	a = 0x00c;
	SET_NZ(a);

//LABEL(27a):   /* sta */
	SET_NZ(a);
	MCU_WRMEM(0x014, a);

LABEL(27c):  /* rts */
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
