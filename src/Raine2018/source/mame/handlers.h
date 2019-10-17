
#ifdef __cplusplus
extern "C" {
#endif
#ifndef READ_HANDLER

#ifdef __GNU__
#define UNUSEDARG __attribute__((__unused__))
#else
#define UNUSEDARG
#endif

/* ----- typedefs for data and offset types ----- */
typedef UINT8			data8_t;
typedef UINT16			data16_t;
typedef UINT32			data32_t;
typedef UINT32			offs_t;
/* ----- typedefs for the various common memory/port handlers ----- */
typedef data8_t			(*read8_handler)  (UNUSEDARG offs_t offset);
typedef void			(*write8_handler) (UNUSEDARG offs_t offset, UNUSEDARG data8_t data);
typedef data16_t		(*read16_handler) (UNUSEDARG offs_t offset);
typedef void			(*write16_handler)(UNUSEDARG offs_t offset, UNUSEDARG data16_t data, UNUSEDARG data16_t mem_mask);
typedef data32_t		(*read32_handler) (UNUSEDARG offs_t offset);
typedef void			(*write32_handler)(UNUSEDARG offs_t offset, UNUSEDARG data32_t data, UNUSEDARG data32_t mem_mask);
typedef offs_t			(*opbase_handler) (UNUSEDARG offs_t address);

/* From a very helpfull email from raine-dev :
   move.w d0, 0x1000
  Calls write handler, offset=0x800, data=0x1234, mem_mask=0x0000
    ACCESSING_MSB=true, ACCESSING_LSB=true

move.b d0, 0x1000
  Calls write handler, offset=0x800, data=0x34??, mem_mask=0x00ff
    ACCESSING_MSB=true, ACCESSING_LSB=false

move.b d0, 0x1001
  Calls write handler, offset=0x800, data=0x??34, mem_mask=0xff00
    ACCESSING_MSB=false, ACCESSING_LSB=true

    So if you want to use these in raine, you have to handle manually
    the mem_mask...
*/

/* ----- 16-bit memory accessing ----- */
#define ACCESSING_LSB16				((mem_mask & 0x00ff) == 0)
#define ACCESSING_MSB16				((mem_mask & 0xff00) == 0)
#define ACCESSING_LSB				ACCESSING_LSB16
#define ACCESSING_MSB				ACCESSING_MSB16

typedef read8_handler	mem_read_handler;
typedef write8_handler	mem_write_handler;
typedef read16_handler	mem_read16_handler;
typedef write16_handler	mem_write16_handler;
typedef read32_handler	mem_read32_handler;
typedef write32_handler	mem_write32_handler;
/* ----- typedefs for the various common port handlers ----- */
typedef read8_handler	port_read_handler;
typedef write8_handler	port_write_handler;
typedef read16_handler	port_read16_handler;
typedef write16_handler	port_write16_handler;
typedef read32_handler	port_read32_handler;
typedef write32_handler	port_write32_handler;

// cpuintf
#define CLEAR_LINE		0		/* clear (a fired, held or pulsed) line */
#define ASSERT_LINE     1       /* assert an interrupt immediately */
#define HOLD_LINE       2       /* hold interrupt line until enable is true */
#define PULSE_LINE		3		/* pulse interrupt line for one instruction */

/***************************************************************************
	Core memory read/write/opbase handler types.
***************************************************************************/

/* ----- macros for declaring the various common memory/port handlers ----- */
#define READ_HANDLER(name) 		data8_t  name(UNUSEDARG offs_t offset)
#define WRITE_HANDLER(name) 	void     name(UNUSEDARG offs_t offset, UNUSEDARG data8_t data)
#define READ16_HANDLER(name)	data16_t name(UNUSEDARG offs_t offset)
#define WRITE16_HANDLER(name)	void     name(UNUSEDARG offs_t offset, UNUSEDARG data16_t data, UNUSEDARG data16_t mem_mask)
#define READ32_HANDLER(name)	data32_t name(UNUSEDARG offs_t offset)
#define WRITE32_HANDLER(name)	void     name(UNUSEDARG offs_t offset, UNUSEDARG data32_t data, UNUSEDARG data32_t mem_mask)
#define OPBASE_HANDLER(name)	offs_t   name(UNUSEDARG offs_t address)

void logerror(const char *text, ...); // convinient debuging

#define memory_region(x) load_region[x]
#define memory_region_length(x) get_region_size(x)
#define activecpu_get_pc s68000readPC

#endif

#ifdef __cplusplus
}
#endif
