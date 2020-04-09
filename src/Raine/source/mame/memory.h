
#ifdef __cplusplus
extern "C" {
#endif
#ifndef MEMORY_H
#define MEMORY_H

#include "deftypes.h"
/* memory.h */

#ifdef __GNU__
#define UNUSEDARG __attribute__((__unused__))
#else
#define UNUSEDARG
#endif

/***************************************************************************

	Basic type definitions
	
	These types are used for memory handlers.

***************************************************************************/

#include "handlers.h"

/***************************************************************************

Note that the memory hooks are not passed the actual memory address where
the operation takes place, but the offset from the beginning of the block
they are assigned to. This makes handling of mirror addresses easier, and
makes the handlers a bit more "object oriented". If you handler needs to
read/write the main memory area, provide a "base" pointer: it will be
initialized by the main engine to point to the beginning of the memory block
assigned to the handler. You may also provided a pointer to "size": it
will be set to the length of the memory area processed by the handler.

***************************************************************************/

struct MemoryReadAddress
{
	offs_t start, end;
  int type;
};

/***************************************************************************

	Memory/port array constants
	
	These apply to values in the array of read/write handlers that is
	declared within each driver.

***************************************************************************/

/* ----- structs for memory read arrays ----- */
struct Memory_ReadAddress
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	int type;		/* type in raine (ram, rom) */
};

struct Memory_WriteAddress
{
    offs_t				start, end;		/* start, end addresses, inclusive */
  int type;
};

/* ----- memory/port width constants ----- */
#define MEMPORT_WIDTH_MASK		0x00000003				/* mask to get at the width bits */
#define MEMPORT_WIDTH_8			0x00000001				/* this memory/port array is for an 8-bit databus */
#define MEMPORT_WIDTH_16 		0x00000002				/* this memory/port array is for a 16-bit databus */
#define MEMPORT_WIDTH_32 		0x00000003				/* this memory/port array is for a 32-bit databus */

/* ----- memory/port type constants ----- */
#define MEMPORT_TYPE_MASK		0x30000000				/* mask to get at the type bits */
#define MEMPORT_TYPE_MEM 		0x10000000				/* this memory/port array is for memory */
#define MEMPORT_TYPE_IO			0x20000000				/* this memory/port array is for ports */

/* ----- memory/port direction constants ----- */
#define MEMPORT_DIRECTION_MASK	0xc0000000				/* mask to get at the direction bits */
#define MEMPORT_DIRECTION_READ	0x40000000				/* this memory/port array is for reads */
#define MEMPORT_DIRECTION_WRITE	0x80000000				/* this memory/port array is for writes */

/* ----- memory/port address bits constants ----- */
#define MEMPORT_ABITS_MASK		0x08000000				/* set this bit to indicate the entry has address bits */
#define MEMPORT_ABITS_VAL_MASK	0x000000ff				/* number of address bits */

/* ----- memory/port struct marker constants ----- */
#define MEMPORT_MARKER			((offs_t)~0)			/* used in the end field to indicate end of array */

/* ----- structs for port read arrays ----- */
struct IO_ReadPort
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	port_read_handler 	handler;		/* handler callback */
};

struct IO_ReadPort16
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	port_read16_handler	handler;		/* handler callback */
};

struct IO_ReadPort32
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	port_read32_handler	handler;		/* handler callback */
};

/* ----- structs for port write arrays ----- */
struct IO_WritePort
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	port_write_handler	handler;		/* handler callback */
};

struct IO_WritePort16
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	port_write16_handler handler;		/* handler callback */
};

struct IO_WritePort32
{
	offs_t				start, end;		/* start, end addresses, inclusive */
	port_write32_handler handler;		/* handler callback */
};



/***************************************************************************

	Memory/port array macros

***************************************************************************/

/* ----- macros for identifying memory/port struct markers ----- */
#define IS_MEMPORT_MARKER(ma)		((ma)->start == MEMPORT_MARKER && (ma)->end < MEMPORT_MARKER)
#define IS_MEMPORT_END(ma)			((ma)->start == MEMPORT_MARKER && (ma)->end == 0)

/* ----- macros for defining the start/stop points ----- */
#define MEMPORT_ARRAY_START(t,n,f)	const struct t n[] = { { MEMPORT_MARKER, (f) },
#define MEMPORT_ARRAY_END			{ MEMPORT_MARKER, 0 } };

/* ----- macros for declaring the start of a port struct array ----- */
#define PORT_READ_START(name)		MEMPORT_ARRAY_START(IO_ReadPort,    name, MEMPORT_DIRECTION_READ  | MEMPORT_TYPE_IO | MEMPORT_WIDTH_8)
#define PORT_WRITE_START(name)		MEMPORT_ARRAY_START(IO_WritePort,   name, MEMPORT_DIRECTION_WRITE | MEMPORT_TYPE_IO | MEMPORT_WIDTH_8)
#define PORT_READ16_START(name)		MEMPORT_ARRAY_START(IO_ReadPort16,  name, MEMPORT_DIRECTION_READ  | MEMPORT_TYPE_IO | MEMPORT_WIDTH_16)
#define PORT_WRITE16_START(name)	MEMPORT_ARRAY_START(IO_WritePort16, name, MEMPORT_DIRECTION_WRITE | MEMPORT_TYPE_IO | MEMPORT_WIDTH_16)
#define PORT_READ32_START(name)		MEMPORT_ARRAY_START(IO_ReadPort32,  name, MEMPORT_DIRECTION_READ  | MEMPORT_TYPE_IO | MEMPORT_WIDTH_32)
#define PORT_WRITE32_START(name)	MEMPORT_ARRAY_START(IO_WritePort32, name, MEMPORT_DIRECTION_WRITE | MEMPORT_TYPE_IO | MEMPORT_WIDTH_32)

#define PORT_ADDRESS_BITS(bits)		MEMPORT_SET_BITS(bits)
#define PORT_END					MEMPORT_ARRAY_END

// Memory


#define MRA_RAM	1
#define MRA_ROM	2
#define MRA_BANK1 3

#define MWA_RAM 1
#define MWA_ROM 2

/* ----- macros for defining the start/stop points ----- */
#define MEMPORT_ARRAY_START(t,n,f)	const struct t n[] = { { MEMPORT_MARKER, (f) },
#define MEMPORT_ARRAY_END			{ MEMPORT_MARKER, 0 } };

/* ----- macros for setting the number of address bits ----- */
#define MEMPORT_SET_BITS(b)			{ MEMPORT_MARKER, MEMPORT_ABITS_MASK | (b) },

/* ----- macros for declaring the start of a memory struct array ----- */
#define MEMORY_READ_START(name)		MEMPORT_ARRAY_START(Memory_ReadAddress,    name, MEMPORT_DIRECTION_READ  | MEMPORT_TYPE_MEM | MEMPORT_WIDTH_8)
#define MEMORY_WRITE_START(name)	MEMPORT_ARRAY_START(Memory_WriteAddress,   name, MEMPORT_DIRECTION_WRITE | MEMPORT_TYPE_MEM | MEMPORT_WIDTH_8)
#define MEMORY_READ16_START(name)	MEMPORT_ARRAY_START(Memory_ReadAddress16,  name, MEMPORT_DIRECTION_READ  | MEMPORT_TYPE_MEM | MEMPORT_WIDTH_16)
#define MEMORY_WRITE16_START(name)	MEMPORT_ARRAY_START(Memory_WriteAddress16, name, MEMPORT_DIRECTION_WRITE | MEMPORT_TYPE_MEM | MEMPORT_WIDTH_16)
#define MEMORY_READ32_START(name)	MEMPORT_ARRAY_START(Memory_ReadAddress32,  name, MEMPORT_DIRECTION_READ  | MEMPORT_TYPE_MEM | MEMPORT_WIDTH_32)
#define MEMORY_WRITE32_START(name)	MEMPORT_ARRAY_START(Memory_WriteAddress32, name, MEMPORT_DIRECTION_WRITE | MEMPORT_TYPE_MEM | MEMPORT_WIDTH_32)

#define MEMORY_ADDRESS_BITS(bits)	MEMPORT_SET_BITS(bits)
#define MEMORY_END					MEMPORT_ARRAY_END

// Fonctions RAINE

void mame_addportsa(struct IO_ReadPort *rp,struct IO_WritePort *wp);
void mame_addz80mema(struct Memory_ReadAddress *rm,
		     struct Memory_WriteAddress *wm);

#endif

#ifdef __cplusplus
}
#endif
