
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                        M6502 INTERFACE (MAKE-6502)                         */
/*                                                                            */
/******************************************************************************/

#include "deftypes.h"
#include "m6502.h"

#define MAX_6502	(3)

struct m6502context	M6502_context[MAX_6502];

struct MemoryReadByte	M6502A_memoryreadbyte[32];
struct MemoryWriteByte	M6502A_memorywritebyte[32];
extern UINT8 *M6502ROM;         // Pointer for Z80ROM memory
extern int M6502Engine;         // Number of M6502's in use

/*
 *  Fill in the basic structures via these functions...
 */

void AddM6502AROMBase(UINT8 *d0);

void AddM6502AReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
#define AddM6502ARead(d0,d1,d2,d3) AddM6502AReadByte(d0,d1,d2,d3)

void AddM6502AWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
#define AddM6502AWrite(d0,d1,d2,d3) AddM6502AWriteByte(d0,d1,d2,d3)

void AddM6502ARW( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

/*
 *  Set Memory pointers to our structures...
 */

void AddM6502AInit(void);

/*
 *  Allocate basic structures. Make sure you allocate
 *  enough room for all memory entries (Max of 32)!
 */

struct MemoryReadByte	M6502B_memoryreadbyte[32];
struct MemoryWriteByte	M6502B_memorywritebyte[32];

/*
 *  Fill in the basic structures via these functions...
 */

void AddM6502BROMBase(UINT8 *d0);

void AddM6502BReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
#define AddM6502BRead(d0,d1,d2,d3) AddM6502BReadByte(d0,d1,d2,d3)
void AddM6502BWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
#define AddM6502BWrite(d0,d1,d2,d3) AddM6502BWriteByte(d0,d1,d2,d3)

/*
 *  Set Memory pointers to our structures...
 */

void AddM6502BInit(void);

/*
 *  Allocate basic structures. Make sure you allocate
 *  enough room for all memory entries (Max of 32)!
 */

struct MemoryReadByte	M6502C_memoryreadbyte[32];
struct MemoryWriteByte	M6502C_memorywritebyte[32];
/*
 *  Fill in the basic structures via these functions...
 */

void AddM6502CROMBase(UINT8 *d0);

void AddM6502CReadByte( UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);
void AddM6502CWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3);

/*
 *  Set Memory pointers to our structures...
 */

void AddM6502CInit(void);

void M6502A_load_update(void);
void M6502B_load_update(void);
void M6502C_load_update(void);

/*----------------------------------------------*/

void ClearM6502List(void);

void StopM6502(UINT16 address, UINT8 data);

void SetStopM6502Mode2(UINT16 address);
void StopM6502Mode2(UINT16 address, UINT8 data);

void SetStopM6502BMode2(UINT16 address);
void StopM6502BMode2(UINT16 address, UINT8 data);

void SetStopM6502CMode2(UINT16 address);
void StopM6502CMode2(UINT16 address, UINT8 data);

UINT8 DefBadReadM6502(UINT16 offset);
void DefBadWriteM6502(UINT16 offset, UINT8 data);

void M6502ASetBank(UINT8 *src);
void M6502BSetBank(UINT8 *src);
void M6502CSetBank(UINT8 *src);

void M6502_disp_context(int nb);
void M6502WriteByte(UINT32 address, UINT16 data);
UINT8 M6502ReadByte(UINT32 address);

#ifdef __cplusplus
}
#endif
