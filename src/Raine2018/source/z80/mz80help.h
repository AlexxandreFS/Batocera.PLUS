
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                          RAINE INTERFACE FOR MZ80                          */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"
#include "mz80.h"

#define MAX_Z80		(4)
#define MAX_Z80_DATA	(32)
#define MAX_Z80_PORT	(16)

extern UINT8 *ROM_BANK[MAX_Z80];

extern struct mz80context	Z80_context[MAX_Z80];
extern struct MemoryReadByte	Z80_memory_rb[MAX_Z80][MAX_Z80_DATA];
extern struct MemoryWriteByte	Z80_memory_wb[MAX_Z80][MAX_Z80_DATA];
extern struct z80PortRead	Z80_port_rb[MAX_Z80][MAX_Z80_PORT];
extern struct z80PortWrite	Z80_port_wb[MAX_Z80][MAX_Z80_PORT];
extern UINT8 *Z80RAM;

void write_z80_bank(int cpu, int n, int address, int data);
int read_z80_bank(int cpu, int n, int address);
// Set a specific data bank (read only), specific to neogeo
void z80_set_read_db(int cpu, int bank, UINT8 *src);

void AddZ80AROMBase(UINT8 *d0, UINT16 d1, UINT16 d2);

void AddZ80AReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80AWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
#define AddZ80ARead AddZ80AReadByte
#define AddZ80AWrite AddZ80AWriteByte
#define AddZ80BRead AddZ80BReadByte
#define AddZ80BWrite AddZ80BWriteByte
#define AddZ80CRead AddZ80CReadByte
#define AddZ80CWrite AddZ80CWriteByte
#define AddZ80ARW(d0,d1,d2,d3) \
  AddZ80ARead(d0,d1,d2,d3); \
  AddZ80AWrite(d0,d1,d2,d3);

#define AddZ80BRW(d0,d1,d2,d3) \
  AddZ80BRead(d0,d1,d2,d3); \
  AddZ80BWrite(d0,d1,d2,d3);

void z80_get_ram(UINT32 cpu, UINT32 *range, UINT32 *count);
UINT8 *z80_get_userdata(UINT32 cpu, UINT32 adr);
void AddZ80AReadPort( UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);
void AddZ80AWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);

void AddZ80AInit(void);

void AddZ80BROMBase(UINT8 *d0, UINT16 d1, UINT16 d2);

void AddZ80BReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80BWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80BReadPort( UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);
void AddZ80BWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);

void AddZ80BInit(void);

void AddZ80CROMBase(UINT8 *d0, UINT16 d1, UINT16 d2);

void AddZ80CReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80CWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80CReadPort( UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);
void AddZ80CWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);

#define AddZ80CRW(d0,d1,d2,d3) \
  AddZ80CRead(d0,d1,d2,d3); \
  AddZ80CWrite(d0,d1,d2,d3);

void AddZ80CInit(void);

void AddZ80DROMBase(UINT8 *d0, UINT16 d1, UINT16 d2);

void AddZ80DReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80DWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80DReadPort( UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);
void AddZ80DWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);

void AddZ80DInit(void);

void Z80A_load_update(void);
void Z80B_load_update(void);
void Z80C_load_update(void);
void Z80D_load_update(void);

/*----------------------------------------------*/

void ClearZ80List(void);

void StopZ80(UINT16 address, UINT8 data);

void SetStopZ80Mode2(UINT16 address);
void StopZ80Mode2(UINT16 address, UINT8 data);

void SetStopZ80BMode2(UINT16 address);
void StopZ80BMode2(UINT16 address, UINT8 data);

void SetStopZ80CMode2(UINT16 address);
void StopZ80CMode2(UINT16 address, UINT8 data);

void SetStopZ80DMode2(UINT16 address);
void StopZ80DMode2(UINT16 address, UINT8 data);

UINT16 DefBadReadZ80(UINT16 offset);
void DefBadWriteZ80(UINT16 offset, UINT8 data);
UINT16 DefBadReadPortZ80(UINT16 offset);
void DefBadWritePortZ80(UINT16 offset, UINT8 data);

void finish_conf_z80(int cpu);
void finish_conf_z80_ports(int cpu);

#define DefBadReadPort DefBadReadPortZ80
#define DefBadWritePort DefBadWritePortZ80

// SetDataBank : just assign the bank to src, without moving the z80base
void Z80SetDataBank(int cpu,UINT8 *src);
void Z80SetBank(int cpu,UINT8 *src);

// compatibility with old bank "interface"
#define Z80ASetBank(src) Z80SetBank(0,src)
#define Z80BSetBank(src) Z80SetBank(1,src)
#define Z80CSetBank(src) Z80SetBank(2,src)
#define Z80DSetBank(src) Z80SetBank(3,src)

void WriteMZ80Byte(UINT32 address, UINT8 data);
UINT8 ReadMZ80Byte(UINT32 address);

// Bankswitch (regions)
// for the comments about banks (how they work) see mz80help.c

void reset_z80_banks(); // automatically called in default.c
void z80_init_banks(int cpu,UINT32 region,UINT32 offset, UINT16 len);
void z80_set_bank(int cpu, UINT8 data);
void z80_set_data_bank(int cpu, UINT16 data);
int z80_get_current_bank(int cpu);
void z80_init_data_banks(int cpu,UINT32 region,UINT32 offset, UINT16 len);
void z80_init_banks_gap(int cpu,UINT32 region,UINT32 offset,
			UINT32 bank_start,UINT16 len);
// Same thing, but without regions (region = pointer+length after all).
void z80_init_banks_area(int cpu,UINT8 *rom, int rom_size, UINT32 offset,
			 UINT16 len);
void z80_init_data_banks_area(int cpu,UINT8 *rom,int rom_size,UINT32 offset,
			      UINT16 len);
void z80_init_banks_area_gap(int cpu,UINT8 *rombase, int rom_size,
			     UINT32 offset,UINT32 bank_start,UINT16 len);
// Same thing with an offset in the banks (banks 0-bank_offs unused or ram)
void z80_init_banks_area_ofs(int cpu,UINT8 *rombase, int rom_size,
			     UINT32 offset,UINT16 len,UINT16 bank_offs);

void z80a_set_bank(UINT16 offset,UINT8 data); // Let's keep this one for compatibility with handlers

// latch (sound commands)

extern int latch;

UINT8 soundlatch_lo_r(UINT32 offset);
UINT8 soundlatch_hi_r(UINT32 offset);
void soundcmd_w(UINT32 offset,UINT16 data);
void soundcmd_wb(UINT32 offset,UINT8 data);
void soundcmd_w_nonmi(UINT32 offset,UINT16 data);
void soundcmd_wb_nonmi(UINT32 offset,UINT8 data);

#ifdef RAINE_DEBUG
// debuger functions
int add_z80_debug_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2);
void remove_z80_debug_rb(UINT32 cpu, int index);
void add_z80_port_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2);
void remove_z80_port_wb(UINT32 cpu, int index);
UINT32 mz80GetPC();
UINT8* mz80GetBase(int cpu);
void mz80ReleaseIRQ(int cpu);
void mz80ClearTimers();
UINT32 mz80GetCyclesDone();
void mz80AddCyclesDone(int cycles);
int mz80GetCyclesRemaining();

void allow_writebank(int allow);

#endif

#ifdef __cplusplus
}
#endif
