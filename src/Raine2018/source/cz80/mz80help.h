#ifndef _MZ80HELP
#define _MZ80HELP

#ifdef __cplusplus
extern "C" {
#endif

    /* Compatibility layer for cz80 using the mz80 interface... */
#include "mz80.h"

#define MAX_Z80		(4)
#define MAX_Z80_DATA	(32)
#define MAX_Z80_PORT	(16)

extern cz80_struc	Z80_context[MAX_Z80];
extern struct MemoryReadByte	Z80_memory_rb[MAX_Z80][MAX_Z80_DATA];
extern struct MemoryWriteByte	Z80_memory_wb[MAX_Z80][MAX_Z80_DATA];
extern struct z80PortRead	Z80_port_rb[MAX_Z80][MAX_Z80_PORT];
extern struct z80PortWrite	Z80_port_wb[MAX_Z80][MAX_Z80_PORT];
extern UINT8 *Z80RAM;
extern int cyclesRemaining; // dummy to workaround some mz80 bug !
extern int Z80Has16bitsPorts;
extern int z80_offdata; // for kabuki encryption, not supported yet

void AddZ80AInit(void);
void AddZ80BInit(void);
void AddZ80AROMBase(UINT8 *d0, UINT16 d1, UINT16 d2);
void AddZ80BROMBase(UINT8 *d0, UINT16 d1, UINT16 d2);
void AddZ80AReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80AWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80BReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddZ80BWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
#define AddZ80ARead AddZ80AReadByte
#define AddZ80AWrite AddZ80AWriteByte
#define AddZ80BRead AddZ80BReadByte
#define AddZ80BWrite AddZ80BWriteByte
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
void AddZ80BReadPort( UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);
void AddZ80BWritePort(UINT16 d0, UINT16 d1, void *d2, UINT8 *d3);

UINT16 DefBadReadZ80(UINT16 offset);
void DefBadWriteZ80(UINT16 offset, UINT8 data);
UINT16 DefBadReadPortZ80(UINT16 offset);
void DefBadWritePortZ80(UINT16 offset, UINT8 data);

#define DefBadReadPort DefBadReadPortZ80
#define DefBadWritePort DefBadWritePortZ80

UINT8 ReadMZ80Byte(UINT32 address);
void WriteMZ80Byte(UINT32 address, UINT8 data);

void ClearZ80List(void);
void mz80GetContext(cz80_struc *);
void mz80SetContext(cz80_struc *);
void mz80reset(void);
UINT32 mz80int(UINT32);
UINT32 mz80nmi(void);
UINT32 mz80exec(unsigned long int);
UINT32 mz80GetPC();
UINT8* mz80GetBase(int cpu);
void mz80ReleaseIRQ(int cpu);
void mz80ClearTimers();
UINT32 mz80GetCyclesDone();
int mz80GetCyclesRemaining();

// banks, not done yet

void reset_z80_banks();

extern int latch;

UINT8 soundlatch_lo_r(UINT32 offset);

void StopZ80Mode2(UINT16 address, UINT8 data);
void StopZ80BMode2(UINT16 address, UINT8 data);
void StopZ80CMode2(UINT16 address, UINT8 data);
void mz80AddCyclesDone(int cycles);
void finish_conf_z80(int cpu);
void allow_writebank(int allow);

#ifdef __cplusplus
}
#endif

#endif
