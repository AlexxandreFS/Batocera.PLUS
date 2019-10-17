
#ifdef __cplusplus
extern "C" {
#endif
/*
 *  RAINE 68020 Interface with UAE engine
 */

#include "raine.h"

#define uae_u8 UINT8
#define uae_s8 INT8
#define uae_u16 UINT16
#define uae_s16 INT16
#define uae_u32 UINT32
#define uae_s32 INT32
#define uaecptr CPTR

#define get_byte(a) cpu_readmem24(a)
#define get_word(a) cpu_readmem24_word(a)
#define get_long(a) cpu_readmem24_dword(a)

#define put_byte(a,d) cpu_writemem24(a,d)
#define put_word(a,d) cpu_writemem24_word(a,d)
#define put_long(a,d) cpu_writemem24_dword(a,d)

// Reset 68020():
//
// Reset 68020 regs and read Stack/PC from Vector table

void Reset68020(void);

// Execute68020(int c):
//
// Execute 68020 for c cycles

void Execute68020(int c);

// Interrupt68020(int level):
//
// Attempt to call Interrupt level (if Interrupt level is in enabled in SR)

void Interrupt68020(int level);

// Stop68020():
//
// Stop Execute68020() loop (for speed hacks)

void Stop68020(void);

#ifdef __cplusplus
}
#endif
