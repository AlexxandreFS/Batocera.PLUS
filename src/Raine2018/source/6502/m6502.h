/* Multi-6502 32 Bit emulator */

/* Copyright 1996, 1997, 1998, Neil Bradley, All rights reserved
 *
 * License agreement:
 *
 * (M6502 Refers to both the assembly code emitted by make6502.c and make6502.c
 * itself)
 *
 * M6502 May be distributed in unmodified form to any medium.
 *
 * M6502 May not be sold, or sold as a part of a commercial package without
 * the express written permission of Neil Bradley (neil@synthcom.com). This
 * includes shareware.
 *
 * Modified versions of M6502 may not be publicly redistributed without author
 * approval (neil@synthcom.com). This includes distributing via a publicly
 * accessible LAN. You may make your own source modifications and distribute
 * M6502 in source or object form, but if you make modifications to M6502
 * then it should be noted in the top as a comment in make6502.c.
 *
 * M6502 Licensing for commercial applications is available. Please email
 * neil@synthcom.com for details.
 *
 * Synthcom Systems, Inc, and Neil Bradley will not be held responsible for
 * any damage done by the use of M6502. It is purely "as-is".
 *
 * If you use M6502 in a freeware application, credit in the following text:
 *
 * "Multi-6502 CPU emulator by Neil Bradley (neil@synthcom.com)"
 *
 * must accompany the freeware application within the application itself or
 * in the documentation.
 *
 * Legal stuff aside:
 *
 * If you find problems with M6502, please email the author so they can get
 * resolved. If you find a bug and fix it, please also email the author so
 * that those bug fixes can be propogated to the installed base of M6502
 * users. If you find performance improvements or problems with M6502, please
 * email the author with your changes/suggestions and they will be rolled in
 * with subsequent releases of M6502.
 *
 * The whole idea of this emulator is to have the fastest available 32 bit
 * Multi-6502 emulator for the PC, giving maximum performance.
 */

/* General 6502 related goodies */

#ifndef _M6502_H_
#define _M6502_H_

/* #ifndef UINT32 */
/* #define UINT32  unsigned long int */
/* #endif */

/* #ifndef UINT16 */
/* #define UINT16  unsigned short int */
/* #endif */

/* #ifndef UINT8 */
/* #define UINT8   unsigned char */
/* #endif */

#ifdef __cplusplus
extern "C" {
#endif

extern UINT32 m6502nmi(void);
extern UINT32 m6502int(UINT32);
extern UINT32 m6502exec(UINT32);
extern void m6502reset(void);
extern UINT32 m6502GetElapsedTicks(UINT32);
extern void m6502ReleaseTimeslice();

extern UINT32 m6502zpnmi(void);
extern UINT32 m6502zpint(UINT32);
extern UINT32 m6502zpexec(UINT32);
extern void m6502zpreset(void);
extern UINT32 m6502zpGetElapsedTicks(UINT32);
extern void m6502zpReleaseTimeslice();

extern UINT32 m6502bsnmi(void);
extern UINT32 m6502bsint(UINT32);
extern UINT32 m6502bsexec(UINT32);
extern void m6502bsreset(void);
extern UINT32 m6502bsGetElapsedTicks(UINT32);
extern void m6502bsReleaseTimeslice();

extern UINT16 m6502bspc;
extern UINT16 m6502zppc;
extern UINT16 m6502pc;

UINT8 *m6502Base;		// Must make global in the asm

#ifndef _MEMORYREADWRITEBYTE_
#define _MEMORYREADWRITEBYTE_

struct MemoryWriteByte
{
	UINT32 lowAddr;
	UINT32 highAddr;
	void (*memoryCall)(UINT32, UINT8, struct MemoryWriteByte *);
	void *pUserArea;
};

struct MemoryReadByte
{
	UINT32 lowAddr;
	UINT32 highAddr;
	UINT8 (*memoryCall)(UINT32, struct MemoryReadByte *);
	void *pUserArea;
};

#endif // _MEMORYREADWRITEBYTE_

/* WARNING: Do not use a sizeof() operator on this structure. The assembly
 * code will pack other context relevant data after this space. Use the
 * GetContextSize() call to obtain the specifics of the context.
 */

struct m6502context
{
	UINT8 *m6502Base;                               /* 32 Bit pointer to base memory address */

	/* 32 Bit pointers to user trap address structure array */

	struct MemoryReadByte *m6502MemoryRead;
	struct MemoryWriteByte *m6502MemoryWrite;

	/* This context's register dump */

	UINT16 m6502af;                 /* A & Flags */
	UINT16 m6502pc;                 /* Program counter */
	UINT8 m6502x;                   /* X register */
	UINT8 m6502y;                   /* Y register */
	UINT8 m6502s;                   /* S register */
	UINT8 irqPending;
};

struct m6502bscontext
{
	UINT8 *m6502Base;                               /* 32 Bit pointer to base memory address */

	/* 32 Bit pointers to user trap address structure array */

	struct MemoryReadByte *m6502MemoryRead;
	struct MemoryWriteByte *m6502MemoryWrite;

	UINT8 *pbBankSwitch[32];		/* 32 2K addresses */

	/* This context's register dump */

	UINT16 m6502af;                 /* A & Flags */
	UINT16 m6502pc;                 /* Program counter */
	UINT8 m6502x;                   /* X register */
	UINT8 m6502y;                   /* Y register */
	UINT8 m6502s;                   /* S register */
	UINT8 irqPending;
};

typedef struct m6502context CONTEXTM6502;
typedef struct m6502bscontext CONTEXTM6502BS;

extern void m6502SetContext(struct m6502context *);
extern void m6502GetContext(struct m6502context *);
extern UINT32 m6502GetContextSize(void);

extern void m6502zpSetContext(struct m6502context *);
extern void m6502zpGetContext(struct m6502context *);
extern UINT32 m6502zpGetContextSize(void);

extern void m6502bsSetContext(struct m6502context *);
extern void m6502bsGetContext(struct m6502context *);
extern UINT32 m6502bsGetContextSize(void);

extern void m6502init(void);
extern void m6502zpinit(void);
extern void m6502bsinit(void);

extern UINT8 *m6502bspbBankSwitch[32];	// Bank switching registers

#ifdef __cplusplus
};
#endif

#endif // _M6502_H_
