#ifndef	_MZ80_H_
#define	_MZ80_H_

#include "cz80.h"
#include "deftypes.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MEMORYREADWRITEBYTE_
#define _MEMORYREADWRITEBYTE_

struct MemoryWriteByte
{
	UINT32 lowAddr;
	UINT32 highAddr;
	void (*memoryCall)(UINT32, UINT32);
	UINT8 *pUserArea;
};

struct MemoryReadByte
{
	UINT32 lowAddr;
	UINT32 highAddr;
	UINT8 (*memoryCall)(UINT32);
	UINT8 *pUserArea;
};

#endif // _MEMORYREADWRITEBYTE_

struct z80PortWrite
{
	UINT16 lowIoAddr;
	UINT16 highIoAddr;
	void (*IOCall)(UINT32, UINT32);
	UINT8 *pUserArea;
};

struct z80PortRead
{
	UINT16 lowIoAddr;
	UINT16 highIoAddr;
	UINT16 (*IOCall)(UINT32);
	UINT8 *pUserArea;
};

#ifdef __cplusplus
}
#endif
#endif

