
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                       MC68000 INTERFACE (STARSCREAM)                       */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"

#include "starcpu.h"

#define MAX_68000	(2)
#define MAX_PROGRAM	(4)
#define MAX_DATA	(32)

// A ReadLong for StarScream (a mix of intel and motorola ways...)
#define ReadLongSc(a) ((ReadWord(a)<<16) | ReadWord(a+2))
#define WriteLongSc(a,b) WriteWord(a,(b)>>16); WriteWord(a+2,((b)&0xffff))

extern struct S68000CONTEXT            M68000_context[MAX_68000];
extern struct STARSCREAM_DATAREGION    M68000_dataregion_ww[MAX_68000][MAX_DATA];

/*
 *  Fill in the basic structures via these functions...
 */

void AddMemFetch (UINT32 d0, UINT32 d1, UINT8 *d2);
void AddReadByte (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddReadWord (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
// AddReadByte + AddReadWord :
void AddReadBW (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

void AddWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddWriteWord(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddWriteBW(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
// AddReadByte+AddReadWord+AddWriteByte+AddWriteWord !!!
void AddRWBW (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void add_68000_ram(int cpu,UINT32 d0, UINT32 d1, UINT8 *d2);
void add_68000_rom(int cpu,UINT32 d0, UINT32 d1, UINT8 *d2);
void add_68000_program_region(UINT32 cpu, UINT32 d0, UINT32 d1, UINT8 *d2);
void add_68000_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void add_68000_rw(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void add_68000_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void add_68000_ww(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

void quiet_reset_handler();
void AddResetHandler(void *d0);

void AddMemFetchMC68000B (UINT32 d0, UINT32 d1, UINT8 *d2);
void AddReadByteMC68000B (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddReadWordMC68000B (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddWriteByteMC68000B(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddWriteWordMC68000B(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

void Add68000Code(int cpu, int offset, int region);

/*
 *  Set Memory pointers to our structures...
 */

void AddInitMemory(void);
void AddInitMemoryMC68000B(void);

void M68000A_load_update(void);
void M68000A_save_update(void);
void M68000B_load_update(void);
void M68000B_save_update(void);

void WriteStarScreamByte(UINT32 address, UINT8 data);
UINT8 ReadStarScreamByte(UINT32 address);

void Clear68000List(void);

/*
 *  Helper Functions for Starscream memory read/write structs
 *  ---------------------------------------------------------
 */

void Stop68000(UINT32 address, UINT8 data);

UINT8 DefBadReadByte(UINT32 address);
UINT16 DefBadReadWord(UINT32 address);
void DefBadWriteByte(UINT32 address, UINT8 data);
void DefBadWriteWord(UINT32 address, UINT16 data);

/*
 *  Byte Swapping
 */

void finish_conf_68000(int cpu);

void set_68000_io(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

void set_68000_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void set_68000_rw(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void set_68000_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void set_68000_ww(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

void s68000_get_ram(UINT32 cpu, UINT32 *range, UINT32 *count);
UINT8 *s68k_get_userdata(UINT32 cpu, UINT32 adr);
UINT8 *s68k_get_code_range(UINT32 cpu, UINT32 adr, UINT32 *start, UINT32 *end);
void *get_userfunc(UINT32 cpu, int read, int size, int off_start, UINT32 offset);

// misc debuging...

int insert_wb(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
int insert_ww(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
int insert_rb(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
int insert_rw(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

void del_wb(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void del_ww(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void del_rb(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void del_rw(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

#ifdef __cplusplus
}
#endif
