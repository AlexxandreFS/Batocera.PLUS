/* Auto-generated from a45.asm! Do not modify! */

#include "raine.h"
#include "debug.h"
#include "ingame.h"
#include "mz80help.h"

UINT8 flstory_MCU_RDMEM(int a);
void flstory_MCU_WRMEM(int a, UINT8 v);
#define MCU_RDMEM(a) flstory_MCU_RDMEM(a)
#define MCU_WRMEM(a,v) flstory_MCU_WRMEM(a,v)

#include "m68705.h"

static unsigned char from_main,from_mcu;
static int mcu_sent = 0,main_sent = 0;
static UINT8 *ram_mcu;
void flstory_mcu(int bih_count);

static void m68705int() {
    M68705 backup = m68705;
    m68705.pc = MCU_RDMEM(0x7fb) | (MCU_RDMEM(0x7fa)<<8);
    flstory_mcu(1);
    m68705 = backup;
}

/***************************************************************************

 Fairy Land Story 68705 protection interface

 The following is ENTIRELY GUESSWORK!!!

***************************************************************************/

static unsigned char portA_in,portA_out,ddrA;

static UINT8 flstory_68705_portA_r(UINT32 offset)
{
//if (errorlog) fprintf(errorlog,"%04x: 68705 port A read %02x\n",cpu_get_pc(),portA_in);
	return (portA_out & ddrA) | (portA_in & ~ddrA);
}

static void flstory_68705_portA_w(UINT32 offset,UINT8 data)
{
//if (errorlog) fprintf(errorlog,"%04x: 68705 port A write %02x\n",cpu_get_pc(),data);
	portA_out = data;
}

static void flstory_68705_ddrA_w(UINT32 offset,UINT8 data)
{
	ddrA = data;
}

/*
 *  Port B connections:
 *
 *  all bits are logical 1 when read (+5V pullup)
 *
 *  1   W  when 1->0, enables latch which brings the command from main CPU (read from port A)
 *  2   W  when 0->1, copies port A to the latch for the main CPU
 */

static unsigned char portB_in,portB_out,ddrB;

UINT8 flstory_68705_portB_r(UINT32 offset)
{
	return (portB_out & ddrB) | (portB_in & ~ddrB);
}

static void flstory_68705_portB_w(UINT32 offset,UINT8 data)
{
//if (errorlog) fprintf(errorlog,"%04x: 68705 port B write %02x\n",cpu_get_pc(),data);

	if ((ddrB & 0x02) && (~data & 0x02) && (portB_out & 0x02))
	{
		portA_in = from_main;
		// if (main_sent) cpu_set_irq_line(2,0,CLEAR_LINE);
		main_sent = 0;
// if (errorlog) fprintf(errorlog,"read command %02x from main cpu\n",portA_in);
	}
	if ((ddrB & 0x04) && (data & 0x04) && (~portB_out & 0x04))
	{
// if (errorlog) fprintf(errorlog,"send command %02x to main cpu\n",portA_out);
		from_mcu = portA_out;
		mcu_sent = 1;
	}

	portB_out = data;
}

static void flstory_68705_ddrB_w(UINT32 offset,UINT8 data)
{
	ddrB = data;
}


static unsigned char portC_in,portC_out,ddrC;

UINT8 flstory_68705_portC_r(UINT32 offset)
{
	portC_in = 0;
	if (main_sent) portC_in |= 0x01;
	if (!mcu_sent) portC_in |= 0x02;
// if (errorlog) fprintf(errorlog,"%04x: 68705 port C read %02x\n",cpu_get_pc(),portC_in);
	return (portC_out & ddrC) | (portC_in & ~ddrC);
}

static void flstory_68705_portC_w(UINT32 offset,UINT8 data)
{
// if (errorlog) fprintf(errorlog,"%04x: 68705 port C write %02x\n",cpu_get_pc(),data);
	portC_out = data;
}

static void flstory_68705_ddrC_w(UINT32 offset,UINT8 data)
{
	ddrC = data;
}

extern UINT8 *fl_mcu_started;

void flstory_mcu_w(UINT32 offset,UINT8 data)
{
	from_main = data;
	main_sent = 1;
	// printf("*** mcu_w from %x data %x\n",z80pc,data);
	if (*fl_mcu_started)
	    m68705int();
	else
	    *fl_mcu_started = 1;
	// cpu_set_irq_line(2,0,ASSERT_LINE);
}

extern int goto_debuger;

UINT8 flstory_mcu_r(UINT32 offset)
{
	mcu_sent = 0;
	// printf("flstory_mcu_r : %x from %x\n",from_mcu,z80pc);
	*fl_mcu_started = 1;
	// goto_debuger = 1;
	// mz80ReleaseTimeslice();
	return from_mcu;
}

UINT8 flstory_mcu_status_r(UINT32 offset)
{
	int res = 0;

	/* bit 0 = when 1, mcu is ready to receive data from main cpu */
	/* bit 1 = when 1, mcu has sent data to the main cpu */
//if (errorlog) fprintf (errorlog, "%04x: mcu_status_r\n",cpu_get_pc());
	if (!main_sent) res |= 0x01;
	if (mcu_sent) res |= 0x02;

	return res;
}

UINT8 flstory_MCU_RDMEM(int offset) {
    offset &= 0x7ff;
    if (offset == 0) return flstory_68705_portA_r(offset);
    else if (offset == 1) return flstory_68705_portB_r(offset);
    else if (offset == 2) return flstory_68705_portC_r(offset);
    else if (offset < 0x800) return ram_mcu[offset];
    return 0xff;
}

void flstory_MCU_WRMEM(int offset, UINT8 data) {
    if (offset == 0) flstory_68705_portA_w(offset,data);
    else if (offset == 1) flstory_68705_portB_w(offset,data);
    else if (offset == 2) flstory_68705_portC_w(offset,data);

    else if (offset == 4) flstory_68705_ddrA_w(offset,data);
    else if (offset == 5) flstory_68705_ddrB_w(offset,data);
    else if (offset == 6) flstory_68705_ddrC_w(offset,data);

    else if (offset < 0x80) ram_mcu[offset] = data;
    else {
	printf("flstory_mcu_wrmem: %x,%x\n",offset,data);
    }
}

static int unpacked;

void flstory_mcu_reset(UINT8 *ram)
{
    ram_mcu = ram;
    m68705.pc = MCU_RDMEM(0x7ff) | (MCU_RDMEM(0x7fe) << 8);
    m68705.sp = 0x7f;
    m68705.a = m68705.x = 0x00;
    m68705.flag_i = 0;
    m68705.flag_n = m68705.flag_h = m68705.flag_z = m68705.flag_c = 0;
    unpacked = 0;
}

void flstory_mcu(int bih_count)
{
	UINT8 temp, dummy;
	UINT16 addr;
	UINT8 x = m68705.x;
	UINT8 a = m68705.a;
	UINT16 sp = m68705.sp;
	UINT8 flag_c = m68705.flag_c;
	UINT8 flag_h = m68705.flag_h;
	UINT8 flag_n = m68705.flag_n;
	UINT8 flag_z = m68705.flag_z;

	static const M68705_JumpTable jump_table[] = {
		{ 0x09f, &&L0x09f },
		{ 0x0a2, &&L0x0a2 },
		{ 0x0a5, &&L0x0a5 },
		{ 0x0a8, &&L0x0a8 },
		{ 0x0ab, &&L0x0ab },
		{ 0x0b7, &&L0x0b7 },
		{ 0x0bd, &&L0x0bd },
		{ 0x0c0, &&L0x0c0 },
		{ 0x0c3, &&L0x0c3 },
		{ 0x0c6, &&L0x0c6 },
		{ 0x0c9, &&L0x0c9 },
		{ 0x0cc, &&L0x0cc },
		{ 0x0d5, &&L0x0d5 },
		{ 0x0e3, &&L0x0e3 },
		{ 0x0e4, &&L0x0e4 },
		{ 0x0ea, &&L0x0ea },
		{ 0x0ed, &&L0x0ed },
		{ 0x100, &&L0x100 },
		{ 0x109, &&L0x109 },
		{ 0x115, &&L0x115 },
		{ 0x116, &&L0x116 },
		{ 0x120, &&L0x120 },
		{ 0x12f, &&L0x12f },
		{ 0x143, &&L0x143 },
		{ 0x146, &&L0x146 },
		{ 0x148, &&L0x148 },
		{ 0x155, &&L0x155 },
		{ 0x159, &&L0x159 },
		{ 0x15f, &&L0x15f },
		{ 0x161, &&L0x161 },
		{ 0x16d, &&L0x16d },
		{ 0x17e, &&L0x17e },
		{ 0x184, &&L0x184 },
		{ 0x195, &&L0x195 },
		{ 0x19b, &&L0x19b },
		{ 0x1b3, &&L0x1b3 },
		{ 0x1c2, &&L0x1c2 },
		{ 0x1c4, &&L0x1c4 },
		{ 0x1d9, &&L0x1d9 },
		{ 0x1e1, &&L0x1e1 },
		{ 0x1ea, &&L0x1ea },
		{ 0x1f3, &&L0x1f3 },
		{ 0x1fd, &&L0x1fd },
		{ 0x205, &&L0x205 },
		{ 0x35d, &&L0x35d },
		{ 0x360, &&L0x360 },
		{ 0x367, &&L0x367 },
		{ 0x36a, &&L0x36a },
		{ 0x36e, &&L0x36e },
		{ 0x371, &&L0x371 },
		{ 0x376, &&L0x376 },
		{ 0x37f, &&L0x37f },
		{ 0x386, &&L0x386 },
		{ 0x38e, &&L0x38e },
		{ 0x397, &&L0x397 },
		{ 0x39d, &&L0x39d },
		{ 0x3a0, &&L0x3a0 },
		{ 0x3af, &&L0x3af },
		{ 0x3b7, &&L0x3b7 },
		{ 0x3bf, &&L0x3bf },
		{ 0x3c7, &&L0x3c7 },
		{ 0x3d0, &&L0x3d0 },
		{ 0x3d6, &&L0x3d6 },
		{ 0x3de, &&L0x3de },
		{ 0x3e5, &&L0x3e5 },
		{ 0x3e8, &&L0x3e8 },
		{ 0x3f0, &&L0x3f0 },
		{ 0x3f4, &&L0x3f4 },
		{ 0x3f8, &&L0x3f8 },
		{ 0x40a, &&L0x40a },
		{ 0x40e, &&L0x40e },
		{ 0x420, &&L0x420 },
		{ 0x425, &&L0x425 },
		{ 0x429, &&L0x429 },
		{ 0x42c, &&L0x42c },
		{ 0x430, &&L0x430 },
		{ 0x433, &&L0x433 },
		{ 0x435, &&L0x435 },
		{ 0x43b, &&L0x43b },
		{ 0x444, &&L0x444 },
		{ 0x44e, &&L0x44e },
		{ 0x45a, &&L0x45a },
		{ 0x45d, &&L0x45d },
		{ 0x463, &&L0x463 },
		{ 0x46c, &&L0x46c },
		{ 0x472, &&L0x472 },
		{ 0x478, &&L0x478 },
		{ 0x482, &&L0x482 },
		{ 0x499, &&L0x499 },
		{ 0x4a0, &&L0x4a0 },
		{ 0x4af, &&L0x4af },
		{ 0x4b1, &&L0x4b1 },
		{ 0x4b8, &&L0x4b8 },
		{ 0x4c0, &&L0x4c0 },
		{ 0x4c3, &&L0x4c3 },
		{ 0x4cc, &&L0x4cc },
		{ 0x4d7, &&L0x4d7 },
		{ 0x4e1, &&L0x4e1 },
		{ 0x4ef, &&L0x4ef },
		{ 0x4fc, &&L0x4fc },
		{ 0x4fe, &&L0x4fe },
		{ 0x503, &&L0x503 },
		{ 0x512, &&L0x512 },
		{ 0x524, &&L0x524 },
		{ 0x530, &&L0x530 },
		{ 0x54b, &&L0x54b },
		{ 0x550, &&L0x550 },
		{ 0x570, &&L0x570 },
		{ 0x575, &&L0x575 },
		{ 0x577, &&L0x577 },
		{ 0x57d, &&L0x57d },
		{ 0x593, &&L0x593 },
		{ 0x595, &&L0x595 },
		{ 0x596, &&L0x596 },
		{ 0x5a8, &&L0x5a8 },
		{ 0x5b0, &&L0x5b0 },
		{ 0x5c8, &&L0x5c8 },
		{ 0x5e1, &&L0x5e1 },
		{ 0x5eb, &&L0x5eb },
		{ 0x5f5, &&L0x5f5 },
		{ 0x5f6, &&L0x5f6 },
		{ 0x5ff, &&L0x5ff },
		{ 0x601, &&L0x601 },
		{ 0x603, &&L0x603 },
		{ 0x607, &&L0x607 },
		{ 0x60c, &&L0x60c },
		{ 0x615, &&L0x615 },
		{ 0x617, &&L0x617 },
		{ 0x618, &&L0x618 },
		{ 0x61a, &&L0x61a },
		{ 0x633, &&L0x633 },
		{ 0x638, &&L0x638 },
		{ 0x63e, &&L0x63e },
		{ 0x656, &&L0x656 },
		{ 0x65e, &&L0x65e },
		{ 0x66e, &&L0x66e },
		{ 0x66f, &&L0x66f },
		{ 0x679, &&L0x679 },
		{ 0x686, &&L0x686 },
		{ 0x696, &&L0x696 },
		{ 0x699, &&L0x699 },
		{ 0x69c, &&L0x69c },
		{ 0x6a3, &&L0x6a3 },
		{ 0x6a5, &&L0x6a5 },
		{ 0x6aa, &&L0x6aa },
		{ 0x6ad, &&L0x6ad },
		{ 0x6af, &&L0x6af },
		{ 0x6b3, &&L0x6b3 },
		{ 0x6b8, &&L0x6b8 },
		{ 0x6bd, &&L0x6bd },
		{ 0x6bf, &&L0x6bf },
		{ 0x6c1, &&L0x6c1 },
		{ 0x6c5, &&L0x6c5 },
		{ 0x6d1, &&L0x6d1 },
		{ 0x6d3, &&L0x6d3 },
		{ 0x6d5, &&L0x6d5 },
		{ 0x6de, &&L0x6de },
		{ 0x6e4, &&L0x6e4 },
		{ 0x6ee, &&L0x6ee },
		{ 0x6f2, &&L0x6f2 },
		{ 0x6fa, &&L0x6fa },
		{ 0x6fc, &&L0x6fc },
		{ 0x704, &&L0x704 },
		{ 0x70b, &&L0x70b },
		{ 0x70d, &&L0x70d },
		{ 0x70f, &&L0x70f },
		{ 0x720, &&L0x720 },
		{ 0x722, &&L0x722 },
		{ 0x726, &&L0x726 },
		{ 0x728, &&L0x728 },
		{ 0x732, &&L0x732 },
		{ 0x73b, &&L0x73b },
		{ 0x73e, &&L0x73e },
		{ 0x749, &&L0x749 },
		{ 0, NULL }
	};

	if (!unpacked) { M68705_Unpack(&jump_table[0], &&invalid_pc); unpacked=1; }

/* code starts here */
	JUMP(m68705.pc);

//L0x080:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x081:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x082:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x083:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x084:	/* rolx */
	ROL(x, x);
	SET_NZ(x);

//L0x085:	/* brclr6 */
	BRCLR(0x0ba, 6)
	goto invalid_pc;

//L0x088:	/* brclr1 */
	BRCLR(0x080, 1)
	JUMP_IMM(0x0e4);

//L0x08b:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x08c:	/* sei */
	m68705.flag_i = 1;

//L0x08d:	/* rolx */
	ROL(x, x);
	SET_NZ(x);

//L0x08e:	/* brset1 */
	BRSET(0x080, 1)
	JUMP_IMM(0x0ea);

//L0x091:	/* brclr6 */
	BRCLR(0x03b, 6)
	JUMP_IMM(0x0ed);

//L0x094:	/* brclr0 */
	BRCLR(0x080, 0)
	goto invalid_pc;

//L0x097:	/* ldx */
	addr = 0x0c2;
	x = MCU_RDMEM(0x0c2);
	SET_NZ(x);

//L0x099:	/* bclr4 */
	BCLR(0x000, 4);

//L0x09b:	/* rti */
//invalid instruction!
	goto invalid_pc;

//L0x09c:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x09f);

L0x09f:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x0a2);

L0x0a2:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x0a5);

L0x0a5:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x0a8);

L0x0a8:	/* brclr0 */
	BRCLR(0x000, 0)
	JUMP_IMM(0x0ab);

L0x0ab:	/* brclr0 */
	BRCLR(0x000, 0)
	goto invalid_pc;

//L0x0ae:	/* brset0 */
	BRSET(0x001, 0)
	goto invalid_pc;

//L0x0b1:	/* brclr0 */
	BRCLR(0x000, 0)
	goto invalid_pc;

//L0x0b4:	/* brclr0 */
	BRCLR(0x001, 0)
	JUMP_IMM(0x0b7);

L0x0b7:	/* brclr0 */
	BRCLR(0x001, 0)
	goto invalid_pc;

//L0x0ba:	/* brset0 */
	BRSET(0x001, 0)
	JUMP_IMM(0x0bd);

L0x0bd:	/* brclr0 */
	BRCLR(0x000, 0)
	JUMP_IMM(0x0c0);

L0x0c0:	/* brclr0 */
	BRCLR(0x000, 0)
	JUMP_IMM(0x0c3);

L0x0c3:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x0c6);

L0x0c6:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x0c9);

L0x0c9:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x0cc);

L0x0cc:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x0cf:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x0d2:	/* brset0 */
	BRSET(0x0ff, 0)
	JUMP_IMM(0x0d5);

L0x0d5:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0d6:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0d7:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0d8:	/* brset0 */
	BRSET(0x0ff, 0)
	goto invalid_pc;

//L0x0db:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0dc:	/* brset0 */
	BRSET(0x0ff, 0)
	goto invalid_pc;

//L0x0df:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0e0:	/* brset0 */
	BRSET(0x0ff, 0)
	JUMP_IMM(0x0e3);

L0x0e3:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

L0x0e4:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x0e7:	/* rti */
//invalid instruction!
	goto invalid_pc;

//L0x0e8:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0e9:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

L0x0ea:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0eb:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0ec:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

L0x0ed:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0ee:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0ef:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f0:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f1:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f2:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f3:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f4:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f5:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f6:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f7:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f8:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0f9:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0fa:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0fb:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0fc:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0fd:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0fe:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x0ff:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

L0x100:	/* ldx */
	x = 0x030;
	SET_NZ(x);

//L0x102:	/* lda */
	a = 0x008;
	SET_NZ(a);

//L0x104:	/* sta */
	addr = x + 0x002;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x107:	/* clra */
	a = 0;
	SET_NZ(a);

//L0x108:	/* clc */
	flag_c = 0;

L0x109:	/* rol */
	addr = x + 0x000;
	ROL(temp, MCU_RDMEM(addr));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x10b:	/* rola */
	ROL(a, a);
	SET_NZ(a);

//L0x10c:	/* cmpa */
	SUB(temp, a, 0x007);

//L0x10e:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x115);

//L0x110:	/* suba */
	SUB(a, a, 0x007);

//L0x112:	/* sec */
	flag_c = 1;

//L0x113:	/* bra */
	JUMP_IMM(0x116);

L0x115:	/* clc */
	flag_c = 0;

L0x116:	/* dec */
	addr = x + 0x002;
	DEC(temp, MCU_RDMEM(addr));
	MCU_WRMEM(addr, temp);

//L0x118:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x109);

//L0x11a:	/* rol */
	addr = x + 0x000;
	ROL(temp, MCU_RDMEM(addr));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x11c:	/* sta */
	addr = x + 0x001;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x11f:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x120:	/* lda */
	addr = 0x030;
	a = MCU_RDMEM(0x030);
	SET_NZ(a);

//L0x123:	/* adda */
	ADD(a, a, 0x080);

//L0x125:	/* tax */
	x = a;

//L0x126:	/* lda */
	addr = x;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x127:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x031, a);

//L0x12a:	/* clra */
	a = 0;
	SET_NZ(a);

//L0x12b:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x033, a);

//L0x12e:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x12f:	/* ldx */
	addr = 0x031;
	x = MCU_RDMEM(0x031);
	SET_NZ(x);

//L0x132:	/* tst */
	addr = 0x033;
	SET_NZ(MCU_RDMEM(0x033));

//L0x134:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x148);

//L0x136:	/* lda */
	addr = x;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x137:	/* cmpa */
	SUB(temp, a, 0x080);

//L0x139:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x143);

//L0x13b:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x032, a);

//L0x13e:	/* incx */
	INC(x, x);

//L0x13f:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x031, x);

//L0x142:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x143:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x033, a);

L0x146:	/* ldx */
	x = 0x09c;
	SET_NZ(x);

L0x148:	/* lda */
	addr = x;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x149:	/* cmpa */
	SUB(temp, a, 0x080);

//L0x14b:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x146);

//L0x14d:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x032, a);

//L0x150:	/* incx */
	INC(x, x);

//L0x151:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x031, x);

//L0x154:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x155:	/* ldx */
	x = 0x039;
	SET_NZ(x);

//L0x157:	/* lda */
	a = 0x010;
	SET_NZ(a);

L0x159:	/* clr */
	addr = x;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x15a:	/* incx */
	INC(x, x);

//L0x15b:	/* deca */
	DEC(a, a);

//L0x15c:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x159);

//L0x15e:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x15f:	/* ldx */
	x = 0x039;
	SET_NZ(x);

L0x161:	/* tst */
	addr = x;
	SET_NZ(MCU_RDMEM(addr));

//L0x162:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x16d);

//L0x164:	/* txa */
	a = x;

//L0x165:	/* adda */
	ADD(a, a, 0x008);

//L0x167:	/* tax */
	x = a;

//L0x168:	/* cmpa */
	SUB(temp, a, 0x049);

//L0x16a:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x161);

//L0x16c:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x16d:	/* lda */
	addr = 0x037;
	a = MCU_RDMEM(0x037);
	SET_NZ(a);

//L0x170:	/* suba */
	addr = 0x035;
	SUB(a, a, MCU_RDMEM(0x035));

//L0x173:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x17e);

//L0x175:	/* nega */
	NEG(a, a);
	SET_NZ(a);

//L0x176:	/* sta */
	addr = x + 0x004;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x178:	/* lda */
	a = 0x0fd;
	SET_NZ(a);

//L0x17a:	/* sta */
	addr = x + 0x006;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x17c:	/* bra */
	JUMP_IMM(0x184);

L0x17e:	/* sta */
	addr = x + 0x004;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x180:	/* lda */
	a = 0x003;
	SET_NZ(a);

//L0x182:	/* sta */
	addr = x + 0x006;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

L0x184:	/* lda */
	addr = 0x038;
	a = MCU_RDMEM(0x038);
	SET_NZ(a);

//L0x187:	/* suba */
	addr = 0x036;
	SUB(a, a, MCU_RDMEM(0x036));

//L0x18a:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x195);

//L0x18c:	/* nega */
	NEG(a, a);
	SET_NZ(a);

//L0x18d:	/* sta */
	addr = x + 0x005;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x18f:	/* lda */
	a = 0x0fd;
	SET_NZ(a);

//L0x191:	/* sta */
	addr = x + 0x007;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x193:	/* bra */
	JUMP_IMM(0x19b);

L0x195:	/* sta */
	addr = x + 0x005;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x197:	/* lda */
	a = 0x003;
	SET_NZ(a);

//L0x199:	/* sta */
	addr = x + 0x007;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

L0x19b:	/* lda */
	a = 0x001;
	SET_NZ(a);

//L0x19d:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(x, a);

//L0x19e:	/* lda */
	addr = x + 0x005;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1a0:	/* cmpa */
	addr = x + 0x004;
	SUB(temp, a, MCU_RDMEM(addr));

//L0x1a2:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x1b3);

//L0x1a4:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x034, a);

//L0x1a7:	/* lda */
	addr = x + 0x004;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1a9:	/* sta */
	addr = x + 0x005;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1ab:	/* lda */
	addr = 0x034;
	a = MCU_RDMEM(0x034);
	SET_NZ(a);

//L0x1ae:	/* sta */
	addr = x + 0x004;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1b0:	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//L0x1b2:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(x, a);

L0x1b3:	/* lda */
	addr = x + 0x005;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1b5:	/* sta */
	addr = x + 0x003;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1b7:	/* lda */
	addr = 0x035;
	a = MCU_RDMEM(0x035);
	SET_NZ(a);

//L0x1ba:	/* sta */
	addr = x + 0x001;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1bc:	/* lda */
	addr = 0x036;
	a = MCU_RDMEM(0x036);
	SET_NZ(a);

//L0x1bf:	/* sta */
	addr = x + 0x002;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1c1:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x1c2:	/* ldx */
	x = 0x039;
	SET_NZ(x);

L0x1c4:	/* tst */
	addr = x;
	SET_NZ(MCU_RDMEM(addr));

//L0x1c5:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x1ea);

//L0x1c7:	/* lda */
	addr = x + 0x005;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1c9:	/* adda */
	addr = x + 0x003;
	ADD(a, a, MCU_RDMEM(addr));

//L0x1cb:	/* sta */
	addr = x + 0x005;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1cd:	/* suba */
	addr = x + 0x004;
	SUB(a, a, MCU_RDMEM(addr));

//L0x1cf:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x1e1);

//L0x1d1:	/* sta */
	addr = x + 0x005;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1d3:	/* lda */
	addr = x + 0x002;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1d5:	/* adda */
	addr = x + 0x007;
	ADD(a, a, MCU_RDMEM(addr));

//L0x1d7:	/* sta */
	addr = x + 0x002;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

L0x1d9:	/* lda */
	addr = x + 0x001;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1db:	/* adda */
	addr = x + 0x006;
	ADD(a, a, MCU_RDMEM(addr));

//L0x1dd:	/* sta */
	addr = x + 0x001;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x1df:	/* bra */
	JUMP_IMM(0x1ea);

L0x1e1:	/* tst */
	addr = x;
	SET_NZ(MCU_RDMEM(addr));

//L0x1e2:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x1d9);

//L0x1e4:	/* lda */
	addr = x + 0x002;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x1e6:	/* adda */
	addr = x + 0x007;
	ADD(a, a, MCU_RDMEM(addr));

//L0x1e8:	/* sta */
	addr = x + 0x002;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

L0x1ea:	/* txa */
	a = x;

//L0x1eb:	/* adda */
	ADD(a, a, 0x008);

//L0x1ed:	/* tax */
	x = a;

//L0x1ee:	/* cmpa */
	SUB(temp, a, 0x049);

//L0x1f0:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x1c4);

//L0x1f2:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x1f3:	/* ldx */
	addr = 0x031;
	x = MCU_RDMEM(0x031);
	SET_NZ(x);

//L0x1f6:	/* tst */
	addr = 0x033;
	SET_NZ(MCU_RDMEM(0x033));

//L0x1f8:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x205);

//L0x1fa:	/* lda */
	addr = x + 0x20a;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

L0x1fd:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x032, a);

//L0x200:	/* incx */
	INC(x, x);

//L0x201:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x031, x);

//L0x204:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x205:	/* lda */
	addr = x + 0x2be;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x208:	/* bra */
	JUMP_IMM(0x1fd);

//L0x20a:	/* cmpa */
	addr = x;
	SUB(temp, a, MCU_RDMEM(addr));

//L0x20b:	/* dec */
	addr = 0x043;
	DEC(temp, MCU_RDMEM(0x043));
	MCU_WRMEM(addr, temp);

//L0x35a:	/* brset7 */
	BRSET(0x000, 7)
	JUMP_IMM(0x35d);

L0x35d:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x360);

L0x360:	/* lsr */
//invalid instruction!
	goto invalid_pc;

//L0x362:	/* brn */
//invalid instruction!
	goto invalid_pc;

//L0x364:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x367);

L0x367:	/* brset0 */
	BRSET(0x08d, 0)
	JUMP_IMM(0x3c7);

L0x36a:	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//L0x36b:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x36e);

L0x36e:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

L0x371:	/* bset5 */
	BSET(0x08e, 5);

//L0x373:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x376);

L0x376:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x379:	/* stx */
	addr = x + 0x1c01;
	SET_NZ(x);
	MCU_WRMEM(addr, x);

//L0x37c:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x37f);

L0x37f:	/* brset0 */
	BRSET(0x0b4, 0)
	JUMP_IMM(0x376);

//L0x382:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x383:	/* brset1 */
	BRSET(0x000, 1)
	JUMP_IMM(0x386);

L0x386:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x389:	/* tst */
	addr = 0x07f;
	SET_NZ(MCU_RDMEM(0x07f));

//L0x38b:	/* brset2 */
	BRSET(0x000, 2)
	JUMP_IMM(0x38e);

L0x38e:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3e5);

//L0x391:	/* bita */
//invalid instruction!
	goto invalid_pc;

//L0x394:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x397);

L0x397:	/* brset0 */
	BRSET(0x044, 0)
	JUMP_IMM(0x40a);

//L0x39a:	/* brclr3 */
	BRCLR(0x012, 3)
	JUMP_IMM(0x39d);

L0x39d:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3a0);

L0x3a0:	/* lsr */
//invalid instruction!
	goto invalid_pc;

//L0x3a2:	/* bset2 */
	BSET(0x024, 2);

//L0x3aa:	/* bhcs */
	IF_CC_H()
	JUMP_IMM(0x3f4);

//L0x3ac:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3af);

L0x3af:	/* brset0 */
	BRSET(0x014, 0)
	goto invalid_pc;

//L0x3b2:	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//L0x3b3:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x3b4:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3b7);

L0x3b7:	/* brset0 */
	BRSET(0x004, 0)
	goto invalid_pc;

//L0x3ba:	/* bita */
//invalid instruction!
	goto invalid_pc;

//L0x3bc:	/* brclr0 */
	BRCLR(0x000, 0)
	JUMP_IMM(0x3bf);

L0x3bf:	/* brset0 */
	BRSET(0x0f4, 0)
	JUMP_IMM(0x36a);

//L0x3c2:	/* asl */
	addr = x + 0x041;
	ASL(temp, MCU_RDMEM(addr));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x3c4:	/* brset1 */
	BRSET(0x000, 1)
	JUMP_IMM(0x3c7);

L0x3c7:	/* brset0 */
	BRSET(0x0e4, 0)
	goto invalid_pc;

//L0x3ca:	/* bita */
//invalid instruction!
	goto invalid_pc;

//L0x3cd:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3d0);

L0x3d0:	/* anda */
	addr = x + 0xf4ad;
	AND(a, a, MCU_RDMEM(addr));
	SET_NZ(a);

//L0x3d3:	/* brclr2 */
	BRCLR(0x009, 2)
	JUMP_IMM(0x3d6);

L0x3d6:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x39d);

//L0x3d9:	/* clrx */
	x = 0;
	SET_NZ(x);

//L0x3da:	/* clrx */
	x = 0;
	SET_NZ(x);

//L0x3db:	/* brclr5 */
	BRCLR(0x012, 5)
	JUMP_IMM(0x3de);

L0x3de:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x3e1:	/* ldx */
	addr = x + 0x0c0;
	x = MCU_RDMEM(addr);
	SET_NZ(x);

//L0x3e3:	/* bset3 */
	BSET(0x024, 3);

L0x3e5:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3e8);

L0x3e8:	/* anda */
	AND(a, a, 0x059);
	SET_NZ(a);

//L0x3ea:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x3eb:	/* bms */
	IF_CC_int()
	JUMP_IMM(0x435);

//L0x3ed:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3f0);

L0x3f0:	/* nega */
	NEG(a, a);
	SET_NZ(a);

//L0x3f1:	/* jmp */
	goto invalid_pc;

//L0x3f2:	/* bset6 */
	BSET(0x05b, 6);

L0x3f4:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x3f5:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3f8);

L0x3f8:	/* lsra */
	flag_c = a & 0x01;
	a >>= 1;
	SET_NZ(a);

//L0x3f9:	/* ldx */
	addr = x + 0xf82b;
	x = MCU_RDMEM(addr);
	SET_NZ(x);

//L0x3fc:	/* adca */
	ADC(a, a, 0x08d);

//L0x3fe:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x43b);

//L0x401:	/* brset0 */
	BRSET(0x07b, 0)
	goto invalid_pc;

//L0x404:	/* bclr1 */
	BCLR(0x0f6, 1);

//L0x406:	/* dec */
	addr = x;
	DEC(temp, MCU_RDMEM(addr));
	MCU_WRMEM(addr, temp);

//L0x407:	/* brset0 */
	BRSET(0x0fb, 0)
	goto invalid_pc;

L0x40a:	/* neg */
	addr = 0x09e;
	NEG(temp, MCU_RDMEM(0x09e));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x40c:	/* bhi */
	IF_CC_HI()
	JUMP_IMM(0x40e);

L0x40e:	/* brset0 */
	BRSET(0x000, 0)
	goto invalid_pc;

//L0x411:	/* com */
//invalid instruction!
	goto invalid_pc;

//L0x413:	/* bclr5 */
	BCLR(0x0ab, 5);

//L0x415:	/* bset5 */
	BSET(0x000, 5);

//L0x417:	/* brset0 */
	BRSET(0x0ed, 0)
	goto invalid_pc;

//L0x41a:	/* sbca */
	addr = 0x922b;
	SBC(a, a, MCU_RDMEM(0x922b));

//L0x41d:	/* comx */
	COM(x, x);
	SET_NZ(x);

//L0x41e:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x3c7);

L0x420:	/* lda */
	a = 0x003;
	SET_NZ(a);

// L0x422:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x060, a);

L0x425:	/* lda */
	a = 0x017;
	SET_NZ(a);

// L0x427:	/* bsr */
	PUSHWORD(0x429);
	JUMP_IMM(0x478);

L0x429:	/* jsr */
	PUSHWORD(0x42c);
	JUMP_IMM(0x4fc);

L0x42c:	/* lda */
	a = 0x014;
	SET_NZ(a);

//L0x42e:	/* bsr */
	PUSHWORD(0x430);
	JUMP_IMM(0x478);

L0x430:	/* jsr */
	PUSHWORD(0x433);
	JUMP_IMM(0x4af);

L0x433:	/* ldx */
	x = 0x007;
	SET_NZ(x);

L0x435:	/* lda */
	addr = x + 0x050;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x438:	/* sta */
	addr = x + 0x040;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

L0x43b:	/* decx */
	DEC(x, x);

//L0x43c:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x435);

//L0x43e:	/* dec */
	addr = 0x060;
	DEC(temp, MCU_RDMEM(0x060));
	MCU_WRMEM(addr, temp);

//L0x440:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x425);

//L0x442:	/* ldx */
	x = 0x007;
	SET_NZ(x);

L0x444:	/* clr */
	addr = x + 0x040;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x446:	/* decx */
	DEC(x, x);

//L0x447:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x444);

//L0x449:	/* lda */
	a = 0x014;
	SET_NZ(a);

//L0x44b:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x060, a);

L0x44e:	/* asl */
	addr = 0x040;
	ASL(temp, MCU_RDMEM(0x040));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x450:	/* rol */
	addr = 0x041;
	ROL(temp, MCU_RDMEM(0x041));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x452:	/* rol */
	addr = 0x042;
	ROL(temp, MCU_RDMEM(0x042));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x454:	/* rol */
	addr = 0x043;
	ROL(temp, MCU_RDMEM(0x043));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x456:	/* lda */
	a = 0x000;
	SET_NZ(a);

//L0x458:	/* bsr */
	PUSHWORD(0x45a);
	JUMP_IMM(0x478);

L0x45a:	/* jsr */
	PUSHWORD(0x45d);
	JUMP_IMM(0x499);

L0x45d:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x46c);

//L0x45f:	/* bset0 */
	BSET(0x040, 0);

//L0x461:	/* ldx */
	x = 0x007;
	SET_NZ(x);

L0x463:	/* lda */
	addr = x + 0x058;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x466:	/* sta */
	addr = x + 0x050;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x469:	/* decx */
	DEC(x, x);

//L0x46a:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x463);

L0x46c:	/* dec */
	addr = 0x060;
	DEC(temp, MCU_RDMEM(0x060));
	MCU_WRMEM(addr, temp);

//L0x46e:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x44e);

//L0x470:	/* ldx */
	x = 0x01f;
	SET_NZ(x);

L0x472:	/* clr */
	addr = x + 0x047;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x474:	/* decx */
	DEC(x, x);

//L0x475:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x472);

//L0x477:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x478:	/* adda */
	addr = 0x060;
	ADD(a, a, MCU_RDMEM(0x060));

//L0x47b:	/* asla */
	ASL(a, a);
	SET_NZ(a);

//L0x47c:	/* asla */
	ASL(a, a);
	SET_NZ(a);

//L0x47d:	/* asla */
	ASL(a, a);
	SET_NZ(a);

//L0x47e:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x063, a);

//L0x481:	/* clrx */
	x = 0;
	SET_NZ(x);

L0x482:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x04f, x);

//L0x485:	/* txa */
	a = x;

//L0x486:	/* adda */
	addr = 0x063;
	ADD(a, a, MCU_RDMEM(0x063));

//L0x489:	/* tax */
	x = a;

//L0x48a:	/* lda */
	addr = x + 0x348;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x48d:	/* ldx */
	addr = 0x04f;
	x = MCU_RDMEM(0x04f);
	SET_NZ(x);

//L0x490:	/* sta */
	addr = x + 0x048;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x493:	/* incx */
	INC(x, x);

//L0x494:	/* cpx */
	SUB(temp, x, 0x008);

//L0x496:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x482);

//L0x498:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x499:	/* clrx */
	x = 0;
	SET_NZ(x);

//L0x49a:	/* lda */
	a = 0x008;
	SET_NZ(a);

//L0x49c:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x063, a);

//L0x49f:	/* clc */
	flag_c = 0;

L0x4a0:	/* lda */
	addr = x + 0x050;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x4a3:	/* sbca */
	addr = x + 0x048;
	SBC(a, a, MCU_RDMEM(addr));

//L0x4a6:	/* sta */
	addr = x + 0x058;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x4a9:	/* incx */
	INC(x, x);

//L0x4aa:	/* dec */
	addr = 0x063;
	DEC(temp, MCU_RDMEM(0x063));
	MCU_WRMEM(addr, temp);

//L0x4ac:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x4a0);

//L0x4ae:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x4af:	/* ldx */
	x = 0x007;
	SET_NZ(x);

L0x4b1:	/* clr */
	addr = x + 0x040;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x4b3:	/* decx */
	DEC(x, x);

//L0x4b4:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x4b1);

//L0x4b6:	/* ldx */
	x = 0x00f;
	SET_NZ(x);

L0x4b8:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x066, x);

//L0x4bb:	/* lda */
	a = 0x008;
	SET_NZ(a);

//L0x4bd:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x065, a);

L0x4c0:	/* lda */
	a = 0x009;
	SET_NZ(a);

//L0x4c2:	/* clc */
	flag_c = 0;

L0x4c3:	/* ror */
	addr = x + 0x040;
	ROR(temp, MCU_RDMEM(addr));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x4c5:	/* decx */
	DEC(x, x);

//L0x4c6:	/* deca */
	DEC(a, a);

//L0x4c7:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x4c3);

//L0x4c9:	/* ldx */
	addr = 0x066;
	x = MCU_RDMEM(0x066);
	SET_NZ(x);

L0x4cc:	/* lda */
	addr = x + 0x050;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x4cf:	/* cmpa */
	addr = x + 0x040;
	SUB(temp, a, MCU_RDMEM(addr));

//L0x4d2:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x4d7);

//L0x4d4:	/* decx */
	DEC(x, x);

//L0x4d5:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x4cc);

L0x4d7:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x4ef);

//L0x4d9:	/* lda */
	a = 0x009;
	SET_NZ(a);

//L0x4db:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x064, a);

//L0x4de:	/* ldx */
	addr = 0x066;
	x = MCU_RDMEM(0x066);
	SET_NZ(x);

L0x4e1:	/* lda */
	addr = x + 0x048;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x4e4:	/* sbca */
	addr = x + 0x038;
	SBC(a, a, MCU_RDMEM(addr));

//L0x4e7:	/* sta */
	addr = x + 0x048;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x4ea:	/* incx */
	INC(x, x);

//L0x4eb:	/* dec */
	addr = 0x064;
	DEC(temp, MCU_RDMEM(0x064));
	MCU_WRMEM(addr, temp);

//L0x4ed:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x4e1);

L0x4ef:	/* ldx */
	addr = 0x066;
	x = MCU_RDMEM(0x066);
	SET_NZ(x);

//L0x4f2:	/* dec */
	addr = 0x065;
	DEC(temp, MCU_RDMEM(0x065));
	MCU_WRMEM(addr, temp);

//L0x4f4:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x4c0);

//L0x4f6:	/* decx */
	DEC(x, x);

//L0x4f7:	/* cpx */
	SUB(temp, x, 0x008);

//L0x4f9:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x4b8);

//L0x4fb:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x4fc:	/* ldx */
	x = 0x00f;
	SET_NZ(x);

L0x4fe:	/* clr */
	addr = x + 0x050;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x500:	/* decx */
	DEC(x, x);

//L0x501:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x4fe);

L0x503:	/* incx */
	INC(x, x);

//L0x504:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x064, x);

//L0x507:	/* lda */
	addr = x + 0x048;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x50a:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x062, a);

//L0x50d:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x066, x);

//L0x510:	/* ldx */
	x = 0x0ff;
	SET_NZ(x);

L0x512:	/* incx */
	INC(x, x);

//L0x513:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x065, x);

//L0x516:	/* lda */
	addr = x + 0x040;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x519:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x061, a);

//L0x51c:	/* lda */
	a = 0x008;
	SET_NZ(a);

//L0x51e:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x063, a);

//L0x521:	/* ldx */
	x = 0x000;
	SET_NZ(x);

//L0x523:	/* txa */
	a = x;

L0x524:	/* asla */
	ASL(a, a);
	SET_NZ(a);

//L0x525:	/* rolx */
	ROL(x, x);
	SET_NZ(x);

//L0x526:	/* asl */
	addr = 0x061;
	ASL(temp, MCU_RDMEM(0x061));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x528:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x530);

//L0x52a:	/* adda */
	addr = 0x062;
	ADD(a, a, MCU_RDMEM(0x062));

//L0x52d:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x530);

//L0x52f:	/* incx */
	INC(x, x);

L0x530:	/* dec */
	addr = 0x063;
	DEC(temp, MCU_RDMEM(0x063));
	MCU_WRMEM(addr, temp);

//L0x532:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x524);

//L0x534:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x063, x);

//L0x537:	/* ldx */
	addr = 0x066;
	x = MCU_RDMEM(0x066);
	SET_NZ(x);

//L0x53a:	/* adda */
	addr = x + 0x050;
	ADD(a, a, MCU_RDMEM(addr));

//L0x53d:	/* sta */
	addr = x + 0x050;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x540:	/* lda */
	addr = 0x063;
	a = MCU_RDMEM(0x063);
	SET_NZ(a);

//L0x543:	/* adca */
	addr = x + 0x051;
	ADC(a, a, MCU_RDMEM(addr));

//L0x546:	/* sta */
	addr = x + 0x051;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x549:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x550);

L0x54b:	/* incx */
	INC(x, x);

//L0x54c:	/* inc */
	addr = x + 0x051;
	INC(temp, MCU_RDMEM(addr));
	MCU_WRMEM(addr, temp);

//L0x54e:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x54b);

L0x550:	/* inc */
	addr = 0x066;
	INC(temp, MCU_RDMEM(0x066));
	MCU_WRMEM(addr, temp);

//L0x552:	/* ldx */
	addr = 0x065;
	x = MCU_RDMEM(0x065);
	SET_NZ(x);

//L0x555:	/* cpx */
	SUB(temp, x, 0x007);

//L0x557:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x512);

//L0x559:	/* ldx */
	addr = 0x064;
	x = MCU_RDMEM(0x064);
	SET_NZ(x);

//L0x55c:	/* cpx */
	SUB(temp, x, 0x007);

//L0x55e:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x503);

//L0x560:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

//L0x561:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x562:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x563:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x564:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x565:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x566:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x567:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x568:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x569:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x56a:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x56b:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x56c:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x56d:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x56e:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

//L0x56f:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);

L0x570:	/* sei */
//INIT_PC
	m68705.flag_i = 1;

//L0x571:	/* rsp */
	sp = 0x7f;

//L0x572:	/* jmp */
	JUMP_IMM(0x66f);

L0x575:	/* ldx */
	x = 0x070;
	SET_NZ(x);

L0x577:	/* clr */
	addr = x + 0x00f;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x579:	/* decx */
	DEC(x, x);

//L0x57a:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x577);

//L0x57c:	/* cli */
	m68705.flag_i = 0;

L0x57d:	/* nop */

//L0x57e:	/* tst */
	addr = 0x018;
	SET_NZ(MCU_RDMEM(0x018));

//L0x580:	/* beq */
	IF_CC_Z() {
	    // waiting for data, we can exit for now...
	    m68705.pc = 0x57d;
	    m68705.x = x;
	    m68705.a = a;
	    m68705.sp = sp;
	    m68705.flag_c = flag_c;
	    m68705.flag_h = flag_h;
	    m68705.flag_n = flag_n;
	    m68705.flag_z = flag_z;
	    return;
	}

//L0x582:	/* brclr1 */
	BRCLR(0x012, 1)
	JUMP_IMM(0x593);

//L0x585:	/* lda */
	a = 0x07d;
	SET_NZ(a);

//L0x587:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x013, a);

//L0x589:	/* clr */
	addr = 0x011;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x58b:	/* clr */
	addr = 0x010;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x58d:	/* lda */
	a = 0x00e;
	SET_NZ(a);

//L0x58f:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x008, a);

//L0x591:	/* clr */
	addr = 0x009;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

L0x593:	/* jsr */
	PUSHWORD(0x595);
	{
	    if (ram_mcu[0x18] == 0xcc) {
		addr = (ram_mcu[0x19]<<8)|ram_mcu[0x1a];
		if (addr == 0x120) // 2
		    JUMP_IMM(0x120);
		else if (addr == 0x12f) // 3
		    JUMP_IMM(0x12f);
		else if (addr == 0x155) // 4
		    JUMP_IMM(0x155);
		else if (addr == 0x15f) // 5
		    JUMP_IMM(0x15f);
		else if (addr == 0x1c2) // 6
		    JUMP_IMM(0x1c2);
		else if (addr == 0x1f3) // 6
		    JUMP_IMM(0x1f3);
		else if (addr == 0x420)
		    JUMP_IMM(0x420);
		else if (addr == 0x570) // index 0 from table at $740
		    JUMP_IMM(0x570);
		else if (addr == 0x100) // 1
		    JUMP_IMM(0x100);
		else {
		    // the other addresses are filled with 33d, which is not code
		    // so this part the else here should never be hit anymore !
		    printf("jump from ram to %x\n",addr);
		    printf("addr unknown !\n");
		    exit(1);
		}
	    } else {
		printf("code in mcu ram 0x18 unknown : %x\n",ram_mcu[0x18]);
		goto invalid_pc;
	    }
	}

L0x595:	/* sei */
	m68705.flag_i = 1;

L0x596:	/* brclr1 */
	BRCLR(0x002, 1)
	JUMP_IMM(0x596);

//L0x599:	/* ldx */
	x = 0x0ff;
	SET_NZ(x);

//L0x59b:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//L0x59d:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//L0x59f:	/* bclr2 */
	BCLR(0x001, 2);

//L0x5a1:	/* bset2 */
	BSET(0x001, 2);

//L0x5a3:	/* clr */
	addr = 0x018;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x5a5:	/* cli */
	m68705.flag_i = 0;

//L0x5a6:	/* bra */
	JUMP_IMM(0x57d);

L0x5a8:	/* brset0 */
	BRSET(0x012, 0)
	JUMP_IMM(0x5c8);

//L0x5ab:	/* anda */
	AND(a, a, 0x007);
	SET_NZ(a);

//L0x5ad:	/* tax */
	x = a;

//L0x5ae:	/* clra */
	a = 0;
	SET_NZ(a);

//L0x5af:	/* sec */
	flag_c = 1;

L0x5b0:	/* rola */
	ROL(a, a);
	SET_NZ(a);

//L0x5b1:	/* decx */
	DEC(x, x);

//L0x5b2:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x5b0);

//L0x5b4:	/* ldx */
	addr = 0x01f;
	x = MCU_RDMEM(0x01f);
	SET_NZ(x);

//L0x5b6:	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//L0x5b7:	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//L0x5b8:	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//L0x5b9:	/* anda */
	addr = x + 0x760;
	AND(a, a, MCU_RDMEM(addr));
	SET_NZ(a);

//L0x5bc:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x5c8);

//L0x5be:	/* bset1 */
	BSET(0x01b, 1);

//L0x5c0:	/* tst */
	addr = 0x01f;
	SET_NZ(MCU_RDMEM(0x01f));

//L0x5c2:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x60c);

//L0x5c4:	/* lda */
	a = 0x09f;
	SET_NZ(a);

//L0x5c6:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01f, a);

L0x5c8:	/* lda */
	addr = 0x01f;
	a = MCU_RDMEM(0x01f);
	SET_NZ(a);

//L0x5ca:	/* cmpa */
	SUB(temp, a, 0x01c);

//L0x5cc:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x603);

//L0x5ce:	/* brset0 */
	BRSET(0x012, 0)
	JUMP_IMM(0x5eb);

//L0x5d1:	/* lda */
	addr = 0x01e;
	a = MCU_RDMEM(0x01e);
	SET_NZ(a);

//L0x5d3:	/* ldx */
	addr = 0x01d;
	x = MCU_RDMEM(0x01d);
	SET_NZ(x);

//L0x5d5:	/* cpx */
	addr = 0x760;
	SUB(temp, x, MCU_RDMEM(0x760));

//L0x5d8:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x601);

//L0x5da:	/* bhi */
	IF_CC_HI()
	JUMP_IMM(0x5e1);

//L0x5dc:	/* cmpa */
	addr = 0x761;
	SUB(temp, a, MCU_RDMEM(0x761));

//L0x5df:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x601);

L0x5e1:	/* cpx */
	SUB(temp, x, 0x003);

//L0x5e3:	/* bhi */
	IF_CC_HI()
	JUMP_IMM(0x601);

//L0x5e5:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x5eb);

//L0x5e7:	/* cmpa */
	SUB(temp, a, 0x04f);

//L0x5e9:	/* bcc */
	IF_CC_NC()
	JUMP_IMM(0x601);

L0x5eb:	/* lda */
	a = 0x0c6;
	SET_NZ(a);

//L0x5ed:	/* ldx */
	x = 0x01c;
	SET_NZ(x);

//L0x5ef:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(x, a);

//L0x5f0:	/* lda */
	a = 0x081;
	SET_NZ(a);

//L0x5f2:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01f, a);

//L0x5f4:	/* jsr */
	PUSHWORD(0x5f5);
	goto invalid_pc;

L0x5f5:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(x, a);

L0x5f6:	/* decx */
	DEC(x, x);

//L0x5f7:	/* inc */
	addr = x + 0x003;
	INC(temp, MCU_RDMEM(addr));
	MCU_WRMEM(addr, temp);

//L0x5f9:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x5f6);

//L0x5fb:	/* ldx */
	x = 0x01c;
	SET_NZ(x);

//L0x5fd:	/* bra */
	JUMP_IMM(0x607);

L0x5ff:	/* bra */
	JUMP_IMM(0x5a8);

L0x601:	/* bset2 */
	BSET(0x01b, 2);

L0x603:	/* ldx */
	addr = 0x01f;
	x = MCU_RDMEM(0x01f);
	SET_NZ(x);

//L0x605:	/* bmi */
	IF_CC_N()
	JUMP_IMM(0x617);

L0x607:	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//L0x609:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//L0x60b:	/* lda */
	addr = x;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

L0x60c:	/* brclr1 */
	BRCLR(0x002, 1)
	JUMP_IMM(0x60c);

//L0x60f:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//L0x611:	/* bclr2 */
	BCLR(0x001, 2);

//L0x613:	/* bset2 */
	BSET(0x001, 2);

L0x615:	/* clr */
	addr = 0x01f;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

L0x617:	/* rti */
//invalid instruction!
	m68705.pc = 0x61a;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
	return;

L0x618:	/* bih */
//BIH 0x61a

L0x61a:	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x61c:	/* bclr1 */
	BCLR(0x001, 1);

//L0x61e:	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//L0x620:	/* bset1 */
	BSET(0x001, 1);

//L0x622:	/* ldx */
	addr = 0x01f;
	x = MCU_RDMEM(0x01f);
	SET_NZ(x);

//L0x624:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x638);

//L0x626:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01f, a);

//L0x628:	/* aslx */
	ASL(x, x);
	SET_NZ(x);

//L0x629:	/* lsrx */
	flag_c = x & 0x01;
	x >>= 1;
	SET_NZ(x);

//L0x62a:	/* lda */
	addr = 0x780;
	a = MCU_RDMEM(0x780);
	SET_NZ(a);

//L0x62d:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x633);

//L0x62f:	/* cpx */
	SUB(temp, x, 0x01d);

//L0x631:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x615);

L0x633:	/* lda */
	addr = 0x01f;
	a = MCU_RDMEM(0x01f);
	SET_NZ(a);

//L0x635:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(x, a);

//L0x636:	/* bra */
	JUMP_IMM(0x615);

L0x638:	/* tsta */
	SET_NZ(a);

//L0x639:	/* bpl */
	IF_CC_NN()
	JUMP_IMM(0x63e);

//L0x63b:	/* eora */
	addr = 0x781;
	EOR(a, a, MCU_RDMEM(0x781));
	SET_NZ(a);

L0x63e:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01f, a);

//L0x640:	/* cmpa */
	SUB(temp, a, 0x00f);

//L0x642:	/* bhi */
	IF_CC_HI()
	JUMP_IMM(0x5ff);

//L0x644:	/* tax */
	x = a;

//L0x645:	/* aslx */
	ASL(x, x);
	SET_NZ(x);

//L0x646:	/* lda */
	addr = x + 0x740;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x649:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x019, a);

//L0x64b:	/* lda */
	addr = x + 0x741;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x64e:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x01a, a);

//L0x650:	/* lda */
	a = 0x0cc;
	SET_NZ(a);

//L0x652:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x018, a);

//L0x654:	/* bra */
	JUMP_IMM(0x615);

	// This address is copied in $10, so I patch the code to read things from there... !
	// ($11, $19, and $20)

L0x656:	/* adda */
	addr = x + (MCU_RDMEM(0x11)<<8); //0x700;
	ADD(a, a, MCU_RDMEM(addr));

//L0x659:	/* incx */
	INC(x, x);

//L0x65a:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x65e);

//L0x65c:	/* inc */
	addr = 0x011;
	INC(temp, MCU_RDMEM(0x011));
	MCU_WRMEM(addr, temp);

L0x65e:	/* cpx */
	SUB(temp, x, MCU_RDMEM(0x019)); // $18

//L0x660:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x656);

//L0x662:	/* ldx */
	addr = 0x011;
	x = MCU_RDMEM(0x011);
	SET_NZ(x);

//L0x665:	/* cpx */ // $1f
	SUB(temp, x, MCU_RDMEM(0x020));

//L0x667:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x66e);

//L0x669:	/* ldx */
	addr = 0x019;
	x = MCU_RDMEM(0x019);
	SET_NZ(x);

//L0x66c:	/* bra */
	JUMP_IMM(0x656);

L0x66e:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x66f:	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//L0x671:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//L0x673:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x005, a);

//L0x675:	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x677:	/* ldx */
	x = 0x019;
	SET_NZ(x);

L0x679:	/* lda */
	addr = x + 0x655;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x67c:	/* sta */
	addr = x + 0x00f;
	SET_NZ(a);
	MCU_WRMEM(addr, a);

//L0x67e:	/* decx */
	DEC(x, x);

//L0x67f:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x679);

//L0x681:	/* clra */
	a = 0;
	SET_NZ(a);

//L0x682:	/* ldx */
	x = 0x0f8;
	SET_NZ(x);

//L0x684:	/* jsr */
	PUSHWORD(0x686);
	JUMP_IMM(0x656);
	// goto invalid_pc;

L0x686:	/* ldx */
	x = 0x007;
	SET_NZ(x);

//L0x688:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x020, x);

//L0x68a:	/* ldx */
	x = 0x038;
	SET_NZ(x);

//L0x68c:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x019, x);

//L0x68e:	/* ldx */
	x = 0x000;
	SET_NZ(x);

//L0x690:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x011, x);

//L0x692:	/* ldx */
	x = 0x080;
	SET_NZ(x);

//L0x694:	/* jsr */
	PUSHWORD(0x696);
	JUMP_IMM(0x656);
	// goto invalid_pc;

L0x696:	/* tax */
	x = a;

//L0x697:	/* bsr */
	PUSHWORD(0x699);
	JUMP_IMM(0x6d3);

L0x699:	/* txa */
	a = x;

//L0x69a:	/* bsr */
	PUSHWORD(0x69c);
	JUMP_IMM(0x6de);

L0x69c:	/* lda */
	addr = 0x010;
	a = MCU_RDMEM(0x010);
	SET_NZ(a);

//L0x69e:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x6a3);

//L0x6a0:	/* jmp */
	JUMP_IMM(0x575);

L0x6a3:	/* ldx */
	x = 0x006;
	SET_NZ(x);

L0x6a5:	/* lda */
	addr = x + 0x738;
	a = MCU_RDMEM(addr);
	SET_NZ(a);

//L0x6a8:	/* bsr */
	PUSHWORD(0x6aa);
	JUMP_IMM(0x6de);

L0x6aa:	/* decx */
	DEC(x, x);

//L0x6ab:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x6a5);

L0x6ad:	/* bsr */
	PUSHWORD(0x6af);
	JUMP_IMM(0x6d3);

L0x6af:	/* txa */
	a = x;

//L0x6b0:	/* eora */
	addr = 0x010;
	EOR(a, a, MCU_RDMEM(0x010));
	SET_NZ(a);

//L0x6b2:	/* coma */
	COM(a, a);
	SET_NZ(a);

L0x6b3:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x6b3);

//L0x6b5:	/* txa */
	a = x;

//L0x6b6:	/* bsr */
	PUSHWORD(0x6b8);
	JUMP_IMM(0x6de);

L0x6b8:	/* incx */
	INC(x, x);

//L0x6b9:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x6ad);

//L0x6bb:	/* bra */
	JUMP_IMM(0x6bf);

L0x6bd:	/* bsr */
	PUSHWORD(0x6bf);
	JUMP_IMM(0x6c5);

L0x6bf:	/* bsr */
	PUSHWORD(0x6c1);
	JUMP_IMM(0x6d3);

L0x6c1:	/* bne */
	IF_CC_NZ()
	JUMP_IMM(0x6bd);

//L0x6c3:	/* bra */
	JUMP_IMM(0x66f);

L0x6c5:	/* deca */
	DEC(a, a);

//L0x6c6:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x6ee);

//L0x6c8:	/* deca */
	DEC(a, a);

//L0x6c9:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x6fa);

//L0x6cb:	/* deca */
	DEC(a, a);

//L0x6cc:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x70b);

//L0x6ce:	/* deca */
	DEC(a, a);

//L0x6cf:	/* beq */
	IF_CC_Z()
	JUMP_IMM(0x726);

L0x6d1:	/* bra */
	JUMP_IMM(0x6d1);

L0x6d3:	/* bih */
//BIH 0x6d5
	if (--bih_count == 0) {
	m68705.pc = 0x6d5;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
	return;
	}

L0x6d5:	/* bclr1 */
	BCLR(0x001, 1);

//L0x6d7:	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//L0x6d9:	/* bset1 */
	BSET(0x001, 1);

//L0x6db:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x010, a);

//L0x6dd:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x6de:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//L0x6e0:	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//L0x6e2:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

L0x6e4:	/* brclr1 */
	BRCLR(0x002, 1) {
	m68705.pc = 0x6e4;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
	return;
	}
	// JUMP_IMM(0x6e4);

//L0x6e7:	/* bclr2 */
	BCLR(0x001, 2);

//L0x6e9:	/* bset2 */
	BSET(0x001, 2);

//L0x6eb:	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x6ed:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x6ee:	/* ldx */
	x = 0x0ff;
	SET_NZ(x);

//L0x6f0:	/* bsr */
	PUSHWORD(0x6f2);
	JUMP_IMM(0x720);

L0x6f2:	/* bclr5 */
	BCLR(0x001, 5);

//L0x6f4:	/* lda */
	addr = 0x000;
	a = MCU_RDMEM(0x000);
	SET_NZ(a);

//L0x6f6:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x001, x);

//L0x6f8:	/* bra */
	JUMP_IMM(0x6de);

L0x6fa:	/* bsr */
	PUSHWORD(0x6fc);
	JUMP_IMM(0x6d3);

L0x6fc:	/* ldx */
	x = 0x0ff;
	SET_NZ(x);

//L0x6fe:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//L0x700:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//L0x702:	/* bsr */
	PUSHWORD(0x704);
	JUMP_IMM(0x720);

L0x704:	/* bclr4 */
	BCLR(0x001, 4);

//L0x706:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x001, x);

//L0x708:	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x70a:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x70b:	/* ldx */
	x = 0x0bf;
	SET_NZ(x);

L0x70d:	/* bsr */
	PUSHWORD(0x70f);
	JUMP_IMM(0x6d3);

L0x70f:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//L0x711:	/* lda */
	a = 0x0ff;
	SET_NZ(a);

//L0x713:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x004, a);

//L0x715:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x001, x);

//L0x717:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x001, a);

//L0x719:	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x71b:	/* sec */
	flag_c = 1;

//L0x71c:	/* rolx */
	ROL(x, x);
	SET_NZ(x);

//L0x71d:	/* bcs */
	IF_CC_C()
	JUMP_IMM(0x70d);

//L0x71f:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x720:	/* bclr3 */
	BCLR(0x001, 3);

L0x722:	/* brset2 */
	BRSET(0x002, 2)
	JUMP_IMM(0x722);

//L0x725:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

L0x726:	/* bsr */
	PUSHWORD(0x728);
	JUMP_IMM(0x6d3);

L0x728:	/* ldx */
	x = 0x0ff;
	SET_NZ(x);

//L0x72a:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x004, x);

//L0x72c:	/* sta */
	SET_NZ(a);
	MCU_WRMEM(0x000, a);

//L0x72e:	/* bclr0 */
	BCLR(0x001, 0);

//L0x730:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(0x001, x);

L0x732:	/* brclr3 */
	BRCLR(0x002, 3)
	JUMP_IMM(0x732);

//L0x735:	/* clr */
	addr = 0x004;
	temp = 0;
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x737:	/* rts */
	PULLWORD(m68705.pc);
	JUMP(m68705.pc);

//L0x738:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x73b);

L0x73b:	/* brset0 */
	BRSET(0x000, 0)
	JUMP_IMM(0x73e);

L0x73e:	/* brset0 */
	BRSET(0x0ff, 0)
	goto invalid_pc;

//L0x741:	/* neg */
	addr = x;
	NEG(temp, MCU_RDMEM(addr));
	SET_NZ(temp);
	MCU_WRMEM(addr, temp);

//L0x742:	/* brclr0 */
	BRCLR(0x000, 0)
	goto invalid_pc;

//L0x745:	/* bra */
	goto invalid_pc;

//L0x747:	/* bih */
//BIH 0x749
	if (--bih_count == 0) {
	m68705.pc = 0x749;
	m68705.x = x;
	m68705.a = a;
	m68705.sp = sp;
	m68705.flag_c = flag_c;
	m68705.flag_h = flag_h;
	m68705.flag_n = flag_n;
	m68705.flag_z = flag_z;
	return;
	}

L0x749:	/* illegal */
//invalid instruction!
	goto invalid_pc;

//L0x74a:	/* brclr0 */
	BRCLR(0x05f, 0)
	goto invalid_pc;

//L0x74d:	/* sbca */
	addr = 0x1f3;
	SBC(a, a, MCU_RDMEM(0x1f3));

//L0x750:	/* brclr1 */
	BRCLR(0x03d, 1)
	goto invalid_pc;

//L0x753:	/* tst */
	addr = 0x003;
	SET_NZ(MCU_RDMEM(0x003));

//L0x755:	/* tst */
	addr = 0x003;
	SET_NZ(MCU_RDMEM(0x003));

//L0x757:	/* tst */
	addr = 0x003;
	SET_NZ(MCU_RDMEM(0x003));

//L0x759:	/* tst */
	addr = 0x003;
	SET_NZ(MCU_RDMEM(0x003));

//L0x75b:	/* tst */
	addr = 0x004;
	SET_NZ(MCU_RDMEM(0x004));

//L0x75f:	/* tst */
	addr = 0x0ff;
	SET_NZ(MCU_RDMEM(0x0ff));

//L0x761:	/* stx */
	SET_NZ(x);
	MCU_WRMEM(x, x);


invalid_pc:
	print_debug("M68705: Invalid jump address (0x%x)\n", m68705.pc);
	printf("M68705: Invalid jump address (0x%x)\n", m68705.pc);
	print_ingame(200, "M68705: Invalid jump address (0x%x)\n", m68705.pc);
	exit(1);
	return;
}
