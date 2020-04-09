/*****************************************************************************
 *
 *   m6502.c
 *   Portable 6502/65c02/65sc02/6510/n2a03 emulator V1.2
 *
 *   Copyright Juergen Buchmueller, all rights reserved.
 *   65sc02 core Copyright Peter Trauner.
 *   Deco16 portions Copyright Bryan McPhail.
 *
 *   - This source code is released as freeware for non-commercial purposes.
 *   - You are free to use and redistribute this code in modified or
 *     unmodified form, provided you list me in the credits.
 *   - If you modify this source code, you must add a notice to each modified
 *     source file that it has been changed.  If you're a nice person, you
 *     will clearly mark each change too.  :)
 *   - If you wish to use this for commercial purposes, please contact me at
 *     pullmoll@t-online.de
 *   - The author of this copywritten work reserves the right to change the
 *     terms of its usage and license at any time, including retroactively
 *   - This entire notice must remain in the source code.
 *
 *****************************************************************************/
/* 2.February 2000 PeT added 65sc02 subtype */
/* 10.March   2000 PeT added 6502 set overflow input line */
/* 13.September 2000 PeT N2A03 jmp indirect */

#include <string.h>
#include "m6502.h"
#include "ops02.h"
#include "ill02.h"
#include "debug.h"

#define INLINE static inline
#define cpu_readop m6502_readop
#define M6502_NMI_VEC	0xfffa
#define M6502_RST_VEC	0xfffc
#define M6502_IRQ_VEC	0xfffe

#define DECO16_RST_VEC	0xfff0
#define DECO16_IRQ_VEC	0xfff2
#define DECO16_NMI_VEC	0xfff4

#define VERBOSE 0

#define LOG(x)	do { if (VERBOSE) print_debug x; } while (0)
#define change_pc(x)

extern UINT8 m6502_readop(UINT32 adr);
extern UINT16 m6502_readop_arg16(UINT32 adr);
extern UINT8 m6502_readop_arg(UINT32 adr);
extern UINT16 m6502_readop_arg16(UINT32 adr);
extern UINT8 m6502_read8(UINT32 adr);
extern UINT16 m6502_read16(UINT32 adr);
extern void m6502_write8(UINT32 adr,UINT8 data);
extern void m6502_write16(UINT32 adr,UINT16 data);

/****************************************************************************
 * The 6502 registers.
 ****************************************************************************/

static int m6502_IntOccured = 0;
static int m6502_ICount = 0;

m6502_Regs m6502;

/***************************************************************
 * include the opcode macros, functions and tables
 ***************************************************************/
#include "t6502.c"

#if (HAS_M6510)
#include "t6510.c"
#endif

#include "opsn2a03.h"

#if (HAS_N2A03)
#include "tn2a03.c"
#endif

#include "opsc02.h"

#if (HAS_M65C02)
#include "t65c02.c"
#endif

#if (HAS_M65SC02)
#include "t65sc02.c"
#endif

#if (HAS_DECO16)
#include "tdeco16.c"
#endif

/*****************************************************************************
 *
 *      6502 CPU interface functions
 *
 *****************************************************************************/

static void m6502_common_init(UINT8 subtype, void (*const *insn)(void), const char *type)
{
	memset(&m6502, 0, sizeof(m6502));
	m6502.subtype = subtype;
	m6502.insn = insn;
}

void m6502_init()
{
	m6502_common_init( SUBTYPE_6502, insn6502, "m6502");
}

void m6502_reset(void)
{
	/* wipe out the rest of the m6502 structure */
	/* read the reset vector into PC */
	PCL = RDMEM(M6502_RST_VEC);
	PCH = RDMEM(M6502_RST_VEC+1);

	m6502.sp.d = 0x01ff;	/* stack pointer starts at page 1 offset FF */
	m6502.p = F_T|F_I|F_Z|F_B|(P&F_D);	/* set T, I and Z flags */
	m6502.pending_irq = 0;	/* nonzero if an IRQ is pending */
	m6502.after_cli = 0;	/* pending IRQ and last insn cleared I */
	m6502.irq_state = 0;

	change_pc(PCD);
}

void m6502_get_context (void *dst)
{
	if( dst )
		*(m6502_Regs*)dst = m6502;
}

void m6502_set_context (void *src)
{
	if( src )
	{
		m6502 = *(m6502_Regs*)src;
		change_pc(PCD);
	}
}

INLINE void m6502_take_irq(void)
{
	if( !(P & F_I) )
	{
		EAD = M6502_IRQ_VEC;
		m6502_ICount -= 2;
		PUSH(PCH);
		PUSH(PCL);
		PUSH(P & ~F_B);
		P |= F_I;		/* set I flag */
		PCL = RDMEM(EAD);
		PCH = RDMEM(EAD+1);
		LOG(("M6502 takes IRQ ($%04x)\n", PCD));
		m6502.irq_state = 0;
		change_pc(PCD);
	}
	m6502.pending_irq = 0;
}

int m6502_execute(int cycles)
{
	m6502_ICount = cycles;

	change_pc(PCD);

	do
	{
		UINT8 op;
		PPC = PCD;

		/* if an irq is pending, take it now */
		if( m6502.pending_irq )
			m6502_take_irq();

		op = RDOP();
		(*m6502.insn[op])();

		/* check if the I flag was just reset (interrupts enabled) */
		if( m6502.after_cli )
		{
			LOG(("M6502 after_cli was >0" ));
			m6502.after_cli = 0;
			if (m6502.irq_state != CLEAR_LINE)
			{
				LOG((": irq line is asserted: set pending IRQ\n"));
				m6502.pending_irq = 1;
			}
			else
			{
				LOG((": irq line is clear\n"));
			}
		}
		else {
			if ( m6502.pending_irq == 2 ) {
				if ( m6502_IntOccured - m6502_ICount > 1 ) {
					m6502.pending_irq = 1;
				}
			}
			if( m6502.pending_irq == 1 )
				m6502_take_irq();
			if ( m6502.pending_irq == 2 ) {
				m6502.pending_irq = 1;
			}
		}

	} while (m6502_ICount > 0);

	return cycles - m6502_ICount;
}

void m6502_release_time_slice() {
    m6502_ICount = 0;
}

void m6502_set_irq_line(int irqline, int state)
{
	if (irqline == INPUT_LINE_NMI)
	{
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502 set_nmi_line(ASSERT)\n" ));
			EAD = M6502_NMI_VEC;
			m6502_ICount -= 2;
			PUSH(PCH);
			PUSH(PCL);
			PUSH(P & ~F_B);
			P |= F_I;		/* set I flag */
			PCL = RDMEM(EAD);
			PCH = RDMEM(EAD+1);
			LOG(("M6502 takes NMI ($%04x)\n", PCD));
			change_pc(PCD);
		}
	}
	else
	{
		if( irqline == M6502_SET_OVERFLOW )
		{
			if( m6502.so_state && !state )
			{
				LOG(( "M6502 set overflow\n" ));
				P|=F_V;
			}
			m6502.so_state=state;
			return;
		}
		m6502.irq_state = state;
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502 set_irq_line(ASSERT)\n" ));
			m6502.pending_irq = 1;
//          m6502.pending_irq = 2;
			m6502_IntOccured = m6502_ICount;
		}
	}
}



/****************************************************************************
 * 2A03 section
 ****************************************************************************/
#if (HAS_N2A03)

static void n2a03_init(int index, int clock, const void *config, int (*irqcallback)(int))
{
	m6502_common_init(index, clock, config, irqcallback, SUBTYPE_2A03, insn2a03, "n2a03");
}

/* The N2A03 is integrally tied to its PSG (they're on the same die).
   Bit 7 of address $4011 (the PSG's DPCM control register), when set,
   causes an IRQ to be generated.  This function allows the IRQ to be called
   from the PSG core when such an occasion arises. */
void n2a03_irq(void)
{
  m6502_take_irq();
}
#endif


/****************************************************************************
 * 6510 section
 ****************************************************************************/
#if (HAS_M6510)

static void m6510_init (int index, int clock, const void *config, int (*irqcallback)(int))
{
	m6502_common_init(index, clock, config, irqcallback, SUBTYPE_6510, insn6510, "m6510");
}

static void m6510_reset (void)
{
	m6502_reset();
	m6502.port = 0xff;
	m6502.ddr = 0x00;
}

static UINT8 m6510_get_port(void)
{
	return (m6502.port & m6502.ddr) | (m6502.ddr ^ 0xff);
}

static READ8_HANDLER( m6510_read_0000 )
{
	UINT8 result = 0x00;

	switch(offset)
	{
		case 0x0000:	/* DDR */
			result = m6502.ddr;
			break;
		case 0x0001:	/* Data Port */
			if (m6502.port_read)
				result = m6502.port_read( m6502.ddr );
			result = (m6502.ddr & m6502.port) | (~m6502.ddr & result);
			break;
	}
	return result;
}

static WRITE8_HANDLER( m6510_write_0000 )
{
	switch(offset)
	{
		case 0x0000:	/* DDR */
			m6502.ddr = data;
			break;
		case 0x0001:	/* Data Port */
			m6502.port = data;
			break;
	}

	if (m6502.port_write)
		m6502.port_write( m6502.ddr, m6502.port & m6502.ddr );
}

static ADDRESS_MAP_START(m6510_mem, ADDRESS_SPACE_PROGRAM, 8)
	AM_RANGE(0x0000, 0x0001) AM_READWRITE(m6510_read_0000, m6510_write_0000)
ADDRESS_MAP_END

#endif


/****************************************************************************
 * 65C02 section
 ****************************************************************************/
#if (HAS_M65C02)

void m65c02_init()
{
	m6502_common_init( SUBTYPE_65C02, insn65c02, "m65c02");
}

void m65c02_reset (void)
{
	m6502_reset();
	P &=~F_D;
}

INLINE void m65c02_take_irq(void)
{
	if( !(P & F_I) )
	{
		EAD = M6502_IRQ_VEC;
		m6502_ICount -= 2;
		PUSH(PCH);
		PUSH(PCL);
		PUSH(P & ~F_B);
		P = (P & ~F_D) | F_I;		/* knock out D and set I flag */
		PCL = RDMEM(EAD);
		PCH = RDMEM(EAD+1);
		LOG(("M65c02 takes IRQ ($%04x)\n", PCD));
		m6502.irq_state = 0;
		change_pc(PCD);
	}
	m6502.pending_irq = 0;
}

int m65c02_execute(int cycles)
{
	m6502_ICount = cycles;

	change_pc(PCD);

	do
	{
		UINT8 op;
		PPC = PCD;

		op = RDOP();
		(*m6502.insn[op])();

		/* if an irq is pending, take it now */
		if( m6502.pending_irq )
			m65c02_take_irq();


		/* check if the I flag was just reset (interrupts enabled) */
		if( m6502.after_cli )
		{
			LOG(("M6502 after_cli was >0" ));
			m6502.after_cli = 0;
			if (m6502.irq_state != CLEAR_LINE)
			{
				LOG((": irq line is asserted: set pending IRQ\n"));
				m6502.pending_irq = 1;
			}
			else
			{
				LOG((": irq line is clear\n"));
			}
		}
		else
		if( m6502.pending_irq )
			m65c02_take_irq();

	} while (m6502_ICount > 0);

	return cycles - m6502_ICount;
}

void m65c02_set_irq_line(int irqline, int state)
{
	if (irqline == INPUT_LINE_NMI)
	{
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502 set_nmi_line(ASSERT)\n"));
			EAD = M6502_NMI_VEC;
			m6502_ICount -= 2;
			PUSH(PCH);
			PUSH(PCL);
			PUSH(P & ~F_B);
			P = (P & ~F_D) | F_I;		/* knock out D and set I flag */
			PCL = RDMEM(EAD);
			PCH = RDMEM(EAD+1);
			LOG(("M6502 takes NMI ($%04x)\n", PCD));
			change_pc(PCD);
		}
	}
	else
		m6502_set_irq_line(irqline,state);
}
#endif

/****************************************************************************
 * 65SC02 section
 ****************************************************************************/
#if (HAS_M65SC02)
static void m65sc02_init(int index, int clock, const void *config, int (*irqcallback)(int))
{
	m6502_common_init(index, clock, config, irqcallback, SUBTYPE_65SC02, insn65sc02, "m65sc02");
}
#endif

/****************************************************************************
 * DECO16 section
 ****************************************************************************/
#if (HAS_DECO16)

static void deco16_init(int index, int clock, const void *config, int (*irqcallback)(int))
{
	m6502_common_init(index, clock, config, irqcallback, SUBTYPE_DECO16, insndeco16, "deco16");
}


static void deco16_reset (void)
{
	m6502_reset();
	m6502.subtype = SUBTYPE_DECO16;
	m6502.insn = insndeco16;

    PCL = RDMEM(DECO16_RST_VEC+1);
    PCH = RDMEM(DECO16_RST_VEC);

	m6502.sp.d = 0x01ff;	/* stack pointer starts at page 1 offset FF */
	m6502.p = F_T|F_I|F_Z|F_B|(P&F_D);	/* set T, I and Z flags */
	m6502.pending_irq = 0;	/* nonzero if an IRQ is pending */
	m6502.after_cli = 0;	/* pending IRQ and last insn cleared I */

	change_pc(PCD);
}

INLINE void deco16_take_irq(void)
{
	if( !(P & F_I) )
	{
		EAD = DECO16_IRQ_VEC;
		m6502_ICount -= 2;
		PUSH(PCH);
		PUSH(PCL);
		PUSH(P & ~F_B);
		P |= F_I;		/* set I flag */
		PCL = RDMEM(EAD+1);
		PCH = RDMEM(EAD);
		LOG(("M6502 takes IRQ ($%04x)\n", PCD));
		/* call back the cpuintrf to let it clear the line */
		m6502.irq_state = 0;
		change_pc(PCD);
	}
	m6502.pending_irq = 0;
}

static void deco16_set_irq_line(int irqline, int state)
{
	if (irqline == INPUT_LINE_NMI)
	{
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502 set_nmi_line(ASSERT)\n"));
			EAD = DECO16_NMI_VEC;
			m6502_ICount -= 7;
			PUSH(PCH);
			PUSH(PCL);
			PUSH(P & ~F_B);
			P |= F_I;		/* set I flag */
			PCL = RDMEM(EAD+1);
			PCH = RDMEM(EAD);
			LOG(("M6502 takes NMI ($%04x)\n", PCD));
			change_pc(PCD);
		}
	}
	else
	{
		if( irqline == M6502_SET_OVERFLOW )
		{
			if( m6502.so_state && !state )
			{
				LOG(( "M6502 set overflow\n"));
				P|=F_V;
			}
			m6502.so_state=state;
			return;
		}
		m6502.irq_state = state;
		if( state != CLEAR_LINE )
		{
			LOG(( "M6502 set_irq_line(ASSERT)\n"));
			m6502.pending_irq = 1;
		}
	}
}

static int deco16_execute(int cycles)
{
	m6502_ICount = cycles;

	change_pc(PCD);

	do
	{
		UINT8 op;
		PPC = PCD;

		op = RDOP();
		(*m6502.insn[op])();

		/* if an irq is pending, take it now */
		if( m6502.pending_irq )
			deco16_take_irq();


		/* check if the I flag was just reset (interrupts enabled) */
		if( m6502.after_cli )
		{
			LOG(("M6502 after_cli was >0"));
			m6502.after_cli = 0;
			if (m6502.irq_state != CLEAR_LINE)
			{
				LOG((": irq line is asserted: set pending IRQ\n"));
				m6502.pending_irq = 1;
			}
			else
			{
				LOG((": irq line is clear\n"));
			}
		}
		else
		if( m6502.pending_irq )
			deco16_take_irq();

	} while (m6502_ICount > 0);

	return cycles - m6502_ICount;
}

#endif

