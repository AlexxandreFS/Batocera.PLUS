
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/*                                                                            */
/*                            RAINE MEMORY MANAGEMENT                         */
/*                                                                            */
/******************************************************************************/

#ifndef __newmem_h_
#define __newmem_h_

#include "deftypes.h"

// ---
// Memory leak tracking, from Mirko Buffoni !!
// ---

#ifdef MEMORY_DEBUG

#define malloc(A) mymalloc(A, __FILE__, __LINE__)
#define realloc(A,B) myrealloc(A, B, __FILE__, __LINE__)
#define free(A) myfree(A, __FILE__, __LINE__)
#define InitPurify mbInitPurify
#define DonePurify mbDonePurify

void mbInitPurify(void);
void mbDonePurify(void);
void *mymalloc(UINT32 size, char *fname, UINT32 fline);
void *myrealloc(void *ptr, UINT32 size, char *fname, UINT32 fline);
void myfree(void *ptr, char *fname, UINT32 fline);

#endif

// ---

void *AllocateMem(UINT32 size);

void FreeMem(void *mem);

void ResetMemoryPool(void);

void FreeMemoryPool(void);
int GetMemoryPoolSize();
void ByteSwap(UINT8 *MEM, UINT32 size);

#endif // __newmem_h_

#ifdef __cplusplus
}
#endif
